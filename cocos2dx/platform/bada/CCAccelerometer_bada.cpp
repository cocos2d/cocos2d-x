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

CCAccelerometer::CCAccelerometer() : m_pAccelDelegate(NULL)
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
}

void CCAccelerometer::OnDataReceived(SensorType sensorType, SensorData& sensorData, result r)
{
	long timeStamp = 0;
	float x = 0.0, y = 0.0, z = 0.0;

	sensorData.GetValue((SensorDataKey)ACCELERATION_DATA_KEY_TIMESTAMP, timeStamp);
	sensorData.GetValue((SensorDataKey)ACCELERATION_DATA_KEY_X, x);
	sensorData.GetValue((SensorDataKey)ACCELERATION_DATA_KEY_Y, y);
	sensorData.GetValue((SensorDataKey)ACCELERATION_DATA_KEY_Z, z);

	CCAcceleration AccValue;
	AccValue.x = -x;
	AccValue.y = -y;
	AccValue.z = -z;
	AccValue.timestamp = timeStamp;

	m_pAccelDelegate->didAccelerate(&AccValue);
	AppLog("####################TimeStamp:[%d], Accel.x,y,z:[%f,%f,%f]", timeStamp, x, y, z);
}

NS_CC_END;
