--[[
Serialzation bytes stream like ActionScript flash.utils.ByteArray.
It depends on lpack.
A sample: https://github.com/zrong/lua#ByteArray

@see http://underpop.free.fr/l/lua/lpack/
@see http://help.adobe.com/en_US/FlashPlatform/reference/actionscript/3/flash/utils/ByteArray.html
@author zrong(zengrong.net)

Creation 2013-11-14
Last Modification 2014-01-01
]]
local ByteArray = class("ByteArray")

ByteArray.ENDIAN_LITTLE = "ENDIAN_LITTLE"
ByteArray.ENDIAN_BIG = "ENDIAN_BIG"
ByteArray.radix = {[10]="%03u",[8]="%03o",[16]="%02X"}

require("pack")

--- Return a string to display.
-- If self is ByteArray, read string from self.
-- Else, treat self as byte string.
-- @param __radix radix of display, value is 8, 10 or 16, default is 10.
-- @param __separator default is " ".
-- @return string, number
function ByteArray.toString(self, __radix, __separator)
	__radix = __radix or 16 
	__radix = ByteArray.radix[__radix] or "%02X"
	__separator = __separator or " "
	local __fmt = __radix..__separator
	local __format = function(__s)
		return string.format(__fmt, string.byte(__s))
	end
	if type(self) == "string" then
		return string.gsub(self, "(.)", __format)
	end
	local __bytes = {}
	for i=1,#self._buf do
		__bytes[i] = __format(self._buf[i])
	end
	return table.concat(__bytes) ,#__bytes
end

function ByteArray:ctor(__endian)
	self._endian = __endian
	self._buf = {}
	self._pos = 1
end

function ByteArray:getLen()
	return #self._buf
end

function ByteArray:getAvailable()
	return #self._buf - self._pos + 1
end

function ByteArray:getPos()
	return self._pos
end

function ByteArray:setPos(__pos)
	self._pos = __pos
	return self
end

function ByteArray:getEndian()
	return self._endian
end

function ByteArray:setEndian(__endian)
	self._endian = __endian
end

--- Get all byte array as a lua string.
-- Do not update position.
function ByteArray:getBytes(__offset, __length)
	__offset = __offset or 1
	__length = __length or #self._buf
	--printf("getBytes,offset:%u, length:%u", __offset, __length)
	return table.concat(self._buf, "", __offset, __length)
end

