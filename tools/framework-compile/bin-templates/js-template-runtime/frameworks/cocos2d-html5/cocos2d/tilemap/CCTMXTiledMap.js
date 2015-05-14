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
 Orthogonal orientation
 * @constant
 * @type Number
 */
cc.TMX_ORIENTATION_ORTHO = 0;

/**
 * Hexagonal orientation
 * @constant
 * @type Number
 */

cc.TMX_ORIENTATION_HEX = 1;

/**
 * Isometric orientation
 * @constant
 * @type Number
 */
cc.TMX_ORIENTATION_ISO = 2;

/**
 * <p>cc.TMXTiledMap knows how to parse and render a TMX map.</p>
 *
 * <p>It adds support for the TMX tiled map format used by http://www.mapeditor.org <br />
 * It supports isometric, hexagonal and orthogonal tiles.<br />
 * It also supports object groups, objects, and properties.</p>
 *
 * <p>Features: <br />
 * - Each tile will be treated as an cc.Sprite<br />
 * - The sprites are created on demand. They will be created only when you call "layer.getTileAt(position)" <br />
 * - Each tile can be rotated / moved / scaled / tinted / "opacitied", since each tile is a cc.Sprite<br />
 * - Tiles can be added/removed in runtime<br />
 * - The z-order of the tiles can be modified in runtime<br />
 * - Each tile has an anchorPoint of (0,0) <br />
 * - The anchorPoint of the TMXTileMap is (0,0) <br />
 * - The TMX layers will be added as a child <br />
 * - The TMX layers will be aliased by default <br />
 * - The tileset image will be loaded using the cc.TextureCache <br />
 * - Each tile will have a unique tag<br />
 * - Each tile will have a unique z value. top-left: z=1, bottom-right: z=max z<br />
 * - Each object group will be treated as an cc.MutableArray <br />
 * - Object class which will contain all the properties in a dictionary<br />
 * - Properties can be assigned to the Map, Layer, Object Group, and Object</p>
 *
 * <p>Limitations: <br />
 * - It only supports one tileset per layer. <br />
 * - Embeded images are not supported <br />
 * - It only supports the XML format (the JSON format is not supported)</p>
 *
 * <p>Technical description: <br />
 * Each layer is created using an cc.TMXLayer (subclass of cc.SpriteBatchNode). If you have 5 layers, then 5 cc.TMXLayer will be created, <br />
 * unless the layer visibility is off. In that case, the layer won't be created at all. <br />
 * You can obtain the layers (cc.TMXLayer objects) at runtime by: <br />
 * - map.getChildByTag(tag_number);  // 0=1st layer, 1=2nd layer, 2=3rd layer, etc...<br />
 * - map.getLayer(name_of_the_layer); </p>
 *
 * <p>Each object group is created using a cc.TMXObjectGroup which is a subclass of cc.MutableArray.<br />
 * You can obtain the object groups at runtime by: <br />
 * - map.getObjectGroup(name_of_the_object_group); </p>
 *
 * <p>Each object is a cc.TMXObject.</p>
 *
 * <p>Each property is stored as a key-value pair in an cc.MutableDictionary.<br />
 * You can obtain the properties at runtime by: </p>
 *
 * <p>map.getProperty(name_of_the_property); <br />
 * layer.getProperty(name_of_the_property); <br />
 * objectGroup.getProperty(name_of_the_property); <br />
 * object.getProperty(name_of_the_property);</p>
 * @class
 * @extends cc.Node
 * @param {String} tmxFile tmxFile fileName or content string
 * @param {String} resourcePath   If tmxFile is a file name ,it is not required.If tmxFile is content string ,it is must required.

 *
 * @property {Array}    properties      - Properties from the map. They can be added using tilemap editors
 * @property {Number}   mapOrientation  - Map orientation
 * @property {Array}    objectGroups    - Object groups of the map
 * @property {Number}   mapWidth        - Width of the map
 * @property {Number}   mapHeight       - Height of the map
 * @property {Number}   tileWidth       - Width of a tile
 * @property {Number}   tileHeight      - Height of a tile
 *
 * @example
 * //example
 * 1.
 * //create a TMXTiledMap with file name
 * var tmxTiledMap = new cc.TMXTiledMap("res/orthogonal-test1.tmx");
 * 2.
 * //create a TMXTiledMap with content string and resource path
 * var resources = "res/TileMaps";
 * var filePath = "res/TileMaps/orthogonal-test1.tmx";
 * var xmlStr = cc.loader.getRes(filePath);
 * var tmxTiledMap = new cc.TMXTiledMap(xmlStr, resources);
 */
