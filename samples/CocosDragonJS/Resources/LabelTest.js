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
var TAG_LABEL = 1;
var TAG_LABEL_SPRITE_MANAGER = 1;
var TAG_ANIMATION1 = 1;
var TAG_BITMAP_ATLAS1 = 1;
var TAG_BITMAP_ATLAS2 = 2;
var TAG_BITMAP_ATLAS3 = 3;

var TAG_LABEL_SPRITE1 = 660;
var TAG_LABEL_SPRITE12 = 661;
var TAG_LABEL_SPRITE13 = 662;
var TAG_LABEL_SPRITE14 = 663;
var TAG_LABEL_SPRITE15 = 664;
var TAG_LABEL_SPRITE16 = 665;
var TAG_LABEL_SPRITE17 = 666;
var TAG_LABEL_SPRITE18 = 667;

var sceneIdx = -1;

var LabelTestScene = TestScene.extend({
    runThisTest:function () {
        sceneIdx = -1;
        this.addChild(nextLabelTest());
        director.replaceScene(this);
    }
});

var AtlasDemo = cc.Layer.extend({
    ctor:function() {
        cc.associateWithNative( this, cc.Layer );
        this.init();
    },
    init:function() {
        // this._super(cc.c4b(0, 0, 0, 255), cc.c4b(0, 128, 255, 255));
        this._super();
    },
    title:function () {
        return "No title";
    },
    subtitle:function () {
        return "";
    },
    onEnter:function () {
        this._super();

        var s = director.getWinSize();

        var label = cc.LabelTTF.create(this.title(), "Arial", 28);
        this.addChild(label, 1);
        label.setPosition(cc.p(s.width / 2, s.height - 50));

        var strSubtitle = this.subtitle();
        if (strSubtitle) {
            var l = cc.LabelTTF.create(strSubtitle.toString(), "Thonburi", 16);
            this.addChild(l, 1);
            l.setPosition(cc.p(s.width / 2, s.height - 80));
        }

        var item1 = cc.MenuItemImage.create(s_pathB1, s_pathB2, this, this.backCallback);
        var item2 = cc.MenuItemImage.create(s_pathR1, s_pathR2, this, this.restartCallback);
        var item3 = cc.MenuItemImage.create(s_pathF1, s_pathF2, this, this.nextCallback);

        var menu = cc.Menu.create(item1, item2, item3);

        menu.setPosition(cc.p(0,0));
        var cs = item2.getContentSize();
        item1.setPosition( cc.p(winSize.width/2 - cs.width*2, cs.height/2) );
        item2.setPosition( cc.p(winSize.width/2, cs.height/2) );
        item3.setPosition( cc.p(winSize.width/2 + cs.width*2, cs.height/2) );

        this.addChild(menu, 1);
    },
    restartCallback:function (sender) {
        var s = new LabelTestScene();
        s.addChild(restartLabelTest());
        director.replaceScene(s);

    },
    nextCallback:function (sender) {
        var s = new LabelTestScene();
        s.addChild(nextLabelTest());
        director.replaceScene(s);

    },
    backCallback:function (sender) {
        var s = new LabelTestScene();
        s.addChild(previousLabelTest());
        director.replaceScene(s);
    }
});

//------------------------------------------------------------------
//
// Atlas1
//
//------------------------------------------------------------------
var Atlas1 = AtlasDemo.extend({
    textureAtlas:null,
    init:function () {
        this._super();
        this.textureAtlas = cc.TextureAtlas.create(s_atlasTest, 3);

        var s = director.getWinSize();

        //
        // Notice: u,v tex coordinates are inverted
        //
        var quads = [
            new cc.V3F_C4B_T2F_Quad(
                new cc.V3F_C4B_T2F(new cc.Vertex3F(0, 0, 0), cc.c4b(0, 0, 255, 255), new cc.Tex2F(0.0, 1.0)), // bottom left
                new cc.V3F_C4B_T2F(new cc.Vertex3F(s.width, 0, 0), cc.c4b(0, 0, 255, 0), new cc.Tex2F(1.0, 1.0)), // bottom right
                new cc.V3F_C4B_T2F(new cc.Vertex3F(0, s.height, 0), cc.c4b(0, 0, 255, 0), new cc.Tex2F(0.0, 0.0)), // top left
                new cc.V3F_C4B_T2F(new cc.Vertex3F(s.width, s.height, 0), cc.c4b(0, 0, 255, 255), new cc.Tex2F(1.0, 0.0))    // top right
            ),

            new cc.V3F_C4B_T2F_Quad(
                new cc.V3F_C4B_T2F(new cc.Vertex3F(40, 40, 0), cc.c4b(255, 255, 255, 255), new cc.Tex2F(0.0, 0.2)), // bottom left
                new cc.V3F_C4B_T2F(new cc.Vertex3F(120, 80, 0), cc.c4b(255, 0, 0, 255), new cc.Tex2F(0.5, 0.2)), // bottom right
                new cc.V3F_C4B_T2F(new cc.Vertex3F(40, 160, 0), cc.c4b(255, 255, 255, 255), new cc.Tex2F(0.0, 0.0)), // top left
                new cc.V3F_C4B_T2F(new cc.Vertex3F(160, 160, 0), cc.c4b(0, 255, 0, 255), new cc.Tex2F(0.5, 0.0))            // top right
            ),

            new cc.V3F_C4B_T2F_Quad(
                new cc.V3F_C4B_T2F(new cc.Vertex3F(s.width / 2, 40, 0), cc.c4b(255, 0, 0, 255), new cc.Tex2F(0.0, 1.0)), // bottom left
                new cc.V3F_C4B_T2F(new cc.Vertex3F(s.width, 40, 0), cc.c4b(0, 255, 0, 255), new cc.Tex2F(1.0, 1.0)), // bottom right
                new cc.V3F_C4B_T2F(new cc.Vertex3F(s.width / 2 - 50, 200, 0), cc.c4b(0, 0, 255, 255), new cc.Tex2F(0.0, 0.0)), // top left
                new cc.V3F_C4B_T2F(new cc.Vertex3F(s.width, 100, 0), cc.c4b(255, 255, 0, 255), new cc.Tex2F(1.0, 0.0))        // top right
            )

        ];


        for (var i = 0; i < 3; i++) {
            this.textureAtlas.updateQuad(quads[i], i);
        }
    },
    title:function () {
        return "cc.TextureAtlas";
    },
    subtitle:function () {
        return "Manual creation of cc.TextureAtlas";
    },
    draw:function () {
        this._super();
        this.textureAtlas.drawQuads();
    }
});

