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

#define VERSION_FILENAME        "version.manifest"
#define MANIFEST_FILENAME       "project.manifest"

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
: _waitToUpdate(false)
, _manifestUrl(manifestUrl)
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
    
    // Init variables
    _eventDispatcher = Director::getInstance()->getEventDispatcher();
    _fileUtils = FileUtils::getInstance();
    _updateState = UNKNOWN;
    
    _downloader = new Downloader(this);
    setStoragePath(storagePath);
    
    // Prefer to use the cached manifest file, if not found use user configured manifest file
    // Prepend storage path to avoid multi package conflict issue
    if (_fileUtils->isFileExist(storagePath + MANIFEST_FILENAME))
        _localManifest = new Manifest(storagePath + MANIFEST_FILENAME);
    else _localManifest = new Manifest(_manifestUrl);
    
    // Download version file
    checkUpdate();
}

AAssetsManager::~AAssetsManager()
{
}

std::string AAssetsManager::getLoadedEventName(const std::string& key)
{
    std::string eventName = "AM_" + key + "_Loaded";
    return eventName;
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

AAssetsManager::UpdateState AAssetsManager::updateState()
{
    if (_updateState == UNKNOWN || _updateState == NEED_UPDATE || _updateState == UP_TO_DATE || _updateState == UPDATING) {
        return _updateState;
    }
    else return CHECKING;
}

void AAssetsManager::checkUpdate()
{
    switch (_updateState) {
        case UNKNOWN:
        case PREDOWNLOAD_VERSION:
        {
            std::string versionUrl = _localManifest->getVersionFileUrl();
            if (versionUrl.size() > 0)
            {
                // Download version file asynchronously
                _downloader->downloadAsync(versionUrl, _storagePath + VERSION_FILENAME, "@version");
                _updateState = DOWNLOADING_VERSION;
            }
            // No version file found
            else
            {
                CCLOG("No version file found, step skipped\n");
                _updateState = PREDOWNLOAD_MANIFEST;
            }
        }
        break;
        case VERSION_LOADED:
        {
            if (!_remoteManifest)
                _remoteManifest = new Manifest(VERSION_FILENAME);
            else
                _remoteManifest->parse(VERSION_FILENAME);
            
            if (!_remoteManifest->isVersionLoaded())
            {
                CCLOG("Error parsing version file, step skipped\n");
                _updateState = PREDOWNLOAD_MANIFEST;
            }
            else
            {
                if (_localManifest->versionEquals(_remoteManifest))
                    _updateState = UP_TO_DATE;
                else _updateState = NEED_UPDATE;
            }
        }
        break;
        case PREDOWNLOAD_MANIFEST:
        {
            std::string manifestUrl = _localManifest->getManifestFileUrl();
            if (manifestUrl.size() > 0)
            {
                // Download version file asynchronously
                _downloader->downloadAsync(manifestUrl, _storagePath + MANIFEST_FILENAME, "@manifest");
                _updateState = DOWNLOADING_MANIFEST;
            }
            // No version file found
            else
            {
                CCLOG("No manifest file found, check update failed\n");
                _updateState = UNKNOWN;
            }
        }
        break;
        case MANIFEST_LOADED:
        {
            if (!_remoteManifest)
                _remoteManifest = new Manifest(MANIFEST_FILENAME);
            else
                _remoteManifest->parse(MANIFEST_FILENAME);
            
            if (!_remoteManifest->isLoaded())
            {
                CCLOG("Error parsing manifest file\n");
                _updateState = UNKNOWN;
            }
            else
            {
                if (_localManifest->versionEquals(_remoteManifest))
                    _updateState = UP_TO_DATE;
                else
                {
                    _updateState = NEED_UPDATE;
                    if (_waitToUpdate)
                    {
                        update();
                    }
                }
            }
        }
        break;
        default:
        break;
    }
}

void AAssetsManager::update()
{
    switch (_updateState) {
        case NEED_UPDATE:
        {
            // Check difference
            if (_localManifest && _remoteManifest)
            {
                std::map<std::string, Manifest::AssetDiff> diff_map = _localManifest->genDiff(_remoteManifest);
                if (diff_map.size() == 0)
                {
                    _updateState = UP_TO_DATE;
                }
                else
                {
                    _updateState = UPDATING;
// UPDATE
                    std::string packageUrl = _remoteManifest->getPackageUrl();
                    std::vector<Downloader::DownloadUnit> update_units;
                    for (auto it = diff_map.begin(); it != diff_map.end(); it++) {
                        Manifest::AssetDiff diff = it->second;
                        
                        if (diff.type == Manifest::DELETED) {
// DELETE
                        }
                        else
                        {
                            std::string path = diff.asset->path;
                            Downloader::DownloadUnit unit;
                            unit.customId = it->first;
                            unit.srcUrl = packageUrl + path;
                            unit.storagePath = _storagePath + path;
                            update_units.push_back(unit);
                        }
                    }
                    _downloader->batchDownload(update_units);
                }
            }
            
            _updateState = UPDATING;
        }
        break;
        case UP_TO_DATE:
        case UPDATING:
        break;
        default:
        {
            _waitToUpdate = true;
            checkUpdate();
        }
        break;
    }
}


void AAssetsManager::onError(const Downloader::Error &error)
{
    // Rollback check states when error occured
    if (error.customId == "@version")
    {
        _updateState = PREDOWNLOAD_VERSION;
    }
    
    CCLOG("%d : %s\n", error.code, error.message.c_str());
}

void AAssetsManager::onProgress(double total, double downloaded, const std::string &url, const std::string &customId)
{
    int percent = (downloaded / total) * 100;
    CCLOG("Progress: %d\n", percent);
}

void AAssetsManager::onSuccess(const std::string &srcUrl, const std::string &customId)
{
    CCLOG("SUCCEED: %s\n", customId.c_str());
    
    if (customId == "@version")
    {
        _updateState = VERSION_LOADED;
        checkUpdate();
    }
    else if (customId == "@manifest")
    {
        _updateState = MANIFEST_LOADED;
        checkUpdate();
    }
    else
    {
        std::string eventName = getLoadedEventName(customId);
        EventCustom event(eventName);
        std::string cid = customId;
        event.setUserData(&cid);
        _eventDispatcher->dispatchEvent(&event);
    }
}

NS_CC_EXT_END;