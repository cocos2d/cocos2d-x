
--------------------------------
-- @module Scheduler
-- @extend Ref
-- @parent_module cc

--------------------------------
--  Modifies the time of all scheduled callbacks.<br>
-- You can use this property to create a 'slow motion' or 'fast forward' effect.<br>
-- Default is 1.0. To create a 'slow motion' effect, use values below 1.0.<br>
-- To create a 'fast forward' effect, use values higher than 1.0.<br>
-- since v0.8<br>
-- warning It will affect EVERY scheduled selector / action.
-- @function [parent=#Scheduler] setTimeScale 
-- @param self
-- @param #float timeScale
        
--------------------------------
-- 
-- @function [parent=#Scheduler] getTimeScale 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- js ctor
-- @function [parent=#Scheduler] Scheduler 
-- @param self
        
return nil
