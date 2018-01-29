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

var pluginXTestItemNames = [];

if (cc.sys.isMobile && cc.sys.os == cc.sys.OS_IOS) {
    pluginXTestItemNames.push({
        itemTitle: "Analytics Test",
        testLayer: function () {
            return new AnalyticsTestLayer(this.itemTitle);
        }
    });
}
if (cc.sys.isMobile && cc.sys.os == cc.sys.OS_IOS) {
    pluginXTestItemNames.push({
        itemTitle: "iOS IAP Test",
        testLayer: function () {
            return new IAPTestLayer(this.itemTitle);
        }
    });
}

var pluginXSceneManager = {
    _currentPluginXSceneId: 0,

    getCurrentPluginXSceneId: function () {
        return this._currentPluginXSceneId;
    },
    setCurrentPluginXSceneId: function (currentPluginXSceneId) {
        this._currentPluginXSceneId = currentPluginXSceneId
    },

    nextPluginXScene: function () {
        this._currentPluginXSceneId = (this._currentPluginXSceneId + 1) % pluginXTestItemNames.length;
        return this.currentPluginXScene();
    },

    previousPluginXScene: function () {
        this._currentPluginXSceneId = this._currentPluginXSceneId - 1;
        if (this._currentPluginXSceneId < 0) {
            this._currentPluginXSceneId = pluginXTestItemNames.length - 1;
        }

        return this.currentPluginXScene();
    },

    currentPluginXScene: function () {
        var scene = new cc.Scene();
        var layer = pluginXTestItemNames[this._currentPluginXSceneId].testLayer();
        scene.addChild(layer);
        return scene;
    }
};