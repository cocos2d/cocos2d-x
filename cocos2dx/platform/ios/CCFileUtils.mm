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
#import <Foundation/Foundation.h>
#import <UIKit/UIDevice.h>

#include <string>
#include <stack>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xmlmemory.h>
#include "cocoa/CCString.h"
#include "CCFileUtils.h"
#include "CCDirector.h"
#include "CCSAXParser.h"
#include "CCDictionary.h"
#include "support/zip_support/unzip.h"

#define MAX_PATH 260

USING_NS_CC;

static void static_addValueToCCDict(id key, id value, CCDictionary* pDict);
static void static_addItemToCCArray(id item, CCArray* pArray);

static void static_addItemToCCArray(id item, CCArray *pArray)
{
    // add string value into array
    if ([item isKindOfClass:[NSString class]]) {
        CCString* pValue = new CCString([item UTF8String]);
        
        pArray->addObject(pValue);
        pValue->release();
        return;
    }

    // add number value into array(such as int, float, bool and so on)
    if ([item isKindOfClass:[NSNumber class]]) {
        NSString* pStr = [item stringValue];
        CCString* pValue = new CCString([pStr UTF8String]);
        
        pArray->addObject(pValue);
        pValue->release();
        return;
    }
    
    // add dictionary value into array
    if ([item isKindOfClass:[NSDictionary class]]) {
        CCDictionary* pDictItem = new CCDictionary();
        for (id subKey in [item allKeys]) {
            id subValue = [item objectForKey:subKey];
            static_addValueToCCDict(subKey, subValue, pDictItem);
        }
        pArray->addObject(pDictItem);
        pDictItem->release();
        return;
    }
    
    // add array value into array
    if ([item isKindOfClass:[NSArray class]]) {
        CCArray *pArrayItem = new CCArray();
        pArrayItem->init();
        for (id subItem in item) {
            static_addItemToCCArray(subItem, pArrayItem);
        }
        pArray->addObject(pArrayItem);
        pArrayItem->release();
        return;
    }
}

static void static_addValueToCCDict(id key, id value, CCDictionary* pDict)
{
    // the key must be a string
    CCAssert([key isKindOfClass:[NSString class]], "The key should be a string!");
    std::string pKey = [key UTF8String];

    // the value is a new dictionary
    if ([value isKindOfClass:[NSDictionary class]]) {
        CCDictionary* pSubDict = new CCDictionary();
        for (id subKey in [value allKeys]) {
            id subValue = [value objectForKey:subKey];
            static_addValueToCCDict(subKey, subValue, pSubDict);
        }
        pDict->setObject(pSubDict, pKey.c_str());
        pSubDict->release();
        return;
    }

    // the value is a string
    if ([value isKindOfClass:[NSString class]]) {
        CCString* pValue = new CCString([value UTF8String]);

        pDict->setObject(pValue, pKey.c_str());
        pValue->release();
        return;
    }

    // the value is a number
    if ([value isKindOfClass:[NSNumber class]]) {
        NSString* pStr = [value stringValue];
        CCString* pValue = new CCString([pStr UTF8String]);
        
        pDict->setObject(pValue, pKey.c_str());
        pValue->release();
        return;
    }

    // the value is a array
    if ([value isKindOfClass:[NSArray class]]) {
        CCArray *pArray = new CCArray();
        pArray->init();
        for (id item in value) {
            static_addItemToCCArray(item, pArray);
        }
        pDict->setObject(pArray, pKey.c_str());
        pArray->release();
        return;
    }
}

NS_CC_BEGIN

static std::map<std::string, std::string> s_fullPathCache;

static CCFileUtils* s_pFileUtils = NULL;
static NSFileManager* s_fileManager = [NSFileManager defaultManager];

CCFileUtils* CCFileUtils::sharedFileUtils()
{
    if (s_pFileUtils == NULL)
    {
        s_pFileUtils = new CCFileUtils();
        s_pFileUtils->init();
    }
    return s_pFileUtils;
}

