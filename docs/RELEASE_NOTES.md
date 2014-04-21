# cocos2d-x v3.0 Release Notes #

**Table of Contents**  *generated with [DocToc](http://doctoc.herokuapp.com/)*

- [cocos2d-x v3.0 Release Notes](#user-content-cocos2d-x-v30-release-notes)
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
- [Highlights of v3.0](#user-content-highlights-of-v30)
- [Features in detail](#user-content-features-in-detail)
	- [C++11 features](#user-content-c11-features)
		- [std::function](#user-content-stdfunction)
		- [Strongly typed enums](#user-content-strongly-typed-enums)
		- [override](#user-content-override)
	- [Removed Objective-C patterns](#user-content-removed-objective-c-patterns)
		- [No more 'CC' prefix for C++ classes and free functions](#user-content-no-more-cc-prefix-for-c-classes-and-free-functions)
		- [clone() instead of copy()](#user-content-clone-instead-of-copy)
		- [Singletons use getInstance() and destroyInstance()](#user-content-singletons-use-getinstance-and-destroyinstance)
		- [Object is replaced with Ref](#user-content-object-is-replaced-with-ref)
		- [getters](#user-content-getters)
		- [POD types](#user-content-pod-types)
	- [New Renderer](#user-content-new-renderer)
		- [Renderer features](#user-content-renderer-features)
			- [Auto-batching](#user-content-auto-batching)
			- [Auto-culling](#user-content-auto-culling)
			- [Global Z order](#user-content-global-z-order)
		- [Sprite vs. SpriteBatchNode](#user-content-sprite-vs-spritebatchnode)
	- [Improved LabelTTF / LabelBMFont / LabelAtlas](#user-content-improved-labelttf--labelbmfont--labelatlas)
	- [New EventDispatcher](#user-content-new-eventdispatcher)
	- [Physics Integration](#user-content-physics-integration)
- [Misc API Changes](#user-content-misc-api-changes)
	- [ccTypes.h](#user-content-cctypesh)
	- [deprecated functions and  global variables](#user-content-deprecated-functions-and--global-variables)
- [Changes in the Lua bindings](#user-content-changes-in-the-lua-bindings)
	- [Use bindings-generator tool for lua binding](#user-content-use-bindings-generator-tool-for-lua-binding)
		- [Bind the classes with namespace to lua](#user-content-bind-the-classes-with-namespace-to-lua)
		- [Use ScriptHandlerMgr to manage the register and unregister of Lua function](#user-content-use-scripthandlermgr-to-manage-the-register-and-unregister-of-lua-function)
	- [Misc API changes](#user-content-misc-api-changes-1)
		- [Use cc、ccs、ccui gl and sp as module name](#user-content-use-ccccsccui-gl-and-sp-as-module-name)
		- [Modified functions](#user-content-modified-functions)
		- [Add some modules](#user-content-add-some-modules)
		- [Add more lua bindings](#user-content-add-more-lua-bindings)
		- [Replace some lua-bindings of Class or Struct with lua table](#user-content-replace-some-lua-bindings-of-class-or-struct-with-lua-table)
		- [Support lua script codes call Object-C codes and Java codes](#user-content-support-lua-script-codes-call-object-c-codes-and-java-codes)
		- [Add some lua files to store the constants of different modules](#user-content-add-some-lua-files-to-store-the-constants-of-different-modules)

# Misc Information

* Download: http://cdn.cocos2d-x.org/cocos2d-x-3.0beta.zip
* Full Changelog: https://github.com/cocos2d/cocos2d-x/blob/cocos2d-x-3.0beta/CHANGELOG
* API Reference: http://www.cocos2d-x.org/reference/native-cpp/V3.0beta/index.html

# Requirements

## Runtime Requirements

* Android 2.3 or newer
* iOS 5.0 or newer
* OS X 10.7 or newer
* Windows 7 or newer
* ~~Windows Phone 8 or newer~~ N/A for the moment
* Linux Ubuntu 12.04 (or newer)
* ~~Browsers via Emscripten~~ N/A for the moment

## Compiler Requirements

* Xcode 4.6 (for iOS or Mac)
* gcc 4.7 for Linux or Android. For Android ndk-r9 or newer is required.
* Visual Studio 2012 (for Windows)

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

Please refer to [ReadMe](../README.md). And there is a [document](https://github.com/chukong/cocos-docs/blob/master/manual/framework/native/getting-started/v3.0/how-to-start-a-new-game/en.md) for it.
    

# Highlights of v3.0

* Replaced Objective-C patterns with C++ (C++11) patterns and best practices
* Improved Labels
* Improved renderer (much faster than in v2.2!!)
* New Event Dispatcher
* Physics integration
* New UI objects
* [JavaScript remote debugger](https://github.com/cocos2d/cocos-docs/blob/master/manual/framework/native/scripting/javascript/js-remote-debugger/en.md)
* Remote Console support
* Use [cocos console](https://github.com/cocos2d/cocos2d-console) to create and run project
* Refactor Image - release memory in time and uniform the api of supported file format
* Automatically generated Lua bindings, add LuaJavaBridge and LuaObjcBridge
* Templated containers
    * `CCDictionary` is replaced by `cocos2d::Map<>`, [usage](https://github.com/cocos2d/cocos-docs/blob/master/manual/framework/native/data-structure/v3/map/en.md)
    * `CCArray` is replaced by `cocos2d::Vector<>`, [usage](https://github.com/cocos2d/cocos-docs/blob/master/manual/framework/native/data-structure/v3/vector/en.md)
    * `CCBool`, `CCFLoat`, `CCDouble` are replaced with `cocos2d::Value`, [usage](https://github.com/cocos2d/cocos-docs/blob/master/manual/framework/native/data-structure/v3/value/en.md)

# Features in detail

## C++11 features

_Feature added in v3.0-pre-alpha0_

A subset of C++11 features are being used in cocos2d-x:

* `std::function`, including lambda objects for callbacks
* strongly typed enums, for most of the cocos2d-x enums and constants
* `std::thread` for threading
* `override` and `final` context keywords, for overriden and final methods


### std::function

* `CallFunc` can be created with an `std::function<void()>`
* `CallFuncN` can be created with an `std::function<void(Node*)>`
* `CallFuncND` and `CallFuncO` were removed since it can be created with simulated with `CallFuncN` and `CallFunc`. See ActionsTest.cpp for more examples
* `MenuItem` supports `std::function<void(Node*)>` as callbacks

`CallFunc` example:

```cpp
// in v2.1
CCCallFunc *action1 = CCCallFunc::create( this, callfunc_selector( MyClass::callback_0 ) );

// in v3.0 (short version)
auto action1 = CallFunc::create( CC_CALLBACK_0(MyClass::callback_0,this));
auto action2 = CallFunc::create( CC_CALLBACK_0(MyClass::callback_1,this, additional_parameters));

// in v3.0 (long version)
auto action1 = CallFunc::create( std::bind( &MyClass::callback_0, this));
auto action2 = CallFunc::create( std::bind( &MyClass::callback_1, this, additional_parameters));

// in v3.0 you can also use lambdas or any other "Function" object
auto action1 = CallFunc::create(
                 [&](){
                     auto s = Director::sharedDirector()->getWinSize();
                     auto label = LabelTTF::create("called:lambda callback", "Marker Felt", 16);
                     label->setPosition(ccp( s.width/4*1,s.height/2-40));
                     this->addChild(label);
                 }  );
```

`MenuItem` example:

```cpp
// in v2.1
CCMenuItemLabel *item = CCMenuItemLabel::create(label, this, menu_selector(MyClass::callback));

// in v3.0 (short version)
auto item = MenuItemLabel::create(label, CC_CALLBACK_1(MyClass::callback, this));

// in v3.0 (long version)
auto item = MenuItemLabel::create(label, std::bind(&MyClass::callback, this, std::placeholders::_1));

// in v3.0 you can use lambdas or any other "Function" object
auto item = MenuItemLabel::create(label,
                 [&](Object *sender) {
                     // do something. Item "sender" clicked
                  });
```

### Strongly typed enums

_Feature added in v3.0-pre-alpha0_

Constants and enums that started with `k`, and that usually were defined as `int` or as simple `enum` where replaced with strongly typed enums ( `enum class` ) to prevent collisions and type errors.
The new format is:

    | v2.1       | v3.0        |
    | kTypeValue | Type::VALUE |

Examples:

	| v2.1                             | v3.0                             |
	| kCCTexture2DPixelFormat_RGBA8888 | Texture2D::PixelFormat::RGBA8888 |
	| kCCDirectorProjectionCustom      | Director::Projection::CUSTOM     |
	| ccGREEN                          | Color3B::GREEN                   |
	| CCPointZero                      | Point::ZERO                      |
	| CCSizeZero                       | Size::ZERO                       |

The old values can still be used, but are deprecated.

### override

To catch possible errors while overriding methods, subclasses with override methods have the `override` context keyword.
Example:
```cpp
class Sprite : public Node {
    bool isFlipY(void) const;
    void setFlipY(bool bFlipY);

    // Overrides
    virtual void setTexture(Texture2D *texture) override;
    virtual Texture2D* getTexture() const override;
    inline void setBlendFunc(const BlendFunc &blendFunc) override;
    inline const BlendFunc& getBlendFunc() const override;
}
```

## Removed Objective-C patterns

_Feature added in v3.0-pre-alpha0_

### No more 'CC' prefix for C++ classes and free functions

*Changes in classes*

Since cocos2d-x already uses the `cocos2d` namespace, there is not need to add the prefix `CC` to all its classes.

Examples:

	| v2.1       | v3.0     |
	| CCSprite   | Sprite   |
	| CCNode     | Node     |
	| CCDirector | Director |
	| etc...                |

v2.1 class names are still available, but they were tagged as deprecated.

*Changes in free functions*

For the *drawing primitives*:
* They were added in the `DrawPrimitives` namespace
* The `cc` prefix was removed

For the *gl proxy functions*:
* They were added in the `GL` namespace
* The `ccGL` prefix was removed

Examples:

	| v2.1                | v3.0                         |
	| ccDrawPoint()       | DrawPrimitives::drawPoint()  |
	| ccDrawCircle()      | DrawPrimitives::drawCircle() |
	| ccGLBlendFunc()     | GL::blendFunc()              |
	| ccGLBindTexture2D() | GL::bindTexture2D()          |
	| etc...                       				          |

v2.1 free functions are still available, but they were tagged as deprecated.


### clone() instead of copy()

`clone()` returns an autoreleased version of the copy.

`copy()` is no longer supported. If you use it, it will compile, but the code will crash.

Example:
```cpp
// v2.1
CCMoveBy *action = (CCMoveBy*) move->copy();
action->autorelease();

// v3.0
// No need to do autorelease, no need to do casting.
auto action = move->clone();
```

### Singletons use getInstance() and destroyInstance()

All singletons use `getInstance()` and `destroyInstance()` (if applicable) to get and destroy the instance.

Examples:

	| v2.1                          | v3.0                        |
	| CCDirector->sharedDirector()  | Director->getInstance()     |
	| CCDirector->endDirector()     | Director->destroyInstance() |
	| etc...                                                      |


v2.1 methods are still available, but they were tagged as deprecated.

### Object is replaced with Ref

Because the name `Object` is confused, so rename it to `Ref`, and remove functions that are not related with reference count. All classes that inherit from `Object` now inherit from `Ref`.

### getters

Getters now use the `get` prefix.

Examples:

	| v2.1                            | v3.0* 				 		       |
	| node->boundingBox()             | node->getBoundingBox() 			   |
	| sprite->nodeToParentTransform() | sprite->getNodeToParentTransform() |
	| etc...                                                               |

And getters were also tagged as `const` in their declaration. Example:

```cpp
// v2.1
virtual float getScale();

// v3.0
virtual float getScale() const;
```

v2.1 methods are still available, but they were tagged as deprecated.

### POD types

Methods that were receiving POD types as arguments (eg: `TexParams`, `Point`, `Size`, etc.) are being passed as `const` reference.

Example:
```cpp
// v2.1
void setTexParameters(ccTexParams* texParams);

// v3.0
void setTexParameters(const ccTexParams& texParams);
```


## New Renderer

_Feature added in v3.0-beta and improved in v3.0-beta2_

The way currently cocos2d-x v2.2 does rendering is OK but it is difficult to optimize, difficult to add new functionality and difficult to port to new platforms.
So cocos2d-x v3.0 has a new renderer that is more performing, elegant, scalable, flexible but still simple to use and to understand. Also existing cocos2d-x users will find the new API familiar and they will feel immediately comfortable with, without having to bother about what’s changed or what's new under the hood.

Features of the new renderer:

- It has been decoupled from the Scene Graph. The `draw()` method, instead of "drawing" it sends a `RenderCommand` to the `Renderer`, and `Renderer` is responsible for drawing the queued `RenderCommand` commands.
- `QuadCommands` (used by `Sprite` and `ParticleSystem` objects) will be automatically batched.
- `CustomCommand` objects allow the user to use custom OpenGL code, using a API similar to v2.2
- `GroupCommand` objects allow to have "stacks" in the Renderer with different OpenGL values.
- Auto-culling for `Sprite` objects (although, technically, Auto-culling is not performed in `Renderer` code, but in the `Sprite` code)
- Global Z ordering (local Z ordering is still supported)

For detailed information, please read the following doc: [Renderer Specification document](https://docs.google.com/document/d/17zjC55vbP_PYTftTZEuvqXuMb9PbYNxRFu0EGTULPK8/edit)

### Renderer features

#### Auto-batching

Auto-batching means that the `Renderer` will package "multiple draw calls" in just one "big draw call" (AKA batch). In order to group "draw calls" certain conditions are needed:

- It only works with `QuadCommand` commands (used by Sprite and ParticleSystem objects)
- The `QuadCommands` must share the same Material ID: same Texture ID, same GLProgram and same blending function
- The `QuadCommands` must consecutive 

If those conditions are met, the `Renderer` will create create a batch (one draw call) with all those `QuadCommand` objects.

In case you are unfamiliar with the OpenGL best practices, batching is very important to have decent speed in your games. The less batches (draw calls) the more performance your game is going to be.

#### Auto-culling

For the moment auto-culling is only implemented on `Sprite` objects.

When the method `Sprite::draw()` is called, it will check if the `Sprite` is outside the screen. If so, it won't send the `QuadCommand` command to the `Renderer`, and thus, it will gain some performance.


#### Global Z order

A new method called `setGlobalZOrder()` / `getGlobalZOrder()` was added to `Node`, and the old methods `setZOrder()` / `getZOrder()` were renamed to `setLocalZOrder()` / `getLocalZOrder()`.

`globalZOrder` receives a `float` (and not an `int`) as argument. And this value is used to sort the `RenderCommand` objects in the `Renderer`. Lower values have higher priority over higher values. That means that a Node with a `globalZOrder` of `-10` is going to be drawn BEFORE a Node with `globalZOrder` of `10`.

Nodes that have a `globalZOrder` of `0` (default value) will be drawn according to the Scene Graph order.

If the `globalZOrder` is not changed, cocos2d-x v3.0 will behave exactly as cocos2d-x v2.2.

__`globalZOrder()` vs. `localZOrder()`__:

* `globalZOrder` is used to sort the "draw commands" in the `Renderer`
* `localZOrder` is used to sort the `Node` objects in its parent's children Array

__Exceptions__:

TODO

### Sprite vs. SpriteBatchNode

In v2.2 the recommended way to have good performance was to parent `Sprite` objects to a `SpriteBatchNode` object.
Although the performance was (is still) very good by using `SpriteBatchNode` objects, they had (still have) some limitations like:

- `Sprite` objects can only have `Sprite` objects as children (if not, cocos2d-x will raise an Assert)
    - You cannot add a `ParticleSystem` as a child of `Sprite`, when the `Sprite` is parented to a `SpriteBatchNode`
    - As a consequence of that, you cannot use `ParallaxNode` with `Sprites` parented to `SpriteBatchNode`
- All `Sprite` objects must share the same TextureId (if not, cocos2d-x will raise an Assert)
- `Sprite` objects use the `SpriteBatchNode`'s blending function and shader.


And although v3.0 still supports `SpriteBatchNode` (with the same features and limitations), we no longer encourage its usage. Instead, we recommend to use `Sprite` objects without parenting them to a `SpriteBatchNode`.

But in order to have a very good performance in v3.0, you have to make sure that your `Sprite` objects:

- Share the same TextureId (place them in a spritesheet, like if you were using a `SpriteBatchNode`)
- Make sure all of them use the same shader and blending function (like if you were using a `SpriteBatchNode`)

If you do so, the `Sprites` will perform almost as fast as to using `SpriteBatchNode`... (about 10% slower on old devices. On newer devices the difference is almost imperceptible)

The big differences between v2.2 and v3.0 are:

- `Sprite` objects can have different Texture IDs. 
- `Sprite` objects can have any kind of `Node` as children, including `ParticleSystem`. 
- `Sprite` objects can have different blending functions and use different shaders. 

But if you do that, the `Renderer` might not be able to batch all its children (less performant). But the game will keep running, without raising any Assert.

__To summarize__:

- Keep putting all your sprites in a big spritesheet
- Use the same Blending Function (just use the default one)
- Use the same Shader (just use the default one)
- And don't parent your sprites to a `SpriteBatchNode`

Only use `SpriteBatchNode` as the last resort, when you really need an extra (although minor) boost in performance (and you are OK with its limitations).


## Improved LabelTTF / LabelBMFont / LabelAtlas

_Feature added in v3.0-alpha0_

`LabelTTF`, `LabelBMFont` and `LabelAtlas` will be replaced by new `Label`. The benefits of new `Label` are:

* uniform api to create `LabelTTF`, `LabelBMFont` and `LabelAtlas`
* use `freetype` to generate texture for labels, which make sure that labels have the same effect on different platforms
* will cache textures to improve performance

## New EventDispatcher

_Feature added in v3.0-alpha0_

All events such as touch event, keyboard event, acceleration event and custom event are dispatched by `EventDispatcher`.
`TouchDispatcher`, `KeypadDispatcher`, `KeyboardDispatcher`, `AccelerometerDispatcher` were removed.

Features of `EventDispatcher` are:

* dispatch events based on rendering sequence
* all events are dispatched by `EventDispatcher`
* can use `EventDispatcher` to dispatch custom events
* can register a lambda as call back function

Detail information of `EventDispatcher` can refer to [this document](https://github.com/cocos2d/cocos-docs/blob/master/manual/framework/native/input/event-dispatcher/en.md).

## Physics Integration

_Feature added in v3.0-pre-alpha0_

In v3.0, we integrate physics engine into cocos2d-x based on [Chipmunk2D](https://chipmunk-physics.net/). By using this feature, you can create physics based games without understanding physics engine.

More detail information of this feature, please refer to [this document](https://github.com/cocos2d/cocos-docs/blob/master/manual/framework/native/physics/physics-integration/en.md)


# Misc API Changes

## `ccTypes.h`

Remove *cc* prefix for structure names in ccTypes.h, move global functions into static member functions, and move global constants into const static member variables.

	| v2.1 struct names       | v3.0 struct names |
	| ccColor3B 	          | Color3B |
	| ccColor4B 		      | Color4B |
	| ccColor4F 		      | Color4F |
	| ccVertex2F 		      | Vertex2F |
	| ccVertex3F 		      | Vertex3F |
	| ccTex2F 			      | Tex2F |
	| ccPointSprite 	      | PointSprite |
	| ccQuad2 			      | Quad2 |
	| ccQuad3 			      | Quad3 |
	| ccV2F_C4B_T2F 	      | V2F_C4B_T2F |
	| ccV2F_C4F_T2F 	      | V2F_C4F_T2F |
	| ccV3F_C4B_T2F 	      | V3F_C4B_T2F |
	| ccV2F_C4B_T2F_Triangle  | V2F_C4B_T2F_Triangle |
	| ccV2F_C4B_T2F_Quad      | V2F_C4B_T2F_Quad |
	| ccV3F_C4B_T2F_Quad      | V3F_C4B_T2F_Quad |
	| ccV2F_C4F_T2F_Quad      | V2F_C4F_T2F_Quad |
	| ccBlendFunc 		      | BlendFunc |
	| ccT2F_Quad 		      | T2F_Quad |
	| ccAnimationFrameData    | AnimationFrameData |

Global functions changed example
```c++
// in v2.1
ccColor3B color3B = ccc3(0, 0, 0);
ccc3BEqual(color3B, ccc3(1, 1, 1));
ccColor4B color4B = ccc4(0, 0, 0, 0);
ccColor4F color4F = ccc4f(0, 0, 0, 0);
color4F = ccc4FFromccc3B(color3B);
color4F = ccc4FFromccc4B(color4B);
ccc4FEqual(color4F, ccc4F(1, 1, 1, 1));
color4B = ccc4BFromccc4F(color4F);

color3B = ccWHITE;

// in v3.0
Color3B color3B = Color3B(0, 0, 0);
color3B.equals(Color3B(1, 1, 1));
Color4B color4B = Color4B(0, 0, 0, 0);
Color4F color4F = Color4F(0, 0, 0, 0);
color4F = Color4F(color3B);
color4F = Color4F(color4B);
color4F.equals(Color4F(1, 1, 1, 1));
color4B = Color4B(color4F);

color3B = Color3B::WHITE;
```

## deprecated functions and  global variables

	| v2.1 names 	| v3.0 names |
	| ccp 			| Point |
	| ccpNeg 		| Point::- |
	| ccpAdd 		| Point::+ |
	| ccpSub 		| Point::- |
	| ccpMult 		| Point::* |
	| ccpMidpoint 	| Point::getMidpoint |
	| ccpDot 		| Point::dot |
	| ccpCrosss 	| Point::cross |
	| ccpPerp 		| Point::getPerp |
	| ccpRPerp 		| Point::getRPerp |
	| ccpProject 	| Point::project |
	| ccpRotate 	| Point::rotate |
	| ccpUnrotate 	| Point::unrotate |
	| ccpLengthSQ 	| Point::getLengthSq() |
	| ccpDistanceSQ | Point::getDistanceSq |
	| ccpLength 	| Point::getLength |
	| ccpDistance 	| Point::getDistance |
	| ccpNormalize 	| Point::normalize |
	| ccpForAngle 	| Point::forAngle |
	| ccpToAngle 	| Point::getAngle |
	| ccpClamp 		| Point::getClampPoint |
	| ccpFromSize 	| Point::Point |
	| ccpCompOp		| Point::compOp |
	| ccpLerp 		| Point::lerp |
	| ccpFuzzyEqual | Point::fuzzyEqual |
	| ccpCompMult 	| Point::Point |
	| ccpAngleSigned | Point::getAngle |
	| ccpAngle 		| Point::getAngle |
	| ccpRotateByAngle | Point::rotateByAngle |
	| ccpLineInersect | Point::isLineIntersect |
	| ccpSegmentIntersect | Point::isSegmentIntersect |
	| ccpIntersectPoint | Point::getIntersectPoint |
	| CCPointMake	| Point::Point |
	| CCSizeMake	| Size::Size |
	| CCRectMake 	| Rect::Rect |
	| PointZero 	| Point::ZERO |
	| SizeZero 		| Size::ZERO |
	| RectZero 		| Rect::ZERO |
	| TiledGrid3DAction::tile | TiledGrid3DAction::getTile |
	| TiledGrid3DAction::originalTile | TiledGrid3DAction::getOriginalTile |
	| TiledGrid3D::tile | TiledGrid3D::getTile |
	| TiledGrid3D::originalTile | TiledGrid3D::getOriginalTile |
	| Grid3DAction::vertex | Grid3DAction::getVertex |
	| Grid3DAction::originalVertex | Grid3DAction::getOriginalVertex |
	| Grid3D::vertex | Grid3D::getVertex |
	| Grid3D::originalVertex | Grid3D::getOriginalVertex |
	| Configuration::sharedConfiguration | Configuration::getInstance |
	| Configuration::purgeConfiguration | Configuration::destroyInstance() |
	| Director::sharedDirector() | Director::getInstance() |
	| FileUtils::sharedFileUtils | FileUtils::getInstance |
	| FileUtils::purgeFileUtils | FileUtils::destroyInstance |
	| GLView::sharedOpenGLView | GLView::getInstance |
	| ShaderCache::sharedShaderCache | ShaderCache::getInstance |
	| ShaderCache::purgeSharedShaderCache | ShaderCache::destroyInstance |
	| AnimationCache::sharedAnimationCache | AnimationCache::getInstance |
	| AnimationCache::purgeSharedAnimationCache | AnimationCache::destroyInstance |
	| SpriteFrameCache::sharedSpriteFrameCache | SpriteFrameCache::getInstance |
	| SpriteFrameCache:: purgeSharedSpriteFrameCache | SpriteFrameCache::destroyInstance |
	| NotificationCenter::sharedNotificationCenter | NotificationCenter::getInstance |
	| NotificationCenter:: purgeNotificationCenter | NotificationCenter::destroyInstance |
	| Profiler::sharedProfiler | Profiler::getInstance |
	| UserDefault::sharedUserDefault | UserDefault::getInstance |
	| UserDefault::purgeSharedUserDefault | UserDefault::destroyInstance |
	| Application::sharedApplication | Application::getInstance |
	| ccc3() 		| Color3B() |
	| ccc3BEqual() 	| Color3B::equals() |
	| ccc4() 		| Color4B() |
	| ccc4FFromccc3B() | Color4F() |
	| ccc4f() 		| Color4F() |
	| ccc4FFromccc4B() | Color4F() |
	| ccc4BFromccc4F() | Color4B() |
	| ccc4FEqual() 	| Color4F::equals() |
	| ccWHITE 		| Color3B::WHITE |
	| ccYELLOW 		| Color3B::YELLOW |
	| ccBLUE 		| Color3B::BLUE |
	| ccGREEN 		| Color3B::GREEN |
	| ccRED 		| Color3B::RED |
	| ccMAGENTA 	| Color3B::MAGENTA |
	| ccBLACK 		| Color3B::BLACK |
	| ccORANGE 		| Color3B::ORANGE |
	| ccGRAY 		| Color3B::GRAY |
	| kBlendFuncDisable | BlendFunc::BLEND_FUNC_DISABLE |

# Changes in the Lua bindings

## Use bindings-generator tool for lua binding

Only have to write an ini file for a module, don't have to write a lot of .pkg files

### Bind the classes with namespace to lua

In previous, the lua binding can not bind classes that have the same class name but different namespaces. In order to resolve this issue, now the metatable name of a class is changed. For example, `CCNode` will be changed to `cc.Node`. This modification will affect some APIs as follows:

	|           v2.x                   |                  v3.0             |
	| tolua_usertype(tolua_S,"CCNode") | tolua_usertype(tolua_S,"cc.Node") |
	| tolua_isusertable(tolua_S,1,"CCNode",0,&tolua_err 		| tolua_isusertable(tolua_S,1,"cc.Node",0,&tolua_err  |
	| tolua_isusertype(tolua_S,1,"CCNode",0,&tolua_err) 		| tolua_isusertype(tolua_S,1,"cc.Node",0,&tolua_err)  |
	| toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCNode") 		| toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"cc.Node")  |
	| tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCFileUtils") 		| tolua_pushusertype(tolua_S,(void*)tolua_ret,"cc.FileUtils")  |
	| tolua.cast(pChildren[i + 1], "CCNode") 			| tolua.cast(pChildren[i + 1], "cc.Node") |

### Use ScriptHandlerMgr to manage the register and unregister of Lua function

When we want to add register and unregister functions of Lua function for class, we need to change the declarative and defined files and then bind to Lua.
In v3.0, we use the `ScriptHandlerMgr`. As an example, lets see the `MenuItem` class:
In the 2.x version, we needed to add a declaration in the MenuItem header file:
```c++
 virtual void registerScriptTapHandler(int nHandler);
 virtual void unregisterScriptTapHandler(void);
```
then implement them in the .cpp file. In the Lua script ,we use it as follow:
```lua
menuItem:registerScriptTapHandler(luafunction)
```

In v3.0 version, we only need to add the `HandlerType` enum in the `ScriptHandlerMgr`, and the implementation in luascript as follow:
```lua
ScriptHandlerMgr:getInstance():registerScriptHandler(menuItem, luafunction,cc.HANDLERTYPE_MENU_CLICKED)
```

## Misc API changes

### Use `cc`、`ccs`、`ccui` `gl` and `sp` as module name

Now classes are bound into different modules instead of using global module. This will avoid conflicts with other codes.

* classes in `cocos2d`、`cocos2d::extension`、`CocosDenshion` and `cocosbuilder`  were bound to `cc` module
* classes in `cocos2d::ui` were bound to `ccui` module
* classes in `spine` were bound to `sp` module
* classes in `cocostudio` were bound to `ccs` module
* global variables are bound to corresponding modules
* all funcionts and constants about `openGl` were bound to `gl` module

Examples:

    | v2.1                    | v3.0                    |
    | CCDirector              | cc.Director             |
    | CCArmature              | ccs.Armature            |
    | kCCTextAlignmentLeft    | cc.kCCTextAlignmentLeft |

### Modified functions

Some global function names are renamed:

Examples:

    | v2.1                    | v3.0                    |
    | CCPoint/ccp             | cc.p                    |
    | CCRect                  | cc.rect                 |
    | CCColor3B               | cc.c3b                  |
    | CCColor4B               | cc.c4b                  |
    | CCColor4F               | cc.c4f                  |

### Add some modules

In the version 3.0, more modules were bound to lua, specific as follows:

* physics
* spine
* XMLHttpRequest
* OpenGL
 
The `XMLHttpRequest` and `physics` are in the `cc` module, the `spine` is in the `sp` module, and the `OpenGL` is in the `gl` module. Related test cases located in:

* physics   ---> TestLua/PhysicsTest
* spine     ---> TestLua/SpineTest
* XMLHttpRequest ---> TestLua/XMLHttpRequestTest
* openGL    ---> TestLua/OpenGLTest

### Add more lua bindings
Such as: New Label、New EventDispatcher and AssetsManager,etc.Related test cases located in:

* New Label ---> TestLua/LabelTestNew
* New EventDispatcher --->TestLua/NewEventDispatcherTest
* AssetsManager  ---> TestLua/AssetsManagerTest

### Replace some lua-bindings of Class or Struct with lua table
In the version 3.0, all the lua-binding of Struct type were replaced with the lua table

Examples:
 
    | v2.1                    | v3.0                    |
    | CCPoint                 | lua table               |
    | CCRect                  | lua table               |
    | CCColor3B               | lua table               |
    | CCColor4B               | lua table               |
    | CCColor4F               | lua table               |
    | CCAffineTransform       | lua table               |
    | CCArray                 | lua table               |    
    | CCDictionary            | lua table               |
    | CCPointArray            | lua table               |
    
### Support lua script codes call Object-C codes and Java codes 
`LuaObjcBridge` and `LuaJavaBridge` bound to lua supported lua script codes calls Object-C codes and java codes.
    
### Add some lua files to store the constants of different modules

* Cocos2DConstants.lua store the constants of `cc` module
* StudioConstants.lua store the constants of  `ccs` module
* GuiConstants.lua store the constants of `ccui` module
* OpenglConstants.lua store the constants of `gl` module
