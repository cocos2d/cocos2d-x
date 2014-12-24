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

--------------------------------
-- @module init

--[[--

quick framework 初始化

载入 quick framework 预定义的常量、模块。

### 常量

在初始化框架之前，可以定义以下常量：

-   DEBUG: 设置框架的调试输出级别

    ```lua
    DEBUG = 0           -- 不输出任何调试信息（默认值）
    DEBUG = 1           -- 输出基本的调试信息
    DEBUG = 2           -- 输出详细的调试信息
    ```

-   DEBUG_FPS: 设置是否在画面中显示渲染帧率等信息

    ```lua
    DEBUG_FPS = false   -- 不显示（默认值）
    DEBUG_FPS = true    -- 显示
    ```

-   DEBUG_MEM: 设置是否输出内存占用信息

    ```lua
    DEBUG_MEM = false   -- 不输出（默认值）
    DEBUG_MEM = true    -- 每 10 秒输出一次
    ```

-   LOAD_DEPRECATED_API: 是否载入过时的 API 定义，默认为 false

-   DISABLE_DEPRECATED_WARNING: 使用过时的 API 时是否显示警告信息，默认为 true

-   USE_DEPRECATED_EVENT_ARGUMENTS: 是否使用过时的 Node 事件参数格式，默认为 false

<br />

### 自动载入的模块

框架初始化时，会自动载入以下基本模块：

-   debug: 调试接口
-   functions: 提供一组常用的函数，以及对 Lua 标准库的扩展
-   cocos2dx: 对 cocos2d-x C++ 接口的封装和扩展
-   device: 针对设备接口的扩展
-   transition: 与动作相关的接口
-   display: 创建场景、图像、动画的接口
-   filter: 具备过滤器渲染的 Sprite 接口
-   audio: 音乐和音效的接口
-   network: 网络相关的接口
-   crypto: 加密相关的接口
-   json: JSON 的编码和解码接口
-   luaj: 提供从 Lua 调用 Java 方法的接口（仅限 Android 平台）
-   luaoc: 提供从 Lua 调用 Objective-C 方法的接口（仅限 iOS 平台）
-   cc: quick 框架扩展的基础类和组件

]]

print("===========================================================")
print("              LOAD QUICK FRAMEWORK")
print("===========================================================")


if type(DEBUG) ~= "number" then DEBUG = 0 end
if type(DEBUG_FPS) ~= "boolean" then DEBUG_FPS = false end
if type(DEBUG_MEM) ~= "boolean" then DEBUG_MEM = false end
if type(LOAD_SHORTCODES_API) ~= "boolean" then LOAD_SHORTCODES_API = true end
if type(LOAD_DEPRECATED_API) ~= "boolean" then LOAD_DEPRECATED_API = false end
if type(DISABLE_DEPRECATED_WARNING) ~= "boolean" then DISABLE_DEPRECATED_WARNING = false end
if type(USE_DEPRECATED_EVENT_ARGUMENTS) ~= "boolean" then USE_DEPRECATED_EVENT_ARGUMENTS = false end

----

local CURRENT_MODULE_NAME = ...

cc = cc or {}
cc.PACKAGE_NAME = string.sub(CURRENT_MODULE_NAME, 1, -6)
cc.VERSION = "3.3"
cc.FRAMEWORK_NAME = "quick-cocos2d-x"

if cc.Node.removeTouchEvent then
    cc.bPlugin_ = true
end

require(cc.PACKAGE_NAME .. ".debug")
require(cc.PACKAGE_NAME .. ".functions")
require(cc.PACKAGE_NAME .. ".cocos2dx")

printInfo("")
printInfo("# DEBUG                        = "..DEBUG)
printInfo("#")

device     = require(cc.PACKAGE_NAME .. ".device")
transition = require(cc.PACKAGE_NAME .. ".transition")
display    = require(cc.PACKAGE_NAME .. ".display")
filter     = require(cc.PACKAGE_NAME .. ".filter")
audio      = require(cc.PACKAGE_NAME .. ".audio")
network    = require(cc.PACKAGE_NAME .. ".network")
crypto     = require(cc.PACKAGE_NAME .. ".crypto")

local cjson = require(cc.PACKAGE_NAME .. ".json")
if cjson then
    json = cjson
else
    require("cocos.cocos2d.json")
end

if device.platform == "android" then
    require(cc.PACKAGE_NAME .. ".platform.android")
elseif device.platform == "ios" then
    require(cc.PACKAGE_NAME .. ".platform.ios")
elseif device.platform == "mac" then
    require(cc.PACKAGE_NAME .. ".platform.mac")
end

require(cc.PACKAGE_NAME .. ".cc.init")

if LOAD_DEPRECATED_API then
    ui         = require(cc.PACKAGE_NAME .. ".ui")

    local dp = cc.PACKAGE_NAME .. ".deprecated."
    require(dp .. "deprecated_functions")
end

if LOAD_SHORTCODES_API then
    require(cc.PACKAGE_NAME .. ".shortcodes")
end

----

local sharedTextureCache = cc.Director:getInstance():getTextureCache()
local sharedDirector = cc.Director:getInstance()

if DEBUG_FPS then
    sharedDirector:setDisplayStats(true)
else
    sharedDirector:setDisplayStats(false)
end

if DEBUG_MEM then
    local sharedTextureCache = cc.Director:getInstance():getTextureCache()
    --[[--
    @ignore
    ]]
    local function showMemoryUsage()
        printInfo(string.format("LUA VM MEMORY USED: %0.2f KB", collectgarbage("count")))
        printInfo(sharedTextureCache:getCachedTextureInfo())
        printInfo("---------------------------------------------------")
    end
    sharedDirector:getScheduler():scheduleScriptFunc(showMemoryUsage, DEBUG_MEM_INTERVAL or 10.0, false)
end
