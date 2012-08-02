CC      = gcc
CXX     = g++
TARGET	= HelloCpp
CCFLAGS = -Wall -g -O2 
CXXFLAGS = -Wall -g -O2 
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
			-I$(COCOS2DX_PATH)/platform/third_party/linux/glew-1.7.0/glew-1.7.0/include/ \
			-I$(COCOS2DX_PATH)/kazmath/include \
			-I$(COCOS2DX_PATH)/platform/third_party/linux/libxml2 \
			-I$(COCOS2DX_PATH)/platform/third_party/linux/libjpeg  \


DEFINES = -DLINUX

OBJECTS = ./main.o \
        ../Classes/AppDelegate.o \
        ../Classes/HelloWorldScene.o 

LBITS := $(shell getconf LONG_BIT)
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
#				$(STATICLIBS_DIR)/libGLEW.a \


SHAREDLIBS = -L../../../lib/linux/Debug -lcocos2d -lrt -lz -lcocosdenshion -Wl,-rpath,../../../lib/linux/Debug/ 
SHAREDLIBS += -lglfw
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
