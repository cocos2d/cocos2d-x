/****************************************************************************
 Copyright (c) 2008-2010 Ricardo Quesada
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

cc._globalFontSize = cc.ITEM_SIZE;
cc._globalFontName = "Arial";
cc._globalFontNameRelease = false;

/**
 * Subclass cc.MenuItem (or any subclass) to create your custom cc.MenuItem objects.
 * @class
 * @extends cc.Node
 * @param {function|String} callback
 * @param  {cc.Node} target
 */
cc.MenuItem = cc.Node.extend(/** @lends cc.MenuItem# */{
    _enabled: false,
    _target: null,
    _callback: null,
    _isSelected: false,
    _className: "MenuItem",

    /**
     * Constructor of cc.MenuItem
     * @param {function|String} callback
     * @param {cc.Node} target
     */
    ctor: function (callback, target) {
        var nodeP = cc.Node.prototype;
        nodeP.ctor.call(this);
        this._target = null;
        this._callback = null;
        this._isSelected = false;
        this._enabled = false;

        nodeP.setAnchorPoint.call(this, 0.5, 0.5);
        this._target = target || null;
        this._callback = callback || null;
        if (this._callback) {
            this._enabled = true;
        }
    },

    /**
     * return whether MenuItem is selected
     * @return {Boolean}
     */
    isSelected: function () {
        return this._isSelected;
    },
    /**
     * only use for jsbinding
     * @param value
     */
    setOpacityModifyRGB: function (value) {
    },
    /**
     * only use for jsbinding
     * @returns {boolean}
     */
    isOpacityModifyRGB: function () {
        return false;
    },

    /**
     * set the target/selector of the menu item
     * @param {function|String} selector
     * @param {cc.Node} rec
     * @deprecated since v3.0
     */
    setTarget: function (selector, rec) {
        this._target = rec;
        this._callback = selector;
    },

    /**
     * return whether MenuItem is Enabled
     * @return {Boolean}
     */
    isEnabled: function () {
        return this._enabled;
    },

    /**
     * set enable value of MenuItem
     * @param {Boolean} enable
     */
    setEnabled: function (enable) {
        this._enabled = enable;
    },

    /**
     * initializes a cc.MenuItem with callback
     * @param {function|String} callback
     * @param {cc.Node} target
     * @return {Boolean}
     */
    initWithCallback: function (callback, target) {
        this.anchorX = 0.5;
        this.anchorY = 0.5;
        this._target = target;
        this._callback = callback;
        this._enabled = true;
        this._isSelected = false;
        return true;
    },

    /**
     * return rect value of cc.MenuItem
     * @return {cc.Rect}
     */
    rect: function () {
        var locPosition = this._position, locContentSize = this._contentSize, locAnchorPoint = this._anchorPoint;
        return cc.rect(locPosition.x - locContentSize.width * locAnchorPoint.x,
            locPosition.y - locContentSize.height * locAnchorPoint.y,
            locContentSize.width, locContentSize.height);
    },

    /**
     * set the cc.MenuItem selected same as setIsSelected(true)
     */
    selected: function () {
        this._isSelected = true;
    },

    /**
     * set the cc.MenuItem unselected same as setIsSelected(false)
     */
    unselected: function () {
        this._isSelected = false;
    },

    /**
     * set the callback to the menu item
     * @param {function|String} callback
     * @param {cc.Node} target
     */
    setCallback: function (callback, target) {
        this._target = target;
        this._callback = callback;
    },

    /**
     * call the selector with target
     */
    activate: function () {
        if (this._enabled) {
            var locTarget = this._target, locCallback = this._callback;
            if (!locCallback)
                return;
            if (locTarget && cc.isString(locCallback)) {
                locTarget[locCallback](this);
            } else if (locTarget && cc.isFunction(locCallback)) {
                locCallback.call(locTarget, this);
            } else
                locCallback(this);
        }
    }
});

var _p = cc.MenuItem.prototype;

// Extended properties
/** @expose */
_p.enabled;
cc.defineGetterSetter(_p, "enabled", _p.isEnabled, _p.setEnabled);

/**
 * creates an empty menu item with target and callback<br/>
 * Not recommended to use the base class, should use more defined menu item classes
 * @deprecated since v3.0, please use new cc.MenuItem(callback,target) instead
 * @param {function|String} callback callback
 * @param {cc.Node} target
 * @return {cc.MenuItem}
 */
cc.MenuItem.create = function (callback, target) {
    return new cc.MenuItem(callback, target);
};

/**
 *  Any cc.Node that supports the cc.LabelProtocol protocol can be added.<br/>
 * Supported nodes:<br/>
 * - cc.BitmapFontAtlas<br/>
 * - cc.LabelAtlas<br/>
 * - cc.LabelTTF<br/>
 * @class
 * @extends cc.MenuItem
 * @param {cc.Node} label
 * @param {function|String} selector
 * @param {cc.Node} target
 * @example
 * var menuitemLabel = new cc.MenuItemLabel(label,selector,target);
 *
 * @property {String}   string          - Content string of label item
 * @property {cc.Node}  label           - Label of label item
 * @property {cc.Color} disabledColor   - Color of label when it's disabled
 */
