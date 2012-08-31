setAutoWaitTimeout(10000)

val = getFindFailedResponse()
if val == ABORT:
    print "Abort"
if val == SKIP:
    print "SKIP"
if val == PROMPT:
    print "PROMPT"
if val == RETRY:
    print "RETRY"

def common_test(a,b,c):
    for i in range(a,b):
        wait(c)
        if exists("Next.png"):
            click("Next.png")

#ActionTest
click("ActionsTest.png")
print("Run ActionsTest")
common_test(1,28,1.0)
click(Pattern("MainMenu_Common.png").targetOffset(-93,0))
common_test(1,3,3.0)
common_test(1,6,1.0)
print("ActionsTest finished!")
click("MainMenu_Common.png")

#TransitionsTest
click("TransitionsTest.png")
print("Run TransitionsTest")
common_test(1,27,1.0)
print("TransitionsTest finished!")
click(Pattern("1346297215212.png").targetOffset(49,0))

#ActionsProgressTest
click("ActionsProgressTest.png")
print("Run ActionsProgressTest")
common_test(1,8,1.0)
print("ActionsProgressTest finished!")
click("MainMenu_ActionsProgress.png")


#EffectsTest
click("EffectsTest.png")
print("Run EffectsTest")
common_test(1,22,3.0)
print("Effects finished!")
click("MainMenu_Effects.png")

#ClickAndMoveTest
print("Run ClickAndMoveTest")
click("CickAndMoveTest.png")
wait(4)
click("ClickAndMove_Click.png")
click(Pattern("ClickAndMove_Click.png").targetOffset(200,-3))
click("MainMenu_ClickAndMove.png")

print("ClickAndMoveTest finished!")

#RotateWorldTest
print("Run RotateWorldTest")
click("RotateWorldTest.png")
wait(4)
click("MainMenu_ActionsProgress.png")
print("RotateWorldTest finished!")

#ParticleTest
print("Run ParticleTest")
click("ParticleTest.png")
common_test(1,43,2.0)
print("ParticleTest finished!")
click("MainMenu_Common.png")

dragDrop(Pattern("ParticleTest-1.png").targetOffset(91,17), Pattern("Acti0nsTest.png").targetOffset(93,-19))

#ActionEaseTest
print("Run ActionEaseTest")
click("ActionsEaseTest.png")
common_test(1,14,2.0)
click("MainMenu_Common.png")
print("ActionEaseTest finished!")

#MotionStreakTest
print("Run MotionStreakTest")
click("MotionStreakTest.png")
wait(1.0)
click(Pattern("MotionStreak_ChangeFastMode.png").targetOffset(20,0))
wait(1.0)
click("Next.png")
dragDrop("Motion_Drag1.png", "Motion_Drag2.png")
click(Pattern("MotionStreak_ChangeFastMode.png").targetOffset(20,0))
dragDrop("Motion_Drag1.png", "Motion_Drag2.png")
click("Next.png")
click(Pattern("MotionStreak_ChangeFastMode.png").targetOffset(20,0))
wait(1.0)
click("MainMenu_Common.png")
print("MotionStreakTest finished!")

#DrawPimitivesTest
print("Run DrawPimitivesTest")
click("DrawPrimitivesTest.png")
if exists("DrawPrimitives.png"):
    print("DrawPrimitivesTest success!")
print("DrawPimitivesTest finished!")
click("MainMenu_DrawPimitives.png")

#NodeTest
print("Run NodeTest")
click("NodeTest.png")
common_test(1,14,1.0)
click("MainMenu_Common.png")
print("NodeTest finished!")

#TouchesTest
print("Run TouchesTest")
click("TouchesTest.png")
wait(1.0)
click("MainMenu_Common.png")
print("TouchesTest finished!")

#MenuTest
print("Run MenuTest")
click("MenuTest.png")
click("MenuTest_AtlasSprite.png")
click("MenuTest_HighScores.png")
click("MenuTest_Play.png")
click("MenuTest_Eitems.png")
click("MenuTest_Config.png")
click("MenuTest_Back.png")
click("MenuTest_Quit.png")
click("MainMenu_Common.png")
print("MenuTest finished!")

