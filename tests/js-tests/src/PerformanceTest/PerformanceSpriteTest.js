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
var MAX_SPRITES = 10000;
var SPRITES_INCREASE = 500;

if ( !cc.sys.isNative) {
   if(cc.sys.isMobile){
       MAX_SPRITES = 3000;
       SPRITES_INCREASE = 50;
   }
}

var TAG_INFO_LAYER = 1;
var TAG_MAIN_LAYER = 2;
var TAG_SPRITE_MENU_LAYER = (MAX_SPRITES + 1000);

var s_nSpriteCurCase = 0;

////////////////////////////////////////////////////////
//
// SubTest
//
////////////////////////////////////////////////////////
var SubTest = cc.Class.extend({
    _subtestNumber:null,
    _batchNode:null,
    _parent:null,
    removeByTag:function (tag) {
        switch (this._subtestNumber) {
            case 1:
            case 4:
            case 7:
                this._parent.removeChildByTag(tag + 100, true);
                break;
            case 2:
            case 3:
            case 5:
            case 6:
            case 8:
            case 9:
                this._batchNode.removeChildAtIndex(tag, true);
                break;
            default:
                break;
        }
    },
    createSpriteWithTag:function (tag) {
// create
        if( "opengl" in cc.sys.capabilities )
            cc.Texture2D.defaultPixelFormat = cc.Texture2D.PIXEL_FORMAT_RGBA8888;

        var sprite = null;
        switch (this._subtestNumber) {
            case 1:
            {
                sprite = new cc.Sprite("Images/grossinis_sister1.png");
                this._parent.addChild(sprite, 0, tag + 100);
                break;
            }
            case 2:
            case 3:
            {
                sprite = new cc.Sprite(this._batchNode.texture, cc.rect(0, 0, 52, 139));
                this._batchNode.addChild(sprite, 0, tag + 100);
                break;
            }
            case 4:
            {
                var idx = parseInt(Math.random() * 14) + 1;
                idx = idx < 10 ? "0" + idx : idx.toString();
                var str = "Images/grossini_dance_" + idx + ".png";
                sprite = new cc.Sprite(str);
                this._parent.addChild(sprite, 0, tag + 100);
                break;
            }
            case 5:
            case 6:
            {
                var idx = 0 | (Math.random() * 14);
                var x = (idx % 5) * 85;
                var y = (0 | (idx / 5)) * 121;
                sprite = new cc.Sprite(this._batchNode.texture, cc.rect(x, y, 85, 121));
                this._batchNode.addChild(sprite, 0, tag + 100);
                break;
            }

            case 7:
            {
                var y, x;
                var r = 0 | (Math.random() * 64);

                y = parseInt(r / 8);
                x = parseInt(r % 8);

                var str = "Images/sprites_test/sprite-" + x + "-" + y + ".png";
                sprite = new cc.Sprite(str);
                this._parent.addChild(sprite, 0, tag + 100);
                break;
            }

            case 8:
            case 9:
            {
                var y, x;
                var r = 0 | (Math.random() * 64);

                y = (0 | (r / 8)) * 32;
                x = (r % 8) * 32;
                sprite = new cc.Sprite(this._batchNode.texture, cc.rect(x, y, 32, 32));
                this._batchNode.addChild(sprite, 0, tag + 100);
                break;
            }

            default:
                break;
        }

        if( "opengl" in cc.sys.capabilities )
            cc.Texture2D.defaultPixelFormat = cc.Texture2D.PIXEL_FORMAT_DEFAULT;

        return sprite;
    },
    initWithSubTest:function (subTest, p) {
        this._subtestNumber = subTest;
        this._parent = p;
        this._batchNode = null;
        /*
         * Tests:
         * 1: 1 (32-bit) PNG sprite of 52 x 139
         * 2: 1 (32-bit) PNG Batch Node using 1 sprite of 52 x 139
         * 3: 1 (16-bit) PNG Batch Node using 1 sprite of 52 x 139
         * 4: 1 (4-bit) PVRTC Batch Node using 1 sprite of 52 x 139

         * 5: 14 (32-bit) PNG sprites of 85 x 121 each
         * 6: 14 (32-bit) PNG Batch Node of 85 x 121 each
         * 7: 14 (16-bit) PNG Batch Node of 85 x 121 each
         * 8: 14 (4-bit) PVRTC Batch Node of 85 x 121 each

         * 9: 64 (32-bit) sprites of 32 x 32 each
         *10: 64 (32-bit) PNG Batch Node of 32 x 32 each
         *11: 64 (16-bit) PNG Batch Node of 32 x 32 each
         *12: 64 (4-bit) PVRTC Batch Node of 32 x 32 each
         */

        // purge textures
        //
        //		[mgr removeAllTextures];
        if ( cc.sys.isNative) {
            var mgr = cc.textureCache;
            mgr.removeTexture(mgr.addImage("Images/grossinis_sister1.png"));
            mgr.removeTexture(mgr.addImage("Images/grossini_dance_atlas.png"));
            mgr.removeTexture(mgr.addImage("Images/spritesheet1.png"));
        }

        switch (this._subtestNumber) {
            case 1:
            case 4:
            case 7:
                break;
            ///
            case 2:
                if( "opengl" in cc.sys.capabilities )
                    cc.Texture2D.defaultPixelFormat = cc.Texture2D.PIXEL_FORMAT_RGBA8888;
                this._batchNode = new cc.SpriteBatchNode("Images/grossinis_sister1.png", 500);
                p.addChild(this._batchNode, 0);
                break;
            case 3:
                if( "opengl" in cc.sys.capabilities )
                    cc.Texture2D.defaultPixelFormat = cc.Texture2D.PIXEL_FORMAT_RGBA4444;
                this._batchNode = new cc.SpriteBatchNode("Images/grossinis_sister1.png", 500);
                p.addChild(this._batchNode, 0);
                break;

            ///
            case 5:
                if( "opengl" in cc.sys.capabilities )
                    cc.Texture2D.defaultPixelFormat = cc.Texture2D.PIXEL_FORMAT_RGBA8888;
                this._batchNode = new cc.SpriteBatchNode("Images/grossini_dance_atlas.png", 500);
                p.addChild(this._batchNode, 0);
                break;
            case 6:
                if( "opengl" in cc.sys.capabilities )
                    cc.Texture2D.defaultPixelFormat = cc.Texture2D.PIXEL_FORMAT_RGBA4444;
                this._batchNode = new cc.SpriteBatchNode("Images/grossini_dance_atlas.png", 500);
                p.addChild(this._batchNode, 0);
                break;

            ///
            case 8:
                if( "opengl" in cc.sys.capabilities )
                    cc.Texture2D.defaultPixelFormat = cc.Texture2D.PIXEL_FORMAT_RGBA8888;
                this._batchNode = new cc.SpriteBatchNode("Images/spritesheet1.png", 500);
                p.addChild(this._batchNode, 0);
                break;
            case 9:
                if( "opengl" in cc.sys.capabilities )
                    cc.Texture2D.defaultPixelFormat = cc.Texture2D.PIXEL_FORMAT_RGBA4444;
                this._batchNode = new cc.SpriteBatchNode("Images/spritesheet1.png", 500);
                p.addChild(this._batchNode, 0);
                break;

            default:
                break;
        }

        if( "opengl" in cc.sys.capabilities )
            cc.Texture2D.defaultPixelFormat = cc.Texture2D.PIXEL_FORMAT_DEFAULT;
    }
});

