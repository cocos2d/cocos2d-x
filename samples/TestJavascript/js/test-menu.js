//
// http://www.cocos2d-iphone.org
// http://www.cocos2d-html5.org
// http://www.cocos2d-x.org
//
// Javascript + cocos2d actions tests
//

require("js/helper.js");

director = cc.Director.getInstance();
winSize = director.getWinSize();
centerPos = cc.p( winSize.width/2, winSize.height/2 );

var scenes = []
var currentScene = 0;

var nextScene = function () {
	currentScene = currentScene + 1;
	if( currentScene >= scenes.length )
		currentScene = 0;

	withTransition = true;
	loadScene(currentScene);
};

var previousScene = function () {
	currentScene = currentScene -1;
	if( currentScene < 0 )
		currentScene = scenes.length -1;

	withTransition = true;
	loadScene(currentScene);
};

var restartScene = function () {
	loadScene( currentScene );
};

var loadScene = function (sceneIdx)
{
	winSize = director.getWinSize();
	centerPos = cc.p( winSize.width/2, winSize.height/2 );

	var scene = new cc.Scene();
	scene.init();
	var layer = new scenes[ sceneIdx ]();

	scene.addChild( layer );

//	scene.walkSceneGraph(0);

	director.replaceScene( scene );
//    __jsc__.garbageCollect();
}



//
// Base Layer
//

var BaseLayer = cc.LayerGradient.extend({

    ctor:function () {
                                
        var parent = new cc.LayerGradient();
        __associateObjWithNative(this, parent);
        this.init(cc.c4b(0, 0, 0, 255), cc.c4b(0, 128, 255, 255));
    },

    title:function () {
        return "No Title";
    },

    subtitle:function () {
        return "";
    },

    code:function () {
        return "";
    },

    restartCallback:function (sender) {
        restartScene();
    },

    nextCallback:function (sender) {
        nextScene();
    },

    backCallback:function (sender) {
       previousScene();
    },

    onEnter:function () {
        // DO NOT CALL this._super()
//        this._super();

        // add title and subtitle
        var label = cc.LabelTTF.create(this.title(), "Arial", 28);
        this.addChild(label, 1);
        label.setPosition( cc.p(winSize.width / 2, winSize.height - 40));

        var strSubtitle = this.subtitle();
        if (strSubtitle != "") {
            var l = cc.LabelTTF.create(strSubtitle, "Thonburi", 16);
            this.addChild(l, 1);
            l.setPosition( cc.p(winSize.width / 2, winSize.height - 70));
        }

        var strCode = this.code();
        if( strCode !="" ) {
            var label = cc.LabelTTF.create(strCode, 'CourierNewPSMT', 16);
            label.setPosition( cc.p( winSize.width/2, winSize.height-120) );
            this.addChild( label,10 );

            var labelbg = cc.LabelTTF.create(strCode, 'CourierNewPSMT', 16);
            labelbg.setColor( cc.c3b(10,10,255) );
            labelbg.setPosition( cc.p( winSize.width/2 +1, winSize.height-120 -1) );
            this.addChild( labelbg,9);
        }

        // Menu
        var item1 = cc.MenuItemImage.create("b1.png", "b2.png", this, this.backCallback);
        var item2 = cc.MenuItemImage.create("r1.png", "r2.png", this, this.restartCallback);
        var item3 = cc.MenuItemImage.create("f1.png", "f2.png", this, this.nextCallback);
        var item4 = cc.MenuItemFont.create("back", this, function() { require("js/main.js"); } );
        item4.setFontSize( 22 );

        var menu = cc.Menu.create(item1, item2, item3, item4 );

        menu.setPosition( cc.p(0,0) );
        item1.setPosition( cc.p(winSize.width / 2 - 100, 30));
        item2.setPosition( cc.p(winSize.width / 2, 30));
        item3.setPosition( cc.p(winSize.width / 2 + 100, 30));
        item4.setPosition( cc.p(winSize.width - 60, winSize.height - 30 ) );

        this.addChild(menu, 1);


        // back menu
    }
});

//------------------------------------------------------------------
//
// MenuItemFontTest
//
//------------------------------------------------------------------
var MenuItemFontTest = BaseLayer.extend({
    onEnter:function () {
        this._super();

        var item1 = cc.MenuItemFont.create("Item 1. Should be RED");
        var item2 = cc.MenuItemFont.create("This item is bigger", this, this.item_cb);
        var item3 = cc.MenuItemFont.create("This item should be disabled", this, this.item_cb);

        // callback function can be modified in runtime
        item1.setCallback( this, this.item_cb );

        // font color can be changed in runtime
        item1.setColor( cc.c3b(255,0,0) );

        // font size can be changed in runtime (it is faster to do it before creating the item)
        item2.setFontSize( 48 );

        // font name can be changed in runtime (it is faster to do it before creating the item)
        item3.setFontName( "Courier New");

        // item could be enabled / disabled in runtime
        item3.setEnabled( false );

        var menu = cc.Menu.create( item1, item2, item3 );
        menu.alignItemsVertically();

        menu.setPosition( cc.p( winSize.width/2, winSize.height/2) );

        this.addChild( menu );
    },

    title:function () {
        return "Menu Item Font";
    },
    subtitle:function () {
        return "3 items. 3rd should be disabled. Smaller font";
    },
    code:function () {
        return "item = cc.MenuItemFont.create('Press me', this, this.callback)";
    },

    // callback
    item_cb:function(sender) {
        cc.log("Item " + sender + " pressed");
    },


});

