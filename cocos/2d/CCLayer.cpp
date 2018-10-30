/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2016 Chukong Technologies Inc.
Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
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
#include "2d/CCLayer.h"
#include "base/CCScriptSupport.h"
#include "base/ccUtils.h"
#include "platform/CCDevice.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCGLProgramState.h"
#include "base/CCDirector.h"
#include "base/CCEventDispatcher.h"
#include "base/CCEventListenerTouch.h"
#include "base/CCEventTouch.h"
#include "base/CCEventKeyboard.h"
#include "base/CCEventListenerKeyboard.h"
#include "base/CCEventAcceleration.h"
#include "base/CCEventListenerAcceleration.h"
#include "base/ccUTF8.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
#include "platform/desktop/CCGLViewImpl-desktop.h"
#endif

NS_CC_BEGIN

// Layer
Layer::Layer()
: _touchEnabled(false)
, _accelerometerEnabled(false)
, _keyboardEnabled(false)
, _touchListener(nullptr)
, _keyboardListener(nullptr)
, _accelerationListener(nullptr)
, _touchMode(Touch::DispatchMode::ALL_AT_ONCE)
, _swallowsTouches(true)
{
    _ignoreAnchorPointForPosition = true;
    setAnchorPoint(Vec2(0.5f, 0.5f));
}

Layer::~Layer()
{

}

bool Layer::init()
{
    Director * director = Director::getInstance();
    setContentSize(director->getWinSize());
    return true;
}

