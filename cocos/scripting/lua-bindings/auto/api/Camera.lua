
--------------------------------
-- @module Camera
-- @extend Node
-- @parent_module cc

--------------------------------
-- Gets the camera's projection matrix.<br>
-- return The camera projection matrix.
-- @function [parent=#Camera] getProjectionMatrix 
-- @param self
-- @return mat4_table#mat4_table ret (return value: mat4_table)
        
--------------------------------
-- get view projection matrix
-- @function [parent=#Camera] getViewProjectionMatrix 
-- @param self
-- @return mat4_table#mat4_table ret (return value: mat4_table)
        
--------------------------------
-- Gets the camera's view matrix.<br>
-- return The camera view matrix.
-- @function [parent=#Camera] getViewMatrix 
-- @param self
-- @return mat4_table#mat4_table ret (return value: mat4_table)
        
--------------------------------
-- get & set Camera flag
-- @function [parent=#Camera] getCameraFlag 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- Gets the type of camera.<br>
-- return The camera type.
-- @function [parent=#Camera] getType 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- Get object depth towards camera
-- @function [parent=#Camera] getDepthInView 
-- @param self
-- @param #mat4_table transform
-- @return float#float ret (return value: float)
        
--------------------------------
-- Make Camera looks at target<br>
-- param target The target camera is point at<br>
-- param up The up vector, usually it's Y axis
-- @function [parent=#Camera] lookAt 
-- @param self
-- @param #vec3_table target
-- @param #vec3_table up
        
--------------------------------
-- Is this aabb visible in frustum
-- @function [parent=#Camera] isVisibleInFrustum 
-- @param self
-- @param #cc.AABB aabb
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#Camera] setCameraFlag 
-- @param self
-- @param #int flag
        
--------------------------------
--  create default camera, the camera type depends on Director::getProjection 
-- @function [parent=#Camera] create 
-- @param self
-- @return Camera#Camera ret (return value: cc.Camera)
        
--------------------------------
-- Creates a perspective camera.<br>
-- param fieldOfView The field of view for the perspective camera (normally in the range of 40-60 degrees).<br>
-- param aspectRatio The aspect ratio of the camera (normally the width of the viewport divided by the height of the viewport).<br>
-- param nearPlane The near plane distance.<br>
-- param farPlane The far plane distance.
-- @function [parent=#Camera] createPerspective 
-- @param self
-- @param #float fieldOfView
-- @param #float aspectRatio
-- @param #float nearPlane
-- @param #float farPlane
-- @return Camera#Camera ret (return value: cc.Camera)
        
--------------------------------
-- Creates an orthographic camera.<br>
-- param zoomX The zoom factor along the X-axis of the orthographic projection (the width of the ortho projection).<br>
-- param zoomY The zoom factor along the Y-axis of the orthographic projection (the height of the ortho projection).<br>
-- param aspectRatio The aspect ratio of the orthographic projection.<br>
-- param nearPlane The near plane distance.<br>
-- param farPlane The far plane distance.
-- @function [parent=#Camera] createOrthographic 
-- @param self
-- @param #float zoomX
-- @param #float zoomY
-- @param #float nearPlane
-- @param #float farPlane
-- @return Camera#Camera ret (return value: cc.Camera)
        
--------------------------------
-- 
-- @function [parent=#Camera] getDefaultCamera 
-- @param self
-- @return Camera#Camera ret (return value: cc.Camera)
        
--------------------------------
-- 
-- @function [parent=#Camera] getVisitingCamera 
-- @param self
-- @return Camera#Camera ret (return value: cc.Camera)
        
--------------------------------
-- Sets the position (X, Y, and Z) in its parent's coordinate system
-- @function [parent=#Camera] setPosition3D 
-- @param self
-- @param #vec3_table position
        
return nil
