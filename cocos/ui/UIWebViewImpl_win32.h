#ifndef __cocos2d_plugin_WebViewImpl_win32_H_
#define __cocos2d_plugin_WebViewImpl_win32_H_

#include "base/CCPlatformConfig.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32

#include <string>
#include "CCStdC.h"

namespace cocos2d {
    class Data;
    class Renderer;
    class Mat4;

    namespace experimental {
        namespace ui {
            class WebView;
        }
    }
}

class Win32WebControl;

namespace cocos2d {
    namespace experimental {
        namespace ui {

            class WebViewImpl
            {
            public:
                WebViewImpl(cocos2d::experimental::ui::WebView *webView);

                virtual ~WebViewImpl();

                void setJavascriptInterfaceScheme(const std::string &scheme);

                void loadData(const cocos2d::Data &data, const std::string &MIMEType, const std::string &encoding, const std::string &baseURL);

                void loadHTMLString(const std::string &string, const std::string &baseURL);

                void loadUrl(const std::string &url);

                void loadFile(const std::string &fileName);

                void stopLoading();

                void reload();

                bool canGoBack();

                bool canGoForward();

                void goBack();

                void goForward();

                void evaluateJS(const std::string &js);

                void setScalesPageToFit(const bool scalesPageToFit);

                virtual void draw(cocos2d::Renderer *renderer, cocos2d::Mat4 const &transform, uint32_t flags);

                virtual void setVisible(bool visible);

            private:
                bool _createSucceeded;
                Win32WebControl *_systemWebControl;
                WebView *_webView;
            };

        } // namespace ui
    } // namespace experimental
} //cocos2d

#endif //__cocos2d_plugin_WebViewImpl_win32_H_

#endif
