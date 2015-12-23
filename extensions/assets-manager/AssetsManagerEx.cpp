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
#include "AssetsManagerEx.h"
#include "CCEventListenerAssetsManagerEx.h"
#include "deprecated/CCString.h"
#include "base/CCDirector.h"

#include <stdio.h>

#ifdef MINIZIP_FROM_SYSTEM
#include <minizip/unzip.h>
#else // from our embedded sources
#include "unzip.h"
#endif
#include "base/CCAsyncTaskPool.h"

using namespace cocos2d;
using namespace std;

NS_CC_EXT_BEGIN

#define VERSION_FILENAME        "version.manifest"
#define TEMP_MANIFEST_FILENAME  "project.manifest.temp"
#define MANIFEST_FILENAME       "project.manifest"

#define BUFFER_SIZE    8192
#define MAX_FILENAME   512

#define DEFAULT_CONNECTION_TIMEOUT 8

const std::string AssetsManagerEx::VERSION_ID = "@version";
const std::string AssetsManagerEx::MANIFEST_ID = "@manifest";

// Implementation of AssetsManagerEx

AssetsManagerEx::AssetsManagerEx(const std::string& manifestUrl, const std::string& storagePath)
: _updateState(State::UNCHECKED)
, _assets(nullptr)
, _storagePath("")
, _cacheVersionPath("")
, _cacheManifestPath("")
, _tempManifestPath("")
, _manifestUrl(manifestUrl)
, _localManifest(nullptr)
, _tempManifest(nullptr)
, _remoteManifest(nullptr)
, _waitToUpdate(false)
, _percent(0)
, _percentByFile(0)
, _totalToDownload(0)
, _totalWaitToDownload(0)
, _inited(false)
{
    // Init variables
    _eventDispatcher = Director::getInstance()->getEventDispatcher();
    std::string pointer = StringUtils::format("%p", this);
    _eventName = EventListenerAssetsManagerEx::LISTENER_ID + pointer;
    _fileUtils = FileUtils::getInstance();
    _updateState = State::UNCHECKED;

    _downloader = std::shared_ptr<network::Downloader>(new network::Downloader);
//    _downloader->setConnectionTimeout(DEFAULT_CONNECTION_TIMEOUT);
    _downloader->onTaskError = bind(&AssetsManagerEx::onError, this, placeholders::_1, placeholders::_2, placeholders::_3, placeholders::_4);
    _downloader->onTaskProgress = [this](const network::DownloadTask& task,
                                         int64_t bytesReceived,
                                         int64_t totalBytesReceived,
                                         int64_t totalBytesExpected)
    {
        this->onProgress(totalBytesExpected, totalBytesReceived, task.requestURL, task.identifier);
    };
    _downloader->onFileTaskSuccess = [this](const network::DownloadTask& task)
    {
        this->onSuccess(task.requestURL, task.storagePath, task.identifier);
    };
    setStoragePath(storagePath);
    _cacheVersionPath = _storagePath + VERSION_FILENAME;
    _cacheManifestPath = _storagePath + MANIFEST_FILENAME;
    _tempManifestPath = _storagePath + TEMP_MANIFEST_FILENAME;

    initManifests(manifestUrl);
}

AssetsManagerEx::~AssetsManagerEx()
{
    _downloader->onTaskError = (nullptr);
    _downloader->onFileTaskSuccess = (nullptr);
    _downloader->onTaskProgress = (nullptr);
    CC_SAFE_RELEASE(_localManifest);
    // _tempManifest could share a ptr with _remoteManifest or _localManifest
    if (_tempManifest != _localManifest && _tempManifest != _remoteManifest)
        CC_SAFE_RELEASE(_tempManifest);
    CC_SAFE_RELEASE(_remoteManifest);
}

