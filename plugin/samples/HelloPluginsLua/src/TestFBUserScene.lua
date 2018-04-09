require "cocos.lua_plugin.lua_plugin"

local visibleSize = cc.Director:getInstance():getVisibleSize()
local origin = cc.Director:getInstance():getVisibleOrigin()
local posBR = cc.p(origin.x + visibleSize.width, origin.y)

local TestFBUserScene = class("TestFBUserScene",function()
    return cc.Scene:create()
end)

function TestFBUserScene.create()
    local scene = TestFBUserScene.new()
    return scene
end

function TestFBUserScene:ctor()
    local title = cc.Label:createWithSystemFont("Test Facebook user", "Arial", 32)
    title:setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - 50)
    self:addChild(title)

    local sdkVersion = "SDK Version is: " .. plugin.FacebookAgent:getInstance():getSDKVersion()
    local subTitle = cc.Label:createWithSystemFont(sdkVersion, "Arial", 12)
    subTitle:setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - 74)
    self:addChild(subTitle)

    self:createLayerMenu()

    self.infoLabel = cc.Label:createWithSystemFont("You can see the result at this label", "Arial", 18)

    self.infoLabel:setPosition(origin.x + visibleSize.width - self.infoLabel:getContentSize().width + 100, origin.y + visibleSize.height / 2)
    self.infoLabel:setDimensions(self.infoLabel:getContentSize().width, 0)
    self:addChild(self.infoLabel)
end

function TestFBUserScene:createLayerMenu()

    local backItem = cc.MenuItemFont:create("Back")
    backItem:registerScriptTapHandler(function()
        cc.Director:getInstance():replaceScene(require("HelloWorldScene").create())
    end)
    local backSize = backItem:getContentSize()
    backItem:setPosition(posBR.x - backSize.width / 2, posBR.y + backSize.height / 2)
    local menu = cc.Menu:create(backItem)
    menu:setPosition(cc.p(0,0))
    self:addChild(menu, 1) 

    local menuItemNames =
    {
        {"login", function(tag, sender)
            if plugin.FacebookAgent:getInstance():isLoggedIn() then
                self.infoLabel:setString("already login in")
            else
                plugin.FacebookAgent:getInstance():login(function(ret, msg)
                    self.infoLabel:setString(string.format("type is %d, msg is %s", ret, msg))
                end
                )
            end
        end},

        {"loginWithPermission", function(tag, sender)
            local permissions = "create_event,create_note,manage_pages,publish_actions,user_about_me"
            plugin.FacebookAgent:getInstance():login(permissions, function(ret, msg)
                    self.infoLabel:setString(msg)
                end
            )
        end},

        {"logout", function(tag, sender)
            plugin.FacebookAgent:getInstance():logout()
            self.infoLabel:setString("FacebookAgent: User logout succeed")
        end},

        {"getUid", function(tag, sender)
            if plugin.FacebookAgent:getInstance():isLoggedIn() then
                self.infoLabel:setString(plugin.FacebookAgent:getInstance():getUserID())
            else
                self.infoLabel:setString("User haven't been logged in")
            end
        end},

        {"getToken", function(tag, sender)
            if plugin.FacebookAgent:getInstance():isLoggedIn() then
                self.infoLabel:setString(plugin.FacebookAgent:getInstance():getAccessToken())
            else
                self.infoLabel:setString("User haven't been logged in")
            end  
        end
        },

        {"getPermissions", function(tag, sender)
            local path = "/me/permissions"
            if plugin.FacebookAgent:getInstance():isLoggedIn() then
                plugin.FacebookAgent:getInstance():api(path,  plugin.FacebookAgent.HttpMethod.GET, {}, function(ret, msg)
                    self.infoLabel:setString(msg)
                end)
            else
                self.infoLabel:setString("User haven't been logged in")
            end
        end
        },

        {"request API", function(tag, sender)
            local path = "/me/photos"
            local params = {url = "http://files.cocos2d-x.org/images/orgsite/logo.png"}
            plugin.FacebookAgent:getInstance():api(path,  plugin.FacebookAgent.HttpMethod.POST, params, function(ret, msg)
                if 0 == ret then
                    self.infoLabel:setString(msg)
                end
            end)
        end
        },

        {"logEvent", function(tag, sender)
            local floatVal = 888.888
            local fbInfo = {}
            fbInfo[plugin.FacebookAgent.AppEventParam.SUCCESS] =  plugin.FacebookAgent.AppEventParamValue.VALUE_YES
            plugin.FacebookAgent:getInstance():logEvent(plugin.FacebookAgent.AppEvent.COMPLETED_TUTORIAL, floatVal)
            plugin.FacebookAgent:getInstance():logEvent(plugin.FacebookAgent.AppEvent.COMPLETED_TUTORIAL, fbInfo)
            plugin.FacebookAgent:getInstance():logEvent(plugin.FacebookAgent.AppEvent.COMPLETED_TUTORIAL, floatVal, fbInfo)
            self.infoLabel:setString("logEvent is invoked")
        end
        },

        {"logPurchase", function (tag, sender)
            local mount = 1.23
            local currency = "CNY"
            local fbInfo = {}
            fbInfo[plugin.FacebookAgent.AppEventParam.CURRENCY] = "CNY"
            fbInfo[plugin.FacebookAgent.AppEventParam.REGISTRATION_METHOD] = "Facebook"
            fbInfo[plugin.FacebookAgent.AppEventParam.CONTENT_TYPE] = "game"
            fbInfo[plugin.FacebookAgent.AppEventParam.CONTENT_ID] = "201410102342"
            fbInfo[plugin.FacebookAgent.AppEventParam.SEARCH_STRING] = "cocos2dx-lua"
            fbInfo[plugin.FacebookAgent.AppEventParam.SUCCESS] = plugin.FacebookAgent.AppEventParamValue.VALUE_YES
            fbInfo[plugin.FacebookAgent.AppEventParam.MAX_RATING_VALUE] = "10"
            fbInfo[plugin.FacebookAgent.AppEventParam.PAYMENT_INFO_AVAILABLE] = plugin.FacebookAgent.AppEventParamValue.VALUE_YES
            fbInfo[plugin.FacebookAgent.AppEventParam.NUM_ITEMS] = "99"
            fbInfo[plugin.FacebookAgent.AppEventParam.LEVEL] = "10"
            fbInfo[plugin.FacebookAgent.AppEventParam.DESCRIPTION] = "Cocos2dx-lua"

            plugin.FacebookAgent:getInstance():logPurchase(mount, currency, fbInfo)
            self.infoLabel:setString("Purchase logged.")
        end
        },
    }
    local y_pos = 0
    for i = 1, table.getn(menuItemNames) do
        local label = cc.Label:createWithSystemFont(menuItemNames[i][1], "Arial", 16)
        local menuItem = cc.MenuItemLabel:create(label)
        menuItem:registerScriptTapHandler(menuItemNames[i][2])
        y_pos = visibleSize.height - 24 * (i - 1) - 90
        menuItem:setPosition(origin.x + 100, y_pos)
        menu:addChild(menuItem, 0, i -1 )
    end
end

return TestFBUserScene
