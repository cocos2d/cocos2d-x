
--------------------------------
-- @module LayerMultiplex
-- @extend Layer
-- @parent_module cc

--------------------------------
--  release the current layer and switches to another layer indexed by n.<br>
-- The current (old) layer will be removed from it's parent with 'cleanup=true'.<br>
-- param n The layer indexed by n will display.
-- @function [parent=#LayerMultiplex] switchToAndReleaseMe 
-- @param self
-- @param #int n
-- @return LayerMultiplex#LayerMultiplex self (return value: cc.LayerMultiplex)
        
--------------------------------
--  Add a certain layer to LayerMultiplex.<br>
-- param layer A layer need to be added to the LayerMultiplex.
-- @function [parent=#LayerMultiplex] addLayer 
-- @param self
-- @param #cc.Layer layer
-- @return LayerMultiplex#LayerMultiplex self (return value: cc.LayerMultiplex)
        
--------------------------------
--  Switches to a certain layer indexed by n.<br>
-- The current (old) layer will be removed from it's parent with 'cleanup=true'.<br>
-- param n The layer indexed by n will display.
-- @function [parent=#LayerMultiplex] switchTo 
-- @param self
-- @param #int n
-- @return LayerMultiplex#LayerMultiplex self (return value: cc.LayerMultiplex)
        
--------------------------------
-- 
-- @function [parent=#LayerMultiplex] getDescription 
-- @param self
-- @return string#string ret (return value: string)
        
return nil