#ActionManagerTest
print("Run ActionManagerTest")
click("ActionManaerTest.png")
common_test(1,5,3.0)
click("MainMenu_Common.png")
print("ActionManagerTest finished!")

#LayerTest
print("Run LayerTest")
click("LayerTest.png")
dragDrop("Layer_Drag1.png", "Layer_Drag2.png")
click("Next.png")
wait(1.0)
click("Next.png")
wait(1.0)
click("Next.png")
dragDrop("Layer_Drag3.png", "Layer_Drag4.png")
common_test(1,3,1.0)
click("MainMenu_Common.png")
print("LayerTest finished!")

dragDrop(Pattern("LaverTest-1.png").targetOffset(98,6), Pattern("Acti0nsEaseT.png").targetOffset(106,-11))

#SceneTest
print("Run SceneTest")
click("SceneTest.png")
click("Scene_pushScene.png")
click("Scene_relaceScene.png")
click("Scene_popToRoot.png")
click("Scene_Quit.png")
click("MainMenu_Common.png")
print("SceneTest finished!")

#ParallaxTest
print("Run ParallaxTest")
click("ParaIIaxTest.png")
wait(3.0)
click("Next.png")
dragDrop("Parallax_Drag1.png", "Parallax_Drag2.png")
click("MainMenu_Parallax.png")
print("ParallaxTest finished!")

#TileMapTest
print("Run TileMapTest")
click("TileMapTest.png")
common_test(1,21,2.0)
click("MainMenu_TileMap.png")
print("TileMapTest finished!")

#IntervalTest
print("Run IntervalTest")
click("IntervaITest.png")
wait(2.0)
click("Interval_pause.png")
wait(1.0)
click("Interval_pause.png")
click("MainMenu_Common.png")
print("IntervalTest finished!")

#ChipmunkAccelTouchTest
print("Run ChipmunkAccelTouchTest")
click("ChipmunkAccelTouchTest.png")
for i in range(1,3):
    click("ChipmunkAccelTouchTest_Click.png")
for i in range(1,3):
    click("it.png")
wait(3.0)
click("MainMenu_Common.png")
print("ChipmunkAccelTouchTest finished!")

#LabelTest
print("Run LabelTest")
click("LabeITest.png")
wait(1.0)
common_test(1,26,0.5)
click("MainMenu_Common.png")
print("LabelTest finished!")

#TextInputTest
print("Run TextInputTest")
click("TextInputTest.png")
type("TextInput_herefor.png", "1q~<?;\@")
click("TextInput_return.png")
click("Next.png")
type("TextInput_herefor.png", "1q~<?;\@")
click("TextInput_return.png")
click("MainMenu_Common.png")
print("TextInputTest finished!")

dragDrop(Pattern(".png").targetOffset(100,14), Pattern("I_yUIICDI.png").targetOffset(75,-8))

#SpriteTest
print("Run SpriteTest")
click("SpriteTest.png")
for i in range(1,3):
    click("SpriteTest_SpriteClick1.png")
for j in range(1,3):
    click("SpriteTest_SpriteClick2.png")
click("Next.png")
for i in range(1,3):
    click("SpriteTest_SpriteClick1.png")
for j in range(1,3):
    click("SpriteTest_SpriteClick2.png")
common_test(1,100,0.5)
click("MainMenu_Common.png")
print("SpriteTest finished!")

#SchdulerTest
print("Run SchdulerTest")
click("SchduIerTest.png")
wait(1.0)
click("Next.png")
dragDrop(Pattern("SchdulerTest_timeScale.png").targetOffset(23,0),Pattern("SchdulerTest_timeScale.png").targetOffset(-50,0))
click("Next.png")
dragDrop("Schduler_custom.png",Pattern("Schduler_custom.png").targetOffset(58,0))
common_test(1,11,1)
click("MainMenu_Common.png")
print("SchdulerTest finished!")

