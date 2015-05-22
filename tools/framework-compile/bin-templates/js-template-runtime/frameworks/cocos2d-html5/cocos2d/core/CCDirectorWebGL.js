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


if (cc._renderType === cc._RENDER_TYPE_WEBGL) {
    (function () {

        /**
         * OpenGL projection protocol
         * @class
         * @extends cc.Class
         */
        cc.DirectorDelegate = cc.Class.extend(/** @lends cc.DirectorDelegate# */{
            /**
             * Called by CCDirector when the projection is updated, and "custom" projection is used
             */
            updateProjection: function () {
            }
        });

        var _p = cc.Director.prototype;

        _p.setProjection = function (projection) {
            var _t = this;
            var size = _t._winSizeInPoints;

            _t.setViewport();

            var view = _t._openGLView,
                ox = view._viewPortRect.x / view._scaleX,
                oy = view._viewPortRect.y / view._scaleY;

            switch (projection) {
                case cc.Director.PROJECTION_2D:
                    cc.kmGLMatrixMode(cc.KM_GL_PROJECTION);
                    cc.kmGLLoadIdentity();
                    var orthoMatrix = cc.math.Matrix4.createOrthographicProjection(
                        -ox,
                        size.width - ox,
                        -oy,
                        size.height - oy,
                        -1024, 1024);
                    cc.kmGLMultMatrix(orthoMatrix);
                    cc.kmGLMatrixMode(cc.KM_GL_MODELVIEW);
                    cc.kmGLLoadIdentity();
                    break;
                case cc.Director.PROJECTION_3D:
                    var zeye = _t.getZEye();
                    var matrixPerspective = new cc.math.Matrix4(), matrixLookup = new cc.math.Matrix4();
                    cc.kmGLMatrixMode(cc.KM_GL_PROJECTION);
                    cc.kmGLLoadIdentity();

                    // issue #1334
                    matrixPerspective = cc.math.Matrix4.createPerspectiveProjection(60, size.width / size.height, 0.1, zeye * 2);

                    cc.kmGLMultMatrix(matrixPerspective);

                    cc.kmGLMatrixMode(cc.KM_GL_MODELVIEW);
                    cc.kmGLLoadIdentity();
                    var eye = new cc.math.Vec3(-ox + size.width / 2, -oy + size.height / 2, zeye);
                    var center = new cc.math.Vec3( -ox + size.width / 2, -oy + size.height / 2, 0.0);
                    var up = new cc.math.Vec3( 0.0, 1.0, 0.0);
                    matrixLookup.lookAt(eye, center, up);
                    cc.kmGLMultMatrix(matrixLookup);
                    break;
                case cc.Director.PROJECTION_CUSTOM:
                    if (_t._projectionDelegate)
                        _t._projectionDelegate.updateProjection();
                    break;
                default:
                    cc.log(cc._LogInfos.Director_setProjection);
                    break;
            }
            _t._projection = projection;
            cc.eventManager.dispatchEvent(_t._eventProjectionChanged);
            cc.setProjectionMatrixDirty();
            cc.renderer.childrenOrderDirty = true;
        };

        _p.setDepthTest = function (on) {

            var loc_gl = cc._renderContext;
            if (on) {
                loc_gl.clearDepth(1.0);
                loc_gl.enable(loc_gl.DEPTH_TEST);
                loc_gl.depthFunc(loc_gl.LEQUAL);
                //cc._renderContext.hint(cc._renderContext.PERSPECTIVE_CORRECTION_HINT, cc._renderContext.NICEST);
            } else {
                loc_gl.disable(loc_gl.DEPTH_TEST);
            }
            //cc.checkGLErrorDebug();
        };

        _p.setOpenGLView = function (openGLView) {
            var _t = this;
            // set size
            _t._winSizeInPoints.width = cc._canvas.width;      //_t._openGLView.getDesignResolutionSize();
            _t._winSizeInPoints.height = cc._canvas.height;
            _t._openGLView = openGLView || cc.view;

            // Configuration. Gather GPU info
            var conf = cc.configuration;
            conf.gatherGPUInfo();
            conf.dumpInfo();

            // set size
            //_t._winSizeInPoints = _t._openGLView.getDesignResolutionSize();
            //_t._winSizeInPixels = cc.size(_t._winSizeInPoints.width * _t._contentScaleFactor, _t._winSizeInPoints.height * _t._contentScaleFactor);

            //if (_t._openGLView != openGLView) {
            // because EAGLView is not kind of CCObject

            _t._createStatsLabel();

            //if (_t._openGLView)
            _t.setGLDefaultValues();

            /* if (_t._contentScaleFactor != 1) {
             _t.updateContentScaleFactor();
             }*/

            //}
            if (cc.eventManager)
                cc.eventManager.setEnabled(true);
        };

        _p._clear = function () {
            var gl = cc._renderContext;
            gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);
        };

        _p._beforeVisitScene = function () {
            cc.kmGLPushMatrix();
        };

        _p._afterVisitScene = function () {
            cc.kmGLPopMatrix();
        };

        _p._createStatsLabel = function () {
            var _t = this;
            if (!cc.LabelAtlas){
                _t._createStatsLabelForCanvas();
                return
            }

            if ((cc.Director._fpsImageLoaded == null) || (cc.Director._fpsImageLoaded === false))
                return;

            var texture = new cc.Texture2D();
            texture.initWithElement(cc.Director._fpsImage);
            texture.handleLoadedTexture();

            /*
             We want to use an image which is stored in the file named ccFPSImage.c
             for any design resolutions and all resource resolutions.

             To achieve this,

             Firstly, we need to ignore 'contentScaleFactor' in 'CCAtlasNode' and 'CCLabelAtlas'.
             So I added a new method called 'setIgnoreContentScaleFactor' for 'CCAtlasNode',
             this is not exposed to game developers, it's only used for displaying FPS now.

             Secondly, the size of this image is 480*320, to display the FPS label with correct size,
             a factor of design resolution ratio of 480x320 is also needed.
             */
            var factor = cc.view.getDesignResolutionSize().height / 320.0;
            if (factor === 0)
                factor = _t._winSizeInPoints.height / 320.0;

            var tmpLabel = new cc.LabelAtlas();
            tmpLabel._setIgnoreContentScaleFactor(true);
            tmpLabel.initWithString("00.0", texture, 12, 32, '.');
            tmpLabel.scale = factor;
            _t._FPSLabel = tmpLabel;

            tmpLabel = new cc.LabelAtlas();
            tmpLabel._setIgnoreContentScaleFactor(true);
            tmpLabel.initWithString("0.000", texture, 12, 32, '.');
            tmpLabel.scale = factor;
            _t._SPFLabel = tmpLabel;

            tmpLabel = new cc.LabelAtlas();
            tmpLabel._setIgnoreContentScaleFactor(true);
            tmpLabel.initWithString("000", texture, 12, 32, '.');
            tmpLabel.scale = factor;
            _t._drawsLabel = tmpLabel;

            var locStatsPosition = cc.DIRECTOR_STATS_POSITION;
            _t._drawsLabel.setPosition(locStatsPosition.x, 34 * factor + locStatsPosition.y);
            _t._SPFLabel.setPosition(locStatsPosition.x, 17 * factor + locStatsPosition.y);
            _t._FPSLabel.setPosition(locStatsPosition);
        };

        _p._createStatsLabelForCanvas = function () {
            var _t = this;
            //The original _createStatsLabelForCanvas method
            //Because the referenced by a cc.Director.prototype._createStatsLabel
            var fontSize = 0;
            if (_t._winSizeInPoints.width > _t._winSizeInPoints.height)
                fontSize = 0 | (_t._winSizeInPoints.height / 320 * 24);
            else
                fontSize = 0 | (_t._winSizeInPoints.width / 320 * 24);

            _t._FPSLabel = new cc.LabelTTF("000.0", "Arial", fontSize);
            _t._SPFLabel = new cc.LabelTTF("0.000", "Arial", fontSize);
            _t._drawsLabel = new cc.LabelTTF("0000", "Arial", fontSize);

            var locStatsPosition = cc.DIRECTOR_STATS_POSITION;
            _t._drawsLabel.setPosition(_t._drawsLabel.width / 2 + locStatsPosition.x, _t._drawsLabel.height * 5 / 2 + locStatsPosition.y);
            _t._SPFLabel.setPosition(_t._SPFLabel.width / 2 + locStatsPosition.x, _t._SPFLabel.height * 3 / 2 + locStatsPosition.y);
            _t._FPSLabel.setPosition(_t._FPSLabel.width / 2 + locStatsPosition.x, _t._FPSLabel.height / 2 + locStatsPosition.y);
        };

        _p.convertToGL = function (uiPoint) {
            var transform = new cc.math.Matrix4();
            cc.GLToClipTransform(transform);

            var transformInv = transform.inverse();

            // Calculate z=0 using -> transform*[0, 0, 0, 1]/w
            var zClip = transform.mat[14] / transform.mat[15];
            var glSize = this._openGLView.getDesignResolutionSize();
            var glCoord = new cc.math.Vec3(2.0 * uiPoint.x / glSize.width - 1.0, 1.0 - 2.0 * uiPoint.y / glSize.height, zClip);
            glCoord.transformCoord(transformInv);
            return cc.p(glCoord.x, glCoord.y);
        };

        _p.convertToUI = function (glPoint) {
            var transform = new cc.math.Matrix4();
            cc.GLToClipTransform(transform);

            var clipCoord = new cc.math.Vec3(glPoint.x, glPoint.y, 0.0);
            // Need to calculate the zero depth from the transform.
            clipCoord.transformCoord(transform);

            var glSize = this._openGLView.getDesignResolutionSize();
            return cc.p(glSize.width * (clipCoord.x * 0.5 + 0.5), glSize.height * (-clipCoord.y * 0.5 + 0.5));
        };

        _p.getVisibleSize = function () {
            //if (this._openGLView) {
            return this._openGLView.getVisibleSize();
            //} else {
            //return this.getWinSize();
            //}
        };

        _p.getVisibleOrigin = function () {
            //if (this._openGLView) {
            return this._openGLView.getVisibleOrigin();
            //} else {
            //return cc.p(0,0);
            //}
        };

        _p.getZEye = function () {
            return (this._winSizeInPoints.height / 1.1566 );
        };

        _p.setViewport = function () {
            var view = this._openGLView;
            if (view) {
                var locWinSizeInPoints = this._winSizeInPoints;
                view.setViewPortInPoints(-view._viewPortRect.x/view._scaleX, -view._viewPortRect.y/view._scaleY, locWinSizeInPoints.width, locWinSizeInPoints.height);
            }
        };

        _p.getOpenGLView = function () {
            return this._openGLView;
        };

        _p.getProjection = function () {
            return this._projection;
        };

        _p.setAlphaBlending = function (on) {
            if (on)
                cc.glBlendFunc(cc.BLEND_SRC, cc.BLEND_DST);
            else
                cc.glBlendFunc(cc._renderContext.ONE, cc._renderContext.ZERO);
            //cc.checkGLErrorDebug();
        };

        _p.setGLDefaultValues = function () {
            var _t = this;
            _t.setAlphaBlending(true);
            // XXX: Fix me, should enable/disable depth test according the depth format as cocos2d-iphone did
            // [self setDepthTest: view_.depthFormat];
            _t.setDepthTest(false);
            _t.setProjection(_t._projection);

            // set other opengl default values
            cc._renderContext.clearColor(0.0, 0.0, 0.0, 1.0);
        };
    })();
}
