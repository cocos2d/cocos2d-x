CC      = gcc
CXX     = g++
TARGET	= libcocosdenshion.so
CCFLAGS = -Wall -fPIC
CXXFLAGS = -Wall -fPIC
VISIBILITY = 

COCOS2DX_PATH = ../../cocos2dx

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

INCLUDES += -I$(COCOS2DX_PATH) \
			-I$(COCOS2DX_PATH)/platform/third_party/linux \
			-I$(COCOS2DX_PATH)/platform/third_party/linux/libfreetype2 \
			-I$(COCOS2DX_PATH)/cocoa \
			-I$(COCOS2DX_PATH)/include \
			-I$(COCOS2DX_PATH)/platform \
			-I$(COCOS2DX_PATH)/platform/linux \
			-I$(COCOS2DX_PATH)/kazmath/include \
			-I$(COCOS2DX_PATH)/platform/third_party/linux/libxml2 \
			-I$(COCOS2DX_PATH)/platform/third_party/linux/libjpeg 

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
