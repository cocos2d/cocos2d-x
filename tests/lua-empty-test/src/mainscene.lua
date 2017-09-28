local handleButtonClick
local createScene
local currentScene
local currentReader

function scene()
	local scene = createScene('creator/scenes/Main.ccreator')
	handleButtonClick(scene)
	return scene
end

createScene = function (path)
	local reader = creator.CreatorReader:createWithFilename(path)
    reader:setup()
    local scene = reader:getSceneGraph()

    currentScene = scene
    currentReader = reader

    return scene
end

local function findChild(node, childName, type)
    local target = node:getChildByName(childName)
    if target ~= nil then
    	return tolua.cast(target, type)
    end

    local children = node:getChildren()
    for i = 1, #children do
    	print(i)
    	local child = children[i]
    	local result = findChild(child, childName, type)
    	if result ~= nil then
    		return tolua.cast(result, type)
    	end
    end

    return nil
end

local function createBackButton()
	local director = cc.Director:getInstance()
	local visibleSize = director:getVisibleSize()
	local visibleOrigin = director:getVisibleOrigin()

	local backButton = ccui.Button:create()
	backButton:setTitleText('back')
	backButton:setTitleFontSize(30)
	local contentSize = backButton:getContentSize()
	backButton:setPosition(visibleOrigin.x + visibleSize.width - contentSize.width/2,
		                   contentSize.height/2)
	backButton:addClickEventListener(function(sender)
		local scene = createScene('creator/scenes/Main.ccreator')
		handleButtonClick(scene)
		director:replaceScene(scene)
	end)

	return backButton
end

local function replaceScene(creatorPath)
	local scene = createScene(creatorPath)
	local backButton = createBackButton()
	scene:addChild(backButton)
	cc.Director:getInstance():replaceScene(scene)
end

local function handleNormalButtonClick(scene, buttonName, creatorPath)
	local button = findChild(scene, buttonName, 'ccui.Button')
	button:addClickEventListener(function(sender)
        replaceScene(creatorPath)
    end)
end

local function handleAnimatoinButtonClick(scene)
	local button = findChild(scene, 'animation', 'ccui.Button')
	button:addClickEventListener(function (sender)
		replaceScene('creator/scenes/animation/CreatorAnim.ccreator')
		local grossini_dance_08_02 = findChild(currentScene, 'grossini_dance_08_02', 'cc.Sprite')
		local animationManager = currentReader:getAnimationManager()
		grossini_dance_08_02:runAction(cc.Sequence:create(cc.DelayTime:create(3),
			                                              cc.CallFunc:create(function()
			                                              	    animationManager:pauseAnimationClip(grossini_dance_08_02, 'Animation2')
			                                              	end)),
		                                                  cc.DelayTime:create(1),
		                                                  cc.CallFunc:create(function()
		                                                  	animationManager:resumeAnimationClip(grossini_dance_08_02, 'Animation2')
		                                                  end))
	end)
end

local function handleColliderButtonClick(scene)
	local button = findChild(scene, 'collider', 'ccui.Button')
	button:addClickEventListener(function (sender)
		replaceScene('creator/scenes/collider/collider.ccreator')
		local colliderManager = currentReader:getColliderManager()
		--colliderManager:registerCollitionCallback
	end)
end


handleButtonClick = function (scene)
	handleNormalButtonClick(scene, 'label', 'creator/scenes/label/CreatorLabels.ccreator')
	handleNormalButtonClick(scene, 'mask', 'creator/scenes/mask/Mask.ccreator')
	handleNormalButtonClick(scene, 'pageview', 'creator/scenes/pageview/pageview.ccreator')
	handleNormalButtonClick(scene, 'prefab', 'creator/scenes/prefab/prefab-test.ccreator')
	handleNormalButtonClick(scene, 'richtext', 'creator/scenes/richtext/CreatorRichtext.ccreator')
	handleNormalButtonClick(scene, 'slider', 'creator/scenes/slider/slider.ccreator')
	handleNormalButtonClick(scene, 'sprites', 'creator/scenes/sprites/CreatorSprites.ccreator')
	handleNormalButtonClick(scene, 'tilemap', 'creator/scenes/tilemap/CreatorTilemap.ccreator')
	handleNormalButtonClick(scene, 'toggle', 'creator/scenes/toggle/toggle.ccreator')
	handleNormalButtonClick(scene, 'toggle_group', 'creator/scenes/toggle_group/toggle_group.ccreator')
	handleNormalButtonClick(scene, 'ui', 'creator/scenes/ui/CreatorUI.ccreator')

	handleAnimatoinButtonClick(scene)
	handleColliderButtonClick(scene)
end