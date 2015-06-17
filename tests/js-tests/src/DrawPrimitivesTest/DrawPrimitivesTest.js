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

var drawTestSceneIdx = -1;

//------------------------------------------------------------------
//
// DrawTestDemo
//
//------------------------------------------------------------------
var DrawTestDemo = BaseTestLayer.extend({
    _title:"",
    _subtitle:"",

    ctor:function() {
        this._super(cc.color(0,0,0,255), cc.color(98,99,117,255));
    },

    onRestartCallback:function (sender) {
        var s = new DrawPrimitivesTestScene();
        s.addChild(restartDrawTest());
        director.runScene(s);
    },
    onNextCallback:function (sender) {
        var s = new DrawPrimitivesTestScene();
        s.addChild(nextDrawTest());
        director.runScene(s);
    },
    onBackCallback:function (sender) {
        var s = new DrawPrimitivesTestScene();
        s.addChild(previousDrawTest());
        director.runScene(s);
    },
    // automation
    numberOfPendingTests:function() {
        return ( (arrayOfDrawTest.length-1) - drawTestSceneIdx );
    },

    getTestNumber:function() {
        return drawTestSceneIdx;
    }

});

//------------------------------------------------------------------
//
// Testing cc.DrawNode API 2
//
//------------------------------------------------------------------
var DrawNewAPITest2 = DrawTestDemo.extend({
    _title: "cc.DrawNode",
    _subtitle: "Testing cc.DrawNode API 2",
    ctor: function () {
        //----start0----ctor
        this._super();
        var draw = new cc.DrawNode();
        this.addChild(draw, 10);
        var winSize = cc.director.getWinSize();
        var centerPos = cc.p(winSize.width / 2, winSize.height / 2);
        //drawSegment
        draw.drawSegment(cc.p(0, 0), cc.p(winSize.width, winSize.height), 1, cc.color(255, 255, 255, 255));
        draw.drawSegment(cc.p(0, winSize.height), cc.p(winSize.width, 0), 5, cc.color(255, 0, 0, 255));

        //drawDot
        draw.drawDot(cc.p(winSize.width / 2, winSize.height / 2), 40, cc.color(0, 0, 255, 128));
        var points = [cc.p(60, 60), cc.p(70, 70), cc.p(60, 70), cc.p(70, 60)];
        for (var i = 0; i < points.length; i++) {
            draw.drawDot(points[i], 4, cc.color(0, 255, 255, 255));
        }
        //drawCircle
        draw.drawCircle(cc.p(winSize.width / 2, winSize.height / 2), 100, 0, 10, false, 6, cc.color(0, 255, 0, 255));
        draw.drawCircle(cc.p(winSize.width / 2, winSize.height / 2), 50, cc.degreesToRadians(90), 50, true, 2, cc.color(0, 255, 255, 255));

        //draw poly
        //not fill
        var vertices = [cc.p(0, 0), cc.p(50, 50), cc.p(100, 50), cc.p(100, 100), cc.p(50, 100) ];
        draw.drawPoly(vertices, null, 5, cc.color(255, 255, 0, 255));
        var vertices2 = [cc.p(30, 130), cc.p(30, 230), cc.p(50, 200)];
        draw.drawPoly(vertices2, null, 2, cc.color(255, 0, 255, 255));
        //fill
        var vertices3 = [cc.p(60, 130), cc.p(60, 230), cc.p(80, 200)];
        draw.drawPoly(vertices3, cc.color(0, 255, 255, 50), 2, cc.color(255, 0, 255, 255));

        //draw rect
        //not fill
        draw.drawRect(cc.p(120, 120), cc.p(200, 200), null, 2, cc.color(255, 0, 255, 255));
        //fill
        draw.drawRect(cc.p(120, 220), cc.p(200, 300), cc.color(0, 255, 255, 50), 2, cc.color(128, 128, 0, 255));

        // draw quad bezier path
        draw.drawQuadBezier(cc.p(0, winSize.height), cc.p(centerPos.x, centerPos.y), cc.p(winSize.width, winSize.height), 50, 2, cc.color(255, 0, 255, 255));

        // draw cubic bezier path
        draw.drawCubicBezier(cc.p(winSize.width / 2, winSize.height / 2), cc.p(winSize.width / 2 + 30, winSize.height / 2 + 50),
            cc.p(winSize.width / 2 + 60, winSize.height / 2 - 50), cc.p(winSize.width, winSize.height / 2), 100, 2, cc.color(255, 0, 255, 255));

        //draw cardinal spline
        var vertices4 = [
            cc.p(centerPos.x - 130, centerPos.y - 130),
            cc.p(centerPos.x - 130, centerPos.y + 130),
            cc.p(centerPos.x + 130, centerPos.y + 130),
            cc.p(centerPos.x + 130, centerPos.y - 130),
            cc.p(centerPos.x - 130, centerPos.y - 130)
        ];
        draw.drawCardinalSpline(vertices4, 0.5, 100, 2, cc.color(255, 255, 255, 255));
        //----end0----
    }
});
DrawNewAPITest2.prototype.title = function(){
    return 'cc.DrawNode 2';
};

