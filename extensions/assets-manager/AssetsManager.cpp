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
#include "AssetsManager.h"

#include "CCEventListenerAssetsManager.h"

#include <curl/curl.h>
#include <curl/easy.h>
#include <stdio.h>

#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32) && (CC_TARGET_PLATFORM != CC_PLATFORM_WP8) && (CC_TARGET_PLATFORM != CC_PLATFORM_WINRT)
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <dirent.h>
#endif

#include "unzip.h"

NS_CC_EXT_BEGIN

#define ENABLE_MULTITHREAD      0

#define VERSION_FILENAME        "version.manifest"
#define TEMP_MANIFEST_FILENAME  "project.manifest.temp"
#define MANIFEST_FILENAME       "project.manifest"

#define DEFAULT_CONNECTION_TIMEOUT 8

const std::string AssetsManager::VERSION_ID = "@version";
const std::string AssetsManager::MANIFEST_ID = "@manifest";

// Implementation of AssetsManager

AssetsManager::AssetsManager(const std::string& manifestUrl, const std::string& storagePath)
: _updateState(State::UNCHECKED)
, _waitToUpdate(false)
, _totalToDownload(0)
, _totalWaitToDownload(0)
, _percent(0)
, _manifestUrl(manifestUrl)
, _storagePath("")
, _cacheVersionPath("")
, _cacheManifestPath("")
, _tempManifestPath("")
, _assets(nullptr)
, _localManifest(nullptr)
, _remoteManifest(nullptr)
{
    // Init variables
    _eventDispatcher = Director::getInstance()->getEventDispatcher();
    std::string pointer = StringUtils::format("%p", this);
    _eventName = EventListenerAssetsManager::LISTENER_ID + pointer;
    _fileUtils = FileUtils::getInstance();
    _updateState = State::UNCHECKED;

    _downloader = std::make_shared<Downloader>();
    _downloader->setConnectionTimeout(DEFAULT_CONNECTION_TIMEOUT);
    _downloader->_onError = std::bind( &AssetsManager::onError, this, std::placeholders::_1 );
    _downloader->_onProgress = std::bind(&AssetsManager::onProgress,
                                         this,
                                         std::placeholders::_1,
                                         std::placeholders::_2,
                                         std::placeholders::_3,
                                         std::placeholders::_4);
    _downloader->_onSuccess = std::bind(&AssetsManager::onSuccess, this, std::placeholders::_1, std::placeholders::_2);
    setStoragePath(storagePath);
    _cacheVersionPath = _storagePath + VERSION_FILENAME;
    _cacheManifestPath = _storagePath + MANIFEST_FILENAME;
    _tempManifestPath = _storagePath + TEMP_MANIFEST_FILENAME;

    _localManifest = new Manifest();
    loadManifest(manifestUrl);

    _remoteManifest = new Manifest();
}

AssetsManager::~AssetsManager()
{
    removeFile(_tempManifestPath);
    _downloader->_onError = nullptr;
    _downloader->_onSuccess = nullptr;
    _downloader->_onProgress = nullptr;
    CC_SAFE_RELEASE(_localManifest);
    CC_SAFE_RELEASE(_remoteManifest);
}

