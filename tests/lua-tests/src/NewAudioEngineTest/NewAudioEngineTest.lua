local SliderEx = class("SliderEx", function()
    local slider = cc.Sprite:create("cocosui/sliderTrack.png")
    return slider
end)

SliderEx.TouchEventDown = 0
SliderEx.TouchEventMove = 1
SliderEx.TouchEventUp = 2
SliderEx.TouchEventCancel = 3

function SliderEx:create()
    local slider = SliderEx:new()
    slider:registerScriptHandler(function(tag)
        if "enter" == tag then
            slider:onEnter()
        elseif "exit" == tag then
        end
    end)
    return slider
end

function SliderEx:onEnter()
    self._ratio = 0
    self._thumbX = 0
    
    local progressBar = cc.Sprite:create("cocosui/sliderProgress.png")
    progressBar:setAnchorPoint(cc.p(0,0))
    self:addChild(progressBar)
    
    local sliderSize = self:getContentSize()
    self._width = sliderSize.width
    self._thumb = cc.Sprite:create("cocosui/sliderThumb.png")
    self._thumb:setPosition(cc.p(0,sliderSize.height/2))
    self:addChild(self._thumb)
    
    local thumbSize = self._thumb:getContentSize()
    self._thumbRect = cc.rect(0, 0, thumbSize.width, thumbSize.height)
    
    local  listenner = cc.EventListenerTouchOneByOne:create()
    listenner:setSwallowTouches(true)
    listenner:registerScriptHandler(function(touch, event)
        local location = touch:getLocation()
        local locationInNode = self._thumb:convertToNodeSpace(location)
        if not cc.rectContainsPoint(self._thumbRect, locationInNode) then
            return false
        end
        
        self._touchBeganX = self:convertToNodeSpace(location).x
        self._thumbBeganX = self._thumbX
        if self._callback then
            self._callback(self,self._ratio,SliderEx.TouchEventDown)
        end
        return true
    end, cc.Handler.EVENT_TOUCH_BEGAN )
    
    listenner:registerScriptHandler(function(touch, event)
        local locationInNodeX = self:convertToNodeSpace(touch:getLocation()).x     
        self:setThumbPosX(self._thumbBeganX + locationInNodeX - self._touchBeganX)
        
        if self._callback then
            self._callback(self,self._ratio,SliderEx.TouchEventMove)
        end
    end, cc.Handler.EVENT_TOUCH_MOVED )
    
    listenner:registerScriptHandler(function(touch, event)
        local locationInNodeX = self:convertToNodeSpace(touch:getLocation()).x
        self:setThumbPosX(self._thumbBeganX + locationInNodeX - self._touchBeganX)
        
        if self._callback then
            self._callback(self,self._ratio,SliderEx.TouchEventUp)
        end
    end, cc.Handler.EVENT_TOUCH_ENDED )
      
    local eventDispatcher = self:getEventDispatcher()
    eventDispatcher:addEventListenerWithSceneGraphPriority(listenner, self)
end

function SliderEx:setThumbPosX(newX)
    self._thumbX = newX
    if self._thumbX < 0 then
        self._thumbX = 0
    elseif self._thumbX > self._width then
        self._thumbX = self._width
    end
    
    self._ratio = self._thumbX / self._width
    self._thumb:setPositionX(self._thumbX)
end

function SliderEx:addRatioListener(callback)
    self._callback = callback
end

function SliderEx:setRatio(ratio)
    if ratio < 0 then
        ratio = 0
    elseif ratio > 1.0 then
        ratio = 1.0
    end
    
    self._ratio = ratio
    self._thumbX = self._ratio * self._width
    self._thumb:setPositionX(self._thumbX)
end

------------------------------------------------------------------------
local AudioControlTest = {}

