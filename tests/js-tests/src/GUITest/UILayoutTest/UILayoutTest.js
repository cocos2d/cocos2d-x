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

var UILayoutTestBase = UIMainLayer.extend({
    layout: null,
    button: null,
    textButton: null,
    button_scale9: null,
    init: function () {
        if (this._super()) {
            var widgetSize = this._widget.getContentSize();
            //init text
            this._topDisplayLabel.setString("");
            this._bottomDisplayLabel.setString(this.getText());
            this._bottomDisplayLabel.x = widgetSize.width / 2;
            this._bottomDisplayLabel.y = widgetSize.height / 2 - this._bottomDisplayLabel.height * 3;

            var background = this._widget.getChildByName("background_Panel");
            this._mainNode.width = widgetSize.width;
            this._mainNode.height = widgetSize.height;

            // Create the layout
            this.layout = this.createLayout();
            var layoutRect = this.layout.getContentSize();
            var backgroundRect = background.getContentSize();
            this.layout.x = (widgetSize.width - backgroundRect.width) / 2 + (backgroundRect.width - layoutRect.width) / 2;
	        this.layout.y = (widgetSize.height - backgroundRect.height) / 2 + (backgroundRect.height - layoutRect.height) / 2;
            this._mainNode.addChild(this.layout);

            this.button = new ccui.Button();
            this.button.setTouchEnabled(true);
            this.button.loadTextures("ccs-res/cocosui/animationbuttonnormal.png", "ccs-res/cocosui/animationbuttonpressed.png", "");
            this.button.x = this.button.width / 2;
            this.button.y = layoutRect.height - this.button.height / 2;
            this.layout.addChild(this.button);

            this.textButton = new ccui.Button();
            this.textButton.setTouchEnabled(true);
            this.textButton.loadTextures("ccs-res/cocosui/backtotopnormal.png", "ccs-res/cocosui/backtotoppressed.png", "");
            this.textButton.setTitleText("Text Button");
            this.textButton.x = layoutRect.width / 2;
            this.textButton.y = layoutRect.height / 2;
            this.layout.addChild(this.textButton);

            this.button_scale9 = new ccui.Button();
            this.button_scale9.setTouchEnabled(true);
            this.button_scale9.setScale9Enabled(true);
            this.button_scale9.loadTextures("ccs-res/cocosui/button.png", "ccs-res/cocosui/buttonHighlighted.png", "");
            this.button_scale9.width = 100;
	        this.button_scale9.height = 32;
            this.button_scale9.x = layoutRect.width - this.button_scale9.width / 2;
            this.button_scale9.y = this.button_scale9.height / 2;
            this.layout.addChild(this.button_scale9);

            this.setLayoutParameter();
            return true;
        }
        return false;
    },
    getText: function () {
        return "";
    },
    createLayout: function () {
        var layout = new ccui.Layout();
        layout.setContentSize(cc.size(280, 150));
        return layout;
    },
    setLayoutParameter: function () {

    }
});
var UILayoutTest = UILayoutTestBase.extend({
    createLayout: function () {
        var layout = new ccui.Layout();
        layout.setContentSize(cc.size(280, 150));
        return layout;
    },
    getText: function () {
        return "Layout";
    }
});
var UILayoutTest_Color = UILayoutTestBase.extend({
    createLayout: function () {
        var layout = new ccui.Layout();
        layout.setBackGroundColorType(ccui.Layout.BG_COLOR_SOLID);
        layout.setBackGroundColor(cc.color(128, 128, 128));
        layout.setContentSize(cc.size(280, 150));
        return layout;
    },
    getText: function () {
        return "Layout color render";
    }
});
var UILayoutTest_Gradient = UILayoutTestBase.extend({
    createLayout: function () {
        var layout = new ccui.Layout();
        layout.setBackGroundColorType(ccui.Layout.BG_COLOR_GRADIENT);
        layout.setBackGroundColor(cc.color(64, 64, 64), cc.color(192, 192, 192));
        layout.setContentSize(cc.size(280, 150));
        return layout;
    },
    getText: function () {
        return "Layout gradient render";
    }
});
var UILayoutTest_BackGroundImage = UILayoutTestBase.extend({
    createLayout: function () {
        var layout = new ccui.Layout();
        layout.setClippingEnabled(true);
        layout.setBackGroundImage("ccs-res/cocosui/Hello.png");
        layout.setContentSize(cc.size(280, 150));
        return layout;
    },
    getText: function () {
        return "Layout background image";
    }
});

