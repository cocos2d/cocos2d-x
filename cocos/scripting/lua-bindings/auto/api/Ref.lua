
--------------------------------
-- @module Ref
-- @parent_module cc

--------------------------------
-- Releases the ownership immediately.<br>
-- This decrements the Ref's reference count.<br>
-- If the reference count reaches 0 after the descrement, this Ref is<br>
-- destructed.<br>
-- see retain, autorelease<br>
-- js NA
-- @function [parent=#Ref] release 
-- @param self
        
--------------------------------
-- Retains the ownership.<br>
-- This increases the Ref's reference count.<br>
-- see release, autorelease<br>
-- js NA
-- @function [parent=#Ref] retain 
-- @param self
        
--------------------------------
-- Returns the Ref's current reference count.<br>
-- returns The Ref's reference count.<br>
-- js NA
-- @function [parent=#Ref] getReferenceCount 
-- @param self
-- @return unsigned int#unsigned int ret (return value: unsigned int)
        
return nil
