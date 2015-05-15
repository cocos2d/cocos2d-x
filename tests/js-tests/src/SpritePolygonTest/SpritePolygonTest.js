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
var SpritePolygonTestIdx = -1;

var SpritePolygonTestDemo = BaseTestLayer.extend({
    _title:"",
    _subtitle:"",
    _debugDraw:null,

    ctor:function () {
        this._super();
    },

    initDefaultSprite:function(filename, inst){
        cc.director.setClearColor(cc.color(102/255, 184/255, 204/255, 255/255));
        this.addChild(inst);

        var s = cc.director.getWinSize();
        inst.setPosition(s.width/2 + 0.15*s.width, s.height/2);

        var sp = new cc.Sprite(filename);
        this.addChild(sp);
        sp.setPosition(s.width/2 - 0.15*s.width, s.height/2);

        this._debugDraw = new cc.DrawNode();
        sp.addChild(this._debugDraw);

        var self = this;
        cc.eventManager.addListener({
            event:cc.EventListener.TOUCH_ONE_BY_ONE,
            onTouchBegan:function(){
                inst.showDebug(true);
                self._debugDraw.setVisible(true);
                return true;
            },
            onTouchEnded:function(){
                inst.showDebug(false);
                self._debugDraw.setVisible(false);
            }
        }, this);

        var positions = new Array(4);
        var spSize = sp.getContentSize();
        positions[0] = cc.p(0, spSize.height);
        positions[1] = cc.p(spSize.width, spSize.height);
        positions[2] = cc.p(spSize.width, 0);
        positions[3] = cc.p(0, 0);

        this._debugDraw.drawSegment(positions[0], positions[1], 1, cc.color.GREEN);
        this._debugDraw.drawSegment(positions[1], positions[2], 1, cc.color.GREEN);
        this._debugDraw.drawSegment(positions[2], positions[3], 1, cc.color.GREEN);
        this._debugDraw.drawSegment(positions[3], positions[0], 1, cc.color.GREEN);
        this._debugDraw.drawSegment(positions[0], positions[2], 1, cc.color.GREEN);

        this._debugDraw.setVisible(false);

        var label1 = new cc.LabelTTF("Sprite:\nPixels drawn:"+spSize.width*spSize.height, "fonts/arial.ttf", 10);
        sp.addChild(label1);
        label1.setAnchorPoint(cc.p(0, 1));

        var label2 = new cc.LabelTTF("SpritePolygon:\nPixels drawn:"+(inst.getArea()+inst.getVertCount()), "fonts/arial.ttf", 10);
        inst.addChild(label2);
        label2.setAnchorPoint(cc.p(0, 1));

    },

    onRestartCallback:function (sender) {
        var s = new SpritePolygonTestScene();
        s.addChild(restartSpritePolygonTest());
        director.runScene(s);
    },

    onNextCallback:function (sender) {
        var s = new SpritePolygonTestScene();
        s.addChild(nextSpritePolygonTest());
        director.runScene(s);
    },

    onBackCallback:function (sender) {
        var s = new SpritePolygonTestScene();
        s.addChild(previousSpritePolygonTest());
        director.runScene(s);
    }
});

var SpritePolygonTestScene = cc.Scene.extend({
    ctor:function () {
        this._super();

        var label = new cc.LabelTTF("Main Menu", "Arial", 20);
        var menuItem = new cc.MenuItemLabel(label, this.onMainMenuCallback, this);

        var menu = new cc.Menu(menuItem);
        menu.x = 0;
        menu.y = 0;
        menuItem.x = winSize.width - 50;
        menuItem.y = 25;
        this.addChild(menu, 99);
    },
    onMainMenuCallback:function () {
        var scene = new cc.Scene();
        var layer = new TestController();
        scene.addChild(layer);
        director.runScene(scene);
    },
    runThisTest:function (num) {
        SpritePolygonTestIdx = (num || num == 0) ? (num - 1) : -1;
        var layer = nextSpritePolygonTest();
        this.addChild(layer);

        director.runScene(this);
    }
});

var SpritePolygonTest1 = SpritePolygonTestDemo.extend({
    _title:"SpritePolygon Creation",
    _subtitle:"SpritePolygon::create(\"Images/grossini.png\")",

    ctor:function(){
        this._super();

        var s = ccexp.SpritePolygon.create(s_pathGrossini);
        this.initDefaultSprite(s_pathGrossini, s);
    }
});

