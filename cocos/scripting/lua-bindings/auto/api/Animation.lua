
--------------------------------
-- @module Animation
-- @extend Ref
-- @parent_module cc

--------------------------------
-- @function [parent=#Animation] getLoops 
-- @param self
-- @return unsigned int#unsigned int ret (return value: unsigned int)
        
--------------------------------
-- @function [parent=#Animation] addSpriteFrame 
-- @param self
-- @param #cc.SpriteFrame spriteframe
        
--------------------------------
-- @function [parent=#Animation] setRestoreOriginalFrame 
-- @param self
-- @param #bool bool
        
--------------------------------
-- @function [parent=#Animation] clone 
-- @param self
-- @return Animation#Animation ret (return value: cc.Animation)
        
--------------------------------
-- @function [parent=#Animation] getDuration 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- @function [parent=#Animation] setFrames 
-- @param self
-- @param #array_table array
        
--------------------------------
-- @function [parent=#Animation] getFrames 
-- @param self
-- @return array_table#array_table ret (return value: array_table)
        
--------------------------------
-- @function [parent=#Animation] setLoops 
-- @param self
-- @param #unsigned int int
        
--------------------------------
-- @function [parent=#Animation] setDelayPerUnit 
-- @param self
-- @param #float float
        
--------------------------------
-- @function [parent=#Animation] addSpriteFrameWithFile 
-- @param self
-- @param #string str
        
--------------------------------
-- @function [parent=#Animation] getTotalDelayUnits 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- @function [parent=#Animation] getDelayPerUnit 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- @function [parent=#Animation] getRestoreOriginalFrame 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#Animation] addSpriteFrameWithTexture 
-- @param self
-- @param #cc.Texture2D texture2d
-- @param #rect_table rect
        
--------------------------------
-- @overload self, array_table, float, unsigned int         
-- @overload self         
-- @function [parent=#Animation] create
-- @param self
-- @param #array_table array
-- @param #float float
-- @param #unsigned int int
-- @return Animation#Animation ret (retunr value: cc.Animation)

--------------------------------
-- @function [parent=#Animation] createWithSpriteFrames 
-- @param self
-- @param #array_table array
-- @param #float float
-- @param #unsigned int int
-- @return Animation#Animation ret (return value: cc.Animation)
        
return nil
