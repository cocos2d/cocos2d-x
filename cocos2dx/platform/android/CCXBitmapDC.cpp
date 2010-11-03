/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

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
#include <cstring>
#include "CCXBitmapDC.h"
#include "CCXApplication_android.h"
#include "CCDirector.h"
#include "platform/platform.h"

#include <android/log.h>
#include <android/bitmap.h>
#include <string.h>
#include <jni.h>

namespace cocos2d {

	CCXBitmapDC::CCXBitmapDC()
	{
		m_nWidth = 0;
		m_nHeight = 0;
		data = NULL;
	}
	
	CCXBitmapDC::CCXBitmapDC(const char *text, CGSize dimensions, UITextAlignment alignment, const char *fontName, float fontSize)
	{
		m_nWidth = 0;
		m_nHeight = 0;
		data = NULL;
		
		getBitmapFromJava(text, fontSize);
	}
	
	CCXBitmapDC::~CCXBitmapDC()
	{
		if (data)
		{
			delete[] data;
		}
	}
	
	int CCXBitmapDC::getWidth()
    {
    	return m_nWidth;
    }
    
    int CCXBitmapDC::getHeight()
    {
    	return m_nHeight;
    }
    
    unsigned char* CCXBitmapDC::getData()
    {
    	return data;
    }
	
	void CCXBitmapDC::getBitmapFromJava(const char *text, float fontSize)
	{
		JNIEnv *env;
		if (gJavaVM->GetEnv((void**)&env, JNI_VERSION_1_4) <0 )
		{
			if (gJavaVM->AttachCurrentThread(&env, NULL) < 0)
			{
				return;
			}
		}
		
		//__android_log_write(ANDROID_LOG_DEBUG, "cocos2d::CCXBitmapDC", "get env");
		
		jclass mClass = env->FindClass("org/cocos2dx/Cocos2dJNI");
		if (! mClass)
		{
			__android_log_write(ANDROID_LOG_DEBUG, "cocos2d::CCXBitmapDC", "can not find org.cocos2dx.Cocos2dJNI");
			return;
		}
		
		jmethodID mid = env->GetStaticMethodID(mClass, "createTextBitmap", "(Ljava/lang/String;I)Landroid/graphics/Bitmap;");
	    if (! mid)
	    {
	    	__android_log_write(ANDROID_LOG_DEBUG, "cocos2d::CCXBitmapDC", "can not find method createTextBitmap");
	    	return;
	    }
	    
	    jobject bitmap = env->CallStaticObjectMethod(mClass, mid, env->NewStringUTF(text), (int)fontSize);
	    
	    AndroidBitmapInfo  info;
	    if (AndroidBitmap_getInfo(env, bitmap, &info) < 0) 
	    {
            __android_log_write(ANDROID_LOG_DEBUG, "cocos2d::CCXBitmapDC", "failed to get bitmapinfo");
            return;
        }
                
        void *pixels;
        if (AndroidBitmap_lockPixels(env, bitmap, &pixels) < 0) 
        {
            __android_log_write(ANDROID_LOG_DEBUG, "cocos2d::CCXBitmapDC", "AndroidBitmap_lockPixels() failed !");
        }
        
        // get data
        data = new unsigned char[info.width * info.height * 4];
        if (! data)
        {
        	AndroidBitmap_unlockPixels(evn, bitmap);
        	__android_log_write(ANDROID_LOG_DEBUG, "cocos2d::CCXBitmapDC", "failed to allocate memory");
        	return;
        }
        
        memcpy(data, pixels, info.width * info.height * 4);
        
        m_nWidth = info.width;
        m_nHeight =info.height;
	}
	
	unsigned int CCXBitmapDC::swapAlpha(unsigned int value)
	{
		return ((value << 8 & 0xffffff00) | (value >> 24 & 0x000000ff));
	}
}
