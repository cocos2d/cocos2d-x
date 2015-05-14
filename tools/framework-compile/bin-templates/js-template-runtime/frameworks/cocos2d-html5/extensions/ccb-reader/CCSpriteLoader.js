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

var PROPERTY_FLIP = "flip";
var PROPERTY_DISPLAYFRAME = "displayFrame";
var PROPERTY_COLOR = "color";
var PROPERTY_OPACITY = "opacity";
var PROPERTY_BLENDFUNC = "blendFunc";

cc.SpriteLoader = cc.NodeLoader.extend({
    _createCCNode:function (parent, ccbReader) {
        return new cc.Sprite();
    },

    onHandlePropTypeColor3:function (node, parent, propertyName, ccColor3B, ccbReader) {
        if (propertyName === PROPERTY_COLOR) {
            if(ccColor3B.r !== 255 || ccColor3B.g !== 255 || ccColor3B.b !== 255){
                node.setColor(ccColor3B);
            }
        } else {
            cc.NodeLoader.prototype.onHandlePropTypeColor3.call(this, node, parent, propertyName, ccColor3B, ccbReader);
        }
    },
    onHandlePropTypeByte:function (node, parent, propertyName, byteValue, ccbReader) {
        if (propertyName === PROPERTY_OPACITY) {
            node.setOpacity(byteValue);
        } else {
            cc.NodeLoader.prototype.onHandlePropTypeByte.call(this, node, parent, propertyName, byteValue, ccbReader);
        }
    },
    onHandlePropTypeBlendFunc:function (node, parent, propertyName, ccbBlendFunc, ccbReader) {
        if (propertyName === PROPERTY_BLENDFUNC) {
            node.setBlendFunc(ccbBlendFunc);
        } else {
            cc.NodeLoader.prototype.onHandlePropTypeBlendFunc.call(this, node, parent, propertyName, ccbBlendFunc, ccbReader);
        }
    },
    onHandlePropTypeSpriteFrame:function (node, parent, propertyName, ccSpriteFrame, ccbReader) {
        if (propertyName === PROPERTY_DISPLAYFRAME) {
            if(ccSpriteFrame)
                node.setSpriteFrame(ccSpriteFrame);
            else
                cc.log("ERROR: SpriteFrame is null");
        } else {
            cc.NodeLoader.prototype.onHandlePropTypeSpriteFrame.call(this, node, parent, propertyName, ccSpriteFrame, ccbReader);
        }
    },
    onHandlePropTypeFlip:function (node, parent, propertyName, flip, ccbReader) {
        if (propertyName === PROPERTY_FLIP) {
            node.setFlippedX(flip[0]);
            node.setFlippedY(flip[1]);
        } else {
            cc.NodeLoader.prototype.onHandlePropTypeFlip.call(this, node, parent, propertyName, flip, ccbReader);
        }
    }
});

cc.SpriteLoader.loader = function () {
    return new cc.SpriteLoader();
};

var PROPERTY_TOUCH_ENABLED = "touchEnabled";
var PROPERTY_IS_TOUCH_ENABLED = "isTouchEnabled";
var PROPERTY_ACCELEROMETER_ENABLED = "accelerometerEnabled";
var PROPERTY_IS_ACCELEROMETER_ENABLED = "isAccelerometerEnabled";
var PROPERTY_IS_MOUSE_ENABLED = "isMouseEnabled";
var PROPERTY_MOUSE_ENABLED = "mouseEnabled";
var PROPERTY_KEYBOARD_ENABLED = "keyboardEnabled";
var PROPERTY_IS_KEYBOARD_ENABLED = "isKeyboardEnabled";

