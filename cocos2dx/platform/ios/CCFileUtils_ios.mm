/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org
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

#include <string>
#include <stack>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xmlmemory.h>
#include "CCString.h"
#include "CCFileUtils.h"
#include "CCDirector.h"
#include "CCSAXParser.h"

#define MAX_PATH 260

using namespace cocos2d;

static void static_addValueToCCDict(id key, id value, CCDictionary<std::string, CCObject*>* pDict);
static void static_addItemToCCArray(id item, CCMutableArray<CCObject*> *pArray);

static const char *static_ccRemoveHDSuffixFromFile( const char *pszPath)
{
#if CC_IS_RETINA_DISPLAY_SUPPORTED

    if(cocos2d::CC_CONTENT_SCALE_FACTOR() == 2 ) {
        NSString *path = [NSString stringWithUTF8String: pszPath];
        NSString *name = [path lastPathComponent];
        NSString *suffix = [NSString stringWithUTF8String: CC_RETINA_DISPLAY_FILENAME_SUFFIX];

        // check if path already has the suffix.
        if( [name rangeOfString: suffix].location != NSNotFound ) {

            CCLOG("cocos2d: Filename(%@) contains %@ suffix. Removing it. See cocos2d issue #1040", path, CC_RETINA_DISPLAY_FILENAME_SUFFIX);

            NSString *newLastname = [name stringByReplacingOccurrencesOfString: suffix withString:@""];

            NSString *pathWithoutLastname = [path stringByDeletingLastPathComponent];
            return [[pathWithoutLastname stringByAppendingPathComponent:newLastname] UTF8String];
        }		
    }

#endif // CC_IS_RETINA_DISPLAY_SUPPORTED

    return pszPath;
}

static NSString* getDoubleResolutionImage(NSString* path)
{
#if CC_IS_RETINA_DISPLAY_SUPPORTED

    if( cocos2d::CC_CONTENT_SCALE_FACTOR() == 2 )
    {

        NSString *pathWithoutExtension = [path stringByDeletingPathExtension];
        NSString *name = [pathWithoutExtension lastPathComponent];
        NSString *suffix = [NSString stringWithUTF8String: CC_RETINA_DISPLAY_FILENAME_SUFFIX];

        // check if path already has the suffix.
        if( [name rangeOfString: suffix].location != NSNotFound ) {

            CCLOG("cocos2d: WARNING Filename(%@) already has the suffix %@. Using it.", name, CC_RETINA_DISPLAY_FILENAME_SUFFIX);			
            return path;
        }


        NSString *extension = [path pathExtension];

        if( [extension isEqualToString:@"ccz"] || [extension isEqualToString:@"gz"] )
        {
            // All ccz / gz files should be in the format filename.xxx.ccz
            // so we need to pull off the .xxx part of the extension as well
            extension = [NSString stringWithFormat:@"%@.%@", [pathWithoutExtension pathExtension], extension];
            pathWithoutExtension = [pathWithoutExtension stringByDeletingPathExtension];
        }


        NSString *retinaName = [pathWithoutExtension stringByAppendingString: suffix];
        retinaName = [retinaName stringByAppendingPathExtension:extension];

        NSFileManager *fileManager = [[[NSFileManager alloc] init] autorelease];
        if( [fileManager fileExistsAtPath:retinaName] )
            return retinaName;

        CCLOG("cocos2d: CCFileUtils: Warning HD file not found: %@", [retinaName lastPathComponent] );
    }

#endif // CC_IS_RETINA_DISPLAY_SUPPORTED

    return path;
}

static const char* static_fullPathFromRelativePath(const char *pszRelativePath)

{

    // NSAssert(pszRelativePath != nil, @"CCFileUtils: Invalid path");

    // do not convert an absolute path (starting with '/')
    NSString *relPath = [NSString stringWithUTF8String: pszRelativePath];
    NSString *fullpath = nil;
	
	// only if it is not an absolute path
	if( ! [relPath isAbsolutePath] )
	{
		NSString *file = [relPath lastPathComponent];
		NSString *imageDirectory = [relPath stringByDeletingLastPathComponent];
		
		fullpath = [[NSBundle mainBundle] pathForResource:file
												   ofType:nil
											  inDirectory:imageDirectory];
	}
	
	if (fullpath == nil)
		fullpath = relPath;
	
	fullpath = getDoubleResolutionImage(fullpath);
	
	return [fullpath UTF8String];	
}

static void static_addItemToCCArray(id item, CCMutableArray<CCObject*> *pArray)
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
        CCDictionary<std::string, CCObject*>* pDictItem = new CCDictionary<std::string, CCObject*>();
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
        CCMutableArray<CCObject*> *pArrayItem = new CCMutableArray<CCObject*>();
        for (id subItem in item) {
            static_addItemToCCArray(subItem, pArrayItem);
        }
        pArray->addObject(pArrayItem);
        pArrayItem->release();
        return;
    }
}

