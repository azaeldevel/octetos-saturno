
AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\"

AM_CFLAGS =\
	 -Wall\
	 -g

bin_PROGRAMS = saturno exp-virtual

noinst_SCRIPTS = exp-virtual.sh

saturno_SOURCES = \
	Exception.cc Main.cc saturno.cc saturno-main.cc Votacion.cc Main-search.cc

saturno_LDFLAGS = $(OCTETOS_SATURNO_CFLAGS) 

saturno_LDADD = $(OCTETOS_SATURNO_LIBS) 

exp_virtual_SOURCES = saturno.cc exp-virtual.cc
exp_virtual_LDFLAGS = $(OCTETOS_SATURNO_CFLAGS) 
exp_virtual_LDADD = $(OCTETOS_SATURNO_LIBS) 

