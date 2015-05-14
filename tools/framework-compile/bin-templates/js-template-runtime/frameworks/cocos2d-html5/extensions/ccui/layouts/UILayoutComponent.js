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

ccui.LayoutComponent_ReferencePoint = {
    BOTTOM_LEFT: 0,
    TOP_LEFT: 1,
    BOTTOM_RIGHT: 2,
    TOP_RIGHT: 3
};
ccui.LayoutComponent_PositionType = {
    Position: 0,
    RelativePosition: 1,
    PreRelativePosition: 2,
    PreRelativePositionEnable: 3
};
ccui.LayoutComponent_SizeType = {
    Size: 0,
    PreSize: 1,
    PreSizeEnable: 2
};

//refactor since v3.3
ccui.LayoutComponent = cc.Component.extend({
    _horizontalEdge: 0,
    _verticalEdge: 0,

    _leftMargin: 0,
    _rightMargin: 0,
    _bottomMargin: 0,
    _topMargin: 0,

    _usingPositionPercentX: false,
    _positionPercentX: 0,
    _usingPositionPercentY: false,
    _positionPercentY: 0,

    _usingStretchWidth: false,
    _usingStretchHeight: false,

    _percentWidth: 0,
    _usingPercentWidth: false,

    _percentHeight: 0,
    _usingPercentHeight: false,

    _actived: true,
    _isPercentOnly: false,

    ctor: function () {
        this._name = ccui.LayoutComponent.NAME;
    },

    init: function () {
        var ret = true;

        if (!cc.Component.prototype.init.call(this)) {
            return false;
        }

        //put layout component initalized code here

        return ret;
    },

    getPercentContentSize: function () {
        return cc.p(this._percentWidth, this._percentHeight);
    },
    setPercentContentSize: function (percent) {
        this.setPercentWidth(percent.x);
        this.setPercentHeight(percent.y);
    },

    setUsingPercentContentSize: function (isUsed) {
        this._usingPercentWidth = this._usingPercentHeight = isUsed;
    },

    //old
    SetActiveEnable: function (enable) {
        this._actived = enable;
    },

    //v3.3
    getUsingPercentContentSize: function () {
        return this._usingPercentWidth && this._usingPercentHeight;
    },

    //position & margin
    getAnchorPosition: function () {
        return this._owner.getAnchorPoint();
    },

    setAnchorPosition: function (point, y) {
        var oldRect = this._owner.getBoundingBox();
        this._owner.setAnchorPoint(point, y);
        var newRect = this._owner.getBoundingBox();
        var offSetX = oldRect.x - newRect.x, offSetY = oldRect.y - newRect.y;

        var ownerPosition = this._owner.getPosition();
        ownerPosition.x += offSetX;
        ownerPosition.y += offSetY;
        this.setPosition(ownerPosition);
    },

    getPosition: function () {
        return this._owner.getPosition();
    },

    setPosition: function (position, y) {
        var parent = this._getOwnerParent(), x;
        if (parent != null) {
            if (y === undefined) {
                x = position.x;
                y = position.y;
            } else
                x = position;
            var parentSize = parent.getContentSize();

            if (parentSize.width !== 0)
                this._positionPercentX = x / parentSize.width;
            else {
                this._positionPercentX = 0;
                if (this._usingPositionPercentX)
                    x = 0;
            }

            if (parentSize.height !== 0)
                this._positionPercentY = y / parentSize.height;
            else {
                this._positionPercentY = 0;
                if (this._usingPositionPercentY)
                    y = 0;
            }

            this._owner.setPosition(x, y);
            this._refreshHorizontalMargin();
            this._refreshVerticalMargin();
        } else
            this._owner.setPosition(position, y);
    },

    isPositionPercentXEnabled: function () {
        return this._usingPositionPercentX;
    },
    setPositionPercentXEnabled: function (isUsed) {
        this._usingPositionPercentX = isUsed;
        if (this._usingPositionPercentX)
            this._horizontalEdge = ccui.LayoutComponent.horizontalEdge.NONE;
    },

    getPositionPercentX: function () {
        return this._positionPercentX;
    },
    setPositionPercentX: function (percentMargin) {
        this._positionPercentX = percentMargin;

        var parent = this._getOwnerParent();
        if (parent !== null) {
            this._owner.setPositionX(parent.width * this._positionPercentX);
            this._refreshHorizontalMargin();
        }
    },

    isPositionPercentYEnabled: function () {
        return this._usingPositionPercentY;
    },
    setPositionPercentYEnabled: function (isUsed) {
        this._usingPositionPercentY = isUsed;
        if (this._usingPositionPercentY)
            this._verticalEdge = ccui.LayoutComponent.verticalEdge.NONE;
    },

    getPositionPercentY: function () {
        return this._positionPercentY;
    },
    setPositionPercentY: function (percentMargin) {
        this._positionPercentY = percentMargin;

        var parent = this._getOwnerParent();
        if (parent !== null) {
            this._owner.setPositionY(parent.height * this._positionPercentY);
            this._refreshVerticalMargin();
        }
    },

    getHorizontalEdge: function () {
        return this._horizontalEdge;
    },
    setHorizontalEdge: function (hEdge) {
        this._horizontalEdge = hEdge;
        if (this._horizontalEdge !== ccui.LayoutComponent.horizontalEdge.NONE)
            this._usingPositionPercentX = false;

        var parent = this._getOwnerParent();
        if (parent !== null) {
            var ownerPoint = this._owner.getPosition();
            var parentSize = parent.getContentSize();
            if (parentSize.width !== 0)
                this._positionPercentX = ownerPoint.x / parentSize.width;
            else {
                this._positionPercentX = 0;
                ownerPoint.x = 0;
                if (this._usingPositionPercentX)
                    this._owner.setPosition(ownerPoint);
            }
            this._refreshHorizontalMargin();
        }
    },

    getVerticalEdge: function () {
        return this._verticalEdge;
    },
    setVerticalEdge: function (vEdge) {
        this._verticalEdge = vEdge;
        if (this._verticalEdge !== ccui.LayoutComponent.verticalEdge.NONE)
            this._usingPositionPercentY = false;

        var parent = this._getOwnerParent();
        if (parent !== null) {
            var ownerPoint = this._owner.getPosition();
            var parentSize = parent.getContentSize();
            if (parentSize.height !== 0)
                this._positionPercentY = ownerPoint.y / parentSize.height;
            else {
                this._positionPercentY = 0;
                ownerPoint.y = 0;
                if (this._usingPositionPercentY)
                    this._owner.setPosition(ownerPoint);
            }
            this._refreshVerticalMargin();
        }
    },

    getLeftMargin: function () {
        return this._leftMargin;
    },
    setLeftMargin: function (margin) {
        this._leftMargin = margin;
    },

    getRightMargin: function () {
        return this._rightMargin;
    },
    setRightMargin: function (margin) {
        this._rightMargin = margin;
    },

    getTopMargin: function () {
        return this._topMargin;
    },
    setTopMargin: function (margin) {
        this._topMargin = margin;
    },

    getBottomMargin: function () {
        return this._bottomMargin;
    },
    setBottomMargin: function (margin) {
        this._bottomMargin = margin;
    },

    //size &
    getSize: function () {
        return this.getOwner().getContentSize();
    },
    setSize: function (size) {
        var parent = this._getOwnerParent();
        if (parent !== null) {
            var ownerSize = size, parentSize = parent.getContentSize();

            if (parentSize.width !== 0)
                this._percentWidth = ownerSize.width / parentSize.width;
            else {
                this._percentWidth = 0;
                if (this._usingPercentWidth)
                    ownerSize.width = 0;
            }

            if (parentSize.height !== 0)
                this._percentHeight = ownerSize.height / parentSize.height;
            else {
                this._percentHeight = 0;
                if (this._usingPercentHeight)
                    ownerSize.height = 0;
            }

            this._owner.setContentSize(ownerSize);

            this._refreshHorizontalMargin();
            this._refreshVerticalMargin();
        }
        else
            this._owner.setContentSize(size);
    },

    isPercentWidthEnabled: function () {
        return this._usingPercentWidth;
    },
    setPercentWidthEnabled: function (isUsed) {
        this._usingPercentWidth = isUsed;
        if (this._usingPercentWidth)
            this._usingStretchWidth = false;
    },

    getSizeWidth: function () {
        return this._owner.width;
    },
    setSizeWidth: function (width) {
        var ownerSize = this._owner.getContentSize();
        ownerSize.width = width;

        var parent = this._getOwnerParent();
        if (parent !== null) {
            var parentSize = parent.getContentSize();
            if (parentSize.width !== 0)
                this._percentWidth = ownerSize.width / parentSize.width;
            else {
                this._percentWidth = 0;
                if (this._usingPercentWidth)
                    ownerSize.width = 0;
            }
            this._owner.setContentSize(ownerSize);
            this._refreshHorizontalMargin();
        } else
            this._owner.setContentSize(ownerSize);
    },

    getPercentWidth: function () {
        return this._percentWidth;
    },
    setPercentWidth: function (percentWidth) {
        this._percentWidth = percentWidth;

        var parent = this._getOwnerParent();
        if (parent !== null) {
            var ownerSize = this._owner.getContentSize();
            ownerSize.width = parent.width * this._percentWidth;
            this._owner.setContentSize(ownerSize);
            this._refreshHorizontalMargin();
        }
    },

    isPercentHeightEnabled: function () {
        return this._usingPercentHeight;
    },
    setPercentHeightEnabled: function (isUsed) {
        this._usingPercentHeight = isUsed;
        if (this._usingPercentHeight)
            this._usingStretchHeight = false;
    },

    getSizeHeight: function () {
        return this._owner.height;
    },
    setSizeHeight: function (height) {
        var ownerSize = this._owner.getContentSize();
        ownerSize.height = height;

        var parent = this._getOwnerParent();
        if (parent !== null) {
            var parentSize = parent.getContentSize();
            if (parentSize.height !== 0)
                this._percentHeight = ownerSize.height / parentSize.height;
            else {
                this._percentHeight = 0;
                if (this._usingPercentHeight)
                    ownerSize.height = 0;
            }
            this._owner.setContentSize(ownerSize);
            this._refreshVerticalMargin();
        }
        else
            this._owner.setContentSize(ownerSize);
    },

    getPercentHeight: function () {
        return this._percentHeight;
    },
    setPercentHeight: function (percentHeight) {
        this._percentHeight = percentHeight;

        var parent = this._getOwnerParent();
        if (parent !== null) {
            var ownerSize = this._owner.getContentSize();
            ownerSize.height = parent.height * this._percentHeight;
            this._owner.setContentSize(ownerSize);
            this._refreshVerticalMargin();
        }
    },

    isStretchWidthEnabled: function () {
        return this._usingStretchWidth;
    },
    setStretchWidthEnabled: function (isUsed) {
        this._usingStretchWidth = isUsed;
        if (this._usingStretchWidth)
            this._usingPercentWidth = false;
    },

    isStretchHeightEnabled: function () {
        return this._usingStretchHeight;
    },
    setStretchHeightEnabled: function (isUsed) {
        this._usingStretchHeight = isUsed;
        if (this._usingStretchHeight)
            this._usingPercentHeight = false;
    },

    setPercentOnlyEnabled: function(enable){
        this._isPercentOnly = enable;
    },

    setActiveEnabled: function (enable) {
        this._actived = enable;
    },
    refreshLayout: function () {
        if(!this._actived)
            return;

        var parent = this._getOwnerParent();
        if (parent === null)
            return;

        var parentSize = parent.getContentSize(), locOwner = this._owner;
        var ownerAnchor = locOwner.getAnchorPoint(), ownerSize = locOwner.getContentSize();
        var ownerPosition = locOwner.getPosition();

        switch (this._horizontalEdge) {
            case ccui.LayoutComponent.horizontalEdge.NONE:
                if (this._usingStretchWidth && !this._isPercentOnly) {
                    ownerSize.width = parentSize.width * this._percentWidth;
                    ownerPosition.x = this._leftMargin + ownerAnchor.x * ownerSize.width;
                } else {
                    if (this._usingPositionPercentX)
                        ownerPosition.x = parentSize.width * this._positionPercentX;
                    if (this._usingPercentWidth)
                        ownerSize.width = parentSize.width * this._percentWidth;
                }
                break;
            case ccui.LayoutComponent.horizontalEdge.LEFT:
                if(this._isPercentOnly)
                    break;
                if (this._usingPercentWidth || this._usingStretchWidth)
                    ownerSize.width = parentSize.width * this._percentWidth;
                ownerPosition.x = this._leftMargin + ownerAnchor.x * ownerSize.width;
                break;
            case ccui.LayoutComponent.horizontalEdge.RIGHT:
                if(this._isPercentOnly)
                    break;
                if (this._usingPercentWidth || this._usingStretchWidth)
                    ownerSize.width = parentSize.width * this._percentWidth;
                ownerPosition.x = parentSize.width - (this._rightMargin + (1 - ownerAnchor.x) * ownerSize.width);
                break;
            case ccui.LayoutComponent.horizontalEdge.CENTER:
                if(this._isPercentOnly)
                    break;
                if (this._usingStretchWidth) {
                    ownerSize.width = parentSize.width - this._leftMargin - this._rightMargin;
                    if (ownerSize.width < 0)
                        ownerSize.width = 0;
                    ownerPosition.x = this._leftMargin + ownerAnchor.x * ownerSize.width;
                } else {
                    if (this._usingPercentWidth)
                        ownerSize.width = parentSize.width * this._percentWidth;
                    ownerPosition.x = parentSize.width * this._positionPercentX;
                }
                break;
            default:
                break;
        }

        switch (this._verticalEdge) {
            case ccui.LayoutComponent.verticalEdge.NONE:
                if (this._usingStretchHeight && !this._isPercentOnly) {
                    ownerSize.height = parentSize.height * this._percentHeight;
                    ownerPosition.y = this._bottomMargin + ownerAnchor.y * ownerSize.height;
                } else {
                    if (this._usingPositionPercentY)
                        ownerPosition.y = parentSize.height * this._positionPercentY;
                    if (this._usingPercentHeight)
                        ownerSize.height = parentSize.height * this._percentHeight;
                }
                break;
            case ccui.LayoutComponent.verticalEdge.BOTTOM:
                if(this._isPercentOnly)
                    break;
                if (this._usingPercentHeight || this._usingStretchHeight)
                    ownerSize.height = parentSize.height * this._percentHeight;
                ownerPosition.y = this._bottomMargin + ownerAnchor.y * ownerSize.height;
                break;
            case ccui.LayoutComponent.verticalEdge.TOP:
                if(this._isPercentOnly)
                    break;
                if (this._usingPercentHeight || this._usingStretchHeight)
                    ownerSize.height = parentSize.height * this._percentHeight;
                ownerPosition.y = parentSize.height - (this._topMargin + (1 - ownerAnchor.y) * ownerSize.height);
                break;
            case ccui.LayoutComponent.verticalEdge.CENTER:
                if(this._isPercentOnly)
                    break;
                if (this._usingStretchHeight) {
                    ownerSize.height = parentSize.height - this._topMargin - this._bottomMargin;
                    if (ownerSize.height < 0)
                        ownerSize.height = 0;
                    ownerPosition.y = this._bottomMargin + ownerAnchor.y * ownerSize.height;
                } else {
                    if(this._usingPercentHeight)
                        ownerSize.height = parentSize.height * this._percentHeight;
                    ownerPosition.y = parentSize.height * this._positionPercentY;
                }
                break;
            default:
                break;
        }

        locOwner.setPosition(ownerPosition);
        locOwner.setContentSize(ownerSize);

        ccui.helper.doLayout(locOwner);
    },

    _getOwnerParent: function () {
        return this._owner ? this._owner.getParent() : null;
    },
    _refreshHorizontalMargin: function () {
        var parent = this._getOwnerParent();
        if (parent === null)
            return;

        var ownerPoint = this._owner.getPosition(), ownerAnchor = this._owner.getAnchorPoint();
        var ownerSize = this._owner.getContentSize(), parentSize = parent.getContentSize();

        this._leftMargin = ownerPoint.x - ownerAnchor.x * ownerSize.width;
        this._rightMargin = parentSize.width - (ownerPoint.x + (1 - ownerAnchor.x) * ownerSize.width);
    },
    _refreshVerticalMargin: function () {
        var parent = this._getOwnerParent();
        if (parent === null)
            return;

        var ownerPoint = this._owner.getPosition(), ownerAnchor = this._owner.getAnchorPoint();
        var ownerSize = this._owner.getContentSize(), parentSize = parent.getContentSize();

        this._bottomMargin = ownerPoint.y - ownerAnchor.y * ownerSize.height;
        this._topMargin = parentSize.height - (ownerPoint.y + (1 - ownerAnchor.y) * ownerSize.height);
    }
});

ccui.LayoutComponent.horizontalEdge = {NONE: 0, LEFT: 1, RIGHT: 2, CENTER: 3};
ccui.LayoutComponent.verticalEdge = {NONE: 0, BOTTOM: 1, TOP: 2, CENTER: 3};

ccui.LayoutComponent.NAME = "__ui_layout";
ccui.LayoutComponent.bindLayoutComponent = function (node) {
    var layout = node.getComponent(ccui.LayoutComponent.NAME);
    if (layout !== undefined)
        return layout;

    layout = new ccui.LayoutComponent();
    if (layout && layout.init()) {
        node.addComponent(layout);
        return layout;
    }
    return null;
};