////////////////////////////////////////////////////////
//
// SpriteMenuLayer
//
////////////////////////////////////////////////////////
var SpriteMenuLayer = PerformBasicLayer.extend({
    _maxCases:7,
    showCurrentTest:function () {
        var scene = null;
        var preScene = this.parent;
        var subTest = preScene.getSubTestNum();
        var nodes = preScene.getNodesNum();

        Math.seedrandom('perftest');

        switch (this._curCase) {
            case 0:
                scene = new SpritePerformTest1();
                break;
            case 1:
                scene = new SpritePerformTest2();
                break;
            case 2:
                scene = new SpritePerformTest3();
                break;
            case 3:
                scene = new SpritePerformTest4();
                break;
            case 4:
                scene = new SpritePerformTest5();
                break;
            case 5:
                scene = new SpritePerformTest6();
                break;
            case 6:
                scene = new SpritePerformTest7();
                break;
        }
        s_nSpriteCurCase = this._curCase;

        if (scene) {
            scene.initWithSubTest(subTest, nodes);
            cc.director.runScene(scene);
        }
    }
});

////////////////////////////////////////////////////////
//
// SpriteMainScene
//
////////////////////////////////////////////////////////
var SpriteMainScene = cc.Scene.extend({
    _lastRenderedCount:null,
    _quantityNodes:null,
    _subTest:null,
    _subtestNumber:1,
    ctor:function() {
        this._super();
        this.init();
    },

    title:function () {
        return "No title";
    },
    initWithSubTest:function (asubtest, nodes) {
        this._subtestNumber = asubtest;
        this._subTest = new SubTest();
        this._subTest.initWithSubTest(asubtest, this);

        var s = cc.director.getWinSize();

        this._lastRenderedCount = 0;
        this._quantityNodes = 0;

        // add title label
        var label = new cc.LabelTTF(this.title(), "Arial", 40);
        this.addChild(label, 1);
        label.x = s.width / 2;
        label.y = s.height - 32;
        label.color = cc.color(255, 255, 40);

        cc.MenuItemFont.setFontSize(65);
        var decrease = new cc.MenuItemFont(" - ", this.onDecrease, this);
        decrease.color = cc.color(0, 200, 20);
        var increase = new cc.MenuItemFont(" + ", this.onIncrease, this);
        increase.color = cc.color(0, 200, 20);

        var menu = new cc.Menu(decrease, increase);
        menu.alignItemsHorizontally();

        menu.x = s.width / 2;

        menu.y = s.height - 65;
        this.addChild(menu, 1);

        var infoLabel = new cc.LabelTTF("0 nodes", "Marker Felt", 30);
        infoLabel.color = cc.color(0, 200, 20);
        infoLabel.x = s.width / 2;
        infoLabel.y = s.height - 90;
        this.addChild(infoLabel, 1, TAG_INFO_LAYER);

        // add menu
        var menu = new SpriteMenuLayer(true, 7, s_nSpriteCurCase);
        this.addChild(menu, 1, TAG_SPRITE_MENU_LAYER);

        // Sub Tests
        cc.MenuItemFont.setFontSize(32);
        var subMenu = new cc.Menu();
        for (var i = 1; i <= 9; ++i) {
            var text = i.toString();
            var itemFont = new cc.MenuItemFont(text, this.testNCallback, this);
            itemFont.tag = i;
            subMenu.addChild(itemFont, 10);

            if (i <= 3)
                itemFont.color = cc.color(200, 20, 20);
            else if (i <= 6)
                itemFont.color = cc.color(0, 200, 20);
            else
                itemFont.color = cc.color(0, 20, 200);
        }

        subMenu.alignItemsHorizontally();
        subMenu.x = s.width / 2;
        subMenu.y = 80;
        this.addChild(subMenu, 2);

        while (this._quantityNodes < nodes) {
            this.onIncrease(this);
        }
    },
    updateNodes:function () {
        if (this._quantityNodes != this._lastRenderedCount) {
            var infoLabel = this.getChildByTag(TAG_INFO_LAYER);
            var str = this._quantityNodes + " nodes";
            infoLabel.setString(str);

            this._lastRenderedCount = this._quantityNodes;
        }
    },
    testNCallback:function (sender) {
        this._subtestNumber = sender.tag;
        var menu = this.getChildByTag(TAG_SPRITE_MENU_LAYER);
        menu.restartCallback(sender);
    },
    onIncrease:function (sender) {
        if (this._quantityNodes >= MAX_SPRITES)
            return;

        for (var i = 0; i < SPRITES_INCREASE; i++) {
            var sprite = this._subTest.createSpriteWithTag(this._quantityNodes);
            this.doTest(sprite);
            this._quantityNodes++;
        }

        this.updateNodes();
    },
    onDecrease:function (sender) {
        if (this._quantityNodes <= 0)
            return;

        for (var i = 0; i < SPRITES_INCREASE; i++) {
            this._quantityNodes--;
            this._subTest.removeByTag(this._quantityNodes);
        }

        this.updateNodes();
    },

    doTest:function (sprite) {

    },

    getSubTestNum:function () {
        return this._subtestNumber
    },
    getNodesNum:function () {
        return this._quantityNodes
    }
});