Layer *Layer::create()
{
    Layer *ret = new (std::nothrow) Layer();
    if (ret && ret->init())
    {
        ret->autorelease();
        return ret;
    }
    else
    {
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
}

int Layer::executeScriptTouchHandler(EventTouch::EventCode eventType, Touch* touch, Event* event)
{
#if CC_ENABLE_SCRIPT_BINDING
    if (kScriptTypeLua == _scriptType)
    {
        TouchScriptData data(eventType, this, touch, event);
        ScriptEvent scriptEvent(kTouchEvent, &data);
        return ScriptEngineManager::getInstance()->getScriptEngine()->sendEvent(&scriptEvent);
    }
#else
    CC_UNUSED_PARAM(eventType);
    CC_UNUSED_PARAM(touch);
    CC_UNUSED_PARAM(event);
#endif
    return 0;
}

int Layer::executeScriptTouchesHandler(EventTouch::EventCode eventType, const std::vector<Touch*>& touches, Event* event)
{
#if CC_ENABLE_SCRIPT_BINDING
    if (kScriptTypeLua == _scriptType)
    {
        TouchesScriptData data(eventType, this, touches, event);
        ScriptEvent scriptEvent(kTouchesEvent, &data);
        return ScriptEngineManager::getInstance()->getScriptEngine()->sendEvent(&scriptEvent);
    }
#else
    CC_UNUSED_PARAM(eventType);
    CC_UNUSED_PARAM(touches);
    CC_UNUSED_PARAM(event);
#endif
    return 0;
}

bool Layer::ccTouchBegan(Touch* /*pTouch*/, Event* /*pEvent*/) {return false;};
void Layer::ccTouchMoved(Touch* /*pTouch*/, Event* /*pEvent*/) {}
void Layer::ccTouchEnded(Touch* /*pTouch*/, Event* /*pEvent*/) {}
void Layer::ccTouchCancelled(Touch* /*pTouch*/, Event* /*pEvent*/) {}
void Layer::ccTouchesBegan(__Set* /*pTouches*/, Event* /*pEvent*/) {}
void Layer::ccTouchesMoved(__Set* /*pTouches*/, Event* /*pEvent*/) {}
void Layer::ccTouchesEnded(__Set* /*pTouches*/, Event* /*pEvent*/) {}
void Layer::ccTouchesCancelled(__Set* /*pTouches*/, Event* /*pEvent*/) {}

#if defined(__GNUC__) && ((__GNUC__ >= 4) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 1)))
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#elif _MSC_VER >= 1400 //vs 2005 or higher
#pragma warning (push)
#pragma warning (disable: 4996)
#endif

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
        if (enabled)
        {
            if (_touchListener != nullptr)
                return;

            if( _touchMode == Touch::DispatchMode::ALL_AT_ONCE )
            {
                // Register Touch Event
                auto listener = EventListenerTouchAllAtOnce::create();

                listener->onTouchesBegan = CC_CALLBACK_2(Layer::onTouchesBegan, this);
                listener->onTouchesMoved = CC_CALLBACK_2(Layer::onTouchesMoved, this);
                listener->onTouchesEnded = CC_CALLBACK_2(Layer::onTouchesEnded, this);
                listener->onTouchesCancelled = CC_CALLBACK_2(Layer::onTouchesCancelled, this);

                _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
                _touchListener = listener;
            }
            else
            {
                // Register Touch Event
                auto listener = EventListenerTouchOneByOne::create();
                listener->setSwallowTouches(_swallowsTouches);

                listener->onTouchBegan = CC_CALLBACK_2(Layer::onTouchBegan, this);
                listener->onTouchMoved = CC_CALLBACK_2(Layer::onTouchMoved, this);
                listener->onTouchEnded = CC_CALLBACK_2(Layer::onTouchEnded, this);
                listener->onTouchCancelled = CC_CALLBACK_2(Layer::onTouchCancelled, this);

                _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
                _touchListener = listener;
            }
        }
        else
        {
            _eventDispatcher->removeEventListener(_touchListener);
            _touchListener = nullptr;
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

        _eventDispatcher->removeEventListener(_accelerationListener);
        _accelerationListener = nullptr;

        if (enabled)
        {
            _accelerationListener = EventListenerAcceleration::create(CC_CALLBACK_2(Layer::onAcceleration, this));
            _eventDispatcher->addEventListenerWithSceneGraphPriority(_accelerationListener, this);
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

void Layer::onAcceleration(Acceleration* acc, Event* /*unused_event*/)
{
#if CC_ENABLE_SCRIPT_BINDING
    if(kScriptTypeNone != _scriptType)
    {
        BasicScriptData data(this,(void*)acc);
        ScriptEvent event(kAccelerometerEvent,&data);
        ScriptEngineManager::getInstance()->getScriptEngine()->sendEvent(&event);
    }
#else
    CC_UNUSED_PARAM(acc);
#endif
}

void Layer::onKeyPressed(EventKeyboard::KeyCode /*keyCode*/, Event* /*unused_event*/)
{
}

void Layer::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* /*unused_event*/)
{
#if CC_ENABLE_SCRIPT_BINDING
    if(kScriptTypeNone != _scriptType)
    {
        KeypadScriptData data(keyCode, this);
        ScriptEvent event(kKeypadEvent,&data);
        ScriptEngineManager::getInstance()->getScriptEngine()->sendEvent(&event);
    }
#else
    CC_UNUSED_PARAM(keyCode);
#endif
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

        _eventDispatcher->removeEventListener(_keyboardListener);
        _keyboardListener = nullptr;

        if (enabled)
        {
            auto listener = EventListenerKeyboard::create();
            listener->onKeyPressed = CC_CALLBACK_2(Layer::onKeyPressed, this);
            listener->onKeyReleased = CC_CALLBACK_2(Layer::onKeyReleased, this);

            _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
            _keyboardListener = listener;
        }
    }
}

void Layer::setKeypadEnabled(bool enabled)
{
    setKeyboardEnabled(enabled);
}
/// Callbacks

bool Layer::onTouchBegan(Touch *touch, Event *event)
{
#if CC_ENABLE_SCRIPT_BINDING
    if (kScriptTypeLua == _scriptType)
    {
        return executeScriptTouchHandler(EventTouch::EventCode::BEGAN, touch, event) == 0 ? false : true;
    }
#else
    CC_UNUSED_PARAM(touch);
    CC_UNUSED_PARAM(event);
#endif
    CCASSERT(false, "Layer#ccTouchBegan override me");
    return true;
}

void Layer::onTouchMoved(Touch *touch, Event *event)
{
#if CC_ENABLE_SCRIPT_BINDING
    if (kScriptTypeLua == _scriptType)
    {
        executeScriptTouchHandler(EventTouch::EventCode::MOVED, touch, event);
        return;
    }
#else
    CC_UNUSED_PARAM(touch);
    CC_UNUSED_PARAM(event);
#endif
}

void Layer::onTouchEnded(Touch *touch, Event *event)
{
#if CC_ENABLE_SCRIPT_BINDING
    if (kScriptTypeLua == _scriptType)
    {
        executeScriptTouchHandler(EventTouch::EventCode::ENDED, touch, event);
        return;
    }
#else
    CC_UNUSED_PARAM(touch);
    CC_UNUSED_PARAM(event);
#endif
}

void Layer::onTouchCancelled(Touch *touch, Event *event)
{
#if CC_ENABLE_SCRIPT_BINDING
    if (kScriptTypeLua == _scriptType)
    {
        executeScriptTouchHandler(EventTouch::EventCode::CANCELLED, touch, event);
        return;
    }
#else
    CC_UNUSED_PARAM(touch);
    CC_UNUSED_PARAM(event);
#endif
}    

void Layer::onTouchesBegan(const std::vector<Touch*>& touches, Event *event)
{
#if CC_ENABLE_SCRIPT_BINDING
    if (kScriptTypeLua == _scriptType)
    {
        executeScriptTouchesHandler(EventTouch::EventCode::BEGAN, touches, event);
        return;
    }
#else
    CC_UNUSED_PARAM(touches);
    CC_UNUSED_PARAM(event);
#endif
}

void Layer::onTouchesMoved(const std::vector<Touch*>& touches, Event *event)
{
#if CC_ENABLE_SCRIPT_BINDING
    if (kScriptTypeLua == _scriptType)
    {
        executeScriptTouchesHandler(EventTouch::EventCode::MOVED, touches, event);
        return;
    }
#else
    CC_UNUSED_PARAM(touches);
    CC_UNUSED_PARAM(event);
#endif
}

void Layer::onTouchesEnded(const std::vector<Touch*>& touches, Event *event)
{
#if CC_ENABLE_SCRIPT_BINDING
    if (kScriptTypeLua == _scriptType)
    {
        executeScriptTouchesHandler(EventTouch::EventCode::ENDED, touches, event);
        return;
    }
#else
    CC_UNUSED_PARAM(touches);
    CC_UNUSED_PARAM(event);
#endif
}

void Layer::onTouchesCancelled(const std::vector<Touch*>& touches, Event *event)
{
#if CC_ENABLE_SCRIPT_BINDING
    if (kScriptTypeLua == _scriptType)
    {
        executeScriptTouchesHandler(EventTouch::EventCode::CANCELLED, touches, event);
        return;
    }
#else
    CC_UNUSED_PARAM(touches);
    CC_UNUSED_PARAM(event);
#endif
}

std::string Layer::getDescription() const
{
    return StringUtils::format("<Layer | Tag = %d>", _tag);
}

__LayerRGBA::__LayerRGBA()
{
    CCLOG("LayerRGBA deprecated.");
}


#if defined(__GNUC__) && ((__GNUC__ >= 4) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 1)))
#pragma GCC diagnostic warning "-Wdeprecated-declarations"
#elif _MSC_VER >= 1400 //vs 2005 or higher
#pragma warning (pop)
#endif
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
    LayerColor* ret = new (std::nothrow) LayerColor();
    if (ret && ret->init())
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

LayerColor * LayerColor::create(const Color4B& color, GLfloat width, GLfloat height)
{
    LayerColor * layer = new (std::nothrow) LayerColor();
    if( layer && layer->initWithColor(color,width,height))
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return nullptr;
}

LayerColor * LayerColor::create(const Color4B& color)
{
    LayerColor * layer = new (std::nothrow) LayerColor();
    if(layer && layer->initWithColor(color))
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return nullptr;
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

        setGLProgramState(GLProgramState::getOrCreateWithGLProgramName(GLProgram::SHADER_NAME_POSITION_COLOR_NO_MVP));
        return true;
    }
    return false;
}

