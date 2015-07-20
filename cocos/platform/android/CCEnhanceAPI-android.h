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

/**@~english
 * The purpose of Enhance API is to optimize Cocos2D-X game engine special for Samsung products.
 * Note: The minimum required Android version is 5.0.
 *
 * @~chinese 
 * EnhanceAPI的目的是专门为三星设备上面的Cocos2D-X游戏进行优化。
 * 注意:Android版本最低要求是5.0。
 * 
 */
class CC_DLL EnhanceAPI
{
public:
    /**
     * @~english Default constructor
     * @~chinese 默认构造函数
     * @js ctor
     */
    EnhanceAPI();
    /**
     * @~english Default destructor
     * @~chinese 默认析构函数
     * @js NA
     * @lua NA
     */
    virtual ~EnhanceAPI();

    /**
     * @brief  @~english The function is used to set screen buffer size ratio.
     * The purpose of the API is to modify off screen buffer size for the game app.
     * It will reduce the off screen buffer according to the given ration.
     * The ration value varies from 50 to 100. 100 means using 100% size of the on screen buffer
     * as off screen buffer and 50 means 50% size of the on screen buffer will be used as off screen buffer.
     *
     * @~chinese 该函数用于设置屏幕缓冲区大小比例。
     * 此API的目的是修改了游戏应用的屏幕外的缓冲区大小。
     * 它将根据给定的比例减少屏幕外缓冲区大小。
     * 比例值从50到100不等。100意味着使用100%屏幕缓冲区的大小
     * 当屏幕缓冲区为50意味着50%大小的屏幕上的缓冲区将被用作屏幕外缓冲区。
     * 
     * @param  percent @~english The optimized percent value, value varies from 50 to 100.
     * @~chinese 优化的百分比值,值从50到100不等。
     * @return  @~english success: 0, fail: -1.
     * @~chinese 成功:0,失败: -1。
     */
    static int setResolutionPercent(int percent);

	/**
   *@brief  @~english The function is used to set FPS level.
  * @~chinese 该函数用于设置FPS的级别。
   *@Warn @~english The input fps level(0-99) corresponds to game fps value(0-60).
   * FPS level 99 means game FPS value 60.
   * The purpose of the API is reducing power consumption when we set dynamic fps in some situations.
   * @~chinese 输入帧级别(0 - 99)对应于游戏的fps值(0-60) 。
   * FPS 99级意味着游戏的帧速为60 FPS。
   * 这个API的目的是通过动态调整FPS级别来减少电量消耗。
   *@param  fps @~english the fps value.
   * @~chinese fps的值。
   *@return  @~english success: 0, fail: -1.
   * @~chinese 成功:0,失败: -1。
   */
    static int setFPS(int fps);

    /**
     *@brief   @~english The function is used to set Boost Up seconds.
     * The input parameter means the loading seconds. The maximum settings seconds is 7.
     * The purpose of the API is reducing the application's loading time.
     * @~chinese 该函数用于设置启动时间。
     * 输入参数意味着程序加载时间。7秒为最大值。
     * 此API的目的是减少应用程序的加载时间。
     *@param   sec @~english The fast loading seconds.
     * @~chinese 启动时间，单位是秒
     *@return  @~english success: 0, fail: -1.
     * @~chinese 成功:0,失败: -1。
     */
    static int fastLoading(int sec);

    /**
     *@brief   @~english The function is used to get temperature level(0-3).
     * The purpose of the API is get temperature status of the device.
     * Temperature 0 means normal temperature and 1-3 means different temperature level.
     * 1 is the minimum high temperature level and 3 is the maximum high temperature level.
     * @~chinese 此函数是用于获取设备的温度水平(0 - 3)。
     * API的目的是获得设备的温度状态。
     * 温度0意味着正常温度和1 - 3处于不同的温度水平。
     * 1 is the minimum high temperature level and 3 is the maximum high temperature level.
     *@return  @~english
     * - -1: fail to get temperature.
     * - 0: normal temperature
     * - 1: high
     * - 2,3: very high
     * @~chinese
     * - -1: 无法获取温度。
     * - 0:正常温度
     * - 1:温度过高
     * - 2,3: 温度非常高
     */
    static int getTemperature();

    /**
     *@brief @~english The function is used to set power saving mode for true or false.
     * The purpose of the API is reducing Power consumption when set power saving mode for true.
     *
     * @~chinese 该函数用于设置是否开启省电模式。
     * 此API可以通过设置节能模式来降低设备的功耗。
     * 
     *@return  @~english -1: fail to get temperature
     * - 0: normal temperature
     * - 1: high
     * - 2,3: very high
     * @~chinese
     * - -1:没有得到温度
     * - 0:正常温度
     * - 1:温度过高
     * - 2,3:温度非常高
     */
    static int setLowPowerMode(bool enable);
};

NS_CC_END

#endif // CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

#endif // __CC_ENHANCEAPI_ANDROID_H__
