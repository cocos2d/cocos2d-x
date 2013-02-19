CC      = gcc
CXX     = g++
TARGET	= HelloCpp
CCFLAGS = -Wall
CXXFLAGS = -Wall
VISIBILITY = 
LIBS = 

COCOS2DX_PATH = ../../../cocos2dx
INCLUDES =  -I../ \
			-I../../ \
			-I../Classes \
			-I$(COCOS2DX_PATH) \
			-I$(COCOS2DX_PATH)/platform/third_party/linux/libfreetype2 \
			-I$(COCOS2DX_PATH)/cocoa \
			-I$(COCOS2DX_PATH)/include \
			-I$(COCOS2DX_PATH)/kazmath/include \
			-I$(COCOS2DX_PATH)/platform \
			-I$(COCOS2DX_PATH)/platform/linux \
			-I$(COCOS2DX_PATH)/platform/third_party/linux/libxml2 \
			-I$(COCOS2DX_PATH)/platform/third_party/linux/libjpeg  \
			-I../../../CocosDenshion/include \
			-I../../../extensions/ \
			-I../../../external/ \
			-I../../../external/chipmunk/include/chipmunk \


LBITS := $(shell getconf LONG_BIT)
ifeq ($(LBITS),64)
INCLUDES += -I$(COCOS2DX_PATH)/platform/third_party/linux/include64
else
INCLUDES += -I$(COCOS2DX_PATH)/platform/third_party/linux
endif

DEFINES = -DLINUX

OBJECTS = ../Classes/AppDelegate.o \
		  ../Classes/HelloWorldScene.o \
		  ./main.o 

ifeq ($(LBITS),64)
STATICLIBS_DIR = ../../../cocos2dx/platform/third_party/linux/libraries/lib64
else
STATICLIBS_DIR = ../../../cocos2dx/platform/third_party/linux/libraries
endif
STATICLIBS = 
STATICLIBS = $(STATICLIBS_DIR)/libfreetype.a \
				$(STATICLIBS_DIR)/libcurl.a \
				$(STATICLIBS_DIR)/libxml2.a \
				$(STATICLIBS_DIR)/libpng.a \
				$(STATICLIBS_DIR)/libjpeg.a \
				$(STATICLIBS_DIR)/libtiff.a \
				../../../lib/linux/Debug/libextension.a \
				../../../lib/linux/Debug/libbox2d.a \
				../../../lib/linux/Debug/libchipmunk.a 

SHAREDLIBS = 
ifeq ($(LBITS),64)
SHAREDLIBS_DIR = ../../../CocosDenshion/third_party/fmod/lib64/api/lib
SHAREDLIBS = -L$(SHAREDLIBS_DIR) -lfmodex64
else
SHAREDLIBS_DIR = ../../../CocosDenshion/third_party/fmod/api/lib
SHAREDLIBS = -L$(SHAREDLIBS_DIR) -lfmodex
endif

SHAREDLIBS += -Wl,-rpath,../../$(SHAREDLIBS_DIR)
SHAREDLIBS += -lglfw -lGLEW -lcurl

BIN_DIR_ROOT=bin
BIN_DIR = BIN_DIR_ROOT

debug: SHAREDLIBS += -L../../../lib/linux/Debug -lcocos2d -lrt -lz -lcocosdenshion -Wl,-rpath,../../../../../lib/linux/Debug
debug: CCFLAGS += -g3 -O0
debug: CXXFLAGS += -g3 -O0
debug: DEFINES += -DDEBUG -DCC_ENABLE_CHIPMUNK_INTEGRATION=1 -DCOCOS2D_DEBUG=1
debug: BIN_DIR = $(BIN_DIR_ROOT)/debug
debug: $(TARGET)

release: SHAREDLIBS += -L../../../lib/linux/Release -lcocos2d -lrt -lz -lcocosdenshion -Wl,-rpath,../../../../../lib/linux/Release
release: CCFLAGS += -O3
release: CXXFLAGS += -O3
release: DEFINES += -DNDEBUG -DCC_ENABLE_CHIPMUNK_INTEGRATION=1
release: BIN_DIR = $(BIN_DIR_ROOT)/release
release: $(TARGET)

####### Build rules
$(TARGET): $(OBJECTS)
	mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEFINES) $(OBJECTS) -o $(BIN_DIR)/$(TARGET) $(SHAREDLIBS) $(STATICLIBS) $(LIBS)


####### Compile
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEFINES) $(VISIBILITY) -c $< -o $@

%.o: %.c
	$(CC) $(CCFLAGS) $(INCLUDES) $(DEFINES) $(VISIBILITY) -c $< -o $@


clean: 
	rm -f $(OBJECTS) $(TARGET) core
