//bullet
var Bullet = cc.Sprite.extend({
    active:true,
    xVelocity:0,
    yVelocity:200,
    power:1,
    HP:1,
    moveType:null,
    zOrder:3000,
    attackMode:MW.ENEMY_MOVE_TYPE.NORMAL,
    parentType:MW.BULLET_TYPE.PLAYER,
    ctor:function (bulletSpeed, weaponType, attackMode) {
        // needed for JS-Bindings compatibility
        cc.associateWithNative( this, cc.Sprite );

        this.yVelocity = -bulletSpeed;
        this.attackMode = attackMode;
        cc.SpriteFrameCache.getInstance().addSpriteFrames(s_bullet_plist);
        this.initWithSpriteFrameName(weaponType);
        this.setBlendFunc(gl.SRC_ALPHA, gl.ONE);
        /*var tmpAction;
         switch (this.attackMode) {
         case MW.ENEMY_MOVE_TYPE.NORMAL:
         tmpAction = cc.MoveBy.create(2, cc.p(this.getPosition().x, 400));
         break;
         case MW.ENEMY_ATTACK_MODE.TSUIHIKIDAN:
         tmpAction = cc.MoveTo.create(2, GameLayer.create()._ship.getPosition());
         break;
         }
         this.runAction(tmpAction);*/
    },
    update:function (dt) {
        var p = this.getPosition();
        p.x -= this.xVelocity * dt;
        p.y -= this.yVelocity * dt;
        this.setPosition( p );
        if (this.HP <= 0) {
            this.active = false;
        }
    },
    destroy:function () {
        var explode = cc.Sprite.create(s_hit);
        explode.setBlendFunc(gl.SRC_ALPHA, gl.ONE);
        explode.setPosition(this.getPosition());
        explode.setRotation(Math.random()*360);
        explode.setScale(0.75);
        this.getParent().addChild(explode,9999);
        cc.ArrayRemoveObject(MW.CONTAINER.ENEMY_BULLETS,this);
        cc.ArrayRemoveObject(MW.CONTAINER.PLAYER_BULLETS,this);
        this.removeFromParentAndCleanup(true);
	
	var removeExplode = cc.CallFunc.create(explode, function(sender) {
		explode.removeFromParentAndCleanup(true);
	    });

        explode.runAction(cc.ScaleBy.create(0.3, 2,2));
        explode.runAction(cc.Sequence.create(cc.FadeOut.create(0.3), removeExplode));
    },
    hurt:function () {
        this.HP--;
    },
    collideRect:function(){
        var p = this.getPosition();
        return cc.rect(p.x - 3, p.y - 3, 6, 6);
    }
});
