#include <atlbase.h>
#include <atlwin.h>
#include <ExDispid.h>

#include "UIWebViewImpl_win32.h"
#include "UIWebView.h"

#include "base/CCDirector.h"
#include "platform/CCFileUtils.h"
#include "platform/CCGLView.h"

namespace {

    class Win32WebView
    {
    public:
        Win32WebView()
            : m_pWebBrowser2(NULL)
            , m_bCanGoBack(true)
            , m_bCanGoForward(true)
            , m_dwCookie(0)
            , m_ulRef(0)
        {
            lazyInit();
        }

        bool createWebView()
        {
            bool bRet = false;
            do
            {
                HWND hwnd = cocos2d::Director::getInstance()->getOpenGLView()->getWin32Window();
                m_winContainer.Create(hwnd, NULL, NULL, WS_CHILD | WS_VISIBLE);

                HRESULT hr;
                hr = m_winContainer.CreateControl(L"shell.Explorer.2");
                CC_BREAK_IF(FAILED(hr));
                hr = m_winContainer.QueryControl(__uuidof(IWebBrowser2), (void **)&m_pWebBrowser2);
                CC_BREAK_IF(FAILED(hr) || m_pWebBrowser2 == NULL);

                m_pWebBrowser2->put_Silent(VARIANT_TRUE);

                VARIANT varURL;
                VariantInit(&varURL);
                varURL.vt = VT_BSTR;
                varURL.bstrVal = SysAllocString(L"about:blank");
                hr = m_pWebBrowser2->Navigate2(&varURL, NULL, NULL, NULL, NULL);
                VariantClear(&varURL);
                CC_BREAK_IF(FAILED(hr));

                bRet = true;
            } while (0);

            if (!bRet)
            {
                removeWebView();
            }
            return bRet;
        }

        void removeWebView()
        {
            if (m_pWebBrowser2 != NULL)
            {
                m_pWebBrowser2->Release();
                m_pWebBrowser2 = NULL;
            }
            m_winContainer.DestroyWindow();
        }

        void setWebViewRect(const int left, const int top, const int width, const int height)
        {
            m_winContainer.MoveWindow(left, top, width, height);
        }

        void setJavascriptInterfaceScheme(const std::string &scheme)
        {
        }

        void loadData(const std::string &data, const std::string &MIMEType, const std::string &encoding, const std::string &baseURL)
        {
        }

        void loadHTMLString(const std::string &str, const std::string &baseURL)
        {
            int len = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);
            if (len <= 0)
            {
                return;
            }

            HGLOBAL hHTMLText = GlobalAlloc(GMEM_FIXED | GMEM_ZEROINIT, (len + 1) * sizeof(WCHAR));
            if (hHTMLText == NULL)
            {
                return;
            }
            MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, (WCHAR *)hHTMLText, len);

            IStream* pStream = NULL;
            if (SUCCEEDED(CreateStreamOnHGlobal(hHTMLText, TRUE, &pStream)))
            {
                IDispatch* pHtmlDoc = NULL;
                if (SUCCEEDED(m_pWebBrowser2->get_Document(&pHtmlDoc)))
                {
                    IPersistStreamInit* pPersistStreamInit = NULL;
                    if (SUCCEEDED(pHtmlDoc->QueryInterface(IID_IPersistStreamInit, (void **)&pPersistStreamInit)))
                    {
                        pPersistStreamInit->InitNew();
                        pPersistStreamInit->Load(pStream);
                        pPersistStreamInit->Release();
                    }
                    pHtmlDoc->Release();
                }
                //pStream->Release();
            }
            GlobalFree(hHTMLText);
        }

        void loadUrl(const std::string &url)
        {
            int len = MultiByteToWideChar(CP_UTF8, 0, url.c_str(), -1, NULL, 0);
            if (len <= 0)
            {
                return;
            }

            HGLOBAL unicodeStr = GlobalAlloc(GMEM_FIXED | GMEM_ZEROINIT, (len + 1) * sizeof(WCHAR));
            if (unicodeStr == NULL)
            {
                return;
            }
            MultiByteToWideChar(CP_UTF8, 0, url.c_str(), -1, (WCHAR *)unicodeStr, len);

            VARIANT varURL;
            VariantInit(&varURL);
            varURL.vt = VT_BSTR;
            varURL.bstrVal = SysAllocString((WCHAR *)unicodeStr);
            m_pWebBrowser2->Navigate2(&varURL, NULL, NULL, NULL, NULL);
            VariantClear(&varURL);

            GlobalFree(unicodeStr);
        }

        void loadFile(const std::string &filePath)
        {
            int len = MultiByteToWideChar(CP_UTF8, 0, filePath.c_str(), -1, NULL, 0);
            if (len <= 0)
            {
                return;
            }

            HGLOBAL unicodeStr = GlobalAlloc(GMEM_FIXED | GMEM_ZEROINIT, (len + 1) * sizeof(WCHAR));
            if (unicodeStr == NULL)
            {
                return;
            }
            MultiByteToWideChar(CP_UTF8, 0, filePath.c_str(), -1, (WCHAR *)unicodeStr, len);

            HRESULT hr;

            VARIANT varURL;
            VariantInit(&varURL);
            varURL.vt = VT_BSTR;
            varURL.bstrVal = SysAllocString((WCHAR *)unicodeStr);
            hr = m_pWebBrowser2->Navigate2(&varURL, NULL, NULL, NULL, NULL);
            VariantClear(&varURL);

            GlobalFree(unicodeStr);
        }

        void stopLoading()
        {
            m_pWebBrowser2->Stop();
        }

        void reload()
        {
            m_pWebBrowser2->Refresh();
        }

        bool canGoBack()
        {
            return m_bCanGoBack;
        }

        bool canGoForward()
        {
            return m_bCanGoForward;
        }

        void goBack()
        {
            m_pWebBrowser2->GoBack();
        }

        void goForward()
        {
            m_pWebBrowser2->GoForward();
        }

        void evaluateJS(const std::string &js)
        {
            std::string url("javascript:");
            url.append(js);
            loadUrl(url);
        }

        void setScalesPageToFit(const bool scalesPageToFit)
        {
        }

        void setWebViewVisible(const bool visible)
        {
            m_pWebBrowser2->put_Visible(visible ? VARIANT_TRUE : VARIANT_FALSE);
        }

    private:
        CAxWindow m_winContainer;
        IWebBrowser2 *m_pWebBrowser2;
        bool m_bCanGoBack;
        bool m_bCanGoForward;
        DWORD m_dwCookie;
        ULONG m_ulRef;

        static bool s_bIsInitialized;
        static CComModule s_module;

        static void lazyInit()
        {
            if (!s_bIsInitialized)
            {
                HWND hwnd = cocos2d::Director::getInstance()->getOpenGLView()->getWin32Window();
                LONG style = GetWindowLong(hwnd, GWL_STYLE);
                SetWindowLong(hwnd, GWL_STYLE, style | WS_CLIPCHILDREN);

                HINSTANCE hInstance = GetModuleHandle(NULL);
                CoInitialize(NULL);
                s_module.Init(NULL, hInstance);
                AtlAxWinInit();
                s_bIsInitialized = true;
            }
        }
    };
    bool Win32WebView::s_bIsInitialized = false;
    CComModule Win32WebView::s_module;

} // namespace

