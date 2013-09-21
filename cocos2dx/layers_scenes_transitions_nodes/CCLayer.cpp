/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2011      Zynga Inc.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#include <stdarg.h>
#include "CCLayer.h"
#include "CCDirector.h"
#include "script_support/CCScriptSupport.h"
#include "shaders/CCShaderCache.h"
#include "shaders/CCGLProgram.h"
#include "shaders/ccGLStateCache.h"
#include "support/TransformUtils.h"
// extern
#include "kazmath/GL/matrix.h"
#include "event_dispatcher/CCEventDispatcher.h"
#include "event_dispatcher/CCEventListenerTouch.h"
#include "event_dispatcher/CCEventTouch.h"
#include "event_dispatcher/CCEventKeyboard.h"
#include "event_dispatcher/CCEventListenerKeyboard.h"
#include "event_dispatcher/CCEventAcceleration.h"
#include "event_dispatcher/CCEventListenerAcceleration.h"
#include "platform/CCDevice.h"
#include "CCScene.h"

NS_CC_BEGIN

// Layer
Layer::Layer()
: _touchEnabled(false)
, _accelerometerEnabled(false)
, _keyboardEnabled(false)
, _touchMode(Touch::DispatchMode::ALL_AT_ONCE)
, _swallowsTouches(true)
, _touchListener(nullptr)
, _keyboardListener(nullptr)
, _accelerationListener(nullptr)
{
    _ignoreAnchorPointForPosition = true;
    setAnchorPoint(Point(0.5f, 0.5f));
}

Layer::~Layer()
{

}

bool Layer::init()
{
    bool bRet = false;
    do 
    {        
        Director * pDirector;
        CC_BREAK_IF(!(pDirector = Director::getInstance()));
        this->setContentSize(pDirector->getWinSize());
        setTouchEnabled(false);
        setAccelerometerEnabled(false);
        // success
        bRet = true;
    } while(0);
    return bRet;
}

Layer *Layer::create()
{
    Layer *pRet = new Layer();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        CC_SAFE_DELETE(pRet);
        return NULL;
    }
}

/// Touch and Accelerometer related

void Layer::addTouchListener()
{
    if (_touchListener != nullptr)
        return;
    
    auto dispatcher = EventDispatcher::getInstance();    
    
    if( _touchMode == Touch::DispatchMode::ALL_AT_ONCE )
    {
        // Register Touch Event
        auto listener = EventListenerTouch::create(Touch::DispatchMode::ALL_AT_ONCE);
        
        listener->onTouchesBegan = CC_CALLBACK_2(Layer::onTouchesBegan, this);
        listener->onTouchesMoved = CC_CALLBACK_2(Layer::onTouchesMoved, this);
        listener->onTouchesEnded = CC_CALLBACK_2(Layer::onTouchesEnded, this);
        listener->onTouchesCancelled = CC_CALLBACK_2(Layer::onTouchesCancelled, this);
        
        dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
        _touchListener = listener;
    }
    else
    {
        // Register Touch Event
        auto listener = EventListenerTouch::create(Touch::DispatchMode::ONE_BY_ONE);
        listener->setSwallowTouches(_swallowsTouches);
        
        listener->onTouchBegan = CC_CALLBACK_2(Layer::onTouchBegan, this);
        listener->onTouchMoved = CC_CALLBACK_2(Layer::onTouchMoved, this);
        listener->onTouchEnded = CC_CALLBACK_2(Layer::onTouchEnded, this);
        listener->onTouchCancelled = CC_CALLBACK_2(Layer::onTouchCancelled, this);
        
        dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
        _touchListener = listener;
    }
}

int Layer::executeScriptTouchHandler(EventTouch::EventCode eventType, Touch* touch)
{
    if (kScriptTypeNone != _scriptType)
    {
        TouchScriptData data(eventType, this, touch);
        ScriptEvent event(kTouchEvent, &data);
        return ScriptEngineManager::getInstance()->getScriptEngine()->sendEvent(&event);
    }

    //can not reach it
    return 0;
}

