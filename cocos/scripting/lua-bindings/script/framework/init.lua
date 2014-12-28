--[[

Copyright (c) 2011-2015 chukong-incc.com

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

]]

__G__TRACKBACK__ = function(msg)
    local msg = debug.traceback(msg, 3)
    print(msg)
    return msg
end

if type(DEBUG) ~= "number" then DEBUG = 0 end

-- load framework
printInfo("")
printInfo("# DEBUG                        = " .. DEBUG)
printInfo("#")

device  = require("cocos.framework.device")
display = require("cocos.framework.display")
audio   = require("cocos.framework.audio")

require("cocos.framework.extends.NodeEx")

-- Cocos2d-Lua core functions
cc.loaded_packages = {}
local loaded_packages = cc.loaded_packages

function cc.load(...)
    local names = {...}
    assert(#names > 0, "cc.load() - invalid package names")

    local packages = {}
    for _, name in ipairs(names) do
        assert(type(name) == "string", string.format("cc.load() - invalid package name \"%s\"", tostring(name)))
        if not loaded_packages[name] then
            local packageName = string.format("packages.%s.init", name)
            local cls = require(packageName)
            assert(cls, string.format("cc.load() - package class \"%s\" load failed", packageName))
            loaded_packages[name] = cls

            if DEBUG > 1 then
                printInfo("cc.load() - load module \"packages.%s.init\"", name)
            end
        end
        packages[#packages + 1] = loaded_packages[name]
    end
    return unpack(packages)
end

local load_ = cc.load
local bind_
bind_ = function(target, ...)
    local t = type(target)
    assert(t == "table" or t == "userdata", string.format("cc.bind() - invalid target, expected is object, actual is %s", t))
    local names = {...}
    assert(#names > 0, "cc.bind() - package names expected")

    load_(...)
    if not target.components_ then target.components_ = {} end
    for _, name in ipairs(names) do
        assert(type(name) == "string" and name ~= "", string.format("cc.bind() - invalid package name \"%s\"", name))
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
cc.bind = bind_

function cc.unbind(target, ...)
    if not target.components_ then return end

    local names = {...}
    assert(#names > 0, "cc.unbind() - invalid package names")

    for _, name in ipairs(names) do
        assert(type(name) == "string" and name ~= "", string.format("cc.unbind() - invalid package name \"%s\"", name))
        local component = target.components_[name]
        assert(component, string.format("cc.unbind() - component \"%s\" not found", tostring(name)))
        component:unbind(target)
        target.components_[name] = nil
    end
    return target
end

function cc.setmethods(target, component, methods)
    for _, name in ipairs(methods) do
        local method = component[name]
        target[name] = function(__, ...)
            return method(component, ...)
        end
    end
end

function cc.unsetmethods(target, methods)
    for _, name in ipairs(methods) do
        target[name] = nil
    end
end

-- export global variable
local __g = _G
cc.exports = {}
setmetatable(cc.exports, {
    __newindex = function(_, name, value)
        rawset(__g, name, value)
    end,

    __index = function(_, name)
        return rawget(__g, name)
    end
})

-- disable create unexpected global variable
function cc.disable_global()
    setmetatable(__g, {
        __newindex = function(_, name, value)
            error(string.format("USE \" cc.exports.%s = value \" INSTEAD OF SET GLOBAL VARIABLE", name), 0)
        end
    })
end

if CONFIG_DISABLE_GLOBAL then
    cc.disable_global()
end
