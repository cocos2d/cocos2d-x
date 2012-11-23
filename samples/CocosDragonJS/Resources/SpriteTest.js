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

var sceneIdx = -1;

var spriteFrameCache = cc.SpriteFrameCache.getInstance();

//------------------------------------------------------------------
//
// SpriteTestDemo
//
//------------------------------------------------------------------
// var SpriteTestDemo = cc.LayerGradient.extend({
var SpriteTestDemo = cc.Layer.extend({
    _title:"",
    _subtitle:"",

    ctor:function() {
        cc.associateWithNative( this, cc.Layer );
        this.init();
    },
    init:function() {
        // this._super(cc.c4b(0, 0, 0, 255), cc.c4b(0, 128, 255, 255));
        this._super();
    },
    onEnter:function () {
        this._super();

        var label = cc.LabelTTF.create(this._title, "Arial", 28);
        this.addChild(label, 1);
        label.setPosition(cc.p(winSize.width / 2, winSize.height - 50));

        if (this._subtitle !== "") {
            var l = cc.LabelTTF.create(this._subtitle, "Thonburi", 16);
            this.addChild(l, 1);
            l.setPosition(cc.p(winSize.width / 2, winSize.height - 80));
        }

        var item1 = cc.MenuItemImage.create(s_pathB1, s_pathB2, this, this.onBackCallback);
        var item2 = cc.MenuItemImage.create(s_pathR1, s_pathR2, this, this.onRestartCallback);
        var item3 = cc.MenuItemImage.create(s_pathF1, s_pathF2, this, this.onNextCallback);

        var menu = cc.Menu.create(item1, item2, item3);

        menu.setPosition(cc.p(0,0));
        var cs = item2.getContentSize();
        item1.setPosition( cc.p(winSize.width/2 - cs.width*2, cs.height/2) );
        item2.setPosition( cc.p(winSize.width/2, cs.height/2) );
        item3.setPosition( cc.p(winSize.width/2 + cs.width*2, cs.height/2) );

        this.addChild(menu, 1);
    },

    onExit:function () {
        this._super();
    },

    onRestartCallback:function (sender) {
        var s = new SpriteTestScene();
        s.addChild(restartSpriteTest());
        director.replaceScene(s);
    },
    onNextCallback:function (sender) {
        var s = new SpriteTestScene();
        s.addChild(nextSpriteTest());
        director.replaceScene(s);
    },
    onBackCallback:function (sender) {
        var s = new SpriteTestScene();
        s.addChild(previousSpriteTest());
        director.replaceScene(s);
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

    init:function () {
        this._super();

        this.addNewSpriteWithCoords(cc.p(winSize.width / 2, winSize.height / 2));

        var t = cc.config.deviceType;
        if( t == 'browser' )  {
            this.setTouchEnabled(true);
            // this.setKeyboardEnabled(true);
        } else if( t == 'desktop' ) {
            this.setMouseEnabled(true);
        } else if( t == 'mobile' ) {
            this.setTouchEnabled(true);
        }
    },

    addNewSpriteWithCoords:function (p) {
        var idx = 0 | (Math.random() * 14);
        var x = (idx % 5) * 85;
        var y = (0 | (idx / 5)) * 121;
        var sprite = cc.Sprite.create(s_grossini_dance_atlas, cc.rect(x, y, 85, 121));
        this.addChild(sprite);
        sprite.setPosition(cc.p(p.x, p.y));

        var action;
        var random = Math.random();
        if (random < 0.20) {
            action = cc.ScaleBy.create(3, 2);
        } else if (random < 0.40) {
            action = cc.RotateBy.create(3, 360);
        } else if (random < 0.60) {
            action = cc.Blink.create(1, 3);
        } else if (random < 0.8) {
            action = cc.TintBy.create(2, 0, -255, -255);
        } else {
            action = cc.FadeOut.create(2);
        }

        var action_back = action.reverse();
        var seq = cc.Sequence.create(action, action_back);

        sprite.runAction(cc.RepeatForever.create(seq));
    },
    onTouchesEnded:function (touches, event) {
        for (var it = 0; it < touches.length; it++) {
            var touch = touches[it];

            if (!touch)
                break;

            var location = touch.getLocation();
            //location = director.convertToGL(location);
            this.addNewSpriteWithCoords(location);
        }
    },

    onMouseDown : function( event ) {
        var location = event.getLocation();
        this.addNewSpriteWithCoords(location);
        return true;
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

        var batchNode = cc.SpriteBatchNode.create(s_grossini_dance_atlas, 50);
        this.addChild(batchNode, 0, TAG_SPRITE_BATCH_NODE);
        this.addNewSpriteWithCoords(cc.p(winSize.width / 2, winSize.height / 2));
    },

    addNewSpriteWithCoords:function (p) {
        var batchNode = this.getChildByTag(TAG_SPRITE_BATCH_NODE);

        var idx = 0 | (Math.random() * 14);
        var x = (idx % 5) * 85;
        var y = (0 | (idx / 5)) * 121;

        var sprite = cc.Sprite.createWithTexture(batchNode.getTexture(), cc.rect(x, y, 85, 121));
        batchNode.addChild(sprite);

        sprite.setPosition(cc.p(p.x, p.y));

        var action;
        var random = Math.random();

        if (random < 0.20)
            action = cc.ScaleBy.create(3, 2);
        else if (random < 0.40)
            action = cc.RotateBy.create(3, 360);
        else if (random < 0.60)
            action = cc.Blink.create(1, 3);
        else if (random < 0.8)
            action = cc.TintBy.create(2, 0, -255, -255);
        else
            action = cc.FadeOut.create(2);

        var action_back = action.reverse();
        var seq = cc.Sequence.create(action, action_back);

        sprite.runAction(cc.RepeatForever.create(seq));
    },
    onTouchesEnded:function (touches, event) {
        for (var it = 0; it < touches.length; it++) {
            var touch = touches[it];

            if (!touch)
                break;

            var location = touch.getLocation();
            //location = director.convertToGL(location);
            this.addNewSpriteWithCoords(location);
        }
    },
    onMouseDown : function( event ) {
        var location = event.getLocation();
        this.addNewSpriteWithCoords(location);
        return true;
    }
});

//------------------------------------------------------------------
//
// SpriteColorOpacity
//
//------------------------------------------------------------------
var SpriteColorOpacity = SpriteTestDemo.extend({

    _title:"Sprite: Color & Opacity",

    init:function () {
        this._super();
        var sprite1 = cc.Sprite.create(s_grossini_dance_atlas, cc.rect(0, 121, 85, 121));
        var sprite2 = cc.Sprite.create(s_grossini_dance_atlas, cc.rect(85, 121, 85, 121));
        var sprite3 = cc.Sprite.create(s_grossini_dance_atlas, cc.rect(85 * 2, 121, 85, 121));
        var sprite4 = cc.Sprite.create(s_grossini_dance_atlas, cc.rect(85 * 3, 121, 85, 121));

        var sprite5 = cc.Sprite.create(s_grossini_dance_atlas, cc.rect(0, 121, 85, 121));
        var sprite6 = cc.Sprite.create(s_grossini_dance_atlas, cc.rect(85, 121, 85, 121));
        var sprite7 = cc.Sprite.create(s_grossini_dance_atlas, cc.rect(85 * 2, 121, 85, 121));
        var sprite8 = cc.Sprite.create(s_grossini_dance_atlas, cc.rect(85 * 3, 121, 85, 121));

        sprite1.setPosition(cc.p((winSize.width / 5), (winSize.height / 3)));
        sprite2.setPosition(cc.p((winSize.width / 5) * 2, (winSize.height / 3)));
        sprite3.setPosition(cc.p((winSize.width / 5) * 3, (winSize.height / 3)));
        sprite4.setPosition(cc.p((winSize.width / 5) * 4, (winSize.height / 3)));
        sprite5.setPosition(cc.p((winSize.width / 5), (winSize.height / 3) * 2));
        sprite6.setPosition(cc.p((winSize.width / 5) * 2, (winSize.height / 3) * 2));
        sprite7.setPosition(cc.p((winSize.width / 5) * 3, (winSize.height / 3) * 2));
        sprite8.setPosition(cc.p((winSize.width / 5) * 4, (winSize.height / 3) * 2));

        var action = cc.FadeIn.create(2);
        var action_back = action.reverse();
        var fade = cc.RepeatForever.create(cc.Sequence.create(action, action_back));

        var tintRed = cc.TintBy.create(2, 0, -255, -255);
        var tintRedBack = tintRed.reverse();
        var red = cc.RepeatForever.create(cc.Sequence.create(tintRed, tintRedBack));

        var tintGreen = cc.TintBy.create(2, -255, 0, -255);
        var tintGreenBack = tintGreen.reverse();
        var green = cc.RepeatForever.create(cc.Sequence.create(tintGreen, tintGreenBack));

        var tintBlue = cc.TintBy.create(2, -255, -255, 0);
        var tintBlueBack = tintBlue.reverse();
        var blue = cc.RepeatForever.create(cc.Sequence.create(tintBlue, tintBlueBack));

        sprite5.runAction(red);
        sprite6.runAction(green);
        sprite7.runAction(blue);
        sprite8.runAction(fade);

        // late add: test dirtyColor and dirtyPosition
        this.addChild(sprite1, 0, TAG_SPRITE1);
        this.addChild(sprite2, 0, TAG_SPRITE2);
        this.addChild(sprite3, 0, TAG_SPRITE3);
        this.addChild(sprite4, 0, TAG_SPRITE4);
        this.addChild(sprite5, 0, TAG_SPRITE5);
        this.addChild(sprite6, 0, TAG_SPRITE6);
        this.addChild(sprite7, 0, TAG_SPRITE7);
        this.addChild(sprite8, 0, TAG_SPRITE8);

        this.schedule(this.removeAndAddSprite, 2);
    },
    // this function test if remove and add works as expected:
//   color array and vertex array should be reindexed
    removeAndAddSprite:function (dt) {
        var sprite = this.getChildByTag(TAG_SPRITE5);

        this.removeChild(sprite, false);
        this.addChild(sprite, 0, TAG_SPRITE5);
    }
});

//------------------------------------------------------------------
//
// SpriteBatchNodeColorOpacity
//
//------------------------------------------------------------------
var SpriteBatchNodeColorOpacity = SpriteTestDemo.extend({

    _title:"SpriteBatchNode: Color & Opacity",

    init:function () {
        this._super();
        // small capacity. Testing resizing.
        // Don't use capacity=1 in your real game. It is expensive to resize the capacity
        var batch = cc.SpriteBatchNode.create(s_grossini_dance_atlas, 1);
        this.addChild(batch, 0, TAG_SPRITE_BATCH_NODE);

        var sprite1 = cc.Sprite.createWithTexture(batch.getTexture(), cc.rect(0, 121, 85, 121));
        var sprite2 = cc.Sprite.createWithTexture(batch.getTexture(), cc.rect(85, 121, 85, 121));
        var sprite3 = cc.Sprite.createWithTexture(batch.getTexture(), cc.rect(85 * 2, 121, 85, 121));
        var sprite4 = cc.Sprite.createWithTexture(batch.getTexture(), cc.rect(85 * 3, 121, 85, 121));

        var sprite5 = cc.Sprite.createWithTexture(batch.getTexture(), cc.rect(0, 121, 85, 121));
        var sprite6 = cc.Sprite.createWithTexture(batch.getTexture(), cc.rect(85, 121, 85, 121));
        var sprite7 = cc.Sprite.createWithTexture(batch.getTexture(), cc.rect(85 * 2, 121, 85, 121));
        var sprite8 = cc.Sprite.createWithTexture(batch.getTexture(), cc.rect(85 * 3, 121, 85, 121));


        sprite1.setPosition(cc.p((winSize.width / 5) * 1, (winSize.height / 3) * 1));
        sprite2.setPosition(cc.p((winSize.width / 5) * 2, (winSize.height / 3) * 1));
        sprite3.setPosition(cc.p((winSize.width / 5) * 3, (winSize.height / 3) * 1));
        sprite4.setPosition(cc.p((winSize.width / 5) * 4, (winSize.height / 3) * 1));
        sprite5.setPosition(cc.p((winSize.width / 5) * 1, (winSize.height / 3) * 2));
        sprite6.setPosition(cc.p((winSize.width / 5) * 2, (winSize.height / 3) * 2));
        sprite7.setPosition(cc.p((winSize.width / 5) * 3, (winSize.height / 3) * 2));
        sprite8.setPosition(cc.p((winSize.width / 5) * 4, (winSize.height / 3) * 2));

        var action = cc.FadeIn.create(2);
        var action_back = action.reverse();
        var fade = cc.RepeatForever.create(cc.Sequence.create(action, action_back));

        var tintRed = cc.TintBy.create(2, 0, -255, -255);
        var red = cc.RepeatForever.create(cc.Sequence.create(tintRed, tintRed.reverse()));

        var tintGreen = cc.TintBy.create(2, -255, 0, -255);
        var tintGreenBack = tintGreen.reverse();
        var green = cc.RepeatForever.create(cc.Sequence.create(tintGreen, tintGreenBack));

        var tintBlue = cc.TintBy.create(2, -255, -255, 0);
        var tintBlueBack = tintBlue.reverse();
        var blue = cc.RepeatForever.create(cc.Sequence.create(tintBlue, tintBlueBack));

        sprite5.runAction(red);
        sprite6.runAction(green);
        sprite7.runAction(blue);
        sprite8.runAction(fade);

        // late add: test dirtyColor and dirtyPosition
        batch.addChild(sprite1, 0, TAG_SPRITE1);
        batch.addChild(sprite2, 0, TAG_SPRITE2);
        batch.addChild(sprite3, 0, TAG_SPRITE3);
        batch.addChild(sprite4, 0, TAG_SPRITE4);
        batch.addChild(sprite5, 0, TAG_SPRITE5);
        batch.addChild(sprite6, 0, TAG_SPRITE6);
        batch.addChild(sprite7, 0, TAG_SPRITE7);
        batch.addChild(sprite8, 0, TAG_SPRITE8);

        this.schedule(this.removeAndAddSprite, 2);
    },
    // this function test if remove and add works as expected:
    //   color array and vertex array should be reindexed
    removeAndAddSprite:function (dt) {
        var batch = this.getChildByTag(TAG_SPRITE_BATCH_NODE);
        var sprite = batch.getChildByTag(TAG_SPRITE5);

        batch.removeChild(sprite, false);
        batch.addChild(sprite, 0, TAG_SPRITE5);
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
    init:function () {
        this._super();
        this._dir = 1;

        var sprite;
        var step = winSize.width / 11;
        for (var i = 0; i < 5; i++) {
            sprite = cc.Sprite.create(s_grossini_dance_atlas, cc.rect(85 * 0, 121 * 1, 85, 121));
            sprite.setPosition(cc.p((i + 1) * step, winSize.height / 2));
            this.addChild(sprite, i);
        }

        for (i = 5; i < 10; i++) {
            sprite = cc.Sprite.create(s_grossini_dance_atlas, cc.rect(85 * 1, 121 * 0, 85, 121));
            sprite.setPosition(cc.p((i + 1) * step, winSize.height / 2));
            this.addChild(sprite, 14 - i);
        }

        sprite = cc.Sprite.create(s_grossini_dance_atlas, cc.rect(85 * 3, 121 * 0, 85, 121));
        this.addChild(sprite, -1, TAG_SPRITE1);
        sprite.setPosition(cc.p(winSize.width / 2, winSize.height / 2 - 20));
        sprite.setScaleX(10);
        sprite.setColor( cc.c3b(255,0,0) );
        // sprite.setColor(cc.RED);

        this.schedule(this.reorderSprite, 1);
    },
    reorderSprite:function (dt) {
        var sprite = this.getChildByTag(TAG_SPRITE1);

        var z = sprite.getZOrder();

        if (z < -1)
            this._dir = 1;
        if (z > 10)
            this._dir = -1;

        z += this._dir * 3;

        this.reorderChild(sprite, z);
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
    init:function () {
        this._super();
        this._dir = 1;

        // small capacity. Testing resizing.
        // Don't use capacity=1 in your real game. It is expensive to resize the capacity
        var batch = cc.SpriteBatchNode.create(s_grossini_dance_atlas, 1);
        this.addChild(batch, 0, TAG_SPRITE_BATCH_NODE);

        var sprite;
        var step = winSize.width / 11;
        for (var i = 0; i < 5; i++) {
            sprite = cc.Sprite.createWithTexture(batch.getTexture(), cc.rect(85 * 0, 121 * 1, 85, 121));
            sprite.setPosition(cc.p((i + 1) * step, winSize.height / 2));
            batch.addChild(sprite, i);
        }

        for (i = 5; i < 10; i++) {
            sprite = cc.Sprite.createWithTexture(batch.getTexture(), cc.rect(85 * 1, 121 * 0, 85, 121));
            sprite.setPosition(cc.p((i + 1) * step, winSize.height / 2));
            batch.addChild(sprite, 14 - i);
        }

        sprite = cc.Sprite.createWithTexture(batch.getTexture(), cc.rect(85 * 3, 121 * 0, 85, 121));
        batch.addChild(sprite, -1, TAG_SPRITE1);
        sprite.setPosition(cc.p(winSize.width / 2, winSize.height / 2 - 20));
        sprite.setScaleX(10);
        // sprite.setColor(cc.RED);
        sprite.setColor( cc.c3b(255,0,0) );
        this.schedule(this.reorderSprite, 1);
    },
    reorderSprite:function (dt) {
        var batch = this.getChildByTag(TAG_SPRITE_BATCH_NODE);
        var sprite = batch.getChildByTag(TAG_SPRITE1);

        var z = sprite.getZOrder();

        if (z < -1)
            this._dir = 1;
        if (z > 10)
            this._dir = -1;

        z += this._dir * 3;

        batch.reorderChild(sprite, z);
    }
});

//------------------------------------------------------------------
//
// SpriteBatchNodeReorder
//
//------------------------------------------------------------------
var SpriteBatchNodeReorder = SpriteTestDemo.extend({

    _title:"SpriteBatchNode: reorder #1",
    _subtitle:"Should not crash",

    init:function () {
        this._super();
        var a = [];
        var asmtest = cc.SpriteBatchNode.create(s_ghosts);

        for (var i = 0; i < 10; i++) {
            var s1 = cc.Sprite.createWithTexture(asmtest.getTexture(), cc.rect(0, 0, 50, 50));
            a.push(s1);
            asmtest.addChild(s1, 10);
        }

        for (i = 0; i < 10; i++) {
            if (i != 5)
                asmtest.reorderChild(a[i], 9);
        }

        var prev = -1, currentIndex;
        var children = asmtest.getChildren();
        var child;
        for (i = 0; i < children.length; i++) {
            child = children[i];
            if (!child)
                break;

            //TODO need fixed
            currentIndex = child.getAtlasIndex();
            //cc.Assert(prev == currentIndex - 1, "Child order failed");
            ////----UXLog("children %x - atlasIndex:%d", child, currentIndex);
            prev = currentIndex;
        }

        prev = -1;
        var sChildren = asmtest.getDescendants();
        for (i = 0; i < sChildren.length; i++) {
            child = sChildren[i];
            if (!child)
                break;

            currentIndex = child.getAtlasIndex();
            //cc.Assert(prev == currentIndex - 1, "Child order failed");
            ////----UXLog("descendant %x - atlasIndex:%d", child, currentIndex);
            prev = currentIndex;
        }
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

    init:function () {
        this._super();

        // Testing issue #744
        // http://code.google.com/p/cocos2d-iphone/issues/detail?id=744
        var batch = cc.SpriteBatchNode.create(s_grossini_dance_atlas, 15);
        this.addChild(batch, 0, TAG_SPRITE_BATCH_NODE);

        var sprite = cc.Sprite.createWithTexture(batch.getTexture(), cc.rect(0, 0, 85, 121));
        sprite.setPosition(cc.p(winSize.width / 2, winSize.height / 2));
        batch.addChild(sprite, 3);
        batch.reorderChild(sprite, 1);
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

    init:function () {
        this._super();
        this._batchNode = cc.SpriteBatchNode.create(s_piece, 15);
        this.addChild(this._batchNode, 1, 0);

        this._sprite1 = this.makeSpriteZ(2);
        this._sprite1.setPosition(cc.p(200, 160));

        this._sprite2 = this.makeSpriteZ(3);
        this._sprite2.setPosition(cc.p(264, 160));

        this._sprite3 = this.makeSpriteZ(4);
        this._sprite3.setPosition(cc.p(328, 160));

        this.schedule(this.reorderSprite, 2);
    },
    reorderSprite:function (dt) {
        this.unschedule(this.reorderSprite);

        this._batchNode.reorderChild(this._sprite1, 4);
    },
    makeSpriteZ:function (aZ) {
        var sprite = cc.Sprite.createWithTexture(this._batchNode.getTexture(), cc.rect(128, 0, 64, 64));
        this._batchNode.addChild(sprite, aZ + 1, 0);

        //children
        var spriteShadow = cc.Sprite.createWithTexture(this._batchNode.getTexture(), cc.rect(0, 0, 64, 64));
        spriteShadow.setOpacity(128);
        sprite.addChild(spriteShadow, aZ, 3);

        var spriteTop = cc.Sprite.createWithTexture(this._batchNode.getTexture(), cc.rect(64, 0, 64, 64));
        sprite.addChild(spriteTop, aZ + 2, 3);

        return sprite;
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

    init:function () {
        this._super();

        spriteFrameCache.addSpriteFrames(s_ghostsPlist, s_ghosts);
        //
        // SpriteBatchNode: 3 levels of children
        //
        var aParent = cc.SpriteBatchNode.create(s_ghosts);
        this.addChild(aParent, 0, TAG_SPRITE1);

        // parent
        var l1 = cc.Sprite.createWithSpriteFrame(spriteFrameCache.getSpriteFrame("father.gif"));
        l1.setPosition(cc.p(winSize.width / 2, winSize.height / 2));
        aParent.addChild(l1, 0, TAG_SPRITE2);
        var l1Size = l1.getContentSize();

        // child left
        var l2a = cc.Sprite.createWithSpriteFrame(spriteFrameCache.getSpriteFrame("sister1.gif"));
        l2a.setPosition(cc.p(-25 + l1Size.width / 2, 0 + l1Size.height / 2));
        l1.addChild(l2a, -1, TAG_SPRITE_LEFT);
        var l2aSize = l2a.getContentSize();


        // child right
        var l2b = cc.Sprite.createWithSpriteFrame(spriteFrameCache.getSpriteFrame("sister2.gif"));
        l2b.setPosition(cc.p(+25 + l1Size.width / 2, 0 + l1Size.height / 2));
        l1.addChild(l2b, 1, TAG_SPRITE_RIGHT);
        var l2bSize = l2a.getContentSize();


        // child left bottom
        var l3a1 = cc.Sprite.createWithSpriteFrame(spriteFrameCache.getSpriteFrame("child1.gif"));
        l3a1.setScale(0.65);
        l3a1.setPosition(cc.p(0 + l2aSize.width / 2, -50 + l2aSize.height / 2));
        l2a.addChild(l3a1, -1);

        // child left top
        var l3a2 = cc.Sprite.createWithSpriteFrame(spriteFrameCache.getSpriteFrame("child1.gif"));
        l3a2.setScale(0.65);
        l3a2.setPosition(cc.p(0 + l2aSize.width / 2, +50 + l2aSize.height / 2));
        l2a.addChild(l3a2, 1);

        // child right bottom
        var l3b1 = cc.Sprite.createWithSpriteFrame(spriteFrameCache.getSpriteFrame("child1.gif"));
        l3b1.setScale(0.65);
        l3b1.setPosition(cc.p(0 + l2bSize.width / 2, -50 + l2bSize.height / 2));
        l2b.addChild(l3b1, -1);

        // child right top
        var l3b2 = cc.Sprite.createWithSpriteFrame(spriteFrameCache.getSpriteFrame("child1.gif"));
        l3b2.setScale(0.65);
        l3b2.setPosition(cc.p(0 + l2bSize.width / 2, +50 + l2bSize.height / 2));
        l2b.addChild(l3b2, 1);

        this.schedule(this.reorderSprites, 1);
    },
    reorderSprites:function (dt) {
        var spritebatch = this.getChildByTag(TAG_SPRITE1);
        var father = spritebatch.getChildByTag(TAG_SPRITE2);
        var left = father.getChildByTag(TAG_SPRITE_LEFT);
        var right = father.getChildByTag(TAG_SPRITE_RIGHT);

        var newZLeft = 1;

        if (left.getZOrder() == 1)
            newZLeft = -1;

        father.reorderChild(left, newZLeft);
        father.reorderChild(right, -newZLeft);
    }
});

//------------------------------------------------------------------
//
// SpriteZVertex
//
//------------------------------------------------------------------
var SpriteZVertex = SpriteTestDemo.extend({
    _dir:0,
    _time:0,
    _title:"Sprite: openGL Z vertex",

    init:function () {
        //
        // This test tests z-order
        // If you are going to use it is better to use a 3D projection
        //
        // WARNING:
        // The developer is resposible for ordering it's sprites according to it's Z if the sprite has
        // transparent parts.
        //

        //
        // Configure shader to mimic glAlphaTest
        //
        //var alphaTestShader = cc.ShaderCache.getInstance().programForKey(kCCShader_PositionTextureColorAlphaTest);
        //var alphaValueLocation = glGetUniformLocation(alphaTestShader.getProgram(), kCCUniformAlphaTestValue);

        // set alpha test value
        // NOTE: alpha test shader is hard-coded to use the equivalent of a glAlphaFunc(GL_GREATER) comparison
        //if (this.getShaderProgram()){
        //    this.getShaderProgram().setUniformLocationWith1f(alphaValueLocation, 0.0);
        //}

        this._super();
        this._dir = 1;
        this._time = 0;

        var step = winSize.width / 12;

        var node = cc.Node.create();
        // camera uses the center of the image as the pivoting point
        node.setContentSize(cc.size(winSize.width, winSize.height));
        node.setAnchorPoint(cc.p(0.5, 0.5));
        node.setPosition(cc.p(winSize.width / 2, winSize.height / 2));

        this.addChild(node, 0);
        var sprite;
        for (var i = 0; i < 5; i++) {
            sprite = cc.Sprite.create(s_grossini_dance_atlas, cc.rect(0, 121, 85, 121));
            sprite.setPosition(cc.p((i + 1) * step, winSize.height / 2));
            sprite.setVertexZ(10 + i * 40);
            //sprite.setShaderProgram(alphaTestShader);
            node.addChild(sprite, 0);
        }

        for (i = 5; i < 11; i++) {
            sprite = cc.Sprite.create(s_grossini_dance_atlas, cc.rect(85, 0, 85, 121));
            sprite.setPosition(cc.p((i + 1) * step, winSize.height / 2));
            sprite.setVertexZ(10 + (10 - i) * 40);
            //sprite.setShaderProgram(alphaTestShader);
            node.addChild(sprite, 0);
        }

        node.runAction(cc.OrbitCamera.create(10, 1, 0, 0, 360, 0, 0));
    },
    onEnter:function () {
        this._super();
        director.setProjection(cc.DIRECTOR_PROJECTION_3D);
    },
    onExit:function () {
        director.setProjection(cc.DIRECTOR_PROJECTION_2D);
        this._super();
    }
});

//------------------------------------------------------------------
//
// SpriteBatchNodeZVertex
//
//------------------------------------------------------------------
var SpriteBatchNodeZVertex = SpriteTestDemo.extend({
    _dir:0,
    _time:0,
    _title:"SpriteBatchNode: openGL Z vertex",

    init:function () {
        //
        // This test tests z-order
        // If you are going to use it is better to use a 3D projection
        //
        // WARNING:
        // The developer is resposible for ordering it's sprites according to it's Z if the sprite has
        // transparent parts.
        //

        //
        // Configure shader to mimic glAlphaTest
        //
        //var alphaTestShader = cc.ShaderCache.getInstance().programForKey(kCCShader_PositionTextureColorAlphaTest);
        //var alphaValueLocation = glGetUniformLocation(alphaTestShader.getProgram(), kCCUniformAlphaTestValue);

        // set alpha test value
        // NOTE: alpha test shader is hard-coded to use the equivalent of a glAlphaFunc(GL_GREATER) comparison
        //if (this.getShaderProgram()){
        //    this.getShaderProgram().setUniformLocationWith1f(alphaValueLocation, 0.0);
        //}

        this._super();
        var step = winSize.width / 12;

        // small capacity. Testing resizing.
        // Don't use capacity=1 in your real game. It is expensive to resize the capacity
        var batch = cc.SpriteBatchNode.create(s_grossini_dance_atlas, 1);
        // camera uses the center of the image as the pivoting point
        batch.setContentSize(cc.size(winSize.width, winSize.height));
        batch.setAnchorPoint(cc.p(0.5, 0.5));
        batch.setPosition(cc.p(winSize.width / 2, winSize.height / 2));

        this.addChild(batch, 0, TAG_SPRITE_BATCH_NODE);
        var sprite;

        for (var i = 0; i < 5; i++) {
            sprite = cc.Sprite.createWithTexture(batch.getTexture(), cc.rect(0, 121, 85, 121));
            sprite.setPosition(cc.p((i + 1) * step, winSize.height / 2));
            sprite.setVertexZ(10 + i * 40);
            batch.addChild(sprite, 0);

        }

        for (i = 5; i < 11; i++) {
            sprite = cc.Sprite.createWithTexture(batch.getTexture(), cc.rect(85, 0, 85, 121));
            sprite.setPosition(cc.p((i + 1) * step, winSize.height / 2));
            sprite.setVertexZ(10 + (10 - i) * 40);
            batch.addChild(sprite, 0);
        }

        batch.runAction(cc.OrbitCamera.create(10, 1, 0, 0, 360, 0, 0));
    },
    onEnter:function () {
        this._super();
        director.setProjection(cc.DIRECTOR_PROJECTION_3D);
    },
    onExit:function () {
        director.setProjection(cc.DIRECTOR_PROJECTION_2D);
        this._super();
    }
});

//------------------------------------------------------------------
//
// SpriteAnchorPoint
//
//------------------------------------------------------------------
var SpriteAnchorPoint = SpriteTestDemo.extend({
    _title:"Sprite: anchor point",

    init:function () {
        this._super();

        for (var i = 0; i < 3; i++) {
            var rotate = cc.RotateBy.create(10, 360);
            var action = cc.RepeatForever.create(rotate);
            var sprite = cc.Sprite.create(s_grossini_dance_atlas, cc.rect(85 * i, 121, 85, 121));
            sprite.setPosition(cc.p(winSize.width / 4 * (i + 1), winSize.height / 2));

            var point = cc.Sprite.create(s_pathR1);
            point.setScale(0.25);
            point.setPosition(sprite.getPosition());
            this.addChild(point, 10);

            switch (i) {
                case 0:
                    sprite.setAnchorPoint(cc.p(0,0));
                    break;
                case 1:
                    sprite.setAnchorPoint(cc.p(0.5, 0.5));
                    break;
                case 2:
                    sprite.setAnchorPoint(cc.p(1, 1));
                    break;
            }

            point.setPosition(sprite.getPosition());

            //var copy = action.copy();
            sprite.runAction(action);
            this.addChild(sprite, i);
        }
    }
});

//------------------------------------------------------------------
//
// SpriteBatchNodeAnchorPoint
//
//------------------------------------------------------------------
var SpriteBatchNodeAnchorPoint = SpriteTestDemo.extend({
    _title:"SpriteBatchNode: anchor point",

    init:function () {
        this._super();
        // small capacity. Testing resizing.
        // Don't use capacity=1 in your real game. It is expensive to resize the capacity
        var batch = cc.SpriteBatchNode.create(s_grossini_dance_atlas, 1);
        this.addChild(batch, 0, TAG_SPRITE_BATCH_NODE);

        for (var i = 0; i < 3; i++) {
            var rotate = cc.RotateBy.create(10, 360);
            var action = cc.RepeatForever.create(rotate);
            var sprite = cc.Sprite.createWithTexture(batch.getTexture(), cc.rect(85 * i, 121, 85, 121));
            sprite.setPosition(cc.p(winSize.width / 4 * (i + 1), winSize.height / 2));

            var point = cc.Sprite.create(s_pathR1);
            point.setScale(0.25);
            point.setPosition(sprite.getPosition());
            this.addChild(point, 1);

            switch (i) {
                case 0:
                    sprite.setAnchorPoint(cc.p(0,0));
                    break;
                case 1:
                    sprite.setAnchorPoint(cc.p(0.5, 0.5));
                    break;
                case 2:
                    sprite.setAnchorPoint(cc.p(1, 1));
                    break;
            }

            point.setPosition(sprite.getPosition());
            sprite.runAction(action);
            batch.addChild(sprite, i);
        }
    }
});

//------------------------------------------------------------------
//
// Sprite6
//
//------------------------------------------------------------------
var Sprite6 = SpriteTestDemo.extend({
    _title:"SpriteBatchNode transformation",

    init:function () {
        this._super();
        // small capacity. Testing resizing
        // Don't use capacity=1 in your real game. It is expensive to resize the capacity
        var batch = cc.SpriteBatchNode.create(s_grossini_dance_atlas, 1);
        this.addChild(batch, 0, TAG_SPRITE_BATCH_NODE);
        batch.ignoreAnchorPointForPosition(true);

        batch.setAnchorPoint(cc.p(0.5, 0.5));
        batch.setContentSize(cc.size(winSize.width, winSize.height));

        // SpriteBatchNode actions
        var rotate1 = cc.RotateBy.create(5, 360);
        var rotate_back = rotate1.reverse();
        var rotate_seq = cc.Sequence.create(rotate1, rotate_back);
        var rotate_forever = cc.RepeatForever.create(rotate_seq);

        var scale = cc.ScaleBy.create(5, 1.5);
        var scale_back = scale.reverse();
        var scale_seq = cc.Sequence.create(scale, scale_back);
        var scale_forever = cc.RepeatForever.create(scale_seq);

        var step = winSize.width / 4;

        for (var i = 0; i < 3; i++) {
            var sprite = cc.Sprite.createWithTexture(batch.getTexture(), cc.rect(85 * i, 121, 85, 121));
            sprite.setPosition(cc.p((i + 1) * step, winSize.height / 2));

            var rotate = cc.RotateBy.create(5, 360);
            var action = cc.RepeatForever.create(rotate);
            sprite.runAction(action.copy());
            batch.addChild(sprite, i);
        }

        batch.runAction(scale_forever);
        batch.runAction(rotate_forever);
    }
});

//------------------------------------------------------------------
//
// SpriteFlip
//
//------------------------------------------------------------------
var SpriteFlip = SpriteTestDemo.extend({
    _title:"Sprite Flip X & Y",

    init:function () {
        this._super();
        var sprite1 = cc.Sprite.create(s_grossini_dance_atlas, cc.rect(85, 121, 85, 121));
        sprite1.setPosition(cc.p(winSize.width / 2 - 100, winSize.height / 2));
        this.addChild(sprite1, 0, TAG_SPRITE1);

        var sprite2 = cc.Sprite.create(s_grossini_dance_atlas, cc.rect(85, 121, 85, 121));
        sprite2.setPosition(cc.p(winSize.width / 2 + 100, winSize.height / 2));
        this.addChild(sprite2, 0, TAG_SPRITE2);

        this.schedule(this.onFlipSprites, 1);
    },
    onFlipSprites:function (dt) {
        var sprite1 = this.getChildByTag(TAG_SPRITE1);
        var sprite2 = this.getChildByTag(TAG_SPRITE2);

        sprite1.setFlipX(!sprite1.isFlippedX());
        sprite2.setFlipY(!sprite2.isFlippedY());
    }
});

//------------------------------------------------------------------
//
// SpriteBatchNodeFlip
//
//------------------------------------------------------------------
var SpriteBatchNodeFlip = SpriteTestDemo.extend({
    _title:"SpriteBatchNode Flip X & Y",

    init:function () {
        this._super();
        var batch = cc.SpriteBatchNode.create(s_grossini_dance_atlas, 10);
        this.addChild(batch, 0, TAG_SPRITE_BATCH_NODE);

        var sprite1 = cc.Sprite.createWithTexture(batch.getTexture(), cc.rect(85, 121, 85, 121));
        sprite1.setPosition(cc.p(winSize.width / 2 - 100, winSize.height / 2));
        batch.addChild(sprite1, 0, TAG_SPRITE1);

        var sprite2 = cc.Sprite.createWithTexture(batch.getTexture(), cc.rect(85, 121, 85, 121));
        sprite2.setPosition(cc.p(winSize.width / 2 + 100, winSize.height / 2));
        batch.addChild(sprite2, 0, TAG_SPRITE2);

        this.schedule(this.onFlipSprites, 1);
    },
    onFlipSprites:function (dt) {
        var batch = this.getChildByTag(TAG_SPRITE_BATCH_NODE);
        var sprite1 = batch.getChildByTag(TAG_SPRITE1);
        var sprite2 = batch.getChildByTag(TAG_SPRITE2);

        sprite1.setFlipX(!sprite1.isFlippedX());
        sprite2.setFlipY(!sprite2.isFlippedY());
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

    init:function () {
        this._super();
        var sprite1 = cc.Sprite.create(s_grossini_dance_atlas, cc.rect(85, 121, 85, 121));
        sprite1.setPosition(cc.p(winSize.width / 2 - 100, winSize.height / 2));
        this.addChild(sprite1, 0, TAG_SPRITE1);

        var sprite2 = cc.Sprite.create(s_grossini_dance_atlas, cc.rect(85, 121, 85, 121));
        sprite2.setPosition(cc.p(winSize.width / 2 + 100, winSize.height / 2));
        this.addChild(sprite2, 0, TAG_SPRITE2);

        var scale = cc.ScaleBy.create(2, 5);
        var scale_back = scale.reverse();
        var seq = cc.Sequence.create(scale, scale_back);
        var repeat = cc.RepeatForever.create(seq);

        var scale2 = cc.ScaleBy.create(2, 5);
        var scale_back2 = scale2.reverse();
        var seq2 = cc.Sequence.create(scale2, scale_back2);
        var repeat2 = cc.RepeatForever.create(seq2);

        sprite1.runAction(repeat);
        sprite2.runAction(repeat2);
    },
    onEnter:function () {
        this._super();
        //
        // IMPORTANT:
        // This change will affect every sprite that uses the same texture
        // So sprite1 and sprite2 will be affected by this change
        //
        if( cc.config.deviceType == 'browser' )  {
            var label = cc.LabelTTF.create("Not supported on HTML5-canvas", "Times New Roman", 30);
            this.addChild( label );
            label.setPosition( cc.p( winSize.width/2, winSize.height/2) );
        } else {
            var sprite = this.getChildByTag(TAG_SPRITE1);
            sprite.getTexture().setAliasTexParameters();
        }

    },
    onExit:function () {
        if( cc.config.deviceType == 'browser' )  {
        } else {
            var sprite = this.getChildByTag(TAG_SPRITE1);
            sprite.getTexture().setAntiAliasTexParameters();
        }
        this._super();
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

    init:function () {
        this._super();
        var batch = cc.SpriteBatchNode.create(s_grossini_dance_atlas, 10);
        this.addChild(batch, 0, TAG_SPRITE_BATCH_NODE);

        var sprite1 = cc.Sprite.createWithTexture(batch.getTexture(), cc.rect(85, 121, 85, 121));
        sprite1.setPosition(cc.p(winSize.width / 2 - 100, winSize.height / 2));
        batch.addChild(sprite1, 0, TAG_SPRITE1);

        var sprite2 = cc.Sprite.createWithTexture(batch.getTexture(), cc.rect(85, 121, 85, 121));
        sprite2.setPosition(cc.p(winSize.width / 2 + 100, winSize.height / 2));
        batch.addChild(sprite2, 0, TAG_SPRITE2);

        var scale = cc.ScaleBy.create(2, 5);
        var scale_back = scale.reverse();
        var seq = cc.Sequence.create(scale, scale_back);
        var repeat = cc.RepeatForever.create(seq);

        var scale2 = cc.ScaleBy.create(2, 5);
        var scale_back2 = scale2.reverse();
        var seq2 = cc.Sequence.create(scale2, scale_back2);
        var repeat2 = cc.RepeatForever.create(seq2);

        sprite1.runAction(repeat);
        sprite2.runAction(repeat2);
    },
    onEnter:function () {
        this._super();
        //
        // IMPORTANT:
        // This change will affect every sprite that uses the same texture
        // So sprite1 and sprite2 will be affected by this change
        //
        if( cc.config.deviceType == 'browser' )  {
            var label = cc.LabelTTF.create("Not supported on HTML5-canvas", "Times New Roman", 30);
            this.addChild( label );
            label.setPosition( cc.p( winSize.width/2, winSize.height/2) );
        } else {
            var sprite = this.getChildByTag(TAG_SPRITE_BATCH_NODE);
            sprite.getTexture().setAliasTexParameters();
        }

    },
    onExit:function () {
        if( cc.config.deviceType == 'browser' )  {
        } else {
            var sprite = this.getChildByTag(TAG_SPRITE_BATCH_NODE);
            sprite.getTexture().setAntiAliasTexParameters();
        }
        this._super();
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

        var node = cc.Node.create();
        this.addChild(node, 0, TAG_SPRITE_BATCH_NODE);

        this._texture1 = cc.TextureCache.getInstance().addImage(s_grossini_dance_atlas);
        this._texture2 = cc.TextureCache.getInstance().addImage(s_grossini_dance_atlas_mono);

        this._usingTexture1 = true;

        for (var i = 0; i < 30; i++) {
            this.addNewSprite();
        }

    },
    addNewSprite:function () {
        var p = cc.p(Math.random() * winSize.width, Math.random() * winSize.height);

        var idx = 0 | (Math.random() * 14);
        var x = (idx % 5) * 85;
        var y = (0 | (idx / 5)) * 121;


        var node = this.getChildByTag(TAG_SPRITE_BATCH_NODE);
        var sprite = cc.Sprite.createWithTexture(this._texture1, cc.rect(x, y, 85, 121));
        node.addChild(sprite);

        sprite.setPosition(cc.p(p.x, p.y));

        var action;
        var random = Math.random();

        if (random < 0.20)
            action = cc.ScaleBy.create(3, 2);
        else if (random < 0.40)
            action = cc.RotateBy.create(3, 360);
        else if (random < 0.60)
            action = cc.Blink.create(1, 3);
        // else if (random < 0.8)
        //     action = cc.TintBy.create(2, 0, -255, -255);
        else
            action = cc.FadeOut.create(2);

        var action_back = action.reverse();
        var seq = cc.Sequence.create(action, action_back);

        sprite.runAction(cc.RepeatForever.create(seq));
    },

    onChangeTexture:function() {
        var node = this.getChildByTag(TAG_SPRITE_BATCH_NODE);

        var children = node.getChildren();
        var sprite;
        var i;

        if (this._usingTexture1) {                         //-. win32 : Let's it make just simple sentence
            for (i = 0; i < children.length; i++) {
                sprite = children[i];
                if (!sprite)
                    break;
                sprite.setTexture(this._texture2);
            }
            this._usingTexture1 = false;
        } else {
            for (i = 0; i < children.length; i++) {
                sprite = children[i];
                if (!sprite)
                    break;
                sprite.setTexture(this._texture1);
            }
            this._usingTexture1 = true;
        }
    },
    onTouchesEnded:function (touches, event) {
        this.onChangeTexture();
    },
    onMouseDown : function( event ) {
        this.onChangeTexture();
        return true;
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

    init:function() {
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

        var batch = cc.SpriteBatchNode.create(s_grossini_dance_atlas, 50);
        this.addChild(batch, 0, TAG_SPRITE_BATCH_NODE);

        this._texture1 = batch.getTexture();
        this._texture2 = cc.TextureCache.getInstance().addImage(s_grossini_dance_atlas_mono);

        for (var i = 0; i < 30; i++) {
            this.addNewSprite();
        }
    },
    addNewSprite:function () {
        var s = winSize;

        var p = cc.p(Math.random() * winSize.width, Math.random() * winSize.height);

        var batch = this.getChildByTag(TAG_SPRITE_BATCH_NODE);

        var idx = 0 | (Math.random() * 14);
        var x = (idx % 5) * 85;
        var y = (0 | (idx / 5)) * 121;

        var sprite = cc.Sprite.createWithTexture(batch.getTexture(), cc.rect(x, y, 85, 121));
        batch.addChild(sprite);

        sprite.setPosition(cc.p(p.x, p.y));

        var action;
        var random = Math.random();

        if (random < 0.20)
            action = cc.ScaleBy.create(3, 2);
        else if (random < 0.40)
            action = cc.RotateBy.create(3, 360);
        else if (random < 0.60)
            action = cc.Blink.create(1, 3);
        //else if (random < 0.8)
        //    action = cc.TintBy.create(2, 0, -255, -255);
        else
            action = cc.FadeOut.create(2);
        var action_back = action.reverse();
        var seq = cc.Sequence.create(action, action_back);

        sprite.runAction(cc.RepeatForever.create(seq));
    },
    onChangeTexture:function () {
        var batch = this.getChildByTag(TAG_SPRITE_BATCH_NODE);

        if (batch.getTexture() == this._texture1)
            batch.setTexture(this._texture2);
        else
            batch.setTexture(this._texture1);
    },
    onTouchesEnded:function (touches, event) {
        this.onChangeTexture();
    },
    onMouseDown : function( event ) {
        this.onChangeTexture();
        return true;
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
        this._super();
        // IMPORTANT:
        // The sprite frames will be cached AND RETAINED, and they won't be released unless you call
        //     cc.SpriteFrameCache.getInstance().removeUnusedSpriteFrames);
        spriteFrameCache.addSpriteFrames(s_grossiniPlist);
        spriteFrameCache.addSpriteFrames(s_grossini_grayPlist, s_grossini_gray);
        spriteFrameCache.addSpriteFrames(s_grossini_bluePlist, s_grossini_blue);

        //
        // Animation using Sprite BatchNode
        //
        this._sprite1 = cc.Sprite.createWithSpriteFrameName("grossini_dance_01.png");
        this._sprite1.setPosition(cc.p(winSize.width / 2 - 80, winSize.height / 2));

        var spritebatch = cc.SpriteBatchNode.create(s_grossini);
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

        var animation = cc.Animation.create(animFrames, 0.3);
        this._sprite1.runAction(cc.RepeatForever.create(cc.Animate.create(animation)));

        // to test issue #732, uncomment the following line
        this._sprite1.setFlipX(false);
        this._sprite1.setFlipY(false);

        //
        // Animation using standard Sprite
        //
        this._sprite2 = cc.Sprite.createWithSpriteFrameName("grossini_dance_01.png");
        this._sprite2.setPosition(cc.p(winSize.width / 2 + 80, winSize.height / 2));
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
        var animMixed = cc.Animation.create(moreFrames, 0.3);

        this._sprite2.runAction(cc.RepeatForever.create(cc.Animate.create(animMixed)));

        // to test issue #732, uncomment the following line
        this._sprite2.setFlipX(false);
        this._sprite2.setFlipY(false);

        this.schedule(this.onStartIn05Secs, 0.5);
        this._counter = 0;
    },
    onExit:function () {
        this._super();
        spriteFrameCache.removeSpriteFramesFromFile(s_grossiniPlist);
        spriteFrameCache.removeSpriteFramesFromFile(s_grossini_grayPlist);
        spriteFrameCache.removeSpriteFramesFromFile(s_grossini_bluePlist);
    },
    onStartIn05Secs:function () {
        this.unschedule(this.onStartIn05Secs);
        this.schedule(this.onFlipSprites, 1.0);
    },
    onFlipSprites:function (dt) {
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

        this._sprite1.setFlipX(fx);
        this._sprite1.setFlipY(fy);
        this._sprite2.setFlipX(fx);
        this._sprite2.setFlipY(fy);
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
    onEnter:function () {
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
        // Sprites that are contained in that texture can be instantiatied as cc.Sprites and then added to the cc.SpriteBatchNode
        // All cc.Sprites added to a cc.SpriteBatchNode are drawn in one OpenGL ES draw call
        // If the cc.Sprites are not added to a cc.SpriteBatchNode then an OpenGL ES draw call will be needed for each one, which is less efficient
        //
        // When you animate a sprite, CCAnimation changes the frame of the sprite using setDisplayFrame: (this is why the animation must be in the same texture)
        // When setDisplayFrame: is used in the CCAnimation it changes the frame to one specified by the cc.SpriteFrames that were added to the animation,
        // but texture id is still the same and so the sprite is still a child of the cc.SpriteBatchNode,
        // and therefore all the animation sprites are also drawn as part of the cc.SpriteBatchNode
        //
        var sprite = cc.Sprite.createWithSpriteFrameName("grossini_dance_01.png");
        sprite.setPosition(cc.p(winSize.width/2, winSize.height/2));

        var spriteBatch = cc.SpriteBatchNode.create(s_grossini_aliases);
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

        var animation = cc.Animation.create(animFrames, 0.3);
        // 14 frames * 1sec = 14 seconds
        sprite.runAction(cc.RepeatForever.create(cc.Animate.create(animation)));
    },
    onExit:function () {
        this._super();
        spriteFrameCache.removeSpriteFramesFromFile(s_grossini_aliasesPlist);
    }
});

//------------------------------------------------------------------
//
// SpriteOffsetAnchorRotation
//
//------------------------------------------------------------------
var SpriteOffsetAnchorRotation = SpriteTestDemo.extend({

    _title:"Sprite offset + anchor + rot",
    init:function () {
        this._super();
        spriteFrameCache.addSpriteFrames(s_grossiniPlist);
        spriteFrameCache.addSpriteFrames(s_grossini_grayPlist, s_grossini_gray);

        for (var i = 0; i < 3; i++) {
            //
            // Animation using Sprite BatchNode
            //
            var sprite = cc.Sprite.createWithSpriteFrame(spriteFrameCache.getSpriteFrame("grossini_dance_01.png"));
            sprite.setPosition(cc.p(winSize.width / 4 * (i + 1), winSize.height / 2));

            var point = cc.Sprite.create(s_pathR1);
            point.setScale(0.25);
            point.setPosition(sprite.getPosition());
            this.addChild(point, 1);

            switch (i) {
                case 0:
                    sprite.setAnchorPoint(cc.p(0,0));
                    break;
                case 1:
                    sprite.setAnchorPoint(cc.p(0.5, 0.5));
                    break;
                case 2:
                    sprite.setAnchorPoint(cc.p(1, 1));
                    break;
            }

            point.setPosition(sprite.getPosition());

            var animFrames = [];
            var str = "";
            for (var j = 1; j < 15; j++) {
                str = "grossini_dance_" + (j < 10 ? ("0" + j) : j) + ".png";
                var frame = spriteFrameCache.getSpriteFrame(str);
                animFrames.push(frame);
            }

            var animation = cc.Animation.create(animFrames, 0.3);
            sprite.runAction(cc.RepeatForever.create(cc.Animate.create(animation)));
            sprite.runAction(cc.RepeatForever.create(cc.RotateBy.create(10, 360)));

            this.addChild(sprite, 0);
        }
    },
    onExit:function () {
        this._super();
        spriteFrameCache.removeSpriteFramesFromFile(s_grossiniPlist);
        spriteFrameCache.removeSpriteFramesFromFile(s_grossini_grayPlist);
    }
});

//------------------------------------------------------------------
//
// SpriteBatchNodeOffsetAnchorRotation
//
//------------------------------------------------------------------
var SpriteBatchNodeOffsetAnchorRotation = SpriteTestDemo.extend({

    _title:"SpriteBatchNode offset + anchor + rot",

    init:function () {
        this._super();

        spriteFrameCache.addSpriteFrames(s_grossiniPlist);
        spriteFrameCache.addSpriteFrames(s_grossini_grayPlist, s_grossini_gray);

        var spritebatch = cc.SpriteBatchNode.create(s_grossini);
        this.addChild(spritebatch);

        for (var i = 0; i < 3; i++) {
            //
            // Animation using Sprite BatchNode
            //
            var sprite = cc.Sprite.createWithSpriteFrame(spriteFrameCache.getSpriteFrame("grossini_dance_01.png"));
            sprite.setPosition(cc.p(winSize.width / 4 * (i + 1), winSize.height / 2));

            var point = cc.Sprite.create(s_pathR1);
            point.setScale(0.25);
            point.setPosition(sprite.getPosition());
            this.addChild(point, 200);

            switch (i) {
                case 0:
                    sprite.setAnchorPoint(cc.p(0,0));
                    break;
                case 1:
                    sprite.setAnchorPoint(cc.p(0.5, 0.5));
                    break;
                case 2:
                    sprite.setAnchorPoint(cc.p(1, 1));
                    break;
            }
            point.setPosition(sprite.getPosition());

            var animFrames = [];
            var str = "";
            for (var k = 1; k < 15; k++) {
                str = "grossini_dance_" + (k < 10 ? ("0" + k) : k) + ".png";
                var frame = spriteFrameCache.getSpriteFrame(str);
                animFrames.push(frame);
            }

            var animation = cc.Animation.create(animFrames, 0.3);
            sprite.runAction(cc.RepeatForever.create(cc.Animate.create(animation)));
            sprite.runAction(cc.RepeatForever.create(cc.RotateBy.create(10, 360)));

            spritebatch.addChild(sprite, i);
        }
    },
    onExit:function () {
        this._super();
        spriteFrameCache.removeSpriteFramesFromFile(s_grossiniPlist);
        spriteFrameCache.removeSpriteFramesFromFile(s_grossini_grayPlist);
    }
});

//------------------------------------------------------------------
//
// SpriteOffsetAnchorScale
//
//------------------------------------------------------------------
var SpriteOffsetAnchorScale = SpriteTestDemo.extend({

    _title: "Sprite offset + anchor + scale",

    init:function () {
        this._super();
        spriteFrameCache.addSpriteFrames(s_grossiniPlist);
        spriteFrameCache.addSpriteFrames(s_grossini_grayPlist, s_grossini_gray);

        for (var i = 0; i < 3; i++) {
            //
            // Animation using Sprite BatchNode
            //
            var sprite = cc.Sprite.createWithSpriteFrame(spriteFrameCache.getSpriteFrame("grossini_dance_01.png"));
            sprite.setPosition(cc.p(winSize.width / 4 * (i + 1), winSize.height / 2));

            var point = cc.Sprite.create(s_pathR1);
            point.setScale(0.25);
            point.setPosition(sprite.getPosition());
            this.addChild(point, 1);

            switch (i) {
                case 0:
                    sprite.setAnchorPoint(cc.p(0,0));
                    break;
                case 1:
                    sprite.setAnchorPoint(cc.p(0.5, 0.5));
                    break;
                case 2:
                    sprite.setAnchorPoint(cc.p(1, 1));
                    break;
            }

            point.setPosition(sprite.getPosition());

            var animFrames = [];
            var str = "";
            for (var k = 1; k <= 14; k++) {
                str = "grossini_dance_" + (k < 10 ? ("0" + k) : k) + ".png";
                var frame = spriteFrameCache.getSpriteFrame(str);
                animFrames.push(frame);
            }

            var animation = cc.Animation.create(animFrames, 0.3);
            sprite.runAction(cc.RepeatForever.create(cc.Animate.create(animation)));

            var scale = cc.ScaleBy.create(2, 2);
            var scale_back = scale.reverse();
            var seq_scale = cc.Sequence.create(scale, scale_back);
            sprite.runAction(cc.RepeatForever.create(seq_scale));

            this.addChild(sprite, 0);
        }
    },
    onExit:function () {
        this._super();
        spriteFrameCache.removeSpriteFramesFromFile(s_grossiniPlist);
        spriteFrameCache.removeSpriteFramesFromFile(s_grossini_grayPlist);
    }
});


//------------------------------------------------------------------
//
// SpriteBatchNodeOffsetAnchorScale
//
//------------------------------------------------------------------
var SpriteBatchNodeOffsetAnchorScale = SpriteTestDemo.extend({

    _title:"SpriteBatchNode offset + anchor + scale",

    init:function () {
        this._super();
        var batch = cc.SpriteBatchNode.create(s_grossini);
        this.addChild(batch);

        spriteFrameCache.addSpriteFrames(s_grossiniPlist);
        spriteFrameCache.addSpriteFrames(s_grossini_grayPlist, s_grossini_gray);

        for (var i = 0; i < 3; i++) {
            //
            // Animation using Sprite BatchNode
            //
            var sprite = cc.Sprite.createWithSpriteFrame(spriteFrameCache.getSpriteFrame("grossini_dance_01.png"));
            sprite.setPosition(cc.p(winSize.width / 4 * (i + 1), winSize.height / 2));

            var point = cc.Sprite.create(s_pathR1);
            point.setScale(0.25);
            point.setPosition(sprite.getPosition());
            this.addChild(point, 200);

            switch (i) {
                case 0:
                    sprite.setAnchorPoint(cc.p(0,0));
                    break;
                case 1:
                    sprite.setAnchorPoint(cc.p(0.5, 0.5));
                    break;
                case 2:
                    sprite.setAnchorPoint(cc.p(1, 1));
                    break;
            }

            point.setPosition(sprite.getPosition());

            var animFrames = [];
            var str = "";
            for (var k = 1; k <= 14; k++) {
                str = "grossini_dance_" + (k < 10 ? ("0" + k) : k) + ".png";
                var frame = spriteFrameCache.getSpriteFrame(str);
                animFrames.push(frame);
            }

            var animation = cc.Animation.create(animFrames, 0.3);
            sprite.runAction(cc.RepeatForever.create(cc.Animate.create(animation)));

            var scale = cc.ScaleBy.create(2, 2);
            var scale_back = scale.reverse();
            var seq_scale = cc.Sequence.create(scale, scale_back);
            sprite.runAction(cc.RepeatForever.create(seq_scale));

            batch.addChild(sprite, i);
        }
    },
    onExit:function () {
        this._super();
        spriteFrameCache.removeSpriteFramesFromFile(s_grossiniPlist);
        spriteFrameCache.removeSpriteFramesFromFile(s_grossini_grayPlist);
    }
});

//
// SpriteOffsetAnchorSkew
//
var SpriteOffsetAnchorSkew = SpriteTestDemo.extend({

    _title:"Sprite offset + anchor + scale",

    init:function () {
        this._super();
        spriteFrameCache.addSpriteFrames(s_grossiniPlist);
        spriteFrameCache.addSpriteFrames(s_grossini_grayPlist, s_grossini_gray);

        for (var i = 0; i < 3; i++) {
            //
            // Animation using Sprite batch
            //
            var sprite = cc.Sprite.createWithSpriteFrameName("grossini_dance_01.png");
            sprite.setPosition(cc.p(winSize.width / 4 * (i + 1), winSize.height / 2));

            var point = cc.Sprite.create(s_pathR1);
            point.setScale(0.25);
            point.setPosition(sprite.getPosition());
            this.addChild(point, 1);

            switch (i) {
                case 0:
                    sprite.setAnchorPoint(cc.p(0,0));
                    break;
                case 1:
                    sprite.setAnchorPoint(cc.p(0.5, 0.5));
                    break;
                case 2:
                    sprite.setAnchorPoint(cc.p(1, 1));
                    break;
            }

            point.setPosition(sprite.getPosition());

            var animFrames = [];
            var tmp = "";
            for (var j = 1; j <= 14; j++) {
                tmp = "grossini_dance_" + (j < 10 ? ("0" + j) : j) + ".png";
                var frame = spriteFrameCache.getSpriteFrame(tmp);
                animFrames.push(frame);
            }

            var animation = cc.Animation.create(animFrames, 0.3);
            sprite.runAction(cc.RepeatForever.create(cc.Animate.create(animation)));

            var skewX = cc.SkewBy.create(2, 45, 0);
            var skewX_back = skewX.reverse();
            var skewY = cc.SkewBy.create(2, 0, 45);
            var skewY_back = skewY.reverse();

            var seq_skew = cc.Sequence.create(skewX, skewX_back, skewY, skewY_back);
            sprite.runAction(cc.RepeatForever.create(seq_skew));

            this.addChild(sprite, 0);
        }
    }
});

//
// SpriteBatchNodeOffsetAnchorSkew
//
var SpriteBatchNodeOffsetAnchorSkew = SpriteTestDemo.extend({

    _title:"SpriteBatchNode offset + anchor + skew",

    init:function () {
        this._super();
        spriteFrameCache.addSpriteFrames(s_grossiniPlist);
        spriteFrameCache.addSpriteFrames(s_grossini_grayPlist, s_grossini_gray);

        var spritebatch = cc.SpriteBatchNode.create(s_grossini);
        this.addChild(spritebatch);

        for (var i = 0; i < 3; i++) {
            //
            // Animation using Sprite batch
            //
            var sprite = cc.Sprite.createWithSpriteFrameName("grossini_dance_01.png");
            sprite.setPosition(cc.p(winSize.width / 4 * (i + 1), winSize.height / 2));

            var point = cc.Sprite.create(s_pathR1);
            point.setScale(0.25);
            point.setPosition(sprite.getPosition());
            this.addChild(point, 200);

            switch (i) {
                case 0:
                    sprite.setAnchorPoint(cc.p(0,0));
                    break;
                case 1:
                    sprite.setAnchorPoint(cc.p(0.5, 0.5));
                    break;
                case 2:
                    sprite.setAnchorPoint(cc.p(1, 1));
                    break;
            }

            point.setPosition(sprite.getPosition());

            var animFrames = [];
            var tmp = "";
            for (var j = 1; j <= 14; j++) {
                tmp = "grossini_dance_" + (j < 10 ? ("0" + j) : j) + ".png";
                var frame = spriteFrameCache.getSpriteFrame(tmp);
                animFrames.push(frame);
            }

            var animation = cc.Animation.create(animFrames, 0.3);
            sprite.runAction(cc.RepeatForever.create(cc.Animate.create(animation)));

            animFrames = null;

            var skewX = cc.SkewBy.create(2, 45, 0);
            var skewX_back = skewX.reverse();
            var skewY = cc.SkewBy.create(2, 0, 45);
            var skewY_back = skewY.reverse();

            var seq_skew = cc.Sequence.create(skewX, skewX_back, skewY, skewY_back);
            sprite.runAction(cc.RepeatForever.create(seq_skew));

            spritebatch.addChild(sprite, i);
        }
    }
});

//
// SpriteOffsetAnchorSkewScale
//
var SpriteOffsetAnchorSkewScale = SpriteTestDemo.extend({

    _title:"Sprite anchor + skew + scale",
    init:function () {
        this._super();
        spriteFrameCache.addSpriteFrames(s_grossiniPlist);
        spriteFrameCache.addSpriteFrames(s_grossini_grayPlist, s_grossini_gray);

        for (var i = 0; i < 3; i++) {
            //
            // Animation using Sprite batch
            //
            var sprite = cc.Sprite.createWithSpriteFrame(spriteFrameCache.getSpriteFrame("grossini_dance_01.png"));
            sprite.setPosition(cc.p(winSize.width / 4 * (i + 1), winSize.height / 2));

            var point = cc.Sprite.create(s_pathR1);
            point.setScale(0.25);
            point.setPosition(sprite.getPosition());
            this.addChild(point, 1);

            switch (i) {
                case 0:
                    sprite.setAnchorPoint(cc.p(0,0));
                    break;
                case 1:
                    sprite.setAnchorPoint(cc.p(0.5, 0.5));
                    break;
                case 2:
                    sprite.setAnchorPoint(cc.p(1, 1));
                    break;
            }

            point.setPosition(sprite.getPosition());

            var animFrames = [];
            var tmp = "";
            for (var j = 1; j <= 14; j++) {
                tmp = "grossini_dance_" + (j < 10 ? ("0" + j) : j) + ".png";
                var frame = spriteFrameCache.getSpriteFrame(tmp);
                animFrames.push(frame);
            }

            var animation = cc.Animation.create(animFrames, 0.3);
            sprite.runAction(cc.RepeatForever.create(cc.Animate.create(animation)));

            animFrames = null;

            // Skew
            var skewX = cc.SkewBy.create(2, 45, 0);
            var skewX_back = skewX.reverse();
            var skewY = cc.SkewBy.create(2, 0, 45);
            var skewY_back = skewY.reverse();

            var seq_skew = cc.Sequence.create(skewX, skewX_back, skewY, skewY_back);
            sprite.runAction(cc.RepeatForever.create(seq_skew));

            // Scale
            var scale = cc.ScaleBy.create(2, 2);
            var scale_back = scale.reverse();
            var seq_scale = cc.Sequence.create(scale, scale_back);
            sprite.runAction(cc.RepeatForever.create(seq_scale));

            this.addChild(sprite, 0);
        }
    }
});

//
// SpriteBatchNodeOffsetAnchorSkewScale
//
var SpriteBatchNodeOffsetAnchorSkewScale = SpriteTestDemo.extend({

    _title:"SpriteBatchNode anchor + skew + scale",

    init:function () {
        this._super();

        spriteFrameCache.addSpriteFrames(s_grossiniPlist);
        spriteFrameCache.addSpriteFrames(s_grossini_grayPlist, s_grossini_gray);

        var spritebatch = cc.SpriteBatchNode.create(s_grossini);
        this.addChild(spritebatch);

        for (var i = 0; i < 3; i++) {
            //
            // Animation using Sprite batch
            //
            var sprite = cc.Sprite.createWithSpriteFrameName("grossini_dance_01.png");
            sprite.setPosition(cc.p(winSize.width / 4 * (i + 1), winSize.height / 2));

            var point = cc.Sprite.create(s_pathR1);
            point.setScale(0.25);
            point.setPosition(sprite.getPosition());
            this.addChild(point, 200);

            switch (i) {
                case 0:
                    sprite.setAnchorPoint(cc.p(0,0));
                    break;
                case 1:
                    sprite.setAnchorPoint(cc.p(0.5, 0.5));
                    break;
                case 2:
                    sprite.setAnchorPoint(cc.p(1, 1));
                    break;
            }

            point.setPosition(sprite.getPosition());

            var animFrames = [];
            var tmp = "";
            for (var j = 1; j <= 14; j++) {
                tmp = "grossini_dance_" + (j < 10 ? ("0" + j) : j) + ".png";
                var frame = spriteFrameCache.getSpriteFrame(tmp);
                animFrames.push(frame);
            }

            var animation = cc.Animation.create(animFrames, 0.3);
            sprite.runAction(cc.RepeatForever.create(cc.Animate.create(animation)));

            animFrames = null;

            // skew
            var skewX = cc.SkewBy.create(2, 45, 0);
            var skewX_back = skewX.reverse();
            var skewY = cc.SkewBy.create(2, 0, 45);
            var skewY_back = skewY.reverse();

            var seq_skew = cc.Sequence.create(skewX, skewX_back, skewY, skewY_back);
            sprite.runAction(cc.RepeatForever.create(seq_skew));

            // scale
            var scale = cc.ScaleBy.create(2, 2);
            var scale_back = scale.reverse();
            var seq_scale = cc.Sequence.create(scale, scale_back);
            sprite.runAction(cc.RepeatForever.create(seq_scale));

            spritebatch.addChild(sprite, i);
        }
    }
});

//
// SpriteOffsetAnchorFlip
//
var SpriteOffsetAnchorFlip = SpriteTestDemo.extend({

    _title:"Sprite offset + anchor + flip",
    _subtitle:"issue #1078",

    init:function () {
        this._super();
        spriteFrameCache.addSpriteFrames(s_grossiniPlist);
        spriteFrameCache.addSpriteFrames(s_grossini_grayPlist, s_grossini_gray);

        for (var i = 0; i < 3; i++) {
            //
            // Animation using Sprite batch
            //
            var sprite = cc.Sprite.createWithSpriteFrameName("grossini_dance_01.png");
            sprite.setPosition(cc.p(winSize.width / 4 * (i + 1), winSize.height / 2));

            var point = cc.Sprite.create(s_pathR1);
            point.setScale(0.25);
            point.setPosition(sprite.getPosition());
            this.addChild(point, 1);

            switch (i) {
                case 0:
                    sprite.setAnchorPoint(cc.p(0,0));
                    break;
                case 1:
                    sprite.setAnchorPoint(cc.p(0.5, 0.5));
                    break;
                case 2:
                    sprite.setAnchorPoint(cc.p(1, 1));
                    break;
            }

            point.setPosition(sprite.getPosition());

            var animFrames = [];
            var tmp = "";
            for (var j = 1; j <= 14; j++) {
                tmp = "grossini_dance_" + (j < 10 ? ("0" + j) : j) + ".png";
                var frame = spriteFrameCache.getSpriteFrame(tmp);
                animFrames.push(frame);
            }

            var animation = cc.Animation.create(animFrames, 0.3);
            sprite.runAction(cc.RepeatForever.create(cc.Animate.create(animation)));

            animFrames = null;

            var flip = cc.FlipY.create(true);
            var flip_back = cc.FlipY.create(false);
            var delay = cc.DelayTime.create(1);
            var delay1 = cc.DelayTime.create(1);
            var seq = cc.Sequence.create(delay, flip, delay1, flip_back);
            sprite.runAction(cc.RepeatForever.create(seq));

            this.addChild(sprite, 0);
        }
    }
});

//
// SpriteBatchNodeOffsetAnchorFlip
//
var SpriteBatchNodeOffsetAnchorFlip = SpriteTestDemo.extend({

    _title:"SpriteBatchNode offset + anchor + flip",
    _subtitle:"issue #1078",

    init:function () {
        this._super();
        spriteFrameCache.addSpriteFrames(s_grossiniPlist);
        spriteFrameCache.addSpriteFrames(s_grossini_grayPlist, s_grossini_gray);

        var spritebatch = cc.SpriteBatchNode.create(s_grossini);
        this.addChild(spritebatch);

        for (var i = 0; i < 3; i++) {
            //
            // Animation using Sprite batch
            //
            var sprite = cc.Sprite.createWithSpriteFrame(spriteFrameCache.getSpriteFrame("grossini_dance_01.png"));
            sprite.setPosition(cc.p(winSize.width / 4 * (i + 1), winSize.height / 2));

            var point = cc.Sprite.create(s_pathR1);
            point.setScale(0.25);
            point.setPosition(sprite.getPosition());
            this.addChild(point, 200);

            switch (i) {
                case 0:
                    sprite.setAnchorPoint(cc.p(0,0));
                    break;
                case 1:
                    sprite.setAnchorPoint(cc.p(0.5, 0.5));
                    break;
                case 2:
                    sprite.setAnchorPoint(cc.p(1, 1));
                    break;
            }

            point.setPosition(sprite.getPosition());

            var animFrames = [];
            var tmp = "";
            for (var j = 1; j <= 14; j++) {
                tmp = "grossini_dance_" + (j < 10 ? ("0" + j) : j) + ".png";
                var frame = spriteFrameCache.getSpriteFrame(tmp);
                animFrames.push(frame);
            }

            var animation = cc.Animation.create(animFrames, 0.3);
            sprite.runAction(cc.RepeatForever.create(cc.Animate.create(animation)));

            animFrames = null;

            var flip = cc.FlipY.create(true);
            var flip_back = cc.FlipY.create(false);
            var delay = cc.DelayTime.create(1);
            var seq = cc.Sequence.create(delay, flip, delay.copy(), flip_back);
            sprite.runAction(cc.RepeatForever.create(seq));

            spritebatch.addChild(sprite, i);
        }
    }
});

//------------------------------------------------------------------
//
// SpriteAnimationSplit
//
//------------------------------------------------------------------
var SpriteAnimationSplit = SpriteTestDemo.extend({

    _title:"Sprite: Animation + flip",
    init:function () {
        this._super();
        var texture = cc.TextureCache.getInstance().addImage(s_dragon_animation);

        // manually add frames to the frame cache
        var frame0 = cc.SpriteFrame.createWithTexture(texture, cc.rect(132 * 0, 132 * 0, 132, 132));
        var frame1 = cc.SpriteFrame.createWithTexture(texture, cc.rect(132 * 1, 132 * 0, 132, 132));
        var frame2 = cc.SpriteFrame.createWithTexture(texture, cc.rect(132 * 2, 132 * 0, 132, 132));
        var frame3 = cc.SpriteFrame.createWithTexture(texture, cc.rect(132 * 3, 132 * 0, 132, 132));
        var frame4 = cc.SpriteFrame.createWithTexture(texture, cc.rect(132 * 0, 132 * 1, 132, 132));
        var frame5 = cc.SpriteFrame.createWithTexture(texture, cc.rect(132 * 1, 132 * 1, 132, 132));

        //
        // Animation using Sprite BatchNode
        //
        var sprite = cc.Sprite.createWithSpriteFrame(frame0);
        sprite.setPosition(cc.p(winSize.width / 2, winSize.height / 2));
        this.addChild(sprite);

        var animFrames = [];
        animFrames.push(frame0);
        animFrames.push(frame1);
        animFrames.push(frame2);
        animFrames.push(frame3);
        animFrames.push(frame4);
        animFrames.push(frame5);

        var animation = cc.Animation.create(animFrames, 0.2);
        var animate = cc.Animate.create(animation);
        var seq = cc.Sequence.create(animate,
            cc.FlipX.create(true),
            animate.copy(),
            cc.FlipX.create(false));

        sprite.runAction(cc.RepeatForever.create(seq));
    },
    onExit:function () {
        this._super();
    }
});

//------------------------------------------------------------------
//
// SpriteHybrid
//
//------------------------------------------------------------------
var SpriteHybrid = SpriteTestDemo.extend({
    _usingSpriteBatchNode:false,
    _title:"Hibryd.Sprite* sprite Test",

    init:function () {
        this._super();
        // parents
        var parent1 = cc.Node.create();
        var parent2 = cc.SpriteBatchNode.create(s_grossini, 50);

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
            var sprite = cc.Sprite.createWithSpriteFrame(frame);
            parent1.addChild(sprite, i, i);

            var x = -1000;
            var y = -1000;
            if (Math.random() < 0.2) {
                x = Math.random() * winSize.width;
                y = Math.random() * winSize.height;
            }
            sprite.setPosition(cc.p(x, y));

            var action = cc.RotateBy.create(4, 360);
            sprite.runAction(cc.RepeatForever.create(action));
        }

        this._usingSpriteBatchNode = false;

        this.schedule(this.reparentSprite, 2);
    },
    onExit:function () {
        this._super();
        spriteFrameCache.removeSpriteFramesFromFile(s_grossiniPlist);
    },
    reparentSprite:function () {
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

        var children = p1.getChildren();
        for (var i = 0; i < children.length; i++) {
            node = children[i];
            if (!node)
                break;

            retArray.push(node);
        }

        p1.removeAllChildrenWithCleanup(false);
        for (i = 0; i < retArray.length; i++) {
            node = retArray[i];
            if (!node)
                break;

            p2.addChild(node, i, i);
        }

        this._usingSpriteBatchNode = !this._usingSpriteBatchNode;
    }
});

//------------------------------------------------------------------
//
// SpriteBatchNodeChildren
//
//------------------------------------------------------------------
var SpriteBatchNodeChildren = SpriteTestDemo.extend({

    _title:"SpriteBatchNode Grand Children",

    init:function () {
        this._super();
        // parents
        var batch = cc.SpriteBatchNode.create(s_grossini, 50);
        this.addChild(batch, 0, TAG_SPRITE_BATCH_NODE);

        spriteFrameCache.addSpriteFrames(s_grossiniPlist);

        var sprite1 = cc.Sprite.createWithSpriteFrame(spriteFrameCache.getSpriteFrame("grossini_dance_01.png"));
        sprite1.setPosition(cc.p(winSize.width / 3, winSize.height / 2));

        var sprite2 = cc.Sprite.createWithSpriteFrame(spriteFrameCache.getSpriteFrame("grossini_dance_02.png"));
        sprite2.setPosition(cc.p(50, 50));

        var sprite3 = cc.Sprite.createWithSpriteFrame(spriteFrameCache.getSpriteFrame("grossini_dance_03.png"));
        sprite3.setPosition(cc.p(-50, -50));

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

        var animation = cc.Animation.create(animFrames, 0.2);
        sprite1.runAction(cc.RepeatForever.create(cc.Animate.create(animation)));
        // END NEW CODE

        var action = cc.MoveBy.create(2, cc.p(200, 0));
        var action_back = action.reverse();
        var action_rot = cc.RotateBy.create(2, 360);
        var action_s = cc.ScaleBy.create(2, 2);
        var action_s_back = action_s.reverse();

        var seq2 = action_rot.reverse();
        sprite2.runAction(cc.RepeatForever.create(seq2));

        sprite1.runAction(cc.RepeatForever.create(action_rot));
        sprite1.runAction(cc.RepeatForever.create(cc.Sequence.create(action, action_back)));
        sprite1.runAction(cc.RepeatForever.create(cc.Sequence.create(action_s, action_s_back)));
    },
    onExit:function () {
        this._super();
    }
});

//------------------------------------------------------------------
//
// SpriteBatchNodeChildrenZ
//
//------------------------------------------------------------------
var SpriteBatchNodeChildrenZ = SpriteTestDemo.extend({

    _title:"SpriteBatchNode Children Z",

    init:function () {
        this._super();
        // parents
        var batch;
        var sprite1, sprite2, sprite3;
        spriteFrameCache.addSpriteFrames(s_grossiniPlist);

        // test 1
        batch = cc.SpriteBatchNode.create(s_grossini, 50);
        this.addChild(batch, 0, TAG_SPRITE_BATCH_NODE);

        sprite1 = cc.Sprite.createWithSpriteFrame(spriteFrameCache.getSpriteFrame("grossini_dance_01.png"));
        sprite1.setPosition(cc.p(winSize.width / 3, winSize.height / 2));

        sprite2 = cc.Sprite.createWithSpriteFrame(spriteFrameCache.getSpriteFrame("grossini_dance_02.png"));
        sprite2.setPosition(cc.p(20, 30));

        sprite3 = cc.Sprite.createWithSpriteFrame(spriteFrameCache.getSpriteFrame("grossini_dance_03.png"));
        sprite3.setPosition(cc.p(-20, 30));

        batch.addChild(sprite1);
        sprite1.addChild(sprite2, 2);
        sprite1.addChild(sprite3, -2);

        // test 2
        batch = cc.SpriteBatchNode.create(s_grossini, 50);
        this.addChild(batch, 0, TAG_SPRITE_BATCH_NODE);

        sprite1 = cc.Sprite.createWithSpriteFrame(spriteFrameCache.getSpriteFrame("grossini_dance_01.png"));
        sprite1.setPosition(cc.p(2 * winSize.width / 3, winSize.height / 2));

        sprite2 = cc.Sprite.createWithSpriteFrame(spriteFrameCache.getSpriteFrame("grossini_dance_02.png"));
        sprite2.setPosition(cc.p(20, 30));

        sprite3 = cc.Sprite.createWithSpriteFrame(spriteFrameCache.getSpriteFrame("grossini_dance_03.png"));
        sprite3.setPosition(cc.p(-20, 30));

        batch.addChild(sprite1);
        sprite1.addChild(sprite2, -2);
        sprite1.addChild(sprite3, 2);

        // test 3
        batch = cc.SpriteBatchNode.create(s_grossini, 50);
        this.addChild(batch, 0, TAG_SPRITE_BATCH_NODE);

        sprite1 = cc.Sprite.createWithSpriteFrame(spriteFrameCache.getSpriteFrame("grossini_dance_01.png"));
        sprite1.setPosition(cc.p(winSize.width / 2 - 90, winSize.height / 4));

        sprite2 = cc.Sprite.createWithSpriteFrame(spriteFrameCache.getSpriteFrame("grossini_dance_02.png"));
        sprite2.setPosition(cc.p(winSize.width / 2 - 60, winSize.height / 4));

        sprite3 = cc.Sprite.createWithSpriteFrame(spriteFrameCache.getSpriteFrame("grossini_dance_03.png"));
        sprite3.setPosition(cc.p(winSize.width / 2 - 30, winSize.height / 4));

        batch.addChild(sprite1, 10);
        batch.addChild(sprite2, -10);
        batch.addChild(sprite3, -5);

        // test 4
        batch = cc.SpriteBatchNode.create(s_grossini, 50);
        this.addChild(batch, 0, TAG_SPRITE_BATCH_NODE);

        sprite1 = cc.Sprite.createWithSpriteFrame(spriteFrameCache.getSpriteFrame("grossini_dance_01.png"));
        sprite1.setPosition(cc.p(winSize.width / 2 + 30, winSize.height / 4));

        sprite2 = cc.Sprite.createWithSpriteFrame(spriteFrameCache.getSpriteFrame("grossini_dance_02.png"));
        sprite2.setPosition(cc.p(winSize.width / 2 + 60, winSize.height / 4));

        sprite3 = cc.Sprite.createWithSpriteFrame(spriteFrameCache.getSpriteFrame("grossini_dance_03.png"));
        sprite3.setPosition(cc.p(winSize.width / 2 + 90, winSize.height / 4));

        batch.addChild(sprite1, -10);
        batch.addChild(sprite2, -5);
        batch.addChild(sprite3, -2);
    },
    onExit:function () {
        this._super();
    }
});

//------------------------------------------------------------------
//
// SpriteChildrenVisibility
//
//------------------------------------------------------------------
var SpriteChildrenVisibility = SpriteTestDemo.extend({
    _title:"Sprite & SpriteBatchNode Visibility",

    init:function () {
        this._super();

        spriteFrameCache.addSpriteFrames(s_grossiniPlist);
        //
        // SpriteBatchNode
        //
        // parents
        var aParent = cc.SpriteBatchNode.create(s_grossini, 50);
        aParent.setPosition(cc.p(winSize.width / 3, winSize.height / 2));
        this.addChild(aParent, 0);

        var sprite1 = cc.Sprite.createWithSpriteFrame(spriteFrameCache.getSpriteFrame("grossini_dance_01.png"));
        sprite1.setPosition(cc.p(0, 0));

        var sprite2 = cc.Sprite.createWithSpriteFrame(spriteFrameCache.getSpriteFrame("grossini_dance_02.png"));
        sprite2.setPosition(cc.p(20, 30));

        var sprite3 = cc.Sprite.createWithSpriteFrame(spriteFrameCache.getSpriteFrame("grossini_dance_03.png"));
        sprite3.setPosition(cc.p(-20, 30));

        aParent.addChild(sprite1);
        sprite1.addChild(sprite2, -2);
        sprite1.addChild(sprite3, 2);

        sprite1.runAction(cc.Blink.create(5, 10));

        //
        // Sprite
        //
        aParent = cc.Node.create();
        aParent.setPosition(cc.p(2 * winSize.width / 3, winSize.height / 2));
        this.addChild(aParent, 0);

        sprite1 = cc.Sprite.createWithSpriteFrame(spriteFrameCache.getSpriteFrame("grossini_dance_01.png"));
        sprite1.setPosition(cc.p(0, 0));

        sprite2 = cc.Sprite.createWithSpriteFrame(spriteFrameCache.getSpriteFrame("grossini_dance_02.png"));
        sprite2.setPosition(cc.p(20, 30));

        sprite3 = cc.Sprite.createWithSpriteFrame(spriteFrameCache.getSpriteFrame("grossini_dance_03.png"));
        sprite3.setPosition(cc.p(-20, 30));

        aParent.addChild(sprite1);
        sprite1.addChild(sprite2, -2);
        sprite1.addChild(sprite3, 2);

        sprite1.runAction(cc.Blink.create(5, 10));
    },
    onExit:function () {
        this._super();
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

    init:function () {
        this._super();
        spriteFrameCache.addSpriteFrames(s_grossiniPlist);
        //
        // SpriteBatchNode
        //
        // parents
        var aParent = cc.SpriteBatchNode.create(s_grossini, 50);
        aParent.setPosition(cc.p(winSize.width / 3, winSize.height / 2));
        this.addChild(aParent, 0);

        var sprite1 = cc.Sprite.createWithSpriteFrame(spriteFrameCache.getSpriteFrame("grossini_dance_01.png"));
        sprite1.setPosition(cc.p(0, 0));

        var sprite2 = cc.Sprite.createWithSpriteFrame(spriteFrameCache.getSpriteFrame("grossini_dance_02.png"));
        sprite2.setPosition(cc.p(20, 30));

        var sprite3 = cc.Sprite.createWithSpriteFrame(spriteFrameCache.getSpriteFrame("grossini_dance_03.png"));
        sprite3.setPosition(cc.p(-20, 30));

        // test issue #665
        sprite1.setVisible(false);

        aParent.addChild(sprite1);
        sprite1.addChild(sprite2, -2);
        sprite1.addChild(sprite3, 2);

        //
        // Sprite
        //
        aParent = cc.Node.create();
        aParent.setPosition(cc.p(2 * winSize.width / 3, winSize.height / 2));
        this.addChild(aParent, 0);

        sprite1 = cc.Sprite.createWithSpriteFrame(spriteFrameCache.getSpriteFrame("grossini_dance_01.png"));
        sprite1.setPosition(cc.p(0, 0));

        sprite2 = cc.Sprite.createWithSpriteFrame(spriteFrameCache.getSpriteFrame("grossini_dance_02.png"));
        sprite2.setPosition(cc.p(20, 30));

        sprite3 = cc.Sprite.createWithSpriteFrame(spriteFrameCache.getSpriteFrame("grossini_dance_03.png"));
        sprite3.setPosition(cc.p(-20, 30));

        // test issue #665
        sprite1.setVisible(false);

        aParent.addChild(sprite1);
        sprite1.addChild(sprite2, -2);
        sprite1.addChild(sprite3, 2);
    }
});

//------------------------------------------------------------------
//
// SpriteChildrenAnchorPoint
//
//------------------------------------------------------------------
var SpriteChildrenAnchorPoint = SpriteTestDemo.extend({

    _title:"Sprite: children + anchor",

    init:function() {
        this._super();
        spriteFrameCache.addSpriteFrames(s_grossiniPlist);

        var aParent = cc.Node.create();
        this.addChild(aParent, 0);

        // anchor (0,0)
        var sprite1 = cc.Sprite.createWithSpriteFrame(spriteFrameCache.getSpriteFrame("grossini_dance_08.png"));
        sprite1.setPosition(cc.p(winSize.width / 4, winSize.height / 2));
        sprite1.setAnchorPoint(cc.p(0, 0));

        var sprite2 = cc.Sprite.createWithSpriteFrame(spriteFrameCache.getSpriteFrame("grossini_dance_02.png"));
        sprite2.setPosition(cc.p(20, 30));

        var sprite3 = cc.Sprite.createWithSpriteFrame(spriteFrameCache.getSpriteFrame("grossini_dance_03.png"));
        sprite3.setPosition(cc.p(-20, 30));

        var sprite4 = cc.Sprite.createWithSpriteFrame(spriteFrameCache.getSpriteFrame("grossini_dance_04.png"));
        sprite4.setPosition(cc.p(0, 0));
        sprite4.setScale(0.5);

        aParent.addChild(sprite1);
        sprite1.addChild(sprite2, -2);
        sprite1.addChild(sprite3, -2);
        sprite1.addChild(sprite4, 3);

        var point = cc.Sprite.create(s_pathR1);
        point.setScale(0.25);
        point.setPosition(sprite1.getPosition());
        this.addChild(point, 10);

        // anchor (0.5, 0.5)
        sprite1 = cc.Sprite.createWithSpriteFrame(spriteFrameCache.getSpriteFrame("grossini_dance_08.png"));
        sprite1.setPosition(cc.p(winSize.width / 2, winSize.height / 2));
        sprite1.setAnchorPoint(cc.p(0.5, 0.5));

        sprite2 = cc.Sprite.createWithSpriteFrame(spriteFrameCache.getSpriteFrame("grossini_dance_02.png"));
        sprite2.setPosition(cc.p(20, 30));

        sprite3 = cc.Sprite.createWithSpriteFrame(spriteFrameCache.getSpriteFrame("grossini_dance_03.png"));
        sprite3.setPosition(cc.p(-20, 30));

        sprite4 = cc.Sprite.createWithSpriteFrame(spriteFrameCache.getSpriteFrame("grossini_dance_04.png"));
        sprite4.setPosition(cc.p(0, 0));
        sprite4.setScale(0.5);

        aParent.addChild(sprite1);
        sprite1.addChild(sprite2, -2);
        sprite1.addChild(sprite3, -2);
        sprite1.addChild(sprite4, 3);

        point = cc.Sprite.create(s_pathR1);
        point.setScale(0.25);
        point.setPosition(sprite1.getPosition());
        this.addChild(point, 10);

        // anchor (1,1)
        sprite1 = cc.Sprite.createWithSpriteFrame(spriteFrameCache.getSpriteFrame("grossini_dance_08.png"));
        sprite1.setPosition(cc.p(winSize.width / 2 + winSize.width / 4, winSize.height / 2));
        sprite1.setAnchorPoint(cc.p(1, 1));

        sprite2 = cc.Sprite.createWithSpriteFrame(spriteFrameCache.getSpriteFrame("grossini_dance_02.png"));
        sprite2.setPosition(cc.p(20, 30));

        sprite3 = cc.Sprite.createWithSpriteFrame(spriteFrameCache.getSpriteFrame("grossini_dance_03.png"));
        sprite3.setPosition(cc.p(-20, 30));

        sprite4 = cc.Sprite.createWithSpriteFrame(spriteFrameCache.getSpriteFrame("grossini_dance_04.png"));
        sprite4.setPosition(cc.p(0, 0));
        sprite4.setScale(0.5);

        aParent.addChild(sprite1);
        sprite1.addChild(sprite2, -2);
        sprite1.addChild(sprite3, -2);
        sprite1.addChild(sprite4, 3);

        point = cc.Sprite.create(s_pathR1);
        point.setScale(0.25);
        point.setPosition(sprite1.getPosition());
        this.addChild(point, 10);
    },
    onExit:function () {
        this._super();
    }
});

//------------------------------------------------------------------
//
// SpriteBatchNodeChildrenAnchorPoint
//
//------------------------------------------------------------------
var SpriteBatchNodeChildrenAnchorPoint = SpriteTestDemo.extend({

    _title:"SpriteBatchNode: children + anchor",

    init:function() {
        this._super();

        spriteFrameCache.addSpriteFrames(s_grossiniPlist);
        //
        // SpriteBatchNode
        //
        // parents
        var aParent = cc.SpriteBatchNode.create(s_grossini, 50);
        this.addChild(aParent, 0);

        // anchor (0,0)
        var sprite1 = cc.Sprite.createWithSpriteFrame(spriteFrameCache.getSpriteFrame("grossini_dance_08.png"));
        sprite1.setPosition(cc.p(winSize.width / 4, winSize.height / 2));
        sprite1.setAnchorPoint(cc.p(0, 0));

        var sprite2 = cc.Sprite.createWithSpriteFrame(spriteFrameCache.getSpriteFrame("grossini_dance_02.png"));
        sprite2.setPosition(cc.p(20, 30));

        var sprite3 = cc.Sprite.createWithSpriteFrame(spriteFrameCache.getSpriteFrame("grossini_dance_03.png"));
        sprite3.setPosition(cc.p(-20, 30));

        var sprite4 = cc.Sprite.createWithSpriteFrame(spriteFrameCache.getSpriteFrame("grossini_dance_04.png"));
        sprite4.setPosition(cc.p(0, 0));
        sprite4.setScale(0.5);

        aParent.addChild(sprite1);
        sprite1.addChild(sprite2, -2);
        sprite1.addChild(sprite3, -2);
        sprite1.addChild(sprite4, 3);

        var point = cc.Sprite.create(s_pathR1);
        point.setScale(0.25);
        point.setPosition(sprite1.getPosition());
        this.addChild(point, 10);

        // anchor (0.5, 0.5)
        sprite1 = cc.Sprite.createWithSpriteFrame(spriteFrameCache.getSpriteFrame("grossini_dance_08.png"));
        sprite1.setPosition(cc.p(winSize.width / 2, winSize.height / 2));
        sprite1.setAnchorPoint(cc.p(0.5, 0.5));

        sprite2 = cc.Sprite.createWithSpriteFrame(spriteFrameCache.getSpriteFrame("grossini_dance_02.png"));
        sprite2.setPosition(cc.p(20, 30));

        sprite3 = cc.Sprite.createWithSpriteFrame(spriteFrameCache.getSpriteFrame("grossini_dance_03.png"));
        sprite3.setPosition(cc.p(-20, 30));

        sprite4 = cc.Sprite.createWithSpriteFrame(spriteFrameCache.getSpriteFrame("grossini_dance_04.png"));
        sprite4.setPosition(cc.p(0, 0));
        sprite4.setScale(0.5);

        aParent.addChild(sprite1);
        sprite1.addChild(sprite2, -2);
        sprite1.addChild(sprite3, -2);
        sprite1.addChild(sprite4, 3);

        point = cc.Sprite.create(s_pathR1);
        point.setScale(0.25);
        point.setPosition(sprite1.getPosition());
        this.addChild(point, 10);


        // anchor (1,1)
        sprite1 = cc.Sprite.createWithSpriteFrame(spriteFrameCache.getSpriteFrame("grossini_dance_08.png"));
        sprite1.setPosition(cc.p(winSize.width / 2 + winSize.width / 4, winSize.height / 2));
        sprite1.setAnchorPoint(cc.p(1, 1));

        sprite2 = cc.Sprite.createWithSpriteFrame(spriteFrameCache.getSpriteFrame("grossini_dance_02.png"));
        sprite2.setPosition(cc.p(20, 30));

        sprite3 = cc.Sprite.createWithSpriteFrame(spriteFrameCache.getSpriteFrame("grossini_dance_03.png"));
        sprite3.setPosition(cc.p(-20, 30));

        sprite4 = cc.Sprite.createWithSpriteFrame(spriteFrameCache.getSpriteFrame("grossini_dance_04.png"));
        sprite4.setPosition(cc.p(0, 0));
        sprite4.setScale(0.5);

        aParent.addChild(sprite1);
        sprite1.addChild(sprite2, -2);
        sprite1.addChild(sprite3, -2);
        sprite1.addChild(sprite4, 3);

        point = cc.Sprite.create(s_pathR1);
        point.setScale(0.25);
        point.setPosition(sprite1.getPosition());
        this.addChild(point, 10);
    },
    onExit:function () {
        this._super();
    }
});

//------------------------------------------------------------------
//
// SpriteBatchNodeChildrenScale
//
//------------------------------------------------------------------
var SpriteBatchNodeChildrenScale = SpriteTestDemo.extend({

    _title:"Sprite/BatchNode + child + scale + rot",

    init:function() {
        this._super();
        spriteFrameCache.addSpriteFrames(s_grossini_familyPlist);

        var rot = cc.RotateBy.create(10, 360);
        var seq = cc.RepeatForever.create(rot);

        //
        // Children + Scale using Sprite
        // Test 1
        //
        var aParent = cc.Node.create();
        var sprite1 = cc.Sprite.createWithSpriteFrame(spriteFrameCache.getSpriteFrame("grossinis_sister1.png"));
        sprite1.setPosition(cc.p(winSize.width / 4, winSize.height / 4));
        sprite1.setScaleX(0.5);
        sprite1.setScaleY(2.0);
        sprite1.runAction(seq);


        var sprite2 = cc.Sprite.createWithSpriteFrame(spriteFrameCache.getSpriteFrame("grossinis_sister2.png"));
        sprite2.setPosition(cc.p(50, 0));

        this.addChild(aParent);
        aParent.addChild(sprite1);
        sprite1.addChild(sprite2);

        rot = cc.RotateBy.create(10, 360);
        seq = cc.RepeatForever.create(rot);
        //
        // Children + Scale using SpriteBatchNode
        // Test 2
        //
        aParent = cc.SpriteBatchNode.create(s_grossini_family);
        sprite1 = cc.Sprite.createWithSpriteFrame(spriteFrameCache.getSpriteFrame("grossinis_sister1.png"));
        sprite1.setPosition(cc.p(3 * winSize.width / 4, winSize.height / 4));
        sprite1.setScaleX(0.5);
        sprite1.setScaleY(2.0);
        sprite1.runAction(seq);

        sprite2 = cc.Sprite.createWithSpriteFrame(spriteFrameCache.getSpriteFrame("grossinis_sister2.png"));
        sprite2.setPosition(cc.p(50, 0));

        this.addChild(aParent);
        aParent.addChild(sprite1);
        sprite1.addChild(sprite2);

        rot = cc.RotateBy.create(10, 360);
        seq = cc.RepeatForever.create(rot);
        //
        // Children + Scale using Sprite
        // Test 3
        //
        aParent = cc.Node.create();
        sprite1 = cc.Sprite.createWithSpriteFrame(spriteFrameCache.getSpriteFrame("grossinis_sister1.png"));
        sprite1.setPosition(cc.p(winSize.width / 4, 2 * winSize.height / 3));
        sprite1.setScaleX(1.5);
        sprite1.setScaleY(0.5);
        sprite1.runAction(seq);

        sprite2 = cc.Sprite.createWithSpriteFrame(spriteFrameCache.getSpriteFrame("grossinis_sister2.png"));
        sprite2.setPosition(cc.p(50, 0));

        this.addChild(aParent);
        aParent.addChild(sprite1);
        sprite1.addChild(sprite2);

        rot = cc.RotateBy.create(10, 360);
        seq = cc.RepeatForever.create(rot);
        //
        // Children + Scale using Sprite
        // Test 4
        //
        aParent = cc.SpriteBatchNode.create(s_grossini_family);
        sprite1 = cc.Sprite.createWithSpriteFrame(spriteFrameCache.getSpriteFrame("grossinis_sister1.png"));
        sprite1.setPosition(cc.p(3 * winSize.width / 4, 2 * winSize.height / 3));
        sprite1.setScaleX(1.5);
        sprite1.setScaleY(0.5);
        sprite1.runAction(seq);

        sprite2 = cc.Sprite.createWithSpriteFrame(spriteFrameCache.getSpriteFrame("grossinis_sister2.png"));
        sprite2.setPosition(cc.p(50, 0));

        this.addChild(aParent);
        aParent.addChild(sprite1);
        sprite1.addChild(sprite2);
    }
});

//------------------------------------------------------------------
//
// SpriteChildrenChildren
//
//------------------------------------------------------------------
var SpriteChildrenChildren = SpriteTestDemo.extend({

    _title:"Sprite/BatchNode + child + scale + rot",

    init:function() {
        this._super();

        spriteFrameCache.addSpriteFrames(s_ghostsPlist);

        var rot = cc.RotateBy.create(10, 360);
        var seq = cc.RepeatForever.create(rot);

        var rot_back = rot.reverse();
        var rot_back_fe = cc.RepeatForever.create(rot_back);

        //
        // SpriteBatchNode: 3 levels of children
        //
        var aParent = cc.Node.create();
        this.addChild(aParent);

        // parent
        var l1 = cc.Sprite.createWithSpriteFrame(spriteFrameCache.getSpriteFrame("father.gif"));
        l1.setPosition(cc.p(winSize.width / 2, winSize.height / 2));
        l1.runAction(seq.copy());
        aParent.addChild(l1);
        var l1Size = l1.getContentSize();

        // child left
        var l2a = cc.Sprite.createWithSpriteFrame(spriteFrameCache.getSpriteFrame("sister1.gif"));
        l2a.setPosition(cc.p(-50 + l1Size.width / 2, 0 + l1Size.height / 2));
        l2a.runAction(rot_back_fe.copy());
        l1.addChild(l2a);
        var l2aSize = l2a.getContentSize();


        // child right
        var l2b = cc.Sprite.createWithSpriteFrame(spriteFrameCache.getSpriteFrame("sister2.gif"));
        l2b.setPosition(cc.p(+50 + l1Size.width / 2, 0 + l1Size.height / 2));
        l2b.runAction(rot_back_fe.copy());
        l1.addChild(l2b);
        var l2bSize = l2a.getContentSize();


        // child left bottom
        var l3a1 = cc.Sprite.createWithSpriteFrame(spriteFrameCache.getSpriteFrame("child1.gif"));
        l3a1.setScale(0.45);
        l3a1.setPosition(cc.p(0 + l2aSize.width / 2, -100 + l2aSize.height / 2));
        l2a.addChild(l3a1);

        // child left top
        var l3a2 = cc.Sprite.createWithSpriteFrame(spriteFrameCache.getSpriteFrame("child1.gif"));
        l3a2.setScale(0.45);
        l3a1.setPosition(cc.p(0 + l2aSize.width / 2, +100 + l2aSize.height / 2));
        l2a.addChild(l3a2);

        // child right bottom
        var l3b1 = cc.Sprite.createWithSpriteFrame(spriteFrameCache.getSpriteFrame("child1.gif"));
        l3b1.setScale(0.45);
        l3b1.setFlipY(true);
        l3b1.setPosition(cc.p(0 + l2bSize.width / 2, -100 + l2bSize.height / 2));
        l2b.addChild(l3b1);

        // child right top
        var l3b2 = cc.Sprite.createWithSpriteFrame(spriteFrameCache.getSpriteFrame("child1.gif"));
        l3b2.setScale(0.45);
        l3b2.setFlipY(true);
        l3b1.setPosition(cc.p(0 + l2bSize.width / 2, +100 + l2bSize.height / 2));
        l2b.addChild(l3b2);
    }
});

//------------------------------------------------------------------
//
// SpriteBatchNodeChildrenChildren
//
//------------------------------------------------------------------
var SpriteBatchNodeChildrenChildren = SpriteTestDemo.extend({

    _title:"SpriteBatchNode multiple levels of children",

    init:function() {
        this._super();

        spriteFrameCache.addSpriteFrames(s_ghostsPlist);

        var rot = cc.RotateBy.create(10, 360);
        var seq = cc.RepeatForever.create(rot);

        var rot_back = rot.reverse();
        var rot_back_fe = cc.RepeatForever.create(rot_back);

        //
        // SpriteBatchNode: 3 levels of children
        //
        var aParent = cc.SpriteBatchNode.create(s_ghosts);
        //TODO for WebGL
        //aParent.getTexture().generateMipmap();
        this.addChild(aParent);

        // parent
        var l1 = cc.Sprite.createWithSpriteFrame(spriteFrameCache.getSpriteFrame("father.gif"));
        l1.setPosition(cc.p(winSize.width / 2, winSize.height / 2));
        l1.runAction(seq.copy());
        aParent.addChild(l1);
        var l1Size = l1.getContentSize();

        // child left
        var l2a = cc.Sprite.createWithSpriteFrame(spriteFrameCache.getSpriteFrame("sister1.gif"));
        l2a.setPosition(cc.p(-50 + l1Size.width / 2, 0 + l1Size.height / 2));
        l2a.runAction(rot_back_fe.copy());
        l1.addChild(l2a);
        var l2aSize = l2a.getContentSize();


        // child right
        var l2b = cc.Sprite.createWithSpriteFrame(spriteFrameCache.getSpriteFrame("sister2.gif"));
        l2b.setPosition(cc.p(50 + l1Size.width / 2, 0 + l1Size.height / 2));
        l2b.runAction(rot_back_fe.copy());
        l1.addChild(l2b);
        var l2bSize = l2a.getContentSize();


        // child left bottom
        var l3a1 = cc.Sprite.createWithSpriteFrame(spriteFrameCache.getSpriteFrame("child1.gif"));
        l3a1.setScale(0.45);
        l3a1.setPosition(cc.p(0 + l2aSize.width / 2, -100 + l2aSize.height / 2));
        l2a.addChild(l3a1);

        // child left top
        var l3a2 = cc.Sprite.createWithSpriteFrame(spriteFrameCache.getSpriteFrame("child1.gif"));
        l3a2.setScale(0.45);
        l3a1.setPosition(cc.p(0 + l2aSize.width / 2, +100 + l2aSize.height / 2));
        l2a.addChild(l3a2);

        // child right bottom
        var l3b1 = cc.Sprite.createWithSpriteFrame(spriteFrameCache.getSpriteFrame("child1.gif"));
        l3b1.setScale(0.45);
        l3b1.setFlipY(true);
        l3b1.setPosition(cc.p(0 + l2bSize.width / 2, -100 + l2bSize.height / 2));
        l2b.addChild(l3b1);

        // child right top
        var l3b2 = cc.Sprite.createWithSpriteFrame(spriteFrameCache.getSpriteFrame("child1.gif"));
        l3b2.setScale(0.45);
        l3b2.setFlipY(true);
        l3b1.setPosition(cc.p(0 + l2bSize.width / 2, +100 + l2bSize.height / 2));
        l2b.addChild(l3b2);
    }
});

//------------------------------------------------------------------
//
// SpriteNilTexture
//
//------------------------------------------------------------------
var SpriteNilTexture = SpriteTestDemo.extend({

    _title:"Sprite without texture",
    _subtitle:"opacity and color should work",

    init:function() {
        this._super();

        // TEST: If no texture is given, then Opacity + Color should work.
        var sprite = cc.Sprite.create();
        sprite.setTextureRect(cc.rect(0, 0, 300, 300));
        // sprite.setColor(cc.RED);
        sprite.setColor( cc.c3b(255,0,0) );
        sprite.setOpacity(128);
        sprite.setPosition(cc.p(3 * winSize.width / 4, winSize.height / 2));
        this.addChild(sprite, 100);

        sprite = cc.Sprite.create();
        sprite.setTextureRect(cc.rect(0, 0, 300, 300));
        // sprite.setColor(cc.BLUE);
        sprite.setColor( cc.c3b(0,0,255) );
        sprite.setOpacity(128);
        sprite.setPosition(cc.p(winSize.width / 4, winSize.height / 2));
        this.addChild(sprite, 100);
    }
});

//------------------------------------------------------------------
//
// SpriteSubclass
//
//------------------------------------------------------------------
var MySprite1 = cc.Sprite.extend({
    _ivar:0,
    init:function() {
        this._super();
    }
});
MySprite1.spriteWithSpriteFrameName = function (spriteFrameName) {
    var pFrame = spriteFrameCache.getSpriteFrame(spriteFrameName);
    var sprite = new MySprite1();
    sprite.initWithSpriteFrame(pFrame);

    return sprite;
};

var MySprite2 = cc.Sprite.extend({
    _ivar:0,
    init:function() {
        this._super();
    }
});
MySprite2.spriteWithFile = function (name) {
    var sprite = new MySprite2();
    sprite.initWithFile(name);

    return sprite;
};

var SpriteSubclass = SpriteTestDemo.extend({
    _title:"Sprite subclass",
    _subtitle:"Testing initWithTexture:rect method",

    init:function() {
        this._super();

        spriteFrameCache.addSpriteFrames(s_ghostsPlist);
        var aParent = cc.SpriteBatchNode.create(s_ghosts);

        // MySprite1
        var sprite = MySprite1.spriteWithSpriteFrameName("father.gif");
        sprite.setPosition(cc.p(winSize.width / 4, winSize.height / 2));
        aParent.addChild(sprite);
        this.addChild(aParent);

        // MySprite2
        var sprite2 = MySprite2.spriteWithFile(s_pathGrossini);
        this.addChild(sprite2);
        sprite2.setPosition(cc.p(winSize.width / 4 * 3, winSize.height / 2));
    }
});

//------------------------------------------------------------------
//
// AnimationCache
//
//------------------------------------------------------------------
var AnimationCache = SpriteTestDemo.extend({

    _title:"AnimationCache",
    _subtitle:"Sprite should be animated",

    init:function() {
        this._super();
        spriteFrameCache.addSpriteFrames(s_grossiniPlist);
        spriteFrameCache.addSpriteFrames(s_grossini_grayPlist);
        spriteFrameCache.addSpriteFrames(s_grossini_bluePlist);

        //
        // create animation "dance"
        //
        var animFrames = [];
        var frame;
        var str = "";
        for (var i = 1; i < 15; i++) {
            str = "grossini_dance_" + (i < 10 ? ("0" + i) : i) + ".png";
            frame = spriteFrameCache.getSpriteFrame(str);
            animFrames.push(frame);
        }

        var animation = cc.Animation.create(animFrames, 0.2);

        // Add an animation to the Cache
        cc.AnimationCache.getInstance().addAnimation(animation, "dance");

        //
        // create animation "dance gray"
        //
        animFrames = [];
        for (i = 1; i < 15; i++) {
            str = "grossini_dance_gray_" + (i < 10 ? ("0" + i) : i) + ".png";
            frame = spriteFrameCache.getSpriteFrame(str);
            animFrames.push(frame);
        }

        animation = cc.Animation.create(animFrames, 0.2);

        // Add an animation to the Cache
        cc.AnimationCache.getInstance().addAnimation(animation, "dance_gray");

        //
        // create animation "dance blue"
        //
        animFrames = [];
        for (i = 1; i < 4; i++) {
            str = "grossini_blue_0" + i + ".png";
            frame = spriteFrameCache.getSpriteFrame(str);
            animFrames.push(frame);
        }

        animation = cc.Animation.create(animFrames, 0.2);

        // Add an animation to the Cache
        cc.AnimationCache.getInstance().addAnimation(animation, "dance_blue");

        var animCache = cc.AnimationCache.getInstance();

        var normal = animCache.getAnimation("dance");
        normal.setRestoreOriginalFrame(true);
        var dance_grey = animCache.getAnimation("dance_gray");
        dance_grey.setRestoreOriginalFrame(true);
        var dance_blue = animCache.getAnimation("dance_blue");
        dance_blue.setRestoreOriginalFrame(true);

        var animN = cc.Animate.create(normal);
        var animG = cc.Animate.create(dance_grey);
        var animB = cc.Animate.create(dance_blue);

        var seq = cc.Sequence.create(animN, animG, animB);

        frame = spriteFrameCache.getSpriteFrame("grossini_dance_01.png");
        var grossini = cc.Sprite.createWithSpriteFrame( frame );

        grossini.setPosition(cc.p(winSize.width / 2, winSize.height / 2));
        this.addChild(grossini);

        // run the animation
        grossini.runAction(seq);
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

    init:function() {
        this._super();
        this._node = cc.Node.create();
        this.addChild(this._node, 0, 0);

        this._sprite1 = cc.Sprite.create(s_piece, cc.rect(128, 0, 64, 64));
        this._sprite1.setPosition(cc.p(100, 160));
        this._node.addChild(this._sprite1, -6, 1);

        this._sprite2 = cc.Sprite.create(s_piece, cc.rect(128, 0, 64, 64));
        this._sprite2.setPosition(cc.p(164, 160));
        this._node.addChild(this._sprite2, -6, 2);

        this._sprite4 = cc.Sprite.create(s_piece, cc.rect(128, 0, 64, 64));
        this._sprite4.setPosition(cc.p(292, 160));
        this._node.addChild(this._sprite4, -3, 4);

        this._sprite3 = cc.Sprite.create(s_piece, cc.rect(128, 0, 64, 64));
        this._sprite3.setPosition(cc.p(228, 160));
        this._node.addChild(this._sprite3, -4, 3);

        this._sprite5 = cc.Sprite.create(s_piece, cc.rect(128, 0, 64, 64));
        this._sprite5.setPosition(cc.p(356, 160));
        this._node.addChild(this._sprite5, -3, 5);

        this.schedule(this.reorderSprite);
    },

    reorderSprite:function (dt) {
        this.unschedule(this.reorderSprite);

        cc.log("Before reorder--");

        var i = 0;
        var child;
        var nodeChildren = this._node.getChildren();
        for (i = 0; i < nodeChildren.length; i++) {
            child = nodeChildren[i];
            cc.log("tag:" + child.getTag() + "  z: " + child.getZOrder());
        }

        //z-4
        this._node.reorderChild(this._node.getChildren()[0], -6);
        this._node.sortAllChildren();

        cc.log("After reorder--");
        nodeChildren = this._node.getChildren();
        for (i = 0; i < nodeChildren.length; i++) {
            child = nodeChildren[i];
            cc.log("tag:" + child.getTag() + "  z: " +
                child.getZOrder());
        }
    }
});

var SpriteBatchNodeReorderSameIndex = SpriteTestDemo.extend({
    _batchNode:null,
    _sprite1:null,
    _sprite2:null,
    _sprite3:null,
    _sprite4:null,
    _sprite5:null,

    _title:"SpriteBatchNodeReorder same index",
    _subtitle:"tag order in console should be 2,3,4,5,1",

    init:function() {
        this._super();
        this._batchNode = cc.SpriteBatchNode.create(s_piece, 15);
        this.addChild(this._batchNode, 1, 0);

        this._sprite1 = cc.Sprite.createWithTexture(this._batchNode.getTexture(), cc.rect(128, 0, 64, 64));
        this._sprite1.setPosition(cc.p(100, 160));
        this._batchNode.addChild(this._sprite1, 3, 1);

        this._sprite2 = cc.Sprite.createWithTexture(this._batchNode.getTexture(), cc.rect(128, 0, 64, 64));
        this._sprite2.setPosition(cc.p(164, 160));
        this._batchNode.addChild(this._sprite2, 4, 2);

        this._sprite3 = cc.Sprite.createWithTexture(this._batchNode.getTexture(), cc.rect(128, 0, 64, 64));
        this._sprite3.setPosition(cc.p(228, 160));
        this._batchNode.addChild(this._sprite3, 4, 3);

        this._sprite4 = cc.Sprite.createWithTexture(this._batchNode.getTexture(), cc.rect(128, 0, 64, 64));
        this._sprite4.setPosition(cc.p(292, 160));
        this._batchNode.addChild(this._sprite4, 5, 4);

        this._sprite5 = cc.Sprite.createWithTexture(this._batchNode.getTexture(), cc.rect(128, 0, 64, 64));
        this._sprite5.setPosition(cc.p(356, 160));
        this._batchNode.addChild(this._sprite5, 6, 5);

        this.scheduleOnce(this.reorderSprite, 2);
    },

    reorderSprite:function (dt) {
        this._batchNode.reorderChild(this._sprite4, 4);
        this._batchNode.reorderChild(this._sprite5, 4);
        this._batchNode.reorderChild(this._sprite1, 4);

        this._batchNode.sortAllChildren();

        var descendants = this._batchNode.getDescendants();

        for (var i = 0; i < descendants.length; i++) {
            var child = descendants[i];
            cc.log("tag:" + child.getTag());
        }
    }
});

var SpriteBatchNodeReorderOneChild = SpriteTestDemo.extend({
    _batchNode:null,
    _reoderSprite:null,

    _title:"SpriteBatchNode reorder 1 child",

    init:function() {
        this._super();

        spriteFrameCache.addSpriteFrames(s_ghostsPlist);
        //
        // SpriteBatchNode: 3 levels of children
        //
        var aParent = cc.SpriteBatchNode.create(s_ghosts);

        this._batchNode = aParent;
        //[[aParent texture] generateMipmap];
        this.addChild(aParent);

        // parent
        var l1 = cc.Sprite.createWithSpriteFrameName("father.gif");
        l1.setPosition(cc.p(winSize.width / 2, winSize.height / 2));

        aParent.addChild(l1);
        var l1Size = l1.getContentSize();

        // child left
        var l2a = cc.Sprite.createWithSpriteFrameName("sister1.gif");
        l2a.setPosition(cc.p(-10 + l1Size.width / 2, 0 + l1Size.height / 2));

        l1.addChild(l2a, 1);
        var l2aSize = l2a.getContentSize();

        // child right
        var l2b = cc.Sprite.createWithSpriteFrameName("sister2.gif");
        l2b.setPosition(cc.p(+50 + l1Size.width / 2, 0 + l1Size.height / 2));

        l1.addChild(l2b, 2);
        var l2bSize = l2a.getContentSize();

        // child left bottom
        var l3a1 = cc.Sprite.createWithSpriteFrameName("child1.gif");
        l3a1.setScale(0.45);
        l3a1.setPosition(cc.p(0 + l2aSize.width / 2, -50 + l2aSize.height / 2));
        l2a.addChild(l3a1, 1);

        // child left top
        var l3a2 = cc.Sprite.createWithSpriteFrameName("child1.gif");
        l3a2.setScale(0.45);
        l3a2.setPosition(cc.p(0 + l2aSize.width / 2, +50 + l2aSize.height / 2));
        l2a.addChild(l3a2, 2);

        this._reoderSprite = l2a;

        // child right bottom
        var l3b1 = cc.Sprite.createWithSpriteFrameName("child1.gif");
        l3b1.setScale(0.45);
        l3b1.setFlipY(true);
        l3b1.setPosition(cc.p(0 + l2bSize.width / 2, -50 + l2bSize.height / 2));
        l2b.addChild(l3b1);

        // child right top
        var l3b2 = cc.Sprite.createWithSpriteFrameName("child1.gif");
        l3b2.setScale(0.45);
        l3b2.setFlipY(true);
        l3b2.setPosition(cc.p(0 + l2bSize.width / 2, +50 + l2bSize.height / 2));
        l2b.addChild(l3b2);

        this.scheduleOnce(this.reorderSprite, 2.0);
    },

    reorderSprite:function (dt) {
        this._reoderSprite.getParent().reorderChild(this._reoderSprite, -1);

        this._batchNode.sortAllChildren();
        //cc.Sprite* child;
        //CCARRAY_FOREACH(batchNode.descendants,child) NSLog(@"tag %i",child.tag);
    }
});

var SpriteBatchNodeSkewNegativeScaleChildren = SpriteTestDemo.extend({
    _title:"SpriteBatchNode + children + skew",
    _subtitle:"SpriteBatchNode skew + negative scale with children",

    init:function() {
        this._super();

        var cache = spriteFrameCache;
        cache.addSpriteFrames(s_grossiniPlist);
        cache.addSpriteFrames(s_grossini_grayPlist, s_grossini_gray);

        var spritebatch = cc.SpriteBatchNode.create(s_grossini);
        this.addChild(spritebatch);

        for (var i = 0; i < 2; i++) {
            var sprite = cc.Sprite.createWithSpriteFrameName("grossini_dance_01.png");
            sprite.setPosition(cc.p(winSize.width / 4 * (i + 1), winSize.height / 2));

            // Skew
            var skewX = cc.SkewBy.create(2, 45, 0);
            var skewX_back = skewX.reverse();
            var skewY = cc.SkewBy.create(2, 0, 45);
            var skewY_back = skewY.reverse();

            if (i == 1) {
                sprite.setScale(-1.0);
            }

            var seq_skew = cc.Sequence.create(skewX, skewX_back, skewY, skewY_back);
            sprite.runAction(cc.RepeatForever.create(seq_skew));

            var child1 = cc.Sprite.createWithSpriteFrameName("grossini_dance_01.png");
            child1.setPosition(cc.p(sprite.getContentSize().width / 2.0, sprite.getContentSize().height / 2.0));

            child1.setScale(0.8);

            sprite.addChild(child1);

            spritebatch.addChild(sprite, i);
        }
    }
});

var SpriteSkewNegativeScaleChildren = SpriteTestDemo.extend({
    _title:"Sprite + children + skew",
    _subtitle:"Sprite skew + negative scale with children",

    init:function() {
        this._super();

        var cache = spriteFrameCache;
        cache.addSpriteFrames(s_grossiniPlist);
        cache.addSpriteFrames(s_grossini_grayPlist, s_grossini_gray);

        var parent = cc.Node.create();
        this.addChild(parent);

        for (var i = 0; i < 2; i++) {
            var sprite = cc.Sprite.createWithSpriteFrameName("grossini_dance_01.png");
            sprite.setPosition(cc.p(winSize.width / 4 * (i + 1), winSize.height / 2));

            // Skew
            var skewX = cc.SkewBy.create(2, 45, 0);
            var skewX_back = skewX.reverse();
            var skewY = cc.SkewBy.create(2, 0, 45);
            var skewY_back = skewY.reverse();

            if (i == 1) {
                sprite.setScale(-1.0);
            }

            var seq_skew = cc.Sequence.create(skewX, skewX_back, skewY, skewY_back);
            sprite.runAction(cc.RepeatForever.create(seq_skew));

            var child1 = cc.Sprite.createWithSpriteFrameName("grossini_dance_01.png");
            child1.setPosition(cc.p(sprite.getContentSize().width / 2.0, sprite.getContentSize().height / 2.0));

            sprite.addChild(child1);
            child1.setScale(0.8);
            parent.addChild(sprite, i);
        }
    }
});

var DoubleSprite = cc.Sprite.extend({
    HD:false,
    initWithTexture:function (texture, rect) {
        if (this._super(texture, rect)) {
            //var resolutionType = texture.getResolutionType();
            //this.HD = ( resolutionType == cc.kCCResolutioniPhoneRetinaDisplay || resolutionType == kCCResolutioniPadRetinaDisplay );
            return true;
        }
        return false;
    },

    setContentSize:function (size) {
        var newSize = cc.size(size.width, size.height);
        // If Retina Display and Texture is in HD then scale the vertex rect
        if (cc.CONTENT_SCALE_FACTOR() == 2 && !this.HD) {
            newSize.width *= 2;
            newSize.height *= 2;
        }
        this._super(newSize);
    },

    setVertexRect:function (rect) {
        // If Retina Display and Texture is in HD then scale the vertex rect
        if (cc.CONTENT_SCALE_FACTOR() == 2 && !this.HD) {
            rect.size.width *= 2;
            rect.size.height *= 2;
        }
        this._super(rect);
    }
});

DoubleSprite.create = function (fileName) {
    var pSp = new DoubleSprite();
    pSp.initWithFile(fileName);
    return pSp;
};

var SpriteDoubleResolution = SpriteTestDemo.extend({

    _title:"Sprite Double resolution",
    _subtitle:"Retina Display. SD (left) should be equal to HD (right)",

    init:function() {
        this._super();

        //
        // LEFT: SD sprite
        //
        // there is no HD resolution file of grossini_dance_08.
        var spriteSD = DoubleSprite.create(s_grossiniDance08);
        this.addChild(spriteSD);
        spriteSD.setPosition(cc.p(winSize.width / 4, winSize.height / 2));

        var child1_left = DoubleSprite.create(s_grossiniDance08);
        spriteSD.addChild(child1_left);
        child1_left.setPosition(cc.p(-30, 0));

        var child1_right = cc.Sprite.create(s_pathGrossini);
        spriteSD.addChild(child1_right);
        child1_left.setPosition(cc.p(spriteSD.getContentSize().height, 0));

        //
        // RIGHT: HD sprite
        //
        // there is an HD version of grossini.png
        var spriteHD = cc.Sprite.create(s_pathGrossini);
        this.addChild(spriteHD);
        spriteHD.setPosition(cc.p(winSize.width / 4 * 3, winSize.height / 2));

        var child2_left = DoubleSprite.create(s_grossiniDance08);
        spriteHD.addChild(child2_left);
        child2_left.setPosition(cc.p(-30, 0));

        var child2_right = cc.Sprite.create(s_pathGrossini);
        spriteHD.addChild(child2_right);
        child2_left.setPosition(cc.p(spriteHD.getContentSize().height, 0));


        // Actions
        var scale = cc.ScaleBy.create(2, 0.5);
        var scale_back = scale.reverse();
        var seq = cc.Sequence.create(scale, scale_back);

        var seq_copy = seq.copy();

        spriteSD.runAction(seq);
        spriteHD.runAction(seq_copy);
    }
});

var AnimationCacheFile = SpriteTestDemo.extend({

    _title:"AnimationCache - Load file",
    _subtitle:"Sprite should be animated",

    init:function () {
        this._super();
        var frameCache = spriteFrameCache;
        frameCache.addSpriteFrames(s_grossiniPlist);
        frameCache.addSpriteFrames(s_grossini_grayPlist);
        frameCache.addSpriteFrames(s_grossini_bluePlist);

        // Purge previously loaded animation
        cc.AnimationCache.purgeSharedAnimationCache();
        var animCache = cc.AnimationCache.getInstance();

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

        var animN = cc.Animate.create(normal);
        var animG = cc.Animate.create(dance_grey);
        var animB = cc.Animate.create(dance_blue);

        var seq = cc.Sequence.create(animN, animG, animB);

        // create an sprite with frame name
        // texture-less sprites are not supported
        var grossini = cc.Sprite.createWithSpriteFrameName("grossini_dance_01.png");

        grossini.setPosition(cc.p(winSize.width / 2, winSize.height / 2));
        this.addChild(grossini);

        // run the animation
        grossini.runAction(seq);
    }
});

var SpriteBatchBug1217 = SpriteTestDemo.extend({

    _title:"SpriteBatch - Bug 1217",
    _subtitle:"Adding big family to spritebatch. You shall see 3 heads",

    init:function() {
        this._super();
        var bn = cc.SpriteBatchNode.create(s_grossini_dance_atlas, 15);

        var s1 = cc.Sprite.createWithTexture(bn.getTexture(), cc.rect(0, 0, 57, 57));
        var s2 = cc.Sprite.createWithTexture(bn.getTexture(), cc.rect(0, 0, 57, 57));
        var s3 = cc.Sprite.createWithTexture(bn.getTexture(), cc.rect(0, 0, 57, 57));

        s1.setColor(cc.c3b(255, 0, 0));
        s2.setColor(cc.c3b(0, 255, 0));
        s3.setColor(cc.c3b(0, 0, 255));

        s1.setPosition(cc.p(20, 200));
        s2.setPosition(cc.p(100, 0));
        s3.setPosition(cc.p(100, 0));

        bn.setPosition(cc.p(0, 0));

        //!!!!!
        s1.addChild(s2);
        s2.addChild(s3);
        bn.addChild(s1);

        this.addChild(bn);
    }
});

var SpriteTestScene = TestScene.extend({
    runThisTest:function () {
        sceneIdx = -1;
        MAX_LAYER = 48;
        var layer = nextSpriteTest();
        this.addChild(layer);

        director.replaceScene(this);
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
    SpriteBatchNodeReorder,
    SpriteBatchNodeReorderIssue744,
    SpriteBatchNodeReorderIssue766,
    SpriteBatchNodeReorderIssue767,
    SpriteZVertex,
    SpriteBatchNodeZVertex,
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
    SpriteNilTexture,
    SpriteSubclass,
    AnimationCache,
    SpriteOffsetAnchorSkew,
    SpriteBatchNodeOffsetAnchorSkew,
    SpriteOffsetAnchorSkewScale,
    SpriteBatchNodeOffsetAnchorSkewScale,
    SpriteOffsetAnchorFlip,
    SpriteBatchNodeOffsetAnchorFlip,
    SpriteBatchNodeReorderSameIndex,
    SpriteBatchNodeReorderOneChild,
    NodeSort,
    SpriteSkewNegativeScaleChildren,
    SpriteBatchNodeSkewNegativeScaleChildren,
    SpriteDoubleResolution,
    SpriteBatchBug1217,
    AnimationCacheFile
];

var nextSpriteTest = function () {
    sceneIdx++;
    sceneIdx = sceneIdx % arrayOfSpriteTest.length;

    return new arrayOfSpriteTest[sceneIdx]();
};
var previousSpriteTest = function () {
    sceneIdx--;
    if (sceneIdx < 0)
        sceneIdx += arrayOfSpriteTest.length;

    return new arrayOfSpriteTest[sceneIdx]();
};
var restartSpriteTest = function () {
    return new arrayOfSpriteTest[sceneIdx]();
};

