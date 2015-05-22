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
 * Base class for ccui.Margin
 * @class
 * @extends ccui.Class
 *
 * @property {Number}           left       - Left of margin
 * @property {Number}           top        - Top of margin
 * @property {Number}           right      - right of margin
 * @property {Number}           bottom     - bottom of margin
 */
ccui.Margin = ccui.Class.extend(/** @lends ccui.Margin# */{
    left: 0,
    top: 0,
    right: 0,
    bottom: 0,
    /**
     * Constructor of ccui.Margin.
     * @param {Number|ccui.Margin} margin a margin or left
     * @param {Number} [top]
     * @param {Number} [right]
     * @param {Number} [bottom]
     */
    ctor: function (margin, top, right, bottom) {
        if (margin !== undefined && top === undefined) {
            this.left = margin.left;
            this.top = margin.top;
            this.right = margin.right;
            this.bottom = margin.bottom;
        }
        if (bottom !== undefined) {
            this.left = margin;
            this.top = top;
            this.right = right;
            this.bottom = bottom;
        }
    },
    /**
     * Sets boundary of margin
     * @param {Number} l left
     * @param {Number} t top
     * @param {Number} r right
     * @param {Number} b bottom
     */
    setMargin: function (l, t, r, b) {
        this.left = l;
        this.top = t;
        this.right = r;
        this.bottom = b;
    },
    /**
     * Checks target whether equals itself.
     * @param {ccui.Margin} target
     * @returns {boolean}
     */
    equals: function (target) {
        return (this.left === target.left && this.top === target.top && this.right === target.right && this.bottom === target.bottom);
    }
});

/**
 * Gets a zero margin object
 * @function
 * @returns {ccui.Margin}
 */
ccui.MarginZero = function(){
    return new ccui.Margin(0,0,0,0);
};

/**
 * Layout parameter contains a margin and layout parameter type. It uses for ccui.LayoutManager.
 * @class
 * @extends ccui.Class
 */
ccui.LayoutParameter = ccui.Class.extend(/** @lends ccui.LayoutParameter# */{
    _margin: null,
    _layoutParameterType: null,

    /**
     * The constructor of ccui.LayoutParameter.
     * @function
     */
    ctor: function () {
        this._margin = new ccui.Margin();
        this._layoutParameterType = ccui.LayoutParameter.NONE;
    },

    /**
     * Sets Margin to LayoutParameter.
     * @param {ccui.Margin} margin
     */
    setMargin: function (margin) {
        if(cc.isObject(margin)){
            this._margin.left = margin.left;
            this._margin.top = margin.top;
            this._margin.right = margin.right;
            this._margin.bottom = margin.bottom;
        }else{
            this._margin.left = arguments[0];
            this._margin.top = arguments[1];
            this._margin.right = arguments[2];
            this._margin.bottom = arguments[3];
        }
    },

    /**
     * Gets Margin of LayoutParameter.
     * @returns {ccui.Margin}
     */
    getMargin: function () {
        return this._margin;
    },

    /**
     * Gets LayoutParameterType of LayoutParameter.
     * @returns {Number}
     */
    getLayoutType: function () {
        return this._layoutParameterType;
    },

    /**
     * Clones a ccui.LayoutParameter object from itself.
     * @returns {ccui.LayoutParameter}
     */
    clone:function(){
        var parameter = this._createCloneInstance();
        parameter._copyProperties(this);
        return parameter;
    },

    /**
     * create clone instance.
     * @returns {ccui.LayoutParameter}
     */
    _createCloneInstance:function(){
        return new ccui.LayoutParameter();
    },

    /**
     * copy properties from model.
     * @param {ccui.LayoutParameter} model
     */
    _copyProperties:function(model){
        this._margin.bottom = model._margin.bottom;
        this._margin.left = model._margin.left;
        this._margin.right = model._margin.right;
        this._margin.top = model._margin.top;
    }
});

/**
 * allocates and initializes a LayoutParameter.
 * @constructs
 * @return {ccui.LayoutParameter}
 */
ccui.LayoutParameter.create = function () {
    return new ccui.LayoutParameter();
};

// Constants
//layout parameter type
/**
 * The none of ccui.LayoutParameter's type.
 * @constant
 * @type {number}
 */
ccui.LayoutParameter.NONE = 0;
/**
 * The linear of ccui.LayoutParameter's type.
 * @constant
 * @type {number}
 */
ccui.LayoutParameter.LINEAR = 1;
/**
 * The relative of ccui.LayoutParameter's type.
 * @constant
 * @type {number}
 */
