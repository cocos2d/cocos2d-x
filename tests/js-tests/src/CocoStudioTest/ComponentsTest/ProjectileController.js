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

var ProjectileController = ccs.ComController.extend({
    ctor: function () {
        this._super();
        this._name = "ProjectileController";
    },
    init: function () {
        return true;
    },

    onEnter: function () {
        var winSize = cc.director.getWinSize();
        this.getOwner().x = 30;
	    this.getOwner().y = winSize.height / 2;
        this.getOwner().tag = 3;
        var com = this.getOwner().parent.getComponent("SceneController");
        com.getProjectiles().push(this.getOwner());
    },

    onExit: function () {
    },

    update: function (dt) {
        var com = this.getOwner().parent.getComponent("SceneController");
        var targets = com.getTargets();

        var projectile = this.getOwner();
        var projectileRect = cc.rect(projectile.x - (projectile.width / 2), projectile.y - (projectile.height / 2), projectile.width, projectile.height);

        var targetsToDelete = [];
        var target = null;
        var targetSize = null;
        for (var i = 0; i < targets.length; i++) {
            target = targets[i];
            var targetRect = cc.rect(target.x - (target.width / 2), target.y - (target.height / 2), target.width, target.height);
            if (cc.rectIntersectsRect(projectileRect, targetRect)) {
                targetsToDelete.push(target);
            }
        }

        for (var i = 0; i < targetsToDelete.length; i++) {
            var target = targetsToDelete[i];
            target.getComponent("EnemyController").die();
        }

        var isDied = targetsToDelete.length;

        if (isDied) {
            this.die();
        }
    },

    move: function (x, y) {
        var winSize = cc.director.getWinSize();

        var offX = x - this.getOwner().x;
        var offY = y - this.getOwner().y;

        if (offX <= 0) return;

        // Determine where we wish to shoot the projectile to
        var realX = winSize.width + (this.getOwner().width / 2);
        var ratio = offY / offX;
        var realY = (realX * ratio) + this.getOwner().y;
        var realDest = cc.p(realX, realY);

        // Determine the length of how far we're shooting
        var offRealX = realX - this.getOwner().x;
        var offRealY = realY - this.getOwner().y;
        var length = Math.sqrt((offRealX * offRealX) + (offRealY * offRealY));
        var velocity = 480 / 1; // 480pixels/1sec
        var realMoveDuration = length / velocity;

        // Move projectile to actual endpoint
        this.getOwner().runAction(cc.sequence(
            cc.moveTo(realMoveDuration, realDest),
            cc.callFunc(function () {
                var sceneController = this.getOwner().parent.getComponent("SceneController");
                sceneController.spriteMoveFinished(this.getOwner());
            }, this)));

    },

    die: function () {
        var com = this.getOwner().parent.getComponent("SceneController");
        var projectiles = com.getProjectiles();
        cc.arrayRemoveObject(projectiles, this.getOwner());
        this.getOwner().removeFromParent(true);
    }

});

ProjectileController.create = function () {
    var controller = new ProjectileController();
    controller.init();
    return controller;
};