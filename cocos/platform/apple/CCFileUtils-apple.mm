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

#include "platform/apple/CCFileUtils-apple.h"

#include <ftw.h>

#include <string>
#include <stack>

#include "base/CCDirector.h"
#include "deprecated/CCDictionary.h"
#include "platform/CCFileUtils.h"
#include "platform/CCSAXParser.h"

NS_CC_BEGIN

struct FileUtilsApple::IMPL {
    IMPL(NSBundle* bundle):bundle_([NSBundle mainBundle]) {}
    void setBundle(NSBundle* bundle) {
        bundle_ = bundle;
    }
    NSBundle* getBundle() const {
        return bundle_;
    }
private:
    NSBundle* bundle_;
};

static id convertCCValueToNSObject(const cocos2d::Value &value);
static cocos2d::Value convertNSObjectToCCValue(id object);

static void addNSObjectToCCMap(id nsKey, id nsValue, ValueMap& dict);
static void addCCValueToNSDictionary(const std::string& key, const Value& value, NSMutableDictionary *dict);
static void addNSObjectToCCVector(id item, ValueVector& array);
static void addCCValueToNSArray(const Value& value, NSMutableArray *array);

static id convertCCValueToNSObject(const cocos2d::Value &value)
{
    switch (value.getType())
    {
        case Value::Type::NONE:
            return [NSNull null];
            
        case Value::Type::STRING:
            return [NSString stringWithCString:value.asString().c_str() encoding:NSUTF8StringEncoding];
            
        case Value::Type::BYTE:
            return [NSNumber numberWithInt:value.asByte()];
            
        case Value::Type::INTEGER:
            return [NSNumber numberWithInt:value.asInt()];
            
        case Value::Type::UNSIGNED:
            return [NSNumber numberWithUnsignedInt:value.asUnsignedInt()];
            
        case Value::Type::FLOAT:
            return [NSNumber numberWithFloat:value.asFloat()];
            
        case Value::Type::DOUBLE:
            return [NSNumber numberWithDouble:value.asDouble()];
            
        case Value::Type::BOOLEAN:
            return [NSNumber numberWithBool:value.asBool()];
            
        case Value::Type::VECTOR: {
            NSMutableArray *array = [NSMutableArray array];
            const ValueVector &vector = value.asValueVector();
            for (const auto &e : vector) {
                addCCValueToNSArray(e, array);
            }
            return array;
        }
            
        case Value::Type::MAP: {
            NSMutableDictionary *dictionary = [NSMutableDictionary dictionary];
            const ValueMap &map = value.asValueMap();
            for (auto iter = map.begin(); iter != map.end(); ++iter) {
                addCCValueToNSDictionary(iter->first, iter->second, dictionary);
            }
            return dictionary;
        }
            
        case Value::Type::INT_KEY_MAP:
            break;
    }
    
    return [NSNull null];
}

static cocos2d::Value convertNSObjectToCCValue(id item)
{
    // add string value into array
    if ([item isKindOfClass:[NSString class]])
    {
        return Value([item UTF8String]);
    }
    
    // add number value into array(such as int, float, bool and so on)
    // the value is a number
    if ([item isKindOfClass:[NSNumber class]])
    {
        NSNumber* num = item;
        const char* numType = [num objCType];
        if(num == (void*)kCFBooleanFalse || num == (void*)kCFBooleanTrue)
        {
            bool v = [num boolValue];
            return Value(v);
        }
        else if(strcmp(numType, @encode(float)) == 0)
        {
            return Value([num floatValue]);
        }
        else if(strcmp(numType, @encode(double)) == 0)
        {
            return Value([num doubleValue]);
        }
        else
        {
            return Value([num intValue]);
        }
    }
    
    
    // add dictionary value into array
    if ([item isKindOfClass:[NSDictionary class]])
    {
        ValueMap dict;
        for (id subKey in [item allKeys])
        {
            id subValue = [item objectForKey:subKey];
            addNSObjectToCCMap(subKey, subValue, dict);
        }
        
        return Value(dict);
    }
    
    // add array value into array
    if ([item isKindOfClass:[NSArray class]])
    {
        ValueVector subArray;
        for (id subItem in item)
        {
            addNSObjectToCCVector(subItem, subArray);
        }
        return Value(subArray);
    }
    
    return Value::Null;
}

static void addNSObjectToCCVector(id item, ValueVector& array)
{
    array.push_back(convertNSObjectToCCValue(item));
}

static void addCCValueToNSArray(const Value& value, NSMutableArray *array)
{
    [array addObject:convertCCValueToNSObject(value)];
}

static void addNSObjectToCCMap(id nsKey, id nsValue, ValueMap& dict)
{
    // the key must be a string
    CCASSERT([nsKey isKindOfClass:[NSString class]], "The key should be a string!");
    std::string key = [nsKey UTF8String];
    dict[key] = convertNSObjectToCCValue(nsValue);
}

