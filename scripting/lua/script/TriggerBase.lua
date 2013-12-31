require "ObjectFactory"

function sendTriggerEvent(event)
    local triggerObjArr = TriggerMng.getInstance():get(event)
    
    if nil == triggerObjArr then
        return
    end

    for i = 1, table.getn(triggerObjArr) do
        local triObj = triggerObjArr[i]
        if nil ~= triObj and triObj.detect then
            triObj:done()
        end
    end
end

function registerTriggerClass(className, createFunc)
    TInfo.new(className,createFunc)
end