
--------------------------------
-- @module Sprite3D
-- @extend Node,BlendProtocol
-- @parent_module cc

--------------------------------
-- 
-- @function [parent=#Sprite3D] setCullFaceEnabled 
-- @param self
-- @param #bool enable
-- @return Sprite3D#Sprite3D self (return value: cc.Sprite3D)
        
--------------------------------
-- @overload self, cc.Texture2D         
-- @overload self, string         
-- @function [parent=#Sprite3D] setTexture
-- @param self
-- @param #string texFile
-- @return Sprite3D#Sprite3D self (return value: cc.Sprite3D)

--------------------------------
-- 
-- @function [parent=#Sprite3D] getLightMask 
-- @param self
-- @return unsigned int#unsigned int ret (return value: unsigned int)
        
--------------------------------
-- 
-- @function [parent=#Sprite3D] createAttachSprite3DNode 
-- @param self
-- @param #cc.NodeData nodedata
-- @param #cc.MaterialDatas matrialdatas
-- @return Sprite3D#Sprite3D self (return value: cc.Sprite3D)
        
--------------------------------
--  load file and set it to meshedatas, nodedatas and materialdatas, obj file .mtl file should be at the same directory if exist 
-- @function [parent=#Sprite3D] loadFromFile 
-- @param self
-- @param #string path
-- @param #cc.NodeDatas nodedatas
-- @param #cc.MeshDatas meshdatas
-- @param #cc.MaterialDatas materialdatas
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#Sprite3D] setCullFace 
-- @param self
-- @param #unsigned int cullFace
-- @return Sprite3D#Sprite3D self (return value: cc.Sprite3D)
        
--------------------------------
-- 
-- @function [parent=#Sprite3D] addMesh 
-- @param self
-- @param #cc.Mesh mesh
-- @return Sprite3D#Sprite3D self (return value: cc.Sprite3D)
        
--------------------------------
-- remove all attach nodes
-- @function [parent=#Sprite3D] removeAllAttachNode 
-- @param self
-- @return Sprite3D#Sprite3D self (return value: cc.Sprite3D)
        
--------------------------------
-- generate default GLProgramState
-- @function [parent=#Sprite3D] genGLProgramState 
-- @param self
-- @return Sprite3D#Sprite3D self (return value: cc.Sprite3D)
        
--------------------------------
-- get mesh
-- @function [parent=#Sprite3D] getMesh 
-- @param self
-- @return Mesh#Mesh ret (return value: cc.Mesh)
        
--------------------------------
-- 
-- @function [parent=#Sprite3D] createSprite3DNode 
-- @param self
-- @param #cc.NodeData nodedata
-- @param #cc.ModelData modeldata
-- @param #cc.MaterialDatas matrialdatas
-- @return Sprite3D#Sprite3D ret (return value: cc.Sprite3D)
        
--------------------------------
--  get mesh count 
-- @function [parent=#Sprite3D] getMeshCount 
-- @param self
-- @return long#long ret (return value: long)
        
--------------------------------
-- 
-- @function [parent=#Sprite3D] onAABBDirty 
-- @param self
-- @return Sprite3D#Sprite3D self (return value: cc.Sprite3D)
        
--------------------------------
-- get Mesh by index
-- @function [parent=#Sprite3D] getMeshByIndex 
-- @param self
-- @param #int index
-- @return Mesh#Mesh ret (return value: cc.Mesh)
        
--------------------------------
-- 
-- @function [parent=#Sprite3D] createNode 
-- @param self
-- @param #cc.NodeData nodedata
-- @param #cc.Node root
-- @param #cc.MaterialDatas matrialdatas
-- @param #bool singleSprite
-- @return Sprite3D#Sprite3D self (return value: cc.Sprite3D)
        
--------------------------------
-- 
-- @function [parent=#Sprite3D] isForceDepthWrite 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#Sprite3D] getBlendFunc 
-- @param self
-- @return BlendFunc#BlendFunc ret (return value: cc.BlendFunc)
        
--------------------------------
-- get MeshIndexData by Id
-- @function [parent=#Sprite3D] getMeshIndexData 
-- @param self
-- @param #string indexId
-- @return MeshIndexData#MeshIndexData ret (return value: cc.MeshIndexData)
        
--------------------------------
-- remove attach node
-- @function [parent=#Sprite3D] removeAttachNode 
-- @param self
-- @param #string boneName
-- @return Sprite3D#Sprite3D self (return value: cc.Sprite3D)
        
--------------------------------
--  light mask getter & setter, light works only when _lightmask & light's flag is true, default value of _lightmask is 0xffff 
-- @function [parent=#Sprite3D] setLightMask 
-- @param self
-- @param #unsigned int mask
-- @return Sprite3D#Sprite3D self (return value: cc.Sprite3D)
        
--------------------------------
-- 
-- @function [parent=#Sprite3D] afterAsyncLoad 
-- @param self
-- @param #void param
-- @return Sprite3D#Sprite3D self (return value: cc.Sprite3D)
        
--------------------------------
-- load sprite3d from cache, return true if succeed, false otherwise
-- @function [parent=#Sprite3D] loadFromCache 
-- @param self
-- @param #string path
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#Sprite3D] initFrom 
-- @param self
-- @param #cc.NodeDatas nodedatas
-- @param #cc.MeshDatas meshdatas
-- @param #cc.MaterialDatas materialdatas
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- get AttachNode by bone name, return nullptr if not exist
-- @function [parent=#Sprite3D] getAttachNode 
-- @param self
-- @param #string boneName
-- @return AttachNode#AttachNode ret (return value: cc.AttachNode)
        
--------------------------------
-- 
-- @function [parent=#Sprite3D] initWithFile 
-- @param self
-- @param #string path
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#Sprite3D] setBlendFunc 
-- @param self
-- @param #cc.BlendFunc blendFunc
-- @return Sprite3D#Sprite3D self (return value: cc.Sprite3D)
        
--------------------------------
-- 
-- @function [parent=#Sprite3D] getSkeleton 
-- @param self
-- @return Skeleton3D#Skeleton3D ret (return value: cc.Skeleton3D)
        
--------------------------------
-- Force to write to depth buffer, this is useful if you want to achieve effects like fading.
-- @function [parent=#Sprite3D] setForceDepthWrite 
-- @param self
-- @param #bool value
-- @return Sprite3D#Sprite3D self (return value: cc.Sprite3D)
        
--------------------------------
-- get Mesh by Name, it returns the first one if there are more than one mesh with the same name 
-- @function [parent=#Sprite3D] getMeshByName 
-- @param self
-- @param #string name
-- @return Mesh#Mesh ret (return value: cc.Mesh)
        
--------------------------------
-- @overload self, string         
-- @overload self         
-- @overload self, string, string         
-- @function [parent=#Sprite3D] create
-- @param self
-- @param #string modelPath
-- @param #string texturePath
-- @return Sprite3D#Sprite3D ret (return value: cc.Sprite3D)

--------------------------------
-- draw
-- @function [parent=#Sprite3D] draw 
-- @param self
-- @param #cc.Renderer renderer
-- @param #mat4_table transform
-- @param #unsigned int flags
-- @return Sprite3D#Sprite3D self (return value: cc.Sprite3D)
        
--------------------------------
-- Visits this Sprite3D's children and draw them recursively.<br>
-- Note: all its children will rendered as 3D objects
-- @function [parent=#Sprite3D] visit 
-- @param self
-- @param #cc.Renderer renderer
-- @param #mat4_table parentTransform
-- @param #unsigned int parentFlags
-- @return Sprite3D#Sprite3D self (return value: cc.Sprite3D)
        
--------------------------------
-- Executes an action, and returns the action that is executed. For Sprite3D special logic are needed to take care of Fading.<br>
-- This node becomes the action's target. Refer to Action::getTarget()<br>
-- warning Actions don't retain their target.<br>
-- return An Action pointer
-- @function [parent=#Sprite3D] runAction 
-- @param self
-- @param #cc.Action action
-- @return Action#Action ret (return value: cc.Action)
        
--------------------------------
-- 
-- @function [parent=#Sprite3D] init 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
--  just rember bind attributes 
-- @function [parent=#Sprite3D] setGLProgram 
-- @param self
-- @param #cc.GLProgram glprogram
-- @return Sprite3D#Sprite3D self (return value: cc.Sprite3D)
        
--------------------------------
-- Returns 2d bounding-box<br>
-- Note: the bouding-box is just get from the AABB which as Z=0, so that is not very accurate.
-- @function [parent=#Sprite3D] getBoundingBox 
-- @param self
-- @return rect_table#rect_table ret (return value: rect_table)
        
--------------------------------
--  set GLProgramState, you should bind attributes by yourself 
-- @function [parent=#Sprite3D] setGLProgramState 
-- @param self
-- @param #cc.GLProgramState glProgramState
-- @return Sprite3D#Sprite3D self (return value: cc.Sprite3D)
        
--------------------------------
-- 
-- @function [parent=#Sprite3D] Sprite3D 
-- @param self
-- @return Sprite3D#Sprite3D self (return value: cc.Sprite3D)
        
return nil
