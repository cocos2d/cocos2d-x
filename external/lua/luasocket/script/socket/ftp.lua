-----------------------------------------------------------------------------
-- FTP support for the Lua language
-- LuaSocket toolkit.
-- Author: Diego Nehab
-----------------------------------------------------------------------------

-----------------------------------------------------------------------------
-- Declare module and import dependencies
-----------------------------------------------------------------------------
local base = _G
local table = require("table")
local string = require("string")
local math = require("math")
local socket = require("socket.socket")
local url = require("socket.url")
local tp = require("socket.tp")
local ltn12 = require("ltn12")
socket.ftp = {}
local _M = socket.ftp
-----------------------------------------------------------------------------
-- Program constants
-----------------------------------------------------------------------------
-- timeout in seconds before the program gives up on a connection
_M.TIMEOUT = 60
-- default port for ftp service
_M.PORT = 21
-- this is the default anonymous password. used when no password is
-- provided in url. should be changed to your e-mail.
_M.USER = "ftp"
_M.PASSWORD = "anonymous@anonymous.org"

-----------------------------------------------------------------------------
-- Low level FTP API
-----------------------------------------------------------------------------
local metat = { __index = {} }

function _M.open(server, port, create)
    local tp = socket.try(tp.connect(server, port or _M.PORT, _M.TIMEOUT, create))
    local f = base.setmetatable({ tp = tp }, metat)
    -- make sure everything gets closed in an exception
    f.try = socket.newtry(function() f:close() end)
    return f
end

function metat.__index:portconnect()
    self.try(self.server:settimeout(_M.TIMEOUT))
    self.data = self.try(self.server:accept())
    self.try(self.data:settimeout(_M.TIMEOUT))
end

function metat.__index:pasvconnect()
    self.data = self.try(socket.tcp())
    self.try(self.data:settimeout(_M.TIMEOUT))
    self.try(self.data:connect(self.pasvt.ip, self.pasvt.port))
end

function metat.__index:login(user, password)
    self.try(self.tp:command("user", user or _M.USER))
    local code, reply = self.try(self.tp:check{"2..", 331})
    if code == 331 then
        self.try(self.tp:command("pass", password or _M.PASSWORD))
        self.try(self.tp:check("2.."))
    end
    return 1
end

function metat.__index:pasv()
    self.try(self.tp:command("pasv"))
    local code, reply = self.try(self.tp:check("2.."))
    local pattern = "(%d+)%D(%d+)%D(%d+)%D(%d+)%D(%d+)%D(%d+)"
    local a, b, c, d, p1, p2 = socket.skip(2, string.find(reply, pattern))
    self.try(a and b and c and d and p1 and p2, reply)
    self.pasvt = {
        ip = string.format("%d.%d.%d.%d", a, b, c, d),
        port = p1*256 + p2
    }
    if self.server then
        self.server:close()
        self.server = nil
    end
    return self.pasvt.ip, self.pasvt.port
end

function metat.__index:port(ip, port)
    self.pasvt = nil
    if not ip then
        ip, port = self.try(self.tp:getcontrol():getsockname())
        self.server = self.try(socket.bind(ip, 0))
        ip, port = self.try(self.server:getsockname())
        self.try(self.server:settimeout(_M.TIMEOUT))
    end
    local pl = math.mod(port, 256)
    local ph = (port - pl)/256
    local arg = string.gsub(string.format("%s,%d,%d", ip, ph, pl), "%.", ",")
    self.try(self.tp:command("port", arg))
    self.try(self.tp:check("2.."))
    return 1
end

function metat.__index:send(sendt)
    self.try(self.pasvt or self.server, "need port or pasv first")
    -- if there is a pasvt table, we already sent a PASV command
    -- we just get the data connection into self.data
    if self.pasvt then self:pasvconnect() end
    -- get the transfer argument and command
    local argument = sendt.argument or
        url.unescape(string.gsub(sendt.path or "", "^[/\\]", ""))
    if argument == "" then argument = nil end
    local command = sendt.command or "stor"
    -- send the transfer command and check the reply
    self.try(self.tp:command(command, argument))
    local code, reply = self.try(self.tp:check{"2..", "1.."})
    -- if there is not a a pasvt table, then there is a server
    -- and we already sent a PORT command
    if not self.pasvt then self:portconnect() end
    -- get the sink, source and step for the transfer
    local step = sendt.step or ltn12.pump.step
    local readt = {self.tp.c}
    local checkstep = function(src, snk)
        -- check status in control connection while downloading
        local readyt = socket.select(readt, nil, 0)
        if readyt[tp] then code = self.try(self.tp:check("2..")) end
        return step(src, snk)
    end
    local sink = socket.sink("close-when-done", self.data)
    -- transfer all data and check error
    self.try(ltn12.pump.all(sendt.source, sink, checkstep))
    if string.find(code, "1..") then self.try(self.tp:check("2..")) end
    -- done with data connection
    self.data:close()
    -- find out how many bytes were sent
    local sent = socket.skip(1, self.data:getstats())
    self.data = nil
    return sent
