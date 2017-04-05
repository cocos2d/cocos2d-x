
--------------------------------
-- @module EventDispatcher
-- @extend Ref
-- @parent_module cc

--------------------------------
--  Pauses all listeners which are associated the specified target.<br>
-- param target A given target node.<br>
-- param recursive True if pause recursively, the default value is false.
-- @function [parent=#EventDispatcher] pauseEventListenersForTarget 
-- @param self
-- @param #cc.Node target
-- @param #bool recursive
-- @return EventDispatcher#EventDispatcher self (return value: cc.EventDispatcher)
        
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
-- @return EventDispatcher#EventDispatcher self (return value: cc.EventDispatcher)
        
--------------------------------
--  Whether to enable dispatching events.<br>
-- param isEnabled  True if enable dispatching events.
-- @function [parent=#EventDispatcher] setEnabled 
-- @param self
-- @param #bool isEnabled
-- @return EventDispatcher#EventDispatcher self (return value: cc.EventDispatcher)
        
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
-- @return EventDispatcher#EventDispatcher self (return value: cc.EventDispatcher)
        
--------------------------------
--  Remove a listener.<br>
-- param listener The specified event listener which needs to be removed.
-- @function [parent=#EventDispatcher] removeEventListener 
-- @param self
-- @param #cc.EventListener listener
-- @return EventDispatcher#EventDispatcher self (return value: cc.EventDispatcher)
        
--------------------------------
--  Dispatches a Custom Event with a event name an optional user data.<br>
-- param eventName The name of the event which needs to be dispatched.<br>
-- param optionalUserData The optional user data, it's a void*, the default value is nullptr.
-- @function [parent=#EventDispatcher] dispatchCustomEvent 
-- @param self
-- @param #string eventName
-- @param #void optionalUserData
-- @return EventDispatcher#EventDispatcher self (return value: cc.EventDispatcher)
        
--------------------------------
--  Resumes all listeners which are associated the specified target.<br>
-- param target A given target node.<br>
-- param recursive True if resume recursively, the default value is false.
-- @function [parent=#EventDispatcher] resumeEventListenersForTarget 
-- @param self
-- @param #cc.Node target
-- @param #bool recursive
-- @return EventDispatcher#EventDispatcher self (return value: cc.EventDispatcher)
        
--------------------------------
--  Removes all listeners which are associated with the specified target.<br>
-- param target A given target node.<br>
-- param recursive True if remove recursively, the default value is false.
-- @function [parent=#EventDispatcher] removeEventListenersForTarget 
-- @param self
-- @param #cc.Node target
-- @param #bool recursive
-- @return EventDispatcher#EventDispatcher self (return value: cc.EventDispatcher)
        
--------------------------------
--  Sets listener's priority with fixed value.<br>
-- param listener A given listener.<br>
-- param fixedPriority The fixed priority value.
-- @function [parent=#EventDispatcher] setPriority 
-- @param self
-- @param #cc.EventListener listener
-- @param #int fixedPriority
-- @return EventDispatcher#EventDispatcher self (return value: cc.EventDispatcher)
        
--------------------------------
--  Adds a Custom event listener.<br>
-- It will use a fixed priority of 1.<br>
-- param eventName A given name of the event.<br>
-- param callback A given callback method that associated the event name.<br>
-- return the generated event. Needed in order to remove the event from the dispatcher
-- @function [parent=#EventDispatcher] addCustomEventListener 
-- @param self
-- @param #string eventName
-- @param #function callback
-- @return EventListenerCustom#EventListenerCustom ret (return value: cc.EventListenerCustom)
        
--------------------------------
--  Dispatches the event.<br>
-- Also removes all EventListeners marked for deletion from the<br>
-- event dispatcher list.<br>
-- param event The event needs to be dispatched.
-- @function [parent=#EventDispatcher] dispatchEvent 
-- @param self
-- @param #cc.Event event
-- @return EventDispatcher#EventDispatcher self (return value: cc.EventDispatcher)
        
--------------------------------
--  Query whether the specified event listener id has been added.<br>
-- param listenerID The listenerID of the event listener id.<br>
-- return True if dispatching events is exist
-- @function [parent=#EventDispatcher] hasEventListener 
-- @param self
-- @param #std::basic_string<char> listenerID
-- @return bool#bool ret (return value: bool)
        
--------------------------------
--  Removes all listeners.
-- @function [parent=#EventDispatcher] removeAllEventListeners 
-- @param self
-- @return EventDispatcher#EventDispatcher self (return value: cc.EventDispatcher)
        
--------------------------------
--  Removes all custom listeners with the same event name.<br>
-- param customEventName A given event listener name which needs to be removed.
-- @function [parent=#EventDispatcher] removeCustomEventListeners 
-- @param self
-- @param #string customEventName
-- @return EventDispatcher#EventDispatcher self (return value: cc.EventDispatcher)
        
--------------------------------
--  Checks whether dispatching events is enabled.<br>
-- return True if dispatching events is enabled.
-- @function [parent=#EventDispatcher] isEnabled 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
--  Removes all listeners with the same event listener type.<br>
-- param listenerType A given event listener type which needs to be removed.
-- @function [parent=#EventDispatcher] removeEventListenersForType 
-- @param self
-- @param #int listenerType
-- @return EventDispatcher#EventDispatcher self (return value: cc.EventDispatcher)
        
--------------------------------
--  Constructor of EventDispatcher.
-- @function [parent=#EventDispatcher] EventDispatcher 
-- @param self
-- @return EventDispatcher#EventDispatcher self (return value: cc.EventDispatcher)
        
return nil
