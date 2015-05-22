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

var PROPERTY_CCBFILE = "ccbFile";

cc.BuilderFileLoader = cc.NodeLoader.extend({
    _createCCNode:function (parent, ccbReader) {
        return cc.BuilderFile.create();
    },
    onHandlePropTypeCCBFile:function (node, parent, propertyName, ccbFileNode, ccbReader) {
        if (propertyName === PROPERTY_CCBFILE) {
            node.setCCBFileNode(ccbFileNode);
        } else {
            cc.NodeLoader.prototype.onHandlePropTypeCCBFile.call(this, node, parent, propertyName, ccbFileNode, ccbReader);
        }
    }
});

cc.BuilderFileLoader.loader = function () {
    return new cc.BuilderFileLoader();
};

var PROPERTY_ENABLED = "enabled";
var PROPERTY_SELECTED = "selected";
var PROPERTY_CCCONTROL = "ccControl";

cc.ControlLoader = cc.NodeLoader.extend({
    _createCCNode:function (parent, ccbReander) {
    },
    onHandlePropTypeBlockCCControl:function (node, parent, propertyName, blockCCControlData, ccbReader) {
        if (propertyName === PROPERTY_CCCONTROL) {
            node.addTargetWithActionForControlEvents(blockCCControlData.target, blockCCControlData.selCCControlHandler, blockCCControlData.controlEvents);
        } else {
            cc.NodeLoader.prototype.onHandlePropTypeBlockCCControl.call(this, node, parent, propertyName, blockCCControlData, ccbReader);
        }
    },
    onHandlePropTypeCheck:function (node, parent, propertyName, check, ccbReader) {
        if (propertyName === PROPERTY_ENABLED) {
            node.setEnabled(check);
        } else if (propertyName === PROPERTY_SELECTED) {
            node.setSelected(check);
        } else {
            cc.NodeLoader.prototype.onHandlePropTypeCheck.call(this, node, parent, propertyName, check, ccbReader);
        }
    }
});

var PROPERTY_ZOOMONTOUCHDOWN = "zoomOnTouchDown";
var PROPERTY_TITLE_NORMAL = "title|1";
var PROPERTY_TITLE_HIGHLIGHTED = "title|2";
var PROPERTY_TITLE_DISABLED = "title|3";
var PROPERTY_TITLECOLOR_NORMAL = "titleColor|1";
var PROPERTY_TITLECOLOR_HIGHLIGHTED = "titleColor|2";
var PROPERTY_TITLECOLOR_DISABLED = "titleColor|3";
var PROPERTY_TITLETTF_NORMAL = "titleTTF|1";
var PROPERTY_TITLETTF_HIGHLIGHTED = "titleTTF|2";
var PROPERTY_TITLETTF_DISABLED = "titleTTF|3";
var PROPERTY_TITLETTFSIZE_NORMAL = "titleTTFSize|1";
var PROPERTY_TITLETTFSIZE_HIGHLIGHTED = "titleTTFSize|2";
var PROPERTY_TITLETTFSIZE_DISABLED = "titleTTFSize|4";
var PROPERTY_LABELANCHORPOINT = "labelAnchorPoint";
var PROPERTY_PREFEREDSIZE = "preferedSize";         // TODO Should be = "preferredSize". This is a typo in cocos2d-iphone, cocos2d-x and CocosBuilder!
var PROPERTY_BACKGROUNDSPRITEFRAME_NORMAL = "backgroundSpriteFrame|1";
var PROPERTY_BACKGROUNDSPRITEFRAME_HIGHLIGHTED = "backgroundSpriteFrame|2";
var PROPERTY_BACKGROUNDSPRITEFRAME_DISABLED = "backgroundSpriteFrame|3";

