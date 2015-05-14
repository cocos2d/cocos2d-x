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
 * the DOM object
 * @namespace
 * @name cc.DOM
 */
cc.DOM = {};

/**
 * @function
 * @private
 * @param node
 */
cc.DOM._addMethods = function (node) {
    for (var funcs in cc.DOM.methods) {
	    node[funcs] = cc.DOM.methods[funcs];
    }

	// Redefine getter setter
	cc.defineGetterSetter(node, "x", node.getPositionX, node.setPositionX);
	cc.defineGetterSetter(node, "y", node.getPositionY, node.setPositionY);
	cc.defineGetterSetter(node, "width", node._getWidth, node._setWidth);
	cc.defineGetterSetter(node, "height", node._getHeight, node._setHeight);
	cc.defineGetterSetter(node, "anchorX", node._getAnchorX, node._setAnchorX);
	cc.defineGetterSetter(node, "anchorY", node._getAnchorY, node._setAnchorY);
	cc.defineGetterSetter(node, "scale", node.getScale, node.setScale);
	cc.defineGetterSetter(node, "scaleX", node.getScaleX, node.setScaleX);
	cc.defineGetterSetter(node, "scaleY", node.getScaleY, node.setScaleY);
	cc.defineGetterSetter(node, "rotation", node.getRotation, node.setRotation);
 	cc.defineGetterSetter(node, "skewX", node.getSkewX, node.setSkewX);
	cc.defineGetterSetter(node, "skewY", node.getSkewY, node.setSkewY);
	cc.defineGetterSetter(node, "visible", node.isVisible, node.setVisible);
	cc.defineGetterSetter(node, "parent", node.getParent, node.setParent);
	cc.defineGetterSetter(node, "opacity", node.getOpacity, node.setOpacity);
};
cc.DOM.methods = /** @lends cc.DOM# */{
    /**
     * Replace the set position of ccNode
     * @param {cc.Point|Number} x
     * @param {Number} y
     */
    setPosition:function (x, y) {
        if (y === undefined) {
	        this._position.x = x.x;
	        this._position.y = x.y;
        } else {
	        this._position.x = x;
	        this._position.y = y;
        }
        this.setNodeDirty();
        this.dom.translates(this._position.x, -this._position.y);
    },
    /**
     * replace set Position Y of ccNode
     * @param {Number} y
     */
    setPositionY:function (y) {
        this._position.y = y;
        this.setNodeDirty();
        this.dom.translates(this._position.x, -this._position.y);
    },

    /**
     * replace set Position X of ccNode
     * @param {Number} x
     */
    setPositionX:function (x) {
        this._position.x = x;
        this.setNodeDirty();
        this.dom.translates(this._position.x, -this._position.y);
    },

    /**
     * replace set Scale of ccNode
     * @param {object|Number} scale
     * @param {Number} scaleY
     */
    setScale:function (scale, scaleY) {
        //save dirty region when before change
        //this._addDirtyRegionToDirector(this.getBoundingBoxToWorld());

        this._scaleX = scale;
        this._scaleY = scaleY || scale;

        //save dirty region when after changed
        //this._addDirtyRegionToDirector(this.getBoundingBoxToWorld());
        this.setNodeDirty();
        this.dom.resize(this._scaleX, this._scaleY);
    },

    /**
     * replace set Scale X of ccNode
     * @param {Number} x
     */
    setScaleX:function (x) {
        this._scaleX = x;
        this.setNodeDirty();
        this.dom.resize(this._scaleX, this._scaleY);
    },

    /**
     * replace set Scale Y of ccNode
     * @param {Number} y
     */
    setScaleY:function (y) {
        this._scaleY = y;
        this.setNodeDirty();
        this.dom.resize(this._scaleX, this._scaleY);
    },

    /**
     * replace set anchorpoint of ccNode
     * @param {cc.Point|Number} point The anchor point of node or The anchor point.x of node.
     * @param {Number} [y] The anchor point.y of node.
     */
    setAnchorPoint:function (point, y) {
        var cmd = this._renderCmd;

        var locAnchorPoint = this._anchorPoint;
        if (y === undefined) {
	        locAnchorPoint.x = point.x;
	        locAnchorPoint.y = point.y;
        } else {
	        locAnchorPoint.x = point;
	        locAnchorPoint.y = y;
        }
        var locAPP = cmd._anchorPointInPoints, locSize = this._contentSize;
        locAPP.x = locSize.width * locAnchorPoint.x;
        locAPP.y = locSize.height * locAnchorPoint.y;

        this.dom.style[cc.$.pfx + 'TransformOrigin'] = '' + locAPP.x + 'px ' + -locAPP.y + 'px';
        if (this.ignoreAnchor) {
            this.dom.style.marginLeft = 0;
            this.dom.style.marginBottom = 0;
        } else {
            this.dom.style.marginLeft = (this.isToggler) ? 0 : -locAPP.x + 'px';
            this.dom.style.marginBottom = -locAPP.y + 'px';
        }
        this.setNodeDirty();
    },

	/**
	 * replace set anchorpoint x of ccNode
	 * @param {Number} x The anchor x of node.
	 */
	_setAnchorX:function (x) {
		var locAnchorPoint = this._anchorPoint;
        var cmd = this._renderCmd;

		if (x === locAnchorPoint.x)
			return;
		locAnchorPoint.x = x;

		var locAPP = cmd._anchorPointInPoints, locSize = this._contentSize;
		locAPP.x = locSize.width * locAnchorPoint.x;

		this.dom.style[cc.$.pfx + 'TransformOrigin'] = '' + locAPP.x + 'px ' + -locAPP.y + 'px';
		if (this.ignoreAnchor) {
			this.dom.style.marginLeft = 0;
			this.dom.style.marginBottom = 0;
		} else {
			this.dom.style.marginLeft = (this.isToggler) ? 0 : -locAPP.x + 'px';
		}
		this.setNodeDirty();
	},

	/**
	 * replace set anchorpoint y of ccNode
	 * @param {Number} y The anchor y of node.
	 */
	_setAnchorY:function (y) {
		var locAnchorPoint = this._anchorPoint;
        var cmd = this._renderCmd;

		if (y === locAnchorPoint.y)
			return;
		locAnchorPoint.y = y;

		var locAPP = cmd._anchorPointInPoints, locSize = this._contentSize;
		locAPP.y = locSize.height * locAnchorPoint.y;

		this.dom.style[cc.$.pfx + 'TransformOrigin'] = '' + locAPP.x + 'px ' + -locAPP.y + 'px';
		if (this.ignoreAnchor) {
			this.dom.style.marginLeft = 0;
			this.dom.style.marginBottom = 0;
		} else {
			this.dom.style.marginBottom = -locAPP.y + 'px';
		}
		this.setNodeDirty();
	},

    /**
     * replace set ContentSize of ccNode
     * @param {cc.Size|Number} size The untransformed size of the node or The untransformed size's width of the node.
     * @param {Number} [height] The untransformed size's height of the node.
     */
    setContentSize:function (size, height) {
        var cmd = this._renderCmd;

        var locContentSize = this._contentSize;
        if (height === undefined) {
	        locContentSize.width = size.width;
	        locContentSize.height = size.height;
        } else {
	        locContentSize.width = size;
	        locContentSize.height = height;
        }
        var locAPP = cmd._anchorPointInPoints, locAnchorPoint = this._anchorPoint;
        locAPP.x = locContentSize.width * locAnchorPoint.x;
        locAPP.y = locContentSize.height * locAnchorPoint.y;
        this.dom.width = locContentSize.width;
        this.dom.height = locContentSize.height;
        this.setAnchorPoint(this.getAnchorPoint());
        if (this.canvas) {
            this.canvas.width = locContentSize.width;
            this.canvas.height = locContentSize.height;
        }
        this.setNodeDirty();
        this.redraw();
    },

	/**
	 * replace set width of ccNode
	 * @param {Number} width The untransformed size's width of the node.
	 */
	_setWidth:function (width) {
		var locContentSize = this._contentSize;
        var cmd = this._renderCmd;
		if (width === locContentSize.width)
			return;
		locContentSize.width = width;

		var locAPP = cmd._anchorPointInPoints, locAnchorPoint = this._anchorPoint;
		locAPP.x = locContentSize.width * locAnchorPoint.x;
		this.dom.width = locContentSize.width;
		this.anchorX = locAnchorPoint.x;
		if (this.canvas) {
			this.canvas.width = locContentSize.width;
		}
		this.setNodeDirty();
		this.redraw();
	},

	/**
	 * replace set height of ccNode
	 * @param {Number} height The untransformed size's height of the node.
	 */
	_setHeight:function (height) {
		var locContentSize = this._contentSize;
        var cmd = this._renderCmd;
		if (height === locContentSize.height)
			return;
		locContentSize.height = height;

		var locAPP = cmd._anchorPointInPoints, locAnchorPoint = this._anchorPoint;
		locAPP.y = locContentSize.height * locAnchorPoint.y;
		this.dom.height = locContentSize.height;
		this.anchorY = locAnchorPoint.y;
		if (this.canvas) {
			this.canvas.height = locContentSize.height;
		}
		this.setNodeDirty();
		this.redraw();
	},

    /**
     * replace set Rotation of ccNode
     * @param {Number} newRotation
     */
    setRotation:function (newRotation) {
        if (this._rotation === newRotation)
            return;

        this._rotationX = this._rotationY = newRotation;
        this.setNodeDirty();
        this.dom.rotate(newRotation);
    },

    /**
     * replace set SkewX of ccNode
     * @param {Number} x
     */
    setSkewX:function (x) {
        this._skewX = x;
        this.setNodeDirty();
        this.dom.setSkew(this._skewX, this._skewY);
    },

    /**
     * replace set SkewY of ccNode
     * @param {Number} y
     */
    setSkewY:function (y) {
        this._skewY = y;
        this.setNodeDirty();
        this.dom.setSkew(this._skewX, this._skewY);
    },

    /**
     * replace set Visible of ccNode
     * @param {Boolean} x
     */
    setVisible:function (x) {
        this._visible = x;
        this.setNodeDirty();
        if (this.dom)
            this.dom.style.display = (x) ? 'block' : 'none';
    },
    _setLocalZOrder:function (z) {
        this._localZOrder = z
        this.setNodeDirty();
        if (this.dom)
            this.dom.zIndex = z;
    },

    /**
     * replace set Parent of ccNode
     * @param {cc.Node} p
     */
    setParent:function (p) {
        this._parent = p;

        if (p !== null) {
            p.setAnchorPoint(p.getAnchorPoint());
            this.setNodeDirty();
            cc.DOM.parentDOM(this);
        }
    },

    /**
     * replace resume Schedule and actions of ccNode
     */
    resume:function () {
        this.getScheduler().resumeTarget(this);
        this.getActionManager().resumeTarget(this);
        cc.eventManager.resumeTarget(this);
        //if dom does not have parent, but node has no parent and its running
        if (this.dom && !this.dom.parentNode) {
            if (!this.getParent()) {
                if(this.dom.id === ""){
                    cc.DOM._createEGLViewDiv(this);
                }else{
                    this.dom.appendTo(cc.container);
                }
            } else {
                cc.DOM.parentDOM(this);
            }
        }
        if (this.dom)
            this.dom.style.visibility = "visible";
    },

    /**
     * replace pause Schedule and Actions of ccNode
     */
    pause:function () {
        this.getScheduler().pauseTarget(this);
        this.getActionManager().pauseTarget(this);
        cc.eventManager.pauseTarget(this);
        if (this.dom) {
            this.dom.style.visibility = 'hidden';
        }
    },

    /**
     * replace clean up of ccNode
     */
    cleanup:function () {
        // actions
        this.stopAllActions();
        this.unscheduleAllCallbacks();

        // timers
        this._arrayMakeObjectsPerformSelector(this._children, cc.Node._stateCallbackType.cleanup);
        if (this.dom) {
            this.dom.remove();
        }
    },
    /**
     * replace remove from parent and clean up of ccNode
     */
    removeFromParentAndCleanup:function () {
        this.dom.remove();
    },
    setOpacity:function (o) {
        this._opacity = o;
        this.dom.style.opacity = o / 255;
    },
    /**
     * refresh/updates the DOM element
     */
    redraw:function () {
        if (this.isSprite) {
            var tmp = this._children;
            this._children = [];
            cc.Sprite.prototype.visit.call(this, this.ctx);
            this._children = tmp;
        }
        else {
            cc.Sprite.prototype.visit.call(this, this.ctx);
        }
    }
};

