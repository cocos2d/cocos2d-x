/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org

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
#include "CCUserDefault.h"
#include "platform/CCPlatformConfig.h"
#include "platform/CCCommon.h"
#include "support/base64.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "platform/android/jni/Java_org_cocos2dx_lib_Cocos2dxHelper.h"

// root name of xml
#define USERDEFAULT_ROOT_NAME    "userDefaultRoot"

#define KEEP_COMPATABILITY

#define XML_FILE_NAME "UserDefault.xml"

#ifdef KEEP_COMPATABILITY
#include "platform/CCFileUtils.h"
#include "../tinyxml2/tinyxml2.h"
#endif

using namespace std;

NS_CC_BEGIN

/**
 * implements of UserDefault
 */

UserDefault* UserDefault::_userDefault = 0;
string UserDefault::_filePath = string("");
bool UserDefault::_isFilePathInitialized = false;

#ifdef KEEP_COMPATABILITY
static tinyxml2::XMLElement* getXMLNodeForKey(const char* pKey, tinyxml2::XMLDocument **doc)
{
    tinyxml2::XMLElement* curNode = NULL;
    tinyxml2::XMLElement* rootNode = NULL;
    
    if (! UserDefault::isXMLFileExist())
    {
        return NULL;
    }
    
    // check the key value
    if (! pKey)
    {
        return NULL;
    }
    
    do
    {
        tinyxml2::XMLDocument* xmlDoc = new tinyxml2::XMLDocument();
        *doc = xmlDoc;
        unsigned long nSize;
        const char* pXmlBuffer = (const char*)FileUtils::getInstance()->getFileData(UserDefault::getInstance()->getXMLFilePath().c_str(), "rb", &nSize);
        //const char* pXmlBuffer = (const char*)data.getBuffer();
        if(NULL == pXmlBuffer)
        {
            CCLOG("can not read xml file");
            break;
        }
        xmlDoc->Parse(pXmlBuffer);
		delete[] pXmlBuffer;
        // get root node
        rootNode = xmlDoc->RootElement();
        if (NULL == rootNode)
        {
            CCLOG("read root node error");
            break;
        }
        // find the node
        curNode = rootNode->FirstChildElement();
        if (!curNode)
        {
            // There is not xml node, delete xml file.
            remove(UserDefault::getInstance()->getXMLFilePath().c_str());
            
            return NULL;
        }
        
        while (NULL != curNode)
        {
            const char* nodeName = curNode->Value();
            if (!strcmp(nodeName, pKey))
            {
                // delete the node
                break;
            }
            
            curNode = curNode->NextSiblingElement();
        }
    } while (0);
    
    return curNode;
}

static void deleteNode(tinyxml2::XMLDocument* doc, tinyxml2::XMLElement* node)
{
    if (node)
    {
        doc->DeleteNode(node);
        doc->SaveFile(UserDefault::getInstance()->getXMLFilePath().c_str());
        delete doc;
    }
}

static void deleteNodeByKey(const char *pKey)
{
    tinyxml2::XMLDocument* doc = NULL;
    tinyxml2::XMLElement* node = getXMLNodeForKey(pKey, &doc);
    deleteNode(doc, node);
}
#endif

/**
 * If the user invoke delete UserDefault::getInstance(), should set _userDefault
 * to null to avoid error when he invoke UserDefault::getInstance() later.
 */
UserDefault::~UserDefault()
{
	CC_SAFE_DELETE(_userDefault);
    _userDefault = NULL;
}

UserDefault::UserDefault()
{
	_userDefault = NULL;
}

// XXX: deprecated
void UserDefault::purgeSharedUserDefault()
{
    UserDefault::destroyInstance();
}

void UserDefault::destroyInstance()
{
    _userDefault = NULL;
}

bool UserDefault::getBoolForKey(const char* pKey)
{
    return getBoolForKey(pKey, false);
}

bool UserDefault::getBoolForKey(const char* pKey, bool defaultValue)
{
#ifdef KEEP_COMPATABILITY
    tinyxml2::XMLDocument* doc = NULL;
    tinyxml2::XMLElement* node = getXMLNodeForKey(pKey, &doc);
    if (node)
    {
        if (node->FirstChild())
        {
            const char* value = (const char*)node->FirstChild()->Value();
            bool ret = (! strcmp(value, "true"));
            
            // set value in NSUserDefaults
            setBoolForKey(pKey, ret);
            flush();
            
            // delete xmle node
            deleteNode(doc, node);
            
            return ret;
        }
        else
        {
            // delete xmle node
            deleteNode(doc, node);
        }
    }
#endif

    return getBoolForKeyJNI(pKey, defaultValue);
}

