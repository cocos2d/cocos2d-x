/****************************************************************************
Copyright (c) 2015 Chukong Technologies Inc.

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
#include "base/CCUserDefaultData.h"
#include "platform/CCCommon.h"
#include "platform/CCFileUtils.h"
#include "tinyxml2.h"
#include "base/base64.h"
#include "base/ccUtils.h"

using namespace std;

NS_CC_BEGIN

UserDefaultData* UserDefaultData::_userDefaultData = nullptr;
DataStoreDelegate* UserDefaultData::_dataStore = nullptr;

void UserDefaultData::makeCurrentUserDefault()
{
    // If first call or change UserDefault Delegate
    if (_userDefaultData == nullptr || UserDefault::getInstance() != _userDefaultData)
    {
        _userDefaultData = new (std::nothrow) UserDefaultData();
    }

    if (_userDefaultData)
    {
        UserDefault::setDelegate(_userDefaultData);
    }
}

UserDefaultData::~UserDefaultData()
{
    CC_SAFE_DELETE(_dataStore);
    _userDefaultData = nullptr;
}

UserDefaultData::UserDefaultData() :_loaded(false)
{
    if (_dataStore == nullptr)
    {
        _dataStore = getDefaultXmlDataStore();
    }
}

void UserDefaultData::checkLoaded()
{
    if (!_loaded)
    {
        bool okLoad = _dataStore->Load(_valueMap);
        if (!okLoad)
        {
            CCLOGERROR("Can't load UserDefaultData");
        }
        _loaded = true;
    }
}

void UserDefaultData::flush()
{
    checkLoaded();

    bool okSave = _dataStore->Save(_valueMap);
    if (!okSave)
    {
        CCLOGERROR("Can't save UserDefaultData");
    }
}



const std::string DATA_STORE_XML_DEFAULT_FILE = "UserDefault.xml";
const std::string DATA_STORE_XML_ROOT_NAME = "userDefaultRoot";
/**
* Delegate Load/Save ValueMap:
*/
class DataStoreXml: public DataStoreDelegate
{
public:
    virtual bool Load(ValueMap& valueMap) override
    {
        std::string filePath = FileUtils::getInstance()->getWritablePath() + DATA_STORE_XML_DEFAULT_FILE;

        if (!FileUtils::getInstance()->isFileExist(filePath))
        {
            return false;
        }

        bool bRet = false;
        do
        {
            tinyxml2::XMLDocument* xmlDoc = new tinyxml2::XMLDocument();

            std::string xmlBuffer = FileUtils::getInstance()->getStringFromFile(filePath);

            if (xmlBuffer.empty())
            {
                CCLOG("DataStoreXml: can not read xml file");
                break;
            }
            xmlDoc->Parse(xmlBuffer.c_str(), xmlBuffer.size());

            // get root node
            auto rootNode = xmlDoc->RootElement();
            if (nullptr == rootNode)
            {
                CCLOG("DataStoreXml: read root node error");
                break;
            }
            // clear data
            valueMap.clear();

            // find the node
            auto curNode = rootNode->FirstChildElement();
            while (nullptr != curNode)
            {
                std::string nodeName = curNode->Value();
                auto textNode = curNode->FirstChild();

                if (!nodeName.empty() && textNode && textNode->Value())
                {
                    std::string text = textNode->Value();
                    if (!text.empty())
                    {
                        Value value(text);
                        std::string type;
                        if (curNode->Attribute("type"))
                        {
                            type = curNode->Attribute("type");
                        }
                        switch (GetType(type))
                        {
                        case Value::Type::INTEGER:
                            value = value.asInt();
                            break;
                        case Value::Type::FLOAT:
                            value = value.asFloat();
                            break;
                        case Value::Type::DOUBLE:
                            value = value.asDouble();
                            break;
                        case Value::Type::BOOLEAN:
                            value = value.asBool();
                            break;
                        }
                        valueMap.insert(std::make_pair(nodeName, value));
                    }
                }

                curNode = curNode->NextSiblingElement();
            }

            bRet = true;
        } while (0);

        return bRet;
    }
    virtual bool Save(ValueMap& valueMap) override
    {
        // Save backup, and move if all ok
        std::string fileTmp = DATA_STORE_XML_DEFAULT_FILE + ".tmp";
        bool bRet = false;
        do
        {
            // Generate xml header
            tinyxml2::XMLDocument *pDoc = new (std::nothrow) tinyxml2::XMLDocument();
            CC_BREAK_IF(nullptr == pDoc);

            tinyxml2::XMLDeclaration *pDeclaration = pDoc->NewDeclaration(nullptr);
            CC_BREAK_IF(nullptr == pDeclaration);

            pDoc->LinkEndChild(pDeclaration);
            tinyxml2::XMLElement *pRootEle = pDoc->NewElement(DATA_STORE_XML_ROOT_NAME.c_str());
            CC_BREAK_IF(nullptr == pRootEle);

            pDoc->LinkEndChild(pRootEle);

            // Generate data
            for (const auto &value : valueMap)
            {
                std::string type = GetValueType(value.second);
                if (!type.empty())
                {
                    tinyxml2::XMLElement* tmpNode = pDoc->NewElement(value.first.c_str());
                    pRootEle->LinkEndChild(tmpNode);

                    tmpNode->SetAttribute("type", type.c_str());

                    tinyxml2::XMLText* content = pDoc->NewText(value.second.asString().c_str());
                    tmpNode->LinkEndChild(content);
                }
            }

            // Save xml
            std::string filePathTmp = FileUtils::getInstance()->getWritablePath() + fileTmp;
            if (pDoc->SaveFile(filePathTmp.c_str()) == tinyxml2::XML_SUCCESS)
            {
                // Move tmp to original
                bRet = FileUtils::getInstance()->renameFile(FileUtils::getInstance()->getWritablePath(), fileTmp, DATA_STORE_XML_DEFAULT_FILE);
            }

            CC_SAFE_DELETE(pDoc);

        } while (0);        

        return bRet;
    }
private:

