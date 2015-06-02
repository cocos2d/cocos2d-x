
--------------------------------
-- @module Material
-- @extend RenderState
-- @parent_module cc

--------------------------------
--  returns a clone (deep-copy) of the material 
-- @function [parent=#Material] clone 
-- @param self
-- @return Material#Material ret (return value: cc.Material)
        
--------------------------------
--  Returns the number of Techniques in the Material. 
-- @function [parent=#Material] getTechniqueCount 
-- @param self
-- @return long#long ret (return value: long)
        
--------------------------------
-- / sets the material name
-- @function [parent=#Material] setName 
-- @param self
-- @param #string name
-- @return Material#Material self (return value: cc.Material)
        
--------------------------------
--  Returns a Technique by index. <br>
-- returns `nullptr` if the index is invalid.
-- @function [parent=#Material] getTechniqueByIndex 
-- @param self
-- @param #long index
-- @return Technique#Technique ret (return value: cc.Technique)
        
--------------------------------
-- / returns the material name
-- @function [parent=#Material] getName 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
--  Returns the list of Techniques 
-- @function [parent=#Material] getTechniques 
-- @param self
-- @return array_table#array_table ret (return value: array_table)
        
--------------------------------
--  Sets the current technique 
-- @function [parent=#Material] setTechnique 
-- @param self
-- @param #string techniqueName
-- @return Material#Material self (return value: cc.Material)
        
--------------------------------
--  Returns a Technique by its name.<br>
-- returns `nullptr` if the Technique can't be found.
-- @function [parent=#Material] getTechniqueByName 
-- @param self
-- @param #string name
-- @return Technique#Technique ret (return value: cc.Technique)
        
--------------------------------
--  Adds a Technique into the Material 
-- @function [parent=#Material] addTechnique 
-- @param self
-- @param #cc.Technique technique
-- @return Material#Material self (return value: cc.Material)
        
--------------------------------
--  Returns the Technique used by the Material 
-- @function [parent=#Material] getTechnique 
-- @param self
-- @return Technique#Technique ret (return value: cc.Technique)
        
--------------------------------
-- Creates a Material using the data from the Properties object defined at the specified URL,<br>
-- where the URL is of the format "<file-path>.<extension>#<namespace-id>/<namespace-id>/.../<namespace-id>"<br>
-- (and "#<namespace-id>/<namespace-id>/.../<namespace-id>" is optional).<br>
-- param url The URL pointing to the Properties object defining the material.<br>
-- return A new Material or NULL if there was an error.
-- @function [parent=#Material] createWithFilename 
-- @param self
-- @param #string path
-- @return Material#Material ret (return value: cc.Material)
        
--------------------------------
--  Creates a Material with a GLProgramState.<br>
-- It will only contain one Technique and one Pass.<br>
-- Added in order to support legacy code.
-- @function [parent=#Material] createWithGLStateProgram 
-- @param self
-- @param #cc.GLProgramState programState
-- @return Material#Material ret (return value: cc.Material)
        
--------------------------------
-- Creates a material from the specified properties object.<br>
-- param materialProperties The properties object defining the<br>
-- material (must have namespace equal to 'material').<br>
-- return A new Material.
-- @function [parent=#Material] createWithProperties 
-- @param self
-- @param #cc.Properties materialProperties
-- @return Material#Material ret (return value: cc.Material)
        
return nil
