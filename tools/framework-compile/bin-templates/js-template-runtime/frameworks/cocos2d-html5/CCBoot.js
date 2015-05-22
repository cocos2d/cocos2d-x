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
 * The main namespace of Cocos2d-JS, all engine core classes, functions, properties and constants are defined in this namespace
 * @namespace
 * @name cc
 */
var cc = cc || {};
cc._tmp = cc._tmp || {};
cc._LogInfos = {};

/** @expose */
window._p;
_p = window;
/** @expose */
_p.gl;
/** @expose */
_p.WebGLRenderingContext;
/** @expose */
_p.DeviceOrientationEvent;
/** @expose */
_p.DeviceMotionEvent;
/** @expose */
_p.AudioContext;
/** @expose */
_p.webkitAudioContext;
/** @expose */
_p.mozAudioContext;
_p = Object.prototype;
/** @expose */
_p._super;
/** @expose */
_p.ctor;
delete window._p;

cc.newElement = function (x) {
    return document.createElement(x);
};

cc._addEventListener = function (element, type, listener, useCapture) {
    element.addEventListener(type, listener, useCapture);
};

//is nodejs ? Used to support node-webkit.
cc._isNodeJs = typeof require !== 'undefined' && require("fs");

/**
 * Iterate over an object or an array, executing a function for each matched element.
 * @param {object|array} obj
 * @param {function} iterator
 * @param {object} [context]
 */
cc.each = function (obj, iterator, context) {
    if (!obj)
        return;
    if (obj instanceof Array) {
        for (var i = 0, li = obj.length; i < li; i++) {
            if (iterator.call(context, obj[i], i) === false)
                return;
        }
    } else {
        for (var key in obj) {
            if (iterator.call(context, obj[key], key) === false)
                return;
        }
    }
};

/**
 * Copy all of the properties in source objects to target object and return the target object.
 * @param {object} target
 * @param {object} *sources
 * @returns {object}
 */
cc.extend = function(target) {
    var sources = arguments.length >= 2 ? Array.prototype.slice.call(arguments, 1) : [];

    cc.each(sources, function(src) {
        for(var key in src) {
            if (src.hasOwnProperty(key)) {
                target[key] = src[key];
            }
        }
    });
    return target;
};

/**
 * Check the obj whether is function or not
 * @param {*} obj
 * @returns {boolean}
 */
cc.isFunction = function(obj) {
    return typeof obj === 'function';
};

/**
 * Check the obj whether is number or not
 * @param {*} obj
 * @returns {boolean}
 */
cc.isNumber = function(obj) {
    return typeof obj === 'number' || Object.prototype.toString.call(obj) === '[object Number]';
};

/**
 * Check the obj whether is string or not
 * @param {*} obj
 * @returns {boolean}
 */
cc.isString = function(obj) {
    return typeof obj === 'string' || Object.prototype.toString.call(obj) === '[object String]';
};

/**
 * Check the obj whether is array or not
 * @param {*} obj
 * @returns {boolean}
 */
cc.isArray = function(obj) {
    return Array.isArray(obj) ||
        (typeof obj === 'object' && Object.prototype.toString.call(obj) === '[object Array]');
};

/**
 * Check the obj whether is undefined or not
 * @param {*} obj
 * @returns {boolean}
 */
cc.isUndefined = function(obj) {
    return typeof obj === 'undefined';
};

/**
 * Check the obj whether is object or not
 * @param {*} obj
 * @returns {boolean}
 */
cc.isObject = function(obj) {
    return typeof obj === "object" && Object.prototype.toString.call(obj) === '[object Object]';
};

/**
 * Check the url whether cross origin
 * @param {String} url
 * @returns {boolean}
 */
cc.isCrossOrigin = function (url) {
    if (!url) {
        cc.log("invalid URL");
        return false;
    }
    var startIndex = url.indexOf("://");
    if (startIndex === -1)
        return false;

    var endIndex = url.indexOf("/", startIndex + 3);
    var urlOrigin = (endIndex === -1) ? url : url.substring(0, endIndex);
    return urlOrigin !== location.origin;
};

//+++++++++++++++++++++++++something about async begin+++++++++++++++++++++++++++++++
/**
 * Async Pool class, a helper of cc.async
 * @param {Object|Array} srcObj
 * @param {Number} limit the limit of parallel number
 * @param {function} iterator
 * @param {function} onEnd
 * @param {object} target
 * @constructor
 */
cc.AsyncPool = function(srcObj, limit, iterator, onEnd, target){
    var self = this;
    self._srcObj = srcObj;
    self._limit = limit;
    self._pool = [];
    self._iterator = iterator;
    self._iteratorTarget = target;
    self._onEnd = onEnd;
    self._onEndTarget = target;
    self._results = srcObj instanceof Array ? [] : {};
    self._isErr = false;

    cc.each(srcObj, function(value, index){
        self._pool.push({index : index, value : value});
    });

    self.size = self._pool.length;
    self.finishedSize = 0;
    self._workingSize = 0;

    self._limit = self._limit || self.size;

    self.onIterator = function(iterator, target){
        self._iterator = iterator;
        self._iteratorTarget = target;
    };

    self.onEnd = function(endCb, endCbTarget){
        self._onEnd = endCb;
        self._onEndTarget = endCbTarget;
    };

    self._handleItem = function(){
        var self = this;
        if(self._pool.length === 0 || self._workingSize >= self._limit)
            return;                                                         //return directly if the array's length = 0 or the working size great equal limit number

        var item = self._pool.shift();
        var value = item.value, index = item.index;
        self._workingSize++;
        self._iterator.call(self._iteratorTarget, value, index,
            function(err) {
                if (self._isErr)
                    return;

                self.finishedSize++;
                self._workingSize--;
                if (err) {
                    self._isErr = true;
                    if (self._onEnd)
                        self._onEnd.call(self._onEndTarget, err);
                    return;
                }

                var arr = Array.prototype.slice.call(arguments, 1);
                self._results[this.index] = arr[0];
                if (self.finishedSize === self.size) {
                    if (self._onEnd)
                        self._onEnd.call(self._onEndTarget, null, self._results);
                    return;
                }
                self._handleItem();
            }.bind(item),
            self);
    };

    self.flow = function(){
        var self = this;
        if(self._pool.length === 0) {
            if(self._onEnd)
                self._onEnd.call(self._onEndTarget, null, []);
                return;
        }
        for(var i = 0; i < self._limit; i++)
            self._handleItem();
    }
};

/**
 * @class
 */
cc.async = /** @lends cc.async# */{
    /**
     * Do tasks series.
     * @param {Array|Object} tasks
     * @param {function} [cb] callback
     * @param {Object} [target]
     * @return {cc.AsyncPool}
     */
    series : function(tasks, cb, target){
        var asyncPool = new cc.AsyncPool(tasks, 1, function(func, index, cb1){
            func.call(target, cb1);
        }, cb, target);
        asyncPool.flow();
        return asyncPool;
    },

    /**
     * Do tasks parallel.
     * @param {Array|Object} tasks
     * @param {function} cb callback
     * @param {Object} [target]
     * @return {cc.AsyncPool}
     */
    parallel : function(tasks, cb, target){
        var asyncPool = new cc.AsyncPool(tasks, 0, function(func, index, cb1){
            func.call(target, cb1);
        }, cb, target);
        asyncPool.flow();
        return asyncPool;
    },

    /**
     * Do tasks waterfall.
     * @param {Array|Object} tasks
     * @param {function} cb callback
     * @param {Object} [target]
     * @return {cc.AsyncPool}
     */
    waterfall : function(tasks, cb, target){
        var args = [];
        var lastResults = [null];//the array to store the last results
        var asyncPool = new cc.AsyncPool(tasks, 1,
            function (func, index, cb1) {
                args.push(function (err) {
                    args = Array.prototype.slice.call(arguments, 1);
                    if(tasks.length - 1 === index) lastResults = lastResults.concat(args);//while the last task
                    cb1.apply(null, arguments);
                });
                func.apply(target, args);
            }, function (err) {
                if (!cb)
                    return;
                if (err)
                    return cb.call(target, err);
                cb.apply(target, lastResults);
            });
        asyncPool.flow();
        return asyncPool;
    },

    /**
     * Do tasks by iterator.
     * @param {Array|Object} tasks
     * @param {function|Object} iterator
     * @param {function} [callback]
     * @param {Object} [target]
     * @return {cc.AsyncPool}
     */
    map : function(tasks, iterator, callback, target){
        var locIterator = iterator;
        if(typeof(iterator) === "object"){
            callback = iterator.cb;
            target = iterator.iteratorTarget;
            locIterator = iterator.iterator;
        }
        var asyncPool = new cc.AsyncPool(tasks, 0, locIterator, callback, target);
        asyncPool.flow();
        return asyncPool;
    },

    /**
     * Do tasks by iterator limit.
     * @param {Array|Object} tasks
     * @param {Number} limit
     * @param {function} iterator
     * @param {function} cb callback
     * @param {Object} [target]
     */
    mapLimit : function(tasks, limit, iterator, cb, target){
        var asyncPool = new cc.AsyncPool(tasks, limit, iterator, cb, target);
        asyncPool.flow();
        return asyncPool;
    }
};
//+++++++++++++++++++++++++something about async end+++++++++++++++++++++++++++++++++

