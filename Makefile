PLATFORM ?= linux

MAKE_TARGET =	external/chipmunk/proj.$(PLATFORM)\
external/Box2D/proj.$(PLATFORM)\
CocosDenshion/proj.$(PLATFORM)\
extensions/proj.$(PLATFORM)\
cocos2dx/proj.$(PLATFORM)\
scripting/lua/proj.$(PLATFORM)\
samples/Cpp/HelloCpp/proj.$(PLATFORM)\
samples/Cpp/TestCpp/proj.$(PLATFORM)\
samples/Cpp/SimpleGame/proj.$(PLATFORM)\
samples/Lua/HelloLua/proj.$(PLATFORM)\
samples/Lua/TestLua/proj.$(PLATFORM)

COMPILE = @for target in $(MAKE_TARGET); do if [ -d $$target ]; then $(MAKE) -C $$target $@; fi; done;

all:
	+$(COMPILE)

clean:
	+$(COMPILE)

.PHONY: all clean
