/****************************************************************************
 Copyright (c) 2008-2010 Ricardo Quesada
 Copyright (c) 2011-2012 cocos2d-x.org
 Copyright (c) 2013-2014 Chukong Technologies Inc.
 Copyright (c) 2012 Neofect. All rights reserved.

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

 Created by Jung Sang-Taik on 2012-03-16
 ****************************************************************************/

/**
 * A 9-slice sprite for cocos2d.
 *
 * 9-slice scaling allows you to specify how scaling is applied
 * to specific areas of a sprite. With 9-slice scaling (3x3 grid),
 * you can ensure that the sprite does not become distorted when
 * scaled.
 *
 * @see http://yannickloriot.com/library/ios/cccontrolextension/Classes/CCScale9Sprite.html
 * @class
 * @extends cc.Node
 *
 * @property {cc.Size}  preferredSize   - The preferred size of the 9-slice sprite
 * @property {cc.Rect}  capInsets       - The cap insets of the 9-slice sprite
 * @property {Number}   insetLeft       - The left inset of the 9-slice sprite
 * @property {Number}   insetTop        - The top inset of the 9-slice sprite
 * @property {Number}   insetRight      - The right inset of the 9-slice sprite
 * @property {Number}   insetBottom     - The bottom inset of the 9-slice sprite
 */
