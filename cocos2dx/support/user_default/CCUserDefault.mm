/****************************************************************************
 Copyright (c) 2013 cocos2d-x.org
 
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

#import "CCUserDefault.h"
#import <string>
#import "platform/CCFileUtils.h"
#import "../tinyxml2/tinyxml2.h"
#import "platform/CCPlatformConfig.h"
#import "platform/CCPlatformMacros.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)


#define XML_FILE_NAME "UserDefault.xml"

// root name of xml
#define USERDEFAULT_ROOT_NAME    "userDefaultRoot"

#define KEEP_COMPATABILITY

using namespace std;

NS_CC_BEGIN

/**
 * implements of CCUserDefault
 */

CCUserDefault* CCUserDefault::m_spUserDefault = 0;
string CCUserDefault::m_sFilePath = string("");
bool CCUserDefault::m_sbIsFilePathInitialized = false;

#ifdef KEEP_COMPATABILITY
static tinyxml2::XMLElement* getXMLNodeForKey(const char* pKey, tinyxml2::XMLDocument **doc)
{
    tinyxml2::XMLElement* curNode = NULL;
    tinyxml2::XMLElement* rootNode = NULL;
    
    if (! CCUserDefault::isXMLFileExist())
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
		const char* pXmlBuffer = (const char*)CCFileUtils::sharedFileUtils()->getFileData(CCUserDefault::sharedUserDefault()->getXMLFilePath().c_str(), "rb", &nSize);
		//const char* pXmlBuffer = (const char*)data.getBuffer();
		if(NULL == pXmlBuffer)
		{
            NSLog(@"can not read xml file");
			break;
		}
		xmlDoc->Parse(pXmlBuffer);
        delete[] pXmlBuffer;
		// get root node
		rootNode = xmlDoc->RootElement();
		if (NULL == rootNode)
		{
            NSLog(@"read root node error");
			break;
		}
		// find the node
		curNode = rootNode->FirstChildElement();
        if (!curNode)
        {
            // There is not xml node, delete xml file.
            remove(CCUserDefault::sharedUserDefault()->getXMLFilePath().c_str());
            
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
        doc->SaveFile(CCUserDefault::sharedUserDefault()->getXMLFilePath().c_str());
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
 * If the user invoke delete CCUserDefault::sharedUserDefault(), should set m_spUserDefault
 * to null to avoid error when he invoke CCUserDefault::sharedUserDefault() later.
 */
CCUserDefault::~CCUserDefault()
{
	CC_SAFE_DELETE(m_spUserDefault);
    m_spUserDefault = NULL;
}

CCUserDefault::CCUserDefault()
{
	m_spUserDefault = NULL;
}

void CCUserDefault::purgeSharedUserDefault()
{
    m_spUserDefault = NULL;
}

bool CCUserDefault::getBoolForKey(const char* pKey)
{
    return getBoolForKey(pKey, false);
}

bool CCUserDefault::getBoolForKey(const char* pKey, bool defaultValue)
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
    
    bool ret = defaultValue;
    
    NSNumber *value = [[NSUserDefaults standardUserDefaults] objectForKey:[NSString stringWithUTF8String:pKey]];
    if (value)
    {
        ret = [value boolValue];
    }
    
    return ret;
}

int CCUserDefault::getIntegerForKey(const char* pKey)
{
    return getIntegerForKey(pKey, 0);
}

int CCUserDefault::getIntegerForKey(const char* pKey, int defaultValue)
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
    
    int ret = defaultValue;
    
    NSNumber *value = [[NSUserDefaults standardUserDefaults] objectForKey:[NSString stringWithUTF8String:pKey]];
    if (value)
    {
        ret = [value intValue];
    }
    
    return ret;
}

float CCUserDefault::getFloatForKey(const char* pKey)
{
    return getFloatForKey(pKey, 0);
}

float CCUserDefault::getFloatForKey(const char* pKey, float defaultValue)
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
    
    float ret = defaultValue;
    
    NSNumber *value = [[NSUserDefaults standardUserDefaults] objectForKey:[NSString stringWithUTF8String:pKey]];
    if (value)
    {
        ret = [value floatValue];
    }
    
    return ret;
}

