/****************************************************************************
Copyright (c) 2010-2013 cocos2d-x.org
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

#include "CCFileUtils.h"

#include <stack>

#include "base/CCData.h"
#include "base/ccMacros.h"
#include "base/CCDirector.h"
#include "platform/CCSAXParser.h"
#include "base/ccUtils.h"

#include "tinyxml2.h"
#ifdef MINIZIP_FROM_SYSTEM
#include <minizip/unzip.h>
#else // from our embedded sources
#include "unzip.h"
#endif
#include <sys/stat.h>

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_WINRT || CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
#include <regex>
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
#include <ftw.h>
#endif

#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32) && (CC_TARGET_PLATFORM != CC_PLATFORM_WP8) && (CC_TARGET_PLATFORM != CC_PLATFORM_WINRT)
#include <sys/types.h>
#include <errno.h>
#include <dirent.h>
#endif

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
}SAXState;

typedef enum
{
    SAX_RESULT_NONE = 0,
    SAX_RESULT_DICT,
    SAX_RESULT_ARRAY
}SAXResult;

class DictMaker : public SAXDelegator
{
public:
    SAXResult _resultType;
	ValueMap _rootDict;
	ValueVector _rootArray;

    std::string _curKey;   ///< parsed key
    std::string _curValue; // parsed value
    SAXState _state;

	ValueMap*  _curDict;
    ValueVector* _curArray;

	std::stack<ValueMap*> _dictStack;
    std::stack<ValueVector*> _arrayStack;
    std::stack<SAXState>  _stateStack;

public:
    DictMaker()        
        : _resultType(SAX_RESULT_NONE)
    {
    }

    ~DictMaker()
    {
    }

    ValueMap dictionaryWithContentsOfFile(const std::string& fileName)
    {
        _resultType = SAX_RESULT_DICT;
        SAXParser parser;

        CCASSERT(parser.init("UTF-8"), "The file format isn't UTF-8");
        parser.setDelegator(this);

        parser.parse(fileName);
		return _rootDict;
    }

	ValueMap dictionaryWithDataOfFile(const char* filedata, int filesize)
	{
		_resultType = SAX_RESULT_DICT;
		SAXParser parser;

		CCASSERT(parser.init("UTF-8"), "The file format isn't UTF-8");
		parser.setDelegator(this);

		parser.parse(filedata, filesize);
		return _rootDict;
	}

    ValueVector arrayWithContentsOfFile(const std::string& fileName)
    {
        _resultType = SAX_RESULT_ARRAY;
        SAXParser parser;

        CCASSERT(parser.init("UTF-8"), "The file format isn't UTF-8");
        parser.setDelegator(this);

        parser.parse(fileName);
		return _rootArray;
    }

    void startElement(void *ctx, const char *name, const char **atts)
    {
        CC_UNUSED_PARAM(ctx);
        CC_UNUSED_PARAM(atts);
        const std::string sName(name);
        if( sName == "dict" )
        {
			if(_resultType == SAX_RESULT_DICT && _rootDict.empty())
            {
                _curDict = &_rootDict;
            }

            _state = SAX_DICT;

            SAXState preState = SAX_NONE;
            if (! _stateStack.empty())
            {
                preState = _stateStack.top();
            }

            if (SAX_ARRAY == preState)
            {
                // add a new dictionary into the array
                _curArray->push_back(Value(ValueMap()));
				_curDict = &(_curArray->rbegin())->asValueMap();
            }
            else if (SAX_DICT == preState)
            {
                // add a new dictionary into the pre dictionary
                CCASSERT(! _dictStack.empty(), "The state is wrong!");
                ValueMap* preDict = _dictStack.top();
                (*preDict)[_curKey] = Value(ValueMap());
				_curDict = &(*preDict)[_curKey].asValueMap();
            }

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

			if (_resultType == SAX_RESULT_ARRAY && _rootArray.empty())
            {
				_curArray = &_rootArray;
            }
            SAXState preState = SAX_NONE;
            if (! _stateStack.empty())
            {
                preState = _stateStack.top();
            }

            if (preState == SAX_DICT)
            {
                (*_curDict)[_curKey] = Value(ValueVector());
				_curArray = &(*_curDict)[_curKey].asValueVector();
            }
            else if (preState == SAX_ARRAY)
            {
                CCASSERT(! _arrayStack.empty(), "The state is wrong!");
                ValueVector* preArray = _arrayStack.top();
                preArray->push_back(Value(ValueVector()));
				_curArray = &(_curArray->rbegin())->asValueVector();
            }
            // record the array state
            _stateStack.push(_state);
            _arrayStack.push(_curArray);
        }
        else
        {
            _state = SAX_NONE;
        }
    }

    void endElement(void *ctx, const char *name)
    {
        CC_UNUSED_PARAM(ctx);
        SAXState curState = _stateStack.empty() ? SAX_DICT : _stateStack.top();
        const std::string sName((char*)name);
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
                _curArray = _arrayStack.top();
            }
        }
        else if (sName == "true")
        {
            if (SAX_ARRAY == curState)
            {
                _curArray->push_back(Value(true));
            }
            else if (SAX_DICT == curState)
            {
                (*_curDict)[_curKey] = Value(true);
            }
        }
        else if (sName == "false")
        {
            if (SAX_ARRAY == curState)
            {
                _curArray->push_back(Value(false));
            }
            else if (SAX_DICT == curState)
            {
                (*_curDict)[_curKey] = Value(false);
            }
        }
        else if (sName == "string" || sName == "integer" || sName == "real")
        {
            if (SAX_ARRAY == curState)
            {
                if (sName == "string")
                    _curArray->push_back(Value(_curValue));
                else if (sName == "integer")
                    _curArray->push_back(Value(atoi(_curValue.c_str())));
                else
                    _curArray->push_back(Value(utils::atof(_curValue.c_str())));
            }
            else if (SAX_DICT == curState)
            {
                if (sName == "string")
                    (*_curDict)[_curKey] = Value(_curValue);
                else if (sName == "integer")
                    (*_curDict)[_curKey] = Value(atoi(_curValue.c_str()));
                else
                    (*_curDict)[_curKey] = Value(utils::atof(_curValue.c_str()));
            }

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

        SAXState curState = _stateStack.empty() ? SAX_DICT : _stateStack.top();
        const std::string text = std::string((char*)ch,len);

        switch(_state)
        {
        case SAX_KEY:
            _curKey = text;
            break;
        case SAX_INT:
        case SAX_REAL:
        case SAX_STRING:
            {
                if (curState == SAX_DICT)
                {
                    CCASSERT(!_curKey.empty(), "key not found : <integer/real>");
                }
                
                _curValue.append(text);
            }
            break;
        default:
            break;
        }
    }
};

ValueMap FileUtils::getValueMapFromFile(const std::string& filename)
{
    const std::string fullPath = fullPathForFilename(filename.c_str());
    DictMaker tMaker;
    return tMaker.dictionaryWithContentsOfFile(fullPath.c_str());
}

ValueMap FileUtils::getValueMapFromData(const char* filedata, int filesize)
{
    DictMaker tMaker;
    return tMaker.dictionaryWithDataOfFile(filedata, filesize);
}

ValueVector FileUtils::getValueVectorFromFile(const std::string& filename)
{
    const std::string fullPath = fullPathForFilename(filename.c_str());
    DictMaker tMaker;
    return tMaker.arrayWithContentsOfFile(fullPath.c_str());
}


/*
 * forward statement
 */
