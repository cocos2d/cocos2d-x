/****************************************************************************
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

/**
 * plugin manager
 * @class
 *
 */
(function(){

    if(cc === undefined){
        return;
    }

    var config = cc.game.config.plugin || {};

    //Native plugin usage
    var PluginManager = function(){};

    PluginManager.prototype = {
        constructor: PluginManager,

        /**
         * @returns {PluginManager}
         * @expose
         */
        getInstance: function(){
            return this;
        },

        /**
         * @param {String} pluginName
         * @expose
         */
        loadPlugin: function(pluginName){

        },

        /**
         *
         * @param pluginName
         * @expose
         */
        unloadPlugin: function(pluginName){

        }
    };

    var PluginAssembly = function(){};

    PluginAssembly.prototype = {
        constructor: PluginAssembly,

        /**
         * @param {Boolean} debug
         * @expose
         */
        setDebugMode: function(debug){},

        /**
         * @param {String} appKey
         * @expose
         */
        startSession: function(appKey){},

        /**
         * @param {Boolean} Capture
         * @expose
         */
        setCaptureUncaughtException: function(Capture){},

        /**
         * @param {String} funName
         * @param {All} Params
         * @expose
         */
        callFuncWithParam: function(funName){
            if(typeof this[funName] === 'function'){
                return this[funName].apply(this, Array.prototype.splice.call(arguments, 1));
            }else{
                cc.log("function is not define");
            }
        },

        /**
         * @param {String} funName
         * @param {All} Params
         * @expose
         */
        callStringFuncWithParam: function(funName){
            this.callFuncWithParam.apply(arguments);
        },

        /**
         * @returns {String}
         * @expose
         */
        getPluginName: function(){
            return this._name;
        },

        /**
         * @returns {String}
         * @expose
         */
        getPluginVersion: function(){
            return this._version;
        }
    };

    /** @expose */
    PluginAssembly.extend = function(name, porp){
        var p, prototype = {};
        for(p in PluginAssembly.prototype){
            prototype[p] = PluginAssembly.prototype[p];
        }
        for(p in porp){
            prototype[p] = porp[p];
        }
        var tmp = eval("(function " + name + "Plugin(){})");
        prototype.constructor = tmp;
        tmp.prototype = prototype;
        return tmp;
    };

    //Param
    var Param = function(type, value){
        var paramType = plugin.PluginParam.ParamType,tmpValue;
        switch(type){
            case paramType.TypeInt:
                tmpValue = parseInt(value);
                break;
            case paramType.TypeFloat:
                tmpValue = parseFloat(value);
                break;
            case paramType.TypeBool:
                tmpValue = Boolean(value);
                break;
            case paramType.TypeString:
                tmpValue = String(value);
                break;
            case paramType.TypeStringMap:
                tmpValue = value//JSON.stringify(value);
                break;
            default:
                tmpValue = value;
        }
        return tmpValue
    };

    /** @expose */
    Param.ParamType = {
        /** @expose */
        TypeInt:1,
        /** @expose */
        TypeFloat:2,
        /** @expose */
        TypeBool:3,
        /** @expose */
        TypeString:4,
        /** @expose */
        TypeStringMap:5
    };

    /** @expose */
    Param.AdsResultCode = {
        /** @expose */
        AdsReceived:0,
        /** @expose */
        FullScreenViewShown:1,
        /** @expose */
        FullScreenViewDismissed:2,
        /** @expose */
        PointsSpendSucceed:3,
        /** @expose */
        PointsSpendFailed:4,
        /** @expose */
        NetworkError:5,
        /** @expose */
        UnknownError:6
    };

    /** @expose */
    Param.PayResultCode = {
        /** @expose */
        PaySuccess:0,
        /** @expose */
        PayFail:1,
        /** @expose */
        PayCancel:2,
        /** @expose */
        PayTimeOut:3
    };

    /** @expose */
    Param.ShareResultCode = {
        /** @expose */
        ShareSuccess:0,
        /** @expose */
        ShareFail:1,
        /** @expose */
        ShareCancel:2,
        /** @expose */
        ShareTimeOut:3
    };

    /** @expose */
    var PluginList = {};

    /** @expose */
    var Plugin = {

        /** @expose */
        extend: function(name, extend){
            PluginList[name] = new (PluginAssembly.extend(name, extend));
            typeof PluginList[name].ctor === "function" && PluginList[name].ctor(config[name]);
        },

        /** @expose */
        PluginList: PluginList,

        /** @expose */
        PluginParam: Param,

        /** @expose */
        PluginManager: new PluginManager()

    };

    /** @expose */
    window.plugin = Plugin;

})();