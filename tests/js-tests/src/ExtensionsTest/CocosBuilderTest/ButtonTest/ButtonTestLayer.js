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
cc.BuilderReader.registerController("TestButtonsLayer", {
    "onCCControlButtonClicked" : function(sender,controlEvent) {
        var str = (function(){
            switch(controlEvent) {
                case cc.CONTROL_EVENT_TOUCH_DOWN: return "Touch Down.";
                case cc.CONTROL_EVENT_TOUCH_DRAG_INSIDE: return "Touch Drag Inside.";
                case cc.CONTROL_EVENT_TOUCH_DRAG_OUTSIDE: return "Touch Drag Outside.";
                case cc.CONTROL_EVENT_TOUCH_DRAG_ENTER: return "Touch Drag Enter.";
                case cc.CONTROL_EVENT_TOUCH_DRAG_EXIT: return "Touch Drag Exit.";
                case cc.CONTROL_EVENT_TOUCH_UP_INSIDE: return "Touch Up Inside.";
                case cc.CONTROL_EVENT_TOUCH_UP_OUTSIDE: return "Touch Up Outside.";
                case cc.CONTROL_EVENT_TOUCH_CANCEL: return "Touch Cancel.";
                case cc.CONTROL_EVENT_VALUECHANGED: return "Value Changed.";
            }
            return "";
        })();
        this["mCCControlEventLabel"].setString(str);
    }
});