int UserDefault::getIntegerForKey(const char* pKey)
{
    return getIntegerForKey(pKey, 0);
}

int UserDefault::getIntegerForKey(const char* pKey, int defaultValue)
{
#ifdef KEEP_COMPATABILITY
    tinyxml2::XMLDocument* doc = NULL;
    tinyxml2::XMLElement* node = getXMLNodeForKey(pKey, &doc);
    if (node)
    {
        if (node->FirstChild())
        {
            int ret = atoi((const char*)node->FirstChild()->Value());
            
            // set value in NSUserDefaults
            setIntegerForKey(pKey, ret);
            flush();
            
            // delete xmle node
            deleteNode(doc, node);
            
            return ret;
        }
        else
        {
            // delete xmle node
            deleteNode(doc, node);
        }
    }
#endif
    
	return getIntegerForKeyJNI(pKey, defaultValue);
}

float UserDefault::getFloatForKey(const char* pKey)
{
    return getFloatForKey(pKey, 0.0f);
}

float UserDefault::getFloatForKey(const char* pKey, float defaultValue)
{
#ifdef KEEP_COMPATABILITY
    tinyxml2::XMLDocument* doc = NULL;
    tinyxml2::XMLElement* node = getXMLNodeForKey(pKey, &doc);
    if (node)
    {
        if (node->FirstChild())
        {
            float ret = atof((const char*)node->FirstChild()->Value());
            
            // set value in NSUserDefaults
            setFloatForKey(pKey, ret);
            flush();
            
            // delete xmle node
            deleteNode(doc, node);
            
            return ret;
        }
        else
        {
            // delete xmle node
            deleteNode(doc, node);
        }
    }
#endif

    return getFloatForKeyJNI(pKey, defaultValue);
}

double  UserDefault::getDoubleForKey(const char* pKey)
{
    return getDoubleForKey(pKey, 0.0);
}

double UserDefault::getDoubleForKey(const char* pKey, double defaultValue)
{
#ifdef KEEP_COMPATABILITY
    tinyxml2::XMLDocument* doc = NULL;
    tinyxml2::XMLElement* node = getXMLNodeForKey(pKey, &doc);
    if (node)
    {
        if (node->FirstChild())
        {
            double ret = atof((const char*)node->FirstChild()->Value());
            
            // set value in NSUserDefaults
            setDoubleForKey(pKey, ret);
            flush();
            
            // delete xmle node
            deleteNode(doc, node);
            
            return ret;
        }
        else
        {
            // delete xmle node
            deleteNode(doc, node);
        }
    }
#endif

	return getDoubleForKeyJNI(pKey, defaultValue);
}

std::string UserDefault::getStringForKey(const char* pKey)
{
    return getStringForKey(pKey, "");
}

string UserDefault::getStringForKey(const char* pKey, const std::string & defaultValue)
{
#ifdef KEEP_COMPATABILITY
    tinyxml2::XMLDocument* doc = NULL;
    tinyxml2::XMLElement* node = getXMLNodeForKey(pKey, &doc);
    if (node)
    {
        if (node->FirstChild())
        {
            string ret = (const char*)node->FirstChild()->Value();
            
            // set value in NSUserDefaults
            setStringForKey(pKey, ret);
            flush();
            
            // delete xmle node
            deleteNode(doc, node);
            
            return ret;
        }
        else
        {
            // delete xmle node
            deleteNode(doc, node);
        }
    }
#endif

    return getStringForKeyJNI(pKey, defaultValue.c_str());
}

Data* UserDefault::getDataForKey(const char* pKey)
{
    return getDataForKey(pKey, NULL);
}

