# Imports the monkeyrunner modules used by this program
import sys
import subprocess
import random
import os
from com.android.monkeyrunner import MonkeyRunner as mr
from com.android.monkeyrunner import MonkeyDevice as md
from com.android.monkeyrunner import MonkeyImage as  mi

#Define test functions.
def common_test(a,b,c):
    for i in range(a,b):
        mr.sleep(c)
        device.touch(s_width/8*5,s_height/16*15,'DOWN_AND_UP')

def random_click(a,b,c):
    for i in range(a,b):
        touch_x = random.randint(0,s_width/20*19)
        touch_y = random.randint(0,s_height)
        device.touch(touch_x,touch_y,'DOWN_AND_UP')
        mr.sleep(c)

def random_drag(a,b,c):
    for i in range(a,b):
        drag_x = random.randint(0,s_width/20*18)
        drag_y = random.randint(0,s_height)
        drop_x = random.randint(0,s_width/20*18)
        drop_y = random.randint(0,s_height)
        device.drag((drag_x,drag_y),(drop_x,drop_y))

def check_activity(a):
    print "get running activities..."
    subprocess.call("adb shell ps > running_activities.txt",shell=True)
    #subprocess.call("adb pull running_activities.txt",shell=True)
    
    f1 = open('running_activities.txt')
    while True:
        line = f1.readline()
        if not line.find('org.cocos2dx.testcpp') == -1:
            break;
        if len(line) == 0:
            str = "TestCpp wasn't running,maybe it has crashes,please checkout:"
            f2 = file('monkeyrunner_Error.log','w')
            print "get logcat information..."
            f2.write(str)
            f2.write(a)
            #subprocess.call("adb shell logcat | $ANDROID_NDK/ndk-stack -sym $ANDROID_HOME/tools/obj/local/armeabi > monkeyrunner_Error.log",shell=True);
            f2.close()
            sys.exit(1)
    print "subprocess has finished!"
    f1.close()

# Connects to the current device, returning a MonkeyDevice object
device = mr.waitForConnection()
if not device:
    print >> sys.stderr,"fail"
    check_activity("is there a device connect to the testing machine.")
    sys.exit(1)
else:
    print "Start......"

# Installs the Android package. Notice that this method returns a boolean, so you can test
# to see if the installation worked.
if device.installPackage(sys.argv[1]):
    print "Install success!"
else:
    print "Install failed,please make sure you have put apk in the right places"
    check_activity("you have put apk in the right place")
    sys.exit(1)

# sets a variable with the package's internal name
package = 'org.cocos2dx.testcpp'
print "Package name: "+ package

# sets a variable with the name of an Activity in the package
activity = 'org.cocos2dx.testcpp.TestCpp'
print "Activity name: " + activity

# sets the name of the component to start
runComponent = package + '/' + activity

# Runs the component
device.startActivity(component=runComponent)
print "Running activity......"

#Set Screen's Length and Width
s_width = 800
s_height = 480

#Set boolean variable of Acticity_IsRunning
Acticity_IsRunning = 1

#----------------ActionsTest----------------
print "Run ActionsTest"
mr.sleep(2.0)
device.touch(s_width/2,s_height/48*5,'DOWN_AND_UP')
#Last Test
#device.touch(s_width/8*3,s_height/16*15,'DOWN_AND_UP')
common_test(1,28,1.0)
common_test(1,3,3.0)
common_test(1,6,1.0)
mr.sleep(1.0)
#Next Test
#device.touch(s_width/8*5,s_height/16*15,'DOWN_AND_UP')
print "ActionsTest finished!"
#MainMenu
device.touch(s_width/40*39,s_height/96*91,'DOWN_AND_UP')
check_activity("ActionsTest")

#----------------TransitionsTest----------------
print "Run TransitionsTest"
mr.sleep(1.0)
device.touch(s_width/2,s_height/6,'DOWN_AND_UP')
common_test(1,27,1.0)
mr.sleep(1.0)
print "TransitionsTest finished!"
#MainMenu
device.touch(s_width/40*39,s_height/96*91,'DOWN_AND_UP')
check_activity("TransitionsTest")