function AudioControlTest.create()
    local layer = cc.Layer:create()
    Helper.initWithLayer(layer)
    Helper.titleLabel:setString("audio control test")
    -- Helper.subtitleLabel:setString("subtitleLabel")
    local layerSize = layer:getContentSize()
    
    AudioControlTest._audioID = cc.AUDIO_INVAILD_ID
    AudioControlTest._loopEnabled = false
    AudioControlTest._volume = 1.0
    AudioControlTest._duration = cc.AUDIO_TIME_UNKNOWN
    AudioControlTest._timeRatio = 0.0
    AudioControlTest._updateTimeSlider = true
    
    ------playItem
    local function playAudio(tag, sender)
        if AudioControlTest._audioID == cc.AUDIO_INVAILD_ID then
            AudioControlTest._audioID = ccexp.AudioEngine:play2d("background.mp3", AudioControlTest._loopEnabled, AudioControlTest._volume)
            
            if AudioControlTest._audioID ~= cc.AUDIO_INVAILD_ID then
                AudioControlTest._playItem:setEnabled(false)
                
                local function finishCallback(audioID,filePath)
                    AudioControlTest._audioID = cc.AUDIO_INVAILD_ID
                    AudioControlTest._playItem:setEnabled(true)
                end
                
                ccexp.AudioEngine:setFinishCallback(AudioControlTest._audioID,finishCallback)
            end
        end
    end
    
    AudioControlTest._playItem = cc.MenuItemFont:create("play")
    AudioControlTest._playItem:setPosition(cc.p(layerSize.width * 0.3,layerSize.height * 0.7))
    AudioControlTest._playItem:registerScriptTapHandler(playAudio)
    
    ------stopItem
    local function stopAudio(tag, sender)
        if AudioControlTest._audioID ~= cc.AUDIO_INVAILD_ID then
            ccexp.AudioEngine:stop(AudioControlTest._audioID)
            AudioControlTest._audioID = cc.AUDIO_INVAILD_ID
            AudioControlTest._playItem:setEnabled(true)
        end
    end
    
    local stopItem = cc.MenuItemFont:create("stop")
    stopItem:setPosition(cc.p(layerSize.width * 0.7,layerSize.height * 0.7))
    stopItem:registerScriptTapHandler(stopAudio)
    
    ------pauseItem
    local function pauseAudio(tag, sender)
        if AudioControlTest._audioID ~= cc.AUDIO_INVAILD_ID then
            ccexp.AudioEngine:pause(AudioControlTest._audioID)
        end
    end
    
    local pauseItem = cc.MenuItemFont:create("pause")
    pauseItem:setPosition(cc.p(layerSize.width * 0.3,layerSize.height * 0.6))
    pauseItem:registerScriptTapHandler(pauseAudio)
    
    ------resumeItem
    local function resumeAudio(tag, sender)
        if AudioControlTest._audioID ~= cc.AUDIO_INVAILD_ID then
            ccexp.AudioEngine:resume(AudioControlTest._audioID)
        end
    end
    
    local resumeItem = cc.MenuItemFont:create("resume")
    resumeItem:setPosition(cc.p(layerSize.width * 0.7,layerSize.height * 0.6))
    resumeItem:registerScriptTapHandler(resumeAudio)
    
    ------loopItem
    local function switchLoop(tag, sender)
        AudioControlTest._loopEnabled = not AudioControlTest._loopEnabled
        if AudioControlTest._audioID ~= cc.AUDIO_INVAILD_ID then
            ccexp.AudioEngine:setLoop(AudioControlTest._audioID, AudioControlTest._loopEnabled)
        end
        if AudioControlTest._loopEnabled then
            AudioControlTest.loopItem:setString("disable-loop")
        else
            AudioControlTest.loopItem:setString("enable-loop")
        end
    end
    
    AudioControlTest.loopItem = cc.MenuItemFont:create("enable-loop")
    AudioControlTest.loopItem:setPosition(cc.p(layerSize.width * 0.3,layerSize.height * 0.5))
    AudioControlTest.loopItem:registerScriptTapHandler(switchLoop)
    
    ------uncacheItem
    local function uncache(tag, sender)
        ccexp.AudioEngine:uncache("background.mp3")
        AudioControlTest._audioID = cc.AUDIO_INVAILD_ID
        AudioControlTest._playItem:setEnabled(true)
    end
    
    local uncacheItem = cc.MenuItemFont:create("uncache")
    uncacheItem:setPosition(cc.p(layerSize.width * 0.7,layerSize.height * 0.5))
    uncacheItem:registerScriptTapHandler(uncache)
    
    local menu = cc.Menu:create()
    menu:addChild(AudioControlTest._playItem)
    menu:addChild(stopItem)
    menu:addChild(pauseItem)
    menu:addChild(resumeItem)
    menu:addChild(AudioControlTest.loopItem)
    menu:addChild(uncacheItem)
    menu:setPosition(cc.p(0, 0))
    layer:addChild(menu)
    
    local function volumeSliderChangedEvent(sender,eventType)
        AudioControlTest._volume = sender:getPercent() / 100.0
        if AudioControlTest._audioID ~= cc.AUDIO_INVAILD_ID then
            ccexp.AudioEngine:setVolume(AudioControlTest._audioID, AudioControlTest._volume)
        end
    end
    local volumeSlider = ccui.Slider:create()
    volumeSlider:setTouchEnabled(true)
    volumeSlider:loadBarTexture("cocosui/sliderTrack.png")
    volumeSlider:loadSlidBallTextures("cocosui/sliderThumb.png", "cocosui/sliderThumb.png", "")
    volumeSlider:loadProgressBarTexture("cocosui/sliderProgress.png")
    volumeSlider:setPosition(cc.p(layerSize.width * 0.5,layerSize.height * 0.35))
    volumeSlider:addEventListener(volumeSliderChangedEvent)
    volumeSlider:setPercent(100)
    layer:addChild(volumeSlider)
    
    local sliderSize = volumeSlider:getContentSize()
    local volumeLabel = cc.Label:createWithTTF("volume:  ","fonts/arial.ttf", 20)
    volumeLabel:setAnchorPoint(cc.p(1.0,0.5))
    volumeLabel:setPosition(cc.p((layerSize.width - sliderSize.width)/2, layerSize.height * 0.35))
    layer:addChild(volumeLabel)
    
    local timeLabel = cc.Label:createWithTTF("time:  ","fonts/arial.ttf", 20)
    timeLabel:setAnchorPoint(cc.p(1.0,0.5))
    timeLabel:setPosition(cc.p((layerSize.width - sliderSize.width)/2, layerSize.height * 0.25))
    layer:addChild(timeLabel)
    
    local function timeSlideChangeCallback(sender,ratio,eventType)
        if (eventType == SliderEx.TouchEventDown or eventType == SliderEx.TouchEventMove) then
            AudioControlTest._updateTimeSlider = false
        else
            if (AudioControlTest._audioID ~= cc.AUDIO_INVAILD_ID and AudioControlTest._duration ~= cc.AUDIO_TIME_UNKNOWN) then
                ccexp.AudioEngine:setCurrentTime(AudioControlTest._audioID,AudioControlTest._duration * ratio)
            end
            AudioControlTest._updateTimeSlider = true
        end
    end
    
    AudioControlTest._timeSlider = SliderEx:create()
    AudioControlTest._timeSlider:setPosition(cc.p(layerSize.width * 0.5,layerSize.height * 0.25))
    AudioControlTest._timeSlider:addRatioListener(timeSlideChangeCallback)
    layer:addChild(AudioControlTest._timeSlider)
    
    local function step(dt)
        if AudioControlTest._audioID ~= cc.AUDIO_INVAILD_ID then
            if AudioControlTest._duration == cc.AUDIO_TIME_UNKNOWN then
                AudioControlTest._duration = ccexp.AudioEngine:getDuration(AudioControlTest._audioID)
            end
            if AudioControlTest._duration ~= cc.AUDIO_TIME_UNKNOWN then
                local time = ccexp.AudioEngine:getCurrentTime(AudioControlTest._audioID)
                AudioControlTest._timeRatio = time / AudioControlTest._duration
                if AudioControlTest._updateTimeSlider then
                    AudioControlTest._timeSlider:setRatio(AudioControlTest._timeRatio)
                end
            end
        end
    end
   
    layer:scheduleUpdateWithPriorityLua(step, 0.05)
    
    function onNodeEvent(tag)
        if tag == "exit" then
            ccexp.AudioEngine:stopAll()
        end
    end
    layer:registerScriptHandler(onNodeEvent)
    
    return layer
