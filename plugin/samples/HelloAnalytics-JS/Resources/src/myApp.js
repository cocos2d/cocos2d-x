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



var g_pAnalytics = null;
var s_strAppKey = "";
// The app key of flurry
var FLURRY_KEY_IOS      =    "KMGG7CD9WPK2TW4X9VR8";
var FLURRY_KEY_ANDROID  =    "SPKFH8KMPGHMMBWRBT5W";
var UMENG_KEY_IOS       =    "50d2b18c5270152187000097";
var UMENG_KEY_ANDROID   =    "";          // umeng key for android is setted in AndroidManifest.xml


plugin.onApplicationDidEnterBackground = function() {
    if (g_pAnalytics != null) {
        cc.log("plugin.onApplicationDidEnterBackground.");
        g_pAnalytics.stopSession();
    }
};


plugin.onApplicationWillEnterForeground = function() {
    if (g_pAnalytics != null) {
        cc.log("plugin.onApplicationWillEnterForeground.");
        g_pAnalytics.startSession(s_strAppKey);
    }
};

var loadAnalyticsPlugin = function() {
    var langType = cc.Application.getInstance().getCurrentLanguage();

    var umengKey  = "";
    var flurryKey = "";

    var targetDevice = cc.Application.getInstance().getTargetPlatform();
    if (targetDevice == cc.kTargetIphone || targetDevice == cc.kTargetIpad)
    {
        umengKey  = UMENG_KEY_IOS;
        flurryKey = FLURRY_KEY_IOS;
    }
    else if (targetDevice == cc.kTargetAndroid)
    {
        umengKey  = UMENG_KEY_ANDROID;
        flurryKey = FLURRY_KEY_ANDROID;
    }


    if (cc.LANGUAGE_CHINESE == langType)
    {
        g_pAnalytics = plugin.PluginManager.getInstance().loadPlugin("AnalyticsUmeng");
        s_strAppKey = umengKey;
    }
    else
    {
        g_pAnalytics = plugin.PluginManager.getInstance().loadPlugin("AnalyticsFlurry");
        s_strAppKey = flurryKey;
    }

    g_pAnalytics.setDebugMode(true);
    g_pAnalytics.startSession(s_strAppKey);
    g_pAnalytics.setCaptureUncaughtException(true);

    if (g_pAnalytics instanceof plugin.AnalyticsUmeng)
    {
        g_pAnalytics.updateOnlineConfig();
        g_pAnalytics.setDefaultReportPolicy(plugin.AnalyticsUmeng.UmengReportPolicy.REALTIME);
    }

    if (g_pAnalytics instanceof plugin.AnalyticsFlurry)
    {
        g_pAnalytics.setReportLocation(true);
        g_pAnalytics.logPageView();
        // const char* sdkVersion = pFlurry.getSDKVersion();
        g_pAnalytics.setVersionName("1.1");
        g_pAnalytics.setAge(20);
        g_pAnalytics.setGender(plugin.AnalyticsFlurry.Gender.MALE);
        g_pAnalytics.setUserId("123456");
        g_pAnalytics.setUseHttps(false);
    }
}


TAG_LOG_EVENT_ID = 0;
TAG_LOG_EVENT_ID_KV = 1;
TAG_LOG_ONLINE_CONFIG = 2;
TAG_LOG_EVENT_ID_DURATION = 3;
TAG_LOG_EVENT_BEGIN = 4;
TAG_LOG_EVENT_END = 5;
TAG_MAKE_ME_CRASH = 6;

var s_EventMenuItem = [
    {id: "OnlineConfig",     tag: TAG_LOG_ONLINE_CONFIG},
    {id: "LogEvent-eventId", tag:  TAG_LOG_EVENT_ID},
    {id: "LogEvent-eventId-kv", tag: TAG_LOG_EVENT_ID_KV},
    {id: "LogEvent-eventId-Duration", tag: TAG_LOG_EVENT_ID_DURATION},
    {id: "LogEvent-Begin", tag: TAG_LOG_EVENT_BEGIN},
    {id: "LogEvent-End", tag: TAG_LOG_EVENT_END},
    {id: "MakeMeCrash", tag: TAG_MAKE_ME_CRASH}
];

