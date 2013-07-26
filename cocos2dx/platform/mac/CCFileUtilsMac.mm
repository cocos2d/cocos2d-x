/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.

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
#include "CCFileUtilsMac.h"
#import <Foundation/Foundation.h>
#include <string>
#include <stack>
#include "cocoa/CCString.h"
#include "CCFileUtils.h"
#include "CCDirector.h"
#include "CCSAXParser.h"
#include "CCDictionary.h"
#include "support/zip_support/unzip.h"

NS_CC_BEGIN

static void addValueToDict(id key, id value, Dictionary* pDict);
static void addObjectToNSDict(const char*key, Object* object, NSMutableDictionary *dict);

static void addItemToArray(id item, Array *pArray)
{
    // add string value into array
    if ([item isKindOfClass:[NSString class]]) {
        String* pValue = new String([item UTF8String]);
        
        pArray->addObject(pValue);
        pValue->release();
        return;
    }
    
    // add number value into array(such as int, float, bool and so on)
    if ([item isKindOfClass:[NSNumber class]]) {
        NSString* pStr = [item stringValue];
        String* pValue = new String([pStr UTF8String]);
        
        pArray->addObject(pValue);
        pValue->release();
        return;
    }
    
    // add dictionary value into array
    if ([item isKindOfClass:[NSDictionary class]]) {
        Dictionary* pDictItem = new Dictionary();
        for (id subKey in [item allKeys]) {
            id subValue = [item objectForKey:subKey];
            addValueToDict(subKey, subValue, pDictItem);
        }
        pArray->addObject(pDictItem);
        pDictItem->release();
        return;
    }
    
    // add array value into array
    if ([item isKindOfClass:[NSArray class]]) {
        Array *pArrayItem = new Array();
        pArrayItem->init();
        for (id subItem in item) {
            addItemToArray(subItem, pArrayItem);
        }
        pArray->addObject(pArrayItem);
        pArrayItem->release();
        return;
    }
}

static void addObjectToNSArray(Object *object, NSMutableArray *array)
{
    // add string into array
    if (String *ccString = dynamic_cast<String *>(object)) {
        NSString *strElement = [NSString stringWithCString:ccString->getCString() encoding:NSUTF8StringEncoding];
        [array addObject:strElement];
        return;
    }
    
    // add array into array
    if (Array *ccArray = dynamic_cast<Array *>(object)) {
        NSMutableArray *arrElement = [NSMutableArray array];
        Object *element = NULL;
        CCARRAY_FOREACH(ccArray, element)
        {
            addObjectToNSArray(element, arrElement);
        }
        [array addObject:arrElement];
        return;
    }
    
    // add dictionary value into array
    if (Dictionary *ccDict = dynamic_cast<Dictionary *>(object)) {
        NSMutableDictionary *dictElement = [NSMutableDictionary dictionary];
        DictElement *element = NULL;
        CCDICT_FOREACH(ccDict, element)
        {
            addObjectToNSDict(element->getStrKey(), element->getObject(), dictElement);
        }
        [array addObject:dictElement];
    }
    
}

static void addValueToDict(id key, id value, Dictionary* pDict)
{
    // the key must be a string
    CCASSERT([key isKindOfClass:[NSString class]], "The key should be a string!");
    std::string pKey = [key UTF8String];
    
    // the value is a new dictionary
    if ([value isKindOfClass:[NSDictionary class]]) {
        Dictionary* pSubDict = new Dictionary();
        for (id subKey in [value allKeys]) {
            id subValue = [value objectForKey:subKey];
            addValueToDict(subKey, subValue, pSubDict);
        }
        pDict->setObject(pSubDict, pKey.c_str());
        pSubDict->release();
        return;
    }
    
    // the value is a string
    if ([value isKindOfClass:[NSString class]]) {
        String* pValue = new String([value UTF8String]);
        
        pDict->setObject(pValue, pKey.c_str());
        pValue->release();
        return;
    }
    
    // the value is a number
    if ([value isKindOfClass:[NSNumber class]]) {
        NSString* pStr = [value stringValue];
        String* pValue = new String([pStr UTF8String]);
        
        pDict->setObject(pValue, pKey.c_str());
        pValue->release();
        return;
    }
    
    // the value is a array
    if ([value isKindOfClass:[NSArray class]]) {
        Array *pArray = new Array();
        pArray->init();
        for (id item in value) {
            addItemToArray(item, pArray);
        }
        pDict->setObject(pArray, pKey.c_str());
        pArray->release();
        return;
    }
}

static void addObjectToNSDict(const char * key, Object* object, NSMutableDictionary *dict)
{
    NSString *NSkey = [NSString stringWithCString:key encoding:NSUTF8StringEncoding];
    
    // the object is a Dictionary
    if (Dictionary *ccDict = dynamic_cast<Dictionary *>(object)) {
        NSMutableDictionary *dictElement = [NSMutableDictionary dictionary];
        DictElement *element = NULL;
        CCDICT_FOREACH(ccDict, element)
        {
            addObjectToNSDict(element->getStrKey(), element->getObject(), dictElement);
        }
        
        [dict setObject:dictElement forKey:NSkey];
        return;
    }
    
    // the object is a String
    if (String *element = dynamic_cast<String *>(object)) {
        NSString *strElement = [NSString stringWithCString:element->getCString() encoding:NSUTF8StringEncoding];
        [dict setObject:strElement forKey:NSkey];
        return;
    }
    
    // the object is a Array
    if (Array *ccArray = dynamic_cast<Array *>(object)) {
        NSMutableArray *arrElement = [NSMutableArray array];
        Object *element = NULL;
        CCARRAY_FOREACH(ccArray, element)
        {
            addObjectToNSArray(element, arrElement);
        }
        [dict setObject:arrElement forKey:NSkey];
        return;
    }
}

