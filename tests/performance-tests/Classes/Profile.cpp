#include "Profile.h"
#include "json/document.h"
#include "json/prettywriter.h"
#include "json/stringbuffer.h"

#define LOG_FILE_NAME       "PerformanceLog.json"
#define PLIST_FILE_NAME     "PerformanceLog.plist"

static Profile* s_profile = nullptr;

USING_NS_CC;

// tools methods
std::string genStr(const char* format, ...)
{
    va_list arg_ptr;
    va_start(arg_ptr, format);
    
    int bufferSize = MAX_LOG_LENGTH;
    char buf[bufferSize];
    vsnprintf(buf, bufferSize - 3, format, arg_ptr);

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
    
    auto findValue = testData.find(curTestName);
    if (findValue != testData.end())
    {
        curTestResults = findValue->second.asValueVector();
    }
    else
    {
        curTestResults.clear();
    }
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
}

void Profile::flush()
{
    auto writablePath = cocos2d::FileUtils::getInstance()->getWritablePath();
    std::string fullPath = genStr("%s/%s", writablePath.c_str(), LOG_FILE_NAME);
    
    rapidjson::Document document;
    rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
    rapidjson::Value theData = valueMapToJson(testData, allocator);
    
    rapidjson::StringBuffer buffer;

    // write pretty format json
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);

    // write json in one line
//    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);

    theData.Accept(writer);
    auto out = buffer.GetString();
    
    FILE *fp = fopen(fullPath.c_str(), "w");
    fputs(out, fp);
    fclose(fp);

//  // Write the test data into plist file.
//    std::string plistFullPath = genStr("%s/%s", writablePath.c_str(), PLIST_FILE_NAME);
//    cocos2d::FileUtils::getInstance()->writeValueMapToFile(testData, plistFullPath);
}