var HelloWorld = cc.Layer.extend({
    ctor:function() {
        this._super();
        cc.associateWithNative( this, cc.Layer );
    },

    onEnter: function() {
        this._super();
        var size = cc.Director.getInstance().getWinSize();

        /////////////////////////////
        // 2. add a menu item with "X" image, which is clicked to quit the program
        //    you may modify it.

        // add a "close" icon to exit the progress. it's an autorelease object
        var pCloseItem = cc.MenuItemImage.create(
                                            "CloseNormal.png",
                                            "CloseSelected.png",
                                            this.menuCloseCallback, 
                                            this);
        pCloseItem.setPosition( cc.p(size.width - 20, 20) );

        // create menu, it's an autorelease object
        var pMenu = cc.Menu.create(pCloseItem);
        pMenu.setPosition( cc.p(0, 0) );
        this.addChild(pMenu, 1);

        var yPos = 0;
        for (var i = 0; i < s_EventMenuItem.length; i++) {
            var label = cc.LabelTTF.create(s_EventMenuItem[i].id, "Arial", 24);
            var pMenuItem = cc.MenuItemLabel.create(label, this.eventMenuCallback, this);
            pMenu.addChild(pMenuItem, 0, s_EventMenuItem[i].tag);
            yPos = size.height - 50*i - 100;
            pMenuItem.setPosition( cc.p(size.width / 2, yPos));
        }

        var strName = g_pAnalytics.getPluginName();
        var strVer = g_pAnalytics.getPluginVersion();
        var ret = "Plugin : "+strName+", Ver : "+ strVer;
        var pLabel = cc.LabelTTF.create(ret, "Arial", 24, cc.size(size.width, 0), cc.TEXT_ALIGNMENT_CENTER);
        pLabel.setPosition(cc.p(size.width / 2, yPos - 100));
        this.addChild(pLabel);

        var label = cc.LabelTTF.create("reload all plugins", "Arial", 24);
        var pMenuItem = cc.MenuItemLabel.create(label, this.reloadPluginMenuCallback, this);
        pMenuItem.setAnchorPoint(cc.p(0.5, 0));
        pMenu.addChild(pMenuItem, 0);
        pMenuItem.setPosition( cc.p(size.width / 2, 0));
    },

    reloadPluginMenuCallback: function(pSender) {
        cc.log("reloadPluginMenuCallback");
        plugin.PluginManager.getInstance().unloadPlugin("AnalyticsFlurry");
        plugin.PluginManager.getInstance().unloadPlugin("AnalyticsUmeng");

        loadAnalyticsPlugin();
    },

    eventMenuCallback: function(pSender) {
        var isUmeng = g_pAnalytics instanceof plugin.AnalyticsUmeng;
        var isFlurry = g_pAnalytics instanceof plugin.AnalyticsFlurry;

        switch (pSender.getTag())
        {
        case TAG_LOG_EVENT_ID:
            {
                g_pAnalytics.logEvent("click");
                g_pAnalytics.logEvent("music");
            }
            break;
        case TAG_LOG_EVENT_ID_KV:
            {
                var paramMap = {};
                paramMap["type"] = "popular";
                paramMap["artist"] = "JJLin";
                g_pAnalytics.logEvent("music", paramMap);
            }
            break;
        case TAG_LOG_ONLINE_CONFIG:
            {
                if (isUmeng)
                {
                    cc.log("Online config = %s", g_pAnalytics.getConfigParams("abc"));           
                }
                else
                {
                    cc.log("Now is not using umeng!");
                }
            }
            break;
        case TAG_LOG_EVENT_ID_DURATION:
            {
                if (isUmeng)
                {
                    g_pAnalytics.logEventWithDuration("book", 12000);
                    g_pAnalytics.logEventWithDuration("book", 23000, "chapter1");
                    var paramMap = {};
                    paramMap["type"] = "popular";
                    paramMap["artist"] = "JJLin";
                    g_pAnalytics.logEventWithDuration("music", 2330000, paramMap);
                }
                else
                {
                    cc.log("Now is not using umeng!");
                }
            }
            break;
        case TAG_LOG_EVENT_BEGIN:
            {
                g_pAnalytics.logTimedEventBegin("music");

                var paramMap = {};
                paramMap["type"] = "popular";
                paramMap["artist"] = "JJLin";

                if (isUmeng)
                {
                    g_pAnalytics.logTimedEventWithLabelBegin("music", "one");
                    g_pAnalytics.logTimedKVEventBegin("music", "flag0", paramMap);
                }
                else if (isFlurry)
                {
                    g_pAnalytics.logTimedEventBegin("music-kv", paramMap);
                }
            }
            break;
        case TAG_LOG_EVENT_END:
            {
                g_pAnalytics.logTimedEventEnd("music");
                if (isUmeng)
                {          
                    g_pAnalytics.logTimedEventWithLabelEnd("music", "one");
                    g_pAnalytics.logTimedKVEventEnd("music", "flag0");
                }
                else if (isFlurry)
                {
                    g_pAnalytics.logTimedEventEnd("music-kv");
                }
            }
            break;
        case TAG_MAKE_ME_CRASH:
            {

            }
            break;
        default:
            break;
        }
    },

    menuCloseCallback: function() {
        cc.log("menuCloseCallback");
    }

});

var MyScene = cc.Scene.extend({
    ctor:function() {
        this._super();
        cc.associateWithNative( this, cc.Scene );
    },

    onEnter:function () {
        this._super();
        loadAnalyticsPlugin();

        var layer = new HelloWorld();
        layer.init();
        this.addChild(layer);
    }
});
