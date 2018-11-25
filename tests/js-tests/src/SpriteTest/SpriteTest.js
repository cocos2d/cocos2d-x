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
var TAG_TILE_MAP = 1;
var TAG_SPRITE_BATCH_NODE = 1;
var TAG_NODE = 2;
var TAG_ANIMATION1 = 1;
var TAG_SPRITE_LEFT = 2;
var TAG_SPRITE_RIGHT = 3;

var TAG_SPRITE1 = 0;
var TAG_SPRITE2 = 1;
var TAG_SPRITE3 = 2;
var TAG_SPRITE4 = 3;
var TAG_SPRITE5 = 4;
var TAG_SPRITE6 = 5;
var TAG_SPRITE7 = 6;
var TAG_SPRITE8 = 7;

var IDC_NEXT = 100;
var IDC_BACK = 101;
var IDC_RESTART = 102;

var spriteTestIdx = -1;

var spriteFrameCache = cc.spriteFrameCache;

//------------------------------------------------------------------
//
// SpriteTestDemo
//
//------------------------------------------------------------------
var SpriteTestDemo = BaseTestLayer.extend({
    _title:"",
    _subtitle:"",

    ctor:function () {
        if (arguments.length === 0) {
            this._super(cc.color(0, 0, 0, 255), cc.color(98, 99, 117, 255));
        } else {
            this._super.apply(this, arguments);
        }
    },

    onRestartCallback:function (sender) {
        var s = new SpriteTestScene();
        s.addChild(restartSpriteTest());
        director.runScene(s);
    },

    onNextCallback:function (sender) {
        var s = new SpriteTestScene();
        s.addChild(nextSpriteTest());
        director.runScene(s);
    },

    onBackCallback:function (sender) {
        var s = new SpriteTestScene();
        s.addChild(previousSpriteTest());
        director.runScene(s);
    },

    // automation
    numberOfPendingTests:function () {
        return ( (arrayOfSpriteTest.length - 1) - spriteTestIdx );
    },

    getTestNumber:function () {
        return spriteTestIdx;
    }
});

//------------------------------------------------------------------
//
// Sprite1
//
//------------------------------------------------------------------
var Sprite1 = SpriteTestDemo.extend({
    _title:"Non Batched Sprite ",
    _subtitle:"Tap screen to add more sprites",

    ctor:function () {
        //----start0----ctor
        this._super();

        this.addNewSpriteWithCoords(cc.p(winSize.width / 2, winSize.height / 2));

        if ('touches' in cc.sys.capabilities) {
            cc.eventManager.addListener({
                event: cc.EventListener.TOUCH_ALL_AT_ONCE,
                onTouchesEnded: function(touches, event){
                    for (var it = 0; it < touches.length; it++) {
                        var touch = touches[it];
                        if (!touch)
                            break;

                        var location = touch.getLocation();
                        event.getCurrentTarget().addNewSpriteWithCoords(location);
                    }
                }
            }, this);
        } else if ('mouse' in cc.sys.capabilities)
            cc.eventManager.addListener({
                event: cc.EventListener.MOUSE,
                onMouseUp: function(event){
                    event.getCurrentTarget().addNewSpriteWithCoords(event.getLocation());
                }
            }, this);
        //----end0----
    },

    addNewSpriteWithCoords:function (p) {
        //----start0----addNewSpriteWithCoords
        var idx = 0 | (Math.random() * 14);
        var x = (idx % 5) * 85;
        var y = (0 | (idx / 5)) * 121;
        var sprite = new cc.Sprite(s_grossini_dance_atlas, cc.rect(x, y, 85, 121));
        this.addChild(sprite);
        sprite.x = p.x;
        sprite.y = p.y;

        var action;
        var random = Math.random();
        if (random < 0.20) {
            action = cc.scaleBy(3, 2);
        } else if (random < 0.40) {
            action = cc.rotateBy(3, 360);
        } else if (random < 0.60) {
            action = cc.blink(1, 3);
        } else if (random < 0.8) {
            action = cc.tintBy(2, 0, -255, -255);
        } else {
            action = cc.fadeOut(2);
        }

        var action_back = action.reverse();
        var seq = cc.sequence(action, action_back);

        sprite.runAction(seq.repeatForever());
        this.testSprite = sprite;
        //----end0----
    },
    //
    // Automation
    //
    testDuration:1,
    pixel:{"0":51, "1":0, "2":51, "3":255},
    testSprite:null,
    setupAutomation:function () {
        var fun = function () {
            var sprite = new cc.Sprite(s_grossini_dance_atlas, cc.rect(0, 0, 85, 121));
            this.addChild(sprite, 999);
            sprite.x = winSize.width / 2;
            sprite.y = winSize.height / 2;
        };
        this.scheduleOnce(fun, 0.5);
    },
    getExpectedResult:function () {
        var ret = {"useBatch":false, "pixel":"yes"};
        return JSON.stringify(ret);
    },
    getCurrentResult:function () {
        var ret1 = this.readPixels(winSize.width / 2, winSize.height / 2, 5, 5);
        var ret = {"useBatch":this.testSprite.getBatchNode() != null, "pixel":this.containsPixel(ret1, this.pixel) ? "yes" : "no"};
        return JSON.stringify(ret);
    }
});

//------------------------------------------------------------------
//
// SpriteBatchNode1
//
//------------------------------------------------------------------
var SpriteBatchNode1 = SpriteTestDemo.extend({

    _title:"Batched Sprite ",
    _subtitle:"Tap screen to add more sprites",

    ctor:function () {
        //----start1----ctor
        this._super();
        if ('touches' in cc.sys.capabilities) {
            cc.eventManager.addListener({
                event: cc.EventListener.TOUCH_ALL_AT_ONCE,
                onTouchesEnded: function (touches, event) {
                    for (var it = 0; it < touches.length; it++) {
                        var touch = touches[it];
                        if (!touch)
                            break;

                        var location = touch.getLocation();
                        event.getCurrentTarget().addNewSpriteWithCoords(location);
                    }
                }
            }, this);
        } else if ('mouse' in cc.sys.capabilities)
            cc.eventManager.addListener({
                event: cc.EventListener.MOUSE,
                onMouseUp: function(event){
                    event.getCurrentTarget().addNewSpriteWithCoords(event.getLocation());
                }
            }, this);

        var batchNode = new cc.SpriteBatchNode(s_grossini_dance_atlas, 50);
        this.addChild(batchNode, 0, TAG_SPRITE_BATCH_NODE);
        this.addNewSpriteWithCoords(cc.p(winSize.width / 2, winSize.height / 2));
        //----end1----
    },

    addNewSpriteWithCoords:function (p) {
        //----start1----addNewSpriteWithCoords
        var batchNode = this.getChildByTag(TAG_SPRITE_BATCH_NODE);

        var idx = 0 | (Math.random() * 14);
        var x = (idx % 5) * 85;
        var y = (0 | (idx / 5)) * 121;

        var sprite = new cc.Sprite(batchNode.texture, cc.rect(x, y, 85, 121));
        batchNode.addChild(sprite);

        sprite.x = p.x;

        sprite.y = p.y;

        var action;
        var random = Math.random();

        if (random < 0.20)
            action = cc.scaleBy(3, 2);
        else if (random < 0.40)
            action = cc.rotateBy(3, 360);
        else if (random < 0.60)
            action = cc.blink(1, 3);
        else if (random < 0.8)
            action = cc.tintBy(2, 0, -255, -255);
        else
            action = cc.fadeOut(2);

        var action_back = action.reverse();
        var seq = cc.sequence(action, action_back);

        sprite.runAction(seq.repeatForever());
        this.testSprite = sprite;
        //----end1----
    },

    //
    // Automation
    //
    testDuration:1,
    pixel:{"0":51, "1":0, "2":51, "3":255},
    testSprite:null,
    setupAutomation:function () {
        var fun = function () {
            var sprite = new cc.Sprite(s_grossini_dance_atlas, cc.rect(0, 0, 85, 121));
            this.addChild(sprite, 999);
            sprite.x = winSize.width / 2;
            sprite.y = winSize.height / 2;
        }
        this.scheduleOnce(fun, 0.5);
    },
    getExpectedResult:function () {
        var ret = {"useBatch":true, "pixel":"yes"};
        return JSON.stringify(ret);
    },
    getCurrentResult:function () {
        var ret1 = this.readPixels(winSize.width / 2, winSize.height / 2, 5, 5);
        var ret = {"useBatch":this.testSprite.getBatchNode() != null, "pixel":this.containsPixel(ret1, this.pixel) ? "yes" : "no"};
        return JSON.stringify(ret);
    }
});

//------------------------------------------------------------------
//
// SpriteColorOpacity
//
//------------------------------------------------------------------
var SpriteColorOpacity = SpriteTestDemo.extend({

    _title:"Sprite: Color & Opacity",

    ctor:function () {
        //----start11----ctor
        this._super();
        var sprite1 = new cc.Sprite(s_grossini_dance_atlas, cc.rect(0, 121, 85, 121));
        var sprite2 = new cc.Sprite(s_grossini_dance_atlas, cc.rect(85, 121, 85, 121));
        var sprite3 = new cc.Sprite(s_grossini_dance_atlas, cc.rect(85 * 2, 121, 85, 121));
        var sprite4 = new cc.Sprite(s_grossini_dance_atlas, cc.rect(85 * 3, 121, 85, 121));

        var sprite5 = new cc.Sprite(s_grossini_dance_atlas, cc.rect(0, 121, 85, 121));
        var sprite6 = new cc.Sprite(s_grossini_dance_atlas, cc.rect(85, 121, 85, 121));
        var sprite7 = new cc.Sprite(s_grossini_dance_atlas, cc.rect(85 * 2, 121, 85, 121));
        var sprite8 = new cc.Sprite(s_grossini_dance_atlas, cc.rect(85 * 3, 121, 85, 121));

        sprite1.x = (winSize.width / 5);

        sprite1.y = (winSize.height / 3);
        sprite2.x = (winSize.width / 5) * 2;
        sprite2.y = (winSize.height / 3);
        sprite3.x = (winSize.width / 5) * 3;
        sprite3.y = (winSize.height / 3);
        sprite4.x = (winSize.width / 5) * 4;
        sprite4.y = (winSize.height / 3);
        sprite5.x = (winSize.width / 5);
        sprite5.y = (winSize.height / 3) * 2;
        sprite6.x = (winSize.width / 5) * 2;
        sprite6.y = (winSize.height / 3) * 2;
        sprite7.x = (winSize.width / 5) * 3;
        sprite7.y = (winSize.height / 3) * 2;
        sprite8.x = (winSize.width / 5) * 4;
        sprite8.y = (winSize.height / 3) * 2;

        var delay = cc.delayTime(0.25);
        var action = cc.fadeOut(2);
        var action_back = action.reverse();
        var fade = cc.sequence(action, delay.clone(), action_back).repeatForever();

        var tintRed = cc.tintBy(2, 0, -255, -255);
        var tintRedBack = tintRed.reverse();
        var red = cc.sequence(tintRed, delay.clone(), tintRedBack).repeatForever();

        var tintGreen = cc.tintBy(2, -255, 0, -255);
        var tintGreenBack = tintGreen.reverse();
        var green = cc.sequence(tintGreen, delay.clone(), tintGreenBack).repeatForever();

        var tintBlue = cc.tintBy(2, -255, -255, 0);
        var tintBlueBack = tintBlue.reverse();
        var blue = cc.sequence(tintBlue, delay.clone(), tintBlueBack).repeatForever();

        // late add: test dirtyColor and dirtyPosition
        this.addChild(sprite1, 0, TAG_SPRITE1);
        this.addChild(sprite2, 0, TAG_SPRITE2);
        this.addChild(sprite3, 0, TAG_SPRITE3);
        this.addChild(sprite4, 0, TAG_SPRITE4);
        this.addChild(sprite5, 0, TAG_SPRITE5);
        this.addChild(sprite6, 0, TAG_SPRITE6);
        this.addChild(sprite7, 0, TAG_SPRITE7);
        this.addChild(sprite8, 0, TAG_SPRITE8);

        sprite5.runAction(red);
        sprite6.runAction(green);
        sprite7.runAction(blue);
        sprite8.runAction(fade);

        this.schedule(this.removeAndAddSprite, 2);
        //----end11----
    },
    // this function test if remove and add works as expected:
//   color array and vertex array should be reindexed
    removeAndAddSprite:function (dt) {
        //----start11----removeAndAddSprite
        var sprite = this.getChildByTag(TAG_SPRITE5);

        this.removeChild(sprite, false);
        this.addChild(sprite, 0, TAG_SPRITE5);
        //----end11----
    },
    //
    // Automation
    //
    testDuration:2.1,
    pixel1:{"0":255, "1":0, "2":0, "3":255},
    pixel2:{"0":0, "1":204, "2":0, "3":255},
    pixel3:{"0":0, "1":0, "2":153, "3":255},
    pixel4:{"0":255, "1":204, "2":153, "3":255},
    getExpectedResult:function () {
        var ret = {"pixel1":"yes", "pixel2":"yes", "pixel3":"yes", "pixel4":"yes"};
        return JSON.stringify(ret);
    },
    getCurrentResult:function () {
        var ret1 = this.readPixels((winSize.width / 5) * 1, (winSize.height / 3) * 2 + 40, 5, 5);
        var ret2 = this.readPixels((winSize.width / 5) * 2, (winSize.height / 3) * 2 + 40, 5, 5);
        var ret3 = this.readPixels((winSize.width / 5) * 3, (winSize.height / 3) * 2 + 40, 5, 5);
        var ret4 = this.readPixels((winSize.width / 5) * 4, (winSize.height / 3) * 2 + 40, 5, 5);
        var ret = {"pixel1":this.containsPixel(ret1, this.pixel1) ? "yes" : "no",
            "pixel2":this.containsPixel(ret2, this.pixel2) ? "yes" : "no",
            "pixel3":this.containsPixel(ret3, this.pixel3) ? "yes" : "no",
            "pixel4":this.containsPixel(ret4, this.pixel4) ? "yes" : "no"};
        return JSON.stringify(ret);
    }
});

//------------------------------------------------------------------
//
// SpriteBatchNodeColorOpacity
//
//------------------------------------------------------------------
var SpriteBatchNodeColorOpacity = SpriteTestDemo.extend({

    _title:"SpriteBatchNode: Color & Opacity",

    ctor:function () {
        //----start12----ctor
        this._super();
        // small capacity. Testing resizing.
        // Don't use capacity=1 in your real game. It is expensive to resize the capacity
        var batch = new cc.SpriteBatchNode(s_grossini_dance_atlas, 1);
        this.addChild(batch, 0, TAG_SPRITE_BATCH_NODE);

        var sprite1 = new cc.Sprite(batch.texture, cc.rect(0, 121, 85, 121));
        var sprite2 = new cc.Sprite(batch.texture, cc.rect(85, 121, 85, 121));
        var sprite3 = new cc.Sprite(batch.texture, cc.rect(85 * 2, 121, 85, 121));
        var sprite4 = new cc.Sprite(batch.texture, cc.rect(85 * 3, 121, 85, 121));

        var sprite5 = new cc.Sprite(batch.texture, cc.rect(0, 121, 85, 121));
        var sprite6 = new cc.Sprite(batch.texture, cc.rect(85, 121, 85, 121));
        var sprite7 = new cc.Sprite(batch.texture, cc.rect(85 * 2, 121, 85, 121));
        var sprite8 = new cc.Sprite(batch.texture, cc.rect(85 * 3, 121, 85, 121));


        sprite1.x = (winSize.width / 5) * 1;
        sprite1.y = (winSize.height / 3) * 1;
        sprite2.x = (winSize.width / 5) * 2;
        sprite2.y = (winSize.height / 3) * 1;
        sprite3.x = (winSize.width / 5) * 3;
        sprite3.y = (winSize.height / 3) * 1;
        sprite4.x = (winSize.width / 5) * 4;
        sprite4.y = (winSize.height / 3) * 1;
        sprite5.x = (winSize.width / 5) * 1;
        sprite5.y = (winSize.height / 3) * 2;
        sprite6.x = (winSize.width / 5) * 2;
        sprite6.y = (winSize.height / 3) * 2;
        sprite7.x = (winSize.width / 5) * 3;
        sprite7.y = (winSize.height / 3) * 2;
        sprite8.x = (winSize.width / 5) * 4;
        sprite8.y = (winSize.height / 3) * 2;

        var delay = cc.delayTime(0.25);
        var action = cc.fadeOut(2);
        var action_back = action.reverse();
        var fade = cc.sequence(action, delay.clone(), action_back).repeatForever();

        var tintRed = cc.tintBy(2, 0, -255, -255);
        var red = cc.sequence(tintRed, delay.clone(), tintRed.reverse()).repeatForever();

        var tintGreen = cc.tintBy(2, -255, 0, -255);
        var tintGreenBack = tintGreen.reverse();
        var green = cc.sequence(tintGreen, delay.clone(), tintGreenBack).repeatForever();

        var tintBlue = cc.tintBy(2, -255, -255, 0);
        var tintBlueBack = tintBlue.reverse();
        var blue = cc.sequence(tintBlue, delay.clone(), tintBlueBack).repeatForever();

        // late add: test dirtyColor and dirtyPosition
        batch.addChild(sprite1, 0, TAG_SPRITE1);
        batch.addChild(sprite2, 0, TAG_SPRITE2);
        batch.addChild(sprite3, 0, TAG_SPRITE3);
        batch.addChild(sprite4, 0, TAG_SPRITE4);
        batch.addChild(sprite5, 0, TAG_SPRITE5);
        batch.addChild(sprite6, 0, TAG_SPRITE6);
        batch.addChild(sprite7, 0, TAG_SPRITE7);
        batch.addChild(sprite8, 0, TAG_SPRITE8);

        sprite5.runAction(red);
        sprite6.runAction(green);
        sprite7.runAction(blue);
        sprite8.runAction(fade);

        this.schedule(this.removeAndAddSprite, 2);
        //----end12----
    },
    // this function test if remove and add works as expected:
    //   color array and vertex array should be reindexed
    removeAndAddSprite:function (dt) {
        //----start12----removeAndAddSprite
        var batch = this.getChildByTag(TAG_SPRITE_BATCH_NODE);
        var sprite = batch.getChildByTag(TAG_SPRITE5);

        batch.removeChild(sprite, false);
        batch.addChild(sprite, 0, TAG_SPRITE5);
        //----end12----
    },
    //
    // Automation
    //
    testDuration:2.1,
    pixel1:{"0":255, "1":0, "2":0, "3":255},
    pixel2:{"0":0, "1":204, "2":0, "3":255},
    pixel3:{"0":0, "1":0, "2":153, "3":255},
    pixel4:{"0":255, "1":204, "2":153, "3":255},
    getExpectedResult:function () {
        var ret = {"pixel1":"yes", "pixel2":"yes", "pixel3":"yes", "pixel4":"yes"};
        return JSON.stringify(ret);
    },
    getCurrentResult:function () {
        var ret1 = this.readPixels((winSize.width / 5) * 1, (winSize.height / 3) * 2 + 40, 5, 5);
        var ret2 = this.readPixels((winSize.width / 5) * 2, (winSize.height / 3) * 2 + 40, 5, 5);
        var ret3 = this.readPixels((winSize.width / 5) * 3, (winSize.height / 3) * 2 + 40, 5, 5);
        var ret4 = this.readPixels((winSize.width / 5) * 4, (winSize.height / 3) * 2 + 40, 5, 5);
        var ret = {"pixel1":this.containsPixel(ret1, this.pixel1) ? "yes" : "no",
            "pixel2":this.containsPixel(ret2, this.pixel2) ? "yes" : "no",
            "pixel3":this.containsPixel(ret3, this.pixel3) ? "yes" : "no",
            "pixel4":this.containsPixel(ret4, this.pixel4) ? "yes" : "no"};
        return JSON.stringify(ret);
    }

});

//------------------------------------------------------------------
//
// SpriteZOrder
//
//------------------------------------------------------------------
var SpriteZOrder = SpriteTestDemo.extend({
    _dir:0,
    _title:"Sprite: Z order",
    ctor:function () {
        //----start13----ctor
        this._super();
        this._dir = 1;

        var sprite;
        var step = winSize.width / 11;
        for (var i = 0; i < 5; i++) {
            sprite = new cc.Sprite(s_grossini_dance_atlas, cc.rect(85 * 0, 121 * 1, 85, 121));
            sprite.x = (i + 1) * step;
            sprite.y = winSize.height / 2;
            this.addChild(sprite, i);
        }

        for (i = 5; i < 10; i++) {
            sprite = new cc.Sprite(s_grossini_dance_atlas, cc.rect(85 * 1, 121 * 0, 85, 121));
            sprite.x = (i + 1) * step;
            sprite.y = winSize.height / 2;
            this.addChild(sprite, 14 - i);
        }

        sprite = new cc.Sprite(s_grossini_dance_atlas, cc.rect(85 * 3, 121 * 0, 85, 121));
        this.addChild(sprite, -1, TAG_SPRITE1);
        sprite.x = winSize.width / 2;
        sprite.y = winSize.height / 2 - 20;
        sprite.scaleX = 10;
        sprite.color = cc.color.RED;

        this.schedule(this.reorderSprite, 1);
        //----end13----
    },
    reorderSprite:function (dt) {
        //----start13----reorderSprite
        var sprite = this.getChildByTag(TAG_SPRITE1);
        var z = sprite.zIndex;
        if (z < -1)
            this._dir = 1;
        if (z > 10)
            this._dir = -1;
        z += this._dir * 3;
        this.reorderChild(sprite, z);
        //----end13----
    },
    //
    // Automation
    //
    testDuration:4.2,
    pixel:{"0":255, "1":0, "2":0, "3":255},
    getExpectedResult:function () {
        var ret = {"pixel":"yes"};
        return JSON.stringify(ret);
    },
    getCurrentResult:function () {
        var step = winSize.width / 11;
        var ret1 = this.readPixels((6 + 1) * step, winSize.height / 2 + 10, 5, 5);
        var ret = {"pixel":this.containsPixel(ret1, this.pixel) ? "yes" : "no"};
        return JSON.stringify(ret);
    }
});

