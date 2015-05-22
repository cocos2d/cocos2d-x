/****************************************************************************
 Copyright (c) 2008-2010 Ricardo Quesada
 Copyright (c) 2011-2012 cocos2d-x.org
 Copyright (c) 2013-2014 Chukong Technologies Inc.
 Copyright (c) 2008-2009 Jason Booth

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
 * cc.MotionStreak manages a Ribbon based on it's motion in absolute space.                 <br/>
 * You construct it with a fadeTime, minimum segment size, texture path, texture            <br/>
 * length and color. The fadeTime controls how long it takes each vertex in                 <br/>
 * the streak to fade out, the minimum segment size it how many pixels the                  <br/>
 * streak will move before adding a new ribbon segment, and the texture                     <br/>
 * length is the how many pixels the texture is stretched across. The texture               <br/>
 * is vertically aligned along the streak segment.
 * @class
 * @extends cc.Node
 *
 * @property {cc.Texture2D} texture                         - Texture used for the motion streak.
 * @property {Boolean}      fastMode                        - Indicate whether use fast mode.
 * @property {Boolean}      startingPositionInitialized     - Indicate whether starting position initialized.
 * @example
 * //example
 * new cc.MotionStreak(2, 3, 32, cc.color.GREEN, s_streak);
 */
cc.MotionStreak = cc.Node.extend(/** @lends cc.MotionStreak# */{
    texture:null,
    fastMode:false,
    startingPositionInitialized:false,

    _blendFunc:null,

    _stroke:0,
    _fadeDelta:0,
    _minSeg:0,

    _maxPoints:0,
    _nuPoints:0,
    _previousNuPoints:0,

    /* Pointers */
    _pointVertexes:null,
    _pointState:null,

    // webgl
    _vertices:null,
    _colorPointer:null,
    _texCoords:null,

    _verticesBuffer:null,
    _colorPointerBuffer:null,
    _texCoordsBuffer:null,
    _className:"MotionStreak",

    /**
     * creates and initializes a motion streak with fade in seconds, minimum segments, stroke's width, color, texture filename or texture   <br/>
     * Constructor of cc.MotionStreak
     * @param {Number} fade time to fade
     * @param {Number} minSeg minimum segment size
     * @param {Number} stroke stroke's width
     * @param {Number} color
     * @param {string|cc.Texture2D} texture texture filename or texture
     */
    ctor: function (fade, minSeg, stroke, color, texture) {
        cc.Node.prototype.ctor.call(this);
        this._positionR = cc.p(0, 0);
        this._blendFunc = new cc.BlendFunc(cc.SRC_ALPHA, cc.ONE_MINUS_SRC_ALPHA);

        this.fastMode = false;
        this.startingPositionInitialized = false;

        this.texture = null;

        this._stroke = 0;
        this._fadeDelta = 0;
        this._minSeg = 0;

        this._maxPoints = 0;
        this._nuPoints = 0;
        this._previousNuPoints = 0;

        /** Pointers */
        this._pointVertexes = null;
        this._pointState = null;

        // webgl
        this._vertices = null;
        this._colorPointer = null;
        this._texCoords = null;

        this._verticesBuffer = null;
        this._colorPointerBuffer = null;
        this._texCoordsBuffer = null;

        if(texture !== undefined)
            this.initWithFade(fade, minSeg, stroke, color, texture);
    },

    /**
     * Gets the texture.
     * @return {cc.Texture2D}
     */
    getTexture:function () {
        return this.texture;
    },

    /**
     * Set the texture.
     * @param {cc.Texture2D} texture
     */
    setTexture:function (texture) {
        if (this.texture !== texture)
            this.texture = texture;
    },

    /**
     * Gets the blend func.
     * @return {cc.BlendFunc}
     */
    getBlendFunc:function () {
        return this._blendFunc;
    },

    /**
     * Set the blend func.
     * @param {Number} src
     * @param {Number} dst
     */
    setBlendFunc:function (src, dst) {
        if (dst === undefined) {
            this._blendFunc = src;
        } else {
            this._blendFunc.src = src;
            this._blendFunc.dst = dst;
        }
    },

    /**
     * Gets opacity.
     * @warning cc.MotionStreak.getOpacity has not been supported.
     * @returns {number}
     */
    getOpacity:function () {
        cc.log("cc.MotionStreak.getOpacity has not been supported.");
        return 0;
    },

    /**
     * Set opacity.
     * @warning cc.MotionStreak.setOpacity has not been supported.
     * @param opacity
     */
    setOpacity:function (opacity) {
        cc.log("cc.MotionStreak.setOpacity has not been supported.");
    },

    /**
     * set opacity modify RGB.
     * @warning cc.MotionStreak.setOpacityModifyRGB has not been supported.
     * @param value
     */
    setOpacityModifyRGB:function (value) {
    },

    /**
     * Checking OpacityModifyRGB.
     * @returns {boolean}
     */
    isOpacityModifyRGB:function () {
        return false;
    },

    /**
     * Checking fast mode.
     * @returns {boolean}
     */
    isFastMode:function () {
        return this.fastMode;
    },

    /**
     * set fast mode
     * @param {Boolean} fastMode
     */
    setFastMode:function (fastMode) {
        this.fastMode = fastMode;
    },

    /**
     * Checking starting position initialized.
     * @returns {boolean}
     */
    isStartingPositionInitialized:function () {
        return this.startingPositionInitialized;
    },

    /**
     * Set Starting Position Initialized.
     * @param {Boolean} startingPositionInitialized
     */
    setStartingPositionInitialized:function (startingPositionInitialized) {
        this.startingPositionInitialized = startingPositionInitialized;
    },

    /**
     * Get stroke.
     * @returns {Number} stroke
     */
    getStroke:function () {
        return this._stroke;
    },

    /**
     * Set stroke.
     * @param {Number} stroke
     */
    setStroke:function (stroke) {
        this._stroke = stroke;
    },

    /**
     * initializes a motion streak with fade in seconds, minimum segments, stroke's width, color and texture filename or texture
     * @param {Number} fade time to fade
     * @param {Number} minSeg minimum segment size
     * @param {Number} stroke stroke's width
     * @param {Number} color
     * @param {string|cc.Texture2D} texture texture filename or texture
     * @return {Boolean}
     */
    initWithFade:function (fade, minSeg, stroke, color, texture) {
        if(!texture)
            throw "cc.MotionStreak.initWithFade(): Invalid filename or texture";

        if (cc.isString(texture))
            texture = cc.textureCache.addImage(texture);

        cc.Node.prototype.setPosition.call(this, cc.p(0,0));
        this.anchorX = 0;
        this.anchorY = 0;
        this.ignoreAnchor = true;
        this.startingPositionInitialized = false;

        this.fastMode = true;
        this._minSeg = (minSeg === -1.0) ? (stroke / 5.0) : minSeg;
        this._minSeg *= this._minSeg;

        this._stroke = stroke;
        this._fadeDelta = 1.0 / fade;

        var locMaxPoints = (0 | (fade * 60)) + 2;
        this._maxPoints = locMaxPoints;
        this._nuPoints = 0;
        this._pointState = new Float32Array(locMaxPoints);
        this._pointVertexes = new Float32Array(locMaxPoints * 2);

        this._vertices = new Float32Array(locMaxPoints * 4);
        this._texCoords = new Float32Array(locMaxPoints * 4);
        this._colorPointer = new Uint8Array(locMaxPoints * 8);

        this._verticesBuffer = gl.createBuffer();
        this._texCoordsBuffer = gl.createBuffer();
        this._colorPointerBuffer = gl.createBuffer();

        // Set blend mode
        this._blendFunc.src = gl.SRC_ALPHA;
        this._blendFunc.dst = gl.ONE_MINUS_SRC_ALPHA;

        this.texture = texture;
        this.color = color;
        this.scheduleUpdate();

        //bind buffer
        gl.bindBuffer(gl.ARRAY_BUFFER, this._verticesBuffer);
        gl.bufferData(gl.ARRAY_BUFFER, this._vertices, gl.DYNAMIC_DRAW);
        gl.bindBuffer(gl.ARRAY_BUFFER, this._texCoordsBuffer);
        gl.bufferData(gl.ARRAY_BUFFER, this._texCoords, gl.DYNAMIC_DRAW);
        gl.bindBuffer(gl.ARRAY_BUFFER, this._colorPointerBuffer);
        gl.bufferData(gl.ARRAY_BUFFER, this._colorPointer, gl.DYNAMIC_DRAW);

        return true;
    },

    /**
     * color used for the tint
     * @param {cc.Color} color
     */
    tintWithColor:function (color) {
        this.color = color;

        // Fast assignation
        var locColorPointer = this._colorPointer;
        for (var i = 0, len = this._nuPoints * 2; i < len; i++) {
            locColorPointer[i * 4] = color.r;
            locColorPointer[i * 4 + 1] = color.g;
            locColorPointer[i * 4 + 2] = color.b;
        }
    },

    /**
     * Remove all living segments of the ribbon
     */
    reset:function () {
        this._nuPoints = 0;
    },

    /**
     * Set the position. <br />
     *
     * @param {cc.Point|Number} position
     * @param {Number} [yValue=undefined] If not exists, the first parameter must be cc.Point.
     */
    setPosition:function (position, yValue) {
        this.startingPositionInitialized = true;
        if(yValue === undefined){
            this._positionR.x = position.x;
            this._positionR.y = position.y;
        } else {
            this._positionR.x = position;
            this._positionR.y = yValue;
        }
    },

    /**
     * Gets the position.x
     * @return {Number}
     */
    getPositionX:function () {
        return this._positionR.x;
    },

    /**
     * Set the position.x
     * @param {Number} x
     */
    setPositionX:function (x) {
        this._positionR.x = x;
        if(!this.startingPositionInitialized)
            this.startingPositionInitialized = true;
    },

    /**
     * Gets the position.y
     * @return {Number}
     */
    getPositionY:function () {
        return  this._positionR.y;
    },

    /**
     * Set the position.y
     * @param {Number} y
     */
    setPositionY:function (y) {
        this._positionR.y = y;
        if(!this.startingPositionInitialized)
            this.startingPositionInitialized = true;
    },

    /**
     * <p>schedules the "update" method.                                                                           <br/>
     * It will use the order number 0. This method will be called every frame.                                  <br/>
     * Scheduled methods with a lower order value will be called before the ones that have a higher order value.<br/>
     * Only one "update" method could be scheduled per node.</p>
     * @param {Number} delta
     */
    update:function (delta) {
        if (!this.startingPositionInitialized)
            return;

        //TODO update the color    (need move to render cmd)
        this._renderCmd._updateDisplayColor();

        delta *= this._fadeDelta;

        var newIdx, newIdx2, i, i2;
        var mov = 0;

        // Update current points
        var locNuPoints = this._nuPoints;
        var locPointState = this._pointState, locPointVertexes = this._pointVertexes, locVertices = this._vertices;
        var locColorPointer = this._colorPointer;

        for (i = 0; i < locNuPoints; i++) {
            locPointState[i] -= delta;

            if (locPointState[i] <= 0)
                mov++;
            else {
                newIdx = i - mov;
                if (mov > 0) {
                    // Move data
                    locPointState[newIdx] = locPointState[i];
                    // Move point
                    locPointVertexes[newIdx * 2] = locPointVertexes[i * 2];
                    locPointVertexes[newIdx * 2 + 1] = locPointVertexes[i * 2 + 1];

                    // Move vertices
                    i2 = i * 2;
                    newIdx2 = newIdx * 2;
                    locVertices[newIdx2 * 2] = locVertices[i2 * 2];
                    locVertices[newIdx2 * 2 + 1] = locVertices[i2 * 2 + 1];
                    locVertices[(newIdx2 + 1) * 2] = locVertices[(i2 + 1) * 2];
                    locVertices[(newIdx2 + 1) * 2 + 1] = locVertices[(i2 + 1) * 2 + 1];

                    // Move color
                    i2 *= 4;
                    newIdx2 *= 4;
                    locColorPointer[newIdx2 + 0] = locColorPointer[i2 + 0];
                    locColorPointer[newIdx2 + 1] = locColorPointer[i2 + 1];
                    locColorPointer[newIdx2 + 2] = locColorPointer[i2 + 2];
                    locColorPointer[newIdx2 + 4] = locColorPointer[i2 + 4];
                    locColorPointer[newIdx2 + 5] = locColorPointer[i2 + 5];
                    locColorPointer[newIdx2 + 6] = locColorPointer[i2 + 6];
                } else
                    newIdx2 = newIdx * 8;

                var op = locPointState[newIdx] * 255.0;
                locColorPointer[newIdx2 + 3] = op;
                locColorPointer[newIdx2 + 7] = op;
            }
        }
        locNuPoints -= mov;

        // Append new point
        var appendNewPoint = true;
        if (locNuPoints >= this._maxPoints)
            appendNewPoint = false;
        else if (locNuPoints > 0) {
            var a1 = cc.pDistanceSQ(cc.p(locPointVertexes[(locNuPoints - 1) * 2], locPointVertexes[(locNuPoints - 1) * 2 + 1]),
                this._positionR) < this._minSeg;
            var a2 = (locNuPoints === 1) ? false : (cc.pDistanceSQ(
                cc.p(locPointVertexes[(locNuPoints - 2) * 2], locPointVertexes[(locNuPoints - 2) * 2 + 1]), this._positionR) < (this._minSeg * 2.0));
            if (a1 || a2)
                appendNewPoint = false;
        }

        if (appendNewPoint) {
            locPointVertexes[locNuPoints * 2] = this._positionR.x;
            locPointVertexes[locNuPoints * 2 + 1] = this._positionR.y;
            locPointState[locNuPoints] = 1.0;

            // Color assignment
            var offset = locNuPoints * 8;

            var locDisplayedColor = this.getDisplayedColor();
            locColorPointer[offset] = locDisplayedColor.r;
            locColorPointer[offset + 1] = locDisplayedColor.g;
            locColorPointer[offset + 2] = locDisplayedColor.b;
            //*((ccColor3B*)(m_pColorPointer + offset+4)) = this._color;
            locColorPointer[offset + 4] = locDisplayedColor.r;
            locColorPointer[offset + 5] = locDisplayedColor.g;
            locColorPointer[offset + 6] = locDisplayedColor.b;

            // Opacity
            locColorPointer[offset + 3] = 255;
            locColorPointer[offset + 7] = 255;

            // Generate polygon
            if (locNuPoints > 0 && this.fastMode) {
                if (locNuPoints > 1)
                    cc.vertexLineToPolygon(locPointVertexes, this._stroke, this._vertices, locNuPoints, 1);
                else
                    cc.vertexLineToPolygon(locPointVertexes, this._stroke, this._vertices, 0, 2);
            }
            locNuPoints++;
        }

        if (!this.fastMode)
            cc.vertexLineToPolygon(locPointVertexes, this._stroke, this._vertices, 0, locNuPoints);

        // Updated Tex Coords only if they are different than previous step
        if (locNuPoints && this._previousNuPoints !== locNuPoints) {
            var texDelta = 1.0 / locNuPoints;
            var locTexCoords = this._texCoords;
            for (i = 0; i < locNuPoints; i++) {
                locTexCoords[i * 4] = 0;
                locTexCoords[i * 4 + 1] = texDelta * i;

                locTexCoords[(i * 2 + 1) * 2] = 1;
                locTexCoords[(i * 2 + 1) * 2 + 1] = texDelta * i;
            }

            this._previousNuPoints = locNuPoints;
        }

        this._nuPoints = locNuPoints;
    },

    _createRenderCmd: function(){
        if(cc._renderType === cc._RENDER_TYPE_WEBGL)
            return new cc.MotionStreak.WebGLRenderCmd(this);
        else
            return null;  //MotionStreak doesn't support Canvas mode
    }
});

/**
 * Please use new cc.MotionStreak instead. <br />
 * Creates and initializes a motion streak with fade in seconds, minimum segments, stroke's width, color, texture filename or texture
 * @deprecated since v3.0 please use new cc.MotionStreak instead.
 * @param {Number} fade time to fade
 * @param {Number} minSeg minimum segment size
 * @param {Number} stroke stroke's width
 * @param {Number} color
 * @param {string|cc.Texture2D} texture texture filename or texture
 * @return {cc.MotionStreak}
 * @example
 * //example
 * new cc.MotionStreak(2, 3, 32, cc.color.GREEN, s_streak);
 */
cc.MotionStreak.create = function (fade, minSeg, stroke, color, texture) {
    return new cc.MotionStreak(fade, minSeg, stroke, color, texture);
};