#----------------ActionsProgressTest----------------
print "Run ActionsProgressTest"
mr.sleep(1.0)
device.touch(s_width/2,s_height/48*11,'DOWN_AND_UP')
common_test(1,8,2.0)
mr.sleep(1.0)
print "ActionsProgressTest finished!"
#MainMenu
device.touch(s_width/40*39,s_height/96*91,'DOWN_AND_UP')
check_activity("ActionsProgressTest")

#----------------EffectsTest----------------
mr.sleep(1.0)
print "Run EffectsTest"
device.touch(s_width/2,s_height/3,'DOWN_AND_UP')
common_test(1,22,3.0)
mr.sleep(1.0)
print "EffectsTest finished!"
#MainMenu
device.touch(s_width/40*39,s_height/96*91,'DOWN_AND_UP')
check_activity("EffectsTest")

#----------------ClickAndMoveTest----------------
print "Run ClickAndMoveTest"
mr.sleep(5.0)
device.touch(s_width/2,s_height/12*5,'DOWN_AND_UP')
mr.sleep(1.0)
random_click(1,11,2.0)
mr.sleep(1.0)
random_click(1,101,0.0)
mr.sleep(1.0)
print "ClickAndMoveTest finished!"
#MainMenu
device.touch(s_width/40*39,s_height/96*91,'DOWN_AND_UP')
check_activity("ClickAndMoveTest")

#----------------RotateWorldTest----------------
print "Run RotateWorldTest"
mr.sleep(1.0)
device.touch(s_width/2,s_height/2,'DOWN_AND_UP')
mr.sleep(5.0)
print "RotateWorldTest finished!"
mr.sleep(3.0)
#MainMenu
device.touch(s_width/40*39,s_height/96*91,'DOWN_AND_UP')
check_activity("RotateWorldTest")

#----------------ParticleTest----------------
print "Run ParticleTest"
mr.sleep(1.0)
device.touch(s_width/2,s_height/12*7,'DOWN_AND_UP')
common_test(1,43,2.0)
print "ParticleTest finished!"
mr.sleep(2.0)
#MainMenu
device.touch(s_width/40*39,s_height/96*91,'DOWN_AND_UP')
check_activity("ParticleTest")

#----------------ActionsEaseTest----------------
print "Run ActionsEaseTest"
mr.sleep(1.0)
device.touch(s_width/2,s_height/3*2,'DOWN_AND_UP')
mr.sleep(2.0)
common_test(1,14,2.0)
print "ActionsEaseTest finished!"
mr.sleep(1.0)
#MainMenu
device.touch(s_width/40*39,s_height/96*91,'DOWN_AND_UP')
check_activity("ActionsEaseTest")

#----------------MotionStreakTest----------------
print "Run MontionStreakTest"
mr.sleep(1.0)
device.touch(s_width/2,s_height/4*3,'DOWN_AND_UP')
mr.sleep(1.0)
#Next Test
device.touch(s_width/8*5,s_height/16*15,'DOWN_AND_UP')
random_drag(1,11,0.5)
mr.sleep(1.0)
device.touch(s_width/2,s_height/4*3,'DOWN_AND_UP')
mr.sleep(1.0)
random_drag(1,11,0.5)
print "MontionStreakTest finished!"
mr.sleep(1.0)
#MainMenu
device.touch(s_width/40*39,s_height/96*91,'DOWN_AND_UP')
check_activity("MontionStreakTest")

#----------------DrawPrimitivesTest----------------
print "Run DrawprimitivesTest"
mr.sleep(1.0)
device.touch(s_width/2,s_height/6*5,'DOWN_AND_UP')
mr.sleep(1.0)
print "DrawPrimitivesTest finished!"
#MainMenu
device.touch(s_width/40*39,s_height/96*91,'DOWN_AND_UP')
check_activity("DrawPrimitivesTest")

#----------------NodeTest----------------
print "Run NodeTest"
mr.sleep(1.0)
device.touch(s_width/2,s_height/12*11,'DOWN_AND_UP')
mr.sleep(1.0)
common_test(1,14,1.0)
print "NodeTest finished!"
mr.sleep(3.0)
#MainMenu
device.touch(s_width/40*39,s_height/96*91,'DOWN_AND_UP')
check_activity("NodeTest")
mr.sleep(1.0)
device.drag((s_width/4*3,s_height/16*15),(s_width/4*3,0))

