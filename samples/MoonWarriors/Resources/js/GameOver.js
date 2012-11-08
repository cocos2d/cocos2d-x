var GameOver = cc.Layer.extend({
    _ship:null,
    _lbScore:0,
    ctor:function() {
        // needed for JS-Bindings compatibility
        cc.associateWithNative( this, cc.Layer);
    },
    init:function () {
        var bRet = false;
        if (this._super()) {
            var sp = cc.Sprite.create(s_loading);
            sp.setAnchorPoint( cc.p(0,0) );
            this.addChild(sp, 0, 1);

            var logo = cc.Sprite.create(s_gameOver);
            logo.setAnchorPoint(cc.p(0,0));
            logo.setPosition(0,300);
            this.addChild(logo,10,1);

            var playAgainNormal = cc.Sprite.create(s_menu, cc.rect(378, 0, 126, 33));
            var playAgainSelected = cc.Sprite.create(s_menu, cc.rect(378, 33, 126, 33));
            var playAgainDisabled = cc.Sprite.create(s_menu, cc.rect(378, 33 * 2, 126, 33));

            var cocos2dhtml5 = cc.Sprite.create(s_cocos2dhtml5);
            cocos2dhtml5.setPosition(160,150);
            this.addChild(cocos2dhtml5,10);
            var playAgain = cc.MenuItemSprite.create(playAgainNormal, playAgainSelected, playAgainDisabled, function(){
                flareEffect(this,this,this.onPlayAgain);
            }.bind(this) );

            var menu = cc.Menu.create(playAgain);
            this.addChild(menu, 1, 2);
            menu.setPosition(winSize.width / 2, 220);

            var lbScore = cc.LabelTTF.create("Your Score:"+MW.SCORE,"Arial Bold",16);
            lbScore.setPosition(160,280);
            lbScore.setColor(cc.c3b(250,179,0));
            this.addChild(lbScore,10);

            var b1 = cc.LabelTTF.create("Download Cocos2d-html5","Arial",14);
            var b2 = cc.LabelTTF.create("Download This Sample","Arial",14);
            var menu1 = cc.MenuItemLabel.create(b1,function(){
                window.location.href = "http://www.cocos2d-x.org/projects/cocos2d-x/wiki/Cocos2d-html5";
            });
            var menu2 = cc.MenuItemLabel.create(b2,function(){
                window.location.href = "https://github.com/ShengxiangChen/MoonWarriors";
            });
            var cocos2dMenu = cc.Menu.create(menu1,menu2);
            cocos2dMenu.alignItemsVerticallyWithPadding(10);
            cocos2dMenu.setPosition(160,80);
            this.addChild(cocos2dMenu);


            if(MW.SOUND){
                cc.AudioEngine.getInstance().playMusic(s_mainMainMusic);
            }

            bRet = true;
        }
        return bRet;
    },
    onPlayAgain:function (pSender) {
        var scene = cc.Scene.create();
        scene.addChild(GameLayer.create());
        scene.addChild(GameControlMenu.create());
        cc.Director.getInstance().replaceScene(cc.TransitionFade.create(1.2,scene));
    }
});

GameOver.create = function () {
    var sg = new GameOver();
    if (sg && sg.init()) {
        return sg;
    }
    return null;
};

GameOver.scene = function () {
    var scene = cc.Scene.create();
    var layer = GameOver.create();
    scene.addChild(layer);
    return scene;
};