bool LayerColor::initWithColor(const Color4B& color)
{
    Size s = Director::getInstance()->getWinSize();
    return initWithColor(color, s.width, s.height);
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

void LayerColor::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
    _customCommand.init(_globalZOrder, transform, flags);
    _customCommand.func = CC_CALLBACK_0(LayerColor::onDraw, this, transform, flags);
    renderer->addCommand(&_customCommand);
    
    for(int i = 0; i < 4; ++i)
    {
        Vec4 pos;
        pos.x = _squareVertices[i].x; pos.y = _squareVertices[i].y; pos.z = _positionZ;
        pos.w = 1;
        _modelViewTransform.transformVector(&pos);
        _noMVPVertices[i] = Vec3(pos.x,pos.y,pos.z)/pos.w;
    }
}

void LayerColor::onDraw(const Mat4& transform, uint32_t /*flags*/)
{
    getGLProgram()->use();
    getGLProgram()->setUniformsForBuiltins(transform);
    
    glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_POSITION);
    glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_COLOR);
    
    //
    // Attributes
    //
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, 0, _noMVPVertices);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_FLOAT, GL_FALSE, 0, _squareColors);

    utils::setBlending(_blendFunc.src, _blendFunc.dst);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1,4);
}

std::string LayerColor::getDescription() const
{
    return StringUtils::format("<LayerColor | Tag = %d>", _tag);
}

