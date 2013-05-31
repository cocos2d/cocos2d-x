/****************************************************************************
Copyright (c) 2013 cocos2d-x.org

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

#include "CCInputDelegate.h"

NS_CC_EXT_BEGIN

CCInputDelegate::CCInputDelegate(void)
: m_bTouchEnabled(false)
, m_bAccelerometerEnabled(false)
, m_bKeypadEnabled(false)
, m_nTouchPriority(0)
, m_eTouchMode(kCCTouchesAllAtOnce)
{

}

CCInputDelegate::~CCInputDelegate(void)
{
}

bool CCInputDelegate::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    CC_UNUSED_PARAM(pTouch);
    CC_UNUSED_PARAM(pEvent);
    return true;
}

void CCInputDelegate::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    CC_UNUSED_PARAM(pTouch);
    CC_UNUSED_PARAM(pEvent);
}
    
void CCInputDelegate::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    CC_UNUSED_PARAM(pTouch);
    CC_UNUSED_PARAM(pEvent);
}

void CCInputDelegate::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
    CC_UNUSED_PARAM(pTouch);
    CC_UNUSED_PARAM(pEvent);
}    

void CCInputDelegate::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
    CC_UNUSED_PARAM(pTouches);
    CC_UNUSED_PARAM(pEvent);
}

void CCInputDelegate::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
    CC_UNUSED_PARAM(pTouches);
    CC_UNUSED_PARAM(pEvent);
}

void CCInputDelegate::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
    CC_UNUSED_PARAM(pTouches);
    CC_UNUSED_PARAM(pEvent);
}

void CCInputDelegate::ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent)
{
    CC_UNUSED_PARAM(pTouches);
    CC_UNUSED_PARAM(pEvent);
}

void CCInputDelegate::didAccelerate(CCAcceleration* pAccelerationValue)
{
   CC_UNUSED_PARAM(pAccelerationValue);
}

bool CCInputDelegate::isTouchEnabled()
{
    return m_bTouchEnabled;
}

void CCInputDelegate::setTouchEnabled(bool enabled)
{
    if (m_bTouchEnabled != enabled)
    {
        m_bTouchEnabled = enabled;
        if (enabled)
        {
            if( m_eTouchMode == kCCTouchesAllAtOnce )
            {
                CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this, 0);
            }
            else
            {
                CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, m_nTouchPriority, true);
            }
        }
        else
        {
            CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
        }
    }
}

void CCInputDelegate::setTouchMode(ccTouchesMode mode)
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

void CCInputDelegate::setTouchPriority(int priority)
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

int CCInputDelegate::getTouchPriority()
{
    return m_nTouchPriority;
}

int CCInputDelegate::getTouchMode()
{
    return m_eTouchMode;
}

bool CCInputDelegate::isAccelerometerEnabled()
{
    return m_bAccelerometerEnabled;
}

void CCInputDelegate::setAccelerometerEnabled(bool enabled)
{
    if (enabled != m_bAccelerometerEnabled)
    {
        m_bAccelerometerEnabled = enabled;

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

bool CCInputDelegate::isKeypadEnabled()
{
    return m_bKeypadEnabled;
}

void CCInputDelegate::setKeypadEnabled(bool enabled)
{
    if (enabled != m_bKeypadEnabled)
    {
        m_bKeypadEnabled = enabled;

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


NS_CC_EXT_END