#----------------TouchesTest----------------
print "Run TouchesTest"
mr.sleep(1.0)
device.touch(s_width/2,s_height/12,'DOWN_AND_UP')
print "TouchesTest finished!"
mr.sleep(1.0)
#MainMenu
device.touch(s_width/40*39,s_height/96*91,'DOWN_AND_UP')
check_activity("TouchesTest")

#----------------MenuTest----------------
print "Run MenuTest"
mr.sleep(1.0)
device.touch(s_width/2,s_height/6,'DOWN_AND_UP')
mr.sleep(1.0)
#Atlas Sprite
device.touch(s_width/2,s_height/48*13,'DOWN_AND_UP')
mr.sleep(1.0)
#Play
device.touch(s_width/8*3,s_height/24*11,'DOWN_AND_UP')
mr.sleep(1.0)
#items
device.touch(s_width/2,s_height/24*11,'DOWN_AND_UP')
device.touch(s_width/2,s_height/24*11,'DOWN_AND_UP')
mr.sleep(1.0)
#Configuration
device.touch(400,260,'DOWN_AND_UP')
mr.sleep(1.0)
print "MenuTest finished!"
mr.sleep(1.0)
#MainMenu
device.touch(s_width/40*39,s_height/96*91,'DOWN_AND_UP')
check_activity("MenuTest")

#----------------ActionManagerTest----------------
print "Run ActionManagerTest"
mr.sleep(1.0)
device.touch(s_width/2,s_height/48*11,'DOWN_AND_UP')
common_test(1,5,3.0)
print "ActionManagerTest finished!"
mr.sleep(1.0)
#MainMenu
device.touch(s_width/40*39,s_height/96*91,'DOWN_AND_UP')
check_activity("ActionManagerTest")

#----------------LayerTest----------------
print "Run LayerTest"
mr.sleep(1.0)
device.touch(s_width/2,s_height/3,'DOWN_AND_UP')
random_drag(1,11,0.5)
mr.sleep(1.0)
#Next Test
device.touch(s_width/8*5,s_height/16*15,'DOWN_AND_UP')
mr.sleep(2.0)
#Next Test
device.touch(s_width/8*5,s_height/16*15,'DOWN_AND_UP')
mr.sleep(2.0)
#Next Test
device.touch(s_width/8*5,s_height/16*15,'DOWN_AND_UP')
random_drag(1,11,0.5)
print "LayerTest finished!"
#MainMenu
device.touch(s_width/40*39,s_height/96*91,'DOWN_AND_UP')
check_activity("LayerTest")

#----------------SceneTest----------------
print "Run SceneTest"
mr.sleep(1.0)
device.touch(s_width/2,s_height/12*5,'DOWN_AND_UP')
mr.sleep(1.0)
device.touch(s_width/2,s_height/12*5,'DOWN_AND_UP')
mr.sleep(1.0)
device.touch(s_width/2,s_height/12*5,'DOWN_AND_UP')
mr.sleep(1.0)
device.touch(s_width/2,s_height/12*5,'DOWN_AND_UP')
mr.sleep(1.0)
device.touch(s_width/2,s_height/12*7,'DOWN_AND_UP')
mr.sleep(1.0)
device.touch(s_width/2,s_height/2,'DOWN_AND_UP')
mr.sleep(1.5)
device.touch(s_width/2,s_height/2,'DOWN_AND_UP')
mr.sleep(1.5)
device.touch(s_width/2,s_height/2,'DOWN_AND_UP')
print "SceneTest finished!"
mr.sleep(1.0)
#MainMenu
device.touch(s_width/40*39,s_height/96*91,'DOWN_AND_UP')
check_activity("SceneTest")

#----------------ParallaxTest----------------
print "Run ParallaxTest"
mr.sleep(1.0)
device.touch(s_width/2,s_height/2,'DOWN_AND_UP')
mr.sleep(5.0)
#Next Test
device.touch(s_width/8*5,s_height/16*15,'DOWN_AND_UP')
random_drag(1,11,0.5)
print "ParallaxTest finished!"
mr.sleep(1.0)
#MainMenu
device.touch(s_width/40*39,s_height/96*91,'DOWN_AND_UP')
check_activity("ParallaxTest")

