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

NS_CC_BEGIN

// CCLayer
CCLayer::CCLayer()
: m_bTouchEnabled(false)
, m_bAccelerometerEnabled(false)
, m_bKeypadEnabled(false)
, m_pScriptTouchHandlerEntry(NULL)
, m_pScriptKeypadHandlerEntry(NULL)
, m_pScriptAccelerateHandlerEntry(NULL)
, m_nTouchPriority(0)
, m_eTouchMode(kCCTouchesAllAtOnce)
{
    m_bIgnoreAnchorPointForPosition = true;
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
        m_bTouchEnabled = false;
        m_bAccelerometerEnabled = false;
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
    if (m_pScriptTouchHandlerEntry)
    {
	    if (m_pScriptTouchHandlerEntry->isMultiTouches())
	    {
	       pDispatcher->addStandardDelegate(this, 0);
	       LUALOG("[LUA] Add multi-touches event handler: %d", m_pScriptTouchHandlerEntry->getHandler());
	    }
	    else
	    {
	       pDispatcher->addTargetedDelegate(this,
						m_pScriptTouchHandlerEntry->getPriority(),
						m_pScriptTouchHandlerEntry->getSwallowsTouches());
	       LUALOG("[LUA] Add touch event handler: %d", m_pScriptTouchHandlerEntry->getHandler());
	    }
    }
    else
    {
        if( m_eTouchMode == kCCTouchesAllAtOnce ) {
            pDispatcher->addStandardDelegate(this, 0);
        } else {
            pDispatcher->addTargetedDelegate(this, m_nTouchPriority, true);
        }
    }
}

void CCLayer::registerScriptTouchHandler(int nHandler, bool bIsMultiTouches, int nPriority, bool bSwallowsTouches)
{
    unregisterScriptTouchHandler();
    m_pScriptTouchHandlerEntry = CCTouchScriptHandlerEntry::create(nHandler, bIsMultiTouches, nPriority, bSwallowsTouches);
    m_pScriptTouchHandlerEntry->retain();
}

