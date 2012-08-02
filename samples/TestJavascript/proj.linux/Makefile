CC      = gcc
CXX     = g++
TARGET	= testjs
CCFLAGS = -Wall -g -O2 
CXXFLAGS = -Wall -g -O2 
VISIBILITY = 

COCOS2DX_PATH = ../../../cocos2dx
JSBINDING_PATH=../../../scripting/javascript/bindings
INCLUDES =  -I../ \
			-I../Classes \
			-I$(JSBINDING_PATH) \
			-I$(JSBINDING_PATH)/../spidermonkey-linux/js-1.8.5/js/src \
			-I../../../CocosDenshion/include \
			-I$(COCOS2DX_PATH) \
			-I$(COCOS2DX_PATH)/cocoa \
			-I$(COCOS2DX_PATH)/include \
			-I$(COCOS2DX_PATH)/platform \
			-I$(COCOS2DX_PATH)/platform/linux \
			-I$(COCOS2DX_PATH)/platform/third_party/linux \
			-I$(COCOS2DX_PATH)/platform/third_party/linux/libfreetype2 \
			-I$(COCOS2DX_PATH)/platform/third_party/linux/glew-1.7.0/glew-1.7.0/include/ \
			-I$(COCOS2DX_PATH)/platform/third_party/linux/libxml2 \
			-I$(COCOS2DX_PATH)/platform/third_party/linux/libjpeg  \
			-I$(COCOS2DX_PATH)/kazmath/include \


DEFINES = -DLINUX

OBJECTS = ./main.o \
        ../Classes/AppDelegate.o \
		$(JSBINDING_PATH)/ScriptingCore.o \
		$(JSBINDING_PATH)/cocos2d_generated.o \
		$(JSBINDING_PATH)/cocos2d_manual_bindings.o \
		$(JSBINDING_PATH)/cocos_denshion_generated.o \
#		../Classes/simple_class.o \
#		../Classes/simple_native_generated.o


LBITS := $(shell getconf LONG_BIT)
ifeq ($(LBITS),64)
STATICLIBS_DIR = ../../../cocos2dx/platform/third_party/linux/libraries/lib64
else
STATICLIBS_DIR = ../../../cocos2dx/platform/third_party/linux/libraries
endif
STATICLIBS =  
STATICLIBS += $(STATICLIBS_DIR)/libtiff.a \
				$(JSBINDING_PATH)/../spidermonkey-linux/js-1.8.5/js/src/libjs_static.a \

ifeq ($(LBITS),64)
SHAREDLIBS_DIR = ../../../CocosDenshion/third_party/fmod/lib64/api/lib
SHAREDLIBS = -L$(SHAREDLIBS_DIR) -lfmodex64
else
SHAREDLIBS_DIR = ../../../CocosDenshion/third_party/fmod/api/lib
SHAREDLIBS = -L$(SHAREDLIBS_DIR) -lfmodex
endif

SHAREDLIBS += -L../../../lib/linux/Debug -lcocos2d -lrt -lz -lcocosdenshion -Wl,-rpath,../../../lib/linux/Debug/ 
SHAREDLIBS += -lglfw
#SHAREDLIBS += -lGLEW
SHAREDLIBS += -Wl,-rpath,$(SHAREDLIBS_DIR)
SHAREDLIBS += -Wl,-rpath,../../../cocos2dx/platform/third_party/linux/glew-1.7.0/glew-1.7.0/lib 
SHAREDLIBS += -L../../../cocos2dx/platform/third_party/linux/glew-1.7.0/glew-1.7.0/lib -lGLEW

#$(shell ../../build-linux.sh $<)
####### Build rules
$(TARGET): $(OBJECTS) 
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEFINES) $(OBJECTS) -o $(TARGET) $(SHAREDLIBS) $(STATICLIBS)
	
####### Compile
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEFINES) $(VISIBILITY) -c $< -o $@

%.o: %.c
	$(CC) $(CCFLAGS) $(INCLUDES) $(DEFINES) $(VISIBILITY) -c $< -o $@
		
clean: 
	rm -f $(OBJECTS) $(TARGET) core