var UILayoutTest_BackGroundImage_Scale9 = UILayoutTestBase.extend({
    createLayout: function () {
        var layout = new ccui.Layout();
        layout.setBackGroundImageScale9Enabled(true);
        layout.setBackGroundImage("ccs-res/cocosui/green_edit.png");
        layout.setContentSize(cc.size(280, 150));
        return layout;
    },
    getText: function () {
        return "Layout background image scale9";
    }
});
var UILayoutTest_Layout_Linear_Vertical = UILayoutTestBase.extend({
    createLayout: function () {
        var layout = new ccui.Layout();
        layout.setLayoutType(ccui.Layout.LINEAR_VERTICAL);
        layout.setContentSize(cc.size(280, 150));
        return layout;
    },
    getText: function () {
        return "Layout Layout Linear Vertical";
    },
    setLayoutParameter: function () {
        var lp1 = new ccui.LinearLayoutParameter();
        this.button.setLayoutParameter(lp1);
        lp1.setGravity(ccui.LinearLayoutParameter.CENTER_HORIZONTAL);
        lp1.setMargin(new ccui.Margin(0, 5, 0, 10));

        var lp2 = new ccui.LinearLayoutParameter();
        this.textButton.setLayoutParameter(lp2);
        lp2.setGravity(ccui.LinearLayoutParameter.CENTER_HORIZONTAL);
        lp2.setMargin(new ccui.Margin(0, 10, 0, 10));

        var lp3 = new ccui.LinearLayoutParameter();
        this.button_scale9.setLayoutParameter(lp3);
        lp3.setGravity(ccui.LinearLayoutParameter.CENTER_HORIZONTAL);
        lp3.setMargin(new ccui.Margin(0, 10, 0, 10));
    }
});
var UILayoutTest_Layout_Linear_Horizontal = UILayoutTestBase.extend({
    createLayout: function () {
        var layout = new ccui.Layout();
        layout.setLayoutType(ccui.Layout.LINEAR_HORIZONTAL);
        layout.setClippingEnabled(true);
        layout.setContentSize(cc.size(280, 150));
        return layout;
    },
    getText: function () {
        return "Layout Layout Linear Horizontal";
    },
    setLayoutParameter: function () {
        var lp1 = new ccui.LinearLayoutParameter();
        this.button.setLayoutParameter(lp1);
        lp1.setGravity(ccui.LinearLayoutParameter.CENTER_VERTICAL);
        lp1.setMargin(new ccui.Margin(0, 10, 0, 10));

        var lp2 = new ccui.LinearLayoutParameter();
        this.textButton.setLayoutParameter(lp2);
        lp2.setGravity(ccui.LinearLayoutParameter.CENTER_VERTICAL);
        lp2.setMargin(new ccui.Margin(0, 10, 0, 10));

        var lp3 = new ccui.LinearLayoutParameter();
        this.button_scale9.setLayoutParameter(lp3);
        lp3.setGravity(ccui.LinearLayoutParameter.CENTER_VERTICAL);
        lp3.setMargin(new ccui.Margin(0, 10, 0, 10));
    }
});

var UILayoutTest_Layout_Relative = UILayoutTestBase.extend({
    createLayout: function () {
        var layout = new ccui.Layout();
        layout.ignoreContentAdaptWithSize(false);
        layout.setLayoutType(ccui.Layout.RELATIVE);
        layout.sizeType = ccui.Widget.SIZE_PERCENT;
        layout.setSizePercent(cc.p(0.5, 0.5));
        //layout.setContentSize(cc.size(280, 150));
        layout.setPositionType(ccui.Widget.POSITION_PERCENT);
        layout.setPositionPercent(cc.p(0.25, 0.25));
        //layout.setPosition(cc.p(cc.winSize.width/2, cc.winSize.height/2));
        layout.setBackGroundColorType(ccui.Layout.BG_COLOR_SOLID);
        layout.setBackGroundColor(cc.color.GREEN);
        return layout;
    },
    getText: function () {
        return "Layout Layout Relative";
    },
    setLayoutParameter: function () {
        var lp1 = new ccui.RelativeLayoutParameter();
        this.button.setLayoutParameter(lp1);
        lp1.setAlign(ccui.RelativeLayoutParameter.PARENT_TOP_LEFT);

        var lp2 = new ccui.RelativeLayoutParameter();
        this.textButton.setLayoutParameter(lp2);
        lp2.setAlign(ccui.RelativeLayoutParameter.CENTER_IN_PARENT);

        var lp3 = new ccui.RelativeLayoutParameter();
        this.button_scale9.setLayoutParameter(lp3);
        lp3.setAlign(ccui.RelativeLayoutParameter.PARENT_RIGHT_BOTTOM);
    }
});

