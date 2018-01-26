/****************************************************************************
 Copyright (c) 2015-2016 Chukong Technologies Inc.
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

require("src/ComponentTest/gameoverscene.js");

Scene = cc.ComponentJS.extend({
    // add a new enemy every second
    durationOfAddEnemy: 1.0,
    // how long past after last time of adding a new enemy
    totalDt: 0,
    numEnemyDestroyed: 0,
    enemies: null,

    onEnter: function() {
        this.enemies = [];
        jsb.AudioEngine.play2d("background-music-aac.mp3", true);
    },

    update: function(dt) {
        this.totalDt += dt;
        if (this.totalDt > this.durationOfAddEnemy) {
            this.addNewEnemy();
            this.totalDt = 0;
        }
    },

    addNewEnemy: function() {
        var owner = this.getOwner();
        var enemy = new cc.Sprite("components/Target.png");
        var enemyJSComponent = new cc.ComponentJS("src/ComponentTest/enemy.js");
        enemy.addComponent(enemyJSComponent);
        owner.addChild(enemy);
        this.enemies.push(enemy);
    },

    loseGame: function(node) {
        var scene = GameOverScene.create("You Lose");
        cc.director.runScene(scene);
    },

    increaseCount: function() {
        this.numEnemyDestroyed = this.numEnemyDestroyed + 1;
        if (this.numEnemyDestroyed >= 5) {
            var scene = GameOverScene.create("You Win!");
            cc.director.runScene(scene);
        }
    }
});