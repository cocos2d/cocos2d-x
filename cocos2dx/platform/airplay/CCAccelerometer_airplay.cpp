/****************************************************************************
 Copyright (c) 2011      cocos2d-x.org   http://cocos2d-x.org
 Copyright (c) 2011      Максим Аксенов
 
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

#include "CCAccelerometer_airplay.h"
#include "ccMacros.h"

namespace cocos2d
{
static CCAccelerometer s_Accelerometer;

//------------------------------------------------------------------
//
// CCAccelerometerHandler
//
//------------------------------------------------------------------
CCAccelerometerDelegate* CCAccelerometerHandler::getDelegate()
{
    return m_pDelegate;
}
CCAccelerometerHandler::~CCAccelerometerHandler()
{
    m_pDelegate->AccelerometerDestroy();
}
void CCAccelerometerHandler::setDelegate(CCAccelerometerDelegate *pDelegate)
{
    if (pDelegate)
    {
        pDelegate->AccelerometerKeep();
    }

    if (m_pDelegate)
    {
        m_pDelegate->AccelerometerDestroy();
    }
    m_pDelegate = pDelegate;
}
bool CCAccelerometerHandler::initWithDelegate(CCAccelerometerDelegate *pDelegate)
{
    assert(pDelegate != NULL);

    m_pDelegate = pDelegate;
    pDelegate->AccelerometerKeep();

    return true;
}
CCAccelerometerHandler* CCAccelerometerHandler::handlerWithDelegate(CCAccelerometerDelegate *pDelegate)
{
    CCAccelerometerHandler* pHandler = new CCAccelerometerHandler;

    if (pHandler)
    {
        if (pHandler->initWithDelegate(pDelegate))
        {
            pHandler->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(pHandler);
        }
    }

    return pHandler;
}
//------------------------------------------------------------------
//
// CCAccelerometer
//
//------------------------------------------------------------------
CCAccelerometer::CCAccelerometer()

{
	s3eAccelerometerStart();

    m_pDelegates = new AccDelegateArray;

}
CCAccelerometer::~CCAccelerometer()
{
    m_pDelegates->release();
    s3eAccelerometerStop();
}

CCAccelerometer* CCAccelerometer::sharedAccelerometer()
{
    return &s_Accelerometer;
}
void CCAccelerometer::removeDelegate(CCAccelerometerDelegate* pDelegate)
{
    CCAccelerometerHandler *pHandler;
    CCMutableArray<CCAccelerometerHandler*>::CCMutableArrayIterator  iter;

    if (pDelegate)
    {
        for (iter = m_pDelegates->begin(); iter != m_pDelegates->end(); ++iter)
        {
            pHandler = *iter;
            if (pHandler && pHandler->getDelegate() == pDelegate)
            {
                m_pDelegates->removeObject(pHandler);
                break;
            }
        }
    }

    if (0 == m_pDelegates->count())
    {
//        m_pSensor->Release();
//        m_pSensor = NULL;
    }
}
void CCAccelerometer::addDelegate(CCAccelerometerDelegate* pDelegate)
{
    CCAccelerometerHandler* pHandler = CCAccelerometerHandler::handlerWithDelegate(pDelegate);

    if (pHandler)
    {
		m_pDelegates->addObject(pHandler);
	}
	else
	{
		CCLOG("cocos2d: The Accelerometer Sensor Open failed");
    }
}

void CCAccelerometer::didAccelerate(CCAcceleration* pAccelerationValue)
{
    CCAccelerometerHandler  *pHandler;
    CCAccelerometerDelegate *pDelegate;
    CCMutableArray<CCAccelerometerHandler*>::CCMutableArrayIterator  iter;

    if (m_pDelegates->count() > 0)
    {
        for (iter = m_pDelegates->begin(); iter != m_pDelegates->end(); ++iter)
        {
            pHandler = *iter;
            pDelegate = pHandler->getDelegate();
            pDelegate->didAccelerate(pAccelerationValue);
        }
    }
}

} // end of namespace cococs2d

