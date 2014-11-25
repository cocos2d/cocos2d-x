--[[

Copyright (c) 2011-2014 chukong-inc.com

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

--[[--

初始化 cc 扩展

cc 扩展在 cocos2dx C++ API 和 quick 基本模块的基础上，提供了符合脚本风格的事件接口、组件架构等扩展。

]]

local CURRENT_MODULE_NAME = ...

-- init base classes
cc.Registry   = import(".Registry")
cc.GameObject = import(".GameObject")
cc.EventProxy = import(".EventProxy")
cc.Component  = import(".components.Component")

-- init components
local components = {
    "components.behavior.StateMachine",
    "components.behavior.EventProtocol",
    "components.ui.BasicLayoutProtocol",
    "components.ui.LayoutProtocol",
    "components.ui.DraggableProtocol",
}
for _, packageName in ipairs(components) do
    cc.Registry.add(import("." .. packageName, CURRENT_MODULE_NAME), packageName)
end

-- cc = cc.GameObject.extend()
local GameObject = cc.GameObject
local ccmt = {}
ccmt.__call = function(self, target)
    if target then
        return GameObject.extend(target)
    end
    printError("cc() - invalid target")
end
setmetatable(cc, ccmt)

-- load MVC
cc.mvc = import(".mvc.init")

-- load more library
cc.ui = import(".ui.init")

-- load extensions
cc.uiloader = import(".uiloader.init")
