--
-- MobDebug 0.542
-- Copyright 2011-13 Paul Kulchenko
-- Based on RemDebug 1.0 Copyright Kepler Project 2005
--

local mobdebug = {
  _NAME = "mobdebug",
  _VERSION = 0.542,
  _COPYRIGHT = "Paul Kulchenko",
  _DESCRIPTION = "Mobile Remote Debugger for the Lua programming language",
  port = os and os.getenv and os.getenv("MOBDEBUG_PORT") or 8172,
  checkcount = 200,
  yieldtimeout = 0.02,
}

local coroutine = coroutine
local error = error
local getfenv = getfenv
local setfenv = setfenv
local loadstring = loadstring or load -- "load" replaced "loadstring" in Lua 5.2
local io = io
local os = os
local pairs = pairs
local require = require
local setmetatable = setmetatable
local string = string
local tonumber = tonumber
local unpack = table.unpack or unpack
local rawget = rawget

-- if strict.lua is used, then need to avoid referencing some global
-- variables, as they can be undefined;
-- use rawget to to avoid complaints from strict.lua at run-time.
-- it's safe to do the initialization here as all these variables
-- should get defined values (of any) before the debugging starts.
-- there is also global 'wx' variable, which is checked as part of
-- the debug loop as 'wx' can be loaded at any time during debugging.
local genv = _G or _ENV
local jit = rawget(genv, "jit")
local MOAICoroutine = rawget(genv, "MOAICoroutine")

if not setfenv then -- Lua 5.2
  -- based on http://lua-users.org/lists/lua-l/2010-06/msg00314.html
  -- this assumes f is a function
  local function findenv(f)
    local level = 1
    repeat
      local name, value = debug.getupvalue(f, level)
      if name == '_ENV' then return level, value end
      level = level + 1
    until name == nil
    return nil end
  getfenv = function (f) return(select(2, findenv(f)) or _G) end
  setfenv = function (f, t)
    local level = findenv(f)
    if level then debug.setupvalue(f, level, t) end
    return f end
end

-- check for OS and convert file names to lower case on windows
-- (its file system is case insensitive, but case preserving), as setting a
-- breakpoint on x:\Foo.lua will not work if the file was loaded as X:\foo.lua.
-- OSX and Windows behave the same way (case insensitive, but case preserving)
local iscasepreserving = os and os.getenv and (os.getenv('WINDIR')
  or (os.getenv('OS') or ''):match('[Ww]indows')
  or os.getenv('DYLD_LIBRARY_PATH'))
  or not io.open("/proc")

-- turn jit off based on Mike Pall's comment in this discussion:
-- http://www.freelists.org/post/luajit/Debug-hooks-and-JIT,2
-- "You need to turn it off at the start if you plan to receive
-- reliable hook calls at any later point in time."
if jit and jit.off then jit.off() end

local socket = require "socket"
local debug = require "debug"
local coro_debugger
local coro_debugee
local coroutines = {}; setmetatable(coroutines, {__mode = "k"}) -- "weak" keys
local events = { BREAK = 1, WATCH = 2, RESTART = 3, STACK = 4 }
local breakpoints = {}
local watches = {}
local lastsource
local lastfile
local watchescnt = 0
local abort -- default value is nil; this is used in start/loop distinction
local seen_hook = false
local checkcount = 0
local step_into = false
local step_over = false
local step_level = 0
local stack_level = 0
local server
local buf
local outputs = {}
local iobase = {print = print}
local basedir = ""
local deferror = "execution aborted at default debugee"
local debugee = function () 
  local a = 1
  for _ = 1, 10 do a = a + 1 end
  error(deferror)
end
local function q(s) return s:gsub('([%(%)%.%%%+%-%*%?%[%^%$%]])','%%%1') end