//------------------------------------------------------------------
//
// MenuItemImage
//
//------------------------------------------------------------------
var MenuItemImageTest = BaseLayer.extend({

    _vertically : true,

    _menu : null,

    onEnter:function () {
        this._super();
  
        var item1 = cc.MenuItemImage.create("btn-play-normal.png", "btn-play-selected.png" );
        var item2 = cc.MenuItemImage.create("btn-highscores-normal.png", "btn-highscores-selected.png", this, this.item_cb  );
        var item3 = cc.MenuItemImage.create("btn-about-normal.png", "btn-about-selected.png", this, this.item_cb  );
        
        // callback function can be modified in runtime
        item1.setCallback( this, this.item_cb );

        // item could be enabled / disabled in runtime
        item3.setEnabled( false );

        this._menu = cc.Menu.create( item1, item2, item3 );
        this._menu.alignItemsVertically();

        this._menu.setPosition( cc.p( winSize.width/2, winSize.height/2) );

        this.addChild( this._menu );
    },


    title:function () {
        return "Menu Item Image";
    },
    subtitle:function () {
        return "3 items. 3rd should be disabled.";
    },
    code:function () {
        return "item = cc.MenuItemImage.create('normal.png', 'selected.png' , 'disabled.png', this, this.cb )";
    },

    // callback
    item_cb:function(sender) {
        cc.log("Item " + sender + " pressed");
        if( this._vertically )
            this._menu.alignItemsHorizontally();
        else
            this._menu.alignItemsVertically();

        this._vertically = ! this._vertically;

    },

});

//------------------------------------------------------------------
//
// MenuItemSpriteTest
//
//------------------------------------------------------------------
var MenuItemSpriteTest = BaseLayer.extend({

    _vertically : true,
    _menu : null,

    onEnter:function () {
        this._super();
   
        // Sprites can't be reused since they are children of MenuItem
        // If you want to reuse them, use "MenuItemImage" instead
        var sprite1_1 = cc.Sprite.create("menuitemsprite.png", cc.rect(0, 23*2, 115, 23) );
        var sprite2_1 = cc.Sprite.create("menuitemsprite.png", cc.rect(0, 23*1, 115, 23) );
        var sprite1_2 = cc.Sprite.create("menuitemsprite.png", cc.rect(0, 23*2, 115, 23) );
        var sprite2_2 = cc.Sprite.create("menuitemsprite.png", cc.rect(0, 23*1, 115, 23) );
        var sprite3_2 = cc.Sprite.create("menuitemsprite.png", cc.rect(0, 23*0, 115, 23) );
        var sprite1_3 = cc.Sprite.create("menuitemsprite.png", cc.rect(0, 23*2, 115, 23) );
        var sprite2_3 = cc.Sprite.create("menuitemsprite.png", cc.rect(0, 23*1, 115, 23) );
        var sprite3_3 = cc.Sprite.create("menuitemsprite.png", cc.rect(0, 23*0, 115, 23) );

        var item1 = cc.MenuItemSprite.create(sprite1_1, sprite2_1);
        var item2 = cc.MenuItemSprite.create(sprite1_2, sprite2_2, sprite3_2, this, this.item_cb);
        var item3 = cc.MenuItemSprite.create(sprite1_3, sprite2_3, sprite3_3, this, this.item_cb);

        // callback function can be modified in runtime
        item1.setCallback( this, this.item_cb );

        // item could be enabled / disabled in runtime
        item3.setEnabled( false );

        this._menu = cc.Menu.create( item1, item2, item3 );
        this._menu.alignItemsVertically();

        this._menu.setPosition( cc.p( winSize.width/2, winSize.height/2) );

        this.addChild( this._menu );
    },

    title:function () {
        return "Menu Item Sprite";
    },
    subtitle:function () {
        return "3 items. 3rd should be disabled.";
    },
    code:function () {
        return "item = cc.MenuItemSprite.create(spr_normal, spr_selected, spr_disabled, this, this.cb )";
    },

    // callback
    item_cb:function(sender) {
        cc.log("Item " + sender + " pressed");
        if( this._vertically )
            this._menu.alignItemsHorizontally();
        else
            this._menu.alignItemsVertically();

        this._vertically = ! this._vertically;

    },

});