void CCLayer::unregisterScriptTouchHandler(void)
{
    CC_SAFE_RELEASE_NULL(m_pScriptTouchHandlerEntry);
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
    return m_bTouchEnabled;
}
/// isTouchEnabled setter
void CCLayer::setTouchEnabled(bool enabled)
{
    if (m_bTouchEnabled != enabled)
    {
        m_bTouchEnabled = enabled;
        if (m_bRunning)
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
    if(m_eTouchMode != mode)
    {
        m_eTouchMode = mode;
        
		if( m_bTouchEnabled)
        {
			setTouchEnabled(false);
			setTouchEnabled(true);
		}
    }
}

void CCLayer::setTouchPriority(int priority)
{
    if (m_nTouchPriority != priority)
    {
        m_nTouchPriority = priority;
        
		if( m_bTouchEnabled)
        {
			setTouchEnabled(false);
			setTouchEnabled(true);
		}
    }
}

int CCLayer::getTouchPriority()
{
    return m_nTouchPriority;
}

int CCLayer::getTouchMode()
{
    return m_eTouchMode;
}

/// isAccelerometerEnabled getter
bool CCLayer::isAccelerometerEnabled()
{
    return m_bAccelerometerEnabled;
}
/// isAccelerometerEnabled setter
void CCLayer::setAccelerometerEnabled(bool enabled)
{
    if (enabled != m_bAccelerometerEnabled)
    {
        m_bAccelerometerEnabled = enabled;

        if (m_bRunning)
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
    if (m_bAccelerometerEnabled)
    {
        if (m_bRunning)
        {
            CCDirector* pDirector = CCDirector::sharedDirector();
            pDirector->getAccelerometer()->setAccelerometerInterval(interval);
        }
    }
}


void CCLayer::didAccelerate(CCAcceleration* pAccelerationValue)
{
   CC_UNUSED_PARAM(pAccelerationValue);
   if ( m_eScriptType != kScriptTypeNone)
   {
       CCScriptEngineManager::sharedManager()->getScriptEngine()->executeAccelerometerEvent(this, pAccelerationValue);
   }
}

void CCLayer::registerScriptAccelerateHandler(int nHandler)
{
    unregisterScriptAccelerateHandler();
    m_pScriptAccelerateHandlerEntry = CCScriptHandlerEntry::create(nHandler);
    m_pScriptAccelerateHandlerEntry->retain();
}

void CCLayer::unregisterScriptAccelerateHandler(void)
{
    CC_SAFE_RELEASE_NULL(m_pScriptAccelerateHandlerEntry);
}

/// isKeypadEnabled getter
bool CCLayer::isKeypadEnabled()
{
    return m_bKeypadEnabled;
}
/// isKeypadEnabled setter
void CCLayer::setKeypadEnabled(bool enabled)
{
    if (enabled != m_bKeypadEnabled)
    {
        m_bKeypadEnabled = enabled;

        if (m_bRunning)
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
    m_pScriptKeypadHandlerEntry = CCScriptHandlerEntry::create(nHandler);
    m_pScriptKeypadHandlerEntry->retain();
}

void CCLayer::unregisterScriptKeypadHandler(void)
{
    CC_SAFE_RELEASE_NULL(m_pScriptKeypadHandlerEntry);
}

void CCLayer::keyBackClicked(void)
{
    if (m_pScriptKeypadHandlerEntry || m_eScriptType == kScriptTypeJavascript)
    {
        CCScriptEngineManager::sharedManager()->getScriptEngine()->executeLayerKeypadEvent(this, kTypeBackClicked);
    }
}

void CCLayer::keyMenuClicked(void)
{
    if (m_pScriptKeypadHandlerEntry)
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
    if (m_bTouchEnabled)
    {
        this->registerWithTouchDispatcher();
    }

    // then iterate over all the children
    CCNode::onEnter();

    // add this layer to concern the Accelerometer Sensor
    if (m_bAccelerometerEnabled)
    {
        pDirector->getAccelerometer()->setDelegate(this);
    }

    // add this layer to concern the keypad msg
    if (m_bKeypadEnabled)
    {
        pDirector->getKeypadDispatcher()->addDelegate(this);
    }
}

void CCLayer::onExit()
{
    CCDirector* pDirector = CCDirector::sharedDirector();
    if( m_bTouchEnabled )
    {
        pDirector->getTouchDispatcher()->removeDelegate(this);
        // [lua]:don't unregister script touch handler, or the handler will be destroyed
        // unregisterScriptTouchHandler();
    }

    // remove this layer from the delegates who concern Accelerometer Sensor
    if (m_bAccelerometerEnabled)
    {
        pDirector->getAccelerometer()->setDelegate(NULL);
    }

    // remove this layer from the delegates who concern the keypad msg
    if (m_bKeypadEnabled)
    {
        pDirector->getKeypadDispatcher()->removeDelegate(this);
    }

    CCNode::onExit();
}

void CCLayer::onEnterTransitionDidFinish()
{
    if (m_bAccelerometerEnabled)
    {
        CCDirector* pDirector = CCDirector::sharedDirector();
        pDirector->getAccelerometer()->setDelegate(this);
    }
    
    CCNode::onEnterTransitionDidFinish();
}

bool CCLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    if (kScriptTypeNone != m_eScriptType)
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
    if (kScriptTypeNone != m_eScriptType)
    {
        excuteScriptTouchHandler(CCTOUCHMOVED, pTouch);
        return;
    }

    CC_UNUSED_PARAM(pTouch);
    CC_UNUSED_PARAM(pEvent);
}
    
void CCLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    if (kScriptTypeNone != m_eScriptType)
    {
        excuteScriptTouchHandler(CCTOUCHENDED, pTouch);
        return;
    }

    CC_UNUSED_PARAM(pTouch);
    CC_UNUSED_PARAM(pEvent);
}

void CCLayer::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
    if (kScriptTypeNone != m_eScriptType)
    {
        excuteScriptTouchHandler(CCTOUCHCANCELLED, pTouch);
        return;
    }

    CC_UNUSED_PARAM(pTouch);
    CC_UNUSED_PARAM(pEvent);
}    

void CCLayer::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
    if (kScriptTypeNone != m_eScriptType)
    {
        excuteScriptTouchHandler(CCTOUCHBEGAN, pTouches);
        return;
    }

    CC_UNUSED_PARAM(pTouches);
    CC_UNUSED_PARAM(pEvent);
}

void CCLayer::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
    if (kScriptTypeNone != m_eScriptType)
    {
        excuteScriptTouchHandler(CCTOUCHMOVED, pTouches);
        return;
    }

    CC_UNUSED_PARAM(pTouches);
    CC_UNUSED_PARAM(pEvent);
}

void CCLayer::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
    if (kScriptTypeNone != m_eScriptType)
    {
        excuteScriptTouchHandler(CCTOUCHENDED, pTouches);
        return;
    }

    CC_UNUSED_PARAM(pTouches);
    CC_UNUSED_PARAM(pEvent);
}

void CCLayer::ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent)
{
    if (kScriptTypeNone != m_eScriptType)
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
        CCRGBAProtocol *parent = dynamic_cast<CCRGBAProtocol*>(m_pParent);
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
        CCRGBAProtocol* parent = dynamic_cast<CCRGBAProtocol*>(m_pParent);
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
        CCARRAY_FOREACH(m_pChildren, obj)
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
        CCARRAY_FOREACH(m_pChildren, obj)
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
    m_tBlendFunc.src = CC_BLEND_SRC;
    m_tBlendFunc.dst = CC_BLEND_DST;
}
    
