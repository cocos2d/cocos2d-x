PLATFORM = linux

define MAKE_TARGET
	+$(MAKE) -C external/chipmunk/proj.$(PLATFORM) $@
	+$(MAKE) -C external/Box2D/proj.$(PLATFORM) $@
	+$(MAKE) -C CocosDenshion/proj.$(PLATFORM) $@
	+$(MAKE) -C extensions/proj.$(PLATFORM) $@
	+$(MAKE) -C cocos2dx/proj.$(PLATFORM) $@
	+$(MAKE) -C scripting/lua/proj.$(PLATFORM) $@
	+$(MAKE) -C samples/Cpp/HelloCpp/proj.$(PLATFORM) $@
	+$(MAKE) -C samples/Cpp/TestCpp/proj.$(PLATFORM) $@
	+$(MAKE) -C samples/Cpp/SimpleGame/proj.$(PLATFORM) $@
	+$(MAKE) -C samples/Lua/HelloLua/proj.$(PLATFORM) $@
	+$(MAKE) -C samples/Lua/TestLua/proj.$(PLATFORM) $@
endef

define EMSCRIPTEN_MAKE_TARGET
	+$(MAKE) -C external/chipmunk/proj.emscripten $1
	+$(MAKE) -C external/Box2D/proj.emscripten $1
	+$(MAKE) -C CocosDenshion/proj.emscripten $1
	+$(MAKE) -C extensions/proj.emscripten $1
	+$(MAKE) -C cocos2dx/proj.emscripten $1
	+$(MAKE) -C scripting/lua/proj.emscripten $1
	+$(MAKE) -C samples/Cpp/HelloCpp/proj.emscripten $1
	+$(MAKE) -C samples/Cpp/TestCpp/proj.emscripten $1
	+$(MAKE) -C samples/Cpp/SimpleGame/proj.emscripten $1
endef

all:
	$(call MAKE_TARGET,all)

clean:
	$(call MAKE_TARGET,clean)
	$(call EMSCRIPTEN_MAKE_TARGET,clean)

emscripten:
	$(call EMSCRIPTEN_MAKE_TARGET,all)

.PHONY: all clean emscripten
