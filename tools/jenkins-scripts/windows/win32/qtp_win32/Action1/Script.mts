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

	 If DIalog("Microsoft Visual C++ Runtime").Exist(3) Then
		 Dialog("Microsoft Visual C++ Runtime").Activate
		 Dialog("Microsoft Visual C++ Runtime").Move 872,177
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

	If Dialog("Microsoft Visual C++ Runtime").Exist(3) Then
		Dialog("Microsoft Visual C++ Runtime").WinButton("中止(A)").Click
	End If
	
End If
Err.Clear
On Error goto 0

Function common_test(a,b,c)
   For i = a To b
		Window("Cocos2dxWin32").Click 338,291
		Wait c
   Next
End Function

Function random_click(a,b,c)
	Dim touch_x,touch_y
	Randomize
	For  Response = a To b
		touch_x = Int((400 * Rnd + 0))
		touch_y = Int((250 * Rnd + 0))
		Window("Cocos2dxWin32").Click touch_x,touch_y
		Wait c
	Next
End Function

Function random_drag(a,b,c)
	Dim drag_x,drag_y,drop_x,drop_y
	Randomize
	For  Response = a To b
		drag_x = Int((400 * Rnd + 0))
		drag_y = Int((250 * Rnd + 0))
		drop_x = Int((400 * Rnd + 0))
		drop_y = Int((250 * Rnd + 0))
		Window("Cocos2dxWin32").Drag drag_x,drag_y
		Window("Cocos2dxWin32").Drop drop_x,drop_y
		Wait c
	Next
End Function

