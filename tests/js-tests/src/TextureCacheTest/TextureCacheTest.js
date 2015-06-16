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

var TextureCacheTestBase = BaseTestLayer.extend({
    _title:"",
    _subtitle:"",

    ctor:function() {
        this._super(cc.color(0,0,0,255), cc.color(98,99,117,255));
    },

    onRestartCallback:function (sender) {
        var s = new TexCacheTestScene();
        s.addChild(restartTexCacheTest());
        director.runScene(s);
    },
    onNextCallback:function (sender) {
        var s = new TexCacheTestScene();
        s.addChild(nextTexCacheTest());
        director.runScene(s);
    },
    onBackCallback:function (sender) {
        var s = new TexCacheTestScene();
        s.addChild(previousTexCacheTest());
        director.runScene(s);
    }
});

var TextureLoadImgTest = TextureCacheTestBase.extend({
    _title: "Load Same Image Twice",
    _labelFirst:null,
    _labelSecond:null,
    ctor: function () {
        this._super();

        if('opengl' in cc.sys.capabilities && !cc.sys.isNative){
            var label = new cc.LabelTTF("Not support Loading texture from remote site on HTML5-WebGL", "Times New Roman", 28);
            label.x = winSize.width / 2;
            label.y = winSize.height / 2;
            this.addChild(label, 100);
            return;
        }

        this._labelFirst = new cc.LabelTTF("load first image");
        this._labelFirst.attr({
            x:cc.winSize.width/2,
            y:cc.winSize.height/2 + 30
        });
        this.addChild(this._labelFirst, 1);


        this._labelSecond = new cc.LabelTTF("load second image");
        this._labelSecond.attr({
            x:cc.winSize.width/2,
            y:cc.winSize.height/2 - 30
        });
        this.addChild(this._labelSecond, 1);

        var url = "http://cn.cocos2d-x.org/image/logo.png";
        cc.textureCache.addImageAsync(url, this.texFirstLoaded, this);
        cc.textureCache.addImageAsync(url, this.texSecondLoaded, this);
    },

    texFirstLoaded: function(texture) {
        if (!texture)
        {
            this._labelFirst.setString("texFirstLoaded fail");
            return;
        }

        if (this.sprite) {
            this.removeChild(this.sprite);
        }
        this.sprite = new cc.Sprite(texture);
        this.sprite.x = cc.winSize.width/2;
        this.sprite.y = cc.winSize.height/2;
        this.addChild(this.sprite);

        this._labelFirst.setString("texFirstLoaded successful");
    },

    texSecondLoaded: function(texture) {

        if (!texture)
        {
            this._labelSecond.setString("texSecondLoaded fail");
            return;
        }

        if (this.sprite2) {
            this.removeChild(this.sprite2);
        }
        this.sprite2 = new cc.Sprite(texture);
        this.sprite2.x = cc.winSize.width/2;
        this.sprite2.y = cc.winSize.height/2 + 70;
        this.addChild(this.sprite2);

        this._labelSecond.setString("texSecondLoaded successful");
    }
});

