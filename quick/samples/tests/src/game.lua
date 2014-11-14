
require("config")
require("framework.init")

-- define global module
game = {}

function game.startup()
    cc.FileUtils:getInstance():addSearchPath("res/")

    game.enterMainScene()
end

function game.createMenu(items, callback)
    local menu = display.newNode()

    for i, item in ipairs(items) do
        cc.ui.UIPushButton.new()
            :setButtonLabel(cc.ui.UILabel.new({text = item, size = 32, color = display.COLOR_BLUE}))
            :onButtonClicked(function(event)
                callback(item)
            end)
            :align(display.LEFT_BOTTOM, 0, 40*i)
            :addTo(menu)
    end

    menu:setPosition(display.cx, display.cy)
    return menu
end

function game.exit()
    os.exit()
end

function game.enterMainScene()
    display.replaceScene(require("scenes.MainScene").new(), "fade", 0.6, display.COLOR_WHITE)

    -- local Scene = require("tests.framework.networkTest")
    -- display.replaceScene(Scene.new())
end

function game.createSceneClass(name)
    local cls = class(name, function()
        return display.newScene(name)
    end)

    function cls:prepare(args)
        self.menuLayer = display.newLayer()
        self.menuLayer:setTouchSwallowEnabled(false)
        self:addChild(self.menuLayer, 30000)

        -- local label = ui.newTTFLabelMenuItem({
        --     text = "RETURN",
        --     color = ccc3(255, 0, 0),
        --     x = display.right - 80,
        --     y = display.bottom + 30,
        --     listener = function()
        --         display.replaceScene(require("scenes.MainScene").new())
        --     end
        -- })
        -- self.menuLayer:addChild(ui.newMenu({label}))

        cc.ui.UIPushButton.new()
            :setButtonLabel(cc.ui.UILabel.new({text = "RETURN", size = 32, color = display.COLOR_BLUE}))
            :onButtonClicked(function(event)
                display.replaceScene(require("scenes.MainScene").new())
            end)
            :align(display.LEFT_BOTTOM, display.right - 80, display.bottom + 30)
            :addTo(self.menuLayer)

        local label = display.newTTFLabel({
            text = "====   " .. cls.__cname .. "   ====",
            size = 24,
            color = cc.c3b(0, 255, 0),
            x = display.cx,
            y = display.top - 30,
            align = display.TEXT_ALIGN_CENTER,
        })
        self.menuLayer:addChild(label)

        if args and args.description then
            local label = display.newTTFLabel({
                text = args.description,
                size = 20,
                color = cc.c3b(0, 160, 0),
                x = display.cx,
                y = display.top - 60,
                align = display.TEXT_ALIGN_CENTER,
            })
            self.menuLayer:addChild(label)
        end
    end


    function cls:runTest(name)
        printf("----------------------------------------")
        printf("-- run test %s", name)
        print("--")
        name = string.gsub(name, " ", "_")
        if self.beforeRunTest then self:beforeRunTest() end
        local m = self[name .. "Test"]
        m(self)
    end

    return cls
end

function bin2hex(bin)
    local t = {}
    for i = 1, string.len(bin) do
        local c = string.byte(bin, i, i)
        t[#t + 1] = string.format("%02x", c)
    end
    return table.concat(t, " ")
end
