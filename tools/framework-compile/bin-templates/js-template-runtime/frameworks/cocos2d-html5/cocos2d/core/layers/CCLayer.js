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

/** cc.Layer is a subclass of cc.Node that implements the TouchEventsDelegate protocol.<br/>
 * All features from cc.Node are valid, plus the bake feature: Baked layer can cache a static layer to improve performance
 * @class
 * @extends cc.Node
 */
cc.Layer = cc.Node.extend(/** @lends cc.Layer# */{
    _className: "Layer",

    /**
     * <p>Constructor of cc.Layer, override it to extend the construction behavior, remember to call "this._super()" in the extended "ctor" function.</p>
     */
    ctor: function () {
        var nodep = cc.Node.prototype;
        nodep.ctor.call(this);
        this._ignoreAnchorPointForPosition = true;
        nodep.setAnchorPoint.call(this, 0.5, 0.5);
        nodep.setContentSize.call(this, cc.winSize);
    },

    /**
     * Initialization of the layer, please do not call this function by yourself, you should pass the parameters to constructor to initialize a layer
     */
    init: function(){
        var _t = this;
        _t._ignoreAnchorPointForPosition = true;
        _t.setAnchorPoint(0.5, 0.5);
        _t.setContentSize(cc.winSize);
        _t._cascadeColorEnabled = false;
        _t._cascadeOpacityEnabled = false;
        return true;
    },

    /**
     * Sets the layer to cache all of children to a bake sprite, and draw itself by bake sprite. recommend using it in UI.<br/>
     * This is useful only in html5 engine
     * @function
     * @see cc.Layer#unbake
     */
    bake: function(){
        this._renderCmd.bake();
    },

    /**
     * Cancel the layer to cache all of children to a bake sprite.<br/>
     * This is useful only in html5 engine
     * @function
     * @see cc.Layer#bake
     */
    unbake: function(){
        this._renderCmd.unbake();
    },

    /**
     * Determines if the layer is baked.
     * @function
     * @returns {boolean}
     * @see cc.Layer#bake and cc.Layer#unbake
     */
    isBaked: function(){
        return this._isBaked;
    },

    addChild: function(child, localZOrder, tag){
        cc.Node.prototype.addChild.call(this, child, localZOrder, tag);
        this._renderCmd._bakeForAddChild(child);
    },

    _createRenderCmd: function(){
        if (cc._renderType === cc._RENDER_TYPE_CANVAS)
            return new cc.Layer.CanvasRenderCmd(this);
        else
            return new cc.Layer.WebGLRenderCmd(this);
    }
});

/**
 * Creates a layer
 * @deprecated since v3.0, please use the new construction instead
 * @see cc.Layer
 * @return {cc.Layer|Null}
 */
cc.Layer.create = function () {
    return new cc.Layer();
};

/**
 * <p>
 * CCLayerColor is a subclass of CCLayer that implements the CCRGBAProtocol protocol.       <br/>
 *  All features from CCLayer are valid, plus the following new features:                   <br/>
 * - opacity                                                                     <br/>
 * - RGB colors                                                                  </p>
 * @class
 * @extends cc.Layer
 *
 * @param {cc.Color} [color=] The color of the layer
 * @param {Number} [width=] The width of the layer
 * @param {Number} [height=] The height of the layer
 *
 * @example
 * // Example
 * //Create a yellow color layer as background
 * var yellowBackground = new cc.LayerColor(cc.color(255,255,0,255));
 * //If you didn't pass in width and height, it defaults to the same size as the canvas
 *
 * //create a yellow box, 200 by 200 in size
 * var yellowBox = new cc.LayerColor(cc.color(255,255,0,255), 200, 200);
 */
