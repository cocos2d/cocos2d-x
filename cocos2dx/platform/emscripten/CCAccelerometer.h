/*
 * Accelerometer.h
 *
 *  Created on: Aug 9, 2011
 *      Author: laschweinski
 */

#ifndef CCACCELEROMETER_H_
#define CCACCELEROMETER_H_

#include "platform/CCAccelerometerDelegate.h"
#include <functional>

namespace   cocos2d {

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

}//namespace   cocos2d

#endif /* CCACCELEROMETER_H_ */
