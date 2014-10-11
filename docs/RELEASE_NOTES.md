# cocos2d-x v3.3beta0 Release Notes #

**Table of Contents**  *generated with [DocToc](http://doctoc.herokuapp.com/)*

- [cocos2d-x v3.3beta0 Release Notes](#user-content-cocos2d-x-v33beta0-release-notes)
- [Misc Information](#user-content-misc-information)
- [Requirements](#user-content-requirements)
	- [Runtime Requirements](#user-content-runtime-requirements)
	- [Compiler Requirements](#user-content-compiler-requirements)
	- [How to run tests](#user-content-how-to-run-tests)
		- [Mac OSX & iOS](#user-content-mac-osx--ios)
		- [Android](#user-content-android)
		- [Windows](#user-content-windows)
		- [Linux](#user-content-linux)
	- [How to start a new game](#user-content-how-to-start-a-new-game)
- [Highlights of v3.3beta0](#user-content-highlights-of-v33beta0)
- [Features in detail](#user-content-features-in-detail)
	- [Camera](#user-content-camera)
	- [Reskin](#user-content-reskin)
	- [Attachment](#user-content-attachment)
	- [Better support for FBX](#user-content-better-support-for-fbx)
	- [New fbx-conv](#user-content-new-fbx-conv)
	- [AABB, OBB and Ray](#user-content-aabb-obb-and-ray)
	- [BillBoard](#user-content-billboard)
	- [Primitive](#user-content-primitive)
	- [Triangles command](#user-content-triangles-command)
	- [WebView](#user-content-webview)
	- [New audio](#user-content-new-audio)
	- [Only two libraries left](#user-content-only-two-libraries-left)

# Misc Information

* Full Changelog: https://github.com/cocos2d/cocos2d-x/blob/cocos2d-x-3.3alpha0/CHANGELOG
* v3.0 Release Notes can be found here: [v3.0 Release Notes](https://github.com/cocos2d/cocos2d-x/blob/cocos2d-x-3.0/docs/RELEASE_NOTES.md)

# Requirements

## Runtime Requirements

* Android 2.3 or newer
* iOS 5.0 or newer
* OS X 10.7 or newer
* Windows 7 or newer
* Windows Phone 8 or newer
* Linux Ubuntu 14.04 or newer
* ~~Browsers via Emscripten~~ N/A for the moment

## Compiler Requirements

* Xcode 5.1 or newer for iOS or Mac
* gcc 4.9 or newer for Linux
* ndk-r9d for Android
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

# Highlights of v3.3beta0

* 3d: `Camera`, 'Reskin', 'Attachment', 'Better support for FBX', 'New fbx-conv', `AABB`, `OBB`, `Ray` and `BillBoard`
* audio: new audio is added on iOS and Android
* DrawNode: added as many functions as `DrawPrimitive`, and `DrawPrimitive` is deprecated
* Primitive: Support Points, Lines and Triagles for rendering
* Renderer: added `trianle command`
* UI: added `WebView` on iOS and Android
* Only two libraries in cocos2d-x, one for c++ codes, another one for lua-binding codes
* Many other small features added and many bugs fixed

# Features in detail

## Camera

This version of camera is powerful then previous one. And you can add it as a child anywhere. If you want to let a Node to be visited by a camera, Node's camera mask should include Camera's flag:

```c++
// let sprite to be visited by a camera
auto sprite = Sprite::create("myFile.png");
sprite->setCameraMask(CameraFlag::USER1);
auto camera = Camera::createPerspective(60, winSize.width/winSize.height, 1, 1000);
camera->setCameraFlag(CameraFlag::USER1);
scene->addChild(camera);
```

If you have many Nodes that want to be visited by a camera, there is a convenient way:

```c++
auto layer = Layer::create();
auto sprite1 = Sprite::create();
auto sprite2 = Sprite::create();
layer->addChild(sprite1);
layer->addChild(sprite2);
// it will set camera mask for all its children
layer->setCameraMask(CameraFlg::USER1); 

auto camera = Camera::createPerspective();
camera->setCameraFlag(CameraFlag::USER1);
scene->addChild(camera);
```

Full test case please  refer to `tests/cpp-tests/res/Camera3DTest/Camera3DTest.cpp`.

## Reskin

It is a powerful feature, all the user change the appearance of character.

For example, there a model named girl.c3b, which has two coats, coat0 and coat1. 
The character's coat can be changed like this,

```c++
//load the girl from file
auto sprite3d = Sprite3D::create("girl.c3b");
//get the mesh named coat0
auto mesh0 = sprite3d->getMeshByName("coat0");
//you can change texture of this mesh if you like
mesh0->setTexture("cloth.png");
//you can change visibility for this mesh, too
mesh0->setVisible(true);
//hide coat1
auto mesh1 = sprite3d->getMeshByName("coat1");
mesh1->setVisible(false);
```

Full test case please refer to `tests/cpp-tests/Classes/Spret3DTest/Sprite3DTest.cpp`.

## Attachment

Allows to attach a node to a bone

Usage,

```c++
auto sprite = Sprite3D::create("girl.c3b");
auto weapon = Sprite::create("weapon.c3b");
auto attachNode = sprite->getAttachNode("left_hand");
attachNode->addChild(weapon);
```

Full test case please refer to `tests/cpp-tests/Classes/Spret3DTest/Sprite3DTest.cpp`.

## Better support for FBX

support multiple mesh
support multiple material
bones bind to each mesh limited to 40. But the FBX model can contain more meshes. So the model can contain much more bones.

## New fbx-conv

It can export more complex model, which contains multiple meshes and multiple materials.

## AABB, OBB and Ray

AABB means Axis Aligned Bounding Box
OBB means Oriented Bounding Box
Ray has a origin position and direction

Each Sprite3D or Mesh has its own AABB.
AABB and OBB can be picked by Ray.

Usage,

```c++
//get ray from camera
Vec3 nearP(location.x, location.y, -1.0f), farP(location.x, location.y, 1.0f); 
auto size = Director::getInstance()->getWinSize();
camera->unproject(size, &nearP, &nearP);
camera->unproject(size, &farP, &farP);
ray._origin = nearP;
ray._direction = farP - nearP;
ray.intersects(sprite3d->getAABB( ) );
```

Full test case please refer to `tests/cpp-tests/Classes/Spret3DTest/Sprite3DTest.cpp`.

## BillBoard

`BillBoard` is a rectangle always faces to the camera. It is useful in the 3D world. People use BillBoard to create trees in some racing games. It looks real, but the cost is much lower than 3d tree.

`BillBoard` inherits from Sprite, so it also supports animate. Here is example of creating BillBoard.

```c++
//create billboard from .png
auto billboard = BillBoard::create("Images/Icon.png");
addChild(billboard);

//create camera that is looking at this billboard. Otherwise, it is seen by the default camera
auto camera = Camera::createPerspective(60, (GLfloat)s.width/s.height, 1, 1000);
camera->setCameraFlag(CameraFlag::CAMERA_USER1);
addChild(camera); //add this camera

//This billboard is only seen by the camera with flag CameraFlag::CAMERA_USER1.
billboard->setCameraMask((unsigned short)CameraFlag::CAMERA_USER1);
```


## Primitive

`Primitive` is added to support `Points`,`Lines`,`Triangles` rendering. Previously, if we want to draw a custom geometry(sphere, line), we can only do this by using `CustomCommand`. Now, what is need is to create a Primitive, set datas, and use the corresponding `PrimitiveCommand` to draw the Primitive. 

Here is a simple example of rendering a quad in `Sprite`.

1. create verexBuffer

```c++
auto vertexBuffer = VerexBuffer::create(sizeof(V3F_C4B_T2F), 4);
vertexBuffer->updateVertices(&_quad, 4, 0);
```

2. create vertexData

```c++
auto vertexData = VertexData::create();
vertexData->addStream(vertexBuffer, VertexStreamAttribute(0, VERTEX_ATTRIB_POSITION, GL_FLOAT, 3, fasle));
vertexData->addStream(vertexBuffer, VertexStreamAttribute(12, VERTEX_ATTRIB_COLOR, GL_UNSIGNED_BTYE, 4, true));
vertexData->addStream(vertexBuffer, VertexStreamAttribute(16, VERTEX_ATTRIB_TEX_COORD, GL_FLOAT, 2, fasle));
	```
3. create IndexBuffer
	
```c++
auto indexBuffer = IndexBuffer::create(IndexType::INDEX_TYPE_SHORT_16, 6);
short indices[6] = {0,1,2,3,2,1};
indexBuffer->updateIndices(indices,6, 0);
```
4. create primitive
	
```c++
auto primitve = Primitive::create(vertexData, indexBuffer, GL_TRIANGLES);
primitive->setStart(0);
primitive->setCount(6);
```
5. add command to renderer
	
```c++
_command->init(globalZorder,textureID, glprogramState, blend, primitve, modelViewMatrix);
renderer->addCommand(&_command);
```

Primitive supports three typs of primitives (POINTS, LINES, TRIANGLES), vertex and index sharing, multiple streams. It has some constrains:

1. The size of vertex and index Buffer is fixed, which means data must be pre allocated.

2. Batching is not supported.

## Triangles command

We have enhanced auto batching feature by introduce `TrianglesCommand`, the rendering of the `Triangles` can be auto batched. Now if we have anything which can be rendered by `Triangles`, we can use `TrianglesCommand` or inherit from `TrianglesCommand` to take use of auto batching feature and gain rendering improvements. The `QuadCommand`, which is used for `Quad` rendering, is a good example of inheriting from `TrianglesCommand`.

The step to use Triangle Command is very simple.

```
	Triangles trs{verts, indices, vertCount, indexCount};
	command->init(globalZOrder,textureID, glProgramState,blend,trs,matrix);
	renderer->addCommand(command);
```
To improve performance, `Triangles` will hold a weak reference to the vertices and indices data to be rendered, which is the same like `QuadCommand`. The userer should not release any rendered data before the `Command` is executed by `Renderer`.

## WebView
WebView is an new widget type which allows you to display web content inside Cocos2D-X. We only provide iOS and Android implementation currently, more platform might be added in the future.

The class is under `cocos2d::ui::experimental` namespace.

As we clarified the `experimental` namespace before, the `experimental` namespace doesn't mean the widget is incomplete, but only due to the lack of full platform support. Feel free to use the WebView
widget in your game.

To display the website Google in a WebView, we could simply write:

```cpp
    _webView = cocos2d::experimental::ui::WebView::create();
    _webView->setPosition(winSize/2);
    _webView->setContentSize(winSize * 0.5);
    _webView->loadUrl("http://www.google.com");
    _webView->setScalesPageToFit(true);
```

The `setscalesPageToFit` method will adjust the WebView content to fit the content size you set.

We could also set some callback to the WebView:

```cpp
    //we should check the validation of the URL and decide whether to continue or not
    _webView->shouldStartLoading = CC_CALLBACK_2(WebViewTest::onWebViewShouldStartLoading, this);
    //called when web page is finish loading
    _webView->didFinishLoading = CC_CALLBACK_2(WebViewTest::onWebViewDidFinishLoading, this);
    //called when web page is fail loading
    _webView->didFailLoading = CC_CALLBACK_2(WebViewTest::onWebViewDidFailLoading, this);
```

For full test case, please refer to [WebViewTest](https://github.com/cocos2d/cocos2d-x/blob/v3/tests/cpp-tests/Classes/UITest/CocoStudioGUITest/UIWebViewTest/UIWebViewTest.cpp)


## New audio

New audio is more powerful than old one, and it is not compatible with old one. We will deprecated old one when new audio is ready on all supported platforms. Now it only supports iOS and Android. We plan to finish it on v3.4.

What's enhanced in new audio engine:

* can play more than one backgournd music
* can have a call back when an audio(music or effect) finishs
* can get duration of an audio
* can get/set playback position of a playing audio
* can change loop state when playing

The difference compared to old audio engine

* all functions are static, which means you can more easy to invoke function, such as `Audio::play2d()`
* there is only one method `play2d()` to play music or effect
* should use `Audio::getState()` to determine an audio is playing, paused
* its class name is `cocos2d::experimental::AudioEngine` in c++, and its module name is `ccexp.AudioEngine` in lua-binding
* there is not preload function, you can play an audio immediately

Full test case please refer to `tests/cpp-tests/Classes/NewAudioEngineTest/NewAudioEngineTest.cpp`.


## Only two libraries left

Now there are two libraries left: one for all c++ codes and another one for lua-bindings codes. 

If you are developing with c++, you only have to link to `libcocos2d`. `libcocos2d` includes all c++ codes:

* cocos2d(including 2d and 3d)
* network
* cocosstudio
* ui
* cocosbuilder
* spine
* chipmunk
* box2d
* ...

Not used codes will be stripped by linker.

If you are developing with lua, you should link to `libcocos2d` and `libluacocos2d`. You can comment codes in `lua_module_register.h` if you don't want to some module.

```c++
int lua_module_register(lua_State* L)
{
    register_cocosdenshion_module(L); // comment this line to remove cocosdenshion
    register_network_module(L);       // comment this line to remove network
    register_cocosbuilder_module(L);  // comment this line to remove cocosbuilder
    register_cocostudio_module(L);    // comment this line to remove cocostudio
    register_extension_module(L);     // comment this line to remove extension
    register_ui_moudle(L);            // comment this line to remove ui
    register_spine_module(L);         // comment this line to remove spine
    register_cocos3d_module(L);       // comment this line to remove 3d
    return 1;
}
```
