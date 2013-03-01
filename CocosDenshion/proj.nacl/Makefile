COCOS_ROOT = ../..

INCLUDES = -I../include

SOURCES = ../blackberry/SimpleAudioEngine.cpp

include $(COCOS_ROOT)/cocos2dx/proj.nacl/cocos2dx.mk

TARGET = $(LIB_DIR)/libcocosdenshion.a

####### Build rules
$(TARGET): $(OBJECTS)
	@mkdir -p $(@D)
	$(NACL_AR) $(ARFLAGS) $(TARGET) $(OBJECTS)

####### Compile
$(OBJ_DIR)/%.o: ../%.cpp
	@mkdir -p $(@D)
	$(NACL_CXX) -MMD $(CXXFLAGS) $(INCLUDES) $(DEFINES) -c $< -o $@

$(OBJ_DIR)/%.o: ../%.c
	@mkdir -p $(@D)
	$(NACL_CC) -MMD $(CCFLAGS) $(INCLUDES) $(DEFINES) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET) $(DEPS) core

-include $(DEPS)

.PHONY: clean all