namespace cocos2d {
    namespace experimental {
        namespace ui {

            WebViewImpl::WebViewImpl(WebView *webView) : _createSucceeded(false), _systemWebView(nullptr), _webView(webView)
            {
                _systemWebView = new Win32WebView();
                if (_systemWebView != nullptr)
                {
                    _createSucceeded = _systemWebView->createWebView();
                }
            }

            WebViewImpl::~WebViewImpl()
            {
                if (_systemWebView != nullptr)
                {
                    _systemWebView->removeWebView();
                    delete _systemWebView;
                    _systemWebView = nullptr;
                }
            }

            void WebViewImpl::loadData(const Data &data, const std::string &MIMEType, const std::string &encoding, const std::string &baseURL)
            {
                if (_createSucceeded)
                {
                    std::string dataString(reinterpret_cast<char *>(data.getBytes()), static_cast<unsigned int>(data.getSize()));
                    _systemWebView->loadData(dataString, MIMEType, encoding, baseURL);
                }
            }

            void WebViewImpl::loadHTMLString(const std::string &string, const std::string &baseURL)
            {
                if (_createSucceeded)
                {
                    _systemWebView->loadHTMLString(string, baseURL);
                }
            }

            void WebViewImpl::loadUrl(const std::string &url)
            {
                if (_createSucceeded)
                {
                    _systemWebView->loadUrl(url);
                }
            }

            void WebViewImpl::loadFile(const std::string &fileName)
            {
                if (_createSucceeded)
                {
                    std::string fullPath = FileUtils::getInstance()->fullPathForFilename(fileName);
                    _systemWebView->loadFile(fullPath);
                }
            }

            void WebViewImpl::stopLoading()
            {
                if (_createSucceeded)
                {
                    _systemWebView->stopLoading();
                }
            }

            void WebViewImpl::reload()
            {
                if (_createSucceeded)
                {
                    _systemWebView->reload();
                }
            }

            bool WebViewImpl::canGoBack()
            {
                if (_createSucceeded)
                {
                    return _systemWebView->canGoBack();
                }
                return false;
            }

            bool WebViewImpl::canGoForward()
            {
                if (_createSucceeded)
                {
                    return _systemWebView->canGoForward();
                }
                return false;
            }

            void WebViewImpl::goBack()
            {
                if (_createSucceeded)
                {
                    _systemWebView->goBack();
                }
            }

            void WebViewImpl::goForward()
            {
                if (_createSucceeded)
                {
                    _systemWebView->goForward();
                }
            }

            void WebViewImpl::setJavascriptInterfaceScheme(const std::string &scheme)
            {
                if (_createSucceeded)
                {
                    _systemWebView->setJavascriptInterfaceScheme(scheme);
                }
            }

            void WebViewImpl::evaluateJS(const std::string &js)
            {
                if (_createSucceeded)
                {
                    _systemWebView->evaluateJS(js);
                }
            }

            void WebViewImpl::setScalesPageToFit(const bool scalesPageToFit)
            {
                if (_createSucceeded)
                {
                    _systemWebView->setScalesPageToFit(scalesPageToFit);
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

                    _systemWebView->setWebViewRect(uiLeft, uiTop,
                        (rightTop.x - leftBottom.x) * glView->getScaleX(),
                        (rightTop.y - leftBottom.y) * glView->getScaleY());
                }
            }

            void WebViewImpl::setVisible(bool visible)
            {
                if (_createSucceeded)
                {
                    _systemWebView->setWebViewVisible(visible);
                }
            }
        } // namespace ui
    } // namespace experimental
} //namespace cocos2d