int Layer::executeScriptTouchesHandler(EventTouch::EventCode eventType, const std::vector<Touch*>& touches)
{
    if (kScriptTypeNone != _scriptType)
    {
        TouchesScriptData data(eventType, this, touches);
        ScriptEvent event(kTouchesEvent, &data);
        return ScriptEngineManager::getInstance()->getScriptEngine()->sendEvent(&event);
    }

    return 0;
}

/// isTouchEnabled getter
bool Layer::isTouchEnabled() const
{
    return _touchEnabled;
}

/// isTouchEnabled setter
void Layer::setTouchEnabled(bool enabled)
{
    if (_touchEnabled != enabled)
    {
        _touchEnabled = enabled;
        if (_running)
        {
            if (enabled)
            {
                this->addTouchListener();
            }
            else
            {
                EventDispatcher::getInstance()->removeEventListener(_touchListener);
                _touchListener = nullptr;
            }
        }
    }
}

void Layer::setTouchMode(Touch::DispatchMode mode)
{
    if(_touchMode != mode)
    {
        _touchMode = mode;
        
		if( _touchEnabled)
        {
			setTouchEnabled(false);
			setTouchEnabled(true);
		}
    }
}

void Layer::setSwallowsTouches(bool swallowsTouches)
{
    if (_swallowsTouches != swallowsTouches)
    {
        _swallowsTouches = swallowsTouches;
        
        if( _touchEnabled)
        {
            setTouchEnabled(false);
            setTouchEnabled(true);
        }
    }
}

Touch::DispatchMode Layer::getTouchMode() const
{
    return _touchMode;
}

bool Layer::isSwallowsTouches() const
{
	return _swallowsTouches;
}



/// isAccelerometerEnabled getter
bool Layer::isAccelerometerEnabled() const
{
    return _accelerometerEnabled;
}
/// isAccelerometerEnabled setter
void Layer::setAccelerometerEnabled(bool enabled)
{
    if (enabled != _accelerometerEnabled)
    {
        _accelerometerEnabled = enabled;

        Device::setAccelerometerEnabled(enabled);
        
        if (_running)
        {
            auto dispatcher = EventDispatcher::getInstance();
            dispatcher->removeEventListener(_accelerationListener);
            _accelerationListener = nullptr;
            
            if (enabled)
            {
                _accelerationListener = EventListenerAcceleration::create(CC_CALLBACK_2(Layer::onAcceleration, this));
                dispatcher->addEventListenerWithSceneGraphPriority(_accelerationListener, this);
            }
        }
    }
}


void Layer::setAccelerometerInterval(double interval) {
    if (_accelerometerEnabled)
    {
        if (_running)
        {
            Device::setAccelerometerInterval(interval);
        }
    }
}


void Layer::onAcceleration(Acceleration* pAccelerationValue, Event* event)
{
    CC_UNUSED_PARAM(pAccelerationValue);
    
    if(kScriptTypeNone != _scriptType)
    {
        BasicScriptData data(this,(void*)pAccelerationValue);
        ScriptEvent event(kAccelerometerEvent,&data);
        ScriptEngineManager::getInstance()->getScriptEngine()->sendEvent(&event);
    }
}

void Layer::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
    CC_UNUSED_PARAM(keyCode);
    CC_UNUSED_PARAM(event);
}

void Layer::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
    CC_UNUSED_PARAM(event);
    if(kScriptTypeNone != _scriptType)
    {
        KeypadScriptData data(keyCode, this);
        ScriptEvent event(kKeypadEvent,&data);
        ScriptEngineManager::getInstance()->getScriptEngine()->sendEvent(&event);
    }
}

