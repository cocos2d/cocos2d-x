/****************************************************************************
 Copyright (c) 2008-2010 Ricardo Quesada
 Copyright (c) 2011-2012 cocos2d-x.org
 Copyright (c) 2013-2014 Chukong Technologies Inc.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

/**
 * cc.ShakyTiles3D action. <br />
 * Reference the test cases (Effects Test)
 * @class
 * @extends cc.TiledGrid3DAction
 * @param {Number} duration
 * @param {cc.Size} gridSize
 * @param {Number} range
 * @param {Boolean} shakeZ
 */
cc.ShakyTiles3D = cc.TiledGrid3DAction.extend(/** @lends cc.ShakyTiles3D# */{
    _randRange:0,
    _shakeZ:false,

	/**
     * Constructor function, override it to extend the construction behavior, remember to call "this._super()" in the extended "ctor" function. <br />
	 * Creates the action with a range, whether or not to shake Z vertices, a grid size, and duration.
	 * @param {Number} duration
	 * @param {cc.Size} gridSize
	 * @param {Number} range
	 * @param {Boolean} shakeZ
	 */
    ctor:function (duration, gridSize, range, shakeZ) {
        cc.GridAction.prototype.ctor.call(this);
		shakeZ !== undefined && this.initWithDuration(duration, gridSize, range, shakeZ);
    },

    /**
     * Initializes the action with a range, whether or not to shake Z vertices, a grid size, and duration.
     * @param {Number} duration
     * @param {cc.Size} gridSize
     * @param {Number} range
     * @param {Boolean} shakeZ
     * @return {Boolean}
     */
    initWithDuration:function (duration, gridSize, range, shakeZ) {
        if (cc.TiledGrid3DAction.prototype.initWithDuration.call(this, duration, gridSize)) {
            this._randRange = range;
            this._shakeZ = shakeZ;
            return true;
        }
        return false;
    },

    /**
     * Called once per frame. Time is the number of seconds of a frame interval.  <br />
     * @param {Number}  dt
     */
    update:function (dt) {
        var locGridSize = this._gridSize, locRandRange = this._randRange;
        var locPos = cc.p(0, 0);
        for (var i = 0; i < locGridSize.width; ++i) {
            for (var j = 0; j < locGridSize.height; ++j) {
                locPos.x = i;
                locPos.y = j;
                var coords = this.originalTile(locPos);

                // X
                coords.bl.x += ( cc.rand() % (locRandRange * 2) ) - locRandRange;
                coords.br.x += ( cc.rand() % (locRandRange * 2) ) - locRandRange;
                coords.tl.x += ( cc.rand() % (locRandRange * 2) ) - locRandRange;
                coords.tr.x += ( cc.rand() % (locRandRange * 2) ) - locRandRange;

                // Y
                coords.bl.y += ( cc.rand() % (locRandRange * 2) ) - locRandRange;
                coords.br.y += ( cc.rand() % (locRandRange * 2) ) - locRandRange;
                coords.tl.y += ( cc.rand() % (locRandRange * 2) ) - locRandRange;
                coords.tr.y += ( cc.rand() % (locRandRange * 2) ) - locRandRange;

                if (this._shakeZ) {
                    coords.bl.z += ( cc.rand() % (locRandRange * 2) ) - locRandRange;
                    coords.br.z += ( cc.rand() % (locRandRange * 2) ) - locRandRange;
                    coords.tl.z += ( cc.rand() % (locRandRange * 2) ) - locRandRange;
                    coords.tr.z += ( cc.rand() % (locRandRange * 2) ) - locRandRange;
                }

                this.setTile(locPos, coords);
            }
        }
    }
});

/**
 * Creates the action with a range, whether or not to shake Z vertices, a grid size, and duration. <br />
 * Reference the test cases (Effects Test)
 * @function
 * @param {Number} duration
 * @param {cc.Size} gridSize
 * @param {Number} range
 * @param {Boolean} shakeZ
 * @return {cc.ShakyTiles3D}
 */
cc.shakyTiles3D = function (duration, gridSize, range, shakeZ) {
    return new cc.ShakyTiles3D(duration, gridSize, range, shakeZ);
};

/**
 * Please use cc.shakyTiles3D instead. <br />
 * creates the action with a range, whether or not to shake Z vertices, a grid size, and duration. <br />
 * Reference the test cases (Effects Test)
 * @param {Number} duration
 * @param {cc.Size} gridSize
 * @param {Number} range
 * @param {Boolean} shakeZ
 * @return {cc.ShakyTiles3D}
 * @static
 * @deprecated since v3.0 <br /> Please use cc.shakyTiles3D instead.
 */
cc.ShakyTiles3D.create = cc.shakyTiles3D;

/**
 * cc.ShatteredTiles3D action. <br />
 * Reference the test cases (Effects Test)
 * @class
 * @extends cc.TiledGrid3DAction
 * @param {Number} duration
 * @param {cc.Size} gridSize
 * @param {Number} range
 * @param {Boolean} shatterZ
 */
