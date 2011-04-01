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

#include "CCFileUtils.h"

#if (CC_TARGET_PLATFORM != CC_PLATFORM_IOS) && (CC_TARGET_PLATFORM != CC_PLATFORM_AIRPLAY)

#include <stack>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xmlmemory.h>
#include "CCLibxml2.h"
#include "CCString.h"
#include "CCSAXParser.h"
#include "support/zip_support/unzip.h"

NS_CC_BEGIN;

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
    bool    m_bInArray;
    CCMutableArray<CCObject*> *m_pArray;

public:
    CCDictMaker()
		: m_pRootDict(NULL),
		  m_pCurDict(NULL),
          m_tState(SAX_NONE),
          m_pArray(NULL),
		  m_bInArray(false)
    {
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
            if (sName == "array")
            {
                m_bInArray = true;
                m_pArray = new CCMutableArray<CCObject*>();
            }
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
        else if (sName == "array")
        {
            CCAssert(m_bInArray, "The plist file is wrong!");
            m_pCurDict->setObject(m_pArray, m_sCurKey);
            m_pArray->release();
            m_pArray = NULL;
            m_bInArray = false;
        }
        else if (sName == "true")
        {
            CCString *str = new CCString("1");
            if (m_bInArray)
            {
                m_pArray->addObject(str);
            }
            else
            {
                m_pCurDict->setObject(str, m_sCurKey);
            }
            str->release();
        }
        else if (sName == "false")
        {
            CCString *str = new CCString("0");
            if (m_bInArray)
            {
                m_pArray->addObject(str);
            }
            else
            {
                m_pCurDict->setObject(str, m_sCurKey);
            }
            str->release();
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

                if (m_bInArray)
                {
                    m_pArray->addObject(pText);
                }
                else
                {
                    m_pCurDict->setObject(pText, m_sCurKey);
                }
                break;
            }
        }
        pText->release();
    }
};

std::string& CCFileUtils::ccRemoveHDSuffixFromFile(std::string& path)
{
#if CC_IS_RETINA_DISPLAY_SUPPORTED

    if( CC_CONTENT_SCALE_FACTOR() == 2 )
    {
        std::string::size_type pos = path.rfind("/") + 1; // the begin index of last part of path

        std::string::size_type suffixPos = path.rfind(CC_RETINA_DISPLAY_FILENAME_SUFFIX);
        if (std::string::npos != suffixPos && suffixPos > pos)
        {
            CCLog("cocos2d: FilePath(%s) contains suffix(%s), remove it.", path.c_str(),
                CC_RETINA_DISPLAY_FILENAME_SUFFIX);
            path.replace(suffixPos, strlen(CC_RETINA_DISPLAY_FILENAME_SUFFIX), "");
        }
    }

#endif // CC_IS_RETINA_DISPLAY_SUPPORTED

    return path;
}

CCDictionary<std::string, CCObject*> *CCFileUtils::dictionaryWithContentsOfFile(const char *pFileName)
{
    CCDictMaker tMaker;
    return tMaker.dictionaryWithContentsOfFile(pFileName);
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
        CCAssert(nSize == 0 || nSize == FileInfo.uncompressed_size, "the file size is wrong");

        *pSize = FileInfo.uncompressed_size;
        unzCloseCurrentFile(pFile);
    } while (0);

    if (pFile)
    {
        unzClose(pFile);
    }

    return pBuffer;
}

//////////////////////////////////////////////////////////////////////////
// Notification support when getFileData from invalid file path.
//////////////////////////////////////////////////////////////////////////
static bool s_bPopupNotify = true;

void CCFileUtils::setIsPopupNotify(bool bNotify)
{
    s_bPopupNotify = bNotify;
}

bool CCFileUtils::getIsPopupNotify()
{
    return s_bPopupNotify;
}

NS_CC_END;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include "win32/CCFileUtils_win32.cpp"
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WOPHONE)
#include "wophone/CCFileUtils_wophone.cpp"
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "android/CCFileUtils_android.cpp"
#endif

#endif // (CC_TARGET_PLATFORM != CC_PLATFORM_IOS && CC_TARGET_PLATFORM != CC_PLATFORM_AIRPLAY)