AssetsManagerEx* AssetsManagerEx::create(const std::string& manifestUrl, const std::string& storagePath)
{
    AssetsManagerEx* ret = new (std::nothrow) AssetsManagerEx(manifestUrl, storagePath);
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

void AssetsManagerEx::initManifests(const std::string& manifestUrl)
{
    _inited = true;
    // Init and load local manifest
    _localManifest = new (std::nothrow) Manifest();
    if (_localManifest)
    {
        loadLocalManifest(manifestUrl);
        
        // Init and load temporary manifest
        _tempManifest = new (std::nothrow) Manifest();
        if (_tempManifest)
        {
            _tempManifest->parse(_tempManifestPath);
            if (!_tempManifest->isLoaded() && _fileUtils->isFileExist(_tempManifestPath))
                _fileUtils->removeFile(_tempManifestPath);
        }
        else
        {
            _inited = false;
        }
        
        // Init remote manifest for future usage
        _remoteManifest = new (std::nothrow) Manifest();
        if (!_remoteManifest)
        {
            _inited = false;
        }
    }
    else
    {
        _inited = false;
    }
    
    if (!_inited)
    {
        CC_SAFE_DELETE(_localManifest);
        CC_SAFE_DELETE(_tempManifest);
        CC_SAFE_DELETE(_remoteManifest);
    }
}

void AssetsManagerEx::prepareLocalManifest()
{
    // An alias to assets
    _assets = &(_localManifest->getAssets());

    // Add search paths
    _localManifest->prependSearchPaths();
}

void AssetsManagerEx::loadLocalManifest(const std::string& manifestUrl)
{
    Manifest *cachedManifest = nullptr;
    // Find the cached manifest file
    if (_fileUtils->isFileExist(_cacheManifestPath))
    {
        cachedManifest = new (std::nothrow) Manifest();
        if (cachedManifest) {
            cachedManifest->parse(_cacheManifestPath);
            if (!cachedManifest->isLoaded())
            {
                _fileUtils->removeFile(_cacheManifestPath);
                CC_SAFE_RELEASE(cachedManifest);
                cachedManifest = nullptr;
            }
        }
    }
    
    // Load local manifest in app package
    _localManifest->parse(_manifestUrl);
    if (_localManifest->isLoaded())
    {
        // Compare with cached manifest to determine which one to use
        if (cachedManifest) {
            if (strcmp(_localManifest->getVersion().c_str(), cachedManifest->getVersion().c_str()) > 0)
            {
                // Recreate storage, to empty the content
                _fileUtils->removeDirectory(_storagePath);
                _fileUtils->createDirectory(_storagePath);
                CC_SAFE_RELEASE(cachedManifest);
            }
            else
            {
                CC_SAFE_RELEASE(_localManifest);
                _localManifest = cachedManifest;
            }
        }
        prepareLocalManifest();
    }

    // Fail to load local manifest
    if (!_localManifest->isLoaded())
    {
        CCLOG("AssetsManagerEx : No local manifest file found error.\n");
        dispatchUpdateEvent(EventAssetsManagerEx::EventCode::ERROR_NO_LOCAL_MANIFEST);
    }
}

std::string AssetsManagerEx::basename(const std::string& path) const
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

std::string AssetsManagerEx::get(const std::string& key) const
{
    auto it = _assets->find(key);
    if (it != _assets->cend()) {
        return _storagePath + it->second.path;
    }
    else return "";
}

const Manifest* AssetsManagerEx::getLocalManifest() const
{
    return _localManifest;
}

const Manifest* AssetsManagerEx::getRemoteManifest() const
{
    return _remoteManifest;
}

const std::string& AssetsManagerEx::getStoragePath() const
{
    return _storagePath;
}

void AssetsManagerEx::setStoragePath(const std::string& storagePath)
{
    _storagePath = storagePath;
    adjustPath(_storagePath);
    _fileUtils->createDirectory(_storagePath);
}

void AssetsManagerEx::adjustPath(std::string &path)
{
    if (path.size() > 0 && path[path.size() - 1] != '/')
    {
        path.append("/");
    }
}

bool AssetsManagerEx::decompress(const std::string &zip)
{
    // Find root path for zip file
    size_t pos = zip.find_last_of("/\\");
    if (pos == std::string::npos)
    {
        CCLOG("AssetsManagerEx : no root path specified for zip file %s\n", zip.c_str());
        return false;
    }
    const std::string rootPath = zip.substr(0, pos+1);
    
    // Open the zip file
    unzFile zipfile = unzOpen(FileUtils::getInstance()->getSuitableFOpen(zip).c_str());
    if (! zipfile)
    {
        CCLOG("AssetsManagerEx : can not open downloaded zip file %s\n", zip.c_str());
        return false;
    }
    
    // Get info about the zip file
    unz_global_info global_info;
    if (unzGetGlobalInfo(zipfile, &global_info) != UNZ_OK)
    {
        CCLOG("AssetsManagerEx : can not read file global info of %s\n", zip.c_str());
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
            CCLOG("AssetsManagerEx : can not read compressed file info\n");
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
            if ( !_fileUtils->createDirectory(basename(fullPath)) )
            {
                // Failed to create directory
                CCLOG("AssetsManagerEx : can not create directory %s\n", fullPath.c_str());
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
                CCLOG("AssetsManagerEx : can not extract file %s\n", fileName);
                unzClose(zipfile);
                return false;
            }
            
            // Create a file to store current file.
            FILE *out = fopen(FileUtils::getInstance()->getSuitableFOpen(fullPath).c_str(), "wb");
            if (!out)
            {
                CCLOG("AssetsManagerEx : can not create decompress destination file %s\n", fullPath.c_str());
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
                    CCLOG("AssetsManagerEx : can not read zip file %s, error code is %d\n", fileName, error);
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
                CCLOG("AssetsManagerEx : can not read next file for decompressing\n");
                unzClose(zipfile);
                return false;
            }
        }
    }
    
    unzClose(zipfile);
    return true;
}