static tinyxml2::XMLElement* generateElementForArray(const ValueVector& array, tinyxml2::XMLDocument *doc);
static tinyxml2::XMLElement* generateElementForDict(const ValueMap& dict, tinyxml2::XMLDocument *doc);

/*
 * Use tinyxml2 to write plist files
 */
bool FileUtils::writeToFile(ValueMap& dict, const std::string &fullPath)
{
    //CCLOG("tinyxml2 Dictionary %d writeToFile %s", dict->_ID, fullPath.c_str());
    tinyxml2::XMLDocument *doc = new tinyxml2::XMLDocument();
    if (nullptr == doc)
        return false;
    
    tinyxml2::XMLDeclaration *declaration = doc->NewDeclaration("xml version=\"1.0\" encoding=\"UTF-8\"");
    if (nullptr == declaration)
    {
        delete doc;
        return false;
    }
    
    doc->LinkEndChild(declaration);
    tinyxml2::XMLElement *docType = doc->NewElement("!DOCTYPE plist PUBLIC \"-//Apple//DTD PLIST 1.0//EN\" \"http://www.apple.com/DTDs/PropertyList-1.0.dtd\"");
    doc->LinkEndChild(docType);
    
    tinyxml2::XMLElement *rootEle = doc->NewElement("plist");
    rootEle->SetAttribute("version", "1.0");
    if (nullptr == rootEle)
    {
        delete doc;
        return false;
    }
    doc->LinkEndChild(rootEle);
    
    tinyxml2::XMLElement *innerDict = generateElementForDict(dict, doc);
    if (nullptr == innerDict )
    {
        delete doc;
        return false;
    }
    rootEle->LinkEndChild(innerDict);
    
    bool ret = tinyxml2::XML_SUCCESS == doc->SaveFile(fullPath.c_str());
    
    delete doc;
    return ret;
}

