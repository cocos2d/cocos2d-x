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

#include <string>
#include <stack>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xmlmemory.h>
#include <TG3.h>
#include "NSString.h"
#include "CCXFileUtils_uphone.h"
#include "CCXCocos2dDefine.h"

#include "support/file_support/FileData.h"
#include "support/zip_support/unzip.h"

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
        FileData data;
        unsigned long size = 0;
        char *pBuffer = (char *) data.getFileData(pFileName, "r", &size);

        if (!pBuffer)
        {
            return NULL;
        }

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

		int result = xmlSAXUserParseMemory( &saxHandler, this, pBuffer, size );
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
static char s_pszZipFilePath[MAX_PATH]  = {0};

void CCFileUtils::setResourcePath(const char *pszResourcePath)
{
    NSAssert(pszResourcePath != NULL, "[FileUtils setResourcePath] -- wrong resource path");
    NSAssert(strlen(pszResourcePath) <= MAX_PATH, "[FileUtils setResourcePath] -- resource path too long");

    strcpy(s_pszResourcePath, pszResourcePath);
}

void CCFileUtils::setResourceZipFile(const char* pszZipPath)
{
    NSAssert(pszZipPath != NULL, "[FileUtils setResourceZipFile] -- wrong zip file path");

    // if the zip file not exist,use message box to warn developer
    TUChar pszTmp[MAX_PATH] = {0};
    TUString::StrGBToUnicode(pszTmp, (const Char*) pszZipPath);
    Boolean bExist = EOS_IsFileExist(pszTmp);
    if (!bExist)
    {
        std::string strErr = "zip file ";
        strErr += pszZipPath;
        strErr += " not exist!";
        TUChar szText[MAX_PATH] = { 0 };
        TUString::StrUtf8ToStrUnicode(szText,(Char*)strErr.c_str());
        TApplication::GetCurrentApplication()->MessageBox(szText,NULL,WMB_OK);
        return;
    }

#ifndef _TRANZDA_VM_
    char *pszDriver = "";
#else
    char *pszDriver = "D:/Work7";
#endif
    NSAssert((strlen(pszDriver) + strlen(pszZipPath)) <= MAX_PATH, "[FileUtils setResourceZipFile] -- zip file path too long");

    // record the zip file path
    strcpy(s_pszZipFilePath, pszDriver);
    strcat(s_pszZipFilePath, pszZipPath);
}

const char* CCFileUtils::fullPathFromRelativePath(const char *pszRelativePath)
{
    // if have set the zip file path,return the relative path of zip file
    if (strlen(s_pszZipFilePath) != 0)
    {
        return CCFileUtils::getDiffResolutionPath(pszRelativePath);
    }

    // get the user data path and append relative path to it
    if (strlen(s_pszResourcePath) == 0)
    {
        const TUChar *pszTmp = EOS_GetSpecialPath(EOS_FILE_SPECIAL_PATH_USER_DATA);
        TUString::StrUnicodeToStrUtf8((Char*) s_pszResourcePath, pszTmp);
    }

#ifndef _TRANZDA_VM_
    char *pszDriver = "";
#else
    char *pszDriver = "D:/Work7";
#endif

    NSString * pRet = new NSString();
    pRet->autorelease();
    if ((strlen(pszRelativePath) > 1 && pszRelativePath[1] == ':'))
    {
        pRet->m_sString = pszRelativePath;
    }
    else if (strlen(pszRelativePath) > 0 && pszRelativePath[0] == '/')
    {
        pRet->m_sString = pszDriver;
        pRet->m_sString += pszRelativePath;
    }
    else
    {
        pRet->m_sString = pszDriver;
        pRet->m_sString += s_pszResourcePath;
        pRet->m_sString += pszRelativePath;
    }
    return CCFileUtils::getDiffResolutionPath(pRet->m_sString.c_str());
}
const char *CCFileUtils::fullPathFromRelativeFile(const char *pszFilename, const char *pszRelativeFile)
{
	std::string relativeFile = fullPathFromRelativePath(pszRelativeFile);
	NSString *pRet = new NSString();
	pRet->autorelease();
	pRet->m_sString = relativeFile.substr(0, relativeFile.rfind('/')+1);
	pRet->m_sString += pszFilename;
	return CCFileUtils::getDiffResolutionPath(pRet->m_sString.c_str());
}
NSDictionary<std::string, NSObject*> *CCFileUtils::dictionaryWithContentsOfFile(const char *pFileName)
{
	CCDictMaker tMaker;
	return tMaker.dictionaryWithContentsOfFile(pFileName);
}