ccui.LayoutParameter.RELATIVE = 2;

/**
 * The linear of Layout parameter. its parameter type is ccui.LayoutParameter.LINEAR.
 * @class
 * @extends ccui.LayoutParameter
 */
ccui.LinearLayoutParameter = ccui.LayoutParameter.extend(/** @lends ccui.LinearLayoutParameter# */{
    _linearGravity: null,
    /**
     * The constructor of ccui.LinearLayoutParameter.
     * @function
     */
    ctor: function () {
        ccui.LayoutParameter.prototype.ctor.call(this);
        this._linearGravity = ccui.LinearLayoutParameter.NONE;
        this._layoutParameterType = ccui.LayoutParameter.LINEAR;
    },

    /**
     * Sets LinearGravity to LayoutParameter.
     * @param {Number} gravity
     */
    setGravity: function (gravity) {
        this._linearGravity = gravity;
    },

    /**
     * Gets LinearGravity of LayoutParameter.
     * @returns {Number}
     */
    getGravity: function () {
        return this._linearGravity;
    },

    _createCloneInstance: function () {
        return new ccui.LinearLayoutParameter();
    },

    _copyProperties: function (model) {
        ccui.LayoutParameter.prototype._copyProperties.call(this, model);
        if (model instanceof ccui.LinearLayoutParameter)
            this.setGravity(model._linearGravity);
    }
});

/**
 * allocates and initializes a LinearLayoutParameter.
 * @constructs
 * @return {ccui.LinearLayoutParameter}
 * @deprecated since v3.0, please use new construction instead
 */
ccui.LinearLayoutParameter.create = function () {
    return new ccui.LinearLayoutParameter();
};

// Constants
//Linear layout parameter LinearGravity
/**
 * The none of ccui.LinearLayoutParameter's linear gravity.
 * @constant
 * @type {number}
 */
ccui.LinearLayoutParameter.NONE = 0;

/**
 * The left of ccui.LinearLayoutParameter's linear gravity.
 * @constant
 * @type {number}
 */
ccui.LinearLayoutParameter.LEFT = 1;
/**
 * The top of ccui.LinearLayoutParameter's linear gravity.
 * @constant
 * @type {number}
 */
ccui.LinearLayoutParameter.TOP = 2;
/**
 * The right of ccui.LinearLayoutParameter's linear gravity.
 * @constant
 * @type {number}
 */
ccui.LinearLayoutParameter.RIGHT = 3;
/**
 * The bottom of ccui.LinearLayoutParameter's linear gravity.
 * @constant
 * @type {number}
 */
ccui.LinearLayoutParameter.BOTTOM = 4;
/**
 * The center vertical of ccui.LinearLayoutParameter's linear gravity.
 * @constant
 * @type {number}
 */
ccui.LinearLayoutParameter.CENTER_VERTICAL = 5;
/**
 * The center horizontal of ccui.LinearLayoutParameter's linear gravity.
 * @constant
 * @type {number}
 */
ccui.LinearLayoutParameter.CENTER_HORIZONTAL = 6;

/**
 * The relative of layout parameter. Its layout parameter type is ccui.LayoutParameter.RELATIVE.
 * @class
 * @extends ccui.LayoutParameter
 */
ccui.RelativeLayoutParameter = ccui.LayoutParameter.extend(/** @lends ccui.RelativeLayoutParameter# */{
    _relativeAlign: null,
    _relativeWidgetName: "",
    _relativeLayoutName: "",
    _put:false,
    /**
     * The constructor of ccui.RelativeLayoutParameter
     * @function
     */
    ctor: function () {
        ccui.LayoutParameter.prototype.ctor.call(this);
        this._relativeAlign = ccui.RelativeLayoutParameter.NONE;
        this._relativeWidgetName = "";
        this._relativeLayoutName = "";
        this._put = false;
        this._layoutParameterType = ccui.LayoutParameter.RELATIVE;
    },

    /**
     * Sets RelativeAlign parameter for LayoutParameter.
     * @param {Number} align
     */
    setAlign: function (align) {
        this._relativeAlign = align;
    },

    /**
     * Gets RelativeAlign parameter for LayoutParameter.
     * @returns {Number}
     */
    getAlign: function () {
        return this._relativeAlign;
    },

    /**
     * Sets a key for LayoutParameter. Witch widget named this is relative to.
     * @param {String} name
     */
    setRelativeToWidgetName: function (name) {
        this._relativeWidgetName = name;
    },

    /**
     * Gets the key of LayoutParameter. Witch widget named this is relative to.
     * @returns {string}
     */
    getRelativeToWidgetName: function () {
        return this._relativeWidgetName;
    },

    /**
     * Sets a name in Relative Layout for LayoutParameter.
     * @param {String} name
     */
    setRelativeName: function (name) {
        this._relativeLayoutName = name;
    },

    /**
     * Gets a name in Relative Layout of LayoutParameter.
     * @returns {string}
     */
    getRelativeName: function () {
        return this._relativeLayoutName;
    },

    _createCloneInstance:function(){
        return new ccui.RelativeLayoutParameter();
    },

    _copyProperties:function(model){
        ccui.LayoutParameter.prototype._copyProperties.call(this, model);
        if (model instanceof ccui.RelativeLayoutParameter) {
            this.setAlign(model._relativeAlign);
            this.setRelativeToWidgetName(model._relativeWidgetName);
            this.setRelativeName(model._relativeLayoutName);
        }
    }
});

