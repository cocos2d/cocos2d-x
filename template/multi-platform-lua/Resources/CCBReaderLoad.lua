ccb = ccb or {}

function CCBReaderLoad(strFilePath,proxy,bSetOwner,strOwnerName)
    if nil == proxy then
        return
    end

    local ccbReader = proxy:createCCBReader()
    local node      = proxy:readCCBFromFile(strFilePath,ccbReader,bSetOwner)
    local owner     = ccbReader:getOwner()
    local rootName  = "" 
    --owner set in readCCBFromFile is proxy
    if nil ~= owner then

        --Callbacks
        local ownerCallbackNames = tolua.cast(ccbReader:getOwnerCallbackNames(),"CCArray")
        local ownerCallbackNodes = tolua.cast(ccbReader:getOwnerCallbackNodes(),"CCArray")
        local i = 1
        for i = 1,ownerCallbackNames:count() do
            local callbackName = tolua.cast(ownerCallbackNames:objectAtIndex(i - 1),"CCString")
            local callbackNode = tolua.cast(ownerCallbackNodes:objectAtIndex(i - 1),"CCNode")
            if "" ~= strOwnerName and nil ~= ccb[strOwnerName] then
            	local cbName = callbackName:getCString()
            	if "function" == type(ccb[strOwnerName][cbName]) then
                	proxy:setCallback(callbackNode,ccb[strOwnerName][cbName])
                else
                	print("WARNING: Cannot found lua function [" .. strOwnerName .. "." .. cbName .. "] for owner selector")
                end
            end
        end

        --Variables
        local ownerOutletNames = tolua.cast(ccbReader:getOwnerOutletNames(),"CCArray")
        local ownerOutletNodes = tolua.cast(ccbReader:getOwnerOutletNodes(),"CCArray")

        for i = 1, ownerOutletNames:count() do
            local outletName = tolua.cast(ownerOutletNames:objectAtIndex(i - 1),"CCString")
            local outletNode = tolua.cast(ownerOutletNodes:objectAtIndex(i - 1),"CCNode")

            if "" ~= strOwnerName and nil ~= ccb[strOwnerName] then
                ccb[strOwnerName][outletName:getCString()] = tolua.cast(outletNode, proxy:getNodeTypeName(outletNode))
            end
        end
    end

    local nodesWithAnimationManagers = tolua.cast(ccbReader:getNodesWithAnimationManagers(),"CCArray")
    local animationManagersForNodes  = tolua.cast(ccbReader:getAnimationManagersForNodes(),"CCArray")

    for i = 1 , nodesWithAnimationManagers:count() do
        local innerNode = tolua.cast(nodesWithAnimationManagers:objectAtIndex(i - 1),"CCNode")
        local animationManager = tolua.cast(animationManagersForNodes:objectAtIndex(i - 1),"CCBAnimationManager")
        local documentControllerName = animationManager:getDocumentControllerName()
        if "" == documentControllerName then
            
        end
        if nil ~=  ccb[documentControllerName] then
            ccb[documentControllerName]["mAnimationManager"] = animationManager
        end
        
        --Callbacks
        local documentCallbackNames = tolua.cast(animationManager:getDocumentCallbackNames(),"CCArray")
        local documentCallbackNodes = tolua.cast(animationManager:getDocumentCallbackNodes(),"CCArray")

        for i = 1,documentCallbackNames:count() do
            local callbackName = tolua.cast(documentCallbackNames:objectAtIndex(i - 1),"CCString")
            local callbackNode = tolua.cast(documentCallbackNodes:objectAtIndex(i - 1),"CCNode")
            if "" ~= documentControllerName and nil ~= ccb[documentControllerName] then
                --proxy:setCallback(callbackNode,ccb[documentControllerName][callbackName:getCString()])
          		local cbName = callbackName:getCString()
            	if "function" == type(ccb[documentControllerName][cbName]) then
                	proxy:setCallback(callbackNode,ccb[documentControllerName][cbName])
                else
                	print("WARNING: Cannot found lua function [" .. documentControllerName .. "." .. cbName .. "] for docRoot selector")
                end
            end
        end

        --Variables
        local documentOutletNames = tolua.cast(animationManager:getDocumentOutletNames(),"CCArray")
        local documentOutletNodes = tolua.cast(animationManager:getDocumentOutletNodes(),"CCArray")

        for i = 1, documentOutletNames:count() do
            local outletName = tolua.cast(documentOutletNames:objectAtIndex(i - 1),"CCString")
            local outletNode = tolua.cast(documentOutletNodes:objectAtIndex(i - 1),"CCNode")

            if nil ~= ccb[documentControllerName] then
                ccb[documentControllerName][outletName:getCString()] = tolua.cast(outletNode, proxy:getNodeTypeName(outletNode))
            end 
        end
        --[[
        if (typeof(controller.onDidLoadFromCCB) == "function")
            controller.onDidLoadFromCCB();
        ]]--
        --Setup timeline callbacks
        local keyframeCallbacks = animationManager:getKeyframeCallbacks()

        for i = 1 , keyframeCallbacks:count() do
            local callbackCombine = tolua.cast(keyframeCallbacks:objectAtIndex(i - 1),"CCString"):getCString()
            local beignIndex,endIndex = string.find(callbackCombine,":")
            local callbackType    = tonumber(string.sub(callbackCombine,1,beignIndex - 1))
            local callbackName    = string.sub(callbackCombine,endIndex + 1, -1)
            --Document callback

            if 1 == callbackType and nil ~= ccb[documentControllerName] then
                local callfunc = CCCallFunc:create(ccb[documentControllerName][callbackName])
                animationManager:setCallFuncForLuaCallbackNamed(callfunc, callbackCombine);
            elseif 2 == callbackType and nil ~= owner then --Owner callback
                local callfunc = CCCallFunc:create(ccb[strOwnerName][callbackName])
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
