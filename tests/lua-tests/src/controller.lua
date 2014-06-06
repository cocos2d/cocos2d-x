
-- avoid memory leak
collectgarbage("setpause", 100) 
collectgarbage("setstepmul", 5000)
	

----------------
-- run

local glView = cc.Director:getInstance():getOpenGLView()

local screenSize = glView:getFrameSize()
local designSize = {width = 480, height = 320}
local fileUtils = cc.FileUtils:getInstance()


local targetPlatform = cc.Application:getInstance():getTargetPlatform()

local dd = glView:getDesignResolutionSize()

if screenSize.height > 320 then
    local resourceSize = {width = 960, height = 640}
    local rate = resourceSize.height/screenSize.height
    cc.Director:getInstance():setContentScaleFactor(resourceSize.height/designSize.height);
end
glView:setDesignResolutionSize(designSize.width, designSize.height, 0);
 
local function addSearchPath(resPrefix, height)
    if height > 320 then
        fileUtils:addSearchPath(resPrefix .. "ccs-res/hd/scenetest/ArmatureComponentTest")
        fileUtils:addSearchPath(resPrefix .. "ccs-res/hd/scenetest/AttributeComponentTest")
        fileUtils:addSearchPath(resPrefix .. "ccs-res/hd/scenetest/BackgroundComponentTest")
        fileUtils:addSearchPath(resPrefix .. "ccs-res/hd/scenetest/EffectComponentTest")
        fileUtils:addSearchPath(resPrefix .. "ccs-res/hd/scenetest/LoadSceneEdtiorFileTest")
        fileUtils:addSearchPath(resPrefix .. "ccs-res/hd/scenetest/ParticleComponentTest")
        fileUtils:addSearchPath(resPrefix .. "ccs-res/hd/scenetest/SpriteComponentTest")
        fileUtils:addSearchPath(resPrefix .. "ccs-res/hd/scenetest/TmxMapComponentTest")
        fileUtils:addSearchPath(resPrefix .. "ccs-res/hd/scenetest/UIComponentTest")
        fileUtils:addSearchPath(resPrefix .. "ccs-res/hd/scenetest/TriggerTest")
        fileUtils:addSearchPath(resPrefix .. "ccs-res/hd/Images")
        fileUtils:addSearchPath(resPrefix .. "ccs-res/hd")
        fileUtils:addSearchPath(resPrefix .. "ccs-res")
        fileUtils:addSearchPath(resPrefix .. "hd")
        fileUtils:addSearchPath("hd")
    else
        fileUtils:addSearchPath(resPrefix .. "ccs-res/scenetest/ArmatureComponentTest")
        fileUtils:addSearchPath(resPrefix .. "ccs-res/scenetest/AttributeComponentTest")
        fileUtils:addSearchPath(resPrefix .. "ccs-res/scenetest/BackgroundComponentTest")
        fileUtils:addSearchPath(resPrefix .. "ccs-res/scenetest/EffectComponentTest")
        fileUtils:addSearchPath(resPrefix .. "ccs-res/scenetest/LoadSceneEdtiorFileTest")
        fileUtils:addSearchPath(resPrefix .. "ccs-res/scenetest/ParticleComponentTest")
        fileUtils:addSearchPath(resPrefix .. "ccs-res/scenetest/SpriteComponentTest")
        fileUtils:addSearchPath(resPrefix .. "ccs-res/scenetest/TmxMapComponentTest")
        fileUtils:addSearchPath(resPrefix .. "ccs-res/scenetest/UIComponentTest")
        fileUtils:addSearchPath(resPrefix .. "ccs-res/scenetest/TriggerTest")
        fileUtils:addSearchPath(resPrefix .. "ccs-res/Images")
    end
    
    fileUtils:addSearchPath("cocosbuilderRes")
    fileUtils:addSearchPath(resPrefix)
end

addSearchPath("res/", screenSize.height)
addSearchPath("", screenSize.height)


require "src/mainMenu"

local scene = cc.Scene:create()
scene:addChild(CreateTestMenu())
if cc.Director:getInstance():getRunningScene() then
    cc.Director:getInstance():replaceScene(scene)
else
    cc.Director:getInstance():runWithScene(scene)
end
