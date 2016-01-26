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

    return scene;
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

    return scene;
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
    
    var touchListener = null;
    var mouseListener = null;

    // 'browser' can use touches or mouse.
    // The benefit of using 'touches' in a browser, is that it works both with mouse events or touches events
    if ('touches' in cc.sys.capabilities) {
        touchListener = cc.eventManager.addListener({
                event: cc.EventListener.TOUCH_ALL_AT_ONCE,
                onTouchesMoved: function (touches, event) {
                    var delta = touches[0].getDelta();
                    cc.log("onTouchesMoved:" + delta);
                    return true;
                }
        },
        10);
    } else if ('mouse' in cc.sys.capabilities) {
        mouseListener = cc.eventManager.addListener({
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

    this.label.onExit = function () {
        if (touchListener) {
            cc.eventManager.removeListener(touchListener);
        }
        if (mouseListener) {
            cc.eventManager.removeListener(mouseListener);
        }
        cc.LabelTTF.prototype.onExit.call(this);
    };

    return scene;
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

    return scene;
}


function runScene5(sender) {
    var scene = new cc.Scene();
    
    var TREE_TAG = 888;
    var tree = createTree(5, cc.rect(0, 0, cc.winSize.width, cc.winSize.height));
    scene.addChild(tree, 0, TREE_TAG);

    var fontDef = new cc.FontDefinition();
    fontDef.fontName = "Arial";
    fontDef.fontSize = 20;
    fontDef.boundingWidth = cc.winSize.width * 0.8;
    var label = new cc.LabelTTF("Click 'Replace Tree' to create a new tree and the current tree should be garbage collected", fontDef);
    label.setPosition(cc.winSize.width / 2, cc.winSize.height / 2);
    scene.addChild(label, 10);

    // menu
    var menu = new cc.Menu();
    var button = new cc.MenuItemFont("Replace Tree", function () {
        var levels = 4 + Math.floor( Math.random() * 4 );
        var newTree = createTree(levels, cc.rect(0, 0, cc.winSize.width, cc.winSize.height));
        label.string = "Now click 'Run GC', you should see a list of finalize message, the number should match the number of old tree nodes";
        cc.log("Now click 'Run GC', you should see a list of finalize message, the number should match the number of old tree nodes");
        var oldTree = scene.getChildByTag(TREE_TAG);
        oldTree.removeFromParent(true);
        scene.addChild(newTree, 0, TREE_TAG);
    });
    button.fontSize = 20;
    button.fontName = "Arial";
    menu.addChild(button);
    menu.setPosition(cc.winSize.width / 4, cc.winSize.height - 40);
    scene.addChild(menu);

    return scene;
}

function runScene6 () {
    var scene = new cc.Scene();

    var callback = function () {
        cc.log('A callback which do nothing');
    };

    var sprite = new cc.Sprite("res/Images/grossini_dance_01.png");
    sprite.x = cc.winSize.width/2;
    sprite.y = cc.winSize.height/2;
    sprite.action = cc.callFunc(callback, sprite);

    var SPRITE_TAG = 999;
    scene.addChild(sprite, 0, SPRITE_TAG);

    var fontDef = new cc.FontDefinition();
    fontDef.fontName = "Arial";
    fontDef.fontSize = 20;
    fontDef.boundingWidth = cc.winSize.width * 0.8;
    var label = new cc.LabelTTF("Click screen to remove sprite and it should be garbage collected", fontDef);
    label.setPosition(cc.winSize.width / 2, cc.winSize.height / 2 + 100);
    scene.addChild(label);

    var touchListener = cc.eventManager.addListener({
        event: cc.EventListener.TOUCH_ALL_AT_ONCE,
        onTouchesEnded: function (touches, event) {
            cc.sys.garbageCollect();
            cc.sys.garbageCollect();
            cc.log('You should see immidiately two release messages in Console (Sprite and Action)');
            label.setString('You should see immidiately two release messages in Console (Sprite and Action)');
            var target = event.getCurrentTarget();
            target.removeChildByTag(SPRITE_TAG);
            cc.sys.garbageCollect();
            cc.eventManager.removeListener(touchListener);
        }
    }, scene);

    return scene;
}

function runScene7 () {
    var scene = new cc.Scene();

    var fontDef = new cc.FontDefinition();
    fontDef.fontName = "Arial";
    fontDef.fontSize = 20;
    fontDef.boundingWidth = cc.winSize.width * 0.8;
    var label = new cc.LabelTTF("Click screen to remove button and it should be garbage collected", fontDef);
    label.setPosition(cc.winSize.width / 2, cc.winSize.height / 2 + 100);
    scene.addChild(label);

    var menu = new cc.Menu();
    var button = new cc.MenuItemFont("Remove myself", function () {
        cc.sys.garbageCollect();
        cc.sys.garbageCollect();
        label.string = "Now click 'Run GC', you should see finalize message of button";
        cc.log("Now click 'Run GC', you should see finalize message of button");
        menu.removeAllChildren(true);
    }, menu);
    menu.addChild(button);
    menu.setPosition(cc.winSize.width / 2, cc.winSize.height / 2);
    scene.addChild(menu);

    return scene;
}

function runScene8 () {
    var scene = new cc.Scene();

    var fontDef = new cc.FontDefinition();
    fontDef.fontName = "Arial";
    fontDef.fontSize = 20;
    fontDef.boundingWidth = cc.winSize.width * 0.8;
    var label = new cc.LabelTTF("Click screen to remove button and it should be garbage collected", fontDef);
    label.setPosition(cc.winSize.width / 2, cc.winSize.height / 2 + 100);
    scene.addChild(label);

    var scrollView = new cc.ScrollView();
    var obj = {
        scrollView: scrollView
    };
    scrollView.setDelegate(obj);

    var menu = new cc.Menu();
    menu.scrollView = scrollView;
    var button = new cc.MenuItemFont("Remove ScrollView (invisible)", function () {
        cc.sys.garbageCollect();
        label.string = "Now you should see finalize message of ScrollView";
        cc.log("Now you should see finalize message of ScrollView");
        delete menu.scrollView;
        cc.sys.garbageCollect();
    }, menu);
    menu.addChild(button);
    menu.setPosition(cc.winSize.width / 2, cc.winSize.height / 2);
    scene.addChild(menu);

    return scene;
}

var tests = [
    runScene1,
    runScene2,
    runScene3,
    runScene4,
    runScene5,
    runScene6,
    runScene7,
    runScene8
];

var replaceScene = (function () {
    var curr = tests.length-1;

    return function () {
        if (curr < tests.length-1) {
            curr++;
        }
        else {
            curr = 0;
        }

        var scene = tests[curr]();

        // menu
        var menu = new cc.Menu();
        var button = new cc.MenuItemFont("Next Scene", replaceScene);
        button.fontSize = 20;
        button.fontName = "Arial";
        menu.addChild(button);
        button = new cc.MenuItemFont("Run GC", cc.sys.garbageCollect);
        button.fontSize = 20;
        button.fontName = "Arial";
        button.x = cc.winSize.width/4;
        button.y = cc.winSize.height - 60;
        menu.addChild(button);
        menu.setPosition(cc.winSize.width/2, 20);
        scene.addChild(menu);

        cc.director.replaceScene(scene);

        cc.sys.garbageCollect();
    };
})();

//
// Main Entry point
//
function runMain() {

    var scene = new cc.Scene();

    // menu
    var button = new cc.MenuItemFont("Start Test", replaceScene);
    button.fontSize = 20;
    button.fontName = "Arial";
    var menu = new cc.Menu();
    menu.addChild(button);
    menu.setPosition(300,300);

    scene.addChild(menu);
    cc.director.runScene(scene);
}
