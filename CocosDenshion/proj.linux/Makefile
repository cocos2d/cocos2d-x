CC      = gcc
CXX     = g++
TARGET	= libcocosdenshion.so
CCFLAGS = -Wall -fPIC
CXXFLAGS = -Wall -fPIC
VISIBILITY = 

LBITS := $(shell getconf LONG_BIT)
ifeq ($(LBITS),64)
INCLUDES = -I.. \
		-I../include \
		-I../third_party/fmod/lib64/api/inc 
else
INCLUDES = -I.. \
		-I../include \
		-I../third_party/fmod/api/inc 
endif


DEFINES = -DLINUX

OBJECTS =   ../linux/FmodAudioPlayer.o \
            ../linux/SimpleAudioEngine.o \

STATICLIBS = 

ifeq ($(LBITS),64)
SHAREDLIBS_DIR = ../third_party/fmod/lib64/api/lib
SHAREDLIBS = -L$(SHAREDLIBS_DIR) -lfmodex64
else
SHAREDLIBS_DIR = ../third_party/fmod/api/lib
SHAREDLIBS = -L$(SHAREDLIBS_DIR) -lfmodex
endif

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