//------------------------------------------------------------------
//
// SpriteBatchNodeZOrder
//
//------------------------------------------------------------------
var SpriteBatchNodeZOrder = SpriteTestDemo.extend({
    _dir:0,
    _title:"SpriteBatch: Z order",
    ctor:function () {
        //----start14----ctor
        this._super();
        this._dir = 1;

        // small capacity. Testing resizing.
        // Don't use capacity=1 in your real game. It is expensive to resize the capacity
        var batch = new cc.SpriteBatchNode(s_grossini_dance_atlas, 1);
        this.addChild(batch, 0, TAG_SPRITE_BATCH_NODE);

        var sprite;
        var step = winSize.width / 11;
        for (var i = 0; i < 5; i++) {
            sprite = new cc.Sprite(batch.texture, cc.rect(85 * 0, 121 * 1, 85, 121));
            sprite.x = (i + 1) * step;
            sprite.y = winSize.height / 2;
            batch.addChild(sprite, i);
        }

        for (i = 5; i < 10; i++) {
            sprite = new cc.Sprite(batch.texture, cc.rect(85 * 1, 121 * 0, 85, 121));
            sprite.x = (i + 1) * step;
            sprite.y = winSize.height / 2;
            batch.addChild(sprite, 14 - i);
        }

        sprite = new cc.Sprite(batch.texture, cc.rect(85 * 3, 121 * 0, 85, 121));
        batch.addChild(sprite, -1, TAG_SPRITE1);
        sprite.x = winSize.width / 2;
        sprite.y = winSize.height / 2 - 20;
        sprite.scaleX = 10;
        sprite.color = cc.color.RED;
        this.schedule(this.reorderSprite, 1);
        //----end14----
    },
    reorderSprite:function (dt) {
        //----start14----reorderSprite
        var batch = this.getChildByTag(TAG_SPRITE_BATCH_NODE);
        var sprite = batch.getChildByTag(TAG_SPRITE1);
        var z = sprite.zIndex;
        if (z < -1)
            this._dir = 1;
        if (z > 10)
            this._dir = -1;
        z += this._dir * 3;
        batch.reorderChild(sprite, z);
        //----end14----
    },
    //
    // Automation
    //
    testDuration:4.2,
    pixel:{"0":255, "1":0, "2":0, "3":255},
    getExpectedResult:function () {
        var ret = {"pixel":"yes"};
        return JSON.stringify(ret);
    },
    getCurrentResult:function () {
        var step = winSize.width / 11;
        var ret1 = this.readPixels((6 + 1) * step, winSize.height / 2 + 10, 5, 5);
        var ret = {"pixel":this.containsPixel(ret1, this.pixel) ? "yes" : "no"};
        return JSON.stringify(ret);
    }
});

//------------------------------------------------------------------
//
// SpriteBatchNodeReorderIssue744
//
//------------------------------------------------------------------
var SpriteBatchNodeReorderIssue744 = SpriteTestDemo.extend({
    _title:"SpriteBatchNode: reorder issue #744",
    _subtitle:"Should not crash",

    ctor:function () {
        //----start16----ctor
        this._super();

        // Testing issue #744
        // http://code.google.com/p/cocos2d-iphone/issues/detail?id=744
        var batch = new cc.SpriteBatchNode(s_grossini_dance_atlas, 15);
        this.addChild(batch, 0, TAG_SPRITE_BATCH_NODE);

        var sprite = new cc.Sprite(batch.texture, cc.rect(0, 0, 85, 121));
        sprite.x = winSize.width / 2;
        sprite.y = winSize.height / 2;
        batch.addChild(sprite, 3);
        batch.reorderChild(sprite, 1);
        //----end16----
    },
    //
    // Automation
    //
    testDuration:1.2,
    pixel:{"0":51, "1":0, "2":51, "3":255},
    getExpectedResult:function () {
        var ret = {"pixel":"yes"};
        return JSON.stringify(ret);
    },
    getCurrentResult:function () {
        var ret1 = this.readPixels(winSize.width / 2, winSize.height / 2, 5, 5);
        var ret = {"pixel":this.containsPixel(ret1, this.pixel) ? "yes" : "no"};
        return JSON.stringify(ret);
    }
});

//------------------------------------------------------------------
//
// SpriteBatchNodeReorderIssue766
//
//------------------------------------------------------------------
var SpriteBatchNodeReorderIssue766 = SpriteTestDemo.extend({
    _batchNode:null,
    _sprite1:null,
    _sprite2:null,
    _sprite3:null,

    _title:"SpriteBatchNode: reorder issue #766",
    _subtitle:"In 2 seconds 1 sprite will be reordered",

    ctor:function () {
        //----start17----ctor
        this._super();
        this._batchNode = new cc.SpriteBatchNode(s_piece, 15);
        this.addChild(this._batchNode, 1, 0);

        this._sprite1 = this.makeSpriteZ(2);
        this._sprite1.x = 200;
        this._sprite1.y = 160;

        this._sprite2 = this.makeSpriteZ(3);
        this._sprite2.x = 264;
        this._sprite2.y = 160;

        this._sprite3 = this.makeSpriteZ(4);
        this._sprite3.x = 328;
        this._sprite3.y = 160;

        this.schedule(this.reorderSprite, 2);
        //----end17----
    },
    reorderSprite:function (dt) {
        //----start17----reorderSprite
        this.unschedule(this.reorderSprite);

        this._batchNode.reorderChild(this._sprite1, 4);
        //----end17----
    },
    makeSpriteZ:function (aZ) {
        //----start17----makeSpriteZ
        var sprite = new cc.Sprite(this._batchNode.texture, cc.rect(128, 0, 64, 64));
        this._batchNode.addChild(sprite, aZ + 1, 0);

        //children
        var spriteShadow = new cc.Sprite(this._batchNode.texture, cc.rect(0, 0, 64, 64));
        spriteShadow.opacity = 128;
        sprite.addChild(spriteShadow, aZ, 3);

        var spriteTop = new cc.Sprite(this._batchNode.texture, cc.rect(64, 0, 64, 64));
        sprite.addChild(spriteTop, aZ + 2, 3);

        return sprite;
        //----end17----
    },
    //
    // Automation
    //
    testDuration:2.2,
    pixel1:{"0":0, "1":0, "2":0, "3":255},
    pixel2:{"0":255, "1":255, "2":255, "3":255},
    getExpectedResult:function () {
        var ret = {"pixel1":"yes", "pixel2":"yes"};
        return JSON.stringify(ret);
    },
    getCurrentResult:function () {
        var ret1 = this.readPixels(213, 159, 5, 5);
        var ret2 = this.readPixels(211, 108, 5, 5);
        var ret = {"pixel1":!this.containsPixel(ret1, this.pixel1) ? "yes" : "no",
            "pixel2":this.containsPixel(ret2, this.pixel2) ? "yes" : "no"};
        return JSON.stringify(ret);
    }
});

//------------------------------------------------------------------
//
// SpriteBatchNodeReorderIssue767
//
//------------------------------------------------------------------
var SpriteBatchNodeReorderIssue767 = SpriteTestDemo.extend({
    _title:"SpriteBatchNode: reorder issue #767",
    _subtitle:"Should not crash",

    ctor:function () {
        //----start18----ctor
        this._super();

        spriteFrameCache.addSpriteFrames(s_ghostsPlist, s_ghosts);
        //
        // SpriteBatchNode: 3 levels of children
        //
        var aParent = new cc.SpriteBatchNode(s_ghosts);
        this.addChild(aParent, 0, TAG_SPRITE1);

        // parent
        var l1 = new cc.Sprite(spriteFrameCache.getSpriteFrame("father.gif"));
        l1.x = winSize.width / 2;
        l1.y = winSize.height / 2;
        aParent.addChild(l1, 0, TAG_SPRITE2);
        var l1W = l1.width, l1H = l1.height;

        // child left
        var l2a = new cc.Sprite(spriteFrameCache.getSpriteFrame("sister1.gif"));
        l2a.x = -25 + l1W / 2;
        l2a.y = 0 + l1H / 2;
        l1.addChild(l2a, -1, TAG_SPRITE_LEFT);
        var l2aW = l2a.width, l2aH = l2a.height;


        // child right
        var l2b = new cc.Sprite(spriteFrameCache.getSpriteFrame("sister2.gif"));
        l2b.x = 25 + l1W / 2;
        l2b.y = 0 + l1H / 2;
        l1.addChild(l2b, 1, TAG_SPRITE_RIGHT);
        var l2bW = l2b.width, l2bH = l2b.height;


        // child left bottom
        var l3a1 = new cc.Sprite(spriteFrameCache.getSpriteFrame("child1.gif"));
        l3a1.scale = 0.65;
        l3a1.x = 0 + l2aW / 2;
        l3a1.y = -50 + l2aH / 2;
        l2a.addChild(l3a1, -1);

        // child left top
        var l3a2 = new cc.Sprite(spriteFrameCache.getSpriteFrame("child1.gif"));
        l3a2.scale = 0.65;
        l3a2.x = 0 + l2aW / 2;
        l3a2.y = +50 + l2aH / 2;
        l2a.addChild(l3a2, 1);

        // child right bottom
        var l3b1 = new cc.Sprite(spriteFrameCache.getSpriteFrame("child1.gif"));
        l3b1.scale = 0.65;
        l3b1.x = 0 + l2bW / 2;
        l3b1.y = -50 + l2bH / 2;
        l2b.addChild(l3b1, -1);

        // child right top
        var l3b2 = new cc.Sprite(spriteFrameCache.getSpriteFrame("child1.gif"));
        l3b2.scale = 0.65;
        l3b2.x = 0 + l2bW / 2;
        l3b2.y = +50 + l2bH / 2;
        l2b.addChild(l3b2, 1);

        this.schedule(this.reorderSprites, 1);
        //----end18----
    },
    reorderSprites:function (dt) {
        //----start18----reorderSprites
        var spritebatch = this.getChildByTag(TAG_SPRITE1);
        var father = spritebatch.getChildByTag(TAG_SPRITE2);
        var left = father.getChildByTag(TAG_SPRITE_LEFT);
        var right = father.getChildByTag(TAG_SPRITE_RIGHT);

        var newZLeft = 1;

        if (left.zIndex === 1)
            newZLeft = -1;

        father.reorderChild(left, newZLeft);
        father.reorderChild(right, -newZLeft);
        //----end18----
    },
    //
    // Automation
    //
    testDuration:1.5,
    pixel1:{"0":255, "1":204, "2":153, "3":255},
    pixel2:{"0":255, "1":255, "2":255, "3":255},
    curPixel1:null,
    curPixel2:null,
    setupAutomation:function () {
        var fun = function(){
            this.curPixel1 = this.readPixels(winSize.width / 2 + 11, winSize.height / 2 - 11, 2, 2);
        }
        this.scheduleOnce(fun, 0.5);
    },
    getExpectedResult:function () {
        var ret = {"pixel1":"yes", "pixel2":"yes"};
        return JSON.stringify(ret);
    },
    getCurrentResult:function () {
        this.curPixel2 = this.readPixels(winSize.width / 2 + 11, winSize.height / 2 - 11, 2, 2);
        var ret = {"pixel1":this.containsPixel(this.curPixel1, this.pixel1) ? "yes" : "no",
            "pixel2":this.containsPixel(this.curPixel2, this.pixel2) ? "yes" : "no"};
        return JSON.stringify(ret);
    }
});

//------------------------------------------------------------------
//
// SpriteAnchorPoint
//
//------------------------------------------------------------------
var SpriteAnchorPoint = SpriteTestDemo.extend({
    _title:"Sprite: anchor point",

    ctor:function () {
        //----start4----ctor
        this._super();

        for (var i = 0; i < 3; i++) {
            var rotate = cc.rotateBy(10, 360);
            var action = rotate.repeatForever();
            var sprite = new cc.Sprite(s_grossini_dance_atlas, cc.rect(85 * i, 121, 85, 121));
            sprite.x = winSize.width / 4 * (i + 1);
            sprite.y = winSize.height / 2;

            var point = new cc.Sprite(s_pathR1);
            point.scale = 0.25;
            point.x = sprite.x;
            point.y = sprite.y;
            this.addChild(point, 10);

            switch (i) {
                case 0:
                    sprite.anchorX = 0;
                    sprite.anchorY = 0;
                    break;
                case 1:
                    sprite.anchorX = 0.5;
                    sprite.anchorY = 0.5;
                    break;
                case 2:
                    sprite.anchorX = 1;
                    sprite.anchorY = 1;
                    break;
            }

            point.x = sprite.x;

            point.y = sprite.y;

            //var copy = action.clone();
            sprite.runAction(action);
            this.addChild(sprite, i);
        }
        //----end4----
    },
    //
    // Automation
    //
    testDuration:0.15,
    pixel:{"0":255, "1":204, "2":153, "3":255},
    getExpectedResult:function () {
        var ret = {"pixel1":"yes", "pixel2":"yes", "pixel3":"yes"};
        return JSON.stringify(ret);
    },
    getCurrentResult:function () {
        var ret1 = this.readPixels(winSize.width / 4 + 45, winSize.height / 2 + 104, 5, 5);
        var ret2 = this.readPixels(winSize.width / 4 * 2 - 3, winSize.height / 2 + 44, 5, 5);
        var ret3 = this.readPixels(winSize.width / 4 * 3 - 44, winSize.height / 2 - 16, 5, 5);
        var ret = {"pixel1":this.containsPixel(ret1, this.pixel) ? "yes" : "no", "pixel2":this.containsPixel(ret2, this.pixel) ? "yes" : "no", "pixel3":this.containsPixel(ret3, this.pixel) ? "yes" : "no"};
        return JSON.stringify(ret);
    }
});

//------------------------------------------------------------------
//
// SpriteBatchNodeAnchorPoint
//
//------------------------------------------------------------------
var SpriteBatchNodeAnchorPoint = SpriteTestDemo.extend({
    _title:"SpriteBatchNode: anchor point",

    ctor:function () {
        //----start5----ctor
        this._super();
        // small capacity. Testing resizing.
        // Don't use capacity=1 in your real game. It is expensive to resize the capacity
        var batch = new cc.SpriteBatchNode(s_grossini_dance_atlas, 1);
        this.addChild(batch, 0, TAG_SPRITE_BATCH_NODE);

        for (var i = 0; i < 3; i++) {
            var rotate = cc.rotateBy(10, 360);
            var action = rotate.repeatForever();
            var sprite = new cc.Sprite(batch.texture, cc.rect(85 * i, 121, 85, 121));
            sprite.x = winSize.width / 4 * (i + 1);
            sprite.y = winSize.height / 2;

            var point = new cc.Sprite(s_pathR1);
            point.scale = 0.25;
            point.x = sprite.x;
            point.y = sprite.y;
            this.addChild(point, 1);

            switch (i) {
                case 0:
                    sprite.anchorX = 0;
                    sprite.anchorY = 0;
                    break;
                case 1:
                    sprite.anchorX = 0.5;
                    sprite.anchorY = 0.5;
                    break;
                case 2:
                    sprite.anchorX = 1;
                    sprite.anchorY = 1;
                    break;
            }

            point.x = sprite.x;

            point.y = sprite.y;
            sprite.runAction(action);
            batch.addChild(sprite, i);
        }
        //----end5----
    },
    //
    // Automation
    //
    testDuration:0.15,
    pixel:{"0":255, "1":204, "2":153, "3":255},
    getExpectedResult:function () {
        var ret = {"pixel1":"yes", "pixel2":"yes", "pixel3":"yes"};
        return JSON.stringify(ret);
    },
    getCurrentResult:function () {
        var ret1 = this.readPixels(winSize.width / 4 + 45, winSize.height / 2 + 104, 5, 5);
        var ret2 = this.readPixels(winSize.width / 4 * 2 - 3, winSize.height / 2 + 44, 5, 5);
        var ret3 = this.readPixels(winSize.width / 4 * 3 - 44, winSize.height / 2 - 16, 5, 5);
        var ret = {"pixel1":this.containsPixel(ret1, this.pixel) ? "yes" : "no", "pixel2":this.containsPixel(ret2, this.pixel) ? "yes" : "no", "pixel3":this.containsPixel(ret3, this.pixel) ? "yes" : "no"};
        return JSON.stringify(ret);
    }
});

//------------------------------------------------------------------
//
// Sprite6
//
//------------------------------------------------------------------
var Sprite6 = SpriteTestDemo.extend({
    _title:"SpriteBatchNode transformation",

    ctor:function () {
        //----start21----ctor
        this._super();
        // small capacity. Testing resizing
        // Don't use capacity=1 in your real game. It is expensive to resize the capacity
        var batch = new cc.SpriteBatchNode(s_grossini_dance_atlas, 1);
        this.addChild(batch, 0, TAG_SPRITE_BATCH_NODE);
        batch.ignoreAnchorPointForPosition(true);

        batch.anchorX = 0.5;

        batch.anchorY = 0.5;
        batch.width = winSize.width;
	    batch.height = winSize.height;

        // SpriteBatchNode actions
        var rotate1 = cc.rotateBy(5, 360);
        var rotate_back = rotate1.reverse();
        var rotate_seq = cc.sequence(rotate1, rotate_back);
        var rotate_forever = rotate_seq.repeatForever();

        var scale = cc.scaleBy(5, 1.5);
        var scale_back = scale.reverse();
        var scale_seq = cc.sequence(scale, scale_back);
        var scale_forever = scale_seq.repeatForever();

        for (var i = 0; i < 3; i++) {
            var sprite = new cc.Sprite(batch.texture, cc.rect(85 * i, 121, 85, 121));
            switch (i) {
                case 0:
                    sprite.x = winSize.width / 2 - 100;
                    sprite.y = winSize.height / 2;
                    break;
                case 1:
                    sprite.x = winSize.width / 2;
                    sprite.y = winSize.height / 2;
                    break;
                case 2:
                    sprite.x = winSize.width / 2 + 100;
                    sprite.y = winSize.height / 2;
                    break;
            }
            var rotate = cc.rotateBy(5, 360);
            var action = rotate.repeatForever();
            sprite.runAction(action.clone());
            batch.addChild(sprite, i);
        }

        batch.runAction(scale_forever);
        batch.runAction(rotate_forever);
        //----end21----
    },
    // Automation
    testDuration:2,
    pixel:{"0":255, "1":204, "2":153, "3":255},
    getExpectedResult:function () {
        var ret = {"pixel1":"yes", "pixel2":"yes"};
        return JSON.stringify(ret);
    },
    getCurrentResult:function () {
        var ret1 = this.readPixels(winSize.width / 2 + 111, winSize.height / 2 + 82, 5, 5);
        var ret2 = this.readPixels(winSize.width / 2 - 148, winSize.height / 2 - 58, 5, 5);
        var ret = {"pixel1":this.containsPixel(ret1, this.pixel, false) ? "yes" : "no",
            "pixel2":this.containsPixel(ret2, this.pixel, false) ? "yes" : "no"};
        return JSON.stringify(ret);
    }
});

//------------------------------------------------------------------
//
// SpriteFlip
//
//------------------------------------------------------------------
var SpriteFlip = SpriteTestDemo.extend({
    _title:"Sprite Flip X & Y",

    ctor:function () {
        //----start22----ctor
        this._super();
        var sprite1 = new cc.Sprite(s_grossini_dance_atlas, cc.rect(85, 121, 85, 121));
        sprite1.x = winSize.width / 2 - 100;
        sprite1.y = winSize.height / 2;
        this.addChild(sprite1, 0, TAG_SPRITE1);

        var sprite2 = new cc.Sprite(s_grossini_dance_atlas, cc.rect(85, 121, 85, 121));
        sprite2.x = winSize.width / 2 + 100;
        sprite2.y = winSize.height / 2;
        this.addChild(sprite2, 0, TAG_SPRITE2);

        this.schedule(this.onFlipSprites, 1);
        //----end22----
    },
    onFlipSprites:function (dt) {
        //----start22----onFlipSprites
        var sprite1 = this.getChildByTag(TAG_SPRITE1);
        var sprite2 = this.getChildByTag(TAG_SPRITE2);

        sprite1.flippedX = !sprite1.flippedX;
        sprite2.flippedY = !sprite2.flippedY;
        //----end22----
    },
    //
    // Automation
    //
    testDuration:1.5,
    pixel:{"0":255, "1":204, "2":153, "3":255},
    pixel1:null,
    pixel2:null,
    pixel3:null,
    pixel4:null,
    setupAutomation:function () {
        this.scheduleOnce(this.getBeforePixel, 0.5);
    },
    getBeforePixel:function () {
        this.pixel1 = this.readPixels(winSize.width / 2 - 131, winSize.height / 2 - 11, 5, 5);
        this.pixel2 = this.readPixels(winSize.width / 2 + 100, winSize.height / 2 + 44, 5, 5);
    },
    getExpectedResult:function () {
        var ret = {"pixel1":"yes", "pixel2":"yes", "pixel3":"yes", "pixel4":"yes"};
        return JSON.stringify(ret);
    },
    getCurrentResult:function () {
        this.pixel3 = this.readPixels(winSize.width / 2 - 69, winSize.height / 2 - 11, 5, 5);
        this.pixel4 = this.readPixels(winSize.width / 2 + 100, winSize.height / 2 - 44, 5, 5);
        var ret = {"pixel1":this.containsPixel(this.pixel1, this.pixel) ? "yes" : "no",
            "pixel2":this.containsPixel(this.pixel2, this.pixel) ? "yes" : "no",
            "pixel3":this.containsPixel(this.pixel3, this.pixel) ? "yes" : "no",
            "pixel4":this.containsPixel(this.pixel4, this.pixel) ? "yes" : "no"};
        return JSON.stringify(ret);
    }
});

//------------------------------------------------------------------
//
// SpriteBatchNodeFlip
//
//------------------------------------------------------------------
var SpriteBatchNodeFlip = SpriteTestDemo.extend({
    _title:"SpriteBatchNode Flip X & Y",

    ctor:function () {
        //----start23----ctor
        this._super();
        var batch = new cc.SpriteBatchNode(s_grossini_dance_atlas, 10);
        this.addChild(batch, 0, TAG_SPRITE_BATCH_NODE);

        var sprite1 = new cc.Sprite(batch.texture, cc.rect(85, 121, 85, 121));
        sprite1.x = winSize.width / 2 - 100;
        sprite1.y = winSize.height / 2;
        batch.addChild(sprite1, 0, TAG_SPRITE1);

        var sprite2 = new cc.Sprite(batch.texture, cc.rect(85, 121, 85, 121));
        sprite2.x = winSize.width / 2 + 100;
        sprite2.y = winSize.height / 2;
        batch.addChild(sprite2, 0, TAG_SPRITE2);

        this.schedule(this.onFlipSprites, 1);
        //----end23----
    },
    onFlipSprites:function (dt) {
        //----start23----onFlipSprites
        var batch = this.getChildByTag(TAG_SPRITE_BATCH_NODE);
        var sprite1 = batch.getChildByTag(TAG_SPRITE1);
        var sprite2 = batch.getChildByTag(TAG_SPRITE2);

        sprite1.flippedX = !sprite1.flippedX;
        sprite2.flippedY = !sprite2.flippedY;
        //----end23----
    },
    //
    // Automation
    //
    testDuration:1.5,
    pixel:{"0":255, "1":204, "2":153, "3":255},
    pixel1:null,
    pixel2:null,
    pixel3:null,
    pixel4:null,
    setupAutomation:function () {
        this.scheduleOnce(this.getBeforePixel, 0.5);
    },
    getBeforePixel:function () {
        this.pixel1 = this.readPixels(winSize.width / 2 - 131, winSize.height / 2 - 11, 5, 5);
        this.pixel2 = this.readPixels(winSize.width / 2 + 100, winSize.height / 2 + 44, 5, 5);
    },
    getExpectedResult:function () {
        var ret = {"pixel1":"yes", "pixel2":"yes", "pixel3":"yes", "pixel4":"yes"};
        return JSON.stringify(ret);
    },
    getCurrentResult:function () {
        this.pixel3 = this.readPixels(winSize.width / 2 - 69, winSize.height / 2 - 11, 5, 5);
        this.pixel4 = this.readPixels(winSize.width / 2 + 100, winSize.height / 2 - 44, 5, 5);
        var ret = {"pixel1":this.containsPixel(this.pixel1, this.pixel) ? "yes" : "no",
            "pixel2":this.containsPixel(this.pixel2, this.pixel) ? "yes" : "no",
            "pixel3":this.containsPixel(this.pixel3, this.pixel) ? "yes" : "no",
            "pixel4":this.containsPixel(this.pixel4, this.pixel) ? "yes" : "no"};
        return JSON.stringify(ret);
    }
});

