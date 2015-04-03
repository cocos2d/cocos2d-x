
-- avoid memory leak
collectgarbage("setpause", 100) 
collectgarbage("setstepmul", 5000)

----------------
-- run
cc.FileUtils:getInstance():addSearchPath("src")
CC_USE_DEPRECATED_API = true
require "cocos.init"

local director = cc.Director:getInstance()
local glView   = director:getOpenGLView()
if nil == glView then
    glView = cc.GLViewImpl:createWithRect("Lua Tests", cc.rect(0,0,900,640))
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

        table.insert(searchPaths, 1, resPrefix .. "ccs-res/hd/cocosui/UIEditorTest/UIButton")
        table.insert(searchPaths, 1, resPrefix .. "ccs-res/hd/cocosui/UIEditorTest/UICheckBox")
        table.insert(searchPaths, 1, resPrefix .. "ccs-res/hd/cocosui/UIEditorTest/UIImageView")
        table.insert(searchPaths, 1, resPrefix .. "ccs-res/hd/cocosui/UIEditorTest/UILabel")
        table.insert(searchPaths, 1, resPrefix .. "ccs-res/hd/cocosui/UIEditorTest/UILabelBMFont")
        table.insert(searchPaths, 1, resPrefix .. "ccs-res/hd/cocosui/UIEditorTest/UILayout/BackgroundImage")
        table.insert(searchPaths, 1, resPrefix .. "ccs-res/hd/cocosui/UIEditorTest/UILayout/Color")
        table.insert(searchPaths, 1, resPrefix .. "ccs-res/hd/cocosui/UIEditorTest/UILayout/Layout")
        table.insert(searchPaths, 1, resPrefix .. "ccs-res/hd/cocosui/UIEditorTest/UILayout/Gradient_Color")
        table.insert(searchPaths, 1, resPrefix .. "ccs-res/hd/cocosui/UIEditorTest/UILayout/Scale9_BackgroundImage")
        table.insert(searchPaths, 1, resPrefix .. "ccs-res/hd/cocosui/UIEditorTest/UILayout/LayoutComponent")
        table.insert(searchPaths, 1, resPrefix .. "ccs-res/hd/cocosui/UIEditorTest/UILoadingBar")
        table.insert(searchPaths, 1, resPrefix .. "ccs-res/hd/cocosui/UIEditorTest/UIPageView")
        table.insert(searchPaths, 1, resPrefix .. "ccs-res/hd/cocosui/UIEditorTest/UIScrollView/Both")
        table.insert(searchPaths, 1, resPrefix .. "ccs-res/hd/cocosui/UIEditorTest/UIScrollView/Horizontal")
        table.insert(searchPaths, 1, resPrefix .. "ccs-res/hd/cocosui/UIEditorTest/UIScrollView/Vertical")
        table.insert(searchPaths, 1, resPrefix .. "ccs-res/hd/cocosui/UIEditorTest/UISlider")
        table.insert(searchPaths, 1, resPrefix .. "ccs-res/hd/cocosui/UIEditorTest/UITextField")
        table.insert(searchPaths, 1, resPrefix .. "ccs-res/hd/cocosui/UIEditorTest/UIWidgetAddNode")
        table.insert(searchPaths, 1, resPrefix .. "ccs-res/hd/cocosui/UIEditorTest/UIListView/New")

        table.insert(searchPaths, 1, resPrefix .. "hd/ActionTimeline")
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

        table.insert(searchPaths, 1, resPrefix .. "ccs-res/cocosui/UIEditorTest/UIButton")
        table.insert(searchPaths, 1, resPrefix .. "ccs-res/cocosui/UIEditorTest/UICheckBox")
        table.insert(searchPaths, 1, resPrefix .. "ccs-res/cocosui/UIEditorTest/UIImageView")
        table.insert(searchPaths, 1, resPrefix .. "ccs-res/cocosui/UIEditorTest/UILabel")
        table.insert(searchPaths, 1, resPrefix .. "ccs-res/cocosui/UIEditorTest/UILabelBMFont")
        table.insert(searchPaths, 1, resPrefix .. "ccs-res/cocosui/UIEditorTest/UILayout/BackgroundImage")
        table.insert(searchPaths, 1, resPrefix .. "ccs-res/cocosui/UIEditorTest/UILayout/Color")
        table.insert(searchPaths, 1, resPrefix .. "ccs-res/cocosui/UIEditorTest/UILayout/Layout")
        table.insert(searchPaths, 1, resPrefix .. "ccs-res/cocosui/UIEditorTest/UILayout/Gradient_Color")
        table.insert(searchPaths, 1, resPrefix .. "ccs-res/cocosui/UIEditorTest/UILayout/Scale9_BackgroundImage")
        table.insert(searchPaths, 1, resPrefix .. "ccs-res/cocosui/UIEditorTest/UILayout/LayoutComponent")
        table.insert(searchPaths, 1, resPrefix .. "ccs-res/cocosui/UIEditorTest/UILoadingBar")
        table.insert(searchPaths, 1, resPrefix .. "ccs-res/cocosui/UIEditorTest/UIPageView")
        table.insert(searchPaths, 1, resPrefix .. "ccs-res/cocosui/UIEditorTest/UIScrollView/Both")
        table.insert(searchPaths, 1, resPrefix .. "ccs-res/cocosui/UIEditorTest/UIScrollView/Horizontal")
        table.insert(searchPaths, 1, resPrefix .. "ccs-res/cocosui/UIEditorTest/UIScrollView/Vertical")
        table.insert(searchPaths, 1, resPrefix .. "ccs-res/cocosui/UIEditorTest/UISlider")
        table.insert(searchPaths, 1, resPrefix .. "ccs-res/cocosui/UIEditorTest/UITextField")
        table.insert(searchPaths, 1, resPrefix .. "ccs-res/cocosui/UIEditorTest/UIWidgetAddNode")
        table.insert(searchPaths, 1, resPrefix .. "ccs-res/cocosui/UIEditorTest/UIListView/New")

        table.insert(searchPaths, 1, resPrefix .. "ActionTimeline")
    end

    fileUtils:setSearchPaths(searchPaths)

end

addSearchPath("res/", screenSize.height)
addSearchPath("", screenSize.height)

require "mainMenu"

local scene = cc.Scene:create()
scene:addChild(CreateTestMenu())
if cc.Director:getInstance():getRunningScene() then
    cc.Director:getInstance():replaceScene(scene)
else
    cc.Director:getInstance():runWithScene(scene)
end