end
------------------------------------------------------------------------
local PlaySimultaneouslyTest = {}

function PlaySimultaneouslyTest.create()
    local layer = cc.Layer:create()
    Helper.initWithLayer(layer)
    Helper.titleLabel:setString("Simultaneously play multiple audio")
    
    PlaySimultaneouslyTest._playingcount = 0
    PlaySimultaneouslyTest.files = {}
    for index=1,10 do
        PlaySimultaneouslyTest.files[index] = string.format("audio/SoundEffectsFX009/FX0%d.mp3",80 + index)
    end
    
    local function playAudio(tag, sender)
        local audioID = cc.AUDIO_INVAILD_ID
        --for k, v in pairs(PlaySimultaneouslyTest.files) do
        for index=1,10 do
            audioID = ccexp.AudioEngine:play2d(PlaySimultaneouslyTest.files[index])
            
            if audioID ~= cc.AUDIO_INVAILD_ID then
                PlaySimultaneouslyTest._playItem:setEnabled(false)
                PlaySimultaneouslyTest._playingcount = PlaySimultaneouslyTest._playingcount + 1
                
                local function finishCallback(audioID,filePath)
                    PlaySimultaneouslyTest._playingcount = PlaySimultaneouslyTest._playingcount - 1
                    if PlaySimultaneouslyTest._playingcount <= 0 then
                        PlaySimultaneouslyTest._playItem:setEnabled(true)
                    end
                end
                
                ccexp.AudioEngine:setFinishCallback(audioID,finishCallback)
            end   
        end
    end
    
    PlaySimultaneouslyTest._playItem = cc.MenuItemFont:create("play-simultaneously")
    PlaySimultaneouslyTest._playItem:setNormalizedPosition(cc.p(0.5,0.5))
    PlaySimultaneouslyTest._playItem:registerScriptTapHandler(playAudio)
    
    local menu = cc.Menu:create(PlaySimultaneouslyTest._playItem)
    menu:setPosition(cc.p(0, 0))
    layer:addChild(menu)
    
    function onNodeEvent(tag)
        if tag == "exit" then
            ccexp.AudioEngine:stopAll()
        end
    end
    layer:registerScriptHandler(onNodeEvent)
    
    return layer
