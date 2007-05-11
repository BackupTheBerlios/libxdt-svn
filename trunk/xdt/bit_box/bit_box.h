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
// none

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
//! \brief Elementary bit_box container that can read and iterate throw
//!	bit_box data.
/*!	
*/
template <class data_type>
class bit_box: public basic_bit_box<data_type>
{
public:
	// public types ------------------------------------------------------------

	//!	\brief 
	/*!	
	*/
	class iterator: public basic_bit_box<data_type>
	{
	public:
		// public methods ------------------------------------------------------

		//! \brief Constructor
		/*!	
		*/
		iterator(data_type *const bits): basic_bit_box<data_type>(bits)
		{
		}

		template <class t>
		iterator(typename const bit_box<t>::iterator &i):
			basic_bit_box<data_type>(i)
		{
		}

		bool operator ==(const iterator &b) {
			return (b.bits() == b.bits());
		}
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
