/*
 * Copyright (c) 2014 Chukong Technologies Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

/**
 *  <p>Properties configuration function </br>
 *  All properties in attrs will be set to the node, </br>
 *  when the setter of the node is available, </br>
 *  the property will be set via setter function.</br>
 *  </p>
 * @param {Object} attrs Properties to be set to node
 */
cc.Node.prototype.attr = function(attrs) {
    for(var key in attrs) {
        this[key] = attrs[key];
    }
};

var _proto = cc.Action.prototype;
cc.defineGetterSetter(_proto, "tag", _proto.getTag, _proto.setTag);

// Overrides
_proto = cc.AtlasNode.prototype;
cc.defineGetterSetter(_proto, "opacity", _proto.getOpacity, _proto.setOpacity);
cc.defineGetterSetter(_proto, "opacityModifyRGB", _proto.isOpacityModifyRGB, _proto.setOpacityModifyRGB);
cc.defineGetterSetter(_proto, "color", _proto.getColor, _proto.setColor);

_proto = cc.LabelTTF.prototype;
cc.defineGetterSetter(_proto, "size", _proto.getContentSize, _proto.setContentSize);
cc.defineGetterSetter(_proto, "width", _proto._getWidth, _proto._setWidth);
cc.defineGetterSetter(_proto, "height", _proto._getHeight, _proto._setHeight);

_proto = cc.LayerColor.prototype;
cc.defineGetterSetter(_proto, "width", _proto._getWidth, _proto._setWidth);
cc.defineGetterSetter(_proto, "height", _proto._getHeight, _proto._setHeight);
cc.defineGetterSetter(_proto, "opacity", _proto.getOpacity, _proto.setOpacity);
cc.defineGetterSetter(_proto, "color", _proto.getColor, _proto.setColor);
cc.defineGetterSetter(_proto, "opacityModifyRGB", _proto.isOpacityModifyRGB, _proto.setOpacityModifyRGB);

_proto = cc.LayerGradient.prototype;
cc.defineGetterSetter(_proto, "size", _proto.getContentSize, _proto.setContentSize);
cc.defineGetterSetter(_proto, "width", _proto._getWidth, _proto._setWidth);
cc.defineGetterSetter(_proto, "height", _proto._getHeight, _proto._setHeight);

_proto = cc.Sprite.prototype;
cc.defineGetterSetter(_proto, "ignoreAnchor", _proto.isIgnoreAnchorPointForPosition, _proto.ignoreAnchorPointForPosition);

_proto = cc.LabelAtlas.prototype;
cc.defineGetterSetter(_proto, "color", _proto.getColor, _proto.setColor);

_proto = cc.LabelBMFont.prototype;
cc.defineGetterSetter(_proto, "anchorX", _proto._getAnchorX, _proto._setAnchorX);
cc.defineGetterSetter(_proto, "anchorY", _proto._getAnchorY, _proto._setAnchorY);
cc.defineGetterSetter(_proto, "scale", _proto.getScale, _proto.setScale);
cc.defineGetterSetter(_proto, "scaleX", _proto.getScaleX, _proto.setScaleX);
cc.defineGetterSetter(_proto, "scaleY", _proto.getScaleY, _proto.setScaleY);
cc.defineGetterSetter(_proto, "opacityModifyRGB", _proto.isOpacityModifyRGB, _proto.setOpacityModifyRGB);
cc.defineGetterSetter(_proto, "opacity", _proto.getOpacity, _proto.setOpacity);
cc.defineGetterSetter(_proto, "cascadeOpacity", _proto.isCascadeOpacityEnabled, _proto.setCascadeOpacityEnabled);
cc.defineGetterSetter(_proto, "color", _proto.getColor, _proto.setColor);
cc.defineGetterSetter(_proto, "cascadeColor", _proto.isCascadeColorEnabled, _proto.setCascadeColorEnabled);