double  CCUserDefault::getDoubleForKey(const char* pKey)
{
    return getDoubleForKey(pKey, 0);
}

double CCUserDefault::getDoubleForKey(const char* pKey, double defaultValue)
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
    
	double ret = defaultValue;
    
    NSNumber *value = [[NSUserDefaults standardUserDefaults] objectForKey:[NSString stringWithUTF8String:pKey]];
    if (value)
    {
        ret = [value doubleValue];
    }
    
    return ret;
}

std::string CCUserDefault::getStringForKey(const char* pKey)
{
    return getStringForKey(pKey, "");
}

string CCUserDefault::getStringForKey(const char* pKey, const std::string & defaultValue)
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
    
    NSString *str = [[NSUserDefaults standardUserDefaults] stringForKey:[NSString stringWithUTF8String:pKey]];
    if (! str)
    {
        return defaultValue;
    }
    else
    {
        return [str UTF8String];
    }
}

void CCUserDefault::setBoolForKey(const char* pKey, bool value)
{
#ifdef KEEP_COMPATABILITY
    deleteNodeByKey(pKey);
#endif
    
    [[NSUserDefaults standardUserDefaults] setObject:[NSNumber numberWithBool:value] forKey:[NSString stringWithUTF8String:pKey]];
}

void CCUserDefault::setIntegerForKey(const char* pKey, int value)
{
#ifdef KEEP_COMPATABILITY
    deleteNodeByKey(pKey);
#endif
    
    [[NSUserDefaults standardUserDefaults] setObject:[NSNumber numberWithInt:value] forKey:[NSString stringWithUTF8String:pKey]];
}

void CCUserDefault::setFloatForKey(const char* pKey, float value)
{
#ifdef KEEP_COMPATABILITY
    deleteNodeByKey(pKey);
#endif
    
    [[NSUserDefaults standardUserDefaults] setObject:[NSNumber numberWithFloat:value] forKey:[NSString stringWithUTF8String:pKey]];
}

void CCUserDefault::setDoubleForKey(const char* pKey, double value)
{
#ifdef KEEP_COMPATABILITY
    deleteNodeByKey(pKey);
#endif
    
    [[NSUserDefaults standardUserDefaults] setObject:[NSNumber numberWithDouble:value] forKey:[NSString stringWithUTF8String:pKey]];
}

void CCUserDefault::setStringForKey(const char* pKey, const std::string & value)
{
#ifdef KEEP_COMPATABILITY
    deleteNodeByKey(pKey);
#endif
    
    [[NSUserDefaults standardUserDefaults] setObject:[NSString stringWithUTF8String:value.c_str()] forKey:[NSString stringWithUTF8String:pKey]];
}

CCUserDefault* CCUserDefault::sharedUserDefault()
{
#ifdef KEEP_COMPATABILITY
    initXMLFilePath();
#endif
    
    if (! m_spUserDefault)
    {
        m_spUserDefault = new CCUserDefault();
    }
    
    return m_spUserDefault;
}

bool CCUserDefault::isXMLFileExist()
{
    FILE *fp = fopen(m_sFilePath.c_str(), "r");
	bool bRet = false;
    
	if (fp)
	{
		bRet = true;
		fclose(fp);
	}
    
	return bRet;
}

void CCUserDefault::initXMLFilePath()
{
#ifdef KEEP_COMPATABILITY
    if (! m_sbIsFilePathInitialized)
    {
        // xml file is stored in cache directory before 2.1.2
        NSArray *paths = NSSearchPathForDirectoriesInDomains(NSCachesDirectory, NSUserDomainMask, YES);
        NSString *documentsDirectory = [paths objectAtIndex:0];
        m_sFilePath = [documentsDirectory UTF8String];
        m_sFilePath.append("/");
        
        m_sFilePath +=  XML_FILE_NAME;
        m_sbIsFilePathInitialized = true;
    }
#endif
}

// create new xml file
bool CCUserDefault::createXMLFile()
{
    return false;
}

const string& CCUserDefault::getXMLFilePath()
{
    return m_sFilePath;
}

void CCUserDefault::flush()
{
    [[NSUserDefaults standardUserDefaults] synchronize];
}


NS_CC_END

#endif // (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