local serpent = (function() ---- include Serpent module for serialization
local n, v = "serpent", 0.25 -- (C) 2012-13 Paul Kulchenko; MIT License
local c, d = "Paul Kulchenko", "Lua serializer and pretty printer"
local snum = {[tostring(1/0)]='1/0 --[[math.huge]]',[tostring(-1/0)]='-1/0 --[[-math.huge]]',[tostring(0/0)]='0/0'}
local badtype = {thread = true, userdata = true, cdata = true}
local keyword, globals, G = {}, {}, (_G or _ENV)
for _,k in ipairs({'and', 'break', 'do', 'else', 'elseif', 'end', 'false',
  'for', 'function', 'goto', 'if', 'in', 'local', 'nil', 'not', 'or', 'repeat',
  'return', 'then', 'true', 'until', 'while'}) do keyword[k] = true end
for k,v in pairs(G) do globals[v] = k end -- build func to name mapping
for _,g in ipairs({'coroutine', 'debug', 'io', 'math', 'string', 'table', 'os'}) do
  for k,v in pairs(G[g]) do globals[v] = g..'.'..k end end

local function s(t, opts)
  local name, indent, fatal, maxnum = opts.name, opts.indent, opts.fatal, opts.maxnum
  local sparse, custom, huge = opts.sparse, opts.custom, not opts.nohuge
  local space, maxl = (opts.compact and '' or ' '), (opts.maxlevel or math.huge)
  local iname, comm = '_'..(name or ''), opts.comment and (tonumber(opts.comment) or math.huge)
  local seen, sref, syms, symn = {}, {'local '..iname..'={}'}, {}, 0
  local function gensym(val) return '_'..(tostring(tostring(val)):gsub("[^%w]",""):gsub("(%d%w+)",
    -- tostring(val) is needed because __tostring may return a non-string value
    function(s) if not syms[s] then symn = symn+1; syms[s] = symn end return syms[s] end)) end
  local function safestr(s) return type(s) == "number" and (huge and snum[tostring(s)] or s)
    or type(s) ~= "string" and tostring(s) -- escape NEWLINE/010 and EOF/026
    or ("%q"):format(s):gsub("\010","n"):gsub("\026","\\026") end
  local function comment(s,l) return comm and (l or 0) < comm and ' --[['..tostring(s)..']]' or '' end
  local function globerr(s,l) return globals[s] and globals[s]..comment(s,l) or not fatal
    and safestr(select(2, pcall(tostring, s))) or error("Can't serialize "..tostring(s)) end
  local function safename(path, name) -- generates foo.bar, foo[3], or foo['b a r']
    local n = name == nil and '' or name
    local plain = type(n) == "string" and n:match("^[%l%u_][%w_]*$") and not keyword[n]
    local safe = plain and n or '['..safestr(n)..']'
    return (path or '')..(plain and path and '.' or '')..safe, safe end
  local alphanumsort = type(opts.sortkeys) == 'function' and opts.sortkeys or function(k, o, n)  -- k=keys, o=originaltable, n=padding
    local maxn, to = tonumber(n) or 12, {number = 'a', string = 'b'}
    local function padnum(d) return ("%0"..maxn.."d"):format(d) end
    table.sort(k, function(a,b)
      -- sort numeric keys first: k[key] is non-nil for numeric keys
      return (k[a] and 0 or to[type(a)] or 'z')..(tostring(a):gsub("%d+",padnum))
           < (k[b] and 0 or to[type(b)] or 'z')..(tostring(b):gsub("%d+",padnum)) end) end
  local function val2str(t, name, indent, insref, path, plainindex, level)
    local ttype, level, mt = type(t), (level or 0), getmetatable(t)
    local spath, sname = safename(path, name)
    local tag = plainindex and
      ((type(name) == "number") and '' or name..space..'='..space) or
      (name ~= nil and sname..space..'='..space or '')
    if seen[t] then -- already seen this element
      sref[#sref+1] = spath..space..'='..space..seen[t]
      return tag..'nil'..comment('ref', level) end
    if type(mt) == 'table' and (mt.__serialize or mt.__tostring) then -- knows how to serialize itself
      seen[t] = insref or spath
      if mt.__serialize then t = mt.__serialize(t) else t = tostring(t) end
      ttype = type(t) end -- new value falls through to be serialized
    if ttype == "table" then
      if level >= maxl then return tag..'{}'..comment('max', level) end
      seen[t] = insref or spath
      if next(t) == nil then return tag..'{}'..comment(t, level) end -- table empty
      local maxn, o, out = math.min(#t, maxnum or #t), {}, {}
      for key = 1, maxn do o[key] = key end
      if not maxnum or #o < maxnum then
        local n = #o -- n = n + 1; o[n] is much faster than o[#o+1] on large tables
        for key in pairs(t) do if o[key] ~= key then n = n + 1; o[n] = key end end end
      if maxnum and #o > maxnum then o[maxnum+1] = nil end
      if opts.sortkeys and #o > maxn then alphanumsort(o, t, opts.sortkeys) end
      local sparse = sparse and #o > maxn -- disable sparsness if only numeric keys (shorter output)
      for n, key in ipairs(o) do
        local value, ktype, plainindex = t[key], type(key), n <= maxn and not sparse
        if opts.valignore and opts.valignore[value] -- skip ignored values; do nothing
        or opts.keyallow and not opts.keyallow[key]
        or opts.valtypeignore and opts.valtypeignore[type(value)] -- skipping ignored value types
        or sparse and value == nil then -- skipping nils; do nothing
        elseif ktype == 'table' or ktype == 'function' or badtype[ktype] then
          if not seen[key] and not globals[key] then
            sref[#sref+1] = 'placeholder'
            local sname = safename(iname, gensym(key)) -- iname is table for local variables
            sref[#sref] = val2str(key,sname,indent,sname,iname,true) end
          sref[#sref+1] = 'placeholder'
          local path = seen[t]..'['..(seen[key] or globals[key] or gensym(key))..']'
          sref[#sref] = path..space..'='..space..(seen[value] or val2str(value,nil,indent,path))
        else
          out[#out+1] = val2str(value,key,indent,insref,seen[t],plainindex,level+1)
        end
      end
      local prefix = string.rep(indent or '', level)
      local head = indent and '{\n'..prefix..indent or '{'
      local body = table.concat(out, ','..(indent and '\n'..prefix..indent or space))
      local tail = indent and "\n"..prefix..'}' or '}'
      return (custom and custom(tag,head,body,tail) or tag..head..body..tail)..comment(t, level)
    elseif badtype[ttype] then
      seen[t] = insref or spath
      return tag..globerr(t, level)
    elseif ttype == 'function' then
      seen[t] = insref or spath
      local ok, res = pcall(string.dump, t)
      local func = ok and ((opts.nocode and "function() --[[..skipped..]] end" or
        "loadstring("..safestr(res)..",'@serialized')")..comment(t, level))
      return tag..(func or globerr(t, level))
    else return tag..safestr(t) end -- handle all other types
  end
  local sepr = indent and "\n" or ";"..space
  local body = val2str(t, name, indent) -- this call also populates sref
  local tail = #sref>1 and table.concat(sref, sepr)..sepr or ''
  local warn = opts.comment and #sref>1 and space.."--[[incomplete output with shared/self-references skipped]]" or ''
  return not name and body..warn or "do local "..body..sepr..tail.."return "..name..sepr.."end"
end

local function merge(a, b) if b then for k,v in pairs(b) do a[k] = v end end; return a; end
return { _NAME = n, _COPYRIGHT = c, _DESCRIPTION = d, _VERSION = v, serialize = s,
  dump = function(a, opts) return s(a, merge({name = '_', compact = true, sparse = true}, opts)) end,
  line = function(a, opts) return s(a, merge({sortkeys = true, comment = true}, opts)) end,
  block = function(a, opts) return s(a, merge({indent = '  ', sortkeys = true, comment = true}, opts)) end }
end)() ---- end of Serpent module

local function removebasedir(path, basedir)
  if iscasepreserving then
    -- check if the lowercased path matches the basedir
    -- if so, return substring of the original path (to not lowercase it)
    return path:lower():find('^'..q(basedir:lower()))
      and path:sub(#basedir+1) or path
  else
    return string.gsub(path, '^'..q(basedir), '')
  end
end

local function stack(start)
  local function vars(f)
    local func = debug.getinfo(f, "f").func
    local i = 1
    local locals = {}
    while true do
      local name, value = debug.getlocal(f, i)
      if not name then break end
      if string.sub(name, 1, 1) ~= '(' then locals[name] = {value, tostring(value)} end
      i = i + 1
    end
    i = 1
    local ups = {}
    while func and true do -- check for func as it may be nil for tail calls
      local name, value = debug.getupvalue(func, i)
      if not name then break end
      ups[name] = {value, tostring(value)}
      i = i + 1
    end
    return locals, ups
  end

  local stack = {}
  for i = (start or 0), 100 do
    local source = debug.getinfo(i, "Snl")
    if not source then break end

    local src = source.source
    if src:find("@") == 1 then
      src = src:sub(2):gsub("\\", "/")
      if src:find("%./") == 1 then src = src:sub(3) end
    end

    table.insert(stack, { -- remove basedir from source
      {source.name, removebasedir(src, basedir), source.linedefined,
       source.currentline, source.what, source.namewhat, source.short_src},
      vars(i+1)})
    if source.what == 'main' then break end
  end
  return stack
end

local function set_breakpoint(file, line)
  if file == '-' and lastfile then file = lastfile
  elseif iscasepreserving then file = string.lower(file) end
  if not breakpoints[line] then breakpoints[line] = {} end
  breakpoints[line][file] = true
end

local function remove_breakpoint(file, line)
  if file == '-' and lastfile then file = lastfile
  elseif iscasepreserving then file = string.lower(file) end
  if breakpoints[line] then breakpoints[line][file] = nil end
end

local function has_breakpoint(file, line)
  return breakpoints[line]
     and breakpoints[line][iscasepreserving and string.lower(file) or file]
end

local function restore_vars(vars)
  if type(vars) ~= 'table' then return end

  -- locals need to be processed in the reverse order, starting from
  -- the inner block out, to make sure that the localized variables
  -- are correctly updated with only the closest variable with
  -- the same name being changed
  -- first loop find how many local variables there is, while
  -- the second loop processes them from i to 1
  local i = 1
  while true do
    local name = debug.getlocal(3, i)
    if not name then break end
    i = i + 1
  end
  i = i - 1
  local written_vars = {}
  while i > 0 do
    local name = debug.getlocal(3, i)
    if not written_vars[name] then
      if string.sub(name, 1, 1) ~= '(' then
        debug.setlocal(3, i, rawget(vars, name))
      end
      written_vars[name] = true
    end
    i = i - 1
  end

  i = 1
  local func = debug.getinfo(3, "f").func
  while true do
    local name = debug.getupvalue(func, i)
    if not name then break end
    if not written_vars[name] then
      if string.sub(name, 1, 1) ~= '(' then
        debug.setupvalue(func, i, rawget(vars, name))
      end
      written_vars[name] = true
    end
    i = i + 1
  end
end

local function capture_vars(level)
  local vars = {}
  local func = debug.getinfo(level or 3, "f").func
  local i = 1
  while true do
    local name, value = debug.getupvalue(func, i)
    if not name then break end
    if string.sub(name, 1, 1) ~= '(' then vars[name] = value end
    i = i + 1
  end
  i = 1
  while true do
    local name, value = debug.getlocal(level or 3, i)
    if not name then break end
    if string.sub(name, 1, 1) ~= '(' then vars[name] = value end
    i = i + 1
  end
  -- returned 'vars' table plays a dual role: (1) it captures local values
  -- and upvalues to be restored later (in case they are modified in "eval"),
  -- and (2) it provides an environment for evaluated chunks.
  -- getfenv(func) is needed to provide proper environment for functions,
  -- including access to globals, but this causes vars[name] to fail in
  -- restore_vars on local variables or upvalues with `nil` values when
  -- 'strict' is in effect. To avoid this `rawget` is used in restore_vars.
  setmetatable(vars, { __index = getfenv(func), __newindex = getfenv(func) })
  return vars
end

local function stack_depth(start_depth)
  for i = start_depth, 0, -1 do
    if debug.getinfo(i, "l") then return i+1 end
  end
  return start_depth
end

local function is_safe(stack_level)
  -- the stack grows up: 0 is getinfo, 1 is is_safe, 2 is debug_hook, 3 is user function
  if stack_level == 3 then return true end
  for i = 3, stack_level do
    -- return if it is not safe to abort
    local info = debug.getinfo(i, "S")
    if not info then return true end
    if info.what == "C" then return false end
  end
  return true
end

local function in_debugger()
  local this = debug.getinfo(1, "S").source
  -- only need to check few frames as mobdebug frames should be close
  for i = 3, 7 do
    local info = debug.getinfo(i, "S")
    if not info then return false end
    if info.source == this then return true end
  end
  return false
end

local function is_pending(peer)
  -- if there is something already in the buffer, skip check
  if not buf and checkcount >= mobdebug.checkcount then
    peer:settimeout(0) -- non-blocking
    buf = peer:receive(1)
    peer:settimeout() -- back to blocking
    checkcount = 0
  end
  return buf
end

local function debug_hook(event, line)
  -- (1) LuaJIT needs special treatment. Because debug_hook is set for
  -- *all* coroutines, and not just the one being debugged as in regular Lua
  -- (http://lua-users.org/lists/lua-l/2011-06/msg00513.html),
  -- need to avoid debugging mobdebug's own code as LuaJIT doesn't
  -- always correctly generate call/return hook events (there are more
  -- calls than returns, which breaks stack depth calculation and
  -- 'step' and 'step over' commands stop working; possibly because
  -- 'tail return' events are not generated by LuaJIT).
  -- the next line checks if the debugger is run under LuaJIT and if
  -- one of debugger methods is present in the stack, it simply returns.
  if jit then
    -- when luajit is compiled with LUAJIT_ENABLE_LUA52COMPAT,
    -- coroutine.running() returns non-nil for the main thread.
    local coro, main = coroutine.running()
    if not coro or main then coro = 'main' end
    local disabled = coroutines[coro] == false
      or coroutines[coro] == nil and coro ~= (coro_debugee or 'main')
    if coro_debugee and disabled or not coro_debugee and (disabled or in_debugger())
    then return end
  end

  -- (2) check if abort has been requested and it's safe to abort
  if abort and is_safe(stack_level) then error(abort) end

  -- (3) also check if this debug hook has not been visited for any reason.
  -- this check is needed to avoid stepping in too early
  -- (for example, when coroutine.resume() is executed inside start()).
  if not seen_hook and in_debugger() then return end

  if event == "call" then
    stack_level = stack_level + 1
  elseif event == "return" or event == "tail return" then
    stack_level = stack_level - 1
  elseif event == "line" then
    -- may need to fall through because of the following:
    -- (1) step_into
    -- (2) step_over and stack_level <= step_level (need stack_level)
    -- (3) breakpoint; check for line first as it's known; then for file
    -- (4) socket call (only do every Xth check)
    -- (5) at least one watch is registered
    if not (
      step_into or step_over or breakpoints[line] or watchescnt > 0
      or is_pending(server)
    ) then checkcount = checkcount + 1; return end

    checkcount = mobdebug.checkcount -- force check on the next command

    -- this is needed to check if the stack got shorter or longer.
    -- unfortunately counting call/return calls is not reliable.
    -- the discrepancy may happen when "pcall(load, '')" call is made
    -- or when "error()" is called in a function.
    -- in either case there are more "call" than "return" events reported.
    -- this validation is done for every "line" event, but should be "cheap"
    -- as it checks for the stack to get shorter (or longer by one call).
    -- start from one level higher just in case we need to grow the stack.
    -- this may happen after coroutine.resume call to a function that doesn't
    -- have any other instructions to execute. it triggers three returns:
    -- "return, tail return, return", which needs to be accounted for.
    stack_level = stack_depth(stack_level+1)

    local caller = debug.getinfo(2, "S")

    -- grab the filename and fix it if needed
    local file = lastfile
    if (lastsource ~= caller.source) then
      file, lastsource = caller.source, caller.source
      -- technically, users can supply names that may not use '@',
      -- for example when they call loadstring('...', 'filename.lua').
      -- Unfortunately, there is no reliable/quick way to figure out
      -- what is the filename and what is the source code.
      -- The following will work if the supplied filename uses Unix path.
      if file:find("^@") then
        file = file:gsub("^@", ""):gsub("\\", "/")
        -- need this conversion to be applied to relative and absolute
        -- file names as you may write "require 'Foo'" to
        -- load "foo.lua" (on a case insensitive file system) and breakpoints
        -- set on foo.lua will not work if not converted to the same case.
        if iscasepreserving then file = string.lower(file) end
        if file:find("%./") == 1 then file = file:sub(3)
        else file = file:gsub('^'..q(basedir), '') end
        -- some file systems allow newlines in file names; remove these.
        file = file:gsub("\n", ' ')
      else
        -- this is either a file name coming from loadstring("chunk", "file"),
        -- or the actual source code that needs to be serialized (as it may
        -- include newlines); assume it's a file name if it's all on one line.
        file = file:find("[\r\n]") and serpent.line(file) or file
      end

      -- set to true if we got here; this only needs to be done once per
      -- session, so do it here to at least avoid setting it for every line.
      seen_hook = true
      lastfile = file
    end

    local vars, status, res
    if (watchescnt > 0) then
      vars = capture_vars()
      for index, value in pairs(watches) do
        setfenv(value, vars)
        local ok, fired = pcall(value)
        if ok and fired then
          status, res = coroutine.resume(coro_debugger, events.WATCH, vars, file, line, index)
          break -- any one watch is enough; don't check multiple times
        end
      end
    end

    -- need to get into the "regular" debug handler, but only if there was
    -- no watch that was fired. If there was a watch, handle its result.
    local getin = (status == nil) and
      (step_into
      or (step_over and stack_level <= step_level)
      or has_breakpoint(file, line)
      or is_pending(server))

    if getin then
      vars = vars or capture_vars()
      step_into = false
      step_over = false
      status, res = coroutine.resume(coro_debugger, events.BREAK, vars, file, line)
    end

    -- handle 'stack' command that provides stack() information to the debugger
    if status and res == 'stack' then
      while status and res == 'stack' do
        -- resume with the stack trace and variables
        if vars then restore_vars(vars) end -- restore vars so they are reflected in stack values
        -- this may fail if __tostring method fails at run-time
        local ok, snapshot = pcall(stack, 4)
        status, res = coroutine.resume(coro_debugger, ok and events.STACK or events.BREAK, snapshot, file, line)
      end
    end

    -- need to recheck once more as resume after 'stack' command may
    -- return something else (for example, 'exit'), which needs to be handled
    if status and res and res ~= 'stack' then
      if abort == nil and res == "exit" then os.exit(1); return end
      abort = res
      -- only abort if safe; if not, there is another (earlier) check inside
      -- debug_hook, which will abort execution at the first safe opportunity
      if is_safe(stack_level) then error(abort) end
    elseif not status and res then
      error(res, 2) -- report any other (internal) errors back to the application
    end

    if vars then restore_vars(vars) end
  end
end

local function stringify_results(status, ...)
  if not status then return status, ... end -- on error report as it

  local t = {...}
  for i,v in pairs(t) do -- stringify each of the returned values
    local ok, res = pcall(serpent.line, v, {nocode = true, comment = 1})
    t[i] = ok and res or ("%q"):format(res):gsub("\010","n"):gsub("\026","\\026")
  end
  -- stringify table with all returned values
  -- this is done to allow each returned value to be used (serialized or not)
  -- intependently and to preserve "original" comments
  return pcall(serpent.dump, t, {sparse = false})
end

local function debugger_loop(sev, svars, sfile, sline)
  local command
  local app, osname
  local eval_env = svars or {}
  local function emptyWatch () return false end
  local loaded = {}
  for k in pairs(package.loaded) do loaded[k] = true end

  while true do
    local line, err
    local wx = rawget(genv, "wx") -- use rawread to make strict.lua happy
    if (wx or mobdebug.yield) and server.settimeout then server:settimeout(mobdebug.yieldtimeout) end
    while true do
      line, err = server:receive()
      if not line and err == "timeout" then
        -- yield for wx GUI applications if possible to avoid "busyness"
        app = app or (wx and wx.wxGetApp and wx.wxGetApp())
        if app then
          local win = app:GetTopWindow()
          local inloop = app:IsMainLoopRunning()
          osname = osname or wx.wxPlatformInfo.Get():GetOperatingSystemFamilyName()
          if win and not inloop then
            -- process messages in a regular way
            -- and exit as soon as the event loop is idle
            if osname == 'Unix' then wx.wxTimer(app):Start(10, true) end
            local exitLoop = function()
              win:Disconnect(wx.wxID_ANY, wx.wxID_ANY, wx.wxEVT_IDLE)
              win:Disconnect(wx.wxID_ANY, wx.wxID_ANY, wx.wxEVT_TIMER)
              app:ExitMainLoop()
            end
            win:Connect(wx.wxEVT_IDLE, exitLoop)
            win:Connect(wx.wxEVT_TIMER, exitLoop)
            app:MainLoop()
          end
        elseif mobdebug.yield then mobdebug.yield()
        end
      elseif not line and err == "closed" then
        error("Debugger connection unexpectedly closed", 0)
      else
        -- if there is something in the pending buffer, prepend it to the line
        if buf then line = buf .. line; buf = nil end
        break
      end
    end
    if server.settimeout then server:settimeout() end -- back to blocking
    command = string.sub(line, string.find(line, "^[A-Z]+"))
    if command == "SETB" then
      local _, _, _, file, line = string.find(line, "^([A-Z]+)%s+(.-)%s+(%d+)%s*$")
      if file and line then
        set_breakpoint(file, tonumber(line))
        server:send("200 OK\n")
      else
        server:send("400 Bad Request\n")
      end
    elseif command == "DELB" then
      local _, _, _, file, line = string.find(line, "^([A-Z]+)%s+(.-)%s+(%d+)%s*$")
      if file and line then
        remove_breakpoint(file, tonumber(line))
        server:send("200 OK\n")
      else
        server:send("400 Bad Request\n")
      end
    elseif command == "EXEC" then
      local _, _, chunk = string.find(line, "^[A-Z]+%s+(.+)$")
      if chunk then 
        local func, res = loadstring(chunk)
        local status
        if func then
          setfenv(func, eval_env)
          status, res = stringify_results(pcall(func))
        end
        if status then
          server:send("200 OK " .. #res .. "\n")
          server:send(res)
        else
          server:send("401 Error in Expression " .. #res .. "\n")
          server:send(res)
        end
      else
        server:send("400 Bad Request\n")
      end
    elseif command == "LOAD" then
      local _, _, size, name = string.find(line, "^[A-Z]+%s+(%d+)%s+(%S.-)%s*$")
      size = tonumber(size)

      if abort == nil then -- no LOAD/RELOAD allowed inside start()
        if size > 0 then server:receive(size) end
        if sfile and sline then
          server:send("201 Started " .. sfile .. " " .. sline .. "\n")
        else
          server:send("200 OK 0\n")
        end
      else
        -- reset environment to allow required modules to load again
        -- remove those packages that weren't loaded when debugger started
        for k in pairs(package.loaded) do
          if not loaded[k] then package.loaded[k] = nil end
        end

        if size == 0 and name == '-' then -- RELOAD the current script being debugged
          server:send("200 OK 0\n")
          coroutine.yield("load")
        else
          -- receiving 0 bytes blocks (at least in luasocket 2.0.2), so skip reading
          local chunk = size == 0 and "" or server:receive(size)
          if chunk then -- LOAD a new script for debugging
            local func, res = loadstring(chunk, "@"..name)
            if func then
              server:send("200 OK 0\n")
              debugee = func
              coroutine.yield("load")
            else
              server:send("401 Error in Expression " .. #res .. "\n")
              server:send(res)
            end
          else
            server:send("400 Bad Request\n")
          end
        end
      end
    elseif command == "SETW" then
      local _, _, exp = string.find(line, "^[A-Z]+%s+(.+)%s*$")
      if exp then 
        local func, res = loadstring("return(" .. exp .. ")")
        if func then
          watchescnt = watchescnt + 1
          local newidx = #watches + 1
          watches[newidx] = func
          server:send("200 OK " .. newidx .. "\n") 
        else
          server:send("401 Error in Expression " .. #res .. "\n")
          server:send(res)
        end
      else
        server:send("400 Bad Request\n")
      end
    elseif command == "DELW" then
      local _, _, index = string.find(line, "^[A-Z]+%s+(%d+)%s*$")
      index = tonumber(index)
      if index > 0 and index <= #watches then
        watchescnt = watchescnt - (watches[index] ~= emptyWatch and 1 or 0)
        watches[index] = emptyWatch
        server:send("200 OK\n")
      else
        server:send("400 Bad Request\n")
      end
    elseif command == "RUN" then
      server:send("200 OK\n")

      local ev, vars, file, line, idx_watch = coroutine.yield()
      eval_env = vars
      if ev == events.BREAK then
        server:send("202 Paused " .. file .. " " .. line .. "\n")
      elseif ev == events.WATCH then
        server:send("203 Paused " .. file .. " " .. line .. " " .. idx_watch .. "\n")
      elseif ev == events.RESTART then
        -- nothing to do
      else
        server:send("401 Error in Execution " .. #file .. "\n")
        server:send(file)
      end
    elseif command == "STEP" then
      server:send("200 OK\n")
      step_into = true

      local ev, vars, file, line, idx_watch = coroutine.yield()
      eval_env = vars
      if ev == events.BREAK then
        server:send("202 Paused " .. file .. " " .. line .. "\n")
      elseif ev == events.WATCH then
        server:send("203 Paused " .. file .. " " .. line .. " " .. idx_watch .. "\n")
      elseif ev == events.RESTART then
        -- nothing to do
      else
        server:send("401 Error in Execution " .. #file .. "\n")
        server:send(file)
      end
    elseif command == "OVER" or command == "OUT" then
      server:send("200 OK\n")
      step_over = true
      
      -- OVER and OUT are very similar except for 
      -- the stack level value at which to stop
      if command == "OUT" then step_level = stack_level - 1
      else step_level = stack_level end

      local ev, vars, file, line, idx_watch = coroutine.yield()
      eval_env = vars
      if ev == events.BREAK then
        server:send("202 Paused " .. file .. " " .. line .. "\n")
      elseif ev == events.WATCH then
        server:send("203 Paused " .. file .. " " .. line .. " " .. idx_watch .. "\n")
      elseif ev == events.RESTART then
        -- nothing to do
      else
        server:send("401 Error in Execution " .. #file .. "\n")
        server:send(file)
      end
    elseif command == "BASEDIR" then
      local _, _, dir = string.find(line, "^[A-Z]+%s+(.+)%s*$")
      if dir then
        basedir = iscasepreserving and string.lower(dir) or dir
        -- reset cached source as it may change with basedir
        lastsource = nil
        server:send("200 OK\n")
      else
        server:send("400 Bad Request\n")
      end
    elseif command == "SUSPEND" then
      -- do nothing; it already fulfilled its role
    elseif command == "STACK" then
      -- first check if we can execute the stack command
      -- as it requires yielding back to debug_hook it cannot be executed
      -- if we have not seen the hook yet as happens after start().
      -- in this case we simply return an empty result
      local vars, ev = {}
      if seen_hook then
        ev, vars = coroutine.yield("stack")
      end
      if ev and ev ~= events.STACK then
        server:send("401 Error in Execution " .. #vars .. "\n")
        server:send(vars)
      else
        local ok, res = pcall(serpent.dump, vars, {nocode = true, sparse = false})
        if ok then
          server:send("200 OK " .. res .. "\n")
        else
          server:send("401 Error in Execution " .. #res .. "\n")
          server:send(res)
        end
      end
    elseif command == "OUTPUT" then
      local _, _, stream, mode = string.find(line, "^[A-Z]+%s+(%w+)%s+([dcr])%s*$")
      if stream and mode and stream == "stdout" then
        -- assign "print" in the global environment
        genv.print = mode == 'd' and iobase.print or coroutine.wrap(function(...)
          -- wrapping into coroutine.wrap protects this function from
          -- being stepped through in the debugger
          local tbl = {...}
          while true do
            if mode == 'c' then iobase.print(unpack(tbl)) end
            for n = 1, #tbl do
              tbl[n] = select(2, pcall(serpent.line, tbl[n], {nocode = true, comment = false})) end
            local file = table.concat(tbl, "\t").."\n"
            server:send("204 Output " .. stream .. " " .. #file .. "\n" .. file)
            tbl = {coroutine.yield()}
          end
        end)
        server:send("200 OK\n")
      else
        server:send("400 Bad Request\n")
      end
    elseif command == "EXIT" then
      server:send("200 OK\n")
      coroutine.yield("exit")
    else
      server:send("400 Bad Request\n")
    end
  end
end

local function connect(controller_host, controller_port)
  return (socket.connect4 or socket.connect)(controller_host, controller_port)
end

local function isrunning()
  return coro_debugger and coroutine.status(coro_debugger) == 'suspended'
end

local lasthost, lastport

-- Starts a debug session by connecting to a controller
local function start(controller_host, controller_port)
  -- only one debugging session can be run (as there is only one debug hook)
  if isrunning() then return end

  lasthost = controller_host or lasthost
  lastport = controller_port or lastport

  controller_host = lasthost or "localhost"
  controller_port = lastport or mobdebug.port

  local err
  server, err = (socket.connect4 or socket.connect)(controller_host, controller_port)
  if server then
    -- correct stack depth which already has some calls on it
    -- so it doesn't go into negative when those calls return
    -- as this breaks subsequence checks in stack_depth().
    -- start from 16th frame, which is sufficiently large for this check.
    stack_level = stack_depth(16)

    -- provide our own traceback function to report the error remotely
    do
      local dtraceback = debug.traceback
      debug.traceback = function (...)
        if select('#', ...) >= 1 then
          local err, lvl = ...
          if err and type(err) ~= 'thread' then
            local trace = dtraceback(err, (lvl or 2)+1)
            if genv.print == iobase.print then -- no remote redirect
              return trace
            else
              genv.print(trace) -- report the error remotely
              return -- don't report locally to avoid double reporting
            end
          end
        end
        -- direct call to debug.traceback: return the original.
        -- debug.traceback(nil, level) doesn't work in Lua 5.1
        -- (http://lua-users.org/lists/lua-l/2011-06/msg00574.html), so
        -- simply remove first frame from the stack trace
        return (dtraceback(...):gsub("(stack traceback:\n)[^\n]*\n", "%1"))
      end
    end
    coro_debugger = coroutine.create(debugger_loop)
    debug.sethook(debug_hook, "lcr")
    seen_hook = nil -- reset in case the last start() call was refused
    step_into = true -- start with step command
    return true
  else
    print(("Could not connect to %s:%s: %s")
      :format(controller_host, controller_port, err or "unknown error"))
  end
end

local function controller(controller_host, controller_port, scratchpad)
  -- only one debugging session can be run (as there is only one debug hook)
  if isrunning() then return end

  lasthost = controller_host or lasthost
  lastport = controller_port or lastport

  controller_host = lasthost or "localhost"
  controller_port = lastport or mobdebug.port

  local exitonerror = not scratchpad
  local err
  server, err = (socket.connect4 or socket.connect)(controller_host, controller_port)
  if server then
    local function report(trace, err)
      local msg = err .. "\n" .. trace
      server:send("401 Error in Execution " .. #msg .. "\n")
      server:send(msg)
      return err
    end

    seen_hook = true -- allow to accept all commands
    coro_debugger = coroutine.create(debugger_loop)

    while true do
      step_into = true -- start with step command
      abort = false -- reset abort flag from the previous loop
      if scratchpad then checkcount = mobdebug.checkcount end -- force suspend right away

      coro_debugee = coroutine.create(debugee)
      debug.sethook(coro_debugee, debug_hook, "lcr")
      local status, err = coroutine.resume(coro_debugee)

      -- was there an error or is the script done?
      -- 'abort' state is allowed here; ignore it
      if abort then
        if tostring(abort) == 'exit' then break end
      else
        if status then -- normal execution is done
          break
        elseif err and not tostring(err):find(deferror) then
          -- report the error back
          -- err is not necessarily a string, so convert to string to report
          report(debug.traceback(coro_debugee), tostring(err))
          if exitonerror then break end
          -- resume once more to clear the response the debugger wants to send
          -- need to use capture_vars(2) as three would be the level of
          -- the caller for controller(), but because of the tail call,
          -- the caller may not exist;
          -- This is not entirely safe as the user may see the local
          -- variable from console, but they will be reset anyway.
          -- This functionality is used when scratchpad is paused to
          -- gain access to remote console to modify global variables.
          local status, err = coroutine.resume(coro_debugger, events.RESTART, capture_vars(2))
          if not status or status and err == "exit" then break end
        end
      end
    end
  else
    print(("Could not connect to %s:%s: %s")
      :format(controller_host, controller_port, err or "unknown error"))
    return false
  end
  return true
end

local function scratchpad(controller_host, controller_port)
  return controller(controller_host, controller_port, true)
end

local function loop(controller_host, controller_port)
  return controller(controller_host, controller_port, false)
end

local function on()
  if not (isrunning() and server) then return end

  -- main is set to true under Lua5.2 for the "main" chunk.
  -- Lua5.1 returns co as `nil` in that case.
  local co, main = coroutine.running()
  if main then co = nil end
  if co then
    coroutines[co] = true
    debug.sethook(co, debug_hook, "lcr")
  else
    if jit then coroutines.main = true end
    debug.sethook(debug_hook, "lcr")
  end
end

local function off()
  if not (isrunning() and server) then return end

  -- main is set to true under Lua5.2 for the "main" chunk.
  -- Lua5.1 returns co as `nil` in that case.
  local co, main = coroutine.running()
  if main then co = nil end

  -- don't remove coroutine hook under LuaJIT as there is only one (global) hook
  if co then
    coroutines[co] = false
    if not jit then debug.sethook(co) end
  else
    if jit then coroutines.main = false end
    if not jit then debug.sethook() end
  end

  -- check if there is any thread that is still being debugged under LuaJIT;
  -- if not, turn the debugging off
  if jit then
    local remove = true
    for co, debugged in pairs(coroutines) do
      if debugged then remove = false; break end
    end
    if remove then debug.sethook() end
  end
end

-- Handles server debugging commands 
local function handle(params, client, options)
  local _, _, command = string.find(params, "^([a-z]+)")
  local file, line, watch_idx
  if command == "run" or command == "step" or command == "out"
  or command == "over" or command == "exit" then
    client:send(string.upper(command) .. "\n")
    client:receive() -- this should consume the first '200 OK' response
    while true do
      local done = true
      local breakpoint = client:receive()
      if not breakpoint then
        print("Program finished")
        os.exit()
        return -- use return here for those cases where os.exit() is not wanted
      end
      local _, _, status = string.find(breakpoint, "^(%d+)")
      if status == "200" then
        -- don't need to do anything
      elseif status == "202" then
        _, _, file, line = string.find(breakpoint, "^202 Paused%s+(.-)%s+(%d+)%s*$")
        if file and line then
          print("Paused at file " .. file .. " line " .. line)
        end
      elseif status == "203" then
        _, _, file, line, watch_idx = string.find(breakpoint, "^203 Paused%s+(.-)%s+(%d+)%s+(%d+)%s*$")
        if file and line and watch_idx then
          print("Paused at file " .. file .. " line " .. line .. " (watch expression " .. watch_idx .. ": [" .. watches[watch_idx] .. "])")
        end
      elseif status == "204" then
        local _, _, stream, size = string.find(breakpoint, "^204 Output (%w+) (%d+)$")
        if stream and size then
          local msg = client:receive(tonumber(size))
          print(msg)
          if outputs[stream] then outputs[stream](msg) end
          -- this was just the output, so go back reading the response
          done = false
        end
      elseif status == "401" then
        local _, _, size = string.find(breakpoint, "^401 Error in Execution (%d+)$")
        if size then
          local msg = client:receive(tonumber(size))
          print("Error in remote application: " .. msg)
          os.exit(1)
          return nil, nil, msg -- use return here for those cases where os.exit() is not wanted
        end
      else
        print("Unknown error")
        os.exit(1)
        -- use return here for those cases where os.exit() is not wanted
        return nil, nil, "Debugger error: unexpected response '" .. breakpoint .. "'"
      end
      if done then break end
    end
  elseif command == "setb" then
    _, _, _, file, line = string.find(params, "^([a-z]+)%s+(.-)%s+(%d+)%s*$")
    if file and line then
      -- if this is a file name, and not a file source
      if not file:find('^".*"$') then
        file = string.gsub(file, "\\", "/") -- convert slash
        file = removebasedir(file, basedir)
      end
      client:send("SETB " .. file .. " " .. line .. "\n")
      if client:receive() == "200 OK" then
        set_breakpoint(file, line)
      else
        print("Error: breakpoint not inserted")
      end
    else
      print("Invalid command")
    end
  elseif command == "setw" then
    local _, _, exp = string.find(params, "^[a-z]+%s+(.+)$")
    if exp then
      client:send("SETW " .. exp .. "\n")
      local answer = client:receive()
      local _, _, watch_idx = string.find(answer, "^200 OK (%d+)%s*$")
      if watch_idx then
        watches[watch_idx] = exp
        print("Inserted watch exp no. " .. watch_idx)
      else
        local _, _, size = string.find(answer, "^401 Error in Expression (%d+)$")
        if size then
          local err = client:receive(tonumber(size)):gsub(".-:%d+:%s*","")
          print("Error: watch expression not set: " .. err)
        else
          print("Error: watch expression not set")
        end
      end
    else
      print("Invalid command")
    end
  elseif command == "delb" then
    _, _, _, file, line = string.find(params, "^([a-z]+)%s+(.-)%s+(%d+)%s*$")
    if file and line then
      -- if this is a file name, and not a file source
      if not file:find('^".*"$') then
        file = string.gsub(file, "\\", "/") -- convert slash
        file = removebasedir(file, basedir)
      end
      client:send("DELB " .. file .. " " .. line .. "\n")
      if client:receive() == "200 OK" then 
        remove_breakpoint(file, line)
      else
        print("Error: breakpoint not removed")
      end
    else
      print("Invalid command")
    end
  elseif command == "delallb" then
    for line, breaks in pairs(breakpoints) do
      for file, _ in pairs(breaks) do
        client:send("DELB " .. file .. " " .. line .. "\n")
        if client:receive() == "200 OK" then
          remove_breakpoint(file, line)
        else
          print("Error: breakpoint at file " .. file .. " line " .. line .. " not removed")
        end
      end
    end
  elseif command == "delw" then
    local _, _, index = string.find(params, "^[a-z]+%s+(%d+)%s*$")
    if index then
      client:send("DELW " .. index .. "\n")
      if client:receive() == "200 OK" then 
        watches[index] = nil
      else
        print("Error: watch expression not removed")
      end
    else
      print("Invalid command")
    end
  elseif command == "delallw" then
    for index, exp in pairs(watches) do
      client:send("DELW " .. index .. "\n")
      if client:receive() == "200 OK" then 
        watches[index] = nil
      else
        print("Error: watch expression at index " .. index .. " [" .. exp .. "] not removed")
      end
    end    
  elseif command == "eval" or command == "exec" 
      or command == "load" or command == "loadstring"
      or command == "reload" then
    local _, _, exp = string.find(params, "^[a-z]+%s+(.+)$")
    if exp or (command == "reload") then 
      if command == "eval" or command == "exec" then
        exp = (exp:gsub("%-%-%[(=*)%[.-%]%1%]", "") -- remove comments
                  :gsub("%-%-.-\n", " ") -- remove line comments
                  :gsub("\n", " ")) -- convert new lines
        if command == "eval" then exp = "return " .. exp end
        client:send("EXEC " .. exp .. "\n")
      elseif command == "reload" then
        client:send("LOAD 0 -\n")
      elseif command == "loadstring" then
        local _, _, _, file, lines = string.find(exp, "^([\"'])(.-)%1%s+(.+)")
        if not file then
           _, _, file, lines = string.find(exp, "^(%S+)%s+(.+)")
        end
        client:send("LOAD " .. #lines .. " " .. file .. "\n")
        client:send(lines)
      else
        local file = io.open(exp, "r")
        if not file and pcall(require, "winapi") then
          -- if file is not open and winapi is there, try with a short path;
          -- this may be needed for unicode paths on windows
          winapi.set_encoding(winapi.CP_UTF8)
          file = io.open(winapi.short_path(exp), "r")
        end
        if not file then error("Cannot open file " .. exp) end
        -- read the file and remove the shebang line as it causes a compilation error
        local lines = file:read("*all"):gsub("^#!.-\n", "\n")
        file:close()

        local file = string.gsub(exp, "\\", "/") -- convert slash
        file = removebasedir(file, basedir)
        client:send("LOAD " .. #lines .. " " .. file .. "\n")
        if #lines > 0 then client:send(lines) end
      end
      while true do
        local params, err = client:receive()
        if not params then
          return nil, nil, "Debugger connection " .. (err or "error")
        end
        local done = true
        local _, _, status, len = string.find(params, "^(%d+).-%s+(%d+)%s*$")
        if status == "200" then
          len = tonumber(len)
          if len > 0 then
            local status, res
            local str = client:receive(len)
            -- handle serialized table with results
            local func, err = loadstring(str)
            if func then
              status, res = pcall(func)
              if not status then err = res
              elseif type(res) ~= "table" then
                err = "received "..type(res).." instead of expected 'table'"
              end
            end
            if err then
              print("Error in processing results: " .. err)
              return nil, nil, "Error in processing results: " .. err
            end
            print(unpack(res))
            return res[1], res
          end
        elseif status == "201" then
          _, _, file, line = string.find(params, "^201 Started%s+(.-)%s+(%d+)%s*$")
        elseif status == "202" or params == "200 OK" then
          -- do nothing; this only happens when RE/LOAD command gets the response
          -- that was for the original command that was aborted
        elseif status == "204" then
          local _, _, stream, size = string.find(params, "^204 Output (%w+) (%d+)$")
          if stream and size then
            local msg = client:receive(tonumber(size))
            print(msg)
            if outputs[stream] then outputs[stream](msg) end
            -- this was just the output, so go back reading the response
            done = false
          end
        elseif status == "401" then
          len = tonumber(len)
          local res = client:receive(len)
          print("Error in expression: " .. res)
          return nil, nil, res
        else
          print("Unknown error")
          return nil, nil, "Debugger error: unexpected response after EXEC/LOAD '" .. params .. "'"
        end
        if done then break end
      end
    else
      print("Invalid command")
    end
  elseif command == "listb" then
    for l, v in pairs(breakpoints) do
      for f in pairs(v) do
        print(f .. ": " .. l)
      end
    end
  elseif command == "listw" then
    for i, v in pairs(watches) do
      print("Watch exp. " .. i .. ": " .. v)
    end    
  elseif command == "suspend" then
    client:send("SUSPEND\n")
  elseif command == "stack" then
    client:send("STACK\n")
    local resp = client:receive()
    local _, _, status, res = string.find(resp, "^(%d+)%s+%w+%s+(.+)%s*$")
    if status == "200" then
      local func, err = loadstring(res)
      if func == nil then
        print("Error in stack information: " .. err)
        return nil, nil, err
      end
      local ok, stack = pcall(func)
      if not ok then
        print("Error in stack information: " .. stack)
        return nil, nil, stack
      end
      for _,frame in ipairs(stack) do
        print(serpent.line(frame[1], {comment = false}))
      end
      return stack
    elseif status == "401" then
      local _, _, len = string.find(resp, "%s+(%d+)%s*$")
      len = tonumber(len)
      local res = len > 0 and client:receive(len) or "Invalid stack information."
      print("Error in expression: " .. res)
      return nil, nil, res
    else
      print("Unknown error")
      return nil, nil, "Debugger error: unexpected response after STACK"
    end
  elseif command == "output" then
    local _, _, stream, mode = string.find(params, "^[a-z]+%s+(%w+)%s+([dcr])%s*$")
    if stream and mode then
      client:send("OUTPUT "..stream.." "..mode.."\n")
      local resp = client:receive()
      local _, _, status = string.find(resp, "^(%d+)%s+%w+%s*$")
      if status == "200" then
        print("Stream "..stream.." redirected")
        outputs[stream] = type(options) == 'table' and options.handler or nil
      else
        print("Unknown error")
        return nil, nil, "Debugger error: can't redirect "..stream
      end
    else
      print("Invalid command")
    end
  elseif command == "basedir" then
    local _, _, dir = string.find(params, "^[a-z]+%s+(.+)$")
    if dir then
      dir = string.gsub(dir, "\\", "/") -- convert slash
      if not string.find(dir, "/$") then dir = dir .. "/" end

      local remdir = dir:match("\t(.+)")
      if remdir then dir = dir:gsub("/?\t.+", "/") end
      basedir = dir

      client:send("BASEDIR "..(remdir or dir).."\n")
      local resp = client:receive()
      local _, _, status = string.find(resp, "^(%d+)%s+%w+%s*$")
      if status == "200" then
        print("New base directory is " .. basedir)
      else
        print("Unknown error")
        return nil, nil, "Debugger error: unexpected response after BASEDIR"
      end
    else
      print(basedir)
    end
  elseif command == "help" then
    print("setb <file> <line>    -- sets a breakpoint")
    print("delb <file> <line>    -- removes a breakpoint")
    print("delallb               -- removes all breakpoints")
    print("setw <exp>            -- adds a new watch expression")
    print("delw <index>          -- removes the watch expression at index")
    print("delallw               -- removes all watch expressions")
    print("run                   -- runs until next breakpoint")
    print("step                  -- runs until next line, stepping into function calls")
    print("over                  -- runs until next line, stepping over function calls")
    print("out                   -- runs until line after returning from current function")
    print("listb                 -- lists breakpoints")
    print("listw                 -- lists watch expressions")
    print("eval <exp>            -- evaluates expression on the current context and returns its value")
    print("exec <stmt>           -- executes statement on the current context")
    print("load <file>           -- loads a local file for debugging")
    print("reload                -- restarts the current debugging session")
    print("stack                 -- reports stack trace")
    print("output stdout <d|c|r> -- capture and redirect io stream (default|copy|redirect)")
    print("basedir [<path>]      -- sets the base path of the remote application, or shows the current one")
    print("exit                  -- exits debugger")
  else
    local _, _, spaces = string.find(params, "^(%s*)$")
    if not spaces then
      print("Invalid command")
      return nil, nil, "Invalid command"
    end
  end
  return file, line
end

-- Starts debugging server
local function listen(host, port)
  host = host or "*"
  port = port or mobdebug.port

  local socket = require "socket"

  print("Lua Remote Debugger")
  print("Run the program you wish to debug")

  local server = socket.bind(host, port)
  local client = server:accept()

  client:send("STEP\n")
  client:receive()

  local breakpoint = client:receive()
  local _, _, file, line = string.find(breakpoint, "^202 Paused%s+(.-)%s+(%d+)%s*$")
  if file and line then
    print("Paused at file " .. file )
    print("Type 'help' for commands")
  else
    local _, _, size = string.find(breakpoint, "^401 Error in Execution (%d+)%s*$")
    if size then
      print("Error in remote application: ")
      print(client:receive(size))
    end
  end

  while true do
    io.write("> ")
    local line = io.read("*line")
    handle(line, client)
  end
end

local cocreate
local function coro()
  if cocreate then return end -- only set once
  cocreate = cocreate or coroutine.create
  coroutine.create = function(f, ...)
    return cocreate(function(...)
      require("mobdebug").on()
      return f(...)
    end, ...)
  end
end

local moconew
local function moai()
  if moconew then return end -- only set once
  moconew = moconew or (MOAICoroutine and MOAICoroutine.new)
  if not moconew then return end
  MOAICoroutine.new = function(...)
    local thread = moconew(...)
    -- need to support both thread.run and getmetatable(thread).run, which
    -- was used in earlier MOAI versions
    local mt = thread.run and thread or getmetatable(thread)
    local patched = mt.run
    mt.run = function(self, f, ...)
      return patched(self,  function(...)
        require("mobdebug").on()
        return f(...)
      end, ...)
    end
    return thread
  end
end

-- this is a function that removes all hooks and closes the socket to
-- report back to the controller that the debugging is done.
-- the script that called `done` can still continue.
local function done()
  if not (isrunning() and server) then return end

  if not jit then
    for co, debugged in pairs(coroutines) do
      if debugged then debug.sethook(co) end
    end
  end

  debug.sethook()
  server:close()

  coro_debugger = nil -- to make sure isrunning() returns `false`
  seen_hook = nil -- to make sure that the next start() call works
  abort = nil -- to make sure that callback calls use proper "abort" value
end

-- make public functions available
mobdebug.listen = listen
mobdebug.loop = loop
mobdebug.scratchpad = scratchpad
mobdebug.handle = handle
mobdebug.connect = connect
mobdebug.start = start
mobdebug.on = on
mobdebug.off = off
mobdebug.moai = moai
mobdebug.coro = coro
mobdebug.done = done
mobdebug.line = serpent.line
mobdebug.dump = serpent.dump
mobdebug.yield = nil -- callback

-- this is needed to make "require 'modebug'" to work when mobdebug
-- module is loaded manually
package.loaded.mobdebug = mobdebug

return mobdebug
