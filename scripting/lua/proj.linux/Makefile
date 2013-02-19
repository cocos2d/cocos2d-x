CC      = gcc
CXX     = g++
TARGET	= liblua.so
CCFLAGS = -Wall -fPIC
CXXFLAGS = -Wall -fPIC
VISIBILITY = 

LBITS := $(shell getconf LONG_BIT)
INCLUDES = -I../lua \
           -I../tolua \

DEFINES = -DLINUX

OBJECTS = ../lua/lapi.o \
          ../lua/lauxlib.o \
          ../lua/lbaselib.o \
          ../lua/lcode.o \
          ../lua/ldblib.o \
          ../lua/ldebug.o \
          ../lua/ldo.o \
          ../lua/ldump.o \
          ../lua/lfunc.o \
          ../lua/lgc.o \
          ../lua/linit.o \
          ../lua/liolib.o \
          ../lua/llex.o \
          ../lua/lmathlib.o \
          ../lua/lmem.o \
          ../lua/loadlib.o \
          ../lua/lobject.o \
          ../lua/lopcodes.o \
          ../lua/loslib.o \
          ../lua/lparser.o \
          ../lua/lstate.o \
          ../lua/lstring.o \
          ../lua/lstrlib.o \
          ../lua/ltable.o \
          ../lua/ltablib.o \
          ../lua/ltm.o \
          ../lua/lua.o \
          ../lua/lundump.o \
          ../lua/lvm.o \
          ../lua/lzio.o \
          ../lua/print.o \
          ../tolua/tolua_event.o \
          ../tolua/tolua_is.o \
          ../tolua/tolua_map.o \
          ../tolua/tolua_push.o \
          ../tolua/tolua_to.o

STATICLIBS = 

debug: CCFLAGS += -g3 -O0
debug: CXXFLAGS += -g3 -O0
debug: DEFINES += -DDEBUG
debug: $(TARGET)

release: CCFLAGS += -O3
release: CXXFLAGS += -O3
release: DEFINES += -DNDEBUG
release: $(TARGET)

####### Build rules
$(TARGET): $(OBJECTS) 
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEFINES) $(OBJECTS) -shared -o $(TARGET) $(SHAREDLIBS) $(STATICLIBS)

####### Compile
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEFINES) $(VISIBILITY) -c $< -o $@

%.o: %.c
	$(CC) $(CCFLAGS) $(INCLUDES) $(DEFINES) $(VISIBILITY) -c $< -o $@

clean: 
	rm -f $(OBJECTS) $(TARGET) core