cc.LayerColor = cc.Layer.extend(/** @lends cc.LayerColor# */{
    _blendFunc: null,
    _className: "LayerColor",

    /**
     * Returns the blend function
     * @return {cc.BlendFunc}
     */
    getBlendFunc: function () {
        return this._blendFunc;
    },

    /**
     * Changes width and height
     * @deprecated since v3.0 please use setContentSize instead
     * @see cc.Node#setContentSize
     * @param {Number} w width
     * @param {Number} h height
     */
    changeWidthAndHeight: function (w, h) {
        this.width = w;
        this.height = h;
    },

    /**
     * Changes width in Points
     * @deprecated since v3.0 please use setContentSize instead
     * @see cc.Node#setContentSize
     * @param {Number} w width
     */
    changeWidth: function (w) {
        this.width = w;
    },

    /**
     * change height in Points
     * @deprecated since v3.0 please use setContentSize instead
     * @see cc.Node#setContentSize
     * @param {Number} h height
     */
    changeHeight: function (h) {
        this.height = h;
    },

    setOpacityModifyRGB: function (value) {
    },

    isOpacityModifyRGB: function () {
        return false;
    },

    /**
     * Constructor of cc.LayerColor
     * @function
     * @param {cc.Color} [color=]
     * @param {Number} [width=]
     * @param {Number} [height=]
     */
    ctor: function(color, width, height){
        cc.Layer.prototype.ctor.call(this);
        this._blendFunc = new cc.BlendFunc(cc.BLEND_SRC, cc.BLEND_DST);
        cc.LayerColor.prototype.init.call(this, color, width, height);
    },

    /**
     * Initialization of the layer, please do not call this function by yourself, you should pass the parameters to constructor to initialize a layer
     * @param {cc.Color} [color=]
     * @param {Number} [width=]
     * @param {Number} [height=]
     * @return {Boolean}
     */
    init: function (color, width, height) {
        if (cc._renderType !== cc._RENDER_TYPE_CANVAS)
            this.shaderProgram = cc.shaderCache.programForKey(cc.SHADER_POSITION_COLOR);

        var winSize = cc.director.getWinSize();
        color = color || cc.color(0, 0, 0, 255);
        width = width === undefined ? winSize.width : width;
        height = height === undefined ? winSize.height : height;

        var locRealColor = this._realColor;
        locRealColor.r = color.r;
        locRealColor.g = color.g;
        locRealColor.b = color.b;
        this._realOpacity = color.a;
        this._renderCmd.setDirtyFlag(cc.Node._dirtyFlags.colorDirty|cc.Node._dirtyFlags.opacityDirty);

        cc.LayerColor.prototype.setContentSize.call(this, width, height);
        return true;
    },

    /**
     * Sets the blend func, you can pass either a cc.BlendFunc object or source and destination value separately
     * @param {Number|cc.BlendFunc} src
     * @param {Number} [dst]
     */
    setBlendFunc: function (src, dst) {
        var locBlendFunc = this._blendFunc;
        if (dst === undefined) {
            locBlendFunc.src = src.src;
            locBlendFunc.dst = src.dst;
        } else {
            locBlendFunc.src = src;
            locBlendFunc.dst = dst;
        }
        this._renderCmd.updateBlendFunc(locBlendFunc);
    },

    _setWidth: function(width){
        cc.Node.prototype._setWidth.call(this, width);
        this._renderCmd._updateSquareVerticesWidth(width);
    },

    _setHeight: function(height){
        cc.Node.prototype._setHeight.call(this, height);
        this._renderCmd._updateSquareVerticesHeight(height);
    },

    setContentSize: function(size, height){
        cc.Layer.prototype.setContentSize.call(this, size, height);
        this._renderCmd._updateSquareVertices(size, height);
    },

    _createRenderCmd: function(){
        if (cc._renderType === cc._RENDER_TYPE_CANVAS)
            return new cc.LayerColor.CanvasRenderCmd(this);
        else
            return new cc.LayerColor.WebGLRenderCmd(this);
    }
});

/**
 * Creates a cc.Layer with color, width and height in Points
 * @deprecated since v3.0 please use the new construction instead
 * @see cc.LayerColor
 * @param {cc.Color} color
 * @param {Number|Null} [width=]
 * @param {Number|Null} [height=]
 * @return {cc.LayerColor}
 */
