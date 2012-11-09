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
        for(var i = 0; i< level.enemies.length; i++){
            this._currentLevel.enemies[i].ShowTime = this._minuteToSecond(this._currentLevel.enemies[i].ShowTime);
        }
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
        //load enemy
        for(var i = 0; i< this._currentLevel.enemies.length; i++){
            var selEnemy = this._currentLevel.enemies[i];
            if(selEnemy){
                if(selEnemy.ShowType == "Once"){
                    if(selEnemy.ShowTime == deltaTime){
                        for(var tIndex = 0; tIndex < selEnemy.Types.length;tIndex++ ){
                            this.addEnemyToGameLayer(selEnemy.Types[tIndex]);
                        }
                    }
                }else if(selEnemy.ShowType == "Repeate"){
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
        var addEnemy = new Enemy(EnemyType[enemyType]);

        var enemypos = cc.p( 80 + (winSize.width - 160) * Math.random(), winSize.height);
        var enemycs =  addEnemy.getContentSize();
        addEnemy.setPosition( enemypos );


        var offset, tmpAction;
        var a0=0;
        var a1=0;
        switch (addEnemy.moveType) {
            case MW.ENEMY_MOVE_TYPE.ATTACK:
                offset = this._gameLayer._ship.getPosition();
                tmpAction = cc.MoveTo.create(1, offset);
                break;
            case MW.ENEMY_MOVE_TYPE.VERTICAL:
                offset = cc.p(0, -winSize.height - enemycs.height);
                tmpAction = cc.MoveBy.create(4, offset);
                break;
            case MW.ENEMY_MOVE_TYPE.HORIZONTAL:
                offset = cc.p(0, -100 - 200 * Math.random());
                a0 = cc.MoveBy.create(0.5, offset);
                a1 = cc.MoveBy.create(1, cc.p(-50 - 100 * Math.random(), 0));
                var onComplete = cc.CallFunc.create(function (pSender) {
                    var a2 = cc.DelayTime.create(1);
                    var a3 = cc.MoveBy.create(1, cc.p(100 + 100 * Math.random(), 0));
                    pSender.runAction(cc.RepeatForever.create(
                        cc.Sequence.create(a2, a3, a2.copy(), a3.reverse())
                    ));
                }.bind(addEnemy) );
                tmpAction = cc.Sequence.create(a0, a1, onComplete);
                break;
            case MW.ENEMY_MOVE_TYPE.OVERLAP:
                var newX = (enemypos.x <= winSize.width / 2) ? 320 : -320;
                a0 = cc.MoveBy.create(4, cc.p(newX, -240));
                a1 = cc.MoveBy.create(4,cc.p(-newX,-320));
                tmpAction = cc.Sequence.create(a0,a1);
                break;
        }

        this._gameLayer.addChild(addEnemy, addEnemy.zOrder, MW.UNIT_TAG.ENEMY);
        MW.CONTAINER.ENEMIES.push(addEnemy);
        addEnemy.runAction(tmpAction);
    }
});