    std::string GetValueType(const Value& value)
    {
        switch (value.getType())
        {
        case Value::Type::STRING:
            return "str";
            break;
        case Value::Type::INTEGER:
            return "int";
            break;
        case Value::Type::FLOAT:
            return "float";
            break;
        case Value::Type::DOUBLE:
            return "double";
            break;
        case Value::Type::BOOLEAN:
            return "bool";
            break;
        default:
            return "";
            break;
        }
    }

    Value::Type GetType(const std::string& valueType)
    {
        if (valueType == "int")
        {
            return Value::Type::INTEGER;
        }
        else if (valueType == "float")
        {
            return Value::Type::FLOAT;
        }
        else if (valueType == "double")
        {
            return Value::Type::DOUBLE;
        }
        else if (valueType == "bool")
        {
            return Value::Type::BOOLEAN;
        }
        else
        {
            return Value::Type::STRING;
        }
    }
};

DataStoreDelegate* UserDefaultData::getDefaultXmlDataStore()
{
    static DataStoreXml dataStoreXml;
    return &dataStoreXml;
}

bool UserDefaultData::getBoolForKey(const char* key, bool defaultValue)
{
    // Load data, if not loaded
    checkLoaded();

    auto iter = _valueMap.find(key);
    if (iter == _valueMap.end())
    {
        // Add to store, if not found
        auto ret = _valueMap.insert(std::make_pair(key, Value(defaultValue)));
        iter = ret.first;
    }
    else if (iter->second.getType() != Value::Type::BOOLEAN)
    {
        // Correct Value type, if not equal
        iter->second = iter->second.asBool();
    }

    return iter->second.asBool();
}