//+++++++++++++++++++++++++something about path begin++++++++++++++++++++++++++++++++
/**
 * @class
 */
cc.path = /** @lends cc.path# */{
    /**
     * Join strings to be a path.
     * @example
     cc.path.join("a", "b.png");//-->"a/b.png"
     cc.path.join("a", "b", "c.png");//-->"a/b/c.png"
     cc.path.join("a", "b");//-->"a/b"
     cc.path.join("a", "b", "/");//-->"a/b/"
     cc.path.join("a", "b/", "/");//-->"a/b/"
     * @returns {string}
     */
    join: function () {
        var l = arguments.length;
        var result = "";
        for (var i = 0; i < l; i++) {
            result = (result + (result === "" ? "" : "/") + arguments[i]).replace(/(\/|\\\\)$/, "");
        }
        return result;
    },

    /**
     * Get the ext name of a path.
     * @example
     cc.path.extname("a/b.png");//-->".png"
     cc.path.extname("a/b.png?a=1&b=2");//-->".png"
     cc.path.extname("a/b");//-->null
     cc.path.extname("a/b?a=1&b=2");//-->null
     * @param {string} pathStr
     * @returns {*}
     */
    extname: function (pathStr) {
        var temp = /(\.[^\.\/\?\\]*)(\?.*)?$/.exec(pathStr);
        return temp ? temp[1] : null;
    },

    /**
     * Get the main name of a file name
     * @param {string} fileName
     * @returns {string}
     */
    mainFileName: function(fileName){
        if(fileName){
           var idx = fileName.lastIndexOf(".");
            if(idx !== -1)
               return fileName.substring(0,idx);
        }
        return fileName;
    },

    /**
     * Get the file name of a file path.
     * @example
     cc.path.basename("a/b.png");//-->"b.png"
     cc.path.basename("a/b.png?a=1&b=2");//-->"b.png"
     cc.path.basename("a/b.png", ".png");//-->"b"
     cc.path.basename("a/b.png?a=1&b=2", ".png");//-->"b"
     cc.path.basename("a/b.png", ".txt");//-->"b.png"
     * @param {string} pathStr
     * @param {string} [extname]
     * @returns {*}
     */
    basename: function (pathStr, extname) {
        var index = pathStr.indexOf("?");
        if (index > 0) pathStr = pathStr.substring(0, index);
        var reg = /(\/|\\\\)([^(\/|\\\\)]+)$/g;
        var result = reg.exec(pathStr.replace(/(\/|\\\\)$/, ""));
        if (!result) return null;
        var baseName = result[2];
        if (extname && pathStr.substring(pathStr.length - extname.length).toLowerCase() === extname.toLowerCase())
            return baseName.substring(0, baseName.length - extname.length);
        return baseName;
    },

    /**
     * Get dirname of a file path.
     * @example
     * unix
     cc.path.driname("a/b/c.png");//-->"a/b"
     cc.path.driname("a/b/c.png?a=1&b=2");//-->"a/b"
     cc.path.dirname("a/b/");//-->"a/b"
     cc.path.dirname("c.png");//-->""
     * windows
     cc.path.driname("a\\b\\c.png");//-->"a\b"
     cc.path.driname("a\\b\\c.png?a=1&b=2");//-->"a\b"
     * @param {string} pathStr
     * @returns {*}
     */
    dirname: function (pathStr) {
        return pathStr.replace(/((.*)(\/|\\|\\\\))?(.*?\..*$)?/, '$2');
    },

    /**
     * Change extname of a file path.
     * @example
     cc.path.changeExtname("a/b.png", ".plist");//-->"a/b.plist"
     cc.path.changeExtname("a/b.png?a=1&b=2", ".plist");//-->"a/b.plist?a=1&b=2"
     * @param {string} pathStr
     * @param {string} [extname]
     * @returns {string}
     */
    changeExtname: function (pathStr, extname) {
        extname = extname || "";
        var index = pathStr.indexOf("?");
        var tempStr = "";
        if (index > 0) {
            tempStr = pathStr.substring(index);
            pathStr = pathStr.substring(0, index);
        }
        index = pathStr.lastIndexOf(".");
        if (index < 0) return pathStr + extname + tempStr;
        return pathStr.substring(0, index) + extname + tempStr;
    },
    /**
     * Change file name of a file path.
     * @example
     cc.path.changeBasename("a/b/c.plist", "b.plist");//-->"a/b/b.plist"
     cc.path.changeBasename("a/b/c.plist?a=1&b=2", "b.plist");//-->"a/b/b.plist?a=1&b=2"
     cc.path.changeBasename("a/b/c.plist", ".png");//-->"a/b/c.png"
     cc.path.changeBasename("a/b/c.plist", "b");//-->"a/b/b"
     cc.path.changeBasename("a/b/c.plist", "b", true);//-->"a/b/b.plist"
     * @param {String} pathStr
     * @param {String} basename
     * @param {Boolean} [isSameExt]
     * @returns {string}
     */
    changeBasename: function (pathStr, basename, isSameExt) {
        if (basename.indexOf(".") === 0) return this.changeExtname(pathStr, basename);
        var index = pathStr.indexOf("?");
        var tempStr = "";
        var ext = isSameExt ? this.extname(pathStr) : "";
        if (index > 0) {
            tempStr = pathStr.substring(index);
            pathStr = pathStr.substring(0, index);
        }
        index = pathStr.lastIndexOf("/");
        index = index <= 0 ? 0 : index + 1;
        return pathStr.substring(0, index) + basename + ext + tempStr;
    }
};
//+++++++++++++++++++++++++something about path end++++++++++++++++++++++++++++++++

//+++++++++++++++++++++++++something about loader start+++++++++++++++++++++++++++
/**
 * Loader for resource loading process. It's a singleton object.
 * @class
 */