cc.LayerLoader = cc.NodeLoader.extend({
    _createCCNode:function (parent, ccbReader) {

        var layer = new cc.Layer();

        layer.setContentSize(0,0);

        return layer;
    },
    onHandlePropTypeCheck:function (node, parent, propertyName, check, ccbReader) {
        if (propertyName === PROPERTY_TOUCH_ENABLED || propertyName === PROPERTY_IS_TOUCH_ENABLED) {
            //node.setTouchEnabled(check);
        } else if (propertyName === PROPERTY_ACCELEROMETER_ENABLED || propertyName === PROPERTY_IS_ACCELEROMETER_ENABLED) {
            //node.setAccelerometerEnabled(check);
        } else if (propertyName === PROPERTY_MOUSE_ENABLED || propertyName === PROPERTY_IS_MOUSE_ENABLED ) {
            //node.setMouseEnabled(check);
        } else if (propertyName === PROPERTY_KEYBOARD_ENABLED || propertyName === PROPERTY_IS_KEYBOARD_ENABLED) {
            // TODO XXX
            if(node.setKeyboardEnabled && !cc.sys.isNative) {
                node.setKeyboardEnabled(check);
            } else {
                cc.log("The property '" + PROPERTY_IS_KEYBOARD_ENABLED + "' is not supported!");
                // This comes closest: ((CCLayer *)pNode).setKeypadEnabled(pCheck);
            }
        } else {
            cc.NodeLoader.prototype.onHandlePropTypeCheck.call(this, node, parent, propertyName, check, ccbReader);
        }
    }
});

cc.LayerLoader.loader = function () {
    return new cc.LayerLoader();
};


cc.LayerColorLoader = cc.LayerLoader.extend({
    _createCCNode:function (parent, ccbReader) {
        return new cc.LayerColor();
    },

    onHandlePropTypeColor3:function (node, parent, propertyName, ccColor3B, ccbReader) {
        if (propertyName === PROPERTY_COLOR) {
            node.setColor(ccColor3B);
        } else {
            cc.LayerLoader.prototype.onHandlePropTypeColor3.call(this, node, parent, propertyName, ccColor3B, ccbReader);
        }
    },
    onHandlePropTypeByte:function (node, parent, propertyName, byteValue, ccbReader) {
        if (propertyName === PROPERTY_OPACITY) {
            node.setOpacity(byteValue);
        } else {
            cc.LayerLoader.prototype.onHandlePropTypeByte.call(this, node, parent, propertyName, byteValue, ccbReader);
        }
    },
    onHandlePropTypeBlendFunc:function (node, parent, propertyName, ccBlendFunc, ccbReader) {
        if (propertyName === PROPERTY_BLENDFUNC) {
            node.setBlendFunc(ccBlendFunc);
        } else {
            cc.LayerLoader.prototype.onHandlePropTypeBlendFunc.call(this, node, parent, propertyName, ccBlendFunc, ccbReader);
        }
    }
});

cc.LayerColorLoader.loader = function () {
    return new cc.LayerColorLoader();
};

var PROPERTY_STARTCOLOR = "startColor";
var PROPERTY_ENDCOLOR = "endColor";
var PROPERTY_STARTOPACITY = "startOpacity";
var PROPERTY_ENDOPACITY = "endOpacity";
var PROPERTY_VECTOR = "vector";

cc.LayerGradientLoader = cc.LayerLoader.extend({
    _createCCNode:function (parent, ccbReader) {
        return new cc.LayerGradient();
    },
    onHandlePropTypeColor3:function (node, parent, propertyName, ccColor3B, ccbReader) {
        if (propertyName === PROPERTY_STARTCOLOR) {
            node.setStartColor(ccColor3B);
        } else if (propertyName === PROPERTY_ENDCOLOR) {
            node.setEndColor(ccColor3B);
        } else {
            cc.LayerLoader.prototype.onHandlePropTypeColor3.call(this, node, parent, propertyName, ccColor3B, ccbReader);
        }
    },
    onHandlePropTypeByte:function (node, parent, propertyName, byteValue, ccbReader) {
        if (propertyName === PROPERTY_STARTOPACITY) {
            node.setStartOpacity(byteValue);
        } else if (propertyName === PROPERTY_ENDOPACITY) {
            node.setEndOpacity(byteValue);
        } else {
            cc.LayerLoader.prototype.onHandlePropTypeByte.call(this, node, parent, propertyName, byteValue, ccbReader);
        }
    },
    onHandlePropTypePoint:function (node, parent, propertyName, point, ccbReader) {
        if (propertyName === PROPERTY_VECTOR) {
            node.setVector(point);
            // TODO Not passed along the ccbi file.
            // node.setCompressedInterpolation(true);
        } else {
            cc.LayerLoader.prototype.onHandlePropTypePoint.call(this, node, parent, propertyName, point, ccbReader);
        }
    },
    onHandlePropTypeBlendFunc:function (node, parent, propertyName, ccBlendFunc, ccbReader) {
        if (propertyName === PROPERTY_BLENDFUNC) {
            node.setBlendFunc(ccBlendFunc);
        } else {
            cc.LayerLoader.prototype.onHandlePropTypeBlendFunc.call(this, node, parent, propertyName, ccBlendFunc, ccbReader);
        }
    }
});

