/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2014 Chukong Technologies Inc.

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

#include "CCGLViewProtocol.h"
#include "CCTouch.h"
#include "CCDirector.h"
#include "CCSet.h"
#include "CCEventDispatcher.h"


NS_CC_BEGIN

namespace {
    
    static Touch* g_touches[EventTouch::MAX_TOUCHES] = { nullptr };
    static unsigned int g_indexBitsUsed = 0;
    // System touch pointer ID (It may not be ascending order number) <-> Ascending order number from 0
    static std::map<int, int> g_touchIdReorderMap;
    
    static int getUnUsedIndex()
    {
        int i;
        int temp = g_indexBitsUsed;
        
        for (i = 0; i < EventTouch::MAX_TOUCHES; i++) {
            if (! (temp & 0x00000001)) {
                g_indexBitsUsed |= (1 <<  i);
                return i;
            }
            
            temp >>= 1;
        }
        
        // all bits are used
        return -1;
    }
    
    static void removeUsedIndexBit(int index)
    {
        if (index < 0 || index >= EventTouch::MAX_TOUCHES)
        {
            return;
        }
        
        unsigned int temp = 1 << index;
        temp = ~temp;
        g_indexBitsUsed &= temp;
    }
    
}

GLViewProtocol::GLViewProtocol()
: _scaleX(1.0f)
, _scaleY(1.0f)
, _resolutionPolicy(ResolutionPolicy::UNKNOWN)
{
}

GLViewProtocol::~GLViewProtocol()
{

}

void GLViewProtocol::pollInputEvents()
{
}

void GLViewProtocol::setDesignResolutionSize(float width, float height, ResolutionPolicy resolutionPolicy)
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
    
    else if (resolutionPolicy == ResolutionPolicy::SHOW_ALL)
    {
        _scaleX = _scaleY = MIN(_scaleX, _scaleY);
    }

    else if ( resolutionPolicy == ResolutionPolicy::FIXED_HEIGHT) {
    	_scaleX = _scaleY;
    	_designResolutionSize.width = ceilf(_screenSize.width/_scaleX);
    }

    else if ( resolutionPolicy == ResolutionPolicy::FIXED_WIDTH) {
    	_scaleY = _scaleX;
    	_designResolutionSize.height = ceilf(_screenSize.height/_scaleY);
    }

    // calculate the rect of viewport    
    float viewPortW = _designResolutionSize.width * _scaleX;
    float viewPortH = _designResolutionSize.height * _scaleY;

    _viewPortRect.setRect((_screenSize.width - viewPortW) / 2, (_screenSize.height - viewPortH) / 2, viewPortW, viewPortH);
    
    _resolutionPolicy = resolutionPolicy;
    
	// reset director's member variables to fit visible rect
    auto director = Director::getInstance();
    director->_winSizeInPoints = getDesignResolutionSize();
    director->createStatsLabel();
    director->setGLDefaultValues();
}

const Size& GLViewProtocol::getDesignResolutionSize() const 
{
    return _designResolutionSize;
}

const Size& GLViewProtocol::getFrameSize() const
{
    return _screenSize;
}

void GLViewProtocol::setFrameSize(float width, float height)
{
    _designResolutionSize = _screenSize = Size(width, height);
}

Size  GLViewProtocol::getVisibleSize() const
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

Point GLViewProtocol::getVisibleOrigin() const
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

void GLViewProtocol::setViewPortInPoints(float x , float y , float w , float h)
{
    glViewport((GLint)(x * _scaleX + _viewPortRect.origin.x),
               (GLint)(y * _scaleY + _viewPortRect.origin.y),
               (GLsizei)(w * _scaleX),
               (GLsizei)(h * _scaleY));
}

void GLViewProtocol::setScissorInPoints(float x , float y , float w , float h)
{
    glScissor((GLint)(x * _scaleX + _viewPortRect.origin.x),
              (GLint)(y * _scaleY + _viewPortRect.origin.y),
              (GLsizei)(w * _scaleX),
              (GLsizei)(h * _scaleY));
}

bool GLViewProtocol::isScissorEnabled()
{
	return (GL_FALSE == glIsEnabled(GL_SCISSOR_TEST)) ? false : true;
}

Rect GLViewProtocol::getScissorRect() const
{
	GLfloat params[4];
	glGetFloatv(GL_SCISSOR_BOX, params);
	float x = (params[0] - _viewPortRect.origin.x) / _scaleX;
	float y = (params[1] - _viewPortRect.origin.y) / _scaleY;
	float w = params[2] / _scaleX;
	float h = params[3] / _scaleY;
	return Rect(x, y, w, h);
}

void GLViewProtocol::setViewName(const std::string& viewname )
{
    _viewName = viewname;
}

const std::string& GLViewProtocol::getViewName() const
{
    return _viewName;
}

