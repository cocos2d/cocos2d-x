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

#include "base/CCPlatformConfig.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

#include "2d/platform/CCDevice.h"
#include <string.h>
#include <android/log.h>
#include <jni.h>
#include "2d/ccTypes.h"
#include "jni/DPIJni.h"
#include "jni/Java_org_cocos2dx_lib_Cocos2dxHelper.h"
#include "jni/JniHelper.h"
#include "2d/platform/CCFileUtils.h"

NS_CC_BEGIN

int Device::getDPI()
{
    static int dpi = -1;
    if (dpi == -1)
    {
        dpi = (int)getDPIJNI();
    }
    return dpi;
}

void Device::setAccelerometerEnabled(bool isEnabled)
{
    if (isEnabled)
    {
        enableAccelerometerJni();
    }
    else
    {
        disableAccelerometerJni();
    }
}

void Device::setAccelerometerInterval(float interval)
{
	setAccelerometerIntervalJni(interval);
}

class BitmapDC
{
public:

    BitmapDC()
    : _data(nullptr)
    , _width(0)
    , _height(0)
    {
    }

    ~BitmapDC(void)
    {
    }

    bool getBitmapFromJavaShadowStroke(	const char *text,
    									int nWidth,
    									int nHeight,
    									Device::TextAlign eAlignMask,
    									const char * pFontName,
    									float fontSize,
    									float textTintR 		= 1.0,
    									float textTintG 		= 1.0,
    									float textTintB 		= 1.0,
    									bool shadow 			= false,
    									float shadowDeltaX 		= 0.0,
    									float shadowDeltaY 		= 0.0,
    									float shadowBlur 		= 0.0,
    									float shadowOpacity 	= 0.0,
    									bool stroke 			= false,
    									float strokeColorR 		= 0.0,
    									float strokeColorG 		= 0.0,
    									float strokeColorB 		= 0.0,
    									float strokeSize 		= 0.0 )
    {
           JniMethodInfo methodInfo;
           if (! JniHelper::getStaticMethodInfo(methodInfo, "org/cocos2dx/lib/Cocos2dxBitmap", "createTextBitmapShadowStroke",
               "(Ljava/lang/String;Ljava/lang/String;IFFFIIIZFFFFZFFFF)Z"))
           {
               CCLOG("%s %d: error to get methodInfo", __FILE__, __LINE__);
               return false;
           }

           // Do a full lookup for the font path using FileUtils in case the given font name is a relative path to a font file asset,
           // or the path has been mapped to a different location in the app package:
           std::string fullPathOrFontName = FileUtils::getInstance()->fullPathForFilename(pFontName);
            
           // If the path name returned includes the 'assets' dir then that needs to be removed, because the android.content.Context
           // requires this portion of the path to be omitted for assets inside the app package.
           if (fullPathOrFontName.find("assets/") == 0)
           {
               fullPathOrFontName = fullPathOrFontName.substr(strlen("assets/"));	// Chop out the 'assets/' portion of the path.
           }

           /**create bitmap
            * this method call Cococs2dx.createBitmap()(java code) to create the bitmap, the java code
            * will call Java_org_cocos2dx_lib_Cocos2dxBitmap_nativeInitBitmapDC() to init the width, height
            * and data.
            * use this approach to decrease the jni call number
           */
           jstring jstrText = methodInfo.env->NewStringUTF(text);
           jstring jstrFont = methodInfo.env->NewStringUTF(fullPathOrFontName.c_str());

           if(!shadow)
           {
               shadowDeltaX = 0.0f;
               shadowDeltaY = 0.0f;
               shadowBlur = 0.0f;
               shadowOpacity = 0.0f;
           }
           if (!stroke)
           {
               strokeColorR = 0.0f;
               strokeColorG = 0.0f;
               strokeColorB = 0.0f;
               strokeSize = 0.0f;
           }
           if(!methodInfo.env->CallStaticBooleanMethod(methodInfo.classID, methodInfo.methodID, jstrText,
               jstrFont, (int)fontSize, textTintR, textTintG, textTintB, eAlignMask, nWidth, nHeight, shadow, shadowDeltaX, -shadowDeltaY, shadowBlur, shadowOpacity, stroke, strokeColorR, strokeColorG, strokeColorB, strokeSize))
           {
                return false;
           }

           methodInfo.env->DeleteLocalRef(jstrText);
           methodInfo.env->DeleteLocalRef(jstrFont);
           methodInfo.env->DeleteLocalRef(methodInfo.classID);

           return true;
    }

public:
    int _width;
    int _height;
    unsigned char *_data;
};

static BitmapDC& sharedBitmapDC()
{
    static BitmapDC s_BmpDC;
    return s_BmpDC;
}

Data Device::getTextureDataForText(const char * text,const FontDefinition& textDefinition,TextAlign align,int &width,int &height)
{
    Data ret;
    do 
    {
        BitmapDC &dc = sharedBitmapDC();

        if(! dc.getBitmapFromJavaShadowStroke(text, 
            (int)textDefinition._dimensions.width, 
            (int)textDefinition._dimensions.height, 
            align, textDefinition._fontName.c_str(),
            textDefinition._fontSize,
            textDefinition._fontFillColor.r / 255.0f, 
            textDefinition._fontFillColor.g / 255.0f, 
            textDefinition._fontFillColor.b / 255.0f, 
            textDefinition._shadow._shadowEnabled,
            textDefinition._shadow._shadowOffset.width, 
            textDefinition._shadow._shadowOffset.height, 
            textDefinition._shadow._shadowBlur, 
            textDefinition._shadow._shadowOpacity,
            textDefinition._stroke._strokeEnabled, 
            textDefinition._stroke._strokeColor.r / 255.0f, 
            textDefinition._stroke._strokeColor.g / 255.0f, 
            textDefinition._stroke._strokeColor.b / 255.0f, 
            textDefinition._stroke._strokeSize )) { break;};

        width = dc._width;
        height = dc._height;
        ret.fastSet(dc._data,width * height * 4);
    } while (0);

    return ret;
}

NS_CC_END

#endif // CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

// this method is called by Cocos2dxBitmap
extern "C"
{
    /**
    * this method is called by java code to init width, height and pixels data
    */
    JNIEXPORT void JNICALL Java_org_cocos2dx_lib_Cocos2dxBitmap_nativeInitBitmapDC(JNIEnv*  env, jobject thiz, int width, int height, jbyteArray pixels)
    {
        int size = width * height * 4;
        cocos2d::BitmapDC& bitmapDC = cocos2d::sharedBitmapDC();
        bitmapDC._width = width;
        bitmapDC._height = height;
        bitmapDC._data = (unsigned char*)malloc(sizeof(unsigned char) * size);
        env->GetByteArrayRegion(pixels, 0, size, (jbyte*)bitmapDC._data);
    }
};
