
local MainScene = class("MainScene", function()
    return display.newScene("MainScene")
end)


function newButton(imageName, listener, setAlpha)
    local sprite = display.newScale9Sprite(imageName)
    if setAlpha == nil then setAlpha = true end

    sprite:setTouchEnabled(true)
    sprite:addNodeEventListener(cc.NODE_TOUCH_EVENT, function(event)
        if event.name == "began" then
            if setAlpha then sprite:setOpacity(128) end
            return true
        end

        local touchInSprite = sprite:getCascadeBoundingBox():containsPoint(cc.p(event.x, event.y))
        if event.name == "moved" then
            if touchInSprite then
                if setAlpha then sprite:setOpacity(128) end
            else
                sprite:setOpacity(255)
            end
        elseif event.name == "ended" then
            if touchInSprite then listener() end
            sprite:setOpacity(255)
        else
            sprite:setOpacity(255)
        end
    end)

    return sprite
end


function MainScene:ctor()
    local btn = newButton("EditBoxBg.png", function ( )
        print("button pressed")
    end):addTo(self):pos(display.cx - 100, display.cy)
    btn:setContentSize(cc.size(120, 160))

    local editBox2 = cc.ui.UIInput.new({
        image = "EditBoxBg.png",
        size = cc.size(400, 96),
        x = display.cx,
        y = display.cy,
        listener = function(event, editbox)
            if event == "began" then
                self:onEditBoxBegan(editbox)
            elseif event == "ended" then
                self:onEditBoxEnded(editbox)
            elseif event == "return" then
                self:onEditBoxReturn(editbox)
            elseif event == "changed" then
                self:onEditBoxChanged(editbox)
            else
                printf("EditBox event %s", tostring(event))
            end
        end
    })
    editBox2:setReturnType(cc.KEYBOARD_RETURNTYPE_SEND)
    self:addChild(editBox2)

    local btn = newButton("EditBoxBg.png", function ( )
        print("button pressed")
    end):addTo(self):pos(display.cx + 100, display.cy)
    btn:setContentSize(cc.size(120, 160))
end

function MainScene:onEditBoxBegan(editbox)
    printf("editBox1 event began : text = %s", editbox:getText())
end

function MainScene:onEditBoxEnded(editbox)
    printf("editBox1 event ended : %s", editbox:getText())
end

function MainScene:onEditBoxReturn(editbox)
    printf("editBox1 event return : %s", editbox:getText())
end

function MainScene:onEditBoxChanged(editbox)
    printf("editBox1 event changed : %s", editbox:getText())
end

function MainScene:onEnter()

end

return MainScene