Data* UserDefault::getDataForKey(const char* pKey, Data* defaultValue)
{
#ifdef KEEP_COMPATABILITY
    tinyxml2::XMLDocument* doc = NULL;
    tinyxml2::XMLElement* node = getXMLNodeForKey(pKey, &doc);
    if (node)
    {
        if (node->FirstChild())
        {
            const char * encodedData = node->FirstChild()->Value();
            
            unsigned char * decodedData;
            int decodedDataLen = base64Decode((unsigned char*)encodedData, (unsigned int)strlen(encodedData), &decodedData);
            
            if (decodedData) {
                Data *ret = Data::create(decodedData, decodedDataLen);
                
                // set value in NSUserDefaults
                setDataForKey(pKey, ret);
                
                CC_SAFE_DELETE_ARRAY(decodedData);
                
                delete decodedData;
                
                flush();
                
                // delete xmle node
                deleteNode(doc, node);
                
                return ret;
            }
        }
        else
        {
            // delete xmle node
            deleteNode(doc, node);
        }
    }
#endif
    
    char * encodedDefaultData = NULL;
    unsigned int encodedDefaultDataLen = defaultValue ? base64Encode(defaultValue->getBytes(), defaultValue->getSize(), &encodedDefaultData) : 0;
    
    string encodedStr = getStringForKeyJNI(pKey, encodedDefaultData);

    if (encodedDefaultData) {
        delete encodedDefaultData;
    }

    CCLOG("ENCODED STRING: --%s--%d", encodedStr.c_str(), encodedStr.length());
    
    Data *ret = defaultValue;
    
    unsigned char * decodedData = NULL;
    int decodedDataLen = base64Decode((unsigned char*)encodedStr.c_str(), (unsigned int)encodedStr.length(), &decodedData);

    CCLOG("AFTER DECoDE. ret %p defaultValue %p", ret, defaultValue);
    CCLOG("DECoDED DATA: %s %d", decodedData, decodedDataLen);
    
    if (decodedData && decodedDataLen) {
        ret = Data::create(decodedData, decodedDataLen);
    }

    CCLOG("RETURNED %p!", ret);
    
    return ret;
}


void UserDefault::setBoolForKey(const char* pKey, bool value)
{
#ifdef KEEP_COMPATABILITY
    deleteNodeByKey(pKey);
#endif

    return setBoolForKeyJNI(pKey, value);
}

void UserDefault::setIntegerForKey(const char* pKey, int value)
{
#ifdef KEEP_COMPATABILITY
    deleteNodeByKey(pKey);
#endif

    return setIntegerForKeyJNI(pKey, value);
}

void UserDefault::setFloatForKey(const char* pKey, float value)
{
#ifdef KEEP_COMPATABILITY
    deleteNodeByKey(pKey);
#endif

    return setFloatForKeyJNI(pKey, value);
}

void UserDefault::setDoubleForKey(const char* pKey, double value)
{
#ifdef KEEP_COMPATABILITY
    deleteNodeByKey(pKey);
#endif

    return setDoubleForKeyJNI(pKey, value);
}

void UserDefault::setStringForKey(const char* pKey, const std::string & value)
{
#ifdef KEEP_COMPATABILITY
    deleteNodeByKey(pKey);
#endif

    return setStringForKeyJNI(pKey, value.c_str());
}

void UserDefault::setDataForKey(const char* pKey, const Data& value)
{
#ifdef KEEP_COMPATABILITY
    deleteNodeByKey(pKey);
#endif
    
    CCLOG("SET DATA FOR KEY: --%s--%d", value.getBytes(), value.getSize());
    char * encodedData = NULL;
    unsigned int encodedDataLen = base64Encode(value.getBytes(), value.getSize(), &encodedData);

    CCLOG("SET DATA ENCODED: --%s", encodedData);
    
    return setStringForKeyJNI(pKey, encodedData);
    
    if (encodedData) {
        delete encodedData;
    }
}

// XXX: deprecated
UserDefault* UserDefault::sharedUserDefault()
{
    return UserDefault::getInstance();
}

UserDefault* UserDefault::getInstance()
{
#ifdef KEEP_COMPATABILITY
    initXMLFilePath();
#endif
    
    if (! _userDefault)
    {
        _userDefault = new UserDefault();
    }

    return _userDefault;
}

bool UserDefault::isXMLFileExist()
{
    FILE *fp = fopen(_filePath.c_str(), "r");
    bool bRet = false;
    
    if (fp)
    {
        bRet = true;
        fclose(fp);
    }
    
    return bRet;
}

void UserDefault::initXMLFilePath()
{
#ifdef KEEP_COMPATABILITY
    if (! _isFilePathInitialized)
    {
        // UserDefault.xml is stored in /data/data/<package-path>/ before v2.1.2
        _filePath += "/data/data/" + getPackageNameJNI() + "/" + XML_FILE_NAME;
        _isFilePathInitialized = true;
    }
#endif
}

// create new xml file
bool UserDefault::createXMLFile()
{
    return false;
}

const string& UserDefault::getXMLFilePath()
{
    return _filePath;
}

void UserDefault::flush()
{
}

NS_CC_END

#endif // (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
