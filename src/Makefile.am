
AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\"

AM_CFLAGS =\
	 -Wall\
	 -g

bin_PROGRAMS = saturno

saturno_SOURCES = \
	Exception.cc saturno.cc main.cc

saturno_LDFLAGS = $(OCTETOS_SATURNO_CFLAGS) 

saturno_LDADD = $(OCTETOS_SATURNO_LIBS) 