/// isKeyboardEnabled getter
bool Layer::isKeyboardEnabled() const
{
    return _keyboardEnabled;
}
/// isKeyboardEnabled setter
void Layer::setKeyboardEnabled(bool enabled)
{
    if (enabled != _keyboardEnabled)
    {
        _keyboardEnabled = enabled;

        auto dispatcher = EventDispatcher::getInstance();
        dispatcher->removeEventListener(_keyboardListener);
        _keyboardListener = nullptr;
        
        if (enabled)
        {
            auto listener = EventListenerKeyboard::create();
            listener->onKeyPressed = CC_CALLBACK_2(Layer::onKeyPressed, this);
            listener->onKeyReleased = CC_CALLBACK_2(Layer::onKeyReleased, this);
            
            dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
            _keyboardListener = listener;
        }
    }
}

/// Callbacks
void Layer::onEnter()
{
    // register 'parent' nodes first
    // since events are propagated in reverse order
    if (_touchEnabled)
    {
        this->addTouchListener();
    }

    // then iterate over all the children
    Node::onEnter();

    // add this layer to concern the Accelerometer Sensor
    if (_accelerometerEnabled)
    {
        auto dispatcher = EventDispatcher::getInstance();
        dispatcher->removeEventListener(_accelerationListener);
        _accelerationListener = EventListenerAcceleration::create(CC_CALLBACK_2(Layer::onAcceleration, this));
        dispatcher->addEventListenerWithSceneGraphPriority(_accelerationListener, this);
    }
}

void Layer::onExit()
{
    auto dispatcher = EventDispatcher::getInstance();

    dispatcher->removeEventListener(_touchListener);
    _touchListener = nullptr;
    
    // remove this layer from the delegates who concern Accelerometer Sensor
    dispatcher->removeEventListener(_accelerationListener);
    _accelerationListener = nullptr;
    
    // remove this layer from the delegates who concern the keypad msg
    dispatcher->removeEventListener(_keyboardListener);
    _keyboardListener = nullptr;

    Node::onExit();
}

void Layer::onEnterTransitionDidFinish()
{
    if (_accelerometerEnabled)
    {
        auto dispatcher = EventDispatcher::getInstance();
        dispatcher->removeEventListener(_accelerationListener);
        _accelerationListener = EventListenerAcceleration::create(CC_CALLBACK_2(Layer::onAcceleration, this));
        dispatcher->addEventListenerWithSceneGraphPriority(_accelerationListener, this);
    }
    
    Node::onEnterTransitionDidFinish();
}

bool Layer::onTouchBegan(Touch *pTouch, Event *pEvent)
{
    if (kScriptTypeNone != _scriptType)
    {
        return executeScriptTouchHandler(EventTouch::EventCode::BEGAN, pTouch) == 0 ? false : true;
    }

    CC_UNUSED_PARAM(pTouch);
    CC_UNUSED_PARAM(pEvent);
    CCASSERT(false, "Layer#ccTouchBegan override me");
    return true;
}

void Layer::onTouchMoved(Touch *pTouch, Event *pEvent)
{
    if (kScriptTypeNone != _scriptType)
    {
        executeScriptTouchHandler(EventTouch::EventCode::MOVED, pTouch);
        return;
    }

    CC_UNUSED_PARAM(pTouch);
    CC_UNUSED_PARAM(pEvent);
}
    
void Layer::onTouchEnded(Touch *pTouch, Event *pEvent)
{
    if (kScriptTypeNone != _scriptType)
    {
        executeScriptTouchHandler(EventTouch::EventCode::ENDED, pTouch);
        return;
    }

    CC_UNUSED_PARAM(pTouch);
    CC_UNUSED_PARAM(pEvent);
}

void Layer::onTouchCancelled(Touch *pTouch, Event *pEvent)
{
    if (kScriptTypeNone != _scriptType)
    {
        executeScriptTouchHandler(EventTouch::EventCode::CANCELLED, pTouch);
        return;
    }

    CC_UNUSED_PARAM(pTouch);
    CC_UNUSED_PARAM(pEvent);
}    

