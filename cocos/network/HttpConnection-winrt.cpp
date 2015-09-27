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

#include "platform/CCPlatformConfig.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)

#include "network/HttpCookie.h"
#include "HttpConnection-winrt.h"

NS_CC_BEGIN

namespace network {

    // Format and add default headers (Platform specific approach)
    static void formatHeaders(std::vector<std::string>& headers)
    {
#if defined(_XBOX_ONE)
        for(auto iter = headers.begin(); iter != headers.end(); ++iter)
        {
            (*iter) += "\r\n";
        }

        // append default headers
        headers.emplace_back("User-Agent: XB1_IXHR2_HTTP\r\n");
        headers.emplace_back("x-xbl-device-type: XboxOne\r\n");
        headers.emplace_back("x-xbl-client-type: Console\r\n");
        headers.emplace_back("x-xbl-client-version: 1.0\r\n");
        headers.emplace_back("x-xbl-contract-version: 1\r\n");
#endif
    }

    // Get user authentication token (Platform specific approach)
    static bool getAuthenticationToken(std::string verb, std::string url, std::string headersXST, std::string bodyXST, std::string& token, std::string& signature)
    {
#if defined(_XBOX_ONE)
        using namespace Windows::Xbox::System;

        token = "";
        signature = "";
        User^ loggedInUser = nullptr;
        int ind = 0;

        while(ind < User::Users->Size)
        {
            loggedInUser = User::Users->GetAt(ind++);
            if(loggedInUser->IsSignedIn)
                break;

            loggedInUser = nullptr;
        }

        if(nullptr ==  loggedInUser)
            return false;

        Platform::Array<unsigned char>^ body;

        if(!bodyXST.empty()) {
            body = ref new Platform::Array<unsigned char>((unsigned char*)bodyXST.c_str(), bodyXST.size());
        }
        else {
            body = ref new Platform::Array<unsigned char>(1);
            body[0] = 0;
        }

        // this method will crash if TitleId & PrimaryServiceConfigId not specified in Package.appxmanifest.
        auto asynOp = loggedInUser->GetTokenAndSignatureAsync(
            ref new Platform::String(std::wstring(verb.begin(), verb.end()).c_str()),
            ref new Platform::String(std::wstring(url.begin(), url.end()).c_str()),
            ref new Platform::String(std::wstring(headersXST.begin(), headersXST.end()).c_str()), body);

        bool bRet = false;
        HRESULT hr = S_OK;

        asynOp->Completed = ref new Windows::Foundation::AsyncOperationCompletedHandler<GetTokenAndSignatureResult^>(
            [&token, &signature, &bRet, &hr](Windows::Foundation::IAsyncOperation<GetTokenAndSignatureResult^>^ operation, Windows::Foundation::AsyncStatus status)
        {
            if(status == Windows::Foundation::AsyncStatus::Completed) {
                try
                {
                    auto result = operation->GetResults();

                    std::wstring tok = result->Token->Data();
                    std::wstring sig = result->Signature->Data();
                    token = std::string(tok.begin(), tok.end());
                    signature = std::string(sig.begin(), sig.end());

                    bRet = true;
                }
                catch(Platform::Exception^ e)
                {
                    bRet = false;
                }
            }
            else {
                hr = operation->ErrorCode.Value;

                if(hr == 0x87dd0021) //AM_E_NO_TOKEN_REQUIRED
                    bRet = true;
            }
        });

        while(asynOp->Status == Windows::Foundation::AsyncStatus::Started)
        {
            ::Sleep(1);
        }

        return bRet;
#else
        return false;
#endif
    }


    // CXMLHTTPRequest2Callback
    CXHR2Callback::CXHR2Callback() :
        _statusCode(0),
        _hWfC(nullptr),
        _errorMsg("")
    {
    }

    CXHR2Callback::~CXHR2Callback()
    {
        if (nullptr != _hWfC)
        {
            CloseHandle(_hWfC);
            _hWfC = nullptr;
        }
    }

    HRESULT CXHR2Callback::RuntimeClassInitialize()
    {
        _hWfC = CreateEventEx(nullptr, nullptr, CREATE_EVENT_MANUAL_RESET, EVENT_ALL_ACCESS);
        return HRESULT_FROM_WIN32(GetLastError());
    }