--- Get pack style string by lpack.
-- The result use ByteArray.getBytes to get is unavailable for lua socket.
-- E.g. the #self:_buf is 18, but #ByteArray.getBytes is 63.
-- I think the cause is the table.concat treat every item in ByteArray._buf as a general string, not a char.
-- So, I use lpack repackage the ByteArray._buf, theretofore, I must convert them to a byte number.
function ByteArray:getPack(__offset, __length)
	__offset = __offset or 1
	__length = __length or #self._buf
	local __t = {}
	for i=__offset,__length do
		__t[#__t+1] = string.byte(self._buf[i])
	end
	local __fmt = self:_getLC("b"..#__t)
	--print("fmt:", __fmt)
	local __s = string.pack(__fmt, unpack(__t))
	return __s
end

--- rawUnPack perform like lpack.pack, but return the ByteArray.
function ByteArray:rawPack(__fmt, ...)
	local __s = string.pack(__fmt, ...)
	self:writeBuf(__s)
	return self
end

--- rawUnPack perform like lpack.unpack, but it is only support FORMAT parameter.
-- Because ByteArray include a position itself, so we haven't to save another.
function ByteArray:rawUnPack(__fmt)
	-- read all of bytes.
	local __s = self:getBytes(self._pos)
	local __next, __val = string.unpack(__s, __fmt)
	-- update position of the ByteArray
	self._pos = self._pos + __next
	-- Alternate value and next
	return __val, __next
end

function ByteArray:readBool()
	-- When char > 256, the readByte method will show an error.
	-- So, we have to use readChar
	return self:readChar() ~= 0
end

function ByteArray:writeBool(__bool)
	if __bool then 
		self:writeByte(1)
	else
		self:writeByte(0)
	end
	return self
end

function ByteArray:readDouble()
	local __, __v = string.unpack(self:readBuf(8), self:_getLC("d"))
	return __v
end

function ByteArray:writeDouble(__double)
	local __s = string.pack( self:_getLC("d"), __double)
	self:writeBuf(__s)
	return self
end

function ByteArray:readFloat()
	local __, __v = string.unpack(self:readBuf(4), self:_getLC("f"))
	return __v
end

function ByteArray:writeFloat(__float)
	local __s = string.pack( self:_getLC("f"),  __float)
	self:writeBuf(__s)
	return self
end

function ByteArray:readInt()
	local __, __v = string.unpack(self:readBuf(4), self:_getLC("i"))
	return __v
end

function ByteArray:writeInt(__int)
	local __s = string.pack( self:_getLC("i"),  __int)
	self:writeBuf(__s)
	return self
end

function ByteArray:readUInt()
	local __, __v = string.unpack(self:readBuf(4), self:_getLC("I"))
	return __v
end

function ByteArray:writeUInt(__uint)
	local __s = string.pack(self:_getLC("I"), __uint)
	self:writeBuf(__s)
	return self
end

function ByteArray:readShort()
	local __, __v = string.unpack(self:readBuf(2), self:_getLC("h"))
	return __v
end

function ByteArray:writeShort(__short)
	local __s = string.pack( self:_getLC("h"),  __short)
	self:writeBuf(__s)
	return self
end

function ByteArray:readUShort()
	local __, __v = string.unpack(self:readBuf(2), self:_getLC("H"))
	return __v
end

function ByteArray:writeUShort(__ushort)
	local __s = string.pack(self:_getLC("H"),  __ushort)
	self:writeBuf(__s)
	return self
end

function ByteArray:readLong()
	local __, __v = string.unpack(self:readBuf(8), self:_getLC("l"))
	return __v
end

function ByteArray:writeLong(__long)
	local __s = string.pack( self:_getLC("l"),  __long)
	self:writeBuf(__s)
	return self
end

function ByteArray:readULong()
	local __, __v = string.unpack(self:readBuf(4), self:_getLC("L"))
	return __v
end


function ByteArray:writeULong(__ulong)
	local __s = string.pack( self:_getLC("L"), __ulong)
	self:writeBuf(__s)
	return self
end

function ByteArray:readUByte()
	local __, __val = string.unpack(self:readRawByte(), "b")
	return __val
end

function ByteArray:writeUByte(__ubyte)
	local __s = string.pack("b", __ubyte)
	self:writeBuf(__s)
	return self
end

function ByteArray:readLuaNumber(__number)
	local __, __v = string.unpack(self:readBuf(8), self:_getLC("n"))
	return __v
end

function ByteArray:writeLuaNumber(__number)
	local __s = string.pack(self:_getLC("n"), __number)
	self:writeBuf(__s)
	return self
end

function ByteArray:readStringBytes(__len)
	assert(__len, "Need a length of the string!")
	if __len == 0 then return "" end
	self:_checkAvailable()
	local __, __v = string.unpack(self:readBuf(__len), self:_getLC("A"..__len))
	return __v
end

function ByteArray:writeStringBytes(__string)
	local __s = string.pack(self:_getLC("A"), __string)
	self:writeBuf(__s)
	return self
end

--- DO NOT use this method, it's inefficient.
-- Alternatively use readStringBytes.
function ByteArray:readString(__len)
	assert(__len, "Need a length of the string!")
	if __len == 0 then return "" end
	self:_checkAvailable()
	local __bytes = ""
	for i=self._pos, #self._buf do
		local __byte = string.byte(self._buf[i])
		__bytes = __bytes .. string.char(__byte)
	end
	return __bytes
end

function ByteArray:writeString(__string)
	self:writeBuf(__string)
	return self
end

function ByteArray:readStringUInt()
	self:_checkAvailable()
	local __len = self:readUInt()
	return self:readStringBytes(__len)
end

function ByteArray:writeStringUInt(__string)
	self:writeUInt(#__string)
	self:writeStringBytes(__string)
	return self
end

--- The length of size_t in C/C++ is mutable.
-- In 64bit os, it is 8 bytes.
-- In 32bit os, it is 4 bytes.
function ByteArray:readStringSizeT()
	self:_checkAvailable()
	local __s = self:rawUnPack(self:_getLC("a"))
	return  __s
end

--- Perform rawPack() simply.
function ByteArray:writeStringSizeT(__string)
	self:rawPack(self:_getLC("a"), __string)
	return self
end

function ByteArray:readStringUShort()
	self:_checkAvailable()
	local __len = self:readUShort()
	return self:readStringBytes(__len)
end

function ByteArray:writeStringUShort(__string)
	local __s = string.pack(self:_getLC("P"), __string)
	self:writeBuf(__s)
	return self
end

--- Read some bytes from buf
-- @return a bit string
function ByteArray:readBytes(__bytes, __offset, __length)
	assert(iskindof(__bytes, "ByteArray"), "Need a ByteArray instance!")
	local __selfLen = #self._buf
	local __availableLen = __selfLen - self._pos
	__offset = __offset or 1
	if __offset > __selfLen then __offset = 1 end
	__length = __length or 0
	if __length == 0 or __length > __availableLen then __length = __availableLen end
	__bytes:setPos(__offset)
	for i=__offset,__offset+__length do
		__bytes:writeRawByte(self:readRawByte())
	end
end

--- Write some bytes into buf
function ByteArray:writeBytes(__bytes, __offset, __length)
	assert(iskindof(__bytes, "ByteArray"), "Need a ByteArray instance!")
	local __bytesLen = __bytes:getLen()
	if __bytesLen == 0 then return end
	__offset = __offset or 1
	if __offset > __bytesLen then __offset = 1 end
	local __availableLen = __bytesLen - __offset
	__length = __length or __availableLen
	if __length == 0 or __length > __availableLen then __length = __availableLen end
	local __oldPos = __bytes:getPos()
	__bytes:setPos(__offset)
	for i=__offset,__offset+__length do
		self:writeRawByte(__bytes:readRawByte())
	end
	__bytes:setPos(__oldPos)
	return self
end

--- Actionscript3 readByte == lpack readChar
-- A signed char
function ByteArray:readChar()
	local __, __val = string.unpack( self:readRawByte(), "c")
	return __val
end

function ByteArray:writeChar(__char)
	self:writeRawByte(string.pack("c", __char))
	return self
end

--- Use the lua string library to get a byte
-- A unsigned char
function ByteArray:readByte()
	return string.byte(self:readRawByte())
end

--- Use the lua string library to write a byte.
-- The byte is a number between 0 and 255, otherwise, the lua will get an error.
function ByteArray:writeByte(__byte)
	self:writeRawByte(string.char(__byte))
	return self
end

function ByteArray:readRawByte()
	self:_checkAvailable()
	local __byte = self._buf[self._pos]
	self._pos = self._pos + 1
	return __byte
end

function ByteArray:writeRawByte(__rawByte)
	if self._pos > #self._buf+1 then
		for i=#self._buf+1,self._pos-1 do
			self._buf[i] = string.char(0)
		end
	end
	self._buf[self._pos] = __rawByte
	self._pos = self._pos + 1
	return self
end

--- Read a byte array as string from current position, then update the position.
function ByteArray:readBuf(__len)
	--printf("readBuf,len:%u, pos:%u", __len, self._pos)
	local __ba = self:getBytes(self._pos, self._pos + __len - 1)
	self._pos = self._pos + __len
	return __ba
end

--- Write a encoded char array into buf
function ByteArray:writeBuf(__s)
	for i=1,#__s do
		self:writeRawByte(__s:sub(i))
	end
	return self
end

----------------------------------------
-- private
----------------------------------------
function ByteArray:_checkAvailable()
	assert(#self._buf >= self._pos, string.format("End of file was encountered. pos: %d, len: %d.", self._pos, #self._buf))
end

--- Get Letter Code
function ByteArray:_getLC(__fmt)
	__fmt = __fmt or ""
	if self._endian == ByteArray.ENDIAN_LITTLE then
		return "<"..__fmt
	elseif self._endian == ByteArray.ENDIAN_BIG then
		return ">"..__fmt
	end
	return "="..__fmt
end

return ByteArray
