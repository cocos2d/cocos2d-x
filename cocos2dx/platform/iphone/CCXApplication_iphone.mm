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

#include "CCXApplication_iphone.h"
#include "CCXUIImage_iphone.h"
#include "CCXEGLView_iphone.h"
#include "CCDirector.h"

#include <GLES/gl.h>

namespace   cocos2d {
    static CCXApplication *s_pApplication;

    CCXApplication::CCXApplication()
    {
    	s_pApplication = this;
    }

    CCXApplication::~CCXApplication()
    {
        
    }

	ccDeviceOrientation CCXApplication::setDeviceOrientation(ccDeviceOrientation eOritation)
    {
        return eOritation;
    }

    CGRect CCXApplication::statusBarFrame()
    {
        CGRect rc;
        return rc;
    }
	
    void CCXApplication::run()
    {
        initCocos2d();
        [[CCDirectorCaller sharedDirectorCaller] startMainLoop];
    }

	//////////////////////////////////////////////////////////////////////////
	/// Implement static class member
	//////////////////////////////////////////////////////////////////////////
	CCXApplication * CCXApplication::getSharedApplication()
	{
		return s_pApplication;
	}
}

