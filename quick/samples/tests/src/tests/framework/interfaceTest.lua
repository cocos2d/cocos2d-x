
local InterfaceTestScene = game.createSceneClass("InterfaceTestScene")

function InterfaceTestScene:ctor()
    self:prepare({
        description = "Please check console output"
    })

    local items = {
        "register",
        "modebase",
        "functions"
    }
    self:addChild(game.createMenu(items, handler(self, self.runTest)))

    cc.FileUtils:getInstance():addSearchPath("res/")
end

function InterfaceTestScene:registerTest()
	local register = require("framework.cc.Registry")

	local eventProtocol = register.newObject("components.behavior.EventProtocol")
	if not eventProtocol then
		printError("ERROR some thing wrong please check Register")
	end
	register.setObject(eventProtocol, "cryptoTest1")
	if not register.isObjectExists("cryptoTest1") then
		printError("ERROR some thing wrong please check Register")
	end
	register.getObject("cryptoTest1")
	register.removeObject("cryptoTest1")
	if register.isObjectExists("cryptoTest1") then
		printError("ERROR some thing wrong please check Register")
	end

	if not register.exists("components.behavior.EventProtocol") then
		printError("ERROR some thing wrong please check Register")
	end

end

function InterfaceTestScene:modebaseTest()
	local mvcBase = require("framework.cc.mvc.ModelBase")
end

function InterfaceTestScene:functionsTest()

	-- iskindof
	local Animal = class("Animal")
	local Duck = class("Duck", Animal)
	if not iskindof(Duck.new(), "Animal") then
		printError("ERROR somenthing wrong in iskindof()")
	end

	local subNode = class("subNode", function() return display.newNode() end).new()
	if not iskindof(subNode, "subNode") then
		printError("ERROR somenthing wrong in iskindof()")
	end

	local val = math.round(0.1)
	print("val want 0, actual is " .. val)
	val = math.round(1.5)
	print("val want 2, actual is " .. val)
	val = math.round("string")
	print("val want 0, actual is " .. val)

	val = math.angle2radian(1)
	print("val want 0.017453292519943, actual is " .. val)
	val = math.radian2angle(1)
	print("val want 57.295779513082, actual is " .. val)

	local path = cc.FileUtils:getInstance():fullPathForFilename("testFile.dat")

	if not io.exists(path) then
		printError("ERROR somenthing wrong in io.exists()")
	end
	print("io.readfile content:" .. io.readfile(path))

	io.writefile(io.pathinfo(path).dirname .. "testFile1.dat", "1232kddk")

	val = io.filesize(path)
	print("io.filesize size:" .. val)

	-- table
	local table1 = {key1 = "val1", "val2", key3 = "val3"}
	local array = {45, 25, "name1", "name2", "same", "htl", "same"}
	val = table.nums(table1)
	print("table.nums want 3, actual " .. val)
	dump(table.keys(table1), "table.keys want {1, key1, key3}, actual:")
	dump(table.values(table1), "table.values want {val2, val1, val3}, actual:")
	
	local table2 = {3, key11 = "val11"}
	table.merge(table2, table1)
	dump(table2, "tabel.merge want {val2, key1 = val1, key11 = val11, key3 = val3, actual:")

	local src = {4, 5}
	local dest = {1, 2}
	table.insertto(dest, src, 4)
	dump(dest, "tabel.insertto want {1, 2, 4, 5, actual:")

	val = table.indexof(dest, 2)
	print("table.indexof want 2, actual " .. val)
	val = table.keyof(table2, "val11")
	print("table.keyof want key11, actual " .. val)

	val = table.removebyvalue(array, "same", true)
	print("table.removebyvalue want 2, actual " .. val)


	local t = {name = "dualface", comp = "chukong"}
	table.map(table2, function(v, k)
	    return "[" .. v .. "]"
	end)

	table.walk(table2, function(v, k)
	    print(v)
	end)

	table.filter(table2, function(v, k)
	    return v ~= "[val11]"
	end)

	table.walk(table2, function(v, k)
	    print(v)
	end)

	table2[102] = "same"
	table2[103] = "same"

	table2 = table.unique(table2)
	dump(table2, "should just have one \"same\" value:")

	print(string.htmlspecialchars("<ABC>"))
	print(string.restorehtmlspecialchars(string.htmlspecialchars("<ABC>")))
	print(string.nl2br("Hello\nWorld"))
	print(string.text2html("<Hello>\nWorld"))

	local input = "Hello-+-World-+-Quick"
	local res = string.split(input, "-+-")
	dump(res, "string.split :")

	print(string.ltrim("   ABC"))
	print(string.rtrim("ABC   "))
	print(string.trim("   ABC   "))

	print(string.ucfirst("aBC"))

	print(string.urlencode("ABC ABC"))
	print(string.urldecode(string.urlencode("ABC ABC")))
	print(string.utf8len("你好World"))
	print(string.formatnumberthousands(1924235))
end

return InterfaceTestScene
