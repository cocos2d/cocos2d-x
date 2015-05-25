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

var UITextFieldEditorTest = UIBaseLayer.extend({
    ctor: function () {
        this._super();
        var root = this._parseUIFile("ccs-res/cocosui/UIEditorTest/UITextField/textfield_1.json");
        this._mainNode.addChild(root);

        var back_label =ccui.helper.seekWidgetByName(root, "back");
        back_label.addTouchEventListener(this.backEvent,this);

        var textField_normal = ccui.helper.seekWidgetByName(root, "TextField_1109");
        textField_normal.addEventListener(this.textFieldEvent,this);

        var textField_max_character = ccui.helper.seekWidgetByName(root, "TextField_1110");
        textField_max_character.addEventListener(this.textFieldEvent,this);

        var textField_password = ccui.helper.seekWidgetByName(root, "TextField_1107");
        textField_password.addEventListener(this.textFieldEvent,this);
    },
    textFieldEvent: function (sender, type) {
        switch (type) {
            case ccui.TextField. EVENT_ATTACH_WITH_IME:
                this._topDisplayText.setString("attach with IME");
                break;
            case ccui.TextField. EVENT_DETACH_WITH_IME:
                this._topDisplayText.setString("detach with IME");
                break;
            case ccui.TextField. EVENT_INSERT_TEXT:
                this._topDisplayText.setString("insert words");
                break;
            case ccui.TextField. EVENT_DELETE_BACKWARD:
                this._topDisplayText.setString("delete word");
                break;
            default:
                break;
        }
    }
});
