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
#include "NSString.h"
#include "CCXFileUtils_iphone.h"
#include "CCXCocos2dDefine.h"

#define MAX_PATH 260

static const char *static_ccRemoveHDSuffixFromFile( const char *pszPath )
{
#if CC_IS_RETINA_DISPLAY_SUPPORTED
    
	if( CC_CONTENT_SCALE_FACTOR() == 2 ) {
                NSString *path = [NSString stringWithUTF8String: pszPath]
		NSString *name = [path lastPathComponent];
		
		// check if path already has the suffix.
		if( [name rangeOfString:CC_RETINA_DISPLAY_FILENAME_SUFFIX].location != NSNotFound ) {
			
			CCLOG(@"cocos2d: Filename(%@) contains %@ suffix. Removing it. See cocos2d issue #1040", path, CC_RETINA_DISPLAY_FILENAME_SUFFIX);
            
			NSString *newLastname = [name stringByReplacingOccurrencesOfString:CC_RETINA_DISPLAY_FILENAME_SUFFIX withString:@""];
			
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
    
	if( CC_CONTENT_SCALE_FACTOR() == 2 )
	{
		
		NSString *pathWithoutExtension = [path stringByDeletingPathExtension];
		NSString *name = [pathWithoutExtension lastPathComponent];
		
		// check if path already has the suffix.
		if( [name rangeOfString:CC_RETINA_DISPLAY_FILENAME_SUFFIX].location != NSNotFound ) {
            
			CCLOG(@"cocos2d: WARNING Filename(%@) already has the suffix %@. Using it.", name, CC_RETINA_DISPLAY_FILENAME_SUFFIX);			
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
		
		
		NSString *retinaName = [pathWithoutExtension stringByAppendingString:CC_RETINA_DISPLAY_FILENAME_SUFFIX];
		retinaName = [retinaName stringByAppendingPathExtension:extension];
        
                NSFileManager *fileManager = [[[NSFileManager alloc] init] autorelease];
		if( [fileManager fileExistsAtPath:retinaName] )
			return retinaName;
        
		CCLOG(@"cocos2d: CCFileUtils: Warning HD file not found: %@", [retinaName lastPathComponent] );
	}
	
#endif // CC_IS_RETINA_DISPLAY_SUPPORTED
	
	return path;
}

static const char* static_fullPathFromRelativePath(const char *pszRelativePath)

{
    
	NSAssert(pszRelativePath != nil, @"CCFileUtils: Invalid path");
    
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
    void plist_startElement(void *ctx, const xmlChar *name, const xmlChar **atts);
    void plist_endElement(void *ctx, const xmlChar *name);
    void plist_characters(void *ctx, const xmlChar *ch, int len);
    
    typedef enum 
    {
        SAX_NONE = 0,
        SAX_KEY,
        SAX_DICT,
        SAX_INT,
        SAX_REAL,
        SAX_STRING
    }CCSAXState;
    
    class CCDictMaker
    {
    public:
        NSDictionary<std::string, NSObject*> *m_pRootDict;
        NSDictionary<std::string, NSObject*> *m_pCurDict;
        std::stack<NSDictionary<std::string, NSObject*>*> m_tDictStack;
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
        NSDictionary<std::string, NSObject*> *dictionaryWithContentsOfFile(const char *pFileName)
        {
            FILE *fp = NULL;
            if( !(fp = fopen(pFileName, "r")) )
            {
                return NULL;
            }
            fseek(fp,0,SEEK_END);
            int size = ftell(fp);
            fseek(fp,0,SEEK_SET);
            char *buffer = new char[size+1];
            fread(buffer,sizeof(char),size,fp);
            fclose(fp);
            /*
             * this initialize the library and check potential ABI mismatches
             * between the version it was compiled for and the actual shared
             * library used.
             */
            LIBXML_TEST_VERSION
            xmlSAXHandler saxHandler;
            memset( &saxHandler, 0, sizeof(saxHandler) );
            // Using xmlSAXVersion( &saxHandler, 2 ) generate crash as it sets plenty of other pointers...
            saxHandler.initialized = XML_SAX2_MAGIC;  // so we do this to force parsing as SAX2.
            saxHandler.startElement = &plist_startElement;
            saxHandler.endElement = &plist_endElement;
            saxHandler.characters = &plist_characters;
            
            int result = xmlSAXUserParseMemory( &saxHandler, this, buffer, size );
            if ( result != 0 )
            {
                return NULL;
            }
            /*
             * Cleanup function for the XML library.
             */
            xmlCleanupParser();
            /*
             * this is to debug memory for regression tests
             */
            xmlMemoryDump();
            delete []buffer;
            return m_pRootDict;
        }
    };
    void plist_startElement(void *ctx, const xmlChar *name, const xmlChar **atts)
    {
        CCDictMaker *pMaker = (CCDictMaker*)(ctx);
        std::string sName((char*)name);
        if( sName == "dict" )
        {
            NSDictionary<std::string, NSObject*> *pNewDict = new NSDictionary<std::string, NSObject*>();
            if(! pMaker->m_pRootDict)
            {
                pMaker->m_pRootDict = pNewDict;
                pNewDict->autorelease();
            }
            else
            {
                NSAssert(pMaker->m_pCurDict && !pMaker->m_sCurKey.empty(), "");
                pMaker->m_pCurDict->setObject(pNewDict, pMaker->m_sCurKey);
                pNewDict->release();
                pMaker->m_sCurKey.clear();
            }
            pMaker->m_pCurDict = pNewDict;
            pMaker->m_tDictStack.push(pMaker->m_pCurDict);
            pMaker->m_tState = SAX_DICT;
        }
        else if(sName == "key")
        {
            pMaker->m_tState = SAX_KEY;
        }
        else if(sName == "integer")
        {
            pMaker->m_tState = SAX_INT;
        }
        else if(sName == "real")
        {
            pMaker->m_tState = SAX_REAL;
        }
        else if(sName == "string")
        {
            pMaker->m_tState = SAX_STRING;
        }
        else
        {
            pMaker->m_tState = SAX_NONE;
        }
    }
    void plist_endElement(void *ctx, const xmlChar *name)
    {
        CCDictMaker * pMaker = (CCDictMaker*)(ctx);
        std::string sName((char*)name);
        if( sName == "dict" )
        {
            pMaker->m_tDictStack.pop();
            if ( !pMaker->m_tDictStack.empty() )
            {
                pMaker->m_pCurDict = (NSDictionary<std::string, NSObject*>*)(pMaker->m_tDictStack.top());
            }
        }
        pMaker->m_tState = SAX_NONE;
    }
    void plist_characters(void *ctx, const xmlChar *ch, int len)
    {
        CCDictMaker * pMaker = (CCDictMaker*)(ctx);
        if (pMaker->m_tState == SAX_NONE)
        {
            return;
        }
        NSString *pText = new NSString();
        pText->m_sString = std::string((char*)ch,0,len);
        
        switch(pMaker->m_tState)
        {
            case SAX_KEY:
                pMaker->m_sCurKey = pText->m_sString;
                break;
            case SAX_INT:
            case SAX_REAL:
            case SAX_STRING:
            {
                NSAssert(!pMaker->m_sCurKey.empty(), "not found key : <integet/real>");
                pMaker->m_pCurDict->setObject(pText, pMaker->m_sCurKey);
                break;
            }
        }
        pText->release();
    }
    
    // record the resource path
    static char s_pszResourcePath[MAX_PATH] = {0};
    
    void CCFileUtils::setResourcePath(const char *pszResourcePath)
    {
        NSAssert(pszResourcePath != NULL, "[FileUtils setResourcePath] -- wrong resource path");
        NSAssert(strlen(pszResourcePath) <= MAX_PATH, "[FileUtils setResourcePath] -- resource path too long");
        
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
    
    const char* CCFileUtils::ccRemoveHDSuffixFromFile( const char *path )
    {
        return static_ccRemoveHDSuffixFromFile(path);
    }
    
    const char* CCFileUtils::fullPathFromRelativePath(const char *pszRelativePath)
    {
        return static_fullPathFromRelativePath(pszRelativePath);
    }
    
    const char *CCFileUtils::fullPathFromRelativeFile(const char *pszFilename, const char *pszRelativeFile)
    {
        std::string relativeFile = fullPathFromRelativePath(pszRelativeFile);
        NSString *pRet = new NSString();
        pRet->autorelease();
        pRet->m_sString = relativeFile.substr(0, relativeFile.rfind('/')+1);
        pRet->m_sString += pszFilename;
        return pRet->m_sString.c_str();
    }
    NSDictionary<std::string, NSObject*> *CCFileUtils::dictionaryWithContentsOfFile(const char *pFileName)
    {
        CCDictMaker tMaker;
        return tMaker.dictionaryWithContentsOfFile(pFileName);
    }	
}//namespace   cocos2d 
