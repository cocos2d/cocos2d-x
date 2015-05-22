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
 * The display manager for CocoStudio Armature bone.
 * @Class ccs.DisplayManager
 * @extend cc.Class
 *
 * @param {ccs.Bone} bone The bone for the display manager
 */
ccs.DisplayManager = ccs.Class.extend(/** @lends ccs.DisplayManager */{
    _decoDisplayList:null,
    _currentDecoDisplay:null,
    _displayRenderNode:null,
    _displayIndex: null,
    _forceChangeDisplay:false,
    _bone:null,
    _visible:true,
    _displayType: null,

    ctor:function (bone) {
        this._decoDisplayList = [];
        this._currentDecoDisplay = null;
        this._displayRenderNode = null;
        this._displayIndex = null;
        this._forceChangeDisplay = false;
        this._bone = null;
        this._visible = true;
        this._displayType = ccs.DISPLAY_TYPE_MAX;

        bone && ccs.DisplayManager.prototype.init.call(this, bone);
    },

    /**
     * Initializes a ccs.DisplayManager.
     * @param bone
     * @returns {boolean}
     */
    init:function (bone) {
        this._bone = bone;
        this.initDisplayList(bone.getBoneData());
        return true;
    },

    /**
     * <p>
     *     Add display and use  _DisplayData init the display.                              <br/>
     *     If index already have a display, then replace it.                                <br/>
     *     If index is current display index, then also change display to _index            <br/>
     * </p>
     * @param {ccs.DisplayData|cc.Node} display it include the display information, like DisplayType. If you want to create a sprite display, then create a SpriteDisplayData param
     * @param {Number} index  the index of the display you want to replace or add to. -1 : append display from back
     */
    addDisplay: function (display, index) {
        var decoDisplay, locDisplayList = this._decoDisplayList;
        if( (index >= 0) && (index < locDisplayList.length) )
            decoDisplay = locDisplayList[index];
        else{
            decoDisplay = new ccs.DecorativeDisplay();
            locDisplayList.push(decoDisplay);
        }

        if(display instanceof ccs.DisplayData){
            ccs.displayFactory.addDisplay(this._bone, decoDisplay, display);
            //! if changed display index is current display index, then change current display to the new display
            if(index === this._displayIndex) {
                this._displayIndex = -1;
                this.changeDisplayWithIndex(index, false);
            }
            return;
        }

        var displayData = null;
        if (display instanceof ccs.Skin) {
            display.setBone(this._bone);
            displayData = new ccs.SpriteDisplayData();
            ccs.displayFactory.initSpriteDisplay(this._bone, decoDisplay, display.getDisplayName(), display);

            var spriteDisplayData = decoDisplay.getDisplayData();
            if (spriteDisplayData instanceof ccs.SpriteDisplayData) {
                display.setSkinData(spriteDisplayData.skinData);
                displayData.skinData = spriteDisplayData.skinData;
            } else {
                var find = false;
                for (var i = locDisplayList.length - 2; i >= 0; i--) {
                    var dd = locDisplayList[i];
                    var sdd = dd.getDisplayData();
                    if (sdd instanceof ccs.SpriteDisplayData) {
                        find = true;
                        display.setSkinData(sdd.skinData);
                        displayData.skinData = sdd.skinData;
                        break;
                    }
                }
                if (!find)
                    display.setSkinData(new ccs.BaseData());
            }
        } else if (display instanceof cc.ParticleSystem){
            displayData = new ccs.ParticleDisplayData();
            display.removeFromParent();
            display.cleanup();
            var armature = this._bone.getArmature();
            if (armature)
                display.setParent(armature);
        } else if(display instanceof ccs.Armature) {
            displayData = new ccs.ArmatureDisplayData();
            displayData.displayName = display.getName();
            display.setParentBone(this._bone);
        } else
            displayData = new ccs.DisplayData();
        decoDisplay.setDisplay(display);
        decoDisplay.setDisplayData(displayData);

        //! if changed display index is current display index, then change current display to the new display
        if(index === this._displayIndex) {
            this._displayIndex = -1;
            this.changeDisplayWithIndex(index, false);
        }
    },

    _addDisplayOther:function(decoDisplay,display){
        var displayData = null;
        if (display instanceof ccs.Skin){
            var skin = display;
            skin.setBone(this._bone);
            displayData = new ccs.SpriteDisplayData();
            displayData.displayName = skin.getDisplayName();
            ccs.displayFactory.initSpriteDisplay(this._bone, decoDisplay, skin.getDisplayName(), skin);
            var spriteDisplayData = decoDisplay.getDisplayData();
            if (spriteDisplayData instanceof ccs.SpriteDisplayData)
                skin.setSkinData(spriteDisplayData.skinData);
            else{
                var find = false;
                for (var i = this._decoDisplayList.length - 2; i >= 0; i--) {
                    var dd = this._decoDisplayList[i];
                    var sdd = dd.getDisplayData();
                    if (sdd) {
                        find = true;
                        skin.setSkinData(sdd.skinData);
                        displayData.skinData = sdd.skinData;
                        break;
                    }
                }
                if (!find) {
                    skin.setSkinData(new ccs.BaseData());
                }
                skin.setSkinData(new ccs.BaseData());
            }
                
        }
        else if (display instanceof cc.ParticleSystem){
            displayData = new ccs.ParticleDisplayData();
            displayData.displayName = display._plistFile;
        }
        else if (display instanceof ccs.Armature){
            displayData = new ccs.ArmatureDisplayData();
            displayData.displayName = display.getName();
            display.setParentBone(this._bone);
        }
        else  {
            displayData = new ccs.DisplayData();
        }
        decoDisplay.setDisplay(display);
        decoDisplay.setDisplayData(displayData);
    },

    /**
     * Removes display node from list.
     * @param {Number} index
     */
    removeDisplay:function (index) {
        this._decoDisplayList.splice(index, 1);
        if (index === this._displayIndex) {
            this.setCurrentDecorativeDisplay(null);
            this._displayIndex = -1;
        }
    },

    /**
     * Returns the display node list.
     * @returns {Array}
     */
    getDecorativeDisplayList:function(){
        return this._decoDisplayList;
    },

    /**
     * <p>
     *     Change display by index. You can just use this method to change display in the display list.            <br/>
     *     The display list is just used for this bone, and it is the displays you may use in every frame.         <br/>
     *     Note : if index is the same with prev index, the method will not effect                                 <br/>
     * </p>
     * @param {Number} index  The index of the display you want to change
     * @param {Boolean} force  If true, then force change display to specified display, or current display will set to  display index edit in the flash every key frame.
     */
    changeDisplayWithIndex:function (index, force) {
        if (index >= this._decoDisplayList.length) {
            cc.log("the index value is out of range");
            return;
        }
        this._forceChangeDisplay = force;

        //if index is equal to current display index,then do nothing
        if (this._displayIndex === index)
            return;

        this._displayIndex = index;

        //! If displayIndex < 0, it means you want to hide you display
        if (index < 0) {
            if(this._displayRenderNode) {
                this._displayRenderNode.removeFromParent(true);
                this.setCurrentDecorativeDisplay(null);
            }
            return;
        }
        this.setCurrentDecorativeDisplay(this._decoDisplayList[index]);
    },

    /**
     * Change display by name. @see changeDisplayWithIndex.
     * @param {String} name
     * @param {Boolean} force
     */
    changeDisplayWithName: function (name, force) {
        var locDisplayList = this._decoDisplayList;
        for (var i = 0; i < locDisplayList.length; i++) {
            if (locDisplayList[i].getDisplayData().displayName === name) {
                this.changeDisplayWithIndex(i, force);
                break;
            }
        }
    },

    /**
     * Sets current decorative display.
     * @param {ccs.DecorativeDisplay} decoDisplay
     */
    setCurrentDecorativeDisplay:function (decoDisplay) {
        var locCurrentDecoDisplay = this._currentDecoDisplay;
        if (ccs.ENABLE_PHYSICS_CHIPMUNK_DETECT || ccs.ENABLE_PHYSICS_SAVE_CALCULATED_VERTEX) {
            if (locCurrentDecoDisplay && locCurrentDecoDisplay.getColliderDetector())
                locCurrentDecoDisplay.getColliderDetector().setActive(false);
        }

        this._currentDecoDisplay = decoDisplay;
        locCurrentDecoDisplay = this._currentDecoDisplay;
        if (ccs.ENABLE_PHYSICS_CHIPMUNK_DETECT || ccs.ENABLE_PHYSICS_SAVE_CALCULATED_VERTEX) {
            if (locCurrentDecoDisplay && locCurrentDecoDisplay.getColliderDetector())
                locCurrentDecoDisplay.getColliderDetector().setActive(true);
        }

        var displayRenderNode = (!locCurrentDecoDisplay) ? null : locCurrentDecoDisplay.getDisplay();

        var locRenderNode = this._displayRenderNode, locBone = this._bone;
        if (locRenderNode) {
            if (locRenderNode instanceof ccs.Armature)
                locBone.setChildArmature(null);
            locRenderNode.removeFromParent(true);
        }
        this._displayRenderNode = displayRenderNode;

        if (displayRenderNode) {
            if (displayRenderNode instanceof ccs.Armature) {
                this._bone.setChildArmature(displayRenderNode);
                displayRenderNode.setParentBone(this._bone);
            } else if (displayRenderNode instanceof cc.ParticleSystem) {
                if (displayRenderNode instanceof ccs.Armature) {
                    locBone.setChildArmature(displayRenderNode);
                    displayRenderNode.setParentBone(locBone);
                } else if (displayRenderNode instanceof cc.ParticleSystem)
                    displayRenderNode.resetSystem();
            }

            displayRenderNode.setColor(locBone.getDisplayedColor());
            displayRenderNode.setOpacity(locBone.getDisplayedOpacity());

            this._displayRenderNode.setVisible(this._visible);
            this._displayType = this._currentDecoDisplay.getDisplayData().displayType;
        }else
            this._displayType = ccs.DISPLAY_TYPE_MAX;


        cc.renderer.childrenOrderDirty = true;
    },

    /**
     *  Returns the current display render node.
     * @returns {cc.Node}
     */
    getDisplayRenderNode:function () {
        return this._displayRenderNode;
    },

    /**
     * Returns the type of display render node.
     * @returns {Number}
     */
    getDisplayRenderNodeType:function(){
        return this._displayType;
    },

    /**
     * Returns the index of display render node.
     * @returns {Number}
     */
    getCurrentDisplayIndex:function () {
        return this._displayIndex;
    },

    /**
     * Returns the current decorative display
     * @returns {ccs.DecorativeDisplay}
     */
    getCurrentDecorativeDisplay:function () {
        return this._currentDecoDisplay;
    },

    /**
     * Gets a decorative display by index.
     * @param index
     * @returns {ccs.DecorativeDisplay}
     */
    getDecorativeDisplayByIndex:function (index) {
        return this._decoDisplayList[index];
    },

    /**
     * <p>
     *  Use BoneData to init the display list.
     *  If display is a sprite, and it have texture info in the TextureData, then use TextureData to init the display node's anchor point
     *  If the display is a Armature, then create a new Armature
     * </p>
     * @param {ccs.BoneData} boneData
     */
    initDisplayList:function (boneData) {
        this._decoDisplayList.length = 0;
        if (!boneData)
            return;
        var displayList = boneData.displayDataList, decoList = this._decoDisplayList, locBone = this._bone;
        for (var i = 0; i < displayList.length; i++) {
            var displayData = displayList[i];
            var decoDisplay = new ccs.DecorativeDisplay();
            decoDisplay.setDisplayData(displayData);
            ccs.displayFactory.createDisplay(locBone, decoDisplay);
            decoList.push(decoDisplay);
        }
    },

    /**
     * Check if the position is inside the bone.
     * @param {cc.Point|Number} point
     * @param {Number} [y]
     * @returns {boolean}
     */
    containPoint: function (point, y) {
        if (!this._visible || this._displayIndex < 0)
            return false;

        if (y !== undefined)
            point = cc.p(point, y);

        if(this._currentDecoDisplay.getDisplayData().displayType === ccs.DISPLAY_TYPE_SPRITE){
            /*
             *  First we first check if the point is in the sprite content rect. If false, then we continue to check
             *  the contour point. If this step is also false, then we can say the bone not contain this point.
             *
             */
            var sprite = this._currentDecoDisplay.getDisplay();
            sprite = sprite.getChildByTag(0);
            return ccs.SPRITE_CONTAIN_POINT_WITH_RETURN(sprite, point);
        }
        return false;
    },

    /**
     * <p>
     *  Sets whether the display is visible                                               <br/>
     *  The default value is true, a node is default to visible
     * </p>
     * @param {boolean} visible
     */
    setVisible:function (visible) {
        if (!this._displayRenderNode)
            return;
        this._visible = visible;
        this._displayRenderNode.setVisible(visible);
    },

    /**
     * Determines if the display is visible
     * @returns {boolean} true if the node is visible, false if the node is hidden.
     */
    isVisible:function () {
        return this._visible;
    },

    getContentSize:function () {
        if (!this._displayRenderNode)
            return cc.size(0, 0);
        return this._displayRenderNode.getContentSize();
    },

    getBoundingBox:function () {
        if (!this._displayRenderNode)
            return cc.rect(0, 0, 0, 0);
        return this._displayRenderNode.getBoundingBox();
    },

    getAnchorPoint:function () {
        if (!this._displayRenderNode)
            return  cc.p(0, 0);
        return this._displayRenderNode.getAnchorPoint();
    },

    getAnchorPointInPoints:function () {
        if (!this._displayRenderNode)
            return  cc.p(0, 0);
        return this._displayRenderNode.getAnchorPointInPoints();
    },

    getForceChangeDisplay:function () {
        return this._forceChangeDisplay;
    },

    release:function () {
        this._decoDisplayList = null;
        if (this._displayRenderNode) {
            this._displayRenderNode.removeFromParent(true);
            this._displayRenderNode = null;
        }
    }
});

/**
 * Allocates and initializes a display manager with ccs.Bone.
 * @param {ccs.Bone} bone
 * @returns {ccs.DisplayManager}
 * @deprecated since v3.1, please use new construction instead
 */
ccs.DisplayManager.create = function (bone) {
    return new ccs.DisplayManager(bone);
};