CCLayerColor::~CCLayerColor()
{
}

/// blendFunc getter
ccBlendFunc CCLayerColor::getBlendFunc()
{
    return m_tBlendFunc;
}
/// blendFunc setter
void CCLayerColor::setBlendFunc(ccBlendFunc var)
{
    m_tBlendFunc = var;
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
        m_tBlendFunc.src = GL_SRC_ALPHA;
        m_tBlendFunc.dst = GL_ONE_MINUS_SRC_ALPHA;

        _displayedColor.r = _realColor.r = color.r;
        _displayedColor.g = _realColor.g = color.g;
        _displayedColor.b = _realColor.b = color.b;
        _displayedOpacity = _realOpacity = color.a;

        for (size_t i = 0; i<sizeof(m_pSquareVertices) / sizeof( m_pSquareVertices[0]); i++ )
        {
            m_pSquareVertices[i].x = 0.0f;
            m_pSquareVertices[i].y = 0.0f;
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
    m_pSquareVertices[1].x = size.width;
    m_pSquareVertices[2].y = size.height;
    m_pSquareVertices[3].x = size.width;
    m_pSquareVertices[3].y = size.height;

    CCLayer::setContentSize(size);
}

void CCLayerColor::changeWidthAndHeight(GLfloat w ,GLfloat h)
{
    this->setContentSize(CCSizeMake(w, h));
}

void CCLayerColor::changeWidth(GLfloat w)
{
    this->setContentSize(CCSizeMake(w, m_obContentSize.height));
}

void CCLayerColor::changeHeight(GLfloat h)
{
    this->setContentSize(CCSizeMake(m_obContentSize.width, h));
}

void CCLayerColor::updateColor()
{
    for( unsigned int i=0; i < 4; i++ )
    {
        m_pSquareColors[i].r = _displayedColor.r / 255.0f;
        m_pSquareColors[i].g = _displayedColor.g / 255.0f;
        m_pSquareColors[i].b = _displayedColor.b / 255.0f;
        m_pSquareColors[i].a = _displayedOpacity / 255.0f;
    }
}

void CCLayerColor::draw()
{
    CC_NODE_DRAW_SETUP();

    ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position | kCCVertexAttribFlag_Color );

    //
    // Attributes
    //
    glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, m_pSquareVertices);
    glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_FLOAT, GL_FALSE, 0, m_pSquareColors);

    ccGLBlendFunc( m_tBlendFunc.src, m_tBlendFunc.dst );

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
    m_endColor.r  = end.r;
    m_endColor.g  = end.g;
    m_endColor.b  = end.b;

    m_cEndOpacity   = end.a;
    m_cStartOpacity    = start.a;
    m_AlongVector   = v;

    m_bCompressedInterpolation = true;

    return CCLayerColor::initWithColor(ccc4(start.r, start.g, start.b, 255));
}

void CCLayerGradient::updateColor()
{
    CCLayerColor::updateColor();

    float h = ccpLength(m_AlongVector);
    if (h == 0)
        return;

    float c = sqrtf(2.0f);
    CCPoint u = ccp(m_AlongVector.x / h, m_AlongVector.y / h);

    // Compressed Interpolation mode
    if (m_bCompressedInterpolation)
    {
        float h2 = 1 / ( fabsf(u.x) + fabsf(u.y) );
        u = ccpMult(u, h2 * (float)c);
    }

    float opacityf = (float)_displayedOpacity / 255.0f;

    ccColor4F S = {
        _displayedColor.r / 255.0f,
        _displayedColor.g / 255.0f,
        _displayedColor.b / 255.0f,
        m_cStartOpacity * opacityf / 255.0f
    };

    ccColor4F E = {
        m_endColor.r / 255.0f,
        m_endColor.g / 255.0f,
        m_endColor.b / 255.0f,
        m_cEndOpacity * opacityf / 255.0f
    };

    // (-1, -1)
    m_pSquareColors[0].r = E.r + (S.r - E.r) * ((c + u.x + u.y) / (2.0f * c));
    m_pSquareColors[0].g = E.g + (S.g - E.g) * ((c + u.x + u.y) / (2.0f * c));
    m_pSquareColors[0].b = E.b + (S.b - E.b) * ((c + u.x + u.y) / (2.0f * c));
    m_pSquareColors[0].a = E.a + (S.a - E.a) * ((c + u.x + u.y) / (2.0f * c));
    // (1, -1)
    m_pSquareColors[1].r = E.r + (S.r - E.r) * ((c - u.x + u.y) / (2.0f * c));
    m_pSquareColors[1].g = E.g + (S.g - E.g) * ((c - u.x + u.y) / (2.0f * c));
    m_pSquareColors[1].b = E.b + (S.b - E.b) * ((c - u.x + u.y) / (2.0f * c));
    m_pSquareColors[1].a = E.a + (S.a - E.a) * ((c - u.x + u.y) / (2.0f * c));
    // (-1, 1)
    m_pSquareColors[2].r = E.r + (S.r - E.r) * ((c + u.x - u.y) / (2.0f * c));
    m_pSquareColors[2].g = E.g + (S.g - E.g) * ((c + u.x - u.y) / (2.0f * c));
    m_pSquareColors[2].b = E.b + (S.b - E.b) * ((c + u.x - u.y) / (2.0f * c));
    m_pSquareColors[2].a = E.a + (S.a - E.a) * ((c + u.x - u.y) / (2.0f * c));
    // (1, 1)
    m_pSquareColors[3].r = E.r + (S.r - E.r) * ((c - u.x - u.y) / (2.0f * c));
    m_pSquareColors[3].g = E.g + (S.g - E.g) * ((c - u.x - u.y) / (2.0f * c));
    m_pSquareColors[3].b = E.b + (S.b - E.b) * ((c - u.x - u.y) / (2.0f * c));
    m_pSquareColors[3].a = E.a + (S.a - E.a) * ((c - u.x - u.y) / (2.0f * c));
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
    m_endColor = color;
    updateColor();
}

