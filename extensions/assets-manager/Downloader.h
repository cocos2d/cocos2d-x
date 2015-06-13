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

#ifndef __Downloader__
#define __Downloader__

#include "platform/CCFileUtils.h"
#include "extensions/ExtensionMacros.h"
#include "extensions/ExtensionExport.h"

#include <unordered_map>
#include <string>
#include <functional>
#include <memory>

NS_CC_EXT_BEGIN

/**
 * @addtogroup AssetsManager
 * @{
 */

/**@~english
 * Downloader class is a util class for downloading files from a server.
 * It uses lib curl as its base network library.
 * - It can download a file to local file or a buffer in memory.
 * - It can download several files simultaneously.
 * - It can start a asynchronous download process within another thread.
 * @~chinese 
 * Downloader下载器类是一个用于从服务器下载文件的工具类。
 * 它使用lib curl作为其基础网络库。
 * - 它可以下载文件到本地文件或内存缓冲区。
 * - 它可以同时下载多个文件。
 * - 它可以在另一个线程启动异步下载流程。
 */
class CC_EX_DLL Downloader : public std::enable_shared_from_this<Downloader>
{
public:

    friend class AssetsManagerEx;

    /** @~english The error code during download
     * @~chinese 下载错误代码
     */
    enum class ErrorCode
    {
        /** @~english Error during creating file
         * @~chinese 创建文件错误
         */
        CREATE_FILE,

        /** @~english Network error 
         * @~chinese 网络错误
         */
        NETWORK,

        /** @~english No new version found 
         * @~chinese 没有发现新版本
         */
        NO_NEW_VERSION,

        /** @~english Error during decompressing
         * @~chinese 解压错误
         */
        UNCOMPRESS,

        /** @~english Curl object uninited error
         * @~chinese Curl对象未初始化错误
         */
        CURL_UNINIT,
        
        /** @~english Curl multi download error
         * @~chinese Curl批量下载错误
         */
        CURL_MULTI_ERROR,
        
        /** @~english Curl easy download error
         * @~chinese Curl简单下载错误
         */
        CURL_EASY_ERROR,

        /** @~english Url given is not valid
         * @~chinese Url是无效的
         */
        INVALID_URL,

        /** @~english Storage path given is not valid
         * @~chinese 存储路径无效
         */
        INVALID_STORAGE_PATH,
        
        /** @~english Fail to retrieve header info
         * @~chinese 无法获取Header信息
         */
        PREPARE_HEADER_ERROR
    };

    /** @~english The error structure
     * @~chinese 错误结构体
     */
    struct Error
    {
        /** @~english The error code
         * @~chinese 错误代码
         */
        ErrorCode code;
        /** @~english The curl multi download error code
         * @~chinese Curl批量下载错误代码
         */
        int curlm_code;
        /** @~english The curl easy download error code
         * @~chinese Curl简单下载错误代码
         */
        int curle_code;
        /** @~english The error message
         * @~chinese 错误消息
         */
        std::string message;
        /** @~english The custom id to identify the download file
         * @~chinese 用来识别下载文件的自定义id
         */
        std::string customId;
        /** @~english The url of the download file
         * @~chinese 下载文件的url
         */
        std::string url;
    };

    /** @~english The progression data structure
     * @~chinese 下载进度数据结构体
     */
    struct ProgressData
    {
        /** @~english The weak pointer to the downloader
         * @~chinese 指向下载器的弱指针
         */
        std::weak_ptr<Downloader> downloader;
        /** @~english The custom id to identify the download file
         * @~chinese 自定义id来识别下载文件
         */
        std::string customId;
        /** @~english The url of the download file
         * @~chinese 下载文件的url
         */
        std::string url;
        /** @~english The storage path of the download file
         * @~chinese 下载文件的存储路径
         */
        std::string path;
        /** @~english The storage name of the download file
         * @~chinese 下载文件的存储名称
         */
        std::string name;
        /** @~english The size that have already been downloaded
         * @~chinese 已经下载的大小
         */
        double downloaded;
        /** @~english The total size of the file
         * @~chinese 文件的总大小
         */
        double totalToDownload;
    };

    /** @~english The download unit structure
     * @~chinese 下载单元结构体
     */
    struct DownloadUnit
    {
        /** @~english The source url of the download file
         * @~chinese 下载文件的url
         */
        std::string srcUrl;
        /** @~english The storage path of the download file
         * @~chinese 下载文件的存储路径
         */
        std::string storagePath;
        /** @~english The custom id to identify the download file
         * @~chinese 自定义id来识别下载文件
         */
        std::string customId;
        /** @~english Flag to indicate whether the download can be resumed from previous download
         * @~chinese 指示下载是否是从之前的下载恢复的标识
         */
        bool resumeDownload;
    };
    
