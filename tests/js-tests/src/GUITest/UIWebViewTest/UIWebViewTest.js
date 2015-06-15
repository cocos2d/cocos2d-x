/****************************************************************************
 Copyright (c) 2011-2012 cocos2d-x.org
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


var UIWebViewTest = UIScene.extend({

    onEnter: function(){
        UIScene.prototype.onEnter.call(this);

        var webView = new ccui.WebView("http://www.baidu.com");
        webView.setContentSize(320, 240);
        webView.setPosition(800/2, 450/2);
        webView.setScale(0.5);
        webView.setScalesPageToFit(true);
        window.webView = webView;
        this.addChild(webView);


        webView.setEventListener(ccui.WebView.EventType.LOADED, function(sender, url){
            cc.log("webview LOADED url:" + url);
        });
        webView.setEventListener(ccui.WebView.EventType.LOADING, function(sender, url){
            cc.log("webview LOADING url:" + url);
        });
        webView.setEventListener(ccui.WebView.EventType.ERROR, function(sender, url){
            cc.log("webview ERROR url:" + url);
        });

        var list = [
            { name: "loadURL", func: function(){
                cc.log("loadURL!");
                webView.loadURL("src/GUITest/UIWebViewTest/webview2.html");
            }},
            { name: "reload", func: function(){
                cc.log("reload!");
                webView.reload();
            }},
            { name: "goBack", func: function(){
                if (webView.canGoBack())
                {
                    cc.log("goBack!");
                    webView.goBack();    
                }
                else
                {
                    cc.log("can not goBack!");
                }
            }},
            { name: "goForward", func: function(){
                if (webView.canGoForward())
                {
                    cc.log("goForward!");
                    webView.goForward();
                }
                else
                {
                    cc.log("can not goForward!");
                }
            }},
            { name: "evaluateJS", func: function(){
                cc.log("evaluateJS!");
                var code = "alert('evaluateJS!')";
                webView.evaluateJS(code);
            }},
            { name: "Scale", func: function(){
                var scale = ((Math.random() * 0.5 + 0.2) * 100 | 0) / 100;
                cc.log("setScale(%f)!", scale);
                webView.setScale(scale);
            }},
            { name: "AnchorPoint 0 / 1", func: function(){
                var anp = webView.getAnchorPoint();
                if(anp.x === 1)
                    webView.setAnchorPoint(0, 0);
                else
                    webView.setAnchorPoint(1, 1);
            }},
            { name: "AnchorPoint 0.5", func: function(){
                webView.setAnchorPoint(0.5, 0.5);
            }}
        ];

        var layer = this;
        list.forEach(function(item, i){
            var but = new ccui.Button();
            but.setPosition( 140 + (i / 5 | 0) * 500, 300 - (i % 5) * 35);
            but.setTitleText(item.name);
            but.setZoomScale(0.3);
            but.setPressedActionEnabled(true);
            but.addClickEventListener(item.func);
            layer.addChild(but);
        });

    }

});