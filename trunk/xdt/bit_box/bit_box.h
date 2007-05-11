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
//! \brief
/*!	
*/
template <class data_type>
class bit_box: public basic_bit_box<data_type>
{
public:
	// public types ------------------------------------------------------------
	class const_iterator: public basic_bit_box
	{
	public:
		bool operator ==(const_iterator &i2);
	};

	// public methods ----------------------------------------------------------

	//!	\brief Constructor
	/*!	\param[in] bits Pointer on bit_box data with header
	*/
	bit_box(const byte_t *const bits): basic_bit_box(bits)
	{
	}

	const_iterator begin() const;
	const_iterator end() const;

protected:
	// protected types ---------------------------------------------------------
	class _basic_iterator: public basic_bit_box
	{
		bool operator ==(const_iterator &i2);
	};

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