_proto = cc.Menu.prototype;
cc.defineGetterSetter(_proto, "opacityModifyRGB", _proto.isOpacityModifyRGB, _proto.setOpacityModifyRGB);
cc.defineGetterSetter(_proto, "opacity", _proto.getOpacity, _proto.setOpacity);
cc.defineGetterSetter(_proto, "cascadeOpacity", _proto.isCascadeOpacityEnabled, _proto.setCascadeOpacityEnabled);
cc.defineGetterSetter(_proto, "color", _proto.getColor, _proto.setColor);
cc.defineGetterSetter(_proto, "cascadeColor", _proto.isCascadeColorEnabled, _proto.setCascadeColorEnabled);

_proto = cc.MenuItem.prototype;
cc.defineGetterSetter(_proto, "opacityModifyRGB", _proto.isOpacityModifyRGB, _proto.setOpacityModifyRGB);
cc.defineGetterSetter(_proto, "opacity", _proto.getOpacity, _proto.setOpacity);
cc.defineGetterSetter(_proto, "cascadeOpacity", _proto.isCascadeOpacityEnabled, _proto.setCascadeOpacityEnabled);
cc.defineGetterSetter(_proto, "color", _proto.getColor, _proto.setColor);
cc.defineGetterSetter(_proto, "cascadeColor", _proto.isCascadeColorEnabled, _proto.setCascadeColorEnabled);

_proto = cc.MotionStreak.prototype;
cc.defineGetterSetter(_proto, "x", _proto.getPositionX, _proto.setPositionX);
cc.defineGetterSetter(_proto, "y", _proto.getPositionY, _proto.setPositionY);
cc.defineGetterSetter(_proto, "opacityModifyRGB", _proto.isOpacityModifyRGB, _proto.setOpacityModifyRGB);
cc.defineGetterSetter(_proto, "opacity", _proto.getOpacity, _proto.setOpacity);
cc.defineGetterSetter(_proto, "opacityModifyRGB", _proto.isOpacityModifyRGB, _proto.setOpacityModifyRGB);
cc.defineGetterSetter(_proto, "color", _proto.getColor, _proto.setColor);
cc.defineGetterSetter(_proto, "cascadeColor", _proto.isCascadeColorEnabled, _proto.setCascadeColorEnabled);

_proto = cc.ParticleSystem.prototype;
cc.defineGetterSetter(_proto, "rotation", _proto.getRotation, _proto.setRotation);
cc.defineGetterSetter(_proto, "scale", _proto.getScale, _proto.setScale);
cc.defineGetterSetter(_proto, "scaleX", _proto.getScaleX, _proto.setScaleX);
cc.defineGetterSetter(_proto, "scaleY", _proto.getScaleY, _proto.setScaleY);

_proto = cc.ProgressTimer.prototype;
cc.defineGetterSetter(_proto, "opacity", _proto.getOpacity, _proto.setOpacity);
cc.defineGetterSetter(_proto, "opacityModifyRGB", _proto.isOpacityModifyRGB, _proto.setOpacityModifyRGB);
cc.defineGetterSetter(_proto, "color", _proto.getColor, _proto.setColor);

_proto = cc.TextFieldTTF.prototype;
cc.defineGetterSetter(_proto, "string", _proto.getString, _proto.setString);



// Extends
var _proto = cc.ClippingNode.prototype;
cc.defineGetterSetter(_proto, "alphaThreshold", _proto.getAlphaThreshold, _proto.setAlphaThreshold);
cc.defineGetterSetter(_proto, "inverted", _proto.getInverted, _proto.setInverted);
cc.defineGetterSetter(_proto, "stencil", _proto.getStencil, _proto.setStencil);

_proto = cc.AtlasNode.prototype;
cc.defineGetterSetter(_proto, "texture", _proto.getTexture, _proto.setTexture);
cc.defineGetterSetter(_proto, "textureAtlas", _proto.getTextureAtlas, _proto.setTextureAtlas);
cc.defineGetterSetter(_proto, "quadsToDraw", _proto.getQuadsToDraw, _proto.setQuadsToDraw);