cc.DOM._resetEGLViewDiv = function(){
    var div = cc.$("#EGLViewDiv");
    if(div){
        var view = cc.view;
        var designSize = view.getDesignResolutionSize();
        var viewPortRect = view.getViewPortRect();
        var screenSize = view.getFrameSize();
	    var pixelRatio = view.getDevicePixelRatio();
        var designSizeWidth = designSize.width, designSizeHeight = designSize.height;
        if((designSize.width === 0) && (designSize.height === 0)){
            designSizeWidth = screenSize.width;
            designSizeHeight = screenSize.height;
        }

        var viewPortWidth = viewPortRect.width/pixelRatio;
        if((viewPortRect.width === 0) && (viewPortRect.height === 0)){
            viewPortWidth = screenSize.width;
        }

        div.style.position = 'absolute';
        //x.dom.style.display='block';
        div.style.width = designSizeWidth + "px";
        div.style.maxHeight = designSizeHeight + "px";
        div.style.margin = 0;

        div.resize(view.getScaleX()/pixelRatio, view.getScaleY()/pixelRatio);
        if (view.getResolutionPolicy() === view._rpNoBorder) {
            div.style.left = (view.getFrameSize().width - designSizeWidth)/2 + "px";
            div.style.bottom = (view.getFrameSize().height - designSizeHeight*view.getScaleY()/pixelRatio)/2 + "px";
        }
        else {
            div.style.left = (designSizeWidth*view.getScaleX()/pixelRatio - designSizeWidth) / 2 + "px";
            div.style.bottom = "0px";
        }
    }
};

