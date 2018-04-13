#ifndef ProjectTemplateLinuxConfig_h
#define ProjectTemplateLinuxConfig_h

/*
 * Copyright (c) 1997 - 2013 Askesis B.V. See license.txt for details.
 * For information, bug reports and additions send an e-mail to ProjectTemplate@Askesis.nl.
 *
 * Author: jkr
 */

#ifdef PROJECTTEMPLATE_COMPILER
#undef PROJECTTEMPLATE_COMPILER
#endif
#define PROJECTTEMPLATE_COMPILER 					"GCC/linux"

#if defined ( PROJECTTEMPLATEDLL )
	#define PROJECTTEMPLATEIMPEXP
#elif defined ( PROJECTTEMPLATEEXE )
	#define PROJECTTEMPLATEIMPEXP
#elif defined ( PROJECTTEMPLATEEXEDLL )
	#define PROJECTTEMPLATEIMPEXP
else
	#error "No PROJECTTEMPLATEEXE, PROJECTTEMPLATEDLL or PROJECTTEMPLATEEXEDLL defined."
#endif // PROJECTTEMPLATEDLL | PROJECTTEMPLATEEXE | PROJECTTEMPLATEEXEDLL

#ifdef __PROJECTTEMPLATEFUNCTION__
	#undef __PROJECTTEMPLATEFUNCTION__
	#define __PROJECTTEMPLATEFUNCTION__		__PRETTY_FUNCTION__
#endif

#endif // ProjectTemplateLinuxConfig_h
