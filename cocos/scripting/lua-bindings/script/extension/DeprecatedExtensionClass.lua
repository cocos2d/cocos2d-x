-- This is the DeprecatedExtensionClass

DeprecatedExtensionClass = {} or DeprecatedExtensionClass

--tip
local function deprecatedTip(old_name,new_name)
    print("\n********** \n"..old_name.." was deprecated please use ".. new_name .. " instead.\n**********")
end

--CCControl class will be Deprecated,begin
function DeprecatedExtensionClass.CCControl()
    deprecatedTip("CCControl","cc.Control")
    return cc.Control
end
_G["CCControl"] = DeprecatedExtensionClass.CCControl()
--CCControl class will be Deprecated,end

--CCEditBox class will be Deprecated,begin
function DeprecatedExtensionClass.CCEditBox()
    deprecatedTip("CCEditBox","ccui.EditBox")
    return ccui.EditBox
end
_G["CCEditBox"] = DeprecatedExtensionClass.CCEditBox()

function DeprecatedExtensionClass.CCUIEditBox()
    deprecatedTip("cc.EditBox","ccui.EditBox")
    return ccui.EditBox
end
_G["cc"]["EditBox"] = DeprecatedExtensionClass.CCUIEditBox()

--CCEditBox class will be Deprecated,end

--CCScrollView class will be Deprecated,begin
function DeprecatedExtensionClass.CCScrollView()
    deprecatedTip("CCScrollView","cc.ScrollView")
    return cc.ScrollView
end
_G["CCScrollView"] = DeprecatedExtensionClass.CCScrollView()
--CCScrollView class will be Deprecated,end

--CCTableView class will be Deprecated,begin
function DeprecatedExtensionClass.CCTableView()
    deprecatedTip("CCTableView","cc.TableView")
    return cc.TableView
end
_G["CCTableView"] = DeprecatedExtensionClass.CCTableView()
--CCTableView class will be Deprecated,end

--CCControlPotentiometer class will be Deprecated,begin
function DeprecatedExtensionClass.CCControlPotentiometer()
    deprecatedTip("CCControlPotentiometer","cc.ControlPotentiometer")
    return cc.ControlPotentiometer
end
_G["CCControlPotentiometer"] = DeprecatedExtensionClass.CCControlPotentiometer()
--CCControlPotentiometer class will be Deprecated,end

--CCControlStepper class will be Deprecated,begin
function DeprecatedExtensionClass.CCControlStepper()
    deprecatedTip("CCControlStepper","cc.ControlStepper")
    return cc.ControlStepper
end
_G["CCControlStepper"] = DeprecatedExtensionClass.CCControlStepper()
--CCControlStepper class will be Deprecated,end

--CCControlHuePicker class will be Deprecated,begin
function DeprecatedExtensionClass.CCControlHuePicker()
    deprecatedTip("CCControlHuePicker","cc.ControlHuePicker")
    return cc.ControlHuePicker
end
_G["CCControlHuePicker"] = DeprecatedExtensionClass.CCControlHuePicker()
--CCControlHuePicker class will be Deprecated,end

--CCControlSlider class will be Deprecated,begin
function DeprecatedExtensionClass.CCControlSlider()
    deprecatedTip("CCControlSlider","cc.ControlSlider")
    return cc.ControlSlider
end
_G["CCControlSlider"] = DeprecatedExtensionClass.CCControlSlider()
--CCControlSlider class will be Deprecated,end

--CCControlSaturationBrightnessPicker class will be Deprecated,begin
function DeprecatedExtensionClass.CCControlSaturationBrightnessPicker()
    deprecatedTip("CCControlSaturationBrightnessPicker","cc.ControlSaturationBrightnessPicker")
    return cc.ControlSaturationBrightnessPicker
end
_G["CCControlSaturationBrightnessPicker"] = DeprecatedExtensionClass.CCControlSaturationBrightnessPicker()
--CCControlSaturationBrightnessPicker class will be Deprecated,end

--CCControlSwitch class will be Deprecated,begin
function DeprecatedExtensionClass.CCControlSwitch()
    deprecatedTip("CCControlSwitch","cc.ControlSwitch")
    return cc.ControlSwitch
end
_G["CCControlSwitch"] = DeprecatedExtensionClass.CCControlSwitch()
--CCControlSwitch class will be Deprecated,end

--CCControlButton class will be Deprecated,begin
function DeprecatedExtensionClass.CCControlButton()
    deprecatedTip("CCControlButton","cc.ControlButton")
    return cc.ControlButton
end
_G["CCControlButton"] = DeprecatedExtensionClass.CCControlButton()
--CCControlButton class will be Deprecated,end

--CCScale9Sprite class will be Deprecated,begin
function DeprecatedExtensionClass.CCScale9Sprite()
    deprecatedTip("CCScale9Sprite","ccui.Scale9Sprite")
    return ccui.Scale9Sprite
end
_G["CCScale9Sprite"] = DeprecatedExtensionClass.CCScale9Sprite()

function DeprecatedExtensionClass.UIScale9Sprite()
    deprecatedTip("cc.Scale9Sprite","ccui.Scale9Sprite")
    return ccui.Scale9Sprite
end
_G["cc"]["Scale9Sprite"] = DeprecatedExtensionClass.UIScale9Sprite()
--CCScale9Sprite class will be Deprecated,end

--CCControlColourPicker class will be Deprecated,begin
function DeprecatedExtensionClass.CCControlColourPicker()
    deprecatedTip("CCControlColourPicker","cc.ControlColourPicker")
    return cc.ControlColourPicker
end
_G["CCControlColourPicker"] = DeprecatedExtensionClass.CCControlColourPicker()
--CCControlColourPicker class will be Deprecated,end

