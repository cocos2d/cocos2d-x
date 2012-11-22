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

var TileMapTests = [
    //function(){ return new TileMapTest();}, //not support tga format
    // function(){ return new TileMapEditTest();}, //not support tga format
    function () {
        return new TMXOrthoTest();
    }, //ok
    function () {
        return new TMXOrthoTest2();
    }, //camera bug
    function () {
        return new TMXOrthoTest3();
    }, //ok
    function () {
        return new TMXOrthoTest4();
    }, //ok
    function () {
        return new TMXReadWriteTest();
    }, //ok
    function () {
        return new TMXHexTest();
    }, //ok
    function () {
        return new TMXIsoTest();
    }, //ok
    function () {
        return new TMXIsoTest1();
    }, //ok
    function () {
        return new TMXIsoTest2();
    }, //ok
    function () {
        return new TMXUncompressedTest();
    }, //ok
    function () {
        return new TMXTilesetTest();
    }, //ok
    function () {
        return new TMXOrthoObjectsTest();
    }, //ok
    function () {
        return new TMXIsoObjectsTest();
    }, //ok
    function () {
        return new TMXResizeTest();
    }, //ok
    function () {
        return new TMXIsoZorder();
    }, //ok
    function () {
        return new TMXOrthoZorder();
    }, //ok
    //function(){ return new TMXIsoVertexZ();}, //VertexZ bug
    //function(){ return new TMXOrthoVertexZ();}, //VertexZ bug
    function () {
        return new TMXIsoMoveLayer();
    }, //ok
    function () {
        return new TMXOrthoMoveLayer();
    }, //ok
    function () {
        return new TMXTilePropertyTest();
    }, //ok
    function () {
        return new TMXOrthoFlipTest();
    }, //ok
    function () {
        return new TMXOrthoFlipRunTimeTest();
    },
    function () {
        return new TMXOrthoFromXMLTest();
    }, //ok
    function () {
        return new TMXBug987();
    }, //ok
    function () {
        return new TMXBug787();
    }, //ok
    function () {
        return new TMXGIDObjectsTest();
    }//ok
];
var tileMapIdx = -1;
function nextTileMapAction() {
    ++tileMapIdx;
    tileMapIdx = tileMapIdx % TileMapTests.length;
    return TileMapTests[tileMapIdx]();
}
function backTileMapAction() {
    --tileMapIdx;
    if (tileMapIdx < 0) {
        tileMapIdx += TileMapTests.length;
    }
    return TileMapTests[tileMapIdx]();
}
function restartTileMapAction() {
    return TileMapTests[tileMapIdx]();
}

// the class inherit from TestScene
// every .Scene each test used must inherit from TestScene,
// make sure the test have the menu item for back to main menu
var TileMapTestScene = TestScene.extend({
    runThisTest:function () {
        tileMapIdx = -1;
        this.addChild(nextTileMapAction());
        cc.Director.getInstance().replaceScene(this);
    }
});

//------------------------------------------------------------------
//
// TileDemo
//
//------------------------------------------------------------------
var TileDemo = cc.Layer.extend({
    ctor:function () {
        this.setTouchEnabled(true);
    },
    title:function () {
        return "No title";
    },
    subtitle:function () {
        return "drag the screen";
    },
    onEnter:function () {

        //this.m_label.setString(this.title().toString());
        //this.m_subtitle.setString(this.subtitle().toString());

        this._super();
        var s = cc.Director.getInstance().getWinSize();
        // add title and subtitle
        var title = this.title();
        var label = cc.LabelTTF.create(title, "Arial", 28);
        this.addChild(label, 1);
        label.setPosition(cc.p(s.width / 2, s.height - 50));

        var strSubtitle = this.subtitle();
        if (strSubtitle) {
            var l = cc.LabelTTF.create(strSubtitle, "Thonburi", 16);
            this.addChild(l, 1);
            l.setPosition(cc.p(s.width / 2, s.height - 80));
        }

        // add menu
        var item1 = cc.MenuItemImage.create(s_pathB1, s_pathB2, this, this.backCallback);
        var item2 = cc.MenuItemImage.create(s_pathR1, s_pathR2, this, this.restartCallback);
        var item3 = cc.MenuItemImage.create(s_pathF1, s_pathF2, this, this.nextCallback);

        var menu = cc.Menu.create(item1, item2, item3, null);

        menu.setPosition(cc.p(0,0));
        item1.setPosition(cc.p(s.width / 2 - 100, 30));
        item2.setPosition(cc.p(s.width / 2, 30));
        item3.setPosition(cc.p(s.width / 2 + 100, 30));

        this.addChild(menu, 1);
    },

    restartCallback:function (sender) {
        var s = new TileMapTestScene();
        s.addChild(restartTileMapAction());

        cc.Director.getInstance().replaceScene(s);
    },
    nextCallback:function (sender) {
        var s = new TileMapTestScene();
        s.addChild(nextTileMapAction());
        cc.Director.getInstance().replaceScene(s);
    },
    backCallback:function (sender) {
        var s = new TileMapTestScene();
        s.addChild(backTileMapAction());
        cc.Director.getInstance().replaceScene(s);
    },

    registerWithTouchDispatcher:function () {
        cc.Director.getInstance().getTouchDispatcher().addTargetedDelegate(this, 0, true);
    },
    onTouchBegan:function (touch, event) {
        return true;
    },
    onTouchEnded:function (touch, event) {
        this.prevLocation = null;
    },
    onTouchCancelled:function (touch, event) {
    },
    prevLocation:null,
    onTouchMoved:function (touch, event) {
        var touchLocation = touch.getLocation();

        if (!this.prevLocation) {
            this.prevLocation = cc.p(touchLocation.x, touchLocation.y);
            return;
        }
        var node = this.getChildByTag(TAG_TILE_MAP);
        var diff = cc.pSub(touchLocation, this.prevLocation);
        var currentPos = node.getPosition();

        //diff = cc.p(diff.x * node.getScaleX(),diff.y * node.getScaleY());
        var curPos = cc.pAdd(currentPos, diff);
        node.setPosition(curPos);
        this.prevLocation = cc.p(touchLocation.x, touchLocation.y);
    }
});

