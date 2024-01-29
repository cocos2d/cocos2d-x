/****************************************************************************
 Copyright (c) 2011-2012 cocos2d-x.org
 Copyright (c) 2013-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

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


var UIWebViewTest = UIMainLayer.extend({

    onEnter: function(){
        UIMainLayer.prototype.onEnter.call(this);

        var webView = new ccui.WebView("http://www.baidu.com");
        webView.setContentSize(320, 240);
        webView.setPosition(800/2, 450/2);
        webView.setScale(0.5);
        webView.setScalesPageToFit(true);
        window.webView = webView;
        this.addChild(webView);

        var widgetSize = this._widget.getContentSize();
        var playState = this._topDisplayLabel;
        playState.setString("Press buttons to start");
        playState.y = widgetSize.height / 2.0 + playState.height * 1.5;
        this._bottomDisplayLabel.setString("");

        var list = [
            { name: "loadURL", func: function(){
                playState.setString("loadURL!");
                webView.loadURL("src/GUITest/UIWebViewTest/webview2.html");
            }},
            { name: "Reload", func: function(){
                playState.setString("reload!");
                webView.reload();
            }},
            { name: "goBack", func: function(){
                if (webView.canGoBack())
                {
                    playState.setString("goBack!");
                    webView.goBack();    
                }
                else
                {
                    playState.setString("can not goBack!");
                }
            }},
            { name: "goForward", func: function(){
                if (webView.canGoForward()) {
                    playState.setString("goForward!");
                    webView.goForward();
                }
                else {
                    playState.setString("can not goForward!");
                }
            }},
            { name: "EvaluateJS", func: function(){
                playState.setString("evaluateJS!");
                var code = "alert('evaluateJS!')";
                webView.evaluateJS(code);
            }},
            { name: "Scale", func: function(){
                var scale = ((Math.random() * 0.5 + 0.2) * 100 | 0) / 100;
                playState.setString("setScale(" + scale + ")");
                webView.setScale(scale);
            }},
            { name: "setAnchorPoint", func: function(){
                var anpX = webView.getAnchorPoint().x === 1 ? 0: webView.getAnchorPoint().x+ 0.5;
                var anpY = webView.getAnchorPoint().y === 1 ? 0: webView.getAnchorPoint().y+ 0.5;
                webView.setAnchorPoint(anpX, anpY);
            }}
        ];

        var layer = this;
        list.forEach(function(item, i){
            var button = new ccui.Button();
            i+1 !== list.length ? button.setScale(1.3) : button.setScale(1);
            button.setPosition( 140 + (i / 4 | 0) * 530, 320 - (i % 4) * 50);
            button.setTitleText(item.name);
            button.setTitleColor(cc.color.YELLOW);
            button.setZoomScale(0.3);
            button.setPressedActionEnabled(true);
            button.addClickEventListener(item.func);
            layer.addChild(button);
        });

    }

});
