local scheduler = cc.Director:getInstance():getScheduler()
local SID_STEP1    = 100
local SID_STEP2    = 101
local SID_STEP3    = 102
local IDC_PAUSE    = 200

local function IntervalLayer()
    local ret = cc.Layer:create()
    local m_time0 = 0
    local m_time1 = 0
    local m_time2 = 0
    local m_time3 = 0
    local m_time4 = 0

    local s = cc.Director:getInstance():getWinSize()
    -- sun
    local  sun = cc.ParticleSun:create()
    sun:setTexture(cc.Director:getInstance():getTextureCache():addImage("Images/fire.png"))
    sun:setPosition( cc.p(VisibleRect:rightTop().x-32,VisibleRect:rightTop().y-32) )

    sun:setTotalParticles(130)
    sun:setLife(0.6)
    ret:addChild(sun)

    -- timers
    m_label0 = cc.LabelBMFont:create("0", "fonts/bitmapFontTest4.fnt")
    m_label1 = cc.LabelBMFont:create("0", "fonts/bitmapFontTest4.fnt")
    m_label2 = cc.LabelBMFont:create("0", "fonts/bitmapFontTest4.fnt")
    m_label3 = cc.LabelBMFont:create("0", "fonts/bitmapFontTest4.fnt")
    m_label4 = cc.LabelBMFont:create("0", "fonts/bitmapFontTest4.fnt")

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
            if cc.Director:getInstance():isPaused() then
                cc.Director:getInstance():resume()
            end
        end
    end

    ret:registerScriptHandler(onNodeEvent)


    m_label0:setPosition(cc.p(s.width*1/6, s.height/2))
    m_label1:setPosition(cc.p(s.width*2/6, s.height/2))
    m_label2:setPosition(cc.p(s.width*3/6, s.height/2))
    m_label3:setPosition(cc.p(s.width*4/6, s.height/2))
    m_label4:setPosition(cc.p(s.width*5/6, s.height/2))

    ret:addChild(m_label0)
    ret:addChild(m_label1)
    ret:addChild(m_label2)
    ret:addChild(m_label3)
    ret:addChild(m_label4)

    -- Sprite
    local  sprite = cc.Sprite:create(s_pPathGrossini)
    sprite:setPosition( cc.p(VisibleRect:left().x + 40, VisibleRect:bottom().y + 50) )

    local  jump = cc.JumpBy:create(3, cc.p(s.width-80,0), 50, 4)

    ret:addChild(sprite)
    sprite:runAction( cc.RepeatForever:create(cc.Sequence:create(jump, jump:reverse())))
    -- pause button
    local  item1 = cc.MenuItemFont:create("Pause")
    local function onPause(tag, pSender)
        if cc.Director:getInstance():isPaused() then
            cc.Director:getInstance():resume()
        else
            cc.Director:getInstance():pause()
        end
    end

    item1:registerScriptTapHandler(onPause)
    local  menu = cc.Menu:create(item1)
    menu:setPosition( cc.p(s.width/2, s.height-50) )

    ret:addChild( menu )

    return ret
end


function IntervalTestMain()
    cclog("IntervalTestMain")
    local scene = cc.Scene:create()
    local  layer = IntervalLayer()
    scene:addChild(layer, 0)
    scene:addChild(CreateBackMenuItem())
    return scene
end
