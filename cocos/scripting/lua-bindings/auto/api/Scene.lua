
--------------------------------
-- @module Scene
-- @extend Node
-- @parent_module cc

--------------------------------
--  render the scene 
-- @function [parent=#Scene] render 
-- @param self
-- @param #cc.Renderer renderer
-- @return Scene#Scene self (return value: cc.Scene)
        
--------------------------------
-- 
-- @function [parent=#Scene] getDefaultCamera 
-- @param self
-- @return Camera#Camera ret (return value: cc.Camera)
        
--------------------------------
--  creates a new Scene object with a predefined Size 
-- @function [parent=#Scene] createWithSize 
-- @param self
-- @param #size_table size
-- @return Scene#Scene ret (return value: cc.Scene)
        
--------------------------------
--  creates a new Scene object 
-- @function [parent=#Scene] create 
-- @param self
-- @return Scene#Scene ret (return value: cc.Scene)
        
--------------------------------
-- @overload self, cc.Node, int, string         
-- @overload self, cc.Node, int, int         
-- @function [parent=#Scene] addChild
-- @param self
-- @param #cc.Node child
-- @param #int zOrder
-- @param #int tag
-- @return Scene#Scene self (return value: cc.Scene)

--------------------------------
-- 
-- @function [parent=#Scene] getDescription 
-- @param self
-- @return string#string ret (return value: string)
        
return nil
