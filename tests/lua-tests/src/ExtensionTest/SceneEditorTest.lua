require "CCBReaderLoad"

function SceneEditorTestLayer(filename)

	local layer = cc.Layer:create()
	local isCsbLoad = false;
	local loadtypeStr = {"change to load \nwith binary file","change to load \nwith json file"}
	local loadtypelb = cc.Label:createWithSystemFont(loadtypeStr[1], "Arial", 12);
	local filePath = filename
	layer.rootNode = nil
	function layer:defaultPlay()end

	local loadFileChangeHelper = function(filename)
	    if filename ~= nil then
	    	if isCsbLoad then
	    		return filename .. ".csb"
	    	else
	    		return filename .. ".json"
	    	end
	    end

	    return filename
	end

	local changeLoadTypeCallback = function(sender)
	    isCsbLoad = not isCsbLoad
	    loadtypelb:setString(loadtypeStr[isCsbLoad == false and 1 or 2])
	    local file = loadFileChangeHelper(filePath)

	    if layer.rootNode ~= nil then
	    	layer:removeChild(layer.rootNode)
	    	layer.rootNode = SceneReader:getInstance():createNodeWithSceneFile(file)
	        layer:addChild(layer.rootNode, 0, 1)
	    	layer:defaultPlay()
	    end
	end

    function layer:enter()
	    layer.rootNode = SceneReader:getInstance():createNodeWithSceneFile(loadFileChangeHelper(filePath))
	    layer:addChild(layer.rootNode, 0, 1)
	    layer:defaultPlay()
    end

    function layer:exit()
    	ccs.ArmatureDataManager:destroyInstance()
    	ccs.SceneReader:destroyInstance()
        ccs.ActionManagerEx:destroyInstance()
        ccs.GUIReader:destroyInstance()
    end

    local function onNodeEvent(event)
        if "enter" == event then
            layer:enter()
        elseif "exit" == event then
        	layer:exit()
        end
    end
    layer:registerScriptHandler(onNodeEvent)

	local itemlb = cc.MenuItemLabel:create(loadtypelb)
	itemlb:registerScriptTapHandler(changeLoadTypeCallback)
	local loadtypemenu = cc.Menu:create(itemlb)
	loadtypemenu:setPosition(cc.p(VisibleRect:rightTop().x -50,VisibleRect:rightTop().y -20));
	layer:addChild(loadtypemenu,100);

	Helper.initWithLayer(layer)
	Helper.titleLabel:setString("SceneReader Test LoadSceneEditorFile")
	return layer
end

function LoadSceneEdtiorFileTest()
	local layer = SceneEditorTestLayer("scenetest/LoadSceneEdtiorFileTest/FishJoy2")
	Helper.titleLabel:setString("loadSceneEdtiorFile Test")
	
	return layer
end

function SpriteComponentTest()
	local layer = SceneEditorTestLayer("scenetest/SpriteComponentTest/SpriteComponentTest")
	Helper.titleLabel:setString("Sprite Component Test")

	function layer:defaultPlay()
		layer.rootNode:getChildByTag(10003):getComponent("CCSprite"):getNode():runAction(cc.Blink:create(2, 10));
		layer.rootNode:getChildByTag(10004):getComponent("CCSprite"):getNode():runAction(cc.Blink:create(2, 5));
	end

	return layer
end

function ArmatureComponentTest()
	local layer = SceneEditorTestLayer("scenetest/ArmatureComponentTest/ArmatureComponentTest")
	Helper.titleLabel:setString("Armature Component Test")

	function layer:defaultPlay()
		layer.rootNode:getChildByTag(10007):getComponent("CCArmature"):getNode():runAction(cc.MoveBy:create(10.0, cc.p(-1000.0, 0)))
		layer.rootNode:getChildByTag(10008):getComponent("CCArmature"):getNode():runAction(cc.MoveBy:create(10.0, cc.p(-1000.0, 0)))
	end

	return layer
end

function UIComponentTest()
	local layer = SceneEditorTestLayer("scenetest/UIComponentTest/UIComponentTest")
	Helper.titleLabel:setString("UI Component Test")

	local function touchEvent(sender,eventType)
        if eventType == ccui.TouchEventType.began then
        	layer.rootNode:getChildByTag(10010):getComponent("CCArmature"):getNode():runAction(cc.MoveBy:create(10.0, cc.p(-1000.0, 0)))
        	layer.rootNode:getChildByTag(10011):getComponent("CCArmature"):getNode():runAction(cc.MoveBy:create(10.0, cc.p(-1000.0, 0)))
        end
    end

	function layer:defaultPlay()
		local render = layer.rootNode:getChildByTag(10025):getComponent("GUIComponent")
		local widget = render:getNode()
		local button = widget:getChildByName("Button_156")
		button:addTouchEventListener(touchEvent)
	end

	return layer
end

function TmxMapComponentTest()
	local layer = SceneEditorTestLayer("scenetest/TmxMapComponentTest/TmxMapComponentTest")
	Helper.titleLabel:setString("TmxMap Component Test")

	function layer:defaultPlay()
		local render = layer.rootNode:getChildByTag(10015):getComponent("CCTMXTiledMap")

		local skewTo = cc.SkewTo:create(2, 0, 2);
		local rotateTo = cc.RotateTo:create(2, 61);
		local scaleTo = cc.ScaleTo:create(2, -0.44, 0.47);
		local scaleBack = cc.ScaleTo:create(2, 1, 1);
		local rotateBack = cc.RotateTo:create(2, 0);
		local skewBack = cc.SkewTo:create(2, 0, 0);
		render:getNode():runAction(cc.Sequence:create(skewTo, skewBack));
		render:getNode():runAction(cc.Sequence:create(rotateTo, rotateBack));
		render:getNode():runAction(cc.Sequence:create(scaleTo, scaleBack));
	end

	return layer
