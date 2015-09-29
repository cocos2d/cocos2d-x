
--------------------------------
-- @module CheckBox
-- @extend AbstractCheckButton
-- @parent_module ccui

--------------------------------
-- Add a callback function which would be called when checkbox is selected or unselected.<br>
-- param callback A std::function with type @see `ccCheckBoxCallback`
-- @function [parent=#CheckBox] addEventListener 
-- @param self
-- @param #function callback
-- @return CheckBox#CheckBox self (return value: ccui.CheckBox)
        
--------------------------------
-- @overload self, string, string, string, string, string, int         
-- @overload self         
-- @overload self, string, string, int         
-- @function [parent=#CheckBox] create
-- @param self
-- @param #string backGround
-- @param #string backGroundSelected
-- @param #string cross
-- @param #string backGroundDisabled
-- @param #string frontCrossDisabled
-- @param #int texType
-- @return CheckBox#CheckBox ret (return value: ccui.CheckBox)

--------------------------------
-- 
-- @function [parent=#CheckBox] createInstance 
-- @param self
-- @return Ref#Ref ret (return value: cc.Ref)
        
--------------------------------
-- 
-- @function [parent=#CheckBox] getDescription 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- Default constructor.<br>
-- lua new
-- @function [parent=#CheckBox] CheckBox 
-- @param self
-- @return CheckBox#CheckBox self (return value: ccui.CheckBox)
        
return nil
