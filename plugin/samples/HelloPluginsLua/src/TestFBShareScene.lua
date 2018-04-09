local visibleSize = cc.Director:getInstance():getVisibleSize()
local origin = cc.Director:getInstance():getVisibleOrigin()
local posBR = cc.p(origin.x + visibleSize.width, origin.y)

local TestFBShareScene = class("TestFBShareScene",function()
    return cc.Scene:create()
end)

function TestFBShareScene.create()
    local scene = TestFBShareScene.new()
    return scene
end

function TestFBShareScene:ctor()
    local title = cc.Label:createWithSystemFont("Test Facebook share", "Arial", 32)
    title:setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - 50)
    self:addChild(title)

    local sdkVersion = "SDK Version is: " .. plugin.FacebookAgent:getInstance():getSDKVersion()
    local subTitle = cc.Label:createWithSystemFont(sdkVersion, "Arial", 12)
    subTitle:setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - 74)
    self:addChild(subTitle)

    self:createLayerMenu()
end

function TestFBShareScene:sceenshot(filename)
    local visibleSize = cc.Director:getInstance():getVisibleSize()
    local origin = cc.Director:getInstance():getVisibleOrigin()
    local tex = cc.RenderTexture:create(visibleSize.width, visibleSize.height, cc.TEXTURE2_D_PIXEL_FORMAT_RGB_A8888)
    tex:setPosition((origin.x + visibleSize.width) / 2, (origin.y + visibleSize.height) / 2)
    tex:begin()
    cc.Director:getInstance():getRunningScene():visit()
    tex:endToLua()
    
    local imgPath = cc.FileUtils:getInstance():getWritablePath()
    if imgPath == "" then 
        return ""
    end
    
    
    local ret = tex:saveToFile(filename, cc.IMAGE_FORMAT_JPEG)
    if ret then
        imgPath = imgPath .. filename
        print(string.format("save image to %s", imgPath))
        return imgPath
    end

    return ""
end

local secondMenuItem_SL = {
    {"share a simple link", function(tag, sender)
        local params = {
            dialog = "share_link",
            link   = "http://www.cocos2d-x.org",
        }

        if plugin.FacebookAgent:getInstance():canPresentDialogWithParams(params) then
            plugin.FacebookAgent:getInstance():dialog(params, function(ret, msg)
                print(msg)
            end)
        else
            params.dialog = "feed_dialog"
            plugin.FacebookAgent:getInstance():dialog(params, function(ret, msg)
                print(msg)
            end)
        end
    end},

    {"share a Text link", function(tag, sender)
        local params = {
            dialog = "share_link",
            name   = "Cocos2dx-lua web site",
            caption = "Cocos2dx-lua caption",
            description = "Cocos2dx-lua description",
            link   = "http://www.cocos2d-x.org",
        }

        if plugin.FacebookAgent:getInstance():canPresentDialogWithParams(params) then
            plugin.FacebookAgent:getInstance():dialog(params, function(ret, msg)
                print(msg)
            end)
        else
            params.dialog = "feed_dialog"
            plugin.FacebookAgent:getInstance():dialog(params, function(ret, msg)
                print(msg)
            end)
        end
    end},

    {"share a Picture link", function(tag, sender)
        local params = {
            dialog = "share_link",
            name   = "Cocos2dx-lua web site",
            caption = "Cocos2dx-lua caption",
            description = "Cocos2dx-lua description",
            to  = "100006738453912",--android only web view support
            picture = "http://files.cocos2d-x.org/images/orgsite/logo.png",
            link   = "http://www.cocos2d-x.org",
        }

        if plugin.FacebookAgent:getInstance():canPresentDialogWithParams(params) then
            plugin.FacebookAgent:getInstance():dialog(params, function(ret, msg)
                print(msg)
            end)
        else
            params.dialog = "feed_dialog"
            plugin.FacebookAgent:getInstance():dialog(params, function(ret, msg)
                print(msg)
            end)
        end
    end},

    {"share a media link", function(tag, sender)
        local params = {
            dialog = "share_link",
            name   = "Cocos2dx-lua web site",
            caption = "Cocos2dx-lua caption",
            description = "Cocos2dx-lua description",
            media_source  = "http://221.203.1.212/youku/6775B002C8F48839F6AFA63BDA/0300200100540438A173C515AA2BED245C4903-F675-B311-EF1A-4544B5C04370.mp4",
            link   = "http://www.cocos2d-x.org",
        }

        -- only support in web dialog
        plugin.FacebookAgent:getInstance():dialog(params, function(ret, msg)
            print(msg)
        end)
    end},
}

