/****************************************************************************
Copyright (c) 2010-2013 cocos2d-x.org

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
#include "CCDirector.h"
#include "cocoa/CCDictionary.h"
#include "cocoa/CCString.h"
#include "CCSAXParser.h"
#include "support/tinyxml2/tinyxml2.h"
#include "support/zip_support/unzip.h"
#include <stack>

using namespace std;

#if (CC_TARGET_PLATFORM != CC_PLATFORM_IOS) && (CC_TARGET_PLATFORM != CC_PLATFORM_MAC)

NS_CC_BEGIN

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

typedef enum
{
    SAX_RESULT_NONE = 0,
    SAX_RESULT_DICT,
    SAX_RESULT_ARRAY
}CCSAXResult;

class CCDictMaker : public CCSAXDelegator
{
public:
    CCSAXResult _resultType;
    CCArray* _rootArray;
    CCDictionary *_rootDict;
    CCDictionary *_curDict;
    std::stack<CCDictionary*> _dictStack;
    std::string _curKey;   ///< parsed key
    std::string _curValue; // parsed value
    CCSAXState _state;
    CCArray* _array;

    std::stack<CCArray*> _arrayStack;
    std::stack<CCSAXState>  _stateStack;

public:
    CCDictMaker()        
        : _resultType(SAX_RESULT_NONE),
          _rootArray(NULL), 
          _rootDict(NULL),
          _curDict(NULL),
          _state(SAX_NONE),
          _array(NULL)
    {
    }

    ~CCDictMaker()
    {
    }

    CCDictionary* dictionaryWithContentsOfFile(const char *pFileName)
    {
        _resultType = SAX_RESULT_DICT;
        CCSAXParser parser;

        if (false == parser.init("UTF-8"))
        {
            return NULL;
        }
        parser.setDelegator(this);

        parser.parse(pFileName);
        return _rootDict;
    }

    CCArray* arrayWithContentsOfFile(const char* pFileName)
    {
        _resultType = SAX_RESULT_ARRAY;
        CCSAXParser parser;

        if (false == parser.init("UTF-8"))
        {
            return NULL;
        }
        parser.setDelegator(this);

        parser.parse(pFileName);
        return _array;
    }

    void startElement(void *ctx, const char *name, const char **atts)
    {
        CC_UNUSED_PARAM(ctx);
        CC_UNUSED_PARAM(atts);
        std::string sName((char*)name);
        if( sName == "dict" )
        {
            _curDict = new CCDictionary();
            if(_resultType == SAX_RESULT_DICT && _rootDict == NULL)
            {
                // Because it will call _curDict->release() later, so retain here.
                _rootDict = _curDict;
                _rootDict->retain();
            }
            _state = SAX_DICT;

            CCSAXState preState = SAX_NONE;
            if (! _stateStack.empty())
            {
                preState = _stateStack.top();
            }

            if (SAX_ARRAY == preState)
            {
                // add the dictionary into the array
                _array->addObject(_curDict);
            }
            else if (SAX_DICT == preState)
            {
                // add the dictionary into the pre dictionary
                CCAssert(! _dictStack.empty(), "The state is wrong!");
                CCDictionary* pPreDict = _dictStack.top();
                pPreDict->setObject(_curDict, _curKey.c_str());
            }

            _curDict->release();

            // record the dict state
            _stateStack.push(_state);
            _dictStack.push(_curDict);
        }
        else if(sName == "key")
        {
            _state = SAX_KEY;
        }
        else if(sName == "integer")
        {
            _state = SAX_INT;
        }
        else if(sName == "real")
        {
            _state = SAX_REAL;
        }
        else if(sName == "string")
        {
            _state = SAX_STRING;
        }
        else if (sName == "array")
        {
            _state = SAX_ARRAY;
            _array = new CCArray();
            if (_resultType == SAX_RESULT_ARRAY && _rootArray == NULL)
            {
                _rootArray = _array;
                _rootArray->retain();
            }
            CCSAXState preState = SAX_NONE;
            if (! _stateStack.empty())
            {
                preState = _stateStack.top();
            }

            if (preState == SAX_DICT)
            {
                _curDict->setObject(_array, _curKey.c_str());
            }
            else if (preState == SAX_ARRAY)
            {
                CCAssert(! _arrayStack.empty(), "The state is wrong!");
                CCArray* pPreArray = _arrayStack.top();
                pPreArray->addObject(_array);
            }
            _array->release();
            // record the array state
            _stateStack.push(_state);
            _arrayStack.push(_array);
        }
        else
        {
            _state = SAX_NONE;
        }
    }

    void endElement(void *ctx, const char *name)
    {
        CC_UNUSED_PARAM(ctx);
        CCSAXState curState = _stateStack.empty() ? SAX_DICT : _stateStack.top();
        std::string sName((char*)name);
        if( sName == "dict" )
        {
            _stateStack.pop();
            _dictStack.pop();
            if ( !_dictStack.empty())
            {
                _curDict = _dictStack.top();
            }
        }
        else if (sName == "array")
        {
            _stateStack.pop();
            _arrayStack.pop();
            if (! _arrayStack.empty())
            {
                _array = _arrayStack.top();
            }
        }
        else if (sName == "true")
        {
            CCString *str = new CCString("1");
            if (SAX_ARRAY == curState)
            {
                _array->addObject(str);
            }
            else if (SAX_DICT == curState)
            {
                _curDict->setObject(str, _curKey.c_str());
            }
            str->release();
        }
        else if (sName == "false")
        {
            CCString *str = new CCString("0");
            if (SAX_ARRAY == curState)
            {
                _array->addObject(str);
            }
            else if (SAX_DICT == curState)
            {
                _curDict->setObject(str, _curKey.c_str());
            }
            str->release();
        }
        else if (sName == "string" || sName == "integer" || sName == "real")
        {
            CCString* pStrValue = new CCString(_curValue);

            if (SAX_ARRAY == curState)
            {
                _array->addObject(pStrValue);
            }
            else if (SAX_DICT == curState)
            {
                _curDict->setObject(pStrValue, _curKey.c_str());
            }

            pStrValue->release();
            _curValue.clear();
        }
        
        _state = SAX_NONE;
    }

    void textHandler(void *ctx, const char *ch, int len)
    {
        CC_UNUSED_PARAM(ctx);
        if (_state == SAX_NONE)
        {
            return;
        }

        CCSAXState curState = _stateStack.empty() ? SAX_DICT : _stateStack.top();
        CCString *pText = new CCString(std::string((char*)ch,0,len));

        switch(_state)
        {
        case SAX_KEY:
            _curKey = pText->getCString();
            break;
        case SAX_INT:
        case SAX_REAL:
        case SAX_STRING:
            {
                if (curState == SAX_DICT)
                {
                    CCAssert(!_curKey.empty(), "key not found : <integer/real>");
                }
                
                _curValue.append(pText->getCString());
            }
            break;
        default:
            break;
        }
        pText->release();
    }
};

CCDictionary* CCFileUtils::createCCDictionaryWithContentsOfFile(const std::string& filename)
{
    std::string fullPath = fullPathForFilename(filename.c_str());
    CCDictMaker tMaker;
    return tMaker.dictionaryWithContentsOfFile(fullPath.c_str());
}

CCArray* CCFileUtils::createCCArrayWithContentsOfFile(const std::string& filename)
{
    std::string fullPath = fullPathForFilename(filename.c_str());
    CCDictMaker tMaker;
    return tMaker.arrayWithContentsOfFile(fullPath.c_str());
}

/*
 * forward statement
 */
