Dim Milliseconds
DefaultTimeout = Setting("DefaultTimeout")

If DefaultTimeout > 10000 Then
	Milliseconds = 10000
	Setting("DefaultTimeout") = Milliseconds
End If

Err.Clear
On Error Resume Next
call CaseFunctionName

If Err.Number <> 0 Then

    If Dialog("TestCpp.exe").Exist(3) Then
		Dialog("TestCpp.exe").Activate
		Dialog("TestCpp.exe").Move 872,177
		Dialog("TestCpp.exe").WinObject("DirectUIHWND").Click 21,235
		Wait 1
	End If
	
    WriteLog Err.Number
    WriteLog Err.Description
    WriteLog Err.Source

  	Dim FileName ,TimeNow, ResPath
	ResPath = Environment.Value("TestDir")
	ResPath = ResPath & "\"
	TestNameNow=environment.Value("TestName") 
	FileName = ResPath & ""&TestNameNow & ".png"

	desktop.CaptureBitmap  filename,True
	Systemutil.closedescendentprocesses
	
	If Dialog("TestCpp.exe").Exist(3) Then
		Dialog("TestCpp.exe").WinObject("关闭程序").Click
	End If
	
End If
Err.Clear
On Error goto 0

Function CaseFunctionName()
   'SystemUtil.BlockInput
	Window("Hello Tests").Activate
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	'ActionsTest
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	Window("Hello Tests").Click 241,43
	Wait 2
	
	Dim ActionsTest_i
	For ActionsTest_i = 1 To 27
		Window("Hello Tests").Click 338,291
		Wait 1
	Next
	
	Window("Hello Tests").Click 338,291
	Wait 5
	Window("Hello Tests").Click 338,291
	Wait 2
	
	Dim ActionsTest_j
	For ActionsTest_j = 1 To 5
		Window("Hello Tests").Click 338,291
		Wait 1
	Next
	'MainMenu
	Window("Hello Tests").Click 441,296
	Wait 2
	
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	'TransitionsTest
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	Window("Hello Tests").Click 236,77
	Wait 5
	
	Dim Transitions_i
	For Transitions_i = 1 To 26
		Window("Hello Tests").Click 338,291
		Wait 1
	Next
	Wait 1
	'MainMenu
	Window("Hello Tests").Click 441,296
	Wait 2
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	'ActionsProgressTest
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	Window("Hello Tests").Click 287,113
	Wait 2
	
	Dim ActionsProgress_i
	For ActionsProgress_i = 1 To 7
		Window("Hello Tests").Click 338,291
		Wait 2
	Next
	'MainMenu
	Window("Hello Tests").Click 441,296
	Wait 2
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	'EffectsTest
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	Window("Hello Tests").Click 236,163
	Wait 3
	
	Dim Effects_i
	For Effects_i = 1 To 21
		Window("Hello Tests").Click 338,291
		Wait 4
	Next
	'MainMenu
	Window("Hello Tests").Click 441,296
	Wait 2
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	'ClickAndMoveTest
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	Window("Hello Tests").Click 228,199
	Wait 3

	Dim touch_x,touch_y
	Randomize
	For  Response = 0 To 10
		touch_x = Int((400 * Rnd + 0))
		touch_y = Int((250 * Rnd + 0))
		Window("Hello Tests").Click touch_x,touch_y
		Wait 2
	Next
	
	For Response = 0 To 100
		touch_x = Int((400 * Rnd + 0))
		touch_y = Int((250 * Rnd + 0))
		Window("Hello Tests").Click touch_x,touch_y
	Next
	'MainMenu
	Window("Hello Tests").Click 441,296
	Wait 2
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	'RotateWorldTest
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	Window("Hello Tests").Click 237,235
	Wait 3.5
	''MainMenu
	Window("Hello Tests").Click 441,296
	Wait 2
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	'ParticleTest
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	Window("Hello Tests").Click 236,276
	Wait 3
	
	Dim Particle_i
	For Particle_i = 1 To 42
		Window("Hello Tests").Click 338,291
		Wait 2
	Next
	MainMenu
	Window("Hello Tests").Click 441,296
	Wait 2
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	'ActionEaseTest
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	Window("Hello Tests").Drag 363,307
	Window("Hello Tests").Drop 363,10
	Wait 1
	Window("Hello Tests").Click 237,19
	Wait 2
	
	Dim ActionEase_i
	For ActionEase_i = 1 To 13
		Window("Hello Tests").Click 338,291
		Wait 2
	Next
	'MainMenu
	Window("Hello Tests").Click 441,296
	Wait 2
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	'MotionStreakTest
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	Window("Hello Tests").Click 240,61
	Wait 2
	
	Window("Hello Tests").Click 230,239
	Window("Hello Tests").Click 338,291
	
	Dim drag_x,drag_y,drop_x,drop_y
	Randomize
	For  Response = 0 To 10
		drag_x = Int((400 * Rnd + 0))
		drag_y = Int((250 * Rnd + 0))
		drop_x = Int((400 * Rnd + 0))
		drop_y = Int((250 * Rnd + 0))
		Window("Hello Tests").Drag drag_x,drag_y
		Window("Hello Tests").Drop drop_x,drop_y
	Next
	Window("Hello Tests").Click 230,239
	Randomize
	For  Response = 0 To 10
		drag_x = Int((400 * Rnd + 0))
		drag_y = Int((250 * Rnd + 0))
		drop_x = Int((400 * Rnd + 0))
		drop_y = Int((250 * Rnd + 0))
		Window("Hello Tests").Drag drag_x,drag_y
		Window("Hello Tests").Drop drop_x,drop_y
	Next
	
	Window("Hello Tests").Click 338,291
	Wait 2
	
	'MainMenu
	Window("Hello Tests").Click 441,296
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	'DrawPrimitivesTest
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	Window("Hello Tests").Click 235,101
	Wait 1
	'MainMenu
	Window("Hello Tests").Click 441,296
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	'NodeTest
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	Window("Hello Tests").Click 237,139
	Wait 1
	
	Dim DrawPrimitives_i
	For DrawPrimitives_i = 1 To 13
		Window("Hello Tests").Click 338,291
		Wait 1
	Next
	'MainMenu
	Window("Hello Tests").Click 441,296
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	'TouchesTest
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	Window("Hello Tests").Click 238,183
	Window("Hello Tests").Drag 236,221
	Window("Hello Tests").Drop 175,226
	
	Wait 5
	'MainMenu
	Window("Hello Tests").Click 441,296
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	'MenuTest
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	Window("Hello Tests").Click 234,220
	Window("Hello Tests").Click 238,63
	Window("Hello Tests").Click 158,132

	Window("Hello Tests").Click 238,155
	Window("Hello Tests").Click 236,180
	Window("Hello Tests").Click 158,188
	Window("Hello Tests").Click 313,184
	Window("Hello Tests").Click 190,217
	Window("Hello Tests").Click 235,216
	Window("Hello Tests").Click 205,144
	Window("Hello Tests").Click 218,143
	Window("Hello Tests").Click 237,247
	'MainMenu
	Window("Hello Tests").Click 441,296
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	'ActionManagerTest
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	Window("Hello Tests").Click 234,261
	
	Dim ActionManager_i
	For ActionManager_i = 1 To 4
		Window("Hello Tests").Click 338,291
		Wait 3
	Next
	'MainMenu
	Window("Hello Tests").Click 441,296
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	'LayerTest
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	Window("Hello Tests").Click 240,302

	Randomize
	For  Response = 0 To 10
		drag_x = Int((400 * Rnd + 0))
		drag_y = Int((250 * Rnd + 0))
		drop_x = Int((400 * Rnd + 0))
		drop_y = Int((250 * Rnd + 0))
		Window("Hello Tests").Drag drag_x,drag_y
		Window("Hello Tests").Drop drop_x,drop_y
	Next
	Window("Hello Tests").Click 338,291
	Wait 2
	Window("Hello Tests").Click 338,291
	Wait 2
	Window("Hello Tests").Click 338,291
	Randomize
	For  Response = 0 To 10
		drag_x = Int((400 * Rnd + 0))
		drag_y = Int((250 * Rnd + 0))
		drop_x = Int((400 * Rnd + 0))
		drop_y = Int((250 * Rnd + 0))
		Window("Hello Tests").Drag drag_x,drag_y
		Window("Hello Tests").Drop drop_x,drop_y
	Next
	Window("Hello Tests").Click 338,291
	Wait 1
	Window("Hello Tests").Click 242,164
	Wait 1
	Window("Hello Tests").Click 338,291
	Wait 1
	Window("Hello Tests").Click 254,163
	Wait 1
	Window("Hello Tests").Click 338,291
	Wait 1
	Window("Hello Tests").Click 231,164
	Wait 1
	'MainMenu
	Window("Hello Tests").Click 441,296
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	'SceneTest
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	Window("Hello Tests").Drag 370,306
	Window("Hello Tests").Drop 370,-20
	Wait 1
	Window("Hello Tests").Click 234,17
	Wait 1
	Window("Hello Tests").Click 230,111
	Window("Hello Tests").Click 230,111
	Window("Hello Tests").Click 230,111
	Window("Hello Tests").Click 233,163
	Window("Hello Tests").Click 226,218
	Window("Hello Tests").Click 226,218
	'MainMenu
	Window("Hello Tests").Click 441,296
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	'ParallaxTest
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	Window("Hello Tests").Click 232,55
	Wait 5
	Window("Hello Tests").Click 338,291

	Randomize
	For  Response = 0 To 10
		drag_x = Int((400 * Rnd + 0))
		drag_y = Int((250 * Rnd + 0))
		drop_x = Int((400 * Rnd + 0))
		drop_y = Int((250 * Rnd + 0))
		Window("Hello Tests").Drag drag_x,drag_y
		Window("Hello Tests").Drop drop_x,drop_y
	Next
	'MainMenu
	Window("Hello Tests").Click 441,296
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	'TileMapTest
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	Window("Hello Tests").Click 233,99
	Wait 2
	Window("Hello Tests").Click 338,291
	Wait 2

	Randomize
	For  Response = 0 To 10
		drag_x = Int((400 * Rnd + 0))
		drag_y = Int((250 * Rnd + 0))
		drop_x = Int((400 * Rnd + 0))
		drop_y = Int((250 * Rnd + 0))
		Window("Hello Tests").Drag drag_x,drag_y
		Window("Hello Tests").Drop drop_x,drop_y
	Next
	'MainMenu
	Window("Hello Tests").Click 441,296
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	'IntervalTest
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	Window("Hello Tests").Click 235,139
	Wait 3
	Window("Hello Tests").Click 224,48
	Wait 1
	Window("Hello Tests").Click 231,52
	Window("Hello Tests").Click 228,56
	Window("Hello Tests").Click 228,56
	'MainMenu
	Window("Hello Tests").Click 441,296
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	'ChipmunkAccelTouchTest
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	Window("Hello Tests").Click 235,178

	Randomize
	For  Response = 0 To 20
		touch_x = Int((400 * Rnd + 0))
		touch_y = Int((250 * Rnd + 0))
		Window("Hello Tests").Click touch_x,touch_y
	Next
	Wait 2
	'MainMenu
	Window("Hello Tests").Click 441,296
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	'LabelTest
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	Window("Hello Tests").Click 239,216
	Wait 3
	Dim LabelTest_i
	For LabelTest_i = 1 To 25
		Window("Hello Tests").Click 338,291
		Wait 0.5
	Next
	'MainMenu
	Window("Hello Tests").Click 441,296
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	'TextInputTest
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	Window("Hello Tests").Click 236,255

	Window("Hello Tests").Click 238,161
	Const constring = "0123456789abcdefgchijklmnopqrstuvwxyz"
	Dim TextInput_i,TextInput_j,randstring
	Randomize 
	For TextInput_i=1 To 8
		randstring = randstring & Mid(constring, Int(Len(constring)*Rnd)+1, 1)
	Next
	Window("Hello Tests").Type randstring
	Window("Hello Tests").Click 338,291
	Window("Hello Tests").Click 238,161
	Randomize 
	For TextInput_j=1 To 8
		randstring = randstring & Mid(constring, Int(Len(constring)*Rnd)+1, 1)
	Next
	Window("Hello Tests").Type randstring
	'MainMenu
	Window("Hello Tests").Click 441,296
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	'SpriteTest
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	Window("Hello Tests").Click 238,294
	
	Dim Sprite_Response
	Randomize
	For  Sprite_Response = 0 To 10
		touch_x = Int((400 * Rnd + 0))
		touch_y = Int((250 * Rnd + 0))
		Window("Hello Tests").Click touch_x,touch_y
	Next
	Wait 2
	Window("Hello Tests").Click 338,291
	Randomize
	For  Sprite_Response = 0 To 10
		touch_x = Int((400 * Rnd + 0))
		touch_y = Int((250 * Rnd + 0))
		Window("Hello Tests").Click touch_x,touch_y
	Next
	Wait 2
	Window("Hello Tests").Click 338,291
	Dim SpiteTest_i
	For SpriteTest_i = 1 To 108
		Window("Hello Tests").Click 338,291
		Wait 0.5
	Next
	'MainMenu
	Window("Hello Tests").Click 441,296
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	'SchdulerTest
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	Window("Hello Tests").Drag 359,309
	Window("Hello Tests").Drop 359,-11
	Wait 1
	'Schedule with delay of 3sec,repeat 4
	Window("Hello Tests").Click 236,15
	Window("Hello Tests").Click 338,291
	'Scheduler timeScale Test
	Window("Hello Tests").Drag 260,212
	Window("Hello Tests").Drop 301,212
	Wait 1
	Window("Hello Tests").Drag 301,212
	Window("Hello Tests").Drop 209,214
	Wait 1
	Window("Hello Tests").Drag 209,214
	Window("Hello Tests").Drop 100,208
	Wait 2
	Window("Hello Tests").Click 338,291
	'Two custom schedulers
	Window("Hello Tests").Drag 126,16
	Window("Hello Tests").Drop 81,22
	Wait 1
	Window("Hello Tests").Drag 361,19
	Window("Hello Tests").Drop 422,22
	Wait 3
	Window("Hello Tests").Click 338,291
	'Self -remove an scheduler
	Window("Hello Tests").Click 338,291
	'Pause/Resume
	Window("Hello Tests").Click 338,291
	'Pause/Resume
	Wait 3
	Window("Hello Tests").Click 338,291
	'Unschedule All selectors
	Window("Hello Tests").Click 338,291
	'Unschedule All selectors(HARD)
	Wait 2
	Window("Hello Tests").Click 338,291
	'Unschedule All selectors
	Wait 4
	Window("Hello Tests").Click 338,291
	'Schedule from Schedule
	Window("Hello Tests").Click 338,291
	'Schedule update with priority
	Window("Hello Tests").Click 338,291
	'MainMenu
	Window("Hello Tests").Click 441,296
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	'RenderTextureTest
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	Window("Hello Tests").Click 240,59
	'Save Image

	Randomize
	For  Response = 0 To 10
		drag_x = Int((400 * Rnd + 0))
		drag_y = Int((250 * Rnd + 0))
		drop_x = Int((400 * Rnd + 0))
		drop_y = Int((250 * Rnd + 0))
		Window("Hello Tests").Drag drag_x,drag_y
		Window("Hello Tests").Drop drop_x,drop_y
	Next
	Window("Hello Tests").Click 388,17
	Window("Hello Tests").Click 398,41
	Wait 1
	Window("Hello Tests").Click 338,291
	'Testing issue #937
	Window("Hello Tests").Click 338,291
	'Testing Z Buffer in Render Texture
	Dim Render_Response
	Randomize
	For  Render_Response = 0 To 10
		touch_x = Int((400 * Rnd + 0))
		touch_y = Int((250 * Rnd + 0))
		Window("Hello Tests").Click touch_x,touch_y
	Next
	Window("Hello Tests").Click 338,291
	'Testing depthStencil attachment
	MainMenu
	Window("Hello Tests").Click 441,296
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	'Texture2DTest
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	Window("Hello Tests").Click 234,97
	Dim Texture2D_i
	For Texture2D_i = 1 To 35
		Window("Hello Tests").Click 338,291
		Wait 0.5
	Next
	MainMenu
	Window("Hello Tests").Click 441,296
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	'Box2dTest
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	Window("Hello Tests").Click 235,134
	Dim Box2d_Response
	Randomize
	For  Box2d_Response = 0 To 30
		touch_x = Int((400 * Rnd + 0))
		touch_y = Int((250 * Rnd + 0))
		Window("Hello Tests").Click touch_x,touch_y
	Next
	Wait 2
	'MainMenu
	Window("Hello Tests").Click 441,296
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	'Box2dTestBed
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	Window("Hello Tests").Click 236,176
	Dim Box2D_i
	For Box2D_i = 1 To 35
		Window("Hello Tests").Click 338,291
		Wait 2
	Next
	'MainMenu
	Window("Hello Tests").Click 441,296
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	'EffectAdvancedTest
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	Window("Hello Tests").Click 237,217
	Dim Effect_i
	For Effect_i = 1 To 5
		Window("Hello Tests").Click 338,291
		Wait 1
	Next
	'MainMenu
	Window("Hello Tests").Click 441,296
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	AccelerometerTest
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	Window("Hello Tests").Click 244,255
	'MainMenu
	Window("Hello Tests").Click 441,296
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	'KeypadTest
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	Window("Hello Tests").Click 240,298
	'MainMenu
	Window("Hello Tests").Click 441,296
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	'CocosDenshionTest
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	Window("Hello Tests").Drag 377,314 @@ hightlight id_;_920298_;_script infofile_;_ZIP::ssf411.xml_;_
	Window("Hello Tests").Drop 377,0 @@ hightlight id_;_920298_;_script infofile_;_ZIP::ssf412.xml_;_
	Wait 1
	Window("Hello Tests").Click 243,20 @@ hightlight id_;_920298_;_script infofile_;_ZIP::ssf413.xml_;_
	
	Window("Hello Tests").Click 248,38 @@ hightlight id_;_920298_;_script infofile_;_ZIP::ssf415.xml_;_
	Wait 1
	Window("Hello Tests").Click 248,78 @@ hightlight id_;_920298_;_script infofile_;_ZIP::ssf416.xml_;_
	Wait 1
	Window("Hello Tests").Click 247,121 @@ hightlight id_;_920298_;_script infofile_;_ZIP::ssf417.xml_;_
	Wait 1
	Window("Hello Tests").Click 246,158 @@ hightlight id_;_920298_;_script infofile_;_ZIP::ssf418.xml_;_
	Wait 1
	Window("Hello Tests").Click 251,202 @@ hightlight id_;_920298_;_script infofile_;_ZIP::ssf419.xml_;_
	Wait 1
	Window("Hello Tests").Click 246,238 @@ hightlight id_;_920298_;_script infofile_;_ZIP::ssf420.xml_;_
	Wait 1
	Window("Hello Tests").Click 241,282 @@ hightlight id_;_920298_;_script infofile_;_ZIP::ssf421.xml_;_
	Wait 1
	Window("Hello Tests").Drag 427,260 @@ hightlight id_;_920298_;_script infofile_;_ZIP::ssf422.xml_;_
	Window("Hello Tests").Drop 427,6 @@ hightlight id_;_920298_;_script infofile_;_ZIP::ssf423.xml_;_
	Window("Hello Tests").Click 232,18 @@ hightlight id_;_920298_;_script infofile_;_ZIP::ssf424.xml_;_
	Wait 1
	Window("Hello Tests").Click 245,56 @@ hightlight id_;_920298_;_script infofile_;_ZIP::ssf425.xml_;_
	Wait 1
	Window("Hello Tests").Click 242,109 @@ hightlight id_;_920298_;_script infofile_;_ZIP::ssf426.xml_;_
	Wait 1
	Window("Hello Tests").Click 242,144 @@ hightlight id_;_920298_;_script infofile_;_ZIP::ssf427.xml_;_
	Wait 1
	Window("Hello Tests").Click 243,189 @@ hightlight id_;_920298_;_script infofile_;_ZIP::ssf428.xml_;_
	Wait 1
	Window("Hello Tests").Click 243,230 @@ hightlight id_;_920298_;_script infofile_;_ZIP::ssf429.xml_;_
	Wait 1
	Window("Hello Tests").Click 254,275 @@ hightlight id_;_920298_;_script infofile_;_ZIP::ssf430.xml_;_
	Wait 1
	Window("Hello Tests").Click 248,304 @@ hightlight id_;_920298_;_script infofile_;_ZIP::ssf431.xml_;_
	Wait 1
	Window("Hello Tests").Drag 412,272 @@ hightlight id_;_920298_;_script infofile_;_ZIP::ssf432.xml_;_
	Window("Hello Tests").Drop 412,-13 @@ hightlight id_;_920298_;_script infofile_;_ZIP::ssf433.xml_;_
	Window("Hello Tests").Click 235,124 @@ hightlight id_;_920298_;_script infofile_;_ZIP::ssf434.xml_;_
	Wait 1
	Window("Hello Tests").Click 238,158 @@ hightlight id_;_920298_;_script infofile_;_ZIP::ssf435.xml_;_
	Wait 1
	Window("Hello Tests").Click 229,200 @@ hightlight id_;_920298_;_script infofile_;_ZIP::ssf436.xml_;_
	Wait 1
	Window("Hello Tests").Click 239,243 @@ hightlight id_;_920298_;_script infofile_;_ZIP::ssf437.xml_;_
	Wait 1
	Window("Hello Tests").Click 246,277 @@ hightlight id_;_920298_;_script infofile_;_ZIP::ssf438.xml_;_
	Wait 1
	'MainMenu
	Window("Hello Tests").Click 441,296
	'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	'PerformanceTest
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	Window("Hello Tests").Click 237,64 @@ hightlight id_;_920298_;_script infofile_;_ZIP::ssf440.xml_;_
	Window("Hello Tests").Click 238,37 @@ hightlight id_;_920298_;_script infofile_;_ZIP::ssf441.xml_;_

	'PerformanceNodeChildrenTest @@ hightlight id_;_920298_;_script infofile_;_ZIP::ssf442.xml_;_
	Window("Hello Tests").Click 238,38 @@ hightlight id_;_920298_;_script infofile_;_ZIP::ssf458.xml_;_
	Dim Performance_i
	For Performance_i = 1 To 4
		Window("Hello Tests").Click 273,145 @@ hightlight id_;_920298_;_script infofile_;_ZIP::ssf470.xml_;_
		Window("Hello Tests").Click 338,291
		Wait 1
	Next
	Back
	Window("Hello Tests").Click 427,290 @@ hightlight id_;_920298_;_script infofile_;_ZIP::ssf472.xml_;_

	'PerformanceParticeTest
	Window("Hello Tests").Click 237,78 @@ hightlight id_;_920298_;_script infofile_;_ZIP::ssf473.xml_;_

	For Performance_j = 1 To 4
		Window("Hello Tests").Click 273,145 @@ hightlight id_;_920298_;_script infofile_;_ZIP::ssf470.xml_;_
		Window("Hello Tests").Click 338,291
		Wait 1
	Next
	'Back @@ hightlight id_;_920298_;_script infofile_;_ZIP::ssf474.xml_;_
	Window("Hello Tests").Click 427,290 @@ hightlight id_;_920298_;_script infofile_;_ZIP::ssf472.xml_;_

	'PerformanceSpriteTest @@ hightlight id_;_920298_;_script infofile_;_ZIP::ssf479.xml_;_
	Window("Hello Tests").Click 233,120 @@ hightlight id_;_920298_;_script infofile_;_ZIP::ssf480.xml_;_
	Dim Performance_k @@ hightlight id_;_920298_;_script infofile_;_ZIP::ssf481.xml_;_
	For Performance_k = 1 To 5
		Window("Hello Tests").Click 271,64 @@ hightlight id_;_920298_;_script infofile_;_ZIP::ssf470.xml_;_
		Window("Hello Tests").Click 338,291
		Wait 1
	Next
	'Back @@ hightlight id_;_920298_;_script infofile_;_ZIP::ssf474.xml_;_
	Window("Hello Tests").Click 427,290 @@ hightlight id_;_920298_;_script infofile_;_ZIP::ssf472.xml_;_

	'PerformanceTextureTest
	Window("Hello Tests").Click 229,159 @@ hightlight id_;_4064864_;_script infofile_;_ZIP::ssf499.xml_;_
	'Back @@ hightlight id_;_920298_;_script infofile_;_ZIP::ssf474.xml_;_
	Window("Hello Tests").Click 427,290 @@ hightlight id_;_920298_;_script infofile_;_ZIP::ssf472.xml_;_

	'PerformanceTouchesTest
	Window("Hello Tests").Click 234,200 @@ hightlight id_;_4064864_;_script infofile_;_ZIP::ssf506.xml_;_
	Randomize @@ hightlight id_;_4064864_;_script infofile_;_ZIP::ssf507.xml_;_
	For  Response = 0 To 10
		drag_x = Int((400 * Rnd + 0))
		drag_y = Int((250 * Rnd + 0))
		drop_x = Int((400 * Rnd + 0))
		drop_y = Int((250 * Rnd + 0))
		Window("Hello Tests").Drag drag_x,drag_y
		Window("Hello Tests").Drop drop_x,drop_y
	Next
	Window("Hello Tests").Click 338,291
	Randomize @@ hightlight id_;_4064864_;_script infofile_;_ZIP::ssf507.xml_;_
	For  Response = 0 To 10
		drag_x = Int((400 * Rnd + 0))
		drag_y = Int((250 * Rnd + 0))
		drop_x = Int((400 * Rnd + 0))
		drop_y = Int((250 * Rnd + 0))
		Window("Hello Tests").Drag drag_x,drag_y
		Window("Hello Tests").Drop drop_x,drop_y
	Next
	'Back @@ hightlight id_;_920298_;_script infofile_;_ZIP::ssf474.xml_;_
	Window("Hello Tests").Click 427,290 @@ hightlight id_;_920298_;_script infofile_;_ZIP::ssf472.xml_;_
	'MainMenu
	Window("Hello Tests").Click 441,296
	'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	'ZwoptexTest
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	Window("Hello Tests").Click 233,104 @@ hightlight id_;_1116094_;_script infofile_;_ZIP::ssf511.xml_;_
	Wait 1 @@ hightlight id_;_1116094_;_script infofile_;_ZIP::ssf512.xml_;_
	'MainMenu
	Window("Hello Tests").Click 441,296
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	'CurlTest
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	Window("Hello Tests").Click 239,141
	Window("Hello Tests").Click 242,160 @@ hightlight id_;_1116094_;_script infofile_;_ZIP::ssf521.xml_;_
	'MainMenu @@ hightlight id_;_1116094_;_script infofile_;_ZIP::ssf522.xml_;_
	Window("Hello Tests").Click 441,296
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	'UserDefaultTest
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	Window("Hello Tests").Click 238,184 @@ hightlight id_;_1116094_;_script infofile_;_ZIP::ssf528.xml_;_
	'MainMenu @@ hightlight id_;_1116094_;_script infofile_;_ZIP::ssf529.xml_;_
	Window("Hello Tests").Click 441,296
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	'BugsTest
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	Window("Hello Tests").Click 240,222
	'MainMenu @@ hightlight id_;_1116094_;_script infofile_;_ZIP::ssf529.xml_;_
	Window("Hello Tests").Click 441,296
	'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	'FontTest
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	Window("Hello Tests").Click 237,261 @@ hightlight id_;_1116094_;_script infofile_;_ZIP::ssf559.xml_;_
	Dim Font_i
	For Font_i = 1 To 4
		Wait 0.5
		Window("Hello Tests").Click 338,291
	Next
	'MainMenu @@ hightlight id_;_1116094_;_script infofile_;_ZIP::ssf529.xml_;_
	Window("Hello Tests").Click 441,296
	'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	'CurrentLanguageTest
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	Window("Hello Tests").Click 244,301 @@ hightlight id_;_1116094_;_script infofile_;_ZIP::ssf562.xml_;_
	'MainMenu @@ hightlight id_;_1116094_;_script infofile_;_ZIP::ssf529.xml_;_
	Window("Hello Tests").Click 441,296
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	'TextureCacheTest
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	Window("Hello Tests").Drag 385,309 @@ hightlight id_;_1116094_;_script infofile_;_ZIP::ssf563.xml_;_
	Window("Hello Tests").Drop 385,33 @@ hightlight id_;_1116094_;_script infofile_;_ZIP::ssf564.xml_;_
	Wait 1
	Window("Hello Tests").Click 241,159 @@ hightlight id_;_1116094_;_script infofile_;_ZIP::ssf565.xml_;_
	'MainMenu @@ hightlight id_;_1116094_;_script infofile_;_ZIP::ssf579.xml_;_
	Window("Hello Tests").Click 441,296
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	'ExtensionsTest
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	Window("Hello Tests").Click 241,197 @@ hightlight id_;_1116094_;_script infofile_;_ZIP::ssf567.xml_;_
	Wait 1
	'NotificationCenterTest
	Window("Hello Tests").Click 235,41 @@ hightlight id_;_1116094_;_script infofile_;_ZIP::ssf568.xml_;_
	Window("Hello Tests").Click 339,166 @@ hightlight id_;_1116094_;_script infofile_;_ZIP::ssf595.xml_;_
	Window("Hello Tests").Click 339,166 @@ hightlight id_;_1116094_;_script infofile_;_ZIP::ssf596.xml_;_
	Window("Hello Tests").Click 113,189 @@ hightlight id_;_1116094_;_script infofile_;_ZIP::ssf598.xml_;_
	'Back
	Window("Hello Tests").Click 429,289 @@ hightlight id_;_1116094_;_script infofile_;_ZIP::ssf569.xml_;_
	Wait 1 @@ hightlight id_;_1116094_;_script infofile_;_ZIP::ssf599.xml_;_
	'CCControlButtonTest
	Window("Hello Tests").Click 238,79 @@ hightlight id_;_1116094_;_script infofile_;_ZIP::ssf570.xml_;_
	Window("Hello Tests").Drag 118,181 @@ hightlight id_;_1116094_;_script infofile_;_ZIP::ssf601.xml_;_
	Window("Hello Tests").Drop 374,189 @@ hightlight id_;_1116094_;_script infofile_;_ZIP::ssf602.xml_;_
	Wait 1
	Window("Hello Tests").Drag 367,179 @@ hightlight id_;_1116094_;_script infofile_;_ZIP::ssf603.xml_;_
	Window("Hello Tests").Drop 76,183 @@ hightlight id_;_1116094_;_script infofile_;_ZIP::ssf604.xml_;_
	Wait 1
	'Back
	Window("Hello Tests").Click 422,293 @@ hightlight id_;_1116094_;_script infofile_;_ZIP::ssf571.xml_;_
	'CocosBuilderTest
	Window("Hello Tests").Click 237,119 @@ hightlight id_;_1116094_;_script infofile_;_ZIP::ssf572.xml_;_
		'Menus_Items @@ hightlight id_;_1116094_;_script infofile_;_ZIP::ssf608.xml_;_
		Window("Hello Tests").Click 137,158 @@ hightlight id_;_1116094_;_script infofile_;_ZIP::ssf609.xml_;_
		Window("Hello Tests").Click 242,157 @@ hightlight id_;_1116094_;_script infofile_;_ZIP::ssf610.xml_;_
		Window("Hello Tests").Click 113,147 @@ hightlight id_;_1116094_;_script infofile_;_ZIP::ssf611.xml_;_
		Window("Hello Tests").Click 23,20 @@ hightlight id_;_1116094_;_script infofile_;_ZIP::ssf612.xml_;_
		'Button
		Window("Hello Tests").Click 132,209 @@ hightlight id_;_1116094_;_script infofile_;_ZIP::ssf613.xml_;_
		Window("Hello Tests").Click 240,149 @@ hightlight id_;_1116094_;_script infofile_;_ZIP::ssf614.xml_;_
		Window("Hello Tests").Drag 255,150 @@ hightlight id_;_1116094_;_script infofile_;_ZIP::ssf615.xml_;_
		Window("Hello Tests").Drop 259,233 @@ hightlight id_;_1116094_;_script infofile_;_ZIP::ssf616.xml_;_
		Window("Hello Tests").Click 23,20 @@ hightlight id_;_1116094_;_script infofile_;_ZIP::ssf612.xml_;_
		'Particle Systems
		Window("Hello Tests").Click 131,261 @@ hightlight id_;_1116094_;_script infofile_;_ZIP::ssf618.xml_;_
		Window("Hello Tests").Click 23,20 @@ hightlight id_;_1116094_;_script infofile_;_ZIP::ssf612.xml_;_
		'Sprites_9 Slice @@ hightlight id_;_1116094_;_script infofile_;_ZIP::ssf621.xml_;_
		Window("Hello Tests").Click 341,161 @@ hightlight id_;_1116094_;_script infofile_;_ZIP::ssf622.xml_;_
		Window("Hello Tests").Click 23,20 @@ hightlight id_;_1116094_;_script infofile_;_ZIP::ssf612.xml_;_
		'Labels
		Window("Hello Tests").Click 345,210 @@ hightlight id_;_1116094_;_script infofile_;_ZIP::ssf626.xml_;_
		Window("Hello Tests").Click 23,20 @@ hightlight id_;_1116094_;_script infofile_;_ZIP::ssf612.xml_;_
		'ScrollViewTest
		Window("Hello Tests").Click 347,259 @@ hightlight id_;_1116094_;_script infofile_;_ZIP::ssf628.xml_;_
		Randomize @@ hightlight id_;_1116094_;_script infofile_;_ZIP::ssf629.xml_;_
		For  Response = 0 To 10
			drag_x = Int((400 * Rnd + 0))
			drag_y = Int((250 * Rnd + 0))
			drop_x = Int((400 * Rnd + 0))
			drop_y = Int((250 * Rnd + 0))
			Window("Hello Tests").Drag drag_x,drag_y
			Window("Hello Tests").Drop drop_x,drop_y
		Next @@ hightlight id_;_1116094_;_script infofile_;_ZIP::ssf579.xml_;_
	Window("Hello Tests").Click 23,20 @@ hightlight id_;_1116094_;_script infofile_;_ZIP::ssf612.xml_;_
 @@ hightlight id_;_1116094_;_script infofile_;_ZIP::ssf588.xml_;_
	'MainMenu @@ hightlight id_;_1116094_;_script infofile_;_ZIP::ssf579.xml_;_
	Window("Hello Tests").Click 441,296
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	'SharderTest
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	Window("Hello Tests").Click 242,239 @@ hightlight id_;_1116094_;_script infofile_;_ZIP::ssf579.xml_;_
	Dim Sharder_i @@ hightlight id_;_3804062_;_script infofile_;_ZIP::ssf580.xml_;_
	For Sharder_i = 1 To 6
		Wait 0.5
		Window("Hello Tests").Click 338,291
	Next	
	Window("Hello Tests").Drag 197,235 @@ hightlight id_;_1116094_;_script infofile_;_ZIP::ssf582.xml_;_
	Window("Hello Tests").Drop 358,236 @@ hightlight id_;_1116094_;_script infofile_;_ZIP::ssf583.xml_;_
	Wait 1
	Window("Hello Tests").Drag 358,236 @@ hightlight id_;_1116094_;_script infofile_;_ZIP::ssf584.xml_;_
	Window("Hello Tests").Drop 78,221 @@ hightlight id_;_1116094_;_script infofile_;_ZIP::ssf585.xml_;_

	Window("Hello Tests").Click 338,291
	'MainMenu
	Window("Hello Tests").Click 441,296
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	'MutiTouchTest
	'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''' @@ hightlight id_;_1116094_;_script infofile_;_ZIP::ssf576.xml_;_
	Window("Hello Tests").Click 240,279 @@ hightlight id_;_4064864_;_script infofile_;_ZIP::ssf507.xml_;_
	Randomize
	For  Response = 0 To 5
		drag_x = Int((400 * Rnd + 0))
		drag_y = Int((250 * Rnd + 0))
		drop_x = Int((400 * Rnd + 0))
		drop_y = Int((250 * Rnd + 0))
		Window("Hello Tests").Drag drag_x,drag_y
		Window("Hello Tests").Drop drop_x,drop_y
	Next @@ hightlight id_;_1116094_;_script infofile_;_ZIP::ssf579.xml_;_
	'MainMenu
	Window("Hello Tests").Click 441,296
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	'Quit
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	Window("Hello Tests").Click 461,22
	'SystemUtil.UnblockInput
end function