var UILayoutTest_Layout_Relative_Align_Parent = UIMainLayer.extend({
     init: function(){
         if (this._super()) {
             var widgetSize = this._widget.getContentSize();

             // Add the alert
             var alert = new ccui.Text("Layout Relative Align Parent", "Arial", 20);
             alert.setColor(cc.color(159, 168, 176));
             alert.setPosition(widgetSize.width / 2.0, widgetSize.height / 2.0 - alert.getContentSize().height * 4.5);
             this._mainNode.addChild(alert);

             var root = this._mainNode.getChildByTag(81);
             var background = root.getChildByName("background_Panel");

             // Create the layout
             var layout = new ccui.Layout();
             layout.setLayoutType(ccui.Layout.RELATIVE);
             layout.setContentSize(280, 150);
             layout.setBackGroundColorType(ccui.Layout.BG_COLOR_SOLID);
             layout.setBackGroundColor(cc.color.GREEN);
             var backgroundSize = background.getContentSize();
             layout.setPosition((widgetSize.width - backgroundSize.width) / 2.0 + (backgroundSize.width - layout.width) / 2.0,
                     (widgetSize.height - backgroundSize.height) / 2.0 + (backgroundSize.height - layout.height) / 2.0);
             this._mainNode.addChild(layout);

             // top left
             var button_TopLeft = new ccui.Button("ccs-res/cocosui/animationbuttonnormal.png", "ccs-res/cocosui/animationbuttonpressed.png");
             layout.addChild(button_TopLeft);

             var rp_TopLeft = new ccui.RelativeLayoutParameter();
             rp_TopLeft.setAlign(ccui.RelativeLayoutParameter.PARENT_TOP_LEFT);
             button_TopLeft.setLayoutParameter(rp_TopLeft);

             // top center horizontal
             var button_TopCenter = new ccui.Button("ccs-res/cocosui/animationbuttonnormal.png", "ccs-res/cocosui/animationbuttonpressed.png");
             layout.addChild(button_TopCenter);

             var rp_TopCenter = new ccui.RelativeLayoutParameter();
             rp_TopCenter.setAlign(ccui.RelativeLayoutParameter.PARENT_TOP_CENTER_HORIZONTAL);
             button_TopCenter.setLayoutParameter(rp_TopCenter);

             // top right
             var button_TopRight = new ccui.Button("ccs-res/cocosui/animationbuttonnormal.png", "ccs-res/cocosui/animationbuttonpressed.png");
             layout.addChild(button_TopRight);
             var rp_TopRight = new ccui.RelativeLayoutParameter();
             rp_TopRight.setAlign(ccui.RelativeLayoutParameter.PARENT_TOP_RIGHT);
             button_TopRight.setLayoutParameter(rp_TopRight);

             // left center
             var button_LeftCenter = new ccui.Button("ccs-res/cocosui/animationbuttonnormal.png", "ccs-res/cocosui/animationbuttonpressed.png");
             layout.addChild(button_LeftCenter);
             var rp_LeftCenter = new ccui.RelativeLayoutParameter();
             rp_LeftCenter.setAlign(ccui.RelativeLayoutParameter.PARENT_LEFT_CENTER_VERTICAL);
             button_LeftCenter.setLayoutParameter(rp_LeftCenter);

             // center
             var buttonCenter = new ccui.Button("ccs-res/cocosui/animationbuttonnormal.png", "ccs-res/cocosui/animationbuttonpressed.png");
             layout.addChild(buttonCenter);

             var rpCenter = new ccui.RelativeLayoutParameter();
             rpCenter.setAlign(ccui.RelativeLayoutParameter.CENTER_IN_PARENT);
             buttonCenter.setLayoutParameter(rpCenter);

             // right center
             var button_RightCenter = new ccui.Button("ccs-res/cocosui/animationbuttonnormal.png", "ccs-res/cocosui/animationbuttonpressed.png");
             layout.addChild(button_RightCenter);
             var rp_RightCenter = new ccui.RelativeLayoutParameter();
             rp_RightCenter.setAlign(ccui.RelativeLayoutParameter.PARENT_RIGHT_CENTER_VERTICAL);
             button_RightCenter.setLayoutParameter(rp_RightCenter);


             // left bottom
             var button_LeftBottom = new ccui.Button("ccs-res/cocosui/animationbuttonnormal.png", "ccs-res/cocosui/animationbuttonpressed.png");
             layout.addChild(button_LeftBottom);
             var rp_LeftBottom = new ccui.RelativeLayoutParameter();
             rp_LeftBottom.setAlign(ccui.RelativeLayoutParameter.PARENT_LEFT_BOTTOM);
             button_LeftBottom.setLayoutParameter(rp_LeftBottom);

             // bottom center
             var button_BottomCenter = new ccui.Button("ccs-res/cocosui/animationbuttonnormal.png", "ccs-res/cocosui/animationbuttonpressed.png");
             layout.addChild(button_BottomCenter);
             var rp_BottomCenter = new ccui.RelativeLayoutParameter();
             rp_BottomCenter.setAlign(ccui.RelativeLayoutParameter.PARENT_BOTTOM_CENTER_HORIZONTAL);
             button_BottomCenter.setLayoutParameter(rp_BottomCenter);

             // right bottom
             var button_RightBottom = new ccui.Button("ccs-res/cocosui/animationbuttonnormal.png", "ccs-res/cocosui/animationbuttonpressed.png");
             layout.addChild(button_RightBottom);
             var rp_RightBottom = new ccui.RelativeLayoutParameter();
             rp_RightBottom.setAlign(ccui.RelativeLayoutParameter.PARENT_RIGHT_BOTTOM);
             button_RightBottom.setLayoutParameter(rp_RightBottom);

             return true;
         }
         return false;
     }
});

