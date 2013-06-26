PLATFORM ?= linux

define MAKE_TARGETS
	+$(MAKE) -C external/chipmunk/proj.$(PLATFORM) $@
	+$(MAKE) -C external/Box2D/proj.$(PLATFORM) $@
	+$(MAKE) -C CocosDenshion/proj.$(PLATFORM) $@
	+$(MAKE) -C extensions/proj.$(PLATFORM) $@
	+$(MAKE) -C cocos2dx/proj.$(PLATFORM) $@
	+$(MAKE) -C scripting/lua/proj.$(PLATFORM) $@
	+$(MAKE) -C samples/Cpp/HelloCpp/proj.$(PLATFORM) $@
	+$(MAKE) -C samples/Cpp/TestCpp/proj.$(PLATFORM) $@
	+$(MAKE) -C samples/Cpp/SimpleGame/proj.$(PLATFORM) $@
endef

# Haven't yet got the lua projects working with emscripten
ifneq ($(PLATFORM),emscripten)
define MAKE_LUA
	+$(MAKE) -C samples/Lua/HelloLua/proj.$(PLATFORM) $@
	+$(MAKE) -C samples/Lua/TestLua/proj.$(PLATFORM) $@
endef
endif

all:
	$(call MAKE_TARGETS,all)
	$(call MAKE_LUA,all)

clean:
	$(call MAKE_TARGETS,clean)
	$(call MAKE_LUA,clean)

.PHONY: all clean