//------------------------------------------------------------------
//
// LabelAtlasTest
//
//------------------------------------------------------------------
var LabelAtlasTest = AtlasDemo.extend({
    time:null,
    init:function () {
        this._super();
        this.time = 0;

        var label1 = cc.LabelAtlas.create("123 Test", "res/fonts/tuffy_bold_italic-charmap.plist");
        this.addChild(label1, 0, TAG_LABEL_SPRITE1);
        label1.setPosition(cc.p(10, 100));
        label1.setOpacity(200);

        var label2 = cc.LabelAtlas.create("0123456789", "res/fonts/tuffy_bold_italic-charmap.plist");
        this.addChild(label2, 0, TAG_LABEL_SPRITE12);
        label2.setPosition(cc.p(10, 200));
        label2.setOpacity(32);

        this.schedule(this.step);
    },
    step:function (dt) {
        this.time += dt;

        var label1 = this.getChildByTag(TAG_LABEL_SPRITE1);
        var string1 = this.time.toFixed(2) + " Test";
        label1.setString(string1);

        var label2 = this.getChildByTag(TAG_LABEL_SPRITE12);
        var string2 = parseInt(this.time,10).toString();
        label2.setString(string2);
    },
    title:function () {
        return "LabelAtlas";
    },
    subtitle:function () {
        return "Updating label should be fast";
    }
});

//------------------------------------------------------------------
//
// LabelAtlasColorTest
//
//------------------------------------------------------------------
var LabelAtlasColorTest = AtlasDemo.extend({
    time:null,
    init:function () {
        this._super();
        var label1 = cc.LabelAtlas.create("123 Test", "res/fonts/tuffy_bold_italic-charmap.png", 48, 64, ' '.charCodeAt(0));
        this.addChild(label1, 0, TAG_LABEL_SPRITE1);
        label1.setPosition(cc.p(10, 100));
        label1.setOpacity(200);

        var label2 = cc.LabelAtlas.create("0123456789", "res/fonts/tuffy_bold_italic-charmap.png", 48, 64, ' '.charCodeAt(0));
        this.addChild(label2, 0, TAG_LABEL_SPRITE12);
        label2.setPosition(cc.p(10, 200));
        label2.setColor(cc.c3b(255,0,0));

        var fade = cc.FadeOut.create(1.0);
        var fade_in = fade.reverse();
        var seq = cc.Sequence.create(fade, fade_in);
        var repeat = cc.RepeatForever.create(seq);
        label2.runAction(repeat);

        this.time = 0;

        this.schedule(this.step);
    },
    step:function (dt) {
        this.time += dt;
        var string1 = this.time.toFixed(2) + " Test";
        var label1 = this.getChildByTag(TAG_LABEL_SPRITE1);
        label1.setString(string1);

        var label2 = this.getChildByTag(TAG_LABEL_SPRITE12);
        var string2 = parseInt(this.time,10).toString();
        label2.setString(string2);
    },
    title:function () {
        return "cc.LabelAtlas";
    },
    subtitle:function () {
        return "Opacity + Color should work at the same time";
    }
});

//------------------------------------------------------------------
//
// Atlas3
//
// Use any of these editors to generate BMFonts:
//
//------------------------------------------------------------------
var Atlas3 = AtlasDemo.extend({
    time:0,
    init:function () {
        this._super();
        var col = cc.LayerColor.create(cc.c4b(128, 128, 128, 255));
        this.addChild(col, -10);

        var label1 = cc.LabelBMFont.create("Test", "res/fonts/bitmapFontTest2.fnt");

        // testing anchors
        label1.setAnchorPoint(cc.p(0, 0));
        this.addChild(label1, 0, TAG_BITMAP_ATLAS1);
        var fade = cc.FadeOut.create(1.0);
        var fade_in = fade.reverse();
        var seq = cc.Sequence.create(fade, fade_in);
        var repeat = cc.RepeatForever.create(seq);
        label1.runAction(repeat);

        // VERY IMPORTANT
        // color and opacity work OK because bitmapFontAltas2 loads a BMP image (not a PNG image)
        // If you want to use both opacity and color, it is recommended to use NON premultiplied images like BMP images
        // Of course, you can also tell XCode not to compress PNG images, but I think it doesn't work as expected
        var label2 = cc.LabelBMFont.create("Test", "res/fonts/bitmapFontTest2.fnt");
        // testing anchors
        label2.setAnchorPoint(cc.p(0.5, 0.5));
        label2.setColor(cc.c3b(255,0,0));
        this.addChild(label2, 0, TAG_BITMAP_ATLAS2);
        label2.runAction(repeat.copy());

        var label3 = cc.LabelBMFont.create("Test", "res/fonts/bitmapFontTest.fnt");
        // testing anchors
        label3.setAnchorPoint(cc.p(1, 1));
        this.addChild(label3, 0, TAG_BITMAP_ATLAS3);

        var s = director.getWinSize();
        label1.setPosition(cc.p(0, 0));
        label2.setPosition(cc.p(s.width / 2, s.height / 2));
        label3.setPosition(cc.p(s.width, s.height));

        this.schedule(this.step);
    },
    step:function (dt) {
        this.time += dt;
        //var string;
        var string = this.time.toFixed(2) + "Test j";

        var label1 = this.getChildByTag(TAG_BITMAP_ATLAS1);
        label1.setString(string);

        var label2 = this.getChildByTag(TAG_BITMAP_ATLAS2);
        label2.setString(string);

        var label3 = this.getChildByTag(TAG_BITMAP_ATLAS3);
        label3.setString(string);
    },

    title:function () {
        return "cc.LabelBMFont";
    },
    subtitle:function () {
        return "Testing alignment. Testing opacity + tint";
    }
});

