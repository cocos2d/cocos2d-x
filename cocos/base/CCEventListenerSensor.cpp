/****************************************************************************
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

#include "base/CCEventListenerSensor.h"
#include "base/CCEventSensor.h"
#include "base/CCConsole.h"

NS_CC_BEGIN

const std::string EventListenerSensor::LISTENER_ID =
  "__cc_magnetic_field";

EventListenerSensor::EventListenerSensor()
{

}

EventListenerSensor::~EventListenerSensor()
{
    CCLOGINFO("In the destructor of SensorEventListener. %p", this);
}

EventListenerSensor* EventListenerSensor::create(
  const std::function<void(Sensor*, Event*)>& callback)
{
    EventListenerSensor* ret =
      new (std::nothrow) EventListenerSensor();
    if (ret && ret->init(callback))
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }

    return ret;
}

bool EventListenerSensor::init(
  const std::function<void(Sensor*, Event* event)>& callback)
{
    auto listener = [this](Event* event){
        auto sensorEvent = static_cast<EventSensor*>(event);
        this->onSensorEvent(&sensorEvent->_sensor, event);
    };

    if (EventListener::init(Type::SENSOR, LISTENER_ID, listener))
    {
        onSensorEvent = callback;
        return true;
    }

    return false;
}

EventListenerSensor* EventListenerSensor::clone()
{
    auto ret = new (std::nothrow) EventListenerSensor();

    if (ret && ret->init(onSensorEvent))
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }

    return ret;
}

bool EventListenerSensor::checkAvailable()
{
    CCASSERT(onSensorEvent, "onSensorEvent can't be nullptr!");

    return true;
}

NS_CC_END