/*
 * Generate tinyxml2::XMLElement for Object through a tinyxml2::XMLDocument
 */
static tinyxml2::XMLElement* generateElementForObject(const Value& value, tinyxml2::XMLDocument *doc)
{
    // object is String
    if (value.getType() == Value::Type::STRING)
    {
        tinyxml2::XMLElement* node = doc->NewElement("string");
        tinyxml2::XMLText* content = doc->NewText(value.asString().c_str());
        node->LinkEndChild(content);
        return node;
    }
    
    // object is integer
    if (value.getType() == Value::Type::INTEGER)
    {
        tinyxml2::XMLElement* node = doc->NewElement("integer");
        tinyxml2::XMLText* content = doc->NewText(value.asString().c_str());
        node->LinkEndChild(content);
        return node;
    }

    // object is real
    if (value.getType() == Value::Type::FLOAT || value.getType() == Value::Type::DOUBLE)
    {
        tinyxml2::XMLElement* node = doc->NewElement("real");
        tinyxml2::XMLText* content = doc->NewText(value.asString().c_str());
        node->LinkEndChild(content);
        return node;
    }
    
    //object is bool
    if (value.getType() == Value::Type::BOOLEAN) {
		tinyxml2::XMLElement* node = doc->NewElement(value.asString().c_str());
		return node;
    }

    // object is Array
    if (value.getType() == Value::Type::VECTOR)
        return generateElementForArray(value.asValueVector(), doc);
    
    // object is Dictionary
    if (value.getType() == Value::Type::MAP)
        return generateElementForDict(value.asValueMap(), doc);
    
    CCLOG("This type cannot appear in property list");
    return nullptr;
}

/*
 * Generate tinyxml2::XMLElement for Dictionary through a tinyxml2::XMLDocument
 */
static tinyxml2::XMLElement* generateElementForDict(const ValueMap& dict, tinyxml2::XMLDocument *doc)
{
    tinyxml2::XMLElement* rootNode = doc->NewElement("dict");
    
    for (const auto &iter : dict)
    {
        tinyxml2::XMLElement* tmpNode = doc->NewElement("key");
        rootNode->LinkEndChild(tmpNode);
        tinyxml2::XMLText* content = doc->NewText(iter.first.c_str());
        tmpNode->LinkEndChild(content);
        
        tinyxml2::XMLElement *element = generateElementForObject(iter.second, doc);
        if (element)
            rootNode->LinkEndChild(element);
    }
    return rootNode;
}

/*
 * Generate tinyxml2::XMLElement for Array through a tinyxml2::XMLDocument
 */
static tinyxml2::XMLElement* generateElementForArray(const ValueVector& array, tinyxml2::XMLDocument *pDoc)
{
    tinyxml2::XMLElement* rootNode = pDoc->NewElement("array");

    for(const auto &value : array) {
        tinyxml2::XMLElement *element = generateElementForObject(value, pDoc);
        if (element)
            rootNode->LinkEndChild(element);
    }
    return rootNode;
}

#else
NS_CC_BEGIN

/* The subclass FileUtilsApple should override these two method. */
ValueMap FileUtils::getValueMapFromFile(const std::string& filename) {return ValueMap();}
ValueMap FileUtils::getValueMapFromData(const char* filedata, int filesize) {return ValueMap();}
ValueVector FileUtils::getValueVectorFromFile(const std::string& filename) {return ValueVector();}
bool FileUtils::writeToFile(ValueMap& dict, const std::string &fullPath) {return false;}

#endif /* (CC_TARGET_PLATFORM != CC_PLATFORM_IOS) && (CC_TARGET_PLATFORM != CC_PLATFORM_MAC) */

FileUtils* FileUtils::s_sharedFileUtils = nullptr;

void FileUtils::destroyInstance()
{
    CC_SAFE_DELETE(s_sharedFileUtils);
}

