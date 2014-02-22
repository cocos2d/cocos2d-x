/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2014 Chukong Technologies Inc.

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
#import <Foundation/Foundation.h>

#include <string>
#include <stack>
#include "CCString.h"
#include "CCFileUtils.h"
#include "CCDirector.h"
#include "CCSAXParser.h"
#include "CCDictionary.h"
#include "unzip.h"

#include "CCFileUtilsApple.h"

NS_CC_BEGIN

static void addValueToDict(id nsKey, id nsValue, ValueMap& dict);
static void addItemToArray(id item, ValueVector& array);

static void addObjectToNSArray(const Value& value, NSMutableArray *array);
static void addObjectToNSDict(const std::string& key, const Value& value, NSMutableDictionary *dict);

static NSObject *convertValueToNSObject(const Value &value)
{
    // add string into array
    if (value.getType() == Value::Type::STRING)
    {
        return [NSString stringWithCString:value.asString().c_str() encoding:NSUTF8StringEncoding];
    }
    
    // add array into array
    if (value.getType() == Value::Type::VECTOR)
    {
        NSMutableArray *element = [NSMutableArray array];
        
        const ValueVector &valueArray = value.asValueVector();
        for (const auto &e : valueArray)
        {
            addObjectToNSArray(e, element);
        }
        
        return element;
    }
    
    // add dictionary value into array
    if (value.getType() == Value::Type::MAP)
    {
        NSMutableDictionary *element = [NSMutableDictionary dictionary];
        
        const auto &valueDict = value.asValueMap();
        for (const auto &dictEntry : valueDict)
        {
            addObjectToNSDict(dictEntry.first, dictEntry.second, element);
        }
        
        return element;
    }
    
    if (value.getType() == Value::Type::BYTE)
    {
        return [NSNumber numberWithChar:value.asByte()];
    }
    
    if (value.getType() == Value::Type::DOUBLE)
    {
        return [NSNumber numberWithDouble:value.asDouble()];
    }
    
    if (value.getType() == Value::Type::FLOAT)
    {
        return [NSNumber numberWithFloat:value.asFloat()];
    }
    
    if (value.getType() == Value::Type::INTEGER)
    {
        return [NSNumber numberWithInt:value.asInt()];
    }
    
    if (value.getType() == Value::Type::BOOLEAN)
    {
        return [NSNumber numberWithBool:value.asBool()];
    }

    return nil;
}

static Value convertNSObjectToValue(id object) {
    // add string value into array
    if ([object isKindOfClass:[NSString class]])
    {
        return Value([object UTF8String]);
    }
    
    // add number value into array(such as int, float, bool and so on)
    if ([object isKindOfClass:[NSNumber class]])
    {
        return Value([object doubleValue]);
    }
    
    // add dictionary value into array
    if ([object isKindOfClass:[NSDictionary class]])
    {
        ValueMap dict;
        for (id subKey in [object allKeys])
        {
            id subValue = [object objectForKey:subKey];
            addValueToDict(subKey, subValue, dict);
        }
        
        return Value(dict);
    }
    
    // add array value into array
    if ([object isKindOfClass:[NSArray class]])
    {
        ValueVector subArray;
        for (id subItem in object)
        {
            addItemToArray(subItem, subArray);
        }
        return Value(subArray);
    }

    return Value::Null;
}

static void addItemToArray(id item, ValueVector& array)
{
    array.push_back(convertNSObjectToValue(item));
}

static void addValueToDict(id nsKey, id nsValue, ValueMap& dict)
{
    // the key must be a string
    CCASSERT([nsKey isKindOfClass:[NSString class]], "The key should be a string!");
    std::string key = [nsKey UTF8String];
    dict[key] = convertNSObjectToValue(nsValue);
}

static void addObjectToNSArray(const Value& value, NSMutableArray *array)
{
    NSObject *nsObject = convertValueToNSObject(value);
    [array addObject:nsObject];
}

static void addObjectToNSDict(const std::string& key, const Value& value, NSMutableDictionary *dict)
{
    NSString *nsKey = [NSString stringWithCString:key.c_str() encoding:NSUTF8StringEncoding];
    NSObject *nsObject = convertValueToNSObject(value);
    [dict setObject:nsObject forKey:nsKey];
}


#pragma mark - FileUtils

static NSFileManager* s_fileManager = [NSFileManager defaultManager];

