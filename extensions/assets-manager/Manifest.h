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

#include "extensions/ExtensionMacros.h"
#include "extensions/ExtensionExport.h"
#include "Downloader.h"

#include <string>
#include <unordered_map>
#include <vector>

#include "json/document.h"

NS_CC_EXT_BEGIN


class CC_EX_DLL Manifest : public Ref
{
public:
    
    friend class AssetsManagerEx;
    
    /** @~english Type of difference between local and remote asset
     * @~chinese 本地和远程资源的差异类型
     */
    enum class DiffType {
        /** @~english Added in remote, absent in local
         * @~chinese 在远程资源列表中存在，在本地不存在
         */
        ADDED,
        /** @~english Deleted in remote, present in local
         * @~chinese 在远程资源列表中已删除，在当地仍然存在
         */
        DELETED,
        /** @~english Updated in remote, local version is old
         * @~chinese 在远程资源列表中已更新，本地的版本是旧的
         */
        MODIFIED
    };

    /** @~english Download state of a updating asset
     * @~chinese 下载更新资源的状态
     */
    enum class DownloadState {
        /** @~english Wait to be updated
         * @~chinese 等待更新
         */
        UNSTARTED,
        /** @~english Downloading
         * @~chinese 下载中
         */
        DOWNLOADING,
        /** @~english Updated
         * @~chinese 已更新
         */
        SUCCESSED
    };
    
    /** @~english The asset object
     * @~chinese 资源对象
     */
    struct Asset {
        /** @~english The version number string, suggested to use md5.
         * @~chinese 版本号的字符串，建议使用md5。
         */
        std::string md5;
        /** @~english The url address of the remote asset
         * @~chinese 远程资源的url地址
         */
        std::string path;
        /** @~english Indicate whether the asset is compressed or not
         * @~chinese 指示资源是否被压缩
         */
        bool compressed;
        /** @~english The download state
         * @~chinese 下载的状态
         */
        DownloadState downloadState;
    };

    /** @~english Object indicate the difference between two Assets
     * @~chinese 显示两种资源之间区别的对象
     */
    struct AssetDiff {
        /** @~english The asset object
         * @~chinese 资源对象
         */
        Asset asset;
        /** @~english Type of difference between local and remote asset
         * @~chinese 本地和远程资源的区别类型
         */
        DiffType type;
    };
    
    /** @brief @~english Check whether the version informations have been fully loaded
     * @~chinese 检查版本信息是否已加载
     * @return @~english The version informations have been loaded or not
     * @~chinese 返回版本信息是否已加载
     */
    bool isVersionLoaded() const;
    
    /** @brief @~english Check whether the manifest have been fully loaded
     * @~chinese 检查资源清单是否已满载
     * @return @~english The manifest have been loaded or not
     * @~chinese 返回清单是否已经被加载
     */
    bool isLoaded() const;
    
    /** @brief @~english Gets remote package url.
     * @~chinese 获取远程资源包url。
     * @return @~english The remote package url
     * @~chinese 远程资源包url
     */
    const std::string& getPackageUrl() const;
    
    /** @brief @~english Gets remote manifest file url.
     * @~chinese 获取远程资源清单文件的url。
     * @return @~english The remote manifest file url
     * @~chinese 远程资源清单文件的url
     */
    const std::string& getManifestFileUrl() const;
    
    /** @brief @~english Gets remote version file url.
     * @~chinese 获取远程版本文件的url。
     * @return @~english The remote version file url
     * @~chinese 远程版本文件的url
     */
    const std::string& getVersionFileUrl() const;
    
    /** @brief @~english Gets manifest version.
     * @~chinese 获取资源清单的版本。
     * @return @~english The manifest version
     * @~chinese 资源清单的版本
     */
    const std::string& getVersion() const;
    
    /** @brief @~english Get the search paths list related to the Manifest.
     * @~chinese Manifest相关搜索路径列表。
     * @return @~english The search paths
     * @~chinese 搜索路径列表
     */
    std::vector<std::string> getSearchPaths() const;
    
protected:
    
    /** @brief @~english Constructor for Manifest class
     * @~chinese Manifest资源清单类的构造函数
     * @param manifestUrl @~english Url of the local manifest
     * @~chinese 本地资源清单地址
     */
    Manifest(const std::string& manifestUrl = "");
    
