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
#include "CCEGLView_android.h"
#include "GLES/gl.h"
#include "CCSet.h"
#include "CCDirector.h"
#include "ccMacros.h"
#include "CCTouchDispatcher.h"
#include "jni/IMEJni.h"
#include "jni/MessageJni.h"

#include <stdlib.h>

namespace cocos2d {

CCEGLView::CCEGLView()
    : m_bNotHVGA(false), 
      m_pDelegate(NULL),
      m_fScreenScaleFactor(1.0)  
{
}

void CCEGLView::setFrameWidthAndHeight(int width, int height)
{
	m_sSizeInPixel.width = width;
	m_sSizeInPixel.height = height;
}

void CCEGLView::create(int width, int height)
{
	if (width == 0 || height == 0)
	{
		return;
	}

	m_sSizeInPoint.width = width;
	m_sSizeInPoint.height = height;

	// calculate the factor and the rect of viewport	
	m_fScreenScaleFactor =  MIN((float)m_sSizeInPixel.width / m_sSizeInPoint.width, 
		                         (float)m_sSizeInPixel.height / m_sSizeInPoint.height);
	int viewPortW = (int)(m_sSizeInPoint.width * m_fScreenScaleFactor);
	int viewPortH = (int)(m_sSizeInPoint.height * m_fScreenScaleFactor);
	m_rcViewPort.origin.x = (m_sSizeInPixel.width - viewPortW) / 2;
	m_rcViewPort.origin.y = (m_sSizeInPixel.height - viewPortH) / 2;
	m_rcViewPort.size.width = viewPortW;
	m_rcViewPort.size.height = viewPortH;
	
	m_bNotHVGA = true;
	
}

CCEGLView::~CCEGLView()
{
	CC_SAFE_DELETE(m_pDelegate);
}

CCSize  CCEGLView::getSize()
{
        if (m_bNotHVGA)
        {
                CCSize size(m_sSizeInPoint.width, m_sSizeInPoint.height);
	        return size;
        }
        else
        {
                CCSize size(m_sSizeInPixel.width, m_sSizeInPixel.height);
	        return size;
        }
	
}

bool CCEGLView::isOpenGLReady()
{
	return (m_sSizeInPixel.width != 0 && m_sSizeInPixel.height != 0);
}

void CCEGLView::release()
{
	terminateProcessJNI();
}

void CCEGLView::setTouchDelegate(EGLTouchDelegate * pDelegate)
{
	m_pDelegate = pDelegate;
}

EGLTouchDelegate* CCEGLView::getDelegate(void)
{
	return m_pDelegate;
}

void CCEGLView::swapBuffers()
{
}

bool CCEGLView::canSetContentScaleFactor()
{
    // can scale content?
    return false;
}

void CCEGLView::setContentScaleFactor(float contentScaleFactor)
{
	m_fScreenScaleFactor = contentScaleFactor;
} 

void CCEGLView::setViewPortInPoints(float x, float y, float w, float h)
{
    if (m_bNotHVGA)
    {
        float factor = m_fScreenScaleFactor / CC_CONTENT_SCALE_FACTOR();
        glViewport((GLint)(x * factor) + m_rcViewPort.origin.x,
            (GLint)(y * factor) + m_rcViewPort.origin.y,
            (GLint)(w * factor),
            (GLint)(h * factor));
    }
    else
    {
        glViewport((GLint)x,
            (GLint)y,
            (GLint)w,
            (GLint)h);
    }		
}

void CCEGLView::setScissorInPoints(float x, float y, float w, float h)
{
    if (m_bNotHVGA)
    {
        float factor = m_fScreenScaleFactor / CC_CONTENT_SCALE_FACTOR();
        glScissor((GLint)(x * factor) + m_rcViewPort.origin.x,
            (GLint)(y * factor) + m_rcViewPort.origin.y,
            (GLint)(w * factor),
            (GLint)(h * factor));
    }
    else
    {
        glScissor((GLint)x,
            (GLint)y,
            (GLint)w,
            (GLint)h);
    }		
}

CCEGLView& CCEGLView::sharedOpenGLView()
{
	static CCEGLView instance;
	return instance;
}

float CCEGLView::getScreenScaleFactor()
{
        return m_fScreenScaleFactor;
}

CCRect CCEGLView::getViewPort()
{
    if (m_bNotHVGA)
    {
        return m_rcViewPort;
    }
    else
    {
        CCRect rect(0, 0, 0, 0);
        return rect;
    }
}

void CCEGLView::setIMEKeyboardState(bool bOpen)
{

    setKeyboardStateJNI((int)bOpen);
}

}       // end of namespace cocos2d

