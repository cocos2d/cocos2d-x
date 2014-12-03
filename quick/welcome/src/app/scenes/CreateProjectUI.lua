--
-- FILE: CreateProjectUI.lua
-- DATE: 2014-08-21
--

local EditBoxLite = import(".EditBoxLite")
local eventDispatcher = cc.Director:getInstance():getEventDispatcher()

local CreateProjectUI = class("CreateProjectUI", function()
        return display.newColorLayer(cc.c4b(56, 56, 56, 250))
    end)

-- settings
local fontSize = 25
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
function CreateProjectUI:ctor()
    self:addNodeEventListener(cc.NODE_EVENT, function(e)
            if e.name == "enter" then self:onEnter()
            elseif e.name == "exit" then
                eventDispatcher:removeEventListener(self.eventListenerCustom_)
            end
        end)
end

function CreateProjectUI:onEnter()

    -- project location:
    cc.ui.UILabel.new({
        UILabelType = 2,
        text = "Choose Project Location:",
        size = fontSize,
        color = display.COLOR_WHITE
        })
    :align(display.LEFT_CENTER, 40, display.top - 55)
    :addTo(self)

    local t = {
        image = "#ButtonNormal.png",
        size = cc.size(display.width-250, 40),
        x = 40,
        y = display.top - 120,
    }

    local locationEditbox = EditBoxLite.create(t)
    locationEditbox:setAnchorPoint(0,0)
    self:addChild(locationEditbox)

    local selectButton = cc.ui.UIPushButton.new(images, {scale9 = true})
    selectButton:setAnchorPoint(0,0)
    selectButton:setButtonSize(150, 40)
    :setButtonLabel("normal", cc.ui.UILabel.new({
            UILabelType = 2,
            text = "Select",
            size = fontSize,
        }))
    :pos(display.right - 170, display.top - 120)
    :addTo(self)
    :onButtonClicked(function()
        local filedialog = PlayerProtocol:getInstance():getFileDialogService()
        local locationDirectory = filedialog:openDirectory("Choose Localtion", "")
        if string.len(locationDirectory) > 0 then
            locationEditbox:setText(locationDirectory)
        end
    end)


    -- package name:

    cc.ui.UILabel.new({
        UILabelType = 2,
        text = "Project package name: (etc: com.mycomp.games.mygame)",
        size = fontSize,
        color = display.COLOR_WHITE,
        })
    :align(display.LEFT_CENTER, 40, display.top - 155)
    :addTo(self)

    local packageEditbox = EditBoxLite.create({
        image = "#ButtonNormal.png",
        size = cc.size(display.width-250, 40),
        x = 40,
        y = display.top - 220,
    })
    packageEditbox:setAnchorPoint(0,0)
    self:addChild(packageEditbox)

    -- screen direction:

    cc.ui.UILabel.new({
        UILabelType = 2,
        text = "Screen Direction:",
        size = fontSize,
        color = display.COLOR_WHITE,
        })
    :align(display.LEFT_CENTER, 40, display.top - 255)
    :addTo(self)

    local portraitCheckBox =
    cc.ui.UICheckBoxButton.new(checkboxImages)
        :setButtonLabel(cc.ui.UILabel.new({text = "Portrait", size = fontSize,  color = display.COLOR_WHITE}))
        :setButtonLabelOffset(30, 0)
        :setButtonLabelAlignment(display.LEFT_CENTER)
        :align(display.LEFT_CENTER, 40, display.cy)
        :onButtonClicked(function() self.landscapeCheckBox:setButtonSelected(not self.portraitCheckBox:isButtonSelected()) end)
        :addTo(self)

    local landscapeCheckBox =
    cc.ui.UICheckBoxButton.new(checkboxImages)
        :setButtonLabel(cc.ui.UILabel.new({text = "Landscape", size = fontSize,  color = display.COLOR_WHITE}))
        :setButtonLabelOffset(30, 0)
        :setButtonLabelAlignment(display.LEFT_CENTER)
        :align(display.LEFT_CENTER, 230, display.cy)
        :onButtonClicked(function() self.portraitCheckBox:setButtonSelected(not self.landscapeCheckBox:isButtonSelected()) end)
        :addTo(self)

    portraitCheckBox:setButtonSelected(true)
    self.portraitCheckBox = portraitCheckBox
    self.landscapeCheckBox = landscapeCheckBox


    -- copy source if
    self.copySourceCB_ = cc.ui.UICheckBoxButton.new(checkboxImages)
        :setButtonLabel(cc.ui.UILabel.new({text = "Copy Source Files", size = fontSize,  color = display.COLOR_WHITE}))
        :setButtonLabelOffset(30, 0)
        :setButtonLabelAlignment(display.LEFT_CENTER)
        :align(display.LEFT_CENTER, 40, display.cy - 50)
        :addTo(self)
        :setButtonSelected(true)


    -- ok or cancel

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
    createProjectbutton.currState = 1
    createProjectbutton:setAnchorPoint(0,0)
    createProjectbutton:setButtonSize(250, 40)
    :setButtonLabel("normal", cc.ui.UILabel.new({
            UILabelType = 2,
            text = "Create Project",
            size = fontSize,
        }))
    :pos(display.right - 270, 30)
    :addTo(self)
    :onButtonClicked(function()
        if createProjectbutton.currState == 1 then
            if string.len(locationEditbox:getText()) > 0 and string.len(packageEditbox:getText()) > 0 then
                createProjectbutton:setButtonLabelString("normal", "Processing ...")
                local t = packageEditbox:getText():splitBySep('.')
                self.projectFolder = locationEditbox:getText() .. device.directorySeparator .. t[#t]

                local projectConfig = ProjectConfig:new()
                projectConfig:setProjectDir(self.projectFolder)
                projectConfig:changeFrameOrientationToPortait()
                self.projectConfig = projectConfig

                local scriptPath = cc.player.quickRootPath .. "quick/bin/create_project.sh"
                if device.platform == "windows" then
                    scriptPath = cc.player.quickRootPath .. "quick/bin/create_project.bat"
                end

                local screenDirection = " -r portrait "
                if self.landscapeCheckBox:isButtonSelected() then
                    projectConfig:changeFrameOrientationToLandscape()
                    screenDirection = " -r landscape "
                end
                local copySource = ""
                if not self.copySourceCB_:isButtonSelected() then
                    copySource = " -lt "
                end
                local arguments = " -p " .. packageEditbox:getText() .. " -f " .. " -o " .. self.projectFolder .. screenDirection .. copySource
                local taskId = tostring(os.time())

                -- local scriptPath = cc.player.quickRootPath .. "cocos new"

                -- local screenDirection = "-r portrait"
                -- if self.landscapeCheckBox:isButtonSelected() then
                --     projectConfig:changeFrameOrientationToLandscape()
                --     screenDirection = "-r landscape"
                -- end

                -- local cmds = {}
                -- table.insert(cmds, "-l lua")
                -- table.insert(cmds, "-t quick")
                -- table.insert(cmds, "-d " .. self.projectFolder)
                -- table.insert(cmds, "-p " .. packageEditbox:getText())
                -- table.insert(cmds, screenDirection)

                -- local arguments = table.concat(cmds, " ")
                -- arguments = " " .. arguments
                
                print("Create Cmd:" .. scriptPath .. " " .. arguments)
                local task = PlayerProtocol:getInstance():getTaskService():createTask(taskId, scriptPath, arguments)
                eventDispatcher:addEventListenerWithFixedPriority(cc.EventListenerCustom:create(taskId,
                            function()
                                if task:getResultCode() == 0 then
                                    createProjectbutton:setButtonLabelString("normal", "Open ...")
                                    createProjectbutton.currState = 2
                                else
                                    createProjectbutton:setButtonLabelString("normal", "Create Project")
                                    local messageBox = PlayerProtocol:getInstance():getMessageBoxService()
                                    messageBox:showMessageBox("player v3", task:getOutput())
                                end
                            end),
                           1)
                task:runInTerminal()

                createProjectbutton:setButtonLabelString("normal", "Open ...")
                createProjectbutton.currState = 2
                local messageBox = PlayerProtocol:getInstance():getMessageBoxService()
                messageBox:showMessageBox("player v3", "Please wait create success and then click Open")
            else
                local messageBox = PlayerProtocol:getInstance():getMessageBoxService()
                messageBox:showMessageBox("player v3", "please fill all infomation..")
            end
        else
            PlayerProtocol:getInstance():openNewPlayerWithProjectConfig(self.projectConfig)
        end
    end)

    -- keyboard event
    local event = function(e)
        local data = json.decode(e:getDataString())
        if data == nil then return end

        -- esc keyc = 6
        if data.data == 6 then self:removeFromParent(true) end
    end
    self.eventListenerCustom_ = cc.EventListenerCustom:create("APP.EVENT", event)
    eventDispatcher:addEventListenerWithFixedPriority(self.eventListenerCustom_, 1)
end


return CreateProjectUI
