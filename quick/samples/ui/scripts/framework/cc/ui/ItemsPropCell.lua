local ButtonNumBoard    = import("app.components.ButtonNumBoard")
local ItemsPropCell = class("ItemsPropCell", cc.ui.UIGroup)

ItemsPropCell.HEIGHT = 210

function ItemsPropCell:ctor(param)
    ItemsPropCell.super.ctor(self)

    self.iconImage_   = param.iconImage or ""
    self.showImage_   = param.showImage or nil
    self.title_       = param.title or ""
    self.description_ = param.description or ""
    self.pay_         = param.pay or 0
    self.isUse_       = param.isUse or false
    self.ownCounts_   = param.own or 0
    self.propId_      = param.propId or ""

    self.board_ = cc.ui.UIImage.new("#MakeCommonBoard.png", {scale9 = true})
        :setLayoutSize(display.width - 40, ItemsPropCell.HEIGHT)
        :addTo(self)

    self.boardWidth_, self.boardHeight_ = self.board_:getLayoutSize()

    -- self.icon_
    self.icon_ = cc.ui.UIImage.new(self.iconImage_)
        :pos(15, 75)
        :addTo(self)

    if self.showImage_ then
        self.show_ = cc.ui.UIImage.new(self.showImage_)
            :align(display.RIGHT_BOTTOM, 126, 84)
            :addTo(self)
    end

    -- 114 60拥有
    if self.isUse_ then
        self.useButton_ = cc.ui.UIPushButton.new({
                normal = "#Button_2.png",
                pressed = "#ButtonPressed_2.png",
                disabled = "#GrayButton.png",
            }, {scale9 = true})
            :setButtonSize(114, 60)
            -- :setButtonEnabled(false)
            :setButtonLabel(cc.ui.UILabel.new({text = "可用:"..self.ownCounts_, size = 22}))
            -- :setButtonLabelAlignment(display.CENTER)
            -- :setButtonLabelOffset(0, 22)
            :onButtonClicked(function(x, y)
                self:dispatchEvent({name = "use", counts = self.ownCounts_, id = self.propId_})
            end)
            :pos(78, 45)
        self:addChild(self.useButton_)
        if self.ownCounts_ == 0 then
            self.useButton_:setButtonEnabled(false)
        end
    else
        self.useCounts_ = ui.newTTFLabel({
                text = "拥有:"..self.ownCounts_,
                color = display.COLOR_BLACK,
                size = 22,
                x = 46, 
                y = 45
            })
        self:addChild(self.useCounts_)
    end

    -- title
    self.titleLabel_ = cc.ui.UILabel.new({
            text = self.title_,
            color = display.COLOR_BLACK,
            size = 24
        })
        :align(display.LEFT_CENTER, display.left + 150, 170)
        :addTo(self)

    -- description
    self.descriptionLabel_ = ui.newTTFLabel({
            text = self.description_, 
            size = 22, 
            color = display.COLOR_BLACK,
            align = ui.TEXT_ALIGN_LEFT,
            valign  = ui.TEXT_VALIGN_TOP,
            dimensions  = CCSize(280, 200),
            x = display.left + 150, 
            y = 50
        })
        :addTo(self)

    -- 购买140 114
    self.buyButton_ = cc.ui.UIPushButton.new({
            normal = "#Button_1.png",
            pressed = "#ButtonPressed_1.png",
            disabled = "#GrayButton.png",
        }, {scale9 = true})
        :setButtonSize(140, 114)
        -- :setButtonEnabled(false)
        :setButtonLabel(cc.ui.UILabel.new({text = "购 买", size = 22}))
        :setButtonLabelOffset(0, 22)
        :pos(display.right - 130, 130)
        :onButtonClicked(function(x, y)
            self:dispatchEvent({name = "buy", cost = self.pay_})
        end)
    self:addChild(self.buyButton_)

    self.buyButton_.buttonNumBoard = ButtonNumBoard.new({
            width       = 100,
            num         = string.formatnumberthousands(self.pay_),
            boardType   = "gold",
            size        = 22
        })
        :pos(5, -22)
        :addTo(self.buyButton_)
end

function ItemsPropCell:isUnableBuy(bool)
    if self.useButton_ then
        self.useButton_:setButtonEnabled(bool)
    end
    self.buyButton_:setButtonEnabled(bool)
end

function ItemsPropCell:update(own)
    self.ownCounts_ = own
    if self.useButton_ then
        self.useButton_:setButtonLabelString("可用:"..self.ownCounts_)
    else
        self.useCounts_:setString("拥有:"..self.ownCounts_)
    end
    if self.ownCounts_ > 0 and self.useButton_ then
        self.useButton_:setButtonEnabled(true)
    elseif self.useButton_ then
        self.useButton_:setButtonEnabled(false)
    end
    self.buyButton_:setButtonEnabled(true)
end

return ItemsPropCell