var UILayoutTest_Layout_Relative_Location = UIMainLayer.extend({
     init: function(){
         if (this._super()) {
             var widgetSize = this._widget.getContentSize();

             // Add the alert
             var alert = new ccui.Text("Layout Relative Location", "Marker Felt", 20);
             alert.setColor(cc.color(159, 168, 176));
             alert.setPosition(widgetSize.width / 2.0, widgetSize.height / 2.0 - alert.height * 4.5);
             this._mainNode.addChild(alert);

             var root = this._mainNode.getChildByTag(81);
             var background = root.getChildByName("background_Panel");

             // Create the layout
             var layout = new ccui.Layout();
             layout.setLayoutType(ccui.Layout.RELATIVE);
             layout.setContentSize(280, 150);
             var backgroundSize = background.getContentSize();
             layout.setPosition((widgetSize.width - backgroundSize.width) / 2.0 + (backgroundSize.width - layout.width) / 2.0,
                     (widgetSize.height - backgroundSize.height) / 2.0 + (backgroundSize.height - layout.height) / 2.0 );
             this._mainNode.addChild(layout);

             // center
             var imageView_Center = new ccui.ImageView("ccs-res/cocosui/scrollviewbg.png");
             layout.addChild(imageView_Center);
             var rp_Center = new ccui.RelativeLayoutParameter();
             rp_Center.setRelativeName("rp_Center");
             rp_Center.setAlign(ccui.RelativeLayoutParameter.CENTER_IN_PARENT);
             imageView_Center.setLayoutParameter(rp_Center);

             // above center
             var imageView_AboveCenter = new ccui.ImageView("ccs-res/cocosui/switch-mask.png");
             layout.addChild(imageView_AboveCenter);
             var rp_AboveCenter = new ccui.RelativeLayoutParameter();
             rp_AboveCenter.setRelativeToWidgetName("rp_Center");
             rp_AboveCenter.setAlign(ccui.RelativeLayoutParameter.LOCATION_ABOVE_CENTER);
             imageView_AboveCenter.setLayoutParameter(rp_AboveCenter);

             // below center
             var imageView_BelowCenter = new ccui.ImageView("ccs-res/cocosui/switch-mask.png");
             layout.addChild(imageView_BelowCenter);
             var rp_BelowCenter = new ccui.RelativeLayoutParameter();
             rp_BelowCenter.setRelativeToWidgetName("rp_Center");
             rp_BelowCenter.setAlign(ccui.RelativeLayoutParameter.LOCATION_BELOW_CENTER);
             imageView_BelowCenter.setLayoutParameter(rp_BelowCenter);

             // left center
             var imageView_LeftCenter = new ccui.ImageView("ccs-res/cocosui/switch-mask.png");
             layout.addChild(imageView_LeftCenter);
             var rp_LeftCenter = new ccui.RelativeLayoutParameter();
             rp_LeftCenter.setRelativeToWidgetName("rp_Center");
             rp_LeftCenter.setAlign(ccui.RelativeLayoutParameter.LOCATION_LEFT_OF_CENTER);
             imageView_LeftCenter.setLayoutParameter(rp_LeftCenter);

             // right center
             var imageView_RightCenter = new ccui.ImageView("ccs-res/cocosui/switch-mask.png");
             layout.addChild(imageView_RightCenter);
             var rp_RightCenter = new ccui.RelativeLayoutParameter();
             rp_RightCenter.setRelativeToWidgetName("rp_Center");
             rp_RightCenter.setAlign(ccui.RelativeLayoutParameter.LOCATION_RIGHT_OF_CENTER);
             imageView_RightCenter.setLayoutParameter(rp_RightCenter);

             return true;
         }
         return false;
     }
});

