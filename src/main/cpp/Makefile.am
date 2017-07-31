lib_LTLIBRARIES = libmodule_vtun.la

libmodule_vtun_la_SOURCES  = vtun.cpp
libmodule_vtun_la_CXXFLAGS = -Wall -Wno-write-strings -fno-strict-aliasing \
                             -I$(builddir) -I$(srcdir) \
                             @ROBOTKERNEL_CFLAGS@ @LIBSTRING_UTIL_CFLAGS@ @YAML_CPP_CFLAGS@
libmodule_vtun_la_LDFLAGS  = -Wall -release $(PACKAGE_VERSION) 

VPATH = $(top_srcdir):$(srcdir)
