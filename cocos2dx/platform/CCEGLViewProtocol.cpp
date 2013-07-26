#include "CCEGLViewProtocol.h"
#include "touch_dispatcher/CCTouchDispatcher.h"
#include "touch_dispatcher/CCTouch.h"
#include "CCDirector.h"
#include "cocoa/CCSet.h"
#include "cocoa/CCDictionary.h"
#include "cocoa/CCInteger.h"

NS_CC_BEGIN

static Touch* s_pTouches[CC_MAX_TOUCHES] = { NULL };
static unsigned int s_indexBitsUsed = 0;
static Dictionary s_TouchesIntergerDict;

static int getUnUsedIndex()
{
    int i;
    int temp = s_indexBitsUsed;

    for (i = 0; i < CC_MAX_TOUCHES; i++) {
        if (! (temp & 0x00000001)) {
            s_indexBitsUsed |= (1 <<  i);
            return i;
        }

        temp >>= 1;
    }

    // all bits are used
    return -1;
}

static void removeUsedIndexBit(int index)
{
    if (index < 0 || index >= CC_MAX_TOUCHES) 
    {
        return;
    }

    unsigned int temp = 1 << index;
    temp = ~temp;
    s_indexBitsUsed &= temp;
}

EGLViewProtocol::EGLViewProtocol()
: _delegate(NULL)
, _scaleX(1.0f)
, _scaleY(1.0f)
, _resolutionPolicy(ResolutionPolicy::UNKNOWN)
{
}

EGLViewProtocol::~EGLViewProtocol()
{

}

void EGLViewProtocol::setDesignResolutionSize(float width, float height, ResolutionPolicy resolutionPolicy)
{
    CCASSERT(resolutionPolicy != ResolutionPolicy::UNKNOWN, "should set resolutionPolicy");
    
    if (width == 0.0f || height == 0.0f)
    {
        return;
    }

    _designResolutionSize.setSize(width, height);
    
    _scaleX = (float)_screenSize.width / _designResolutionSize.width;
    _scaleY = (float)_screenSize.height / _designResolutionSize.height;
    
    if (resolutionPolicy == ResolutionPolicy::NO_BORDER)
    {
        _scaleX = _scaleY = MAX(_scaleX, _scaleY);
    }
    
    if (resolutionPolicy == ResolutionPolicy::SHOW_ALL)
    {
        _scaleX = _scaleY = MIN(_scaleX, _scaleY);
    }

    if ( resolutionPolicy == ResolutionPolicy::FIXED_HEIGHT) {
    	_scaleX = _scaleY;
    	_designResolutionSize.width = ceilf(_screenSize.width/_scaleX);
    }

    if ( resolutionPolicy == ResolutionPolicy::FIXED_WIDTH) {
    	_scaleY = _scaleX;
    	_designResolutionSize.height = ceilf(_screenSize.height/_scaleY);
    }

    // calculate the rect of viewport    
    float viewPortW = _designResolutionSize.width * _scaleX;
    float viewPortH = _designResolutionSize.height * _scaleY;

    _viewPortRect.setRect((_screenSize.width - viewPortW) / 2, (_screenSize.height - viewPortH) / 2, viewPortW, viewPortH);
    
    _resolutionPolicy = resolutionPolicy;
    
	// reset director's member variables to fit visible rect
    Director::getInstance()->_winSizeInPoints = getDesignResolutionSize();
    Director::getInstance()->createStatsLabel();
    Director::getInstance()->setGLDefaultValues();
}

const Size& EGLViewProtocol::getDesignResolutionSize() const 
{
    return _designResolutionSize;
}

const Size& EGLViewProtocol::getFrameSize() const
{
    return _screenSize;
}

void EGLViewProtocol::setFrameSize(float width, float height)
{
    _designResolutionSize = _screenSize = Size(width, height);
}

Size  EGLViewProtocol::getVisibleSize() const
{
    if (_resolutionPolicy == ResolutionPolicy::NO_BORDER)
    {
        return Size(_screenSize.width/_scaleX, _screenSize.height/_scaleY);
    }
    else 
    {
        return _designResolutionSize;
    }
}

Point EGLViewProtocol::getVisibleOrigin() const
{
    if (_resolutionPolicy == ResolutionPolicy::NO_BORDER)
    {
        return Point((_designResolutionSize.width - _screenSize.width/_scaleX)/2, 
                           (_designResolutionSize.height - _screenSize.height/_scaleY)/2);
    }
    else 
    {
        return Point::ZERO;
    }
}

void EGLViewProtocol::setTouchDelegate(EGLTouchDelegate * pDelegate)
{
    _delegate = pDelegate;
}

void EGLViewProtocol::setViewPortInPoints(float x , float y , float w , float h)
{
    glViewport((GLint)(x * _scaleX + _viewPortRect.origin.x),
               (GLint)(y * _scaleY + _viewPortRect.origin.y),
               (GLsizei)(w * _scaleX),
               (GLsizei)(h * _scaleY));
}

void EGLViewProtocol::setScissorInPoints(float x , float y , float w , float h)
{
    glScissor((GLint)(x * _scaleX + _viewPortRect.origin.x),
              (GLint)(y * _scaleY + _viewPortRect.origin.y),
              (GLsizei)(w * _scaleX),
              (GLsizei)(h * _scaleY));
}

bool EGLViewProtocol::isScissorEnabled()
{
	return (GL_FALSE == glIsEnabled(GL_SCISSOR_TEST)) ? false : true;
}

