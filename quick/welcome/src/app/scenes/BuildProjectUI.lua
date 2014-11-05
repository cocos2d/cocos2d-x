
local Utilitys = require("app.utilitys.Utilitys")
local EditBoxLite = import(".EditBoxLite")

local BuildProjectUI = class("BuildProjectUI", function()
        return display.newColorLayer(cc.c4b(56, 56, 56, 250))
    end)

function BuildProjectUI:ctor(args)
	self.cmdArgs_ = {}
	self.cmdArgs_.projDir = args.projDir
	self.cmdArgs_.platform = "android"
	self.cmdArgs_.mode = "debug"
	self.cmdArgs_.compileRes = true
	self.cmdArgs_.compileScr = true

	self.cmdArgs_.outputDir = self:addOutputFromPath(self.cmdArgs_.projDir)

	self:createUI()
end

function BuildProjectUI:onEnter()
end

function BuildProjectUI:onExit()
end

function BuildProjectUI:createUI()
	local winSize = cc.Director:getInstance():getWinSize()
	local posY = winSize.height
	local posX = display.left + 40

	local fontSize = 25
	local images = {
	    normal = "#ButtonNormal.png",
	    pressed = "#ButtonPressed.png",
	    disabled = "#ButtonDisabled.png",
	}
	local radioImages = {
		off = "RadioButtonOff.png",
		on = "RadioButtonOn.png"
	}
	local checkboxImages = {
	    off = "CheckBoxButton2Off.png",
	    on = "CheckBoxButton2On.png",
	}

	-- Porject Dir
	posY = posY - 30
    self:addLabel("Project dir:", posX, posY)

    posY = posY - 60
    self.projDirTF_ = self:addEditbox({x = posX, y = posY})
    self:addButton("Select", display.right - 170, posY, function(event)
    	local filedialog = PlayerProtocol:getInstance():getFileDialogService()
        local locationDirectory = filedialog:openDirectory("Choose Localtion", "")
        if string.len(locationDirectory) > 0 then
            self.projDirTF_:setText(locationDirectory)
            self.outputDirTF_:setText(self:addOutputFromPath(locationDirectory))
        end
    	end)
    self.projDirTF_:setText(self.cmdArgs_.projDir)

    -- out dir
    posY = posY - 20
    self:addLabel("Output dir:", posX, posY)

    posY = posY - 60
    self.outputDirTF_ = self:addEditbox({x = posX, y = posY})
    self:addButton("Select", display.right - 170, posY, function(event)
    	local filedialog = PlayerProtocol:getInstance():getFileDialogService()
        local locationDirectory = filedialog:openDirectory("Choose Localtion", "")
        if string.len(locationDirectory) > 0 then
            self.outputDirTF_:setText(locationDirectory)
        end
    	end)
    self.outputDirTF_:setText(self.cmdArgs_.outputDir)

    -- platform
    posY = posY - 20
    self:addLabel("Platform:", posX, posY)

	posY = posY - 50
    local group = cc.ui.UICheckBoxButtonGroup.new(display.LEFT_TO_RIGHT)
        :addButton(cc.ui.UICheckBoxButton.new(radioImages)
            :setButtonLabel(cc.ui.UILabel.new({text = "Android", color = display.COLOR_BLACK}))
            :setButtonLabelOffset(20, 0)
            :align(display.LEFT_CENTER))
    if "ios" == device.platform or "mac" == device.platform then
        group:addButton(cc.ui.UICheckBoxButton.new(radioImages)
            :setButtonLabel(cc.ui.UILabel.new({text = "IOS", color = display.COLOR_BLACK}))
            :setButtonLabelOffset(20, 0)
            :align(display.LEFT_CENTER))
        :addButton(cc.ui.UICheckBoxButton.new(radioImages)
            :setButtonLabel(cc.ui.UILabel.new({text = "Mac", color = display.COLOR_BLACK}))
            :setButtonLabelOffset(20, 0)
            :align(display.LEFT_CENTER))
    elseif "windows" == device.platform then
        group:addButton(cc.ui.UICheckBoxButton.new(radioImages)
            :setButtonLabel(cc.ui.UILabel.new({text = "Win32", color = display.COLOR_BLACK}))
            :setButtonLabelOffset(20, 0)
            :align(display.LEFT_CENTER))
    end
        -- :addButton(cc.ui.UICheckBoxButton.new(radioImages)
        --     :setButtonLabel(cc.ui.UILabel.new({text = "Linux", color = display.COLOR_BLACK}))
        --     :setButtonLabelOffset(20, 0)
        --     :align(display.LEFT_CENTER))
        -- :addButton(cc.ui.UICheckBoxButton.new(radioImages)
        --     :setButtonLabel(cc.ui.UILabel.new({text = "web", color = display.COLOR_BLACK}))
        --     :setButtonEnabled(false)
        --     :setButtonLabelOffset(25, 0)
        --     :align(display.LEFT_CENTER))
    group:setButtonsLayoutMargin(10, 80, 10, 10)
        :onButtonSelectChanged(function(event)
        	if not self.platformNode_ then
        		return
        	end

        	self.androidArgsPanel_:setVisible(false)
			self.IOSArgsPanel_:setVisible(false)
			self.MacArgsPanel_:setVisible(false)

        	if 1 == event.selected then
        		self.androidArgsPanel_:setVisible(true)
        		self.cmdArgs_.platform = "android"
        	elseif 2 == event.selected then
        		if "windows" == device.platform then
        			self.cmdArgs_.platform = "win32"
        		else
	        		self.IOSArgsPanel_:setVisible(true)
	        		self.cmdArgs_.platform = "ios"
	        	end
        	elseif 3 == event.selected then
        		self.MacArgsPanel_:setVisible(true)
        		self.cmdArgs_.platform = "mac"
        	elseif 4 == event.selected then
        		self.cmdArgs_.platform = "win32"
        	end
        end)
        :align(display.LEFT_BOTTOM, posX, posY)
        :addTo(self)
    group:getButtonAtIndex(1):setButtonSelected(true)

	-- mode
    posY = posY - 10
    self:addLabel("Mode:", posX, posY)

	posY = posY - 50
	group = cc.ui.UICheckBoxButtonGroup.new(display.LEFT_TO_RIGHT)
        :addButton(cc.ui.UICheckBoxButton.new(radioImages)
            :setButtonLabel(cc.ui.UILabel.new({text = "Debug", color = display.COLOR_BLACK}))
            :setButtonLabelOffset(20, 0)
            :align(display.LEFT_CENTER))
        :addButton(cc.ui.UICheckBoxButton.new(radioImages)
            :setButtonLabel(cc.ui.UILabel.new({text = "Release", color = display.COLOR_BLACK}))
            :setButtonLabelOffset(20, 0)
            :align(display.LEFT_CENTER))
        :setButtonsLayoutMargin(10, 80, 10, 10)
        :onButtonSelectChanged(function(event)
        	if 1 == event.selected then
        		self.cmdArgs_.mode = "debug"
        	elseif 2 == event.selected then
        		self.cmdArgs_.mode = "release"
        	end
        end)
        :align(display.LEFT_BOTTOM, posX, posY)
        :addTo(self)
    group:getButtonAtIndex(1):setButtonSelected(true)

    -- lua argments
    posY = posY - 10
    self:addLabel("Lua Args:", posX, posY)
    posY = posY - 30
    local spaceW = 300
    cc.ui.UICheckBoxButton.new(checkboxImages, {scale9 = true})
    	:setButtonSize(36, 36)
        :setButtonLabel(cc.ui.UILabel.new({text = "Compile Resource",  color = display.COLOR_BLACK}))
        :setButtonLabelOffset(25, 0)
        :setButtonLabelAlignment(display.LEFT_CENTER)
        :align(display.LEFT_CENTER, posX, posY)
        :setButtonSelected(true)
        :addTo(self)
        :onButtonStateChanged(function(event)
        	if "on" == event.state then
        		self.cmdArgs_.compileRes = true
        	elseif "off" == event.state then
        		self.cmdArgs_.compileRes = false
        	end
        	end)
    cc.ui.UICheckBoxButton.new(checkboxImages, {scale9 = true})
    	:setButtonSize(36, 36)
        :setButtonLabel(cc.ui.UILabel.new({text = "Compile Script",  color = display.COLOR_BLACK}))
        :setButtonLabelOffset(25, 0)
        :setButtonLabelAlignment(display.LEFT_CENTER)
        :align(display.LEFT_CENTER, posX + spaceW, posY)
        :setButtonSelected(true)
        :addTo(self)
        :onButtonStateChanged(function(event)
        	if "on" == event.state then
        		self.cmdArgs_.compileScr = true
        	elseif "off" == event.state then
        		self.cmdArgs_.compileScr = false
        	end
        	end)

    posY = posY - 40
    cc.ui.UICheckBoxButton.new(checkboxImages, {scale9 = true})
    	:setButtonSize(36, 36)
        :setButtonLabel(cc.ui.UILabel.new({text = "Enable Lua Encrypt",  color = display.COLOR_BLACK}))
        :setButtonLabelOffset(25, 0)
        :setButtonLabelAlignment(display.LEFT_CENTER)
        :align(display.LEFT_CENTER, posX, posY)
        :addTo(self)
        :onButtonStateChanged(function(event)
        	if "on" == event.state then
        		self.encyrPanel_:setVisible(true)
        		self:updatePlatformPanelPos()
        		self.cmdArgs_.LuaEncrypt = true
        	elseif "off" == event.state then
        		self.encyrPanel_:setVisible(false)
        		self:updatePlatformPanelPos()
        		self.cmdArgs_.LuaEncrypt = false
        	end
        	end)

	posY = posY - 40
	self.encyrPanel_ = self:addEncryptArgs()
	self.encyrPanel_:setPosition(posX, posY)
	self:addChild(self.encyrPanel_)

	-- posY = posY - 40
	posX = 40
	self.androidArgsPanel_ = self:addAndroidArgs()
	self.IOSArgsPanel_ = self:addIOSArgs()
	self.MacArgsPanel_ = self:addMacArgs()

	local platformNode = display.newNode()
	platformNode:addChild(self.androidArgsPanel_)
	platformNode:addChild(self.IOSArgsPanel_)
	platformNode:addChild(self.MacArgsPanel_)
	self:addChild(platformNode)
	platformNode:setPosition(posX, posY)
	self.platformNode_ = platformNode

	self.androidArgsPanel_:setVisible(true)

	-- back button
	self:addButton("Back", display.left + 20, 10, function(event)
		self:removeFromParent(true)
    	end)

	-- compile button
	self.compileBtn = self:addButton("Compile", display.right - 170, 10, function(event)
		if Utilitys.stringIsNull(self.projDirTF_:getText()) then
			print("project directory is nil")
			return
		end
		if Utilitys.stringIsNull(self.outputDirTF_:getText()) then
			print("output directory is nil")
			return
		end

		self:runCompile()
    	end)
