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
    _sp: null,
    _spp: null,

    ctor:function () {
        this._super();
    },

    initTouchDebugDraw: function() {
        var touchListener = cc.EventListener.create({
            event: cc.EventListener.TOUCH_ONE_BY_ONE,
            swallowTouch: true,
            onTouchBegan: function (touch, event) {
                var target = event.getCurrentTarget();
                target._sp.debugDraw(true);
                target._spp.debugDraw(true);
                return true;
            },
            onTouchMoved: function (touch, event) {
                var target = event.getCurrentTarget();
                var pos = touch.getDelta();
                var newScale = cc.clampf(target._spp.getScale() + pos.x * 0.01, 0.1, 2);
                target._spp.setScale(newScale);
                target._sp.setScale(newScale);
            },
            onTouchEnded: function (touch, event) {
                var target = event.getCurrentTarget();
                target._sp.debugDraw(false);
                target._spp.debugDraw(false);
            }
        });
        cc.eventManager.addListener(touchListener, this);
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
    _title:"PolygonSprite Creation",
    _subtitle:"new cc.Sprite(jsb.AutoPolygon.generatePolygon(filename))",

    ctor:function () {
        this._super();
        this.make2Sprites();
    },
    make2Sprites: function() {
        var polygons = jsb.AutoPolygon.generatePolygon(s_pathGrossini);
        this._spp = new cc.Sprite(polygons);
        this._spp.setPosition((0.5+0.15) * winSize.width, 0.5 * winSize.height);
        this.addChild(this._spp);

        this._sp = new cc.Sprite(s_pathGrossini);
        this.addChild(this._sp);
        this._sp.setPosition((0.5-0.15) * winSize.width, 0.5 * winSize.height);

        var ttfConfig = new cc.FontDefinition({
            fontName: "fonts/arial.ttf",
            fontSize: 8
        });
        var temp = "Sprite:\nPixels drawn: ";
        var spSize = this._sp.getContentSize();
        var spArea = new cc.LabelTTF(temp+Math.round(spSize.width*spSize.height), ttfConfig);
        spArea.anchorX = 0;
        spArea.anchorY = 1;
        this._sp.addChild(spArea);
        
        temp = "PolygonSprite:\nPixels drawn: ";
        var vertCount = "\nverts:"+Math.round(polygons.getVertCount());
        var sppArea = new cc.LabelTTF(temp+Math.round(polygons.getArea())+vertCount, ttfConfig);
        sppArea.anchorX = 0;
        sppArea.anchorY = 1;
        this._spp.addChild(sppArea);
        
        this.initTouchDebugDraw();
    }
});

var SpritePolygonTest2 = SpritePolygonTestDemo.extend({
    _title:"PolygonSprite Creation with a rect",
    _subtitle:"new cc.Sprite(jsb.AutoPolygon.generatePolygon(filename, rect))",

    ctor:function(){
        this._super();
        this.make2Sprites();
    },
    make2Sprites: function() {
        var head = cc.rect(30, 25, 25, 25);
        var polygons = jsb.AutoPolygon.generatePolygon(s_pathGrossini, head);
        this._spp = new cc.Sprite(polygons);
        this._spp.setPosition((0.5+0.15) * winSize.width, 0.5 * winSize.height);
        this.addChild(this._spp);

        this._sp = new cc.Sprite(s_pathGrossini, head);
        this.addChild(this._sp);
        this._sp.setPosition((0.5-0.15) * winSize.width, 0.5 * winSize.height);

        var ttfConfig = new cc.FontDefinition({
            fontName: "fonts/arial.ttf",
            fontSize: 8
        });
        var temp = "Sprite:\nPixels drawn: ";
        var spSize = this._sp.getContentSize();
        var spArea = new cc.LabelTTF(temp+Math.round(spSize.width*spSize.height), ttfConfig);
        spArea.anchorX = 0;
        spArea.anchorY = 1;
        this._sp.addChild(spArea);
        
        temp = "PolygonSprite:\nPixels drawn: ";
        var vertCount = "\nverts:"+Math.round(polygons.getVertCount());
        var sppArea = new cc.LabelTTF(temp+Math.round(polygons.getArea())+vertCount, ttfConfig);
        sppArea.anchorX = 0;
        sppArea.anchorY = 1;
        this._spp.addChild(sppArea);
        
        this.initTouchDebugDraw();
    }
});

