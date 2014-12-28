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

#include "Manifest.h"
#include "json/filestream.h"
#include "json/prettywriter.h"
#include "json/stringbuffer.h"

#include <fstream>

#define KEY_VERSION             "version"
#define KEY_PACKAGE_URL         "packageUrl"
#define KEY_MANIFEST_URL        "remoteManifestUrl"
#define KEY_VERSION_URL         "remoteVersionUrl"
#define KEY_GROUP_VERSIONS      "groupVersions"
#define KEY_ENGINE_VERSION      "engineVersion"
#define KEY_ASSETS              "assets"
#define KEY_COMPRESSED_FILES    "compressedFiles"
#define KEY_SEARCH_PATHS        "searchPaths"

#define KEY_PATH                "path"
#define KEY_MD5                 "md5"
#define KEY_GROUP               "group"
#define KEY_COMPRESSED          "compressed"
#define KEY_COMPRESSED_FILE     "compressedFile"
#define KEY_DOWNLOAD_STATE      "downloadState"

NS_CC_EXT_BEGIN

Manifest::Manifest(const std::string& manifestUrl/* = ""*/)
: _versionLoaded(false)
, _loaded(false)
, _manifestRoot("")
, _remoteManifestUrl("")
, _remoteVersionUrl("")
, _version("")
, _engineVer("")
{
    // Init variables
    _fileUtils = FileUtils::getInstance();
    if (manifestUrl.size() > 0)
        parse(manifestUrl);
}

void Manifest::loadJson(const std::string& url)
{
    clear();
    std::string content;
    if (_fileUtils->isFileExist(url))
    {
        // Load file content
        content = _fileUtils->getStringFromFile(url);
        
        if (content.size() == 0)
        {
            CCLOG("Fail to retrieve local file content: %s\n", url.c_str());
        }
        else
        {
            // Parse file with rapid json
            _json.Parse<0>(content.c_str());
            // Print error
            if (_json.HasParseError()) {
                size_t offset = _json.GetErrorOffset();
                if (offset > 0)
                    offset--;
                std::string errorSnippet = content.substr(offset, 10);
                CCLOG("File parse error %s at <%s>\n", _json.GetParseError(), errorSnippet.c_str());
            }
        }
    }
}

void Manifest::parseVersion(const std::string& versionUrl)
{
    loadJson(versionUrl);
    
    if (_json.IsObject())
    {
        loadVersion(_json);
    }
}

void Manifest::parse(const std::string& manifestUrl)
{
    loadJson(manifestUrl);
	
    if (_json.IsObject())
    {
        // Register the local manifest root
        size_t found = manifestUrl.find_last_of("/\\");
        if (found != std::string::npos)
        {
            _manifestRoot = manifestUrl.substr(0, found+1);
        }
        loadManifest(_json);
    }
}

bool Manifest::isVersionLoaded() const
{
    return _versionLoaded;
}
bool Manifest::isLoaded() const
{
    return _loaded;
}

bool Manifest::versionEquals(const Manifest *b) const
{
    // Check manifest version
    if (_version != b->getVersion())
    {
        return false;
    }
    // Check group versions
    else
    {
        std::vector<std::string> bGroups = b->getGroups();
        std::unordered_map<std::string, std::string> bGroupVer = b->getGroupVerions();
        // Check group size
        if (bGroups.size() != _groups.size())
            return false;
        
        // Check groups version
        for (int i = 0; i < _groups.size(); ++i) {
            std::string gid =_groups[i];
            // Check group name
            if (gid != bGroups[i])
                return false;
            // Check group version
            if (_groupVer.at(gid) != bGroupVer.at(gid))
                return false;
        }
    }
    return true;
}

std::unordered_map<std::string, Manifest::AssetDiff> Manifest::genDiff(const Manifest *b) const
{
    std::unordered_map<std::string, AssetDiff> diff_map;
    std::unordered_map<std::string, Asset> bAssets = b->getAssets();
    
    std::string key;
    Asset valueA;
    Asset valueB;
    std::unordered_map<std::string, Asset>::const_iterator valueIt, it;
    for (it = _assets.begin(); it != _assets.end(); ++it)
    {
        key = it->first;
        valueA = it->second;
        
        // Deleted
        valueIt = bAssets.find(key);
        if (valueIt == bAssets.cend()) {
            AssetDiff diff;
            diff.asset = valueA;
            diff.type = DiffType::DELETED;
            diff_map.emplace(key, diff);
            continue;
        }
        
        // Modified
        valueB = valueIt->second;
        if (valueA.md5 != valueB.md5) {
            AssetDiff diff;
            diff.asset = valueB;
            diff.type = DiffType::MODIFIED;
            diff_map.emplace(key, diff);
        }
    }
    
    for (it = bAssets.begin(); it != bAssets.end(); ++it)
    {
        key = it->first;
        valueB = it->second;
        
        // Added
        valueIt = _assets.find(key);
        if (valueIt == _assets.cend()) {
            AssetDiff diff;
            diff.asset = valueB;
            diff.type = DiffType::ADDED;
            diff_map.emplace(key, diff);
        }
    }
    
    return diff_map;
}