end

function BuildProjectUI:addLabel(text, posX, posY, node)
	node = node or self
	cc.ui.UILabel.new({
        text = text,
        size = fontSize,
        color = display.COLOR_WHITE,
        })
    :align(display.LEFT_CENTER, posX, posY)
    :addTo(node)
end

function BuildProjectUI:addEditbox(args, node)
	node = node or self
	local editboxArg = {
        image = "#ButtonNormal.png",
        size = args.size or cc.size(display.width-250, 35),
        x = args.x,
        y = args.y,
    }

    local locationEditbox = EditBoxLite.create(editboxArg)
    locationEditbox:setAnchorPoint(0,0)
    node:addChild(locationEditbox)

    return locationEditbox
end

function BuildProjectUI:addButton(text, posX, posY, listener)
	local images = {
	    normal = "#ButtonNormal.png",
	    pressed = "#ButtonPressed.png",
	    disabled = "#ButtonDisabled.png",
	}
	local fontSize = 25

	local btn = cc.ui.UIPushButton.new(images, {scale9 = true})
	    :setButtonSize(150, 40)
	    :setButtonLabel("normal", cc.ui.UILabel.new({
	            text = text,
	            size = fontSize}))
	    :align(display.LEFT_BOTTOM, posX, posY)
	    :addTo(self)
	    :onButtonClicked(listener)

	return btn