void AssetsManagerEx::decompressDownloadedZip()
{
    // Decompress all compressed files
    for (auto it = _compressedFiles.begin(); it != _compressedFiles.end(); ++it) {
        std::string zipfile = *it;
        if (!decompress(zipfile))
        {
            dispatchUpdateEvent(EventAssetsManagerEx::EventCode::ERROR_DECOMPRESS, "", "Unable to decompress file " + zipfile);
        }
        _fileUtils->removeFile(zipfile);
    }
    _compressedFiles.clear();
}

void AssetsManagerEx::dispatchUpdateEvent(EventAssetsManagerEx::EventCode code, const std::string &assetId/* = ""*/, const std::string &message/* = ""*/, int curle_code/* = CURLE_OK*/, int curlm_code/* = CURLM_OK*/)
{
    EventAssetsManagerEx event(_eventName, this, code, _percent, _percentByFile, assetId, message, curle_code, curlm_code);
    _eventDispatcher->dispatchEvent(&event);
}

AssetsManagerEx::State AssetsManagerEx::getState() const
{
    return _updateState;
}

void AssetsManagerEx::downloadVersion()
{
    if (_updateState > State::PREDOWNLOAD_VERSION)
        return;

    std::string versionUrl = _localManifest->getVersionFileUrl();

    if (versionUrl.size() > 0)
    {
        _updateState = State::DOWNLOADING_VERSION;
        // Download version file asynchronously
        _downloader->createDownloadFileTask(versionUrl, _cacheVersionPath, VERSION_ID);
    }
    // No version file found
    else
    {
        CCLOG("AssetsManagerEx : No version file found, step skipped\n");
        _updateState = State::PREDOWNLOAD_MANIFEST;
        downloadManifest();
    }
}