//------------------------------------------------------------------
//
// SpriteAliased
//
//------------------------------------------------------------------
var SpriteAliased = SpriteTestDemo.extend({
    _title:"Sprite Aliased",
    _subtitle:"You should see pixelated sprites",

    ctor:function () {
        //----start24----ctor
        this._super();
        var sprite1 = new cc.Sprite(s_grossini_dance_atlas, cc.rect(85, 121, 85, 121));
        sprite1.x = winSize.width / 2 - 100;
        sprite1.y = winSize.height / 2;
        this.addChild(sprite1, 0, TAG_SPRITE1);

        var sprite2 = new cc.Sprite(s_grossini_dance_atlas, cc.rect(85, 121, 85, 121));
        sprite2.x = winSize.width / 2 + 100;
        sprite2.y = winSize.height / 2;
        this.addChild(sprite2, 0, TAG_SPRITE2);

        var scale = cc.scaleBy(2, 5);
        var scale_back = scale.reverse();
        var seq = cc.sequence(scale, scale_back);
        var repeat = seq.repeatForever();

        var scale2 = cc.scaleBy(2, 5);
        var scale_back2 = scale2.reverse();
        var seq2 = cc.sequence(scale2, scale_back2);
        var repeat2 = seq2.repeatForever();

        sprite1.runAction(repeat);
        sprite2.runAction(repeat2);
        //----end24----
    },
    onEnter:function () {
        //----start24----onEnter
        this._super();
        //
        // IMPORTANT:
        // This change will affect every sprite that uses the same texture
        // So sprite1 and sprite2 will be affected by this change
        //
        if (!cc.sys.isNative && !("opengl" in cc.sys.capabilities && cc._renderType === cc.game.RENDER_TYPE_WEBGL)) {
            var label = new cc.LabelTTF("Not supported on HTML5-canvas", "Times New Roman", 30);
            this.addChild(label);
            label.x = winSize.width / 2;
            label.y = winSize.height / 2;
        } else {
            var sprite = this.getChildByTag(TAG_SPRITE1);
            sprite.texture.setAliasTexParameters();
        }

        //----end24----
    },
    onExit:function () {
        //----start24----onExit
        if (cc.sys.isNative || ("opengl" in cc.sys.capabilities && cc._renderType === cc.game.RENDER_TYPE_WEBGL)) {
            var sprite = this.getChildByTag(TAG_SPRITE1);
            sprite.texture.setAntiAliasTexParameters();
        }
        this._super();
        //----end24----
    }
});

//------------------------------------------------------------------
//
// SpriteBatchNodeAliased
//
//------------------------------------------------------------------
var SpriteBatchNodeAliased = SpriteTestDemo.extend({
    _title:"SpriteBatchNode Aliased",
    _subtitle:"You should see pixelated sprites",

    ctor:function () {
        //----start25----ctor
        this._super();
        var batch = new cc.SpriteBatchNode(s_grossini_dance_atlas, 10);
        this.addChild(batch, 0, TAG_SPRITE_BATCH_NODE);

        var sprite1 = new cc.Sprite(batch.texture, cc.rect(85, 121, 85, 121));
        sprite1.x = winSize.width / 2 - 100;
        sprite1.y = winSize.height / 2;
        batch.addChild(sprite1, 0, TAG_SPRITE1);

        var sprite2 = new cc.Sprite(batch.texture, cc.rect(85, 121, 85, 121));
        sprite2.x = winSize.width / 2 + 100;
        sprite2.y = winSize.height / 2;
        batch.addChild(sprite2, 0, TAG_SPRITE2);

        var scale = cc.scaleBy(2, 5);
        var scale_back = scale.reverse();
        var seq = cc.sequence(scale, scale_back);
        var repeat = seq.repeatForever();

        var scale2 = cc.scaleBy(2, 5);
        var scale_back2 = scale2.reverse();
        var seq2 = cc.sequence(scale2, scale_back2);
        var repeat2 = seq2.repeatForever();

        sprite1.runAction(repeat);
        sprite2.runAction(repeat2);
        //----end25----
    },
    onEnter:function () {
        //----start25----onEnter
        this._super();
        //
        // IMPORTANT:
        // This change will affect every sprite that uses the same texture
        // So sprite1 and sprite2 will be affected by this change
        //
        if (!cc.sys.isNative && !("opengl" in cc.sys.capabilities && cc._renderType === cc.game.RENDER_TYPE_WEBGL)) {
            var label = new cc.LabelTTF("Not supported on HTML5-canvas", "Times New Roman", 30);
            this.addChild(label);
            label.x = winSize.width / 2;
            label.y = winSize.height / 2;
        } else {
            var sprite = this.getChildByTag(TAG_SPRITE_BATCH_NODE);
            sprite.texture.setAliasTexParameters();
        }
        //----end25----

    },
    onExit:function () {
        //----start25----onExit
        if (cc.sys.isNative || ("opengl" in cc.sys.capabilities && cc._renderType === cc.game.RENDER_TYPE_WEBGL)) {
            var sprite = this.getChildByTag(TAG_SPRITE_BATCH_NODE);
            sprite.texture.setAntiAliasTexParameters();
        }
        this._super();
        //----end25----
    }
});

//------------------------------------------------------------------
//
// SpriteNewTexture
//
//------------------------------------------------------------------
var SpriteNewTexture = SpriteTestDemo.extend({
    _usingTexture1:false,
    _texture1:null,
    _texture2:null,
    _title:"Sprite New texture (tap)",

    ctor:function () {
        //----start26----ctor
        this._super();

        if ('touches' in cc.sys.capabilities){
            cc.eventManager.addListener({
                event: cc.EventListener.TOUCH_ALL_AT_ONCE,
                onTouchesEnded:function (touches, event) {
                    event.getCurrentTarget().onChangeTexture();
                }
            }, this);
        } else if ('mouse' in cc.sys.capabilities)
            cc.eventManager.addListener({
                event: cc.EventListener.MOUSE,
                onMouseUp: function(event){
                    event.getCurrentTarget().onChangeTexture();
                }
            }, this);

        var node = new cc.Node();
        this.addChild(node, 0, TAG_SPRITE_BATCH_NODE);

        this._texture1 = cc.textureCache.addImage(s_grossini_dance_atlas);
        this._texture2 = cc.textureCache.addImage(s_grossini_dance_atlas_mono);

        this._usingTexture1 = true;

        for (var i = 0; i < 30; i++) {
            this.addNewSprite();
        }
        //----end26----
    },

    addNewSprite:function () {
        //----start26----addNewSprite
        var p = cc.p(Math.random() * winSize.width, Math.random() * winSize.height);

        var idx = 0 | (Math.random() * 14);
        var x = (idx % 5) * 85;
        var y = (0 | (idx / 5)) * 121;


        var node = this.getChildByTag(TAG_SPRITE_BATCH_NODE);
        var sprite = new cc.Sprite(this._texture1, cc.rect(x, y, 85, 121));
        node.addChild(sprite);

        sprite.x = p.x;

        sprite.y = p.y;

        var action;
        var random = Math.random();

        if (random < 0.20)
            action = cc.scaleBy(3, 2);
        else if (random < 0.40)
            action = cc.rotateBy(3, 360);
        else if (random < 0.60)
            action = cc.blink(1, 3);
        // else if (random < 0.8)
        //     action = cc.tintBy(2, 0, -255, -255);
        else
            action = cc.fadeOut(2);

        var action_back = action.reverse();
        var seq = cc.sequence(action, action_back);

        sprite.runAction(seq.repeatForever());
        //----end26----
    },

    onChangeTexture:function () {
        //----start26----onChangeTexture
        var node = this.getChildByTag(TAG_SPRITE_BATCH_NODE);
        var children = node.children, sprite, i;

        if (this._usingTexture1) {                         //-. win32 : Let's it make just simple sentence
            for (i = 0; i < children.length; i++) {
                sprite = children[i];
                if (!sprite)
                    break;
                sprite.texture = this._texture2;
            }
            this._usingTexture1 = false;
        } else {
            for (i = 0; i < children.length; i++) {
                sprite = children[i];
                if (!sprite)
                    break;
                sprite.texture = this._texture1;
            }
            this._usingTexture1 = true;
        }
        //----end26----
    },

    //
    // Automation
    //
    testDuration:1,
    pixel:{"0":51, "1":0, "2":51, "3":255},
    setupAutomation:function () {
        this.scheduleOnce(this.addTestSprite, 0.5);
    },
    addTestSprite:function () {
        var node = this.getChildByTag(TAG_SPRITE_BATCH_NODE);
        var sprite = new cc.Sprite(this._texture1, cc.rect(0, 0, 85, 121));
        sprite.x = winSize.width / 2;
        sprite.y = winSize.height / 2;
        node.addChild(sprite);
    },
    getExpectedResult:function () {
        var ret = {"pixel":"yes"};
        return JSON.stringify(ret);
    },
    getCurrentResult:function () {
        var ret1 = this.readPixels(winSize.width / 2, winSize.height / 2, 5, 5);
        var ret = {"pixel":this.containsPixel(ret1, this.pixel) ? "yes" : "no"};
        return JSON.stringify(ret);
    }
});

//------------------------------------------------------------------
//
// SpriteBatchNodeNewTexture
//
//------------------------------------------------------------------
var SpriteBatchNodeNewTexture = SpriteTestDemo.extend({
    _texture1:null,
    _texture2:null,
    _title:"SpriteBatchNode new texture (tap)",

    ctor:function () {
        //----start27----ctor
        this._super();
        if ('touches' in cc.sys.capabilities){
            cc.eventManager.addListener({
                event: cc.EventListener.TOUCH_ALL_AT_ONCE,
                onTouchesEnded:function (touches, event) {
                    event.getCurrentTarget().onChangeTexture();
                }
            }, this);
        } else if ('mouse' in cc.sys.capabilities)
           cc.eventManager.addListener({
               event: cc.EventListener.MOUSE,
               onMouseUp: function(event){
                   event.getCurrentTarget().onChangeTexture();
               }
           }, this);

        var batch = new cc.SpriteBatchNode(s_grossini_dance_atlas, 50);
        this.addChild(batch, 0, TAG_SPRITE_BATCH_NODE);

        this._texture1 = batch.texture;
        this._texture2 = cc.textureCache.addImage(s_grossini_dance_atlas_mono);

        for (var i = 0; i < 30; i++) {
            this.addNewSprite();
        }
        //----end27----
    },
    addNewSprite:function () {
        //----start27----addNewSprite
        var s = winSize;

        var p = cc.p(Math.random() * winSize.width, Math.random() * winSize.height);

        var batch = this.getChildByTag(TAG_SPRITE_BATCH_NODE);

        var idx = 0 | (Math.random() * 14);
        var x = (idx % 5) * 85;
        var y = (0 | (idx / 5)) * 121;

        var sprite = new cc.Sprite(batch.texture, cc.rect(x, y, 85, 121));
        batch.addChild(sprite);

        sprite.x = p.x;

        sprite.y = p.y;

        var action;
        var random = Math.random();

        if (random < 0.20)
            action = cc.scaleBy(3, 2);
        else if (random < 0.40)
            action = cc.rotateBy(3, 360);
        else if (random < 0.60)
            action = cc.blink(1, 3);
        //else if (random < 0.8)
        //    action = cc.tintBy(2, 0, -255, -255);
        else
            action = cc.fadeOut(2);
        var action_back = action.reverse();
        var seq = cc.sequence(action, action_back);

        sprite.runAction(seq.repeatForever());
        //----end27----
    },
    onChangeTexture:function () {
        //----start27----onChangeTexture
        var batch = this.getChildByTag(TAG_SPRITE_BATCH_NODE);

        if (batch.texture == this._texture1)
            batch.texture = this._texture2;
        else
            batch.texture = this._texture1;
        //----end27----
    },

    //
    // Automation
    //
    testDuration:1,
    pixel:{"0":51, "1":0, "2":51, "3":255},
    setupAutomation:function () {
        this.scheduleOnce(this.addTestSprite, 0.5);
    },
    addTestSprite:function () {
        var node = this.getChildByTag(TAG_SPRITE_BATCH_NODE);
        var sprite = new cc.Sprite(this._texture1, cc.rect(0, 0, 85, 121));
        sprite.x = winSize.width / 2;
        sprite.y = winSize.height / 2;
        node.addChild(sprite);
    },
    getExpectedResult:function () {
        var ret = {"pixel":"yes"};
        return JSON.stringify(ret);
    },
    getCurrentResult:function () {
        var ret1 = this.readPixels(winSize.width / 2, winSize.height / 2, 5, 5);
        var ret = {"pixel":this.containsPixel(ret1, this.pixel) ? "yes" : "no"};
        return JSON.stringify(ret);
    }
});

//------------------------------------------------------------------
//
// SpriteFrameTest
//
//------------------------------------------------------------------
var SpriteFrameTest = SpriteTestDemo.extend({
    _sprite1:null,
    _sprite2:null,
    _counter:0,
    _title:"Sprite vs. SpriteBatchNode animation",
    _subtitle:"Testing issue #792",

    onEnter:function () {
        //----start2----onEnter
        this._super();
        // IMPORTANT:
        // The sprite frames will be cached AND RETAINED, and they won't be released unless you call
        //     cc.spriteFrameCache.removeUnusedSpriteFrames);
        spriteFrameCache.addSpriteFrames(s_grossiniPlist);
        spriteFrameCache.addSpriteFrames(s_grossini_grayPlist, s_grossini_gray);
        spriteFrameCache.addSpriteFrames(s_grossini_bluePlist, s_grossini_blue);

        //
        // Animation using Sprite BatchNode
        //
        this._sprite1 = new cc.Sprite("#grossini_dance_01.png");
        this._sprite1.x = winSize.width / 2 - 80;
        this._sprite1.y = winSize.height / 2;

        var spritebatch = new cc.SpriteBatchNode(s_grossini);
        spritebatch.addChild(this._sprite1);
        this.addChild(spritebatch);

        var animFrames = [];
        var str = "";
        var frame;
        for (var i = 1; i < 15; i++) {
            str = "grossini_dance_" + (i < 10 ? ("0" + i) : i) + ".png";
            frame = spriteFrameCache.getSpriteFrame(str);
            animFrames.push(frame);
        }

        var animation = new cc.Animation(animFrames, 0.3);
        this._sprite1.runAction(cc.animate(animation).repeatForever());

        // to test issue #732, uncomment the following line
        this._sprite1.flippedX = false;
        this._sprite1.flippedY = false;

        //
        // Animation using standard Sprite
        //
        this._sprite2 = new cc.Sprite("#grossini_dance_01.png");
        this._sprite2.x = winSize.width / 2 + 80;
        this._sprite2.y = winSize.height / 2;
        this.addChild(this._sprite2);

        var moreFrames = [];
        for (i = 1; i < 15; i++) {
            str = "grossini_dance_gray_" + (i < 10 ? ("0" + i) : i) + ".png";
            frame = spriteFrameCache.getSpriteFrame(str);
            moreFrames.push(frame);
        }

        for (i = 1; i < 5; i++) {
            str = "grossini_blue_0" + i + ".png";
            frame = spriteFrameCache.getSpriteFrame(str);
            moreFrames.push(frame);
        }

        // append frames from another batch
        moreFrames = moreFrames.concat(animFrames);
        var animMixed = new cc.Animation(moreFrames, 0.3);

        this._sprite2.runAction(cc.animate(animMixed).repeatForever());

        // to test issue #732, uncomment the following line
        this._sprite2.flippedX = false;
        this._sprite2.flippedY = false;

        this.schedule(this.onStartIn05Secs, 0.5);
        this._counter = 0;
        //----end2----
    },
    onExit:function () {
        //----start2----onExit
        this._super();
        spriteFrameCache.removeSpriteFramesFromFile(s_grossiniPlist);
        spriteFrameCache.removeSpriteFramesFromFile(s_grossini_grayPlist);
        spriteFrameCache.removeSpriteFramesFromFile(s_grossini_bluePlist);
        //----end2----
    },
    onStartIn05Secs:function () {
        //----start2----onStartIn05Secs
        this.unschedule(this.onStartIn05Secs);
        this.schedule(this.onFlipSprites, 1.0);
        //----end2----
    },
    onFlipSprites:function (dt) {
        //----start2----onFlipSprites
        this._counter++;

        var fx = false;
        var fy = false;
        var i = this._counter % 4;

        switch (i) {
            case 0:
                fx = false;
                fy = false;
                break;
            case 1:
                fx = true;
                fy = false;
                break;
            case 2:
                fx = false;
                fy = true;
                break;
            case 3:
                fx = true;
                fy = true;
                break;
        }

        this._sprite1.flippedX = fx;
        this._sprite1.flippedY = fy;
        this._sprite2.flippedX = fx;
        this._sprite2.flippedY = fy;
        //----end2----
    },
    //
    // Automation
    //
    testDuration:3.1,
    pixel1:{"0":255, "1":204, "2":153, "3":255},
    pixel2:{"0":255, "1":204, "2":153, "3":255},
    getExpectedResult:function () {
        var ret = {"pixel1":"yes", "pixel2":"yes"};
        return JSON.stringify(ret);
    },
    getCurrentResult:function () {
        var ret1 = this.readPixels(winSize.width / 2 - 50, winSize.height / 2 + 8, 5, 5);
        var ret2 = this.readPixels(winSize.width / 2 - 80, winSize.height / 2 - 42, 5, 5);
        var ret = {"pixel1":this.containsPixel(ret1, this.pixel1) ? "yes" : "no",
            "pixel2":this.containsPixel(ret2, this.pixel2) ? "yes" : "no"};
        return JSON.stringify(ret);
    }
});

//------------------------------------------------------------------
//
// SpriteFrameAliasNameTest
//
//------------------------------------------------------------------
var SpriteFrameAliasNameTest = SpriteTestDemo.extend({
    _title:"SpriteFrame Alias Name",
    _subtitle:"SpriteFrames are obtained using the alias name",
    onEnter:function (){
        //----start3----onEnter
        this._super();
        // IMPORTANT:
        // The sprite frames will be cached AND RETAINED, and they won't be released unless you call
        //
        // cc.SpriteFrameCache is a cache of cc.SpriteFrames
        // cc.SpriteFrames each contain a texture id and a rect (frame).
        spriteFrameCache.addSpriteFrames(s_grossini_aliasesPlist, s_grossini_aliases);

        //
        // Animation using Sprite batch
        //
        // A cc.SpriteBatchNode can reference one and only one texture (one .png file)
        // Sprites that are contained in that texture can be instantiated as cc.Sprites and then added to the cc.SpriteBatchNode
        // All cc.Sprites added to a cc.SpriteBatchNode are drawn in one OpenGL ES draw call
        // If the cc.Sprites are not added to a cc.SpriteBatchNode then an OpenGL ES draw call will be needed for each one, which is less efficient
        //
        // When you animate a sprite, CCAnimation changes the frame of the sprite using setDisplayFrame: (this is why the animation must be in the same texture)
        // When setDisplayFrame: is used in the CCAnimation it changes the frame to one specified by the cc.SpriteFrames that were added to the animation,
        // but texture id is still the same and so the sprite is still a child of the cc.SpriteBatchNode,
        // and therefore all the animation sprites are also drawn as part of the cc.SpriteBatchNode
        //
        var sprite = new cc.Sprite("#grossini_dance_01.png");
        sprite.x = winSize.width / 2;
        sprite.y = winSize.height / 2;

        var spriteBatch = new cc.SpriteBatchNode(s_grossini_aliases);
        spriteBatch.addChild(sprite);
        this.addChild(spriteBatch);

        var animFrames = [];
        var str = "";
        for (var i = 1; i < 15; i++) {
            // Obtain frames by alias name
            str = "dance_" + (i < 10 ? ("0" + i) : i);
            var frame = spriteFrameCache.getSpriteFrame(str);
            animFrames.push(frame);
        }

        var animation = new cc.Animation(animFrames, 0.3);
        // 14 frames * 1sec = 14 seconds
        sprite.runAction(cc.animate(animation).repeatForever());
        this.testSprite = sprite;
        //----end3----
    },
    onExit:function () {
        this._super();
        spriteFrameCache.removeSpriteFramesFromFile(s_grossini_aliasesPlist);
    },
    //
    // Automation
    //
    testDuration:0.5,
    pixel:{"0":255, "1":204, "2":153, "3":255},
    getExpectedResult:function () {
        var ret = {"pixel":"yes"};
        return JSON.stringify(ret);
    },
    getCurrentResult:function () {
        var ret1 = this.readPixels(winSize.width / 2 - 32, winSize.height / 2 - 10, 5, 5);
        var ret = {"pixel":this.containsPixel(ret1, this.pixel, false) ? "yes" : "no"};
        return JSON.stringify(ret);
    }
});

//------------------------------------------------------------------
//
// SpriteOffsetAnchorRotation
//
//------------------------------------------------------------------
var SpriteOffsetAnchorRotation = SpriteTestDemo.extend({

    _title:"Sprite offset + anchor + rot",
    ctor:function () {
        //----start6----ctor
        this._super();
        spriteFrameCache.addSpriteFrames(s_grossiniPlist);
        spriteFrameCache.addSpriteFrames(s_grossini_grayPlist, s_grossini_gray);

        for (var i = 0; i < 3; i++) {
            //
            // Animation using Sprite BatchNode
            //
            var sprite = new cc.Sprite(spriteFrameCache.getSpriteFrame("grossini_dance_01.png"));
            sprite.x = winSize.width / 4 * (i + 1);
            sprite.y = winSize.height / 2;

            var point = new cc.Sprite(s_pathR1);
            point.scale = 0.25;
            point.x = sprite.x;
            point.y = sprite.y;
            this.addChild(point, 1);

            switch (i) {
                case 0:
                    sprite.anchorX = 0;
                    sprite.anchorY = 0;
                    break;
                case 1:
                    sprite.anchorX = 0.5;
                    sprite.anchorY = 0.5;
                    break;
                case 2:
                    sprite.anchorX = 1;
                    sprite.anchorY = 1;
                    break;
            }

            point.x = sprite.x;

            point.y = sprite.y;

            var animFrames = [];
            var str = "";
            for (var j = 1; j < 15; j++) {
                str = "grossini_dance_" + (j < 10 ? ("0" + j) : j) + ".png";
                var frame = spriteFrameCache.getSpriteFrame(str);
                animFrames.push(frame);
            }

            var animation = new cc.Animation(animFrames, 0.3);
            sprite.runAction(cc.animate(animation).repeatForever());
            sprite.runAction(cc.rotateBy(10, 360).repeatForever());

            this.addChild(sprite, 0);
        }
        //----end6----
    },
    onExit:function () {
        //----start6----onExit
        this._super();
        spriteFrameCache.removeSpriteFramesFromFile(s_grossiniPlist);
        spriteFrameCache.removeSpriteFramesFromFile(s_grossini_grayPlist);
        //----end6----
    },
    //
    // Automation
    //
    testDuration:5,
    pixel:{"0":255, "1":204, "2":153, "3":255},
    getExpectedResult:function () {
        var ret = {"pixel1":"yes", "pixel2":"yes", "pixel3":"yes"};
        return JSON.stringify(ret);
    },
    getCurrentResult:function () {
        var ret1 = this.readPixels(winSize.width / 4 - 13, winSize.height / 2 - 50, 5, 5);
        var ret2 = this.readPixels(winSize.width / 4 * 2 + 29, winSize.height / 2 + 11, 5, 5);
        var ret3 = this.readPixels(winSize.width / 4 * 3 + 71, winSize.height / 2 + 71, 5, 5);
        var ret = {"pixel1":this.containsPixel(ret1, this.pixel) ? "yes" : "no", "pixel2":this.containsPixel(ret2, this.pixel) ? "yes" : "no", "pixel3":this.containsPixel(ret3, this.pixel) ? "yes" : "no"};
        return JSON.stringify(ret);
    }
});

