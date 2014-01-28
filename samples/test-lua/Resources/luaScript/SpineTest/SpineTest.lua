local SpineTestLayer1 = nil


--------------------------------------------------------------------
--
-- SpineTestLayer1
--
--------------------------------------------------------------------

SpineTestLayer1 = function()
    local ret = cc.Layer:create()

    local s = cc.Director:getInstance():getWinSize()
    local spineboy
    
    local addSpineBoy = function()
		  spineboy = sp.SkeletonAnimation:create(s_pPathSpineBoyJson, s_pPathSpineBoyAtlas, 0.8)
    	ret:addChild(spineboy)
    	spineboy:setPosition(cc.p(s.width/2, 20))
      spineboy:setMix("walk", "jump", 0.2)
      spineboy:setMix("jump", "walk", 0.4)
      spineboy:setTimeScale(0.3)
      spineboy:setDebugBones(true)
      spineboy:setAnimation(0, 'walk', false)
      spineboy:addAnimation(0, 'jump', false)
      spineboy:addAnimation(0, 'walk', true)
      spineboy:addAnimation(0, 'jump', true, 4)
      
      spineboy:registerSpineEventHandler(function(event)
        if event.type == 'start' then
          print(string.format("[spine] %d start: %s", 
                              event.trackIndex,
                              event.animation))
        elseif event.type == 'end' then
          print(string.format("[spine] %d end: %s", 
                              event.trackIndex,
                              event.animation))
        elseif event.type == 'complete' then
          print(string.format("[spine] %d complete: %s, %d", 
                              event.trackIndex,
                              event.animation, 
                              event.loopCount))
        elseif event.type == 'event' then
          print(string.format("[spine] %d event: %s, %s: %d, %f, %s", 
                              event.trackIndex,
                              event.animation,
                              event.eventData.name,
                              event.eventData.intValue,
                              event.eventData.floatValue,
                              event.eventData.stringValue))
        end
      end)

     spineboy:runAction(cc.RepeatForever:create(cc.Sequence:create(cc.FadeOut:create(1),
                                                                    cc.FadeIn:create(1),
                                                                    cc.DelayTime:create(5))))
           
    
    end

    local function onNodeEvent(event)
        if event == "enter" then
            cclog("SpineTestLayer1#onEnter")
            addSpineBoy()
        elseif event == "enterTransitionFinish" then
            cclog("SceneTestLayer1#onEnterTransitionDidFinish")
        end
    end

    ret:registerScriptHandler(onNodeEvent)
    return ret
end


function SpineTestMain()
    cclog("SpineTestMain")
    local scene = cc.Scene:create()
    local  layer = SpineTestLayer1()
    scene:addChild(layer, 0)
    scene:addChild(CreateBackMenuItem())
    return scene
end
