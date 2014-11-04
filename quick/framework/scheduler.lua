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

全局计时器、计划任务

«该模块在框架初始化时不会自动载入» 

加载方式: local scheduler = require(cc.PACKAGE_NAME .. ".scheduler")

]]
local scheduler = {}

local sharedScheduler = cc.Director:getInstance():getScheduler()

--[[--

计划一个全局帧事件回调，并返回该计划的句柄。

全局帧事件在任何场景中都会执行，因此可以在整个应用程序范围内实现较为精确的全局计时器。

该函数返回的句柄用作 scheduler.unscheduleGlobal() 的参数，可以取消指定的计划。 

@param function 回调函数

@return mixed schedule句柄

]]
function scheduler.scheduleUpdateGlobal(listener)
    return sharedScheduler:scheduleScriptFunc(listener, 0, false)
end

--[[--

计划一个以指定时间间隔执行的全局事件回调，并返回该计划的句柄。 

~~~ lua

local function onInterval(dt)
end
 
-- 每 0.5 秒执行一次 onInterval()
local handle = scheduler.scheduleGlobal(onInterval, 0.5) 

~~~

@param function listener 回调函数
@param number interval 间隔时间

@return mixed schedule句柄

]]
function scheduler.scheduleGlobal(listener, interval)
    return sharedScheduler:scheduleScriptFunc(listener, interval, false)
end

--[[--

取消一个全局计划 

scheduler.unscheduleGlobal() 的参数就是 scheduler.scheduleUpdateGlobal() 和 scheduler.scheduleGlobal() 的返回值。

@param mixed schedule句柄

]]
function scheduler.unscheduleGlobal(handle)
    sharedScheduler:unscheduleScriptEntry(handle)
end

--[[--

计划一个全局延时回调，并返回该计划的句柄。

scheduler.performWithDelayGlobal() 会在等待指定时间后执行一次回调函数，然后自动取消该计划。

@param function listener 回调函数
@param number time 延迟时间

@return mixed schedule句柄

]]
function scheduler.performWithDelayGlobal(listener, time)
    local handle
    handle = sharedScheduler:scheduleScriptFunc(function()
        scheduler.unscheduleGlobal(handle)
        listener()
    end, time, false)
    return handle
end

return scheduler