FileUtils* FileUtils::getInstance()
{
    if (s_sharedFileUtils == NULL)
    {
        s_sharedFileUtils = new FileUtilsMac();
        if(!s_sharedFileUtils->init())
        {
          delete s_sharedFileUtils;
          s_sharedFileUtils = NULL;
          CCLOG("ERROR: Could not init CCFileUtilsMac");
        }
    }
    return s_sharedFileUtils;
}


static NSFileManager* s_fileManager = [NSFileManager defaultManager];

std::string FileUtilsMac::getWritablePath()
{
    // save to document folder
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSCachesDirectory, NSUserDomainMask, YES);
    NSString *documentsDirectory = [paths objectAtIndex:0];
    std::string strRet = [documentsDirectory UTF8String];
    strRet.append("/");
    return strRet;
}

bool FileUtilsMac::isFileExist(const std::string& strFilePath)
{
    if (0 == strFilePath.length())
    {
        return false;
    }
    
    bool bRet = false;
    
    if (strFilePath[0] != '/')
    {
        std::string path = strFilePath;
        std::string file;
        size_t pos = path.find_last_of("/");
        if (pos != std::string::npos)
        {
            file = path.substr(pos+1);
            path = path.substr(0, pos+1);
            NSString* fullpath = [[NSBundle mainBundle] pathForResource:[NSString stringWithUTF8String:file.c_str()]
                                                                 ofType:nil
                                                            inDirectory:[NSString stringWithUTF8String:path.c_str()]];
            if (fullpath != nil) {
                bRet = true;
            }
        }
    }
    else
    {
        // Search path is an absolute path.
        if ([s_fileManager fileExistsAtPath:[NSString stringWithUTF8String:strFilePath.c_str()]]) {
            bRet = true;
        }
    }
    
    return bRet;
}

std::string FileUtilsMac::getFullPathForDirectoryAndFilename(const std::string& strDirectory, const std::string& strFilename)
{
    if (strDirectory[0] != '/')
    {
        NSString* fullpath = [[NSBundle mainBundle] pathForResource:[NSString stringWithUTF8String:strFilename.c_str()]
                                                             ofType:nil
                                                        inDirectory:[NSString stringWithUTF8String:strDirectory.c_str()]];
        if (fullpath != nil) {
            return [fullpath UTF8String];
        }
    }
    else
    {
        std::string fullPath = strDirectory+strFilename;
        // Search path is an absolute path.
        if ([s_fileManager fileExistsAtPath:[NSString stringWithUTF8String:fullPath.c_str()]]) {
            return fullPath;
        }
    }
    return "";
}

bool FileUtilsMac::isAbsolutePath(const std::string& strPath)
{
    NSString* path = [NSString stringWithUTF8String:strPath.c_str()];
    return [path isAbsolutePath] ? true : false;
}

Dictionary* FileUtilsMac::createDictionaryWithContentsOfFile(const std::string& filename)
{
    std::string fullPath = FileUtils::getInstance()->fullPathForFilename(filename.c_str());
    NSString* pPath = [NSString stringWithUTF8String:fullPath.c_str()];
    NSDictionary* pDict = [NSDictionary dictionaryWithContentsOfFile:pPath];
    
    Dictionary* pRet = new Dictionary();
    for (id key in [pDict allKeys]) {
        id value = [pDict objectForKey:key];
        addValueToDict(key, value, pRet);
    }
    
    return pRet;
}

bool FileUtilsMac::writeToFile(Dictionary *dict, const std::string &fullPath)
{
    CCLOG("iOS||Mac Dictionary %d write to file %s", dict->_ID, fullPath.c_str());
    NSMutableDictionary *nsDict = [NSMutableDictionary dictionary];
    
    DictElement *element = NULL;
    CCDICT_FOREACH(dict, element)
    {
        addObjectToNSDict(element->getStrKey(), element->getObject(), nsDict);
    }
    
    NSString *file = [NSString stringWithUTF8String:fullPath.c_str()];
    // do it atomically
    return [nsDict writeToFile:file atomically:YES];
}

Array* FileUtilsMac::createArrayWithContentsOfFile(const std::string& filename)
{
    //    NSString* pPath = [NSString stringWithUTF8String:pFileName];
    //    NSString* pathExtension= [pPath pathExtension];
    //    pPath = [pPath stringByDeletingPathExtension];
    //    pPath = [[NSBundle mainBundle] pathForResource:pPath ofType:pathExtension];
    //    fixing cannot read data using Array::createWithContentsOfFile
    std::string fullPath = FileUtils::getInstance()->fullPathForFilename(filename.c_str());
    NSString* pPath = [NSString stringWithUTF8String:fullPath.c_str()];
    NSArray* pArray = [NSArray arrayWithContentsOfFile:pPath];
    
    Array* pRet = new Array();
    for (id value in pArray) {
        addItemToArray(value, pRet);
    }
    
    return pRet;
}


NS_CC_END