var SpritePolygonTest2 = SpritePolygonTestDemo.extend({
    _title:"SpritePolygon Creation",
    _subtitle:"SpritePolygon::create(\"Images/grossini.png\", verts)",

    ctor:function(){
        this._super();

        var verts = [];
        verts.push(cc.p(36.5, 242.0-128.5));
        verts.push(cc.p(27.5, 242.0-133.5));
        verts.push(cc.p(24.5, 242.0-145.5));
        verts.push(cc.p(26.5, 242.0-161.5));
        verts.push(cc.p(33.5, 242.0-168.5));
        verts.push(cc.p(27.5, 242.0-168.5));
        verts.push(cc.p(16.5, 242.0-179.5));
        verts.push(cc.p(30.5, 242.0-197.5));
        verts.push(cc.p(28.5, 242.0-237.5));
        verts.push(cc.p(56.5, 242.0-237.5));
        verts.push(cc.p(54.5, 242.0-197.5));
        verts.push(cc.p(68.5, 242.0-184.5));
        verts.push(cc.p(57.5, 242.0-168.5));
        verts.push(cc.p(51.5, 242.0-168.5));
        verts.push(cc.p(60.5, 242.0-154.5));
        verts.push(cc.p(57.5, 242.0-133.5));
        verts.push(cc.p(48.5, 242.0-127.5));
        verts.push(cc.p(36.5, 242.0-127.5));

        cc.SpritePolygonCache.getInstance().removeAllSpritePolygonCache();
        var s = ccexp.SpritePolygon.create(s_pathGrossini, verts);
        this.initDefaultSprite(s_pathGrossini, s);
    }
});

var SpritePolygonTest3 = SpritePolygonTestDemo.extend({
    _title:"SpritePolygon Creation",
    _subtitle:"SpritePolygon::create(\"Images/grossini.png\", verts, indices)",

    ctor:function(){
        this._super();

        var verts = [];
        verts.push(cc.p(33.500000, 73.500000));
        verts.push(cc.p(27.500000, 73.500000));
        verts.push(cc.p(16.500000, 62.500000));
        verts.push(cc.p(30.500000, 44.500000));
        verts.push(cc.p(54.500000, 44.500000));
        verts.push(cc.p(51.500000, 73.500000));
        verts.push(cc.p(60.500000, 87.500000));
        verts.push(cc.p(26.500000, 80.500000));
        verts.push(cc.p(24.500000, 96.500000));
        verts.push(cc.p(57.500000, 108.500000));
        verts.push(cc.p(36.500000, 113.500000));
        verts.push(cc.p(48.500000, 114.500000));
        verts.push(cc.p(36.500000, 114.500000));
        verts.push(cc.p(27.500000, 108.500000));
        verts.push(cc.p(68.500000, 57.500000));
        verts.push(cc.p(57.500000, 73.500000));
        verts.push(cc.p(56.500000, 4.500000));
        verts.push(cc.p(28.500000, 4.500000));

        var indices = [0, 1, 2, 3, 0, 2, 4, 0, 3, 5, 0, 4, 5, 6, 0, 0, 6, 7, 8, 7, 6, 6, 9, 8, 9, 10, 8, 9, 11, 10, 11, 12, 10, 8, 10, 13, 14, 5, 4, 15, 5, 14, 4, 3, 16, 3, 17, 16];

        cc.SpritePolygonCache.getInstance().removeAllSpritePolygonCache();
        var s = ccexp.SpritePolygon.create(s_pathGrossini, verts, indices);
        this.initDefaultSprite(s_pathGrossini, s);
    }
});

