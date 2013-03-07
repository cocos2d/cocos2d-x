TARGET = libcocosdenshion.so

INCLUDES += -I.. -I../include

ifeq ($(LBITS),64)
INCLUDES += -I../third_party/fmod/lib64/api/inc
else
INCLUDES += -I../third_party/fmod/api/inc
endif

SOURCES = ../linux/FmodAudioPlayer.cpp \
          ../linux/SimpleAudioEngine.cpp \

COCOS_ROOT = ../..
include $(COCOS_ROOT)/cocos2dx/proj.linux/cocos2dx.mk

TARGET := $(LIB_DIR)/$(TARGET)

all: $(TARGET)

$(TARGET): $(OBJECTS) $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_LINK)$(CXX) $(CXXFLAGS) $(OBJECTS) -shared -o $(TARGET) $(SHAREDLIBS) $(STATICLIBS)

$(OBJ_DIR)/%.o: ../%.cpp $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_CXX)$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEFINES) $(VISIBILITY) -c $< -o $@