cc.LayerGradientLoader.loader = function () {
    return new cc.LayerGradientLoader();
};

cc.MenuLoader = cc.LayerLoader.extend({
    _createCCNode:function (parent, ccbReader) {
        var menu = new cc.Menu();

        menu.setContentSize(0,0);

        return menu;
    }
});

cc.MenuLoader.loader = function () {
    return new cc.MenuLoader();
};

var PROPERTY_BLOCK = "block";
var PROPERTY_ISENABLED = "isEnabled";

cc.MenuItemLoader = cc.NodeLoader.extend({
    _createCCNode:function (parent, ccbReader) {
        return null;
    },

    onHandlePropTypeBlock:function (node, parent, propertyName, blockData, ccbReader) {
        if (propertyName === PROPERTY_BLOCK) {
            if (null != blockData) { // Add this condition to allow CCMenuItemImage without target/selector predefined
                node.setTarget(blockData.selMenuHander, blockData.target);
            }
        } else {
            cc.NodeLoader.prototype.onHandlePropTypeBlock.call(this, node, parent, propertyName, blockData, ccbReader);
        }
    },
    onHandlePropTypeCheck:function (node, parent, propertyName, check, ccbReader) {
        if (propertyName === PROPERTY_ISENABLED) {
            node.setEnabled(check);
        } else {
            cc.NodeLoader.prototype.onHandlePropTypeCheck.call(this, node, parent, propertyName, check, ccbReader);
        }
    }
});

var PROPERTY_NORMALDISPLAYFRAME = "normalSpriteFrame";
var PROPERTY_SELECTEDDISPLAYFRAME = "selectedSpriteFrame";
var PROPERTY_DISABLEDDISPLAYFRAME = "disabledSpriteFrame";

cc.MenuItemImageLoader = cc.MenuItemLoader.extend({
    _createCCNode:function (parent, ccbReader) {
        return new cc.MenuItemImage();
    },

    onHandlePropTypeSpriteFrame:function (node, parent, propertyName, spriteFrame, ccbReader) {
        if (propertyName === PROPERTY_NORMALDISPLAYFRAME) {
            if (spriteFrame != null) {
                node.setNormalSpriteFrame(spriteFrame);
            }
        } else if (propertyName === PROPERTY_SELECTEDDISPLAYFRAME) {
            if (spriteFrame != null) {
                node.setSelectedSpriteFrame(spriteFrame);
            }
        } else if (propertyName === PROPERTY_DISABLEDDISPLAYFRAME) {
            if (spriteFrame != null) {
                node.setDisabledSpriteFrame(spriteFrame);
            }
        } else {
            cc.MenuItemLoader.prototype.onHandlePropTypeSpriteFrame.call(this, node, parent, propertyName, spriteFrame, ccbReader);
        }
    }
});

cc.MenuItemImageLoader.loader = function () {
    return new cc.MenuItemImageLoader();
};

var PROPERTY_FONTNAME = "fontName";
var PROPERTY_FONTSIZE = "fontSize";
var PROPERTY_HORIZONTALALIGNMENT = "horizontalAlignment";
var PROPERTY_VERTICALALIGNMENT = "verticalAlignment";
var PROPERTY_STRING = "string";
var PROPERTY_DIMENSIONS = "dimensions";

