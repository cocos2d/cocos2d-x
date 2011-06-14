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
    SAX_STRING,
    SAX_ARRAY
}CCSAXState;

class CCDictMaker : public CCSAXDelegator
{
public:
    CCDictionary<std::string, CCObject*> *m_pRootDict;
    CCDictionary<std::string, CCObject*> *m_pCurDict;
    std::stack<CCDictionary<std::string, CCObject*>*> m_tDictStack;
    std::string m_sCurKey;///< parsed key
    CCSAXState m_tState;
    CCMutableArray<CCObject*> *m_pArray;

    std::stack<CCMutableArray<CCObject*>*> m_tArrayStack;
    std::stack<CCSAXState>  m_tStateStack;

public:
    CCDictMaker()
		: m_pRootDict(NULL),
		  m_pCurDict(NULL),
          m_tState(SAX_NONE),
          m_pArray(NULL)
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
        CC_UNUSED_PARAM(ctx);
        CC_UNUSED_PARAM(atts);
        std::string sName((char*)name);
        if( sName == "dict" )
        {
            m_pCurDict = new CCDictionary<std::string, CCObject*>();
            if(! m_pRootDict)
            {
                m_pRootDict = m_pCurDict;
            }
            m_tState = SAX_DICT;

            CCSAXState preState = SAX_NONE;
            if (! m_tStateStack.empty())
            {
                preState = m_tStateStack.top();
            }

            if (SAX_ARRAY == preState)
            {
                // add the dictionary into the array
                m_pArray->addObject(m_pCurDict);
            }
            else if (SAX_DICT == preState)
            {
                // add the dictionary into the pre dictionary
                CCAssert(! m_tDictStack.empty(), "The state is wrong!");
                CCDictionary<std::string, CCObject*>* pPreDict = m_tDictStack.top();
                pPreDict->setObject(m_pCurDict, m_sCurKey);
            }
            m_pCurDict->autorelease();

            // record the dict state
            m_tStateStack.push(m_tState);
            m_tDictStack.push(m_pCurDict);
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
        else if (sName == "array")
        {
            m_tState = SAX_ARRAY;
            m_pArray = new CCMutableArray<CCObject*>();

            CCSAXState preState = m_tStateStack.empty() ? SAX_DICT : m_tStateStack.top();
            if (preState == SAX_DICT)
            {
                m_pCurDict->setObject(m_pArray, m_sCurKey);
            }
            else if (preState == SAX_ARRAY)
            {
                CCAssert(! m_tArrayStack.empty(), "The state is worng!");
                CCMutableArray<CCObject*>* pPreArray = m_tArrayStack.top();
                pPreArray->addObject(m_pArray);
            }
            m_pArray->release();
            // record the array state
            m_tStateStack.push(m_tState);
            m_tArrayStack.push(m_pArray);
        }
        else
        {
            m_tState = SAX_NONE;
        }
    }

    void endElement(void *ctx, const char *name)
    {
        CC_UNUSED_PARAM(ctx);
        CCSAXState curState = m_tStateStack.empty() ? SAX_DICT : m_tStateStack.top();
        std::string sName((char*)name);
        if( sName == "dict" )
        {
            m_tStateStack.pop();
            m_tDictStack.pop();
            if ( !m_tDictStack.empty())
            {
                m_pCurDict = m_tDictStack.top();
            }
        }
        else if (sName == "array")
        {
            m_tStateStack.pop();
            m_tArrayStack.pop();
            if (! m_tArrayStack.empty())
            {
                m_pArray = m_tArrayStack.top();
            }
        }
        else if (sName == "true")
        {
            CCString *str = new CCString("1");
            if (SAX_ARRAY == curState)
            {
                m_pArray->addObject(str);
            }
            else if (SAX_DICT == curState)
            {
                m_pCurDict->setObject(str, m_sCurKey);
            }
            str->release();
        }
        else if (sName == "false")
        {
            CCString *str = new CCString("0");
            if (SAX_ARRAY == curState)
            {
                m_pArray->addObject(str);
            }
            else if (SAX_DICT == curState)
            {
                m_pCurDict->setObject(str, m_sCurKey);
            }
            str->release();
        }
        m_tState = SAX_NONE;
    }

    void textHandler(void *ctx, const char *ch, int len)
    {
        CC_UNUSED_PARAM(ctx);
        if (m_tState == SAX_NONE)
        {
            return;
        }

        CCSAXState curState = m_tStateStack.empty() ? SAX_DICT : m_tStateStack.top();
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

                if (SAX_ARRAY == curState)
                {
                    m_pArray->addObject(pText);
                }
                else if (SAX_DICT == curState)
                {
                    m_pCurDict->setObject(pText, m_sCurKey);
                }
                break;
            }
        default:
            break;
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
