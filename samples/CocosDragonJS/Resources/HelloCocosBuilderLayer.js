/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org
 Copyright (c) 2008-2010 Ricardo Quesada
 Copyright (c) 2011      Zynga Inc.

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

var HelloCocosBuilderLayer = cc.Layer.extend({
    _burstSprite:null,
    _testTitleLableTTF:null,

    openTest:function(ccbFileName, nodeName,nodeLoader){
        /* Create an autorelease CCNodeLoaderLibrary. */
        var ccNodeLoaderLibrary = cc.NodeLoaderLibrary.newDefaultCCNodeLoaderLibrary();

        ccNodeLoaderLibrary.registerCCNodeLoader("TestHeaderLayer", new TestHeaderLayerLoader());
        if(nodeName != null && nodeLoader != null) {
            ccNodeLoaderLibrary.registerCCNodeLoader(nodeName, nodeLoader);
        }

        /* Create an autorelease CCBReader. */
        var ccbReader = new cc.CCBReader(ccNodeLoaderLibrary);

        /* Read a ccbi file. */
        // Load the scene from the ccbi-file, setting this class as
        // the owner will cause lblTestTitle to be set by the CCBReader.
        // lblTestTitle is in the TestHeader.ccbi, which is referenced
        // from each of the test scenes.
        var node = ccbReader.readNodeGraphFromFile("res/ccb/official/pub/", ccbFileName, this);

        this._testTitleLableTTF.setString(ccbFileName);
        var scene = cc.Scene.create();
        if(node != null)
            scene.addChild(node);

        /* Push the new scene with a fancy transition. */
        cc.Director.getInstance().pushScene(cc.TransitionFade.create(0.5, scene, cc.black()));
    },

    onResolveCCBCCMenuItemSelector:function(target,selectorName){
        return null;
    },
    onResolveCCBCCControlSelector:function(target,selectorName){
        if(this == target && "onMenuTestClicked" == selectorName){
            return this.onMenuTestClicked;
        }
        if(this == target && "onSpriteTestClicked" == selectorName){
            return this.onSpriteTestClicked;
        }
        if(this == target && "onButtonTestClicked" == selectorName){
            return this.onButtonTestClicked;
        }
        if(this == target && "onLabelTestClicked" == selectorName){
            return this.onLabelTestClicked;
        }
        if(this == target && "onParticleSystemTestClicked" == selectorName){
            return this.onParticleSystemTestClicked;
        }
        if(this == target && "onScrollViewTestClicked" == selectorName){
            return this.onScrollViewTestClicked;
        }

        return null;
    },

    onAssignCCBMemberVariable:function(target,memberVariableName,node){
        if(target == this && memberVariableName == "mBurstSprite"){
            if(node instanceof  cc.Sprite){
                this._burstSprite = node;
            }
            return true;
        }

        if(target == this && memberVariableName == "mTestTitleLabelTTF"){
            if(node instanceof  cc.LabelTTF){
                this.mTestTitleLabelTTF = node;
            }
            return true;
        }

        return false;
    },
    onNodeLoaded:function(node,nodeLoader){
        var ccRotateBy = cc.RotateBy.create(0.5, 10);
        var ccRepeatForever = cc.RepeatForever.create(ccRotateBy);
        this._burstSprite.runAction(ccRepeatForever);
    },

    onMenuTestClicked:function(sender,controlEvent){
        this.openTest("ccb/MenuTest.ccbi", "MenuTestLayer", MenuTestLayerLoader.loader());
    },

    onSpriteTestClicked:function(sender,controlEvent){
        this.openTest("ccb/SpriteTest.ccbi", "SpriteTestLayer", SpriteTestLayerLoader.loader());
    },
    onButtonTestClicked:function(sender,controlEvent){
        this.openTest("ccb/ButtonTest.ccbi", "ButtonTestLayer", ButtonTestLayerLoader.loader());
    },
    onLabelTestClicked:function(sender,controlEvent){
        this.openTest("ccb/LabelTest.ccbi", "LabelTestLayer", LabelTestLayerLoader.loader());
    },
    onParticleSystemTestClicked:function(sender,controlEvent){
        this.openTest("ccb/ParticleSystemTest.ccbi", "ParticleSystemTestLayer", ParticleSystemTestLayerLoader.loader());
    },
    onScrollViewTestClicked:function(sender,controlEvent){
        this.openTest("ccb/ScrollViewTest.ccbi", "ScrollViewTestLayer", ScrollViewTestLayerLoader.loader());
    }
});

HelloCocosBuilderLayer.create = function(){
    var retLayer = new HelloCocosBuilderLayer();
    if(retLayer && retLayer.init()){
        return retLayer;
    }
    return null;
};

var HelloCocosBuilderLayerLoader = cc.LayerLoader.extend({
    _createCCNode:function(parent,ccbReader){
        return HelloCocosBuilderLayer.create();
    }
});
