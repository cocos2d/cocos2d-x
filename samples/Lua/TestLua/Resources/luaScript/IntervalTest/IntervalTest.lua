local scheduler = CCDirector:sharedDirector():getScheduler()
local SID_STEP1    = 100
local SID_STEP2    = 101
local SID_STEP3    = 102
local IDC_PAUSE    = 200

local function IntervalLayer()
    local ret = CCLayer:create()
    local m_time0 = 0
    local m_time1 = 0
    local m_time2 = 0
    local m_time3 = 0
    local m_time4 = 0

    local s = CCDirector:sharedDirector():getWinSize()
    -- sun
    local  sun = CCParticleSun:create()
    sun:setTexture(CCTextureCache:sharedTextureCache():addImage("Images/fire.png"))
    sun:setPosition( ccp(VisibleRect:rightTop().x-32,VisibleRect:rightTop().y-32) )

    sun:setTotalParticles(130)
    sun:setLife(0.6)
    ret:addChild(sun)

    -- timers
    m_label0 = CCLabelBMFont:create("0", "fonts/bitmapFontTest4.fnt")
    m_label1 = CCLabelBMFont:create("0", "fonts/bitmapFontTest4.fnt")
    m_label2 = CCLabelBMFont:create("0", "fonts/bitmapFontTest4.fnt")
    m_label3 = CCLabelBMFont:create("0", "fonts/bitmapFontTest4.fnt")
    m_label4 = CCLabelBMFont:create("0", "fonts/bitmapFontTest4.fnt")

    local function update(dt)
        m_time0 = m_time0 + dt
        local str = string.format("%2.1f", m_time0)
        m_label0:setString(str)
    end

    ret:scheduleUpdateWithPriorityLua(update, 0)

    local function step1(dt)
        m_time1 = m_time1 + dt
        local str = string.format("%2.1f", m_time1)
        m_label1:setString( str )
    end

    local function step2(dt)
        m_time2 = m_time2 + dt
        local str = string.format("%2.1f", m_time2)
        m_label2:setString( str )
    end

    local function step3(dt)
        m_time3 = m_time3 + dt
        local str = string.format("%2.1f", m_time3)
        m_label3:setString( str )
    end

    local function step4(dt)
        m_time4 = m_time4 + dt
        local str = string.format("%2.1f", m_time4)
        m_label4:setString( str )
    end

    local schedulerEntry1 = nil
    local schedulerEntry2 = nil
    local schedulerEntry3 = nil
    local schedulerEntry4 = nil

    local function onNodeEvent(event)
        if event == "enter" then
            schedulerEntry1 = scheduler:scheduleScriptFunc(step1, 0, false)
            schedulerEntry2 = scheduler:scheduleScriptFunc(step2, 0, false)
            schedulerEntry3 = scheduler:scheduleScriptFunc(step3, 1.0, false)
            schedulerEntry4 = scheduler:scheduleScriptFunc(step4, 2.0, false)
        elseif event == "exit" then
            scheduler:unscheduleScriptEntry(schedulerEntry1)
            scheduler:unscheduleScriptEntry(schedulerEntry2)
            scheduler:unscheduleScriptEntry(schedulerEntry3)
            scheduler:unscheduleScriptEntry(schedulerEntry4)
            if CCDirector:sharedDirector():isPaused() then
                CCDirector:sharedDirector():resume()
            end
        end
    end

    ret:registerScriptHandler(onNodeEvent)


    m_label0:setPosition(ccp(s.width*1/6, s.height/2))
    m_label1:setPosition(ccp(s.width*2/6, s.height/2))
    m_label2:setPosition(ccp(s.width*3/6, s.height/2))
    m_label3:setPosition(ccp(s.width*4/6, s.height/2))
    m_label4:setPosition(ccp(s.width*5/6, s.height/2))

    ret:addChild(m_label0)
    ret:addChild(m_label1)
    ret:addChild(m_label2)
    ret:addChild(m_label3)
    ret:addChild(m_label4)

    -- Sprite
    local  sprite = CCSprite:create(s_pPathGrossini)
    sprite:setPosition( ccp(VisibleRect:left().x + 40, VisibleRect:bottom().y + 50) )

    local  jump = CCJumpBy:create(3, ccp(s.width-80,0), 50, 4)

    ret:addChild(sprite)
    local arr = CCArray:create()
    arr:addObject(jump)
    arr:addObject(jump:reverse())
    sprite:runAction( CCRepeatForever:create(CCSequence:create(arr)))
    -- pause button
    local  item1 = CCMenuItemFont:create("Pause")
    local function onPause(tag, pSender)
        if CCDirector:sharedDirector():isPaused() then
            CCDirector:sharedDirector():resume()
        else
            CCDirector:sharedDirector():pause()
        end
    end

    item1:registerScriptTapHandler(onPause)
    local  menu = CCMenu:createWithItem(item1)
    menu:setPosition( ccp(s.width/2, s.height-50) )

    ret:addChild( menu )

    return ret
end


function IntervalTestMain()
    cclog("IntervalTestMain")
    local scene = CCScene:create()
    local  layer = IntervalLayer()
    scene:addChild(layer, 0)
    scene:addChild(CreateBackMenuItem())
    return scene
end
