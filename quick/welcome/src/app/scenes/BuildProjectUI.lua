
local Utilitys = require("app.utilitys.Utilitys")
local EditBoxLite = import(".EditBoxLite")

local BuildProjectUI = class("BuildProjectUI", function()
        return display.newColorLayer(cc.c4b(56, 56, 56, 250))
    end)

function BuildProjectUI:ctor(args)
	self.cmdArgs_ = {}
	self.cmdArgs_.projDir = args.projDir
	self.cmdArgs_.buildNative = true
	self.cmdArgs_.signAPK = true

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
	local spaceW = 80

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

	posY = posY - 30
    self:addLabel("Project path:", posX, posY)
    posY = posY - 60
    self.projDirTF_ = self:addEditbox({x = posX, y = posY})
    self:addButton("Selected", display.right - 170, posY, function(event)
    	self:openFileDialog(self.projDirTF_)
    	end)
    self.projDirTF_:setText(self.cmdArgs_.projDir)

    posY = posY - 50
    local group = cc.ui.UICheckBoxButtonGroup.new(display.LEFT_TO_RIGHT)
        :addButton(cc.ui.UICheckBoxButton.new(radioImages)
            :setButtonLabel(cc.ui.UILabel.new({text = "BuildNative", color = display.COLOR_BLACK}))
            :setButtonLabelOffset(20, 0)
            :align(display.LEFT_CENTER))
        :addButton(cc.ui.UICheckBoxButton.new(radioImages)
            :setButtonLabel(cc.ui.UILabel.new({text = "BuildAPK", color = display.COLOR_BLACK}))
            :setButtonLabelOffset(20, 0)
            :align(display.LEFT_CENTER))
    group:setButtonsLayoutMargin(10, 80, 10, 10)
        :onButtonSelectChanged(function(event)
        	if not self.buildAPKPanel_ then
        		return
        	end

			self.buildAPKPanel_:setVisible(false)

        	if 1 == event.selected then
        		self.cmdArgs_.buildNative = true
        	elseif 2 == event.selected then
        		self.buildAPKPanel_:setVisible(true)
        		self.cmdArgs_.buildNative = false
        	end
        end)
        :align(display.LEFT_BOTTOM, posX, posY)
        :addTo(self)
    group:getButtonAtIndex(1):setButtonSelected(true)

    cc.ui.UICheckBoxButton.new(checkboxImages, {scale9 = true})
    	:setButtonSize(36, 36)
        :setButtonLabel(cc.ui.UILabel.new({text = "Release", color = display.COLOR_BLACK}))
        :setButtonLabelOffset(25, 0)
        :setButtonLabelAlignment(display.LEFT_CENTER)
        :align(display.LEFT_BOTTOM, display.right - 400, posY)
        :setButtonSelected(false)
        :addTo(self)
        :onButtonStateChanged(function(event)
        	if "on" == event.state then
        		self.cmdArgs_.bRelease = true
        	elseif "off" == event.state then
        		self.cmdArgs_.bRelease = false
        	end
        	end)

    posY = posY - 30
    self.buildAPKPanel_ = self:addAndroidArgs()
    self.buildAPKPanel_:setPosition(posX, posY)
    self:addChild(self.buildAPKPanel_)

	-- back button
	self:addButton("Back", display.left + 20, 10, function(event)
		self:removeFromParent(true)
    	end)

	-- clear button
	self.compileBtn = self:addButton("Clear", display.right - 370, 10, function(event)
		self:runClear()
    	end)

	-- compile button
	self.compileBtn = self:addButton("Compile", display.right - 170, 10, function(event)
		if Utilitys.stringIsNull(self.projDirTF_:getText()) then
			print("project directory is nil")
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

function BuildProjectUI:addButton(text, posX, posY, listener, node)
	node = node or self
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
	    :addTo(node)
	    :onButtonClicked(listener)

	return btn
end

function BuildProjectUI:addKeyStoreArgs()
	local node = display.newNode()
	local posX = 0
	local posY = 0
	local spaceW = 200

    self:addLabel("KeyStore path:", posX, posY, node)
    posY = posY - 60
    self.KeyStorePathTF_ = self:addEditbox({x = posX, y = posY}, node)
    self:addButton("Selected", display.right - 210, posY, function(event)
    	print("keystore clicked")
    	end, node)

    posY = posY - 40
	self:addLabel("KeyStore Password:", posX, posY, node)
	self.keyStorePWTF_ = self:addEditbox({x = posX + 220, y = posY - 20, size = cc.size(200, 35)}, node)
	posX = display.cx
	self:addLabel("KeyStore alias:", posX, posY, node)
	self.keyStoreAliasTF_ = self:addEditbox({x = posX + 180, y = posY - 20, size = cc.size(200, 35)}, node)

	node:setVisible(false)
	return node
end

function BuildProjectUI:addAndroidArgs()
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

	local node = display.newNode()
	local posX = 0
	local posY = 0
	local spaceW = 200

    self:addLabel("Android build tools path:", posX, posY, node)
    posY = posY - 60
    self.androidBuildToosPathTF_ = self:addEditbox({x = posX, y = posY}, node)
    self:addButton("Selected", display.right - 210, posY, function(event)
    	self:openFileDialog(self.androidBuildToosPathTF_)
    	end, node)

    posY = posY - 30
    self:addLabel("Java extra path:", posX, posY, node)
    posY = posY - 60
    self.javaExtraPathTF_ = self:addEditbox({x = posX, y = posY}, node)
    self:addButton("Selected", display.right - 210, posY, function(event)
    	self:openFileDialog(self.javaExtraPathTF_)
    	end, node)

    posY = posY - 40
	self:addLabel("AndroidAPI:", posX, posY, node)
	self.androidAPITF_ = self:addEditbox({x = posX + spaceW, y = posY - 20, size = cc.size(200, 35)}, node)
	posX = display.cx
	self:addLabel("JavaSDKVer:", posX, posY, node)
	self.javaSDKVerTF_ = self:addEditbox({x = posX + spaceW, y = posY - 20, size = cc.size(200, 35)}, node)

	posX = 0
	posY = posY - 40
	cc.ui.UICheckBoxButton.new(checkboxImages, {scale9 = true})
    	:setButtonSize(36, 36)
        :setButtonLabel(cc.ui.UILabel.new({text = "sign the apk",  color = display.COLOR_BLACK}))
        :setButtonLabelOffset(25, 0)
        :setButtonLabelAlignment(display.LEFT_CENTER)
        :align(display.LEFT_CENTER, posX, posY)
        :setButtonSelected(true)
        :addTo(node)
        :onButtonStateChanged(function(event)
        	if "on" == event.state then
        		self.cmdArgs_.signAPK = true
        		self.keystorePanel_:setVisible(true)
        	elseif "off" == event.state then
        		self.cmdArgs_.signAPK = false
        		self.keystorePanel_:setVisible(false)
        	end
        	end)

	posY = posY - 40
	self.keystorePanel_ = self:addKeyStoreArgs()
	self.keystorePanel_:setPosition(posX, posY)
	node:addChild(self.keystorePanel_)

	self.keystorePanel_:setVisible(true)

	node:setVisible(false)
	return node
end

function BuildProjectUI:getCommandString()
	local cmds = {}

	local insertValTotable = function(t, key, val)
		if Utilitys.stringIsNull(val) then
			return
		end
		table.insert(t, key .. val)
	end

	-- insertValTotable(cmds, "-pdir ", self.projDirTF_:getText())
	insertValTotable(cmds, "-classpath ", self.javaExtraPathTF_:getText())
	insertValTotable(cmds, "-bt ", self.androidBuildToosPathTF_:getText())

	if self.cmdArgs_.signAPK then
		insertValTotable(cmds, "-k ", self.KeyStorePathTF_:getText())
		insertValTotable(cmds, "-kp ", self.keyStorePWTF_:getText())
		insertValTotable(cmds, "-ksa ", self.keyStoreAliasTF_:getText())
	else
		table.insert(cmds, "-nosign")
	end

	insertValTotable(cmds, "-api ", self.androidAPITF_:getText())
	insertValTotable(cmds, "-jv ", self.javaSDKVerTF_:getText())

	if not self.cmdArgs_.buildNative and self.cmdArgs_.bRelease then
		table.insert(cmds, "-bldm release")
	end

	return table.concat(cmds, " ")
end

function BuildProjectUI:runCompile()
	local strCmd = self:getCommandString()
	local projDir = self:addSymbolForPath(self.projDirTF_:getText())

	local scriptPath
	if self.cmdArgs_.buildNative then
		if self.cmdArgs_.bRelease then
			if device.platform == "windows" then
	        	scriptPath = projDir .. "build_native_release.bat"
	        else
	        	scriptPath = projDir .. "build_native_release.sh"
	    	end
		else
			if device.platform == "windows" then
	        	scriptPath = projDir .. "build_native.bat"
	        else
	        	scriptPath = projDir .. "build_native.sh"
	    	end
	    end
    	strCmd = ""
	else
		if device.platform == "windows" then
        	scriptPath = projDir .. "build_apk.bat"
        else
        	scriptPath = projDir .. "build_apk.sh"
    	end
	end

	print("Create Cmd:" .. scriptPath .. " " .. strCmd)
	local taskId = tostring(os.time())
    local task = PlayerProtocol:getInstance():getTaskService():createTask(taskId, scriptPath, strCmd)
    task:runInTerminal()
end

function BuildProjectUI:runClear()
	local scriptPath
    local strCmd = ""
    local projDir = self:addSymbolForPath(self.projDirTF_:getText())

	if device.platform == "windows" then
    	scriptPath = projDir .. "clean.bat"
    else
    	scriptPath = projDir .. "clean.sh"
	end

	local taskId = tostring(os.time())
    local task = PlayerProtocol:getInstance():getTaskService():createTask(taskId, scriptPath, strCmd)
    task:runInTerminal()
end

function BuildProjectUI:addSymbolForPath(projDir)
	if not Utilitys.stringIsNull(projDir) then
		local paths = {}

		-- '/' 47 '\' 92
		local strLen = string.len(projDir)
		local val = string.byte(projDir, strLen)
		if 47 == val or 92 == val then
			table.insert(paths, string.sub(projDir, 1, strLen - 1))
		else
			table.insert(paths, projDir)
		end
		table.insert(paths, "frameworks")
		table.insert(paths, "runtime-src")
		table.insert(paths, "proj.android")

		return table.concat(paths, device.directorySeparator) .. device.directorySeparator
	end
end

function BuildProjectUI:openFileDialog(textField)
    local filedialog = PlayerProtocol:getInstance():getFileDialogService()
    local locationDirectory = filedialog:openDirectory("Choose Localtion", "")
    if string.len(locationDirectory) > 0 then
        textField:setText(locationDirectory)
    end

end



return BuildProjectUI