/**
 * @function
 * @private
 * @param x
 * @return {Boolean}
 */
cc.DOM.parentDOM = function (x) {
    var p = x.getParent();
    //if has parent, parent need to have dom too
    if (!p || !x.dom)
        return false;
    if (!p.dom) {
        cc.DOM.placeHolder(p);
        p.setParent = cc.DOM.methods.setParent;
    }
    //if parent have dom, attach self to parent
    x.dom.appendTo(p.dom);
    p.setAnchorPoint(p.getAnchorPoint());

    if (p.getParent()) {
        cc.DOM.parentDOM(p);
    } else {
        //parent has no more parent, if its running, then add it to the container
        if (p.isRunning()) {
            //find EGLView div
            var eglViewDiv = cc.$("#EGLViewDiv");
            if (eglViewDiv) {
                p.dom.appendTo(eglViewDiv);
            } else {
                cc.DOM._createEGLViewDiv(p);
            }
        }
    }
    return true;
};

cc.DOM._createEGLViewDiv = function(p){
    var div = cc.$("#EGLViewDiv");
    if(!div){
        div = cc.$new("div");
        div.id = "EGLViewDiv";
    }

    var view = cc.view;
    var designSize = view.getDesignResolutionSize();
    var viewPortRect = view.getViewPortRect();
    var screenSize = view.getFrameSize();
    var pixelRatio = view.getDevicePixelRatio();
    var designSizeWidth = designSize.width, designSizeHeight = designSize.height;
    if ((designSize.width === 0) && (designSize.height === 0)) {
        designSizeWidth = screenSize.width;
        designSizeHeight = screenSize.height;
    }

    var viewPortWidth = viewPortRect.width/pixelRatio;
    if ((viewPortRect.width === 0) && (viewPortRect.height === 0)) {
        viewPortWidth = screenSize.width;
    }

    div.style.position = 'absolute';
    //x.dom.style.display='block';
    div.style.width = designSizeWidth + "px";
    div.style.maxHeight = designSizeHeight + "px";
    div.style.margin = 0;

    div.resize(view.getScaleX()/pixelRatio, view.getScaleY()/pixelRatio);
    if (view.getResolutionPolicy() === view._rpNoBorder) {
        div.style.left = (screenSize.width - designSizeWidth)/2 + "px";
        div.style.bottom = (screenSize.height - designSizeHeight*view.getScaleY()/pixelRatio)/2 + "px";
    }
    else {
        div.style.left = (designSizeWidth*view.getScaleX()/pixelRatio - designSizeWidth) / 2 + "px";
        div.style.bottom = "0px";
    }

    p.dom.appendTo(div);
    div.appendTo(cc.container);
};

