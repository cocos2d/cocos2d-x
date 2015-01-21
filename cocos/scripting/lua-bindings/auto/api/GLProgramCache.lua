
--------------------------------
-- @module GLProgramCache
-- @extend Ref
-- @parent_module cc

--------------------------------
--  adds a GLProgram to the cache for a given name 
-- @function [parent=#GLProgramCache] addGLProgram 
-- @param self
-- @param #cc.GLProgram program
-- @param #string key
-- @return GLProgramCache#GLProgramCache self (return value: cc.GLProgramCache)
        
--------------------------------
--  returns a GL program for a given key 
-- @function [parent=#GLProgramCache] getGLProgram 
-- @param self
-- @param #string key
-- @return GLProgram#GLProgram ret (return value: cc.GLProgram)
        
--------------------------------
--  reload the default shaders 
-- @function [parent=#GLProgramCache] reloadDefaultGLPrograms 
-- @param self
-- @return GLProgramCache#GLProgramCache self (return value: cc.GLProgramCache)
        
--------------------------------
--  loads the default shaders 
-- @function [parent=#GLProgramCache] loadDefaultGLPrograms 
-- @param self
-- @return GLProgramCache#GLProgramCache self (return value: cc.GLProgramCache)
        
--------------------------------
--  purges the cache. It releases the retained instance. 
-- @function [parent=#GLProgramCache] destroyInstance 
-- @param self
-- @return GLProgramCache#GLProgramCache self (return value: cc.GLProgramCache)
        
--------------------------------
--  returns the shared instance 
-- @function [parent=#GLProgramCache] getInstance 
-- @param self
-- @return GLProgramCache#GLProgramCache ret (return value: cc.GLProgramCache)
        
--------------------------------
-- js ctor
-- @function [parent=#GLProgramCache] GLProgramCache 
-- @param self
-- @return GLProgramCache#GLProgramCache self (return value: cc.GLProgramCache)
        
return nil