cc.ControlButtonLoader = cc.ControlLoader.extend({
    _createCCNode:function (parent, ccbReader) {
        return new cc.ControlButton();
    },

    onHandlePropTypeCheck:function (node, parent, propertyName, check, ccbReader) {
        if (propertyName === PROPERTY_ZOOMONTOUCHDOWN) {
            node.setZoomOnTouchDown(check);
        } else {
            cc.ControlLoader.prototype.onHandlePropTypeCheck.call(this, node, parent, propertyName, check, ccbReader);
        }
    },
    onHandlePropTypeString:function (node, parent, propertyName, stringValue, ccbReader) {
        if (propertyName === PROPERTY_TITLE_NORMAL) {
            node.setTitleForState(stringValue, cc.CONTROL_STATE_NORMAL);
        } else if (propertyName === PROPERTY_TITLE_HIGHLIGHTED) {
            node.setTitleForState(stringValue, cc.CONTROL_STATE_HIGHLIGHTED);
        } else if (propertyName === PROPERTY_TITLE_DISABLED) {
            node.setTitleForState(stringValue, cc.CONTROL_STATE_DISABLED);
        } else {
            cc.ControlLoader.prototype.onHandlePropTypeString.call(this, node, parent, propertyName, stringValue, ccbReader);
        }
    },
    onHandlePropTypeFontTTF:function (node, parent, propertyName, fontTTF, ccbReader) {
        if (propertyName === PROPERTY_TITLETTF_NORMAL) {
            node.setTitleTTFForState(fontTTF, cc.CONTROL_STATE_NORMAL);
        } else if (propertyName === PROPERTY_TITLETTF_HIGHLIGHTED) {
            node.setTitleTTFForState(fontTTF, cc.CONTROL_STATE_HIGHLIGHTED);
        } else if (propertyName === PROPERTY_TITLETTF_DISABLED) {
            node.setTitleTTFForState(fontTTF, cc.CONTROL_STATE_DISABLED);
        } else {
            cc.ControlLoader.prototype.onHandlePropTypeFontTTF.call(this, node, parent, propertyName, fontTTF, ccbReader);
        }
    },
    onHandlePropTypeFloatScale:function (node, parent, propertyName, floatScale, ccbReader) {
        if (propertyName === PROPERTY_TITLETTFSIZE_NORMAL) {
            node.setTitleTTFSizeForState(floatScale, cc.CONTROL_STATE_NORMAL);
        } else if (propertyName === PROPERTY_TITLETTFSIZE_HIGHLIGHTED) {
            node.setTitleTTFSizeForState(floatScale, cc.CONTROL_STATE_HIGHLIGHTED);
        } else if (propertyName === PROPERTY_TITLETTFSIZE_DISABLED) {
            node.setTitleTTFSizeForState(floatScale, cc.CONTROL_STATE_DISABLED);
        } else {
            cc.ControlLoader.prototype.onHandlePropTypeFloatScale.call(this, node, parent, propertyName, floatScale, ccbReader);
        }
    },
    onHandlePropTypePoint:function (node, parent, propertyName, point, ccbReader) {
        if (propertyName === PROPERTY_LABELANCHORPOINT) {
            node.setLabelAnchorPoint(point);
        } else {
            cc.ControlLoader.prototype.onHandlePropTypePoint.call(this, node, parent, propertyName, point, ccbReader);
        }
    },
    onHandlePropTypeSize:function (node, parent, propertyName, size, ccbReader) {
        if (propertyName === PROPERTY_PREFEREDSIZE) {
            node.setPreferredSize(size);
        } else {
            cc.ControlLoader.prototype.onHandlePropTypeSize.call(this, node, parent, propertyName, size, ccbReader);
        }
    },
    onHandlePropTypeSpriteFrame:function (node, parent, propertyName, spriteFrame, ccbReader) {
        if (propertyName === PROPERTY_BACKGROUNDSPRITEFRAME_NORMAL) {
            if (spriteFrame != null) {
                node.setBackgroundSpriteFrameForState(spriteFrame, cc.CONTROL_STATE_NORMAL);
            }
        } else if (propertyName === PROPERTY_BACKGROUNDSPRITEFRAME_HIGHLIGHTED) {
            if (spriteFrame != null) {
                node.setBackgroundSpriteFrameForState(spriteFrame, cc.CONTROL_STATE_HIGHLIGHTED);
            }
        } else if (propertyName === PROPERTY_BACKGROUNDSPRITEFRAME_DISABLED) {
            if (spriteFrame != null) {
                node.setBackgroundSpriteFrameForState(spriteFrame, cc.CONTROL_STATE_DISABLED);
            }
        } else {
            cc.ControlLoader.prototype.onHandlePropTypeSpriteFrame.call(this, node, parent, propertyName, spriteFrame, ccbReader);
        }
    },
    onHandlePropTypeColor3:function (node, parent, propertyName, ccColor3B, ccbReader) {
        if (propertyName === PROPERTY_TITLECOLOR_NORMAL) {
            node.setTitleColorForState(ccColor3B, cc.CONTROL_STATE_NORMAL);
        } else if (propertyName === PROPERTY_TITLECOLOR_HIGHLIGHTED) {
            node.setTitleColorForState(ccColor3B, cc.CONTROL_STATE_HIGHLIGHTED);
        } else if (propertyName === PROPERTY_TITLECOLOR_DISABLED) {
            node.setTitleColorForState(ccColor3B, cc.CONTROL_STATE_DISABLED);
        } else {
            cc.ControlLoader.prototype.onHandlePropTypeColor3.call(this, node, parent, propertyName, ccColor3B, ccbReader);
        }
    }
});