cc.loader = /** @lends cc.loader# */{
    _jsCache: {},//cache for js
    _register: {},//register of loaders
    _langPathCache: {},//cache for lang path
    _aliases: {},//aliases for res url

    resPath: "",//root path of resource
    audioPath: "",//root path of audio
    cache: {},//cache for data loaded

    /**
     * Get XMLHttpRequest.
     * @returns {XMLHttpRequest}
     */
    getXMLHttpRequest: function () {
        return window.XMLHttpRequest ? new window.XMLHttpRequest() : new ActiveXObject("MSXML2.XMLHTTP");
    },

    //@MODE_BEGIN DEV

    _getArgs4Js: function (args) {
        var a0 = args[0], a1 = args[1], a2 = args[2], results = ["", null, null];

        if (args.length === 1) {
            results[1] = a0 instanceof Array ? a0 : [a0];
        } else if (args.length === 2) {
            if (typeof a1 === "function") {
                results[1] = a0 instanceof Array ? a0 : [a0];
                results[2] = a1;
            } else {
                results[0] = a0 || "";
                results[1] = a1 instanceof Array ? a1 : [a1];
            }
        } else if (args.length === 3) {
            results[0] = a0 || "";
            results[1] = a1 instanceof Array ? a1 : [a1];
            results[2] = a2;
        } else throw "arguments error to load js!";
        return results;
    },

    /**
     * Load js files.
     * If the third parameter doesn't exist, then the baseDir turns to be "".
     *
     * @param {string} [baseDir]   The pre path for jsList or the list of js path.
     * @param {array} jsList    List of js path.
     * @param {function} [cb]  Callback function
     * @returns {*}
     */
    loadJs: function (baseDir, jsList, cb) {
        var self = this, localJsCache = self._jsCache,
            args = self._getArgs4Js(arguments);

        var preDir = args[0], list = args[1], callback = args[2];
        if (navigator.userAgent.indexOf("Trident/5") > -1) {
            self._loadJs4Dependency(preDir, list, 0, callback);
        } else {
            cc.async.map(list, function (item, index, cb1) {
                var jsPath = cc.path.join(preDir, item);
                if (localJsCache[jsPath]) return cb1(null);
                self._createScript(jsPath, false, cb1);
            }, callback);
        }
    },
    /**
     * Load js width loading image.
     *
     * @param {string} [baseDir]
     * @param {array} jsList
     * @param {function} [cb]
     */
    loadJsWithImg: function (baseDir, jsList, cb) {
        var self = this, jsLoadingImg = self._loadJsImg(),
            args = self._getArgs4Js(arguments);
        this.loadJs(args[0], args[1], function (err) {
            if (err) throw err;
            jsLoadingImg.parentNode.removeChild(jsLoadingImg);//remove loading gif
            if (args[2]) args[2]();
        });
    },
    _createScript: function (jsPath, isAsync, cb) {
        var d = document, self = this, s = cc.newElement('script');
        s.async = isAsync;
        self._jsCache[jsPath] = true;
        if(cc.game.config["noCache"] && typeof jsPath === "string"){
            if(self._noCacheRex.test(jsPath))
                s.src = jsPath + "&_t=" + (new Date() - 0);
            else
                s.src = jsPath + "?_t=" + (new Date() - 0);
        }else{
            s.src = jsPath;
        }
        cc._addEventListener(s, 'load', function () {
            s.parentNode.removeChild(s);
            this.removeEventListener('load', arguments.callee, false);
            cb();
        }, false);
        cc._addEventListener(s, 'error', function () {
            s.parentNode.removeChild(s);
            cb("Load " + jsPath + " failed!");
        }, false);
        d.body.appendChild(s);
    },
    _loadJs4Dependency: function (baseDir, jsList, index, cb) {
        if (index >= jsList.length) {
            if (cb) cb();
            return;
        }
        var self = this;
        self._createScript(cc.path.join(baseDir, jsList[index]), false, function (err) {
            if (err) return cb(err);
            self._loadJs4Dependency(baseDir, jsList, index + 1, cb);
        });
    },
    _loadJsImg: function () {
        var d = document, jsLoadingImg = d.getElementById("cocos2d_loadJsImg");
        if (!jsLoadingImg) {
            jsLoadingImg = cc.newElement('img');

            if (cc._loadingImage)
                jsLoadingImg.src = cc._loadingImage;

            var canvasNode = d.getElementById(cc.game.config["id"]);
            canvasNode.style.backgroundColor = "black";
            canvasNode.parentNode.appendChild(jsLoadingImg);

            var canvasStyle = getComputedStyle ? getComputedStyle(canvasNode) : canvasNode.currentStyle;
            if (!canvasStyle)
                canvasStyle = {width: canvasNode.width, height: canvasNode.height};
            jsLoadingImg.style.left = canvasNode.offsetLeft + (parseFloat(canvasStyle.width) - jsLoadingImg.width) / 2 + "px";
            jsLoadingImg.style.top = canvasNode.offsetTop + (parseFloat(canvasStyle.height) - jsLoadingImg.height) / 2 + "px";
            jsLoadingImg.style.position = "absolute";
        }
        return jsLoadingImg;
    },
    //@MODE_END DEV

    /**
     * Load a single resource as txt.
     * @param {string} url
     * @param {function} [cb] arguments are : err, txt
     */
    loadTxt: function (url, cb) {
        if (!cc._isNodeJs) {
            var xhr = this.getXMLHttpRequest(),
                errInfo = "load " + url + " failed!";
            xhr.open("GET", url, true);
            if (/msie/i.test(navigator.userAgent) && !/opera/i.test(navigator.userAgent)) {
                // IE-specific logic here
                xhr.setRequestHeader("Accept-Charset", "utf-8");
                xhr.onreadystatechange = function () {
                    if(xhr.readyState === 4)
                        xhr.status === 200 ? cb(null, xhr.responseText) : cb(errInfo);
                };
            } else {
                if (xhr.overrideMimeType) xhr.overrideMimeType("text\/plain; charset=utf-8");
                xhr.onload = function () {
                    if(xhr.readyState === 4)
                        xhr.status === 200 ? cb(null, xhr.responseText) : cb(errInfo);
                };
            }
            xhr.send(null);
        } else {
            var fs = require("fs");
            fs.readFile(url, function (err, data) {
                err ? cb(err) : cb(null, data.toString());
            });
        }
    },
    _loadTxtSync: function (url) {
        if (!cc._isNodeJs) {
            var xhr = this.getXMLHttpRequest();
            xhr.open("GET", url, false);
            if (/msie/i.test(navigator.userAgent) && !/opera/i.test(navigator.userAgent)) {
                // IE-specific logic here
                xhr.setRequestHeader("Accept-Charset", "utf-8");
            } else {
                if (xhr.overrideMimeType) xhr.overrideMimeType("text\/plain; charset=utf-8");
            }
            xhr.send(null);
            if (!xhr.readyState === 4 || xhr.status !== 200) {
                return null;
            }
            return xhr.responseText;
        } else {
            var fs = require("fs");
            return fs.readFileSync(url).toString();
        }
    },

    loadCsb: function(url, cb){
        var xhr = new XMLHttpRequest();
        xhr.open("GET", url, true);
        xhr.responseType = "arraybuffer";

        xhr.onload = function () {
            var arrayBuffer = xhr.response; // Note: not oReq.responseText
            if (arrayBuffer) {
                window.msg = arrayBuffer;
            }
            if(xhr.readyState === 4)
                xhr.status === 200 ? cb(null, xhr.response) : cb("load " + url + " failed!");
        };

        xhr.send(null);
    },

    /**
     * Load a single resource as json.
     * @param {string} url
     * @param {function} [cb] arguments are : err, json
     */
    loadJson: function (url, cb) {
        this.loadTxt(url, function (err, txt) {
            if (err) {
                cb(err);
            }
            else {
                try {
                    var result = JSON.parse(txt);
                }
                catch (e) {
                    throw "parse json [" + url + "] failed : " + e;
                    return;
                }
                cb(null, result);
            }
        });
    },

    _checkIsImageURL: function (url) {
        var ext = /(\.png)|(\.jpg)|(\.bmp)|(\.jpeg)|(\.gif)/.exec(url);
        return (ext != null);
    },
    /**
     * Load a single image.
     * @param {!string} url
     * @param {object} [option]
     * @param {function} callback
     * @returns {Image}
     */
    loadImg: function (url, option, callback) {
        var opt = {
            isCrossOrigin: true
        };
        if (callback !== undefined)
            opt.isCrossOrigin = option.isCrossOrigin === null ? opt.isCrossOrigin : option.isCrossOrigin;
        else if (option !== undefined)
            callback = option;

        var img = this.getRes(url);
        if (img) {
            callback && callback(null, img);
            return img;
        }

        img = new Image();
        if (opt.isCrossOrigin && location.origin !== "file://")
            img.crossOrigin = "Anonymous";

        var loadCallback = function () {
            this.removeEventListener('load', loadCallback, false);
            this.removeEventListener('error', errorCallback, false);

            cc.loader.cache[url] = img;
            if (callback)
                callback(null, img);
        };

        var self = this;
        var errorCallback = function () {
            this.removeEventListener('error', errorCallback, false);

            if(img.crossOrigin && img.crossOrigin.toLowerCase() === "anonymous"){
                opt.isCrossOrigin = false;
                self.release(url);
                cc.loader.loadImg(url, opt, callback);
            }else{
                typeof callback === "function" && callback("load image failed");
            }
        };

        cc._addEventListener(img, "load", loadCallback);
        cc._addEventListener(img, "error", errorCallback);
        img.src = url;
        return img;
    },

    /**
     * Iterator function to load res
     * @param {object} item
     * @param {number} index
     * @param {function} [cb]
     * @returns {*}
     * @private
     */
    _loadResIterator: function (item, index, cb) {
        var self = this, url = null;
        var type = item.type;
        if (type) {
            type = "." + type.toLowerCase();
            url = item.src ? item.src : item.name + type;
        } else {
            url = item;
            type = cc.path.extname(url);
        }

        var obj = self.getRes(url);
        if (obj)
            return cb(null, obj);
        var loader = null;
        if (type) {
            loader = self._register[type.toLowerCase()];
        }
        if (!loader) {
            cc.error("loader for [" + type + "] not exists!");
            return cb();
        }
        var basePath = loader.getBasePath ? loader.getBasePath() : self.resPath;
        var realUrl = self.getUrl(basePath, url);
        if(cc.game.config["noCache"] && typeof realUrl === "string"){
            if(self._noCacheRex.test(realUrl))
                realUrl += "&_t=" + (new Date() - 0);
            else
                realUrl += "?_t=" + (new Date() - 0);
        }
        loader.load(realUrl, url, item, function (err, data) {
            if (err) {
                cc.log(err);
                self.cache[url] = null;
                delete self.cache[url];
                cb();
            } else {
                self.cache[url] = data;
                cb(null, data);
            }
        });
    },
    _noCacheRex: /\?/,

    /**
     * Get url with basePath.
     * @param {string} basePath
     * @param {string} [url]
     * @returns {*}
     */
    getUrl: function (basePath, url) {
        var self = this, langPathCache = self._langPathCache, path = cc.path;
        if (basePath !== undefined && url === undefined) {
            url = basePath;
            var type = path.extname(url);
            type = type ? type.toLowerCase() : "";
            var loader = self._register[type];
            if (!loader)
                basePath = self.resPath;
            else
                basePath = loader.getBasePath ? loader.getBasePath() : self.resPath;
        }
        url = cc.path.join(basePath || "", url);
        if (url.match(/[\/(\\\\)]lang[\/(\\\\)]/i)) {
            if (langPathCache[url])
                return langPathCache[url];
            var extname = path.extname(url) || "";
            url = langPathCache[url] = url.substring(0, url.length - extname.length) + "_" + cc.sys.language + extname;
        }
        return url;
    },

    /**
     * Load resources then call the callback.
     * @param {string} resources
     * @param {function} [option] callback or trigger
     * @param {function|Object} [loadCallback]
     * @return {cc.AsyncPool}
     */
    load : function(resources, option, loadCallback){
        var self = this;
        var len = arguments.length;
        if(len === 0)
            throw "arguments error!";

        if(len === 3){
            if(typeof option === "function"){
                if(typeof loadCallback === "function")
                    option = {trigger : option, cb : loadCallback };
                else
                    option = { cb : option, cbTarget : loadCallback};
            }
        }else if(len === 2){
            if(typeof option === "function")
                option = {cb : option};
        }else if(len === 1){
            option = {};
        }

        if(!(resources instanceof Array))
            resources = [resources];
        var asyncPool = new cc.AsyncPool(
            resources, 0,
            function (value, index, AsyncPoolCallback, aPool) {
                self._loadResIterator(value, index, function (err) {
                    if (err)
                        return AsyncPoolCallback(err);
                    var arr = Array.prototype.slice.call(arguments, 1);
                    if (option.trigger)
                        option.trigger.call(option.triggerTarget, arr[0], aPool.size, aPool.finishedSize);   //call trigger
                    AsyncPoolCallback(null, arr[0]);
                });
            },
            option.cb, option.cbTarget);
        asyncPool.flow();
        return asyncPool;
    },

    _handleAliases: function (fileNames, cb) {
        var self = this, aliases = self._aliases;
        var resList = [];
        for (var key in fileNames) {
            var value = fileNames[key];
            aliases[key] = value;
            resList.push(value);
        }
        this.load(resList, cb);
    },

    /**
     * <p>
     *     Loads alias map from the contents of a filename.                                        <br/>
     *                                                                                                                 <br/>
     *     @note The plist file name should follow the format below:                                                   <br/>
     *     <?xml version="1.0" encoding="UTF-8"?>                                                                      <br/>
     *         <!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd">  <br/>
     *             <plist version="1.0">                                                                               <br/>
     *                 <dict>                                                                                          <br/>
     *                     <key>filenames</key>                                                                        <br/>
     *                     <dict>                                                                                      <br/>
     *                         <key>sounds/click.wav</key>                                                             <br/>
     *                         <string>sounds/click.caf</string>                                                       <br/>
     *                         <key>sounds/endgame.wav</key>                                                           <br/>
     *                         <string>sounds/endgame.caf</string>                                                     <br/>
     *                         <key>sounds/gem-0.wav</key>                                                             <br/>
     *                         <string>sounds/gem-0.caf</string>                                                       <br/>
     *                     </dict>                                                                                     <br/>
     *                     <key>metadata</key>                                                                         <br/>
     *                     <dict>                                                                                      <br/>
     *                         <key>version</key>                                                                      <br/>
     *                         <integer>1</integer>                                                                    <br/>
     *                     </dict>                                                                                     <br/>
     *                 </dict>                                                                                         <br/>
     *              </plist>                                                                                           <br/>
     * </p>
     * @param {String} url  The plist file name.
     * @param {Function} [callback]
     */
    loadAliases: function (url, callback) {
        var self = this, dict = self.getRes(url);
        if (!dict) {
            self.load(url, function (err, results) {
                self._handleAliases(results[0]["filenames"], callback);
            });
        } else
            self._handleAliases(dict["filenames"], callback);
    },

    /**
     * Register a resource loader into loader.
     * @param {string} extNames
     * @param {function} loader
     */
    register: function (extNames, loader) {
        if (!extNames || !loader) return;
        var self = this;
        if (typeof extNames === "string")
            return this._register[extNames.trim().toLowerCase()] = loader;
        for (var i = 0, li = extNames.length; i < li; i++) {
            self._register["." + extNames[i].trim().toLowerCase()] = loader;
        }
    },

    /**
     * Get resource data by url.
     * @param url
     * @returns {*}
     */
    getRes: function (url) {
        return this.cache[url] || this.cache[this._aliases[url]];
    },

    /**
     * Release the cache of resource by url.
     * @param url
     */
    release: function (url) {
        var cache = this.cache, aliases = this._aliases;
        delete cache[url];
        delete cache[aliases[url]];
        delete aliases[url];
    },

    /**
     * Resource cache of all resources.
     */
    releaseAll: function () {
        var locCache = this.cache, aliases = this._aliases;
        for (var key in locCache)
            delete locCache[key];
        for (var key in aliases)
            delete aliases[key];
    }
};
//+++++++++++++++++++++++++something about loader end+++++++++++++++++++++++++++++

