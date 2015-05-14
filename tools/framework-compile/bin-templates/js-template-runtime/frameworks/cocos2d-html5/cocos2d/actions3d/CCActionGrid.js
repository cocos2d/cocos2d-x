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
 * Base class for Grid actions
 * @class
 * @extends cc.ActionInterval
 * @param {Number} duration
 * @param {cc.Size} gridSize
 */
cc.GridAction = cc.ActionInterval.extend(/** @lends cc.GridAction# */{
    _gridSize:null,
    _gridNodeTarget:null,

	/**
	 * Constructor function, override it to extend the construction behavior, remember to call "this._super()" in the extended "ctor" function.
	 * @param {Number} duration
	 * @param {cc.Size} gridSize
	 */
    ctor:function(duration, gridSize){
        cc._checkWebGLRenderMode();
        cc.ActionInterval.prototype.ctor.call(this);
        this._gridSize = cc.size(0,0);

		gridSize && this.initWithDuration(duration, gridSize);
    },

    _cacheTargetAsGridNode: function(){},

    /**
     * to copy object with deep copy.
     * returns a clone of action.
     *
     * @return {cc.Action}
     */
    clone:function(){
        var action = new cc.GridAction();
        var locGridSize = this._gridSize;
        action.initWithDuration(this._duration, cc.size(locGridSize.width, locGridSize.height));
        return action;
    },

    /**
     * called before the action start. It will also set the target.
     *
     * @param {cc.Node} target
     */
    startWithTarget:function (target) {
        cc.ActionInterval.prototype.startWithTarget.call(this, target);
        cc.renderer.childrenOrderDirty = true;
        var newGrid = this.getGrid();
        var t = this.target;
        var targetGrid = t.grid;
        if (targetGrid && targetGrid.getReuseGrid() > 0) {
            var locGridSize = targetGrid.getGridSize();
            if (targetGrid.isActive() && (locGridSize.width === this._gridSize.width) && (locGridSize.height === this._gridSize.height))
                targetGrid.reuse();
        } else {
            if (targetGrid && targetGrid.isActive())
                targetGrid.setActive(false);
            t.grid = newGrid;
            t.grid.setActive(true);
        }
    },

    /**
     * Create a cc.ReverseTime action. Opposite with the original motion trajectory.
     * @return {cc.ReverseTime}
     */
    reverse:function () {
        return new cc.ReverseTime(this);
    },

    /**
     * Initializes the action with size and duration.
     * @param {Number} duration
     * @param {cc.Size} gridSize
     * @return {Boolean}
     */
    initWithDuration:function (duration, gridSize) {
        if (cc.ActionInterval.prototype.initWithDuration.call(this, duration)) {
            this._gridSize.width = gridSize.width;
            this._gridSize.height = gridSize.height;
            return true;
        }
        return false;
    },

    /**
     * Returns the grid.
     * @return {cc.GridBase}
     */
    getGrid:function () {
        // Abstract class needs implementation
        cc.log("cc.GridAction.getGrid(): it should be overridden in subclass.");
    }
});

/**
 * creates the action with size and duration
 * @function
 * @param {Number} duration
 * @param {cc.Size} gridSize
 * @return {cc.GridAction}
 */
cc.gridAction = function (duration, gridSize) {
    return new cc.GridAction(duration, gridSize);
};

/**
 * Please use cc.gridAction instead. <br />
 * Creates the action with size and duration.
 * @param {Number} duration
 * @param {cc.Size} gridSize
 * @return {cc.GridAction}
 * @static
 * @deprecated since v3.0 <br /> Please use cc.gridAction instead.
 */
cc.GridAction.create = cc.gridAction;

/**
 * Base class for cc.Grid3D actions. <br/>
 * Grid3D actions can modify a non-tiled grid.
 * @class
 * @extends cc.GridAction
 */
cc.Grid3DAction = cc.GridAction.extend(/** @lends cc.Grid3DAction# */{

    /**
     * returns the grid
     * @return {cc.Grid3D}
     */
    getGrid:function () {
        return new cc.Grid3D(this._gridSize);
    },

    /**
     * returns the vertex than belongs to certain position in the grid.                           <br/>
     * It will be deprecated in future, please use getVertex instead.
     * @param {cc.Point} position
     * @return {cc.Vertex3F}
     */
    vertex:function (position) {
        return this.getVertex(position);
    },

    /**
     * returns the vertex than belongs to certain position in the grid
     * @param {cc.Point} position
     * @return {cc.Vertex3F}
     */
    getVertex: function(position){
        return this.target.grid.getVertex(position);
    },

    /**
     * returns the non-transformed vertex than belongs to certain position in the grid          <br/>
     * It will be deprecated in future, please use getVertex instead.
     * @param {cc.Point} position
     * @return {cc.Vertex3F}
     */
    originalVertex:function (position) {
        return this.getOriginalVertex(position);
    },

    /**
     * returns the non-transformed vertex than belongs to certain position in the grid
     * @param {cc.Point} position
     * @return {cc.Vertex3F}
     */
    getOriginalVertex:function (position) {
        return this.target.grid.originalVertex(position);
    },

    /**
     * sets a new vertex to a certain position of the grid
     * @param {cc.Point} position
     * @param {cc.Vertex3F} vertex
     */
    setVertex:function (position, vertex) {
        this.target.grid.setVertex(position, vertex);
    }
});

/**
 * creates the action with size and duration
 * @function
 * @param {Number} duration
 * @param {cc.Size} gridSize
 * @return {cc.Grid3DAction}
 */
