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

var UIPageViewTest = UIScene.extend({
    init: function () {
        if (this._super()) {
            var widgetSize = this._widget.getContentSize();
            //init text
            this._topDisplayLabel.setString("Move by horizontal direction");
            this._topDisplayLabel.x = widgetSize.width / 2.0;
            this._topDisplayLabel.y = widgetSize.height / 2.0 + this._topDisplayLabel.height * 1.5;
            this._bottomDisplayLabel.setString("PageView");
            this._bottomDisplayLabel.x = widgetSize.width / 2;
            this._bottomDisplayLabel.y = widgetSize.height / 2 - this._bottomDisplayLabel.height * 3;

            var background = this._widget.getChildByName("background_Panel");

            // Create the page view
            var pageView = new ccui.PageView();
            pageView.setTouchEnabled(true);
            pageView.setContentSize(cc.size(240, 130));
            pageView.x = (widgetSize.width - background.width) / 2 + (background.width - pageView.width) / 2;
            pageView.y = (widgetSize.height - background.height) / 2 + (background.height - pageView.height) / 2;

            for (var i = 0; i < 3; ++i) {
                var layout = new ccui.Layout();
                layout.setContentSize(cc.size(240, 130));
                var layoutRect = layout.getContentSize();

                var imageView = new ccui.ImageView();
                imageView.setTouchEnabled(true);
                imageView.setScale9Enabled(true);
                imageView.loadTexture("ccs-res/cocosui/scrollviewbg.png");
                imageView.setContentSize(cc.size(240, 130));
                imageView.x = layoutRect.width / 2;
                imageView.y = layoutRect.height / 2;
                layout.addChild(imageView);

                var text = new ccui.Text();
                text.string = "page" + (i + 1);
                text.font = "30px 'Marker Felt'";
                text.color = cc.color(192, 192, 192);
                text.x = layoutRect.width / 2;
                text.y = layoutRect.height / 2;
                layout.addChild(text);

                pageView.addPage(layout);
            }
            pageView.addEventListener(this.pageViewEvent, this);
            this._mainNode.addChild(pageView);

            return true;
        }
        return false;
    },

    pageViewEvent: function (sender, type) {
        switch (type) {
            case ccui.PageView.EVENT_TURNING:
                var pageView = sender;
                this._topDisplayLabel.setString("page = " + (pageView.getCurPageIndex().valueOf()-0 + 1));
                break;
            default:
                break;
        }
    }
});

//2015-01-14
var UIPageViewButtonTest = UIScene.extend({
    init: function(){
        if (this._super()){
            var widgetSize = this._widget.getContentSize();

            // Add a label in which the dragpanel events will be displayed
            this._topDisplayLabel.setString("Move by horizontal direction");
            this._topDisplayLabel.x = widgetSize.width / 2.0;
            this._topDisplayLabel.y = widgetSize.height / 2.0 + this._topDisplayLabel.height * 1.5;

            // Add the black background
            this._bottomDisplayLabel.setString("PageView with Buttons");
            this._bottomDisplayLabel.setPosition(widgetSize.width / 2.0, widgetSize.height / 2.0 - this._bottomDisplayLabel.height * 3.075);

            var root = this._mainNode.getChildByTag(81);
            var background = root.getChildByName("background_Panel");

            // Create the page view
            var pageView = new ccui.PageView();
            pageView.setContentSize(cc.size(240.0, 130.0));
            var backgroundSize = background.getContentSize();
            pageView.setPosition(cc.p((widgetSize.width - backgroundSize.width) / 2.0 +
                (backgroundSize.width - pageView.getContentSize().width) / 2.0,
                (widgetSize.height - backgroundSize.height) / 2.0 +
                (backgroundSize.height - pageView.getContentSize().height) / 2.0));

            pageView.removeAllPages();

            var pageCount = 4;
            for (var i = 0; i < pageCount; ++i){
                var outerBox = new ccui.HBox();
                outerBox.setContentSize(cc.size(240.0, 130.0));

                for (var k = 0; k < 2; ++k) {
                    var innerBox = new ccui.VBox();

                    for (var j = 0; j < 3; j++) {
                        var btn = new ccui.Button("ccs-res/cocosui/animationbuttonnormal.png", "ccs-res/cocosui/animationbuttonpressed.png");
                        btn.setName("button " + j);
                        btn.addTouchEventListener( this.onButtonClicked, this);
                        innerBox.addChild(btn);
                    }

                    var parameter = new ccui.LinearLayoutParameter();
                    parameter.setMargin({left: 0, top: 0, right: 100, bottom: 0});
                    innerBox.setLayoutParameter(parameter);

                    outerBox.addChild(innerBox);
                }
                pageView.insertPage(outerBox,i);
            }

            pageView.removePageAtIndex(0);
            pageView.addEventListener(this.pageViewEvent, this);
            this._mainNode.addChild(pageView);

            return true;
        }
    },

    onButtonClicked: function(sender, type){
        cc.log("button %s clicked", sender.getName());
    },

    pageViewEvent: function(pageView, type){
        switch (type){
            case ccui.PageView.EVENT_TURNING:
                this._topDisplayLabel.setString("page = " + pageView.getCurPageIndex() + 1);
                break;
            default:
                break;
        }
    }
});

