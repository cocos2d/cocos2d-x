/****************************************************************************
 Copyright (c) 2014 cocos2d-x.org
 
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
#include "AAssetsManager.h"

#include <curl/curl.h>
#include <curl/easy.h>
#include <stdio.h>
#include <thread>

#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32) && (CC_TARGET_PLATFORM != CC_PLATFORM_WP8) && (CC_TARGET_PLATFORM != CC_PLATFORM_WINRT)
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <dirent.h>
#endif

#include "unzip.h"

using namespace cocos2d;

NS_CC_EXT_BEGIN;

#define KEY_VERSION             "version"
#define KEY_MANIFEST_URL        "remoteManifestUrl"
#define KEY_VERSION_URL         "remoteVersionUrl"
#define KEY_GROUP_VERSIONS      "groupVersions"
#define KEY_ENGINE_VERSION      "engineVersion"
#define KEY_ASSETS              "assets"
#define KEY_COMPRESSED_FILES    "compressedFiles"

#define KEY_PATH                "path"
#define KEY_MD5                 "md5"
#define KEY_GROUP               "group"
#define KEY_COMPRESSED          "compressed"
#define KEY_COMPRESSED_FILE     "compressedFile"

#define BUFFER_SIZE         8192
#define MAX_FILENAME        512
#define LOW_SPEED_LIMIT     1L
#define LOW_SPEED_TIME      5L


// Message type
#define ASSETSMANAGER_MESSAGE_UPDATE_SUCCEED                0
#define ASSETSMANAGER_MESSAGE_RECORD_DOWNLOADED_VERSION     1
#define ASSETSMANAGER_MESSAGE_PROGRESS                      2
#define ASSETSMANAGER_MESSAGE_ERROR                         3

// Some data struct for sending messages

struct ErrorMessage
{
    AAssetsManager::ErrorCode code;
    AAssetsManager* manager;
};

struct ProgressMessage
{
    int percent;
    AAssetsManager* manager;
};

std::string AAssetsManager::s_nWritableRoot = "";

// Implementation of AssetsManager

AAssetsManager::AAssetsManager(const std::string& manifestUrl, const std::string& storagePath/* = "" */)
: _manifestUrl(manifestUrl)
, _remoteManifestUrl("")
, _remoteVersionUrl("")
, _remoteUrl("")
, _currentVer("")
, _engineVer("")
, _remoteManifestVer("")
, _remoteEngineVer("")
, _manifestLoaded(false)
, _curl(nullptr)
, _connectionTimeout(0)
, _isDownloading(false)
{
    // Init writable path
    if (s_nWritableRoot.size() == 0) {
        s_nWritableRoot = FileUtils::getInstance()->getWritablePath();
        CCLOG("%s", s_nWritableRoot.c_str());
        prependSearchPath(s_nWritableRoot);
    }
    
    _downloader = new Downloader(this);
    setStoragePath(storagePath);
    loadManifest();
}

AAssetsManager::~AAssetsManager()
{
}

const std::string& AAssetsManager::getStoragePath() const
{
    return _storagePath;
}

void AAssetsManager::setStoragePath(const std::string& storagePath)
{
// TODO Check if need to destroy old path
    //if (_storagePath.size() > 0)
        //destroyStoragePath();
    
    _storagePath = storagePath;
    createStoragePath();
    if (_storagePath.size() > 0)
        prependSearchPath(_storagePath);
}

void AAssetsManager::adjustStoragePath()
{
    if (_storagePath.size() > 0 && _storagePath[_storagePath.size() - 1] != '/')
    {
        _storagePath.append("/");
    }
    _storagePath.insert(0, s_nWritableRoot);
}

void AAssetsManager::prependSearchPath(const std::string& path)
{
    std::vector<std::string> searchPaths = FileUtils::getInstance()->getSearchPaths();
    std::vector<std::string>::iterator iter = searchPaths.begin();
    searchPaths.insert(iter, path);
    FileUtils::getInstance()->setSearchPaths(searchPaths);
}

void AAssetsManager::createStoragePath()
{
    adjustStoragePath();
    // Check writable path existance
    if (_storagePath.find(s_nWritableRoot) == std::string::npos)
    {
        CCLOG("Storage path which isn't under system writable path cannot be created.");
        return;
    }
    
    // Split the path
    size_t start = s_nWritableRoot.size();
    size_t found = _storagePath.find_first_of("/\\", start);
    std::string subpath;
    std::vector<std::string> dirs;
    while (found != std::string::npos)
    {
        subpath = _storagePath.substr(start, found - start + 1);
        if (subpath.size() > 0) dirs.push_back(subpath);
        start = found+1;
        found = _storagePath.find_first_of("/\\", start);
    }
    
    // Remove downloaded files
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
    DIR *dir = NULL;
    
    // Create path recursively
    subpath = s_nWritableRoot;
    for (int i = 0; i < dirs.size(); i++) {
        subpath += dirs[i];
        dir = opendir (subpath.c_str());
        if (!dir)
        {
            mkdir(subpath.c_str(), S_IRWXU | S_IRWXG | S_IRWXO);
        }
    }
#else
    if ((GetFileAttributesA(_storagePath.c_str())) == INVALID_FILE_ATTRIBUTES)
    {
// TODO: create recursively the path on windows
        CreateDirectoryA(_storagePath.c_str(), 0);
    }
#endif
}

