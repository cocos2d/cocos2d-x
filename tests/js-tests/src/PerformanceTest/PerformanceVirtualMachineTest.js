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

var VM_TAG_BASE = 2000;
var VM_MAX_NODES = 1500;
var VM_NODES_INCREASE = 100;
var s_nVMCurCase = 0;

////////////////////////////////////////////////////////
//
// VirtualMachineTestMenuLayer
//
// These are some demo test cases about low level JS engine behavior, so in
// some sense this is simliar to PerformanceNodeChildrenTest. This file is
// derived from PerformanceNodeChildrenTest.js actually.
//
// See https://github.com/oupengsoftware/v8/wiki for some of the details (V8)
// under the hood.
// Keyword: hidden class, inline cache, dictionary mode.
//
////////////////////////////////////////////////////////
var VirtualMachineTestMenuLayer = PerformBasicLayer.extend({
    _maxCases:6,
    ctor:function(){
        this._super();
        this._maxCases = (cc._renderType === cc._RENDER_TYPE_CANVAS) ? 6 : 4;
    },
    showCurrentTest:function () {
        var nodes = (this.parent).getQuantityOfNodes();
        var scene = null;
        switch (this._curCase) {
            case 0:
                scene = new SpritesWithManyPropertiesTestScene1();
                break;
            case 1:
                scene = new SpritesWithManyPropertiesTestScene2();
                break;
            case 2:
                scene = new SpritesUndergoneDifferentOperationsTestScene1();
                break;
            case 3:
                scene = new SpritesUndergoneDifferentOperationsTestScene2();
                break;
            case 4:
                scene = new ClonedSpritesTestScene1();
                break;
            case 5:
                scene = new ClonedSpritesTestScene2();
                break;
        }
        s_nVMCurCase = this._curCase;

        if (scene) {
            scene.initWithQuantityOfNodes(nodes);
            cc.director.runScene(scene);
        }
    }
});

////////////////////////////////////////////////////////
//
// VirtualMachineTestMainScene
//
////////////////////////////////////////////////////////
var VirtualMachineTestMainScene = cc.Scene.extend({
    _lastRenderedCount:null,
    _quantityOfNodes:null,
    _currentQuantityOfNodes:null,
    _batchNode:null,

    ctor:function() {
        this._super();
        this.init();
    },

    initWithQuantityOfNodes:function (nodes) {
        this._batchNode = new cc.SpriteBatchNode("Images/grossinis_sister1.png");
        this.addChild(this._batchNode);

        //srand(time());
        var s = cc.director.getWinSize();

        // Title
        var label = new cc.LabelTTF(this.title(), "Arial", 40);
        this.addChild(label, 1);
        label.x = s.width / 2;
        label.y = s.height - 32;
        label.color = cc.color(255, 255, 40);

        // Subtitle
        var strSubTitle = this.subtitle();
        if (strSubTitle.length) {
            var l = new cc.LabelTTF(strSubTitle, "Thonburi", 16);
            this.addChild(l, 1);
            l.x = s.width / 2;
            l.y = s.height - 80;
        }

        this._lastRenderedCount = 0;
        this._currentQuantityOfNodes = 0;
        this._quantityOfNodes = nodes;

        cc.MenuItemFont.setFontSize(65);
        var that = this;
        var decrease = new cc.MenuItemFont(" - ", this.onDecrease, this);
        decrease.color = cc.color(0, 200, 20);
        var increase = new cc.MenuItemFont(" + ", this.onIncrease, this);
        increase.color = cc.color(0, 200, 20);

        var menu = new cc.Menu(decrease, increase);
        menu.alignItemsHorizontally();
        menu.x = s.width / 2;
        menu.y = s.height / 2 + 15;
        this.addChild(menu, 1);

        var infoLabel = new cc.LabelTTF("0 nodes", "Marker Felt", 30);
        infoLabel.color = cc.color(0, 200, 20);
        infoLabel.x = s.width / 2;
        infoLabel.y = s.height / 2 - 15;
        this.addChild(infoLabel, 1, TAG_INFO_LAYER);

        var menu = new VirtualMachineTestMenuLayer(true, 3, s_nVMCurCase);
        this.addChild(menu);

        this.updateQuantityLabel();
        this.updateQuantityOfNodes();
        this.scheduleUpdate();
    },
    title:function () {
        cc.Assert(0);
        // override me
    },
    subtitle:function () {
        cc.Assert(0);
        // override me
    },
    updateQuantityOfNodes:function () {
        cc.Assert(0);
        // override me
    },
    onDecrease:function (sender) {
        this._quantityOfNodes -= VM_NODES_INCREASE;
        if (this._quantityOfNodes < 0) {
            this._quantityOfNodes = 0;
        }

        this.updateQuantityLabel();
        this.updateQuantityOfNodes();
    },
    onIncrease:function (sender) {
        this._quantityOfNodes += VM_NODES_INCREASE;
        if (this._quantityOfNodes > VM_MAX_NODES) {
            this._quantityOfNodes = VM_MAX_NODES
        }

        this.updateQuantityLabel();
        this.updateQuantityOfNodes();
    },
    updateQuantityLabel:function () {
        if (this._quantityOfNodes != this._lastRenderedCount) {
            var infoLabel = this.getChildByTag(TAG_INFO_LAYER);
            var str = this._quantityOfNodes + " nodes";
            infoLabel.setString(str);

            this._lastRenderedCount = this._quantityOfNodes;
        }
    },
    getQuantityOfNodes:function () {
        return this._quantityOfNodes;
    },
    arrayToUpdate:null,
    update:function (dt) {
        if (!this.arrayToUpdate) return;
        for (var i = 0, imax = this.arrayToUpdate.length; i < imax; ++i) {
            var child = this.arrayToUpdate[i];
            if (!(child instanceof SimpleNewtonianSprite) &&
                child instanceof cc.Class) continue; // old cc.clone-ed
                                                     // sprite is not a cc.Class
            for (var j = 0; j < 1000; ++j ) {
                child._velocityX = child._velocityX + dt * child._accelerationX;
                child._velocityY = child._velocityY + dt * child._accelerationY;
                child._positionX = child._positionX + dt * child._velocityX;
                child._positionY = child._positionY + dt * child._velocityY;
            }
        }
    }
});

