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

// globals
var director = null;
var winSize = null;

var TestScene = cc.Scene.extend({
    ctor:function (bPortrait) {
        cc.associateWithNative( this, cc.Scene );
        // this._super();
        this.init();
    },

    init:function() {
        this._super();
    },

    // callbacks
    onEnter:function () {
        this._super();
        var label = cc.LabelTTF.create("MainMenu", "Arial", 20);
        var menuItem = cc.MenuItemLabel.create(label, this, this.onMainMenuCallback);

        var menu = cc.Menu.create(menuItem);
        log(menu.setPosition);
        menu.setPosition(cc.p(0,0));
        menuItem.setPosition(cc.p(winSize.width - 50, 25));

        this.addChild(menu, 1);
    },
    onMainMenuCallback:function () {
        var scene = cc.Scene.create();
        var layer = new TestController();
        scene.addChild(layer);
        director.replaceScene(scene);
    },

    runThisTest:function () {
        // override me
    }

});

//Controller stuff
var LINE_SPACE = 40;
var curPos = cc.p(0,0);

var TestController = cc.Layer.extend({
    _itemMenu:null,
    _beginPos:0,
    isMouseDown:false,
    ctor:function () {
        cc.associateWithNative( this, cc.Layer );
        this.init();
    },

    init:function() {
        if( this._super() ) {

            // globals
            director = cc.Director.getInstance();
            winSize = director.getWinSize();

            // add close menu
            var closeItem = cc.MenuItemImage.create(s_pathClose, s_pathClose, this, this.onCloseCallback);
            var menu = cc.Menu.create(closeItem);//pmenu is just a holder for the close button
            menu.setPosition(cc.p(0,0));
            closeItem.setPosition(cc.p(winSize.width - 30, winSize.height - 30));

            // add menu items for tests
            this._itemMenu = cc.Menu.create();//item menu is where all the label goes, and the one gets scrolled

            for (var i = 0, len = testNames.length; i < len; i++) {
                var label = cc.LabelTTF.create(testNames[i].title, "Arial", 24);
                var menuItem = cc.MenuItemLabel.create(label, this, this.onMenuCallback);
                this._itemMenu.addChild(menuItem, i + 10000);
                menuItem.setPosition(cc.p(winSize.width / 2, (winSize.height - (i + 1) * LINE_SPACE)));
            }

            this._itemMenu.setContentSize(cc.size(winSize.width, (testNames.length + 1) * LINE_SPACE));
            this._itemMenu.setPosition(curPos);
            this.addChild(this._itemMenu);
            this.addChild(menu, 1);

            var t = cc.config.deviceType;
            if( t == 'browser' )  {
                this.setTouchEnabled(true);
                // this.setKeyboardEnabled(true);
            } else if( t == 'desktop' ) {
                this.setMouseEnabled(true);
            } else if( t == 'mobile' ) {
                this.setTouchEnabled(true);
            }
        }
    },
    onMenuCallback:function (sender) {
        var idx = sender.getZOrder() - 10000;
        // get the userdata, it's the index of the menu item clicked
        // create the test scene and run it
        var scene = testNames[idx].testScene();
        if (scene) {
            scene.runThisTest();
        }
    },
    onCloseCallback:function () {
        history.go(-1);
    },

    onTouchesBegan:function (touches, event) {
        if (!this.isMouseDown) {
            //this._beginPos = cc.p(touches[0].getLocation().x, touches[0].getLocation().y);
            this._beginPos = touches[0].getLocation().y;
        }
        this.isMouseDown = true;
    },
    onTouchesMoved:function (touches, event) {
        if (this.isMouseDown) {
            var touchLocation = touches[0].getLocation().y;
            var nMoveY = touchLocation - this._beginPos;
            curPos = this._itemMenu.getPosition();

            var nextPos = cc.p(curPos.x, curPos.y + nMoveY);
            if (nextPos.y < 0.0) {
                this._itemMenu.setPosition(cc.p(0,0));
                return;
            }

            if (nextPos.y > ((testNames.length + 1) * LINE_SPACE - winSize.height)) {
                this._itemMenu.setPosition(cc.p(0, ((testNames.length + 1) * LINE_SPACE - winSize.height)));
                return;
            }
            this._itemMenu.setPosition(nextPos);
            this._beginPos = touchLocation;
            curPos = nextPos;
        }
    },
    
    onTouchesEnded:function () {
        this.isMouseDown = false;
    },

    onMouseDragged : function( event ) {
        var delta = event.getDelta();
        var current = this._itemMenu.getPosition();
        this._itemMenu.setPosition( cc.p( current.x, current.y + delta.y ) );
        return true;
    }
});