var TileMapTest = TileDemo.extend({
    ctor:function () {
        this._super();
        var map = cc.TileMapAtlas.create(s_tilesPng, s_levelMapTga, 16, 16);
        map.getTexture().setAntiAliasTexParameters();

        var s = map.getContentSize();
        cc.log("ContentSize: " + s.width + " " + s.height);

        map.releaseMap();

        this.addChild(map, 0, TAG_TILE_MAP);

        map.setAnchorPoint(cc.p(0, 0.5));

        var scale = cc.ScaleBy.create(4, 0.8);
        var scaleBack = scale.reverse();

        var seq = cc.Sequence.create(scale, scaleBack, null);

        map.runAction(cc.RepeatForever.create(seq));
    },
    title:function () {
        return "TileMapAtlas";
    }
});

var TileMapEditTest = TileDemo.extend({
    ctor:function () {
        this._super();
        var map = cc.TileMapAtlas.create(s_tilesPng, s_levelMapTga, 16, 16);
        // Create an Aliased Atlas
        map.getTexture().setAliasTexParameters();

        var s = map.getContentSize();
        cc.log("ContentSize: " + s.width + " " + s.height);

        // If you are not going to use the Map, you can free it now
        // [tilemap releaseMap);
        // And if you are going to use, it you can access the data with:

        this.schedule(this.updateMap, 0.2);//:@selector(updateMap:) interval:0.2f);

        this.addChild(map, 0, TAG_TILE_MAP);

        map.setAnchorPoint(cc.p(0, 0));
        map.setPosition(cc.p(-20, -200));

    },
    title:function () {
        return "Editable TileMapAtlas";
    },
    updateMap:function (dt) {
        // IMPORTANT
        //   The only limitation is that you cannot change an empty, or assign an empty tile to a tile
        //   The value 0 not rendered so don't assign or change a tile with value 0

        var tilemap = this.getChildByTag(TAG_TILE_MAP);

        // NEW since v0.7
        var c = tilemap.tileAt(cc.g(13, 21));
        c.r++;
        c.r %= 50;
        if (c.r == 0)
            c.r = 1;

        // NEW since v0.7
        tilemap.setTile(c, cc.g(13, 21));
    }
});

//------------------------------------------------------------------
//
// TMXOrthoTest
//
//------------------------------------------------------------------
var TMXOrthoTest = TileDemo.extend({
    ctor:function () {
        this._super();
        var map = cc.TMXTiledMap.create("res/TileMaps/orthogonal-test1.tmx");
        this.addChild(map, 0, TAG_TILE_MAP);

        map.runAction(cc.ScaleBy.create(2, 0.5));
    },
    title:function () {
        return "TMX Ortho test";
    }
});

//------------------------------------------------------------------
//
// TMXOrthoTest2
//
//------------------------------------------------------------------
var TMXOrthoTest2 = TileDemo.extend({
    ctor:function () {
        this._super();
        //
        // Test orthogonal with 3d camera and anti-alias textures
        //
        // it should not flicker. No artifacts should appear
        //
        var map = cc.TMXTiledMap.create("res/TileMaps/orthogonal-test2.tmx");
        this.addChild(map, 0, TAG_TILE_MAP);

        /*var x, y, z;
         map.getCamera().getEyeXYZ(x, y, z);
         map.getCamera().setEyeXYZ(x - 200, y, z + 300);*/
    },
    title:function () {
        return "TMX Orthogonal test 2";
    },
    onEnter:function () {
        this._super();
        cc.Director.getInstance().setProjection(cc.DIRECTOR_PROJECTION_3D);
    },
    onExit:function () {
        this._super();
        cc.Director.getInstance().setProjection(cc.DIRECTOR_PROJECTION_2D);
    }
});


