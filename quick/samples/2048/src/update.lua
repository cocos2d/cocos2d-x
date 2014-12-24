------------------------------------------------------------------------------
--Load origin framework
------------------------------------------------------------------------------
cc.LuaLoadChunksFromZIP("res/framework_precompiled.zip")

------------------------------------------------------------------------------
--If you would update the modoules which have been require here,
--you can reset them, and require them again in modoule "appentry"
------------------------------------------------------------------------------
require("config")
require("framework.init")

------------------------------------------------------------------------------
--define UpdateScene
------------------------------------------------------------------------------
local UpdateScene = class("UpdateScene", function()
    return display.newScene("UpdateScene")
end)

local NEEDUPDATE = false
--local server = "https://raw.githubusercontent.com/hanxi/quick-cocos2d-x-2048/release/"
local server = "http://192.168.16.13:8080/"
local param = "?dev="..device.platform
local list_filename = "flist"
local downList = {}

local function hex(s)
 s=string.gsub(s,"(.)",function (x) return string.format("%02X",string.byte(x)) end)
 return s
end

local function readFile(path)
    local file = io.open(path, "rb")
    if file then
        local content = file:read("*all")
        io.close(file)
        return content
    end
    return nil
end

local function removeFile(path)
    --CCLuaLog("removeFile: "..path)
    io.writefile(path, "")
    if device.platform == "windows" then
        --os.execute("del " .. string.gsub(path, '/', '\\'))
    else
        os.execute("rm " .. path)
    end
end

local function checkFile(fileName, cryptoCode)
    print("checkFile:", fileName)
    print("cryptoCode:", cryptoCode)

    if not io.exists(fileName) then
        return false
    end

    local data=readFile(fileName)
    if data==nil then
        return false
    end

    if cryptoCode==nil then
        return true
    end

    local ms = crypto.md5(hex(data))
    print("file cryptoCode:", ms)
    if ms==cryptoCode then
        return true
    end

    return false
end

local function checkDirOK( path )
        require "lfs"
        local oldpath = lfs.currentdir()
        CCLuaLog("old path------> "..oldpath)

         if lfs.chdir(path) then
            lfs.chdir(oldpath)
            CCLuaLog("path check OK------> "..path)
            return true
         end

         if lfs.mkdir(path) then
            CCLuaLog("path create OK------> "..path)
            return true
         end
end

function UpdateScene:ctor()
        self.path = device.writablePath.."upd/"
        --if device.platform == "android" then
        --    self.path = "/mnt/sdcard/quick_x_update/"
        --end

    local label = cc.ui.UILabel.new({
        UILabelType = 2,
        text = "Loading...",
        size = 64,
        x = display.cx,
        y = display.cy,
        align = cc.ui.TEXT_ALIGN_CENTER
    })
    self:addChild(label)
end

function UpdateScene:updateFiles()
    local data = readFile(self.newListFile)
    io.writefile(self.curListFile, data)
    self.fileList = dofile(self.curListFile)
    if self.fileList==nil then
        self:endProcess()
        return
    end
    removeFile(self.newListFile)

    for i,v in ipairs(downList) do
        print(i,v)
        local data=readFile(v)
        local fn = string.sub(v, 1, -5)
        print("fn: ", fn)
        io.writefile(fn, data)
        removeFile(v)
    end
    self:endProcess()
end

function UpdateScene:reqNextFile()
    self.numFileCheck = self.numFileCheck+1
    self.curStageFile = self.fileListNew.stage[self.numFileCheck]
    if self.curStageFile and self.curStageFile.name then
        local fn = self.path..self.curStageFile.name
        if checkFile(fn, self.curStageFile.code) then
            self:reqNextFile()
            return
        end
        fn = fn..".upd"
        if checkFile(fn, self.curStageFile.code) then
            table.insert(downList, fn)
            self:reqNextFile()
            return
        end
        self:requestFromServer(self.curStageFile.name)
        return
    end

    self:updateFiles()
end

