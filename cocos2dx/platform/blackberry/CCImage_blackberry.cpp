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

#include "CCImage.h"

#include "SkTypeface.h"
#include "SkBitmap.h"
#include "SkPaint.h"
#include "SkCanvas.h"

using namespace std;

NS_CC_BEGIN;

class BitmapDC
{
public:
    BitmapDC() : m_pBitmap(NULL),
	  	  	  	 m_pPaint(NULL)
    {
    }

    ~BitmapDC(void)
    {
		CC_SAFE_DELETE(m_pPaint);
		CC_SAFE_DELETE(m_pBitmap);
    }

	bool setFont(const char *pFontName = NULL, int nSize = 0)
	{
		bool bRet = false;

		if (m_pPaint)
		{
			delete m_pPaint;
			m_pPaint = NULL;
		}

		do 
		{
			/* init paint */
			m_pPaint = new SkPaint();
			CC_BREAK_IF(! m_pPaint);
			m_pPaint->setColor(SK_ColorWHITE);
			m_pPaint->setTextSize(nSize);

			/* create font */
			SkTypeface *pTypeFace = SkTypeface::CreateFromName(pFontName, SkTypeface::kNormal);
			if (! pTypeFace)
			{
				// let's replace with Arial first before failing
				pTypeFace = SkTypeface::CreateFromName("Arial", SkTypeface::kNormal);
				CCLOG("could not find font %s replacing with Arial\n", pFontName);

				if (!pTypeFace)
				{
					CC_SAFE_DELETE(m_pPaint);
					break;
				}
			}
			m_pPaint->setTypeface( pTypeFace );
			/* cannot unref, I don't know why. It may be memory leak, but how to avoid? */
			pTypeFace->unref();

			bRet = true;
		} while (0);

		return bRet;
	}

	bool prepareBitmap(int nWidth, int nHeight)
	{
		// release bitmap
		if (m_pBitmap)
		{
			delete m_pBitmap;
			m_pBitmap = NULL;
		}
		
		if (nWidth > 0 && nHeight > 0)
		{
			/* create and init bitmap */
			m_pBitmap = new SkBitmap();
			if (! m_pBitmap)
			{
				return false;
			}

			/* use rgba8888 and alloc memory */
            m_pBitmap->setConfig(SkBitmap::kARGB_8888_Config, nWidth, nHeight);
			if (! m_pBitmap->allocPixels())
			{
				CC_SAFE_DELETE(m_pBitmap);
				return false;
			}

			/* start with black/transparent pixels */
			m_pBitmap->eraseColor(0);
		}

		return true;
	}

	bool drawText(const char *pszText, int nWidth, int nHeight, CCImage::ETextAlign eAlignMask)
    {
        bool bRet = false;

        do 
        {
            CC_BREAK_IF(! pszText);
            CC_BREAK_IF(! prepareBitmap(nWidth, nHeight));

			/* create canvas */
			SkPaint::FontMetrics font;
			m_pPaint->getFontMetrics(&font);
			SkCanvas canvas(*m_pBitmap);

			/*
			 * draw text
			 * @todo: alignment
			 */
			canvas.drawText(pszText, strlen(pszText), 0.0, -font.fAscent, *m_pPaint);
			bRet = true;
        } while (0);

        return bRet;
    }

	bool getTextExtentPoint(const char * pszText, int *pWidth, int *pHeight)
	{
		bool bRet = false;

		do 
		{
			CC_BREAK_IF(!pszText || !pWidth || !pHeight);

			// get text width and height
			if (m_pPaint)
			{
				SkPaint::FontMetrics font;
				m_pPaint->getFontMetrics(&font);
				*pHeight = (int)ceil((font.fDescent - font.fAscent));
				*pWidth = (int)ceil((m_pPaint->measureText(pszText, strlen(pszText))));

				bRet = true;
			}			
		} while (0);

		return bRet;
	}

	SkBitmap* getBitmap()
	{
		return m_pBitmap;
	}

private:
    SkPaint  *m_pPaint;
	SkBitmap *m_pBitmap;

};

static BitmapDC& sharedBitmapDC()
{
    static BitmapDC s_BmpDC;
    return s_BmpDC;
}

bool CCImage::initWithString(
                               const char *    pText, 
                               int             nWidth/* = 0*/, 
                               int             nHeight/* = 0*/,
                               ETextAlign      eAlignMask/* = kAlignCenter*/,
                               const char *    pFontName/* = nil*/,
                               int             nSize/* = 0*/)
{
    bool bRet = false;

    do 
    {
        CC_BREAK_IF(! pText);
		
        BitmapDC &dc = sharedBitmapDC();

		/* init font with font name and size */
		CC_BREAK_IF(! dc.setFont(pFontName, nSize));

		/* compute text width and height */
		if (nWidth <= 0 || nHeight <= 0)
		{
			dc.getTextExtentPoint(pText, &nWidth, &nHeight);
		}
		CC_BREAK_IF(nWidth <= 0 || nHeight <= 0);

		CC_BREAK_IF( false == dc.drawText(pText, nWidth, nHeight, eAlignMask) );

		/*init image information */
		SkBitmap *pBitmap = dc.getBitmap();
		CC_BREAK_IF(! pBitmap);

		int nWidth	= pBitmap->width();
		int nHeight	= pBitmap->height();
		CC_BREAK_IF(nWidth <= 0 || nHeight <= 0);

		int nDataLen = pBitmap->rowBytes() * pBitmap->height();
		m_pData = new unsigned char[nDataLen];
		CC_BREAK_IF(! m_pData);
		memcpy((void*) m_pData, pBitmap->getPixels(), nDataLen);

		m_nWidth    = (short)nWidth;
		m_nHeight   = (short)nHeight;
		m_bHasAlpha = true;
		m_bPreMulti = true;
		m_nBitsPerComponent = pBitmap->bytesPerPixel();

		bRet = true;
    } while (0);

    return bRet;
}

NS_CC_END;

