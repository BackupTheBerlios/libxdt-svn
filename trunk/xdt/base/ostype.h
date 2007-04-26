/*******************************************************************************
* file:         ostype.h                                                       *
* version:      0.0.1                                                          *
* author:       mice, ICQ: 332-292-380, mailto:my_mice@mail.ru                 *
* description:  defines specific for OS                                        *
* tests:        ok                                                             *
*******************************************************************************/

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

#if defined _MACOS_ || defined _MACOSX_ || defined __APPLE__
	// cool, it's mac os
	#define XDT_OS_MACOS
	#define XDT_OSTYPE_UNIX
#elif defined WIN32 || defined WIN64 || defined WINDOWS
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
