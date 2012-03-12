/**
 * the different blocks
 * @enum {number}
 */
var TILES = {
	I: 0,
	J: 1,
	L: 2,
	O: 3,
	S: 4,
	T: 5,
	Z: 6
};

/**
 * @enum {number}
 */
var COLORS = {
	EMPTY: 0,
	CYAN: 1,
	BLUE: 2,
	ORANGE: 3,
	YELLOW: 4,
	GREEN: 5,
	MAGENTA: 6,
	RED: 7
};

/**
 * @type {Array.<string>}
 */
var COLOR_NAMES = [
	"",
	"cyan.png",
	"blue.png",
	"orange.png",
	"yellow.png",
	"green.png",
	"magenta.png",
	"red.png"
];

/**
 * @type {Array.<Object>}
 */
var TILE_SPECS = [
	{
		name: "I",
		color: COLORS.CYAN,
		cols: 4,
		grid: [
			0, 0, 0, 0,
			1, 1, 1, 1,
			0, 0, 0, 0,
			0, 0, 0, 0
		]
	},
	{
		name: "J",
		color: COLORS.BLUE,
		cols: 3,
		grid: [
			1, 0, 0,
			1, 1, 1,
			0, 0, 0
		]
	},
	{
		name: "L",
		color: COLORS.ORANGE,
		cols: 3,
		grid: [
			0, 0, 1,
			1, 1, 1,
			0, 0, 0
		]
	},
	{
		name: "O",
		color: COLORS.YELLOW,
		cols: 2,
		grid: [
			1, 1,
			1, 1
		]
	},
	{
		name: "S",
		color: COLORS.GREEN,
		cols: 3,
		grid: [
			0, 1, 1,
			1, 1, 0,
			0, 0, 0
		]
	},
	{
		name: "T",
		color: COLORS.MAGENTA,
		cols: 3,
		grid: [
			0, 1, 0,
			1, 1, 1,
			0, 0, 0
		]
	},
	{
		name: "Z",
		color: COLORS.RED,
		cols: 3,
		grid: [
			1, 1, 0,
			0, 1, 1,
			0, 0, 0
		]
	}
];

/**
 * @constructor
 * @param {cocos2d.SpriteBatchNode} batchNode
 */
var Block = function () {
	// every block is a new batch node
	this.batchNode = new cocos2d.SpriteBatchNode("tiles.png");
	this.batchNode.setAnchorPoint(new cocos2d.Point(0, 0));
	this.matrix = [];
	this.cols = 0;
	this.color = -1;
};

/**
 * @type {?Array.<cocos2d.Sprite>}
 */
Block.prototype.blocks = null;

/**
 * @type {?Array.<number>}
 */
Block.prototype.matrix = null;

/**
 * @type {?cocos2d.SpriteBatchNode}
 */
Block.prototype.batchNode = null;

/**
 * @type {number}
 */
Block.prototype.cols = 0;

/**
 * @type {number}
 */
Block.prototype.color = 0;

/**
 * @type {?cocos2d.Point}
 */
Block.prototype.position = null;

/**
 * lowest position in Y that contains a block
 * @type {number}
 */
Block.prototype.lowestY = 0;


/**
 * max position in X that contains a block
 * @type {number}
 */
Block.prototype.maxX = 0;

/**
 * min position in X that contains a block
 * @type {number}
 */
Block.prototype.minX = 0;

/**
 * sets the block matrix. It should be a square matrix
 * @param {Array.<number>} matrix
 * @param {number} cols
 * @param {number} color
 */
Block.prototype.setMatrix = function (matrix, cols, color) {
	this.cols = cols || this.cols;
	this.color = color || this.color;
	this.matrix = [].concat(matrix);

	cols = this.cols;

	this.minX = 100;
	this.maxX = 0;
	
	// go through the matrix and add as many blocks as we need
	var count = 0;
	for (var j=0; j < cols; j++) {
		for (var i=0; i < cols; i++) {
			if (this.matrix[j * cols + i] > 0) {
				this.lowestY = (cols - j) - 1;
				this.maxX = Math.max(this.maxX, i);
				this.minX = Math.min(this.minX, i);
				// we assume the matrix is never changed, only rotated
				// this means the number of nodes is always the same
				var sp = this.batchNode.getChildByTag(count);
				if (!sp) {
					sp = new cocos2d.Sprite(COLOR_NAMES[this.color], 1);
					this.batchNode.addChild(sp);
					sp.setTag(count);
					sp.setAnchorPoint(new cocos2d.Point(0, 0));
				}
				// rows == cols
				sp.setPosition(new cocos2d.Point(i * Game.TILE_SIZE, (cols - j) * Game.TILE_SIZE));
				count++;
			}
		}
	}
	// debug.log("min,max x: " + this.minX + "," + this.maxX);
};

