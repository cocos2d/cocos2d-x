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

#include "CCAccelerometer_wophone.h"
#include "CCMacros.h"

#include "TCOM_Generic_Method_IIDs.h"

// Can only include once
#include "TCOM_Sensors_IIDs.h"

namespace   cocos2d {

static CCAccelerometer s_Accelerometer;

//------------------------------------------------------------------
//
// CCAccelerometer
//
//------------------------------------------------------------------
CCAccelerometer::CCAccelerometer()
: m_pSensor(NULL)
, m_pDelegate(NULL)
{
}

CCAccelerometer::~CCAccelerometer()
{
    if (m_pSensor)
    {
        m_pSensor->Release();
        m_pSensor = NULL;
    }

	m_pDelegate = NULL;
}

CCAccelerometer* CCAccelerometer::sharedAccelerometer()
{
    return &s_Accelerometer;
}

void CCAccelerometer::setDelegate(CCAccelerometerDelegate* pDelegate)
{
	m_pDelegate = pDelegate;

	if (m_pDelegate)
	{
		do 
		{
			if (m_pSensor)
			{
				break;
			}

			m_pSensor = TCOM_Sensors_DataType_Client::GetInstance();

			if (m_pSensor)
			{
				m_pSensor->StartUp();
				m_pSensor->SetDelay(TG3_SENSOR_DELAY_FASTEST);

				TApplication* pApp = TApplication::GetCurrentApplication();
				TWindow* pWnd = pApp->GetActiveWindow();
				m_pSensor->SetWindowCtrlId(pWnd->GetWindowHwndId(), 0);
				m_pSensor->Activate(TG3_SENSOR_TYPE_ACCELEROMETER, TRUE);
			}
			else
			{
				CCLOG("cocos2d: The Accelerometer Sensor Open failed");
			}
		} while (0);
	}
	else
	{
		if (m_pSensor)
		{
			m_pSensor->Release();
			m_pSensor = NULL;
		}
	}
}

void CCAccelerometer::didAccelerate(CCAcceleration* pAccelerationValue)
{
	if (m_pDelegate)
	{
		m_pDelegate->didAccelerate(pAccelerationValue);
	}	
}

}//namespace   cocos2d 
