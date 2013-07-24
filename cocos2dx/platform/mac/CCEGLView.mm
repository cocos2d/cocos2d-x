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
#include "CCEGLView.h"
#include "EAGLView.h"
#include "CCDirectorCaller.h"
#include "CCSet.h"
#include "CCTouch.h"
#include "CCTouchDispatcher.h"

NS_CC_BEGIN

EGLView* EGLView::s_sharedView = NULL;

EGLView* EGLView::getInstance(void)
{
    if (!s_sharedView)
    {
        s_sharedView = new EGLView();
    }
    return s_sharedView;
}

// XXX: deprecated
EGLView* EGLView::sharedOpenGLView()
{
    return EGLView::getInstance();
}

EGLView::EGLView(void)
{
}

EGLView::~EGLView(void)
{
    CCLOG("cocos2d: deallocing EGLView %p", this);
    s_sharedView = NULL;
}

bool EGLView::isOpenGLReady(void)
{
    return [CCEAGLView sharedEGLView] != NULL;
}

bool EGLView::setContentScaleFactor(float contentScaleFactor)
{
    return false;
}

void EGLView::end(void)
{
    [[CCDirectorCaller sharedDirectorCaller] end];
    
    // destroy EAGLView
    [[CCEAGLView sharedEGLView] removeFromSuperview];
    
    delete this;
}

void EGLView::swapBuffers()
{
	[[CCEAGLView sharedEGLView] swapBuffers];
}

void EGLView::setIMEKeyboardState(bool bOpen)
{
    if (bOpen)
    {
        [[CCEAGLView sharedEGLView] becomeFirstResponder];
    }
    else
    {
        [[CCEAGLView sharedEGLView] resignFirstResponder];
    }
}

void EGLView::setViewPortInPoints(float x , float y , float w , float h)
{
    float frameZoomFactor = [[CCEAGLView sharedEGLView] frameZoomFactor];
    
    glViewport((GLint)(x * _scaleX * frameZoomFactor + _viewPortRect.origin.x * frameZoomFactor),
               (GLint)(y * _scaleY * frameZoomFactor + _viewPortRect.origin.y * frameZoomFactor),
               (GLsizei)(w * _scaleX * frameZoomFactor),
               (GLsizei)(h * _scaleY * frameZoomFactor));
}

void EGLView::setScissorInPoints(float x , float y , float w , float h)
{
    float frameZoomFactor = [[CCEAGLView sharedEGLView] frameZoomFactor];
    
    glScissor((GLint)(x * _scaleX * frameZoomFactor + _viewPortRect.origin.x * frameZoomFactor),
              (GLint)(y * _scaleY * frameZoomFactor + _viewPortRect.origin.y * frameZoomFactor),
              (GLsizei)(w * _scaleX * frameZoomFactor),
              (GLsizei)(h * _scaleY * frameZoomFactor));
}

void EGLView::setMultiTouchMask(bool mask)
{
	//CCEAGLView *glView = [CCEAGLView sharedEGLView];
	//glView.multipleTouchEnabled = mask ? YES : NO;
}

NS_CC_END // end of namespace cocos2d;