cc.ShatteredTiles3D = cc.TiledGrid3DAction.extend(/** @lends cc.ShatteredTiles3D# */{
    _randRange:0,
    _once:false,
    _shatterZ:false,

	/**
     * Constructor function, override it to extend the construction behavior, remember to call "this._super()" in the extended "ctor" function. <br />
	 * Creates the action with a range, whether of not to shatter Z vertices, a grid size and duration.
	 * @param {Number} duration
	 * @param {cc.Size} gridSize
	 * @param {Number} range
	 * @param {Boolean} shatterZ
	 */
    ctor:function (duration, gridSize, range, shatterZ) {
        cc.GridAction.prototype.ctor.call(this);
		shatterZ !== undefined && this.initWithDuration(duration, gridSize, range, shatterZ);
    },

    /**
     * Initializes the action with a range, whether or not to shatter Z vertices, a grid size and duration. <br />
     * @param {Number} duration
     * @param {cc.Size} gridSize
     * @param {Number} range
     * @param {Boolean} shatterZ
     * @return {Boolean}
     */
    initWithDuration:function (duration, gridSize, range, shatterZ) {
        if (cc.TiledGrid3DAction.prototype.initWithDuration.call(this, duration, gridSize)) {
            this._once = false;
            this._randRange = range;
            this._shatterZ = shatterZ;
            return true;
        }
        return false;
    },

    /**
     * Called once per frame. Time is the number of seconds of a frame interval. <br />
     * @param {Number}  dt
     */
    update:function (dt) {
        if (this._once === false) {
            var locGridSize = this._gridSize, locRandRange = this._randRange;
            var coords, locPos = cc.p(0, 0);
            for (var i = 0; i < locGridSize.width; ++i) {
                for (var j = 0; j < locGridSize.height; ++j) {
                    locPos.x = i;
                    locPos.y = j;
                    coords = this.originalTile(locPos);

                    // X
                    coords.bl.x += ( cc.rand() % (locRandRange * 2) ) - locRandRange;
                    coords.br.x += ( cc.rand() % (locRandRange * 2) ) - locRandRange;
                    coords.tl.x += ( cc.rand() % (locRandRange * 2) ) - locRandRange;
                    coords.tr.x += ( cc.rand() % (locRandRange * 2) ) - locRandRange;

                    // Y
                    coords.bl.y += ( cc.rand() % (locRandRange * 2) ) - locRandRange;
                    coords.br.y += ( cc.rand() % (locRandRange * 2) ) - locRandRange;
                    coords.tl.y += ( cc.rand() % (locRandRange * 2) ) - locRandRange;
                    coords.tr.y += ( cc.rand() % (locRandRange * 2) ) - locRandRange;

                    if (this._shatterZ) {
                        coords.bl.z += ( cc.rand() % (locRandRange * 2) ) - locRandRange;
                        coords.br.z += ( cc.rand() % (locRandRange * 2) ) - locRandRange;
                        coords.tl.z += ( cc.rand() % (locRandRange * 2) ) - locRandRange;
                        coords.tr.z += ( cc.rand() % (locRandRange * 2) ) - locRandRange;
                    }
                    this.setTile(locPos, coords);
                }
            }
            this._once = true;
        }
    }
});

/**
 * Creates the action with a range, whether of not to shatter Z vertices, a grid size and duration. <br />
 * Reference the test cases (Effects Test)
 * @function
 * @param {Number} duration
 * @param {cc.Size} gridSize
 * @param {Number} range
 * @param {Boolean} shatterZ
 * @return {cc.ShatteredTiles3D}
 */
cc.shatteredTiles3D = function (duration, gridSize, range, shatterZ) {
    return new cc.ShatteredTiles3D(duration, gridSize, range, shatterZ);
};

/**
 * Please use cc.shatteredTiles3D instead. <br />
 * Creates the action with a range, whether of not to shatter Z vertices, a grid size and duration. <br />
 * Reference the test cases (Effects Test)
 * @param {Number} duration
 * @param {cc.Size} gridSize
 * @param {Number} range
 * @param {Boolean} shatterZ
 * @return {cc.ShatteredTiles3D}
 * @static
 * @deprecated since v3.0 <br /> Please use cc.shatteredTiles3D instead.
 */
cc.ShatteredTiles3D.create = cc.shatteredTiles3D;

/**
 * A Tile composed of position, startPosition and delta.
 * @Class
 * @constructor
 * @param {cc.Point} [position=cc.p(0,0)]
 * @param {cc.Point} [startPosition=cc.p(0,0)]
 * @param {cc.Size} [delta=cc.p(0,0)]
 */
cc.Tile = function (position, startPosition, delta) {
    this.position = position || cc.p(0,0);
    this.startPosition = startPosition || cc.p(0,0);
    this.delta = delta || cc.p(0,0);
};

/**
 * cc.ShuffleTiles action, Shuffle the tiles in random order. <br />
 * Reference the test cases (Effects Test)
 * @class
 * @extends cc.TiledGrid3DAction
 * @param {Number} duration
 * @param {cc.Size} gridSize
 * @param {Number} seed
 */
