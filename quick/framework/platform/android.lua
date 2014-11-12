
if cc.bPlugin_ then
	luaj = require("cocos.cocos2d.luaj")
else
	luaj = require(cc.PACKAGE_NAME .. ".luaj")
end

function io.exists(path)
    return cc.FileUtils:getInstance():isFileExist(path)
end

function io.readfile(path)
    return cc.HelperFunc:getFileData(path)
end

function device.showAlertAndroid(title, message, buttonLabels, listener)
end
