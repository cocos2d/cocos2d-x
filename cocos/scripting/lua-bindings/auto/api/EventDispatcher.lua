
--------------------------------
-- @module EventDispatcher
-- @extend Ref
-- @parent_module cc

--------------------------------
--  Pauses all listeners which are associated the specified target. 
-- @function [parent=#EventDispatcher] pauseEventListenersForTarget 
-- @param self
-- @param #cc.Node target
-- @param #bool recursive
        
--------------------------------
--  Adds a event listener for a specified event with the priority of scene graph.<br>
-- param listener The listener of a specified event.<br>
-- param node The priority of the listener is based on the draw order of this node.<br>
-- note  The priority of scene graph will be fixed value 0. So the order of listener item<br>
-- in the vector will be ' <0, scene graph (0 priority), >0'.
-- @function [parent=#EventDispatcher] addEventListenerWithSceneGraphPriority 
-- @param self
-- @param #cc.EventListener listener
-- @param #cc.Node node
        
--------------------------------
--  Whether to enable dispatching events 
-- @function [parent=#EventDispatcher] setEnabled 
-- @param self
-- @param #bool isEnabled
        
--------------------------------
--  Adds a event listener for a specified event with the fixed priority.<br>
-- param listener The listener of a specified event.<br>
-- param fixedPriority The fixed priority of the listener.<br>
-- note A lower priority will be called before the ones that have a higher value.<br>
-- 0 priority is forbidden for fixed priority since it's used for scene graph based priority.
-- @function [parent=#EventDispatcher] addEventListenerWithFixedPriority 
-- @param self
-- @param #cc.EventListener listener
-- @param #int fixedPriority
        
--------------------------------
--  Remove a listener<br>
-- param listener The specified event listener which needs to be removed.
-- @function [parent=#EventDispatcher] removeEventListener 
-- @param self
-- @param #cc.EventListener listener
        
--------------------------------
--  Resumes all listeners which are associated the specified target. 
-- @function [parent=#EventDispatcher] resumeEventListenersForTarget 
-- @param self
-- @param #cc.Node target
-- @param #bool recursive
        
--------------------------------
--  Removes all listeners which are associated with the specified target. 
-- @function [parent=#EventDispatcher] removeEventListenersForTarget 
-- @param self
-- @param #cc.Node target
-- @param #bool recursive
        
--------------------------------
--  Sets listener's priority with fixed value. 
-- @function [parent=#EventDispatcher] setPriority 
-- @param self
-- @param #cc.EventListener listener
-- @param #int fixedPriority
        
--------------------------------
--  Adds a Custom event listener.<br>
-- It will use a fixed priority of 1.<br>
-- return the generated event. Needed in order to remove the event from the dispather
-- @function [parent=#EventDispatcher] addCustomEventListener 
-- @param self
-- @param #string eventName
-- @param #function callback
-- @return EventListenerCustom#EventListenerCustom ret (return value: cc.EventListenerCustom)
        
--------------------------------
--  Dispatches the event<br>
-- Also removes all EventListeners marked for deletion from the<br>
-- event dispatcher list.
-- @function [parent=#EventDispatcher] dispatchEvent 
-- @param self
-- @param #cc.Event event
        
--------------------------------
--  Removes all listeners 
-- @function [parent=#EventDispatcher] removeAllEventListeners 
-- @param self
        
--------------------------------
--  Removes all custom listeners with the same event name 
-- @function [parent=#EventDispatcher] removeCustomEventListeners 
-- @param self
-- @param #string customEventName
        
--------------------------------
--  Checks whether dispatching events is enabled 
-- @function [parent=#EventDispatcher] isEnabled 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
--  Removes all listeners with the same event listener type 
-- @function [parent=#EventDispatcher] removeEventListenersForType 
-- @param self
-- @param #int listenerType
        
--------------------------------
--  Constructor of EventDispatcher 
-- @function [parent=#EventDispatcher] EventDispatcher 
-- @param self
        
return nil
