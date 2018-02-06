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

#ifndef __PROFILE_H__
#define __PROFILE_H__

#include <string.h>
#include <vector>
#include "base/CCMap.h"
#include "base/CCValue.h"
#include "base/CCVector.h"

std::string genStr(const char* format, ...);
std::vector<std::string> genStrVector(const char* str1, ...);

class Profile
{
public:
    static Profile* getInstance();
    static void destroyInstance();
    
    Profile();
    virtual ~Profile();
    
    // methods for test cases
    void testCaseBegin(std::string testName, std::vector<std::string> condHeaders, std::vector<std::string> retHeaders);
    void addTestResult(std::vector<std::string> conditions, std::vector<std::string> results);
    void testCaseEnd();
    
    // write the test result to file
    void flush();

protected:
    cocos2d::ValueMap testData;
    
    std::string curTestName;
    cocos2d::ValueVector curTestResults;
};

#endif // __PROFILE_H__
