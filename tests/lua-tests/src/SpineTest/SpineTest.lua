require "cocos.spine.SpineConstants"

local SpineTestLayerNormal = class("SpineTestLayerNormal",function()
    return cc.Layer:create()
end)

function SpineTestLayerNormal:ctor()

  local function onNodeEvent(event)
    if event == "enter" then
        self:init()
    end
  end

  self:registerScriptHandler(onNodeEvent)
end

function SpineTestLayerNormal:init()
  local skeletonNode = sp.SkeletonAnimation:create("spine/spineboy.json", "spine/spineboy.atlas", 0.6)
  skeletonNode:setScale(0.5)

  skeletonNode:registerSpineEventHandler(function (event)
      print(string.format("[spine] %d start: %s", 
                              event.trackIndex,
                              event.animation))
  end, sp.EventType.ANIMATION_START)

  skeletonNode:registerSpineEventHandler(function (event)
      print(string.format("[spine] %d end:", 
                                event.trackIndex))
  end, sp.EventType.ANIMATION_END)
    
  skeletonNode:registerSpineEventHandler(function (event)
      print(string.format("[spine] %d complete: %d", 
                              event.trackIndex, 
                              event.loopCount))
  end, sp.EventType.ANIMATION_COMPLETE)

  skeletonNode:registerSpineEventHandler(function (event)
      print(string.format("[spine] %d event: %s, %d, %f, %s", 
                              event.trackIndex,
                              event.eventData.name,
                              event.eventData.intValue,
                              event.eventData.floatValue,
                              event.eventData.stringValue)) 
  end, sp.EventType.ANIMATION_EVENT)

  skeletonNode:setMix("walk", "jump", 0.2)
  skeletonNode:setMix("jump", "run", 0.2)
  skeletonNode:setAnimation(0, "walk", true)

  skeletonNode:addAnimation(0, "jump", false, 3)
  skeletonNode:addAnimation(0, "run", true)

  local windowSize = cc.Director:getInstance():getWinSize()
  skeletonNode:setPosition(cc.p(windowSize.width / 2, 20))
  self:addChild(skeletonNode)

  local listener = cc.EventListenerTouchOneByOne:create()
  listener:registerScriptHandler(function (touch, event)
        if not skeletonNode:getDebugBonesEnabled() then
            skeletonNode:setDebugBonesEnabled(true)
        elseif skeletonNode:getTimeScale() == 1 then
            skeletonNode:setTimeScale(0.3)
        else
            skeletonNode:setTimeScale(1)
            skeletonNode:setDebugBonesEnabled(false)
        end

        return true
    end,cc.Handler.EVENT_TOUCH_BEGAN )

  local eventDispatcher = self:getEventDispatcher()
  eventDispatcher:addEventListenerWithSceneGraphPriority(listener, self)
end

function SpineTestLayerNormal.create( ... )
    local layer = SpineTestLayerNormal.new()
    Helper.initWithLayer(layer)
    Helper.titleLabel:setString("SpineTestLayerNormal Test")
    return layer
end

----
local SpineTestLayerFFD = class("SpineTestLayerFFD",function()
    return cc.Layer:create()
end)

function SpineTestLayerFFD:ctor()

  local function onNodeEvent(event)
    if event == "enter" then
        self:init()
    end
  end

  self:registerScriptHandler(onNodeEvent)
end

function SpineTestLayerFFD:init()
  skeletonNode = sp.SkeletonAnimation:create("spine/goblins-ffd.json", "spine/goblins-ffd.atlas", 1.5)
  skeletonNode:setAnimation(0, "walk", true)
  skeletonNode:setSkin("goblin")
    
  skeletonNode:setScale(0.5)
  local windowSize = cc.Director:getInstance():getWinSize()
  skeletonNode:setPosition(cc.p(windowSize.width / 2, 20))
  self:addChild(skeletonNode)
    
  local listener = cc.EventListenerTouchOneByOne:create()
  listener:registerScriptHandler(function (touch, event)
        if not skeletonNode:getDebugBonesEnabled() then
            skeletonNode:setDebugBonesEnabled(true)
        elseif skeletonNode:getTimeScale() == 1 then
            skeletonNode:setTimeScale(0.3)
        else
            skeletonNode:setTimeScale(1)
            skeletonNode:setDebugBonesEnabled(false)
        end

        return true
    end,cc.Handler.EVENT_TOUCH_BEGAN )

  local eventDispatcher = self:getEventDispatcher()
  eventDispatcher:addEventListenerWithSceneGraphPriority(listener, self)
end

function SpineTestLayerFFD.create( ... )
    local layer = SpineTestLayerFFD.new()
    Helper.initWithLayer(layer)
    Helper.titleLabel:setString("SpineTestLayerFFD Test")
    return layer
end

function SpineTestMain()
    cclog("SpineTestMain")
    local scene = cc.Scene:create()

    Helper.createFunctionTable = 
    {
        SpineTestLayerNormal.create,
        SpineTestLayerFFD.create,
    }

    scene:addChild(SpineTestLayerNormal.create(), 0)
    scene:addChild(CreateBackMenuItem())
    return scene
end
