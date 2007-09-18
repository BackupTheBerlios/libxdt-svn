/*!	\file		basic_chest.h
	\version	0.0.1
	\author		mice, ICQ: 332-292-380, mailto:wonder.mice@gmail.com
	\brief		Declarations and difinitions for xdt::bit_box::basic_chest
				template class

	\sa xdt::bit_box::basic_chest, xdt::bit_box

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
	typedef xdt::bit_box::basic_chest<char, int> rw_chest;
	typedef xdt::bit_box::basic_chest<const char, const int> r_chest;

	// allocate some memory for solid block
	char *const ptr = new char[rw_chest::solid_sz(sizeof(int))];

	// attach to this raw and clean solid block
	const rw_chest ch1(ptr, sizeof(int), rw_chest::bbt_sint32);

	// set stored data
	(*ch1.bits()) = 4;

	// use copy constructor
	const r_chest ch2(ch1);

	// we will fail here, because this basic_chest is read only
	// (*ch2.bits()) = 4;

	// attach another basic_chest to our solid block
	const r_chest ch3(ch1.solid_ptr());

	// test result
	std::cout << (*ch3.bits()) << std::endl;

	// free memory
	delete[] ptr;
	\endcode

	<i>%basic_chest</i> is not very useful by itself. However here is a small
	example to simplify understanding of this class:
	\code
	\endcode
	
	Few words about template parameters. <i>solid_t</i> serves to build
	pointer type <i>(solid_t *)</i> that will represent pointers on solid
	blocks. <i>bits_t</i> serves to build <i>(bits_t *)</i> pointer type that
	will represent pointers on data, stored in <i>%basic_chest</i>.

	\todo basic_chest needs some example code
*/
template <class solid_t, class bits_t>
class basic_chest
{
public:
	// friends -----------------------------------------------------------------

	//!	\brief Friend <i>%basic_chest</i> with all kind of template parameters
	/*!	We need this, to have access to private and protected members of
		<i>%basic_chest</i> classes with different template parameters. This is
		very important for converting constructor and converting assigment
		operator.
	*/
	template <class solid_from_t, class bits_from_t>
	friend class basic_chest;

	// public types ------------------------------------------------------------

	//!	\brief Alias for template parameter <i>solid_t</i>
	/*!	This type is used to construct type <i>(solid_type *)</i> for pointers
		on <i>%bit_box</i> solid blocks (stored data with header). The main
		idea is to have an opportunity to work with pointers on constant data
		and with pointers on volatile data.
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
	/*!
	*/
	typedef uint32_t type_id_type;

	//!	\brief Type for size and count values
	/*!
	*/
	typedef uint32_t size_type;

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

	//!	\brief Default constructor
	/*!
	*/
	basic_chest(): _header(0), _bits(0)
	{
	}
	
	//! \brief Constructor (attachs to existing solid block)
	/*!	\param[in] solid_ptr Pointer on valid <i>%bit_box</i> data block
		(<i>solid block</i>)

		\attention It's very important, that <b>valid</b> header must precedes
		stored data.

		\sa basic_chest::_use()
	*/
	basic_chest(solid_type *const solid_ptr)
	{
		_use(solid_ptr);
	}

	//! \brief Constructor (initializes new solid block)
	/*!	\param[in,out] solid_ptr Pointer on memory block, that will become
		valid <i>%bit_box</i> data block (<i>solid block</i>)
		\param[in] bits_sz Size of stored data (in bytes)
		\param[in] type_id Type identifier of stored data

		\sa basic_chest::_use()
	*/
	basic_chest(solid_type *const solid_ptr, const bits_sz_type &bits_sz,
				const type_id_type &type_id)
	{
		_use(solid_ptr, bits_sz, type_id);
	}