cc.LayerColor.create = function (color, width, height) {
    return new cc.LayerColor(color, width, height);
};

//LayerColor - Getter Setter
(function(){
    var proto = cc.LayerColor.prototype;
    cc.defineGetterSetter(proto, "width", proto._getWidth, proto._setWidth);
    cc.defineGetterSetter(proto, "height", proto._getHeight, proto._setHeight);
})();

/**
 * <p>
 * CCLayerGradient is a subclass of cc.LayerColor that draws gradients across the background.<br/>
 *<br/>
 * All features from cc.LayerColor are valid, plus the following new features:<br/>
 * <ul><li>direction</li>
 * <li>final color</li>
 * <li>interpolation mode</li></ul>
 * <br/>
 * Color is interpolated between the startColor and endColor along the given<br/>
 * vector (starting at the origin, ending at the terminus).  If no vector is<br/>
 * supplied, it defaults to (0, -1) -- a fade from top to bottom.<br/>
 * <br/>
 * If 'compressedInterpolation' is disabled, you will not see either the start or end color for<br/>
 * non-cardinal vectors; a smooth gradient implying both end points will be still<br/>
 * be drawn, however.<br/>
 *<br/>
 * If 'compressedInterpolation' is enabled (default mode) you will see both the start and end colors of the gradient.
 * </p>
 * @class
 * @extends cc.LayerColor
 *
 * @param {cc.Color} start Starting color
 * @param {cc.Color} end Ending color
 * @param {cc.Point} [v=cc.p(0, -1)] A vector defines the gradient direction, default direction is from top to bottom
 *
 * @property {cc.Color} startColor              - Start color of the color gradient
 * @property {cc.Color} endColor                - End color of the color gradient
 * @property {Number}   startOpacity            - Start opacity of the color gradient
 * @property {Number}   endOpacity              - End opacity of the color gradient
 * @property {Number}   vector                  - Direction vector of the color gradient
 * @property {Number}   compressedInterpolation  - Indicate whether or not the interpolation will be compressed
 */
