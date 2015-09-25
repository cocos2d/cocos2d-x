/****************************************************************************
 Copyright (c) 2008-2010 Ricardo Quesada
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

var UILoadingBarEditorTest = UIBaseLayer.extend({
    _count: 0,
    _loadingBar_left_to_right:null,
    _loadingBar_right_to_left:null,
    ctor: function () {
        this._super();
        var root = this._parseUIFile("ccs-res/cocosui/UIEditorTest/UILoadingBar/loadingbar_1.json");
        this._mainNode.addChild(root);

        var back_label =ccui.helper.seekWidgetByName(root, "back");
        back_label.addTouchEventListener(this.backEvent,this);

        this._loadingBar_left_to_right = ccui.helper.seekWidgetByName(root, "LoadingBar_856");
        this._loadingBar_left_to_right.setPercent(0);

        this._loadingBar_right_to_left = ccui.helper.seekWidgetByName(root, "LoadingBar_857");
        this._loadingBar_right_to_left.setPercent(0);

        this.scheduleUpdate();
    },
    update: function (dt) {
        this._count++;
        if (this._count > 100) {
            this._count = 0;
        }
        this._loadingBar_left_to_right.setPercent(this._count);
        this._loadingBar_right_to_left.setPercent(this._count);
    }
});
