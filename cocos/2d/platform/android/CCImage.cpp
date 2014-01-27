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

//#define COCOS2D_DEBUG 1

#define __CC_PLATFORM_IMAGE_CPP__
#include "platform/CCImageCommon_cpp.h"
#include "CCPlatformMacros.h"
#include "platform/CCImage.h"
#include "platform/CCFileUtils.h"
#include "jni/JniHelper.h"

#include <android/log.h>
#include <string.h>
#include <jni.h>

NS_CC_BEGIN

class BitmapDC
{
public:

    BitmapDC()
    : _data(NULL)
    , _width(0)
    , _height(0)
    {
    }

    ~BitmapDC(void)
    {
        if (_data)
        {
            delete [] _data;
        }
    }

    bool getBitmapFromJavaShadowStroke(	const char *text,
    									int nWidth,
    									int nHeight,
    									Image::TextAlign eAlignMask,
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


    bool getBitmapFromJava(const char *text, int nWidth, int nHeight, Image::TextAlign eAlignMask, const char * pFontName, float fontSize)
    {
    	return  getBitmapFromJavaShadowStroke(	text, nWidth, nHeight, eAlignMask, pFontName, fontSize );
    }

public:
    int _width;
    int _height;
    unsigned char *_data;
    JNIEnv *env;
};

static BitmapDC& sharedBitmapDC()
{
    static BitmapDC s_BmpDC;
    return s_BmpDC;
}

bool Image::initWithString(
                               const char *    pText, 
                               int             nWidth/* = 0*/, 
                               int             nHeight/* = 0*/,
                               TextAlign      eAlignMask/* = kAlignCenter*/,
                               const char *    pFontName/* = nil*/,
                               int             nSize/* = 0*/)
{
    bool bRet = false;

    do 
    {
        CC_BREAK_IF(! pText);
        
        BitmapDC &dc = sharedBitmapDC();

        CC_BREAK_IF(! dc.getBitmapFromJava(pText, nWidth, nHeight, eAlignMask, pFontName, nSize));

        // assign the dc._data to _data in order to save time
        _data = dc._data;
        CC_BREAK_IF(! _data);

        _width    = (short)dc._width;
        _height   = (short)dc._height;
        _preMulti = true;
        _renderFormat = Texture2D::PixelFormat::RGBA8888;
        _dataLen = _width * _height * 4;

        bRet = true;
    } while (0);

    return bRet;
}

bool Image::initWithStringShadowStroke(
                                         const char * pText,
                                         int         nWidth ,
                                         int         nHeight ,
                                         TextAlign eAlignMask ,
                                         const char * pFontName ,
                                         int          nSize ,
                                         float        textTintR,
                                         float        textTintG,
                                         float        textTintB,
                                         bool shadow,
                                         float shadowOffsetX,
                                         float shadowOffsetY,
                                         float shadowOpacity,
                                         float shadowBlur,
                                         bool  stroke,
                                         float strokeR,
                                         float strokeG,
                                         float strokeB,
                                         float strokeSize)
{
	 bool bRet = false;
	    do
	    {
	        CC_BREAK_IF(! pText);

	        BitmapDC &dc = sharedBitmapDC();


	        CC_BREAK_IF(! dc.getBitmapFromJavaShadowStroke(pText, nWidth, nHeight, eAlignMask, pFontName,
	        											   nSize, textTintR, textTintG, textTintB, shadow,
	        											   shadowOffsetX, shadowOffsetY, shadowBlur, shadowOpacity,
	        											   stroke, strokeR, strokeG, strokeB, strokeSize ));


	        // assign the dc._data to _data in order to save time
	        _data = dc._data;

	        CC_BREAK_IF(! _data);

	        _width    = (short)dc._width;
	        _height   = (short)dc._height;
	        _preMulti = true;
		    _renderFormat = Texture2D::PixelFormat::RGBA8888;
            _dataLen = _width * _height * 4;

	        // ok
	        bRet = true;

	    } while (0);

	    return bRet;
}

NS_CC_END

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
        bitmapDC._data = new unsigned char[size];
        env->GetByteArrayRegion(pixels, 0, size, (jbyte*)bitmapDC._data);
    }
};