void Layer::onTouchesBegan(const std::vector<Touch*>& pTouches, Event *pEvent)
{
    if (kScriptTypeNone != _scriptType)
    {
        executeScriptTouchesHandler(EventTouch::EventCode::BEGAN, pTouches);
        return;
    }

    CC_UNUSED_PARAM(pTouches);
    CC_UNUSED_PARAM(pEvent);
}

void Layer::onTouchesMoved(const std::vector<Touch*>& pTouches, Event *pEvent)
{
    if (kScriptTypeNone != _scriptType)
    {
        executeScriptTouchesHandler(EventTouch::EventCode::MOVED, pTouches);
        return;
    }

    CC_UNUSED_PARAM(pTouches);
    CC_UNUSED_PARAM(pEvent);
}

void Layer::onTouchesEnded(const std::vector<Touch*>& pTouches, Event *pEvent)
{
    if (kScriptTypeNone != _scriptType)
    {
        executeScriptTouchesHandler(EventTouch::EventCode::ENDED, pTouches);
        return;
    }

    CC_UNUSED_PARAM(pTouches);
    CC_UNUSED_PARAM(pEvent);
}

void Layer::onTouchesCancelled(const std::vector<Touch*>& pTouches, Event *pEvent)
{
    if (kScriptTypeNone != _scriptType)
    {
        executeScriptTouchesHandler(EventTouch::EventCode::CANCELLED, pTouches);
        return;
    }

    CC_UNUSED_PARAM(pTouches);
    CC_UNUSED_PARAM(pEvent);
}


#ifdef CC_USE_PHYSICS
void Layer::addChild(Node* child)
{
    Node::addChild(child);
}

void Layer::addChild(Node* child, int zOrder)
{
    Node::addChild(child, zOrder);
}

void Layer::addChild(Node* child, int zOrder, int tag)
{
    Node::addChild(child, zOrder, tag);
    
    if (this->getParent() &&
        dynamic_cast<Scene*>(this->getParent()) != nullptr)
    {
        dynamic_cast<Scene*>(this->getParent())->addChildToPhysicsWorld(child);
    }
}
#endif

// LayerRGBA
LayerRGBA::LayerRGBA()
: _displayedOpacity(255)
, _realOpacity (255)
, _displayedColor(Color3B::WHITE)
, _realColor(Color3B::WHITE)
, _cascadeOpacityEnabled(false)
, _cascadeColorEnabled(false)
{}

LayerRGBA::~LayerRGBA() {}

bool LayerRGBA::init()
{
	if (Layer::init())
    {
        _displayedOpacity = _realOpacity = 255;
        _displayedColor = _realColor = Color3B::WHITE;
        setCascadeOpacityEnabled(false);
        setCascadeColorEnabled(false);
        
        return true;
    }
    else
    {
        return false;
    }
}

GLubyte LayerRGBA::getOpacity() const
{
	return _realOpacity;
}

GLubyte LayerRGBA::getDisplayedOpacity() const
{
	return _displayedOpacity;
}

/** Override synthesized setOpacity to recurse items */
void LayerRGBA::setOpacity(GLubyte opacity)
{
	_displayedOpacity = _realOpacity = opacity;
    
	if( _cascadeOpacityEnabled )
    {
		GLubyte parentOpacity = 255;
        RGBAProtocol *parent = dynamic_cast<RGBAProtocol*>(_parent);
        if (parent && parent->isCascadeOpacityEnabled())
        {
            parentOpacity = parent->getDisplayedOpacity();
        }
        updateDisplayedOpacity(parentOpacity);
	}
}

const Color3B& LayerRGBA::getColor() const
{
	return _realColor;
}

const Color3B& LayerRGBA::getDisplayedColor() const
{
	return _displayedColor;
}

void LayerRGBA::setColor(const Color3B& color)
{
	_displayedColor = _realColor = color;
	
	if (_cascadeColorEnabled)
    {
		Color3B parentColor = Color3B::WHITE;
        RGBAProtocol* parent = dynamic_cast<RGBAProtocol*>(_parent);
		if (parent && parent->isCascadeColorEnabled())
        {
            parentColor = parent->getDisplayedColor();
        }

        updateDisplayedColor(parentColor);
	}
}

