if nil == cc.XMLHttpRequest then
    return
end
-- This is the DeprecatedNetworkClass

DeprecatedNetworkClass = {} or DeprecatedNetworkClass

--tip
local function deprecatedTip(old_name,new_name)
    print("\n********** \n"..old_name.." was deprecated please use ".. new_name .. " instead.\n**********")
end

--WebSocket class will be Deprecated,begin
function DeprecatedNetworkClass.WebSocket()
    deprecatedTip("WebSocket","cc.WebSocket")
    return cc.WebSocket
end
_G["WebSocket"] = DeprecatedNetworkClass.WebSocket()
--WebSocket class will be Deprecated,end