cc.LayerGradient = cc.LayerColor.extend(/** @lends cc.LayerGradient# */{
    _endColor: null,
    _startOpacity: 255,
    _endOpacity: 255,
    _alongVector: null,
    _compressedInterpolation: false,
    _className: "LayerGradient",
    _colorStops: [],

    /**
     * Constructor of cc.LayerGradient
     * @param {cc.Color} start
     * @param {cc.Color} end
     * @param {cc.Point} [v=cc.p(0, -1)]
     * @param {Array|Null} stops
     *
     * @example Using ColorStops argument:
     * //startColor & endColor are for default and backward compatibility
     * var layerGradient = new cc.LayerGradient(cc.color.RED, new cc.Color(255,0,0,0), cc.p(0, -1),
     *                                          [{p:0, color: cc.color.RED},
     *                                           {p:.5, color: new cc.Color(0,0,0,0)},
     *                                           {p:1, color: cc.color.RED}]);
     * //where p = A value between 0.0 and 1.0 that represents the position between start and end in a gradient
     *
     */
    ctor: function (start, end, v, stops) {
        cc.LayerColor.prototype.ctor.call(this);
        this._endColor = cc.color(0, 0, 0, 255);
        this._alongVector = cc.p(0, -1);
        this._startOpacity = 255;
        this._endOpacity = 255;

        if(stops && stops instanceof Array){
            this._colorStops = stops;
            stops.splice(0, 0, {p:0, color: start || cc.color.BLACK});
            stops.push({p:1, color: end || cc.color.BLACK});
        } else
            this._colorStops = [{p:0, color: start || cc.color.BLACK}, {p:1, color: end || cc.color.BLACK}];

        cc.LayerGradient.prototype.init.call(this, start, end, v, stops);
    },

    /**
     * Initialization of the layer, please do not call this function by yourself, you should pass the parameters to constructor to initialize a layer
     * @param {cc.Color} start starting color
     * @param {cc.Color} end
     * @param {cc.Point|Null} v
     * @param {Array|Null} stops
     * @return {Boolean}
     */
    init: function (start, end, v, stops) {
        start = start || cc.color(0, 0, 0, 255);
        end = end || cc.color(0, 0, 0, 255);
        v = v || cc.p(0, -1);
        var _t = this;

        // Initializes the CCLayer with a gradient between start and end in the direction of v.
        var locEndColor = _t._endColor;
        _t._startOpacity = start.a;

        locEndColor.r = end.r;
        locEndColor.g = end.g;
        locEndColor.b = end.b;
        _t._endOpacity = end.a;

        _t._alongVector = v;
        _t._compressedInterpolation = true;

        cc.LayerColor.prototype.init.call(_t, cc.color(start.r, start.g, start.b, 255));
        this._renderCmd.setDirtyFlag(cc.Node._dirtyFlags.colorDirty|cc.Node._dirtyFlags.opacityDirty|cc.Node._dirtyFlags.gradientDirty);
        return true;
    },

    /**
     * Sets the untransformed size of the LayerGradient.
     * @param {cc.Size|Number} size The untransformed size of the LayerGradient or The untransformed size's width of the LayerGradient.
     * @param {Number} [height] The untransformed size's height of the LayerGradient.
     */
    setContentSize: function (size, height) {
        cc.LayerColor.prototype.setContentSize.call(this, size, height);
        this._renderCmd.setDirtyFlag(cc.Node._dirtyFlags.gradientDirty);
    },

    _setWidth: function (width) {
        cc.LayerColor.prototype._setWidth.call(this, width);
        this._renderCmd.setDirtyFlag(cc.Node._dirtyFlags.gradientDirty);
    },
    _setHeight: function (height) {
        cc.LayerColor.prototype._setHeight.call(this, height);
        this._renderCmd.setDirtyFlag(cc.Node._dirtyFlags.gradientDirty);
    },

    /**
     * Returns the starting color
     * @return {cc.Color}
     */
    getStartColor: function () {
        return cc.color(this._realColor);
    },

    /**
     * Sets the starting color
     * @param {cc.Color} color
     * @example
     * // Example
     * myGradientLayer.setStartColor(cc.color(255,0,0));
     * //set the starting gradient to red
     */
    setStartColor: function (color) {
        this.color = color;
        //update the color stops
        var stops = this._colorStops;
        if(stops && stops.length > 0){
            var selColor = stops[0].color;
            selColor.r = color.r;
            selColor.g = color.g;
            selColor.b = color.b;
        }
    },

    /**
     * Sets the end gradient color
     * @param {cc.Color} color
     * @example
     * // Example
     * myGradientLayer.setEndColor(cc.color(255,0,0));
     * //set the ending gradient to red
     */
    setEndColor: function (color) {
        var locColor = this._endColor;
        locColor.r = color.r;
        locColor.g = color.g;
        locColor.b = color.b;
        //update the color stops
        var stops = this._colorStops;
        if(stops && stops.length > 0){
            var selColor = stops[stops.length -1].color;
            selColor.r = color.r;
            selColor.g = color.g;
            selColor.b = color.b;
        }
        this._renderCmd.setDirtyFlag(cc.Node._dirtyFlags.colorDirty);
    },

    /**
     * Returns the end color
     * @return {cc.Color}
     */
    getEndColor: function () {
        return cc.color(this._endColor);
    },

    /**
     * Sets starting gradient opacity
     * @param {Number} o from 0 to 255, 0 is transparent
     */
    setStartOpacity: function (o) {
        this._startOpacity = o;
        //update the color stops
        var stops = this._colorStops;
        if(stops && stops.length > 0)
            stops[0].color.a = o;
        this._renderCmd.setDirtyFlag(cc.Node._dirtyFlags.opacityDirty);
    },

    /**
     * Returns the starting gradient opacity
     * @return {Number}
     */
    getStartOpacity: function () {
        return this._startOpacity;
    },

    /**
     * Sets the end gradient opacity
     * @param {Number} o
     */
    setEndOpacity: function (o) {
        this._endOpacity = o;
        var stops = this._colorStops;
        if(stops && stops.length > 0)
            stops[stops.length -1].color.a = o;
        this._renderCmd.setDirtyFlag(cc.Node._dirtyFlags.opacityDirty);
    },

    /**
     * Returns the end gradient opacity
     * @return {Number}
     */
    getEndOpacity: function () {
        return this._endOpacity;
    },

    /**
     * Sets the direction vector of the gradient
     * @param {cc.Point} Var
     */
    setVector: function (Var) {
        this._alongVector.x = Var.x;
        this._alongVector.y = Var.y;
        this._renderCmd.setDirtyFlag(cc.Node._dirtyFlags.gradientDirty);
    },

    /**
     * Returns the direction vector of the gradient
     * @return {cc.Point}
     */
    getVector: function () {
        return cc.p(this._alongVector.x, this._alongVector.y);
    },

    /**
     * Returns whether compressed interpolation is enabled
     * @return {Boolean}
     */
    isCompressedInterpolation: function () {
        return this._compressedInterpolation;
    },

    /**
     * Sets whether compressed interpolation is enabled
     * @param {Boolean} compress
     */
    setCompressedInterpolation: function (compress) {
        this._compressedInterpolation = compress;
        this._renderCmd.setDirtyFlag(cc.Node._dirtyFlags.gradientDirty);
    },

    /**
     * Return an array of Object representing a colorStop for the gradient, if no stops was specified
     * start & endColor will be provided as default values
     * @example
     * [{p: 0, color: cc.color.RED},{p: 1, color: cc.color.RED},...]
     * @returns {Array}
     */
    getColorStops: function(){
        return this._colorStops;
    },
    /**
     * Set the colorStops to create the gradient using multiple point & color
     *
     * @param colorStops
     *
     * @example
     * //startColor & endColor are for default and backward compatibility
     * var layerGradient = new cc.LayerGradient(cc.color.RED, new cc.Color(255,0,0,0), cc.p(0, -1));
     * layerGradient.setColorStops([{p:0, color: cc.color.RED},
     *                              {p:.5, color: new cc.Color(0,0,0,0)},
     *                              {p:1, color: cc.color.RED}]);
     * //where p = A value between 0.0 and 1.0 that represents the position between start and end in a gradient
     *
     */
    setColorStops: function(colorStops){
        this._colorStops = colorStops;
        //todo need update  the start color and end color
        this._renderCmd.setDirtyFlag(cc.Node._dirtyFlags.colorDirty|cc.Node._dirtyFlags.opacityDirty|cc.Node._dirtyFlags.gradientDirty);
    },

    _createRenderCmd: function(){
        if (cc._renderType === cc._RENDER_TYPE_CANVAS)
            return new cc.LayerGradient.CanvasRenderCmd(this);
        else
            return new cc.LayerGradient.WebGLRenderCmd(this);
    }
});

