/****************************************************************************
 Copyright (c) 2010-2013 cocos2d-x.org
 Copyright (c) 2008-2010 Ricardo Quesada
 Copyright (c) 2012 Pierre-David Bélanger

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

var TAG_TITLELABEL = 1;
var TAG_SUBTITLELABEL = 2;
var TAG_STENCILNODE = 100;
var TAG_CLIPPERNODE = 101;
var TAG_CONTENTNODE = 102;

var clippingNodeTestSceneIdx = -1;

var BaseClippingNodeTest = BaseTestLayer.extend({
    _title:"",
    _subtitle:"",

    ctor:function() {
        this._super(cc.color(0,0,0,255), cc.color(98,99,117,255));
        this.setup();
    },

    onRestartCallback:function (sender) {
        var s = new ClippingNodeTestScene();
        s.addChild(restartClippingNodeTest());
        director.runScene(s);
    },
    onNextCallback:function (sender) {
        var s = new ClippingNodeTestScene();
        s.addChild(nextClippingNodeTest());
        director.runScene(s);
    },
    onBackCallback:function (sender) {
        var s = new ClippingNodeTestScene();
        s.addChild(previousClippingNodeTest());
        director.runScene(s);
    },
    // automation
    numberOfPendingTests:function() {
        return ( (arrayOfClippingNodeTest.length-1) - clippingNodeTestSceneIdx );
    },

    getTestNumber:function() {
        return clippingNodeTestSceneIdx;
    }

});



var BasicTest = BaseClippingNodeTest.extend({
    title:function () {
        return "Basic Test";
    },

    subtitle:function () {
        return "";
    },

    setup:function () {
        var winSize = cc.director.getWinSize();

        var stencil = this.stencil();
        stencil.tag = TAG_STENCILNODE;
        stencil.x = 50;
        stencil.y = 50;

        var clipper = this.clipper();
        clipper.tag = TAG_CLIPPERNODE;
        clipper.anchorX = 0.5;
        clipper.anchorY = 0.5;
        clipper.x = winSize.width / 2 - 50;
        clipper.y = winSize.height / 2 - 50;
        clipper.stencil = stencil;
        this.addChild(clipper);

        var content = this.content();
        content.x = 50;
        content.y = 50;
        clipper.addChild(content);
        //content.x = 400;
        //content.y = 225;
        //this.addChild(content);
    },

    actionRotate:function () {
        return cc.rotateBy(1.0, 90.0).repeatForever();
    },

    actionScale:function () {
        var scale = cc.scaleBy(1.33, 1.5);
        return cc.sequence(scale, scale.reverse()).repeatForever();
    },

    shape:function () {
        var shape = new cc.DrawNode();
        var triangle = [cc.p(-100, -100),cc.p(100, -100), cc.p(0, 100)];

        var green = cc.color(0, 255, 0, 255);
        shape.drawPoly(triangle, green, 3, green);
        return shape;
    },

    grossini:function () {
        var grossini = new cc.Sprite(s_pathGrossini);
        grossini.scale = 1.5;
        return grossini;
    },

    stencil:function () {
        return null;
    },

    clipper:function () {
        return new cc.ClippingNode();
    },

    content:function () {
        return null;
    }
});

var ShapeTest = BasicTest.extend({
    title:function () {
        return "Shape Basic Test";
    },

    subtitle:function () {
        return "A DrawNode as stencil and Sprite as content";
    },

    stencil:function () {
        var node = this.shape();
        node.runAction(this.actionRotate());
        return node;
    },

    content:function () {
        var node = this.grossini();
        node.runAction(this.actionScale());
        return node;
    }
});

var ShapeInvertedTest = ShapeTest.extend({
    title:function () {
        return "Shape Inverted Basic Test";
    },

    subtitle:function () {
        return "A DrawNode as stencil and Sprite as content, inverted";
    },

    clipper:function () {
        var clipper = this._super();
        clipper.setInverted(true);
        return clipper;
    }
});

var SpriteTest = BasicTest.extend({
    title:function () {
        return "Sprite Basic Test";
    },
    subtitle:function () {
        return "A Sprite as stencil and DrawNode as content";
    },

    stencil:function () {
        var node = this.grossini();
        node.runAction(this.actionRotate());
        return node;
    },

    clipper:function () {
        var clipper = this._super();
        clipper.alphaThreshold = 0.05;
        return clipper;
    },

    content:function () {
        var node = this.shape();
        node.runAction(this.actionScale());
        return node;
    }
});

var SpriteNoAlphaTest = SpriteTest.extend({
    title:function () {
        return "Sprite No Alpha Basic Test";
    },

    subtitle:function () {
        return "A Sprite as stencil and DrawNode as content, no alpha";
    },

    clipper:function () {
        var clipper = this._super();
        clipper.alphaThreshold = 1;
        return clipper;
    }
});

var SpriteInvertedTest = SpriteTest.extend({
    title:function () {
        return "Sprite Inverted Basic Test";
    },

    subtitle:function () {
        return "A Sprite as stencil and DrawNode as content, inverted";
    },

    clipper:function () {
        var clipper = this._super();
        clipper.alphaThreshold = 0.05;
        clipper.inverted = true;
        return clipper;
    }
});

var NestedTest = BaseClippingNodeTest.extend({
    title:function () {
        return "Nested Test";
    },

    subtitle:function () {
        return "Nest 9 Clipping Nodes, max is usually 8";
    },

    setup:function () {
        var depth = 9;

        var parent = this;

        for (var i = 0;  i < depth; i++ ) {
            var size = 225 - i * (225 / (depth * 2));

            var clipper = new cc.ClippingNode();
            clipper.attr({
	            width: size,
	            height: size,
	            anchorX: 0.5,
	            anchorY: 0.5,
	            x: parent.width / 2,
	            y: parent.height / 2
            });
            clipper.alphaThreshold = 0.05;
            clipper.runAction(cc.rotateBy((i % 3) ? 1.33 : 1.66, (i % 2) ? 90 : -90).repeatForever());
            parent.addChild(clipper);

            var stencil = new cc.Sprite(s_pathGrossini);
            stencil.attr({
	            scale: 2.5 - (i * (2.5 / depth)),
	            anchorX: 0.5,
	            anchorY: 0.5,
	            x: clipper.width / 2,
	            y: clipper.height / 2,
	            visible: false
            });
            stencil.runAction(cc.sequence(cc.delayTime(i), cc.show()));
            clipper.stencil = stencil;

            clipper.addChild(stencil);
            parent = clipper;
        }
    }
});

var HoleDemo = BaseClippingNodeTest.extend({
    _outerClipper:null,
    _holes:null,
    _holesStencil:null,

    setup:function () {
        var target = new cc.Sprite(s_pathBlock);
        target.anchorX = 0;
        target.anchorY = 0;
        target.scale = 3;

        var scale = target.scale;
        var stencil = new cc.DrawNode();

        var rectangle = [cc.p(0, 0),cc.p(target.width*scale, 0),
            cc.p(target.width*scale, target.height*scale),
            cc.p(0, target.height*scale)];
        stencil.drawPoly(rectangle, cc.color(255, 0, 0, 255), 0, cc.color(255, 255, 255, 0));

        this._outerClipper = new cc.ClippingNode();
        this._outerClipper.retain();
        var transform = cc.affineTransformMakeIdentity();
        transform = cc.affineTransformScale(transform, target.scale, target.scale);

	    var ocsize = cc.sizeApplyAffineTransform(cc.size(target.width, target.height), transform);
        this._outerClipper.width = ocsize.width;
	    this._outerClipper.height = ocsize.height;
        this._outerClipper.anchorX = 0.5;
        this._outerClipper.anchorY = 0.5;
        this._outerClipper.x = this.width * 0.5;
	    this._outerClipper.y = this.height * 0.5;
        this._outerClipper.runAction(cc.rotateBy(1, 45).repeatForever());

        this._outerClipper.stencil = stencil;

        var holesClipper = new cc.ClippingNode();
        holesClipper.inverted = true;
        holesClipper.alphaThreshold = 0.05;

        holesClipper.addChild(target);

        this._holes = new cc.Node();
        this._holes.retain();

        holesClipper.addChild(this._holes);

        this._holesStencil = new cc.Node();
        this._holesStencil.retain();

        holesClipper.stencil = this._holesStencil;
        this._outerClipper.addChild(holesClipper);
        this.addChild(this._outerClipper);

        cc.eventManager.addListener(cc.EventListener.create({
            event: cc.EventListener.TOUCH_ALL_AT_ONCE,
            onTouchesBegan:function (touches, event) {
                var target = event.getCurrentTarget();
                var touch = touches[0];
                var point = target._outerClipper.convertToNodeSpace(touch.getLocation());
                var rect = cc.rect(0, 0, target._outerClipper.width, target._outerClipper.height);
                if (!cc.rectContainsPoint(rect,point))
                    return;
                target.pokeHoleAtPoint(point);
            }
        }), this);
    },

    title:function () {
        return "Hole Demo";
    },

    subtitle:function () {
        return "Touch/click to poke holes";
    },

    pokeHoleAtPoint:function (point) {
        var scale = Math.random() * 0.2 + 0.9;
        var rotation = Math.random() * 360;

        var hole = new cc.Sprite(s_hole_effect_png);
        hole.attr({
	        x: point.x,
	        y: point.y,
	        rotation: rotation,
	        scale: scale
        });

        this._holes.addChild(hole);

        var holeStencil = new cc.Sprite(s_hole_stencil_png);
        holeStencil.attr({
	        x: point.x,
	        y: point.y,
	        rotation: rotation,
	        scale: scale
        });

        this._holesStencil.addChild(holeStencil);
        this._outerClipper.runAction(cc.sequence(cc.scaleBy(0.05, 0.95), cc.scaleTo(0.125, 1)));
    }
});

var ScrollViewDemo = BaseClippingNodeTest.extend({
    _scrolling:false,
    _lastPoint:null,

    title:function () {
        return "Scroll View Demo";
    },

    subtitle:function () {
        return "Move/drag to scroll the content";
    },

    setup:function () {
        var clipper = new cc.ClippingNode();
        clipper.tag = TAG_CLIPPERNODE;
        clipper.width = 200;
	    clipper.height = 200;
        clipper.anchorX = 0.5;
        clipper.anchorY = 0.5;
        clipper.x = this.width / 2;
        clipper.y = this.height / 2;
        clipper.runAction(cc.rotateBy(1, 45).repeatForever());
        this.addChild(clipper);

        var stencil = new cc.DrawNode();
        var rectangle = [cc.p(0, 0),cc.p(clipper.width, 0),
            cc.p(clipper.width, clipper.height),
            cc.p(0, clipper.height)];

        var white = cc.color(255, 255, 255, 255);
        stencil.drawPoly(rectangle, white, 1, white);
        clipper.stencil = stencil;

        var content = new cc.Sprite(s_back2);
        content.tag = TAG_CONTENTNODE;
        content.anchorX = 0.5;
        content.anchorY = 0.5;
        content.x = clipper.width / 2;
	    content.y = clipper.height / 2;
        clipper.addChild(content);

        this._scrolling = false;
        cc.eventManager.addListener(cc.EventListener.create({
            event: cc.EventListener.TOUCH_ALL_AT_ONCE,
            onTouchesBegan: function (touches, event) {
                if (!touches || touches.length == 0)
                    return;
	            var target = event.getCurrentTarget();

                var touch = touches[0];
                var clipper = target.getChildByTag(TAG_CLIPPERNODE);
                var point = clipper.convertToNodeSpace(touch.getLocation());
                var rect = cc.rect(0, 0, clipper.width, clipper.height);
                target._scrolling = cc.rectContainsPoint(rect, point);
                target._lastPoint = point;
            },

            onTouchesMoved: function (touches, event) {
                var target = event.getCurrentTarget();
                if (!target._scrolling)
                    return;

                if (!touches || touches.length == 0)
                    return;
                var touch = touches[0];
                var clipper = target.getChildByTag(TAG_CLIPPERNODE);
                var point = clipper.convertToNodeSpace(touch.getLocation());
                var diff = cc.pSub(point, target._lastPoint);
                var content = clipper.getChildByTag(TAG_CONTENTNODE);
                content.setPosition(cc.pAdd(content.getPosition(), diff));
                target._lastPoint = point;
            },

            onTouchesEnded: function (touches, event) {
                var target = event.getCurrentTarget();
                if (!target._scrolling) return;
                target._scrolling = false;
            }
        }), this);
    }
});

var _stencilBits = -1;
var _alphaThreshold = 0.05;
var _PLANE_COUNT = 8;

var _planeColor = [
    cc.color(0, 0, 0, 166),
    cc.color(179, 0, 0, 153),
    cc.color(0, 179, 0, 140),
    cc.color(0, 0, 179, 128),
    cc.color(179, 179, 0, 115),
    cc.color(0, 179, 179, 102),
    cc.color(179, 0, 179, 89),
    cc.color(179, 179, 179, 77)
];

var RawStencilBufferTest = BaseClippingNodeTest.extend({
    _sprite:null,

    _initRendererCmd: function(){
        this._rendererCmd = new cc.CustomRenderCmdWebGL(this, this.draw);
    },

    title:function () {
        return "Raw Stencil Tests";
    },

    subtitle:function () {
        return "1:Default";
    },

    setup:function () {
        _stencilBits = cc._renderContext.getParameter(cc._renderContext.STENCIL_BITS);
        if (_stencilBits < 3)
            cc.log("Stencil must be enabled for the current CCGLView.");

        this._sprite = new cc.Sprite(s_pathGrossini);
        this._sprite.anchorX = 0.5;
        this._sprite.anchorY = 0;
        this._sprite.scale = 2.5;
        cc.director.setAlphaBlending(true);
    },

    draw:function (ctx) {
        var gl = ctx || cc._renderContext;
        var winPoint = cc.pFromSize(cc.director.getWinSize());
        var planeSize = cc.pMult(winPoint, 1.0 / _PLANE_COUNT);

        gl.enable(gl.STENCIL_TEST);
        //cc.checkGLErrorDebug();

        for (var i = 0; i < _PLANE_COUNT; i++) {
            var stencilPoint = cc.pMult(planeSize, _PLANE_COUNT - i);
            stencilPoint.x = winPoint.x;

            var x = planeSize.x / 2 + planeSize.x * i, y = 0;
            this._sprite.x = x;
	        this._sprite.y = y;

            this.setupStencilForClippingOnPlane(i);
            //cc.checkGLErrorDebug();

            cc._drawingUtil.drawSolidRect(cc.p(0, 0), stencilPoint, cc.color(255, 255, 255, 255));

            cc.kmGLPushMatrix();
            this.transform();
            this._sprite.visit();
            cc.kmGLPopMatrix();

            this.setupStencilForDrawingOnPlane(i);
            //cc.checkGLErrorDebug();

            cc._drawingUtil.drawSolidRect(cc.p(0, 0), winPoint, _planeColor[i]);

            cc.kmGLPushMatrix();
            this.transform();
            this._sprite.visit();
            cc.kmGLPopMatrix();
        }

        gl.disable(gl.STENCIL_TEST);
        //cc.checkGLErrorDebug();
    },

    setupStencilForClippingOnPlane:function (plane) {
        var gl = cc._renderContext;
        var planeMask = 0x1 << plane;
        gl.stencilMask(planeMask);
        gl.clearStencil(0x0);
        gl.clear(gl.STENCIL_BUFFER_BIT);
        gl.flush();
        gl.stencilFunc(gl.NEVER, planeMask, planeMask);
        gl.stencilOp(gl.REPLACE, gl.KEEP, gl.KEEP);
    },

    setupStencilForDrawingOnPlane:function (plane) {
        var gl = cc._renderContext;
        var planeMask = 0x1 << plane;
        var equalOrLessPlanesMask = planeMask | (planeMask - 1);
        gl.stencilFunc(gl.EQUAL, equalOrLessPlanesMask, equalOrLessPlanesMask);
        gl.stencilOp(gl.KEEP, gl.KEEP, gl.KEEP);
    }
});

var RawStencilBufferTest2 = RawStencilBufferTest.extend({
    subtitle:function () {
        return "2:DepthMask:FALSE";
    },

    setupStencilForClippingOnPlane:function (plane) {
        this._super(plane);
        cc._renderContext.depthMask(false);
    },

    setupStencilForDrawingOnPlane:function (plane) {
        cc._renderContext.depthMask(true);
        this._super(plane);
    }
});

var RawStencilBufferTest3 = RawStencilBufferTest.extend({
    subtitle:function () {
        return "3:DepthTest:DISABLE,DepthMask:FALSE";
    },

    setupStencilForClippingOnPlane:function (plane) {
        var gl = cc._renderContext;
        this._super(plane);
        gl.disable(gl.DEPTH_TEST);
        gl.depthMask(false);
    },

    setupStencilForDrawingOnPlane:function (plane) {
        var gl = cc._renderContext;
        gl.depthMask(true);
        //gl.enable(gl.DEPTH_TEST);
        this._super(plane);
    }
});

var RawStencilBufferTest4 = RawStencilBufferTest.extend({
    subtitle:function () {
        return "4:DepthMask:FALSE,AlphaTest:ENABLE";
    },

    setupStencilForClippingOnPlane:function (plane) {
        var gl = cc._renderContext;
        this._super(plane);
        gl.depthMask(false);

        var program = cc.shaderCache.programForKey(cc.SHADER_POSITION_TEXTURECOLORALPHATEST);
        var alphaValueLocation = gl.getUniformLocation(program.getProgram(),cc.UNIFORM_ALPHA_TEST_VALUE_S);
        cc.glUseProgram(program.getProgram());
        program.setUniformLocationWith1f(alphaValueLocation, _alphaThreshold);
        this._sprite.shaderProgram = program;
    },

    setupStencilForDrawingOnPlane:function (plane) {
        cc._renderContext.depthMask(true);
        this._super(plane);
    }
});

var RawStencilBufferTest5 = RawStencilBufferTest.extend({
    subtitle:function () {
        return "5:DepthTest:DISABLE,DepthMask:FALSE,AlphaTest:ENABLE";
    },

    setupStencilForClippingOnPlane:function (plane) {
        var gl = cc._renderContext;
        this._super(plane);
        gl.disable(gl.DEPTH_TEST);
        gl.depthMask(false);

        var program = cc.shaderCache.programForKey(cc.SHADER_POSITION_TEXTURECOLORALPHATEST);
        var alphaValueLocation = gl.getUniformLocation(program.getProgram(), cc.UNIFORM_ALPHA_TEST_VALUE_S);
        cc.glUseProgram(program.getProgram());
        program.setUniformLocationWith1f(alphaValueLocation, _alphaThreshold);
        this._sprite.shaderProgram = program;
    },

    setupStencilForDrawingOnPlane:function (plane) {
        cc._renderContext.depthMask(true);
        //cc._renderContext.enable(cc._renderContext.DEPTH_TEST);
        this._super(plane);
    }
});

var RawStencilBufferTest6 = RawStencilBufferTest.extend({
    subtitle:function () {
        return "6:ManualClear,AlphaTest:ENABLE";
    },

    setup:function () {
        cc._renderContext.stencilMask(~0);
        this._super();
    },

    setupStencilForClippingOnPlane:function (plane) {
        var gl = cc._renderContext;
        var planeMask = 0x1 << plane;
        gl.stencilMask(planeMask);
        gl.stencilFunc(gl.NEVER, 0, planeMask);
        gl.stencilOp(gl.REPLACE, gl.KEEP, gl.KEEP);
        cc._drawingUtil.drawSolidRect(cc.p(0, 0), cc.pFromSize(cc.director.getWinSize()), cc.color(255, 255, 255, 255));
        gl.stencilFunc(gl.NEVER, planeMask, planeMask);
        gl.stencilOp(gl.REPLACE, gl.KEEP, gl.KEEP);
        gl.disable(gl.DEPTH_TEST);
        gl.depthMask(false);

        var program = cc.shaderCache.programForKey(cc.SHADER_POSITION_TEXTURECOLORALPHATEST);
        var alphaValueLocation = gl.getUniformLocation(program.getProgram(), cc.UNIFORM_ALPHA_TEST_VALUE_S);
        cc.glUseProgram(program.getProgram());
        program.setUniformLocationWith1f(alphaValueLocation, _alphaThreshold);
        this._sprite.shaderProgram = program;

        gl.flush();
    },

    setupStencilForDrawingOnPlane:function (plane) {
        var gl = cc._renderContext;
        gl.depthMask(true);
        //gl.enable(gl.DEPTH_TEST);
        this._super(plane);
        gl.flush();
    }
});

var arrayOfClippingNodeTest = [
    ScrollViewDemo,
    ShapeTest,
    SpriteTest
];


if (!cc.sys.isNative && ("opengl" in cc.sys.capabilities)) {
    arrayOfClippingNodeTest.push(
        ShapeInvertedTest,
        SpriteNoAlphaTest,
        SpriteInvertedTest
        //TODO re-open them later.
        /*    RawStencilBufferTest,
         RawStencilBufferTest2,
         RawStencilBufferTest3,
         RawStencilBufferTest4,
         RawStencilBufferTest5,
         RawStencilBufferTest6*/
    );
}