static void addCCValueToNSDictionary(const std::string& key, const Value& value, NSMutableDictionary *dict)
{
    NSString *NSkey = [NSString stringWithCString:key.c_str() encoding:NSUTF8StringEncoding];
    [dict setObject:convertCCValueToNSObject(value) forKey:NSkey];
}


FileUtilsApple::FileUtilsApple() : pimpl_(new IMPL([NSBundle mainBundle])) {
}

FileUtilsApple::~FileUtilsApple() = default;

#if CC_FILEUTILS_APPLE_ENABLE_OBJC
void FileUtilsApple::setBundle(NSBundle* bundle) {
    pimpl_->setBundle(bundle);
}
#endif

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

        NSString* fullpath = [pimpl_->getBundle() pathForResource:[NSString stringWithUTF8String:file.c_str()]
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

static int unlink_cb(const char *fpath, const struct stat *sb, int typeflag, struct FTW *ftwbuf)
{
    auto ret = remove(fpath);
    if (ret)
    {
        log("Fail to remove: %s ",fpath);
    }

    return ret;
}

bool FileUtilsApple::removeDirectory(const std::string& path)
{
    if (path.empty())
    {
        CCLOGERROR("Fail to remove directory, path is empty!");
        return false;
    }

    if (nftw(path.c_str(),unlink_cb, 64, FTW_DEPTH | FTW_PHYS))
        return false;
    else
        return true;
}

std::string FileUtilsApple::getFullPathForDirectoryAndFilename(const std::string& directory, const std::string& filename) const
{
    if (directory[0] != '/')
    {
        NSString* fullpath = [pimpl_->getBundle() pathForResource:[NSString stringWithUTF8String:filename.c_str()]
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
    auto d(FileUtils::getInstance()->getDataFromFile(filename));
    return getValueMapFromData(reinterpret_cast<char*>(d.getBytes()), static_cast<int>(d.getSize()));
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
            addNSObjectToCCMap(key, value, ret);
        }
    }
    return ret;
}

bool FileUtilsApple::writeToFile(const ValueMap& dict, const std::string &fullPath)
{
    return writeValueMapToFile(dict, fullPath);
}

bool FileUtils::writeValueMapToFile(const ValueMap& dict, const std::string& fullPath)
{
    valueMapCompact(const_cast<ValueMap&>(dict));
    //CCLOG("iOS||Mac Dictionary %d write to file %s", dict->_ID, fullPath.c_str());
    NSMutableDictionary *nsDict = [NSMutableDictionary dictionary];

    for (auto iter = dict.begin(); iter != dict.end(); ++iter)
    {
        addCCValueToNSDictionary(iter->first, iter->second, nsDict);
    }

    NSString *file = [NSString stringWithUTF8String:fullPath.c_str()];
    // do it atomically
    return [nsDict writeToFile:file atomically:YES];
}

void FileUtilsApple::valueMapCompact(ValueMap& valueMap)
{
    auto itr = valueMap.begin();
    while(itr != valueMap.end()){
        auto vtype = itr->second.getType();
        switch(vtype){
            case Value::Type::NONE:{
                itr = valueMap.erase(itr);
                continue;
            }
                break;
            case Value::Type::MAP:{
                valueMapCompact(itr->second.asValueMap());
            }
                break;
            case Value::Type::VECTOR:{
                valueVectorCompact(itr->second.asValueVector());
            }
                break;
            default:
                break;
        }
        itr++;
    }
}

void FileUtilsApple::valueVectorCompact(ValueVector& valueVector)
{
    auto itr = valueVector.begin();
    while(itr != valueVector.end()){
        auto vtype = (*itr).getType();
        switch(vtype){
            case Value::Type::NONE:{
                itr = valueVector.erase(itr);
                continue;
            }
                break;
            case Value::Type::MAP:{
                valueMapCompact((*itr).asValueMap());
            }
                break;
            case Value::Type::VECTOR:{
                valueVectorCompact((*itr).asValueVector());
            }
                break;
            default:
                break;
        }
        itr++;
    }
}

bool FileUtils::writeValueVectorToFile(const ValueVector& vecData, const std::string& fullPath)
{
    NSString* path = [NSString stringWithUTF8String:fullPath.c_str()];
    NSMutableArray* array = [NSMutableArray array];

    for (const auto &e : vecData)
    {
        addCCValueToNSArray(e, array);
    }

    [array writeToFile:path atomically:YES];

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
        addNSObjectToCCVector(value, ret);
    }

    return ret;
}

bool FileUtilsApple::createDirectory(const std::string& path)
{
    CCASSERT(!path.empty(), "Invalid path");
    
    if (isDirectoryExist(path))
        return true;
    
    NSError* error;
    
    bool result = [s_fileManager createDirectoryAtPath:[NSString stringWithUTF8String:path.c_str()] withIntermediateDirectories:YES attributes:nil error:&error];
    
    if(!result && error != nil)
    {
        CCLOGERROR("Fail to create directory \"%s\": %s", path.c_str(), [error.localizedDescription UTF8String]);
    }
    
    return result;
}

NS_CC_END
