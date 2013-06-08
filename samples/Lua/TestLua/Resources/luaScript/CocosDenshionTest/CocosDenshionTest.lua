require "audioEngine" 
local EFFECT_FILE = "effect1.wav"
local MUSIC_FILE  = "background.mp3"

local LINE_SPACE = 40

local function CocosDenshionTest()
    local ret = CCLayer:create()
    local m_pItmeMenu = nil
    local m_tBeginPos = ccp(0, 0)
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
        local nIdx = pMenuItem:getZOrder() - 10000
        -- play background music
        if nIdx ==  0 then
            audioEngine.playMusic(MUSIC_FILE, true)
        elseif nIdx == 1 then
            -- stop background music
            audioEngine.stopMusic()
        elseif nIdx == 2 then
            -- pause background music
            audioEngine.pauseMusic()
        elseif nIdx == 3 then
            -- resume background music
            audioEngine.resumeMusic()
            -- rewind background music
        elseif nIdx == 4 then
            audioEngine.rewindMusic()
        elseif nIdx == 5 then
            -- is background music playing
            if audioEngine.isMusicPlaying () then
                cclog("background music is playing")
            else
                cclog("background music is not playing")
            end
        elseif nIdx == 6 then
            -- play effect
            m_nSoundId = audioEngine.playEffect(EFFECT_FILE)
        elseif nIdx == 7 then
            -- play effect
            m_nSoundId = audioEngine.playEffect(EFFECT_FILE, true)
        elseif nIdx == 8 then
            -- stop effect
            audioEngine.stopEffect(m_nSoundId)
        elseif nIdx == 9 then
            -- unload effect
            audioEngine.unloadEffect(EFFECT_FILE)
        elseif nIdx == 10 then
            -- add bakcground music volume
            audioEngine.setMusicVolume(audioEngine.getMusicVolume() + 0.1)
        elseif nIdx == 11 then
            -- sub backgroud music volume
            audioEngine.setMusicVolume(audioEngine.getMusicVolume() - 0.1)
        elseif nIdx == 12 then
            -- add effects volume
            audioEngine.setEffectsVolume(audioEngine.getEffectsVolume() + 0.1)
        elseif nIdx == 13 then
            -- sub effects volume
            audioEngine.setEffectsVolume(audioEngine.getEffectsVolume() - 0.1)
        elseif nIdx == 14 then
            audioEngine.pauseEffect(m_nSoundId)
        elseif nIdx == 15 then
            audioEngine.resumeEffect(m_nSoundId)
        elseif nIdx == 16 then
            audioEngine.pauseAllEffects()
        elseif nIdx == 17 then
            audioEngine.resumeAllEffects()
        elseif nIdx == 18 then
            audioEngine.stopAllEffects()
        end
    end
    -- add menu items for tests
    m_pItmeMenu = CCMenu:create()

    m_nTestCount = table.getn(testItems)
    local i = 1
    for  i = 1, m_nTestCount do
        local  label = CCLabelTTF:create(testItems[i], "Arial", 24)
        local  pMenuItem = CCMenuItemLabel:create(label)
        pMenuItem:registerScriptTapHandler(menuCallback)
        m_pItmeMenu:addChild(pMenuItem, i + 10000 -1)
        pMenuItem:setPosition( ccp( VisibleRect:center().x, (VisibleRect:top().y - i * LINE_SPACE) ))
    end

    m_pItmeMenu:setContentSize(CCSizeMake(VisibleRect:getVisibleRect().size.width, (m_nTestCount + 1) * LINE_SPACE))
    m_pItmeMenu:setPosition(ccp(0, 0))
    ret:addChild(m_pItmeMenu)
    ret:setTouchEnabled(true)

    -- preload background music and effect
    SimpleAudioEngine:sharedEngine():preloadBackgroundMusic( MUSIC_FILE )
    SimpleAudioEngine:sharedEngine():preloadEffect( EFFECT_FILE )

    -- set default volume
    SimpleAudioEngine:sharedEngine():setEffectsVolume(0.5)
    SimpleAudioEngine:sharedEngine():setBackgroundMusicVolume(0.5)

    local function onNodeEvent(event)
        if event == "enter" then

        elseif event == "exit" then
            --SimpleAudioEngine:sharedEngine():endToLua()
        end
    end

    ret:registerScriptHandler(onNodeEvent)

    local prev = {x = 0, y = 0}
    local function onTouchEvent(eventType, x, y)
        if eventType == "began" then
            prev.x = x
            prev.y = y
            m_tBeginPos = ccp(x, y)
            return true
        elseif  eventType == "moved" then
            local touchLocation = ccp(x, y)
            local nMoveY = touchLocation.y - m_tBeginPos.y
            local curPosX, curPosY = m_pItmeMenu:getPosition()
            local curPos = ccp(curPosX, curPosY)
            local nextPos = ccp(curPos.x, curPos.y + nMoveY)

            if nextPos.y < 0.0 then
                m_pItmeMenu:setPosition(ccp(0, 0))
            end

            if nextPos.y > ((m_nTestCount + 1)* LINE_SPACE - VisibleRect:getVisibleRect().size.height) then
                m_pItmeMenu:setPosition(ccp(0, ((m_nTestCount + 1)* LINE_SPACE - VisibleRect:getVisibleRect().size.height)))
            end

            m_pItmeMenu:setPosition(nextPos)
            m_tBeginPos.x = touchLocation.x
            m_tBeginPos.y = touchLocation.y

            prev.x = x
            prev.y = y
        end
    end

    ret:registerScriptTouchHandler(onTouchEvent)
    return ret
end

function CocosDenshionTestMain()
    cclog("CocosDenshionTestMain")
    local scene = CCScene:create()
    scene:addChild(CocosDenshionTest())
    scene:addChild(CreateBackMenuItem())
    return scene
end
