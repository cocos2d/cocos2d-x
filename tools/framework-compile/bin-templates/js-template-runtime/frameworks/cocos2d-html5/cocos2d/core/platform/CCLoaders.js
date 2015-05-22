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

cc._txtLoader = {
    load : function(realUrl, url, res, cb){
        cc.loader.loadTxt(realUrl, cb);
    }
};
cc.loader.register(["txt", "xml", "vsh", "fsh", "atlas"], cc._txtLoader);

cc._jsonLoader = {
    load : function(realUrl, url, res, cb){
        cc.loader.loadJson(realUrl, cb);
    }
};
cc.loader.register(["json", "ExportJson"], cc._jsonLoader);

cc._jsLoader = {
    load : function(realUrl, url, res, cb){
        cc.loader.loadJs(realUrl, cb);
    }
};
cc.loader.register(["js"], cc._jsLoader);

cc._imgLoader = {
    load : function(realUrl, url, res, cb){
        cc.loader.cache[url] =  cc.loader.loadImg(realUrl, function(err, img){
            if(err)
                return cb(err);
            cc.textureCache.handleLoadedTexture(url);
            cb(null, img);
        });
    }
};
cc.loader.register(["png", "jpg", "bmp","jpeg","gif", "ico"], cc._imgLoader);
cc._serverImgLoader = {
    load : function(realUrl, url, res, cb){
        cc.loader.cache[url] =  cc.loader.loadImg(res.src, function(err, img){
            if(err)
                return cb(err);
            cc.textureCache.handleLoadedTexture(url);
            cb(null, img);
        });
    }
};
cc.loader.register(["serverImg"], cc._serverImgLoader);

cc._plistLoader = {
    load : function(realUrl, url, res, cb){
        cc.loader.loadTxt(realUrl, function(err, txt){
            if(err)
                return cb(err);
            cb(null, cc.plistParser.parse(txt));
        });
    }
};
cc.loader.register(["plist"], cc._plistLoader);

cc._fontLoader = {
    TYPE : {
        ".eot" : "embedded-opentype",
        ".ttf" : "truetype",
        ".woff" : "woff",
        ".svg" : "svg"
    },
    _loadFont : function(name, srcs, type){
        var doc = document, path = cc.path, TYPE = this.TYPE, fontStyle = cc.newElement("style");
        fontStyle.type = "text/css";
        doc.body.appendChild(fontStyle);

        var fontStr = "@font-face { font-family:" + name + "; src:";
        if(srcs instanceof Array){
            for(var i = 0, li = srcs.length; i < li; i++){
                var src = srcs[i];
                type = path.extname(src).toLowerCase();
                fontStr += "url('" + srcs[i] + "') format('" + TYPE[type] + "')";
                fontStr += (i === li - 1) ? ";" : ",";
            }
        }else{
            fontStr += "url('" + srcs + "') format('" + TYPE[type] + "');";
        }
        fontStyle.textContent += fontStr + "};";

        //<div style="font-family: PressStart;">.</div>
        var preloadDiv = cc.newElement("div");
        var _divStyle =  preloadDiv.style;
        _divStyle.fontFamily = name;
        preloadDiv.innerHTML = ".";
        _divStyle.position = "absolute";
        _divStyle.left = "-100px";
        _divStyle.top = "-100px";
        doc.body.appendChild(preloadDiv);
    },
    load : function(realUrl, url, res, cb){
        var self = this;
        var type = res.type, name = res.name, srcs = res.srcs;
        if(cc.isString(res)){
            type = cc.path.extname(res);
            name = cc.path.basename(res, type);
            self._loadFont(name, res, type);
        }else{
            self._loadFont(name, srcs);
        }
        cb(null, true);
    }
};
cc.loader.register(["font", "eot", "ttf", "woff", "svg"], cc._fontLoader);

cc._binaryLoader = {
    load : function(realUrl, url, res, cb){
        cc.loader.loadBinary(realUrl, cb);
    }
};

cc._csbLoader = {
    load: function(realUrl, url, res, cb){
        cc.loader.loadCsb(realUrl, cb);
    }
};
cc.loader.register(["csb"], cc._csbLoader);