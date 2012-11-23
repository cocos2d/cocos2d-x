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
var s_nTouchCurCase = 0;

var TouchesMainScene = PerformBasicLayer.extend({
    _maxCases:2,
    _plabel:null,
    _numberOfTouchesB:0,
    _numberOfTouchesM:0,
    _numberOfTouchesE:0,
    _numberOfTouchesC:0,
    _elapsedTime:null,
    showCurrentTest:function () {
        var layer = null;
        switch (this._curCase) {
            case 0:
                layer = new TouchesPerformTest1(true, 2, this._curCase);
                break;
            case 1:
                layer = new TouchesPerformTest2(true, 2, this._curCase);
                break;
        }
        s_nTouchCurCase = this._curCase;

        if (layer) {
            var scene = cc.Scene.create();
            scene.addChild(layer);

            cc.Director.getInstance().replaceScene(scene);
        }
    },
    onEnter:function () {
        this._super();

        var s = cc.Director.getInstance().getWinSize();

        // add title
        var label = cc.LabelTTF.create(this.title(), "Arial", 32);
        this.addChild(label, 1);
        label.setPosition(cc.p(s.width / 2, s.height - 50));

        this.scheduleUpdate();

        this._plabel = cc.LabelTTF.create("00.0", "Arial", 16);
        this._plabel.setPosition(cc.p(s.width / 2, s.height / 2));
        this.addChild(this._plabel);

        this._elapsedTime = 0;
        this._numberOfTouchesB = this._numberOfTouchesM = this._numberOfTouchesE = this._numberOfTouchesC = 0;
    },
    title:function () {
        return "No title";
    },
    update:function (dt) {
        this._elapsedTime += dt;

        if (this._elapsedTime > 1.0) {
            var frameRateB = (this._numberOfTouchesB / this._elapsedTime).toFixed(1);
            var frameRateM = (this._numberOfTouchesM / this._elapsedTime).toFixed(1);
            var frameRateE = (this._numberOfTouchesE / this._elapsedTime).toFixed(1);
            var frameRateC = (this._numberOfTouchesC / this._elapsedTime).toFixed(1);
            this._elapsedTime = 0;
            this._numberOfTouchesB = this._numberOfTouchesM = this._numberOfTouchesE = this._numberOfTouchesC = 0;

            var str = frameRateB + " " + frameRateM + " " + frameRateE + " " + frameRateC;
            this._plabel.setString(str);
        }
    }
});

////////////////////////////////////////////////////////
//
// TouchesPerformTest1
//
////////////////////////////////////////////////////////
var TouchesPerformTest1 = TouchesMainScene.extend({
    onEnter:function () {
        this._super();
        this.setTouchEnabled(true);
    },
    title:function () {
        return "Targeted touches";
    },
    registerWithTouchDispatcher:function () {
        cc.Director.getInstance().getTouchDispatcher().addTargetedDelegate(this, 0, true);
    },
    onTouchBegan:function (touch, event) {
        this._numberOfTouchesB++;
        return true;
    },
    onTouchMoved:function (touch, event) {
        this._numberOfTouchesM++;
    },
    onTouchEnded:function (touch, event) {
        this._numberOfTouchesE++;
    },
    onTouchCancelled:function (touch, event) {
        this._numberOfTouchesC++;
    }
});

////////////////////////////////////////////////////////
//
// TouchesPerformTest2
//
////////////////////////////////////////////////////////
var TouchesPerformTest2 = TouchesMainScene.extend({
    onEnter:function () {
        this._super();
        this.setTouchEnabled(true);
    },
    title:function () {
        return "Standard touches";
    },
    registerWithTouchDispatcher:function () {
        cc.Director.getInstance().getTouchDispatcher().addStandardDelegate(this, 0);
    },

    onTouchesBegan:function (touches, event) {
        this._numberOfTouchesB += touches.length;
    },
    onTouchesMoved:function (touches, event) {
        this._numberOfTouchesM += touches.length;
    },
    onTouchesEnded:function (touches, event) {
        this._numberOfTouchesE += touches.length;
    },
    onTouchesCancelled:function (touches, event) {
        this._numberOfTouchesC += touches.length;
    }
});

function runTouchesTest() {
    s_nTouchCurCase = 0;
    var scene = cc.Scene.create();
    var layer = new TouchesPerformTest1(true, 2, s_nTouchCurCase);
    scene.addChild(layer);
    cc.Director.getInstance().replaceScene(scene);
}
