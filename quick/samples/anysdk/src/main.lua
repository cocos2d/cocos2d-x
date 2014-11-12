
cc.FileUtils:getInstance():addSearchPath("src")
cc.FileUtils:getInstance():addSearchPath("res")

require "cocos.init"

-- cclog
cclog = function(...)
    print(string.format(...))
end

-- for CCLuaEngine traceback
function __G__TRACKBACK__(msg)
    cclog("----------------------------------------")
    cclog("LUA ERROR: " .. tostring(msg) .. "\n")
    cclog(debug.traceback())
    cclog("----------------------------------------")
    return msg
end

local function main()
    collectgarbage("collect")
    -- avoid memory leak
    collectgarbage("setpause", 100)
    collectgarbage("setstepmul", 5000)
    cc.Director:getInstance():getOpenGLView():setDesignResolutionSize(480, 320, 0);
    cc.Director:getInstance():setDisplayStats(false);
	cc.FileUtils:getInstance():addSearchResolutionsOrder("src");
	cc.FileUtils:getInstance():addSearchResolutionsOrder("res");
	local schedulerID = 0

    --support debug
    local targetPlatform = cc.Application:getInstance():getTargetPlatform()
    if (cc.PLATFORM_OS_ANDROID ~= targetPlatform) then
        local hint = cc.Label:createWithSystemFont("Please run on android", "Helvetica", 24)
        hint:setTextColor(cc.c4b(255, 255, 255, 255))
        hint:setPosition(240, 160)

        local sceneGame = cc.Scene:create()
        sceneGame:addChild(hint)
        
        if cc.Director:getInstance():getRunningScene() then
            cc.Director:getInstance():replaceScene(sceneGame)
        else
            cc.Director:getInstance():runWithScene(sceneGame)
        end
        return
    end

    require "anysdkConst"

    --for anysdk
    local agent = AgentManager:getInstance()
    cclog("agent is---" .. type(agent))
    --init
    local appKey = "BA5B660B-6DD5-0F67-8CC7-8FE0BA7545D6";
    local appSecret = "e23ae7d6da34334d4cc11df0dc7f3de0";
    local privateKey = "76E1D975EA4B9A4ECD0E85AF2D782E99";
    local oauthLoginServer = "http://oauth.anysdk.com/api/OauthLoginDemo/Login.php";
    agent:init(appKey,appSecret,privateKey,oauthLoginServer)
    --load
    agent:loadALLPlugin()
    local user_plugin = agent:getUserPlugin()
    cclog("getUserPlugin()--" .. type(user_plugin))
    local ads_plugin = agent:getAdsPlugin()
    local social_plugin =  agent:getSocialPlugin()
    local share_plugin =  agent:getSharePlugin()
    local push_plugin =  agent:getPushPlugin()
    local analytics_plugin =  agent:getAnalyticsPlugin()

    local function onResult( ... )
        print("pay result----")
    end
    iap_plugin_maps = agent:getIAPPlugin()
    for key, value in pairs(iap_plugin_maps) do
        print("key:" .. key)
        cclog("value: " .. type(value))
        value:setResultListener(onResult)
    end
    --login
    -- user_plugin:login()
    
    --add user action listener
    local function onActionListener( ... )
    	print("on user action listener.")
        print("agent is ", agent, "user_plugin is " , user_plugin)
    end
    user_plugin:setActionListener(onActionListener)

    --add user share listener
    local function onSharedResultListener( ... )
        print("on user shared result listener.")
    end
    if nil ~= share_plugin then
        share_plugin:setResultListener(onSharedResultListener)
    else
        cclog("share_plugin is nil.")
    end

    --add social listener
    local function onSocialResultListener( ... )
        print("on social result listener.")
    end
    if nil ~= social_plugin then
        social_plugin:setListener(onSocialResultListener)
    else
        cclog("social_plugin is nil.")
    end
    ---------------

    local visibleSize = cc.Director:getInstance():getVisibleSize()
    local origin = cc.Director:getInstance():getVisibleOrigin()

    function CreatEnumTable(tbl, index) 
        local enumtbl = {} 
        local enumindex = index or 0 
        for i, v in ipairs(tbl) do 
            enumtbl[v] = enumindex + i - 1
        end 
        return enumtbl 
    end 
    -- add buttons
    -- local function addButton()
    --     l
    -- end
    base_menu = {
        "USER_SYS",
        "IAP_SYS",
        "SHARE_SYS",
        "ADS_SYS",
        "SOCIAL_SYS",
        "PUSH_SYS",
    }
    base_menu = CreatEnumTable(base_menu, 1)
    local info_btns = {
        {text = "User system", tag = base_menu.USER_SYS},
        {text = "IAP system", tag = base_menu.IAP_SYS},
        {text = "Share system", tag = base_menu.SHARE_SYS},
        {text = "Ads system", tag = base_menu.ADS_SYS},
        {text = "Social system", tag = base_menu.SOCIAL_SYS},
        {text = "Push system", tag = base_menu.PUSH_SYS}
    }
    user_menu = {
        "LOGIN",
        "LOGOUT",
        "ENTER_PLATFORM",
        "SHOW_TOOLBAR",
        "HIDE_TOOLBAR",
        "ACCOUNTSWITCH_PAY",
        "REALNAME_REGISTER",
        "ANTI_ADDICTION_QUERY",
        "SUBMIT_LOGIN_GAMEROLE",
    }
    user_menu = CreatEnumTable(user_menu, 100)
    local user_btns = {
        {text = "login", tag = user_menu.LOGIN},
        {text = "logout", tag = user_menu.LOGOUT},
        {text = "enterPlatform", tag = user_menu.ENTER_PLATFORM},
        {text = "showToolBar", tag = user_menu.SHOW_TOOLBAR},
        {text = "hideToolBar", tag = user_menu.HIDE_TOOLBAR},
        {text = "accountSwitch pay", tag = user_menu.ACCOUNTSWITCH_PAY},
        {text = "realNameRegister", tag = user_menu.REALNAME_REGISTER},
        {text = "antiAddictionQuery", tag = user_menu.ANTI_ADDICTION_QUERY},
        {text = "submitLoginGameRole", tag = user_menu.SUBMIT_LOGIN_GAMEROLE}
    }
    iap_menu = {"PAY"}
    iap_menu = CreatEnumTable(iap_menu, 200)
    local iap_btns = {
        {text="pay", tag = iap_menu.PAY}
    }
    share_menu = {"SHARE"}
    share_menu = CreatEnumTable(share_menu, 300)
    local share_btns = {
        {text="share", tag = share_menu.SHARE}
    }
    ads_menu = {"SHOW_ADS", "HIDE_ADS"}
    ads_menu = CreatEnumTable(ads_menu, 400)
    local ads_btns = {
        {text="show ads", tag = ads_menu.SHOW_ADS},
        {text="hide ads", tag = ads_menu.HIDE_ADS}
    }
    social_menu = {
        "SUBMIT_SCORE", 
        "SHOW_LEADERBOARD", 
        "UNLOCK_ACHIEVEMENT", 
        "SHOW_ACHIEVEMENT"
    }
    social_menu = CreatEnumTable(social_menu, 500)
    local social_btns = {
        {text="submit score", tag = social_menu.SUBMIT_SCORE},
        {text="show Leaderboard", tag = social_menu.SHOW_LEADERBOARD},
        {text="unlock achievement", tag = social_menu.UNLOCK_ACHIEVEMENT},
        {text="show achievements", tag = social_menu.SHOW_ACHIEVEMENT}
    }
    push_menu = {
        "CLOSE_PUSH", 
        "SET_ALIAS", 
        "DEL_ALIAS", 
        "SET_TAGS", 
        "DEL_TAGS"
    }
    push_menu = CreatEnumTable(push_menu, 600)
    local push_btns = {
        {text="close push", tag = push_menu.CLOSE_PUSH},
        {text="set Alias", tag = push_menu.SET_ALIAS},
        {text="del Alias", tag = push_menu.DEL_ALIAS},
        {text="set Tags", tag = push_menu.SET_TAGS},
        {text="del Tags", tag = push_menu.DEL_TAGS}
    }
    local sec_infos = {
        user_btns, iap_btns, share_btns, ads_btns, social_btns, push_btns
    }
    local FONT_SIZE = 24
    local current_menu_idx = -1
    local display_second_menu = false

    local function createClickLayer()
        local pLayer = cc.Layer:create()
        local menu = cc.Menu:create()
        menu:setPosition(0, 0)
        pLayer:addChild(menu)

        local x = 100
        local y = 310
        local h = 43
        
        local function createBtn(str, tag, pos)
            local lb = cc.Label:createWithSystemFont(str, "Helvetica", FONT_SIZE)
            lb:setTextColor(cc.c4b(255, 255, 255, 255))
            local btn = cc.MenuItemLabel:create(lb)
            btn:setPosition(pos)
            btn:setTag(tag)
            return btn
        end
        local BASE_LEVEL = 100
        local USER_LEVEL = 200
        local IAP_LEVEL = 300
        local SHARE_LEVEL = 400
        local ADS_LEVEL = 500
        local SOCIAL_LEVEL = 600
        local PUSH_LEVEL = 700
        local sec_btns = {}
        local sec_top_arr = {}
        local sec_top_idx = 0
        local function menuCallback(item)
            cclog("on click:%d", item)
            x = 300
            if item == base_menu.USER_SYS then
                y = 320
                h = 31.5
            elseif item == base_menu.ADS_SYS then
                y = 330
                h = 35
            else
                y = 300
                h = 35
            end

            local function createBtns( tb )
                local arr = {}
                for i=1, #(tb) do
                    local btn = createBtn(tb[i].text, tb[i].tag, cc.p(x, y-i*h))
                    btn:registerScriptTapHandler(menuCallback)
                    menu:addChild(btn)
                    arr[i] = btn
                end
                return arr
            end
            local function setBtnState( tb )
                local visible = tb[1]:isVisible()
                cclog("is visible: " .. type(visible))
                for i=1, #(tb) do
                    tb[i]:setVisible(not visible)
                end
            end
            local function setOtherInvisible( idx )
                local function setInvisible(tb)
                    if tb == nil then
                        return
                    end
                    for i=1, #(tb) do
                        tb[i]:setVisible(false)
                    end
                end
                print("sec_btns count:" .. #(sec_btns))
                for i=1, #(sec_top_arr) do
                    setInvisible(sec_btns[sec_top_arr[i]])
                end
            end

            if item < BASE_LEVEL then
                setOtherInvisible()
                if item ~= current_menu_idx then
                    if sec_btns[item] == nil then
                        sec_btns[item] = createBtns(sec_infos[item])
                        sec_top_idx = sec_top_idx + 1
                        sec_top_arr[sec_top_idx] = item
                    else
                        setBtnState(sec_btns[item])
                    end
                    display_second_menu = true
                    current_menu_idx = item
                elseif display_second_menu then
                    display_second_menu = false
                    current_menu_idx = -1
                end
            elseif item < USER_LEVEL then
                if item == user_menu.LOGIN then
                    user_plugin:login()
                    analytics_plugin:logEvent("login")
                elseif item == user_menu.LOGOUT then
                    if user_plugin:isFunctionSupported("logout") then
                        user_plugin:callFuncWithParam("logout")
                    end
                elseif item == user_menu.ENTER_PLATFORM then
                    if user_plugin:isFunctionSupported("enterPlatform") then
                        user_plugin:callFuncWithParam("enterPlatform")
                    end
                elseif item == user_menu.SHOW_TOOLBAR then
                    if user_plugin:isFunctionSupported("showToolBar") then
                        local param1 = PluginParam:create(ToolBarPlace.kToolBarTopLeft)
                        user_plugin:callFuncWithParam("showToolBar", {param1})
                    end
                elseif item == user_menu.HIDE_TOOLBAR then
                    if user_plugin:isFunctionSupported("hideToolBar") then
                        user_plugin:callFuncWithParam("hideToolBar")
                    end
                elseif item == user_menu.ACCOUNTSWITCH_PAY then
                    if user_plugin:isFunctionSupported("accountSwitch") then
                        user_plugin:callFuncWithParam("accountSwitch")
                    end
                elseif item == user_menu.REALNAME_REGISTER then
                    if user_plugin:isFunctionSupported("realNameRegister") then
                        user_plugin:callFuncWithParam("realNameRegister")
                    end
                elseif item == user_menu.ANTI_ADDICTION_QUERY then
                    if user_plugin:isFunctionSupported("antiAddictionQuery") then
                        user_plugin:callFuncWithParam("antiAddictionQuery")
                    end
                elseif item == user_menu.SUBMIT_LOGIN_GAMEROLE then
                    if user_plugin:isFunctionSupported("submitLoginGameRole") then
                        local data = PluginParam:create({roleId="123456",roleName="test",roleLevel="10",zoneId="123",zoneName="test",dataType="1",ext="login"})
                        user_plugin:callFuncWithParam("submitLoginGameRole", data)
                    end
                end
            elseif item < IAP_LEVEL then
                if item == iap_menu.PAY then
                    cclog("on clicked pay.")
                    
                    local info = {
                    		Product_Price="1", 
                    		Product_Id="monthly",  
                    		Product_Name="gold",  
                    		Server_Id="13",  
                    		Product_Count="1",  
                    		Role_Id="1001",  
                    		Role_Name="asd"
                    	}
                    analytics_plugin:logEvent("pay", info)
                    for key, value in pairs(iap_plugin_maps) do
                        print("key:" .. key)
                        cclog("value: " .. type(value))
                        value:payForProduct(info)
                    end
                end
            elseif item < SHARE_LEVEL then
                if item == share_menu.SHARE then
                    cclog("on clicked share.")
                    if share_plugin ~= nil then
                        local info = {
                            title = "ShareSDK是一个神奇的SDK",
                            titleUrl = "http://sharesdk.cn",
                            site = "ShareSDK",
                            siteUrl = "http://sharesdk.cn",
                            text = "ShareSDK集成了简单、支持如微信、新浪微博、腾讯微博等社交平台",
                            comment = "无",
                        }
                        share_plugin:share(info)
                        analytics_plugin:logEvent("share")
                    end
                end
            elseif item < ADS_LEVEL then
                if item == ads_menu.SHOW_ADS then
                    if ads_plugin ~= nil then
                        ads_plugin:showAds(AdsType.AD_TYPE_FULLSCREEN)
                        -- if ads_plugin:isFunctionSupported("AD_TYPE_FULLSCREEN") then
                        --     ads_plugin:showAds(AdsType.AD_TYPE_FULLSCREEN)
                        -- end
                    end
                elseif item == ads_menu.HIDE_ADS then
                    if ads_plugin ~= nil then
                        ads_plugin:hideAds(AdsType.AD_TYPE_FULLSCREEN)
                        -- if ads_plugin:isFunctionSupported("AD_TYPE_FULLSCREEN") then
                        --     ads_plugin:hideAds(AdsType.AD_TYPE_FULLSCREEN)
                        -- end
                    end
                end
            elseif item < SOCIAL_LEVEL then
                if social_plugin ~= nil then
                    cclog("on clicked social.")
                    if item == social_menu.SUBMIT_SCORE then
                        local score = 132   --score
                        social_plugin:submitScore("friend", score)
                        social_plugin:signIn();
                        social_plugin:signOut();
                    elseif item == social_menu.SHOW_LEADERBOARD then
                        social_plugin:showLeaderboard("friend");
                    elseif item == social_menu.UNLOCK_ACHIEVEMENT then
                        local achInfo = {rank="friends"}
                        social_plugin:unlockAchievement(achInfo);
                    elseif item == social_menu.SHOW_ACHIEVEMENT then
                        social_plugin:showAchievements();
                        analytics_plugin:logEvent("showAchievements");
                    end
                end
            elseif item < PUSH_LEVEL then
                cclog("on clicked push.")
                if push_plugin ~= nil then
                    if item == push_menu.CLOSE_PUSH then
                        push_plugin:closePush()
                    elseif item == push_menu.SET_ALIAS then
                        push_plugin:setAlias("AnySDK")
                    elseif item == push_menu.DEL_ALIAS then
                        push_plugin:delAlias("AnySDK")
                    elseif item == push_menu.SET_TAGS then
                        push_plugin:setTags({"easy","fast","qwe"})
                    elseif item == push_menu.DEL_TAGS then
                        push_plugin:delTags({"easy","qwe"})
                    end
                end
            end
        end
        
        for i=1, #(info_btns) do
            local btn = createBtn(info_btns[i].text, info_btns[i].tag, cc.p(x, y-i*h))
            btn:registerScriptTapHandler(menuCallback)
            menu:addChild(btn)
        end

        return pLayer
    end
    local operateLy = createClickLayer()

    -- run
    local sceneGame = cc.Scene:create()
    sceneGame:addChild(operateLy)
	
	if cc.Director:getInstance():getRunningScene() then
		cc.Director:getInstance():replaceScene(sceneGame)
	else
		cc.Director:getInstance():runWithScene(sceneGame)
	end

end


local status, msg = xpcall(main, __G__TRACKBACK__)
if not status then
    error(msg)
end
