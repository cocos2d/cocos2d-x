/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org
 Copyright (c) 2008-2010 Ricardo Quesada
 Copyright (c) 2011      Zynga Inc.

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
            cc.Director.getInstance().replaceScene(scene);
        }
    },

    onEnter:function () {
        this._super();

        var s = cc.Director.getInstance().getWinSize();

        // Title
        var label = cc.LabelTTF.create(this.title(), "Arial", 40);
        this.addChild(label, 1);
        label.setPosition(cc.p(s.width / 2, s.height - 32));
        label.setColor(cc.c3b(255, 255, 40));

        // Subtitle
        var strSubTitle = this.subtitle();
        if (strSubTitle.length) {
            var l = cc.LabelTTF.create(strSubTitle, "Thonburi", 16);
            this.addChild(l, 1);
            l.setPosition(cc.p(s.width / 2, s.height - 80));
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
        this.performTestsPNG("res/Images/test_image.png");

        cc.log("--- PNG 512x512 ---");
        this.performTestsPNG("res/Images/texture512x512.png");

        cc.log("EMPTY IMAGE");
        cc.log("--- PNG 1024x1024 ---");
        this.performTestsPNG("res/Images/texture1024x1024.png");

        cc.log("LANDSCAPE IMAGE");
        cc.log("--- PNG 1024x1024 ---");
        this.performTestsPNG("res/Images/landscape-1024x1024.png");
    },
    title:function () {
        return "Texture Performance Test";
    },
    subtitle:function () {
        return "See console for results";
    },
    performTestsPNG:function (filename) {
        var now = cc.timeval();
        var texture;
        var cache = cc.TextureCache.getInstance();

        cc.log("RGBA 8888");
        cc.Texture2D.setDefaultAlphaPixelFormat(cc.TEXTURE_2D_PIXEL_FORMAT_RGBA8888);
        var now = cc.Time.gettimeofdayCocos2d();
        texture = cache.addImage(filename);
        if (texture)
            cc.log("  ms:" + calculateDeltaTime(now));
        else
            cc.log(" ERROR");
        cache.removeTexture(texture);

        cc.log("RGBA 4444");
        cc.Texture2D.setDefaultAlphaPixelFormat(cc.TEXTURE_2D_PIXEL_FORMAT_RGBA4444);
        var now = cc.Time.gettimeofdayCocos2d();
        texture = cache.addImage(filename);
        if (texture)
            cc.log("  ms:" + calculateDeltaTime(now));
        else
            cc.log(" ERROR");
        cache.removeTexture(texture);

        cc.log("RGBA 5551");
        cc.Texture2D.setDefaultAlphaPixelFormat(cc.TEXTURE_2D_PIXEL_FORMAT_RGB5A1);
        var now = cc.Time.gettimeofdayCocos2d();
        texture = cache.addImage(filename);
        if (texture)
            cc.log("  ms:" + calculateDeltaTime(now));
        else
            cc.log(" ERROR");
        cache.removeTexture(texture);

        cc.log("RGB 565");
        cc.Texture2D.setDefaultAlphaPixelFormat(cc.TEXTURE_2D_PIXEL_FORMAT_RGB565);
        var now = cc.Time.gettimeofdayCocos2d();
        texture = cache.addImage(filename);
        if (texture)
            cc.log("  ms:" + calculateDeltaTime(now));
        else
            cc.log(" ERROR");
        cache.removeTexture(texture);
    }
});

TextureTest.scene = function () {
    var scene = cc.Scene.create();
    var layer = new TextureTest(false, 1, s_nTexCurCase);
    scene.addChild(layer);
    return scene;
};
function runTextureTest() {
    s_nTexCurCase = 0;
    var scene = TextureTest.scene();
    cc.Director.getInstance().replaceScene(scene);
}

function calculateDeltaTime(lastUpdate) {
    var now = cc.Time.gettimeofdayCocos2d();
    var dt = (now.tv_sec - lastUpdate.tv_sec) + (now.tv_usec - lastUpdate.tv_usec) / 1000000.0;
    return dt;
}
