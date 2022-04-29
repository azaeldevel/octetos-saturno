

AC_INIT(octetos-saturno, 0.11.0-alpha, azael.devel@gmail.com)

AC_CONFIG_HEADERS([config.h])

AM_INIT_AUTOMAKE

AM_SILENT_RULES([yes])

AC_PROG_CXX
AX_CXX_COMPILE_STDCXX(20)

dnl ***************************************************************************
dnl Internationalization
dnl ***************************************************************************
dnl IT_PROG_INTLTOOL([0.35.0])

dnl GETTEXT_PACKAGE=octetos_saturno
dnl AC_SUBST(GETTEXT_PACKAGE)
dnl AC_DEFINE_UNQUOTED(GETTEXT_PACKAGE,"$GETTEXT_PACKAGE", [GETTEXT package name])
dnl AM_GLIB_GNU_GETTEXT

LT_INIT

PKG_CHECK_MODULES(OCTETOS_SATURNO, [octetos-core])

AM_CONDITIONAL(WITH_TESTS, test x"$with_tests" = "xyes")
AC_ARG_WITH([tests], AS_HELP_STRING([--with-tests], [Compilando con soporte para Tests]))
if test "x$with_tests" = "xyes"; then 
	PKG_CHECK_MODULES(CUNIT,cunit)
fi

AM_CONDITIONAL(ENABLE_DEBUG, test x"$enable_debug" = "xyes")
AC_ARG_WITH([debug], AS_HELP_STRING([--enable-debug], [Actiacion de opcion de depuracion]))
if test "x$enable_debug" = "xyes"; then 
	OCTETOS_SATURNO_DEBUG=1
else
	OCTETOS_SATURNO_DEBUG=0
fi

AC_OUTPUT([
Makefile
src/Makefile
tests/Makefile
src/octetos-saturno.pc
])
