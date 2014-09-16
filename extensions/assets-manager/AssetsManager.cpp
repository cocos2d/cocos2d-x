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
, _percentByFile(0)
, _manifestUrl(manifestUrl)
, _storagePath("")
, _cacheVersionPath("")
, _cacheManifestPath("")
, _tempManifestPath("")
, _assets(nullptr)
, _localManifest(nullptr)
, _tempManifest(nullptr)
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

    // Init and load local manifest
    _localManifest = new Manifest();
    loadLocalManifest(manifestUrl);
    
    // Init and load temporary manifest
    _tempManifest = new Manifest();
    _tempManifest->parse(_tempManifestPath);
    if (!_tempManifest->isLoaded())
        _fileUtils->removeFile(_tempManifestPath);

    // Init remote manifest for future usage
    _remoteManifest = new Manifest();
}

AssetsManager::~AssetsManager()
{
    _downloader->_onError = nullptr;
    _downloader->_onSuccess = nullptr;
    _downloader->_onProgress = nullptr;
    CC_SAFE_RELEASE(_localManifest);
    // _tempManifest could share a ptr with _remoteManifest or _localManifest
    if (_tempManifest != _localManifest && _tempManifest != _remoteManifest)
        CC_SAFE_RELEASE(_tempManifest);
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

void AssetsManager::loadLocalManifest(const std::string& manifestUrl)
{
    // Prefer to use the cached manifest file, if not found use user configured manifest file
    if (_fileUtils->isFileExist(_cacheManifestPath))
    {
        _localManifest->parse(_cacheManifestPath);
        if (_localManifest->isLoaded())
            prepareLocalManifest();
        else
            _fileUtils->removeFile(_cacheManifestPath);
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
        CCLOG("AssetsManager : No local manifest file found error.\n");
        dispatchUpdateEvent(EventAssetsManager::EventCode::ERROR_NO_LOCAL_MANIFEST);
    }
}

std::string AssetsManager::basename(const std::string& path) const
{
    size_t found = path.find_last_of("/\\");
    
    if (std::string::npos != found)
    {
        return path.substr(0, found);
    }
    else
    {
        return path;
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
        _fileUtils->removeDirectory(_storagePath);

    _storagePath = storagePath;
    adjustPath(_storagePath);
    _fileUtils->createDirectories(_storagePath);
}

void AssetsManager::adjustPath(std::string &path)
{
    if (path.size() > 0 && path[path.size() - 1] != '/')
    {
        path.append("/");
    }
}

bool AssetsManager::decompress(const std::string &zip)
{
    // Find root path for zip file
    size_t pos = zip.find_last_of("/\\");
    if (pos == std::string::npos)
    {
        CCLOG("AssetsManager : no root path specified for zip file %s\n", zip.c_str());
        return false;
    }
    const std::string rootPath = zip.substr(0, pos+1);
    
    // Open the zip file
    unzFile zipfile = unzOpen(zip.c_str());
    if (! zipfile)
    {
        CCLOG("AssetsManager : can not open downloaded zip file %s\n", zip.c_str());
        return false;
    }
    
    // Get info about the zip file
    unz_global_info global_info;
    if (unzGetGlobalInfo(zipfile, &global_info) != UNZ_OK)
    {
        CCLOG("AssetsManager : can not read file global info of %s\n", zip.c_str());
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
            CCLOG("AssetsManager : can not read compressed file info\n");
            unzClose(zipfile);
            return false;
        }
        const std::string fullPath = rootPath + fileName;
        
        // Check if this entry is a directory or a file.
        const size_t filenameLength = strlen(fileName);
        if (fileName[filenameLength-1] == '/')
        {
            //There are not directory entry in some case.
            //So we need to create directory when decompressing file entry
            if ( !_fileUtils->createDirectories(basename(fullPath)) )
            {
                // Failed to create directory
                CCLOG("AssetsManager : can not create directory %s\n", fullPath.c_str());
                unzClose(zipfile);
                return false;
            }
        }
        else
        {
            // Entry is a file, so extract it.
            // Open current file.
            if (unzOpenCurrentFile(zipfile) != UNZ_OK)
            {
                CCLOG("AssetsManager : can not extract file %s\n", fileName);
                unzClose(zipfile);
                return false;
            }
            
            // Create a file to store current file.
            FILE *out = fopen(fullPath.c_str(), "wb");
            if (!out)
            {
                CCLOG("AssetsManager : can not create decompress destination file %s\n", fullPath.c_str());
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
                    CCLOG("AssetsManager : can not read zip file %s, error code is %d\n", fileName, error);
                    fclose(out);
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
                CCLOG("AssetsManager : can not read next file for decompressing\n");
                unzClose(zipfile);
                return false;
            }
        }
    }
    
    unzClose(zipfile);
    return true;
}

void AssetsManager::decompressDownloadedZip()
{
    // Decompress all compressed files
    for (auto it = _compressedFiles.begin(); it != _compressedFiles.end(); ++it) {
        std::string zipfile = *it;
        if (!decompress(zipfile))
        {
            dispatchUpdateEvent(EventAssetsManager::EventCode::ERROR_DECOMPRESS, "", "Unable to decompress file " + zipfile);
        }
        _fileUtils->removeFile(zipfile);
    }
    _compressedFiles.clear();
}

void AssetsManager::dispatchUpdateEvent(EventAssetsManager::EventCode code, const std::string &assetId/* = ""*/, const std::string &message/* = ""*/, int curle_code/* = CURLE_OK*/, int curlm_code/* = CURLM_OK*/)
{
    EventAssetsManager event(_eventName, this, code, _percent, _percentByFile, assetId, message, curle_code, curlm_code);
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

    _updateState = State::UPDATING;
    // Clean up before update
    _failedUnits.clear();
    _downloadUnits.clear();
    _compressedFiles.clear();
    _totalWaitToDownload = _totalToDownload = 0;
    _percent = _percentByFile = _sizeCollected = _totalSize = 0;
    _downloadedSize.clear();
    _totalEnabled = false;
    
    // Temporary manifest exists, resuming previous download
    if (_tempManifest->isLoaded() && _tempManifest->versionEquals(_remoteManifest))
    {
        _tempManifest->genResumeAssetsList(&_downloadUnits);
        
        _totalWaitToDownload = _totalToDownload = (int)_downloadUnits.size();
        _downloader->batchDownloadAsync(_downloadUnits, BATCH_UPDATE_ID);
        
        std::string msg = StringUtils::format("Resuming from previous unfinished update, %d files remains to be finished.", _totalToDownload);
        dispatchUpdateEvent(EventAssetsManager::EventCode::UPDATE_PROGRESSION, "", msg);
    }
    // Check difference
    else
    {
        // Temporary manifest not exists,
        // it will be used to register the download states of each asset,
        // in this case, it equals remote manifest.
        if(!_tempManifest->isLoaded()) {
            _tempManifest->release();
            _tempManifest = _remoteManifest;
        }
        
        std::unordered_map<std::string, Manifest::AssetDiff> diff_map = _localManifest->genDiff(_remoteManifest);
        if (diff_map.size() == 0)
        {
            _updateState = State::UP_TO_DATE;
            // Rename temporary manifest to valid manifest
            _fileUtils->renameFile(_storagePath, TEMP_MANIFEST_FILENAME, MANIFEST_FILENAME);
            dispatchUpdateEvent(EventAssetsManager::EventCode::ALREADY_UP_TO_DATE);
        }
        else
        {
            // Generate download units for all assets that need to be updated or added
            std::string packageUrl = _remoteManifest->getPackageUrl();
            for (auto it = diff_map.begin(); it != diff_map.end(); ++it)
            {
                Manifest::AssetDiff diff = it->second;

                if (diff.type == Manifest::DiffType::DELETED)
                {
                    _fileUtils->removeFile(_storagePath + diff.asset.path);
                }
                else
                {
                    std::string path = diff.asset.path;
                    // Create path
                    _fileUtils->createDirectories(basename(_storagePath + path));

                    Downloader::DownloadUnit unit;
                    unit.customId = it->first;
                    unit.srcUrl = packageUrl + path;
                    unit.storagePath = _storagePath + path;
                    unit.resumeDownload = false;
                    _downloadUnits.emplace(unit.customId, unit);
                }
            }
            // Set other assets' downloadState to SUCCESSED
            auto assets = _remoteManifest->getAssets();
            for (auto it = assets.cbegin(); it != assets.cend(); ++it)
            {
                const std::string &key = it->first;
                auto diffIt = diff_map.find(key);
                if (diffIt == diff_map.end())
                {
                    _tempManifest->setAssetDownloadState(key, Manifest::DownloadState::SUCCESSED);
                }
            }
            
            _totalWaitToDownload = _totalToDownload = (int)_downloadUnits.size();
            _downloader->batchDownloadAsync(_downloadUnits, BATCH_UPDATE_ID);
            
            std::string msg = StringUtils::format("Start to update %d files from remote package.", _totalToDownload);
            dispatchUpdateEvent(EventAssetsManager::EventCode::UPDATE_PROGRESSION, "", msg);
        }
    }

    _waitToUpdate = false;
}

void AssetsManager::updateSucceed()
{
    // Every thing is correctly downloaded, do the following
    // 1. rename temporary manifest to valid manifest
    _fileUtils->renameFile(_storagePath, TEMP_MANIFEST_FILENAME, MANIFEST_FILENAME);
    // 2. swap the localManifest
    if (_localManifest != nullptr)
        _localManifest->release();
    _localManifest = _remoteManifest;
    _remoteManifest = nullptr;
    // 3. make local manifest take effect
    prepareLocalManifest();
    // 4. decompress all compressed files
    decompressDownloadedZip();
    // 5. Set update state
    _updateState = State::UP_TO_DATE;
    // 6. Notify finished event
    dispatchUpdateEvent(EventAssetsManager::EventCode::UPDATE_FINISHED);
}

void AssetsManager::checkUpdate()
{
    if (!_localManifest->isLoaded())
    {
        CCLOG("AssetsManager : No local manifest file found error.\n");
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
        CCLOG("AssetsManager : No local manifest file found error.\n");
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

void AssetsManager::updateAssets(const Downloader::DownloadUnits& assets)
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
        else if (size == 0 && _totalWaitToDownload == 0)
        {
            updateSucceed();
        }
    }
}

const Downloader::DownloadUnits& AssetsManager::getFailedAssets() const
{
    return _failedUnits;
}

void AssetsManager::downloadFailedAssets()
{
    CCLOG("AssetsManager : Start update %lu failed assets.\n", _failedUnits.size());
    updateAssets(_failedUnits);
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
    else
    {
        // Calcul total downloaded
        bool found = false;
        double totalDownloaded = 0;
        for (auto it = _downloadedSize.begin(); it != _downloadedSize.end(); ++it)
        {
            if (it->first == customId)
            {
                it->second = downloaded;
                found = true;
            }
            totalDownloaded += it->second;
        }
        // Collect information if not registed
        if (!found)
        {
            // Set download state to DOWNLOADING, this will run only once in the download process
            _tempManifest->setAssetDownloadState(customId, Manifest::DownloadState::DOWNLOADING);
            // Register the download size information
            _downloadedSize.emplace(customId, downloaded);
            _totalSize += total;
            _sizeCollected++;
            // All collected, enable total size
            if (_sizeCollected == _totalToDownload)
            {
                _totalEnabled = true;
            }
        }
        
        if (_totalEnabled && _updateState == State::UPDATING)
        {
            float currentPercent = 100 * totalDownloaded / _totalSize;
            // Notify at integer level change
            if ((int)currentPercent != (int)_percent) {
                _percent = currentPercent;
                // Notify progression event
                dispatchUpdateEvent(EventAssetsManager::EventCode::UPDATE_PROGRESSION, "");
            }
        }
    }
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
            // Save current download manifest information for resuming
            _tempManifest->saveToFile(_tempManifestPath);
            
            decompressDownloadedZip();
            
            _updateState = State::FAIL_TO_UPDATE;
            dispatchUpdateEvent(EventAssetsManager::EventCode::UPDATE_FAILED);
        }
        else
        {
            updateSucceed();
        }
    }
    else
    {
        auto assets = _remoteManifest->getAssets();
        auto assetIt = assets.find(customId);
        if (assetIt != assets.end())
        {
            // Set download state to SUCCESSED
            _tempManifest->setAssetDownloadState(customId, Manifest::DownloadState::SUCCESSED);
            
            // Add file to need decompress list
            if (assetIt->second.compressed) {
                _compressedFiles.push_back(storagePath);
            }
        }
        
        auto unitIt = _downloadUnits.find(customId);
        if (unitIt != _downloadUnits.end())
        {
            // Reduce count only when unit found in _downloadUnits
            _totalWaitToDownload--;
            
            _percentByFile = 100 * (float)(_totalToDownload - _totalWaitToDownload) / _totalToDownload;
            // Notify progression event
            dispatchUpdateEvent(EventAssetsManager::EventCode::UPDATE_PROGRESSION, "");
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
    }
}

void AssetsManager::destroyDownloadedVersion()
{
    _fileUtils->removeFile(_cacheVersionPath);
    _fileUtils->removeFile(_cacheManifestPath);
}

NS_CC_EXT_END
