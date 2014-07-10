local PromotionBanner       = import("..views.PromotionBanner")
local PromptMessageBoard    = import("..views.PromptMessageBoard")
local UnableTeleportDialog  = import("app.views.worldMap.UnableTeleportDialog")
local ShopType              = import("shared.models.shop.ShopType")
local RenamePage            = import(".itemsPage.RenamePage")
local CommonPage            = import("..components.CommonPage")
local CommonBoard           = import("..components.CommonBoard")
local ItemsPropCell         = import("..views.itemsPage.ItemsPropCell")
local MyPropCell            = import("..views.itemsPage.MyPropCell")

-- 临时数据
-- local SpecialShopProperties    = import("shared.properties.SpecialShopProperties")
-- local ResourcesShopProperties  = import("shared.properties.ResourceShopProperties")
-- local SpeedUpShopProperties    = import("shared.properties.SpeedUpShopProperties")
-- local WarShopProperties        = import("shared.properties.WarShopProperties")
-- local SpecialShopProperties = import("..shared.properties.city.SpecialShopProperties")

local ItemsPage = class("ItemsPage", CommonPage)

ItemsPage.BOARD_GROUP  = 1
ItemsPage.UI_GROUP     = 100
ItemsPage.DIALOG_GROUP = 200
ItemsPage.BANNER_GROUP = 300

ItemsPage.PAGE_LABEL = {
    off         = "#LabelPageTopPressButton.png",
    on          = "#LabelPageTopNormalButton.png",
    on_disabled = "#LabelPageTopNormalButton.png"
}

ItemsPage.MENU_LABEL = {
    off         = "#LabelPageChildrenNormalButton.png",
    on          = "#LabelPageChildrenPressButton.png",
    on_disabled = "#LabelPageChildrenPressButton.png"
}

function ItemsPage:ctor(param)
    ItemsPage.super.ctor(self, param)

    self.contents_ = self:getContents()
    self.parent_ = param.parent

    self.boardGroup_ = cc.ui.UIGroup.new()
    self.contents_:addChild(self.boardGroup_, self.BOARD_GROUP)

    self.uiGroup_ = cc.ui.UIGroup.new()
        :onTouch(function(event, x, y)
            self:onTouch(event, x, y)
            return true
        end)
        :enableTouch(true)
    self.contents_:addChild(self.uiGroup_, self.UI_GROUP)

    self.dialogGroup_ = cc.ui.UIGroup.new()
    self.contents_:addChild(self.dialogGroup_, self.DIALOG_GROUP)

    self.bannerGroup_ = cc.ui.UIGroup.new()
    self.contents_:addChild(self.bannerGroup_, self.BANNER_GROUP)

    self.listBox_           = {}
    self.choosePage_        = 1
    self.chooseMenu_        = 1
    self.chooseType_        = nil
    self.topContentHeight_  = 0
    self.currentCellHeight_ = 0
    self.movedY_            = 0

    -- banner底
    local boardBottom = cc.ui.UIImage.new("#ScaleColor01.png", {scale9 = true})
        :setLayoutSize(display.width, 254)
        :pos(display.c_left, display.c_top - 254)
        :addTo(self.bannerGroup_)
    boardBottom:setTouchEnabled(true)
    boardBottom:addTouchEventListener(function(event, x, y)
        if event == "began" then
            return true
        end
    end)

    -- 促销banner
    -- self.promotionBanner_ = PromotionBanner.new()
    -- self.promotionBanner_:setPosition(0, display.c_top - self:getTopBoardHeight() * 1.5)
    -- self.bannerGroup_:addChild(self.promotionBanner_)

    -- 分页标签
    self.pageLabel_ = cc.ui.UICheckBoxButtonGroup.new(display.LEFT_TO_RIGHT)
        :addButton(cc.ui.UICheckBoxButton.new(self.PAGE_LABEL, {scale9 = true})
            :setButtonSize(300, 66)
            :setButtonLabel(cc.ui.UILabel.new({text = "商 店", align = ui.TEXT_ALIGN_CENTER, color = display.COLOR_BLACK}))
            :setButtonLabelOffset(-25, 0))
        :addButton(cc.ui.UICheckBoxButton.new(self.PAGE_LABEL, {scale9 = true})
            :setButtonSize(300, 66)
            :setButtonLabel(cc.ui.UILabel.new({text = "我的物品", align = ui.TEXT_ALIGN_CENTER, color = display.COLOR_BLACK}))
            :setButtonLabelOffset(-45, 0))
        :setButtonsLayoutMargin(0, 100, 0, 0)
        :align(display.BOTTOM_CENTER, -253, display.c_top - 155)

        :addTo(self.bannerGroup_)
    self.topContentHeight_ = 245

    self.pageLabel_:onButtonSelectChanged(function(event)
            if event.selected == 1 then
                self.choosePage_ = 1
                -- self:createWorldList()
            elseif event.selected == 2 then
                self.choosePage_ = 2
                -- self:createAllianceList()
            end
            self:createList()
            printf("Option %d selected, Option %d unselected", event.selected, event.last)
        end)
    self.pageLabel_:getButtonAtIndex(1):setButtonSelected(true)

    -- 分类菜单
    local menuBanner = CommonBoard.new({
            boardName = "#ScaleColor04.png",
            width = display.width,
            height = 100,
            rimName = "#ScaleGoldFrame.png",
            rimType = "GoldenSmall"
        })
    menuBanner:setPosition(0, display.c_top - 208)
    self.bannerGroup_:addChild(menuBanner)

    self.menuDefines_ = {
        {"特 殊", ShopType.SPECIAL, "tip:特殊物品, 奖励增益"},
        {"资 源", ShopType.RESOURCES, "tip:资源不足？试着获取资源包"},
        {"加 速", ShopType.SPEED_UP, "tip:特殊物品, 加速各种任务"},
        {"战 争", ShopType.WAR, "tip:这里有你需要的战斗相关物品"},
    }

    self.menuLabel = cc.ui.UICheckBoxButtonGroup.new(display.LEFT_TO_RIGHT)
    for i, define in pairs(self.menuDefines_) do
        local button = cc.ui.UICheckBoxButton.new(self.MENU_LABEL, {scale9 = true})
        self.menuLabel:addButton(button)
        button:setButtonSize(150, 55)
        button:setButtonLabel(cc.ui.UILabel.new({text = define[1], align = ui.TEXT_ALIGN_CENTER, color = display.COLOR_WHITE}))
        button:setButtonLabelOffset(-25, 0)
    end
    self.menuLabel:setButtonsLayoutMargin(0, 118, 0, 0)
    self.menuLabel:align(display.TOP_CENTER, -240, display.c_top - 235)

    self.menuLabel:onButtonSelectChanged(function(event)
            self.chooseMenu_ = event.selected
            self.chooseType_ = self.menuDefines_[event.selected][2]
            -- print(self.defines_[event.selected][2])
            -- self:createResourceList()
            self:createList()
        end)
    self.menuLabel:getButtonAtIndex(1):setButtonSelected(true)

    self.bannerGroup_:addChild(self.menuLabel)
    -- self:createList()