//------------------------------------------------------------------
//
// TMXOrthoTest3
//
//------------------------------------------------------------------
var TMXOrthoTest3 = TileDemo.extend({
    ctor:function () {
        this._super();
        var map = cc.TMXTiledMap.create("res/TileMaps/orthogonal-test3.tmx");
        this.addChild(map, 0, TAG_TILE_MAP);

        map.setScale(0.2);
        map.setAnchorPoint(cc.p(0.5, 0.5));
    },
    title:function () {
        return "TMX anchorPoint test";
    }
});

//------------------------------------------------------------------
//
// TMXOrthoTest4
//
//------------------------------------------------------------------
var TMXOrthoTest4 = TileDemo.extend({
    ctor:function () {
        this._super();
        var map = cc.TMXTiledMap.create("res/TileMaps/orthogonal-test4.tmx");
        this.addChild(map, 0, TAG_TILE_MAP);

        map.setAnchorPoint(cc.p(0, 0));

        var layer = map.layerNamed("Layer 0");
        var s = layer.getLayerSize();

        var sprite;
        sprite = layer.tileAt(cc.p(0, 0));
        sprite.setScale(2);

        sprite = layer.tileAt(cc.p(s.width - 1, 0));
        sprite.setScale(2);

        sprite = layer.tileAt(cc.p(0, s.height - 1));
        sprite.setScale(2);

        sprite = layer.tileAt(cc.p(s.width - 1, s.height - 1));
        sprite.setScale(2);

        this.schedule(this.removeSprite, 2);
    },
    removeSprite:function (dt) {
        this.unschedule(this.removeSprite);

        var map = this.getChildByTag(TAG_TILE_MAP);

        var layer = map.layerNamed("Layer 0");
        var s = layer.getLayerSize();

        var sprite = layer.tileAt(cc.p(s.width - 1, 0));
        layer.removeChild(sprite, true);
    },
    title:function () {
        return "TMX width/height test";
    }
});

//------------------------------------------------------------------
//
// TMXReadWriteTest
//
//------------------------------------------------------------------
var TMXReadWriteTest = TileDemo.extend({
    gid:0,
    ctor:function () {
        this._super();

        var map = cc.TMXTiledMap.create("res/TileMaps/orthogonal-test2.tmx");
        this.addChild(map, 0, TAG_TILE_MAP);

        var s = map.getContentSize();

        var layer = map.layerNamed("Layer 0");
        //layer.getTexture().setAntiAliasTexParameters();

        map.setScale(1);

        var tile0 = layer.tileAt(cc.p(1, 63));
        var tile1 = layer.tileAt(cc.p(2, 63));
        var tile2 = layer.tileAt(cc.p(3, 62));//cc.p(1,62));
        var tile3 = layer.tileAt(cc.p(2, 62));

        tile0.setAnchorPoint(cc.p(0.5, 0.5));
        tile1.setAnchorPoint(cc.p(0.5, 0.5));
        tile2.setAnchorPoint(cc.p(0.5, 0.5));
        tile3.setAnchorPoint(cc.p(0.5, 0.5));

        var move = cc.MoveBy.create(0.5, cc.p(0, 160));
        var rotate = cc.RotateBy.create(2, 360);
        var scale = cc.ScaleBy.create(2, 5);
        var opacity = cc.FadeOut.create(2);
        var fadein = cc.FadeIn.create(2);
        var scaleback = cc.ScaleTo.create(1, 1);
        var finish = cc.CallFunc.create(this, this.removeSprite);

        var seq0 = cc.Sequence.create(move, rotate, scale, opacity, fadein, scaleback, finish, null);

        tile0.runAction(seq0);
        tile1.runAction(seq0.copy());
        tile2.runAction(seq0.copy());
        tile3.runAction(seq0.copy());

        this.gid = layer.tileGIDAt(cc.p(0, 63));

        this.schedule(this.updateCol, 2.0);
        this.schedule(this.repaintWithGID, 2.0);
        this.schedule(this.removeTiles, 1.0);

        this.gid2 = 0;
    },
    removeSprite:function (sender) {
        var p = sender.getParent();
        if (p) {
            p.removeChild(sender, true);
        }
    },
    updateCol:function (dt) {
        var map = this.getChildByTag(TAG_TILE_MAP);
        var layer = map.getChildByTag(0);

        var s = layer.getLayerSize();

        for (var y = 0; y < s.height; y++) {
            layer.setTileGID(this.gid2, cc.p(3, y));
        }

        this.gid2 = (this.gid2 + 1) % 80;
    },
    repaintWithGID:function (dt) {

        var map = this.getChildByTag(TAG_TILE_MAP);
        var layer = map.getChildByTag(0);

        var s = layer.getLayerSize();
        for (var x = 0; x < s.width; x++) {
            var y = s.height - 1;
            var tmpgid = layer.tileGIDAt(cc.p(x, y));
            layer.setTileGID(tmpgid + 1, cc.p(x, y));
        }
    },
    removeTiles:function (dt) {
        this.unschedule(this.removeTiles);

        var map = this.getChildByTag(TAG_TILE_MAP);

        var layer = map.getChildByTag(0);
        var s = layer.getLayerSize();

        for (var y = 0; y < s.height; y++) {
            layer.removeTileAt(cc.p(5.0, y));
        }
    },
    title:function () {
        return "TMX Read/Write test";
    }
});

