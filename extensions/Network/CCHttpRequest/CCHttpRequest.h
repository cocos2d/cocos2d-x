/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org
 Copyright (c) 2012 greathqy
 
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

#include "cocos2d.h"
#include "ExtensionMacros.h"

NS_CC_EXT_BEGIN

/**
 * @addtogroup Network
 * @{
 */

//Http request type
typedef enum {
    kHttpRequestGet,
    kHttpRequestPost,
    kHttpRequestDownloadFile,
} HttpRequestType;

//Request structure
typedef struct {
    HttpRequestType             reqType;
    std::string                 url;
    std::string                 reqData;
    std::vector<std::string>    files;
    std::string                 reqId;
    cocos2d::CCObject           *pTarget;
    cocos2d::SEL_CallFuncND     pSelector;
} HttpRequestPacket;

//Response structure
typedef struct {
    HttpRequestPacket       *request;
    std::string             responseData;
    int32_t                 responseCode;
    bool                    succeed;
} HttpResponsePacket;

/** @brief Singleton that handles asynchrounous http requests
 * Once the request completed, a callback will issued in main thread when it provided during make request
 */
class CC_DLL CCHttpRequest : public cocos2d::CCObject
{
public:
    /** Return the shared instance **/
    static CCHttpRequest *sharedHttpRequest();
    
    /** Relase the shared instance **/
    static void purgeSharedHttpRequest();
    
    CCHttpRequest();
    virtual ~CCHttpRequest();
    
    /**
     * Add a get request to task queue
     * @param url url want to get
     * @param pTarget  callback target
     * @param pSelector callback selector
     * @return NULL
     */
    void addGetTask(std::string url, cocos2d::CCObject *pTarget, cocos2d::SEL_CallFuncND pSelector);
    
    /**
     * Add a post request to task queue
     * @param url the post destination url
     * @param postData data want to post
     * @param pTarget  callback target
     * @param pSelector callback selector
     * @return NULL
     */
    void addPostTask(std::string &url, std::string &postData, cocos2d::CCObject *pTarget, cocos2d::SEL_CallFuncND pSelector);
    
    /**
     * Add a post request to task queue, binary data supported 
     * @param url the post destination url
     * @param buffer the data want to post
     * @param pTarget callback target
     * @param pSelector callback selector
     * @return NULL
     */
    void addPostTask(std::string &url, std::vector<char> &buffer, cocos2d::CCObject *pTarget, cocos2d::SEL_CallFuncND pSelector);
    
    /**
     * Add a post request to task queue, binary data supported
     * @param url the post destination url
     * @param buffer the data want to post
     * @param buffer the data's length
     * @param pTarget callback target
     * @param pSelector callback selector
     * @return NULL
     */
    void addPostTask(std::string &url, const char *buffer, int32_t bufferLen, cocos2d::CCObject *pTarget, cocos2d::SEL_CallFuncND pSelector);
    
    /**
     * Add a download request to task queue
     * @param url urls want to download
     * @param pTarget  callback target
     * @param pSelector callback selector
     * @return NULL
     */
    void addDownloadTask(std::vector<std::string> &urls, cocos2d::CCObject *pTarget, cocos2d::SEL_CallFuncND pSelector);
    
public:
    /**
     * Change the connect timeout
     * @param timeout 
     * @return NULL
     */
    inline void setConnectTimeout(int32_t timeout) {m_connectTimeout = timeout;};
    
    /**
     * Get connect timeout
     * @return int
     */ 
    inline int32_t getConnectTimeout() {return m_connectTimeout;}
    
    
    /**
     * Change the download timeout
     * @param timeout
     * @return NULL
     */
    inline void setDownloadTimeout(int32_t timeout) {m_timeout = timeout;};
    

    /**
     * Get download timeout
     * @return int
     */
    inline int32_t getDownloadTimeout() {return m_timeout;}
    
    /**
     * Set request Id
     * Used to distinguish multple requests if you don't want to provide different callbacks for each request
     * @param reqId request identifier
     * @return NULL
     */
    inline void setReqId(const std::string reqId) {this->reqId = reqId;}
    
    /**
     * Get request id
     * @return NULL
     */
    inline const std::string& getReqId() {return this->reqId;};
    
private:
    /**
     * Init pthread mutex, semaphore, and create new thread for http requests
     * @return bool
     */
    bool lazyInitThreadSemphore();
    /** Poll function called from main thread to dispatch callbacks when http requests finished **/
    void dispatchResponseCallbacks(float delta);
    
private:
    int32_t m_connectTimeout;
    int32_t m_timeout;
    
    std::string reqId;
};

// end of Network group
/// @}

NS_CC_EXT_END

#endif //__CCHTTPREQUEST_H__