var TextureCacheTest = TextureCacheTestBase.extend({
    _title:"Texture Cache Loading Test",
    _labelLoading:null,
    _labelPercent:null,
    _numberOfSprites:20,
    _numberOfLoadedSprites:0,
    ctor:function () {
        this._super();

        var size = cc.director.getWinSize();

        this._labelLoading = new cc.LabelTTF("loading...", "Arial", 15);
        this._labelPercent = new cc.LabelTTF("%0", "Arial", 15);

        this._labelLoading.x = size.width / 2;

        this._labelLoading.y = size.height / 2 - 20;
        this._labelPercent.x = size.width / 2;
        this._labelPercent.y = size.height / 2 + 20;

        this.addChild(this._labelLoading);
        this.addChild(this._labelPercent);

        var texCache = cc.textureCache;
        // load textrues
        texCache.addImageAsync("Images/HelloWorld.png", this.loadingCallBack, this);
        texCache.addImageAsync("Images/grossini.png", this.loadingCallBack, this);
        texCache.addImageAsync("Images/grossini_dance_01.png", this.loadingCallBack, this);
        texCache.addImageAsync("Images/grossini_dance_02.png", this.loadingCallBack, this);
        texCache.addImageAsync("Images/grossini_dance_03.png", this.loadingCallBack, this);
        texCache.addImageAsync("Images/grossini_dance_04.png", this.loadingCallBack, this);
        texCache.addImageAsync("Images/grossini_dance_05.png", this.loadingCallBack, this);
        texCache.addImageAsync("Images/grossini_dance_06.png", this.loadingCallBack, this);
        texCache.addImageAsync("Images/grossini_dance_07.png", this.loadingCallBack, this);
        texCache.addImageAsync("Images/grossini_dance_08.png", this.loadingCallBack, this);
        texCache.addImageAsync("Images/grossini_dance_09.png", this.loadingCallBack, this);
        texCache.addImageAsync("Images/grossini_dance_10.png", this.loadingCallBack, this);
        texCache.addImageAsync("Images/grossini_dance_11.png", this.loadingCallBack, this);
        texCache.addImageAsync("Images/grossini_dance_12.png", this.loadingCallBack, this);
        texCache.addImageAsync("Images/grossini_dance_13.png", this.loadingCallBack, this);
        texCache.addImageAsync("Images/grossini_dance_14.png", this.loadingCallBack, this);
        texCache.addImageAsync("Images/background1.png", this.loadingCallBack, this);
        texCache.addImageAsync("Images/background2.png", this.loadingCallBack, this);
        texCache.addImageAsync("Images/background3.png", this.loadingCallBack, this);
        texCache.addImageAsync("Images/blocks.png", this.loadingCallBack, this);
    },
    addSprite:function () {
        var size = cc.director.getWinSize();

        // create sprites
        var bg = new cc.Sprite("Images/HelloWorld.png");
        bg.x = size.width / 2;
        bg.y = size.height / 2;
        //bg.scale = 1.7;

        var s1 = new cc.Sprite("Images/grossini.png");
        var s2 = new cc.Sprite("Images/grossini_dance_01.png");
        var s3 = new cc.Sprite("Images/grossini_dance_02.png");
        var s4 = new cc.Sprite("Images/grossini_dance_03.png");
        var s5 = new cc.Sprite("Images/grossini_dance_04.png");
        var s6 = new cc.Sprite("Images/grossini_dance_05.png");
        var s7 = new cc.Sprite("Images/grossini_dance_06.png");
        var s8 = new cc.Sprite("Images/grossini_dance_07.png");
        var s9 = new cc.Sprite("Images/grossini_dance_08.png");
        var s10 = new cc.Sprite("Images/grossini_dance_09.png");
        var s11 = new cc.Sprite("Images/grossini_dance_10.png");
        var s12 = new cc.Sprite("Images/grossini_dance_11.png");
        var s13 = new cc.Sprite("Images/grossini_dance_12.png");
        var s14 = new cc.Sprite("Images/grossini_dance_13.png");
        var s15 = new cc.Sprite("Images/grossini_dance_14.png");

        // just loading textures to slow down
        var s16 = new cc.Sprite("Images/background1.png");
        var s17 = new cc.Sprite("Images/background2.png");
        var s18 = new cc.Sprite("Images/background3.png");
        var s19 = new cc.Sprite("Images/blocks.png");

        s1.x = 50;
        s1.y = 50;
        s2.x = 60;
        s2.y = 50;
        s3.x = 70;
        s3.y = 50;
        s4.x = 80;
        s4.y = 50;
        s5.x = 90;
        s5.y = 50;
        s6.x = 100;
        s6.y = 50;

        s7.x = 50;
        s7.y = 180;
        s8.x = 60;
        s8.y = 180;
        s9.x = 70;
        s9.y = 180;
        s10.x = 80;
        s10.y = 180;
        s11.x = 90;
        s11.y = 180;
        s12.x = 100;
        s12.y = 180;

        s13.x = 50;
        s13.y = 270;
        s14.x = 60;
        s14.y = 270;
        s15.x = 70;
        s15.y = 270;

        this.addChild(bg);

        this.addChild(s1);
        this.addChild(s2);
        this.addChild(s3);
        this.addChild(s4);
        this.addChild(s5);
        this.addChild(s6);
        this.addChild(s7);
        this.addChild(s8);
        this.addChild(s9);
        this.addChild(s10);
        this.addChild(s11);
        this.addChild(s12);
        this.addChild(s13);
        this.addChild(s14);
        this.addChild(s15);
    },
    loadingCallBack:function (obj) {
        ++this._numberOfLoadedSprites;
        this._labelPercent.setString((this._numberOfLoadedSprites / this._numberOfSprites) * 100 + '');
        if (this._numberOfLoadedSprites == this._numberOfSprites) {
            this.removeChild(this._labelLoading, true);
            this.removeChild(this._labelPercent, true);
            this.addSprite();
        }
    }
});

