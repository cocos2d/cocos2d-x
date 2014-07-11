
-- avoid memory leak
collectgarbage("setpause", 100) 
collectgarbage("setstepmul", 5000)
	

----------------
-- run
local director = cc.Director:getInstance()
local glView   = director:getOpenGLView()
if nil == glView then
    glView = cc.GLView:createWithRect("Lua Tests", cc.rect(0,0,900,640))
    director:setOpenGLView(glView)
end

--turn on display FPS
director:setDisplayStats(true)

--set FPS. the default value is 1.0/60 if you don't call this
director:setAnimationInterval(1.0 / 60)

local screenSize = glView:getFrameSize()

local designSize = {width = 480, height = 320}

if screenSize.height > 320 then
    local resourceSize = {width = 960, height = 640}
    cc.Director:getInstance():setContentScaleFactor(resourceSize.height/designSize.height)
end

glView:setDesignResolutionSize(designSize.width, designSize.height, cc.ResolutionPolicy.FIXED_HEIGHT)

local fileUtils = cc.FileUtils:getInstance()
local function addSearchPath(resPrefix, height)
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