function UpdateScene:onEnterFrame(dt)
	if self.dataRecv then
		if self.requesting == list_filename then
			io.writefile(self.newListFile, self.dataRecv)
			self.dataRecv = nil

			self.fileListNew = dofile(self.newListFile)
			if self.fileListNew==nil then
				CCLuaLog(self.newListFile..": Open Error!")
				self:endProcess()
				return
			end

			CCLuaLog(self.fileListNew.ver)
			if self.fileListNew.ver==self.fileList.ver then
				self:endProcess()
				return
			end

                                    self.numFileCheck = 0
                                    self.requesting = "files"
                                    self:reqNextFile()
                                    return
		end

                        if self.requesting == "files" then
                            local fn = self.path..self.curStageFile.name..".upd"
                            io.writefile(fn, self.dataRecv)
                            self.dataRecv = nil
                            if checkFile(fn, self.curStageFile.code) then
                                table.insert(downList, fn)
                                self:reqNextFile()
                            else
                                self:endProcess()
                            end
                            return
                        end

                        return
	end

end

function UpdateScene:onEnter()
        if not checkDirOK(self.path) then
            require("appentry")
            return
        end

              self.curListFile =  self.path..list_filename               
	self.fileList = nil
	if io.exists(self.curListFile) then
		self.fileList = dofile(self.curListFile)
	end
	if self.fileList==nil then
		self.fileList = {
			ver = "1.0.0",
			stage = {},
			remove = {},
		}
	end

	self.requestCount = 0
	self.requesting = list_filename
             self.newListFile = self.curListFile..".upd"
	self.dataRecv = nil
	self:requestFromServer(self.requesting)

    self:addNodeEventListener(cc.NODE_ENTER_FRAME_EVENT, function(dt) self:onEnterFrame(dt) end)
    self:scheduleUpdate()
end

function UpdateScene:onExit()
end

function UpdateScene:endProcess()
	CCLuaLog("----------------------------------------UpdateScene:endProcess")

            if self.fileList and self.fileList.stage then
                local checkOK = true
                for i,v in ipairs(self.fileList.stage) do
                    if not checkFile(self.path..v.name, v.code) then
                        CCLuaLog("----------------------------------------Check Files Error")
                        checkOK = false
                        break
                    end
                end

                if checkOK then
                    for i,v in ipairs(self.fileList.stage) do
                        if v.act=="load" then
                            cc.LuaLoadChunksFromZIP(self.path..v.name)
                        end
                    end
                    for i,v in ipairs(self.fileList.remove) do
                        removeFile(self.path..v)
                    end
                else
                    removeFile(self.curListFile)
                end
              end

            require("appentry")
end

function UpdateScene:requestFromServer(filename, waittime)
    local url = server..filename..param
    self.requestCount = self.requestCount + 1
    local index = self.requestCount
    local request = nil
    if NEEDUPDATE then
        request = network.createHTTPRequest(function(event)
            self:onResponse(event, index)
        end, url, "GET")
    end
    if request then
        request:setTimeout(waittime or 30)
        request:start()
    else
        self:endProcess()
    end
end

function UpdateScene:onResponse(event, index, dumpResponse)
    local request = event.request
    printf("REQUEST %d - event.name = %s", index, event.name)
    if event.name == "completed" then
        printf("REQUEST %d - getResponseStatusCode() = %d", index, request:getResponseStatusCode())
        --printf("REQUEST %d - getResponseHeadersString() =\n%s", index, request:getResponseHeadersString())

        if request:getResponseStatusCode() ~= 200 then
        	self:endProcess()
        else
            printf("REQUEST %d - getResponseDataLength() = %d", index, request:getResponseDataLength())
            if dumpResponse then
                printf("REQUEST %d - getResponseString() =\n%s", index, request:getResponseString())
            end
            self.dataRecv = request:getResponseData()
        end
    elseif event.name ~= "progress" then
        printf("REQUEST %d - getErrorCode() = %d, getErrorMessage() = %s", index, request:getErrorCode(), request:getErrorMessage())
        self:endProcess()
    end

    print("----------------------------------------")
end

local upd = UpdateScene.new()
display.replaceScene(upd)