// Simple sprite extension used for testing the performance of property access.
var SimpleNewtonianSprite = cc.Sprite.extend({
    ctor:function(texture, rect) {
        cc.Sprite.prototype.ctor.call(this);
        // Since jsb doesn't have ._position, in order not to make these 
        // showcase more complicated by introducing fuction calls (because
        // different JS engines have different inlining strategy), we simply
        // introduce ._postionX ._positionY here. These (and update()) really 
        // just represent *heavy property access operation* anyway (they're 
        // otherwise dummy). 
        this._positionX = 0.0;
        this._positionY = 0.0;
        this._velocityX = 0.0;
        this._velocityY = 0.0;
        this._accelerationX = 0.0;
        this._accelerationY = 0.0;

        if(texture && rect)
            this.initWithTexture(texture, rect);
    }
});

////////////////////////////////////////////////////////
//
// SpritesWithManyPropertiesTestScene
//
// Some JS engines (notably, V8) assume that objects with many properties are
// dictionary (c.f CCClass.js) and that makes bad performance. Here we
// simulate a character class with many properties of a character, but 
// otherwise these properties are dummy (and probably doesn't make much 
// sense) in the test of course.
// (TODO: Find a open source real world example, which shouldn't be that hard.
//  :) )
//
////////////////////////////////////////////////////////
var SpriteWithManyProperties = SimpleNewtonianSprite.extend({
    ctor:function(texture, rect) {
        SimpleNewtonianSprite.prototype.ctor.call(this, texture, rect);
        this._name = "";
        this._species = "";
        this._id = -1;
        this._hp = 100;
        this._mp = 100;
        this._exp = 100;
        this._lv = 1;
        this._str = 100;
        this._dex = 100;
        this._int = 100;
        this._luk = 100;
        this._gold = 10000000; // I'm rich.
        this._weight = 100.0;
        this._height = 100.0;
        this._items = [];
        this._spells = [];
        this._dressing = null;
        this._weapon = null;
        this._mission = null;
        this._friends = [];
        this._groups = [];

        this._idleTime = 0.0;
        this._loginTime = 0.0;
        this._isAutoMove = false;
        this._autoMoveTarget = false;
        this._attackMode = 0;
        this._active = true;
        this._canBeAttack = true;
        this._isLocalPlayer = false;
        this._moveType = null;
        this._I_AM_TIRED_OF_COMING_UP_WITH_NEW_PROPERTIES = true;
    }
});