//------------------------------------------------------------------
//
// TMXHexTest
//
//------------------------------------------------------------------
var TMXHexTest = TileDemo.extend({
    ctor:function () {
        this._super();
        var color = cc.LayerColor.create(cc.c4b(64, 64, 64, 255));
        this.addChild(color, -1);

        var map = cc.TMXTiledMap.create("res/TileMaps/hexa-test.tmx");
        this.addChild(map, 0, TAG_TILE_MAP);
    },
    title:function () {
        return "TMX Hex test";
    }
});

//------------------------------------------------------------------
//
// TMXIsoTest
//
//------------------------------------------------------------------
var TMXIsoTest = TileDemo.extend({
    ctor:function () {
        this._super();
        var color = cc.LayerColor.create(cc.c4b(64, 64, 64, 255));
        this.addChild(color, -1);

        var map = cc.TMXTiledMap.create("res/TileMaps/iso-test.tmx");
        this.addChild(map, 0, TAG_TILE_MAP);

        // move map to the center of the screen
        var ms = map.getMapSize();
        var ts = map.getTileSize();
        map.runAction(cc.MoveTo.create(1.0, cc.p(-ms.width * ts.width / 2, -ms.height * ts.height / 2)));
    },
    title:function () {
        return "TMX Isometric test 0";
    }
});

//------------------------------------------------------------------
//
// TMXIsoTest1
//
//------------------------------------------------------------------
var TMXIsoTest1 = TileDemo.extend({
    ctor:function () {
        this._super();
        var color = cc.LayerColor.create(cc.c4b(64, 64, 64, 255));
        this.addChild(color, -1);

        var map = cc.TMXTiledMap.create("res/TileMaps/iso-test1.tmx");
        this.addChild(map, 0, TAG_TILE_MAP);

        var s = map.getContentSize();

        map.setAnchorPoint(cc.p(0.5, 0.5));
    },
    title:function () {
        return "TMX Isometric test + anchorPoint";
    }
});

//------------------------------------------------------------------
//
// TMXIsoTest2
//
//------------------------------------------------------------------
var TMXIsoTest2 = TileDemo.extend({
    ctor:function () {
        this._super();
        var color = cc.LayerColor.create(cc.c4b(64, 64, 64, 255));
        this.addChild(color, -1);

        var map = cc.TMXTiledMap.create("res/TileMaps/iso-test2.tmx");
        this.addChild(map, 0, TAG_TILE_MAP);

        var s = map.getContentSize();

        // move map to the center of the screen
        var ms = map.getMapSize();
        var ts = map.getTileSize();
        map.runAction(cc.MoveTo.create(1.0, cc.p(-ms.width * ts.width / 2, -ms.height * ts.height / 2)));
    },
    title:function () {
        return "TMX Isometric test 2";
    }
});

//------------------------------------------------------------------
//
// TMXUncompressedTest
//
//------------------------------------------------------------------
var TMXUncompressedTest = TileDemo.extend({
    ctor:function () {
        this._super();
        var color = cc.LayerColor.create(cc.c4b(64, 64, 64, 255));
        this.addChild(color, -1);

        var map = cc.TMXTiledMap.create("res/TileMaps/iso-test2-uncompressed.tmx");
        this.addChild(map, 0, TAG_TILE_MAP);

        var s = map.getContentSize();

        // move map to the center of the screen
        var ms = map.getMapSize();
        var ts = map.getTileSize();
        map.runAction(cc.MoveTo.create(1.0, cc.p(-ms.width * ts.width / 2, -ms.height * ts.height / 2)));

        // testing release map
        var childrenArray = map.getChildren();
        var layer = null;
        for (var i = 0, len = childrenArray.length; i < len; i++) {
            layer = childrenArray[i];
            if (!layer)
                break;

            layer.releaseMap();
        }
    },
    title:function () {
        return "TMX Uncompressed test";
    }
});

//------------------------------------------------------------------
//
// TMXTilesetTest
//
//------------------------------------------------------------------
var TMXTilesetTest = TileDemo.extend({
    ctor:function () {
        this._super();
        var map = cc.TMXTiledMap.create("res/TileMaps/orthogonal-test5.tmx");
        this.addChild(map, 0, TAG_TILE_MAP);
        var s = map.getContentSize();

        /*var layer;
         layer = map.layerNamed("Layer 0");
         layer.getTexture().setAntiAliasTexParameters();

         layer = map.layerNamed("Layer 1");
         layer.getTexture().setAntiAliasTexParameters();

         layer = map.layerNamed("Layer 2");
         layer.getTexture().setAntiAliasTexParameters();*/
    },
    title:function () {
        return "TMX Tileset test";
    }
});

