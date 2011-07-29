/*
 * =====================================================================================
 *
 *       Filename:  https.hpp
 *
 *    Description:  HTTPS base for our library
 *
 *        Version:  1.0
 *        Created:  26/07/11 19:20:05
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matthew Sherborne (), msherborne@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#include <iostream>
#include <istream>
#include <ostream>
#include <string>
#include <sstream>
#include <stdexcept>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/case_conv.hpp>
#include <boost/lexical_cast.hpp>


using boost::asio::ip::tcp;
namespace ssl = boost::asio::ssl;
using boost::algorithm::trim;
using boost::algorithm::to_lower;
using boost::lexical_cast;
using std::string;
using std::istream;
using std::ostream;
using std::stringstream;

namespace openstack {

/**
* Gives a nice interface to buffered reads, hot off the Internet.
*/
class StreamReader {
private:
    boost::asio::streambuf _buffer;
    ssl::stream<tcp::socket>& _sslStream;
public:
    StreamReader(ssl::stream<tcp::socket>& sslStream) : _sslStream(sslStream) {}
    boost::asio::streambuf* readLine() {
       boost::asio::read_until(_sslStream, _buffer, "\r\n"); // Fill the buffer
       return &_buffer;
    }
    /**
    * @brief Copies the rest of the tcp/ip (ssl) stream into a stream.
    *
    * We pass the number of bytes because if it tries to read to eof, it'll slow things down while it waits for nothing to come down the line.
    *
    * @param destination stream to copy the data to
    * @param toReadTotal number of bytes to read max. -1 means just read until eof
    */
    void readRest(ostream& destination, long toReadTotal=-1) {
        if (toReadTotal == 0)
            return;
        // Write whatever content we already have into the destination
        unsigned int toRead = toReadTotal - _buffer.size();
        if (_buffer.size() > 0)
           destination << &_buffer;
        boost::system::error_code error;
        // Read until EOF or toRead, writing data to output as we go.
        while (boost::asio::read(_sslStream, _buffer, boost::asio::transfer_at_least(1), error)) {
            toRead -= _buffer.size();
            destination << &_buffer;
            if ((toRead == 0) && (toReadTotal > 0))
                return;
        }
        if (error != boost::asio::error::eof)
            throw boost::system::system_error(error);
    }
};

class HTTPS {
public:
    typedef std::map<string, string> Headers;
    typedef std::pair<string, string> Header;
    typedef std::map<string, string>::const_iterator cpHeader; // cp means const pointer
private:
    string _hostname;
    boost::asio::io_service io_service;
    tcp::resolver resolver;
    tcp::resolver::query query;
    ssl::context sslContext; 
    ssl::stream<tcp::socket> sslStream;
    StreamReader input;
    unsigned short checkResponse() {
        istream line(input.readLine());
        // Check that response is OK.
        string http_version;
        line >> http_version;
        unsigned short status_code;
        line >> status_code;
        string status_message;
        std::getline(line, status_message);
        if (!line || http_version.substr(0, 5) != "HTTP/") {
            throw std::runtime_error("Invalid response\n");
        }
        if ((status_code < 200) || (status_code >= 300)) {
            std::stringstream errmsg("Response returned with status code: ");
            errmsg << status_code << " - and message: " << status_message;
            throw std::runtime_error(errmsg.str());
        }
        return status_code;
    }
    void getResponseHeaders(Headers& headers) {
        while (true) {
            istream line(input.readLine());
            Header newHeader;
            getline(line, newHeader.first, ':'); // Only read up until the ':'
            trim(newHeader.first);
            to_lower(newHeader.first);
            if (newHeader.first.empty())
                break;
            getline(line, newHeader.second); // Read the rest of the line
            trim(newHeader.second);
            headers.insert(newHeader);
        }

    }
public:
    HTTPS(const string& hostname) 
        : _hostname(hostname), resolver(io_service), query(hostname, "https"), sslContext(io_service, ssl::context::sslv23), sslStream(io_service, sslContext), input(sslStream) {
        // Setup SSL
        sslContext.set_verify_mode(ssl::context::verify_peer);
        sslContext.add_verify_path("certs");
    }
    void connect() {
        // First get some IPs to try
        tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
        tcp::resolver::iterator end;
        boost::system::error_code error = boost::asio::error::host_not_found;
        tcp::socket::lowest_layer_type& socket = sslStream.lowest_layer();
        // Connect to one of the IPs
        while (error && endpoint_iterator != end) {
          socket.close();
          socket.connect(*endpoint_iterator++, error);
        }
        if (error)
          throw boost::system::system_error(error);
        // SSL bit
        sslStream.handshake(ssl::stream_base::client);
        // Connected :)
    }
    bool isConnected() { return sslStream.lowest_layer().is_open(); }
    void request(const string& path, Headers& requestHeaders, Headers& responseHeaders, ostream& body) {
        // Make up the request
        boost::asio::streambuf buffer;
        std::stringstream debug_stream;
        ostream request_stream(&buffer);
        request_stream << "GET " << path << " HTTPS/1.1\r\n";
        boost::asio::write(sslStream, buffer);
        requestHeaders.insert(Header("Host", _hostname));
        for (Headers::const_iterator i=requestHeaders.begin(); i != requestHeaders.end(); ++i) {
            request_stream << i->first << ": " << i->second << "\r\n";
            boost::asio::write(sslStream, buffer);
        }
        request_stream << "\r\n\r\n";
        // Send the buffer.
        boost::asio::write(sslStream, buffer);
        unsigned short responseCode = checkResponse();
        // Parse the response
        getResponseHeaders(responseHeaders);
        // Write whatever content we already have into the body
        cpHeader contentLengthHeader = responseHeaders.find("content-length");
        if (contentLengthHeader != responseHeaders.end()) {
            unsigned int toRead = lexical_cast<unsigned int>((*contentLengthHeader).second);
            input.readRest(body, toRead);
        } else {
            input.readRest(body);
        }
    }
};

} // namespace openstack