//------------------------------------------------------------------
//
// Atlas4
//
// Use any of these editors to generate BMFonts:
//
//------------------------------------------------------------------
var Atlas4 = AtlasDemo.extend({
    time:null,
    init:function () {
        this._super();
        this.time = 0;

        // Upper Label
        var label = cc.LabelBMFont.create("Bitmap Font Atlas", "res/fonts/bitmapFontTest.fnt");
        this.addChild(label);

        var s = director.getWinSize();

        label.setPosition(cc.p(s.width / 2, s.height / 2));
        label.setAnchorPoint(cc.p(0.5, 0.5));

        var BChar = label.getChildByTag(0);
        var FChar = label.getChildByTag(7);
        var AChar = label.getChildByTag(12);

        var rotate = cc.RotateBy.create(2, 360);
        var rot_4ever = cc.RepeatForever.create(rotate);

        var scale = cc.ScaleBy.create(2, 1.5);
        var scale_back = scale.reverse();
        var scale_seq = cc.Sequence.create(scale, scale_back);
        var scale_4ever = cc.RepeatForever.create(scale_seq);

        var jump = cc.JumpBy.create(0.5, cc.p(0,0), 60, 1);
        var jump_4ever = cc.RepeatForever.create(jump);

        var fade_out = cc.FadeOut.create(1);
        var fade_in = cc.FadeIn.create(1);
        var seq = cc.Sequence.create(fade_out, fade_in);
        var fade_4ever = cc.RepeatForever.create(seq);

        BChar.runAction(rot_4ever);
        BChar.runAction(scale_4ever);
        FChar.runAction(jump_4ever);
        AChar.runAction(fade_4ever);

        // Bottom Label
        var label2 = cc.LabelBMFont.create("00.0", "res/fonts/bitmapFontTest.fnt");
        this.addChild(label2, 0, TAG_BITMAP_ATLAS2);
        label2.setPosition(cc.p(s.width / 2.0, 80));

        var lastChar = label2.getChildByTag(3);
        lastChar.runAction(rot_4ever.copy());

        this.schedule(this.step, 0.1);
    },
    step:function (dt) {
        this.time += dt;
        var string = this.time.toFixed(1);
        string = (string < 10) ? "0" + string : string;
        var label1 = this.getChildByTag(TAG_BITMAP_ATLAS2);
        label1.setString(string);
    },
    draw:function () {
        var s = director.getWinSize();
        var c = cc.c3b(255,0,0);
        cc.renderContext.strokeStyle = "rgba(" + c.r + "," + c.g + "," + c.b + ",1)";
        cc.drawingUtil.drawLine(cc.p(0, s.height / 2), cc.p(s.width, s.height / 2));
        cc.drawingUtil.drawLine(cc.p(s.width / 2, 0), cc.p(s.width / 2, s.height));
    },
    title:function () {
        return "cc.LabelBMFont";
    },
    subtitle:function () {
        return "Using fonts as cc.Sprite objects. Some characters should rotate.";
    }
});

//------------------------------------------------------------------
//
// Atlas5
//
// Use any of these editors to generate BMFonts:
//
//
//------------------------------------------------------------------
var Atlas5 = AtlasDemo.extend({
    init:function () {
        this._super();
        var label = cc.LabelBMFont.create("abcdefg", "res/fonts/bitmapFontTest4.fnt");
        this.addChild(label);

        var s = director.getWinSize();

        label.setPosition(cc.p(s.width / 2, s.height / 2));
        label.setAnchorPoint(cc.p(0.5, 0.5));
    },
    title:function () {
        return "cc.LabelBMFont";
    },
    subtitle:function () {
        return "Testing padding";
    }
});

//------------------------------------------------------------------
//
// Atlas6
//
// Use any of these editors to generate BMFonts:
//
//------------------------------------------------------------------
var Atlas6 = AtlasDemo.extend({
    init:function () {
        this._super();
        var s = director.getWinSize();

        var label = null;
        label = cc.LabelBMFont.create("FaFeFiFoFu", "res/fonts/bitmapFontTest5.fnt");
        this.addChild(label);
        label.setPosition(cc.p(s.width / 2, s.height / 2 + 50));
        label.setAnchorPoint(cc.p(0.5, 0.5));

        label = cc.LabelBMFont.create("fafefifofu", "res/fonts/bitmapFontTest5.fnt");
        this.addChild(label);
        label.setPosition(cc.p(s.width / 2, s.height / 2));
        label.setAnchorPoint(cc.p(0.5, 0.5));

        label = cc.LabelBMFont.create("aeiou", "res/fonts/bitmapFontTest5.fnt");
        this.addChild(label);
        label.setPosition(cc.p(s.width / 2, s.height / 2 - 50));
        label.setAnchorPoint(cc.p(0.5, 0.5));
    },
    title:function () {
        return "cc.LabelBMFont";
    },
    subtitle:function () {
        return "Rendering should be OK. Testing offset";
    }
});

