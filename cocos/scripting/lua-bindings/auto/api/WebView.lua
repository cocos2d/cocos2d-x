
--------------------------------
-- @module WebView
-- @extend Widget
-- @parent_module ccexp

--------------------------------
-- Gets whether this WebView has a back history item.<br>
-- return WebView has a back history item.
-- @function [parent=#WebView] canGoBack 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- Sets the main page content and base URL.<br>
-- param string The content for the main page.<br>
-- param baseURL The base URL for the content.
-- @function [parent=#WebView] loadHTMLString 
-- @param self
-- @param #string string
-- @param #string baseURL
-- @return experimental::ui::WebView#experimental::ui::WebView self (return value: cc.experimental::ui::WebView)
        
--------------------------------
-- Goes forward in the history.
-- @function [parent=#WebView] goForward 
-- @param self
-- @return experimental::ui::WebView#experimental::ui::WebView self (return value: cc.experimental::ui::WebView)
        
--------------------------------
-- Goes back in the history.
-- @function [parent=#WebView] goBack 
-- @param self
-- @return experimental::ui::WebView#experimental::ui::WebView self (return value: cc.experimental::ui::WebView)
        
--------------------------------
-- Set WebView should support zooming. The default value is false.
-- @function [parent=#WebView] setScalesPageToFit 
-- @param self
-- @param #bool scalesPageToFit
-- @return experimental::ui::WebView#experimental::ui::WebView self (return value: cc.experimental::ui::WebView)
        
--------------------------------
-- Loads the given fileName.<br>
-- param fileName Content fileName.
-- @function [parent=#WebView] loadFile 
-- @param self
-- @param #string fileName
-- @return experimental::ui::WebView#experimental::ui::WebView self (return value: cc.experimental::ui::WebView)
        
--------------------------------
-- @overload self, string, bool         
-- @overload self, string         
-- @function [parent=#WebView] loadURL
-- @param self
-- @param #string url
-- @param #bool cleanCachedData
-- @return experimental::ui::WebView#experimental::ui::WebView self (return value: cc.experimental::ui::WebView)

--------------------------------
-- Set whether the webview bounces at end of scroll of WebView.
-- @function [parent=#WebView] setBounces 
-- @param self
-- @param #bool bounce
-- @return experimental::ui::WebView#experimental::ui::WebView self (return value: cc.experimental::ui::WebView)
        
--------------------------------
-- Evaluates JavaScript in the context of the currently displayed page.
-- @function [parent=#WebView] evaluateJS 
-- @param self
-- @param #string js
-- @return experimental::ui::WebView#experimental::ui::WebView self (return value: cc.experimental::ui::WebView)
        
--------------------------------
-- Get the Javascript callback.
-- @function [parent=#WebView] getOnJSCallback 
-- @param self
-- @return function#function ret (return value: function)
        
--------------------------------
-- Gets whether this WebView has a forward history item.<br>
-- return WebView has a forward history item.
-- @function [parent=#WebView] canGoForward 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- Stops the current load.
-- @function [parent=#WebView] stopLoading 
-- @param self
-- @return experimental::ui::WebView#experimental::ui::WebView self (return value: cc.experimental::ui::WebView)
        
--------------------------------
-- Reloads the current URL.
-- @function [parent=#WebView] reload 
-- @param self
-- @return experimental::ui::WebView#experimental::ui::WebView self (return value: cc.experimental::ui::WebView)
        
--------------------------------
-- Set javascript interface scheme.<br>
-- see WebView::setOnJSCallback()
-- @function [parent=#WebView] setJavascriptInterfaceScheme 
-- @param self
-- @param #string scheme
-- @return experimental::ui::WebView#experimental::ui::WebView self (return value: cc.experimental::ui::WebView)
        
--------------------------------
-- Allocates and initializes a WebView.
-- @function [parent=#WebView] create 
-- @param self
-- @return experimental::ui::WebView#experimental::ui::WebView ret (return value: cc.experimental::ui::WebView)
        
--------------------------------
-- 
-- @function [parent=#WebView] onEnter 
-- @param self
-- @return experimental::ui::WebView#experimental::ui::WebView self (return value: cc.experimental::ui::WebView)
        
--------------------------------
-- Toggle visibility of WebView.
-- @function [parent=#WebView] setVisible 
-- @param self
-- @param #bool visible
-- @return experimental::ui::WebView#experimental::ui::WebView self (return value: cc.experimental::ui::WebView)
        
--------------------------------
-- 
-- @function [parent=#WebView] onExit 
-- @param self
-- @return experimental::ui::WebView#experimental::ui::WebView self (return value: cc.experimental::ui::WebView)
        
--------------------------------
-- Default constructor.
-- @function [parent=#WebView] WebView 
-- @param self
-- @return experimental::ui::WebView#experimental::ui::WebView self (return value: cc.experimental::ui::WebView)
        
return nil
