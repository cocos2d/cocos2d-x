
local net = require("framework.cc.net.init")
local SocketTcpTestScene = game.createSceneClass("SocketTcpTestScene")

function SocketTcpTestScene:ctor()
    cc.FileUtils:getInstance():addSearchPath("src/")

    self:prepare({
        description = "Please run server listen on 127.0.0.1:8080"
    })

    local items = {
        "Connect",
        "SendData",
        "Close"
    }
    self:addChild(game.createMenu(items, handler(self, self.runTest)))

    self:init()
end

function SocketTcpTestScene:init()
	local time = net.SocketTCP.getTime()
	print("socket time:" .. time)

	local socket = net.SocketTCP.new()
	socket:setName("TestSocketTcp")
	socket:setTickTime(1)
	socket:setReconnTime(6)
	socket:setConnFailTime(4)

	socket:addEventListener(net.SocketTCP.EVENT_DATA, handler(self, self.tcpData))
	socket:addEventListener(net.SocketTCP.EVENT_CLOSE, handler(self, self.tcpClose))
	socket:addEventListener(net.SocketTCP.EVENT_CLOSED, handler(self, self.tcpClosed))
	socket:addEventListener(net.SocketTCP.EVENT_CONNECTED, handler(self, self.tcpConnected))
	socket:addEventListener(net.SocketTCP.EVENT_CONNECT_FAILURE, handler(self, self.tcpConnectedFail))

	self.socket_ = socket
end

function SocketTcpTestScene:ConnectTest()
	self.socket_:connect("127.0.0.1", 8080, true)
end

function SocketTcpTestScene:SendDataTest()
	self.socket_:send("TcpSendContent")
end

function SocketTcpTestScene:CloseTest()
	if self.socket_.isConnected then
		self.socket_:close()
	end
end

function SocketTcpTestScene:tcpData(event)
	print("SocketTCP receive data:" .. event.data)
end

function SocketTcpTestScene:tcpClose()
	print("SocketTCP close")
end

function SocketTcpTestScene:tcpClosed()
	print("SocketTCP closed")
end

function SocketTcpTestScene:tcpConnected()
	print("SocketTCP connect success")
end

function SocketTcpTestScene:tcpConnectedFail()
	print("SocketTCP connect fail")
end

function SocketTcpTestScene:onExit()
	if self.socket_.isConnected then
		self.socket_:close()
	end
	self.socket_:disconnect()
end

return SocketTcpTestScene
