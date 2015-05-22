/****************************************************************************
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
 * @ignore
 */
ccs.PT_RATIO = 32;

/**
 * Base class for ccs.ColliderFilter
 * @class
 * @extends ccs.Class
 */
ccs.ColliderFilter = ccs.Class.extend(/** @lends ccs.ColliderFilter# */{
    _collisionType: 0,
    _group: 0,
    _categoryBits: 0,
    _groupIndex: 0,
    _maskBits: 0,

    ctor: function (collisionType, group) {
        this._collisionType = collisionType || 0;
        this._group = group || 0;
    },

    updateShape: function (shape) {
        if(shape instanceof cp.Shape){
            shape.collision_type = this._collisionType;
            shape.group = this._group;
        }else if(shape instanceof Box2D.b2FilterData){
            var filter = new Box2D.b2FilterData();
            filter.categoryBits = this._categoryBits;
            filter.groupIndex = this._groupIndex;
            filter.maskBits = this._maskBits;

            shape.SetFilterData(filter);
        }
    }
});

/**
 * Base class for ccs.ColliderBody
 * @class
 * @extends ccs.Class
 *
 * @property {ccs.ContourData}      contourData     - The contour data of collider body
 * @property {ccs.Shape}            shape           - The shape of collider body
 * @property {ccs.ColliderFilter}   colliderFilter  - The collider filter of collider body
 *
 */
ccs.ColliderBody = ccs.Class.extend(/** @lends ccs.ColliderBody# */{
    shape: null,
    coutourData: null,
    colliderFilter: null,
    _calculatedVertexList: null,
    ctor: function (contourData) {
        this.shape = null;
        this.coutourData = contourData;
        this.colliderFilter = new ccs.ColliderFilter();
        if (ccs.ENABLE_PHYSICS_SAVE_CALCULATED_VERTEX) {
            this._calculatedVertexList = [];
        }
    },

    /**
     * contourData getter
     * @returns {ccs.ContourData}
     */
    getContourData: function () {
        return this.coutourData;
    },

    /**
     * colliderFilter setter
     * @param {ccs.ColliderFilter} colliderFilter
     */
    setColliderFilter: function (colliderFilter) {
        this.colliderFilter = colliderFilter;
    },

    /**
     * get calculated vertex list
     * @returns {Array}
     */
    getCalculatedVertexList: function () {
        return this._calculatedVertexList;
    },

    setB2Fixture: function(fixture){
        this._fixture = fixture;
    },

    getB2Fixture: function(){
        return this._fixture;
    },

    /**
     * shape getter
     * @param {ccs.Shape} shape
     */
    setShape: function (shape) {
        this.shape = shape;
    },

    /**
     * shape setter
     * @return {ccs.Shape}
     */
    getShape: function () {
        return this.shape;
    },

    /**
     * contourData setter
     * @param {ccs.ContourData} contourData
     */
    setContourData: function (contourData) {
        this.coutourData = contourData;
    },

    /**
     * colliderFilter getter
     * @returns {ccs.ColliderFilter}
     */
    getColliderFilter: function () {
        return this.colliderFilter;
    }
});

/**
 * Base class for ccs.ColliderDetector
 * @class
 * @extends ccs.Class
 *
 * @param {ccs.Bone} [bone]
 *
 * @property {ccs.ColliderFilter}   colliderFilter  - The collider filter of the collider detector
 * @property {Boolean}              active          - Indicate whether the collider detector is active
 * @property {Object}               body            - The collider body
 */
