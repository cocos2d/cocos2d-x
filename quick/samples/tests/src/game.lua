
require("config")
require("framework.init")

-- define global module
game = {}

function game.startup()
    cc.FileUtils:getInstance():addSearchPath("res/")

    game.enterMainScene()
end

function game.createMenu(items, callback)
    local menu = cc.ui.UIListView.new {
        viewRect = cc.rect(display.cx - 200, display.bottom + 100, 400, display.height - 200),
        direction = cc.ui.UIScrollView.DIRECTION_VERTICAL}
        :onScroll(function(event)
                if "moved" == event.name then
                    game.bListViewMove = true
                elseif "ended" == event.name then
                    game.bListViewMove = false
                end
            end)

    for i, v in ipairs(items) do
        local item = menu:newItem()
        local content

        content = cc.ui.UIPushButton.new()
            :setButtonSize(200, 40)
            :setButtonLabel(cc.ui.UILabel.new({text = v, size = 24, color = display.COLOR_BLUE}))
            :onButtonClicked(function(event)
                if game.bListViewMove then
                    return
                end

                callback(v)
            end)
        content:setTouchSwallowEnabled(false)
        item:addContent(content)
        item:setItemSize(120, 40)

        menu:addItem(item)
    end
    menu:reload()

    return menu
end

function game.exit()
    os.exit()
end

function game.enterMainScene()
    display.replaceScene(require("scenes.MainScene").new(), "random", 1)

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
                display.replaceScene(require("scenes.MainScene").new(), "random", 1)
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