//------------------------------------------------------------------
//
// TMXOrthoObjectsTest
//
//------------------------------------------------------------------
var TMXOrthoObjectsTest = TileDemo.extend({
    ctor:function () {
        this._super();
        var map = cc.TMXTiledMap.create("res/TileMaps/ortho-objects.tmx");
        this.addChild(map, -1, TAG_TILE_MAP);
        var s = map.getContentSize();

        var group = map.objectGroupNamed("Object Group 1");
        var objects = group.getObjects();

        for (var i = 0; i < objects.length; i++) {
            var dict = objects[i];
            if (!dict)
                break;
        }
    },
    draw:function () {
        var map = this.getChildByTag(TAG_TILE_MAP);
        var group = map.objectGroupNamed("Object Group 1");
        var objects = group.getObjects();
        for (var i = 0; i < objects.length; i++) {
            var dict = objects[i];
            if (!dict)
                break;

            var x = dict["x"];
            var y = dict["y"];
            var width = dict["width"];
            var height = dict["height"];

            cc.renderContext.lineWidth = 3;
            cc.renderContext.strokeStyle = "#ffffff";

            cc.drawingUtil.drawLine(cc.p(x, y), cc.p((x + width), y));
            cc.drawingUtil.drawLine(cc.p((x + width), y), cc.p((x + width), (y + height)));
            cc.drawingUtil.drawLine(cc.p((x + width), (y + height)), cc.p(x, (y + height)));
            cc.drawingUtil.drawLine(cc.p(x, (y + height)), cc.p(x, y));

            cc.renderContext.lineWidth = 1;
        }
    },
    title:function () {
        return "TMX Ortho object test";
    },
    subtitle:function () {
        return "You should see a white box around the 3 platforms";
    }
});

//------------------------------------------------------------------
//
// TMXIsoObjectsTest
//
//------------------------------------------------------------------
var TMXIsoObjectsTest = TileDemo.extend({
    ctor:function () {
        this._super();
        var map = cc.TMXTiledMap.create("res/TileMaps/iso-test-objectgroup.tmx");
        this.addChild(map, -1, TAG_TILE_MAP);

        var s = map.getContentSize();

        var group = map.objectGroupNamed("Object Group 1");
        var objects = group.getObjects();

        var dict;
        for (var i = 0, len = objects.length; i < len; i++) {
            dict = objects[i];
            if (!dict)
                break;
        }
    },
    title:function () {
        return "TMX Iso object test";
    },
    draw:function () {
        var map = this.getChildByTag(TAG_TILE_MAP);
        var group = map.objectGroupNamed("Object Group 1");
        var objects = group.getObjects();
        var dict;
        for (var i = 0, len = objects.length; i < len; i++) {
            dict = objects[i];
            if (!dict)
                break;

            var x = dict["x"];
            var y = dict["y"];
            var width = dict["width"];
            var height = dict["height"];

            cc.renderContext.lineWidth = 3;
            cc.renderContext.strokeStyle = "#ffffff";

            cc.drawingUtil.drawLine(cc.p(x, y), cc.p(x + width, y));
            cc.drawingUtil.drawLine(cc.p(x + width, y), cc.p(x + width, y + height));
            cc.drawingUtil.drawLine(cc.p(x + width, y + height), cc.p(x, y + height));
            cc.drawingUtil.drawLine(cc.p(x, y + height), cc.p(x, y));

            cc.renderContext.lineWidth = 1;
        }
    },
    subtitle:function () {
        return "You need to parse them manually. See bug #810";
    }
});

//------------------------------------------------------------------
//
// TMXResizeTest
//
//------------------------------------------------------------------
var TMXResizeTest = TileDemo.extend({
    ctor:function () {
        this._super();
        var map = cc.TMXTiledMap.create("res/TileMaps/orthogonal-test5.tmx");
        this.addChild(map, 0, TAG_TILE_MAP);

        var s = map.getContentSize();

        var layer;
        layer = map.layerNamed("Layer 0");

        var ls = layer.getLayerSize();
        for (var y = 0; y < ls.height; y++) {
            for (var x = 0; x < ls.width; x++) {
                layer.setTileGID(1, cc.p(x, y));
            }
        }
    },
    title:function () {
        return "TMX resize test";
    },
    subtitle:function () {
        return "Should not crash. Testing issue #740";
    }
});

//------------------------------------------------------------------
//
// TMXIsoZorder
//
//------------------------------------------------------------------
var TMXIsoZorder = TileDemo.extend({
    tamara:null,
    ctor:function () {
        this._super();
        var map = cc.TMXTiledMap.create("res/TileMaps/iso-test-zorder.tmx");
        this.addChild(map, 0, TAG_TILE_MAP);

        var s = map.getContentSize();
        map.setPosition(cc.p(-s.width / 2, 0));

        this.tamara = cc.Sprite.create(s_pathSister1);
        map.addChild(this.tamara, map.getChildren().length);
        var mapWidth = map.getMapSize().width * map.getTileSize().width;
        this.tamara.setPosition(cc.POINT_PIXELS_TO_POINTS(cc.p(mapWidth / 2, 0)));
        this.tamara.setAnchorPoint(cc.p(0.5, 0));

        var move = cc.MoveBy.create(10, cc.pMult(cc.p(300, 250), 1 / cc.CONTENT_SCALE_FACTOR()));
        var back = move.reverse();
        var seq = cc.Sequence.create(move, back, null);
        this.tamara.runAction(cc.RepeatForever.create(seq));

        this.schedule(this.repositionSprite);
    },
    title:function () {
        return "TMX Iso Zorder";
    },
    subtitle:function () {
        return "Sprite should hide behind the trees";
    },
    onExit:function () {
        this.unschedule(this.repositionSprite);
        this._super();
    },
    repositionSprite:function (dt) {
        var p = this.tamara.getPosition();
        p = cc.POINT_POINTS_TO_PIXELS(p);
        var map = this.getChildByTag(TAG_TILE_MAP);

        // there are only 4 layers. (grass and 3 trees layers)
        // if tamara < 48, z=4
        // if tamara < 96, z=3
        // if tamara < 144, z=2

        var newZ = 4 - (p.y / 48);
        newZ = parseInt(Math.max(newZ, 0));
        map.reorderChild(this.tamara, newZ);
    }
});

