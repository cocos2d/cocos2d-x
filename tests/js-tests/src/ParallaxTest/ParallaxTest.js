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
var TAG_NODE = 9960;

var parallaxTestSceneIdx = -1;

ParallaxDemo = BaseTestLayer.extend({
    _atlas:null,
    ctor:function() {
        this._super(cc.color(0,0,0,255), cc.color(160,32,32,255));
    },

    title:function () {
        return "No title";
    },

    onBackCallback:function (sender) {
        var s = new ParallaxTestScene();
        s.addChild(previousParallaxTest());
        director.runScene(s);
    },

    onRestartCallback:function (sender) {
        var s = new ParallaxTestScene();
        s.addChild(restartParallaxTest());
        director.runScene(s);
    },

    onNextCallback:function (sender) {
        var s = new ParallaxTestScene();
        s.addChild(nextParallaxTest());
        director.runScene(s);
    },
    // automation
    numberOfPendingTests:function() {
        return ( (arrayOfParallaxTest.length-1) - parallaxTestSceneIdx );
    },

    getTestNumber:function() {
        return parallaxTestSceneIdx;
    }

});

var Parallax1 = ParallaxDemo.extend({
    _parentNode:null,
    _background:null,
    _tilemap:null,
    _cocosimage:null,

    ctor:function () {
        this._super();

        // Top Layer, a simple image
        this._cocosimage = new cc.Sprite(s_power);
        // scale the image (optional)
        this._cocosimage.scale = 1.5;
        // change the transform anchor point to 0,0 (optional)
        this._cocosimage.anchorX = 0;
        this._cocosimage.anchorY = 0;

        // Middle layer: a Tile map atlas
        //var tilemap = cc.TileMapAtlas.create(s_tilesPng, s_levelMapTga, 16, 16);
        this._tilemap = new cc.TMXTiledMap(s_resprefix + "TileMaps/orthogonal-test2.tmx");

        // change the transform anchor to 0,0 (optional)
        this._tilemap.anchorX = 0;
        this._tilemap.anchorY = 0;

        // Anti Aliased images
        //tilemap.texture.setAntiAliasTexParameters();

        // background layer: another image
        this._background = new cc.Sprite(s_back);
        // scale the image (optional)
        //background.scale = 1.5;
        // change the transform anchor point (optional)
        this._background.anchorX = 0;
        this._background.anchorY = 0;

        // create a void node, a parent node
        this._parentNode = new cc.ParallaxNode();

        // NOW add the 3 layers to the 'void' node

        // background image is moved at a ratio of 0.4x, 0.5y
        this._parentNode.addChild(this._background, -1, cc.p(0.4, 0.5), cc.p(0,0));

        // tiles are moved at a ratio of 2.2x, 1.0y
        this._parentNode.addChild(this._tilemap, 1, cc.p(2.2, 1.0), cc.p(0, 0));

        // top image is moved at a ratio of 3.0x, 2.5y
        this._parentNode.addChild(this._cocosimage, 2, cc.p(3.0, 2.5), cc.p(0, 0));

        // now create some actions that will move the '_parent' node
        // and the children of the '_parent' node will move at different
        // speed, thus, simulation the 3D environment
        var goUp = cc.moveBy(2, cc.p(0, 100));
        var goRight = cc.moveBy(2, cc.p(200, 0));
        var delay = cc.delayTime(2.0);
        var goDown = goUp.reverse();
        var goLeft = goRight.reverse();
        var seq = cc.sequence(goUp, goRight, delay, goDown, goLeft);
        this._parentNode.runAction(seq.repeatForever());

        this.addChild(this._parentNode);
    },

    title:function () {
        return "Parallax: parent and 3 children";
    },

    // default values for automation
    testDuration:5,
    getExpectedResult:function() {
        var ret = {};
        ret.pos_parent = cc.p(200,100);
        ret.pos_child1 = cc.p(-120, -50);
        ret.pos_child2 = cc.p(240, 0);
        ret.pos_child3 = cc.p(400, 150);

        return JSON.stringify(ret);
    },

    getCurrentResult:function() {
        var ret = {};
        ret.pos_parent = cc.p(Math.round(this._parentNode.x), Math.round(this._parentNode.y));
        ret.pos_child1 = cc.p(Math.round(this._background.x), Math.round(this._background.y));
        ret.pos_child2 = cc.p(Math.round(this._tilemap.x), Math.round(this._tilemap.y));
        ret.pos_child3 = cc.p(Math.round(this._cocosimage.x), Math.round(this._cocosimage.y));

        return JSON.stringify(ret);
    }
});

