PLATFORM ?= linux

all:

chipmunk:
	$(MAKE) -C external/chipmunk/proj.$(PLATFORM)
chipmunk-clean:
	$(MAKE) -C external/chipmunk/proj.$(PLATFORM) clean

box2d:
	$(MAKE) -C external/Box2D/proj.$(PLATFORM)
box2d-clean:
	$(MAKE) -C external/Box2D/proj.$(PLATFORM) clean

libextensions: cocosdenshion chipmunk box2d
	$(MAKE) -C extensions/proj.$(PLATFORM)
libextensions-clean:
	$(MAKE) -C extensions/proj.$(PLATFORM) clean

libcocos2dx: libextensions
	$(MAKE) -C cocos2dx/proj.$(PLATFORM)
libcocos2dx-clean:
	$(MAKE) -C cocos2dx/proj.$(PLATFORM) clean

cocosdenshion: libcocos2dx
	$(MAKE) -C CocosDenshion/proj.$(PLATFORM)
cocosdenshion-clean:
	$(MAKE) -C CocosDenshion/proj.$(PLATFORM) clean

lua: libextensions
	$(MAKE) -C scripting/lua/proj.$(PLATFORM)
lua-clean:
	$(MAKE) -C scripting/lua/proj.$(PLATFORM) clean

hellocpp: libcocos2dx
	$(MAKE) -C samples/Cpp/HelloCpp/proj.$(PLATFORM)
hellocpp-clean:
	$(MAKE) -C samples/Cpp/HelloCpp/proj.$(PLATFORM) clean

testcpp: libcocos2dx libextensions
	$(MAKE) -C samples/Cpp/TestCpp/proj.$(PLATFORM)
testcpp-clean:
	$(MAKE) -C samples/Cpp/TestCpp/proj.$(PLATFORM) clean

simplegame: libcocos2dx
	$(MAKE) -C samples/Cpp/SimpleGame/proj.$(PLATFORM)
simplegame-clean:
	$(MAKE) -C samples/Cpp/SimpleGame/proj.$(PLATFORM) clean

all: box2d cocosdenshion libextensions libcocos2dx lua hellocpp testcpp simplegame
clean: libcocos2dx-clean box2d-clean chipmunk-clean cocosdenshion-clean libextensions-clean lua-clean hellocpp-clean testcpp-clean simplegame-clean

# Haven't yet got the lua projects working with emscripten
ifneq ($(PLATFORM),emscripten)

hellolua: libcocos2dx lua
	$(MAKE) -C samples/Lua/HelloLua/proj.$(PLATFORM)
hellolua-clean:
	$(MAKE) -C samples/Lua/HelloLua/proj.$(PLATFORM) clean

testlua: libcocos2dx lua
	$(MAKE) -C samples/Lua/TestLua/proj.$(PLATFORM)
testlua-clean:
	$(MAKE) -C samples/Lua/TestLua/proj.$(PLATFORM) clean
	
all: hellolua testlua
clean: hellolua-clean testlua-clean
endif

.PHONY: all clean
