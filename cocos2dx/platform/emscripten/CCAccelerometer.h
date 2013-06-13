/*
 * CCAccelerometer.h
 *
 *  Created on: Aug 9, 2011
 *      Author: laschweinski
 */

#ifndef CCACCELEROMETER_H_
#define CCACCELEROMETER_H_

#include "platform/CCAccelerometerDelegate.h"

namespace   cocos2d {

class CCAccelerometer
{
public:
    CCAccelerometer(){}
    ~CCAccelerometer(){}

    static CCAccelerometer* sharedAccelerometer() { return NULL; };

    void removeDelegate(CCAccelerometerDelegate* pDelegate) {CC_UNUSED_PARAM(pDelegate);};
    void addDelegate(CCAccelerometerDelegate* pDelegate) {CC_UNUSED_PARAM(pDelegate);};
    void setDelegate(CCAccelerometerDelegate* pDelegate) {CC_UNUSED_PARAM(pDelegate);};
    void setAccelerometerInterval(float interval) {CC_UNUSED_PARAM(interval);};
};

}//namespace   cocos2d

#endif /* CCACCELEROMETER_H_ */
