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

    var scene = new cc.Scene();

    for (i = 0; i < 5; i++) {
        var sprite = new MySprite("res/Images/grossini_dance_01.png");
        sprite.something(50 + 50*i,200);
        scene.addChild(sprite);
    }

    // menu
    var button = new cc.MenuItemFont("Go to Scene 2", runScene2);
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

    var scene = new cc.Scene();

    for (i = 0; i < 5; i++) {
        var sprite = new cc.Sprite("res/Images/grossini_dance_08.png");
        sprite.setPosition(50 + 50*i,200);
        scene.addChild(sprite);
    }

    // menu
    var button = new cc.MenuItemFont("Go to Scene 3", runScene3);
    button.fontSize = 20;
    button.fontName = "Arial";
    var menu = new cc.Menu();
    menu.addChild(button);
    menu.setPosition(300,20);
    scene.addChild(menu);

    cc.director.replaceScene(scene);
}

//
// Scene Test 3
//
function runScene3(sender) {

    var scene = new cc.Scene();

    var fontDef = new cc.FontDefinition();
    fontDef.fontName = "Arial";
    fontDef.fontSize = 32;
    this.label = new cc.LabelTTF("See console!", fontDef);
    this.label.setPosition(300,300);
    scene.addChild(this.label);

    // menu
    var button = new cc.MenuItemFont("Go to Scene 4", runScene4);
    button.fontSize = 20;
    button.fontName = "Arial";
    var menu = new cc.Menu();
    menu.addChild(button);
    menu.setPosition(300,20);
    scene.addChild(menu);

    // 'browser' can use touches or mouse.
    // The benefit of using 'touches' in a browser, is that it works both with mouse events or touches events
    if ('touches' in cc.sys.capabilities) {
        cc.eventManager.addListener({
                event: cc.EventListener.TOUCH_ALL_AT_ONCE,
                    onTouchesMoved: function (touches, event) {
                        var delta = touches[0].getDelta();
                        cc.log("onTouchesMoved:" + delta);
                        return true;
                    }
        },
        10);
    } else if ('mouse' in cc.sys.capabilities) {
        cc.eventManager.addListener({
                event: cc.EventListener.MOUSE,
                    onMouseMove: function (event) {
                        if(event.getButton() == cc.EventMouse.BUTTON_LEFT)
                            cc.log("onMouseMove" + event.getDelta());
                    },
                    onMouseScroll: function (event) {
                        var delta = cc.sys.isNative ? event.getScrollY() * 6 : -event.getScrollY();
                        cc.log("onMouseScroll:" + delta);
                        return true;
                    }
        },
        10);
    }

    cc.director.replaceScene(scene);
}


function runScene4(sender) {

        var scene = new cc.Scene();

        var actionTo = cc.jumpTo(2, cc.p(300, 300), 50, 4);
        var actionBy = cc.jumpBy(2, cc.p(300, 0), 50, 4);
        var actionUp = cc.jumpBy(2, cc.p(0, 0), 80, 4);
        var actionByBack = actionBy.reverse();

        var delay = cc.delayTime(0.25);

        var sprite1 = new cc.Sprite("res/Images/grossini_dance_08.png");
        sprite1.setPosition(10,10);
        var sprite2 = new cc.Sprite("res/Images/grossini_dance_01.png");
        sprite2.setPosition(200,10);
        var sprite3 = new cc.Sprite("res/Images/grossini_dance_04.png");
        sprite3.setPosition(400,10);

        scene.addChild(sprite1);
        scene.addChild(sprite2);
        scene.addChild(sprite3);

        sprite1.runAction(actionTo);
        sprite2.runAction(cc.sequence(actionBy, delay, actionByBack));

        var action = cc.sequence(actionUp, delay.clone()).repeatForever();
        sprite3.runAction(action);


        // menu
        var button = new cc.MenuItemFont("Go to Scene 1", runScene1);
        button.fontSize = 20;
        button.fontName = "Arial";
        var menu = new cc.Menu();
        menu.addChild(button);
        menu.setPosition(300,20);
        scene.addChild(menu);

        cc.director.replaceScene(scene);
}

//
// Main Entry point
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