cc.MenuItemLabel = cc.MenuItem.extend(/** @lends cc.MenuItemLabel# */{
    _disabledColor: null,
    _label: null,
    _originalScale: 0,
    _colorBackup: null,

    /**
     * Constructor of cc.MenuItemLabel
     * @param {cc.Node} label
     * @param {function|String} selector
     * @param {cc.Node} target
     */
    ctor: function (label, selector, target) {
        cc.MenuItem.prototype.ctor.call(this, selector, target);
        this._disabledColor = null;
        this._label = null;
        this._colorBackup = null;

        if (label) {
            this._originalScale = 1.0;
            this._colorBackup = cc.color.WHITE;
            this._disabledColor = cc.color(126, 126, 126);
            this.setLabel(label);

            this.cascadeColor = true;
            this.cascadeOpacity = true;
        }
    },

    /**
     * return the disable color for this cc.MenuItemLabel
     * @return {cc.Color}
     */
    getDisabledColor: function () {
        return this._disabledColor;
    },

    /**
     * set the disable color for this cc.MenuItemLabel
     * @param {cc.Color} color
     */
    setDisabledColor: function (color) {
        this._disabledColor = color;
    },

    /**
     * return label of cc.MenuItemLabel
     * @return {cc.Node}
     */
    getLabel: function () {
        return this._label;
    },

    /**
     * set a label for cc.MenuItemLabel
     * @param {cc.Node} label
     */
    setLabel: function (label) {
        if (label) {
            this.addChild(label);
            label.anchorX = 0;
            label.anchorY = 0;
            this.width = label.width;
            this.height = label.height;
        }

        if (this._label) {
            this.removeChild(this._label, true);
        }

        this._label = label;
    },

    /**
     * set enable value to cc.MenuItemLabel
     * @param {Boolean} enabled
     */
    setEnabled: function (enabled) {
        if (this._enabled !== enabled) {
            var locLabel = this._label;
            if (!enabled) {
                this._colorBackup = locLabel.color;
                locLabel.color = this._disabledColor;
            } else {
                locLabel.color = this._colorBackup;
            }
        }
        cc.MenuItem.prototype.setEnabled.call(this, enabled);
    },

    /**
     * set opacity for cc.MenuItemLabel
     * @param {Number} opacity from 0-255
     */
    setOpacity: function (opacity) {
        this._label.opacity = opacity;
    },

    /**
     * return the opacity of cc.MenuItemLabel
     * @return {Number}
     */
    getOpacity: function () {
        return this._label.opacity;
    },

    /**
     * set the opacity for cc.MenuItemLabel
     * @param {cc.Color} color
     */
    setColor: function (color) {
        this._label.color = color;
    },

    /**
     * return the color of cc.MenuItemLabel
     * @return {cc.Color}
     */
    getColor: function () {
        return this._label.color;
    },

    /**
     * initializes a cc.MenuItemLabel with a label
     * @param {cc.Node} label
     * @param {function|String} selector
     * @param {cc.Node} target
     * @return {Boolean}
     */
    initWithLabel: function (label, selector, target) {
        this.initWithCallback(selector, target);
        this._originalScale = 1.0;
        this._colorBackup = cc.color.WHITE;
        this._disabledColor = cc.color(126, 126, 126);
        this.setLabel(label);

        this.cascadeColor = true;
        this.cascadeOpacity = true;

        return true;
    },

    /**
     * set the string for  cc.MenuItemLabel
     * @param {String} label
     */
    setString: function (label) {
        this._label.string = label;
        this.width = this._label.width;
        this.height = this._label.height;
    },
    /**
     * return the string of cc.MenuItemLabel
     * @returns {*|string|_p.string|ret.string|q.string|String}
     */
    getString: function () {
        return this._label.string;
    },

    /**
     * activate the menu item
     */
    activate: function () {
        if (this._enabled) {
            this.stopAllActions();
            this.scale = this._originalScale;
            cc.MenuItem.prototype.activate.call(this);
        }
    },

    /**
     * menu item is selected (runs callback)
     */
    selected: function () {
        if (this._enabled) {
            cc.MenuItem.prototype.selected.call(this);

            var action = this.getActionByTag(cc.ZOOM_ACTION_TAG);
            if (action)
                this.stopAction(action);
            else
                this._originalScale = this.scale;

            var zoomAction = cc.scaleTo(0.1, this._originalScale * 1.2);
            zoomAction.setTag(cc.ZOOM_ACTION_TAG);
            this.runAction(zoomAction);
        }
    },

    /**
     * menu item goes back to unselected state
     */
    unselected: function () {
        if (this._enabled) {
            cc.MenuItem.prototype.unselected.call(this);
            this.stopActionByTag(cc.ZOOM_ACTION_TAG);
            var zoomAction = cc.scaleTo(0.1, this._originalScale);
            zoomAction.setTag(cc.ZOOM_ACTION_TAG);
            this.runAction(zoomAction);
        }
    }
});

var _p = cc.MenuItemLabel.prototype;

