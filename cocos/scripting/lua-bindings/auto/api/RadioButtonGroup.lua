
--------------------------------
-- @module RadioButtonGroup
-- @extend Widget
-- @parent_module ccui

--------------------------------
-- Remove a radio button from this group.<br>
-- param radio button instance
-- @function [parent=#RadioButtonGroup] removeRadioButton 
-- @param self
-- @param #ccui.RadioButton radioButton
-- @return RadioButtonGroup#RadioButtonGroup self (return value: ccui.RadioButtonGroup)
        
--------------------------------
-- Query whether no-selection is allowed or not.<br>
-- param true means no-selection is allowed, false means no-selection is not allowed.
-- @function [parent=#RadioButtonGroup] isAllowedNoSelection 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- Get the index of selected radio button.<br>
-- return the selected button's index. Returns -1 if no button is selected.
-- @function [parent=#RadioButtonGroup] getSelectedButtonIndex 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- Set a flag for allowing no-selection feature.<br>
-- If it is allowed, no radio button can be selected.<br>
-- If it is not allowed, one radio button must be selected all time except it is empty.<br>
-- Default is not allowed.<br>
-- param true means allowing no-selection, false means disallowing no-selection.
-- @function [parent=#RadioButtonGroup] setAllowedNoSelection 
-- @param self
-- @param #bool allowedNoSelection
-- @return RadioButtonGroup#RadioButtonGroup self (return value: ccui.RadioButtonGroup)
        
--------------------------------
-- @overload self, ccui.RadioButton         
-- @overload self, int         
-- @function [parent=#RadioButtonGroup] setSelectedButtonWithoutEvent
-- @param self
-- @param #int index
-- @return RadioButtonGroup#RadioButtonGroup self (return value: ccui.RadioButtonGroup)

--------------------------------
-- Add a callback function which would be called when radio button is selected or unselected.<br>
-- param callback A std::function with type @see `ccRadioButtonGroupCallback`
-- @function [parent=#RadioButtonGroup] addEventListener 
-- @param self
-- @param #function callback
-- @return RadioButtonGroup#RadioButtonGroup self (return value: ccui.RadioButtonGroup)
        
--------------------------------
-- Remove all radio button from this group.
-- @function [parent=#RadioButtonGroup] removeAllRadioButtons 
-- @param self
-- @return RadioButtonGroup#RadioButtonGroup self (return value: ccui.RadioButtonGroup)
        
--------------------------------
-- Get a radio button in this group by index.<br>
-- param index of the radio button<br>
-- return radio button instance. Returns nullptr if out of index.
-- @function [parent=#RadioButtonGroup] getRadioButtonByIndex 
-- @param self
-- @param #int index
-- @return RadioButton#RadioButton ret (return value: ccui.RadioButton)
        
--------------------------------
-- Get the number of radio buttons in this group.<br>
-- return the number of radio buttons in this group
-- @function [parent=#RadioButtonGroup] getNumberOfRadioButtons 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- Add a radio button into this group.<br>
-- param radio button instance
-- @function [parent=#RadioButtonGroup] addRadioButton 
-- @param self
-- @param #ccui.RadioButton radioButton
-- @return RadioButtonGroup#RadioButtonGroup self (return value: ccui.RadioButtonGroup)
        
--------------------------------
-- @overload self, ccui.RadioButton         
-- @overload self, int         
-- @function [parent=#RadioButtonGroup] setSelectedButton
-- @param self
-- @param #int index
-- @return RadioButtonGroup#RadioButtonGroup self (return value: ccui.RadioButtonGroup)

--------------------------------
-- Create and return a empty RadioButtonGroup instance pointer.
-- @function [parent=#RadioButtonGroup] create 
-- @param self
-- @return RadioButtonGroup#RadioButtonGroup ret (return value: ccui.RadioButtonGroup)
        
--------------------------------
-- 
-- @function [parent=#RadioButtonGroup] getDescription 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- Default constructor.<br>
-- lua new
-- @function [parent=#RadioButtonGroup] RadioButtonGroup 
-- @param self
-- @return RadioButtonGroup#RadioButtonGroup self (return value: ccui.RadioButtonGroup)
        
return nil
