# If given on the commandline, the following options overrule any
# options given in the Autotools files. They either replace the
# value (cc and cxx) or ar added as last and additional/overruling
# argument (all others).
#
#	CC
#	CXX
#	LIBTOOLFLAGS
#	CPPFLAGS
#	CFLAGS
#	CXXFLAGS
#	LDFLAGS

# If you change anything: tabs and spaces matter. Google it....

AC_INIT([projecttemplate],[0.0.1],[J.Kraaijeveld@askesis.nl],[projecttemplate-0.0.1])
AC_CONFIG_AUX_DIR(.)
AM_INIT_AUTOMAKE([subdir-objects])

AC_CONFIG_MACRO_DIR(./m4)

# Check for programs

LT_INIT

AC_PROG_MAKE_SET

AC_PROG_CC
AC_PROG_CXX

AC_LANG([C])
AC_LANG([C++])

AC_CANONICAL_HOST

# Check for libraries

#########################################################################################################
#                     Boost
#########################################################################################################

BOOST_REQUIRE([1.60])
BOOST_SYSTEM([mt])
BOOST_THREAD([mt])
BOOST_FILESYSTEM([mt])
BOOST_CHRONO([mt])
BOOST_TEST([mt])

BOOST_LIBS=""
BOOST_LIBS+="$BOOST_SYSTEM_LIBS "
BOOST_LIBS+="$BOOST_THREAD_LIBS "
BOOST_LIBS+="$BOOST_FILESYSTEM_LIBS "
BOOST_LIBS+="$BOOST_CHRONO_LIBS " # Put a space after every library (except the last one)!
BOOST_LIBS+="$BOOST_UNIT_TEST_FRAMEWORK_LIBS" #see https://github.com/tsuna/boost.m4/blob/master/README for notes on BOOST_TEST
AC_SUBST([BOOST_LIBS])

BOOST_LDFLAGS="$BOOST_SYSTEM_LDFLAGS $BOOST_THREAD_LDFLAGS $BOOST_FILESYSTEM_LDFLAGS $BOOST_CHRONO_LDFLAGS"
# using tr, split string on ' ', sort unique and, using rt, resplit (i.e. concatinate) again on '\n'
BOOST_LDFLAGS=$(echo $BOOST_LDFLAGS | tr ' ' '\n' | sort -u | tr '\n' ' ')
AC_SUBST([BOOST_LDFLAGS])

#########################################################################################################
#                     wxWidgets
#########################################################################################################

AM_OPTIONS_WXCONFIG
AM_PATH_WXCONFIG(3.0.2, wxWin=1, , ,[--debug=yes])
if test "$wxWin" != 1; then
	AC_MSG_ERROR([
				wxWidgets must be installed on your system
				but no wx-config script could be found.

				Please check that wx-config is in path, the directory
				where wxWidgets libraries are installed as returned by
				'wx-config --libs' is in the linker path (LD_LIBRARY_PATH
				or equivalent variable) and wxWidgets version is 2.9.4 or
				above.
		])
	fi
if test "$wxWin" != 0; then
	AC_DEFINE(HAVE_WXWIDGETS,1,[define if the wxWidgets 3.0.2. or higher is available])
fi

#########################################################################################################
#                     Windows Sockets, Unix works out of the box.....
#########################################################################################################
case $host in
*mingw* | *i686-pc-mingw64* | *i686-pc-mingw32* | *i686-pc-msys* | *x86_64-unknown-msys* | *x86_64-w64-mingw32* | *x86_64-pc-msys* )
	SOCKET_LIBS="-lwsock32 -lws2_32"
	;;
esac
AC_SUBST([SOCKET_LIBS])

#########################################################################################################
#                     Set the preprocessor, c-compiler, c++-compiler and linker option
#########################################################################################################

# set the CPP options
case $host in
*linux*)
	PROJECTTEMPLATE_CPPFLAGS=""
	;;
*mingw* | *i686-pc-mingw64* | *i686-pc-mingw32* | *i686-pc-msys* | *x86_64-unknown-msys*)
	PROJECTTEMPLATE_CPPFLAGS="-D_WIN32_WINNT=0x0501"
	;;
*darwin*)
	PROJECTTEMPLATE_CPPFLAGS=""
	;;
esac
AC_SUBST([PROJECTTEMPLATE_CPPFLAGS])

# set the C options
case $host in
*linux*)
	PROJECTTEMPLATE_CFLAGS="-pipe -std=gnu11"
	;;
*mingw* | *i686-pc-mingw64* | *i686-pc-mingw32* | *i686-pc-msys* | *x86_64-unknown-msys*)
	PROJECTTEMPLATE_CFLAGS="-pipe -std=gnu11"
	;;
