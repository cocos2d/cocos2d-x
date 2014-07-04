--[[
    file: player.lua

    player 的 lua 核心
]]

--
-- 返回 table 的字符串
--

local function table_print (tt, indent, done)
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

        table.insert(sb, table_print (value, indent + 2, done))
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
      -- else
      --   table.insert(sb, string.format(
      --       "%s = \"%s\",\n", tostring (key), tostring(value)))
       end
    end
    return table.concat(sb)
  else
    return tt .. "\n"
  end
end

local function to_string( tbl )
    if  "nil"       == type( tbl ) then
        return tostring(nil)
    elseif  "table" == type( tbl ) then
        return table_print(tbl)
    elseif  "string" == type( tbl ) then
        return tbl
    else
        return tostring(tbl)
    end
end

--
-- save player setting to ~/.quick_player.lua
--
local player = {}
player.defaultSettings = [[
PLAYER_COCOACHINA_KEY = "USER_KEY",
PLAYER_COCOACHINA_USER = "USER_NAME",
PLAYER_WINDOW_X = 0,
PLAYER_WINDOW_Y = 0,
PLAYER_WINDOW_WIDTH = 960,
PLAYER_WINDOW_HEIGHT = 640,
PLAYER_OPEN_LAST_PROJECT = true,
PLAYER_OPEN_RECTNS ={
},

]]

function player.saveSetting(fileName)
    fileName = fileName or player.configFilePath
    local file, err = io.open(fileName, "wb")
    if err then return err end

    -- table.sort(cc.player.settings)
    local ret = to_string(cc.player.settings)
    file:write(ret)
    file:close()
end

function player.loadSetting(fileName)
    local file, err = io.open(fileName, "rb")
    if err then return err end

    local data = file:read("*all")
    local func = loadstring("local settings = {" .. data .. "} return settings")
    cc.player.settings = func()
end

function player.restorDefaultSettings()
    local func = loadstring("local settings = {" .. player.defaultSettings .. "} return settings")
    cc.player.settings = func()
    player.saveSetting()
end

--
-- title: string
-- args : table
--
function player.openProject( title, args )
    local welcomeTitle = __G__QUICK_PATH__ .. "player/welcome/"
    if title == welcomeTitle then return end

    local recents = cc.player.settings.PLAYER_OPEN_RECTNS
    if recents then
        local index = #recents
        while index > 0 do
            local v = recents[index]
            if v.title == title then table.remove(recents, index) end
            index = index - 1
        end
        table.insert(recents, 1, {title=title, args=args})
        cc.player.saveSetting()
    end
end

function player.clearMenu()
    cc.player.settings.PLAYER_OPEN_RECTNS = {}
    player.saveSetting()
end

function player.buildUI()
    -- local menu = PlayerProtocol:getInstance():getMenuService()
    -- local item = PlayerMenuItem:new()
    -- item.itemId = "MENU_MORE"
    -- item.title = "More";
    -- item.isGroup = true
    -- menu:addItem(item, "", 4)

    -- item.itemId= "MORE_UPGRADE"
    -- item.title = "Upgrade to full version";
    -- item.isGroup = false
    -- item.scriptHandlerId = function() print("run 'upgrade' script to upgrade to full version") end
    -- menu:addItem(item, "MENU_MORE")
end

function player.init()
    player.configFilePath = __USER_HOME__ .. ".quick_player.lua"
    if not cc.FileUtils:getInstance():isFileExist(player.configFilePath) then player.restorDefaultSettings() end

    player.loadSetting(player.configFilePath)

    local s = PlayerSettings:new()
    s.offsetX = cc.player.settings.PLAYER_WINDOW_X
    s.offsetY = cc.player.settings.PLAYER_WINDOW_Y 
    s.windowWidth = cc.player.settings.PLAYER_WINDOW_WIDTH 
    s.windowHeight = cc.player.settings.PLAYER_WINDOW_HEIGHT 
    s.openLastProject = cc.player.settings.PLAYER_OPEN_LAST_PROJECT
    PlayerProtocol:getInstance():setPlayerSettings(s)
end

-- load player settings


cc = cc or {}
cc.player = cc.player or player

cc.player.init()

function __PLAYER_OPEN__(title, args)
    cc.player.openProject(title, args)
    cc.player.buildUI()
end