/*!	\file     types.h
	\version  0.0.1
	\author   mice, ICQ: 332-292-380, mailto:wonder.mice@gmail.com
	\brief    Declarations of small simple types

	\todo     Add detailed comment for types.h file
*/

#pragma once

#ifndef XDT_BASE_TYPES_INCLUDED
#define XDT_BASE_TYPES_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// headers

// code configuration headers
#include <xdt/base/ostype.h>

// standart C++ library headers
// none

// external libraries headers
// none

// OS specific headers
#ifdef			XDT_OS_MACOS
	#include <Carbon/Carbon.h>
#elif defined	XDT_OS_WINDOWS
	#include <windows.h>
#elif defined	XDT_OS_LINUX

#else
	#error No support for target OS
#endif

// xdt headers
// none


////////////////////////////////////////////////////////////////////////////////
// xdt namespace
namespace xdt {


////////////////////////////////////////////////////////////////////////////////
// public types


////////////////////////////////////////////////////////////////////////////////
// Platform specific public types

#ifdef XDT_OS_MACOS

	//! \brief Unsigned integer 8bit type for Mac OS
	typedef UInt8	uint8;
	//! \brief Unsigned integer 16bit type for Mac OS
	typedef UInt16	uint16;
	//! \brief Unsigned integer 32bit type for Mac OS
	typedef UInt32	uint32;
	//! \brief Signed integer 32bit type for Mac OS
	typedef SInt32	sint32;

#elif defined XDT_OS_WINDOWS

	//! \brief Unsigned integer 8bit type for Windows
	typedef BYTE	uint8;
	//! \brief Unsigned integer 16bit type for Windows
	typedef WORD	uint16;
	//! \brief Unsigned integer 32bit type for Windows
	typedef DWORD	uint32;
	//! \brief Signed integer 32bit type for Windows
	typedef LONG	sint32;

#elif defined XDT_OS_LINUX

	typedef unsigned int uint32;

#else 
	#error No support for target OS
#endif


////////////////////////////////////////////////////////////////////////////////
// Platform independent public types

//!	\brief Just single byte (8 bits).
/*!	It's cool sometimes to have cpecial type for this. Byte is always byte
	and it is good. Like free lunch :^)
*/
typedef uint8 byte_t;



}	// xdt namespace



#endif	// XDT_BASE_TYPES_INCLUDED
