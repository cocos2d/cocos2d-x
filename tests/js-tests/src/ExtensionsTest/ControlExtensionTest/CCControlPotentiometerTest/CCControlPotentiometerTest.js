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

var ControlPotentiometerTest = ControlScene.extend({
    _displayValueLabel:null,
    init:function () {
        if (this._super()) {
            var screenSize = cc.director.getWinSize();

            var layer = new cc.Node();
            layer.x = screenSize.width / 2;
            layer.y = screenSize.height / 2;
            this.addChild(layer, 1);

            var layer_width = 0;

            // Add the black background for the text
            var background = new cc.Scale9Sprite("extensions/buttonBackground.png");
            background.width = 80;
	        background.height = 50;
            background.x = layer_width + background.width / 2.0;
            background.y = 0;
            layer.addChild(background);

            layer_width += background.width;

            this._displayValueLabel = new cc.LabelTTF("", "HelveticaNeue-Bold", 30);

            this._displayValueLabel.x = background.x;
            this._displayValueLabel.y = background.y;
            layer.addChild(this._displayValueLabel);

            // Add the slider
            var potentiometer = new cc.ControlPotentiometer("extensions/potentiometerTrack.png"
                , "extensions/potentiometerProgress.png"
                , "extensions/potentiometerButton.png");
            potentiometer.x = layer_width + 10 + potentiometer.width / 2;
            potentiometer.y = 0;

            // When the value of the slider will change, the given selector will be call
            potentiometer.addTargetWithActionForControlEvents(this, this.valueChanged, cc.CONTROL_EVENT_VALUECHANGED);

            layer.addChild(potentiometer);

            layer_width += potentiometer.width;

            // Set the layer size
            layer.width = layer_width;
	        layer.height = 0;
            layer.anchorX = 0.5;
	        layer.anchorY = 0.5;

            // Update the value label
            this.valueChanged(potentiometer, cc.CONTROL_EVENT_VALUECHANGED);

            return true;
        }
        return false;
    },
    valueChanged:function (sender, controlEvent) {
        // Change value of label.
        this._displayValueLabel.setString(sender.getValue().toFixed(2));
    }
});
ControlPotentiometerTest.create = function (sceneTitle) {
    var scene = new cc.Scene();
    var controlLayer = new ControlPotentiometerTest();
    if (controlLayer && controlLayer.init()) {
        controlLayer.getSceneTitleLabel().setString(sceneTitle);
        scene.addChild(controlLayer);
    }
    return scene;
};