/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

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

#include "CCXUIAccelerometer_bada.h"
#include "CCXCocos2dDefine.h"
#include "ccMacros.h"
using namespace Osp::Uix;

//#include "TCOM_Generic_Method_IIDs.h"

//ֻ�ܰ�һ��
//#include "TCOM_Sensors_IIDs.h"

namespace   cocos2d {

static UIAccelerometer s_Accelerometer;

//------------------------------------------------------------------
//
// UIAccelerometerHandler
//
//------------------------------------------------------------------
UIAccelerometerDelegate* UIAccelerometerHandler::getDelegate()
{
    return m_pDelegate;
}

UIAccelerometerHandler::~UIAccelerometerHandler()
{
    m_pDelegate->AccelerometerDestroy();
}

void UIAccelerometerHandler::setDelegate(UIAccelerometerDelegate *pDelegate)
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

bool UIAccelerometerHandler::initWithDelegate(UIAccelerometerDelegate *pDelegate)
{
    assert(pDelegate != NULL);

    m_pDelegate = pDelegate;
    pDelegate->AccelerometerKeep();

    return true;
}

UIAccelerometerHandler* UIAccelerometerHandler::handlerWithDelegate(UIAccelerometerDelegate *pDelegate)
{
    UIAccelerometerHandler* pHandler = new UIAccelerometerHandler;

    if (pHandler)
    {
        if (pHandler->initWithDelegate(pDelegate))
        {
            pHandler->autorelease();
        }
        else
        {
            CCX_SAFE_RELEASE_NULL(pHandler);
        }
    }

    return pHandler;
}


//------------------------------------------------------------------
//
// UIAccelerometer
//
//------------------------------------------------------------------
UIAccelerometer::UIAccelerometer()
: m_pSensor(NULL)
{
    m_pDelegates = new AccDelegateArray;
}

UIAccelerometer::~UIAccelerometer()
{
    m_pDelegates->release();

    if (m_pSensor)
    {
        delete m_pSensor;
        m_pSensor = NULL;
    }
}

UIAccelerometer* UIAccelerometer::sharedAccelerometer()
{
    return &s_Accelerometer;
}

void UIAccelerometer::removeDelegate(UIAccelerometerDelegate* pDelegate)
{
    UIAccelerometerHandler *pHandler;
    NSMutableArray<UIAccelerometerHandler*>::NSMutableArrayIterator  iter;

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
        delete m_pSensor;
        m_pSensor = NULL;
    }
}

void UIAccelerometer::addDelegate(UIAccelerometerDelegate* pDelegate)
{
    UIAccelerometerHandler* pHandler = UIAccelerometerHandler::handlerWithDelegate(pDelegate);

    if (pHandler)
    {
        m_pDelegates->addObject(pHandler);

        if (!m_pSensor)
        {
        	long	interval = 10;
        	bool	available = false;
        	result	r = E_INVALID_STATE;
        	m_pSensor = new SensorManager();
        	m_pSensor->Construct();

        	available = m_pSensor->IsAvailable(SENSOR_TYPE_ACCELERATION);

        	if (true == available)
        	{
        		long	intervalTemp = 0;
        		m_pSensor->GetMaxInterval(SENSOR_TYPE_ACCELERATION, intervalTemp);
        		if (interval > intervalTemp)
        			interval = intervalTemp;
        		m_pSensor->GetMinInterval(SENSOR_TYPE_ACCELERATION, intervalTemp);
        		if (interval < intervalTemp)
        			interval = intervalTemp;

        	    r = m_pSensor->AddSensorListener(*this, SENSOR_TYPE_ACCELERATION, interval, false);
        	}

//            m_pSensor = TCOM_Sensors_DataType_Client::GetInstance();
//
//            if (m_pSensor)
//            {
//                m_pSensor->StartUp();
//                m_pSensor->SetDelay(TG3_SENSOR_DELAY_FASTEST);
//
//                TApplication* pApp = TApplication::GetCurrentApplication();
//                TWindow* pWnd = pApp->GetActiveWindow();
//                m_pSensor->SetWindowCtrlId(pWnd->GetWindowHwndId(), 0);
//                m_pSensor->Activate(TG3_SENSOR_TYPE_ACCELEROMETER, TRUE);
//            }
//            else
//            {
//                CCLOG("cocos2d: The Accelerometer Sensor Open failed");
//            }
        }
    }
}

void UIAccelerometer::didAccelerate(UIAcceleration* pAccelerationValue)
{
    UIAccelerometerHandler  *pHandler;
    UIAccelerometerDelegate *pDelegate;
    NSMutableArray<UIAccelerometerHandler*>::NSMutableArrayIterator  iter;

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

void UIAccelerometer::OnDataReceived(SensorType sensorType, SensorData& sensorData, result r)
{
	long timeStamp = 0;
	float x = 0.0, y = 0.0, z = 0.0;

	sensorData.GetValue((SensorDataKey)ACCELERATION_DATA_KEY_TIMESTAMP, timeStamp);
	sensorData.GetValue((SensorDataKey)ACCELERATION_DATA_KEY_X, x);
	sensorData.GetValue((SensorDataKey)ACCELERATION_DATA_KEY_Y, y);
	sensorData.GetValue((SensorDataKey)ACCELERATION_DATA_KEY_Z, z);

	UIAcceleration AccValue;
	AccValue.x = -x;
	AccValue.y = -y;
	AccValue.z = -z;
	AccValue.timestamp = timeStamp;
//	AppLog("x = %d, y = %d, z = %d, timestamp = %d", AccValue.x, AccValue.y, AccValue.z, AccValue.timestamp);
	// call delegates' didAccelerate function
	UIAccelerometer::sharedAccelerometer()->didAccelerate(&AccValue);
//	bHandled = TRUE;

	AppLog("####################TimeStamp:[%d], Accel.x,y,z:[%f,%f,%f]",
		timeStamp,
		x, y, z);

	/*
	TG3SensorsDataType	data;

	if (Sys_GetMessageBody((MESSAGE_t *)pEvent, &data, sizeof(TG3SensorsDataType)) == sizeof(TG3SensorsDataType) &&
		TG3_SENSOR_TYPE_ACCELEROMETER == data.sensorMask)
	{
		// convert the data to iphone format
		UIAcceleration AccValue;
		AccValue.x = -(data.acceleration.x / TG3_GRAVITY_EARTH);
		AccValue.y = -(data.acceleration.y / TG3_GRAVITY_EARTH);
		AccValue.z = -(data.acceleration.z / TG3_GRAVITY_EARTH);
		AccValue.timestamp = (double) TimGetTicks() / 100;

		// call delegates' didAccelerate function
		UIAccelerometer::sharedAccelerometer()->didAccelerate(&AccValue);
		bHandled = TRUE;
	}
	 */

}

}//namespace   cocos2d 
