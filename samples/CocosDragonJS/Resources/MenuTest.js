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


var TAG_MENU = 77771;
var TAG_MENU0 = 77770;
var TAG_MENU1 = 77771;


//------------------------------------------------------------------
//
// LayerMainMenu
//
//------------------------------------------------------------------
var LayerMainMenu = cc.Layer.extend({
    ctor:function() {
        cc.associateWithNative( this, cc.Layer );
        this.init();
    },
    init:function () {
        this._super();
        cc.MenuItemFont.setFontSize(30);
        cc.MenuItemFont.setFontName("Courier New");

        var t = cc.config.deviceType;
        if( t == 'browser' )  {
            this.setTouchEnabled(true);
            // this.setKeyboardEnabled(true);
        } else if( t == 'desktop' ) {
            this.setMouseEnabled(true);
        } else if( t == 'mobile' ) {
            this.setTouchEnabled(true);
        }

        // Font Item

        var spriteNormal = cc.Sprite.create(s_menuItem, cc.rect(0, 23 * 2, 115, 23));
        var spriteSelected = cc.Sprite.create(s_menuItem, cc.rect(0, 23, 115, 23));
        var spriteDisabled = cc.Sprite.create(s_menuItem, cc.rect(0, 0, 115, 23));

        var item1 = cc.MenuItemSprite.create(spriteNormal, spriteSelected, spriteDisabled, this, this.onMenuCallback);

        // Image Item
        var item2 = cc.MenuItemImage.create(s_sendScore, s_pressSendScore, this, this.onMenuCallback2);

        // Label Item (LabelAtlas)
        var labelAtlas = cc.LabelAtlas.create("0123456789", s_fpsImages, 16, 24, '.'.charCodeAt(0));
        var item3 = cc.MenuItemLabel.create(labelAtlas, this, this.onMenuCallbackDisabled);
        item3.setDisabledColor(cc.c3b(32, 32, 64));
        item3.setColor(cc.c3b(200, 200, 255));

        // Font Item
        var item4 = cc.MenuItemFont.create("I toggle enable items", this, this.onMenuCallbackEnabled);

        item4.setFontSize(20);
        cc.MenuItemFont.setFontName("Marker Felt");

        // Label Item (CCLabelBMFont)
        var label = cc.LabelBMFont.create("configuration", s_bitmapFontTest3_fnt);
        var item5 = cc.MenuItemLabel.create(label, this, this.onMenuCallbackConfig);

        // Testing issue #500
        item5.setScale(0.8);

        // Font Item
        var item6 = cc.MenuItemFont.create("Quit", this, this.onQuit);

        var color_action = cc.TintBy.create(0.5, 0, -255, -255);
        var color_back = color_action.reverse();
        var seq = cc.Sequence.create(color_action, color_back);
        item6.runAction(cc.RepeatForever.create(seq));

        var menu = cc.Menu.create(item1, item2, item3, item4, item5, item6);
        menu.alignItemsVertically();

        // elastic effect
        var s = director.getWinSize();

        var child;
        var array = menu.getChildren();
        for (var i = 0; i < array.length; i++) {
            if (array[i] === null)
                break;

            child = array[i];

            var dstPoint = child.getPosition();
            var offset = (s.width / 2 + 50);
            if (i % 2 === 0)
                offset = -offset;

            child.setPosition(cc.p(dstPoint.x + offset, dstPoint.y));
            child.runAction(
                cc.EaseElasticOut.create(cc.MoveBy.create(2, cc.p(dstPoint.x - offset, 0)), 0.35)
            );
        }
        this._disabledItem = item3;
        this._disabledItem.setEnabled(false);

        this.addChild(menu);
    },
    registerWithTouchDispatcher:function () {
        director.getTouchDispatcher().addTargetedDelegate(this, cc.MENU_HANDLER_PRIORITY + 1, true);
    },
    onTouchBegan:function () {
        return true;
    },
    onMenuCallback:function (sender) {
        var scene = cc.Scene.create();
        var layer = new MenuLayer2();
        scene.addChild( layer );
        director.pushScene( scene );
    },
    onMenuCallbackConfig:function (sender) {
        var scene = cc.Scene.create();
        var layer = new MenuLayer4();
        scene.addChild( layer );
        director.pushScene( scene );
    },
    onAllowTouches:function (dt) {
        director.getTouchDispatcher().setPriority(cc.MENU_HANDLER_PRIORITY + 1, this);
        this.unscheduleAllSelectors();
        cc.log("Touches allowed again!");
    },
    onMenuCallbackDisabled:function (sender) {
        // hijack all touch events for 5 seconds
        director.getTouchDispatcher().setPriority(cc.MENU_HANDLER_PRIORITY - 1, this);
        this.schedule(this.allowTouches, 5.0);
        cc.log("TOUCHES DISABLED FOR 5 SECONDS");
    },
    onMenuCallbackEnabled:function (sender) {
        this._disabledItem.setEnabled(!this._disabledItem.isEnabled());
    },
    onMenuCallback2:function (sender) {
        var scene = cc.Scene.create();
        var layer = new MenuLayer3();
        scene.addChild( layer );
        director.pushScene( scene );
    },
    onQuit:function (sender) {
        cc.log("Quit called");
    }
});

