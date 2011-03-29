/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

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

namespace cocos2d {

typedef enum 
{
    SAX_NONE = 0,
    SAX_KEY,
    SAX_DICT,
    SAX_INT,
    SAX_REAL,
    SAX_STRING
}CCSAXState;

class CCDictMaker : public CCSAXDelegator
{
public:
    CCDictionary<std::string, CCObject*> *m_pRootDict;
    CCDictionary<std::string, CCObject*> *m_pCurDict;
    std::stack<CCDictionary<std::string, CCObject*>*> m_tDictStack;
    std::string m_sCurKey;///< parsed key
    CCSAXState m_tState;
public:
    CCDictMaker()
    {
        m_pRootDict = NULL;
        m_pCurDict = NULL;
        m_tState = SAX_NONE;
    }
    ~CCDictMaker()
    {
    }
    CCDictionary<std::string, CCObject*> *dictionaryWithContentsOfFile(const char *pFileName)
    {
        CCSAXParser parser;

        if (false == parser.init("UTF-8"))
        {
            return NULL;
        }
        parser.setDelegator(this);

        parser.parse(pFileName);
        return m_pRootDict;
    }

    void startElement(void *ctx, const char *name, const char **atts)
    {
        std::string sName((char*)name);
        if( sName == "dict" )
        {
            CCDictionary<std::string, CCObject*> *pNewDict = new CCDictionary<std::string, CCObject*>();
            if(! m_pRootDict)
            {
                m_pRootDict = pNewDict;
                pNewDict->autorelease();
            }
            else
            {
                CCAssert(m_pCurDict && !m_sCurKey.empty(), "");
                m_pCurDict->setObject(pNewDict, m_sCurKey);
                pNewDict->release();
                m_sCurKey.clear();
            }
            m_pCurDict = pNewDict;
            m_tDictStack.push(m_pCurDict);
            m_tState = SAX_DICT;
        }
        else if(sName == "key")
        {
            m_tState = SAX_KEY;
        }
        else if(sName == "integer")
        {
            m_tState = SAX_INT;
        }
        else if(sName == "real")
        {
            m_tState = SAX_REAL;
        }
        else if(sName == "string")
        {
            m_tState = SAX_STRING;
        }
        else
        {
            m_tState = SAX_NONE;
        }
    }

    void endElement(void *ctx, const char *name)
    {
        std::string sName((char*)name);
        if( sName == "dict" )
        {
            m_tDictStack.pop();
            if ( !m_tDictStack.empty() )
            {
                m_pCurDict = (CCDictionary<std::string, CCObject*>*)(m_tDictStack.top());
            }
        }
        m_tState = SAX_NONE;
    }

    void textHandler(void *ctx, const char *ch, int len)
    {
        if (m_tState == SAX_NONE)
        {
            return;
        }
        CCString *pText = new CCString();
        pText->m_sString = std::string((char*)ch,0,len);

        switch(m_tState)
        {
        case SAX_KEY:
            m_sCurKey = pText->m_sString;
            break;
        case SAX_INT:
        case SAX_REAL:
        case SAX_STRING:
            {
                CCAssert(!m_sCurKey.empty(), "not found key : <integet/real>");
                m_pCurDict->setObject(pText, m_sCurKey);
                break;
            }
        }
        pText->release();
    }
};
    
    // record the resource path
    static char s_pszResourcePath[MAX_PATH] = {0};
    
    void CCFileUtils::setResourcePath(const char *pszResourcePath)
    {
                    // NSAssert(pszResourcePath != NULL, "[FileUtils setResourcePath] -- wrong resource path");
                    // NSAssert(strlen(pszResourcePath) <= MAX_PATH, "[FileUtils setResourcePath] -- resource path too long");
        
        strcpy(s_pszResourcePath, pszResourcePath);
    }
    
    const char* CCFileUtils::getResourcePath()
    {
        return s_pszResourcePath;
    }

    int CCFileUtils::ccLoadFileIntoMemory(const char *filename, unsigned char **out)
    {
        assert( out );
        assert( &*out );
        
        int size = 0;
        FILE *f = fopen(filename, "rb");
        if( !f ) { 
            *out = NULL;
            return -1;
        } 
        
        fseek(f, 0, SEEK_END);
        size = ftell(f);
        fseek(f, 0, SEEK_SET);
        
        *out = (unsigned char*)malloc(size);
        int read = fread(*out, 1, size, f);
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
        CCDictMaker tMaker;
        return tMaker.dictionaryWithContentsOfFile(pFileName);
    }
    unsigned char* CCFileUtils::getFileData(const char* pszFileName, const char* pszMode, unsigned long * pSize)
    {
        unsigned char * Buffer = NULL;

        do 
        {
            // read the file from hardware
            FILE *fp = fopen(pszFileName, pszMode);
            CC_BREAK_IF(!fp);

            fseek(fp,0,SEEK_END);
            *pSize = ftell(fp);
            fseek(fp,0,SEEK_SET);
            Buffer = new unsigned char[*pSize];
            *pSize = fread(Buffer,sizeof(unsigned char), *pSize,fp);
            fclose(fp);
        } while (0);

        return Buffer;
    }
    void CCFileUtils::setResource(const char* pszZipFileName, const char* pszResPath)
    {
        CCAssert(0, "Have not implement!");
    }
    void CCFileUtils::setRelativePath(const char* pszRelativePath)
    {
        CCAssert(0, "Have not implement!");
    }
}//namespace   cocos2d 