/**
 * @function
 * @private
 * @param x
 */
cc.DOM.setTransform = function (x) {
    if (x.ctx) {
        x.ctx.translate(x.getAnchorPointInPoints().x, x.getAnchorPointInPoints().y);
        if (x.isSprite) {
            var tmp = x._children;
            x._children = [];
            cc.Sprite.prototype.visit.call(x);
            x._children = tmp;
        }
        else {
            cc.Sprite.prototype.visit.call(x);
        }
    }
    if (x.dom) {
        x.dom.position.x = x.getPositionX();
        x.dom.position.y = -x.getPositionY();
        x.dom.rotation = x.getRotation();
        x.dom.scale = {x:x.getScaleX(), y:x.getScaleY()};
        x.dom.skew = {x:x.getSkewX(), y:x.getSkewY()};
        if (x.setAnchorPoint)
            x.setAnchorPoint(x.getAnchorPoint());
        x.dom.transforms();
    }

};

/**
 * @function
 * @private
 * @param x
 */
cc.DOM.forSprite = function (x) {
    x.dom = cc.$new('div');
    x.canvas = cc.$new('canvas');
    var locContentSize = x.getContentSize();
    x.canvas.width = locContentSize.width;
    x.canvas.height = locContentSize.height;
    x.dom.style.position = 'absolute';
    x.dom.style.bottom = 0;
    x.ctx = x.canvas.getContext('2d');
    x.dom.appendChild(x.canvas);
    if (x.getParent()) {
        cc.DOM.parentDOM(x);
    }
    x.isSprite = true;
};

