/*
 * Copyright (c) 2013-2016 Chukong Technologies Inc.
 * Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

//
// JavaScript Bindings helper file
//

// DO NOT ALTER THE ORDER
require('script/jsb_cocos2d_constants.js');
require('script/jsb_cocos2d.js');
require('script/jsb_common.js');
require('script/jsb_property_impls.js');
require('script/jsb_property_apis.js');
require('script/jsb_create_apis.js');

if (window.ccs) {
    require('script/studio/jsb_studio_boot.js');
    require('script/studio/jsb_cocos2d_studio.js');
    require('script/studio/jsb_studio_property_apis.js');
    require('script/studio/jsb_studio_create_apis.js');

    require('script/studio/jsb_studio_load.js');
    require('script/studio/parsers/action-1.x.js');
    require('script/studio/parsers/action-2.x.js');
    require('script/studio/parsers/scene-1.x.js');
    require('script/studio/parsers/timelineParser-1.x.js');
    require('script/studio/parsers/timelineParser-2.x.js');
    require('script/studio/parsers/uiParser-1.x.js');
    require('script/studio/parsers/compatible.js');
}

if (window.ccui) {
    require('script/ccui/jsb_cocos2d_ui.js');
    require('script/ccui/jsb_ccui_property_impls.js');
    require('script/ccui/jsb_ccui_property_apis.js');
    require('script/ccui/jsb_ccui_create_apis.js');
    require('script/ccui/jsb_ccui_deprecated.js');
}

if (cc.ControlButton) {
    require('script/extension/jsb_cocos2d_extension.js');
    require('script/extension/jsb_ext_property_apis.js');
    require('script/extension/jsb_ext_create_apis.js');
}

if (cc.PhysicsSprite) {
    require('script/physicsSprite/jsb_physicsSprite.js');
}

if (window.cp) {
    // chipmunk
    require('script/chipmunk/jsb_chipmunk_constants.js');
    require('script/chipmunk/jsb_chipmunk.js');
}

require('script/jsb_opengl_constants.js');
require('script/jsb_opengl.js');

if (cc.BuilderAnimationManager) {
    require('script/jsb_cocosbuilder.js');
}

if (jsb.fileUtils.isFileExist('jsb_pluginx.js') || jsb.fileUtils.isFileExist('jsb_pluginx.jsc')) {
    if (cc.sys.os == cc.sys.OS_IOS || cc.sys.os == cc.sys.OS_ANDROID) {
        require('jsb_pluginx.js');
    }
}

if (window.sp) {
    require('script/jsb_spine.js');
}

if (jsb.Sprite3D){
    require('script/3d/jsb_cocos2d_3d.js');
}

if (jsb.ParticleSystem3D) {
    require('script/3d/jsb_cocos2d_3d_ext.js');
}

if (jsb.Physics3DObject) {
    require("script/physics3d/jsb_physics3d.js");
}

if (jsb.NavMeshAgent) {
    require("script/navmesh/jsb_navmesh.js");
}

require("script/jsb_audioengine.js");

require('script/jsb_loaders.js');
require('script/jsb_pool.js');
require('script/jsb_deprecated.js');