cc.TMXTiledMap = cc.Node.extend(/** @lends cc.TMXTiledMap# */{
	properties: null,
	mapOrientation: null,
	objectGroups: null,

    //the map's size property measured in tiles
    _mapSize: null,
    _tileSize: null,
    //tile properties
    _tileProperties: null,
    _className: "TMXTiledMap",

    /**
     * Creates a TMX Tiled Map with a TMX file  or content string. <br/>
     * Constructor of cc.TMXTiledMap
     * @param {String} tmxFile tmxFile fileName or content string
     * @param {String} resourcePath   If tmxFile is a file name ,it is not required.If tmxFile is content string ,it is must required.
     */
    ctor:function(tmxFile,resourcePath){
        cc.Node.prototype.ctor.call(this);
        this._mapSize = cc.size(0, 0);
        this._tileSize = cc.size(0, 0);

        if(resourcePath !== undefined){
            this.initWithXML(tmxFile,resourcePath);
        }else if(tmxFile !== undefined){
            this.initWithTMXFile(tmxFile);
        }
    },

    /**
     * Gets the map size.
     * @return {cc.Size}
     */
    getMapSize:function () {
        return cc.size(this._mapSize.width, this._mapSize.height);
    },

    /**
     * Set the map size.
     * @param {cc.Size} Var
     */
    setMapSize:function (Var) {
        this._mapSize.width = Var.width;
        this._mapSize.height = Var.height;
    },

	_getMapWidth: function () {
		return this._mapSize.width;
	},
	_setMapWidth: function (width) {
		this._mapSize.width = width;
	},
	_getMapHeight: function () {
		return this._mapSize.height;
	},
	_setMapHeight: function (height) {
		this._mapSize.height = height;
	},

    /**
     * Gets the tile size.
     * @return {cc.Size}
     */
    getTileSize:function () {
        return cc.size(this._tileSize.width, this._tileSize.height);
    },

    /**
     * Set the tile size
     * @param {cc.Size} Var
     */
    setTileSize:function (Var) {
        this._tileSize.width = Var.width;
        this._tileSize.height = Var.height;
    },

	_getTileWidth: function () {
		return this._tileSize.width;
	},
	_setTileWidth: function (width) {
		this._tileSize.width = width;
	},
	_getTileHeight: function () {
		return this._tileSize.height;
	},
	_setTileHeight: function (height) {
		this._tileSize.height = height;
	},

    /**
     * map orientation
     * @return {Number}
     */
    getMapOrientation:function () {
        return this.mapOrientation;
    },

    /**
     * map orientation
     * @param {Number} Var
     */
    setMapOrientation:function (Var) {
        this.mapOrientation = Var;
    },

    /**
     * object groups
     * @return {Array}
     */
    getObjectGroups:function () {
        return this.objectGroups;
    },

    /**
     * object groups
     * @param {Array} Var
     */
    setObjectGroups:function (Var) {
        this.objectGroups = Var;
    },

    /**
     * Gets the properties
     * @return {object}
     */
    getProperties:function () {
        return this.properties;
    },

    /**
     * Set the properties
     * @param {object} Var
     */
    setProperties:function (Var) {
        this.properties = Var;
    },

    /**
     * Initializes the instance of cc.TMXTiledMap with tmxFile
     * @param {String} tmxFile
     * @return {Boolean} Whether the initialization was successful.
     * @example
     * //example
     * var map = new cc.TMXTiledMap()
     * map.initWithTMXFile("hello.tmx");
     */
    initWithTMXFile:function (tmxFile) {
        if(!tmxFile || tmxFile.length === 0)
            throw "cc.TMXTiledMap.initWithTMXFile(): tmxFile should be non-null or non-empty string.";
	    this.width = 0;
	    this.height = 0;
        var mapInfo = new cc.TMXMapInfo(tmxFile);
        if (!mapInfo)
            return false;

        var locTilesets = mapInfo.getTilesets();
        if(!locTilesets || locTilesets.length === 0)
            cc.log("cc.TMXTiledMap.initWithTMXFile(): Map not found. Please check the filename.");
        this._buildWithMapInfo(mapInfo);
        return true;
    },

    /**
     * Initializes the instance of cc.TMXTiledMap with tmxString
     * @param {String} tmxString
     * @param {String} resourcePath
     * @return {Boolean} Whether the initialization was successful.
     */
    initWithXML:function(tmxString, resourcePath){
        this.width = 0;
	    this.height = 0;

        var mapInfo = new cc.TMXMapInfo(tmxString, resourcePath);
        var locTilesets = mapInfo.getTilesets();
        if(!locTilesets || locTilesets.length === 0)
            cc.log("cc.TMXTiledMap.initWithXML(): Map not found. Please check the filename.");
        this._buildWithMapInfo(mapInfo);
        return true;
    },

    _buildWithMapInfo:function (mapInfo) {
        this._mapSize = mapInfo.getMapSize();
        this._tileSize = mapInfo.getTileSize();
        this.mapOrientation = mapInfo.orientation;
        this.objectGroups = mapInfo.getObjectGroups();
        this.properties = mapInfo.properties;
        this._tileProperties = mapInfo.getTileProperties();

        var idx = 0;
        var layers = mapInfo.getLayers();
        if (layers) {
            var layerInfo = null;
            for (var i = 0, len = layers.length; i < len; i++) {
                layerInfo = layers[i];
                if (layerInfo && layerInfo.visible) {
                    var child = this._parseLayer(layerInfo, mapInfo);
                    this.addChild(child, idx, idx);
                    // update content size with the max size
	                this.width = Math.max(this.width, child.width);
	                this.height = Math.max(this.height, child.height);
                    idx++;
                }
            }
        }
    },

    /**
     * Return All layers array.
     * @returns {Array}
     */
    allLayers: function () {
        var retArr = [], locChildren = this._children;
        for(var i = 0, len = locChildren.length;i< len;i++){
            var layer = locChildren[i];
            if(layer && layer instanceof cc.TMXLayer)
                retArr.push(layer);
        }
        return retArr;
    },

    /**
     * return the TMXLayer for the specific layer
     * @param {String} layerName
     * @return {cc.TMXLayer}
     */
    getLayer:function (layerName) {
        if(!layerName || layerName.length === 0)
            throw "cc.TMXTiledMap.getLayer(): layerName should be non-null or non-empty string.";
        var locChildren = this._children;
        for (var i = 0; i < locChildren.length; i++) {
            var layer = locChildren[i];
            if (layer && layer.layerName === layerName)
                return layer;
        }
        // layer not found
        return null;
    },

    /**
     * Return the TMXObjectGroup for the specific group
     * @param {String} groupName
     * @return {cc.TMXObjectGroup}
     */
    getObjectGroup:function (groupName) {
        if(!groupName || groupName.length === 0)
            throw "cc.TMXTiledMap.getObjectGroup(): groupName should be non-null or non-empty string.";
        if (this.objectGroups) {
            for (var i = 0; i < this.objectGroups.length; i++) {
                var objectGroup = this.objectGroups[i];
                if (objectGroup && objectGroup.groupName === groupName) {
                    return objectGroup;
                }
            }
        }
        // objectGroup not found
        return null;
    },

    /**
     * Return the value for the specific property name
     * @param {String} propertyName
     * @return {String}
     */
    getProperty:function (propertyName) {
        return this.properties[propertyName.toString()];
    },

    /**
     * Return properties dictionary for tile GID
     * @param {Number} GID
     * @return {object}
     * @deprecated
     */
    propertiesForGID:function (GID) {
        cc.log("propertiesForGID is deprecated. Please use getPropertiesForGID instead.");
        return this.getPropertiesForGID[GID];
    },

    /**
     * Return properties dictionary for tile GID
     * @param {Number} GID
     * @return {object}
     */
    getPropertiesForGID: function(GID) {
        return this._tileProperties[GID];
    },

    _parseLayer:function (layerInfo, mapInfo) {
        var tileset = this._tilesetForLayer(layerInfo, mapInfo);
        var layer = new cc.TMXLayer(tileset, layerInfo, mapInfo);
        // tell the layerinfo to release the ownership of the tiles map.
        layerInfo.ownTiles = false;
        layer.setupTiles();
        return layer;
    },

    _tilesetForLayer:function (layerInfo, mapInfo) {
        var size = layerInfo._layerSize;
        var tilesets = mapInfo.getTilesets();
        if (tilesets) {
            for (var i = tilesets.length - 1; i >= 0; i--) {
                var tileset = tilesets[i];
                if (tileset) {
                    for (var y = 0; y < size.height; y++) {
                        for (var x = 0; x < size.width; x++) {
                            var pos = x + size.width * y;
                            var gid = layerInfo._tiles[pos];
                            if (gid !== 0) {
                                // Optimization: quick return
                                // if the layer is invalid (more than 1 tileset per layer) an cc.assert will be thrown later
                                if (((gid & cc.TMX_TILE_FLIPPED_MASK)>>>0) >= tileset.firstGid) {
                                    return tileset;
                                }
                            }

                        }
                    }
                }
            }
        }

        // If all the tiles are 0, return empty tileset
        cc.log("cocos2d: Warning: TMX Layer " + layerInfo.name + " has no tiles");
        return null;
    }
});

