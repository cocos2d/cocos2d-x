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
var TAG_NODE = 9960;
var TAG_GROSSINI = 9961;

var sceneIdx = -1;

var MAX_LAYER = 2;


function createParallaxTestLayer(index) {
    switch (index) {
        case 0:
            return new Parallax1();
        case 1:
            return new Parallax2();
    }

    return null;
}

function nextParallaxAction() {
    sceneIdx++;
    sceneIdx = sceneIdx % MAX_LAYER;

    var layer = createParallaxTestLayer(sceneIdx);
    return layer;
}

function backParallaxAction() {
    sceneIdx--;
    var total = MAX_LAYER;
    if (sceneIdx < 0)
        sceneIdx += total;

    var layer = createParallaxTestLayer(sceneIdx);
    return layer;
}

function restartParallaxAction() {
    var layer = createParallaxTestLayer(sceneIdx);
    return layer;
}
ParallaxDemo = cc.Layer.extend({

    _atlas:null,

    ctor:function () {
    },

    title:function () {
        return "No title";
    },

    onEnter:function () {
        this._super();

        var s = cc.Director.getInstance().getWinSize();

        var label = cc.LabelTTF.create(this.title(), "Arial", 28);
        this.addChild(label, 1);
        label.setPosition(cc.p(s.width / 2, s.height - 50));

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
        var s = new ParallaxTestScene();
        s.addChild(restartParallaxAction());

        cc.Director.getInstance().replaceScene(s);
    },

    nextCallback:function (sender) {
        var s = new ParallaxTestScene();
        s.addChild(nextParallaxAction());
        cc.Director.getInstance().replaceScene(s);

    },

    backCallback:function (sender) {
        var s = new ParallaxTestScene();
        s.addChild(backParallaxAction());
        cc.Director.getInstance().replaceScene(s);
    }
});

Parallax1 = ParallaxDemo.extend({

    _root:null,
    _target:null,
    _streak:null,


    ctor:function () {
        // Top Layer, a simple image
        var cocosImage = cc.Sprite.create(s_power);
        // scale the image (optional)
        cocosImage.setScale(0.5);
        // change the transform anchor point to 0,0 (optional)
        cocosImage.setAnchorPoint(cc.p(0, 0));


        // Middle layer: a Tile map atlas
        //var tilemap = cc.TileMapAtlas.create(s_tilesPng, s_levelMapTga, 16, 16);
        var tilemap = cc.TMXTiledMap.create("res/TileMaps/orthogonal-test2.tmx");


        // change the transform anchor to 0,0 (optional)
        tilemap.setAnchorPoint(cc.p(0, 0));

        // Anti Aliased images
        //tilemap.getTexture().setAntiAliasTexParameters();


        // background layer: another image
        var background = cc.Sprite.create(s_back);
        // scale the image (optional)
        //background.setScale(1.5);
        // change the transform anchor point (optional)
        background.setAnchorPoint(cc.p(0, 0));


        // create a void node, a parent node
        var voidNode = cc.ParallaxNode.create();

        // NOW add the 3 layers to the 'void' node

        // background image is moved at a ratio of 0.4x, 0.5y
        voidNode.addChild(background, -1, cc.p(0.4, 0.5), cc.p(0,0));

        // tiles are moved at a ratio of 2.2x, 1.0y
        voidNode.addChild(tilemap, 1, cc.p(2.2, 1.0), cc.p(0, 0));

        // top image is moved at a ratio of 3.0x, 2.5y
        voidNode.addChild(cocosImage, 2, cc.p(3.0, 2.5), cc.p(0, 0));


        // now create some actions that will move the 'void' node
        // and the children of the 'void' node will move at different
        // speed, thus, simulation the 3D environment
        var goUp = cc.MoveBy.create(4, cc.p(0, 100));
        var goDown = goUp.reverse();
        var go = cc.MoveBy.create(8, cc.p(200, 0));
        var goBack = go.reverse();
        var seq = cc.Sequence.create(goUp, go, goDown, goBack, null);
        voidNode.runAction((cc.RepeatForever.create(seq) ));

        this.addChild(voidNode);
    },

    title:function () {
        return "Parallax: parent and 3 children";
    }
});

Parallax2 = ParallaxDemo.extend({

    _root:null,
    _target:null,
    _streak:null,


    ctor:function () {
        this.setTouchEnabled(true);

        // Top Layer, a simple image
        var cocosImage = cc.Sprite.create(s_power);
        // scale the image (optional)
        cocosImage.setScale(0.5);
        // change the transform anchor point to 0,0 (optional)
        cocosImage.setAnchorPoint(cc.p(0, 0));


        // Middle layer: a Tile map atlas
        //var tilemap = cc.TileMapAtlas.create(s_tilesPng, s_levelMapTga, 16, 16);
        var tilemap = cc.TMXTiledMap.create("res/TileMaps/orthogonal-test2.tmx");

        // change the transform anchor to 0,0 (optional)
        tilemap.setAnchorPoint(cc.p(0, 0));

        // Anti Aliased images
        //tilemap.getTexture().setAntiAliasTexParameters();


        // background layer: another image
        var background = cc.Sprite.create(s_back);
        // scale the image (optional)
        //background.setScale(1.5);
        // change the transform anchor point (optional)
        background.setAnchorPoint(cc.p(0, 0));


        // create a void node, a parent node
        var voidNode = cc.ParallaxNode.create();

        // NOW add the 3 layers to the 'void' node

        // background image is moved at a ratio of 0.4x, 0.5y
        voidNode.addChild(background, -1, cc.p(0.4, 0.5), cc.p(0,0));

        // tiles are moved at a ratio of 1.0, 1.0y
        voidNode.addChild(tilemap, 1, cc.p(1.0, 1.0), cc.p(0, 0));

        // top image is moved at a ratio of 3.0x, 2.5y
        voidNode.addChild(cocosImage, 2, cc.p(3.0, 2.5), cc.p(0, 0));
        this.addChild(voidNode, 0, TAG_NODE);

    },

    registerWithTouchDispatcher:function () {
        cc.Director.getInstance().getTouchDispatcher().addTargetedDelegate(this, 0, true);
    },
    onTouchBegan:function (touch, event) {
        return true;
    },

    onTouchMoved:function (touch, event) {
        var node = this.getChildByTag(TAG_NODE);
        var currentPos = node.getPosition();
        node.setPosition(cc.pAdd(currentPos, touch.getDelta() ));
    },

    title:function () {
        return "Parallax: drag screen";
    }
});

ParallaxTestScene = TestScene.extend({

    runThisTest:function () {
        sceneIdx = -1;
        MAX_LAYER = 2;
        var layer = nextParallaxAction();

        this.addChild(layer);
        cc.Director.getInstance().replaceScene(this);
    }
});
