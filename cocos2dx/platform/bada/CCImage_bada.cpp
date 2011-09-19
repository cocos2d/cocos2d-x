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

using namespace Osp::Graphics;

NS_CC_BEGIN;

bool CCImage::initWithString(
                               const char *    pText,
                               int             nWidth/* = 0*/,
                               int             nHeight/* = 0*/,
                               ETextAlign      eAlignMask/* = kAlignCenter*/,
                               const char *    pFontName/* = nil*/,
                               int             nSize/* = 0*/)
{
    bool bRet = false;
    result r = E_FAILURE;
	do
	{
		Canvas * pCanvas = new Canvas();
		CC_BREAK_IF(! pCanvas);

		r = pCanvas->Construct(Rectangle(0, 0, nWidth, nHeight));
		CC_BREAK_IF(IsFailed(r));

		BufferInfo bufferInfo;
		r = pCanvas->Lock(bufferInfo);
		CC_BREAK_IF(IsFailed(r));

		int nLen = bufferInfo.pitch * nHeight;
		m_pData = new unsigned char [nLen];
		CC_BREAK_IF(!m_pData);
		memcpy(m_pData, bufferInfo.pPixels, nLen);

		m_nHeight		= nHeight;
		m_nWidth		= nWidth;
		m_bHasAlpha	= true;
		m_bPreMulti = true;
		m_nBitsPerComponent = bufferInfo.bitsPerPixel / 4;
		pCanvas->Unlock();

		CC_SAFE_DELETE(pCanvas);
		bRet = true;
	} while (0);

    return bRet;
}

NS_CC_END;
