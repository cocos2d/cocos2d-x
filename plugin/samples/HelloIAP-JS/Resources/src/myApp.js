/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org
 Copyright (c) 2008-2010 Ricardo Quesada
 Copyright (c) 2011      Zynga Inc.

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

eNoneMode = 0;
eAlipay = 1;
eND91 = 2;


var __iapInstance = null;

var MyPurchase = cc.Class.extend({
    _pAlipay: null,
    _pRetListener: null,
    _pNd91: null,

    loadIAPPlugin: function() {

        // init alipay plugin
        this._pAlipay = plugin.PluginManager.getInstance().loadPlugin("IAPAlipay");
        var pAlipayInfo = {};

        if (Object.keys(pAlipayInfo).length == 0)
        {
            cc.log("Alipay Warning: Developer info is empty. PLZ fill your alipay info to pAlipayInfo)");
        }

        this._pAlipay.setDebugMode(true);
        this._pAlipay.configDeveloperInfo(pAlipayInfo);
        this._pAlipay.setResultListener(this);

        var pNdInfo = {};
        pNdInfo["Nd91AppId"] = "100010";
        pNdInfo["Nd91AppKey"] = "C28454605B9312157C2F76F27A9BCA2349434E546A6E9C75";
        pNdInfo["Nd91Orientation"] = "landscape";
        if (Object.keys(pNdInfo).length == 0) {
            cc.log("Nd91 Warning: Developer info is empty. PLZ fill your alipay info to pAlipayInfo)");
        }
        this._pNd91 = plugin.PluginManager.getInstance().loadPlugin("IAPNd91");
        this._pNd91.setDebugMode(true);
        this._pNd91.configDeveloperInfo(pNdInfo);
        this._pNd91.setResultListener(this);
    },

    unloadIAPPlugin: function() {
        if (this._pAlipay)
        {
            plugin.PluginManager.getInstance().unloadPlugin("IAPAlipay");
            this._pAlipay = null;
        }

        if (this._pNd91)
        {
            plugin.PluginManager.getInstance().unloadPlugin("IAPNd91");
            this._pNd91 = null;
        }
    },

    payByMode:function(info, mode) {
        var pIAP = null;
        switch(mode)
        {
        case eAlipay:
            pIAP = this._pAlipay;
            break;
        case eND91:
            pIAP = this._pNd91;
            break;
        default:
            break;
        }

        if (pIAP) {
            pIAP.payForProduct(info);
        }
    },

    onPayResult: function(ret, msg, productInfo) {
        cc.log("---------onPayResult callback begin-----------------");
        cc.log("onPayResult="+ ret + ";msg=" +msg + ";productinfo="+productInfo);
        cc.log("---------onPayResult callback end-----------------");
    },
});

MyPurchase.getInstance = function() {
    if (__iapInstance == null) {
        __iapInstance = new MyPurchase();
    }
    return __iapInstance;
}

TAG_PAY_BY_ALIPAY = 100;
TAG_PAY_BY_ND91 = 101;

var _EventMenuItem = [
    {id: "BtnAlipay.png", tag: TAG_PAY_BY_ALIPAY},
    {id: "BtnND91.png", tag: TAG_PAY_BY_ND91}
];

var IAPTestLayer = cc.Layer.extend({

    ctor:function() {
        this._super();
        cc.associateWithNative( this, cc.Layer );
    },

    menuCloseCallback: function() {
        cc.log("menuCloseCallback");
        __jsc__.garbageCollect();
    },

    eventMenuCallback: function(pSender) {
        var pMenuItem = pSender;
        var pInfo = {};
        var mode = 0;
        
        switch (pMenuItem.getTag())
        {
            case TAG_PAY_BY_ALIPAY:
                pInfo["productName"] = "100金币";
                pInfo["productPrice"] = "0.1";
                pInfo["productDesc"] = "100个金灿灿的游戏币哦";
                mode = eAlipay;
                break;
            case TAG_PAY_BY_ND91:
                pInfo["productName"] = "100金币";
                pInfo["productPrice"] = "0.01";
                pInfo["productDesc"] = "100个金灿灿的游戏币哦";
                pInfo["Nd91ProductId"] = "685994";
                mode = eND91;
                break;
            default:
                break;
        }
        cc.log("eventMenuCallback, item tag = "+pMenuItem.getTag());
        MyPurchase.getInstance().payByMode(pInfo, mode);
    },

    reloadPluginMenuCallback: function() {
        MyPurchase.getInstance().unloadIAPPlugin();
        MyPurchase.getInstance().loadIAPPlugin();
        cc.log("reloadPluginMenuCallback");
    },

    onEnter:function () {
        this._super();
        MyPurchase.getInstance().loadIAPPlugin();

        var director = cc.Director.getInstance();
        var size = director.getWinSize();
        
        var background = cc.Sprite.create("res/background.png");
        background.setPosition(cc.p(size.width / 2, size.height / 2));
        this.addChild(background);

        var posBR = cc.p(director.getVisibleOrigin().x + director.getVisibleSize().width, director.getVisibleOrigin().y);
        var posTL = cc.p(director.getVisibleOrigin().x, director.getVisibleOrigin().y + director.getVisibleSize().height);
        
        var pCloseItem = cc.MenuItemImage.create(
                              "res/CloseNormal.png",
                              "res/CloseSelected.png",
                              this.menuCloseCallback,
                              this );
        pCloseItem.setPosition( cc.p(posBR.x - 20, posBR.y + 20) );
        
        // create menu, it's an autorelease object
        var pMenu = cc.Menu.create(pCloseItem);
        pMenu.setPosition( cc.p(0, 0) );
        this.addChild(pMenu, 1);
        
        var posStep = cc.p(220, -150);
        var beginPos = cc.pAdd(posTL, cc.pMult(posStep, 0.5));
        var line = 0;
        var row = 0;
        for (var i = 0; i < _EventMenuItem.length; i++) {
            var pMenuItem = cc.MenuItemImage.create(_EventMenuItem[i].id, _EventMenuItem[i].id,
                                                this.eventMenuCallback, this);

            pMenu.addChild(pMenuItem, 0, _EventMenuItem[i].tag);
            
            var pos = cc.pAdd(beginPos, cc.p(posStep.x * row, posStep.y * line));
            var itemSize = pMenuItem.getContentSize();
            if ((pos.x + itemSize.width / 2) > posBR.x)
            {
                line += 1;
                row = 0;
                pos = cc.pAdd(beginPos, cc.p(posStep.x * row, posStep.y * line));
            }
            row += 1;
            pMenuItem.setPosition(pos);
        }
        
        var label = cc.LabelTTF.create("reload all plugins", "Arial", 24);
        var pMenuItem = cc.MenuItemLabel.create(label, this.reloadPluginMenuCallback, this);
        pMenuItem.setAnchorPoint(cc.p(0.5, 0));
        pMenu.addChild(pMenuItem, 0);
        pMenuItem.setPosition( cc.p(size.width / 2, 0));
    },
});

var MyScene = cc.Scene.extend({
    ctor:function() {
        this._super();
        cc.associateWithNative( this, cc.Scene );
    },

    onEnter:function () {
        this._super();
        var layer = new IAPTestLayer();
        layer.init();
        this.addChild(layer);
    }
});