void CCFileUtils::purgeFileUtils()
{
    if (s_pFileUtils != NULL)
    {
        s_pFileUtils->purgeCachedEntries();
        CC_SAFE_RELEASE(s_pFileUtils->m_pFilenameLookupDict);
    }

    CC_SAFE_DELETE(s_pFileUtils);
}

void CCFileUtils::purgeCachedEntries()
{
    s_fullPathCache.clear();
}

bool CCFileUtils::init()
{
    m_strDefaultResRootPath = "";
    m_searchPathArray.push_back(m_strDefaultResRootPath);
    m_searchResolutionsOrderArray.push_back("");

    return true;
}

void CCFileUtils::setSearchResolutionsOrder(const std::vector<std::string>& searchResolutionsOrder)
{
    bool bExistDefault = false;
    m_searchResolutionsOrderArray.clear();
    for (std::vector<std::string>::const_iterator iter = searchResolutionsOrder.begin(); iter != searchResolutionsOrder.end(); ++iter)
    {
        if (!bExistDefault && (*iter) == "")
        {
            bExistDefault = true;
        }
        m_searchResolutionsOrderArray.push_back(*iter);
    }
    if (!bExistDefault)
    {
        m_searchResolutionsOrderArray.push_back("");
    }
}

const std::vector<std::string>& CCFileUtils::getSearchResolutionsOrder()
{
    return m_searchResolutionsOrderArray;
}

void CCFileUtils::setSearchPaths(const std::vector<std::string>& searchPaths)
{
    bool bExistDefault = false;
    m_searchPathArray.clear();
    for (std::vector<std::string>::const_iterator iter = searchPaths.begin(); iter != searchPaths.end(); ++iter)
    {
        if (!bExistDefault && (*iter) == "")
        {
            bExistDefault = true;
        }
        m_searchPathArray.push_back(*iter);
    }
    if (!bExistDefault)
    {
        m_searchPathArray.push_back(m_strDefaultResRootPath);
    }
}

const std::vector<std::string>& CCFileUtils::getSearchPaths()
{
    return m_searchPathArray;
}

void CCFileUtils::setResourceDirectory(const char *pszDirectoryName)
{
    m_obDirectory = pszDirectoryName;
    if (m_obDirectory.size() > 0 && m_obDirectory[m_obDirectory.size() - 1] != '/')
    {
        m_obDirectory.append("/");
    }
    m_searchPathArray.insert(m_searchPathArray.begin(), m_obDirectory);
}

const char* CCFileUtils::getResourceDirectory()
{
    return m_obDirectory.c_str();
}

const char* CCFileUtils::fullPathFromRelativePath(const char *pszRelativePath)
{
    return CCString::create(fullPathForFilename(pszRelativePath))->getCString();
}

std::string CCFileUtils::getNewFilename(const char* pszFileName)
{
    const char* pszNewFileName = NULL;
    // in Lookup Filename dictionary ?
    CCString* fileNameFound = m_pFilenameLookupDict ? (CCString*)m_pFilenameLookupDict->objectForKey(pszFileName) : NULL;
    if( NULL == fileNameFound || fileNameFound->length() == 0) {
        pszNewFileName = pszFileName;
    }
    else {
        pszNewFileName = fileNameFound->getCString();
    }
    return pszNewFileName;
}

std::string CCFileUtils::getPathForFilename(const std::string& filename, const std::string& resourceDirectory, const std::string& searchPath)
{
    std::string file = filename;
    std::string file_path = "";
    size_t pos = filename.find_last_of("/");
    if (pos != std::string::npos)
    {
        file_path = filename.substr(0, pos+1);
        file = filename.substr(pos+1);
    }
    
	// searchPath + file_path + resourceDirectory
    std::string path = searchPath;
    if (path[path.length()-1] != '/')
    {
        path += "/";
    }
    path += file_path;
	path += resourceDirectory;
    
    if (searchPath[0] != '/')
    {
        NSString* fullpath = [[NSBundle mainBundle] pathForResource:[NSString stringWithUTF8String:file.c_str()]
                                               ofType:nil
                                          inDirectory:[NSString stringWithUTF8String:path.c_str()]];
        if (fullpath != nil) {
            return [fullpath UTF8String];
        }
    }
    else
    {// Search path is an absolute path.
        std::string fullPath = path + file;
        if ([s_fileManager fileExistsAtPath:[NSString stringWithUTF8String:fullPath.c_str()]]) {
            return fullPath;
        }
    }
    
    // Return empty string when file wasn't found.
	return "";
}