local secondMenuItem_AR = {

    {"Invites request", function(tag, sender)
        local params = {
            message = "Cocos2dx-lua is a great game engine",
            title   = "Cocos2dx-lua title",
        }

        plugin.FacebookAgent:getInstance():appRequest(params, function(ret, msg)
            print(msg)
        end)
    end},

    {"Target invite request", function(tag, sender)
        local params = {
            message = "Cocos2dx-lua is a great game engine",
            title   = "Cocos2dx-lua title",
            to = "100006738453912, 10204182777160522",
        }
        --android only web view support to
        plugin.FacebookAgent:getInstance():appRequest(params, function(ret, msg)
            print(msg)
        end)
    end},

    {"Specific lists of friends", function(tag, sender)
        local params = {
            message = "Cocos2dx-lua is a great game engine",
            title   = "Cocos2dx-lua title",
            filters = "[{\"name\":\"company\", \"user_ids\":[\"100006738453912\",\"10204182777160522\"]}]",
        }
        -- android not support filters
        plugin.FacebookAgent:getInstance():appRequest(params, function(ret, msg)
            print(msg)
        end)
    end},

    {"Sending requests explicitly", function(tag, sender)
        local params = {
            message = "Cocos2dx-lua is a great game engine",
            to = "100006738453912",
            action_type = "send",
            object_id   = "191181717736427",-- 191181717736427   1426774790893461
        }
        --android not support action_type
        plugin.FacebookAgent:getInstance():appRequest(params, function(ret, msg)
            print(msg)
        end)
    end},

    {"Turn-based games", function(tag, sender)

        local params = {
            message = "Cocos2dx-lua is a great game engine",
            title   = "Cocos2dx-lua title",
            to = "100006738453912",
            action_type = "turn",
        }
        -- android not support action_type
        plugin.FacebookAgent:getInstance():appRequest(params, function(ret, msg)
            print(msg)
        end)
    end},
}

function TestFBShareScene:showSecondMenu(tag)
    local secondMenu = self:getChildByTag(2)
    if nil ~= secondMenu then
        local visibleSize = cc.Director:getInstance():getVisibleSize()
        local origin = cc.Director:getInstance():getVisibleOrigin()
        local posBR = cc.p(origin.x + visibleSize.width, origin.y)
        
        secondMenu:removeAllChildren()
        local top = 90

        if 0 == tag then
            for i = 1, table.getn(secondMenuItem_SL) do
                local label = cc.Label:createWithSystemFont(secondMenuItem_SL[i][1], "Arial", 18)
                local menuItem = cc.MenuItemLabel:create(label)
                menuItem:registerScriptTapHandler(secondMenuItem_SL[i][2])
                menuItem:setPosition(cc.p(visibleSize.width / 9, visibleSize.height - top))
                secondMenu:addChild(menuItem, 0, i - 1 )
                top = top + 50
            end
        else
            for i = 1, table.getn(secondMenuItem_AR) do
                local label = cc.Label:createWithSystemFont(secondMenuItem_AR[i][1], "Arial", 18)
                local menuItem = cc.MenuItemLabel:create(label)
                menuItem:registerScriptTapHandler(secondMenuItem_AR[i][2])
                menuItem:setPosition(cc.p(visibleSize.width / 9, visibleSize.height - top))
                secondMenu:addChild(menuItem, 0, i - 1 )
                top = top + 50
            end
        end
    end
end

