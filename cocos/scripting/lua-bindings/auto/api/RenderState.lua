
--------------------------------
-- @module RenderState
-- @extend Ref
-- @parent_module cc

--------------------------------
--  Texture that will use in the CC_Texture0 uniform.<br>
-- Added to be backwards compatible. Use Samplers from .material instead.
-- @function [parent=#RenderState] setTexture 
-- @param self
-- @param #cc.Texture2D texture
-- @return RenderState#RenderState self (return value: cc.RenderState)
        
--------------------------------
-- Returns the topmost RenderState in the hierarchy below the given RenderState.
-- @function [parent=#RenderState] getTopmost 
-- @param self
-- @param #cc.RenderState below
-- @return RenderState#RenderState ret (return value: cc.RenderState)
        
--------------------------------
--  Returns the texture that is going to be used for CC_Texture0.<br>
-- Added to be backwards compatible.
-- @function [parent=#RenderState] getTexture 
-- @param self
-- @return Texture2D#Texture2D ret (return value: cc.Texture2D)
        
--------------------------------
-- Binds the render state for this RenderState and any of its parents, top-down,<br>
-- for the given pass.
-- @function [parent=#RenderState] bind 
-- @param self
-- @param #cc.Pass pass
-- @return RenderState#RenderState self (return value: cc.RenderState)
        
--------------------------------
-- 
-- @function [parent=#RenderState] getName 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- 
-- @function [parent=#RenderState] getStateBlock 
-- @param self
-- @return RenderState::StateBlock#RenderState::StateBlock ret (return value: cc.RenderState::StateBlock)
        
--------------------------------
-- Static initializer that is called during game startup.
-- @function [parent=#RenderState] initialize 
-- @param self
-- @return RenderState#RenderState self (return value: cc.RenderState)
        
return nil