////////////////////////////////////////////////////////
//
// For test functions
//
////////////////////////////////////////////////////////
function performanceActions(sprite) {
    var size = cc.director.getWinSize();
    sprite.x = parseInt(Math.random() * size.width);
    sprite.y = parseInt(Math.random() * size.height);

    var period = 0.5 + (Math.random() * 1000) / 500.0;
    var rot = cc.rotateBy(period, 360.0 * Math.random());
    var rot_back = rot.reverse();
    var permanentRotation = cc.sequence(rot, rot_back).repeatForever();
    sprite.runAction(permanentRotation);

    var growDuration = 0.5 + (Math.random() * 1000) / 500.0;
    var grow = cc.scaleBy(growDuration, 0.5, 0.5);
    var permanentScaleLoop = cc.sequence(grow, grow.reverse()).repeatForever();
    sprite.runAction(permanentScaleLoop);
}

function performanceActions20(sprite) {
    var size = cc.director.getWinSize();
    if (Math.random() < 0.2) {
        sprite.x = parseInt(Math.random() * size.width);
        sprite.y = parseInt(Math.random() * size.height);
    }
    else {
        sprite.x = -1000;
        sprite.y = -1000;
    }

    var period = 0.5 + (Math.random() * 1000) / 500.0;
    var rot = cc.rotateBy(period, 360.0 * Math.random());
    var rot_back = rot.reverse();
    var permanentRotation = cc.sequence(rot, rot_back).repeatForever();
    sprite.runAction(permanentRotation);

    var growDuration = 0.5 + (Math.random() * 1000) / 500.0;
    var grow = cc.scaleBy(growDuration, 0.5, 0.5);
    var permanentScaleLoop = cc.sequence(grow, grow.reverse()).repeatForever();
    sprite.runAction(permanentScaleLoop);
}

