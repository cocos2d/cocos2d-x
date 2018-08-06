/****************************************************************************
 Copyright (c) 2014-2016 Chukong Technologies Inc.
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

var button_share = {
    "login": "loginClick",
    "loginWithPermission": "loginWithPermissionClick",
    "logout": "logoutClick",
    "getUid": "getUidClick",
    "getToken": "getTokenClick",
    "getPermissions": "getPermissionClick",
    "request API": "requestClick",
    "activateApp": "activateAppClick",
    "logEvent": "LogEventClick",
    "logPurchase": "LogPurchaseClick",
    "payment": "paymentClick"
};
var FacebookUserTest = FacebookTest.extend({
    _title: "Facebook SDK User Test",
    _subtitle: "",
    _agentManager: null,
    _isLogin: false,
    ctor: function (title) {
        this._super(title);

        window.facebook = window.facebook || (window["plugin"] ? window["plugin"]["FacebookAgent"]["getInstance"]() : null);

        var menu = cc.Menu.create();
        for (var action in button_share) {
            var label = new cc.LabelTTF(action, "Arial", 22);
            var item = new cc.MenuItemLabel(label, this[button_share[action]], this);
            menu.addChild(item);
        }
        menu.alignItemsVerticallyWithPadding(8);
        menu.setPosition(cc.pAdd(cc.visibleRect.left, cc.p(+180, 0)));
        this.addChild(menu);


        this.result = new cc.LabelTTF("You can see the result at this label", "Arial", 22);
        this.result.setPosition(cc.pAdd(cc.visibleRect.right, cc.p(-this.result.width / 2 - 30, 0)));
        this.result.boundingWidth = this.result.width;
        this.addChild(this.result, 1);
    },
    activateAppClick: function () {
        if (cc.sys.isNative|| facebook_is_canvas) {
            facebook.activateApp();
            this.result.setString("activateApp is invoked");
        }
        else {
            this.result.setString("activateApp is only available for Facebook Canvas App");
        }
    },
    LogEventClick: function () {
        if (cc.sys.isNative || facebook_is_canvas) {
            var parameters = {};
            var floatVal = 888.888;
            parameters[window["plugin"].FacebookAgent.AppEventParam.SUCCESS] = window["plugin"].FacebookAgent.AppEventParamValue.VALUE_YES;
    //        facebook.logEvent(plugin.FacebookAgent.AppEvent.COMPLETED_TUTORIAL);
            facebook.logEvent(window["plugin"].FacebookAgent.AppEvent.COMPLETED_TUTORIAL, floatVal);
            facebook.logEvent(window["plugin"].FacebookAgent.AppEvent.COMPLETED_TUTORIAL, parameters);
            facebook.logEvent(window["plugin"].FacebookAgent.AppEvent.COMPLETED_TUTORIAL, floatVal, parameters);
            this.result.setString("logEvent is invoked");
        }
        else {
            this.result.setString("LogEvent is only available for Facebook Canvas App");
        }
    },
    loginClick: function (sender) {
        var self = this;

        if (facebook.isLoggedIn()) {
            self.result.setString("logged in");
        }
        else {
            facebook.login(function (type, msg) {
                self.result.setString("type is " + type + " msg is " + JSON.stringify(msg));
            });
        }
    },
    logoutClick: function (sender) {
        var self = this;
        facebook.logout(function (type, msg) {
            self.result.setString(JSON.stringify(msg));
        });
    },
    getUidClick: function (sender) {
        var self = this;

        if (facebook.isLoggedIn()) {
            self.result.setString(facebook.getUserID());
        }
        else {
            self.result.setString("User haven't been logged in");
        }
    },
    getTokenClick: function (sender) {
        var self = this;

        if (facebook.isLoggedIn()) {
            self.result.setString(facebook.getAccessToken());
        }
        else {
            self.result.setString("User haven't been logged in");
        }
    },

    loginWithPermissionClick: function (sender) {
        var self = this;
        var permissions = ["create_event", "create_note", "manage_pages", "publish_actions"];
        facebook.login(permissions, function (type, msg) {
            if (type == window["plugin"].FacebookAgent.CODE_SUCCEED) {
                self.result.setString(msg["permissions"]);
            }
        });
    },
    getPermissionClick: function (sender) {
        var self = this;
        facebook.api("/me/permissions", window["plugin"].FacebookAgent.HttpMethod.GET, {}, function (type, data) {
            if (type == window["plugin"].FacebookAgent.CODE_SUCCEED) {
                data = JSON.stringify(data);
                self.result.setString(data);
            }
            else {
                self.result.setString(JSON.stringify(data));
            }
        });
    },
    requestClick: function (sender) {
        var self = this;
        facebook.api("/me/photos", window["plugin"].FacebookAgent.HttpMethod.POST, {"url": "http://files.cocos2d-x.org/images/orgsite/logo.png"}, function (type, msg) {
            if (type == window["plugin"].FacebookAgent.CODE_SUCCEED) {
                self.result.setString("post_id: " + msg["post_id"]);
            }
        });
    },
    LogPurchaseClick: function (sender) {
        if (cc.sys.isNative || facebook_is_canvas) {
            var params = {};
            // All supported parameters are listed here
            params[window["plugin"].FacebookAgent.AppEventParam.CURRENCY] = "CNY";
            params[window["plugin"].FacebookAgent.AppEventParam.REGISTRATION_METHOD] = "Facebook";
            params[window["plugin"].FacebookAgent.AppEventParam.CONTENT_TYPE] = "game";
            params[window["plugin"].FacebookAgent.AppEventParam.CONTENT_ID] = "201410102342";
            params[window["plugin"].FacebookAgent.AppEventParam.SEARCH_STRING] = "cocos2djs";
            params[window["plugin"].FacebookAgent.AppEventParam.SUCCESS] = window["plugin"].FacebookAgent.AppEventParamValue.VALUE_YES;
            params[window["plugin"].FacebookAgent.AppEventParam.MAX_RATING_VALUE] = "10";
            params[window["plugin"].FacebookAgent.AppEventParam.PAYMENT_INFO_AVAILABLE] = window["plugin"].FacebookAgent.AppEventParamValue.VALUE_YES;
            params[window["plugin"].FacebookAgent.AppEventParam.NUM_ITEMS] = "99";
            params[window["plugin"].FacebookAgent.AppEventParam.LEVEL] = "10";
            params[window["plugin"].FacebookAgent.AppEventParam.DESCRIPTION] = "Cocos2d-JS";
            facebook.logPurchase(1.23, "CNY", params);
            this.result.setString("Purchase logged.");
        }
        else {
            this.result.setString("LogPurchase is only available for Facebook Canvas App");
        }
    },
    paymentClick: function () {
        if(facebook_is_canvas){
            var info = {
                product: 'https://www.cocos2d-x.org/demo/facebooktest/pay/item1.html'
            };

            var self = this;
            facebook.canvas.pay(info, function(code, response){
                if (code == window["plugin"].FacebookAgent.CODE_SUCCEED){
                    if (response['status'] === 'completed')
                        self.result.setString("Payment succeeded: " + response['amount'] + response['currency']);
                    else
                        self.result.setString("Payment failed: " + JSON.stringify(response['status']))
                } else {
                    self.result.setString("Request send failed, error #" + code + ": " + JSON.stringify(response));
                }
            });
        }else{
            this.result.setString("canvas.pay is only available for Facebook Canvas App");
        }
    }
});