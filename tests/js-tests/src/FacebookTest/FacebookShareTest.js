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

var buttons = {
    "Share link": "onShareLink",
    "Share open graph": "onShareOG",
    "Share photo": "onSharePhoto",
    "Link message": "onLinkMsg",
    "Open graph message": "onOGMsg",
    "Photo message": "onPhotoMsg",
    "App request": "onRequest"
};

var appRequestAction = {
    "Invites request": "onInviteRequest",
    "Target invite request": "onTargetInviteRequest",
    "specific lists of friends": "onSpecificListsFriends",
    "Sending gift request": "sendingGiftRequest",
    "Turn-based games": "onTurnBasedGamesRequest"
};
var shareLinkAction = {
    "share a simple link": "onShareSimpleLink",
    "share a Text link": "onShareTextInfoLink",
    "share a Picture link": "onSharePictureInfoLink",
    "share a media link": "onShareMediaSource"
};

var FacebookShareTest = FacebookTest.extend({
    _title: "Facebook SDK Sharing Test",
    _subtitle: "",
    _agentManager: null,
    _showTips: false,
    _secondMenu:null,
    ctor: function (title) {
        this._super(title);

        window.facebook = window.facebook || (window["plugin"] ? window["plugin"]["FacebookAgent"]["getInstance"]() : null);

        var menu = new cc.Menu();
        menu.setPosition(cc.p(0, 0));
        menu.width = winSize.width;
        menu.height = winSize.height;
        this.addChild(menu, 1);

        var top = 50;
        for (var action in buttons) {
            var label = new cc.LabelTTF(action, "Arial", 24);
            var item = new cc.MenuItemLabel(label, this[buttons[action]], this);
            item.setPosition(winSize.width * 1 / 3, winSize.height - top);
            menu.addChild(item);
            top += 50;
        }

        var logo = new cc.Sprite(s_html5_logo);
        logo.setPosition(winSize.width * 2 / 3, winSize.height / 2);
        this.addChild(logo);

        this._agentManager = window["plugin"].agentManager;

        this.tipsLabel = new cc.LabelTTF("", "Arial", 20);
        this.tipsLabel.setDimensions(cc.size(350, 0));
        this.addChild(this.tipsLabel, 100);
        this.tipsLabel.setPosition(cc.pAdd(cc.visibleRect.bottomRight, cc.p(-350 / 2 - 20, 150)));
        this.tipsLabel.visible = false;

        this._secondMenu = new cc.Menu();
        this._secondMenu.setPosition(cc.p(340, 0));
        this._secondMenu.width = winSize.width / 2;
        this._secondMenu.height = winSize.height;
        this.addChild(this._secondMenu, 2);
    },
    showSecondMenu: function (buttonActions) {
        this._secondMenu.removeAllChildren();
        var top = 50;
        for (var action in buttonActions) {
            var label = new cc.LabelTTF(action, "Arial", 24);
            var item = new cc.MenuItemLabel(label, this[buttonActions[action]], this);
            item.setPosition(winSize.width * 1 / 3, winSize.height - top);
            this._secondMenu.addChild(item);
            top += 50;
        }
    },
    onShareLink: function () {
        this.showSecondMenu(shareLinkAction);
    },

    onShareSimpleLink: function (){
        var map = {
            "dialog": "shareLink",
            "link": "http://www.cocos2d-x.org"
        };
        var self = this;
        if(facebook.canPresentDialog(map)){
            facebook.dialog(map,function(errorCode,msg){
                self.showDisableTips(JSON.stringify(msg));
            });
        }else{
            map["dialog"] = "feedDialog";
            facebook.dialog(map,function(errorCode,msg){
                self.showDisableTips(JSON.stringify(msg));
            });
        }
    },
    onShareTextInfoLink: function (){
        var map = {
            "dialog": "shareLink",
            "name": "Cocos2d-JS web site",
            "caption": "Cocos2d-JS caption",
            "description":"Cocos2d-JS description",
            "link": "http://www.cocos2d-x.org"
        };
        var self = this;
        if(facebook.canPresentDialog(map)){
            facebook.dialog(map,function(errorCode,msg){
                self.showDisableTips(JSON.stringify(msg));
            });
        }else{
            map["dialog"] = "feedDialog";
            facebook.dialog(map,function(errorCode,msg){
                self.showDisableTips(JSON.stringify(msg));
            });
        }
    },
    onSharePictureInfoLink: function (){
        var map = {
            "dialog": "shareLink",
            "name": "Cocos2d-JS web site",
            "caption": "Cocos2d-JS caption",
            "description":"Cocos2d-JS description",
            "to": "100008180737293,100006738453912",
            "picture": "http://files.cocos2d-x.org/images/orgsite/logo.png",
            "link": "http://www.cocos2d-x.org"
        };
        var self = this;
        if(facebook.canPresentDialog(map)){
            facebook.dialog(map,function(errorCode,msg){
                self.showDisableTips(JSON.stringify(msg));
            });
        }else{
            map["dialog"] = "feedDialog";
            facebook.dialog(map,function(errorCode,msg){
                self.showDisableTips(JSON.stringify(msg));
            });
        }
    },
    onShareMediaSource: function () {
        var map = {
            "dialog": "shareLink",
            "name": "Cocos2d-JS web site",
            "caption": "Cocos2d-JS caption",
            "description":"Cocos2d-JS description",
            "link": "http://www.youtube.com/watch?v=uMnHAHpMtDc&feature=youtu.be"
        };

        var self = this;
        // only support in feed dialog
        facebook.dialog(map,function(errorCode,msg){
            self.showDisableTips(JSON.stringify(msg));
        });
    },
    showDisableTips: function (msg) {
        if (!this._showTips) {
            this._showTips = true;
            if (msg) {
                var preMsg = this.tipsLabel.getString();
                this.tipsLabel.setString(msg);
            }
            var anim = cc.sequence(
                cc.fadeIn(0.2),
                cc.delayTime(3),
                cc.fadeOut(0.2),
                cc.callFunc(function () {
                    this._showTips = false;
                    this.tipsLabel.visible = false;
                    if (preMsg)
                        this.tipsLabel.setString(preMsg);
                }, this)
            );
            this.tipsLabel.visible = true;
            this.tipsLabel.runAction(anim);
        }
    },
    onShareOG: function () {
        var map = {
            "dialog": "shareOpenGraph",
            "action_type": "cocostestmyfc:share",
            "preview_property_name": "cocos_document",
            "title": "Cocos2d-JS Game Engine",
            "image": "http://files.cocos2d-x.org/images/orgsite/logo.png",
            "url": "http://cocos2d-x.org/docs/manual/framework/html5/en",
            "description": "cocos document"
        };
        var self = this;
        if(facebook.canPresentDialog(map)){
            facebook.dialog(map, function (resultcode, msg) {
                self.showDisableTips(JSON.stringify(msg));
            });
        }else{
            self.showDisableTips("Can't open dialog for shareOpenGraph");
        }


    },

    onSharePhoto: function () {
        var self = this;
        if (!cc.sys.isNative) {
            self.showDisableTips("This share function is not available on web version of Facebook plugin");
            return;
        }
        var img = self.screenshot("facebookshare.jpg");

        var delay = cc.delayTime(2);
        var share = cc.callFunc(function () {
            var map = {
                "dialog": "sharePhoto",
                "photo": img
            };

            if(facebook.canPresentDialog(map)){
                facebook.dialog(map, function (resultcode, msg) {
                    self.showDisableTips(JSON.stringify(msg));
                });
            }else{
                self.showDisableTips("Can't open dialog for sharePhoto");
            }
        });
        var seq = cc.sequence(delay, share);
        this.runAction(seq);

    },

    onLinkMsg: function () {
        var map = {
            "dialog": "messageLink",
            "description": "Cocos2d-JS is a great game engine",
            "title": "Cocos2d-JS",
            "link": "http://www.cocos2d-x.org",
            "imageUrl": "http://files.cocos2d-x.org/images/orgsite/logo.png"
        };
        if(facebook.canPresentDialog(map)){
            var self = this;
            facebook.dialog(map, function (resultcode, msg) {
                self.showDisableTips(JSON.stringify(msg));
            });
        }else{
            this.showDisableTips("Can't open dialog for messageLink");
        }
    },

    onOGMsg: function () {
        if (!cc.sys.isNative) {
            this.showDisableTips("This share function is not available on web version of Facebook plugin");
            return;
        }
        var map = {
            "dialog": "messageOpenGraph",
            "action_type": "cocostestmyfc:share",
            "preview_property_name": "cocos_document",
            "title": "Cocos2d-JS Game Engine",
            "image": "http://files.cocos2d-x.org/images/orgsite/logo.png",
            "url": "http://cocos2d-x.org/docs/manual/framework/html5/en",
            "description": "cocos document"
        };
        if(facebook.canPresentDialog(map)){
            var self = this;
            facebook.dialog(map, function (resultcode, msg) {
                self.showDisableTips(JSON.stringify(msg));
            });
        }else{
            this.showDisableTips("Can't open dialog for messageOpenGraph");
        }
    },

    onPhotoMsg: function () {
        var self = this;
        if (!cc.sys.isNative) {
            self.showDisableTips("This share function is not available on web version of Facebook plugin");
            return;
        }
        var img = this.screenshot("facebookmessage.jpg");

        var delay = cc.delayTime(2);
        var share = cc.callFunc(function () {
            var map = {
                "dialog": "messagePhoto",
                "photo": img
            };
            if(facebook.canPresentDialog(map)){
                facebook.dialog(map, function (resultcode, msg) {
                    self.showDisableTips(JSON.stringify(msg));
                });
            }else{
                self.showDisableTips("Can't open dialog for messagePhoto");
            }
        });
        var seq = cc.sequence(delay, share);
        this.runAction(seq);
    },

    onRequest: function () {
        this.showSecondMenu(appRequestAction);
    },

    onInviteRequest: function () {
        var map = {
            "message": "Cocos2d-JS is a great game engine",
            "title": "Cocos2d-JS title"
        };
        var self = this;
        facebook.appRequest(map, function (resultcode, msg) {
            self.showDisableTips(JSON.stringify(msg));
        });
    },
    onTargetInviteRequest: function () {
        var map = {
            "message": "Cocos2d-JS is a great game engine",
            "title": "Cocos2d-JS title",
            "to": "100006738453912, 10204182777160522"
        };
        var self = this;
        // android only web view support to
        facebook.appRequest(map, function (resultcode, msg) {
            self.showDisableTips(JSON.stringify(msg));
        });
    },
    onSpecificListsFriends: function () {
        var map = {
            "message": "Cocos2d-JS is a great game engine",
            "title": "Cocos2d-JS title",
            "filters": '[{"name":"company", "user_ids":["100006738453912","10204182777160522"]}]'
        };
        var self = this;
        // android not support filters
        facebook.appRequest(map, function (resultcode, msg) {
            self.showDisableTips(JSON.stringify(msg));
        });
    },
    sendingGiftRequest: function () {
        var map = {
            "message": "Cocos2d-JS is a great game engine",
            "to": "100006738453912",
            "action_type":"send",
            "object_id":"649590015121283"// 191181717736427   1426774790893461
        };
        var self = this;
        // android not support action_type
        facebook.appRequest(map, function (resultcode, msg) {
            self.showDisableTips(JSON.stringify(msg));
        });
    },
    onTurnBasedGamesRequest: function () {
        var map = {
            "message": "Cocos2d-JS is a great game engine",
            "title": "Cocos2d-JS title",
            "to": "100006738453912",
            "action_type":"turn"
        };
        var self = this;
        // android not support action_type
        facebook.appRequest(map, function (resultcode, msg) {
            self.showDisableTips(JSON.stringify(msg));
        });
    },

    screenshot: function (fileName) {
        var tex = new cc.RenderTexture(winSize.width, winSize.height, cc.Texture2D.PIXEL_FORMAT_RGBA8888);
        tex.setPosition(cc.p(winSize.width / 2, winSize.height / 2));
        tex.begin();
        cc.director.getRunningScene().visit();
        tex.end();

        var imgPath = jsb.fileUtils.getWritablePath();
        if (imgPath.length == 0) {
            return;
        }
        var result = tex.saveToFile(fileName, cc.IMAGE_FORMAT_JPEG);
        if (result) {
            imgPath += fileName;
            cc.log("save image:" + imgPath);
            return imgPath;
        }
        return "";
    }
});