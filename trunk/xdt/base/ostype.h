/*!	\file     ostype.h
	\version  0.0.1
	\author   mice, ICQ: 332-292-380, mailto:wonder.mice@gmail.com
	\brief    OS specific defines

	This header serves only one purpose - it detects OS and OS type on wich
	(or for wich) it is sompiled.
*/

#pragma once

#ifndef XDT_BASE_OSTYPE_INCLUDED
#define XDT_BASE_OSTYPE_INCLUDED

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
// none


////////////////////////////////////////////////////////////////////////////////
// defines

#if defined __APPLE__
	// cool, it's mac os!
	#define XDT_OS_MACOS
	#define XDT_OSTYPE_UNIX
#elif defined __linux__
	// fine, it's linux
	#define XDT_OS_LINUX
	#define XDT_OSTYPE_UNIX
#elif defined __windows__ || defined WIN32 || defined WIN64
	// ok, it's windows
	#define XDT_OS_WINDOWS
	#define XDT_OSTYPE_WINDOWS
#else
	// bad, no support for this OS now
	#error No support for target OS
#endif


////////////////////////////////////////////////////////////////////////////////
// xdt namespace
namespace xdt {




}	// xdt namespace



#endif	// XDT_BASE_OSTYPE_INCLUDED
