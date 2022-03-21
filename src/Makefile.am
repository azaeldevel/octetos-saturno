
AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\"

AM_CFLAGS =\
	 -Wall\
	 -g


lib_LTLIBRARIES = liboctetos-saturno.la

bin_PROGRAMS = saturno exp-virtual

noinst_SCRIPTS = exp-virtual.sh


liboctetos_saturno_la_CXXFLAGS = $(OCTETOS_SATURNO_CFLGAS)  
liboctetos_saturno_la_LIBADD = $(OCTETOS_SATURNO_LIBS)
liboctetos_saturno_la_SOURCES = Exception.cc Saturno.cc Votacion.cc 

saturno_SOURCES = Main.cc main-saturno.cc Main-search.cc
saturno_LDFLAGS = $(OCTETOS_SATURNO_CFLAGS) 
saturno_LDADD = liboctetos-saturno.la $(OCTETOS_SATURNO_LIBS) 

exp_virtual_SOURCES = exp-virtual.cc
exp_virtual_LDFLAGS = $(OCTETOS_SATURNO_CFLAGS) 
exp_virtual_LDADD = $(OCTETOS_SATURNO_LIBS) liboctetos-saturno.la 