cc.ShuffleTiles = cc.TiledGrid3DAction.extend(/** @lends cc.ShuffleTiles# */{
    _seed:0,
    _tilesCount:0,
    _tilesOrder:null,
    _tiles:null,

	/**
     * Constructor function, override it to extend the construction behavior, remember to call "this._super()" in the extended "ctor" function. <br />
	 * Creates the action with a random seed, the grid size and the duration.
	 * @param {Number} duration
	 * @param {cc.Size} gridSize
	 * @param {Number} seed
	 */
    ctor:function (duration, gridSize, seed) {
        cc.GridAction.prototype.ctor.call(this);
        this._tilesOrder = [];
        this._tiles = [];

		seed !== undefined && this.initWithDuration(duration, gridSize, seed);
    },

    /**
     * Initializes the action with a random seed, the grid size and the duration.
     * @param {Number} duration
     * @param {cc.Size} gridSize
     * @param {Number} seed
     * @return {Boolean}
     */
    initWithDuration:function (duration, gridSize, seed) {
        if (cc.TiledGrid3DAction.prototype.initWithDuration.call(this, duration, gridSize)) {
            this._seed = seed;
            this._tilesOrder.length = 0;
            this._tiles.length = 0;
            return true;
        }
        return false;
    },

    /**
     * Shuffle
     * @param {Array} array
     * @param {Number} len
     */
    shuffle:function (array, len) {
        for (var i = len - 1; i >= 0; i--) {
            var j = 0 | (cc.rand() % (i + 1));
            var v = array[i];
            array[i] = array[j];
            array[j] = v;
        }
    },

    /**
     * Get Delta
     * @param {cc.Size} pos
     */
    getDelta:function (pos) {
        var locGridSize = this._gridSize;
        var idx = pos.width * locGridSize.height + pos.height;
        return cc.size(((this._tilesOrder[idx] / locGridSize.height) - pos.width),
            ((this._tilesOrder[idx] % locGridSize.height) - pos.height));
    },

    /**
     * Place Tile
     * @param {cc.Point} pos
     * @param {cc.Tile} tile
     */
    placeTile:function (pos, tile) {
        var coords = this.originalTile(pos);

        var step = this.target.grid.getStep();
        var locPosition = tile.position;
        coords.bl.x += (locPosition.x * step.x);
        coords.bl.y += (locPosition.y * step.y);

        coords.br.x += (locPosition.x * step.x);
        coords.br.y += (locPosition.y * step.y);

        coords.tl.x += (locPosition.x * step.x);
        coords.tl.y += (locPosition.y * step.y);

        coords.tr.x += (locPosition.x * step.x);
        coords.tr.y += (locPosition.y * step.y);

        this.setTile(pos, coords);
    },

    /**
     * Start with target
     * @param {cc.Node} target
     */
    startWithTarget:function (target) {
        cc.TiledGrid3DAction.prototype.startWithTarget.call(this, target);
        var locGridSize = this._gridSize;

        this._tilesCount = locGridSize.width * locGridSize.height;
        var locTilesOrder = this._tilesOrder;
        locTilesOrder.length = 0;

        /**
         * Use k to loop. Because m_nTilesCount is unsigned int,
         * and i is used later for int.
         */
        for (var k = 0; k < this._tilesCount; ++k)
            locTilesOrder[k] = k;
        this.shuffle(locTilesOrder, this._tilesCount);

        var locTiles = this._tiles ;
        locTiles.length = 0;
        var tileIndex = 0, tempSize = cc.size(0,0);
        for (var i = 0; i < locGridSize.width; ++i) {
            for (var j = 0; j < locGridSize.height; ++j) {
                locTiles[tileIndex] = new cc.Tile();
                locTiles[tileIndex].position = cc.p(i, j);
                locTiles[tileIndex].startPosition = cc.p(i, j);
                tempSize.width = i;
                tempSize.height = j;
                locTiles[tileIndex].delta = this.getDelta(tempSize);
                ++tileIndex;
            }
        }
    },

    /**
     * Called once per frame. Time is the number of seconds of a frame interval.
     * @param {Number}  dt
     */
    update:function (dt) {
        var tileIndex = 0, locGridSize = this._gridSize, locTiles = this._tiles;
        var selTile, locPos = cc.p(0, 0);
        for (var i = 0; i < locGridSize.width; ++i) {
            for (var j = 0; j < locGridSize.height; ++j) {
                locPos.x = i;
                locPos.y = j;
                selTile = locTiles[tileIndex];
                selTile.position.x = selTile.delta.width * dt;
                selTile.position.y = selTile.delta.height * dt;
                this.placeTile(locPos, selTile);
                ++tileIndex;
            }
        }
    }
});

/**
 * Creates the action with a random seed, the grid size and the duration. <br />
 * Reference the test cases (Effects Test)
 * @function
 * @param {Number} duration
 * @param {cc.Size} gridSize
 * @param {Number} seed
 * @return {cc.ShuffleTiles}
 */
cc.shuffleTiles = function (duration, gridSize, seed) {
    return new cc.ShuffleTiles(duration, gridSize, seed);
};

/**
 * Please use cc.shuffleTiles instead. <br />
 * Creates the action with a random seed, the grid size and the duration. <br />
 * Reference the test cases (Effects Test)
 * @param {Number} duration
 * @param {cc.Size} gridSize
 * @param {Number} seed
 * @return {cc.ShuffleTiles}
 * @static
 * @deprecated since v3.0 <br /> Please use cc.shuffleTiles instead.
 */
cc.ShuffleTiles.create = cc.shuffleTiles;

/**
 * cc.FadeOutTRTiles action. Fades out the tiles in a Top-Right direction. <br />
 * Reference the test cases (Effects Test)
 * @class
 * @extends cc.TiledGrid3DAction
 */
