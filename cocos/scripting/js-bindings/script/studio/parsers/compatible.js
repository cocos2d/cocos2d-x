/****************************************************************************
 Copyright (c) 2013-2016 Chukong Technologies Inc.
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


/*
 This file is for compatibility compatibility with older versions of GUIReader and SceneReader
 todo: deprecated all
 */

(function(){

    ccs.uiReader = {

        _fileDesignSizes: {},

        //@deprecated This function will be deprecated sooner or later please use ccs.load
        /**
         * Create CCUI Node
         * @param file
         * @returns {*}
         */
        widgetFromJsonFile: function(file){
            var json = cc.loader.getRes(cc.path.join(cc.loader.resPath, file));
            if(json)
                this._fileDesignSizes[file] = cc.size(json["designWidth"]||0, json["designHeight"]||0);

            var version = json["Version"] || json["version"];
            var versionNum = ccs.uiReader.getVersionInteger(version);
            if(!version || versionNum >= 1700){
                cc.warn("Not supported file types, Please try use the ccs.load");
                return null;
            }
            return ccs._load(file, "ccui");
        },

        //@deprecated This function will be deprecated sooner or later please use parser.registerParser
        /**
         * Register a custom Widget reader
         * @param classType
         * @param ins
         * @param object
         * @param callback
         * @deprecated This function will be deprecated sooner or later please use parser.registerParser
         */
        registerTypeAndCallBack: function(classType, ins, object, callback){
            var parser = ccs._load.getParser("ccui")["*"];
            var func = callback.bind(object);
            parser.registerParser(classType, function(options, resourcePath){
                var widget = new ins();
                var uiOptions = options["options"];
                object.setPropsFromJsonDictionary && object.setPropsFromJsonDictionary(widget, uiOptions);
                this.generalAttributes(widget, uiOptions);
                var customProperty = uiOptions["customProperty"];
                if(customProperty)
                    customProperty = JSON.parse(customProperty);
                else
                    customProperty = {};
                func(classType, widget, customProperty);
                this.colorAttributes(widget, uiOptions);
                this.anchorPointAttributes(widget, uiOptions);
                this.parseChild.call(this, widget, options, resourcePath);
                return widget;
            });
        },

        //@deprecated This function will be deprecated sooner or later
        /**
         * Gets the version number by version string.
         * @param {String} version version string.
         * @returns {Number}
         */
        getVersionInteger: function(version){
            if(!version || typeof version !== "string") return 0;
            var arr = version.split(".");
            if (arr.length !== 4)
                return 0;
            var num = 0;
            arr.forEach(function(n, i){
                num += n * Math.pow(10, 3 - i);
            });
            return num;
        },

        //@deprecated This function will be deprecated sooner or later
        /**
         * stores the designSize of UI file.
         * @param {String} fileName
         * @param {cc.Size} size
         */
        storeFileDesignSize: function (fileName, size) {
            this._fileDesignSizes[fileName] = size;
        },

        //@deprecated This function will be deprecated sooner or later
        /**
         * Gets the design size by filename.
         * @param {String} fileName
         * @returns {cc.Size}
         */
        getFileDesignSize: function (fileName) {
            return this._fileDesignSizes[fileName];
        },

        //@deprecated This function will be deprecated sooner or later
        /**
         * Returns the file path
         * @returns {string}
         */
        getFilePath: function(){
            return this._filePath;
        },

        //@deprecated This function will be deprecated sooner or later
        setFilePath: function(path){
            this._filePath = path;
        },

        //@deprecated This function will be deprecated sooner or later
        /**
         * Returns the parsed object map. (analytic function)
         * @returns {Object}
         */
        getParseObjectMap: function(){
            return ccs._load.getParser("ccui")["*"]["parsers"];
        },

        //@deprecated This function will be deprecated sooner or later
        /**
         * Returns the parsed callback map. (analytic function)
         * @returns {*}
         */
        getParseCallBackMap: function(){
            return ccs._load.getParser("ccui")["*"]["parsers"];
        },

        //@deprecated This function will be deprecated sooner or later
        clear: function(){}
    };

    var parser = ccs._load.getParser("ccui")["*"];
    ccs.imageViewReader  = {setPropsFromJsonDictionary: parser.ImageViewAttributes};
    ccs.buttonReader     = {setPropsFromJsonDictionary: parser.ButtonAttributes};
    ccs.checkBoxReader   = {setPropsFromJsonDictionary: parser.CheckBoxAttributes};
    ccs.labelAtlasReader = {setPropsFromJsonDictionary: parser.TextAtlasAttributes};
    ccs.labelBMFontReader= {setPropsFromJsonDictionary: parser.TextBMFontAttributes};
    ccs.labelReader      = {setPropsFromJsonDictionary: parser.TextAttributes};
    ccs.layoutReader     = {setPropsFromJsonDictionary: parser.LayoutAttributes};
    ccs.listViewReader   = {setPropsFromJsonDictionary: parser.ListViewAttributes};
    ccs.loadingBarReader = {setPropsFromJsonDictionary: parser.LoadingBarAttributes};
    ccs.pageViewReader   = {setPropsFromJsonDictionary: parser.PageViewAttributes};
    ccs.scrollViewReader = {setPropsFromJsonDictionary: parser.ScrollViewAttributes};
    ccs.sliderReader     = {setPropsFromJsonDictionary: parser.SliderAttributes};
    ccs.textFieldReader  = {setPropsFromJsonDictionary: parser.TextFieldAttributes};
})();

(function(){
    ccs.sceneReader = {

        _node: null,

        //@deprecated This function will be deprecated sooner or later please use ccs.load
        /**
         * Create Scene Node
         * @param file
         * @returns {*}
         */
        createNodeWithSceneFile: function(file){
            var node = ccs._load(file, "scene");
            this._node = node;
            return node;
        },

        /**
         * Get a node by tag.
         * @param {Number} tag
         * @returns {cc.Node|null}
         */
        getNodeByTag: function(tag){
            if (this._node == null)
                return null;
            if (this._node.getTag() === tag)
                return this._node;
            return this._nodeByTag(this._node, tag);
        },

        _nodeByTag: function (parent, tag) {
            if (parent == null)
                return null;
            var retNode = null;
            var children = parent.getChildren();
            for (var i = 0; i < children.length; i++) {
                var child = children[i];
                if (child && child.getTag() === tag) {
                    retNode = child;
                    break;
                } else {
                    retNode = this._nodeByTag(child, tag);
                    if (retNode)
                        break;
                }
            }
            return retNode;
        },

        //@deprecated This function will be deprecated sooner or later
        /**
         * Returns the version of ccs.SceneReader.
         * @returns {string}
         */
        version: function(){
            return "*";
        },

        //@deprecated This function will be deprecated sooner or later
        /**
         * Sets the listener to reader.
         * Cannot use
         */
        setTarget: function(){},

        //@deprecated This function will be deprecated sooner or later
        /**
         * Clear all triggers and stops all sounds.
         */
        clear: function(){
            ccs.triggerManager.removeAll();
            cc.audioEngine.end();
        }
    };
})();