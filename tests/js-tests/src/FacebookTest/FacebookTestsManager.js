/****************************************************************************
 Copyright (c) 2014 Chukong Technologies Inc.

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

var facebook_is_canvas = false;
var arrayOfFacebookTest = [
    FacebookShareTest,
    FacebookUserTest
];

var __sceneIdx = -1;

var nextFacebookTest = function () {
    __sceneIdx++;
    __sceneIdx = __sceneIdx % arrayOfFacebookTest.length;
    return new arrayOfFacebookTest[__sceneIdx]();
};

FacebookTestScene = TestScene.extend({
    runThisTest:function (num) {
        var self = this;
        __sceneIdx = (num || num == 0) ? (num - 1) : -1;

        if(!cc.sys.isNative) {   //browser
            cc.loader.loadJs('', [
                "../../web/external/pluginx/platform/facebook_sdk.js",
                "../../web/external/pluginx/platform/facebook.js"
            ], function() {
                var layer = nextFacebookTest();
                self.addChild(layer);
                director.runScene(self);
            });
        }
        else {
            var layer = nextFacebookTest();
            self.addChild(layer);
            director.runScene(self);
        }
    }
});