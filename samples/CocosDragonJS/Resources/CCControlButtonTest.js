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

var ControlButtonTest_HelloVariableSize = ControlScene.extend({
     init:function(){
         if (this._super()) {
             var screenSize = cc.Director.getInstance().getWinSize();

             // Defines an array of title to create buttons dynamically
             var stringArray = ["Hello", "Variable", "Size","!"];

             var layer = cc.Node.create();
             this.addChild(layer, 1);

             var total_width = 0, height = 0;

             // For each title in the array
             for(var i = 0; i< stringArray.length; i++){
                 var button = this.standardButtonWithTitle(stringArray[i]);
                 button.setPosition(cc.p(total_width + button.getContentSize().width / 2, button.getContentSize().height / 2));
                 layer.addChild(button);

                 // Compute the size of the layer
                 height = button.getContentSize().height;
                 total_width += button.getContentSize().width;
             }

             layer.setAnchorPoint(cc.p(0.5, 0.5));
             layer.setContentSize(cc.SizeMake(total_width, height));
             layer.setPosition(cc.p(screenSize.width / 2.0, screenSize.height / 2.0));

             // Add the black background
             var background = cc.Scale9Sprite.create(s_extensions_buttonBackground);
             background.setContentSize(cc.SizeMake(total_width + 14, height + 14));
             background.setPosition(cc.p(screenSize.width / 2.0, screenSize.height / 2.0));
             this.addChild(background);
             return true;
         }
         return false;
     },
    /** Creates and return a button with a default background and title color. */
    standardButtonWithTitle:function(title){
        /** Creates and return a button with a default background and title color. */
        var backgroundButton = cc.Scale9Sprite.create(s_extensions_button);
        var backgroundHighlightedButton = cc.Scale9Sprite.create(s_extensions_buttonHighlighted);

        var titleButton = cc.LabelTTF.create(title, "Marker Felt", 30);

        titleButton.setColor(cc.c3(159, 168, 176));

        var button = cc.ControlButton.create(titleButton, backgroundButton);
        button.setBackgroundSpriteForState(backgroundHighlightedButton, cc.CONTROL_STATE_HIGHLIGHTED);
        button.setTitleColorForState(cc.white(), cc.CONTROL_STATE_HIGHLIGHTED);

        return button;
    }
});

ControlButtonTest_HelloVariableSize.create = function(sceneTitle){
    var scene = cc.Scene.create();
    var controlLayer = new ControlButtonTest_HelloVariableSize();
    if(controlLayer && controlLayer.init()){
        controlLayer.getSceneTitleLabel().setString(sceneTitle);
        scene.addChild(controlLayer);
    }
    return scene;
};

var ControlButtonTest_Event = ControlScene.extend({
    _displayValueLabel:null,

    ctor:function(){},
    init:function(){
        if (this._super()) {
            var screenSize = cc.Director.getInstance().getWinSize();

            // Add a label in which the button events will be displayed
            this.setDisplayValueLabel(cc.LabelTTF.create("No Event", "Marker Felt", 32));
            this._displayValueLabel.setAnchorPoint(cc.p(0.5, -1));
            this._displayValueLabel.setPosition(cc.p(screenSize.width / 2.0, screenSize.height / 2.0));
            this.addChild(this._displayValueLabel, 1);

            // Add the button
            var backgroundButton = cc.Scale9Sprite.create(s_extensions_button);
            var backgroundHighlightedButton = cc.Scale9Sprite.create(s_extensions_buttonHighlighted);

            var titleButton = cc.LabelTTF.create("Touch Me!", "Marker Felt", 30);

            titleButton.setColor(cc.c3(159, 168, 176));

            var controlButton = cc.ControlButton.create(titleButton, backgroundButton);
            controlButton.setBackgroundSpriteForState(backgroundHighlightedButton, cc.CONTROL_STATE_HIGHLIGHTED);
            controlButton.setTitleColorForState(cc.white(), cc.CONTROL_STATE_HIGHLIGHTED);

            controlButton.setAnchorPoint(cc.p(0.5, 1));
            controlButton.setPosition(cc.p(screenSize.width / 2.0, screenSize.height / 2.0));
            this.addChild(controlButton, 1);

            // Add the black background
            var background = cc.Scale9Sprite.create(s_extensions_buttonBackground);
            background.setContentSize(cc.SizeMake(300, 170));
            background.setPosition(cc.p(screenSize.width / 2.0, screenSize.height / 2.0));
            this.addChild(background);

            // Sets up event handlers
            controlButton.addTargetWithActionForControlEvent(this, this.touchDownAction, cc.CONTROL_EVENT_TOUCH_DOWN);
            controlButton.addTargetWithActionForControlEvent(this, this.touchDragInsideAction, cc.CONTROL_EVENT_TOUCH_DRAGINSIDE);
            controlButton.addTargetWithActionForControlEvent(this, this.touchDragOutsideAction, cc.CONTROL_EVENT_TOUCH_DRAGOUTSIDE);
            controlButton.addTargetWithActionForControlEvent(this, this.touchDragEnterAction, cc.CONTROL_EVENT_TOUCH_DRAGENTER);
            controlButton.addTargetWithActionForControlEvent(this, this.touchDragExitAction, cc.CONTROL_EVENT_TOUCH_DRAGEXIT);
            controlButton.addTargetWithActionForControlEvent(this, this.touchUpInsideAction, cc.CONTROL_EVENT_TOUCH_UPINSIDE);
            controlButton.addTargetWithActionForControlEvent(this, this.touchUpOutsideAction, cc.CONTROL_EVENT_TOUCH_UPOUTSIDE);
            controlButton.addTargetWithActionForControlEvent(this, this.touchCancelAction, cc.CONTROL_EVENT_TOUCH_CANCEL);
            return true;
        }
        return false;
    },

    getDisplayValueLabel:function(){return this._displayValueLabel;},
    setDisplayValueLabel:function(displayValueLabel) {this._displayValueLabel = displayValueLabel;},

    touchDownAction:function(sender, controlEvent){
        this._displayValueLabel.setString("Touch Down");
    },
    touchDragInsideAction:function(sender,controlEvent){
        this._displayValueLabel.setString("Drag Inside");
    },
    touchDragOutsideAction:function(sender, controlEvent){
        this._displayValueLabel.setString("Drag Outside");
    },
    touchDragEnterAction:function(sender,controlEvent){
        this._displayValueLabel.setString("Drag Enter");
    },
    touchDragExitAction:function(sender, controlEvent){
        this._displayValueLabel.setString("Drag Exit");
    },
    touchUpInsideAction:function(sender,controlEvent){
        this._displayValueLabel.setString("Touch Up Inside.");
    },
    touchUpOutsideAction:function(sender, controlEvent){
        this._displayValueLabel.setString("Touch Up Outside.");
    },
    touchCancelAction:function(sender,controlEvent){
        this._displayValueLabel.setString("Touch Cancel");
    }
});