// Extended properties
/** @expose */
_p.string;
cc.defineGetterSetter(_p, "string", _p.getString, _p.setString);
/** @expose */
_p.disabledColor;
cc.defineGetterSetter(_p, "disabledColor", _p.getDisabledColor, _p.setDisabledColor);
/** @expose */
_p.label;
cc.defineGetterSetter(_p, "label", _p.getLabel, _p.setLabel);


/**
 * @deprecated since v3.0 ,please use new cc.MenuItemLabel(label,selector,target) instead
 * @param {cc.Node} label
 * @param {function|String|Null} [selector=]
 * @param {cc.Node|Null} [target=]
 * @return {cc.MenuItemLabel}
 */
cc.MenuItemLabel.create = function (label, selector, target) {
    return new cc.MenuItemLabel(label, selector, target);
};

/**
 * Helper class that creates a MenuItemLabel class with a LabelAtlas
 * @class
 * @extends cc.MenuItemLabel
 * @param {String} value
 * @param {String} charMapFile
 * @param {Number} itemWidth
 * @param {Number} itemHeight
 * @param {String} startCharMap a single character
 * @param {function|String|Null} callback
 * @param {cc.Node|Null} target
 * @example
 * var menuItem = new cc.MenuItemAtlasFont(param1,param2...);
 */
cc.MenuItemAtlasFont = cc.MenuItemLabel.extend(/** @lends cc.MenuItemAtlasFont# */{

    /**
     * the contructor of cc.MenuItemAtlasFont
     * @param {String} value
     * @param {String} charMapFile
     * @param {Number} itemWidth
     * @param {Number} itemHeight
     * @param {String} startCharMap a single character
     * @param {function|String|Null} callback
     * @param {cc.Node|Null} target
     */
    ctor: function (value, charMapFile, itemWidth, itemHeight, startCharMap, callback, target) {
        var label;
        if (value && value.length > 0) {
            label = new cc.LabelAtlas(value, charMapFile, itemWidth, itemHeight, startCharMap);
        }

        cc.MenuItemLabel.prototype.ctor.call(this, label, callback, target);
    },

    /**
     * initializes a cc.MenuItemAtlasFont with string
     * @param {String} value
     * @param {String} charMapFile
     * @param {Number} itemWidth
     * @param {Number} itemHeight
     * @param {String} startCharMap a single character
     * @param {function|String|Null} callback
     * @param {cc.Node|Null} target
     * @return {Boolean}
     */
    initWithString: function (value, charMapFile, itemWidth, itemHeight, startCharMap, callback, target) {
        if (!value || value.length === 0)
            throw "cc.MenuItemAtlasFont.initWithString(): value should be non-null and its length should be greater than 0";

        var label = new cc.LabelAtlas();
        label.initWithString(value, charMapFile, itemWidth, itemHeight, startCharMap);
        if (this.initWithLabel(label, callback, target)) {
            // do something ?
        }
        return true;
    }
});

/**
 * create menu item from string with font
 * @deprecated since v3.0 ,please use new cc.MenuItemAtlasFont() instead.
 * @param {String} value the text to display
 * @param {String} charMapFile the character map file
 * @param {Number} itemWidth
 * @param {Number} itemHeight
 * @param {String} startCharMap a single character
 * @param {function|String|Null} [callback=null]
 * @param {cc.Node|Null} [target=]
 * @return {cc.MenuItemAtlasFont}
 */
cc.MenuItemAtlasFont.create = function (value, charMapFile, itemWidth, itemHeight, startCharMap, callback, target) {
    return new cc.MenuItemAtlasFont(value, charMapFile, itemWidth, itemHeight, startCharMap, callback, target);
};

/**
 * Helper class that creates a CCMenuItemLabel class with a Label
 * @class
 * @extends cc.MenuItemLabel
 * @param {String} value text for the menu item
 * @param {function|String} callback
 * @param {cc.Node} target
 * @example
 * var menuItem = new cc.MenuItemFont(value, callback, target);
 *
 * @property {Number}   fontSize    - Font size of font item
 * @property {String}   fontName    - Font name of font item
 */
cc.MenuItemFont = cc.MenuItemLabel.extend(/** @lends cc.MenuItemFont# */{
    _fontSize: null,
    _fontName: null,

    /**
     * Constructor of cc.MenuItemFont
     * @param {String} value text for the menu item
     * @param {function|String} callback
     * @param {cc.Node} target
     */
    ctor: function (value, callback, target) {
        var label;
        if (value && value.length > 0) {
            this._fontName = cc._globalFontName;
            this._fontSize = cc._globalFontSize;
            label = new cc.LabelTTF(value, this._fontName, this._fontSize);
        }
        else {
            this._fontSize = 0;
            this._fontName = "";
        }

        cc.MenuItemLabel.prototype.ctor.call(this, label, callback, target);
    },

    /**
     * initializes cc.MenuItemFont with  string
     * @param {String} value text for the menu item
     * @param {function|String} callback
     * @param {cc.Node} target
     * @return {Boolean}
     */
    initWithString: function (value, callback, target) {
        if (!value || value.length === 0)
            throw "Value should be non-null and its length should be greater than 0";

        this._fontName = cc._globalFontName;
        this._fontSize = cc._globalFontSize;

        var label = new cc.LabelTTF(value, this._fontName, this._fontSize);
        if (this.initWithLabel(label, callback, target)) {
            // do something ?
        }
        return true;
    },

    /**
     * set the font size for cc.MenuItemFont
     * @param {Number} s
     */
    setFontSize: function (s) {
        this._fontSize = s;
        this._recreateLabel();
    },

    /**
     *return the font size of cc.MenuItemFont
     * @return {Number}
     */
    getFontSize: function () {
        return this._fontSize;
    },

    /**
     * set the font name for cc.MenuItemFont
     * @param {String} name
     */
    setFontName: function (name) {
        this._fontName = name;
        this._recreateLabel();
    },

    /**
     * return the font name for cc.MenuItemFont
     * @return {String}
     */
    getFontName: function () {
        return this._fontName;
    },

    _recreateLabel: function () {
        var label = new cc.LabelTTF(this._label.string, this._fontName, this._fontSize);
        this.setLabel(label);
    }
});

