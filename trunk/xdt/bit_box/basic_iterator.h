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
*/
template <class chest_t>
class basic_iterator
{
public:
	// friends -----------------------------------------------------------------

	//!	\brief Friend <i>%basic_chest</i> with all kind of template parameters
	/*!	We need this, to have access to private and protected members of
		<i>%basic_chest</i> classes with different template parameters. This is
		very important for converting constructor and converting assigment
		operator.
	*/
	template <class chest_t>
	friend class basic_iterator;

	// public types ------------------------------------------------------------

	//!	\brief Alias for template parameter <i>chest_t</i>
	/*!	
	*/
	typedef chest_t chest_type;

	typedef basic_iterator<chest_type> self_type;

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

	//! \brief Copy constructor
	/*!
	*/
	basic_iterator(const self_type &from):
		_chest(from._chest)
	{
	}

	//! \brief Convert constructor
	/*!
	*/
	template <class chest_from_t>
	basic_iterator(const basic_iterator<chest_from_t> &from):
		_chest(from._chest)
	{
	}

	//!	\brief Destructor
	/*!	\todo Do we really need it? May be it must be virtual?
	*/
	virtual ~basic_iterator()
	{
	}

	//@}

	//!	\name Equality operators
	//@{

	//!	\brief Equality
	/*!
	*/
	template <class chest_b_t>
	bool operator == (const basic_iterator<chest_b_t> &b) const
	{
		return (_chest.is_same_as(b._chest));
	}

	//!	\brief Inequality
	/*!
	*/
	template <class chest_b_t>
	bool operator != (const basic_iterator<chest_b_t> &b) const
	{
		return (!_chest.is_same_as(b._chest));
	}

	//@}

	//!	\name Dereference and member selection operators
	//@{

	chest_type *operator -> ()
	{
		return (&_chest);
	}

	const chest_type *operator -> () const
	{
		return (&_chest);
	}

	chest_type &operator * ()
	{
		return _chest;
	}

	const chest_type &operator * () const
	{
		return _chest;
	}

	//@}

	//!	\name Assigment operators
	//@{

	template <class chest_from_t>
	self_type &operator = (const basic_iterator<chest_from_t> &from)
	{
		_chest = from._chest;

		return (*this);
	}

	//@}

	//!	\name Increment operators
	//@{

	//!	\brief Prefix increment operator
	/*!
	*/
	self_type &operator++()
	{
	}

	//!	\brief Postfix increment operator
	self_type operator++(int)
	{
	}

	//@}

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
