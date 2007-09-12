/*!	\file		basic_chest.h
	\version	0.0.1
	\author		mice, ICQ: 332-292-380, mailto:wonder.mice@gmail.com
	\brief		Declarations and difinitions for xdt::bit_box::basic_chest
				template class

	\sa xdt::bit_box, xdt::bit_box::basic_chest

	\todo		Add detailed comment for basic_chest.h file
*/

#pragma once

#ifndef XDT_BIT_BOX_BASIC_CHEST_INCLUDED
#define XDT_BIT_BOX_BASIC_CHEST_INCLUDED

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
//!	\brief namespace for <i>%bit_box</i> suit
/*! <i>%bit_box</i> is a set of classes, which can store binary data of any
	type in solid plain byte array. With it it's very easy to save any
	number of raw (or not raw) binary data and then restore it.

	<i>%bit_box</i> suit was originally designed to send sets of mixed binary
	data through a pipe-like (or socket-like) channel. It may be helpful, when
	organizing some message or event driven communications.

	<i>%bit_box</i> is much like an STL compatible container. But not at all.

	\todo Need more comments on bit_box namespace
*/
namespace bit_box
{


////////////////////////////////////////////////////////////////////////////////
// basic_chest class declaration
//! \brief Simplest unit of <i>%bit_box</i> data. Also base class for almost
//!	all <i>%bit_box</i> suit. Handles the most simple "physical level" work.
/*!	<b>%basic_chest</b> is called basic because it is really basic :^) But
	it is powerful enough to be a base class for almost all <i>%bit_box</i>
	suit. Any <i>%basic_chest</i> attached to memory partition, called
	<i>solid block</i>. Solid block has two parts: header information and
	stored data (called <i>bits</i>). From header information
	<i>%basic_chest</i> knows size and type identifier of its data.

	Some words about magic type identifiers. <i>%basic_chest</i> works
	with raw bytes, it has no idea with what really data it operates. And this
	is good. So, <i>%bit_box</i> data type identifier is just a number.
	It's up to class user to decide, what type some data has. Only 0 (zero) is
	reserved to represent another (nested) <i>%basic_chest</i>. Also,
	<i>%basic_chest</i> has some predefined type identifiers, and it's good
	idea for custom types not to overlap with them (basic_chest::bb_types).

	To unify its usage <i>%basic_chest</i> defines some types, in STL
	compatible manner:
	- basic_bit_box::size_type to represent some size or length. Note, that
	  in terms of <i>%bit_box</i> <i>size</i> is size in bytes of associated
	  data. So, we will call it <i>sz</i> to prevent confusion with STL
	  containers <i>size</i> wich is count of elements.
	- basic_bit_box::bits_type to represent type of pointers, used by
	  <i>%basic_bit_box</i>. Note, that actual pointers type will be
	  (<i>%basic_bit_box::bits_type *</i>). Star (<i>*</i>) added
	  automatically to guarantee that pointers are really of some pointer type.
	- basic_bit_box::type_id_type for type identifiers. Just unsigned integer.

	<i>%basic_chest</i> has one important feature - it knows internals of
	<i>%bit_box</i> data format. So, it is possible to extract data type
	identifier, data size and data itself from solid data block. Note, that
	<i>%basic_chest</i> uses special types for values, stored in its
	header(like xdt::uint32_t, for example). So you can easily transfer
	<i>%bit_box</i> data from one system to another - everything will be okay.

	Class has no error checking built-in (we want to make it as fast as
	possible), so if you get data from noisy and lossy channel - use something
	like CRC to prevent destructive consequences. You are responsible to give
	pointers on valid memory blocks with valid <i>%basic_chest</i> headers.

	\note The only reason, that <i>%basic_chest</i> is a template class,
	is to allow both constant and non-constant data pointers. Try not to use
	this feature in other ways (however, it correctly handles any type of
	template parameters). Here small example of what like template parameter
	should be:
	\code
	xdt::bit_box::basic_chest<xdt::byte_t>		 bb1(0);
	xdt::bit_box::basic_chest<const xdt::byte_t> bb2(0);
	\endcode

	<i>%basic_chest</i> is not very useful by itself. However here is a small
	example to simplify understanding of this class:
	\code
	//TODO: some example
	xdt::bit_box::basic_bit_box<char> bb(0);
	\endcode
	
	Few words about template parameters. <i>solid_t</i> serves to build
	pointer type <i>(solid_t *)</i> that will represent pointers on solid
	block. <i>bits_t</i> serves to build <i>(bits_t *)</i> pointer type that
	will represent pointers on data, stored in <i>%basic_chest</i>.

	\todo basic_chest needs some example code
*/
template <class solid_t, class bits_t>
class basic_chest
{
public:
	// public types ------------------------------------------------------------