end

function BuildProjectUI:addEncryptArgs()
	local node = display.newNode()
	local posX = 0
	local posY = 0
	local spaceW = 200

	self:addLabel("EncryptKey:", posX, posY, node)
	self.encryptKeyTF_ = self:addEditbox({x = posX + spaceW, y = posY - 20, size = cc.size(200, 35)}, node)
	posX = display.cx
	self:addLabel("EncryptSign:", posX, posY, node)
	self.encryptKeySign_ = self:addEditbox({x = posX + spaceW, y = posY - 20, size = cc.size(200, 35)}, node)

	node:setVisible(false)
	return node
end

function BuildProjectUI:addAndroidArgs()
	local node = display.newNode()
	local posX = 0
	local posY = 0
	local spaceW = 200

	self:addLabel("Android:", posX, posY, node)
	posY = posY - 40
	self:addLabel("AndroidPlatform:", posX, posY, node)
	self.androidPlatformTF_ = self:addEditbox({x = posX + spaceW, y = posY - 20, size = cc.size(200, 35)}, node)
	posX = display.cx
	self:addLabel("NDK_MODE:", posX, posY, node)
	self.androidNDKMODETF_ = self:addEditbox({x = posX + spaceW, y = posY - 20, size = cc.size(200, 35)}, node)

	posY = posY - 40
	posX = 0
	self:addLabel("APP_ABI:", posX, posY, node)
	self.androidABITF_ = self:addEditbox({x = posX + spaceW, y = posY - 20, size = cc.size(200, 35)}, node)
	posX = display.cx
	self:addLabel("TOOLCHAIN:", posX, posY, node)
	self.androidToolChainTF_ = self:addEditbox({x = posX + spaceW, y = posY - 20, size = cc.size(200, 35)}, node)

	posY = posY - 40
	posX = 0
	self:addLabel("CPP_FLAGS:", posX, posY, node)
	self.androidCppFlagsTF_ = self:addEditbox({x = posX + spaceW, y = posY - 20, size = cc.size(200, 35)}, node)

	node:setVisible(false)
	return node