static tinyxml2::XMLElement* generateElementForArray(cocos2d::CCArray *array, tinyxml2::XMLDocument *pDoc);
static tinyxml2::XMLElement* generateElementForDict(cocos2d::CCDictionary *dict, tinyxml2::XMLDocument *pDoc);

/*
 * Use tinyxml2 to write plist files
 */
bool CCFileUtils::writeToFile(cocos2d::CCDictionary *dict, const std::string &fullPath)
{
    //CCLOG("tinyxml2 CCDictionary %d writeToFile %s", dict->_ID, fullPath.c_str());
    tinyxml2::XMLDocument *pDoc = new tinyxml2::XMLDocument();
    if (NULL == pDoc)
        return false;
    
    tinyxml2::XMLDeclaration *pDeclaration = pDoc->NewDeclaration("xml version=\"1.0\" encoding=\"UTF-8\"");
    if (NULL == pDeclaration)
    {
        delete pDoc;
        return false;
    }
    
    pDoc->LinkEndChild(pDeclaration);
    tinyxml2::XMLElement *docType = pDoc->NewElement("!DOCTYPE plist PUBLIC \"-//Apple//DTD PLIST 1.0//EN\" \"http://www.apple.com/DTDs/PropertyList-1.0.dtd\"");
    pDoc->LinkEndChild(docType);
    
    tinyxml2::XMLElement *pRootEle = pDoc->NewElement("plist");
    pRootEle->SetAttribute("version", "1.0");
    if (NULL == pRootEle)
    {
        delete pDoc;
        return false;
    }
    pDoc->LinkEndChild(pRootEle);
    
    tinyxml2::XMLElement *innerDict = generateElementForDict(dict, pDoc);
    if (NULL == innerDict )
    {
        delete pDoc;
        return false;
    }
    pRootEle->LinkEndChild(innerDict);
    
    bool bRet = tinyxml2::XML_SUCCESS == pDoc->SaveFile(fullPath.c_str());
    
    delete pDoc;
    return bRet;
}

