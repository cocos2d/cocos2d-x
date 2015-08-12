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

// globals
var director = null;
var winSize = null;

var PLATFORM_JSB = 1 << 0;
var PLATFORM_HTML5 = 1 << 1;
var PLATFORM_HTML5_WEBGL = 1 << 2;
var PLATFROM_ANDROID = 1 << 3;
var PLATFROM_IOS = 1 << 4;
var PLATFORM_MAC = 1 << 5;
var PLATFORM_JSB_AND_WEBGL =  PLATFORM_JSB | PLATFORM_HTML5_WEBGL;
var PLATFORM_ALL = PLATFORM_JSB | PLATFORM_HTML5 | PLATFORM_HTML5_WEBGL | PLATFROM_ANDROID | PLATFROM_IOS;
var PLATFROM_APPLE = PLATFROM_IOS | PLATFORM_MAC;

// automation vars
var autoTestEnabled = autoTestEnabled || false;
var autoTestCurrentTestName = autoTestCurrentTestName || "N/A";

var TestScene = cc.Scene.extend({
    ctor:function (bPortrait) {
        this._super();
        this.init();

        var label = new cc.LabelTTF("Main Menu", "Arial", 20);
        var menuItem = new cc.MenuItemLabel(label, this.onMainMenuCallback, this);

        var menu = new cc.Menu(menuItem);
        menu.x = 0;
        menu.y = 0;
        menuItem.x = winSize.width - 50;
        menuItem.y = 25;

        if(!window.sideIndexBar){
            this.addChild(menu, 1);
        }
    },
    onMainMenuCallback:function () {
        var scene = new cc.Scene();
        var layer = new TestController();
        scene.addChild(layer);
        var transition = new cc.TransitionProgressRadialCCW(0.5,scene);
        director.runScene(transition);
    },

    runThisTest:function () {
        // override me
    }

});

//Controller stuff
var LINE_SPACE = 40;
var curPos = cc.p(0,0);