	//!	\brief Alias for template parameter <i>solid_t</i>
	/*!	
	*/
	typedef solid_t solid_type;

	//! \brief Alias for template parameter <i>bits_t</i>
	/*!	Represents type, on wich <i>%basic_chest</i> pointers will point.
		It's not a real pointer type, because you always can add star
		(<i>*</i>) to any type and get pointer type. But it is difficult
		to remove star from type (to dereference a type) without any tricks.
	*/
	typedef bits_t bits_type;

	//! \brief Type to store size of stored <i>%basic_chest</i> data, or
	//!	something like this.
	/*!	\note We can't use cool <i>STL</i> <i>size_t</i>, because we
		need some cross-platform type.
	*/
	typedef uint32_t bits_sz_type;

	//! \brief Type for type identifiers. Just unsigned integer.
	typedef uint32_t type_id_type;
	
	typedef size_t

	//!	\brief Type of this <i>%basic_bit_box</i>
	/*!	It's very useful to have such type. With it there is no need to type
		full class name with template parameters everytime.
	*/
	typedef basic_chest<solid_type, bits_type> self_type;

	// public constants --------------------------------------------------------

	//! \brief Predefined type identifiers for <i>%bit_box</i> data
	/*!	Only 0 is strictly reserved - it represents data type of another
		(nested) <i>%bit_box</i>. All other identifiers are free to use. But
		it's a good idea not to use this predefined values, because they are
		very common and can be used by some <i>%bit_box</i> wrapper (for
		example, STL like stream wrapper).
	*/
	enum bb_types
	{
		bbt_bit_box	= 0,	//!< \brief Data is another (nested) bit_box
		bbt_index	= 1,	//!< \brief bit_box data index (not used now)
		bbt_binary	= 2,	//!< \brief Data is byte array
		bbt_sint32	= 3,	//!< \brief Data is 32 bit signed integer
		bbt_uint32	= 4,	//!< \brief Data is 32 bit unsigned integer
		bbt_double	= 5,	//!< \brief Data is 64 bit floating point value
		bbt_string	= 6,	//!< \brief Data is null-terminated ASCII string
		bbt_wstring	= 7,	//!< \brief Data is null-terminated UTF-16 string
		bbt_user	= 0xFFF	//!< \brief This and greater for user defined types
	};

	// public methods ----------------------------------------------------------

	//!	\name Constructors and destructors
	//@{
	
	//! \brief Constructor
	/*!	\param[in] bits Pointer on <i>%bit_box</i> data with header information

		This constructor extracts from <i>%bit_box</i> header type idenifier and
		size of contained (stored) data.

		\attention It's very important, that <b>real</b> header must precedes
		<i>%bit_box</i> stored data.
	*/
	basic_chest(solid_type *const solid_ptr)
	{
		_set(solid_ptr);
	}

	//! \brief Constructor
	/*!	\param[in] bits Pointer on raw bit_box data
		\param[in] sz Size of bit_box data (raw data, without any headers)
		pointed by <i>bits</i>

		This constructor sets type identifier to
		<i>basic_bit_box::bbt_bit_box</i> so use it only with data that
		is another bit_box.
	*/
	basic_chest(solid_type *const solid_ptr, const bits_sz_type &bits_sz,
				const type_id_type &type_id)
	{
		_set(solid_ptr, sz, bbt_bit_box);
	}