    HRESULT CXHR2Callback::OnRedirect(IXMLHTTPRequest2 *pXHR, const WCHAR *pwszRedirectUrl)
    {
        UNREFERENCED_PARAMETER(pXHR);
        UNREFERENCED_PARAMETER(pwszRedirectUrl);

        return S_OK;
    }

    HRESULT CXHR2Callback::OnHeadersAvailable(IXMLHTTPRequest2 *pXHR, DWORD dwStatus, const WCHAR *pwszStatus)
    {
        _statusCode = dwStatus;

        if(nullptr == pXHR) {
            return E_INVALIDARG;
        }

        WCHAR *headers = nullptr;
        HRESULT hr = pXHR->GetAllResponseHeaders(&headers);

        if(SUCCEEDED(hr)) {
            std::wstring hdr = headers;
            _headers.insert(_headers.end(), hdr.begin(), hdr.end()); 
        }

        if(headers != nullptr) {
            CoTaskMemFree(headers);
            headers = nullptr;
        }

        return hr;
    }

    HRESULT CXHR2Callback::OnDataAvailable(IXMLHTTPRequest2 *pXHR, ISequentialStream *pResponseStream)
    {
        UNREFERENCED_PARAMETER(pXHR);

        return ReadStreamData(pResponseStream);
    }

    HRESULT CXHR2Callback::OnResponseReceived(IXMLHTTPRequest2 *pXHR, ISequentialStream *pResponseStream)
    {
        UNREFERENCED_PARAMETER(pXHR);

        HRESULT hr = ReadStreamData(pResponseStream);

        CompleteRequest(hr);

        return hr;
    }

    HRESULT CXHR2Callback::OnError(IXMLHTTPRequest2 *pXHR, HRESULT hrError)
    {
        CompleteRequest(hrError);

        return hrError;
    }

    HRESULT CXHR2Callback::WaitForComplete(PDWORD pdwStatus)
    {
        HRESULT hr = E_FAIL;

        if (NULL != _hWfC)
        {
            hr = S_OK;
            DWORD error;

            error = WaitForSingleObjectEx(_hWfC, INFINITE, FALSE);

            if (error == WAIT_FAILED) {
                hr = HRESULT_FROM_WIN32(GetLastError());
            }

            if (error != WAIT_OBJECT_0) {
                hr = E_ABORT;
            }
        }

        if (SUCCEEDED(hr)) {
            *pdwStatus = _statusCode;
        }

        return hr;
    }

    HRESULT CXHR2Callback::ReadStreamData(ISequentialStream* pResponseStream)
    {
        if(pResponseStream == NULL) {
            return E_INVALIDARG;
        }

        CCHAR buff[READ_BUFFER_MAX];
        DWORD totalBytes = 0;
        DWORD bytesRead = 0;
        HRESULT hr = S_OK;

        do
        {
            hr = pResponseStream->Read(buff, READ_BUFFER_MAX, &bytesRead);

            if(FAILED(hr)) {
                break;
            }

            _data.insert(_data.end(), &buff[0], buff + bytesRead);
            totalBytes += bytesRead;
        }
        while(hr == S_OK);

        if(SUCCEEDED(hr)) {
            hr = S_OK;
        }

        return hr;
    }

    void CXHR2Callback::CompleteRequest(HRESULT hrError)
    {
        if (NULL != _hWfC) {
            SetEvent(_hWfC);
        }

        switch (hrError)
        {
        case S_OK:
        case S_FALSE:
            _statusCode = 200;
            break;

        case INET_E_AUTHENTICATION_REQUIRED:
            _statusCode = 401;
            _errorMsg = ERR_MSG_401;
            break;

        case INET_E_DOWNLOAD_FAILURE:
            _statusCode = 500;
            _errorMsg = ERR_MSG_DL_FLD;
            break;

        case INET_E_FORBIDFRAMING:
            _statusCode = 403;
            _errorMsg = ERR_MSG_403;
            break;

        case INET_E_RESOURCE_NOT_FOUND:
            _statusCode = 404;
            _errorMsg = ERR_MSG_404;
            break;

        case RPC_S_PROXY_ACCESS_DENIED:
            _statusCode = 407;
            _errorMsg = ERR_MSG_407;
            break;

        case ERROR_RESOURCE_CALL_TIMED_OUT:
            _statusCode = 408;
            _errorMsg = ERR_MSG_408;
            break;

        case INET_E_INVALID_REQUEST:
            _statusCode = 400;
            _errorMsg = ERR_MSG_400;
            break;

        case E_ABORT:
            _statusCode = 412;
            _errorMsg = ERR_MSG_412;
            break;

        default:
            _statusCode = 500;
            _errorMsg = ERR_MSG_500;
            break;
        }
    }


