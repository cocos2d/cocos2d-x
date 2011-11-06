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

#include "CCAccelerometer_bada.h"
#include "ccMacros.h"

using namespace Osp::Uix;

NS_CC_BEGIN;

CCAccelerometer* CCAccelerometer::m_spCCAccelerometer = NULL;

CCAccelerometer::CCAccelerometer() :
  m_pAccelDelegate(NULL)
, m_pSensor(NULL)
{

}

CCAccelerometer::~CCAccelerometer() 
{
	m_spCCAccelerometer = NULL;
}

CCAccelerometer* CCAccelerometer::sharedAccelerometer() 
{
  if (m_spCCAccelerometer == NULL)
  {
  	m_spCCAccelerometer = new CCAccelerometer();
  }
  return m_spCCAccelerometer;
}

void CCAccelerometer::setDelegate(CCAccelerometerDelegate* pDelegate)
{
	m_pAccelDelegate = pDelegate;
	if (pDelegate != NULL)
	{
		setEnable(true);
	}
	else
	{
		setEnable(false);
	}
}

void CCAccelerometer::OnDataReceived(SensorType sensorType, SensorData& sensorData, result r)
{
	long timeStamp = 0;
	float x = 0.0, y = 0.0, z = 0.0;

	sensorData.GetValue((SensorDataKey)ACCELERATION_DATA_KEY_TIMESTAMP, timeStamp);
	sensorData.GetValue((SensorDataKey)ACCELERATION_DATA_KEY_X, x);
	sensorData.GetValue((SensorDataKey)ACCELERATION_DATA_KEY_Y, y);
	sensorData.GetValue((SensorDataKey)ACCELERATION_DATA_KEY_Z, z);

	// only consider land postion, to be continued.
	CCAcceleration AccValue;
	AccValue.x = -x;
	AccValue.y = -y;
	AccValue.z = -z;
	AccValue.timestamp = timeStamp;

	if (m_pAccelDelegate != NULL)
	{
		m_pAccelDelegate->didAccelerate(&AccValue);
	}
	//AppLog("##TimeStamp:[%d], Accel.x,y,z:[%f,%f,%f]", timeStamp, x, y, z);
}

void CCAccelerometer::setEnable(bool bEnable)
{
	if (m_pSensor != NULL)
	{
		m_pSensor->RemoveSensorListener(*this);
	}
	CC_SAFE_DELETE(m_pSensor);
	if (bEnable)
	{
		long	interval = 10;
		bool	available = false;
		result	r = E_INVALID_STATE;
		m_pSensor = new SensorManager();
		m_pSensor->Construct();

		available = m_pSensor->IsAvailable(SENSOR_TYPE_ACCELERATION);

		if (available)
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
	}
}

NS_CC_END;