	//! \brief Copy constructor
	/*!	\param[in] src Source <i>basic_bit_box</i> to copy from. Nothing
		tricky, just copy as is.

		\attention This copy constructor copies only pointers, not their data.
		basic_bit_box does no any memory allocation in every its part.
		Remember it :^)

		\attention You can't assign <i>basic_bit_box</i> with
		<i>bits_type</i>, for example, <i>const xdt::byte_t</i> to
		<i>basic_bit_box</i> with <i>bits_type</i> <i>xdt::byte_t</i>. In
		first case we have pointer on constant data. In second - pointer on
		volatile data. So, if you will get a compilation error here - check
		your code once again on such mistakes.
	*/
	template <class t>
	basic_bit_box(const basic_bit_box<t> &src):
		_bits(reinterpret_cast<t *>(src.bits())),
		_sz(src.sz()), _type_id(src.type_id())
	{
	}

	//!	\brief Destructor
	/*!	\todo Do we really need it?
	*/
	virtual ~basic_bit_box()
	{
	}

	//@}


	//!	\name Data access functions
	//@{

	//!	\brief Returns pointer on bit_box data
	/*!	\return Pointer on bit_box data
	*/
	bits_type *bits() const { return _bits; }

	//!	\brief Returns size of bit_box data
	/*! \return Size of bit_box data in bytes (8 bits)
	*/
	size_type sz() const { return _sz; }

	//!	\brief Returns type of bit_box data
	/*! \return Type of bit_box data as type identifier
	*/
	type_id_type type_id() const { return _type_id; }

	//@}

protected:
	// protected types ---------------------------------------------------------

	//! \brief Transplants <i>const</i> modifier from one type to another.
	//!	Baseline declaration for non-constant types.
	/*!	This helper class is useful when you need to transplant
		<i>const modifier</i> from one type to another. It means, that second
		type (destination) will have <i>const</i> modifier only if first
		(source) has it. For example:
		\code
		// this type will NOT have <i>const</i> modifier
		typedef _const_transplant<char, int>::t non_const_int;
		// this type will have <i>const</i> modifier
		typedef _const_transplant<const char, int>::t const_int;
		\endcode

		\todo Possibly, it's a good idea to place all classes like this
		in separate sub-library. For example, in
		<tt>xdt/tricks/const_transplantator.h</tt>.
	*/
	template <class src_t, class dest_t>
	struct _const_transplant
	{
		//! \brief Resulting type
		typedef dest_t t;
	};

	//! \brief Transplants <i>const</i> modifier from one type to another.
	//!	Specialization for constant types.
	/*!	\sa _const_transplant
	*/
	template <class src_t, class dest_t>
	struct _const_transplant<const src_t, dest_t>
	{
		//! \brief Resulting type
		typedef const dest_t t;
	};

	//! \brief Header that precedes actual data and hold size and type
	//!	information
	/*!	<i>%basic_chest</i> incapsulates all functionality, required for
		working with solid blocks. Therefor this header for bit_box
		internal usage only.
	*/
	#pragma pack(push, 1)
	struct _header_t
	{
		//!	\brief Size of stored data in bytes
		bits_sz_type bits_sz;
		//!	\brief Type identifier of stored data
		type_id_type type_id;
	};
	#pragma pack(pop)

	//! \brief Alias for header type with proper <i>const</i> modifier
	/*!	I think it's not a good idea to widely use this type. It's part of
		header information and it's good to keep it protected as long as
		possible.
	*/
	typedef typename _const_transplant<solid_type, _header_t>::t _header_type;

	// protected methods -------------------------------------------------------