void LayerRGBA::updateDisplayedOpacity(GLubyte parentOpacity)
{
	_displayedOpacity = _realOpacity * parentOpacity/255.0;
    
    if (_cascadeOpacityEnabled)
    {
        Object *obj = NULL;
        CCARRAY_FOREACH(_children, obj)
        {
            RGBAProtocol *item = dynamic_cast<RGBAProtocol*>(obj);
            if (item)
            {
                item->updateDisplayedOpacity(_displayedOpacity);
            }
        }
    }
}

void LayerRGBA::updateDisplayedColor(const Color3B& parentColor)
{
	_displayedColor.r = _realColor.r * parentColor.r/255.0;
	_displayedColor.g = _realColor.g * parentColor.g/255.0;
	_displayedColor.b = _realColor.b * parentColor.b/255.0;
    
    if (_cascadeColorEnabled)
    {
        Object *obj = NULL;
        CCARRAY_FOREACH(_children, obj)
        {
            RGBAProtocol *item = dynamic_cast<RGBAProtocol*>(obj);
            if (item)
            {
                item->updateDisplayedColor(_displayedColor);
            }
        }
    }
}

bool LayerRGBA::isCascadeOpacityEnabled() const
{
    return _cascadeOpacityEnabled;
}

void LayerRGBA::setCascadeOpacityEnabled(bool cascadeOpacityEnabled)
{
    _cascadeOpacityEnabled = cascadeOpacityEnabled;
}

bool LayerRGBA::isCascadeColorEnabled() const
{
    return _cascadeColorEnabled;
}

void LayerRGBA::setCascadeColorEnabled(bool cascadeColorEnabled)
{
    _cascadeColorEnabled = cascadeColorEnabled;
}

/// LayerColor

LayerColor::LayerColor()
{
    // default blend function
    _blendFunc = BlendFunc::ALPHA_PREMULTIPLIED;
}
    
LayerColor::~LayerColor()
{
}

/// blendFunc getter
const BlendFunc &LayerColor::getBlendFunc() const
{
    return _blendFunc;
}
/// blendFunc setter
void LayerColor::setBlendFunc(const BlendFunc &var)
{
    _blendFunc = var;
}

LayerColor* LayerColor::create()
{
    LayerColor* pRet = new LayerColor();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}

LayerColor * LayerColor::create(const Color4B& color, GLfloat width, GLfloat height)
{
    LayerColor * pLayer = new LayerColor();
    if( pLayer && pLayer->initWithColor(color,width,height))
    {
        pLayer->autorelease();
        return pLayer;
    }
    CC_SAFE_DELETE(pLayer);
    return NULL;
}

LayerColor * LayerColor::create(const Color4B& color)
{
    LayerColor * pLayer = new LayerColor();
    if(pLayer && pLayer->initWithColor(color))
    {
        pLayer->autorelease();
        return pLayer;
    }
    CC_SAFE_DELETE(pLayer);
    return NULL;
}

bool LayerColor::init()
{
    Size s = Director::getInstance()->getWinSize();
    return initWithColor(Color4B(0,0,0,0), s.width, s.height);
}

bool LayerColor::initWithColor(const Color4B& color, GLfloat w, GLfloat h)
{
    if (Layer::init())
    {

        // default blend function
        _blendFunc = BlendFunc::ALPHA_NON_PREMULTIPLIED;

        _displayedColor.r = _realColor.r = color.r;
        _displayedColor.g = _realColor.g = color.g;
        _displayedColor.b = _realColor.b = color.b;
        _displayedOpacity = _realOpacity = color.a;

        for (size_t i = 0; i<sizeof(_squareVertices) / sizeof( _squareVertices[0]); i++ )
        {
            _squareVertices[i].x = 0.0f;
            _squareVertices[i].y = 0.0f;
        }

        updateColor();
        setContentSize(Size(w, h));

        setShaderProgram(ShaderCache::getInstance()->getProgram(GLProgram::SHADER_NAME_POSITION_COLOR));
        return true;
    }
    return false;
}