ccs.ColliderDetector = ccs.Class.extend(/** @lends ccs.ColliderDetector# */{
    _colliderBodyList: null,
    _bone: null,
    _body: null,
    _active: false,
    _filter: null,
    helpPoint: cc.p(0, 0),

    ctor: function (bone) {
        this._colliderBodyList = [];
        this._bone = null;
        this._body = null;
        this._active = false;
        this._filter = null;

        ccs.ColliderDetector.prototype.init.call(this, bone);
    },
    init: function (bone) {
        this._colliderBodyList.length = 0;
        if (bone)
            this._bone = bone;
        this._filter = new ccs.ColliderFilter();
        return true;
    },

    /**
     *  add contourData
     * @param {ccs.ContourData} contourData
     */
    addContourData: function (contourData) {
        var colliderBody = new ccs.ColliderBody(contourData);
        this._colliderBodyList.push(colliderBody);

        if (ccs.ENABLE_PHYSICS_SAVE_CALCULATED_VERTEX) {
            var calculatedVertexList = colliderBody.getCalculatedVertexList();
            var vertexList = contourData.vertexList;
            for (var i = 0; i < vertexList.length; i++) {
                var newVertex = new ccs.ContourVertex2(0, 0);
                calculatedVertexList.push(newVertex);
            }
        }
    },

    /**
     * add contourData
     * @param {Array} contourDataList
     */
    addContourDataList: function (contourDataList) {
        for (var i = 0; i < contourDataList.length; i++) {
            this.addContourData(contourDataList[i]);
        }
    },

    /**
     * remove contourData
     * @param contourData
     */
    removeContourData: function (contourData) {
        var eraseList = [], i, locBodyList = this._colliderBodyList;
        for (i = 0; i < locBodyList.length; i++) {
            var body = locBodyList[i];
            if (body && body.getContourData() === contourData)
                eraseList.push(body);
        }

        for (i=0; i<eraseList.length; i++)
            cc.arrayRemoveObject(locBodyList, eraseList[i]);
    },

    /**
     * remove all body
     */
    removeAll: function () {
        this._colliderBodyList.length = 0;
    },

    setActive: function (active) {
        if (this._active === active)
            return;
        this._active = active;

        var locBody = this._body;
        var locShape;
        if (locBody) {
            var colliderBody = null;
            if (this._active) {
                for (var i = 0; i < this._colliderBodyList.length; i++) {
                    colliderBody = this._colliderBodyList[i];
                    locShape = colliderBody.getShape();
                    locBody.space.addShape(locShape);
                }
            } else {
                for (var i = 0; i < this._colliderBodyList.length; i++) {
                    colliderBody = this._colliderBodyList[i];
                    locShape = colliderBody.getShape();
                    locBody.space.removeShape(locShape);
                }
            }
        }
    },

    getActive: function () {
        return this._active;
    },

    getColliderBodyList: function(){
        return this._colliderBodyList;
    },

    /**
     * set colliderFilter
     * @param {ccs.ColliderFilter} filter
     */
    setColliderFilter: function (filter) {
        this._filter = filter;
        var locBodyList = this._colliderBodyList;
        for(var i=0; i< locBodyList.length; i++){
            var colliderBody = locBodyList[i];
            colliderBody.setColliderFilter(filter);
            if (colliderBody.getShape())
                colliderBody.getColliderFilter().updateShape(colliderBody.getShape());
        }
    },

    /**
     * get colliderFilter
     * @returns {ccs.ColliderFilter}
     */
    getColliderFilter: function () {
        return this._filter;
    },

    updateTransform: function (t) {
        if (!this._active)
            return;

        var colliderBody = null;
        var locBody = this._body;
        var locHelpPoint = this.helpPoint;
        for (var i = 0; i < this._colliderBodyList.length; i++) {

            colliderBody = this._colliderBodyList[i];
            var contourData = colliderBody.getContourData();

            //default physics engine: Chipmunk
            var shape = null;
            if (locBody) {
                //Box2d shape = (b2PolygonShape *)colliderBody->getB2Fixture()->GetShape();
                shape = colliderBody.getShape();
            }

            var vs = contourData.vertexList;
            var cvs = colliderBody.getCalculatedVertexList();

            for (var j = 0; j < vs.length; j++) {
                locHelpPoint.x = vs[j].x;
                locHelpPoint.y = vs[j].y;
                locHelpPoint = cc.pointApplyAffineTransform(locHelpPoint, t);

                if (ccs.ENABLE_PHYSICS_SAVE_CALCULATED_VERTEX) {
                    var v = cc.p(0, 0);
                    v.x = locHelpPoint.x;
                    v.y = locHelpPoint.y;
                    cvs[j] = v;
                }

                if (shape) {
                    shape.verts[j * 2] = locHelpPoint.x;
                    shape.verts[j * 2 + 1] = locHelpPoint.y;
                }
            }
            if (shape) {
                for (var j = 0; j < vs.length; j++) {
                    var b = shape.verts[(j + 1) % shape.verts.length];
                    var n = cp.v.normalize(cp.v.perp(cp.v.sub(b, shape.verts[j])));

                    if(shape.planes){
                        shape.planes[j].n = n;
                        shape.planes[j].d = cp.v.dot(n, shape.verts[j]);
                    }
//                    var b = shape.verts[(i + 1) % shape.numVerts];
//                    var n = cp.v.normalize(cp.v.perp(cp.v.sub(b, shape.verts[i])));
//
//                    shape.planes[i].n = n;
//                    shape.planes[i].d = cp.v.dot(n, shape.verts[i]);
                }
            }
        }
    },

    setBody: function (body) {
        this._body = body;
        var colliderBody, locBodyList = this._colliderBodyList;
        for (var i = 0; i < locBodyList.length; i++) {
            colliderBody = locBodyList[i];
            var contourData = colliderBody.getContourData(), verts = [];
            var vs = contourData.vertexList;
            for (var j = 0; j < vs.length; j++) {
                var v = vs[j];
                verts.push(v.x);
                verts.push(v.y);
            }
            var shape = new cp.PolyShape(this._body, verts, cp.vzero);
            shape.sensor = true;
            shape.data = this._bone;
            if (this._active)
                this._body.space.addShape(shape);
            colliderBody.setShape(shape);
            colliderBody.getColliderFilter().updateShape(shape);
        }
    },

    getBody: function () {
        return this._body;
    }
});

var _p = ccs.ColliderDetector.prototype;

// Extended properties
/** @expose */
_p.colliderFilter;
cc.defineGetterSetter(_p, "colliderFilter", _p.getColliderFilter, _p.setColliderFilter);
/** @expose */
_p.active;
cc.defineGetterSetter(_p, "active", _p.getActive, _p.setActive);
/** @expose */
_p.body;
cc.defineGetterSetter(_p, "body", _p.getBody, _p.setBody);

_p = null;

ccs.ColliderDetector.create = function (bone) {
    return new ccs.ColliderDetector(bone);
};