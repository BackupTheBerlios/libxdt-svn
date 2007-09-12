/*!	\file     bit_box.h
	\version  0.0.1
	\author   mice, ICQ: 332-292-380, mailto:wonder.mice@gmail.com
	\brief    Declarations and difinitions of xdt::bit_box::bit_box class

	\todo     Add detailed comment for bit_box.h file
*/

#pragma once

#ifndef XDT_BIT_BOX_BIT_BOX_INCLUDED
#define XDT_BIT_BOX_BIT_BOX_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// headers

// code configuration headers
#include <assert.h>

// standart C++ library headers
#include <iterator>

// external libraries headers
// none

// OS specific headers
// none

// xdt headers
#include <xdt/bit_box/basic_bit_box.h>


////////////////////////////////////////////////////////////////////////////////
// xdt namespace
namespace xdt
{


////////////////////////////////////////////////////////////////////////////////
// bit_box namespace
namespace bit_box
{


////////////////////////////////////////////////////////////////////////////////
// bit_box class declaration
//! \brief Elementary bit_box container that can read and iterate through
//!	bit_box data.
/*!

	\code
	xdt::bit_box::writer writer;
	writer.put(data_ptr, size, type);
	xdt::bit_box::writer writer(size);
	xdt::bit_box::writer writer(ptr, size);
	\endcode
*/
template <class data_type>
class bit_box: public basic_bit_box<data_type>
{
public:
	// public types ------------------------------------------------------------

	//!	\brief Iterator over bit_box data blocks
	/*!	
	*/
	class iterator
	{
	public:
		// public types --------------------------------------------------------

		//! \brief Type of iterator category
		/*!	bit_box in its base variant can iterate only forward.
		*/
		typedef std::forward_iterator_tag iterator_category;

		typedef basic_bit_box<data_type> value_type

		// public methods ------------------------------------------------------

		//! \brief Constructor
		/*!	
		*/
		iterator(data_type *const bits): basic_bit_box<data_type>(bits)
		{
		}

		//!	\brief Copy constructor
		/*!
		*/
		template <class t>
		iterator(const basic_bit_box<t> &i): basic_bit_box<data_type>(i)
		{
		}

		basic_bit_box<data_type> *operator->() { return this; }

		basic_bit_box<data_type> &operator *() { return (*this); }

		//! \brief 
		bool operator ==(const iterator &b) {
			return (b.bits() == b.bits());
		}
	private:
		// private data --------------------------------------------------------

		//!	\brief Internal bit_box data
		/*!	This bit_box is a current value of iterator
		*/
		basic_bit_box<data_type> _bb;

	};

	// public methods ----------------------------------------------------------

	//!	\brief Constructor
	/*!	\param[in] bits Pointer on bit_box data with header
	*/
	bit_box(byte_t *const bits): basic_bit_box<data_type>(bits)
	{
	}

	iterator begin() const
	{
		return iterator(bits());

	}

	iterator end() const;

protected:

	// protected methods -------------------------------------------------------

private:
	// private data ------------------------------------------------------------

};

template <class data_type>
class composer: public bit_box<data_type>
{
};

typedef bit_box<const byte_t> reader;
typedef composer<const byte_t> writer;



}	// bit_box namespace



}	// xdt namespace



#endif	// XDT_BIT_BOX_BIT_BOX_INCLUDED
