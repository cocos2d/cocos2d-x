
require("config")
require("framework.init")
require("app.Utility")
require("app.widget.UIDrag")

local MyApp = class("MyApp", cc.mvc.AppBase)

function MyApp:ctor()
    MyApp.super.ctor(self)
end

function MyApp:run()
    cc.FileUtils:getInstance():addSearchPath("res/")
    self:enterScene("DragScene")
end

return MyApp
