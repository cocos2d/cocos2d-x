/*
 * Copyright (c) 2014 Chukong Technologies Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

//
// cocos2d boot
//

var cc = cc || {};
var window = window || this;

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
    return typeof obj == 'function';
};

/**
 * Check the obj whether is number or not
 * @param {*} obj
 * @returns {boolean}
 */
cc.isNumber = function(obj) {
    return typeof obj == 'number' || Object.prototype.toString.call(obj) == '[object Number]';
};

/**
 * Check the obj whether is string or not
 * @param {*} obj
 * @returns {boolean}
 */
cc.isString = function(obj) {
    return typeof obj == 'string' || Object.prototype.toString.call(obj) == '[object String]';
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
    return obj.__nativeObj !== undefined ||
        ( typeof obj === "object" && Object.prototype.toString.call(obj) === '[object Object]' );
};

/**
 * Check the url whether cross origin
 * @param {String} url
 * @returns {boolean}
 */
cc.isCrossOrigin = function (url) {
    return false;
};

/**
 * Common getter setter configuration function
 * @function
 * @param {Object}   proto      A class prototype or an object to config
 * @param {String}   prop       Property name
 * @param {function} getter     Getter function for the property
 * @param {function} setter     Setter function for the property
 */
cc.defineGetterSetter = function (proto, prop, getter, setter){
    var desc = { enumerable: false, configurable: true };
    getter && (desc.get = getter);
    setter && (desc.set = setter);
    Object.defineProperty(proto, prop, desc);
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
        if(self._pool.length == 0)
            return;                                                         //return directly if the array's length = 0
        if(self._workingSize >= self._limit)
            return;                                                         //return directly if the working size great equal limit number
        var item = self._pool.shift();
        var value = item.value, index = item.index;
        self._workingSize++;
        self._iterator.call(self._iteratorTarget, value, index, function(err){
            if(self._isErr)
                return;

            self.finishedSize++;
            self._workingSize--;
            if(err) {
                self._isErr = true;
                if(self._onEnd)
                    self._onEnd.call(self._onEndTarget, err);
                return
            }

            var arr = Array.prototype.slice.call(arguments, 1);
            self._results[this.index] = arr[0];
            if(self.finishedSize == self.size) {
                if(self._onEnd)
                    self._onEnd.call(self._onEndTarget, null, self._results);
                return;
            }
            self._handleItem();
        }.bind(item), self);
    };

    self.flow = function(){
        var self = this;
        if(self._pool.length == 0) {
            if(self._onEnd)
                self._onEnd.call(self._onEndTarget, null, []);
            return;
        }
        for(var i = 0; i < self._limit; i++)
            self._handleItem();
    }
};

