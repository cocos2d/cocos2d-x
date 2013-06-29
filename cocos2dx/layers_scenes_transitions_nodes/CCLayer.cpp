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
#include "touch_dispatcher/CCTouchDispatcher.h"
#include "keypad_dispatcher/CCKeypadDispatcher.h"
#include "CCAccelerometer.h"
#include "CCDirector.h"
#include "support/CCPointExtension.h"
#include "script_support/CCScriptSupport.h"
#include "shaders/CCShaderCache.h"
#include "shaders/CCGLProgram.h"
#include "shaders/ccGLStateCache.h"
#include "support/TransformUtils.h"
// extern
#include "kazmath/GL/matrix.h"
#ifdef KEYBOARD_SUPPORT
#include "keyboard_dispatcher/CCKeyboardDispatcher.h"
#endif

NS_CC_BEGIN

// CCLayer
CCLayer::CCLayer()
: _touchEnabled(false)
, _accelerometerEnabled(false)
#ifdef KEYBOARD_SUPPORT
, _keyboardEnabled(false)
#endif
, _keypadEnabled(false)
, _scriptTouchHandlerEntry(NULL)
, _scriptKeypadHandlerEntry(NULL)
, _scriptAccelerateHandlerEntry(NULL)
, _touchPriority(0)
, _touchMode(kCCTouchesAllAtOnce)
{
    _ignoreAnchorPointForPosition = true;
    setAnchorPoint(ccp(0.5f, 0.5f));
}

CCLayer::~CCLayer()
{
    unregisterScriptTouchHandler();
    unregisterScriptKeypadHandler();
    unregisterScriptAccelerateHandler();
}

bool CCLayer::init()
{
    bool bRet = false;
    do 
    {        
        CCDirector * pDirector;
        CC_BREAK_IF(!(pDirector = CCDirector::sharedDirector()));
        this->setContentSize(pDirector->getWinSize());
        _touchEnabled = false;
        _accelerometerEnabled = false;
        // success
        bRet = true;
    } while(0);
    return bRet;
}