/**
 * a shared function to set the fontSize for menuitem font
 * @param {Number} fontSize
 */
cc.MenuItemFont.setFontSize = function (fontSize) {
    cc._globalFontSize = fontSize;
};

/**
 * a shared function to get the font size for menuitem font
 * @return {Number}
 */
cc.MenuItemFont.fontSize = function () {
    return cc._globalFontSize;
};

/**
 * a shared function to set the fontsize for menuitem font
 * @param name
 */
cc.MenuItemFont.setFontName = function (name) {
    if (cc._globalFontNameRelease) {
        cc._globalFontName = '';
    }
    cc._globalFontName = name;
    cc._globalFontNameRelease = true;
};

var _p = cc.MenuItemFont.prototype;

// Extended properties
/** @expose */
_p.fontSize;
cc.defineGetterSetter(_p, "fontSize", _p.getFontSize, _p.setFontSize);
/** @expose */
_p.fontName;
cc.defineGetterSetter(_p, "fontName", _p.getFontName, _p.setFontName);


/**
 * a shared function to get the font name for menuitem font
 * @return {String}
 */
cc.MenuItemFont.fontName = function () {
    return cc._globalFontName;
};

/**
 * create a menu item from string
 * @deprecated since v3.0, please use new construction instead
 * @param {String} value the text to display
 * @param {String|function|Null} callback the callback to run, either in function name or pass in the actual function
 * @param {cc.Node|Null} target the target to run callback
 * @return {cc.MenuItemFont}
 */
cc.MenuItemFont.create = function (value, callback, target) {
    return new cc.MenuItemFont(value, callback, target);
};


/**
 * CCMenuItemSprite accepts CCNode<CCRGBAProtocol> objects as items.<br/>
 * The images has 3 different states:<br/>
 *   - unselected image<br/>
 *   - selected image<br/>
 *   - disabled image<br/>
 * @class
 * @extends cc.MenuItem
 * @param {Image|Null} normalSprite normal state image
 * @param {Image|Null} selectedSprite selected state image
 * @param {Image|cc.Node|Null} three disabled state image OR target node
 * @param {String|function|cc.Node|Null} four callback function name in string or actual function, OR target Node
 * @param {String|function|Null} five callback function name in string or actual function
 *
 * @example
 * var item = new cc.MenuItemSprite(normalImage)//create a menu item from a sprite with no functionality
 * var item = new cc.MenuItemSprite(normalImage, selectedImage)//create a menu Item, nothing will happen when clicked
 * var item = new cc.MenuItemSprite(normalImage, SelectedImage, disabledImage)//same above, but with disabled state image
 * var item = new cc.MenuItemSprite(normalImage, SelectedImage, 'callback', targetNode)//create a menu item, when clicked runs targetNode.callback()
 * var item = new cc.MenuItemSprite(normalImage, SelectedImage, disabledImage, targetNode.callback, targetNode)
 * //same as above, but with disabled image, and passing in callback function
 *
 * @property {cc.Sprite}    normalImage     - Sprite in normal state
 * @property {cc.Sprite}    selectedImage     - Sprite in selected state
 * @property {cc.Sprite}    disabledImage     - Sprite in disabled state
 */
