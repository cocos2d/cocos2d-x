
--------------------------------
-- @module ProtocolAnalytics
-- @extend PluginProtocol
-- @parent_module plugin

--------------------------------
-- brief Track an event begin.<br>
-- param eventId The identity of event
-- @function [parent=#ProtocolAnalytics] logTimedEventBegin 
-- @param self
-- @param #char eventId
        
--------------------------------
-- brief log an error<br>
-- param errorId The identity of error<br>
-- param message Extern message for the error
-- @function [parent=#ProtocolAnalytics] logError 
-- @param self
-- @param #char errorId
-- @param #char message
        
--------------------------------
-- brief Whether to catch uncaught exceptions to server.<br>
-- warning This interface only worked on android.
-- @function [parent=#ProtocolAnalytics] setCaptureUncaughtException 
-- @param self
-- @param #bool enabled
        
--------------------------------
-- brief Set the timeout for expiring a session.<br>
-- param millis In milliseconds as the unit of time.<br>
-- note It must be invoked before calling startSession.
-- @function [parent=#ProtocolAnalytics] setSessionContinueMillis 
-- @param self
-- @param #long millis
        
--------------------------------
-- brief log an event.<br>
-- param eventId The identity of event<br>
-- param paramMap Extern parameters of the event, use NULL if not needed.
-- @function [parent=#ProtocolAnalytics] logEvent 
-- @param self
-- @param #char eventId
-- @param #map_table paramMap
        
--------------------------------
-- brief Start a new session.<br>
-- param appKey The identity of the application.
-- @function [parent=#ProtocolAnalytics] startSession 
-- @param self
-- @param #char appKey
        
--------------------------------
-- brief Stop a session.<br>
-- warning This interface only worked on android
-- @function [parent=#ProtocolAnalytics] stopSession 
-- @param self
        
--------------------------------
-- brief Track an event end.<br>
-- param eventId The identity of event
-- @function [parent=#ProtocolAnalytics] logTimedEventEnd 
-- @param self
-- @param #char eventId
        
return nil
