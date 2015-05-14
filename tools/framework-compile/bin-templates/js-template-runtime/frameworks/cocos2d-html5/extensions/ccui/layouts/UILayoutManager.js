/****************************************************************************
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
 * Gets the layout manager by ccui.Layout's layout type.
 * @param {Number} type
 * @returns {ccui.linearVerticalLayoutManager|ccui.linearHorizontalLayoutManager|ccui.relativeLayoutManager|null}
 */
ccui.getLayoutManager = function (type) {
    switch (type) {
        case ccui.Layout.LINEAR_VERTICAL:
            return ccui.linearVerticalLayoutManager;
        case ccui.Layout.LINEAR_HORIZONTAL:
            return ccui.linearHorizontalLayoutManager;
        case ccui.Layout.RELATIVE:
            return ccui.relativeLayoutManager;
    }
    return null;
};

/**
 * ccui.linearVerticalLayoutManager is a singleton object which is the linear vertical layout manager for ccui.Layout.
 * @class
 * @name ccui.linearVerticalLayoutManager
 */
ccui.linearVerticalLayoutManager = /** @lends ccui.linearVerticalLayoutManager# */{
    _doLayout: function(layout){
        var layoutSize = layout._getLayoutContentSize();
        var container = layout._getLayoutElements();
        var topBoundary = layoutSize.height;

        for (var i = 0, len = container.length; i < len; i++) {
            var child = container[i];
            if (child) {
                var layoutParameter = child.getLayoutParameter();

                if (layoutParameter){
                    var childGravity = layoutParameter.getGravity();
                    var ap = child.getAnchorPoint();
                    var cs = child.getContentSize();
                    var finalPosX = ap.x * cs.width;
                    var finalPosY = topBoundary - ((1.0 - ap.y) * cs.height);
                    switch (childGravity){
                        case ccui.LinearLayoutParameter.NONE:
                        case ccui.LinearLayoutParameter.LEFT:
                            break;
                        case ccui.LinearLayoutParameter.RIGHT:
                            finalPosX = layoutSize.width - ((1.0 - ap.x) * cs.width);
                            break;
                        case ccui.LinearLayoutParameter.CENTER_HORIZONTAL:
                            finalPosX = layoutSize.width / 2.0 - cs.width * (0.5 - ap.x);
                            break;
                        default:
                            break;
                    }
                    var mg = layoutParameter.getMargin();
                    finalPosX += mg.left;
                    finalPosY -= mg.top;
                    child.setPosition(finalPosX, finalPosY);
                    topBoundary = child.getPositionY() - ap.y * cs.height - mg.bottom;
                }
            }
        }
    }
};

/**
 * ccui.linearHorizontalLayoutManager is a singleton object which is the linear horizontal layout manager for ccui.Layout
 * @class
 * @name ccui.linearHorizontalLayoutManager
 */
ccui.linearHorizontalLayoutManager = /** @lends ccui.linearHorizontalLayoutManager# */{
    _doLayout: function(layout){
        var layoutSize = layout._getLayoutContentSize();
        var container = layout._getLayoutElements();
        var leftBoundary = 0.0;
        for (var i = 0, len = container.length;  i < len; i++) {
            var child = container[i];
            if (child) {
                var layoutParameter = child.getLayoutParameter();
                if (layoutParameter){
                    var childGravity = layoutParameter.getGravity();
                    var ap = child.getAnchorPoint();
                    var cs = child.getContentSize();
                    var finalPosX = leftBoundary + (ap.x * cs.width);
                    var finalPosY = layoutSize.height - (1.0 - ap.y) * cs.height;
                    switch (childGravity){
                        case ccui.LinearLayoutParameter.NONE:
                        case ccui.LinearLayoutParameter.TOP:
                            break;
                        case ccui.LinearLayoutParameter.BOTTOM:
                            finalPosY = ap.y * cs.height;
                            break;
                        case ccui.LinearLayoutParameter.CENTER_VERTICAL:
                            finalPosY = layoutSize.height / 2.0 - cs.height * (0.5 - ap.y);
                            break;
                        default:
                            break;
                    }
                    var mg = layoutParameter.getMargin();
                    finalPosX += mg.left;
                    finalPosY -= mg.top;
                    child.setPosition(finalPosX, finalPosY);
                    leftBoundary = child.getRightBoundary() + mg.right;
                }
            }
        }
    }
};

