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

#define VERSION_FILENAME        "version.manifest"
#define TEMP_MANIFEST_FILENAME  "project.manifest.temp"
#define MANIFEST_FILENAME       "project.manifest"

#define BUFFER_SIZE    8192
#define MAX_FILENAME   512

#define DEFAULT_CONNECTION_TIMEOUT 8

const std::string AssetsManager::VERSION_ID = "@version";
const std::string AssetsManager::MANIFEST_ID = "@manifest";
const std::string AssetsManager::BATCH_UPDATE_ID = "@batch_update";

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
    _downloader->_onError = std::bind(&AssetsManager::onError, this, std::placeholders::_1);
    _downloader->_onProgress = std::bind(&AssetsManager::onProgress,
                                         this,
                                         std::placeholders::_1,
                                         std::placeholders::_2,
                                         std::placeholders::_3,
                                         std::placeholders::_4);
    _downloader->_onSuccess = std::bind(&AssetsManager::onSuccess, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
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
    if (!_localManifest->isLoaded())
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

bool AssetsManager::createDirectory(const std::string& path)
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

#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
    DIR *dir = NULL;

    // Create path recursively
    subpath = "";
    for (int i = 0; i < dirs.size(); ++i) {
        subpath += dirs[i];
        dir = opendir(subpath.c_str());
        if (!dir)
        {
            int ret = mkdir(subpath.c_str(), S_IRWXU | S_IRWXG | S_IRWXO);
            if (ret != 0 && (errno != EEXIST))
            {
                return false;
            }
        }
    }
    return true;
#else
    if ((GetFileAttributesA(path.c_str())) == INVALID_FILE_ATTRIBUTES)
    {
		subpath = "";
		for(int i = 0 ; i < dirs.size() ; ++i)
		{
			subpath += dirs[i];
			BOOL ret = CreateDirectoryA(subpath.c_str(), NULL);
            if (!ret && ERROR_ALREADY_EXISTS != GetLastError())
            {
                return false;
            }
		}
    }
    return true;
#endif
}

bool AssetsManager::removeDirectory(const std::string& path)
{
    if (path.size() > 0 && path[path.size() - 1] != '/')
    {
        CCLOGERROR("Fail to remove directory, invalid path: %s", path.c_str());
        return false;
    }

    // Remove downloaded files
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
    std::string command = "rm -r ";
    // Path may include space.
    command += "\"" + path + "\"";
    if (system(command.c_str()) >= 0)
        return true;
    else
        return false;
#else
    std::string command = "rd /s /q ";
    // Path may include space.
    command += "\"" + path + "\"";
	if (WinExec(command.c_str(), SW_HIDE) > 31)
        return true;
    else
        return false;
#endif
}

bool AssetsManager::removeFile(const std::string &path)
{
    // Remove downloaded file
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
    std::string command = "rm -f ";
    // Path may include space.
    command += "\"" + path + "\"";
    if (system(command.c_str()) >= 0)
        return true;
    else
        return false;
#else
    std::string command = "del /q ";
    // Path may include space.
    command += "\"" + path + "\"";
	if (WinExec(command.c_str(), SW_HIDE) > 31)
        return true;
    else
        return false;
#endif
}

bool AssetsManager::renameFile(const std::string &path, const std::string &oldname, const std::string &name)
{
    // Rename a file
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
    std::string oldPath = path + oldname;
    std::string newPath = path + name;
    if (rename(oldPath.c_str(), newPath.c_str()) != 0)
    {
        CCLOGERROR("Fail to rename file %s to %s !", oldPath.c_str(), newPath.c_str());
        return false;
    }
    return true;
#else
    std::string command = "ren ";
    // Path may include space.
    command += "\"" + path + oldname + "\" \"" + name + "\"";
	if (WinExec(command.c_str(), SW_HIDE) > 31)
        return true;
    else
        return false;
#endif
}