//2015-01-14
var UIPageViewCustomScrollThreshold = UIScene.extend({
    init: function(){
        if (this._super()){
            var widgetSize = this._widget.getContentSize();

            // Add a label in which the dragpanel events will be displayed
            this._topDisplayLabel.setString("Scroll Threshold");
            this._topDisplayLabel.x = widgetSize.width / 2.0;
            this._topDisplayLabel.y = widgetSize.height / 2.0 + this._topDisplayLabel.height * 1.5;

            // Add the black background
            this._bottomDisplayLabel.setString("PageView");
            this._bottomDisplayLabel.setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0 - this._bottomDisplayLabel.height * 3.075));

            var root = this._mainNode.getChildByTag(81);
            var background = root.getChildByName("background_Panel");

            // Create the page view
            var pageView = new ccui.PageView();
            pageView.setContentSize(cc.size(240.0, 100.0));
            var backgroundSize = background.getContentSize();
            pageView.setPosition(cc.p((widgetSize.width - backgroundSize.width) / 2.0 +
                (backgroundSize.width - pageView.getContentSize().width) / 2.0,
                (widgetSize.height - backgroundSize.height) / 2.0 +
                (backgroundSize.height - pageView.getContentSize().height) / 2.0 + 20));

            var pageCount = 4;
            for (var i = 0; i < pageCount; ++i) {
                var layout = new ccui.Layout();
                layout.setContentSize(cc.size(240.0, 130.0));

                var imageView = new ccui.ImageView("ccs-res/cocosui/scrollviewbg.png");
                imageView.setScale9Enabled(true);
                imageView.setContentSize(cc.size(240, 130));
                imageView.setPosition(cc.p(layout.getContentSize().width / 2.0, layout.getContentSize().height / 2.0));
                layout.addChild(imageView);

                var label = new ccui.Text("page " + (i+1) , "Marker Felt", 30);
                label.setColor(cc.color(192, 192, 192));
                label.setPosition(cc.p(layout.getContentSize().width / 2.0, layout.getContentSize().height / 2.0));
                layout.addChild(label);

                pageView.insertPage(layout,i);
            }

            this._mainNode.addChild(pageView);
            pageView.setName("pageView");

            var slider = new ccui.Slider();
            slider.loadBarTexture("ccs-res/cocosui/sliderTrack.png");
            slider.loadSlidBallTextures("ccs-res/cocosui/sliderThumb.png", "ccs-res/cocosui/sliderThumb.png", "");
            slider.loadProgressBarTexture("ccs-res/cocosui/sliderProgress.png");
            slider.setPosition(cc.p(widgetSize.width / 2.0 , widgetSize.height / 2.0 - 40));
            slider.addEventListener(this.sliderEvent, this);
            slider.setPercent(50);
            this._mainNode.addChild(slider);

            return true;
        }
    },

    sliderEvent: function(slider, type){
        if (type == ccui.Slider.EVENT_PERCENT_CHANGED){
            var percent = slider.getPercent();
            var pageView = this._mainNode.getChildByName("pageView");
            if (percent == 0)
                percent = 1;
            pageView.setCustomScrollThreshold(percent * 0.01 * pageView.width);

            this._topDisplayLabel.setString("Scroll Threshold: " + pageView.getCustomScrollThreshold().toFixed(2));
        }
    }
});

