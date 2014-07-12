require("Cocos2d")
require("Cocos2dConstants")

collectgarbage("setpause", 100) 
collectgarbage("setstepmul", 5000)

local mediumResource =
{
    size = cc.size(960, 540),
    directory = "ipad",
}

local largeResource = 
{
    size = cc.size(1920, 1080),
    directory = "ipadhd",
}

local director = cc.Director:getInstance()
local glView = director:getOpenGLView()
if nil == glView then
    glView = cc.GLView:create("Game Controller Test")
    director:setOpenGLView(glView)
end

director:setOpenGLView(glView)

local designResolutionSize = cc.size(1920, 1080)

glView:setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, cc.ResolutionPolicy.SHOW_ALL)

local frameSize = glView:getFrameSize()

local targetPlatform = cc.Application:getInstance():getTargetPlatform()
local resPrefix = ""
if targetPlatform == cc.PLATFORM_OS_ANDROID then
    resPrefix = "res/"
end

local fileUtils = cc.FileUtils:getInstance()
local searchPaths = fileUtils:getSearchPaths()

table.insert(searchPaths, 1, resPrefix)
if frameSize.height > mediumResource.size.height then
    table.insert(searchPaths, 1, resPrefix..largeResource.directory)
    cc.Director:getInstance():setContentScaleFactor(math.min(largeResource.size.height/designResolutionSize.height, largeResource.size.width/designResolutionSize.width))
else
    table.insert(searchPaths, 1, resPrefix..mediumResource.directory)
    cc.Director:getInstance():setContentScaleFactor(math.min(mediumResource.size.height/designResolutionSize.height, mediumResource.size.width/designResolutionSize.width))
end

fileUtils:setSearchPaths(searchPaths)

local scene = cc.Scene:create()
scene:addChild(require("src/GameControllerTest").new())
if cc.Director:getInstance():getRunningScene() then
    cc.Director:getInstance():replaceScene(scene)
else
    cc.Director:getInstance():runWithScene(scene)
end