EXECUTABLE = SimpleGame

INCLUDES = -I.. -I../Classes

SOURCES = main.cpp \
        ../Classes/AppDelegate.cpp \
        ../Classes/HelloWorldScene.cpp \
        ../Classes/GameOverScene.cpp

COCOS_ROOT = ../../../..
include $(COCOS_ROOT)/cocos/2d/cocos2dx.mk

SHAREDLIBS += -lcocos2d -lcocosdenshion
INCLUDES += -I$(COCOS_ROOT)/cocos/audio/include

$(TARGET): $(OBJECTS) $(STATICLIBS) $(COCOS_LIBS) $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_LINK)$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@ $(SHAREDLIBS) $(STATICLIBS)

$(OBJ_DIR)/%.o: %.cpp $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_CXX)$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEFINES) $(VISIBILITY) -c $< -o $@

$(OBJ_DIR)/%.o: ../%.cpp $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_CXX)$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEFINES) $(VISIBILITY) -c $< -o $@
