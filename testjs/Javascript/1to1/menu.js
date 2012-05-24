// prepare the menu and other things

cocos.Point.create = function (x, y) {
	var pt = new cocos.Point();
	pt.x = x;
	pt.y = y;
	return pt;
};

var pointZero = cocos.Point.create(0, 0);

var director = cocos.Director.sharedDirector;
var winSize = director.winSize();

var hudMenu = new cocos.Menu();

(function () {
	// we add the items as members of menu to avoid GC
	// ** otherwise the GC will try to remove the itemN object **
	hudMenu.item1 = new cocos.MenuItemImage();
	item1.initWithNormalImage("b1.png", "b2.png");
	hudMenu.item2 = new cocos.MenuItemImage();
	item2.initWithNormalImage("r1.png", "r2.png");
	hudMenu.item3 = new cocos.MenuItemImage();
	item3.initWithNormalImage("f1.png", "f2.png");

	hudMenu.addChild(menu.item1);
	hudMenu.addChild(menu.item2);
	hudMenu.addChild(menu.item3);
	hudMenu.position = pointZero;

	hudMenu.item1.position = cocos.Point.create(winSize.width / 2 - 100, 30);
	hudMenu.item2.position = cocos.Point.create(winSize.width / 2      , 30);
	hudMenu.item3.position = cocos.Point.create(winSize.width / 2 + 100, 30);
})();
