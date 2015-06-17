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

var g_pAnalytics = null;
var s_strAppKey = "";
// The app key of flurry
var FLURRY_KEY_IOS      =    "KMGG7CD9WPK2TW4X9VR8";
var FLURRY_KEY_ANDROID  =    "SPKFH8KMPGHMMBWRBT5W";
var UMENG_KEY_IOS       =    "50d2b18c5270152187000097";
var UMENG_KEY_ANDROID   =    "";          // umeng key for android is setted in AndroidManifest.xml


if (!plugin) {
    var plugin = {};
}

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
    var langType = cc.sys.language;//cc.Application.getInstance().getCurrentLanguage();

    var umengKey  = "";
    var flurryKey = "";

    if (cc.sys.os == cc.sys.OS_IOS)
    {
        umengKey  = UMENG_KEY_IOS;
        flurryKey = FLURRY_KEY_IOS;
    }
    else if (cc.sys.os == cc.sys.OS_ANDROID)
    {
        umengKey  = UMENG_KEY_ANDROID;
        flurryKey = FLURRY_KEY_ANDROID;
    }

    var pluginManager = plugin.PluginManager.getInstance();
    if (cc.LANGUAGE_CHINESE == langType)
    {
        g_pAnalytics = pluginManager.loadPlugin("AnalyticsUmeng");
        s_strAppKey = umengKey;
    }
    else
    {
        g_pAnalytics = pluginManager.loadPlugin("AnalyticsFlurry");
        s_strAppKey = flurryKey;
    }

    g_pAnalytics.setDebugMode(true);
    g_pAnalytics.startSession(s_strAppKey);
    g_pAnalytics.setCaptureUncaughtException(true);

    g_pAnalytics.callFuncWithParam("updateOnlineConfig", null);
    g_pAnalytics.callFuncWithParam("setReportLocation", new plugin.PluginParam(plugin.PluginParam.ParamType.TypeBool, true));
    g_pAnalytics.callFuncWithParam("logPageView", null);
    g_pAnalytics.callFuncWithParam("setVersionName", new plugin.PluginParam(plugin.PluginParam.ParamType.TypeString, "1.1"));
    g_pAnalytics.callFuncWithParam("setAge", new plugin.PluginParam(plugin.PluginParam.ParamType.TypeInt, 20));
    g_pAnalytics.callFuncWithParam("setGender", new plugin.PluginParam(plugin.PluginParam.ParamType.TypeInt, 1));
    g_pAnalytics.callFuncWithParam("setUserId", new plugin.PluginParam(plugin.PluginParam.ParamType.TypeString, "123456"));
    g_pAnalytics.callFuncWithParam("setUseHttps", new plugin.PluginParam(plugin.PluginParam.ParamType.TypeBool, false));
};


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