/*
 * Generate tinyxml2::XMLElement for CCObject through a tinyxml2::XMLDocument
 */
static tinyxml2::XMLElement* generateElementForObject(cocos2d::CCObject *object, tinyxml2::XMLDocument *pDoc)
{
    // object is CCString
    if (CCString *str = dynamic_cast<CCString *>(object))
    {
        tinyxml2::XMLElement* node = pDoc->NewElement("string");
        tinyxml2::XMLText* content = pDoc->NewText(str->getCString());
        node->LinkEndChild(content);
        return node;
    }
    
    // object is CCArray
    if (CCArray *array = dynamic_cast<CCArray *>(object))
        return generateElementForArray(array, pDoc);
    
    // object is CCDictionary
    if (CCDictionary *innerDict = dynamic_cast<CCDictionary *>(object))
        return generateElementForDict(innerDict, pDoc);
    
    CCLOG("This type cannot appear in property list");
    return NULL;
}

/*
 * Generate tinyxml2::XMLElement for CCDictionary through a tinyxml2::XMLDocument
 */
static tinyxml2::XMLElement* generateElementForDict(cocos2d::CCDictionary *dict, tinyxml2::XMLDocument *pDoc)
{
    tinyxml2::XMLElement* rootNode = pDoc->NewElement("dict");
    
    CCDictElement *dictElement = NULL;
    CCDICT_FOREACH(dict, dictElement)
    {
        tinyxml2::XMLElement* tmpNode = pDoc->NewElement("key");
        rootNode->LinkEndChild(tmpNode);
        tinyxml2::XMLText* content = pDoc->NewText(dictElement->getStrKey());
        tmpNode->LinkEndChild(content);
        
        CCObject *object = dictElement->getObject();
        tinyxml2::XMLElement *element = generateElementForObject(object, pDoc);
        if (element)
            rootNode->LinkEndChild(element);
    }
    return rootNode;
}

/*
 * Generate tinyxml2::XMLElement for CCArray through a tinyxml2::XMLDocument
 */
static tinyxml2::XMLElement* generateElementForArray(cocos2d::CCArray *array, tinyxml2::XMLDocument *pDoc)
{
    tinyxml2::XMLElement* rootNode = pDoc->NewElement("array");
    
    CCObject *object = NULL;
    CCARRAY_FOREACH(array, object)
    {
        tinyxml2::XMLElement *element = generateElementForObject(object, pDoc);
        if (element)
            rootNode->LinkEndChild(element);
    }
    return rootNode;
}


#else
NS_CC_BEGIN

/* The subclass CCFileUtilsIOS and CCFileUtilsMac should override these two method. */
CCDictionary* CCFileUtils::createCCDictionaryWithContentsOfFile(const std::string& filename) {return NULL;}
bool CCFileUtils::writeToFile(cocos2d::CCDictionary *dict, const std::string &fullPath) {return NULL;}
CCArray* CCFileUtils::createCCArrayWithContentsOfFile(const std::string& filename) {return NULL;}