bool LayerColor::initWithColor(const Color4B& color)
{
    Size s = Director::getInstance()->getWinSize();
    this->initWithColor(color, s.width, s.height);
    return true;
}

/// override contentSize
void LayerColor::setContentSize(const Size & size)
{
    _squareVertices[1].x = size.width;
    _squareVertices[2].y = size.height;
    _squareVertices[3].x = size.width;
    _squareVertices[3].y = size.height;

    Layer::setContentSize(size);
}

void LayerColor::changeWidthAndHeight(GLfloat w ,GLfloat h)
{
    this->setContentSize(Size(w, h));
}

void LayerColor::changeWidth(GLfloat w)
{
    this->setContentSize(Size(w, _contentSize.height));
}

void LayerColor::changeHeight(GLfloat h)
{
    this->setContentSize(Size(_contentSize.width, h));
}

void LayerColor::updateColor()
{
    for( unsigned int i=0; i < 4; i++ )
    {
        _squareColors[i].r = _displayedColor.r / 255.0f;
        _squareColors[i].g = _displayedColor.g / 255.0f;
        _squareColors[i].b = _displayedColor.b / 255.0f;
        _squareColors[i].a = _displayedOpacity / 255.0f;
    }
}

void LayerColor::draw()
{
    CC_NODE_DRAW_SETUP();

    GL::enableVertexAttribs( GL::VERTEX_ATTRIB_FLAG_POSITION | GL::VERTEX_ATTRIB_FLAG_COLOR );

    //
    // Attributes
    //
#ifdef EMSCRIPTEN
    setGLBufferData(_squareVertices, 4 * sizeof(Vertex2F), 0);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, 0, 0);

    setGLBufferData(_squareColors, 4 * sizeof(Color4F), 1);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_FLOAT, GL_FALSE, 0, 0);
#else
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, 0, _squareVertices);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_FLOAT, GL_FALSE, 0, _squareColors);
#endif // EMSCRIPTEN

    GL::blendFunc( _blendFunc.src, _blendFunc.dst );

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    CC_INCREMENT_GL_DRAWS(1);
}

void LayerColor::setColor(const Color3B &color)
{
    LayerRGBA::setColor(color);
    updateColor();
}

void LayerColor::setOpacity(GLubyte opacity)
{
    LayerRGBA::setOpacity(opacity);
    updateColor();
}

//
// LayerGradient
// 
LayerGradient* LayerGradient::create(const Color4B& start, const Color4B& end)
{
    LayerGradient * pLayer = new LayerGradient();
    if( pLayer && pLayer->initWithColor(start, end))
    {
        pLayer->autorelease();
        return pLayer;
    }
    CC_SAFE_DELETE(pLayer);
    return NULL;
}

LayerGradient* LayerGradient::create(const Color4B& start, const Color4B& end, const Point& v)
{
    LayerGradient * pLayer = new LayerGradient();
    if( pLayer && pLayer->initWithColor(start, end, v))
    {
        pLayer->autorelease();
        return pLayer;
    }
    CC_SAFE_DELETE(pLayer);
    return NULL;
}

LayerGradient* LayerGradient::create()
{
    LayerGradient* pRet = new LayerGradient();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}

bool LayerGradient::init()
{
	return initWithColor(Color4B(0, 0, 0, 255), Color4B(0, 0, 0, 255));
}

bool LayerGradient::initWithColor(const Color4B& start, const Color4B& end)
{
    return initWithColor(start, end, Point(0, -1));
}