_proto = cc.Node.prototype;
cc.defineGetterSetter(_proto, "x", _proto.getPositionX, _proto.setPositionX);
cc.defineGetterSetter(_proto, "y", _proto.getPositionY, _proto.setPositionY);
cc.defineGetterSetter(_proto, "width", _proto._getWidth, _proto._setWidth);
cc.defineGetterSetter(_proto, "height", _proto._getHeight, _proto._setHeight);
cc.defineGetterSetter(_proto, "anchorX", _proto._getAnchorX, _proto._setAnchorX);
cc.defineGetterSetter(_proto, "anchorY", _proto._getAnchorY, _proto._setAnchorY);
cc.defineGetterSetter(_proto, "skewX", _proto.getSkewX, _proto.setSkewX);
cc.defineGetterSetter(_proto, "skewY", _proto.getSkewY, _proto.setSkewY);
cc.defineGetterSetter(_proto, "zIndex", _proto.getLocalZOrder, _proto.setLocalZOrder);
cc.defineGetterSetter(_proto, "vertexZ", _proto.getVertexZ, _proto.setVertexZ);
cc.defineGetterSetter(_proto, "rotation", _proto.getRotation, _proto.setRotation);
cc.defineGetterSetter(_proto, "rotationX", _proto.getRotationX, _proto.setRotationX);
cc.defineGetterSetter(_proto, "rotationY", _proto.getRotationY, _proto.setRotationY);
cc.defineGetterSetter(_proto, "scale", _proto.getScale, _proto.setScale);
cc.defineGetterSetter(_proto, "scaleX", _proto.getScaleX, _proto.setScaleX);
cc.defineGetterSetter(_proto, "scaleY", _proto.getScaleY, _proto.setScaleY);
cc.defineGetterSetter(_proto, "children", _proto.getChildren);
cc.defineGetterSetter(_proto, "childrenCount", _proto.getChildrenCount);
cc.defineGetterSetter(_proto, "parent", _proto.getParent, _proto.setParent);
cc.defineGetterSetter(_proto, "visible", _proto.isVisible, _proto.setVisible);
cc.defineGetterSetter(_proto, "running", _proto.isRunning);
cc.defineGetterSetter(_proto, "ignoreAnchor", _proto.isIgnoreAnchorPointForPosition, _proto.ignoreAnchorPointForPosition);
cc.defineGetterSetter(_proto, "actionManager", _proto.getActionManager, _proto.setActionManager);
cc.defineGetterSetter(_proto, "scheduler", _proto.getScheduler, _proto.setScheduler);
cc.defineGetterSetter(_proto, "shaderProgram", _proto.getShaderProgram, _proto.setShaderProgram);
cc.defineGetterSetter(_proto, "glServerState", _proto.getGLServerState, _proto.setGLServerState);
cc.defineGetterSetter(_proto, "tag", _proto.getTag, _proto.setTag);
cc.defineGetterSetter(_proto, "userObject", _proto.getUserObject, _proto.setUserObject);
cc.defineGetterSetter(_proto, "arrivalOrder", _proto.getArrivalOrder, _proto.setArrivalOrder);

_proto = cc.NodeRGBA.prototype;
cc.defineGetterSetter(_proto, "opacity", _proto.getOpacity, _proto.setOpacity);
cc.defineGetterSetter(_proto, "opacityModifyRGB", _proto.isOpacityModifyRGB, _proto.setOpacityModifyRGB);
cc.defineGetterSetter(_proto, "cascadeOpacity", _proto.isCascadeOpacityEnabled, _proto.setCascadeOpacityEnabled);
cc.defineGetterSetter(_proto, "color", _proto.getColor, _proto.setColor);
cc.defineGetterSetter(_proto, "cascadeColor", _proto.isCascadeColorEnabled, _proto.setCascadeColorEnabled);

