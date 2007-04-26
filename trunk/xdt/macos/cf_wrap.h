/*******************************************************************************
* file:         cf_wrap.h                                                      *
* version:      0.0.1                                                          *
* author:       mice, ICQ: 332-292-380, mailto:wonder.mice@gmail.com           *
* description:  wrappers for Mac OS Core Foundation objects                    *
* tests:        ok                                                             *
*******************************************************************************/

#pragma once

#ifndef XDT_MACOS_CF_WRAP_INCLUDED
#define XDT_MACOS_CF_WRAP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// headers

// code configuration headers
// none

// standart C++ library headers
// none

// external libraries headers
// none

// OS specific headers
#ifdef XDT_OS_MACOS
#include <CoreFoundation/CoreFoundation.h>
#else
#error Only Mac OS X supported
#endif

// xdt headers
#include <xdt/base/ostype.h>


////////////////////////////////////////////////////////////////////////////////
// xdt namespace
namespace xdt {


////////////////////////////////////////////////////////////////////////////////
// cf_ref_w class declaration
//! \brief Wrapper class for \c CFTypeRef like objects (CFString, CFArray, ...)
/*!	Template class to wrap different Mac OS Core Foundation objects.
	Like those with "CF" prefix and many others, without it.

	This class serves one purpose - to release Core Foundation object when it
	is not needed any more. It is very small and clear.

	\warning This class is not thread safe. It is very simple. To achive more
	complex object management you have to write additional code.

	\warning Use this wrapper class only with those Core Foundation objects,
	that need \c CFRelease().
*/
template <class ref_t>
class cf_ref_w {
public:
	// public types ------------------------------------------------------------
	
	//! \brief Type of Core Foundation object under control
	/*!	This can be used to access wrapper type information at runtime
	*/
	typedef ref_t cf_ref_t;
	
	// public functions --------------------------------------------------------
	
	//! \brief Constructor
	inline cf_ref_w(const ref_t &ref);
	
	//! \brief Copy constructor
	inline cf_ref_w(const cf_ref_w<ref_t> &wrapped);
	
	//! \brief Destructor
	virtual ~cf_ref_w();
	
	//! \brief Returns wrapped CF object reference
	inline ref_t get() const { return _ref; }

	//! \brief Returns wrapped CF object reference
	inline ref_t operator()() const { return _ref; }

	//! \brief Returns wrapped CF object reference
	/*!	This can be used only for non-mutable CF objects.
	*/
	inline const ref_t &ref() const { return _ref; }
	
protected:
private:
	// private data ------------------------------------------------------------

	//! \brief Core Foundation object reference
	/*!	Once assigned in constructor it can not be changed any more
	*/
	const ref_t _ref;
};



////////////////////////////////////////////////////////////////////////////////
// predefined wrapped types

//! \brief Wrapper for CFString
typedef cf_ref_w<CFStringRef> cf_string_w;

//! \brief Wrapper for CFArray
typedef cf_ref_w<CFArrayRef> cf_array_w;

//! \brief Wrapper for CFURL
typedef cf_ref_w<CFURLRef> cf_url_w;

//! \brief Wrapper for CFDictionary
typedef cf_ref_w<CFDictionaryRef> cf_dict_w;

//! \brief Wrapper for CFData
typedef cf_ref_w<CFDataRef> cf_data_w;



////////////////////////////////////////////////////////////////////////////////
// cf_ref_w class public definitions

/*!	\param[in] ref CFTypeRef object

	This constructor does not call to CFRetain() funcion. It must be used only
	with CF functions that use "Create rule". If function use "Get rule", one
	have no need in any wrappers (or CF object must be retained manually).

	This template class hase no error checking, except destructor, so you are
	responsible to check returned result (see example).

	Example:
	\code
	// declare new type for CFStringRef wrapper
	typedef xdt::cf_ref_w<CFStringRef> cf_string_w;

	// create wrapped object
	cf_string_w string_wrapped(
			CFStringCreateWithCString(0, "Hello World!",
									  kCFStringEncodingMacRoman)
	);
	if (0 == string_wrapped.get()) {
		return -1;
	}
	\endcode
*/
template <class ref_t>
cf_ref_w<ref_t>::cf_ref_w(const ref_t &ref): _ref(ref) {
}


/*!	\param[in] w Core Foundation wrapped object

	This constructor calls CFRetain() to retain object reference, so
	it's pretty safe. Also constructor checks for null references and
	ignores them (no CFRetain() or CFRelease() called)
*/
template <class ref_t>
cf_ref_w<ref_t>::cf_ref_w(const cf_ref_w<ref_t> &w): _ref(w.get()) {
	if (0 != _ref) CFRetain(_ref);
}


/*!	Destructor calls CFRelease() if internal reference on
	Core Foundation object is not 0.
*/
template <class ref_t>
cf_ref_w<ref_t>::~cf_ref_w() {
	if (0 != _ref) CFRelease(_ref);
}



}	// xdt namespace



#endif	// XDT_MACOS_CF_WRAP_INCLUDED