	//! \brief Extracts data information from header and sets it
	/*!	\param[in] bits Pointer on bit_box data with header information

		This function knows about headers. It will be pretty cool, if it will
		stay the only function, that knows about them.

		\attention Function extracts size and type of bit_box data using header
		information. Try to make your best not to fool it by passing invalid
		pointer - consequences will be unpredictable :^)
	*/
	void _set(bits_type *const bits)
	{
		assert(0 != bits);

		_header_type *header = (_header_type *)bits;

		_set(reinterpret_cast<bits_type *>(header + 1),
			 header->sz, header->type_id);
	}

	//! \brief Sets internal data information
	/*!	\param[in] bits Pointer on bit_box data. Raw real data, without any
		headers.
		\param[in] sz Size of data in bytes
		\param[in] type_id Type of data. Any identifier or one of predefined in
		basic_bit_box::bb_types.

		This function is the only direct way to set internal data
		information. It does no any error checks.
	*/
	void _set(bits_type *const bits, const size_type sz,
			  const type_id_type type_id = bbt_bit_box)
	{
		assert(0 != bits);

		_bits		= bits;
		_sz			= sz;
		_type_id	= type_id;
	}

	//!	\brief Loading
	/*!	\param[in] solid_ptr 
	*/
	void _set(solid_t *const solid_ptr)
	{
		assert(0 != solid_ptr);

		_header	= (_header_type *)solid_ptr;
		
		_bits = reinterpret_cast<bits_type *>(_header + 1);
	}

	//!	\brief 
	/*!	\param[in,out] solid_ptr
		\param[in] bits_sz
		\param[in] type_id
	*/
	void _set(solid_t *const solid_ptr, const bits_sz_type &bits_sz,
			  const type_id_type &type_id)
	{
		_set(solid_ptr);

		assert(0 != _header);

		_header->bits_sz = bits_sz;
		_header->type_id = type_id;
	}

	//!	\brief
	/*!
	*/
	void _set_type_id(const type_id_type &type_id)
	{
		assert(0 != _header);
		
		_header->type_id = type_id;
	}

private:
	// private data ------------------------------------------------------------

	//!	\brief Pointer on header that precedes stored data
	_header_type *_header;

	//! \brief Pointer on stored data
	/*!	It is a pointer on raw data, without any headers or something else.
	*/
	bits_type *_bits;

};



}	// bit_box namespace



}	// xdt namespace



#endif	// XDT_BIT_BOX_BASIC_CHEST_INCLUDED





//!	\brief Only physical level!!!
/*!
*/
template <class solid_t, class bits_t>
class basic_chest
{
public:
	// public types ------------------------------------------------------------

	typedef solid_t solid_type;
	typedef solid_t *solid_ptr_type;

	typedef bits_t bits_type;
	typedef bits_t *bits_ptr_type;

	typedef uint32_t bits_sz_type;
	typedef uint32_t type_id_type;

	// public methods ----------------------------------------------------------

	//!	\name Constructors and destructors
	//@{

	//!	\brief Constructor loads existing chest
	basic_chest(solid_type *const solid_ptr)
	{
		set
	}

	//!	\brief Constructor maps new chest
	basic_chest(solid_type *const solid_ptr, const bits_sz_type &bits_sz,
				const type_id_type &type_id = 0);

	template <class s_t, class b_t>
	basic_chest(const basic_chest<s_t, b_t> &from);

	//@}

	bits_sz();
	solid_sz();

	bits_sz_type solid_sz() const;
	solid_type *solid_ptr() const;


protected:
	// protected types ---------------------------------------------------------

	//! \brief bit_box data header
	/*!	Header has size and type identifier of bit_box data. It's for bit_box
		internal usage only.
	*/
	#pragma pack(push, 1)
	struct _header_t
	{
		capacity_type capacity;	//!< \brief Size of bit_box data in bytes
		type_id_type type_id;	//!< \brief Type identifier of bit_box data
	};
	#pragma pack(pop)

private:
	// private data ------------------------------------------------------------

	//!	\brief Pointer on header that precedes stored data
	_header_t *_header;

	//! \brief Pointer on stored data
	/*!	It is a pointer on raw data, without any headers or something else.
	*/
	bits_type *_bits;
};
