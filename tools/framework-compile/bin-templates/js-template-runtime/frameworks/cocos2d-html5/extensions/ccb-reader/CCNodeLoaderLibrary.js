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

cc.NodeLoaderLibrary = cc.Class.extend({
    _ccNodeLoaders:null,

    ctor:function(){
        this._ccNodeLoaders = {};
    },

    registerDefaultCCNodeLoaders:function(){
        this.registerCCNodeLoader("CCNode", cc.NodeLoader.loader());
        this.registerCCNodeLoader("CCLayer", cc.LayerLoader.loader());
        this.registerCCNodeLoader("CCLayerColor", cc.LayerColorLoader.loader());
        this.registerCCNodeLoader("CCLayerGradient", cc.LayerGradientLoader.loader());
        this.registerCCNodeLoader("CCSprite", cc.SpriteLoader.loader());
        this.registerCCNodeLoader("CCLabelBMFont", cc.LabelBMFontLoader.loader());
        this.registerCCNodeLoader("CCLabelTTF", cc.LabelTTFLoader.loader());
        this.registerCCNodeLoader("CCScale9Sprite", cc.Scale9SpriteLoader.loader());
        this.registerCCNodeLoader("CCScrollView", cc.ScrollViewLoader.loader());
        this.registerCCNodeLoader("CCBFile", cc.BuilderFileLoader.loader());
        this.registerCCNodeLoader("CCMenu", cc.MenuLoader.loader());
        this.registerCCNodeLoader("CCMenuItemImage", cc.MenuItemImageLoader.loader());
        this.registerCCNodeLoader("CCControlButton", cc.ControlButtonLoader.loader());
        this.registerCCNodeLoader("CCParticleSystemQuad", cc.ParticleSystemLoader.loader());
    },

    registerCCNodeLoader:function(className,ccNodeLoader){
        this._ccNodeLoaders[className] =  ccNodeLoader;
    },

    unregisterCCNodeLoader:function(className){
        if(this._ccNodeLoaders[className]){
           delete this._ccNodeLoaders[className];
        }
    },

    getCCNodeLoader:function(className){
        if(this._ccNodeLoaders[className])
            return this._ccNodeLoaders[className];
        return null;
    },

    purge:function(releaseCCNodeLoaders){
        if(releaseCCNodeLoaders) {
            for(var className in this._ccNodeLoaders) {
                delete this._ccNodeLoaders[className];
            }
        }
        this._ccNodeLoaders = {};
    }
});

cc.NodeLoaderLibrary.sSharedCCNodeLoaderLibrary = null;
cc.NodeLoaderLibrary.library = function(){
    return new cc.NodeLoaderLibrary();
};

cc.NodeLoaderLibrary.sharedCCNodeLoaderLibrary = function(){
    if(cc.NodeLoaderLibrary.sSharedCCNodeLoaderLibrary == null) {
        cc.NodeLoaderLibrary.sSharedCCNodeLoaderLibrary = new cc.NodeLoaderLibrary();
        cc.NodeLoaderLibrary.sSharedCCNodeLoaderLibrary.registerDefaultCCNodeLoaders();
    }
    return cc.NodeLoaderLibrary.sSharedCCNodeLoaderLibrary;
};

cc.NodeLoaderLibrary.purgeSharedCCNodeLoaderLibrary = function(){
    cc.NodeLoaderLibrary.sSharedCCNodeLoaderLibrary = null;
};

cc.NodeLoaderLibrary.newDefaultCCNodeLoaderLibrary = function(){
    var ccNodeLoaderLibrary = cc.NodeLoaderLibrary.library();
    ccNodeLoaderLibrary.registerDefaultCCNodeLoaders();
    return ccNodeLoaderLibrary;
};