cc.grid3DAction = function (duration, gridSize) {
    return new cc.Grid3DAction(duration, gridSize);
};
/**
 * Please use cc.grid3DAction instead. <br />
 * creates the action with size and duration. <br />
 * @param {Number} duration
 * @param {cc.Size} gridSize
 * @return {cc.Grid3DAction}
 * @static
 * @deprecated since v3.0 <br /> Please use cc.grid3DAction instead.
 */
cc.Grid3DAction.create = cc.grid3DAction;

/**
 * Base class for cc.TiledGrid3D actions.
 * @class
 * @extends cc.GridAction
 */
cc.TiledGrid3DAction = cc.GridAction.extend(/** @lends cc.TiledGrid3DAction# */{

    /**
     * returns the tile that belongs to a certain position of the grid        <br/>
     * It will be deprecated in future, please use getTile instead.
     * @param {cc.Point} position
     * @return {cc.Quad3}
     */
    tile:function (position) {
        return this.getTile(position);
    },

    /**
     * returns the tile that belongs to a certain position of the grid
     * @param {cc.Point} position
     * @return {cc.Quad3}
     */
    getTile:function (position) {
        return this.target.grid.tile(position);
    },

    /**
     * returns the non-transformed tile that belongs to a certain position of the grid               <br/>
     * It will be deprecated in future, please use getOriginalTile instead.
     * @param {cc.Point} position
     * @return {cc.Quad3}
     */
    originalTile:function (position) {
        return this.getOriginalTile(position);
    },

    /**
     * returns the non-transformed tile that belongs to a certain position of the grid
     * @param {cc.Point} position
     * @return {cc.Quad3}
     */
    getOriginalTile:function (position) {
        return this.target.grid.originalTile(position);
    },

    /**
     * sets a new tile to a certain position of the grid
     * @param {cc.Point} position
     * @param {cc.Quad3} coords
     */
    setTile:function (position, coords) {
        this.target.grid.setTile(position, coords);
    },

    /**
     * returns the grid
     * @return {cc.TiledGrid3D}
     */
    getGrid:function () {
        return new cc.TiledGrid3D(this._gridSize);
    }
});

/**
 * Creates the action with duration and grid size
 * @function
 * @param {Number} duration
 * @param {cc.Size} gridSize
 * @return {cc.TiledGrid3DAction}
 */
cc.tiledGrid3DAction = function (duration, gridSize) {
    return new cc.TiledGrid3DAction(duration, gridSize);
};

/**
 * Please use cc.tiledGrid3DAction instead
 * Creates the action with duration and grid size
 * @param {Number} duration
 * @param {cc.Size} gridSize
 * @return {cc.TiledGrid3DAction}
 * @static
 * @deprecated since v3.0 <br /> Please use cc.tiledGrid3DAction instead.
 */
cc.TiledGrid3DAction.create = cc.tiledGrid3DAction;

/**
 * <p>
 * cc.StopGrid action.                                               <br/>
 * @warning Don't call this action if another grid action is active.                 <br/>
 * Call if you want to remove the the grid effect. Example:                          <br/>
 * cc.sequence(Lens.action(...), cc.stopGrid(...), null);              <br/>
 * </p>
 * @class
 * @extends cc.ActionInstant
 */
cc.StopGrid = cc.ActionInstant.extend(/** @lends cc.StopGrid# */{

    /**
     * called before the action start. It will also set the target.
     *
     * @param {cc.Node} target
     */
    startWithTarget:function (target) {
        cc.ActionInstant.prototype.startWithTarget.call(this, target);
        cc.renderer.childrenOrderDirty = true;
        var grid = this.target.grid;
        if (grid && grid.isActive())
            grid.setActive(false);
    }
});

/**
 * Allocates and initializes the action
 * @function
 * @return {cc.StopGrid}
 */
cc.stopGrid = function () {
    return new cc.StopGrid();
};
/**
 * Please use cc.stopGrid instead
 * Allocates and initializes the action
 * @return {cc.StopGrid}
 * @static
 * @deprecated since v3.0 <br /> Please use cc.stopGrid instead.
 */
cc.StopGrid.create = cc.stopGrid;

/**
 * cc.ReuseGrid action
 * @class
 * @extends cc.ActionInstant
 * @param {Number} times
 */
cc.ReuseGrid = cc.ActionInstant.extend(/** @lends cc.ReuseGrid# */{
    _times:null,

	/**
	 * Constructor function, override it to extend the construction behavior, remember to call "this._super()" in the extended "ctor" function.
	 * @param {Number} times
	 */
	ctor: function(times) {
		cc.ActionInstant.prototype.ctor.call(this);
		times !== undefined && this.initWithTimes(times);
	},

    /**
     * initializes an action with the number of times that the current grid will be reused
     * @param {Number} times
     * @return {Boolean}
     */
    initWithTimes:function (times) {
        this._times = times;
        return true;
    },

    /**
     * called before the action start. It will also set the target.
     *
     * @param {cc.Node} target
     */
    startWithTarget:function (target) {
        cc.ActionInstant.prototype.startWithTarget.call(this, target);
        cc.renderer.childrenOrderDirty = true;
        if (this.target.grid && this.target.grid.isActive())
            this.target.grid.setReuseGrid(this.target.grid.getReuseGrid() + this._times);
    }
});

/**
 * creates an action with the number of times that the current grid will be reused
 * @function
 * @param {Number} times
 * @return {cc.ReuseGrid}
 */
cc.reuseGrid = function (times) {
    return new cc.ReuseGrid(times);
};
/**
 * Please use cc.reuseGrid instead
 * creates an action with the number of times that the current grid will be reused
 * @param {Number} times
 * @return {cc.ReuseGrid}
 * @static
 * @deprecated since v3.0 <br /> Please use cc.reuseGrid instead.
 */
cc.ReuseGrid.create = cc.reuseGrid;