cc.Scale9Sprite = cc.Node.extend(/** @lends cc.Scale9Sprite# */{
    _spriteRect: null,
    _capInsetsInternal: null,
    _positionsAreDirty: false,

    _scale9Image: null,
    _topLeft: null,
    _top: null,
    _topRight: null,
    _left: null,
    _centre: null,
    _right: null,
    _bottomLeft: null,
    _bottom: null,
    _bottomRight: null,

    _scale9Dirty: true,

    _opacityModifyRGB: false,

    _originalSize: null,
    _preferredSize: null,
    _opacity: 0,
    _color: null,
    _capInsets: null,
    _insetLeft: 0,
    _insetTop: 0,
    _insetRight: 0,
    _insetBottom: 0,

    _spritesGenerated: false,
    _spriteFrameRotated: false,
    _textureLoaded:false,
    _className:"Scale9Sprite",

    //v3.3
    _flippedX: false,
    _flippedY: false,

    /**
     * return  texture is loaded
     * @returns {boolean}
     */
    textureLoaded:function(){
        return this._textureLoaded;
    },

    /**
     * add texture loaded event listener
     * @param {Function} callback
     * @param {Object} target
     * @deprecated since 3.1, please use addEventListener instead
     */
    addLoadedEventListener:function(callback, target){
        this.addEventListener("load", callback, target);
    },

    _updateCapInset: function () {
        var insets, locInsetLeft = this._insetLeft, locInsetTop = this._insetTop, locInsetRight = this._insetRight;
        var locSpriteRect = this._spriteRect, locInsetBottom = this._insetBottom;
        if (locInsetLeft === 0 && locInsetTop === 0 && locInsetRight === 0 && locInsetBottom === 0) {
            insets = cc.rect(0, 0, 0, 0);
        } else {
            insets = this._spriteFrameRotated ? cc.rect(locInsetBottom, locInsetLeft,
                    locSpriteRect.width - locInsetRight - locInsetLeft,
                    locSpriteRect.height - locInsetTop - locInsetBottom) :
                cc.rect(locInsetLeft, locInsetTop,
                        locSpriteRect.width - locInsetLeft - locInsetRight,
                        locSpriteRect.height - locInsetTop - locInsetBottom);
        }
        this.setCapInsets(insets);
    },

    _updatePositions: function () {
        // Check that instances are non-NULL
        if (!((this._topLeft) && (this._topRight) && (this._bottomRight) &&
            (this._bottomLeft) && (this._centre))) {
            // if any of the above sprites are NULL, return
            return;
        }

        var size = this._contentSize;
        var locTopLeft = this._topLeft, locTopRight = this._topRight, locBottomRight = this._bottomRight, locBottomLeft = this._bottomLeft;
        var locCenter = this._centre, locCenterContentSize = this._centre.getContentSize();
        var locTopLeftContentSize = locTopLeft.getContentSize();
        var locBottomLeftContentSize = locBottomLeft.getContentSize();

        var sizableWidth = size.width - locTopLeftContentSize.width - locTopRight.getContentSize().width;
        var sizableHeight = size.height - locTopLeftContentSize.height - locBottomRight.getContentSize().height;

        var horizontalScale = sizableWidth / locCenterContentSize.width;
        var verticalScale = sizableHeight / locCenterContentSize.height;

        var rescaledWidth = locCenterContentSize.width * horizontalScale;
        var rescaledHeight = locCenterContentSize.height * verticalScale;

        var leftWidth = locBottomLeftContentSize.width;
        var bottomHeight = locBottomLeftContentSize.height;

        if (cc._renderType === cc._RENDER_TYPE_WEBGL) {
            //browser is in canvas mode, need to manually control rounding to prevent overlapping pixels
            var roundedRescaledWidth = Math.round(rescaledWidth);
            if (rescaledWidth !== roundedRescaledWidth) {
                rescaledWidth = roundedRescaledWidth;
                horizontalScale = rescaledWidth / locCenterContentSize.width;
            }
            var roundedRescaledHeight = Math.round(rescaledHeight);
            if (rescaledHeight !== roundedRescaledHeight) {
                rescaledHeight = roundedRescaledHeight;
                verticalScale = rescaledHeight / locCenterContentSize.height;
            }
        }

        locCenter.setScaleX(horizontalScale);
        locCenter.setScaleY(verticalScale);

        var locLeft = this._left, locRight = this._right, locTop = this._top, locBottom = this._bottom;
        var tempAP = cc.p(0, 0);
        locBottomLeft.setAnchorPoint(tempAP);
        locBottomRight.setAnchorPoint(tempAP);
        locTopLeft.setAnchorPoint(tempAP);
        locTopRight.setAnchorPoint(tempAP);
        locLeft.setAnchorPoint(tempAP);
        locRight.setAnchorPoint(tempAP);
        locTop.setAnchorPoint(tempAP);
        locBottom.setAnchorPoint(tempAP);
        locCenter.setAnchorPoint(tempAP);

        // Position corners
        locBottomLeft.setPosition(0, 0);
        locBottomRight.setPosition(leftWidth + rescaledWidth, 0);
        locTopLeft.setPosition(0, bottomHeight + rescaledHeight);
        locTopRight.setPosition(leftWidth + rescaledWidth, bottomHeight + rescaledHeight);

        // Scale and position borders
        locLeft.setPosition(0, bottomHeight);
        locLeft.setScaleY(verticalScale);
        locRight.setPosition(leftWidth + rescaledWidth, bottomHeight);
        locRight.setScaleY(verticalScale);
        locBottom.setPosition(leftWidth, 0);
        locBottom.setScaleX(horizontalScale);
        locTop.setPosition(leftWidth, bottomHeight + rescaledHeight);
        locTop.setScaleX(horizontalScale);

        // Position centre
        locCenter.setPosition(leftWidth, bottomHeight);
    },

    /**
     * Constructor function. override it to extend the construction behavior, remember to call "this._super()" in the extended "ctor" function.
     * @function
     * @param {string|cc.SpriteFrame} file file name of texture or a SpriteFrame
     * @param {cc.Rect} rect
     * @param {cc.Rect} capInsets
     * @returns {Scale9Sprite}
     */
    ctor: function (file, rect, capInsets) {
        cc.Node.prototype.ctor.call(this);
        this._spriteRect = cc.rect(0, 0, 0, 0);
        this._capInsetsInternal = cc.rect(0, 0, 0, 0);

        this._originalSize = cc.size(0, 0);
        this._preferredSize = cc.size(0, 0);
        this._capInsets = cc.rect(0, 0, 0, 0);

        if(file != undefined){
            if(file instanceof cc.SpriteFrame)
                this.initWithSpriteFrame(file, rect);
            else{
                var frame = cc.spriteFrameCache.getSpriteFrame(file);
                if(frame != null)
                    this.initWithSpriteFrame(frame, rect);
                else
                    this.initWithFile(file, rect, capInsets);
            }
        }else{
            this.init();
        }
    },

    getSprite: function () {
        return this._scale9Image;
    },

    /** Original sprite's size. */
    getOriginalSize: function () {
        return cc.size(this._originalSize);
    },

    //if the preferredSize component is given as -1, it is ignored
    getPreferredSize: function () {
        return cc.size(this._preferredSize);
    },
    _getPreferredWidth: function () {
        return this._preferredSize.width;
    },
    _getPreferredHeight: function () {
        return this._preferredSize.height;
    },
    setPreferredSize: function (preferredSize) {
        this.setContentSize(preferredSize);
        this._preferredSize = preferredSize;

        if (this._positionsAreDirty) {
            this._updatePositions();
            this._positionsAreDirty = false;
            this._scale9Dirty = true;
        }
    },
    _setPreferredWidth: function (value) {
        this._setWidth(value);
        this._preferredSize.width = value;
    },
    _setPreferredHeight: function (value) {
        this._setHeight(value);
        this._preferredSize.height = value;
    },

    /** Opacity: conforms to CCRGBAProtocol protocol */
    setOpacity: function (opacity) {
        if(!this._scale9Image)
            return;
        cc.Node.prototype.setOpacity.call(this, opacity);
        var scaleChildren = this._scale9Image.getChildren();
        for (var i = 0; i < scaleChildren.length; i++) {
            var selChild = scaleChildren[i];
            if (selChild)
                selChild.setOpacity(opacity);
        }
        this._scale9Dirty = true;
    },

    /** Color: conforms to CCRGBAProtocol protocol */
    setColor: function (color) {
        if(!this._scale9Image)
            return;

        cc.Node.prototype.setColor.call(this, color);
        var scaleChildren = this._scale9Image.getChildren();
        for (var i = 0; i < scaleChildren.length; i++) {
            var selChild = scaleChildren[i];
            if (selChild)
                selChild.setColor(color);
        }
        this._scale9Dirty = true;
    },

    getCapInsets: function () {
        return cc.rect(this._capInsets);
    },

    setCapInsets: function (capInsets) {
        if(!this._scale9Image)
            return;
        //backup the contentSize
        var contentSize = this._contentSize;
        var tempWidth = contentSize.width, tempHeight = contentSize.height;

        this.updateWithBatchNode(this._scale9Image, this._spriteRect, this._spriteFrameRotated, capInsets);
        //restore the contentSize
        this.setContentSize(tempWidth, tempHeight);
    },

    /**
     * Gets the left side inset
     * @returns {number}
     */
    getInsetLeft: function () {
        return this._insetLeft;
    },

    /**
     * Sets the left side inset
     * @param {Number} insetLeft
     */
    setInsetLeft: function (insetLeft) {
        this._insetLeft = insetLeft;
        this._updateCapInset();
    },

    /**
     * Gets the top side inset
     * @returns {number}
     */
    getInsetTop: function () {
        return this._insetTop;
    },

    /**
     * Sets the top side inset
     * @param {Number} insetTop
     */
    setInsetTop: function (insetTop) {
        this._insetTop = insetTop;
        this._updateCapInset();
    },

    /**
     * Gets the right side inset
     * @returns {number}
     */
    getInsetRight: function () {
        return this._insetRight;
    },
    /**
     * Sets the right side inset
     * @param {Number} insetRight
     */
    setInsetRight: function (insetRight) {
        this._insetRight = insetRight;
        this._updateCapInset();
    },

    /**
     * Gets the bottom side inset
     * @returns {number}
     */
    getInsetBottom: function () {
        return this._insetBottom;
    },
    /**
     * Sets the bottom side inset
     * @param {number} insetBottom
     */
    setInsetBottom: function (insetBottom) {
        this._insetBottom = insetBottom;
        this._updateCapInset();
    },

    /**
     * Sets the untransformed size of the Scale9Sprite.
     * @override
     * @param {cc.Size|Number} size The untransformed size of the Scale9Sprite or The untransformed size's width of the Scale9Sprite.
     * @param {Number} [height] The untransformed size's height of the Scale9Sprite.
     */
    setContentSize: function (size, height) {
        cc.Node.prototype.setContentSize.call(this, size, height);
        this._positionsAreDirty = true;
    },

    _setWidth: function (value) {
        cc.Node.prototype._setWidth.call(this, value);
        this._positionsAreDirty = true;
    },

    _setHeight: function (value) {
        cc.Node.prototype._setHeight.call(this, value);
        this._positionsAreDirty = true;
    },

    /**
     * Initializes a cc.Scale9Sprite. please do not call this function by yourself, you should pass the parameters to constructor to initialize it.
     * @returns {boolean}
     */
    init: function () {
        return this.initWithBatchNode(null, cc.rect(0, 0, 0, 0), false, cc.rect(0, 0, 0, 0));
    },

    /**
     * Initializes a 9-slice sprite with a SpriteBatchNode.
     * @param {cc.SpriteBatchNode} batchNode
     * @param {cc.Rect} rect
     * @param {boolean|cc.Rect} rotated
     * @param {cc.Rect} [capInsets]
     * @returns {boolean}
     */
    initWithBatchNode: function (batchNode, rect, rotated, capInsets) {
        if (capInsets === undefined) {
            capInsets = rotated;
            rotated = false;
        }

        if (batchNode)
            this.updateWithBatchNode(batchNode, rect, rotated, capInsets);
        this.setCascadeColorEnabled(true);
        this.setCascadeOpacityEnabled(true);
        this.setAnchorPoint(0.5, 0.5);
        this._positionsAreDirty = true;
        return true;
    },

    /**
     * Initializes a 9-slice sprite with a texture file, a delimitation zone and
     * with the specified cap insets.
     * Once the sprite is created, you can then call its "setContentSize:" method
     * to resize the sprite will all it's 9-slice goodness intact.
     * It respects the anchorPoint too.
     *
     * @param {String} file The name of the texture file.
     * @param {cc.Rect} rect The rectangle that describes the sub-part of the texture that
     * is the whole image. If the shape is the whole texture, set this to the texture's full rect.
     * @param {cc.Rect} capInsets The values to use for the cap insets.
     */
    initWithFile: function (file, rect, capInsets) {
        if (file instanceof cc.Rect) {
            file = arguments[1];
            capInsets = arguments[0];
            rect = cc.rect(0, 0, 0, 0);
        } else {
            rect = rect || cc.rect(0, 0, 0, 0);
            capInsets = capInsets || cc.rect(0, 0, 0, 0);
        }

        if(!file)
            throw "cc.Scale9Sprite.initWithFile(): file should be non-null";

        var texture = cc.textureCache.getTextureForKey(file);
        if (!texture) {
            texture = cc.textureCache.addImage(file);
        }

        var locLoaded = texture.isLoaded();
        this._textureLoaded = locLoaded;
        if(!locLoaded){
            texture.addEventListener("load", function(sender){
                // the texture is rotated on Canvas render mode, so isRotated always is false.
                var preferredSize = this._preferredSize, restorePreferredSize = (preferredSize.width !== 0 || preferredSize.height !== 0);
                if(restorePreferredSize)preferredSize = cc.size(preferredSize.width, preferredSize.height);
                var size  = sender.getContentSize();
                this.updateWithBatchNode(this._scale9Image, cc.rect(0,0,size.width,size.height), false, this._capInsets);
                if(restorePreferredSize)this.setPreferredSize(preferredSize);
                this._positionsAreDirty = true;
                this.dispatchEvent("load");
            }, this);
        }

        return this.initWithBatchNode(new cc.SpriteBatchNode(file, 9), rect, false, capInsets);
    },

    /**
     * Initializes a 9-slice sprite with an sprite frame and with the specified
     * cap insets.
     * Once the sprite is created, you can then call its "setContentSize:" method
     * to resize the sprite will all it's 9-slice goodness interact.
     * It respects the anchorPoint too.
     *
     * @param spriteFrame The sprite frame object.
     * @param capInsets The values to use for the cap insets.
     */
    initWithSpriteFrame: function (spriteFrame, capInsets) {
        if(!spriteFrame || !spriteFrame.getTexture())
            throw "cc.Scale9Sprite.initWithSpriteFrame(): spriteFrame should be non-null and its texture should be non-null";

        capInsets = capInsets || cc.rect(0, 0, 0, 0);
        var locLoaded = spriteFrame.textureLoaded();
        this._textureLoaded = locLoaded;
        if(!locLoaded){
            spriteFrame.addEventListener("load", function(sender){
                // the texture is rotated on Canvas render mode, so isRotated always is false.
                var preferredSize = this._preferredSize, restorePreferredSize = (preferredSize.width !== 0 || preferredSize.height !== 0);
                if(restorePreferredSize)preferredSize = cc.size(preferredSize.width, preferredSize.height);
                this.updateWithBatchNode(this._scale9Image, sender.getRect(), cc._renderType === cc._RENDER_TYPE_WEBGL && sender.isRotated(), this._capInsets);
                if(restorePreferredSize)this.setPreferredSize(preferredSize);
                this._positionsAreDirty = true;
                this.dispatchEvent("load");
            },this);
        }
        var batchNode = new cc.SpriteBatchNode(spriteFrame.getTexture(), 9);
        // the texture is rotated on Canvas render mode, so isRotated always is false.
        return this.initWithBatchNode(batchNode, spriteFrame.getRect(), cc._renderType === cc._RENDER_TYPE_WEBGL && spriteFrame.isRotated(), capInsets);
    },

    /**
     * Initializes a 9-slice sprite with an sprite frame name and with the specified
     * cap insets.
     * Once the sprite is created, you can then call its "setContentSize:" method
     * to resize the sprite will all it's 9-slice goodness interact.
     * It respects the anchorPoint too.
     *
     * @param spriteFrameName The sprite frame name.
     * @param capInsets The values to use for the cap insets.
     */
    initWithSpriteFrameName: function (spriteFrameName, capInsets) {
        if(!spriteFrameName)
            throw "cc.Scale9Sprite.initWithSpriteFrameName(): spriteFrameName should be non-null";
        capInsets = capInsets || cc.rect(0, 0, 0, 0);

        var frame = cc.spriteFrameCache.getSpriteFrame(spriteFrameName);
        if (frame == null) {
            cc.log("cc.Scale9Sprite.initWithSpriteFrameName(): can't find the sprite frame by spriteFrameName");
            return false;
        }

        return this.initWithSpriteFrame(frame, capInsets);
    },

    /**
     * Creates and returns a new sprite object with the specified cap insets.
     * You use this method to add cap insets to a sprite or to change the existing
     * cap insets of a sprite. In both cases, you get back a new image and the
     * original sprite remains untouched.
     *
     * @param {cc.Rect} capInsets The values to use for the cap insets.
     */
    resizableSpriteWithCapInsets: function (capInsets) {
        var pReturn = new cc.Scale9Sprite();
        if (pReturn && pReturn.initWithBatchNode(this._scale9Image, this._spriteRect, false, capInsets))
            return pReturn;
        return null;
    },

    /** sets the premultipliedAlphaOpacity property.
     If set to NO then opacity will be applied as: glColor(R,G,B,opacity);
     If set to YES then opacity will be applied as: glColor(opacity, opacity, opacity, opacity );
     Textures with premultiplied alpha will have this property by default on YES. Otherwise the default value is NO
     @since v0.8
     */
    setOpacityModifyRGB: function (value) {
        if(!this._scale9Image)
            return;
        this._opacityModifyRGB = value;
        var scaleChildren = this._scale9Image.getChildren();
        if (scaleChildren) {
            for (var i = 0, len = scaleChildren.length; i < len; i++)
                scaleChildren[i].setOpacityModifyRGB(value);
        }
    },

    /** returns whether or not the opacity will be applied using glColor(R,G,B,opacity) or glColor(opacity, opacity, opacity, opacity);
     @since v0.8
     */
    isOpacityModifyRGB: function () {
        return this._opacityModifyRGB;
    },

    /**
     * Update the scale9Sprite with a SpriteBatchNode.
     * @param {cc.SpriteBatchNode} batchNode
     * @param {cc.Rect} originalRect
     * @param {boolean} rotated
     * @param {cc.Rect} capInsets
     * @returns {boolean}
     */
    updateWithBatchNode: function (batchNode, originalRect, rotated, capInsets) {
        var opacity = this.getOpacity();
        var color = this.getColor();
        var rect = cc.rect(originalRect.x, originalRect.y, originalRect.width, originalRect.height);

        // Release old sprites
        this.removeAllChildren(true);

        if (this._scale9Image !== batchNode)
            this._scale9Image = batchNode;

        if(!this._scale9Image)
            return false;

        var tmpTexture = batchNode.getTexture();
        var locLoaded = tmpTexture.isLoaded();
        this._textureLoaded = locLoaded;

        //this._capInsets = capInsets;
        var locCapInsets = this._capInsets;
        locCapInsets.x = capInsets.x;
        locCapInsets.y = capInsets.y;
        locCapInsets.width = capInsets.width;
        locCapInsets.height = capInsets.height;

        if(!locLoaded){
            tmpTexture.addEventListener("load", function(sender){
                this._positionsAreDirty = true;
                this.dispatchEvent("load");
            },this);
            return true;
        }
        var locScale9Image = this._scale9Image;
        locScale9Image.removeAllChildren(true);

        this._spriteFrameRotated = rotated;

        var selTexture = locScale9Image.getTexture();

        // If there is no given rect
        if (cc._rectEqualToZero(rect)) {
            // Get the texture size as original
            var textureSize = selTexture.getContentSize();
            rect = cc.rect(0, 0, textureSize.width, textureSize.height);
        }

        // Set the given rect's size as original size
        this._spriteRect = rect;
        var locSpriteRect = this._spriteRect;
        locSpriteRect.x = rect.x;
        locSpriteRect.y = rect.y;
        locSpriteRect.width = rect.width;
        locSpriteRect.height = rect.height;

        this._originalSize.width = rect.width;
        this._originalSize.height = rect.height;

        var locPreferredSize = this._preferredSize;
        if(locPreferredSize.width === 0 && locPreferredSize.height === 0){
            locPreferredSize.width = rect.width;
            locPreferredSize.height = rect.height;
        }

        var locCapInsetsInternal = this._capInsetsInternal;
        if(capInsets){
            locCapInsetsInternal.x = capInsets.x;
            locCapInsetsInternal.y = capInsets.y;
            locCapInsetsInternal.width = capInsets.width;
            locCapInsetsInternal.height = capInsets.height;
        }
        var w = rect.width, h = rect.height;

        // If there is no specified center region
        if (cc._rectEqualToZero(locCapInsetsInternal)) {
            // CCLog("... cap insets not specified : using default cap insets ...");
            locCapInsetsInternal.x = w / 3;
            locCapInsetsInternal.y = h / 3;
            locCapInsetsInternal.width = w / 3;
            locCapInsetsInternal.height = h / 3;
        }

        var left_w = locCapInsetsInternal.x, center_w = locCapInsetsInternal.width, right_w = w - (left_w + center_w);

        var top_h = locCapInsetsInternal.y, center_h = locCapInsetsInternal.height, bottom_h = h - (top_h + center_h);

        // calculate rects
        // ... top row
        var x = 0.0, y = 0.0;

        // top left
        var lefttopbounds = cc.rect(x + 0.5 | 0, y + 0.5 | 0, left_w + 0.5 | 0, top_h + 0.5 | 0);

        // top center
        x += left_w;
        var centertopbounds = cc.rect(x + 0.5 | 0, y + 0.5 | 0, center_w + 0.5 | 0, top_h + 0.5 | 0);

        // top right
        x += center_w;
        var righttopbounds = cc.rect(x + 0.5 | 0, y + 0.5 | 0, right_w + 0.5 | 0, top_h + 0.5 | 0);

        // ... center row
        x = 0.0;
        y = 0.0;

        y += top_h;
        // center left
        var leftcenterbounds = cc.rect(x + 0.5 | 0, y + 0.5 | 0, left_w + 0.5 | 0, center_h + 0.5 | 0);

        // center center
        x += left_w;
        var centerbounds = cc.rect(x + 0.5 | 0, y + 0.5 | 0, center_w + 0.5 | 0, center_h + 0.5 | 0);

        // center right
        x += center_w;
        var rightcenterbounds = cc.rect(x + 0.5 | 0, y + 0.5 | 0, right_w + 0.5 | 0, center_h + 0.5 | 0);

        // ... bottom row
        x = 0.0;
        y = 0.0;
        y += top_h;
        y += center_h;

        // bottom left
        var leftbottombounds = cc.rect(x + 0.5 | 0, y + 0.5 | 0, left_w + 0.5 | 0, bottom_h + 0.5 | 0);

        // bottom center
        x += left_w;
        var centerbottombounds = cc.rect(x + 0.5 | 0, y + 0.5 | 0, center_w + 0.5 | 0, bottom_h + 0.5 | 0);

        // bottom right
        x += center_w;
        var rightbottombounds = cc.rect(x + 0.5 | 0, y + 0.5 | 0, right_w + 0.5 | 0, bottom_h + 0.5 | 0);

        var t = cc.affineTransformMakeIdentity();
        if (!rotated) {
            // CCLog("!rotated");
            t = cc.affineTransformTranslate(t, rect.x, rect.y);

            cc._rectApplyAffineTransformIn(centerbounds, t);
            cc._rectApplyAffineTransformIn(rightbottombounds, t);
            cc._rectApplyAffineTransformIn(leftbottombounds, t);
            cc._rectApplyAffineTransformIn(righttopbounds, t);
            cc._rectApplyAffineTransformIn(lefttopbounds, t);
            cc._rectApplyAffineTransformIn(rightcenterbounds, t);
            cc._rectApplyAffineTransformIn(leftcenterbounds, t);
            cc._rectApplyAffineTransformIn(centerbottombounds, t);
            cc._rectApplyAffineTransformIn(centertopbounds, t);

            // Centre
            this._centre = new cc.Sprite();
            this._centre.initWithTexture(selTexture, centerbounds);
            locScale9Image.addChild(this._centre, 0, cc.Scale9Sprite.POSITIONS_CENTRE);

            // Top
            this._top = new cc.Sprite();
            this._top.initWithTexture(selTexture, centertopbounds);
            locScale9Image.addChild(this._top, 1, cc.Scale9Sprite.POSITIONS_TOP);

            // Bottom
            this._bottom = new cc.Sprite();
            this._bottom.initWithTexture(selTexture, centerbottombounds);
            locScale9Image.addChild(this._bottom, 1, cc.Scale9Sprite.POSITIONS_BOTTOM);

            // Left
            this._left = new cc.Sprite();
            this._left.initWithTexture(selTexture, leftcenterbounds);
            locScale9Image.addChild(this._left, 1, cc.Scale9Sprite.POSITIONS_LEFT);

            // Right
            this._right = new cc.Sprite();
            this._right.initWithTexture(selTexture, rightcenterbounds);
            locScale9Image.addChild(this._right, 1, cc.Scale9Sprite.POSITIONS_RIGHT);

            // Top left
            this._topLeft = new cc.Sprite();
            this._topLeft.initWithTexture(selTexture, lefttopbounds);
            locScale9Image.addChild(this._topLeft, 2, cc.Scale9Sprite.POSITIONS_TOPLEFT);

            // Top right
            this._topRight = new cc.Sprite();
            this._topRight.initWithTexture(selTexture, righttopbounds);
            locScale9Image.addChild(this._topRight, 2, cc.Scale9Sprite.POSITIONS_TOPRIGHT);

            // Bottom left
            this._bottomLeft = new cc.Sprite();
            this._bottomLeft.initWithTexture(selTexture, leftbottombounds);
            locScale9Image.addChild(this._bottomLeft, 2, cc.Scale9Sprite.POSITIONS_BOTTOMLEFT);

            // Bottom right
            this._bottomRight = new cc.Sprite();
            this._bottomRight.initWithTexture(selTexture, rightbottombounds);
            locScale9Image.addChild(this._bottomRight, 2, cc.Scale9Sprite.POSITIONS_BOTTOMRIGHT);
        } else {
            // set up transformation of coordinates
            // to handle the case where the sprite is stored rotated
            // in the spritesheet
            // CCLog("rotated");
            var rotatedcenterbounds = centerbounds;
            var rotatedrightbottombounds = rightbottombounds;
            var rotatedleftbottombounds = leftbottombounds;
            var rotatedrighttopbounds = righttopbounds;
            var rotatedlefttopbounds = lefttopbounds;
            var rotatedrightcenterbounds = rightcenterbounds;
            var rotatedleftcenterbounds = leftcenterbounds;
            var rotatedcenterbottombounds = centerbottombounds;
            var rotatedcentertopbounds = centertopbounds;

            t = cc.affineTransformTranslate(t, rect.height + rect.x, rect.y);
            t = cc.affineTransformRotate(t, 1.57079633);

            centerbounds = cc.rectApplyAffineTransform(centerbounds, t);
            rightbottombounds = cc.rectApplyAffineTransform(rightbottombounds, t);
            leftbottombounds = cc.rectApplyAffineTransform(leftbottombounds, t);
            righttopbounds = cc.rectApplyAffineTransform(righttopbounds, t);
            lefttopbounds = cc.rectApplyAffineTransform(lefttopbounds, t);
            rightcenterbounds = cc.rectApplyAffineTransform(rightcenterbounds, t);
            leftcenterbounds = cc.rectApplyAffineTransform(leftcenterbounds, t);
            centerbottombounds = cc.rectApplyAffineTransform(centerbottombounds, t);
            centertopbounds = cc.rectApplyAffineTransform(centertopbounds, t);

            rotatedcenterbounds.x = centerbounds.x;
            rotatedcenterbounds.y = centerbounds.y;

            rotatedrightbottombounds.x = rightbottombounds.x;
            rotatedrightbottombounds.y = rightbottombounds.y;

            rotatedleftbottombounds.x = leftbottombounds.x;
            rotatedleftbottombounds.y = leftbottombounds.y;

            rotatedrighttopbounds.x = righttopbounds.x;
            rotatedrighttopbounds.y = righttopbounds.y;

            rotatedlefttopbounds.x = lefttopbounds.x;
            rotatedlefttopbounds.y = lefttopbounds.y;

            rotatedrightcenterbounds.x = rightcenterbounds.x;
            rotatedrightcenterbounds.y = rightcenterbounds.y;

            rotatedleftcenterbounds.x = leftcenterbounds.x;
            rotatedleftcenterbounds.y = leftcenterbounds.y;

            rotatedcenterbottombounds.x = centerbottombounds.x;
            rotatedcenterbottombounds.y = centerbottombounds.y;

            rotatedcentertopbounds.x = centertopbounds.x;
            rotatedcentertopbounds.y = centertopbounds.y;

            // Centre
            this._centre = new cc.Sprite();
            this._centre.initWithTexture(selTexture, rotatedcenterbounds, true);
            locScale9Image.addChild(this._centre, 0, cc.Scale9Sprite.POSITIONS_CENTRE);

            // Top
            this._top = new cc.Sprite();
            this._top.initWithTexture(selTexture, rotatedcentertopbounds, true);
            locScale9Image.addChild(this._top, 1, cc.Scale9Sprite.POSITIONS_TOP);

            // Bottom
            this._bottom = new cc.Sprite();
            this._bottom.initWithTexture(selTexture, rotatedcenterbottombounds, true);
            locScale9Image.addChild(this._bottom, 1, cc.Scale9Sprite.POSITIONS_BOTTOM);

            // Left
            this._left = new cc.Sprite();
            this._left.initWithTexture(selTexture, rotatedleftcenterbounds, true);
            locScale9Image.addChild(this._left, 1, cc.Scale9Sprite.POSITIONS_LEFT);

            // Right
            this._right = new cc.Sprite();
            this._right.initWithTexture(selTexture, rotatedrightcenterbounds, true);
            locScale9Image.addChild(this._right, 1, cc.Scale9Sprite.POSITIONS_RIGHT);

            // Top left
            this._topLeft = new cc.Sprite();
            this._topLeft.initWithTexture(selTexture, rotatedlefttopbounds, true);
            locScale9Image.addChild(this._topLeft, 2, cc.Scale9Sprite.POSITIONS_TOPLEFT);

            // Top right
            this._topRight = new cc.Sprite();
            this._topRight.initWithTexture(selTexture, rotatedrighttopbounds, true);
            locScale9Image.addChild(this._topRight, 2, cc.Scale9Sprite.POSITIONS_TOPRIGHT);

            // Bottom left
            this._bottomLeft = new cc.Sprite();
            this._bottomLeft.initWithTexture(selTexture, rotatedleftbottombounds, true);
            locScale9Image.addChild(this._bottomLeft, 2, cc.Scale9Sprite.POSITIONS_BOTTOMLEFT);

            // Bottom right
            this._bottomRight = new cc.Sprite();
            this._bottomRight.initWithTexture(selTexture, rotatedrightbottombounds, true);
            locScale9Image.addChild(this._bottomRight, 2, cc.Scale9Sprite.POSITIONS_BOTTOMRIGHT);
        }

        this.setContentSize(rect.width, rect.height);
        if(cc._renderType === cc._RENDER_TYPE_WEBGL)
            this.addChild(locScale9Image);

        if (this._spritesGenerated) {
            // Restore color and opacity
            this.setOpacity(opacity);
            this.setColor(color);
        }
        this._spritesGenerated = true;
        return true;
    },

    /**
     * set the sprite frame of cc.Scale9Sprite
     * @param {cc.SpriteFrame} spriteFrame
     */
    setSpriteFrame: function (spriteFrame) {
        var batchNode = new cc.SpriteBatchNode(spriteFrame.getTexture(), 9);
        // the texture is rotated on Canvas render mode, so isRotated always is false.
        var locLoaded = spriteFrame.textureLoaded();
        this._textureLoaded = locLoaded;
        if(!locLoaded){
            spriteFrame.addEventListener("load", function(sender){
                // the texture is rotated on Canvas render mode, so isRotated always is false.
                var preferredSize = this._preferredSize, restorePreferredSize = (preferredSize.width !== 0 || preferredSize.height !== 0);
                if(restorePreferredSize)preferredSize = cc.size(preferredSize.width, preferredSize.height);
                this.updateWithBatchNode(this._scale9Image, sender.getRect(), cc._renderType === cc._RENDER_TYPE_WEBGL && sender.isRotated(), this._capInsets);
                if(restorePreferredSize)this.setPreferredSize(preferredSize);
                this._positionsAreDirty = true;
                this.dispatchEvent("load");
            },this);
        }
        this.updateWithBatchNode(batchNode, spriteFrame.getRect(), cc._renderType === cc._RENDER_TYPE_WEBGL && spriteFrame.isRotated(), cc.rect(0, 0, 0, 0));

        // Reset insets
        this._insetLeft = 0;
        this._insetTop = 0;
        this._insetRight = 0;
        this._insetBottom = 0;
    },

    //v3.3
    /**
     * Sets cc.Scale9Sprite's state
     * @since v3.3
     * @param {Number} state
     */
    setState: function(state){
        this._renderCmd.setState(state);
    },

    //setScale9Enabled implement late

    /**
     * Sets whether the widget should be flipped horizontally or not.
     * @since v3.3
     * @param flippedX true if the widget should be flipped horizontally, false otherwise.
     */
    setFlippedX: function(flippedX){
        var realScale = this.getScaleX();
        this._flippedX = flippedX;
        this.setScaleX(realScale);
    },

    /**
     * <p>
     * Returns the flag which indicates whether the widget is flipped horizontally or not.                         <br/>
     *                                                                                                             <br/>
     * It only flips the texture of the widget, and not the texture of the widget's children.                      <br/>
     * Also, flipping the texture doesn't alter the anchorPoint.                                                   <br/>
     * If you want to flip the anchorPoint too, and/or to flip the children too use:                               <br/>
     * widget->setScaleX(sprite->getScaleX() * -1);                                                                <br/>
     * </p>
     * @since v3.3
     * @return {Boolean} true if the widget is flipped horizontally, false otherwise.
     */
    isFlippedX: function(){
        return this._flippedX;
    },

    /**
     * Sets whether the widget should be flipped vertically or not.
     * @since v3.3
     * @param flippedY true if the widget should be flipped vertically, false otherwise.
     */
    setFlippedY:function(flippedY){
        var realScale = this.getScaleY();
        this._flippedY = flippedY;
        this.setScaleY(realScale);
    },

    /**
     * <p>
     * Return the flag which indicates whether the widget is flipped vertically or not.                             <br/>
     *                                                                                                              <br/>
     * It only flips the texture of the widget, and not the texture of the widget's children.                       <br/>
     * Also, flipping the texture doesn't alter the anchorPoint.                                                    <br/>
     * If you want to flip the anchorPoint too, and/or to flip the children too use:                                <br/>
     * widget->setScaleY(widget->getScaleY() * -1);                                                                 <br/>
     * </p>
     * @since v3.3
     * @return {Boolean} true if the widget is flipped vertically, false otherwise.
     */
    isFlippedY:function(){
        return this._flippedY;
    },

    setScaleX: function (scaleX) {
        if (this._flippedX)
            scaleX = scaleX * -1;
        cc.Node.prototype.setScaleX.call(this, scaleX);
    },

    setScaleY: function (scaleY) {
        if (this._flippedY)
            scaleY = scaleY * -1;
        cc.Node.prototype.setScaleY.call(this, scaleY);
    },

    setScale: function (scaleX, scaleY) {
        if(scaleY === undefined)
            scaleY = scaleX;
        this.setScaleX(scaleX);
        this.setScaleY(scaleY);
    },

    getScaleX: function () {
        var originalScale = cc.Node.prototype.getScaleX.call(this);
        if (this._flippedX)
            originalScale = originalScale * -1.0;
        return originalScale;
    },

    getScaleY: function () {
        var originalScale = cc.Node.prototype.getScaleY.call(this);
        if (this._flippedY)
            originalScale = originalScale * -1.0;
        return originalScale;
    },

    getScale: function () {
        if(this.getScaleX() !== this.getScaleY())
            cc.log("Scale9Sprite#scale. ScaleX != ScaleY. Don't know which one to return");
        return this.getScaleX();
    },

    _createRenderCmd: function(){
        if(cc._renderType === cc._RENDER_TYPE_CANVAS)
            return new cc.Scale9Sprite.CanvasRenderCmd(this);
        else
            return new cc.Scale9Sprite.WebGLRenderCmd(this);
    }
});

