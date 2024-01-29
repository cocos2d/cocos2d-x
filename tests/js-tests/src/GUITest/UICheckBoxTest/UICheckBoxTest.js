/****************************************************************************
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

var UICheckBoxTest = UIMainLayer.extend({
    init: function () {
        if (this._super()) {
            //init text
            this._topDisplayLabel.setString("No Event");
            this._bottomDisplayLabel.setString("CheckBox");

            var widgetSize = this._widget.getContentSize();
            // Create the checkbox
            var checkBox = new ccui.CheckBox();
            checkBox.setTouchEnabled(true);
            checkBox.loadTextures("ccs-res/cocosui/check_box_normal.png",
                "ccs-res/cocosui/check_box_normal_press.png",
                "ccs-res/cocosui/check_box_active.png",
                "ccs-res/cocosui/check_box_normal_disable.png",
                "ccs-res/cocosui/check_box_active_disable.png");
            checkBox.x = widgetSize.width / 2.0;
	        checkBox.y = widgetSize.height / 2.0;
            checkBox.addEventListener(this.selectedStateEvent, this);
            this._mainNode.addChild(checkBox);

            return true;
        }
        return false;
    },

    selectedStateEvent: function (sender, type) {
        switch (type) {
            case  ccui.CheckBox.EVENT_UNSELECTED:
                this._topDisplayLabel.setString("Unselected");
                break;
            case ccui.CheckBox.EVENT_SELECTED:
                this._topDisplayLabel.setString("Selected");
                break;

            default:
                break;
        }
    }
});

//2015-01-14
var UICheckBoxDefaultBehaviorTest = UIMainLayer.extend({

    init: function(){
        if(this._super()){
            var widgetSize = this._widget.getContentSize();

            // Add a label in which the checkbox events will be displayed
            this._displayValueLabel = new ccui.Text("No Event", "Marker Felt", 32);
            this._displayValueLabel.setAnchorPoint(cc.p(0.5, -1));
            this._displayValueLabel.setPosition(cc.p(widgetSize.width / 2, widgetSize.height / 2));
            this._mainNode.addChild(this._displayValueLabel);
            this._bottomDisplayLabel.setString("");

            // Add the alert
            var alert = new ccui.Text("Only left two can be clicked!", "Marker Felt", 20);
            alert.setColor(cc.color(159, 168, 176));
            alert.setPosition(cc.p(widgetSize.width / 2, widgetSize.height / 2 - alert.getContentSize().height * 1.75));
            this._mainNode.addChild(alert);

            // Create the checkbox
            var checkBox = new ccui.CheckBox("ccs-res/cocosui/check_box_normal.png", "ccs-res/cocosui/check_box_active.png");
            checkBox.setPosition(cc.p(widgetSize.width / 2 - 50, widgetSize.height / 2));

            this._mainNode.addChild(checkBox);


            // Create the checkbox
            var checkBox2 = new ccui.CheckBox("ccs-res/cocosui/check_box_normal.png", "ccs-res/cocosui/check_box_active.png");
            checkBox2.setPosition(cc.p(widgetSize.width / 2 - 150, widgetSize.height / 2));
            checkBox2.ignoreContentAdaptWithSize(false);
            checkBox2.setZoomScale(0.5);
            checkBox2.setContentSize(cc.size(80,80));
            checkBox2.setName("bigCheckBox");
            this._mainNode.addChild(checkBox2);


            // Create the checkbox
            var checkBoxDisabled = new ccui.CheckBox("ccs-res/cocosui/check_box_normal.png", "ccs-res/cocosui/check_box_active.png");
            checkBoxDisabled.setPosition(cc.p(widgetSize.width / 2 + 20, widgetSize.height / 2));
            checkBoxDisabled.setEnabled(false);
            checkBoxDisabled.setBright(false);
            this._mainNode.addChild(checkBoxDisabled);

            var checkBoxDisabled2 = new ccui.CheckBox("ccs-res/cocosui/check_box_normal.png", "ccs-res/cocosui/check_box_active.png");
            checkBoxDisabled2.setPosition(cc.p(widgetSize.width / 2 + 70, widgetSize.height / 2));
            checkBoxDisabled2.setEnabled(false);
            checkBoxDisabled2.setBright(false);
            checkBoxDisabled2.setSelected(true);
            this._mainNode.addChild(checkBoxDisabled2);
            return true;
        }
    }

});