std::string CCFileUtils::fullPathForFilename(const char* pszFileName)
{
    CCAssert(pszFileName != NULL, "CCFileUtils: Invalid path");

    NSString *relPath = [NSString stringWithUTF8String:pszFileName];
    
    // Return directly if it's an absolute path.
    if ([relPath isAbsolutePath]) {
        return pszFileName;
    }
    
    // Already Cached ?
    std::map<std::string, std::string>::iterator cacheIter = s_fullPathCache.find(pszFileName);
    if (cacheIter != s_fullPathCache.end()) {
        //CCLOG("Return full path from cache: %s", cacheIter->second.c_str());
        return cacheIter->second;
    }
    
    std::string fullpath = "";
    
    // in Lookup Filename dictionary ?
    std::string newfilename = this->getNewFilename(pszFileName);

    for (std::vector<std::string>::iterator searchPathsIter = m_searchPathArray.begin();
         searchPathsIter != m_searchPathArray.end(); ++searchPathsIter) {
        for (std::vector<std::string>::iterator resOrderIter = m_searchResolutionsOrderArray.begin();
             resOrderIter != m_searchResolutionsOrderArray.end(); ++resOrderIter) {
            
            fullpath = this->getPathForFilename(newfilename, *resOrderIter, *searchPathsIter);
            
            if (fullpath.length() > 0)
            {
                // Adding the full path to cache if the file was found.
                s_fullPathCache.insert(std::pair<std::string, std::string>(pszFileName, fullpath));
                return fullpath;
            }
        }
    }

    // The file wasn't found, return the file name passed in.
    return pszFileName;
}

void CCFileUtils::loadFilenameLookupDictionaryFromFile(const char* filename)
{
    std::string pFullPath = this->fullPathForFilename(filename);
    if (pFullPath.length() > 0)
    {
        CCDictionary* pDict = CCDictionary::createWithContentsOfFile(filename);
        if (pDict)
        {
            CCDictionary* pMetadata = (CCDictionary*)pDict->objectForKey("metadata");
            int version = ((CCString*)pMetadata->objectForKey("version"))->intValue();
            if (version != 1)
            {
                CCLOG("cocos2d: ERROR: Invalid filenameLookup dictionary version: %ld. Filename: %s", (long)version, filename);
                return;
            }
            
            setFilenameLookupDictionary((CCDictionary*)pDict->objectForKey("filenames"));
        }
    }
}

void CCFileUtils::setFilenameLookupDictionary(CCDictionary* pFilenameLookupDict)
{
    CC_SAFE_RELEASE(m_pFilenameLookupDict);
    m_pFilenameLookupDict = pFilenameLookupDict;
    CC_SAFE_RETAIN(m_pFilenameLookupDict);
}

const char* CCFileUtils::fullPathFromRelativeFile(const char *pszFilename, const char *pszRelativeFile)
{
    std::string relativeFile = fullPathForFilename(pszRelativeFile);
    CCString *pRet = CCString::create("");
    pRet->m_sString = relativeFile.substr(0, relativeFile.rfind('/')+1);
    pRet->m_sString += getNewFilename(pszFilename);
    return pRet->m_sString.c_str();
}

CCDictionary* ccFileUtils_dictionaryWithContentsOfFileThreadSafe(const char *pFileName)
{
    std::string fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(pFileName);
    NSString* pPath = [NSString stringWithUTF8String:fullPath.c_str()];
    NSDictionary* pDict = [NSDictionary dictionaryWithContentsOfFile:pPath];
    
    CCDictionary* pRet = new CCDictionary();
    for (id key in [pDict allKeys]) {
        id value = [pDict objectForKey:key];
        static_addValueToCCDict(key, value, pRet);
    }
    
    return pRet;
}