void AssetsManagerEx::parseVersion()
{
    if (_updateState != State::VERSION_LOADED)
        return;

    _remoteManifest->parseVersion(_cacheVersionPath);

    if (!_remoteManifest->isVersionLoaded())
    {
        CCLOG("AssetsManagerEx : Fail to parse version file, step skipped\n");
        _updateState = State::PREDOWNLOAD_MANIFEST;
        downloadManifest();
    }
    else
    {
        if (_localManifest->versionEquals(_remoteManifest))
        {
            _updateState = State::UP_TO_DATE;
            dispatchUpdateEvent(EventAssetsManagerEx::EventCode::ALREADY_UP_TO_DATE);
        }
        else
        {
            _updateState = State::NEED_UPDATE;
            dispatchUpdateEvent(EventAssetsManagerEx::EventCode::NEW_VERSION_FOUND);

            // Wait to update so continue the process
            if (_waitToUpdate)
            {
                _updateState = State::PREDOWNLOAD_MANIFEST;
                downloadManifest();
            }
        }
    }
}

void AssetsManagerEx::downloadManifest()
{
    if (_updateState != State::PREDOWNLOAD_MANIFEST)
        return;

    std::string manifestUrl = _localManifest->getManifestFileUrl();
    if (manifestUrl.size() > 0)
    {
        _updateState = State::DOWNLOADING_MANIFEST;
        // Download version file asynchronously
        _downloader->createDownloadFileTask(manifestUrl, _tempManifestPath, MANIFEST_ID);
    }
    // No manifest file found
    else
    {
        CCLOG("AssetsManagerEx : No manifest file found, check update failed\n");
        dispatchUpdateEvent(EventAssetsManagerEx::EventCode::ERROR_DOWNLOAD_MANIFEST);
        _updateState = State::UNCHECKED;
    }
}

void AssetsManagerEx::parseManifest()
{
    if (_updateState != State::MANIFEST_LOADED)
        return;

    _remoteManifest->parse(_tempManifestPath);

    if (!_remoteManifest->isLoaded())
    {
        CCLOG("AssetsManagerEx : Error parsing manifest file\n");
        dispatchUpdateEvent(EventAssetsManagerEx::EventCode::ERROR_PARSE_MANIFEST);
        _updateState = State::UNCHECKED;
    }
    else
    {
        if (_localManifest->versionEquals(_remoteManifest))
        {
            _updateState = State::UP_TO_DATE;
            dispatchUpdateEvent(EventAssetsManagerEx::EventCode::ALREADY_UP_TO_DATE);
        }
        else
        {
            _updateState = State::NEED_UPDATE;
            dispatchUpdateEvent(EventAssetsManagerEx::EventCode::NEW_VERSION_FOUND);

            if (_waitToUpdate)
            {
                startUpdate();
            }
        }
    }
}

void AssetsManagerEx::startUpdate()
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
        this->batchDownload();
        
        std::string msg = StringUtils::format("Resuming from previous unfinished update, %d files remains to be finished.", _totalToDownload);
        dispatchUpdateEvent(EventAssetsManagerEx::EventCode::UPDATE_PROGRESSION, "", msg);
    }
    // Check difference
    else
    {
        // Temporary manifest not exists or out of date,
        // it will be used to register the download states of each asset,
        // in this case, it equals remote manifest.
        _tempManifest->release();
        _tempManifest = _remoteManifest;
        
        std::unordered_map<std::string, Manifest::AssetDiff> diff_map = _localManifest->genDiff(_remoteManifest);
        if (diff_map.size() == 0)
        {
            updateSucceed();
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
                    _fileUtils->createDirectory(basename(_storagePath + path));

                    DownloadUnit unit;
                    unit.customId = it->first;
                    unit.srcUrl = packageUrl + path;
                    unit.storagePath = _storagePath + path;
                    _downloadUnits.emplace(unit.customId, unit);
                }
            }
            // Set other assets' downloadState to SUCCESSED
            auto &assets = _remoteManifest->getAssets();
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
            this->batchDownload();
            
            std::string msg = StringUtils::format("Start to update %d files from remote package.", _totalToDownload);
            dispatchUpdateEvent(EventAssetsManagerEx::EventCode::UPDATE_PROGRESSION, "", msg);
        }
    }

    _waitToUpdate = false;
}

