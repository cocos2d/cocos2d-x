
--------------------------------
-- @module Technique
-- @extend RenderState
-- @parent_module cc

--------------------------------
--  Returns the number of Passes in the Technique 
-- @function [parent=#Technique] getPassCount 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
--  Returns a new clone of the Technique 
-- @function [parent=#Technique] clone 
-- @param self
-- @return Technique#Technique ret (return value: cc.Technique)
        
--------------------------------
--  Adds a new pass to the Technique.<br>
-- Order matters. First added, first rendered
-- @function [parent=#Technique] addPass 
-- @param self
-- @param #cc.Pass pass
-- @return Technique#Technique self (return value: cc.Technique)
        
--------------------------------
--  Returns the list of passes 
-- @function [parent=#Technique] getPasses 
-- @param self
-- @return array_table#array_table ret (return value: array_table)
        
--------------------------------
--  Returns the name of the Technique 
-- @function [parent=#Technique] getName 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
--  Returns the Pass at given index 
-- @function [parent=#Technique] getPassByIndex 
-- @param self
-- @param #int index
-- @return Pass#Pass ret (return value: cc.Pass)
        
--------------------------------
-- 
-- @function [parent=#Technique] create 
-- @param self
-- @param #cc.Material parent
-- @return Technique#Technique ret (return value: cc.Technique)
        
--------------------------------
--  Creates a new Technique with a GLProgramState.<br>
-- Method added to support legacy code
-- @function [parent=#Technique] createWithGLProgramState 
-- @param self
-- @param #cc.Material parent
-- @param #cc.GLProgramState state
-- @return Technique#Technique ret (return value: cc.Technique)
        
return nil