function performanceRotationScale(sprite) {
    var size = cc.director.getWinSize();
    sprite.x = parseInt(Math.random() * size.width);
    sprite.y = parseInt(Math.random() * size.height);
    sprite.rotation = Math.random() * 360;
    sprite.scale = Math.random() * 2;
}

function performancePosition(sprite) {
    var size = cc.director.getWinSize();
    sprite.x = parseInt(Math.random() * size.width);
    sprite.y = parseInt(Math.random() * size.height);
}

function performanceout20(sprite) {
    var size = cc.director.getWinSize();

    if (Math.random() < 0.2) {
        sprite.x = parseInt(Math.random() * size.width);
        sprite.y = parseInt(Math.random() * size.height);
    }
    else {
        sprite.x = -1000;
        sprite.y = -1000;
    }
}

function performanceOut100(sprite) {
    sprite.x = -1000;
    sprite.y = -1000;
}

function performanceScale(sprite) {
    var size = cc.director.getWinSize();
    sprite.x = parseInt(Math.random() * size.width);
    sprite.y = parseInt(Math.random() * size.height);
    sprite.scale = Math.random() * 100 / 50;
}


////////////////////////////////////////////////////////
//
// SpritePerformTest1
//
////////////////////////////////////////////////////////
var SpritePerformTest1 = SpriteMainScene.extend({
    doTest:function (sprite) {
        performancePosition(sprite);
    },
    title:function () {
        return "A (" + this._subtestNumber + ") position";
    }
});

////////////////////////////////////////////////////////
//
// SpritePerformTest2
//
////////////////////////////////////////////////////////
var SpritePerformTest2 = SpriteMainScene.extend({
    doTest:function (sprite) {
        performanceScale(sprite);
    },
    title:function () {
        return "B (" + this._subtestNumber + ") scale";
    }
});

////////////////////////////////////////////////////////
//
// SpritePerformTest3
//
////////////////////////////////////////////////////////
var SpritePerformTest3 = SpriteMainScene.extend({
    doTest:function (sprite) {
        performanceRotationScale(sprite);
    },
    title:function () {
        return "C (" + this._subtestNumber + ") scale + rot";
    }
});

////////////////////////////////////////////////////////
//
// SpritePerformTest4
//
////////////////////////////////////////////////////////
var SpritePerformTest4 = SpriteMainScene.extend({
    doTest:function (sprite) {
        performanceOut100(sprite);
    },
    title:function () {
        return "D (" + this._subtestNumber + ") 100% out";
    }
});

////////////////////////////////////////////////////////
//
// SpritePerformTest5
//
////////////////////////////////////////////////////////
var SpritePerformTest5 = SpriteMainScene.extend({
    doTest:function (sprite) {
        performanceout20(sprite);
    },
    title:function () {
        return "E (" + this._subtestNumber + ") 80% out";
    }
});

////////////////////////////////////////////////////////
//
// SpritePerformTest6
//
////////////////////////////////////////////////////////
var SpritePerformTest6 = SpriteMainScene.extend({
    doTest:function (sprite) {
        performanceActions(sprite);
    },
    title:function () {
        return "F (" + this._subtestNumber + ") actions";
    }
});

////////////////////////////////////////////////////////
//
// SpritePerformTest7
//
////////////////////////////////////////////////////////
var SpritePerformTest7 = SpriteMainScene.extend({
    doTest:function (sprite) {
        performanceActions20(sprite);
    },
    title:function () {
        return "G (" + this._subtestNumber + ") actions 80% out";
    }
});

function runSpriteTest() {
    Math.seedrandom('perftest');

    var scene = new SpritePerformTest1;
    scene.initWithSubTest(1, 50);
    cc.director.runScene(scene);
}
