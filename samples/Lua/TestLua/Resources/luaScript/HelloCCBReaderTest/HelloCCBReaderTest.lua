--local  ccbRootPath = "ccb/Published-iOS/"
require "CCBReaderLoad"

MainScene = MainScene or {}
ccb["MainScene"] = MainScene

MainSceneProxy = MainSceneProxy or {}
ccb["MainSceneProxy"] = MainSceneProxy

local function onBtnTilteClick()
    if nil ~= MainScene["helloLabel"] then
        local pHelloLabel = tolua.cast(MainScene["helloLabel"],"CCLabelTTF")
        if nil ~= pHelloLabel then
            pHelloLabel:setString("Title Click")
        end
    end
end

local function onCallFun1()
    if nil ~= MainScene["helloLabel"] then
        local pHelloLabel = tolua.cast(MainScene["helloLabel"],"CCLabelTTF")
        if nil ~= pHelloLabel then
            pHelloLabel:runAction(CCRotateBy:create(1, 360))
            pHelloLabel:setString("Callback 1")
        end
    end
end
MainScene["onBtnTilteClick"] = onBtnTilteClick
MainScene["onCallFun1"]      = onCallFun1

local function onPressButton()
    if nil ~= MainScene["helloLabel"] then
        local pHelloLabel = tolua.cast(MainScene["helloLabel"],"CCLabelTTF")
        if nil ~= pHelloLabel then
            pHelloLabel:setString("Hello CocosBuild")
        end
    end
end

local function onCallFun2()
    if nil ~= MainScene["helloLabel"] then
        local pHelloLabel = tolua.cast(MainScene["helloLabel"],"CCLabelTTF")
        if nil ~= pHelloLabel then
            pHelloLabel:runAction(CCRotateBy:create(1, -360))
            pHelloLabel:setString("Callback 2")
        end
    end
end
MainSceneProxy["onPressButton"] = onPressButton
MainSceneProxy["onCallFun2"]    = onCallFun2

local function HelloCCBReaderTestMainLayer()
    CCFileUtils:sharedFileUtils():loadFilenameLookupDictionaryFromFile("fileLookup.plist")
    local  proxy = CCBProxy:create()
    local  node  = CCBReaderLoad("ccb/Published-iOS/MainScene.ccbi",proxy,true,"MainSceneProxy")
    local  layer = tolua.cast(node,"CCLayer")
    return layer
end

function HelloCCBReaderTestMain()
    cclog("HelloCCBReaderTestMain");
    local scene = CCScene:create();
    scene:addChild(HelloCCBReaderTestMainLayer());
    scene:addChild(CreateBackMenuItem());
    return scene;
end
