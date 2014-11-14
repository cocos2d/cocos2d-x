cc.utils = require("framework.cc.utils.init")
local ByteArray = cc.utils.ByteArray
local ByteArrayVarint = cc.utils.ByteArrayVarint

local MainScene = class("MainScene", function()
    return display.newScene("MainScene")
end)

function MainScene:ctor()
	cc.ui.UIPushButton.new()
        :setButtonLabel(cc.ui.UILabel.new({text = "Compare lpack and ByteArray", size = 32}))
        :onButtonClicked(function()
            self:_onTest1()
        end)
        :align(display.CENTER, display.cx, display.top - 32)
        :addTo(self)

    cc.ui.UIPushButton.new()
        :setButtonLabel(cc.ui.UILabel.new({text = "Test bug 1", size = 32}))
        :onButtonClicked(function()
            self:_onTest2()
        end)
        :align(display.CENTER, display.cx, display.top - 64)
        :addTo(self)

    cc.ui.UIPushButton.new()
        :setButtonLabel(cc.ui.UILabel.new({text = "Test length of long", size = 32}))
        :onButtonClicked(function()
            self:_onTest3()
        end)
        :align(display.CENTER, display.cx, display.top - 96)
        :addTo(self)
end

function MainScene:_onTest1()
	local __pack = self:_getDataByLpack()
	local __ba1 = ByteArray.new()
	:writeBuf(__pack)
	:setPos(1)
	print("ba1.len:", __ba1:getLen())
	print("ba1.readByte:", __ba1:readByte())
	print("ba1.readInt:", __ba1:readInt())
	print("ba1.readShort:", __ba1:readShort())
	print("ba1.readString:", __ba1:readStringUShort())
	print("ba1.readString:", __ba1:readStringUShort())
	print("ba1.available:", __ba1:getAvailable())
	print("ba1.toString(16):", __ba1:toString(16))
	print("ba1.toString(10):", __ba1:toString(10))

	local __ba2 = self:_getByteArray()
	print("ba2.toString(10):", __ba2:toString(10))


	local __ba3 = ByteArray.new()
	local __str = ""
	for i=1,20 do
	__str = __str.."ABCDEFGHIJ"
	end
	__ba3:writeStringSizeT(__str)
	__ba3:setPos(1)
	print("__ba3:readUInt:", __ba3:readUInt())
	--print("__ba3.readStringSizeT:", __ba3:readStringUInt())
end

function MainScene:_onTest2()
	print("test2")
	local ba = ByteArrayVarint.new(ByteArrayVarint.ENDIAN_BIG)
		:writeInt(34)
	print(ba:toString(), ba:getLen())
	print(string.format("buf all bytes:%s, %d", 
		ByteArray.toString(ba:getBytes(), 16), 
		ba:getLen()))
end

function MainScene:_onTest3()
	print("test3")
	local l = string.pack("l", 32333)
	print(#l)
	local L = string.pack("L", 33333)
	print(#L)
	local i = string.pack("i", 32333)
	print(#i)
	local I = string.pack("I", 33333)
	print(#I)
end

function MainScene:_getDataByLpack()
	local __pack = string.pack("<bihP2", 0x59, 11, 1101, "", "中文")
	return __pack
end

function MainScene:_getByteArray()
	return ByteArray.new()
		:writeByte(0x59)
		:writeInt(11)
		:writeShort(1101)
		:writeStringUShort("")
		:writeStringUShort("中文")
end

return MainScene