var SpritesWithManyPropertiesTestScene1 = VirtualMachineTestMainScene.extend({
    updateQuantityOfNodes:function () {
        var s = cc.director.getWinSize();

        // increase nodes
        if (this._currentQuantityOfNodes < this._quantityOfNodes) {
            for (var i = 0;
                 i < (this._quantityOfNodes - this._currentQuantityOfNodes);
                 i++) {
                var sprite = 
                    new SpriteWithManyProperties(this._batchNode.texture,
                                                 cc.rect(0, 0, 52, 139));
                this._batchNode.addChild(sprite);
                sprite.x = Math.random() * s.width;
                sprite.y = Math.random() * s.height;
            }
        }

        // decrease nodes
        else if (this._currentQuantityOfNodes > this._quantityOfNodes) {
            for (var i = 0;
                 i < (this._currentQuantityOfNodes - this._quantityOfNodes);
                 i++) {
                var index = this._currentQuantityOfNodes - i - 1;
                this._batchNode.removeChildAtIndex(index, true);
            }
        }

        this._currentQuantityOfNodes = this._quantityOfNodes;
    },
    title:function () {
        return "A1 - Sprites Have Many Properties";
    },
    subtitle:function () {
        return "See fps (and source code of this test).";
    }
});

var SpritesWithManyPropertiesTestScene2 = 
    SpritesWithManyPropertiesTestScene1.extend({
    updateQuantityOfNodes:function () {
        this._super();
        var arrayToUpdate = this._batchNode.children;
        for (var i = 0, imax = arrayToUpdate.length; i < imax; ++i)
            arrayToUpdate[i].visible = false;
        this.arrayToUpdate = arrayToUpdate;
    },
    title:function () {
        return "A2 - Sprites Have Many Properties";
    },
    subtitle:function () {
        return "No draw(). update() does heavy calculations.";
    }
});

////////////////////////////////////////////////////////
//
// SpritesUndergoneDifferentOperationsTestScene
//
// If properties in use are not initilized on each instance, a combinarial
// explosion of hidden classes have to be created for each possible
// permutation of operations. This increases inline cache size and
// constitutes significant performance penalty.
//
////////////////////////////////////////////////////////

var SpritesUndergoneDifferentOperationsTestScene1 = VirtualMachineTestMainScene.extend({
    // Adpated from http://codereview.stackexchange.com/a/7025
    possibleOperationSeries:(function permutations(array){
        var fn = function(active, rest, a) {
            if (!active.length && !rest.length) {
                a.push([]);
                return;
            }
            if (!rest.length) {
                if (active.length === 1) {
                    a.push(active);
                    return;
                }

                var fac = 1;
                for (var i = active.length; i > 0; --i) fac = fac * i;
                for (var i = 0; i < fac; ++i) {
                    var choice_num = i;
                    var choice = [];
                    for (var j = 1; j < active.length + 1; ++j) {
                        choice.unshift(choice_num % j);
                        choice_num = (choice_num - choice_num % j) / j;
                    }

                    var to_choose_from = active.slice(0);
                    var new_permutation = [];
                    for (var k = 0; k < active.length; ++k)
                        new_permutation.push(to_choose_from.
                                             splice(choice[k], 1)[0]);
                    a.push(new_permutation);
                }
            } else {
                fn(active.concat([rest[0]]), rest.slice(1), a);
                fn(active, rest.slice(1), a);
            }
            return a;
        };
        return fn([], array, []);
    })([
        function() { this.children; }, // appends ._children
        function() { this.tag = cc.NODE_TAG_INVALID; }, // appends .tag
        function() { this.setParent(null); }, // appends ._parent
        function() { this.zIndex = 0; }, // appends ._zOrder
        function() { this.rotation = 0; }, // appends ._rotationX/Y
        function() { this.visible = true; }, // appends ._visible
        function() { this.onEnter(); } // appends ._running
    ]),
    updateQuantityOfNodes:function () {
        var s = cc.director.getWinSize();

        // increase nodes
        if (this._currentQuantityOfNodes < this._quantityOfNodes) {
            for (var i = 0;
                 i < (this._quantityOfNodes - this._currentQuantityOfNodes);
                 i++) {
                var sprite = 
                    new SimpleNewtonianSprite(this._batchNode.texture,
                                              cc.rect(0, 0, 52, 139));
                var series = this.possibleOperationSeries[i];
                for (var op = 0, opmax = series.length; op < opmax; ++op)
                    series[op].call(sprite);

                this._batchNode.addChild(sprite);
                sprite.x = Math.random() * s.width;
                sprite.y = Math.random() * s.height;
            }
        }

        // decrease nodes
        else if (this._currentQuantityOfNodes > this._quantityOfNodes) {
            for (var i = 0;
                 i < (this._currentQuantityOfNodes - this._quantityOfNodes);
                 i++) {
                var index = this._currentQuantityOfNodes - i - 1;
                this._batchNode.removeChildAtIndex(index, true);
            }
        }

        this._currentQuantityOfNodes = this._quantityOfNodes;
    },
    title:function () {
        return "B1 - Sprites Undergone Different Op. Order";
    },
    subtitle:function () {
        return "See fps (and source code of this test).";
    }
});

