AM_CPPFLAGS = -I$(top_srcdir)/src
lib_LTLIBRARIES = libwebpmux.la

libwebpmux_la_SOURCES =
libwebpmux_la_SOURCES += demux.c
libwebpmux_la_SOURCES += muxedit.c
libwebpmux_la_SOURCES += muxi.h
libwebpmux_la_SOURCES += muxinternal.c
libwebpmux_la_SOURCES += muxread.c

libwebpmuxinclude_HEADERS =
libwebpmuxinclude_HEADERS += ../webp/mux.h
libwebpmuxinclude_HEADERS += ../webp/types.h

libwebpmux_la_LDFLAGS = -version-info 0:0:0
libwebpmuxincludedir = $(includedir)/webp
