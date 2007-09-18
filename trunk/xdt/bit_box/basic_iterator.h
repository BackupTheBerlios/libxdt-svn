/*!	\file		basic_iterator.h
	\version	0.0.1
	\author		mice, ICQ: 332-292-380, mailto:wonder.mice@gmail.com
	\brief		Declarations and difinitions for xdt::bit_box::basic_iterator
				template class

	\sa xdt::bit_box::basic_iterator, xdt::bit_box

	\todo		Add detailed comment for basic_iterator.h file
*/

#pragma once

#ifndef XDT_BIT_BOX_BASIC_ITERATOR_INCLUDED
#define XDT_BIT_BOX_BASIC_ITERATOR_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// headers

// debug headers
#include <assert.h>

// xdt atomic types headers
#include <xdt/base/types.h>

// standart C++ library headers
// none

// external libraries headers
// none

// OS specific headers
// none

// xdt headers
// none


////////////////////////////////////////////////////////////////////////////////
// xdt namespace
namespace xdt
{


////////////////////////////////////////////////////////////////////////////////
// bit_box namespace
namespace bit_box
{


////////////////////////////////////////////////////////////////////////////////
// basic_iterator class declaration
//! \brief 
/*!
	i = ch.begin();
	(*i) = other;
*/
template <class chest_t>
class basic_iterator
{
public:
	// public types ------------------------------------------------------------

	//!	\brief Alias for template parameter <i>chest_t</i>
	/*!	
	*/
	typedef chest_t chest_type;

	// public constants --------------------------------------------------------

	// public methods ----------------------------------------------------------

	//!	\name Constructors and destructors
	//@{
	
	//! \brief Default constructor
	/*!
	*/
	basic_iterator()
	{
	}

	//!	\brief Destructor
	/*!	\todo Do we really need it? May be it must be virtual?
	*/
	virtual ~basic_iterator()
	{
	}

	//@}

	operator > ();
	operator < ();
	operator <= ();
	operator >= ();
	operator != ();
	operator == ();
	operator -> ();
	operator * ();

protected:
	// protected types ---------------------------------------------------------

	// protected methods -------------------------------------------------------

private:
	// private data ------------------------------------------------------------

	//!	\brief 
	chest_type _chest;

};



}	// bit_box namespace



}	// xdt namespace



#endif	// XDT_BIT_BOX_BASIC_ITERATOR_INCLUDED
