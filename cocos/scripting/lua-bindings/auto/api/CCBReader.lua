
--------------------------------
-- @module CCBReader
-- @extend Ref

--------------------------------
-- @function [parent=#CCBReader] addOwnerOutletName 
-- @param self
-- @param #string str
        
--------------------------------
-- @function [parent=#CCBReader] getOwnerCallbackNames 
-- @param self
-- @return array_table#array_table ret (return value: array_table)
        
--------------------------------
-- @function [parent=#CCBReader] addDocumentCallbackControlEvents 
-- @param self
-- @param #cc.Control::EventType eventtype
        
--------------------------------
-- @function [parent=#CCBReader] setCCBRootPath 
-- @param self
-- @param #char char
        
--------------------------------
-- @function [parent=#CCBReader] addOwnerOutletNode 
-- @param self
-- @param #cc.Node node
        
--------------------------------
-- @function [parent=#CCBReader] getOwnerCallbackNodes 
-- @param self
-- @return array_table#array_table ret (return value: array_table)
        
--------------------------------
-- @function [parent=#CCBReader] readSoundKeyframesForSeq 
-- @param self
-- @param #cc.CCBSequence ccbsequence
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#CCBReader] getCCBRootPath 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- @function [parent=#CCBReader] getOwnerCallbackControlEvents 
-- @param self
-- @return array_table#array_table ret (return value: array_table)
        
--------------------------------
-- @function [parent=#CCBReader] getOwnerOutletNodes 
-- @param self
-- @return array_table#array_table ret (return value: array_table)
        
--------------------------------
-- @function [parent=#CCBReader] readUTF8 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- @function [parent=#CCBReader] addOwnerCallbackControlEvents 
-- @param self
-- @param #cc.Control::EventType eventtype
        
--------------------------------
-- @function [parent=#CCBReader] getOwnerOutletNames 
-- @param self
-- @return array_table#array_table ret (return value: array_table)
        
--------------------------------
-- @function [parent=#CCBReader] setAnimationManager 
-- @param self
-- @param #cc.CCBAnimationManager ccbanimationmanager
        
--------------------------------
-- @function [parent=#CCBReader] readCallbackKeyframesForSeq 
-- @param self
-- @param #cc.CCBSequence ccbsequence
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#CCBReader] getAnimationManagersForNodes 
-- @param self
-- @return array_table#array_table ret (return value: array_table)
        
--------------------------------
-- @function [parent=#CCBReader] getNodesWithAnimationManagers 
-- @param self
-- @return array_table#array_table ret (return value: array_table)
        
--------------------------------
-- @function [parent=#CCBReader] getAnimationManager 
-- @param self
-- @return CCBAnimationManager#CCBAnimationManager ret (return value: cc.CCBAnimationManager)
        
--------------------------------
-- @function [parent=#CCBReader] setResolutionScale 
-- @param self
-- @param #float float
        
--------------------------------
-- overload function: CCBReader(cc.CCBReader)
--          
-- overload function: CCBReader(cc.NodeLoaderLibrary, cc.CCBMemberVariableAssigner, cc.CCBSelectorResolver, cc.NodeLoaderListener)
--          
-- overload function: CCBReader()
--          
-- @function [parent=#CCBReader] CCBReader
-- @param self
-- @param #cc.NodeLoaderLibrary nodeloaderlibrary
-- @param #cc.CCBMemberVariableAssigner ccbmembervariableassigner
-- @param #cc.CCBSelectorResolver ccbselectorresolver
-- @param #cc.NodeLoaderListener nodeloaderlistener

return nil