ControlButtonTest_Event.create = function(sceneTitle){
    var scene = cc.Scene.create();
    var controlLayer = new ControlButtonTest_Event();
    if(controlLayer && controlLayer.init()){
        controlLayer.getSceneTitleLabel().setString(sceneTitle);
        scene.addChild(controlLayer);
    }
    return scene;
};

var ControlButtonTest_Styling = ControlScene.extend({
    init:function(){
        if (this._super()) {
            var screenSize = cc.Director.getInstance().getWinSize();

            var layer = cc.Node.create();
            this.addChild(layer, 1);

            var space = 10; // px

            var max_w = 0, max_h = 0;
            for (var i = 0; i < 3; i++)
            {
                for (var j = 0; j < 3; j++)
                {
                    // Add the buttons
                    var button = this.standardButtonWithTitle((0|(Math.random() * 30)) + "");
                    button.setAdjustBackgroundImage(false);  // Tells the button that the background image must not be adjust
                    // It'll use the prefered size of the background image
                    button.setPosition(cc.p (button.getContentSize().width / 2 + (button.getContentSize().width + space) * i,
                        button.getContentSize().height / 2 + (button.getContentSize().height + space) * j));
                    layer.addChild(button);

                    max_w = Math.max(button.getContentSize().width * (i + 1) + space  * i, max_w);
                    max_h = Math.max(button.getContentSize().height * (j + 1) + space * j, max_h);
                }
            }

            layer.setAnchorPoint(cc.p(0.5, 0.5));
            layer.setContentSize(cc.SizeMake(max_w, max_h));
            layer.setPosition(cc.p(screenSize.width / 2.0, screenSize.height / 2.0));

            // Add the black background
            var backgroundButton = cc.Scale9Sprite.create(s_extensions_buttonBackground);
            backgroundButton.setContentSize(cc.SizeMake(max_w + 14, max_h + 14));
            backgroundButton.setPosition(cc.p(screenSize.width / 2.0, screenSize.height / 2.0));
            this.addChild(backgroundButton);
            return true;
        }
        return false;
    },
    standardButtonWithTitle:function(title){
        /** Creates and return a button with a default background and title color. */
        var backgroundButton = cc.Scale9Sprite.create(s_extensions_button);
        backgroundButton.setPreferredSize(cc.SizeMake(45, 45));  // Set the prefered size
        var backgroundHighlightedButton = cc.Scale9Sprite.create(s_extensions_buttonHighlighted);
        backgroundHighlightedButton.setPreferredSize(cc.SizeMake(45, 45));  // Set the prefered size

        var titleButton = cc.LabelTTF.create(title, "Marker Felt", 30);

        titleButton.setColor(cc.c3(159, 168, 176));

        var button = cc.ControlButton.create(titleButton, backgroundButton);
        button.setBackgroundSpriteForState(backgroundHighlightedButton, cc.CONTROL_STATE_HIGHLIGHTED);
        button.setTitleColorForState(cc.white(), cc.CONTROL_STATE_HIGHLIGHTED);

        return button;
    }
});

ControlButtonTest_Styling.create = function(sceneTitle){
    var scene = cc.Scene.create();
    var controlLayer = new ControlButtonTest_Styling();
    if(controlLayer && controlLayer.init()){
        controlLayer.getSceneTitleLabel().setString(sceneTitle);
        scene.addChild(controlLayer);
    }
    return scene;
};

