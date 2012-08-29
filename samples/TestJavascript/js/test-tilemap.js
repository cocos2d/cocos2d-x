//
// http://www.cocos2d-iphone.org
// http://www.cocos2d-html5.org
// http://www.cocos2d-x.org
//
// Javascript + cocos2d actions tests
//

require("js/helper.js");

var TAG_TILE_MAP = 1;

director = cc.Director.getInstance();
winSize = director.getWinSize();
centerPos = cc.p( winSize.width/2, winSize.height/2 );

var scenes = []
var currentScene = 0;

var nextScene = function () {
	currentScene = currentScene + 1;
	if( currentScene >= scenes.length )
		currentScene = 0;

	withTransition = true;
	loadScene(currentScene);
};

var previousScene = function () {
	currentScene = currentScene -1;
	if( currentScene < 0 )
		currentScene = scenes.length -1;

	withTransition = true;
	loadScene(currentScene);
};

var restartScene = function () {
	loadScene( currentScene );
};

var loadScene = function (sceneIdx)
{
	winSize = director.getWinSize();
	centerPos = cc.p( winSize.width/2, winSize.height/2 );

	var scene = new cc.Scene();
	scene.init();
	var layer = new scenes[ sceneIdx ]();

	scene.addChild( layer );

//	scene.walkSceneGraph(0);

	director.replaceScene( scene );
//    __jsc__.garbageCollect();
}

//
// Base Layer
//

var BaseLayer = cc.Layer.extend({

    prevLocation:null,

    ctor:function () {
                                
        var parent = new cc.Layer();
        __associateObjWithNative(this, parent);
        this.init();

//        var gradient = cc.LayerGradient.create( cc.c4b(0, 0, 0, 255), cc.c4b(0, 128, 255, 255) );
//        this.addChild( gradient, -100 );
    },

    title:function () {
        return "No Title";
    },

    subtitle:function () {
        return "";
    },

    code:function () {
        return "";
    },

    restartCallback:function (sender) {
        restartScene();
    },

    nextCallback:function (sender) {
        nextScene();
    },

    backCallback:function (sender) {
       previousScene();
    },

    onEnter:function () {
        // DO NOT CALL this._super()
//        this._super();

        var platform = __getPlatform();
        if( platform.substring(0,7) == 'desktop' )
            this.setMouseEnabled( true );
        else if( platform.substring(0,6) == 'mobile' )
            this.setTouchEnabled( true );

        // add title and subtitle
        var label = cc.LabelTTF.create(this.title(), "Arial", 28);
        this.addChild(label, 1);
        label.setPosition( cc.p(winSize.width / 2, winSize.height - 50));

        var strSubtitle = this.subtitle();
        if (strSubtitle != "") {
            var l = cc.LabelTTF.create(strSubtitle, "Thonburi", 16);
            this.addChild(l, 1);
            l.setPosition( cc.p(winSize.width / 2, winSize.height - 80));
        }

        var strCode = this.code();
        if( strCode !="" ) {
            var label = cc.LabelTTF.create(strCode, 'CourierNewPSMT', 16);
            label.setPosition( cc.p( winSize.width/2, winSize.height-100) );
            this.addChild( label,10 );

            var labelbg = cc.LabelTTF.create(strCode, 'CourierNewPSMT', 16);
            labelbg.setColor( cc.c3b(10,10,255) );
            labelbg.setPosition( cc.p( winSize.width/2 +1, winSize.height-100 -1) );
            this.addChild( labelbg,9);
        }

        // Menu
        var item1 = cc.MenuItemImage.create("b1.png", "b2.png", this, this.backCallback);
        var item2 = cc.MenuItemImage.create("r1.png", "r2.png", this, this.restartCallback);
        var item3 = cc.MenuItemImage.create("f1.png", "f2.png", this, this.nextCallback);
        var item4 = cc.MenuItemFont.create("back", this, function() { require("js/main.js"); } );
        item4.setFontSize( 22 );

        var menu = cc.Menu.create(item1, item2, item3, item4 );

        menu.setPosition( cc.p(0,0) );
        item1.setPosition( cc.p(winSize.width / 2 - 100, 30));
        item2.setPosition( cc.p(winSize.width / 2, 30));
        item3.setPosition( cc.p(winSize.width / 2 + 100, 30));
        item4.setPosition( cc.p(winSize.width - 60, winSize.height - 30 ) );

        this.addChild(menu, 1);
    },
    onExit:function () {
        // nothing
    },

    onTouchesMoved:function (touches, event) {
        this.moveTile( touches[0].getDelta() );
    },

    onMouseDragged : function( event ) {
        this.moveTile( event.getDelta() );
    },

    moveTile:function ( delta ) {

        var node = this.getChildByTag(TAG_TILE_MAP);
        var currentPos = node.getPosition();
        var newPos = cc.pAdd(currentPos, delta );
        node.setPosition(newPos);
    },
});