/**
 * A string tool to construct a string with format string.
 * for example:
 *      cc.formatStr("a: %d, b: %b", a, b);
 *      cc.formatStr(a, b, c);
 * @returns {String}
 */
cc.formatStr = function(){
    var args = arguments;
    var l = args.length;
    if(l < 1)
        return "";

    var str = args[0];
    var needToFormat = true;
    if(typeof str === "object"){
        needToFormat = false;
    }
    for(var i = 1; i < l; ++i){
        var arg = args[i];
        if(needToFormat){
            while(true){
                var result = null;
                if(typeof arg === "number"){
                    result = str.match(/(%d)|(%s)/);
                    if(result){
                        str = str.replace(/(%d)|(%s)/, arg);
                        break;
                    }
                }
                result = str.match(/%s/);
                if(result)
                    str = str.replace(/%s/, arg);
                else
                    str += "    " + arg;
                break;
            }
        }else
            str += "    " + arg;
    }
    return str;
};


//+++++++++++++++++++++++++something about window events begin+++++++++++++++++++++++++++
(function () {
    var win = window, hidden, visibilityChange, _undef = "undefined";
    if (!cc.isUndefined(document.hidden)) {
        hidden = "hidden";
        visibilityChange = "visibilitychange";
    } else if (!cc.isUndefined(document.mozHidden)) {
        hidden = "mozHidden";
        visibilityChange = "mozvisibilitychange";
    } else if (!cc.isUndefined(document.msHidden)) {
        hidden = "msHidden";
        visibilityChange = "msvisibilitychange";
    } else if (!cc.isUndefined(document.webkitHidden)) {
        hidden = "webkitHidden";
        visibilityChange = "webkitvisibilitychange";
    }

    var onHidden = function () {
        if (cc.eventManager && cc.game._eventHide)
            cc.eventManager.dispatchEvent(cc.game._eventHide);
    };
    var onShow = function () {
        if (cc.eventManager && cc.game._eventShow)
            cc.eventManager.dispatchEvent(cc.game._eventShow);

        if(cc.game._intervalId){
            window.cancelAnimationFrame(cc.game._intervalId);

            cc.game._runMainLoop();
        }
    };

    if (hidden) {
        cc._addEventListener(document, visibilityChange, function () {
            if (document[hidden]) onHidden();
            else onShow();
        }, false);
    } else {
        cc._addEventListener(win, "blur", onHidden, false);
        cc._addEventListener(win, "focus", onShow, false);
    }

    if(navigator.userAgent.indexOf("MicroMessenger") > -1){
        win.onfocus = function(){ onShow() };
    }

    if ("onpageshow" in window && "onpagehide" in window) {
        cc._addEventListener(win, "pagehide", onHidden, false);
        cc._addEventListener(win, "pageshow", onShow, false);
    }
    win = null;
    visibilityChange = null;
})();
//+++++++++++++++++++++++++something about window events end+++++++++++++++++++++++++++++

//+++++++++++++++++++++++++something about log start++++++++++++++++++++++++++++

//to make sure the cc.log, cc.warn, cc.error and cc.assert would not throw error before init by debugger mode.

cc.log = cc.warn = cc.error = cc.assert = function () {
};

//+++++++++++++++++++++++++something about log end+++++++++++++++++++++++++++++

/**
 * create a webgl context
 * @param {HTMLCanvasElement} canvas
 * @param {Object} opt_attribs
 * @return {WebGLRenderingContext}
 */
