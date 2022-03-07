

check_PROGRAMS = v0
TESTS= $(check_PROGRAMS)


v0_LDFLAGS =
v0_LDADD = $(CUNIT_LIBS) $(LIBCONFIG_LIBS) $(top_builddir)/src/liboctetos-saturno.a
v0_CPPFLAGS = $(CUNIT_CFLAGS) $(LIBCONFIG_CFLAGS) -I$(top_srcdir)/src -I$(top_builddir)/src -DSRCDIRTEST='"$(top_srcdir)/tests"'
v0_SOURCES = main.cc  