end

function ParticleComponentTest()
	local layer = SceneEditorTestLayer("scenetest/ParticleComponentTest/ParticleComponentTest")
	Helper.titleLabel:setString("Particle Component Test")

	function layer:defaultPlay()
		local render = layer.rootNode:getChildByTag(10020):getComponent("CCParticleSystemQuad")

		local action = cc.JumpBy:create(5, cc.p(-500,0), 50, 4);
		render:getNode():runAction(cc.Sequence:create(action, action:reverse()))
	end

	return layer
end

function EffectComponentTest()
	local layer = SceneEditorTestLayer("scenetest/EffectComponentTest/EffectComponentTest")
	Helper.titleLabel:setString("Effect Component Test")

	local animationEvent = function(armature,movementType,movementID)
	    if movementType == ccs.MovementEventType.loopComplete then
	    	if movementID == "Fire" then
	    		layer.rootNode:getChildByTag(10015):getComponent("CCComAudio"):playEffect()
	    	end
	    end
	end

	function layer:defaultPlay()
		local render = layer.rootNode:getChildByTag(10015):getComponent("CCArmature")

		render:getNode():getAnimation():setMovementEventCallFunc(animationEvent);
	end

	return layer
end

function BackgroundComponentTest()
	local layer = SceneEditorTestLayer("scenetest/BackgroundComponentTest/BackgroundComponentTest")
	Helper.titleLabel:setString("Background Component Test")

	function layer:defaultPlay()
		layer.rootNode:getComponent("CCBackgroundAudio"):playBackgroundMusic();
	end

	return layer
end

function AttributeComponentTest()
	local layer = SceneEditorTestLayer("scenetest/AttributeComponentTest/AttributeComponentTest")
	Helper.titleLabel:setString("Attribute Component Test")

	function layer:defaultPlay()
		local attribute = layer.rootNode:getChildByTag(10015):getComponent("CCComAttribute")
		cclog("Name: " .. attribute:getString("name") .. ", HP: " .. attribute:getFloat("maxHP") .. ", MP: " .. attribute:getFloat("maxMP"))
	end

	return layer
end

function TriggerTest()
	local layer = SceneEditorTestLayer("scenetest/TriggerTest/TriggerTest")
	Helper.titleLabel:setString("Trigger Test")

	local function onTouchBegan(touch, event)
		ccs.sendTriggerEvent(triggerEventDef.TRIGGEREVENT_TOUCHBEGAN)
	end
	local function onTouchMoved(touch, event)
		ccs.sendTriggerEvent(triggerEventDef.TRIGGEREVENT_TOUCHMOVED)
	end
	local function onTouchEnded(touch, event)
		ccs.sendTriggerEvent(triggerEventDef.TRIGGEREVENT_TOUCHENDED)
	end
	local function onTouchCancelled(touch, event)
		ccs.sendTriggerEvent(triggerEventDef.TRIGGEREVENT_TOUCHCANCELLED)
	end


    local touchListener = cc.EventListenerTouchOneByOne:create()
    touchListener:setSwallowTouches(true)
    touchListener:registerScriptHandler(onTouchBegan, cc.Handler.EVENT_TOUCH_BEGAN) 
    touchListener:registerScriptHandler(onTouchMoved, cc.Handler.EVENT_TOUCH_MOVED) 
    touchListener:registerScriptHandler(onTouchEnded, cc.Handler.EVENT_TOUCH_ENDED)
    touchListener:registerScriptHandler(onTouchCancelled, cc.Handler.EVENT_TOUCH_CANCELLED)
    local eventDispatcher = layer:getEventDispatcher()
    eventDispatcher:addEventListenerWithFixedPriority(touchListener, 1)


    local function gameLogic(dt)
    	ccs.sendTriggerEvent(triggerEventDef.TRIGGEREVENT_UPDATESCENE)
    end

    local layerExit = layer.exit
    function layer:exit()
    	ccs.sendTriggerEvent(triggerEventDef.TRIGGEREVENT_LEAVESCENE)
    	layer:unschedule(gameLogic)
    	eventDispatcher:removeEventListener(touchListener)
    	layerExit(layer)
    end

    schedule(layer,gameLogic)

    function layer:defaultPlay()
	    ccs.sendTriggerEvent(triggerEventDef.TRIGGEREVENT_ENTERSCENE);
	end

	return layer
end

function runStudioSceneTest()
    local scene = cc.Scene:create()

	Helper.createFunctionTable = {
		LoadSceneEdtiorFileTest,
		SpriteComponentTest,
		ArmatureComponentTest,
		UIComponentTest,
		TmxMapComponentTest,
		ParticleComponentTest,
		EffectComponentTest,
		BackgroundComponentTest,
		AttributeComponentTest,	
		TriggerTest,
    }

    scene:addChild(Helper.createFunctionTable[1]())
    scene:addChild(CreateBackMenuItem())
    return scene
end
