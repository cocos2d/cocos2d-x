PLATFORM	=	$(shell uname -m)
DEBUG		=	yes

CC		=	gcc
CXX		=	g++
AR		=	ar

CCFLAGS		=	-Wall
CXXFLAGS	=	-Wall
ARFLAGS		=	cr

ifeq ($(PLATFORM),x86_64)

CCLIBFLAGS	=	-fPIC
CXXLIBFLAGS	=	-fPIC

endif

ifeq ($(DEBUG),yes)

CCFLAGS		+=	-g
CXXFLAGS	+=	-g
OUTDIRSUFFIX	=	Debug

else

CCFLAGS		+=	-O2
CXXFLAGS	+=	-O2
OUTDIRSUFFIX	=	Release

endif

# TODO: There is absolutely no need for this symbol, gcc defines __linux__, linux and __linux
DEFINES		=	-DLINUX

FREETYPEINC	=	/usr/include/freetype2
CURLINC		=	/usr/include/curl
XML2INC		=	/usr/include/libxml2

FREETYPELIB	=	freetype
CURLLIB		=	curl
XML2LIB		=	xml2
PNGLIB		=	png
JPEGLIB		=	jpeg

# Modify this to where you have installed fmod.
FMODDIR		=	/usr/local
FMODINC		=	$(FMODDIR)/include/fmodex
FMODLIB		=	fmodex