#endif /* (CC_TARGET_PLATFORM != CC_PLATFORM_IOS) && (CC_TARGET_PLATFORM != CC_PLATFORM_MAC) */


CCFileUtils* CCFileUtils::s_sharedFileUtils = NULL;

void CCFileUtils::purgeFileUtils()
{
    CC_SAFE_DELETE(s_sharedFileUtils);
}

CCFileUtils::CCFileUtils()
: _filenameLookupDict(NULL)
{
}

CCFileUtils::~CCFileUtils()
{
    CC_SAFE_RELEASE(_filenameLookupDict);
}

bool CCFileUtils::init()
{
    _searchPathArray.push_back(_defaultResRootPath);
    _searchResolutionsOrderArray.push_back("");
    return true;
}

void CCFileUtils::purgeCachedEntries()
{
    _fullPathCache.clear();
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
    
    if (! pBuffer)
    {
        std::string msg = "Get data from file(";
        msg.append(pszFileName).append(") failed!");
        
        CCLOG("%s", msg.c_str());
    }
    return pBuffer;
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
        int CC_UNUSED nSize = unzReadCurrentFile(pFile, pBuffer, FileInfo.uncompressed_size);
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

std::string CCFileUtils::getNewFilename(const char* pszFileName)
{
    const char* pszNewFileName = NULL;
    // in Lookup Filename dictionary ?
    CCString* fileNameFound = _filenameLookupDict ? (CCString*)_filenameLookupDict->objectForKey(pszFileName) : NULL;
    if( NULL == fileNameFound || fileNameFound->length() == 0) {
        pszNewFileName = pszFileName;
    }
    else {
        pszNewFileName = fileNameFound->getCString();
        //CCLOG("FOUND NEW FILE NAME: %s.", pszNewFileName);
    }
    return pszNewFileName;
}

std::string CCFileUtils::getPathForFilename(const std::string& filename, const std::string& resolutionDirectory, const std::string& searchPath)
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
    path += file_path;
    path += resolutionDirectory;
    
    path = getFullPathForDirectoryAndFilename(path, file);
    
    //CCLOG("getPathForFilename, fullPath = %s", path.c_str());
    return path;
}


std::string CCFileUtils::fullPathForFilename(const char* pszFileName)
{
    CCAssert(pszFileName != NULL, "CCFileUtils: Invalid path");
    
    std::string strFileName = pszFileName;
    if (isAbsolutePath(pszFileName))
    {
        //CCLOG("Return absolute path( %s ) directly.", pszFileName);
        return pszFileName;
    }
    
    // Already Cached ?
    std::map<std::string, std::string>::iterator cacheIter = _fullPathCache.find(pszFileName);
    if (cacheIter != _fullPathCache.end())
    {
        //CCLOG("Return full path from cache: %s", cacheIter->second.c_str());
        return cacheIter->second;
    }
    
    // Get the new file name.
    std::string newFilename = getNewFilename(pszFileName);
    
    string fullpath = "";
    
    for (std::vector<std::string>::iterator searchPathsIter = _searchPathArray.begin();
         searchPathsIter != _searchPathArray.end(); ++searchPathsIter) {
        for (std::vector<std::string>::iterator resOrderIter = _searchResolutionsOrderArray.begin();
             resOrderIter != _searchResolutionsOrderArray.end(); ++resOrderIter) {
            
            //CCLOG("\n\nSEARCHING: %s, %s, %s", newFilename.c_str(), resOrderIter->c_str(), searchPathsIter->c_str());
            
            fullpath = this->getPathForFilename(newFilename, *resOrderIter, *searchPathsIter);
            
            if (fullpath.length() > 0)
            {
                // Using the filename passed in as key.
                _fullPathCache.insert(std::pair<std::string, std::string>(pszFileName, fullpath));
                //CCLOG("Returning path: %s", fullpath.c_str());
                return fullpath;
            }
        }
    }
    
    //CCLOG("cocos2d: fullPathForFilename: No file found at %s. Possible missing file.", pszFileName);

    // The file wasn't found, return the file name passed in.
    return pszFileName;
}

const char* CCFileUtils::fullPathFromRelativeFile(const char *pszFilename, const char *pszRelativeFile)
{
    std::string relativeFile = pszRelativeFile;
    CCString *pRet = CCString::create("");
    pRet->_string = relativeFile.substr(0, relativeFile.rfind('/')+1);
    pRet->_string += getNewFilename(pszFilename);
    return pRet->getCString();
}

