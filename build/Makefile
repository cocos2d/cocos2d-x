PLATFORM ?= linux

all:

chipmunk:
	$(MAKE) -C ../external/chipmunk/proj.$(PLATFORM)
chipmunk-clean:
	$(MAKE) -C ../external/chipmunk/proj.$(PLATFORM) clean

box2d:
	$(MAKE) -C ../external/Box2D/proj.$(PLATFORM)
box2d-clean:
	$(MAKE) -C ../external/Box2D/proj.$(PLATFORM) clean

cocos2dx: chipmunk
	$(MAKE) -C ../cocos/2d
cocos2dx-clean:
	$(MAKE) -C ../cocos/2d clean

audio: cocos2dx
	$(MAKE) -C ../cocos/audio/proj.$(PLATFORM)
audio-clean:
	$(MAKE) -C ../cocos/audio/proj.$(PLATFORM) clean

gui:
	$(MAKE) -C ../cocos/gui
gui-clean:
	$(MAKE) -C ../cocos/gui clean

network: cocos2dx
	$(MAKE) -C ../cocos/network
network-clean:
	$(MAKE) -C ../cocos/network clean

cocosbuilder:
	$(MAKE) -C ../cocos/editor-support/cocosbuilder
cocosbuilder-clean:
	$(MAKE) -C ../cocos/editor-support/cocosbuilder clean

spine:
	$(MAKE) -C ../cocos/editor-support/spine
spine-clean:
	$(MAKE) -C ../cocos/editor-support/spine clean

cocostudio:
	$(MAKE) -C ../cocos/editor-support/cocostudio
cocostudio-clean:
	$(MAKE) -C ../cocos/editor-support/cocostudio clean

extensions: chipmunk audio  box2d
	$(MAKE) -C ../extensions/proj.$(PLATFORM)
extensions-clean:
	$(MAKE) -C ../extensions/proj.$(PLATFORM) clean

lua: extensions cocosbuilder cocostudio
	$(MAKE) -C ../cocos/scripting/lua/bindings
lua-clean:
	$(MAKE) -C ../cocos/scripting/lua/bindings clean

hellocpp: cocos2dx
	$(MAKE) -C ../samples/Cpp/HelloCpp/proj.$(PLATFORM)
hellocpp-clean:
	$(MAKE) -C ../samples/Cpp/HelloCpp/proj.$(PLATFORM) clean

testcpp: cocos2dx audio extensions cocostudio gui cocosbuilder spine network
	$(MAKE) -C ../samples/Cpp/TestCpp/proj.$(PLATFORM)
testcpp-clean:
	$(MAKE) -C ../samples/Cpp/TestCpp/proj.$(PLATFORM) clean

simplegame: cocos2dx audio
	$(MAKE) -C ../samples/Cpp/SimpleGame/proj.$(PLATFORM)
simplegame-clean:
	$(MAKE) -C ../samples/Cpp/SimpleGame/proj.$(PLATFORM) clean

all: chipmunk audio extensions cocos2dx lua hellocpp testcpp simplegame
clean: cocos2dx-clean box2d-clean chipmunk-clean audio-clean extensions-clean lua-clean hellocpp-clean testcpp-clean simplegame-clean

hellolua: cocos2dx lua
	$(MAKE) -C ../samples/Lua/HelloLua/proj.$(PLATFORM)
hellolua-clean:
	$(MAKE) -C ../samples/Lua/HelloLua/proj.$(PLATFORM) clean

testlua: cocos2dx lua
	$(MAKE) -C ../samples/Lua/TestLua/proj.$(PLATFORM)
testlua-clean:
	$(MAKE) -C ../samples/Lua/TestLua/proj.$(PLATFORM) clean
	
all: hellolua testlua
clean: hellolua-clean testlua-clean

.PHONY: all clean
