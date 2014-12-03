--[[
    file: player.lua

    player 的 lua 核心
]]

--
-- 返回 table 的字符串
--

function table.serializeToString (tt, indent, done)
  done = done or {}
  indent = indent or 0
  if type(tt) == "table" then
    local sb = {}
    for key, value in pairs (tt) do
      table.insert(sb, string.rep (" ", indent)) -- indent it
      if type (value) == "table" and not done [value] then
        done [value] = true

        if "string" == type(key) then
            table.insert(sb, string.format("%s ={\n", tostring(key)));
        else
            table.insert(sb, "{\n");
        end

        table.insert(sb, table.serializeToString (value, indent + 2, done))
        table.insert(sb, string.rep (" ", indent)) -- indent it
        table.insert(sb, "},\n");
      elseif type(value) == "function" then

      elseif "number" == type(key) then
        table.insert(sb, string.format("\"%s\",\n", tostring(value)))
      elseif type (value) == "number" then
                table.insert(sb, string.format(
            "%s = %s,\n", tostring (key), tostring(value)))

      elseif type (value) == "string" then
                table.insert(sb, string.format(
            "%s = \"%s\",\n", tostring (key), tostring(value)))

      elseif type (value) == "boolean" then
                table.insert(sb, string.format(
            "%s = %s,\n", tostring (key), tostring(value)))
       end
    end
    return table.concat(sb)
  else
    return tt .. "\n"
  end
end