/**
 * ccui.relativeLayoutManager is the singleton object which is the relative layout manager for ccui.Layout, it has a _doLayout function to do layout.
 * @class
 * @name ccui.relativeLayoutManager
 */
ccui.relativeLayoutManager = /** @lends ccui.relativeLayoutManager# */{
    _unlayoutChildCount: 0,
    _widgetChildren: [],
    _widget: null,
    _finalPositionX:0,
    _finalPositionY:0,
    _relativeWidgetLP:null,

    _doLayout: function(layout){
        this._widgetChildren = this._getAllWidgets(layout);

        var locChildren = this._widgetChildren;
        while (this._unlayoutChildCount > 0) {
            for (var i = 0, len = locChildren.length;  i < len; i++) {
                this._widget = locChildren[i];

                var layoutParameter = this._widget.getLayoutParameter();
                if (layoutParameter){
                    if (layoutParameter._put)
                        continue;

                    var ret = this._calculateFinalPositionWithRelativeWidget(layout);
                    if (!ret)
                        continue;

                    this._calculateFinalPositionWithRelativeAlign();

                    this._widget.setPosition(this._finalPositionX, this._finalPositionY);
                    layoutParameter._put = true;
                }
            }
            this._unlayoutChildCount--;
        }
        this._widgetChildren.length = 0;
    },

    _getAllWidgets: function(layout){
        var container = layout._getLayoutElements();
        var locWidgetChildren = this._widgetChildren;
        locWidgetChildren.length = 0;
        for (var i = 0, len = container.length; i < len; i++){
            var child = container[i];
            if (child) {
                var layoutParameter = child.getLayoutParameter();
                layoutParameter._put = false;
                this._unlayoutChildCount++;
                locWidgetChildren.push(child);
            }
        }
        return locWidgetChildren;
    },

    _getRelativeWidget: function(widget){
        var relativeWidget = null;
        var layoutParameter = widget.getLayoutParameter();
        var relativeName = layoutParameter.getRelativeToWidgetName();

        if (relativeName && relativeName.length !== 0) {
            var locChildren =  this._widgetChildren;
            for(var i = 0, len = locChildren.length;  i  < len; i++){
                var child = locChildren[i];
                if (child){
                    var rlayoutParameter = child.getLayoutParameter();
                    if (rlayoutParameter &&  rlayoutParameter.getRelativeName() === relativeName) {
                        relativeWidget = child;
                        this._relativeWidgetLP = rlayoutParameter;
                        break;
                    }
                }
            }
        }
        return relativeWidget;
    },

    _calculateFinalPositionWithRelativeWidget: function(layout){
        var locWidget = this._widget;
        var ap = locWidget.getAnchorPoint();
        var cs = locWidget.getContentSize();

        this._finalPositionX = 0.0;
        this._finalPositionY = 0.0;

        var relativeWidget = this._getRelativeWidget(locWidget);
        var layoutParameter = locWidget.getLayoutParameter();
        var align = layoutParameter.getAlign();
        var layoutSize = layout._getLayoutContentSize();

        switch (align) {
            case ccui.RelativeLayoutParameter.NONE:
            case ccui.RelativeLayoutParameter.PARENT_TOP_LEFT:
                this._finalPositionX = ap.x * cs.width;
                this._finalPositionY = layoutSize.height - ((1.0 - ap.y) * cs.height);
                break;
            case ccui.RelativeLayoutParameter.PARENT_TOP_CENTER_HORIZONTAL:
                this._finalPositionX = layoutSize.width * 0.5 - cs.width * (0.5 - ap.x);
                this._finalPositionY = layoutSize.height - ((1.0 - ap.y) * cs.height);
                break;
            case ccui.RelativeLayoutParameter.PARENT_TOP_RIGHT:
                this._finalPositionX = layoutSize.width - ((1.0 - ap.x) * cs.width);
                this._finalPositionY = layoutSize.height - ((1.0 - ap.y) * cs.height);
                break;
            case ccui.RelativeLayoutParameter.PARENT_LEFT_CENTER_VERTICAL:
                this._finalPositionX = ap.x * cs.width;
                this._finalPositionY = layoutSize.height * 0.5 - cs.height * (0.5 - ap.y);
                break;
            case ccui.RelativeLayoutParameter.CENTER_IN_PARENT:
                this._finalPositionX = layoutSize.width * 0.5 - cs.width * (0.5 - ap.x);
                this._finalPositionY = layoutSize.height * 0.5 - cs.height * (0.5 - ap.y);
                break;
            case ccui.RelativeLayoutParameter.PARENT_RIGHT_CENTER_VERTICAL:
                this._finalPositionX = layoutSize.width - ((1.0 - ap.x) * cs.width);
                this._finalPositionY = layoutSize.height * 0.5 - cs.height * (0.5 - ap.y);
                break;
            case ccui.RelativeLayoutParameter.PARENT_LEFT_BOTTOM:
                this._finalPositionX = ap.x * cs.width;
                this._finalPositionY = ap.y * cs.height;
                break;
            case ccui.RelativeLayoutParameter.PARENT_BOTTOM_CENTER_HORIZONTAL:
                this._finalPositionX = layoutSize.width * 0.5 - cs.width * (0.5 - ap.x);
                this._finalPositionY = ap.y * cs.height;
                break;
            case ccui.RelativeLayoutParameter.PARENT_RIGHT_BOTTOM:
                this._finalPositionX = layoutSize.width - ((1.0 - ap.x) * cs.width);
                this._finalPositionY = ap.y * cs.height;
                break;

            case ccui.RelativeLayoutParameter.LOCATION_ABOVE_LEFTALIGN:
                if (relativeWidget){
                    if (this._relativeWidgetLP && !this._relativeWidgetLP._put)
                        return false;
                    this._finalPositionY = relativeWidget.getTopBoundary() + ap.y * cs.height;
                    this._finalPositionX = relativeWidget.getLeftBoundary() + ap.x * cs.width;
                }
                break;
            case ccui.RelativeLayoutParameter.LOCATION_ABOVE_CENTER:
                if (relativeWidget){
                    if (this._relativeWidgetLP && !this._relativeWidgetLP._put)
                        return false;
                    var rbs = relativeWidget.getContentSize();
                    this._finalPositionY = relativeWidget.getTopBoundary() + ap.y * cs.height;
                    this._finalPositionX = relativeWidget.getLeftBoundary() + rbs.width * 0.5 + ap.x * cs.width - cs.width * 0.5;
                }
                break;
            case ccui.RelativeLayoutParameter.LOCATION_ABOVE_RIGHTALIGN:
                if (relativeWidget) {
                    if (this._relativeWidgetLP && !this._relativeWidgetLP._put)
                        return false;
                    this._finalPositionY = relativeWidget.getTopBoundary() + ap.y * cs.height;
                    this._finalPositionX = relativeWidget.getRightBoundary() - (1.0 - ap.x) * cs.width;
                }
                break;
            case ccui.RelativeLayoutParameter.LOCATION_LEFT_OF_TOPALIGN:
                if (relativeWidget){
                    if (this._relativeWidgetLP && !this._relativeWidgetLP._put)
                        return false;
                    this._finalPositionY = relativeWidget.getTopBoundary() - (1.0 - ap.y) * cs.height;
                    this._finalPositionX = relativeWidget.getLeftBoundary() - (1.0 - ap.x) * cs.width;
                }
                break;
            case ccui.RelativeLayoutParameter.LOCATION_LEFT_OF_CENTER:
                if (relativeWidget) {
                    if (this._relativeWidgetLP && !this._relativeWidgetLP._put)
                        return false;
                    var rbs = relativeWidget.getContentSize();
                    this._finalPositionX = relativeWidget.getLeftBoundary() - (1.0 - ap.x) * cs.width;
                    this._finalPositionY = relativeWidget.getBottomBoundary() + rbs.height * 0.5 + ap.y * cs.height - cs.height * 0.5;
                }
                break;
            case ccui.RelativeLayoutParameter.LOCATION_LEFT_OF_BOTTOMALIGN:
                if (relativeWidget) {
                    if (this._relativeWidgetLP && !this._relativeWidgetLP._put)
                        return false;
                    this._finalPositionY = relativeWidget.getBottomBoundary() + ap.y * cs.height;
                    this._finalPositionX = relativeWidget.getLeftBoundary() - (1.0 - ap.x) * cs.width;
                }
                break;
            case ccui.RelativeLayoutParameter.LOCATION_RIGHT_OF_TOPALIGN:
                if (relativeWidget){
                    if (this._relativeWidgetLP && !this._relativeWidgetLP._put)
                        return false;
                    this._finalPositionY = relativeWidget.getTopBoundary() - (1.0 - ap.y) * cs.height;
                    this._finalPositionX = relativeWidget.getRightBoundary() + ap.x * cs.width;
                }
                break;
            case ccui.RelativeLayoutParameter.LOCATION_RIGHT_OF_CENTER:
                if (relativeWidget){
                    if (this._relativeWidgetLP && !this._relativeWidgetLP._put)
                        return false;
                    var rbs = relativeWidget.getContentSize();
                    var locationRight = relativeWidget.getRightBoundary();
                    this._finalPositionX = locationRight + ap.x * cs.width;
                    this._finalPositionY = relativeWidget.getBottomBoundary() + rbs.height * 0.5 + ap.y * cs.height - cs.height * 0.5;
                }
                break;
            case ccui.RelativeLayoutParameter.LOCATION_RIGHT_OF_BOTTOMALIGN:
                if (relativeWidget){
                    if (this._relativeWidgetLP && !this._relativeWidgetLP._put)
                        return false;
                    this._finalPositionY = relativeWidget.getBottomBoundary() + ap.y * cs.height;
                    this._finalPositionX = relativeWidget.getRightBoundary() + ap.x * cs.width;
                }
                break;
            case ccui.RelativeLayoutParameter.LOCATION_BELOW_LEFTALIGN:
                if (relativeWidget){
                    if (this._relativeWidgetLP && !this._relativeWidgetLP._put)
                        return false;
                    this._finalPositionY =  relativeWidget.getBottomBoundary() - (1.0 - ap.y) * cs.height;
                    this._finalPositionX = relativeWidget.getLeftBoundary() + ap.x * cs.width;
                }
                break;
            case ccui.RelativeLayoutParameter.LOCATION_BELOW_CENTER:
                if (relativeWidget) {
                    if (this._relativeWidgetLP && !this._relativeWidgetLP._put)
                        return false;
                    var rbs = relativeWidget.getContentSize();
                    this._finalPositionY = relativeWidget.getBottomBoundary() - (1.0 - ap.y) * cs.height;
                    this._finalPositionX = relativeWidget.getLeftBoundary() + rbs.width * 0.5 + ap.x * cs.width - cs.width * 0.5;
                }
                break;
            case ccui.RelativeLayoutParameter.LOCATION_BELOW_RIGHTALIGN:
                if (relativeWidget) {
                    if (this._relativeWidgetLP && !this._relativeWidgetLP._put)
                        return false;
                    this._finalPositionY = relativeWidget.getBottomBoundary() - (1.0 - ap.y) * cs.height;
                    this._finalPositionX = relativeWidget.getRightBoundary() - (1.0 - ap.x) * cs.width;
                }
                break;
            default:
                break;
        }
        return true;
    },

    _calculateFinalPositionWithRelativeAlign: function(){
        var layoutParameter = this._widget.getLayoutParameter();

        var mg = layoutParameter.getMargin();
        var align = layoutParameter.getAlign();

        //handle margin
        switch (align) {
            case ccui.RelativeLayoutParameter.NONE:
            case ccui.RelativeLayoutParameter.PARENT_TOP_LEFT:
                this._finalPositionX += mg.left;
                this._finalPositionY -= mg.top;
                break;
            case ccui.RelativeLayoutParameter.PARENT_TOP_CENTER_HORIZONTAL:
                this._finalPositionY -= mg.top;
                break;
            case ccui.RelativeLayoutParameter.PARENT_TOP_RIGHT:
                this._finalPositionX -= mg.right;
                this._finalPositionY -= mg.top;
                break;
            case ccui.RelativeLayoutParameter.PARENT_LEFT_CENTER_VERTICAL:
                this._finalPositionX += mg.left;
                break;
            case ccui.RelativeLayoutParameter.CENTER_IN_PARENT:
                break;
            case ccui.RelativeLayoutParameter.PARENT_RIGHT_CENTER_VERTICAL:
                this._finalPositionX -= mg.right;
                break;
            case ccui.RelativeLayoutParameter.PARENT_LEFT_BOTTOM:
                this._finalPositionX += mg.left;
                this._finalPositionY += mg.bottom;
                break;
            case ccui.RelativeLayoutParameter.PARENT_BOTTOM_CENTER_HORIZONTAL:
                this._finalPositionY += mg.bottom;
                break;
            case ccui.RelativeLayoutParameter.PARENT_RIGHT_BOTTOM:
                this._finalPositionX -= mg.right;
                this._finalPositionY += mg.bottom;
                break;
            case ccui.RelativeLayoutParameter.LOCATION_ABOVE_LEFTALIGN:
                this._finalPositionY += mg.bottom;
                this._finalPositionX += mg.left;
                break;
            case ccui.RelativeLayoutParameter.LOCATION_ABOVE_RIGHTALIGN:
                this._finalPositionY += mg.bottom;
                this._finalPositionX -= mg.right;
                break;
            case ccui.RelativeLayoutParameter.LOCATION_ABOVE_CENTER:
                this._finalPositionY += mg.bottom;
                break;
            case ccui.RelativeLayoutParameter.LOCATION_LEFT_OF_TOPALIGN:
                this._finalPositionX -= mg.right;
                this._finalPositionY -= mg.top;
                break;
            case ccui.RelativeLayoutParameter.LOCATION_LEFT_OF_BOTTOMALIGN:
                this._finalPositionX -= mg.right;
                this._finalPositionY += mg.bottom;
                break;
            case ccui.RelativeLayoutParameter.LOCATION_LEFT_OF_CENTER:
                this._finalPositionX -= mg.right;
                break;
            case ccui.RelativeLayoutParameter.LOCATION_RIGHT_OF_TOPALIGN:
                this._finalPositionX += mg.left;
                this._finalPositionY -= mg.top;
                break;
            case ccui.RelativeLayoutParameter.LOCATION_RIGHT_OF_BOTTOMALIGN:
                this._finalPositionX += mg.left;
                this._finalPositionY += mg.bottom;
                break;
            case ccui.RelativeLayoutParameter.LOCATION_RIGHT_OF_CENTER:
                this._finalPositionX += mg.left;
                break;
            case ccui.RelativeLayoutParameter.LOCATION_BELOW_LEFTALIGN:
                this._finalPositionY -= mg.top;
                this._finalPositionX += mg.left;
                break;
            case ccui.RelativeLayoutParameter.LOCATION_BELOW_RIGHTALIGN:
                this._finalPositionY -= mg.top;
                this._finalPositionX -= mg.right;
                break;
            case ccui.RelativeLayoutParameter.LOCATION_BELOW_CENTER:
                this._finalPositionY -= mg.top;
                break;
            default:
                break;
        }
    }
};