cc.FadeOutTRTiles = cc.TiledGrid3DAction.extend(/** @lends cc.FadeOutTRTiles# */{
    /**
     * Test function
     * @param {cc.Size} pos
     * @param {Number} time
     */
    testFunc:function (pos, time) {
        var locX = this._gridSize.width * time;
        var locY = this._gridSize.height * time;
        if ((locX + locY) === 0.0)
            return 1.0;
        return Math.pow((pos.width + pos.height) / (locX + locY), 6);
    },

    /**
     * Turn on Tile
     * @param {cc.Point} pos
     */
    turnOnTile:function (pos) {
        this.setTile(pos, this.originalTile(pos));
    },

    /**
     * Turn Off Tile
     * @param {cc.Point} pos
     */
    turnOffTile:function (pos) {
        this.setTile(pos, new cc.Quad3());
    },

    /**
     * Transform tile
     * @param {cc.Point} pos
     * @param {Number} distance
     */
    transformTile:function (pos, distance) {
        var coords = this.originalTile(pos);
        var step = this.target.grid.getStep();

        coords.bl.x += (step.x / 2) * (1.0 - distance);
        coords.bl.y += (step.y / 2) * (1.0 - distance);

        coords.br.x -= (step.x / 2) * (1.0 - distance);
        coords.br.y += (step.y / 2) * (1.0 - distance);

        coords.tl.x += (step.x / 2) * (1.0 - distance);
        coords.tl.y -= (step.y / 2) * (1.0 - distance);

        coords.tr.x -= (step.x / 2) * (1.0 - distance);
        coords.tr.y -= (step.y / 2) * (1.0 - distance);

        this.setTile(pos, coords);
    },

    /**
     * Called once per frame. Time is the number of seconds of a frame interval.
     * @param {Number}  dt
     */
    update:function (dt) {
        var locGridSize = this._gridSize;
        var locPos = cc.p(0, 0), locSize = cc.size(0, 0), distance;
        for (var i = 0; i < locGridSize.width; ++i) {
            for (var j = 0; j < locGridSize.height; ++j) {
                locPos.x = i;
                locPos.y = j;
                locSize.width = i;
                locSize.height = j;
                distance = this.testFunc(locSize, dt);
                if (distance === 0)
                    this.turnOffTile(locPos);
                else if (distance < 1)
                    this.transformTile(locPos, distance);
                else
                    this.turnOnTile(locPos);
            }
        }
    }
});

/**
 * Creates the action with the grid size and the duration. <br />
 * Reference the test cases (Effects Test)
 * @function
 * @param duration
 * @param gridSize
 * @return {cc.FadeOutTRTiles}
 */
cc.fadeOutTRTiles = function (duration, gridSize) {
    return new cc.FadeOutTRTiles(duration, gridSize);
};

/**
 * Please use cc.fadeOutTRTiles instead. <br />
 * Creates the action with the grid size and the duration. <br />
 * Reference the test cases (Effects Test)
 * @param duration
 * @param gridSize
 * @return {cc.FadeOutTRTiles}
 * @static
 * @deprecated since v3.0 <br /> Please use cc.fadeOutTRTiles instead.
 */
cc.FadeOutTRTiles.create = cc.fadeOutTRTiles;

/**
 * cc.FadeOutBLTiles action. Fades out the tiles in a Bottom-Left direction. <br />
 * Reference the test cases (Effects Test)
 * @class
 * @extends cc.FadeOutTRTiles
 */
cc.FadeOutBLTiles = cc.FadeOutTRTiles.extend(/** @lends cc.FadeOutBLTiles# */{
    /**
     * Test function
     * @param {cc.Size} pos
     * @param {Number} time
     */
    testFunc:function (pos, time) {
        var locX = this._gridSize.width * (1.0 - time);
        var locY = this._gridSize.height * (1.0 - time);
        if ((pos.width + pos.height) === 0)
            return 1.0;

        return Math.pow((locX + locY) / (pos.width + pos.height), 6);
    }
});

/**
 * Creates the action with the grid size and the duration. <br />
 * Reference the test cases (Effects Test)
 * @function
 * @param duration
 * @param gridSize
 * @return {cc.FadeOutBLTiles}
 */
cc.fadeOutBLTiles = function (duration, gridSize) {
    return new cc.FadeOutBLTiles(duration, gridSize);
};

/**
 * Please use cc.fadeOutBLTiles instead. <br />
 * Creates the action with the grid size and the duration. <br />
 * Reference the test cases (Effects Test)
 * @param duration
 * @param gridSize
 * @return {cc.FadeOutBLTiles}
 * @static
 * @deprecated since v3.0 <br /> Please use cc.fadeOutBLTiles instead.
 */
cc.FadeOutBLTiles.create = cc.fadeOutBLTiles;

/**
 * cc.FadeOutUpTiles action. Fades out the tiles in upwards direction. <br />
 * Reference the test cases (Effects Test)
 * @class
 * @extends cc.FadeOutTRTiles
 */
cc.FadeOutUpTiles = cc.FadeOutTRTiles.extend(/** @lends cc.FadeOutUpTiles# */{
    testFunc:function (pos, time) {
        var locY = this._gridSize.height * time;
        if (locY === 0.0)
            return 1.0;
        return Math.pow(pos.height / locY, 6);
    },

    transformTile:function (pos, distance) {
        var coords = this.originalTile(pos);
        var step = this.target.grid.getStep();

        coords.bl.y += (step.y / 2) * (1.0 - distance);
        coords.br.y += (step.y / 2) * (1.0 - distance);
        coords.tl.y -= (step.y / 2) * (1.0 - distance);
        coords.tr.y -= (step.y / 2) * (1.0 - distance);

        this.setTile(pos, coords);
    }
});

/**
 * Creates the action with the grid size and the duration. <br />
 * Reference the test cases (Effects Test)
 * @function
 * @param {Number} duration
 * @param {cc.Size} gridSize
 * @return {cc.FadeOutUpTiles}
 */
