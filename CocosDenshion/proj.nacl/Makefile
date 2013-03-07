COCOS_ROOT = ../..

INCLUDES = -I../include

SOURCES = ../blackberry/SimpleAudioEngine.cpp

include $(COCOS_ROOT)/cocos2dx/proj.nacl/cocos2dx.mk

TARGET = $(LIB_DIR)/libcocosdenshion.a

all: $(TARGET)

$(TARGET): $(OBJECTS) $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_AR)$(NACL_AR) $(ARFLAGS) $(TARGET) $(OBJECTS)

$(OBJ_DIR)/%.o: ../%.cpp $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_CXX)$(NACL_CXX) -MMD $(CXXFLAGS) $(INCLUDES) $(DEFINES) -c $< -o $@