cc.MenuItemSprite = cc.MenuItem.extend(/** @lends cc.MenuItemSprite# */{
    _normalImage: null,
    _selectedImage: null,
    _disabledImage: null,

    /**
     * Constructor of cc.MenuItemSprite
     * @param {Image|Null} normalSprite normal state image
     * @param {Image|Null} selectedSprite selected state image
     * @param {Image|cc.Node|Null} three disabled state image OR target node
     * @param {String|function|cc.Node|Null} four callback function name in string or actual function, OR target Node
     * @param {String|function|Null} five callback function name in string or actual function
     */
    ctor: function (normalSprite, selectedSprite, three, four, five) {
        cc.MenuItem.prototype.ctor.call(this);
        this._normalImage = null;
        this._selectedImage = null;
        this._disabledImage = null;

        if (selectedSprite !== undefined) {
            //normalSprite = normalSprite;
            //selectedSprite = selectedSprite;
            var disabledImage, target, callback;
            //when you send 4 arguments, five is undefined
            if (five !== undefined) {
                disabledImage = three;
                callback = four;
                target = five;
            } else if (four !== undefined && cc.isFunction(four)) {
                disabledImage = three;
                callback = four;
            } else if (four !== undefined && cc.isFunction(three)) {
                target = four;
                callback = three;
                disabledImage = null;
            } else if (three === undefined) {
                disabledImage = null;
            }
            this.initWithNormalSprite(normalSprite, selectedSprite, disabledImage, callback, target);
        }
    },

    /**
     * return the normal status image(cc.Sprite)
     * @return {cc.Sprite}
     */
    getNormalImage: function () {
        return this._normalImage;
    },

    /**
     * set the normal status image(cc.Sprite)
     * @param {cc.Sprite} normalImage
     */
    setNormalImage: function (normalImage) {
        if (this._normalImage === normalImage) {
            return;
        }
        if (normalImage) {
            this.addChild(normalImage, 0, cc.NORMAL_TAG);
            normalImage.anchorX = 0;
            normalImage.anchorY = 0;
        }
        if (this._normalImage) {
            this.removeChild(this._normalImage, true);
        }

        this._normalImage = normalImage;
        this.width = this._normalImage.width;
        this.height = this._normalImage.height;
        this._updateImagesVisibility();

        if (normalImage.textureLoaded && !normalImage.textureLoaded()) {
            normalImage.addEventListener("load", function (sender) {
                this.width = sender.width;
                this.height = sender.height;
            }, this);
        }
    },

    /**
     * return the selected status image(cc.Sprite) of cc.MenuItemSprite
     * @return {cc.Sprite}
     */
    getSelectedImage: function () {
        return this._selectedImage;
    },

    /**
     * set the selected status image(cc.Sprite)
     * @param {cc.Sprite} selectedImage
     */
    setSelectedImage: function (selectedImage) {
        if (this._selectedImage === selectedImage)
            return;

        if (selectedImage) {
            this.addChild(selectedImage, 0, cc.SELECTED_TAG);
            selectedImage.anchorX = 0;
            selectedImage.anchorY = 0;
        }

        if (this._selectedImage) {
            this.removeChild(this._selectedImage, true);
        }

        this._selectedImage = selectedImage;
        this._updateImagesVisibility();
    },

    /**
     * return the disabled status of cc.MenuItemSprite
     * @return {cc.Sprite}
     */
    getDisabledImage: function () {
        return this._disabledImage;
    },

    /**
     * set the disabled status image(cc.Sprite)
     * @param {cc.Sprite} disabledImage
     */
    setDisabledImage: function (disabledImage) {
        if (this._disabledImage === disabledImage)
            return;

        if (disabledImage) {
            this.addChild(disabledImage, 0, cc.DISABLE_TAG);
            disabledImage.anchorX = 0;
            disabledImage.anchorY = 0;
        }

        if (this._disabledImage)
            this.removeChild(this._disabledImage, true);

        this._disabledImage = disabledImage;
        this._updateImagesVisibility();
    },

    /**
     * initializes cc.MenuItemSprite with a cc.Sprite
     * @param {cc.Node} normalSprite
     * @param {cc.Node} selectedSprite
     * @param {cc.Node} disabledSprite
     * @param {function|String} callback
     * @param {cc.Node} target
     * @return {Boolean}
     */
    initWithNormalSprite: function (normalSprite, selectedSprite, disabledSprite, callback, target) {
        this.initWithCallback(callback, target);
        this.setNormalImage(normalSprite);
        this.setSelectedImage(selectedSprite);
        this.setDisabledImage(disabledSprite);
        var locNormalImage = this._normalImage;
        if (locNormalImage) {
            this.width = locNormalImage.width;
            this.height = locNormalImage.height;

            if (locNormalImage.textureLoaded && !locNormalImage.textureLoaded()) {
                locNormalImage.addEventListener("load", function (sender) {
                    this.width = sender.width;
                    this.height = sender.height;
                    this.cascadeColor = true;
                    this.cascadeOpacity = true;
                }, this);
            }
        }
        this.cascadeColor = true;
        this.cascadeOpacity = true;
        return true;
    },

    /**
     * set the color for cc.MenuItemSprite
     * @param {cc.Color} color
     */
    setColor: function (color) {
        this._normalImage.color = color;

        if (this._selectedImage)
            this._selectedImage.color = color;

        if (this._disabledImage)
            this._disabledImage.color = color;
    },

    /**
     * return the color of cc.MenuItemSprite
     * @return {cc.Color}
     */
    getColor: function () {
        return this._normalImage.color;
    },

    /**
     * set the opacity for cc.MenuItemSprite
     * @param {Number} opacity 0 - 255
     */
    setOpacity: function (opacity) {
        this._normalImage.opacity = opacity;

        if (this._selectedImage)
            this._selectedImage.opacity = opacity;

        if (this._disabledImage)
            this._disabledImage.opacity = opacity;
    },

    /**
     * return the opacity of cc.MenuItemSprite
     * @return {Number} opacity from 0 - 255
     */
    getOpacity: function () {
        return this._normalImage.opacity;
    },

    /**
     * menu item is selected (runs callback)
     */
    selected: function () {
        cc.MenuItem.prototype.selected.call(this);
        if (this._normalImage) {
            if (this._disabledImage)
                this._disabledImage.visible = false;

            if (this._selectedImage) {
                this._normalImage.visible = false;
                this._selectedImage.visible = true;
            } else
                this._normalImage.visible = true;
        }
    },

    /**
     * menu item goes back to unselected state
     */
    unselected: function () {
        cc.MenuItem.prototype.unselected.call(this);
        if (this._normalImage) {
            this._normalImage.visible = true;

            if (this._selectedImage)
                this._selectedImage.visible = false;

            if (this._disabledImage)
                this._disabledImage.visible = false;
        }
    },

    /**
     * set cc.MenuItemSprite  enable to receive the touch event
     * @param {Boolean} bEnabled
     */
    setEnabled: function (bEnabled) {
        if (this._enabled !== bEnabled) {
            cc.MenuItem.prototype.setEnabled.call(this, bEnabled);
            this._updateImagesVisibility();
        }
    },

    _updateImagesVisibility: function () {
        var locNormalImage = this._normalImage, locSelImage = this._selectedImage, locDisImage = this._disabledImage;
        if (this._enabled) {
            if (locNormalImage)
                locNormalImage.visible = true;
            if (locSelImage)
                locSelImage.visible = false;
            if (locDisImage)
                locDisImage.visible = false;
        } else {
            if (locDisImage) {
                if (locNormalImage)
                    locNormalImage.visible = false;
                if (locSelImage)
                    locSelImage.visible = false;
                if (locDisImage)
                    locDisImage.visible = true;
            } else {
                if (locNormalImage)
                    locNormalImage.visible = true;
                if (locSelImage)
                    locSelImage.visible = false;
            }
        }
    }
});

