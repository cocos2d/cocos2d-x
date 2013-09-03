#include "CCEGLViewProtocol.h"
#include "event_dispatcher/CCTouch.h"
#include "CCDirector.h"
#include "cocoa/CCSet.h"
#include "event_dispatcher/CCEventDispatcher.h"
#include "event_dispatcher/CCTouchEvent.h"

NS_CC_BEGIN

namespace {
    
    static Touch* _touches[CC_MAX_TOUCHES] = { NULL };
    static unsigned int _indexBitsUsed = 0;
    // System touch pointer ID (It may not be ascending order number) <-> Ascending order number from 0
    static std::map<int, int> _touchIdReorderMap;
    
    static int getUnUsedIndex()
    {
        int i;
        int temp = _indexBitsUsed;
        
        for (i = 0; i < CC_MAX_TOUCHES; i++) {
            if (! (temp & 0x00000001)) {
                _indexBitsUsed |= (1 <<  i);
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
        _indexBitsUsed &= temp;
    }
    
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

void EGLViewProtocol::pollInputEvents()
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

        auto iter = _touchIdReorderMap.find(id);
        int nUnusedIndex = 0;

        // it is a new touch
        if (iter == _touchIdReorderMap.end())
        {
            nUnusedIndex = getUnUsedIndex();

            // The touches is more than MAX_TOUCHES ?
            if (nUnusedIndex == -1) {
                CCLOG("The touches is more than MAX_TOUCHES, nUnusedIndex = %d", nUnusedIndex);
                continue;
            }

            Touch* pTouch = _touches[nUnusedIndex] = new Touch();
			pTouch->setTouchInfo(nUnusedIndex, (x - _viewPortRect.origin.x) / _scaleX, 
                                     (y - _viewPortRect.origin.y) / _scaleY);
            
            //CCLOG("x = %f y = %f", pTouch->getLocationInView().x, pTouch->getLocationInView().y);
            
            _touchIdReorderMap.insert(std::make_pair(id, nUnusedIndex));
            set.addObject(pTouch);
        }
    }

    if (set.count() == 0)
    {
        CCLOG("touchesBegan: count = 0");
        return;
    }

    
    TouchEvent touchEvent;

    for (auto iter = set.begin(); iter != set.end(); ++iter)
    {
        touchEvent._touches.push_back(static_cast<Touch*>(*iter));
    }
    
    touchEvent._eventCode = TouchEvent::EventCode::BEGAN;
    EventDispatcher::getInstance()->dispatchEvent(&touchEvent);
}

void EGLViewProtocol::handleTouchesMove(int num, int ids[], float xs[], float ys[])
{
    Set set;
    for (int i = 0; i < num; ++i)
    {
        int id = ids[i];
        float x = xs[i];
        float y = ys[i];

        auto iter = _touchIdReorderMap.find(id);
        if (iter == _touchIdReorderMap.end())
        {
            CCLOG("if the index doesn't exist, it is an error");
            continue;
        }

        CCLOGINFO("Moving touches with id: %d, x=%f, y=%f", id, x, y);
        Touch* pTouch = _touches[iter->second];
        if (pTouch)
        {
			pTouch->setTouchInfo(iter->second, (x - _viewPortRect.origin.x) / _scaleX, 
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
    
    TouchEvent touchEvent;
    
    for (auto iter = set.begin(); iter != set.end(); ++iter)
    {
        touchEvent._touches.push_back(static_cast<Touch*>(*iter));
    }
    
    touchEvent._eventCode = TouchEvent::EventCode::MOVED;
    
    EventDispatcher::getInstance()->dispatchEvent(&touchEvent);
}

void EGLViewProtocol::getSetOfTouchesEndOrCancel(Set& set, int num, int ids[], float xs[], float ys[])
{
    for (int i = 0; i < num; ++i)
    {
        int id = ids[i];
        float x = xs[i];
        float y = ys[i];

        auto iter = _touchIdReorderMap.find(id);
        if (iter == _touchIdReorderMap.end())
        {
            CCLOG("if the index doesn't exist, it is an error");
            continue;
        }
        /* Add to the set to send to the director */
        Touch* pTouch = _touches[iter->second];
        if (pTouch)
        {
            CCLOGINFO("Ending touches with id: %d, x=%f, y=%f", id, x, y);
			pTouch->setTouchInfo(iter->second, (x - _viewPortRect.origin.x) / _scaleX, 
								(y - _viewPortRect.origin.y) / _scaleY);

            set.addObject(pTouch);

            // release the object
            pTouch->release();
            _touches[iter->second] = NULL;
            removeUsedIndexBit(iter->second);

            _touchIdReorderMap.erase(id);
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
    
    TouchEvent touchEvent;
    
    for (auto iter = set.begin(); iter != set.end(); ++iter)
    {
        touchEvent._touches.push_back(static_cast<Touch*>(*iter));
    }
    
    touchEvent._eventCode = TouchEvent::EventCode::ENDED;
    EventDispatcher::getInstance()->dispatchEvent(&touchEvent);
}

void EGLViewProtocol::handleTouchesCancel(int num, int ids[], float xs[], float ys[])
{
    Set set;
    getSetOfTouchesEndOrCancel(set, num, ids, xs, ys);
    
    TouchEvent touchEvent;
    
    for (auto iter = set.begin(); iter != set.end(); ++iter)
    {
        touchEvent._touches.push_back(static_cast<Touch*>(*iter));
    }
    
    touchEvent._eventCode = TouchEvent::EventCode::CANCELLED;
    EventDispatcher::getInstance()->dispatchEvent(&touchEvent);
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