//------------------------------------------------------------------
//
// SpriteBatchNodeOffsetAnchorRotation
//
//------------------------------------------------------------------
var SpriteBatchNodeOffsetAnchorRotation = SpriteTestDemo.extend({
    _title:"SpriteBatchNode offset + anchor + rot",

    ctor:function () {
        //----start7----ctor
        this._super();

        spriteFrameCache.addSpriteFrames(s_grossiniPlist);
        spriteFrameCache.addSpriteFrames(s_grossini_grayPlist, s_grossini_gray);

        var spritebatch = new cc.SpriteBatchNode(s_grossini);
        this.addChild(spritebatch);

        for (var i = 0; i < 3; i++) {
            //
            // Animation using Sprite BatchNode
            //
            var sprite = new cc.Sprite(spriteFrameCache.getSpriteFrame("grossini_dance_01.png"));
            sprite.x = winSize.width / 4 * (i + 1);
            sprite.y = winSize.height / 2;

            var point = new cc.Sprite(s_pathR1);
            point.scale = 0.25;
            point.x = sprite.x;
            point.y = sprite.y;
            this.addChild(point, 200);

            switch (i) {
                case 0:
                    sprite.anchorX = 0;
                    sprite.anchorY = 0;
                    break;
                case 1:
                    sprite.anchorX = 0.5;
                    sprite.anchorY = 0.5;
                    break;
                case 2:
                    sprite.anchorX = 1;
                    sprite.anchorY = 1;
                    break;
            }
            point.x = sprite.x;
            point.y = sprite.y;

            var animFrames = [];
            var str = "";
            for (var k = 1; k < 15; k++) {
                str = "grossini_dance_" + (k < 10 ? ("0" + k) : k) + ".png";
                var frame = spriteFrameCache.getSpriteFrame(str);
                animFrames.push(frame);
            }

            var animation = new cc.Animation(animFrames, 0.3);
            sprite.runAction(cc.animate(animation).repeatForever());
            sprite.runAction(cc.rotateBy(10, 360).repeatForever());

            spritebatch.addChild(sprite, i);
        }
        //----end7----
    },
    onExit:function () {
        this._super();
        spriteFrameCache.removeSpriteFramesFromFile(s_grossiniPlist);
        spriteFrameCache.removeSpriteFramesFromFile(s_grossini_grayPlist);
    },
    //
    // Automation
    //
    testDuration:5,
    pixel:{"0":255, "1":204, "2":153, "3":255},
    getExpectedResult:function () {
        var ret = {"pixel1":"yes", "pixel2":"yes", "pixel3":"yes"};
        return JSON.stringify(ret);
    },
    getCurrentResult:function () {
        var ret1 = this.readPixels(winSize.width / 4 - 13, winSize.height / 2 - 50, 5, 5);
        var ret2 = this.readPixels(winSize.width / 4 * 2 + 29, winSize.height / 2 + 11, 5, 5);
        var ret3 = this.readPixels(winSize.width / 4 * 3 + 71, winSize.height / 2 + 71, 5, 5);
        var ret = {"pixel1":this.containsPixel(ret1, this.pixel) ? "yes" : "no", "pixel2":this.containsPixel(ret2, this.pixel) ? "yes" : "no", "pixel3":this.containsPixel(ret3, this.pixel) ? "yes" : "no"};
        return JSON.stringify(ret);
    }
});

//------------------------------------------------------------------
//
// SpriteOffsetAnchorScale
//
//------------------------------------------------------------------
var SpriteOffsetAnchorScale = SpriteTestDemo.extend({

    _title:"Sprite offset + anchor + scale",

    ctor:function () {
        //----start8----ctor
        this._super();
        spriteFrameCache.addSpriteFrames(s_grossiniPlist);
        spriteFrameCache.addSpriteFrames(s_grossini_grayPlist, s_grossini_gray);

        for (var i = 0; i < 3; i++) {
            //
            // Animation using Sprite BatchNode
            //
            var sprite = new cc.Sprite(spriteFrameCache.getSpriteFrame("grossini_dance_01.png"));
            sprite.x = winSize.width / 4 * (i + 1);
            sprite.y = winSize.height / 2;

            var point = new cc.Sprite(s_pathR1);
            point.scale = 0.25;
            point.x = sprite.x;
            point.y = sprite.y;
            this.addChild(point, 1);

            switch (i) {
                case 0:
                    sprite.anchorX = 0;
                    sprite.anchorY = 0;
                    break;
                case 1:
                    sprite.anchorX = 0.5;
                    sprite.anchorY = 0.5;
                    break;
                case 2:
                    sprite.anchorX = 1;
                    sprite.anchorY = 1;
                    break;
            }

            point.x = sprite.x;

            point.y = sprite.y;

            var animFrames = [];
            var str = "";
            for (var k = 1; k <= 14; k++) {
                str = "grossini_dance_" + (k < 10 ? ("0" + k) : k) + ".png";
                var frame = spriteFrameCache.getSpriteFrame(str);
                animFrames.push(frame);
            }

            var animation = new cc.Animation(animFrames, 0.3);
            sprite.runAction(cc.animate(animation).repeatForever());

            var scale = cc.scaleBy(2, 2);
            var scale_back = scale.reverse();
            var delay = cc.delayTime(0.25);
            var seq_scale = cc.sequence(scale, delay, scale_back);
            sprite.runAction(seq_scale.repeatForever());

            this.addChild(sprite, 0);
        }
        //----end8----
    },
    onExit:function () {
        //----start8----onExit
        this._super();
        spriteFrameCache.removeSpriteFramesFromFile(s_grossiniPlist);
        spriteFrameCache.removeSpriteFramesFromFile(s_grossini_grayPlist);
        //----end8----
    },
    //
    // Automation
    //
    testDuration:2.1,
    pixel:{"0":153, "1":0, "2":153, "3":255},
    getExpectedResult:function () {
        var ret = {"pixel1":"yes", "pixel2":"yes", "pixel3":"yes"};
        return JSON.stringify(ret);
    },
    getCurrentResult:function () {
        var ret1 = this.readPixels(winSize.width / 4 * 3 - 85, winSize.height / 2 - 106, 5, 5);
        var ret2 = this.readPixels(winSize.width / 4 * 2, winSize.height / 2 + 13, 5, 5);
        var ret3 = this.readPixels(winSize.width / 4 + 82, winSize.height / 2 + 133, 5, 5);
        var ret = {"pixel1":this.containsPixel(ret1, this.pixel) ? "yes" : "no", "pixel2":this.containsPixel(ret2, this.pixel) ? "yes" : "no", "pixel3":this.containsPixel(ret3, this.pixel) ? "yes" : "no"};
        return JSON.stringify(ret);
    }
});


//------------------------------------------------------------------
//
// SpriteBatchNodeOffsetAnchorScale
//
//------------------------------------------------------------------
var SpriteBatchNodeOffsetAnchorScale = SpriteTestDemo.extend({

    _title:"SpriteBatchNode offset + anchor + scale",

    ctor:function () {
        this._super();
        //----start9----ctor
        var batch = new cc.SpriteBatchNode(s_grossini);
        this.addChild(batch);

        spriteFrameCache.addSpriteFrames(s_grossiniPlist);
        spriteFrameCache.addSpriteFrames(s_grossini_grayPlist, s_grossini_gray);

        for (var i = 0; i < 3; i++) {
            //
            // Animation using Sprite BatchNode
            //
            var sprite = new cc.Sprite(spriteFrameCache.getSpriteFrame("grossini_dance_01.png"));
            sprite.x = winSize.width / 4 * (i + 1);
            sprite.y = winSize.height / 2;

            var point = new cc.Sprite(s_pathR1);
            point.scale = 0.25;
            point.x = sprite.x;
            point.y = sprite.y;
            this.addChild(point, 200);

            switch (i) {
                case 0:
                    sprite.anchorX = 0;
                    sprite.anchorY = 0;
                    break;
                case 1:
                    sprite.anchorX = 0.5;
                    sprite.anchorY = 0.5;
                    break;
                case 2:
                    sprite.anchorX = 1;
                    sprite.anchorY = 1;
                    break;
            }

	        point.x = sprite.x;
	        point.y = sprite.y;

            var animFrames = [];
            var str = "";
            for (var k = 1; k <= 14; k++) {
                str = "grossini_dance_" + (k < 10 ? ("0" + k) : k) + ".png";
                var frame = spriteFrameCache.getSpriteFrame(str);
                animFrames.push(frame);
            }

            var animation = new cc.Animation(animFrames, 0.3);
            sprite.runAction(cc.animate(animation).repeatForever());

            var scale = cc.scaleBy(2, 2);
            var scale_back = scale.reverse();
            var seq_scale = cc.sequence(scale, scale_back);
            sprite.runAction(seq_scale.repeatForever());

            batch.addChild(sprite, i);
        }
        //----end9----
    },
    onExit:function () {
        //----start9----onExit
        this._super();
        spriteFrameCache.removeSpriteFramesFromFile(s_grossiniPlist);
        spriteFrameCache.removeSpriteFramesFromFile(s_grossini_grayPlist);
        //----end9----
    },
    //
    // Automation
    //
    testDuration:2.1,
    pixel:{"0":153, "1":0, "2":153, "3":255},
    getExpectedResult:function () {
        var ret = {"pixel1":"yes", "pixel2":"yes", "pixel3":"yes"};
        return JSON.stringify(ret);
    },
    getCurrentResult:function () {
        var ret1 = this.readPixels(winSize.width / 4 * 3 - 85, winSize.height / 2 - 106, 5, 5);
        var ret2 = this.readPixels(winSize.width / 4 * 2, winSize.height / 2 + 13, 5, 5);
        var ret3 = this.readPixels(winSize.width / 4 + 82, winSize.height / 2 + 133, 5, 5);
        var ret = {"pixel1":this.containsPixel(ret1, this.pixel) ? "yes" : "no", "pixel2":this.containsPixel(ret2, this.pixel) ? "yes" : "no", "pixel3":this.containsPixel(ret3, this.pixel) ? "yes" : "no"};
        return JSON.stringify(ret);
    }
});

//
// SpriteOffsetAnchorSkew
//
var SpriteOffsetAnchorSkew = SpriteTestDemo.extend({

    _title:"Sprite offset + anchor + skew",

    ctor:function () {
        //----start41----ctor
        this._super();
        spriteFrameCache.addSpriteFrames(s_grossiniPlist);
        spriteFrameCache.addSpriteFrames(s_grossini_grayPlist, s_grossini_gray);

        for (var i = 0; i < 3; i++) {
            //
            // Animation using Sprite batch
            //
            var sprite = new cc.Sprite("#grossini_dance_01.png");
            sprite.x = winSize.width / 4 * (i + 1);
            sprite.y = winSize.height / 2;

            var point = new cc.Sprite(s_pathR1);
            point.scale = 0.25;
	        point.x = sprite.x;
	        point.y = sprite.y;
            this.addChild(point, 1);

            switch (i) {
                case 0:
                    sprite.anchorX = 0;
                    sprite.anchorY = 0;
                    break;
                case 1:
                    sprite.anchorX = 0.5;
                    sprite.anchorY = 0.5;
                    break;
                case 2:
                    sprite.anchorX = 1;
                    sprite.anchorY = 1;
                    break;
            }

	        point.x = sprite.x;
	        point.y = sprite.y;

            var animFrames = [];
            var tmp = "";
            for (var j = 1; j <= 14; j++) {
                tmp = "grossini_dance_" + (j < 10 ? ("0" + j) : j) + ".png";
                var frame = spriteFrameCache.getSpriteFrame(tmp);
                animFrames.push(frame);
            }

            var animation = new cc.Animation(animFrames, 0.3);
            sprite.runAction(cc.animate(animation).repeatForever());

            var skewX = cc.skewBy(2, 45, 0);
            var skewX_back = skewX.reverse();
            var skewY = cc.skewBy(2, 0, 45);
            var skewY_back = skewY.reverse();

            var seq_skew = cc.sequence(skewX, skewX_back, skewY, skewY_back);
            sprite.runAction(seq_skew.repeatForever());

            this.addChild(sprite, 0);
        }
        //----end41----
    },
    //
    // Automation
    //
    testDuration:2,
    pixel:{"0":255, "1":204, "2":153, "3":255},
    getExpectedResult:function () {
        var ret = {"pixel1":"yes", "pixel2":"yes"};
        return JSON.stringify(ret);
    },
    getCurrentResult:function () {
        var ret1 = this.readPixels(winSize.width / 4 + 142, winSize.height / 2 + 98, 5, 5);
        var ret2 = this.readPixels(winSize.width / 4 * 2 + 50, winSize.height / 2 + 43, 5, 5);
        var ret = {"pixel1":this.containsPixel(ret1, this.pixel) ? "yes" : "no",
            "pixel2":this.containsPixel(ret2, this.pixel) ? "yes" : "no"};
        return JSON.stringify(ret);
    }
});

//
// SpriteBatchNodeOffsetAnchorSkew
//
var SpriteBatchNodeOffsetAnchorSkew = SpriteTestDemo.extend({

    _title:"SpriteBatchNode offset + anchor + skew",

    ctor:function () {
        //----start42----ctor
        this._super();
        spriteFrameCache.addSpriteFrames(s_grossiniPlist);
        spriteFrameCache.addSpriteFrames(s_grossini_grayPlist, s_grossini_gray);

        var spritebatch = new cc.SpriteBatchNode(s_grossini);
        this.addChild(spritebatch);

        for (var i = 0; i < 3; i++) {
            //
            // Animation using Sprite batch
            //
            var sprite = new cc.Sprite("#grossini_dance_01.png");
            sprite.x = winSize.width / 4 * (i + 1);
            sprite.y = winSize.height / 2;

            var point = new cc.Sprite(s_pathR1);
            point.scale = 0.25;
	        point.x = sprite.x;
	        point.y = sprite.y;
            this.addChild(point, 200);

            switch (i) {
                case 0:
                    sprite.anchorX = 0;
                    sprite.anchorY = 0;
                    break;
                case 1:
                    sprite.anchorX = 0.5;
                    sprite.anchorY = 0.5;
                    break;
                case 2:
                    sprite.anchorX = 1;
                    sprite.anchorY = 1;
                    break;
            }

	        point.x = sprite.x;
	        point.y = sprite.y;

            var animFrames = [];
            var tmp = "";
            for (var j = 1; j <= 14; j++) {
                tmp = "grossini_dance_" + (j < 10 ? ("0" + j) : j) + ".png";
                var frame = spriteFrameCache.getSpriteFrame(tmp);
                animFrames.push(frame);
            }

            var animation = new cc.Animation(animFrames, 0.3);
            sprite.runAction(cc.animate(animation).repeatForever());

            animFrames = null;

            var skewX = cc.skewBy(2, 45, 0);
            var skewX_back = skewX.reverse();
            var skewY = cc.skewBy(2, 0, 45);
            var skewY_back = skewY.reverse();

            var seq_skew = cc.sequence(skewX, skewX_back, skewY, skewY_back);
            sprite.runAction(seq_skew.repeatForever());

            spritebatch.addChild(sprite, i);
        }
        //----end42----
    },
    //
    // Automation
    //
    testDuration:2,
    pixel:{"0":255, "1":204, "2":153, "3":255},
    getExpectedResult:function () {
        var ret = {"pixel1":"yes", "pixel2":"yes"};
        return JSON.stringify(ret);
    },
    getCurrentResult:function () {
        var ret1 = this.readPixels(winSize.width / 4 + 142, winSize.height / 2 + 98, 5, 5);
        var ret2 = this.readPixels(winSize.width / 4 * 2 + 50, winSize.height / 2 + 43, 5, 5);
        var ret = {"pixel1":this.containsPixel(ret1, this.pixel) ? "yes" : "no",
            "pixel2":this.containsPixel(ret2, this.pixel) ? "yes" : "no"};
        return JSON.stringify(ret);
    }
});

//
// SpriteOffsetAnchorSkewScale
//
var SpriteOffsetAnchorSkewScale = SpriteTestDemo.extend({

    _title:"Sprite anchor + skew + scale",
    ctor:function () {
        //----start43----ctor
        this._super();
        spriteFrameCache.addSpriteFrames(s_grossiniPlist);
        spriteFrameCache.addSpriteFrames(s_grossini_grayPlist, s_grossini_gray);

        for (var i = 0; i < 3; i++) {
            //
            // Animation using Sprite batch
            //
            var sprite = new cc.Sprite(spriteFrameCache.getSpriteFrame("grossini_dance_01.png"));
            sprite.x = winSize.width / 4 * (i + 1);
            sprite.y = winSize.height / 2;

            var point = new cc.Sprite(s_pathR1);
            point.scale = 0.25;
	        point.x = sprite.x;
	        point.y = sprite.y;
            this.addChild(point, 1);

            switch (i) {
                case 0:
                    sprite.anchorX = 0;
                    sprite.anchorY = 0;
                    break;
                case 1:
                    sprite.anchorX = 0.5;
                    sprite.anchorY = 0.5;
                    break;
                case 2:
                    sprite.anchorX = 1;
                    sprite.anchorY = 1;
                    break;
            }

	        point.x = sprite.x;
	        point.y = sprite.y;

            var animFrames = [];
            var tmp = "";
            for (var j = 1; j <= 14; j++) {
                tmp = "grossini_dance_" + (j < 10 ? ("0" + j) : j) + ".png";
                var frame = spriteFrameCache.getSpriteFrame(tmp);
                animFrames.push(frame);
            }

            var animation = new cc.Animation(animFrames, 0.3);
            sprite.runAction(cc.animate(animation).repeatForever());

            animFrames = null;

            // Skew
            var skewX = cc.skewBy(2, 45, 0);
            var skewX_back = skewX.reverse();
            var skewY = cc.skewBy(2, 0, 45);
            var skewY_back = skewY.reverse();

            var seq_skew = cc.sequence(skewX, skewX_back, skewY, skewY_back);
            sprite.runAction(seq_skew.repeatForever());

            // Scale
            var scale = cc.scaleBy(2, 2);
            var scale_back = scale.reverse();
            var seq_scale = cc.sequence(scale, scale_back);
            sprite.runAction(seq_scale.repeatForever());

            this.addChild(sprite, 0);
        }
        //----end43----
    },
    //
    // Automation
    //
    testDuration:2,
    pixel:{"0":255, "1":204, "2":153, "3":255},
    getExpectedResult:function () {
        var ret = {"pixel1":"yes", "pixel2":"yes", "pixel3":"yes"};
        return JSON.stringify(ret);
    },
    getCurrentResult:function () {
        var ret1 = this.readPixels(winSize.width / 4 + 121, winSize.height / 2 + 99, 5, 5);
        var ret2 = this.readPixels(winSize.width / 4 * 2 - 83, winSize.height / 2 - 21, 5, 5);
        var ret3 = this.readPixels(winSize.width / 4 * 3 - 286, winSize.height / 2 - 140, 5, 5);
        var ret = {"pixel1":this.containsPixel(ret1, this.pixel) ? "yes" : "no",
            "pixel2":this.containsPixel(ret2, this.pixel) ? "yes" : "no",
            "pixel3":this.containsPixel(ret3, this.pixel) ? "yes" : "no"};
        return JSON.stringify(ret);
    }
});

//
// SpriteBatchNodeOffsetAnchorSkewScale
//
var SpriteBatchNodeOffsetAnchorSkewScale = SpriteTestDemo.extend({

    _title:"SpriteBatchNode anchor + skew + scale",

    ctor:function () {
        //----start44----ctor
        this._super();

        spriteFrameCache.addSpriteFrames(s_grossiniPlist);
        spriteFrameCache.addSpriteFrames(s_grossini_grayPlist, s_grossini_gray);

        var spritebatch = new cc.SpriteBatchNode(s_grossini);
        this.addChild(spritebatch);

        for (var i = 0; i < 3; i++) {
            //
            // Animation using Sprite batch
            //
            var sprite = new cc.Sprite("#grossini_dance_01.png");
            sprite.x = winSize.width / 4 * (i + 1);
            sprite.y = winSize.height / 2;

            var point = new cc.Sprite(s_pathR1);
            point.scale = 0.25;
	        point.x = sprite.x;
	        point.y = sprite.y;
            this.addChild(point, 200);

            switch (i) {
                case 0:
                    sprite.anchorX = 0;
                    sprite.anchorY = 0;
                    break;
                case 1:
                    sprite.anchorX = 0.5;
                    sprite.anchorY = 0.5;
                    break;
                case 2:
                    sprite.anchorX = 1;
                    sprite.anchorY = 1;
                    break;
            }

	        point.x = sprite.x;
	        point.y = sprite.y;

            var animFrames = [];
            var tmp = "";
            for (var j = 1; j <= 14; j++) {
                tmp = "grossini_dance_" + (j < 10 ? ("0" + j) : j) + ".png";
                var frame = spriteFrameCache.getSpriteFrame(tmp);
                animFrames.push(frame);
            }

            var animation = new cc.Animation(animFrames, 0.3);
            sprite.runAction(cc.animate(animation).repeatForever());

            animFrames = null;

            // skew
            var skewX = cc.skewBy(2, 45, 0);
            var skewX_back = skewX.reverse();
            var skewY = cc.skewBy(2, 0, 45);
            var skewY_back = skewY.reverse();

            var seq_skew = cc.sequence(skewX, skewX_back, skewY, skewY_back);
            sprite.runAction(seq_skew.repeatForever());

            // scale
            var scale = cc.scaleBy(2, 2);
            var scale_back = scale.reverse();
            var seq_scale = cc.sequence(scale, scale_back);
            sprite.runAction(seq_scale.repeatForever());

            spritebatch.addChild(sprite, i);
        }
        //----end44----
    },
    //
    // Automation
    //
    testDuration:2,
    pixel:{"0":255, "1":204, "2":153, "3":255},
    getExpectedResult:function () {
        var ret = {"pixel1":"yes", "pixel2":"yes", "pixel3":"yes"};
        return JSON.stringify(ret);
    },
    getCurrentResult:function () {
        var ret1 = this.readPixels(winSize.width / 4 + 121, winSize.height / 2 + 99, 5, 5);
        var ret2 = this.readPixels(winSize.width / 4 * 2 - 83, winSize.height / 2 - 21, 5, 5);
        var ret3 = this.readPixels(winSize.width / 4 * 3 - 286, winSize.height / 2 - 140, 5, 5);
        var ret = {"pixel1":this.containsPixel(ret1, this.pixel) ? "yes" : "no",
            "pixel2":this.containsPixel(ret2, this.pixel) ? "yes" : "no",
            "pixel3":this.containsPixel(ret3, this.pixel) ? "yes" : "no"};
        return JSON.stringify(ret);
    }
});

