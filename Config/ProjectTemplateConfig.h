#ifndef PROJECTTEMPLATECONFIG_H_
#define PROJECTTEMPLATECONFIG_H_

/*
 * Copyright (c) 1997 - 2013 Askesis B.V. See license.txt for details.
 * For information, bug reports and additions send an e-mail to ProjectTemplate@Askesis.nl.
 *
 * Author: jkr
 */

/*! \file
	\brief The main ProjectTemplate configuration file

	This file is a hand coded configure.h. This file contains the global MACROS that are needed for the difference in
	compiler, debug setting etc.. It should always be the first file included in a source file, even before any compiler
	or platform header.

	This file includes the compiler dependent files by checking the compiler defined macros.

	The general idea is to set the global macros to a sensible value first and than to include the compiler specific
	to allow for compiler specific version of the macros.

	A sensible default is a macro that will always go wrong.

	Macros should always be UPPERCASE, using "_" as word boundary if needed for readability

	Do not redefine ANSI macros, but redefine all compiler related macros to some PROJECTTEMPLATE_xxxx macro so that in the code
	no compiler stuff is included other than through the configuration files.

	$Date: 2003/12/24 08:07:56 $
	$Author: jkr $
	$Revision: 1.5 $

*/


/** \defgroup global_configuration_macros Global configuration macros */

/*@{*/

#define PROJECTTEMPLATE_MAJOR   0
#define PROJECTTEMPLATE_MINOR   1

// Implementation comment: because we do not generate platform dependent documentation we must create these defines
// globally as there is no WIN32 or __linux__ defined in the DoxyGen preprocessor....
#define		PROJECTTEMPLATE_PLATFORM_WINDOWS
#define		PROJECTTEMPLATE_PLATFORM_LINUX

#if defined (_WIN32) || defined (__CYGWIN__)
	#undef 		PROJECTTEMPLATE_PLATFORM_WINDOWS
	#define		PROJECTTEMPLATE_PLATFORM_WINDOWS		1
	#undef		PROJECTTEMPLATE_PLATFORM_LINUX
#elif defined (__linux__)
	#undef		PROJECTTEMPLATE_PLATFORM_WINDOWS
	#undef		PROJECTTEMPLATE_PLATFORM_LINUX
	#define		PROJECTTEMPLATE_PLATFORM_LINUX			1
#else
	#error		You must define a platform!!!!
#endif

// Compiler string
#define PROJECTTEMPLATE_COMPILER 					"unknown compiler"

// We use Unicode for all our programs
#define PROJECTTEMPLATE_UNICODE	1

// To prevent compiler warnings
#define UNUSEDPARAM(parameter) /* parameter */
#define UNUSEDCAST(argument) (void)argument

// Not all compilers actually have these macros:
// VC 6.0 has no __FUNCTION__ or __PRETTY_FUNCTION__
// GCC has does not demangle __FUNCTION__ but __PRETTY_FUNCTION__ does etc.
#define __PROJECTTEMPLATEFILE__			__FILE__
#define __PROJECTTEMPLATEFUNCTION__		"Unknown function"
#define __PROJECTTEMPLATELINE__			__LINE__

/*
The following macros are used for compiling shared libraries and executables
#ifdef PROJECTTEMPLATEDLL : we are compiling a DLL
#define PROJECTTEMPLATEIMPEXP __declspec(dllexport)

#elif PROJECTTEMPLATEEXE : we are compiling an executable that uses a DLL
#define PROJECTTEMPLATEIMPEXP __declspec(dllimport)

#elif PROJECTTEMPLATEEXEDLL : we are compiling an executable and include (statically) the dll in the project as
					if is part of the project
#define PROJECTTEMPLATEIMPEXP
*/


/*@}*/

/**
 *	@name Boost defines to make optimal use of Boost
 */
//@{

/**
 * Allow this number of template arguments in the boost::fusion::map used as MOCFunctionParameter
 */
//#define FUSION_MAX_VECTOR_SIZE 30
//#define BOOST_FUSION_DONT_USE_PREPROCESSED_FILES
//#define BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
//#define BOOST_MPL_LIMIT_VECTOR_SIZE 30
//#define FUSION_MAX_MAP_SIZE 30
/**
 * Allow this number of parameters in named parameter functions
 */
//#define BOOST_PARAMETER_MAX_ARITY 30

//@}

// Compiler specific includes.
// Include these files as last so that they can reference the global stuff !!!
#ifdef __MINGW32__
#include "ProjectTemplateMinGWConfig.h"
#endif // __MINGW32__

#ifdef __linux__
#include "ProjectTemplateLinuxConfig.h"
#endif // linux

#endif // PROJECTTEMPLATECONFIG_H_

