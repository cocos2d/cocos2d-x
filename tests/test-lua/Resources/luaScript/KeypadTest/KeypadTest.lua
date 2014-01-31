local function KeypadMainLayer()	
    local layer = cc.Layer:create() 

    local function onEnter()
        print("come in")
        local  s = cc.Director:getInstance():getWinSize()
        local  label = cc.LabelTTF:create("Keypad Test", "Arial", 28)
        layer:addChild(label, 0)
        label:setPosition(cc.p(s.width/2, s.height-50))

        local labelTip = cc.LabelTTF:create("Please press any key...", "Arial", 22)
        labelTip:setPosition(cc.p(s.width / 2, s.height / 2))
        layer:addChild(labelTip, 0)

        local function onKeyReleased(keyCode, event)
            local label = event:getCurrentTarget()
            if keyCode == cc.KeyCode.KEY_BACKSPACE then
                label:setString("BACK clicked!")
            elseif keyCode == cc.KeyCode.KEY_MENU  then
                label:setString("MENU clicked!")
            end
        end

        local listener = cc.EventListenerKeyboard:create()
        listener:registerScriptHandler(onKeyReleased, cc.Handler.EVENT_KEYBOARD_RELEASED )

        local eventDispatcher = layer:getEventDispatcher()
        eventDispatcher:addEventListenerWithSceneGraphPriority(listener, labelTip)
    end

    local function onNodeEvent(event)
        if event == "enter" then
            onEnter()
        end
    end

    layer:registerScriptHandler(onNodeEvent)

    return layer
end


function KeypadTestMain()
	cclog("KeypadTestMain")
	local scene = cc.Scene:create()
	scene:addChild(KeypadMainLayer())
	scene:addChild(CreateBackMenuItem())
	return scene
end
