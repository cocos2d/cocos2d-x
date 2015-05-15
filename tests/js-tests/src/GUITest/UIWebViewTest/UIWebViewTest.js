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