    /** @~english The streaming data structure
     * @~chinese 流数据结构体
     */
    struct StreamData
    {
        /** @~english The offset to continue saving the streaming data
         * @~chinese 保存流数据的偏移量
         */
        long offset;
        /** @~english The total size of the streaming data
         * @~chinese 流数据的总大小
         */
        long total;
        /** @~english The buffer object
         * @~chinese 缓冲区对象
         */
        unsigned char *buffer;
    };
    
    /** @~english The header info structure
     * @~chinese Header信息结构体
     */
    struct HeaderInfo
    {
        /** @~english Header valid or not
         * @~chinese Header有效与否
         */
        bool valid;
        /** @~english The source url
         * @~chinese 文件的url
         */
        std::string url;
        /** @~english The content type
         * @~chinese 内容类型
         */
        std::string contentType;
        /** @~english The content size
         * @~chinese 内容大小
         */
        double contentSize;
        /** @~english The response code
         * @~chinese 响应代码
         */
        double responseCode;
    };
    
    typedef std::unordered_map<std::string, DownloadUnit> DownloadUnits;
    
    typedef std::function<void(const Downloader::Error &)> ErrorCallback;
    typedef std::function<void(double, double, const std::string &, const std::string &)> ProgressCallback;
    typedef std::function<void(const std::string &, const std::string &, const std::string &)> SuccessCallback;
    typedef std::function<void(const std::string &, const HeaderInfo &)> HeaderCallback;

    /** @~english Gets the connection time out, counted in seconds
     * @~chinese 获取连接超时时间，以秒为单位计算
     * @return @~english The connection time out
     * @~chinese 连接超时时间
     */
    int getConnectionTimeout();

    /** @~english Sets the connection time out, counted in seconds
     * @~chinese 设置连接超时时间，以秒为单位计算
     * @param timeout @~english The connection time out
     * @~chinese 连接超时时间
     */
    void setConnectionTimeout(int timeout);
    
    /** @~english Sets the callback for notifing error
     * @~chinese 设置通知错误的回调函数
     * @param callback @~english The error callback
     * @~chinese 错误的回调函数
     */
    void setErrorCallback(const ErrorCallback &callback) { _onError = callback; };
    
    /** @~english Sets the callback for notifing download progression
     * @~chinese 设置通知下载进度的回调函数
     * @param callback @~english The download progression callback
     * @~chinese 下载进程回调函数
     */
    void setProgressCallback(const ProgressCallback &callback) { _onProgress = callback; };
    
    /** @~english Sets the callback for notifing succeed
     * @~chinese 设置通知成功的回调函数
     * @param callback @~english The succeed callback
     * @~chinese 成功的回调函数
     */
    void setSuccessCallback(const SuccessCallback &callback) { _onSuccess = callback; };
    
    /** @~english Sets the callback for notifing header
     * @~chinese 设置请求Header信息的回调函数
     * @param callback @~english The header callback
     * @~chinese 请求Header回调函数
     */
    void setHeaderCallback(const HeaderCallback &callback) { _onHeader = callback; };

    /** @~english Gets the callback for notifing error
     * @~chinese 获取错误的回调函数
     * @return @~english The error callback
     * @~chinese 错误的回调函数
     */
    ErrorCallback getErrorCallback() const { return _onError; };

    /** @~english Gets the callback for notifing download progression
     * @~chinese 获取通知下载进度的回调函数
     * @return @~english The download progression callback
     * @~chinese 下载进程回调函数
     */
    ProgressCallback getProgressCallback() const { return _onProgress; };

    /** @~english Gets the callback for notifing succeed
     * @~chinese 获取通知成功的回调函数
     * @return @~english The succeed callback
     * @~chinese 成功的回调函数
     */
    SuccessCallback getSuccessCallback() const { return _onSuccess; };
    
    /** @~english Gets the callback for notifing header
     * @~chinese 获取请求Header信息的回调函数
     * @return @~english The header callback
     * @~chinese 请求Header回调函数
     */
    HeaderCallback getHeaderCallback() const { return _onHeader; };
    
    /** @~english Gets the file content size of the given url
     * @~chinese 获取给定Url的文件内容大小
     * @param srcUrl @~english The source url
     * @~chinese 资源Url地址
     * @return @~english The content size
     * @~chinese 内容大小
     */
    long getContentSize(const std::string &srcUrl);
    
    /** @~english Gets the file header of the given url asynchronously
     * @~chinese 异步获取给定url的文件Header
     * @param srcUrl @~english The source url
     * @~chinese 给定的资源url
     * @param callback @~english The callback while the header returned
     * @~chinese 获取Header信息的回调函数
     */
    void getHeaderAsync(const std::string &srcUrl, const HeaderCallback &callback);
    