//
// LayerGradient
//
LayerGradient::LayerGradient()
: _startColor(Color4B::BLACK)
, _endColor(Color4B::BLACK)
, _startOpacity(255)
, _endOpacity(255)
, _alongVector(Vec2(0, -1))
, _compressedInterpolation(true)
{
    
}

LayerGradient::~LayerGradient()
{
}

LayerGradient* LayerGradient::create(const Color4B& start, const Color4B& end)
{
    LayerGradient * layer = new (std::nothrow) LayerGradient();
    if( layer && layer->initWithColor(start, end))
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return nullptr;
}

LayerGradient* LayerGradient::create(const Color4B& start, const Color4B& end, const Vec2& v)
{
    LayerGradient * layer = new (std::nothrow) LayerGradient();
    if( layer && layer->initWithColor(start, end, v))
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return nullptr;
}

LayerGradient* LayerGradient::create()
{
    LayerGradient* ret = new (std::nothrow) LayerGradient();
    if (ret && ret->init())
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

bool LayerGradient::init()
{
    return initWithColor(Color4B(0, 0, 0, 255), Color4B(0, 0, 0, 255));
}

bool LayerGradient::initWithColor(const Color4B& start, const Color4B& end)
{
    return initWithColor(start, end, Vec2(0, -1));
}

bool LayerGradient::initWithColor(const Color4B& start, const Color4B& end, const Vec2& v)
{
    _endColor.r  = end.r;
    _endColor.g  = end.g;
    _endColor.b  = end.b;

    _endOpacity     = end.a;
    _startOpacity   = start.a;
    _alongVector    = v;

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
    Vec2 u(_alongVector.x / h, _alongVector.y / h);

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

void LayerGradient::setVector(const Vec2& var)
{
    _alongVector = var;
    updateColor();
}

const Vec2& LayerGradient::getVector() const
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

std::string LayerGradient::getDescription() const
{
    return StringUtils::format("<LayerGradient | Tag = %d>", _tag);
}

/**
 * LayerRadialGradient
 */
LayerRadialGradient* LayerRadialGradient::create(const Color4B& startColor, const Color4B& endColor, float radius, const Vec2& center, float expand)
{
    auto layerGradient = new LayerRadialGradient();
    if (layerGradient && layerGradient->initWithColor(startColor, endColor, radius, center, expand))
    {
        layerGradient->autorelease();
        return layerGradient;
    }
    
    delete layerGradient;
    return nullptr;
}

LayerRadialGradient* LayerRadialGradient::create()
{
    auto layerGradient = new LayerRadialGradient();
    if (layerGradient && layerGradient->initWithColor(Color4B::BLACK, Color4B::BLACK, 0, Vec2(0,0), 0))
    {
        layerGradient->autorelease();
        return layerGradient;
    }
    
    delete layerGradient;
    return nullptr;
}

LayerRadialGradient::LayerRadialGradient()
: _startColor(Color4B::BLACK)
, _startColorRend(Color4F::BLACK)
, _endColor(Color4B::BLACK)
, _endColorRend(Color4F::BLACK)
, _center(Vec2(0,0))
, _radius(0.f)
, _expand(0.f)
, _uniformLocationStartColor(0)
, _uniformLocationEndColor(0)
, _uniformLocationCenter(0)
, _uniformLocationRadius(0)
, _uniformLocationExpand(0)
, _blendFunc(BlendFunc::ALPHA_NON_PREMULTIPLIED)
{ }

LayerRadialGradient::~LayerRadialGradient()
{}

bool LayerRadialGradient::initWithColor(const cocos2d::Color4B &startColor, const cocos2d::Color4B &endColor, float radius, const Vec2& center, float expand)
{
    // should do it before Layer::init()
    for (int i = 0; i < 4; ++i)
        _vertices[i] = {0.0f, 0.0f};
    
    if (Layer::init())
    {
        convertColor4B24F(_startColorRend, startColor);
        _startColor = startColor;
        
        convertColor4B24F(_endColorRend, endColor);
        _endColor = endColor;
        
        _expand = expand;
        
        setRadius(radius);
        setCenter(center);
        
        setGLProgramState(GLProgramState::getOrCreateWithGLProgramName(GLProgram::SHADER_LAYER_RADIAL_GRADIENT));
        auto program = getGLProgram();
        _uniformLocationStartColor = program->getUniformLocation("u_startColor");
        _uniformLocationEndColor = program->getUniformLocation("u_endColor");
        _uniformLocationExpand = program->getUniformLocation("u_expand");
        _uniformLocationRadius = program->getUniformLocation("u_radius");
        _uniformLocationCenter = program->getUniformLocation("u_center");
        
        return true;
    }
    
    return false;
}

void LayerRadialGradient::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
    _customCommand.init(_globalZOrder, transform, flags);
    _customCommand.func = CC_CALLBACK_0(LayerRadialGradient::onDraw, this, transform, flags);
    renderer->addCommand(&_customCommand);
}

void LayerRadialGradient::onDraw(const Mat4& transform, uint32_t /*flags*/)
{
    auto program = getGLProgram();
    program->use();
    program->setUniformsForBuiltins(transform);
    program->setUniformLocationWith4f(_uniformLocationStartColor, _startColorRend.r,
                                      _startColorRend.g, _startColorRend.b, _startColorRend.a);
    program->setUniformLocationWith4f(_uniformLocationEndColor, _endColorRend.r,
                                      _endColorRend.g, _endColorRend.b, _endColorRend.a);
    program->setUniformLocationWith2f(_uniformLocationCenter, _center.x, _center.y);
    program->setUniformLocationWith1f(_uniformLocationRadius, _radius);
    program->setUniformLocationWith1f(_uniformLocationExpand, _expand);
    
    
    glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_POSITION);
    
    //
    // Attributes
    //
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, 0, _vertices);
    
    utils::setBlending(_blendFunc.src, _blendFunc.dst);
    
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    
    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1,4);
}

