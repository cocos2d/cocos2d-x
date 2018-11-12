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

function _dispatchEvent(params)
    local eventName = params.name
    local data      = params.data

    local event     = cc.EventCustom:new(eventName)
    event.data      = data
    local eventDispatcher = cc.Director:getInstance():getEventDispatcher()
    eventDispatcher:dispatchEvent(event)
end

function _isContainTouch(node,touch)
    local point = node:convertToNodeSpace(touch:getLocation())
    point.x = point.x*node:getScaleX()
    point.y = point.y*node:getScaleY()
    local s = node:getBoundingBox()
    local rect_ =  cc.rect(0, 0, s.width, s.height)
    local touchSize = node._touchSize
    if (touchSize ~= nil) and touchSize.width > 0 and touchSize.height > 0 then
        rect_ =  cc.rect( (node:getBoundingBox().width - touchSize.width) / 2 
            , (node:getBoundingBox().height - touchSize.height) / 2 , touchSize.width , touchSize.height)
    end
    return cc.rectContainsPoint( rect_, point )
end


function SpineTestLayerNormal:init()
  local skeletonNode = sp.SkeletonAnimation:create("spine/spineboy-ess.json", "spine/spineboy.atlas", 0.6)
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
    
  -- skeletonNode:registerSpineEventHandler(function (event)
  --     print(string.format("[spine] %d complete: %d", 
  --                             event.trackIndex,
  --                             event.loopCount))
  -- end, sp.EventType.ANIMATION_COMPLETE)

  -- skeletonNode:registerSpineEventHandler(function (event)
  --     print(string.format("[spine] %d event: %s, %d, %f, %s", 
  --                             event.trackIndex,
  --                             event.eventData.name,
  --                             event.eventData.intValue,
  --                             event.eventData.floatValue,
  --                             event.eventData.stringValue)) 
  -- end, sp.EventType.ANIMATION_EVENT)

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
  skeletonNode:setScale(0.5)
  
  local skeletonNodeGoblin = sp.SkeletonAnimation:create("spine/goblins-pro.json", "spine/goblins.atlas", 1.5)
  skeletonNodeGoblin:setAnimation(0, "walk", true)
  skeletonNodeGoblin:setSkin("goblin")
    
  skeletonNodeGoblin:setScale(0.3)
  skeletonNodeGoblin:setPosition(cc.p(windowSize.width / 2, 20))
  self:addChild(skeletonNodeGoblin)
    


  local ttfConfig = {}
  ttfConfig.fontFilePath="fonts/arial.ttf"
  ttfConfig.fontSize=18

  local label1 = cc.Label:createWithTTF(ttfConfig,"remove goblin's spine and release its png data", cc.VERTICAL_TEXT_ALIGNMENT_CENTER, 400)
  label1:setTextColor( cc.c4b(0, 255, 0, 255))
  label1:setPosition(cc.p(20, 230))
  label1:setAnchorPoint( cc.p(0, 0.5) )
  self:addChild(label1)

  local label2 = cc.Label:createWithTTF(ttfConfig,"remove goblin's spine's config data(json&atlas)", cc.VERTICAL_TEXT_ALIGNMENT_CENTER, 400)
  label2:setTextColor( cc.c4b(0, 255, 0, 255))
  label2:setPosition(cc.p(20, 200))
  label2:setAnchorPoint( cc.p(0, 0.5) )
  self:addChild(label2)

  local label3 = cc.Label:createWithTTF(ttfConfig,"add a goblin spine", cc.VERTICAL_TEXT_ALIGNMENT_CENTER, 400)
  label3:setTextColor( cc.c4b(0, 255, 0, 255))
  label3:setPosition(cc.p(20, 150))
  label3:setAnchorPoint( cc.p(0, 0.5) )
  self:addChild(label3)

  local listener1 = cc.EventListenerTouchOneByOne:create()
  listener1:registerScriptHandler(function (touch, event)
    if _isContainTouch(label1,touch) then
      cc.TextureCache:getInstance():dumpCachedTextureInfo()
      --1.we removed the spine , and its ref count will -1
      if not tolua.isnull(skeletonNodeGoblin) then skeletonNodeGoblin:removeFromParent() end
      --2.we notice the c++ to release the cached spine's skeletonData if its ref count == 0
      _dispatchEvent({name = "REMOVE_UNUSED_SPINES"})
      --3.we removed the unsed spine's png data
      cc.Director:getInstance():getTextureCache():removeUnusedTextures()
      --4.we dump the textures' info to confirm the spine's png was deleted.
      cc.TextureCache:getInstance():dumpCachedTextureInfo()
    end
    return true
  end,cc.Handler.EVENT_TOUCH_BEGAN )

  local eventDispatcher = self:getEventDispatcher()
  eventDispatcher:addEventListenerWithSceneGraphPriority(listener1, label1)


  local listener2 = cc.EventListenerTouchOneByOne:create()
  listener2:registerScriptHandler(function (touch, event)
    if _isContainTouch(label2,touch) then
      _dispatchEvent({name = "REMOVE_UNUSED_SPINE_CONFIG_DATA"})
    end
    return true
  end,cc.Handler.EVENT_TOUCH_BEGAN )
  eventDispatcher:addEventListenerWithSceneGraphPriority(listener2, label2)

  local listener3 = cc.EventListenerTouchOneByOne:create()
  listener3:registerScriptHandler(function (touch, event)
    if _isContainTouch(label3,touch) and tolua.isnull(skeletonNodeGoblin)  then
      skeletonNodeGoblin = sp.SkeletonAnimation:create("spine/goblins-pro.json", "spine/goblins.atlas", 1.5)
      skeletonNodeGoblin:setAnimation(0, "walk", true)
      skeletonNodeGoblin:setSkin("goblin")
        
      skeletonNodeGoblin:setScale(0.3)
      skeletonNodeGoblin:setPosition(cc.p(windowSize.width / 2, 120))
      self:addChild(skeletonNodeGoblin)
    end
    return true
  end,cc.Handler.EVENT_TOUCH_BEGAN )
  eventDispatcher:addEventListenerWithSceneGraphPriority(listener3, label3)
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
  skeletonNode = sp.SkeletonAnimation:create("spine/goblins-pro.json", "spine/goblins.atlas", 1.5)
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
    Helper.index = 1

    scene:addChild(SpineTestLayerNormal.create(), 0)
    scene:addChild(CreateBackMenuItem())
    return scene
end
