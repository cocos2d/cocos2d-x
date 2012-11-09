
try {

    cc.p = cc.p || function( x, y ) {
        return {x:x, y:y};
    };
    
    cc.c4b = cc.c4 || function (r, g, b, o) {
        return {r: r, g: g, b: b, a: o};
    };
  
    
    cc.c3 = cc.c3 || function (r, g, b) {
        return {r: r, g: g, b: b};
    };
    cc.BLACK = cc.c3(0,0,0);

    // MenuItemToggle
    cc.MenuItemToggle.create = function (/* var args */) {
        
        var n = arguments.length;
        
        if (typeof arguments[n - 1] === 'function') {
            var args = Array.prototype.slice.call(arguments);
            var func = args.pop();
            var obj = args.pop();
            
            // create it with arguments,
            var item = cc.MenuItemToggle._create.apply(this, args);
            
            // then set the callback
            item.setCallback(obj, func);
            return item;
        } else {
            return cc.MenuItemToggle._create.apply(this, arguments);
        }
    };
    
    
    director = cc.Director.getInstance();
    winSize = director.getWinSize();
    centerPos = cc.p( winSize.width/2, winSize.height/2 );

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
            
            var back = cc.MenuItemFont.create("Back", this.callbacks, this.callbacks.onBack );
            back.setColor( cc.BLACK );
            
            var menu = cc.Menu.create( back );
            layer.addChild( menu );
            menu.alignItemsVertically();
            menu.setPosition( cc.p( winSize.width - 50, 50) );
            
            scene.addChild(layer);
            
            return scene;
        };
        
        self.getMainMenuScene = function() {
            var l = cc.Layer.create();
            var scene = cc.Scene.create();
            
            var node = cc.Reader.load("MainMenu.ccbi", this, winSize);
            l.addChild(node);
            
            scene.addChild(l);
            
            return scene;
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
            };
            
            toggle.setCallback( this, this.onMusicToggle);
            
            var back = cc.MenuItemFont.create("Back", this.callbacks, this.callbacks.onBack );
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
            var about = cc.Reader.load("About.ccbi", this);
            l.addChild( about )
            
            var back = cc.MenuItemFont.create("Back", this.callbacks, this.callbacks.onBack );
            back.setColor( cc.BLACK );
            var menu = cc.Menu.create( back );
            l.addChild( menu );
            menu.alignItemsVertically();
            menu.setPosition( cc.p( winSize.width - 50, 50) );
            
            scene.addChild( l );
            
            return scene;
        };
        
        
        // CCBuilder Selectors
        
        self.onPlay = function() {
            director.replaceScene( cc.TransitionFade.create(1, this.getPlayScene()) );
        }
        
        self.onAbout = function() {
            director.replaceScene( cc.TransitionZoomFlipY.create(1, this.getAboutScene()) );
        };
    
        self.onOptions = function() {
            director.replaceScene( cc.TransitionZoomFlipY.create(1, this.getOptionsScene()) );
        };
        
        
        // Manual Callbacks
        
        self.callbacks.onBack  = function( sender) {
            director.replaceScene( cc.TransitionFlipX.create(1,  self.getMainMenuScene()) );
        };
        
        return self;

    };
    
    var game = GameCreator();
    
    __jsc__.garbageCollect();
    
    director.runWithScene(game.getMainMenuScene());
    
} catch(e) {log(e);}