void CCFileUtils::setSearchResolutionsOrder(const std::vector<std::string>& searchResolutionsOrder)
{
    bool bExistDefault = false;
    _searchResolutionsOrderArray.clear();
    for (std::vector<std::string>::const_iterator iter = searchResolutionsOrder.begin(); iter != searchResolutionsOrder.end(); ++iter)
    {
        std::string resolutionDirectory = *iter;
        if (!bExistDefault && resolutionDirectory == "")
        {
            bExistDefault = true;
        }
        
        if (resolutionDirectory.length() > 0 && resolutionDirectory[resolutionDirectory.length()-1] != '/')
        {
            resolutionDirectory += "/";
        }
        
        _searchResolutionsOrderArray.push_back(resolutionDirectory);
    }
    if (!bExistDefault)
    {
        _searchResolutionsOrderArray.push_back("");
    }
}

void CCFileUtils::addSearchResolutionsOrder(const char* order)
{
    _searchResolutionsOrderArray.push_back(order);
}

const std::vector<std::string>& CCFileUtils::getSearchResolutionsOrder()
{
    return _searchResolutionsOrderArray;
}

const std::vector<std::string>& CCFileUtils::getSearchPaths()
{
    return _searchPathArray;
}

void CCFileUtils::setSearchPaths(const std::vector<std::string>& searchPaths)
{
    bool bExistDefaultRootPath = false;
    
    _searchPathArray.clear();
    for (std::vector<std::string>::const_iterator iter = searchPaths.begin(); iter != searchPaths.end(); ++iter)
    {
        std::string strPrefix;
        std::string path;
        if (!isAbsolutePath(*iter))
        { // Not an absolute path
            strPrefix = _defaultResRootPath;
        }
        path = strPrefix+(*iter);
        if (path.length() > 0 && path[path.length()-1] != '/')
        {
            path += "/";
        }
        if (!bExistDefaultRootPath && path == _defaultResRootPath)
        {
            bExistDefaultRootPath = true;
        }
        _searchPathArray.push_back(path);
    }
    
    if (!bExistDefaultRootPath)
    {
        //CCLOG("Default root path doesn't exist, adding it.");
        _searchPathArray.push_back(_defaultResRootPath);
    }
}

void CCFileUtils::addSearchPath(const char* path_)
{
    std::string strPrefix;
    std::string path(path_);
    if (!isAbsolutePath(path))
    { // Not an absolute path
        strPrefix = _defaultResRootPath;
    }
    path = strPrefix + path;
    if (path.length() > 0 && path[path.length()-1] != '/')
    {
        path += "/";
    }
    _searchPathArray.push_back(path);
}

void CCFileUtils::setFilenameLookupDictionary(CCDictionary* pFilenameLookupDict)
{
    CC_SAFE_RELEASE(_filenameLookupDict);
    _filenameLookupDict = pFilenameLookupDict;
    CC_SAFE_RETAIN(_filenameLookupDict);
}

void CCFileUtils::loadFilenameLookupDictionaryFromFile(const char* filename)
{
    std::string fullPath = this->fullPathForFilename(filename);
    if (fullPath.length() > 0)
    {
        CCDictionary* pDict = CCDictionary::createWithContentsOfFile(fullPath.c_str());
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

std::string CCFileUtils::getFullPathForDirectoryAndFilename(const std::string& strDirectory, const std::string& strFilename)
{
    std::string ret = strDirectory+strFilename;
    if (!isFileExist(ret)) {
        ret = "";
    }
    return ret;
}

bool CCFileUtils::isAbsolutePath(const std::string& strPath)
{
    return strPath[0] == '/' ? true : false;
}

//////////////////////////////////////////////////////////////////////////
// Notification support when getFileData from invalid file path.
//////////////////////////////////////////////////////////////////////////
static bool s_bPopupNotify = true;

void CCFileUtils::setPopupNotify(bool bNotify)
{
    s_bPopupNotify = bNotify;
}

bool CCFileUtils::isPopupNotify()
{
    return s_bPopupNotify;
}

NS_CC_END

