/*
 * Accelerometer.h
 *
 *  Created on: Aug 9, 2011
 *      Author: laschweinski
 */

#ifndef CCACCELEROMETER_H_
#define CCACCELEROMETER_H_

#include "platform/CCPlatformMacros.h"
#include "platform/CCAccelerometerDelegate.h"
#include <functional>

NS_CC_BEGIN

class Accelerometer
{
public:
    Accelerometer(){}
    ~Accelerometer(){}

    static Accelerometer* sharedAccelerometer() { return NULL; };

    void removeDelegate(std::function<void(Acceleration*)> function) {CC_UNUSED_PARAM(function);};
    void addDelegate(std::function<void(Acceleration*)> function) {CC_UNUSED_PARAM(function);};
    void setDelegate(std::function<void(Acceleration*)> function) {CC_UNUSED_PARAM(function);};
    void setAccelerometerInterval(float interval) {CC_UNUSED_PARAM(interval);};
};

NS_CC_END

#endif /* CCACCELEROMETER_H_ */
