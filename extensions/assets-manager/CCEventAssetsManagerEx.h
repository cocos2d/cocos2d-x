/****************************************************************************
 Copyright (c) 2014 Chukong Technologies Inc.
 
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

#ifndef __cocos2d_libs__CCEventAssetsManagerEx__
#define __cocos2d_libs__CCEventAssetsManagerEx__

#include "base/CCEvent.h"
#include "base/CCEventCustom.h"
#include "extensions/ExtensionMacros.h" 
#include "extensions/ExtensionExport.h"

NS_CC_EXT_BEGIN

/**
 * @addtogroup AssetsManager
 * @{
 */

class AssetsManagerEx;

/**
 * @~english EventAssetsManagerEx is the event class which will be distributed during AssetsManagerEx updating process
 * @~chinese EventAssetsManagerEx是AssetsManagerEx在更新过程中分发的事件类型
 */
class CC_EX_DLL EventAssetsManagerEx : public cocos2d::EventCustom
{
public:
    
    friend class AssetsManagerEx;
    
    /** @~english Update events code
     * @~chinese 更新事件列表
     */
    enum class EventCode
    {
        /** @~english Local manifest not found error
         * @~chinese 本地资源清单文件未找到
         */
        ERROR_NO_LOCAL_MANIFEST,
        /** @~english Remote manifest download failed
         * @~chinese 远程资源清单文件下载失败
         */
        ERROR_DOWNLOAD_MANIFEST,
        /** @~english Manifest parse failed
         * @~chinese 资源清单文件解析失败
         */
        ERROR_PARSE_MANIFEST,
        /** @~english New version found
         * @~chinese 找到新版本
         */
        NEW_VERSION_FOUND,
        /** @~english Already up to date with the remote resources server
         * @~chinese 已经更新到服务器最新版本
         */
        ALREADY_UP_TO_DATE,
        /** @~english Update progression event
         * @~chinese 更新过程的进度事件
         */
        UPDATE_PROGRESSION,
        /** @~english One asset updated event
         * @~chinese 单个资源被更新事件
         */
        ASSET_UPDATED,
        /** @~english Error during update process
         * @~chinese 更新过程中遇到错误
         */
        ERROR_UPDATING,
        /** @~english Update finished event
         * @~chinese 更新成功事件
         */
        UPDATE_FINISHED,
        /** @~english Update failed event
         * @~chinese 更新失败事件
         */
        UPDATE_FAILED,
        /** @~english Failed to decompress a file event
         * @~chinese 解压缩失败
         */
        ERROR_DECOMPRESS
    };
    
    /** @brief @~english Gets the event code.
     * @~chinese 获取事件代码。
     * @return @~english The event code.
     * @~chinese 事件代码
     */
    inline EventCode getEventCode() const { return _code; };
    
    /** @brief @~english Gets the original curl error code for single file downloading `curl_easy_perform`.
     * Refer to the official error code document for detailed informations: http://curl.haxx.se/libcurl/c/libcurl-errors.html
     * @~chinese 获取CURL单文件下载`curl_easy_perform`出错时的错误代码。
     * 详细信息请参考官方错误代码文档：http://curl.haxx.se/libcurl/c/libcurl-errors.html
     * @return @~english The curl error code.
     * @~chinese CURL错误代码
     */
    inline int getCURLECode() const { return _curle_code; };
    
    /** @brief @~english Gets the original curl error code for multi file downloading `curl_multi_perform`.
     * Refer to the official error code document for detailed informations: http://curl.haxx.se/libcurl/c/libcurl-errors.html
     * @~chinese 获取CURL多文件下载`curl_multi_perform`出错时的错误代码。
     * 详细信息请参考官方错误代码文档：http://curl.haxx.se/libcurl/c/libcurl-errors.html
     * @return @~english The curl error code.
     * @~chinese CURL错误代码
     */
    inline int getCURLMCode() const { return _curlm_code; };
    
    /** @brief @~english Gets the event message.
     * @~chinese 获取事件信息。
     * @return @~english The event message.
     * @~chinese 事件信息
     */
    inline std::string getMessage() const { return _message; };
    
    /** @brief @~english Gets the asset id.
     * @~chinese 获取资源标识字符串。
     * @return @~english The asset id
     * @~chinese 资源标识字符串
     */
    inline std::string getAssetId() const { return _assetId; };
    
    /** @brief @~english Gets the AssetsManagerEx object.
     * @~chinese 获取资源管理器AssetsManagerEx对象。
     * @return @~english The AssetsManagerEx object
     * @~chinese 资源管理器AssetsManagerEx对象
     */
    inline cocos2d::extension::AssetsManagerEx *getAssetsManagerEx() const { return _manager; };
    
    /** @brief @~english Gets the byte level download percentage.
     * @~chinese 获取字节级下载进度。
     * @return @~english The byte level download percentage
     * @~chinese 字节级下载进度
     */
    inline float getPercent() const { return _percent; };
    
    /** @brief @~english Gets the file level download percentage.
     * @~chinese 获取文件级下载进度。
     * @return @~english The file level download percentage
     * @~chinese 文件级下载进度
     */
    inline float getPercentByFile() const { return _percentByFile; };
    
CC_CONSTRUCTOR_ACCESS:
    /** @~english Constructor  @~chinese 构造函数*/
    EventAssetsManagerEx(const std::string& eventName, cocos2d::extension::AssetsManagerEx *manager, const EventCode &code, float percent = 0, float percentByFile = 0, const std::string& assetId = "", const std::string& message = "", int curle_code = 0, int curlm_code = 0);
    
private:
    EventCode _code;
    
    cocos2d::extension::AssetsManagerEx *_manager;
    
    std::string _message;
    
    std::string _assetId;
    
    int _curle_code;
    
    int _curlm_code;
    
    float _percent;
    
    float _percentByFile;
};

/**
 * // AssetsManager
 * @}
 */

NS_CC_EXT_END

#endif /* defined(__cocos2d_libs__CCEventAssetsManagerEx__) */
