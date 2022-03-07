
AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\"

AM_CFLAGS =\
	 -Wall\
	 -g

bin_PROGRAMS = saturno exp-virtual

noinst_SCRIPTS = exp-virtual.sh

lib_LTLIBRARIES = liboctetos-saturno.la

liboctetos_saturno_la_CXXFLAGS = $(SATURNO_CFLGAS)  
liboctetos_saturno_la_LIBADD = $(SATURNO_LIBS)
liboctetos_saturno_la_SOURCES = Exception.cc saturno.cc Votacion.cc 

saturno_LDADD = liboctetos-saturno.a
saturno_SOURCES = Main.cc saturno-main.cc 
saturno_LDFLAGS = $(OCTETOS_SATURNO_CFLAGS) 
saturno_LDADD = $(OCTETOS_SATURNO_LIBS) 

exp_virtual_SOURCES = saturno.cc exp-virtual.cc
exp_virtual_LDFLAGS = $(OCTETOS_SATURNO_CFLAGS) 
exp_virtual_LDADD = $(OCTETOS_SATURNO_LIBS) 

