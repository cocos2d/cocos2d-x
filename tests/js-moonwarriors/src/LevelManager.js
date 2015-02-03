/****************************************************************************
 Cocos2d-html5 show case : Moon Warriors

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
 FITNESS FOR A PARTICULAR PURPOSE AND NON INFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.

 @Authors:
 Programmer: Shengxiang Chen (陈升想), Dingping Lv (吕定平), Ricardo Quesada
 Effects animation: Hao Wu (吴昊)
 Quality Assurance: Sean Lin (林顺)
 ****************************************************************************/

var LevelManager = cc.Class.extend({
    _currentLevel:null,
    _gameLayer:null,
    ctor:function(gameLayer){
        if(!gameLayer){
            throw "gameLayer must be non-nil";
        }
        this._currentLevel = Level1;
        this._gameLayer = gameLayer;
        this.setLevel(this._currentLevel);
    },

    setLevel:function(level){
        var locCurrentLevelEnemies = this._currentLevel.enemies;
        for(var i = 0; i< level.enemies.length; i++)
            locCurrentLevelEnemies[i].ShowTime = this._minuteToSecond(locCurrentLevelEnemies[i].ShowTime);
    },
    _minuteToSecond:function(minuteStr){
        if(!minuteStr)
            return 0;
        if(typeof(minuteStr) !=  "number"){
            var mins = minuteStr.split(':');
            if(mins.length == 1){
                return parseInt(mins[0],10);
            }else {
                return parseInt(mins[0],10 )* 60 + parseInt(mins[1],10);
            }
        }
        return minuteStr;
    },

    loadLevelResource:function(deltaTime){
        if(MW.ACTIVE_ENEMIES>= this._currentLevel.enemyMax){
            return;
        }
        //load enemy
        var locCurrentLevel = this._currentLevel;
        for(var i = 0; i< locCurrentLevel.enemies.length; i++){
            var selEnemy = locCurrentLevel.enemies[i];
            if(selEnemy){
                if(selEnemy.ShowType === "Once"){
                    if(selEnemy.ShowTime == deltaTime){
                        for(var tIndex = 0; tIndex < selEnemy.Types.length;tIndex++ ){
                            this.addEnemyToGameLayer(selEnemy.Types[tIndex]);
                        }
                    }
                }else if(selEnemy.ShowType === "Repeate"){
                    if(deltaTime % selEnemy.ShowTime === 0){
                        for(var rIndex = 0; rIndex < selEnemy.Types.length;rIndex++ ){
                            this.addEnemyToGameLayer(selEnemy.Types[rIndex]);
                        }
                    }
                }
            }
        }
    },

    addEnemyToGameLayer:function(enemyType){
		var addEnemy = Enemy.getOrCreateEnemy(EnemyType[enemyType]);
        addEnemy.x = 80 + (winSize.width - 160) * Math.random();
	    addEnemy.y = winSize.height;

        var offset, tmpAction;
        var a0=0;
        var a1=0;
        switch (addEnemy.moveType) {
            case MW.ENEMY_MOVE_TYPE.ATTACK:
                offset = cc.p(this._gameLayer._ship.x, this._gameLayer._ship.y);
                tmpAction = cc.moveTo(1, offset);
                break;
            case MW.ENEMY_MOVE_TYPE.VERTICAL:
                offset = cc.p(0, -winSize.height - addEnemy.height);
                tmpAction = cc.moveBy(4, offset);
                break;
            case MW.ENEMY_MOVE_TYPE.HORIZONTAL:
                offset = cc.p(0, -100 - 200 * Math.random());
                a0 = cc.moveBy(0.5, offset);
                a1 = cc.moveBy(1, cc.p(-50 - 100 * Math.random(), 0));
                var onComplete = cc.callFunc(function (pSender) {
                    var a2 = cc.delayTime(1);
                    var a3 = cc.moveBy(1, cc.p(100 + 100 * Math.random(), 0));
                    pSender.runAction(cc.sequence(a2, a3, a2.clone(), a3.reverse()).repeatForever());
                }.bind(addEnemy) );
                tmpAction = cc.sequence(a0, a1, onComplete);
                break;
            case MW.ENEMY_MOVE_TYPE.OVERLAP:
                var newX = (addEnemy.x <= winSize.width / 2) ? MW.WIDTH : -MW.WIDTH;
                a0 = cc.moveBy(4, cc.p(newX, -MW.WIDTH*0.75));
                a1 = cc.moveBy(4, cc.p(-newX,-MW.WIDTH));
                tmpAction = cc.sequence(a0,a1);
                break;
        }

        addEnemy.runAction(tmpAction);
    }
});