end

function ItemsPage:createMessageBanner()
    -- 600, 45
    local banner = cc.ui.UIImage.new("#ScaleBlackBoard.png", {scale9 = true})
        :setLayoutSize(display.width - 40, 45)
        -- print(self.menuDefines_[self.chooseMenu_][3])
    local label = cc.ui.UILabel.new({
            text = self.menuDefines_[self.chooseMenu_][3],
        })
        :pos(14, 22)
    banner:addChild(label)
    return banner
end

function ItemsPage:createList()
    self:removeAllCells()

    local allId = {}
    local listCounts = 0
    local shop = app.player:getShop()

    if self.chooseType_ == ShopType.SPECIAL then
        allId = shop.getSpecialAllId()
    elseif self.chooseType_ == ShopType.RESOURCES then
        allId = shop.getResourceAllId()
    elseif self.chooseType_ == ShopType.SPEED_UP then
        allId = shop.getSpeedUpAllId()
    elseif self.chooseType_ == ShopType.WAR then
        allId = shop.getWarAllId()
    end
 
    -- dump(allId)
    for i = 1, #allId do
        local item = ShopType.getModel(shop, self.chooseType_, allId[i])
        cc.EventProxy.new(item, self)
            :addEventListener(ShopType.getEventName(item, self.chooseType_), function()
                self:performWithDelay(function()
                    self:updateCell(item)
                end, 0.3)
            end)
        local define = item:getDefine()
        local cell = nil

        if i == 1 then
            local banner = self:createMessageBanner()
            banner:align(display.BOTTOM_CENTER, 0, display.c_top - 302)
            self.uiGroup_:addChild(banner)
            self:addCell("banner", banner) 
        end

        if self.choosePage_ == 1 then
            -- 商店列表
            cell = ItemsPropCell.new({
                iconImage   = define.image,
                showImage   = define.show,
                title       = define.title,
                description = define.description,
                pay         = define.gold,
                isUse       = define.isUse,
                propId      = allId[i],
                own         = item:getAmount()
            })
            local w, h = cell:getLayoutSize()
            self.currentCellHeight_ = cell.HEIGHT + 5
            cell:addEventListener("buy", function(event)
                    if event.cost <= app.player:getGold() then
                        cell:isUnableBuy(false)
                        api.shop.buy(app.player, self.chooseType_, item, function(event)
                            self:showMessage("购买", item, define.image)
                        end, function(err) 
                            app:apiError(function()
                                cell:isUnableBuy(true)
                            end) 
                        end)
                    else
                        self.parent_:goldIsNotEnough()
                    end
                end)
            cell:addEventListener("use", function(event)
                    if self.chooseType_ ==  ShopType.RESOURCES then
                        cell:isUnableBuy(false)
                        self:useResPropApi(event.id, function()
                            self:showMessage("使用", item, define.image)
                        end, function()
                            cell:isUnableBuy(true)
                        end)
                    elseif self.chooseType_ == ShopType.SPECIAL then
                        self:useSpecialProp(event.id, function()
                            self:showMessage("使用", item, define.image)
                        end, function()
                            cell:isUnableBuy(true)
                        end)
                    elseif self.chooseType_ == ShopType.WAR then
                        self:useWarProp(event.id, function()
                            self:showMessage("使用", item, define.image)
                        end, function()
                            cell:isUnableBuy(true)
                        end)
                    end
                end)
            cell:setPosition(display.c_left + 20, display.c_top - 515 - (i - 1) * self.currentCellHeight_)
        else
            -- 我的物品列表
            if item:getAmount() > 0 then
                listCounts = listCounts + 1
                cell = MyPropCell.new({
                    iconImage   = define.image,
                    showImage   = define.show,
                    title       = define.title,
                    description = define.description,
                    pay         = define.gold,
                    isUse       = define.isUse,
                    isShop      = true,
                    propId      = allId[i],
                    own         = item:getAmount()
                })
                local w, h = cell:getLayoutSize()
                self.currentCellHeight_ = cell.HEIGHT + 5
                cell:addEventListener("use", function(event)
                    if self.chooseType_ ==  ShopType.RESOURCES then
                        cell:isUnableBuy(false)
                        self:useResPropApi(event.id, function()
                            self:showMessage("使用", item, define.image)
                            self:performWithDelay(function()
                                cell:isUnableBuy(true)
                            end, 0.2)
                        end, function()
                            cell:isUnableBuy(true)
                        end)
                    elseif self.chooseType_ == ShopType.SPECIAL then
                        self:useSpecialProp(event.id, function()
                            self:showMessage("使用", item, define.image)
                            self:performWithDelay(function()
                                cell:isUnableBuy(true)
                            end, 0.2)
                        end, function()
                            cell:isUnableBuy(true)
                        end)
                    elseif self.chooseType_ == ShopType.WAR then
                        self:useWarProp(event.id, function()
                            self:showMessage("使用", item, define.image)
                            self:performWithDelay(function()
                                cell:isUnableBuy(true)
                            end, 0.2)
                        end, function()
                            cell:isUnableBuy(true)
                        end)
                    end
                end)
                cell:setPosition(display.c_left + 20, display.c_top - 485 - (listCounts - 1) * self.currentCellHeight_)
            end
        end
        -- print(display.c_top - 575, display.c_top - 605)
        if cell then
            self.uiGroup_:addChild(cell)
            self:addCell("cell"..tostring(allId[i]), cell)
        end
    end

    -- 还原位置
    self.movedY_ = 0
    self:setListPos(0)