var _p = cc.Scale9Sprite.prototype;
cc.EventHelper.prototype.apply(_p);

// Extended properties
/** @expose */
_p.preferredSize;
cc.defineGetterSetter(_p, "preferredSize", _p.getPreferredSize, _p.setPreferredSize);
/** @expose */
_p.capInsets;
cc.defineGetterSetter(_p, "capInsets", _p.getCapInsets, _p.setCapInsets);
/** @expose */
_p.insetLeft;
cc.defineGetterSetter(_p, "insetLeft", _p.getInsetLeft, _p.setInsetLeft);
/** @expose */
_p.insetTop;
cc.defineGetterSetter(_p, "insetTop", _p.getInsetTop, _p.setInsetTop);
/** @expose */
_p.insetRight;
cc.defineGetterSetter(_p, "insetRight", _p.getInsetRight, _p.setInsetRight);
/** @expose */
_p.insetBottom;
cc.defineGetterSetter(_p, "insetBottom", _p.getInsetBottom, _p.setInsetBottom);

_p = null;

/**
 * Creates a 9-slice sprite with a texture file, a delimitation zone and
 * with the specified cap insets.
 * @deprecated
 * @param {String|cc.SpriteFrame} file file name of texture or a cc.Sprite object
 * @param {cc.Rect} rect the rect of the texture
 * @param {cc.Rect} capInsets the cap insets of cc.Scale9Sprite
 * @returns {cc.Scale9Sprite}
 */