function TestFBShareScene:createLayerMenu()

    local backItem = cc.MenuItemFont:create("Back")
    backItem:registerScriptTapHandler(function()
        cc.Director:getInstance():replaceScene(require("HelloWorldScene").create())
    end)
    local backSize = backItem:getContentSize()
    backItem:setPosition(posBR.x - backSize.width / 2, posBR.y + backSize.height / 2)
    local menu = cc.Menu:create(backItem)
    menu:setPosition(cc.p(0,0))
    self:addChild(menu, 0, 1) 

    local menuItemNames =
    {
        {"Share link", function(tag, sender)
            self:showSecondMenu(0)
        end},

        {"Share open graph", function(tag, sender)
            local params = {
            dialog = "share_open_graph",
            action_type = "cocostestmyfc:share",
            preview_property_name =  "cocos_document",
            title = "Cocos2dx-lua Game Engine",
            image =  "http://files.cocos2d-x.org/images/orgsite/logo.png",
            url = "http://cocos2d-x.org/docs/catalog/en",
            description = "cocos document",
            }

            if plugin.FacebookAgent:getInstance():canPresentDialogWithParams(params) then
                plugin.FacebookAgent:getInstance():dialog(params, function(ret, msg)
                    print(msg)
                end)
            else
                print("Can't open dialog for share_open_graph")
            end
        end},

        {"Share photo", function(tag, sender)
            local fileName = "facebookshare.jpg"
            local imgPath = self:sceenshot(fileName)
            
            local delay = cc.DelayTime:create(2.0)
            local share = cc.CallFunc:create(function( ... )
                    local params = {
                        dialog = "share_photo",
                        photo  = imgPath,
                    }

                    if plugin.FacebookAgent:getInstance():canPresentDialogWithParams(params) then
                            plugin.FacebookAgent:getInstance():dialog(params, function(ret, msg)
                            print(msg)
                        end)
                    else
                        print("Can't open dialog for share_open_graph")
                    end
                end)
            
            local seq = cc.Sequence:create(delay, share)
            self:runAction(seq)
        end},

        {"Link message", function(tag, sender)
            local params = {
                dialog = "message_link",
                description =  "Cocos2dx-lua is a great game engine",
                title = "Cocos2dx-lua",
                link = "http://www.cocos2d-x.org",
                imageUrl = "http://files.cocos2d-x.org/images/orgsite/logo.png",
            }

            if plugin.FacebookAgent:getInstance():canPresentDialogWithParams(params) then
                plugin.FacebookAgent:getInstance():dialog(params, function(ret, msg )
                    print(msg)
                end)
            else
                print("Can't open dialog for message_link")
            end
        end},

        {"Open graph message", function(tag, sender)
            local params = {
                dialog = "share_open_graph",
                action_type = "cocostestmyfc:share",
                preview_property_name = "cocos_document",
                title =  "Cocos2dx-lua Game Engine",
                image = "http://files.cocos2d-x.org/images/orgsite/logo.png",
                url =  "http://cocos2d-x.org/docs/catalog/en",
                description =  "cocos document",
            }

            if plugin.FacebookAgent:getInstance():canPresentDialogWithParams(params) then
                plugin.FacebookAgent:getInstance():dialog(params, function(ret, msg )
                    print(msg)
                end)
            else
                print("Can't open dialog for message_open_graph")
            end
        end},

        {"Photo message", function(tag, sender)
            local fileName = "facebookmessage.jpg"
            local imgPath = self:sceenshot(fileName)
            
            local delay = cc.DelayTime:create(2.0)
            local share = cc.CallFunc:create(function()
                local params = {
                    dialog = "message_photo",
                    photo  = imgPath,
                }
                if plugin.FacebookAgent:getInstance():canPresentDialogWithParams(params) then
                    plugin.FacebookAgent:getInstance():dialog(params, function(ret, msg )
                        print(msg)
                    end)
                else
                    print("Can't open dialog for message_photo")
                end
            end)
            
            local seq = cc.Sequence:create(delay, share)
            self:runAction(seq)
        end},
        {"App request", function(tag, sender)
            self:showSecondMenu(1)
        end},
    }

    local y_pos = 0
    for i = 1, table.getn(menuItemNames) do
        local label = cc.Label:createWithSystemFont(menuItemNames[i][1], "Arial", 22)
        local menuItem = cc.MenuItemLabel:create(label)
        menuItem:registerScriptTapHandler(menuItemNames[i][2])
        y_pos = visibleSize.height - 35 * (i - 1) - 100
        menuItem:setPosition(origin.x + 100, y_pos)
        menu:addChild(menuItem, 0, i -1 )
    end

    --create second menu
    local secondMenu = cc.Menu:create()
    secondMenu:setPosition(cc.p(340, 0))
    self:addChild(secondMenu, 0, 2) 
end

return TestFBShareScene