Rect EGLViewProtocol::getScissorRect()
{
	GLfloat params[4];
	glGetFloatv(GL_SCISSOR_BOX, params);
	float x = (params[0] - _viewPortRect.origin.x) / _scaleX;
	float y = (params[1] - _viewPortRect.origin.y) / _scaleY;
	float w = params[2] / _scaleX;
	float h = params[3] / _scaleY;
	return Rect(x, y, w, h);
}

void EGLViewProtocol::setViewName(const char* pszViewName)
{
    if (pszViewName != NULL && strlen(pszViewName) > 0)
    {
        strncpy(_viewName, pszViewName, sizeof(_viewName));
    }
}

const char* EGLViewProtocol::getViewName()
{
    return _viewName;
}

void EGLViewProtocol::handleTouchesBegin(int num, int ids[], float xs[], float ys[])
{
    Set set;
    for (int i = 0; i < num; ++i)
    {
        int id = ids[i];
        float x = xs[i];
        float y = ys[i];

        Integer* pIndex = (Integer*)s_TouchesIntergerDict.objectForKey(id);
        int nUnusedIndex = 0;

        // it is a new touch
        if (pIndex == NULL)
        {
            nUnusedIndex = getUnUsedIndex();

            // The touches is more than MAX_TOUCHES ?
            if (nUnusedIndex == -1) {
                CCLOG("The touches is more than MAX_TOUCHES, nUnusedIndex = %d", nUnusedIndex);
                continue;
            }

            Touch* pTouch = s_pTouches[nUnusedIndex] = new Touch();
			pTouch->setTouchInfo(nUnusedIndex, (x - _viewPortRect.origin.x) / _scaleX, 
                                     (y - _viewPortRect.origin.y) / _scaleY);
            
            //CCLOG("x = %f y = %f", pTouch->getLocationInView().x, pTouch->getLocationInView().y);
            
            Integer* pInterObj = new Integer(nUnusedIndex);
            s_TouchesIntergerDict.setObject(pInterObj, id);
            set.addObject(pTouch);
            pInterObj->release();
        }
    }

    if (set.count() == 0)
    {
        CCLOG("touchesBegan: count = 0");
        return;
    }

    _delegate->touchesBegan(&set, NULL);
}

void EGLViewProtocol::handleTouchesMove(int num, int ids[], float xs[], float ys[])
{
    Set set;
    for (int i = 0; i < num; ++i)
    {
        int id = ids[i];
        float x = xs[i];
        float y = ys[i];

        Integer* pIndex = (Integer*)s_TouchesIntergerDict.objectForKey(id);
        if (pIndex == NULL) {
            CCLOG("if the index doesn't exist, it is an error");
            continue;
        }

        CCLOGINFO("Moving touches with id: %d, x=%f, y=%f", id, x, y);
        Touch* pTouch = s_pTouches[pIndex->getValue()];
        if (pTouch)
        {
			pTouch->setTouchInfo(pIndex->getValue(), (x - _viewPortRect.origin.x) / _scaleX, 
								(y - _viewPortRect.origin.y) / _scaleY);
            
            set.addObject(pTouch);
        }
        else
        {
            // It is error, should return.
            CCLOG("Moving touches with id: %d error", id);
            return;
        }
    }

    if (set.count() == 0)
    {
        CCLOG("touchesMoved: count = 0");
        return;
    }

    _delegate->touchesMoved(&set, NULL);
}

void EGLViewProtocol::getSetOfTouchesEndOrCancel(Set& set, int num, int ids[], float xs[], float ys[])
{
    for (int i = 0; i < num; ++i)
    {
        int id = ids[i];
        float x = xs[i];
        float y = ys[i];

        Integer* pIndex = (Integer*)s_TouchesIntergerDict.objectForKey(id);
        if (pIndex == NULL)
        {
            CCLOG("if the index doesn't exist, it is an error");
            continue;
        }
        /* Add to the set to send to the director */
        Touch* pTouch = s_pTouches[pIndex->getValue()];        
        if (pTouch)
        {
            CCLOGINFO("Ending touches with id: %d, x=%f, y=%f", id, x, y);
			pTouch->setTouchInfo(pIndex->getValue(), (x - _viewPortRect.origin.x) / _scaleX, 
								(y - _viewPortRect.origin.y) / _scaleY);

            set.addObject(pTouch);

            // release the object
            pTouch->release();
            s_pTouches[pIndex->getValue()] = NULL;
            removeUsedIndexBit(pIndex->getValue());

            s_TouchesIntergerDict.removeObjectForKey(id);

        } 
        else
        {
            CCLOG("Ending touches with id: %d error", id);
            return;
        } 

    }

    if (set.count() == 0)
    {
        CCLOG("touchesEnded or touchesCancel: count = 0");
        return;
    }
}

void EGLViewProtocol::handleTouchesEnd(int num, int ids[], float xs[], float ys[])
{
    Set set;
    getSetOfTouchesEndOrCancel(set, num, ids, xs, ys);
    _delegate->touchesEnded(&set, NULL);
}

void EGLViewProtocol::handleTouchesCancel(int num, int ids[], float xs[], float ys[])
{
    Set set;
    getSetOfTouchesEndOrCancel(set, num, ids, xs, ys);
    _delegate->touchesCancelled(&set, NULL);
}

const Rect& EGLViewProtocol::getViewPortRect() const
{
    return _viewPortRect;
}

float EGLViewProtocol::getScaleX() const
{
    return _scaleX;
}

float EGLViewProtocol::getScaleY() const
{
    return _scaleY;
}

NS_CC_END