//
// SpriteOffsetAnchorFlip
//
var SpriteOffsetAnchorFlip = SpriteTestDemo.extend({

    _title:"Sprite offset + anchor + flip",
    _subtitle:"issue #1078",

    ctor:function () {
        //----start45----ctor
        this._super();
        spriteFrameCache.addSpriteFrames(s_grossiniPlist);
        spriteFrameCache.addSpriteFrames(s_grossini_grayPlist, s_grossini_gray);

        for (var i = 0; i < 3; i++) {
            //
            // Animation using Sprite batch
            //
            var sprite = new cc.Sprite("#grossini_dance_01.png");
            sprite.x = winSize.width / 4 * (i + 1);
            sprite.y = winSize.height / 2;

            var point = new cc.Sprite(s_pathR1);
            point.scale = 0.25;
	        point.x = sprite.x;
	        point.y = sprite.y;
            this.addChild(point, 1);

            switch (i) {
                case 0:
                    sprite.anchorX = 0;
                    sprite.anchorY = 0;
                    break;
                case 1:
                    sprite.anchorX = 0.5;
                    sprite.anchorY = 0.5;
                    break;
                case 2:
                    sprite.anchorX = 1;
                    sprite.anchorY = 1;
                    break;
            }

	        point.x = sprite.x;
	        point.y = sprite.y;

            var animFrames = [];
            var tmp = "";
            for (var j = 1; j <= 14; j++) {
                tmp = "grossini_dance_" + (j < 10 ? ("0" + j) : j) + ".png";
                var frame = spriteFrameCache.getSpriteFrame(tmp);
                animFrames.push(frame);
            }

            var animation = new cc.Animation(animFrames, 0.3);
            sprite.runAction(cc.animate(animation).repeatForever());

            animFrames = null;

            var flip = cc.flipY(true);
            var flip_back = cc.flipY(false);
            var delay = cc.delayTime(1);
            var delay1 = cc.delayTime(1);
            var seq = cc.sequence(delay, flip, delay1, flip_back);
            sprite.runAction(seq.repeatForever());

            this.addChild(sprite, 0);
        }
        //----end45----
    },
    //
    // Automation
    //
    testDuration:1.5,
    pixel:{"0":255, "1":204, "2":153, "3":255},
    getExpectedResult:function () {
        var ret = {"pixel1":"yes", "pixel2":"yes", "pixel3":"yes"};
        return JSON.stringify(ret);
    },
    getCurrentResult:function () {
        var ret1 = this.readPixels(winSize.width / 4 + 40, winSize.height / 2 + 18, 5, 5);
        var ret2 = this.readPixels(winSize.width / 4 * 2, winSize.height / 2 - 44, 5, 5);
        var ret3 = this.readPixels(winSize.width / 4 * 3 - 45, winSize.height / 2 - 105, 5, 5);
        var ret = {"pixel1":this.containsPixel(ret1, this.pixel) ? "yes" : "no", "pixel2":this.containsPixel(ret2, this.pixel) ? "yes" : "no", "pixel3":this.containsPixel(ret3, this.pixel) ? "yes" : "no"};
        return JSON.stringify(ret);
    }
});

//
// SpriteBatchNodeOffsetAnchorFlip
//
var SpriteBatchNodeOffsetAnchorFlip = SpriteTestDemo.extend({

    _title:"SpriteBatchNode offset + anchor + flip",
    _subtitle:"issue #1078",

    ctor:function () {
        //----start46----ctor
        this._super();
        spriteFrameCache.addSpriteFrames(s_grossiniPlist);
        spriteFrameCache.addSpriteFrames(s_grossini_grayPlist, s_grossini_gray);

        var spritebatch = new cc.SpriteBatchNode(s_grossini);
        this.addChild(spritebatch);

        for (var i = 0; i < 3; i++) {
            //
            // Animation using Sprite batch
            //
            var sprite = new cc.Sprite(spriteFrameCache.getSpriteFrame("grossini_dance_01.png"));
            sprite.x = winSize.width / 4 * (i + 1);
            sprite.y = winSize.height / 2;

            var point = new cc.Sprite(s_pathR1);
            point.scale = 0.25;
	        point.x = sprite.x;
	        point.y = sprite.y;
            this.addChild(point, 200);

            switch (i) {
                case 0:
                    sprite.anchorX = 0;
                    sprite.anchorY = 0;
                    break;
                case 1:
                    sprite.anchorX = 0.5;
                    sprite.anchorY = 0.5;
                    break;
                case 2:
                    sprite.anchorX = 1;
                    sprite.anchorY = 1;
                    break;
            }

	        point.x = sprite.x;
	        point.y = sprite.y;

            var animFrames = [];
            var tmp = "";
            for (var j = 1; j <= 14; j++) {
                tmp = "grossini_dance_" + (j < 10 ? ("0" + j) : j) + ".png";
                var frame = spriteFrameCache.getSpriteFrame(tmp);
                animFrames.push(frame);
            }

            var animation = new cc.Animation(animFrames, 0.3);
            sprite.runAction(cc.animate(animation).repeatForever());

            animFrames = null;

            var flip = cc.flipY(true);
            var flip_back = cc.flipY(false);
            var delay = cc.delayTime(1);
            var seq = cc.sequence(delay, flip, delay.clone(), flip_back);
            sprite.runAction(seq.repeatForever());

            spritebatch.addChild(sprite, i);
        }
        //----end46----
    },
    //
    // Automation
    //
    testDuration:1.5,
    pixel:{"0":255, "1":204, "2":153, "3":255},
    getExpectedResult:function () {
        var ret = {"pixel1":"yes", "pixel2":"yes", "pixel3":"yes"};
        return JSON.stringify(ret);
    },
    getCurrentResult:function () {
        var ret1 = this.readPixels(winSize.width / 4 + 40, winSize.height / 2 + 18, 5, 5);
        var ret2 = this.readPixels(winSize.width / 4 * 2, winSize.height / 2 - 44, 5, 5);
        var ret3 = this.readPixels(winSize.width / 4 * 3 - 45, winSize.height / 2 - 105, 5, 5);
        var ret = {"pixel1":this.containsPixel(ret1, this.pixel) ? "yes" : "no", "pixel2":this.containsPixel(ret2, this.pixel) ? "yes" : "no", "pixel3":this.containsPixel(ret3, this.pixel) ? "yes" : "no"};
        return JSON.stringify(ret);
    }
});

//------------------------------------------------------------------
//
// SpriteAnimationSplit
//
//------------------------------------------------------------------
var SpriteAnimationSplit = SpriteTestDemo.extend({

    _title:"Sprite: Animation + flip",
    ctor:function () {
        //----start10----ctor
        this._super();
        var texture = cc.textureCache.addImage(s_dragon_animation);

        // manually add frames to the frame cache
        var frame0 = new cc.SpriteFrame(texture, cc.rect(132 * 0, 132 * 0, 132, 132));
        var frame1 = new cc.SpriteFrame(texture, cc.rect(132 * 1, 132 * 0, 132, 132));
        var frame2 = new cc.SpriteFrame(texture, cc.rect(132 * 2, 132 * 0, 132, 132));
        var frame3 = new cc.SpriteFrame(texture, cc.rect(132 * 3, 132 * 0, 132, 132));
        var frame4 = new cc.SpriteFrame(texture, cc.rect(132 * 0, 132 * 1, 132, 132));
        var frame5 = new cc.SpriteFrame(texture, cc.rect(132 * 1, 132 * 1, 132, 132));

        //
        // Animation using Sprite BatchNode
        //
        var sprite = new cc.Sprite(frame0);
        sprite.x = winSize.width / 2;
        sprite.y = winSize.height / 2;
        this.addChild(sprite);

        var animFrames = [];
        animFrames.push(frame0);
        animFrames.push(frame1);
        animFrames.push(frame2);
        animFrames.push(frame3);
        animFrames.push(frame4);
        animFrames.push(frame5);

        var animation = new cc.Animation(animFrames, 0.2);
        var animate = cc.animate(animation);
        var delay = cc.delayTime(0.5);
        var seq = cc.sequence(animate,
            cc.flipX(true),
            animate.clone(),
            delay,
            cc.flipX(false));

        sprite.runAction(seq.repeatForever());
        //----end10----
    },
    onExit:function () {
        this._super();
    },
    //
    // Automation
    //
    testDuration:2.8,
    pixel1:{"0":208, "1":208, "2":208, "3":255},
    pixel2:{"0":0, "1":0, "2":0, "3":255},
    getExpectedResult:function () {
        var ret = {"pixel1":"yes", "pixel2":"yes"};
        return JSON.stringify(ret);
    },
    getCurrentResult:function () {
        var ret1 = this.readPixels(winSize.width / 2 + 52, winSize.height / 2 - 29, 5, 5);
        var ret2 = this.readPixels(winSize.width / 2, winSize.height / 2 - 22, 5, 5);
        var ret = {"pixel1":this.containsPixel(ret1, this.pixel1, true, 3) ? "yes" : "no",
            "pixel2":this.containsPixel(ret2, this.pixel2, false) ? "yes" : "no"};
        return JSON.stringify(ret);
    }
});

//------------------------------------------------------------------
//
// SpriteHybrid
//
//------------------------------------------------------------------
var SpriteHybrid = SpriteTestDemo.extend({
    _usingSpriteBatchNode:false,
    _title:"Hybrid.Sprite* sprite Test",

    ctor:function () {
        //----start28----ctor
        this._super();
        // parents
        var parent1 = new cc.Node();
        var parent2 = new cc.SpriteBatchNode(s_grossini, 50);

        this.addChild(parent1, 0, TAG_NODE);
        this.addChild(parent2, 0, TAG_SPRITE_BATCH_NODE);

        // IMPORTANT:
        // The sprite frames will be cached AND RETAINED, and they won't be released unless you call
        spriteFrameCache.addSpriteFrames(s_grossiniPlist);

        // create 250 sprites
        // only show 80% of them
        for (var i = 1; i <= 250; i++) {
            var spriteIdx = Math.round(Math.random() * 14);
            if (spriteIdx === 0)
                spriteIdx = 1;
            var str = "grossini_dance_" + (spriteIdx < 10 ? ("0" + spriteIdx) : spriteIdx) + ".png";

            var frame = spriteFrameCache.getSpriteFrame(str);
            var sprite = new cc.Sprite(frame);
            parent1.addChild(sprite, i, i);

            var x = -1000;
            var y = -1000;
            if (Math.random() < 0.2) {
                x = Math.random() * winSize.width;
                y = Math.random() * winSize.height;
            }
            sprite.x = x;
            sprite.y = y;

            var action = cc.rotateBy(4, 360);
            sprite.runAction(action.repeatForever());
        }

        this._usingSpriteBatchNode = false;

        this.schedule(this.reparentSprite, 2);
        //----end28----
    },
    onExit:function () {
        //----start28----onExit
        this._super();
        spriteFrameCache.removeSpriteFramesFromFile(s_grossiniPlist);
        //----end28----
    },
    reparentSprite:function () {
        //----start28----reparentSprite
        var p1 = this.getChildByTag(TAG_NODE);
        var p2 = this.getChildByTag(TAG_SPRITE_BATCH_NODE);

        var retArray = [];
        var node;

        if (this._usingSpriteBatchNode) {
            var tempNode = p2;
            p2 = p1;
            p1 = tempNode;
        }
        ////----UXLog("New parent is: %x", p2);

        var children = p1.children;
        for (var i = 0; i < children.length; i++) {
            node = children[i];
            if (!node)
                break;

            retArray.push(node);
        }

        p1.removeAllChildren(false);
        for (i = 0; i < retArray.length; i++) {
            node = retArray[i];
            if (!node)
                break;

            p2.addChild(node, i, i);
        }

        this._usingSpriteBatchNode = !this._usingSpriteBatchNode;
        //----end28----
    },
    //
    // Automation
    //
    testDuration:2.5,
    pixel:{"0":51, "1":0, "2":51, "3":255},
    firstPixel1:false,
    firstPixel2:false,
    setupAutomation:function () {
        this.scheduleOnce(this.addTestSprite, 1);
        this.scheduleOnce(this.checkFirstPixel, 1.5);
    },
    addTestSprite:function () {
        var p = this.getChildByTag(TAG_NODE);
        var frame = spriteFrameCache.getSpriteFrame("grossini_dance_01.png");
        var sprite1 = new cc.Sprite(frame);
        sprite1.retain();
        p.addChild(sprite1, 1000);
        sprite1.x = winSize.width / 4;
        sprite1.y = winSize.height / 2;
        var sprite2 = new cc.Sprite(frame);
        sprite2.retain();
        p.addChild(sprite2, 1000);
        sprite2.x = winSize.width / 2;
        sprite2.y = winSize.height / 2;
    },
    checkFirstPixel:function () {
        var ret1 = this.readPixels(winSize.width / 4, winSize.height / 2, 5, 5);
        var ret2 = this.readPixels(winSize.width / 2, winSize.height / 2, 5, 5);
        this.firstPixel1 = this.containsPixel(ret1, this.pixel);
        this.firstPixel2 = this.containsPixel(ret2, this.pixel);
    },
    getExpectedResult:function () {
        var ret = {"firstPixel1":true, "firstPixel2":true, "secondPixel1":true, "pixel2":true};
        return JSON.stringify(ret);
    },
    getCurrentResult:function () {
        var pixel1 = this.readPixels(winSize.width / 4, winSize.height / 2, 5, 5);
        var pixel2 = this.readPixels(winSize.width / 2, winSize.height / 2, 5, 5);
        var secondPixel1 = this.containsPixel(pixel1, this.pixel);
        var secondPixel2 = this.containsPixel(pixel2, this.pixel);
        var ret = {"firstPixel1":this.firstPixel1, "firstPixel2":this.firstPixel2, "secondPixel1":secondPixel1, "pixel2":secondPixel2};
        return JSON.stringify(ret);
    }
});

//------------------------------------------------------------------
//
// SpriteBatchNodeChildren
//
//------------------------------------------------------------------
var SpriteBatchNodeChildren = SpriteTestDemo.extend({
    _title:"SpriteBatchNode Grand Children",

    ctor:function () {
        //----start29----ctor
        this._super();
        // parents
        var batch = new cc.SpriteBatchNode(s_grossini, 50);
        this.addChild(batch, 0, TAG_SPRITE_BATCH_NODE);

        spriteFrameCache.addSpriteFrames(s_grossiniPlist);

        var sprite1 = new cc.Sprite(spriteFrameCache.getSpriteFrame("grossini_dance_01.png"));
        sprite1.x = winSize.width / 3;
        sprite1.y = winSize.height / 2;

        var sprite2 = new cc.Sprite(spriteFrameCache.getSpriteFrame("grossini_dance_02.png"));
        sprite2.x = 50;
        sprite2.y = 50;

        var sprite3 = new cc.Sprite(spriteFrameCache.getSpriteFrame("grossini_dance_03.png"));
        sprite3.x = -50;
        sprite3.y = -50;

        batch.addChild(sprite1);
        sprite1.addChild(sprite2);
        sprite1.addChild(sprite3);

        // BEGIN NEW CODE
        var animFrames = [];
        var str = "";
        for (var i = 1; i < 15; i++) {
            str = "grossini_dance_" + (i < 10 ? ("0" + i) : i) + ".png";
            var frame = spriteFrameCache.getSpriteFrame(str);
            animFrames.push(frame);
        }

        var animation = new cc.Animation(animFrames, 0.2);
        sprite1.runAction(cc.animate(animation).repeatForever());
        // END NEW CODE

        var action = cc.moveBy(2, cc.p(200, 0));
        var action_back = action.reverse();
        var action_rot = cc.rotateBy(2, 360);
        var action_s = cc.scaleBy(2, 2);
        var action_s_back = action_s.reverse();

        var seq2 = action_rot.reverse();
        sprite2.runAction(seq2.repeatForever());

        sprite1.runAction(action_rot.repeatForever());
        sprite1.runAction(cc.sequence(action, action_back).repeatForever());
        sprite1.runAction(cc.sequence(action_s, action_s_back).repeatForever());
        //----end29----
    },
    //
    // Automation
    //
    testDuration:0.5,
    pixel:{"0":255, "1":204, "2":153, "3":255},
    getExpectedResult:function () {
        var ret = {"pixel1":"yes", "pixel2":"yes"};
        return JSON.stringify(ret);
    },
    getCurrentResult:function () {
        var ret1 = this.readPixels(winSize.width / 3 - 47, winSize.height / 2 + 107, 5, 5);
        var ret2 = this.readPixels(winSize.width / 3 + 95, winSize.height / 2 - 5, 5, 5);
        var ret = {"pixel1":this.containsPixel(ret1, this.pixel) ? "yes" : "no", "pixel2":this.containsPixel(ret2, this.pixel) ? "yes" : "no"};
        return JSON.stringify(ret);
    }
});

//------------------------------------------------------------------
//
// SpriteBatchNodeChildrenZ
//
//------------------------------------------------------------------
var SpriteBatchNodeChildrenZ = SpriteTestDemo.extend({

    _title:"SpriteBatchNode Children Z",

    ctor:function () {
        //----start30----ctor
        this._super();
        // parents
        var batch;
        var sprite1, sprite2, sprite3;
        spriteFrameCache.addSpriteFrames(s_grossiniPlist);

        // test 1
        batch = new cc.SpriteBatchNode(s_grossini, 50);
        this.addChild(batch, 0, TAG_SPRITE_BATCH_NODE);

        sprite1 = new cc.Sprite(spriteFrameCache.getSpriteFrame("grossini_dance_01.png"));
        sprite1.x = winSize.width / 3;
        sprite1.y = winSize.height / 2;

        sprite2 = new cc.Sprite(spriteFrameCache.getSpriteFrame("grossini_dance_02.png"));
        sprite2.x = 20;
        sprite2.y = 30;

        sprite3 = new cc.Sprite(spriteFrameCache.getSpriteFrame("grossini_dance_03.png"));
        sprite3.x = -20;
        sprite3.y = 30;

        batch.addChild(sprite1);
        sprite1.addChild(sprite2, 2);
        sprite1.addChild(sprite3, -2);

        // test 2
        batch = new cc.SpriteBatchNode(s_grossini, 50);
        this.addChild(batch, 0, TAG_SPRITE_BATCH_NODE);

        sprite1 = new cc.Sprite(spriteFrameCache.getSpriteFrame("grossini_dance_01.png"));
        sprite1.x = 2 * winSize.width / 3;
        sprite1.y = winSize.height / 2;

        sprite2 = new cc.Sprite(spriteFrameCache.getSpriteFrame("grossini_dance_02.png"));
        sprite2.x = 20;
        sprite2.y = 30;

        sprite3 = new cc.Sprite(spriteFrameCache.getSpriteFrame("grossini_dance_03.png"));
        sprite3.x = -20;
        sprite3.y = 30;

        batch.addChild(sprite1);
        sprite1.addChild(sprite2, -2);
        sprite1.addChild(sprite3, 2);

        // test 3
        batch = new cc.SpriteBatchNode(s_grossini, 50);
        this.addChild(batch, 0, TAG_SPRITE_BATCH_NODE);

        sprite1 = new cc.Sprite(spriteFrameCache.getSpriteFrame("grossini_dance_01.png"));
        sprite1.x = winSize.width / 2 - 90;
        sprite1.y = winSize.height / 4;

        sprite2 = new cc.Sprite(spriteFrameCache.getSpriteFrame("grossini_dance_02.png"));
        sprite2.x = winSize.width / 2 - 60;
        sprite2.y = winSize.height / 4;

        sprite3 = new cc.Sprite(spriteFrameCache.getSpriteFrame("grossini_dance_03.png"));
        sprite3.x = winSize.width / 2 - 30;
        sprite3.y = winSize.height / 4;

        batch.addChild(sprite1, 10);
        batch.addChild(sprite2, -10);
        batch.addChild(sprite3, -5);

        // test 4
        batch = new cc.SpriteBatchNode(s_grossini, 50);
        this.addChild(batch, 0, TAG_SPRITE_BATCH_NODE);

        sprite1 = new cc.Sprite(spriteFrameCache.getSpriteFrame("grossini_dance_01.png"));
        sprite1.x = winSize.width / 2 + 30;
        sprite1.y = winSize.height / 4;

        sprite2 = new cc.Sprite(spriteFrameCache.getSpriteFrame("grossini_dance_02.png"));
        sprite2.x = winSize.width / 2 + 60;
        sprite2.y = winSize.height / 4;

        sprite3 = new cc.Sprite(spriteFrameCache.getSpriteFrame("grossini_dance_03.png"));
        sprite3.x = winSize.width / 2 + 90;
        sprite3.y = winSize.height / 4;

        batch.addChild(sprite1, -10);
        batch.addChild(sprite2, -5);
        batch.addChild(sprite3, -2);
        //----end30----
    },
    //
    // Automation
    //
    testDuration:1,
    pixel1:{"0":51, "1":0, "2":51, "3":255},
    pixel2:{"0":51, "1":0, "2":51, "3":255},
    pixel3:{"0":255, "1":204, "2":153, "3":255},
    getExpectedResult:function () {
        var ret = {"pixel1":"yes", "pixel2":"yes", "pixel3":"yes"};
        return JSON.stringify(ret);
    },
    getCurrentResult:function () {
        var ret1 = this.readPixels(2 * winSize.width / 3 - 20, winSize.height / 2, 5, 5);
        var ret2 = this.readPixels(winSize.width / 3 - 20, winSize.height / 2 + 115, 5, 5);
        var ret3 = this.readPixels(winSize.width / 2 + 30, winSize.height / 4 - 10, 5, 5);
        var ret = {"pixel1":this.containsPixel(ret1, this.pixel1) ? "yes" : "no",
            "pixel2":!this.containsPixel(ret2, this.pixel2) ? "yes" : "no",
            "pixel3":this.containsPixel(ret3, this.pixel3) ? "yes" : "no"};
        return JSON.stringify(ret);
    }
});