end

function BuildProjectUI:addIOSArgs()
	local node = display.newNode()
	local posX = 0
	local posY = 0
	local spaceW = 200

	self:addLabel("IOS:", posX, posY, node)
	posY = posY - 30
	self:addLabel("Target:", posX, posY, node)
	self.iosTargetTF_ = self:addEditbox({x = posX + spaceW, y = posY - 20, size = cc.size(200, 40)}, node)
	posX = display.cx
	self:addLabel("SIGN_ID:", posX, posY, node)
	self.iosSignTF_ = self:addEditbox({x = posX + spaceW, y = posY - 20, size = cc.size(200, 40)}, node)

	node:setVisible(false)
	return node
end

function BuildProjectUI:addMacArgs()
	local node = display.newNode()
	local posX = 0
	local posY = 0
	local spaceW = 200

	self:addLabel("Mac:", posX, posY, node)
	posY = posY - 30
	self:addLabel("Target:", posX, posY, node)
	self.macTargetTF_ = self:addEditbox({x = posX + spaceW, y = posY - 20, size = cc.size(200, 40)}, node)

	node:setVisible(false)
	return node
end

--lua加密的要显示,各平台的参数就要下移,不显示,各平台参数就要上移
function BuildProjectUI:updatePlatformPanelPos()
	local posX, posY = self.encyrPanel_:getPosition()
	local bVisible = self.encyrPanel_:isVisible()
	if bVisible then
		self.platformNode_:setPosition(posX, posY - 40)
	else
		self.platformNode_:setPosition(posX, posY)
	end
end

function BuildProjectUI:getCommandString()
	local cmds = {}

	local insertValTotable = function(t, key, val)
		if Utilitys.stringIsNull(val) then
			return
		end
		table.insert(t, key .. val)
	end

	table.insert(cmds, "-s " .. self.projDirTF_:getText())
	table.insert(cmds, "-o " .. self.outputDirTF_:getText())
	table.insert(cmds, "-p " .. self.cmdArgs_.platform)
	table.insert(cmds, "-m " .. self.cmdArgs_.mode)
	if not self.cmdArgs_.compileRes then
		table.insert(cmds, "--no-res")
	end
	if self.cmdArgs_.compileScr then
		table.insert(cmds, "--compile-script 1")
	else
		table.insert(cmds, "--compile-script 0")
	end
	if self.cmdArgs_.LuaEncrypt then
		table.insert(cmds, "--lua-encrypt")
		insertValTotable(cmds, "--lua-encrypt-key ", self.encryptKeyTF_:getText())
		insertValTotable(cmds, "--lua-encrypt-sign ", self.encryptKeySign_:getText())
	end

	if "android" == self.cmdArgs_.platform then
		insertValTotable(cmds, "--ap ", self.androidPlatformTF_:getText())
		insertValTotable(cmds, "--ndk-mode ", self.androidNDKMODETF_:getText())
		insertValTotable(cmds, "--app-abi ", self.androidABITF_:getText())
		insertValTotable(cmds, "--ndk-toolchain ", self.androidToolChainTF_:getText())
		insertValTotable(cmds, "--ndk-cppflags ", self.androidCppFlagsTF_:getText())
	elseif "ios" == self.cmdArgs_.platform then
		insertValTotable(cmds, "-t ", self.iosTargetTF_:getText())
		insertValTotable(cmds, "--sign-identity ", self.iosSignTF_:getText())
	elseif "mac" == self.cmdArgs_.platform then
		insertValTotable(cmds, "-t ", self.macTargetTF_:getText())
	end

	return table.concat(cmds, " ")
end

function BuildProjectUI:runCompile()
	local strCmd = self:getCommandString()
	print("command string:" .. strCmd)
	local scriptPath = cc.player.quickRootPath .. "quick/bin/cocos_compile.sh"
    if device.platform == "windows" then
        scriptPath = cc.player.quickRootPath .. "quick/bin/cocos_compile.bat"
    end

	local taskId = tostring(os.time())
    local task = PlayerProtocol:getInstance():getTaskService():createTask(taskId, scriptPath, strCmd)
    task:runInTerminal()
end

function BuildProjectUI:addOutputFromPath(projDir)
	if not Utilitys.stringIsNull(projDir) then
		-- '/' 47 '\' 92
		local val = string.byte(projDir, string.len(projDir))
		if 47 == val or 92 == val then
			return projDir .. "output" .. string.char(val)
		else
			return projDir .. "/output/"
		end
	end
end



return BuildProjectUI