#RenderTextureTest
print("Run RenderTextureTest")
click("RenderTextureTest.png")
dragDrop("RenderTexture_Drag1.png", "RenderTexture_Drag2.png")
dragDrop("RenderTexture_Drag3.png", "RenderTexture_Drag4.png")
click("SaveImage.png")
click("Clear.png")
click("Next.png")
wait(1.0)
click("Next.png")
click("RenderTexture_vertexZclick1.png")
click("RenderTexture_vertexZclick2.png")
click("RenderTexture_vertexZclick3.png")
click("Next.png")
wait(1.0)
click("MainMenu_Common.png")
print("RenderTextureTest finished!")

#Texture2DTest
print("Run Texture2DTest")
click("Texture2DTest.png")
common_test(1,36,0.5)
click("MainMenu_Common.png")
print("Texture2DTest finished!")

#Box2dTest
print("Run Box2dTest")
click("Box2dTest.png")
for i in range(1,6):
    click("Box2dTest_Click1.png")
for i in range(1,6):
    click("Box2dTest_Click2.png")  
click("MainMenu_Common.png")
print("Box2dTest finished!")

#Box2dTestBed
print("Run Box2dTestBed")
click("Box2dTestBed.png")
common_test(1,36,2.0)
click("MainMenu_Common.png")
print("Box2dTestBed finished!")

#EffectAdvancedTest
print("Run EffectAdvancedTest")
click("EffectAdvancedTest.png")
common_test(1,6,1.0)
click("MainMenu_Common.png")
print("EffectAdvancedTest finished!")

#Accelerometer
print("Run Accelerometer")
click("Accelerometer.png")
click("MainMenu_Common.png")
print("Accelerometer finished!")

dragDrop(Pattern("AccalaromeLI.png").targetOffset(120,2), Pattern("SmiteTest.png").targetOffset(130,-9))

#KeypadTest
print("Run KeypadTest")
click("KeypadTest.png")
click("MainMenu_Common.png")
print("KeypadTest finished!")

#CocosDenshionTest
print("Run CocosDenshionTest")
click("CocosDenshionTest.png")
click("CocosDenshionTest_play.png")
click("CocosDenshionTest_stop.png")
click("CocosDenshionTest_pause.png")
click("CocosDenshionTest_resume.png")
click("CocosDenshionTest_rewind.png")
click("CocosDenshionTest_is.png")
click("CocosDenshionTest_playeffect.png")
dragDrop(Pattern("playeffectrr.png").targetOffset(-130,15), Pattern("Dlavbackqrou.png").targetOffset(-140,-15))
click("CocosDenshionTest_playeffect.png")
click("CocosDenshionTest_stop.png")
click("CocosDenshionTest_unload.png")
click("CocosDenshionTest_addback.png")
click("CocosDenshionTest_subback.png")
click("CocosDenshionTest_addeff.png")
click("CocosDenshionTest_subeff.png")
click("CocosDenshionTest_pause.png")
dragDrop(Pattern("pauseeffect.png").targetOffset(-120,6), Pattern("playeffectre.png").targetOffset(-130,-9))
click("CocosDenshionTest_addeff.png")
click("CocosDenshionTest_subeff.png")
click("CocosDenshionTest_pauseeffect.png")
click("CocosDenshionTest_resumeff.png")
click("CocosDenshionTest_pauseall.png")
click("CocosDenshionTest_resumeall.png")
click("CocosDenshionTest_stop.png")
click("MainMenu_Common.png")
print("CocosDenshionTest finished!")

#PerformanceTest
print("Run PerformanceTest")
click("PerformanceTest.png")
click("Performance_NodeChiIdren.png")
click("Performance_Add.png")
common_test(1,6,0.5)
click("Common_Back.png")
click("Performance_Particle.png")
click("Performance_Add.png")
common_test(1,5,0.5)
click("Common_Back.png")
click("Performance_Sprite.png")
common_test(1,5,0.5)
click("nf.png")
click("Performance_Texture.png")
click("Common_Back.png")
click("Touches.png")
click("T.png")
click("Performance_Click2.png")
click("Next.png")
click("Performance_Click3.png")
click("Performance_Click2.png")
click("Common_Back.png")
click("MainMenu_Common.png")
print("PerformanceTest finished!")

