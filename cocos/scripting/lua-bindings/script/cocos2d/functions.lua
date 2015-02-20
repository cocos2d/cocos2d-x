--[[

Copyright (c) 2011-2015 chukong-inc.com

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

local tostring = tostring
local tonumber = tonumber
local assert = assert
local error = error
local type = type
local pairs = pairs
local ipairs = ipairs
local pcall = pcall
local ngx = ngx
local ngx_log = nil
if ngx then ngx_log = ngx.log end
local table_insert = table.insert
local table_remove = table.remove
local table_format = string.format
local string_upper = string.upper
local string_len = string.len
local string_rep = string.rep
local string_find = string.find
local string_gsub = string.gsub
local string_sub = string.sub
local string_byte = string.byte
local string_char = string.char
local math_floor = math.floor
local math_ceil = math.ceil
local math_random = math.random
local math_randomseed = math.randomseed
local io_open = io.open
local io_close = io.close
local os_time = os.time
local debug_traceback = debug.traceback
local debug_getlocal = debug.getlocal

-- internal function, advise you not to call it directly.
function printLog(tag, fmt, ...)
    if ngx_log then
        ngx_log(ngx[tag], table_format(tostring(fmt), ...))
        if tag == "ERR" then
            ngx_log(ngx.ERR, debug_traceback("", 2))
        end
        return
    end

    local t = {
        "[",
        string_upper(tostring(tag)),
        "] ",
        table_format(tostring(fmt), ...)
    }
    if tag == "ERR" then
        table_insert(t, debug_traceback("", 2))
    end
    print(table.concat(t))
end

function printError(fmt, ...)
    printLog("ERR", fmt, ...)
end

function printDebug(fmt, ...)
    if DEBUG < 3 then return end
    printLog("DEBUG", fmt, ...)
end

function printInfo(fmt, ...)
    if DEBUG < 2 then return end
    printLog("INFO", fmt, ...)
end

function printWarn(fmt, ...)
    if DEBUG < 1 then return end
    printLog("WARN", fmt, ...)
end

local function _dump_value(v)
    if type(v) == "string" then
        v = "\"" .. v .. "\""
    end
    return tostring(v)
end

function dump(value, desciption, nesting)
    if type(nesting) ~= "number" then nesting = 3 end

    local lookup = {}
    local result = {}
    local traceback = string.split(debug_traceback("", 2), "\n")
    print("dump from: " .. string.trim(traceback[3]))

    local function _dump(value, desciption, indent, nest, keylen)
        desciption = desciption or "<var>"
        local spc = ""
        if type(keylen) == "number" then
            spc = string_rep(" ", keylen - string_len(_dump_value(desciption)))
        end
        if type(value) ~= "table" then
            result[#result +1 ] = table_format("%s%s%s = %s", indent, _dump_value(desciption), spc, _dump_value(value))
        elseif lookup[tostring(value)] then
            result[#result +1 ] = table_format("%s%s%s = *REF*", indent, _dump_value(desciption), spc)
        else
            lookup[tostring(value)] = true
            if nest > nesting then
                result[#result +1 ] = table_format("%s%s = *MAX NESTING*", indent, _dump_value(desciption))
            else
                result[#result +1 ] = table_format("%s%s = {", indent, _dump_value(desciption))
                local indent2 = indent.."    "
                local keys = {}
                local keylen = 0
                local values = {}
                for k, v in pairs(value) do
                    keys[#keys + 1] = k
                    local vk = _dump_value(k)
                    local vkl = string_len(vk)
                    if vkl > keylen then keylen = vkl end
                    values[k] = v
                end
                table.sort(keys, function(a, b)
                    if type(a) == "number" and type(b) == "number" then
                        return a < b
                    else
                        return tostring(a) < tostring(b)
                    end
                end)
                for i, k in ipairs(keys) do
                    _dump(values[k], k, indent2, nest + 1, keylen)
                end
                result[#result +1] = table_format("%s}", indent)
            end
        end
    end
    _dump(value, desciption, "- ", 1)

    for i, line in ipairs(result) do
        print(line)
    end
end

function printf(fmt, ...)
    print(table_format(tostring(fmt), ...))
end

function checknumber(value, base)
    return tonumber(value, base) or 0
end

function checkint(value)
    return math.round(checknumber(value))
end

function checkbool(value)
    return (value ~= nil and value ~= false)
end

function checktable(value)
    if type(value) ~= "table" then value = {} end
    return value
end

function isset(hashtable, key)
    local t = type(hashtable)
    return (t == "table" or t == "userdata") and hashtable[key] ~= nil
end

local _setmetatableindex
_setmetatableindex = function(t, index)
    if type(t) == "userdata" then
        local peer = tolua.getpeer(t)
        if not peer then
            peer = {}
            tolua.setpeer(t, peer)
        end
        _setmetatableindex(peer, index)
    else
        local mt = getmetatable(t)
        if not mt then mt = {} end
        if not mt.__index then
            mt.__index = index
            setmetatable(t, mt)
        elseif mt.__index ~= index then
            _setmetatableindex(mt, index)
        end
    end
end
setmetatableindex = _setmetatableindex

function clone(object)
    local lookup = {}
    local function _copy(object)
        if type(object) ~= "table" then
            return object
        elseif lookup[object] then
            return lookup[object]
        end
        local newObject = {}
        lookup[object] = newObject
        for key, value in pairs(object) do
            newObject[_copy(key)] = _copy(value)
        end
        return setmetatable(newObject, getmetatable(object))
    end
    return _copy(object)
end

function class(classname, ...)
    local cls = {__cname = classname}

    local supers = {...}
    for _, super in ipairs(supers) do
        local superType = type(super)
        assert(superType == "nil" or superType == "table" or superType == "function",
            table_format("class() - create class \"%s\" with invalid super class type \"%s\"",
                classname, superType))

        if superType == "function" then
            assert(cls.__create == nil,
                table_format("class() - create class \"%s\" with more than one creating function",
                    classname));
            -- if super is function, set it to __create
            cls.__create = super
        elseif superType == "table" then
            if super[".isclass"] then
                -- super is native class
                assert(cls.__create == nil,
                    table_format("class() - create class \"%s\" with more than one creating function or native class",
                        classname));
                cls.__create = function() return super:create() end
            else
                -- super is pure lua class
                cls.__supers = cls.__supers or {}
                cls.__supers[#cls.__supers + 1] = super
                if not cls.super then
                    -- set first super pure lua class as class.super
                    cls.super = super
                end
            end
        else
            error(table_format("class() - create class \"%s\" with invalid super type",
                        classname), 0)
        end
    end

    cls.__index = cls
    if not cls.__supers or #cls.__supers == 1 then
        setmetatable(cls, {__index = cls.super})
    else
        setmetatable(cls, {__index = function(_, key)
            local supers = cls.__supers
            for i = 1, #supers do
                local super = supers[i]
                if super[key] then return super[key] end
            end
        end})
    end

    if not cls.ctor then
        -- add default constructor
        cls.ctor = function() end
    end
    cls.new = function(...)
        local instance
        if cls.__create then
            instance = cls.__create(...)
        else
            instance = {}
        end
        _setmetatableindex(instance, cls)
        instance.class = cls
        instance:ctor(...)
        return instance
    end
    cls.create = function(_, ...)
        return cls.new(...)
    end

    return cls
end

local _iskindof
_iskindof = function(cls, name)
    local __index = rawget(cls, "__index")
    if type(__index) == "table" and rawget(__index, "__cname") == name then return true end

    if rawget(cls, "__cname") == name then return true end
    local __supers = rawget(cls, "__supers")
    if not __supers then return false end
    for _, super in ipairs(__supers) do
        if _iskindof(super, name) then return true end
    end
    return false
end

function iskindof(obj, classname)
    local t = type(obj)
    if t ~= "table" and t ~= "userdata" then return false end

    local mt
    if t == "userdata" then
        if tolua.iskindof(obj, classname) then return true end
        mt = tolua.getpeer(obj)
    else
        mt = getmetatable(obj)
    end
    if mt then
        return _iskindof(mt, classname)
    end
    return false
end

function import(moduleName, currentModuleName)
    local currentModuleNameParts
    local moduleFullName = moduleName
    local offset = 1

    while true do
        if string_byte(moduleName, offset) ~= 46 then -- .
            moduleFullName = string_sub(moduleName, offset)
            if currentModuleNameParts and #currentModuleNameParts > 0 then
                moduleFullName = table.concat(currentModuleNameParts, ".") .. "." .. moduleFullName
            end
            break
        end
        offset = offset + 1

        if not currentModuleNameParts then
            if not currentModuleName then
                local n,v = debug_getlocal(3, 1)
                currentModuleName = v
            end

            currentModuleNameParts = string.split(currentModuleName, ".")
        end
        table_remove(currentModuleNameParts, #currentModuleNameParts)
    end

    return require(moduleFullName)
end

function handler(obj, method)
    return function(...)
        return method(obj, ...)
    end
end

function math.newrandomseed()
    math_randomseed(os_time())
    math_random()
    math_random()
    math_random()
    math_random()
end

function math.round(value)
    value = checknumber(value)
    return math_floor(value + 0.5)
end

function math.trunc(x)
    if x <= 0 then
        return math_ceil(x);
    end
    if math_ceil(x) == x then
        x = math_ceil(x);
    else
        x = math_ceil(x) - 1;
    end
    return x;
end

local _pi = math.pi
local _piDiv180 = _pi / 180
function math.angle2radian(angle)
    return angle * _piDiv180
end

local _piMul180 = _pi * 180
function math.radian2angle(radian)
    return radian / _piMul180
end

function io.exists(path)
    local file = io_open(path, "r")
    if file then
        io_close(file)
        return true
    end
    return false
end

function io.readfile(path)
    local file = io_open(path, "r")
    if file then
        local content = file:read("*a")
        io_close(file)
        return content
    end
    return nil
end

function io.writefile(path, content, mode)
    mode = mode or "w+b"
    local file = io_open(path, mode)
    if file then
        if file:write(content) == nil then return false end
        io_close(file)
        return true
    else
        return false
    end
end

function io.pathinfo(path)
    local pos = string_len(path)
    local extpos = pos + 1
    while pos > 0 do
        local b = string_byte(path, pos)
        if b == 46 then -- 46 = char "."
            extpos = pos
        elseif b == 47 then -- 47 = char "/"
            break
        end
        pos = pos - 1
    end

    local dirname = string_sub(path, 1, pos)
    local filename = string_sub(path, pos + 1)
    extpos = extpos - pos
    local basename = string_sub(filename, 1, extpos - 1)
    local extname = string_sub(filename, extpos)
    return {
        dirname = dirname,
        filename = filename,
        basename = basename,
        extname = extname
    }
end

function io.filesize(path)
    local size = false
    local file = io_open(path, "r")
    if file then
        local current = file:seek()
        size = file:seek("end")
        file:seek("set", current)
        io_close(file)
    end
    return size
end

function table.nums(t)
    local count = 0
    for k, v in pairs(t) do
        count = count + 1
    end
    return count
end

function table.keys(hashtable)
    local keys = {}
    for k, v in pairs(hashtable) do
        keys[#keys + 1] = k
    end
    return keys
end

function table.values(hashtable)
    local values = {}
    for k, v in pairs(hashtable) do
        values[#values + 1] = v
    end
    return values
end

function table.merge(dest, src)
    for k, v in pairs(src) do
        dest[k] = v
    end
end

function table.insertto(dest, src, begin)
    begin = checkint(begin)
    if begin <= 0 then
        begin = #dest + 1
    end

    local len = #src
    for i = 0, len - 1 do
        dest[i + begin] = src[i + 1]
    end
end

function table.indexof(array, value, begin)
    for i = begin or 1, #array do
        if array[i] == value then return i end
    end
    return false
end

function table.keyof(hashtable, value)
    for k, v in pairs(hashtable) do
        if v == value then return k end
    end
    return nil
end

function table.removebyvalue(array, value, removeall)
    local c, i, max = 0, 1, #array
    while i <= max do
        if array[i] == value then
            table_remove(array, i)
            c = c + 1
            i = i - 1
            max = max - 1
            if not removeall then break end
        end
        i = i + 1
    end
    return c
end

function table.map(t, fn)
    local n = {}
    for k, v in pairs(t) do
        n[k] = fn(v, k)
    end
    return n
end

function table.walk(t, fn)
    for k,v in pairs(t) do
        fn(v, k)
    end
end

function table.filter(t, fn)
    local n = {}
    for k, v in pairs(t) do
        if fn(v, k) then
            n[k] = v
        end
    end
    return n
end

function table.unique(t, bArray)
    local check = {}
    local n = {}
    local idx = 1
    for k, v in pairs(t) do
        if not check[v] then
            if bArray then
                n[idx] = v
                idx = idx + 1
            else
                n[k] = v
            end
            check[v] = true
        end
    end
    return n
end

local _htmlSpecialCharsTable = {}
_htmlSpecialCharsTable["&"] = "&amp;"
_htmlSpecialCharsTable["\""] = "&quot;"
_htmlSpecialCharsTable["'"] = "&#039;"
_htmlSpecialCharsTable["<"] = "&lt;"
_htmlSpecialCharsTable[">"] = "&gt;"
function string.htmlspecialchars(input)
    for k, v in pairs(_htmlSpecialCharsTable) do
        input = string_gsub(input, k, v)
    end
    return input
end

function string.restorehtmlspecialchars(input)
    for k, v in pairs(_htmlSpecialCharsTable) do
        input = string_gsub(input, v, k)
    end
    return input
end

function string.nl2br(input)
    return string_gsub(input, "\n", "<br />")
end

function string.text2html(input)
    input = string_gsub(input, "\t", "    ")
    input = string.htmlspecialchars(input)
    input = string_gsub(input, " ", "&nbsp;")
    input = string.nl2br(input)
    return input
end

function string.split(input, delimiter)
    input = tostring(input)
    delimiter = tostring(delimiter)
    if (delimiter=='') then return false end
    local pos,arr = 0, {}
    for st,sp in function() return string_find(input, delimiter, pos, true) end do
        table_insert(arr, string_sub(input, pos, st - 1))
        pos = sp + 1
    end
    table_insert(arr, string_sub(input, pos))
    return arr
end

function string.ltrim(input)
    return string_gsub(input, "^[ \t\n\r]+", "")
end

function string.rtrim(input)
    return string_gsub(input, "[ \t\n\r]+$", "")
end

function string.trim(input)
    input = string_gsub(input, "^[ \t\n\r]+", "")
    return string_gsub(input, "[ \t\n\r]+$", "")
end

function string.ucfirst(input)
    return string_upper(string_sub(input, 1, 1)) .. string_sub(input, 2)
end

local function urlencodechar(char)
    return "%" .. table_format("%02X", string_byte(char))
end
function string.urlencode(input)
    input = string_gsub(tostring(input), "\n", "\r\n")
    input = string_gsub(input, "([^%w%.%- ])", urlencodechar)
    return string_gsub(input, " ", "+")
end

local _checknumber = checknumber
function string.urldecode(input)
    input = string_gsub (input, "+", " ")
    input = string_gsub (input, "%%(%x%x)", function(h) return string_char(_checknumber(h, 16)) end)
    input = string_gsub (input, "\r\n", "\n")
    return input
end

function string.utf8len(input)
    local len  = string_len(input)
    local left = len
    local cnt  = 0
    local arr  = {0, 0xc0, 0xe0, 0xf0, 0xf8, 0xfc}
    while left ~= 0 do
        local tmp = string_byte(input, -left)
        local i   = #arr
        while arr[i] do
            if tmp >= arr[i] then
                left = left - i
                break
            end
            i = i - 1
        end
        cnt = cnt + 1
    end
    return cnt
end

function string.formatnumberthousands(num)
    local formatted = tostring(checknumber(num))
    local k
    while true do
        formatted, k = string_gsub(formatted, "^(-?%d+)(%d%d%d)", '%1,%2')
        if k == 0 then break end
    end
    return formatted
end