var _p = cc.MenuItemSprite.prototype;

// Extended properties
/** @expose */
_p.normalImage;
cc.defineGetterSetter(_p, "normalImage", _p.getNormalImage, _p.setNormalImage);
/** @expose */
_p.selectedImage;
cc.defineGetterSetter(_p, "selectedImage", _p.getSelectedImage, _p.setSelectedImage);
/** @expose */
_p.disabledImage;
cc.defineGetterSetter(_p, "disabledImage", _p.getDisabledImage, _p.setDisabledImage);

/**
 * create a menu item from sprite
 * @deprecated since v3.0 please use new cc.MenuItemSprite(normalSprite, selectedSprite, three, four, five) instead
 * @param {Image} normalSprite normal state image
 * @param {Image|Null} selectedSprite selected state image
 * @param {Image|cc.Node|Null} three disabled state image OR target node
 * @param {String|function|cc.Node|Null} four callback function name in string or actual function, OR target Node
 * @param {String|function|Null} five callback function name in string or actual function
 * @return {cc.MenuItemSprite}
 */
cc.MenuItemSprite.create = function (normalSprite, selectedSprite, three, four, five) {
    return new cc.MenuItemSprite(normalSprite, selectedSprite, three, four, five || undefined);
};

/**
 * cc.MenuItemImage accepts images as items.<br/>
 * The images has 3 different states:<br/>
 * - unselected image<br/>
 * - selected image<br/>
 * - disabled image<br/>
 * <br/>
 * For best results try that all images are of the same size<br/>
 * @class
 * @extends cc.MenuItemSprite
 * @param {string|null} normalImage
 * @param {string|null} selectedImage
 * @param {string|null} disabledImage
 * @param {function|string|null} callback
 * @param {cc.Node|null} target
 * @example
 * var menuItem = new cc.MenuItemImage(normalImage, selectedImage, three, four, five);
 */
cc.MenuItemImage = cc.MenuItemSprite.extend(/** @lends cc.MenuItemImage# */{

    /**
     * Constructor of cc.MenuItemImage
     * @param {string|null} normalImage
     * @param {string|null} selectedImage
     * @param {string|null} disabledImage
     * @param {function|string|null} callback
     * @param {cc.Node|null} target
     */
    ctor: function (normalImage, selectedImage, three, four, five) {
        var normalSprite = null,
            selectedSprite = null,
            disabledSprite = null,
            callback = null,
            target = null;

        if (normalImage === undefined) {
            cc.MenuItemSprite.prototype.ctor.call(this);
        }
        else {
            normalSprite = new cc.Sprite(normalImage);
            selectedImage &&
            (selectedSprite = new cc.Sprite(selectedImage));
            if (four === undefined) {
                callback = three;
            }
            else if (five === undefined) {
                callback = three;
                target = four;
            }
            else if (five) {
                disabledSprite = new cc.Sprite(three);
                callback = four;
                target = five;
            }
            cc.MenuItemSprite.prototype.ctor.call(this, normalSprite, selectedSprite, disabledSprite, callback, target);
        }
    },

    /**
     * sets the sprite frame for the normal image
     * @param {cc.SpriteFrame} frame
     */
    setNormalSpriteFrame: function (frame) {
        this.setNormalImage(new cc.Sprite(frame));
    },

    /**
     * sets the sprite frame for the selected image
     * @param {cc.SpriteFrame} frame
     */
    setSelectedSpriteFrame: function (frame) {
        this.setSelectedImage(new cc.Sprite(frame));
    },

    /**
     * sets the sprite frame for the disabled image
     * @param {cc.SpriteFrame} frame
     */
    setDisabledSpriteFrame: function (frame) {
        this.setDisabledImage(new cc.Sprite(frame));
    },

    /**
     * initializes a cc.MenuItemImage
     * @param {string|null} normalImage
     * @param {string|null} selectedImage
     * @param {string|null} disabledImage
     * @param {function|string|null} callback
     * @param {cc.Node|null} target
     * @returns {boolean}
     */
    initWithNormalImage: function (normalImage, selectedImage, disabledImage, callback, target) {
        var normalSprite = null;
        var selectedSprite = null;
        var disabledSprite = null;

        if (normalImage) {
            normalSprite = new cc.Sprite(normalImage);
        }
        if (selectedImage) {
            selectedSprite = new cc.Sprite(selectedImage);
        }
        if (disabledImage) {
            disabledSprite = new cc.Sprite(disabledImage);
        }
        return this.initWithNormalSprite(normalSprite, selectedSprite, disabledSprite, callback, target);
    }
});