/**
 * Creates a gradient layer
 * @deprecated since v3.0, please use the new construction instead
 * @see cc.layerGradient
 * @param {cc.Color} start starting color
 * @param {cc.Color} end ending color
 * @param {cc.Point|Null} v
 * @param {Array|NULL} stops
 * @return {cc.LayerGradient}
 */
cc.LayerGradient.create = function (start, end, v, stops) {
    return new cc.LayerGradient(start, end, v, stops);
};
//LayerGradient - Getter Setter
(function(){
    var proto = cc.LayerGradient.prototype;
    // Extended properties
    /** @expose */
    proto.startColor;
    cc.defineGetterSetter(proto, "startColor", proto.getStartColor, proto.setStartColor);
    /** @expose */
    proto.endColor;
    cc.defineGetterSetter(proto, "endColor", proto.getEndColor, proto.setEndColor);
    /** @expose */
    proto.startOpacity;
    cc.defineGetterSetter(proto, "startOpacity", proto.getStartOpacity, proto.setStartOpacity);
    /** @expose */
    proto.endOpacity;
    cc.defineGetterSetter(proto, "endOpacity", proto.getEndOpacity, proto.setEndOpacity);
    /** @expose */
    proto.vector;
    cc.defineGetterSetter(proto, "vector", proto.getVector, proto.setVector);
    /** @expose */
    proto.colorStops;
    cc.defineGetterSetter(proto, "colorStops", proto.getColorStops, proto.setColorStops);
})();

