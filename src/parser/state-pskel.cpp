// Copyright (c) 2005-2014 Code Synthesis Tools CC
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

// Begin prologue.
//
//
// End prologue.

#include <xsd/cxx/pre.hxx>

#include "state-pskel.hpp"

#include "id_type-pskel.hpp"

#include "title_type-pskel.hpp"

// state_pskel
//

void state_pskel::
id_parser (::id_type_pskel& p)
{
  this->id_parser_ = &p;
}

void state_pskel::
title_parser (::title_type_pskel& p)
{
  this->title_parser_ = &p;
}

void state_pskel::
parsers (::id_type_pskel& id,
         ::title_type_pskel& title)
{
  this->id_parser_ = &id;
  this->title_parser_ = &title;
}

state_pskel::
state_pskel ()
: id_parser_ (0),
  title_parser_ (0),
  v_state_attr_stack_ (sizeof (v_state_attr_), &v_state_attr_first_)
{
}

// state_pskel
//

void state_pskel::
id (uint32_t)
{
}

void state_pskel::
title (::std::string)
{
}

#include <cassert>

// Attribute validation and dispatch functions for state_pskel.
//
bool state_pskel::
_attribute_impl_phase_one (const ::xml_schema::ro_string& ns,
                           const ::xml_schema::ro_string& n,
                           const ::xml_schema::ro_string& s)
{
  if (n == "id" && ns.empty ())
  {
    if (this->id_parser_)
    {
      this->id_parser_->pre ();
      this->id_parser_->_pre_impl ();
      this->id_parser_->_characters (s);
      this->id_parser_->_post_impl ();
      this->id (this->id_parser_->post_id_type ());
    }

    static_cast< v_state_attr_* > (this->v_state_attr_stack_.top ())->id = true;
    return true;
  }

  if (n == "title" && ns.empty ())
  {
    if (this->title_parser_)
    {
      this->title_parser_->pre ();
      this->title_parser_->_pre_impl ();
      this->title_parser_->_characters (s);
      this->title_parser_->_post_impl ();
      this->title (this->title_parser_->post_title_type ());
    }

    static_cast< v_state_attr_* > (this->v_state_attr_stack_.top ())->title = true;
    return true;
  }

  return false;
}

void state_pskel::
_pre_a_validate ()
{
  this->v_state_attr_stack_.push ();
  v_state_attr_& as = *static_cast< v_state_attr_* > (this->v_state_attr_stack_.top ());

  as.id = false;
  as.title = false;
}

void state_pskel::
_post_a_validate ()
{
  v_state_attr_& as = *static_cast< v_state_attr_* > (this->v_state_attr_stack_.top ());

  if (!as.id)
    this->_expected_attribute (
      "", "id");
  if (!as.title)
    this->_expected_attribute (
      "", "title");

  this->v_state_attr_stack_.pop ();
}

#include <xsd/cxx/post.hxx>

// Begin epilogue.
//
//
// End epilogue.