bool LayerGradient::initWithColor(const Color4B& start, const Color4B& end, const Point& v)
{
    _endColor.r  = end.r;
    _endColor.g  = end.g;
    _endColor.b  = end.b;

    _endOpacity   = end.a;
    _startOpacity    = start.a;
    _alongVector   = v;

    _compressedInterpolation = true;

    return LayerColor::initWithColor(Color4B(start.r, start.g, start.b, 255));
}

void LayerGradient::updateColor()
{
    LayerColor::updateColor();

    float h = _alongVector.getLength();
    if (h == 0)
        return;

    float c = sqrtf(2.0f);
    Point u = Point(_alongVector.x / h, _alongVector.y / h);

    // Compressed Interpolation mode
    if (_compressedInterpolation)
    {
        float h2 = 1 / ( fabsf(u.x) + fabsf(u.y) );
        u = u * (h2 * (float)c);
    }

    float opacityf = (float)_displayedOpacity / 255.0f;

    Color4F S(
        _displayedColor.r / 255.0f,
        _displayedColor.g / 255.0f,
        _displayedColor.b / 255.0f,
        _startOpacity * opacityf / 255.0f
    );

    Color4F E(
        _endColor.r / 255.0f,
        _endColor.g / 255.0f,
        _endColor.b / 255.0f,
        _endOpacity * opacityf / 255.0f
    );

    // (-1, -1)
    _squareColors[0].r = E.r + (S.r - E.r) * ((c + u.x + u.y) / (2.0f * c));
    _squareColors[0].g = E.g + (S.g - E.g) * ((c + u.x + u.y) / (2.0f * c));
    _squareColors[0].b = E.b + (S.b - E.b) * ((c + u.x + u.y) / (2.0f * c));
    _squareColors[0].a = E.a + (S.a - E.a) * ((c + u.x + u.y) / (2.0f * c));
    // (1, -1)
    _squareColors[1].r = E.r + (S.r - E.r) * ((c - u.x + u.y) / (2.0f * c));
    _squareColors[1].g = E.g + (S.g - E.g) * ((c - u.x + u.y) / (2.0f * c));
    _squareColors[1].b = E.b + (S.b - E.b) * ((c - u.x + u.y) / (2.0f * c));
    _squareColors[1].a = E.a + (S.a - E.a) * ((c - u.x + u.y) / (2.0f * c));
    // (-1, 1)
    _squareColors[2].r = E.r + (S.r - E.r) * ((c + u.x - u.y) / (2.0f * c));
    _squareColors[2].g = E.g + (S.g - E.g) * ((c + u.x - u.y) / (2.0f * c));
    _squareColors[2].b = E.b + (S.b - E.b) * ((c + u.x - u.y) / (2.0f * c));
    _squareColors[2].a = E.a + (S.a - E.a) * ((c + u.x - u.y) / (2.0f * c));
    // (1, 1)
    _squareColors[3].r = E.r + (S.r - E.r) * ((c - u.x - u.y) / (2.0f * c));
    _squareColors[3].g = E.g + (S.g - E.g) * ((c - u.x - u.y) / (2.0f * c));
    _squareColors[3].b = E.b + (S.b - E.b) * ((c - u.x - u.y) / (2.0f * c));
    _squareColors[3].a = E.a + (S.a - E.a) * ((c - u.x - u.y) / (2.0f * c));
}

const Color3B& LayerGradient::getStartColor() const
{
    return _realColor;
}

void LayerGradient::setStartColor(const Color3B& color)
{
    setColor(color);
}

void LayerGradient::setEndColor(const Color3B& color)
{
    _endColor = color;
    updateColor();
}

const Color3B& LayerGradient::getEndColor() const
{
    return _endColor;
}

void LayerGradient::setStartOpacity(GLubyte o)
{
    _startOpacity = o;
    updateColor();
}

GLubyte LayerGradient::getStartOpacity() const
{
    return _startOpacity;
}

void LayerGradient::setEndOpacity(GLubyte o)
{
    _endOpacity = o;
    updateColor();
}

