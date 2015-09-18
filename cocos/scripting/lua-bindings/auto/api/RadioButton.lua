
--------------------------------
-- @module RadioButton
-- @extend AbstractCheckButton
-- @parent_module ccui

--------------------------------
-- Add a callback function which would be called when radio button is selected or unselected.<br>
-- param callback A std::function with type @see `ccRadioButtonCallback`
-- @function [parent=#RadioButton] addEventListener 
-- @param self
-- @param #function callback
-- @return RadioButton#RadioButton self (return value: ccui.RadioButton)
        
--------------------------------
-- @overload self, string, string, string, string, string, int         
-- @overload self         
-- @overload self, string, string, int         
-- @function [parent=#RadioButton] create
-- @param self
-- @param #string backGround
-- @param #string backGroundSelected
-- @param #string cross
-- @param #string backGroundDisabled
-- @param #string frontCrossDisabled
-- @param #int texType
-- @return RadioButton#RadioButton ret (return value: ccui.RadioButton)

--------------------------------
-- 
-- @function [parent=#RadioButton] createInstance 
-- @param self
-- @return Ref#Ref ret (return value: cc.Ref)
        
--------------------------------
-- 
-- @function [parent=#RadioButton] getDescription 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- Default constructor.<br>
-- lua new
-- @function [parent=#RadioButton] RadioButton 
-- @param self
-- @return RadioButton#RadioButton self (return value: ccui.RadioButton)
        
return nil