CCArray* ccFileUtils_arrayWithContentsOfFileThreadSafe(const char* pFileName)
{
//    NSString* pPath = [NSString stringWithUTF8String:pFileName];
//    NSString* pathExtension= [pPath pathExtension];
//    pPath = [pPath stringByDeletingPathExtension];
//    pPath = [[NSBundle mainBundle] pathForResource:pPath ofType:pathExtension];
//    fixing cannot read data using CCArray::createWithContentsOfFile
    std::string fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(pFileName);
    NSString* pPath = [NSString stringWithUTF8String:fullPath.c_str()];
    NSArray* pArray = [NSArray arrayWithContentsOfFile:pPath];
    
    CCArray* pRet = new CCArray();
    for (id value in pArray) {
        static_addItemToCCArray(value, pRet);
    }

    return pRet;
}

unsigned char* CCFileUtils::getFileData(const char* pszFileName, const char* pszMode, unsigned long * pSize)
{
    unsigned char * pBuffer = NULL;
    CCAssert(pszFileName != NULL && pSize != NULL && pszMode != NULL, "Invalid parameters.");
    *pSize = 0;
    do 
    {
        // read the file from hardware
        std::string fullPath = fullPathForFilename(pszFileName);
        FILE *fp = fopen(fullPath.c_str(), pszMode);
        CC_BREAK_IF(!fp);

        fseek(fp,0,SEEK_END);
        *pSize = ftell(fp);
        fseek(fp,0,SEEK_SET);
        pBuffer = new unsigned char[*pSize];
        *pSize = fread(pBuffer,sizeof(unsigned char), *pSize,fp);
        fclose(fp);
    } while (0);

    if (! pBuffer && isPopupNotify()) 
    {
        std::string title = "Notification";
        std::string msg = "Get data from file(";
        msg.append(pszFileName).append(") failed!");

        CCMessageBox(msg.c_str(), title.c_str());
    }
    return pBuffer;
}

// notification support when getFileData from a invalid file
static bool s_bPopupNotify = true;

void CCFileUtils::setPopupNotify(bool bNotify)
{
    s_bPopupNotify = bNotify;
}

bool CCFileUtils::isPopupNotify()
{
    return s_bPopupNotify;
}

std::string CCFileUtils::getWriteablePath()
{
    // save to document folder
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSCachesDirectory, NSUserDomainMask, YES);
    NSString *documentsDirectory = [paths objectAtIndex:0];
    std::string strRet = [documentsDirectory UTF8String];
    strRet.append("/");
    return strRet;
}

unsigned char* CCFileUtils::getFileDataFromZip(const char* pszZipFilePath, const char* pszFileName, unsigned long * pSize)
{
        unsigned char * pBuffer = NULL;
        unzFile pFile = NULL;
        *pSize = 0;
    
        do 
        {
            CC_BREAK_IF(!pszZipFilePath || !pszFileName);
            CC_BREAK_IF(strlen(pszZipFilePath) == 0);
    
            pFile = unzOpen(pszZipFilePath);
            CC_BREAK_IF(!pFile);
    
            int nRet = unzLocateFile(pFile, pszFileName, 1);
            CC_BREAK_IF(UNZ_OK != nRet);
    
            char szFilePathA[260];
            unz_file_info FileInfo;
            nRet = unzGetCurrentFileInfo(pFile, &FileInfo, szFilePathA, sizeof(szFilePathA), NULL, 0, NULL, 0);
            CC_BREAK_IF(UNZ_OK != nRet);
    
            nRet = unzOpenCurrentFile(pFile);
            CC_BREAK_IF(UNZ_OK != nRet);
    
            pBuffer = new unsigned char[FileInfo.uncompressed_size];
            int nSize = 0;
            nSize = unzReadCurrentFile(pFile, pBuffer, FileInfo.uncompressed_size);
            CCAssert(nSize == 0 || nSize == (int)FileInfo.uncompressed_size, "the file size is wrong");
    
            *pSize = FileInfo.uncompressed_size;
            unzCloseCurrentFile(pFile);
        } while (0);
    
        if (pFile)
        {
            unzClose(pFile);
        }

            return pBuffer;
}

NS_CC_END