//------------------------------------------------------------------
//
// MenuLayer2
//
//------------------------------------------------------------------
var MenuLayer2 = cc.Layer.extend({
    ctor:function() {
        cc.associateWithNative( this, cc.Layer );
        this.init();
    },
    init:function () {
        this._super();
        for (var i = 0; i < 2; i++) {
            var item1 = cc.MenuItemImage.create(s_playNormal, s_playSelect, this, this.onMenuCallback);
            var item2 = cc.MenuItemImage.create(s_highNormal, s_highSelect, this, this.onMenuCallbackOpacity);
            var item3 = cc.MenuItemImage.create(s_aboutNormal, s_aboutSelect, this, this.onMenuCallbackAlign);
            item1.setScaleX(1.5);
            item2.setScaleX(0.5);
            item3.setScaleX(0.5);
            var menu = cc.Menu.create(item1, item2, item3);
            menu.setTag(TAG_MENU);
            this.addChild(menu, 0, 100 + i);
            this._centeredMenu = menu.getPosition();
        }
        this._alignedH = true;
        this.alignMenuH();
    },
    alignMenuH:function () {
        var p;
        for (var i = 0; i < 2; i++) {
            var menu = this.getChildByTag(100 + i);
            menu.setPosition(this._centeredMenu);
            if (i === 0) {
                menu.alignItemsHorizontally();
                p = menu.getPosition();
                menu.setPosition(cc.pAdd(p, cc.p(0, 30)));
            }
            else {
                menu.alignItemsHorizontallyWithPadding(40);
                p = menu.getPosition();
                menu.setPosition(cc.pSub(p, cc.p(0, 30)));
            }
        }
    },
    alignMenusV:function () {
        var p;
        for (var i = 0; i < 2; i++) {
            var menu = this.getChildByTag(100 + i);
            menu.setPosition(this._centeredMenu);
            if (i === 0) {
                menu.alignItemsVertically();
                p = menu.getPosition();
                menu.setPosition(cc.pAdd(p, cc.p(100, 0)));
            }
            else {
                menu.alignItemsVerticallyWithPadding(40);
                p = menu.getPosition();
                menu.setPosition(cc.pSub(p, cc.p(100, 0)));
            }
        }
    },
    // callbacks
    onMenuCallback:function (sender) {
        director.popScene();
    },
    onMenuCallbackOpacity:function (sender) {
        var menu = sender.getParent();
        var opacity = menu.getOpacity();
        if (opacity == 128)
            menu.setOpacity(255);
        else
            menu.setOpacity(128);
    },
    onMenuCallbackAlign:function (sender) {
        this._alignedH = !this._alignedH;
        if (this._alignedH)
            this.alignMenuH();
        else
            this.alignMenusV();
    }
});

//------------------------------------------------------------------
//
// MenuLayer3
//
//------------------------------------------------------------------
var MenuLayer3 = cc.Layer.extend({
    ctor:function() {
        cc.associateWithNative( this, cc.Layer );
        this.init();
    },
    init:function () {
        this._super();
        cc.MenuItemFont.setFontName("Marker Felt");
        cc.MenuItemFont.setFontSize(28);

        var label = cc.LabelBMFont.create("Enable AtlasItem", s_bitmapFontTest3_fnt);
        var item1 = cc.MenuItemLabel.create(label, this, this.onMenuCallback2);
        var item2 = cc.MenuItemFont.create("--- Go Back ---", this, this.onMenuCallback);

        var spriteNormal = cc.Sprite.create(s_menuItem, cc.rect(0, 23 * 2, 115, 23));
        var spriteSelected = cc.Sprite.create(s_menuItem, cc.rect(0, 23, 115, 23));
        var spriteDisabled = cc.Sprite.create(s_menuItem, cc.rect(0, 0, 115, 23));


        var item3 = cc.MenuItemSprite.create(spriteNormal, spriteSelected, spriteDisabled, this, this.onMenuCallback3);
        this._disabledItem = item3;
        this._disabledItem.setEnabled(false);

        var menu = cc.Menu.create(item1, item2, item3);
        menu.setPosition(cc.p(0, 0));

        var s = director.getWinSize();

        item1.setPosition(cc.p(s.width / 2 - 150, s.height / 2));
        item2.setPosition(cc.p(s.width / 2 - 200, s.height / 2));
        item3.setPosition(cc.p(s.width / 2, s.height / 2 - 100));

        var jump = cc.JumpBy.create(3, cc.p(400, 0), 50, 4);
        item2.runAction(
            cc.RepeatForever.create(
                cc.Sequence.create(jump, jump.reverse())
            )
        );
        var spin1 = cc.RotateBy.create(3, 360);
        var spin2 = spin1.copy();
        var spin3 = spin1.copy();

        item1.runAction(cc.RepeatForever.create(spin1));
        item2.runAction(cc.RepeatForever.create(spin2));
        item3.runAction(cc.RepeatForever.create(spin3));

        this.addChild(menu);
    },
    // callbacks
    onMenuCallback:function (sender) {
        director.popScene();
    },
    onMenuCallback2:function (sender) {
        this._disabledItem.setEnabled(!this._disabledItem.isEnabled());
        this._disabledItem.stopAllActions();
    },
    onMenuCallback3:function () {
        cc.log("do something");
    }
});

