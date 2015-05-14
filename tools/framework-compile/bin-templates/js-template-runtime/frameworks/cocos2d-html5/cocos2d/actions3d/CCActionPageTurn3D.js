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
 * <p>
 *     This action simulates a page turn from the bottom right hand corner of the screen.     <br/>
 *     It's not much use by itself but is used by the PageTurnTransition.                     <br/>
 *                                                                                            <br/>
 *     Based on an original paper by L Hong et al.                                            <br/>
 *     http://www.parc.com/publication/1638/turning-pages-of-3d-electronic-books.html
 * </p>
 * @class
 * @extends cc.Grid3DAction
 */
cc.PageTurn3D = cc.Grid3DAction.extend(/** @lends cc.PageTurn3D# */{
    getGrid: function(){
        var result = new cc.Grid3D(this._gridSize);
        result.setNeedDepthTestForBlit(true);
        return result;
    },

    clone: function(){
       var ret = new cc.PageTurn3D();
        ret.initWithDuration(this._duration, this._gridSize);
        return ret;
    },

    /**
     * Update each tick                                         <br/>
     * Time is the percentage of the way through the duration
     */
    update:function (time) {
        var tt = Math.max(0, time - 0.25);
        var deltaAy = (tt * tt * 500);
        var ay = -100 - deltaAy;

        var deltaTheta = -Math.PI / 2 * Math.sqrt(time);
        var theta = /*0.01f */ +Math.PI / 2 + deltaTheta;

        var sinTheta = Math.sin(theta);
        var cosTheta = Math.cos(theta);

        var locGridSize = this._gridSize;
        var locVer = cc.p(0, 0);
        for (var i = 0; i <= locGridSize.width; ++i) {
            for (var j = 0; j <= locGridSize.height; ++j) {
                locVer.x = i;
                locVer.y = j;
                // Get original vertex
                var p = this.getOriginalVertex(locVer);

                var R = Math.sqrt((p.x * p.x) + ((p.y - ay) * (p.y - ay)));
                var r = R * sinTheta;
                var alpha = Math.asin(p.x / R);
                var beta = alpha / sinTheta;
                var cosBeta = Math.cos(beta);

                // If beta > PI then we've wrapped around the cone
                // Reduce the radius to stop these points interfering with others
                if (beta <= Math.PI)
                    p.x = ( r * Math.sin(beta));
                else
                    p.x = 0;     //Force X = 0 to stop wrapped points

                p.y = ( R + ay - ( r * (1 - cosBeta) * sinTheta));

                // We scale z here to avoid the animation being
                // too much bigger than the screen due to perspectve transform
                p.z = (r * ( 1 - cosBeta ) * cosTheta) / 7;// "100" didn't work for

                //	Stop z coord from dropping beneath underlying page in a transition
                // issue #751
                if (p.z < 0.5)
                    p.z = 0.5;

                // Set new coords
                this.setVertex(locVer, p);
            }
        }
    }
});

/**
 * create PageTurn3D action
 * @function
 * @param {Number} duration
 * @param {cc.Size} gridSize
 * @return {cc.PageTurn3D}
 */
cc.pageTurn3D = function (duration, gridSize) {
    return new cc.PageTurn3D(duration, gridSize);
};
/**
 * Please use cc.pageTurn3D instead
 * create PageTurn3D action
 * @param {Number} duration
 * @param {cc.Size} gridSize
 * @return {cc.PageTurn3D}
 * @static
 * @deprecated since v3.0 please use cc.pageTurn3D instead.
 */
cc.PageTurn3D.create = cc.pageTurn3D;