_proto = cc.LabelTTF.prototype;
cc.defineGetterSetter(_proto, "string", _proto.getString, _proto.setString);
cc.defineGetterSetter(_proto, "textAlign", _proto.getHorizontalAlignment, _proto.setHorizontalAlignment);
cc.defineGetterSetter(_proto, "verticalAlign", _proto.getVerticalAlignment, _proto.setVerticalAlignment);
cc.defineGetterSetter(_proto, "fontSize", _proto.getFontSize, _proto.setFontSize);
cc.defineGetterSetter(_proto, "fontName", _proto.getFontName, _proto.setFontName);
cc.defineGetterSetter(_proto, "font", _proto._getFont, _proto._setFont);
cc.defineGetterSetter(_proto, "boundingWidth", _proto._getBoundingWidth, _proto._setBoundingWidth);
cc.defineGetterSetter(_proto, "boundingHeight", _proto._getBoundingHeight, _proto._setBoundingHeight);
cc.defineGetterSetter(_proto, "fillStyle", _proto._getFillStyle, _proto.setFontFillColor);
cc.defineGetterSetter(_proto, "strokeStyle", _proto._getStrokeStyle, _proto._setStrokeStyle);
cc.defineGetterSetter(_proto, "lineWidth", _proto._getLineWidth, _proto._setLineWidth);
cc.defineGetterSetter(_proto, "shadowOffsetX", _proto._getShadowOffsetX, _proto._setShadowOffsetX);
cc.defineGetterSetter(_proto, "shadowOffsetY", _proto._getShadowOffsetY, _proto._setShadowOffsetY);
cc.defineGetterSetter(_proto, "shadowOpacity", _proto._getShadowOpacity, _proto._setShadowOpacity);
cc.defineGetterSetter(_proto, "shadowBlur", _proto._getShadowBlur, _proto._setShadowBlur);
cc.defineGetterSetter(_proto, "opacity", _proto.getOpacity, _proto.setOpacity);
cc.defineGetterSetter(_proto, "opacityModifyRGB", _proto.isOpacityModifyRGB, _proto.setOpacityModifyRGB);
cc.defineGetterSetter(_proto, "cascadeOpacity", _proto.isCascadeOpacityEnabled, _proto.setCascadeOpacityEnabled);
cc.defineGetterSetter(_proto, "color", _proto.getColor, _proto.setColor);
cc.defineGetterSetter(_proto, "cascadeColor", _proto.isCascadeColorEnabled, _proto.setCascadeColorEnabled);

_proto = cc.LayerRGBA.prototype;
cc.defineGetterSetter(_proto, "opacityModifyRGB", _proto.isOpacityModifyRGB, _proto.setOpacityModifyRGB);
cc.defineGetterSetter(_proto, "opacity", _proto.getOpacity, _proto.setOpacity);
cc.defineGetterSetter(_proto, "cascadeOpacity", _proto.isCascadeOpacityEnabled, _proto.setCascadeOpacityEnabled);
cc.defineGetterSetter(_proto, "color", _proto.getColor, _proto.setColor);
cc.defineGetterSetter(_proto, "cascadeColor", _proto.isCascadeColorEnabled, _proto.setCascadeColorEnabled);

_proto = cc.LayerColor.prototype;
cc.defineGetterSetter(_proto, "width", _proto._getWidth, _proto._setWidth);
cc.defineGetterSetter(_proto, "height", _proto._getHeight, _proto._setHeight);
cc.defineGetterSetter(_proto, "opacity", _proto.getOpacity, _proto.setOpacity);
cc.defineGetterSetter(_proto, "opacityModifyRGB", _proto.isOpacityModifyRGB, _proto.setOpacityModifyRGB);
cc.defineGetterSetter(_proto, "cascadeOpacity", _proto.isCascadeOpacityEnabled, _proto.setCascadeOpacityEnabled);
cc.defineGetterSetter(_proto, "color", _proto.getColor, _proto.setColor);
cc.defineGetterSetter(_proto, "cascadeColor", _proto.isCascadeColorEnabled, _proto.setCascadeColorEnabled);