cc.create3DContext = function (canvas, opt_attribs) {
    var names = ["webgl", "experimental-webgl", "webkit-3d", "moz-webgl"];
    var context = null;
    for (var ii = 0; ii < names.length; ++ii) {
        try {
            context = canvas.getContext(names[ii], opt_attribs);
        } catch (e) {
        }
        if (context) {
            break;
        }
    }
    return context;
};
//+++++++++++++++++++++++++something about sys begin+++++++++++++++++++++++++++++
cc._initSys = function (config, CONFIG_KEY) {
    /**
     * Canvas of render type
     * @constant
     * @type {Number}
     */
    cc._RENDER_TYPE_CANVAS = 0;

    /**
     * WebGL of render type
     * @constant
     * @type {Number}
     */
    cc._RENDER_TYPE_WEBGL = 1;

    /**
     * System variables
     * @namespace
     * @name cc.sys
     */
    cc.sys = {};
    var sys = cc.sys;

    /**
     * English language code
     * @memberof cc.sys
     * @name LANGUAGE_ENGLISH
     * @constant
     * @type {Number}
     */
    sys.LANGUAGE_ENGLISH = "en";

    /**
     * Chinese language code
     * @memberof cc.sys
     * @name LANGUAGE_CHINESE
     * @constant
     * @type {Number}
     */
    sys.LANGUAGE_CHINESE = "zh";

    /**
     * French language code
     * @memberof cc.sys
     * @name LANGUAGE_FRENCH
     * @constant
     * @type {Number}
     */
    sys.LANGUAGE_FRENCH = "fr";

    /**
     * Italian language code
     * @memberof cc.sys
     * @name LANGUAGE_ITALIAN
     * @constant
     * @type {Number}
     */
    sys.LANGUAGE_ITALIAN = "it";

    /**
     * German language code
     * @memberof cc.sys
     * @name LANGUAGE_GERMAN
     * @constant
     * @type {Number}
     */
    sys.LANGUAGE_GERMAN = "de";

    /**
     * Spanish language code
     * @memberof cc.sys
     * @name LANGUAGE_SPANISH
     * @constant
     * @type {Number}
     */
    sys.LANGUAGE_SPANISH = "es";

    /**
     * Spanish language code
     * @memberof cc.sys
     * @name LANGUAGE_DUTCH
     * @constant
     * @type {Number}
     */
    sys.LANGUAGE_DUTCH = "du";

    /**
     * Russian language code
     * @memberof cc.sys
     * @name LANGUAGE_RUSSIAN
     * @constant
     * @type {Number}
     */
    sys.LANGUAGE_RUSSIAN = "ru";

    /**
     * Korean language code
     * @memberof cc.sys
     * @name LANGUAGE_KOREAN
     * @constant
     * @type {Number}
     */
    sys.LANGUAGE_KOREAN = "ko";

    /**
     * Japanese language code
     * @memberof cc.sys
     * @name LANGUAGE_JAPANESE
     * @constant
     * @type {Number}
     */
    sys.LANGUAGE_JAPANESE = "ja";

    /**
     * Hungarian language code
     * @memberof cc.sys
     * @name LANGUAGE_HUNGARIAN
     * @constant
     * @type {Number}
     */
    sys.LANGUAGE_HUNGARIAN = "hu";

    /**
     * Portuguese language code
     * @memberof cc.sys
     * @name LANGUAGE_PORTUGUESE
     * @constant
     * @type {Number}
     */
    sys.LANGUAGE_PORTUGUESE = "pt";

    /**
     * Arabic language code
     * @memberof cc.sys
     * @name LANGUAGE_ARABIC
     * @constant
     * @type {Number}
     */
    sys.LANGUAGE_ARABIC = "ar";

    /**
     * Norwegian language code
     * @memberof cc.sys
     * @name LANGUAGE_NORWEGIAN
     * @constant
     * @type {Number}
     */
    sys.LANGUAGE_NORWEGIAN = "no";

    /**
     * Polish language code
     * @memberof cc.sys
     * @name LANGUAGE_POLISH
     * @constant
     * @type {Number}
     */
    sys.LANGUAGE_POLISH = "pl";

    /**
     * @memberof cc.sys
     * @name OS_IOS
     * @constant
     * @type {string}
     */
    sys.OS_IOS = "iOS";
    /**
     * @memberof cc.sys
     * @name OS_ANDROID
     * @constant
     * @type {string}
     */
    sys.OS_ANDROID = "Android";
    /**
     * @memberof cc.sys
     * @name OS_WINDOWS
     * @constant
     * @type {string}
     */
    sys.OS_WINDOWS = "Windows";
    /**
     * @memberof cc.sys
     * @name OS_MARMALADE
     * @constant
     * @type {string}
     */
    sys.OS_MARMALADE = "Marmalade";
    /**
     * @memberof cc.sys
     * @name OS_LINUX
     * @constant
     * @type {string}
     */
    sys.OS_LINUX = "Linux";
    /**
     * @memberof cc.sys
     * @name OS_BADA
     * @constant
     * @type {string}
     */
    sys.OS_BADA = "Bada";
    /**
     * @memberof cc.sys
     * @name OS_BLACKBERRY
     * @constant
     * @type {string}
     */
    sys.OS_BLACKBERRY = "Blackberry";
    /**
     * @memberof cc.sys
     * @name OS_OSX
     * @constant
     * @type {string}
     */
    sys.OS_OSX = "OS X";
    /**
     * @memberof cc.sys
     * @name OS_WP8
     * @constant
     * @type {string}
     */
    sys.OS_WP8 = "WP8";
    /**
     * @memberof cc.sys
     * @name OS_WINRT
     * @constant
     * @type {string}
     */
    sys.OS_WINRT = "WINRT";
    /**
     * @memberof cc.sys
     * @name OS_UNKNOWN
     * @constant
     * @type {string}
     */
    sys.OS_UNKNOWN = "Unknown";

    /**
     * @memberof cc.sys
     * @name UNKNOWN
     * @constant
     * @default
     * @type {Number}
     */
    sys.UNKNOWN = 0;
    /**
     * @memberof cc.sys
     * @name IOS
     * @constant
     * @default
     * @type {Number}
     */
    sys.IOS = 1;
    /**
     * @memberof cc.sys
     * @name ANDROID
     * @constant
     * @default
     * @type {Number}
     */
    sys.ANDROID = 2;
    /**
     * @memberof cc.sys
     * @name WIN32
     * @constant
     * @default
     * @type {Number}
     */
    sys.WIN32 = 3;
    /**
     * @memberof cc.sys
     * @name MARMALADE
     * @constant
     * @default
     * @type {Number}
     */
    sys.MARMALADE = 4;
    /**
     * @memberof cc.sys
     * @name LINUX
     * @constant
     * @default
     * @type {Number}
     */
    sys.LINUX = 5;
    /**
     * @memberof cc.sys
     * @name BADA
     * @constant
     * @default
     * @type {Number}
     */
    sys.BADA = 6;
    /**
     * @memberof cc.sys
     * @name BLACKBERRY
     * @constant
     * @default
     * @type {Number}
     */
    sys.BLACKBERRY = 7;
    /**
     * @memberof cc.sys
     * @name MACOS
     * @constant
     * @default
     * @type {Number}
     */
    sys.MACOS = 8;
    /**
     * @memberof cc.sys
     * @name NACL
     * @constant
     * @default
     * @type {Number}
     */
    sys.NACL = 9;
    /**
     * @memberof cc.sys
     * @name EMSCRIPTEN
     * @constant
     * @default
     * @type {Number}
     */
    sys.EMSCRIPTEN = 10;
    /**
     * @memberof cc.sys
     * @name TIZEN
     * @constant
     * @default
     * @type {Number}
     */
    sys.TIZEN = 11;
    /**
     * @memberof cc.sys
     * @name QT5
     * @constant
     * @default
     * @type {Number}
     */
    sys.QT5 = 12;
    /**
     * @memberof cc.sys
     * @name WP8
     * @constant
     * @default
     * @type {Number}
     */
    sys.WP8 = 13;
    /**
     * @memberof cc.sys
     * @name WINRT
     * @constant
     * @default
     * @type {Number}
     */
    sys.WINRT = 14;
    /**
     * @memberof cc.sys
     * @name MOBILE_BROWSER
     * @constant
     * @default
     * @type {Number}
     */
    sys.MOBILE_BROWSER = 100;
    /**
     * @memberof cc.sys
     * @name DESKTOP_BROWSER
     * @constant
     * @default
     * @type {Number}
     */
    sys.DESKTOP_BROWSER = 101;

    sys.BROWSER_TYPE_WECHAT = "wechat";
    sys.BROWSER_TYPE_ANDROID = "androidbrowser";
    sys.BROWSER_TYPE_IE = "ie";
    sys.BROWSER_TYPE_QQ = "qqbrowser";
    sys.BROWSER_TYPE_MOBILE_QQ = "mqqbrowser";
    sys.BROWSER_TYPE_UC = "ucbrowser";
    sys.BROWSER_TYPE_360 = "360browser";
    sys.BROWSER_TYPE_BAIDU_APP = "baiduboxapp";
    sys.BROWSER_TYPE_BAIDU = "baidubrowser";
    sys.BROWSER_TYPE_MAXTHON = "maxthon";
    sys.BROWSER_TYPE_OPERA = "opera";
    sys.BROWSER_TYPE_OUPENG = "oupeng";
    sys.BROWSER_TYPE_MIUI = "miuibrowser";
    sys.BROWSER_TYPE_FIREFOX = "firefox";
    sys.BROWSER_TYPE_SAFARI = "safari";
    sys.BROWSER_TYPE_CHROME = "chrome";
    sys.BROWSER_TYPE_LIEBAO = "liebao";
    sys.BROWSER_TYPE_QZONE = "qzone";
    sys.BROWSER_TYPE_SOUGOU = "sogou";
    sys.BROWSER_TYPE_UNKNOWN = "unknown";

    /**
     * Is native ? This is set to be true in jsb auto.
     * @memberof cc.sys
     * @name isNative
     * @type {Boolean}
     */
    sys.isNative = false;

    var win = window, nav = win.navigator, doc = document, docEle = doc.documentElement;
    var ua = nav.userAgent.toLowerCase();

    /**
     * Indicate whether system is mobile system
     * @memberof cc.sys
     * @name isMobile
     * @type {Boolean}
     */
    sys.isMobile = ua.indexOf('mobile') !== -1 || ua.indexOf('android') !== -1;

    /**
     * Indicate the running platform
     * @memberof cc.sys
     * @name platform
     * @type {Number}
     */
    sys.platform = sys.isMobile ? sys.MOBILE_BROWSER : sys.DESKTOP_BROWSER;

    var currLanguage = nav.language;
    currLanguage = currLanguage ? currLanguage : nav.browserLanguage;
    currLanguage = currLanguage ? currLanguage.split("-")[0] : sys.LANGUAGE_ENGLISH;

    /**
     * Indicate the current language of the running system
     * @memberof cc.sys
     * @name language
     * @type {String}
     */
    sys.language = currLanguage;

    var browserType = sys.BROWSER_TYPE_UNKNOWN;
    var browserTypes = ua.match(/sogou|qzone|liebao|micromessenger|qqbrowser|ucbrowser|360 aphone|360browser|baiduboxapp|baidubrowser|maxthon|trident|oupeng|opera|miuibrowser|firefox/i)
        || ua.match(/chrome|safari/i);
    if (browserTypes && browserTypes.length > 0) {
        browserType = browserTypes[0];
        if (browserType === 'micromessenger') {
            browserType = sys.BROWSER_TYPE_WECHAT;
        } else if (browserType === "safari" && (ua.match(/android.*applewebkit/)))
            browserType = sys.BROWSER_TYPE_ANDROID;
        else if (browserType === "trident") browserType = sys.BROWSER_TYPE_IE;
        else if (browserType === "360 aphone") browserType = sys.BROWSER_TYPE_360;
    }else if(ua.indexOf("iphone") && ua.indexOf("mobile")){
        browserType = "safari";
    }
    /**
     * Indicate the running browser type
     * @memberof cc.sys
     * @name browserType
     * @type {String}
     */
    sys.browserType = browserType;

    // Get the os of system
    var iOS = ( ua.match(/(iPad|iPhone|iPod)/i) ? true : false );
    var isAndroid = ua.match(/android/i) || nav.platform.match(/android/i) ? true : false;
    var osName = sys.OS_UNKNOWN;
    if (nav.appVersion.indexOf("Win") !== -1) osName = sys.OS_WINDOWS;
    else if (iOS) osName = sys.OS_IOS;
    else if (nav.appVersion.indexOf("Mac") !== -1) osName = sys.OS_OSX;
    else if (nav.appVersion.indexOf("X11") !== -1 && nav.appVersion.indexOf("Linux") === -1) osName = sys.OS_UNIX;
    else if (isAndroid) osName = sys.OS_ANDROID;
    else if (nav.appVersion.indexOf("Linux") !== -1) osName = sys.OS_LINUX;

    /**
     * Indicate the running os name
     * @memberof cc.sys
     * @name os
     * @type {String}
     */
    sys.os = osName;

    var multipleAudioWhiteList = [
        sys.BROWSER_TYPE_BAIDU, sys.BROWSER_TYPE_OPERA, sys.BROWSER_TYPE_FIREFOX, sys.BROWSER_TYPE_CHROME, sys.BROWSER_TYPE_BAIDU_APP,
        sys.BROWSER_TYPE_SAFARI, sys.BROWSER_TYPE_UC, sys.BROWSER_TYPE_QQ, sys.BROWSER_TYPE_MOBILE_QQ, sys.BROWSER_TYPE_IE
    ];

    sys._supportMultipleAudio = multipleAudioWhiteList.indexOf(sys.browserType) > -1;


    //++++++++++++++++++something about cc._renderTYpe and cc._supportRender begin++++++++++++++++++++++++++++

    (function(sys, config){
        var userRenderMode = config[CONFIG_KEY.renderMode] - 0;
        if(isNaN(userRenderMode) || userRenderMode > 2 || userRenderMode < 0)
            userRenderMode = 0;
        var shieldOs = [sys.OS_ANDROID];
        var shieldBrowser = [];
        var tmpCanvas = cc.newElement("canvas");
        cc._renderType = cc._RENDER_TYPE_CANVAS;
        cc._supportRender = false;

        var supportWebGL = win.WebGLRenderingContext;

        if(userRenderMode === 2 || (userRenderMode === 0 && supportWebGL && shieldOs.indexOf(sys.os) === -1 && shieldBrowser.indexOf(sys.browserType) === -1))
            try{
                var context = cc.create3DContext(tmpCanvas, {'stencil': true, 'preserveDrawingBuffer': true });
                if(context){
                    cc._renderType = cc._RENDER_TYPE_WEBGL;
                    cc._supportRender = true;
                }
            }catch(e){}

        if(userRenderMode === 1 || (userRenderMode === 0 && cc._supportRender === false))
            try {
                tmpCanvas.getContext("2d");
                cc._renderType = cc._RENDER_TYPE_CANVAS;
                cc._supportRender = true;
            } catch (e) {}
    })(sys, config);

    sys._canUseCanvasNewBlendModes = function(){
        var canvas = document.createElement('canvas');
        canvas.width = 1;
        canvas.height = 1;
        var context = canvas.getContext('2d');
        context.fillStyle = '#000';
        context.fillRect(0,0,1,1);
        context.globalCompositeOperation = 'multiply';

        var canvas2 = document.createElement('canvas');
        canvas2.width = 1;
        canvas2.height = 1;
        var context2 = canvas2.getContext('2d');
        context2.fillStyle = '#fff';
        context2.fillRect(0,0,1,1);

        context.drawImage(canvas2, 0, 0, 1, 1);

        return context.getImageData(0,0,1,1).data[0] === 0;
    };

    //Whether or not the Canvas BlendModes are supported.
    sys._supportCanvasNewBlendModes = sys._canUseCanvasNewBlendModes();

    //++++++++++++++++++something about cc._renderType and cc._supportRender end++++++++++++++++++++++++++++++

    // check if browser supports Web Audio
    // check Web Audio's context
    try {
        sys._supportWebAudio = !!(win.AudioContext || win.webkitAudioContext || win.mozAudioContext);
    } catch (e) {
        sys._supportWebAudio = false;
    }

    /**
     * cc.sys.localStorage is a local storage component.
     * @memberof cc.sys
     * @name localStorage
     * @type {Object}
     */
    try {
        var localStorage = sys.localStorage = win.localStorage;
        localStorage.setItem("storage", "");
        localStorage.removeItem("storage");
        localStorage = null;
    } catch (e) {
        if (e.name === "SECURITY_ERR" || e.name === "QuotaExceededError") {
            cc.warn("Warning: localStorage isn't enabled. Please confirm browser cookie or privacy option");
        }
        sys.localStorage = function () {
        };
    }

    var capabilities = sys.capabilities = {"canvas": true};
    if (cc._renderType === cc._RENDER_TYPE_WEBGL)
        capabilities["opengl"] = true;
    if (docEle['ontouchstart'] !== undefined || doc['ontouchstart'] !== undefined || nav.msPointerEnabled)
        capabilities["touches"] = true;
    if (docEle['onmouseup'] !== undefined)
        capabilities["mouse"] = true;
    if (docEle['onkeyup'] !== undefined)
        capabilities["keyboard"] = true;
    if (win.DeviceMotionEvent || win.DeviceOrientationEvent)
        capabilities["accelerometer"] = true;

    /**
     * Forces the garbage collection, only available in JSB
     * @memberof cc.sys
     * @name garbageCollect
     * @function
     */
    sys.garbageCollect = function () {
        // N/A in cocos2d-html5
    };

    /**
     * Dumps rooted objects, only available in JSB
     * @memberof cc.sys
     * @name dumpRoot
     * @function
     */
    sys.dumpRoot = function () {
        // N/A in cocos2d-html5
    };

    /**
     * Restart the JS VM, only available in JSB
     * @memberof cc.sys
     * @name restartVM
     * @function
     */
    sys.restartVM = function () {
        // N/A in cocos2d-html5
    };

    /**
     * Clean a script in the JS VM, only available in JSB
     * @memberof cc.sys
     * @name cleanScript
     * @param {String} jsfile
     * @function
     */
    sys.cleanScript = function (jsfile) {
        // N/A in cocos2d-html5
    };

    /**
     * Dump system informations
     * @memberof cc.sys
     * @name dump
     * @function
     */
    sys.dump = function () {
        var self = this;
        var str = "";
        str += "isMobile : " + self.isMobile + "\r\n";
        str += "language : " + self.language + "\r\n";
        str += "browserType : " + self.browserType + "\r\n";
        str += "capabilities : " + JSON.stringify(self.capabilities) + "\r\n";
        str += "os : " + self.os + "\r\n";
        str += "platform : " + self.platform + "\r\n";
        cc.log(str);
    }

    /**
     * Open a url in browser
     * @memberof cc.sys
     * @name openURL
     * @param {String} url
     */
    sys.openURL = function(url){
        window.open(url);
    }
};

