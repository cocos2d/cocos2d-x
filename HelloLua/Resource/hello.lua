require "hello2"

cocos2d.CCLuaLog("result is " .. myadd(3, 5))

-- create scene & layer
layerFarm = cocos2d.CCLayer:node()
layerFarm:setIsTouchEnabled(true)

layerMenu = cocos2d.CCLayer:node()

sceneGame = cocos2d.CCScene:node()
sceneGame:addChild(layerFarm)
sceneGame:addChild(layerMenu)

winSize = cocos2d.CCDirector:sharedDirector():getWinSize()

-- add in farm background
spriteFarm = cocos2d.CCSprite:spriteWithFile("farm.jpg")
spriteFarm:setPosition(cocos2d.CCPoint(winSize.width/2 + 80, winSize.height/2))
layerFarm:addChild(spriteFarm)

-- touch handers
pointBegin = nil

function btnTouchMove(e)
    cocos2d.CCLuaLog("btnTouchMove")
    if pointBegin ~= nil then
        local v = e[1]
        local pointMove = v:locationInView(v:view())
        pointMove = cocos2d.CCDirector:sharedDirector():convertToGL(pointMove)
        local positionCurrent = layerFarm:getPosition()
        layerFarm:setPosition(cocos2d.CCPoint(positionCurrent.x + pointMove.x - pointBegin.x, positionCurrent.y + pointMove.y - pointBegin.y))
        pointBegin = pointMove
    end
end

function btnTouchBegin(e)
    cocos2d.CCScheduler:sharedScheduler():unscheduleScriptFunc("tick")
    cocos2d.CCLuaLog("btnTouchBegin")
    for k,v in ipairs(e) do
        pointBegin = v:locationInView(v:view())
        pointBegin = cocos2d.CCDirector:sharedDirector():convertToGL(pointBegin)
    end
end

function btnTouchEnd(e)
    cocos2d.CCLuaLog("btnTouchEnd")
    touchStart = nil
end

-- regiester touch handlers
layerFarm.__CCTouchDelegate__:registerScriptTouchHandler(cocos2d.CCTOUCHBEGAN, "btnTouchBegin")
layerFarm.__CCTouchDelegate__:registerScriptTouchHandler(cocos2d.CCTOUCHMOVED, "btnTouchMove")
layerFarm.__CCTouchDelegate__:registerScriptTouchHandler(cocos2d.CCTOUCHENDED, "btnTouchEnd")


-- add land sprite
for i=0,3,1 do
    for j=0,1,1 do
        spriteLand = cocos2d.CCSprite:spriteWithFile("land.png")
        layerFarm:addChild(spriteLand)
        spriteLand:setPosition(cocos2d.CCPoint(200+j*180 - i%2*90, 10+i*95/2))
    end
end

-- add crop

for i=0,3,1 do
    for j=0,1,1 do

        textureCrop = cocos2d.CCTextureCache:sharedTextureCache():addImage("crop.png")
        frameCrop = cocos2d.CCSpriteFrame:frameWithTexture(textureCrop, cocos2d.CCRectMake(0, 0, 105, 95))
        spriteCrop = cocos2d.CCSprite:spriteWithSpriteFrame(frameCrop);

        layerFarm:addChild(spriteCrop)

        spriteCrop:setPosition(cocos2d.CCPoint(10+200+j*180 - i%2*90, 30+10+i*95/2))

    end
end

-- add the moving dog

FrameWidth = 105
FrameHeight = 95

textureDog = cocos2d.CCTextureCache:sharedTextureCache():addImage("dog.png")
frame0 = cocos2d.CCSpriteFrame:frameWithTexture(textureDog, cocos2d.CCRectMake(0, 0, FrameWidth, FrameHeight))
frame1 = cocos2d.CCSpriteFrame:frameWithTexture(textureDog, cocos2d.CCRectMake(FrameWidth*1, 0, FrameWidth, FrameHeight))

spriteDog = cocos2d.CCSprite:spriteWithSpriteFrame(frame0)
spriteDog:setPosition(cocos2d.CCPoint(0, winSize.height/4*3))
layerFarm:addChild(spriteDog)

animation = cocos2d.CCAnimation:animation()

animFrames = cocos2d.CCMutableArray_CCSpriteFrame__:new(2)
animFrames:addObject(frame0)
animFrames:addObject(frame1)

animation = cocos2d.CCAnimation:animationWithFrames(animFrames,0.5)

animate = cocos2d.CCAnimate:actionWithAnimation(animation, false);
spriteDog:runAction(cocos2d.CCRepeatForever:actionWithAction(animate))


-- add a popup menu

function menuCallbackClosePopup()
-- stop test sound effect
CocosDenshion.SimpleAudioEngine:sharedEngine():stopEffect(effectID)  
menuPopup:setIsVisible(false)
end

menuPopupItem = cocos2d.CCMenuItemImage:itemFromNormalImage("menu2.png", "menu2.png")
menuPopupItem:setPosition( cocos2d.CCPoint(0, 0) )
menuPopupItem:registerScriptHandler("menuCallbackClosePopup")
menuPopup = cocos2d.CCMenu:menuWithItem(menuPopupItem)
menuPopup:setPosition( cocos2d.CCPoint(winSize.width/2, winSize.height/2) )
menuPopup:setIsVisible(false)
layerMenu:addChild(menuPopup)

-- add the left-bottom "tools" menu to invoke menuPopup

function menuCallbackOpenPopup()
-- loop test sound effect
-- NOTE: effectID is global, so it can be used to stop 
effectID = CocosDenshion.SimpleAudioEngine:sharedEngine():playEffect("effect1.wav")  
menuPopup:setIsVisible(true)
end

menuToolsItem = cocos2d.CCMenuItemImage:itemFromNormalImage("menu1.png","menu1.png")
menuToolsItem:setPosition( cocos2d.CCPoint(0, 0) )	
menuToolsItem:registerScriptHandler("menuCallbackOpenPopup")
menuTools = cocos2d.CCMenu:menuWithItem(menuToolsItem)
menuTools:setPosition( cocos2d.CCPoint(30, 40) )
layerMenu:addChild(menuTools)


function tick()

    local point = spriteDog:getPosition();

    if point.x > winSize.width then
        point.x = 0
        spriteDog:setPosition(point)
    else
        point.x = point.x + 1 
        spriteDog:setPosition(point) 
    end

end

-- avoid memory leak
collectgarbage( "setpause", 100) 
collectgarbage( "setstepmul", 5000)


cocos2d.CCScheduler:sharedScheduler():scheduleScriptFunc("tick", 0.01, false)

-- play background music
CocosDenshion.SimpleAudioEngine:sharedEngine():playBackgroundMusic("background.mp3", true);  
-- preload effect
CocosDenshion.SimpleAudioEngine:sharedEngine():preloadEffect("effect1.wav");
-- run 
cocos2d.CCDirector:sharedDirector():runWithScene(sceneGame)
