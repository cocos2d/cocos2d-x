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

/**
 * The namespace for jsb exclusive APIs, all APIs in this namespace should never be used in Web engine.
 * So please check whether the running environment is native or not before any usage.
 * @namespace
 * @name jsb
 * @example
 *
 * if(cc.sys.isNative) {
 *     cc.log(cc.fileUtils.fullPathForFilename("test.js"));
 * }
 */
var jsb = jsb || {};

/**
 * ATTENTION: USE jsb.fileUtils INSTEAD OF jsb.FileUtils.<br/>
 * jsb.fileUtils is the native file utils' singleton object,<br/>
 * please refer to Cocos2d-x's API to know how to use it.<br/>
 * Only available in JSB
 * @class
 * @name jsb.fileUtils
 * @extend cc.Class
 */
jsb.fileUtils = /** @lends jsb.fileUtils# */{

    /**
     * @function fullPathForFilename
     * @param {String} arg0
     * @return {String}
     */
    fullPathForFilename : function (str)
    {
        return ;
    },

    /**
     * @function getStringFromFile
     * @param {String} arg0
     * @return {String}
     */
    getStringFromFile : function (str)
    {
        return ;
    },

    /**
     * @function removeFile
     * @param {String} arg0
     * @return {bool}
     */
    removeFile : function (str)
    {
        return false;
    },

    /**
     * @function isAbsolutePath
     * @param {String} arg0
     * @return {bool}
     */
    isAbsolutePath : function (str)
    {
        return false;
    },

    /**
     * @function renameFile
     * @param {String} arg0
     * @param {String} arg1
     * @param {String} arg2
     * @return {bool}
     */
    renameFile : function (str, str, str)
    {
        return false;
    },

    /**
     * @function loadFilenameLookupDictionaryFromFile
     * @param {String} arg0
     */
    loadFilenameLookupDictionaryFromFile : function (str)
    {
    },

    /**
     * @function isPopupNotify
     * @return {bool}
     */
    isPopupNotify : function ()
    {
        return false;
    },

    /**
     * @function getValueVectorFromFile
     * @param {String} arg0
     * @return {Array}
     */
    getValueVectorFromFile : function (str)
    {
        return new Array();
    },

    /**
     * @function getSearchPaths
     * @return {Array}
     */
    getSearchPaths : function ()
    {
        return new Array();
    },

    /**
     * @function writeToFile
     * @param {map_object} arg0
     * @param {String} arg1
     * @return {bool}
     */
    writeToFile : function (map, str)
    {
        return false;
    },

    /**
     * @function getValueMapFromFile
     * @param {String} arg0
     * @return {map_object}
     */
    getValueMapFromFile : function (str)
    {
        return map_object;
    },

    /**
     * @function getFileSize
     * @param {String} arg0
     * @return {long}
     */
    getFileSize : function (str)
    {
        return 0;
    },

    /**
     * @function removeDirectory
     * @param {String} arg0
     * @return {bool}
     */
    removeDirectory : function (str)
    {
        return false;
    },

    /**
     * @function setSearchPaths
     * @param {Array} arg0
     */
    setSearchPaths : function (array)
    {
    },

    /**
     * @function writeStringToFile
     * @param {String} arg0
     * @param {String} arg1
     * @return {bool}
     */
    writeStringToFile : function (str, str)
    {
        return false;
    },

    /**
     * @function setSearchResolutionsOrder
     * @param {Array} arg0
     */
    setSearchResolutionsOrder : function (array)
    {
    },

    /**
     * @function addSearchResolutionsOrder
     * @param {String} arg0
     */
    addSearchResolutionsOrder : function (str)
    {
    },

    /**
     * @function addSearchPath
     * @param {String} arg0
     */
    addSearchPath : function (str)
    {
    },

    /**
     * @function isFileExist
     * @param {String} arg0
     * @return {bool}
     */
    isFileExist : function (str)
    {
        return false;
    },

    /**
     * @function purgeCachedEntries
     */
    purgeCachedEntries : function ()
    {
    },

    /**
     * @function fullPathFromRelativeFile
     * @param {String} arg0
     * @param {String} arg1
     * @return {String}
     */
    fullPathFromRelativeFile : function (str, str)
    {
        return ;
    },

    /**
     * @function isDirectoryExist
     * @param {String} arg0
     * @return {bool}
     */
    isDirectoryExist : function (str)
    {
        return false;
    },

    /**
     * @function getSearchResolutionsOrder
     * @return {Array}
     */
    getSearchResolutionsOrder : function ()
    {
        return new Array();
    },

    /**
     * @function createDirectory
     * @param {String} arg0
     * @return {bool}
     */
    createDirectory : function (str)
    {
        return false;
    },

    /**
     * @function createDirectories
     * @param {String} arg0
     * @return {bool}
     */
    createDirectories : function (str)
    {
        return false;
    },

    /**
     * @function getWritablePath
     * @return {String}
     */
    getWritablePath : function ()
    {
        return ;
    }

};

/**
 * @class
 */