/**
 * creates a new menu item image
 * @deprecated since v3.0, please use new cc.MenuItemImage(normalImage, selectedImage, three, four, five) instead.
 * @param {String} normalImage file name for normal state
 * @param {String} selectedImage image for selected state
 * @param {String|cc.Node} three Disabled image OR callback function
 * @param {String|function|Null} [four] callback function, either name in string or pass the whole function OR the target
 * @param {cc.Node|String|function|Null} [five] cc.Node target to run callback when clicked
 * @return {cc.MenuItemImage}
 */
cc.MenuItemImage.create = function (normalImage, selectedImage, three, four, five) {
    return new cc.MenuItemImage(normalImage, selectedImage, three, four, five);
};


/**
 * A simple container class that "toggles" it's inner items<br/>
 * The inner items can be any MenuItem
 * @class
 * @extends cc.MenuItem
 *
 * @property {Array}    subItems        - Sub items
 * @property {Number}   selectedIndex   - Index of selected sub item
 *
 *@example
 * // Example
 * //create a toggle item with 2 menu items (which you can then toggle between them later)
 * var toggler = new cc.MenuItemToggle( new cc.MenuItemFont("On"), new cc.MenuItemFont("Off"), this.callback, this)
 * //Note: the first param is the target, the second is the callback function, afterwards, you can pass in any number of menuitems
 *
 * //if you pass only 1 variable, then it must be a cc.MenuItem
 * var notYetToggler = new cc.MenuItemToggle(cc.MenuItemFont("On"));//it is useless right now, until you add more stuff to it
 * notYetToggler.addSubItem(new cc.MenuItemFont("Off"));
 * //this is useful for constructing a toggler without a callback function (you wish to control the behavior from somewhere else)
 */