const char* CCFileUtils::getDiffResolutionPath(const char *pszPath)
{
    NSString *pRet = new NSString(pszPath);
    pRet->autorelease();

    do 
    {
        TApplication* pApp = TApplication::GetCurrentApplication();
        CCX_BREAK_IF(!pApp);

        // get the Resolution
        int nScreenWidth  = pApp->GetScreenWidth();
        int nScreenHeight = pApp->GetScreenHeight();

        // it's default resolution, do nothing
        CCX_BREAK_IF(nScreenWidth == 320 && nScreenHeight == 480);

        if (nScreenWidth == 480 && nScreenHeight == 800)
        {
            // it's WVGA
            CCX_BREAK_IF(pRet->m_sString.find("@WVGA") != -1);

            std::string filePathWithoutExtension = pszPath;
            std::string extension = "";
            std::string filePath = pszPath;
            int nExPos = filePath.find_last_of(".");

            if (nExPos != -1)
            {
                filePathWithoutExtension = filePath.substr(0, nExPos);
                extension = filePath.substr(nExPos);
            }

            // new path, add "@WVGA" before the extension
            pRet->m_sString = filePathWithoutExtension + "@WVGA" + extension;

            // not find the resource of new path,use the original path
            if (! CCFileUtils::isResourceExist(pRet->m_sString.c_str()))
            {
                pRet->m_sString = filePath;
            }
        }
        else
        {
            // not support resolution
            NSAssert(0, "it's not supportted resolution.");
        }
    } while (0);

    return pRet->m_sString.c_str();
}

bool CCFileUtils::isResourceExist(const char* pszResName)
{
    bool bRet = false;

    TUChar FilePath[MAX_PATH] = {0};
    TUString::StrGBToUnicode(FilePath, (const Char *) pszResName);

    if (strlen(s_pszZipFilePath) != 0)
    {
        // if have set the zip file path,find the resource in the zip file
        unzFile pZipFile = unzOpen(s_pszZipFilePath);
        do 
        {
            CCX_BREAK_IF(!pZipFile);

            Int32 nPos = unzLocateFile(pZipFile, pszResName, 1);
            CCX_BREAK_IF(nPos != UNZ_OK);

            bRet = true;
            unzClose(pZipFile);
        } while (0);
    }
    else
    {
        // find in the hardware
        if (EOS_IsFileExist(FilePath))
        {
            bRet = true;
        }
    }

    return bRet;
}

unsigned char* CCFileUtils::getFileData(const char* pszFileName, const char* pszMode, unsigned long * pSize)
{
    unsigned char * pBuffer = NULL;

    do 
    {
        if (strlen(s_pszZipFilePath) != 0)
        {
            // if specify the zip file,load from it first
            pBuffer = FileUtils::getFileDataFromZip(s_pszZipFilePath, pszFileName, pSize);
            CCX_BREAK_IF(pBuffer);
        }

        // read the file from hardware
        FILE *fp = fopen(pszFileName, pszMode);
        CCX_BREAK_IF(!fp);

        fseek(fp,0,SEEK_END);
        *pSize = ftell(fp);
        fseek(fp,0,SEEK_SET);
        pBuffer = new unsigned char[*pSize];
        fread(pBuffer,sizeof(unsigned char), *pSize,fp);
        fclose(fp);
    } while (0);

    return pBuffer;
}

int CCFileUtils::ccLoadFileIntoMemory(const char *filename, unsigned char **out)
{
	///@todo
	return 0;
}

const char* CCFileUtils::ccRemoveHDSuffixFromFile( const char *path )
{
#if CC_IS_RETINA_DISPLAY_SUPPORTED

    if( CC_CONTENT_SCALE_FACTOR() == 2 )
    {
        std::string curPath = path;
        int pos = curPath.rfind("/");
        std::string fileName = curPath.substr(pos + 1);

        std::string filePath = "";
        if (-1 != pos)
        {
            filePath = curPath.substr(0, pos);
        }
        
        int suffixPos = fileName.rfind(CC_RETINA_DISPLAY_FILENAME_SUFFIX);
        if (-1 != suffixPos)
        {
            fileName.replace(pos, strlen(CC_RETINA_DISPLAY_FILENAME_SUFFIX), "");
        }
        
        std::string result = filePath + fileName;
        return result.c_str();
    }

#endif // CC_IS_RETINA_DISPLAY_SUPPORTED

    return path;
}
}//namespace   cocos2d 