var TileMapTest = BaseLayer.extend({
    ctor:function () {
        this._super();
        var map = cc.TileMapAtlas.create("TileMaps/tiles.png", "TileMaps/levelmap.tga", 16, 16);
        map.getTexture().setAntiAliasTexParameters();

        // If you are not going to use the Map, you can free it now
        // NEW since v0.7
        map.releaseMap();

        this.addChild(map, 0, TAG_TILE_MAP);

        map.setAnchorPoint(cc.p(0, 0.5));

        var scale = cc.ScaleBy.create(4, 0.8);
        var scaleBack = scale.reverse();

        var seq = cc.Sequence.create(scale, scaleBack );

        map.runAction(cc.RepeatForever.create(seq));
    },
    title:function () {
        return "TileMapAtlas";
    }
});

var TileMapEditTest = BaseLayer.extend({
    ctor:function () {
        this._super();
        var map = cc.TileMapAtlas.create("TileMaps/tiles.png", "TileMaps/levelmap.tga", 16, 16);
        // Create an Aliased Atlas
        map.getTexture().setAliasTexParameters();

        // If you are not going to use the Map, you can free it now
        // [tilemap releaseMap);
        // And if you are going to use, it you can access the data with:

//        this.schedule(this.updateMap, 0.2);//:@selector(updateMap:) interval:0.2f);

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
var TMXOrthoTest = BaseLayer.extend({
    ctor:function () {
        this._super();
        var map = cc.TMXTiledMap.create("TileMaps/orthogonal-test1.tmx");
        this.addChild(map, 0, TAG_TILE_MAP);

        var childrenArray = map.getChildren();
        for (var i = 0; i < childrenArray.length; i++) {
            var child = childrenArray[i];
            child.getTexture().setAntiAliasTexParameters();
        }
        map.runAction(cc.ScaleBy.create(2, 0.5));
    },
    title:function () {
        return "TMX Orthogonal test";
    },

    subtitle:function () {
        return "Simple TMX test";
    },

    code : function() {
        return 'var map = cc.TMXTiledMap.create("map.tmx");'
    },
});

//------------------------------------------------------------------
//
// TMXOrthoTest2
//
//------------------------------------------------------------------
var TMXOrthoTest2 = BaseLayer.extend({
    ctor:function () {
        this._super();
        //
        // Test orthogonal with 3d camera and anti-alias textures
        //
        // it should not flicker. No artifacts should appear
        //
        var map = cc.TMXTiledMap.create("TileMaps/orthogonal-test2.tmx");
        this.addChild(map, 0, TAG_TILE_MAP);

        var childrenArray = map.getChildren();
        var child = null;
        for (var i = 0, len = childrenArray.length; i < len; i++) {
            child = childrenArray[i];
            child.getTexture().setAntiAliasTexParameters();
        }

//        var x, y, z;
//        map.getCamera().getEyeXYZ(x, y, z);
//        map.getCamera().setEyeXYZ(x - 200, y, z + 300);
    },
    title:function () {
        return "TMX Orthogonal test";
    },

    subtitle:function () {
        return "Testing camera... NOT WORKING YET";
    },
    code : function() {
        return 'var map = cc.TMXTiledMap.create("map.tmx");'
    },
    onEnter:function () {
        this._super();
        // 3D == 1
        director.setProjection(1);
    },
    onExit:function () {
        this._super();
        // 2D == 1
        director.setProjection(0);
    }
});


//------------------------------------------------------------------
//
// TMXOrthoTest3
//
//------------------------------------------------------------------
var TMXOrthoTest3 = BaseLayer.extend({
    ctor:function () {
        this._super();
        var map = cc.TMXTiledMap.create("TileMaps/orthogonal-test3.tmx");
        this.addChild(map, 0, TAG_TILE_MAP);

        var childrenArray = map.getChildren();
        var child = null;
        for (var i = 0, len = childrenArray.length; i < len; i++) {
            child = childrenArray[i];
            child.getTexture().setAntiAliasTexParameters();
        }

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
var TMXOrthoTest4 = BaseLayer.extend({
    elapsedTime:0,

    ctor:function () {
        this._super();
        var map = cc.TMXTiledMap.create("TileMaps/orthogonal-test4.tmx");
        this.addChild(map, 0, TAG_TILE_MAP);

        var childrenArray = map.getChildren();
        var child = null;
        for (var i = 0, len = childrenArray.length; i < len; i++) {
            child = childrenArray[i];
            child.getTexture().setAntiAliasTexParameters();
        }

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

        this.scheduleUpdate();
    },
    update:function (dt) {
        this.elapsedTime += dt;
        if( this.elapsedTime > 2 ) {
            this.unscheduleUpdate();

            var map = this.getChildByTag(TAG_TILE_MAP);

            var layer = map.layerNamed("Layer 0");
            var s = layer.getLayerSize();

            var sprite = layer.tileAt(cc.p(s.width - 1, 0));
            cc.log( layer );
            layer.removeChild(sprite, true);
        }
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
var TMXReadWriteTest = BaseLayer.extend({
    gid:0,
    ctor:function () {
        this._super();

        var map = cc.TMXTiledMap.create("TileMaps/orthogonal-test2.tmx");
        this.addChild(map, 0, TAG_TILE_MAP);


        var layer = map.layerNamed("Layer 0");
        layer.getTexture().setAntiAliasTexParameters();

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

        var seq0 = cc.Sequence.create(move, rotate, scale, opacity, fadein, scaleback, finish );

        tile0.runAction(seq0);
        tile1.runAction(seq0.copy());
        tile2.runAction(seq0.copy());
        tile3.runAction(seq0.copy());

        this.gid = layer.tileGIDAt(cc.p(0, 63));

//        this.schedule(this.updateCol, 2.0);
//        this.schedule(this.repaintWithGID, 2.0);
//        this.schedule(this.removeTiles, 1.0);

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
        //	[self unschedule:_cmd);

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
var TMXHexTest = BaseLayer.extend({
    ctor:function () {
        this._super();
        var color = cc.LayerColor.create(cc.c4b(64, 64, 64, 255));
        this.addChild(color, -1);

        var map = cc.TMXTiledMap.create("TileMaps/hexa-test.tmx");
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
var TMXIsoTest = BaseLayer.extend({
    ctor:function () {
        this._super();
        var color = cc.LayerColor.create(cc.c4b(64, 64, 64, 255));
        this.addChild(color, -1);

        var map = cc.TMXTiledMap.create("TileMaps/iso-test.tmx");
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
var TMXIsoTest1 = BaseLayer.extend({
    ctor:function () {
        this._super();
        var color = cc.LayerColor.create(cc.c4b(64, 64, 64, 255));
        this.addChild(color, -1);

        var map = cc.TMXTiledMap.create("TileMaps/iso-test1.tmx");
        this.addChild(map, 0, TAG_TILE_MAP);

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
var TMXIsoTest2 = BaseLayer.extend({
    ctor:function () {
        this._super();
        var color = cc.LayerColor.create(cc.c4b(64, 64, 64, 255));
        this.addChild(color, -1);

        var map = cc.TMXTiledMap.create("TileMaps/iso-test2.tmx");
        this.addChild(map, 0, TAG_TILE_MAP);

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
var TMXUncompressedTest = BaseLayer.extend({
    ctor:function () {
        this._super();
        var color = cc.LayerColor.create(cc.c4b(64, 64, 64, 255));
        this.addChild(color, -1);

        var map = cc.TMXTiledMap.create("TileMaps/iso-test2-uncompressed.tmx");
        this.addChild(map, 0, TAG_TILE_MAP);

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
var TMXTilesetTest = BaseLayer.extend({
    ctor:function () {
        this._super();
        var map = cc.TMXTiledMap.create("TileMaps/orthogonal-test5.tmx");
        this.addChild(map, 0, TAG_TILE_MAP);

        var layer;
        layer = map.layerNamed("Layer 0");
        layer.getTexture().setAntiAliasTexParameters();

        layer = map.layerNamed("Layer 1");
        layer.getTexture().setAntiAliasTexParameters();

        layer = map.layerNamed("Layer 2");
        layer.getTexture().setAntiAliasTexParameters();
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
var TMXOrthoObjectsTest = BaseLayer.extend({
    ctor:function () {
        this._super();
        var map = cc.TMXTiledMap.create("TileMaps/ortho-objects.tmx");
        this.addChild(map, -1, TAG_TILE_MAP);

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

            var x = parseInt(dict["x"]);
            var y = parseInt(dict["y"]);
            var width = parseInt(dict["width"]);
            var height = parseInt(dict["height"]);

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
var TMXIsoObjectsTest = BaseLayer.extend({
    ctor:function () {
        this._super();
        var map = cc.TMXTiledMap.create("TileMaps/iso-test-objectgroup.tmx");
        this.addChild(map, -1, TAG_TILE_MAP);


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

            var x = parseInt(dict["x"]);
            var y = parseInt(dict["y"]);
            var width = parseInt(dict["width"]);
            var height = parseInt(dict["height"]);

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
var TMXResizeTest = BaseLayer.extend({
    ctor:function () {
        this._super();
        var map = cc.TMXTiledMap.create("TileMaps/orthogonal-test5.tmx");
        this.addChild(map, 0, TAG_TILE_MAP);


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
var TMXIsoZorder = BaseLayer.extend({
    tamara:null,
    ctor:function () {
        this._super();
        var map = cc.TMXTiledMap.create("TileMaps/iso-test-zorder.tmx");
        this.addChild(map, 0, TAG_TILE_MAP);

        var s = map.getContentSize();
        map.setPosition(cc.p(-s.width / 2, 0));

        this.tamara = cc.Sprite.create("grossinis_sister1.png");
        map.addChild(this.tamara, map.getChildren().length);

        // move map to the center of the screen
        var ms = map.getMapSize();
        var ts = map.getTileSize();

        var mapWidth = ms.width * ts.width;
        this.tamara.setPosition(cc.p(mapWidth / 2, 0));
        this.tamara.setAnchorPoint(cc.p(0.5, 0));


        var move = cc.MoveBy.create(10, cc.pMult(cc.p(300, 250), 1 ));
        var back = move.reverse();
        var seq = cc.Sequence.create(move, back );
        this.tamara.runAction(cc.RepeatForever.create(seq));

        this.scheduleUpdate();
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
    update:function (dt) {
        var p = this.tamara.getPosition();

        var map = this.getChildByTag(TAG_TILE_MAP);

        // there are only 4 layers. (grass and 3 trees layers)
        // if tamara < 48, z=4
        // if tamara < 96, z=3
        // if tamara < 144,z=2

        var newZ = 4 - (p.y / 48);
        newZ = Math.max(newZ, 0);

        map.reorderChild(this.tamara, newZ);
    }
});

//------------------------------------------------------------------
//
// TMXOrthoZorder
//
//------------------------------------------------------------------
var TMXOrthoZorder = BaseLayer.extend({
    tamara:null,
    ctor:function () {
        this._super();
        var map = cc.TMXTiledMap.create("TileMaps/orthogonal-test-zorder.tmx");
        this.addChild(map, 0, TAG_TILE_MAP);

        var s = map.getContentSize();

        this.tamara = cc.Sprite.create("grossinis_sister1.png");
        map.addChild(this.tamara, map.getChildren().length, TAG_TILE_MAP);
        this.tamara.setAnchorPoint(cc.p(0.5, 0));

        var move = cc.MoveBy.create(10, cc.pMult(cc.p(400, 450), 1 ));
        var back = move.reverse();
        var seq = cc.Sequence.create(move, back );
        this.tamara.runAction(cc.RepeatForever.create(seq));

        this.scheduleUpdate();
    },
    title:function () {
        return "TMX Ortho Zorder";
    },
    subtitle:function () {
        return "Sprite should hide behind the trees";
    },
    update:function (dt) {
        var p = this.tamara.getPosition();
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
var TMXIsoVertexZ = BaseLayer.extend({
    tamara:null,
    tamara1:null,
    ctor:function () {
        this._super();
        var map = cc.TMXTiledMap.create("TileMaps/iso-test-vertexz.tmx");
        this.addChild(map, 0, TAG_TILE_MAP);

        var s = map.getContentSize();
        map.setPosition(cc.p(-s.width / 2, 0));

        // because I'm lazy, I'm reusing a tile as an sprite, but since this method uses vertexZ, you
        // can use any cc.Sprite and it will work OK.
        var layer = map.layerNamed("Trees");
        this.tamara = layer.tileAt(cc.p(29, 29));

        var move = cc.MoveBy.create(10, cc.pMult(cc.p(300, 250), 1 ));
        var back = move.reverse();
        var seq = cc.Sequence.create(move, back );
        this.tamara.runAction(cc.RepeatForever.create(seq));

        this.scheduleUpdate();
    },
    title:function () {
        return "TMX Iso VertexZ";
    },
    subtitle:function () {
        return "Sprite should hide behind the trees (enable DepthBuffer)";
    },
    onEnter:function () {
        this._super();
        // TIP: 2d projection should be used
        // 0 == 2D
        director.setProjection(0);
    },
    onExit:function () {
// At exit use any other projection.
        // 1 == 3D
        // director.setProjection(1);
        this._super();
    },
    update:function (dt) {
        // tile height is 64x32
        // map size: 30x30
        var p = this.tamara.getPosition();
        this.tamara.setVertexZ(-( (p.y + 32) / 16));
    }
});

//------------------------------------------------------------------
//
// TMXOrthoVertexZ
//
//------------------------------------------------------------------
var TMXOrthoVertexZ = BaseLayer.extend({
    tamara:null,
    ctor:function () {
        this._super();
        var map = cc.TMXTiledMap.create("TileMaps/orthogonal-test-vertexz.tmx");
        this.addChild(map, 0, TAG_TILE_MAP);


        // because I'm lazy, I'm reusing a tile as an sprite, but since this method uses vertexZ, you
        // can use any cc.Sprite and it will work OK.
        var layer = map.layerNamed("trees");
        this.tamara = layer.tileAt(cc.p(0, 11));
        cc.log("vertexZ: " + this.tamara.getVertexZ());

        var move = cc.MoveBy.create(10, cc.pMult(cc.p(400, 450), 1 ));
        var back = move.reverse();
        var seq = cc.Sequence.create(move, back );
        this.tamara.runAction(cc.RepeatForever.create(seq));

        this.scheduleUpdate();
    },
    title:function () {
        return "TMX Ortho vertexZ";
    },
    subtitle:function () {
        return "Sprite should hide behind the trees (enable Depth Buffer!!)";
    },
    onEnter:function () {
        this._super();

        // TIP: 2d projection should be used
        // 2d = 0
        director.setProjection(0);
    },
    onExit:function () {
        // At exit use any other projection.
        // 3d = 1
        // director.setProjection(1);
        this._super();
    },
    update:function (dt) {
        // tile height is 101x81
        // map size: 12x12
        var p = this.tamara.getPosition();
        this.tamara.setVertexZ( -( (p.y + 81) / 81) );
    }
});

//------------------------------------------------------------------
//
// TMXIsoMoveLayer
//
//------------------------------------------------------------------
var TMXIsoMoveLayer = BaseLayer.extend({
    ctor:function () {
        this._super();
        var map = cc.TMXTiledMap.create("TileMaps/iso-test-movelayer.tmx");
        this.addChild(map, 0, TAG_TILE_MAP);
        map.setPosition(cc.p(-700, -50));

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
var TMXOrthoMoveLayer = BaseLayer.extend({
    ctor:function () {
        this._super();
        var map = cc.TMXTiledMap.create("TileMaps/orthogonal-test-movelayer.tmx");
        this.addChild(map, 0, TAG_TILE_MAP);

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
// TMXBug987
//
//------------------------------------------------------------------
var TMXBug987 = BaseLayer.extend({
    ctor:function () {
        this._super();
        var map = cc.TMXTiledMap.create("TileMaps/orthogonal-test6.tmx");
        this.addChild(map, 0, TAG_TILE_MAP);

        var s = map.getContentSize();
        cc.log("ContentSize:" + s.width + "," + s.height);

        var childs = map.getChildren();
        var node = null;
        for (var i = 0, len = childs.length; i < len; i++) {
            node = childs[i];
            node.getTexture().setAntiAliasTexParameters();
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
var TMXBug787 = BaseLayer.extend({
    ctor:function () {
        this._super();
        var map = cc.TMXTiledMap.create("TileMaps/iso-test-bug787.tmx");
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

var TMXGIDObjectsTest = BaseLayer.extend({
    ctor:function () {
        this._super();
        var map = cc.TMXTiledMap.create("TileMaps/test-object-layer.tmx");
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
            var key = "x";
            var x = parseInt(dict[key]);
            key = "y";
            var y = parseInt(dict[key]);
            key = "width";
            var width = parseInt(dict[key]);
            key = "height";
            var height = parseInt(dict[key]);

            cc.renderContext.lineWidth = 3;
            cc.renderContext.strokeStyle = "#ffffff";

            cc.drawingUtil.drawLine(cc.p(x, y), cc.p((x + width), y));
            cc.drawingUtil.drawLine(cc.p((x + width), y), cc.p((x + width), (y + height)));
            cc.drawingUtil.drawLine(cc.p((x + width), (y + height)), cc.p(x, (y + height)));
            cc.drawingUtil.drawLine(cc.p(x, (y + height)), cc.p(x, y));

            cc.renderContext.lineWidth = 1;
        }
    }
});


//
// Order of tests
//
scenes.push( TMXOrthoTest );
scenes.push( TMXOrthoTest2 );
scenes.push( TMXOrthoTest3 );
scenes.push( TMXOrthoTest4 );
scenes.push( TMXReadWriteTest );
scenes.push( TMXHexTest );
scenes.push( TMXIsoTest );
scenes.push( TMXIsoTest1 );
scenes.push( TMXIsoTest2 );
scenes.push( TMXUncompressedTest );
scenes.push( TMXTilesetTest );
scenes.push( TMXOrthoObjectsTest );
scenes.push( TMXIsoObjectsTest );
scenes.push( TMXResizeTest );
scenes.push( TMXIsoZorder );
scenes.push( TMXOrthoZorder );
scenes.push( TMXIsoVertexZ );
scenes.push( TMXOrthoVertexZ );
scenes.push( TMXIsoMoveLayer );
scenes.push( TMXOrthoMoveLayer );
scenes.push( TMXBug987 );
scenes.push( TMXBug787 );
scenes.push( TMXGIDObjectsTest );


//------------------------------------------------------------------
//
// Main entry point
//
//------------------------------------------------------------------
function run()
{
    var scene = cc.Scene.create();
    var layer = new scenes[currentScene]();
    scene.addChild( layer );

    var runningScene = director.getRunningScene();
    if( runningScene == null )
        director.runWithScene( scene );
    else
        director.replaceScene( cc.TransitionFade.create(0.5, scene ) );
}

run();