#----------------TileMapTest----------------
print "Run TileMapTest"
mr.sleep(1.0)
device.touch(s_width/2,s_height/12*7,'DOWN_AND_UP')
mr.sleep(2.0)
for TileMap_i in range(1,20):
    random_drag(1,5,2.0)
    #Next Test
    device.touch(s_width/8*5,s_height/16*15,'DOWN_AND_UP')
    
mr.sleep(2.0)
print "TileMapTest finished!"
mr.sleep(1.0)
#MainMenu
device.touch(s_width/40*39,s_height/96*91,'DOWN_AND_UP')
check_activity("TileMapTest")

#----------------IntervalTest----------------
print "Run IntervalTest"
mr.sleep(1.0)
device.touch(s_width/2,s_height/3*2,'DOWN_AND_UP')
mr.sleep(3.0)
device.touch(s_width/2,s_height/12,'DOWN_AND_UP')
mr.sleep(1.0)
device.touch(s_width/2,s_height/12,'DOWN_AND_UP')
print "IntervalTest finished!"
mr.sleep(1.0)
#MainMenu
device.touch(s_width/40*39,s_height/96*91,'DOWN_AND_UP')
check_activity("IntervalTest")

#----------------ChipmunkAccelTouchTest----------------
print "Run ChipmunkAccelTouchTest"
mr.sleep(1.0)
device.touch(s_width/2,s_height/4*3,'DOWN_AND_UP')
random_click(1,21,0.1)
print "ChipmunkAccelTouchTest finished!"
mr.sleep(2.0)
#MainMenu
device.touch(s_width/40*39,s_height/96*91,'DOWN_AND_UP')
check_activity("ChipmunkAccelTouchTest")

#----------------LabelTest----------------
print "Run LabelTest"
mr.sleep(1.0)
device.touch(s_width/2,s_height/6*5,'DOWN_AND_UP')
mr.sleep(3.0)
common_test(1,26,0.5)
mr.sleep(1.0)
print "LableTest finished!"
#MainMenu
device.touch(s_width/40*39,s_height/96*91,'DOWN_AND_UP')
check_activity("LabelTest")

#----------------TestInputTest----------------
print "Run TestInputTest"
mr.sleep(1.0)
device.touch(s_width/2,s_height/12*11,'DOWN_AND_UP')
print "TestInputTest finished!"
mr.sleep(1.0)
#MainMenu
device.touch(s_width/40*39,s_height/96*91,'DOWN_AND_UP')
check_activity("TestInputTest")
mr.sleep(1.0)
device.drag((s_width/4*3,s_height/16*15),(s_width/4*3,0))

#----------------SpriteTest----------------
print "Run SpriteTest"
mr.sleep(1.0)
device.touch(s_width/2,s_height/16,'DOWN_AND_UP')
mr.sleep(1.0)
random_click(1,11,0.1)
mr.sleep(2.0)
#Next Test
device.touch(s_width/8*5,s_height/16*15,'DOWN_AND_UP')
random_click(1,11,0.1)
mr.sleep(1.0)
#Next Test
device.touch(s_width/8*5,s_height/16*15,'DOWN_AND_UP')
mr.sleep(1.0)
common_test(1,109,0.5)
print "SpriteTest finished!"
mr.sleep(1.0)
#MainMenu
device.touch(s_width/40*39,s_height/96*91,'DOWN_AND_UP')
check_activity("SpriteTest")

#----------------SchdulerTest----------------
print "Run SchdulerTest"
mr.sleep(2.0)
device.touch(s_width/2,s_height/48*7,'DOWN_AND_UP')
mr.sleep(1.0)
#Next Test
device.touch(s_width/8*5,s_height/16*15,'DOWN_AND_UP')
#Scheduler timeScale Test
mr.sleep(1.0)
device.drag((s_width/16*9,s_height/8*5),(s_width/16*7,s_height/8*5))
mr.sleep(1.0)
#Next Test
device.touch(s_width/8*5,s_height/16*15,'DOWN_AND_UP')
#Two custom schedulers
mr.sleep(1.0)
device.drag((s_width/16*5,s_height/24),(s_width/16*3,s_height/24))
mr.sleep(1.0)
common_test(1,11,1)
print "SchdulerTest finished!"
mr.sleep(1.0)
#MainMenu
device.touch(s_width/40*39,s_height/96*91,'DOWN_AND_UP')
check_activity("SchdulerTest")