const ccColor3B& CCLayerGradient::getEndColor()
{
    return m_endColor;
}

void CCLayerGradient::setStartOpacity(GLubyte o)
{
    m_cStartOpacity = o;
    updateColor();
}

GLubyte CCLayerGradient::getStartOpacity()
{
    return m_cStartOpacity;
}

void CCLayerGradient::setEndOpacity(GLubyte o)
{
    m_cEndOpacity = o;
    updateColor();
}

GLubyte CCLayerGradient::getEndOpacity()
{
    return m_cEndOpacity;
}

void CCLayerGradient::setVector(const CCPoint& var)
{
    m_AlongVector = var;
    updateColor();
}

const CCPoint& CCLayerGradient::getVector()
{
    return m_AlongVector;
}

bool CCLayerGradient::isCompressedInterpolation()
{
    return m_bCompressedInterpolation;
}

void CCLayerGradient::setCompressedInterpolation(bool compress)
{
    m_bCompressedInterpolation = compress;
    updateColor();
}

/// MultiplexLayer

CCLayerMultiplex::CCLayerMultiplex()
: m_nEnabledLayer(0)
, m_pLayers(NULL)
{
}
CCLayerMultiplex::~CCLayerMultiplex()
{
    CC_SAFE_RELEASE(m_pLayers);
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
    CCAssert(m_pLayers, "");
    m_pLayers->addObject(layer);
}

bool CCLayerMultiplex::initWithLayers(CCLayer *layer, va_list params)
{
    if (CCLayer::init())
    {
        m_pLayers = CCArray::createWithCapacity(5);
        m_pLayers->retain();
        m_pLayers->addObject(layer);

        CCLayer *l = va_arg(params,CCLayer*);
        while( l ) {
            m_pLayers->addObject(l);
            l = va_arg(params,CCLayer*);
        }

        m_nEnabledLayer = 0;
        this->addChild((CCNode*)m_pLayers->objectAtIndex(m_nEnabledLayer));
        return true;
    }

    return false;
}

bool CCLayerMultiplex::initWithArray(CCArray* arrayOfLayers)
{
    if (CCLayer::init())
    {
        m_pLayers = CCArray::createWithCapacity(arrayOfLayers->count());
        m_pLayers->addObjectsFromArray(arrayOfLayers);
        m_pLayers->retain();

        m_nEnabledLayer = 0;
        this->addChild((CCNode*)m_pLayers->objectAtIndex(m_nEnabledLayer));
        return true;
    }
    return false;
}

void CCLayerMultiplex::switchTo(unsigned int n)
{
    CCAssert( n < m_pLayers->count(), "Invalid index in MultiplexLayer switchTo message" );

    this->removeChild((CCNode*)m_pLayers->objectAtIndex(m_nEnabledLayer), true);

    m_nEnabledLayer = n;

    this->addChild((CCNode*)m_pLayers->objectAtIndex(n));
}

void CCLayerMultiplex::switchToAndReleaseMe(unsigned int n)
{
    CCAssert( n < m_pLayers->count(), "Invalid index in MultiplexLayer switchTo message" );

    this->removeChild((CCNode*)m_pLayers->objectAtIndex(m_nEnabledLayer), true);

    //[layers replaceObjectAtIndex:enabledLayer withObject:[NSNull null]];
    m_pLayers->replaceObjectAtIndex(m_nEnabledLayer, NULL);

    m_nEnabledLayer = n;

    this->addChild((CCNode*)m_pLayers->objectAtIndex(n));
}

NS_CC_END