AssetsManager* AssetsManager::create(const std::string& manifestUrl, const std::string& storagePath)
{
    AssetsManager* ret = new AssetsManager(manifestUrl, storagePath);
    if (ret)
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

void AssetsManager::prepareLocalManifest()
{
    // An alias to assets
    _assets = &(_localManifest->getAssets());

    // Add search paths
    _localManifest->prependSearchPaths();
}

void AssetsManager::loadManifest(const std::string& manifestUrl)
{
    // Prefer to use the cached manifest file, if not found use user configured manifest file
    // Prepend storage path to avoid multi package conflict issue
    if (_fileUtils->isFileExist(_cacheManifestPath))
    {
        _localManifest->parse(_cacheManifestPath);
        if (_localManifest->isLoaded())
            prepareLocalManifest();
        else
            removeFile(_cacheManifestPath);
    }
    // Fail to found or load cached manifest file
    else
    {
        _localManifest->parse(_manifestUrl);
        if (_localManifest->isLoaded())
            prepareLocalManifest();
    }

    // Fail to load local manifest
    if (!_localManifest->isLoaded())
    {
        CCLOG("AssetsManager : No local manifest file found error.");
        dispatchUpdateEvent(EventAssetsManager::EventCode::ERROR_NO_LOCAL_MANIFEST);
    }
}

std::string AssetsManager::get(const std::string& key) const
{
    auto it = _assets->find(key);
    if (it != _assets->cend()) {
        return _storagePath + it->second.path;
    }
    else return "";
}

const Manifest* AssetsManager::getLocalManifest() const
{
    return _localManifest;
}

const Manifest* AssetsManager::getRemoteManifest() const
{
    return _remoteManifest;
}

const std::string& AssetsManager::getStoragePath() const
{
    return _storagePath;
}

void AssetsManager::setStoragePath(const std::string& storagePath)
{
    if (_storagePath.size() > 0)
        removeDirectory(_storagePath);

    _storagePath = storagePath;
    adjustPath(_storagePath);
    createDirectory(_storagePath);
}

void AssetsManager::adjustPath(std::string &path)
{
    if (path.size() > 0 && path[path.size() - 1] != '/')
    {
        path.append("/");
    }
}

void AssetsManager::createDirectory(const std::string& path)
{
    // Split the path
    size_t start = 0;
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
    subpath = "";
    for (int i = 0; i < dirs.size(); ++i) {
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
		subpath = "";
		for(int i = 0 ; i < dirs.size() ; ++i)
		{
			subpath += dirs[i];
			CreateDirectoryA(subpath.c_str(), NULL);
		}
    }
#endif
}

void AssetsManager::removeDirectory(const std::string& path)
{
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
    std::string command = "rd /s /q ";
    // Path may include space.
    command += "\"" + path + "\"";
	WinExec(command.c_str(), SW_HIDE);
#endif
}

void AssetsManager::removeFile(const std::string &path)
{
    // Remove downloaded file
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
    std::string command = "rm -f ";
    // Path may include space.
    command += "\"" + path + "\"";
    system(command.c_str());
#else
    std::string command = "del /q ";
    // Path may include space.
    command += "\"" + path + "\"";
	WinExec(command.c_str(), SW_HIDE);
#endif
}

void AssetsManager::renameFile(const std::string &path, const std::string &oldname, const std::string &name)
{
    // Rename a file
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
    std::string oldPath = path + oldname;
    std::string newPath = path + name;
    if (rename(oldPath.c_str(), newPath.c_str()) != 0)
    {
        CCLOGERROR("Error: Rename file %s to %s !", oldPath.c_str(), newPath.c_str());
    }
#else
    std::string command = "ren ";
    // Path may include space.
    command += "\"" + path + oldname + "\" \"" + name + "\"";
	WinExec(command.c_str(), SW_HIDE);
#endif
}

void AssetsManager::dispatchUpdateEvent(EventAssetsManager::EventCode code, std::string assetId/* = ""*/, std::string message/* = ""*/)
{
    EventAssetsManager event(_eventName, this, code, _percent, assetId, message);
    _eventDispatcher->dispatchEvent(&event);
}

AssetsManager::State AssetsManager::getState() const
{
    return _updateState;
}

void AssetsManager::downloadVersion()
{
    if (_updateState != State::PREDOWNLOAD_VERSION)
        return;

    std::string versionUrl = _localManifest->getVersionFileUrl();

    if (versionUrl.size() > 0)
    {
        _updateState = State::DOWNLOADING_VERSION;
        // Download version file asynchronously
        _downloader->downloadAsync(versionUrl, _cacheVersionPath, VERSION_ID);
    }
    // No version file found
    else
    {
        CCLOG("No version file found, step skipped\n");
        _updateState = State::PREDOWNLOAD_MANIFEST;
        downloadManifest();
    }
}

void AssetsManager::parseVersion()
{
    if (_updateState != State::VERSION_LOADED)
        return;

    _remoteManifest->parse(_cacheVersionPath);

    if (!_remoteManifest->isVersionLoaded())
    {
        CCLOG("Error parsing version file, step skipped\n");
        _updateState = State::PREDOWNLOAD_MANIFEST;
        downloadManifest();
    }
    else
    {
        if (_localManifest->versionEquals(_remoteManifest))
        {
            _updateState = State::UP_TO_DATE;
            dispatchUpdateEvent(EventAssetsManager::EventCode::ALREADY_UP_TO_DATE);
        }
        else
        {
            _updateState = State::NEED_UPDATE;
            dispatchUpdateEvent(EventAssetsManager::EventCode::NEW_VERSION_FOUND);

            // Wait to update so continue the process
            if (_waitToUpdate)
            {
                _updateState = State::PREDOWNLOAD_MANIFEST;
                downloadManifest();
            }
        }
    }
}

void AssetsManager::downloadManifest()
{
    if (_updateState != State::PREDOWNLOAD_MANIFEST)
        return;

    std::string manifestUrl = _localManifest->getManifestFileUrl();
    if (manifestUrl.size() > 0)
    {
        _updateState = State::DOWNLOADING_MANIFEST;
        // Download version file asynchronously
        _downloader->downloadAsync(manifestUrl, _tempManifestPath, MANIFEST_ID);
    }
    // No manifest file found
    else
    {
        CCLOG("No manifest file found, check update failed\n");
        dispatchUpdateEvent(EventAssetsManager::EventCode::ERROR_DOWNLOAD_MANIFEST);
        _updateState = State::UNCHECKED;
    }
}

void AssetsManager::parseManifest()
{
    if (_updateState != State::MANIFEST_LOADED)
        return;

    _remoteManifest->parse(_tempManifestPath);

    if (!_remoteManifest->isLoaded())
    {
        CCLOG("Error parsing manifest file\n");
        dispatchUpdateEvent(EventAssetsManager::EventCode::ERROR_PARSE_MANIFEST);
        _updateState = State::UNCHECKED;
        removeFile(_tempManifestPath);
    }
    else
    {
        if (_localManifest->versionEquals(_remoteManifest))
        {
            _updateState = State::UP_TO_DATE;
            removeFile(_tempManifestPath);
            dispatchUpdateEvent(EventAssetsManager::EventCode::ALREADY_UP_TO_DATE);
        }
        else
        {
            _updateState = State::NEED_UPDATE;
            dispatchUpdateEvent(EventAssetsManager::EventCode::NEW_VERSION_FOUND);

            if (_waitToUpdate)
            {
                update();
            }
        }
    }
}

void AssetsManager::startUpdate()
{
    if (_updateState != State::NEED_UPDATE)
        return;

    // Check difference
    if (_localManifest != nullptr && _remoteManifest != nullptr)
    {
        std::unordered_map<std::string, Manifest::AssetDiff> diff_map = _localManifest->genDiff(_remoteManifest);
        if (diff_map.size() == 0)
        {
            _updateState = State::UP_TO_DATE;
            // Rename temporary manifest to valid manifest
            renameFile(_storagePath, TEMP_MANIFEST_FILENAME, MANIFEST_FILENAME);
            dispatchUpdateEvent(EventAssetsManager::EventCode::ALREADY_UP_TO_DATE);
        }
        else
        {
            _updateState = State::UPDATING;
            // UPDATE
            _downloadUnits.clear();
            _totalWaitToDownload = _totalToDownload = 0;
            std::string packageUrl = _remoteManifest->getPackageUrl();
            for (auto it = diff_map.begin(); it != diff_map.end(); ++it) {
                Manifest::AssetDiff diff = it->second;

                if (diff.type == Manifest::DiffType::DELETED) {
                    removeFile(_storagePath + diff.asset.path);
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
#if ENABLE_MULTITHREAD
            _downloader->batchDownload(_downloadUnits);
#else
            auto t = std::thread(&AssetsManager::batchDownload, this, _downloadUnits);
            t.detach();
#endif
        }
    }

    _waitToUpdate = false;
}

void AssetsManager::checkUpdate()
{
    if (!_localManifest->isLoaded())
    {
        CCLOG("AssetsManager : No local manifest file found error.");
        dispatchUpdateEvent(EventAssetsManager::EventCode::ERROR_NO_LOCAL_MANIFEST);
        return;
    }

    switch (_updateState) {
        case State::UNCHECKED:
        case State::PREDOWNLOAD_VERSION:
        {
            downloadVersion();
        }
            break;
        case State::UP_TO_DATE:
        {
            dispatchUpdateEvent(EventAssetsManager::EventCode::ALREADY_UP_TO_DATE);
        }
            break;
        case State::FAIL_TO_UPDATE:
        case State::NEED_UPDATE:
        {
            dispatchUpdateEvent(EventAssetsManager::EventCode::NEW_VERSION_FOUND);
        }
            break;
        default:
            break;
    }
}

void AssetsManager::update()
{
    if (!_localManifest->isLoaded())
    {
        CCLOG("AssetsManager : No local manifest file found error.");
        dispatchUpdateEvent(EventAssetsManager::EventCode::ERROR_NO_LOCAL_MANIFEST);
        return;
    }

    _waitToUpdate = true;

    switch (_updateState) {
        case State::UNCHECKED:
        {
            _updateState = State::PREDOWNLOAD_VERSION;
        }
        case State::PREDOWNLOAD_VERSION:
        {
            downloadVersion();
        }
            break;
        case State::VERSION_LOADED:
        {
            parseVersion();
        }
            break;
        case State::PREDOWNLOAD_MANIFEST:
        {
            downloadManifest();
        }
            break;
        case State::MANIFEST_LOADED:
        {
            parseManifest();
        }
            break;
        case State::FAIL_TO_UPDATE:
        case State::NEED_UPDATE:
        {
            // Manifest not loaded yet
            if (!_remoteManifest->isLoaded())
            {
                _waitToUpdate = true;
                _updateState = State::PREDOWNLOAD_MANIFEST;
                downloadManifest();
            }
            else
            {
                startUpdate();
            }
        }
            break;
        case State::UP_TO_DATE:
        case State::UPDATING:
            _waitToUpdate = false;
            break;
        default:
            break;
    }
}

void AssetsManager::batchDownload(const std::unordered_map<std::string, Downloader::DownloadUnit> &units)
{
    for (auto it = units.cbegin(); it != units.cend(); ++it) {
        Downloader::DownloadUnit unit = it->second;
        std::string srcUrl = unit.srcUrl;
        std::string storagePath = unit.storagePath;
        std::string customId = unit.customId;
        
        _downloader->downloadAsync(srcUrl, storagePath, customId);
    }
}


void AssetsManager::onError(const Downloader::Error &error)
{
    // Skip version error occured
    if (error.customId == VERSION_ID)
    {
        CCLOG("Error downloading version file, step skipped\n");
        _updateState = State::PREDOWNLOAD_MANIFEST;
        downloadManifest();
    }
    else if (error.customId == MANIFEST_ID)
    {
        dispatchUpdateEvent(EventAssetsManager::EventCode::ERROR_DOWNLOAD_MANIFEST);
    }
    else
    {
        _totalWaitToDownload--;
        dispatchUpdateEvent(EventAssetsManager::EventCode::ERROR_UPDATING, error.customId, error.message);
    }
}

void AssetsManager::onProgress(double total, double downloaded, const std::string &url, const std::string &customId)
{
    if (customId == VERSION_ID || customId == MANIFEST_ID)
    {
        _percent = 100 * (total - downloaded) / total;
        // Notify progression event
        dispatchUpdateEvent(EventAssetsManager::EventCode::UPDATE_PROGRESSION, customId);
        return;
    }
// TODO : Calculate the precised percentage of download
}

void AssetsManager::onSuccess(const std::string &srcUrl, const std::string &customId)
{
    if (customId == VERSION_ID)
    {
        _updateState = State::VERSION_LOADED;
        parseVersion();
    }
    else if (customId == MANIFEST_ID)
    {
        _updateState = State::MANIFEST_LOADED;
        parseManifest();
    }
    else
    {
        _totalWaitToDownload--;
        // Notify asset updated event
        dispatchUpdateEvent(EventAssetsManager::EventCode::ASSET_UPDATED, customId);

        auto unitIt = _downloadUnits.find(customId);
        // Found unit and delete it
        if (unitIt != _downloadUnits.end())
        {
            // Remove from download unit list
            _downloadUnits.erase(unitIt);

            if (_updateState == State::UPDATING) {
                _percent = 100 * (_totalToDownload - _downloadUnits.size()) / _totalToDownload;
                // Notify progression event
                dispatchUpdateEvent(EventAssetsManager::EventCode::UPDATE_PROGRESSION, customId);
            }
        }
        // Finish check
        if (_totalWaitToDownload == 0)
        {
            // Finished with error check
            if (_downloadUnits.size() > 0)
            {
                _updateState = State::FAIL_TO_UPDATE;
                destroyDownloadedVersion();
            }
            else
            {
                // Every thing is correctly downloaded, do the following
                // 1. rename temporary manifest to valid manifest
                renameFile(_storagePath, TEMP_MANIFEST_FILENAME, MANIFEST_FILENAME);
                // 2. swap the localManifest
                if (_localManifest != nullptr)
                    _localManifest->release();
                _localManifest = _remoteManifest;
                _remoteManifest = nullptr;
                // 3. make local manifest take effect
                prepareLocalManifest();
                // 4. Set update state
                _updateState = State::UP_TO_DATE;
            }
            // Notify finished event
            dispatchUpdateEvent(EventAssetsManager::EventCode::UPDATE_FINISHED);
        }
    }
}

void AssetsManager::destroyDownloadedVersion()
{
    removeFile(_cacheVersionPath);
    removeFile(_cacheManifestPath);
}

NS_CC_EXT_END
