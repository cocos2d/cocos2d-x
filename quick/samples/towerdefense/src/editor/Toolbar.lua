
local AutoLayout = require("editor.AutoLayout")
local ToolBase   = require("editor.ToolBase")

local Toolbar = class("Toolbar")

function Toolbar:ctor(map)
    cc(self):addComponent("components.behavior.EventProtocol"):exportMethods()

    self.map_                = map
    self.tools_              = {}
    self.toolsName_          = {}

    self.toolbarHeight_      = 0
    self.defaultTouchTool_   = nil

    self.currentToolName_    = nil
    self.currentButtonIndex_ = nil
    self.sprite_             = nil

    self.isDefaultTouch_     = false
end

function Toolbar:onTouch(event, x, y)
    if y > self.toolbarHeight_ then
        local ret
        if self.isDefaultTouch_ then
            ret = self.tools_[self.defaultTouchTool_]:onIgnoredTouch(event, x, y, true)
            if ret == ToolBase.DEFAULT_TOUCH_ENDED then
                self.isDefaultTouch_ = false
                ret = false
            end
        else
            ret = self.tools_[self.currentToolName_]:onTouch(event, x, y)
            if ret == ToolBase.TOUCH_IGNORED and self.defaultTouchTool_ then
                ret = self.tools_[self.defaultTouchTool_]:onIgnoredTouch(event, x, y, true)
                if ret == true then
                    self.isDefaultTouch_ = true
                end
            end
        end
        return ret
    end
end

function Toolbar:onButtonTap(selectedTool, selectedButton)
    for toolName, tool in pairs(self.tools_) do
        if tool ~= selectedTool then
            for i, buttonSprite in ipairs(tool.buttonsSprite) do
                buttonSprite:setButtonSelected(false)
            end
        end
        for buttonIndex, button in ipairs(tool.buttons) do
            if button == selectedButton then
                self.currentButtonIndex_ = buttonIndex
            elseif button.sprite:isButtonEnabled() then
                button.sprite:setButtonSelected(false)
            end
        end
    end

    self.currentToolName_ = selectedTool:getName()
    selectedButton.sprite:setButtonSelected(true)
    selectedTool:selected(selectedButton.name)

    self:dispatchEvent({
        name       = "SELECT_TOOL",
        toolName   = self.currentToolName_,
        buttonName = selectedButton.name,
    })
end

