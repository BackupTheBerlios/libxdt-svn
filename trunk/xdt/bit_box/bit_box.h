/*******************************************************************************
* file:         bit_box.h                                                      *
* version:      0.0.1                                                          *
* author:       mice, ICQ: 332-292-380, mailto:wonder.mice@gmail.com           *
* description:  base types declarations                                        *
* tests:        ok                                                             *
*******************************************************************************/

#pragma once

#ifndef XDT_BIT_BOX_BIT_BOX_INCLUDED
#define XDT_BIT_BOX_BIT_BOX_INCLUDED


/*!	\file
	\brief bit_box is a set of classes, which can store binary data of any
	type in solid plain byte array. With it it's very easy to save any
	number of raw (or not raw) binary data and then restore it.

	bit_box suit was originally designed to send sets of mixed binary data
	through a pipe-like (or socket-like) channel. It may be helpful, when
	organizing some message driven communications.

	bit_box actually is an STL compatible container. But not at all. It has two
	types of containers:
	- xdt::bit_box::reader with only read acces
	- xdt::bit_box::composer with both read and write access
*/


////////////////////////////////////////////////////////////////////////////////
// headers

// code configuration headers
// none

// standart C++ library headers
// none

// external libraries headers
// none

// OS specific headers
// none

// xdt headers
#include <xdt/base/types.h>


////////////////////////////////////////////////////////////////////////////////
// xdt namespace
namespace xdt {


////////////////////////////////////////////////////////////////////////////////
// bit_box namespace
namespace bit_box {


////////////////////////////////////////////////////////////////////////////////
// basic_bit_box class declaration
//! \brief Simplest unit of bit_box data. Small part of all big block.
/*!	It's base class for all bit_box.

	It knows:
	- where it's d
*/
class basic_bit_box {
public:
	// public types ------------------------------------------------------------

	//! \brief Type to store size of bit_box data, or something like this
	typedef unsigned int sz_t;

	//! \brief
	typedef byte_t bit_box_data_t;
	typedef unsigned int type_t;

	//! \brief Item header of each bit_box data
	#pragma pack(push, 4)
	struct item_t {
		sz_t sz;
		type_t type;
	};
	#pragma pack(pop)

	// public constants --------------------------------------------------------

	//! \brief Predefined types for bit_box data
	enum bb_types {
		bbt_bit_box,	//!< \brief Data is another bit_box
		bbt_binary,		//!< \brief Data is byte array
		bbt_int32,		//!< \brief Data is 32 bit signed integer
		bbt_uint32,		//!< \brief Data is 32 bit unsigned integer
		bbt_double,		//!< \brief Data is 64 bit floating point value
		bbt_string,		//!< \brief Data is null-terminated ASCII string
		bbt_wstring,	//!< \brief Data is null-terminated UTF-16 string
		bbt_user = 0xFFF	//! \brief This and greater for user defined types
	};

	// public methods ----------------------------------------------------------

	//! \brief Constructor

protected:
	// protected methods -------------------------------------------------------

	//! \brief 
	void _set(const byte_t *const bits) {
	}

	//! \brief Constructor
	void _set(const byte_t *const bits, const sz_t sz) {
		_bits	= bits;
		_sz		= sz;
	}

private:
	const byte_t *_bits;
	sz_t _sz;
};


//! \brief Class that can iterate over bit_box data
class reader: public basic_bit_box {
public:
	// public types ------------------------------------------------------------

	//! \brief Constant iterator over bit_box data
	class const_iterator {
	};

	// public methods ----------------------------------------------------------

	//! \brief Copy constructor
	/*!	Copy constructor of reader class does not copies any memory, just bits
		pointer and size value.
	*/
	reader(const reader &r);

	//! \brief Constructor
	/*!	Takes bits like it is bit_box item, so size can be taken from bit_box
		item header. Type in header must be basic_bit_box::bbt_bit_box. Class
		remembers just size and pointer to data itself, not on entire item.
	*/
	reader(const byte_t *const bits);

	//! \brief Constructor
	/*! 
	*/
	reader(const byte_t *const bits, const sz_t sz);

protected:
private:

};


class composer {
};



}	// bit_box namespace



}	// xdt namespace



#endif	// XDT_BIT_BOX_BIT_BOX_INCLUDED
