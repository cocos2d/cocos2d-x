TARGET = libcocosdenshion.so

INCLUDES += -I.. -I../include

##Using OpenAL
ifeq ($(OPENAL),1)
SOURCES = ../linux/SimpleAudioEngineOpenAL.cpp 
SHAREDLIBS += -lopenal -lalut

ifneq ($(NOVORBIS),1)
SHAREDLIBS += -logg -lvorbis -lvorbisfile
else
DEFINES += -DDISABLE_VORBIS
endif

##Using FMOD
else
SOURCES = \
  ../linux/SimpleAudioEngineFMOD.cpp \
  ../linux/FmodAudioPlayer.cpp   
  
ifeq ($(LBITS),64)
INCLUDES += -I../third_party/fmod/lib64/api/inc
else
INCLUDES += -I../third_party/fmod/api/inc
endif
    
endif

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
