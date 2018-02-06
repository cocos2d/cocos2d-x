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

var ControlButtonTest_HelloVariableSize = ControlScene.extend({
    init:function () {
        if (this._super()) {
            var screenSize = cc.director.getWinSize();

            // Defines an array of title to create buttons dynamically
            var stringArray = ["Hello", "Variable", "Size", "!"];

            var layer = new cc.Node();
            this.addChild(layer, 1);

            var total_width = 0, height = 0;

            // For each title in the array
            for (var i = 0; i < stringArray.length; i++) {
                var button = this.standardButtonWithTitle(stringArray[i]);

                if (i == 0) {
                    button.opacity = 50;
                    //todo setColor not work in canvas
                    //button.color = cc.color(0, 255, 0);
                }
                else if (i == 1) {
                    button.opacity = 200;
                    //todo setColor not work in canvas
                    //button.color = cc.color(0, 255, 0);
                }
                else if (i == 2) {
                    button.opacity = 100;
                    //todo setColor not work in canvas
                    //button.color = cc.color(0, 0, 255);
                }

                button.x = total_width + button.width / 2;
                button.y = button.height / 2;
                layer.addChild(button);

                // Compute the size of the layer
                height = button.height;
                total_width += button.width;
            }

            layer.anchorX = 0.5;
            layer.anchorY = 0.5;
            layer.width = total_width;
            layer.height = height;
            layer.x = screenSize.width / 2.0;
            layer.y = screenSize.height / 2.0;

            // Add the black background
            var background = new cc.Scale9Sprite(s_extensions_buttonBackground);
            background.width = total_width + 14;
            background.height = height + 14;
            background.x = screenSize.width / 2.0;
            background.y = screenSize.height / 2.0;
            this.addChild(background);
            return true;
        }
        return false;
    },
    // Creates and return a button with a default background and title color.
    standardButtonWithTitle:function (title) {
        // Creates and return a button with a default background and title color.
        var backgroundButton = new cc.Scale9Sprite(s_extensions_button);
        var backgroundHighlightedButton = new cc.Scale9Sprite(s_extensions_buttonHighlighted);

        var titleButton = new cc.LabelTTF(title, "Marker Felt", 30);

        titleButton.color = cc.color(159, 168, 176);

        var button = new cc.ControlButton(titleButton, backgroundButton);
        button.setBackgroundSpriteForState(backgroundHighlightedButton, cc.CONTROL_STATE_HIGHLIGHTED);
        button.setTitleColorForState(cc.color.WHITE, cc.CONTROL_STATE_HIGHLIGHTED);

        return button;
    }
});

ControlButtonTest_HelloVariableSize.create = function (sceneTitle) {
    var scene = new cc.Scene();
    var controlLayer = new ControlButtonTest_HelloVariableSize();
    if (controlLayer && controlLayer.init()) {
        controlLayer.getSceneTitleLabel().setString(sceneTitle);
        scene.addChild(controlLayer);
    }
    return scene;
};

var ControlButtonTest_Event = ControlScene.extend({
    _displayValueLabel:null,

    init:function () {
        if (this._super()) {
            var screenSize = cc.director.getWinSize();

            // Add the button
            var backgroundButton = new cc.Scale9Sprite(s_extensions_button);
            var backgroundHighlightedButton = new cc.Scale9Sprite(s_extensions_buttonHighlighted);

            // Add a label in which the button events will be displayed
            this.setDisplayValueLabel(new cc.LabelTTF("No Event", "Marker Felt", 32));
            this._displayValueLabel.anchorX = 0.5;
            this._displayValueLabel.anchorY = -1;
            this._displayValueLabel.x = screenSize.width / 2.0;
            this._displayValueLabel.y = screenSize.height / 2.0;
            this.addChild(this._displayValueLabel, 10);

            var titleButton = new cc.LabelTTF("Touch Me!", "Marker Felt", 30);
            titleButton.color = cc.color(159, 168, 176);

            var controlButton = new cc.ControlButton(titleButton, backgroundButton);
            controlButton.setBackgroundSpriteForState(backgroundHighlightedButton, cc.CONTROL_STATE_HIGHLIGHTED);
            controlButton.setTitleColorForState(cc.color.WHITE, cc.CONTROL_STATE_HIGHLIGHTED);

            controlButton.anchorX = 0.5;
            controlButton.anchorY = 1;
            controlButton.x = screenSize.width / 2.0;
            controlButton.y = screenSize.height / 2.0;
            this.addChild(controlButton, 1);

            // Add the black background
            var background = new cc.Scale9Sprite(s_extensions_buttonBackground);
            background.width = 300;
            background.height = 170;
            background.x = screenSize.width / 2.0;
            background.y = screenSize.height / 2.0;
            this.addChild(background);

            // Sets up event handlers
            controlButton.addTargetWithActionForControlEvents(this, this.touchDownAction, cc.CONTROL_EVENT_TOUCH_DOWN);
            controlButton.addTargetWithActionForControlEvents(this, this.touchDragInsideAction, cc.CONTROL_EVENT_TOUCH_DRAG_INSIDE);
            controlButton.addTargetWithActionForControlEvents(this, this.touchDragOutsideAction, cc.CONTROL_EVENT_TOUCH_DRAG_OUTSIDE);
            controlButton.addTargetWithActionForControlEvents(this, this.touchDragEnterAction, cc.CONTROL_EVENT_TOUCH_DRAG_ENTER);
            controlButton.addTargetWithActionForControlEvents(this, this.touchDragExitAction, cc.CONTROL_EVENT_TOUCH_DRAG_EXIT);
            controlButton.addTargetWithActionForControlEvents(this, this.touchUpInsideAction, cc.CONTROL_EVENT_TOUCH_UP_INSIDE);
            controlButton.addTargetWithActionForControlEvents(this, this.touchUpOutsideAction, cc.CONTROL_EVENT_TOUCH_UP_OUTSIDE);
            controlButton.addTargetWithActionForControlEvents(this, this.touchCancelAction, cc.CONTROL_EVENT_TOUCH_CANCEL);
            return true;
        }
        return false;
    },

    getDisplayValueLabel:function () {
        return this._displayValueLabel;
    },
    setDisplayValueLabel:function (displayValueLabel) {
        this._displayValueLabel = displayValueLabel;
    },

    touchDownAction:function (sender, controlEvent) {
        this._displayValueLabel.setString("Touch Down");
    },
    touchDragInsideAction:function (sender, controlEvent) {
        this._displayValueLabel.setString("Drag Inside");
    },
    touchDragOutsideAction:function (sender, controlEvent) {
        this._displayValueLabel.setString("Drag Outside");
    },
    touchDragEnterAction:function (sender, controlEvent) {
        this._displayValueLabel.setString("Drag Enter");
    },
    touchDragExitAction:function (sender, controlEvent) {
        this._displayValueLabel.setString("Drag Exit");
    },
    touchUpInsideAction:function (sender, controlEvent) {
        this._displayValueLabel.setString("Touch Up Inside.");
    },
    touchUpOutsideAction:function (sender, controlEvent) {
        this._displayValueLabel.setString("Touch Up Outside.");
    },
    touchCancelAction:function (sender, controlEvent) {
        this._displayValueLabel.setString("Touch Cancel");
    }
});

