require "AudioEngine" 
local EFFECT_FILE = "effect1.wav"

local MUSIC_FILE = nil 
local targetPlatform = cc.Application:getInstance():getTargetPlatform()
if (cc.PLATFORM_OS_IPHONE == targetPlatform) or (cc.PLATFORM_OS_IPAD == targetPlatform) then
    MUSIC_FILE = "background.caf"
else
    MUSIC_FILE = "background.mp3"
end

local LINE_SPACE = 40

local function CocosDenshionTest()
    local ret = cc.Layer:create()
    local m_pItmeMenu = nil
    local m_tBeginPos = cc.p(0, 0)
    local m_nSoundId = 0

    local testItems = {
        "play background music",
        "stop background music",
        "pause background music",
        "resume background music",
        "rewind background music",
        "is background music playing",
        "play effect",
        "play effect repeatly",
        "stop effect",
        "unload effect",
        "add background music volume",
        "sub background music volume",
        "add effects volume",
        "sub effects volume",
        "pause effect",
        "resume effect",
        "pause all effects",
        "resume all effects",
        "stop all effects"
    }

    local function menuCallback(tag, pMenuItem)
        local nIdx = pMenuItem:getLocalZOrder() - 10000
        -- play background music
        if nIdx ==  0 then
            AudioEngine.playMusic(MUSIC_FILE, true)
        elseif nIdx == 1 then
            -- stop background music
            AudioEngine.stopMusic()
        elseif nIdx == 2 then
            -- pause background music
            AudioEngine.pauseMusic()
        elseif nIdx == 3 then
            -- resume background music
            AudioEngine.resumeMusic()
            -- rewind background music
        elseif nIdx == 4 then
            AudioEngine.rewindMusic()
        elseif nIdx == 5 then
            -- is background music playing
            if AudioEngine.isMusicPlaying () then
                cclog("background music is playing")
            else
                cclog("background music is not playing")
            end
        elseif nIdx == 6 then
            -- play effect
            m_nSoundId = AudioEngine.playEffect(EFFECT_FILE)
        elseif nIdx == 7 then
            -- play effect
            m_nSoundId = AudioEngine.playEffect(EFFECT_FILE, true)
        elseif nIdx == 8 then
            -- stop effect
            AudioEngine.stopEffect(m_nSoundId)
        elseif nIdx == 9 then
            -- unload effect
            AudioEngine.unloadEffect(EFFECT_FILE)
        elseif nIdx == 10 then
            -- add bakcground music volume
            AudioEngine.setMusicVolume(AudioEngine.getMusicVolume() + 0.1)
        elseif nIdx == 11 then
            -- sub backgroud music volume
            AudioEngine.setMusicVolume(AudioEngine.getMusicVolume() - 0.1)
        elseif nIdx == 12 then
            -- add effects volume
            AudioEngine.setEffectsVolume(AudioEngine.getEffectsVolume() + 0.1)
        elseif nIdx == 13 then
            -- sub effects volume
            AudioEngine.setEffectsVolume(AudioEngine.getEffectsVolume() - 0.1)
        elseif nIdx == 14 then
            AudioEngine.pauseEffect(m_nSoundId)
        elseif nIdx == 15 then
            AudioEngine.resumeEffect(m_nSoundId)
        elseif nIdx == 16 then
            AudioEngine.pauseAllEffects()
        elseif nIdx == 17 then
            AudioEngine.resumeAllEffects()
        elseif nIdx == 18 then
            AudioEngine.stopAllEffects()
        end
    end
    -- add menu items for tests
    m_pItmeMenu = cc.Menu:create()

    m_nTestCount = table.getn(testItems)
    local i = 1
    for  i = 1, m_nTestCount do
        local  label = cc.Label:createWithTTF(testItems[i], s_arialPath, 24)
        label:setAnchorPoint(cc.p(0.5, 0.5))
        local  pMenuItem = cc.MenuItemLabel:create(label)
        pMenuItem:registerScriptTapHandler(menuCallback)
        m_pItmeMenu:addChild(pMenuItem, i + 10000 -1)
        pMenuItem:setPosition( cc.p( VisibleRect:center().x, (VisibleRect:top().y - i * LINE_SPACE) ))
    end

    m_pItmeMenu:setContentSize(cc.size(VisibleRect:getVisibleRect().width, (m_nTestCount + 1) * LINE_SPACE))
    m_pItmeMenu:setPosition(cc.p(0, 0))
    ret:addChild(m_pItmeMenu)

    -- preload background music and effect
    AudioEngine.preloadMusic( MUSIC_FILE )
    AudioEngine.preloadEffect( EFFECT_FILE )

    -- set default volume
    AudioEngine.setEffectsVolume(0.5)
    AudioEngine.setMusicVolume(0.5)

    local function onNodeEvent(event)
        if event == "enter" then

        elseif event == "exit" then
            AudioEngine.destroyInstance()
        end
    end

    ret:registerScriptHandler(onNodeEvent)

    local prev = {x = 0, y = 0}
    local function onTouchEvent(eventType, x, y)
        if eventType == "began" then
            prev.x = x
            prev.y = y
            m_tBeginPos = cc.p(x, y)
            return true
        elseif  eventType == "moved" then
            local touchLocation = cc.p(x, y)
            local nMoveY = touchLocation.y - m_tBeginPos.y
            local curPosX, curPosY = m_pItmeMenu:getPosition()
            local curPos = cc.p(curPosX, curPosY)
            local nextPos = cc.p(curPos.x, curPos.y + nMoveY)

            if nextPos.y < 0.0 then
                m_pItmeMenu:setPosition(cc.p(0, 0))
            end

            if nextPos.y > ((m_nTestCount + 1)* LINE_SPACE - VisibleRect:getVisibleRect().height) then
                m_pItmeMenu:setPosition(cc.p(0, ((m_nTestCount + 1)* LINE_SPACE - VisibleRect:getVisibleRect().height)))
            end

            m_pItmeMenu:setPosition(nextPos)
            m_tBeginPos.x = touchLocation.x
            m_tBeginPos.y = touchLocation.y

            prev.x = x
            prev.y = y
        end
    end

    local function onTouchBegan(touch, event)
        local location = touch:getLocation()
        prev.x = location.x
        prev.y = location.y
        m_tBeginPos = location
        return true
    end

    local function onTouchMoved(touch, event)
        local location = touch:getLocation()
        local touchLocation = location
        local nMoveY = touchLocation.y - m_tBeginPos.y
        local curPosX, curPosY = m_pItmeMenu:getPosition()
        local curPos = cc.p(curPosX, curPosY)
        local nextPos = cc.p(curPos.x, curPos.y + nMoveY)

        if nextPos.y < 0.0 then
            m_pItmeMenu:setPosition(cc.p(0, 0))
        end

        if nextPos.y > ((m_nTestCount + 1)* LINE_SPACE - VisibleRect:getVisibleRect().height) then
            m_pItmeMenu:setPosition(cc.p(0, ((m_nTestCount + 1)* LINE_SPACE - VisibleRect:getVisibleRect().height)))
        end

        m_pItmeMenu:setPosition(nextPos)
        m_tBeginPos.x = touchLocation.x
        m_tBeginPos.y = touchLocation.y

        prev.x = location.x
        prev.y = location.y
    end

    local listener = cc.EventListenerTouchOneByOne:create()
    listener:setSwallowTouches(true)

    listener:registerScriptHandler(onTouchBegan,cc.Handler.EVENT_TOUCH_BEGAN )
    listener:registerScriptHandler(onTouchMoved,cc.Handler.EVENT_TOUCH_MOVED )
    local eventDispatcher = ret:getEventDispatcher()
    eventDispatcher:addEventListenerWithSceneGraphPriority(listener, ret)

    return ret
end

function CocosDenshionTestMain()
    cclog("CocosDenshionTestMain")
    local scene = cc.Scene:create()
    scene:addChild(CocosDenshionTest())
    scene:addChild(CreateBackMenuItem())
    return scene
end
