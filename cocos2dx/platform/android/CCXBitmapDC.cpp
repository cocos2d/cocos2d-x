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
#include "Cocos2dJni.h"
#include "CCDirector.h"
#include "platform/platform.h"

#include <android/log.h>
#include <string.h>
#include <math.h>

// undefine ANDROID to include skia headers
#ifdef ANDROID
#undef ANDROID
#endif

#include "SkBitmap.h"
#include "SkPaint.h"
#include "SkScalar.h"
#include "SkCanvas.h"

namespace cocos2d {

	CCXBitmapDC::CCXBitmapDC()
	{
		m_nWidth = 0;
		m_nHeight = 0;
		m_pData = NULL;
	}
	
	CCXBitmapDC::CCXBitmapDC(const char *text, CGSize dimensions, UITextAlignment alignment, const char *fontName, float fontSize)
	{
		m_nWidth = 0;
		m_nHeight = 0;
		m_pData = NULL;
		
		drawText(text, fontSize);
	}
	
	CCXBitmapDC::~CCXBitmapDC()
	{
		if (m_pData)
		{
			delete[] m_pData;
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
    	return m_pData;
    }
	
	void CCXBitmapDC::drawText(const char *text, float fontSize)
	{
		// init paint
		SkPaint *paint = new SkPaint();
		paint->setColor(SK_ColorWHITE);
		paint->setTextSize(fontSize);

        // get text width and height
        SkPaint::FontMetrics font;
		paint->getFontMetrics(&font);
		int h = (int)ceil((font.fDescent - font.fAscent));
		int w = (int)ceil((paint->measureText(text, strlen(text))));

        // create and init bitmap
        SkBitmap *bitmap = new SkBitmap();
		bitmap->setConfig(SkBitmap::kARGB_8888_Config, w, h);
        if (! bitmap->allocPixels())
		{
			CCLOG("alloc pixels error");
			return;
		}
		
		// start with black/transparent pixels
		bitmap->eraseColor(0);

        // create canvas and draw text
		SkCanvas canvas(*bitmap);
	    canvas.drawText(text, strlen(text), 0.0, -font.fAscent, *paint);
		
		// get data
        m_pData = new unsigned char[w * h * 4];        
        memcpy(m_pData, bitmap->getPixels(), w * h * 4);
        
        // destrcut objects          
        // delete canvas;
        delete bitmap;
        delete paint; 
		
		m_nWidth = w;
		m_nHeight = h;
		

// 		JNIEnv *env;
// 		if (gJavaVM->GetEnv((void**)&env, JNI_VERSION_1_4) <0 )
// 		{
// 			if (gJavaVM->AttachCurrentThread(&env, NULL) < 0)
// 			{
// 				return;
// 			}
// 		}
// 		
// 		//__android_log_write(ANDROID_LOG_DEBUG, "cocos2d::CCXBitmapDC", "get env");
// 		
// 		jclass mClass = env->FindClass("org/cocos2dx/lib/Cocos2dxJNI");
// 		if (! mClass)
// 		{
// 			__android_log_write(ANDROID_LOG_DEBUG, "cocos2d::CCXBitmapDC", "can not find org.cocos2dx.Cocos2dJNI");
// 			return;
// 		}
// 		
// 		jmethodID mid = env->GetStaticMethodID(mClass, "createTextBitmap", "(Ljava/lang/String;I)Landroid/graphics/Bitmap;");
	}
}
