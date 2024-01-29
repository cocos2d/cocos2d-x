/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
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

#include "BugsTest.h"
#include "Bug-350.h"
#include "Bug-422.h"
#include "Bug-458/Bug-458.h"
#include "Bug-624.h"
#include "Bug-886.h"
#include "Bug-899.h"
#include "Bug-914.h"
#include "Bug-1159.h"
#include "Bug-1174.h"
#include "Bug-12847.h"
#include "Bug-Child.h"
#include "Bug-CCDrawNode.h"
#include "Bug-15594.h"
#include "Bug-15776.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include "Bug-14327.h"
#endif

BugsTests::BugsTests()
{
    ADD_TEST_CASE(Bug350Layer);
    ADD_TEST_CASE(Bug422Layer);
    ADD_TEST_CASE(Bug458Layer);
    ADD_TEST_CASE(Bug624Layer);
    ADD_TEST_CASE(Bug886Layer);
    ADD_TEST_CASE(Bug899Layer);
    ADD_TEST_CASE(Bug914Layer);
    ADD_TEST_CASE(Bug1159Layer);
    ADD_TEST_CASE(Bug1174Layer);
    ADD_TEST_CASE(BugChild);
    ADD_TEST_CASE(BugCameraMask);
    ADD_TEST_CASE(BugDrawNodeLayer);
    ADD_TEST_CASE(Bug12847Layer);
    ADD_TEST_CASE(Bug15594Layer);
    
    // NOTE: comment this out because it currently crashes during autotest
    //ADD_TEST_CASE(Bug15776Layer);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
    ADD_TEST_CASE(Bug14327Layer);
#endif
}