static void static_addValueToCCDict(id key, id value, CCDictionary<std::string, CCObject*>* pDict)
{
	// the key must be a string
    CCAssert([key isKindOfClass:[NSString class]], "The key should be a string!");
    std::string pKey = [key UTF8String];

	// the value is a new dictionary
    if ([value isKindOfClass:[NSDictionary class]]) {
        CCDictionary<std::string, CCObject*>* pSubDict = new CCDictionary<std::string, CCObject*>();
        for (id subKey in [value allKeys]) {
            id subValue = [value objectForKey:subKey];
            static_addValueToCCDict(subKey, subValue, pSubDict);
        }
        pDict->setObject(pSubDict, pKey);
        pSubDict->release();
        return;
    }

	// the value is a string
    if ([value isKindOfClass:[NSString class]]) {
        CCString* pValue = new CCString([value UTF8String]);

        pDict->setObject(pValue, pKey);
        pValue->release();
        return;
    }

	// the value is a number
    if ([value isKindOfClass:[NSNumber class]]) {
        NSString* pStr = [value stringValue];
        CCString* pValue = new CCString([pStr UTF8String]);
        
        pDict->setObject(pValue, pKey);
        pValue->release();
        return;
    }

	// the value is a array
    if ([value isKindOfClass:[NSArray class]]) {
        CCMutableArray<CCObject*> *pArray = new CCMutableArray<CCObject*>();
        for (id item in value) {
            static_addItemToCCArray(item, pArray);
        }
        pDict->setObject(pArray, pKey);
        pArray->release();
        return;
    }
}

namespace cocos2d {

    // record the resource path
    static char s_pszResourcePath[MAX_PATH] = {0};

    void CCFileUtils::setResourcePath(const char *pszResourcePath)
    {
        // NSAssert(pszResourcePath != NULL, "[FileUtils setResourcePath] -- wrong resource path");
        // NSAssert(strlen(pszResourcePath) <= MAX_PATH, "[FileUtils setResourcePath] -- resource path too long");

        strcpy(s_pszResourcePath, pszResourcePath);
    }
    
    int CCFileUtils::ccLoadFileIntoMemory(const char *filename, unsigned char **out)
    {
        CCAssert( out, "ccLoadFileIntoMemory: invalid 'out' parameter");
        CCAssert( &*out, "ccLoadFileIntoMemory: invalid 'out' parameter");

        size_t size = 0;
        FILE *f = fopen(filename, "rb");
        if( !f ) { 
            *out = NULL;
            return -1;
        } 

        fseek(f, 0, SEEK_END);
        size = ftell(f);
        fseek(f, 0, SEEK_SET);

        *out = (unsigned char*)malloc(size);
        size_t read = fread(*out, 1, size, f);
        if( read != size ) { 
            free(*out);
            *out = NULL;
            return -1;
        }

        fclose(f);

        return size;
    }

    std::string& CCFileUtils::ccRemoveHDSuffixFromFile(std::string& path )
    {
        path = static_ccRemoveHDSuffixFromFile(path.c_str());
        return path;
    }

    const char* CCFileUtils::fullPathFromRelativePath(const char *pszRelativePath)
    {
        return static_fullPathFromRelativePath(pszRelativePath);
    }

    const char *CCFileUtils::fullPathFromRelativeFile(const char *pszFilename, const char *pszRelativeFile)
    {
        std::string relativeFile = fullPathFromRelativePath(pszRelativeFile);
        CCString *pRet = new CCString();
        pRet->autorelease();
        pRet->m_sString = relativeFile.substr(0, relativeFile.rfind('/')+1);
        pRet->m_sString += pszFilename;
        return pRet->m_sString.c_str();
    }
    CCDictionary<std::string, CCObject*> *CCFileUtils::dictionaryWithContentsOfFile(const char *pFileName)
    {
        NSString* pPath = [NSString stringWithUTF8String:pFileName];
        NSDictionary* pDict = [NSDictionary dictionaryWithContentsOfFile:pPath];
        
        CCDictionary<std::string, CCObject*>* pRet = new CCDictionary<std::string, CCObject*>();
        for (id key in [pDict allKeys]) {
            id value = [pDict objectForKey:key];
            static_addValueToCCDict(key, value, pRet);
        }
        pRet->autorelease();
        return pRet;
    }
    unsigned char* CCFileUtils::getFileData(const char* pszFileName, const char* pszMode, unsigned long * pSize)
    {
        unsigned char * pBuffer = NULL;

        do 
        {
            // read the file from hardware
            FILE *fp = fopen(pszFileName, pszMode);
            CC_BREAK_IF(!fp);

            fseek(fp,0,SEEK_END);
            *pSize = ftell(fp);
            fseek(fp,0,SEEK_SET);
            pBuffer = new unsigned char[*pSize];
            *pSize = fread(pBuffer,sizeof(unsigned char), *pSize,fp);
            fclose(fp);
        } while (0);

        if (! pBuffer && getIsPopupNotify()) 
        {
            std::string title = "Notification";
            std::string msg = "Get data from file(";
            msg.append(pszFileName).append(") failed!");

            CCMessageBox(msg.c_str(), title.c_str());
        }
        return pBuffer;
    }
    void CCFileUtils::setResource(const char* pszZipFileName)
    {
        CCAssert(0, "Have not implement!");
    }

    // notification support when getFileData from a invalid file
    static bool s_bPopupNotify = true;

    void CCFileUtils::setIsPopupNotify(bool bNotify)
    {
        s_bPopupNotify = bNotify;
    }

    bool CCFileUtils::getIsPopupNotify()
    {
        return s_bPopupNotify;
    }
    
    std::string CCFileUtils::getWriteablePath()
    {
        // save to document folder
        NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
        NSString *documentsDirectory = [paths objectAtIndex:0];
        std::string strRet = [documentsDirectory UTF8String];
        strRet.append("/");
        return strRet;
    }

}//namespace cocos2d