//------------------------------------------------------------------
//
// AtlasBitmapColor
//
// Use any of these editors to generate BMFonts:
//
//------------------------------------------------------------------
var AtlasBitmapColor = AtlasDemo.extend({
    init:function () {
        this._super();
        var s = director.getWinSize();

        var label = null;
        label = cc.LabelBMFont.create("Blue", "res/fonts/bitmapFontTest5.fnt");
        label.setColor(cc.c3b(0,0,255));
        this.addChild(label);
        label.setPosition(cc.p(s.width / 2, s.height / 4));
        label.setAnchorPoint(cc.p(0.5, 0.5));

        label = cc.LabelBMFont.create("Red", "res/fonts/bitmapFontTest5.fnt");
        this.addChild(label);
        label.setPosition(cc.p(s.width / 2, 2 * s.height / 4));
        label.setAnchorPoint(cc.p(0.5, 0.5));
        label.setColor(cc.c3b(255,0,0));

        label = cc.LabelBMFont.create("G", "res/fonts/bitmapFontTest5.fnt");
        this.addChild(label);
        label.setPosition(cc.p(s.width / 2, 3 * s.height / 4));
        label.setAnchorPoint(cc.p(0.5, 0.5));
        label.setColor(cc.c3b(0,255,0));
        label.setString("Green");
    },
    title:function () {
        return "cc.LabelBMFont";
    },
    subtitle:function () {
        return "Testing color";
    }
});

//------------------------------------------------------------------
//
// AtlasFastBitmap
//
// Use any of these editors to generate BMFonts:
//
//------------------------------------------------------------------
var AtlasFastBitmap = AtlasDemo.extend({
    init:function () {
        this._super();
        // Upper Label
        for (var i = 0; i < 100; i++) {
            var str = "-" + i + "-";
            var label = cc.LabelBMFont.create(str, "res/fonts/bitmapFontTest.fnt");
            this.addChild(label);

            var s = director.getWinSize();

            var p = cc.p(Math.random() * s.width, Math.random() * s.height);
            label.setPosition(p);
            label.setAnchorPoint(cc.p(0.5, 0.5));
        }
    },
    title:function () {
        return "cc.LabelBMFont";
    },
    subtitle:function () {
        return "Creating several cc.LabelBMFont with the same .fnt file should be fast";
    }
});
//------------------------------------------------------------------
//
// BitmapFontMultiLine
//
// Use any of these editors to generate BMFonts:
//
//------------------------------------------------------------------
var BitmapFontMultiLine = AtlasDemo.extend({
    init:function () {
        this._super();
        var s;

        // Left
        var label1 = cc.LabelBMFont.create("Multi line\nLeft", "res/fonts/bitmapFontTest3.fnt");
        label1.setAnchorPoint(cc.p(0, 0));
        this.addChild(label1, 0, TAG_BITMAP_ATLAS1);

        s = label1.getContentSize();
        cc.log("content size:" + s.width + "," + s.height);


        // Center
        var label2 = cc.LabelBMFont.create("Multi line\nCenter", "res/fonts/bitmapFontTest3.fnt");
        label2.setAnchorPoint(cc.p(0.5, 0.5));
        this.addChild(label2, 0, TAG_BITMAP_ATLAS2);

        s = label2.getContentSize();
        cc.log("content size:" + s.width + "," + s.height);

        // right
        var label3 = cc.LabelBMFont.create("Multi line\nRight\nThree lines Three", "res/fonts/bitmapFontTest3.fnt");
        label3.setAnchorPoint(cc.p(1, 1));
        this.addChild(label3, 0, TAG_BITMAP_ATLAS3);

        s = label3.getContentSize();
        cc.log("content size:" + s.width + "," + s.height);

        s = director.getWinSize();
        label1.setPosition(cc.p(0, 0));
        label2.setPosition(cc.p(s.width / 2, s.height / 2));
        label3.setPosition(cc.p(s.width, s.height));
    },
    title:function () {
        return "cc.LabelBMFont";
    },
    subtitle:function () {
        return "Multiline + anchor point";
    }
});

//------------------------------------------------------------------
//
// LabelsEmpty
//
//------------------------------------------------------------------
var LabelsEmpty = AtlasDemo.extend({
    setEmpty:null,
    init:function () {
        this._super();


        // cc.LabelBMFont
        var label1 = cc.LabelBMFont.create("", "res/fonts/bitmapFontTest3.fnt");
        this.addChild(label1, 0, TAG_BITMAP_ATLAS1);
        label1.setPosition(winSize.width / 2, winSize.height - 100);

        // cc.LabelTTF
        var label2 = cc.LabelTTF.create("", "Arial", 24);
        this.addChild(label2, 0, TAG_BITMAP_ATLAS2);
        label2.setPosition(winSize.width / 2, winSize.height / 2);

        // cc.LabelAtlas
        var label3 = cc.LabelAtlas.create("", "res/fonts/tuffy_bold_italic-charmap.png", 48, 64, ' '.charCodeAt(0));
        this.addChild(label3, 0, TAG_BITMAP_ATLAS3);
        label3.setPosition(winSize.width / 2, 0 + 100);

        this.schedule(this.onUpdateStrings, 1.0);

        this.setEmpty = false;
    },
    onUpdateStrings:function (dt) {
        var label1 = this.getChildByTag(TAG_BITMAP_ATLAS1);
        var label2 = this.getChildByTag(TAG_BITMAP_ATLAS2);
        var label3 = this.getChildByTag(TAG_BITMAP_ATLAS3);

        if (!this.setEmpty) {
            label1.setString("not empty");
            label2.setString("not empty");
            label3.setString("hi");

            this.setEmpty = true;
        }
        else {
            label1.setString("");
            label2.setString("");
            label3.setString("");

            this.setEmpty = false;
        }
    },
    title:function () {
        return "Testing empty labels";
    },
    subtitle:function () {
        return "3 empty labels: LabelAtlas, LabelTTF and LabelBMFont";
    }
});