_proto = cc.LayerGradient.prototype;
cc.defineGetterSetter(_proto, "startColor", _proto.getStartColor, _proto.setStartColor);
cc.defineGetterSetter(_proto, "endColor", _proto.getEndColor, _proto.setEndColor);
cc.defineGetterSetter(_proto, "startOpacity", _proto.getStartOpacity, _proto.setStartOpacity);
cc.defineGetterSetter(_proto, "endOpacity", _proto.getEndOpacity, _proto.setEndOpacity);
cc.defineGetterSetter(_proto, "vector", _proto.getVector, _proto.setVector);
cc.defineGetterSetter(_proto, "compresseInterpolation", _proto.isCompressedInterpolation, _proto.setCompressedInterpolation);
cc.defineGetterSetter(_proto, "opacity", _proto.getOpacity, _proto.setOpacity);
cc.defineGetterSetter(_proto, "opacityModifyRGB", _proto.isOpacityModifyRGB, _proto.setOpacityModifyRGB);
cc.defineGetterSetter(_proto, "cascadeOpacity", _proto.isCascadeOpacityEnabled, _proto.setCascadeOpacityEnabled);
cc.defineGetterSetter(_proto, "color", _proto.getColor, _proto.setColor);
cc.defineGetterSetter(_proto, "cascadeColor", _proto.isCascadeColorEnabled, _proto.setCascadeColorEnabled);

_proto = cc.Sprite.prototype;
cc.defineGetterSetter(_proto, "dirty", _proto.getDirty, _proto.setDirty);
cc.defineGetterSetter(_proto, "flippedX", _proto.isFlippedX, _proto.setFlippedX);
cc.defineGetterSetter(_proto, "flippedY", _proto.isFlippedY, _proto.setFlippedY);
cc.defineGetterSetter(_proto, "offsetX", _proto._getOffsetX);
cc.defineGetterSetter(_proto, "offsetY", _proto._getOffsetY);
cc.defineGetterSetter(_proto, "atlasIndex", _proto.getAtlasIndex, _proto.setAtlasIndex);
cc.defineGetterSetter(_proto, "texture", _proto.getTexture, _proto.setTexture);
cc.defineGetterSetter(_proto, "textureRectRotated", _proto.isTextureRectRotated);
cc.defineGetterSetter(_proto, "textureAtlas", _proto.getTextureAtlas, _proto.setTextureAtlas);
cc.defineGetterSetter(_proto, "batchNode", _proto.getBatchNode, _proto.setBatchNode);
cc.defineGetterSetter(_proto, "quad", _proto.getQuad);
cc.defineGetterSetter(_proto, "opacity", _proto.getOpacity, _proto.setOpacity);
cc.defineGetterSetter(_proto, "opacityModifyRGB", _proto.isOpacityModifyRGB, _proto.setOpacityModifyRGB);
cc.defineGetterSetter(_proto, "cascadeOpacity", _proto.isCascadeOpacityEnabled, _proto.setCascadeOpacityEnabled);
cc.defineGetterSetter(_proto, "color", _proto.getColor, _proto.setColor);
cc.defineGetterSetter(_proto, "cascadeColor", _proto.isCascadeColorEnabled, _proto.setCascadeColorEnabled);

_proto = cc.SpriteBatchNode.prototype;
cc.defineGetterSetter(_proto, "textureAtlas", _proto.getTextureAtlas, _proto.setTextureAtlas);
cc.defineGetterSetter(_proto, "descendants", _proto.getDescendants);
cc.defineGetterSetter(_proto, "texture", _proto.getTexture, _proto.setTexture);

