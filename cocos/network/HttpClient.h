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

#ifndef __CCHTTPREQUEST_H__
#define __CCHTTPREQUEST_H__

#include "network/HttpRequest.h"
#include "network/HttpResponse.h"
#include "network/HttpClient.h"

NS_CC_BEGIN

namespace network {

/**
 * @addtogroup 网络
 * @{
 */


/** @brief 处理异步http请求的单例模式
 * 一旦请求完成，一个在生成请求时被提供的回调函数，会被发到主线程中
 */
class HttpClient
{
public:
    /** 返回共享的实例 **/
    static HttpClient *getInstance();
    
    /** 释放共享的实例 **/
    static void destroyInstance();

    /** 启用cookie支持 **/
    void enableCookies(const char* cookieFile);
        
    /**
     * 增加一个get请求到任务队列
     * @param 请求一个HttpRequest对象，这个对象包含了url、相应回调等。
                    请确保在request->_requestData在被"send"调用之前是清晰的
     */
    void send(HttpRequest* request);
  
    
    /**
     * 改变连接的超时
     * @param value 期望的超时
     */
    inline void setTimeoutForConnect(int value) {_timeoutForConnect = value;};
    
    /**
     * 获取连接超时
     * @return int
     */
    inline int getTimeoutForConnect() {return _timeoutForConnect;}
    
    
    /**
     * 改变下载的超时
     * @param value
     */
    inline void setTimeoutForRead(int value) {_timeoutForRead = value;};
    

    /**
     * 获取下载超时
     * @return int
     */
    inline int getTimeoutForRead() {return _timeoutForRead;};
        
private:
    HttpClient();
    virtual ~HttpClient();
    bool init(void);
    
    /**
     * 初始化线程互斥、信号并为http请求创建新的线程
     * @return bool
     */
    bool lazyInitThreadSemphore();
    void networkThread();
    /** 从主线程中调用的poll函数，当http请求完成时分发回调 **/
    void dispatchResponseCallbacks();
    
private:
    int _timeoutForConnect;
    int _timeoutForRead;
};

// end of 网络 group
/// @}

}

NS_CC_END

#endif //__CCHTTPREQUEST_H__
