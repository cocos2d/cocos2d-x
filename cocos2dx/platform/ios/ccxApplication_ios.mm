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

#import "ccxApplication_ios.h"

#import <UIKit/UIKit.h>

#import "CGGeometry.h"
#import "CCDirectorCaller.h"

NS_CC_BEGIN;

ccxApplication* ccxApplication::sm_pSharedApplication = 0;

ccxApplication::ccxApplication()
{
    CCX_ASSERT(! sm_pSharedApplication);
    sm_pSharedApplication = this;
}

ccxApplication::~ccxApplication()
{
    CCX_ASSERT(this == sm_pSharedApplication);
    sm_pSharedApplication = 0;
}

int ccxApplication::run()
{
    if (initInstance() && applicationDidFinishLaunching()) 
    {
        [[CCDirectorCaller sharedDirectorCaller] startMainLoop];
    }
    return 0;
}

void ccxApplication::setAnimationInterval(double interval)
{
    [[CCDirectorCaller sharedDirectorCaller] setAnimationInterval: interval ];
}

ccxApplication::Orientation ccxApplication::setOrientation(Orientation eOritation)
{
    UIApplication * app = [UIApplication sharedApplication];
    UIInterfaceOrientation newOrientation;
    switch (eOritation)
    {
    case kOrientationPortrait:
        newOrientation = UIInterfaceOrientationPortrait;
        break;
    case kOrientationPortraitUpsideDown:
        newOrientation = UIInterfaceOrientationPortraitUpsideDown;
        break;
    case kOrientationLandscapeLeft:
        newOrientation = UIInterfaceOrientationLandscapeRight;
        break;
    case kOrientationLandscapeRight:
        newOrientation = UIInterfaceOrientationLandscapeLeft;
        break;
    default:
        newOrientation = UIInterfaceOrientationPortrait;
        break;
    }
    if (newOrientation != [app statusBarOrientation])
    {
        [app setStatusBarOrientation: newOrientation];
    }
    return eOritation;
}

void ccxApplication::statusBarFrame(cocos2d::CGRect * rect)
{
    rect->origin.x = [[UIApplication sharedApplication] statusBarFrame].origin.x;
    rect->origin.y = [[UIApplication sharedApplication] statusBarFrame].origin.y;
    rect->size.width = [[UIApplication sharedApplication] statusBarFrame].size.width;
    rect->size.height = [[UIApplication sharedApplication] statusBarFrame].size.height;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// static member function
//////////////////////////////////////////////////////////////////////////////////////////////////

ccxApplication& ccxApplication::sharedApplication()
{
    CCX_ASSERT(sm_pSharedApplication);
    return *sm_pSharedApplication;
}

NS_CC_END;
