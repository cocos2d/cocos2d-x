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

var SceneController = ccs.ComController.extend({
    _targets: null,
    _projectiles: null,
    _addTargetTime: 0,
    _elapsedTime: 0,
    ctor: function () {
        this._super();
        this._name = "SceneController";
        this._targets = [];
        this._projectiles = [];
    },
    init: function () {
        return true;
    },

    onEnter: function () {
        this._addTargetTime = 1;
        this._targets = [];
        this._projectiles = [];
        this.getOwner().getComponent("Audio").playBackgroundMusic("background-music-aac.wav", true);
        this.getOwner().getComponent("CCComAttribute").setInt("KillCount", 0);
    },

    onExit: function () {

    },

    update: function (dt) {
        this._elapsedTime += dt;
        if (this._elapsedTime > this._addTargetTime) {
            this.addTarget();
            this._elapsedTime = 0.0;
        }
    },

    addTarget: function () {
        var target = new cc.Sprite("components/Target.png", cc.rect(0, 0, 27, 40));
        this.getOwner().addChild(target, 1, 2);
        target.addComponent(EnemyController.create());
        target.tag = 2;
        this._targets.push(target);
    },

    spriteMoveFinished: function (sender) {
        var sprite = sender;
        this.getOwner().removeChild(sprite, true);
        if (sprite.tag == 2) {
            cc.arrayRemoveObject(this._targets, sprite);
            var gameOverScene = GameOverScene.create();
            gameOverScene.getLayer().getLabel().setString("You Lose!");
            cc.director.runScene(gameOverScene);
        }
        else if (sprite.tag == 3) {
            cc.arrayRemoveObject(this._projectiles, sprite);
        }

    },

    increaseKillCount: function () {
        var comAttribute = this.getOwner().getComponent("CCComAttribute");
        var projectilesDestroyed = comAttribute.getInt("KillCount");
        comAttribute.setInt("KillCount", ++projectilesDestroyed);
        if (projectilesDestroyed >= 5) {
            var gameOverScene = GameOverScene.create();
            gameOverScene.getLayer().getLabel().setString("You Win!");
            cc.director.runScene(gameOverScene);
        }
    },
    getProjectiles: function () {
        return this._projectiles;
    },
    getTargets: function () {
        return this._targets;
    }
});

SceneController.create = function () {
    var controller = new SceneController();
    controller.init();
    return controller;
};