/**
 * @param {number} x
 * @param {number} y
 */
Block.prototype.setPosition = function (x, y) {
	this.position = new cocos2d.Point(x, y);
	this.batchNode.setPosition(new cocos2d.Point(x * Game.TILE_SIZE, y * Game.TILE_SIZE));
};

/**
 * only rotate if we can actually rotate the matrix
 */
Block.prototype.rotate = function () {
	var rotatedMatrix = this.rotateMatrix();
	if (this.canMoveDown(rotatedMatrix, Game.matrix, 0)) {
		this.setMatrix(rotatedMatrix);
	}
};

Block.prototype.rotateMatrix = function () {
	var cols = this.cols,
		mat = [].concat(this.matrix);
	for (var i=0; i < cols; i++) {
		for (var j=0; j < cols; j++) {
			mat[j * cols + i] = this.matrix[(cols - 1 - i) * cols + j];
		}
	}
	return mat;
};

/**
 * just debugs the matrix
 */
Block.prototype.debugMatrix = function (matrix) {
	matrix = matrix || this.matrix;
	for (var j=this.cols-1; j >= 0; j--) {
		var arr = [];
		for (var i=0; i < this.cols; i++) {
			if (matrix[j*this.cols + i] > 0) {
				arr.push(1);
			} else {
				arr.push(0);
			}
		}
		debug.log("" + arr.join(" "));
	}
};

/**
 * can this block be moved one line down?
 * @param {Array.<number>} matrix
 * @return {boolean}
 */
Block.prototype.canMoveDown = function (myMatrix, globalMatrix, dy) {
	var cols = this.cols;
	if (arguments.length == 1) {
		globalMatrix = myMatrix;
		myMatrix = this.matrix;
		dy = -1;
	} else if (arguments == 2) {
		dy = -1;
	}
	for (var j=0; j < cols; j++) {
		for (var i=0; i < cols; i++) {
			var pos = new cocos2d.Point(this.position.x + i, this.position.y + (cols - j) - 1);
			if ((myMatrix[j * cols + i] > 0 && globalMatrix[(pos.y + dy) * Game.COLS + pos.x] > 0)) {
				// debug.log(this.position.x + "," + this.position.y + ": " + i + "," + j);
				// this.debugMatrix(myMatrix);
				// Game.debugMatrix();
				return false;
			}
		}
	}
	if (this.position.y + this.lowestY > 0) {
		return true;
	}
	return false;
};

/**
 * will move the block one row down
 */
Block.prototype.moveDown = function () {
	this.setPosition(this.position.x, this.position.y - 1);
};

Block.prototype.moveHorizontally = function (dx) {
	if (dx > 0 && (this.position.x + this.maxX) < Game.COLS) {
		this.setPosition(this.position.x + 1, this.position.y);
	} else if (this.position.x + this.minX > 0) {
		this.setPosition(this.position.x - 1, this.position.y);
	}
};

/**
 * will add the block to the scene
 * @param {cocos2d.Scene} scene
 */
Block.prototype.addToScene = function (scene) {
	scene.addChild(this.batchNode);
};

/**
 * will remove the block from the scene
 * @param {cocos2d.Scene} scene
 */
Block.prototype.removeFromScene = function (scene) {
	scene.removeChild(this.batchNode);
};

/**
 * create a new random block
 * @return {Block}
 */
Block.random = function () {
	var idx = Math.floor(Math.random() * 7);
	var spec = TILE_SPECS[idx];
	
	var block = new Block();
	block.setMatrix(spec.grid, spec.cols, spec.color);
	
	return block;
};