void AssetsManagerEx::updateSucceed()
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


    _updateState = State::UNZIPPING;
    // 4. decompress all compressed files
    //decompressDownloadedZip();

    struct AsyncData
    {
        std::vector<std::string> compressedFiles;
        std::string errorCompressedFile;
    };

    AsyncData* asyncData = new AsyncData;
    asyncData->compressedFiles = _compressedFiles;
    _compressedFiles.clear();

    std::function<void(void*)> mainThread = [this](void* param) {
        AsyncData* asyncData = (AsyncData*)param;
        if (asyncData->errorCompressedFile.empty())
        {
            // 5. Set update state
            _updateState = State::UP_TO_DATE;
            // 6. Notify finished event
            dispatchUpdateEvent(EventAssetsManagerEx::EventCode::UPDATE_FINISHED);
        }
        else
        {
            _updateState = State::FAIL_TO_UPDATE;
            dispatchUpdateEvent(EventAssetsManagerEx::EventCode::ERROR_DECOMPRESS, "", "Unable to decompress file " + asyncData->errorCompressedFile);
        }

        delete asyncData;
    };
    AsyncTaskPool::getInstance()->enqueue(AsyncTaskPool::TaskType::TASK_OTHER, mainThread, (void*)asyncData, [this, asyncData]() {
        // Decompress all compressed files
        for (auto& zipFile : asyncData->compressedFiles) {
            if (!decompress(zipFile))
            {
                asyncData->errorCompressedFile = zipFile;
                break;
            }
            _fileUtils->removeFile(zipFile);
        }
    });
}

void AssetsManagerEx::checkUpdate()
{
    if (!_inited){
        CCLOG("AssetsManagerEx : Manifests uninited.\n");
        dispatchUpdateEvent(EventAssetsManagerEx::EventCode::ERROR_NO_LOCAL_MANIFEST);
        return;
    }
    if (!_localManifest->isLoaded())
    {
        CCLOG("AssetsManagerEx : No local manifest file found error.\n");
        dispatchUpdateEvent(EventAssetsManagerEx::EventCode::ERROR_NO_LOCAL_MANIFEST);
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
            dispatchUpdateEvent(EventAssetsManagerEx::EventCode::ALREADY_UP_TO_DATE);
        }
            break;
        case State::FAIL_TO_UPDATE:
        case State::NEED_UPDATE:
        {
            dispatchUpdateEvent(EventAssetsManagerEx::EventCode::NEW_VERSION_FOUND);
        }
            break;
        default:
            break;
    }
}

void AssetsManagerEx::update()
{
    if (!_inited){
        CCLOG("AssetsManagerEx : Manifests uninited.\n");
        dispatchUpdateEvent(EventAssetsManagerEx::EventCode::ERROR_NO_LOCAL_MANIFEST);
        return;
    }
    if (!_localManifest->isLoaded())
    {
        CCLOG("AssetsManagerEx : No local manifest file found error.\n");
        dispatchUpdateEvent(EventAssetsManagerEx::EventCode::ERROR_NO_LOCAL_MANIFEST);
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
        case State::UNZIPPING:
            _waitToUpdate = false;
            break;
        default:
            break;
    }
}

void AssetsManagerEx::updateAssets(const DownloadUnits& assets)
{
    if (!_inited){
        CCLOG("AssetsManagerEx : Manifests uninited.\n");
        dispatchUpdateEvent(EventAssetsManagerEx::EventCode::ERROR_NO_LOCAL_MANIFEST);
        return;
    }
    
    if (_updateState != State::UPDATING && _localManifest->isLoaded() && _remoteManifest->isLoaded())
    {
        int size = (int)(assets.size());
        if (size > 0)
        {
            _updateState = State::UPDATING;
            _downloadUnits.clear();
            _downloadUnits = assets;
            this->batchDownload();
        }
        else if (size == 0 && _totalWaitToDownload == 0)
        {
            updateSucceed();
        }
    }
}