//+++++++++++++++++++++++++something about sys end+++++++++++++++++++++++++++++

//+++++++++++++++++++++++++something about CCGame begin+++++++++++++++++++++++++++

/**
 * Device oriented vertically, home button on the bottom
 * @constant
 * @type {Number}
 */
cc.ORIENTATION_PORTRAIT = 0;

/**
 * Device oriented vertically, home button on the top
 * @constant
 * @type {Number}
 */
cc.ORIENTATION_PORTRAIT_UPSIDE_DOWN = 1;

/**
 * Device oriented horizontally, home button on the right
 * @constant
 * @type {Number}
 */
cc.ORIENTATION_LANDSCAPE_LEFT = 2;

/**
 * Device oriented horizontally, home button on the left
 * @constant
 * @type {Number}
 */
cc.ORIENTATION_LANDSCAPE_RIGHT = 3;

/**
 * drawing primitive of game engine
 * @type {cc.DrawingPrimitive}
 */
cc._drawingUtil = null;

/**
 * main Canvas 2D/3D Context of game engine
 * @type {CanvasRenderingContext2D|WebGLRenderingContext}
 */
cc._renderContext = null;

/**
 * main Canvas of game engine
 * @type {HTMLCanvasElement}
 */
cc._canvas = null;

/**
 * This Div element contain all game canvas
 * @type {HTMLDivElement}
 */
