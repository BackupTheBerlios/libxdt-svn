/*!	\file     types.h
	\version  0.0.1
	\author   mice, ICQ: 332-292-380, mailto:wonder.mice@gmail.com
	\brief    Declarations of small simple types

	Here you can find simple type declarations. There is no complex
	structures or cool classes with smart and convenient methods - just
	atomic types, small bricks to build <i>xdt</i> library.

	Like any other library, <i>xdt</i> defines its own types for some
	platform specific things, like 32-bit or 64-bit integer. Now support
	of this kind of types is very poor.
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
	#error TODO: what is unix header for this?
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
	typedef UInt8	uint8_t;
	//! \brief Unsigned integer 16bit type for Mac OS
	typedef UInt16	uint16_t;
	//! \brief Unsigned integer 32bit type for Mac OS
	typedef UInt32	uint32_t;
	//! \brief Signed integer 32bit type for Mac OS
	typedef SInt32	sint32_t;

#elif defined XDT_OS_WINDOWS

	//! \brief Unsigned integer 8bit type for Windows
	typedef BYTE	uint8_t;
	//! \brief Unsigned integer 16bit type for Windows
	typedef WORD	uint16_t;
	//! \brief Unsigned integer 32bit type for Windows
	typedef DWORD	uint32_t;
	//! \brief Signed integer 32bit type for Windows
	typedef LONG	sint32_t;

#elif defined XDT_OS_LINUX

	#error No typedefs for this OS now

#else 
	#error No support for target OS
#endif


////////////////////////////////////////////////////////////////////////////////
// Platform independent public types

//!	\brief Just single byte (8 bits).
/*!	It's cool sometimes to have cpecial type for this. Byte is always byte
	and it is good. Like free lunch :^)
*/
typedef uint8_t byte_t;



}	// xdt namespace



#endif	// XDT_BASE_TYPES_INCLUDED
