// Copyright (C) 2005-2010 Code Synthesis Tools CC
//
// This program was generated by CodeSynthesis XSD, an XML Schema to
// C++ data binding compiler.
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License version 2 as
// published by the Free Software Foundation.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
//
// In addition, as a special exception, Code Synthesis Tools CC gives
// permission to link this program with the Xerces-C++ library (or with
// modified versions of Xerces-C++ that use the same license as Xerces-C++),
// and distribute linked combinations including the two. You must obey
// the GNU General Public License version 2 in all respects for all of
// the code used other than Xerces-C++. If you modify this copy of the
// program, you may extend this exception to your version of the program,
// but you are not obligated to do so. If you do not wish to do so, delete
// this exception statement from your version.
//
// Furthermore, Code Synthesis Tools CC makes a special exception for
// the Free/Libre and Open Source Software (FLOSS) which is described
// in the accompanying FLOSSE file.
//

#ifndef XSDS_FLAVOR_IPP
#define XSDS_FLAVOR_IPP

// Begin prologue.
//
//
// End prologue.

namespace openstack
{
  namespace xml
  {
    // Flavor
    // 

    inline
    const Flavor::IdType& Flavor::
    id () const
    {
      return this->id_.get ();
    }

    inline
    Flavor::IdType& Flavor::
    id ()
    {
      return this->id_.get ();
    }

    inline
    void Flavor::
    id (const IdType& x)
    {
      this->id_.set (x);
    }

    inline
    const Flavor::NameType& Flavor::
    name () const
    {
      return this->name_.get ();
    }

    inline
    Flavor::NameType& Flavor::
    name ()
    {
      return this->name_.get ();
    }

    inline
    void Flavor::
    name (const NameType& x)
    {
      this->name_.set (x);
    }

    inline
    void Flavor::
    name (::std::auto_ptr< NameType > x)
    {
      this->name_.set (x);
    }

    inline
    const Flavor::RamOptional& Flavor::
    ram () const
    {
      return this->ram_;
    }

    inline
    Flavor::RamOptional& Flavor::
    ram ()
    {
      return this->ram_;
    }

    inline
    void Flavor::
    ram (const RamType& x)
    {
      this->ram_.set (x);
    }

    inline
    void Flavor::
    ram (const RamOptional& x)
    {
      this->ram_ = x;
    }

    inline
    const Flavor::DiskOptional& Flavor::
    disk () const
    {
      return this->disk_;
    }

    inline
    Flavor::DiskOptional& Flavor::
    disk ()
    {
      return this->disk_;
    }

    inline
    void Flavor::
    disk (const DiskType& x)
    {
      this->disk_.set (x);
    }

    inline
    void Flavor::
    disk (const DiskOptional& x)
    {
      this->disk_ = x;
    }


    // Flavors
    // 

    inline
    const Flavors::FlavorSequence& Flavors::
    flavor () const
    {
      return this->flavor_;
    }

    inline
    Flavors::FlavorSequence& Flavors::
    flavor ()
    {
      return this->flavor_;
    }

    inline
    void Flavors::
    flavor (const FlavorSequence& s)
    {
      this->flavor_ = s;
    }
  }
}

// Begin epilogue.
//
//
// End epilogue.

#endif // XSDS_FLAVOR_IPP