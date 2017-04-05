
--------------------------------
-- @module TMXObjectGroup
-- @extend Ref
-- @parent_module cc

--------------------------------
--  Sets the offset position of child objects. <br>
-- param offset The offset position of child objects.
-- @function [parent=#TMXObjectGroup] setPositionOffset 
-- @param self
-- @param #vec2_table offset
-- @return TMXObjectGroup#TMXObjectGroup self (return value: cc.TMXObjectGroup)
        
--------------------------------
--  Return the value for the specific property name. <br>
-- param propertyName The specific property name.<br>
-- return Return the value for the specific property name.<br>
-- js NA
-- @function [parent=#TMXObjectGroup] getProperty 
-- @param self
-- @param #string propertyName
-- @return Value#Value ret (return value: cc.Value)
        
--------------------------------
--  Gets the offset position of child objects. <br>
-- return The offset position of child objects.
-- @function [parent=#TMXObjectGroup] getPositionOffset 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
--  Return the dictionary for the specific object name.<br>
-- It will return the 1st object found on the array for the given name.<br>
-- return Return the dictionary for the specific object name.
-- @function [parent=#TMXObjectGroup] getObject 
-- @param self
-- @param #string objectName
-- @return map_table#map_table ret (return value: map_table)
        
--------------------------------
-- @overload self         
-- @overload self         
-- @function [parent=#TMXObjectGroup] getObjects
-- @param self
-- @return array_table#array_table ret (return value: array_table)

--------------------------------
--  Set the group name. <br>
-- param groupName A string,it is used to set the group name.
-- @function [parent=#TMXObjectGroup] setGroupName 
-- @param self
-- @param #string groupName
-- @return TMXObjectGroup#TMXObjectGroup self (return value: cc.TMXObjectGroup)
        
--------------------------------
-- @overload self         
-- @overload self         
-- @function [parent=#TMXObjectGroup] getProperties
-- @param self
-- @return map_table#map_table ret (return value: map_table)

--------------------------------
--  Get the group name. <br>
-- return The group name.
-- @function [parent=#TMXObjectGroup] getGroupName 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
--  Sets the list of properties.<br>
-- param properties The list of properties.
-- @function [parent=#TMXObjectGroup] setProperties 
-- @param self
-- @param #map_table properties
-- @return TMXObjectGroup#TMXObjectGroup self (return value: cc.TMXObjectGroup)
        
--------------------------------
--  Sets the array of the objects.<br>
-- param objects The array of the objects.
-- @function [parent=#TMXObjectGroup] setObjects 
-- @param self
-- @param #array_table objects
-- @return TMXObjectGroup#TMXObjectGroup self (return value: cc.TMXObjectGroup)
        
--------------------------------
-- js ctor
-- @function [parent=#TMXObjectGroup] TMXObjectGroup 
-- @param self
-- @return TMXObjectGroup#TMXObjectGroup self (return value: cc.TMXObjectGroup)
        
return nil
