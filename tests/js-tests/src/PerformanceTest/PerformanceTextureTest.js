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

var s_nTexCurCase = 0;
////////////////////////////////////////////////////////
//
// TextureMenuLayer
//
////////////////////////////////////////////////////////
var TextureMenuLayer = PerformBasicLayer.extend({
    showCurrentTest:function () {
        var scene = null;
        switch (this._curCase) {
            case 0:
                scene = TextureTest.scene();
                break;
        }
        s_nTexCurCase = this._curCase;

        if (scene) {
            cc.director.runScene(scene);
        }
    },

    onEnter:function () {
        this._super();

        var s = cc.director.getWinSize();

        // Title
        var label = new cc.LabelTTF(this.title(), "Arial", 40);
        this.addChild(label, 1);
        label.x = s.width / 2;
        label.y = s.height - 32;
        label.color = cc.color(255, 255, 40);

        // Subtitle
        var strSubTitle = this.subtitle();
        if (strSubTitle.length) {
            var l = new cc.LabelTTF(strSubTitle, "Thonburi", 16);
            this.addChild(l, 1);
            l.x = s.width / 2;
            l.y = s.height - 80;
        }

        this.performTests();
    },
    title:function () {
        return "no title";
    },
    subtitle:function () {
        return "no subtitle";
    },
    performTests:function () {

    }
})

////////////////////////////////////////////////////////
//
// TextureTest
//
////////////////////////////////////////////////////////
var TextureTest = TextureMenuLayer.extend({
    performTests:function () {
        cc.log("--------");
        cc.log("--- PNG 128x128 ---");
        this.performTestsPNG("Images/test_image.png");

        cc.log("--- PNG 512x512 ---");
        this.performTestsPNG("Images/texture512x512.png");

        cc.log("EMPTY IMAGE");
        cc.log("--- PNG 1024x1024 ---");
        this.performTestsPNG("Images/texture1024x1024.png");

        cc.log("LANDSCAPE IMAGE");
        cc.log("--- PNG 1024x1024 ---");
        this.performTestsPNG("Images/landscape-1024x1024.png");
    },
    title:function () {
        return "Texture Performance Test";
    },
    subtitle:function () {
        return "See console for results";
    },
    performTestsPNG:function (filename) {
        var now = Date.now();
        var texture;
        var cache = cc.textureCache;
        if ("opengl" in cc.sys.capabilities)
            var defaultFormat = cc.Texture2D.defaultPixelFormat;
        cc.log("RGBA 8888");
        if ("opengl" in cc.sys.capabilities)
            cc.Texture2D.defaultPixelFormat = cc.Texture2D.PIXEL_FORMAT_RGBA8888;

        var now = Date.now();
        texture = cache.addImage(filename);
        if (texture)
            cc.log("  seconds:" + calculateDeltaTime(now));
        else
            cc.log(" ERROR");
        cache.removeTexture(texture);

        cc.log("RGBA 4444");
        if ("opengl" in cc.sys.capabilities)
            cc.Texture2D.defaultPixelFormat = cc.Texture2D.PIXEL_FORMAT_RGBA4444;

        var now = Date.now();
        texture = cache.addImage(filename);
        if (texture)
            cc.log("  seconds:" + calculateDeltaTime(now));
        else
            cc.log(" ERROR");
        cache.removeTexture(texture);

        cc.log("RGBA 5551");
        if ("opengl" in cc.sys.capabilities)
            cc.Texture2D.defaultPixelFormat = cc.Texture2D.PIXEL_FORMAT_RGB5A1;

        var now = Date.now();
        texture = cache.addImage(filename);
        if (texture)
            cc.log("  seconds:" + calculateDeltaTime(now));
        else
            cc.log(" ERROR");
        cache.removeTexture(texture);

        cc.log("RGB 565");
        if ("opengl" in cc.sys.capabilities)
            cc.Texture2D.defaultPixelFormat = cc.Texture2D.PIXEL_FORMAT_RGB565;

        var now = Date.now();
        texture = cache.addImage(filename);
        if (texture)
            cc.log("  seconds:" + calculateDeltaTime(now));
        else
            cc.log(" ERROR");
        cache.removeTexture(texture);
        if ("opengl" in cc.sys.capabilities)
            cc.Texture2D.defaultPixelFormat = defaultFormat;
    }
});

TextureTest.scene = function () {
    var scene = new cc.Scene();
    var layer = new TextureTest(false, 1, s_nTexCurCase);
    scene.addChild(layer);
    return scene;
};
function runTextureTest() {
    s_nTexCurCase = 0;
    var scene = TextureTest.scene();
    cc.director.runScene(scene);
}

function calculateDeltaTime(lastUpdate) {
    var now = Date.now();
    var dt = (now - lastUpdate) / 1000;
    return dt;
}