//------------------------------------------------------------------
//
// LabelBMFontHD
//
//------------------------------------------------------------------
var LabelBMFontHD = AtlasDemo.extend({
    init:function () {
        this._super();
        var s = director.getWinSize();

        // cc.LabelBMFont
        var label1 = cc.LabelBMFont.create("TESTING RETINA DISPLAY", "res/fonts/konqa32.fnt");
        this.addChild(label1);
        label1.setPosition(cc.p(s.width / 2, s.height / 2));
    },
    title:function () {
        return "Testing Retina Display BMFont";
    },
    subtitle:function () {
        return "loading arista16 or arista16-hd";
    }
});

//------------------------------------------------------------------
//
// LabelAtlasHD
//
//------------------------------------------------------------------
var LabelAtlasHD = AtlasDemo.extend({
    init:function () {
        this._super();
        var s = director.getWinSize();

        // cc.LabelBMFont
        var label1 = cc.LabelAtlas.create("TESTING RETINA DISPLAY", "res/fonts/larabie-16.plist");
        label1.setAnchorPoint(cc.p(0.5, 0.5));

        this.addChild(label1);
        label1.setPosition(cc.p(s.width / 2, s.height / 2));
    },
    title:function () {
        return "LabelAtlas with Retina Display";
    },
    subtitle:function () {
        return "loading larabie-16 / larabie-16-hd";
    }
});

//------------------------------------------------------------------
//
// LabelGlyphDesigner
//
//------------------------------------------------------------------
var LabelGlyphDesigner = AtlasDemo.extend({
    init:function () {
        this._super();
        var s = director.getWinSize();

        var layer = cc.LayerColor.create(cc.c4b(128, 128, 128, 255));
        this.addChild(layer, -10);

        // cc.LabelBMFont
        var label1 = cc.LabelBMFont.create("Testing Glyph Designer", "res/fonts/futura-48.fnt");
        this.addChild(label1);
        label1.setPosition(cc.p(s.width / 2, s.height / 2));
    },
    title:function () {
        return "Testing Glyph Designer";
    },
    subtitle:function () {
        return "You should see a font with shawdows and outline";
    }
});

//------------------------------------------------------------------
//
// LabelTTFTest
//
//------------------------------------------------------------------
var LabelTTFTest = AtlasDemo.extend({
    _label:null,
    _horizAlign:null,
    _vertAlign:null,
    init:function () {
        this._super();
        var blockSize = cc.size(200, 160);
        var s = director.getWinSize();

        var colorLayer = cc.LayerColor.create(cc.c4b(100, 100, 100, 255), blockSize.width, blockSize.height);
        colorLayer.setAnchorPoint(cc.p(0, 0));
        colorLayer.setPosition(cc.p((s.width - blockSize.width) / 2, (s.height - blockSize.height) / 2));

        this.addChild(colorLayer);

        cc.MenuItemFont.setFontSize(30);
        var menu = cc.Menu.create(
            cc.MenuItemFont.create("Left", this, this.setAlignmentLeft),
            cc.MenuItemFont.create("Center", this, this.setAlignmentCenter),
            cc.MenuItemFont.create("Right", this, this.setAlignmentRight));
        menu.alignItemsVerticallyWithPadding(4);
        menu.setPosition(cc.p(50, s.height / 2 - 20));
        this.addChild(menu);

        menu = cc.Menu.create(
            cc.MenuItemFont.create("Top", this, this.setAlignmentTop),
            cc.MenuItemFont.create("Middle", this, this.setAlignmentMiddle),
            cc.MenuItemFont.create("Bottom", this, this.setAlignmentBottom));
        menu.alignItemsVerticallyWithPadding(4);
        menu.setPosition(cc.p(s.width - 50, s.height / 2 - 20));
        this.addChild(menu);

        this._label = null;
        this._horizAlign = cc.TEXT_ALIGNMENT_LEFT;
        this._vertAlign = cc.VERTICAL_TEXT_ALIGNMENT_TOP;

        this.updateAlignment();
    },
    updateAlignment:function () {
        var blockSize = cc.size(200, 160);
        var s = director.getWinSize();

        if (this._label) {
            this._label.removeFromParentAndCleanup(true);
        }

        this._label = cc.LabelTTF.create(this.getCurrentAlignment(), "Arial", 32, blockSize, this._horizAlign, this._vertAlign);

        this._label.setAnchorPoint(cc.p(0, 0));
        this._label.setPosition(cc.p((s.width - blockSize.width) / 2, (s.height - blockSize.height) / 2));

        this.addChild(this._label);
    },
    setAlignmentLeft:function (sender) {
        this._horizAlign = cc.TEXT_ALIGNMENT_LEFT;
        this.updateAlignment();
    },
    setAlignmentCenter:function (sender) {
        this._horizAlign = cc.TEXT_ALIGNMENT_CENTER;
        this.updateAlignment();
    },
    setAlignmentRight:function (sender) {
        this._horizAlign = cc.TEXT_ALIGNMENT_RIGHT;
        this.updateAlignment();
    },
    setAlignmentTop:function (sender) {
        this._vertAlign = cc.VERTICAL_TEXT_ALIGNMENT_TOP;
        this.updateAlignment();
    },
    setAlignmentMiddle:function (sender) {
        this._vertAlign = cc.VERTICAL_TEXT_ALIGNMENT_CENTER;
        this.updateAlignment();
    },
    setAlignmentBottom:function (sender) {
        this._vertAlign = cc.VERTICAL_TEXT_ALIGNMENT_BOTTOM;
        this.updateAlignment();
    },
    getCurrentAlignment:function () {
        var vertical = null;
        var horizontal = null;
        switch (this._vertAlign) {
            case cc.VERTICAL_TEXT_ALIGNMENT_TOP:
                vertical = "Top";
                break;
            case cc.VERTICAL_TEXT_ALIGNMENT_CENTER:
                vertical = "Middle";
                break;
            case cc.VERTICAL_TEXT_ALIGNMENT_BOTTOM:
                vertical = "Bottom";
                break;
        }
        switch (this._horizAlign) {
            case cc.TEXT_ALIGNMENT_LEFT:
                horizontal = "Left";
                break;
            case cc.TEXT_ALIGNMENT_CENTER:
                horizontal = "Center";
                break;
            case cc.TEXT_ALIGNMENT_RIGHT:
                horizontal = "Right";
                break;
        }

        return "Alignment " + vertical + " " + horizontal;
    },
    title:function () {
        return "Testing cc.LabelTTF";
    },
    subtitle:function () {
        return "Select the buttons on the sides to change alignment";
    }
});

