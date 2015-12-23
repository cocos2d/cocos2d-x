/****************************************************************************
 Copyright (c) 2015 Chukong Technologies Inc.

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

Enemy = cc.ComponentJS.extend({
    onEnter: function () {
        var winSize = cc.director.getVisibleSize();
        var visibleOrigin = cc.director.getVisibleOrigin();
        var owner = this.getOwner();
        var contentSize = owner.getContentSize();
        var minY = contentSize.height / 2;
        var maxY = winSize.height - contentSize.height/2;
        var rangeY = maxY - minY;
        var actualY = 1000 * Math.random() % rangeY + minY;
        owner.setPosition(winSize.width + contentSize.width/2, visibleOrigin.y + actualY);

        var minDuration = 2;
        var maxDuration = 4;
        var rangeDuration = maxDuration - minDuration;
        var actualDuration = 1000 * Math.random() % rangeDuration + minDuration;
        var actionMove = cc.moveTo(actualDuration * 2, cc.p(0 - contentSize.width/2, actualY));
        var sceneScriptComponent = owner.getParent().getComponent("sceneJSComponent");
        var sceneScript = sceneScriptComponent.getScriptObject();
        var actionMoveDone = cc.callFunc(sceneScript.loseGame);
        owner.runAction(cc.sequence(actionMove, actionMoveDone));
    }
});