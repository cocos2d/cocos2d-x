/**
 * @enum {number}
 */
var GAME_STATES = {
	RUNNING:      0,
	PAUSED:       1,
	REMOVING_ROW: 2,
	OVER:         3
};

/**
 * returns a simple hash from the point coords.
 * Assumes coords are never greater than 0xff (which should be just
 * fine for our game)
 * @return {number}
 */
var hashFromCoord = function (point) {
	return (0xffff & ((point.x << 8) | point.y));
};

/**
 * @type {Object}
 */
var Game = {};

/**
 * @const
 * @type {number}
 */
Game.TILE_SIZE = 24;

/**
 * @const
 * @type {number}
 */
Game.COLS = 13;

/**
 * @const
 * @type {number}
 */
Game.ROWS = 20;

/**
 * The main game scene
 * @type {?cocos2d.Scene}
 */
Game.scene = null;

/**
 * The current game state
 * @type {number}
 */
Game.state = GAME_STATES.RUNNING;

/**
 * The current speed of the game
 */
Game.speed = 200;

/**
 * Internal time accumulator
 * @type {number}
 * @ignore
 */
Game.__timeAccum = 0.0;

/**
 * @type {?Block}
 */
Game.currentBlock = null;

/**
 * The matrix for the game
 * @type {?Array.<number>}
 */
Game.matrix = null;

/**
 * The batch node
 * @type {?cocos2d.SpriteBatchNode}
 */
Game.batchNode = null;

/**
 * adds a new random block at the top of the screen
 */
Game.addNewBlock = function (scene) {
	Game.currentBlock = Block.random();
	Game.currentBlock.setPosition(5, Game.ROWS - 1);
	Game.currentBlock.addToScene(scene);
};

/**
 * just debugs the internal matrix
 */
Game.debugMatrix = function () {
	for (var j=Game.ROWS - 1; j >= 0; j--) {
		var arr = [];
		for (var i=0; i < Game.COLS; i++) {
			if (this.matrix[j*Game.COLS + i] > 0) {
				arr.push(1);
			} else {
				arr.push(0);
			}
		}
		debug.log("" + arr.join(" "));
	}
};

/**
 * Will copy a block to the game matrix and add the needed
 * sprites to fill in the colors
 * @param {Block} block
 */
Game.copyToMatrix = function (block) {
	var cols = block.cols;
	for (var j=0; j < cols; j++) {
		for (var i=0; i < cols; i++) {
			if (block.matrix[j * cols + i] > 0) {
				var pos = new cocos2d.Point(block.position.x + i, block.position.y + (cols - j) - 1);
				// debug.log("creating block for matrix in " + pos.x + "," + pos.y);
				this.matrix[pos.y * Game.COLS + pos.x] = 1;
				var sprite = new cocos2d.Sprite(COLOR_NAMES[block.color], 1);
				sprite.setTag(hashFromCoord(pos));
				sprite.setAnchorPoint(new cocos2d.Point(0, 0));
				sprite.setPosition(new cocos2d.Point(pos.x * Game.TILE_SIZE, pos.y * Game.TILE_SIZE));
				this.batchNode.addChild(sprite);
			}
		}
	}
	// this.debugMatrix();
};

/**
 * will check the matrix for full lines, and if so, then remove those lines
 */
Game.checkLines = function () {
	for (var j=0; j < Game.ROWS; j++) {
		var full = true;
		for (var i=0; i < Game.COLS; i++) {
			var hasBlock = false;
			if (this.matrix[j * Game.COLS + i] > 0) {
				hasBlock = true;
				if (j == Game.ROWS - 1) {
					Game.gameOver();
					return;
				}
			}
			full = full && hasBlock;
		}
		if (full) {
			// destroy row j and check the same row
			Game.destroyRow(j--);
		}
	}
};

/**
 * destroy a row
 * @param {number} row
 */