var SpritesUndergoneDifferentOperationsTestScene2 = 
    SpritesUndergoneDifferentOperationsTestScene1.extend({
    // This looks exactly like the one on ManyPropertiesTestScene2, but
    // we can't just do 
    // 'updateQuantityOfNodes: SpritesWithManyPropertiesTestScene2.prototype.updateQuantityOfNodes'
    // here becasue this._super() is different!
    updateQuantityOfNodes:function () {
        this._super();
        var arrayToUpdate = this._batchNode.children;
        for (var i = 0, imax = arrayToUpdate.length; i < imax; ++i)
            arrayToUpdate[i].visible = false;
        this.arrayToUpdate = arrayToUpdate;
    },
    title:function () {
        return "B2 - Sprites Undergone Different Op. Order";
    },
    subtitle:function () {
        return "No draw(). update() does heavy calculations.";
    }
});

////////////////////////////////////////////////////////
//
// ClonedSpritesTestScene
//
// cc.clone has to be written carefully or cloned objects all go to dictionary
// mode.
//
////////////////////////////////////////////////////////
var ClonedSpritesTestScene1 = VirtualMachineTestMainScene.extend({
    template:null,
    updateQuantityOfNodes:function () {
        if (!this.template)
            this.template = 
            new SimpleNewtonianSprite(this._batchNode.texture,
                                      cc.rect(0, 0, 52, 139));
        var s = cc.director.getWinSize();

        // increase nodes
        if (this._currentQuantityOfNodes < this._quantityOfNodes) {
            for (var i = 0; 
                 i < (this._quantityOfNodes - this._currentQuantityOfNodes);
                 i++) {
                var sprite = cc.clone(this.template);
                sprite.setParent(null); // old cc.clone copies null as {}...

                // cc.SpriteBatchNode doesn't support adding non-cc.Sprite child
                // and hence incompatible with old cc.clone. We add the sprite 
                // to the scene directly.
                this.addChild(sprite, -1); // zOrder has to be less than 0 or it
                                           // overlaps the menu.
                sprite.x = Math.random() * s.width;
                sprite.y = Math.random() * s.height;
            }
        }

        // decrease nodes
        else if (this._currentQuantityOfNodes > this._quantityOfNodes) {
            var children = this.children;
            var lastChildToRemove = children.length;
            for (var i = children.length - 1; i >= 0; --i) {
                var child = children[i];
                if (child instanceof SimpleNewtonianSprite || 
                    !(child instanceof cc.Class)) { // old cc.clone-ed
                                                    // sprite is not a cc.Class
                    lastChildToRemove = i;
                    break;
                }
            }

            for (var i = 0;
                 i < (this._currentQuantityOfNodes - this._quantityOfNodes);
                 i++) {
                var index = lastChildToRemove - i;
                this.removeChild(children[index], true);
            }
        }

        this._currentQuantityOfNodes = this._quantityOfNodes;
    },
    title:function () {
        return "C1 - Cloned Sprites";
    },
    subtitle:function () {
        return "See fps (and source code of this test).";
    }
});

var ClonedSpritesTestScene2 = ClonedSpritesTestScene1.extend({
    updateQuantityOfNodes:function () {
        if (!this.template) {
            this.template = 
                new SimpleNewtonianSprite(this._batchNode.texture,
                                          cc.rect(0, 0, 52, 139));
            this.template.visible = false;
        }
        this._super();
        this.arrayToUpdate = this.children;
    },
    title:function () {
        return "C2 - Cloned Sprites";
    },
    subtitle:function () {
        return "No draw(). update() does heavy calculations.";
    }
});

function runVirtualMachineTest() {
    var scene = new SpritesWithManyPropertiesTestScene1();
    scene.initWithQuantityOfNodes(VM_NODES_INCREASE);
    cc.director.runScene(scene);
}