void FileUtils::setDelegate(FileUtils *delegate)
{
    if (s_sharedFileUtils)
        delete s_sharedFileUtils;
        
    s_sharedFileUtils = delegate;
}

FileUtils::FileUtils()
    : _writablePath("")
{
}

FileUtils::~FileUtils()
{
}



bool FileUtils::init()
{
    _searchPathArray.push_back(_defaultResRootPath);
    _searchResolutionsOrderArray.push_back("");
    return true;
}

void FileUtils::purgeCachedEntries()
{
    _fullPathCache.clear();
}

static Data getData(const std::string& filename, bool forString)
{
    if (filename.empty())
    {
        return Data::Null;
    }
    
    Data ret;
    unsigned char* buffer = nullptr;
    size_t size = 0;
    size_t readsize;
    const char* mode = nullptr;
    
    if (forString)
        mode = "rt";
    else
        mode = "rb";
    
    do
    {
        // Read the file from hardware
        std::string fullPath = FileUtils::getInstance()->fullPathForFilename(filename);
        FILE *fp = fopen(fullPath.c_str(), mode);
        CC_BREAK_IF(!fp);
        fseek(fp,0,SEEK_END);
        size = ftell(fp);
        fseek(fp,0,SEEK_SET);
        
        if (forString)
        {
            buffer = (unsigned char*)malloc(sizeof(unsigned char) * (size + 1));
            buffer[size] = '\0';
        }
        else
        {
            buffer = (unsigned char*)malloc(sizeof(unsigned char) * size);
        }
        
        readsize = fread(buffer, sizeof(unsigned char), size, fp);
        fclose(fp);
        
        if (forString && readsize < size)
        {
            buffer[readsize] = '\0';
        }
    } while (0);
    
    if (nullptr == buffer || 0 == readsize)
    {
        std::string msg = "Get data from file(";
        msg.append(filename).append(") failed!");
        CCLOG("%s", msg.c_str());
    }
    else
    {
        ret.fastSet(buffer, readsize);
    }
    
    return ret;
}

std::string FileUtils::getStringFromFile(const std::string& filename)
{
    Data data = getData(filename, true);
    if (data.isNull())
    	return "";
    
    std::string ret((const char*)data.getBytes());
    return ret;
}

Data FileUtils::getDataFromFile(const std::string& filename)
{
    return getData(filename, false);
}

unsigned char* FileUtils::getFileData(const std::string& filename, const char* mode, ssize_t *size)
{
    unsigned char * buffer = nullptr;
    CCASSERT(!filename.empty() && size != nullptr && mode != nullptr, "Invalid parameters.");
    *size = 0;
    do
    {
        // read the file from hardware
        const std::string fullPath = fullPathForFilename(filename);
        FILE *fp = fopen(fullPath.c_str(), mode);
        CC_BREAK_IF(!fp);
        
        fseek(fp,0,SEEK_END);
        *size = ftell(fp);
        fseek(fp,0,SEEK_SET);
        buffer = (unsigned char*)malloc(*size);
        *size = fread(buffer,sizeof(unsigned char), *size,fp);
        fclose(fp);
    } while (0);
    
    if (!buffer)
    {
        std::string msg = "Get data from file(";
        msg.append(filename).append(") failed!");
        
        CCLOG("%s", msg.c_str());
    }
    return buffer;
}

unsigned char* FileUtils::getFileDataFromZip(const std::string& zipFilePath, const std::string& filename, ssize_t *size)
{
    unsigned char * buffer = nullptr;
    unzFile file = nullptr;
    *size = 0;

    do 
    {
        CC_BREAK_IF(zipFilePath.empty());

        file = unzOpen(zipFilePath.c_str());
        CC_BREAK_IF(!file);

        // FIXME: Other platforms should use upstream minizip like mingw-w64  
        #ifdef MINIZIP_FROM_SYSTEM
        int ret = unzLocateFile(file, filename.c_str(), NULL);
        #else
        int ret = unzLocateFile(file, filename.c_str(), 1);
        #endif
        CC_BREAK_IF(UNZ_OK != ret);

        char filePathA[260];
        unz_file_info fileInfo;
        ret = unzGetCurrentFileInfo(file, &fileInfo, filePathA, sizeof(filePathA), nullptr, 0, nullptr, 0);
        CC_BREAK_IF(UNZ_OK != ret);

        ret = unzOpenCurrentFile(file);
        CC_BREAK_IF(UNZ_OK != ret);

        buffer = (unsigned char*)malloc(fileInfo.uncompressed_size);
        int CC_UNUSED readedSize = unzReadCurrentFile(file, buffer, static_cast<unsigned>(fileInfo.uncompressed_size));
        CCASSERT(readedSize == 0 || readedSize == (int)fileInfo.uncompressed_size, "the file size is wrong");

        *size = fileInfo.uncompressed_size;
        unzCloseCurrentFile(file);
    } while (0);

    if (file)
    {
        unzClose(file);
    }

    return buffer;
}