//2015-01-14
var UIPageViewTouchPropagationTest = UIScene.extend({
    init: function(){
        if (this._super()){
            var widgetSize = this._widget.getContentSize();

            // Add a label in which the dragpanel events will be displayed
            this._topDisplayLabel.setString("Move by horizontal direction");
            this._topDisplayLabel.x = widgetSize.width / 2.0;
            this._topDisplayLabel.y = widgetSize.height / 2.0 + this._topDisplayLabel.height * 1.5;

            // Add the black background
            this._bottomDisplayLabel.setString("PageView Touch Propagation");
            this._bottomDisplayLabel.setPosition(widgetSize.width / 2.0, widgetSize.height / 2.0 - this._bottomDisplayLabel.height * 3.075);

            var root = this._mainNode.getChildByTag(81);
            var background = root.getChildByName("background_Panel");

            // Create the page view
            var pageView = new ccui.PageView();
            pageView.setContentSize(cc.size(240.0, 130.0));
            pageView.setAnchorPoint(cc.p(0.5,0.5));
            var backgroundSize = background.getContentSize();
            pageView.setPosition(cc.p(widgetSize.width / 2.0 ,widgetSize.height / 2.0));
            pageView.setBackGroundColor(cc.color.GREEN);
            pageView.setBackGroundColorType(ccui.Layout.BG_COLOR_SOLID);

            var pageCount = 4;
            for (var i = 0; i < pageCount; ++i) {
                var outerBox = new ccui.HBox();
                outerBox.setContentSize(cc.size(240.0, 130.0));

                for (var k = 0; k < 2; ++k) {
                    var innerBox = new ccui.VBox();

                    for (var j = 0; j < 3; j++) {
                        var btn = new ccui.Button("ccs-res/cocosui/animationbuttonnormal.png", "ccs-res/cocosui/animationbuttonpressed.png");
                        btn.setName("button " + j);
                        btn.addTouchEventListener(this.onButtonClicked, this);
                        innerBox.addChild(btn);
                    }

                    var parameter = new ccui.LinearLayoutParameter();
                    parameter.setMargin({left: 0, top: 0, right: 100, bottom: 0});
                    innerBox.setLayoutParameter(parameter);

                    outerBox.addChild(innerBox);
                }
                pageView.insertPage(outerBox, i);
            }

            pageView.addEventListener(this.pageViewEvent, this);
            pageView.setName("pageView");
            pageView.addTouchEventListener(function(sender, type){
                if (type == ccui.Widget.TOUCH_BEGAN){
                    cc.log("page view touch began");
                }else if(type == ccui.Widget.TOUCH_MOVED){
                    cc.log("page view touch moved");
                }else if(type == ccui.Widget.TOUCH_ENDED){
                    cc.log("page view touch ended");
                }else{
                    cc.log("page view touch cancelled");
                }
            });
            this._mainNode.addChild(pageView);

            var propagationText = new ccui.Text("Allow Propagation", "Arial", 10);
            propagationText.setAnchorPoint(cc.p(0,0.5));
            propagationText.setTextColor(cc.color.RED);
            propagationText.setPosition(cc.p(0, pageView.getPosition().y + 50));
            this._mainNode.addChild(propagationText);

            var swallowTouchText = new ccui.Text("Swallow Touches", "Arial", 10);
            swallowTouchText.setAnchorPoint(cc.p(0,0.5));
            swallowTouchText.setTextColor(cc.color.RED);
            swallowTouchText.setPosition(cc.p(0, pageView.getPosition().y));
            this._mainNode.addChild(swallowTouchText);

            // Create the checkbox
            var checkBox1 = new ccui.CheckBox("ccs-res/cocosui/check_box_normal.png",
                "ccs-res/cocosui/check_box_normal_press.png",
                "ccs-res/cocosui/check_box_active.png",
                "ccs-res/cocosui/check_box_normal_disable.png",
                "ccs-res/cocosui/check_box_active_disable.png");
            var propagationPosition = propagationText.getPosition();
            checkBox1.setPosition(
                propagationPosition.x + propagationText.getContentSize().width/2,
                propagationPosition.y - 20
            );

            checkBox1.setName("propagation");
            this._mainNode.addChild(checkBox1);

            // Create the checkbox
            var checkBox2 = new ccui.CheckBox("ccs-res/cocosui/check_box_normal.png",
                "ccs-res/cocosui/check_box_normal_press.png",
                "ccs-res/cocosui/check_box_active.png",
                "ccs-res/cocosui/check_box_normal_disable.png",
                "ccs-res/cocosui/check_box_active_disable.png");
            var swallowPosition = swallowTouchText.getPosition();
            checkBox2.setPosition(
                swallowPosition.x + swallowTouchText.getContentSize().width/2,
                swallowPosition.y - 20
            );

            checkBox2.setName("swallow");
            this._mainNode.addChild(checkBox2);

//            var eventListener = new cc.EventListenerTouchOneByOne();
//            eventListener.onTouchBegan = function(touch, event){
//                cc.log("layout recieves touches");
//                return true;
//            };
//            this._eventDispatcher.addEventListenerWithSceneGraphPriority(eventListener, this);

            return true;
        }
    },

    onButtonClicked: function(btn, type){
        var ck1 = this._mainNode.getChildByName("propagation");
        var ck2 = this._mainNode.getChildByName("swallow");
        var pageView = this._mainNode.getChildByName("pageView");

        if (type == ccui.Widget.TOUCH_BEGAN){
            if (ck1.isSelected()){
                btn.setPropagateTouchEvents(true);
                pageView.setPropagateTouchEvents(true);
            }else{
                btn.setPropagateTouchEvents(false);
                pageView.setPropagateTouchEvents(false);
            }

            if (ck2.isSelected()){
                btn.setSwallowTouches(true);
                pageView.setSwallowTouches(true);
            }else{
                btn.setSwallowTouches(false);
                pageView.setSwallowTouches(false);
            }
        }
        if (type == ccui.Widget.TOUCH_ENDED)
            cc.log("button clicked");
    },

    pageViewEvent: function(pageView, type){
        switch (type){
            case ccui.PageView.EVENT_TURNING:
                this._topDisplayLabel.setString("page = " + (pageView.getCurPageIndex()-0 + 1));
                break;
            default:
                break;
        }
    }
});