cc._gameDiv = null;

cc._rendererInitialized = false;
/**
 * <p>
 *   setup game main canvas,renderContext,gameDiv and drawingUtil with argument  <br/>
 *   <br/>
 *   can receive follow type of arguemnt: <br/>
 *      - empty: create a canvas append to document's body, and setup other option    <br/>
 *      - string: search the element by document.getElementById(),    <br/>
 *          if this element is HTMLCanvasElement, set this element as main canvas of engine, and set it's ParentNode as cc._gameDiv.<br/>
 *          if this element is HTMLDivElement, set it's ParentNode to cc._gameDiv， and create a canvas as main canvas of engine.   <br/>
 * </p>
 * @function
 * @example
 * //setup with null
 * cc._setup();
 *
 * // setup with HTMLCanvasElement, gameCanvas is Canvas element
 * // declare like this: <canvas id="gameCanvas" width="800" height="450"></canvas>
 * cc._setup("gameCanvas");
 *
 * //setup with HTMLDivElement, gameDiv is Div element
 * // declare like this: <div id="Cocos2dGameContainer" width="800" height="450"></div>
 * cc._setup("Cocos2dGameContainer");
 */
cc._setupCalled = false;
cc._setup = function (el, width, height) {
    // Avoid setup to be called twice.
    if (cc._setupCalled) return;
    else cc._setupCalled = true;
    var win = window;
    var element = cc.$(el) || cc.$('#' + el);
    var localCanvas, localContainer, localConStyle;

    cc.game._setAnimFrame();

    if (element.tagName === "CANVAS") {
        width = width || element.width;
        height = height || element.height;

        //it is already a canvas, we wrap it around with a div
        localContainer = cc.container = cc.newElement("DIV");
        localCanvas = cc._canvas = element;
        localCanvas.parentNode.insertBefore(localContainer, localCanvas);
        localCanvas.appendTo(localContainer);
        localContainer.setAttribute('id', 'Cocos2dGameContainer');
    } else {//we must make a new canvas and place into this element
        if (element.tagName !== "DIV") {
            cc.log("Warning: target element is not a DIV or CANVAS");
        }
        width = width || element.clientWidth;
        height = height || element.clientHeight;
        localContainer = cc.container = element;
        localCanvas = cc._canvas = cc.$(cc.newElement("CANVAS"));
        element.appendChild(localCanvas);
    }

    localCanvas.addClass("gameCanvas");
    localCanvas.setAttribute("width", width || 480);
    localCanvas.setAttribute("height", height || 320);
    localCanvas.setAttribute("tabindex", 99);
    localCanvas.style.outline = "none";
    localConStyle = localContainer.style;
    localConStyle.width = (width || 480) + "px";
    localConStyle.height = (height || 320) + "px";
    localConStyle.margin = "0 auto";

    localConStyle.position = 'relative';
    localConStyle.overflow = 'hidden';
    localContainer.top = '100%';

    if (cc._renderType === cc._RENDER_TYPE_WEBGL)
        cc._renderContext = cc.webglContext = cc.create3DContext(localCanvas, {
            'stencil': true,
            'preserveDrawingBuffer': true,
            'antialias': !cc.sys.isMobile,
            'alpha': false
        });
    if (cc._renderContext) {
        win.gl = cc._renderContext; // global variable declared in CCMacro.js
        cc._drawingUtil = new cc.DrawingPrimitiveWebGL(cc._renderContext);
        cc._rendererInitialized = true;
        cc.textureCache._initializingRenderer();
        cc.shaderCache._init();
    } else {
        cc._renderContext = new cc.CanvasContextWrapper(localCanvas.getContext("2d"));
        cc._drawingUtil = cc.DrawingPrimitiveCanvas ? new cc.DrawingPrimitiveCanvas(cc._renderContext) : null;
    }

    cc._gameDiv = localContainer;
    cc.log(cc.ENGINE_VERSION);
    cc._setContextMenuEnable(false);

    if (cc.sys.isMobile) {
        var fontStyle = cc.newElement("style");
        fontStyle.type = "text/css";
        document.body.appendChild(fontStyle);

        fontStyle.textContent = "body,canvas,div{ -moz-user-select: none;-webkit-user-select: none;-ms-user-select: none;-khtml-user-select: none;"
            + "-webkit-tap-highlight-color:rgba(0,0,0,0);}";
    }

    // Init singletons

    /**
     * @type {cc.EGLView}
     * @name cc.view
     * cc.view is the shared view object.
     */
    cc.view = cc.EGLView._getInstance();
    // register system events
    cc.inputManager.registerSystemEvent(cc._canvas);

    /**
     * @type {cc.Director}
     * @name cc.director
     */
    cc.director = cc.Director._getInstance();
    if (cc.director.setOpenGLView)
        cc.director.setOpenGLView(cc.view);
    /**
     * @type {cc.Size}
     * @name cc.winSize
     * cc.winSize is the alias object for the size of the current game window.
     */
    cc.winSize = cc.director.getWinSize();

    // Parsers
    cc.saxParser = new cc.SAXParser();
    /**
     * @type {cc.PlistParser}
     * @name cc.plistParser
     * A Plist Parser
     */
    cc.plistParser = new cc.PlistParser();
};

cc._checkWebGLRenderMode = function () {
    if (cc._renderType !== cc._RENDER_TYPE_WEBGL)
        throw "This feature supports WebGL render mode only.";
};

cc._isContextMenuEnable = false;
/**
 * enable/disable contextMenu for Canvas
 * @param {Boolean} enabled
 */
cc._setContextMenuEnable = function (enabled) {
    cc._isContextMenuEnable = enabled;
    cc._canvas.oncontextmenu = function () {
        if (!cc._isContextMenuEnable) return false;
    };
};

/**
 * An object to boot the game.
 * @class
 * @name cc.game
 */
