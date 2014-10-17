
--------------------------------
-- @module TMXObjectGroup
-- @extend Ref
-- @parent_module cc

--------------------------------
--  Sets the offset position of child objects 
-- @function [parent=#TMXObjectGroup] setPositionOffset 
-- @param self
-- @param #vec2_table offset
        
--------------------------------
--  return the value for the specific property name 
-- @function [parent=#TMXObjectGroup] getProperty 
-- @param self
-- @param #string propertyName
-- @return Value#Value ret (return value: cc.Value)
        
--------------------------------
--  Gets the offset position of child objects 
-- @function [parent=#TMXObjectGroup] getPositionOffset 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
--  return the dictionary for the specific object name.<br>
-- It will return the 1st object found on the array for the given name.
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
-- 
-- @function [parent=#TMXObjectGroup] setGroupName 
-- @param self
-- @param #string groupName
        
--------------------------------
-- @overload self         
-- @overload self         
-- @function [parent=#TMXObjectGroup] getProperties
-- @param self
-- @return map_table#map_table ret (return value: map_table)

--------------------------------
-- 
-- @function [parent=#TMXObjectGroup] getGroupName 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
--  Sets the list of properties 
-- @function [parent=#TMXObjectGroup] setProperties 
-- @param self
-- @param #map_table properties
        
--------------------------------
--  Sets the array of the objects 
-- @function [parent=#TMXObjectGroup] setObjects 
-- @param self
-- @param #array_table objects
        
--------------------------------
-- js ctor
-- @function [parent=#TMXObjectGroup] TMXObjectGroup 
-- @param self
        
return nil
