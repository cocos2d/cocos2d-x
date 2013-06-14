EXECUTABLE = TestLua

COCOS_ROOT = ../../../..
INCLUDES =  -I../ -I../Classes -I$(COCOS_ROOT)/CocosDenshion/include \
    -I$(COCOS_ROOT)/scripting/lua/lua \
    -I$(COCOS_ROOT)/scripting/lua/tolua \
    -I$(COCOS_ROOT)/scripting/lua/cocos2dx_support

SOURCES = main.cpp ../Classes/AppDelegate.cpp

SHAREDLIBS += -lcocos2d -lcocosdenshion -llua
COCOS_LIBS = $(LIB_DIR)/libcocos2d.so $(LIB_DIR)/libcocosdenshion.so $(LIB_DIR)/liblua.so

include $(COCOS_ROOT)/cocos2dx/proj.linux/cocos2dx.mk

$(TARGET): $(OBJECTS) $(STATICLIBS) $(COCOS_LIBS) $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	cp -R -n ../../../../samples/Cpp/TestCpp/Resources ../../../../samples/Lua/TestLua
	cp -n ../../../../scripting/lua/script/* ../../../../samples/Lua/TestLua/Resources
	$(LOG_LINK)$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@ $(SHAREDLIBS) $(STATICLIBS) $(LIBS)

$(OBJ_DIR)/%.o: ../%.cpp $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_CXX)$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEFINES) $(VISIBILITY) -c $< -o $@

$(OBJ_DIR)/%.o: %.cpp $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_CXX)$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEFINES) $(VISIBILITY) -c $< -o $@