var SpritePolygonTestSlider = SpritePolygonTestDemo.extend({
    _title:"Optimization Value (default:2.0)",
    _subtitle:"",

    _ttfConfig: null,
    _epsilonLabel: null,

    ctor: function () {
        this._super();

        this._ttfConfig = new cc.FontDefinition({
            fontName: "fonts/arial.ttf",
            fontSize: 8
        });
        
        var vsize = cc.visibleRect;
        var slider = new ccui.Slider();
        slider.setTouchEnabled(true);
        slider.loadBarTexture("ccs-res/cocosui/sliderTrack.png");
        slider.loadSlidBallTextures("ccs-res/cocosui/sliderThumb.png", "ccs-res/cocosui/sliderThumb.png", "");
        slider.loadProgressBarTexture("ccs-res/cocosui/sliderProgress.png");
        slider.setPosition(vsize.width/2, vsize.height/4);
        
        slider.addEventListener(this.changeEpsilon, this);
        slider.setPercent(Math.sqrt(1/19) * 100);
        
        this._epsilonLabel = new cc.LabelTTF("Epsilon: 2.0", this._ttfConfig);
        this.addChild(this._epsilonLabel);
        this._epsilonLabel.setPosition(vsize.width/2, vsize.height/4 + 15);
        this.addChild(slider);
    },
    makeSprites: function (list, y) {
        var vsize = cc.visibleRect;
        var offset = (vsize.width-100)/(list.length-1);
        for(var i = 0; i < list.length; i++)
        {
            var sp = this.makeSprite(list[i], 50+offset*i, y);
            this.addChild(sp);
            sp.debugDraw(true);
        }
    },
    makeSprite: function (filename, x, y) {
        var sp = new cc.Sprite(filename);
        var quadSize = sp.getContentSize();
        var originalSize = quadSize.width * quadSize.height;
        var polygons = jsb.AutoPolygon.generatePolygon(filename);
        var ret = new cc.Sprite(polygons);
        ret.setPosition(x, y);
        
        var pixels = polygons.getArea()/originalSize*100;
        var spArea = new cc.LabelTTF(filename+"\nVerts: "+polygons.getVertCount()+ "\nPixels: "+pixels.toFixed(2)+"%", this._ttfConfig);
        ret.addChild(spArea);
        spArea.setAnchorPoint(cc.p(0,1));
        ret.setName(filename);
        ret.setAnchorPoint(cc.p(0.5, 0));
        return ret;
    },
    updateLabel: function (sp, polygons) {
        var label = sp.getChildren()[0];
        var filename = sp.getName();
        var w = polygons.rect.width/cc.director.getContentScaleFactor();
        var h = polygons.rect.width/cc.director.getContentScaleFactor();
        var pixels = polygons.getArea()/(w*h)*100;
        label.string = filename+"\nVerts: "+polygons.getVertCount()+"\nPixels: "+pixels.toFixed(2)+"%";
    },
    changeEpsilon: function (sender, type) {
        if (type == ccui.Slider.EVENT_PERCENT_CHANGED) {
            var epsilon = Math.pow(sender.getPercent()/100, 2) * 19 + 1;
            var children = this.children, child, file;
            for(var i = 0; i < children.length; i++) {
                child = children[i];
                file = child.getName();
                if(file.length) {
                    var polygons = jsb.AutoPolygon.generatePolygon(file, cc.rect(), epsilon);
                    child.setPolygonInfo(polygons);
                    child.debugDraw(true);
                    this.updateLabel(child, polygons);
                }
            }
            this._epsilonLabel.setString("Epsilon: "+ epsilon.toFixed(2));
        }
    }
});

var SpritePolygonTest3 = SpritePolygonTestSlider.extend({
    _title:"Optimization Value (default:2.0)",
    _subtitle:"",

    ctor:function(){
        this._super();

        var vsize = cc.visibleRect;
        var list = [
            "Images/arrows.png",
            "Images/CyanTriangle.png",
            s_pathB2,
            "Images/elephant1_Diffuse.png"
        ];
        this.makeSprites(list, vsize.height/2);
    }
});

var SpritePolygonTest4 = SpritePolygonTestSlider.extend({
    _title:"Optimization Value (default:2.0)",
    _subtitle: "",

    ctor:function(){
        this._super();

        var vsize = cc.visibleRect;
        var list = [
            s_pathGrossini,
            "Images/grossinis_sister1.png",
            "Images/grossinis_sister2.png"
        ];
        this.makeSprites(list, vsize.height/2);
    }

});

