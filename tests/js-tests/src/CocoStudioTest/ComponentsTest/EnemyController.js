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

var EnemyController = ccs.ComController.extend({
    ctor: function () {
        this._super();
        this._name = "EnemyController";
    },
    init: function () {
        return true;
    },

    onEnter: function () {
        // Determine where to spawn the target along the Y axis
        var winSize = cc.director.getWinSize();
        var minY = this.getOwner().height / 2;
        var rangeY = winSize.height - this.getOwner().height;
        var actualY = (Math.random() * rangeY ) + minY;

        // Create the target slightly off-screen along the right edge,
        // and along a random position along the Y axis as calculated
        this.getOwner().x = winSize.width + (this.getOwner().width / 2);
	    this.getOwner().y = actualY;


        // Determine speed of the target
        var minDuration = 2.0;
        var maxDuration = 4.0;
        var rangeDuration = maxDuration - minDuration;
        var actualDuration = ( Math.random() % rangeDuration ) + minDuration;

        // Create the actions
        var actionMove = cc.moveTo(actualDuration, cc.p(0 - this.getOwner().width / 2, actualY));
        var actionMoveDone = cc.callFunc(function () {
            var comController = this.getOwner().parent.getComponent("SceneController");
            comController.spriteMoveFinished(this.getOwner());
        }, this);
        this.getOwner().runAction(cc.sequence(actionMove, actionMoveDone));
    },

    onExit: function () {
    },

    update: function (dt) {

    },

    die: function () {
        var com = this.getOwner().parent.getComponent("SceneController");
        var targets = com.getTargets();
        cc.arrayRemoveObject(targets, this.getOwner());
        this.getOwner().removeFromParent(true);
        com.increaseKillCount();
    }
});
EnemyController.create = function () {
    var controller = new EnemyController();
    controller.init();
    return controller;
};
