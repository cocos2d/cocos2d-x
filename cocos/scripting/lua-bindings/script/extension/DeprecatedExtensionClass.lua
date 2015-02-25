if nil == cc.Control then
    return
end

-- This is the DeprecatedExtensionClass
DeprecatedExtensionClass = {} or DeprecatedExtensionClass

--tip
local function deprecatedTip(old_name,new_name)
    print("\n********** \n"..old_name.." was deprecated please use ".. new_name .. " instead.\n**********")
end


if nil == ccui then
    return
end

--cc.EditBox class will be Deprecated,begin
function DeprecatedExtensionClass.CCUIEditBox()
    deprecatedTip("cc.EditBox","ccui.EditBox")
    return ccui.EditBox
end
_G["cc"]["EditBox"] = DeprecatedExtensionClass.CCUIEditBox()

--cc.EditBox class will be Deprecated,end

--cc.Scale9Sprite class will be Deprecated,begin
function DeprecatedExtensionClass.UIScale9Sprite()
    deprecatedTip("cc.Scale9Sprite","ccui.Scale9Sprite")
    return ccui.Scale9Sprite
end
_G["cc"]["Scale9Sprite"] = DeprecatedExtensionClass.UIScale9Sprite()
--cc.Scale9Sprite class will be Deprecated,end