var UILayoutComponentTest = UIMainLayer.extend({
    _baseLayer: null,
    init: function(){
        if (this._super()) {
            var widgetSize = this._widget.getContentSize();

            this._baseLayer = new cc.LayerColor();
            this._baseLayer.setColor(cc.color(50, 100, 0));
            this._baseLayer.setOpacity(100);
            this._baseLayer.setContentSize(200, 200);
            this._mainNode.addChild(this._baseLayer);

            var button = new ccui.Button("ccs-res/cocosui/animationbuttonnormal.png");
            cc.log("content size should be greater than 0:  width = %f, height = %f", button.width, button.height);
            button.setPosition(widgetSize.width / 2.0, widgetSize.height / 2.0);
            button.addTouchEventListener(this.touchEvent, this);
            button.setZoomScale(0.4);
            button.setPressedActionEnabled(true);
            this._mainNode.addChild(button);

            return true;
        }
        return false;
    },
    touchEvent: function(sender, type){
        switch (type) {
            case ccui.Widget.TOUCH_BEGAN:
                break;
            case ccui.Widget.TOUCH_MOVED:
                break;
            case ccui.Widget.TOUCH_ENDED:
                var widgetSize = this._widget.getContentSize();
                var layerSize = this._baseLayer.getContentSize();
                if (layerSize.width == widgetSize.width && layerSize.height == widgetSize.height)
                    this._baseLayer.setContentSize(200, 200);
                else
                    this._baseLayer.setContentSize(widgetSize);
                ccui.helper.doLayout(this._baseLayer);
                break;
            case ccui.Widget.TOUCH_CANCELED:
                break;
            default:
                break;
        }
    }
});

var UILayoutComponent_Berth_Test = UILayoutComponentTest.extend({
     init: function(){
         if (this._super()){
             var leftTopSprite = new cc.Sprite("ccs-res/cocosui/CloseSelected.png");
             var leftTop = ccui.LayoutComponent.bindLayoutComponent(leftTopSprite);
             leftTop.setHorizontalEdge(ccui.LayoutComponent.horizontalEdge.LEFT);
             leftTop.setVerticalEdge(ccui.LayoutComponent.verticalEdge.TOP);
             this._baseLayer.addChild(leftTopSprite);

             var leftBottomSprite = new cc.Sprite("ccs-res/cocosui/CloseSelected.png");
             var leftBottom = ccui.LayoutComponent.bindLayoutComponent(leftBottomSprite);
             leftBottom.setHorizontalEdge(ccui.LayoutComponent.horizontalEdge.LEFT);
             leftBottom.setVerticalEdge(ccui.LayoutComponent.verticalEdge.BOTTOM);
             this._baseLayer.addChild(leftBottomSprite);

             var rightTopSprite = new cc.Sprite("ccs-res/cocosui/CloseSelected.png");
             var rightTop = ccui.LayoutComponent.bindLayoutComponent(rightTopSprite);
             rightTop.setHorizontalEdge(ccui.LayoutComponent.horizontalEdge.RIGHT);
             rightTop.setVerticalEdge(ccui.LayoutComponent.verticalEdge.TOP);
             this._baseLayer.addChild(rightTopSprite);

             var rightBottomSprite = new cc.Sprite("ccs-res/cocosui/CloseSelected.png");
             var rightBottom = ccui.LayoutComponent.bindLayoutComponent(rightBottomSprite);
             rightBottom.setHorizontalEdge(ccui.LayoutComponent.horizontalEdge.RIGHT);
             rightBottom.setVerticalEdge(ccui.LayoutComponent.verticalEdge.BOTTOM);
             this._baseLayer.addChild(rightBottomSprite);

             ccui.helper.doLayout(this._baseLayer);
             return true;
         }
         return false;
     }
});

