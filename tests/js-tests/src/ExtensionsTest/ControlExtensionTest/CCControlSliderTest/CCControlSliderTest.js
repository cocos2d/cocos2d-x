/****************************************************************************
 Copyright (c) 2008-2010 Ricardo Quesada
 Copyright (c) 2011-2012 cocos2d-x.org
 Copyright (c) 2013-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

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

var ControlSliderTest = ControlScene.extend({
    _displayValueLabel:null,
    init:function () {
        if (this._super()) {
            var screenSize = cc.director.getWinSize();

            // Add a label in which the slider value will be displayed
            this._displayValueLabel = new cc.LabelTTF("Move the slider thumb!\nThe lower slider is restricted.", "Marker Felt", 32);
            this._displayValueLabel.retain();
            this._displayValueLabel.anchorX = 0.5;
            this._displayValueLabel.anchorY = -1.0;
            this._displayValueLabel.x = screenSize.width / 1.7;
            this._displayValueLabel.y = screenSize.height / 2.0;
            this.addChild(this._displayValueLabel);

            // Add the slider
            var slider = new cc.ControlSlider("extensions/sliderTrack.png", "extensions/sliderProgress.png", "extensions/sliderThumb.png");
            slider.anchorX = 0.5;
            slider.anchorY = 1.0;
            slider.setMinimumValue(0.0); // Sets the min value of range
            slider.setMaximumValue(5.0); // Sets the max value of range
            slider.x = screenSize.width / 2.0;
            slider.y = screenSize.height / 2.0 + 16;
            slider.tag = 1;

            // When the value of the slider will change, the given selector will be call
            slider.addTargetWithActionForControlEvents(this, this.upperValueChanged, cc.CONTROL_EVENT_VALUECHANGED);

            var restrictSlider = new cc.ControlSlider("extensions/sliderTrack.png", "extensions/sliderProgress.png", "extensions/sliderThumb.png");
            restrictSlider.anchorX = 0.5;
	        restrictSlider.anchorY = 1.0;
            restrictSlider.setMinimumValue(0.0); // Sets the min value of range
            restrictSlider.setMaximumValue(5.0); // Sets the max value of range
            restrictSlider.setMaximumAllowedValue(4.0);
            restrictSlider.setMinimumAllowedValue(1.5);
            restrictSlider.setValue(3.0);
            restrictSlider.x = screenSize.width / 2.0;
            restrictSlider.y = screenSize.height / 2.0 - 24;
            restrictSlider.tag = 2;

            //same with restricted
            restrictSlider.addTargetWithActionForControlEvents(this, this.lowerValueChanged, cc.CONTROL_EVENT_VALUECHANGED);

            this.addChild(slider);
            this.addChild(restrictSlider);
            return true;
        }
        return false;
    },
    upperValueChanged:function (sender, controlEvent) {
        // Change value of label.
        this._displayValueLabel.setString("Upper slider value = " + sender.getValue().toFixed(2));
    },
    lowerValueChanged: function (sender, controlEvent) {
        // Change value of label.
        this._displayValueLabel.setString("Lower slider value = " + sender.getValue().toFixed(2));
    }
});

ControlSliderTest.create = function (sceneTitle) {
    var scene = new cc.Scene();
    var controlLayer = new ControlSliderTest();
    if (controlLayer && controlLayer.init()) {
        controlLayer.getSceneTitleLabel().setString(sceneTitle);
        scene.addChild(controlLayer);
    }
    return scene;
};