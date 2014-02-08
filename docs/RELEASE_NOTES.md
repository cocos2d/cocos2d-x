# cocos2d-x v3.0 Release Notes #

**Table of Contents**  *generated with [DocToc](http://doctoc.herokuapp.com/)*

- [cocos2d-x v3.0 Release Notes](#cocos2d-x-v30-release-notes)
- [Misc Information](#misc-information)
- [Requirements](#requirements)
	- [Runtime Requirements](#runtime-requirements)
	- [Compiler Requirements](#compiler-requirements)
- [Highlights of v3.0.0](#highlights-of-v300)
- [Features in detail](#features-in-detail)
	- [C++11 features](#c++11-features)
		- [std::function](#stdfunction)
		- [strongly typed enums](#strongly-typed-enums)
		- [override](#override)
	- [Removed Objective-C patterns](#removed-objective-c-patterns)
		- [No more 'CC' prefix for C++ classes and free functions](#no-more-'cc'-prefix-for-c++-classes-and-free-functions)
		- [clone() instead of copy()](#clone-instead-of-copy)
		- [Singletons use getInstance() and destroyInstance()](#singletons-use-getinstance-and-destroyinstance)
		- [getters](#getters)
		- [POD types](#pod-types)
	- [New renderer](#new-renderer)
	- [Improved LabelTTF / LabelBMFont](#improved-labelttf--labelbmfont)
	- [New EventDispatcher](#new-eventdispatcher)
		- [Adding Touch Event Listener](#adding-touch-event-listener)
		- [Adding Mouse Event Listener](#adding-mouse-event-listener)
		- [Adding A Keyboard Event Listener](#adding-a-keyboard-event-listener)
		- [Adding An Acceleration Event Listener](#adding-an-acceleration-event-listener)
		- [Adding A Custom Event Listener](#adding-a-custom-event-listener)
		- [Dispatching A Custom Event](#dispatching-a-custom-event)
		- [Setting Fixed Priority For A Listener](#setting-fixed-priority-for-a-listener)
		- [Removing Event Listener](#removing-event-listener)
			- [Removing A Specified Event Listener](#removing-a-specified-event-listener)
			- [Removing Custom Event Listener](#removing-custom-event-listener)
			- [Removing All Listeners For Specified Event Listener Type](#removing-all-listeners-for-specified-event-listener-type)
			- [Removing All Listeners](#removing-all-listeners)

	- [Physics Integration](#physics-integration)
		- [PhysicsWorld](#physicsworld)
		- [PhysicsBody](#physicsbody)
		- [PhysicsShape](#physicsshape)
		- [PhysicsJoint](#physicsjoint)
		- [PhysicsContact](#physicscontact)
- [Misc API Changes](#misc-api-changes)
	- [`ccTypes.h`](#cctypesh)
	- [deprecated functions and  global variables](#deprecated-functions-and--global-variables)
	- [Changes in the Lua bindings](#changes-in-the-lua-bindings)
		- [Use bindings-generator tool for lua binding](#use-bindings-generator-tool-for-lua-binding)
		- [Bind the classes with namespace to lua](#bind-the-classes-with-namespace-to-lua)
		- [Use ScriptHandlerMgr to manage the register and unregister of lua function](#use-scripthandlermgr-to-manage-the-register-and-unregister-of-lua-function)
		- [Use "cc" and "ccs" as module name](#use-cc-and-ccs-as-module-name)
		- [Deprecated funtions, tables and classes](#deprecated-funtions-tables-and-classes)
		- [Use the lua table instead of the some structs and classes binding](#use-the-lua-table-instead-of-the-some-structs-and-classes-binding)
		- [Integrate more modules into lua](#integrate-more-modules-into-lua)
	- [Known issues](#known-issues)

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
* ~~Marmalade~~ N/A for the moment
* ~~BlackBerry~~ N/A for the moment

## Compiler Requirements

* Xcode 4.6 (for iOS or Mac)
* gcc 4.7 for Linux or Android. For Android ndk-r9 or newer is required.
* Visual Studio 2012 (for Windows)

# Highlights of v3.0

* Replaced Objective-C patters with C++ (C++11) patterns and best practices
* Improved Labels
* Improved renderer
* New Event Dispatcher
* Physics integration
* New GUI
* JavaScript remote debugger
* Remote Console support
* Refactor Image - release memory in time and uniform the api of supported file format
* Automatically generated Lua bindings, add LuaJavaBridge and LuaObjcBridge
* Templated containers

# Features in detail

## C++11 features

_Feature added in v3.0-pre-alpha0_

A subset of C++11 features are being used in cocos2d-x:

* `std::function`, including lambda objects for callbacks
* strongly typed enums, for most of the cocos2d-x enums and constants
* `std::thread` for threading
* `override` context keyword, for overriden methods


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
```c++
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

### strongly typed enums

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

The old values can still be used, but are not deprecated.

### override

To catch possible errors while overriding methods, subclasses with override methods have the `override` context keyword.
Example:
```c++
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
	| etc...                       						 |

v2.1 free functions are still available, but they were tagged as deprecated.


### clone() instead of copy()

`clone()` returns an autoreleased version of the copy.

`copy()` is no longer supported. If you use it, it will compile, but the code will crash.

Example:
```c++
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

### getters

Getters now use the `get` prefix.

Examples:

	| v2.1                            | v3.0* 				 		       |
	| node->boundingBox()             | node->getBoundingBox() 			   |
	| sprite->nodeToParentTransform() | sprite->getNodeToParentTransform() |
	| etc...                                                               |

And getters were also tagged as `const` in their declaration. Example:

```c++
// v2.1
virtual float getScale();

// v3.0
virtual float getScale() const;
```

v2.1 methods are still available, but they were tagged as deprecated.

### POD types

Methods that were receiving POD types as arguments (eg: `TexParams`, `Point`, `Size`, etc.) are being passed as `const` reference.

Example:
```c++
// v2.1
void setTexParameters(ccTexParams* texParams);

// v3.0
void setTexParameters(const ccTexParams& texParams);
```


## New Renderer

_Feature added in v3.0-beta and improved in v3.0-beta2_

The renderer functionality has been decoupled from the Scene graph / Node logic. A new object called `Renderer` is responsible for rendering the object.

Auto-batching ~~and auto-culling~~ support has been added.

Please, see this document for detail information about its internal funcitonality: [Renderer Specification document](https://docs.google.com/document/d/17zjC55vbP_PYTftTZEuvqXuMb9PbYNxRFu0EGTULPK8/edit)

### Renderer features

#### Auto-batching

TODO

#### Auto-culling

TODO

#### Global Z order

A new method called `setGlobalZOrder()` / `getGlobalZOrder()` was added to `Node`, and the old  methods `setZOrder()` / `getZOrder()` were renamed to `setLocalZOrder()` / `getLocalZOrder()`.

`globalZOrder` receives a `float` (and not an `int`) as argument. And this value is used to sort the Nodes in the Renderer. Lower values have higher priority over higher values. That means that a Node with a `globalZOrder` of `-10` is going to be drawn BEFORE a Node with `globalZOrder` of `10`.

Nodes that have a `globalZOrder` of `0` (default value) will be drawn according to the Scene Graph order.

So, if the `globalZOrder` is not changed, cocos2d-x v3.0 will behave exaclty as cocos2d-x v2.2. 

__`globalZOrder()` vs. `localZOrder()`__:

* `globalZOrder` is used to sort the "draw commands" in the Renderer
* `localZOrder` is used to sort the Node in its parent's children Array

__Exceptions__:

TODO


## Improved LabelTTF / LabelBMFont

_Feature added in v3.0-alpha0_

## New EventDispatcher

_Feature added in v3.0-alpha0_

All events like touch event, keyboard event, acceleration event and custom event are dispatched by `EventDispatcher`.
`TouchDispatcher`, `KeypadDispatcher`, `KeyboardDispatcher`, `AccelerometerDispatcher` were removed.

### Adding Touch Event Listener

For TouchOneByOne:
```c++
auto sprite = Sprite::create("file.png");
...
auto listener = EventListenerTouchOneByOne::create();
listener->setSwallowTouch(true);
listener->onTouchBegan     = [](Touch* touch, Event* event) { do_some_thing();  return true;  };
listener->onTouchMoved     = [](Touch* touch, Event* event) { do_some_thing();  };
listener->onTouchEnded     = [](Touch* touch, Event* event) { do_some_thing();  };
listener->onTouchCancelled = [](Touch* touch, Event* event) { do_some_thing();  };
// The priority of the touch listener is based on the draw order of sprite
EventDispatcher::getInstance()->addEventListenerWithSceneGraphPriority(listener, sprite);
// Or the priority of the touch listener is a fixed value
EventDispatcher::getInstance()->addEventListenerWithFixedPriority(listener, 100); // 100 is a fixed value
```

For TouchAllAtOnce
```c++
auto sprite = Sprite::create("file.png");
...
auto listener = EventListenerTouchAllAtOnce::create();
listener->onTouchesBegan     = [](const std::vector<Touch*>& touches, Event* event) { do_some_thing();  };
listener->onTouchesMoved     = [](const std::vector<Touch*>& touches, Event* event) { do_some_thing();  };
listener->onTouchesEnded     = [](const std::vector<Touch*>& touches, Event* event) { do_some_thing();  };
listener->onTouchesCancelled = [](const std::vector<Touch*>& touches, Event* event) { do_some_thing();  };
// The priority of the touch listener is based on the draw order of sprite
EventDispatcher::getInstance()->addEventListenerWithSceneGraphPriority(listener, sprite);
// Or the priority of the touch listener is a fixed value
EventDispatcher::getInstance()->addEventListenerWithFixedPriority(listener, 100); // 100 is a fixed value
```

### Adding Mouse Event Listener  ###
```c++
auto mouseListener = EventListenerMouse::create();
mouseListener->onMouseScroll = [](Event* event) { EventMouse* e = static_cast<EventMouse*>(event); do_some_thing(); };
mouseListener->onMouseUp     = [](Event* event) { EventMouse* e = static_cast<EventMouse*>(event); do_some_thing(); };
mouseListener->onMouseDown   = [](Event* event) { EventMouse* e = static_cast<EventMouse*>(event); do_some_thing(); };
dispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
```

### Adding A Keyboard Event Listener

```c++
auto listener = EventListenerKeyboard::create();
listener->onKeyPressed = CC_CALLBACK_2(SomeClass::onKeyPressed, this);
listener->onKeyReleased = CC_CALLBACK_2(SomeClass::onKeyReleased, this);
EventDispatcher::getInstance()->addEventListenerWithSceneGraphPriority(listener, this);
```

### Adding An Acceleration Event Listener

```c++
auto listener = EventListenerAcceleration::create(CC_CALLBACK_2(SomeClass::onAcceleration, this));
EventDispatcher::getInstance()->addEventListenerWithSceneGraphPriority(listener, this);
```

### Adding A Custom Event Listener

```c++
auto listener = EventListenerCustom::create("game_custom_event", [=](EventCustom* event){
    void* userData= event->getUserData();
    do_some_with_user_data();
});
dispatcher->addEventListenerWithFixedPriority(listener, 1);
```

### Dispatching A Custom Event

```c++
EventCustom event("game_custom_event");
event.setUserData(some_data);
dispatcher->dispatchEvent(&event);
```

### Setting Fixed Priority For A Listener

```c++
dispatcher->setPriority(fixedPriorityListener, 200);
```

### Removing Event Listener

#### Removing A Specified Event Listener

```c++
dispatcher->removeEventListener(listener);
```

#### Removing Custom Event Listener ####

```c++
dispatcher->removeCustomEventListener("my_custom_event_listener_name");
```

#### Removing All Listeners For An Event Listener Type

```c++
dispatcher->removeEventListeners(EventListener::Type::TOUCH_ONE_BY_ONE);
```

#### Removing All Listeners

```c++
dispatcher->removeAllListeners();
```

## Physics Integration

_Feature added in v3.0-pre-alpha0_

Physics integration have five concepts: `PhysicsWorld`, `PhysicsBody`, `PhysicsShape`, `PhysicsJoint` and `PhysicsContact`.
You must define `CC_USE_PHYSICS` macro in `ccConfig.h` to use the physics API.

### PhysicsWorld

A `PhysicsWorld` object simulates collisions and other physical properties, you do not create it directly, you can get it from scene which create with physics.
```c++
Scene* scene = Scene::createWithPhysics();
PhysicsWorld* world = scene->getPhysicsWorld();
```

### PhysicsBody

A `PhysicsBody` object is used to add physics simulation to a node. If you create a `PhysicsBody` and set it to a node, and add the node the a scene which create with physics, it will perform the physics simulation when update.
```c++
PhysicsBody* body = PhysicsBody::createCircle(5.0f);
Node* node = Node::create();
node->setPhysicsBody(body);
scene->addChild(node);
```

### PhysicsShape

A `PhysicsShape` object is a shape that make the body can have collisions. you can add one or more `PhysicsShape` to a `PhysicsBody`.
Shape classes: `PhysicsShapeCircle`, `PhysicsShapeBox`, `PhysicsShapePolygon`, `PhysicsShapeEdgeSegment`, `PhysicsShapeEdgeBox`, `PhysicsShapeEdgePolygon`, `PhysicsShapeEdgeChain`.
```c++
PhysicsShape* shape = PhysicsShapeBox::create(Size(5.0f, 10.0f);
body->addShape(shape);
```

### PhysicsJoint

A `PhysicsJoint` object connects two physics bodies together so that they are simulated together by the physics world.
Joint classes: `PhysicsJointFixed`, `PhysicsJointLimit`, `PhysicsJointPin`, `PhysicsJointDistance`, `PhysicsJointSpring`, `PhysicsJointGroove`, `PhysicsJointRotarySpring`, `PhysicsJointRotaryLimit`, `PhysicsJointRatchet`, `PhysicsJointGear`, `PhysicsJointMotor`.
```c++
PhysicsJoint* joint = PhysicsJointDistance::construct(bodyA, bodyB, Point::ZERO, Point::ZERO);
world->addJoint(joint);
```

### PhysicsContact

A `PhysicsContact` object is created automatically to describes a contact between two physical bodies in a `PhysicsWorld`. you can control the contact behavior from the physics contact event listener.
Other classes contain the contact information: `PhysicsContactPreSolve`, `PhysicsContactPostSolve`.
The event listener for physics: `EventListenerPhysicsContact`, `EventListenerPhysicsContactWithBodies`, `EventListenerPhysicsContactWithShapes`, `EventListenerPhysicsContactWithGroup`.
```c++
auto contactListener = EventListenerPhysicsContactWithBodies::create(bodyA, bodyB);
contactListener->onContactBegin = [](EventCustom* event, const PhysicsContact& contact) -> bool
{
doSomething();
return true;
};
_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
```


# Misc API Changes

## `ccTypes.h`

Remove *cc* prefix for structure names in ccTypes.h, move global functions into static member functions, and move global constants into const static member variables.

	| v2.1 struct names | v3.0 struct names |
	| ccColor3B 	    | Color3B |
	| ccColor4B 		| Color4B |
	| ccColor4F 		| Color4F |
	| ccVertex2F 		| Vertex2F |
	| ccVertex3F 		| Vertex3F |
	| ccTex2F 			| Tex2F |
	| ccPointSprite 	| PointSprite |
	| ccQuad2 			| Quad2 |
	| ccQuad3 			| Quad3 |
	| ccV2F_C4B_T2F 	| V2F_C4B_T2F |
	| ccV2F_C4F_T2F 	| V2F_C4F_T2F |
	| ccV3F_C4B_T2F 	| V3F_C4B_T2F |
	| ccV2F_C4B_T2F_Triangle | V2F_C4B_T2F_Triangle |
	| ccV2F_C4B_T2F_Quad | V2F_C4B_T2F_Quad |
	| ccV3F_C4B_T2F_Quad | V3F_C4B_T2F_Quad |
	| ccV2F_C4F_T2F_Quad | V2F_C4F_T2F_Quad |
	| ccBlendFunc 		| BlendFunc |
	| ccT2F_Quad 		| T2F_Quad |
	| ccAnimationFrameData | AnimationFrameData |

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

## Changes in the Lua bindings

### Use bindings-generator tool for lua binding

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

### Use "cc"、"ccs"、"ccui" and "sp" as module name
The classes in the `cocos2d`、`cocos2d::extension`、`CocosDenshion` and `cocosbuilder` namespace were bound to lua in the `cc` module;
The classes in the `cocos2d::gui` namespace were bound to lua in the `ccui` module;
The classes in the `spine` namespace were bound to lua in the `sp` module;
The classes in the `cocostudio` namespace were bound to lua in the `ccs` module.

The main differences in the script are as follows:
```lua
// v2.x
CCSprite:create(s_pPathGrossini)
CCEaseIn:create(createSimpleMoveBy(), 2.5)

CCArmature:create("bear")

ImageView:create()

// v3.0
cc.Director:getInstance():getWinSize()
cc.EaseIn:create(createSimpleMoveBy(), 2.5)

ccs.Armature:create("bear")

ccui.ImageView:create()
```

### Deprecated funtions, tables and classes

Add a lot of deprecate funtions、table and classes to support 2.x version as far as possible
Note: `Rect does not support the origin and size member variables`

### Use the Lua table instead of the some structs and classes binding

Point、Size、Rect、Color3b、Color4b、Color4F、AffineTransform、FontDefinition、Array、Dictionary、PointArray are not bound.
The difference is as follow:
```lua
// v2.x
local pt = CCPoint(0 , 0)
local rect = CCRect(0, 0, 0, 0)
// v3.0
local pt = cc.p(0, 0)
local rect = cc.rect(0,0,0,0)
```

Global functions about these classes are changed as follow:
```lua
// in v2.x
local pt = ccp(0,0)
local color3B = ccc3(0, 0, 0)
local color4B = ccc4(0, 0, 0, 0)

// in v3.0
local pt  = cc.p(0,0)
local color3B = cc.c3b(0,0,0)
local color4B = cc.c4b(0,0,0,0)
```

Through the funtions of the LuaBasicConversion file,they can be converted the Lua table when they are as a parameter in the bindings generator.

### Integrate more modules into lua
In the version 3.0,more modules were bound to lua,specific as follows:

```
1.physics
2.spine
3.XMLHttpRequest
``` 
The XMLHttpRequest and physics are in the "cc" module,and the spine is in the "sp" module.
The related test cases located in:

```
physics   ---> TestLua/PhysicsTest
spine     ---> TestLua/SpineTest
XMLHttpRequest ---> TestLua/XMLHttpRequestTest
```  



## Known issues

You can find all the known issues "here":http://www.cocos2d-x.org/projects/native/issues
