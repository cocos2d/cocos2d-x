
--------------------------------
-- @module EventListenerTouchOneByOne
-- @extend EventListener
-- @parent_module cc

--------------------------------
--  Is swall touches or not.<br>
-- return True if needs to swall touches.
-- @function [parent=#EventListenerTouchOneByOne] isSwallowTouches 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
--  Whether or not to swall touches.<br>
-- param needSwallow True if needs to swall touches.
-- @function [parent=#EventListenerTouchOneByOne] setSwallowTouches 
-- @param self
-- @param #bool needSwallow
-- @return EventListenerTouchOneByOne#EventListenerTouchOneByOne self (return value: cc.EventListenerTouchOneByOne)
        
--------------------------------
-- / Overrides
-- @function [parent=#EventListenerTouchOneByOne] clone 
-- @param self
-- @return EventListenerTouchOneByOne#EventListenerTouchOneByOne ret (return value: cc.EventListenerTouchOneByOne)
        
--------------------------------
-- 
-- @function [parent=#EventListenerTouchOneByOne] checkAvailable 
-- @param self
-- @return bool#bool ret (return value: bool)
        
return nil