function Toolbar:createView(parent, bgImageName, padding, scale, toolbarLines)
    if self.sprite_ then return end

    self.sprite_ = display.newNode()
    local bg = display.newSprite(bgImageName)
    bg:setScaleX((display.width / bg:getContentSize().width) * 2)
    bg:setScaleY(scale * toolbarLines)
    bg:align(display.CENTER_BOTTOM, display.cx, 0)
    self.toolbarHeight_ = bg:getContentSize().height * scale
    self.sprite_:addChild(bg)

    local menu = display.newNode()
    local items = {}
    for toolIndex, toolName in ipairs(self.toolsName_) do
        if toolbarLines > 1 and toolIndex == 3 then
            items[#items + 1] = "#"
        elseif toolIndex > 1 then
            items[#items + 1] = "-"
        end

        local tool = self.tools_[toolName]
        tool.buttonsSprite = {}
        for buttonIndex, button in ipairs(tool.buttons) do
            button.sprite = cc.ui.UICheckBoxButton.new({
                off = button.image,
                on = button.imageSelected,
            })
            button.sprite:onButtonClicked(function() self:onButtonTap(tool, button) end)
            button.sprite:setScale(scale)
            menu:addChild(button.sprite)
            tool.buttonsSprite[#tool.buttonsSprite + 1] = button.sprite
            items[#items + 1] = button.sprite
        end
    end

    self.sprite_:addChild(menu)
    AutoLayout.alignItemsHorizontally(items, padding * scale, self.toolbarHeight_ / 2, padding * scale, toolbarLines)

    -- 放大缩小按钮
    cc.ui.UIPushButton.new("#ZoomInButton.png")
        :onButtonClicked(function(event)
            local scale = self.map_:getCamera():getScale()
            if scale < 2.0 then
                scale = scale + 0.5
                if scale > 2.0 then scale = 2.0 end
                self.map_:getCamera():setScale(scale)
                self.map_:updateView()
                self.scaleLabel_:setString(string.format("%0.2f", scale))
            end
        end)
        :align(display.CENTER, display.right - 72 * scale, self.toolbarHeight_ / 2)
        :addTo(self.sprite_)
        :setScale(scale)

    cc.ui.UIPushButton.new("#ZoomOutButton.png")
        :onButtonClicked(function(event)
            local scale = self.map_:getCamera():getScale()
            if scale > 0.5 then
                scale = scale - 0.5
                if scale < 0.5 then scale = 0.5 end
                self.map_:getCamera():setScale(scale)
                self.map_:updateView()
                self.scaleLabel_:setString(string.format("%0.2f", scale))
            end
        end)
        :align(display.CENTER, display.right - 28 * scale, self.toolbarHeight_ / 2)
        :addTo(self.sprite_)
        :setScale(scale)

    -- local zoomInButton = ui.newImageMenuItem({
    --     image    = "#ZoomInButton.png",
    --     x        = display.right - 72 * scale,
    --     y        = self.toolbarHeight_ / 2,
    --     listener = function()
    --         local scale = self.map_:getCamera():getScale()
    --         if scale < 2.0 then
    --             scale = scale + 0.5
    --             if scale > 2.0 then scale = 2.0 end
    --             self.map_:getCamera():setScale(scale)
    --             self.map_:updateView()
    --             self.scaleLabel_:setString(string.format("%0.2f", scale))
    --         end
    --     end
    -- })
    -- zoomInButton:setScale(scale)

    -- local zoomOutButton = ui.newImageMenuItem({
    --     image    = "#ZoomOutButton.png",
    --     x        = display.right - 28 * scale,
    --     y        = self.toolbarHeight_ / 2,
    --     listener = function()
    --         local scale = self.map_:getCamera():getScale()
    --         if scale > 0.5 then
    --             scale = scale - 0.5
    --             if scale < 0.5 then scale = 0.5 end
    --             self.map_:getCamera():setScale(scale)
    --             self.map_:updateView()
    --             self.scaleLabel_:setString(string.format("%0.2f", scale))
    --         end
    --     end
    -- })
    -- zoomOutButton:setScale(scale)

    -- local zoombar = ui.newMenu({zoomInButton, zoomOutButton})
    -- self.sprite_:addChild(zoombar)

    self.scaleLabel_ = cc.ui.UILabel.new({
        text  = "1.00",
        font  = display.DEFAULT_TTF_FONT,
        size  = 24 * scale,
        color = cc.c3b(255, 255, 255),
        align = cc.ui.TEXT_ALIGN_RIGHT,
        x     = display.right - 96 * scale,
        y     = self.toolbarHeight_ / 2,
    }):align(display.CENTER)
    self.scaleLabel_:align(display.CENTER_RIGHT, display.right - 96 * scale, self.toolbarHeight_ / 2)
    self.sprite_:addChild(self.scaleLabel_)

    parent:addChild(self.sprite_)

    self.sprite_:addNodeEventListener(cc.NODE_EVENT, function(event)
        if event.name == "exit" then
            self:removeAllEventListeners()
        end
    end)

    return self.sprite_
end

function Toolbar:getView()
    return self.sprite_
end

function Toolbar:addTool(tool)
    self.tools_[tool:getName()] = tool
    self.toolsName_[#self.toolsName_ + 1] = tool:getName()
end

function Toolbar:setDefaultTouchTool(toolName)
    self.defaultTouchTool_ = toolName
end

function Toolbar:selectButton(toolName, buttonIndex)
    assert(self.sprite_, "Toolbar sprites not created")
    self:onButtonTap(self.tools_[toolName], self.tools_[toolName].buttons[buttonIndex])
end

function Toolbar:getSelectedButtonName()
    return self.tools_[self.currentToolName_].buttons[self.currentButtonIndex_].name
end

function Toolbar:showNotice(text, fontsize, delay)
    local label = cc.ui.UILabel.new({
        text = "Save map ok",
        size = fontsize or 96,
        color = cc.c3b(100, 255, 100),
        align = cc.ui.TEXT_ALIGN_CENTER,
    }):align(display.CENTER)

    label:setPosition(display.cx, display.cy)
    self:getView():addChild(label)

    transition.moveBy(label, {y = 20, time = 1.0, delay = delay or 0.5})
    transition.fadeOut(label, {time = 1.0, delay = delay or 0.5, onComplete = function()
        label:removeSelf()
    end})
end

return Toolbar