void LayerRadialGradient::setContentSize(const Size& size)
{
    _vertices[1].x = size.width;
    _vertices[2].y = size.height;
    _vertices[3].x = size.width;
    _vertices[3].y = size.height;
    Layer::setContentSize(size);
}

void LayerRadialGradient::setStartOpacity(GLubyte opacity)
{
    _startColorRend.a = opacity / 255.0f;
    _startColor.a = opacity;
}

GLubyte LayerRadialGradient::getStartOpacity() const
{
    return _startColor.a;
}

void LayerRadialGradient::setEndOpacity(GLubyte opacity)
{
    _endColorRend.a = opacity / 255.0f;
    _endColor.a = opacity;
}

GLubyte LayerRadialGradient::getEndOpacity() const
{
    return _endColor.a;
}

void LayerRadialGradient::setRadius(float radius)
{
    _radius = radius;
}

float LayerRadialGradient::getRadius() const
{
    return _radius;
}

void LayerRadialGradient::setCenter(const Vec2& center)
{
    _center = center;
}

Vec2 LayerRadialGradient::getCenter() const
{
    return _center;
}

void LayerRadialGradient::setExpand(float expand)
{
    _expand = expand;
}

float LayerRadialGradient::getExpand() const
{
    return _expand;
}

void LayerRadialGradient::setStartColor(const Color3B& color)
{
    setStartColor(Color4B(color));
}

