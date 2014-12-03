--
-- FILE: OpenProjectUI.lua
-- DATE: 2014-08-21
--

local eventDispatcher = cc.Director:getInstance():getEventDispatcher()
local EditBoxLite = import(".EditBoxLite")

local OpenProjectUI = class("OpenProjectUI", function()
        return display.newColorLayer(cc.c4b(56, 56, 56, 250))
    end)

-- settings
local fontSize = 20
local images = {
    normal = "#ButtonNormal.png",
    pressed = "#ButtonPressed.png",
    disabled = "#ButtonDisabled.png",
}
local checkboxImages = {
    off = "CheckBoxButton2Off.png",
    on = "CheckBoxButton2On.png",
}

--
function OpenProjectUI:ctor()
    self:addNodeEventListener(cc.NODE_EVENT, function(e) 
            if e.name == "enter" then 
                self:onEnter() 
            elseif e.name == "exit" then 
                eventDispatcher:removeEventListener(self.eventListenerCustom_)
            end 
        end)
end

function OpenProjectUI:updatePanelInfo()
    local configPath = self.location:getText() .. '/src/config.lua'

    if cc.FileUtils:getInstance():isFileExist(configPath) then
        local data = ""
        for line in io.lines(configPath) do
            if string.find(line, "CONFIG_SCREEN_WIDTH") then
                data = data .. line .. ',\n'
            elseif string.find(line, "CONFIG_SCREEN_HEIGHT") then
                data = data .. line .. ',\n'
            elseif string.find(line, "CONFIG_SCREEN_ORIENTATION") then
                data = data .. line .. ',\n'
            end
        end

        local config = assert(loadstring("local settings = {" .. data .. "} return settings"))()

        local with = tonumber(config.CONFIG_SCREEN_WIDTH)
        local height = tonumber(config.CONFIG_SCREEN_HEIGHT)

        -- screen direction
        if config.CONFIG_SCREEN_ORIENTATION == "portrait" then
            self.portraitCheckBox:setButtonSelected(true)
            self.landscapeCheckBox:setButtonSelected(false)
        elseif config.CONFIG_SCREEN_ORIENTATION == "landscape" then
            self.landscapeCheckBox:setButtonSelected(true)
            self.portraitCheckBox:setButtonSelected(false)
        end
    end

end