var UILayoutComponent_Berth_Stretch_Test = UILayoutComponentTest.extend({
    init: function(){
        if (this._super()) {
            var leftTopSprite = new ccui.ImageView("ccs-res/cocosui/CloseSelected.png");
            leftTopSprite.ignoreContentAdaptWithSize(false);
            var leftTop = ccui.LayoutComponent.bindLayoutComponent(leftTopSprite);
            leftTop.setHorizontalEdge(ccui.LayoutComponent.horizontalEdge.LEFT);
            leftTop.setVerticalEdge(ccui.LayoutComponent.verticalEdge.TOP);
            leftTop.setStretchWidthEnabled(true);
            leftTop.setStretchHeightEnabled(true);
            this._baseLayer.addChild(leftTopSprite);
            leftTop.setSize(leftTopSprite.getContentSize());
            leftTop.setLeftMargin(0);
            leftTop.setTopMargin(0);

            var leftBottomSprite = new ccui.ImageView("ccs-res/cocosui/CloseSelected.png");
            leftBottomSprite.ignoreContentAdaptWithSize(false);
            var leftBottom = ccui.LayoutComponent.bindLayoutComponent(leftBottomSprite);
            leftBottom.setHorizontalEdge(ccui.LayoutComponent.horizontalEdge.LEFT);
            leftBottom.setVerticalEdge(ccui.LayoutComponent.verticalEdge.BOTTOM);
            leftBottom.setStretchWidthEnabled(true);
            leftBottom.setStretchHeightEnabled(true);
            this._baseLayer.addChild(leftBottomSprite);
            leftBottom.setSize(leftBottomSprite.getContentSize());
            leftBottom.setLeftMargin(0);
            leftBottom.setBottomMargin(0);

            var rightTopSprite = new ccui.ImageView("ccs-res/cocosui/CloseSelected.png");
            rightTopSprite.ignoreContentAdaptWithSize(false);
            var rightTop = ccui.LayoutComponent.bindLayoutComponent(rightTopSprite);
            rightTop.setHorizontalEdge(ccui.LayoutComponent.horizontalEdge.RIGHT);
            rightTop.setVerticalEdge(ccui.LayoutComponent.verticalEdge.TOP);
            rightTop.setStretchWidthEnabled(true);
            rightTop.setStretchHeightEnabled(true);
            this._baseLayer.addChild(rightTopSprite);
            rightTop.setSize(rightTopSprite.getContentSize());
            rightTop.setTopMargin(0);
            rightTop.setRightMargin(0);

            var rightBottomSprite = new ccui.ImageView("ccs-res/cocosui/CloseSelected.png");
            rightBottomSprite.ignoreContentAdaptWithSize(false);
            var rightBottom = ccui.LayoutComponent.bindLayoutComponent(rightBottomSprite);
            rightBottom.setHorizontalEdge(ccui.LayoutComponent.horizontalEdge.RIGHT);
            rightBottom.setVerticalEdge(ccui.LayoutComponent.verticalEdge.BOTTOM);
            rightBottom.setStretchWidthEnabled(true);
            rightBottom.setStretchHeightEnabled(true);
            this._baseLayer.addChild(rightBottomSprite);
            rightBottom.setSize(rightBottomSprite.getContentSize());
            rightBottom.setBottomMargin(0);
            rightBottom.setRightMargin(0);

            ccui.helper.doLayout(this._baseLayer);
            return true;
        }
        return false;
    }
});