end
------------------------------------------------------------------------
local AudioProfileTest = {}

function AudioProfileTest.create()
    local layer = cc.Layer:create()
    Helper.initWithLayer(layer)
    Helper.titleLabel:setString("AudioProfileTest")
    Helper.subtitleLabel:setString("See the console.")
    local layerSize = layer:getContentSize()
    
    AudioProfileTest._files = {}
    AudioProfileTest._files[1] = "background.mp3"
    local targetPlatform = cc.Application:getInstance():getTargetPlatform()
    if (cc.PLATFORM_OS_MAC == targetPlatform or cc.PLATFORM_OS_IPHONE == targetPlatform or cc.PLATFORM_OS_IPAD == targetPlatform) then
        AudioProfileTest._files[2] = "background.caf"
    else
        AudioProfileTest._files[2] = "background.ogg"
    end
    
    AudioProfileTest._profile = ccexp.AudioProfile:new()
    AudioProfileTest._profile.name = "AudioProfileTest"
    AudioProfileTest._profile.maxInstances = 3
    AudioProfileTest._profile.minDelay = 1.0
    
    AudioProfileTest._audioCount = 0
    AudioProfileTest._minDelay = 1.0
    AudioProfileTest._time = 0.0
    
    local menu = cc.Menu:create()
    menu:setPosition(cc.p(0, 0))
    layer:addChild(menu)
    
    local heightRatio = 0.7
    for index=1,2 do
        local function itemClickCallback(tag, sender)
            local audioID = ccexp.AudioEngine:play2d(AudioProfileTest._files[tag],false,1.0,AudioProfileTest._profile)
            if audioID ~= cc.AUDIO_INVAILD_ID then
                AudioProfileTest._time = AudioProfileTest._minDelay
                AudioProfileTest._audioCount = AudioProfileTest._audioCount + 1
                AudioProfileTest._showLabel:setString(string.format("audio count:%d",AudioProfileTest._audioCount))
                
                local function finishCallback(audioID,filePath)
                    AudioProfileTest._audioCount = AudioProfileTest._audioCount - 1
                    AudioProfileTest._showLabel:setString(string.format("audio count:%d",AudioProfileTest._audioCount))
                end
                
                ccexp.AudioEngine:setFinishCallback(audioID,finishCallback)
            end
        end

        local item = cc.MenuItemFont:create("play "..AudioProfileTest._files[index])
        item:setFontSizeObj(20)
        item:setPosition(cc.p(layerSize.width * 0.5,layerSize.height * heightRatio))
        item:registerScriptTapHandler(itemClickCallback)
        menu:addChild(item,0,index)
        heightRatio = heightRatio - 0.1
    end
    
    local origin = cc.Director:getInstance():getVisibleOrigin()
    local size = cc.Director:getInstance():getVisibleSize()
    
    local profileInfoLabel = cc.Label:createWithTTF("AudioProfile Info:\n    max instance:3  \n    minimum delay:1.0","fonts/arial.ttf", 12)
    profileInfoLabel:setAnchorPoint(cc.p(0,0.5))
    profileInfoLabel:setPosition(cc.p(origin.x, origin.y + size.height * 0.65))
    layer:addChild(profileInfoLabel)
    
    AudioProfileTest._showLabel = cc.Label:createWithTTF("audio count:0","fonts/arial.ttf", 12)
    AudioProfileTest._showLabel:setAnchorPoint(cc.p(0,0.5))
    AudioProfileTest._showLabel:setPosition(cc.p(origin.x, origin.y + size.height * 0.5))
    layer:addChild(AudioProfileTest._showLabel)
    
    AudioProfileTest._timeSlider = ccui.Slider:create()
    AudioProfileTest._timeSlider:setTouchEnabled(false)
    AudioProfileTest._timeSlider:loadBarTexture("cocosui/sliderTrack.png")
    AudioProfileTest._timeSlider:loadSlidBallTextures("cocosui/sliderThumb.png", "cocosui/sliderThumb.png", "")
    AudioProfileTest._timeSlider:loadProgressBarTexture("cocosui/sliderProgress.png")
    AudioProfileTest._timeSlider:setPosition(cc.p(layerSize.width * 0.5,layerSize.height * heightRatio))
    layer:addChild(AudioProfileTest._timeSlider)
    
    local function step(dt)
        if AudioProfileTest._time > 0 then
            AudioProfileTest._time = AudioProfileTest._time - dt
            if AudioProfileTest._time < 0 then
                AudioProfileTest._time = 0
            end
            AudioProfileTest._timeSlider:setPercent(100 * AudioProfileTest._time / AudioProfileTest._minDelay)
        end
    end
    layer:scheduleUpdateWithPriorityLua(step, 0.05)
    
    function onNodeEvent(tag)
        if tag == "exit" then
            ccexp.AudioEngine:stopAll()
        end
    end
    layer:registerScriptHandler(onNodeEvent)
    
    return layer