cc.LabelTTFLoader = cc.NodeLoader.extend({
    _createCCNode:function (parent, ccbReader) {
        return new cc.LabelTTF();
    },
    onHandlePropTypeColor3:function (node, parent, propertyName, ccColor3B, ccbReader) {
        if (propertyName === PROPERTY_COLOR) {
            if(ccColor3B.r !== 255 || ccColor3B.g !== 255 || ccColor3B.b !== 255){
                node.setColor(ccColor3B);
            }
        } else {
            cc.NodeLoader.prototype.onHandlePropTypeColor3.call(this, node, parent, propertyName, ccColor3B, ccbReader);
        }
    },
    onHandlePropTypeByte:function (node, parent, propertyName, byteValue, ccbReader) {
        if (propertyName === PROPERTY_OPACITY) {
            node.setOpacity(byteValue);
        } else {
            cc.NodeLoader.prototype.onHandlePropTypeByte.call(this, node, parent, propertyName, byteValue, ccbReader);
        }
    },
    onHandlePropTypeBlendFunc:function (node, parent, propertyName, ccBlendFunc, ccbReader) {
        if (propertyName === PROPERTY_BLENDFUNC) {
            node.setBlendFunc(ccBlendFunc);
        } else {
            cc.NodeLoader.prototype.onHandlePropTypeBlendFunc.call(this, node, parent, propertyName, ccBlendFunc, ccbReader);
        }
    },
    onHandlePropTypeFontTTF:function (node, parent, propertyName, fontTTF, ccbReader) {
        if (propertyName === PROPERTY_FONTNAME) {
            node.setFontName(fontTTF);
        } else {
            cc.NodeLoader.prototype.onHandlePropTypeFontTTF.call(this, node, parent, propertyName, fontTTF, ccbReader);
        }
    },
    onHandlePropTypeText:function (node, parent, propertyName, textValue, ccbReader) {
        if (propertyName === PROPERTY_STRING) {
            node.setString(textValue);
        } else {
            cc.NodeLoader.prototype.onHandlePropTypeText.call(this, node, parent, propertyName, textValue, ccbReader);
        }
    },
    onHandlePropTypeFloatScale:function (node, parent, propertyName, floatScale, ccbReader) {
        if (propertyName === PROPERTY_FONTSIZE) {
            node.setFontSize(floatScale);
        } else {
            cc.NodeLoader.prototype.onHandlePropTypeFloatScale.call(this, node, parent, propertyName, floatScale, ccbReader);
        }
    },
    onHandlePropTypeIntegerLabeled:function (node, parent, propertyName, integerLabeled, ccbReader) {
        if (propertyName === PROPERTY_HORIZONTALALIGNMENT) {
            node.setHorizontalAlignment(integerLabeled);
        } else if (propertyName === PROPERTY_VERTICALALIGNMENT) {
            node.setVerticalAlignment(integerLabeled);
        } else {
            cc.NodeLoader.prototype.onHandlePropTypeIntegerLabeled.call(this, node, parent, propertyName, integerLabeled, ccbReader);
        }
    },
    onHandlePropTypeSize:function (node, parent, propertyName, size, ccbReader) {
        if (propertyName === PROPERTY_DIMENSIONS) {
            node.setDimensions(size);
        } else {
            cc.NodeLoader.prototype.onHandlePropTypeSize.call(this, node, parent, propertyName, size, ccbReader);
        }
    }
});

cc.LabelTTFLoader.loader = function () {
    return new cc.LabelTTFLoader();
};

var PROPERTY_FNTFILE = "fntFile";

