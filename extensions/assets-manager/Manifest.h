/****************************************************************************
 Copyright (c) 2013 cocos2d-x.org
 
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

#ifndef __Manifest__
#define __Manifest__

#include "cocos2d.h"
#include "extensions/ExtensionMacros.h"

#include <string>
#include <map>
#include <vector>

#include "json/document.h"

NS_CC_EXT_BEGIN

class CC_DLL Manifest
{
public:
    
    enum DiffType {
        ADDED,
        DELETED,
        MODIFIED
    };
    
    struct Asset {
        std::string md5;
        std::string path;
        std::string group;
        bool updating;
    };
    
    struct AssetDiff {
        Asset asset;
        DiffType type;
    };
    
    Manifest(const std::string& manifestUrl);
    
    void parse(const std::string& manifestUrl);
    
    bool isVersionLoaded() const;
    bool isLoaded() const;
    
    bool versionEquals(const Manifest *b) const;
    
    std::map<std::string, AssetDiff> genDiff(const Manifest *b) const;
    
    void prependSearchPaths();
    
    /* @brief Gets remote package url.
     */
    const std::string& getPackageUrl() const;
    
    /* @brief Sets remote package url.
     */
    void setPackageUrl(const std::string& packageUrl);
    
    /* @brief Gets remote manifest file url.
     */
    const std::string& getManifestFileUrl() const;
    
    /* @brief Sets remote manifest file url.
     */
    void setManifestFileUrl(const std::string& manifestFileUrl);
    
    /* @brief Gets remote version file url.
     */
    const std::string& getVersionFileUrl() const;
    
    /* @brief Sets remote version file url.
     */
    void setVersionFileUrl(const std::string& versionFileUrl);
    
    /* @brief Gets manifest version.
     */
    const std::string& getManifestVersion() const;
    
    /* @brief Gets all groups.
     */
    const std::vector<std::string>& getGroups() const;
    
    /* @brief Gets all groups version.
     */
    const std::map<std::string, std::string>& getGroupVerions() const;
    
    /* @brief Gets version for the given group.
     */
    const std::string& getGroupVersion(const std::string &group) const;
    
    /* @brief Gets engine version.
     */
    const std::string& getEngineVersion() const;
    
    /* @brief Gets assets.
     */
    const std::map<std::string, Asset>& getAssets() const;
    
    /* @brief Gets asset by key.
     */
    const Asset& getAsset(const std::string &key) const;
    
protected:
    void loadVersion(const rapidjson::Document &json);
    void loadManifest(const rapidjson::Document &json);
    Asset parseAsset(const rapidjson::Value &json);
    
private:
    
    bool _versionLoaded;
    
    bool _loaded;
    
    FileUtils *_fileUtils;
    
    //! The local manifest root
    std::string _manifestRoot;
    
    //! The remote package url
    std::string _packageUrl;
    
    //! The remote path of manifest file
    std::string _remoteManifestUrl;
    
    //! The remote path of version file [Optional]
    std::string _remoteVersionUrl;
    
    //! The version of local manifest
    std::string _version;
    
    //! All groups exist in manifest [Optional]
    std::vector<std::string> _groups;
    
    //! The versions of all local group [Optional]
    std::map<std::string, std::string> _groupVer;
    
    //! The version of local engine
    std::string _engineVer;
    
    //! Full assets list
    std::map<std::string, Asset> _assets;
    
    //! All search paths
    std::vector<std::string> _searchPaths;
    
    rapidjson::Document parseJSON(const std::string &url);
    
    void clear();
};

NS_CC_EXT_END;

#endif /* defined(__Manifest__) */
