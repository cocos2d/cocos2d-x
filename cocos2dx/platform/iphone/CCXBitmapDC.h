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
#ifndef __CCXBITMAP_DC_H__
#define __CCXBITMAP_DC_H__

#include "ccTypes.h"
#include "CCXCocos2dDefine.h"
#include "CCXUIImage.h"

namespace cocos2d{
	class CCX_DLL CCXBitmapDC
	{
	public:
		CCXBitmapDC();
		CCXBitmapDC(const char *text, 
					CGSize dimensions = CGSizeZero,
					UITextAlignment alignment = UITextAlignmentCenter,
					const char *fontName = NULL,
					float fontSize = 0);
		~CCXBitmapDC(void);
		
		int getWidth();
        int getHeight();
        unsigned char* getData();
	private:
		unsigned int inline swapAlpha(unsigned int);
		void getBitmapFromJava(const char *text, float fontSize);
		
	private:
		int m_nWidth;
		int m_nHeight;
		unsigned char *m_pData;
	};
}

#endif //__CCXBITMAP_DC_H__