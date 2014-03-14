import os

SAMPLES_DIRS = ["Cpp/HelloCpp", "Cpp/SimpleGame", "Cpp/TestCpp", "Javascript/MoonWarriors", "Javascript/TestJavascript", "Lua/HelloLua", "Lua/TestLua"]
SAMPLEE_NAMES = ["HelloCpp", "SimpleGame", "TestCpp", "MoonWarriors", "TestJavascript", "HelloLua", "TestLua"]
for i, item in enumerate(SAMPLES_DIRS):
    cmd = "xcodebuild -project samples/" + item + "/proj.ios/" + SAMPLEE_NAMES[i] + ".xcodeproj -scheme " + SAMPLEE_NAMES[i] + " test"
    ret = os.system(cmd)
    if (ret != 0):
      break