cc.ControlButtonLoader.loader = function () {
    return new cc.ControlButtonLoader();
};

var PROPERTY_CONTAINER = "container";
var PROPERTY_DIRECTION = "direction";
var PROPERTY_CLIPSTOBOUNDS = "clipsToBounds";
var PROPERTY_BOUNCES = "bounces";
var PROPERTY_SCALE = "scale";

cc.ScrollViewLoader = cc.NodeLoader.extend({
    _createCCNode:function (parent, ccbReader) {
        return new cc.ScrollView();
    },

    onHandlePropTypeSize:function(node,parent,propertyName,size,ccbReader){
        if(propertyName === PROPERTY_CONTENTSIZE){
            node.setViewSize(size);
        }else{
            cc.NodeLoader.prototype.onHandlePropTypeSize.call(this, node,parent,propertyName,size,ccbReader);
        }
    },

    onHandlePropTypeCCBFile:function (node, parent, propertyName, ccbFileNode, ccbReader) {
        if (propertyName === PROPERTY_CONTAINER) {
            node.setContainer(ccbFileNode);
            node.updateInset();
        } else {
            cc.NodeLoader.prototype.onHandlePropTypeCCBFile.call(this, node, parent, propertyName, ccbFileNode, ccbReader);
        }
    },
    onHandlePropTypeCheck:function (node, parent, propertyName, check, ccbReader) {
        if (propertyName === PROPERTY_CLIPSTOBOUNDS) {
            node.setClippingToBounds(check);
        } else if (propertyName === PROPERTY_BOUNCES) {
            node.setBounceable(check);
        } else {
            cc.NodeLoader.prototype.onHandlePropTypeCheck.call(this, node, parent, propertyName, check, ccbReader);
        }
    },
    onHandlePropTypeFloat:function (node, parent, propertyName, floatValue, ccbReader) {
        if (propertyName === PROPERTY_SCALE) {
            node.setScale(floatValue);
        } else {
            cc.NodeLoader.prototype.onHandlePropTypeFloat.call(this, node, parent, propertyName, floatValue, ccbReader);
        }
    },
    onHandlePropTypeIntegerLabeled:function (node, parent, propertyName, integerLabeled, ccbReader) {
        if (propertyName === PROPERTY_DIRECTION) {
            node.setDirection(integerLabeled);
        } else {
            cc.NodeLoader.prototype.onHandlePropTypeIntegerLabeled.call(this, node, parent, propertyName, integerLabeled, ccbReader);
        }
    }
});