//------------------------------------------------------------------
//
// SpriteChildrenVisibility
//
//------------------------------------------------------------------
var SpriteChildrenVisibility = SpriteTestDemo.extend({
    _title:"Sprite & SpriteBatchNode Visibility",

    ctor:function () {
        //----start31----ctor
        this._super();

        spriteFrameCache.addSpriteFrames(s_grossiniPlist);
        //
        // SpriteBatchNode
        //
        // parents
        var aParent = new cc.SpriteBatchNode(s_grossini, 50);
        aParent.x = winSize.width / 3;
        aParent.y = winSize.height / 2;
        this.addChild(aParent, 0);

        var sprite1 = new cc.Sprite(spriteFrameCache.getSpriteFrame("grossini_dance_01.png"));
        sprite1.x = 0;
        sprite1.y = 0;

        var sprite2 = new cc.Sprite(spriteFrameCache.getSpriteFrame("grossini_dance_02.png"));
        sprite2.x = 20;
        sprite2.y = 30;

        var sprite3 = new cc.Sprite(spriteFrameCache.getSpriteFrame("grossini_dance_03.png"));
        sprite3.x = -20;
        sprite3.y = 30;

        aParent.addChild(sprite1);
        sprite1.addChild(sprite2, -2);
        sprite1.addChild(sprite3, 2);

        sprite1.runAction(cc.blink(5, 10));

        //
        // Sprite
        //
        aParent = new cc.Node();
        aParent.x = 2 * winSize.width / 3;
        aParent.y = winSize.height / 2;
        this.addChild(aParent, 0);

        sprite1 = new cc.Sprite(spriteFrameCache.getSpriteFrame("grossini_dance_01.png"));
        sprite1.x = 0;
        sprite1.y = 0;

        sprite2 = new cc.Sprite(spriteFrameCache.getSpriteFrame("grossini_dance_02.png"));
        sprite2.x = 20;
        sprite2.y = 30;

        sprite3 = new cc.Sprite(spriteFrameCache.getSpriteFrame("grossini_dance_03.png"));
        sprite3.x = -20;
        sprite3.y = 30;

        aParent.addChild(sprite1);
        sprite1.addChild(sprite2, -2);
        sprite1.addChild(sprite3, 2);

        sprite1.runAction(cc.blink(5, 10));
        //----end31----
    },
    //
    // Automation
    //
    testDuration:1.7,
    pixel1:{"0":0, "1":0, "2":0, "3":255},
    pixel2:{"0":255, "1":204, "2":153, "3":255},
    visible1:null,
    visible2:null,
    setupAutomation:function () {
        this.scheduleOnce(this.getSpriteVisible, 1.2);
    },
    getSpriteVisible:function () {
        var ret1 = this.readPixels(winSize.width / 3, winSize.height / 2 + 38, 5, 5);
        var ret2 = this.readPixels(2 * winSize.width / 3, winSize.height / 2 + 38, 5, 5);
        this.visible1 = this.containsPixel(ret1, this.pixel1) ? "true" : "false";
        this.visible2 = this.containsPixel(ret2, this.pixel1) ? "true" : "false";
    },
    getExpectedResult:function () {
        var ret = {"visible1":"true", "visible2":"true", "visible3":"false", "visible4":"false"};
        return JSON.stringify(ret);
    },
    getCurrentResult:function () {
        var ret1 = this.readPixels(winSize.width / 3, winSize.height / 2 + 38, 5, 5);
        var ret2 = this.readPixels(2 * winSize.width / 3, winSize.height / 2 + 38, 5, 5);
        this.visible3 = this.containsPixel(ret1, this.pixel2) ? "true" : "false";
        this.visible4 = this.containsPixel(ret2, this.pixel2) ? "true" : "false";
        var ret = {"visible1":this.visible1, "visible2":this.visible2, "visible3":this.visible3, "visible4":this.visible4};
        return JSON.stringify(ret);
    }
});

//------------------------------------------------------------------
//
// SpriteChildrenVisibilityIssue665
//
//------------------------------------------------------------------
var SpriteChildrenVisibilityIssue665 = SpriteTestDemo.extend({

    _title:"Sprite & SpriteBatchNode Visibility",
    _subtitle:"No sprites should be visible",

    ctor:function () {
        //----start32----ctor
        this._super();
        spriteFrameCache.addSpriteFrames(s_grossiniPlist);
        //
        // SpriteBatchNode
        //
        // parents
        var aParent = new cc.SpriteBatchNode(s_grossini, 50);
        aParent.x = winSize.width / 3;
        aParent.y = winSize.height / 2;
        this.addChild(aParent, 0);

        var sprite1 = new cc.Sprite(spriteFrameCache.getSpriteFrame("grossini_dance_01.png"));
        sprite1.x = 0;
        sprite1.y = 0;

        var sprite2 = new cc.Sprite(spriteFrameCache.getSpriteFrame("grossini_dance_02.png"));
        sprite2.x = 20;
        sprite2.y = 30;

        var sprite3 = new cc.Sprite(spriteFrameCache.getSpriteFrame("grossini_dance_03.png"));
        sprite3.x = -20;
        sprite3.y = 30;

        // test issue #665
        sprite1.visible = false;

        aParent.addChild(sprite1);
        sprite1.addChild(sprite2, -2);
        sprite1.addChild(sprite3, 2);

        //
        // Sprite
        //
        aParent = new cc.Node();
        aParent.x = 2 * winSize.width / 3;
        aParent.y = winSize.height / 2;
        this.addChild(aParent, 0);

        sprite1 = new cc.Sprite(spriteFrameCache.getSpriteFrame("grossini_dance_01.png"));
        sprite1.x = 0;
        sprite1.y = 0;

        sprite2 = new cc.Sprite(spriteFrameCache.getSpriteFrame("grossini_dance_02.png"));
        sprite2.x = 20;
        sprite2.y = 30;

        sprite3 = new cc.Sprite(spriteFrameCache.getSpriteFrame("grossini_dance_03.png"));
        sprite3.x = -20;
        sprite3.y = 30;

        // test issue #665
        sprite1.visible = false;

        aParent.addChild(sprite1);
        sprite1.addChild(sprite2, -2);
        sprite1.addChild(sprite3, 2);
        //----end32----
    },
    //
    // Automation
    //
    testDuration:1,
    pixel:{"0":0, "1":0, "2":0, "3":255},
    getExpectedResult:function () {
        var ret = {"visible1":"false", "visible2":"false"};
        return JSON.stringify(ret);
    },
    getCurrentResult:function () {
        var ret1 = this.readPixels(winSize.width / 3, winSize.height / 2 + 38, 5, 5);
        var ret2 = this.readPixels(2 * winSize.width / 3, winSize.height / 2 + 38, 5, 5);
        var ret = {"visible1":this.containsPixel(ret1, this.pixel) ? "false" : "true", "visible2":this.containsPixel(ret2, this.pixel) ? "false" : "true"};
        return JSON.stringify(ret);
    }
});

//------------------------------------------------------------------
//
// SpriteChildrenAnchorPoint
//
//------------------------------------------------------------------
var SpriteChildrenAnchorPoint = SpriteTestDemo.extend({

    _title:"Sprite: children + anchor",

    ctor:function () {
        //----start33----ctor
        this._super();
        spriteFrameCache.addSpriteFrames(s_grossiniPlist);

        var aParent = new cc.Node();
        this.addChild(aParent, 0);

        // anchor (0,0)
        var sprite1 = new cc.Sprite(spriteFrameCache.getSpriteFrame("grossini_dance_08.png"));
        sprite1.x = winSize.width / 4;
        sprite1.y = winSize.height / 2;
        sprite1.anchorX = 0;
        sprite1.anchorY = 0;

        var sprite2 = new cc.Sprite(spriteFrameCache.getSpriteFrame("grossini_dance_02.png"));
        sprite2.x = 20;
        sprite2.y = 30;

        var sprite3 = new cc.Sprite(spriteFrameCache.getSpriteFrame("grossini_dance_03.png"));
        sprite3.x = -20;
        sprite3.y = 30;

        var sprite4 = new cc.Sprite(spriteFrameCache.getSpriteFrame("grossini_dance_04.png"));
        sprite4.x = 0;
        sprite4.y = 0;
        sprite4.scale = 0.5;

        aParent.addChild(sprite1);
        sprite1.addChild(sprite2, -2);
        sprite1.addChild(sprite3, -2);
        sprite1.addChild(sprite4, 3);

        var point = new cc.Sprite(s_pathR1);
        point.scale = 0.25;
	    point.x = sprite1.x;
	    point.y = sprite1.y;
        this.addChild(point, 10);

        // anchor (0.5, 0.5)
        sprite1 = new cc.Sprite(spriteFrameCache.getSpriteFrame("grossini_dance_08.png"));
        sprite1.x = winSize.width / 2;
        sprite1.y = winSize.height / 2;
        sprite1.anchorX = 0.5;
        sprite1.anchorY = 0.5;

        sprite2 = new cc.Sprite(spriteFrameCache.getSpriteFrame("grossini_dance_02.png"));
        sprite2.x = 20;
        sprite2.y = 30;

        sprite3 = new cc.Sprite(spriteFrameCache.getSpriteFrame("grossini_dance_03.png"));
        sprite3.x = -20;
        sprite3.y = 30;

        sprite4 = new cc.Sprite(spriteFrameCache.getSpriteFrame("grossini_dance_04.png"));
        sprite4.x = 0;
        sprite4.y = 0;
        sprite4.scale = 0.5;

        aParent.addChild(sprite1);
        sprite1.addChild(sprite2, -2);
        sprite1.addChild(sprite3, -2);
        sprite1.addChild(sprite4, 3);

        point = new cc.Sprite(s_pathR1);
        point.scale = 0.25;
	    point.x = sprite1.x;
	    point.y = sprite1.y;
        this.addChild(point, 10);

        // anchor (1,1)
        sprite1 = new cc.Sprite(spriteFrameCache.getSpriteFrame("grossini_dance_08.png"));
        sprite1.x = winSize.width / 2 + winSize.width / 4;
        sprite1.y = winSize.height / 2;
        sprite1.anchorX = 1;
        sprite1.anchorY = 1;

        sprite2 = new cc.Sprite(spriteFrameCache.getSpriteFrame("grossini_dance_02.png"));
        sprite2.x = 20;
        sprite2.y = 30;

        sprite3 = new cc.Sprite(spriteFrameCache.getSpriteFrame("grossini_dance_03.png"));
        sprite3.x = -20;
        sprite3.y = 30;

        sprite4 = new cc.Sprite(spriteFrameCache.getSpriteFrame("grossini_dance_04.png"));
        sprite4.x = 0;
        sprite4.y = 0;
        sprite4.scale = 0.5;

        aParent.addChild(sprite1);
        sprite1.addChild(sprite2, -2);
        sprite1.addChild(sprite3, -2);
        sprite1.addChild(sprite4, 3);

        point = new cc.Sprite(s_pathR1);
        point.scale = 0.25;
	    point.x = sprite1.x;
	    point.y = sprite1.y;
        this.addChild(point, 10);
        //----end33----
    },
    //
    // Automation
    //
    testDuration:1,
    pixel:{"0":255, "1":204, "2":153, "3":255},
    getExpectedResult:function () {
        var ret = {"pixel1":"yes", "pixel2":"yes", "pixel2":"yes", "pixel3":"yes"};
        return JSON.stringify(ret);
    },
    getCurrentResult:function () {
        var ret1 = this.readPixels(3 * winSize.width / 4 - 87, winSize.height / 2 - 99, 5, 5);
        var ret2 = this.readPixels(2 * winSize.width / 4 - 59, winSize.height / 2 - 66, 5, 5);
        var ret3 = this.readPixels(winSize.width / 4 - 15, winSize.height / 2 - 6, 5, 5);
        var ret = {"pixel1":this.containsPixel(ret1, this.pixel) ? "yes" : "no", "pixel2":this.containsPixel(ret2, this.pixel) ? "yes" : "no", "pixel3":this.containsPixel(ret3, this.pixel) ? "yes" : "no"};
        return JSON.stringify(ret);
    }
});

//------------------------------------------------------------------
//
// SpriteBatchNodeChildrenAnchorPoint
//
//------------------------------------------------------------------
var SpriteBatchNodeChildrenAnchorPoint = SpriteTestDemo.extend({

    _title:"SpriteBatchNode: children + anchor",

    ctor:function () {
        //----start34----ctor
        this._super();

        spriteFrameCache.addSpriteFrames(s_grossiniPlist);
        //
        // SpriteBatchNode
        //
        // parents
        var aParent = new cc.SpriteBatchNode(s_grossini, 50);
        this.addChild(aParent, 0);

        // anchor (0,0)
        var sprite1 = new cc.Sprite(spriteFrameCache.getSpriteFrame("grossini_dance_08.png"));
        sprite1.x = winSize.width / 4;
        sprite1.y = winSize.height / 2;
        sprite1.anchorX = 0;
        sprite1.anchorY = 0;

        var sprite2 = new cc.Sprite(spriteFrameCache.getSpriteFrame("grossini_dance_02.png"));
        sprite2.x = 20;
        sprite2.y = 30;

        var sprite3 = new cc.Sprite(spriteFrameCache.getSpriteFrame("grossini_dance_03.png"));
        sprite3.x = -20;
        sprite3.y = 30;

        var sprite4 = new cc.Sprite(spriteFrameCache.getSpriteFrame("grossini_dance_04.png"));
        sprite4.x = 0;
        sprite4.y = 0;
        sprite4.scale = 0.5;

        aParent.addChild(sprite1);
        sprite1.addChild(sprite2, -2);
        sprite1.addChild(sprite3, -2);
        sprite1.addChild(sprite4, 3);

        var point = new cc.Sprite(s_pathR1);
        point.scale = 0.25;
	    point.x = sprite1.x;
	    point.y = sprite1.y;
        this.addChild(point, 10);

        // anchor (0.5, 0.5)
        sprite1 = new cc.Sprite(spriteFrameCache.getSpriteFrame("grossini_dance_08.png"));
        sprite1.x = winSize.width / 2;
        sprite1.y = winSize.height / 2;
        sprite1.anchorX = 0.5;
        sprite1.anchorY = 0.5;

        sprite2 = new cc.Sprite(spriteFrameCache.getSpriteFrame("grossini_dance_02.png"));
        sprite2.x = 20;
        sprite2.y = 30;

        sprite3 = new cc.Sprite(spriteFrameCache.getSpriteFrame("grossini_dance_03.png"));
        sprite3.x = -20;
        sprite3.y = 30;

        sprite4 = new cc.Sprite(spriteFrameCache.getSpriteFrame("grossini_dance_04.png"));
        sprite4.x = 0;
        sprite4.y = 0;
        sprite4.scale = 0.5;

        aParent.addChild(sprite1);
        sprite1.addChild(sprite2, -2);
        sprite1.addChild(sprite3, -2);
        sprite1.addChild(sprite4, 3);

        point = new cc.Sprite(s_pathR1);
        point.scale = 0.25;
        point.x = sprite1.x;
	    point.y = sprite1.y;
        this.addChild(point, 10);


        // anchor (1,1)
        sprite1 = new cc.Sprite(spriteFrameCache.getSpriteFrame("grossini_dance_08.png"));
        sprite1.x = winSize.width / 2 + winSize.width / 4;
        sprite1.y = winSize.height / 2;
        sprite1.anchorX = 1;
        sprite1.anchorY = 1;

        sprite2 = new cc.Sprite(spriteFrameCache.getSpriteFrame("grossini_dance_02.png"));
        sprite2.x = 20;
        sprite2.y = 30;

        sprite3 = new cc.Sprite(spriteFrameCache.getSpriteFrame("grossini_dance_03.png"));
        sprite3.x = -20;
        sprite3.y = 30;

        sprite4 = new cc.Sprite(spriteFrameCache.getSpriteFrame("grossini_dance_04.png"));
        sprite4.x = 0;
        sprite4.y = 0;
        sprite4.scale = 0.5;

        aParent.addChild(sprite1);
        sprite1.addChild(sprite2, -2);
        sprite1.addChild(sprite3, -2);
        sprite1.addChild(sprite4, 3);

        point = new cc.Sprite(s_pathR1);
        point.scale = 0.25;
        point.x = sprite1.x;
	    point.y = sprite1.y;
        this.addChild(point, 10);
        //----end34----
    },
    //
    // Automation
    //
    testDuration:1,
    pixel:{"0":255, "1":204, "2":153, "3":255},
    getExpectedResult:function () {
        var ret = {"pixel1":"yes", "pixel2":"yes", "pixel2":"yes", "pixel3":"yes"};
        return JSON.stringify(ret);
    },
    getCurrentResult:function () {
        var ret1 = this.readPixels(3 * winSize.width / 4 - 87, winSize.height / 2 - 99, 5, 5);
        var ret2 = this.readPixels(2 * winSize.width / 4 - 59, winSize.height / 2 - 66, 5, 5);
        var ret3 = this.readPixels(winSize.width / 4 - 15, winSize.height / 2 - 6, 5, 5);
        var ret = {"pixel1":this.containsPixel(ret1, this.pixel) ? "yes" : "no", "pixel2":this.containsPixel(ret2, this.pixel) ? "yes" : "no", "pixel3":this.containsPixel(ret3, this.pixel) ? "yes" : "no"};
        return JSON.stringify(ret);
    }
});

//------------------------------------------------------------------
//
// SpriteBatchNodeChildrenScale
//
//------------------------------------------------------------------
var SpriteBatchNodeChildrenScale = SpriteTestDemo.extend({

    _title:"Sprite/BatchNode + child + scale + rot",

    ctor:function () {
        //----start35----ctor
        this._super();
        spriteFrameCache.addSpriteFrames(s_grossini_familyPlist);

        var rot = cc.rotateBy(10, 360);
        var seq = rot.repeatForever();

        //
        // Children + Scale using Sprite
        // Test 1
        //
        var aParent = new cc.Node();
        var sprite1 = new cc.Sprite(spriteFrameCache.getSpriteFrame("grossinis_sister1.png"));
        sprite1.x = winSize.width / 4;
        sprite1.y = winSize.height / 4;
        sprite1.scaleX = 0.5;
        sprite1.scaleY = 2.0;
        sprite1.runAction(seq);


        var sprite2 = new cc.Sprite(spriteFrameCache.getSpriteFrame("grossinis_sister2.png"));
        sprite2.x = 50;
        sprite2.y = 0;

        this.addChild(aParent);
        aParent.addChild(sprite1);
        sprite1.addChild(sprite2);

        rot = cc.rotateBy(10, 360);
        seq = rot.repeatForever();
        //
        // Children + Scale using SpriteBatchNode
        // Test 2
        //
        aParent = new cc.SpriteBatchNode(s_grossini_family);
        sprite1 = new cc.Sprite(spriteFrameCache.getSpriteFrame("grossinis_sister1.png"));
        sprite1.x = 3 * winSize.width / 4;
        sprite1.y = winSize.height / 4;
        sprite1.scaleX = 0.5;
        sprite1.scaleY = 2.0;
        sprite1.runAction(seq);

        sprite2 = new cc.Sprite(spriteFrameCache.getSpriteFrame("grossinis_sister2.png"));
        sprite2.x = 50;
        sprite2.y = 0;

        this.addChild(aParent);
        aParent.addChild(sprite1);
        sprite1.addChild(sprite2);

        rot = cc.rotateBy(10, 360);
        seq = rot.repeatForever();
        //
        // Children + Scale using Sprite
        // Test 3
        //
        aParent = new cc.Node();
        sprite1 = new cc.Sprite(spriteFrameCache.getSpriteFrame("grossinis_sister1.png"));
        sprite1.x = winSize.width / 4;
        sprite1.y = 2 * winSize.height / 3;
        sprite1.scaleX = 1.5;
        sprite1.scaleY = 0.5;
        sprite1.runAction(seq);

        sprite2 = new cc.Sprite(spriteFrameCache.getSpriteFrame("grossinis_sister2.png"));
        sprite2.x = 50;
        sprite2.y = 0;

        this.addChild(aParent);
        aParent.addChild(sprite1);
        sprite1.addChild(sprite2);

        rot = cc.rotateBy(10, 360);
        seq = rot.repeatForever();
        //
        // Children + Scale using Sprite
        // Test 4
        //
        aParent = new cc.SpriteBatchNode(s_grossini_family);
        sprite1 = new cc.Sprite(spriteFrameCache.getSpriteFrame("grossinis_sister1.png"));
        sprite1.x = 3 * winSize.width / 4;
        sprite1.y = 2 * winSize.height / 3;
        sprite1.scaleX = 1.5;
        sprite1.scaleY = 0.5;
        sprite1.runAction(seq);

        sprite2 = new cc.Sprite(spriteFrameCache.getSpriteFrame("grossinis_sister2.png"));
        sprite2.x = 50;
        sprite2.y = 0;

        this.addChild(aParent);
        aParent.addChild(sprite1);
        sprite1.addChild(sprite2);
        //----end35----
    },
    //
    // Automation
    //
    testDuration:2.5,
    pixel1:{"0":56, "1":116, "2":142, "3":255},
    pixel2:{"0":0, "1":0, "2":0, "3":255},
    getExpectedResult:function () {
        var ret = {"pixel1":"yes", "pixel2":"yes", "pixel3":"yes", "pixel4":"yes"};
        return JSON.stringify(ret);
    },
    getCurrentResult:function () {
        var ret1 = this.readPixels(winSize.width / 4 - 31, 2 * winSize.height / 3 + 16, 5, 5);
        var ret2 = this.readPixels(winSize.width / 4 - 38, 2 * winSize.height / 3 + 16, 3, 3);
        var ret3 = this.readPixels(3 * winSize.width / 4 - 31, 2 * winSize.height / 3 + 16, 5, 5);
        var ret4 = this.readPixels(3 * winSize.width / 4 - 38, 2 * winSize.height / 3 + 16, 3, 3);
        var ret = {"pixel1":this.containsPixel(ret1, this.pixel1) ? "yes" : "no",
            "pixel2":this.containsPixel(ret2, this.pixel2) ? "yes" : "no",
            "pixel3":this.containsPixel(ret3, this.pixel1) ? "yes" : "no",
            "pixel4":this.containsPixel(ret4, this.pixel2) ? "yes" : "no"};
        return JSON.stringify(ret);
    }
});