//------------------------------------------------------------------
//
// MenuItemLabelTest
//
//------------------------------------------------------------------
var MenuItemLabelTest = BaseLayer.extend({

    _vertically : true,
    _menu : null,

    onEnter:function () {
        this._super();
   
        var label1 = cc.LabelTTF.create("This is a LabelTTF item", "Arial", 24 );
        var label2 = cc.LabelBMFont.create("And this is a LabelBMFont item", "futura-48.fnt" );
        var label3 = cc.LabelTTF.create("Disabled Item", "Arial", 24 );

        var item1 = cc.MenuItemLabel.create(label1);
        var item2 = cc.MenuItemLabel.create(label2, this, this.item_cb);
        var item3 = cc.MenuItemLabel.create(label3, this, this.item_cb);

        // callback function can be modified in runtime
        item1.setCallback( this, this.item_cb );

        // item could be enabled / disabled in runtime
        item3.setEnabled( false );

        this._menu = cc.Menu.create( item1, item2, item3 );
        this._menu.alignItemsVertically();

        this._menu.setPosition( cc.p( winSize.width/2, winSize.height/2) );

        this.addChild( this._menu );
    },

    title:function () {
        return "Menu Item Label";
    },
    subtitle:function () {
        return "3 items. 3rd should be disabled.";
    },
    code:function () {
        return "item = cc.MenuItemLabel.create(label, this, this.cb )";
    },

    // callback
    item_cb:function(sender) {
        cc.log("Item " + sender + " pressed");
        if( this._vertically )
            this._menu.alignItemsHorizontally();
        else
            this._menu.alignItemsVertically();

        this._vertically = ! this._vertically;

    },

});

//------------------------------------------------------------------
//
// MenuItemToggleTest
//
//------------------------------------------------------------------
var MenuItemToggleTest = BaseLayer.extend({

    _vertically : true,
    _menu : null,

    onEnter:function () {
        this._super();
   
        var label1 = cc.LabelBMFont.create("Volume Off", "futura-48.fnt" );
        var item1 = cc.MenuItemLabel.create(label1);
        var label2 = cc.LabelBMFont.create("Volume On", "futura-48.fnt" );
        var item2 = cc.MenuItemLabel.create(label2);

        var itema = cc.MenuItemFont.create("Sound Off");
        var itemb = cc.MenuItemFont.create("Sound 50%");
        var itemc = cc.MenuItemFont.create("Sound 100%");

        var toggle1 = cc.MenuItemToggle.create( item1, item2 );
        var toggle2 = cc.MenuItemToggle.create( itema, itemb, itemc );

        toggle1.setCallback( this, this.item_cb);
        toggle2.setCallback( this, this.item_cb);

        this._menu = cc.Menu.create( toggle1, toggle2 );
        this._menu.alignItemsVertically();
        this._menu.setPosition( cc.p( winSize.width/2, winSize.height/2) );

        this.addChild( this._menu );
    },

    title:function () {
        return "Menu Item Toggle";
    },
    subtitle:function () {
        return "2 Toggle Items";
    },
    code:function () {
        return "item = cc.MenuItemToggle.create( item1, item2, item3 );";
    },

    // callback
    item_cb:function(sender) {
        cc.log("toggle pressed");
    },
});

//------------------------------------------------------------------
//
// MenuItemSubclass
//
//------------------------------------------------------------------

var MyMenuItemFont = cc.MenuItemFont.extend({

    ctor:function( label ) {
        var parent = new cc.MenuItemFont();
        __associateObjWithNative(this, parent);
        this.init( label, this, this.callback );
        },

    callback:function(sender) {
        cc.log("Button clicked");
    },
});

var MenuItemSubclass = BaseLayer.extend({

    _vertically : true,
    _menu : null,

    onEnter:function () {
        this._super();
   
        var item1 = new MyMenuItemFont("Item 1");
        var item2 = new MyMenuItemFont("Item 2");

        this._menu = cc.Menu.create( item1, item2 );
        this._menu.alignItemsVertically();
        this._menu.setPosition( cc.p( winSize.width/2, winSize.height/2) );

        this.addChild( this._menu );
    },

    title:function () {
        return "Menu Item Subclass";
    },
    subtitle:function () {
        return "2 items should appear";
    },
});


//
// Order of tests
//

scenes.push( MenuItemFontTest );
scenes.push( MenuItemImageTest );
scenes.push( MenuItemSpriteTest );
scenes.push( MenuItemLabelTest );
scenes.push( MenuItemToggleTest );
scenes.push( MenuItemSubclass );

//------------------------------------------------------------------
//
// Main entry point
//
//------------------------------------------------------------------
function run()
{
    var scene = cc.Scene.create();
    var layer = new scenes[currentScene]();
    scene.addChild( layer );

    var runningScene = director.getRunningScene();
    if( runningScene == null )
        director.runWithScene( scene );
    else
        director.replaceScene( cc.TransitionFade.create(0.5, scene ) );
}

run();