cc.ScrollViewLoader.loader = function () {
    return new cc.ScrollViewLoader();
};

var PROPERTY_CONTENTSIZE = "contentSize";
var PROPERTY_SPRITEFRAME = "spriteFrame";
var PROPERTY_COLOR = "color";
var PROPERTY_OPACITY = "opacity";
var PROPERTY_BLENDFUNC = "blendFunc";
var PROPERTY_INSETLEFT = "insetLeft";
var PROPERTY_INSETTOP = "insetTop" ;
var PROPERTY_INSETRIGHT = "insetRight";
var PROPERTY_INSETBOTTOM = "insetBottom";

cc.Scale9SpriteLoader = cc.NodeLoader.extend({
    _createCCNode:function(parent,ccbReader){
        var sprite = new cc.Scale9Sprite();

        sprite.setAnchorPoint(0, 0);

        return sprite;
    },

    onHandlePropTypeColor3:function(node, parent, propertyName, ccColor3B,ccbReader){
        if(propertyName === PROPERTY_COLOR) {
            if(ccColor3B.r !== 255 || ccColor3B.g !== 255 || ccColor3B.b !== 255){
                node.setColor(ccColor3B);
            }
        } else {
            cc.NodeLoader.prototype.onHandlePropTypeColor3.call(this, node, parent, propertyName, ccColor3B,ccbReader);
        }
    },
    onHandlePropTypeByte:function(node, parent, propertyName, byteValue,ccbReader){
        if(propertyName === PROPERTY_OPACITY) {
            node.setOpacity(byteValue);
        } else {
            cc.NodeLoader.prototype.onHandlePropTypeByte.call(this, node, parent, propertyName, byteValue,ccbReader);
        }
    },
    onHandlePropTypeBlendFunc:function(node, parent, propertyName, ccBlendFunc,ccbReader){
        if(propertyName === PROPERTY_BLENDFUNC) {
            // TODO Not exported by CocosBuilder yet!
            // node.setBlendFunc(ccBlendFunc);
        } else {
            cc.NodeLoader.prototype.onHandlePropTypeBlendFunc.call(this, node, parent, propertyName, ccBlendFunc,ccbReader);
        }
    },
    onHandlePropTypeSpriteFrame:function(node, parent, propertyName, spriteFrame,ccbReader){
        if(propertyName === PROPERTY_SPRITEFRAME) {
            node.setSpriteFrame(spriteFrame);
        } else {
            cc.NodeLoader.prototype.onHandlePropTypeSpriteFrame.call(this, node, parent, propertyName, spriteFrame,ccbReader);
        }
    },
    onHandlePropTypeSize:function(node, parent, propertyName, size,ccbReader){
        if(propertyName === PROPERTY_CONTENTSIZE) {
            //node.setContentSize(size);
        } else if(propertyName === PROPERTY_PREFEREDSIZE) {
            node.setPreferredSize(size);
        } else {
            cc.NodeLoader.prototype.onHandlePropTypeSize.call(this, node, parent, propertyName, size,ccbReader);
        }
    },
    onHandlePropTypeFloat:function(node, parent, propertyName, floatValue,ccbReader){
        if(propertyName === PROPERTY_INSETLEFT) {
            node.setInsetLeft(floatValue);
        } else if(propertyName === PROPERTY_INSETTOP) {
            node.setInsetTop(floatValue);
        } else if(propertyName === PROPERTY_INSETRIGHT) {
            node.setInsetRight(floatValue);
        } else if(propertyName === PROPERTY_INSETBOTTOM) {
            node.setInsetBottom(floatValue);
        } else {
            cc.NodeLoader.prototype.onHandlePropTypeFloat.call(this, node, parent, propertyName, floatValue,ccbReader);
        }
    }
});

cc.Scale9SpriteLoader.loader = function(){
   return new cc.Scale9SpriteLoader();
};