//------------------------------------------------------------------
//
// Draw New API Test
//
//------------------------------------------------------------------
var DrawNewAPITest = DrawTestDemo.extend({
    _title : "cc.DrawNode",
    _subtitle : "Testing cc.DrawNode API",

    ctor:function() {
        //----start1----ctor
        this._super();

        var draw = new cc.DrawNode();
        this.addChild(draw, 10);
        //
        // Circles
        //
        for( var i=0; i < 10; i++) {
            draw.drawDot( cc.p(winSize.width/2, winSize.height/2), 10*(10-i), cc.color( Math.random()*255, Math.random()*255, Math.random()*255, 255) );
        }

        //
        // Polygons
        //
        var points = [ cc.p(winSize.height/4,0), cc.p(winSize.width,winSize.height/5), cc.p(winSize.width/3*2,winSize.height) ];
        draw.drawPoly(points, cc.color(255,0,0,128), 8, cc.color(0,128,128,255) );

        // star poly (triggers bugs)
        var o=80;
        var w=20;
        var h=50;
        var star = [
            cc.p(o+w,o-h), cc.p(o+w*2, o),                  // lower spike
            cc.p(o + w*2 + h, o+w ), cc.p(o + w*2, o+w*2),  // right spike
            cc.p(o +w, o+w*2+h), cc.p(o,o+w*2),             // top spike
            cc.p(o -h, o+w), cc.p(o,o)                     // left spike
        ];
        draw.drawPoly(star, cc.color(255,0,0,128), 2, cc.color(0,0,255,255) );

        // star poly (doesn't trigger bug... order is important un tesselation is supported.
        o=180;
        w=20;
        h=50;
        star = [
            cc.p(o,o), cc.p(o+w,o-h), cc.p(o+w*2, o),       // lower spike
            cc.p(o + w*2 + h, o+w ), cc.p(o + w*2, o+w*2),  // right spike
            cc.p(o +w, o+w*2+h), cc.p(o,o+w*2),             // top spike
            cc.p(o -h, o+w)                                 // left spike
        ];
        draw.drawPoly(star, cc.color(255,0,0,128), 2, cc.color(0,0,255,255) );

        //
        // Segments
        //
        draw.drawSegment( cc.p(20,winSize.height), cc.p(20,winSize.height/2), 10, cc.color(0, 255, 0, 255) );
        draw.drawSegment( cc.p(10,winSize.height/2), cc.p(winSize.width/2, winSize.height/2), 40, cc.color(255, 0, 255, 128) );
        //----end1----
    }
});

DrawNewAPITest.prototype.title = function(){
    return 'cc.DrawNode 1';
};

//
//
var DrawPrimitivesTestScene = TestScene.extend({
    runThisTest:function (num) {
        drawTestSceneIdx = (num || num == 0) ? (num - 1) : -1;
        var layer = nextDrawTest();
        this.addChild(layer);

        director.runScene(this);
    }
});

//
// Flow control
//

var arrayOfDrawTest = [
    DrawNewAPITest,
    DrawNewAPITest2
];

var nextDrawTest = function () {
    drawTestSceneIdx++;
    drawTestSceneIdx = drawTestSceneIdx % arrayOfDrawTest.length;

    if(window.sideIndexBar){
        drawTestSceneIdx = window.sideIndexBar.changeTest(drawTestSceneIdx, 9);
    }

    return new arrayOfDrawTest[drawTestSceneIdx]();
};
var previousDrawTest = function () {
    drawTestSceneIdx--;
    if (drawTestSceneIdx < 0)
        drawTestSceneIdx += arrayOfDrawTest.length;

    if(window.sideIndexBar){
        drawTestSceneIdx = window.sideIndexBar.changeTest(drawTestSceneIdx, 9);
    }

    return new arrayOfDrawTest[drawTestSceneIdx]();
};
var restartDrawTest = function () {
    return new arrayOfDrawTest[drawTestSceneIdx]();
};

