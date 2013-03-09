CC      = gcc
CXX     = g++
TARGET	= HelloLua
CCFLAGS = -Wall
CXXFLAGS = -Wall
VISIBILITY = 

COCOS2DX_PATH = ../../../cocos2dx
INCLUDES =  -I../ \
			-I../Classes \
			-I$(COCOS2DX_PATH) \
			-I$(COCOS2DX_PATH)/platform/third_party/linux \
			-I$(COCOS2DX_PATH)/platform/third_party/linux/libfreetype2 \
			-I$(COCOS2DX_PATH)/cocoa \
			-I$(COCOS2DX_PATH)/include \
			-I$(COCOS2DX_PATH)/platform \
			-I$(COCOS2DX_PATH)/platform/linux \
			-I$(COCOS2DX_PATH)/kazmath/include \
			-I$(COCOS2DX_PATH)/platform/third_party/linux/libxml2 \
			-I$(COCOS2DX_PATH)/platform/third_party/linux/libjpeg  \
			-I../../../CocosDenshion/include \
			-I../../../scripting/lua/lua \
			-I../../../scripting/lua/tolua \
			-I../../../scripting/lua/cocos2dx_support


DEFINES = -DLINUX

OBJECTS = ./main.o \
        ../Classes/AppDelegate.o

LBITS := $(shell getconf LONG_BIT)
ifeq ($(LBITS),64)
STATICLIBS_DIR = ../../../cocos2dx/platform/third_party/linux/libraries/lib64
else
STATICLIBS_DIR = ../../../cocos2dx/platform/third_party/linux/libraries
endif

STATICLIBS = $(STATICLIBS_DIR)/libfreetype.a \
				$(STATICLIBS_DIR)/libcurl.a \
				$(STATICLIBS_DIR)/libxml2.a \
				$(STATICLIBS_DIR)/libpng.a \
				$(STATICLIBS_DIR)/libjpeg.a \
				$(STATICLIBS_DIR)/libtiff.a \
#				$(STATICLIBS_DIR)/libGLEW.a \
				../../../lib/linux/Debug/libbox2d.a \
				../../../lib/linux/Debug/libchipmunk.a

SHAREDLIBS += -lglfw -lcurl -llua -lGLEW
SHAREDLIBS += -Wl,-rpath,../../../../lib/linux/Debug

ifeq ($(LBITS),64)
SHAREDLIBS += -L../../../CocosDenshion/third_party/fmod/lib64/api/lib -lfmodex64 -Wl,-rpath,../../../../CocosDenshion/third_party/fmod/lib64/api/lib
else
SHAREDLIBS += -L../../../CocosDenshion/third_party/fmod/api/lib -lfmodex -Wl,-rpath,../../../../CocosDenshion/third_party/fmod/api/lib
endif

#$(shell ../../build-linux.sh $<)

BIN_DIR_ROOT=bin
BIN_DIR = $(BIN_DIR_ROOT)

debug: BIN_DIR = $(BIN_DIR_ROOT)/debug
debug: CCFLAGS += -g3 -O0
debug: CXXFLAGS += -g3 -O0
debug: SHAREDLIBS += -L../../../lib/linux/Debug -lcocos2d -lrt -lz -lcocosdenshion
debug: SHAREDLIBS += -Wl,-rpath,../../../../lib/linux/Debug/
debug: DEFINES += -DDEBUG
debug: $(TARGET)

release: BIN_DIR = $(BIN_DIR_ROOT)/release
release: CCFLAGS += -O3
release: CXXFLAGS += -O3
release: SHAREDLIBS += -L../../../lib/linux/Release -lcocos2d -lrt -lz -lcocosdenshion
release: SHAREDLIBS += -Wl,-rpath,../../../../lib/linux/Release/
release: DEFINES += -DNDEBUG
release: $(TARGET)

####### Build rules
$(TARGET): $(OBJECTS) 
	mkdir -p $(BIN_DIR)
	cp -R -n ../../../samples/Cpp/TestCpp/Resources ../../../samples/Lua/HelloLua 
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEFINES) $(OBJECTS) -o $(BIN_DIR)/$(TARGET) $(SHAREDLIBS) $(STATICLIBS)

####### Compile
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEFINES) $(VISIBILITY) -c $< -o $@

%.o: %.c
	$(CC) $(CCFLAGS) $(INCLUDES) $(DEFINES) $(VISIBILITY) -c $< -o $@

clean: 
	rm -f $(OBJECTS) $(TARGET) core
