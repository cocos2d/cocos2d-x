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
#define UPDATING_EVENT              "_Updating_Event"
#define NO_LOCAL_MANIFEST           "_No_Local_Manifest"
//#define ALREADY_UP_TO_DATE_EVENT    "_Already_Up_To_Date"
//#define FINISH_UPDATE_EVENT         "_Update_Finished"
//#define NEW_VERSION_EVENT           "_New_Version_Found"
#define UPDATING_PERCENT_EVENT      "_Updating_Percent"

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

struct ProgressMessage
{
    int percent;
    AAssetsManager* manager;
};

std::string AAssetsManager::s_nWritableRoot = "";

// Implementation of AssetsManager

AAssetsManager::AAssetsManager(const std::string &managerId, const std::string& manifestUrl, const std::string& storagePath/* = "" */)
: _managerId(managerId)
, _waitToUpdate(false)
, _manifestUrl(manifestUrl)
, _assets(nullptr)
, _localManifest(nullptr)
, _remoteManifest(nullptr)
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
    
    loadManifest(manifestUrl);
    CCLOG("%s\n%s\n%p\n", _manifestUrl.c_str(), _storagePath.c_str(), this);
}

AAssetsManager::~AAssetsManager()
{
}

AAssetsManager* AAssetsManager::create(const std::string &managerId, const std::string& manifestUrl, const std::string& storagePath/* = ""*/)
{
    AAssetsManager* manager = new AAssetsManager(managerId, manifestUrl, storagePath);
    manager->autorelease();
    return manager;
}

void AAssetsManager::setLocalManifest(Manifest *manifest)
{
    _localManifest = manifest;
    // An alias to assets
    _assets = &(_localManifest->getAssets());
    
    // Add search paths
    _localManifest->prependSearchPaths();
}

void AAssetsManager::loadManifest(const std::string& manifestUrl)
{
    _localManifest = nullptr;
    std::string cachedManifest = _storagePath + MANIFEST_FILENAME;
    // Prefer to use the cached manifest file, if not found use user configured manifest file
    // Prepend storage path to avoid multi package conflict issue
    if (_fileUtils->isFileExist(cachedManifest))
    {
        Manifest *manifest = new Manifest(cachedManifest);
        if (manifest->isLoaded())
            setLocalManifest(manifest);
        else
            destroyFile(cachedManifest);
    }
    
    // Fail to found or load cached manifest file
    if (_localManifest == nullptr)
    {
        Manifest *manifest = new Manifest(_manifestUrl);
        if (manifest->isLoaded())
            setLocalManifest(manifest);
    }
    
    // Fail to load local manifest
    if (_localManifest == nullptr || !_localManifest->isLoaded())
    {
        CCLOG("AssetsManager : No local manifest file found error.");
        EventCustom event(_managerId + NO_LOCAL_MANIFEST);
        std::string url = _manifestUrl;
        event.setUserData(&url);
        _eventDispatcher->dispatchEvent(&event);
    }
}

std::string AAssetsManager::get(const std::string& key) const
{
    auto it = _assets->find(key);
    if (it != _assets->cend()) {
        return _storagePath + it->second.path;
    }
    else return "";
}

std::string AAssetsManager::getLoadedEventName(const std::string& key)
{
    std::string eventName = _managerId + "_" + key + "_Loaded";
    return eventName;
}

const Manifest* AAssetsManager::getLocalManifest()
{
    return _localManifest;
}

const std::string& AAssetsManager::getStoragePath() const
{
    return _storagePath;
}