void AAssetsManager::destroyStoragePath()
{
    // Delete recorded version codes.
// TODO: deleteVersion();
    
// TODO: Delete recursively
    
    // Remove downloaded files
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
    std::string command = "rm -r ";
    // Path may include space.
    command += "\"" + _storagePath + "\"";
    system(command.c_str());
#else
    string command = "rd /s /q ";
    // Path may include space.
    command += "\"" + _storagePath + "\"";
    system(command.c_str());
#endif
}

void AAssetsManager::loadManifest()
{
    if (_manifestUrl.size() == 0) return;
    
    std::string manifest;
    FileUtils* fileUtils = FileUtils::getInstance();
    if (fileUtils->isFileExist(_manifestUrl))
    {
        // Load manifest file content
        manifest = fileUtils->getStringFromFile(_manifestUrl);
        
        // Parse manifest file with rapid json
        rapidjson::Document json;
        
        json.Parse<0>(manifest.c_str());
        // Print error and exit
        if (json.HasParseError()) {
            std::string errorSnippet = manifest.substr(json.GetErrorOffset()-1, 10);
            CCLOG("Manifest file parse error %s at <%s>\n", json.GetParseError(), errorSnippet.c_str());
            return;
        }
        
        // Retrieve remote manifest url
        if( json.HasMember(KEY_MANIFEST_URL) && json[KEY_MANIFEST_URL].IsString() )
        {
            _remoteManifestUrl = json[KEY_MANIFEST_URL].GetString();
        }
        
        // Retrieve remote version url
        if( json.HasMember(KEY_VERSION_URL) && json[KEY_VERSION_URL].IsString() )
        {
            _remoteVersionUrl = json[KEY_VERSION_URL].GetString();
        }
        
        // Retrieve local version
        if( json.HasMember(KEY_VERSION) && json[KEY_VERSION].IsString() )
        {
            _currentVer = json[KEY_VERSION].GetString();
        }
        
        // Retrieve local group version
        if( json.HasMember(KEY_GROUP_VERSIONS) )
        {
            const rapidjson::Value& groupVers = json[KEY_GROUP_VERSIONS];
            if (groupVers.IsObject())
            {
                for (rapidjson::Value::ConstMemberIterator itr = groupVers.MemberonBegin(); itr != groupVers.MemberonEnd(); ++itr)
                {
                    std::string group = itr->name.GetString();
                    std::string version = "0";
                    if(itr->value.IsString())
                    {
                        version = itr->value.GetString();
                    }
                    _groups.push_back(group);
                    _groupVer.emplace(group, version);
                }
            }
        }
        
        // Retrieve local engine version
        if( json.HasMember(KEY_ENGINE_VERSION) && json[KEY_ENGINE_VERSION].IsString() )
        {
            _engineVer = json[KEY_ENGINE_VERSION].GetString();
        }
        
        // Retrieve all compressed files
// TODO
        
        // Retrieve all assets
        if( json.HasMember(KEY_ASSETS) )
        {
            const rapidjson::Value& assets = json[KEY_ASSETS];
            if (assets.IsObject())
            {   
                for (rapidjson::Value::ConstMemberIterator itr = assets.MemberonBegin(); itr != assets.MemberonEnd(); ++itr)
                {
                    std::string key = itr->name.GetString();
                    Asset asset = parseAsset(itr->value);
                    _assets.emplace(key, asset);
                }
            }
        }
        
        // Download version and manifest file
        _downloader->download(_remoteVersionUrl, _storagePath);
    }
}

Asset AAssetsManager::parseAsset(const rapidjson::Value& json) {
    Asset asset;
    asset.updating = false;
    
    // The path info is obligated in Asset
    if( json.HasMember(KEY_PATH) && json[KEY_PATH].IsString() )
    {
        asset.path = json[KEY_PATH].GetString();
        
        if( json.HasMember(KEY_MD5) && json[KEY_MD5].IsString() )
        {
            asset.md5 = json[KEY_MD5].GetString();
        }
        else asset.md5 = "";
        
        if( json.HasMember(KEY_GROUP) && json[KEY_GROUP].IsString() )
        {
            asset.group = json[KEY_GROUP].GetString();
        }
        else asset.group = "";
    }
    
    return asset;
}


void AAssetsManager::onError(const Downloader::Error &error)
{
    CCLOG("%d : %s\n", error.code, error.message.c_str());
}

void AAssetsManager::onProgress(int percent)
{
    CCLOG("Progress: %d\n", percent);
}

void AAssetsManager::onSuccess(const std::string &filename, const std::string &srcUrl)
{
    CCLOG("SUCCEED: %s\n", filename.c_str());
    
    std::string content;
    FileUtils* fileUtils = FileUtils::getInstance();
    if (fileUtils->isFileExist(filename))
    {
        // Load manifest file content
        content = fileUtils->getStringFromFile(filename);
        
        CCLOG("%s", content.c_str());
        
        // Parse manifest file with rapid json
        rapidjson::Document json;
        
        json.Parse<0>(content.c_str());
        // Print error and exit
        if (json.HasParseError()) {
            std::string errorSnippet = content.substr(json.GetErrorOffset()-1, 10);
            CCLOG("Manifest file parse error %s at <%s>\n", json.GetParseError(), errorSnippet.c_str());
            return;
        }
    }
}

NS_CC_EXT_END;