cc.MenuItemToggle = cc.MenuItem.extend(/** @lends cc.MenuItemToggle# */{
    subItems: null,

    _selectedIndex: 0,
    _opacity: null,
    _color: null,

    /**
     * Constructor of cc.MenuItemToggle
    */
    ctor: function (/*Multiple arguments follow*/) {

        cc.MenuItem.prototype.ctor.call(this);
        this._selectedIndex = 0;
        this.subItems = [];
        this._opacity = 0;
        this._color = cc.color.WHITE;

        if(arguments.length > 0)
            this.initWithItems(Array.prototype.slice.apply(arguments));

    },

    /**
     * return the opacity of cc.MenuItemToggle
     * @return {Number}
     */
    getOpacity: function () {
        return this._opacity;
    },

    /**
     * set the opacity for cc.MenuItemToggle
     * @param {Number} opacity
     */
    setOpacity: function (opacity) {
        this._opacity = opacity;
        if (this.subItems && this.subItems.length > 0) {
            for (var it = 0; it < this.subItems.length; it++) {
                this.subItems[it].opacity = opacity;
            }
        }
        this._color.a = opacity;
    },

    /**
     * return the color of cc.MenuItemToggle
     * @return {cc.Color}
     */
    getColor: function () {
        var locColor = this._color;
        return cc.color(locColor.r, locColor.g, locColor.b, locColor.a);
    },

    /**
     * set the color for cc.MenuItemToggle
     * @param {cc.Color} Color
     */
    setColor: function (color) {
        var locColor = this._color;
        locColor.r = color.r;
        locColor.g = color.g;
        locColor.b = color.b;

        if (this.subItems && this.subItems.length > 0) {
            for (var it = 0; it < this.subItems.length; it++) {
                this.subItems[it].setColor(color);
            }
        }

        if (color.a !== undefined && !color.a_undefined) {
            this.setOpacity(color.a);
        }
    },

    /**
     * return the index of selected
     * @return {Number}
     */
    getSelectedIndex: function () {
        return this._selectedIndex;
    },

    /**
     * set the seleceted index for cc.MenuItemToggle
     * @param {Number} SelectedIndex
     */
    setSelectedIndex: function (SelectedIndex) {
        if (SelectedIndex !== this._selectedIndex) {
            this._selectedIndex = SelectedIndex;
            var currItem = this.getChildByTag(cc.CURRENT_ITEM);
            if (currItem)
                currItem.removeFromParent(false);

            var item = this.subItems[this._selectedIndex];
            this.addChild(item, 0, cc.CURRENT_ITEM);
            var w = item.width, h = item.height;
            this.width = w;
            this.height = h;
            item.setPosition(w / 2, h / 2);
        }
    },

    /**
     * similar to get children,return the sumItem array.
     * @return {Array}
     */
    getSubItems: function () {
        return this.subItems;
    },

    /**
     * set the subitem for cc.MenuItemToggle
     * @param {cc.MenuItem} subItems
     */
    setSubItems: function (subItems) {
        this.subItems = subItems;
    },

    /**
     * initializes a cc.MenuItemToggle with items
     * @param {cc.MenuItem} args[0...last-2] the rest in the array are cc.MenuItems
     * @param {function|String} args[last-1] the second item in the args array is the callback
     * @param {cc.Node} args[last] the first item in the args array is a target
     * @return {Boolean}
     */
    initWithItems: function (args) {
        var l = args.length;
        // passing callback.
        if (cc.isFunction(args[args.length - 2])) {
            this.initWithCallback(args[args.length - 2], args[args.length - 1]);
            l = l - 2;
        } else if (cc.isFunction(args[args.length - 1])) {
            this.initWithCallback(args[args.length - 1], null);
            l = l - 1;
        } else {
            this.initWithCallback(null, null);
        }

        var locSubItems = this.subItems;
        locSubItems.length = 0;
        for (var i = 0; i < l; i++) {
            if (args[i])
                locSubItems.push(args[i]);
        }
        this._selectedIndex = cc.UINT_MAX;
        this.setSelectedIndex(0);

        this.cascadeColor = true;
        this.cascadeOpacity = true;

        return true;
    },

    /**
     * add the subitem for cc.MenuItemToggle
     * @param {cc.MenuItem} item
     */
    addSubItem: function (item) {
        this.subItems.push(item);
    },

    /**
     * activate the menu item
     */
    activate: function () {
        // update index
        if (this._enabled) {
            var newIndex = (this._selectedIndex + 1) % this.subItems.length;
            this.setSelectedIndex(newIndex);
        }
        cc.MenuItem.prototype.activate.call(this);
    },

    /**
     * menu item is selected (runs callback)
     */
    selected: function () {
        cc.MenuItem.prototype.selected.call(this);
        this.subItems[this._selectedIndex].selected();
    },

    /**
     * menu item goes back to unselected state
     */
    unselected: function () {
        cc.MenuItem.prototype.unselected.call(this);
        this.subItems[this._selectedIndex].unselected();
    },

    /**
     * set the enable status for cc.MenuItemToggle
     * @param {Boolean} enabled
     */
    setEnabled: function (enabled) {
        if (this._enabled !== enabled) {
            cc.MenuItem.prototype.setEnabled.call(this, enabled);
            var locItems = this.subItems;
            if (locItems && locItems.length > 0) {
                for (var it = 0; it < locItems.length; it++)
                    locItems[it].enabled = enabled;
            }
        }
    },

    /**
     * returns the selected item   (deprecated in -x, please use getSelectedItem instead.)
     * @return {cc.MenuItem}
     */
    selectedItem: function () {
        return this.subItems[this._selectedIndex];
    },

    /**
     * returns the selected item.
     * @return {cc.MenuItem}
     */
    getSelectedItem: function() {
        return this.subItems[this._selectedIndex];
    },

    /**
     * * <p>
     *     Event callback that is invoked every time when cc.MenuItemToggle enters the 'stage'.                                   <br/>
     *     If the cc.MenuItemToggle enters the 'stage' with a transition, this event is called when the transition starts.        <br/>
     *     During onEnter you can't access a "sister/brother" node.                                                    <br/>
     *     If you override onEnter, you must call its parent's onEnter function with this._super().
     * </p>
     */
    onEnter: function () {
        cc.Node.prototype.onEnter.call(this);
        this.setSelectedIndex(this._selectedIndex);
    }
});

var _p = cc.MenuItemToggle.prototype;

// Extended properties
/** @expose */
_p.selectedIndex;
cc.defineGetterSetter(_p, "selectedIndex", _p.getSelectedIndex, _p.setSelectedIndex);


/**
 * create a simple container class that "toggles" it's inner items<br/>
 * The inner items can be any MenuItem
 * @deprecated since v3.0 please use new cc.MenuItemToggle(params) instead
 * @return {cc.MenuItemToggle}
 * @example
 */
cc.MenuItemToggle.create = function (/*Multiple arguments follow*/) {
    if ((arguments.length > 0) && (arguments[arguments.length - 1] == null))
        cc.log("parameters should not be ending with null in Javascript");
    var ret = new cc.MenuItemToggle();
    ret.initWithItems(Array.prototype.slice.apply(arguments));
    return ret;
};