#ZwoptexTest
print("Run ZwoptexTest")
click("ZwoptexTest.png")
click("MainMenu_Common.png")
print("ZwoptexTest finished!")

#CurlTest
print("Run CurlTest")
click("CurlTest.png")
click("SCFGSFI.png")
click("MainMenu_Common.png")
print("CurlTest finished!")

#UserDefaultTest
print("Run UserDefaultTest")
click("UserDefaultTest.png")
click("MainMenu_Common.png")
print("UserDefaultTest finished!")

#BugsTest
print("Run BugsTest")
click("BugsTest-1.png")
click("Bug350.png")
click("Back.png")
click("Buci422.png")
click("One.png")
click("1345694015019.png")
click("Common_Back.png")
click("Bug-458.png")
click("Common_Back.png")
click("Bug-624.png")
click("Common_Back.png")
click("Bug-886.png")
click("Bugs_back_1.png")
click("Bug-899.png")
click("Bugs_back_4.png")
click("Bug914.png")
click("Bugs_back_2.png")
dragDrop(Pattern("Bug914-2.png").targetOffset(-103,16), Pattern("Bug350-1.png").targetOffset(-100,-19))
click("Bug1159.png")
click("Bugs_back_5.png")
click("Bug1174.png")
wait(0.5)
click("Common_Back.png")
click("MainMenu_Common.png")
print("BugsTest finished!")

dragDrop(Pattern("BugsTest-2.png").targetOffset(-110,17), Pattern("HUUBIUIUlIIU.png").targetOffset(-120,-9))

#FontTest
print("Run FontTest")
click("FontTest.png")
common_test(1,6,0.5)
click("MainMenu_Common.png")
print("FontTest finished!")

#CurrentLauguageTest
print("Run CurrentLauguageTest")
click("CurrentLanguageTest.png")
click("MainMenu_Common.png")
print("CurrentLauguageTest finished!")

#TextureCacheTest
print("Run TextureCacheTest")
click("TextureCacheTest.png")
click("MainMenu_TextureCache.png")
print("TextureCacheTest finished!")

#ExtensionsTest
print("Run ExtensionsTest")
click("ExtensionsTest.png")
click("NotificationCenterTest.png")
click("Notification_switchon.png")
click("Common_Back.png")
click("Extensions_CCControlButton.png")
wait(0.5)
dragDrop(Pattern("D.png").targetOffset(-120,0),Pattern("D.png").targetOffset(120,0))
click("Next.png")
click("ControlColourPickerTest.png")
click("Next.png")
click(Pattern("ControlSwitch.png").targetOffset(-19,0))
click("Next.png")
click("ControlButton_Variable.png")
click("Next.png")
click("ControlButton_Event.png")
click("Next.png")
click("ControlButton_Styling.png")
click("Back_ControlButton.png")
click("CocosBuilder.png")
click("CocosBuilder_MenusItems.png")
click("CocosBuilder_back.png")
click("CocosBuilder_Sprite.png")
click("CocosBuilder_back.png")
click("CocosBuilder_Button.png")
click("CocosBuilder_back.png")
click("CocosBuilder_Labels.png")
click("CocosBuilder_back.png")
click("CocosBuilder_ParticleSystems.png")
click("CocosBuilder_back.png")
click("CocosBuilder_ScrollWews.png")
click("CocosBuilder_back.png")
click("MainMenu_Extensions.png")
print("ExtensionsTest finished!")

#ShaderTest
print("Run ShaderTest")
click("ShaderTest.png")
common_test(1,7,0.5)
wait(0.5)
dragDrop(Pattern("1345698378832.png").targetOffset(-44,0),Pattern("1345698378832.png").targetOffset(80,0))
click("Next.png")
click("MainMenu_Common.png")
print("ShaderTest finished!")

#MutiTouchTest
print("Run MutiTouchTest")
click("MutiTouchTest.png")
for i in range(1,3):
    dragDrop("i.png", "Maintvienu.png")
    dragDrop("1346311259004.png", Pattern("C.png").targetOffset(-50,0))  
click("MainMenu_Common.png")
print("MutiTouchTest finished!")

#Quit
print("Quit")
click("1346315512087.png")