FileUtils* FileUtils::getInstance()
{
    if (s_sharedFileUtils == nullptr)
    {
        s_sharedFileUtils = new FileUtilsApple();
        if(!s_sharedFileUtils->init())
        {
          delete s_sharedFileUtils;
          s_sharedFileUtils = nullptr;
          CCLOG("ERROR: Could not init CCFileUtilsApple");
        }
    }
    return s_sharedFileUtils;
}


std::string FileUtilsApple::getWritablePath() const
{
    // save to document folder
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    NSString *documentsDirectory = [paths objectAtIndex:0];
    std::string strRet = [documentsDirectory UTF8String];
    strRet.append("/");
    return strRet;
}

bool FileUtilsApple::isFileExist(const std::string& filePath) const
{
    if(filePath.length() == 0)
    {
        return false;
    }

    bool ret = false;
    
    if (filePath[0] != '/')
    {
        std::string path;
        std::string file;
        size_t pos = filePath.find_last_of("/");
        if (pos != std::string::npos)
        {
            file = filePath.substr(pos+1);
            path = filePath.substr(0, pos+1);
        }
        else
        {
            file = filePath;
        }
        
        NSString* fullpath = [[NSBundle mainBundle] pathForResource:[NSString stringWithUTF8String:file.c_str()]
                                                             ofType:nil
                                                        inDirectory:[NSString stringWithUTF8String:path.c_str()]];
        if (fullpath != nil) {
            ret = true;
        }
    }
    else
    {
        // Search path is an absolute path.
        if ([s_fileManager fileExistsAtPath:[NSString stringWithUTF8String:filePath.c_str()]]) {
            ret = true;
        }
    }
    
    return ret;
}

std::string FileUtilsApple::getFullPathForDirectoryAndFilename(const std::string& directory, const std::string& filename)
{
    if (directory[0] != '/')
    {
        NSString* fullpath = [[NSBundle mainBundle] pathForResource:[NSString stringWithUTF8String:filename.c_str()]
                                                             ofType:nil
                                                        inDirectory:[NSString stringWithUTF8String:directory.c_str()]];
        if (fullpath != nil) {
            return [fullpath UTF8String];
        }
    }
    else
    {
        std::string fullPath = directory+filename;
        // Search path is an absolute path.
        if ([s_fileManager fileExistsAtPath:[NSString stringWithUTF8String:fullPath.c_str()]]) {
            return fullPath;
        }
    }
    return "";
}

ValueMap FileUtilsApple::getValueMapFromFile(const std::string& filename)
{
    std::string fullPath = fullPathForFilename(filename);
    NSString* path = [NSString stringWithUTF8String:fullPath.c_str()];
    NSDictionary* dict = [NSDictionary dictionaryWithContentsOfFile:path];
    
    ValueMap ret;
    
    if (dict != nil)
    {
        for (id key in [dict allKeys])
        {
            id value = [dict objectForKey:key];
            addValueToDict(key, value, ret);
        }
    }
    return ret;
}

bool FileUtilsApple::writeToFile(ValueMap& dict, const std::string &fullPath)
{
    //CCLOG("iOS||Mac Dictionary %d write to file %s", dict->_ID, fullPath.c_str());
    NSMutableDictionary *nsDict = [NSMutableDictionary dictionary];
    
    for (auto iter = dict.begin(); iter != dict.end(); ++iter)
    {
        addObjectToNSDict(iter->first, iter->second, nsDict);
    }
    
    NSString *file = [NSString stringWithUTF8String:fullPath.c_str()];
    // do it atomically
    [nsDict writeToFile:file atomically:YES];
    
    return true;
}

ValueVector FileUtilsApple::getValueVectorFromFile(const std::string& filename)
{
    //    NSString* pPath = [NSString stringWithUTF8String:pFileName];
    //    NSString* pathExtension= [pPath pathExtension];
    //    pPath = [pPath stringByDeletingPathExtension];
    //    pPath = [[NSBundle mainBundle] pathForResource:pPath ofType:pathExtension];
    //    fixing cannot read data using Array::createWithContentsOfFile
    std::string fullPath = fullPathForFilename(filename);
    NSString* path = [NSString stringWithUTF8String:fullPath.c_str()];
    NSArray* array = [NSArray arrayWithContentsOfFile:path];
    
    ValueVector ret;
    
    for (id value in array)
    {
        addItemToArray(value, ret);
    }
    
    return ret;
}

NS_CC_END

