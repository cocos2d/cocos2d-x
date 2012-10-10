var Enemy = cc.Sprite.extend({
    eID:0,
    active:true,
    speed:200,
    bulletSpeed:-200,
    HP:15,
    bulletPowerValue:1,
    moveType:null,
    scoreValue:200,
    zOrder:1000,
    delayTime:1 + 1.2 * Math.random(),
    attackMode:MW.ENEMY_MOVE_TYPE.NORMAL,
    _hurtColorLife:0,
    ctor:function (arg) {
        // needed for JS-Bindings compatibility
        cc.associateWithNative( this, cc.Sprite );

        this.HP = arg.HP;
        this.moveType = arg.moveType;
        this.scoreValue = arg.scoreValue;
        this.attackMode = arg.attackMode;

        this.initWithSpriteFrameName(arg.textureName);
        this.schedule(this.shoot, this.delayTime);
    },
    _timeTick:0,
    update:function (dt) {
        if (this.HP <= 0) {
            this.active = false;
        }
        this._timeTick += dt;
        if (this._timeTick > 0.1) {
            this._timeTick = 0;
            if (this._hurtColorLife > 0) {
                this._hurtColorLife--;
            }
            if (this._hurtColorLife == 1) {
                this.setColor( cc.WHITE );
            }
        }
    },
    destroy:function () {
        MW.SCORE += this.scoreValue;
        var a = new Explosion();
        a.setPosition(this.getPosition());
        this.getParent().addChild(a);
        spark(this.getPosition(),this.getParent(), 1.2, 0.7);
        cc.ArrayRemoveObject(MW.CONTAINER.ENEMIES,this);
        this.removeFromParentAndCleanup(true);
        if(MW.SOUND){
            cc.AudioEngine.getInstance().playEffect(s_explodeEffect);
        }
    },
    shoot:function () {
        var p = this.getPosition();
        var b = new Bullet(this.bulletSpeed, "W2.png", this.attackMode);
        MW.CONTAINER.ENEMY_BULLETS.push(b);
        this.getParent().addChild(b, b.zOrder, MW.UNIT_TAG.ENMEY_BULLET);
        b.setPosition(cc.p(p.x, p.y - this.getContentSize().height * 0.2));
    },
    hurt:function () {
        this._hurtColorLife = 2;
        this.HP--;
        this.setColor( cc.RED );
    },
    collideRect:function(){
        var a = this.getContentSize();
        var p = this.getPosition();
        return cc.rect(p.x - a.width/2, p.y - a.height/4,a.width,a.height/2);
    }
});

Enemy.sharedEnemy = function(){
    cc.SpriteFrameCache.getInstance().addSpriteFrames(s_Enemy_plist, s_Enemy);
};