var LabelTTFMultiline = AtlasDemo.extend({
    init:function () {
        this._super();
        var s = director.getWinSize();

        // cc.LabelBMFont
        var center = cc.LabelTTF.create("word wrap \"testing\" (bla0) bla1 'bla2' [bla3] (bla4) {bla5} {bla6} [bla7] (bla8) [bla9] 'bla0' \"bla1\"",
            "Arial", 32, cc.size(s.width / 2, 200), cc.TEXT_ALIGNMENT_CENTER, cc.VERTICAL_TEXT_ALIGNMENT_TOP);
        center.setPosition(cc.p(s.width / 2, 150));

        this.addChild(center);
    },
    title:function () {
        return "Testing cc.LabelTTF Word Wrap";
    },
    subtitle:function () {
        return "Word wrap using cc.LabelTTF";
    }
});

var LabelTTFChinese = AtlasDemo.extend({
    init:function () {
        this._super();
        var size = director.getWinSize();
        var label = cc.LabelTTF.create("中国", "Microsoft Yahei", 30);
        label.setPosition(cc.p(size.width / 2, size.height / 2));
        this.addChild(label);
    },
    title:function () {
        return "Testing cc.LabelTTF with Chinese character";
    }
});

var LabelBMFontChinese = AtlasDemo.extend({
    init:function () {
        this._super();
        var size = director.getWinSize();
        var label = cc.LabelBMFont.create("中国", "res/fonts/bitmapFontChinese.fnt");
        label.setPosition(cc.p(size.width / 2, size.height / 2));
        this.addChild(label);
    },
    title:function () {
        return "Testing cc.LabelBMFont with Chinese character";
    }
});

var LongSentencesExample = "Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.";
var LineBreaksExample = "Lorem ipsum dolor\nsit amet\nconsectetur adipisicing elit\nblah\nblah";
var MixedExample = "ABC\nLorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt\nDEF";

var ArrowsMax = 0.95;
var ArrowsMin = 0.7;

var LeftAlign = 0;
var CenterAlign = 1;
var RightAlign = 2;

var LongSentences = 0;
var LineBreaks = 1;
var Mixed = 2;

var alignmentItemPadding = 50;
var menuItemPaddingCenter = 50;