std::string FileUtils::getNewFilename(const std::string &filename) const
{
    std::string newFileName;
    
    // in Lookup Filename dictionary ?
    auto iter = _filenameLookupDict.find(filename);

    if (iter == _filenameLookupDict.end())
    {
        newFileName = filename;
    }
    else
    {
        newFileName = iter->second.asString();
    }
    return newFileName;
}

std::string FileUtils::getPathForFilename(const std::string& filename, const std::string& resolutionDirectory, const std::string& searchPath)
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

std::string FileUtils::fullPathForFilename(const std::string &filename)
{
    if (filename.empty())
    {
        return "";
    }
    
    if (isAbsolutePath(filename))
    {
        return filename;
    }

    // Already Cached ?
    auto cacheIter = _fullPathCache.find(filename);
    if(cacheIter != _fullPathCache.end())
    {
        return cacheIter->second;
    }
    
    // Get the new file name.
    const std::string newFilename( getNewFilename(filename) );
    
	std::string fullpath;
    
    for (const auto& searchIt : _searchPathArray)
    {
        for (const auto& resolutionIt : _searchResolutionsOrderArray)
        {
            fullpath = this->getPathForFilename(newFilename, resolutionIt, searchIt);
            
            if (fullpath.length() > 0)
            {
                // Using the filename passed in as key.
                _fullPathCache.insert(std::make_pair(filename, fullpath));
                return fullpath;
            }
            
        }
    }
    
    if(isPopupNotify()){
        CCLOG("cocos2d: fullPathForFilename: No file found at %s. Possible missing file.", filename.c_str());
    }

    // The file wasn't found, return empty string.
    return "";
}

std::string FileUtils::fullPathFromRelativeFile(const std::string &filename, const std::string &relativeFile)
{
    return relativeFile.substr(0, relativeFile.rfind('/')+1) + getNewFilename(filename);
}

void FileUtils::setSearchResolutionsOrder(const std::vector<std::string>& searchResolutionsOrder)
{
    bool existDefault = false;
    _fullPathCache.clear();
    _searchResolutionsOrderArray.clear();
    for(const auto& iter : searchResolutionsOrder)
    {
        std::string resolutionDirectory = iter;
        if (!existDefault && resolutionDirectory == "")
        {
            existDefault = true;
        }
        
        if (resolutionDirectory.length() > 0 && resolutionDirectory[resolutionDirectory.length()-1] != '/')
        {
            resolutionDirectory += "/";
        }
        
        _searchResolutionsOrderArray.push_back(resolutionDirectory);
    }

    if (!existDefault)
    {
        _searchResolutionsOrderArray.push_back("");
    }
}

void FileUtils::addSearchResolutionsOrder(const std::string &order,const bool front)
{
    std::string resOrder = order;
    if (!resOrder.empty() && resOrder[resOrder.length()-1] != '/')
        resOrder.append("/");
    
    if (front) {
        _searchResolutionsOrderArray.insert(_searchResolutionsOrderArray.begin(), resOrder);
    } else {
        _searchResolutionsOrderArray.push_back(resOrder);
    }
}

const std::vector<std::string>& FileUtils::getSearchResolutionsOrder() const
{
    return _searchResolutionsOrderArray;
}

const std::vector<std::string>& FileUtils::getSearchPaths() const
{
    return _searchPathArray;
}

void FileUtils::setWritablePath(const std::string& writablePath)
{
    _writablePath = writablePath;
}

void FileUtils::setDefaultResourceRootPath(const std::string& path)
{
    _defaultResRootPath = path;
}

