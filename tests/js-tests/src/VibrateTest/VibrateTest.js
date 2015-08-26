/****************************************************************************
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

var VibrateTest = BaseTestLayer.extend({
    _duration:0.1,
    _durationLabel:null,
    ctor:function () {
        this._super();
        var s = cc.director.getWinSize();
        var label = new cc.LabelTTF("vibrate control test", "Arial", 28);
        this.addChild(label, 0);
        label.x = s.width / 2;
        label.y = s.height - 50;

        this._duration = 0.1;

        cc.MenuItemFont.setFontName("Arial");
        cc.MenuItemFont.setFontSize(24);

        var vibrateItem = new cc.MenuItemFont("Vibrate", this.startVibrate, this);
        vibrateItem.x = s.width * 0.5;
        vibrateItem.y = s.height * 0.7;

        var menu = new cc.Menu();
        menu.addChild(vibrateItem);
        menu.x = 0;
        menu.y = 0;
        this.addChild(menu);

        this._durationLabel = new cc.LabelTTF("duration: "+this._duration.toFixed(3)+"s", "Arial", 20);
        this._durationLabel.x = s.width * 0.5;
        this._durationLabel.y = s.height * 0.5;
        this.addChild(this._durationLabel);

        // Create the slider
        var durationSlider = new ccui.Slider();
        durationSlider.setPercent(0);
        durationSlider.setTouchEnabled(true);
        durationSlider.loadBarTexture("ccs-res/cocosui/sliderTrack.png");
        durationSlider.loadSlidBallTextures("ccs-res/cocosui/sliderThumb.png", "ccs-res/cocosui/sliderThumb.png", "");
        durationSlider.loadProgressBarTexture("ccs-res/cocosui/sliderProgress.png");
        durationSlider.x = s.width * 0.5;
        durationSlider.y = s.height * 0.35;
        durationSlider.addEventListener(this.durationSliderEvent, this);
        this.addChild(durationSlider);
    },
    startVibrate:function (sender) {
        cc.Device.vibrate(this._duration);
    },
    durationSliderEvent:function (sender, type) {
        switch (type) {
            case ccui.Slider.EVENT_PERCENT_CHANGED:
                var slider = sender;
                var percent = slider.getPercent();
                this._duration = (percent / 100.0) * 1.9 + 0.1; // from 0.1ms to 2s
                this._durationLabel.setString("duration: "+this._duration.toFixed(3)+"s");
                break;
            default:
                break;
        }
    },
    onExit:function () {
        this._super();
    }
});

var VibrateTestScene = TestScene.extend({
    runThisTest:function () {
        var layer = new VibrateTest();
        this.addChild(layer);

        cc.director.runScene(this);
    }
});

var arrayOfVibrateTest = [
    VibrateTest
];