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
#include "EAGLView.h"
#include "CCDirectorCaller.h"
#include "CCEGLView_ios.h"
#include "CCSet.h"
#include "CCTouch.h"
#include "CCTouchDispatcher.h"

namespace cocos2d {

CCEGLView::CCEGLView()
: m_pDelegate(0)
{

}

CCEGLView::~CCEGLView()
{

}

cocos2d::CCSize  CCEGLView::getSize()
{
	cocos2d::CCSize size([[EAGLView sharedEGLView] getWidth], [[EAGLView sharedEGLView] getHeight]);
	return size;
}

bool CCEGLView::isIpad()
{
    return UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad;
}

bool CCEGLView::isOpenGLReady()
{
    return [EAGLView sharedEGLView] != NULL;
}
    
    bool CCEGLView::canSetContentScaleFactor()
    {
       return [[EAGLView sharedEGLView] respondsToSelector:@selector(setContentScaleFactor:)];
    }
    
    void CCEGLView::setContentScaleFactor(float contentScaleFactor)
    {
        UIView * view = [EAGLView sharedEGLView];
        view.contentScaleFactor = contentScaleFactor;
        [view setNeedsLayout];
    }

void CCEGLView::release()
{
	[CCDirectorCaller destroy];
	
	// destroy EAGLView
	[[EAGLView sharedEGLView] removeFromSuperview];
}

void CCEGLView::setTouchDelegate(EGLTouchDelegate * pDelegate)
{
    m_pDelegate = pDelegate;
}

void CCEGLView::swapBuffers()
{
	[[EAGLView sharedEGLView] swapBuffers];
}
	
void CCEGLView::touchesBegan(CCSet *set)
{
	if (m_pDelegate) {
		m_pDelegate->touchesBegan(set, NULL);
	}
}

void CCEGLView::touchesMoved(CCSet *set)
{
	if (m_pDelegate) {
		m_pDelegate->touchesMoved(set, NULL);
	}
}

void CCEGLView::touchesEnded(CCSet *set)
{
	if (m_pDelegate) {
		m_pDelegate->touchesEnded(set, NULL);
	}
}

void CCEGLView::touchesCancelled(CCSet *set)
{
	if (m_pDelegate) {
		m_pDelegate->touchesCancelled(set, NULL);
	}
}

void CCEGLView::setViewPortInPoints(float x, float y, float w, float h)
{
    glViewport((GLint)x, (GLint)y, (GLint)w, (GLint)h);
}

void CCEGLView::setScissorInPoints(float x, float y, float w, float h)
{
    glScissor((GLint)x, (GLint)y, (GLint)w, (GLint)h);
}

void CCEGLView::setIMEKeyboardState(bool bOpen)
{
    if (bOpen)
    {
        [[EAGLView sharedEGLView] becomeFirstResponder];
    }
    else
    {
        [[EAGLView sharedEGLView] resignFirstResponder];
    }
}

CCEGLView& CCEGLView::sharedOpenGLView()
{
    static CCEGLView instance;
    return instance;
}

float CCEGLView::getMainScreenScale()
{
    return [[UIScreen mainScreen] scale];
}

} // end of namespace cocos2d;