/**
 * Allocates and initializes a RelativeLayoutParameter.
 * @function
 * @deprecated since v3.0, please use new ccui.RelativeLayoutParameter() instead.
 * @return {ccui.RelativeLayoutParameter}
 */
ccui.RelativeLayoutParameter.create = function () {
    return new ccui.RelativeLayoutParameter();
};

// Constants
//Relative layout parameter RelativeAlign
/**
 * The none of ccui.RelativeLayoutParameter's relative align.
 * @constant
 * @type {number}
 */
ccui.RelativeLayoutParameter.NONE = 0;
/**
 * The parent's top left of ccui.RelativeLayoutParameter's relative align.
 * @constant
 * @type {number}
 */
ccui.RelativeLayoutParameter.PARENT_TOP_LEFT = 1;
/**
 * The parent's top center horizontal of ccui.RelativeLayoutParameter's relative align.
 * @constant
 * @type {number}
 */
ccui.RelativeLayoutParameter.PARENT_TOP_CENTER_HORIZONTAL = 2;
/**
 * The parent's top right of ccui.RelativeLayoutParameter's relative align.
 * @constant
 * @type {number}
 */
ccui.RelativeLayoutParameter.PARENT_TOP_RIGHT = 3;
/**
 * The parent's left center vertical of ccui.RelativeLayoutParameter's relative align.
 * @constant
 * @type {number}
 */
ccui.RelativeLayoutParameter.PARENT_LEFT_CENTER_VERTICAL = 4;

/**
 * The center in parent of ccui.RelativeLayoutParameter's relative align.
 * @constant
 * @type {number}
 */
ccui.RelativeLayoutParameter.CENTER_IN_PARENT = 5;

/**
 * The parent's right center vertical of ccui.RelativeLayoutParameter's relative align.
 * @constant
 * @type {number}
 */
ccui.RelativeLayoutParameter.PARENT_RIGHT_CENTER_VERTICAL = 6;
/**
 * The parent's left bottom of ccui.RelativeLayoutParameter's relative align.
 * @constant
 * @type {number}
 */
ccui.RelativeLayoutParameter.PARENT_LEFT_BOTTOM = 7;
/**
 * The parent's bottom center horizontal of ccui.RelativeLayoutParameter's relative align.
 * @constant
 * @type {number}
 */
ccui.RelativeLayoutParameter.PARENT_BOTTOM_CENTER_HORIZONTAL = 8;
/**
 * The parent's right bottom of ccui.RelativeLayoutParameter's relative align.
 * @constant
 * @type {number}
 */
ccui.RelativeLayoutParameter.PARENT_RIGHT_BOTTOM = 9;

/**
 * The location above left align of ccui.RelativeLayoutParameter's relative align.
 * @constant
 * @type {number}
 */
ccui.RelativeLayoutParameter.LOCATION_ABOVE_LEFTALIGN = 10;
/**
 * The location above center of ccui.RelativeLayoutParameter's relative align.
 * @constant
 * @type {number}
 */
ccui.RelativeLayoutParameter.LOCATION_ABOVE_CENTER = 11;
/**
 * The location above right align of ccui.RelativeLayoutParameter's relative align.
 * @constant
 * @type {number}
 */
ccui.RelativeLayoutParameter.LOCATION_ABOVE_RIGHTALIGN = 12;
/**
 * The location left of top align of ccui.RelativeLayoutParameter's relative align.
 * @constant
 * @type {number}
 */