	//! \brief Copy constructor
	/*!	\param[in] from Source <i>basic_bit_box</i> to copy from. Nothing
		tricky, just copy as is.

		\attention This copy constructor copies only pointers, not their data.
		<i>%basic_chest</i> does no any memory allocations in every its part.
		Remember it :^)
	*/
	basic_chest(const self_type &from):
		_header(from._header),
		_bits(from._bits)
	{
	}

	//! \brief Convert constructor
	/*!	\param[in] from Source <i>basic_bit_box</i> to copy from. Nothing
		tricky, just copy as is.

		\attention This convert constructor copies only pointers, not their
		data. <i>%basic_chest</i> does no any memory allocations in every
		its part. Remember it :^)

		\attention You can't assign <i>basic_bit_box</i> with
		<i>bits_type</i>, for example, <i>const xdt::byte_t</i> to
		<i>basic_bit_box</i> with <i>bits_type</i> <i>xdt::byte_t</i>. In
		first case we have pointer on constant data. In second - pointer on
		volatile data. So, if you will get a compilation error here - check
		your code once again on such mistakes. The same rule is also valid for
		<i>solid_type</i>.
	*/
	template <class solid_from_t, class bits_from_t>
	basic_chest(const basic_chest<solid_from_t, bits_from_t> &from):
		_header(reinterpret_cast<_header_type *>(from._header)),
		_bits(reinterpret_cast<bits_type *>(from._bits))
	{
	}

	//!	\brief Destructor
	/*!	\todo Do we really need it? May be it must be virtual?
	*/
	virtual ~basic_chest()
	{
	}

	//@}


	//!	\name Data access functions
	//@{

	//!	\brief Checks, if <i>%basic_chest</i> is down
	/*!	\return <i>true</i> if <i>%basic_chest</i> is down

		Down means "not pointing on some actual data" or "uninitialized".
		<i>%basic_chest</i> can be in down state only if it was default
		constructed or after call to _down() method.
	*/
	bool is_down() const
	{
		return (0 == _header || 0 == _bits);
	}

	//!	\brief Returns size of bit_box data
	/*! \return Size of bit_box data in bytes (8 bits)
	*/
	const size_type &bits_sz() const
	{
		assert(0 != _header);

		return _header->bits_sz;
	}

	//!	\brief Returns pointer on bit_box data
	/*!	\return Pointer on bit_box data
	*/
	bits_type *bits() const
	{
		assert(0 != _bits);

		return _bits;
	}

	//!	\brief Returns type identifier of stored data
	/*! \return Constant reference on type identifier of stored data
	*/
	const type_id_type &type_id() const
	{
		assert(0 != _header);

		return _header->type_id;
	}

	//!	\brief Returns type identifier of stored data
	/*! \return Reference on type identifier of stored data

		With this function you can change type identifier of stored data,
		so be careful with it.

		Maybe it's a good idea to put it in protected section in derived
		classes.
	*/
	type_id_type &type_id()
	{
		assert(0 != _header);

		return _header->type_id;
	}

	//!	\brief Returns total ammount of bytes occupied by solid block
	/*!	\return Total size (in bytes) of solid block
	*/
	size_type solid_sz() const
	{
		return (sizeof(_header_type) + bits_sz());
	}

	//!	\brief Returns pointer on solid block
	/*!	\return Pointer on solid block
	*/
	solid_type *solid_ptr() const
	{
		assert(0 != _header);

		return reinterpret_cast<solid_type *>(_header);
	}

	//@}

	//!	\name Static information
	//@{

	//!	\brief Returns amount of bytes required for solid block that can
	//!	store specified amount of data
	/*!	\param[in] bits_sz Size (in  bytes) of stored data
		\return Size of solid block (in bytes) that can hold specified
		amount of sotored data.

		\note Return value is invariant for different template parameters.
		This is part of design and you can always count on this.
	*/
	static size_type solid_sz(const bits_sz_type &bits_sz)
	{
		return (sizeof(_header_type) + bits_sz);
	}

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
		//!	\brief Size of stored data (in bytes)
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