_proto = cc.Texture2D.prototype;
cc.defineGetterSetter(_proto, "name", _proto.getName);
cc.defineGetterSetter(_proto, "pixelFormat", _proto.getPixelFormat);
cc.defineGetterSetter(_proto, "defaultPixelFormat", _proto.getDefaultAlphaPixelFormat, _proto.setDefaultAlphaPixelFormat);
cc.defineGetterSetter(_proto, "pixelsWidth", _proto.getPixelsWide);
cc.defineGetterSetter(_proto, "pixelsHeight", _proto.getPixelsHigh);
cc.defineGetterSetter(_proto, "width", _proto._getWidth);
cc.defineGetterSetter(_proto, "height", _proto._getHeight);
cc.defineGetterSetter(_proto, "shaderProgram", _proto.getShaderProgram, _proto.setShaderProgram);
cc.defineGetterSetter(_proto, "maxS", _proto.getMaxS, _proto.setMaxS);
cc.defineGetterSetter(_proto, "maxT", _proto.getMaxT, _proto.setMaxT);

_proto = cc.LabelAtlas.prototype;
cc.defineGetterSetter(_proto, "string", _proto.getString, _proto.setString);
cc.defineGetterSetter(_proto, "opacity", _proto.getOpacity, _proto.setOpacity);

_proto = cc.LabelBMFont.prototype;
cc.defineGetterSetter(_proto, "string", _proto.getString, _proto._setStringForSetter);
cc.defineGetterSetter(_proto, "textAlign", _proto._getAlignment, _proto.setAlignment);
cc.defineGetterSetter(_proto, "boundingWidth", _proto._getBoundingWidth, _proto.setBoundingWidth);

_proto = cc.Menu.prototype;
cc.defineGetterSetter(_proto, "enabled", _proto.getEnabled, _proto.setEnabled);

_proto = cc.MenuItem.prototype;
cc.defineGetterSetter(_proto, "enabled", _proto.isEnabled, _proto.setEnabled);

_proto = cc.MenuItemLabel.prototype;
cc.defineGetterSetter(_proto, "string", _proto.getString, _proto.setString);
cc.defineGetterSetter(_proto, "label", _proto.getLabel, _proto.setLabel);
cc.defineGetterSetter(_proto, "disabledColor", _proto.getDisabledColor, _proto.setDisabledColor);

_proto = cc.MenuItemFont.prototype;
cc.defineGetterSetter(_proto, "fontSize", _proto.fontSize, _proto.setFontSize);
cc.defineGetterSetter(_proto, "fontName", _proto.fontName, _proto.setFontName);

_proto = cc.MenuItemSprite.prototype;
cc.defineGetterSetter(_proto, "normalImage", _proto.getNormalImage, _proto.setNormalImage);
cc.defineGetterSetter(_proto, "selectedImage", _proto.getSelectedImage, _proto.setSelectedImage);
cc.defineGetterSetter(_proto, "disabledImage", _proto.getDisabledImage, _proto.setDisabledImage);

_proto = cc.ParticleBatchNode.prototype;
cc.defineGetterSetter(_proto, "textureAtlas", _proto.getTextureAtlas, _proto.setTextureAtlas);
cc.defineGetterSetter(_proto, "texture", _proto.getTexture, _proto.setTexture);

