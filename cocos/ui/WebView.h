//
// Created by gin0606 on 2014/07/29.
//

#ifndef __Cocos2d_Plugin_WebView_H_
#define __Cocos2d_Plugin_WebView_H_

#include "ui/UIWidget.h"
#include "base/CCData.h"

namespace cocos2d {
namespace plugin {
class WebViewImpl;

class WebView : public cocos2d::ui::Widget {
public:
    /**
    * Allocates and initializes a WebView.
    */
    static WebView *create();

    /**
    * Default constructor
    */
    WebView();

    /**
    * Default destructor
    */
    virtual ~WebView();

    /**
    * Call before a web view begins loading.
    * @param sender The web view that is about to load new content.
    * @param url content URL.
    * @return YES if the web view should begin loading content; otherwise, NO .
    */
    std::function<bool(WebView *sender, std::string url)> shouldStartLoading;
    /**
    * Call after a web view finishes loading.
    * @param sender The web view that has finished loading.
    * @param url content URL.
    */
    std::function<void(WebView *sender, std::string url)> didFinishLoading;
    /**
    * Call if a web view failed to load content.
    * @param sender The web view that has failed loading.
    * @param url content URL.
    */
    std::function<void(WebView *sender, std::string url)> didFailLoading;

    /**
    * Set javascript interface scheme.
    * @see #onJsCallback
    */
    void setJavascriptInterfaceScheme(const std::string &scheme);

    /**
    * This callback called when load URL that start with javascript interface scheme.
    */
    std::function<void(WebView *sender, std::string message)> onJsCallback;

    /**
    * Sets the main page contents, MIME type, content encoding, and base URL.
    * @param data The content for the main page.
    * @param MIMEType The MIME type of the data.
    * @param encoding the encoding of the data.
    * @param baseURL The base URL for the content.
    */
    void loadData(const cocos2d::Data &data, const std::string &MIMEType, const std::string &encoding, const std::string &baseURL);

    /**
    * Sets the main page content and base URL.
    * @param string The content for the main page.
    * @param baseURL The base URL for the content.
    */
    void loadHTMLString(const std::string &string, const std::string &baseURL);

    /**
    * Loads the given URL.
    * @param url content URL
    */
    void loadUrl(const std::string &url);

    /**
    * Loads the given fileName.
    * @param fileName content fileName
    */
    void loadFile(const std::string &fileName);

    /**
    * Stops the current load.
    */
    void stopLoading();

    /**
    * Reloads the current URL.
    */
    void reload();

    /**
    * Gets whether this WebView has a back history item.
    * @return web view has a back history item.
    */
    bool canGoBack();

    /**
    * Gets whether this WebView has a forward history item.
    * @return web view has a forward history item.
    */
    bool canGoForward();

    /**
    * Goes back in the history.
    */
    void goBack();

    /**
    * Goes forward in the history.
    */
    void goForward();

    /**
    * evaluates JavaScript in the context of the currently displayed page
    */
    void evaluateJS(const std::string &js);

    /**
    * Set WebView should support zooming. The default value is false.
    */
    void setScalesPageToFit(const bool scalesPageToFit);

    virtual void draw(cocos2d::Renderer *renderer, cocos2d::Mat4 const &transform, uint32_t flags) override;

    virtual void setVisible(bool visible) override;

private:
    cocos2d::plugin::WebViewImpl *_impl;
};
} // namespace cocos2d
} // namespace plugin

#endif //__Cocos2d_Plugin_WebView_H_