CCLayer *CCLayer::create()
{
    CCLayer *pRet = new CCLayer();
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

void CCLayer::registerWithTouchDispatcher()
{
    CCTouchDispatcher* pDispatcher = CCDirector::sharedDirector()->getTouchDispatcher();

    // Using LuaBindings
    if (_scriptTouchHandlerEntry)
    {
	    if (_scriptTouchHandlerEntry->isMultiTouches())
	    {
	       pDispatcher->addStandardDelegate(this, 0);
	       LUALOG("[LUA] Add multi-touches event handler: %d", _scriptTouchHandlerEntry->getHandler());
	    }
	    else
	    {
	       pDispatcher->addTargetedDelegate(this,
						_scriptTouchHandlerEntry->getPriority(),
						_scriptTouchHandlerEntry->getSwallowsTouches());
	       LUALOG("[LUA] Add touch event handler: %d", _scriptTouchHandlerEntry->getHandler());
	    }
    }
    else
    {
        if( _touchMode == kCCTouchesAllAtOnce ) {
            pDispatcher->addStandardDelegate(this, 0);
        } else {
            pDispatcher->addTargetedDelegate(this, _touchPriority, true);
        }
    }
}

void CCLayer::registerScriptTouchHandler(int nHandler, bool bIsMultiTouches, int nPriority, bool bSwallowsTouches)
{
    unregisterScriptTouchHandler();
    _scriptTouchHandlerEntry = CCTouchScriptHandlerEntry::create(nHandler, bIsMultiTouches, nPriority, bSwallowsTouches);
    _scriptTouchHandlerEntry->retain();
}

void CCLayer::unregisterScriptTouchHandler(void)
{
    CC_SAFE_RELEASE_NULL(_scriptTouchHandlerEntry);
    }

int CCLayer::excuteScriptTouchHandler(int nEventType, CCTouch *pTouch)
{
    return CCScriptEngineManager::sharedManager()->getScriptEngine()->executeLayerTouchEvent(this, nEventType, pTouch);
}

int CCLayer::excuteScriptTouchHandler(int nEventType, CCSet *pTouches)
{
    return CCScriptEngineManager::sharedManager()->getScriptEngine()->executeLayerTouchesEvent(this, nEventType, pTouches);
}

/// isTouchEnabled getter
bool CCLayer::isTouchEnabled()
{
    return _touchEnabled;
}
/// isTouchEnabled setter
void CCLayer::setTouchEnabled(bool enabled)
{
    if (_touchEnabled != enabled)
    {
        _touchEnabled = enabled;
        if (_running)
        {
            if (enabled)
            {
                this->registerWithTouchDispatcher();
            }
            else
            {
                // have problems?
                CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
            }
        }
    }
}

void CCLayer::setTouchMode(ccTouchesMode mode)
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

void CCLayer::setTouchPriority(int priority)
{
    if (_touchPriority != priority)
    {
        _touchPriority = priority;
        
		if( _touchEnabled)
        {
			setTouchEnabled(false);
			setTouchEnabled(true);
		}
    }
}

int CCLayer::getTouchPriority()
{
    return _touchPriority;
}

int CCLayer::getTouchMode()
{
    return _touchMode;
}

/// isAccelerometerEnabled getter
bool CCLayer::isAccelerometerEnabled()
{
    return _accelerometerEnabled;
}
/// isAccelerometerEnabled setter
void CCLayer::setAccelerometerEnabled(bool enabled)
{
    if (enabled != _accelerometerEnabled)
    {
        _accelerometerEnabled = enabled;

        if (_running)
        {
            CCDirector* pDirector = CCDirector::sharedDirector();
            if (enabled)
            {
                pDirector->getAccelerometer()->setDelegate(this);
            }
            else
            {
                pDirector->getAccelerometer()->setDelegate(NULL);
            }
        }
    }
}


void CCLayer::setAccelerometerInterval(double interval) {
    if (_accelerometerEnabled)
    {
        if (_running)
        {
            CCDirector* pDirector = CCDirector::sharedDirector();
            pDirector->getAccelerometer()->setAccelerometerInterval(interval);
        }
    }
}


void CCLayer::didAccelerate(CCAcceleration* pAccelerationValue)
{
   CC_UNUSED_PARAM(pAccelerationValue);
   if ( _scriptType != kScriptTypeNone)
   {
       CCScriptEngineManager::sharedManager()->getScriptEngine()->executeAccelerometerEvent(this, pAccelerationValue);
   }
}

void CCLayer::registerScriptAccelerateHandler(int nHandler)
{
    unregisterScriptAccelerateHandler();
    _scriptAccelerateHandlerEntry = CCScriptHandlerEntry::create(nHandler);
    _scriptAccelerateHandlerEntry->retain();
}

void CCLayer::unregisterScriptAccelerateHandler(void)
{
    CC_SAFE_RELEASE_NULL(_scriptAccelerateHandlerEntry);
}

#ifdef KEYBOARD_SUPPORT
/// isKeyboardEnabled getter
bool CCLayer::isKeyboardEnabled()
{
    return _keyboardEnabled;
}
/// isKeyboardEnabled setter
void CCLayer::setKeyboardEnabled(bool enabled)
{
    if (enabled != _keyboardEnabled)
    {
        _keyboardEnabled = enabled;

        CCDirector* pDirector = CCDirector::sharedDirector();
        if (enabled)
        {
            pDirector->getKeyboardDispatcher()->setKeyPressDelegate( CC_CALLBACK_1(CCLayer::keyPressed, this) );
            pDirector->getKeyboardDispatcher()->setKeyReleaseDelegate( CC_CALLBACK_1(CCLayer::keyReleased, this) );
        }
        else
        {
            pDirector->getKeyboardDispatcher()->setKeyPressDelegate(NULL);
            pDirector->getKeyboardDispatcher()->setKeyReleaseDelegate(NULL);
        }
    }
}
#endif

/// isKeypadEnabled getter
bool CCLayer::isKeypadEnabled()
{
    return _keypadEnabled;
}
/// isKeypadEnabled setter
void CCLayer::setKeypadEnabled(bool enabled)
{
    if (enabled != _keypadEnabled)
    {
        _keypadEnabled = enabled;

        if (_running)
        {
            CCDirector* pDirector = CCDirector::sharedDirector();
            if (enabled)
            {
                pDirector->getKeypadDispatcher()->addDelegate(this);
            }
            else
            {
                pDirector->getKeypadDispatcher()->removeDelegate(this);
            }
        }
    }
}

void CCLayer::registerScriptKeypadHandler(int nHandler)
{
    unregisterScriptKeypadHandler();
    _scriptKeypadHandlerEntry = CCScriptHandlerEntry::create(nHandler);
    _scriptKeypadHandlerEntry->retain();
}

void CCLayer::unregisterScriptKeypadHandler(void)
{
    CC_SAFE_RELEASE_NULL(_scriptKeypadHandlerEntry);
}

void CCLayer::keyBackClicked(void)
{
    if (_scriptKeypadHandlerEntry || _scriptType == kScriptTypeJavascript)
    {
        CCScriptEngineManager::sharedManager()->getScriptEngine()->executeLayerKeypadEvent(this, kTypeBackClicked);
    }
}

void CCLayer::keyMenuClicked(void)
{
    if (_scriptKeypadHandlerEntry)
    {
        CCScriptEngineManager::sharedManager()->getScriptEngine()->executeLayerKeypadEvent(this, kTypeMenuClicked);
    }
}

/// Callbacks
void CCLayer::onEnter()
{
    CCDirector* pDirector = CCDirector::sharedDirector();
    // register 'parent' nodes first
    // since events are propagated in reverse order
    if (_touchEnabled)
    {
        this->registerWithTouchDispatcher();
    }

    // then iterate over all the children
    CCNode::onEnter();

    // add this layer to concern the Accelerometer Sensor
    if (_accelerometerEnabled)
    {
        pDirector->getAccelerometer()->setDelegate(this);
    }

    // add this layer to concern the keypad msg
    if (_keypadEnabled)
    {
        pDirector->getKeypadDispatcher()->addDelegate(this);
    }
}

void CCLayer::onExit()
{
    CCDirector* pDirector = CCDirector::sharedDirector();
    if( _touchEnabled )
    {
        pDirector->getTouchDispatcher()->removeDelegate(this);
        // [lua]:don't unregister script touch handler, or the handler will be destroyed
        // unregisterScriptTouchHandler();
    }

    // remove this layer from the delegates who concern Accelerometer Sensor
    if (_accelerometerEnabled)
    {
        pDirector->getAccelerometer()->setDelegate(NULL);
    }

    // remove this layer from the delegates who concern the keypad msg
    if (_keypadEnabled)
    {
        pDirector->getKeypadDispatcher()->removeDelegate(this);
    }

    CCNode::onExit();
}

void CCLayer::onEnterTransitionDidFinish()
{
    if (_accelerometerEnabled)
    {
        CCDirector* pDirector = CCDirector::sharedDirector();
        pDirector->getAccelerometer()->setDelegate(this);
    }
    
    CCNode::onEnterTransitionDidFinish();
}

bool CCLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    if (kScriptTypeNone != _scriptType)
    {
        return excuteScriptTouchHandler(CCTOUCHBEGAN, pTouch) == 0 ? false : true;
    }

    CC_UNUSED_PARAM(pTouch);
    CC_UNUSED_PARAM(pEvent);
    CCAssert(false, "Layer#ccTouchBegan override me");
    return true;
}

void CCLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    if (kScriptTypeNone != _scriptType)
    {
        excuteScriptTouchHandler(CCTOUCHMOVED, pTouch);
        return;
    }

    CC_UNUSED_PARAM(pTouch);
    CC_UNUSED_PARAM(pEvent);
}
    
void CCLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    if (kScriptTypeNone != _scriptType)
    {
        excuteScriptTouchHandler(CCTOUCHENDED, pTouch);
        return;
    }

    CC_UNUSED_PARAM(pTouch);
    CC_UNUSED_PARAM(pEvent);
}

void CCLayer::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
    if (kScriptTypeNone != _scriptType)
    {
        excuteScriptTouchHandler(CCTOUCHCANCELLED, pTouch);
        return;
    }

    CC_UNUSED_PARAM(pTouch);
    CC_UNUSED_PARAM(pEvent);
}    

void CCLayer::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
    if (kScriptTypeNone != _scriptType)
    {
        excuteScriptTouchHandler(CCTOUCHBEGAN, pTouches);
        return;
    }

    CC_UNUSED_PARAM(pTouches);
    CC_UNUSED_PARAM(pEvent);
}

void CCLayer::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
    if (kScriptTypeNone != _scriptType)
    {
        excuteScriptTouchHandler(CCTOUCHMOVED, pTouches);
        return;
    }

    CC_UNUSED_PARAM(pTouches);
    CC_UNUSED_PARAM(pEvent);
}