void FileUtils::setSearchPaths(const std::vector<std::string>& searchPaths)
{
    bool existDefaultRootPath = false;
    
    _fullPathCache.clear();
    _searchPathArray.clear();
    for (const auto& iter : searchPaths)
    {
        std::string prefix;
        std::string path;
        
        if (!isAbsolutePath(iter))
        { // Not an absolute path
            prefix = _defaultResRootPath;
        }
        path = prefix + (iter);
        if (path.length() > 0 && path[path.length()-1] != '/')
        {
            path += "/";
        }
        if (!existDefaultRootPath && path == _defaultResRootPath)
        {
            existDefaultRootPath = true;
        }
        _searchPathArray.push_back(path);
    }
    
    if (!existDefaultRootPath)
    {
        //CCLOG("Default root path doesn't exist, adding it.");
        _searchPathArray.push_back(_defaultResRootPath);
    }
}

void FileUtils::addSearchPath(const std::string &searchpath,const bool front)
{
    std::string prefix;
    if (!isAbsolutePath(searchpath))
        prefix = _defaultResRootPath;

    std::string path = prefix + searchpath;
    if (path.length() > 0 && path[path.length()-1] != '/')
    {
        path += "/";
    }
    if (front) {
        _searchPathArray.insert(_searchPathArray.begin(), path);
    } else {
        _searchPathArray.push_back(path);
    }
}

void FileUtils::setFilenameLookupDictionary(const ValueMap& filenameLookupDict)
{
    _fullPathCache.clear();    
    _filenameLookupDict = filenameLookupDict;
}

void FileUtils::loadFilenameLookupDictionaryFromFile(const std::string &filename)
{
    const std::string fullPath = fullPathForFilename(filename);
    if (fullPath.length() > 0)
    {
        ValueMap dict = FileUtils::getInstance()->getValueMapFromFile(fullPath);
        if (!dict.empty())
        {
            ValueMap& metadata =  dict["metadata"].asValueMap();
            int version = metadata["version"].asInt();
            if (version != 1)
            {
                CCLOG("cocos2d: ERROR: Invalid filenameLookup dictionary version: %d. Filename: %s", version, filename.c_str());
                return;
            }
            setFilenameLookupDictionary( dict["filenames"].asValueMap());
        }
    }
}

std::string FileUtils::getFullPathForDirectoryAndFilename(const std::string& directory, const std::string& filename)
{
    // get directory+filename, safely adding '/' as necessary 
    std::string ret = directory;
    if (directory.size() && directory[directory.size()-1] != '/'){
        ret += '/';
    }
    ret += filename;
    
    // if the file doesn't exist, return an empty string
    if (!isFileExistInternal(ret)) {
        ret = "";
    }
    return ret;
}

std::string FileUtils::searchFullPathForFilename(const std::string& filename) const
{
    if (isAbsolutePath(filename))
    {
        return filename;
    }
    std::string path = const_cast<FileUtils*>(this)->fullPathForFilename(filename);
    if (0 == path.compare(filename))
    {
        return "";
    }
    else
    {
        return path;
    }
}

bool FileUtils::isFileExist(const std::string& filename) const
{
    if (isAbsolutePath(filename))
    {
        return isFileExistInternal(filename);
    }
    else
    {
        std::string fullpath = searchFullPathForFilename(filename);
        if (fullpath.empty())
            return false;
        else
            return true;
    }
}

bool FileUtils::isAbsolutePath(const std::string& path) const
{
    return (path[0] == '/');
}

bool FileUtils::isDirectoryExistInternal(const std::string& dirPath) const
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) ||  (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    WIN32_FILE_ATTRIBUTE_DATA wfad;
    std::wstring wdirPath(dirPath.begin(), dirPath.end());
    if (GetFileAttributesEx(wdirPath.c_str(), GetFileExInfoStandard, &wfad))
	{
		return true;
	}
	return false;
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	unsigned long fAttrib = GetFileAttributesA(dirPath.c_str());
    if (fAttrib != INVALID_FILE_ATTRIBUTES &&
        (fAttrib & FILE_ATTRIBUTE_DIRECTORY))
    {
		return true;
    }
    return false;
#else
    struct stat st;
    if (stat(dirPath.c_str(), &st) == 0)
    {
        return S_ISDIR(st.st_mode);
    }
    return false;
#endif


}