cc.LabelBMFontLoader = cc.NodeLoader.extend({
    _createCCNode:function (parent, ccbReader) {
        return new cc.LabelBMFont();
    },

    onHandlePropTypeColor3:function (node, parent, propertyName, ccColor3B, ccbReader) {
        if (propertyName === PROPERTY_COLOR) {
            if(ccColor3B.r !== 255 || ccColor3B.g !== 255 || ccColor3B.b !== 255){
                node.setColor(ccColor3B);
            }
        } else {
            cc.NodeLoader.prototype.onHandlePropTypeColor3.call(this, node, parent, propertyName, ccColor3B, ccbReader);
        }
    },
    onHandlePropTypeByte:function (node, parent, propertyName, byteValue, ccbReader) {
        if (propertyName === PROPERTY_OPACITY) {
            node.setOpacity(byteValue);
        } else {
            cc.NodeLoader.prototype.onHandlePropTypeByte.call(this, node, parent, propertyName, byteValue, ccbReader);
        }
    },
    onHandlePropTypeBlendFunc:function (node, parent, propertyName, ccBlendFunc, ccbReader) {
        if (propertyName === PROPERTY_BLENDFUNC) {
            node.setBlendFunc(ccBlendFunc);
        } else {
            cc.NodeLoader.prototype.onHandlePropTypeBlendFunc.call(this, node, parent, propertyName, ccBlendFunc, ccbReader);
        }
    },
    onHandlePropTypeFntFile:function (node, parent, propertyName, fntFile, ccbReader) {
        if (propertyName === PROPERTY_FNTFILE) {
            node.setFntFile(fntFile);
        } else {
            cc.NodeLoader.prototype.onHandlePropTypeFntFile.call(this, node, parent, propertyName, fntFile, ccbReader);
        }
    },
    onHandlePropTypeText:function (node, parent, propertyName, textValue, ccbReader) {
        if (propertyName === PROPERTY_STRING) {
            node.setString(textValue);
        } else {
            cc.NodeLoader.prototype.onHandlePropTypeText.call(this, node, parent, propertyName, textValue, ccbReader);
        }
    }
});

cc.LabelBMFontLoader.loader = function () {
    return new cc.LabelBMFontLoader();
};

var PROPERTY_EMITERMODE = "emitterMode";
var PROPERTY_POSVAR = "posVar";
var PROPERTY_EMISSIONRATE = "emissionRate";
var PROPERTY_DURATION = "duration";
var PROPERTY_TOTALPARTICLES = "totalParticles";
var PROPERTY_LIFE = "life";
var PROPERTY_STARTSIZE = "startSize";
var PROPERTY_ENDSIZE = "endSize";
var PROPERTY_STARTSPIN = "startSpin";
var PROPERTY_ENDSPIN = "endSpin";
var PROPERTY_ANGLE = "angle";
var PROPERTY_GRAVITY = "gravity";
var PROPERTY_SPEED = "speed";
var PROPERTY_TANGENTIALACCEL = "tangentialAccel";
var PROPERTY_RADIALACCEL = "radialAccel";
var PROPERTY_TEXTURE = "texture";
var PROPERTY_STARTRADIUS = "startRadius";
var PROPERTY_ENDRADIUS = "endRadius";
var PROPERTY_ROTATEPERSECOND = "rotatePerSecond";