var MenuLayer4 = cc.Layer.extend({
    ctor:function () {
        cc.associateWithNative( this, cc.Layer );
        this.init();
    },
    init:function () {
        this._super();
        cc.MenuItemFont.setFontName("American Typewriter");
        cc.MenuItemFont.setFontSize(18);

        var title1 = cc.MenuItemFont.create("Sound");
        title1.setEnabled(false);
        cc.MenuItemFont.setFontName("Marker Felt");
        cc.MenuItemFont.setFontSize(34);

        // you can create a ToggleItem by passing the items
        // and later setting the callback
        var item1 = cc.MenuItemToggle.create(
            cc.MenuItemFont.create("On"),
            cc.MenuItemFont.create("Off") );
        item1.setCallback( this, this.onMenuCallback );

        cc.MenuItemFont.setFontName("American Typewriter");
        cc.MenuItemFont.setFontSize(18);
        var title2 = cc.MenuItemFont.create("Music");
        title2.setEnabled(false);
        cc.MenuItemFont.setFontName("Marker Felt");
        cc.MenuItemFont.setFontSize(34);

        // or you can create a ToggleItem by passing the items
        // an the callback at the last arguments.
        var item2 = cc.MenuItemToggle.create(
            cc.MenuItemFont.create("Off"),
            cc.MenuItemFont.create("33%"),
            cc.MenuItemFont.create("66%"),
            cc.MenuItemFont.create("On"),
            this,
            this.onMenuCallback
            );

        cc.MenuItemFont.setFontName("American Typewriter");
        cc.MenuItemFont.setFontSize(18);
        var title3 = cc.MenuItemFont.create("Quality");
        title3.setEnabled(false);
        cc.MenuItemFont.setFontName("Marker Felt");
        cc.MenuItemFont.setFontSize(34);
        var item3 = cc.MenuItemToggle.create(
            cc.MenuItemFont.create("High"),
            cc.MenuItemFont.create("Low"),
            this,
            this.onMenuCallback
            );

        cc.MenuItemFont.setFontName("American Typewriter");
        cc.MenuItemFont.setFontSize(18);
        var title4 = cc.MenuItemFont.create("Orientation");
        title4.setEnabled(false);
        cc.MenuItemFont.setFontName("Marker Felt");
        cc.MenuItemFont.setFontSize(34);
        var item4 = cc.MenuItemToggle.create(
            cc.MenuItemFont.create("Landscape Left"),
            cc.MenuItemFont.create("Landscape Right"),
            cc.MenuItemFont.create("Portrait"),
            this,
            this.onMenuCallback
            );

        // you can change the one of the items by doing this
        item4.setSelectedIndex(2);

        cc.MenuItemFont.setFontName("Marker Felt");
        cc.MenuItemFont.setFontSize(34);

        var label = cc.LabelBMFont.create("go back", s_bitmapFontTest3_fnt);
        var back = cc.MenuItemLabel.create(label, this, this.onBackCallback);

        var menu = cc.Menu.create(
            title1, title2,
            item1, item2,
            title3, title4,
            item3, item4,
            back); // 9 items.

        menu.alignItemsInColumns(2, 2, 2, 2, 1);

        this.addChild(menu);
    },
    onMenuCallback:function (sender) {
        cc.log("Callback called");
    },
    onBackCallback:function (sender) {
        director.popScene();
    }
});

var MenuTestScene = TestScene.extend({
    runThisTest:function () {
        var mainLayer = new LayerMainMenu();
        this.addChild(mainLayer, 0);
        director.replaceScene(mainLayer);
    }
});
