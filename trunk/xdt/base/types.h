/*******************************************************************************
* file:         types.h                                                        *
* version:      0.0.1                                                          *
* author:       mice, ICQ: 332-292-380, mailto:my_mice@mail.ru                 *
* description:  base types declarations                                        *
* tests:        ok                                                             *
*******************************************************************************/

#pragma once

#ifndef XDT_BASE_TYPES_INCLUDED
#define XDT_BASE_TYPES_INCLUDED

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
#elif defined XDT_OS_WINDOWS
	#include <windows.h>
#else
	#error No support for target OS
#endif

// xdt headers
#include <xdt/base/ostype.h>


////////////////////////////////////////////////////////////////////////////////
// xdt namespace
namespace xdt {


////////////////////////////////////////////////////////////////////////////////
// public types

#ifdef XDT_OS_MACOS

	//! \brief Unsigned integer 8bit type for Mac OS
	typedef UInt8	uint8
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

#else
	#error No support for target OS
#endif



}	// xdt namespace



#endif	// XDT_BASE_TYPES_INCLUDED