//------------------------------------------------------------------
//
// SpriteChildrenChildren
//
//------------------------------------------------------------------
var SpriteChildrenChildren = SpriteTestDemo.extend({
    _title:"Sprite multiple levels of children",

    ctor:function () {
        //----start36----ctor
        this._super();

        spriteFrameCache.addSpriteFrames(s_ghostsPlist);

        var rot = cc.rotateBy(10, 360);
        var seq = rot.repeatForever();

        var rot_back = rot.reverse();
        var rot_back_fe = rot_back.repeatForever();

        //
        // SpriteBatchNode: 3 levels of children
        //
        var aParent = new cc.Node();
        this.addChild(aParent);

        // parent
        var l1 = new cc.Sprite(spriteFrameCache.getSpriteFrame("father.gif"));
        l1.x = winSize.width / 2;
        l1.y = winSize.height / 2;
        l1.runAction(seq.clone());
        aParent.addChild(l1);
        var l1W = l1.width, l1H = l1.height;

        // child left
        var l2a = new cc.Sprite(spriteFrameCache.getSpriteFrame("sister1.gif"));
        l2a.x = -50 + l1W / 2;
        l2a.y = 0 + l1H / 2;
        l2a.runAction(rot_back_fe.clone());
        l1.addChild(l2a);
        var l2aW = l2a.width, l2aH = l2a.height;


        // child right
        var l2b = new cc.Sprite(spriteFrameCache.getSpriteFrame("sister2.gif"));
        l2b.x = +50 + l1W / 2;
        l2b.y = 0 + l1H / 2;
        l2b.runAction(rot_back_fe.clone());
        l1.addChild(l2b);
        var l2bW = l2b.width, l2bH = l2b.height;


        // child left bottom
        var l3a1 = new cc.Sprite(spriteFrameCache.getSpriteFrame("child1.gif"));
        l3a1.scale = 0.45;
        l3a1.x = 0 + l2aW / 2;
        l3a1.y = -100 + l2aH / 2;
        l2a.addChild(l3a1);

        // child left top
        var l3a2 = new cc.Sprite(spriteFrameCache.getSpriteFrame("child1.gif"));
        l3a2.scale = 0.45;
        l3a2.x = 0 + l2aW / 2;
        l3a2.y = +100 + l2aH / 2;
        l2a.addChild(l3a2);

        // child right bottom
        var l3b1 = new cc.Sprite(spriteFrameCache.getSpriteFrame("child1.gif"));
        l3b1.scale = 0.45;
        l3b1.setFlippedY(true);
        l3b1.x = 0 + l2bW / 2;
        l3b1.y = -100 + l2bH / 2;
        l2b.addChild(l3b1);

        // child right top
        var l3b2 = new cc.Sprite(spriteFrameCache.getSpriteFrame("child1.gif"));
        l3b2.scale = 0.45;
        l3b2.setFlippedY(true);
        l3b2.x = 0 + l2bW / 2;
        l3b2.y = +100 + l2bH / 2;
        l2b.addChild(l3b2);
        //----end36----
    },
    //
    // Automation
    //
    testDuration:4,
    pixel:{"0":153, "1":204, "2":153, "3":255},
    getExpectedResult:function () {
        var ret = {"pixel1":"yes", "pixel2":"yes", "pixel3":"yes", "pixel4":"yes"};
        return JSON.stringify(ret);
    },
    getCurrentResult:function () {
        var ret1 = this.readPixels(winSize.width / 2 + 42, winSize.height / 2 + 145, 5, 5);
        var ret2 = this.readPixels(winSize.width / 2 - 39, winSize.height / 2 + 55, 5, 5);
        var ret3 = this.readPixels(winSize.width / 2 - 39, winSize.height / 2 - 146, 5, 5);
        var ret4 = this.readPixels(winSize.width / 2 + 42, winSize.height / 2 - 56, 5, 5);
        var ret = {"pixel1":this.containsPixel(ret1, this.pixel) ? "yes" : "no",
            "pixel2":this.containsPixel(ret2, this.pixel) ? "yes" : "no",
            "pixel3":this.containsPixel(ret3, this.pixel) ? "yes" : "no",
            "pixel4":this.containsPixel(ret4, this.pixel) ? "yes" : "no"};
        return JSON.stringify(ret);
    }
});

//------------------------------------------------------------------
//
// SpriteBatchNodeChildrenChildren
//
//------------------------------------------------------------------
var SpriteBatchNodeChildrenChildren = SpriteTestDemo.extend({

    _title:"SpriteBatchNode multiple levels of children",

    ctor:function () {
        //----start37----ctor
        this._super();

        spriteFrameCache.addSpriteFrames(s_ghostsPlist);

        var rot = cc.rotateBy(10, 360);
        var seq = rot.repeatForever();

        var rot_back = rot.reverse();
        var rot_back_fe = rot_back.repeatForever();

        //
        // SpriteBatchNode: 3 levels of children
        //
        var aParent = new cc.SpriteBatchNode(s_ghosts);
        if ("opengl" in cc.sys.capabilities && cc._renderType === cc.game.RENDER_TYPE_WEBGL)
            aParent.texture.generateMipmap();
        this.addChild(aParent);

        // parent
        var l1 = new cc.Sprite(spriteFrameCache.getSpriteFrame("father.gif"));
        l1.x = winSize.width / 2;
        l1.y = winSize.height / 2;
        l1.runAction(seq.clone());
        aParent.addChild(l1);
        var l1W = l1.width, l1H = l1.height;

        // child left
        var l2a = new cc.Sprite(spriteFrameCache.getSpriteFrame("sister1.gif"));
        l2a.x = -50 + l1W / 2;
        l2a.y = 0 + l1H / 2;
        l2a.runAction(rot_back_fe.clone());
        l1.addChild(l2a);
        var l2aW = l2a.width, l2aH = l2a.height;


        // child right
        var l2b = new cc.Sprite(spriteFrameCache.getSpriteFrame("sister2.gif"));
        l2b.x = 50 + l1W / 2;
        l2b.y = 0 + l1H / 2;
        l2b.runAction(rot_back_fe.clone());
        l1.addChild(l2b);
        var l2bW = l2b.width, l2bH = l2b.height;


        // child left bottom
        var l3a1 = new cc.Sprite(spriteFrameCache.getSpriteFrame("child1.gif"));
        l3a1.scale = 0.45;
        l3a1.x = 0 + l2aW / 2;
        l3a1.y = -100 + l2aH / 2;
        l2a.addChild(l3a1);

        // child left top
        var l3a2 = new cc.Sprite(spriteFrameCache.getSpriteFrame("child1.gif"));
        l3a2.scale = 0.45;
        l3a2.x = 0 + l2aW / 2;
        l3a2.y = +100 + l2aH / 2;
        l2a.addChild(l3a2);

        // child right bottom
        var l3b1 = new cc.Sprite(spriteFrameCache.getSpriteFrame("child1.gif"));
        l3b1.scale = 0.45;
        l3b1.setFlippedY(true);
        l3b1.x = 0 + l2bW / 2;
        l3b1.y = -100 + l2bH / 2;
        l2b.addChild(l3b1);

        // child right top
        var l3b2 = new cc.Sprite(spriteFrameCache.getSpriteFrame("child1.gif"));
        l3b2.scale = 0.45;
        l3b2.setFlippedY(true);
        l3b2.x = 0 + l2bW / 2;
        l3b2.y = +100 + l2bH / 2;
        l2b.addChild(l3b2);
        //----end37----
    },
    //
    // Automation
    //
    testDuration:4,
    pixel:{"0":153, "1":204, "2":153, "3":255},
    getExpectedResult:function () {
        var ret = {"pixel1":"yes", "pixel2":"yes", "pixel3":"yes", "pixel4":"yes"};
        return JSON.stringify(ret);
    },
    getCurrentResult:function () {
        var ret1 = this.readPixels(winSize.width / 2 + 42, winSize.height / 2 + 145, 5, 5);
        var ret2 = this.readPixels(winSize.width / 2 - 39, winSize.height / 2 + 55, 5, 5);
        var ret3 = this.readPixels(winSize.width / 2 - 39, winSize.height / 2 - 146, 5, 5);
        var ret4 = this.readPixels(winSize.width / 2 + 42, winSize.height / 2 - 56, 5, 5);
        var ret = {"pixel1":this.containsPixel(ret1, this.pixel) ? "yes" : "no",
            "pixel2":this.containsPixel(ret2, this.pixel) ? "yes" : "no",
            "pixel3":this.containsPixel(ret3, this.pixel) ? "yes" : "no",
            "pixel4":this.containsPixel(ret4, this.pixel) ? "yes" : "no"};
        return JSON.stringify(ret);
    }
});

//------------------------------------------------------------------
//
// SpriteSubclass
//
//------------------------------------------------------------------
var MySprite1 = cc.Sprite.extend({
    _ivar:0,
	ctor: function(spriteFrameName) {
		this._super(spriteFrameName);
	}
});

var MySprite2 = cc.Sprite.extend({
    _ivar:0,
	ctor: function(name) {
		this._super(name);
	}
});

var SpriteSubclass = SpriteTestDemo.extend({
    _title:"Sprite subclass",
    _subtitle:"Testing initWithTexture:rect method",

    ctor:function () {
        //----start39----ctor
        this._super();

        spriteFrameCache.addSpriteFrames(s_ghostsPlist);
		var aParent = new cc.SpriteBatchNode(s_ghosts);

		// MySprite1
		var sprite = new MySprite1("#father.gif");
		sprite.x = winSize.width / 4;
		sprite.y = winSize.height / 2;
		aParent.addChild(sprite);
		this.addChild(aParent);

        // MySprite2
        var sprite2 = new MySprite2(s_pathGrossini);
        this.addChild(sprite2);
        sprite2.x = winSize.width / 4 * 3;
        sprite2.y = winSize.height / 2;
        //----end39----
    },
    //
    // Automation
    //
    testDuration:1,
    pixel1:{"0":249, "1":30, "2":20, "3":255},
    pixel2:{"0":255, "1":204, "2":153, "3":255},
    getExpectedResult:function () {
        var ret = {"pixel1":"yes", "pixel2":"yes"};
        return JSON.stringify(ret);
    },
    getCurrentResult:function () {
        var ret1 = this.readPixels(winSize.width / 4, winSize.height / 2 - 15, 5, 5);
        var ret2 = this.readPixels(winSize.width / 4 * 3, winSize.height / 2 + 44, 5, 5);
        var ret = {"pixel1":this.containsPixel(ret1, this.pixel1) ? "yes" : "no", "pixel2":this.containsPixel(ret2, this.pixel2) ? "yes" : "no"};
        return JSON.stringify(ret);
    }
});

//------------------------------------------------------------------
//
// AnimationCache
//
//------------------------------------------------------------------
var AnimationCacheTest = SpriteTestDemo.extend({

    _title:"AnimationCache",
    _subtitle:"Sprite should be animated",

    ctor:function () {
        //----start40----ctor
        this._super();
        spriteFrameCache.addSpriteFrames(s_grossiniPlist);
        spriteFrameCache.addSpriteFrames(s_grossini_grayPlist);
        spriteFrameCache.addSpriteFrames(s_grossini_bluePlist);

        //
        // create animation "dance"
        //
        var animFrames = [];
        var frame, animFrame;
        var str = "";
        for (var i = 1; i < 15; i++) {
            str = "grossini_dance_" + (i < 10 ? ("0" + i) : i) + ".png";
            frame = spriteFrameCache.getSpriteFrame(str);
            animFrame = new cc.AnimationFrame(frame, 1);
            animFrames.push(animFrame);
        }

        var animation = new cc.Animation(animFrames, 0.2);

        // Add an animation to the Cache
        cc.animationCache.addAnimation(animation, "dance");

        //
        // create animation "dance gray"
        //
        animFrames = [];
        for (i = 1; i < 15; i++) {
            str = "grossini_dance_gray_" + (i < 10 ? ("0" + i) : i) + ".png";
            frame = spriteFrameCache.getSpriteFrame(str);
            animFrames.push(frame);
        }

        animation = new cc.Animation(animFrames, 0.2);

        // Add an animation to the Cache
        cc.animationCache.addAnimation(animation, "dance_gray");

        //
        // create animation "dance blue"
        //
        animFrames = [];
        for (i = 1; i < 4; i++) {
            str = "grossini_blue_0" + i + ".png";
            frame = spriteFrameCache.getSpriteFrame(str);
            animFrames.push(frame);
        }

        animation = new cc.Animation(animFrames, 0.2);

        // Add an animation to the Cache
        cc.animationCache.addAnimation(animation, "dance_blue");

        var animCache = cc.animationCache;

        var normal = animCache.getAnimation("dance");
        normal.setRestoreOriginalFrame(true);
        var dance_grey = animCache.getAnimation("dance_gray");
        dance_grey.setRestoreOriginalFrame(true);
        var dance_blue = animCache.getAnimation("dance_blue");
        dance_blue.setRestoreOriginalFrame(true);

        var animN = cc.animate(normal);
        var animG = cc.animate(dance_grey);
        var animB = cc.animate(dance_blue);

        var seq = cc.sequence(animN, animG, animB);

        frame = spriteFrameCache.getSpriteFrame("grossini_dance_01.png");
        var grossini = new cc.Sprite(frame);

        grossini.x = winSize.width / 2;

        grossini.y = winSize.height / 2;
        this.addChild(grossini);

        // run the animation
        grossini.runAction(seq);
        //----end40----
    },
    //
    // Automation
    //
    testDuration:6.5,
    ePixel1:{"0":51, "1":0, "2":51, "3":255},
    ePixel2:{"0":15, "1":15, "2":15, "3":255},
    ePixel3:{"0":0, "1":38, "2":0, "3":255},
    cPixel1:null,
    cPixel2:null,
    cPixel3:null,
    setupAutomation:function () {
        //----start40----setupAutomation
        var fun1 = function () {
            this.cPixel1 = this.readPixels(winSize.width / 2, winSize.height / 2, 5, 5);
        }
        this.scheduleOnce(fun1, 0.4);

        var fun2 = function () {
            this.cPixel2 = this.readPixels(winSize.width / 2, winSize.height / 2, 5, 5);
        }
        this.scheduleOnce(fun2, 3.2);

        var fun3 = function () {
            this.cPixel3 = this.readPixels(winSize.width / 2, winSize.height / 2, 5, 5);
        }
        this.scheduleOnce(fun3, 6);
        //----end40----
    },
    getExpectedResult:function () {
        var ret = {"pixel1":"yes", "pixel2":"yes", "pixel3":"yes"};
        return JSON.stringify(ret);
    },
    getCurrentResult:function () {
        var ret = {"pixel1":this.containsPixel(this.cPixel1, this.ePixel1) ? "yes" : "no", "pixel2":this.containsPixel(this.cPixel2, this.ePixel2) ? "yes" : "no", "pixel3":this.containsPixel(this.cPixel3, this.ePixel3, true, 5) ? "yes" : "no"};
        return JSON.stringify(ret);
    }
});

var NodeSort = SpriteTestDemo.extend({
    _node:null,
    _sprite1:null,
    _sprite2:null,
    _sprite3:null,
    _sprite4:null,
    _sprite5:null,

    _title:"node sort same index",
    _subtitle:"tag order in console should be 2,1,3,4,5",

    ctor:function () {
        //----start49----ctor
        this._super();
        this._node = new cc.Node();
        this.addChild(this._node, 0, 0);

        this._sprite1 = new cc.Sprite(s_piece, cc.rect(128, 0, 64, 64));
        this._sprite1.x = 100;
        this._sprite1.y = 160;
        this._node.addChild(this._sprite1, -6, 1);

        this._sprite2 = new cc.Sprite(s_piece, cc.rect(128, 0, 64, 64));
        this._sprite2.x = 164;
        this._sprite2.y = 160;
        this._node.addChild(this._sprite2, -6, 2);

        this._sprite4 = new cc.Sprite(s_piece, cc.rect(128, 0, 64, 64));
        this._sprite4.x = 292;
        this._sprite4.y = 160;
        this._node.addChild(this._sprite4, -3, 4);

        this._sprite3 = new cc.Sprite(s_piece, cc.rect(128, 0, 64, 64));
        this._sprite3.x = 228;
        this._sprite3.y = 160;
        this._node.addChild(this._sprite3, -4, 3);

        this._sprite5 = new cc.Sprite(s_piece, cc.rect(128, 0, 64, 64));
        this._sprite5.x = 356;
        this._sprite5.y = 160;
        this._node.addChild(this._sprite5, -3, 5);

        this.schedule(this.reorderSprite);
        //----end49----
    },

    reorderSprite:function (dt) {
        //----start49----reorderSprite
        this.unschedule(this.reorderSprite);

        cc.log("Before reorder--");

        var i = 0;
        var child;
        var nodeChildren = this._node.children;
        for (i = 0; i < nodeChildren.length; i++) {
            child = nodeChildren[i];
            cc.log("tag:" + child.tag + "  z: " + child.zIndex);
        }

        //z-4
        this._node.reorderChild(this._node.children[0], -6);
        this._node.sortAllChildren();

        cc.log("After reorder--");
        nodeChildren = this._node.children;
        for (i = 0; i < nodeChildren.length; i++) {
            child = nodeChildren[i];
            cc.log("tag:" + child.tag + "  z: " +
                child.zIndex);
            this.testOrders.push(child.tag);
        }
        //----end49----
    },
    //
    // Automation
    //
    testDuration:1,
    testOrders:[],
    getExpectedResult:function () {
        return JSON.stringify([2, 1, 3, 4, 5]);
    },
    getCurrentResult:function () {
        return JSON.stringify(this.testOrders);
    }
});

var SpriteBatchNodeReorderOneChild = SpriteTestDemo.extend({
    _batchNode:null,
    _reoderSprite:null,

    _title:"SpriteBatchNode reorder 1 child",
    ctor:function () {
        //----start48----ctor
        this._super();

        spriteFrameCache.addSpriteFrames(s_ghostsPlist);
        //
        // SpriteBatchNode: 3 levels of children
        //
        var aParent = new cc.SpriteBatchNode(s_ghosts);

        this._batchNode = aParent;
        //[[aParent texture] generateMipmap];
        if ("opengl" in cc.sys.capabilities && cc._renderType === cc.game.RENDER_TYPE_WEBGL)
            aParent.texture.generateMipmap();
        this.addChild(aParent);

        // parent
        var l1 = new cc.Sprite("#father.gif");
        l1.x = winSize.width / 2;
        l1.y = winSize.height / 2;

        aParent.addChild(l1);
        var l1W = l1.width, l1H = l1.height;

        // child left
        var l2a = new cc.Sprite("#sister1.gif");
        l2a.x = -10 + l1W / 2;
        l2a.y = 0 + l1H / 2;

        l1.addChild(l2a, 1);
	    var l2aW = l2a.width, l2aH = l2a.height;

        // child right
        var l2b = new cc.Sprite("#sister2.gif");
        l2b.x = +50 + l1W / 2;
        l2b.y = 0 + l1H / 2;

        l1.addChild(l2b, 2);
        var l2bW = l2b.width, l2bH = l2b.height;

        // child left bottom
        var l3a1 = new cc.Sprite("#child1.gif");
        l3a1.scale = 0.45;
        l3a1.x = 0 + l2aW / 2;
        l3a1.y = -50 + l2aH / 2;
        l2a.addChild(l3a1, 1);

        // child left top
        var l3a2 = new cc.Sprite("#child1.gif");
        l3a2.scale = 0.45;
        l3a2.x = 0 + l2aW / 2;
        l3a2.y = +50 + l2aH / 2;
        l2a.addChild(l3a2, 2);

        this._reoderSprite = l2a;

        // child right bottom
        var l3b1 = new cc.Sprite("#child1.gif");
        l3b1.scale = 0.45;
        l3b1.setFlippedY(true);
        l3b1.x = 0 + l2bW / 2;
        l3b1.y = -50 + l2bH / 2;
        l2b.addChild(l3b1);

        // child right top
        var l3b2 = new cc.Sprite("#child1.gif");
        l3b2.scale = 0.45;
        l3b2.setFlippedY(true);
        l3b2.x = 0 + l2bW / 2;
        l3b2.y = 50 + l2bH / 2;
        l2b.addChild(l3b2);

        this.scheduleOnce(this.reorderSprite, 2.0);
        //----end48----
    },

    reorderSprite:function (dt) {
        this._reoderSprite.parent.reorderChild(this._reoderSprite, -1);
        this._batchNode.sortAllChildren();
        //cc.Sprite* child;
        //CCARRAY_FOREACH(batchNode.descendants,child) NSLog(@"tag %i",child.tag);
    },
    //
    // Automation
    //
    testDuration:2.5,
    pixel:{"0":0, "1":102, "2":255, "3":255},
    getExpectedResult:function () {
        var ret = {"pixel":"yes"};
        return JSON.stringify(ret);
    },
    getCurrentResult:function () {
        var ret1 = this.readPixels(winSize.width / 2 - 11, winSize.height / 2 + 33, 3, 3);
        var ret = {"pixel":this.containsPixel(ret1, this.pixel, false) ? "yes" : "no"};
        return JSON.stringify(ret);
    }
});

var SpriteBatchNodeSkewNegativeScaleChildren = SpriteTestDemo.extend({
    _title:"SpriteBatchNode + children + skew",
    _subtitle:"SpriteBatchNode skew + negative scale with children",

    ctor:function () {
        //----start51----ctor
        this._super();

        var cache = spriteFrameCache;
        cache.addSpriteFrames(s_grossiniPlist);
        cache.addSpriteFrames(s_grossini_grayPlist, s_grossini_gray);

        var spritebatch = new cc.SpriteBatchNode(s_grossini);
        this.addChild(spritebatch);

        for (var i = 0; i < 2; i++) {
            var sprite = new cc.Sprite("#grossini_dance_01.png");
            sprite.x = winSize.width / 4 * (i + 1);
            sprite.y = winSize.height / 2;

            // Skew
            var skewX = cc.skewBy(2, 45, 0);
            var skewX_back = skewX.reverse();
            var skewY = cc.skewBy(2, 0, 45);
            var skewY_back = skewY.reverse();

            if (i === 1)
                sprite.scale = -1.0;

            var seq_skew = cc.sequence(skewX, skewX_back, skewY, skewY_back);
            sprite.runAction(seq_skew.repeatForever());

            var child1 = new cc.Sprite("#grossini_dance_01.png");
            child1.x = sprite.width / 2.0;
            child1.y = sprite.height / 2.0;

            child1.scale = 0.8;
            sprite.addChild(child1);
            spritebatch.addChild(sprite, i);
        }
        //----end51----
    },
    //
    // Automation
    //
    testDuration:6,
    pixel1:{"0":51, "1":0, "2":51, "3":255},
    pixel2:{"0":0, "1":0, "2":0, "3":255},
    getExpectedResult:function () {
        var ret = {"pixel1":"yes", "pixel2":"yes"};
        return JSON.stringify(ret);
    },
    getCurrentResult:function () {
        var ret1 = this.readPixels(winSize.width / 4 + 21, winSize.height / 2 + 22, 5, 5);
        var ret2 = this.readPixels(winSize.width / 4 + 11, winSize.height / 2 + 14, 5, 5);
        var ret = {"pixel1":this.containsPixel(ret1, this.pixel1) ? "yes" : "no",
            "pixel2":!this.containsPixel(ret2, this.pixel2) ? "yes" : "no"};
        return JSON.stringify(ret);
    }
});

