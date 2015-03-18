
--------------------------------
-- @module LayerMultiplex
-- @extend Layer
-- @parent_module cc

--------------------------------
--  initializes a MultiplexLayer with an array of layers<br>
-- since v2.1
-- @function [parent=#LayerMultiplex] initWithArray 
-- @param self
-- @param #array_table arrayOfLayers
-- @return bool#bool ret (return value: bool)
        
--------------------------------
--  release the current layer and switches to another layer indexed by n.<br>
-- The current (old) layer will be removed from it's parent with 'cleanup=true'.
-- @function [parent=#LayerMultiplex] switchToAndReleaseMe 
-- @param self
-- @param #int n
-- @return LayerMultiplex#LayerMultiplex self (return value: cc.LayerMultiplex)
        
--------------------------------
-- 
-- @function [parent=#LayerMultiplex] addLayer 
-- @param self
-- @param #cc.Layer layer
-- @return LayerMultiplex#LayerMultiplex self (return value: cc.LayerMultiplex)
        
--------------------------------
--  switches to a certain layer indexed by n.<br>
-- The current (old) layer will be removed from it's parent with 'cleanup=true'.
-- @function [parent=#LayerMultiplex] switchTo 
-- @param self
-- @param #int n
-- @return LayerMultiplex#LayerMultiplex self (return value: cc.LayerMultiplex)
        
--------------------------------
-- 
-- @function [parent=#LayerMultiplex] init 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#LayerMultiplex] getDescription 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- js ctor
-- @function [parent=#LayerMultiplex] LayerMultiplex 
-- @param self
-- @return LayerMultiplex#LayerMultiplex self (return value: cc.LayerMultiplex)
        
return nil
