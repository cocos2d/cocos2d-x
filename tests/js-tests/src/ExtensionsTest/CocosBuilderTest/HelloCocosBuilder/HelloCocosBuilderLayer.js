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

cc.BuilderReader.registerController("HelloCocosBuilderLayer", {
    _openTest : function(ccbFileName) {
        if (cc.sys.isNative)
        {
            cc.BuilderReader.setResourcePath("res/resjs/");
        }
        else
        {
            cc.BuilderReader.setResourcePath(ccbjs);
        }
        var node = cc.BuilderReader.load(ccbFileName, this);

        this["mTestTitleLabelTTF"].setString(ccbFileName);
        var scene = new cc.Scene();
        if(node != null)
            scene.addChild(node);

        /* Push the new scene with a fancy transition. */
        cc.director.pushScene(new cc.TransitionFade(0.5, scene, cc.color(0, 0, 0)));
    },
    
    "onMenuTestClicked" : function() {
        this._openTest(ccbjs + "ccb/ccb/TestMenus.ccbi");
    },
    
    "onSpriteTestClicked" : function() {
        this._openTest(ccbjs + "ccb/ccb/TestSprites.ccbi");
    },
    
    "onButtonTestClicked" : function() {
        this._openTest(ccbjs + "ccb/ccb/TestButtons.ccbi");
    },
    
    "onAnimationsTestClicked" : function() {
        this._openTest(ccbjs + "ccb/ccb/TestAnimations.ccbi");
    },
    
    "onParticleSystemTestClicked" : function() {
        this._openTest(ccbjs + "ccb/ccb/TestParticleSystems.ccbi");
    },
    
    "onScrollViewTestClicked" : function() {
        this._openTest(ccbjs + "ccb/ccb/TestScrollViews.ccbi");
    },
    
    "onTimelineCallbackSoundClicked" : function() {
        this._openTest(ccbjs + "ccb/ccb/TestTimelineCallback.ccbi");
    }
});

