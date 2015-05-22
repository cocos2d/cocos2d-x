/**
 * Copyright (c) 2012 Scott Lembcke and Howling Moon Software
 * Copyright (c) 2008-2010 Ricardo Quesada
 * Copyright (c) 2011-2012 cocos2d-x.org
 * Copyright (c) 2013-2014 Chukong Technologies Inc.
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
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/** A CCSprite subclass that is bound to a physics body.
 It works with:
 - Chipmunk: Preprocessor macro CC_ENABLE_CHIPMUNK_INTEGRATION should be defined
 - Objective-Chipmunk: Preprocessor macro CC_ENABLE_CHIPMUNK_INTEGRATION should be defined
 - Box2d: Preprocessor macro CC_ENABLE_BOX2D_INTEGRATION should be defined

 Features and Limitations:
 - Scale and Skew properties are ignored.
 - Position and rotation are going to updated from the physics body
 - If you update the rotation or position manually, the physics body will be updated
 - You can't eble both Chipmunk support and Box2d support at the same time. Only one can be enabled at compile time
 */
(function () {
    var box2dAPI = {
        _ignoreBodyRotation:false,
        _body:null,
        _PTMRatio:32,
        _rotation:1,
        /**
         * Create a PhysicsSprite with filename and rect
         * Constructor of cc.PhysicsSprite for Box2d
         * @param {String|cc.Texture2D|cc.SpriteFrame} fileName
         * @param {cc.Rect} rect
         * @example
         *
         * 1.Create a sprite with image path and rect
         * var physicsSprite1 = new cc.PhysicsSprite("res/HelloHTML5World.png");
         * var physicsSprite2 = new cc.PhysicsSprite("res/HelloHTML5World.png",cc.rect(0,0,480,320));
         *
         * 2.Create a sprite with a sprite frame name. Must add "#" before fame name.
         * var physicsSprite = new cc.PhysicsSprite('#grossini_dance_01.png');
         *
         * 3.Create a sprite with a sprite frame
         * var spriteFrame = cc.spriteFrameCache.getSpriteFrame("grossini_dance_01.png");
         * var physicsSprite = new cc.PhysicsSprite(spriteFrame);
         *
         * 4.Creates a sprite with an existing texture contained in a CCTexture2D object
         *      After creation, the rect will be the size of the texture, and the offset will be (0,0).
         * var texture = cc.textureCache.addImage("HelloHTML5World.png");
         * var physicsSprite1 = new cc.PhysicsSprite(texture);
         * var physicsSprite2 = new cc.PhysicsSprite(texture, cc.rect(0,0,480,320));
         *
         */
        ctor:function(fileName, rect){
            cc.Sprite.prototype.ctor.call(this);

            if (fileName === undefined) {
                cc.PhysicsSprite.prototype.init.call(this);
            }else if (cc.isString(fileName)) {
                if (fileName[0] === "#") {
                    //init with a sprite frame name
                    var frameName = fileName.substr(1, fileName.length - 1);
                    var spriteFrame = cc.spriteFrameCache.getSpriteFrame(frameName);
                    this.initWithSpriteFrame(spriteFrame);
                } else {
                    //init  with filename and rect
                    this.init(fileName, rect);
                }
            }else if (cc.isObject(fileName)) {
                if (fileName instanceof cc.Texture2D) {
                    //init  with texture and rect
                    this.initWithTexture(fileName, rect);
                } else if (fileName instanceof cc.SpriteFrame) {
                    //init with a sprite frame
                    this.initWithSpriteFrame(fileName);
                }
            }
            //this._transformCmd = new cc.PhysicsSpriteTransformCmdCanvas(this);
            //cc.rendererCanvas.pushRenderCommand(this._transformCmd);
        },

        //visit: function(){
        //    cc.Sprite.prototype.visit.call(this);
        //    cc.rendererCanvas.pushRenderCommand(this._transformCmd);
        //},

        /**
         * set body
         * @param {Box2D.Dynamics.b2Body} body
         */
        setBody:function (body) {
            this._body = body;
        },

        /**
         * get body
         * @return {Box2D.Dynamics.b2Body}
         */
        getBody:function () {
            return this._body;
        },

        /**
         * set PTM ratio
         * @param {Number} r
         */
        setPTMRatio:function (r) {
            this._PTMRatio = r;
        },

        /**
         * get PTM ration
         * @return {Number}
         */
        getPTMRatio:function () {
            return this._PTMRatio;
        },

        /**
         * get position
         * @return {cc.Point}
         */
        getPosition:function () {
            var pos = this._body.GetPosition();
            var locPTMRatio =this._PTMRatio;
            return cc.p(pos.x * locPTMRatio, pos.y * locPTMRatio);
        },

        /**
         * set position
         * @param {cc.Point} p
         */
        setPosition:function (p) {
            var angle = this._body.GetAngle();
            var locPTMRatio =this._PTMRatio;
            this._body.setTransform(Box2D.b2Vec2(p.x / locPTMRatio, p.y / locPTMRatio), angle);
            this.setNodeDirty();
        },

        /**
         * get rotation
         * @return {Number}
         */
        getRotation:function () {
            return (this._ignoreBodyRotation ? cc.radiansToDegrees(this._rotationRadians) : cc.radiansToDegrees(this._body.GetAngle()));
        },

        /**
         * set rotation
         * @param {Number} r
         */
        setRotation:function (r) {
            if (this._ignoreBodyRotation) {
                this._rotation = r;
            } else {
                var locBody = this._body;
                var p = locBody.GetPosition();
                locBody.SetTransform(p, cc.degreesToRadians(r));
            }
            this.setNodeDirty();
        },
        _syncPosition:function () {
            var pos = this._body.GetPosition();
            this._position.x = pos.x * this._PTMRatio;
            this._position.y = pos.y * this._PTMRatio;
            this._rotationRadians = this._rotation * (Math.PI / 180);
        },
        _syncRotation:function () {
            this._rotationRadians = this._body.GetAngle();
        },
        /**
         * visit
         */
        visit:function () {
            if (this._body && this._PTMRatio) {
                this._syncPosition();
                if (!this._ignoreBodyRotation)
                    this._syncRotation();
            }
            else {
                cc.log("PhysicsSprite body or PTIMRatio was not set");
            }
            this._super();
        },

        /**
         * set whether to ingore body's rotation
         * @param {Boolean} b
         */
        setIgnoreBodyRotation: function(b) {
            this._ignoreBodyRotation = b;
        }
    };

    var chipmunkAPI = {
        _ignoreBodyRotation:false,
        _body:null, //physics body
        _rotation:1,

        /**
         * Create a PhysicsSprite with filename and rect
         * Constructor of cc.PhysicsSprite for chipmunk
         * @param {String|cc.Texture2D|cc.SpriteFrame} fileName
         * @param {cc.Rect} rect
         * @example
         *
         * 1.Create a sprite with image path and rect
         * var physicsSprite1 = new cc.PhysicsSprite("res/HelloHTML5World.png");
         * var physicsSprite2 = new cc.PhysicsSprite("res/HelloHTML5World.png",cc.rect(0,0,480,320));
         *
         * 2.Create a sprite with a sprite frame name. Must add "#" before frame name.
         * var physicsSprite = new cc.PhysicsSprite('#grossini_dance_01.png');
         *
         * 3.Create a sprite with a sprite frame
         * var spriteFrame = cc.spriteFrameCache.getSpriteFrame("grossini_dance_01.png");
         * var physicsSprite = new cc.PhysicsSprite(spriteFrame);
         *
         * 4.Creates a sprite with an exsiting texture contained in a CCTexture2D object
         *      After creation, the rect will be the size of the texture, and the offset will be (0,0).
         * var texture = cc.textureCache.addImage("HelloHTML5World.png");
         * var physicsSprite1 = new cc.PhysicsSprite(texture);
         * var physicsSprite2 = new cc.PhysicsSprite(texture, cc.rect(0,0,480,320));
         *
         */
        ctor:function(fileName, rect){
            cc.Sprite.prototype.ctor.call(this);

            if (fileName === undefined) {
                cc.PhysicsSprite.prototype.init.call(this);
            }else if (cc.isString(fileName)) {
                if (fileName[0] === "#") {
                    //init with a sprite frame name
                    var frameName = fileName.substr(1, fileName.length - 1);
                    var spriteFrame = cc.spriteFrameCache.getSpriteFrame(frameName);
                    this.initWithSpriteFrame(spriteFrame);
                } else {
                    //init  with filename and rect
                    this.init(fileName, rect);
                }
            }else if (cc.isObject(fileName)) {
                if (fileName instanceof cc.Texture2D) {
                    //init  with texture and rect
                    this.initWithTexture(fileName, rect);
                } else if (fileName instanceof cc.SpriteFrame) {
                    //init with a sprite frame
                    this.initWithSpriteFrame(fileName);
                }
            }

            cc.renderer.pushRenderCommand(this._renderCmd);
        },

        visit: function(){
            cc.renderer.pushRenderCommand(this._renderCmd);
            cc.Sprite.prototype.visit.call(this);
        },

        /**
         * set body
         * @param {cp.Body} body
         */
        setBody:function (body) {
            this._body = body;
        },

        /**
         * get body
         * @returns {cp.Body}
         */
        getBody:function () {
            return this._body;
        },

        /**
         * get position
         * @return {cc.Point}
         */
        getPosition:function () {
            var locBody = this._body;
            return {x:locBody.p.x, y:locBody.p.y};
        },

        /**
         * get position x
         * @return {Number}
         */
        getPositionX:function () {
            return this._body.p.x;
        },

        /**
         * get position y
         * @return {Number}
         */
        getPositionY:function () {
            return this._body.p.y;
        },

        /**
         * set position
         * @param {cc.Point|Number}newPosOrxValue
         * @param {Number}yValue
         */
        setPosition:function (newPosOrxValue, yValue) {
            if (yValue === undefined) {
                this._body.p.x = newPosOrxValue.x;
                this._body.p.y = newPosOrxValue.y;
            } else {
                this._body.p.x = newPosOrxValue;
                this._body.p.y = yValue;
            }
            //this._syncPosition();
        },

        /**
         * set position x
         * @param {Number} xValue
         */
        setPositionX:function (xValue) {
            this._body.p.x = xValue;
            //this._syncPosition();
        },

        /**
         * set position y
         * @param {Number} yValue
         */
        setPositionY:function (yValue) {
            this._body.p.y = yValue;
            //this._syncPosition();
        },

        _syncPosition:function () {
            var locPosition = this._position, locBody = this._body;
            if (locPosition.x !== locBody.p.x || locPosition.y !== locBody.p.y) {
                cc.Sprite.prototype.setPosition.call(this, locBody.p.x, locBody.p.y);
            }
        },

        /**
         * get rotation
         * @return {Number}
         */
        getRotation:function () {
            return this._ignoreBodyRotation ? this._rotationX : -cc.radiansToDegrees(this._body.a);
        },

        /**
         * set rotation
         * @param {Number} r
         */
        setRotation:function (r) {
            if (this._ignoreBodyRotation) {
                cc.Sprite.prototype.setRotation.call(this, r);
            } else {
                this._body.a = -cc.degreesToRadians(r);
                //this._syncRotation();
            }
        },
        _syncRotation:function () {
            if (this._rotationX !== -cc.radiansToDegrees(this._body.a)) {
                cc.Sprite.prototype.setRotation.call(this, -cc.radiansToDegrees(this._body.a));
            }
        },

        /**
         * get the affine transform matrix of node to parent coordinate frame
         * @return {cc.AffineTransform}
         */
        getNodeToParentTransform:function () {
            return this._renderCmd.getNodeToParentTransform();
        },

        /**
         * whether dirty
         * @return {Boolean}
         */
        isDirty:function(){
           return !this._body.isSleeping();
        },
        setDirty: function(){ },

        /**
         * set whether to ignore rotation of body
         * @param {Boolean} b
         */
        setIgnoreBodyRotation: function(b) {
            this._ignoreBodyRotation = b;
        },

        _createRenderCmd: function(){
            if(cc._renderType === cc._RENDER_TYPE_CANVAS)
                return new cc.PhysicsSprite.CanvasRenderCmd(this);
            else
                return new cc.PhysicsSprite.WebGLRenderCmd(this);
        }
    };
    cc.PhysicsSprite = cc.Sprite.extend(chipmunkAPI);
    cc.PhysicsSprite._className = "PhysicsSprite";
    var _p = cc.PhysicsSprite.prototype;
    // Extended properties
    /** @expose */
    _p.body;
    cc.defineGetterSetter(_p, "body", _p.getBody, _p.setBody);
    /** @expose */
    _p.dirty;
    cc.defineGetterSetter(_p, "dirty", _p.isDirty, _p.setDirty);


    /**
     * Create a PhysicsSprite with filename and rect
     * @deprecated since v3.0, please use new cc.PhysicsSprite(fileName, rect) instead
     * @param {String|cc.Texture2D|cc.SpriteFrame} fileName
     * @param {cc.Rect} rect
     * @return {cc.PhysicsSprite}
     */
    cc.PhysicsSprite.create = function (fileName, rect) {
        return new cc.PhysicsSprite(fileName, rect);
    };

    /**
     * @deprecated since v3.0, please use new cc.PhysicsSprite(spriteFrameName) instead
     * @type {Function}
     */
    cc.PhysicsSprite.createWithSpriteFrameName = cc.PhysicsSprite.create;

    /**
     * @deprecated since v3.0, please use new cc.PhysicsSprite(spriteFrame) instead
     * @type {Function}
     */
    cc.PhysicsSprite.createWithSpriteFrame = cc.PhysicsSprite.create;
})();
