/****************************************************************************
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

(function() {
    cc.Scale9Sprite.WebGLRenderCmd = function (renderable) {
        cc.Node.WebGLRenderCmd.call(this, renderable);
        this._cachedParent = null;
        this._cacheDirty = false;
    };

    var proto = cc.Scale9Sprite.WebGLRenderCmd.prototype = Object.create(cc.Node.WebGLRenderCmd.prototype);
    proto.constructor = cc.Scale9Sprite.WebGLRenderCmd;

    proto.visit = function(parentCmd){
        var node = this._node;
        if(!node._visible)
            return;

        if (node._positionsAreDirty) {
            node._updatePositions();
            node._positionsAreDirty = false;
            node._scale9Dirty = true;
        }
        cc.Node.WebGLRenderCmd.prototype.visit.call(this, parentCmd);
    };

    proto.transform = function(parentCmd, recursive){
        var node = this._node;
        cc.Node.WebGLRenderCmd.prototype.transform.call(this, parentCmd, recursive);
        if (node._positionsAreDirty) {
            node._updatePositions();
            node._positionsAreDirty = false;
            node._scale9Dirty = true;
        }
    };

    proto._updateDisplayColor = function(parentColor){
        cc.Node.WebGLRenderCmd.prototype._updateDisplayColor.call(this, parentColor);

        var scale9Image = this._node._scale9Image;
        if(scale9Image){
            var scaleChildren = scale9Image.getChildren();
            for (var i = 0; i < scaleChildren.length; i++) {
                var selChild = scaleChildren[i];
                if (selChild){
                    selChild._renderCmd._updateDisplayColor(parentColor);
                    selChild._renderCmd._updateColor();
                }
            }
        }
    };

    proto._updateDisplayOpacity = function(parentColor){
        cc.Node.WebGLRenderCmd.prototype._updateDisplayOpacity.call(this, parentColor);

        var scale9Image = this._node._scale9Image;
        if(scale9Image){
            var scaleChildren = scale9Image.getChildren();
            for (var i = 0; i < scaleChildren.length; i++) {
                var selChild = scaleChildren[i];
                if (selChild){
                    selChild._renderCmd._updateDisplayOpacity(parentColor);
                    selChild._renderCmd._updateColor();
                }
            }
        }
    };

    proto.setState = function (state) {
        var scale9Image = this._node._scale9Image;
        if(scale9Image === null)
            return;
        if (state === cc.Scale9Sprite.state.NORMAL) {
            scale9Image.setShaderProgram(cc.shaderCache.programForKey(cc.SHADER_POSITION_TEXTURECOLOR));
        } else if (state === cc.Scale9Sprite.state.GRAY) {
            scale9Image.setShaderProgram(cc.Scale9Sprite.WebGLRenderCmd._getGrayShaderProgram());
        }
    };

    cc.Scale9Sprite.WebGLRenderCmd._grayShaderProgram = null;
    cc.Scale9Sprite.WebGLRenderCmd._getGrayShaderProgram = function(){
        var grayShader = cc.Scale9Sprite.WebGLRenderCmd._grayShaderProgram;
        if(grayShader)
            return grayShader;

        grayShader = new cc.GLProgram();
        grayShader.initWithVertexShaderByteArray(cc.SHADER_POSITION_TEXTURE_COLOR_VERT, cc.Scale9Sprite.WebGLRenderCmd._grayShaderFragment);
        grayShader.addAttribute(cc.ATTRIBUTE_NAME_POSITION, cc.VERTEX_ATTRIB_POSITION);
        grayShader.addAttribute(cc.ATTRIBUTE_NAME_COLOR, cc.VERTEX_ATTRIB_COLOR);
        grayShader.addAttribute(cc.ATTRIBUTE_NAME_TEX_COORD, cc.VERTEX_ATTRIB_TEX_COORDS);
        grayShader.link();
        grayShader.updateUniforms();

        cc.Scale9Sprite.WebGLRenderCmd._grayShaderProgram = grayShader;
        return grayShader;
    };

    cc.Scale9Sprite.WebGLRenderCmd._grayShaderFragment =
        "precision lowp float;\n"
        + "varying vec4 v_fragmentColor; \n"
        + "varying vec2 v_texCoord; \n"
        + "void main() \n"
        + "{ \n"
        + "    vec4 c = texture2D(CC_Texture0, v_texCoord); \n"
        + "    gl_FragColor.xyz = vec3(0.2126*c.r + 0.7152*c.g + 0.0722*c.b); \n"
        +"     gl_FragColor.w = c.w ; \n"
        + "}";
})();