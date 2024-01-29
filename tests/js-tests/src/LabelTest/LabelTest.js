/****************************************************************************
 Copyright (c) 2008-2010 Ricardo Quesada
 Copyright (c) 2011-2012 cocos2d-x.org
 Copyright (c) 2013-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

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

var labelTestIdx = -1;

var LabelTestScene = TestScene.extend({
    runThisTest:function (num) {
        labelTestIdx = (num || num == 0) ? (num - 1) : -1;
        this.addChild(nextLabelTest());
        director.runScene(this);
    }
});

var AtlasDemo = BaseTestLayer.extend({

    title:function () {
        return "No title";
    },
    subtitle:function () {
        return "";
    },
    onRestartCallback:function (sender) {
        var s = new LabelTestScene();
        s.addChild(restartLabelTest());
        director.runScene(s);

    },
    onNextCallback:function (sender) {
        var s = new LabelTestScene();
        s.addChild(nextLabelTest());
        director.runScene(s);

    },
    onBackCallback:function (sender) {
        var s = new LabelTestScene();
        s.addChild(previousLabelTest());
        director.runScene(s);
    },

    // automation
    numberOfPendingTests:function() {
        return ( (arrayOfLabelTest.length-1) - labelTestIdx );
    },

    getTestNumber:function() {
        return labelTestIdx;
    }

});

//------------------------------------------------------------------
//
// LabelAtlasOpacityTest
//
//------------------------------------------------------------------
var LabelAtlasOpacityTest = AtlasDemo.extend({
    time:null,
    ctor:function () {
        //----start0----ctor
        this._super();
        this.time = 0;

        var label1 = new cc.LabelAtlas("123 Test", s_resprefix + "fonts/tuffy_bold_italic-charmap.plist");
        this.addChild(label1, 0, TAG_LABEL_SPRITE1);
        label1.x = 10;
        label1.y = 100;
        label1.opacity = 200;

        var label2 = new cc.LabelAtlas("0123456789", s_resprefix + "fonts/tuffy_bold_italic-charmap.plist");
        this.addChild(label2, 0, TAG_LABEL_SPRITE12);
        label2.x = 10;
        label2.y = 200;
        label2.opacity = 32;

        this.schedule(this.step);
        //----end0----
    },
    step:function (dt) {
        //----start0----step
        this.time += dt;

        var label1 = this.getChildByTag(TAG_LABEL_SPRITE1);
        var string1 = this.time.toFixed(2) + " Test";
        label1.setString(string1);

        var label2 = this.getChildByTag(TAG_LABEL_SPRITE12);
        var string2 = parseInt(this.time, 10).toString();
        label2.setString(string2);
        //----end0----
    },
    title:function () {
        return "LabelAtlas Opacity";
    },
    subtitle:function () {
        return "Updating label should be fast";
    },

    //
    // Automation
    //
    getExpectedResult:function() {
        // yellow, red, green, blue, yellow
        var ret = [200,32];
        return JSON.stringify(ret);
    },

    getCurrentResult:function() {
        var ret = [];
        var tags = [TAG_LABEL_SPRITE1, TAG_LABEL_SPRITE12];

        for( var i in tags ) {
            var t = tags[i];
            ret.push( this.getChildByTag(t).opacity );
        }
        return JSON.stringify(ret);
    }
});

//------------------------------------------------------------------
//
// LabelAtlasOpacityColorTest
//
//------------------------------------------------------------------
var LabelAtlasOpacityColorTest = AtlasDemo.extend({
    time:null,
    ctor:function () {
        //----start1----ctor
        this._super();
        var label1 = new cc.LabelAtlas("123 Test", s_resprefix + "fonts/tuffy_bold_italic-charmap.png", 48, 64, ' ');
        this.addChild(label1, 0, TAG_LABEL_SPRITE1);
        label1.x = 10;
        label1.y = 100;
        label1.opacity = 200;

        var label2 = new cc.LabelAtlas("0123456789", s_resprefix + "fonts/tuffy_bold_italic-charmap.png", 48, 64, ' ');
        this.addChild(label2, 0, TAG_LABEL_SPRITE12);
        label2.x = 10;
        label2.y = 200;
        label2.color = cc.color(255, 0, 0);

        var fade = cc.fadeOut(1.0);
        var fade_in = fade.reverse();
        var delay = cc.delayTime(0.25);
        var seq = cc.sequence(fade, delay, fade_in, delay.clone());
        var repeat = seq.repeatForever();
        label2.runAction(repeat);

        this.time = 0;

        this.schedule(this.step);
        //----end1----
    },
    step:function (dt) {
        //----start1----step
        this.time += dt;
        var string1 = this.time.toFixed(2) + " Test";
        var label1 = this.getChildByTag(TAG_LABEL_SPRITE1);
        label1.setString(string1);

        var label2 = this.getChildByTag(TAG_LABEL_SPRITE12);
        var string2 = parseInt(this.time, 10).toString();
        label2.setString(string2);
        //----end1----
    },
    title:function () {
        return "LabelAtlas Opacity Color";
    },
    subtitle:function () {
        return "Opacity + Color should work at the same time";
    },

    //
    // Automation
    //
    testDuration:1,
    getExpectedResult:function() {
        // yellow, red, green, blue, yellow
        var ret = [200,{"r":255,"g":255,"b":255},0,{"r":255,"g":0,"b":0}];
        return JSON.stringify(ret);
    },

    getCurrentResult:function() {
        var ret = [];
        var tags = [TAG_LABEL_SPRITE1, TAG_LABEL_SPRITE12];

        for( var i in tags ) {
            var t = tags[i];
            ret.push( this.getChildByTag(t).opacity );
            ret.push( this.getChildByTag(t).color );
        }
        return JSON.stringify(ret);
    }
});

//------------------------------------------------------------------
//
// LabelAtlasHD
//
//------------------------------------------------------------------
var LabelAtlasHD = AtlasDemo.extend({
    ctor:function () {
        //----start2----ctor
        this._super();
        var s = director.getWinSize();

        // cc.LabelBMFont
        var label1 = new cc.LabelAtlas("TESTING RETINA DISPLAY", s_resprefix + "fonts/larabie-16.plist");
        label1.anchorX = 0.5;
        label1.anchorY = 0.5;

        this.addChild(label1);
        label1.x = s.width / 2;
        label1.y = s.height / 2;
        //----end2----
    },
    title:function () {
        return "LabelAtlas with Retina Display";
    },
    subtitle:function () {
        return "loading larabie-16 / larabie-16-hd";
    },


    //
    // Automation
    //

    pixel: {"0": 255, "1": 255, "2": 255, "3": 255},

    getExpectedResult:function() {

        // var ret = [{"0":0,"1":0,"2":226,"3":255},{"0":47,"1":0,"2":0,"3":255},{"0":0,"1":47,"2":0,"3":255}];
        var s = director.getWinSize();
        var ret = {"center": "yes"};
        return JSON.stringify(ret);
    },

    getCurrentResult:function() {

        var s = director.getWinSize();
        var ret2 =  this.readPixels(s.width/2, s.height/2, 100, 100);

        var ret = {"center": this.containsPixel(ret2, this.pixel) ? "yes" : "no"};

        return JSON.stringify(ret);
    }
});


//------------------------------------------------------------------
//
// BMFontOpacityColorAlignmentTest
//
//------------------------------------------------------------------
var BMFontOpacityColorAlignmentTest = AtlasDemo.extend({
    time:0,
    ctor:function () {
        //----start3----ctor
        this._super();
        var col = new cc.LayerColor(cc.color(128, 128, 128, 255));
        this.addChild(col, -10);

        var label1 = new cc.LabelBMFont("Test", s_resprefix + "fonts/bitmapFontTest2.fnt");

        // testing anchors
        label1.anchorX = 0;
        label1.anchorY = 0;
        this.addChild(label1, 0, TAG_BITMAP_ATLAS1);
        var fade = cc.fadeOut(1.0);
        var fade_in = fade.reverse();
        var seq = cc.sequence(fade, cc.delayTime(0.25), fade_in);
        var repeat = seq.repeatForever();
        label1.runAction(repeat);

        // VERY IMPORTANT
        // color and opacity work OK because bitmapFontAltas2 loads a BMP image (not a PNG image)
        // If you want to use both opacity and color, it is recommended to use NON premultiplied images like BMP images
        // Of course, you can also tell XCode not to compress PNG images, but I think it doesn't work as expected
        var label2 = new cc.LabelBMFont("Test", s_resprefix + "fonts/bitmapFontTest2.fnt");
        // testing anchors
        label2.anchorX = 0.5;
        label2.anchorY = 0.5;
        label2.color = cc.color.RED;
        this.addChild(label2, 0, TAG_BITMAP_ATLAS2);
        label2.runAction(repeat.clone());

        var label3 = new cc.LabelBMFont("Test", s_resprefix + "fonts/bitmapFontTest2.fnt");
        // testing anchors
        label3.anchorX = 1;
        label3.anchorY = 1;
        this.addChild(label3, 0, TAG_BITMAP_ATLAS3);

        var s = director.getWinSize();
        label1.x = 0;
        label1.y = 0;
        label2.x = s.width / 2;
        label2.y = s.height / 2;
        label3.x = s.width;
        label3.y = s.height;

        this.schedule(this.step);
        //----end3----
    },
    step:function (dt) {
        //----start3----step
        this.time += dt;
        //var string;
        var string = this.time.toFixed(2) + "Test j";

        var label1 = this.getChildByTag(TAG_BITMAP_ATLAS1);
        label1.setString(string);

        var label2 = this.getChildByTag(TAG_BITMAP_ATLAS2);
        label2.setString(string);

        var label3 = this.getChildByTag(TAG_BITMAP_ATLAS3);
        label3.setString(string);
        //----end3----
    },

    title:function () {
        return "cc.LabelBMFont";
    },
    subtitle:function () {
        return "Testing alignment. Testing opacity + tint";
    },


    //
    // Automation
    //
    testDuration:1.1,
    getExpectedResult:function() {
        // yellow, red, green, blue, yellow
        var ret = [0,{"r":255,"g":255,"b":255},0,{"r":255,"g":0,"b":0}];
        return JSON.stringify(ret);
    },

    getCurrentResult:function() {
        var ret = [];
        var tags = [TAG_BITMAP_ATLAS1, TAG_BITMAP_ATLAS2];

        for( var i in tags ) {
            var t = tags[i];
            ret.push( this.getChildByTag(t).opacity );
            ret.push( this.getChildByTag(t).color );
        }
        return JSON.stringify(ret);
    }
});

//------------------------------------------------------------------
//
// BMFontSubSpriteTest
//
//------------------------------------------------------------------
var BMFontSubSpriteTest = AtlasDemo.extend({
    time:null,
    ctor:function () {
        //----start4----ctor
        this._super();
        this.time = 0;

        var s = director.getWinSize();

        var drawNode = new cc.DrawNode();
        this.addChild(drawNode);
        drawNode.setDrawColor(cc.color(255,0,0,128));
        drawNode.drawSegment(cc.p(0, s.height / 2), cc.p(s.width, s.height / 2), 2);
        drawNode.drawSegment(cc.p(s.width / 2, 0), cc.p(s.width / 2, s.height), 2);

        // Upper Label
        var label = new cc.LabelBMFont("Bitmap Font Atlas", s_resprefix + "fonts/bitmapFontTest.fnt");
        this.labelObj = label;
        this.addChild(label);

        label.x = s.width / 2;
        label.y = s.height / 2;
        label.anchorX = 0.5;
        label.anchorY = 0.5;

        var BChar = label.getChildByTag(0);
        var FChar = label.getChildByTag(7);
        var AChar = label.getChildByTag(12);

        if(autoTestEnabled) {
            var jump = cc.jumpBy(0.5, cc.p(0,0), 60, 1);
            var jump_4ever = cc.sequence(jump, cc.delayTime(0.25)).repeatForever();
            var fade_out = cc.fadeOut(0.5);
            var rotate = cc.rotateBy(0.5, 180);
            var rot_4ever = cc.sequence(rotate, cc.delayTime(0.25), rotate.clone()).repeatForever();

            var scale = cc.scaleBy(0.5, 1.5);
        } else {
            var jump = cc.jumpBy(4, cc.p(0,0), 60, 1);
            var jump_4ever = jump.repeatForever();
            var fade_out = cc.fadeOut(1);
            var rotate = cc.rotateBy(2, 360);
            var rot_4ever = rotate.repeatForever();

            var scale = cc.scaleBy(2, 1.5);
        }

        var scale_back = scale.reverse();
        var scale_seq = cc.sequence(scale, cc.delayTime(0.25), scale_back);
        var scale_4ever = scale_seq.repeatForever();

        var fade_in = cc.fadeIn(1);
        var seq = cc.sequence(fade_out, cc.delayTime(0.25), fade_in);
        var fade_4ever = seq.repeatForever();

        BChar.runAction(rot_4ever);
        BChar.runAction(scale_4ever);
        FChar.runAction(jump_4ever);
        AChar.runAction(fade_4ever);

        // Bottom Label
        var label2 = new cc.LabelBMFont("00.0", s_resprefix + "fonts/bitmapFontTest.fnt");
        this.addChild(label2, 0, TAG_BITMAP_ATLAS2);
        label2.x = s.width / 2.0;
        label2.y = 80;

        var lastChar = label2.getChildByTag(3);
        lastChar.runAction(rot_4ever.clone());

        this.schedule(this.step, 0.1);
        //----end4----
    },
    step:function (dt) {
        //----start4----step
        this.time += dt;
        var string = this.time.toFixed(1);
        string = (string < 10) ? "0" + string : string;
        var label1 = this.getChildByTag(TAG_BITMAP_ATLAS2);
        label1.setString(string);
        //----end4----
    },
    title:function () {
        return "cc.LabelBMFont BMFontSubSpriteTest";
    },
    subtitle:function () {
        return "Using fonts as cc.Sprite objects. Some characters should rotate.";
    },

    //
    // Automation
    //
    testDuration:0.6,
    getExpectedResult:function() {
        // yellow, red, green, blue, yellow
        var ret = {"rotate": 180, "scale": 1.5, "opacity": 0};
        return JSON.stringify(ret);
    },

    getCurrentResult:function() {

        var s = this.labelObj.getChildByTag(0).scale;
        var r = this.labelObj.getChildByTag(0).rotation;
        var o = this.labelObj.getChildByTag(12).opacity;
        var ret = {"rotate": r, "scale": s, "opacity": o};

        return JSON.stringify(ret);
    }
});

//------------------------------------------------------------------
//
// BMFontPaddingTest
//
//------------------------------------------------------------------
var BMFontPaddingTest = AtlasDemo.extend({
    ctor:function () {
        //----start5----
        this._super();
        var label = new cc.LabelBMFont("abcdefg", s_resprefix + "fonts/bitmapFontTest4.fnt");
        this.addChild(label);

        var s = director.getWinSize();

        label.x = s.width / 2;
        label.y = s.height / 2;
        label.anchorX = 0.5;
        label.anchorY = 0.5;
        //----end5----
    },
    title:function () {
        return "cc.LabelBMFont BMFontPaddingTest";
    },
    subtitle:function () {
        return "Testing padding";
    },


    //
    // Automation
    //
    pixel: {"0": 255, "1": 255, "2": 255, "3": 255},

    getExpectedResult:function() {

        // var ret = [{"0":0,"1":0,"2":226,"3":255},{"0":47,"1":0,"2":0,"3":255},{"0":0,"1":47,"2":0,"3":255}];
        var s = director.getWinSize();
        var ret = {"center": "yes"};
        return JSON.stringify(ret);
    },

    getCurrentResult:function() {

        var s = director.getWinSize();
        var ret2 =  this.readPixels(s.width/2, s.height/2, 100, 100);
        var ret = {"center": this.containsPixel(ret2, this.pixel) ? "yes" : "no"};
        return JSON.stringify(ret);
    }
});

//------------------------------------------------------------------
//
// BMFontOffsetTest
//
//------------------------------------------------------------------
var BMFontOffsetTest = AtlasDemo.extend({
    ctor:function () {
        //----start6----ctor
        this._super();
        var s = director.getWinSize();

        var label = null;
        label = new cc.LabelBMFont("FaFeFiFoFu", s_resprefix + "fonts/bitmapFontTest5.fnt");
        this.addChild(label);
        label.x = s.width / 2;
        label.y = s.height / 2 + 50;
        label.anchorX = 0.5;
        label.anchorY = 0.5;

        label = new cc.LabelBMFont("fafefifofu", s_resprefix + "fonts/bitmapFontTest5.fnt");
        this.addChild(label);
        label.x = s.width / 2;
        label.y = s.height / 2;
        label.anchorX = 0.5;
        label.anchorY = 0.5;

        label = new cc.LabelBMFont("aeiou", s_resprefix + "fonts/bitmapFontTest5.fnt");
        this.addChild(label);
        label.x = s.width / 2;
        label.y = s.height / 2 - 50;
        label.anchorX = 0.5;
        label.anchorY = 0.5;
        //----end6----
    },
    title:function () {
        return "cc.LabelBMFont";
    },
    subtitle:function () {
        return "Rendering should be OK. Testing offset";
    },

    //
    // Automation
    //

    pixel: {"0":150,"1":150,"2":150,"3":255},
    getExpectedResult:function() {
	var ret =  {"top": "yes", "center": "yes", "bottom": "yes"};

        return JSON.stringify(ret);
    },

    getCurrentResult:function() {

        var s = director.getWinSize();
        var ret1 =  this.readPixels(s.width/2, s.height/2-50, 50, 50);
        var ret2 =  this.readPixels(s.width/2, s.height/2, 50, 50);
        var ret3 =  this.readPixels(s.width/2, s.height/2+50, 50, 50);
        var ret = {"top": this.containsPixel(ret1, this.pixel, true, 140) ? "yes" : "no",
                   "center": this.containsPixel(ret2, this.pixel, true, 140) ? "yes" : "no",
                   "bottom": this.containsPixel(ret3, this.pixel, true, 140) ? "yes" : "no"};
        return JSON.stringify(ret);
    }
});

//------------------------------------------------------------------
//
// BMFontTintTest
//
//------------------------------------------------------------------
var BMFontTintTest = AtlasDemo.extend({
    ctor:function () {
        //----start7----ctor
        this._super();
        var s = director.getWinSize();

        var label = null;
        label = new cc.LabelBMFont("Blue", s_resprefix + "fonts/bitmapFontTest5.fnt");
        label.color = cc.color(0, 0, 255);
        this.addChild(label);
        label.x = s.width / 2;
        label.y = s.height / 4;
        label.anchorX = 0.5;
        label.anchorY = 0.5;

        label = new cc.LabelBMFont("Red", s_resprefix + "fonts/bitmapFontTest5.fnt");
        this.addChild(label);
        label.x = s.width / 2;
        label.y = 2 * s.height / 4;
        label.anchorX = 0.5;
        label.anchorY = 0.5;
        label.color = cc.color(255, 0, 0);

        label = new cc.LabelBMFont("G", s_resprefix + "fonts/bitmapFontTest5.fnt");
        this.addChild(label);
        label.x = s.width / 2;
        label.y = 3 * s.height / 4;
        label.anchorX = 0.5;
        label.anchorY = 0.5;
        label.color = cc.color(0, 255, 0);
        label.setString("Green");
        //----end7----
    },
    title:function () {
        return "cc.LabelBMFont BMFontTintTest";
    },
    subtitle:function () {
        return "Testing color";
    },

    //
    // Automation
    //

    pixel1: {"0":0,"1":0,"2":255,"3":255},
    pixel2: {"0":255,"1":0,"2":0,"3":255},
    pixel3: {"0":0,"1":255,"2":0,"3":255},
    getExpectedResult:function() {
        var ret = {"left": "yes", "center": "yes", "right": "yes"};
        return JSON.stringify(ret);
    },

    getCurrentResult:function() {

        var s = director.getWinSize();
        var ret1 =  this.readPixels(s.width/2, s.height/4, 50, 50);
        var ret2 =  this.readPixels(s.width/2, 2 * s.height/4, 50, 50);
        var ret3 =  this.readPixels(s.width/2, 3 * s.height/4, 50, 50);
        var ret = {"left": this.containsPixel(ret1, this.pixel1, true, 100) ? "yes" : "no",
                   "center": this.containsPixel(ret2, this.pixel2, true, 100) ? "yes" : "no",
                   "right": this.containsPixel(ret3, this.pixel3, true, 100) ? "yes" : "no"}
        return JSON.stringify(ret);
    }
});

//------------------------------------------------------------------
//
// BMFontSpeedTest
//
//------------------------------------------------------------------
var BMFontSpeedTest = AtlasDemo.extend({
    ctor:function () {
        //----start8----ctor
        this._super();
        // Upper Label
        for (var i = 0; i < 100; i++) {
            var str = "-" + i + "-";
            var label = new cc.LabelBMFont(str, s_resprefix + "fonts/bitmapFontTest.fnt");
            this.addChild(label);

            var s = director.getWinSize();

            var p = cc.p(Math.random() * s.width, Math.random() * s.height);
            label.setPosition(p);
            label.anchorX = 0.5;
            label.anchorY = 0.5;
        }
        //----end8----
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
// BMFontMultiLineTest
//
//------------------------------------------------------------------
var BMFontMultiLineTest = AtlasDemo.extend({
    ctor:function () {
        //----start9----ctor
        this._super();

        // Left
        var label1 = new cc.LabelBMFont("Multi line\nLeft", s_resprefix + "fonts/bitmapFontTest3.fnt");
        label1.anchorX = 0;
        label1.anchorY = 0;
        this.addChild(label1, 0, TAG_BITMAP_ATLAS1);
        cc.log("content size:" + label1.width + "," + label1.height);


        // Center
        var label2 = new cc.LabelBMFont("Multi line\nCenter", s_resprefix + "fonts/bitmapFontTest3.fnt");
        label2.anchorX = 0.5;
        label2.anchorY = 0.5;
        this.addChild(label2, 0, TAG_BITMAP_ATLAS2);
        cc.log("content size:" + label2.width + "," + label2.height);

        // right
        var label3 = new cc.LabelBMFont("Multi line\nRight\nThree lines Three", s_resprefix + "fonts/bitmapFontTest3.fnt");
        label3.anchorX = 1;
        label3.anchorY = 1;
        this.addChild(label3, 0, TAG_BITMAP_ATLAS3);
        cc.log("content size:" + label3.width + "," + label3.height);

        var s = director.getWinSize();
        label1.x = 0;
        label1.y = 0;
        label2.x = s.width / 2;
        label2.y = s.height / 2;
        label3.x = s.width;
        label3.y = s.height;
        //----end9----
    },
    title:function () {
        return "cc.LabelBMFont BMFontMultiLineTest";
    },
    subtitle:function () {
        return "Multiline + anchor point";
    },

    // Automation

    pixel: {"0": 255, "1": 186, "2": 33, "3": 255},

    getExpectedResult:function() {

        // var ret = [{"0":0,"1":0,"2":226,"3":255},{"0":47,"1":0,"2":0,"3":255},{"0":0,"1":47,"2":0,"3":255}];
        var s = director.getWinSize();
        var ret = {"left": "yes", "center": "yes", "right": "yes"};
        return JSON.stringify(ret);
    },

    getCurrentResult:function() {

        var s = director.getWinSize();
        var ret1 =  this.readPixels(0, 0, 100, 100);
        var ret2 =  this.readPixels(s.width/2, s.height/2, 100, 100);
        var ret3 =  this.readPixels(s.width - 100, s.height - 100, 100, 100);


        var ret = {"left": this.containsPixel(ret1, this.pixel) ? "yes" : "no",
                   "center": this.containsPixel(ret2, this.pixel) ? "yes" : "no",
                   "right": this.containsPixel(ret3, this.pixel) ? "yes" : "no"}
        return JSON.stringify(ret);
    }
});

//------------------------------------------------------------------
//
// BMFontMultiLine2Test
//
//------------------------------------------------------------------
var BMFontMultiLine2Test = AtlasDemo.extend({
    ctor:function () {
        //----start10----ctor
        this._super();

        // Left
        var label1 = new cc.LabelBMFont("Multi line\n\nAligned to the left", s_resprefix + "fonts/bitmapFontTest3.fnt");
        label1.anchorX = 0;
        label1.anchorY = 0;
        label1.textAlign = cc.TEXT_ALIGNMENT_LEFT;
        label1.boundingWidth = 400;
        this.addChild(label1, 0, TAG_BITMAP_ATLAS1);
        cc.log("content size:" + label1.width + "," + label1.height);


        // Center
        var label2 = new cc.LabelBMFont("Error\n\nSome error message", s_resprefix + "fonts/bitmapFontTest3.fnt");
        label2.anchorX = 0.5;
        label2.anchorY = 0.5;
        label2.textAlign = cc.TEXT_ALIGNMENT_CENTER;
        label2.boundingWidth = 290;
        this.addChild(label2, 0, TAG_BITMAP_ATLAS2);
        cc.log("content size:" + label2.width + "," + label2.height);

        // right
        var label3 = new cc.LabelBMFont("Multi line\n\nAligned to the right", s_resprefix + "fonts/bitmapFontTest3.fnt");
        label3.anchorX = 1;
        label3.anchorY = 1;
        label3.textAlign = cc.TEXT_ALIGNMENT_RIGHT;
        label3.boundingWidth = 400;
        this.addChild(label3, 0, TAG_BITMAP_ATLAS3);
        cc.log("content size:" + label3.width + "," + label3.height);

        var s = director.getWinSize();
        label1.x = 0;
        label1.y = 0;
        label2.x = s.width / 2;
        label2.y = s.height / 2;
        label3.x = s.width;
        label3.y = s.height;
        //----end10----
    },
    title:function () {
        return "cc.LabelBMFont BMFontMultiLine2Test";
    },
    subtitle:function () {
        return "Multiline with 2 new lines. All characters should appear";
    },
        // Automation

    pixel: {"0": 255, "1": 186, "2": 33, "3": 255},

    getExpectedResult:function() {

        // var ret = [{"0":0,"1":0,"2":226,"3":255},{"0":47,"1":0,"2":0,"3":255},{"0":0,"1":47,"2":0,"3":255}];
        var s = director.getWinSize();
        var ret = {"left": "yes", "center": "yes", "right": "yes"};
        return JSON.stringify(ret);
    },

    getCurrentResult:function() {
        var s = director.getWinSize();
        var ret1 =  this.readPixels(0, 0, 100, 100);
        var ret2 =  this.readPixels(s.width/2, s.height/2, 100, 100);
        var ret3 =  this.readPixels(s.width - 100, s.height - 100, 100, 100);

        var ret = {"left": this.containsPixel(ret1, this.pixel) ? "yes" : "no",
                   "center": this.containsPixel(ret2, this.pixel) ? "yes" : "no",
                   "right": this.containsPixel(ret3, this.pixel) ? "yes" : "no"}
        return JSON.stringify(ret);
    }
});

//------------------------------------------------------------------
//
// LabelsEmpty
//
//------------------------------------------------------------------
var LabelsEmpty = AtlasDemo.extend({
    setEmpty:null,
    ctor:function () {
        //----start25----ctor
        this._super();


        // cc.LabelBMFont
        var label1 = new cc.LabelBMFont("", s_resprefix + "fonts/bitmapFontTest3.fnt");
        this.addChild(label1, 0, TAG_BITMAP_ATLAS1);
        label1.x = winSize.width / 2;
        label1.y = winSize.height - 100;

        // cc.LabelTTF
        var label2 = new cc.LabelTTF("", "Arial", 24);
        this.addChild(label2, 0, TAG_BITMAP_ATLAS2);
        label2.x = winSize.width / 2;
        label2.y = winSize.height / 2;

        // cc.LabelAtlas
        var label3 = new cc.LabelAtlas("", s_resprefix + "fonts/tuffy_bold_italic-charmap.png", 48, 64, ' ');
        this.addChild(label3, 0, TAG_BITMAP_ATLAS3);
        label3.x = winSize.width / 2;
        label3.y = 0 + 100;

        this.schedule(this.onUpdateStrings, 1.0);

        this.setEmpty = false;
        //----end25----
    },
    onUpdateStrings:function (dt) {
        //----start25----onUpdateStrings
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
        //----end25----
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
// BMFontHDTest
//
//------------------------------------------------------------------
var BMFontHDTest = AtlasDemo.extend({
    ctor:function () {
        //----start16----ctor
        this._super();
        var s = director.getWinSize();

        // cc.LabelBMFont
        var label1 = new cc.LabelBMFont("TESTING RETINA DISPLAY", s_resprefix + "fonts/konqa32.fnt");
        this.addChild(label1);
        label1.x = s.width / 2;
        label1.y = s.height / 2;
        //----end16----
    },
    title:function () {
        return "Testing Retina Display BMFont";
    },
    subtitle:function () {
        return "loading arista16 or arista16-hd";
    },

    //
    // Automation
    //

    pixel: {"0": 255, "1": 255, "2": 255, "3": 255},

    getExpectedResult:function() {

        // var ret = [{"0":0,"1":0,"2":226,"3":255},{"0":47,"1":0,"2":0,"3":255},{"0":0,"1":47,"2":0,"3":255}];
        var s = director.getWinSize();
        var ret = {"center": "yes"};
        return JSON.stringify(ret);
    },

    getCurrentResult:function() {

        var s = director.getWinSize();
        var ret2 =  this.readPixels(s.width/2, s.height/2, 100, 100);

        var ret = {"center": this.containsPixel(ret2, this.pixel) ? "yes" : "no"};

        return JSON.stringify(ret);
    }
});

//------------------------------------------------------------------
//
// BMFontGlyphDesignerTest
//
//------------------------------------------------------------------
var BMFontGlyphDesignerTest = AtlasDemo.extend({
    ctor:function () {
        //----start17----ctor
        this._super();
        var s = director.getWinSize();

        var layer = new cc.LayerColor(cc.color(128, 128, 128, 255));
        this.addChild(layer, -10);

        // cc.LabelBMFont
        var label1 = new cc.LabelBMFont("Testing Glyph Designer", s_resprefix + "fonts/futura-48.fnt");
        this.addChild(label1);
        label1.x = s.width / 2;
        label1.y = s.height / 2;
        //----end17----
    },
    title:function () {
        return "Testing Glyph Designer";
    },
    subtitle:function () {
        return "You should see a font with shadows and outline";
    },

    //
    // Automation
    //

    pixel: {"0": 240, "1": 201, "2": 108, "3": 255},

    getExpectedResult:function() {

        // var ret = [{"0":0,"1":0,"2":226,"3":255},{"0":47,"1":0,"2":0,"3":255},{"0":0,"1":47,"2":0,"3":255}];
        var s = director.getWinSize();
        var ret = {"center": "yes"};
        return JSON.stringify(ret);
    },

    getCurrentResult:function() {

        var s = director.getWinSize();
        var ret2 =  this.readPixels(s.width/2, s.height/2, 100, 100);

        var ret = {"center": this.containsPixel(ret2, this.pixel) ? "yes" : "no"};

        return JSON.stringify(ret);
    }
});

//------------------------------------------------------------------
//
// LabelTTFTest
//
//------------------------------------------------------------------

var LabelTTFStrokeShadowTest = AtlasDemo.extend({
    _labelShadow: null,
    _labelStroke: null,
    _labelStrokeShadow: null,

    ctor: function () {
        //----start26----ctor
        this._super();
        this.updateLabels();
        //----end26----
    },

    updateLabels: function () {
        //----start26----updateLabels
        var blockSize = cc.size(400, 100);
        var s = director.getWinSize();

        // colors
        var redColor = cc.color(255, 0, 0);
        var yellowColor = cc.color(255, 255, 0);
        var blueColor = cc.color(0, 0, 255);

        // shadow offset
        var shadowOffset = cc.p(12, -12);

        // positioning stuff
        var posX = s.width / 2 - (blockSize.width / 2);
        var posY_5 = s.height / 7;

        // font definition
        var fontDefRedShadow = new cc.FontDefinition();
        fontDefRedShadow.fontName = "Arial";
        fontDefRedShadow.fontSize = 32;
        fontDefRedShadow.textAlign = cc.TEXT_ALIGNMENT_LEFT;
        fontDefRedShadow.verticalAlign = cc.VERTICAL_TEXT_ALIGNMENT_TOP;
        fontDefRedShadow.fillStyle = redColor;
        fontDefRedShadow.boundingWidth = blockSize.width;
	    fontDefRedShadow.boundingHeight = blockSize.height;
        // shadow
        fontDefRedShadow.shadowEnabled = true;
        fontDefRedShadow.shadowOffsetX = shadowOffset.x;
	    fontDefRedShadow.shadowOffsetY = shadowOffset.y;

        // create the label using the definition
        this._labelShadow = new cc.LabelTTF("Shadow Only", fontDefRedShadow);
        this._labelShadow.anchorX = 0;
        this._labelShadow.anchorY = 0;
        this._labelShadow.x = posX;
        this._labelShadow.y = posY_5;

        // font definition
        var fontDefBlueStroke = new cc.FontDefinition();
        fontDefBlueStroke.fontName = "Arial";
        fontDefBlueStroke.fontSize = 32;
        fontDefBlueStroke.textAlign = cc.TEXT_ALIGNMENT_LEFT;
        fontDefBlueStroke.verticalAlign = cc.VERTICAL_TEXT_ALIGNMENT_TOP;
        fontDefBlueStroke.fillStyle = blueColor;
        fontDefBlueStroke.boundingWidth = blockSize.width;
	    fontDefBlueStroke.boundingHeight = blockSize.height;
        // stroke
        fontDefBlueStroke.strokeEnabled = true;
        fontDefBlueStroke.strokeStyle = yellowColor;

        this._labelStroke = new cc.LabelTTF("Stroke Only", fontDefBlueStroke);
        this._labelStroke.anchorX = 0;
        this._labelStroke.anchorY = 0;
        this._labelStroke.x = posX;
        this._labelStroke.y = posY_5 * 2;

        // font definition
        var fontDefRedStrokeShadow = new cc.FontDefinition();
        fontDefRedStrokeShadow.fontName = "Arial";
        fontDefRedStrokeShadow.fontSize = 32;
        fontDefRedStrokeShadow.textAlign = cc.TEXT_ALIGNMENT_LEFT;
        fontDefRedStrokeShadow.verticalAlign = cc.VERTICAL_TEXT_ALIGNMENT_TOP;
        fontDefRedStrokeShadow.fillStyle = blueColor;
        fontDefRedStrokeShadow.boundingWidth = blockSize.width;
	    fontDefRedStrokeShadow.boundingHeight = blockSize.height;
        // stroke
        fontDefRedStrokeShadow.strokeEnabled = true;
        fontDefRedStrokeShadow.strokeStyle = redColor;
        // shadow
        fontDefRedStrokeShadow.shadowEnabled = true;
        fontDefRedStrokeShadow.shadowOffsetX = -12;
	    fontDefRedStrokeShadow.shadowOffsetY = 12;   //shadowOffset;

        this._labelStrokeShadow = new cc.LabelTTF("Stroke + Shadow\n New Line", fontDefRedStrokeShadow);
        this._labelStrokeShadow.anchorX = 0;
        this._labelStrokeShadow.anchorY = 0;
        this._labelStrokeShadow.x = posX;
        this._labelStrokeShadow.y = posY_5 * 3;

        // add all the labels
        this.addChild(this._labelShadow);
        this.addChild(this._labelStroke);
        this.addChild(this._labelStrokeShadow);
        //----end26----
    },

    title: function () {
        return "Testing cc.LabelTTF + shadow and stroke";
    },

    subtitle: function () {
        return "";
    }
});

var LabelTTFTest = AtlasDemo.extend({
    _label:null,
    _horizAlign:null,
    _vertAlign:null,
    ctor:function () {
        //----start19----ctor
        this._super();
        var blockSize = cc.size(200, 160);
        var s = director.getWinSize();

        var colorLayer = new cc.LayerColor(cc.color(100, 100, 100, 255), blockSize.width, blockSize.height);
        colorLayer.anchorX = 0;
        colorLayer.anchorY = 0;
        colorLayer.x = (s.width - blockSize.width) / 2;
        colorLayer.y = (s.height - blockSize.height) / 2;

        this.addChild(colorLayer);

        cc.MenuItemFont.setFontSize(30);
        var menu = new cc.Menu(
            new cc.MenuItemFont("Left", this.setAlignmentLeft, this),
            new cc.MenuItemFont("Center", this.setAlignmentCenter, this),
            new cc.MenuItemFont("Right", this.setAlignmentRight, this));
        menu.alignItemsVerticallyWithPadding(4);
        menu.x = 50;
        menu.y = s.height / 2 - 20;
        this.addChild(menu);

        menu = new cc.Menu(
            new cc.MenuItemFont("Top", this.setAlignmentTop, this),
            new cc.MenuItemFont("Middle", this.setAlignmentMiddle, this),
            new cc.MenuItemFont("Bottom", this.setAlignmentBottom, this));
        menu.alignItemsVerticallyWithPadding(4);
        menu.x = s.width - 50;
        menu.y = s.height / 2 - 20;
        this.addChild(menu);

        this._label = null;
        this._horizAlign = cc.TEXT_ALIGNMENT_LEFT;
        this._vertAlign = cc.VERTICAL_TEXT_ALIGNMENT_TOP;

        this.updateAlignment();
        //----end19----
    },
    updateAlignment:function () {
        //----start19----updateAlignment
        var blockSize = cc.size(200, 160);
        var s = director.getWinSize();

        if (this._label) {
            this._label.removeFromParent();
        }

        this._label = new cc.LabelTTF(this.getCurrentAlignment(), "Arial", 32, blockSize, this._horizAlign, this._vertAlign);

        this._label.anchorX = 0;
        this._label.anchorY = 0;
        this._label.x = (s.width - blockSize.width) / 2;
        this._label.y = (s.height - blockSize.height) / 2;

        this.addChild(this._label);
        //----end19----
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
        //----start19----getCurrentAlignment
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
        //----end19----
    },
    title:function () {
        return "Testing cc.LabelTTF";
    },
    subtitle:function () {
        return "Select the buttons on the sides to change alignment";
    }
});

var LabelTTFMultiline = AtlasDemo.extend({
    ctor:function () {
        //----start20----ctor
        this._super();
        var s = director.getWinSize();

        // cc.LabelBMFont
        var center = new cc.LabelTTF("word wrap \"testing\" (bla0) bla1 'bla2' [bla3] (bla4) {bla5} {bla6} [bla7] (bla8) [bla9] 'bla0' \"bla1\"",
            "Arial", 32, cc.size(s.width / 2, 200), cc.TEXT_ALIGNMENT_CENTER, cc.VERTICAL_TEXT_ALIGNMENT_TOP);
        center.setDimensions(s.width / 2, 200);
        center.x = s.width / 2;
        center.y = 150;

        this.addChild(center);
        //----end20----
    },
    title:function () {
        return "Testing cc.LabelTTF Word Wrap";
    },
    subtitle:function () {
        return "Word wrap using cc.LabelTTF";
    },

    //
    // Automation
    //

    pixel: {"0": 255, "1": 255, "2": 255, "3": 255},

    getExpectedResult:function() {

        // var ret = [{"0":0,"1":0,"2":226,"3":255},{"0":47,"1":0,"2":0,"3":255},{"0":0,"1":47,"2":0,"3":255}];
        var s = director.getWinSize();
        var ret = {"center": "yes"};
        return JSON.stringify(ret);
    },

    getCurrentResult:function() {

        var s = director.getWinSize();
        var ret2 =  this.readPixels(s.width/2, 125, 100, 100);

        var ret = {"center": this.containsPixel(ret2, this.pixel) ? "yes" : "no"};

        return JSON.stringify(ret);
    }
});

var LabelTTFChinese = AtlasDemo.extend({
    ctor:function () {
        //----start21----ctor
        this._super();
        var size = director.getWinSize();
        var fontname = (cc.sys.os === cc.sys.OS_WP8 ) ? "fonts/arialuni.ttf" : (cc.sys.os == cc.sys.OS_WINRT) ? "DengXian" : "Microsoft Yahei";
        var label = new cc.LabelTTF("中国", fontname, 30);
        label.x = size.width / 2;
        label.y = size.height / 3 * 2;
        this.addChild(label);

        // Test UTF8 string from native to jsval.
        var label2 = new cc.LabelTTF("string from native:"+label.getString(), fontname, 30);
        label2.x = size.width / 2;
        label2.y = size.height / 3;
        this.addChild(label2);
        //----end21----
    },
    title:function () {
        return "Testing cc.LabelTTF with Chinese character";
    }
});

var BMFontChineseTest = AtlasDemo.extend({
    ctor:function () {
        //----start18----ctor
        this._super();
        var size = director.getWinSize();
        var label = new cc.LabelBMFont("中国", s_resprefix + "fonts/bitmapFontChinese.fnt");
        label.x = size.width / 2;
        label.y = size.height / 2;
        this.addChild(label);
        //----end18----
    },
    title:function () {
        return "Testing cc.LabelBMFont with Chinese character";
    },

    //
    // Automation
    //

    pixel: {"0": 255, "1": 0, "2": 142, "3": 255},

    getExpectedResult:function() {

        // var ret = [{"0":0,"1":0,"2":226,"3":255},{"0":47,"1":0,"2":0,"3":255},{"0":0,"1":47,"2":0,"3":255}];
        var s = director.getWinSize();
        var ret = {"center": "yes"};
        return JSON.stringify(ret);
    },

    getCurrentResult:function() {

        var s = director.getWinSize();
        var ret2 =  this.readPixels(s.width/2, s.height / 2, 100, 100);

        var ret = {"center": this.containsPixel(ret2, this.pixel) ? "yes" : "no"};

        return JSON.stringify(ret);
    }
});

var LongSentencesExample = "Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.";
var chineseExampleText = "美好的一天美好的一天美好的一天美好的一天美好的一天美好的一天美好的一天美好的一天美好的一天美好的一天美好的一天";
var chineseMixEnglishText = "美好的一天bdgpy美b好b的d一b天d美好bd的p一g天美好b的d一d天bdgpybdgpybdgpybdg美好的一天bdgpy美好的一天美好的一天";
var mixAllLanguageText = "美好良い一日を一Buen díabdgpy美b好b的d一b天d美Buen い一日を好b的d一d天Buen py美好的一天bdgpy美好的一天美好的一天";
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
var chineseText = 3;
var chineseMixEnglish = 4;
var mixAllLanguage = 5;

var alignmentItemPadding = 40;
var menuItemPaddingCenter = 80;

var BMFontMultiLineAlignmentTest = AtlasDemo.extend({
    labelShouldRetain:null,
    arrowsBarShouldRetain:null,
    arrowsShouldRetain:null,
    lastSentenceItem:null,
    lastAlignmentItem:null,
    lineBreakFlag:false,
    ctor:function () {
        //----start11----ctor
        this._super();

        cc.eventManager.addListener({
            event: cc.EventListener.TOUCH_ALL_AT_ONCE,
            onTouchesBegan: this.onTouchesBegan.bind(this),
            onTouchesMoved: this.onTouchesMoved.bind(this),
            onTouchesEnded: this.onTouchesEnded.bind(this)
        }, this);
        if ('touches' in cc.sys.capabilities){
            cc.eventManager.addListener({
                event: cc.EventListener.TOUCH_ALL_AT_ONCE,
                onTouchesBegan: this.onTouchesBegan.bind(this),
                onTouchesMoved: this.onTouchesMoved.bind(this),
                onTouchesEnded: this.onTouchesEnded.bind(this)
            }, this);
        } else if ('mouse' in cc.sys.capabilities)
            cc.eventManager.addListener({
                event: cc.EventListener.MOUSE,
                onMouseDown: this.onMouseDown.bind(this),
                onMouseMove: this.onMouseMove.bind(this),
                onMouseUp: this.onMouseUp.bind(this)
            }, this);

        // ask director the the window size
        var size = director.getWinSize();

        // create and initialize a Label
        this.labelShouldRetain = new cc.LabelBMFont(LongSentencesExample, s_resprefix + "fonts/markerFelt.fnt", size.width / 2, cc.TEXT_ALIGNMENT_CENTER, cc.p(0, 0));
        this.arrowsBarShouldRetain = new cc.Sprite(s_resprefix + "Images/arrowsBar.png");
        this.arrowsShouldRetain = new cc.Sprite(s_resprefix + "Images/arrows.png");

        cc.MenuItemFont.setFontSize(20);
        var longSentences = new cc.MenuItemFont("Long Flowing Sentences", this.onStringChanged, this);
        var lineBreaks = new cc.MenuItemFont("Short Sentences With Intentional Line Breaks", this.onStringChanged, this);
        var mixed = new cc.MenuItemFont("Long Sentences Mixed With Intentional Line Breaks", this.onStringChanged.bind(this)); // another way to pass 'this'
        var changeChineseItem = new cc.MenuItemFont("change chinese", this.onStringChanged, this);
        var mixEnglishItem = new cc.MenuItemFont("change chinesemixEnglish", this.onStringChanged, this);
        var mixAllLanItem = new cc.MenuItemFont("change mixAllLan", this.onStringChanged, this);

        var stringMenu = new cc.Menu(longSentences, lineBreaks, mixed, changeChineseItem,mixEnglishItem, mixAllLanItem);
        stringMenu.alignItemsVertically();

        var setLineBreakItem = new cc.MenuItemFont("setLineBreakWithoutSpace", this.onLineBreakChanged, this);
        var setScale = new cc.MenuItemFont("setScale", this.onScaleChange, this);
        var lineBreakMenu = new cc.Menu(setLineBreakItem, setScale);
        lineBreakMenu.x = 100;
        lineBreakMenu.y = winSize.height / 2;
        lineBreakMenu.alignItemsVertically();

        longSentences.color = cc.color(255, 0, 0);
        this.lastSentenceItem = longSentences;
        longSentences.tag = LongSentences;
        lineBreaks.tag = LineBreaks;
        mixed.tag = Mixed;
        changeChineseItem.tag = chineseText;
        mixEnglishItem.tag = chineseMixEnglish;
        mixAllLanItem.tag = mixAllLanguage;

        cc.MenuItemFont.setFontSize(30);

        var left = new cc.MenuItemFont("Left", this.onAlignmentChanged, this);
        var center = new cc.MenuItemFont("Center", this.onAlignmentChanged, this);
        var right = new cc.MenuItemFont("Right", this.onAlignmentChanged.bind(this));    // another way to pass 'this'
        var alignmentMenu = new cc.Menu(left, center, right);
        alignmentMenu.alignItemsHorizontallyWithPadding(alignmentItemPadding);

        center.color = cc.color(255, 0, 0);
        this.lastAlignmentItem = center;
        left.tag = LeftAlign;
        center.tag = CenterAlign;
        right.tag = RightAlign;

        // position the label on the center of the screen
        this.labelShouldRetain.x = size.width / 2;
        this.labelShouldRetain.y = size.height / 2;

        this.arrowsBarShouldRetain.visible = false;

        var arrowsWidth = (ArrowsMax - ArrowsMin) * size.width;
        this.arrowsBarShouldRetain.scaleX = arrowsWidth / this.arrowsBarShouldRetain.width;
        this.arrowsBarShouldRetain.anchorX = 0;
        this.arrowsBarShouldRetain.anchorY = 0.5;
        this.arrowsBarShouldRetain.x = ArrowsMin * size.width;
        this.arrowsBarShouldRetain.y = this.labelShouldRetain.y;

        this.arrowsShouldRetain.x = this.arrowsBarShouldRetain.x;
	    this.arrowsShouldRetain.y = this.arrowsBarShouldRetain.y;

        stringMenu.x = size.width / 2;
        stringMenu.y = size.height - menuItemPaddingCenter;
        alignmentMenu.x = size.width / 2;
        alignmentMenu.y = menuItemPaddingCenter + 15;

        this.addChild(this.labelShouldRetain);
        this.addChild(this.arrowsBarShouldRetain);
        this.addChild(this.arrowsShouldRetain);
        this.addChild(stringMenu);
        this.addChild(alignmentMenu);
        this.addChild(lineBreakMenu);


        //----end11----
    },
    __title: function(){
        return 'The scroll bar';
    },
    title:function () {
        return "";
    },
    subtitle:function () {
        return "";
    },

    onScaleChange:function(sener){
        if (this.labelShouldRetain.getScale() > 1)
        {
            this.labelShouldRetain.setScale(1.0);
        }
        else
        {
            this.labelShouldRetain.setScale(2.0);
        }

    },
    onLineBreakChanged:function(sender){
        this.lineBreakFlag = !this.lineBreakFlag;
        this.labelShouldRetain.setLineBreakWithoutSpace(this.lineBreakFlag);
    },
    onStringChanged:function (sender) {
        this.lastSentenceItem.color = cc.color(255, 255, 255);
        sender.color = cc.color(255, 0, 0);
        this.lastSentenceItem = sender;

        switch (sender.tag) {
            case LongSentences:
                this.labelShouldRetain.setString(LongSentencesExample);
                this.labelShouldRetain.setFntFile(s_resprefix + "fonts/markerFelt.fnt");
                break;
            case LineBreaks:
                this.labelShouldRetain.setString(LineBreaksExample);
                this.labelShouldRetain.setFntFile(s_resprefix + "fonts/markerFelt.fnt");
                break;
            case Mixed:
                this.labelShouldRetain.setString(MixedExample);
                this.labelShouldRetain.setFntFile(s_resprefix + "fonts/markerFelt.fnt");
                break;
            case chineseText:
                this.labelShouldRetain.setFntFile(s_resprefix + "fonts/arial-unicode-26.fnt");
                this.labelShouldRetain.setString(chineseExampleText);
                break;
            case chineseMixEnglish:
                this.labelShouldRetain.setFntFile(s_resprefix + "fonts/arial-unicode-26.fnt");
                this.labelShouldRetain.setString(chineseMixEnglishText);
                break;
            case mixAllLanguage:
                this.labelShouldRetain.setFntFile(s_resprefix + "fonts/arial-unicode-26.fnt");
                this.labelShouldRetain.setString(mixAllLanguageText);
                break;
            default:
                break;
        }

        this.snapArrowsToEdge();
    },
    onAlignmentChanged:function (sender) {
        var item = sender;
        this.lastAlignmentItem.color = cc.color(255, 255, 255);
        item.color = cc.color(255, 0, 0);
        this.lastAlignmentItem = item;

        switch (item.tag) {
            case LeftAlign:
                this.labelShouldRetain.textAlign = cc.TEXT_ALIGNMENT_LEFT;
                break;
            case CenterAlign:
                this.labelShouldRetain.textAlign = cc.TEXT_ALIGNMENT_CENTER;
                break;
            case RightAlign:
                this.labelShouldRetain.textAlign = cc.TEXT_ALIGNMENT_RIGHT;
                break;
            default:
                break;
        }

        this.snapArrowsToEdge();
    },
    onTouchesBegan:function (touches) {
        var touch = touches[0];
        var location = touch.getLocation();

        if (cc.rectContainsPoint(this.arrowsShouldRetain.getBoundingBox(), location)) {
            this.arrowsBarShouldRetain.visible = true;
        }
    },
    onTouchesEnded:function () {
        this.arrowsBarShouldRetain.visible = false;
    },
    onTouchesMoved:function (touches) {
        var touch = touches[0];
        var location = touch.getLocation();

        var winSize = director.getWinSize();

        this.arrowsShouldRetain.x = Math.max(Math.min(location.x, ArrowsMax * winSize.width), ArrowsMin * winSize.width);

        this.labelShouldRetain.boundingWidth = Math.abs(this.arrowsShouldRetain.getPosition().x - this.labelShouldRetain.getPosition().x) * 2;
    },

    onMouseDown:function (event) {
        var location = event.getLocation();

        if (cc.rectContainsPoint(this.arrowsShouldRetain.getBoundingBox(), location)) {
            this.arrowsBarShouldRetain.visible = true;
        }
    },
    onMouseMove:function (event) {
        if(!event.getButton || event.getButton() != cc.EventMouse.BUTTON_LEFT)
            return;

        var location = event.getLocation();
        var winSize = director.getWinSize();

        this.arrowsShouldRetain.x = Math.max(Math.min(location.x, ArrowsMax * winSize.width), ArrowsMin * winSize.width);
        this.labelShouldRetain.boundingWidth = Math.abs(this.arrowsShouldRetain.x - this.labelShouldRetain.x) * 2;
    },
    onMouseUp:function (event) {
        //this.snapArrowsToEdge();
        this.arrowsBarShouldRetain.visible = false;
    },

    snapArrowsToEdge:function () {
        var winSize = director.getWinSize();
        this.arrowsShouldRetain.x = ArrowsMin * winSize.width;
        this.arrowsShouldRetain.y = this.arrowsBarShouldRetain.y;
    }
});

/// LabelTTFA8Test
var LabelTTFA8Test = AtlasDemo.extend({
    ctor:function () {
        //----start22----ctor
        this._super();
        var s = director.getWinSize();

        var layer = new cc.LayerColor(cc.color(128, 128, 128, 255));
        this.addChild(layer, -10);

        // cc.LabelBMFont
        var label1 = new cc.LabelTTF("Testing A8 Format", "Arial", 48);
        this.addChild(label1);
        label1.color = cc.color(255, 0, 0);
        label1.x = s.width / 2;
        label1.y = s.height / 2;

        var fadeOut = cc.fadeOut(2);
        var fadeIn = cc.fadeIn(2);
        var seq = cc.sequence(fadeOut, fadeIn);
        var forever = seq.repeatForever();
        label1.runAction(forever);
        //----end22----
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
    ctor:function () {
        //----start12----ctor
        this._super();
        var s = director.getWinSize();

        var label1 = new cc.LabelBMFont("This is Helvetica", s_resprefix + "fonts/helvetica-32.fnt", cc.LabelAutomaticWidth, cc.TEXT_ALIGNMENT_LEFT, cc.p(0, 0));
        this.addChild(label1);
        label1.x = s.width / 2;
        label1.y = s.height * 2 / 3;

        var label2 = new cc.LabelBMFont("And this is Geneva", s_resprefix + "fonts/geneva-32.fnt", cc.LabelAutomaticWidth, cc.TEXT_ALIGNMENT_LEFT, cc.p(0, 128));
        this.addChild(label2);
        label2.x = s.width / 2;
        label2.y = s.height / 3;
        //----end12----
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
    ctor:function () {
        //----start13----ctor
        this._super();
        var chinese = "美好的一天";
        var japanese = "良い一日を";
        var spanish = "Buen día";

        var label1 = new cc.LabelBMFont(spanish, s_resprefix + "fonts/arial-unicode-26.fnt", 200, cc.TEXT_ALIGNMENT_LEFT);
        this.addChild(label1);
        label1.x = winSize.width / 2;
        label1.y = winSize.height / 4;

        var label2 = new cc.LabelBMFont(chinese, s_resprefix + "fonts/arial-unicode-26.fnt");
        this.addChild(label2);
        label2.x = winSize.width / 2;
        label2.y = winSize.height / 2.2;

        var label3 = new cc.LabelBMFont(japanese, s_resprefix + "fonts/arial-unicode-26.fnt");
        this.addChild(label3);
        label3.x = winSize.width / 2;
        label3.y = winSize.height / 1.5;
        //----end13----
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
    ctor:function () {
        //----start14----ctor
        this._super();

        var bmFont = new cc.LabelBMFont();
        bmFont.setFntFile(s_resprefix + "fonts/helvetica-32.fnt");
        bmFont.setString("It is working!");
        this.addChild(bmFont);
        bmFont.x = winSize.width / 2;
        bmFont.y = winSize.height / 2;
        //----end14----
    },
    title:function () {
        return "cc.LabelBMFont init";
    },
    subtitle:function () {
        return "Test for support of init method without parameters.";
    }
});

// LabelTTFFontInitTest
var LabelTTFFontInitTest = AtlasDemo.extend({
    ctor:function () {
        //----start23----ctor
        this._super();
        var font = new cc.LabelTTF();
        font.font = "48px 'Courier New'";
        //font.setFontName("Arial");
        font.string = "It is working!";
        this.addChild(font);
        font.x = winSize.width / 2;
        font.y = winSize.height / 2;
        //----end23----
    },
    title:function () {
        return "cc.LabelTTF init";
    },
    subtitle:function () {
        return "Test for support of init method without parameters.";
    }
});


var LabelTTFAlignment = AtlasDemo.extend({
    ctor:function () {
        //----start24----ctor
        this._super();
        var s = director.getWinSize();
        var ttf0 = new cc.LabelTTF("Alignment 0\nnew line", "Arial", 12, cc.size(256, 32), cc.TEXT_ALIGNMENT_LEFT);
        ttf0.x = s.width / 2;
        ttf0.y = (s.height / 6) * 2;
        ttf0.anchorX = 0.5;
        ttf0.anchorY = 0.5;
        this.addChild(ttf0);

        var ttf1 = new cc.LabelTTF("Alignment 1\nnew line", "Arial", 12, cc.size(256, 32), cc.TEXT_ALIGNMENT_CENTER);
        ttf1.x = s.width / 2;
        ttf1.y = (s.height / 6) * 3;
        ttf1.anchorX = 0.5;
        ttf1.anchorY = 0.5;
        this.addChild(ttf1);

        var ttf2 = new cc.LabelTTF("Alignment 2\nnew line", "Arial", 12, cc.size(256, 32), cc.TEXT_ALIGNMENT_RIGHT);
        ttf2.x = s.width / 2;
        ttf2.y = (s.height / 6) * 4;
        ttf2.anchorX = 0.5;
        ttf2.anchorY = 0.5;
        this.addChild(ttf2);
        //----end24----
    },
    title:function () {
        return "cc.LabelTTF alignment";
    },
    subtitle:function () {
        return "Tests alignment values";
    },

    //
    // Automation
    //
    getExpectedResult:function() {
        // yellow, red, green, blue, yellow
        var ret = [{"r":255,"g":255,"b":0},{"r":255,"g":0,"b":0},{"r":0,"g":255,"b":0},{"r":0,"g":0,"b":255},{"r":255,"g":255,"b":0}];
        return JSON.stringify(ret);
    },

    getCurrentResult:function() {
        var ret = [];
        for( var i=0; i<5; i++) {
            var ch = this.label.getChildByTag(i).getDisplayedColor();
            ret.push(ch);
        }

        return JSON.stringify(ret);
    }

});

var BMFontColorParentChild = AtlasDemo.extend({
    ctor:function () {
        //----start15----ctor
        this._super();

        this.label = new cc.LabelBMFont("YRGB", s_resprefix + "fonts/konqa32.fnt");
        this.addChild(this.label);
        this.label.x = winSize.width / 2;
        this.label.y = winSize.height / 2;
        this.label.color = cc.color.YELLOW;

        // R
        var letter = this.label.getChildByTag(1);
        letter.color = cc.color.RED;

        // G
        letter = this.label.getChildByTag(2);
        letter.color = cc.color.GREEN;

        // B
        letter = this.label.getChildByTag(3);
        letter.color = cc.color.BLUE;

        this.scheduleUpdate();

        this.accum = 0;
        //----end15----
    },

    update:function(dt){
        //----start15----update
        this.accum += dt;

        this.label.setString("YRGB " + parseInt(this.accum,10).toString() );
        //----end15----
    },

    title:function () {
        return "cc.LabelBMFont color parent / child";
    },
    subtitle:function () {
        return "Yellow Red Green Blue and numbers in Yellow";
    },

    //
    // Automation
    //
    getExpectedResult:function() {
        // yellow, red, green, blue, yellow
        var ret = [{"r":255,"g":255,"b":0},{"r":255,"g":0,"b":0},{"r":0,"g":255,"b":0},{"r":0,"g":0,"b":255},{"r":255,"g":255,"b":0}];
        return JSON.stringify(ret);
    },

    getCurrentResult:function() {
        var ret = [];
        for( var i=0; i<5; i++) {
            var ch = this.label.getChildByTag(i).getDisplayedColor();
            ret.push(ch);
        }

        return JSON.stringify(ret);
    }
});

var WrapAlgorithmTest = AtlasDemo.extend({
    ctor: function(){
        this._super();
        var self = this;

        var normalText = [
            "这里是中文测试例",
            "测试带有符号，换行",
            "测试中带有符号，换行",
            "",
            "Here is the English test",
            "aaaaaaaaaaaaaaaaa",
            "test test test aaa, tt",
            "test test test aa, tt",
            "こは日本語テスト",
            "符号のテストに，ついて"
        ];

        normalText.forEach(function(text, i){
            var LabelTTF = new cc.LabelTTF();
            LabelTTF.setString(text);
            LabelTTF.setPosition(30 + 150 * (i/4|0), 300 - (i%4) * 60);
            LabelTTF.setAnchorPoint(0,1);
            LabelTTF.boundingWidth = 120;
            LabelTTF.boundingHeight = 0;
            LabelTTF.enableStroke(cc.color(0, 0, 0, 1), 3.0);
            if (cc.sys.os === cc.sys.OS_WP8)
                LabelTTF.setFontName("fonts/arialuni.ttf");
            else if(cc.sys.os === cc.sys.OS_WINRT)
                LabelTTF.setFontName("DengXian");
            self.addChild(LabelTTF);
        });

        //Extreme test
        var extremeText = [
            "测",
            "\n",
            "\r\n",
            "、",
            ",",
            "W",
            "7"
        ];

        extremeText.forEach(function(text, i){
            var LabelTTF = new cc.LabelTTF();
            LabelTTF.setString(text);
            LabelTTF.setPosition(480 + i * 25, 300);
            LabelTTF.setAnchorPoint(0,1);
            LabelTTF.boundingWidth = 13;
            LabelTTF.boundingHeight = 0;
            LabelTTF.enableStroke(cc.color(0, 0, 0, 1), 3.0);
            if (cc.sys.os === cc.sys.OS_WP8)
                LabelTTF.setFontName("fonts/arialuni.ttf");
            else if(cc.sys.os === cc.sys.OS_WINRT)
                LabelTTF.setFontName("DengXian");
            self.addChild(LabelTTF);
        });

        //Combinatorial testing
        var combinatorialText = [
            "中英混排English",
            "中日混排テスト",
            "日本語テストEnglish"
        ];

        combinatorialText.forEach(function(text, i){
            var LabelTTF = new cc.LabelTTF();
            LabelTTF.setString(text);
            LabelTTF.setPosition(480 + 100 * (i/3|0), 240 - (i%3) * 60);
            LabelTTF.setAnchorPoint(0,1);
            LabelTTF.boundingWidth = 90;
            LabelTTF.boundingHeight = 0;
            LabelTTF.enableStroke(cc.color(0, 0, 0, 1), 3.0);
            if (cc.sys.os === cc.sys.OS_WP8)
                LabelTTF.setFontName("fonts/arialuni.ttf");
            else if(cc.sys.os === cc.sys.OS_WINRT)
                LabelTTF.setFontName("DengXian");
            self.addChild(LabelTTF);
        });

    },
    title: function(){
        return "Wrap algorithm test";
    },
    subtitle: function(){
        return "Wrap effect under various circumstances";
    },
    onEnter: function(){
        this._super();
        cc.SPRITE_DEBUG_DRAW = 1;
    },
    onExit: function(){
        this._super();
        cc.SPRITE_DEBUG_DRAW = 0;
    }
});

var labelTTFDrawModeTest = AtlasDemo.extend({
    ctor:function () {
        this._super();
        var cacheLabel = new cc.LabelTTF();
        cacheLabel.font = "32px 'Courier New'";
        cacheLabel.string = "This is a labelTTF \ndrawn On cached Canvas!";
        cacheLabel.setHorizontalAlignment(cc.TEXT_ALIGNMENT_CENTER);
        this.addChild(cacheLabel);
        cacheLabel.x = winSize.width / 2;
        cacheLabel.y = 3*winSize.height / 4 - cacheLabel.height;


        var directLabel = new cc.LabelTTF();
        if(cc._renderType === cc._RENDER_TYPE_CANVAS) {
            directLabel.setDrawMode(false);
            directLabel.string = "This is a labelTTF \ndrawn On Screen";
        }
        else
            directLabel.string = "WebGL does NOT support to \ndraw labelTTF on Screen";
        directLabel.font = "32px 'Courier New'";
        directLabel.setHorizontalAlignment(cc.TEXT_ALIGNMENT_CENTER);
        this.addChild(directLabel);
        directLabel.x = winSize.width / 2;
        directLabel.y = winSize.height / 4 ;
    },
    title:function () {
        return "LabelTTF DrawMode Test";
    },
    subtitle:function() {
        return "Compare cacheMode to directMode";
    }
});

//
// Flow control
//
var arrayOfLabelTest = [
    LabelAtlasOpacityTest,
    LabelAtlasOpacityColorTest,
    LabelAtlasHD,

    BMFontOpacityColorAlignmentTest,
    BMFontSubSpriteTest,
    BMFontPaddingTest,
    BMFontOffsetTest,
    BMFontTintTest,
    BMFontSpeedTest,
    BMFontMultiLineTest,
    BMFontMultiLine2Test,
    BMFontMultiLineAlignmentTest,
    BMFontOneAtlas,
    BMFontUnicode,
    BMFontInit,
    BMFontColorParentChild,
    BMFontHDTest,
    BMFontGlyphDesignerTest,
    BMFontChineseTest,

    LabelTTFTest,
    LabelTTFMultiline,
    LabelTTFChinese,
    LabelTTFA8Test,
    LabelTTFFontInitTest,
    LabelTTFAlignment,

    LabelsEmpty,
    LabelTTFStrokeShadowTest,
    labelTTFDrawModeTest
];

if (!cc.sys.isNative || cc.sys.isMobile) {
    arrayOfLabelTest.push(WrapAlgorithmTest);
}

var nextLabelTest = function () {
    labelTestIdx++;
    labelTestIdx = labelTestIdx % arrayOfLabelTest.length;

    if(window.sideIndexBar){
        labelTestIdx = window.sideIndexBar.changeTest(labelTestIdx, 19);
    }

    return new arrayOfLabelTest[labelTestIdx]();
};
var previousLabelTest = function () {
    labelTestIdx--;
    if (labelTestIdx < 0)
        labelTestIdx += arrayOfLabelTest.length;

    if(window.sideIndexBar){
        labelTestIdx = window.sideIndexBar.changeTest(labelTestIdx, 19);
    }

    return new arrayOfLabelTest[labelTestIdx]();
};
var restartLabelTest = function () {
    return new arrayOfLabelTest[labelTestIdx]();
};
