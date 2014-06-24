
local c = cc
local ui = {}

function makeUIControl_(control)
    cc(control)
    control:addComponent("components.ui.LayoutProtocol"):exportMethods()
    control:addComponent("components.behavior.EventProtocol"):exportMethods()

    control:setCascadeOpacityEnabled(true)
    control:setCascadeColorEnabled(true)
    control:addNodeEventListener(c.NODE_EVENT, function(event)
        if event.name == "cleanup" then
            control:removeAllEventListeners()
        end
    end)
end

ui.TEXT_ALIGN_LEFT    = kCCTextAlignmentLeft
ui.TEXT_ALIGN_CENTER  = kCCTextAlignmentCenter
ui.TEXT_ALIGN_RIGHT   = kCCTextAlignmentRight
ui.TEXT_VALIGN_TOP    = kCCVerticalTextAlignmentTop
ui.TEXT_VALIGN_CENTER = kCCVerticalTextAlignmentCenter
ui.TEXT_VALIGN_BOTTOM = kCCVerticalTextAlignmentBottom

ui.UIGroup               = import(".UIGroup")
ui.UIImage               = import(".UIImage")
ui.UIPushButton          = import(".UIPushButton")
ui.UICheckBoxButton      = import(".UICheckBoxButton")
ui.UICheckBoxButtonGroup = import(".UICheckBoxButtonGroup")
ui.UILabel               = import(".UILabel")
ui.UISlider              = import(".UISlider")
ui.UIBoxLayout           = import(".UIBoxLayout")

return ui
