/*
 * =====================================================================================
 *
 *       Filename:  url.hpp
 *
 *    Description:  Parses urls
 *
 *        Version:  1.0
 *        Created:  30/07/11 05:56:54
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matthew Sherborne (), msherborne@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef URL_HPP
#define URL_HPP

#include <sstream>
#include <string>

namespace openstack {

/**
* Very simply get the host out of a url. Doesn't check much so feed it good data.
* eh. if you input: "https://some.host.com/some/path?some=param&other=param" .. output will be some.host.com
*
* @param url The url to get the hostname out of
*
* @return the hostname, and the path part of the url
*/
std::pair<string, string> getHostAndPath(const string& url) {
    stringstream urlS(url);
    string schema, host, path;
    char slash;
    getline(urlS, schema, ':');
    urlS >> slash >> slash;
    getline(urlS, host, '/');
    getline(urlS, path, '?');
    return std::pair<string, string>(host, "/" + path);
}

} // namespace openstack {

#endif // URL_HPP

/* I was gonna do this in boost spirit, but it looked like too much work :P
#include <boost/spirit.hpp>

using namespace boost::spirit;
*/

/* EBNF of a url from http://www.ietf.org/rfc/rfc2396.txt:
 *
 * alpha    = lowalpha | upalpha
 *
 *    lowalpha = "a" | "b" | "c" | "d" | "e" | "f" | "g" | "h" | "i" |
 *               "j" | "k" | "l" | "m" | "n" | "o" | "p" | "q" | "r" |
 *               "s" | "t" | "u" | "v" | "w" | "x" | "y" | "z"
 *
 *    upalpha  = "A" | "B" | "C" | "D" | "E" | "F" | "G" | "H" | "I" |
 *               "J" | "K" | "L" | "M" | "N" | "O" | "P" | "Q" | "R" |
 *               "S" | "T" | "U" | "V" | "W" | "X" | "Y" | "Z"
 *
 *    digit    = "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" |
 *               "8" | "9"
 *
 *    alphanum = alpha | digit
 *
 *    uric          = reserved | unreserved | escaped
 *
 *    reserved    = ";" | "/" | "?" | ":" | "@" | "&" | "=" | "+" |
 *                  "$" | ","
 *
 *    unreserved  = alphanum | mark
 *
 *    mark        = "-" | "_" | "." | "!" | "~" | "*" | "'" | "(" | ")"
 *
 *    escaped     = "%" hex hex
 *    hex         = digit | "A" | "B" | "C" | "D" | "E" | "F" |
 *                          "a" | "b" | "c" | "d" | "e" | "f"
 *
 *    control     = <US-ASCII coded characters 00-1F and 7F hexadecimal>
 *    space       = <US-ASCII coded character 20 hexadecimal>
 *    delims      = "<" | ">" | "#" | "%" | <">
 *    unwise      = "{" | "}" | "|" | "\" | "^" | "[" | "]" | "`"
 *
 *  absoluteURI   = scheme ":" ( hier_part | opaque_part )
 *  hier_part     = ( net_path | abs_path ) [ "?" query ]
 *  net_path      = "//" authority [ abs_path ]
 *  abs_path      = "/"  path_segments
 *  opaque_part   = uric_no_slash *uric
 *
 *  uric_no_slash = unreserved | escaped | ";" | "?" | ":" | "@" |
 *                  "&" | "=" | "+" | "$" | ","
 *  scheme        = alpha *( alpha | digit | "+" | "-" | "." )
 *  authority     = server | reg_name
 *  reg_name      = 1*( unreserved | escaped | "$" | "," |
 *                  ";" | ":" | "@" | "&" | "=" | "+" )
 *  server        = [ [ userinfo "@" ] hostport ]
 *  userinfo      = *( unreserved | escaped |
 *                  ";" | ":" | "&" | "=" | "+" | "$" | "," )
 *  hostport      = host [ ":" port ]
 *  host          = hostname | IPv4address
 *  hostname      = *( domainlabel "." ) toplabel [ "." ]
 *  domainlabel   = alphanum | alphanum *( alphanum | "-" ) alphanum
 *  toplabel      = alpha | alpha *( alphanum | "-" ) alphanum
 *  IPv4address   = 1*digit "." 1*digit "." 1*digit "." 1*digit
 *  port          = *digit
 *
 *  path          = [ abs_path | opaque_part ]
 *
 *  path_segments = segment *( "/" segment )
 *  segment       = *pchar *( ";" param )
 *  param         = *pchar
 *
 *  pchar         = unreserved | escaped |
 *                  ":" | "@" | "&" | "=" | "+" | "$" | ","
 *
 *  query         = *uric
 *
 *  URI-reference = [ absoluteURI | relativeURI ] [ "#" fragment ]
 *  fragment      = *uric
 *  relativeURI   = ( net_path | abs_path | rel_path ) [ "?" query ]
 *  rel_path      = rel_segment [ abs_path ]
 *
 *  rel_segment   = 1*( unreserved | escaped |
 *                  ";" | "@" | "&" | "=" | "+" | "$" | "," )
 */