bool AssetsManager::decompress(std::string zip)
{
    // Find root path for zip file
    size_t pos = zip.find_last_of("/\\");
    if (pos == std::string::npos)
    {
        CCLOG("AssetsManager : no root path specified for zip file %s", zip.c_str());
        return false;
    }
    const std::string rootPath = zip.substr(0, pos+1);
    
    // Open the zip file
    unzFile zipfile = unzOpen(zip.c_str());
    if (! zipfile)
    {
        CCLOG("AssetsManager : can not open downloaded zip file %s", zip.c_str());
        return false;
    }
    
    // Get info about the zip file
    unz_global_info global_info;
    if (unzGetGlobalInfo(zipfile, &global_info) != UNZ_OK)
    {
        CCLOG("AssetsManager : can not read file global info of %s", zip.c_str());
        unzClose(zipfile);
        return false;
    }
    
    // Buffer to hold data read from the zip file
    char readBuffer[BUFFER_SIZE];
    // Loop to extract all files.
    uLong i;
    for (i = 0; i < global_info.number_entry; ++i)
    {
        // Get info about current file.
        unz_file_info fileInfo;
        char fileName[MAX_FILENAME];
        if (unzGetCurrentFileInfo(zipfile,
                                  &fileInfo,
                                  fileName,
                                  MAX_FILENAME,
                                  NULL,
                                  0,
                                  NULL,
                                  0) != UNZ_OK)
        {
            CCLOG("AssetsManager : can not read compressed file info");
            unzClose(zipfile);
            return false;
        }
        
        const std::string fullPath = rootPath + fileName;
        
        //There are not directory entry in some case.
        //So we need to create directory when decompressing file entry
        if ( !createDirectory(fullPath) )
        {
            // Failed to create directory
            CCLOG("AssetsManager : can not create directory %s", fullPath.c_str());
            unzClose(zipfile);
            return false;
        }
        
        // Check if this entry is a directory or a file.
        const size_t filenameLength = strlen(fileName);
        if (fileName[filenameLength-1] != '/')
        {
            // Entry is a file, so extract it.
            // Open current file.
            if (unzOpenCurrentFile(zipfile) != UNZ_OK)
            {
                CCLOG("AssetsManager : can not extract file %s", fileName);
                unzClose(zipfile);
                return false;
            }
            
            // Create a file to store current file.
            FILE *out = fopen(fullPath.c_str(), "wb");
            if (!out)
            {
                CCLOG("AssetsManager : can not create decompress destination file %s", fullPath.c_str());
                unzCloseCurrentFile(zipfile);
                unzClose(zipfile);
                return false;
            }
            
            // Write current file content to destinate file.
            int error = UNZ_OK;
            do
            {
                error = unzReadCurrentFile(zipfile, readBuffer, BUFFER_SIZE);
                if (error < 0)
                {
                    CCLOG("AssetsManager : can not read zip file %s, error code is %d", fileName, error);
                    unzCloseCurrentFile(zipfile);
                    unzClose(zipfile);
                    return false;
                }
                
                if (error > 0)
                {
                    fwrite(readBuffer, error, 1, out);
                }
            } while(error > 0);
            
            fclose(out);
        }
        
        unzCloseCurrentFile(zipfile);
        
        // Goto next entry listed in the zip file.
        if ((i+1) < global_info.number_entry)
        {
            if (unzGoToNextFile(zipfile) != UNZ_OK)
            {
                CCLOG("AssetsManager : can not read next file for decompressing");
                unzClose(zipfile);
                return false;
            }
        }
    }
    
    unzClose(zipfile);
    return true;
}

