/****************************************************************************
Copyright (c) 2013 The Chromium Authors

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

#include "CCApplication.h"
#include "CCEGLView.h"
#include <unistd.h>
#include <sys/time.h>
#include <string>
#include "CCDirector.h"

NS_CC_BEGIN

CCApplication* CCApplication::sm_pSharedApplication = 0;
bool CCApplication::s_running = false;

/*
static long getCurrentMillSecond()
{
    long lLastTime;
    struct timeval stCurrentTime;
    gettimeofday(&stCurrentTime,NULL);
    // millseconds
    lLastTime = stCurrentTime.tv_sec * 1000 + stCurrentTime.tv_usec * 0.001;
    return lLastTime;
}
*/

CCApplication::CCApplication()
{
    CC_ASSERT(!sm_pSharedApplication);
    sm_pSharedApplication = this;
    setAnimationInterval(1.0f/60.0f);
}

CCApplication::~CCApplication()
{
    CC_ASSERT(this == sm_pSharedApplication);
    sm_pSharedApplication = NULL;
}

int CCApplication::run()
{
    // Initialize instance and cocos2d.
    if (!applicationDidFinishLaunching())
        return 0;

    s_running = true;
    for (;;)
    {
        //long iLastTime = getCurrentMillSecond();
        CCDirector::sharedDirector()->mainLoop();
        CCEGLView::sharedOpenGLView()->ProcessEventQueue();

        //long iCurTime = getCurrentMillSecond();
        /*
        if (iCurTime-iLastTime<m_nAnimationInterval)
        {
            usleep((m_nAnimationInterval - iCurTime+iLastTime)*1000);
        }
        */
    }

    s_running = false;
    return -1;
}

void CCApplication::setAnimationInterval(double interval)
{
    m_nAnimationInterval = interval * 1000.0f;
}

TargetPlatform CCApplication::getTargetPlatform()
{
    return kTargetNaCl;
}

CCApplication* CCApplication::sharedApplication()
{
    CC_ASSERT(sm_pSharedApplication);
    return sm_pSharedApplication;
}

ccLanguageType CCApplication::getCurrentLanguage()
{
    ccLanguageType ret = kLanguageEnglish;
    return ret;
}

NS_CC_END