var SpriteSkewNegativeScaleChildren = SpriteTestDemo.extend({
    _title:"Sprite + children + skew",
    _subtitle:"Sprite skew + negative scale with children",

    ctor:function () {
        //----start50----ctor
        this._super();

        var cache = spriteFrameCache;
        cache.addSpriteFrames(s_grossiniPlist);
        cache.addSpriteFrames(s_grossini_grayPlist, s_grossini_gray);

        var parent = new cc.Node();
        this.addChild(parent);

        for (var i = 0; i < 2; i++) {
            var sprite = new cc.Sprite("#grossini_dance_01.png");
            sprite.x = winSize.width / 4 * (i + 1);
            sprite.y = winSize.height / 2;

            // Skew
            var skewX = cc.skewBy(2, 45, 0);
            var skewX_back = skewX.reverse();
            var skewY = cc.skewBy(2, 0, 45);
            var skewY_back = skewY.reverse();

            if (i === 1)
                sprite.scale = -1.0;

            var seq_skew = cc.sequence(skewX, skewX_back, skewY, skewY_back);
            sprite.runAction(seq_skew.repeatForever());

            var child1 = new cc.Sprite("#grossini_dance_01.png");
            child1.x = sprite.width / 2.0;
            child1.y = sprite.height / 2.0;

            sprite.addChild(child1);
            child1.scale = 0.8;
            parent.addChild(sprite, i);
        }
        //----end50----
    },
    //
    // Automation
    //
    testDuration:6,
    pixel1:{"0":51, "1":0, "2":51, "3":255},
    pixel2:{"0":0, "1":0, "2":0, "3":255},
    getExpectedResult:function () {
        var ret = {"pixel1":"yes", "pixel2":"yes"};
        return JSON.stringify(ret);
    },
    getCurrentResult:function () {
        var ret1 = this.readPixels(winSize.width / 4 + 21, winSize.height / 2 + 22, 5, 5);
        var ret2 = this.readPixels(winSize.width / 4 + 11, winSize.height / 2 + 14, 5, 5);
        var ret = {"pixel1":this.containsPixel(ret1, this.pixel1, false) ? "yes" : "no",
            "pixel2":!this.containsPixel(ret2, this.pixel2, false) ? "yes" : "no"};
        return JSON.stringify(ret);
    }
});

var DoubleSprite = cc.Sprite.extend({
    HD:false,

    ctor:function (fileName) {
	    this._super(fileName);
        //var resolutionType = texture.getResolutionType();
        //this.HD = ( resolutionType == cc.kCCResolutioniPhoneRetinaDisplay || resolutionType == kCCResolutioniPadRetinaDisplay );
    },

    setContentSize:function (size) {
        var newSize = cc.size(size.width, size.height);
        // If Retina Display and Texture is in HD then scale the vertex rect
        if (cc.contentScaleFactor() == 2 && !this.HD) {
            newSize.width *= 2;
            newSize.height *= 2;
        }
        this._super(newSize);
    },
	_setWidth:function (value) {
		// If Retina Display and Texture is in HD then scale the vertex rect
		if (cc.contentScaleFactor() == 2 && !this.HD) {
			value *= 2;
		}
		this._super(value);
	},
	_setHeight:function (value) {
		// If Retina Display and Texture is in HD then scale the vertex rect
		if (cc.contentScaleFactor() == 2 && !this.HD) {
			value *= 2;
		}
		this._super(value);
	},

    setVertexRect:function (rect) {
        // If Retina Display and Texture is in HD then scale the vertex rect
        if (cc.contentScaleFactor() == 2 && !this.HD) {
            rect.width *= 2;
            rect.height *= 2;
        }
        this._super(rect);
    }
});

cc.defineGetterSetter(DoubleSprite.prototype, "width", DoubleSprite.prototype._getWidth, DoubleSprite.prototype._setWidth);
cc.defineGetterSetter(DoubleSprite.prototype, "height", DoubleSprite.prototype._getHeight, DoubleSprite.prototype._setHeight);

var SpriteDoubleResolution = SpriteTestDemo.extend({

    _title:"Sprite Double resolution",
    _subtitle:"Retina Display. SD (left) should be equal to HD (right)",

    ctor:function () {
        //----start52----ctor
        this._super();

        //
        // LEFT: SD sprite
        //
        // there is no HD resolution file of grossini_dance_08.
        var spriteSD = new DoubleSprite(s_grossiniDance08);
        this.addChild(spriteSD);
        spriteSD.x = winSize.width / 4;
        spriteSD.y = winSize.height / 2;

        var child1_left = new DoubleSprite(s_grossiniDance08);
        spriteSD.addChild(child1_left);
        child1_left.x = -30;
        child1_left.y = 0;

        var child1_right = new cc.Sprite(s_pathGrossini);
        spriteSD.addChild(child1_right);
        child1_left.x = spriteSD.height;
        child1_left.y = 0;

        //
        // RIGHT: HD sprite
        //
        // there is an HD version of grossini.png
        var spriteHD = new cc.Sprite(s_pathGrossini);
        this.addChild(spriteHD);
        spriteHD.x = winSize.width / 4 * 3;
        spriteHD.y = winSize.height / 2;

        var child2_left = new DoubleSprite(s_grossiniDance08);
        spriteHD.addChild(child2_left);
        child2_left.x = -30;
        child2_left.y = 0;

        var child2_right = new cc.Sprite(s_pathGrossini);
        spriteHD.addChild(child2_right);
        child2_left.x = spriteHD.height;
        child2_left.y = 0;


        // Actions
        var scale = cc.scaleBy(2, 0.5);
        var scale_back = scale.reverse();
        var seq = cc.sequence(scale, scale_back);

        var seq_copy = seq.clone();

        spriteSD.runAction(seq);
        spriteHD.runAction(seq_copy);
        //----end52----
    }
});

var AnimationCacheFile = SpriteTestDemo.extend({

    _title:"AnimationCache - Load file",
    _subtitle:"Sprite should be animated",

    ctor:function () {
        //----start54----ctor
        this._super();
        var frameCache = spriteFrameCache;
        frameCache.addSpriteFrames(s_grossiniPlist);
        frameCache.addSpriteFrames(s_grossini_grayPlist);
        frameCache.addSpriteFrames(s_grossini_bluePlist);

        // Purge previously loaded animation
        if(cc.animationCache._clear)
	        cc.animationCache._clear();
        var animCache = cc.animationCache;

        // Add an animation to the Cache
        // XXX API-FIX XXX
        // renamed from addAnimationsWithFile to addAnimations
        animCache.addAnimations(s_animationsPlist);

        var normal = animCache.getAnimation("dance_1");
        normal.setRestoreOriginalFrame(true);
        var dance_grey = animCache.getAnimation("dance_2");
        dance_grey.setRestoreOriginalFrame(true);
        var dance_blue = animCache.getAnimation("dance_3");
        dance_blue.setRestoreOriginalFrame(true);

        var animN = cc.animate(normal);
        var animG = cc.animate(dance_grey);
        var animB = cc.animate(dance_blue);

        var seq = cc.sequence(animN, animG, animB);

        // create an sprite with frame name
        // texture-less sprites are not supported
        var grossini = new cc.Sprite("#grossini_dance_01.png");

        grossini.x = winSize.width / 2;

        grossini.y = winSize.height / 2;
        this.addChild(grossini);

        // run the animation
        grossini.runAction(seq);
        //----end54----
    },
    //
    // Automation
    //
    testDuration:6.5,
    ePixel1:{"0":51, "1":0, "2":51, "3":255},
    ePixel2:{"0":15, "1":15, "2":15, "3":255},
    ePixel3:{"0":0, "1":38, "2":0, "3":255},
    cPixel1:null,
    cPixel2:null,
    cPixel3:null,
    setupAutomation:function () {
        this.scheduleOnce(this.getPixel1, 0.4);
        this.scheduleOnce(this.getPixel2, 3.2);
        this.scheduleOnce(this.getPixel3, 6);
    },
    getPixel1:function () {
        this.cPixel1 = this.readPixels(winSize.width / 2, winSize.height / 2, 5, 5);
    },
    getPixel2:function () {
        this.cPixel2 = this.readPixels(winSize.width / 2, winSize.height / 2, 5, 5);
    },
    getPixel3:function () {
        this.cPixel3 = this.readPixels(winSize.width / 2, winSize.height / 2, 5, 5);
    },
    getExpectedResult:function () {
        var ret = {"pixel1":"yes", "pixel2":"yes", "pixel3":"yes"};
        return JSON.stringify(ret);
    },
    getCurrentResult:function () {
        var ret = {"pixel1":this.containsPixel(this.cPixel1, this.ePixel1) ? "yes" : "no", "pixel2":this.containsPixel(this.cPixel2, this.ePixel2) ? "yes" : "no", "pixel3":this.containsPixel(this.cPixel3, this.ePixel3, true, 5) ? "yes" : "no"};
        return JSON.stringify(ret);
    }
});

var SpriteBatchBug1217 = SpriteTestDemo.extend({

    _title:"SpriteBatch - Bug 1217",
    _subtitle:"Adding big family to spritebatch. You shall see 3 heads",

    ctor:function () {
        //----start53----ctor
        this._super();
        var bn = new cc.SpriteBatchNode(s_grossini_dance_atlas, 15);

        var s1 = new cc.Sprite(bn.texture, cc.rect(0, 0, 57, 57));
        var s2 = new cc.Sprite(bn.texture, cc.rect(0, 0, 57, 57));
        var s3 = new cc.Sprite(bn.texture, cc.rect(0, 0, 57, 57));

        s1.color = cc.color(255, 0, 0);
        s2.color = cc.color(0, 255, 0);
        s3.color = cc.color(0, 0, 255);

        s1.x = 20;

        s1.y = 200;
        s2.x = 100;
        s2.y = 0;
        s3.x = 100;
        s3.y = 0;

        bn.x = 0;

        bn.y = 0;

        //!!!!!
        s1.addChild(s2);
        s2.addChild(s3);
        bn.addChild(s1);

        this.addChild(bn);
        //----end53----
    },
    // Automation
    testDuration:2.1,
    pixel1:{"0":51, "1":0, "2":0, "3":255},
    pixel2:{"0":0, "1":0, "2":0, "3":255},
    pixel3:{"0":0, "1":0, "2":51, "3":255},
    getExpectedResult:function () {
        var ret = {"pixel1":"yes", "pixel2":"yes", "pixel3":"yes"};
        return JSON.stringify(ret);
    },
    getCurrentResult:function () {
        var ret1 = this.readPixels(20, 174, 3, 3);
        var ret2 = this.readPixels(90, 145, 3, 3);
        var ret3 = this.readPixels(163, 116, 3, 3);
        var ret = {"pixel1":this.containsPixel(ret1, this.pixel1, false) ? "yes" : "no",
            "pixel2":this.containsPixel(ret2, this.pixel2, false) ? "yes" : "no",
            "pixel3":this.containsPixel(ret3, this.pixel3, false) ? "yes" : "no"};
        return JSON.stringify(ret);
    }
});

var TextureColorCacheIssue = SpriteTestDemo.extend({

    _title:"Texture Color Cache Issue Test",
    _subtitle:"You should see two different sprites colored green and blue",

    ctor:function () {
        //----start55----ctor
        this._super();

        var spriteFrameCache = cc.spriteFrameCache;
        spriteFrameCache.addSpriteFrames(s_tcc_issue_1_plist, s_tcc_issue_1);
        spriteFrameCache.addSpriteFrames(s_tcc_issue_2_plist, s_tcc_issue_2);

        var grossini = new cc.Sprite('#tcc_grossini_dance_01.png');
        grossini.x = winSize.width / 3;
        grossini.y = winSize.height / 2;

        var sister = new cc.Sprite('#tcc_grossinis_sister1.png');
        sister.x = winSize.width / 3 * 2;
        sister.y = winSize.height / 2;

        this.addChild(grossini);
        this.addChild(sister);

        grossini.color = cc.color(1, 255, 1);
        sister.color = cc.color(1, 1, 255);
        //----end55----
    },
    onExit:function () {
        //----start55----onExit
        spriteFrameCache.removeSpriteFramesFromFile(s_tcc_issue_1_plist);
        spriteFrameCache.removeSpriteFramesFromFile(s_tcc_issue_2_plist);
        this._super();
        //----end55----
    },
    // Automation
    pixel1:{"0":0, "1":204, "2":0, "3":255},
    pixel2:{"0":0, "1":0, "2":153, "3":255},
    getExpectedResult:function () {
        var ret = {"pixel1":"yes", "pixel2":"yes"};
        return JSON.stringify(ret);
    },
    getCurrentResult:function () {
        var ret1 = this.readPixels(winSize.width / 3, winSize.height / 2 + 43, 5, 5);
        var ret2 = this.readPixels(winSize.width / 3 * 2, winSize.height / 2 - 6, 5, 5);
        var ret = {"pixel1":this.containsPixel(ret1, this.pixel1, true, 3) ? "yes" : "no",
            "pixel2":this.containsPixel(ret2, this.pixel2, true, 3) ? "yes" : "no"};
        return JSON.stringify(ret);
    }
});

var TextureColorCacheIssue2 = SpriteTestDemo.extend({

    _title:"Texture Color Cache Issue Test #2",
    _subtitle:"You should see two different sprites magenta and yellow",

    ctor:function () {
        //----start56----ctor
        this._super();

        var spriteFrameCache = cc.spriteFrameCache;
        spriteFrameCache.addSpriteFrames(s_tcc_issue_1_plist, s_tcc_issue_1);
        spriteFrameCache.addSpriteFrames(s_tcc_issue_2_plist, s_tcc_issue_2);

        var grossini = new cc.Sprite('#tcc_grossini_dance_01.png');
        grossini.x = winSize.width / 3;
        grossini.y = winSize.height / 2;

        var sister = new cc.Sprite('#tcc_grossinis_sister1.png');
        sister.x = winSize.width / 3 * 2;
        sister.y = winSize.height / 2;

        this.addChild(grossini);
        this.addChild(sister);

        grossini.color = cc.color(255, 255, 0);
        sister.color = cc.color(255, 0, 255);
        //----end56----
    },
    onExit:function () {
        //----start56----onExit
        spriteFrameCache.removeSpriteFramesFromFile(s_tcc_issue_1_plist);
        spriteFrameCache.removeSpriteFramesFromFile(s_tcc_issue_2_plist);
        this._super();
        //----end56----
    },
    // Automation
    pixel1:{"0":255, "1":204, "2":0, "3":255},
    pixel2:{"0":255, "1":0, "2":153, "3":255},
    getExpectedResult:function () {
        var ret = {"pixel1":"yes", "pixel2":"yes"};
        return JSON.stringify(ret);
    },
    getCurrentResult:function () {
        var ret1 = this.readPixels(winSize.width / 3, winSize.height / 2 + 43, 5, 5);
        var ret2 = this.readPixels(winSize.width / 3 * 2, winSize.height / 2 - 3, 5, 5);
        var ret = {"pixel1":this.containsPixel(ret1, this.pixel1, true, 5) ? "yes" : "no",
            "pixel2":this.containsPixel(ret2, this.pixel2, true, 5) ? "yes" : "no"};
        return JSON.stringify(ret);
    }
});

var TextureRotatedSpriteFrame = SpriteTestDemo.extend({

    _title:"Sub Sprite (rotated source)",
    _subtitle:"createWithSpriteFrameName(); sub sprite",

    ctor:function () {
        //----start57----ctor
        this._super();

        cc.spriteFrameCache.addSpriteFrames(s_s9s_blocks9_plist);

        var block = new cc.Sprite('#blocks9r.png');

        var x = winSize.width / 2;
        var y = 0 + (winSize.height / 2);

        block.setTextureRect(cc.rect(32, 32, 32, 32), true, cc.rect(32, 32, 32, 32));

        block.x = x;

        block.y = y;
        this.addChild(block);
        //----end57----
    },
    // Automation
    pixel1:{"0":255, "1":204, "2":153, "3":255},
    pixel2:{"0":51, "1":0, "2":51, "3":255},
    getExpectedResult:function () {
        var ret = {"pixel1":"yes", "pixel2":"yes"};
        return JSON.stringify(ret);
    },
    getCurrentResult:function () {
        var ret1 = this.readPixels(winSize.width / 2 - 14, winSize.height / 2 - 8, 5, 5);
        var ret2 = this.readPixels(winSize.width / 2 + 12, winSize.height / 2, 5, 5);
        var ret = {"pixel1":this.containsPixel(ret1, this.pixel1, true, 5) ? "yes" : "no",
            "pixel2":this.containsPixel(ret2, this.pixel2, true, 5) ? "yes" : "no"};
        return JSON.stringify(ret);
    }
});

var SpriteWithRepeatingTexture = SpriteTestDemo.extend({

    _title:"Sprite with Repeating texture",
    _subtitle:"aTexture.setTexParameters(cc.LINEAR, cc.LINEAR, cc.REPEAT, cc.REPEAT);",

    ctor:function () {
        //----start58----ctor
        this._super();
        var block = new cc.Sprite(s_pathBlock);

        var x = winSize.width / 2;
        var y = (winSize.height / 2);

        block.setTextureRect(cc.rect(0,0, 320,240));
        block.setPosition(x, y);
        block.getTexture().setTexParameters(cc.LINEAR, cc.LINEAR, cc.REPEAT, cc.REPEAT);
        this.addChild(block);
        //----end58----
    }
});

var SpriteBlendFuncTest = SpriteTestDemo.extend({
    //webgl only
    _title: "",          //Sprite BlendFunc test
    _subtitle: "",

    ctor: function(){
        //----start59----ctor
        this._super();

        var destFactors = [cc.ZERO, cc.ONE, cc.DST_COLOR, cc.ONE_MINUS_DST_COLOR, cc.DST_ALPHA, cc.ONE_MINUS_DST_ALPHA],
           srcFactors = [cc.ZERO, cc.ONE, cc.SRC_COLOR, cc.ONE_MINUS_SRC_COLOR, cc.SRC_ALPHA, cc.ONE_MINUS_SRC_ALPHA];
        var destTitles = ["ZERO", "ONE", "DST_COLOR", "ONE_MINUS_DST_COLOR", "DST_ALPHA", "ONE_MINUS_DST_ALPHA"],
            srcTitles = ["ZERO", "ONE", "SRC_COLOR", "ONE_MINUS_SRC_COLOR", "SRC_ALPHA", "ONE_MINUS_SRC_ALPHA"];

        var sourceImg = "Images/dot.png", destImg = "Images/wood.jpg";
        var sourceTexture = cc.textureCache.addImage(sourceImg);
        sourceTexture.handleLoadedTexture(true);
        var sourceSprite = new cc.Sprite(sourceImg);
        var destSprite = new cc.Sprite(destImg);
        sourceSprite.setScale(0.8);
        destSprite.setScale(0.8);
        sourceSprite.setPosition(60,400);
        destSprite.setPosition(120,400);
        this.addChild(sourceSprite);
        this.addChild(destSprite);

        if(cc._renderType === cc._RENDER_TYPE_CANVAS){
            var info = new cc.LabelTTF("support is not complete on canvas", "Arial", 18);
            info.x = 680;
            info.y = 250;
            info.setDimensions(cc.size(200, 200));
            this.addChild(info);
        }

        var i, j,  title, fontSize, titleLabel;
        for(i = 0; i < destTitles.length; i++){
            title = destTitles[i];
            fontSize = (title.length > 10) ? 14 : 18;
            titleLabel = new cc.LabelTTF(title, "Arial", fontSize);
            titleLabel.setAnchorPoint(0, 0.5);
            titleLabel.setPosition(0, 355 - 60 * i);
            this.addChild(titleLabel);
        }

        for(i = 0; i < srcTitles.length; i++){
            title = srcTitles[i];
            fontSize = (title.length > 10) ? 14 : 18;
            titleLabel = new cc.LabelTTF(title, "Arial", fontSize);
            titleLabel.setAnchorPoint(0, 0.5);
            titleLabel.setPosition(220 + i * 60, 390);
            titleLabel.setRotation(-20);
            this.addChild(titleLabel);
        }
        //j = 0;
        for(i = 0; i < srcFactors.length; i++){
            for(j = 0; j < destFactors.length; j++){
                sourceSprite = new cc.Sprite(sourceImg);
                //sourceSprite.setScale(0.8);
                sourceSprite.setPosition( 220 + i * 60, 355 - j * 60);
                sourceSprite.setBlendFunc(srcFactors[i], destFactors[j]);


                destSprite = new cc.Sprite(destImg);
                //destSprite.setScale(0.8);
                destSprite.setPosition( 220 + i * 60, 355 - j * 60);
//                destSprite.setBlendFunc(srcFactors[j], destFactors[i]);

                this.addChild(destSprite,1);
                this.addChild(sourceSprite,2);
            }
        }
        //----end59----
    }
});

var SpriteTestScene = TestScene.extend({
    runThisTest:function (num) {
        spriteTestIdx = (num || num == 0) ? (num - 1) : -1;
        var layer = nextSpriteTest();
        this.addChild(layer);

        director.runScene(this);
    }
});

//
// Flow control
//
var arrayOfSpriteTest = [
	Sprite1,
    SpriteBatchNode1,
    SpriteFrameTest,
    SpriteFrameAliasNameTest,
    SpriteAnchorPoint,
    SpriteBatchNodeAnchorPoint,
    SpriteOffsetAnchorRotation,
    SpriteBatchNodeOffsetAnchorRotation,
    SpriteOffsetAnchorScale,
    SpriteBatchNodeOffsetAnchorScale,
    SpriteAnimationSplit,
    SpriteColorOpacity,
    SpriteBatchNodeColorOpacity,
    SpriteZOrder,
    SpriteBatchNodeZOrder,
    SpriteBatchNodeReorderIssue744,
    SpriteBatchNodeReorderIssue766,
    SpriteBatchNodeReorderIssue767,
    Sprite6,
    SpriteFlip,
    SpriteBatchNodeFlip,
    SpriteAliased,
    SpriteBatchNodeAliased,
    SpriteNewTexture,
    SpriteBatchNodeNewTexture,
    SpriteHybrid,
    SpriteBatchNodeChildren,
    SpriteBatchNodeChildrenZ,
    SpriteChildrenVisibility,
    SpriteChildrenVisibilityIssue665,
    SpriteChildrenAnchorPoint,
    SpriteBatchNodeChildrenAnchorPoint,
    SpriteBatchNodeChildrenScale,
    SpriteChildrenChildren,
    SpriteBatchNodeChildrenChildren,
	SpriteSubclass,
    AnimationCacheTest,
    SpriteOffsetAnchorSkew,
    SpriteBatchNodeOffsetAnchorSkew,
    SpriteOffsetAnchorSkewScale,
    SpriteBatchNodeOffsetAnchorSkewScale,
    SpriteOffsetAnchorFlip,
    SpriteBatchNodeOffsetAnchorFlip,
    SpriteBatchNodeReorderOneChild,
    NodeSort,
    SpriteSkewNegativeScaleChildren,
    SpriteBatchNodeSkewNegativeScaleChildren,
    SpriteDoubleResolution,
    SpriteBatchBug1217,
    AnimationCacheFile,
    TextureColorCacheIssue,
    TextureColorCacheIssue2,
    TextureRotatedSpriteFrame,
    SpriteWithRepeatingTexture,
    SpriteBlendFuncTest
];

var nextSpriteTest = function () {
    spriteTestIdx++;
    spriteTestIdx = spriteTestIdx % arrayOfSpriteTest.length;

    if(window.sideIndexBar){
        spriteTestIdx = window.sideIndexBar.changeTest(spriteTestIdx, 36);
    }

    return new arrayOfSpriteTest[spriteTestIdx ]();
};
var previousSpriteTest = function () {
    spriteTestIdx--;
    if (spriteTestIdx < 0)
        spriteTestIdx += arrayOfSpriteTest.length;

    if(window.sideIndexBar){
        spriteTestIdx = window.sideIndexBar.changeTest(spriteTestIdx, 36);
    }

    return new arrayOfSpriteTest[spriteTestIdx ]();
};
var restartSpriteTest = function () {
    return new arrayOfSpriteTest[spriteTestIdx ]();
};

