ccb = ccb or {}

function CCBReaderLoad(strFilePath,proxy,owner)
    if nil == proxy then
        return nil
    end

    local ccbReader = proxy:createCCBReader()
    local node      = ccbReader:load(strFilePath)
    local rootName  = "" 
    --owner set in readCCBFromFile is proxy
    if nil ~= owner then
        --Callbacks
        local ownerCallbackNames = ccbReader:getOwnerCallbackNames() 
        local ownerCallbackNodes = ccbReader:getOwnerCallbackNodes()
        local ownerCallbackControlEvents = ccbReader:getOwnerCallbackControlEvents()
        local i = 1
        for i = 1,table.getn(ownerCallbackNames) do
            local callbackName =  ownerCallbackNames[i]
            local callbackNode =  tolua.cast(ownerCallbackNodes[i],"cc.Node")

            if "function" == type(owner[callbackName]) then
                proxy:setCallback(callbackNode, owner[callbackName], ownerCallbackControlEvents[i])
            else
                print("Warning: Cannot find owner's lua function:" .. ":" .. callbackName .. " for ownerVar selector")
            end

        end

        --Variables
        local ownerOutletNames = ccbReader:getOwnerOutletNames() 
        local ownerOutletNodes = ccbReader:getOwnerOutletNodes()

        for i = 1, table.getn(ownerOutletNames) do
            local outletName = ownerOutletNames[i]
            local outletNode = tolua.cast(ownerOutletNodes[i],"cc.Node")
            owner[outletName] = outletNode
        end
    end

    local nodesWithAnimationManagers = ccbReader:getNodesWithAnimationManagers()
    local animationManagersForNodes  = ccbReader:getAnimationManagersForNodes()

    for i = 1 , table.getn(nodesWithAnimationManagers) do
        local innerNode = tolua.cast(nodesWithAnimationManagers[i], "cc.Node")
        local animationManager = tolua.cast(animationManagersForNodes[i], "cc.CCBAnimationManager")
        local documentControllerName = animationManager:getDocumentControllerName()
        if "" == documentControllerName then
            
        end
        if nil ~=  ccb[documentControllerName] then
            ccb[documentControllerName]["mAnimationManager"] = animationManager
        end
        
        --Callbacks
        local documentCallbackNames = animationManager:getDocumentCallbackNames()
        local documentCallbackNodes = animationManager:getDocumentCallbackNodes()
        local documentCallbackControlEvents = animationManager:getDocumentCallbackControlEvents()

        for i = 1,table.getn(documentCallbackNames) do
            local callbackName = documentCallbackNames[i]
            local callbackNode = tolua.cast(documentCallbackNodes[i],"cc.Node")
            if "" ~= documentControllerName and nil ~= ccb[documentControllerName] then
                if "function" == type(ccb[documentControllerName][callbackName]) then
                    proxy:setCallback(callbackNode, ccb[documentControllerName][callbackName], documentCallbackControlEvents[i])
                else
                    print("Warning: Cannot found lua function [" .. documentControllerName .. ":" .. callbackName .. "] for docRoot selector")
                end
            end
        end

        --Variables
        local documentOutletNames = animationManager:getDocumentOutletNames()
        local documentOutletNodes = animationManager:getDocumentOutletNodes()

        for i = 1, table.getn(documentOutletNames) do
            local outletName = documentOutletNames[i]
            local outletNode = tolua.cast(documentOutletNodes[i],"cc.Node")
            
            if nil ~= ccb[documentControllerName] then
                ccb[documentControllerName][outletName] = tolua.cast(outletNode, proxy:getNodeTypeName(outletNode))
            end 
        end
        --[[
        if (typeof(controller.onDidLoadFromCCB) == "function")
            controller.onDidLoadFromCCB();
        ]]--
        --Setup timeline callbacks
        local keyframeCallbacks = animationManager:getKeyframeCallbacks()

        for i = 1 , table.getn(keyframeCallbacks) do
            local callbackCombine = keyframeCallbacks[i]
            local beignIndex,endIndex = string.find(callbackCombine,":")
            local callbackType    = tonumber(string.sub(callbackCombine,1,beignIndex - 1))
            local callbackName    = string.sub(callbackCombine,endIndex + 1, -1)
            --Document callback

            if 1 == callbackType and nil ~= ccb[documentControllerName] then
                local callfunc = cc.CallFunc:create(ccb[documentControllerName][callbackName])
                animationManager:setCallFuncForLuaCallbackNamed(callfunc, callbackCombine);
            elseif 2 == callbackType and nil ~= owner then --Owner callback
                local callfunc = cc.CallFunc:create(owner[callbackName])--need check
                animationManager:setCallFuncForLuaCallbackNamed(callfunc, callbackCombine)
            end
        end
        --start animation
        local autoPlaySeqId = animationManager:getAutoPlaySequenceId()
        if -1 ~= autoPlaySeqId then
            animationManager:runAnimationsForSequenceIdTweenDuration(autoPlaySeqId, 0)
        end
    end

    return node
end


local function CCBuilderReaderLoad(strFilePath,proxy,owner)
    print("\n********** \n".."CCBuilderReaderLoad(strFilePath,proxy,owner)".." was deprecated please use ".. "CCBReaderLoad(strFilePath,proxy,owner)" .. " instead.\n**********")
    return CCBReaderLoad(strFilePath,proxy,owner)
end
rawset(_G,"CCBuilderReaderLoad",CCBuilderReaderLoad)