//------------------------------------------------------------------
//
// TMXOrthoZorder
//
//------------------------------------------------------------------
var TMXOrthoZorder = TileDemo.extend({
    tamara:null,
    ctor:function () {
        this._super();
        var map = cc.TMXTiledMap.create("res/TileMaps/orthogonal-test-zorder.tmx");
        this.addChild(map, 0, TAG_TILE_MAP);

        var s = map.getContentSize();

        this.tamara = cc.Sprite.create(s_pathSister1);
        map.addChild(this.tamara, map.getChildren().length, TAG_TILE_MAP);
        this.tamara.setAnchorPoint(cc.p(0.5, 0));

        var move = cc.MoveBy.create(10, cc.pMult(cc.p(400, 450), 1 / cc.CONTENT_SCALE_FACTOR()));
        var back = move.reverse();
        var seq = cc.Sequence.create(move, back, null);
        this.tamara.runAction(cc.RepeatForever.create(seq));

        this.schedule(this.repositionSprite);
    },
    title:function () {
        return "TMX Ortho Zorder";
    },
    subtitle:function () {
        return "Sprite should hide behind the trees";
    },
    repositionSprite:function (dt) {
        var p = this.tamara.getPosition();
        p = cc.POINT_POINTS_TO_PIXELS(p);
        var map = this.getChildByTag(TAG_TILE_MAP);

        // there are only 4 layers. (grass and 3 trees layers)
        // if tamara < 81, z=4
        // if tamara < 162, z=3
        // if tamara < 243,z=2

        // -10: customization for this particular sample
        var newZ = 4 - ((p.y - 10) / 81);
        newZ = Math.max(newZ, 0);

        map.reorderChild(this.tamara, newZ);
    }
});

//------------------------------------------------------------------
//
// TMXIsoVertexZ
//
//------------------------------------------------------------------
var TMXIsoVertexZ = TileDemo.extend({
    tamara:null,
    tamara1:null,
    ctor:function () {
        this._super();
        var map = cc.TMXTiledMap.create("res/TileMaps/iso-test-vertexz.tmx");
        this.addChild(map, 0, TAG_TILE_MAP);

        var s = map.getContentSize();
        map.setPosition(cc.p(-s.width / 2, 0));

        // because I'm lazy, I'm reusing a tile as an sprite, but since this method uses vertexZ, you
        // can use any cc.Sprite and it will work OK.
        var layer = map.layerNamed("Trees");
        this.tamara = layer.tileAt(cc.p(29, 29));

        var move = cc.MoveBy.create(10, cc.pMult(cc.p(300, 250), 1 / cc.CONTENT_SCALE_FACTOR()));
        var back = move.reverse();
        var seq = cc.Sequence.create(move, back, null);
        this.tamara.runAction(cc.RepeatForever.create(seq));

        this.schedule(this.repositionSprite);
    },
    title:function () {
        return "TMX Iso VertexZ";
    },
    subtitle:function () {
        return "Sprite should hide behind the trees";
    },
    onEnter:function () {
        this._super();
        // TIP: 2d projection should be used
        cc.Director.getInstance().setProjection(cc.DIRECTOR_PROJECTION_2D);
    },
    onExit:function () {
// At exit use any other projection.
        //	cc.Director.getInstance().setProjection:cc.DIRECTOR_PROJECTION_3D);
        this._super();
    },
    repositionSprite:function (dt) {
        // tile height is 64x32
        // map size: 30x30
        var p = this.tamara.getPosition();
        p = cc.POINT_POINTS_TO_PIXELS(p);
        this.tamara.setVertexZ(-( (p.y + 32) / 16));
    }
});