void LayerRadialGradient::setStartColor(const cocos2d::Color4B &color)
{
    _startColor = color;
    convertColor4B24F(_startColorRend, _startColor);
}

Color4B LayerRadialGradient::getStartColor() const
{
    return _startColor;
}

Color3B LayerRadialGradient::getStartColor3B() const
{
    return Color3B(_startColor);
}

void LayerRadialGradient::setEndColor(const Color3B& color)
{
    setEndColor(Color4B(color));
}

void LayerRadialGradient::setEndColor(const cocos2d::Color4B &color)
{
    _endColor = color;
    convertColor4B24F(_endColorRend, _endColor);
}

Color4B LayerRadialGradient::getEndColor() const
{
    return _endColor;
}

Color3B LayerRadialGradient::getEndColor3B() const
{
    return Color3B(_endColor);
}

void LayerRadialGradient::setBlendFunc(const BlendFunc& blendFunc)
{
    _blendFunc = blendFunc;
}

BlendFunc LayerRadialGradient::getBlendFunc() const
{
    return _blendFunc;
}

void LayerRadialGradient::convertColor4B24F(Color4F& outColor, const Color4B& inColor)
{
    outColor.r = inColor.r / 255.0f;
    outColor.g = inColor.g / 255.0f;
    outColor.b = inColor.b / 255.0f;
    outColor.a = inColor.a / 255.0f;
}


/// MultiplexLayer

LayerMultiplex::LayerMultiplex()
: _enabledLayer(0)
{
}