ccui.RelativeLayoutParameter.LOCATION_LEFT_OF_TOPALIGN = 13;
/**
 * The location left of center of ccui.RelativeLayoutParameter's relative align.
 * @constant
 * @type {number}
 */
ccui.RelativeLayoutParameter.LOCATION_LEFT_OF_CENTER = 14;
/**
 * The location left of bottom align of ccui.RelativeLayoutParameter's relative align.
 * @constant
 * @type {number}
 */
ccui.RelativeLayoutParameter.LOCATION_LEFT_OF_BOTTOMALIGN = 15;
/**
 * The location right of top align of ccui.RelativeLayoutParameter's relative align.
 * @constant
 * @type {number}
 */
ccui.RelativeLayoutParameter.LOCATION_RIGHT_OF_TOPALIGN = 16;
/**
 * The location right of center of ccui.RelativeLayoutParameter's relative align.
 * @constant
 * @type {number}
 */
ccui.RelativeLayoutParameter.LOCATION_RIGHT_OF_CENTER = 17;
/**
 * The location right of bottom align of ccui.RelativeLayoutParameter's relative align.
 * @constant
 * @type {number}
 */
ccui.RelativeLayoutParameter.LOCATION_RIGHT_OF_BOTTOMALIGN = 18;
/**
 * The location below left align of ccui.RelativeLayoutParameter's relative align.
 * @constant
 * @type {number}
 */
ccui.RelativeLayoutParameter.LOCATION_BELOW_LEFTALIGN = 19;
/**
 * The location below center of ccui.RelativeLayoutParameter's relative align.
 * @constant
 * @type {number}
 */
ccui.RelativeLayoutParameter.LOCATION_BELOW_CENTER = 20;
/**
 * The location below right align of ccui.RelativeLayoutParameter's relative align.
 * @constant
 * @type {number}
 */
ccui.RelativeLayoutParameter.LOCATION_BELOW_RIGHTALIGN = 21;

/**
 * @ignore
 */
ccui.LINEAR_GRAVITY_NONE = 0;
ccui.LINEAR_GRAVITY_LEFT = 1;
ccui.LINEAR_GRAVITY_TOP = 2;
ccui.LINEAR_GRAVITY_RIGHT = 3;
ccui.LINEAR_GRAVITY_BOTTOM = 4;
ccui.LINEAR_GRAVITY_CENTER_VERTICAL = 5;
ccui.LINEAR_GRAVITY_CENTER_HORIZONTAL = 6;

//RelativeAlign
ccui.RELATIVE_ALIGN_NONE = 0;
ccui.RELATIVE_ALIGN_PARENT_TOP_LEFT = 1;
ccui.RELATIVE_ALIGN_PARENT_TOP_CENTER_HORIZONTAL = 2;
ccui.RELATIVE_ALIGN_PARENT_TOP_RIGHT = 3;
ccui.RELATIVE_ALIGN_PARENT_LEFT_CENTER_VERTICAL = 4;
ccui.RELATIVE_ALIGN_PARENT_CENTER = 5;
ccui.RELATIVE_ALIGN_PARENT_RIGHT_CENTER_VERTICAL = 6;
ccui.RELATIVE_ALIGN_PARENT_LEFT_BOTTOM = 7;
ccui.RELATIVE_ALIGN_PARENT_BOTTOM_CENTER_HORIZONTAL = 8;
ccui.RELATIVE_ALIGN_PARENT_RIGHT_BOTTOM = 9;

ccui.RELATIVE_ALIGN_LOCATION_ABOVE_LEFT = 10;
ccui.RELATIVE_ALIGN_LOCATION_ABOVE_CENTER = 11;
ccui.RELATIVE_ALIGN_LOCATION_ABOVE_RIGHT = 12;

ccui.RELATIVE_ALIGN_LOCATION_LEFT_TOP = 13;
ccui.RELATIVE_ALIGN_LOCATION_LEFT_CENTER = 14;
ccui.RELATIVE_ALIGN_LOCATION_LEFT_BOTTOM = 15;

ccui.RELATIVE_ALIGN_LOCATION_RIGHT_TOP = 16;
ccui.RELATIVE_ALIGN_LOCATION_RIGHT_CENTER = 17;
ccui.RELATIVE_ALIGN_LOCATION_RIGHT_BOTTOM = 18;

ccui.RELATIVE_ALIGN_LOCATION_BELOW_TOP = 19;
ccui.RELATIVE_ALIGN_LOCATION_BELOW_CENTER = 20;
ccui.RELATIVE_ALIGN_LOCATION_BELOW_BOTTOM = 21;