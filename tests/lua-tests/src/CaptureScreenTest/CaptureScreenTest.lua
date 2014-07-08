local winSize = cc.Director:getInstance():getWinSize()
local kTagSprite = 1
local childTag   = 119

local function createLayer()
    local layer = cc.Layer:create()
    local filename = ""

    local title = cc.Label:createWithTTF("New Renderer", "fonts/arial.ttf", 36)
    title:setColor(cc.c3b(255,255,0))
    layer:addChild(title, 1, 10000)
    title:setPosition( cc.p(VisibleRect:center().x, VisibleRect:top().y - 30))

    local subTitle = cc.Label:createWithTTF("Capture screen test, press the menu items to capture the screen", "fonts/arial.ttf", 12)
    subTitle:setColor(cc.c3b(255,255,0))
    layer:addChild(subTitle, 1, 10001)
    subTitle:setPosition( cc.p(VisibleRect:center().x, VisibleRect:top().y - 60) )

    local left  = cc.p(winSize.width / 4, winSize.height / 2)
    local right = cc.p(winSize.width / 4 * 3, winSize.height / 2)

    local sp1 = cc.Sprite:create("Images/grossini.png")
    sp1:setPosition(left)
    local move1 = cc.MoveBy:create(1, cc.p(winSize.width/2, 0))
    local seq1  = cc.RepeatForever:create(cc.Sequence:create(move1, move1:reverse()))
    layer:addChild(sp1)
    sp1:runAction(seq1)
    local sp2 = cc.Sprite:create("Images/grossinis_sister1.png")
    sp2:setPosition(right)
    local move2 = cc.MoveBy:create(1, cc.p(-winSize.width/2, 0))
    local seq2  = cc.RepeatForever:create(cc.Sequence:create(move2, move2:reverse()))
    layer:addChild(sp2)
    sp2:runAction(seq2)

    local function afterCaptured(succeed, outputFile)
        if succeed then
            local sp = cc.Sprite:create(outputFile)
            layer:addChild(sp, 0, childTag)
            sp:setPosition(winSize.width / 2, winSize.height / 2)
            sp:setScale(0.25)
            fileName = outputFile
        else
            cclog("Capture screen failed.")
        end
    end

    local function onCaptured(tag, sender)
        cc.Director:getInstance():getTextureCache():removeTextureForKey(fileName)
        layer:removeChildByTag(childTag)
        fileName = "CaptureScreenTest.png"
        cc.utils:captureScreen(afterCaptured, fileName)
    end

    local ttfConfig = {}
    ttfConfig.fontFilePath = "fonts/arial.ttf"
    ttfConfig.fontSize     = 24
    local label1 = cc.Label:createWithTTF(ttfConfig, "capture all", cc.TEXT_ALIGNMENT_CENTER, winSize.width)
    local mi1 = cc.MenuItemLabel:create(label1)
    mi1:registerScriptTapHandler(onCaptured)
    local menu = cc.Menu:create(mi1)
    layer:addChild(menu)
    menu:setPosition(winSize.width / 2, winSize.height / 4)

    return layer
end

--------------------------------
-- CaptureScreen
--------------------------------
function CaptureScreenTestMain()
    local scene = cc.Scene:create()
    scene:addChild(createLayer())
    scene:addChild(CreateBackMenuItem())
    return scene
end
