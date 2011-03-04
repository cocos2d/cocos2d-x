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

#import "CCDirectorCaller.h"
#import <UIKit/UIKit.h>

#include "CCApplication_iphone.h"
#include "CCImage_iphone.h"
#include "CCEGLView_iphone.h"
#include "CCDirector.h"

#include <GLES/gl.h>

namespace   cocos2d {
    static CCApplication *s_pApplication;

    CCApplication::CCApplication()
    {
    	s_pApplication = this;
    }

    CCApplication::~CCApplication()
    {
        
    }

	ccDeviceOrientation CCApplication::setDeviceOrientation(ccDeviceOrientation eOritation)
    {
        ccDeviceOrientation oldOrientation = CCDirector::sharedDirector()->getDeviceOrientation();
        
        if (eOritation != oldOrientation)
        {
            switch (eOritation) {
                case CCDeviceOrientationPortrait:
                    [[UIApplication sharedApplication] setStatusBarOrientation: UIInterfaceOrientationPortrait animated: NO];
                    break;
                case CCDeviceOrientationPortraitUpsideDown:
                    [[UIApplication sharedApplication] setStatusBarOrientation: UIInterfaceOrientationPortraitUpsideDown animated: NO];
                    break;
                case CCDeviceOrientationLandscapeLeft:
                    [[UIApplication sharedApplication] setStatusBarOrientation: UIInterfaceOrientationLandscapeRight animated: NO];
                    break;
               case CCDeviceOrientationLandscapeRight:
                    [[UIApplication sharedApplication] setStatusBarOrientation: UIInterfaceOrientationLandscapeLeft animated: NO];
                   break;
                default:
                    break;
            }
        }
        
        return eOritation;
    }

    CCRect CCApplication::statusBarFrame()
    {
        float originX = [[UIApplication sharedApplication] statusBarFrame].origin.x;
        float originY = [[UIApplication sharedApplication] statusBarFrame].origin.y;
        float width = [[UIApplication sharedApplication] statusBarFrame].size.width;
        float height = [[UIApplication sharedApplication] statusBarFrame].size.height;
        CCRect rc(originX, originY, width, height);
        
        return rc;
    }
	
    void CCApplication::run()
    {
        applicationDidFinishLaunching();
        [[CCDirectorCaller sharedDirectorCaller] startMainLoop];
    }

        void CCApplication::setAnimationInterval(double interval)
        {
                [[CCDirectorCaller sharedDirectorCaller] setAnimationInterval: interval ];
        }
	
	//////////////////////////////////////////////////////////////////////////
	/// Implement static class member
	//////////////////////////////////////////////////////////////////////////
	CCApplication * CCApplication::sharedApplication()
	{
		return s_pApplication;
	}
}