const DownloadUnits& AssetsManagerEx::getFailedAssets() const
{
    return _failedUnits;
}

void AssetsManagerEx::downloadFailedAssets()
{
    CCLOG("AssetsManagerEx : Start update %lu failed assets.\n", _failedUnits.size());
    updateAssets(_failedUnits);
}


void AssetsManagerEx::onError(const network::DownloadTask& task,
                              int errorCode,
                              int errorCodeInternal,
                              const std::string& errorStr)
{
    // Skip version error occurred
    if (task.identifier == VERSION_ID)
    {
        CCLOG("AssetsManagerEx : Fail to download version file, step skipped\n");
        _updateState = State::PREDOWNLOAD_MANIFEST;
        downloadManifest();
    }
    else if (task.identifier == MANIFEST_ID)
    {
        dispatchUpdateEvent(EventAssetsManagerEx::EventCode::ERROR_DOWNLOAD_MANIFEST, task.identifier, errorStr, errorCode, errorCodeInternal);
    }
    else
    {
        auto unitIt = _downloadUnits.find(task.identifier);
        // Found unit and add it to failed units
        if (unitIt != _downloadUnits.end())
        {
            DownloadUnit unit = unitIt->second;
            _failedUnits.emplace(unit.customId, unit);
        }
        dispatchUpdateEvent(EventAssetsManagerEx::EventCode::ERROR_UPDATING, task.identifier, errorStr, errorCode, errorCodeInternal);
    }
}

void AssetsManagerEx::onProgress(double total, double downloaded, const std::string &url, const std::string &customId)
{
    if (customId == VERSION_ID || customId == MANIFEST_ID)
    {
        _percent = 100 * downloaded / total;
        // Notify progression event
        dispatchUpdateEvent(EventAssetsManagerEx::EventCode::UPDATE_PROGRESSION, customId);
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
                dispatchUpdateEvent(EventAssetsManagerEx::EventCode::UPDATE_PROGRESSION, customId);
            }
        }
    }
}

void AssetsManagerEx::onSuccess(const std::string &srcUrl, const std::string &storagePath, const std::string &customId)
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
        auto &assets = _remoteManifest->getAssets();
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
            dispatchUpdateEvent(EventAssetsManagerEx::EventCode::UPDATE_PROGRESSION, "");
        }
        // Notify asset updated event
        dispatchUpdateEvent(EventAssetsManagerEx::EventCode::ASSET_UPDATED, customId);
        
        unitIt = _failedUnits.find(customId);
        // Found unit and delete it
        if (unitIt != _failedUnits.end())
        {
            // Remove from failed units list
            _failedUnits.erase(unitIt);
        }
        
        if (_totalWaitToDownload <= 0)
        {
            // Finished with error check
            if (_failedUnits.size() > 0)
            {
                // Save current download manifest information for resuming
                _tempManifest->saveToFile(_tempManifestPath);
                
                decompressDownloadedZip();
                
                _updateState = State::FAIL_TO_UPDATE;
                dispatchUpdateEvent(EventAssetsManagerEx::EventCode::UPDATE_FAILED);
            }
            else
            {
                updateSucceed();
            }
        }
    }
}

void AssetsManagerEx::destroyDownloadedVersion()
{
    _fileUtils->removeFile(_cacheVersionPath);
    _fileUtils->removeFile(_cacheManifestPath);
}

void AssetsManagerEx::batchDownload()
{
    for(auto iter : _downloadUnits)
    {
        DownloadUnit& unit = iter.second;
        _downloader->createDownloadFileTask(unit.srcUrl, unit.storagePath, unit.customId);
    }
}

NS_CC_EXT_END