cc.fadeOutUpTiles = function (duration, gridSize) {
    return new cc.FadeOutUpTiles(duration, gridSize);
};

/**
 * Please use cc.fadeOutUpTiles instead. <br />
 * Creates the action with the grid size and the duration. <br />
 * Reference the test cases (Effects Test)
 * @param {Number} duration
 * @param {cc.Size} gridSize
 * @return {cc.FadeOutUpTiles}
 * @static
 * @deprecated since v3.0 <br /> Please use cc.fadeOutUpTiles instead.
 */
cc.FadeOutUpTiles.create = cc.fadeOutUpTiles;

/**
 * cc.FadeOutDownTiles action. Fades out the tiles in downwards direction. <br />
 * Reference the test cases (Effects Test)
 * @class
 * @extends cc.FadeOutUpTiles
 */
cc.FadeOutDownTiles = cc.FadeOutUpTiles.extend(/** @lends cc.FadeOutDownTiles# */{
    testFunc:function (pos, time) {
        var locY = this._gridSize.height * (1.0 - time);
        if (pos.height === 0)
            return 1.0;
        return Math.pow(locY / pos.height, 6);
    }
});

/**
 * Creates the action with the grid size and the duration. <br />
 * Reference the test cases (Effects Test)
 * @function
 * @param {Number} duration
 * @param {cc.Size} gridSize
 * @return {cc.FadeOutDownTiles}
 */
cc.fadeOutDownTiles = function (duration, gridSize) {
    return new cc.FadeOutDownTiles(duration, gridSize);
};
/**
 * Please use cc.fadeOutDownTiles instead. <br />
 * Creates the action with the grid size and the duration. <br />
 * Reference the test cases (Effects Test)
 * @param {Number} duration
 * @param {cc.Size} gridSize
 * @return {cc.FadeOutDownTiles}
 * @static
 * @deprecated since v3.0 <br /> Please use cc.fadeOutDownTiles instead.
 */
cc.FadeOutDownTiles.create = cc.fadeOutDownTiles;

/**
 * cc.TurnOffTiles action.<br/>
 * Turn off the files in random order. <br />
 * Reference the test cases (Effects Test)
 * @class
 * @extends cc.TiledGrid3DAction
 * @param {Number} duration
 * @param {cc.Size} gridSize
 * @param {Number|Null} [seed=0]
 * @example
 * // turnOffTiles without seed
 * var toff = new cc.TurnOffTiles(this._duration, cc.size(x, y));
 *
 * // turnOffTiles with seed
 * var toff = new cc.TurnOffTiles(this._duration, cc.size(x, y), 0);
 */
cc.TurnOffTiles = cc.TiledGrid3DAction.extend(/** @lends cc.TurnOffTiles# */{
    _seed:null,
    _tilesCount:0,
    _tilesOrder:null,

	/**
     * Constructor function, override it to extend the construction behavior, remember to call "this._super()" in the extended "ctor" function. <br />
	 * Creates the action with a random seed, the grid size and the duration.
	 * @param {Number} duration
	 * @param {cc.Size} gridSize
	 * @param {Number|Null} [seed=0]
	 */
    ctor:function (duration, gridSize, seed) {
        cc.GridAction.prototype.ctor.call(this);
        this._tilesOrder = [];

		gridSize !== undefined && this.initWithDuration(duration, gridSize, seed);
    },

    /**
     * Initializes the action with a random seed, the grid size and the duration.
     * @param {Number} duration
     * @param {cc.Size} gridSize
     * @param {Number|Null} [seed=0]
     * @return {Boolean}
     */
    initWithDuration:function (duration, gridSize, seed) {
        if (cc.TiledGrid3DAction.prototype.initWithDuration.call(this, duration, gridSize)) {
            this._seed = seed || 0;
            this._tilesOrder.length = 0;
            return true;
        }
        return false;
    },

    /**
     * Shuffle
     * @param {Array} array
     * @param {Number} len
     */
    shuffle:function (array, len) {
        for (var i = len - 1; i >= 0; i--) {
            var j = 0 | (cc.rand() % (i + 1));
            var v = array[i];
            array[i] = array[j];
            array[j] = v;
        }
    },

    /**
     * Turn on tile.
     * @param {cc.Point} pos
     */
    turnOnTile:function (pos) {
        this.setTile(pos, this.originalTile(pos));
    },

    /**
     * Turn off title.
     * @param {cc.Point} pos
     */
    turnOffTile:function (pos) {
        this.setTile(pos, new cc.Quad3());
    },

    /**
     * called before the action start. It will also set the target.
     * @param {cc.Node} target
     */
    startWithTarget:function (target) {
        cc.TiledGrid3DAction.prototype.startWithTarget.call(this, target);

        this._tilesCount = this._gridSize.width * this._gridSize.height;
        var locTilesOrder = this._tilesOrder;
        locTilesOrder.length = 0;
        for (var i = 0; i < this._tilesCount; ++i)
            locTilesOrder[i] = i;
        this.shuffle(locTilesOrder, this._tilesCount);
    },

    /**
     * Called once per frame. Time is the number of seconds of a frame interval.
     * @param {Number}  dt
     */
    update:function (dt) {
        var l = 0 | (dt * this._tilesCount), locGridSize = this._gridSize;
        var t,tilePos = cc.p(0,0), locTilesOrder = this._tilesOrder;
        for (var i = 0; i < this._tilesCount; i++) {
            t = locTilesOrder[i];
            tilePos.x = 0 | (t / locGridSize.height);
            tilePos.y = t % (0 | locGridSize.height);
            if (i < l)
                this.turnOffTile(tilePos);
            else
                this.turnOnTile(tilePos);
        }
    }
});