var TestController = cc.LayerGradient.extend({
    _itemMenu:null,
    _beginPos:0,
    isMouseDown:false,

    ctor:function() {
        this._super(cc.color(0,0,0,255), cc.color(0x46,0x82,0xB4,255));

        // globals
        director = cc.director;
        winSize = director.getWinSize();

        // add close menu
        var closeItem = new cc.MenuItemImage(s_pathClose, s_pathClose, this.onCloseCallback, this);
        closeItem.x = winSize.width - 30;
	    closeItem.y = winSize.height - 30;

        var subItem1 = new cc.MenuItemFont("Automated Test: Off");
        subItem1.fontSize = 18;
        var subItem2 = new cc.MenuItemFont("Automated Test: On");
        subItem2.fontSize = 18;

        var toggleAutoTestItem = new cc.MenuItemToggle(subItem1, subItem2);
        toggleAutoTestItem.setCallback(this.onToggleAutoTest, this);
        toggleAutoTestItem.x = winSize.width - toggleAutoTestItem.width / 2 - 10;
        toggleAutoTestItem.y = 20;
        toggleAutoTestItem.setVisible(false);
        if( autoTestEnabled )
            toggleAutoTestItem.setSelectedIndex(1);


        var menu = new cc.Menu(closeItem, toggleAutoTestItem);//pmenu is just a holder for the close button
        menu.x = 0;
	    menu.y = 0;

        // add menu items for tests
        this._itemMenu = new cc.Menu();//item menu is where all the label goes, and the one gets scrolled

        for (var i = 0, len = testNames.length; i < len; i++) {
            var label = new cc.LabelTTF(testNames[i].title, "Arial", 24);
            var menuItem = new cc.MenuItemLabel(label, this.onMenuCallback, this);
            this._itemMenu.addChild(menuItem, i + 10000);
            menuItem.x = winSize.width / 2;
	        menuItem.y = (winSize.height - (i + 1) * LINE_SPACE);

            // enable disable
            if ( !cc.sys.isNative) {
                if( 'opengl' in cc.sys.capabilities ){
                    menuItem.enabled = (testNames[i].platforms & PLATFORM_HTML5) | (testNames[i].platforms & PLATFORM_HTML5_WEBGL);
                }else{
                    menuItem.setEnabled( testNames[i].platforms & PLATFORM_HTML5 );
                }
            } else {
                if (cc.sys.os == cc.sys.OS_ANDROID) {
                    menuItem.setEnabled( testNames[i].platforms & ( PLATFORM_JSB | PLATFROM_ANDROID ) );
                } else if (cc.sys.os == cc.sys.OS_IOS) {
                    menuItem.setEnabled( testNames[i].platforms & ( PLATFORM_JSB | PLATFROM_IOS) );
                } else if (cc.sys.os == cc.sys.OS_OSX) {
                    menuItem.setEnabled( testNames[i].platforms & ( PLATFORM_JSB | PLATFORM_MAC) );
                } else {
                    menuItem.setEnabled( testNames[i].platforms & PLATFORM_JSB );
                }
            }
        }

        this._itemMenu.width = winSize.width;
	    this._itemMenu.height = (testNames.length + 1) * LINE_SPACE;
        this._itemMenu.x = curPos.x;
	    this._itemMenu.y = curPos.y;
        this.addChild(this._itemMenu);
        this.addChild(menu, 1);

        // 'browser' can use touches or mouse.
        // The benefit of using 'touches' in a browser, is that it works both with mouse events or touches events
        if ('touches' in cc.sys.capabilities)
            cc.eventManager.addListener({
                event: cc.EventListener.TOUCH_ALL_AT_ONCE,
                onTouchesMoved: function (touches, event) {
                    var target = event.getCurrentTarget();
                    var delta = touches[0].getDelta();
                    target.moveMenu(delta);
                    return true;
                }
            }, this);
        else if ('mouse' in cc.sys.capabilities) {
            cc.eventManager.addListener({
                event: cc.EventListener.MOUSE,
                onMouseMove: function (event) {
                    if(event.getButton() == cc.EventMouse.BUTTON_LEFT)
                        event.getCurrentTarget().moveMenu(event.getDelta());
                },
                onMouseScroll: function (event) {
                    var delta = cc.sys.isNative ? event.getScrollY() * 6 : -event.getScrollY();
                    event.getCurrentTarget().moveMenu({y : delta});
                    return true;
                }
            }, this);
        }
    },
    onEnter:function(){
        this._super();
	    this._itemMenu.y = TestController.YOffset;
    },
    onMenuCallback:function (sender) {
        TestController.YOffset = this._itemMenu.y;
        var idx = sender.getLocalZOrder() - 10000;
        // get the userdata, it's the index of the menu item clicked
        // create the test scene and run it

        autoTestCurrentTestName = testNames[idx].title;

        var testCase = testNames[idx];
        var res = testCase.resource || [];
        cc.LoaderScene.preload(res, function () {
            var scene = testCase.testScene();
            if (scene) {
                scene.runThisTest();
            }
        }, this);
    },
    onCloseCallback:function () {
        window.history && window.history.go(-1);
    },
    onToggleAutoTest:function() {
        autoTestEnabled = !autoTestEnabled;
    },

    moveMenu:function(delta) {
        var newY = this._itemMenu.y + delta.y;
        if (newY < 0 )
            newY = 0;

        if( newY > ((testNames.length + 1) * LINE_SPACE - winSize.height))
            newY = ((testNames.length + 1) * LINE_SPACE - winSize.height);

	    this._itemMenu.y = newY;
    }
});
TestController.YOffset = 0;
var testNames = [
    {
        title:"ActionManager Test",
        platforms: PLATFORM_ALL,
        linksrc:"src/ActionManagerTest/ActionManagerTest.js",
        testScene:function () {
            return new ActionManagerTestScene();
        }
    },
    {
        title:"Actions Test",
        platforms: PLATFORM_ALL,
        linksrc:"src/ActionsTest/ActionsTest.js",
        testScene:function () {
            return new ActionsTestScene();
        }
    },
    {
        title:"Bake Layer Test",
        platforms: PLATFORM_HTML5,
        linksrc:"src/BakeLayerTest/BakeLayerTest.js",
        testScene:function () {
            return new BakeLayerTestScene();
        }
    },
    {
        title:"BillBoard Test",
        platforms: PLATFORM_JSB,
        linksrc:"src/BillBoardTest/BillBoardTest.js",
        testScene:function () {
            return new BillBoardTestScene();
        }
    },
    {
        title:"Box2D Test",
        resource:g_box2d,
        platforms: PLATFORM_HTML5,
        linksrc:"src/Box2dTest/Box2dTest.js",
        testScene:function () {
            return new Box2DTestScene();
        }
    },
    {
        title:"Camera3D Test",
        platforms: PLATFORM_JSB,
        linksrc:"src/Camera3DTest/Camera3DTest.js",
        testScene:function () {
            return new Camera3DTestScene();
        }
    },
    {
        title:"Chipmunk Test",
        platforms: PLATFORM_ALL,
        linksrc:"src/ChipmunkTest/ChipmunkTest.js",
        testScene:function () {
            return new ChipmunkTestScene();
        }
    },
    //"BugsTest",
    {
        title:"Click and Move Test",
        platforms: PLATFORM_ALL,
        linksrc:"src/ClickAndMoveTest/ClickAndMoveTest.js",
        testScene:function () {
            return new ClickAndMoveTestScene();
        }
    },
    {
        title:"ClippingNode Test",
        platforms: PLATFORM_ALL,
        linksrc:"src/ClippingNodeTest/ClippingNodeTest.js",
        testScene:function () {
            return new ClippingNodeTestScene();
        }
    },
    {
        title:"CocosDenshion Test",
        resource:g_cocosdeshion,
        platforms: PLATFORM_ALL,
        linksrc:"src/CocosDenshionTest/CocosDenshionTest.js",
        testScene:function () {
            return new CocosDenshionTestScene();
        }
    },
    {
        title:"CocoStudio Test",
        resource:g_cocoStudio,
        platforms: PLATFORM_ALL,
        linksrc:"",
        testScene:function () {
            return new CocoStudioTestScene();
        }
    },
    {
        title:"CurrentLanguage Test",
        platforms: PLATFORM_ALL,
        linksrc:"src/CurrentLanguageTest/CurrentLanguageTest.js",
        testScene:function () {
            return new CurrentLanguageTestScene();
        }
    },
    //"CurlTest",
    {
        title:"DrawPrimitives Test",
        platforms: PLATFORM_ALL,
        linksrc:"src/DrawPrimitivesTest/DrawPrimitivesTest.js",
        testScene:function () {
            return new DrawPrimitivesTestScene();
        }
    },
    {
        title:"EaseActions Test",
        platforms: PLATFORM_ALL,
        linksrc:"src/EaseActionsTest/EaseActionsTest.js",
        testScene:function () {
            return new EaseActionsTestScene();
        }
    },
    {
        title:"Event Manager Test",
        resource:g_eventDispatcher,
        platforms: PLATFORM_ALL,
        linksrc:"src/NewEventManagerTest/NewEventManagerTest.js",
        testScene:function () {
            return new EventDispatcherTestScene();
        }
    },
    {
        title:"Event Test",
        platforms: PLATFORM_ALL,
        linksrc:"src/EventTest/EventTest.js",
        testScene:function () {
            return new EventTestScene();
        }
    },
    {
        title:"Extensions Test",
        resource:g_extensions,
        platforms: PLATFORM_ALL,
        linksrc:"",
        testScene:function () {
            return new ExtensionsTestScene();
        }
    },
    {
        title:"Effects Test",
        platforms: PLATFORM_JSB_AND_WEBGL,
        linksrc:"src/EffectsTest/EffectsTest.js",
        testScene:function () {
            return new EffectsTestScene();
        }
    },
    {
        title:"Effects Advanced Test",
        platforms: PLATFORM_JSB_AND_WEBGL,
        linksrc:"src/EffectsAdvancedTest/EffectsAdvancedTest.js",
        testScene:function () {
            return new EffectAdvanceScene();
        }
    },
    //{
    //    title:"Facebook SDK Test",
    //    platforms: PLATFROM_ANDROID | PLATFROM_IOS | PLATFORM_HTML5,
    //    linksrc:"src/FacebookTest/FacebookTestsManager.js",
    //    testScene:function () {
    //        return new FacebookTestScene();
    //    }
    //},
    {
        title:"Font Test",
        resource:g_fonts,
        platforms: PLATFORM_ALL,
        linksrc:"src/FontTest/FontTest.js",
        testScene:function () {
            return new FontTestScene();
        }
    },
    {
        title:"UI Test",
        resource:g_ui,
        platforms: PLATFORM_ALL,
        linksrc:"",
        testScene:function () {
            return new GUITestScene();
        }
    },
    //"HiResTest",
    {
        title:"Interval Test",
        platforms: PLATFORM_ALL,
        linksrc:"src/IntervalTest/IntervalTest.js",
        testScene:function () {
            return new IntervalTestScene();
        }
    },
    {
        title:"Label Test",
        resource:g_label,
        platforms: PLATFORM_ALL,
        linksrc:"src/LabelTest/LabelTest.js",
        testScene:function () {
            return new LabelTestScene();
        }
    },
    {
        title:"Layer Test",
        platforms: PLATFORM_ALL,
        linksrc:"src/LayerTest/LayerTest.js",
        testScene:function () {
            return new LayerTestScene();
        }
    },
    {
        title:"Light Test",
        platforms: PLATFORM_JSB,
        linksrc:"src/LightTest/LightTest.js",
        testScene:function () {
            return new LightTestScene();
        }
    },
    {
        title:"Loader Test",
        platforms: PLATFORM_ALL,
        linksrc:"src/LoaderTest/LoaderTest.js",
        testScene:function () {
            return new LoaderTestScene();
        }
    },
    {
        title:"MaterialSystem Test",
        platforms: PLATFORM_JSB,
        linksrc:"src/MaterialSystemTest/MaterialSystemTest.js",
        testScene:function () {
            return new MaterialSystemTestScene();
        }
    },
    {
        title:"Menu Test",
        resource:g_menu,
        platforms: PLATFORM_ALL,
        linksrc:"src/MenuTest/MenuTest.js",
        testScene:function () {
            return new MenuTestScene();
        }
    },
    {
        title:"MotionStreak Test",
        platforms: PLATFORM_JSB_AND_WEBGL,
        linksrc:"src/MotionStreakTest/MotionStreakTest.js",
        testScene:function () {
            return new MotionStreakTestScene();
        }
    },
    {
        title:"Node Test",
        platforms: PLATFORM_ALL,
        linksrc:"src/CocosNodeTest/CocosNodeTest.js",
        testScene:function () {
            return new NodeTestScene();
        }
    },
    {
        title:"OpenGL Test",
        resource:g_opengl_resources,
        platforms: PLATFORM_JSB_AND_WEBGL,
        linksrc:"src/OpenGLTest/OpenGLTest.js",
        testScene:function () {
            return new OpenGLTestScene();
        }
    },
    {
        title:"Parallax Test",
        resource:g_parallax,
        platforms: PLATFORM_ALL,
        linksrc:"src/ParallaxTest/ParallaxTest.js",
        testScene:function () {
            return new ParallaxTestScene();
        }
    },
    {
        title:"Particle3D Test",
        platforms: PLATFORM_JSB,
        testScene:function () {
            return new Particle3DTestScene();
        }
    },
    {
        title:"Particle Test",
        platforms: PLATFORM_ALL,
        linksrc:"",
        resource:g_particle,
        testScene:function () {
            return new ParticleTestScene();
        }
    },
    {
        title:"Path Tests",
        platforms: PLATFORM_ALL,
        linksrc:"src/PathTest/PathTest.js",
        testScene:function () {
            return new PathTestScene();
        }
    },
    {
        title:"Performance Test",
        platforms: PLATFORM_ALL,
        linksrc:"",
        resource:g_performace,
        testScene:function () {
            return new PerformanceTestScene();
        }
    },
    {
        title:"Physics3D Test",
        platforms: PLATFORM_JSB,
        linksrc:"src/Physics3DTest/Physics3DTest.js",
        testScene:function () {
            return new Physics3DTestScene();
        }
    },
    {
        title:"NavMesh Test",
        platforms: PLATFORM_JSB,
        linksrc:"src/NavMeshTest/NavMeshTest.js",
        testScene:function () {
            return new nextNavMeshTest();
        }
    },
    {
        title:"ProgressActions Test",
        platforms: PLATFORM_ALL,
        linksrc:"src/ProgressActionsTest/ProgressActionsTest.js",
        testScene:function () {
            return new ProgressActionsTestScene();
        }
    },
    {
        title:"Reflection Test",
        platforms: PLATFROM_ANDROID | PLATFROM_APPLE,
        linksrc:"src/ReflectionTest/ReflectionTest.js",
        testScene:function () {
            return new ReflectionTestScene();
        }
    },
    {
        title:"RenderTexture Test",
        platforms: PLATFORM_ALL,
        linksrc:"src/RenderTextureTest/RenderTextureTest.js",
        testScene:function () {
            return new RenderTextureTestScene();
        }
    },
    {
        title:"RotateWorld Test",
        platforms: PLATFORM_ALL,
        linksrc:"src/RotateWorldTest/RotateWorldTest.js",
        testScene:function () {
            return new RotateWorldTestScene();
        }
    },
    {
        title:"Scene Test",
        platforms: PLATFORM_ALL,
        linksrc:"src/SceneTest/SceneTest.js",
        testScene:function () {
            return new SceneTestScene();
        }
    },
    {
        title:"Scheduler Test",
        platforms: PLATFORM_ALL,
        linksrc:"src/SchedulerTest/SchedulerTest.js",
        testScene:function () {
            return new SchedulerTestScene();
        }
    },
    {
        title:"Spine Test",
        resource: g_spine,
        platforms: PLATFORM_ALL,
        linksrc:"src/SpineTest/SpineTest.js",
        testScene:function () {
            return new SpineTestScene();
        }
    },
    {
        title:"Sprite3D Test",
        platforms: PLATFORM_JSB,
        linksrc:"src/Sprite3DTest/Sprite3DTest.js",
        testScene:function () {
            return new Sprite3DTestScene();
        }
    },
    {
        title:"SpritePolygon Test",
        platforms: PLATFORM_JSB,
        linksrc:"src/SpritePolygonTest/SpritePolygonTest.js",
        testScene:function () {
            return new SpritePolygonTestScene();
        }
    },
    {
        title:"Sprite Test",
        resource:g_sprites,
        platforms: PLATFORM_ALL,
        linksrc:"src/SpriteTest/SpriteTest.js",
        testScene:function () {
            return new SpriteTestScene();
        }
    },
    {
        title:"Scale9Sprite Test",
        resource:g_s9s_blocks,
        platforms: PLATFORM_ALL,
        linksrc:"src/ExtensionsTest/S9SpriteTest/S9SpriteTest.js",
        testScene:function () {
            return new S9SpriteTestScene();
        }
    },
    {
        title:"Terrain Test",
        platforms: PLATFORM_JSB,
        linksrc:"src/TerrainTest/TerrainTest.js",
        testScene:function () {
            return new TerrainTestScene();
        }
    },
    {
        title:"TextInput Test",
        platforms: PLATFORM_HTML5,
        linksrc:"src/TextInputTest/TextInputTest.js",
        testScene:function () {
            return new TextInputTestScene();
        }
    },
    //"Texture2DTest",
    {
        title:"TextureCache Test",
        platforms: PLATFORM_ALL,
        linksrc:"src/TextureCacheTest/TextureCacheTest.js",
        testScene:function () {
            return new TexCacheTestScene();
        }
    },
    {
        title:"TileMap Test",
        resource:g_tilemaps,
        platforms: PLATFORM_ALL,
        linksrc:"src/TileMapTest/TileMapTest.js",
        testScene:function () {
            return new TileMapTestScene();
        }
    },
    {
        title:"Touches Test",
        resource:g_touches,
        platforms: PLATFORM_HTML5,
        linksrc:"src/TouchesTest/TouchesTest.js",
        testScene:function () {
            return new TouchesTestScene();
        }
    },
    {
        title:"Transitions Test",
        resource:g_transitions,
        platforms: PLATFORM_ALL,
        linksrc:"",
        testScene:function () {
            return new TransitionsTestScene();
        }
    },
    {
        title:"Unit Tests",
        platforms: PLATFORM_ALL,
        linksrc:"src/UnitTest/UnitTest.js",
        testScene:function () {
            return new UnitTestScene();
        }
    },
    {
        title:"Sys Tests",
        platforms: PLATFORM_ALL,
        linksrc:"src/SysTest/SysTest.js",
        testScene:function () {
            return new SysTestScene();
        }
    },
    {
        title:"cocos2d JS Presentation",
        platforms: PLATFORM_JSB,
        linksrc:"src/Presentation/Presentation.js",
        testScene:function () {
            return new PresentationScene();
        }
    },
    {
        title:"XMLHttpRequest",
        platforms: PLATFORM_ALL,
        linksrc:"src/XHRTest/XHRTest.js",
        testScene:function () {
            return new XHRTestScene();
        }
    },
    {
        title:"XMLHttpRequest send ArrayBuffer",
        platforms: PLATFORM_ALL,
        linksrc:"src/XHRTest/XHRArrayBufferTest.js",
        testScene:function () {
            return new XHRArrayBufferTestScene();
        }
    }

    //"UserDefaultTest",
    //"ZwoptexTest",
];
