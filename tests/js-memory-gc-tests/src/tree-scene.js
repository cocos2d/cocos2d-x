var createTree = (function () {

var _ORIGIN_WIDTH = 85;
var _ORIGIN_HEIGHT = 121;

var _createNode = function (x, y) {
    var node = new cc.Sprite("res/Images/grossini_dance_01.png");
    node.x = x;
    node.y = y;
    return node;
};

var _createLevel = function (upLevel, width, height, scale) {
    var level = [];
    var unitW = width / (upLevel.length * 2);
    var y = - height / 2;
    for (var i = 0; i < upLevel.length; ++i) {
        var parent = upLevel[i];
        var centerx = parent.width * scale / 2;
        var x = centerx - unitW / 2;
        var left = _createNode(x / scale, y / scale);
        x = centerx + unitW / 2;
        var right = _createNode(x / scale, y / scale);
        level.push(left);
        parent.addChild(left);
        level.push(right);
        parent.addChild(right);
    }
    return level;
};

return function (levels, zone) {
    var height = zone.height / levels;
    var scale = height * 0.9 / _ORIGIN_HEIGHT;
    if (scale > 1) scale = 1;
    var root = _createNode(zone.x + zone.width/2, zone.y + zone.height - height/2);
    root.scale = scale;
    var nodes = [root];
    for (var i = 1; i < levels; ++i) {
        nodes = _createLevel(nodes, zone.width, height, scale);
    }
    return root;
};

})();