*darwin*)
	PROJECTTEMPLATE_CFLAGS="-pipe -std=gnu11"
	;;
esac
AC_SUBST([PROJECTTEMPLATE_CFLAGS])

# set the C++ options
case $host in
*linux*)
	PROJECTTEMPLATE_CXXFLAGS="-pipe -std=gnu++11"
	;;
*mingw* | *i686-pc-mingw64* | *i686-pc-mingw32* | *i686-pc-msys* | *x86_64-unknown-msys*)
	PROJECTTEMPLATE_CXXFLAGS="-pipe -std=gnu++11"
	;;
*darwin*)
	PROJECTTEMPLATE_CXXFLAGS="-pipe -std=gnu++11"
	;;
esac
AC_SUBST([PROJECTTEMPLATE_CXXFLAGS])

# set the Linker options
case $host in
*linux*)
	PROJECTTEMPLATE_LDFLAGS=""
	;;
*mingw* | *i686-pc-mingw64* | *i686-pc-mingw32* | *i686-pc-msys* | *x86_64-unknown-msys*)
	PROJECTTEMPLATE_LDFLAGS="-Wl,--subsystem,windows -mwindows"
	;;
*darwin*)
	PROJECTTEMPLATE_LDFLAGS=""
	;;

esac
AC_SUBST([PROJECTTEMPLATE_LDFLAGS])

# Check for headers

AC_HEADER_STDC

# Check for typedefs, structures and compiler chracteristics
# Empty for now

# Check for library functions
# Empty for now

#########################################################################################################

AM_CPPFLAGS=
AM_CFLAGS=
AM_CXXFLAGS=
AM_LDFLAGS=

case $host in
*linux*)
	AM_CPPFLAGS="$AM_CPPFLAGS"
	AM_CFLAGS="$AM_CFLAGS"
	AM_CXXFLAGS="$AM_CXXFLAGS"
	AM_LDFLAGS="-no-undefined"
	;;
*mingw* | *i686-pc-mingw64* | *i686-pc-mingw32* | *i686-pc-msys* | *x86_64-unknown-msys*)
	AM_CPPFLAGS="$AM_CPPFLAGS"
	AM_CFLAGS="$AM_CFLAGS"
	AM_CXXFLAGS="$AM_CXXFLAGS"
	AM_LDFLAGS="-no-undefined -Wl,--enable-runtime-pseudo-reloc,--enable-auto-import"
	;;
*darwin*)
	AM_CPPFLAGS="$AM_CPPFLAGS"
	AM_CFLAGS="$AM_CFLAGS"
	AM_CXXFLAGS="$AM_CXXFLAGS"
	AM_LDFLAGS="-no-undefined"
	;;
esac

#########################################################################################################
#                               Set debug related compiler options
#########################################################################################################

development_default="yes"
AC_ARG_ENABLE(development,
AC_HELP_STRING([--enable-development= no/yes],[if enabled all development features will be on]),
enable_development=$enableval,
enable_development=$development_default)
if test "$enable_development" = "yes"; then
	AM_CPPFLAGS="$AM_CPPFLAGS -DDEVELOPMENT"
	AM_CFLAGS="$AM_CFLAGS -O0 -p -pg -g3 -Wall -Wextra -Wconversion"
	AM_CXXFLAGS="$AM_CXXFLAGS -O0 -p -pg -g3 -Wall -Wextra -Wconversion"
	AC_MSG_RESULT(Enabling development tracing)
else
	AM_CPPFLAGS="$AM_CPPFLAGS -DPRODUCTION"
	AM_CFLAGS="$AM_CFLAGS -O3"
	AM_CXXFLAGS="$AM_CXXFLAGS -O3"
	AC_MSG_RESULT(Enabling production tracing)
fi

AC_SUBST([AM_CPPFLAGS])
AC_SUBST([AM_CFLAGS])
AC_SUBST([AM_CXXFLAGS])
AC_SUBST([AM_LDFLAGS])
#AC_SUBST([AM_LDADD])

AM_LIBTOOLFLAGS="--silent"
AC_SUBST([AM_LIBTOOLFLAGS])

AC_PROG_INSTALL

# Output files
AC_CONFIG_HEADER([Config/config.h])
AC_CONFIG_FILES(	Makefile	\
					Lib1/Makefile	\
					Lib2/Makefile	\
					Exe1/Makefile	\
					Exe2/Makefile	\
					TestExe1/Makefile	\
					TestExe2/Makefile)
AC_OUTPUT
