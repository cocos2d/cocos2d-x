/****************************************************************************
Copyright (c) 2012      greathqy
Copyright (c) 2012      cocos2d-x.org
Copyright (c) 2013-2017 Chukong Technologies Inc.

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

#include "platform/CCPlatformConfig.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)

#include "network/HttpRequest.h"
#include "network/HttpClient.h"

#include <thread>
#include <queue>
#include <numeric>
#include <condition_variable>

#include <errno.h>

#include <wrl.h>
#if defined(_XBOX_ONE)
#include <ixmlhttprequest2.h>
#else
#include <Msxml6.h>
#endif
using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Details;

#include "base/CCVector.h"
#include "base/CCDirector.h"
#include "base/CCScheduler.h"

#include "platform/CCFileUtils.h"

NS_CC_BEGIN

namespace network {

    const int READ_BUFFER_MAX = 16 * 1024;
    const int REQUEST_BUFFER_MAX = 4 * 1024 * 1024;

    const char ERR_MSG_500[] = "Internal server error";
    const char ERR_MSG_400[] = "Invalid request";
    const char ERR_MSG_401[] = "Authentication is required to access this resource";
    const char ERR_MSG_403[] = "Forbidden";
    const char ERR_MSG_404[] = "Specified resource could not be found";
    const char ERR_MSG_407[] = "Proxy authentication failed";
    const char ERR_MSG_408[] = "Request timed out";
    const char ERR_MSG_412[] = "Request aborted";
    const char ERR_MSG_DL_FLD[] = "The download of the specified resource has failed";

    class CXHR2Callback : public Microsoft::WRL::RuntimeClass<RuntimeClassFlags<ClassicCom>, IXMLHTTPRequest2Callback>
    {
    public:
        CXHR2Callback();
        ~CXHR2Callback();

        HRESULT RuntimeClassInitialize();
        HRESULT ReadStreamData(ISequentialStream* pResponseStream);
        STDMETHODIMP OnRedirect(IXMLHTTPRequest2 *pXHR, const WCHAR *pwszRedirectUrl);
        STDMETHODIMP OnHeadersAvailable(IXMLHTTPRequest2 *pXHR, DWORD dwStatus, const WCHAR *pwszStatus);
        STDMETHODIMP OnDataAvailable(IXMLHTTPRequest2 *pXHR, ISequentialStream *pResponseStream);
        STDMETHODIMP OnResponseReceived(IXMLHTTPRequest2 *pXHR, ISequentialStream *pResponseStream);
        STDMETHODIMP OnError(IXMLHTTPRequest2 *pXHR, HRESULT hrError);
        STDMETHODIMP WaitForComplete(PDWORD pdwStatus);

    protected:
        void CompleteRequest(HRESULT hrError);

    private:
        HANDLE _hWfC;
        DWORD _statusCode;
        std::string _errorMsg;
        std::vector<char> _headers;
        std::vector<char> _data;

        friend class HttpConnection;
    };

    class CXHR2DataStream : public Microsoft::WRL::RuntimeClass<RuntimeClassFlags<ClassicCom>, ISequentialStream, IDispatch>
    {
    public:
        CXHR2DataStream();
        ~CXHR2DataStream();

        STDMETHODIMP_(ULONG) Length();
        STDMETHODIMP Init(const void *psBuffer, ULONG cbBufferSize);

        STDMETHODIMP Read(void *pv, ULONG cb, ULONG *pcbRead);
        STDMETHODIMP Write(const void *pv,  ULONG cb, ULONG *pcbWritten);

        STDMETHODIMP_(ULONG) AddRef();
        STDMETHODIMP_(ULONG) Release();
        STDMETHODIMP QueryInterface(REFIID riid, void **ppvObject);

        STDMETHODIMP GetTypeInfoCount(unsigned int FAR*  pctinfo);
        STDMETHODIMP GetTypeInfo(unsigned int  iTInfo, LCID  lcid, ITypeInfo FAR* FAR*  ppTInfo);
        STDMETHODIMP GetIDsOfNames(REFIID riid, OLECHAR FAR* FAR* rgszNames, unsigned int cNames, LCID lcid, DISPID FAR* rgDispId);
        STDMETHODIMP Invoke(DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS FAR* pDispParams, VARIANT FAR* pVarResult, EXCEPINFO FAR* pExcepInfo, unsigned int FAR* puArgErr);

    private:
        ULONG    _refCnt;
        BYTE*   _pData;
        ULONG  _dataSize;
        ULONG  _seekIndex;
    };

    class HttpConnection
    {
    public:
        HttpConnection();
        ~HttpConnection();

        bool init(HttpRequest *pRequest, DWORD timeOutInMs = 0);
        bool open(const std::string& verb);
        bool open(const std::string& verb, bool userAuthentication);
        bool open(const std::string& verb, const std::string& cookieFile);
        bool open(const std::string& verb, bool userAuthentication, const std::string& cookieFile);
        bool send();
        DWORD getStatusCode();
        std::string getErrorMessage();
        std::vector<char>* getResponseHeader();
        std::vector<char>* getResponseData();

    protected:
        void cancelRequest(HRESULT hrError);
        HRESULT authenticateUser(const std::string& verb, const std::string& url, const std::string& headers);
        HRESULT processCookieFile(const std::string& url, const std::string& cookieFile);

    private:
        bool _isInitialized;
        ComPtr<IXMLHTTPRequest2> _spXhr;
        ComPtr<CXHR2Callback> _spXhrCallback;
        ComPtr<CXHR2DataStream> _spXhrRequestData;
        DWORD _timeOutInMs;
        cocos2d::network::HttpRequest* _pRequest;
    };
}

NS_CC_END

#endif // #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
