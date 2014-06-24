-------------------------------------------------------------------------------
-- Copyright (c) 2011-2012 Sierra Wireless and others.
-- All rights reserved. This program and the accompanying materials
-- are made available under the terms of the Eclipse Public License v1.0
-- which accompanies this distribution, and is available at
-- http://www.eclipse.org/legal/epl-v10.html
--
-- Contributors:
--     Sierra Wireless - initial API and implementation
-------------------------------------------------------------------------------
-- Debugger using DBGp protocol.
-------------------------------------------------------------------------------
-- The module returns a single init function which takes 6 parameters (IDEHOST, IDEPORT, IDEKEY, TRANSPORT, PLATFORM, WORKINGDIR).
--
-- IDEHOST: the host name or the ip address of the DBGP server (so your ide)
-- if HOST is nil, the DBGP_IDEHOST env var is used.
-- if the env var is nil, the default value '127.0.0.1' is used.
--
-- IDEPORT: the port of the DBGP server (must be configure in the IDE)
-- if PORT is nil, the DBGP_IDEPORT env var is used.
-- if the env var is nil, the default value '10000' is used.
--
-- IDEIDEKEY: a string which is used as session key
-- if IDEKEY is nil, the DBGP_IDEKEY env var is used.
-- if the env var is nil, the default value 'luaidekey' is used.
--
-- TRANSPORT: (advanced optional parameter) the module name of which implement the transport interface used to do the connection with the server.
-- by default the debugger use an  internal implementation based on luasocket, but if can not use it, you could implement or use another transport layer implementation.
-- if TRANSPORT is nil, the DBGP_TRANSPORT env var is used.
-- if the env var is nil, the default value 'debugger.transport.luasocket' is used : this is the default implementation based on luasocket.
--
-- PLATFORM: (advanced optional parameter) 'unix' or 'win32' string which define the kind of platform on which the program to debug is executed.
-- by default the debugger will try to guess it and surely success, if for some reasons it fails you could help it by precise the execution platform.
-- if PLATFORM is nil, the DBGP_PLATFORM env var is used.
-- if the env var is nil, the debugger will try to guess it.
--
-- WORKINGDIR: (advanced optional parameter) the working directory in which the program to debug is executed.
-- by default the debugger will try to guess it and surely success, if for some reasons it fails you could help it by precise the working directory.
-- if WORKINGDIR is nil, the DBGP_WORKINGDIR env var is used.
-- if the env var is nil, the debugger will try to guess it.
--
-------------------------------------------------------------------------------
-- Known Issues:
--   * Functions cannot be created using the debugger and then called in program because their environment is mapped directly to
--     a debugger internal structure which cannot be persisted (i.e. used outside of the debug_hook).
--   * The DLTK client implementation does not handle context for properties. As a workaround, the context is encoded into the
--     fullname attribute of each property and is used likewise in property_get commands. The syntax is "<context ID>|<full name>"
--   * Dynamic code (compiled with load or loadstring) is not handled (the debugger will step over it, like C code)
-- Design notes:
--   * The whole debugger state is kept in a (currently) unique session table in order to ease eventual adaptation to a multi-threaded
--     model, as DBGp needs one connection per thread.
--   * Full names of properties are base64 encoded because they can contain arbitrary data (spaces, escape characters, ...), this makes
--     command parsing munch easier and faster
--   * This debugger supports asynchronous commands: any command can be done at any time, but some of them (continuations) can lead to
--     inconsistent states. In addition, this have a quite big overhead (~66%), if performance is an issue, a custom command to disable
--     async mode could be done.
--   * All commands are implemented in table commands, see this comments on this table to additional details about commands implementation
--   * The environments in which are evaluated user code (property_* and eval commands, conditional breakpoints, ...) is a read/write
--     mapping of the local environment of a given stack level (can be accessed with variable names). See Context for additional details.
--     Context instantiation is pooled inside a debugging loop with ContextManager (each stack level is instantiated only once).
--   * Output redirection is done by redefining print and some values inside the io table. See "Output redirection handling" for details.
-- Todo list:
--   * Override I/O in init function instead of on module loading.
--   * Allow to break programatically (debugger.break()).
--   * Break-on-error feature (break if an error is thrown and there is no pcall in stack to handle it).
--   * Use new 5.2 facilities to provide informations about function (arguments names, vararg, ...)
--   * Allow to see ... content for vararg functions (5.2 only)
--   * Inspect LuaJIT C data (http://lua-users.org/lists/lua-l/2011-02/msg01012.html)-- /!\ This file is auto-generated. Do not alter manually /!\

--------------------------------------------------------------------------------
--  Submodules body
--------------------------------------------------------------------------------
--------------------------------------------------------------------------------
--  Module debugger.transport.apr
package.preload["debugger.transport.apr"] = function(...)
-------------------------------------------------------------------------------
-- Copyright (c) 2011-2012 Sierra Wireless and others.
-- All rights reserved. This program and the accompanying materials
-- are made available under the terms of the Eclipse Public License v1.0
-- which accompanies this distribution, and is available at
-- http://www.eclipse.org/legal/epl-v10.html
--
-- Contributors:
--     Sierra Wireless - initial API and implementation
-------------------------------------------------------------------------------
-- Apache Portable Runtime backend for DBGP debugger.
-------------------------------------------------------------------------------

local apr = require "apr"

-- base 64 wrapping
function b64_wrap(src)
  local t = {}
  local b64_src = mime.b64(src)
  for i=1, #b64_src, 76 do t[#t+1] = b64_src:sub(i, i+75).."\r\n" end
  return table.concat(t)
end

-- implements a subset of LuaSocket API using APR
local SOCKET_MT = {
  connect = function(self, address, port) return self.skt:connect(address, port) end,
  receive = function(self, n)             return self.skt:read(n) end, -- only numeric read is used
  send    = function(self, data)          return self.skt:write(data) end,
  close   = function(self)                return self.skt:close() end,
  settimeout = function(self, sec)
    if     sec == nil then self.skt:timeout_set(true)
    elseif sec == 0   then self.skt:timeout_set(false)
    else                   self.skt:timeout_set(math.floor(sec * 1000000)) end
  end
}
SOCKET_MT.__index = SOCKET_MT

return {
    create = function()
      local skt, err = apr.socket_create('tcp')
      if not skt then return nil, err end
      return setmetatable({skt = skt}, SOCKET_MT)
    end,
    sleep      = apr.sleep, -- exact same API as LuaSocket

    -- Base64 related functions
    --- Encodes a string into Base64 with line wrapping
    -- @param data (string) data to encode
    -- @return base64 encoded string
    b64 = function(data)
        t = {}
        local b64_data = apr.base64_encode(data)
        for i=1, #b64_data, 76 do t[#t+1] = b64_data:sub(i, i+75).."\r\n" end
        return table.concat(t)
    end,

    --- Encodes a string into Base64, without any extra parsing (wrapping, ...)
    -- @param data (string) data to encode
    -- @return decoded string
    rawb64 = apr.base64_encode,

    --- Decodes base64 data
    -- @param data (string) base64 encoded data
    -- @return decoded string
    unb64 = apr.base64_decode,
}

end
--------------------------------------------------------------------------------
-- End of moduledebugger.transport.apr
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
--  Module debugger.transport.luasocket
package.preload["debugger.transport.luasocket"] = function(...)
-------------------------------------------------------------------------------
-- Copyright (c) 2011-2012 Sierra Wireless and others.
-- All rights reserved. This program and the accompanying materials
-- are made available under the terms of the Eclipse Public License v1.0
-- which accompanies this distribution, and is available at
-- http://www.eclipse.org/legal/epl-v10.html
--
-- Contributors:
--     Sierra Wireless - initial API and implementation
-------------------------------------------------------------------------------
-- LuaSocket backend for DBGP debugger.
-------------------------------------------------------------------------------

-- in order to be as lightweight as possible with Luasocket, core API is used
-- directly (to no add yet another layer)

--FIXME: remove this hack as soon as luasocket officially support 5.2
if _VERSION == "Lua 5.2" then
  table.getn = function(t) return t and #t end
end

local socket = require "socket"
local mime   = require "mime"
local ltn12  = require "ltn12"
local reg = debug.getregistry()


return {
    create = socket.tcp,
    sleep  = socket.sleep,

    -- Base64 related functions
    --- Encodes a string into Base64 with line wrapping
    -- @param data (string) data to encode
    -- @return base64 encoded string
    b64 = function(data)
        local filter = ltn12.filter.chain(mime.encode("base64"), mime.wrap("base64"))
        local sink, output = ltn12.sink.table()
        ltn12.pump.all(ltn12.source.string(data), ltn12.sink.chain(filter, sink))
        return table.concat(output)
    end,

    --- Encodes a string into Base64, without any extra parsing (wrapping, ...)
    -- @param data (string) data to encode
    -- @return decoded string
    rawb64 = function(data)
        return (mime.b64(data)) -- first result of the low-level function is fine here
    end,

    --- Decodes base64 data
    -- @param data (string) base64 encoded data
    -- @return decoded string
    unb64 = function(data)
        return (mime.unb64(data)) -- first result of the low-level function is fine here
    end,
}

end
--------------------------------------------------------------------------------
-- End of moduledebugger.transport.luasocket
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
--  Module debugger.transport.luasocket_sched
package.preload["debugger.transport.luasocket_sched"] = function(...)
-------------------------------------------------------------------------------
-- Copyright (c) 2011-2012 Sierra Wireless and others.
-- All rights reserved. This program and the accompanying materials
-- are made available under the terms of the Eclipse Public License v1.0
-- which accompanies this distribution, and is available at
-- http://www.eclipse.org/legal/epl-v10.html
--
-- Contributors:
--     Sierra Wireless - initial API and implementation
-------------------------------------------------------------------------------
-- LuaSocket with LuaSched backend for DBGP debugger.
-------------------------------------------------------------------------------

-- As LuaShed totally hides blocking functions, this module MUST be loaded on the very start of the program
-- (before loading sched) to catch references to blocking functions.

local socketcore = require"socket.core"
local debug      = require "debug"
local reg = debug.getregistry()

local blockingcreate  = socketcore.tcp
local blockingsleep   = socketcore.sleep

local blockingconnect    = reg["tcp{master}"].__index.connect
local blockingreceive    = reg["tcp{client}"].__index.receive
local blockingsend       = reg["tcp{client}"].__index.send
local blockingsettimeout = reg["tcp{master}"].__index.settimeout
local blockingclose      = reg["tcp{master}"].__index.close

-- we cannot set a new metatable directly on socket object, so wrap it into a new table
-- and forward all calls.
local blockingtcp = {
  connect    = function(self, address, port) return blockingconnect(self.skt, address, port) end,
  receive    = function(self, n)             return blockingreceive(self.skt, n) end,
  send       = function(self, data)          return blockingsend(self.skt, data) end,
  settimeout = function(self, sec)           return blockingsettimeout(self.skt, sec) end,
  close      = function(self)                return blockingclose(self.skt) end,
}

blockingtcp.__index = blockingtcp

local mime  = require "mime"
local ltn12 = require "ltn12"

-- verify that the socket function are the real ones and not sched not blocking versions
assert(debug.getinfo(blockingcreate, "S").what == "C", "The debugger needs the real socket functions !")
-- cleanup the package.loaded table (socket.core adds socket field into it)
package.loaded.socket = nil

return {
    create = function() return setmetatable({ skt = blockingcreate() }, blockingtcp) end,
    sleep  = blockingsleep,

    -- Base64 related functions
    --- Encodes a string into Base64 with line wrapping
    -- @param data (string) data to encode
    -- @return base64 encoded string
    b64 = function(data)
        local filter = ltn12.filter.chain(mime.encode("base64"), mime.wrap("base64"))
        local sink, output = ltn12.sink.table()
        ltn12.pump.all(ltn12.source.string(data), ltn12.sink.chain(filter, sink))
        return table.concat(output)
    end,

    --- Encodes a string into Base64, without any extra parsing (wrapping, ...)
    -- @param data (string) data to encode
    -- @return decoded string
    rawb64 = function(data)
        return (mime.b64(data)) -- first result of the low-level function is fine here
    end,

    --- Decodes base64 data
    -- @param data (string) base64 encoded data
    -- @return decoded string
    unb64 = function(data)
        return (mime.unb64(data)) -- first result of the low-level function is fine here
    end,
}

end
--------------------------------------------------------------------------------
-- End of moduledebugger.transport.luasocket_sched
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
--  Module debugger.commands
package.preload["debugger.commands"] = function(...)
-------------------------------------------------------------------------------
-- Copyright (c) 2011-2012 Sierra Wireless and others.
-- All rights reserved. This program and the accompanying materials
-- are made available under the terms of the Eclipse Public License v1.0
-- which accompanies this distribution, and is available at
-- http://www.eclipse.org/legal/epl-v10.html
--
-- Contributors:
--     Sierra Wireless - initial API and implementation
-------------------------------------------------------------------------------
-- Commands handlers for DBGp protocol.
-------------------------------------------------------------------------------
-- Debugger command functions. Each function handle a different command.
-- A command function is called with 3 arguments
--   1. the debug session instance
--   2. the command arguments as table
--   3. the command data, if any
-- The result is either :
--   * true (or any value evaluated to true) : the debugger will resume the execution of the application (continuation command)
--   * false : only in async mode, the debugger WILL wait for further commands instead of continuing (typically, break command)
--   * nil/no return : in sync mode, the debugger will wait for another command. In async mode the debugger will continue the execution

local cowrap, coyield = coroutine.wrap, coroutine.yield
local debug = require "debug"

local core          = require "debugger.core"
local dbgp          = require "debugger.dbgp"
local util          = require "debugger.util"
local platform      = require "debugger.platform"
local introspection = require "debugger.introspection"
local context       = require "debugger.context"
local log = util.log

local M = { } -- command handlers table

--- Gets the coroutine behind an id
-- Throws errors on unknown identifiers
-- @param  coro_id  (string or nil) Coroutine identifier or nil (current coroutine)
-- @return Coroutine instance or nil (if coro_id was nil or if coroutine is the current coroutine)
local function get_coroutine(self, coro_id)
    if coro_id then
        local coro = dbgp.assert(399, core.active_coroutines.from_id[tonumber(coro_id)], "No such coroutine")
        dbgp.assert(399, coroutine.status(coro) ~= "dead", "Coroutine is dead")
        if coro ~= self.coro[1] then return util.ForeignThread(coro) end
    end
    return self.coro
end

M["break"] = function(self, args)
    self.state = "break"
    -- send response to previous command
    core.previous_context_response(self)
    -- and then response to break command itself
    dbgp.send_xml(self.skt, { tag = "response", attr = { command = "break", transaction_id = args.i, success = 1 } } )
    return false
end

function M.status(self, args)
    dbgp.send_xml(self.skt, { tag = "response", attr = {
        command = "status",
        reason = "ok",
        status = self.state,
        transaction_id = args.i } } )
end

function M.stop(self, args)
    dbgp.send_xml(self.skt, { tag = "response", attr = {
        command = "stop",
        reason = "ok",
        status = "stopped",
        transaction_id = args.i } } )
    self.skt:close()
    os.exit(1)
end

function M.feature_get(self, args)
    local name = args.n
    local response = util.features[name] or (not not M[name])
    dbgp.send_xml(self.skt, { tag = "response", attr = {
          command = "feature_get",
          feature_name = name,
          supported = response and "1" or "0",
          transaction_id = args.i },
        tostring(response) } )
end

function M.feature_set(self, args)
    local name, value = args.n, args.v
    local success = pcall(function() util.features[name] = value end)
    dbgp.send_xml(self.skt, { tag = "response", attr = {
        command = "feature_set",
        feature = name,
        success = success and 1 or 0,
        transaction_id = args.i
    } } )
end

function M.typemap_get(self, args)
    local function gentype(name, type, xsdtype)
        return { tag = "map", atts = { name = name, type = type, ["xsi:type"] = xsdtype } }
    end

    dbgp.send_xml(self.skt, { tag = "response", attr = {
            command = "typemap_get",
            transaction_id = args.i,
            ["xmlns:xsi"] = "http://www.w3.org/2001/XMLSchema-instance",
            ["xmlns:xsd"] = "http://www.w3.org/2001/XMLSchema",
        },
        gentype("nil", "null"),
        gentype("boolean", "bool", "xsd:boolean"),
        gentype("number", "float", "xsd:float"),
        gentype("string", "string", "xsd:string"),
        gentype("function", "resource"),
        gentype("userdata", "resource"),
        gentype("thread", "resource"),
        gentype("table", "hash"),
        gentype("sequence", "array"), -- artificial type to represent sequences (1-n continuous indexes)
        gentype("multival", "array"), -- used to represent return values
    } )
end

function M.run(self) return true end

function M.step_over(self)
    core.events.register("over")
    return true
end

function M.step_out(self)
    core.events.register("out")
    return true
end

function M.step_into(self)
    core.events.register("into")
    return true
end

function M.eval(self, args, data)
    log("DEBUG", "Going to eval "..data)
    local result, err, success
    local env = self.stack(self.coro, 0)
    -- first, try to load as expression
    -- DBGp does not support stack level here, see http://bugs.activestate.com/show_bug.cgi?id=81178
    local func, err = util.loadin("return "..data, env)

    -- if it is not an expression, try as statement (assignment, ...)
    if not func then
        func, err = util.loadin(data, env)
    end

    if func then
        success, result = pcall(function() return introspection.Multival(func()) end)
        if not success then err = result end
    end

    local response = { tag = "response", attr = { command = "eval", transaction_id = args.i } }
    if not err then
        local nresults = result.n
        if nresults == 1 then result = result[1] end

        -- store result for further use (property_*)
        -- TODO: this could be optimized: this is only used for Expressions view and totally useless for interactive console,
        --       so storing result or not could be set by an argument
        local idx
        if nresults > 0 then
            local cache = env[context.Context[-1]]
            idx = #cache + 1
            cache[idx] = result
        end

        -- As of Lua 5.1, the maximum stack size (and result count) is 8000, this limit is used to fit all results in one page
        response[1] = introspection.make_property(-1, result, idx or "", nil, 1, 8000, 0, nil)
        response.attr.success = 1
    else
        response.attr.success = 0
        response[1] = dbgp.make_error(206, err)
    end
    dbgp.send_xml(self.skt, response)
end

function M.breakpoint_set(self, args, data)
    if args.o and not core.breakpoints.hit_conditions[args.o] then dbgp.error(200, "Invalid hit_condition operator: "..args.o) end

    local filename, lineno = args.f, tonumber(args.n)
    local bp = {
        type = args.t,
        state = args.s or "enabled",
        temporary = args.r == "1", -- "0" or nil makes this property false
        hit_count = 0,
        filename = filename,
        lineno = lineno,
        hit_value = tonumber(args.h or 0),
        hit_condition = args.o or ">=",
    }

    if args.t == "conditional" then
        bp.expression = data
        -- the expression is compiled only once
        bp.condition = dbgp.assert(207, loadstring("return (" .. data .. ")"))
    elseif args.t ~= "line" then dbgp.error(201, "BP type " .. args.t .. " not yet supported") end

    local bpid = core.breakpoints.insert(bp)
    dbgp.send_xml(self.skt, { tag = "response", attr = { command = "breakpoint_set", transaction_id = args.i, state = bp.state, id = bpid } } )
end

function M.breakpoint_get(self, args)
    dbgp.send_xml(self.skt, { tag = "response",
                              attr = { command = "breakpoint_get", transaction_id = args.i },
                              dbgp.assert(205, core.breakpoints.get_xml(tonumber(args.d))) })
end

function M.breakpoint_list(self, args)
    local bps = { tag = "response", attr = { command = "breakpoint_list", transaction_id = args.i } }
    for id, bp in pairs(core.breakpoints.get()) do bps[#bps + 1] = core.breakpoints.get_xml(id) end
    dbgp.send_xml(self.skt, bps)
end

function M.breakpoint_update(self, args)
    local bp = core.breakpoints.get(tonumber(args.d))
    if not bp then dbgp.error(205, "No such breakpint "..args.d) end
    if args.o and not core.breakpoints.hit_conditions[args.o] then dbgp.error(200, "Invalid hit_condition operator: "..args.o) end

    local response = { tag = "response", attr = { command = "breakpoint_update", transaction_id = args.i } }
    bp.state = args.s or bp.state
    bp.lineno = tonumber(args.n or bp.lineno)
    bp.hit_value = tonumber(args.h or bp.hit_value)
    bp.hit_condition = args.o or bp.hit_condition
    dbgp.send_xml(self.skt, response)
end

function M.breakpoint_remove(self, args)
    local response = { tag = "response", attr = { command = "breakpoint_remove", transaction_id = args.i } }
    if not core.breakpoints.remove(tonumber(args.d)) then dbgp.error(205, "No such breakpint "..args.d) end
    dbgp.send_xml(self.skt, response)
end

function M.stack_depth(self, args)
    local depth = 0
    local coro = get_coroutine(self, args.o)
    for level = 0, math.huge do
        local info = coro:getinfo(level, "St")
        if not info then break end -- end of stack
        depth = depth + 1
        if info.istailcall then depth = depth + 1 end -- a 'fake' level is added in that case
        if info.what == "main" then break end -- levels below main chunk are not interesting
    end
    dbgp.send_xml(self.skt, { tag = "response", attr = { command = "stack_depth", transaction_id = args.i, depth = depth} } )
end

function M.stack_get(self, args) -- TODO: dynamic code
    -- special URIs to identify unreachable stack levels
    local what2uri = {
        tail = "tailreturn:/",
        C    = "ccode:/",
    }

    local function make_level(info, level)
        local attr = { level = level, where = info.name, type="file" }
        local uri = platform.get_uri(info.source)
        if uri and info.currentline then -- reachable level
            attr.filename = uri
            attr.lineno = info.currentline
        else
            attr.filename = what2uri[info.what] or "unknown:/"
            attr.lineno = -1
        end
        return { tag = "stack", attr = attr }
    end

    local node = { tag = "response", attr = { command = "stack_get", transaction_id = args.i} }
    local coro = get_coroutine(self, args.o)

    if args.d then
        local stack_level = tonumber(args.d)
        node[#node+1] = make_level(coro:getinfo(stack_level, "nSl"), stack_level)
    else
        for i=0, math.huge do
            local info = coro:getinfo(i, "nSlt")
            if not info then break end
            node[#node+1] = make_level(info, i)
            -- add a fake level of stack for tail calls (tells user that the function has not been called directly)
            if info.istailcall then
                node[#node+1] = { tag = "stack", attr = { level=i, type="file", filename="tailreturn:/", lineno=-1 } }
            end
            if info.what == "main" then break end -- levels below main chunk are not interesting
        end
    end

    dbgp.send_xml(self.skt, node)
end

--- Lists all active coroutines.
-- Returns a list of active coroutines with their id (an arbitrary string) to query stack and properties. The id is
-- guaranteed to be unique and stable for all coroutine life (they can be reused as long as coroutine exists).
-- Others commands such as stack_get or property_* commands takes an additional -o switch to query a particular cOroutine.
-- If the switch is not given, running coroutine will be used.
-- In case of error on coroutines (most likely coroutine not found or dead), an error 399 is thrown.
-- Note there is an important limitation due to Lua 5.1 coroutine implementation: you cannot query main "coroutine" from
-- another one, so main coroutine is not in returned list (this will change with Lua 5.2).
--
-- This is a non-standard command. The returned XML has the following strucuture:
--     <response command="coroutine_list" transaction_id="0">
--       <coroutine name="<some printtable name>" id="<coroutine id>" running="0|1" />
--       ...
--     </response>
function M.coroutine_list(self, args)
    local running = self.coro[1]
    local coroutines = { tag = "response", attr = { command = "coroutine_list", transaction_id = args.i } }
    -- as any operation on main coroutine will fail, it is not yet listed
    -- coroutines[1] = { name = "coroutine", attr = { id = 0, name = "main", running = (running == nil) and "1" or "0" } }
    for id, coro in pairs(core.active_coroutines.from_id) do
        if id ~= "n" then
            coroutines[#coroutines + 1] = { tag = "coroutine", attr = { id = id, name = tostring(coro), running = (coro == running) and "1" or "0" } }
        end
    end
    dbgp.send_xml(self.skt, coroutines)
end

function M.context_names(self, args)
    local coro = get_coroutine(self, args.o)
    local level = tonumber(args.d or 0)
    local info = coro:getinfo(level, "f") or dbgp.error(301, "No such stack level "..tostring(level))

    -- All contexts are always passed, even if empty. This is how DLTK expect context, what about others ?
    local contexts = {
        tag = "response", attr = { command = "context_names", transaction_id = args.i },
        { tag = "context", attr = { name = "Local",   id = 0 } },
        { tag = "context", attr = { name = "Upvalue", id = 2 } },
        { tag = "context", attr = { name = "Global",  id = 1 } },
    }

    dbgp.send_xml(self.skt, contexts)
end

function M.context_get(self, args)
    local cxt_num = tonumber(args.c or 0)
    local cxt_id = context.Context[cxt_num] or dbgp.error(302, "No such context: "..tostring(cxt_num))
    local level = tonumber(args.d or 0)
    local coro = get_coroutine(self, args.o)
    local cxt = self.stack(coro, level)

    local properties = { tag = "response", attr = { command = "context_get", transaction_id = args.i, context = context} }
    -- iteration over global is different (this could be unified in Lua 5.2 thanks to __pairs metamethod)
    for name, val in (cxt_num == 1 and next or getmetatable(cxt[cxt_id]).iterator), cxt[cxt_id], nil do
        -- the DBGp specification is not clear about the depth of a context_get, but a recursive get could be *really* slow in Lua
        properties[#properties + 1] = introspection.make_property(cxt_num, val, name, nil, 0, util.features.max_children, 0,
                                                    util.features.max_data, cxt_num ~= 1)
    end

    dbgp.send_xml(self.skt, properties)
end

-------------------------------------------------------------------------------
--  Property_* commands
-------------------------------------------------------------------------------
-- This in the environment in which properties are get or set.
-- It notably contain a collection of proxy table which handle transparentely get/set operations on special fields
-- and the cache of complex keys.
local property_evaluation_environment = {
    key_cache = introspection.key_cache,
    metatable = setmetatable({ }, {
        __index = function(self, tbl) return getmetatable(tbl) end,
        __newindex = function(self, tbl, mt) return setmetatable(tbl, mt) end,
    }),
    environment = util.eval_env,
}
-- to allows to be set as metatable
property_evaluation_environment.__index = property_evaluation_environment

function M.property_get(self, args)
    --TODO BUG ECLIPSE TOOLSLINUX-99 352316
    local cxt_num, name = assert(util.unb64(args.n):match("^(%-?%d+)|(.*)$"))
    cxt_num = tonumber(args.c or cxt_num)
    local cxt_id = context.Context[cxt_num] or dbgp.error(302, "No such context: "..tostring(cxt_num))
    local level = tonumber(args.d or 0)
    local coro = get_coroutine(self, args.o)
    local size = tonumber(args.m or util.features.max_data)
    if size < 0 then size = nil end -- call from property_value
    local page = tonumber(args.p or 0)
    local cxt = self.stack(coro, level)
    local chunk = dbgp.assert(206, util.loadin("return "..name, property_evaluation_environment))
    local prop = select(2, dbgp.assert(300, pcall(chunk, cxt[cxt_id])))
    local response = introspection.make_property(cxt_num, prop, name, name, util.features.max_depth, util.features.max_children, page, size)
    -- make_property is not able to flag special variables as such when they are at root of property
    -- special variables queries are in the form "<proxy name>[(...)[a][b]<...>]"
    -- TODO: such parsing is far from perfect
    if name:match("^[%w_]+%[.-%b[]%]$") == name then response.attr.type = "special" end
    dbgp.send_xml(self.skt, { tag = "response",
                              attr = { command = "property_get", transaction_id = args.i, context = context},
                              response } )
end

function M.property_value(self, args)
    args.m = -1
    M.property_get(self, args)
end

function M.property_set(self, args, data)
    local cxt_num, name = assert(util.unb64(args.n):match("^(%-?%d+)|(.*)$"))
    cxt_num = tonumber(args.c or cxt_num)
    local cxt_id = context.Context[cxt_num] or dbgp.error(302, "No such context: "..tostring(cxt_num))
    local level = tonumber(args.d or 0)
    local coro = get_coroutine(self, args.o)
    local cxt = self.stack(coro, level)

    -- evaluate the new value in the local context
    local value = select(2, dbgp.assert(206, pcall(dbgp.assert(206, util.loadin("return "..data, cxt)))))

    local chunk = dbgp.assert(206, util.loadin(name .. " = value", setmetatable({ value = value }, property_evaluation_environment)))
    dbgp.assert(206, pcall(chunk, cxt[cxt_id]))
    dbgp.send_xml(self.skt, { tag = "response", attr = { success = 1, transaction_id = args.i } } )
end

--TODO dynamic code handling
-- The DBGp specification is not clear about the line number meaning, this implementation is 1-based and numbers are inclusive
function M.source(self, args)
    local path
    if args.f then
        path = platform.get_path(args.f)
    else
        path = self.coro:getinfo(0, "S").source
        assert(path:sub(1,1) == "@")
        path = path:sub(2)
    end
    local file, err = io.open(path)
    if not file then dbgp.error(100, err, { success = 0 }) end
    -- Try to identify compiled files
    if file:read(1) == "\033" then dbgp.error(100, args.f.." is bytecode", { success = 0 }) end
    file:seek("set", 0)


    local srclines = { }
    local beginline, endline, currentline = tonumber(args.b or 0), tonumber(args.e or math.huge), 0
    for line in file:lines() do
        currentline = currentline + 1
        if currentline >= beginline and currentline <= endline then
            srclines[#srclines + 1] = line
        elseif currentline >= endline then break end
    end
    file:close()
    srclines[#srclines + 1] = "" -- to add a trailing \n

    dbgp.send_xml(self.skt, { tag = "response",
                              attr = { command = "source", transaction_id = args.i, success = 1},
                              util.b64(table.concat(srclines, "\n")) })
end

-- Factory for both stdout and stderr commands, change file descriptor in io
local function output_command_handler_factory(mode)
    return function(self, args)
        if args.c == "0" then -- disable
            io[mode] = io.base[mode]
        else
            io[mode] = setmetatable({ skt = self.skt, mode = mode }, args.c == "1" and core.copy_output or core.redirect_output)
        end
        dbgp.send_xml(self.skt, { tag = "response", attr = { command = mode, transaction_id = args.i, success = "1" } } )
    end
end

M.stdout = output_command_handler_factory("stdout")
M.stderr = output_command_handler_factory("stderr")


return M

end
--------------------------------------------------------------------------------
-- End of moduledebugger.commands
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
--  Module debugger.context
package.preload["debugger.context"] = function(...)
-------------------------------------------------------------------------------
-- Copyright (c) 2011-2012 Sierra Wireless and others.
-- All rights reserved. This program and the accompanying materials
-- are made available under the terms of the Eclipse Public License v1.0
-- which accompanies this distribution, and is available at
-- http://www.eclipse.org/legal/epl-v10.html
--
-- Contributors:
--     Sierra Wireless - initial API and implementation
-------------------------------------------------------------------------------
--  Context handling: allows to evaluate code snippets in the context of a function
-------------------------------------------------------------------------------

local M = { }

local dbgp = require "debugger.dbgp"
local util = require "debugger.util"

-- make unique object to access contexts
local LOCAL, UPVAL, GLOBAL, EVAL, STORE, HANDLE = {}, {}, {}, {}, {}, {}

local getglobals
if _VERSION == "Lua 5.1" then
    getglobals = function(f) return getfenv(f) end
elseif _VERSION == "Lua 5.2" then
    getglobals = function(f, cxt)
        -- 'global' environment: this is either the local _ENV or upvalue _ENV. A special case happen when a
        -- function does not reference any global variable: the upvalue _ENV may not exist at all. In this case,
        -- global environment is not relevant so it is fixed to an empty table. Another solution would be to set it
        -- to the environment from above stack level but it would require some overhead (especially if multiple
        -- levels must be instantiated)
        if     cxt[LOCAL][STORE]["_ENV"] then return cxt[LOCAL]["_ENV"]
        elseif cxt[UPVAL][STORE]["_ENV"] then return cxt[UPVAL]["_ENV"]
        else return { } end
    end
end

--- Captures variables for given stack level. The capture contains local, upvalues and global variables.
-- The capture can be seen as a proxy table to the stack level: any value can be queried or set no matter
-- it is a local or an upvalue.
-- The individual local and upvalues context are also available and can be queried and modified with indexed notation too.
-- These objects are NOT persistant and must not be used outside the debugger loop which instanciated them !
M.Context = {
    -- Context identifiers can be accessed by their DBGp context ID
    [0] = LOCAL,
    [1] = GLOBAL, -- DLTK internal ID for globals is 1
    [2] = UPVAL,
    -- EVAL is used to keep results from eval in cache in order to browse or modify them, results are stored as sequence
    [-1] = EVAL,
    STORE = STORE,

    -- gets a variable by name with correct handling of Lua scope chain
    -- the or chain does not work here beacause __index metamethod would raise an error instead of returning nil
    __index = function(self, k)
        if     self[LOCAL][STORE][k] then return self[LOCAL][k]
        elseif self[UPVAL][STORE][k] then return self[UPVAL][k]
        else return self[GLOBAL][k] end
    end,
    __newindex = function(self, k, v)
        if     self[LOCAL][STORE][k] then self[LOCAL][k] = v
        elseif self[UPVAL][STORE][k] then self[UPVAL][k] = v
        else self[GLOBAL][k] = v end
    end,

    -- debug only !!
    __tostring = function(self)
        local buf = { "Locals: \n" }
        for k,v in pairs(self[LOCAL][STORE]) do
            buf[#buf+1] = "\t"..tostring(k).."("..tostring(v)..")="..tostring(self[LOCAL][k]).."\n"
        end
        buf[#buf+1] = "Upvalues: \n"
        for k,v in pairs(self[UPVAL][STORE]) do
            buf[#buf+1] = "\t"..tostring(k).."("..tostring(v)..")="..tostring(self[UPVAL][k]).."\n"
        end
        return table.concat(buf)
    end,

    LocalContext = {
        __index = function(self, k)
            local index = self[STORE][k]
            if not index then error("The local "..tostring(k).." does not exists.") end
            local handle = self[HANDLE]
            return select(2, handle.coro:getlocal(handle.level, index))
        end,
        __newindex = function(self, k, v)
            local index = self[STORE][k]
            if index then
                local handle = self[HANDLE]
                handle.coro:setlocal(handle.level, index, v)
            else error("Cannot set local " .. k) end
        end,
        -- Lua 5.2 ready :)
        --__pairs = function(self) return getmetatable(self).iterator, self, nil end,
        iterator = function(self, prev)
            local key, index = next(self[STORE], prev)
            if key then return key, self[key] else return nil end
        end,
    },

    UpvalContext = {
        __index = function(self, k)
            local index = self[STORE][k]
            if not index then error("The local "..tostring(k).." does not exitsts.") end
            return select(2, debug.getupvalue(self[HANDLE], index))
        end,
        __newindex = function(self, k, v)
            local index = self[STORE][k]
            if index then debug.setupvalue(self[HANDLE], index, v)
            else error("Cannot set upvalue " .. k) end
        end,
        -- Lua 5.2 ready :)
        -- __pairs = function(self) return getmetatable(self).iterator, self, nil end,
        iterator = function(self, prev)
            local key, index = next(self[STORE], prev)
            if key then return key, self[key] else return nil end
        end,
    },

    --- Context constructor
    -- @param coro  (util.*Thread instance) coroutine to map to
    -- @param level (number) stack level do dump (script stack level)
    new = function(cls, coro, level)
        local locals, upvalues = {}, {}
        if level < 0 then dbgp.error(301, "No such stack level: "..tostring(level)) end
        local func = (coro:getinfo(level, "f") or dbgp.error(301, "No such stack level: "..tostring(level))).func

        -- local variables
        for i=1, math.huge do
            local name, val = coro:getlocal(level, i)
            if not name then break
            elseif name:sub(1,1) ~= "(" then -- skip internal values
                locals[name] = i
            end
        end

        -- upvalues
        for i=1, math.huge do
            local name, val = debug.getupvalue(func, i)
            if not name then break end
            upvalues[name] = i
        end

        locals = setmetatable({ [STORE] = locals, [HANDLE] = { level = level, coro = coro } }, cls.LocalContext)
        upvalues = setmetatable({ [STORE] = upvalues, [HANDLE] = func }, cls.UpvalContext)

        local result = setmetatable({ [LOCAL] = locals, [UPVAL] = upvalues, [EVAL] = {} }, cls)
        rawset(result, GLOBAL, getglobals(func, result))
        return result
    end,
}

--- Handle caching of all instantiated context.
-- Returns a function which takes 2 parameters: thread and stack level and returns the corresponding context. If this
-- context has been already queried there is no new instantiation. A ContextManager is valid only during the debug loop
-- on which it has been instantiated. References to a ContextManager must be lost after the end of debug loop (so
-- threads can be collected).
-- If a context cannot be instantiated, an 301 DBGP error is thrown.
function M.ContextManager()
    local cache = { }
    return function(thread, level)
        -- the real coroutine is used as key (not the wrapped instance as its unicity is not guaranteed)
        -- otherwise, true is used to identify current thread (as nil is not a valid table key)
        local key = thread[1] or true
        local thread_contexts = cache[key]
        if not thread_contexts then
            thread_contexts = { }
            cache[key] = thread_contexts
        end

        local context = thread_contexts[level]
        if not context then
            context = M.Context:new(thread, level)
            thread_contexts[level] = context
        end

        return context
    end
end

return M

end
--------------------------------------------------------------------------------
-- End of moduledebugger.context
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
--  Module debugger.dbgp
package.preload["debugger.dbgp"] = function(...)
-------------------------------------------------------------------------------
-- Copyright (c) 2011-2012 Sierra Wireless and others.
-- All rights reserved. This program and the accompanying materials
-- are made available under the terms of the Eclipse Public License v1.0
-- which accompanies this distribution, and is available at
-- http://www.eclipse.org/legal/epl-v10.html
--
-- Contributors:
--     Sierra Wireless - initial API and implementation
-------------------------------------------------------------------------------
-- DBGp protocol utility function (parsing, error handling, XML generation).
-------------------------------------------------------------------------------

local util = require "debugger.util"

local error, setmetatable, type, pairs, ipairs, tostring, tconcat =
      error, setmetatable, type, pairs, ipairs, tostring, table.concat

local M = { }

--- Parses the DBGp command arguments and returns it as a Lua table with key/value pairs.
-- For example, the sequence <code>-i 5 -j foo</code> will result in <code>{i=5, j=foo}</code>
-- @param cmd_args (string) sequence of arguments
-- @return table described above
function M.arg_parse(cmd_args)
    local args = {}
    for arg, val in cmd_args:gmatch("%-(%w) (%S+)") do
        args[arg] = val
    end
    return args
end

--- Parses a command line
-- @return commande name (string)
-- @retrun arguments (table)
-- @return data (string, optional)
function M.cmd_parse(cmd)
    local cmd_name, args, data
    if cmd:find("--", 1, true) then -- there is a data part
        cmd_name, args, data = cmd:match("^(%S+)%s+(.*)%s+%-%-%s*(.*)$")
        data = util.unb64(data)
    else
        cmd_name, args = cmd:match("^(%S+)%s+(.*)$")
    end
    return cmd_name, M.arg_parse(args), data
end

--- Returns the packet read from socket, or nil followed by an error message on errors.
function M.read_packet(skt)
    local size = {}
    while true do
        local byte, err = skt:receive(1)
        if not byte then return nil, err end
        if byte == "\000" then break end
        size[#size+1] = byte
    end
    return tconcat(size)
end

M.DBGP_ERR_METATABLE = {} -- unique object used to identify DBGp errors

--- Throws a correct DBGp error which result in a fine tuned error message to the server.
-- It is intended to be called into a command to make a useful error message, a standard Lua error
-- result in a code 998 error (internal debugger error).
-- @param code numerical error code
-- @param message message string (optional)
-- @param attr extra attributes to add to the response tag (optional)
function M.error(code, message, attr)
    error(setmetatable({ code = code, message = message, attr = attr or {} }, M.DBGP_ERR_METATABLE), 2)
end

--- Like core assert but throws a DBGp error if condition is not met.
-- @param code numerical error code thrown if condition is not met.
-- @param message condition to test
-- @param ... will be used as error message if test fails.
function M.assert(code, success, ...)
    if not success then M.error(code, (...)) end
    return success, ...
end

-- -----------------
-- Outgoing data
-- -----------------
local xmlattr_specialchars = { ['"'] = "&quot;", ["<"] = "&lt;", ["&"] = "&amp;" }
--- Very basic XML generator
-- Generates a XML string from a Lua Object Model (LOM) table.
-- See http://matthewwild.co.uk/projects/luaexpat/lom.html
function M.lom2str(xml)
    local pieces = { } -- string buffer

    local function generate(node)
        pieces[#pieces + 1] = "<"..node.tag
        pieces[#pieces + 1] = " "
        -- attribute ordering is not honored here
        for attr, val in pairs(node.attr or {}) do
            if type(attr) == "string" then
                pieces[#pieces + 1] = attr .. '="' .. tostring(val):gsub('["&<]', xmlattr_specialchars) .. '"'
                pieces[#pieces + 1] = " "
            end
        end
        pieces[#pieces] = nil -- remove the last separator (useless)

        if node[1] then
            pieces[#pieces + 1] = ">"
            for _, child in ipairs(node) do
                if type(child) == "table" then generate(child)
                else pieces[#pieces + 1] = "<![CDATA[" .. tostring(child) .. "]]>" end
            end
            pieces[#pieces + 1] = "</" .. node.tag .. ">"
        else
            pieces[#pieces + 1] = "/>"
        end
    end

    generate(xml)
    return tconcat(pieces)
end

function M.send_xml(skt, resp)
    if not resp.attr then resp.attr = {} end
    resp.attr.xmlns = "urn:debugger_protocol_v1"

    local data = '<?xml version="1.0" encoding="UTF-8" ?>\n'..M.lom2str(resp)
    util.log("DEBUG", "Send " .. data)
    skt:send(tostring(#data).."\000"..data.."\000")
end

--- Return an XML tag describing a debugger error, with an optional message
-- @param code (number) error code (see DBGp specification)
-- @param msg  (string, optional) textual description of error
-- @return table, suitable to be converted into XML
function M.make_error(code, msg)
    local elem = { tag = "error", attr = { code = code } }
    if msg then
        elem[1] = { tostring(msg), tag = "message" }
    end
    return elem
end

return M

end
--------------------------------------------------------------------------------
-- End of moduledebugger.dbgp
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
--  Module debugger.introspection
package.preload["debugger.introspection"] = function(...)
-- ----------------------------------------------------------------------------
-- Copyright (c) 2011-2012 Sierra Wireless and others.
-- All rights reserved. This program and the accompanying materials
-- are made available under the terms of the Eclipse Public License v1.0
-- which accompanies this distribution, and is available at
-- http://www.eclipse.org/legal/epl-v10.html
--
-- Contributors:
--     Julien Desgats - initial API and implementation
-- ----------------------------------------------------------------------------
-- Properties generation. Generate a LOM table with data from introspection.
-- ----------------------------------------------------------------------------

local debug = require "debug"
local platform = require "debugger.platform"
local util = require "debugger.util"

local tostring, type, assert, next, rawget, getmetatable, setmetatable, getfenv, select,         coyield,         cocreate,         costatus,         coresume,       sformat,      tconcat =
      tostring, type, assert, next, rawget, getmetatable, setmetatable, getfenv, select, coroutine.yield, coroutine.create, coroutine.status, coroutine.resume, string.format, table.concat

local MULTIVAL_MT = { __tostring = function() return "" end }
local probes = { }

-- ---------- --
-- Public API --
-- ---------- --

---
-- Introspection logic. This module implements Lua objects introspection and
-- generates a [DBGP](http://xdebug.org/docs-dbgp.php) compatible
-- [LOM](http://matthewwild.co.uk/projects/luaexpat/lom.html) data scructure.
-- @module debugger.introspection
local M = { }

---
-- Represent the actual data to send to the debugger.
-- Full XML specification can be found in [DBGP specification](http://xdebug.org/docs-dbgp.php#properties-variables-and-values).
-- Modifying properties after their generation is possible (as actual data serialization/sending is delayed)
-- but should be used with care. The XML structure uses the [LOM](http://matthewwild.co.uk/projects/luaexpat/lom.html)
-- format, refer to these documents to get more informations about fields.
--
-- In addition to table fields, it has an array part, `[1]` being the string representation (base64 encoded),
-- possibly followed by chlid properties (@{#DBGPProperty} themselves)
--
-- @field #string tag Always "property"
-- @field #table attr XML attributes, see DBGP specification
-- @type DBGPProperty

---
-- Inpectors table, contain all inspector functions.
-- Keys are either type names (`string`, `number`, ...) or metatables
-- that have a custom inspector attached.
-- @field [parent=#debugger.introspection] #table inspectors
M.inspectors = { }

---
-- Generate a DBGP property if needed. If data is in data pagination and recursion depth ranges,
-- and send a property to the debugger, otherwise drop current property.
-- @param #string name Property name (displayed in IDE)
-- @param #string typename Type name (displayed in IDE)
-- @param #string repr Value string representation
-- @param #DBGPProperty parent Parent property
-- @param #string fullname Lua expression used to get value back in further calls
-- @return #table description
-- @function [parent=#debugger.introspection] property
M.property = coyield

---
-- Adds a probe that will be called for every unknown table/userdata.
-- @param #function probe Inspector function to call.
-- @function [parent=#debugger.introspection] add_probe
M.add_probe = function(probe) probes[#probes + 1] = probe end

---
-- Inspects a Lua value by dispatching it to correct inspector. Inspector functions have the same API.
-- @param #string name Property name (will be displayed by IDE)
-- @param value Value to inspect
-- @param #table parent Parent property (LOM table of the )
-- @param #string fullname Expression used to retrieve `value` for further debugger calls
-- @return #DBGPProperty The inspected value as returned by @{debugger.introspection#debugger.introspection.property}.
-- @return #nil If the value has not been inspected
-- @function [parent=#debugger.introspection] inspect
M.inspect = function(name, value, parent, fullname)
    return (M.inspectors[type(value)] or M.inspectors.default)(name, value, parent, fullname)
end

-- ----------------- --
-- Utility functions --
-- ----------------- --

local function default_inspector(name, value, parent, fullname)
    return M.property(name, type(value), tostring(value), parent, fullname)
end

-- Inspects types that can have a metatable (table and userdata). Returns
--   1) generated property
--   2) boolean indicating whether a custom inspector has been called (in that case, do not process value any further)
local function metatable_inspector(name, value, parent, fullname)
    local mt = getmetatable(value)
    do
        -- find  by metatable
        local custom = M.inspectors[mt]
        if custom then return custom(name, value, parent, fullname), true end
        -- or else call probes
        for i=1, #probes do
          local prop = probes[i](name, value, parent, fullname)
          if prop then return prop, true end
        end
    end

    local prop = default_inspector(name, value, parent, fullname)
    if mt and prop then
        local mtprop = M.inspect("metatable", mt, prop, "metatable["..prop.attr.fullname.."]")
        if mtprop then mtprop.attr.type = "special" end
    end
    return prop, false
end

local function fancy_func_repr(f, info)
    local args = {}
    for i=1, info.nparams do
        args[i] = debug.getlocal(f, i)
    end

    if info.isvararg then
        args[#args+1] = "..."
    end

    return "function(" .. tconcat(args, ", ") .. ")"
end

--- Generate a name siutable for table index syntax
-- @param name Key name
-- @return #string A table index style index
-- @usage generate_printable_key('foo') => '["foo"]'
-- @usage generate_printable_key(12)    => '[12]'
-- @usage generate_printable_key({})    => '[table: 0x12345678]
-- @function [parent=#debugger.introspection] generate_printable_key
local function generate_printable_key(name)
    return "[" .. (type(name) == "string" and sformat("%q", name) or tostring(name)) .. "]"
end
M.generate_printable_key = generate_printable_key

-- Used to store complex keys (other than string and number) as they cannot be passed in text
-- For these keys, the resulting expression will not be the key itself but "key_cache[...]"
-- where key_cache must be mapped to this table to resolve key correctly.
M.key_cache = setmetatable({ n=0 }, { __mode = "v" })

local function generate_key(name)
    local tname = type(name)
    if tname == "string" then return sformat("%q", name)
    elseif tname == "number" or tname == "boolean" then return tostring(name)
    else -- complex key, use key_cache for lookup
        local i = M.key_cache.n
        M.key_cache[i] = name
        M.key_cache.n = i+1
        return "key_cache["..tostring(i).."]"
    end
end

--- Generate a usable fullname for a value.
-- Based on parent fullname and key value, return a valid Lua expression.
-- Key can be any value (as anything can act as table key). If it cannot
-- be serialized (only string, number and boolean can), it will be temporarly
-- stored in an internal cache to be retrieved later.
-- @param #string parent Parent fullname
-- @param key The child key to generate fullname for
-- @return #string A valid fullname expression
-- @function [parent=#debugger.introspection] make_fullname
local function make_fullname(parent, key)
    return parent .. "[" .. generate_key(key) .. "]"
end
M.make_fullname = make_fullname

-- ---------- --
-- Inspectors --
-- ---------- --

M.inspectors.number   = default_inspector
M.inspectors.boolean  = default_inspector
M.inspectors["nil"]   = default_inspector
M.inspectors.userdata = default_inspector
M.inspectors.thread   = default_inspector
M.inspectors.default  = default_inspector -- allows 3rd party inspectors to use the default inspector if needed

M.inspectors.userdata = function(name, value, parent, fullname)
    return (metatable_inspector(name, value, parent, fullname)) -- drop second return value
end

M.inspectors.string = function(name, value, parent, fullname)
    -- escape linebreaks as \n and not as \<0x0A> like %q does
    return M.property(name, "string", sformat("%q", value):gsub("\\\n", "\\n"), parent, fullname)
end

M.inspectors["function"] = function(name, value, parent, fullname)
    local info = debug.getinfo(value, "nSflu")
    local prop
    if info.what ~= "C" then
        -- try to create a fancy representation if possible
        local repr = info.nparams and fancy_func_repr(value, info) or tostring(value)
        if info.source:sub(1,1) == "@" then
            repr = repr .. "\n" .. platform.get_uri("@" .. info.source) .. "\n" .. tostring(info.linedefined)
        end
        prop = M.property(name, "function (Lua)", repr, parent, fullname)
    else
        prop = M.property(name, "function", tostring(value), parent, fullname)
    end
    if not prop then return nil end

    -- (5.1 only) environment is dumped only if it is different from global environment
    -- TODO: this is not a correct behavior: environment should be dumped if is different from current stack level one
    local fenv = getfenv and getfenv(value)
    if fenv and fenv ~= getfenv(0) then
        local fenvprop = M.inspect("environment", fenv, prop, "environment["..prop.attr.fullname.."]")
        if fenvprop then fenvprop.attr.type = "special" end
    end

    return prop
end


M.inspectors.table = function(name, value, parent, fullname)
    local prop, iscustom = metatable_inspector(name, value, parent, fullname)
    if not prop or iscustom then return prop end

    -- iterate over table values and detect arrays at the same time
    -- next is used to circumvent __pairs metamethod in 5.2
    local isarray, i = true, 1
    for k,v in next, value, nil do
        M.inspect(generate_printable_key(k), v, prop, make_fullname(fullname, k))
        -- array detection: keys should be accessible by 1..n keys
        isarray = isarray and rawget(value, i) ~= nil
        i = i + 1
    end
    -- empty tables are considered as tables
    if isarray and i > 1 then prop.attr.type = "sequence" end

    return prop
end

M.inspectors[MULTIVAL_MT] = function(name, value, parent, fullname)
    if value.n == 1 then
        -- return directly the value as result
        return M.inspect(name, value[1], parent, fullname)
    else
        -- wrap values inside a multival container
        local prop = M.property(name, "multival", "", parent, fullname)
        if not prop then return nil end
        for i=1, value.n do
            M.inspect(generate_printable_key(i), value[i], prop, fullname .. "[" .. i .. "]")
        end
        return prop
    end
end

-- ------------ --
-- Internal API --
-- ------------ --

-- Used to inspect "multival" or "vararg" values. The typical use is to pack function result(s) in a single
-- value to inspect. The Multival instances can be passed to make_property as a single value, they will be
-- correctly reported to debugger
function M.Multival(...)
    return setmetatable({ n=select("#", ...), ... }, MULTIVAL_MT)
end

--- Makes a property form a name/value pair (and fullname). This is an **internal** function, and should not be used by 3rd party inspectors.
-- @param #number cxt_id Context ID in which this value resides (workaround bug 352316)
-- @param value The value to debug
-- @param name The name associated with value, passed through tostring, so it can be anything
-- @param #string fullname A Lua expression to eval to get that property again (if nil, computed automatically)
-- @param #number depth The maximum property depth (recursive calls)
-- @param #number pagesize maximum children to include
-- @param #number page The page to generate (0 based)
-- @param #number size_limit Optional, if set, the maximum size of the string representation (in bytes)
-- @param #boolean safe_name If true, does not encode the name as table key
-- @return #DBGPProperty root property
-- @function [parent=#debugger.introspection] make_property
--TODO BUG ECLIPSE TOOLSLINUX-99 352316 : as a workaround, context is encoded into the fullname property
M.make_property = function(cxt_id, value, name, fullname, depth, pagesize, page, size_limit, safe_name)
    fullname = fullname or "(...)[" .. generate_key(name) .. "]"
    if not safe_name then name = generate_printable_key(name) end

    local generator = cocreate(function() return M.inspect(name, value, nil, fullname) end)
    local propstack = { }
    local rootnode
    local catchthis = true
    local nodestoskip = page * pagesize -- nodes to skip at root level to respect pagination
    local fullname_prefix = tostring(cxt_id).."|"

    while true do
        local succes, name, datatype, repr, parent, fullname = assert(coresume(generator, catchthis and propstack[#propstack] or nil))
        -- finalize and pop all finished properties
        while propstack[#propstack] ~= parent do
            local topop = propstack[#propstack]
            topop.attr.fullname = util.rawb64(fullname_prefix .. topop.attr.fullname)
            propstack[#propstack] = nil
        end
        if costatus(generator) == "dead" then break end

        local prop = {
          tag = "property",
          attr = {
            children = 0,
            pagesize = pagesize,
            page = parent and 0 or page,
            type = datatype,
            name = name,
            fullname = fullname,
            encoding = "base64",
            size = #repr,
          },
          util.b64(size_limit and repr:sub(1, size_limit) or repr)
        }

        if parent then
            parent.attr.children = 1
            parent.attr.numchildren = (parent.attr.numchildren or 0) + 1
            -- take pagination into accont to know if node needs to be catched
            catchthis = #parent <= pagesize and #propstack <= depth
            if parent == rootnode then
                catchthis = catchthis and nodestoskip <= 0
                nodestoskip = nodestoskip - 1
            end
            -- add node to tree
            if catchthis then
              parent[#parent + 1] = prop
              propstack[#propstack + 1] = prop
            end
        else
            rootnode = prop
            catchthis = true
            propstack[#propstack + 1] = prop
        end
    end

    return rootnode
end

return M

end
--------------------------------------------------------------------------------
-- End of moduledebugger.introspection
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
--  Module debugger.plugins.ffi
package.preload["debugger.plugins.ffi"] = function(...)
-------------------------------------------------------------------------------
-- Copyright (c) 2012-2013 Julien Desgats
-- All rights reserved. This program and the accompanying materials
-- are made available under the terms of the Eclipse Public License v1.0
-- which accompanies this distribution, and is available at
-- http://www.eclipse.org/legal/epl-v10.html
--
-- Contributors:
--     Julien Desgats - initial API and implementation
-------------------------------------------------------------------------------
-- LuaJIT cdata introspection library.
-------------------------------------------------------------------------------

-- known issues:
--  * references are de-referenced event if inspect_references is unset
--  * is automatic pointer and reference de-referencing is possible ?
--    (only for first item in case of arrays). Possible leads:
--    http://stackoverflow.com/questions/7134590/how-to-test-if-an-address-is-readable-in-linux-userspace-app
--    http://www.softwareverify.com/blog/?p=319
--  * when setting a value from Eclipse, the type is sometimes changed (e.g. int => number)

local introspection = require "debugger.introspection"
local reflect = require "debugger.plugins.ffi.reflect"
local ffi = require "ffi"

local tostring, tonumber, type, assert, sformat, tconcat = tostring, tonumber, type, assert, string.format, table.concat

local M = { }

--- Whether the reference types are inspected. Usually references should be safe (at least a bit
-- safer than pointers) so they are inspected. If a reference points to unsafe memory, the whole
-- program could crash !
-- If this feature is disabled, deeply nested C types will not be displayed correctly as evaluation
-- has a recursion limit, any further evaluation is done through references.
M.inspect_references = true

local function make_typename(refct)
    local t = refct.what
    if t == "int" then
        if refct.bool then t = "bool"
        else
            -- use C99 type notation to give more details about acutal type
            t = (refct.unsigned and "uint" or "int") .. tostring(refct.size * 8) .. "_t"
        end
    elseif t == "float" then
        -- assume IEEE754
        if     refct.size ==  8 then t = "double"
        elseif refct.size == 16 then t = "long double" -- not really sure this one is always true
        end
    elseif t == "struct" or t == "enum" or t == "union" then
        t = refct.name and (t .. " " .. refct.name) or ("anonymous "..t)
    elseif t == "func" then
        t = "function (FFI)"
    elseif t == "ptr" then
        t = make_typename(refct.element_type) .. "*"
    elseif t == "ref" then
        t = make_typename(refct.element_type) .. "&"
    elseif t == "field" then
        return make_typename(refct.type)
    elseif t == "bitfield" then
        t = (refct.type.unsigned and "unsigned" or "signed") .. ":" .. tostring(refct.size * 8)
        refct = refct.type
    end

    if refct.const then t = "const " .. t end
    if refct.volatile then t = "volatile " .. t end
    return t
end

-- if cdatakind is unknown, this one will be called
local default_inspector = introspection.inspectors.number
local inspect

-- recursion must be handled with some care: if we call regular introspection.inspect
-- we may create boxed references or Lua native objects which will be inspected as such
-- (leading to wrong type names).
local function recurse(name, value, parent, fullname, refct)
    if type(value) == "cdata" then
        return inspect(name, value, parent, fullname, refct)
    else
        local prop = introspection.inspect(name, value, parent, fullname)
        if prop then
            prop.attr.type = make_typename(refct)
        end
        return prop
    end
end

-- cdata specific inspectors
local inspectors = {
    struct = function(name, value, parent, fullname, refct)
        local prop = introspection.property(name, make_typename(refct), tostring(value), parent, fullname)

        -- inspect children, if needed
        if prop then
            for member in refct:members() do
                local mname = member.name
                recurse(mname, value[mname], prop, fullname .. sformat('[%q]', mname), member)
            end
        end
        return prop
    end,

    array = function(name, value, parent, fullname, refct)
        local etype = refct.element_type
        -- for VLAs, reflect does not give size
        local size = refct.size ~= "none" and refct.size or ffi.sizeof(value)
        size = size and (size / etype.size) -- we've got the byte size, not element count

        local typename = make_typename(etype)
        local prop = introspection.property(name, typename .. "[" .. (tostring(size) or "") .. "]", tostring(value), parent, fullname)

        if prop and size then
            for i=0, size-1 do
                local idx = "["..tostring(i).."]"
                recurse(idx, value[i], prop, fullname .. idx, etype)
            end
        end
        return prop
    end,

    func = function(name, value, parent, fullname, refct)
        local args = { }
        for arg in refct:arguments() do
            args[#args + 1] = make_typename(arg.type) .. " " .. arg.name
        end

        if refct.vararg then
            args[#args + 1] = "..."
        end

        local repr = make_typename(refct.return_type) .. " " .. refct.name .. "(" .. tconcat(args, ", ") .. ")"
        return introspection.property(name, make_typename(refct), repr, parent, fullname)
    end,

    enum = function(name, value, parent, fullname, refct)
        local repr = tonumber(value)
        -- try to convert numeric value into enum name
        --TODO: is there a faster method to make it ?
        for val in refct:values() do
            if val.value == repr then
                repr = val.name
                break
            end
        end

        return introspection.property(name, make_typename(refct), tostring(repr), parent, fullname)
    end,

    ref = function(name, value, parent, fullname, refct)
        -- this may be unsafe, see inspect_references setting
        local typename = make_typename(refct)
        if not M.inspect_references then
            return introspection.property(name, typename, tostring(value), parent, fullname)
        end

        local prop = recurse(name, value, parent, fullname, refct.element_type)
        if prop then
            prop.attr.type = typename
        end
        return prop
    end,

    int = function(name, value, parent, fullname, refct)
        return introspection.property(name, make_typename(refct), tostring(tonumber(value)), parent, fullname)
    end,

    -- pointers are too unsafe, do not inspect them
    ptr = function(name, value, parent, fullname, refct)
        return introspection.property(name, make_typename(refct), tostring(value), parent, fullname)
    end,
}

inspectors.union = inspectors.struct
inspectors.float = inspectors.int

-- for struct/union fields, the actual type is nested into the refct
inspectors.field = function(name, value, parent, fullname, refct)
    return inspect(name, value, parent, fullname, refct.type)
end
inspectors.bitfield = inspectors.field

inspect = function(name, value, parent, fullname, refct)
    -- inspect only values, not ctypes
    --FIXME: this cause references to be dereferenced and crash the process if they are wrong !
    if ffi.typeof(value) ~= value then
        refct = refct or reflect.typeof(value)
        return (inspectors[refct.what] or default_inspector)(name, value, parent, fullname, refct)
    end

    -- return a simple property for ctypes
    return introspection.property(name, "ctype", tostring(value), parent, fullname)
end

introspection.inspectors.cdata = inspect

return M

end
--------------------------------------------------------------------------------
-- End of moduledebugger.plugins.ffi
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
--  Module debugger.plugins.ffi.reflect
package.preload["debugger.plugins.ffi.reflect"] = function(...)
--[[ LuaJIT FFI reflection Library ]]--
--[[ Copyright (C) 2013 Peter Cawley <lua@corsix.org>. All rights reserved.

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
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
--]]
local ffi = require "ffi"
local bit = require "bit"
local reflect = {}

-- Relevant minimal definitions from lj_ctype.h
ffi.cdef [[
  typedef struct CType {
    uint32_t info;
    uint32_t size;
    uint16_t sib;
    uint16_t next;
    uint32_t name;
  } CType;

  typedef struct CTState {
    CType *tab;
    uint32_t top;
    uint32_t sizetab;
    void *L;
    void *g;
    void *finalizer;
    void *miscmap;
  } CTState;
]]

local function gc_str(gcref) -- Convert a GCref (to a GCstr) into a string
  if gcref ~= 0 then
    local ts = ffi.cast("uint32_t*", gcref)
    return ffi.string(ts + 4, ts[3])
  end
end

local function memptr(gcobj)
  return tonumber(tostring(gcobj):match"%x*$", 16)
end

-- Acquire a pointer to this Lua universe's CTState
local CTState do
  local co = coroutine.create(function()end) -- Any live coroutine will do.
  local uint32_ptr = ffi.typeof("uint32_t*")
  local G = ffi.cast(uint32_ptr, ffi.cast(uint32_ptr, memptr(co))[2])
  -- In global_State, `MRef ctype_state` is immediately before `GCRef gcroot[GCROOT_MAX]`.
  -- We first find (an entry in) gcroot by looking for a metamethod name string.
  local anchor = ffi.cast("uint32_t", ffi.cast("const char*", "__index"))
  local i = 0
  while math.abs(tonumber(G[i] - anchor)) > 64 do
    i = i + 1
  end
  -- We then work backwards looking for something resembling ctype_state.
  repeat
    i = i - 1
    CTState = ffi.cast("CTState*", G[i])
  until ffi.cast(uint32_ptr, CTState.g) == G
end

-- Acquire the CTState's miscmap table as a Lua variable
local miscmap do
  local t = {}; t[0] = t
  local tvalue = ffi.cast("uint32_t*", memptr(t))[2]
  ffi.cast("uint32_t*", tvalue)[ffi.abi"le" and 0 or 1] = ffi.cast("uint32_t", ffi.cast("uintptr_t", CTState.miscmap))
  miscmap = t[0]
end

-- Information for unpacking a `struct CType`.
-- One table per CT_* constant, containing:
-- * A name for that CT_
-- * Roles of the cid and size fields.
-- * Whether the sib field is meaningful.
-- * Zero or more applicable boolean flags.
local CTs = {[0] =
  {"int",
    "", "size", false,
    {0x08000000, "bool"},
    {0x04000000, "float", "subwhat"},
    {0x02000000, "const"},
    {0x01000000, "volatile"},
    {0x00800000, "unsigned"},
    {0x00400000, "long"},
  },
  {"struct",
    "", "size", true,
    {0x02000000, "const"},
    {0x01000000, "volatile"},
    {0x00800000, "union", "subwhat"},
    {0x00100000, "vla"},
  },
  {"ptr",
    "element_type", "size", false,
    {0x02000000, "const"},
    {0x01000000, "volatile"},
    {0x00800000, "ref", "subwhat"},
  },
  {"array",
    "element_type", "size", false,
    {0x08000000, "vector"},
    {0x04000000, "complex"},
    {0x02000000, "const"},
    {0x01000000, "volatile"},
    {0x00100000, "vla"},
  },
  {"void",
    "", "size", false,
    {0x02000000, "const"},
    {0x01000000, "volatile"},
  },
  {"enum",
    "type", "size", true,
  },
  {"func",
    "return_type", "nargs", true,
    {0x00800000, "vararg"},
    {0x00400000, "sse_reg_params"},
  },
  {"typedef", -- Not seen
    "element_type", "", false,
  },
  {"attrib", -- Only seen internally
    "type", "value", true,
  },
  {"field",
    "type", "offset", true,
  },
  {"bitfield",
    "", "offset", true,
    {0x08000000, "bool"},
    {0x02000000, "const"},
    {0x01000000, "volatile"},
    {0x00800000, "unsigned"},
  },
  {"constant",
    "type", "value", true,
    {0x02000000, "const"},
  },
  {"extern", -- Not seen
    "CID", "", true,
  },
  {"kw", -- Not seen
    "TOK", "size",
  },
}

-- Set of CType::cid roles which are a CTypeID.
local type_keys = {
  element_type = true,
  return_type = true,
  value_type = true,
  type = true,
}

-- Create a metatable for each CT.
local metatables = {
}
for _, CT in ipairs(CTs) do
  local what = CT[1]
  local mt = {__index = {}}
  metatables[what] = mt
end

-- Logic for merging an attribute CType onto the annotated CType.
local CTAs = {[0] =
  function(a, refct) error("TODO: CTA_NONE") end,
  function(a, refct) error("TODO: CTA_QUAL") end,
  function(a, refct)
    a = 2^a.value
    refct.alignment = a
    refct.attributes.align = a
  end,
  function(a, refct)
    refct.transparent = true
    refct.attributes.subtype = refct.typeid
  end,
  function(a, refct) refct.sym_name = a.name end,
  function(a, refct) error("TODO: CTA_BAD") end,
}

-- C function calling conventions (CTCC_* constants in lj_refct.h)
local CTCCs = {[0] =
  "cdecl",
  "thiscall",
  "fastcall",
  "stdcall",
}

local function refct_from_id(id) -- refct = refct_from_id(CTypeID)
  local ctype = CTState.tab[id]
  local CT_code = bit.rshift(ctype.info, 28)
  local CT = CTs[CT_code]
  local what = CT[1]
  local refct = setmetatable({
    what = what,
    typeid = id,
    name = gc_str(ctype.name),
  }, metatables[what])

  -- Interpret (most of) the CType::info field
  for i = 5, #CT do
    if bit.band(ctype.info, CT[i][1]) ~= 0 then
      if CT[i][3] == "subwhat" then
        refct.what = CT[i][2]
      else
        refct[CT[i][2]] = true
      end
    end
  end
  if CT_code <= 5 then
    refct.alignment = bit.lshift(1, bit.band(bit.rshift(ctype.info, 16), 15))
  elseif what == "func" then
    refct.convention = CTCCs[bit.band(bit.rshift(ctype.info, 16), 3)]
  end

  if CT[2] ~= "" then -- Interpret the CType::cid field
    local k = CT[2]
    local cid = bit.band(ctype.info, 0xffff)
    if type_keys[k] then
      if cid == 0 then
        cid = nil
      else
        cid = refct_from_id(cid)
      end
    end
    refct[k] = cid
  end

  if CT[3] ~= "" then -- Interpret the CType::size field
    local k = CT[3]
    refct[k] = ctype.size
    if k == "size" and bit.bnot(refct[k]) == 0 then
      refct[k] = "none"
    end
  end

  if what == "attrib" then
    -- Merge leading attributes onto the type being decorated.
    local CTA = CTAs[bit.band(bit.rshift(ctype.info, 16), 0xff)]
    if refct.type then
      local ct = refct.type
      ct.attributes = {}
      CTA(refct, ct)
      ct.typeid = refct.typeid
      refct = ct
    else
      refct.CTA = CTA
    end
  elseif what == "bitfield" then
    -- Decode extra bitfield fields, and make it look like a normal field.
    refct.offset = refct.offset + bit.band(ctype.info, 127) / 8
    refct.size = bit.band(bit.rshift(ctype.info, 8), 127) / 8
    refct.type = {
      what = "int",
      bool = refct.bool,
      const = refct.const,
      volatile = refct.volatile,
      unsigned = refct.unsigned,
      size = bit.band(bit.rshift(ctype.info, 16), 127),
    }
    refct.bool, refct.const, refct.volatile, refct.unsigned = nil
  end

  if CT[4] then -- Merge sibling attributes onto this type.
    while ctype.sib ~= 0 do
      local entry = CTState.tab[ctype.sib]
      if CTs[bit.rshift(entry.info, 28)][1] ~= "attrib" then break end
      if bit.band(entry.info, 0xffff) ~= 0 then break end
      local sib = refct_from_id(ctype.sib)
      sib:CTA(refct)
      ctype = entry
    end
  end

  return refct
end

local function sib_iter(s, refct)
  repeat
    local ctype = CTState.tab[refct.typeid]
    if ctype.sib == 0 then return end
    refct = refct_from_id(ctype.sib)
  until refct.what ~= "attrib" -- Pure attribs are skipped.
  return refct
end

local function siblings(refct)
  -- Follow to the end of the attrib chain, if any.
  while refct.attributes do
    refct = refct_from_id(refct.attributes.subtype or CTState.tab[refct.typeid].sib)
  end

  return sib_iter, nil, refct
end

metatables.struct.__index.members = siblings
metatables.func.__index.arguments = siblings
metatables.enum.__index.values = siblings

local function find_sibling(refct, name)
  local num = tonumber(name)
  if num then
    for sib in siblings(refct) do
      if num == 1 then
        return sib
      end
      num = num - 1
    end
  else
    for sib in siblings(refct) do
      if sib.name == name then
        return sib
      end
    end
  end
end

metatables.struct.__index.member = find_sibling
metatables.func.__index.argument = find_sibling
metatables.enum.__index.value = find_sibling

function reflect.typeof(x) -- refct = reflect.typeof(ct)
  return refct_from_id(tonumber(ffi.typeof(x)))
end

function reflect.getmetatable(x) -- mt = reflect.getmetatable(ct)
  return miscmap[-tonumber(ffi.typeof(x))]
end

return reflect
end
--------------------------------------------------------------------------------
-- End of moduledebugger.plugins.ffi.reflect
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
--  Module debugger.platform
package.preload["debugger.platform"] = function(...)
-------------------------------------------------------------------------------
-- Copyright (c) 2011-2012 Sierra Wireless and others.
-- All rights reserved. This program and the accompanying materials
-- are made available under the terms of the Eclipse Public License v1.0
-- which accompanies this distribution, and is available at
-- http://www.eclipse.org/legal/epl-v10.html
--
-- Contributors:
--     Sierra Wireless - initial API and implementation
-------------------------------------------------------------------------------
-- Platform/OS specific features and path handling.
-------------------------------------------------------------------------------

local url = require "debugger.url"
local util = require "debugger.util"

local M = { }

-- Execution plaform (could be win or unix)
-- Used to manage file path difference between the 2 platform
local platform = nil

-- keep all computed URIs in cache (as they are quite long to compute)
local uri_cache = { }

-- parse a normalized path and return a table of each segment
-- you could precise the path seperator.
local function split(path,sep)
  local t = {}
  for w in path:gmatch("[^"..(sep or "/").."]+")do
    table.insert(t, w)
  end
  return t
end

--- Returns a RFC2396 compliant URI for given source, or false if the mapping failed
local function get_abs_file_uri (source)
    local uri
    if source:sub(1,1) == "@" then -- real source file
        local sourcepath = source:sub(2)
        local normalizedpath = M.normalize(sourcepath)
        if not M.is_path_absolute(normalizedpath) then
            normalizedpath = M.normalize(M.base_dir .. "/" .. normalizedpath)
        end
        return M.to_file_uri(normalizedpath)
    else -- dynamic code, stripped bytecode, tail return, ...
        return false
    end
end

--FIXME: as result is cached, changes in package.path that modify the module name are missed
-- (mostly affect main module when Lua interpreter is launched with an absolute path)
local function get_module_uri (source)
    if source:sub(1,1) == "@" then -- real source file
        local uri
        local sourcepath = source:sub(2)
        local normalizedpath = M.normalize(sourcepath)
        local luapathtable = split (package.path, ";")
        local is_source_absolute = M.is_path_absolute(sourcepath)
        -- workarround : Add always the ?.lua entry to support
        -- the case where file was loaded by : "lua myfile.lua"
        table.insert(luapathtable,"?.lua")
        for i,var in ipairs(luapathtable) do
            -- avoid relative patterns matching absolute ones (e.g. ?.lua matches anything)
            if M.is_path_absolute(var) == is_source_absolute then
                local escaped = string.gsub(M.normalize(var),"[%^%$%(%)%%%.%[%]%*%+%-%?]",function(c) return "%"..c end)
                local pattern = string.gsub(escaped,"%%%?","(.+)")
                local modulename = string.match(normalizedpath,pattern)
                if modulename then
                    modulename = string.gsub(modulename,"/",".");
                    -- if we find more than 1 possible modulename return the shorter
                    if not uri or string.len(uri)>string.len(modulename) then
                        uri = modulename
                    end
                end
            end
        end
        if uri then return "module:///"..uri end
    end
    return false
end

function M.get_uri (source)
    -- search in cache
    local uri = uri_cache[source]
    if uri ~= nil then return uri end

    -- not found, create uri
    if util.features.uri == "module" then
        uri = get_module_uri(source)
        if not uri then uri = get_abs_file_uri (source) end
    else
        uri =  get_abs_file_uri (source)
    end

    uri_cache[source] = uri
    return uri
end

-- get path file from uri
function M.get_path (uri)
    local parsed_path = assert(url.parse(uri))
    if parsed_path.scheme == "file" then
        return M.to_path(parsed_path)
    else
        -- search in cache
        -- we should surely calculate it instead of find in cache
        for k,v in pairs(uri_cache)do
            if v == uri then
                assert(k:sub(1,1) == "@")
                return k:sub(2)
            end
        end
    end
end

function M.normalize(path)
    local parts = { }
    for w in path:gmatch("[^/]+") do
        if     w == ".." and #parts ~=0 then table.remove(parts)
        elseif w ~= "."  then table.insert(parts, w)
        end
    end
    return (path:sub(1,1) == "/" and "/" or "") .. table.concat(parts, "/")
end

function M.init(executionplatform,workingdirectory)
    --------------------------
    -- define current platform
    --------------------------
    -- check parameter
    if executionplatform and executionplatform ~= "unix" and executionplatform ~="win" then
        error("Unable to initialize platform module : execution platform should be 'unix' or 'win'.")
    end

    -- use parameter as current platform
    if executionplatform then
        platform = executionplatform
    else
        --if not define try to guess it.
        local function iswindows()
            local p = io.popen("echo %os%")
            if p then
                local result =p:read("*l")
                p:close()
                return result == "Windows_NT"
            end
            return false
        end

        local status, iswin = pcall(iswindows)
        if status and iswin then
            platform = "win"
        else
            platform = "unix"
        end
    end

    --------------------------
    -- platform dependent function
    --------------------------
    if platform == "unix" then
        -- The Path separator character
        M.path_sep = "/"

        -- TODO the way to get the absolute path can be wrong if the program loads new source files by relative path after a cd.
        -- currently, the directory is registered on start, this allows program to load any source file and then change working dir,
        -- which is the most common use case.
        M.base_dir = workingdirectory or os.getenv("PWD")

        -- convert parsed URL table to file path  for the current OS (see url.parse from luasocket)
        M.to_file_uri = function (path) return url.build{scheme="file",authority="", path=path} end

        -- return true is the path is absolute
        -- the path must be normalized
        M.is_path_absolute = function (path) return path:sub(1,1) == "/" end

        -- convert absolute normalized path file to uri
        M.to_path = function (parsed_url) return url.unescape(parsed_url.path) end
    else
        -- Implementations for Windows, see UNIX versions for documentation.
        M.path_sep = "\\"
        M.is_path_absolute = function (path) return path:match("^%a:/") end
        M.to_file_uri = function (path) return url.build{scheme="file",authority="", path="/"..path} end
        M.to_path = function (parsed_url) return url.unescape(parsed_url.path):gsub("^/", "") end

        local unixnormalize = M.normalize
        M.normalize = function(path) return unixnormalize(path:gsub("\\","/"):lower()) end

        -- determine base dir
        local function getworkingdirectory()
            local p = io.popen("echo %cd%")
            if p then
                local res = p:read("*l")
                p:close()
                return M.normalize(res)
            end
        end
        M.base_dir = workingdirectory or getworkingdirectory()

    end

    if not M.base_dir then error("Unable to determine the working directory.") end
end

return M

end
--------------------------------------------------------------------------------
-- End of moduledebugger.platform
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
--  Module debugger.util
package.preload["debugger.util"] = function(...)
-------------------------------------------------------------------------------
-- Copyright (c) 2011-2012 Sierra Wireless and others.
-- All rights reserved. This program and the accompanying materials
-- are made available under the terms of the Eclipse Public License v1.0
-- which accompanies this distribution, and is available at
-- http://www.eclipse.org/legal/epl-v10.html
--
-- Contributors:
--     Sierra Wireless - initial API and implementation
-------------------------------------------------------------------------------
-- Utility functions.
-------------------------------------------------------------------------------

local M = { }

-- log system
local LEVELS = { ERROR = 0, WARNING = 1, INFO = 2, DETAIL = 3, DEBUG = 4 }
local LOG_LEVEL = LEVELS.WARNING

-- Debugger features handling. Any feature can be get like any regular table, setting features result in
-- error for unknown or read-only features.
M.features = setmetatable({ }, {
    -- functions that format/validate data. If function is not provided, the feature cannot be modified.
    validators = {
        multiple_sessions = tonumber,
        encoding = tostring,
        max_children = tonumber,
        max_data = tonumber,
        max_depth = tonumber,
        show_hidden = tonumber,
        uri = tostring,
        log_level = function(level_name)
            -- set numerical index in internal var
            LOG_LEVEL = assert(LEVELS[level_name], "No such level")
            return level_name -- the displayed level is still the name
        end,
    },
    __index = {
        multiple_sessions = 0,
        encoding ="UTF-8",
        max_children = 32,
        max_data = 0xFFFF,
        max_depth = 1,
        show_hidden = 1,
        uri = "file",
        log_level = "WARNING",
        -- read only features
        language_supports_threads = 0,
        language_name = "Lua",
        language_version = _VERSION,
        protocol_version = 1,
        supports_async = 1,
        data_encoding = "base64",
        breakpoint_languages = "Lua",
        breakpoint_types = "line conditional",
    },
    __newindex = function(self, k, v)
        local mt = getmetatable(self)
        local values, validator = mt.__index, mt.validators[k]
        if values[k] == nil then error("No such feature " .. tostring(k)) end
        if not validator then error("The feature " .. tostring(k) .. " is read-only") end
        v = assert(validator(v))
        values[k] = v
    end,
})

-- Wraps debug function and an attached thread
-- also handle stack & coroutine management differencies between Lua versions
local getinfo, getlocal, setlocal = debug.getinfo, debug.getlocal, debug.setlocal

-- Foreign thread is used to debug paused thread
local ForeignThreadMT = {
    getinfo  = function(self, level, what)     return getinfo(self[1], level, what) end,
    getlocal = function(self, level, idx)      return getlocal(self[1], level, idx) end,
    setlocal = function(self, level, idx, val) return setlocal(self[1], level, idx, val) end,
}
ForeignThreadMT.__index = ForeignThreadMT
function M.ForeignThread(coro) return setmetatable({ coro }, ForeignThreadMT) end

-- Current thread is used to debug the thread that caused the hook
-- intended to be used *ONLY* in debug loop (executed in a new thread)
local CurrentThreadMT = {
    getinfo  = function(self, level, what)     return getinfo(self[1], level + 2, what) end,
    getlocal = function(self, level, idx)      return getlocal(self[1], level + 2, idx) end,
    setlocal = function(self, level, idx, val) return setlocal(self[1], level + 2, idx, val) end,
}
CurrentThreadMT.__index = CurrentThreadMT
function M.CurrentThread(coro) return setmetatable({ coro }, CurrentThreadMT) end


-- Some version dependant functions
if _VERSION == "Lua 5.1" then
    local loadstring, getfenv, setfenv, debug_getinfo, MainThread =
          loadstring, getfenv, setfenv, debug.getinfo, nil

    -- in 5.1 "t" flag does not exist and trigger an error so remove it from what
    CurrentThreadMT.getinfo = function(self, level, what) return getinfo(self[1], level + 2, what:gsub("t", "", 1)) end
    ForeignThreadMT.getinfo = function(self, level, what) return getinfo(self[1], level, what:gsub("t", "", 1)) end

    -- when we're forced to start debug loop on top of program stack (when on main coroutine)
    -- this requires some hackery to get right stack level

    -- Fallback method to inspect running thread (only for main thread in 5.1 or for conditional breakpoints)
    --- Gets a script stack level with additional debugger logic added
    -- @param l (number) stack level to get for debugged script (0 based)
    -- @return real Lua stack level suitable to be passed through deubg functions
    local function get_script_level(l)
        local hook = debug.gethook()
        for i=2, math.huge do
            if assert(debug.getinfo(i, "f")).func == hook then
                return i + l -- the script to level is just below, but because of the extra call to this function, the level is ok for callee
            end
        end
    end

    if rawget(_G, "jit") then
        MainThread = {
            [1] = "main", -- as the raw thread object is used as table keys, provide a replacement.
            -- LuaJIT completely eliminates tail calls from stack, so get_script_level retunrs wrong result in this case
            getinfo  = function(self, level, what)     return getinfo(get_script_level(level) - 1, what:gsub("t", "", 1)) end,
            getlocal = function(self, level, idx)      return getlocal(get_script_level(level) - 1, idx) end,
            setlocal = function(self, level, idx, val) return setlocal(get_script_level(level) - 1, idx, val) end,
        }
    else
        MainThread = {
            [1] = "main",
            getinfo  = function(self, level, what)     return getinfo(get_script_level(level) , what:gsub("t", "", 1)) end,
            getlocal = function(self, level, idx)      return getlocal(get_script_level(level), idx) end,
            setlocal = function(self, level, idx, val) return setlocal(get_script_level(level), idx, val) end,
        }
    end



    -- If the VM is vanilla Lua 5.1 or LuaJIT 2 without 5.2 compatibility, there is no way to get a reference to
    -- the main coroutine, so fall back to direct mode: the debugger loop is started on the top of main thread
    -- and the actual level is recomputed each time
    local oldCurrentThread = M.CurrentThread
    M.CurrentThread = function(coro) return coro and oldCurrentThread(coro) or MainThread end

    -- load a piece of code alog with its environment
    function M.loadin(code, env)
        local f = loadstring(code)
        return f and setfenv(f, env)
    end

    -- table that maps [gs]et environment to index
    M.eval_env = setmetatable({ }, {
        __index = function(self, func) return getfenv(func) end,
        __newindex = function(self, func, env) return setfenv(func, env) end,
    })
elseif _VERSION == "Lua 5.2" then
    local load, debug_getinfo = load, debug.getinfo
    function M.getinfo(coro, level, what)
        if coro then return debug_getinfo(coro, level, what)
        else return debug_getinfo(level + 1, what) end
    end

    function M.loadin(code, env) return load(code, nil, nil, env) end

    -- no eval_env for 5.2 as functions does not have environments anymore
end

-- ----------------------------------------------------------------------------
-- Bare minimal log system.
-- ----------------------------------------------------------------------------
function M.log(level, msg, ...)
    if (LEVELS[level] or -1) > LOG_LEVEL then return end
    if select("#", ...) > 0 then msg = msg:format(...) end
    io.base.stderr:write(string.format("DEBUGGER\t%s\t%s\n", level, msg))
end

return M

end
--------------------------------------------------------------------------------
-- End of moduledebugger.util
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
--  Module debugger.url
package.preload["debugger.url"] = function(...)
-----------------------------------------------------------------------------
-- URI parsing, composition and relative URL resolution
-- LuaSocket toolkit.
-- Author: Diego Nehab
-- RCS ID: $Id: url.lua,v 1.38 2006/04/03 04:45:42 diego Exp $
-----------------------------------------------------------------------------

-----------------------------------------------------------------------------
-- Declare module
-----------------------------------------------------------------------------
local string = require("string")
local base = _G
local table = require("table")

local _ENV = { }
if setfenv then setfenv(1, _ENV) end

-----------------------------------------------------------------------------
-- Module version
-----------------------------------------------------------------------------
_VERSION = "URL 1.0.1"

-----------------------------------------------------------------------------
-- Encodes a string into its escaped hexadecimal representation
-- Input
--   s: binary string to be encoded
-- Returns
--   escaped representation of string binary
-----------------------------------------------------------------------------
function escape(s)
    return string.gsub(s, "([^A-Za-z0-9_])", function(c)
        return string.format("%%%02x", string.byte(c))
    end)
end

-----------------------------------------------------------------------------
-- Protects a path segment, to prevent it from interfering with the
-- url parsing.
-- Input
--   s: binary string to be encoded
-- Returns
--   escaped representation of string binary
-----------------------------------------------------------------------------
local function make_set(t)
	local s = {}
	for i,v in base.ipairs(t) do
		s[t[i]] = 1
	end
	return s
end

-- these are allowed withing a path segment, along with alphanum
-- other characters must be escaped
local segment_set = make_set {
    "-", "_", ".", "!", "~", "*", "'", "(",
	")", ":", "@", "&", "=", "+", "$", ",",
}

local function protect_segment(s)
	return string.gsub(s, "([^A-Za-z0-9_])", function (c)
		if segment_set[c] then return c
		else return string.format("%%%02x", string.byte(c)) end
	end)
end

-----------------------------------------------------------------------------
-- Encodes a string into its escaped hexadecimal representation
-- Input
--   s: binary string to be encoded
-- Returns
--   escaped representation of string binary
-----------------------------------------------------------------------------
function unescape(s)
    return string.gsub(s, "%%(%x%x)", function(hex)
        return string.char(base.tonumber(hex, 16))
    end)
end

-----------------------------------------------------------------------------
-- Builds a path from a base path and a relative path
-- Input
--   base_path
--   relative_path
-- Returns
--   corresponding absolute path
-----------------------------------------------------------------------------
local function absolute_path(base_path, relative_path)
    if string.sub(relative_path, 1, 1) == "/" then return relative_path end
    local path = string.gsub(base_path, "[^/]*$", "")
    path = path .. relative_path
    path = string.gsub(path, "([^/]*%./)", function (s)
        if s ~= "./" then return s else return "" end
    end)
    path = string.gsub(path, "/%.$", "/")
    local reduced
    while reduced ~= path do
        reduced = path
        path = string.gsub(reduced, "([^/]*/%.%./)", function (s)
            if s ~= "../../" then return "" else return s end
        end)
    end
    path = string.gsub(reduced, "([^/]*/%.%.)$", function (s)
        if s ~= "../.." then return "" else return s end
    end)
    return path
end

-----------------------------------------------------------------------------
-- Parses a url and returns a table with all its parts according to RFC 2396
-- The following grammar describes the names given to the URL parts
-- <url> ::= <scheme>://<authority>/<path>;<params>?<query>#<fragment>
-- <authority> ::= <userinfo>@<host>:<port>
-- <userinfo> ::= <user>[:<password>]
-- <path> :: = {<segment>/}<segment>
-- Input
--   url: uniform resource locator of request
--   default: table with default values for each field
-- Returns
--   table with the following fields, where RFC naming conventions have
--   been preserved:
--     scheme, authority, userinfo, user, password, host, port,
--     path, params, query, fragment
-- Obs:
--   the leading '/' in {/<path>} is considered part of <path>
-----------------------------------------------------------------------------
function parse(url, default)
    -- initialize default parameters
    local parsed = {}
    for i,v in base.pairs(default or parsed) do parsed[i] = v end
    -- empty url is parsed to nil
    if not url or url == "" then return nil, "invalid url" end
    -- remove whitespace
    -- url = string.gsub(url, "%s", "")
    -- get fragment
    url = string.gsub(url, "#(.*)$", function(f)
        parsed.fragment = f
        return ""
    end)
    -- get scheme
    url = string.gsub(url, "^([%w][%w%+%-%.]*)%:",
        function(s) parsed.scheme = s; return "" end)
    -- get authority
    url = string.gsub(url, "^//([^/]*)", function(n)
        parsed.authority = n
        return ""
    end)
    -- get query stringing
    url = string.gsub(url, "%?(.*)", function(q)
        parsed.query = q
        return ""
    end)
    -- get params
    url = string.gsub(url, "%;(.*)", function(p)
        parsed.params = p
        return ""
    end)
    -- path is whatever was left
    if url ~= "" then parsed.path = url end
    local authority = parsed.authority
    if not authority then return parsed end
    authority = string.gsub(authority,"^([^@]*)@",
        function(u) parsed.userinfo = u; return "" end)
    authority = string.gsub(authority, ":([^:]*)$",
        function(p) parsed.port = p; return "" end)
    if authority ~= "" then parsed.host = authority end
    local userinfo = parsed.userinfo
    if not userinfo then return parsed end
    userinfo = string.gsub(userinfo, ":([^:]*)$",
        function(p) parsed.password = p; return "" end)
    parsed.user = userinfo
    return parsed
end

-----------------------------------------------------------------------------
-- Rebuilds a parsed URL from its components.
-- Components are protected if any reserved or unallowed characters are found
-- Input
--   parsed: parsed URL, as returned by parse
-- Returns
--   a stringing with the corresponding URL
-----------------------------------------------------------------------------
function build(parsed)
    local ppath = parse_path(parsed.path or "")
    local url = build_path(ppath)
    if parsed.params then url = url .. ";" .. parsed.params end
    if parsed.query then url = url .. "?" .. parsed.query end
	local authority = parsed.authority
	if parsed.host then
		authority = parsed.host
		if parsed.port then authority = authority .. ":" .. parsed.port end
		local userinfo = parsed.userinfo
		if parsed.user then
			userinfo = parsed.user
			if parsed.password then
				userinfo = userinfo .. ":" .. parsed.password
			end
		end
		if userinfo then authority = userinfo .. "@" .. authority end
	end
    if authority then url = "//" .. authority .. url end
    if parsed.scheme then url = parsed.scheme .. ":" .. url end
    if parsed.fragment then url = url .. "#" .. parsed.fragment end
    -- url = string.gsub(url, "%s", "")
    return url
end

-----------------------------------------------------------------------------
-- Builds a absolute URL from a base and a relative URL according to RFC 2396
-- Input
--   base_url
--   relative_url
-- Returns
--   corresponding absolute url
-----------------------------------------------------------------------------
function absolute(base_url, relative_url)
    if base.type(base_url) == "table" then
        base_parsed = base_url
        base_url = build(base_parsed)
    else
        base_parsed = parse(base_url)
    end
    local relative_parsed = parse(relative_url)
    if not base_parsed then return relative_url
    elseif not relative_parsed then return base_url
    elseif relative_parsed.scheme then return relative_url
    else
        relative_parsed.scheme = base_parsed.scheme
        if not relative_parsed.authority then
            relative_parsed.authority = base_parsed.authority
            if not relative_parsed.path then
                relative_parsed.path = base_parsed.path
                if not relative_parsed.params then
                    relative_parsed.params = base_parsed.params
                    if not relative_parsed.query then
                        relative_parsed.query = base_parsed.query
                    end
                end
            else
                relative_parsed.path = absolute_path(base_parsed.path or "",
                    relative_parsed.path)
            end
        end
        return build(relative_parsed)
    end
end

-----------------------------------------------------------------------------
-- Breaks a path into its segments, unescaping the segments
-- Input
--   path
-- Returns
--   segment: a table with one entry per segment
-----------------------------------------------------------------------------
function parse_path(path)
	local parsed = {}
	path = path or ""
	--path = string.gsub(path, "%s", "")
	string.gsub(path, "([^/]+)", function (s) table.insert(parsed, s) end)
	for i = 1, #parsed do
		parsed[i] = unescape(parsed[i])
	end
	if string.sub(path, 1, 1) == "/" then parsed.is_absolute = 1 end
	if string.sub(path, -1, -1) == "/" then parsed.is_directory = 1 end
	return parsed
end

-----------------------------------------------------------------------------
-- Builds a path component from its segments, escaping protected characters.
-- Input
--   parsed: path segments
--   unsafe: if true, segments are not protected before path is built
-- Returns
--   path: corresponding path stringing
-----------------------------------------------------------------------------
function build_path(parsed, unsafe)
	local path = ""
	local n = #parsed
	if unsafe then
		for i = 1, n-1 do
			path = path .. parsed[i]
			path = path .. "/"
		end
		if n > 0 then
			path = path .. parsed[n]
			if parsed.is_directory then path = path .. "/" end
		end
	else
		for i = 1, n-1 do
			path = path .. protect_segment(parsed[i])
			path = path .. "/"
		end
		if n > 0 then
			path = path .. protect_segment(parsed[n])
			if parsed.is_directory then path = path .. "/" end
		end
	end
	if parsed.is_absolute then path = "/" .. path end
	return path
end

return _ENV

end
--------------------------------------------------------------------------------
-- End of moduledebugger.url
--------------------------------------------------------------------------------


--------------------------------------------------------------------------------
--  Main content
--------------------------------------------------------------------------------

-------------------------------------------------------------------------------
-- Copyright (c) 2011-2012 Sierra Wireless and others.
-- All rights reserved. This program and the accompanying materials
-- are made available under the terms of the Eclipse Public License v1.0
-- which accompanies this distribution, and is available at
-- http://www.eclipse.org/legal/epl-v10.html
--
-- Contributors:
--     Sierra Wireless - initial API and implementation
-------------------------------------------------------------------------------

local debug = require "debug"

-- To avoid cyclic dependency, internal state of the debugger that must be accessed
-- elsewhere (in commands most likely) will be stored in a fake module "debugger.core"
local core = { }
package.loaded["debugger.core"] = core

local util = require "debugger.util"
local platform = require "debugger.platform"
local dbgp = require "debugger.dbgp"
local commands = require "debugger.commands"
local context = require "debugger.context"
local url = require "debugger.url"

local log = util.log


-- TODO complete the stdlib access
local corunning, cocreate, cowrap, coyield, coresume, costatus = coroutine.running, coroutine.create, coroutine.wrap, coroutine.yield, coroutine.resume, coroutine.status


-- register the URI of the debugger, to not jump into with redefined function or coroutine bootstrap stuff
local debugger_uri = nil -- set in init function
local transportmodule_uri = nil -- set in init function

-- will contain the session object, and possibly a list of all sessions if a multi-threaded model is adopted
-- this is only used for async commands.
local active_session = nil

-- tracks all active coroutines and associate an id to them, the table from_id is the id=>coro mapping, the table from_coro is the reverse
core.active_coroutines = { n = 0, from_id = setmetatable({ }, { __mode = "v" }), from_coro = setmetatable({ }, { __mode = "k" }) }

-- "BEGIN VERSION DEPENDENT CODE"
local setbpenv     -- set environment of a breakpoint (compiled function)
if _VERSION == "Lua 5.1" then
    local setfenv = setfenv
    setbpenv = setfenv
elseif _VERSION == "Lua 5.2" then
    local setupvalue = debug.setupvalue
    -- _ENV is the first upvalue
    setbpenv = function(f, t) return setupvalue(f, 1, t) end
else error(_VERSION .. "is not supported.") end
-- "END VERSION DEPENDENT CODE"

-------------------------------------------------------------------------------
--  Output redirection handling
-------------------------------------------------------------------------------
-- Override standard output functions & constants to redirect data written to these files to IDE too.
-- This works only for output done in Lua, output written by C extensions is still go to system output file.

-- references to native values
io.base = { output = io.output, stdin = io.stdin, stdout = io.stdout, stderr = io.stderr }

function print(...)
    local buf = {...}
    for i=1, select("#", ...) do
        buf[i] = tostring(buf[i])
    end
    io.stdout:write(table.concat(buf, "\t") .. "\n")
end

-- Actually change standard output file but still return the "fake" stdout
function io.output(output)
    io.base.output(output)
    return io.stdout
end

local dummy = function() end

-- metatable for redirecting output (not printed at all in actual output)
core.redirect_output = {
    write = function(self, ...)
        local buf = {...}
        for i=1, select("#", ...) do buf[i] = tostring(buf[i]) end
        buf = table.concat(buf):gsub("\n", "\r\n")
        dbgp.send_xml(self.skt, { tag = "stream", attr = { type=self.mode },  util.b64(buf) } )
    end,
    flush = dummy,
    close = dummy,
    setvbuf = dummy,
    seek = dummy
}
core.redirect_output.__index = core.redirect_output

-- metatable for cloning output (outputs to actual system and send to IDE)
core.copy_output = {
    write = function(self, ...)
        core.redirect_output.write(self, ...)
        io.base[self.mode]:write(...)
    end,
    flush   = function(self, ...) return self.out:flush(...) end,
    close   = function(self, ...) return self.out:close(...) end,
    setvbuf = function(self, ...) return self.out:setvbuf(...) end,
    seek    = function(self, ...) return self.out:seek(...) end,
}
core.copy_output.__index = core.copy_output

-------------------------------------------------------------------------------
--  Breakpoint registry
-------------------------------------------------------------------------------
-- Registry of current stack levels of all running threads
local stack_levels = setmetatable( { }, { __mode = "k" } )

-- File/line mapping for breakpoints (BP). For a given file/line, a list of BP is associated (DBGp specification section 7.6.1
-- require that multiple BP at same place must be handled)
-- A BP is a table with all additional properties (type, condition, ...) the id is the string representation of the table.
core.breakpoints = {
    -- functions to call to match hit conditions
    hit_conditions = {
        [">="] = function(value, target) return value >= target end,
        ["=="] = function(value, target) return value == target end,
        ["%"]  = function(value, target) return (value % target) == 0 end,
    }
}

-- tracks events such as step_into or step_over
core.events = { }

do
    local file_mapping = { }
    local id_mapping = { }
    local waiting_sessions = { } -- sessions that wait for an event (over, into, out)
    local step_into = nil        -- session that registered a step_into event, if any
    local sequence = 0 -- used to generate breakpoint IDs

    --- Inserts a new breakpoint into registry
    -- @param bp (table) breakpoint data
    -- @param uri (string, optional) Absolute file URI, for line breakpoints
    -- @param line (number, optional) Line where breakpoint stops, for line breakpoints
    -- @return breakpoint identifier
    function core.breakpoints.insert(bp)
        local bpid = sequence
        sequence = bpid + 1
        bp.id = bpid
        -- re-encode the URI to avoid any mismatch (with authority for example)
        local uri = url.parse(bp.filename)
        bp.filename = url.build{ scheme=uri.scheme, authority="", path=platform.normalize(uri.path)}

        local filereg = file_mapping[bp.filename]
        if not filereg then
            filereg = { }
            file_mapping[bp.filename] = filereg
        end

        local linereg = filereg[bp.lineno]
        if not linereg then
            linereg = {}
            filereg[bp.lineno] = linereg
        end

        table.insert(linereg, bp)

        id_mapping[bpid] = bp
        return bpid
    end

    --- If breakpoint(s) exists for given file/line, uptates breakpoint counters
    -- and returns whether a breakpoint has matched (boolean)
    function core.breakpoints.at(file, line)
        local bps = file_mapping[file] and file_mapping[file][line]
        if not bps then return nil end

        local do_break = false
        for _, bp in pairs(bps) do
            if bp.state == "enabled" then
                local match = true
                if bp.condition then
                    -- TODO: this is not the optimal solution because Context can be instantiated twice if the breakpoint matches
                    local cxt = context.Context:new(active_session.coro, 0)
                    setbpenv(bp.condition, cxt)
                    local success, result = pcall(bp.condition)
                    if not success then log("ERROR", "Condition evaluation failed for breakpoint at %s:%d: %s", file, line, result) end
                    -- debugger always stops if an error occurs
                    match = (not success) or result
                end
                if match then
                    bp.hit_count = bp.hit_count + 1
                    if core.breakpoints.hit_conditions[bp.hit_condition](bp.hit_count, bp.hit_value) then
                        if bp.temporary then
                            core.breakpoints.remove(bp.id)
                        end
                        do_break = true
                        -- there is no break to handle multiple breakpoints: all hit counts must be updated
                    end
                end
            end
        end
        return do_break
    end

    function core.breakpoints.get(id)
        if id then return id_mapping[id]
        else return id_mapping end
    end

    function core.breakpoints.remove(id)
        local bp = id_mapping[id]
        if bp then
            id_mapping[id] = nil
            local linereg = file_mapping[bp.filename][bp.lineno]
            for i=1, #linereg do
                if linereg[i] == bp then
                    table.remove(linereg, i)
                    break
                end
            end

            -- cleanup file_mapping
            if not next(linereg) then file_mapping[bp.filename][bp.lineno] = nil end
            if not next(file_mapping[bp.filename]) then file_mapping[bp.filename] = nil end
            return true
        end
        return false
    end

    --- Returns an XML data structure that describes given breakpoint
    -- @param id (number) breakpoint ID
    -- @return Table describing a <breakpooint> tag or nil followed by an error message
    function core.breakpoints.get_xml(id)
        local bp = id_mapping[id]
        if not bp then return nil, "No such breakpoint: "..tostring(id) end

        local response = { tag = "breakpoint", attr = { } }
        for k,v in pairs(bp) do response.attr[k] = v end
        if bp.expression then
            response[1] = { tag = "expression",  bp.expression }
        end

        -- internal use only
        response.attr.expression = nil
        response.attr.condition = nil
        response.attr.temporary = nil -- TODO: the specification is not clear whether this should be provided, see other implementations
        return response
    end

    --- Register an event to be triggered.
    -- @param event event name to register (must be "over", "out" or "into")
    function core.events.register(event)
        local thread = active_session.coro[1]
        log("DEBUG", "Registered %s event for %s (%d)", event, tostring(thread), stack_levels[thread])
        if event == "into" then
            step_into = true
        else
            waiting_sessions[thread] = { event, stack_levels[thread] }
        end
    end

    --- Returns if an event (step into, over, out) is triggered.
    -- Does *not* discard events (even if they match) as event must be discarded manually if a breakpoint match before anyway.
    -- @return true if an event has matched, false otherwise
    function core.events.does_match()
        if step_into then return true end

        local thread = active_session.coro[1]
        local event = waiting_sessions[thread]
        if event then
            local event_type, target_level = unpack(event)
            local current_level = stack_levels[thread]

            if (event_type == "over" and current_level <= target_level) or   -- step over
               (event_type == "out"  and current_level <  target_level) then -- step out
                log("DEBUG", "Event %s matched!", event_type)
                return true
            end
        end
        return false
    end

    --- Discards event for current thread (if any)
    function core.events.discard()
        waiting_sessions[active_session.coro[1]] = nil
        step_into = nil
    end
end

-------------------------------------------------------------------------------
--  Debugger main loop
-------------------------------------------------------------------------------

--- Send the XML response to the previous continuation command and clear the previous context
function core.previous_context_response(self, reason)
    self.previous_context.status = self.state
    self.previous_context.reason = reason or "ok"
    dbgp.send_xml(self.skt, { tag = "response", attr = self.previous_context } )
    self.previous_context = nil
end

local function cleanup()
    coroutine.resume, coroutine.wrap = coresume, cowrap
    for _, coro in pairs(core.active_coroutines.from_id) do
        debug.sethook(coro)
    end
    -- to remove hook on the main coroutine, it must be the current one (otherwise, this is a no-op) and this function
    -- have to be called adain later on the main thread to finish cleaup
    debug.sethook()
    core.active_coroutines.from_id, core.active_coroutines.from_coro = { }, { }
end

--- This function handles the debugger commands while the execution is paused. This does not use coroutines because there is no
-- way to get main coro in Lua 5.1 (only in 5.2)
local function debugger_loop(self, async_packet)
    self.skt:settimeout(nil) -- set socket blocking

    -- in async mode, the debugger does not wait for another command before continuing and does not modify previous_context
    local async_mode = async_packet ~= nil

    if self.previous_context and not async_mode then
        self.state = "break"
        core.previous_context_response(self)
    end
    self.stack = context.ContextManager(self.coro) -- will be used to mutualize context allocation for each loop

    while true do
        -- reads packet
        local packet = async_packet or dbgp.read_packet(self.skt)
        if not packet then
          log("WARNING", "lost debugger connection")
          cleanup()
          break
        end

        async_packet = nil
        log("DEBUG", packet)
        local cmd, args, data = dbgp.cmd_parse(packet)

        -- FIXME: command such as continuations sent in async mode could lead both engine and IDE in inconsistent state :
        --        make a blacklist/whitelist of forbidden or allowed commands in async ?
        -- invoke function
        local func = commands[cmd]
        if func then
            local ok, cont = xpcall(function() return func(self, args, data) end, debug.traceback)
            if not ok then -- internal exception
                local code, msg, attr
                if type(cont) == "table" and getmetatable(cont) == dbgp.DBGP_ERR_METATABLE then
                    code, msg, attr = cont.code, cont.message, cont.attr
                else
                    code, msg, attr = 998, tostring(cont), { }
                end
                log("ERROR", "Command %s caused: (%d) %s", cmd, code, tostring(msg))
                attr.command, attr.transaction_id = cmd, args.i
                dbgp.send_xml(self.skt, { tag = "response", attr = attr, dbgp.make_error(code, msg) } )
            elseif cont then
                self.previous_context = { command = cmd, transaction_id = args.i }
                break
            elseif cont == nil and async_mode then
                break
            elseif cont == false then -- In case of commands that fully resumes debugger loop, the mode is sync
                async_mode = false
            end
        else
            log("Got unknown command: "..cmd)
            dbgp.send_xml(self.skt, { tag = "response", attr = { command = cmd, transaction_id = args.i, }, dbgp.make_error(4) } )
        end
    end

    self.stack = nil -- free allocated contexts
    self.state = "running"
    self.skt:settimeout(0) -- reset socket to async
end

-- Stack handling can be pretty complex sometimes, especially with LuaJIT (as tail-call optimization are
-- more aggressive as stock Lua). So all debugger stuff is done in another coroutine, which leave the program
-- stack in a clean state and allow faster and clearer stack operations (no need to remove all debugger calls
-- from stack for each operation).
-- However, this does not always work with stock Lua 5.1 as the main coroutine cannot be referenced
-- (coroutine.running() return nil). For this particular case, the debugger loop is started on the top of
-- program stack and every stack operation is relative the the hook level (see MainThread in util.lua).
local function line_hook(line)
    local do_break, packet = nil, nil
    local info = active_session.coro:getinfo(0, "S")
    local uri = platform.get_uri(info.source)
    if uri and uri ~= debugger_uri and uri ~= transportmodule_uri then -- the debugger does not break if the source is not known
        do_break = core.breakpoints.at(uri, line) or core.events.does_match()
        if do_break then
            core.events.discard()
        end

        -- check for async commands
        if not do_break then
            packet = dbgp.read_packet(active_session.skt)
            if packet then do_break = true end
        end
    end

    if do_break then
        local success, err = pcall(debugger_loop, active_session, packet)
        if not success then log("ERROR", "Error while debug loop: "..err) end
    end
end

local line_hook_coro = cocreate(function(line)
    while true do
        line_hook(line)
        line = coyield()
    end
end)

local function debugger_hook(event, line)
    local thread = corunning() or "main"
    if event == "call" then
        stack_levels[thread] = stack_levels[thread] + 1
    elseif event == "tail call" then
        -- tail calls has no effects on stack handling: it is only used only for step commands but a such even does not
        -- interfere with any of them
    elseif event == "return" or event == "tail return" then
        stack_levels[thread] = stack_levels[thread] - 1
    else -- line event: check for breakpoint
        active_session.coro = util.CurrentThread(corunning())
        if active_session.coro[1] == "main" then
            line_hook(line)
        else
            -- run the debugger loop in another thread on the other cases (simplifies stack handling)
            assert(coresume(line_hook_coro, line))
        end
        active_session.coro = nil
    end
end

if rawget(_G, "jit") then
    debugger_hook = function(event, line)
        local thread = corunning() or "main"
        if event == "call" then
            if debug.getinfo(2, "S").what == "C" then return end
            stack_levels[thread] = stack_levels[thread] + 1
        elseif event == "return" or event == "tail return" then
            -- Return hooks are not called for tail calls in JIT (but unlike 5.2 there is no way to know whether a call is tail or not).
            -- So the only reliable way to know stack depth is to walk it.
            local depth = 2
            -- TODO: find the fastest way to call getinfo ('what' parameter)
            while debug.getinfo(depth, "f") do depth = depth + 1 end
            stack_levels[thread] = depth - 2
        elseif event == "line" then
            active_session.coro = util.CurrentThread(corunning())
            if active_session.coro[1] == "main" then
                line_hook(line)
            else
                -- run the debugger loop in another thread on the other cases (simplifies stack handling)
                assert(coresume(line_hook_coro, line))
            end
            active_session.coro = nil
        end
    end
end

local function init(host, port, idekey, transport, executionplatform, workingdirectory)
    -- get connection data
    local host = host or os.getenv "DBGP_IDEHOST" or "127.0.0.1"
    local port = port or os.getenv "DBGP_IDEPORT" or "10000"
    local idekey = idekey or os.getenv("DBGP_IDEKEY") or "luaidekey"

    -- init plaform module
    local executionplatform = executionplatform or os.getenv("DBGP_PLATFORM") or nil
    local workingdirectory = workingdirectory or os.getenv("DBGP_WORKINGDIR") or nil
    platform.init(executionplatform,workingdirectory)

    -- get transport layer
    local transportpath = transport or os.getenv("DBGP_TRANSPORT") or "debugger.transport.luasocket"
    local transport = require(transportpath)

    -- install base64 functions into util
    util.b64, util.rawb64, util.unb64 = transport.b64, transport.rawb64, transport.unb64

    local skt = assert(transport.create())
    skt:settimeout(nil)

    -- try to connect several times: if IDE launches both process and server at same time, first connect attempts may fail
    local ok, err
    for i=1, 5 do
        ok, err = skt:connect(host, port)
        if ok then break end
        transport.sleep(0.5)
    end
    if err then error(string.format("Cannot connect to %s:%d : %s", host, port, err)) end

    -- get the debugger and transport layer URI
    debugger_uri = platform.get_uri(debug.getinfo(1).source)
    transportmodule_uri = platform.get_uri(debug.getinfo(transport.create).source)

    -- get the root script path (the highest possible stack index)
    local source
    for i=2, math.huge do
        local info = debug.getinfo(i)
        if not info then break end
        source = platform.get_uri(info.source) or source
    end
    if not source then source = "unknown:/" end -- when loaded before actual script (with a command line switch)

    -- generate some kind of thread identifier
    local thread = corunning() or "main"
    stack_levels[thread] = 1 -- the return event will set the counter to 0
    local sessionid = tostring(os.time()) .. "_" .. tostring(thread)

    dbgp.send_xml(skt, { tag = "init", attr = {
        appid = "Lua DBGp",
        idekey = idekey,
        session = sessionid,
        thread = tostring(thread),
        parent = "",
        language = "Lua",
        protocol_version = "1.0",
        fileuri = source
    } })

    --FIXME util.CurrentThread(corunning) => util.CurrentThread(corunning()) WHAT DOES IT FIXES ??
    local sess = { skt = skt, state = "starting", id = sessionid, coro = util.CurrentThread(corunning) }
    active_session = sess
    debugger_loop(sess)

    -- set debug hooks
    debug.sethook(debugger_hook, "rlc")

    -- install coroutine collecting functions.
    -- TODO: maintain a list of *all* coroutines can be overkill (for example, the ones created by copcall), make a extension point to
    -- customize debugged coroutines
    -- coroutines are referenced during their first resume (so we are sure that they always have a stack frame)
    local function resume_handler(coro, ...)
        if costatus(coro) == "dead" then
            local coro_id = core.active_coroutines.from_coro[coro]
            core.active_coroutines.from_id[coro_id] = nil
            core.active_coroutines.from_coro[coro] = nil
            stack_levels[coro] = nil
        end
        return ...
    end

    function coroutine.resume(coro, ...)
        if not stack_levels[coro] then
            -- first time referenced
            stack_levels[coro] = 0
            core.active_coroutines.n = core.active_coroutines.n + 1
            core.active_coroutines.from_id[core.active_coroutines.n] = coro
            core.active_coroutines.from_coro[coro] = core.active_coroutines.n
            debug.sethook(coro, debugger_hook, "rlc")
        end
        return resume_handler(coro, coresume(coro, ...))
    end

    -- coroutine.wrap uses directly C API for coroutines and does not trigger our overridden coroutine.resume
    -- so this is an implementation of wrap in pure Lua
    local function wrap_handler(status, ...)
        if not status then error((...)) end
        return ...
    end

    function coroutine.wrap(f)
        local coro = coroutine.create(f)
        return function(...)
            return wrap_handler(coroutine.resume(coro, ...))
        end
    end

    return sess
end

return init