end

-- 使用战争商品
function ItemsPage:useWarProp(id, fun, errFun)
    local shop = app.player:getShop()
    local prop = ShopType.getModel(shop, ShopType.WAR, id)
    api.shop.useBoot(app.player, prop, function()
        if fun then fun() end
    end, function(err)
        -- dump(err)
        app:apiError(function()
            if errFun then errFun() end
        end)
    end)
end

-- 使用资源商品API
function ItemsPage:useResPropApi(id, fun)
    local shop = app.player:getShop()
    local prop = ShopType.getModel(shop, ShopType.RESOURCES, id)
    api.shop.useRes(app.player, prop, function()
        if fun then fun() end
    end, function(err) 
        app:apiError(function()
            self:useResPropApi(id, fun)
        end)
    end)
end

-- 检查行军部队
function ItemsPage:checkIsHaveTroopOutCity()
    local marchs = app.player:getMarchs()
    local allTroops = marchs:getAllTroopObj()
    local currentTroopCounts = 0
    for name, troop in pairs(allTroops) do
        currentTroopCounts = currentTroopCounts + 1
    end
    if currentTroopCounts > 0 then
        return true
    else
        return false
    end
    return false
end

-- 使用特殊道具
function ItemsPage:useSpecialProp(id, fun, errFun)
    if id == "S014" then
        -- 随机传送
        self.parent_:onOpenBuyAndUseItemDialog(ShopType.SPECIAL, "S014", function(fun1, fun2)
            if not self:checkIsHaveTroopOutCity() then
                api.shop.teleport(app.player, nil, nil, function()
                    if fun1 then fun1() end
                    if fun then fun() end
                end, function(err)
                    -- dump(err)
                    app:apiError(function()
                        if fun2 then fun2() end
                    end)
                end)
            else
                if fun2 then fun2() end
                local dialog = UnableTeleportDialog.new({})
                self.parent_.topGroup_:addChild(dialog)
            end
        end)
    elseif id == "S001" or id == "S002" or 
           id == "S003" or id == "S004" or 
           id == "S005" or id == "S010" or 
           id == "S022" or id == "S020" or
           id == "S021" then
        local shop = app.player:getShop()
        local prop = ShopType.getModel(shop, ShopType.SPECIAL, id)
        api.shop.useBoot(app.player, prop, function()
            if fun then fun() end
        end, function(err)
            -- dump(err)
            app:apiError(function()
                if errFun then errFun() end
            end)
        end)
    elseif id == "S016" then
        -- 玩家改名
        local page = RenamePage.new({
                title        = "玩家改名",
                isAutoRemove = true,
                propId       = id,
                parent       = self.parent_
            })
        page:addEventListener("succeed", function()
                self.parent_.cityAndMapBanner_:updatePlayerName()
                if fun then fun() end
                page:close()
            end)
        self.parent_.topGroup_:addChild(page)
    elseif id == "S018" then
        -- 城市改名
        local page = RenamePage.new({
                title        = "城市改名",
                isAutoRemove = true,
                message      = "Tip:城市名字长度不能超过6个汉字",
                propId       = id,
                parent       = self.parent_
            })
        page:addEventListener("succeed", function()
                if fun then fun() end
                page:close()
            end)
        self.parent_.topGroup_:addChild(page)
    end
