
--------------------------------
-- @module AsyncTaskPool
-- @parent_module cc

--------------------------------
-- @overload self, int, function         
-- @overload self, int, function, void, function         
-- @function [parent=#AsyncTaskPool] enqueue
-- @param self
-- @param #int type
-- @param #function callback
-- @param #void callbackParam
-- @param #function task
-- @return AsyncTaskPool#AsyncTaskPool self (return value: cc.AsyncTaskPool)

--------------------------------
-- Stop tasks.<br>
-- param type Task type you want to stop.
-- @function [parent=#AsyncTaskPool] stopTasks 
-- @param self
-- @param #int type
-- @return AsyncTaskPool#AsyncTaskPool self (return value: cc.AsyncTaskPool)
        
--------------------------------
-- Destroys the async task pool.
-- @function [parent=#AsyncTaskPool] destroyInstance 
-- @param self
-- @return AsyncTaskPool#AsyncTaskPool self (return value: cc.AsyncTaskPool)
        
--------------------------------
-- Returns the shared instance of the async task pool.
-- @function [parent=#AsyncTaskPool] getInstance 
-- @param self
-- @return AsyncTaskPool#AsyncTaskPool ret (return value: cc.AsyncTaskPool)
        
--------------------------------
-- 
-- @function [parent=#AsyncTaskPool] AsyncTaskPool 
-- @param self
-- @return AsyncTaskPool#AsyncTaskPool self (return value: cc.AsyncTaskPool)
        
return nil
