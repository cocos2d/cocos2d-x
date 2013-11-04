EXECUTABLE = TestLua

COCOS_ROOT = ../../../..
INCLUDES =  -I../Classes \
     -I$(COCOS_ROOT)/audio/include \
     -I$(COCOS_ROOT)/cocos/scripting/lua/bindings \
     -I$(COCOS_ROOT)/external/lua/lua \
     -I$(COCOS_ROOT)/external/lua/tolua \
     -I$(COCOS_ROOT)/extensions

SOURCES = main.cpp \
../Classes/AppDelegate.cpp \
../Classes/lua_assetsmanager_test_sample.cpp

SHAREDLIBS += -lcocos2d -lcocosdenshion -llua

include $(COCOS_ROOT)/cocos/2d/cocos2dx.mk

$(TARGET): $(OBJECTS) $(STATICLIBS) $(COCOS_LIBS) $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	cp -R -n ../../../../samples/Cpp/TestCpp/Resources ../../../../samples/Lua/TestLua
	cp -n ../../../../cocos/scripting/lua/script/* ../../../../samples/Lua/TestLua/Resources
	$(LOG_LINK)$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@ $(SHAREDLIBS) $(STATICLIBS) $(LIBS)

$(OBJ_DIR)/%.o: ../%.cpp $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_CXX)$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEFINES) $(VISIBILITY) -c $< -o $@

$(OBJ_DIR)/%.o: %.cpp $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_CXX)$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEFINES) $(VISIBILITY) -c $< -o $@
