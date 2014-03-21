
--------------------------------
-- @module EventDispatcher
-- @extend Ref

--------------------------------
-- @function [parent=#EventDispatcher] pauseEventListenersForTarget 
-- @param self
-- @param #cc.Node node
-- @param #bool bool
        
--------------------------------
-- @function [parent=#EventDispatcher] addEventListenerWithSceneGraphPriority 
-- @param self
-- @param #cc.EventListener eventlistener
-- @param #cc.Node node
        
--------------------------------
-- @function [parent=#EventDispatcher] setEnabled 
-- @param self
-- @param #bool bool
        
--------------------------------
-- @function [parent=#EventDispatcher] addEventListenerWithFixedPriority 
-- @param self
-- @param #cc.EventListener eventlistener
-- @param #int int
        
--------------------------------
-- @function [parent=#EventDispatcher] removeEventListener 
-- @param self
-- @param #cc.EventListener eventlistener
        
--------------------------------
-- @function [parent=#EventDispatcher] resumeEventListenersForTarget 
-- @param self
-- @param #cc.Node node
-- @param #bool bool
        
--------------------------------
-- @function [parent=#EventDispatcher] removeEventListenersForTarget 
-- @param self
-- @param #cc.Node node
-- @param #bool bool
        
--------------------------------
-- @function [parent=#EventDispatcher] setPriority 
-- @param self
-- @param #cc.EventListener eventlistener
-- @param #int int
        
--------------------------------
-- @function [parent=#EventDispatcher] addCustomEventListener 
-- @param self
-- @param #string str
-- @param #function func
-- @return EventListenerCustom#EventListenerCustom ret (return value: cc.EventListenerCustom)
        
--------------------------------
-- @function [parent=#EventDispatcher] dispatchEvent 
-- @param self
-- @param #cc.Event event
        
--------------------------------
-- @function [parent=#EventDispatcher] removeAllEventListeners 
-- @param self
        
--------------------------------
-- @function [parent=#EventDispatcher] removeCustomEventListeners 
-- @param self
-- @param #string str
        
--------------------------------
-- @function [parent=#EventDispatcher] isEnabled 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#EventDispatcher] removeEventListenersForType 
-- @param self
-- @param #cc.EventListener::Type type
        
--------------------------------
-- @function [parent=#EventDispatcher] EventDispatcher 
-- @param self
        
return nil