cc.game = /** @lends cc.game# */{
    DEBUG_MODE_NONE: 0,
    DEBUG_MODE_INFO: 1,
    DEBUG_MODE_WARN: 2,
    DEBUG_MODE_ERROR: 3,
    DEBUG_MODE_INFO_FOR_WEB_PAGE: 4,
    DEBUG_MODE_WARN_FOR_WEB_PAGE: 5,
    DEBUG_MODE_ERROR_FOR_WEB_PAGE: 6,

    EVENT_HIDE: "game_on_hide",
    EVENT_SHOW: "game_on_show",
    _eventHide: null,
    _eventShow: null,
    _onBeforeStartArr: [],

    /**
     * Key of config
     * @constant
     * @type {Object}
     */
    CONFIG_KEY: {
        engineDir: "engineDir",
        dependencies: "dependencies",
        debugMode: "debugMode",
        showFPS: "showFPS",
        frameRate: "frameRate",
        id: "id",
        renderMode: "renderMode",
        jsList: "jsList",
        classReleaseMode: "classReleaseMode"
    },

    _prepareCalled: false,//whether the prepare function has been called
    _prepared: false,//whether the engine has prepared
    _paused: true,//whether the game is paused

    _intervalId: null,//interval target of main
    
    _lastTime: null,
    _frameTime: null,

    /**
     * Config of game
     * @type {Object}
     */
    config: null,

    /**
     * Callback when the scripts of engine have been load.
     * @type {Function}
     */
    onStart: null,

    /**
     * Callback when game exits.
     * @type {Function}
     */
    onStop: null,

    /**
     * Set frameRate of game.
     * @param frameRate
     */
    setFrameRate: function (frameRate) {
        var self = this, config = self.config, CONFIG_KEY = self.CONFIG_KEY;
        config[CONFIG_KEY.frameRate] = frameRate;
        if (self._intervalId)
            window.cancelAnimationFrame(self._intervalId);
        self._paused = true;
        self._setAnimFrame();
        self._runMainLoop();
    },
    _setAnimFrame: function () {
        this._lastTime = new Date();
        this._frameTime = 1000 / cc.game.config[cc.game.CONFIG_KEY.frameRate];
        if((cc.sys.os === cc.sys.OS_IOS && cc.sys.browserType === cc.sys.BROWSER_TYPE_WECHAT) || cc.game.config[cc.game.CONFIG_KEY.frameRate] !== 60) {
            window.requestAnimFrame = this._stTime;
            window.cancelAnimationFrame = this._ctTime;
        }
        else {
            window.requestAnimFrame = window.requestAnimationFrame ||
            window.webkitRequestAnimationFrame ||
            window.mozRequestAnimationFrame ||
            window.oRequestAnimationFrame ||
            window.msRequestAnimationFrame ||
            this._stTime;
            window.cancelAnimationFrame = window.cancelAnimationFrame ||
            window.cancelRequestAnimationFrame ||
            window.msCancelRequestAnimationFrame ||
            window.mozCancelRequestAnimationFrame ||
            window.oCancelRequestAnimationFrame ||
            window.webkitCancelRequestAnimationFrame ||
            window.msCancelAnimationFrame ||
            window.mozCancelAnimationFrame ||
            window.webkitCancelAnimationFrame ||
            window.oCancelAnimationFrame ||
            this._ctTime;
        }
    },
    _stTime: function(callback){
        var currTime = new Date().getTime();
        var timeToCall = Math.max(0, cc.game._frameTime - (currTime - cc.game._lastTime));
        var id = window.setTimeout(function() { callback(); },
            timeToCall);
        cc.game._lastTime = currTime + timeToCall;
        return id;
    },
    _ctTime: function(id){
        window.clearTimeout(id);
    },
    //Run game.
    _runMainLoop: function () {
        var self = this, callback, config = self.config, CONFIG_KEY = self.CONFIG_KEY,
            director = cc.director;

        director.setDisplayStats(config[CONFIG_KEY.showFPS]);

        callback = function () {
            if (!self._paused) {
                director.mainLoop();
                if(self._intervalId)
                    window.cancelAnimationFrame(self._intervalId);
                self._intervalId = window.requestAnimFrame(callback);
            }
        };

        window.requestAnimFrame(callback);
        self._paused = false;
    },

    /**
     * Restart game.
     */
    restart: function () {
        cc.director.popToSceneStackLevel(0);
        // Clean up audio
        cc.audioEngine && cc.audioEngine.end();

        cc.game.onStart();
    },

    /**
     * Run game.
     */
    run: function (id) {
        var self = this;
        var _run = function () {
            if (id) {
                self.config[self.CONFIG_KEY.id] = id;
            }
            if (!self._prepareCalled) {
                self.prepare(function () {
                    self._prepared = true;
                });
            }
            if (cc._supportRender) {
                self._checkPrepare = setInterval(function () {
                    if (self._prepared) {
                        cc._setup(self.config[self.CONFIG_KEY.id]);
                        self._runMainLoop();
                        self._eventHide = self._eventHide || new cc.EventCustom(self.EVENT_HIDE);
                        self._eventHide.setUserData(self);
                        self._eventShow = self._eventShow || new cc.EventCustom(self.EVENT_SHOW);
                        self._eventShow.setUserData(self);
                        self.onStart();
                        clearInterval(self._checkPrepare);
                    }
                }, 10);
            }
        };
        document.body ?
            _run() :
            cc._addEventListener(window, 'load', function () {
                this.removeEventListener('load', arguments.callee, false);
                _run();
            }, false);
    },

    _initConfig: function () {
        var self = this, CONFIG_KEY = self.CONFIG_KEY;
        var _init = function (cfg) {
            cfg[CONFIG_KEY.engineDir] = cfg[CONFIG_KEY.engineDir] || "frameworks/cocos2d-html5";
            if(cfg[CONFIG_KEY.debugMode] == null)
                cfg[CONFIG_KEY.debugMode] = 0;
            cfg[CONFIG_KEY.frameRate] = cfg[CONFIG_KEY.frameRate] || 60;
            if(cfg[CONFIG_KEY.renderMode] == null)
                cfg[CONFIG_KEY.renderMode] = 1;
            return cfg;
        };
        if (document["ccConfig"]) {
            self.config = _init(document["ccConfig"]);
        } else {
            try {
                var cocos_script = document.getElementsByTagName('script');
                for(var i=0;i<cocos_script.length;i++){
                    var _t = cocos_script[i].getAttribute('cocos');
                    if(_t === '' || _t){break;}
                }
                var _src, txt, _resPath;
                if(i < cocos_script.length){
                    _src = cocos_script[i].src;
                    if(_src){
                        _resPath = /(.*)\//.exec(_src)[0];
                        cc.loader.resPath = _resPath;
                        _src = cc.path.join(_resPath, 'project.json');
                    }
                    txt = cc.loader._loadTxtSync(_src);
                }
                if(!txt){
                    txt = cc.loader._loadTxtSync("project.json");
                }
                var data = JSON.parse(txt);
                self.config = _init(data || {});
            } catch (e) {
                cc.log("Failed to read or parse project.json");
                self.config = _init({});
            }
        }
        //init debug move to CCDebugger
        cc._initSys(self.config, CONFIG_KEY);
    },

    //cache for js and module that has added into jsList to be loaded.
    _jsAddedCache: {},
    _getJsListOfModule: function (moduleMap, moduleName, dir) {
        var jsAddedCache = this._jsAddedCache;
        if (jsAddedCache[moduleName]) return null;
        dir = dir || "";
        var jsList = [];
        var tempList = moduleMap[moduleName];
        if (!tempList) throw "can not find module [" + moduleName + "]";
        var ccPath = cc.path;
        for (var i = 0, li = tempList.length; i < li; i++) {
            var item = tempList[i];
            if (jsAddedCache[item]) continue;
            var extname = ccPath.extname(item);
            if (!extname) {
                var arr = this._getJsListOfModule(moduleMap, item, dir);
                if (arr) jsList = jsList.concat(arr);
            } else if (extname.toLowerCase() === ".js") jsList.push(ccPath.join(dir, item));
            jsAddedCache[item] = 1;
        }
        return jsList;
    },
    /**
     * Prepare game.
     * @param cb
     */
    prepare: function (cb) {
        var self = this;
        var config = self.config, CONFIG_KEY = self.CONFIG_KEY, engineDir = config[CONFIG_KEY.engineDir], loader = cc.loader;
        if (!cc._supportRender) {
            throw "The renderer doesn't support the renderMode " + config[CONFIG_KEY.renderMode];
        }
        self._prepareCalled = true;

        var jsList = config[CONFIG_KEY.jsList] || [];
        if (cc.Class) {//is single file
            //load user's jsList only
            loader.loadJsWithImg("", jsList, function (err) {
                if (err) throw err;
                self._prepared = true;
                if (cb) cb();
            });
        } else {
            //load cc's jsList first
            var ccModulesPath = cc.path.join(engineDir, "moduleConfig.json");
            loader.loadJson(ccModulesPath, function (err, modulesJson) {
                if (err) throw err;
                var modules = config["modules"] || [];
                var moduleMap = modulesJson["module"];
                var newJsList = [];
                if (cc._renderType === cc._RENDER_TYPE_WEBGL) modules.splice(0, 0, "shaders");
                else if (modules.indexOf("core") < 0) modules.splice(0, 0, "core");
                for (var i = 0, li = modules.length; i < li; i++) {
                    var arr = self._getJsListOfModule(moduleMap, modules[i], engineDir);
                    if (arr) newJsList = newJsList.concat(arr);
                }
                newJsList = newJsList.concat(jsList);
                cc.loader.loadJsWithImg(newJsList, function (err) {
                    if (err) throw err;
                    self._prepared = true;
                    if (cb) cb();
                });
            });
        }
    }
};
cc.game._initConfig();
//+++++++++++++++++++++++++something about CCGame end+++++++++++++++++++++++++++++

Function.prototype.bind = Function.prototype.bind || function (oThis) {
    if (!cc.isFunction(this)) {
        // closest thing possible to the ECMAScript 5
        // internal IsCallable function
        throw new TypeError("Function.prototype.bind - what is trying to be bound is not callable");
    }

    var aArgs = Array.prototype.slice.call(arguments, 1),
        fToBind = this,
        fNOP = function () {},
        fBound = function () {
            return fToBind.apply(this instanceof fNOP && oThis
                ? this
                : oThis,
                aArgs.concat(Array.prototype.slice.call(arguments)));
        };

    fNOP.prototype = this.prototype;
    fBound.prototype = new fNOP();

    return fBound;
};
