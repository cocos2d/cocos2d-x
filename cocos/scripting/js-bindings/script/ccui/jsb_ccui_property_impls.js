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

// Override width and height getter setter
_forceExtend(ccui.Widget.prototype, {
    _getXPercent: function() {
        return this.getPositionPercent().x;
    },
    _getYPercent: function() {
        return this.getPositionPercent().y;
    },

    _setXPercent: function(x) {
        var p = cc.p(x, this.getPositionPercent().y);
        this.setPositionPercent(p);
    },
    _setYPercent: function(y) {
        var p = cc.p(this.getPositionPercent().x, y);
        this.setPositionPercent(p);
    },

    _getWidth: function() {
        return this.getContentSize().width;
    },
    _getHeight: function() {
        return this.getContentSize().height;
    },
    _getWidthPercent: function() {
        return this.getSizePercent().width;
    },
    _getHeightPercent: function() {
        return this.getSizePercent().height;
    },

    _setWidth: function(w) {
        var size = cc.size(w, this.getContentSize().height);
        this.setContentSize(size);
    },
    _setHeight: function(h) {
        var size = cc.size(this.getContentSize().width, h);
        this.setContentSize(size);
    },
    _setWidthPercent: function(w) {
        var size = cc.size(w, this.getSizePercent().height);
        this.setSizePercent(size);
    },
    _setHeightPercent: function(h) {
        var size = cc.size(this.getSizePercent().width, h);
        this.setSizePercent(size);
    }
});

_safeExtend(ccui.Button.prototype, {
    _fontStyleRE: /^(\d+)px\s+['"]?([\w\s\d]+)['"]?$/,

    _getTitleFont: function() {
        var size = this.getTitleFontSize();
        var name = this.getTitleFontName();
        return size + "px '" + name + "'";
    },

    _setTitleFont: function(fontStyle) {
        var res = this._fontStyleRE.exec(fontStyle);
        if(res) {
            this.setTitleFontSize(parseInt(res[1]));
            this.setTitleFontName(res[2]);
        }
    }
});

_safeExtend(ccui.Text.prototype, {
    _getBoundingWidth: function() {
        return this.getTextAreaSize().width;
    },
    _getBoundingHeight: function() {
        return this.getTextAreaSize().height;
    },

    _setBoundingWidth: function(w) {
        var size = cc.size(w, this.getTextAreaSize().height);
        this.setTextAreaSize(size);
    },
    _setBoundingHeight: function(h) {
        var size = cc.size(this.getTextAreaSize().width, h);
        this.setTextAreaSize(size);
    }
});

_safeExtend(ccui.TextField.prototype, {
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
    }
});

_safeExtend(ccui.ScrollView.prototype, {
    _getInnerWidth: function() {
        return this.getInnerContainerSize().width;
    },
    _getInnerHeight: function() {
        return this.getInnerContainerSize().height;
    },

    _setInnerWidth: function(w) {
        var size = cc.size(w, this.getInnerContainerSize().height);
        this.setInnerContainerSize(size);
    },
    _setInnerHeight: function(h) {
        var size = cc.size(this.getInnerContainerSize().width, h);
        this.setInnerContainerSize(size);
    }
});

// _safeExtend(ccui.EditBox.prototype, {
//     _setFont: function(fontStyle) {
//         var res = cc.LabelTTF.prototype._fontStyleRE.exec(fontStyle);
//         if(res) {
//             this.setFontSize(parseInt(res[1]));
//             this.setFontName(res[2]);
//         }
//     }
// });