void GLViewProtocol::handleTouchesBegin(int num, int ids[], float xs[], float ys[])
{
    int id = 0;
    float x = 0.0f;
    float y = 0.0f;
    int unusedIndex = 0;
    EventTouch touchEvent;
    
    for (int i = 0; i < num; ++i)
    {
        id = ids[i];
        x = xs[i];
        y = ys[i];

        auto iter = g_touchIdReorderMap.find(id);
        unusedIndex = 0;

        // it is a new touch
        if (iter == g_touchIdReorderMap.end())
        {
            unusedIndex = getUnUsedIndex();

            // The touches is more than MAX_TOUCHES ?
            if (unusedIndex == -1) {
                CCLOG("The touches is more than MAX_TOUCHES, unusedIndex = %d", unusedIndex);
                continue;
            }

            Touch* touch = g_touches[unusedIndex] = new Touch();
			touch->setTouchInfo(unusedIndex, (x - _viewPortRect.origin.x) / _scaleX,
                                     (y - _viewPortRect.origin.y) / _scaleY);
            
            CCLOGINFO("x = %f y = %f", pTouch->getLocationInView().x, pTouch->getLocationInView().y);
            
            g_touchIdReorderMap.insert(std::make_pair(id, unusedIndex));
            touchEvent._touches.push_back(touch);
        }
    }

    if (touchEvent._touches.size() == 0)
    {
        CCLOG("touchesBegan: size = 0");
        return;
    }
    
    touchEvent._eventCode = EventTouch::EventCode::BEGAN;
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->dispatchEvent(&touchEvent);
}

void GLViewProtocol::handleTouchesMove(int num, int ids[], float xs[], float ys[])
{
    int id = 0;
    float x = 0.0f;
    float y = 0.0f;
    EventTouch touchEvent;
    
    for (int i = 0; i < num; ++i)
    {
        id = ids[i];
        x = xs[i];
        y = ys[i];

        auto iter = g_touchIdReorderMap.find(id);
        if (iter == g_touchIdReorderMap.end())
        {
            CCLOG("if the index doesn't exist, it is an error");
            continue;
        }

        CCLOGINFO("Moving touches with id: %d, x=%f, y=%f", id, x, y);
        Touch* touch = g_touches[iter->second];
        if (touch)
        {
			touch->setTouchInfo(iter->second, (x - _viewPortRect.origin.x) / _scaleX,
								(y - _viewPortRect.origin.y) / _scaleY);
            
            touchEvent._touches.push_back(touch);
        }
        else
        {
            // It is error, should return.
            CCLOG("Moving touches with id: %d error", id);
            return;
        }
    }

    if (touchEvent._touches.size() == 0)
    {
        CCLOG("touchesMoved: size = 0");
        return;
    }
    
    touchEvent._eventCode = EventTouch::EventCode::MOVED;
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->dispatchEvent(&touchEvent);
}

void GLViewProtocol::handleTouchesOfEndOrCancel(EventTouch::EventCode eventCode, int num, int ids[], float xs[], float ys[])
{
    int id = 0;
    float x = 0.0f;
    float y = 0.0f;
    EventTouch touchEvent;
    
    for (int i = 0; i < num; ++i)
    {
        id = ids[i];
        x = xs[i];
        y = ys[i];

        auto iter = g_touchIdReorderMap.find(id);
        if (iter == g_touchIdReorderMap.end())
        {
            CCLOG("if the index doesn't exist, it is an error");
            continue;
        }
        
        /* Add to the set to send to the director */
        Touch* touch = g_touches[iter->second];
        if (touch)
        {
            CCLOGINFO("Ending touches with id: %d, x=%f, y=%f", id, x, y);
			touch->setTouchInfo(iter->second, (x - _viewPortRect.origin.x) / _scaleX,
								(y - _viewPortRect.origin.y) / _scaleY);

            touchEvent._touches.push_back(touch);
            
            g_touches[iter->second] = nullptr;
            removeUsedIndexBit(iter->second);

            g_touchIdReorderMap.erase(id);
        } 
        else
        {
            CCLOG("Ending touches with id: %d error", id);
            return;
        } 

    }

    if (touchEvent._touches.size() == 0)
    {
        CCLOG("touchesEnded or touchesCancel: size = 0");
        return;
    }
    
    touchEvent._eventCode = eventCode;
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->dispatchEvent(&touchEvent);
    
    for (auto& touch : touchEvent._touches)
    {
        // release the touch object.
        touch->release();
    }
}

void GLViewProtocol::handleTouchesEnd(int num, int ids[], float xs[], float ys[])
{
    handleTouchesOfEndOrCancel(EventTouch::EventCode::ENDED, num, ids, xs, ys);
}

void GLViewProtocol::handleTouchesCancel(int num, int ids[], float xs[], float ys[])
{
    handleTouchesOfEndOrCancel(EventTouch::EventCode::CANCELLED, num, ids, xs, ys);
}

const Rect& GLViewProtocol::getViewPortRect() const
{
    return _viewPortRect;
}

float GLViewProtocol::getScaleX() const
{
    return _scaleX;
}

float GLViewProtocol::getScaleY() const
{
    return _scaleY;
}

NS_CC_END