Function CaseFunctionName()
   'SystemUtil.BlockInput
	Window("Cocos2dxWin32").Activate
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	'ActionsTest
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	Window("Cocos2dxWin32").Click 241,43
	Wait 2
	
	Call common_test(1,27,1)
	
	Window("Cocos2dxWin32").Click 338,291
	Wait 5
	Window("Cocos2dxWin32").Click 338,291
	Wait 2
	
	Call common_test(1,5,1)
	'MainMenu
	Window("Cocos2dxWin32").Click 441,296
	Wait 2
	
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	'TransitionsTest
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	Window("Cocos2dxWin32").Click 236,77
	Wait 2
	
	Call common_test(1,26,1)
	Wait 1
	'MainMenu
	Window("Cocos2dxWin32").Click 441,296
	Wait 2
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	'ActionsProgressTest
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	Window("Cocos2dxWin32").Click 287,113
	Wait 2
	
	Call common_test(1,7,2)
	'MainMenu
	Window("Cocos2dxWin32").Click 441,296
	Wait 2
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	'EffectsTest
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	Window("Cocos2dxWin32").Click 236,163
	Wait 3
	
	Call common_test(1,21,4)
	'MainMenu
	Window("Cocos2dxWin32").Click 441,296
	Wait 2
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	'ClickAndMoveTest
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	Window("Cocos2dxWin32").Click 228,199
	Wait 3

	Call random_click(1,10,2)
	
	Call random_click(1,100,0)
	'MainMenu
	Window("Cocos2dxWin32").Click 441,296
	Wait 2
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	'RotateWorldTest
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	Window("Cocos2dxWin32").Click 237,235
	Wait 3.5
	'MainMenu
	Window("Cocos2dxWin32").Click 441,296
	Wait 2
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	'ParticleTest
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	Window("Cocos2dxWin32").Click 236,276
	Wait 3
	
	Call common_test(1,42,2)
	'MainMenu
	Window("Cocos2dxWin32").Click 441,296
	Wait 2
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	'ActionEaseTest
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	Window("Cocos2dxWin32").Drag 363,307
	Window("Cocos2dxWin32").Drop 363,10
	Wait 1
	Window("Cocos2dxWin32").Click 237,19
	Wait 2
	
	Call common_test(1,13,2)
	'MainMenu
	Window("Cocos2dxWin32").Click 441,296
	Wait 2
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	'MotionStreakTest
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	Window("Cocos2dxWin32").Click 240,61
	Wait 2
	
	Window("Cocos2dxWin32").Click 230,239
	Window("Cocos2dxWin32").Click 338,291
	
	Call random_drag(1,10,0)
	Window("Cocos2dxWin32").Click 230,239
	Call random_drag(1,10,0)
	
	Window("Cocos2dxWin32").Click 338,291
	Wait 2
	
	'MainMenu
	Window("Cocos2dxWin32").Click 441,296
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	'DrawPrimitivesTest
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	Window("Cocos2dxWin32").Click 235,101
	Wait 1
	'MainMenu
	Window("Cocos2dxWin32").Click 441,296
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	'NodeTest
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	Window("Cocos2dxWin32").Click 237,139
	Wait 1
	
	Call common_test(1,13,1)
	'MainMenu
	Window("Cocos2dxWin32").Click 441,296
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	'TouchesTest
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	Window("Cocos2dxWin32").Click 238,183
	Window("Cocos2dxWin32").Drag 236,221
	Window("Cocos2dxWin32").Drop 175,226
	
	Wait 5
	'MainMenu
	Window("Cocos2dxWin32").Click 441,296
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	'MenuTest
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	Window("Cocos2dxWin32").Click 234,220
	Window("Cocos2dxWin32").Click 238,63
	Window("Cocos2dxWin32").Click 158,132

	Window("Cocos2dxWin32").Click 238,155
	Window("Cocos2dxWin32").Click 236,180
	Window("Cocos2dxWin32").Click 158,188
	Window("Cocos2dxWin32").Click 313,184
	Window("Cocos2dxWin32").Click 190,217
	Window("Cocos2dxWin32").Click 235,216
	Window("Cocos2dxWin32").Click 205,144
	Window("Cocos2dxWin32").Click 218,143
	Window("Cocos2dxWin32").Click 237,247
	'MainMenu
	Window("Cocos2dxWin32").Click 441,296
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	'ActionManagerTest
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	Window("Cocos2dxWin32").Click 234,261
	
	Call common_test(1,4,3)
	'MainMenu
	Window("Cocos2dxWin32").Click 441,296
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	'LayerTest
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	Window("Cocos2dxWin32").Click 240,302

	Call random_drag(1,10,0)
	Window("Cocos2dxWin32").Click 338,291
	Wait 2
	Window("Cocos2dxWin32").Click 338,291
	Wait 2
	Window("Cocos2dxWin32").Click 338,291
	Call random_drag(1,10,0)
	Window("Cocos2dxWin32").Click 338,291
	Wait 1
	Window("Cocos2dxWin32").Click 242,164
	Wait 1
	Window("Cocos2dxWin32").Click 338,291
	Wait 1
	Window("Cocos2dxWin32").Click 254,163
	Wait 1
	Window("Cocos2dxWin32").Click 338,291
	Wait 1
	Window("Cocos2dxWin32").Click 231,164
	Wait 1
	'MainMenu
	Window("Cocos2dxWin32").Click 441,296
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	'SceneTest
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	Window("Cocos2dxWin32").Drag 370,306
	Window("Cocos2dxWin32").Drop 370,-20
	Wait 1
	Window("Cocos2dxWin32").Click 234,17
	Wait 1
	Window("Cocos2dxWin32").Click 230,111
	Window("Cocos2dxWin32").Click 230,111
	Window("Cocos2dxWin32").Click 230,111
	Window("Cocos2dxWin32").Click 233,163
	Window("Cocos2dxWin32").Click 226,218
	Window("Cocos2dxWin32").Click 226,218
	'MainMenu
	Window("Cocos2dxWin32").Click 441,296
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	'ParallaxTest
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	Window("Cocos2dxWin32").Click 232,55
	Wait 5
	Window("Cocos2dxWin32").Click 338,291

	Call random_drag(1,10,0)
	'MainMenu
	Window("Cocos2dxWin32").Click 441,296
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	'TileMapTest
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	Window("Cocos2dxWin32").Click 233,99
	Wait 2
	Window("Cocos2dxWin32").Click 338,291
	Wait 2

	Call random_drag(1,10,0)
	'MainMenu
	Window("Cocos2dxWin32").Click 441,296
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	'IntervalTest
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	Window("Cocos2dxWin32").Click 235,139
	Wait 3
	Window("Cocos2dxWin32").Click 224,48
	Wait 1
	Window("Cocos2dxWin32").Click 231,52
	Window("Cocos2dxWin32").Click 228,56
	Window("Cocos2dxWin32").Click 228,56
	'MainMenu
	Window("Cocos2dxWin32").Click 441,296
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	'ChipmunkAccelTouchTest
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	Window("Cocos2dxWin32").Click 235,178

	Call random_click(1,20,2)
	'MainMenu
	Window("Cocos2dxWin32").Click 441,296
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	'LabelTest
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	Window("Cocos2dxWin32").Click 239,216
	Wait 3
	Call common_test(1,25,0.5)
	'MainMenu
	Window("Cocos2dxWin32").Click 441,296
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	'TextInputTest
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	Window("Cocos2dxWin32").Click 236,255

	Window("Cocos2dxWin32").Click 238,161
	Const constring = "0123456789abcdefgchijklmnopqrstuvwxyz"
	Dim TextInput_i,TextInput_j,randstring
	Randomize 
	For TextInput_i=1 To 8
		randstring = randstring & Mid(constring, Int(Len(constring)*Rnd)+1, 1)
	Next
	Window("Cocos2dxWin32").Type randstring
	Window("Cocos2dxWin32").Click 338,291
	Window("Cocos2dxWin32").Click 238,161
	Randomize 
	For TextInput_j=1 To 8
		randstring = randstring & Mid(constring, Int(Len(constring)*Rnd)+1, 1)
	Next
	Window("Cocos2dxWin32").Type randstring
	'MainMenu
	Window("Cocos2dxWin32").Click 441,296
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	'SpriteTest
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	Window("Cocos2dxWin32").Click 238,294
	
	Call random_click(1,15,0.2)
	Window("Cocos2dxWin32").Click 338,291
	Call random_click(1,15,0.2)
	Window("Cocos2dxWin32").Click 338,291
	Call common_test(1,108,0.5)
	'MainMenu
	Window("Cocos2dxWin32").Click 441,296
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	'SchdulerTest
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	Window("Cocos2dxWin32").Drag 359,309
	Window("Cocos2dxWin32").Drop 359,-11
	Wait 1
	'Schedule with delay of 3sec,repeat 4
	Window("Cocos2dxWin32").Click 236,15
	Window("Cocos2dxWin32").Click 338,291
	'Scheduler timeScale Test
	Window("Cocos2dxWin32").Drag 260,212
	Window("Cocos2dxWin32").Drop 301,212
	Wait 1
	Window("Cocos2dxWin32").Drag 301,212
	Window("Cocos2dxWin32").Drop 209,214
	Wait 1
	Window("Cocos2dxWin32").Drag 209,214
	Window("Cocos2dxWin32").Drop 100,208
	Wait 2
	Window("Cocos2dxWin32").Click 338,291
	'Two custom schedulers
	Window("Cocos2dxWin32").Drag 126,16
	Window("Cocos2dxWin32").Drop 81,22
	Wait 1
	Window("Cocos2dxWin32").Drag 361,19
	Window("Cocos2dxWin32").Drop 422,22
	Wait 3
	Window("Cocos2dxWin32").Click 338,291
	'Self -remove an scheduler
	Window("Cocos2dxWin32").Click 338,291
	'Pause/Resume
	Window("Cocos2dxWin32").Click 338,291
	'Pause/Resume
	Wait 3
	Window("Cocos2dxWin32").Click 338,291
	'Unschedule All selectors
	Window("Cocos2dxWin32").Click 338,291
	'Unschedule All selectors(HARD)
	Wait 2
	Window("Cocos2dxWin32").Click 338,291
	'Unschedule All selectors
	Wait 4
	Window("Cocos2dxWin32").Click 338,291
	'Schedule from Schedule
	Window("Cocos2dxWin32").Click 338,291
	'Schedule update with priority
	Window("Cocos2dxWin32").Click 338,291
	'MainMenu
	Window("Cocos2dxWin32").Click 441,296
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	'RenderTextureTest
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	Window("Cocos2dxWin32").Click 240,59
	'Save Image

	Call random_drag(1,10,0)
	Window("Cocos2dxWin32").Click 388,17
	Window("Cocos2dxWin32").Click 398,41
	Wait 1
	Window("Cocos2dxWin32").Click 338,291
	'Testing issue #937
	Window("Cocos2dxWin32").Click 338,291
	'Testing Z Buffer in Render Texture
	Call random_click(1,10,0)
	Window("Cocos2dxWin32").Click 338,291
	'Testing depthStencil attachment
	'MainMenu
	Window("Cocos2dxWin32").Click 441,296
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	'Texture2DTest
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	Window("Cocos2dxWin32").Click 234,97
	Call common_test(1,35,0.5)
	'MainMenu
	Window("Cocos2dxWin32").Click 441,296
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	'Box2dTest
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	Window("Cocos2dxWin32").Click 235,134
	Call random_click(1,30,2)
	'MainMenu
	Window("Cocos2dxWin32").Click 441,296
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	'Box2dTestBed
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	Window("Cocos2dxWin32").Click 236,176
	Call common_test(1,35,2)
	'MainMenu
	Window("Cocos2dxWin32").Click 441,296
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	'EffectAdvancedTest
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	Window("Cocos2dxWin32").Click 237,217
	Call common_test(1,5,1)
	'MainMenu
	Window("Cocos2dxWin32").Click 441,296
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	'AccelerometerTest
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	Window("Cocos2dxWin32").Click 244,255
	'MainMenu
	Window("Cocos2dxWin32").Click 441,296
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	'KeypadTest
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	Window("Cocos2dxWin32").Click 240,298
	'MainMenu
	Window("Cocos2dxWin32").Click 441,296
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	'CocosDenshionTest
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	Window("Cocos2dxWin32").Drag 377,314
	Window("Cocos2dxWin32").Drop 377,0
	Wait 1
	Window("Cocos2dxWin32").Click 243,20
	
	Window("Cocos2dxWin32").Click 248,38
	Wait 1 
	Window("Cocos2dxWin32").Click 248,78
	Wait 1
	Window("Cocos2dxWin32").Click 247,121
	Wait 1
	Window("Cocos2dxWin32").Click 246,158
	Wait 1
	Window("Cocos2dxWin32").Click 251,202
	Wait 1
	Window("Cocos2dxWin32").Click 246,238
	Wait 1
	Window("Cocos2dxWin32").Click 241,282
	Wait 1
	Window("Cocos2dxWin32").Drag 427,260
	Window("Cocos2dxWin32").Drop 427,6
	Window("Cocos2dxWin32").Click 232,18
	Wait 1
	Window("Cocos2dxWin32").Click 245,56
	Wait 1
	Window("Cocos2dxWin32").Click 242,109
	Wait 1
	Window("Cocos2dxWin32").Click 242,144
	Wait 1
	Window("Cocos2dxWin32").Click 243,189
	Wait 1
	Window("Cocos2dxWin32").Click 243,230
	Wait 1
	Window("Cocos2dxWin32").Click 254,275
	Wait 1
	Window("Cocos2dxWin32").Click 248,304
	Wait 1
	Window("Cocos2dxWin32").Drag 412,272
	Window("Cocos2dxWin32").Drop 412,-13
	Window("Cocos2dxWin32").Click 235,124
	Wait 1
	Window("Cocos2dxWin32").Click 238,158
	Wait 1
	Window("Cocos2dxWin32").Click 229,200
	Wait 1
	Window("Cocos2dxWin32").Click 239,243
	Wait 1
	Window("Cocos2dxWin32").Click 246,277
	Wait 1
	'MainMenu
	Window("Cocos2dxWin32").Click 441,296
	'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	'PerformanceTest
	'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	Window("Cocos2dxWin32").Click 237,64
	Window("Cocos2dxWin32").Click 238,37

	'PerformanceNodeChildrenTest
	Window("Cocos2dxWin32").Click 238,38
	Dim Performance_i
	For Performance_i = 1 To 4
		Window("Cocos2dxWin32").Click 273,145
		Window("Cocos2dxWin32").Click 338,291
		Wait 1
	Next
	'Back
	Window("Cocos2dxWin32").Click 427,290

	'PerformanceParticeTest
	Window("Cocos2dxWin32").Click 237,78

	For Performance_j = 1 To 4
		Window("Cocos2dxWin32").Click 273,145
		Window("Cocos2dxWin32").Click 338,291
		Wait 1
	Next
	'Back
	Window("Cocos2dxWin32").Click 427,290
	'PerformanceSpriteTest
	Window("Cocos2dxWin32").Click 233,120
	Dim Performance_k
	For Performance_k = 1 To 5
		Window("Cocos2dxWin32").Click 271,64
		Window("Cocos2dxWin32").Click 338,291
		Wait 1
	Next
	'Back
	Window("Cocos2dxWin32").Click 427,290

	'PerformanceTextureTest
	Window("Cocos2dxWin32").Click 229,159
	'Back
	Window("Cocos2dxWin32").Click 427,290

	'PerformanceTouchesTest
	Window("Cocos2dxWin32").Click 234,200
	Call random_drag(1,10,0)
	Window("Cocos2dxWin32").Click 338,291
	Call random_drag(1,10,0)
	'Back
	Window("Cocos2dxWin32").Click 427,290
	'MainMenu
	Window("Cocos2dxWin32").Click 441,296
	'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	'ZwoptexTest
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	Window("Cocos2dxWin32").Click 233,104
	Wait 1
	'MainMenu
	Window("Cocos2dxWin32").Click 441,296
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	'CurlTest
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	Window("Cocos2dxWin32").Click 239,141
	Window("Cocos2dxWin32").Click 242,160
	'MainMenu
	Window("Cocos2dxWin32").Click 441,296
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	'UserDefaultTest
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	Window("Cocos2dxWin32").Click 238,184
	'MainMenu
	Window("Cocos2dxWin32").Click 441,296
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	'BugsTest
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	Window("Cocos2dxWin32").Click 240,222
	'MainMenu
	Window("Cocos2dxWin32").Click 441,296
	'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	'FontTest
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	Window("Cocos2dxWin32").Click 237,261
	Call common_test(1,4,0.5)
	'MainMenu
	Window("Cocos2dxWin32").Click 441,296
	'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	'CurrentLanguageTest
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	Window("Cocos2dxWin32").Click 244,301
	'MainMenu
	Window("Cocos2dxWin32").Click 441,296
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	'TextureCacheTest
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	Window("Cocos2dxWin32").Drag 385,309
	Window("Cocos2dxWin32").Drop 385,33
	Wait 1
	Window("Cocos2dxWin32").Click 241,159
	'MainMenu
	Window("Cocos2dxWin32").Click 441,296
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	'ExtensionsTest
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	Window("Cocos2dxWin32").Click 241,197
	Wait 1
	'NotificationCenterTest
	Window("Cocos2dxWin32").Click 235,41
	Window("Cocos2dxWin32").Click 339,166
	Window("Cocos2dxWin32").Click 339,166
	Window("Cocos2dxWin32").Click 113,189
	'Back
	Window("Cocos2dxWin32").Click 429,289
	Wait 1
	'CCControlButtonTest
	Window("Cocos2dxWin32").Click 238,79
	Window("Cocos2dxWin32").Drag 118,181
	Window("Cocos2dxWin32").Drop 374,189
	Wait 1
	Window("Cocos2dxWin32").Drag 367,179
	Window("Cocos2dxWin32").Drop 76,183
	Wait 1
	'Back
	Window("Cocos2dxWin32").Click 422,293
	'CocosBuilderTest
	Window("Cocos2dxWin32").Click 237,119
		'Menus_Items
		Window("Cocos2dxWin32").Click 137,158
		Window("Cocos2dxWin32").Click 242,157
		Window("Cocos2dxWin32").Click 113,147
		Window("Cocos2dxWin32").Click 23,20
		'Button
		Window("Cocos2dxWin32").Click 132,209
		Window("Cocos2dxWin32").Click 240,149
		Window("Cocos2dxWin32").Drag 255,150
		Window("Cocos2dxWin32").Drop 259,233
		Window("Cocos2dxWin32").Click 23,20
		'Particle Systems
		Window("Cocos2dxWin32").Click 131,261
		Window("Cocos2dxWin32").Click 23,20
		'Sprites_9 Slice
		Window("Cocos2dxWin32").Click 341,161
		Window("Cocos2dxWin32").Click 23,20
		'Labels
		Window("Cocos2dxWin32").Click 345,210
		Window("Cocos2dxWin32").Click 23,20
		'ScrollViewTest
		Window("Cocos2dxWin32").Click 347,259
		Call random_drag(1,10,0)
	Window("Cocos2dxWin32").Click 23,20

	'MainMenu
	Window("Cocos2dxWin32").Click 441,296
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	'SharderTest
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	Window("Cocos2dxWin32").Click 242,239
	Dim Sharder_i
	Call common_test(1,6,0.5)
	Window("Cocos2dxWin32").Drag 197,235
	Window("Cocos2dxWin32").Drop 358,236
	Wait 1
	Window("Cocos2dxWin32").Drag 358,236
	Window("Cocos2dxWin32").Drop 78,221

	Window("Cocos2dxWin32").Click 338,291
	'MainMenu
	Window("Cocos2dxWin32").Click 441,296
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	'MutiTouchTest
	'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	Window("Cocos2dxWin32").Click 240,279
	Call random_drag(1,5,0)
	'MainMenu
	Window("Cocos2dxWin32").Click 441,296
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	'Quit
	''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	Window("Cocos2dxWin32").Click 461,22
	'SystemUtil.UnblockInput
End function