function OpenProjectUI:onEnter()
    
    local y = 0
    self:createLabelAndEditLineAndButton("location", "Choose Project Directory:", "", "Select ...",
        function()
            local filedialog = PlayerProtocol:getInstance():getFileDialogService()
            local directory = filedialog:openDirectory("Choose Localtion", "")
            if string.len(directory) > 0 then
                self.location:setText(directory)
                self:updatePanelInfo()
            end
        end)
        :addTo(self)

    y = y - 80
    self:createLabelAndEditLineAndButton("scriptFile", "Script File:", "$(PROJDIR)/src/main.lua", "Select ...",
        function()
            local filedialog = PlayerProtocol:getInstance():getFileDialogService()
            local scriptPath = filedialog:openFile("Choose main.lua", "", "Lua Script File|*.lua")
            if string.len(scriptPath) > 0 then
                self.scriptFile:setText(scriptPath)
            end
        end)
        :pos(0, y)
        :addTo(self)

    y = y - 80
    self:createLabelAndEditLineAndButton("writablePath", "WritablePath:", "$(PROJDIR)/", "Select ...",
        function()
            local filedialog = PlayerProtocol:getInstance():getFileDialogService()
            local directory = filedialog:openDirectory("Choose Writeable directory", "")
            if string.len(directory) > 0 then
                self.writablePath:setText(directory)
            end
        end)
        :pos(0, y)
        :addTo(self)

    -- screen direction:

    cc.ui.UILabel.new({
        UILabelType = 2,
        text = "Screen Direction:",
        size = fontSize,
        color = display.COLOR_WHITE,
        })
    :align(display.LEFT_CENTER, 40, display.top - 300)
    :addTo(self)

    self.portraitCheckBox = 
    cc.ui.UICheckBoxButton.new(checkboxImages)
        :setButtonLabel(cc.ui.UILabel.new({text = "Portrait", size = fontSize,  color = display.COLOR_WHITE}))
        :setButtonLabelOffset(30, 0)
        :setButtonLabelAlignment(display.LEFT_CENTER)
        :align(display.LEFT_CENTER, 40, display.cy-20)
        :onButtonClicked(function() self.landscapeCheckBox:setButtonSelected(not self.portraitCheckBox:isButtonSelected()) end)
        :addTo(self)
        :setButtonSelected(true)

    self.landscapeCheckBox = 
    cc.ui.UICheckBoxButton.new(checkboxImages)
        :setButtonLabel(cc.ui.UILabel.new({text = "Landscape", size = fontSize,  color = display.COLOR_WHITE}))
        :setButtonLabelOffset(30, 0)
        :setButtonLabelAlignment(display.LEFT_CENTER)
        :align(display.LEFT_CENTER, 200, display.cy-20)
        :onButtonClicked(function() self.portraitCheckBox:setButtonSelected(not self.landscapeCheckBox:isButtonSelected()) end)
        :addTo(self)

    -- Options:

    cc.ui.UILabel.new({
        UILabelType = 2,
        text = "Options:",
        size = fontSize,
        color = display.COLOR_WHITE,
        })
    :pos(40, display.top - 400)
    :addTo(self)

    self.showDebugConsole =
    cc.ui.UICheckBoxButton.new(checkboxImages)
        :setButtonLabel(cc.ui.UILabel.new({text = "Show Debug Console", size = fontSize,  color = display.COLOR_WHITE}))
        :setButtonLabelOffset(30, 0)
        :setButtonLabelAlignment(display.CENTER_LEFT)
        :align(display.LEFT_CENTER, 40, display.cy-120)
        :addTo(self)
        :setButtonSelected(true)

    self.writeDebugToFile =
    cc.ui.UICheckBoxButton.new(checkboxImages)
        :setButtonLabel(cc.ui.UILabel.new({text = "Write Debug Log to File", size = fontSize,  color = display.COLOR_WHITE}))
        :setButtonLabelOffset(30, 0)
        :setButtonLabelAlignment(display.CENTER_LEFT)
        :align(display.LEFT_CENTER, display.cx, display.cy-120)
        :addTo(self)
        :setButtonSelected(true)

    self.loadPrecompiledFramework =
    cc.ui.UICheckBoxButton.new(checkboxImages)
        :setButtonLabel(cc.ui.UILabel.new({text = "Load precompiled framework", size = fontSize,  color = display.COLOR_WHITE}))
        :setButtonLabelOffset(30, 0)
        :setButtonLabelAlignment(display.CENTER_LEFT)
        :align(display.LEFT_CENTER, 40, display.cy-170)
        :addTo(self)
        :setButtonSelected(false)

    --
    self:createYesOrNoButton()
    self:registerEvents() 
end

