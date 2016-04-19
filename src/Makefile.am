libdir = $(prefix)/lib
lib_LTLIBRARIES = libmodule_vtun.la

libmodule_vtun_la_SOURCES  = \
	vtun.cpp
libmodule_vtun_la_CXXFLAGS = -Wall -I$(top_builddir) @ARCH_CFLAGS@ @ROBOTKERNEL_CFLAGS@ -Wno-write-strings -fno-strict-aliasing @LIBSTRING_UTIL_CFLAGS@
libmodule_vtun_la_LDFLAGS  = -Wall @LIBSTRING_UTIL_LIBS@ -release $(PACKAGE_VERSION)

VPATH = $(srcdir)
