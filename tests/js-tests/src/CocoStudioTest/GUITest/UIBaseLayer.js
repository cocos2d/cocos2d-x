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

var UIBaseLayer = cc.Layer.extend({
    _mainNode:null,
    _topDisplayText:null,
    ctor: function () {
        this._super();
        var winSize = cc.director.getWinSize();

        //add main node
        var mainNode = new cc.Node();
        var scale = winSize.height / 320;
        mainNode.attr({anchorX: 0, anchorY: 0, scale: scale, x: (winSize.width - 480 * scale) / 2, y: (winSize.height - 320 * scale) / 2});
        this.addChild(mainNode);

        var topDisplayText = new ccui.Text();
        topDisplayText.attr({
            string: "",
            font: "20px Arial",
            x: 240,
            y: 320-50
        });
        mainNode.addChild(topDisplayText,100);

        this._mainNode = mainNode;
        this._topDisplayText = topDisplayText;
    },

    _parseUIFile: function(file){
        if(cocoStudioOldApiFlag == 0){
            cc.log("ccs.load : %s", file);
            var json = ccs.load(file);
            return json.node;
        }else{
            //ccs.uiReader.widgetFromJsonFile only supports 1.x file.
            cc.log("ccs.uiReader.widgetFromJsonFile : %s", file);
            return ccs.uiReader.widgetFromJsonFile(file)
        }
    },

    backEvent: function (sender, type) {
        if (type == ccui.Widget.TOUCH_ENDED) {
            runGuiTestMain();
        }
    }
});