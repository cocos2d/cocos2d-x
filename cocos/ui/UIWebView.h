/****************************************************************************
 Copyright (c) 2014-2015 Chukong Technologies Inc.
 
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

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS )


#include "ui/UIWidget.h"
#include "ui/GUIExport.h"
#include "base/CCData.h"

/**
 * @addtogroup ui
 * @{
 */

NS_CC_BEGIN
namespace experimental{
    namespace ui{
        
class WebViewImpl;

/**
 * @brief @~english A View that displays web pages. 
 *
 * @~chinese 一个用来显示web页面的控件。
 * 
 * @note @~english WebView displays web pages base on system widget.
 * It's mean WebView displays web pages above all graphical elements of cocos2d-x.
 * @~chinese WebView使用操作系统组件来显示网页内容。
 * 这意味着WebView会处于所有的Cocos2D-X渲染节点的上面。
 * @js NA
 */
class CC_GUI_DLL WebView : public cocos2d::ui::Widget {
public:
    /**@~english
     * Allocates and initializes a WebView.
     * @~chinese 
     * 分配和初始化一个WebView。
     */
    static WebView *create();

    /**@~english
     * Set javascript interface scheme.
     *
     * @~chinese 
     * 设置javascript接口scheme。
     * 
     * @see WebView::setOnJSCallback()
     */
    void setJavascriptInterfaceScheme(const std::string &scheme);

    /**@~english
     * Sets the main page contents, MIME type, content encoding, and base URL.
     *
     * @~chinese 
     * 设置主页内容、MIME类型、内容编码和baseURL
     * 
     * @param data @~english The content for the main page.
     * @~chinese 主页面的内容。
     * @param MIMEType @~english The MIME type of the data.
     * @~chinese MIME类型的数据。
     * @param encoding @~english The encoding of the data.
     * @~chinese 数据的编码。
     * @param baseURL @~english The base URL for the content.
     * @~chinese baseURL
     */
    void loadData(const cocos2d::Data &data,
                  const std::string &MIMEType,
                  const std::string &encoding,
                  const std::string &baseURL);
    
    /**@~english
     * Sets the main page content and base URL.
     *
     * @~chinese 
     * 设置主页内容和baseURL。
     * 
     * @param string @~english The content for the main page.
     * @~chinese 主页面的内容。
     * @param baseURL @~english The base URL for the content.
     * @~chinese baseURL
     */
    void loadHTMLString(const std::string &string, const std::string &baseURL = "");

    /**@~english
     * Loads the given URL.
     *
     * @~chinese 
     * 加载给定URL的网页
     * 
     * @param url @~english Content URL.
     * @~chinese 一个URL字符串
     */
    void loadURL(const std::string &url);

    /**@~english
     * Loads the given fileName.
     *
     * @~chinese 
     * 加载指定的网页文件
     * 
     * @param fileName @~english WebPage fileName.
     * @~chinese 网页文件名
     */
    void loadFile(const std::string &fileName);

    /**@~english
     * Stops the current load.
     * @~chinese 
     * 停止当前页面的加载
     */
    void stopLoading();

    /**@~english
     * Reloads the current URL.
     * @~chinese 
     * 重新加载当前URL。
     */
    void reload();

    /**@~english
     * Gets whether this WebView has a back history item.
     *
     * @~chinese 
     * 判断当前WebView是否有回退历史记录
     * 
     * @return @~english WebView has a back history item.
     * @~chinese 如果WebView有回退历史记录，则返回True;否则返回false。
     */
    bool canGoBack();

    /**@~english
     * Gets whether this WebView has a forward history item.
     *
     * @~chinese 
     * 判断当前WebView是否有前进历史记录
     * 
     * @return @~english WebView has a forward history item.
     * @~chinese 如果WebView有前进历史记录，则返回True;否则返回false
     */
    bool canGoForward();

    /**@~english
     * Goes back in the history.
     * @~chinese 
     * 回退一个历史页面
     */
    void goBack();

    /**@~english
     * Goes forward in the history.
     * @~chinese 
     * 前进一个历史页面
     */
    void goForward();