void CCLayer::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
    if (kScriptTypeNone != _scriptType)
    {
        excuteScriptTouchHandler(CCTOUCHENDED, pTouches);
        return;
    }

    CC_UNUSED_PARAM(pTouches);
    CC_UNUSED_PARAM(pEvent);
}

void CCLayer::ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent)
{
    if (kScriptTypeNone != _scriptType)
    {
        excuteScriptTouchHandler(CCTOUCHCANCELLED, pTouches);
        return;
    }

    CC_UNUSED_PARAM(pTouches);
    CC_UNUSED_PARAM(pEvent);
}

// LayerRGBA
CCLayerRGBA::CCLayerRGBA()
: _displayedOpacity(255)
, _realOpacity (255)
, _displayedColor(ccWHITE)
, _realColor(ccWHITE)
, _cascadeOpacityEnabled(false)
, _cascadeColorEnabled(false)
{}

CCLayerRGBA::~CCLayerRGBA() {}

bool CCLayerRGBA::init()
{
	if (CCLayer::init())
    {
        _displayedOpacity = _realOpacity = 255;
        _displayedColor = _realColor = ccWHITE;
        setCascadeOpacityEnabled(false);
        setCascadeColorEnabled(false);
        
        return true;
    }
    else
    {
        return false;
    }
}

GLubyte CCLayerRGBA::getOpacity()
{
	return _realOpacity;
}

GLubyte CCLayerRGBA::getDisplayedOpacity()
{
	return _displayedOpacity;
}

/** Override synthesized setOpacity to recurse items */
void CCLayerRGBA::setOpacity(GLubyte opacity)
{
	_displayedOpacity = _realOpacity = opacity;
    
	if( _cascadeOpacityEnabled )
    {
		GLubyte parentOpacity = 255;
        CCRGBAProtocol *parent = dynamic_cast<CCRGBAProtocol*>(_parent);
        if (parent && parent->isCascadeOpacityEnabled())
        {
            parentOpacity = parent->getDisplayedOpacity();
        }
        updateDisplayedOpacity(parentOpacity);
	}
}

const ccColor3B& CCLayerRGBA::getColor()
{
	return _realColor;
}

const ccColor3B& CCLayerRGBA::getDisplayedColor()
{
	return _displayedColor;
}

void CCLayerRGBA::setColor(const ccColor3B& color)
{
	_displayedColor = _realColor = color;
	
	if (_cascadeColorEnabled)
    {
		ccColor3B parentColor = ccWHITE;
        CCRGBAProtocol* parent = dynamic_cast<CCRGBAProtocol*>(_parent);
		if (parent && parent->isCascadeColorEnabled())
        {
            parentColor = parent->getDisplayedColor();
        }

        updateDisplayedColor(parentColor);
	}
}

void CCLayerRGBA::updateDisplayedOpacity(GLubyte parentOpacity)
{
	_displayedOpacity = _realOpacity * parentOpacity/255.0;
    
    if (_cascadeOpacityEnabled)
    {
        CCObject *obj = NULL;
        CCARRAY_FOREACH(_children, obj)
        {
            CCRGBAProtocol *item = dynamic_cast<CCRGBAProtocol*>(obj);
            if (item)
            {
                item->updateDisplayedOpacity(_displayedOpacity);
            }
        }
    }
}

