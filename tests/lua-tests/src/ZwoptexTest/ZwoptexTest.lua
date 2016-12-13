local scheduler = cc.Director:getInstance():getScheduler()
--------------------------------------------------------------------
--
-- ZwoptexGenericTest
--
--------------------------------------------------------------------
local function ZwoptexGenericTest()
    local ret = createTestLayer("Zwoptex Tests",
                                "Coordinate Formats, Rotation, Trimming, flipX/Y")
    local spriteFrameIndex = 0
    local counter = 0
    local s = cc.Director:getInstance():getWinSize()
    local schedulerEntry = nil
    local schedulerFlipSpriteEntry = nil
    local sprite1 = nil
    local sprite2 = nil

    local function onEnter()
        cc.SpriteFrameCache:getInstance():addSpriteFrames("zwoptex/grossini.plist")
        cc.SpriteFrameCache:getInstance():addSpriteFrames("zwoptex/grossini-generic.plist")

        local layer1 = cc.LayerColor:create(cc.c4b(255, 0, 0, 255), 85, 121)
        layer1:setPosition(cc.p(s.width/2-80 - (85.0 * 0.5), s.height/2 - (121.0 * 0.5)))
        ret:addChild(layer1)

        sprite1 = cc.Sprite:createWithSpriteFrame(cc.SpriteFrameCache:getInstance():getSpriteFrame("grossini_dance_01.png"))
        sprite1:setPosition(cc.p( s.width/2-80, s.height/2))
        ret:addChild(sprite1)

        sprite1:setFlippedX(false)
        sprite1:setFlippedY(false)

        local layer2 = cc.LayerColor:create(cc.c4b(255, 0, 0, 255), 85, 121)
        layer2:setPosition(cc.p(s.width/2+80 - (85.0 * 0.5), s.height/2 - (121.0 * 0.5)))
        ret:addChild(layer2)

        sprite2 = cc.Sprite:createWithSpriteFrame(cc.SpriteFrameCache:getInstance():getSpriteFrame("grossini_dance_generic_01.png"))
        sprite2:setPosition(cc.p( s.width/2 + 80, s.height/2))
        ret:addChild(sprite2)

        sprite2:setFlippedX(false)
        sprite2:setFlippedY(false)

        local function flipSprites(dt)
            counter = counter + 1

            local fx = false
            local fy = false
            local i = counter % 4

            if i == 0 then
                fx = false
                fy = false
            elseif i == 1 then
                fx = true
                fy = false
            elseif i == 2 then
                fx = false
                fy = true
            elseif i == 3 then
                fx = true
                fy = true
            end

            sprite1:setFlippedX(fx)
            sprite2:setFlippedX(fx)
            sprite1:setFlippedY(fy)
            sprite2:setFlippedY(fy)

            spriteFrameIndex = spriteFrameIndex + 1
            if spriteFrameIndex > 14 then
                spriteFrameIndex = 1
            end

            local str1 = string.format("grossini_dance_%02d.png", spriteFrameIndex)
            local str2 = string.format("grossini_dance_generic_%02d.png", spriteFrameIndex)
            sprite1:setSpriteFrame(cc.SpriteFrameCache:getInstance():getSpriteFrame(str1))
            sprite2:setSpriteFrame(cc.SpriteFrameCache:getInstance():getSpriteFrame(str2))
        end

        sprite1:retain()
        sprite2:retain()
        counter = 0
        local function startIn05Secs(dt)
            scheduler:unscheduleScriptEntry(schedulerEntry)
            schedulerFlipSpriteEntry = scheduler:scheduleScriptFunc(flipSprites, 0.5, false)
        end
        schedulerEntry = scheduler:scheduleScriptFunc(startIn05Secs, 1.0, false)
    end

    local function onExit()
        if schedulerEntry ~= nil then
            scheduler:unscheduleScriptEntry(schedulerEntry)
        end
        if schedulerFlipSpriteEntry ~= nil then
            scheduler:unscheduleScriptEntry(schedulerFlipSpriteEntry)
        end
        sprite1:release()
        sprite2:release()
        local cache = cc.SpriteFrameCache:getInstance()
        cache:removeSpriteFramesFromFile("zwoptex/grossini.plist")
        cache:removeSpriteFramesFromFile("zwoptex/grossini-generic.plist")
    end

    local function onNodeEvent(event)
        if event == "enter" then
            onEnter()
        elseif event == "exit" then
            onExit()
        end
    end

    ret:registerScriptHandler(onNodeEvent)

    return ret
end

function ZwoptexTestMain()
    cclog("ZwoptexTestMain")
    local scene = cc.Scene:create()
    Helper.createFunctionTable = {
        ZwoptexGenericTest
    }
    Helper.index = 1

    scene:addChild(ZwoptexGenericTest())
    scene:addChild(CreateBackMenuItem())
    return scene
end
