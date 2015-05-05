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

var _proto = ccui.Widget.prototype;
cc.defineGetterSetter(_proto, "xPercent", _proto._getXPercent, _proto._setXPercent);
cc.defineGetterSetter(_proto, "yPercent", _proto._getYPercent, _proto._setYPercent);
cc.defineGetterSetter(_proto, "widthPercent", _proto._getWidthPercent, _proto._setWidthPercent);
cc.defineGetterSetter(_proto, "heightPercent", _proto._getHeightPercent, _proto._setHeightPercent);
cc.defineGetterSetter(_proto, "widgetParent", _proto.getWidgetParent);
cc.defineGetterSetter(_proto, "enabled", _proto.isEnabled, _proto.setEnabled);
cc.defineGetterSetter(_proto, "focused", _proto.isFocused, _proto.setFocused);
cc.defineGetterSetter(_proto, "sizeType", _proto.getSizeType, _proto.setSizeType);
cc.defineGetterSetter(_proto, "widgetType", _proto.getWidgetType);
cc.defineGetterSetter(_proto, "touchEnabled", _proto.isTouchEnabled, _proto.setTouchEnabled);
cc.defineGetterSetter(_proto, "updateEnabled", _proto.isUpdateEnabled, _proto.setUpdateEnabled);
cc.defineGetterSetter(_proto, "bright", _proto.isBright, _proto.setBright);
cc.defineGetterSetter(_proto, "name", _proto.getName, _proto.setName);
cc.defineGetterSetter(_proto, "actionTag", _proto.getActionTag, _proto.setActionTag);
cc.defineGetterSetter(_proto, "x", _proto.getPositionX, _proto.setPositionX);
cc.defineGetterSetter(_proto, "y", _proto.getPositionY, _proto.setPositionY);
cc.defineGetterSetter(_proto, "width", _proto._getWidth, _proto._setWidth);
cc.defineGetterSetter(_proto, "height", _proto._getHeight, _proto._setHeight);
cc.defineGetterSetter(_proto, "flippedX", _proto.isFlippedX, _proto.setFlippedX);
cc.defineGetterSetter(_proto, "flippedY", _proto.isFlippedY, _proto.setFlippedY);
cc.defineGetterSetter(_proto, "children", _proto.getChildren);
cc.defineGetterSetter(_proto, "childrenCount", _proto.getChildrenCount);

_proto = ccui.Layout.prototype;
cc.defineGetterSetter(_proto, "clippingEnabled", _proto.isClippingEnabled, _proto.setClippingEnabled);
cc.defineGetterSetter(_proto, "clippingType", _proto.setClippingType);
cc.defineGetterSetter(_proto, "layoutType", _proto.getLayoutType, _proto.setLayoutType);

_proto = ccui.Button.prototype;
cc.defineGetterSetter(_proto, "width", _proto._getWidth, _proto._setWidth);
cc.defineGetterSetter(_proto, "height", _proto._getHeight, _proto._setHeight);
cc.defineGetterSetter(_proto, "titleText", _proto.getTitleText, _proto.setTitleText);
cc.defineGetterSetter(_proto, "titleFont", _proto._getTitleFont, _proto._setTitleFont);
cc.defineGetterSetter(_proto, "titleFontSize", _proto.getTitleFontSize, _proto.setTitleFontSize);
cc.defineGetterSetter(_proto, "titleFontName", _proto.getTitleFontName, _proto.setTitleFontName);
cc.defineGetterSetter(_proto, "titleFontColor", _proto.getTitleFontColor, _proto.setTitleFontColor);
cc.defineGetterSetter(_proto, "pressedActionEnabled", _proto.getPressedActionEnabled, _proto.setPressedActionEnabled);
cc.defineGetterSetter(_proto, "anchorX", _proto._getAnchorX, _proto._setAnchorX);
cc.defineGetterSetter(_proto, "anchorY", _proto._getAnchorY, _proto._setAnchorY);
cc.defineGetterSetter(_proto, "flippedX", _proto.isFlippedX, _proto.setFlippedX);
cc.defineGetterSetter(_proto, "flippedY", _proto.isFlippedY, _proto.setFlippedY);
cc.defineGetterSetter(_proto, "color", _proto.getColor, _proto.setColor);

