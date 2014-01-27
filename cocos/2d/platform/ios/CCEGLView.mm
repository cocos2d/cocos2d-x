/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org
 Copyright (c) 2013-2014 Chukong Technologies Inc.

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

NS_CC_BEGIN

EGLView::EGLView()
{
    _screenSize.width = _designResolutionSize.width = [[CCEAGLView sharedEGLView] getWidth];
    _screenSize.height = _designResolutionSize.height = [[CCEAGLView sharedEGLView] getHeight];
}

EGLView::~EGLView()
{

}

bool EGLView::isOpenGLReady()
{
    return [CCEAGLView sharedEGLView] != nullptr;
}
    
bool EGLView::setContentScaleFactor(float contentScaleFactor)
{
    assert(_resolutionPolicy == ResolutionPolicy::UNKNOWN); // cannot enable retina mode
	
	_scaleX = _scaleY = contentScaleFactor;
	[[CCEAGLView sharedEGLView] setNeedsLayout];
        
	return true;
}

void EGLView::end()
{
    [CCDirectorCaller destroy];
    
    // destroy EAGLView
    [[CCEAGLView sharedEGLView] removeFromSuperview];
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

EGLView* EGLView::getInstance()
{
    static EGLView instance;
    return &instance;
}

// XXX: deprecated
EGLView* EGLView::sharedOpenGLView()
{
    return EGLView::getInstance();
}

NS_CC_END

