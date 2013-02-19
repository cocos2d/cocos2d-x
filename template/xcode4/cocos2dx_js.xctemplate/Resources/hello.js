require("jsb.js");

try {
    
    director = cc.Director.getInstance();
    winSize = director.getWinSize();
    centerPos = cc.p( winSize.width/2, winSize.height/2 );
    
    //
    // Main Menu
    //
    
    // 'MenuLayerController' class is instantiated by CocosBuilder Reader
    var MenuLayerController = function () {
    };
    
    // callback triggered by CCB Reader once the instance is created
    MenuLayerController.prototype.onDidLoadFromCCB = function () {
        // Spin the 'o' in the title
        var o = this.titleLabel.getChildByTag(8);
        
        var a_delay = cc.DelayTime.create(6);
        var a_tint = cc.TintTo.create(0.5, 0, 255, 0);
        var a_rotate = cc.RotateBy.create(4, 360);
        var a_rep = cc.Repeat.create(a_rotate, 1000);
        var a_seq = cc.Sequence.create(a_delay, a_tint, a_delay.copy(), a_rep);
        o.runAction(a_seq);
    };
    
    // callbacks for the menu, defined in the editor
    MenuLayerController.prototype.onPlay = function () {
        director.replaceScene( cc.TransitionFade.create(1, game.getPlayScene()) );
    };
    
    MenuLayerController.prototype.onOptions = function () {
        director.replaceScene( cc.TransitionFade.create(1, game.getOptionsScene()) );
    };
    
    MenuLayerController.prototype.onAbout = function () {
        director.replaceScene( cc.TransitionZoomFlipY.create(1, game.getAboutScene()) );
    };

    var AboutLayerController = function() {}
    
    AboutLayerController.prototype.onDidLoadFromCCB = function () {
        var back = cc.MenuItemFont.create("Back", this.onBack, this);
        back.setColor(cc.BLACK);
        var menu = cc.Menu.create(back);
        this.rootNode.addChild(menu);
        menu.zOrder = 100;
        menu.alignItemsVertically();
        menu.setPosition(winSize.width - 50, 50);
    };
    
    AboutLayerController.prototype.onBack = function () {
        director.replaceScene( cc.TransitionFade.create(1, game.getMainMenuScene()));
    };
    
    var GameCreator = function() {
        
        var self = {};
        self.callbacks = {};
        
        self.getPlayScene = function() {
            
            var scene = new cc.Scene();
            var layer = new cc.LayerGradient();
            
            layer.init(cc.c4b(0, 0, 0, 255), cc.c4b(0, 128, 255, 255));
            
            var lab = "Houston we have liftoff!";
            var label = cc.LabelTTF.create(lab, "Arial", 28);
            layer.addChild(label, 1);
            label.setPosition( cc.p(winSize.width / 2, winSize.height / 2));
            
            var back = cc.MenuItemFont.create("Back", self.callbacks.onBack, self.callbacks);
            back.setColor( cc.BLACK );
            
            var menu = cc.Menu.create( back );
            layer.addChild( menu );
            menu.alignItemsVertically();
            menu.setPosition( cc.p( winSize.width - 50, 50) );
            
            scene.addChild(layer);
            
            return scene;
        };
        
        self.getMainMenuScene = function() {
            return cc.BuilderReader.loadAsScene("MainMenu.ccbi");
        };
        
        self.getOptionsScene = function() {

            var l = cc.LayerGradient.create();
            l.init(cc.c4b(0, 0, 0, 255), cc.c4b(255, 255, 255, 255));

            var scene = cc.Scene.create();
            
            var label1 = cc.LabelBMFont.create("MUSIC ON", "konqa32.fnt" );
            var item1 = cc.MenuItemLabel.create(label1);
            var label2 = cc.LabelBMFont.create("MUSIC OFF", "konqa32.fnt" );
            var item2 = cc.MenuItemLabel.create(label2);
            var toggle = cc.MenuItemToggle.create( item1, item2 );
            
            this.onMusicToggle = function( sender ) {
                cc.log("OptionsScene onMusicToggle...");
            };
            
            toggle.setCallback( this.onMusicToggle, this);
            
            var back = cc.MenuItemFont.create("Back", self.callbacks.onBack, self.callbacks);
            var menu = cc.Menu.create( toggle, back );
            l.addChild( menu );
            menu.alignItemsVertically();
            menu.setPosition( centerPos );

            scene.addChild(l);
            
            return scene;
        };
        
     
        self.getAboutScene = function() {
            
            var scene = cc.Scene.create();
            var l = cc.Layer.create();
            var about = cc.BuilderReader.load("About.ccbi", l);
            l.addChild( about )
            
            scene.addChild( l );
            
            return scene;
        };
        
        // Manual Callbacks
        
        self.callbacks.onBack  = function( sender) {
            director.replaceScene( cc.TransitionFlipX.create(1,  self.getMainMenuScene()) );
        };

        return self;

    };
    
    var game = GameCreator();
    
    __jsc__.garbageCollect();

    // LOADING PLAY SCENE UNTILL CCBREADER IS FIXED
    
    director.runWithScene(game.getPlayScene());
    
} catch(e) {log(e);}