var SpritePolygonTest4 = SpritePolygonTestDemo.extend({
    _title:"SpritePolygon Creation",
    _subtitle: "SpritePolygon::create(\"Images/grossini.png\", \n\tvector<V3F_C4B_T2F> v, vector<unsigned short> indices)",

    ctor:function(){
        this._super();

        var vec3 = [];
        vec3.push(cc.math.vec3(33.500000, 73.500000,0));
        vec3.push(cc.math.vec3(27.500000, 73.500000,0));
        vec3.push(cc.math.vec3(16.500000, 62.500000,0));
        vec3.push(cc.math.vec3(30.500000, 44.500000,0));
        vec3.push(cc.math.vec3(54.500000, 44.500000,0));
        vec3.push(cc.math.vec3(51.500000, 73.500000,0));
        vec3.push(cc.math.vec3(60.500000, 87.500000,0));
        vec3.push(cc.math.vec3(26.500000, 80.500000,0));
        vec3.push(cc.math.vec3(24.500000, 96.500000,0));
        vec3.push(cc.math.vec3(57.500000, 108.500000,0));
        vec3.push(cc.math.vec3(36.500000, 113.500000,0));
        vec3.push(cc.math.vec3(48.500000, 114.500000,0));
        vec3.push(cc.math.vec3(36.500000, 114.500000,0));
        vec3.push(cc.math.vec3(27.500000, 108.500000,0));
        vec3.push(cc.math.vec3(68.500000, 57.500000,0));
        vec3.push(cc.math.vec3(57.500000, 73.500000,0));
        vec3.push(cc.math.vec3(56.500000, 4.500000,0));
        vec3.push(cc.math.vec3(28.500000, 4.50000, 0));

        var t2f = [];
        t2f.push(cc.p(0.394118, 0.392562));
        t2f.push(cc.p(0.323529, 0.392562));
        t2f.push(cc.p(0.194118, 0.483471));
        t2f.push(cc.p(0.358824, 0.632231));
        t2f.push(cc.p(0.641176, 0.632231));
        t2f.push(cc.p(0.605882, 0.392562));
        t2f.push(cc.p(0.711765, 0.276859));
        t2f.push(cc.p(0.311765, 0.334711));
        t2f.push(cc.p(0.288235, 0.202479));
        t2f.push(cc.p(0.676471, 0.103306));
        t2f.push(cc.p(0.429412, 0.061983));
        t2f.push(cc.p(0.570588, 0.053719));
        t2f.push(cc.p(0.429412, 0.053719));
        t2f.push(cc.p(0.323529, 0.103306));
        t2f.push(cc.p(0.805882, 0.524793));
        t2f.push(cc.p(0.676471, 0.392562));
        t2f.push(cc.p(0.664706, 0.962810));
        t2f.push(cc.p(0.335294, 0.962810));

        var verts = [];
        for(var i = 0; i < 18; ++i)
        {
            var t = {
                v3f:vec3[i],
                c4b:cc.color.WHITE,
                t2f:t2f[i]
            };
            verts.push(t);
        }
        var indices = [0, 1, 2, 3, 0, 2, 4, 0, 3, 5, 0, 4, 5, 6, 0, 0, 6, 7, 8, 7, 6, 6, 9, 8, 9, 10, 8, 9, 11, 10, 11, 12, 10, 8, 10, 13, 14, 5, 4, 15, 5, 14, 4, 3, 16, 3, 17, 16];

        cc.SpritePolygonCache.getInstance().removeAllSpritePolygonCache();
        var s = ccexp.SpritePolygon.create(s_pathGrossini, verts, indices);
        this.initDefaultSprite(s_pathGrossini, s);
    }

})
//
// Flow control
//
var arrayOfSpritePolygonTest = [
    SpritePolygonTest1,
    SpritePolygonTest2,
    SpritePolygonTest3,
    SpritePolygonTest4
];

var nextSpritePolygonTest = function () {
    SpritePolygonTestIdx++;
    SpritePolygonTestIdx = SpritePolygonTestIdx % arrayOfSpritePolygonTest.length;

    if(window.sideIndexBar){
        SpritePolygonTestIdx = window.sideIndexBar.changeTest(SpritePolygonTestIdx, 36);
    }

    return new arrayOfSpritePolygonTest[SpritePolygonTestIdx ]();
};
var previousSpritePolygonTest = function () {
    SpritePolygonTestIdx--;
    if (SpritePolygonTestIdx < 0)
        SpritePolygonTestIdx += arrayOfSpritePolygonTest.length;

    if(window.sideIndexBar){
        SpritePolygonTestIdx = window.sideIndexBar.changeTest(SpritePolygonTestIdx, 36);
    }

    return new arrayOfSpritePolygonTest[SpritePolygonTestIdx ]();
};
var restartSpritePolygonTest = function () {
    return new arrayOfSpritePolygonTest[SpritePolygonTestIdx ]();
};