#----------------RenderTextureTest----------------
print "Run RenderTextureTest"
mr.sleep(1.0)
device.touch(s_width/2,s_height/48*11,'DOWN_AND_UP')
mr.sleep(1.0)
random_drag(1,11,0.5)
mr.sleep(1.0)
device.touch(s_width/8*7,s_height/24,'DOWN_AND_UP')
mr.sleep(1.0)
#Next Test
device.touch(s_width/8*5,s_height/16*15,'DOWN_AND_UP')
mr.sleep(1.0)
device.touch(s_width/8*5,s_height/16*15,'DOWN_AND_UP')
mr.sleep(1.0)
#Testing Z Buffer in Render Texture
random_click(1,11,0.1)
mr.sleep(1.0)
#Next Test
device.touch(s_width/8*5,s_height/16*15,'DOWN_AND_UP')
print "RenderTextureTest finished!"
mr.sleep(1.0)
#MainMenu
device.touch(s_width/40*39,s_height/96*91,'DOWN_AND_UP')
check_activity("RenderTextureTest")

#----------------Testure2DTest----------------
print "Run Testure2DTest"
mr.sleep(1.0)
device.touch(s_width/2,s_height/16*5,'DOWN_AND_UP')
common_test(1,36,0.5)
print "Testure2DTest finished!"
mr.sleep(1.0)
#MainMenu
device.touch(s_width/40*39,s_height/96*91,'DOWN_AND_UP')
check_activity("Testure2DTest")

#----------------Box2dTest----------------
print "Run Box2dTest"
mr.sleep(1.0)
device.touch(s_width/2,s_height/48*19,'DOWN_AND_UP')
random_click(1,31,0.1)
print "Box2dTest finished!"
mr.sleep(1.0)
#MainMenu
device.touch(s_width/40*39,s_height/96*91,'DOWN_AND_UP')
check_activity("Box2dTest")

#----------------Box2dTestBed----------------
print "Run Box2dTestBed"
mr.sleep(1.0)
device.touch(s_width/2,s_height/48*23,'DOWN_AND_UP')
common_test(1,36,2.0)
print "Box2dTestBed finished!"
mr.sleep(1.0)
#MainMenu
device.touch(s_width/40*39,s_height/96*91,'DOWN_AND_UP')
check_activity("Box2dTestBed")

#----------------EffectAdvancedTest----------------
print "Run EffectAdvancedTest"
mr.sleep(1.0)
device.touch(s_width/2,s_height/16*9,'DOWN_AND_UP')
common_test(1,6,1.0)
print "EffectAdvancedTest finished!"
mr.sleep(1.0)
#MainMenu
device.touch(s_width/40*39,s_height/96*91,'DOWN_AND_UP')
check_activity("EffectAdvancedTest")

#----------------Accelerometer----------------
print "Run Accelerometer"
mr.sleep(5.0)
device.touch(s_width/2,s_height/48*31,'DOWN_AND_UP')
mr.sleep(1.0)
print "Accelerometer finished!"
#MainMenu
device.touch(s_width/40*39,s_height/96*91,'DOWN_AND_UP')
mr.sleep(3.0)
check_activity("Accelerometer")

#----------------KeypadTest----------------
print "Run KeypadTest"
mr.sleep(3.0)
device.touch(s_width/2,s_height/48*35,'DOWN_AND_UP')
mr.sleep(1.0)
device.press('KEYCODE_BACK','DOWN_AND_UP')
print "KeypadTest finished!"
mr.sleep(1.0)
#MainMenu
device.touch(s_width/40*39,s_height/96*91,'DOWN_AND_UP')
check_activity("KeypadTest")

#----------------CocosDenshionTest----------------
print "Run CocosDenshionTest"
mr.sleep(1.0)
device.touch(s_width/2,s_height/48*39,'DOWN_AND_UP')
#device.touch(400,30,'DOWN_AND_UP')
#device.touch(400,100,'DOWN_AND_UP')
print "CocosDenshionTest finished!"
mr.sleep(1.0)
#MainMenu
device.touch(s_width/40*39,s_height/96*91,'DOWN_AND_UP')
check_activity("CocosDenshionTest")