end

function metat.__index:receive(recvt)
    self.try(self.pasvt or self.server, "need port or pasv first")
    if self.pasvt then self:pasvconnect() end
    local argument = recvt.argument or
        url.unescape(string.gsub(recvt.path or "", "^[/\\]", ""))
    if argument == "" then argument = nil end
    local command = recvt.command or "retr"
    self.try(self.tp:command(command, argument))
    local code,reply = self.try(self.tp:check{"1..", "2.."})
    if (code >= 200) and (code <= 299) then
        recvt.sink(reply)
        return 1
    end
    if not self.pasvt then self:portconnect() end
    local source = socket.source("until-closed", self.data)
    local step = recvt.step or ltn12.pump.step
    self.try(ltn12.pump.all(source, recvt.sink, step))
    if string.find(code, "1..") then self.try(self.tp:check("2..")) end
    self.data:close()
    self.data = nil
    return 1
end

function metat.__index:cwd(dir)
    self.try(self.tp:command("cwd", dir))
    self.try(self.tp:check(250))
    return 1
end

function metat.__index:type(type)
    self.try(self.tp:command("type", type))
    self.try(self.tp:check(200))
    return 1
end

function metat.__index:greet()
    local code = self.try(self.tp:check{"1..", "2.."})
    if string.find(code, "1..") then self.try(self.tp:check("2..")) end
    return 1
end

function metat.__index:quit()
    self.try(self.tp:command("quit"))
    self.try(self.tp:check("2.."))
    return 1
end

function metat.__index:close()
    if self.data then self.data:close() end
    if self.server then self.server:close() end
    return self.tp:close()
end

-----------------------------------------------------------------------------
-- High level FTP API
-----------------------------------------------------------------------------
local function override(t)
    if t.url then
        local u = url.parse(t.url)
        for i,v in base.pairs(t) do
            u[i] = v
        end
        return u
    else return t end
end

local function tput(putt)
    putt = override(putt)
    socket.try(putt.host, "missing hostname")
    local f = _M.open(putt.host, putt.port, putt.create)
    f:greet()
    f:login(putt.user, putt.password)
    if putt.type then f:type(putt.type) end
    f:pasv()
    local sent = f:send(putt)
    f:quit()
    f:close()
    return sent
end

local default = {
    path = "/",
    scheme = "ftp"
}

local function parse(u)
    local t = socket.try(url.parse(u, default))
    socket.try(t.scheme == "ftp", "wrong scheme '" .. t.scheme .. "'")
    socket.try(t.host, "missing hostname")
    local pat = "^type=(.)$"
    if t.params then
        t.type = socket.skip(2, string.find(t.params, pat))
        socket.try(t.type == "a" or t.type == "i",
            "invalid type '" .. t.type .. "'")
    end
    return t
end

local function sput(u, body)
    local putt = parse(u)
    putt.source = ltn12.source.string(body)
    return tput(putt)
end

_M.put = socket.protect(function(putt, body)
    if base.type(putt) == "string" then return sput(putt, body)
    else return tput(putt) end
end)

local function tget(gett)
    gett = override(gett)
    socket.try(gett.host, "missing hostname")
    local f = _M.open(gett.host, gett.port, gett.create)
    f:greet()
    f:login(gett.user, gett.password)
    if gett.type then f:type(gett.type) end
    f:pasv()
    f:receive(gett)
    f:quit()
    return f:close()
end

local function sget(u)
    local gett = parse(u)
    local t = {}
    gett.sink = ltn12.sink.table(t)
    tget(gett)
    return table.concat(t)
end

_M.command = socket.protect(function(cmdt)
    cmdt = override(cmdt)
    socket.try(cmdt.host, "missing hostname")
    socket.try(cmdt.command, "missing command")
    local f = open(cmdt.host, cmdt.port, cmdt.create)
    f:greet()
    f:login(cmdt.user, cmdt.password)
    f.try(f.tp:command(cmdt.command, cmdt.argument))
    if cmdt.check then f.try(f.tp:check(cmdt.check)) end
    f:quit()
    return f:close()
end)

_M.get = socket.protect(function(gett)
    if base.type(gett) == "string" then return sget(gett)
    else return tget(gett) end
end)

return _M
