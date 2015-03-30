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

#include "CCFileUtils-apple.h"

#include <string>
#include <stack>

#include "base/CCDirector.h"
#include "deprecated/CCString.h"
#include "deprecated/CCDictionary.h"
#include "platform/CCFileUtils.h"
#include "platform/CCSAXParser.h"

NS_CC_BEGIN

static void addValueToDict(id nsKey, id nsValue, ValueMap& dict);
static void addObjectToNSDict(const std::string& key, const Value& value, NSMutableDictionary *dict);

static void addItemToArray(id item, ValueVector& array)
{
    // add string value into array
    if ([item isKindOfClass:[NSString class]])
    {
        array.push_back(Value([item UTF8String]));
        return;
    }

    // add number value into array(such as int, float, bool and so on)
    // the value is a number
    if ([item isKindOfClass:[NSNumber class]])
    {
        NSNumber* num = item;
        const char* numType = [num objCType];
        if(num == (void*)kCFBooleanFalse || num == (void*)kCFBooleanTrue)
        {
            array.push_back(Value([num boolValue]));
        }
        else if(strcmp(numType, @encode(float)) == 0)
        {
            array.push_back(Value([num floatValue]));
        }
        else if(strcmp(numType, @encode(double)) == 0)
        {
            array.push_back(Value([num doubleValue]));
        }
        else{
            array.push_back(Value([num intValue]));
        }
        return;
    }


    // add dictionary value into array
    if ([item isKindOfClass:[NSDictionary class]])
    {
        ValueMap dict;
        for (id subKey in [item allKeys])
        {
            id subValue = [item objectForKey:subKey];
            addValueToDict(subKey, subValue, dict);
        }

        array.push_back(Value(dict));
        return;
    }

    // add array value into array
    if ([item isKindOfClass:[NSArray class]])
    {
        ValueVector subArray;
        for (id subItem in item)
        {
            addItemToArray(subItem, subArray);
        }
        array.push_back(Value(subArray));
        return;
    }
}

static void addObjectToNSArray(const Value& value, NSMutableArray *array)
{
    // add string into array
    if (value.getType() == Value::Type::STRING)
    {
        NSString *element = [NSString stringWithCString:value.asString().c_str() encoding:NSUTF8StringEncoding];
        [array addObject:element];
        return;
    }

    //add float  into array
    if (value.getType() == Value::Type::FLOAT) {
        NSNumber *number = [NSNumber numberWithFloat:value.asFloat()];
        [array addObject:number];
    }

    //add double into array
    if (value.getType() == Value::Type::DOUBLE) {
        NSNumber *number = [NSNumber numberWithDouble:value.asDouble()];
        [array addObject:number];
    }

    //add boolean into array
    if (value.getType() == Value::Type::BOOLEAN) {
        NSNumber *element = [NSNumber numberWithBool:value.asBool()];
        [array addObject:element];
    }

    if (value.getType() == Value::Type::INTEGER) {
        NSNumber *element = [NSNumber numberWithInt:value.asInt()];
        [array addObject:element];
    }

    //todo: add date and data support

    // add array into array
    if (value.getType() == Value::Type::VECTOR)
    {
        NSMutableArray *element = [NSMutableArray array];

        ValueVector valueArray = value.asValueVector();

        for (const auto &e : valueArray)
        {
            addObjectToNSArray(e, element);
        }

        [array addObject:element];
        return;
    }

    // add dictionary value into array
    if (value.getType() == Value::Type::MAP)
    {
        NSMutableDictionary *element = [NSMutableDictionary dictionary];

        auto valueDict = value.asValueMap();
        for (auto iter = valueDict.begin(); iter != valueDict.end(); ++iter)
        {
            addObjectToNSDict(iter->first, iter->second, element);
        }

        [array addObject:element];
    }
}

