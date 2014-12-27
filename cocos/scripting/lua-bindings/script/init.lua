
require "cocos.cocos2d.Cocos2d"
require "cocos.cocos2d.Cocos2dConstants"
require "cocos.cocos2d.extern"

-- opengl
require "cocos.cocos2d.Opengl"
require "cocos.cocos2d.OpenglConstants"

-- cocosdenshion
require "cocos.cocosdenshion.AudioEngine"

-- cocosstudio
require "cocos.cocostudio.CocoStudio"

-- ui
require "cocos.ui.GuiConstants"
require "cocos.ui.experimentalUIConstants"

-- extensions
require "cocos.extension.ExtensionConstants"

-- network
require "cocos.network.NetworkConstants"

-- Spine
require "cocos.spine.SpineConstants"

if CC_USE_DEPRECATED_API then
    require "cocos.deprecated"
    require "cocos.cocos2d.DrawPrimitives"

    -- Lua extensions
    require "cocos.cocos2d.bitExtend"

    -- CCLuaEngine
    require "cocos.cocos2d.DeprecatedCocos2dClass"
    require "cocos.cocos2d.DeprecatedCocos2dEnum"
    require "cocos.cocos2d.DeprecatedCocos2dFunc"
    require "cocos.cocos2d.DeprecatedOpenglEnum"

    -- register_cocostudio_module
    require "cocos.cocostudio.DeprecatedCocoStudioClass"
    require "cocos.cocostudio.DeprecatedCocoStudioFunc"

    -- register_cocosbuilder_module
    require "cocos.cocosbuilder.DeprecatedCocosBuilderClass"

    -- register_cocosdenshion_module
    require "cocos.cocosdenshion.DeprecatedCocosDenshionClass"
    require "cocos.cocosdenshion.DeprecatedCocosDenshionFunc"

    -- register_extension_module
    require "cocos.extension.DeprecatedExtensionClass"
    require "cocos.extension.DeprecatedExtensionEnum"
    require "cocos.extension.DeprecatedExtensionFunc"

    -- register_network_module
    require "cocos.network.DeprecatedNetworkClass"
    require "cocos.network.DeprecatedNetworkEnum"
    require "cocos.network.DeprecatedNetworkFunc"

    -- register_ui_moudle
    require "cocos.ui.DeprecatedUIEnum"
    require "cocos.ui.DeprecatedUIFunc"

    -- cocosbuilder
    require "cocos.cocosbuilder.CCBReaderLoad"
end


-- Cocos2d-Lua core functions
local c = cc or {}
c.loaded_packages = {}
local loaded_packages = c.loaded_packages

local function load_(...)
    local names = {...}
    assert(#names > 0, "cc.load() - invalid package names")

    local packages = {}
    for _, name in ipairs(names) do
        if not loaded_packages[name] then
            local packageName = string.format("packages.%s.init", name)
            local cls = require(packageName)
            assert(cls, string.format("cc.load() - package class \"%s\" load failed", packageName))
            loaded_packages[name] = cls
        end
        packages[#packages + 1] = loaded_packages[name]
    end
    return unpack(packages)
end
c.load = load_

local function bind_(target, ...)
    local names = {...}
    assert(#names > 0, "cc.bind() - invalid package names")

    load_(...)
    target.components_ = target.components_ or {}
    for _, name in ipairs(names) do
        if not target.components_[name] then
            local cls = loaded_packages[name]
            for __, depend in ipairs(cls.depends or {}) do
                if not target.components_[depend] then
                    bind_(target, depend)
                end
            end
            local component = cls:create()
            target.components_[name] = component
            component:bind(target)
        end
    end

    return target
end
c.bind = bind_

local function unbind_(target, ...)
    local names = {...}
    assert(#names > 0, "cc.unbind() - invalid package names")
    assert(type(target.components_) == "table", "cc.unbind() - target not binding components")

    for _, name in ipairs(names) do
        local component = target.components_[name]
        assert(component, string.format("cc.unbind() - component \"%s\" not found", tostring(name)))
        component:unbind(target)
        target.components_[name] = nil
    end

    return target
end
c.unbind = unbind_