bool FileUtils::isDirectoryExist(const std::string& dirPath)
{
    CCASSERT(!dirPath.empty(), "Invalid path");
    
    if (isAbsolutePath(dirPath))
    {
        return isDirectoryExistInternal(dirPath);
    }
    
    // Already Cached ?
    auto cacheIter = _fullPathCache.find(dirPath);
    if( cacheIter != _fullPathCache.end() )
    {
        return isDirectoryExistInternal(cacheIter->second);
    }
    
	std::string fullpath;
    for (const auto& searchIt : _searchPathArray)
    {
        for (const auto& resolutionIt : _searchResolutionsOrderArray)
        {
            // searchPath + file_path + resourceDirectory
            fullpath = searchIt + dirPath + resolutionIt;
            if (isDirectoryExistInternal(fullpath))
            {
                const_cast<FileUtils*>(this)->_fullPathCache.insert(std::make_pair(dirPath, fullpath));
                return true;
            }
        }
    }
    
    return false;
}

bool FileUtils::createDirectory(const std::string& path)
{
    CCASSERT(!path.empty(), "Invalid path");
    
    if (isDirectoryExist(path))
        return true;
    
    // Split the path
    size_t start = 0;
    size_t found = path.find_first_of("/\\", start);
    std::string subpath;
    std::vector<std::string> dirs;
    
    if (found != std::string::npos)
    {
        while (true)
        {
            subpath = path.substr(start, found - start + 1);
            if (!subpath.empty())
                dirs.push_back(subpath);
            start = found+1;
            found = path.find_first_of("/\\", start);
            if (found == std::string::npos)
            {
                if (start < path.length())
                {
                    dirs.push_back(path.substr(start));
                }
                break;
            }
        }
    }


#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	WIN32_FILE_ATTRIBUTE_DATA wfad;
    std::wstring wpath(path.begin(), path.end());
    if (!(GetFileAttributesEx(wpath.c_str(), GetFileExInfoStandard, &wfad)))
	{
		subpath = "";
		for(unsigned int i = 0 ; i < dirs.size() ; ++i)
		{
			subpath += dirs[i];
			if (i > 0 && !isDirectoryExist(subpath))
			{
                std::wstring wsubpath(subpath.begin(), subpath.end());
                BOOL ret = CreateDirectory(wsubpath.c_str(), NULL);
				if (!ret && ERROR_ALREADY_EXISTS != GetLastError())
				{
					return false;
				}
			}
		}
	}
	return true;
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
    if ((GetFileAttributesA(path.c_str())) == INVALID_FILE_ATTRIBUTES)
    {
		subpath = "";
		for (unsigned int i = 0; i < dirs.size(); ++i)
		{
			subpath += dirs[i];
			if (!isDirectoryExist(subpath))
			{
				BOOL ret = CreateDirectoryA(subpath.c_str(), NULL);
				if (!ret && ERROR_ALREADY_EXISTS != GetLastError())
				{
					return false;
				}
			}
		}
    }
    return true;
#else
    DIR *dir = NULL;

    // Create path recursively
    subpath = "";
    for (int i = 0; i < dirs.size(); ++i)
    {
        subpath += dirs[i];
        dir = opendir(subpath.c_str());
        
        if (!dir)
        {
            // directory doesn't exist, should create a new one
            
            int ret = mkdir(subpath.c_str(), S_IRWXU | S_IRWXG | S_IRWXO);
            if (ret != 0 && (errno != EEXIST))
            {
                // current directory can not be created, sub directories can not be created too
                // should return
                return false;
            }
        }
        else
        {
            // directory exists, should close opened dir
            closedir(dir);
        }
    }
    return true;
#endif
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
static int unlink_cb(const char *fpath, const struct stat *sb, int typeflag, struct FTW *ftwbuf)
{
    auto ret = remove(fpath);
    if (ret)
    {
        log("Fail to remove: %s ",fpath);
    }
    
    return ret;
}
#endif

bool FileUtils::removeDirectory(const std::string& path)
{
    if (path.size() > 0 && path[path.size() - 1] != '/')
    {
        CCLOGERROR("Fail to remove directory, path must termniate with '/': %s", path.c_str());
        return false;
    }
    
    // Remove downloaded files

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    std::wstring wpath = std::wstring(path.begin(), path.end());
    std::wstring files = wpath +  L"*.*";
	WIN32_FIND_DATA wfd;
	HANDLE  search = FindFirstFileEx(files.c_str(), FindExInfoStandard, &wfd, FindExSearchNameMatch, NULL, 0);
	bool ret=true;   
	if (search!=INVALID_HANDLE_VALUE)   
	{   
		BOOL find=true;   
		while (find)
		{ 
			//. ..
			if(wfd.cFileName[0]!='.')  
			{   
                std::wstring temp = wpath + wfd.cFileName;
				if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				{
                    temp += '/';
                    ret = ret && this->removeDirectory(std::string(temp.begin(), temp.end()));
				}
				else
				{   
                    SetFileAttributes(temp.c_str(), FILE_ATTRIBUTE_NORMAL);
                    ret = ret && DeleteFile(temp.c_str());
				}
			}
			find = FindNextFile(search, &wfd);
		}
		FindClose(search);
	}
    if (ret && RemoveDirectory(wpath.c_str()))
    {
        return true;
    }
	return false;
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	std::string command = "cmd /c rd /s /q ";
	// Path may include space.
	command += "\"" + path + "\"";

	if (WinExec(command.c_str(), SW_HIDE) > 31)
		return true;
	else
		return false;
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
    if (nftw(path.c_str(),unlink_cb, 64, FTW_DEPTH | FTW_PHYS))
        return false;
    else
        return true;
#else
    std::string command = "rm -r ";
    // Path may include space.
    command += "\"" + path + "\"";
    if (system(command.c_str()) >= 0)
        return true;
    else
        return false;
#endif
}

bool FileUtils::removeFile(const std::string &path)
{
    // Remove downloaded file

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    std::wstring wpath(path.begin(), path.end());
    if (DeleteFile(wpath.c_str()))
	{
		return true;
	}
	return false;
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	std::string command = "cmd /c del /q ";
	std::string win32path = path;
	int len = win32path.length();
	for (int i = 0; i < len; ++i)
	{
		if (win32path[i] == '/')
		{
			win32path[i] = '\\';
		}
	}
	command += win32path;

	if (WinExec(command.c_str(), SW_HIDE) > 31)
		return true;
	else
		return false;
#else
    if (remove(path.c_str())) {
        return false;
    } else {
        return true;
    }
#endif
}

bool FileUtils::renameFile(const std::string &path, const std::string &oldname, const std::string &name)
{
    CCASSERT(!path.empty(), "Invalid path");
    std::string oldPath = path + oldname;
    std::string newPath = path + name;
 
    // Rename a file
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT || CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
    std::regex pat("\\/");
    std::string _old = std::regex_replace(oldPath, pat, "\\");
    std::string _new = std::regex_replace(newPath, pat, "\\");
    if (MoveFileEx(std::wstring(_old.begin(), _old.end()).c_str(), 
        std::wstring(_new.begin(), _new.end()).c_str(),
        MOVEFILE_REPLACE_EXISTING & MOVEFILE_WRITE_THROUGH))
    {
        return true;
    }
    return false;
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) 
    std::regex pat("\\/");
    std::string _old = std::regex_replace(oldPath, pat, "\\");
    std::string _new = std::regex_replace(newPath, pat, "\\");

    if(FileUtils::getInstance()->isFileExist(_new))
    {
        DeleteFileA(_new.c_str());
    }

    MoveFileA(_old.c_str(), _new.c_str());

    if (0 == GetLastError())
        return true;
    else
        return false;
#else
    int errorCode = rename(oldPath.c_str(), newPath.c_str());

    if (0 != errorCode)
    {
        CCLOGERROR("Fail to rename file %s to %s !Error code is %d", oldPath.c_str(), newPath.c_str(), errorCode);
        return false;
    }
    return true;
#endif
}

long FileUtils::getFileSize(const std::string &filepath)
{
    CCASSERT(!filepath.empty(), "Invalid path");
    
    std::string fullpath = filepath;
    if (!isAbsolutePath(filepath))
    {
        fullpath = searchFullPathForFilename(filepath);
        if (fullpath.empty())
            return 0;
    }
    
    struct stat info;
    // Get data associated with "crt_stat.c":
    int result = stat( fullpath.c_str(), &info );
    
    // Check if statistics are valid:
    if( result != 0 )
    {
        // Failed
        return -1;
    }
    else
    {
        return (long)(info.st_size);
    }
}

//////////////////////////////////////////////////////////////////////////
// Notification support when getFileData from invalid file path.
//////////////////////////////////////////////////////////////////////////
static bool s_popupNotify = true;

void FileUtils::setPopupNotify(bool notify)
{
    s_popupNotify = notify;
}

bool FileUtils::isPopupNotify()
{
    return s_popupNotify;
}

NS_CC_END

