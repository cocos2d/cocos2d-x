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
    cc.VERTICAL_TEXT_ALIGNMENT_TOP,
    cc.VERTICAL_TEXT_ALIGNMENT_CENTER,
    cc.VERTICAL_TEXT_ALIGNMENT_BOTTOM,
}

local vAlignCount = table.getn(verticalAlignment)

local function showFont(ret, pFont)

    cclog("vAlignIdx="..vAlignIdx)
    local s = cc.Director:getInstance():getWinSize()

    local blockSize = cc.size(s.width/3, 200)
    local fontSize = 26

    ret:removeChildByTag(kTagLabel1, true)
    ret:removeChildByTag(kTagLabel2, true)
    ret:removeChildByTag(kTagLabel3, true)
    ret:removeChildByTag(kTagLabel4, true)

    local top = cc.LabelTTF:create(pFont, pFont, 24)
    local left = cc.LabelTTF:create("alignment left", pFont, fontSize,
                                   blockSize, cc.TEXT_ALIGNMENT_LEFT, verticalAlignment[vAlignIdx])
    local center = cc.LabelTTF:create("alignment center", pFont, fontSize,
                                     blockSize, cc.TEXT_ALIGNMENT_CENTER, verticalAlignment[vAlignIdx])
    local right = cc.LabelTTF:create("alignment right", pFont, fontSize,
                                    blockSize, cc.TEXT_ALIGNMENT_RIGHT, verticalAlignment[vAlignIdx])

    local leftColor = cc.LayerColor:create(cc.c4b(100, 100, 100, 255), blockSize.width, blockSize.height)
    local centerColor = cc.LayerColor:create(cc.c4b(200, 100, 100, 255), blockSize.width, blockSize.height)
    local rightColor = cc.LayerColor:create(cc.c4b(100, 100, 200, 255), blockSize.width, blockSize.height)

    leftColor:ignoreAnchorPointForPosition(false)
    centerColor:ignoreAnchorPointForPosition(false)
    rightColor:ignoreAnchorPointForPosition(false)

    top:setAnchorPoint(cc.p(0.5, 1))
    left:setAnchorPoint(cc.p(0,0.5))
    leftColor:setAnchorPoint(cc.p(0,0.5))
    center:setAnchorPoint(cc.p(0,0.5))
    centerColor:setAnchorPoint(cc.p(0,0.5))
    right:setAnchorPoint(cc.p(0,0.5))
    rightColor:setAnchorPoint(cc.p(0,0.5))

    top:setPosition(cc.p(s.width/2,s.height-20))
    left:setPosition(cc.p(0,s.height/2))
    leftColor:setPosition(left:getPosition())
    center:setPosition(cc.p(blockSize.width, s.height/2))
    centerColor:setPosition(center:getPosition())
    right:setPosition(cc.p(blockSize.width*2, s.height/2))
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
    local scene = cc.Scene:create()
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