    //CXHR2DataStream
    CXHR2DataStream::CXHR2DataStream() :
        _pData(nullptr),
        _dataSize(0),
        _seekIndex(0),
        _refCnt(1)
    {
    }

    CXHR2DataStream::~CXHR2DataStream()
    {
        if(nullptr != _pData)
            delete[] _pData;
    }

    ULONG CXHR2DataStream::Length()
    {
        return _dataSize;
    }

    HRESULT CXHR2DataStream::Init(const void *psBuffer, ULONG cbBufferSize)
    {
        HRESULT hr = S_OK;

        if(psBuffer == nullptr || cbBufferSize > REQUEST_BUFFER_MAX) {
            hr = E_INVALIDARG;
        }

        if(SUCCEEDED(hr)) {
            _dataSize = cbBufferSize;
            _seekIndex = 0;
            _pData = new (std::nothrow) BYTE[_dataSize];

            if(_pData == nullptr)
                hr = E_OUTOFMEMORY;
        }

        if(SUCCEEDED(hr)) {
            memcpy_s(_pData, _dataSize, psBuffer, cbBufferSize);
        }

        return hr;
    }

    HRESULT CXHR2DataStream::Read(void *pv, ULONG cb, ULONG *pcbRead)
    {
        HRESULT hr = S_OK;

        if(pv == nullptr) {
            hr = E_INVALIDARG;
        }

        if(SUCCEEDED(hr)) {
            BYTE* pOutput = (BYTE*)pv;
            BYTE* _pInput = _pData;

            for(*pcbRead = 0; *pcbRead < cb; (*pcbRead)++)
            {
                if(_seekIndex == _dataSize) {
                    hr = S_FALSE;
                    break;
                }

                pOutput[*pcbRead] = _pInput[*pcbRead];
                _seekIndex++;
            }
        }

        return hr;
    }

    HRESULT CXHR2DataStream::Write(const void *pv,  ULONG cb, ULONG *pcbWritten)
    {
        HRESULT hr = E_NOTIMPL;

        UNREFERENCED_PARAMETER(pv);
        UNREFERENCED_PARAMETER(cb);
        UNREFERENCED_PARAMETER(pcbWritten);

        return hr;
    }

    ULONG CXHR2DataStream::AddRef()
    {
        return ::InterlockedIncrement(&_refCnt);
    }

    ULONG CXHR2DataStream::Release()
    {
        ULONG refCnt = ::InterlockedDecrement(&_refCnt);

        if(0 == refCnt) {
            delete this;
        }

        return refCnt;
    }

    HRESULT CXHR2DataStream::QueryInterface(REFIID riid, void **ppvObject)
    {
        HRESULT hr = S_OK;

        if(ppvObject == nullptr) {
            hr = E_INVALIDARG;
        }

        void *pObject = nullptr;

        if(SUCCEEDED(hr)) {

            if(riid == IID_IUnknown) {
                pObject = static_cast<IUnknown*>((IDispatch*)this);
            }
            else if(riid == IID_IDispatch) {
                pObject = static_cast<IDispatch*>(this);
            }
            else if(riid == IID_ISequentialStream) {
                pObject = static_cast<ISequentialStream*>(this);
            }
            else {
                hr = E_NOINTERFACE;
            }
        }

        if(SUCCEEDED(hr)) {
            AddRef();
            *ppvObject = pObject;
            pObject = nullptr;
        }

        return hr;
    }

    HRESULT CXHR2DataStream::GetTypeInfoCount(unsigned int FAR*  pctinfo)
    {
        HRESULT hr = E_NOTIMPL;

        if(pctinfo)
            *pctinfo = 0;

        return hr;
    }