void Manifest::genResumeAssetsList(Downloader::DownloadUnits *units) const
{
    for (auto it = _assets.begin(); it != _assets.end(); ++it)
    {
        Asset asset = it->second;
        
        if (asset.downloadState != DownloadState::SUCCESSED)
        {
            Downloader::DownloadUnit unit;
            unit.customId = it->first;
            unit.srcUrl = _packageUrl + asset.path;
            unit.storagePath = _manifestRoot + asset.path;
            if (asset.downloadState == DownloadState::DOWNLOADING)
            {
                unit.resumeDownload = true;
            }
            else
            {
                unit.resumeDownload = false;
            }
            units->emplace(unit.customId, unit);
        }
    }
}

std::vector<std::string> Manifest::getSearchPaths()
{
    std::vector<std::string> searchPaths;
    searchPaths.push_back(_manifestRoot);
    
    for (int i = (int)_searchPaths.size()-1; i >= 0; i--)
    {
        std::string path = _searchPaths[i];
        if (path.size() > 0 && path[path.size() - 1] != '/')
            path.append("/");
        path = _manifestRoot + path;
        searchPaths.push_back(path);
    }
    return searchPaths;
}

void Manifest::prependSearchPaths()
{
    std::vector<std::string> searchPaths = FileUtils::getInstance()->getSearchPaths();
    std::vector<std::string>::iterator iter = searchPaths.begin();
    searchPaths.insert(iter, _manifestRoot);
    
    for (int i = (int)_searchPaths.size()-1; i >= 0; i--)
    {
        std::string path = _searchPaths[i];
        if (path.size() > 0 && path[path.size() - 1] != '/')
            path.append("/");
        path = _manifestRoot + path;
        iter = searchPaths.begin();
        searchPaths.insert(iter, path);
    }
    FileUtils::getInstance()->setSearchPaths(searchPaths);
}


const std::string& Manifest::getPackageUrl() const
{
    return _packageUrl;
}

const std::string& Manifest::getManifestFileUrl() const
{
    return _remoteManifestUrl;
}

const std::string& Manifest::getVersionFileUrl() const
{
    return _remoteVersionUrl;
}

const std::string& Manifest::getVersion() const
{
    return _version;
}

const std::vector<std::string>& Manifest::getGroups() const
{
    return _groups;
}

const std::unordered_map<std::string, std::string>& Manifest::getGroupVerions() const
{
    return _groupVer;
}

const std::string& Manifest::getGroupVersion(const std::string &group) const
{
    return _groupVer.at(group);
}

const std::unordered_map<std::string, Manifest::Asset>& Manifest::getAssets() const
{
    return _assets;
}

void Manifest::setAssetDownloadState(const std::string &key, const Manifest::DownloadState &state)
{
    auto valueIt = _assets.find(key);
    if (valueIt != _assets.end())
    {
        valueIt->second.downloadState = state;
        
        // Update json object
        if(_json.IsObject())
        {
            if ( _json.HasMember(KEY_ASSETS) )
            {
                rapidjson::Value &assets = _json[KEY_ASSETS];
                if (assets.IsObject())
                {
                    for (rapidjson::Value::MemberIterator itr = assets.MemberonBegin(); itr != assets.MemberonEnd(); ++itr)
                    {
                        std::string jkey = itr->name.GetString();
                        if (jkey == key) {
                            rapidjson::Value &entry = itr->value;
                            rapidjson::Value &value = entry[KEY_DOWNLOAD_STATE];
                            if (value.IsInt())
                            {
                                value.SetInt((int)state);
                            }
                            else
                            {
                                entry.AddMember<int>(KEY_DOWNLOAD_STATE, (int)state, _json.GetAllocator());
                            }
                        }
                    }
                }
            }
        }
    }
}

void Manifest::clear()
{
    if (_versionLoaded || _loaded)
    {
        _groups.clear();
        _groupVer.clear();
        
        _remoteManifestUrl = "";
        _remoteVersionUrl = "";
        _version = "";
        _engineVer = "";
        
        _versionLoaded = false;
    }
    
    if (_loaded)
    {
        _assets.clear();
        _searchPaths.clear();
        _loaded = false;
    }
}