var RemoteTextureTest = TextureCacheTestBase.extend({
    _title:"Remote Texture Test",
    _subtitle:"",
    _remoteTex: "http://cn.cocos2d-x.org/image/logo.png",
    onEnter:function () {
        this._super();
        if('opengl' in cc.sys.capabilities && !cc.sys.isNative){
            var label = new cc.LabelTTF("Not support Loading texture from remote site on HTML5-WebGL", "Times New Roman", 28);
            label.x = winSize.width / 2;
            label.y = winSize.height / 2;
            this.addChild(label, 100);
        } else
            this.scheduleOnce(this.startDownload, 0.1);
    },

    startDownload: function() {
        var imageUrlArray = ["http://www.cocos2d-x.org/s/upload/v35.jpg", "http://www.cocos2d-x.org/s/upload/testin.jpg", "http://www.cocos2d-x.org/s/upload/geometry_dash.jpg", "http://cn.cocos2d-x.org/image/logo.png"];

        for (var i = 0; i < imageUrlArray.length; i++) {
            cc.textureCache.addImageAsync(imageUrlArray[i], this.texLoaded, this);
        }
    },

    texLoaded: function(texture) {
        if (texture instanceof cc.Texture2D) {
            cc.log("Remote texture loaded");
            
            var sprite = new cc.Sprite(texture);
            sprite.x = cc.winSize.width/2;
            sprite.y = cc.winSize.height/2;
            this.addChild(sprite);
        }
        else {
            cc.log("Fail to load remote texture");
        }
    }
});


//
// Flow control
//

var texCacheTestSceneIdx = -1;

var TexCacheTestScene = TestScene.extend({
    runThisTest:function (num) {
        texCacheTestSceneIdx = (num || num == 0) ? (num - 1) : -1;
        var layer = nextTexCacheTest();
        this.addChild(layer);

        cc.director.runScene(this);
    }
});

var arrayOfTexCacheTest = [
    TextureLoadImgTest,
    TextureCacheTest,
    RemoteTextureTest
];

var nextTexCacheTest = function () {
    texCacheTestSceneIdx++;
    texCacheTestSceneIdx = texCacheTestSceneIdx % arrayOfTexCacheTest.length;

    return new arrayOfTexCacheTest[texCacheTestSceneIdx]();
};
var previousTexCacheTest = function () {
    texCacheTestSceneIdx--;
    if (texCacheTestSceneIdx < 0)
        texCacheTestSceneIdx += arrayOfTexCacheTest.length;

    return new arrayOfTexCacheTest[texCacheTestSceneIdx]();
};
var restartTexCacheTest = function () {
    return new arrayOfTexCacheTest[texCacheTestSceneIdx]();
};