var testNames = [
    //"Accelerometer",
    {
        title:"ActionManagerTest",
        testScene:function () {
            return new ActionManagerTestScene();
        }
    },
    {
        title:"ActionsTest",
        testScene:function () {
            return new ActionsTestScene();
        }
    },
    {
        title:"Box2DTest",
        testScene:function () {
            return new Box2DTestScene();
        }
    },
    //"Box2dTestBed",
    //"BugsTest",
    //"ChipmunkTest",
    {
        title:"ClickAndMoveTest",
        testScene:function () {
            return new ClickAndMoveTestScene();
        }
    },
    {
        title:"CocosDenshionTest",
        testScene:function () {
            return new CocosDenshionTestScene();
        }
    },
    {
        title:"CocosNodeTest",
        testScene:function () {
            return new CocosNodeTestScene();
        }
    },
    {
        title:"CurrentLanguageTest",
        testScene:function () {
            return new CurrentLanguageTestScene();
        }
    },
    //"CurlTest",
    {
        title:"DrawPrimitivesTest",
        testScene:function () {
            return new DrawPrimitivesTestScene();
        }
    },
    {
        title:"EaseActionsTest",
        testScene:function () {
            return new EaseActionsTestScene();
        }
    },
    {
        title:"ExtensionsTest",
        testScene:function () {
            return new ExtensionsTestScene();
        }
    },
    //"EffectsTest",
    //"EffectAdvancedTest",
    //"ExtensionsTest",
    {
        title:"FontTest",
        testScene:function () {
            return new FontTestScene();
        }
    },
    //"HiResTest",
    {
        title:"IntervalTest",
        testScene:function () {
            return new IntervalTestScene();
        }
    },
    //"KeyboardTest",
    {
        title:"LabelTest",
        testScene:function () {
            return new LabelTestScene();
        }
    },
    {
        title:"LayerTest",
        testScene:function () {
            return new LayerTestScene();
        }
    },
    {
        title:"MenuTest",
        testScene:function () {
            return new MenuTestScene();
        }
    },
    {
        title:"MultiTouchTest",
        testScene:function () {
            return new MultiTouchTestScene();
        }
    },
    //"MotionStreakTest",
    {
        title:"ParallaxTest",
        testScene:function () {
            return new ParallaxTestScene();
        }
    },
    {
        title:"ParticleTest",
        testScene:function () {
            return new ParticleTestScene();
        }
    },
    {
        title:"PerformanceTest",
        testScene:function () {
            return new PerformanceTestScene();
        }
    },
    {
        title:"ProgressActionsTest",
        testScene:function () {
            return new ProgressActionsTestScene();
        }
    },
    //"RenderTextureTest",
    {
        title:"RotateWorldTest",
        testScene:function () {
            return new RotateWorldTestScene();
        }
    },
    {
        title:"SceneTest",
        testScene:function () {
            return new SceneTestScene();
        }
    },
    {
        title:"SchedulerTest",
        testScene:function () {
            return new SchedulerTestScene();
        }
    },
    {
        title:"SpriteTest",
        testScene:function () {
            return new SpriteTestScene();
        }
    },
    {
        title:"TextInputTest",
        testScene:function () {
            return new TextInputTestScene();
        }
    },
    //"Texture2DTest",
    {
        title:"TextureCacheTest",
        testScene:function () {
            return new TextureCacheTestScene();
        }
    },
    {
        title:"TileMapTest",
        testScene:function () {
            return new TileMapTestScene();
        }
    },
    {
        title:"TouchesTest",
        testScene:function () {
            return new TouchesTestScene();
        }
    },
    {
        title:"TransitionsTest",
        testScene:function () {
            return new TransitionsTestScene();
        }
    }
    //"UserDefaultTest",
    //"ZwoptexTest",
];
