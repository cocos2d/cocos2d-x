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

NS_CC_BEGIN

namespace network {

/**
 * @addtogroup Network
 * @{
 */


/** Singleton that handles asynchrounous http requests.
 *
 * Once the request completed, a callback will issued in main thread when it provided during make request.
 *
 * @lua NA
 */
class CC_DLL HttpClient
{
public:
    /**
     * Get instance of HttpClient.
     *
     * @return the instance of HttpClient.
     */
    static HttpClient *getInstance();
    
    /** 
     * Relase the instance of HttpClient. 
     */
    static void destroyInstance();

    /** 
     * Enable cookie support.
     *
     * @param cookieFile the filepath of cookie file.
     */
    void enableCookies(const char* cookieFile);
    
    /**
     * Set root certificate path for SSL verification.
     *
     * @param caFile a full path of root certificate.if it is empty, SSL verification is disabled.
     */
    void setSSLVerification(const std::string& caFile);
        
    /**
     * Add a get request to task queue
     *
     * @param request a HttpRequest object, which includes url, response callback etc.
                      please make sure request->_requestData is clear before calling "send" here.
     */
    void send(HttpRequest* request);

    /**
     * Immediate send a request
     *
     * @param request a HttpRequest object, which includes url, response callback etc.
                      please make sure request->_requestData is clear before calling "sendImmediate" here.
     */
    void sendImmediate(HttpRequest* request);
  
    
    /**
     * Set the timeout value for connecting.
     *
     * @param value the timeout value for connecting.
     */
    inline void setTimeoutForConnect(int value) {_timeoutForConnect = value;};
    
    /**
     * Get the timeout value for connecting.
     *
     * @return int the timeout value for connecting.
     */
    inline int getTimeoutForConnect() {return _timeoutForConnect;}
    
    
    /**
     * Set the timeout value for reading.
     *
     * @param value the timeout value for reading.
     */
    inline void setTimeoutForRead(int value) {_timeoutForRead = value;};
    

    /**
     * Get the timeout value for reading.
     *
     * @return int the timeout value for reading.
     */
    inline int getTimeoutForRead() {return _timeoutForRead;};
        
private:
    HttpClient();
    virtual ~HttpClient();
    bool init(void);
    
    /**
     * Init pthread mutex, semaphore, and create new thread for http requests
     * @return bool
     */
    bool lazyInitThreadSemphore();
    void networkThread();
    void networkThreadAlone(HttpRequest* request, HttpResponse* response);
    /** Poll function called from main thread to dispatch callbacks when http requests finished **/
    void dispatchResponseCallbacks();
    
private:
    int _timeoutForConnect;
    int _timeoutForRead;
};

// end of Network group
/// @}

}

NS_CC_END

#endif //__CCHTTPREQUEST_H__
