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
#ifndef __CCBITMAP_DC_H__
#define __CCBITMAP_DC_H__

#include <Windows.h>
#include "ccTypes.h"
#include "CCCocos2dDefine.h"
#include "CCImage.h"

namespace cocos2d{
	class CC_DLL CCBitmapDC
	{
	public:
		CCBitmapDC(int width, int height);
		CCBitmapDC(const char *text, 
					CCSize dimensions = CCSizeZero,
					CCTextAlignment alignment = CCTextAlignmentCenter,
					const char *fontName = NULL,
					float fontSize = 0);
		~CCBitmapDC(void);

		HBITMAP getBitmap(void);
		HDC		getDC(void);

	protected:
        HDC     m_hMemDC;
        HBITMAP m_hBmp;
        HGDIOBJ m_hOld;
	};
}

#endif //__CCBITMAP_DC_H__