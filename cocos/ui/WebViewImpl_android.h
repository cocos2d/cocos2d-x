//
// Created by gin0606 on 2014/07/30.
//

#ifndef __cocos2d_plugin_WebViewImpl_android_H_
#define __cocos2d_plugin_WebViewImpl_android_H_

#include <iosfwd>

namespace cocos2d {
class Data;
class Renderer;
class Mat4;

namespace plugin {
class WebView;
}
}

namespace cocos2d {
namespace plugin {

class WebViewImpl {
public:
    WebViewImpl(cocos2d::plugin::WebView *webView);

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

    static bool shouldStartLoading(const int viewTag, const std::string &url);
    static void didFinishLoading(const int viewTag, const std::string &url);
    static void didFailLoading(const int viewTag, const std::string &url);
    static void onJsCallback(const int viewTag, const std::string &message);

private:
    int _viewTag;
    WebView *_webView;
};

} // namespace cocos2d
} // namespace plugin

#endif //__cocos2d_plugin_WebViewImpl_android_H_