#----------------PerformanceTest----------------
print "Run PerformanceTest"
mr.sleep(1.0)
device.touch(s_width/2,s_height/48*43,'DOWN_AND_UP')
mr.sleep(1.0)
#PerformanceNodeChildrenTest
device.touch(s_width/2,s_height/12,'DOWN_AND_UP')
mr.sleep(1.0)
common_test(1,6,1.0)
#Back
device.touch(s_width/20*19,s_height/96*91,'DOWN_AND_UP')
mr.sleep(1.0)
#PerformanceParticleTest
device.touch(s_width/2,s_height/6,'DOWN_AND_UP')
mr.sleep(1.0)
#for NodeChildren_i in range(1,5):
#    device.touch(450,240,'DOWN_AND_UP')
#    mr.sleep(1.0)
#    device.touch(s_width/8*5,s_height/16*15,'DOWN_AND_UP')
#    mr.sleep(1.0)
common_test(1,5,1.0)
#Back
device.touch(s_width/20*19,s_height/96*91,'DOWN_AND_UP')
mr.sleep(1.0)
#PerformanceSpriteTest
device.touch(s_width/2,s_height/4,'DOWN_AND_UP')
mr.sleep(1.0)
#for NodeChildren_i in range(1,8):  
#    device.touch(430,80,'DOWN_AND_UP')
#    mr.sleep(1.0)
#    device.touch(370,80,'DOWN_AND_UP')
#    mr.sleep(1.0)
common_test(1,8,1.0)
#Back
device.touch(s_width/20*19,s_height/96*91,'DOWN_AND_UP')
mr.sleep(1.0)
#PerformanceTextureTest
#device.touch(s_width/2,s_height/3,'DOWN_AND_UP')
#mr.sleep(1.0)
#Back
#device.touch(s_width/20*19,s_height/96*91,'DOWN_AND_UP')
#mr.sleep(1.0)
#PerformanceTouchesTest
device.touch(s_width/2,s_height/12*5,'DOWN_AND_UP')
mr.sleep(1.0)
random_drag(1,11,0.2)
#Next Test
mr.sleep(1.0)
device.touch(s_width/8*5,s_height/16*15,'DOWN_AND_UP')
mr.sleep(1.0)
random_drag(1,11,0.2)
mr.sleep(1.0)
#Back
device.touch(s_width/20*19,s_height/96*91,'DOWN_AND_UP')
print "PerformanceTest finished!"
mr.sleep(1.0)
#MainMenu
device.touch(s_width/40*39,s_height/96*91,'DOWN_AND_UP')
check_activity("PerformanceTest")

#----------------ZwoptexTest----------------
print "Run ZwoptexTest"
mr.sleep(1.0)
device.touch(s_width/2,s_height/48*47,'DOWN_AND_UP')
print "ZwoptexTest finished!"
mr.sleep(1.0)
#MainMenu
device.touch(s_width/40*39,s_height/96*91,'DOWN_AND_UP')
check_activity("ZwoptexTest")
mr.sleep(1.0)
device.drag((s_width/4*3,s_height/16*15),(s_width/4*3,0))

#----------------CurlTest----------------
print "Run CurlTest"
mr.sleep(1.0)
device.touch(s_width/2,s_height/4,'DOWN_AND_UP')
mr.sleep(1.0)
random_click(1,2,1.0)
print "CurlTest finished!"
mr.sleep(1.0)
#MainMenu
device.touch(s_width/40*39,s_height/96*91,'DOWN_AND_UP')
check_activity("CurlTest")
mr.sleep(1.0)
device.drag((s_width/4*3,s_height/16*15),(s_width/4*3,0))

#----------------UserDefaultTest----------------
print "Run UserDefaultTest"
mr.sleep(1.0)
device.touch(s_width/2,s_height/3,'DOWN_AND_UP')
print "UserDefaultTest finished!"
mr.sleep(1.0)
#MainMenu
device.touch(s_width/40*39,s_height/96*91,'DOWN_AND_UP')
check_activity("UserDefaultTest")
mr.sleep(1.0)
device.drag((s_width/4*3,s_height/16*15),(s_width/4*3,0))

