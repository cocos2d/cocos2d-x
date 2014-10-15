
--------------------------------
-- @module ActionTimelineCache
-- @parent_module ccs

--------------------------------
--  Clone a action with the specified name from the container. 
-- @function [parent=#ActionTimelineCache] createActionFromJson 
-- @param self
-- @param #string fileName
-- @return ActionTimeline#ActionTimeline ret (return value: ccs.ActionTimeline)
        
--------------------------------
-- 
-- @function [parent=#ActionTimelineCache] createActionFromProtocolBuffers 
-- @param self
-- @param #string fileName
-- @return ActionTimeline#ActionTimeline ret (return value: ccs.ActionTimeline)
        
--------------------------------
-- 
-- @function [parent=#ActionTimelineCache] createActionFromXML 
-- @param self
-- @param #string fileName
-- @return ActionTimeline#ActionTimeline ret (return value: ccs.ActionTimeline)
        
--------------------------------
-- 
-- @function [parent=#ActionTimelineCache] loadAnimationActionWithFileFromProtocolBuffers 
-- @param self
-- @param #string fileName
-- @return ActionTimeline#ActionTimeline ret (return value: ccs.ActionTimeline)
        
--------------------------------
-- 
-- @function [parent=#ActionTimelineCache] loadAnimationActionWithFileFromXML 
-- @param self
-- @param #string fileName
-- @return ActionTimeline#ActionTimeline ret (return value: ccs.ActionTimeline)
        
--------------------------------
-- 
-- @function [parent=#ActionTimelineCache] purge 
-- @param self
        
--------------------------------
-- 
-- @function [parent=#ActionTimelineCache] init 
-- @param self
        
--------------------------------
-- 
-- @function [parent=#ActionTimelineCache] loadAnimationActionWithFile 
-- @param self
-- @param #string fileName
-- @return ActionTimeline#ActionTimeline ret (return value: ccs.ActionTimeline)
        
--------------------------------
-- 
-- @function [parent=#ActionTimelineCache] loadAnimationActionWithContent 
-- @param self
-- @param #string fileName
-- @param #string content
-- @return ActionTimeline#ActionTimeline ret (return value: ccs.ActionTimeline)
        
--------------------------------
--  Remove action with filename, and also remove other resource relate with this file 
-- @function [parent=#ActionTimelineCache] removeAction 
-- @param self
-- @param #string fileName
        
--------------------------------
--  Destroys the singleton 
-- @function [parent=#ActionTimelineCache] destroyInstance 
-- @param self
        
--------------------------------
-- 
-- @function [parent=#ActionTimelineCache] createAction 
-- @param self
-- @param #string fileName
-- @return ActionTimeline#ActionTimeline ret (return value: ccs.ActionTimeline)
        
return nil
