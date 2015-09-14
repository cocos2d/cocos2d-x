#include "Profile.h"
#include "json/document.h"
#include "json/prettywriter.h"
#include "json/stringbuffer.h"
#include "platform/CCFileUtils.h"
#include "cocos2d.h"
#include <time.h>

#define LOG_FILE_NAME_FMT   "PerformanceLog-%s-%s.json"
#define PLIST_FILE_NAME     "PerformanceLog.plist"

#define KEY_DEVICE              "device"
#define KEY_ENGINE_VERSION      "engineVersion"
#define KEY_RESULTS             "results"
#define KEY_CONDITION_HEADERS   "conditionHeaders"
#define KEY_RESULT_HEADERS      "resultHeaders"
#define KEY_FILE_VERSION        "fileVersion"
#define KEY_OS_VERSION          "osVersion"
#define KEY_TIMESTAMP           "timeStamp"

#define FILE_VERSION          1

#define USE_PRETTY_OUTPUT_FORMAT        0
#define USE_JSON_FORMAT                 1


// For different device & os, change these values
// TODO : get device info automatically
#define DEVICE_NAME         "DeviceName"
#define OS_VERSION          "SystemVersion"

static Profile* s_profile = nullptr;

USING_NS_CC;

// tools methods
std::string genStr(const char* format, ...)
{
    va_list arg_ptr;
    va_start(arg_ptr, format);

    char buf[MAX_LOG_LENGTH];
    vsnprintf(buf, MAX_LOG_LENGTH - 3, format, arg_ptr);

    va_end(arg_ptr);

    return buf;
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

// declare the methods
rapidjson::Value valueVectorToJson(cocos2d::ValueVector & theVector, rapidjson::Document::AllocatorType& allocator);
rapidjson::Value valueMapToJson(cocos2d::ValueMap & theMap, rapidjson::Document::AllocatorType& allocator);

rapidjson::Value convertToJsonValue(cocos2d::Value & value, rapidjson::Document::AllocatorType& allocator)
{
    rapidjson::Value theJsonValue;
    auto type = value.getType();
    switch (type) {
        case cocos2d::Value::Type::STRING:
            theJsonValue.SetString(value.asString().c_str(), allocator);
            break;
        case cocos2d::Value::Type::MAP:
            theJsonValue = valueMapToJson(value.asValueMap(), allocator);
            break;
        case cocos2d::Value::Type::VECTOR:
            theJsonValue = valueVectorToJson(value.asValueVector(), allocator);
            break;
        case cocos2d::Value::Type::INTEGER:
            theJsonValue.SetInt(value.asInt());
            break;
        case cocos2d::Value::Type::BOOLEAN:
            theJsonValue.SetBool(value.asBool());
            break;
        case cocos2d::Value::Type::FLOAT:
        case cocos2d::Value::Type::DOUBLE:
            theJsonValue.SetDouble(value.asDouble());
            break;
        default:
            break;
    }
    
    return theJsonValue;
}

rapidjson::Value valueMapToJson(cocos2d::ValueMap & theMap, rapidjson::Document::AllocatorType& allocator)
{
    rapidjson::Value ret(rapidjson::kObjectType);
    
    for (ValueMap::iterator iter = theMap.begin(); iter != theMap.end(); ++iter) {
        auto key = iter->first;
        rapidjson::Value theJsonKey(rapidjson::kStringType);
        theJsonKey.SetString(key.c_str(), allocator);
        
        cocos2d::Value value = iter->second;
        rapidjson::Value theJsonValue = convertToJsonValue(value, allocator);
        ret.AddMember(theJsonKey, theJsonValue, allocator);
    }
    return ret;
}

rapidjson::Value valueVectorToJson(cocos2d::ValueVector & theVector, rapidjson::Document::AllocatorType& allocator)
{
    rapidjson::Value ret(rapidjson::kArrayType);
    
    auto vectorSize = theVector.size();
    for (int i = 0; i < vectorSize; i++) {
        cocos2d::Value value = theVector[i];
        rapidjson::Value theJsonValue = convertToJsonValue(value, allocator);
        ret.PushBack(theJsonValue, allocator);
    }
    
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

void Profile::destroyInstance()
{
    CC_SAFE_DELETE(s_profile);
}

Profile::Profile()
{
    
}

Profile::~Profile()
{
    
}

void Profile::testCaseBegin(std::string testName, std::vector<std::string> condHeaders, std::vector<std::string> retHeaders)
{
    curTestName = testName;

    ValueVector conds;
    for (int i = 0; i < condHeaders.size(); i++) {
        conds.push_back(Value(condHeaders[i]));
    }
    
    ValueVector rets;
    for (int j = 0; j < retHeaders.size(); j++) {
        rets.push_back(Value(retHeaders[j]));
    }
    
    auto findValue = testData.find(curTestName);
    if (findValue != testData.end())
    {
        auto curMap = findValue->second.asValueMap();
        curMap[KEY_CONDITION_HEADERS] = Value(conds);
        curMap[KEY_RESULT_HEADERS] = Value(rets);

        if (curMap.find(KEY_RESULTS) != curMap.end())
            curTestResults = curMap[KEY_RESULTS].asValueVector();
        else
            curTestResults.clear();
    }
    else
    {
        ValueMap theData;
        theData[KEY_CONDITION_HEADERS] = conds;
        theData[KEY_RESULT_HEADERS] = rets;
        testData[curTestName] = Value(theData);
        curTestResults.clear();
    }
}

void Profile::addTestResult(std::vector<std::string> conditions, std::vector<std::string> results)
{
    ValueVector curRet;

    for (int i = 0; i < conditions.size(); i++) {
        curRet.push_back(Value(conditions[i]));
    }
    
    for (int j = 0; j < results.size(); j++) {
        curRet.push_back(Value(results[j]));
    }
    curTestResults.push_back(Value(curRet));
}

void Profile::testCaseEnd()
{
    // add the result of current test case into the testData.
    ValueMap theData = testData[curTestName].asValueMap();
    theData[KEY_RESULTS] = curTestResults;
    testData[curTestName] = Value(theData);
}

void Profile::flush()
{
    // record the format version
    testData[KEY_FILE_VERSION] = Value(FILE_VERSION);
    testData[KEY_DEVICE] = Value(DEVICE_NAME);
    testData[KEY_OS_VERSION] = Value(OS_VERSION);
    testData[KEY_ENGINE_VERSION] = Value(cocos2d::cocos2dVersion());
    time_t t = time(0);
    localtime(&t);
    testData[KEY_TIMESTAMP] = Value(genStr("%ld", t));

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    std::string checkPath = "/mnt/sdcard/PerfTest";
    auto writablePath = checkPath;
    if (! cocos2d::FileUtils::getInstance()->isDirectoryExist(checkPath)) {
        auto createRet = cocos2d::FileUtils::getInstance()->createDirectory(checkPath);
        if (! createRet) {
            writablePath = cocos2d::FileUtils::getInstance()->getWritablePath();
        }
    }
    cocos2d::log("write path : %s", writablePath.c_str());
#else
    auto writablePath = cocos2d::FileUtils::getInstance()->getWritablePath();
#endif

#if USE_JSON_FORMAT
    char timeStr[64];
    strftime(timeStr, sizeof(timeStr), "%Y-%m-%d-%H%M", localtime(&t));
    std::string fileName = genStr(LOG_FILE_NAME_FMT, DEVICE_NAME, timeStr);
    std::string fullPath = genStr("%s/%s", writablePath.c_str(), fileName.c_str());

    rapidjson::Document document;
    rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
    rapidjson::Value theData = valueMapToJson(testData, allocator);
    
    rapidjson::StringBuffer buffer;

#if USE_PRETTY_OUTPUT_FORMAT
    // write pretty format json
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
#else  // #else USE_PRETTY_OUTPUT_FORMAT
    // write json in one line
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
#endif // #endif USE_PRETTY_OUTPUT_FORMAT

    theData.Accept(writer);
    auto out = buffer.GetString();
    
    FILE *fp = fopen(fullPath.c_str(), "w");
    fputs(out, fp);
    fclose(fp);
#else  // #else USE_JSON_FORMAT
    // Write the test data into plist file.
    std::string plistFullPath = genStr("%s/%s", writablePath.c_str(), PLIST_FILE_NAME);
    cocos2d::FileUtils::getInstance()->writeValueMapToFile(testData, plistFullPath);
#endif // #endif USE_JSON_FORMAT
}
