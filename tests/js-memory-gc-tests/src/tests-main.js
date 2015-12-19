// Custom Sprite
var MySprite = cc.Sprite.extend({
        ctor: function (path) {
                this._super(path);
        },
        something: function (x, y) {
                this.setPosition(x,y);
        }
});

//
// Scene Test 1
//
function runScene1(sender) {

    cc.sys.garbageCollect();

    var scene = new cc.Scene();

    for (i = 0; i < 5; i++) {
        var sprite = new MySprite("res/Images/grossini_dance_01.png");
        sprite.something(50 + 50*i,200);
        scene.addChild(sprite);
    }

    // menu
    var button = new cc.MenuItemFont("Go to Scene 3", runScene2);
    button.fontSize = 20;
    button.fontName = "Arial";
    var menu = new cc.Menu();
    menu.addChild(button);
    menu.setPosition(300,20);
    scene.addChild(menu);

    cc.director.replaceScene(scene);
}

//
// Scene Test 2
//
function runScene2(sender) {

    cc.sys.garbageCollect();

    var scene = new cc.Scene();

    for (i = 0; i < 5; i++) {
        var sprite = new cc.Sprite("res/Images/grossini_dance_08.png");
        sprite.setPosition(50 + 50*i,200);
        scene.addChild(sprite);
    }

    // menu
    var button = new cc.MenuItemFont("Go to Scene 2", runScene1);
    button.fontSize = 20;
    button.fontName = "Arial";
    var menu = new cc.Menu();
    menu.addChild(button);
    menu.setPosition(300,20);
    scene.addChild(menu);

    cc.director.replaceScene(scene);
}

//
// Entry point
//
function runMain() {
    var scene = new cc.Scene();

    // menu
    var button = new cc.MenuItemFont("Start Test", runScene1);
    button.fontSize = 20;
    button.fontName = "Arial";
    var menu = new cc.Menu();
    menu.addChild(button);
    menu.setPosition(300,300);

    scene.addChild(menu);
    cc.director.runScene(scene);
}