//2015-01-14
var UIPageViewDynamicAddAndRemoveTest = UIScene.extend({
    init: function(){
        var self = this;
        if (this._super()){
            var widgetSize = this._widget.getContentSize();

            // Add a label in which the dragpanel events will be displayed
            this._topDisplayLabel.setString("Click Buttons on the Left");
            this._topDisplayLabel.x = widgetSize.width / 2.0;
            this._topDisplayLabel.y = widgetSize.height / 2.0 + this._topDisplayLabel.height * 1.5;

            // Add the black background
            this._bottomDisplayLabel.setString("PageView Dynamic Modification");
            this._bottomDisplayLabel.setPosition(widgetSize.width / 2.0, widgetSize.height / 2.0 - this._bottomDisplayLabel.height * 3.075);

            var root = this._mainNode.getChildByTag(81);
            var background = root.getChildByName("background_Panel");

            // Create the page view
            var pageView = new ccui.PageView();
            pageView.setContentSize(cc.size(240.0, 130.0));
            pageView.setAnchorPoint(cc.p(0.5,0.5));
            var backgroundSize = background.getContentSize();
            pageView.setPosition(cc.p(widgetSize.width / 2.0 ,widgetSize.height / 2.0));
            pageView.setBackGroundColor(cc.color.GREEN);
            pageView.setBackGroundColorType(ccui.Layout.BG_COLOR_SOLID);

            var pageCount = 4;
            for (var i = 0; i < pageCount; ++i){
                var outerBox = new ccui.HBox();
                outerBox.setContentSize(cc.size(240.0, 130.0));

                for (var k = 0; k < 2; ++k){
                    var innerBox = new ccui.VBox();
                    for (var j = 0; j < 3; j++){
                        var btn = new ccui.Button("ccs-res/cocosui/animationbuttonnormal.png",
                            "ccs-res/cocosui/animationbuttonpressed.png");
                        btn.setName("button " + j);
                        innerBox.addChild(btn);
                    }

                    var parameter = new ccui.LinearLayoutParameter();
                    parameter.setMargin({left: 0, top: 0, right: 100, bottom:0});
                    innerBox.setLayoutParameter(parameter);

                    outerBox.addChild(innerBox);
                }
                pageView.insertPage(outerBox,i);
            }

            pageView.addEventListener(this.pageViewEvent, this);
            pageView.setName("pageView");
            this._mainNode.addChild(pageView);

            //add buttons
            var button = new ccui.Button();
//            button.setNormalizedPosition(cc.p(0.12,0.7));
            button.setPosition(20, 220);
            button.setTitleText("Add A Page");
            button.setZoomScale(0.3);
            button.setPressedActionEnabled(true);
            button.setTitleColor(cc.color.RED);
            button.addClickEventListener(function(sender){
                var outerBox = new ccui.HBox();
                outerBox.setContentSize(cc.size(240.0, 130.0));

                for (var k = 0; k < 2; ++k){
                    var innerBox = new ccui.VBox();
                    for (var j = 0; j < 3; j++){
                        var btn = new ccui.Button("ccs-res/cocosui/animationbuttonnormal.png",
                            "ccs-res/cocosui/animationbuttonpressed.png");
                        btn.setName("button " + j);
                        innerBox.addChild(btn);
                    }

                    var parameter = new ccui.LinearLayoutParameter();
                    parameter.setMargin({left: 0, top: 0, right: 100, bottom: 0});
                    innerBox.setLayoutParameter(parameter);

                    outerBox.addChild(innerBox);
                }

                pageView.addPage(outerBox);
                self._topDisplayLabel.setString("page count = " + pageView.getPages().length);
            });
            this._mainNode.addChild(button);

            var button2 = new ccui.Button();
//            button2.setNormalizedPosition(cc.p(0.12,0.5));
            button2.setPosition(20, 180);
            button2.setTitleText("Remove A Page");
            button2.setZoomScale(0.3);
            button2.setPressedActionEnabled(true);
            button2.setTitleColor(cc.color.RED);
            button2.addClickEventListener(function(sender){
                if (pageView.getPages().length > 0){
                    pageView.removePageAtIndex(pageView.getPages().length-1);
                }else{
                    cc.log("There is no page to remove!");
                }
                self._topDisplayLabel.setString("page count = " + pageView.getPages().length);

            });
            this._mainNode.addChild(button2);

            var button3 = new ccui.Button();
//            button3.setNormalizedPosition(cc.p(0.12,0.3));
            button3.setPosition(cc.p(20, 140));
            button3.setTitleText("Remove All Pages");
            button3.setZoomScale(0.3);
            button3.setPressedActionEnabled(true);
            button3.setTitleColor(cc.color.RED);
            button3.addClickEventListener(function(sender){
                pageView.removeAllPages();
                self._topDisplayLabel.setString("page count = " + pageView.getPages().length);
            });
            this._mainNode.addChild(button3);

            return true;
        }
    },

    pageViewEvent: function(pageView, type){
        switch (type){
            case ccui.PageView.EVENT_TURNING:
                this._topDisplayLabel.setString("page = " + (pageView.getCurPageIndex() + 1));
                break;
            default:
                break;
        }
    }
});