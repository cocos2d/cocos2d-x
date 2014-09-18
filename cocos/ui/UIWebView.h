/****************************************************************************
 Copyright (c) 2014 Chukong Technologies Inc.
 
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

#ifndef __COCOS2D_UI_WEBVIEW_H
#define __COCOS2D_UI_WEBVIEW_H

#include "platform/CCPlatformConfig.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)


#include "ui/UIWidget.h"
#include "ui/GUIExport.h"
#include "base/CCData.h"

NS_CC_BEGIN
namespace experimental{
    namespace ui{
        
class WebViewImpl;

class CC_GUI_DLL WebView : public cocos2d::ui::Widget {
public:
    /**
    * Allocates and initializes a WebView.
    */
    static WebView *create();

    /**
    * Set javascript interface scheme.
    * @see #onJsCallback
    */
    void setJavascriptInterfaceScheme(const std::string &scheme);


    /**
    * Sets the main page contents, MIME type, content encoding, and base URL.
    * @param data The content for the main page.
    * @param MIMEType The MIME type of the data.
    * @param encoding the encoding of the data.
    * @param baseURL The base URL for the content.
    */
    void loadData(const cocos2d::Data &data,
                  const std::string &MIMEType,
                  const std::string &encoding,
                  const std::string &baseURL);
    

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
    void loadURL(const std::string &url);

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
    
    typedef std::function<void(WebView *sender, const std::string &url)> ccWebViewCallback;
    
    
    /**
     * Call before a web view begins loading.
     * @param sender The web view that is about to load new content.
     * @param url content URL.
     * @return YES if the web view should begin loading content; otherwise, NO .
     */
    void setOnShouldStartLoading(const std::function<bool(WebView *sender, const std::string &url)>& callback);
    
    /**
     * Call after a web view finishes loading.
     * @param sender The web view that has finished loading.
     * @param url content URL.
     */
    void setOnDidFinishLoading(const ccWebViewCallback& callback);
    
    /**
     * Call if a web view failed to load content.
     * @param sender The web view that has failed loading.
     * @param url content URL.
     */
    void setOnDidFailLoading(const ccWebViewCallback& callback);
    
    /**
     * This callback called when load URL that start with javascript interface scheme.
     */
    void setOnJSCallback(const ccWebViewCallback& callback);
    
    std::function<bool(WebView *sender, const std::string &url)> getOnShouldStartLoading()const;
    ccWebViewCallback getOnDidFinishLoading()const;
    ccWebViewCallback getOnDidFailLoading()const;
    ccWebViewCallback getOnJSCallback()const;
    
protected:
    virtual cocos2d::ui::Widget* createCloneInstance() override;
    virtual void copySpecialProperties(Widget* model) override;
    
    std::function<bool(WebView *sender, const std::string &url)> _onShouldStartLoading;
    
    ccWebViewCallback _onDidFinishLoading;
    
    ccWebViewCallback _onDidFailLoading;
   
    ccWebViewCallback _onJSCallback;

    /**
     * Default constructor
     */
    WebView();
    
    /**
     * Default destructor
     */
    virtual ~WebView();

private:
    WebViewImpl *_impl;
    friend class WebViewImpl;
};
        
      } // namespace ui
   } // namespace experimental
}//namespace cocos2d

#endif

#endif //__COCOS2D_UI_WEBVIEW_H
