/*
 * Copyright (c) 2014-2017 Chukong Technologies Inc.
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

function _safeExtend(obj, list) {
    for (var key in list)
        if(!obj[key])
            obj[key] = list[key];
}
function _forceExtend(obj, list) {
    for (var key in list)
        obj[key] = list[key];
}

function _customUndefined(message) {
    return function() {
        cc.log("Not implemented yet in JSB");
        message && cc.log(message);
        return undefined;
    }
}

var _undefined = {
    _jsbUndefined: function(message) {
        cc.log("Not implemented yet in JSB");
        return undefined;
    },
    _shadowUndefined: _customUndefined("Please use enableShadow function"),
    _strokeUndefined: _customUndefined("Please use enableStroke function")
}

_safeExtend(cc.Node.prototype, {
    _getWidth: function() {
        return this.getContentSize().width;
    },
    _getHeight: function() {
        return this.getContentSize().height;
    },

    _setWidth: function(width) {
        this.setContentSize(width, this.getContentSize().height);
    },
    _setHeight: function(height) {
        this.setContentSize(this.getContentSize().width, height);
    },

    _getAnchorX: function() {
        return this.getAnchorPoint().x;
    },
    _getAnchorY: function() {
        return this.getAnchorPoint().y;
    },

    _setAnchorX: function(x) {
        this.setAnchorPoint(cc.p(x, this.getAnchorPoint().y));
    },
    _setAnchorY: function(y) {
        this.setAnchorPoint(cc.p(this.getAnchorPoint().x, y));
    }
});

_safeExtend(cc.LabelTTF.prototype, {
    _fontStyleRE: /^(\d+)px\s+['"]?([\w\s\d]+)['"]?$/,

    _getFont: function() {
        var size = this.getFontSize();
        var name = this.getFontName();
        return size + "px '" + name + "'";
    },

    _setFont: function(fontStyle) {
        var res = this._fontStyleRE.exec(fontStyle);
        if(res) {
            this.setFontSize(parseInt(res[1]));
            this.setFontName(res[2]);
        }
    },

    _getBoundingWidth: function() {
        return this.getDimensions().width;
    },
    _getBoundingHeight: function() {
        return this.getDimensions().height;
    },

    _setBoundingWidth: function(w) {
        var size = cc.size(w, this.getDimensions().height);
        this.setDimensions(size);
    },
    _setBoundingHeight: function(h) {
        var size = cc.size(this.getDimensions().width, h);
        this.setDimensions(size);
    },

    _getFillStyle: _undefined._jsbUndefined,
    _getStrokeStyle: _undefined._strokeUndefined,
    _setStrokeStyle: _undefined._strokeUndefined,
    _getLineWidth: _undefined._strokeUndefined,
    _setLineWidth: _undefined._strokeUndefined,
    _getShadowOffsetX: _undefined._shadowUndefined,
    _setShadowOffsetX: _undefined._shadowUndefined,
    _getShadowOffsetY: _undefined._shadowUndefined,
    _setShadowOffsetY: _undefined._shadowUndefined,
    _getShadowOpacity: _undefined._shadowUndefined,
    _setShadowOpacity: _undefined._shadowUndefined,
    _getShadowBlur: _undefined._shadowUndefined,
    _setShadowBlur: _undefined._shadowUndefined
});

_safeExtend(cc.Sprite.prototype, {
    _getOffsetX: function() {
        return this.getOffsetPosition().x;
    },
    _getOffsetY: function() {
        return this.getOffsetPosition().y;
    }
});

_safeExtend(cc.LabelBMFont.prototype, {
    _getAlignment: _undefined._jsbUndefined,
    _getBoundingWidth: _undefined._jsbUndefined,
    setBoundingWidth: function (width) {
        this.setWidth(width);
    }
});

_safeExtend(cc.TMXLayer.prototype, {
    _getLayerWidth: function() {
        return this.getLayerSize().width;
    },
    _getLayerHeight: function() {
        return this.getLayerSize().height;
    },

    _setLayerWidth: function(w) {
        var size = cc.size(w, this.getLayerSize().height);
        this.setLayerSize(size);
    },
    _setLayerHeight: function(h) {
        var size = cc.size(this.getLayerSize().width, h);
        this.setLayerSize(size);
    },

    _getTileWidth: function() {
        return this.getMapTileSize().width;
    },
    _getTileHeight: function() {
        return this.getMapTileSize().height;
    },

    _setTileWidth: function(w) {
        var size = cc.size(w, this.getMapTileSize().height);
        this.setMapTileSize(size);
    },
    _setTileHeight: function(h) {
        var size = cc.size(this.getMapTileSize().width, h);
        this.setMapTileSize(size);
    }
});

_safeExtend(cc.TMXTiledMap.prototype, {
    _getMapWidth: function() {
        return this.getMapSize().width;
    },
    _getMapHeight: function() {
        return this.getMapSize().height;
    },

    _setMapWidth: function(w) {
        var size = cc.size(w, this.getMapSize().height);
        this.setMapSize(size);
    },
    _setMapHeight: function(h) {
        var size = cc.size(this.getMapSize().width, h);
        this.setMapSize(size);
    },

    _getTileWidth: function() {
        return this.getTileSize().width;
    },
    _getTileHeight: function() {
        return this.getTileSize().height;
    },

    _setTileWidth: function(w) {
        var size = cc.size(w, this.getTileSize().height);
        this.setTileSize(size);
    },
    _setTileHeight: function(h) {
        var size = cc.size(this.getTileSize().width, h);
        this.setTileSize(size);
    }
});



_safeExtend(cc.Texture2D.prototype, {
    _getWidth : function(){
        return this.getContentSize().width;
    },
    _getHeight : function(){
        return this.getContentSize().height;
    }
});