void CCLayerRGBA::updateDisplayedColor(const ccColor3B& parentColor)
{
	_displayedColor.r = _realColor.r * parentColor.r/255.0;
	_displayedColor.g = _realColor.g * parentColor.g/255.0;
	_displayedColor.b = _realColor.b * parentColor.b/255.0;
    
    if (_cascadeColorEnabled)
    {
        CCObject *obj = NULL;
        CCARRAY_FOREACH(_children, obj)
        {
            CCRGBAProtocol *item = dynamic_cast<CCRGBAProtocol*>(obj);
            if (item)
            {
                item->updateDisplayedColor(_displayedColor);
            }
        }
    }
}

bool CCLayerRGBA::isCascadeOpacityEnabled()
{
    return _cascadeOpacityEnabled;
}

void CCLayerRGBA::setCascadeOpacityEnabled(bool cascadeOpacityEnabled)
{
    _cascadeOpacityEnabled = cascadeOpacityEnabled;
}

bool CCLayerRGBA::isCascadeColorEnabled()
{
    return _cascadeColorEnabled;
}

void CCLayerRGBA::setCascadeColorEnabled(bool cascadeColorEnabled)
{
    _cascadeColorEnabled = cascadeColorEnabled;
}

/// CCLayerColor

CCLayerColor::CCLayerColor()
{
    // default blend function
    _blendFunc.src = CC_BLEND_SRC;
    _blendFunc.dst = CC_BLEND_DST;
}
    
CCLayerColor::~CCLayerColor()
{
}

/// blendFunc getter
ccBlendFunc CCLayerColor::getBlendFunc()
{
    return _blendFunc;
}
/// blendFunc setter
void CCLayerColor::setBlendFunc(ccBlendFunc var)
{
    _blendFunc = var;
}

CCLayerColor* CCLayerColor::create()
{
    CCLayerColor* pRet = new CCLayerColor();
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

CCLayerColor * CCLayerColor::create(const ccColor4B& color, GLfloat width, GLfloat height)
{
    CCLayerColor * pLayer = new CCLayerColor();
    if( pLayer && pLayer->initWithColor(color,width,height))
    {
        pLayer->autorelease();
        return pLayer;
    }
    CC_SAFE_DELETE(pLayer);
    return NULL;
}

CCLayerColor * CCLayerColor::create(const ccColor4B& color)
{
    CCLayerColor * pLayer = new CCLayerColor();
    if(pLayer && pLayer->initWithColor(color))
    {
        pLayer->autorelease();
        return pLayer;
    }
    CC_SAFE_DELETE(pLayer);
    return NULL;
}

bool CCLayerColor::init()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    return initWithColor(ccc4(0,0,0,0), s.width, s.height);
}

bool CCLayerColor::initWithColor(const ccColor4B& color, GLfloat w, GLfloat h)
{
    if (CCLayer::init())
    {

        // default blend function
        _blendFunc.src = GL_SRC_ALPHA;
        _blendFunc.dst = GL_ONE_MINUS_SRC_ALPHA;

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
        setContentSize(CCSizeMake(w, h));

        setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionColor));
    }
    return true;
}

bool CCLayerColor::initWithColor(const ccColor4B& color)
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    this->initWithColor(color, s.width, s.height);
    return true;
}

/// override contentSize
void CCLayerColor::setContentSize(const CCSize & size)
{
    _squareVertices[1].x = size.width;
    _squareVertices[2].y = size.height;
    _squareVertices[3].x = size.width;
    _squareVertices[3].y = size.height;

    CCLayer::setContentSize(size);
}

void CCLayerColor::changeWidthAndHeight(GLfloat w ,GLfloat h)
{
    this->setContentSize(CCSizeMake(w, h));
}

void CCLayerColor::changeWidth(GLfloat w)
{
    this->setContentSize(CCSizeMake(w, _contentSize.height));
}

void CCLayerColor::changeHeight(GLfloat h)
{
    this->setContentSize(CCSizeMake(_contentSize.width, h));
}

void CCLayerColor::updateColor()
{
    for( unsigned int i=0; i < 4; i++ )
    {
        _squareColors[i].r = _displayedColor.r / 255.0f;
        _squareColors[i].g = _displayedColor.g / 255.0f;
        _squareColors[i].b = _displayedColor.b / 255.0f;
        _squareColors[i].a = _displayedOpacity / 255.0f;
    }
}

