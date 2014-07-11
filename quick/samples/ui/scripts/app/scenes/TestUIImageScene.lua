
local TestUIImageScene = class("TestUIImageScene", function()
    return display.newScene("TestUIImageScene")
end)

function TestUIImageScene:ctor()
    app:createGrid(self)

    self:createFixedSizeImages()
    self:createScale9Images()
    self:createScaledImages()

    app:createTitle(self, "Test UIImage")
    app:createNextButton(self)
end

function TestUIImageScene:createFixedSizeImages()
    cc.ui.UIImage.new("PinkScale9Block.png")
        :align(display.LEFT_TOP, display.cx - 400, display.cy + 285)
        :addTo(self)
    cc.ui.UILabel.new({
        text = "fixed size",
        size = 16,
        color = display.COLOR_BLACK,
    }):align(display.CENTER, display.cx - 350, display.cy + 170):addTo(self)

    cc.ui.UIImage.new("PinkScale9Block.png")
        :align(display.RIGHT_TOP, display.cx + 400, display.cy + 285)
        :addTo(self)
    cc.ui.UILabel.new({
        text = "fixed size",
        size = 16,
        color = display.COLOR_BLACK,
    }):align(display.CENTER, display.cx + 350, display.cy + 170):addTo(self)
end

function TestUIImageScene:createScale9Images()
    cc.ui.UIImage.new("PinkScale9Block.png", {scale9 = true})
        :setLayoutSize(200, 100)
        :align(display.LEFT_CENTER, display.cx - 400, display.cy + 45)
        :addTo(self)
    cc.ui.UILabel.new({
        text = "use scale9sprite",
        size = 16,
        color = display.COLOR_BLACK,
    }):align(display.CENTER, display.cx - 300, display.cy - 20):addTo(self)

    cc.ui.UIImage.new("PinkScale9Block.png", {scale9 = true})
        :setLayoutSize(200, 100)
        :align(display.RIGHT_CENTER, display.cx + 400, display.cy + 45)
        :addTo(self)
    cc.ui.UILabel.new({
        text = "use scale9sprite",
        size = 16,
        color = display.COLOR_BLACK,
    }):align(display.CENTER, display.cx + 300, display.cy - 20):addTo(self)

    cc.ui.UIImage.new("PinkScale9Block.png", {scale9 = true})
        :setLayoutSize(200, 150)
        :align(display.CENTER, display.cx, display.cy + 70)
        :addTo(self)
    cc.ui.UILabel.new({
        text = "use scale9sprite",
        size = 16,
        color = display.COLOR_BLACK,
    }):align(display.CENTER, display.cx, display.cy - 20):addTo(self)
end

function TestUIImageScene:createScaledImages()
    cc.ui.UIImage.new("PinkScale9Block.png")
        :setLayoutSize(200, 100)
        :align(display.LEFT_BOTTOM, display.cx - 400, display.cy - 225)
        :addTo(self)
    cc.ui.UILabel.new({
        text = "use scaleX, scaleY",
        size = 16,
        color = display.COLOR_BLACK,
    }):align(display.CENTER, display.cx - 300, display.cy - 240):addTo(self)

    cc.ui.UIImage.new("PinkScale9Block.png")
        :setLayoutSize(200, 100)
        :align(display.RIGHT_BOTTOM, display.cx + 400, display.cy - 225)
        :addTo(self)
    cc.ui.UILabel.new({
        text = "use scaleX, scaleY",
        size = 16,
        color = display.COLOR_BLACK,
    }):align(display.CENTER, display.cx + 300, display.cy - 240):addTo(self)


    cc.ui.UIImage.new("PinkScale9Block.png")
        :setLayoutSize(200, 150)
        :align(display.CENTER, display.cx, display.cy - 150)
        :addTo(self)
    cc.ui.UILabel.new({
        text = "use scaleX, scaleY",
        size = 16,
        color = display.COLOR_BLACK,
    }):align(display.CENTER, display.cx, display.cy - 240):addTo(self)
end


return TestUIImageScene