/**
 * Creates the action with a random seed, the grid size and the duration. <br />
 * Reference the test cases (Effects Test)
 * @function
 * @param {Number} duration
 * @param {cc.Size} gridSize
 * @param {Number|Null} [seed=0]
 * @return {cc.TurnOffTiles}
 * @example
 * // example
 * // turnOffTiles without seed
 * var toff = cc.turnOffTiles(this._duration, cc.size(x, y));
 *
 * // turnOffTiles with seed
 * var toff = cc.turnOffTiles(this._duration, cc.size(x, y), 0);
 */
cc.turnOffTiles = function (duration, gridSize, seed) {
    return new cc.TurnOffTiles(duration, gridSize, seed);
};
/**
 * Please use cc.turnOffTiles instead. <br />
 * Creates the action with a random seed, the grid size and the duration. <br />
 * Reference the test cases (Effects Test)
 * @param {Number} duration
 * @param {cc.Size} gridSize
 * @param {Number|Null} [seed=0]
 * @return {cc.TurnOffTiles}
 * @static
 * @deprecated since v3.0 <br /> Please use cc.turnOffTiles instead.
 */
cc.TurnOffTiles.create = cc.turnOffTiles;

/**
 * cc.WavesTiles3D action. <br />
 * Reference the test cases (Effects Test)
 * @class
 * @extends cc.TiledGrid3DAction
 * @param {Number} duration
 * @param {cc.Size} gridSize
 * @param {Number} waves
 * @param {Number} amplitude
 */
cc.WavesTiles3D = cc.TiledGrid3DAction.extend(/** @lends cc.WavesTiles3D# */{
    _waves:0,
    _amplitude:0,
    _amplitudeRate:0,

	/**
     * Constructor function, override it to extend the construction behavior, remember to call "this._super()" in the extended "ctor" function. <br />
	 * creates the action with a number of waves, the waves amplitude, the grid size and the duration.
	 * @param {Number} duration
	 * @param {cc.Size} gridSize
	 * @param {Number} waves
	 * @param {Number} amplitude
	 */
    ctor:function (duration, gridSize, waves, amplitude) {
        cc.GridAction.prototype.ctor.call(this);
		amplitude !== undefined && this.initWithDuration(duration, gridSize, waves, amplitude);
    },

    /**
     * get amplitude of waves
     * @return {Number}
     */
    getAmplitude:function () {
        return this._amplitude;
    },

    /**
     * set amplitude of waves
     * @param {Number} amplitude
     */
    setAmplitude:function (amplitude) {
        this._amplitude = amplitude;
    },

    /**
     * get amplitude rate of waves
     * @return {Number}
     */
    getAmplitudeRate:function () {
        return this._amplitudeRate;
    },

    /**
     * set amplitude rate of waves
     * @param {Number} amplitudeRate
     */
    setAmplitudeRate:function (amplitudeRate) {
        this._amplitudeRate = amplitudeRate;
    },

    /**
     * initializes the action with a number of waves, the waves amplitude, the grid size and the duration
     * @param {Number} duration
     * @param {cc.Size} gridSize
     * @param {Number} waves
     * @param {Number} amplitude
     * @return {Boolean}
     */
    initWithDuration:function (duration, gridSize, waves, amplitude) {
        if (cc.TiledGrid3DAction.prototype.initWithDuration.call(this, duration, gridSize)) {
            this._waves = waves;
            this._amplitude = amplitude;
            this._amplitudeRate = 1.0;
            return true;
        }
        return false;
    },

    /**
     * Called once per frame. Time is the number of seconds of a frame interval.
     * @param {Number}  dt
     */
    update:function (dt) {
        var locGridSize = this._gridSize, locWaves = this._waves, locAmplitude = this._amplitude, locAmplitudeRate = this._amplitudeRate;
        var locPos = cc.p(0, 0), coords;
        for (var i = 0; i < locGridSize.width; i++) {
            for (var j = 0; j < locGridSize.height; j++) {
                locPos.x = i;
                locPos.y = j;
                coords = this.originalTile(locPos);
                coords.bl.z = (Math.sin(dt * Math.PI * locWaves * 2 +
                    (coords.bl.y + coords.bl.x) * 0.01) * locAmplitude * locAmplitudeRate);
                coords.br.z = coords.bl.z;
                coords.tl.z = coords.bl.z;
                coords.tr.z = coords.bl.z;
                this.setTile(locPos, coords);
            }
        }
    }
});

/**
 * creates the action with a number of waves, the waves amplitude, the grid size and the duration. <br />
 * Reference the test cases (Effects Test)
 * @function
 * @param {Number} duration
 * @param {cc.Size} gridSize
 * @param {Number} waves
 * @param {Number} amplitude
 * @return {cc.WavesTiles3D}
 */
cc.wavesTiles3D = function (duration, gridSize, waves, amplitude) {
    return new cc.WavesTiles3D(duration, gridSize, waves, amplitude);
};
/**
 * Please use cc.wavesTiles3D instead
 * creates the action with a number of waves, the waves amplitude, the grid size and the duration. <br />
 * Reference the test cases (Effects Test)
 * @param {Number} duration
 * @param {cc.Size} gridSize
 * @param {Number} waves
 * @param {Number} amplitude
 * @return {cc.WavesTiles3D}
 * @static
 * @deprecated since v3.0 <br /> Please use cc.wavesTiles3D instead.
 */