void AssetsManager::dispatchUpdateEvent(EventAssetsManager::EventCode code, std::string assetId/* = ""*/, std::string message/* = ""*/, int curle_code/* = CURLE_OK*/, int curlm_code/* = CURLM_OK*/)
{
    EventAssetsManager event(_eventName, this, code, _percent, assetId, message, curle_code, curlm_code);
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
        CCLOG("AssetsManager : No version file found, step skipped\n");
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
        CCLOG("AssetsManager : Fail to parse version file, step skipped\n");
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
        CCLOG("AssetsManager : No manifest file found, check update failed\n");
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
        CCLOG("AssetsManager : Error parsing manifest file\n");
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
                startUpdate();
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
            _failedUnits.clear();
            _downloadUnits.clear();
            _compressedFiles.clear();
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
            _downloader->batchDownloadAsync(_downloadUnits, BATCH_UPDATE_ID);
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

void AssetsManager::updateAssets(const std::unordered_map<std::string, Downloader::DownloadUnit>& assets)
{
    if (_updateState != State::UPDATING && _localManifest->isLoaded() && _remoteManifest->isLoaded())
    {
        int size = (int)(assets.size());
        if (size > 0)
        {
            _updateState = State::UPDATING;
            _downloadUnits.clear();
            _downloadUnits = assets;
            _downloader->batchDownloadAsync(_downloadUnits, BATCH_UPDATE_ID);
        }
    }
}

const std::unordered_map<std::string, Downloader::DownloadUnit>& AssetsManager::getFailedAssets() const
{
    return _failedUnits;
}


void AssetsManager::onError(const Downloader::Error &error)
{
    // Skip version error occured
    if (error.customId == VERSION_ID)
    {
        CCLOG("AssetsManager : Fail to download version file, step skipped\n");
        _updateState = State::PREDOWNLOAD_MANIFEST;
        downloadManifest();
    }
    else if (error.customId == MANIFEST_ID)
    {
        dispatchUpdateEvent(EventAssetsManager::EventCode::ERROR_DOWNLOAD_MANIFEST, error.customId, error.message, error.curle_code, error.curlm_code);
    }
    else
    {
        auto unitIt = _downloadUnits.find(error.customId);
        // Found unit and add it to failed units
        if (unitIt != _downloadUnits.end())
        {
            Downloader::DownloadUnit unit = unitIt->second;
            _failedUnits.emplace(unit.customId, unit);
        }
        dispatchUpdateEvent(EventAssetsManager::EventCode::ERROR_UPDATING, error.customId, error.message, error.curle_code, error.curlm_code);
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

void AssetsManager::onSuccess(const std::string &srcUrl, const std::string &storagePath, const std::string &customId)
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
    else if (customId == BATCH_UPDATE_ID)
    {
        // Finished with error check
        if (_failedUnits.size() > 0 || _totalWaitToDownload > 0)
        {
            _updateState = State::FAIL_TO_UPDATE;
            dispatchUpdateEvent(EventAssetsManager::EventCode::UPDATE_FAILED);
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
            // 4. decompress all compressed files
            for (auto it = _compressedFiles.begin(); it != _compressedFiles.end(); ++it) {
                std::string zipfile = *it;
                if (!decompress(zipfile))
                {
                    dispatchUpdateEvent(EventAssetsManager::EventCode::ERROR_DECOMPRESS, "", "Unable to decompress file " + zipfile);
                }
                removeFile(zipfile);
            }
            // 5. Set update state
            _updateState = State::UP_TO_DATE;
            // 6. Notify finished event
            dispatchUpdateEvent(EventAssetsManager::EventCode::UPDATE_FINISHED);
        }
    }
    else
    {
        // Add file to need decompress list
        auto assets = _remoteManifest->getAssets();
        auto assetIt = assets.find(customId);
        if (assetIt != assets.end()) {
            if (assetIt->second.compressed) {
                _compressedFiles.push_back(storagePath);
            }
        }
        
        auto unitIt = _downloadUnits.find(customId);
        if (unitIt != _downloadUnits.end())
        {
            // Reduce count only when unit found in _downloadUnits
            _totalWaitToDownload--;
        }
        // Notify asset updated event
        dispatchUpdateEvent(EventAssetsManager::EventCode::ASSET_UPDATED, customId);
        
        unitIt = _failedUnits.find(customId);
        // Found unit and delete it
        if (unitIt != _failedUnits.end())
        {
            // Remove from failed units list
            _failedUnits.erase(unitIt);
        }

        if (_updateState == State::UPDATING) {
            _percent = 100 * (_totalToDownload - _totalWaitToDownload) / _totalToDownload;
            // Notify progression event
            dispatchUpdateEvent(EventAssetsManager::EventCode::UPDATE_PROGRESSION, customId);
        }
    }
}

void AssetsManager::destroyDownloadedVersion()
{
    removeFile(_cacheVersionPath);
    removeFile(_cacheManifestPath);
}

NS_CC_EXT_END
