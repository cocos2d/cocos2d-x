--[[--

使用 UIImage, UILabel 和 system 控件组装成一个 EditBox

]]

local EditBoxLite = class("EditBoxLite", function()
        return display.newNode()
    end)

function EditBoxLite.create(params)

    if device.platform == "windows" then
        return cc.ui.UIInput.new(params)
    elseif device.platform == "mac" then
        return EditBoxLite.new(params)
    end

end

--[[

@param: table params

- int    fontSize 文字大小
- string font     文字名字
- string image    输入框底板图片名字
- table  size     输入框大小
- int    x        x 坐标
- int    y        y 坐标
- string text     初始化文字

@return cc.Node
]]
function EditBoxLite:ctor(params)
    local fontSize = params.fontSize or 35
    local fontName = params.font or "arial" --"Courier New"
    local image    = params.image
    local text     = params.text or ""
    local width    = params.size.width
    local height   = params.size.height
    local x        = params.x
    local y        = params.y

    self.bg_ =     cc.ui.UIImage.new(image, {scale9 = true})
                        :setLayoutSize(width, height)
                        :addTo(self)

    self.bg_:setTouchEnabled(true)
    self.bg_:addNodeEventListener(cc.NODE_TOUCH_EVENT, function(e)
        local ed = PlayerProtocol:getInstance():getEditBoxService()
        ed:registerHandler(function(e)
                self.label_:setVisible(true)
                self.label_:setString(e)
            end)
        ed:setFont(fontName, fontSize)
        local p = self:convertToWorldSpace(cc.p(0, 0))
        ed:showSingleLineEditBox(cc.rect(p.x, p.y, width, height))
        ed:setText(self.label_:getString())
        self.label_:setVisible(false)

    end)

    -- 用一个 clipNode 把 Label 裁剪, 不然内容过长
    local rect = cc.rect(0, 0, width, height)
    self.clipnode_ = display.newClippingRegionNode(rect)
    self.clipnode_:addTo(self)

    self.label_ =
    cc.ui.UILabel.new({
        text = text,
        size = fontSize,
        font = fontName,
    })
    self.label_:setAnchorPoint(0,0)
    self.label_:addTo(self.clipnode_)

    self:pos(x, y)
end

function EditBoxLite:setText(text)
    self.label_:setString(text)
end

function EditBoxLite:getText()
    return self.label_:getString()
end

return EditBoxLite