cc.Scale9Sprite.create = function (file, rect, capInsets) {
    return new cc.Scale9Sprite(file, rect, capInsets);
};

/**
 * @deprecated
 * @param spriteFrame
 * @param capInsets
 * @returns {cc.Scale9Sprite}
 */
cc.Scale9Sprite.createWithSpriteFrame = function (spriteFrame, capInsets) {
    return new cc.Scale9Sprite(spriteFrame, capInsets);
};

/**
 * @deprecated
 * @param spriteFrameName
 * @param capInsets
 * @returns {cc.Scale9Sprite}
 */
cc.Scale9Sprite.createWithSpriteFrameName = function (spriteFrameName, capInsets) {
    return new cc.Scale9Sprite(spriteFrameName, capInsets);
};

/**
 * @ignore
 */
cc.Scale9Sprite.POSITIONS_CENTRE = 0;
cc.Scale9Sprite.POSITIONS_TOP = 1;
cc.Scale9Sprite.POSITIONS_LEFT = 2;
cc.Scale9Sprite.POSITIONS_RIGHT = 3;
cc.Scale9Sprite.POSITIONS_BOTTOM = 4;
cc.Scale9Sprite.POSITIONS_TOPRIGHT = 5;
cc.Scale9Sprite.POSITIONS_TOPLEFT = 6;
cc.Scale9Sprite.POSITIONS_BOTTOMRIGHT = 7;

cc.Scale9Sprite.state = {NORMAL: 0, GRAY: 1};