_proto = ccui.CheckBox.prototype;
cc.defineGetterSetter(_proto, "selected", _proto.getSelected, _proto.setSelected);
cc.defineGetterSetter(_proto, "anchorX", _proto._getAnchorX, _proto._setAnchorX);
cc.defineGetterSetter(_proto, "anchorY", _proto._getAnchorY, _proto._setAnchorY);
cc.defineGetterSetter(_proto, "flippedX", _proto.isFlippedX, _proto.setFlippedX);
cc.defineGetterSetter(_proto, "flippedY", _proto.isFlippedY, _proto.setFlippedY);
cc.defineGetterSetter(_proto, "width", _proto._getWidth, _proto._setWidth);
cc.defineGetterSetter(_proto, "height", _proto._getHeight, _proto._setHeight);

_proto = ccui.Text.prototype;
cc.defineGetterSetter(_proto, "boundingWidth", _proto._getBoundingWidth, _proto._setBoundingWidth);
cc.defineGetterSetter(_proto, "boundingHeight", _proto._getBoundingHeight, _proto._setBoundingHeight);
cc.defineGetterSetter(_proto, "string", _proto.getString, _proto.setString);
cc.defineGetterSetter(_proto, "stringLength", _proto.getStringLength);
cc.defineGetterSetter(_proto, "font", _proto._getFont, _proto._setFont);
cc.defineGetterSetter(_proto, "fontName", _proto.getFontName, _proto.setFontName);
cc.defineGetterSetter(_proto, "fontSize", _proto.getFontSize, _proto.setFontSize);
cc.defineGetterSetter(_proto, "textAlign", _proto.getHorizontalAlignment, _proto.setTextHorizontalAlignment);
cc.defineGetterSetter(_proto, "verticalAlign", _proto.getVerticalAlignment, _proto.setTextVerticalAlignment);
cc.defineGetterSetter(_proto, "touchScaleEnabled", _proto.getTouchScaleEnabled, _proto.setTouchScaleEnabled);
cc.defineGetterSetter(_proto, "width", _proto._getWidth, _proto._setWidth);
cc.defineGetterSetter(_proto, "height", _proto._getHeight, _proto._setHeight);
cc.defineGetterSetter(_proto, "anchorX", _proto._getAnchorX, _proto._setAnchorX);
cc.defineGetterSetter(_proto, "anchorY", _proto._getAnchorY, _proto._setAnchorY);
cc.defineGetterSetter(_proto, "scaleX", _proto.getScaleX, _proto.setScaleX);
cc.defineGetterSetter(_proto, "scaleY", _proto.getScaleY, _proto.setScaleY);
cc.defineGetterSetter(_proto, "flippedX", _proto.isFlippedX, _proto.setFlippedX);
cc.defineGetterSetter(_proto, "flippedY", _proto.isFlippedY, _proto.setFlippedY);

_proto = ccui.TextAtlas.prototype;
cc.defineGetterSetter(_proto, "string", _proto.getString, _proto.setString);
cc.defineGetterSetter(_proto, "width", _proto._getWidth, _proto._setWidth);
cc.defineGetterSetter(_proto, "height", _proto._getHeight, _proto._setHeight);
cc.defineGetterSetter(_proto, "anchorX", _proto._getAnchorX, _proto._setAnchorX);
cc.defineGetterSetter(_proto, "anchorY", _proto._getAnchorY, _proto._setAnchorY);

_proto = ccui.TextBMFont.prototype;
cc.defineGetterSetter(_proto, "string", _proto.getString, _proto.setString);
cc.defineGetterSetter(_proto, "width", _proto._getWidth, _proto._setWidth);
cc.defineGetterSetter(_proto, "height", _proto._getHeight, _proto._setHeight);
cc.defineGetterSetter(_proto, "anchorX", _proto._getAnchorX, _proto._setAnchorX);
cc.defineGetterSetter(_proto, "anchorY", _proto._getAnchorY, _proto._setAnchorY);

_proto = ccui.LoadingBar.prototype;
cc.defineGetterSetter(_proto, "direction", _proto.getDirection, _proto.setDirection);
cc.defineGetterSetter(_proto, "percent", _proto.getPercent, _proto.setPercent);
cc.defineGetterSetter(_proto, "width", _proto._getWidth, _proto._setWidth);
cc.defineGetterSetter(_proto, "height", _proto._getHeight, _proto._setHeight);

_proto = ccui.Slider.prototype;
cc.defineGetterSetter(_proto, "percent", _proto.getPercent, _proto.setPercent);
cc.defineGetterSetter(_proto, "width", _proto._getWidth, _proto._setWidth);
cc.defineGetterSetter(_proto, "height", _proto._getHeight, _proto._setHeight);

