/****************************************************************************
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

var CustomParticleWidget = ccui.Widget.extend({

    _emitter: null,

    _emitterPlist: null,

    _emitterPostion: null,

    init: function(){
        if (ccui.Widget.prototype.init.call(this))
        {
            return true;
        }
        return false;
    },

    _initRenderer: function(){
        ccui.Widget.prototype._initRenderer.call(this);
    },

    removeAllChildren: function(){
        ccui.Widget.prototype.removeAllChildren.call(this);
    },

    createInstance: function(){
        return CustomParticleWidget.create();
    },
    setParticlePlist: function(plist){
        if (!this._emitter)
        {
            this._emitter = new cc.ParticleSystem(plist);

        }
        else
        {
            this._emitter.removeFromParent();
            this._emitter = new cc.ParticleSystem(plist);
        }
        //Warning!!! don't forget to set the position
        this.addProtectedChild(this._emitter , this.getLocalZOrder() + 1, -1);
        this.setParticlePosition(cc.p(0, 0));

        this._emitterPlist = plist;

    },
    getParticlePlist: function(){
        return this._emitterPlist;
    },
    setParticlePosition: function(pos){
        this._emitter.setPosition(pos);

        this._emitterPostion = pos;

    },
    getParticlePosition: function(){
        return this._emitterPostion;
    },
    playParticle: function(){
        if (this._emitter)
        {
            this._emitter.resetSystem();
        }
    },
    stopParticle: function(){
        if (this._emitter)
        {
            this._emitter.stopSystem();
        }
    }
});

CustomParticleWidget.create = function(){
    var custom = new CustomParticleWidget();

    if (custom && custom.init())
    {
        return custom;
    }
    return null;
};