INCLUDES = -I.. -I../lua -I../xxtea -I../../../extensions -I../../../external/chipmunk/include/chipmunk

SOURCES = ../lua/lapi.c \
          ../lua/lauxlib.c \
          ../lua/lbaselib.c \
          ../lua/lcode.c \
          ../lua/ldblib.c \
          ../lua/ldebug.c \
          ../lua/ldo.c \
          ../lua/ldump.c \
          ../lua/lfunc.c \
          ../lua/lgc.c \
          ../lua/linit.c \
          ../lua/liolib.c \
          ../lua/llex.c \
          ../lua/lmathlib.c \
          ../lua/lmem.c \
          ../lua/loadlib.c \
          ../lua/lobject.c \
          ../lua/lopcodes.c \
          ../lua/loslib.c \
          ../lua/lparser.c \
          ../lua/lstate.c \
          ../lua/lstring.c \
          ../lua/lstrlib.c \
          ../lua/ltable.c \
          ../lua/ltablib.c \
          ../lua/ltm.c \
          ../lua/lundump.c \
          ../lua/lvm.c \
          ../lua/lzio.c \
          ../lua/print.c \
          ../tolua/tolua_event.c \
          ../tolua/tolua_is.c \
          ../tolua/tolua_map.c \
          ../tolua/tolua_push.c \
          ../tolua/tolua_to.c \
          ../xxtea/xxtea.cpp 

COCOS_ROOT = ../../..

include $(COCOS_ROOT)/cocos2dx/proj.nacl/cocos2dx.mk

CCFLAGS = -Wno-uninitialized

TARGET = $(LIB_DIR)/liblua.a
all: $(TARGET)

$(TARGET): $(OBJECTS) $(CORE_MAKEFILE_LIST)
	$(LOG_AR)$(NACL_AR) $(ARFLAGS) $(TARGET) $(OBJECTS)

$(OBJ_DIR)/%.o: ../%.c $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_CC)$(NACL_CC) -MMD $(CCFLAGS) $(INCLUDES) $(DEFINES) $(VISIBILITY) -c $< -o $@
	
$(OBJ_DIR)/%.o: ../%.cpp $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_CXX)$(NACL_CXX) -MMD $(CXXFLAGS) $(INCLUDES) $(DEFINES) -c $< -o $@