cc.async = {
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
        var asyncPool = new cc.AsyncPool(tasks, 1,
            function (func, index, cb1) {
                args.push(function (err) {
                    args = Array.prototype.slice.call(arguments, 1);
                    cb1.apply(null, arguments);
                });
                func.apply(target, args);
            }, function (err, results) {
                if (!cb)
                    return;
                if (err)
                    return cb.call(target, err);
                cb.call(target, null, results[results.length - 1]);
            });
        asyncPool.flow();
        return asyncPool;
    },

    /**
     * Do tasks by iterator.
     * @param {Array|Object} tasks
     * @param {function|Object} iterator
     * @param {function} cb callback
     * @param {Object} [target]
     * @return {cc.AsyncPool}
     */
    map : function(tasks, iterator, cb, target){
        var locIterator = iterator;
        if(typeof(iterator) == "object"){
            cb = iterator.cb;
            target = iterator.iteratorTarget;
            locIterator = iterator.iterator;
        }
        var asyncPool = new cc.AsyncPool(tasks, 0, locIterator, cb, target);
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
cc.path = {
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
    join : function(){
        var l = arguments.length;
        var result = "";
        for(var i = 0; i < l; i++) {
            result = (result + (result == "" ? "" : "/") + arguments[i]).replace(/(\/|\\\\)$/, "");
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
     * @param pathStr
     * @returns {*}
     */
    extname : function(pathStr){
        var index = pathStr.indexOf("?");
        if(index > 0) pathStr = pathStr.substring(0, index);
        index = pathStr.lastIndexOf(".");
        if(index < 0) return null;
        return pathStr.substring(index, pathStr.length);
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
     * @param pathStr
     * @param extname
     * @returns {*}
     */
    basename : function(pathStr, extname){
        var index = pathStr.indexOf("?");
        if(index > 0) pathStr = pathStr.substring(0, index);
        var reg = /(\/|\\\\)([^(\/|\\\\)]+)$/g;
        var result = reg.exec(pathStr.replace(/(\/|\\\\)$/, ""));
        if(!result) return null;
        var baseName = result[2];
        if(extname && pathStr.substring(pathStr.length - extname.length).toLowerCase() == extname.toLowerCase())
            return baseName.substring(0, baseName.length - extname.length);
        return baseName;
    },
    
    /**
     * Get ext name of a file path.
     * @example
     cc.path.driname("a/b/c.png");//-->"a/b"
     cc.path.driname("a/b/c.png?a=1&b=2");//-->"a/b"
     * @param {String} pathStr
     * @returns {*}
     */
    dirname : function(pathStr){
        return pathStr.replace(/(\/|\\\\)$/, "").replace(/(\/|\\\\)[^(\/|\\\\)]+$/, "");
    },
    
    /**
     * Change extname of a file path.
     * @example
     cc.path.changeExtname("a/b.png", ".plist");//-->"a/b.plist"
     cc.path.changeExtname("a/b.png?a=1&b=2", ".plist");//-->"a/b.plist?a=1&b=2"
     * @param pathStr
     * @param extname
     * @returns {string}
     */
    changeExtname : function(pathStr, extname){
        extname = extname || "";
        var index = pathStr.indexOf("?");
        var tempStr = "";
        if(index > 0) {
            tempStr = pathStr.substring(index);
            pathStr = pathStr.substring(0, index);
        };
        index = pathStr.lastIndexOf(".");
        if(index < 0) return pathStr + extname + tempStr;
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
     * @param [{Boolean}] isSameExt
     * @returns {string}
     */
    changeBasename : function(pathStr, basename, isSameExt){
        if(basename.indexOf(".") == 0) return this.changeExtname(pathStr, basename);
        var index = pathStr.indexOf("?");
        var tempStr = "";
        var ext = isSameExt ? this.extname(pathStr) : "";
        if(index > 0) {
            tempStr = pathStr.substring(index);
            pathStr = pathStr.substring(0, index);
        };
        index = pathStr.lastIndexOf("/");
        index = index <= 0 ? 0 : index+1;
        return pathStr.substring(0, index) + basename + ext + tempStr;
    }
};
//+++++++++++++++++++++++++something about path end++++++++++++++++++++++++++++++++

//+++++++++++++++++++++++++something about loader start+++++++++++++++++++++++++++
cc.loader = {
    _resPath : "",
    _audioPath : "",
    _register : {},//register of loaders
    cache : {},//cache for data loaded
    _langPathCache : {},//cache for lang path
    
    /**
     * Get XMLHttpRequest.
     * @returns {XMLHttpRequest}
     */
    getXMLHttpRequest : function () {
        return new XMLHttpRequest();
    },
    
    
    //@MODE_BEGIN DEV
    
    _jsCache : {},//cache for js
    
    _getArgs4Js : function(args){
        var a0 = args[0], a1 = args[1], a2 = args[2], results = ["", null, null];
        
        if(args.length == 1){
            results[1] = a0 instanceof Array ? a0 : [a0];
        }else if(args.length == 2){
            if(typeof a1 == "function"){
                results[1] = a0 instanceof Array ? a0 : [a0];
                results[2] = a1;
            }else{
                results[0] = a0 || "";
                results[1] = a1 instanceof Array ? a1 : [a1];
            }
        }else if(args.length == 3){
            results[0] = a0 || "";
            results[1] = a1 instanceof Array ? a1 : [a1];
            results[2] = a2;
        }else throw "arguments error to load js!";
        return results;
    },
    /**
     * Load js files.
     * @param {?string=} baseDir   The pre path for jsList.
     * @param {array.<string>} jsList    List of js path.
     * @param {function} cb        Callback function
     *
     *      If the arguments.length == 2, then the baseDir turns to be "".
     * @returns {*}
     */
    loadJs : function(baseDir, jsList, cb){
        var self = this, localJsCache = self._jsCache,
        args = self._getArgs4Js(arguments);
        baseDir = args[0];
        jsList = args[1];
        cb = args[2];
        var ccPath = cc.path;
        for(var i = 0, li = jsList.length; i < li; ++i){
            require(ccPath.join(baseDir, jsList[i]));
        }
        if(cb) cb();
    },
    /**
     * Load js width loading image.
     * @param {?string} baseDir
     * @param {array} jsList
     * @param {function} cb
     */
    loadJsWithImg : function(baseDir, jsList, cb){
        this.loadJs.apply(this, arguments);
    },
    
    //@MODE_END DEV
    
    /**
     * Load a single resource as txt.
     * @param {!string} url
     * @param {function} cb arguments are : err, txt
     */
    loadTxt : function(url, cb){
        cb(null, jsb.fileUtils.getStringFromFile(url));
    },
    
    loadJson : function(url, cb){
        this.loadTxt(url, function(err, txt){
            try{
                err ? cb(err) : cb(null, JSON.parse(txt));
            }catch(e){
                throw e;
                cb("load json [" + url + "] failed : " + e);
            }
        });
    },
    
    /**
     * Load a single image.
     * @param {!string} url
     * @param [{object}] option
     * @param {function} cb
     * @returns {Image}
     */
    loadImg : function(url, option, cb){
        var l = arguments.length;
        if(l == 2) cb = option;

        var cachedTex = cc.textureCache.getTextureForKey(url);
        if (cachedTex) {
            cb && cb(null, cachedTex);
        }
        else if (url.match(jsb.urlRegExp)) {
            jsb.loadRemoteImg(url, function(succeed, tex) {
                if (succeed) {
                    cb && cb(null, tex);
                }
                else {
                    cb && cb("Load image failed");
                }
            });
        }
        else {
            cc.textureCache._addImageAsync(url, function (tex){
                if (tex instanceof cc.Texture2D)
                    cb && cb(null, tex);
                else cb && cb("Load image failed");
            });
        }
    },
    /**
     * Load binary data by url.
     * @param {String} url
     * @param {Function} cb
     */
    loadBinary : function(url, cb){
        cb(null, jsb.fileUtils.getDataFromFile(url));
    },
    loadBinarySync : function(url){
        return jsb.fileUtils.getDataFromFile(url);
    },
    
    /**
     * Iterator function to load res
     * @param {object} item
     * @param {number} index
     * @param {function} cb
     * @returns {*}
     * @private
     */
    _loadResIterator : function(item, index, cb){
        var self = this, url = null;
        var type = item.type;
        if (type) {
            type = "." + type.toLowerCase();
            url = item.src ? item.src : item.name + type;
        } else {
            url = item;
            type = cc.path.extname(url);
        }

        var obj = self.cache[url];
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
    
    /**
     * Get url with basePath.
     * @param [{string}] basePath
     * @param {string} url
     * @returns {*}
     */
    getUrl : function(basePath, url){
        var self = this, langPathCache = self._langPathCache, path = cc.path;
        if(arguments.length == 1){
            url = basePath;
            var type = path.extname(url);
            type = type ? type.toLowerCase() : "";
            var loader = self._register[type];
            if(!loader)
                basePath = self.resPath;
            else
                basePath = loader.getBasePath ? loader.getBasePath() : self.resPath;
        }
        url = cc.path.join(basePath || "", url);
        if(url.match(/[\/(\\\\)]lang[\/(\\\\)]/i)){
            if(langPathCache[url])
                return langPathCache[url];
            var extname = path.extname(url) || "";
            url = langPathCache[url] = url.substring(0, url.length - extname.length) + "_" + cc.sys.language + extname;
        }
        return url;
    },
    
    /**
     * Load resources then call the callback.
     * @param {[string]} res
     * @param [{function}|{}] option
     * @param {function} cb :
     */
    load : function(resources, option, cb){
        var self = this;
        var len = arguments.length;
        if(len == 0)
            throw "arguments error!";

        if(len == 3){
            if(typeof option == "function"){
                if(typeof cb == "function")
                    option = {trigger : option, cb : cb };
                else
                    option = { cb : option, cbTarget : cb};
            }
        }else if(len == 2){
            if(typeof option == "function")
                option = {cb : option};
        }else if(len == 1){
            option = {};
        }

        if(!(resources instanceof Array))
            resources = [resources];
        var asyncPool = new cc.AsyncPool(resources, 0, function(value, index, cb1, aPool){
            self._loadResIterator(value, index, function(err){
                if(err)
                    return cb1(err);
                var arr = Array.prototype.slice.call(arguments, 1);
                if(option.trigger)
                    option.trigger.call(option.triggerTarget, arr[0], aPool.size, aPool.finishedSize); //call trigger
                cb1(null, arr[0]);
            });
        }, option.cb, option.cbTarget);
        asyncPool.flow();
        return asyncPool;
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
     * @param {String} filename  The plist file name.
     * @param {Function} cb     callback
     */
    loadAliases : function(url, cb){
        jsb.fileUtils.loadFilenameLookup(url);
        if(cb) cb();
    },

    /**
     * Register a resource loader into loader.
     * @param {string} extname
     * @param {load : function} loader
     */
    register : function(extNames, loader){
        if(!extNames || !loader) return;
        var self = this;
        if(typeof extNames == "string")
            return this._register[extNames.trim().toLowerCase()] = loader;
        for(var i = 0, li = extNames.length; i < li; i++) {
            self._register["." + extNames[i].trim().toLowerCase()] = loader;
        }
    },
    
    /**
     * Get resource data by url.
     * @param url
     * @returns {*}
     */
    getRes : function(url){
        var cached = this.cache[url];
        if (cached)
            return cached;
        var type = cc.path.extname(url);
        var loader = this._register[type.toLowerCase()];
        if(!loader) return cc.log("loader for [" + type + "] not exists!");
        var basePath = loader.getBasePath ? loader.getBasePath() : this.resPath;
        var realUrl = this.getUrl(basePath, url);
        return loader.load(realUrl, url);
    },
    
    /**
     * Release the cache of resource by url.
     * @param url
     */
    release : function(url){
        var cache = this.cache;
        delete cache[url];
    },
    
    /**
     * Resource cache of all resources.
     */
    releaseAll : function(){
        var locCache = this.cache;
        for (var key in locCache)
            delete locCache[key];
    }
    
};
cc.defineGetterSetter(cc.loader, "resPath", function(){
    return this._resPath;
}, function(resPath){
    this._resPath = resPath || "";
    jsb.fileUtils.addSearchPath(this._resPath);
});
cc.defineGetterSetter(cc.loader, "audioPath", function(){
    return this._audioPath;
}, function(audioPath){
    this._audioPath = audioPath || "";
    jsb.fileUtils.addSearchPath(this._audioPath);
});

//+++++++++++++++++++++++++something about loader end+++++++++++++++++++++++++++++

//+++++++++++++++++++++++++something about format string begin+++++++++++++++++++++++++++++

/**
 * A string tool to construct a string with format string.
 * for example: cc.formatStr("a: %d, b: %b", a, b);
 * @param {String} formatStr format String
 * @returns {String}
 */
cc.formatStr = function(){
    var args = arguments;
    var l = args.length;
    if(l < 1)
        return "";

    var str = args[0];
    var needToFormat = true;
    if(typeof str == "object"){
        needToFormat = false;
    }
    for(var i = 1; i < l; ++i){
        var arg = args[i];
        if(needToFormat){
            while(true){
                var result = null;
                if(typeof arg == "number"){
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

//+++++++++++++++++++++++Define singleton format string end+++++++++++++++++++++++++++

//+++++++++++++++++++++++Define singleton objects begin+++++++++++++++++++++++++++

// Define singleton objects
/**
 * @type {cc.Director}
 * @name cc.director
 */
cc.director = cc.Director.getInstance();
/**
 * @type {cc.Size}
 * @name cc.winSize
 * cc.winSize is the alias object for the size of the current game window.
 */
cc.winSize = cc.director.getWinSize();
/**
 * @type {cc.EGLView}
 * @name cc.view
 * cc.view is the shared view object.
 */
cc.view = cc.director.getOpenGLView();
cc.view.getDevicePixelRatio = function () {
    var sys = cc.sys;
    return (sys.os == sys.OS_IOS || sys.os == sys.OS_OSX) ? 2 : 1;
};
cc.view.convertToLocationInView = function (tx, ty, relatedPos) {
    var _devicePixelRatio = cc.view.getDevicePixelRatio();
    return {x: _devicePixelRatio * (tx - relatedPos.left), y: _devicePixelRatio * (relatedPos.top + relatedPos.height - ty)};
};
cc.view.enableRetina = function(enabled) {};
cc.view.isRetinaEnabled = function() {
    var sys = cc.sys;
    return (sys.os == sys.OS_IOS || sys.os == sys.OS_OSX) ? true : false;
};
cc.view.adjustViewPort = function() {};
cc.view.resizeWithBrowserSize = function () {return;};
cc.view.setResizeCallback = function() {return;};
cc.view.enableAutoFullScreen = function () {return;};
cc.view.isAutoFullScreenEnabled = function() {return true;};
cc.view._setDesignResolutionSize = cc.view.setDesignResolutionSize;
cc.view.setDesignResolutionSize = function(width,height,resolutionPolicy){
    cc.view._setDesignResolutionSize(width,height,resolutionPolicy);
    cc.winSize = cc.director.getWinSize();
    cc.visibleRect.init();
};
cc.view.setResolutionPolicy = function(resolutionPolicy){
    var size = cc.view.getDesignResolutionSize();
    cc.view.setDesignResolutionSize(size.width,size.height,resolutionPolicy);
};
cc.view.setContentTranslateLeftTop = function(){return;};
cc.view.getContentTranslateLeftTop = function(){return null;};
cc.view.setFrameZoomFactor = function(){return;};
cc.DENSITYDPI_DEVICE = "device-dpi";
cc.DENSITYDPI_HIGH = "high-dpi";
cc.DENSITYDPI_MEDIUM = "medium-dpi";
cc.DENSITYDPI_LOW = "low-dpi";
cc.view.setTargetDensityDPI = function() {};
cc.view.getTargetDensityDPI = function() {return cc.DENSITYDPI_DEVICE;};

/**
 * @type {Object}
 * @name cc.eventManager
 */
cc.eventManager = cc.director.getEventDispatcher();

/**
 * @type {cc.AudioEngine}
 * @name cc.audioEngine
 * A simple Audio Engine engine API.
 */
cc.audioEngine = cc.AudioEngine.getInstance();
cc.audioEngine.end = function(){
    this.stopMusic();
    this.stopAllEffects();
};
/**
 * @type {Object}
 * @name cc.configuration
 * cc.configuration contains some openGL variables
 */
cc.configuration = cc.Configuration.getInstance();
/**
 * @type {Object}
 * @name cc.textureCache
 * cc.textureCache is the global cache for cc.Texture2D
 */
cc.textureCache = cc.director.getTextureCache();
cc.TextureCache.prototype._addImageAsync = cc.TextureCache.prototype.addImageAsync;
cc.TextureCache.prototype.addImageAsync = function(url, cb, target) {
    var localTex = null;
    cc.loader.loadImg(url, function(err, tex) {
        if (err) tex = null;
        if (cb) {
            cb.call(target, tex);
        }
        localTex = tex;
    });
    return localTex;
};
// Fix for compatibility with old APIs
cc.TextureCache.prototype._addImage = cc.TextureCache.prototype.addImage;
cc.TextureCache.prototype.addImage = function(url, cb, target) {
    if (typeof cb === "function") {
        return this.addImageAsync(url, cb, target);
    }
    else {
        if (cb) {
            return this._addImage(url, cb)
        }
        else {
            return this._addImage(url);
        }
    }
};
/**
 * @type {Object}
 * @name cc.shaderCache
 * cc.shaderCache is a singleton object that stores manages GL shaders
 */
cc.shaderCache = cc.ShaderCache.getInstance();
/**
 * @type {Object}
 * @name cc.animationCache
 */
cc.animationCache = cc.AnimationCache.getInstance();
/**
 * @type {Object}
 * @name cc.spriteFrameCache
 */
cc.spriteFrameCache = cc.SpriteFrameCache.getInstance();
/**
 * @type {cc.PlistParser}
 * @name cc.plistParser
 * A Plist Parser
 */
cc.plistParser = cc.PlistParser.getInstance();
//cc.tiffReader;
//cc.imeDispatcher;

// File utils (Temporary, won't be accessible)
cc.fileUtils = cc.FileUtils.getInstance();
cc.fileUtils.setPopupNotify(false);



/**
 * @type {Object}
 * @name cc.screen
 * The fullscreen API provides an easy way for web content to be presented using the user's entire screen.
 * It's invalid on safari,QQbrowser and android browser
 */
cc.screen = {
    init: function() {},
    fullScreen: function() {
        return true;
    },
    requestFullScreen: function(element, onFullScreenChange) {
        onFullScreenChange.call();
    },
    exitFullScreen: function() {
        return false;
    },
    autoFullScreen: function(element, onFullScreenChange) {
        onFullScreenChange.call();
    }
};

//+++++++++++++++++++++++Define singleton objects end+++++++++++++++++++++++++++


//+++++++++++++++++++++++++Redefine JSB only APIs+++++++++++++++++++++++++++

/**
 * @namespace jsb
 * @name jsb
 */
var jsb = jsb || {};
/**
 * @type {Object}
 * @name jsb.fileUtils
 * jsb.fileUtils is the native file utils singleton object,
 * please refer to Cocos2d-x API to know how to use it.
 * Only available in JSB
 */
jsb.fileUtils = cc.fileUtils;
delete cc.FileUtils;
delete cc.fileUtils;

/**
 * @type {Object}
 * @name jsb.reflection
 * jsb.reflection is a bridge to let you invoke Java static functions.
 * please refer to this document to know how to use it: http://www.cocos2d-x.org/docs/manual/framework/html5/v3/reflection/en
 * Only available on Android platform
 */
jsb.reflection = {
    callStaticMethod : function(){
        cc.log("not supported on current platform");
    }
};

//+++++++++++++++++++++++++Redefine JSB only APIs+++++++++++++++++++++++++++++


//+++++++++++++++++++++++++something about window events begin+++++++++++++++++++++++++++
cc.winEvents = {//TODO register hidden and show callback for window
    hiddens : [],
    shows : []
};
//+++++++++++++++++++++++++something about window events end+++++++++++++++++++++++++++++

//+++++++++++++++++++++++++something about sys begin+++++++++++++++++++++++++++++
cc._initSys = function(config, CONFIG_KEY){

    var locSys = cc.sys = sys || {},
        platform,
        capabilities;

    /**
     * English language code
     * @constant
     * @default
     * @type {Number}
     */
    locSys.LANGUAGE_ENGLISH = "en";
    /**
     * Chinese language code
     * @constant
     * @default
     * @type {Number}
     */
    locSys.LANGUAGE_CHINESE = "zh";
    /**
     * French language code
     * @constant
     * @default
     * @type {Number}
     */
    locSys.LANGUAGE_FRENCH = "fr";
    /**
     * Italian language code
     * @constant
     * @default
     * @type {Number}
     */
    locSys.LANGUAGE_ITALIAN = "it";
    /**
     * German language code
     * @constant
     * @default
     * @type {Number}
     */
    locSys.LANGUAGE_GERMAN = "de";
    /**
     * Spanish language code
     * @constant
     * @default
     * @type {Number}
     */
    locSys.LANGUAGE_SPANISH = "es";
    
    /**
     * Netherlands language code
     * @type {string}
     */
    locSys.LANGUAGE_DUTCH = "nl";
    /**
     * Dutch language code
     * @constant
     * @default
     * @type {Number}
     */
    locSys.LANGUAGE_DUTCH = "du";
    /**
     * Russian language code
     * @constant
     * @default
     * @type {Number}
     */
    locSys.LANGUAGE_RUSSIAN = "ru";
    /**
     * Korean language code
     * @constant
     * @default
     * @type {Number}
     */
    locSys.LANGUAGE_KOREAN = "ko";
    /**
     * Japanese language code
     * @constant
     * @default
     * @type {Number}
     */
    locSys.LANGUAGE_JAPANESE = "ja";
    /**
     * Hungarian language code
     * @constant
     * @default
     * @type {Number}
     */
    locSys.LANGUAGE_HUNGARIAN = "hu";
    /**
     * Portuguese language code
     * @constant
     * @default
     * @type {Number}
     */
    locSys.LANGUAGE_PORTUGUESE = "pt";
    /**
     * Arabic language code
     * @constant
     * @default
     * @type {Number}
     */
    locSys.LANGUAGE_ARABIC = "ar";
    /**
     * Norwegian language code
     * @constant
     * @default
     * @type {Number}
     */
    locSys.LANGUAGE_NORWEGIAN = "no";
    /**
     * Polish language code
     * @constant
     * @default
     * @type {Number}
     */
    locSys.LANGUAGE_POLISH = "pl";

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
    sys.UNKNOWN = -1;
    /**
     * @memberof cc.sys
     * @name WIN32
     * @constant
     * @default
     * @type {Number}
     */
    sys.WIN32 = 0;
    /**
     * @memberof cc.sys
     * @name LINUX
     * @constant
     * @default
     * @type {Number}
     */
    sys.LINUX = 1;
    /**
     * @memberof cc.sys
     * @name MACOS
     * @constant
     * @default
     * @type {Number}
     */
    sys.MACOS = 2;
    /**
     * @memberof cc.sys
     * @name ANDROID
     * @constant
     * @default
     * @type {Number}
     */
    sys.ANDROID = 3;
    /**
     * @memberof cc.sys
     * @name IOS
     * @constant
     * @default
     * @type {Number}
     */
    sys.IPHONE = 4;
    /**
     * @memberof cc.sys
     * @name IOS
     * @constant
     * @default
     * @type {Number}
     */
    sys.IPAD = 5;
    /**
     * @memberof cc.sys
     * @name BLACKBERRY
     * @constant
     * @default
     * @type {Number}
     */
    sys.BLACKBERRY = 6;
    /**
     * @memberof cc.sys
     * @name NACL
     * @constant
     * @default
     * @type {Number}
     */
    sys.NACL = 7;
    /**
     * @memberof cc.sys
     * @name EMSCRIPTEN
     * @constant
     * @default
     * @type {Number}
     */
    sys.EMSCRIPTEN = 8;
    /**
     * @memberof cc.sys
     * @name TIZEN
     * @constant
     * @default
     * @type {Number}
     */
    sys.TIZEN = 9;
    /**
     * @memberof cc.sys
     * @name WINRT
     * @constant
     * @default
     * @type {Number}
     */
    sys.WINRT = 10;
    /**
     * @memberof cc.sys
     * @name WP8
     * @constant
     * @default
     * @type {Number}
     */
    sys.WP8 = 11;
    /**
     * @constant
     * @default
     * @type {Number}
     */
    locSys.MOBILE_BROWSER = 100;
    /**
     * @constant
     * @default
     * @type {Number}
     */
    locSys.DESKTOP_BROWSER = 101;

    locSys.BROWSER_TYPE_WECHAT = "wechat";
    locSys.BROWSER_TYPE_ANDROID = "androidbrowser";
    locSys.BROWSER_TYPE_IE = "ie";
    locSys.BROWSER_TYPE_QQ = "qqbrowser";
    locSys.BROWSER_TYPE_MOBILE_QQ = "mqqbrowser";
    locSys.BROWSER_TYPE_UC = "ucbrowser";
    locSys.BROWSER_TYPE_360 = "360browser";
    locSys.BROWSER_TYPE_BAIDU_APP = "baiduboxapp";
    locSys.BROWSER_TYPE_BAIDU = "baidubrowser";
    locSys.BROWSER_TYPE_MAXTHON = "maxthon";
    locSys.BROWSER_TYPE_OPERA = "opera";
    locSys.BROWSER_TYPE_MIUI = "miuibrowser";
    locSys.BROWSER_TYPE_FIREFOX = "firefox";
    locSys.BROWSER_TYPE_SAFARI = "safari";
    locSys.BROWSER_TYPE_CHROME = "chrome";
    locSys.BROWSER_TYPE_UNKNOWN = "unknown";

    /**
     * Is native ? This is set to be true in jsb auto.
     * @constant
     * @default
     * @type {Boolean}
     */
    locSys.isNative = true;

    /** Get the target platform of system */
    locSys.platform = __getPlatform();

    /** Get the os of system */
    locSys.os = __getOS();

    // Forces the garbage collector
    locSys.garbageCollect = function() {
        __jsc__.garbageCollect();
    };

    // Dumps rooted objects
    locSys.dumpRoot = function() {
        __jsc__.dumpRoot();
    };

    // restarts the JS VM
    locSys.restartVM = function() {
        __restartVM();
    };

    // clean a singal js file
    locSys.cleanScript = function(jsFile) {
        __cleanScript(jsFile);
    };
    
    // Check whether an object is valid
    locSys.isObjectValid = function(obj) {
        return __isObjectValid(obj);
    };


    locSys.dump = function(){
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

    platform = locSys.platform;
    locSys.isMobile = ( platform === locSys.ANDROID || 
                        platform === locSys.IPAD || 
                        platform === locSys.IPHONE || 
                        platform === locSys.WP8 || 
                        platform === locSys.TIZEN ||
                        platform === locSys.BLACKBERRY ) ? true : false;

    locSys.language = (function(){
        var language = cc.Application.getInstance().getCurrentLanguage();
        switch(language){
            case 0: return locSys.LANGUAGE_ENGLISH;
            case 1: return locSys.LANGUAGE_CHINESE;
            case 2: return locSys.LANGUAGE_FRENCH;
            case 3: return locSys.LANGUAGE_ITALIAN;
            case 4: return locSys.LANGUAGE_GERMAN;
            case 5: return locSys.LANGUAGE_SPANISH;
            case 6: return locSys.LANGUAGE_DUTCH;
            case 7: return locSys.LANGUAGE_RUSSIAN;
            case 8: return locSys.LANGUAGE_KOREAN;
            case 9: return locSys.LANGUAGE_JAPANESE;
            case 10: return locSys.LANGUAGE_HUNGARIAN;
            case 11: return locSys.LANGUAGE_PORTUGUESE;
            case 12: return locSys.LANGUAGE_ARABIC;
            case 13: return locSys.LANGUAGE_NORWEGIAN;
            case 14: return locSys.LANGUAGE_POLISH;
            default : return locSys.LANGUAGE_ENGLISH;
        }
    })();

    /** The type of browser */
    locSys.browserType = null;//null in jsb

    capabilities = locSys.capabilities = {"opengl":true};
    if( locSys.isMobile ) {
        capabilities["accelerometer"] = true;
        capabilities["touches"] = true;
        if (platform === locSys.WINRT || platform === locSys.WP8) {
            capabilities["keyboard"] = true;
        }
    } else {
        // desktop
        capabilities["keyboard"] = true;
        capabilities["mouse"] = true;
        // winrt can't suppot mouse in current version
        if (platform === locSys.WINRT || platform === locSys.WP8)
        {
            capabilities["touches"] = true;
            capabilities["mouse"] = false;
        }
    }

    /**
     * Open a url in browser
     * @memberof cc.sys
     * @name openURL
     * @param {String} url
     */
    locSys.openURL = function(url){
        cc.Application.getInstance().openURL(url);
    }
};

//+++++++++++++++++++++++++something about sys end+++++++++++++++++++++++++++++
//+++++++++++++++++++++++++something about log start++++++++++++++++++++++++++++
/**
 * Init Debug setting.
 * @function
 */
cc._initDebugSetting = function (mode) {
    var ccGame = cc.game;
    var bakLog = cc._cocosplayerLog || cc.log || log;
    cc.log = cc.warn = cc.error = cc.assert = function(){};
    if(mode == ccGame.DEBUG_MODE_NONE){
    }else{
        cc.error = function(){
            bakLog.call(this, "ERROR :  " + cc.formatStr.apply(cc, arguments));
        };
        cc.assert = function(cond, msg) {
            if (!cond && msg) {
                var args = [];
                for (var i = 1; i < arguments.length; i++)
                    args.push(arguments[i]);
                bakLog("Assert: " + cc.formatStr.apply(cc, args));
            }
        };
        if(mode != ccGame.DEBUG_MODE_ERROR && mode != ccGame.DEBUG_MODE_ERROR_FOR_WEB_PAGE){
            cc.warn = function(){
                bakLog.call(this, "WARN :  " + cc.formatStr.apply(cc, arguments));
            };
        }
        if(mode == ccGame.DEBUG_MODE_INFO || mode == ccGame.DEBUG_MODE_INFO_FOR_WEB_PAGE){
            cc.log = function(){
                bakLog.call(this, cc.formatStr.apply(cc, arguments));
            };
        }
    }
};
//+++++++++++++++++++++++++something about log end+++++++++++++++++++++++++++++


//+++++++++++++++++++++++++something about CCGame begin+++++++++++++++++++++++++++

/**
 * @type {Object}
 * @name cc.game
 * An object to boot the game.
 */
cc.game = {
    DEBUG_MODE_NONE : 0,
    DEBUG_MODE_INFO : 1,
    DEBUG_MODE_WARN : 2,
    DEBUG_MODE_ERROR : 3,
    DEBUG_MODE_INFO_FOR_WEB_PAGE : 4,
    DEBUG_MODE_WARN_FOR_WEB_PAGE : 5,
    DEBUG_MODE_ERROR_FOR_WEB_PAGE : 6,

    EVENT_HIDE: "game_on_hide",
    EVENT_SHOW: "game_on_show",
    
    /**
     * Key of config
     * @constant
     * @default
     * @type {Object}
     */
    CONFIG_KEY : {
        engineDir : "engineDir",
        dependencies : "dependencies",
        debugMode : "debugMode",
        showFPS : "showFPS",
        frameRate : "frameRate",
        id : "id",
        renderMode : "renderMode",
        jsList : "jsList",
        classReleaseMode : "classReleaseMode"
    },
    
    _prepareCalled : false,//whether the prepare function has been called
    _prepared : false,//whether the engine has prepared
    _paused : true,//whether the game is paused
    
    _intervalId : null,//interval target of main
    
    
    /**
     * Config of game
     * @type {Object}
     */
    config : null,
    
    /**
     * Callback when the scripts of engine have been load.
     * @type {Function}
     */
    onStart : null,
    
    /**
     * Callback when game exits.
     * @type {Function}
     */
    onExit : null,
    /**
     * Callback before game resumes.
     * @type {Function}
     */
    onBeforeResume : null,
    /**
     * Callback after game resumes.
     * @type {Function}
     */
    onAfterResume : null,
    /**
     * Callback before game pauses.
     * @type {Function}
     */
    onBeforePause : null,
    /**
     * Callback after game pauses.
     * @type {Function}
     */
    onAfterPause : null,
    
    /**
     * Set frameRate of game.
     * @param frameRate
     */
    setFrameRate : function(frameRate){
        var self = this, config = self.config, CONFIG_KEY = self.CONFIG_KEY;
        config[CONFIG_KEY.frameRate] = frameRate;
        cc.director.setAnimationInterval(1.0/frameRate);
    },
    
    /**
     * Restart game.
     */
    restart: function () {
        __restartVM();
    },
    
    /**
     * Run game.
     */
    run : function(){
        var self = this;
        if(!self._prepareCalled){
            self.prepare(function(){
                self.onStart();
            });
        }else{
            self.onStart();
        }
    },
    
    /**
     * Init config.
     * @param cb
     * @returns {*}
     * @private
     */
    _initConfig : function(){
        cc._initDebugSetting(1);
        var self = this, CONFIG_KEY = self.CONFIG_KEY;
        var _init = function(cfg){
            cfg[CONFIG_KEY.engineDir] = cfg[CONFIG_KEY.engineDir] || "frameworks/cocos2d-html5";
            cfg[CONFIG_KEY.debugMode] = cfg[CONFIG_KEY.debugMode] || 0;
            cfg[CONFIG_KEY.frameRate] = cfg[CONFIG_KEY.frameRate] || 60;
            cfg[CONFIG_KEY.renderMode] = cfg[CONFIG_KEY.renderMode] || 0;
            cfg[CONFIG_KEY.showFPS] = cfg[CONFIG_KEY.showFPS] === false ? false : true;
            return cfg;
        };
        try{
            var txt = jsb.fileUtils.getStringFromFile("project.json");
            var data = JSON.parse(txt);
            this.config = _init(data || {});
        }catch(e){
            cc.log("Failed to read or parse project.json");
            this.config = _init({});
        }
        cc._initDebugSetting(this.config[CONFIG_KEY.debugMode]);
        cc.director.setDisplayStats(this.config[CONFIG_KEY.showFPS]);
        cc.director.setAnimationInterval(1.0/this.config[CONFIG_KEY.frameRate]);
        cc._initSys(this.config, CONFIG_KEY);
    },
    
    //cache for js and module that has added into jsList to be loaded.
    _jsAddedCache : {},
    _getJsListOfModule : function(moduleMap, moduleName, dir){
        var jsAddedCache = this._jsAddedCache;
        if(jsAddedCache[moduleName]) return null;
        dir = dir || "";
        var jsList = [];
        var tempList = moduleMap[moduleName];
        if(!tempList) throw "can not find module [" + moduleName + "]";
        var ccPath = cc.path;
        for(var i = 0, li = tempList.length; i < li; i++){
            var item = tempList[i];
            if(jsAddedCache[item]) continue;
            var extname = ccPath.extname(item);
            if(!extname) {
                var arr = this._getJsListOfModule(moduleMap, item, dir);
                if(arr) jsList = jsList.concat(arr);
            }else if(extname.toLowerCase() == ".js") jsList.push(ccPath.join(dir, item));
            jsAddedCache[item] = true;
        }
        return jsList;
    },
    /**
     * Prepare game.
     * @param cb
     */
    prepare : function(cb){
        var self = this, config = self.config, CONFIG_KEY = self.CONFIG_KEY, loader = cc.loader;
        require("script/jsb.js");
        self._prepareCalled = true;
        loader.loadJsWithImg("", config[CONFIG_KEY.jsList] || [], function(err){
            if(err) throw err;
            self._prepared = true;
            if(cb) cb();
        });
    }
};
cc.game._initConfig();

//+++++++++++++++++++++++++something about CCGame end+++++++++++++++++++++++++++++

//+++++++++++++++++++++++++other initializations+++++++++++++++++++++++++++++

// JS to Native bridges
if(window.JavascriptJavaBridge && cc.sys.os == cc.sys.OS_ANDROID){
    jsb.reflection = new JavascriptJavaBridge();
    cc.sys.capabilities["keyboard"] = true;
}
else if(window.JavaScriptObjCBridge && (cc.sys.os == cc.sys.OS_IOS || cc.sys.os == cc.sys.OS_OSX)){
    jsb.reflection = new JavaScriptObjCBridge();
}

jsb.urlRegExp = new RegExp(
    "^" +
        // protocol identifier
        "(?:(?:https?|ftp)://)" +
        // user:pass authentication
        "(?:\\S+(?::\\S*)?@)?" +
        "(?:" +
            // IP address dotted notation octets
            // excludes loopback network 0.0.0.0
            // excludes reserved space >= 224.0.0.0
            // excludes network & broacast addresses
            // (first & last IP address of each class)
            "(?:[1-9]\\d?|1\\d\\d|2[01]\\d|22[0-3])" +
            "(?:\\.(?:1?\\d{1,2}|2[0-4]\\d|25[0-5])){2}" +
            "(?:\\.(?:[1-9]\\d?|1\\d\\d|2[0-4]\\d|25[0-4]))" +
        "|" +
            // host name
            "(?:(?:[a-z\\u00a1-\\uffff0-9]-*)*[a-z\\u00a1-\\uffff0-9]+)" +
            // domain name
            "(?:\\.(?:[a-z\\u00a1-\\uffff0-9]-*)*[a-z\\u00a1-\\uffff0-9]+)*" +
            // TLD identifier
            "(?:\\.(?:[a-z\\u00a1-\\uffff]{2,}))" +
        ")" +
        // port number
        "(?::\\d{2,5})?" +
        // resource path
        "(?:/\\S*)?" +
    "$", "i"
);

//+++++++++++++++++++++++++other initializations end+++++++++++++++++++++++++++++