function OpenProjectUI:createYesOrNoButton()
    local button = cc.ui.UIPushButton.new(images, {scale9 = true})
    button:setAnchorPoint(0,0)
    button:setButtonSize(150, 40)
    :setButtonLabel("normal", cc.ui.UILabel.new({
            UILabelType = 2,
            text = "Cancel",
            size = fontSize,
        }))
    :pos(40, 30)
    :addTo(self)
    :onButtonClicked(function()
        self:removeFromParent(true)
    end)

    local createProjectbutton = cc.ui.UIPushButton.new(images, {scale9 = true})
    createProjectbutton:setAnchorPoint(0,0)
    createProjectbutton:setButtonSize(250, 40)
    :setButtonLabel("normal", cc.ui.UILabel.new({
            UILabelType = 2,
            text = " Open Project ",
            size = fontSize,
        }))
    :pos(display.right - 270, 30)
    :addTo(self)
    :onButtonClicked(function()
        local projectConfig = ProjectConfig:new()
        projectConfig:setProjectDir(self.location:getText())
        projectConfig:setScriptFile(self.scriptFile:getText())
        projectConfig:setWritablePath(self.writablePath:getText())
        projectConfig:setShowConsole(self.showDebugConsole:isButtonSelected())
        projectConfig:setWriteDebugLogToFile(self.writeDebugToFile:isButtonSelected())
        projectConfig:setLoadPrecompiledFramework(self.loadPrecompiledFramework:isButtonSelected())

        -- screen direction
        if self.portraitCheckBox:isButtonSelected() then
            projectConfig:changeFrameOrientationToPortait()
        else
            projectConfig:changeFrameOrientationToLandscape()
        end

        -- PlayerProtocol:getInstance():openNewPlayerWithProjectConfig(projectConfig)
        PlayerProtocol:getInstance():openProjectWithProjectConfig(projectConfig)
    end)
end

function OpenProjectUI:registerEvents()
    -- keyboard event
    local event = function(e)
        local data = json.decode(e:getDataString())
        if data == nil then return end

        -- esc keycode: 6
        if data.data == 6 then self:removeFromParent(true) end
    end
    self.eventListenerCustom_ = cc.EventListenerCustom:create("APP.EVENT", event)
    eventDispatcher:addEventListenerWithFixedPriority(self.eventListenerCustom_, 1)
end

function OpenProjectUI:createLabelAndEditLineAndButton(holder, labelString, editLineString, buttonString, listener)
    local node = display.newNode()

    -- label:
    cc.ui.UILabel.new({
        UILabelType = 2,
        text = labelString,
        size = fontSize,
        color = display.COLOR_WHITE,
        })
    :pos(40, display.top - 55)
    :addTo(node)

    -- edit line
    local locationEditbox = EditBoxLite.create({
        image = "#ButtonNormal.png",
        size = cc.size(display.width-250, 40),
        x = 40,
        y = display.top - 120,
    })
    locationEditbox:setAnchorPoint(0,0)
    locationEditbox:setText(editLineString)
    node:addChild(locationEditbox)

    -- button
    local selectButton = cc.ui.UIPushButton.new(images, {scale9 = true})
    selectButton:setAnchorPoint(0,0)
    selectButton:setButtonSize(150, 40)
    :setButtonLabel("normal", cc.ui.UILabel.new({
            UILabelType = 2,
            text = buttonString,
            size = fontSize,
        }))
    :pos(display.right - 170, display.top - 120)
    :addTo(node)
    :onButtonClicked(listener)

    self[holder] = locationEditbox
    return node
end

function OpenProjectUI:updatePanelInfo()
    local configPath = self.location:getText() .. '/src/config.lua'

    if cc.FileUtils:getInstance():isFileExist(configPath) then
        local data = ""
        for line in io.lines(configPath) do
            if string.find(line, "CONFIG_SCREEN_WIDTH") then
                data = data .. line .. ',\n'
            elseif string.find(line, "CONFIG_SCREEN_HEIGHT") then
                data = data .. line .. ',\n'
            elseif string.find(line, "CONFIG_SCREEN_ORIENTATION") then
                data = data .. line .. ',\n'
            end
        end

        local config = assert(loadstring("local settings = {" .. data .. "} return settings"))()

        local with = tonumber(config.CONFIG_SCREEN_WIDTH)
        local height = tonumber(config.CONFIG_SCREEN_HEIGHT)

        -- screen direction
        if config.CONFIG_SCREEN_ORIENTATION == "portrait" then
            self.portraitCheckBox:setButtonSelected(true)
            self.landscapeCheckBox:setButtonSelected(false)
        elseif config.CONFIG_SCREEN_ORIENTATION == "landscape" then
            self.landscapeCheckBox:setButtonSelected(true)
            self.portraitCheckBox:setButtonSelected(false)
        end
    end

end

return OpenProjectUI