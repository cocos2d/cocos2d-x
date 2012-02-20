LBITS := $(shell getconf LONG_BIT)
ifeq ($(LBITS),64)
FMODEX = libfmodex64
FMODEXL = libfmodexL64
VERSION = 4.38.00
LIBDIR     = lib64/api/lib
HDRDIR     = lib64/api/inc
else
FMODEX = libfmodex
FMODEXL = libfmodexL
VERSION = 4.36.01
LIBDIR     = api/lib
HDRDIR     = api/inc
endif

DESTLIBDIR = /usr/local/lib
DESTHDRDIR = /usr/local/include/fmodex

all:
	@echo "Possible targets:"
	@echo "'make fmod_examples'  - Build all examples"
	@echo "'make install'        - Install FMOD Ex libraries and headers"
	@echo "'make uninstall'      - Uninstall FMOD Ex libraries and headers"

fmod_examples:
	cd examples/3d && make
	cd examples/cdplayer && make
	cd examples/channelgroups && make
	cd examples/dsp_effectperspeaker && make
	cd examples/dsp_custom && make
	cd examples/effects && make
	cd examples/filecallbacks && make
	cd examples/generatetone && make
	cd examples/loadfrommemory && make
	cd examples/multiplesoundcard && make
	cd examples/multispeakeroutput && make
	cd examples/netstream && make
	cd examples/offlinedecoding && make
	cd examples/pitchdetection && make
	cd examples/playlist && make
	cd examples/playsound && make
	cd examples/playstream && make
	cd examples/plugin_dev/codec_raw && make
	cd examples/plugin_dev/dsp_gain && make
	cd examples/readtags && make
	cd examples/realtimestitching && make
	cd examples/recording && make
	cd examples/recordtodisk && make
	cd examples/ripnetstream && make
	cd examples/submixing && make
	cd examples/useplugins && make
	cd examples/usercreatedsound && make
	cd fmoddesignerapi/examples/effects && make
	cd fmoddesignerapi/examples/info_only && make
	cd fmoddesignerapi/examples/load_data && make
	cd fmoddesignerapi/examples/max_playbacks && make
	cd fmoddesignerapi/examples/parameters && make
	cd fmoddesignerapi/examples/programmer_selected && make
	cd fmoddesignerapi/examples/programmer_sound && make
	cd fmoddesignerapi/examples/simple_event && make

install:
	@echo "Installing FMOD Ex libraries and headers..."
	cp -f ${LIBDIR}/${FMODEX}-${VERSION}.so ${DESTLIBDIR}
	cp -f ${LIBDIR}/${FMODEXL}-${VERSION}.so ${DESTLIBDIR}
	ln -s -f ${DESTLIBDIR}/${FMODEX}-${VERSION}.so ${DESTLIBDIR}/${FMODEX}.so
	ln -s -f ${DESTLIBDIR}/${FMODEXL}-${VERSION}.so ${DESTLIBDIR}/${FMODEXL}.so
	ldconfig -n ${DESTLIBDIR}
	mkdir -p ${DESTHDRDIR}
	cp -f ${HDRDIR}/*.h* ${DESTHDRDIR}
	@echo "done."

uninstall:
	@echo "Uninstalling FMOD Ex libraries..."
	rm -f ${DESTLIBDIR}/${FMODEX}.so
	rm -f ${DESTLIBDIR}/${FMODEXL}.so
	rm -f ${DESTLIBDIR}/${FMODEX}-${VERSION}.so
	rm -f ${DESTLIBDIR}/${FMODEXL}-${VERSION}.so
	ldconfig -n ${DESTLIBDIR}
	rm -rf ${DESTHDRDIR}
	@echo "done."