end

-- 暂时滚动起
function ItemsPage:onTouch(event, x, y)
    if event == "began" then
        local bx,by = self.uiGroup_:getPosition()
        self.touches_ = {
            startX = x,
            startY = y,
            mapX = bx,
            mapY = by
        }
    elseif event == "moved" then
        self.movedY_ = self.touches_.mapY + (y - self.touches_.startY)
        self:setListPos(self.movedY_)
        -- self.uiGroup_:setPositionY(self.movedY_)
    elseif event == "ended" then
        self:setListPos(self.movedY_, "end")
    end
end

function ItemsPage:setListPos(y, isEnd)
    if y < 0 and isEnd then
        y = 0
        transition.moveTo(self.uiGroup_, {time = 0.2, y = y})
    elseif y > self:getListCounts() * self.currentCellHeight_ - display.top + self.topContentHeight_ + 130 and isEnd then
        y = self:getListCounts() * self.currentCellHeight_ - display.top + self.topContentHeight_ + 130
        if y < 0 then
            y = 0
        end
        transition.moveTo(self.uiGroup_, {time = 0.2, y = y})
    end
    self.movedY_ = y
    if not isEnd then
        self.uiGroup_:setPositionY(y)
    end
end

function ItemsPage:getListCounts()
    local counts = 0
    for name, cell in pairs(self.listBox_) do
        counts = counts +1
    end
    return counts
end

function ItemsPage:updateCell(item)
    local name = "cell"..tostring(item:getId())
    if self.choosePage_ == 2 and item:getAmount() == 0 then
        self:createList()
    else
        self.listBox_[name]:update(item:getAmount())
    end
end

function ItemsPage:showMessage(title, item, image)
    local board = PromptMessageBoard.new({
        title   = title..tostring(item:getDefine().title).."成功",
        message = "",
        iconUrl = image
    })
    self.parent_.topGroup_:addChild(board)
end

function ItemsPage:addCell(name, cell)
    if self.listBox_[name] then return end
    self.listBox_[name] = cell
end

function ItemsPage:removeAllCells()
    for name, cell in pairs(self.listBox_) do
        self:removeCell(name)
    end
    self.listBox_ = {}
end

function ItemsPage:removeCell(name)
    self.listBox_[name]:removeSelf()
    self.listBox_[name] = nil
end

return ItemsPage