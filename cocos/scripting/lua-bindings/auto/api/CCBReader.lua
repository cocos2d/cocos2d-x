
--------------------------------
-- @module CCBReader
-- @extend Ref
-- @parent_module cc

--------------------------------
-- 
-- @function [parent=#CCBReader] addOwnerOutletName 
-- @param self
-- @param #string name
-- @return CCBReader#CCBReader self (return value: cc.CCBReader)
        
--------------------------------
-- 
-- @function [parent=#CCBReader] getOwnerCallbackNames 
-- @param self
-- @return array_table#array_table ret (return value: array_table)
        
--------------------------------
-- 
-- @function [parent=#CCBReader] addDocumentCallbackControlEvents 
-- @param self
-- @param #int eventType
-- @return CCBReader#CCBReader self (return value: cc.CCBReader)
        
--------------------------------
-- 
-- @function [parent=#CCBReader] setCCBRootPath 
-- @param self
-- @param #char ccbRootPath
-- @return CCBReader#CCBReader self (return value: cc.CCBReader)
        
--------------------------------
-- 
-- @function [parent=#CCBReader] addOwnerOutletNode 
-- @param self
-- @param #cc.Node node
-- @return CCBReader#CCBReader self (return value: cc.CCBReader)
        
--------------------------------
-- 
-- @function [parent=#CCBReader] getOwnerCallbackNodes 
-- @param self
-- @return array_table#array_table ret (return value: array_table)
        
--------------------------------
-- 
-- @function [parent=#CCBReader] readSoundKeyframesForSeq 
-- @param self
-- @param #cc.CCBSequence seq
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#CCBReader] getCCBRootPath 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- 
-- @function [parent=#CCBReader] getOwnerCallbackControlEvents 
-- @param self
-- @return array_table#array_table ret (return value: array_table)
        
--------------------------------
-- 
-- @function [parent=#CCBReader] getOwnerOutletNodes 
-- @param self
-- @return array_table#array_table ret (return value: array_table)
        
--------------------------------
-- 
-- @function [parent=#CCBReader] readUTF8 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- 
-- @function [parent=#CCBReader] addOwnerCallbackControlEvents 
-- @param self
-- @param #int type
-- @return CCBReader#CCBReader self (return value: cc.CCBReader)
        
--------------------------------
-- 
-- @function [parent=#CCBReader] getOwnerOutletNames 
-- @param self
-- @return array_table#array_table ret (return value: array_table)
        
--------------------------------
-- js setActionManager<br>
-- lua setActionManager
-- @function [parent=#CCBReader] setAnimationManager 
-- @param self
-- @param #cc.CCBAnimationManager pAnimationManager
-- @return CCBReader#CCBReader self (return value: cc.CCBReader)
        
--------------------------------
-- 
-- @function [parent=#CCBReader] readCallbackKeyframesForSeq 
-- @param self
-- @param #cc.CCBSequence seq
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#CCBReader] getAnimationManagersForNodes 
-- @param self
-- @return array_table#array_table ret (return value: array_table)
        
--------------------------------
-- 
-- @function [parent=#CCBReader] getNodesWithAnimationManagers 
-- @param self
-- @return array_table#array_table ret (return value: array_table)
        
--------------------------------
-- js getActionManager<br>
-- lua getActionManager
-- @function [parent=#CCBReader] getAnimationManager 
-- @param self
-- @return CCBAnimationManager#CCBAnimationManager ret (return value: cc.CCBAnimationManager)
        
--------------------------------
-- 
-- @function [parent=#CCBReader] setResolutionScale 
-- @param self
-- @param #float scale
-- @return CCBReader#CCBReader self (return value: cc.CCBReader)
        
--------------------------------
-- @overload self, cc.CCBReader         
-- @overload self, cc.NodeLoaderLibrary, cc.CCBMemberVariableAssigner, cc.CCBSelectorResolver, cc.NodeLoaderListener         
-- @overload self         
-- @function [parent=#CCBReader] CCBReader
-- @param self
-- @param #cc.NodeLoaderLibrary pNodeLoaderLibrary
-- @param #cc.CCBMemberVariableAssigner pCCBMemberVariableAssigner
-- @param #cc.CCBSelectorResolver pCCBSelectorResolver
-- @param #cc.NodeLoaderListener pNodeLoaderListener
-- @return CCBReader#CCBReader self (return value: cc.CCBReader)

return nil
