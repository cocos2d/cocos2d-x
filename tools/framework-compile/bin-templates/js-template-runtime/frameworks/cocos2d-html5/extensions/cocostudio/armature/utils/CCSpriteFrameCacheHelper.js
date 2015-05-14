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
 * ccs.spriteFrameCacheHelper is a singleton object, it's a sprite frame cache helper
 * @class
 * @name ccs.spriteFrameCacheHelper
 */
ccs.spriteFrameCacheHelper = /** @lends ccs.spriteFrameCacheHelper# */ {
    _textureAtlasDic:{},
    _imagePaths:[],

    /**
     * Adds sprite frame from file
     * @param plistPath
     * @param imagePath
     */
    addSpriteFrameFromFile:function (plistPath, imagePath) {
        cc.spriteFrameCache.addSpriteFrames(plistPath, imagePath);
    },

    /**
     * Returns texture atlas with texture.
     * @param texture
     * @returns {*}
     */
    getTextureAtlasWithTexture:function (texture) {
        //todo
        return null;
        var textureName = texture.getName();
        var atlas = this._textureAtlasDic[textureName];
        if (atlas == null) {
            atlas = new cc.TextureAtlas(texture, 20);
            this._textureAtlasDic[textureName] = atlas;
        }
        return atlas;
    },

    /**
     * Clear the sprite frame cache's data.
     */
	clear: function () {
		this._textureAtlasDic = {};
		this._imagePaths = [];
	}
};