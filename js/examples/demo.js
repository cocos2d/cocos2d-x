var batch = new CCSpriteBatchNode("icon_xp.png");
var total = 500;

debug.log("total sprites: " + total);

var updateLoop = function () {
	var curPos = this.getPosition();
	var speed = this.speed;
	curPos.x += speed.x;
	curPos.y += speed.y;
	if (curPos.x < 0 || curPos.x > 320) {
		speed.x *= -1;
	}
	if (curPos.y < 0 || curPos.y > 480) {
		speed.y *= -1;
	}
	this.setPosition(curPos);
};

// only used in the case 2
batch.fauxChildrenArray = [];

// case 1:
// manual update loop
for (var i=0; i < total; i++) {
	var sp = new CCSprite("icon_xp.png");
	sp.speed = new CCPoint(Math.random() * 10, Math.random() * 10);
	sp.schedule("update", updateLoop);
	batch.addChild(sp);
	// batch.fauxChildrenArray.push(sp);
}

// case 2:
// manual update but for the batch node (single update call)
/*
batch.schedule("update", function () {
	for (var i=0; i < total; i++) {
		var sprite = batch.fauxChildrenArray[i];
		var curPos = sprite.getPosition();
		var speed = sprite.speed;
		curPos.x += speed.x;
		curPos.y += speed.y;
		if (curPos.x < 0 || curPos.x > 320) {
			speed.x *= -1;
		}
		if (curPos.y < 0 || curPos.y > 480) {
			speed.y *= -1;
		}
		sprite.setPosition(curPos);
	}
});
*/

var scene = new CCScene();
scene.addChild(batch);

CCDirector.runWithScene(scene);