Manifest::Asset Manifest::parseAsset(const std::string &path, const rapidjson::Value &json)
{
    Asset asset;
    asset.path = path;
	
    if ( json.HasMember(KEY_MD5) && json[KEY_MD5].IsString() )
    {
        asset.md5 = json[KEY_MD5].GetString();
    }
    else asset.md5 = "";
    
    if ( json.HasMember(KEY_PATH) && json[KEY_PATH].IsString() )
    {
        asset.path = json[KEY_PATH].GetString();
    }
    
    if ( json.HasMember(KEY_COMPRESSED) && json[KEY_COMPRESSED].IsBool() )
    {
        asset.compressed = json[KEY_COMPRESSED].GetBool();
    }
    else asset.compressed = false;
    
    if ( json.HasMember(KEY_DOWNLOAD_STATE) && json[KEY_DOWNLOAD_STATE].IsInt() )
    {
        asset.downloadState = (DownloadState)(json[KEY_DOWNLOAD_STATE].GetInt());
    }
    else asset.downloadState = DownloadState::UNSTARTED;
    
    return asset;
}

void Manifest::loadVersion(const rapidjson::Document &json)
{
    // Retrieve remote manifest url
    if ( json.HasMember(KEY_MANIFEST_URL) && json[KEY_MANIFEST_URL].IsString() )
    {
        _remoteManifestUrl = json[KEY_MANIFEST_URL].GetString();
    }
    
    // Retrieve remote version url
    if ( json.HasMember(KEY_VERSION_URL) && json[KEY_VERSION_URL].IsString() )
    {
        _remoteVersionUrl = json[KEY_VERSION_URL].GetString();
    }
    
    // Retrieve local version
    if ( json.HasMember(KEY_VERSION) && json[KEY_VERSION].IsString() )
    {
        _version = json[KEY_VERSION].GetString();
    }
    
    // Retrieve local group version
    if ( json.HasMember(KEY_GROUP_VERSIONS) )
    {
        const rapidjson::Value& groupVers = json[KEY_GROUP_VERSIONS];
        if (groupVers.IsObject())
        {
            for (rapidjson::Value::ConstMemberIterator itr = groupVers.MemberonBegin(); itr != groupVers.MemberonEnd(); ++itr)
            {
                std::string group = itr->name.GetString();
                std::string version = "0";
                if (itr->value.IsString())
                {
                    version = itr->value.GetString();
                }
                _groups.push_back(group);
                _groupVer.emplace(group, version);
            }
        }
    }
    
    // Retrieve local engine version
    if ( json.HasMember(KEY_ENGINE_VERSION) && json[KEY_ENGINE_VERSION].IsString() )
    {
        _engineVer = json[KEY_ENGINE_VERSION].GetString();
    }
    
    _versionLoaded = true;
}

void Manifest::loadManifest(const rapidjson::Document &json)
{
    loadVersion(json);
    
    // Retrieve package url
    if ( json.HasMember(KEY_PACKAGE_URL) && json[KEY_PACKAGE_URL].IsString() )
    {
        _packageUrl = json[KEY_PACKAGE_URL].GetString();
        // Append automatically "/"
        if (_packageUrl.size() > 0 && _packageUrl[_packageUrl.size() - 1] != '/')
        {
            _packageUrl.append("/");
        }
    }
    
    // Retrieve all assets
    if ( json.HasMember(KEY_ASSETS) )
    {
        const rapidjson::Value& assets = json[KEY_ASSETS];
        if (assets.IsObject())
        {
            for (rapidjson::Value::ConstMemberIterator itr = assets.MemberonBegin(); itr != assets.MemberonEnd(); ++itr)
            {
                std::string key = itr->name.GetString();
                Asset asset = parseAsset(key, itr->value);
                _assets.emplace(key, asset);
            }
        }
    }
    
    // Retrieve all search paths
    if ( json.HasMember(KEY_SEARCH_PATHS) )
    {
        const rapidjson::Value& paths = json[KEY_SEARCH_PATHS];
        if (paths.IsArray())
        {
            for (rapidjson::SizeType i = 0; i < paths.Size(); ++i)
            {
                if (paths[i].IsString()) {
                    _searchPaths.push_back(paths[i].GetString());
                }
            }
        }
    }
    
    _loaded = true;
}

void Manifest::saveToFile(const std::string &filepath)
{
    rapidjson::StringBuffer buffer;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
    _json.Accept(writer);
    
    std::ofstream output(filepath, std::ofstream::out);
    if(!output.bad())
        output << buffer.GetString() << std::endl;
}

NS_CC_EXT_END