/****************************************************************************
 Copyright (c) 2014 cocos2d-x.org
 Author: Jeff Wang <wohaaitinciu@gmail.com>
 
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

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32

#include <atlbase.h>
#include <atlwin.h>
#include <ExDispid.h>
#include <UrlMon.h>
#include "UIWebViewImpl-win32.h"
#include "UIWebView.h"
#include "base/CCDirector.h"
#include "platform/CCFileUtils.h"
#include "platform/CCGLView.h"

// declarate
class Win32WebControl : public DWebBrowserEvents2
{
public:
    Win32WebControl();

    bool createWebView(
        const std::function<bool (const std::string &)> &shouldStartLoading,
        const std::function<void (const std::string &)> &didFinishLoading,
        const std::function<void (const std::string &)> &didFailLoading,
        const std::function<void (const std::string &)> &onJsCallback);
    void removeWebView();

    void setWebViewRect(const int left, const int top, const int width, const int height);
    void setJavascriptInterfaceScheme(const std::string &scheme) const;
    void loadData(const std::string &data, const std::string &MIMEType, const std::string &encoding, const std::string &baseURL) const;
    void loadHTMLString(const std::string &html, const std::string &baseURL);
    void loadURL(const std::string &url) const;
    void loadFile(const std::string &filePath) const;
    void stopLoading() const;
    void reload() const;
    bool canGoBack() const;
    bool canGoForward() const;
    void goBack() const;
    void goForward() const;
    void evaluateJS(const std::string &js) const;
    void setScalesPageToFit(const bool scalesPageToFit) const;
    void setWebViewVisible(const bool visible) const;

    // Implement IUnknown
    virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void **ppvObject);
    virtual ULONG STDMETHODCALLTYPE AddRef(void);
    virtual ULONG STDMETHODCALLTYPE Release(void);

    // Implement IDispatch
    virtual HRESULT STDMETHODCALLTYPE GetTypeInfoCount(UINT *pctinfo);
    virtual HRESULT STDMETHODCALLTYPE GetTypeInfo(UINT iTInfo, LCID lcid, ITypeInfo **ppTInfo);
    virtual HRESULT STDMETHODCALLTYPE GetIDsOfNames(
        REFIID riid,
        LPOLESTR *rgszNames,
        UINT cNames,
        LCID lcid,
        DISPID *rgDispId);
    virtual HRESULT STDMETHODCALLTYPE Invoke(
        DISPID dispIdMember,
        REFIID riid,
        LCID lcid,
        WORD wFlags,
        DISPPARAMS *pDispParams,
        VARIANT *pVarResult,
        EXCEPINFO *pExcepInfo,
        UINT *puArgErr);

private:
    CAxWindow _winContainer;
    IWebBrowser2 *_webBrowser2;
    IConnectionPoint *_connectionPoint;
    IDispatch *_htmlDoc;
    bool _goBackEnabled;
    bool _goForwardEnabled;
    DWORD _cookie;
    ULONG _reference;
    std::function<bool (const std::string &)> _shouldStartLoading;
    std::function<void (const std::string &)> _didFinishLoading;
    std::function<void (const std::string &)> _didFailLoading;
    std::function<void (const std::string &)> _onJsCallback;
    std::string _htmlWillLoad;

    static bool s_isInitialized;
    static CComModule s_module;
    static void lazyInit();

    void _loadHTMLString(const std::string &html) const;
    void loadURL(BSTR url) const;
    void loadURL(const std::wstring &url) const;
};



namespace cocos2d {
    namespace experimental {
        namespace ui {

            WebViewImpl::WebViewImpl(WebView *webView) : _createSucceeded(false), _systemWebControl(nullptr), _webView(webView)
            {
                _systemWebControl = new Win32WebControl();
                if (_systemWebControl == nullptr)
                {
                    return;
                }

                _createSucceeded = _systemWebControl->createWebView(
                    [this](const std::string &url)->bool {
                        std::function<bool (WebView *sender, const std::string &url)> shouldStartLoading = _webView->getOnShouldStartLoading();
                        if (shouldStartLoading != nullptr)
                        {
                            return shouldStartLoading(_webView, url);
                        }
                        return true;
                    },
                    [this](const std::string &url) {
                        WebView::ccWebViewCallback didFinishLoading = _webView->getOnDidFinishLoading();
                        if (didFinishLoading != nullptr)
                        {
                            didFinishLoading(_webView, url);
                        }
                    },
                    [this](const std::string &url) {
                        WebView::ccWebViewCallback didFailLoading = _webView->getOnDidFailLoading();
                        if (didFailLoading != nullptr)
                        {
                            didFailLoading(_webView, url);
                        }
                    },
                    [this](const std::string &url) {
                        WebView::ccWebViewCallback onJsCallback = _webView->getOnJSCallback();
                        if (onJsCallback != nullptr)
                        {
                            onJsCallback(_webView, url);
                        }
                    });
            }

            WebViewImpl::~WebViewImpl()
            {
                if (_systemWebControl != nullptr)
                {
                    _systemWebControl->removeWebView();
                    delete _systemWebControl;
                    _systemWebControl = nullptr;
                }
            }

            void WebViewImpl::loadData(const Data &data, const std::string &MIMEType, const std::string &encoding, const std::string &baseURL)
            {
                if (_createSucceeded)
                {
                    std::string dataString(reinterpret_cast<char *>(data.getBytes()), static_cast<unsigned int>(data.getSize()));
                    _systemWebControl->loadData(dataString, MIMEType, encoding, baseURL);
                }
            }

            void WebViewImpl::loadHTMLString(const std::string &string, const std::string &baseURL)
            {
                if (_createSucceeded)
                {
                    _systemWebControl->loadHTMLString(string, baseURL);
                }
            }

            void WebViewImpl::loadURL(const std::string &url)
            {
                if (_createSucceeded)
                {
                    _systemWebControl->loadURL(url);
                }
            }

            void WebViewImpl::loadFile(const std::string &fileName)
            {
                if (_createSucceeded)
                {
                    std::string fullPath = FileUtils::getInstance()->fullPathForFilename(fileName);
                    _systemWebControl->loadFile(fullPath);
                }
            }

            void WebViewImpl::stopLoading()
            {
                if (_createSucceeded)
                {
                    _systemWebControl->stopLoading();
                }
            }

            void WebViewImpl::reload()
            {
                if (_createSucceeded)
                {
                    _systemWebControl->reload();
                }
            }

            bool WebViewImpl::canGoBack()
            {
                if (_createSucceeded)
                {
                    return _systemWebControl->canGoBack();
                }
                return false;
            }

            bool WebViewImpl::canGoForward()
            {
                if (_createSucceeded)
                {
                    return _systemWebControl->canGoForward();
                }
                return false;
            }

            void WebViewImpl::goBack()
            {
                if (_createSucceeded)
                {
                    _systemWebControl->goBack();
                }
            }

            void WebViewImpl::goForward()
            {
                if (_createSucceeded)
                {
                    _systemWebControl->goForward();
                }
            }

            void WebViewImpl::setJavascriptInterfaceScheme(const std::string &scheme)
            {
                if (_createSucceeded)
                {
                    _systemWebControl->setJavascriptInterfaceScheme(scheme);
                }
            }

            void WebViewImpl::evaluateJS(const std::string &js)
            {
                if (_createSucceeded)
                {
                    _systemWebControl->evaluateJS(js);
                }
            }

            void WebViewImpl::setScalesPageToFit(const bool scalesPageToFit)
            {
                if (_createSucceeded)
                {
                    _systemWebControl->setScalesPageToFit(scalesPageToFit);
                }
            }

            void WebViewImpl::draw(Renderer *renderer, Mat4 const &transform, uint32_t flags)
            {
                if (_createSucceeded && (flags & Node::FLAGS_TRANSFORM_DIRTY))
                {
                    Director *directorInstance = cocos2d::Director::getInstance();
                    GLView *glView = directorInstance->getOpenGLView();
                    const Size &frameSize = glView->getFrameSize();
                    const Size &winSize = directorInstance->getWinSize();
                    Vec2 leftBottom = this->_webView->convertToWorldSpace(Point::ZERO);
                    Vec2 rightTop = this->_webView->convertToWorldSpace(Point(_webView->getContentSize().width, _webView->getContentSize().height));
                    float uiLeft = frameSize.width / 2 + (leftBottom.x - winSize.width / 2) * glView->getScaleX();
                    float uiTop = frameSize.height / 2 - (rightTop.y - winSize.height / 2) * glView->getScaleY();

                    _systemWebControl->setWebViewRect(uiLeft, uiTop,
                        (rightTop.x - leftBottom.x) * glView->getScaleX(),
                        (rightTop.y - leftBottom.y) * glView->getScaleY());
                }
            }

            void WebViewImpl::setVisible(bool visible)
            {
                if (_createSucceeded)
                {
                    _systemWebControl->setWebViewVisible(visible);
                }
            }
        } // namespace ui
    } // namespace experimental
} //namespace cocos2d

//
// Implement Win32WebControl
//
bool Win32WebControl::s_isInitialized = false;
CComModule Win32WebControl::s_module;

void Win32WebControl::lazyInit()
{
    // reset the main windows style so that its drawing does not cover the webview sub window
    HWND hwnd = cocos2d::Director::getInstance()->getOpenGLView()->getWin32Window();
    LONG style = GetWindowLong(hwnd, GWL_STYLE);
    SetWindowLong(hwnd, GWL_STYLE, style | WS_CLIPCHILDREN);

    HINSTANCE hInstance = GetModuleHandle(NULL);
    CoInitialize(NULL);
    s_module.Init(NULL, hInstance);
    AtlAxWinInit();
}

static HGLOBAL globalAllocWstringFromString(const std::string &str)
{
    int len = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);
    if (len <= 0)
    {
        return NULL;
    }
    HGLOBAL wstr = GlobalAlloc(GMEM_FIXED | GMEM_ZEROINIT, (len + 1) * sizeof(WCHAR));
    if (wstr == NULL)
    {
        return NULL;
    }
    MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, (WCHAR *)wstr, len);
    return wstr;
}

static std::string bstr2string(BSTR bstr)
{
    wchar_t *str = OLE2W(bstr);
    std::string ret;
    int len = WideCharToMultiByte(CP_UTF8, 0, str, -1, NULL, 0, NULL, NULL);
    if (len > 0)
    {
        HGLOBAL utf8Str = GlobalAlloc(GMEM_FIXED | GMEM_ZEROINIT, len + 1);
        if (utf8Str != NULL)
        {
            WideCharToMultiByte(CP_UTF8, 0, str, -1, (char *)utf8Str, len, NULL, NULL);
            ret.assign((char *)utf8Str);
            GlobalFree(utf8Str);
        }
    }
    return ret;
}

static bool isUrlJs(BSTR url)
{
    return wcsncmp(OLE2W(url), L"javascript:", 11) == 0;
}

Win32WebControl::Win32WebControl()
    : _webBrowser2(NULL)
    , _connectionPoint(NULL)
    , _htmlDoc(NULL)
    , _goBackEnabled(true)
    , _goForwardEnabled(true)
    , _cookie(0)
    , _reference(0)
    , _shouldStartLoading(nullptr)
    , _didFinishLoading(nullptr)
    , _didFailLoading(nullptr)
{
    if (!s_isInitialized)
    {
        lazyInit();
    }
}

bool Win32WebControl::createWebView(
    const std::function<bool (const std::string &)> &shouldStartLoading,
    const std::function<void (const std::string &)> &didFinishLoading,
    const std::function<void (const std::string &)> &didFailLoading,
    const std::function<void (const std::string &)> &onJsCallback)
{
    bool ret = false;
    IConnectionPointContainer *container = NULL;
    do
    {
        HWND hwnd = cocos2d::Director::getInstance()->getOpenGLView()->getWin32Window();
        _winContainer.Create(hwnd, NULL, NULL, WS_CHILD | WS_VISIBLE);

        HRESULT hr;
        hr = _winContainer.CreateControl(L"shell.Explorer.2");
        CC_BREAK_IF(FAILED(hr));

        hr = _winContainer.QueryControl(__uuidof(IWebBrowser2), (void **)&_webBrowser2);
        CC_BREAK_IF(FAILED(hr) || _webBrowser2 == NULL);

        _webBrowser2->put_Silent(VARIANT_TRUE);

        VARIANT var;
        VariantInit(&var);
        var.vt = VT_BSTR;
        var.bstrVal = SysAllocString(L"about:blank");
        hr = _webBrowser2->Navigate2(&var, NULL, NULL, NULL, NULL);
        SysFreeString(var.bstrVal);
        VariantClear(&var);
        CC_BREAK_IF(FAILED(hr));

        hr = _webBrowser2->QueryInterface(IID_IConnectionPointContainer, (void **)&container);
        CC_BREAK_IF(FAILED(hr));

        hr = container->FindConnectionPoint(DIID_DWebBrowserEvents2, &_connectionPoint);
        CC_BREAK_IF(FAILED(hr));

        hr = _connectionPoint->Advise(this, &_cookie);
        CC_BREAK_IF(FAILED(hr));

        hr = _webBrowser2->get_Document(&_htmlDoc);
        CC_BREAK_IF(FAILED(hr));

        ret = true;
    } while (0);

    if (!ret)
    {
        removeWebView();
    }
    if (container != NULL)
    {
        container->Release();
        container = NULL;
    }

    _shouldStartLoading = shouldStartLoading;
    _didFinishLoading = didFinishLoading;
    _didFailLoading = didFailLoading;
    _onJsCallback = onJsCallback;
    return ret;
}

void Win32WebControl::removeWebView()
{
    if (_connectionPoint != NULL)
    {
        _connectionPoint->Unadvise(_cookie);
        _connectionPoint->Release();
        _connectionPoint = NULL;
    }
    if (_htmlDoc != NULL)
    {
        _htmlDoc->Release();
        _htmlDoc = NULL;
    }
    if (_webBrowser2 != NULL)
    {
        _webBrowser2->Release();
        _webBrowser2 = NULL;
    }
    _winContainer.DestroyWindow();
}

void Win32WebControl::setWebViewRect(const int left, const int top, const int width, const int height)
{
    _winContainer.MoveWindow(left, top, width, height);
}

void Win32WebControl::setJavascriptInterfaceScheme(const std::string &scheme) const
{
    // To be implemented!
}

void Win32WebControl::loadData(const std::string &data, const std::string &MIMEType, const std::string &encoding, const std::string &baseURL) const
{
    // To be implemented!
}

void Win32WebControl::loadHTMLString(const std::string &html, const std::string &baseURL)
{
    // NOTE: should we load base URL first?
    // If so, we will cause many loadURL callbacks,
    // and it would be very difficult to distinguish between `loadURL' and `loadHTMLString'

    //if (baseURL.empty())
    //{
        _loadHTMLString(html);
    //}
    //else
    //{
    //    _htmlWillLoad = html;
    //    loadURL(baseURL);
    //}
}

void Win32WebControl::_loadHTMLString(const std::string &html) const
{
    bool flag = false;
    HGLOBAL htmlText = globalAllocWstringFromString(html);
    if (htmlText != NULL)
    {
        IStream *stream = NULL;
        if (SUCCEEDED(CreateStreamOnHGlobal(htmlText, FALSE, &stream)))
        {
            IPersistStreamInit *persistStreamInit = NULL;
            if (SUCCEEDED(_htmlDoc->QueryInterface(IID_IPersistStreamInit, (void **)&persistStreamInit)))
            {
                if (SUCCEEDED(persistStreamInit->InitNew()) && SUCCEEDED(persistStreamInit->Load(stream)))
                {
                    flag = true;
                }
                persistStreamInit->Release();
            }
            stream->Release();
        }
        GlobalFree(htmlText);
    }
    if (flag)
    {
        if (_didFinishLoading != nullptr)
        {
            std::string str("data:text/html,");
            str.append(html);
            _didFinishLoading(str);
        }
    }
    else
    {
        if (_didFailLoading != nullptr)
        {
            std::string str("data:text/html,");
            str.append(html);
            _didFailLoading(str);
        }
    }
}

void Win32WebControl::loadURL(BSTR url) const
{
    VARIANT var;
    VariantInit(&var);
    var.vt = VT_BSTR;
    var.bstrVal = url;
    _webBrowser2->Navigate2(&var, NULL, NULL, NULL, NULL);
    VariantClear(&var);
}

void Win32WebControl::loadURL(const std::wstring &url) const
{
    BSTR bstr = SysAllocString(url.c_str());
    loadURL(bstr);
    SysFreeString(bstr);
}

void Win32WebControl::loadURL(const std::string &url) const
{
    HGLOBAL unicodeStr = globalAllocWstringFromString(url);
    if (unicodeStr != NULL)
    {
        loadURL(std::wstring((WCHAR *)unicodeStr));
        GlobalFree(unicodeStr);
    }
}

void Win32WebControl::loadFile(const std::string &filePath) const
{
    HGLOBAL unicodeStr = globalAllocWstringFromString(filePath);
    if (unicodeStr != NULL)
    {
        loadURL(std::wstring((WCHAR *)unicodeStr));
        GlobalFree(unicodeStr);
    }
}

void Win32WebControl::stopLoading() const
{
    _webBrowser2->Stop();
}

void Win32WebControl::reload() const
{
    _webBrowser2->Refresh();
}

bool Win32WebControl::canGoBack() const
{
    return _goBackEnabled;
}

bool Win32WebControl::canGoForward() const
{
    return _goForwardEnabled;
}

void Win32WebControl::goBack() const
{
    _webBrowser2->GoBack();
}

void Win32WebControl::goForward() const
{
    _webBrowser2->GoForward();
}

void Win32WebControl::evaluateJS(const std::string &js) const
{
    std::string url("javascript:");
    url.append(js);
    loadURL(url);
}

void Win32WebControl::setScalesPageToFit(const bool scalesPageToFit) const
{
}

void Win32WebControl::setWebViewVisible(const bool visible) const
{
    _webBrowser2->put_Visible(visible ? VARIANT_TRUE : VARIANT_FALSE);
}

// Implement IUnknown
HRESULT STDMETHODCALLTYPE Win32WebControl::QueryInterface(REFIID riid, void **ppvObject)
{
    BOOL isBadPtr = FALSE;
    CCASSERT(!(isBadPtr = IsBadWritePtr(ppvObject, sizeof(void *))), "");
    if (isBadPtr)
    {
        return E_POINTER;
    }
    *ppvObject = NULL;

    if (IsEqualIID(riid, IID_IUnknown) || IsEqualIID(riid, IID_IDispatch) || IsEqualIID(riid, DIID_DWebBrowserEvents2))
    {
        AddRef();
        *ppvObject = this;
        return S_OK;
    }

    return E_NOINTERFACE;
}

ULONG STDMETHODCALLTYPE Win32WebControl::AddRef(void)
{
    InterlockedIncrement(&_reference);
    return _reference;
}

ULONG STDMETHODCALLTYPE Win32WebControl::Release(void)
{
    CCASSERT(_reference > 0, "reference count should greater than 0");
    InterlockedDecrement(&_reference);
    // DO NOT delete this if _reference == 0, otherwise, it will crash when call removeWebView
    return _reference;
}

// Implement IDispatch
HRESULT STDMETHODCALLTYPE Win32WebControl::GetTypeInfoCount(UINT *pctinfo)
{
    *pctinfo = 0;
    return S_OK;
}

HRESULT STDMETHODCALLTYPE Win32WebControl::GetTypeInfo(UINT iTInfo, LCID lcid, ITypeInfo **ppTInfo)
{
    UNREFERENCED_PARAMETER(iTInfo);
    UNREFERENCED_PARAMETER(lcid);
    *ppTInfo = NULL;
    return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE Win32WebControl::GetIDsOfNames(
    REFIID riid,
    LPOLESTR *rgszNames,
    UINT cNames,
    LCID lcid,
    DISPID *rgDispId)
{
    UNREFERENCED_PARAMETER(riid);
    UNREFERENCED_PARAMETER(rgszNames);
    UNREFERENCED_PARAMETER(cNames);
    UNREFERENCED_PARAMETER(lcid);
    UNREFERENCED_PARAMETER(rgDispId);
    return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE Win32WebControl::Invoke(
    DISPID dispIdMember,
    REFIID riid,
    LCID lcid,
    WORD wFlags,
    DISPPARAMS *pDispParams,
    VARIANT *pVarResult,
    EXCEPINFO *pExcepInfo,
    UINT *puArgErr)
{
    if (!IsEqualIID(riid, IID_NULL)) // riid should always be IID_NULL
    {
        return DISP_E_UNKNOWNINTERFACE;
    }

    switch (dispIdMember)
    {
    case DISPID_COMMANDSTATECHANGE:
        if (pDispParams != NULL && pDispParams->cArgs == 2)
        {
            const VARIANTARG *rgvarg = pDispParams->rgvarg;
            if (rgvarg[0].vt == VT_BOOL && rgvarg[1].vt == VT_I4)
            {
                switch (rgvarg[1].intVal)
                {
                case CSC_NAVIGATEFORWARD:
                    _goForwardEnabled = (rgvarg[0].boolVal != VARIANT_FALSE); // VARIANT_TRUE is -1
                    return S_OK;
                case CSC_NAVIGATEBACK:
                    _goBackEnabled = (rgvarg[0].boolVal != VARIANT_FALSE); // VARIANT_TRUE is -1
                    return S_OK;
                default:
                    break;
                }
            }
        }
        break;

    case DISPID_BEFORENAVIGATE2:
        if (pDispParams != NULL && pDispParams->cArgs == 7)
        {
            VARIANTARG *rgvarg = pDispParams->rgvarg;
            if (rgvarg[6].vt == VT_DISPATCH && rgvarg[6].pdispVal == _webBrowser2)
            {
                if (rgvarg[0].vt == (VT_BYREF | VT_BOOL) && rgvarg[5].vt == (VT_BYREF | VT_VARIANT))
                {
                    VARIANT_BOOL *cancel = rgvarg[0].pboolVal;
                    BSTR url = rgvarg[5].pvarVal->bstrVal;
                    *cancel = VARIANT_FALSE;
                    if (isUrlJs(url))
                    {
                        if (_onJsCallback != nullptr)
                        {
                            _onJsCallback(bstr2string(url + 11));  // skip the prefix `javascript'
                        }
                    }
                    else
                    {
                        if (_shouldStartLoading != nullptr)
                        {
                            *cancel = _shouldStartLoading(bstr2string(url)) ? VARIANT_FALSE : VARIANT_TRUE; // VARIANT_TRUE is -1
                        }
                    }
                    return S_OK;
                }
            }
        }
        break;

    case DISPID_DOCUMENTCOMPLETE:
        if (pDispParams != NULL && pDispParams->cArgs == 2)
        {
            const VARIANTARG *rgvarg = pDispParams->rgvarg;
            if (rgvarg[1].vt == VT_DISPATCH && rgvarg[1].pdispVal == _webBrowser2 && rgvarg[0].vt == (VT_BYREF | VT_VARIANT))
            {
                READYSTATE state;
                if (SUCCEEDED(_webBrowser2->get_ReadyState(&state)) && state == READYSTATE_COMPLETE)
                {
                    BSTR url = rgvarg[0].pvarVal->bstrVal;
                    if (_didFinishLoading != nullptr && !isUrlJs(url)) // ignore js
                    {
                        _didFinishLoading(bstr2string(url));
                    }
                    if (!_htmlWillLoad.empty())
                    {
                        _loadHTMLString(_htmlWillLoad);
                        _htmlWillLoad.clear();
                    }
                    return S_OK;
                }
            }
        }
        break;

    case DISPID_NAVIGATECOMPLETE2:
        if (pDispParams != NULL && pDispParams->cArgs == 2)
        {
            const VARIANTARG *rgvarg = pDispParams->rgvarg;
            if (rgvarg[1].vt == VT_DISPATCH && rgvarg[1].pdispVal == _webBrowser2)
            {
                if (rgvarg[0].vt == (VT_BYREF | VT_VARIANT))
                {
                    BSTR url = rgvarg[0].pvarVal->bstrVal;
                    return S_OK;
                }
            }
        }
        break;

    case DISPID_NAVIGATEERROR:
        if (pDispParams != NULL && pDispParams->cArgs == 5)
        {
            const VARIANTARG *rgvarg = pDispParams->rgvarg;
            if (rgvarg[4].vt == VT_DISPATCH && rgvarg[4].pdispVal == _webBrowser2)
            {
                if (rgvarg[3].vt == (VT_BYREF | VT_VARIANT) && rgvarg[1].vt == (VT_BYREF | VT_VARIANT) && rgvarg[0].vt == (VT_BYREF | VT_BOOL))
                {
                    VARIANT_BOOL *cancel = rgvarg[0].pboolVal;
                    HRESULT codes = rgvarg[1].pvarVal->lVal;
                    BSTR url = rgvarg[3].pvarVal->bstrVal;
                    if (_didFailLoading != nullptr && !isUrlJs(url)) // ignore js
                    {
                        _didFailLoading(bstr2string(url));
                    }
                    *cancel = VARIANT_FALSE;
                    return S_OK;
                }
            }
        }
        break;
    case DISPID_PROGRESSCHANGE:
        if (pDispParams != NULL && pDispParams->cArgs == 2)
        {
            const VARIANTARG *rgvarg = pDispParams->rgvarg;
            if (rgvarg[0].vt == VT_I4 && rgvarg[1].vt == VT_I4)
            {
                LONG maxProgress = rgvarg[0].lVal;
                LONG curProgress = rgvarg[1].lVal;
                return S_OK;
            }
        }
        break;

    case DISPID_NEWWINDOW2:
        if (pDispParams != NULL && pDispParams->cArgs == 2)
        {
            const VARIANTARG *rgvarg = pDispParams->rgvarg;
            if (rgvarg[0].vt == (VT_BYREF | VT_BOOL) && rgvarg[1].vt == (VT_BYREF | VT_DISPATCH))
            {
                VARIANT_BOOL *cancel = rgvarg[0].pboolVal;
                IDispatch **dis = rgvarg[1].ppdispVal;
                *dis = NULL;
                *cancel = VARIANT_TRUE; // forbit to create new window
                return S_OK;
            }
        }
        break;
    case DISPID_NEWWINDOW3:
        if (pDispParams != NULL && pDispParams->cArgs == 5)
        {
            const VARIANTARG *rgvarg = pDispParams->rgvarg;
            if (rgvarg[0].vt == VT_BSTR && rgvarg[1].vt == VT_BSTR && rgvarg[2].vt == VT_I4
                && rgvarg[3].vt == (VT_BYREF | VT_BOOL) && rgvarg[4].vt == (VT_BYREF | VT_DISPATCH))
            {
                BSTR url = rgvarg[0].bstrVal;
                BSTR urlContext = rgvarg[1].bstrVal;
                LONG flags = rgvarg[2].lVal;
                VARIANT_BOOL *cancel = rgvarg[3].pboolVal;
                IDispatch **dis = rgvarg[4].ppdispVal;
                *dis = NULL;
                *cancel = VARIANT_TRUE; // forbit to create new window
                loadURL(url);
                return S_OK;
            }
        }
        break;

    default:
        break;
    }
    return E_NOTIMPL;
}

#endif // CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
