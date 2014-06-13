--[[
Load a mo file, retuan a lua function or table.
A sample and description(in chinese): http://zengrong.net/post/1986.htm 

@see http://lua-users.org/lists/lua-l/2010-04/msg00005.html
Modifier zrong(zengrong.net)
Creation 2013-11-29

usage:

    local mo_data=assert(require("utils.Gettext").loadMOFromFile("main.mo"))
    print(mo_data["hello"])
   -- 你好
    print(mo_data["world"])
   -- nil

then you'll get a kind of gettext function:

    local gettext=assert(require("utils.Gettext").gettextFromFile("main.mo"))
    print(gettext("hello"))
   -- 你好
    print(gettext("world"))
    -- world

with a slight modification this will be ready-to-use for the xgettext tool:

    _ = assert(require("utils.Gettext").gettextFromFile("main.mo"))
    print(_("hello"))
    print(_("world"))
]]

-- Original description
-----------------------------------------------------------
-- load an mo file and return a lua table
-- @param mo_file name of the file to load
-- @return table on success
-- @return nil,string on failure
-- @copyright J.J?rgen von Bargen
-- @licence I provide this as public domain
-- @see http://www.gnu.org/software/hello/manual/gettext/MO-Files.html
-----------------------------------------------------------

local Gettext = {}

function Gettext._getFileData(mo_file)
	--- use lua io, cannot use in Android
	--[[
    local fd,err=io.open(mo_file,"rb")
    if not fd then return nil,err end
    local mo_data=fd:read("*all")
    fd:close()
	--]]

	--- use quick-cocos2d-x CCFileUtils, cross-platform
	local mo_data = CCFileUtils:sharedFileUtils():getFileData(mo_file)
	return mo_data
end

function Gettext.loadMOFromFile(mo_file)
	return Gettext.parseData(Gettext._getFileData(mo_file))
end

function Gettext.gettextFromFile(mo_file)
	return Gettext.gettext(Gettext._getFileData(mo_file))
end

function Gettext.gettext(mo_data)
	local __hash = Gettext.parseData(mo_data)
    return function(text)
        return __hash[text] or text
    end
end

function Gettext.parseData(mo_data)
    --------------------------------
    -- precache some functions
    --------------------------------
    local byte=string.byte
    local sub=string.sub

    --------------------------------
    -- check format
    --------------------------------
    local peek_long --localize
    local magic=sub(mo_data,1,4)
    -- intel magic 0xde120495
    if magic=="\222\018\004\149" then
        peek_long=function(offs)
            local a,b,c,d=byte(mo_data,offs+1,offs+4)
            return ((d*256+c)*256+b)*256+a
        end
    -- motorola magic = 0x950412de
    elseif magic=="\149\004\018\222" then
        peek_long=function(offs)
            local a,b,c,d=byte(mo_data,offs+1,offs+4)
            return ((a*256+b)*256+c)*256+d
        end
    else
        return nil,"no valid mo-file"
    end

    --------------------------------
    -- version
    --------------------------------
    local V=peek_long(4)
    if V~=0 then
        return nul,"unsupported version"
    end

    ------------------------------
    -- get number of offsets of table
    ------------------------------
    local N,O,T=peek_long(8),peek_long(12),peek_long(16)
    ------------------------------
    -- traverse and get strings
    ------------------------------
    local hash={}
    for nstr=1,N do
        local ol,oo=peek_long(O),peek_long(O+4) O=O+8
        local tl,to=peek_long(T),peek_long(T+4) T=T+8
        hash[sub(mo_data,oo+1,oo+ol)]=sub(mo_data,to+1,to+tl)
    end
    return hash    -- return table
end

return Gettext
