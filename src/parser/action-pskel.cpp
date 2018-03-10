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

#include "action-pskel.hpp"

#include "transition-pskel.hpp"

#include "id_type-pskel.hpp"

#include "title_type-pskel.hpp"

#include "state_pointer_type-pskel.hpp"

// action_pskel
//

void action_pskel::
transition_parser (::transition_pskel& p)
{
  this->transition_parser_ = &p;
}

void action_pskel::
id_parser (::id_type_pskel& p)
{
  this->id_parser_ = &p;
}

void action_pskel::
title_parser (::title_type_pskel& p)
{
  this->title_parser_ = &p;
}

void action_pskel::
from_parser (::state_pointer_type_pskel& p)
{
  this->from_parser_ = &p;
}

void action_pskel::
parsers (::transition_pskel& transition,
         ::id_type_pskel& id,
         ::title_type_pskel& title,
         ::state_pointer_type_pskel& from)
{
  this->transition_parser_ = &transition;
  this->id_parser_ = &id;
  this->title_parser_ = &title;
  this->from_parser_ = &from;
}

action_pskel::
action_pskel ()
: transition_parser_ (0),
  id_parser_ (0),
  title_parser_ (0),
  from_parser_ (0),
  v_state_stack_ (sizeof (v_state_), &v_state_first_),
  v_state_attr_stack_ (sizeof (v_state_attr_), &v_state_attr_first_)
{
}

// action_pskel
//

void action_pskel::
transition (marl::transition*)
{
}

void action_pskel::
id (uint32_t)
{
}

void action_pskel::
title (::std::string)
{
}

void action_pskel::
from (::marl::state*)
{
}

#include <cassert>

// Element validation and dispatch functions for action_pskel.
//
bool action_pskel::
_start_element_impl (const ::xml_schema::ro_string& ns,
                     const ::xml_schema::ro_string& n,
                     const ::xml_schema::ro_string* t)
{
  XSD_UNUSED (t);

  v_state_& vs = *static_cast< v_state_* > (this->v_state_stack_.top ());
  v_state_descr_* vd = vs.data + (vs.size - 1);

  if (vd->func == 0 && vd->state == 0)
  {
    if (this->::xml_schema::complex_content::_start_element_impl (ns, n, t))
      return true;
    else
      vd->state = 1;
  }

  while (vd->func != 0)
  {
    (this->*vd->func) (vd->state, vd->count, ns, n, t, true);

    vd = vs.data + (vs.size - 1);

    if (vd->state == ~0UL)
      vd = vs.data + (--vs.size - 1);
    else
      break;
  }

  if (vd->func == 0)
  {
    if (vd->state != ~0UL)
    {
      unsigned long s = ~0UL;

      if (n == "transition" && ns.empty ())
        s = 0UL;

      if (s != ~0UL)
      {
        vd->count++;
        vd->state = ~0UL;

        vd = vs.data + vs.size++;
        vd->func = &action_pskel::sequence_0;
        vd->state = s;
        vd->count = 0;

        this->sequence_0 (vd->state, vd->count, ns, n, t, true);
      }
      else
      {
        if (vd->count < 1UL)
          this->_expected_element (
            "", "transition",
            ns, n);
        return false;
      }
    }
    else
      return false;
  }

  return true;
}

bool action_pskel::
_end_element_impl (const ::xml_schema::ro_string& ns,
                   const ::xml_schema::ro_string& n)
{
  v_state_& vs = *static_cast< v_state_* > (this->v_state_stack_.top ());
  v_state_descr_& vd = vs.data[vs.size - 1];

  if (vd.func == 0 && vd.state == 0)
  {
    if (!::xml_schema::complex_content::_end_element_impl (ns, n))
      assert (false);
    return true;
  }

  assert (vd.func != 0);
  (this->*vd.func) (vd.state, vd.count, ns, n, 0, false);

  if (vd.state == ~0UL)
    vs.size--;

  return true;
}

void action_pskel::
_pre_e_validate ()
{
  this->v_state_stack_.push ();
  static_cast< v_state_* > (this->v_state_stack_.top ())->size = 0;

  v_state_& vs = *static_cast< v_state_* > (this->v_state_stack_.top ());
  v_state_descr_& vd = vs.data[vs.size++];

  vd.func = 0;
  vd.state = 0;
  vd.count = 0;
}

void action_pskel::
_post_e_validate ()
{
  v_state_& vs = *static_cast< v_state_* > (this->v_state_stack_.top ());
  v_state_descr_* vd = vs.data + (vs.size - 1);

  ::xml_schema::ro_string empty;
  while (vd->func != 0)
  {
    (this->*vd->func) (vd->state, vd->count, empty, empty, 0, true);
    assert (vd->state == ~0UL);
    vd = vs.data + (--vs.size - 1);
  }

  if (vd->count < 1UL)
    this->_expected_element (
      "", "transition");

  this->v_state_stack_.pop ();
}

void action_pskel::
sequence_0 (unsigned long& state,
            unsigned long& count,
            const ::xml_schema::ro_string& ns,
            const ::xml_schema::ro_string& n,
            const ::xml_schema::ro_string* t,
            bool start)
{
  XSD_UNUSED (t);

  switch (state)
  {
    case 0UL:
    {
      if (n == "transition" && ns.empty ())
      {
        if (start)
        {
          this->::xml_schema::complex_content::context_.top ().parser_ = this->transition_parser_;

          if (this->transition_parser_)
            this->transition_parser_->pre ();
        }
        else
        {
          if (this->transition_parser_)
          {
            this->transition (this->transition_parser_->post_transition ());
          }

          count++;
        }

        break;
      }
      else
      {
        assert (start);
        if (count < 1UL)
          this->_expected_element (
            "", "transition",
            ns, n);
        count = 0;
        state = ~0UL;
        // Fall through.
      }
    }
    case ~0UL:
      break;
  }
}

// Attribute validation and dispatch functions for action_pskel.
//
bool action_pskel::
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

  if (n == "from" && ns.empty ())
  {
    if (this->from_parser_)
    {
      this->from_parser_->pre ();
      this->from_parser_->_pre_impl ();
      this->from_parser_->_characters (s);
      this->from_parser_->_post_impl ();
      this->from (this->from_parser_->post_state_pointer_type ());
    }

    static_cast< v_state_attr_* > (this->v_state_attr_stack_.top ())->from = true;
    return true;
  }

  return false;
}

void action_pskel::
_pre_a_validate ()
{
  this->v_state_attr_stack_.push ();
  v_state_attr_& as = *static_cast< v_state_attr_* > (this->v_state_attr_stack_.top ());

  as.id = false;
  as.title = false;
  as.from = false;
}

void action_pskel::
_post_a_validate ()
{
  v_state_attr_& as = *static_cast< v_state_attr_* > (this->v_state_attr_stack_.top ());

  if (!as.id)
    this->_expected_attribute (
      "", "id");
  if (!as.title)
    this->_expected_attribute (
      "", "title");
  if (!as.from)
    this->_expected_attribute (
      "", "from");

  this->v_state_attr_stack_.pop ();
}

#include <xsd/cxx/post.hxx>

// Begin epilogue.
//
//
// End epilogue.