    /** @brief @~english Load the json file into local json object
     * @~chinese 加载json文件到json对象
     * @param url @~english Url of the json file
     * @~chinese json文件的Url
     */
    void loadJson(const std::string& url);
    
    /** @brief @~english Parse the version file information into this manifest
     * @~chinese 解析版本文件的版本信息到这个Manifest
     * @param versionUrl @~english Url of the local version file
     * @~chinese 版本文件的Url
     */
    void parseVersion(const std::string& versionUrl);
    
    /** @brief @~english Parse the manifest file information into this manifest
     * @~chinese 解析Manifest文件信息
     * @param manifestUrl @~english Url of the local manifest
     * @~chinese Manifest的本地url地址
     */
    void parse(const std::string& manifestUrl);
    
    /** @brief @~english Check whether the version of this manifest equals to another.
     * @~chinese 检查这个Manifest的版本是否等于另一个Manifest对象
     * @param b   @~english The other manifest
     * @~chinese 另一个Manifest对象
     * @return @~english Return true if the version of this manifest equals to b, otherwise return false.
     * @~chinese 如果想等则返回true，否则返回false。
     */
    bool versionEquals(const Manifest *b) const;
    
    /** @brief @~english Generate difference between this Manifest and another.
     * @~chinese 生成这个Manifest对象和另一个之间的区别。
     * @param b   @~english The other manifest
     * @~chinese 另一个Manifest对象
     * @return @~english Return the different assets between this manifest and b.
     * @~chinese 这个Manifest对象和另一个之间的差异资源列表。
     */
    std::unordered_map<std::string, AssetDiff> genDiff(const Manifest *b) const;
    
    /** @brief @~english Generate assets list for resuming previous download.
     * @~chinese 生成可以用于恢复之前一次下载的资源列表。
     * @param units   @~english The download units reference to be modified by the generation result
     * @~chinese 下载资源列表，结果会被保存在这个参数中
     */
    void genResumeAssetsList(Downloader::DownloadUnits *units) const;
    
    /** @brief @~english Prepend all search paths to the FileUtils.
     * @~chinese 向FileUtils中优先插入这个Manifest对象相关的搜索路径。
     */
    void prependSearchPaths();
    
    void loadVersion(const rapidjson::Document &json);
    
    void loadManifest(const rapidjson::Document &json);
    
    void saveToFile(const std::string &filepath);
    
    Asset parseAsset(const std::string &path, const rapidjson::Value &json);
    
    void clear();
    
    /** @brief @~english Gets all groups.
     * @~chinese 获取所有组。
     */
    const std::vector<std::string>& getGroups() const;
    
    /** @brief @~english Gets all groups version.
     * @~chinese 得到所有组的版本。
     */
    const std::unordered_map<std::string, std::string>& getGroupVerions() const;
    
    /** @brief @~english Gets version for the given group.
     * @~chinese 给定组的版本。
     * @param group   @~english Key of the requested group
     * @~chinese 组的键值
     */
    const std::string& getGroupVersion(const std::string &group) const;
    
    /** 
     * @brief @~english Gets assets.
     * @~chinese 获得所有资源。
     */
    const std::unordered_map<std::string, Asset>& getAssets() const;
    
    /** @brief @~english Set the download state for an asset
     * @~chinese 为一个资源设置下载状态
     * @param key   @~english Key of the asset to set
     * @~chinese 要修改的资源键值
     * @param state @~english The current download state of the asset
     * @~chinese 资源的当前下载状态
     */
    void setAssetDownloadState(const std::string &key, const DownloadState &state);
    
private:
    
    //! Indicate whether the version informations have been fully loaded
    bool _versionLoaded;
    
    //! Indicate whether the manifest have been fully loaded
    bool _loaded;
    
    //! Reference to the global file utils
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
    std::unordered_map<std::string, std::string> _groupVer;
    
    //! The version of local engine
    std::string _engineVer;
    
    //! Full assets list
    std::unordered_map<std::string, Asset> _assets;
    
    //! All search paths
    std::vector<std::string> _searchPaths;
    
    rapidjson::Document _json;
};

NS_CC_EXT_END
#endif /* defined(__Manifest__) */
