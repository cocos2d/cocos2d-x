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

Projectile = cc.ComponentJS.extend({

    sceneJS: null,

    onEnter: function() {
        var sceneScriptComponent = this.getOwner().getParent().getComponent("sceneJSComponent");
        this.sceneJS = sceneScriptComponent.getScriptObject();
    },

    update: function(dt) {
        // if there is any enemy collides with this projectile, then
        // remove this projectile and all collided enemies

        var owner = this.getOwner();
        var projectileX = owner.getPositionX();
        var projectileY = owner.getPositionY();
        var projectileContentSize = owner.getContentSize();
        var projectileRect = cc.rect(projectileX, projectileY, 
                projectileContentSize.width, projectileContentSize.height);

        var scene = owner.getParent();
        var enemies = this.sceneJS.enemies;
        var removeOwner = false;

        for (var i = 0; i < enemies.length; i++) {
            var enemy = enemies[i];
            var enemyX = enemy.getPositionX();
            var enemyY = enemy.getPositionY();
            var enemyContentSize = enemy.getContentSize();
            var enemyRect = cc.rect(enemyX, enemyY, 
                    enemyContentSize.width, enemyContentSize.height);
            if (cc.rectIntersectsRect(projectileRect, enemyRect)) {
                enemies.splice(i, 1);
                scene.removeChild(enemy, true);
                this.sceneJS.increaseCount();
                removeOwner = true;
                break;
            }
        }

        if (removeOwner == true) {
            scene.removeChild(owner, true);
        }
    }
});