    /**@~english
     * Evaluates JavaScript in the context of the currently displayed page.
     * @~chinese 
     * 在当前显示页面的上下文中环境中执行一段js脚本。
     */
    void evaluateJS(const std::string &js);

    /**@~english
     * Set WebView should support zooming. The default value is false.
     * @~chinese 
     * 设置WebView是否支持缩放。默认值是False
     */
    void setScalesPageToFit(const bool scalesPageToFit);
    
    /**@~english
     * Call before a web view begins loading.
     *
     * @~chinese 
     * 在WebView开始加载一个页面之前回调的函数
     * 
     * @param callback @~english The web view that is about to load new content.
     * @~chinese 一个回调函数，用来指定额外需要添加的内容。
     * @return @~english YES if the web view should begin loading content; otherwise, NO .
     * @~chinese 如果传True,则WebView应该开始加载内容;否则,传False.
     */
    void setOnShouldStartLoading(const std::function<bool(WebView *sender, const std::string &url)>& callback);
    
    /**@~english
     * A callback which will be called when a WebView event happens.
     * @~chinese 
     * 一个回调函数，它将在WebView事件发生的时候被调用。
     */
    typedef std::function<void(WebView *sender, const std::string &url)> ccWebViewCallback;

    /**@~english
     * Call after a web view finishes loading.
     *
     * @~chinese 
     * 设置WebView加载页面完成后调用的回调函。
     * 
     * @param callback @~english A @see ccWebViewCallback callback.
     * @~chinese 一个ccWebViewCallback回调
     */
    void setOnDidFinishLoading(const ccWebViewCallback& callback);
    
    /**@~english
     * Call if a web view failed to load content.
     *
     * @~chinese 
     * 设置WebView加载页面失败时会调用的回调函数。
     * 
     * @param callback @~english A @see ccWebViewCallback callback.
     * @~chinese 一个ccWebViewCallback回调
     */
    void setOnDidFailLoading(const ccWebViewCallback& callback);
    
    /**@~english
     * This callback called when load URL that start with javascript interface scheme.
     * @~chinese 
     * 这个回调仅在设置了javascript接口scheme的时候被调用。
     */
    void setOnJSCallback(const ccWebViewCallback& callback);
    
    /**@~english
     * Get the callback when WebView is about to start.
     * @~chinese 
     * 设置WebView开始加载页面的回调函数。
     */
    std::function<bool(WebView *sender, const std::string &url)> getOnShouldStartLoading()const;
    
    /**@~english
     * Get the callback when WebView has finished loading.
     * @~chinese 
     * 获取当前WebView已完成加载时调用的回调函数
     */
    ccWebViewCallback getOnDidFinishLoading()const;
    
    /**@~english
     * Get the callback when WebView has failed loading.
     * @~chinese 
     * 获取当前WebView加载失败时调用的回调函数
     */
    ccWebViewCallback getOnDidFailLoading()const;

    /**@~english
     *Get the Javascript callback.
     * @~chinese 
     * 获取Javascript回调函数。
     */
    ccWebViewCallback getOnJSCallback()const;

    virtual void draw(cocos2d::Renderer *renderer, cocos2d::Mat4 const &transform, uint32_t flags) override;

    /**@~english
     * Toggle visibility of WebView.
     * @~chinese 
     * 设置WebView的可见性。
     */
    virtual void setVisible(bool visible) override;
    
protected:
    virtual cocos2d::ui::Widget* createCloneInstance() override;
    virtual void copySpecialProperties(Widget* model) override;
    
    std::function<bool(WebView *sender, const std::string &url)> _onShouldStartLoading;
    
    ccWebViewCallback _onDidFinishLoading;
    
    ccWebViewCallback _onDidFailLoading;
   
    ccWebViewCallback _onJSCallback;

CC_CONSTRUCTOR_ACCESS:
    /**@~english
     * Default constructor.
     * @~chinese 
     * 默认构造函数。
     */
    WebView();
    
    /**@~english
     * Default destructor.
     * @~chinese 
     * 默认析构函数。
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
// end group
/// @}
#endif //__COCOS2D_UI_WEBVIEW_H