var _p = cc.TMXTiledMap.prototype;

// Extended properties
/** @expose */
_p.mapWidth;
cc.defineGetterSetter(_p, "mapWidth", _p._getMapWidth, _p._setMapWidth);
/** @expose */
_p.mapHeight;
cc.defineGetterSetter(_p, "mapHeight", _p._getMapHeight, _p._setMapHeight);
/** @expose */
_p.tileWidth;
cc.defineGetterSetter(_p, "tileWidth", _p._getTileWidth, _p._setTileWidth);
/** @expose */
_p.tileHeight;
cc.defineGetterSetter(_p, "tileHeight", _p._getTileHeight, _p._setTileHeight);


/**
 * Creates a TMX Tiled Map with a TMX file  or content string.
 * Implementation cc.TMXTiledMap
 * @deprecated since v3.0 please use new cc.TMXTiledMap(tmxFile,resourcePath) instead.
 * @param {String} tmxFile tmxFile fileName or content string
 * @param {String} resourcePath   If tmxFile is a file name ,it is not required.If tmxFile is content string ,it is must required.
 * @return {cc.TMXTiledMap|undefined}
 */
cc.TMXTiledMap.create = function (tmxFile,resourcePath) {
    return new cc.TMXTiledMap(tmxFile,resourcePath);
};
