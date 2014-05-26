
-- avoid memory leak
collectgarbage("setpause", 100) 
collectgarbage("setstepmul", 5000)
	
require "src/mainMenu"
----------------


-- run

local glView = cc.Director:getInstance():getOpenGLView()
local screenSize = glView:getFrameSize()
local designSize = {width = 480, height = 320}
local fileUtils = cc.FileUtils:getInstance()

if screenSize.height > 320 then
    local searchPaths = {}
    table.insert(searchPaths, "hd")
    fileUtils:setSearchPaths(searchPaths)
end

local targetPlatform = cc.Application:getInstance():getTargetPlatform()
local resPrefix = ""
if cc.PLATFORM_OS_IPAD  == targetPlatform or cc.PLATFORM_OS_IPHONE == targetPlatform or cc.PLATFORM_OS_MAC == targetPlatform then
    resPrefix = ""
else
    resPrefix = "res/"
end

local searchPaths = fileUtils:getSearchPaths()
table.insert(searchPaths, 1, resPrefix)
table.insert(searchPaths, 1, resPrefix .. "cocosbuilderRes")

if screenSize.height > 320 then
    table.insert(searchPaths, 1, resPrefix .. "hd")
    table.insert(searchPaths, 1, resPrefix .. "ccs-res")
    table.insert(searchPaths, 1, resPrefix .. "ccs-res/hd")
    table.insert(searchPaths, 1, resPrefix .. "ccs-res/hd/Images")
    table.insert(searchPaths, 1, resPrefix .. "ccs-res/hd/scenetest/ArmatureComponentTest")
    table.insert(searchPaths, 1, resPrefix .. "ccs-res/hd/scenetest/AttributeComponentTest")
    table.insert(searchPaths, 1, resPrefix .. "ccs-res/hd/scenetest/BackgroundComponentTest")
    table.insert(searchPaths, 1, resPrefix .. "ccs-res/hd/scenetest/EffectComponentTest")
    table.insert(searchPaths, 1, resPrefix .. "ccs-res/hd/scenetest/LoadSceneEdtiorFileTest")
    table.insert(searchPaths, 1, resPrefix .. "ccs-res/hd/scenetest/ParticleComponentTest")
    table.insert(searchPaths, 1, resPrefix .. "ccs-res/hd/scenetest/SpriteComponentTest")
    table.insert(searchPaths, 1, resPrefix .. "ccs-res/hd/scenetest/TmxMapComponentTest")
    table.insert(searchPaths, 1, resPrefix .. "ccs-res/hd/scenetest/UIComponentTest")
    table.insert(searchPaths, 1, resPrefix .. "ccs-res/hd/scenetest/TriggerTest")
else
    table.insert(searchPaths, 1, resPrefix .. "ccs-res/Images")
    table.insert(searchPaths, 1, resPrefix .. "ccs-res/scenetest/ArmatureComponentTest")
    table.insert(searchPaths, 1, resPrefix .. "ccs-res/scenetest/AttributeComponentTest")
    table.insert(searchPaths, 1, resPrefix .. "ccs-res/scenetest/BackgroundComponentTest")
    table.insert(searchPaths, 1, resPrefix .. "ccs-res/scenetest/EffectComponentTest")
    table.insert(searchPaths, 1, resPrefix .. "ccs-res/scenetest/LoadSceneEdtiorFileTest")
    table.insert(searchPaths, 1, resPrefix .. "ccs-res/scenetest/ParticleComponentTest")
    table.insert(searchPaths, 1, resPrefix .. "ccs-res/scenetest/SpriteComponentTest")
    table.insert(searchPaths, 1, resPrefix .. "ccs-res/scenetest/TmxMapComponentTest")
    table.insert(searchPaths, 1, resPrefix .. "ccs-res/scenetest/UIComponentTest")
    table.insert(searchPaths, 1, resPrefix .. "ccs-res/scenetest/TriggerTest")
end

fileUtils:setSearchPaths(searchPaths)

local scene = cc.Scene:create()
scene:addChild(CreateTestMenu())
if cc.Director:getInstance():getRunningScene() then
    cc.Director:getInstance():replaceScene(scene)
else
    cc.Director:getInstance():runWithScene(scene)
end
