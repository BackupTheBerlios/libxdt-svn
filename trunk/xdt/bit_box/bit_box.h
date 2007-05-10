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
//!	\brief namespace for bit_box suit
/*! \todo detailed bit_box description
*/
namespace bit_box {


////////////////////////////////////////////////////////////////////////////////
// basic_bit_box class declaration
//! \brief Simplest unit of bit_box data. Also base class for all bit_box.
/*!	It knows:
	- Where its data is. Every basic_bit_box has pointer on its data.
	- Size of this data.
	- Type of this data.

	Some words about types. bit_box works with raw bytes, it has no idea with
	what really data it operates. bit_box type is just a number, only 0 is
	reserved to represent another (nested) bit_box. It's up to class user
	to decide, what type some data has. Also, bit_box has some predefined
	types, and it's good idea for user types not to overlap with them.

	basic_bit_box defines some types, to unify it's usage:
	- basic_bit_box::sz_t to represent some size or length
	- basic_bit_box::type_t for type identifiers

	It also uses xdt::byte_t to represent pointers on byte arrays.
*/
class basic_bit_box {
public:
	// public types ------------------------------------------------------------

	//! \brief Type to store size of bit_box data, or something like this
	typedef unsigned int sz_t;

	//! \brief Type for type identifiers.
	typedef unsigned int type_t;

	// public constants --------------------------------------------------------

	//! \brief Predefined types for bit_box data
	/*!	Only 0 is strictly reserved - it represents data type of bit_box. All
		other identifiers are free to use. But it's a good idea not to use
		those predefined values, because they are very common and can be
		used by some bit_box wrappers (for example, STL like stream wrapper).
	*/
	enum bb_types {
		bbt_bit_box	= 0,	//!< \brief Data is another (nested) bit_box
		bbt_index	= 1		//!< \brief bit_box data index (not used now)
		bbt_binary	= 2,	//!< \brief Data is byte array
		bbt_int32	= 3,	//!< \brief Data is 32 bit signed integer
		bbt_uint32	= 4,	//!< \brief Data is 32 bit unsigned integer
		bbt_double	= 5,	//!< \brief Data is 64 bit floating point value
		bbt_string	= 6,	//!< \brief Data is null-terminated ASCII string
		bbt_wstring	= 7,	//!< \brief Data is null-terminated UTF-16 string
		bbt_user	= 0xFFF	//!< \brief This and greater for user defined types
	};

	// public methods ----------------------------------------------------------
	
	//! \brief Constructor
	/*!	
	*/
	void basic_bit_box(const byte_t *const bits) {
		_set(bits);
	}

	//! \brief Constructor
	/*!	
	*/
	void basic_bit_box(const byte_t *const bits, const sz_t sz) {
		_set(bits, sz);
	}

	//! \brief Copy constructor
	/*!	
	*/
	void basic_bit_box(const basic_bit_box &bbb):
		_bits(bbb._bits), _sz(bbb._sz), _type(bbb._type)
	{
	}

	//!	\brief Returns type of bit_box data
	/*! \return Type of bit_box data as type identifier
	*/
	type_t type() const { return _type; }

	//!	\brief Returns size of bit_box data
	/*! \return Size of bit_box data in bytes (8 bits)
	*/
	sz_t sz() const { return _sz; }

	//!	\brief Returns pointer on bit_box data
	/*!	\return Pointer on bit_box data
	*/
	byte_t *bits() const { return _bits; }

protected:
	// protected types ---------------------------------------------------------

	//! \brief bit_box data header
	/*!	Header has size and type of bit_box data. It's for bit_box internal
		usage only.
	*/
	#pragma pack(push, 4)
	struct _header_t {
		sz_t sz;		//!< \brief Size of bit_box data
		type_t type;	//!< \brief Type of bit_box data
	};
	#pragma pack(pop)

	// protected methods -------------------------------------------------------

	//! \brief 
	/*!	
	*/
	void _set(const byte_t *const bits) {
		const _header_t *const header = (_header_t *)bits;

		_set(bits + sizeof(_header_t),
			 header->sz,
			 header->type
		);
	}

	//! \brief
	/*!	
	*/
	void _set(const byte_t *const bits, const sz_t sz,
			  const type_t type = bbt_bit_box)
	{
		_bits	= bits;
		_sz		= sz;
		_type	= type;
	}

private:
	// private data ------------------------------------------------------------

	//! \brief Pointer on bit_box data
	/*!	It is a pointer on raw data, without any headers or something else.
	*/
	const byte_t *_bits;

	//! \brief Size of data pointed by basic_bit_box::_bits
	sz_t _sz;

	//!	\brief Type identifier of pointed data
	type_t _type;


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
