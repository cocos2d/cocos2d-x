//
// MoonWarriors
//
// Handles the Game Logic
//

STATE_PLAYING = 0;
STATE_GAMEOVER = 1;

var GameLayer = cc.Layer.extend({
    _time:null,
    _ship:null,
    _backSky:null,
    _backSkyHeight:0,
    _backSkyRe:null,
    _backTileMap:null,
    _backTileMapHeight:0,
    _backTileMapRe:null,
    _levelManager:null,
    _tmpScore:0,
    _isBackSkyReload:false,
    _isBackTileReload:false,
    lbScore:null,
    screenRect:null,
    explosionAnimation:[],
    _beginPos:cc.p(0, 0),
    _state:STATE_PLAYING,
    ctor:function () {
        cc.associateWithNative( this, cc.Layer );
    },
    init:function () {
        var bRet = false;
        if (this._super()) {

            // reset global values
            MW.CONTAINER.ENEMIES = [];
            MW.CONTAINER.ENEMY_BULLETS = [];
            MW.CONTAINER.PLAYER_BULLETS = [];
            MW.SCORE = 0;
            MW.LIFE = 4;
            this._state = STATE_PLAYING;

            Explosion.sharedExplosion();
            Enemy.sharedEnemy();
            winSize = cc.Director.getInstance().getWinSize();
            this._levelManager = new LevelManager(this);
            this.initBackground();
            this.screenRect = cc.rect(0, 0, winSize.width, winSize.height + 10);

            // score
            this.lbScore = cc.LabelBMFont.create("Score: 0", s_arial14_fnt);
            this.lbScore.setAnchorPoint( cc.p(1,0) );
            this.lbScore.setAlignment( cc.TEXT_ALIGNMENT_RIGHT );
            this.addChild(this.lbScore, 1000);
            this.lbScore.setPosition(cc.p(winSize.width - 5 , winSize.height - 30));

            // ship life
            var shipTexture = cc.TextureCache.getInstance().addImage(s_ship01);
            var life = cc.Sprite.createWithTexture(shipTexture, cc.rect(0, 0, 60, 38));
            life.setScale(0.6);
            life.setPosition(cc.p(30, 460));
            this.addChild(life, 1, 5);

            // ship Life count
            this._lbLife = cc.LabelTTF.create("0", "Arial", 20);
            this._lbLife.setPosition(cc.p(60, 463));
            this._lbLife.setColor(cc.RED);
            this.addChild(this._lbLife, 1000);

            // ship
            this._ship = new Ship();
            this.addChild(this._ship, this._ship.zOrder, MW.UNIT_TAG.PLAYER);

            // accept touch now!

            var t = cc.config.deviceType;
            if( t == 'browser' )  {
                this.setTouchEnabled(true);
                this.setKeyboardEnabled(true);
            } else if( t == 'desktop' ) {
                this.setMouseEnabled(true);
            } else if( t == 'mobile' ) {
                this.setTouchEnabled(true);
            }

            // schedule
            this.scheduleUpdate();
            this.schedule(this.scoreCounter, 1);

            if (MW.SOUND) {
                cc.AudioEngine.getInstance().playBackgroundMusic(s_bgMusic, true);
            }

            bRet = true;
        }
        return bRet;
    },
    scoreCounter:function () {
        if( this._state == STATE_PLAYING ) {
            this._time++;

            var minute = 0 | (this._time / 60);
            var second = this._time % 60;
            minute = minute > 9 ? minute : "0" + minute;
            second = second > 9 ? second : "0" + second;
            var curTime = minute + ":" + second;
            this._levelManager.loadLevelResource(this._time);
        }
    },

    onTouchesMoved:function (touches, event) {
        this.processEvent( touches[0] );
    },

    onMouseDragged:function( event ) {
        this.processEvent( event );
    },

    processEvent:function( event ) {
        if( this._state == STATE_PLAYING ) {
            var delta = event.getDelta();
            var curPos = this._ship.getPosition();
            curPos= cc.pAdd( curPos, delta );
            curPos = cc.pClamp(curPos, cc.POINT_ZERO, cc.p(winSize.width, winSize.height) );
            this._ship.setPosition( curPos );
        }
    },

    onKeyDown:function (e) {
        MW.KEYS[e] = true;
    },

    onKeyUp:function (e) {
        MW.KEYS[e] = false;
    },

    update:function (dt) {
        if( this._state == STATE_PLAYING ) {
            this.checkIsCollide();
            this.removeInactiveUnit(dt);
            this.checkIsReborn();
            this.updateUI();
        }

        if( cc.config.deviceType == 'browser' )
            cc.$("#cou").innerHTML = "Ship:" + 1 + ", Enemy: " + MW.CONTAINER.ENEMIES.length + ", Bullet:" + MW.CONTAINER.ENEMY_BULLETS.length + "," + MW.CONTAINER.PLAYER_BULLETS.length + " all:" + this.getChildren().length;
    },
    checkIsCollide:function () {
        var selChild, bulletChild;
        //check collide
        var i =0;
        for (i = 0; i < MW.CONTAINER.ENEMIES.length; i++) {
            selChild = MW.CONTAINER.ENEMIES[i];
            for (var j = 0; j < MW.CONTAINER.PLAYER_BULLETS.length; j++) {
                bulletChild = MW.CONTAINER.PLAYER_BULLETS[j];
                if (this.collide(selChild, bulletChild)) {
                    bulletChild.hurt();
                    selChild.hurt();
                }
                if (!cc.rectIntersectsRect(this.screenRect, bulletChild.getBoundingBox() )) {
                    bulletChild.destroy();
                }
            }
            if (this.collide(selChild, this._ship)) {
                if (this._ship.active) {
                    selChild.hurt();
                    this._ship.hurt();
                }
            }
            if (!cc.rectIntersectsRect(this.screenRect, selChild.getBoundingBox() )) {
                selChild.destroy();
            }
        }

        for (i = 0; i < MW.CONTAINER.ENEMY_BULLETS.length; i++) {
            selChild = MW.CONTAINER.ENEMY_BULLETS[i];
            if (this.collide(selChild, this._ship)) {
                if (this._ship.active) {
                    selChild.hurt();
                    this._ship.hurt();
                }
            }
            if (!cc.rectIntersectsRect(this.screenRect, selChild.getBoundingBox() )) {
                selChild.destroy();
            }
        }
    },
    removeInactiveUnit:function (dt) {
        var selChild, layerChildren = this.getChildren();
        for (var i in layerChildren) {
            selChild = layerChildren[i];
            if (selChild) {
                if( typeof selChild.update == 'function' ) {
                    selChild.update(dt);
                    var tag = selChild.getTag();
                    if ((tag == MW.UNIT_TAG.PLAYER) || (tag == MW.UNIT_TAG.PLAYER_BULLET) ||
                        (tag == MW.UNIT_TAG.ENEMY) || (tag == MW.UNIT_TAG.ENMEY_BULLET)) {
                        if (selChild && !selChild.active) {
                            selChild.destroy();
                        }
                    }
                }
            }
        }
    },
    checkIsReborn:function () {
        if (MW.LIFE > 0 && !this._ship.active) {
            // ship
            this._ship = new Ship();
            this.addChild(this._ship, this._ship.zOrder, MW.UNIT_TAG.PLAYER);
        }
        else if (MW.LIFE <= 0 && !this._ship.active) {
            this._state = STATE_GAMEOVER;
            // XXX: needed for JS bindings.
            this._ship = null;
            this.runAction(cc.Sequence.create(
                cc.DelayTime.create(0.2),
                cc.CallFunc.create(this, this.onGameOver)));
        }
    },
    updateUI:function () {
        if (this._tmpScore < MW.SCORE) {
            this._tmpScore += 5;
        }
        this._lbLife.setString(MW.LIFE);
        this.lbScore.setString("Score: " + this._tmpScore);
    },
    collide:function (a, b) {
        var aRect = a.collideRect();
        var bRect = b.collideRect();
        if (cc.rectIntersectsRect(aRect, bRect)) {
            return true;
        }
    },
    initBackground:function () {
        // bg
        this._backSky = cc.Sprite.create(s_bg01);
        this._backSky.setAnchorPoint(cc.p(0, 0));
        this._backSkyHeight = this._backSky.getContentSize().height;
        this.addChild(this._backSky, -10);

        //tilemap
        this._backTileMap = cc.TMXTiledMap.create(s_level01);
        this.addChild(this._backTileMap, -9);
        this._backTileMapHeight = this._backTileMap.getMapSize().height * this._backTileMap.getTileSize().height;

        this._backSkyHeight -= 48;
        this._backTileMapHeight -= 200;
        this._backSky.runAction(cc.MoveBy.create(3, cc.p(0, -48)));
        this._backTileMap.runAction(cc.MoveBy.create(3, cc.p(0, -200)));

        this.schedule(this.movingBackground, 3);
    },
    movingBackground:function () {
        this._backSky.runAction(cc.MoveBy.create(3, cc.p(0, -48)));
        this._backTileMap.runAction(cc.MoveBy.create(3, cc.p(0, -200)));
        this._backSkyHeight -= 48;
        this._backTileMapHeight -= 200;

        if (this._backSkyHeight <= winSize.height) {
            if (!this._isBackSkyReload) {
                this._backSkyRe = cc.Sprite.create(s_bg01);
                this._backSkyRe.setAnchorPoint(cc.p(0, 0));
                this.addChild(this._backSkyRe, -10);
                this._backSkyRe.setPosition(cc.p(0, winSize.height));
                this._isBackSkyReload = true;
            }
            this._backSkyRe.runAction(cc.MoveBy.create(3, cc.p(0, -48)));
        }
        if (this._backSkyHeight <= 0) {
            this._backSkyHeight = this._backSky.getContentSize().height;
            this.removeChild(this._backSky, true);
            this._backSky = this._backSkyRe;
            this._backSkyRe = null;
            this._isBackSkyReload = false;
        }

        if (this._backTileMapHeight <= winSize.height) {
            if (!this._isBackTileReload) {
                this._backTileMapRe = cc.TMXTiledMap.create(s_level01);
                this.addChild(this._backTileMapRe, -9);
                this._backTileMapRe.setPosition(cc.p(0, winSize.height));
                this._isBackTileReload = true;
            }
            this._backTileMapRe.runAction(cc.MoveBy.create(3, cc.p(0, -200)));
        }
        if (this._backTileMapHeight <= 0) {
            this._backTileMapHeight = this._backTileMapRe.getMapSize().height * this._backTileMapRe.getTileSize().height;
            this.removeChild(this._backTileMap, true);
            this._backTileMap = this._backTileMapRe;
            this._backTileMapRe = null;
            this._isBackTileReload = false;
        }
    },
    onGameOver:function () {
        var scene = cc.Scene.create();
        scene.addChild(GameOver.create());
        cc.Director.getInstance().replaceScene(cc.TransitionFade.create(1.2, scene));
    }
});

GameLayer.create = function () {
    var sg = new GameLayer();
    if (sg && sg.init()) {
        return sg;
    }
    return null;
};

GameLayer.scene = function () {
    var scene = cc.Scene.create();
    var layer = GameLayer.create();
    scene.addChild(layer, 1);
    return scene;
};