    /** @~english Streaming download a file to a memory buffer asynchronously
     * @~chinese 异步下载文件到内存缓冲区
     * @param srcUrl @~english The source url
     * @~chinese 资源url
     * @param buffer @~english The buffer to store the stream
     * @~chinese 存储缓冲区
     * @param size @~english The size of the buffer
     * @~chinese 缓冲区的大小
     * @param customId @~english The custom id to identify the file
     * @~chinese 自定义id来识别文件
     */
    void downloadToBufferAsync(const std::string &srcUrl, unsigned char *buffer, const long &size, const std::string &customId = "");
    
    /** @~english Streaming download a file to a memory buffer synchronously
     * @~chinese 同步下载文件到内存缓冲区
     * @param srcUrl @~english The source url
     * @~chinese 资源url
     * @param buffer @~english The buffer to store the stream
     * @~chinese 存储缓冲区
     * @param size @~english The size of the buffer
     * @~chinese 缓冲区的大小
     * @param customId @~english The custom id to identify the file
     * @~chinese 自定义id来识别文件
     */
    void downloadToBufferSync(const std::string &srcUrl, unsigned char *buffer, const long &size, const std::string &customId = "");

    /** @~english Download a file to a local file asynchronously
     * @~chinese 异步下载文件到本地文件
     * @param srcUrl @~english The source url
     * @~chinese 资源url
     * @param storagePath @~english The local storage path
     * @~chinese 本地存储路径
     * @param customId @~english The custom id to identify the file
     * @~chinese 自定义id来识别文件
     */
    void downloadAsync(const std::string &srcUrl, const std::string &storagePath, const std::string &customId = "");

    /** @~english Download a file to a local file synchronously
     * @~chinese 同步下载一个文件到本地文件
     * @param srcUrl @~english The source url
     * @~chinese 资源url
     * @param storagePath @~english The local storage path
     * @~chinese 本地存储路径
     * @param customId @~english The custom id to identify the file
     * @~chinese 自定义id来识别文件
     */
    void downloadSync(const std::string &srcUrl, const std::string &storagePath, const std::string &customId = "");
    
    /** @~english Batch download a list of files to local files asynchronously
     * @~chinese 异步批量下载文件列表到本地
     * @param units @~english The list of download units
     * @~chinese 下载单元列表，一个单元指示一个文件
     * @param batchId @~english The custom id to identify the batch download process
     * @~chinese 自定义id来识别批量下载过程
     */
    void batchDownloadAsync(const DownloadUnits &units, const std::string &batchId = "");
    
    /** @~english Batch download a list of files to local files synchronously
     * @~chinese 同步批量下载文件列表到本地
     * @param units @~english The list of download units
     * @~chinese 下载单元列表，一个单元指示一个文件
     * @param batchId @~english The custom id to identify the batch download process
     * @~chinese 自定义id来识别批量下载过程
     */
    void batchDownloadSync(const DownloadUnits &units, const std::string &batchId = "");

    /**@~english
     *  The default constructor.
     * @~chinese 
     * 默认构造函数。
     */
    Downloader();

    /**@~english
     *  The default destructor.
     * @~chinese 
     * 默认析构函数。
     */
    ~Downloader();

protected:
    
    struct FileDescriptor
    {
        FILE *fp;
        void *curl;
    };

    void prepareDownload(const std::string &srcUrl, const std::string &storagePath, const std::string &customId, bool resumeDownload, FileDescriptor *fDesc, ProgressData *pData);
    
#if(CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    HeaderInfo prepare(const std::string &srcUrl);
#endif
    HeaderInfo prepareHeader(const std::string &srcUrl, void* header = nullptr);
    
    void downloadToBuffer(const std::string &srcUrl, const std::string &customId, const StreamData &buffer, const ProgressData &data);

    void download(const std::string &srcUrl, const std::string &customId, const FileDescriptor &fDesc, const ProgressData &data);
    
    void groupBatchDownload(const DownloadUnits &units);

    void notifyError(ErrorCode code, const std::string &msg = "", const std::string &customId = "", int curle_code = 0, int curlm_code = 0);
    
    void notifyError(const std::string &msg, int curlm_code, const std::string &customId = "");
    
    void notifyError(const std::string &msg, const std::string &customId, int curle_code);

private:

    int _connectionTimeout;

    ErrorCallback _onError;

    ProgressCallback _onProgress;

    SuccessCallback _onSuccess;
    
    HeaderCallback _onHeader;

    std::string getFileNameFromUrl(const std::string &srcUrl);
    
    void clearBatchDownloadData();
    
    std::vector<FileDescriptor *> _files;
    
    std::vector<ProgressData *> _progDatas;
    
    FileUtils *_fileUtils;
    
    bool _supportResuming;
};

int downloadProgressFunc(Downloader::ProgressData *ptr, double totalToDownload, double nowDownloaded, double totalToUpLoad, double nowUpLoaded);

/**
 * // AssetsManager
 * @}
 */

NS_CC_EXT_END

#endif /* defined(__Downloader__) */