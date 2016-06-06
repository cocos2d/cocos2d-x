/****************************************************************************
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

var CCSIssueAnimationsWithOnlyOneFrameLayer = cc.Layer.extend({

    onEnter: function(){
        cc.Layer.prototype.onEnter.call(this);

		var json = ccs.load(s_testIssueAnimationsWithOnlyOneFrame_json);
		var jsonNode = json.node;
		jsonNode.x = this.getContentSize().width * 0.5 - jsonNode.getContentSize().width * 0.5;
		jsonNode.y = this.getContentSize().height * 0.5 - jsonNode.getContentSize().height * 0.5;
		
        this.addChild(jsonNode);

		var winSize = director.getWinSize();
        var logLabel = new cc.LabelTTF("Issue #15714: Animations with only one frame are allowed now", "Thonburi", 16);
        this.addChild(logLabel);
        logLabel.x = winSize.width / 2;
	    logLabel.y = winSize.height / 3;
		
		var animationOneFramePosition = ccs.actionManager.getActionByName(
		  s_testIssueAnimationsWithOnlyOneFrame_json,
		  "AnimationOneFramePosition"
		);
		
		var animationOneFrameRotation = ccs.actionManager.getActionByName(
		  s_testIssueAnimationsWithOnlyOneFrame_json,
		  "AnimationOneFrameRotation"
		);
		
		var delayTime = 5;
		var that = this;
		this.runAction(cc.sequence(
			cc.delayTime(delayTime),
			cc.callFunc(function(target) {
				if(animationOneFramePosition != null)
				{
					animationOneFramePosition.play();
					logLabel.setString("Animation with only one frame played! Image position should change");
				}
			}, this),
			cc.delayTime(delayTime),
			cc.callFunc(function(target) {
				if(animationOneFrameRotation != null)
				{
					animationOneFrameRotation.play();
					logLabel.setString("Animation with only one frame played! Image rotation should change");
				}
			}, this)
		));
		
    }
});

var CCSIssueAnimationsWithOnlyOneFrameScene = cc.Scene.extend({

    onEnter: function(){
        cc.Scene.prototype.onEnter.call(this);

        var label = new cc.LabelTTF("Back", "fonts/arial.ttf", 20);
        //#endif
        var pMenuItem = new cc.MenuItemLabel(label, this.BackCallback, this);

        var pMenu = new cc.Menu(pMenuItem);

        pMenu.setPosition( cc.p(0, 0) );
        pMenuItem.setPosition(cc.pAdd(cc.visibleRect.bottomRight,cc.p(-50,25)));

        this.addChild(pMenu, 1);
    },
    runThisTest: function(){
        var pLayer = new CCSIssueAnimationsWithOnlyOneFrameLayer();
        this.addChild(pLayer);
        cc.director.runScene(this);
    },
    BackCallback: function(pSender){
        var pScene = new CCSIssueTestScene();
        pScene.runThisTest();
    }
});