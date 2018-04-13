#ifndef ProjectTemplateMinGWConfig_h
#define ProjectTemplateMinGWConfig_h

/*
 * Copyright (c) 1997 - 2013 Askesis B.V. See license.txt for details.
 * For information, bug reports and additions send an e-mail to ProjectTemplate@Askesis.nl.
 *
 * Author: jkr
 */

#ifdef PROJECTTEMPLATE_COMPILER
#undef PROJECTTEMPLATE_COMPILER
#endif
#define PROJECTTEMPLATE_COMPILER 					"GCC/mingw"

#define WIN32_LEAN_AND_MEAN

#if defined ( PROJECTTEMPLATEDLL )
	#define PROJECTTEMPLATEIMPEXP __declspec(dllexport)
#elif defined ( PROJECTTEMPLATEEXE )
	#define PROJECTTEMPLATEIMPEXP __declspec(dllimport)
#elif defined ( PROJECTTEMPLATEEXEDLL )
	#define PROJECTTEMPLATEIMPEXP
else
	#error "No PROJECTTEMPLATEEXE, PROJECTTEMPLATEDLL or PROJECTTEMPLATEEXEDLL defined."
#endif // PROJECTTEMPLATEDLL | PROJECTTEMPLATEEXE | PROJECTTEMPLATEEXEDLL

#ifdef __PROJECTTEMPLATEFUNCTION__
	#undef __PROJECTTEMPLATEFUNCTION__
	#define __PROJECTTEMPLATEFUNCTION__		__PRETTY_FUNCTION__
#endif

#ifdef PROJECTTEMPLATE_UNICODE
	#if !defined(UNICODE)
		#define UNICODE
	#endif
	#if !defined(_UNICODE)
		#define _UNICODE
	#endif
#endif

// We have to disable these warnings for Boost under Windows?
#pragma GCC diagnostic ignored "-Wattributes"
#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"



#endif // ProjectTemplateMinGWConfig_h
