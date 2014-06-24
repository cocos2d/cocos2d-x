
luaj = require(cc.PACKAGE_NAME .. ".luaj")

function io.exists(path)
    return cc.FileUtils:getInstance():isFileExist(path)
end

function io.readfile(path)
    return cc.FileUtils:getInstance():getFileData(path)
end

function device.showAlertAndroid(title, message, buttonLabels, listener)
end
