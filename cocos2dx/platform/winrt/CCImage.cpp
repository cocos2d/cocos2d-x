/****************************************************************************
Copyright (c) 2010 cocos2d-x.org
Copyright (c) Microsoft Open Technologies, Inc.

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
#define __CC_PLATFORM_IMAGE_CPP__
#include "platform/CCImageCommon_cpp.h"
#include "CCWinRTUtils.h"
#include "CCFreeTypeFont.h"
#include <memory>

#define generic GenericFromFreeTypeLibrary
#define internal InternalFromFreeTypeLibrary

#include <ft2build.h>
#include <freetype/freetype.h>
#include <freetype/ftglyph.h>
#include <freetype/ftoutln.h>
#include <freetype/fttrigon.h>
#include <map>
#include <set>
using namespace std;

#undef generic
#undef internal

using namespace Windows::UI::Core;

NS_CC_BEGIN

bool CCImage::initWithString(
    const char *    pText, 
    int             nWidth, 
    int             nHeight,
    ETextAlign      eAlignMask,
    const char *    pFontName,
    int             nSize)
{
    bool ok = true;
    int rwidth=0;
    int rheight=0;

    if(!pText || strlen(pText) == 0)
        return false;

    if(!m_ft)
    {
        m_ft = new CCFreeTypeFont();
    }

    ok = m_ft->initWithString(pText, pFontName, nSize, nWidth, nHeight);
    if(ok)
    {
        m_pData = m_ft->getBitmap(eAlignMask, &rwidth, &rheight);
        m_nWidth    = rwidth;
        m_nHeight   = rheight;
        m_bHasAlpha = true;
        m_bPreMulti = false;
        m_nBitsPerComponent = 8;
        return (m_pData) ? true:false;    
    }
    return false;
}

NS_CC_END