	//!	\name Use methods
	//@{

	//!	\brief Attaches <i>%basic_chest</i> to valid <i>%bit_box</i> data block
	/*!	\param[in] solid_ptr Pointer on valid <i>%bit_box</i> data block
		(<i>solid block</i>)

		This function tells <i>%basic_chest</i> to use specified memory block.
		It extracts header information and gets pointer on data, stored
		in this block. So, it's up to you to provide good pointers on valid
		solid blocks. After call to this function you can start using
		basic_chest::_header and basic_chest::_bits pointers to work with
		attached solid block. But be careful, it is big responsibility to have
		full access to all <i>%basic_chest</i> header information. For example,
		if's very bad idea to change _header_t::bits_sz field, because you
		can loose integrity on higher level (break <i>%bit_box</i> data chain,
		corrupt memory or something like this).

		Constructor or assigment operator is a good place for this function.
	*/
	void _use(solid_t *const solid_ptr)
	{
		assert(0 != solid_ptr);

		_header	= (_header_type *)solid_ptr;
		
		_bits = reinterpret_cast<bits_type *>(_header + 1);
	}

	//!	\brief Attaches <i>%basic_chest</i> to memory block and initializes
	//!	it to be a valid <i>%bit_box</i> data block (<i>solid block</i>)
	/*!	\param[in,out] solid_ptr Pointer on memory block, that will become
		valid <i>%bit_box</i> data block (<i>solid block</i>)
		\param[in] bits_sz Size of stored data (in bytes)
		\param[in] type_id Type identifier of stored data

		This function marks (formats) raw memory block to be a valid
		<i>%bit_box</i> data block (<i>solid block</i>). Note, that you must
		specify size of stored data - be careful here, there is know polite
		way to do this. After call to this function you will be allowed only
		to change type identifier (through _set_type_id() function) and
		stored data itself.

		Possibly, it is a good idea, to make <i>%type_id</i> parameter
		optional.
	*/
	void _use(solid_t *const solid_ptr, const bits_sz_type &bits_sz,
			  const type_id_type &type_id)
	{
		_use(solid_ptr);

		assert(0 != _header);

		_header->bits_sz = bits_sz;
		_header->type_id = type_id;
	}

	//!	\brief Brings <i>%basic_chest</i> down (makes it invalid)
	/*!	Function sets all internal pointers to <i>0</i>, so <i>%basic_chest</i>
		becomes invalid (bad).
	*/
	void _down()
	{
		_header	= 0;
		_bits	= 0;
	}

	//@}

	//!	\name Assigment operators
	//@{

	//!	\brief Assigment operator
	/*!	\param[in] from Source <i>%basic_chest</i> to copy information from
	*/
	self_type &operator = (const self_type &from)
	{
		_header	= tt._header;
		_bits	= from._bits;

		return (*this);
	}

	//!	\brief Assigment operator with conversion
	/*!	\param[in] from Source <i>%basic_chest</i> to copy information from
	*/
	template <class solid_from_t, class bits_from_t>
	self_type &operator = (const basic_chest<solid_from_t, bits_from_t> &from)
	{
		_header	= reinterpret_cast<_header_type *>(from._header);
		_bits	= reinterpret_cast<bits_type *>(from._bits);

		return (*this);
	}

	//@}

private:
	// private data ------------------------------------------------------------

	//!	\brief Pointer on header that precedes stored data
	/*!	This pointer can be set to <i>0</i> to indicate that
		<i>%basic_chest</i> is invalid (bad).
	*/
	_header_type *_header;

	//! \brief Pointer on stored data
	/*!	It is a pointer on raw data, without any headers or something else.
		It can be set to <i>0</i> to indicate that <i>%basic_chest</i> is
		invalid (bad).
	*/
	bits_type *_bits;

};



}	// bit_box namespace



}	// xdt namespace



#endif	// XDT_BIT_BOX_BASIC_CHEST_INCLUDED