void CCLayerColor::draw()
{
    CC_NODE_DRAW_SETUP();

    ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position | kCCVertexAttribFlag_Color );

    //
    // Attributes
    //
#ifdef EMSCRIPTEN
    setGLBufferData(_squareVertices, 4 * sizeof(ccVertex2F), 0);
    glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, 0);

    setGLBufferData(_squareColors, 4 * sizeof(ccColor4F), 1);
    glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_FLOAT, GL_FALSE, 0, 0);
#else
    glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, _squareVertices);
    glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_FLOAT, GL_FALSE, 0, _squareColors);
#endif // EMSCRIPTEN

    ccGLBlendFunc( _blendFunc.src, _blendFunc.dst );

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    CC_INCREMENT_GL_DRAWS(1);
}

void CCLayerColor::setColor(const ccColor3B &color)
{
    CCLayerRGBA::setColor(color);
    updateColor();
}

void CCLayerColor::setOpacity(GLubyte opacity)
{
    CCLayerRGBA::setOpacity(opacity);
    updateColor();
}

//
// CCLayerGradient
// 

CCLayerGradient* CCLayerGradient::create(const ccColor4B& start, const ccColor4B& end)
{
    CCLayerGradient * pLayer = new CCLayerGradient();
    if( pLayer && pLayer->initWithColor(start, end))
    {
        pLayer->autorelease();
        return pLayer;
    }
    CC_SAFE_DELETE(pLayer);
    return NULL;
}

CCLayerGradient* CCLayerGradient::create(const ccColor4B& start, const ccColor4B& end, const CCPoint& v)
{
    CCLayerGradient * pLayer = new CCLayerGradient();
    if( pLayer && pLayer->initWithColor(start, end, v))
    {
        pLayer->autorelease();
        return pLayer;
    }
    CC_SAFE_DELETE(pLayer);
    return NULL;
}

