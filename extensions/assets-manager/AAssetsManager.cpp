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

// Events
#define FINISH_UPDATE_EVENT     "AM_Update_Finished"
#define NEW_VERSION_EVENT       "AM_New_Version_Found"
#define UPDATING_PERCENT_EVENT  "AM_Updating"

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
    
    std::string cachedManifest = _storagePath + MANIFEST_FILENAME;
    // Prefer to use the cached manifest file, if not found use user configured manifest file
    // Prepend storage path to avoid multi package conflict issue
    if (_fileUtils->isFileExist(cachedManifest))
        _localManifest = new Manifest(cachedManifest);
    
    // Fail to found cached manifest file
    if (!_localManifest) {
        _localManifest = new Manifest(_manifestUrl);
    }
    // Fail to load cached manifest file
    else if (!_localManifest->isLoaded()) {
        destroyFile(cachedManifest);
        _localManifest->parse(_manifestUrl);
    }
    
    // Download version file
    update();
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
    adjustPath(_storagePath);
    createDirectory(_storagePath);
    if (_storagePath.size() > 0)
        prependSearchPath(_storagePath);
}

void AAssetsManager::adjustPath(std::string &path)
{
    if (path.size() > 0 && path[path.size() - 1] != '/')
    {
        path.append("/");
    }
    path.insert(0, s_nWritableRoot);
}

void AAssetsManager::prependSearchPath(const std::string& path)
{
    std::vector<std::string> searchPaths = FileUtils::getInstance()->getSearchPaths();
    std::vector<std::string>::iterator iter = searchPaths.begin();
    searchPaths.insert(iter, path);
    FileUtils::getInstance()->setSearchPaths(searchPaths);
}

void AAssetsManager::createDirectory(const std::string& path)
{
    // Check writable path existance
    if (path.find(s_nWritableRoot) == std::string::npos)
    {
        CCLOG("Path which isn't under system's writable path cannot be created.");
        return;
    }
    
    // Split the path
    size_t start = s_nWritableRoot.size();
    size_t found = path.find_first_of("/\\", start);
    std::string subpath;
    std::vector<std::string> dirs;
    while (found != std::string::npos)
    {
        subpath = path.substr(start, found - start + 1);
        if (subpath.size() > 0) dirs.push_back(subpath);
        start = found+1;
        found = path.find_first_of("/\\", start);
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
    if ((GetFileAttributesA(path.c_str())) == INVALID_FILE_ATTRIBUTES)
    {
        // TODO: create recursively the path on windows
        CreateDirectoryA(path.c_str(), 0);
    }
#endif
}

void AAssetsManager::destroyDirectory(const std::string& path)
{
    // Check writable path existance
    if (path.find(s_nWritableRoot) == std::string::npos)
    {
        CCLOG("Path which isn't under system's writable path cannot be destroyed.");
        return;
    }
    
    if (path.size() > 0 && path[path.size() - 1] != '/')
    {
        CCLOG("Invalid path.");
        return;
    }
    
    // Remove downloaded files
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
    std::string command = "rm -r ";
    // Path may include space.
    command += "\"" + path + "\"";
    system(command.c_str());
#else
    string command = "rd /s /q ";
    // Path may include space.
    command += "\"" + path + "\"";
    system(command.c_str());
#endif
}

void AAssetsManager::destroyFile(const std::string &path)
{
    if (path.find(s_nWritableRoot) != std::string::npos)
    {
        // Remove downloaded file
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
        std::string command = "rm ";
        // Path may include space.
        command += "\"" + path + "\"";
        system(command.c_str());
#else
        string command = "del /q ";
        // Path may include space.
        command += "\"" + path + "\"";
        system(command.c_str());
#endif
    }

}

AAssetsManager::UpdateState AAssetsManager::updateState()
{
    if (_updateState == UNKNOWN || _updateState == NEED_UPDATE || _updateState == UP_TO_DATE || _updateState == UPDATING)
    {
        return _updateState;
    }
    // A special case
    else if (_remoteManifest && _remoteManifest->isVersionLoaded())
    {
        return UPDATING;
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
                checkUpdate();
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
                checkUpdate();
            }
            else
            {
                if (_localManifest->versionEquals(_remoteManifest))
                    _updateState = UP_TO_DATE;
                else
                {
                    _updateState = NEED_UPDATE;
                    EventCustom newVerEvent(NEW_VERSION_EVENT);
                    newVerEvent.setUserData(this);
                    _eventDispatcher->dispatchEvent(&newVerEvent);
                    
                    // Wait to update so continue the process
                    if (_waitToUpdate)
                    {
                        _updateState = PREDOWNLOAD_MANIFEST;
                        checkUpdate();
                    }
                }
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
                    EventCustom newVerEvent(NEW_VERSION_EVENT);
                    newVerEvent.setUserData(this);
                    _eventDispatcher->dispatchEvent(&newVerEvent);
                    
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
            // Manifest not loaded yet
            if (!_remoteManifest->isLoaded())
            {
                _waitToUpdate = true;
                _updateState = PREDOWNLOAD_MANIFEST;
                checkUpdate();
                break;
            }
            
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
                    _downloadUnits.clear();
                    std::string packageUrl = _remoteManifest->getPackageUrl();
                    for (auto it = diff_map.begin(); it != diff_map.end(); it++) {
                        Manifest::AssetDiff diff = it->second;
                        
                        if (diff.type == Manifest::DELETED) {
// DELETE
                        }
                        else
                        {
                            std::string path = diff.asset.path;
                            // Create path
                            createDirectory(_storagePath + path);
                            
                            Downloader::DownloadUnit unit;
                            unit.customId = it->first;
                            unit.srcUrl = packageUrl + path;
                            unit.storagePath = _storagePath + path;
                            _downloadUnits.emplace(unit.customId, unit);
                        }
                    }
                    _downloader->batchDownload(_downloadUnits);
                }
            }
            
            _updateState = UPDATING;
            _waitToUpdate = false;
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
        
        auto unitIt = _downloadUnits.find(customId);
        // Found unit and delete it
        if (unitIt != _downloadUnits.end())
        {
            _downloadUnits.erase(unitIt);
        }
        // Finish check
        if (_downloadUnits.size() == 0)
        {
            EventCustom finishEvent(FINISH_UPDATE_EVENT);
            finishEvent.setUserData(this);
            _eventDispatcher->dispatchEvent(&finishEvent);
        }
    }
}

NS_CC_EXT_END;