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
var DrawPrimitivesTest = cc.Layer.extend({
    ctor:function () {
    },
    draw:function () {
        this._super();

        var s = cc.Director.getInstance().getWinSize();

        cc.renderContext.fillStyle = "rgba(255,255,255,1)";
        cc.renderContext.strokeStyle = "rgba(255,255,255,1)";
        // draw a simple line
        // The default state is:
        // Line Width: 1
        // color: 255,255,255,255 (white, non-transparent)
        // Anti-Aliased
        cc.drawingUtil.drawLine(cc.p(0, 0), cc.p(s.width, s.height));

        // line: color, width, aliased
        // glLineWidth > 1 and GL_LINE_SMOOTH are not compatible
        // GL_SMOOTH_LINE_WIDTH_RANGE = (1,1) on iPhone
        cc.renderContext.strokeStyle = "rgba(255,0,0,1)";
        cc.renderContext.lineWidth = "5";

        /*glColor4ub(255,0,0,255);*/
        //glColor4f(1.0, 0.0, 0.0, 1.0);
        cc.drawingUtil.drawLine(cc.p(0, s.height), cc.p(s.width, 0));

        // TIP:
        // If you are going to use always the same color or width, you don't
        // need to call it before every draw
        //
        // Remember: OpenGL is a state-machine.

        // draw big point in the center
        /*glColor4ub(0,0,255,128);*/
        //glColor4f(0.0, 0.0, 1.0, 0.5);
        cc.renderContext.fillStyle = "rgba(0,0,255,0.5)";
        cc.drawingUtil.drawPoint(cc.p(s.width / 2, s.height / 2), 40);

        // draw 4 small points
        var points = [cc.p(60, 60), cc.p(70, 70), cc.p(60, 70), cc.p(70, 60)];
        /*glColor4ub(0,255,255,255);*/
        cc.renderContext.fillStyle = "rgba(0,255,255,1)";
        //glColor4f(0.0, 1.0, 1.0, 1.0);
        cc.drawingUtil.drawPoints(points, 4, 4);

        // draw a green circle with 10 segments
        //glLineWidth(16);
        cc.renderContext.lineWidth = "16";
        /*glColor4ub(0, 255, 0, 255);*/
        //glColor4f(0.0, 1.0, 0.0, 1.0);
        cc.renderContext.strokeStyle = "rgba(0,255,0,1)";
        cc.drawingUtil.drawCircle(cc.p(s.width / 2, s.height / 2), 100, 0, 10, false);

        // draw a green circle with 50 segments with line to center
        //glLineWidth(2);
        cc.renderContext.lineWidth = "2";
        /*glColor4ub(0, 255, 255, 255);*/
        //glColor4f(0.0, 1.0, 1.0, 1.0);
        cc.renderContext.strokeStyle = "rgba(0,255,255,1)";
        cc.drawingUtil.drawCircle(cc.p(s.width / 2, s.height / 2), 50, cc.DEGREES_TO_RADIANS(90), 50, true);

        // open yellow poly
        /*glColor4ub(255, 255, 0, 255);*/
        //glColor4f(1.0, 1.0, 0.0, 1.0);
        cc.renderContext.strokeStyle = "rgba(255,255,0,1)";
        //glLineWidth(10);
        cc.renderContext.lineWidth = "10";
        var vertices = [cc.p(0, 0), cc.p(50, 50), cc.p(100, 50), cc.p(100, 100), cc.p(50, 100) ];
        cc.drawingUtil.drawPoly(vertices, 5, false);

        // closed purble poly
        /*glColor4ub(255, 0, 255, 255);*/
        //glColor4f(1.0, 0.0, 1.0, 1.0);
        cc.renderContext.strokeStyle = "rgba(255,0,255,1)";
        //glLineWidth(2);
        cc.renderContext.lineWidth = "2";
        var vertices2 = [cc.p(30, 130), cc.p(30, 230), cc.p(50, 200)];
        cc.drawingUtil.drawPoly(vertices2, 3, true);

        // draw quad bezier path
        cc.drawingUtil.drawQuadBezier(cc.p(0, s.height), cc.p(s.width / 2, s.height / 2), cc.p(s.width, s.height), 50);

        // draw cubic bezier path
        cc.drawingUtil.drawCubicBezier(cc.p(s.width / 2, s.height / 2), cc.p(s.width / 2 + 30, s.height / 2 + 50),
            cc.p(s.width / 2 + 60, s.height / 2 - 50), cc.p(s.width, s.height / 2), 100);

        // restore original values
        cc.renderContext.lineWidth = "1";
        //glLineWidth(1);
        /*glColor4ub(255,255,255,255);*/
        //glColor4f(1.0, 1.0, 1.0, 1.0);
        //glPointSize(1);
        cc.renderContext.fillStyle = "rgba(255,255,255,1)";
        cc.renderContext.strokeStyle = "rgba(255,255,255,1)";
    }
});

var DrawPrimitivesTestScene = TestScene.extend({
    runThisTest:function () {
        var layer = new DrawPrimitivesTest();
        this.addChild(layer);

        cc.Director.getInstance().replaceScene(this);
    }
});