    HRESULT CXHR2DataStream::GetTypeInfo(unsigned int  iTInfo, LCID  lcid, ITypeInfo FAR* FAR*  ppTInfo)
    {
        HRESULT hr = E_NOTIMPL;

        if(ppTInfo)
            *ppTInfo = 0;

        UNREFERENCED_PARAMETER(iTInfo);
        UNREFERENCED_PARAMETER(lcid);

        return hr;
    }

    HRESULT CXHR2DataStream::GetIDsOfNames(REFIID riid, OLECHAR FAR* FAR* rgszNames, unsigned int cNames, LCID lcid, DISPID FAR* rgDispId)
    {
        HRESULT hr = DISP_E_UNKNOWNNAME;

        UNREFERENCED_PARAMETER(riid);
        UNREFERENCED_PARAMETER(rgszNames);
        UNREFERENCED_PARAMETER(cNames);
        UNREFERENCED_PARAMETER(lcid);
        UNREFERENCED_PARAMETER(rgDispId);

        return hr;
    }

    HRESULT CXHR2DataStream::Invoke(DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS FAR* pDispParams, VARIANT FAR* pVarResult, EXCEPINFO FAR* pExcepInfo, unsigned int FAR* puArgErr)
    {
        HRESULT hr = S_OK;

        UNREFERENCED_PARAMETER(dispIdMember);
        UNREFERENCED_PARAMETER(riid);
        UNREFERENCED_PARAMETER(lcid);
        UNREFERENCED_PARAMETER(wFlags);
        UNREFERENCED_PARAMETER(pDispParams);
        UNREFERENCED_PARAMETER(pVarResult);
        UNREFERENCED_PARAMETER(pExcepInfo);
        UNREFERENCED_PARAMETER(puArgErr);

        return hr;
    }


    // HttpConnection
    HttpConnection::HttpConnection() :
        _isInitialized(false),
        _spXhr(nullptr),
        _spXhrCallback(nullptr),
        _spXhrRequestData(nullptr),
        _pRequest(nullptr),
        _timeOutInMs(0)
    {
    }

    HttpConnection::~HttpConnection()
    {
    }

    bool HttpConnection::init(HttpRequest *pRequest, DWORD timeOutInMs)
    {
        if (_isInitialized || nullptr == pRequest) {
            return _isInitialized;
        }

        HRESULT hr = CoInitializeEx(NULL, NULL);

        if (SUCCEEDED(hr)) {
            hr = CoCreateInstance(CLSID_FreeThreadedXMLHTTP60, NULL, CLSCTX_SERVER, IID_PPV_ARGS(&_spXhr));
        }

        if (SUCCEEDED(hr)) {
            hr = MakeAndInitialize<CXHR2Callback>(&_spXhrCallback);
        }

        if(SUCCEEDED(hr)) {
            _pRequest = pRequest;
            _timeOutInMs = timeOutInMs;

            LONG size = _pRequest->getRequestDataSize();

            if(size > 0) {
                _spXhrRequestData = Make<CXHR2DataStream>();
                hr = _spXhrRequestData->Init(_pRequest->getRequestData(), size);
            }
        }

        return _isInitialized = SUCCEEDED(hr);
    }

    bool HttpConnection::open(std::string verb)
    {
        return open(verb, false, "");
    }

    bool HttpConnection::open(std::string verb, bool userAuthentication)
    {
        return open(verb, userAuthentication, "");
    }

    bool HttpConnection::open(std::string verb, std::string cookieFile)
    {
        return open(verb, false, cookieFile);
    }