//------------------------------------------------------------------
//
// TMXOrthoVertexZ
//
//------------------------------------------------------------------
var TMXOrthoVertexZ = TileDemo.extend({
    tamara:null,
    ctor:function () {
        this._super();
        var map = cc.TMXTiledMap.create("res/TileMaps/orthogonal-test-vertexz.tmx");
        this.addChild(map, 0, TAG_TILE_MAP);

        var s = map.getContentSize();

        // because I'm lazy, I'm reusing a tile as an sprite, but since this method uses vertexZ, you
        // can use any cc.Sprite and it will work OK.
        var layer = map.layerNamed("trees");
        this.tamara = layer.tileAt(cc.p(0, 11));
        cc.log("vertexZ: " + this.tamara.getVertexZ());

        var move = cc.MoveBy.create(10, cc.pMult(cc.p(400, 450), 1 / cc.CONTENT_SCALE_FACTOR()));
        var back = move.reverse();
        var seq = cc.Sequence.create(move, back, null);
        this.tamara.runAction(cc.RepeatForever.create(seq));

        this.schedule(this.repositionSprite);
    },
    title:function () {
        return "TMX Ortho vertexZ";
    },
    subtitle:function () {
        return "Sprite should hide behind the trees";
    },
    onEnter:function () {
        this._super();

        // TIP: 2d projection should be used
        cc.Director.getInstance().setProjection(cc.DIRECTOR_PROJECTION_2D);
    },
    onExit:function () {
        // At exit use any other projection.
        //	cc.Director.getInstance().setProjection:cc.DIRECTOR_PROJECTION_3D);
        this._super();
    },
    repositionSprite:function (dt) {
        // tile height is 64x32
        // map size: 30x30
        var p = this.tamara.getPosition();
        p = cc.POINT_POINTS_TO_PIXELS(p);
        this.tamara.setVertexZ(-( (p.y + 32) / 16));
    }
});

//------------------------------------------------------------------
//
// TMXIsoMoveLayer
//
//------------------------------------------------------------------
var TMXIsoMoveLayer = TileDemo.extend({
    ctor:function () {
        this._super();
        var map = cc.TMXTiledMap.create("res/TileMaps/iso-test-movelayer.tmx");
        this.addChild(map, 0, TAG_TILE_MAP);
        map.setPosition(cc.p(-700, -50));

        var s = map.getContentSize();
    },
    title:function () {
        return "TMX Iso Move Layer";
    },
    subtitle:function () {
        return "Trees should be horizontally aligned";
    }
});

//------------------------------------------------------------------
//
// TMXOrthoMoveLayer
//
//------------------------------------------------------------------
var TMXOrthoMoveLayer = TileDemo.extend({
    ctor:function () {
        this._super();
        var map = cc.TMXTiledMap.create("res/TileMaps/orthogonal-test-movelayer.tmx");
        this.addChild(map, 0, TAG_TILE_MAP);

        var s = map.getContentSize();
    },
    title:function () {
        return "TMX Ortho Move Layer";
    },
    subtitle:function () {
        return "Trees should be horizontally aligned";
    }
});

//------------------------------------------------------------------
//
// TMXTilePropertyTest
//
//------------------------------------------------------------------
var TMXTilePropertyTest = TileDemo.extend({
    ctor:function () {
        this._super();
        var map = cc.TMXTiledMap.create("res/TileMaps/ortho-tile-property.tmx");
        this.addChild(map, 0, TAG_TILE_MAP);

        for (var i = 1; i <= 20; i++) {
            cc.log("GID:" + i + ", Properties:" + JSON.stringify(map.propertiesForGID(i)));
        }

    },
    title:function () {
        return "TMX Tile Property Test";
    },
    subtitle:function () {
        return "In the console you should see tile properties";
    }
});

//------------------------------------------------------------------
//
// TMXOrthoFlipTest
//
//------------------------------------------------------------------
var TMXOrthoFlipTest = TileDemo.extend({
    ctor:function () {
        this._super();
        var map = cc.TMXTiledMap.create("res/TileMaps/ortho-rotation-test.tmx");
        this.addChild(map, 0, TAG_TILE_MAP);
        var s = map.getContentSize();
        cc.log("ContentSize:" + s.width + "," + s.height);

        var action = cc.ScaleBy.create(2, 0.5);
        map.runAction(action);
    },
    title:function () {
        return "TMX tile flip test";
    }
});

//------------------------------------------------------------------
//
// TMXOrthoFlipRunTimeTest
//
//------------------------------------------------------------------
var TMXOrthoFlipRunTimeTest = TileDemo.extend({
    ctor:function () {
        this._super();
        var map = cc.TMXTiledMap.create("res/TileMaps/ortho-rotation-test.tmx");
        this.addChild(map, 0, TAG_TILE_MAP);

        var s = map.getContentSize();
        cc.log("ContentSize:" + s.width + "," + s.height);

        var action = cc.ScaleBy.create(2, 0.5);
        map.runAction(action);

        this.schedule(this.flipIt, 1);
    },
    title:function () {
        return "TMX tile flip run time test";
    },
    subtitle:function () {
        return "in 2 sec bottom left tiles will flip";
    },
    flipIt:function () {
        var map = this.getChildByTag(TAG_TILE_MAP);
        var layer = map.layerNamed("Layer 0");

        //blue diamond
        var tileCoord = cc.p(1, 10);
        var flags = layer.tileFlagAt(tileCoord);
        var GID = layer.tileGIDAt(tileCoord);
        // Vertical
        if ((flags & cc.TMXTileVerticalFlag) >>> 0) {
            flags = (flags & ~cc.TMXTileVerticalFlag >>> 0) >>> 0;
        }
        else {
            flags = (flags | cc.TMXTileVerticalFlag) >>> 0;
        }
        layer.setTileGID(GID, tileCoord, flags);

        tileCoord = cc.p(1, 8);
        flags = layer.tileFlagAt(tileCoord);
        GID = layer.tileGIDAt(tileCoord);
        // Vertical
        if ((flags & cc.TMXTileVerticalFlag) >>> 0)
            flags = (flags & ~cc.TMXTileVerticalFlag >>> 0) >>> 0;
        else
            flags = (flags | cc.TMXTileVerticalFlag) >>> 0;
        layer.setTileGID(GID, tileCoord, flags);

        tileCoord = cc.p(2, 8);
        flags = layer.tileFlagAt(tileCoord);
        GID = layer.tileGIDAt(tileCoord);
        // Horizontal
        if ((flags & cc.TMXTileHorizontalFlag) >>> 0)
            flags = (flags & ~cc.TMXTileHorizontalFlag >>> 0) >>> 0;
        else
            flags = (flags | cc.TMXTileHorizontalFlag) >>> 0;
        layer.setTileGID(GID, tileCoord, flags);
    }
});