Game.destroyRow = function (row) {
	cocos2d.AudioManager.playEffect("check_in.caf");
	Game.state = GAME_STATES.REMOVING_ROW;
	var i;
	for (i=0; i < Game.COLS; i++) {
		var point = new cocos2d.Point(i, row);
		this.batchNode.removeChildByTag(hashFromCoord(point));
		// reset the matrix as well
		Game.matrix[row * Game.COLS + i] = 0;
	}
	// now move all elements from the row after to the next one
	for (var j=row+1; j < Game.ROWS; j++) {
		for (i=0; i < Game.COLS; i++) {
			if (Game.matrix[j * Game.COLS + i] > 0) {
				var hash = hashFromCoord(new cocos2d.Point(i, j));
				var sprite = this.batchNode.getChildByTag(hash);
				sprite.setTag(hashFromCoord(new cocos2d.Point(i, j-1)));
				sprite.setPosition(new cocos2d.Point(i * Game.TILE_SIZE, (j-1) * Game.TILE_SIZE));
				// and update matrix
				Game.matrix[    j * Game.COLS + i] = 0;
				Game.matrix[(j-1) * Game.COLS + i] = 1;
			} else {
				// just copy the blank space
				Game.matrix[(j-1) * Game.COLS + i] = 0;
			}
		}
	}
	Game.state = GAME_STATES.RUNNING;
};

/**
 * should display the game over function
 */
Game.gameOver = function () {
	Game.state = GAME_STATES.OVER;
	Game.cleanup();
	cocos2d.AudioManager.stopBackgroundMusic();
	debug.log("game over!");
	cocos2d.Director.popScene();
};

/**
 * clean up the game scene and other things
 */
Game.cleanup = function () {
	Game.scene.unregisterAsTouchHandler();
	cocos2d.Scheduler.unschedule(Game.__updateId);
};

/**
 * scroll the block one line below, if not possible, then
 * move the contents of the block to the matrix
 */
Game.tick = function () {
	// debug.log("tick");
	if (Game.currentBlock && Game.state == GAME_STATES.RUNNING) {
		if (Game.currentBlock.canMoveDown(Game.matrix)) {
			// debug.log("  will move block down");
			Game.currentBlock.moveDown();
		} else {
			// debug.log("  need to copy block to matrix");
			// debug.log("  copying block from " + Game.currentBlock.position.x + "," + Game.currentBlock.position.y);
			Game.copyToMatrix(Game.currentBlock);
			Game.currentBlock.removeFromScene(Game.scene);
			Game.addNewBlock(Game.scene);
		}
		// check for full lines
		Game.checkLines();
	}
};

/**
 * start a new game
 */
Game.start = function () {
	// load tile frames
	cocos2d.SpriteFrameCache.addSpriteFramesWithFile("tiles.plist");
	
	Game.matrix = new Array(Game.COLS * Game.ROWS);
	Game.batchNode = new cocos2d.SpriteBatchNode("tiles.png");
	Game.batchNode.setPosition(new cocos2d.Point(0, 0));
	Game.batchNode.setAnchorPoint(new cocos2d.Point(0, 0));

	// create the scene
	var scene = new cocos2d.Scene();
	scene.setPosition(new cocos2d.Point(4, 0));

	var background = new cocos2d.Sprite("background.png");
	background.setPosition(new cocos2d.Point(-4, 0));
	scene.addChild(background);

	scene.addChild(Game.batchNode);

	Game.state = GAME_STATES.RUNNING;
	Game.addNewBlock(scene);

	// schedule every frame
	Game.__updateId = cocos2d.Scheduler.schedule(function (delta) {
		Game.__timeAccum += delta;
		if (Game.__timeAccum >= Game.speed) {
			Game.tick();
			Game.__timeAccum = 0.0;
		}
	}, 0);

	scene.registerAsTouchHandler();
	scene.touchesBegan = function (points) {
		this.initialPoint = points[0];
		this.movedBlock = false;
	};

	scene.touchesMoved = function (points) {
		if (Game.currentBlock) {
			var distx = points[0].x - this.initialPoint.x;
			var disty = points[0].y - this.initialPoint.y;
			if (Math.abs(distx) > Game.TILE_SIZE) {
				Game.currentBlock.moveHorizontally(distx);
				this.initialPoint = points[0];
				Game.movedBlock = true;
			}
			// do not use the drag down/up for now
			// but do not allow to rotate the block using that
			if (Math.abs(disty) > Game.TILE_SIZE) {
				Game.movedBlock = true;
			}
		}
	};

	scene.touchesEnded = function (points) {
		if (Game.currentBlock && !Game.movedBlock) {
			Game.currentBlock.rotate();
		}
		Game.movedBlock = false;
	};

	Game.scene = scene;
	// play the music (not at full volume, and loop)
	cocos2d.AudioManager.playBackgroundMusic("music.mp3", true);
	cocos2d.AudioManager.setBackgroundMusicVolume(0.2);

	// run the game scene with a transition
	var transitionScene = new cocos2d.TransitionTurnOffTiles(1.0, Game.scene);
	cocos2d.Director.pushScene(transitionScene);
};
