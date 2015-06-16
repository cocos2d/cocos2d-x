/****************************************************************************
 Copyright (c) 2012      greathqy
 Copyright (c) 2012      cocos2d-x.org
 Copyright (c) 2013-2014 Chukong Technologies Inc.
 
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

#ifndef __CCHTTPCLIENT_H__
#define __CCHTTPCLIENT_H__

#include <thread>
#include <condition_variable>
#include "base/CCVector.h"
#include "base/CCScheduler.h"
#include "network/HttpRequest.h"
#include "network/HttpResponse.h"
#include "network/HttpCookie.h"

/**
 * @addtogroup network
 * @{
 */

NS_CC_BEGIN

namespace network {
    


/** @~english Singleton that handles asynchronous http requests.
 *
 * Once the request completed, a callback will be issued in main thread when it provided during make request.
 *
 * @~chinese 用于处理异步http请求的单例。
 *
 * 一旦完成一个请求,将设置一个主线程中调用的回调函数用来进行请求返回处理。
 * 
 * @lua NA
 */
class CC_DLL HttpClient
{
public:
	/**@~english
	* The buffer size of _responseMessage
    * @~chinese 
    * _responseMessage的缓存大小
	*/
	static const int RESPONSE_BUFFER_SIZE = 256;

    /**@~english
     * Get instance of HttpClient.
     *
     * @~chinese 
     * HttpClient的实例。
     * 
     * @return @~english the instance of HttpClient.
     * @~chinese HttpClient实例。
     */
    static HttpClient *getInstance();
    
    /** @~english
     * Destroy the instance of HttpClient. 
     * @~chinese 
     * 销毁HttpClient实例。
     */
    static void destroyInstance();

    /** @~english
     * Enable cookie support.
     *
     * @~chinese 
     * 启用cookie支持。
     * 
     * @param cookieFile @~english the filepath of cookie file.
     * @~chinese cookie文件的文件名。
     */
    void enableCookies(const char* cookieFile);
    
    /**@~english
     * Get the cookie filename
     * 
     * @~chinese 
     * 获取Cookie文件名
     * 
     * @return @~english the cookie filename
     * @~chinese Cookie文件名
     */
    const std::string& getCookieFilename();
    
    /**@~english
     * Set root certificate path for SSL verification.
     *
     * @~chinese 
     * 设置SSL证书路径。
     * 
     * @param caFile @~english a full path of root certificate.if it is empty, SSL verification is disabled.
     * @~chinese SSL证书的全路径，如果这个值为空, SSL验证将不起效。
     */
    void setSSLVerification(const std::string& caFile);
    
    /**@~english
     * Get ths SSL CA filename
     * 
     * @~chinese 
     * 获怪SSL证书的文件名
     * 
     * @return @~english the SSL CA filename
     * @~chinese SSL证书文件名
     */
    const std::string& getSSLVerification();
        
    /**@~english
     * Add a request to task queue
     *
     * @~chinese 
     * 添加一个request到任务队列中
     * 
     * @param request @~english a HttpRequest object, which includes url, response callback etc.
     * @~chinese 一个HttpRequest对象,包括url,响应回调等。
     */
    void send(HttpRequest* request);

    /**@~english
     * Immediate send a request
     *
     * @~chinese 
     * 立即发送一个request
     * 
     * @param request @~english a HttpRequest object, which includes url, response callback etc.
     * @~chinese HttpRequest对象,包括url,响应回调等。
     */
    void sendImmediate(HttpRequest* request);
    
    /**@~english
     * Set the timeout value for connecting in seconds.
     *
     * @~chinese 
     * 以秒为单位设置连接超时时间。
     * 
     * @param value @~english the timeout value for connecting in seconds.
     * @~chinese 以秒为单位的连接超时时间。
     */
    void setTimeoutForConnect(int value);
    
    /**@~english
     * Get the timeout value for connecting in seconds.
     *
     * @~chinese 
     * 获取以秒为单痊的连接超时时间。
     * 
     * @return @~english the timeout value for connecting in seconds.
     * @~chinese 以秒为单位的连接超时时间。
     */
    int getTimeoutForConnect();
    
    /**@~english
     * Set the timeout value for reading in seconds.
     *
     * @~chinese 
     * 设置以秒为单位的read超时时间。
     * 
     * @param value @~english the timeout value for reading in seconds.
     * @~chinese 以秒为单位的read超时时间。
     */
    void setTimeoutForRead(int value);

    /**@~english
     * Get the timeout value for reading in seconds.
     *
     * @~chinese 
     * 获得以秒为单位的read超时时间。
     * 
     * @return @~english the timeout value for reading in seconds.
     * @~chinese 以秒为单位的read超时时间。
     */
    int getTimeoutForRead();
    
    /**@~english
     *Get the Cookie object
     *
     *@~chinese
     *获取Cookie对象
     *
     * @return @~english the Cookie object
     * @~chinese Cookie对象
     */
    HttpCookie* getCookie() const {return _cookie; }
    
    /**@~english
     *Get the _cookieFileMutex that represents the std::mutex of the cookie files
     *
     *@~chinese
     *获取cookie文件互斥量_cookieFileMutex
     *
     * @return @~english the std::mutex 
     * @~chinese std::mutex
     */
    std::mutex& getCookieFileMutex() {return _cookieFileMutex;}
    
    /**@~english
     *Get the _sslCaFileMutex that represents the std::mutex of the SSL files
     *
     *@~chinese
     *获取SSL文件互斥量_cookieFileMutex
     *
     * @return @~english the std::mutex 
     * @~chinese std::mutex
     */
    std::mutex& getSSLCaFileMutex() {return _sslCaFileMutex;}
private:
    HttpClient();
    virtual ~HttpClient();
    bool init(void);
    
    /**@~english
     * Init pthread mutex, semaphore, and create new thread for http requests
     * @~chinese 
     * 初始化pthread互斥信号量,为http请求创建新线程
     * @return @~english bool
     * @~chinese bool值
     */
    bool lazyInitThreadSemphore();
    void networkThread();
    void networkThreadAlone(HttpRequest* request, HttpResponse* response);

    void dispatchResponseCallbacks();
    
    void processResponse(HttpResponse* response, char* responseMessage);
    void increaseThreadCount();
    void decreaseThreadCountAndMayDeleteThis();
    
private:
    bool _isInited;
    
    int _timeoutForConnect;
    std::mutex _timeoutForConnectMutex;
    
    int _timeoutForRead;
    std::mutex _timeoutForReadMutex;
    
    int  _threadCount;
    std::mutex _threadCountMutex;
    
    Scheduler* _scheduler;
    std::mutex _schedulerMutex;
    
    Vector<HttpRequest*>  _requestQueue;
    std::mutex _requestQueueMutex;
    
    Vector<HttpResponse*> _responseQueue;
    std::mutex _responseQueueMutex;
    
    std::string _cookieFilename;
    std::mutex _cookieFileMutex;
    
    std::string _sslCaFilename;
    std::mutex _sslCaFileMutex;
    
    HttpCookie* _cookie;
    
    std::condition_variable_any _sleepCondition;
    
	char _responseMessage[RESPONSE_BUFFER_SIZE];
    
    HttpRequest* _requestSentinel;
};

}

NS_CC_END

// end group
/// @}

#endif //__CCHTTPCLIENT_H__