function string:splitBySep(sep)
    local sep, fields = sep or device.directorySeparator, {}
    local pattern = string.format("([^%s]+)", sep)
    self:gsub(pattern, function(c) fields[#fields+1] = c end)
    return fields
end

--
-- save player setting to ~/.quick_player.lua
--
local player = {}

function player:saveSetting(fileName)
    fileName = fileName or player.configFilePath
    local file, err = io.open(fileName, "wb")
    if err then return err end

    local ret =  table.serializeToString(self.settings)
    file:write(ret)
    file:close()
end

function player:loadSetting(fileName)
    local file, err = io.open(fileName, "rb")
    if err then return err end

    local data = file:read("*all")
    local func = loadstring("local settings = {" .. data .. "} return settings")
    self.settings = func()
    self.settings.PLAYER_OPEN_RECENTS = self.settings.PLAYER_OPEN_RECENTS or {}
    file:close()
end

function player:setQuickRootPath()
    self.quickRootPath = __G_QUICK_V3_ROOT__
    if self.quickRootPath == nil then
        local fileName = self.userHomeDir .. ".QUICK_V3_ROOT"
        local file, err = io.open(fileName, "rb")
        if err then return err end

        self.quickRootPath = file:read("*l") .. "/"
        file:close()
    end
end

function player:restorDefaultSettings()
    local func = loadstring("local settings = {" .. self.defaultSettings .. "} return settings")
    if func then
        self.settings = func()
    else
        self.settings = {}
    end
    self:saveSetting()
end

--
-- title: string
-- args : table
--
function player:openProject( title, args )
    local welcomeTitle = self.quickRootPath .. "quick/welcome/"
    if title == welcomeTitle then return end

    local recents = self.settings.PLAYER_OPEN_RECENTS
    if recents then
        local index = #recents
        while index > 0 do
            local v = recents[index]
            if v.title == title then table.remove(recents, index) end
            index = index - 1
        end
        table.insert(recents, 1, {title=title, args=args})
        self:saveSetting()
    end
end

function player:clearMenu()
    self.settings.PLAYER_OPEN_RECENTS = {}
    self:saveSetting()
end

function player:buildUI()
    local menuBar = PlayerProtocol:getInstance():getMenuService()

    -- FILE
    local fileMenu = menuBar:addItem("FILE_MENU", "&File")
    -- menuBar:addItem("QUIT_MENU", "New Project...", "FILE_MENU")
    -- menuBar:addItem("OPEN_MENU", "Open", "FILE_MENU")
    -- menuBar:addItem("SAVE_MENU", "Save", "FILE_MENU")

    -- menuBar:addItem("WELCOME_MENU_SEP", "-", "FILE_MENU")
    menuBar:addItem("WELCOME_MENU", "Welcome", "FILE_MENU")
        :setShortcut("super+w")
    -- exit
    menuBar:addItem("EXIT_MENU_SEP", "-", "FILE_MENU")
    menuBar:addItem("EXIT_MENU", "Exit", "FILE_MENU")

    -- VIEW
    local viewMenu = menuBar:addItem("VIEW_MENU", "&View")

    -- screen list
    local viewSize = {{title = "iPhone 3Gs",w=320,h=480},
                      {title = "iPhone 4",  w=640,h=960},
                      {title = "iPhone 5",  w=640,h=1136},
                      {title = "iPad",      w=768,h=1024},
                      {title = "iPad Retina", w=1536,h=2048},
                      {title = "Android",   w=480,h=800},
                      {title = "Android",   w=480,h=854},
                      {title = "Android",   w=540,h=960},
                      {title = "Android",   w=600,h=1024},
                      {title = "Android",   w=720,h=1280},
                      {title = "Android",   w=800,h=1280},
                      {title = "Android",   w=1080,h=1920},
	}
    self.screenSizeList = {}
    local s = self.projectConfig_:getFrameSize()
    for i,v in ipairs(viewSize) do
        local title = string.format("%s (%dx%d)", v.title, v.w, v.h)
        local item  = menuBar:addItem("VIEWSIZE_ITEM_MENU_"..i, title, "VIEW_MENU")
        item.width  = v.w
        item.height = v.h
        self.screenSizeList[#self.screenSizeList +1] = item

        if v.w == s.width and v.h == s.height then
            item:setChecked(true)
        elseif v.w == s.height and v.h == s.width then
            item:setChecked(true)
        end
    end

    -- direction
    menuBar:addItem("DIRECTION_MENU_SEP", "-", "VIEW_MENU")
    local portrait = menuBar:addItem("DIRECTION_PORTRAIT_MENU", "Portrait", "VIEW_MENU")
    portrait.type  = "portrait"
    if self.projectConfig_:isPortraitFrame() then portrait:setChecked(true) end

    local landscape = menuBar:addItem("DIRECTION_LANDSCAPE_MENU", "Landscape", "VIEW_MENU")
    landscape.type  = "landscape"
    if self.projectConfig_:isLandscapeFrame() then landscape:setChecked(true) end

    -- scale
    menuBar:addItem("VIEW_SCALE_MENU_SEP", "-", "VIEW_MENU")
    local viewScale = {{title="Actual (100%)",st="super+0",scale=100},
                       {title="Zoom Out (75%)",st="super+6",scale=70},
                       {title="Zoom Out (50%)",st="super+5",scale=50},
                       {title="Zoom Out (25%)",st="super+4",scale=25},
                   }
    self.screenScaleList = {}
    local scaleValue     = self.projectConfig_:getFrameScale() * 100
    for i,v in ipairs(viewScale) do
        local item = menuBar:addItem("VIEW_SCALE_MENU_"..i, v.title, "VIEW_MENU")
        item:setShortcut(v.st)
        item.scale = v.scale
        self.screenScaleList[#self.screenScaleList +1] = item

        if math.ceil(scaleValue) ==  v.scale then item:setChecked(true) end
    end

    -- refresh
    menuBar:addItem("REFRESH_MENU_SEP", "-", "VIEW_MENU")
    menuBar:addItem("REFRESH_MENU", "Refresh", "VIEW_MENU")
        :setShortcut("super+r")
end

function player:registerEventHandler()
    -- for app event
    local eventDispatcher = cc.Director:getInstance():getEventDispatcher()
    local event = function(e)
        if not json then return end

        data = json.decode(e:getDataString())
        if data.name == "menuClicked" then
            self:onMenuClicked(data)
        end

    end

    eventDispatcher:addEventListenerWithFixedPriority(cc.EventListenerCustom:create("APP.EVENT", event), 1)
end

function player:onMenuClicked(event)
    local data = event.data
    if data == "CLOSE_MENU" or data == "EXIT_MENU" then
        PlayerProtocol:getInstance():quit()
    elseif data == "REFRESH_MENU" then
        PlayerProtocol:getInstance():relaunch()
    elseif data == "WELCOME_MENU" then
        local config = ProjectConfig:new()
        config:resetToWelcome()
        PlayerProtocol:getInstance():openProjectWithProjectConfig(config)
    elseif string.match(data, "VIEW_SCALE_MENU_") and self.projectConfig_ then
        local menubar = PlayerProtocol:getInstance():getMenuService()
        local item    = menubar:getItem(data)
        self:onScreenZoomOut(item)
    elseif string.match(data, "VIEWSIZE_ITEM_MENU_") and self.projectConfig_ then
        local menubar = PlayerProtocol:getInstance():getMenuService()
        local item    = menubar:getItem(data)
        self:onScreenChangeFrameSize(item)
    elseif string.match(data, "DIRECTION_") then
        local menubar = PlayerProtocol:getInstance():getMenuService()
        local item    = menubar:getItem(data)
        self:onScreenChangeDirection(item)
    end

end

function player:onScreenChangeFrameSize(sender)
    if sender:isChecked() then return end

    local w, h = sender.width, sender.height
    if self.projectConfig_:isLandscapeFrame() then
        w,h = h,w
    end

    self.projectConfig_:setFrameSize(w, h)
    self.projectConfig_:setFrameScale(1.0)
    
    local player = PlayerProtocol:getInstance()
    if player.getPositionX then
        print(player:getPositionX(), player:getPositionY())
        self.projectConfig_:setWindowOffset(player:getPositionX(), player:getPositionY())
    end

    player:openProjectWithProjectConfig(self.projectConfig_)
end

function player:onScreenChangeDirection(sender)
    if sender:isChecked() then return end

    if sender.type == "portrait" then
        self.projectConfig_:changeFrameOrientationToPortait()
    elseif sender.type == "landscape" then
        self.projectConfig_:changeFrameOrientationToLandscape()
    end

    PlayerProtocol:getInstance():openProjectWithProjectConfig(self.projectConfig_)
end

function player:onScreenZoomOut(sender)
    if sender:isChecked() then return end

    for _,v in ipairs(self.screenScaleList) do
        v:setChecked(false)
    end
    sender:setChecked(true)
    local scaleValue = sender.scale / 100.0
    self.projectConfig_:setFrameScale(scaleValue)

    local eventcustom = cc.EventCustom:new("APP.VIEW_SCALE")
    eventcustom:setDataString(tostring(scaleValue))
    cc.Director:getInstance():getEventDispatcher():dispatchEvent(eventcustom)
end

function player:readSettings()
    self.userHomeDir = __USER_HOME__
    self.configFilePath = player.userHomeDir .. ".quick_player.lua"
    if not cc.FileUtils:getInstance():isFileExist(player.configFilePath) then
        self:restorDefaultSettings()
    end
    self:loadSetting(player.configFilePath)

    -- get QUICK_V3_ROOT path
    self:setQuickRootPath()

    local s = PlayerSettings:new()
    s.offsetX = cc.player.settings.PLAYER_WINDOW_X
    s.offsetY = cc.player.settings.PLAYER_WINDOW_Y
    s.windowWidth = cc.player.settings.PLAYER_WINDOW_WIDTH
    s.windowHeight = cc.player.settings.PLAYER_WINDOW_HEIGHT
    s.openLastProject = cc.player.settings.PLAYER_OPEN_LAST_PROJECT
    PlayerProtocol:getInstance():setPlayerSettings(s)
end

function player:init()
    self.defaultSettings = [[
        PLAYER_COCOACHINA_KEY = "USER_KEY",
        PLAYER_COCOACHINA_USER = "USER_NAME",
        PLAYER_WINDOW_X = 0,
        PLAYER_WINDOW_Y = 0,
        PLAYER_WINDOW_WIDTH = 960,
        PLAYER_WINDOW_HEIGHT = 640,
        PLAYER_OPEN_LAST_PROJECT = true,
        PLAYER_OPEN_RECENTS ={
        },

    ]]

    self:registerEventHandler()
    self:readSettings()

    -- record project
    if __PLAYER_OPEN_TITLE__ and __PLAYER_OPEN_COMMAND__ then
        local title = string.gsub(__PLAYER_OPEN_TITLE__, '\\', '/')
        local args = string.gsub(__PLAYER_OPEN_COMMAND__, '\\', '/'):splitBySep(' ')

        self.projectConfig_ = ProjectConfig:new()
        local argumentVector = vector_string_:new_local()
        local arguments = args
        for _,v in ipairs(arguments) do
            argumentVector:push_back(v)
        end
        self.projectConfig_:parseCommandLine(argumentVector)
        self:openProject(title, args)
    end

    self:buildUI()
end
-- load player settings

cc = cc or {}
cc.player = cc.player or player

cc.player:init()
