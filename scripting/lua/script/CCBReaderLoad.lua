ccb = ccb or {}

function CCBuilderReaderLoad(strFilePath,proxy,owner)
    if nil == proxy then
        return
    end

    local ccbReader = proxy:createCCBReader()
    local node      = ccbReader:load(strFilePath)
    local rootName  = ""

    if nil ~= owner then
        --Callbacks
        local ownerCallbackNames = tolua.cast(ccbReader:getOwnerCallbackNames(),"CCArray")
        local ownerCallbackNodes = tolua.cast(ccbReader:getOwnerCallbackNodes(),"CCArray")
        local ownerCallbackControlEvents = tolua.cast(ccbReader:getOwnerCallbackControlEvents(),"CCArray")
        local i = 1
        for i = 1,ownerCallbackNames:count() do
            local callbackName =  tolua.cast(ownerCallbackNames:objectAtIndex(i - 1),"CCString")
            local callbackNode =  tolua.cast(ownerCallbackNodes:objectAtIndex(i - 1),"CCNode")

            if "function" == type(owner[callbackName:getCString()]) then
                local integerValue = tolua.cast(ownerCallbackControlEvents:objectAtIndex(i - 1),"CCInteger")
                if nil ~= integerValue then
                    proxy:setCallback(callbackNode, owner[callbackName:getCString()], integerValue:getValue())
                end
            else
                print("Warning: Cannot find owner's lua function:" .. ":" .. callbackName:getCString() .. " for ownerVar selector")
            end

        end

        --Variables
        local ownerOutletNames =  tolua.cast(ccbReader:getOwnerOutletNames(),"CCArray")
        local ownerOutletNodes =  tolua.cast(ccbReader:getOwnerOutletNodes(),"CCArray") 
        for i = 1, ownerOutletNames:count() do
            local outletName = tolua.cast(ownerOutletNames:objectAtIndex(i - 1),"CCString")
            local outletNode = tolua.cast(ownerOutletNodes:objectAtIndex(i - 1),"CCNode")
            owner[outletName:getCString()] = outletNode
        end
    end

    local nodesWithAnimationManagers = tolua.cast(ccbReader:getNodesWithAnimationManagers(),"CCArray")
    local animationManagersForNodes  = tolua.cast(ccbReader:getAnimationManagersForNodes(),"CCArray")

    for i = 1 , nodesWithAnimationManagers:count() do
        local innerNode = tolua.cast(nodesWithAnimationManagers:objectAtIndex(i - 1),"CCNode")
        local animationManager = tolua.cast(animationManagersForNodes:objectAtIndex(i - 1), "CCBAnimationManager")
        local documentControllerName = animationManager:getDocumentControllerName()
        if "" == documentControllerName then
            
        end
        if nil ~=  ccb[documentControllerName] then
            ccb[documentControllerName]["mAnimationManager"] = animationManager
        end
        
        --Callbacks
        local documentCallbackNames = tolua.cast(animationManager:getDocumentCallbackNames(),"CCArray")
        local documentCallbackNodes = tolua.cast(animationManager:getDocumentCallbackNodes(),"CCArray")
        local documentCallbackControlEvents = tolua.cast(animationManager:getDocumentCallbackControlEvents(),"CCArray")

        for i = 1,documentCallbackNames:count() do
            local callbackName = tolua.cast(documentCallbackNames:objectAtIndex(i - 1),"CCString")
            local callbackNode = tolua.cast(documentCallbackNodes:objectAtIndex(i - 1),"CCNode")
            if "" ~= documentControllerName and nil ~= ccb[documentControllerName] then
                local cbName = callbackName:getCString()
                if "function" == type(ccb[documentControllerName][cbName]) then
                    local integerValue = tolua.cast(documentCallbackControlEvents:objectAtIndex(i - 1),"CCInteger")
                    if nil ~= integerValue then
                        proxy:setCallback(callbackNode, ccb[documentControllerName][cbName], integerValue:getValue())
                    end
                else
                    print("Warning: Cannot found lua function [" .. documentControllerName .. ":" .. callbackName .. "] for docRoot selector")
                end
            end
        end

        --Variables
        local documentOutletNames =  tolua.cast(animationManager:getDocumentOutletNames(),"CCArray")
        local documentOutletNodes = tolua.cast(animationManager:getDocumentOutletNodes(),"CCArray")

        for i = 1, documentOutletNames:count() do
            local outletName = tolua.cast(documentOutletNames:objectAtIndex(i - 1),"CCString")
            local outletNode = tolua.cast(documentOutletNodes:objectAtIndex(i - 1),"CCNode")
            
            if nil ~= ccb[documentControllerName] then
                ccb[documentControllerName][outletName:getCString()] = tolua.cast(outletNode, proxy:getNodeTypeName(outletNode))
            end 
        end

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
                animationManager:setCallFuncForLuaCallbackNamed(callfunc, callbackCombine)
            elseif 2 == callbackType and nil ~= owner then --Owner callback
                local callfunc = CCCallFunc:create(owner[callbackName])
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

function CCBReaderLoad(strFilePath,proxy,bSetOwner,strOwnerName)
    print("CCBReaderLoad was deprecated, Please use CCBuilderReaderLoad(strFilePath,proxy,owner) instead.In the newest CocosBuilderTest,you can find out the usage of this new function")
    return
end
