/****************************************************************************
Copyright (c) 2013 cocos2d-x.org
Copyright (c) 2013 Lee, Jae-Hong

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

#include "CCStdC.h"
#include "CCAccelerometer.h"

using namespace Tizen::Uix::Sensor;

NS_CC_BEGIN

Accelerometer::Accelerometer()
    : _function(nullptr)
    , __sensorMgr(nullptr)
{
}

Accelerometer::~Accelerometer()
{

}

void Accelerometer::setDelegate(std::function<void(Acceleration*)> function)
{
    _function = function;

    if (_function)
    {
        startSensor();
    }
    else
    {
        stopSensor();
    }
}

void Accelerometer::setAccelerometerInterval(float interval)
{
    if (__sensorMgr)
    {
        __sensorMgr->SetInterval(SENSOR_TYPE_ACCELERATION, interval * 1000);
    }
}

void Accelerometer::startSensor()
{
    long interval = 0L;

    if (__sensorMgr)
    {
        __sensorMgr->RemoveSensorListener(*this);
        delete __sensorMgr;
        __sensorMgr = null;
    }

    __sensorMgr = new SensorManager();
    __sensorMgr->Construct();
    __sensorMgr->GetMinInterval(SENSOR_TYPE_ACCELERATION, interval);

    if (interval < 50)
    {
        interval = 50;
    }
    __sensorMgr->AddSensorListener(*this, SENSOR_TYPE_ACCELERATION, interval, true);

}

void Accelerometer::stopSensor()
{
    if (__sensorMgr)
    {
        __sensorMgr->RemoveSensorListener(*this);
        delete __sensorMgr;
        __sensorMgr = null;
    }
}

void Accelerometer::OnDataReceived(SensorType sensorType, SensorData& sensorData , result r)
{
    if (_function)
    {
        AccelerationSensorData& data = static_cast<AccelerationSensorData&>(sensorData);
        AppLog("AccelerationSensorData    x = %5.4f , y = %5.4f,  z = %5.4f ", data.x,data.y,data.z);

        _accelerationValue.x = data.y;
        _accelerationValue.y = -data.x;
        _accelerationValue.z = -data.z;
        _accelerationValue.timestamp = data.timestamp;

        _function(&_accelerationValue);
    }
}

NS_CC_END