LayerMultiplex::~LayerMultiplex()
{
    for(const auto &layer : _layers) {
        layer->cleanup();
    }
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
LayerMultiplex * LayerMultiplex::createVariadic(Layer * layer, ...)
{
    va_list args;
    va_start(args,layer);

    LayerMultiplex * multiplexLayer = new (std::nothrow) LayerMultiplex();
    if(multiplexLayer && multiplexLayer->initWithLayers(layer, args))
    {
        multiplexLayer->autorelease();
        va_end(args);
        return multiplexLayer;
    }
    va_end(args);
    CC_SAFE_DELETE(multiplexLayer);
    return nullptr;
}
#else
LayerMultiplex * LayerMultiplex::create(Layer * layer, ...)
{
    va_list args;
    va_start(args,layer);

    LayerMultiplex * multiplexLayer = new (std::nothrow) LayerMultiplex();
    if(multiplexLayer && multiplexLayer->initWithLayers(layer, args))
    {
        multiplexLayer->autorelease();
        va_end(args);
        return multiplexLayer;
    }
    va_end(args);
    CC_SAFE_DELETE(multiplexLayer);
    return nullptr;
}
#endif

LayerMultiplex * LayerMultiplex::createWithLayer(Layer* layer)
{
    return LayerMultiplex::create(layer, nullptr);
}

LayerMultiplex* LayerMultiplex::create()
{
    LayerMultiplex* ret = new (std::nothrow) LayerMultiplex();
    if (ret && ret->init())
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

LayerMultiplex* LayerMultiplex::createWithArray(const Vector<Layer*>& arrayOfLayers)
{
    LayerMultiplex* ret = new (std::nothrow) LayerMultiplex();
    if (ret && ret->initWithArray(arrayOfLayers))
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

void LayerMultiplex::addLayer(Layer* layer)
{
#if CC_ENABLE_GC_FOR_NATIVE_OBJECTS
    auto sEngine = ScriptEngineManager::getInstance()->getScriptEngine();
    if (sEngine)
    {
        sEngine->retainScriptObject(this, layer);
    }
#endif // CC_ENABLE_GC_FOR_NATIVE_OBJECTS
    _layers.pushBack(layer);
}

bool LayerMultiplex::init()
{
    if (Layer::init())
    {
        _enabledLayer = 0;
        return true;
    }
    return false;
}

bool LayerMultiplex::initWithLayers(Layer *layer, va_list params)
{
    if (Layer::init())
    {
        _layers.reserve(5);
#if CC_ENABLE_GC_FOR_NATIVE_OBJECTS
        auto sEngine = ScriptEngineManager::getInstance()->getScriptEngine();
        if (sEngine)
        {
            sEngine->retainScriptObject(this, layer);
        }
#endif // CC_ENABLE_GC_FOR_NATIVE_OBJECTS
        _layers.pushBack(layer);

        Layer *l = va_arg(params,Layer*);
        while( l ) {
#if CC_ENABLE_GC_FOR_NATIVE_OBJECTS
            if (sEngine)
            {
                sEngine->retainScriptObject(this, l);
            }
#endif // CC_ENABLE_GC_FOR_NATIVE_OBJECTS
            _layers.pushBack(l);
            l = va_arg(params,Layer*);
        }

        _enabledLayer = 0;
        this->addChild(_layers.at(_enabledLayer));
        return true;
    }

    return false;
}

bool LayerMultiplex::initWithArray(const Vector<Layer*>& arrayOfLayers)
{
    if (Layer::init())
    {
#if CC_ENABLE_GC_FOR_NATIVE_OBJECTS
        auto sEngine = ScriptEngineManager::getInstance()->getScriptEngine();
        if (sEngine)
        {
            for (const auto &layer : arrayOfLayers)
            {
                if (layer)
                {
                    sEngine->retainScriptObject(this, layer);
                }
            }
        }
#endif // CC_ENABLE_GC_FOR_NATIVE_OBJECTS
        _layers.reserve(arrayOfLayers.size());
        _layers.pushBack(arrayOfLayers);

        _enabledLayer = 0;
        this->addChild(_layers.at(_enabledLayer));
        return true;
    }
    return false;
}

void LayerMultiplex::switchTo(int n)
{
    
    switchTo(n, true);
}

void LayerMultiplex::switchTo(int n, bool cleanup)
{
    CCASSERT( n < _layers.size(), "Invalid index in MultiplexLayer switchTo message" );
    
    this->removeChild(_layers.at(_enabledLayer), cleanup);
    
    _enabledLayer = n;
    
    this->addChild(_layers.at(n));
}

void LayerMultiplex::switchToAndReleaseMe(int n)
{
    CCASSERT( n < _layers.size(), "Invalid index in MultiplexLayer switchTo message" );

    this->removeChild(_layers.at(_enabledLayer), true);
#if CC_ENABLE_GC_FOR_NATIVE_OBJECTS
    auto sEngine = ScriptEngineManager::getInstance()->getScriptEngine();
    if (sEngine)
    {
        sEngine->releaseScriptObject(this, _layers.at(_enabledLayer));
    }
#endif // CC_ENABLE_GC_FOR_NATIVE_OBJECTS
    
    _layers.replace(_enabledLayer, nullptr);

    _enabledLayer = n;

    this->addChild(_layers.at(n));
}

std::string LayerMultiplex::getDescription() const
{
    return StringUtils::format("<LayerMultiplex | Tag = %d, Layers = %d", _tag, static_cast<int>(_children.size()));
}

NS_CC_END