CCLayerGradient* CCLayerGradient::create()
{
    CCLayerGradient* pRet = new CCLayerGradient();
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

bool CCLayerGradient::init()
{
	return initWithColor(ccc4(0, 0, 0, 255), ccc4(0, 0, 0, 255));
}

bool CCLayerGradient::initWithColor(const ccColor4B& start, const ccColor4B& end)
{
    return initWithColor(start, end, ccp(0, -1));
}

bool CCLayerGradient::initWithColor(const ccColor4B& start, const ccColor4B& end, const CCPoint& v)
{
    _endColor.r  = end.r;
    _endColor.g  = end.g;
    _endColor.b  = end.b;

    _endOpacity   = end.a;
    _startOpacity    = start.a;
    _alongVector   = v;

    _compressedInterpolation = true;

    return CCLayerColor::initWithColor(ccc4(start.r, start.g, start.b, 255));
}

void CCLayerGradient::updateColor()
{
    CCLayerColor::updateColor();

    float h = ccpLength(_alongVector);
    if (h == 0)
        return;

    float c = sqrtf(2.0f);
    CCPoint u = ccp(_alongVector.x / h, _alongVector.y / h);

    // Compressed Interpolation mode
    if (_compressedInterpolation)
    {
        float h2 = 1 / ( fabsf(u.x) + fabsf(u.y) );
        u = ccpMult(u, h2 * (float)c);
    }

    float opacityf = (float)_displayedOpacity / 255.0f;

    ccColor4F S = {
        _displayedColor.r / 255.0f,
        _displayedColor.g / 255.0f,
        _displayedColor.b / 255.0f,
        _startOpacity * opacityf / 255.0f
    };

    ccColor4F E = {
        _endColor.r / 255.0f,
        _endColor.g / 255.0f,
        _endColor.b / 255.0f,
        _endOpacity * opacityf / 255.0f
    };

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

const ccColor3B& CCLayerGradient::getStartColor()
{
    return _realColor;
}

void CCLayerGradient::setStartColor(const ccColor3B& color)
{
    setColor(color);
}

void CCLayerGradient::setEndColor(const ccColor3B& color)
{
    _endColor = color;
    updateColor();
}

const ccColor3B& CCLayerGradient::getEndColor()
{
    return _endColor;
}

void CCLayerGradient::setStartOpacity(GLubyte o)
{
    _startOpacity = o;
    updateColor();
}

GLubyte CCLayerGradient::getStartOpacity()
{
    return _startOpacity;
}

void CCLayerGradient::setEndOpacity(GLubyte o)
{
    _endOpacity = o;
    updateColor();
}

GLubyte CCLayerGradient::getEndOpacity()
{
    return _endOpacity;
}

void CCLayerGradient::setVector(const CCPoint& var)
{
    _alongVector = var;
    updateColor();
}

const CCPoint& CCLayerGradient::getVector()
{
    return _alongVector;
}

bool CCLayerGradient::isCompressedInterpolation()
{
    return _compressedInterpolation;
}

void CCLayerGradient::setCompressedInterpolation(bool compress)
{
    _compressedInterpolation = compress;
    updateColor();
}

/// MultiplexLayer

CCLayerMultiplex::CCLayerMultiplex()
: _enabledLayer(0)
, _layers(NULL)
{
}
CCLayerMultiplex::~CCLayerMultiplex()
{
    CC_SAFE_RELEASE(_layers);
}

CCLayerMultiplex * CCLayerMultiplex::create(CCLayer * layer, ...)
{
    va_list args;
    va_start(args,layer);

    CCLayerMultiplex * pMultiplexLayer = new CCLayerMultiplex();
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

CCLayerMultiplex * CCLayerMultiplex::createWithLayer(CCLayer* layer)
{
    return CCLayerMultiplex::create(layer, NULL);
}

CCLayerMultiplex* CCLayerMultiplex::create()
{
    CCLayerMultiplex* pRet = new CCLayerMultiplex();
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

CCLayerMultiplex* CCLayerMultiplex::createWithArray(CCArray* arrayOfLayers)
{
    CCLayerMultiplex* pRet = new CCLayerMultiplex();
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

void CCLayerMultiplex::addLayer(CCLayer* layer)
{
    CCAssert(_layers, "");
    _layers->addObject(layer);
}

bool CCLayerMultiplex::initWithLayers(CCLayer *layer, va_list params)
{
    if (CCLayer::init())
    {
        _layers = CCArray::createWithCapacity(5);
        _layers->retain();
        _layers->addObject(layer);

        CCLayer *l = va_arg(params,CCLayer*);
        while( l ) {
            _layers->addObject(l);
            l = va_arg(params,CCLayer*);
        }

        _enabledLayer = 0;
        this->addChild((CCNode*)_layers->objectAtIndex(_enabledLayer));
        return true;
    }

    return false;
}

bool CCLayerMultiplex::initWithArray(CCArray* arrayOfLayers)
{
    if (CCLayer::init())
    {
        _layers = CCArray::createWithCapacity(arrayOfLayers->count());
        _layers->addObjectsFromArray(arrayOfLayers);
        _layers->retain();

        _enabledLayer = 0;
        this->addChild((CCNode*)_layers->objectAtIndex(_enabledLayer));
        return true;
    }
    return false;
}

void CCLayerMultiplex::switchTo(unsigned int n)
{
    CCAssert( n < _layers->count(), "Invalid index in MultiplexLayer switchTo message" );

    this->removeChild((CCNode*)_layers->objectAtIndex(_enabledLayer), true);

    _enabledLayer = n;

    this->addChild((CCNode*)_layers->objectAtIndex(n));
}

void CCLayerMultiplex::switchToAndReleaseMe(unsigned int n)
{
    CCAssert( n < _layers->count(), "Invalid index in MultiplexLayer switchTo message" );

    this->removeChild((CCNode*)_layers->objectAtIndex(_enabledLayer), true);

    //[layers replaceObjectAtIndex:enabledLayer withObject:[NSNull null]];
    _layers->replaceObjectAtIndex(_enabledLayer, NULL);

    _enabledLayer = n;

    this->addChild((CCNode*)_layers->objectAtIndex(n));
}

NS_CC_END
