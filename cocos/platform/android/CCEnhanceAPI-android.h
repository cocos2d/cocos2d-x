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
#pragma once

#include "platform/CCCommon.h"
#include "platform/CCApplicationProtocol.h"

NS_CC_BEGIN

/**
 * The purpose of Enhance API is to optimize Cocos2D-X game engine special for Samsung products.
 * Note: The minimum required Android version is 5.0.
 *
 */
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
     * @brief  The function is used to set screen buffer size ratio.
     * The purpose of the API is to modify off screen buffer size for the game app.
     * It will reduce the off screen buffer according to the given ration.
     * The ration value varies from 50 to 100. 100 means using 100% size of the on screen buffer
     * as off screen buffer and 50 means 50% size of the on screen buffer will be used as off screen buffer.
     *
     * @param  percent The optimized percent value, value varies from 50 to 100.
     * @return  success: 0, fail: -1.
     */
    static int setResolutionPercent(int percent);

    /**
   *@brief  The function is used to set FPS level.
   *@Warn The input fps level(0-99) corresponds to game fps value(0-60).
   * FPS level 99 means game FPS value 60.
   * The purpose of the API is reducing power consumption when we set dynamic fps in some situations.
   *@param  fps the fps value.
   *@return  success: 0, fail: -1.
   */
    static int setFPS(int fps);

    /**
     *@brief   The function is used to set Boost Up seconds.
     * The input parameter means the loading seconds. The maximum settings seconds is 7.
     * The purpose of the API is reducing the application's loading time.
     *@param   sec The fast loading seconds.
     *@return  success: 0, fail: -1.
     */
    static int fastLoading(int sec);

    /**
     *@brief   The function is used to get temperature level(0-3).
     * The purpose of the API is get temperature status of the device.
     * Temperature 0 means normal temperature and 1-3 means different temperature level.
     * 1 is the minimum high temperature level and 3 is the maximum high temperature level.
     *@return  -1: fail to get temperature.
     * - 0: normal temperature
     * - 1: high
     * - 2,3: very high
     */
    static int getTemperature();

    /**
     *@brief The function is used to set power saving mode for true or false.
     * The purpose of the API is reducing Power consumption when set power saving mode for true.
     *
     *@return  -1: fail to get temperature
     * - 0: normal temperature
     * - 1: high
     * - 2,3: very high
     */
    static int setLowPowerMode(bool enable);
};

NS_CC_END