//------------------------------------------------------------------
//
// TMXOrthoFromXMLTest
//
//------------------------------------------------------------------
var TMXOrthoFromXMLTest = TileDemo.extend({
    ctor:function () {
        this._super();
        var resources = "res/TileMaps";        // partial paths are OK as resource paths.
        var file = resources + "/orthogonal-test1.tmx";

        var str = cc.FileUtils.getInstance().fullPathFromRelativePath(file);
        cc.Assert(str != null, "Unable to open file");

        var map = cc.TMXTiledMap.create(str, resources);
        this.addChild(map, 0, TAG_TILE_MAP);

        var s = map.getContentSize();
        cc.log("ContentSize:" + s.width + "," + s.height);

        var action = cc.ScaleBy.create(2, 0.5);
        map.runAction(action);
    },
    title:function () {
        return "TMX created from XML test";
    }
});

//------------------------------------------------------------------
//
// TMXBug987
//
//------------------------------------------------------------------
var TMXBug987 = TileDemo.extend({
    ctor:function () {
        this._super();
        var map = cc.TMXTiledMap.create("res/TileMaps/orthogonal-test6.tmx");
        this.addChild(map, 0, TAG_TILE_MAP);

        var s1 = map.getContentSize();
        cc.log("ContentSize:" + s1.width + "," + s1.height);

        var childs = map.getChildren();
        var node = null;
        for (var i = 0, len = childs.length; i < len; i++) {
            node = childs[i];
            if (!node) break;
            //node.getTexture().setAntiAliasTexParameters();
        }

        map.setAnchorPoint(cc.p(0, 0));
        var layer = map.layerNamed("Tile Layer 1");
        layer.setTileGID(3, cc.p(2, 2));
    },
    title:function () {
        return "TMX Bug 987";
    },
    subtitle:function () {
        return "You should see an square";
    }
});

//------------------------------------------------------------------
//
// TMXBug787
//
//------------------------------------------------------------------
var TMXBug787 = TileDemo.extend({
    ctor:function () {
        this._super();
        var map = cc.TMXTiledMap.create("res/TileMaps/iso-test-bug787.tmx");
        this.addChild(map, 0, TAG_TILE_MAP);

        map.setScale(0.25);
    },
    title:function () {
        return "TMX Bug 787";
    },
    subtitle:function () {
        return "You should see a map";
    }
});

var TMXGIDObjectsTest = TileDemo.extend({
    ctor:function () {
        this._super();
        var map = cc.TMXTiledMap.create("res/TileMaps/test-object-layer.tmx");
        this.addChild(map, -1, TAG_TILE_MAP);

        var s = map.getContentSize();
        cc.log("ContentSize:" + s.width + "," + s.height);
        cc.log("---. Iterating over all the group objets");
    },
    title:function () {
        return "TMX GID objects";
    },
    subtitle:function () {
        return "Tiles are created from an object group";
    },
    draw:function () {
        var map = this.getChildByTag(TAG_TILE_MAP);
        var group = map.objectGroupNamed("Object Layer 1");

        var array = group.getObjects();
        var dict;
        for (var i = 0, len = array.length; i < len; i++) {
            dict = array[i];
            if (!dict)
                break;
            var x = dict["x"];
            var y = dict["y"];
            var width = dict["width"];
            var height = dict["height"];

            cc.renderContext.lineWidth = 3;
            cc.renderContext.strokeStyle = "#ffffff";

            cc.drawingUtil.drawLine(cc.p(x, y), cc.p(x + width, y));
            cc.drawingUtil.drawLine(cc.p(x + width, y), cc.p(x + width, y + height));
            cc.drawingUtil.drawLine(cc.p(x + width, y + height), cc.p(x, y + height));
            cc.drawingUtil.drawLine(cc.p(x, y + height), cc.p(x, y));

            cc.renderContext.lineWidth = 1;
        }
    }
});