ControlButtonTest_Event.create = function (sceneTitle) {
    var scene = new cc.Scene();
    var controlLayer = new ControlButtonTest_Event();
    if (controlLayer && controlLayer.init()) {
        controlLayer.getSceneTitleLabel().setString(sceneTitle);
        scene.addChild(controlLayer);
    }
    return scene;
};

var ControlButtonTest_Styling = ControlScene.extend({
    init:function () {
        if (this._super()) {
            var screenSize = cc.director.getWinSize();

            var layer = new cc.Node();
            this.addChild(layer, 1);

            var space = 10; // px

            var max_w = 0, max_h = 0;
            for (var i = 0; i < 3; i++) {
                for (var j = 0; j < 3; j++) {
                    // Add the buttons
                    var button = this.standardButtonWithTitle((0 | (Math.random() * 30)) + "");
                    button.setAdjustBackgroundImage(false);  // Tells the button that the background image must not be adjust
                    // It'll use the prefered size of the background image
                    button.x = button.width / 2 + (button.width + space) * i;
                    button.y = button.height / 2 + (button.height + space) * j;
                    layer.addChild(button);

                    max_w = Math.max(button.width * (i + 1) + space * i, max_w);
                    max_h = Math.max(button.height * (j + 1) + space * j, max_h);
                }
            }

            layer.anchorX = 0.5;
            layer.anchorY = 0.5;
            layer.width = max_w;
            layer.height = max_h;
            layer.x = screenSize.width / 2.0;
            layer.y = screenSize.height / 2.0;

            // Add the black background
            var backgroundButton = new cc.Scale9Sprite(s_extensions_buttonBackground);
            backgroundButton.width = max_w + 14;
            backgroundButton.height = max_h + 14;
            backgroundButton.x = screenSize.width / 2.0;
            backgroundButton.y = screenSize.height / 2.0;
            this.addChild(backgroundButton);
            return true;
        }
        return false;
    },
    standardButtonWithTitle:function (title) {
        /** Creates and return a button with a default background and title color. */
        var backgroundButton = new cc.Scale9Sprite(s_extensions_button);
        backgroundButton.setPreferredSize(cc.size(45, 45));  // Set the prefered size
        var backgroundHighlightedButton = new cc.Scale9Sprite(s_extensions_buttonHighlighted);
        backgroundHighlightedButton.setPreferredSize(cc.size(45, 45));  // Set the prefered size

        var titleButton = new cc.LabelTTF(title, "Marker Felt", 30);

        titleButton.color = cc.color(159, 168, 176);

        var button = new cc.ControlButton(titleButton, backgroundButton, null, null, false);
        button.setBackgroundSpriteForState(backgroundHighlightedButton, cc.CONTROL_STATE_HIGHLIGHTED);
        button.setTitleColorForState(cc.color.WHITE, cc.CONTROL_STATE_HIGHLIGHTED);

        return button;
    }
});

ControlButtonTest_Styling.create = function (sceneTitle) {
    var scene = new cc.Scene();
    var controlLayer = new ControlButtonTest_Styling();
    if (controlLayer && controlLayer.init()) {
        controlLayer.getSceneTitleLabel().setString(sceneTitle);
        scene.addChild(controlLayer);
    }
    return scene;
};