_proto = ccui.TextField.prototype;
cc.defineGetterSetter(_proto, "maxLengthEnabled", _proto.isMaxLengthEnabled, _proto.setMaxLengthEnabled);
cc.defineGetterSetter(_proto, "maxLength", _proto.getMaxLength, _proto.setMaxLength);
cc.defineGetterSetter(_proto, "passwordEnabled", _proto.isPasswordEnabled, _proto.setPasswordEnabled);
cc.defineGetterSetter(_proto, "string", _proto.getString, _proto.setString);
cc.defineGetterSetter(_proto, "font", _proto._getFont, _proto._setFont);
cc.defineGetterSetter(_proto, "fontSize", _proto.getFontSize, _proto.setFontSize);
cc.defineGetterSetter(_proto, "fontName", _proto.getFontName, _proto.setFontName);
cc.defineGetterSetter(_proto, "width", _proto._getWidth, _proto._setWidth);
cc.defineGetterSetter(_proto, "height", _proto._getHeight, _proto._setHeight);
cc.defineGetterSetter(_proto, "anchorX", _proto._getAnchorX, _proto._setAnchorX);
cc.defineGetterSetter(_proto, "anchorY", _proto._getAnchorY, _proto._setAnchorY);

_proto = ccui.ScrollView.prototype;
cc.defineGetterSetter(_proto, "innerWidth", _proto._getInnerWidth, _proto._setInnerWidth);
cc.defineGetterSetter(_proto, "innerHeight", _proto._getInnerHeight, _proto._setInnerHeight);
cc.defineGetterSetter(_proto, "bounceEnabled", _proto.getBounceEnabled, _proto.setBounceEnabled);
cc.defineGetterSetter(_proto, "inertiaScrollEnabled", _proto.getInertiaScrollEnabled, _proto.setInertiaScrollEnabled);
cc.defineGetterSetter(_proto, "children", _proto.getChildren);
cc.defineGetterSetter(_proto, "childrenCount", _proto.getChildrenCount);
cc.defineGetterSetter(_proto, "layoutType", _proto.getLayoutType, _proto.setLayoutType);

_proto = cc.Scale9Sprite.prototype;
cc.defineGetterSetter(_proto, "width", _proto._getWidth, _proto._setWidth);
cc.defineGetterSetter(_proto, "height", _proto._getHeight, _proto._setHeight);
cc.defineGetterSetter(_proto, "color", _proto.getColor, _proto.setColor);
cc.defineGetterSetter(_proto, "opacity", _proto.getOpacity, _proto.setOpacity);
cc.defineGetterSetter(_proto, "opacityModifyRGB", _proto.isOpacityModifyRGB, _proto.setOpacityModifyRGB);
cc.defineGetterSetter(_proto, "preferredSize", _proto.getPreferredSize, _proto.setPreferredSize);
cc.defineGetterSetter(_proto, "capInsets", _proto.getCapInsets, _proto.setCapInsets);
cc.defineGetterSetter(_proto, "insetLeft", _proto.getInsetLeft, _proto.setInsetLeft);
cc.defineGetterSetter(_proto, "insetTop", _proto.getInsetTop, _proto.setInsetTop);
cc.defineGetterSetter(_proto, "insetRight", _proto.getInsetRight, _proto.setInsetRight);
cc.defineGetterSetter(_proto, "insetBottom", _proto.getInsetBottom, _proto.setInsetBottom);

_proto = cc.EditBox.prototype;
cc.defineGetterSetter(_proto, "font", null, _proto._setFont);
cc.defineGetterSetter(_proto, "fontName", null, _proto.setFontName);
cc.defineGetterSetter(_proto, "fontSize", null, _proto.setFontSize);
cc.defineGetterSetter(_proto, "string", _proto.getString, _proto.setString);
cc.defineGetterSetter(_proto, "maxLength", _proto.getMaxLength, _proto.setMaxLength);

_proto = ccui.ImageView.prototype;
cc.defineGetterSetter(_proto, "anchorX", _proto._getAnchorX, _proto._setAnchorX);
cc.defineGetterSetter(_proto, "anchorY", _proto._getAnchorY, _proto._setAnchorY);
cc.defineGetterSetter(_proto, "flippedX", _proto.isFlippedX, _proto.setFlippedX);
cc.defineGetterSetter(_proto, "flippedY", _proto.isFlippedY, _proto.setFlippedY);
cc.defineGetterSetter(_proto, "width", _proto._getWidth, _proto._setWidth);
cc.defineGetterSetter(_proto, "height", _proto._getHeight, _proto._setHeight);
