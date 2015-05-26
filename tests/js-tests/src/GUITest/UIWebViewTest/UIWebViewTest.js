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

//2015-01-14
var UIWebViewTest = UIScene.extend({
    _webView: null,
    init: function () {
        if (this._super()) {
            var self = this;
            var winSize = cc.size(480, 320);

            if (!((cc.sys.os == cc.sys.OS_ANDROID || cc.sys.os == cc.sys.OS_IOS || cc.sys.os == cc.sys.OS_WINDOWS) && cc.sys.isNative))
            {
                var showErrorLabel = new cc.LabelTTF("Only run in android, ios and windows ", "Arial", 20);
                showErrorLabel.setPosition(cc.p(winSize.width / 2 , winSize.height / 2));
                this._mainNode.addChild(showErrorLabel);
                return;
            }

            this._webView = new ccui.WebView();
            this._webView.setAnchorPoint(cc.p(0.5, 0.5));
            this._webView.setPosition(cc.p(winSize.width / 2, winSize.height / 2));
            this._webView.setContentSize(cc.size(winSize.width * 0.5, winSize.height * 0.5));
            this._webView.loadURL("http://www.baidu.com");
            this._webView.setScalesPageToFit(true);

            this._webView.setOnShouldStartLoading(this.onWebViewShouldStartLoading);
            this._webView.setOnDidFinishLoading(this.onWebViewDidFinishLoading);
            this._webView.setOnDidFailLoading(this.onWebViewDidFailLoading);

            this._mainNode.addChild(this._webView);

            var urlTextField = new ccui.TextField("Input a URL here", "Arial", 20);
            urlTextField.setPlaceHolderColor(cc.color(255, 0, 0));
            urlTextField.setPosition(cc.p(winSize.width / 2 - 80, winSize.height / 2 +
            this._webView.getContentSize().height / 2 + urlTextField.getContentSize().height / 2 + 10));
            this._mainNode.addChild(urlTextField);

            var textFieldPos = urlTextField.getPosition();

            var httpLabel = new cc.LabelTTF("http:// ", "Arial", 20);
            httpLabel.setFontFillColor(cc.color(0, 255, 0));
            httpLabel.setAnchorPoint(cc.p(1.0, 0.5));
            httpLabel.setPosition(cc.p(textFieldPos.x - urlTextField.getContentSize().width / 2, textFieldPos.y));
            this._mainNode.addChild(httpLabel);


            var resetBtn = new ccui.Button("res/cocosui/animationbuttonnormal.png",
                "res/cocosui/animationbuttonpressed.png");
            resetBtn.setTitleText("Visit URL");
            resetBtn.setPosition(cc.p(winSize.width / 2 + 50, winSize.height / 2 + this._webView.getContentSize().height / 2 +
            resetBtn.getContentSize().height / 2 + 10));
            resetBtn.addClickEventListener(function () {
                if (urlTextField.getString().length != 0) {
                    self._webView.loadURL("http://" + urlTextField.getString());
                }
            });
            this._mainNode.addChild(resetBtn);

            var reloadBtn = new ccui.Button("res/cocosui/animationbuttonnormal.png",
                "res/cocosui/animationbuttonpressed.png");
            reloadBtn.setTitleText("Reload");
            reloadBtn.setPosition(cc.p(winSize.width / 2 + this._webView.getContentSize().width / 2 +
                                    reloadBtn.getContentSize().width / 2 + 10, winSize.height / 2 + 50));
            reloadBtn.addClickEventListener(function () {
                self._webView.reload();
            });
            this._mainNode.addChild(reloadBtn);

            var forwardBtn = new ccui.Button("res/cocosui/animationbuttonnormal.png",
                "res/cocosui/animationbuttonpressed.png");
            forwardBtn.setTitleText("Forward");
            forwardBtn.setPosition(cc.p(winSize.width / 2 + this._webView.getContentSize().width / 2 +
                                    forwardBtn.getContentSize().width / 2 + 10, winSize.height / 2));
            forwardBtn.addClickEventListener(function () {
                self._webView.goForward();
            });
            this._mainNode.addChild(forwardBtn);

            var backBtn = new ccui.Button("res/cocosui/animationbuttonnormal.png",
                "res/cocosui/animationbuttonpressed.png");
            backBtn.setTitleText("Back");
            backBtn.setPosition(cc.p(winSize.width / 2 + this._webView.getContentSize().width / 2 +
                                backBtn.getContentSize().width / 2 + 10, winSize.height / 2 - 50));
            backBtn.addClickEventListener(function () {
                self._webView.goBack();
            });
            this._mainNode.addChild(backBtn);


            var loadFileBtn = new ccui.Button("res/cocosui/animationbuttonnormal.png",
                "res/cocosui/animationbuttonpressed.png");
            loadFileBtn.setTitleText("Load FILE");
            loadFileBtn.setPosition(cc.p(winSize.width / 2 - this._webView.getContentSize().width / 2 -
                                    loadFileBtn.getContentSize().width / 2 - 10, winSize.height / 2 - 50));
            loadFileBtn.addClickEventListener(function () {
                self._webView.loadFile("res/cocosui/Test.html");
            });
            this._mainNode.addChild(loadFileBtn);

            var loadHTMLBtn = new ccui.Button("res/cocosui/animationbuttonnormal.png",
                "res/cocosui/animationbuttonpressed.png");
            loadHTMLBtn.setTitleText("Load Data");
            loadHTMLBtn.setPosition(cc.p(winSize.width / 2 - this._webView.getContentSize().width / 2 -
                                    loadHTMLBtn.getContentSize().width / 2 - 10, winSize.height / 2));
            loadHTMLBtn.addClickEventListener(function () {
                self._webView.loadHTMLString("<body style=\"font-size:50px;\">Hello World <img src=\"Icon.png\"/> </body>", "Images/");
            });
            this._mainNode.addChild(loadHTMLBtn);

            var evalJsBtn = new ccui.Button("res/cocosui/animationbuttonnormal.png",
                "res/cocosui/animationbuttonpressed.png");
            evalJsBtn.setTitleText("Evaluate JS");
            evalJsBtn.setPosition(cc.p(winSize.width / 2 - this._webView.getContentSize().width / 2 -
                                    evalJsBtn.getContentSize().width / 2 - 10, winSize.height / 2 + 50));
            evalJsBtn.addClickEventListener(function () {
                self._webView.evaluateJS("alert(\"hello\")");
            });
            this._mainNode.addChild(evalJsBtn);

            return true;
        }
    },
    onWebViewShouldStartLoading: function (sender, url) {
        cc.log("onWebViewShouldStartLoading, url is " + url);
    },
    onWebViewDidFinishLoading: function (sender, url) {
        cc.log("onWebViewDidFinishLoading, url is " + url);
    },
    onWebViewDidFailLoading: function (sender, url) {
        cc.log("onWebViewDidFailLoading, url is " + url);
    }
});
var UIWebViewTest = UIScene.extend({

    onEnter: function(){
        UIScene.prototype.onEnter.call(this);

        var webView = new ccui.WebView("src/GUITest/UIWebViewTest/webview.html");
        webView.setContentSize(320, 240);
        webView.setPosition(800/2, 450/2);
        webView.setScale(0.5);
        window.webView = webView;
        this.addChild(webView);

        var cb = function(){
            cc.log("loaded");
        };
        webView.addEventListener("load", cb);

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
                cc.log("goBack!");
                webView.goBack();
            }},
            { name: "goForward", func: function(){
                cc.log("goForward!");
                webView.goForward();
            }},
            { name: "evaluateJS", func: function(){
                cc.log("evaluateJS!");
                var code = "document.getElementById('test').innerHTML = 'evaluateJS!'";
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