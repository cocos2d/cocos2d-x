var Ship = cc.Sprite.extend({
    speed:220,
    bulletSpeed:900,
    HP:5,
    bulletTypeValue:1,
    bulletPowerValue:1,
    throwBombing:false,
    canBeAttack:true,
    isThrowingBomb:false,
    zOrder:3000,
    maxBulletPowerValue:4,
    appearPosition:cc.p(160, 60),
    _hurtColorLife:0,
    active:true,
    ctor:function () {

        // needed for JS-Bindings compatibility
        cc.associateWithNative( this, cc.Sprite );

        //init life
        var shipTexture = cc.TextureCache.getInstance().addImage(s_ship01);
        this.initWithTexture(shipTexture, cc.rect(0, 0, 60, 38));
        this.setTag(this.zOrder);
        this.setPosition(this.appearPosition);

        // set frame
        var frame0 = cc.SpriteFrame.createWithTexture(shipTexture, cc.rect(0, 0, 60, 38));
        var frame1 = cc.SpriteFrame.createWithTexture(shipTexture, cc.rect(60, 0, 60, 38));

        var animFrames = [];
        animFrames.push(frame0);
        animFrames.push(frame1);

        // ship animate
        var animation = cc.Animation.create(animFrames, 0.1);
        var animate = cc.Animate.create(animation);
        this.runAction(cc.RepeatForever.create(animate));
        this.schedule(this.shoot, 1 / 6);

        //revive effect
        this.canBeAttack = false;
        var ghostSprite = cc.Sprite.createWithTexture(shipTexture, cc.rect(0, 45, 60, 38));
        ghostSprite.setBlendFunc(gl.SRC_ALPHA, gl.ONE);
        ghostSprite.setScale(8);
        ghostSprite.setPosition(this.getContentSize().width / 2, 12);
        this.addChild(ghostSprite, 3000, 99999);
        ghostSprite.runAction(cc.ScaleTo.create(0.5, 1, 1));
        var blinks = cc.Blink.create(3, 9);
        var makeBeAttack = cc.CallFunc.create(function (t) {
            t.canBeAttack = true;
            t.setVisible(true);
            t.removeChild(ghostSprite,true);
        }.bind(this));
        this.runAction(cc.Sequence.create(cc.DelayTime.create(0.5), blinks, makeBeAttack));
    },
    update:function (dt) {

        // Keys are only enabled on the browser
        if( cc.config.deviceType == 'browser' ) {
            var pos = this.getPosition();
            if ((MW.KEYS[cc.KEY.w] || MW.KEYS[cc.KEY.up]) && pos.y <= winSize.height) {
                pos.y += dt * this.speed;
            }
            if ((MW.KEYS[cc.KEY.s] || MW.KEYS[cc.KEY.down]) && pos.y >= 0) {
                pos.y -= dt * this.speed;
            }
            if ((MW.KEYS[cc.KEY.a] || MW.KEYS[cc.KEY.left]) && pos.x >= 0) {
                pos.x -= dt * this.speed;
            }
            if ((MW.KEYS[cc.KEY.d] || MW.KEYS[cc.KEY.right]) && pos.x <= winSize.width) {
                pos.x += dt * this.speed;
            }
            this.setPosition( pos );
        }

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
                this.setColor(cc.WHITE);
            }
        }
    },
    shoot:function (dt) {
        //this.shootEffect();
        var offset = 13;
        var p = this.getPosition();
        var cs = this.getContentSize();
        var a = new Bullet(this.bulletSpeed, "W1.png", MW.ENEMY_MOVE_TYPE.NORMAL);
        MW.CONTAINER.PLAYER_BULLETS.push(a);
        this.getParent().addChild(a, a.zOrder, MW.UNIT_TAG.PLAYER_BULLET);
        a.setPosition(p.x + offset, p.y + 3 + cs.height * 0.3);

        var b = new Bullet(this.bulletSpeed, "W1.png", MW.ENEMY_MOVE_TYPE.NORMAL);
        MW.CONTAINER.PLAYER_BULLETS.push(b);
        this.getParent().addChild(b, b.zOrder, MW.UNIT_TAG.PLAYER_BULLET);
        b.setPosition(p.x - offset, p.y + 3 + cs.height * 0.3);
    },
    destroy:function () {
        MW.LIFE--;
        var p = this.getPosition();
        var myParent = this.getParent();
        myParent.addChild( new Explosion(p) );
        myParent.removeChild(this,true);
        if (MW.SOUND) {
            cc.AudioEngine.getInstance().playEffect(s_shipDestroyEffect);
        }
    },
    hurt:function () {
        if (this.canBeAttack) {
            this._hurtColorLife = 2;
            this.HP--;
            this.setColor(cc.RED);
        }
    },
    collideRect:function(){
        var p = this.getPosition();
        var a = this.getContentSize();
        var r = new cc.rect(p.x - a.width/2, p.y - a.height/2, a.width, a.height/2);
        return r;
    }
});
