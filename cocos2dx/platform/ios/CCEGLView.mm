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
#include "CCEGLView.h"
#include "CCSet.h"
#include "CCTouch.h"
#include "CCTouchDispatcher.h"

NS_CC_BEGIN

CCEGLView::CCEGLView()
{

}

CCEGLView::~CCEGLView()
{

}

CCSize CCEGLView::getSize()
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

void CCEGLView::end()
{
    [CCDirectorCaller destroy];
    
    // destroy EAGLView
    [[EAGLView sharedEGLView] removeFromSuperview];
}


void CCEGLView::swapBuffers()
{
    [[EAGLView sharedEGLView] swapBuffers];
}

CCSize  CCEGLView::getFrameSize()
{
    assert(false);
	return CCSizeMake(0, 0);
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

NS_CC_END

