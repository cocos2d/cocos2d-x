/*
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
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

// move from extension
// start
//PhysicsDebugNode
cc.PhysicsDebugNode.create = function( space ) {
    var s = space;
    if( space.handle !== undefined )
        s = space.handle;
    return cc.PhysicsDebugNode._create( s );
};

cc.PhysicsDebugNode.prototype._ctor = function(space){
    this.init();
    var s = space;
    if( space.handle !== undefined )
        s = space.handle;
    this.setSpace(s);
};

cc.PhysicsDebugNode.prototype.setSpace = function( space ) {
    var s = space;
    if( space.handle !== undefined )
        s = space.handle;
    return this._setSpace( s );
};

// physicsSprite
cc.PhysicsSprite.prototype.setBody = function( body ) {
    var b = body;
    if( body.handle !== undefined )
        b = body.handle;
    return this._setCPBody( b );
};

cc.PhysicsSprite.prototype.getBody = function() {
    return this.getCPBody();
};
// end

// move from property_impls
// start
_safeExtend(cc.PhysicsSprite.prototype, {
    setPositionX: function(x) {
        this.setPosition( cc.p(x, this.getPositionY()) );
    },
    setPositionY: function(y) {
        this.setPosition( cc.p(this.getPositionX(), y) );
    }
});
// end

// move from property_apis
// start
var _proto = cc.PhysicsSprite.prototype;
cc.defineGetterSetter(_proto, "body", _proto.getBody, _proto.setBody);
cc.defineGetterSetter(_proto, "x", _proto.getPositionX, _proto.setPositionX);
cc.defineGetterSetter(_proto, "y", _proto.getPositionY, _proto.setPositionY);
cc.defineGetterSetter(_proto, "rotation", _proto.getRotation, _proto.setRotation);
cc.defineGetterSetter(_proto, "dirty", _proto.isDirty, _proto.setDirty);
// end

// move from create_apis
// start
/************************  PhysicsSprite  *************************/
var _p = cc.PhysicsSprite.prototype;
_p._ctor = function(fileName, rect){
    if (fileName === undefined) {
        cc.PhysicsSprite.prototype.init.call(this);
    }else if (typeof(fileName) === "string") {
        if (fileName[0] === "#") {
            //init with a sprite frame name
            var frameName = fileName.substr(1, fileName.length - 1);
            var spriteFrame = cc.spriteFrameCache.getSpriteFrame(frameName);
            this.initWithSpriteFrame(spriteFrame);
        } else {
            //init  with filename and rect
            if(rect)
                this.initWithFile(fileName, rect);
            else
                this.initWithFile(fileName);
        }
    }else if (typeof(fileName) === "object") {
        if (fileName instanceof cc.Texture2D) {
            //init  with texture and rect
            this.initWithTexture(fileName, rect);
        } else if (fileName instanceof cc.SpriteFrame) {
            //init with a sprite frame
            this.initWithSpriteFrame(fileName);
        }
    }
};

cc.PhysicsSprite._create = cc.PhysicsSprite.create;
cc.PhysicsSprite.create = function (fileName, rect) {
    var sprite;

    if (arguments.length == 0) {
        sprite = cc.PhysicsSprite._create();
        return sprite;
    }

    if (typeof(fileName) === "string") {
        if (fileName[0] === "#") {
            //init with a sprite frame name
            var frameName = fileName.substr(1, fileName.length - 1);
            var spriteFrame = cc.spriteFrameCache.getSpriteFrame(frameName);
            sprite = cc.PhysicsSprite.createWithSpriteFrame(spriteFrame);
        } else {
            // Create with filename and rect
            sprite = rect ? cc.PhysicsSprite._create(fileName, rect) : cc.PhysicsSprite._create(fileName);
        }
        if (sprite)
            return sprite;
        else return null;
    }

    if (typeof(fileName) === "object") {
        if (fileName instanceof cc.Texture2D) {
            //init  with texture and rect
            sprite = rect ? cc.PhysicsSprite.createWithTexture(fileName, rect) : cc.PhysicsSprite.createWithTexture(fileName);
        } else if (fileName instanceof cc.SpriteFrame) {
            //init with a sprite frame
            sprite = cc.PhysicsSprite.createWithSpriteFrame(fileName)
        }
        if (sprite)
            return  sprite;
        else return null;
    }

    return null;
};
// end

