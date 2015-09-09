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
