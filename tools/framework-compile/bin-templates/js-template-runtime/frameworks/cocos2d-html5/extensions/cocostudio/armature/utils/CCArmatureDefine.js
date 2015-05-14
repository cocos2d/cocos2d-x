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
ccs.VERSION_COMBINED = 0.30;
ccs.VERSION_CHANGE_ROTATION_RANGE = 1.0;
ccs.VERSION_COLOR_READING = 1.1;
ccs.MAX_VERTEXZ_VALUE = 5000000.0;
ccs.ARMATURE_MAX_CHILD = 50.0;
ccs.ARMATURE_MAX_ZORDER = 100;
ccs.ARMATURE_MAX_COUNT = ((ccs.MAX_VERTEXZ_VALUE) / (ccs.ARMATURE_MAX_CHILD) / ccs.ARMATURE_MAX_ZORDER);
ccs.AUTO_ADD_SPRITE_FRAME_NAME_PREFIX = false;
ccs.ENABLE_PHYSICS_CHIPMUNK_DETECT = false;
ccs.ENABLE_PHYSICS_SAVE_CALCULATED_VERTEX = false;

/**
 * Returns the version of Armature.
 * @returns {string}
 */
ccs.armatureVersion = function(){
    return "v1.1.0.0";
};