cc.WavesTiles3D.create = cc.wavesTiles3D;

/**
 * cc.JumpTiles3D action.  A sin function is executed to move the tiles across the Z axis. <br />
 * Reference the test cases (Effects Test)
 * @class
 * @extends cc.TiledGrid3DAction
 * @param {Number} duration
 * @param {cc.Size} gridSize
 * @param {Number} numberOfJumps
 * @param {Number} amplitude
 */
cc.JumpTiles3D = cc.TiledGrid3DAction.extend(/** @lends cc.JumpTiles3D# */{
    _jumps:0,
    _amplitude:0,
    _amplitudeRate:0,

	/**
     * Constructor function, override it to extend the construction behavior, remember to call "this._super()" in the extended "ctor" function. <br />
	 * creates the action with the number of jumps, the sin amplitude, the grid size and the duration.
	 * @param {Number} duration
	 * @param {cc.Size} gridSize
	 * @param {Number} numberOfJumps
	 * @param {Number} amplitude
	 */
    ctor:function (duration, gridSize, numberOfJumps, amplitude) {
        cc.GridAction.prototype.ctor.call(this);
		amplitude !== undefined && this.initWithDuration(duration, gridSize, numberOfJumps, amplitude);
    },

    /**
     * get amplitude of the sin
     * @return {Number}
     */
    getAmplitude:function () {
        return this._amplitude;
    },

    /**
     * set amplitude of the sin
     * @param {Number} amplitude
     */
    setAmplitude:function (amplitude) {
        this._amplitude = amplitude;
    },

    /**
     * get amplitude rate
     * @return {Number}
     */
    getAmplitudeRate:function () {
        return this._amplitudeRate;
    },

    /**
     * set amplitude rate
     * @param amplitudeRate
     */
    setAmplitudeRate:function (amplitudeRate) {
        this._amplitudeRate = amplitudeRate;
    },

    /**
     * initializes the action with the number of jumps, the sin amplitude, the grid size and the duration
     * @param {Number} duration
     * @param {cc.Size} gridSize
     * @param {Number} numberOfJumps
     * @param {Number} amplitude
     */
    initWithDuration:function (duration, gridSize, numberOfJumps, amplitude) {
        if (cc.TiledGrid3DAction.prototype.initWithDuration.call(this, duration, gridSize)) {
            this._jumps = numberOfJumps;
            this._amplitude = amplitude;
            this._amplitudeRate = 1.0;
            return true;
        }
        return false;
    },

    /**
     * Called once per frame. Time is the number of seconds of a frame interval.
     * @param {Number}  dt
     */
    update:function (dt) {
        var sinz = (Math.sin(Math.PI * dt * this._jumps * 2) * this._amplitude * this._amplitudeRate );
        var sinz2 = (Math.sin(Math.PI * (dt * this._jumps * 2 + 1)) * this._amplitude * this._amplitudeRate );

        var locGridSize = this._gridSize;
        var locGrid = this.target.grid;
        var coords, locPos = cc.p(0, 0);
        for (var i = 0; i < locGridSize.width; i++) {
            for (var j = 0; j < locGridSize.height; j++) {
                locPos.x = i;
                locPos.y = j;
                //hack for html5
                //var coords = this.originalTile(cc.p(i, j));
                coords = locGrid.originalTile(locPos);

                if (((i + j) % 2) === 0) {
                    coords.bl.z += sinz;
                    coords.br.z += sinz;
                    coords.tl.z += sinz;
                    coords.tr.z += sinz;
                } else {
                    coords.bl.z += sinz2;
                    coords.br.z += sinz2;
                    coords.tl.z += sinz2;
                    coords.tr.z += sinz2;
                }
                //hack for html5
                //this.setTile(cc.p(i, j), coords);
                locGrid.setTile(locPos, coords);
            }
        }
    }
});

/**
 * creates the action with the number of jumps, the sin amplitude, the grid size and the duration. <br />
 * Reference the test cases (Effects Test)
 * @function
 * @param {Number} duration
 * @param {cc.Size} gridSize
 * @param {Number} numberOfJumps
 * @param {Number} amplitude
 * @return {cc.JumpTiles3D}
 */
cc.jumpTiles3D = function (duration, gridSize, numberOfJumps, amplitude) {
    return new cc.JumpTiles3D(duration, gridSize, numberOfJumps, amplitude);
};

/**
 * Please use cc.jumpTiles3D instead
 * creates the action with the number of jumps, the sin amplitude, the grid size and the duration. <br />
 * Reference the test cases (Effects Test)
 * @param {Number} duration
 * @param {cc.Size} gridSize
 * @param {Number} numberOfJumps
 * @param {Number} amplitude
 * @return {cc.JumpTiles3D}
 * @static
 * @deprecated since v3.0 <br /> Please use cc.jumpTiles3D instead.
 */
cc.JumpTiles3D.create = cc.jumpTiles3D;

/**
 * cc.SplitRows action. <br />
 * Reference the test cases (Effects Test)
 * @class
 * @extends cc.TiledGrid3DAction
 * @param {Number} duration
 * @param {Number} rows
 */