end
------------------------------------------------------------------------
local InvalidAudioFileTest = {}

function InvalidAudioFileTest.create()
    local layer = cc.Layer:create()
    Helper.initWithLayer(layer)
    Helper.titleLabel:setString("Test invalid audio file")
    Helper.subtitleLabel:setString("Not crash,please see the console.")
    local layerSize = layer:getContentSize()
    
    -- unsupported media type
    local function playUnsupportedAudio(tag, sender)
        local targetPlatform = cc.Application:getInstance():getTargetPlatform()
        if (cc.PLATFORM_OS_MAC == currPlatform or cc.PLATFORM_OS_IPHONE == targetPlatform or cc.PLATFORM_OS_IPAD == targetPlatform) then
            ccexp.AudioEngine:play2d("background.ogg")
        end
        if (cc.PLATFORM_OS_ANDROID == targetPlatform) then
            ccexp.AudioEngine:play2d("background.caf")
        end
    end
    
    local playItem1 = cc.MenuItemFont:create("play unsupported media type")
    playItem1:setNormalizedPosition(cc.p(0.5,0.6))
    playItem1:registerScriptTapHandler(playUnsupportedAudio)
    
    -- not-existent audio
    local function playNotExistentAudio(tag, sender)
        ccexp.AudioEngine:play2d("not-existent file.mp3")
    end
    
    local playItem2 = cc.MenuItemFont:create("play not-existent file")
    playItem2:setNormalizedPosition(cc.p(0.5,0.4))
    playItem2:registerScriptTapHandler(playNotExistentAudio)
    
    local menu = cc.Menu:create()
    menu:addChild(playItem1)
    menu:addChild(playItem2)
    menu:setPosition(cc.p(0, 0))
    layer:addChild(menu)
    
    return layer
end
------------------------------------------------------------------------
local LargeAudioFileTest = {}

function LargeAudioFileTest.create()
    local layer = cc.Layer:create()
    Helper.initWithLayer(layer)
    Helper.titleLabel:setString("Test large audio file")
    local layerSize = layer:getContentSize()
    
    local function playAudio(tag, sender)
        ccexp.AudioEngine:play2d("audio/LuckyDay.mp3")
    end
    
    local playItem = cc.MenuItemFont:create("play large audio file")
    playItem:setNormalizedPosition(cc.p(0.5,0.5))
    playItem:registerScriptTapHandler(playAudio)
    
    local menu = cc.Menu:create(playItem)
    menu:setPosition(cc.p(0, 0))
    layer:addChild(menu)
    
    function onNodeEvent(tag)
        if tag == "exit" then
            ccexp.AudioEngine:stopAll()
        end
    end
    layer:registerScriptHandler(onNodeEvent)
    
    return layer
end
------------------------------------------------------------------------
function AudioEngineTest()
    local scene = cc.Scene:create()

    Helper.createFunctionTable = {
        AudioControlTest.create,
        PlaySimultaneouslyTest.create,
        AudioProfileTest.create,
        InvalidAudioFileTest.create,
        LargeAudioFileTest.create
    }
    Helper.index = 1
    
    scene:addChild(AudioControlTest.create())
    scene:addChild(CreateBackMenuItem())
    return scene
end