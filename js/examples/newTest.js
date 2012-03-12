try {
	var sprite = new CCSprite("mapletree.png");

	var scene = new CCScene();
	scene.addChild(sprite);

	var total = 800;
	debug.log("total set positions: " + total);

	scene.schedule("update", function (delta) {
		try {
			var pt = new CCPoint(Math.random() * 320.0, Math.random() * 480.0);
			// debug.log("pt: " + pt.x + "," + pt.y);
			var sum = 0.0, i=0;
			for (i=0; i < total; i++)
			{
				// var curTime = Date.now();
				sprite.setPosition(pt);
				// var endTime = Date.now();
				// sum += (endTime - curTime) / 1000.0;
			}
			// debug.log("sum: " + i);
		} catch (e) {
			debug.log(e);
		}
	});

	CCDirector.runWithScene(scene);
	
	/*
	var sum = 0;
	debug.log("starting test");
	var pos = [100.0, 100.0];

	var __x = 0;
	for (__x = 0; __x < 20; __x++) {
	}
	debug.log(i + "\t" + (sum / __x));
	*/

} catch (e) {
	debug.log("error: " + e);
}