cc.SplitRows = cc.TiledGrid3DAction.extend(/** @lends cc.SplitRows# */{
    _rows:0,
    _winSize:null,

	/**
     * Constructor function, override it to extend the construction behavior, remember to call "this._super()" in the extended "ctor" function. <br />
	 * creates the action with the number of rows to split and the duration.
	 * @param {Number} duration
	 * @param {Number} rows
	 */
    ctor:function (duration, rows) {
        cc.GridAction.prototype.ctor.call(this);
		rows !== undefined && this.initWithDuration(duration, rows);
    },

    /**
     * initializes the action with the number of rows to split and the duration
     * @param {Number} duration
     * @param {Number} rows
     * @return {Boolean}
     */
    initWithDuration:function (duration, rows) {
        this._rows = rows;
        return cc.TiledGrid3DAction.prototype.initWithDuration.call(this, duration, cc.size(1, rows));
    },

    /**
     * Called once per frame. Time is the number of seconds of a frame interval.
     * @param {Number}  dt
     */
    update:function (dt) {
        var locGridSize = this._gridSize, locWinSizeWidth = this._winSize.width;
        var coords, direction, locPos = cc.p(0, 0);
        for (var j = 0; j < locGridSize.height; ++j) {
            locPos.y = j;
            coords = this.originalTile(locPos);
            direction = 1;

            if ((j % 2 ) === 0)
                direction = -1;

            coords.bl.x += direction * locWinSizeWidth * dt;
            coords.br.x += direction * locWinSizeWidth * dt;
            coords.tl.x += direction * locWinSizeWidth * dt;
            coords.tr.x += direction * locWinSizeWidth * dt;

            this.setTile(locPos, coords);
        }
    },

    /**
     * called before the action start. It will also set the target.
     * @param {cc.Node} target
     */
    startWithTarget:function (target) {
        cc.TiledGrid3DAction.prototype.startWithTarget.call(this, target);
        this._winSize = cc.director.getWinSizeInPixels();
    }
});

/**
 * creates the action with the number of rows to split and the duration. <br />
 * Reference the test cases (Effects Test)
 * @function
 * @param {Number} duration
 * @param {Number} rows
 * @return {cc.SplitRows}
 */
cc.splitRows = function (duration, rows) {
    return new cc.SplitRows(duration, rows);
};

/**
 * Please use cc.splitRows instead
 * creates the action with the number of rows to split and the duration. <br />
 * Reference the test cases (Effects Test)
 * @param {Number} duration
 * @param {Number} rows
 * @return {cc.SplitRows}
 * @static
 * @deprecated since v3.0 <br /> Please use cc.splitRows instead.
 */
cc.SplitRows.create = cc.splitRows;

/**
 * cc.SplitCols action. <br />
 * Reference the test cases (Effects Test)
 * @class
 * @extends cc.TiledGrid3DAction
 * @param {Number} duration
 * @param {Number} cols
 */
cc.SplitCols = cc.TiledGrid3DAction.extend(/** @lends cc.SplitCols# */{
    _cols:0,
    _winSize:null,

	/**
     * Constructor function, override it to extend the construction behavior, remember to call "this._super()" in the extended "ctor" function. <br />
	 * Creates the action with the number of columns to split and the duration.
	 * @param {Number} duration
	 * @param {Number} cols
	 */
    ctor:function (duration, cols) {
        cc.GridAction.prototype.ctor.call(this);
		cols !== undefined && this.initWithDuration(duration, cols);
    },
    /**
     * initializes the action with the number of columns to split and the duration
     * @param {Number} duration
     * @param {Number} cols
     * @return {Boolean}
     */
    initWithDuration:function (duration, cols) {
        this._cols = cols;
        return cc.TiledGrid3DAction.prototype.initWithDuration.call(this, duration, cc.size(cols, 1));
    },

    /**
     * Called once per frame. Time is the number of seconds of a frame interval.
     * @param {Number}  dt
     */
    update:function (dt) {
        var locGridSizeWidth = this._gridSize.width, locWinSizeHeight = this._winSize.height;
        var coords, direction, locPos = cc.p(0, 0);
        for (var i = 0; i < locGridSizeWidth; ++i) {
            locPos.x = i;
            coords = this.originalTile(locPos);
            direction = 1;

            if ((i % 2 ) === 0)
                direction = -1;

            coords.bl.y += direction * locWinSizeHeight * dt;
            coords.br.y += direction * locWinSizeHeight * dt;
            coords.tl.y += direction * locWinSizeHeight * dt;
            coords.tr.y += direction * locWinSizeHeight * dt;

            this.setTile(locPos, coords);
        }
        cc.renderer.childrenOrderDirty = true;
    },

    /**
     * called before the action start. It will also set the target.
     * @param {cc.Node} target
     */
    startWithTarget:function (target) {
        cc.TiledGrid3DAction.prototype.startWithTarget.call(this, target);
        this._winSize = cc.director.getWinSizeInPixels();
    }
});

/**
 * creates the action with the number of columns to split and the duration.  <br />
 * Reference the test cases (Effects Test)
 * @function
 * @param {Number} duration
 * @param {Number} cols
 * @return {cc.SplitCols}
 */
cc.splitCols = function (duration, cols) {
    return new cc.SplitCols(duration, cols);
};

/**
 * Please use cc.splitCols instead.
 * creates the action with the number of columns to split and the duration.  <br />
 * Reference the test cases (Effects Test)
 * @param {Number} duration
 * @param {Number} cols
 * @return {cc.SplitCols}
 * @static
 * @deprecated since v3.0 <br /> Please use cc.splitCols instead.
 */
cc.SplitCols.create = cc.splitCols;