GLubyte LayerGradient::getEndOpacity() const
{
    return _endOpacity;
}

void LayerGradient::setVector(const Point& var)
{
    _alongVector = var;
    updateColor();
}

const Point& LayerGradient::getVector() const
{
    return _alongVector;
}

bool LayerGradient::isCompressedInterpolation() const
{
    return _compressedInterpolation;
}

void LayerGradient::setCompressedInterpolation(bool compress)
{
    _compressedInterpolation = compress;
    updateColor();
}

/// MultiplexLayer

LayerMultiplex::LayerMultiplex()
: _enabledLayer(0)
, _layers(NULL)
{
}
LayerMultiplex::~LayerMultiplex()
{
    CC_SAFE_RELEASE(_layers);
}

LayerMultiplex * LayerMultiplex::create(Layer * layer, ...)
{
    va_list args;
    va_start(args,layer);

    LayerMultiplex * pMultiplexLayer = new LayerMultiplex();
    if(pMultiplexLayer && pMultiplexLayer->initWithLayers(layer, args))
    {
        pMultiplexLayer->autorelease();
        va_end(args);
        return pMultiplexLayer;
    }
    va_end(args);
    CC_SAFE_DELETE(pMultiplexLayer);
    return NULL;
}

LayerMultiplex * LayerMultiplex::createWithLayer(Layer* layer)
{
    return LayerMultiplex::create(layer, NULL);
}

LayerMultiplex* LayerMultiplex::create()
{
    LayerMultiplex* pRet = new LayerMultiplex();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}

LayerMultiplex* LayerMultiplex::createWithArray(Array* arrayOfLayers)
{
    LayerMultiplex* pRet = new LayerMultiplex();
    if (pRet && pRet->initWithArray(arrayOfLayers))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}

void LayerMultiplex::addLayer(Layer* layer)
{
    CCASSERT(_layers, "");
    _layers->addObject(layer);
}

bool LayerMultiplex::init()
{
    if (Layer::init())
    {
        _layers = Array::create();
        _layers->retain();

        _enabledLayer = 0;
        return true;
    }
    return false;
}

bool LayerMultiplex::initWithLayers(Layer *layer, va_list params)
{
    if (Layer::init())
    {
        _layers = Array::createWithCapacity(5);
        _layers->retain();
        _layers->addObject(layer);

        Layer *l = va_arg(params,Layer*);
        while( l ) {
            _layers->addObject(l);
            l = va_arg(params,Layer*);
        }

        _enabledLayer = 0;
        this->addChild((Node*)_layers->getObjectAtIndex(_enabledLayer));
        return true;
    }

    return false;
}

bool LayerMultiplex::initWithArray(Array* arrayOfLayers)
{
    if (Layer::init())
    {
        _layers = Array::createWithCapacity(arrayOfLayers->count());
        _layers->addObjectsFromArray(arrayOfLayers);
        _layers->retain();

        _enabledLayer = 0;
        this->addChild((Node*)_layers->getObjectAtIndex(_enabledLayer));
        return true;
    }
    return false;
}

void LayerMultiplex::switchTo(int n)
{
    CCASSERT( n < _layers->count(), "Invalid index in MultiplexLayer switchTo message" );

    this->removeChild((Node*)_layers->getObjectAtIndex(_enabledLayer), true);

    _enabledLayer = n;

    this->addChild((Node*)_layers->getObjectAtIndex(n));
}

void LayerMultiplex::switchToAndReleaseMe(int n)
{
    CCASSERT( n < _layers->count(), "Invalid index in MultiplexLayer switchTo message" );

    this->removeChild((Node*)_layers->getObjectAtIndex(_enabledLayer), true);

    //[layers replaceObjectAtIndex:enabledLayer withObject:[NSNull null]];
    _layers->replaceObjectAtIndex(_enabledLayer, NULL);

    _enabledLayer = n;

    this->addChild((Node*)_layers->getObjectAtIndex(n));
}

NS_CC_END
