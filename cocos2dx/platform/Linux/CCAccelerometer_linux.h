/*
 * CCAccelerometer_linux.h
 *
 *  Created on: Aug 9, 2011
 *      Author: laschweinski
 */

#ifndef CCACCELEROMETER_LINUX_H_
#define CCACCELEROMETER_LINUX_H_

#include "CCCommon.h"

namespace   cocos2d {

class CCAccelerometer
{
public:
    CCAccelerometer();
    ~CCAccelerometer();

    static CCAccelerometer* sharedAccelerometer() { return NULL; };

    void removeDelegate(CCAccelerometerDelegate* pDelegate) {CC_UNUSED_PARAM(pDelegate);};
    void addDelegate(CCAccelerometerDelegate* pDelegate) {CC_UNUSED_PARAM(pDelegate);};
    void setDelegate(CCAccelerometerDelegate* pDelegate) {CC_UNUSED_PARAM(pDelegate);}
};

}//namespace   cocos2d

#endif /* CCACCELEROMETER_LINUX_H_ */
