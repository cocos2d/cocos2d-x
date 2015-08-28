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
    static void releaseInstance();
    
    Profile();
    virtual ~Profile();

    // Set the basic attribute of the profile.
    void setDeviceName(std::string name);
    void setEngineVersion(std::string version);
    
    // methods for test cases
    void testCaseBegin(std::string testName, std::vector<std::string> condHeaders, std::vector<std::string> retHeaders);
    void addTestResult(std::vector<std::string> conditions, std::vector<std::string> results);
    void testCaseEnd();

protected:
    cocos2d::ValueMap testData;
    
    std::string curTestName;
    std::vector<std::string> curCondHeaders;
    std::vector<std::string> curRetHeaders;
    cocos2d::ValueVector curTestResults;
};

#endif // __PROFILE_H__