jsb.EventAssetsManager = cc.Class.extend(/** @lends jsb.EventAssetsManager# */{

    /**
     * @function getAssetsManager
     * @return {cc.AssetsManager}
     */
    getAssetsManager : function (
        )
    {
        return cc.AssetsManager;
    },

    /**
     * @function getAssetId
     * @return {String}
     */
    getAssetId : function (
        )
    {
        return ;
    },

    /**
     * @function getCURLECode
     * @return {int}
     */
    getCURLECode : function (
        )
    {
        return 0;
    },

    /**
     * @function getMessage
     * @return {String}
     */
    getMessage : function (
        )
    {
        return ;
    },

    /**
     * @function getCURLMCode
     * @return {int}
     */
    getCURLMCode : function (
        )
    {
        return 0;
    },

    /**
     * @function getPercentByFile
     * @return {float}
     */
    getPercentByFile : function (
        )
    {
        return 0;
    },

    /**
     * @function getEventCode
     * @return {cc.EventAssetsManager::EventCode}
     */
    getEventCode : function (
        )
    {
        return 0;
    },

    /**
     * @function getPercent
     * @return {float}
     */
    getPercent : function (
        )
    {
        return 0;
    },

    /**
     * @function EventAssetsManager
     * @constructor
     * @param {String} arg0
     * @param {cc.AssetsManager} arg1
     * @param {cc.EventAssetsManager::EventCode} arg2
     * @param {float} arg3
     * @param {float} arg4
     * @param {String} arg5
     * @param {String} arg6
     * @param {int} arg7
     * @param {int} arg8
     */
    EventAssetsManager : function (
        str,
        assetsmanager,
        eventcode,
        float,
        float,
        str,
        str,
        int,
        int
        )
    {
    }
});


/**
 * @class
 */
jsb.EventListenerAssetsManager = cc.Class.extend(/** @lends jsb.EventListenerAssetsManager# */{

    /**
     * @function init
     * @param {cc.AssetsManager} arg0
     * @param {function} arg1
     * @return {bool}
     */
    init : function (
        assetsmanager,
        func
        )
    {
        return false;
    },

    /**
     * @function create
     * @param {cc.AssetsManager} arg0
     * @param {function} arg1
     * @return {cc.EventListenerAssetsManager}
     */
    create : function (
        assetsmanager,
        func
        )
    {
        return cc.EventListenerAssetsManager;
    },

    /**
     * @function EventListenerAssetsManager
     * @constructor
     */
    EventListenerAssetsManager : function (
        )
    {
    }

});

/**
 * @class
 * jsb.AssetsManager is the native AssetsManager for your game resources or scripts.
 * please refer to this document to know how to use it: http://www.cocos2d-x.org/docs/manual/framework/html5/v3/assets-manager/en
 * Only available in JSB
 */
jsb.AssetsManager = cc.Class.extend(/** @lends jsb.AssetsManager# */{

    /**
     * @function getState
     * @return {jsb.AssetsManager::State}
     */
    getState : function ()
    {
        return 0;
    },

    /**
     * @function checkUpdate
     */
    checkUpdate : function ()
    {
    },

    /**
     * @function getStoragePath
     * @return {String}
     */
    getStoragePath : function ()
    {
        return ;
    },

    /**
     * @function update
     */
    update : function ()
    {
    },

    /**
     * @function getLocalManifest
     * @return {jsb.Manifest}
     */
    getLocalManifest : function ()
    {
        return cc.Manifest;
    },

    /**
     * @function getRemoteManifest
     * @return {jsb.Manifest}
     */
    getRemoteManifest : function ()
    {
        return cc.Manifest;
    },

    /**
     * @function downloadFailedAssets
     */
    downloadFailedAssets : function ()
    {
    },

    /**
     * @function create
     * @param {String} arg0
     * @param {String} arg1
     * @return {jsb.AssetsManager}
     */
    create : function (str, str)
    {
        return cc.AssetsManager;
    },

    /**
     * @function AssetsManager
     * @constructor
     * @param {String} arg0
     * @param {String} arg1
     */
    ctor : function (str, str)
    {
    }

});

/**
 * @class
 */
jsb.Manifest = cc.Class.extend(/** @lends jsb.Manifest# */{

    /**
     * @function getManifestFileUrl
     * @return {String}
     */
    getManifestFileUrl : function ()
    {
        return ;
    },

    /**
     * @function isVersionLoaded
     * @return {bool}
     */
    isVersionLoaded : function ()
    {
        return false;
    },

    /**
     * @function isLoaded
     * @return {bool}
     */
    isLoaded : function ()
    {
        return false;
    },

    /**
     * @function getPackageUrl
     * @return {String}
     */
    getPackageUrl : function ()
    {
        return ;
    },

    /**
     * @function getVersion
     * @return {String}
     */
    getVersion : function ()
    {
        return ;
    },

    /**
     * @function getVersionFileUrl
     * @return {String}
     */
    getVersionFileUrl : function ()
    {
        return ;
    }
});

/**
 * jsb.reflection is a bridge to let you invoke Java static functions.
 * please refer to this document to know how to use it: http://www.cocos2d-x.org/docs/manual/framework/html5/v3/reflection/en
 * Only available on iOS/Mac/Android platform
 * @class
 * @name jsb.reflection
 */
jsb.reflection = /** @lends jsb.reflection# */{
    /**
     * @function
     */
    callStaticMethod : function(){
    }
};