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

var TAG_BASE = 2000;
var MAX_NODES = 1500;
var NODES_INCREASE = 50;
var s_nCurCase = 0;

////////////////////////////////////////////////////////
//
// NodeChildrenMenuLayer
//
////////////////////////////////////////////////////////
var NodeChildrenMenuLayer = PerformBasicLayer.extend({
    _maxCases:4,
    showCurrentTest:function () {
        var nodes = (this.parent).getQuantityOfNodes();
        var scene = null;
        switch (this._curCase) {
            case 0:
                scene = new IterateSpriteSheetCArray();
                break;
            case 1:
                scene = new AddSpriteSheet();
                break;
            case 2:
                scene = new RemoveSpriteSheet();
                break;
            case 3:
                scene = new ReorderSpriteSheet();
                break;
        }
        s_nCurCase = this._curCase;

        if (scene) {
            scene.initWithQuantityOfNodes(nodes);
            cc.director.runScene(scene);
        }
    }
});

////////////////////////////////////////////////////////
//
// NodeChildrenMainScene
//
////////////////////////////////////////////////////////
var NodeChildrenMainScene = cc.Scene.extend({
    _lastRenderedCount:null,
    _quantityOfNodes:null,
    _currentQuantityOfNodes:null,

    ctor:function() {
        this._super();
        this.init();
    },

    initWithQuantityOfNodes:function (nodes) {
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

        var menu = new NodeChildrenMenuLayer(true, 4, s_nCurCase);
        this.addChild(menu);

        this.updateQuantityLabel();
        this.updateQuantityOfNodes();
    },
    title:function () {
        return "No title";
    },
    subtitle:function () {
        return "";
    },
    updateQuantityOfNodes:function () {

    },
    onDecrease:function (sender) {
        this._quantityOfNodes -= NODES_INCREASE;
        if (this._quantityOfNodes < 0) {
            this._quantityOfNodes = 0;
        }

        this.updateQuantityLabel();
        this.updateQuantityOfNodes();
    },
    onIncrease:function (sender) {
        this._quantityOfNodes += NODES_INCREASE;
        if (this._quantityOfNodes > MAX_NODES) {
            this._quantityOfNodes = MAX_NODES
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
    }
});

////////////////////////////////////////////////////////
//
// IterateSpriteSheet
//
////////////////////////////////////////////////////////
var IterateSpriteSheet = NodeChildrenMainScene.extend({
    _batchNode:null,
    _profilingTimer:null,
    ctor:function () {
        this._super();
        if (cc.ENABLE_PROFILERS) {
            this._profilingTimer = new cc.ProfilingTimer();
        }
    },
    updateQuantityOfNodes:function () {
        var s = cc.director.getWinSize();

        // increase nodes
        if (this._currentQuantityOfNodes < this._quantityOfNodes) {
            for (var i = 0; i < (this._quantityOfNodes - this._currentQuantityOfNodes); i++) {
                var sprite = new cc.Sprite(this._batchNode.texture, cc.rect(0, 0, 32, 32));
                this._batchNode.addChild(sprite);
                sprite.x = Math.random() * s.width;
                sprite.y = Math.random() * s.height;
            }
        }

        // decrease nodes
        else if (this._currentQuantityOfNodes > this._quantityOfNodes) {
            for (var i = 0; i < (this._currentQuantityOfNodes - this._quantityOfNodes); i++) {
                var index = this._currentQuantityOfNodes - i - 1;
                this._batchNode.removeChildAtIndex(index, true);
            }
        }

        this._currentQuantityOfNodes = this._quantityOfNodes;
    },
    initWithQuantityOfNodes:function (nodes) {
        this._batchNode = new cc.SpriteBatchNode("Images/spritesheet1.png");
        this.addChild(this._batchNode);

        this._super(nodes);

        if (cc.ENABLE_PROFILERS) {
            this._profilingTimer = cc.Profiler.timerWithName(this.profilerName(), this);
        }
        this.scheduleUpdate();
    },
    update:function (dt) {
    },
    profilerName:function () {
        return "none";
    }
});

////////////////////////////////////////////////////////
//
// IterateSpriteSheetFastEnum
//
////////////////////////////////////////////////////////
var IterateSpriteSheetFastEnum = IterateSpriteSheet.extend({
    update:function (dt) {
        // iterate using fast enumeration protocol
        var children = this._batchNode.children;

        if (cc.ENABLE_PROFILERS) {
            cc.ProfilingBeginTimingBlock(this._profilingTimer);
        }

        for (var i = 0; i < children.length; i++) {
            var sprite = children[i];
            sprite.visible = false;
        }

        if (cc.ENABLE_PROFILERS) {
            cc.ProfilingEndTimingBlock(this._profilingTimer);
        }
    },

    title:function () {
        return "A - Iterate SpriteSheet";
    },
    subtitle:function () {
        return "Iterate children using Fast Enum API. See console";
    },
    profilerName:function () {
        return "iter fast enum";
    }
});

////////////////////////////////////////////////////////
//
// IterateSpriteSheetCArray
//
////////////////////////////////////////////////////////
var IterateSpriteSheetCArray = IterateSpriteSheet.extend({
    update:function (dt) {
        // iterate using fast enumeration protocol
        var children = this._batchNode.children;

        if (cc.ENABLE_PROFILERS) {
            cc.ProfilingBeginTimingBlock(this._profilingTimer);
        }
        for (var i = 0; i < children.length; i++) {
            var sprite = children[i];
            sprite.visible = false;
        }

        if (cc.ENABLE_PROFILERS) {
            cc.ProfilingEndTimingBlock(this._profilingTimer);
        }
    },

    title:function () {
        return "B - Iterate SpriteSheet";
    },
    subtitle:function () {
        return "Iterate children using Array API. See console";
    },
    profilerName:function () {
        return "iter c-array";
    }
});

////////////////////////////////////////////////////////
//
// AddRemoveSpriteSheet
//
////////////////////////////////////////////////////////
var AddRemoveSpriteSheet = NodeChildrenMainScene.extend({
    _batchNode:null,
    ctor:function () {
        this._super();
        if (cc.ENABLE_PROFILERS) {
            this._profilingTimer = new cc.ProfilingTimer();
        }
    },
    updateQuantityOfNodes:function () {
        var s = cc.director.getWinSize();

        // increase nodes
        if (this._currentQuantityOfNodes < this._quantityOfNodes) {
            for (var i = 0; i < (this._quantityOfNodes - this._currentQuantityOfNodes); i++) {
                var sprite = new cc.Sprite(this._batchNode.texture, cc.rect(0, 0, 32, 32));
                this._batchNode.addChild(sprite);
                sprite.x = Math.random() * s.width;
                sprite.y = Math.random() * s.height;
                sprite.visible = false;
            }
        }
        // decrease nodes
        else if (this._currentQuantityOfNodes > this._quantityOfNodes) {
            for (var i = 0; i < (this._currentQuantityOfNodes - this._quantityOfNodes); i++) {
                var index = this._currentQuantityOfNodes - i - 1;
                this._batchNode.removeChildAtIndex(index, true);
            }
        }

        this._currentQuantityOfNodes = this._quantityOfNodes;
    },
    initWithQuantityOfNodes:function (nodes) {
        this._batchNode = new cc.SpriteBatchNode("Images/spritesheet1.png");
        this.addChild(this._batchNode);

        this._super(nodes);

        if (cc.ENABLE_PROFILERS) {
            this._profilingTimer = cc.Profiler.timerWithName(this.profilerName(), this);
        }

        this.scheduleUpdate();
    },
    update:function (dt) {
    },
    profilerName:function () {
        return "none";
    }
});

////////////////////////////////////////////////////////
//
// AddSpriteSheet
//
////////////////////////////////////////////////////////
var AddSpriteSheet = AddRemoveSpriteSheet.extend({
        update:function (dt) {
            // reset seed
            //srandom(0);

            // 15 percent
            var totalToAdd = this._currentQuantityOfNodes * 0.15;

            if (totalToAdd > 0) {
                var sprites = [];
                var zs = [];

                // Don't include the sprite creation time and random as part of the profiling
                for (var i = 0; i < totalToAdd; i++) {
                    var sprite = new cc.Sprite(this._batchNode.texture, cc.rect(0, 0, 32, 32));
                    sprites.push(sprite);
                    zs[i] = (Math.random()*2-1) * 50;
                }

                // add them with random Z (very important!)
                if (cc.ENABLE_PROFILERS)
                    cc.ProfilingBeginTimingBlock(this._profilingTimer);
            }

            for (var i = 0; i < totalToAdd; i++) {
                this._batchNode.addChild(sprites[i], zs[i], TAG_BASE + i);
            }

            if (cc.ENABLE_PROFILERS) {
                cc.ProfilingEndTimingBlock(this._profilingTimer);
            }

            // remove them
            for (var i = 0; i < totalToAdd; i++) {
                this._batchNode.removeChildByTag(TAG_BASE + i, true);
            }

            delete zs;

        },
        title:function () {
            return "C - Add to spritesheet";
        },
        subtitle:function () {
            return "Adds %10 of total sprites with random z. See console";
        },
        profilerName:function () {
            return "add sprites";
        }
    })
    ;

////////////////////////////////////////////////////////
//
// RemoveSpriteSheet
//
////////////////////////////////////////////////////////
var RemoveSpriteSheet = AddRemoveSpriteSheet.extend({
    update:function (dt) {
        //srandom(0);

        // 15 percent
        var totalToAdd = this._currentQuantityOfNodes * 0.15;

        if (totalToAdd > 0) {
            var sprites = [];

            // Don't include the sprite creation time as part of the profiling
            for (var i = 0; i < totalToAdd; i++) {
                var sprite = new cc.Sprite(this._batchNode.texture, cc.rect(0, 0, 32, 32));
                sprites.push(sprite);
            }

            // add them with random Z (very important!)
            for (var i = 0; i < totalToAdd; i++) {
                this._batchNode.addChild(sprites[i], (Math.random()*2-1) * 50, TAG_BASE + i);
            }

            // remove them
            if (cc.ENABLE_PROFILERS) {
                cc.ProfilingBeginTimingBlock(this._profilingTimer);
            }

            for (var i = 0; i < totalToAdd; i++) {
                this._batchNode.removeChildByTag(TAG_BASE + i, true);
            }

            if (cc.ENABLE_PROFILERS) {
                cc.ProfilingEndTimingBlock(this._profilingTimer);
            }
        }
    },
    title:function () {
        return "D - Del from spritesheet";
    },
    subtitle:function () {
        return "Remove %10 of total sprites placed randomly. See console";
    },
    profilerName:function () {
        return "remove sprites";
    }
});

////////////////////////////////////////////////////////
//
// ReorderSpriteSheet
//
////////////////////////////////////////////////////////
var ReorderSpriteSheet = AddRemoveSpriteSheet.extend({

    update:function (dt) {
        //srandom(0);

        // 15 percent
        var totalToAdd = this._currentQuantityOfNodes * 0.15;

        if (totalToAdd > 0) {
            var sprites = [];

            // Don't include the sprite creation time as part of the profiling
            for (var i = 0; i < totalToAdd; i++) {
                var sprite = new cc.Sprite(this._batchNode.texture, cc.rect(0, 0, 32, 32));
                sprites.push(sprite);
            }

            // add them with random Z (very important!)
            for (var i = 0; i < totalToAdd; i++) {
                this._batchNode.addChild(sprites[i], (Math.random()*2-1) * 50, TAG_BASE + i);
            }

            //		[this._batchNode sortAllChildren];

            // reorder them
            if (cc.ENABLE_PROFILERS) {
                cc.ProfilingBeginTimingBlock(this._profilingTimer);
            }

            for (var i = 0; i < totalToAdd; i++) {
                var node = this._batchNode.children[i];
                ;
                this._batchNode.reorderChild(node, (Math.random()*2-1) * 50);
            }
            if (cc.ENABLE_PROFILERS) {
                cc.ProfilingEndTimingBlock(this._profilingTimer);
            }
        }


        // remove them
        for (var i = 0; i < totalToAdd; i++) {
            this._batchNode.removeChildByTag(TAG_BASE + i, true);
        }

    },

    title:function () {
        return "E - Reorder from spritesheet";
    },
    subtitle:function () {
        return "Reorder %10 of total sprites placed randomly. See console";
    },
    profilerName:function () {
        return "reorder sprites";
    }
});

function runNodeChildrenTest() {
    var scene = new IterateSpriteSheetCArray();
    scene.initWithQuantityOfNodes(NODES_INCREASE);
    cc.director.runScene(scene);
}
