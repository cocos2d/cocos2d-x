AM_CPPFLAGS = -I$(top_srcdir)/src
noinst_LTLIBRARIES = libwebpencode.la

libwebpencode_la_SOURCES =
libwebpencode_la_SOURCES += alpha.c
libwebpencode_la_SOURCES += analysis.c
libwebpencode_la_SOURCES += backward_references.c
libwebpencode_la_SOURCES += config.c
libwebpencode_la_SOURCES += cost.c
libwebpencode_la_SOURCES += cost.h
libwebpencode_la_SOURCES += filter.c
libwebpencode_la_SOURCES += frame.c
libwebpencode_la_SOURCES += histogram.c
libwebpencode_la_SOURCES += iterator.c
libwebpencode_la_SOURCES += layer.c
libwebpencode_la_SOURCES += picture.c
libwebpencode_la_SOURCES += quant.c
libwebpencode_la_SOURCES += syntax.c
libwebpencode_la_SOURCES += tree.c
libwebpencode_la_SOURCES += vp8enci.h
libwebpencode_la_SOURCES += vp8l.c
libwebpencode_la_SOURCES += webpenc.c

libwebpencodeinclude_HEADERS =
libwebpencodeinclude_HEADERS += ../webp/encode.h
libwebpencodeinclude_HEADERS += ../webp/types.h
noinst_HEADERS =
noinst_HEADERS += ../webp/format_constants.h

libwebpencode_la_LDFLAGS = -lm
libwebpencode_la_CPPFLAGS = $(USE_EXPERIMENTAL_CODE)
libwebpencodeincludedir = $(includedir)/webp