var BitmapFontMultiLineAlignment = AtlasDemo.extend({
    labelShouldRetain:null,
    arrowsBarShouldRetain:null,
    arrowsShouldRetain:null,
    lastSentenceItem:null,
    lastAlignmentItem:null,
    drag:null,
    init:function () {
        this._super();

        var t = cc.config.deviceType;
        if( t == 'browser' )  {
            this.setTouchEnabled(true);
            // this.setKeyboardEnabled(true);
        } else if( t == 'desktop' ) {
            this.setMouseEnabled(true);
        } else if( t == 'mobile' ) {
            this.setTouchEnabled(true);
        }

        // ask director the the window size
        var size = director.getWinSize();

        // create and initialize a Label
        this.labelShouldRetain = cc.LabelBMFont.create(LongSentencesExample, "res/fonts/markerFelt.fnt", size.width / 2, cc.TEXT_ALIGNMENT_CENTER, cc.p(0,0));
        this.arrowsBarShouldRetain = cc.Sprite.create("res/Images/arrowsBar.png");
        this.arrowsShouldRetain = cc.Sprite.create("res/Images/arrows.png");

        cc.MenuItemFont.setFontSize(20);
        var longSentences = cc.MenuItemFont.create("Long Flowing Sentences", this, this.stringChanged);
        var lineBreaks = cc.MenuItemFont.create("Short Sentences With Intentional Line Breaks", this, this.stringChanged);
        var mixed = cc.MenuItemFont.create("Long Sentences Mixed With Intentional Line Breaks", this, this.stringChanged);
        var stringMenu = cc.Menu.create(longSentences, lineBreaks, mixed);
        stringMenu.alignItemsVertically();

        longSentences.setColor(cc.c3b(255,0,0));
        this.lastSentenceItem = longSentences;
        longSentences.setTag(LongSentences);
        lineBreaks.setTag(LineBreaks);
        mixed.setTag(Mixed);

        cc.MenuItemFont.setFontSize(30);

        var left = cc.MenuItemFont.create("Left", this, this.alignmentChanged);
        var center = cc.MenuItemFont.create("Center", this, this.alignmentChanged);
        var right = cc.MenuItemFont.create("Right", this, this.alignmentChanged);
        var alignmentMenu = cc.Menu.create(left, center, right);
        alignmentMenu.alignItemsHorizontallyWithPadding(alignmentItemPadding);

        center.setColor(cc.c3b(255,0,0));
        this.lastAlignmentItem = center;
        left.setTag(LeftAlign);
        center.setTag(CenterAlign);
        right.setTag(RightAlign);

        // position the label on the center of the screen
        this.labelShouldRetain.setPosition(cc.p(size.width / 2, size.height / 2));

        this.arrowsBarShouldRetain.setVisible(false);

        var arrowsWidth = (ArrowsMax - ArrowsMin) * size.width;
        this.arrowsBarShouldRetain.setScaleX(arrowsWidth / this.arrowsBarShouldRetain.getContentSize().width);
        this.arrowsBarShouldRetain.setPosition(cc.p(((ArrowsMax + ArrowsMin) / 2) * size.width, this.labelShouldRetain.getPosition().y));

        this.snapArrowsToEdge();

        stringMenu.setPosition(cc.p(size.width / 2, size.height - menuItemPaddingCenter));
        alignmentMenu.setPosition(cc.p(size.width / 2, menuItemPaddingCenter + 15));

        this.addChild(this.labelShouldRetain);
        this.addChild(this.arrowsBarShouldRetain);
        this.addChild(this.arrowsShouldRetain);
        this.addChild(stringMenu);
        this.addChild(alignmentMenu);
    },
    title:function () {
        return "";
    },
    subtitle:function () {
        return "";
    },
    stringChanged:function (sender) {
        sender.setColor(cc.c3b(255,0,0));
        this.lastSentenceItem.setColor(cc.c3b(255,255,255));
        this.lastSentenceItem = sender;

        switch (sender.getTag()) {
            case LongSentences:
                this.labelShouldRetain.setString(LongSentencesExample);
                break;
            case LineBreaks:
                this.labelShouldRetain.setString(LineBreaksExample);
                break;
            case Mixed:
                this.labelShouldRetain.setString(MixedExample);
                break;

            default:
                break;
        }

        this.snapArrowsToEdge();
    },
    alignmentChanged:function (sender) {
        var item = sender;
        item.setColor(cc.c3b(255,0,0));
        this.lastAlignmentItem.setColor(cc.c3b(255,255,255));
        this.lastAlignmentItem = item;

        switch (item.getTag()) {
            case LeftAlign:
                this.labelShouldRetain.setAlignment(cc.TEXT_ALIGNMENT_LEFT);
                break;
            case CenterAlign:
                this.labelShouldRetain.setAlignment(cc.TEXT_ALIGNMENT_CENTER);
                break;
            case RightAlign:
                this.labelShouldRetain.setAlignment(cc.TEXT_ALIGNMENT_RIGHT);
                break;

            default:
                break;
        }

        this.snapArrowsToEdge();
    },
    onTouchesBegan:function (touches) {
        var touch = touches[0];
        var location = touch.getLocation();

        if (cc.Rect.CCRectContainsPoint(this.arrowsShouldRetain.getBoundingBox(), location)) {
            this.drag = true;
            this.arrowsBarShouldRetain.setVisible(true);
        }
    },
    onTouchesEnded:function () {
        this.drag = false;
        this.snapArrowsToEdge();
        this.arrowsBarShouldRetain.setVisible(false);
    },
    onTouchesMoved:function (touches) {
        if (!this.drag) {
            return;
        }

        var touch = touches[0];
        var location = touch.getLocation();

        var winSize = director.getWinSize();

        this.arrowsShouldRetain.setPosition(cc.p(Math.max(Math.min(location.x, ArrowsMax * winSize.width), ArrowsMin * winSize.width),
            this.arrowsShouldRetain.getPosition().y));

        var labelWidth = Math.abs(this.arrowsShouldRetain.getPosition().x - this.labelShouldRetain.getPosition().x) * 2;

        this.labelShouldRetain.setWidth(labelWidth);
    },
    snapArrowsToEdge:function () {
        this.arrowsShouldRetain.setPosition(cc.p(this.labelShouldRetain.getPosition().x + this.labelShouldRetain.getContentSize().width / 2,
            this.labelShouldRetain.getPosition().y));
    }
});

/// LabelTTFA8Test
var LabelTTFA8Test = AtlasDemo.extend({
    init:function () {
        this._super();
        var s = director.getWinSize();

        var layer = cc.LayerColor.create(cc.c4b(128, 128, 128, 255));
        this.addChild(layer, -10);

        // cc.LabelBMFont
        var label1 = cc.LabelTTF.create("Testing A8 Format", "Arial", 48);
        this.addChild(label1);
        label1.setColor(cc.c3b(255,0,0));
        label1.setPosition(cc.p(s.width / 2, s.height / 2));

        var fadeOut = cc.FadeOut.create(2);
        var fadeIn = cc.FadeIn.create(2);
        var seq = cc.Sequence.create(fadeOut, fadeIn);
        var forever = cc.RepeatForever.create(seq);
        label1.runAction(forever);
    },
    title:function () {
        return "Testing A8 Format";
    },
    subtitle:function () {
        return "RED label, fading In and Out in the center of the screen";
    }
});