/**
 * This creates divs for parent Nodes that are related to the current node
 * @function
 * @private
 * @param x
 */
cc.DOM.placeHolder = function (x) {
    //creating a placeholder dom to simulate other ccNode in the hierachy
    x.dom = cc.$new('div');
    x.placeholder = true;
    x.dom.style.position = 'absolute';
    x.dom.style.bottom = 0;
    //x.dom.style.display='block';
    x.dom.style.width = (x.getContentSize().width || cc.director.getWinSize().width) + "px";
    x.dom.style.maxHeight = (x.getContentSize().height || cc.director.getWinSize().height) + "px";
    x.dom.style.margin = 0;
    cc.DOM.setTransform(x);
    x.dom.transforms();
    cc.DOM._addMethods(x);
    //x.dom.style.border = 'red 1px dotted';
};

/**
 * Converts cc.Sprite or cc.MenuItem to DOM elements <br/>
 * It currently only supports cc.Sprite and cc.MenuItem
 * @function
 * @param {cc.Sprite|cc.MenuItem|Array} nodeObject
 * @example
 * // example
 * cc.DOM.convert(Sprite1, Sprite2, Menuitem);
 *
 * var myDOMElements = [Sprite1, Sprite2, MenuItem];
 * cc.DOM.convert(myDOMElements);
 */
cc.DOM.convert = function (nodeObject) {
    //if passing by list, make it an array
    if (arguments.length > 1) {
        cc.DOM.convert(arguments);
        return;
    } else if (arguments.length === 1 && !arguments[0].length) {
        cc.DOM.convert([arguments[0]]);
        return;
    }
    var args = arguments[0];
    for (var i = 0; i < args.length; i++) {
        //first check if its sprite
        if (args[i] instanceof cc.Sprite) {
            // create a canvas
            if (!args[i].dom)
                cc.DOM.forSprite(args[i]);
        } else {
            cc.log('DOM converter only supports sprite and menuitems yet');
        }
        cc.DOM._addMethods(args[i]);
        args[i].visit = function () {
        };
        args[i].transform = function () {
        };
        cc.DOM.setTransform(args[i]);
        args[i].setVisible(args[i].isVisible());
    }
};