static void addValueToDict(id nsKey, id nsValue, ValueMap& dict)
{
    // the key must be a string
    CCASSERT([nsKey isKindOfClass:[NSString class]], "The key should be a string!");
    std::string key = [nsKey UTF8String];

    // the value is a string
    if ([nsValue isKindOfClass:[NSString class]])
    {
        dict[key] = Value([nsValue UTF8String]);
        return;
    }

    // the value is a number
    if ([nsValue isKindOfClass:[NSNumber class]])
    {
        NSNumber* num = nsValue;
        const char* numType = [num objCType];
        if(num == (void*)kCFBooleanFalse || num == (void*)kCFBooleanTrue)
        {
             dict[key] = Value([num boolValue]);
        }
        else if(strcmp(numType, @encode(float)) == 0)
        {
            dict[key] = Value([num floatValue]);
        }
        else if(strcmp(numType, @encode(double)) == 0)
        {
            dict[key] = Value([num doubleValue]);
        }
        else{
            dict[key] = Value([num intValue]);
        }
        return;
    }


    // the value is a new dictionary
    if ([nsValue isKindOfClass:[NSDictionary class]])
    {
        ValueMap subDict;

        for (id subKey in [nsValue allKeys])
        {
            id subValue = [nsValue objectForKey:subKey];
            addValueToDict(subKey, subValue, subDict);
        }
        dict[key] = Value(subDict);
        return;
    }

    // the value is a array
    if ([nsValue isKindOfClass:[NSArray class]])
    {
        ValueVector valueArray;

        for (id item in nsValue)
        {
            addItemToArray(item, valueArray);
        }
        dict[key] = Value(valueArray);
        return;
    }

}

static void addObjectToNSDict(const std::string& key, const Value& value, NSMutableDictionary *dict)
{
    NSString *NSkey = [NSString stringWithCString:key.c_str() encoding:NSUTF8StringEncoding];

    // the object is a Dictionary
    if (value.getType() == Value::Type::MAP)
    {
        NSMutableDictionary *dictElement = [NSMutableDictionary dictionary];
        ValueMap subDict = value.asValueMap();
        for (auto iter = subDict.begin(); iter != subDict.end(); ++iter)
        {
            addObjectToNSDict(iter->first, iter->second, dictElement);
        }

        [dict setObject:dictElement forKey:NSkey];
        return;
    }

    //add float  into dict
    if (value.getType() == Value::Type::FLOAT) {
        NSNumber *number = [NSNumber numberWithFloat:value.asFloat()];
        [dict setObject:number forKey:NSkey];
    }

    //add double into dict
    if (value.getType() == Value::Type::DOUBLE) {
        NSNumber *number = [NSNumber numberWithDouble:value.asDouble()];
        [dict setObject:number forKey:NSkey];
    }

    //add boolean into dict
    if (value.getType() == Value::Type::BOOLEAN) {
        NSNumber *element = [NSNumber numberWithBool:value.asBool()];
        [dict setObject:element forKey:NSkey];
    }

    //add integer into dict
    if (value.getType() == Value::Type::INTEGER) {
        NSNumber *element = [NSNumber numberWithInt:value.asInt()];
        [dict setObject:element forKey:NSkey];
    }

    // the object is a String
    if (value.getType() == Value::Type::STRING)
    {
        NSString *strElement = [NSString stringWithCString:value.asString().c_str() encoding:NSUTF8StringEncoding];
        [dict setObject:strElement forKey:NSkey];
        return;
    }

    // the object is a Array
    if (value.getType() == Value::Type::VECTOR)
    {
        NSMutableArray *arrElement = [NSMutableArray array];

        ValueVector array = value.asValueVector();

        for(const auto& v : array)
        {
            addObjectToNSArray(v, arrElement);
        }

        [dict setObject:arrElement forKey:NSkey];
        return;
    }
}

FileUtilsApple::FileUtilsApple() {
    _bundle = [NSBundle mainBundle];
}


void FileUtilsApple::setBundle(NSBundle* bundle) {
    _bundle = bundle;
}

NSBundle* FileUtilsApple::getBundle() const {
    return _bundle;
}


#pragma mark - FileUtils

static NSFileManager* s_fileManager = [NSFileManager defaultManager];

FileUtils* FileUtils::getInstance()
{
    if (s_sharedFileUtils == nullptr)
    {
        s_sharedFileUtils = new (std::nothrow) FileUtilsApple();
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
    if (_writablePath.length())
    {
        return _writablePath;
    }

    // save to document folder
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    NSString *documentsDirectory = [paths objectAtIndex:0];
    std::string strRet = [documentsDirectory UTF8String];
    strRet.append("/");
    return strRet;
}

bool FileUtilsApple::isFileExistInternal(const std::string& filePath) const
{
    if (filePath.empty())
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

        NSString* fullpath = [getBundle() pathForResource:[NSString stringWithUTF8String:file.c_str()]
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
        NSString* fullpath = [getBundle() pathForResource:[NSString stringWithUTF8String:filename.c_str()]
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

ValueMap FileUtilsApple::getValueMapFromData(const char* filedata, int filesize)
{
    NSData* file = [NSData dataWithBytes:filedata length:filesize];
    NSPropertyListFormat format;
    NSError* error;
    NSDictionary* dict = [NSPropertyListSerialization propertyListWithData:file options:NSPropertyListImmutable format:&format error:&error];
    
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