_proto = cc.ParticleSystem.prototype;
cc.defineGetterSetter(_proto, "opacityModifyRGB", _proto.isOpacityModifyRGB, _proto.setOpacityModifyRGB);
cc.defineGetterSetter(_proto, "batchNode", _proto.getBatchNode, _proto.setBatchNode);
cc.defineGetterSetter(_proto, "active", _proto.isActive);
cc.defineGetterSetter(_proto, "shapeType", _proto.getShapeType, _proto.setShapeType);
cc.defineGetterSetter(_proto, "atlasIndex", _proto.getAtlasIndex, _proto.setAtlasIndex);
cc.defineGetterSetter(_proto, "particleCount", _proto.getParticleCount, _proto.setParticleCount);
cc.defineGetterSetter(_proto, "duration", _proto.getDuration, _proto.setDuration);
cc.defineGetterSetter(_proto, "sourcePos", _proto.getSourcePosition, _proto.setSourcePosition);
cc.defineGetterSetter(_proto, "posVar", _proto.getPosVar, _proto.setPosVar);
cc.defineGetterSetter(_proto, "life", _proto.getLife, _proto.setLife);
cc.defineGetterSetter(_proto, "lifeVar", _proto.getLifeVar, _proto.setLifeVar);
cc.defineGetterSetter(_proto, "angle", _proto.getAngle, _proto.setAngle);
cc.defineGetterSetter(_proto, "angleVar", _proto.getAngleVar, _proto.setAngleVar);
cc.defineGetterSetter(_proto, "startSize", _proto.getStartSize, _proto.setStartSize);
cc.defineGetterSetter(_proto, "startSizeVar", _proto.getStartSizeVar, _proto.setStartSizeVar);
cc.defineGetterSetter(_proto, "endSize", _proto.getEndSize, _proto.setEndSize);
cc.defineGetterSetter(_proto, "endSizeVar", _proto.getEndSizeVar, _proto.setEndSizeVar);
cc.defineGetterSetter(_proto, "startSpin", _proto.getStartSpin, _proto.setStartSpin);
cc.defineGetterSetter(_proto, "startSpinVar", _proto.getStartSpinVar, _proto.setStartSpinVar);
cc.defineGetterSetter(_proto, "endSpin", _proto.getEndSpin, _proto.setEndSpin);
cc.defineGetterSetter(_proto, "endSpinVar", _proto.getEndSpinVar, _proto.setEndSpinVar);
cc.defineGetterSetter(_proto, "gravity", _proto.getGravity, _proto.setGravity);
cc.defineGetterSetter(_proto, "speed", _proto.getSpeed, _proto.setSpeed);
cc.defineGetterSetter(_proto, "speedVar", _proto.getSpeedVar, _proto.setSpeedVar);
cc.defineGetterSetter(_proto, "tangentialAccel", _proto.getTangentialAccel, _proto.setTangentialAccel);
cc.defineGetterSetter(_proto, "tangentialAccelVar", _proto.getTangentialAccelVar, _proto.setTangentialAccelVar);
cc.defineGetterSetter(_proto, "tangentialAccel", _proto.getTangentialAccel, _proto.setTangentialAccel);
cc.defineGetterSetter(_proto, "tangentialAccelVar", _proto.getTangentialAccelVar, _proto.setTangentialAccelVar);
cc.defineGetterSetter(_proto, "rotationIsDir", _proto.getRotationIsDir, _proto.setRotationIsDir);
cc.defineGetterSetter(_proto, "startRadius", _proto.getStartRadius, _proto.setStartRadius);
cc.defineGetterSetter(_proto, "startRadiusVar", _proto.getStartRadiusVar, _proto.setStartRadiusVar);
cc.defineGetterSetter(_proto, "endRadius", _proto.getEndRadius, _proto.setEndRadius);
cc.defineGetterSetter(_proto, "endRadiusVar", _proto.getEndRadiusVar, _proto.setEndRadiusVar);
cc.defineGetterSetter(_proto, "rotatePerS", _proto.getRotatePerSecond, _proto.setRotatePerSecond);
cc.defineGetterSetter(_proto, "rotatePerSVar", _proto.getRotatePerSecondVar, _proto.setRotatePerSecondVar);
cc.defineGetterSetter(_proto, "startColor", _proto.getStartColor, _proto.setStartColor);
cc.defineGetterSetter(_proto, "startColorVar", _proto.getStartColorVar, _proto.setStartColorVar);
cc.defineGetterSetter(_proto, "endColor", _proto.getEndColor, _proto.setEndColor);
cc.defineGetterSetter(_proto, "endColorVar", _proto.getEndColorVar, _proto.setEndColorVar);
cc.defineGetterSetter(_proto, "emissionRate", _proto.getEmissionRate, _proto.setEmissionRate);
cc.defineGetterSetter(_proto, "emitterMode", _proto.getEmitterMode, _proto.setEmitterMode);
cc.defineGetterSetter(_proto, "positionType", _proto.getPositionType, _proto.setPositionType);
cc.defineGetterSetter(_proto, "totalParticles", _proto.getTotalParticles, _proto.setTotalParticles);
cc.defineGetterSetter(_proto, "autoRemoveOnFinish", _proto.getAutoRemoveOnFinish, _proto.setAutoRemoveOnFinish);
cc.defineGetterSetter(_proto, "texture", _proto.getTexture, _proto.setTexture);

