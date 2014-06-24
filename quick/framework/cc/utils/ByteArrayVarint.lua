--[[
Serialzation bytes stream use varint encoding of google protocol buffer, I implemented it in ActionScript. 
It depends on BitOp.
A description: https://github.com/zrong/lua#ByteArrayVarint

@see https://developers.google.com/protocol-buffers/docs/encoding
@see https://github.com/zrong/as3/blob/master/src/org/zengrong/utils/ByteArrayVariant.as
@see http://bitop.luajit.org/index.html
@author zrong(zengrong.net)
Creation: 2013-11-14
]]
local ByteArrayVarint = class("BitVaiant", import(".ByteArray"))

require("bit")

function ByteArrayVarint:ctor(__endian)
	self._endian = __endian
	self._buf = {}
	self._pos = 1
end

function ByteArrayVarint:readVInt()
	local __v = self:_decodeVarint()
	return self:_zigZagDecode(__v)
end

function  ByteArrayVarint:writeVInt(__vint)
	local __v = self:_zigZagEncode(__vint)
	self:_encodeVarint(__v)
	return self
end

function ByteArrayVarint:readUVInt()
	return self:_decodeVarint()
end

function ByteArrayVarint:writeUVInt(__uvint)
	self:_encodeVarint(__uvint)
	return self
end

function ByteArrayVarint:readStringUVInt()
	local __len = self:readUVInt()
	return self:readStringBytes(__len)
end

function ByteArrayVarint:writeStringUVInt(__str)
	self:writeUVInt(#__str)
	self:writeStringBytes(__str)
	return self
end

--- Convert signed int to unsigned int
-- After converting, 1=2, -1=1, -2=3, 2=4
function ByteArrayVarint:_zigZagEncode(__value)
	if __value >= 0 then return bit.lshift(__value, 1) end
	return bit.bxor(bit.lshift(__value, 1), bit.bnot(0))
end

function ByteArrayVarint:_zigZagDecode(__value)
	if bit.band(__value, 0x1) == 0 then return bit.rshift(__value, 1) end
	return bit.bxor(bit.rshift(__value, 1), bit.bnot(0))
end

function ByteArrayVarint:_encodeVarint(__value)
	assert(type(__value) == "number", "Value to encode must be a number!")
	--[[ 2013-11-19 zrong
	Our server need a number greater than 32bit, but BitOp only support 32bit signed nubmers. 
	Client will get a negative number if server send a number greater than 21 4748 3648.
	But, when client send the number to server use writeUVInt, server will get a positive number.
	Yes, it can get the number sent to client.
	Thus, we discard the estimating for __value.
	]]
	-- if __value < 0 then __value = 0 end
	local __bytes = bit.band(__value ,0x7f)
	__value = bit.rshift(__value, 7)
	while __value ~= 0 do
		self:writeByte(bit.bor(0x80, __bytes))
		__bytes = bit.band(__value , 0x7f)
		__value = bit.rshift(__value, 7)
		-- print(__bytes, __value)
	end
	self:writeByte(__bytes)
end

function ByteArrayVarint:_decodeVarint()
	local __result = 0
	local __shift = 0
	local __byte = nil
	while self._pos <= #self._buf do
		__byte = self:readByte()
		__result = bit.bor(__result, bit.lshift(bit.band(__byte, 0x7f), __shift))
		if bit.band(__byte, 0x80) == 0 then
			return __result
		end
		__shift = __shift + 7
		-- BitOp do not support bitwise greater than 32bit
		assert(__shift<32, "Varint decode error! 32bit bitwise is unavailable in BitOp!")
	end
	error("Read variant at EOF!")
end

return ByteArrayVarint