    bool HttpConnection::open(std::string verb, bool userAuthentication, std::string cookieFile)
    {
        if (!_isInitialized) {
            return false;
        }

        std::wstring method(verb.begin(), verb.end());
        std::string url(_pRequest->getUrl());
        std::wstring wUrl(url.begin(), url.end());
        HRESULT hr = _spXhr->Open(method.c_str(), wUrl.c_str(), _spXhrCallback.Get(), NULL, NULL, NULL, NULL);

        if(SUCCEEDED(hr) && _timeOutInMs != 0) {
            hr = _spXhr->SetProperty(XHR_PROP_TIMEOUT, _timeOutInMs);
        }

#if 0
        if(SUCCEEDED(hr)) {
            hr = _spXhr->SetProperty(XHR_PROP_ONDATA_THRESHOLD, READ_BUFFER_MAX);
        }
#endif

        auto headers = _pRequest->getHeaders();
        formatHeaders(headers);

        for(auto header : headers)
        {
            std::string key = header.substr(0, header.find_first_of(':'));
            std::string value = header.substr(header.find_first_of(':') + 1, header.size() - 1);
            if(SUCCEEDED(hr)) {
                hr = _spXhr->SetRequestHeader(std::wstring(key.begin(), key.end()).c_str(), std::wstring(value.begin(), value.end()).c_str());
            }
        }

        if(SUCCEEDED(hr) && userAuthentication) {
            std::string authHeaders = std::accumulate(headers.begin(), headers.end(), std::string(""));
            hr = authenticateUser(verb, url, authHeaders);
        }

        if(SUCCEEDED(hr) && !cookieFile.empty()) {
            hr =  processCookieFile(url, cookieFile);
        }

        if(FAILED(hr)) {
            cancelRequest(hr);
        }

        return SUCCEEDED(hr);
    }

    HRESULT HttpConnection::authenticateUser(std::string& verb, std::string& url, std::string& headers)
    {
        HRESULT hr = S_OK;
        std::string authToken;
        std::string authSig;
        std::string authBody;

        if(_pRequest->getRequestDataSize() > 0)
            authBody = _pRequest->getRequestData();

        if(getAuthenticationToken(verb, url, headers, authBody, authToken, authSig)) {
            hr = _spXhr->SetRequestHeader(L"Authorization", std::wstring(authToken.begin(), authToken.end()).c_str());

            if(SUCCEEDED(hr)) {
                hr = _spXhr->SetRequestHeader(L"Signature", std::wstring(authSig.begin(), authSig.end()).c_str());
            }
        }
        else 
        {
            hr = INET_E_AUTHENTICATION_REQUIRED;
        }

        return hr;
    }

    HRESULT HttpConnection::processCookieFile(std::string& url, std::string& cookieFile)
    {
        HRESULT hr = S_OK;

        HttpCookie cookie;
        cookie.setCookieFileName(cookieFile);
        auto cookies = cookie.getCookies();
        std::string cookieInfo = "";
        int cCnt = 0;

        for(auto iter = cookies->begin(); iter != cookies->end(); iter++)
        {
            if(url.find(iter->domain) != std::string::npos)
            {
                std::string keyVal = iter->name;
                keyVal.append("=");
                keyVal.append(iter->value);
                if(cCnt != 0) {
                    cookieInfo.append(";");
                }
                cookieInfo.append(keyVal);
                cCnt++;
            }
        }

        if(!cookieInfo.empty() && nullptr != _spXhr) {
            hr = _spXhr->SetRequestHeader(L"Cookie", std::wstring(cookieInfo.begin(), cookieInfo.end()).c_str());
        }

        return hr;
    }

    bool HttpConnection::send()
    {
        if (!_isInitialized) {
            return false; 
        }

        HRESULT hr = E_FAIL;

        if(nullptr == _spXhrRequestData) {
            hr = _spXhr->Send(NULL, 0);
        }
        else {
            hr = _spXhr->Send(_spXhrRequestData.Get(), _spXhrRequestData->Length());
        }

        if(SUCCEEDED(hr)) {
            DWORD status = 0;
            hr = _spXhrCallback->WaitForComplete(&status);
        }
        else {
            cancelRequest(hr);
        }

        return SUCCEEDED(hr);
    }

    DWORD HttpConnection::getStatusCode()
    {
        return _spXhrCallback != nullptr ? _spXhrCallback->_statusCode : 500;
    }

    std::string HttpConnection::getErrorMessage()
    {
        return _spXhrCallback != nullptr ? _spXhrCallback->_errorMsg : ERR_MSG_500;
    }

    std::vector<char>* HttpConnection::getResponseHeader()
    {
        return _spXhrCallback != nullptr ? &_spXhrCallback->_headers : nullptr;
    }

    std::vector<char>* HttpConnection::getResponseData()
    {
        return _spXhrCallback != nullptr ? &_spXhrCallback->_data : nullptr;
    }

    void HttpConnection::cancelRequest(HRESULT hrError)
    {
        if(nullptr != _spXhr) {
            _spXhr->Abort();
            _spXhrCallback->CompleteRequest(hrError);
        }
    }
}

NS_CC_END

#endif // #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