#----------------BugsTest----------------
print "Run BugsTest"
mr.sleep(1.0)
device.touch(s_width/2,s_height/12*5,'DOWN_AND_UP')
print "BugsTest is finished!"
mr.sleep(1.0)
#MainMenu
device.touch(s_width/40*39,s_height/96*91,'DOWN_AND_UP')
check_activity("BugsTest")
mr.sleep(1.0)
device.drag((s_width/4*3,s_height/16*15),(s_width/4*3,0))

#----------------FontTest----------------
print "Run FontTest"
mr.sleep(1.0)
device.touch(s_width/2,s_height/2,'DOWN_AND_UP')
mr.sleep(1.0)
common_test(1,6,0.5)
mr.sleep(1.0)
print "FontTest finished!"
#MainMenu
device.touch(s_width/40*39,s_height/96*91,'DOWN_AND_UP')
check_activity("FontTest")
mr.sleep(1.0)
device.drag((s_width/4*3,s_height/16*15),(s_width/4*3,0))

#----------------CurrentLanguageTest----------------
print "Run CurrentLanguageTest"
mr.sleep(1.0)
device.touch(s_width/2,s_height/12*7,'DOWN_AND_UP')
print "CurrentLanguageTest finished!"
mr.sleep(1.0)
#MainMenu
device.touch(s_width/40*39,s_height/96*91,'DOWN_AND_UP')
check_activity("CurrentLanguageTest")
mr.sleep(1.0)
device.drag((s_width/4*3,s_height/16*15),(s_width/4*3,0))

#----------------TextureCacheTest----------------
print "Run TextureCacheTest"
mr.sleep(1.0)
device.touch(s_width/2,s_height/3*2,'DOWN_AND_UP')
print "TextureCacheTest is finished!"
mr.sleep(1.0)
#MainMenu
device.touch(s_width/40*39,s_height/96*91,'DOWN_AND_UP')
check_activity("TextureCacheTest")
mr.sleep(1.0)
device.drag((s_width/4*3,s_height/16*15),(s_width/4*3,0))

#----------------ExtensionsTest----------------
print "Run ExtensionsTest"
mr.sleep(1.0)
device.touch(s_width/2,s_height/4*3,'DOWN_AND_UP')
#NotificationCenterTest
mr.sleep(1.0)
device.touch(s_width/2,s_height/12,'DOWN_AND_UP')
mr.sleep(1.0)
device.touch(s_width/40*23,s_height/2,'DOWN_AND_UP')
mr.sleep(1.0)
device.touch(s_width/40*23,s_height/2,'DOWN_AND_UP')
#Back
mr.sleep(1.0)
device.touch(s_width/20*19,s_height/96*91,'DOWN_AND_UP')
#CCControlButtonTest
mr.sleep(1.5)
device.touch(s_width/2,s_height/6,'DOWN_AND_UP')
mr.sleep(1.5)
device.drag((s_width/2,s_height/48*25),(s_width/20*13,s_height/48*25))
mr.sleep(1.5)
device.drag((s_width/20*13,s_height/48*25),(s_width/20*7,s_height/48*25))
    #Next Test
device.touch(s_width/8*5,s_height/16*15,'DOWN_AND_UP')
mr.sleep(1.5)
device.touch(s_width/16*7,s_height/2,'DOWN_AND_UP')
mr.sleep(1.5)
device.touch(s_width/40*19,s_height/2,'DOWN_AND_UP')
mr.sleep(1.5)
    #Next Test
device.touch(s_width/8*5,s_height/16*15,'DOWN_AND_UP')
mr.sleep(1.5)
    #Next Test
device.touch(s_width/8*5,s_height/16*15,'DOWN_AND_UP')
mr.sleep(1.5)
random_click(1,10,0.1)
    #Next Test
device.touch(s_width/8*5,s_height/16*15,'DOWN_AND_UP')
mr.sleep(1.5)
random_click(1,10,0.1)
mr.sleep(1.5)
#Next Test
device.touch(s_width/8*5,s_height/16*15,'DOWN_AND_UP')
mr.sleep(1.5)
random_click(1,10,0.1)
mr.sleep(1.5)
    #Back
