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
ccs.displayFactory = {
    addDisplay: function (bone, decoDisplay, displayData) {
        switch (displayData.displayType) {
            case ccs.DISPLAY_TYPE_SPRITE:
                this.addSpriteDisplay(bone, decoDisplay, displayData);
                break;
            case ccs.DISPLAY_TYPE_PARTICLE:
                this.addParticleDisplay(bone, decoDisplay, displayData);
                break;
            case ccs.DISPLAY_TYPE_ARMATURE:
                this.addArmatureDisplay(bone, decoDisplay, displayData);
                break;
            default:
                break;
        }
    },

    createDisplay: function (bone, decoDisplay) {
        switch (decoDisplay.getDisplayData().displayType) {
            case ccs.DISPLAY_TYPE_SPRITE:
                this.createSpriteDisplay(bone, decoDisplay);
                break;
            case ccs.DISPLAY_TYPE_PARTICLE:
                this.createParticleDisplay(bone, decoDisplay);
                break;
            case ccs.DISPLAY_TYPE_ARMATURE:
                this.createArmatureDisplay(bone, decoDisplay);
                break;
            default:
                break;
        }
    },

    _helpTransform: {a:1, b:0, c:0, d:1, tx:0, ty:0},
    updateDisplay: function (bone,dt, dirty) {
        var display = bone.getDisplayRenderNode();
        if(!display)
            return;

        switch (bone.getDisplayRenderNodeType()) {
            case ccs.DISPLAY_TYPE_SPRITE:
                if (dirty)
                    display.updateArmatureTransform();
                break;
            case ccs.DISPLAY_TYPE_PARTICLE:
                this.updateParticleDisplay(bone, display, dt);
                break;
            case ccs.DISPLAY_TYPE_ARMATURE:
                this.updateArmatureDisplay(bone, display, dt);
                break;
            default:
                var transform = bone.getNodeToArmatureTransform();
                display.setAdditionalTransform(transform);
                break;
        }
        if (ccs.ENABLE_PHYSICS_CHIPMUNK_DETECT || ccs.ENABLE_PHYSICS_SAVE_CALCULATED_VERTEX) {
            if (dirty) {
                var decoDisplay = bone.getDisplayManager().getCurrentDecorativeDisplay();
                var detector = decoDisplay.getColliderDetector();
                if (detector) {
                    var node = decoDisplay.getDisplay();
                    var displayTransform = node.getNodeToParentTransform();
                    var helpTransform = this._helpTransform;
                    helpTransform.a = displayTransform.a;
                    helpTransform.b = displayTransform.b;
                    helpTransform.c = displayTransform.c;
                    helpTransform.d = displayTransform.d;
                    helpTransform.tx = displayTransform.tx;
                    helpTransform.ty = displayTransform.ty;
                    var anchorPoint = cc.pointApplyAffineTransform(node.getAnchorPointInPoints(), helpTransform);
                    helpTransform.tx = anchorPoint.x;
                    helpTransform.ty = anchorPoint.y;
                    var t = cc.affineTransformConcat(helpTransform, bone.getArmature().getNodeToParentTransform());
                    detector.updateTransform(t);
                }
            }
        }
    },

    addSpriteDisplay: function (bone, decoDisplay, displayData) {
        var sdp = new ccs.SpriteDisplayData();
        sdp.copy(displayData);
        decoDisplay.setDisplayData(sdp);
        this.createSpriteDisplay(bone, decoDisplay);
    },

    createSpriteDisplay: function (bone, decoDisplay) {
        var skin = null;
        var displayData = decoDisplay.getDisplayData();
        //! remove .xxx
        var textureName = displayData.displayName;
        var startPos = textureName.lastIndexOf(".");
        if (startPos !== -1)
            textureName = textureName.substring(0, startPos);
        //! create display
        if (textureName === "")
            skin = new ccs.Skin();
        else
            skin = new ccs.Skin("#" + textureName + ".png");

        decoDisplay.setDisplay(skin);

        skin.setBone(bone);
        this.initSpriteDisplay(bone, decoDisplay, displayData.displayName, skin);

        var armature = bone.getArmature();
        if (armature) {
            if (armature.getArmatureData().dataVersion >= ccs.CONST_VERSION_COMBINED)
                skin.setSkinData(displayData.skinData);
            else
                skin.setSkinData(bone.boneData);
        }
    },

    initSpriteDisplay: function (bone, decoDisplay, displayName, skin) {
        //! remove .xxx
        var textureName = displayName;
        var startPos = textureName.lastIndexOf(".");

        if (startPos !== -1)
            textureName = textureName.substring(0, startPos);

        var textureData = ccs.armatureDataManager.getTextureData(textureName);
        if (textureData) {
            //! Init display anchorPoint, every Texture have a anchor point
            skin.setAnchorPoint(cc.p(textureData.pivotX, textureData.pivotY));
        }

        if (ccs.ENABLE_PHYSICS_CHIPMUNK_DETECT || ccs.ENABLE_PHYSICS_SAVE_CALCULATED_VERTEX) {
            if (textureData && textureData.contourDataList.length > 0) {
                //! create ContourSprite
                var colliderDetector = new ccs.ColliderDetector(bone);
                colliderDetector.addContourDataList(textureData.contourDataList);
                decoDisplay.setColliderDetector(colliderDetector);
            }
        }
    },

    addArmatureDisplay: function (bone, decoDisplay, displayData) {
        var adp = new ccs.ArmatureDisplayData();
        adp.copy(displayData);
        decoDisplay.setDisplayData(adp);

        this.createArmatureDisplay(bone, decoDisplay);
    },

    createArmatureDisplay: function (bone, decoDisplay) {
        var displayData = decoDisplay.getDisplayData();
        var armature = new ccs.Armature(displayData.displayName, bone);
        decoDisplay.setDisplay(armature);
    },

    updateArmatureDisplay: function (bone, armature, dt) {
        if (armature) {
            armature.sortAllChildren();
            armature.update(dt);
        }
    },

    addParticleDisplay: function (bone, decoDisplay, displayData) {
        var adp = new ccs.ParticleDisplayData();
        adp.copy(displayData);
        decoDisplay.setDisplayData(adp);
        this.createParticleDisplay(bone, decoDisplay);
    },

    createParticleDisplay: function (bone, decoDisplay) {
        var displayData = decoDisplay.getDisplayData();
        var system = new cc.ParticleSystem(displayData.displayName);

        system.removeFromParent();
        system.cleanup();

        var armature = bone.getArmature();
        if (armature)
            system.setParent(bone.getArmature());

        decoDisplay.setDisplay(system);
    },

    updateParticleDisplay: function (bone, particleSystem, dt) {
        var node = new ccs.BaseData();
        ccs.TransformHelp.matrixToNode(bone.nodeToArmatureTransform(), node);
        particleSystem.setPosition(node.x, node.y);
        particleSystem.setScaleX(node.scaleX);
        particleSystem.setScaleY(node.scaleY);
        particleSystem.update(dt);
    }
};