int UserDefaultData::getIntegerForKey(const char* key, int defaultValue)
{
    // Load data, if not loaded
    checkLoaded();

    auto iter = _valueMap.find(key);
    if (iter == _valueMap.end())
    {
        // Add to store, if not found
        auto ret = _valueMap.insert(std::make_pair(key, Value(defaultValue)));
        iter = ret.first;
    }
    else if (iter->second.getType() != Value::Type::INTEGER)
    {
        // Correct Value type, if not equal
        iter->second = iter->second.asInt();
    }

    return iter->second.asInt();
}

float UserDefaultData::getFloatForKey(const char* key, float defaultValue)
{
    // Load data, if not loaded
    checkLoaded();

    auto iter = _valueMap.find(key);
    if (iter == _valueMap.end())
    {
        // Add to store, if not found
        auto ret = _valueMap.insert(std::make_pair(key, Value(defaultValue)));
        iter = ret.first;
    }
    else if (iter->second.getType() != Value::Type::FLOAT)
    {
        // Correct Value type, if not equal
        iter->second = iter->second.asFloat();
    }

    return iter->second.asFloat();
}

double UserDefaultData::getDoubleForKey(const char* key, double defaultValue)
{
    // Load data, if not loaded
    checkLoaded();

    auto iter = _valueMap.find(key);
    if (iter == _valueMap.end())
    {
        // Add to store, if not found
        auto ret = _valueMap.insert(std::make_pair(key, Value(defaultValue)));
        iter = ret.first;
    }
    else if (iter->second.getType() != Value::Type::DOUBLE)
    {
        // Correct Value type, if not equal
        iter->second = iter->second.asDouble();
    }

    return iter->second.asDouble();
}

std::string UserDefaultData::getStringForKey(const char* key, const std::string & defaultValue)
{
    // Load data, if not loaded
    checkLoaded();

    auto iter = _valueMap.find(key);
    if (iter == _valueMap.end())
    {
        // Add to store, if not found
        auto ret = _valueMap.insert(std::make_pair(key, Value(defaultValue)));
        iter = ret.first;
    }

    return iter->second.asString();
}

cocos2d::Data UserDefaultData::getDataForKey(const char* key, const Data& defaultValue)
{
    // Load data, if not loaded
    checkLoaded();

    auto iter = _valueMap.find(key);
    if (iter == _valueMap.end())
    {
        // Add to store, if not found
        return defaultValue;
    }

    unsigned char * decodedData = nullptr;
    string dataString = iter->second.asString();
    int decodedDataLen = base64Decode((unsigned char*)dataString.c_str(), (unsigned int)dataString.length(), &decodedData);

    if (decodedData)
    {
        Data data;
        data.fastSet(decodedData, decodedDataLen);
        return data;
    }
    else
    {
        return Data::Null;
    }
}

void UserDefaultData::setBoolForKey(const char* key, bool value)
{
    // Load data, if not loaded
    checkLoaded();

    _valueMap[key] = value;
}

void UserDefaultData::setIntegerForKey(const char* key, int value)
{
    // Load data, if not loaded
    checkLoaded();

    _valueMap[key] = value;
}

void UserDefaultData::setFloatForKey(const char* key, float value)
{
    // Load data, if not loaded
    checkLoaded();

    _valueMap[key] = value;
}

void UserDefaultData::setDoubleForKey(const char* key, double value)
{
    // Load data, if not loaded
    checkLoaded();

    _valueMap[key] = value;
}

void UserDefaultData::setStringForKey(const char* key, const std::string & value)
{
    // Load data, if not loaded
    checkLoaded();

    _valueMap[key] = value;
}

void UserDefaultData::setDataForKey(const char* key, const Data& value)
{
    char *encodedData = 0;

    base64Encode(value.getBytes(), static_cast<unsigned int>(value.getSize()), &encodedData);

    setStringForKey(key, encodedData);

    if (encodedData)
        free(encodedData);
}

void UserDefaultData::setDataStoreDelegate(DataStoreDelegate* delegate)
{
    makeCurrentUserDefault();

    _dataStore = delegate;
}


NS_CC_END