var AnalyticsTestLayer = PluginXTest.extend({

    _title:"Plugin-x Test",
    _subtitle: cc.LANGUAGE_CHINESE == cc.sys.language ? "umeng" : "flurry",//cc.Application.getInstance().getCurrentLanguage() ? "umeng" : "flurry",

    onEnter: function() {
        this._super();
        var size = cc.director.getWinSize();

        loadAnalyticsPlugin();

        var pMenu = new cc.Menu();
        pMenu.setPosition( cc.p(0, 0) );
        this.addChild(pMenu, 1);

        var yPos = 0;
        for (var i = 0; i < s_EventMenuItem.length; i++) {
            var label = new cc.LabelTTF(s_EventMenuItem[i].id, "Arial", 24);
            var pMenuItem = new cc.MenuItemLabel(label, this.eventMenuCallback, this);
            pMenu.addChild(pMenuItem, 0, s_EventMenuItem[i].tag);
            yPos = size.height - 50*i - 100;
            pMenuItem.setPosition( cc.p(size.width / 2, yPos));
        }

        var strName = g_pAnalytics.getPluginName();
        var strVer = g_pAnalytics.getPluginVersion();
        var ret = "Plugin : "+strName+", Ver : "+ strVer;
        var pLabel = new cc.LabelTTF(ret, "Arial", 24, cc.size(size.width, 0), cc.TEXT_ALIGNMENT_CENTER);
        pLabel.setPosition(cc.p(size.width / 2, yPos - 100));
        this.addChild(pLabel);

        var label = new cc.LabelTTF("reload all plugins", "Arial", 24);
        var pMenuItem = new cc.MenuItemLabel(label, this.reloadPluginMenuCallback, this);
        pMenuItem.setAnchorPoint(cc.p(0.5, 0));
        pMenu.addChild(pMenuItem, 0);
        pMenuItem.setPosition( cc.p(size.width / 2, 0));
    },

    reloadPluginMenuCallback: function(pSender) {
        plugin.PluginManager.getInstance().unloadPlugin("AnalyticsFlurry");
        plugin.PluginManager.getInstance().unloadPlugin("AnalyticsUmeng");

        loadAnalyticsPlugin();
    },

    eventMenuCallback: function(pSender) {
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
                cc.log("Online config = " + g_pAnalytics.callStringFuncWithParam("getConfigParams", new plugin.PluginParam(plugin.PluginParam.ParamType.TypeString, "abc")));
            }
                break;
            case TAG_LOG_EVENT_ID_DURATION:
            {
                g_pAnalytics.callFuncWithParam("logEventWithDuration",
                    new plugin.PluginParam(plugin.PluginParam.ParamType.TypeString, "book"),
                    new plugin.PluginParam(plugin.PluginParam.ParamType.TypeInt, 12000));
                g_pAnalytics.callFuncWithParam("logEventWithDurationLabel",
                    new plugin.PluginParam(plugin.PluginParam.ParamType.TypeString, "book"),
                    new plugin.PluginParam(plugin.PluginParam.ParamType.TypeInt, 23000),
                    new plugin.PluginParam(plugin.PluginParam.ParamType.TypeString, "chapter1"));
                var paramMap = {};
                paramMap["type"] = "popular";
                paramMap["artist"] = "JJLin";
                g_pAnalytics.callFuncWithParam("logEventWithDurationParams",
                    new plugin.PluginParam(plugin.PluginParam.ParamType.TypeString, "music"),
                    new plugin.PluginParam(plugin.PluginParam.ParamType.TypeInt, 2330000),
                    new plugin.PluginParam(plugin.PluginParam.ParamType.TypeStringMap, paramMap));
            }
                break;
            case TAG_LOG_EVENT_BEGIN:
            {
                g_pAnalytics.logTimedEventBegin("music");

                var paramMap = {};
                paramMap["type"] = "popular";
                paramMap["artist"] = "JJLin";

                g_pAnalytics.callFuncWithParam("logTimedEventWithLabelBegin",
                    new plugin.PluginParam(plugin.PluginParam.ParamType.TypeString, "music"),
                    new plugin.PluginParam(plugin.PluginParam.ParamType.TypeString, "one"));
                g_pAnalytics.callFuncWithParam("logTimedKVEventBegin",
                    new plugin.PluginParam(plugin.PluginParam.ParamType.TypeString, "music"),
                    new plugin.PluginParam(plugin.PluginParam.ParamType.TypeString, "flag0"),
                    new plugin.PluginParam(plugin.PluginParam.ParamType.TypeStringMap, paramMap));

                g_pAnalytics.callFuncWithParam("logTimedEventBeginWithParams",
                    new plugin.PluginParam(plugin.PluginParam.ParamType.TypeString, "music-kv"),
                    new plugin.PluginParam(plugin.PluginParam.ParamType.TypeStringMap, paramMap));
            }
                break;
            case TAG_LOG_EVENT_END:
            {
                g_pAnalytics.logTimedEventEnd("music");

                g_pAnalytics.callFuncWithParam("logTimedEventWithLabelEnd",
                    new plugin.PluginParam(plugin.PluginParam.ParamType.TypeString, "music"),
                    new plugin.PluginParam(plugin.PluginParam.ParamType.TypeString, "one"));
                g_pAnalytics.callFuncWithParam("logTimedKVEventEnd",
                    new plugin.PluginParam(plugin.PluginParam.ParamType.TypeString, "music"),
                    new plugin.PluginParam(plugin.PluginParam.ParamType.TypeString, "flag0"));

                g_pAnalytics.callFuncWithParam("logTimedEventEnd", new plugin.PluginParam(plugin.PluginParam.ParamType.TypeString, "music-kv"));
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

    onNextCallback:function (sender) {
        var s = new FacebookTest();
        s.addChild(new FacebookLayer);
        director.runScene(s);
    },
    onBackCallback:function (sender) {
        var s = new FacebookTest();
        s.addChild(new FacebookLayer);
        director.runScene(s);
    }

});
