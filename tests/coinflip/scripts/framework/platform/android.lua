
luaj = require(cc.PACKAGE_NAME .. ".luaj")

function io.exists(path)
    return CCFileUtils:sharedFileUtils():isFileExist(path)
end

function io.readfile(path)
    return CCFileUtils:sharedFileUtils():getFileData(path)
end

function device.showAlertAndroid(title, message, buttonLabels, listener)
end