void AAssetsManager::setStoragePath(const std::string& storagePath)
{
    if (_storagePath.size() > 0)
        destroyDirectory(_storagePath);
    
    _storagePath = storagePath;
    adjustPath(_storagePath);
    createDirectory(_storagePath);
    //if (_storagePath.size() > 0)
        //prependSearchPath(_storagePath);
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

void AAssetsManager::dispatchUpdateEvent(UpdateEventCode code, std::string message/* = ""*/, std::string assetId/* = ""*/)
{
    EventCustom event(_managerId + UPDATING_EVENT);
    UpdateEvent e;
    e.code = code;
    e.message = message;
    e.assetId = assetId;
    e.manager = this;
    event.setUserData(&e);
    _eventDispatcher->dispatchEvent(&event);
}

void AAssetsManager::addUpdateEventListener(const std::function<void(EventCustom*)>& callback, int priority/* = 1*/)
{
    EventListenerCustom *listener = EventListenerCustom::create(_managerId + UPDATING_EVENT, callback);
    _eventDispatcher->addEventListenerWithFixedPriority(listener, priority);
}

void AAssetsManager::addUpdateProgressEventListener(const std::function<void(EventCustom*)>& callback, int priority/* = 1*/)
{
    EventListenerCustom *listener = EventListenerCustom::create(_managerId + UPDATING_PERCENT_EVENT, callback);
    _eventDispatcher->addEventListenerWithFixedPriority(listener, priority);
}

void AAssetsManager::addNoLocalManifestErrorListener(const std::function<void(EventCustom*)>& callback, int priority/* = 1*/)
{
    EventListenerCustom *listener = EventListenerCustom::create(_managerId + NO_LOCAL_MANIFEST, callback);
    _eventDispatcher->addEventListenerWithFixedPriority(listener, priority);
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
    if (!_localManifest->isLoaded())
    {
        CCLOG("AssetsManager : No local manifest file found error.");
        EventCustom event(_managerId + NO_LOCAL_MANIFEST);
        std::string url = _manifestUrl;
        event.setUserData(&url);
        _eventDispatcher->dispatchEvent(&event);
        return;
    }
    
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
            if (_remoteManifest == nullptr)
                _remoteManifest = new Manifest(_storagePath + VERSION_FILENAME);
            else
                _remoteManifest->parse(_storagePath + VERSION_FILENAME);
            
            if (!_remoteManifest->isVersionLoaded())
            {
                CCLOG("Error parsing version file, step skipped\n");
                _updateState = PREDOWNLOAD_MANIFEST;
                checkUpdate();
            }
            else
            {
                if (_localManifest->versionEquals(_remoteManifest))
                {
                    _updateState = UP_TO_DATE;
                    dispatchUpdateEvent(UpdateEventCode::ALREADY_UP_TO_DATE);
                }
                else
                {
                    _updateState = NEED_UPDATE;
                    dispatchUpdateEvent(UpdateEventCode::NEW_VERSION_FOUND);
                    
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
            // No manifest file found
            else
            {
                CCLOG("No manifest file found, check update failed\n");
                dispatchUpdateEvent(UpdateEventCode::FAIL_DOWNLOAD_MANIFEST);
                _updateState = UNKNOWN;
            }
        }
        break;
        case MANIFEST_LOADED:
        {
            if (_remoteManifest == nullptr)
                _remoteManifest = new Manifest(_storagePath + MANIFEST_FILENAME);
            else
                _remoteManifest->parse(_storagePath + MANIFEST_FILENAME);
            
            if (!_remoteManifest->isLoaded())
            {
                CCLOG("Error parsing manifest file\n");
                dispatchUpdateEvent(UpdateEventCode::FAIL_PARSE_MANIFEST);
                _updateState = UNKNOWN;
            }
            else
            {
                if (_localManifest->versionEquals(_remoteManifest))
                {
                    _updateState = UP_TO_DATE;
                    dispatchUpdateEvent(UpdateEventCode::ALREADY_UP_TO_DATE);
                }
                else
                {
                    _updateState = NEED_UPDATE;
                    dispatchUpdateEvent(UpdateEventCode::NEW_VERSION_FOUND);
                    
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
    if (!_localManifest->isLoaded())
    {
        CCLOG("AssetsManager : No local manifest file found error.");
        EventCustom event(_managerId + NO_LOCAL_MANIFEST);
        std::string url = _manifestUrl;
        event.setUserData(&url);
        _eventDispatcher->dispatchEvent(&event);
        return;
    }
    
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
            if (_localManifest != nullptr && _remoteManifest != nullptr)
            {
                std::map<std::string, Manifest::AssetDiff> diff_map = _localManifest->genDiff(_remoteManifest);
                if (diff_map.size() == 0)
                {
                    _updateState = UP_TO_DATE;
                    dispatchUpdateEvent(UpdateEventCode::ALREADY_UP_TO_DATE);
                }
                else
                {
                    _updateState = UPDATING;
                    // UPDATE
                    _downloadUnits.clear();
                    _totalWaitToDownload = _totalToDownload = 0;
                    std::string packageUrl = _remoteManifest->getPackageUrl();
                    for (auto it = diff_map.begin(); it != diff_map.end(); it++) {
                        Manifest::AssetDiff diff = it->second;
                        
                        if (diff.type == Manifest::DELETED) {
                            destroyFile(_storagePath + diff.asset.path);
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
                    _totalWaitToDownload = _totalToDownload = (int)_downloadUnits.size();
                    auto t = std::thread(&Downloader::batchDownload, _downloader, _downloadUnits);
                    t.detach();
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
    _totalWaitToDownload--;
    
    CCLOG("%d : %s\n", error.code, error.message.c_str());
    
    // Skip version error occured
    if (error.customId == "@version")
    {
        CCLOG("Error downloading version file, step skipped\n");
        _updateState = PREDOWNLOAD_MANIFEST;
        checkUpdate();
    }
    else if (error.customId == "@manifest")
        dispatchUpdateEvent(UpdateEventCode::FAIL_DOWNLOAD_MANIFEST);
    else
        dispatchUpdateEvent(UpdateEventCode::UPDATING_ERROR, error.message, error.customId);
}

void AAssetsManager::onProgress(double total, double downloaded, const std::string &url, const std::string &customId)
{
    int percent = (downloaded / total) * 100;
    CCLOG("Progress: %d\n", percent);
    
    EventCustom event(_managerId + UPDATING_PERCENT_EVENT);
    event.setUserData(&percent);
    _eventDispatcher->dispatchEvent(&event);
}

void AAssetsManager::onSuccess(const std::string &srcUrl, const std::string &customId)
{
    CCLOG("SUCCEED: %s\n", customId.c_str());
    _totalWaitToDownload--;
    
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
            // Remove from download unit list
            _downloadUnits.erase(unitIt);
            
            EventCustom updateEvent(_managerId + UPDATING_PERCENT_EVENT);
            double percent = 100 * (_totalToDownload - _downloadUnits.size()) / _totalToDownload;
            updateEvent.setUserData(&percent);
            time_t t = time(0);
            CCLOG("TOTAL DOWNLOAD PROCESS (%ld) : %f\n", t, percent);
            _eventDispatcher->dispatchEvent(&updateEvent);
        }
        // Finish check
        if (_downloadUnits.size() == 0)
        {
            // Every thing is correctly downloaded, swap the localManifest
            setLocalManifest(_remoteManifest);
            
            dispatchUpdateEvent(UpdateEventCode::FINISHED_UPDATE);
        }
        // Finished with error check
        if (_totalWaitToDownload == 0)
        {
            dispatchUpdateEvent(UpdateEventCode::FINISHED_WITH_ERROR);
        }
    }
}

NS_CC_EXT_END;