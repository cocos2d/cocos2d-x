# cocos2d-x v3.1 Release Notes #

**Table of Contents**  *generated with [DocToc](http://doctoc.herokuapp.com/)*

- [Misc Information](#user-content-misc-information)
- [Requirements](#user-content-requirements)
	- [Runtime Requirements](#user-content-runtime-requirements)
	- [Compiler Requirements](#user-content-compiler-requirements)
	- [How to run tests](#user-content-how-to-run-tests)
	- [How to start a new game](#user-content-how-to-start-a-new-game)
- [Highlights of v3.1](#user-content-highlights-of-v31)
- [Features in detail](#user-content-features-in-detail)
	- [Sprite3D](#user-content-sprite3d)
	- [Improved Shader Subsystem](#user-content-improved-shader-subsystem)
	- [New math library](#user-content-new-math-library)
	- [New UIVideoPlayer](#user-content-new-uivideoplayer)
	- [UI navigation](#user-content-ui-navigation)
	- [Improved folder structure](#user-content-improved-folder-structure)
	- [Particle System fixes](#user-content-particle-system-fixes)
- [Misc API Changes](#user-content-misc-api-changes)
	- [deprecated functions and  global variables](#user-content-deprecated-functions-and--global-variables)

# Misc Information

* Download: http://cdn.cocos2d-x.org/cocos2d-x-3.1rc0.zip
* Full Changelog: https://github.com/cocos2d/cocos2d-x/blob/cocos2d-x-3.1rc0/CHANGELOG
* ~~API Reference: http://www.cocos2d-x.org/reference/native-cpp/V3.0/index.html~~
* v3.0 Release Notes can be found here: [v3.0 Release Notes](https://github.com/cocos2d/cocos2d-x/blob/cocos2d-x-3.0/docs/RELEASE_NOTES.md)

# Requirements

## Runtime Requirements

* Android 2.3 or newer
* iOS 5.0 or newer
* OS X 10.7 or newer
* Windows 7 or newer
* Windows Phone 8 or newer
* Linux Ubuntu 12.04 or newer
* ~~Browsers via Emscripten~~ N/A for the moment

## Compiler Requirements

* Xcode 4.6 or newer for iOS or Mac
* gcc 4.7 or newer for Linux
* gcc 4.7 and ndk-r9 or newer for Android
* Visual Studio 2012  or newer for Windows (win32)
* Visual Studio 2012  or newer for Windows Phone 8

## How to run tests

### Mac OSX & iOS

* Enter `cocos2d-x/build` folder, open `cocos2d_test.xcodeproj`
* Select `iOS` or `OS X` target in scheme toolbar
* Click `run` button

### Android

You can run the samples...

**Using command line:**

    $ cd cocos2d-x
    $ ./setup.py
    $ cd build
    $ ./android-build.py cpp-empty-test -p 10
    $ adb install cocos2d-x/tests/cpp-empty-test/proj.android/bin/CppEmptyTest-debug.apk
    
Then click item on Android device to run tests. Available value of `-p` is the API level, cocos2d-x supports from level 10.

**Using Eclipse:**

    $ cd cocos2d-x
    $ ./setup.py
    $ cd build
    $ ./android-build.py cpp-empty-test -p 10
    
Then

* Import cocos2d-x Android project into Eclipse, the path used to import is `cocos/2d/platform/android`
* Import `cpp-empty-test` Android project into Eclipse, the path used to import is `tests/cpp-empty-test/proj.android`
* Build `cpp-empty-test` Android project and run

### Windows

* Enter `cocos2d-x/build`, and open `cocos2d-win32.vs2012.sln`
* Select `cpp-empty-test` as running target
* Click run button


### Linux

    $ cd cocos2d-x/build
    $ ./install-deps-linux.sh
    $ cd ../..
    
Then

    $ mkdir build
    $ cd build
    $ cmake ../cocos2d-x
    $ make -j4
    
Run

    $ cd bin/cpp-empty-test
    $ ./cpp-empty-test
    
## How to start a new game

Please refer to this document: [ReadMe](../README.md)

# Highlights of v3.1

* `Sprite3D`, a new node to render 3D models
* Improved Shader subsystem
* New, unified, math library
* `ui::VideoPlayer`, a new node to play videos


# Features in detail

## Sprite3D

cocos2d-x v3.0 replaced `Node`'s 2x3 transform matrix with a 4x4 one. This feature allows you to transform any node in a 3d space.

`Sprite3D` allows users to render a 3d model inside cocos2d. And since cocos2d-x already has 4x4 transform matrix, it is possible to move scale and rotate the `Sprite3D` in the x, y, and z axis.

The API is like `Sprite`:

```c++
// v3.1 only supports the Wavefront file format
auto sprite3d = Sprite3D::create("mymodel.obj");

// if the material is not specified in .obj, you can override it with:
auto sprite3d = Sprite3D::create("mymodel.obj", "texture.png");

// Since Sprite3D is a regular node, you can add it into the scene like any other node
scene->addChild(sprite3d);
sprite3d->setRotation3D(Vec3(x,y,z));
```

## Improved Shader Subsystem

In order to support `Sprite3D`, we refactored our shader subsystem. The result is that we have an easier to use, yet more powerful shader system that can be used both for 2D and 3D.


In v3.0, the class `GLProgram` was used both for holdin the _OpenGL program_ (shader), and also the shader state (uniforms and attributes).

That design had one big constraint: In order to add or remove an attribute or uniform, you had to subclass `GLProgram`.

In v3.1, we decoupled the shader state from the shader. We added the `GLProgramState` class which holds the attributes and uniforms.

The API is the following:

```c++
auto glprogram = GLProgram::create(...);

// it will automatically parse all the attributes and uniforms
// used by glprogram, and it will populate the glprogramstate dictionary
// with them
auto glprogramstate = GLProgramState::create( glprogram );

// How to set a uniform for Vec2 (Int, Texture, Vec3, Vec4, Mat4, are all supported)
glprogramstate->setUniformVec2("u_my_uniform", Vec2(x,y));
// or how to set it using a callback
glprogramstate->setUniformCallback("u_my_uniform", [](Uniform*uniform){
    // do something
});

// How to set an attribute
glprogramstate->setVertexAttribPointer("a_my_attrib", 4, GL_FLOAT, GL_FALSE, 0, vertex);
// or how to set it using a callback
glprogramstate->setVertexAttribCallback("a_my_attrib", [](VertexAttrib*attrib){
    // do something
 });
```

By using this API it is possible to change the effect on a `Sprite3D` (or even an `Sprite`) without subclassing any cocos2d class!

Possible examples:

 - Outline / Shadow / Glow effects
 - Multi-texturing effects
 - Sepia, Grey or other color effects
 - and more
 
For a complete example, please see the [Shader - Sprite](https://github.com/cocos2d/cocos2d-x/blob/cocos2d-x-3.1rc0/tests/cpp-tests/Classes/ShaderTest/ShaderTest2.cpp) and [Shader - Basic](https://github.com/cocos2d/cocos2d-x/blob/cocos2d-x-3.1rc0/tests/cpp-tests/Classes/ShaderTest/ShaderTest.cpp) examples.



## New math library

cocos2d-x v1.0 only supported 2D features. So it made sense to use a 2x3 Transform matrix for the operations.

In cocos2d-x v2.0 we added OpenGL ES 2.0 support (no more built-in OpenGL matrix operations) so it made sense to use [Kazmath](https://github.com/Kazade/kazmath), a math library that replaced the OpenGL ES 1.0 functionality. Kazmath was used internally, and most of the users never used the Kazmath API at all.

In cocos2d-x v3.0 we refactored the renderer and we exposed a bit more the Kazmath API to the users.

And in v3.1, with `Sprite3D` we needed to expose even more the the Kazmath API. And it no longer made sense to have multiple math libraries inside cocos2d-x.

The problems were:

 * Part of the code was using the old 2D math library
 * Part of the code was using Kazmath
 * Part of the code was using ad-hoc math code
 
The goal was to use only one math library for cocos2d-x, with the following requirements:
 * Easy to use, easy to mantain
 * Proven
 * In C++ if possible
  
So we took the [GamePlay3D](http://gameplay3d.org/) math library, we did some minor changes, and the cocos2d-x math code with it.

How to use it:

```c++
// vector2
Vec2 vec2(10,20);
Vec2 other2(30,40);
auto ret = vec2.cross(other2);
auto ret2 = vec2 + other2;
auto ret3 = vec3 * scalar;

node->setPosition(vec2);

// vector3
Vec3 vec3(30,40,50);
node->setPosition3D(vec3);

// vector4
Vec4 vec4 = Vec4::ZERO;

// Matrix 4x4
auto identity = Mat4::IDENTITY;
node->setNodeToParentTransform(identity);
```

The good news is that the old API still works since we `typedef` the old classes and structs to the new math classes.


## New UIVideoPlayer

v3.1 has a new `Node` to play videos. The API is:


```c++
// VideoPlayer is under the "experimental" namespace since
// it only works for iOS and Android, and we might change its 
// API in the future
auto videoPlayer = cocos2d::experimental::ui::VideoPlayer::create();
videoPlayer->setContentSize(Size(x,y));
videoPlayer->setURL("http://example.com/video.mp4");  
//you could also play a local video file as follows:
//videoPlayer->setFileName("filepath/video.mp4");
videoPlayer->play();
```


## UI navigation

3.1 supports focus navigation of UI widget which is very useful for OTT manufacturer.

###Usage
Suppose that your screen has 3 widgets layout horizontally. We could define it like this:

```c++
HBox(widget1, widget2, widget3)
```

If you want the `widget1` to get focused, you could call

```c++
widget1->setfocused(true)
```

If you want to move the focus to the next widget, you could just call

```c++
widget1->findNextFocusedWidget(Widget::FocusDirection::RIGHT, _firstFocusedWidget);
```

When the focus goes to `widget3`, if you call 

```c++
widget3->findNextFocusedWidget(Widget::FocusDirection::RIGHT, _firstFocusedWidget);
```
, the focus will stay there only when you call `HBox->setLoopFocus()` then the focus will move to `widget1` again.

**Note:**

The HBox and VBox could be nested in any ways and all the widgets should be added into the HBox/VBox if you want them to be focused later.

When a focus moves from one widget to another, it will trigger a *focus event*. You could add the following code to handle these event:

```c++
auto eventListener = EventListenerFocus::create();
eventListener->onFocusChanged = CC_CALLBACK_2(UIFocusTestBase::onFocusChanged, this);
eventDispatcher->addEventListenerWithFixedPriority(_eventListener, 1);
``` 

The onFocusChanged callback, when the widget lose focus, we change its color to white, when the widget get focus, we change its color to red. You could add more complex animations to them when focus change happens.

```c++
void UIFocusTestBase::onFocusChanged(cocos2d::ui::Widget *widgetLostFocus, cocos2d::ui::Widget *widgetGetFocus)
{
    Layout *getLayout = dynamic_cast<Layout*>(widgetGetFocus);
    if (!getLayout && widgetGetFocus && widgetGetFocus->isFocusEnabled()) {
        widgetGetFocus->setColor(Color3B::RED);
    }
    Layout *loseLayout = dynamic_cast<Layout*>(widgetLostFocus);
    if (!loseLayout && widgetLostFocus && widgetLostFocus->isFocusEnabled()) {
        widgetLostFocus->setColor(Color3B::WHITE);
    }
}
```
For more usage information, please refer to [this file](https://github.com/cocos2d/cocos2d-x/blob/v3/tests/cpp-tests/Classes/UITest/CocoStudioGUITest/UIFocusTest/UIFocusTest.cpp) for more information.


###Limitations
Only Layout type `HORIZONTAL` and `VERTICAL` is supported which means we could not treat Scrollview and PageView as a base layout.

The following layouts:

```c++
HBox(VBox, ScrollView(HBox(VBox, VBox, VBox)))
VBox(HBox, PageView(VBox(HBox,HBox))))
```
 are not supported yet, we will implement it in cocos2d-x v3.2.
 
 If you want to achieve the focus movement in scrollview, you could use a normal VBox or HBox to layout elements and call `setFocusEnabled(true/false)` manually to skip the unwanted widgets.
  
## Improved folder structure

In v3.0 we started a folder re-organization for cocos2d-x. Unfortunately we didn't have the time to finish it on time.

In v3.1 we finished the folder re-organization, and it looks like this:

    cocos/: includes cocos2d.cpp and other build files
    cocos/2d/: includes base nodes, 2d nodes and related objects like Node, Scene, Sprite, etc.
    cocos/3d/: includes 3d nodes and related objects like Sprite3D
    cocos/audio/: sound and music related objects
    cocos/math/: math related objects
    cocos/platform/: platform specific objects
    cocos/renderer/: GPU related objects like Renderer, Texture2D, Render Commands, etc.
    cocos/physcis/: physics related objects
    cocos/network/: network retlated objects
    cocos/editor-support/: 3rd party editors file format

## Particle System fixes

cocos2d-x v3.0 and earlier versions had a bug in `ParticleSystem` where the the Y-flipped parameter was not calculated correctly.

We fixed that bug in v3.1. The problem is that fixing this bug breaks backward compatiblility in particles that were relying on the broken behavior.

In order to try to make the transition easier to v3.1, we created a tool that fixes the broken particle system files. How to use it:

    # Will convert broken .plist files into fixed ones.
    # Will generate a backup file of the converted files
    $ cocos/tools/particle/convert_YCoordFlipped.py *.plist


# Misc API Changes

## deprecated functions and  global variables

TODO: The old Math API
