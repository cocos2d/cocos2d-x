/****************************************************************************
 * Samsung API for cocos
 * Developed by Game Engine part
 *
 * Copyright 2015 by Mobile Solution Lab, MSG, SRC-NJ.
 * Wang Ying
 * All rights reserved.
 *
 * This software is the confidential and proprietary information of
 * Samsung Electronics, Inc. ("Confidential Information"). You
 * Shall not disclose such Confidential Information and shall use
 * it only in accordance with the terms of the license agreement
 * you entered into with Samsung
****************************************************************************/

#ifndef __CC_ENHANCEAPI_ANDROID_H__
#define __CC_ENHANCEAPI_ANDROID_H__

#include "platform/CCPlatformConfig.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

#include "platform/CCCommon.h"
#include "platform/CCApplicationProtocol.h"

NS_CC_BEGIN

class CC_DLL EnhanceAPI
{
public:
    /**
     * @js ctor
     */
    EnhanceAPI();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~EnhanceAPI();

    /**
    @brief   call gameservice setResolutionSize API.
    @param   the optimized percent value.
	@return  success: 0, fail: -1.
    */
    static int setResolutionPercent(int n);

	/**
    @brief   call gameservice setFPS API.
	@param   the fps value.
	@return  success: 0, fail: -1.
    */
    static int setFPS(int fps);
	
    /**
    @brief   call gameservice fastLoading API.
	@param   the fast loading seconds.
	@return  success: 0, fail: -1.
    */
    static int fastLoading(int sec);
	
    /**
    @brief   call gameservice getTemperature API.
	@return  -1: fail to get temperature
             0: normal temperature
             1: high
             2,3: very high
    */
    static int getTemperature();
	
	/**
    @brief   call gameservice setLowPowerMode API.
	@return  -1: fail to get temperature
             0: normal temperature
             1: high
             2,3: very high
    */
    static int setLowPowerMode(bool enable);
};

NS_CC_END

#endif // CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

#endif // __CC_ENHANCEAPI_ANDROID_H__