var Parallax2 = ParallaxDemo.extend({
    _root:null,
    _target:null,
    _streak:null,
    ctor:function () {
        this._super();

        if( 'touches' in cc.sys.capabilities ){
            cc.eventManager.addListener({
                event: cc.EventListener.TOUCH_ALL_AT_ONCE,
                onTouchesMoved:function (touches, event) {
                    var touch = touches[0];
                    var node = event.getCurrentTarget().getChildByTag(TAG_NODE);
                    node.x += touch.getDelta().x;
                    node.y += touch.getDelta().y;
                }
            }, this);
        } else if ('mouse' in cc.sys.capabilities ){
            cc.eventManager.addListener({
                event: cc.EventListener.MOUSE,
                onMouseMove: function(event){
                    if(event.getButton() == cc.EventMouse.BUTTON_LEFT){
                        var node = event.getCurrentTarget().getChildByTag(TAG_NODE);
                        node.x += event.getDeltaX();
                        node.y += event.getDeltaY();
                    }
                }
            }, this);
        }


        // Top Layer, a simple image
        var cocosImage = new cc.Sprite(s_power);
        // scale the image (optional)
        cocosImage.scale = 1.5;
        // change the transform anchor point to 0,0 (optional)
        cocosImage.anchorX = 0;
        cocosImage.anchorY = 0;

        // Middle layer: a Tile map atlas
        //var tilemap = cc.TileMapAtlas.create(s_tilesPng, s_levelMapTga, 16, 16);
        var tilemap = new cc.TMXTiledMap(s_resprefix + "TileMaps/orthogonal-test2.tmx");

        // change the transform anchor to 0,0 (optional)
        tilemap.anchorX = 0;
        tilemap.anchorY = 0;

        // Anti Aliased images
        //tilemap.texture.setAntiAliasTexParameters();

        // background layer: another image
        var background = new cc.Sprite(s_back);
        // scale the image (optional)
        //background.scale = 1.5;
        // change the transform anchor point (optional)
        background.anchorX = 0;
        background.anchorY = 0;

        // create a void node, a parent node
        var voidNode = new cc.ParallaxNode();
        // NOW add the 3 layers to the 'void' node

        // background image is moved at a ratio of 0.4x, 0.5y
        voidNode.addChild(background, -1, cc.p(0.4, 0.5), cc.p(0,0));

        // tiles are moved at a ratio of 1.0, 1.0y
        voidNode.addChild(tilemap, 1, cc.p(1.0, 1.0), cc.p(0, 0));

        // top image is moved at a ratio of 3.0x, 2.5y
        voidNode.addChild(cocosImage, 2, cc.p(3.0, 2.5), cc.p(0, 0));
        this.addChild(voidNode, 0, TAG_NODE);
    },

    title:function () {
        return "Parallax: drag screen";
    }
});

ParallaxTestScene = TestScene.extend({
    runThisTest:function (num) {
        parallaxTestSceneIdx = (num || num == 0) ? (num - 1) : -1;
        this.addChild(nextParallaxTest());
        director.runScene(this);
    }
});

var arrayOfParallaxTest = [
    Parallax1,
    Parallax2
];

var nextParallaxTest = function () {
    parallaxTestSceneIdx++;
    parallaxTestSceneIdx = parallaxTestSceneIdx % arrayOfParallaxTest.length;

    return new arrayOfParallaxTest[parallaxTestSceneIdx]();
};
var previousParallaxTest = function () {
    parallaxTestSceneIdx--;
    if (parallaxTestSceneIdx < 0)
        parallaxTestSceneIdx += arrayOfParallaxTest.length;

    return new arrayOfParallaxTest[parallaxTestSceneIdx]();
};
var restartParallaxTest = function () {
    return new arrayOfParallaxTest[parallaxTestSceneIdx]();
};
