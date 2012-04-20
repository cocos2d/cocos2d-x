/*
 * CCAccelerometer_linux.h
 *
 *  Created on: Aug 9, 2011
 *      Author: laschweinski
 */

#ifndef CCACCELEROMETER_LINUX_H_
#define CCACCELEROMETER_LINUX_H_

#include "CCCommon.h"

NS_CC_BEGIN

class CCAccelerometer
{
public:
    CCAccelerometer();
    ~CCAccelerometer();

    void removeDelegate(CCAccelerometerDelegate* pDelegate) {CC_UNUSED_PARAM(pDelegate);};
    void addDelegate(CCAccelerometerDelegate* pDelegate) {CC_UNUSED_PARAM(pDelegate);};
    void setDelegate(CCAccelerometerDelegate* pDelegate) {CC_UNUSED_PARAM(pDelegate);}
};

NS_CC_END

#endif /* CCACCELEROMETER_LINUX_H_ */
