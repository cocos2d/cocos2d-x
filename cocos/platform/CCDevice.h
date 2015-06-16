/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2015 Chukong Technologies Inc.

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

#ifndef __CCDEVICE_H__
#define __CCDEVICE_H__

#include "platform/CCPlatformMacros.h"
#include "base/ccMacros.h"
#include "base/CCData.h"

NS_CC_BEGIN

struct FontDefinition;

/**
 * @addtogroup platform
 * @{
 */

/**
 * @class Device
 * @brief  @~english A class for providing platform specific features.
 * @~chinese 一个用来处理不同平台的独有特性的类。
 */
class CC_DLL Device
{
public:
    /** @~english Defines the alignment of text.  @~chinese 定义文本的对齐方式。*/
    enum class TextAlign
    {
        CENTER        = 0x33, /** @~english Horizontal center and vertical center. @~chinese 水平居中和垂直居中 */
        TOP           = 0x13, /** @~english Horizontal center and vertical top. @~chinese 水平居中和垂直居上*/
        TOP_RIGHT     = 0x12, /** @~english Horizontal right and vertical top. @~chinese 水平居右和垂直居上*/
        RIGHT         = 0x32, /** @~english Horizontal right and vertical center. @~chinese 水平居右和垂直居中*/
        BOTTOM_RIGHT  = 0x22, /** @~english Horizontal right and vertical bottom. @~chinese 水平居右和垂直居下*/
        BOTTOM        = 0x23, /** @~english Horizontal center and vertical bottom. @~chinese 水平居中和垂直居下*/
        BOTTOM_LEFT   = 0x21, /** @~english Horizontal left and vertical bottom. @~chinese 水平居左和垂直居下*/
        LEFT          = 0x31, /** @~english Horizontal left and vertical center. @~chinese 水平居左和垂直居中*/
        TOP_LEFT      = 0x11, /** @~english Horizontal left and vertical top. @~chinese 水平居左和垂直居上*/
    };

    /**@~english
     *  Gets the DPI of device
     * @~chinese 
     * 设备的每个英寸的点数(DPI)
     *  @return @~english The DPI of device.
     * @~chinese 设备的DPI。
     */
    static int getDPI();
    
    /**@~english
     * To enable or disable accelerometer.
     * @~chinese 
     * 启用或禁用加速度计。
     */
    static void setAccelerometerEnabled(bool isEnabled);

    /**@~english
     *  Sets the interval of accelerometer.
     * @~chinese 
     * 设置加速度计的间隔。
     */
    static void setAccelerometerInterval(float interval);

    /**@~english
     * Controls whether the screen should remain on.
     * 
     * @~chinese 
     * 控制屏幕是否应该保持唤醒状态。
     * 
     * @param keepScreenOn @~english One flag indicating that the screen should remain on.
     * @~chinese 一个标志,指示屏幕上是否保持唤醒状态。
     */
    static void setKeepScreenOn(bool keepScreenOn);

    /**@~english
     * Gets texture data for text.
     * @~chinese 
     * 文本的纹理数据。
     */
    static Data getTextureDataForText(const char * text, const FontDefinition& textDefinition, TextAlign align, int &width, int &height, bool& hasPremultipliedAlpha);

private:
    CC_DISALLOW_IMPLICIT_CONSTRUCTORS(Device);
};

// end group
/// @}

NS_CC_END

#endif /* __CCDEVICE_H__ */
