local testPatches = {
{'LuaLoaderTest/?.lua', 'simple'},
{'LuaLoaderTest/?/init.lua', 'in_dir'},
{'LuaLoaderTest/?.lc', 'strange_ext'},
{'./LuaLoaderTest/?.lua', 'simple'}, -- test removing leading `./`
{'LuaLoaderTest/?;LuaLoaderTest/?/init.lua', 'in_dir'} -- test case then directory found
}

local function TestNode()

    local function title()
        return "LuaLoaderTest"
    end
    local node = cc.Node:create()

    local function onEnter()
        local titleLabel = cc.Label:createWithTTF(title(), "fonts/arial.ttf", 32)
        node:addChild(titleLabel, 1)
        titleLabel:setAnchorPoint(cc.p(0.5, 0.5))
        titleLabel:setPosition( cc.p(VisibleRect:center().x, VisibleRect:top().y - 50) )
        local oldPath = package.path
        local result = {}
        for _,tab in ipairs(testPatches) do
            package.path = package.path..';'..tab[1]
            local ok, msg = pcall(require, tab[2])
            result[#result+1] = 'Loading by path "'..tab[1]..'", filename "'..tab[2]..'": '..(ok and 'success' or 'failure')
            package.path = oldPath
        end
        local label = cc.LabelTTF:create(table.concat(result, '\n'), "Marker Felt", 10)
        node:addChild(label, 1)
        label:setAnchorPoint(cc.p(0.5, 0.5))
        label:setPosition(VisibleRect:center())
    end

    local function onNodeEvent(event)
        if "enter" == event then
            onEnter()
        end
    end

    node:registerScriptHandler(onNodeEvent)
    
    return node
end

function LuaLoaderMain()
    cclog("LuaLoaderMain")
    local scene = cc.Scene:create()
    scene:addChild(TestNode())
    scene:addChild(CreateBackMenuItem())
    return scene
end
