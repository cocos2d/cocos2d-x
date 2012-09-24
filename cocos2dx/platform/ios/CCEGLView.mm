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
    m_obScreenSize.width = m_obDesignResolutionSize.width = [[EAGLView sharedEGLView] getWidth];
    m_obScreenSize.height = m_obDesignResolutionSize.height = [[EAGLView sharedEGLView] getHeight];
}

CCEGLView::~CCEGLView()
{

}

bool CCEGLView::isOpenGLReady()
{
    return [EAGLView sharedEGLView] != NULL;
}
    
bool CCEGLView::setContentScaleFactor(float contentScaleFactor)
{
    assert(m_eResolutionPolicy == kResolutionUnKnown); // cannot enable retina mode
	
	m_fScaleX = m_fScaleY = contentScaleFactor;
	[[EAGLView sharedEGLView] setNeedsLayout];
        
	return true;
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

CCEGLView* CCEGLView::sharedOpenGLView()
{
    static CCEGLView instance;
    return &instance;
}

NS_CC_END