/// BMFontOneAtlas
var BMFontOneAtlas = AtlasDemo.extend({
    init:function () {
        this._super();
        var s = director.getWinSize();

        var label1 = cc.LabelBMFont.create("This is Helvetica", "res/fonts/helvetica-32.fnt", cc.LabelAutomaticWidth, cc.TEXT_ALIGNMENT_LEFT, cc.p(0,0));
        this.addChild(label1);
        label1.setPosition(cc.p(s.width / 2, s.height * 2 / 3));

        var label2 = cc.LabelBMFont.create("And this is Geneva", "res/fonts/geneva-32.fnt", cc.LabelAutomaticWidth, cc.TEXT_ALIGNMENT_LEFT, cc.p(0, 128));
        this.addChild(label2);
        label2.setPosition(cc.p(s.width / 2, s.height / 3));
    },

    title:function () {
        return "cc.LabelBMFont with one texture";
    },

    subtitle:function () {
        return "Using 2 .fnt definitions that share the same texture atlas.";
    }
});

/// BMFontUnicode
var BMFontUnicode = AtlasDemo.extend({
    init:function () {
        this._super();
        var chinese = "美好的一天";
        var japanese = "良い一日を";
        var spanish = "Buen día";

        var label1 = cc.LabelBMFont.create(spanish, "res/fonts/arial-unicode-26.fnt", 200, cc.TEXT_ALIGNMENT_LEFT);
        this.addChild(label1);
        label1.setPosition(winSize.width / 2, winSize.height / 4);

        var label2 = cc.LabelBMFont.create(chinese, "res/fonts/arial-unicode-26.fnt");
        this.addChild(label2);
        label2.setPosition(winSize.width / 2, winSize.height / 2.2);

        var label3 = cc.LabelBMFont.create(japanese, "res/fonts/arial-unicode-26.fnt");
        this.addChild(label3);
        label3.setPosition( winSize.width / 2, winSize.height / 1.5);
    },
    title:function () {
        return "cc.LabelBMFont with Unicode support";
    },
    subtitle:function () {
        return "You should see 3 different labels: In Spanish, Chinese and Korean";
    }
});

// BMFontInit
var BMFontInit = AtlasDemo.extend({
    init:function () {
        this._super();

        var bmFont = cc.LabelBMFont.create();
        bmFont.setFntFile("res/fonts/helvetica-32.fnt");
        bmFont.setString("It is working!");
        this.addChild(bmFont);
        bmFont.setPosition( winSize.width / 2, winSize.height / 2);
    },
    title:function () {
        return "cc.LabelBMFont init";
    },
    subtitle:function () {
        return "Test for support of init method without parameters.";
    }
});

// TTFFontInit
var TTFFontInit = AtlasDemo.extend({
    init:function () {
        this._super();
        var font = cc.LabelTTF.create();
        font.setFontName("Courier New");
        font.setFontSize(48);
        font.setString("It is working!");
        this.addChild(font);
        font.setPosition( winSize.width / 2, winSize.height / 2);
    },
    title:function () {
        return "cc.LabelTTF init";
    },
    subtitle:function () {
        return "Test for support of init method without parameters.";
    }
});


var LabelTTFAlignment = AtlasDemo.extend({
    init:function () {
        this._super();
        var s = director.getWinSize();
        var ttf0 = cc.LabelTTF.create("Alignment 0\nnew line", "Arial", 12, cc.size(256, 32), cc.TEXT_ALIGNMENT_LEFT);
        ttf0.setPosition(cc.p(s.width / 2, (s.height / 6) * 2));
        ttf0.setAnchorPoint(cc.p(0.5, 0.5));
        this.addChild(ttf0);

        var ttf1 = cc.LabelTTF.create("Alignment 1\nnew line", "Arial", 12, cc.size(256, 32), cc.TEXT_ALIGNMENT_CENTER);
        ttf1.setPosition(cc.p(s.width / 2, (s.height / 6) * 3));
        ttf1.setAnchorPoint(cc.p(0.5, 0.5));
        this.addChild(ttf1);

        var ttf2 = cc.LabelTTF.create("Alignment 2\nnew line", "Arial", 12, cc.size(256, 32), cc.TEXT_ALIGNMENT_RIGHT);
        ttf2.setPosition(cc.p(s.width / 2, (s.height / 6) * 4));
        ttf2.setAnchorPoint(cc.p(0.5, 0.5));
        this.addChild(ttf2);
    },
    title:function () {
        return "cc.LabelTTF alignment";
    },
    subtitle:function () {
        return "Tests alignment values";
    }
});

//
// Flow control
//
var arrayOfLabelTest = [
    LabelAtlasTest,
    LabelAtlasColorTest,
    Atlas3,
    Atlas4,
    Atlas5,
    Atlas6,
    AtlasBitmapColor,
    AtlasFastBitmap,
    BitmapFontMultiLine,
    LabelsEmpty,
    LabelBMFontHD,
    LabelAtlasHD,
    LabelGlyphDesigner,
    LabelTTFTest,
    LabelTTFMultiline,
    LabelTTFChinese,
    LabelBMFontChinese,
    BitmapFontMultiLineAlignment,
    LabelTTFA8Test,
    BMFontOneAtlas,
    BMFontUnicode,
    BMFontInit,
    TTFFontInit,
    LabelTTFAlignment
];

var nextLabelTest = function () {
    sceneIdx++;
    sceneIdx = sceneIdx % arrayOfLabelTest.length;

    return new arrayOfLabelTest[sceneIdx]();
};
var previousLabelTest = function () {
    sceneIdx--;
    if (sceneIdx < 0)
        sceneIdx += arrayOfLabelTest.length;

    return new arrayOfLabelTest[sceneIdx]();
};
var restartLabelTest = function () {
    return new arrayOfLabelTest[sceneIdx]();
};