cc.ParticleSystemLoader = cc.NodeLoader.extend({
    _createCCNode:function (parent, ccbReader) {
        return new cc.ParticleSystem();
    },

    onHandlePropTypeIntegerLabeled:function (node, parent, propertyName, integerLabeled, ccbReader) {
        if (propertyName === PROPERTY_EMITERMODE) {
            node.setEmitterMode(integerLabeled);
        } else {
            cc.NodeLoader.prototype.onHandlePropTypeIntegerLabeled.call(this, node, parent, propertyName, integerLabeled, ccbReader);
        }
    },
    onHandlePropTypePoint:function (node, parent, propertyName, point, ccbReader) {
        if (propertyName === PROPERTY_POSVAR) {
            node.setPosVar(point);
        } else if (propertyName === PROPERTY_GRAVITY) {
            node.setGravity(point);
        } else {
            cc.NodeLoader.prototype.onHandlePropTypePoint.call(this, node, parent, propertyName, point, ccbReader);
        }
    },
    onHandlePropTypeFloat:function (node, parent, propertyName, floatValue, ccbReader) {
        if (propertyName === PROPERTY_EMISSIONRATE) {
            node.setEmissionRate(floatValue);
        } else if (propertyName === PROPERTY_DURATION) {
            node.setDuration(floatValue);
        } else {
            cc.NodeLoader.prototype.onHandlePropTypeFloat.call(this, node, parent, propertyName, floatValue, ccbReader);
        }
    },
    onHandlePropTypeInteger:function (node, parent, propertyName, integerValue, ccbReader) {
        if (propertyName === PROPERTY_TOTALPARTICLES) {
            node.setTotalParticles(integerValue);
        } else {
            cc.NodeLoader.prototype.onHandlePropTypeInteger.call(this, node, parent, propertyName, integerValue, ccbReader);
        }
    },
    onHandlePropTypeFloatVar:function (node, parent, propertyName, floatVar, ccbReader) {
        if (propertyName === PROPERTY_LIFE) {
            node.setLife(floatVar[0]);
            node.setLifeVar(floatVar[1]);
        } else if (propertyName === PROPERTY_STARTSIZE) {
            node.setStartSize(floatVar[0]);
            node.setStartSizeVar(floatVar[1]);
        } else if (propertyName === PROPERTY_ENDSIZE) {
            node.setEndSize(floatVar[0]);
            node.setEndSizeVar(floatVar[1]);
        } else if (propertyName === PROPERTY_STARTSPIN) {
            node.setStartSpin(floatVar[0]);
            node.setStartSpinVar(floatVar[1]);
        } else if (propertyName === PROPERTY_ENDSPIN) {
            node.setEndSpin(floatVar[0]);
            node.setEndSpinVar(floatVar[1]);
        } else if (propertyName === PROPERTY_ANGLE) {
            node.setAngle(floatVar[0]);
            node.setAngleVar(floatVar[1]);
        } else if (propertyName === PROPERTY_SPEED) {
            node.setSpeed(floatVar[0]);
            node.setSpeedVar(floatVar[1]);
        } else if (propertyName === PROPERTY_TANGENTIALACCEL) {
            node.setTangentialAccel(floatVar[0]);
            node.setTangentialAccelVar(floatVar[1]);
        } else if (propertyName === PROPERTY_RADIALACCEL) {
            node.setRadialAccel(floatVar[0]);
            node.setRadialAccelVar(floatVar[1]);
        } else if (propertyName === PROPERTY_STARTRADIUS) {
            node.setStartRadius(floatVar[0]);
            node.setStartRadiusVar(floatVar[1]);
        } else if (propertyName === PROPERTY_ENDRADIUS) {
            node.setEndRadius(floatVar[0]);
            node.setEndRadiusVar(floatVar[1]);
        } else if (propertyName === PROPERTY_ROTATEPERSECOND) {
            node.setRotatePerSecond(floatVar[0]);
            node.setRotatePerSecondVar(floatVar[1]);
        } else {
            cc.NodeLoader.prototype.onHandlePropTypeFloatVar.call(this, node, parent, propertyName, floatVar, ccbReader);
        }
    },
    onHandlePropTypeColor4FVar:function (node, parent, propertyName, ccColor4FVar, ccbReader) {
        if (propertyName === PROPERTY_STARTCOLOR) {
            node.setStartColor(ccColor4FVar[0]);
            node.setStartColorVar(ccColor4FVar[1]);
        } else if (propertyName === PROPERTY_ENDCOLOR) {
            node.setEndColor(ccColor4FVar[0]);
            node.setEndColorVar(ccColor4FVar[1]);
        } else {
            cc.NodeLoader.prototype.onHandlePropTypeColor4FVar.call(this, node, parent, propertyName, ccColor4FVar, ccbReader);
        }
    },
    onHandlePropTypeBlendFunc:function (node, parent, propertyName, ccBlendFunc, ccbReader) {
        if (propertyName === PROPERTY_BLENDFUNC) {
            node.setBlendFunc(ccBlendFunc);
        } else {
            cc.NodeLoader.prototype.onHandlePropTypeBlendFunc.call(this, node, parent, propertyName, ccBlendFunc, ccbReader);
        }
    },
    onHandlePropTypeTexture:function (node, parent, propertyName, ccTexture2D, ccbReader) {
        if (propertyName === PROPERTY_TEXTURE) {
            node.setTexture(ccTexture2D);
        } else {
            cc.NodeLoader.prototype.onHandlePropTypeTexture.call(this, node, parent, propertyName, ccTexture2D, ccbReader);
        }
    }
});

cc.ParticleSystemLoader.loader = function () {
    return new cc.ParticleSystemLoader();
};







