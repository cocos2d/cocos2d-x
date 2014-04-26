/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
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

#ifndef __CCDEVICE_H__
#define __CCDEVICE_H__

#include "base/CCPlatformMacros.h"
#include "2d/ccMacros.h"
#include "base/CCData.h"

NS_CC_BEGIN

struct FontDefinition;

class CC_DLL Device
{
public:
    enum class TextAlign
    {
        CENTER        = 0x33, ///< Horizontal center and vertical center.
        TOP           = 0x13, ///< Horizontal center and vertical top.
        TOP_RIGHT     = 0x12, ///< Horizontal right and vertical top.
        RIGHT         = 0x32, ///< Horizontal right and vertical center.
        BOTTOM_RIGHT = 0x22, ///< Horizontal right and vertical bottom.
        BOTTOM        = 0x23, ///< Horizontal center and vertical bottom.
        BOTTOM_LEFT  = 0x21, ///< Horizontal left and vertical bottom.
        LEFT          = 0x31, ///< Horizontal left and vertical center.
        TOP_LEFT      = 0x11, ///< Horizontal left and vertical top.
    };
    /**
     *  Gets the DPI of device
     *  @return The DPI of device.
     */
    static int getDPI();
    
    /**
     * To enable or disable accelerometer.
     */
    static void setAccelerometerEnabled(bool isEnabled);
    /**
     *  Sets the interval of accelerometer.
     */
    static void setAccelerometerInterval(float interval);

    static Data getTextureDataForText(const char * text,const FontDefinition& textDefinition,TextAlign align,int &widht,int &height);

private:
    CC_DISALLOW_IMPLICIT_CONSTRUCTORS(Device);
};


NS_CC_END

#endif /* __CCDEVICE_H__ */
