AM_CPPFLAGS = -I$(top_srcdir)/src
noinst_LTLIBRARIES = libwebpdsp.la

libwebpdsp_la_SOURCES =
libwebpdsp_la_SOURCES += cpu.c
libwebpdsp_la_SOURCES += dec.c
libwebpdsp_la_SOURCES += dec_neon.c
libwebpdsp_la_SOURCES += dec_sse2.c
libwebpdsp_la_SOURCES += dsp.h
libwebpdsp_la_SOURCES += enc.c
libwebpdsp_la_SOURCES += enc_sse2.c
libwebpdsp_la_SOURCES += lossless.c
libwebpdsp_la_SOURCES += lossless.h
libwebpdsp_la_SOURCES += upsampling.c
libwebpdsp_la_SOURCES += upsampling_sse2.c
libwebpdsp_la_SOURCES += yuv.c
libwebpdsp_la_SOURCES += yuv.h

libwebpdspinclude_HEADERS = ../webp/types.h
noinst_HEADERS =
noinst_HEADERS += ../dec/decode_vp8.h
noinst_HEADERS += ../webp/decode.h

libwebpdsp_la_LDFLAGS = -lm
libwebpdsp_la_CPPFLAGS = $(USE_EXPERIMENTAL_CODE)
libwebpdspincludedir = $(includedir)/webp