device.touch(s_width/20*19,s_height/96*91,'DOWN_AND_UP')
mr.sleep(1.5)
#CocosBuilderTest
device.touch(s_width/2,s_height/4,'DOWN_AND_UP')
mr.sleep(1.5)
    #Menus & Items
device.touch(s_width/4,s_height/2,'DOWN_AND_UP')
mr.sleep(1.5)
device.touch(s_width/4,s_height/24*11,'DOWN_AND_UP')
mr.sleep(1.5)
device.touch(s_width/2,s_height/24*11,'DOWN_AND_UP')
mr.sleep(1.5)
        #ItemBack
device.touch(s_width/40,s_height/24,'DOWN_AND_UP')
mr.sleep(1.5)
    #Sprite & 9 Slice
device.touch(s_width/4*3,s_height/2,'DOWN_AND_UP')
mr.sleep(1.5)
        #ItemBack
device.touch(s_width/40,s_height/24,'DOWN_AND_UP')
mr.sleep(1.5)
    #Button
device.touch(s_width/4,s_height/8*5,'DOWN_AND_UP')
mr.sleep(1.5)
device.touch(s_width/2,s_height/24*11,'DOWN_AND_UP')
mr.sleep(1.5)
device.drag((s_width/2,s_height/24*11),(s_width/2,s_height/8*5))
mr.sleep(1.5)
        #ItemBack
device.touch(s_width/40,s_height/24,'DOWN_AND_UP')
mr.sleep(1.5)
    #Labels
device.touch(s_width/4*3,s_height/8*5,'DOWN_AND_UP')
mr.sleep(1.5)
        #ItemBack
device.touch(s_width/40,s_height/24,'DOWN_AND_UP')
mr.sleep(1.5)
    #Particle Systems
device.touch(s_width/40,s_height/4*3,'DOWN_AND_UP')
mr.sleep(1.5)
        #ItemBack
device.touch(s_width/40,s_height/24,'DOWN_AND_UP')
mr.sleep(1.5)
    #Scroll Views
device.touch(s_width/4*3,s_height/4*3,'DOWN_AND_UP')
mr.sleep(1.5)
random_drag(1,10,0.2)
mr.sleep(1.5)
        #ItemBack
device.touch(s_width/40,s_height/24,'DOWN_AND_UP')
mr.sleep(1.5)
print "ExtensionsTest finished!"
mr.sleep(1.5)
#MainMenu
device.touch(s_width/40*39,s_height/96*91,'DOWN_AND_UP')
check_activity("ExtensionsTest")
mr.sleep(1.0)
device.drag((s_width/4*3,s_height/16*15),(s_width/4*3,0))

#----------------ShaderTest----------------
print "Run ShaderTest"
mr.sleep(1.0)
device.touch(s_width/2,s_height/6*5,'DOWN_AND_UP')
mr.sleep(7.0)
common_test(1,7,1.0)
mr.sleep(2.0)
device.drag((s_width/2,s_height/3*2),(s_width/80*51,s_height/3*2))
mr.sleep(1.0)
device.drag((s_width/80*51,s_height/3*2),(s_width/80*29,s_height/3*2))
mr.sleep(1.0)
#Next Test
device.touch(s_width/8*5,s_height/16*15,'DOWN_AND_UP')
print "ShaderTest finished!"
mr.sleep(3.0)
#MainMenu
device.touch(s_width/40*39,s_height/96*91,'DOWN_AND_UP')
check_activity("ShaderTest")
mr.sleep(1.0)
device.drag((s_width/4*3,s_height/16*15),(s_width/4*3,0))

#----------------MutiTouchTest----------------
print "Run MutiTouchTest"
mr.sleep(3.0)
device.touch(s_width/2,s_height/12*11,'DOWN_AND_UP')
mr.sleep(1.0)
random_drag(1,10,0.1)
print "MutiTouchTest finished!"
mr.sleep(1.0)
#MainMenu
device.touch(s_width/40*39,s_height/96*91,'DOWN_AND_UP')
check_activity("MutiTouchTest")

#----------------Quit----------------
mr.sleep(1.0)
device.touch(s_width/80*77,s_height/12,'DOWN_AND_UP')
