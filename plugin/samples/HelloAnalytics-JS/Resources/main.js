/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org

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

// boot code needed for cocos2d + JS bindings.
// Not needed by cocos2d-html5
require("jsb_cocos2d.js");
cc.log("main.js12222");
require("jsb_pluginx.js");
cc.log("main.js133333");
var appFiles = [
    'src/resource.js',
    'src/myApp.js'
];
cc.log("main.js33344441");
cc.dumpConfig();

for( var i=0; i < appFiles.length; i++) {
    require( appFiles[i] );
}
cc.log("main.js14555555");
var director = cc.Director.getInstance();
director.setDisplayStats(true);
cc.log("main.js666666661");
// set FPS. the default value is 1.0/60 if you don't call this
director.setAnimationInterval(1.0 / 60);
cc.log("main.js177777");
// create a scene. it's an autorelease object
var myScene = new MyScene();
cc.log("main.js18888");
// run
director.runWithScene(myScene);
cc.log("main.js199999");
