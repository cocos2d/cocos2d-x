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


var UILabelTest = UIScene.extend({
    init: function () {
        if (this._super()) {
            //init text
            this._topDisplayLabel.setString("");
            this._bottomDisplayLabel.setString("Label");

            // Create the label
            var text = new ccui.Text();
            text.attr({
	            string: "Label",
	            font: "30px AmericanTypewriter",
	            x: this._widget.width / 2,
	            y: this._widget.height / 2 + text.height / 4
            });
            this._mainNode.addChild(text);

            return true;
        }
        return false;
    }
});

var UILabelTest_LineWrap = UIScene.extend({
    init: function () {
        if (this._super()) {
            var widgetSize = this._widget.getContentSize();
            //init text
            this._topDisplayLabel.string = "";
            this._bottomDisplayLabel.string = "Label line wrap";

            // Create the text area
            var text = new ccui.Text();
            text.boundingWidth = 280;
	        text.boundingHeight = 150;
            text.attr({
	            textAlign: cc.TEXT_ALIGNMENT_CENTER,
	            string: "Label can line wrap",
	            font: "32px AmericanTypewriter",
	            x: this._widget.width / 2
            });
	        text.y = this._widget.height / 2 - text.height / 8;
            this._mainNode.addChild(text);

            return true;
        }
        return false;
    }
});


var UILabelTest_TTF = UIScene.extend({
    init: function () {
        if (this._super()) {
            //init text
            this._topDisplayLabel.setString("");
            this._bottomDisplayLabel.setString("Label set TTF font");

            // Create the text area
            var text = new ccui.Text();
            text.boundingWidth = 280;
	        text.boundingHeight = 150;
            text.attr({
	            textAlign: cc.TEXT_ALIGNMENT_CENTER,
	            string: "Label TTF",
	            font: "32px mericanTypewriter",
	            x: this._widget.width / 2,
	            y: this._widget.height / 2 - text.height / 8
            });
            this._mainNode.addChild(text);

            return true;
        }
        return false;
    }
});