_proto = cc.ProgressTimer.prototype;
cc.defineGetterSetter(_proto, "midPoint", _proto.getMidpoint, _proto.setMidpoint);
cc.defineGetterSetter(_proto, "barChangeRate", _proto.getBarChangeRate, _proto.setBarChangeRate);
cc.defineGetterSetter(_proto, "type", _proto.getType, _proto.setType);
cc.defineGetterSetter(_proto, "percentage", _proto.getPercentage, _proto.setPercentage);
cc.defineGetterSetter(_proto, "sprite", _proto.getSprite, _proto.setSprite);
cc.defineGetterSetter(_proto, "reverseDir", _proto.isReverseDirection, _proto.setReverseDirection);

_proto = cc.RenderTexture.prototype;
cc.defineGetterSetter(_proto, "sprite", _proto.getSprite, _proto.setSprite);
cc.defineGetterSetter(_proto, "clearFlags", _proto.getClearFlags, _proto.setClearFlags);
cc.defineGetterSetter(_proto, "clearDepthVal", _proto.getClearDepthVal, _proto.setClearDepthVal);
cc.defineGetterSetter(_proto, "clearStencilVal", _proto.getClearStencilVal, _proto.setClearStencilVal);
cc.defineGetterSetter(_proto, "clearColorVal", _proto.getClearColor, _proto.setClearColor);
cc.defineGetterSetter(_proto, "autoDraw", _proto.getAutoDraw, _proto.setAutoDraw);

_proto = cc.NodeGrid.prototype;
cc.defineGetterSetter(_proto, "grid", _proto.getGrid, _proto.setGrid);
cc.defineGetterSetter(_proto, "target", null, _proto.setTarget);

_proto = cc.TMXLayer.prototype;
cc.defineGetterSetter(_proto, "tiles", _proto.getTiles, _proto.setTiles);
cc.defineGetterSetter(_proto, "tileset", _proto.getTileset, _proto.setTileset);
cc.defineGetterSetter(_proto, "layerOrientation", _proto.getLayerOrientation, _proto.setLayerOrientation);
cc.defineGetterSetter(_proto, "properties", _proto.getProperties, _proto.setProperties);
cc.defineGetterSetter(_proto, "layerName", _proto.getLayerName, _proto.setLayerName);
cc.defineGetterSetter(_proto, "layerWidth", _proto._getLayerWidth, _proto._setLayerWidth);
cc.defineGetterSetter(_proto, "layerHeight", _proto._getLayerHeight, _proto._setLayerHeight);
cc.defineGetterSetter(_proto, "tileWidth", _proto._getTileWidth, _proto._setTileWidth);
cc.defineGetterSetter(_proto, "tileHeight", _proto._getTileHeight, _proto._setTileHeight);
cc.defineGetterSetter(_proto, "texture", _proto.getTexture, _proto.setTexture);

_proto = cc.TMXTiledMap.prototype;
cc.defineGetterSetter(_proto, "properties", _proto.getProperties, _proto.setProperties);
cc.defineGetterSetter(_proto, "mapOrientation", _proto.getMapOrientation, _proto.setMapOrientation);
cc.defineGetterSetter(_proto, "objectGroups", _proto.getObjectGroups, _proto.setObjectGroups);
cc.defineGetterSetter(_proto, "mapWidth", _proto._getMapWidth, _proto._setMapWidth);
cc.defineGetterSetter(_proto, "mapHeight", _proto._getMapHeight, _proto._setMapHeight);
cc.defineGetterSetter(_proto, "tileWidth", _proto._getTileWidth, _proto._setTileWidth);
cc.defineGetterSetter(_proto, "tileHeight", _proto._getTileHeight, _proto._setTileHeight);
