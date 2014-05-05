local  kTagLabel1 = 0
local  kTagLabel2 = 1
local  kTagLabel3 = 2
local  kTagLabel4 = 3

local  fontList = {
    "fonts/A Damn Mess.ttf",
    "fonts/Abberancy.ttf",
    "fonts/Abduction.ttf",
    "fonts/Paint Boy.ttf",
    "fonts/Schwarzwald Regular.ttf",
    "fonts/Scissor Cuts.ttf"
}

local fontCount = table.getn(fontList)
cclog("font count = "..fontCount)

local vAlignIdx = 1
local verticalAlignment = {
    kCCVerticalTextAlignmentTop,
    kCCVerticalTextAlignmentCenter,
    kCCVerticalTextAlignmentBottom,
}

local vAlignCount = table.getn(verticalAlignment)

local function showFont(ret, pFont)

    cclog("vAlignIdx="..vAlignIdx)
    local s = CCDirector:sharedDirector():getWinSize()

    local blockSize = CCSizeMake(s.width/3, 200)
    local fontSize = 26

    ret:removeChildByTag(kTagLabel1, true)
    ret:removeChildByTag(kTagLabel2, true)
    ret:removeChildByTag(kTagLabel3, true)
    ret:removeChildByTag(kTagLabel4, true)

    local top = CCLabelTTF:create(pFont, pFont, 24)
    local left = CCLabelTTF:create("alignment left", pFont, fontSize,
                                   blockSize, kCCTextAlignmentLeft, verticalAlignment[vAlignIdx])
    local center = CCLabelTTF:create("alignment center", pFont, fontSize,
                                     blockSize, kCCTextAlignmentCenter, verticalAlignment[vAlignIdx])
    local right = CCLabelTTF:create("alignment right", pFont, fontSize,
                                    blockSize, kCCTextAlignmentRight, verticalAlignment[vAlignIdx])

    local leftColor = CCLayerColor:create(ccc4(100, 100, 100, 255), blockSize.width, blockSize.height)
    local centerColor = CCLayerColor:create(ccc4(200, 100, 100, 255), blockSize.width, blockSize.height)
    local rightColor = CCLayerColor:create(ccc4(100, 100, 200, 255), blockSize.width, blockSize.height)

    leftColor:ignoreAnchorPointForPosition(false)
    centerColor:ignoreAnchorPointForPosition(false)
    rightColor:ignoreAnchorPointForPosition(false)

    top:setAnchorPoint(ccp(0.5, 1))
    left:setAnchorPoint(ccp(0,0.5))
    leftColor:setAnchorPoint(ccp(0,0.5))
    center:setAnchorPoint(ccp(0,0.5))
    centerColor:setAnchorPoint(ccp(0,0.5))
    right:setAnchorPoint(ccp(0,0.5))
    rightColor:setAnchorPoint(ccp(0,0.5))

    top:setPosition(ccp(s.width/2,s.height-20))
    left:setPosition(ccp(0,s.height/2))
    leftColor:setPosition(left:getPosition())
    center:setPosition(ccp(blockSize.width, s.height/2))
    centerColor:setPosition(center:getPosition())
    right:setPosition(ccp(blockSize.width*2, s.height/2))
    rightColor:setPosition(right:getPosition())

    ret:addChild(leftColor, -1)
    ret:addChild(left, 0, kTagLabel1)
    ret:addChild(rightColor, -1)
    ret:addChild(right, 0, kTagLabel2)
    ret:addChild(centerColor, -1)
    ret:addChild(center, 0, kTagLabel3)
    ret:addChild(top, 0, kTagLabel4)
end

local isFirst = true
local originCreateLayer = createTestLayer
local function createTestLayer()
    if isFirst == false then
        if Helper.index == 1 then
            vAlignIdx =  vAlignIdx % vAlignCount + 1
        end
    else
        isFirst = false
    end

    local ret = originCreateLayer("")
    showFont(ret, fontList[Helper.index])
    return ret
end

function FontTestMain()
    cclog("FontTestMain")
    Helper.index = 1
    vAlignIdx = 1
    local scene = CCScene:create()
    Helper.createFunctionTable = {
        createTestLayer,
        createTestLayer,
        createTestLayer,
        createTestLayer,
        createTestLayer,
        createTestLayer
    }
    scene:addChild(createTestLayer())
    scene:addChild(CreateBackMenuItem())
    return scene
end