/**
 * CCMultipleLayer is a CCLayer with the ability to multiplex it's children.<br/>
 * Features:<br/>
 *  <ul><li>- It supports one or more children</li>
 *  <li>- Only one children will be active a time</li></ul>
 * @class
 * @extends cc.Layer
 * @param {Array} layers an array of cc.Layer
 * @example
 * // Example
 * var multiLayer = new cc.LayerMultiple(layer1, layer2, layer3);//any number of layers
 */
cc.LayerMultiplex = cc.Layer.extend(/** @lends cc.LayerMultiplex# */{
    _enabledLayer: 0,
    _layers: null,
    _className: "LayerMultiplex",

    /**
     * Constructor of cc.LayerMultiplex
     * @param {Array} layers an array of cc.Layer
     */
    ctor: function (layers) {
        cc.Layer.prototype.ctor.call(this);
        if (layers instanceof Array)
            cc.LayerMultiplex.prototype.initWithLayers.call(this, layers);
        else
            cc.LayerMultiplex.prototype.initWithLayers.call(this, Array.prototype.slice.call(arguments));
    },

    /**
     * Initialization of the layer multiplex, please do not call this function by yourself, you should pass the parameters to constructor to initialize a layer multiplex
     * @param {Array} layers an array of cc.Layer
     * @return {Boolean}
     */
    initWithLayers: function (layers) {
        if ((layers.length > 0) && (layers[layers.length - 1] == null))
            cc.log(cc._LogInfos.LayerMultiplex_initWithLayers);

        this._layers = layers;
        this._enabledLayer = 0;
        this.addChild(this._layers[this._enabledLayer]);
        return true;
    },

    /**
     * Switches to a certain layer indexed by n.<br/>
     * The current (old) layer will be removed from it's parent with 'cleanup:YES'.
     * @param {Number} n the layer index to switch to
     */
    switchTo: function (n) {
        if (n >= this._layers.length) {
            cc.log(cc._LogInfos.LayerMultiplex_switchTo);
            return;
        }

        this.removeChild(this._layers[this._enabledLayer], true);
        this._enabledLayer = n;
        this.addChild(this._layers[n]);
    },

    /**
     * Release the current layer and switches to another layer indexed by n.<br/>
     * The current (old) layer will be removed from it's parent with 'cleanup:YES'.
     * @param {Number} n the layer index to switch to
     */
    switchToAndReleaseMe: function (n) {
        if (n >= this._layers.length) {
            cc.log(cc._LogInfos.LayerMultiplex_switchToAndReleaseMe);
            return;
        }

        this.removeChild(this._layers[this._enabledLayer], true);

        //[layers replaceObjectAtIndex:_enabledLayer withObject:[NSNull null]];
        this._layers[this._enabledLayer] = null;
        this._enabledLayer = n;
        this.addChild(this._layers[n]);
    },

    /**
     * Add a layer to the multiplex layers list
     * @param {cc.Layer} layer
     */
    addLayer: function (layer) {
        if (!layer) {
            cc.log(cc._LogInfos.LayerMultiplex_addLayer);
            return;
        }
        this._layers.push(layer);
    }
});

/**
 * Creates a cc.LayerMultiplex with one or more layers using a variable argument list.
 * @deprecated since v3.0, please use new construction instead
 * @see cc.LayerMultiplex
 * @return {cc.LayerMultiplex|Null}
 */
cc.LayerMultiplex.create = function (/*Multiple Arguments*/) {
    return new cc.LayerMultiplex(Array.prototype.slice.call(arguments));
};