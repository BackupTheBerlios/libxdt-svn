/*******************************************************************************
* file:         cf_wrap.h                                                      *
* version:      0.0.1                                                          *
* author:       mice, ICQ: 332-292-380, mailto:wonder.mice@gmail.com           *
* description:  wrapper class for Handle Mac OS object                         *
* tests:        ok                                                             *
*******************************************************************************/

#pragma once

#ifndef XDT_MACOS_HANDLE_W_INCLUDED
#define XDT_MACOS_HANDLE_W_INCLUDED

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
#include <Carbon/Carbon.h>
#else
#error Only Mac OS X supported
#endif

// xdt headers
// none


////////////////////////////////////////////////////////////////////////////////
// xdt namespace
namespace xdt {


////////////////////////////////////////////////////////////////////////////////
// mac namespace
namespace mac {


////////////////////////////////////////////////////////////////////////////////
// handle_w class declaration
//! \brief Wrapper class for \c Handle Mac OS object
/*!	This class wrapps Handle Mac OS object. It calls DisposeHandle() in
	destructor, so there is no need to release it by hands. It is the main
	and the only feature of this class. It's very simple and clear.

	\attention Handle objects can't be retained, like Core Foundation objects.
	That because this class has no copy constructor. Mac OS Handle is much
	like a single pointer with several features.

	This class is very convenient, but not absolutely safe. Please, use it
	with care and avoid thing like this:
	\code
	void some_func {
		handle_w h(1024);
		
		// ...
		
		DisposeHandle(h.get());
	}
	\endcode
	
	Also, this class does not checks any error codes returned by Handle
	functions (yet).
*/
class handle_w {
public:
	// public methods ----------------------------------------------------------
	
	//! \brief Constructor
	/*!	\param[in] sz Size of memory in bytes to alloc.

		This constructor creates new handle objects, allocating some memory
		for it. It is safe enough, so prefer it, where possible. Try to
		minimize usage of "own constructor".
	*/
	handle_w(Size sz): _h(NewHandle(sz)), _locked(false) {}

	//! \brief Own constructor (use with care)
	/*!	This constructor owns the Handle object. Handle object MUST
		not be locked. This method is dangerous, so use it with care.
		Nerver write code like this:
		\code
		{
			xdt::mac::handle_w h_01(1024);
			xdt::mac::handle_w h_02(h_01.get());
		}
		\endcode
		This will crash your program or entire Mac OS.
	*/
	handle_w(const Handle &h): _h(h), _locked(false) {}

	//! \brief Destructor
	/*!	Destructor always calls DisposeHandle(), except thos case, when
		internal Handle object is 0. If Handle was locked, it calls
		HUnlock() to unlock it. Handle does not support lock/unlock
		managment, so do not call HLock() or HUnlock() on wrapped handle.
		Use it's methods instead.
	*/
	~handle_w() {
		if (0 == _h) return;
		
		unlock();
		
		DisposeHandle(_h);
	}
	
	//! \brief Returns locked state (\c true if locked)
	/*!	\return \c true if Handle is locked.

		This function does not knows exactly locked Handle object or not.
		Result is based on lock() and unlock() calls, considering, that
		initially Handle was not locked. Try not to use this function if
		possible.
	*/
	bool locked() const { return _locked; }
	
	//! \brief Calls to HLock() and locks the handle
	/*!	\return Self reference

		Can lock only valid not 0 Handle
	*/
	handle_w &lock() {
		if (_locked || 0 == _h) return (*this);
		
		HLock(_h);
		_locked = true;
		
		return (*this);
	}
	
	//! \brief Calls to HUnlock() and unlocks the handle
	/*!	\return Self reference
	
		Can unlock only valid not 0 Handle
	*/
	handle_w &unlock() {
		if (!_locked || 0 == _h) return (*this);
		
		HUnlock(_h);
		_locked = false;
		
		return (*this);
	}
	
	//! \brief Returns internal Handle object
	const Handle &get() const { return _h; }
	
	//! \brief Returns Handle data
	char *data() const { return ( (_locked)? (*_h): 0 ); }

	//! \brief Returns Handle data and lock handle
	char *ptr() { return (lock().data()); }

	//! \brief Returns size of memory block
	Size sz() const { return GetHandleSize(_h); } 

protected:
	// protected methods -------------------------------------------------------

private:
	// private data ------------------------------------------------------------
		
	//! \brief Handle object
	Handle _h;
	
	//! \brief \c true when Handle is locked
	bool _locked;
};



}	// mac namespace



}	// xdt namespace



#endif	// XDT_MACOS_HANDLE_W_INCLUDED
