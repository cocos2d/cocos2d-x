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
#include "CCBitmapDC.h"
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
#include "SkTypeface.h"

namespace cocos2d {

	CCBitmapDC::CCBitmapDC()
	{
		m_nWidth = 0;
		m_nHeight = 0;
		m_pData = NULL;
	}
	
	CCBitmapDC::CCBitmapDC(const char *text, CCSize dimensions, CCTextAlignment alignment, const char *fontName, float fontSize)
	{
		m_nWidth = 0;
		m_nHeight = 0;
		m_pData = NULL;
		
		drawText(text, fontName, fontSize);
	}
	
	CCBitmapDC::~CCBitmapDC()
	{
		if (m_pData)
		{
			delete[] m_pData;
		}
	}
	
	int CCBitmapDC::getWidth()
    {
    	return m_nWidth;
    }
    
    int CCBitmapDC::getHeight()
    {
    	return m_nHeight;
    }
    
    unsigned char* CCBitmapDC::getData()
    {
    	return m_pData;
    }
	
	void CCBitmapDC::drawText(const char *text, const char *fontName, float fontSize)
	{
		// init paint
		SkPaint *paint = new SkPaint();
		paint->setColor(SK_ColorWHITE);
		paint->setTextSize(fontSize);

        // create font
        SkTypeface *pTypeFace = SkTypeface::CreateFromName(fontName, SkTypeface::kNormal);
        paint->setTypeface( pTypeFace ); 

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
	}
}