if ( cc.sys.isNative){
    arrayOfClippingNodeTest.push(
        ShapeInvertedTest,
        SpriteNoAlphaTest,
        SpriteInvertedTest,
        NestedTest);
} else {
    arrayOfClippingNodeTest.push(HoleDemo
    );
}

var nextClippingNodeTest = function () {
    clippingNodeTestSceneIdx++;
    clippingNodeTestSceneIdx = clippingNodeTestSceneIdx % arrayOfClippingNodeTest.length;

    if(window.sideIndexBar){
        clippingNodeTestSceneIdx = window.sideIndexBar.changeTest(clippingNodeTestSceneIdx, 5);
    }

    return new arrayOfClippingNodeTest[clippingNodeTestSceneIdx]();
};

var previousClippingNodeTest = function () {
    clippingNodeTestSceneIdx--;
    if (clippingNodeTestSceneIdx < 0)
        clippingNodeTestSceneIdx += arrayOfClippingNodeTest.length;

    if(window.sideIndexBar){
        clippingNodeTestSceneIdx = window.sideIndexBar.changeTest(clippingNodeTestSceneIdx, 5);
    }

    return new arrayOfClippingNodeTest[clippingNodeTestSceneIdx]();
};

var restartClippingNodeTest = function () {
    return new arrayOfClippingNodeTest[clippingNodeTestSceneIdx]();
};

var ClippingNodeTestScene = TestScene.extend({
    runThisTest:function (num) {
        clippingNodeTestSceneIdx = (num || num == 0) ? (num - 1) : -1;
        cc.director.runScene(this);
	    var layer = nextClippingNodeTest();
	    this.addChild(layer);
    }
});