var SpritePolygonPerformance = SpritePolygonTestDemo.extend({
    spriteCount: 0,
    vertCount: 0,
    triCount: 0,
    pixelCount: 0,
    elapsedTime: 0,
    perfLabel: null,
    continuousLowDt: 0,
    continuousHighDtTime: 0,
    waitingTime: 0,
    _posX: 0,
    _posY: 0,
    _leftX: 0,
    _rightX: 0,
    goRight: true,
    ended: false,
    prevDt: 0,
    _incVert: 0,
    _incTri: 0,
    _incPix: 0,
    ctor: function () {
        this._super();
        var ttfConfig = new cc.FontDefinition({
            fontName: "fonts/arial.ttf",
            fontSize: 10
        });
        this.perfLabel = new cc.LabelTTF("Performance test", ttfConfig);
        this.addChild(this.perfLabel);
        this.perfLabel.setPosition(cc.visibleRect.width/2, 80);
        
        var size = cc.visibleRect;
        this._posX = this._leftX = size.width*0.15;
        this._rightX = size.width*0.85;
        this._posY = size.height/2;
        this.prevDt = 0.016;
        this.goRight = true;
        this.ended = false;
        this.scheduleUpdate();
    },
    updateLabel: function () {
        var temp = "Nodes: "+this.spriteCount+" Triangles: "+this.triCount+"\nPixels: "+this.pixelCount.toFixed(2)+" Vertices: "+this.vertCount;
        if(!this.ended)
            this.perfLabel.string = temp;
    },
    makeSprite: function () {
        return new cc.Node();
    },
    update: function (dt) {
        dt = dt*0.3 + this.prevDt*0.7;
        this.prevDt = dt;
        this.elapsedTime += dt;
        var loops = (0.025-dt)*1000;
        if(dt < 0.025 && loops>0)
        {
            this.continuousHighDtTime = cc.clampf(this.continuousHighDtTime-dt*2, 0.0, 1.0);
            this.waitingTime = cc.clampf(this.waitingTime-dt, 0.0, 5.0);
            this.continuousLowDt++;
        }
        else
        {
            this.continuousHighDtTime+=dt;
            this.continuousLowDt = 0;
        }
        if (this.continuousLowDt >= 5 && loops > 0) {
            for(var i = 0; i < loops; i++)
            {
                if(this._posX >= this._rightX)
                {
                    this.goRight = false;
                }
                else if(this._posX <= this._leftX)
                {
                    this.goRight = true;
                }
                var s = this.makeSprite();
                this.addChild(s);
                s.setPosition(this._posX, this._posY);
                if(this.goRight)
                    this._posX++;
                else
                    this._posX--;
                
                this.incrementStats();
            }
            this.updateLabel();
        }

        //if we have 10 continuous low dt, then we will start to create more sprites
        else if(this.continuousHighDtTime >= 0.5 || this.waitingTime > 3.0){
            // its now 1 seconds with high DT time, time to end
            this.ended = true;
            this.unscheduleUpdate();
            this.perfLabel.string = "Test ended in " + this.elapsedTime + " seconds\nNodes: " + this.spriteCount + "   Triangles: " + this.triCount + "\nPixels: " + this.pixelCount.toFixed() + "   Vertices: " + this.vertCount;
            this.getChildByTag(BASE_TEST_SUBTITLE_TAG).string = "Test ended";
        }
        else{
            this.waitingTime += dt;
        }
    },
    incrementStats: function () {
        this.spriteCount ++;
        this.vertCount += this._incVert;
        this.triCount += this._incTri;
        this.pixelCount += this._incPix;
    }
});

var SpritePolygonPerformanceTestDynamic = SpritePolygonPerformance.extend({
    _title: "Dynamic SpritePolygon Performance",
    _subtitle: "Test running, please wait until it ends",
    _polygons: null,
    ctor: function () {
        this._super();
        this._polygons = jsb.AutoPolygon.generatePolygon(s_pathGrossini);
        this.initIncrementStats();
    },
    initIncrementStats: function () {
        this._incVert = this._polygons.getVertCount();
        this._incTri = this._polygons.getTrianglesCount();
        this._incPix = this._polygons.getArea();
    },
    makeSprite: function () {
        var ret = new cc.Sprite(this._polygons);
        ret.runAction(cc.rotateBy(1,360).repeatForever());
        return ret;
    }
});

var SpritePerformanceTestDynamic = SpritePolygonPerformance.extend({
    _title: "Dynamic Sprite Performance",
    _subtitle: "Test running, please wait until it ends",
    ctor: function () {
        this._super();
        this.initIncrementStats();
    },
    initIncrementStats: function () {
        var t = new cc.Sprite(s_pathGrossini);
        this._incVert = 4;
        this._incTri = 2;
        this._incPix = t.width * t.height;
    },
    makeSprite: function () {
        var ret = new cc.Sprite(s_pathGrossini);
        ret.runAction(cc.rotateBy(1,360).repeatForever());
        return ret;
    }
});

//
// Flow control
//
var arrayOfSpritePolygonTest = [
    SpritePolygonTest1,
    SpritePolygonTest2,
    SpritePolygonTest3,
    SpritePolygonTest4,
    SpritePolygonPerformanceTestDynamic,
    SpritePerformanceTestDynamic
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
