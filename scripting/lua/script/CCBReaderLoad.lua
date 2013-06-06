ccb = ccb or {}

function CCBReaderLoad(strFilePath,proxy,bSetOwner,strOwnerName)
    if nil == proxy then
        return
    end
    local strFmt = string.format("%p",proxy)
    print(strFmt)
    local ccbReader = proxy:createCCBReader()
    local node      = proxy:readCCBFromFile(strFilePath,ccbReader,bSetOwner)
    local owner     = ccbReader:getOwner()
    local rootName  = "" 
    --owner set in readCCBFromFile is proxy
    if nil ~= owner then
        print("come in owner")
        --Callbacks
        local ownerCallbackNames = tolua.cast(ccbReader:getOwnerCallbackNames(),"CCArray")
        local ownerCallbackNodes = tolua.cast(ccbReader:getOwnerCallbackNodes(),"CCArray")
        local i = 1
        for i = 1,ownerCallbackNames:count() do
            local callbackName = tolua.cast(ownerCallbackNames:objectAtIndex(i - 1),"CCString")
            local callbackNode = tolua.cast(ownerCallbackNodes:objectAtIndex(i - 1),"CCNode")
            if "" ~= strOwnerName and nil ~= ccb[strOwnerName] then
                proxy:setCallback(callbackNode,ccb[strOwnerName][callbackName:getCString()])
            end
        end

        --Variables
        local ownerOutletNames = tolua.cast(ccbReader:getOwnerOutletNames(),"CCArray")
        local ownerOutletNodes = tolua.cast(ccbReader:getOwnerOutletNodes(),"CCArray")
        print(ownerOutletNames:count())
        for i = 1, ownerOutletNames:count() do
            local outletName = tolua.cast(ownerOutletNames:objectAtIndex(i - 1),"CCString")
            local outletNode = tolua.cast(ownerOutletNodes:objectAtIndex(i - 1),"CCNode")
            print(outletName:getCString())
            if "" ~= strOwnerName and nil ~= ccb[strOwnerName] then
                ccb[strOwnerName][outletName:getCString()] = outletNode
            end
        end
    end

    local nodesWithAnimationManagers = tolua.cast(ccbReader:getNodesWithAnimationManagers(),"CCArray")
    local animationManagersForNodes  = tolua.cast(ccbReader:getAnimationManagersForNodes(),"CCArray")
    print("Test count")
    print(nodesWithAnimationManagers:count())
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
        print(documentControllerName)
        print(documentCallbackNames:count())
        for i = 1,documentCallbackNames:count() do
            local callbackName = tolua.cast(documentCallbackNames:objectAtIndex(i - 1),"CCString")
            local callbackNode = tolua.cast(documentCallbackNodes:objectAtIndex(i - 1),"CCNode")
            if "" ~= documentControllerName and nil ~= ccb[documentControllerName] then
                print(callbackName:getCString())
                proxy:setCallback(callbackNode,ccb[documentControllerName][callbackName:getCString()])
            end
        end

        --Variables
        local documentOutletNames = tolua.cast(animationManager:getDocumentOutletNames(),"CCArray")
        local documentOutletNodes = tolua.cast(animationManager:getDocumentOutletNodes(),"CCArray")
        print(documentOutletNames:count())
        for i = 1, documentOutletNames:count() do
            local outletName = tolua.cast(documentOutletNames:objectAtIndex(i - 1),"CCString")
            local outletNode = tolua.cast(documentOutletNodes:objectAtIndex(i - 1),"CCNode")
            print(outletName:getCString())
            if nil ~= ccb[documentControllerName] then
                ccb[documentControllerName][outletName:getCString()] = outletNode
            end 
        end
        --[[
        if (typeof(controller.onDidLoadFromCCB) == "function")
            controller.onDidLoadFromCCB();
        ]]--
        --Setup timeline callbacks
        local keyframeCallbacks = animationManager:getKeyframeCallbacks()
        print(keyframeCallbacks:count())
        for i = 1 , keyframeCallbacks:count() do
            local callbackCombine = tolua.cast(keyframeCallbacks:objectAtIndex(i - 1),"CCString"):getCString()
            local beignIndex,endIndex = string.find(callbackCombine,":")
            local callbackType    = tonumber(string.sub(callbackCombine,1,beignIndex - 1))
            local callbackName    = string.sub(callbackCombine,endIndex + 1, -1)
            --Document callback
            print(callbackName)
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
