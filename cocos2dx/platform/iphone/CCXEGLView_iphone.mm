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
#include "CCXEGLView_iphone.h"
#include "NSSet.h"
#include "CCTouch.h"
#include "CCTouchDispatcher.h"

namespace cocos2d {

CCXEGLView::CCXEGLView()
{

}

CCXEGLView::~CCXEGLView()
{

}

cocos2d::CGSize  CCXEGLView::getSize()
{
	cocos2d::CGSize size([[EAGLView sharedEGLView] getWidth], [[EAGLView sharedEGLView] getHeight]);
	return size;
}

bool CCXEGLView::isOpenGLReady()
{
    return [EAGLView sharedEGLView] != NULL;
}
    
    bool CCXEGLView::canSetContentScaleFactor()
    {
       return [[EAGLView sharedEGLView] respondsToSelector:@selector(setContentScaleFactor:)];
    }
    
    void CCXEGLView::setContentScaleFactor(float contentScaleFactor)
    {
        [[EAGLView sharedEGLView] setContentScaleFactor:contentScaleFactor];
    }

void CCXEGLView::release()
{
	[CCDirectorCaller destroy];
	
	// destroy EAGLView
	[[EAGLView sharedEGLView] removeFromSuperview];
}

void CCXEGLView::setTouchDelegate(EGLTouchDelegate * pDelegate)
{
    m_pDelegate = pDelegate;
}

void CCXEGLView::swapBuffers()
{
	[[EAGLView sharedEGLView] swapBuffers];
}
	
void CCXEGLView::touchesBegan(NSSet *set)
{
	if (m_pDelegate) {
		m_pDelegate->touchesBegan(set, NULL);
	}
}

void CCXEGLView::touchesMoved(NSSet *set)
{
	if (m_pDelegate) {
		m_pDelegate->touchesMoved(set, NULL);
	}
}

void CCXEGLView::touchesEnded(NSSet *set)
{
	if (m_pDelegate) {
		m_pDelegate->touchesEnded(set, NULL);
	}
}

void CCXEGLView::touchesCancelled(NSSet *set)
{
	if (m_pDelegate) {
		m_pDelegate->touchesCancelled(set, NULL);
	}
}

}       // end of namespace cocos2d

