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

Lua 与 Objective-C 的交互接口

]]
local luaoc = {}

local callStaticMethod = LuaObjcBridge.callStaticMethod

--[[--

调用Objective-C类的接口。

只能调用Objective-C类的类方法

@param string className Objective-C类名
@param string methodName Objective-C类方法名
@param table args Objective-C类方法所需要的各种参数字典,key值为方法的参数名

@return boolean ok, mixed ret ok为是否调用成功, ok为true时,ret为Objective-C方法的返回值,ok为false时,ret为出错原因

]]
function luaoc.callStaticMethod(className, methodName, args)
    local ok, ret = callStaticMethod(className, methodName, args)
    if not ok then
        local msg = string.format("luaoc.callStaticMethod(\"%s\", \"%s\", \"%s\") - error: [%s] ",
                className, methodName, tostring(args), tostring(ret))
        if ret == -1 then
            printError(msg .. "INVALID PARAMETERS")
        elseif ret == -2 then
            printError(msg .. "CLASS NOT FOUND")
        elseif ret == -3 then
            printError(msg .. "METHOD NOT FOUND")
        elseif ret == -4 then
            printError(msg .. "EXCEPTION OCCURRED")
        elseif ret == -5 then
            printError(msg .. "INVALID METHOD SIGNATURE")
        else
            printError(msg .. "UNKNOWN")
        end
    end
    return ok, ret
end

return luaoc
