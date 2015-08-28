#include "Profile.h"

#define LOG_FILE_NAME       "PerformanceLog.plist"

static Profile* s_profile = nullptr;

USING_NS_CC;

// tools methods
std::string genStr(const char* format, ...)
{
    va_list arg_ptr;
    va_start(arg_ptr, format);
    char temp[256];
    sprintf(temp, format, arg_ptr);
    va_end(arg_ptr);
    return temp;
}

std::vector<std::string> genStrVector(const char* str1, ...)
{
    std::vector<std::string> ret;
    va_list arg_ptr;
    const char* str = str1;
    va_start(arg_ptr, str1);
    while (nullptr != str) {
        std::string strObj = str;
        ret.push_back(strObj);
        str = va_arg(arg_ptr, const char*);
    }
    va_end(arg_ptr);
    
    return ret;
}

Profile* Profile::getInstance()
{
    if (nullptr == s_profile)
    {
        s_profile = new Profile();
    }
    
    return s_profile;
}

void Profile::releaseInstance()
{
    if (nullptr != s_profile)
    {
        delete s_profile;
    }
}

Profile::Profile()
{
    
}

Profile::~Profile()
{
    
}

void Profile::setDeviceName(std::string name)
{
    testData["device"] = Value(name);
}

void Profile::setEngineVersion(std::string version)
{
    testData["engineVersion"] = Value(version);
}

void Profile::testCaseBegin(std::string testName, std::vector<std::string> condHeaders, std::vector<std::string> retHeaders)
{
    curTestName = testName;
    curCondHeaders = condHeaders;
    curRetHeaders = retHeaders;
    curTestResults.clear();
}

void Profile::addTestResult(std::vector<std::string> conditions, std::vector<std::string> results)
{
    ValueMap curInfo;

    ValueMap condInfo;
    auto conditionSize = conditions.size();
    auto conHeaderSize = curCondHeaders.size();
    for (int i = 0; i < conditionSize; i++) {
        if (i >= conHeaderSize)
        {
            // the number of conditions is larger than the number of condition headers
            break;
        }
        
        std::string header = curCondHeaders.at(i);
        Value condValue = Value(conditions.at(i));
        condInfo[header] = condValue;
    }

    ValueMap retInfo;
    auto retSize = results.size();
    auto retHeaderSize = curRetHeaders.size();
    for (int i = 0; i < retSize; i++) {
        if (i >= retHeaderSize)
        {
            // the number of results is larger than the number of result headers
            break;
        }
        
        std::string header = curRetHeaders.at(i);
        Value retValue = Value(results.at(i));
        retInfo[header] = retValue;
    }
    
    curInfo["conditions"] = condInfo;
    curInfo["results"] = retInfo;
    curTestResults.push_back(Value(curInfo));
}

void Profile::testCaseEnd()
{
    // add the result of current test case into the testData.
    testData[curTestName] = Value(curTestResults);

    // write the testData to log file.
    auto writablePath = cocos2d::FileUtils::getInstance()->getWritablePath();
    char fullPath[256];
    sprintf(fullPath, "%s/%s", writablePath.c_str(), LOG_FILE_NAME);
    
    cocos2d::FileUtils::getInstance()->writeValueMapToFile(testData, fullPath);
}
