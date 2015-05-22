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

/**
 * RelativeData uses to save plist files, armature files, animations and textures for armature data manager.
 * @constructor
 */
ccs.RelativeData = function(){
    this.plistFiles=[];
    this.armatures=[];
    this.animations=[];
    this.textures=[];
};

/**
 * ccs.armatureDataManager is a singleton object which format and manage armature configuration and armature animation
 * @class
 * @name ccs.armatureDataManager
 */
ccs.armatureDataManager = /** @lends ccs.armatureDataManager# */{
    _animationDatas: {},
    _armatureDatas: {},
    _textureDatas: {},
    _autoLoadSpriteFile: false,
    _relativeDatas: {},

    s_sharedArmatureDataManager: null,

    /**
     * Removes armature cache data by configFilePath
     * @param {String} configFilePath
     */
    removeArmatureFileInfo:function(configFilePath){
        var data = this.getRelativeData(configFilePath);
        if(data){
            var i, obj;
            for (i = 0; i < data.armatures.length; i++) {
                obj = data.armatures[i];
                this.removeArmatureData(obj);
            }
            for ( i = 0; i < data.animations.length; i++) {
                obj = data.animations[i];
                this.removeAnimationData(obj);
            }
            for ( i = 0; i < data.textures.length; i++) {
                obj = data.textures[i];
                this.removeTextureData(obj);
            }
            for ( i = 0; i < data.plistFiles.length; i++) {
                obj = data.plistFiles[i];
                cc.spriteFrameCache.removeSpriteFramesFromFile(obj);
            }
            delete this._relativeDatas[configFilePath];
            ccs.dataReaderHelper.removeConfigFile(configFilePath);
        }
    },

    /**
     * Adds armature data
     * @param {string} id The id of the armature data
     * @param {ccs.ArmatureData} armatureData
     */
    addArmatureData:function (id, armatureData, configFilePath) {
        var data = this.getRelativeData(configFilePath);
        if (data){
            data.armatures.push(id);
        }
        this._armatureDatas[id] = armatureData;
    },

    /**
     * Gets armatureData by id
     * @param {String} id
     * @return {ccs.ArmatureData}
     */
    getArmatureData:function (id) {
        var armatureData = null;
        if (this._armatureDatas) {
            armatureData = this._armatureDatas[id];
        }
        return armatureData;
    },

    /**
     * Removes armature data from armature data manager.
     * @param {string} id
     */
    removeArmatureData:function(id){
        if (this._armatureDatas[id])
            delete this._armatureDatas[id];
    },

    /**
     * Adds animation data to armature data manager.
     * @param {String} id
     * @param {ccs.AnimationData} animationData
     */
    addAnimationData:function (id, animationData, configFilePath) {
        var data = this.getRelativeData(configFilePath);
        if(data)
            data.animations.push(id);
        this._animationDatas[id] = animationData;
    },

    /**
     * Gets animationData by id
     * @param {String} id
     * @return {ccs.AnimationData}
     */
    getAnimationData:function (id) {
        var animationData = null;
        if (this._animationDatas[id]) {
            animationData = this._animationDatas[id];
        }
        return animationData;
    },

    /**
     * Removes animation data
     * @param {string} id
     */
    removeAnimationData:function(id){
        if (this._animationDatas[id])
            delete this._animationDatas[id];
    },

    /**
     * Adds texture data to Armature data manager.
     * @param {String} id
     * @param {ccs.TextureData} textureData
     */
    addTextureData:function (id, textureData, configFilePath) {
        var data = this.getRelativeData(configFilePath);
        if (data) {
            data.textures.push(id);
        }
        this._textureDatas[id] = textureData;
    },

    /**
     * Gets textureData by id
     * @param {String} id
     * @return {ccs.TextureData}
     */
    getTextureData:function (id) {
        var textureData = null;
        if (this._textureDatas) {
            textureData = this._textureDatas[id];
        }
        return textureData;
    },

    /**
     * Removes texture data by id
     * @param {string} id
     */
    removeTextureData:function(id){
        if (this._textureDatas[id])
            delete this._textureDatas[id];
    },

    /**
     * Adds ArmatureFileInfo, it is managed by CCArmatureDataManager.
     * @param {String} imagePath
     * @param {String} plistPath
     * @param {String} configFilePath
     * @example
     * //example1
     * ccs.armatureDataManager.addArmatureFileInfo("res/test.json");
     * //example2
     * ccs.armatureDataManager.addArmatureFileInfo("res/test.png","res/test.plist","res/test.json");
     */
    addArmatureFileInfo:function (/*imagePath, plistPath, configFilePath*/) {
        var imagePath, plistPath, configFilePath;
        switch(arguments.length){
            case 1:
                configFilePath = arguments[0];

                this.addRelativeData(configFilePath);

                this._autoLoadSpriteFile = true;
                ccs.dataReaderHelper.addDataFromFile(configFilePath);
                break;
            case 3:
                imagePath = arguments[0];
                plistPath = arguments[1];
                configFilePath = arguments[2];

                this.addRelativeData(configFilePath);

                this._autoLoadSpriteFile = false;
                ccs.dataReaderHelper.addDataFromFile(configFilePath);
                this.addSpriteFrameFromFile(plistPath, imagePath);
        }
    },

    /**
     * Adds ArmatureFileInfo, it is managed by CCArmatureDataManager.
     * @param {String} imagePath
     * @param {String} plistPath
     * @param {String} configFilePath
     * @param {Function} selector
     * @param {Object} target
     */
    addArmatureFileInfoAsync:function (/*imagePath, plistPath, configFilePath, selector, target*/) {
        var imagePath, plistPath, configFilePath, target, selector;
        switch(arguments.length){
            case 3:
                configFilePath = arguments[0];
                target = arguments[2];
                selector = arguments[1];
                this.addRelativeData(configFilePath);
                this._autoLoadSpriteFile = true;
                ccs.dataReaderHelper.addDataFromFileAsync("", "", configFilePath, selector,target);
                break;
            case 5:
                imagePath = arguments[0];
                plistPath = arguments[1];
                configFilePath = arguments[2];
                target = arguments[4];
                selector = arguments[3];
                this.addRelativeData(configFilePath);

                this._autoLoadSpriteFile = false;
                ccs.dataReaderHelper.addDataFromFileAsync(imagePath, plistPath, configFilePath, selector, target);
                this.addSpriteFrameFromFile(plistPath, imagePath);
        }
    },

    /**
     * Add sprite frame to CCSpriteFrameCache, it will save display name and it's relative image name
     * @param {String} plistPath
     * @param {String} imagePath
     * @param {String} configFilePath
     */
    addSpriteFrameFromFile:function (plistPath, imagePath, configFilePath) {
        var data = this.getRelativeData(configFilePath);
        if(data)
            data.plistFiles.push(plistPath);
        ccs.spriteFrameCacheHelper.addSpriteFrameFromFile(plistPath, imagePath);
    },

    /**
     * Returns whether or not need auto load sprite file
     * @returns {boolean}
     */
    isAutoLoadSpriteFile:function(){
        return this._autoLoadSpriteFile;
    },

    /**
     * Returns armature Data of Armature data manager.
     * @return {Object}
     */
    getArmatureDatas:function () {
        return this._armatureDatas;
    },

    /**
     * Returns animation data of Armature data manager.
     * @return {Object}
     */
    getAnimationDatas:function () {
        return this._animationDatas;
    },

    /**
     * Returns texture data of Armature data manager.
     * @return {Object}
     */
    getTextureDatas:function () {
        return this._textureDatas;
    },

    /**
     * Adds Relative data of Armature data manager.
     * @param {String} configFilePath
     */
    addRelativeData: function (configFilePath) {
        if (!this._relativeDatas[configFilePath])
            this._relativeDatas[configFilePath] = new ccs.RelativeData();
    },

    /**
     * Gets RelativeData of Armature data manager.
     * @param {String} configFilePath
     * @returns {ccs.RelativeData}
     */
    getRelativeData: function (configFilePath) {
        return this._relativeDatas[configFilePath];
    },

    /**
     * Clear data
     */
    clear: function() {
        this._animationDatas = {};
        this._armatureDatas = {};
        this._textureDatas = {};
        ccs.spriteFrameCacheHelper.clear();
        ccs.dataReaderHelper.clear();
    }
};