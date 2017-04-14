
--------------------------------
-- @module Node
-- @extend Ref
-- @parent_module cc

--------------------------------
-- @overload self, cc.Node, int         
-- @overload self, cc.Node         
-- @overload self, cc.Node, int, int         
-- @overload self, cc.Node, int, string         
-- @function [parent=#Node] addChild
-- @param self
-- @param #cc.Node child
-- @param #int localZOrder
-- @param #string name
-- @return Node#Node self (return value: cc.Node)

--------------------------------
-- @overload self, cc.Component         
-- @overload self, string         
-- @function [parent=#Node] removeComponent
-- @param self
-- @param #string name
-- @return bool#bool ret (return value: bool)

--------------------------------
-- 
-- @function [parent=#Node] setPhysicsBody 
-- @param self
-- @param #cc.PhysicsBody physicsBody
-- @return Node#Node self (return value: cc.Node)
        
--------------------------------
-- Gets the description string. It makes debugging easier.<br>
-- return A string<br>
-- js NA<br>
-- lua NA
-- @function [parent=#Node] getDescription 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- Sets the Y rotation (angle) of the node in degrees which performs a vertical rotational skew.<br>
-- The difference between `setRotationalSkew()` and `setSkew()` is that the first one simulate Flash's skew functionality,<br>
-- while the second one uses the real skew function.<br>
-- 0 is the default rotation angle.<br>
-- Positive values rotate node clockwise, and negative values for anti-clockwise.<br>
-- param rotationY    The Y rotation in degrees.<br>
-- warning The physics body doesn't support this.<br>
-- js setRotationY
-- @function [parent=#Node] setRotationSkewY 
-- @param self
-- @param #float rotationY
-- @return Node#Node self (return value: cc.Node)
        
--------------------------------
-- If you want the opacity affect the color property, then set to true.<br>
-- param value A boolean value.
-- @function [parent=#Node] setOpacityModifyRGB 
-- @param self
-- @param #bool value
-- @return Node#Node self (return value: cc.Node)
        
--------------------------------
-- Change node's cascadeOpacity property.<br>
-- param cascadeOpacityEnabled True to enable cascadeOpacity, false otherwise.
-- @function [parent=#Node] setCascadeOpacityEnabled 
-- @param self
-- @param #bool cascadeOpacityEnabled
-- @return Node#Node self (return value: cc.Node)
        
--------------------------------
-- @overload self         
-- @overload self         
-- @function [parent=#Node] getChildren
-- @param self
-- @return array_table#array_table ret (return value: array_table)

--------------------------------
-- Set the callback of event onExit.<br>
-- param callback A std::function<void()> callback.
-- @function [parent=#Node] setOnExitCallback 
-- @param self
-- @param #function callback
-- @return Node#Node self (return value: cc.Node)
        
--------------------------------
-- Sets the ActionManager object that is used by all actions.<br>
-- warning If you set a new ActionManager, then previously created actions will be removed.<br>
-- param actionManager     A ActionManager object that is used by all actions.
-- @function [parent=#Node] setActionManager 
-- @param self
-- @param #cc.ActionManager actionManager
-- @return Node#Node self (return value: cc.Node)
        
--------------------------------
-- Converts a local Vec2 to world space coordinates.The result is in Points.<br>
-- treating the returned/received node point as anchor relative.<br>
-- param nodePoint A given coordinate.<br>
-- return A point in world space coordinates, anchor relative.
-- @function [parent=#Node] convertToWorldSpaceAR 
-- @param self
-- @param #vec2_table nodePoint
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
-- Gets whether the anchor point will be (0,0) when you position this node.<br>
-- see `setIgnoreAnchorPointForPosition(bool)`<br>
-- return true if the anchor point will be (0,0) when you position this node.
-- @function [parent=#Node] isIgnoreAnchorPointForPosition 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- Gets a child from the container with its name.<br>
-- param name   An identifier to find the child node.<br>
-- return a Node object whose name equals to the input parameter.<br>
-- since v3.2
-- @function [parent=#Node] getChildByName 
-- @param self
-- @param #string name
-- @return Node#Node ret (return value: cc.Node)
        
--------------------------------
-- Update the displayed opacity of node with it's parent opacity;<br>
-- param parentOpacity The opacity of parent node.
-- @function [parent=#Node] updateDisplayedOpacity 
-- @param self
-- @param #unsigned char parentOpacity
-- @return Node#Node self (return value: cc.Node)
        
--------------------------------
-- 
-- @function [parent=#Node] init 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- get & set camera mask, the node is visible by the camera whose camera flag & node's camera mask is true
-- @function [parent=#Node] getCameraMask 
-- @param self
-- @return unsigned short#unsigned short ret (return value: unsigned short)
        
--------------------------------
-- Sets the rotation (angle) of the node in degrees.<br>
-- 0 is the default rotation angle.<br>
-- Positive values rotate node clockwise, and negative values for anti-clockwise.<br>
-- param rotation     The rotation of the node in degrees.
-- @function [parent=#Node] setRotation 
-- @param self
-- @param #float rotation
-- @return Node#Node self (return value: cc.Node)
        
--------------------------------
-- Changes the scale factor on Z axis of this node<br>
-- The Default value is 1.0 if you haven't changed it before.<br>
-- param scaleZ   The scale factor on Z axis.<br>
-- warning The physics body doesn't support this.
-- @function [parent=#Node] setScaleZ 
-- @param self
-- @param #float scaleZ
-- @return Node#Node self (return value: cc.Node)
        
--------------------------------
-- Sets the scale (y) of the node.<br>
-- It is a scaling factor that multiplies the height of the node and its children.<br>
-- param scaleY   The scale factor on Y axis.<br>
-- warning The physics body doesn't support this.
-- @function [parent=#Node] setScaleY 
-- @param self
-- @param #float scaleY
-- @return Node#Node self (return value: cc.Node)
        
--------------------------------
-- Sets the scale (x) of the node.<br>
-- It is a scaling factor that multiplies the width of the node and its children.<br>
-- param scaleX   The scale factor on X axis.<br>
-- warning The physics body doesn't support this.
-- @function [parent=#Node] setScaleX 
-- @param self
-- @param #float scaleX
-- @return Node#Node self (return value: cc.Node)
        
--------------------------------
-- Sets the X rotation (angle) of the node in degrees which performs a horizontal rotational skew.<br>
-- The difference between `setRotationalSkew()` and `setSkew()` is that the first one simulate Flash's skew functionality,<br>
-- while the second one uses the real skew function.<br>
-- 0 is the default rotation angle.<br>
-- Positive values rotate node clockwise, and negative values for anti-clockwise.<br>
-- param rotationX    The X rotation in degrees which performs a horizontal rotational skew.<br>
-- warning The physics body doesn't support this.<br>
-- js setRotationX
-- @function [parent=#Node] setRotationSkewX 
-- @param self
-- @param #float rotationX
-- @return Node#Node self (return value: cc.Node)
        
--------------------------------
-- Set the callback of event EnterTransitionDidFinish.<br>
-- param callback A std::function<void()> callback.
-- @function [parent=#Node] setonEnterTransitionDidFinishCallback 
-- @param self
-- @param #function callback
-- @return Node#Node self (return value: cc.Node)
        
--------------------------------
-- Removes all components
-- @function [parent=#Node] removeAllComponents 
-- @param self
-- @return Node#Node self (return value: cc.Node)
        
--------------------------------
-- 
-- @function [parent=#Node] _setLocalZOrder 
-- @param self
-- @param #int z
-- @return Node#Node self (return value: cc.Node)
        
--------------------------------
-- Modify the camera mask for current node.<br>
-- If applyChildren is true, then it will modify the camera mask of its children recursively.<br>
-- param mask A unsigned short bit for mask.<br>
-- param applyChildren A boolean value to determine whether the mask bit should apply to its children or not.
-- @function [parent=#Node] setCameraMask 
-- @param self
-- @param #unsigned short mask
-- @param #bool applyChildren
-- @return Node#Node self (return value: cc.Node)
        
--------------------------------
-- Returns a tag that is used to identify the node easily.<br>
-- return An integer that identifies the node.<br>
-- Please use `getTag()` instead.
-- @function [parent=#Node] getTag 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- / @{/ @name GLProgram<br>
-- Return the GLProgram (shader) currently used for this node.<br>
-- return The GLProgram (shader) currently used for this node.
-- @function [parent=#Node] getGLProgram 
-- @param self
-- @return GLProgram#GLProgram ret (return value: cc.GLProgram)
        
--------------------------------
-- Returns the world affine transform matrix. The matrix is in Pixels.<br>
-- return transformation matrix, in pixels.
-- @function [parent=#Node] getNodeToWorldTransform 
-- @param self
-- @return mat4_table#mat4_table ret (return value: mat4_table)
        
--------------------------------
-- Returns the position (X,Y,Z) in its parent's coordinate system.<br>
-- return The position (X, Y, and Z) in its parent's coordinate system.<br>
-- js NA
-- @function [parent=#Node] getPosition3D 
-- @param self
-- @return vec3_table#vec3_table ret (return value: vec3_table)
        
--------------------------------
-- Removes a child from the container. It will also cleanup all running actions depending on the cleanup parameter.<br>
-- param child     The child node which will be removed.<br>
-- param cleanup   True if all running actions and callbacks on the child node will be cleanup, false otherwise.
-- @function [parent=#Node] removeChild 
-- @param self
-- @param #cc.Node child
-- @param #bool cleanup
-- @return Node#Node self (return value: cc.Node)
        
--------------------------------
-- Converts a Vec2 to world space coordinates. The result is in Points.<br>
-- param nodePoint A given coordinate.<br>
-- return A point in world space coordinates.
-- @function [parent=#Node] convertToWorldSpace 
-- @param self
-- @param #vec2_table nodePoint
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
--  Returns the Scene that contains the Node.<br>
-- It returns `nullptr` if the node doesn't belong to any Scene.<br>
-- This function recursively calls parent->getScene() until parent is a Scene object. The results are not cached. It is that the user caches the results in case this functions is being used inside a loop.<br>
-- return The Scene that contains the node.
-- @function [parent=#Node] getScene 
-- @param self
-- @return Scene#Scene ret (return value: cc.Scene)
        
--------------------------------
--  Get the event dispatcher of scene.<br>
-- return The event dispatcher of scene.
-- @function [parent=#Node] getEventDispatcher 
-- @param self
-- @return EventDispatcher#EventDispatcher ret (return value: cc.EventDispatcher)
        
--------------------------------
-- Changes the X skew angle of the node in degrees.<br>
-- The difference between `setRotationalSkew()` and `setSkew()` is that the first one simulate Flash's skew functionality<br>
-- while the second one uses the real skew function.<br>
-- This angle describes the shear distortion in the X direction.<br>
-- Thus, it is the angle between the Y coordinate and the left edge of the shape<br>
-- The default skewX angle is 0. Positive values distort the node in a CW direction.<br>
-- param skewX The X skew angle of the node in degrees.<br>
-- warning The physics body doesn't support this.
-- @function [parent=#Node] setSkewX 
-- @param self
-- @param #float skewX
-- @return Node#Node self (return value: cc.Node)
        
--------------------------------
-- Set the GLProgramState for this node.<br>
-- param glProgramState The GLProgramState for this node.
-- @function [parent=#Node] setGLProgramState 
-- @param self
-- @param #cc.GLProgramState glProgramState
-- @return Node#Node self (return value: cc.Node)
        
--------------------------------
-- Set the callback of event onEnter.<br>
-- param callback A std::function<void()> callback.
-- @function [parent=#Node] setOnEnterCallback 
-- @param self
-- @param #function callback
-- @return Node#Node self (return value: cc.Node)
        
--------------------------------
-- Removes all actions from the running action list by its flags.<br>
-- param flags   A flag field that removes actions based on bitwise AND.
-- @function [parent=#Node] stopActionsByFlags 
-- @param self
-- @param #unsigned int flags
-- @return Node#Node self (return value: cc.Node)
        
--------------------------------
-- 
-- @function [parent=#Node] setNormalizedPosition 
-- @param self
-- @param #vec2_table position
-- @return Node#Node self (return value: cc.Node)
        
--------------------------------
-- Set the callback of event ExitTransitionDidStart.<br>
-- param callback A std::function<void()> callback.
-- @function [parent=#Node] setonExitTransitionDidStartCallback 
-- @param self
-- @param #function callback
-- @return Node#Node self (return value: cc.Node)
        
--------------------------------
-- convenience methods which take a Touch instead of Vec2.<br>
-- param touch A given touch.<br>
-- return A point in world space coordinates.
-- @function [parent=#Node] convertTouchToNodeSpace 
-- @param self
-- @param #cc.Touch touch
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
-- @overload self, bool         
-- @overload self         
-- @function [parent=#Node] removeAllChildrenWithCleanup
-- @param self
-- @param #bool cleanup
-- @return Node#Node self (return value: cc.Node)

--------------------------------
-- @overload self, cc.Node         
-- @overload self         
-- @function [parent=#Node] getNodeToParentAffineTransform
-- @param self
-- @param #cc.Node ancestor
-- @return AffineTransform#AffineTransform ret (return value: cc.AffineTransform)

--------------------------------
-- Whether cascadeOpacity is enabled or not.<br>
-- return A boolean value.
-- @function [parent=#Node] isCascadeOpacityEnabled 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- Sets the parent node.<br>
-- param parent    A pointer to the parent node.
-- @function [parent=#Node] setParent 
-- @param self
-- @param #cc.Node parent
-- @return Node#Node self (return value: cc.Node)
        
--------------------------------
--  Returns a string that is used to identify the node.<br>
-- return A string that identifies the node.<br>
-- since v3.2
-- @function [parent=#Node] getName 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- Resumes all scheduled selectors, actions and event listeners.<br>
-- This method is called internally by onEnter.
-- @function [parent=#Node] resume 
-- @param self
-- @return Node#Node self (return value: cc.Node)
        
--------------------------------
-- Returns the rotation (X,Y,Z) in degrees.<br>
-- return The rotation of the node in 3d.<br>
-- js NA
-- @function [parent=#Node] getRotation3D 
-- @param self
-- @return vec3_table#vec3_table ret (return value: vec3_table)
        
--------------------------------
-- @overload self, cc.Node         
-- @overload self         
-- @function [parent=#Node] getNodeToParentTransform
-- @param self
-- @param #cc.Node ancestor
-- @return mat4_table#mat4_table ret (return value: mat4_table)

--------------------------------
-- converts a Touch (world coordinates) into a local coordinate. This method is AR (Anchor Relative).<br>
-- param touch A given touch.<br>
-- return A point in world space coordinates, anchor relative.
-- @function [parent=#Node] convertTouchToNodeSpaceAR 
-- @param self
-- @param #cc.Touch touch
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
-- Converts a Vec2 to node (local) space coordinates. The result is in Points.<br>
-- param worldPoint A given coordinate.<br>
-- return A point in node (local) space coordinates.
-- @function [parent=#Node] convertToNodeSpace 
-- @param self
-- @param #vec2_table worldPoint
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
--  Sets the position (x,y) using values between 0 and 1.<br>
-- The positions in pixels is calculated like the following:<br>
-- code pseudo code<br>
-- void setNormalizedPosition(Vec2 pos) {<br>
-- Size s = getParent()->getContentSize();<br>
-- _position = pos * s;<br>
-- }<br>
-- endcode<br>
-- param position The normalized position (x,y) of the node, using value between 0 and 1.
-- @function [parent=#Node] setPositionNormalized 
-- @param self
-- @param #vec2_table position
-- @return Node#Node self (return value: cc.Node)
        
--------------------------------
-- Pauses all scheduled selectors, actions and event listeners.<br>
-- This method is called internally by onExit.
-- @function [parent=#Node] pause 
-- @param self
-- @return Node#Node self (return value: cc.Node)
        
--------------------------------
-- If node opacity will modify the RGB color value, then you should override this method and return true.<br>
-- return A boolean value, true indicates that opacity will modify color; false otherwise.
-- @function [parent=#Node] isOpacityModifyRGB 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @overload self, float, float         
-- @overload self, vec2_table         
-- @function [parent=#Node] setPosition
-- @param self
-- @param #float x
-- @param #float y
-- @return Node#Node self (return value: cc.Node)

--------------------------------
-- Removes an action from the running action list by its tag.<br>
-- param tag   A tag that indicates the action to be removed.
-- @function [parent=#Node] stopActionByTag 
-- @param self
-- @param #int tag
-- @return Node#Node self (return value: cc.Node)
        
--------------------------------
-- Reorders a child according to a new z value.<br>
-- param child     An already added child node. It MUST be already added.<br>
-- param localZOrder Z order for drawing priority. Please refer to setLocalZOrder(int).
-- @function [parent=#Node] reorderChild 
-- @param self
-- @param #cc.Node child
-- @param #int localZOrder
-- @return Node#Node self (return value: cc.Node)
        
--------------------------------
-- Changes the Y skew angle of the node in degrees.<br>
-- The difference between `setRotationalSkew()` and `setSkew()` is that the first one simulate Flash's skew functionality<br>
-- while the second one uses the real skew function.<br>
-- This angle describes the shear distortion in the Y direction.<br>
-- Thus, it is the angle between the X coordinate and the bottom edge of the shape.<br>
-- The default skewY angle is 0. Positive values distort the node in a CCW direction.<br>
-- param skewY    The Y skew angle of the node in degrees.<br>
-- warning The physics body doesn't support this.
-- @function [parent=#Node] setSkewY 
-- @param self
-- @param #float skewY
-- @return Node#Node self (return value: cc.Node)
        
--------------------------------
-- Sets the 'z' coordinate in the position. It is the OpenGL Z vertex value.<br>
-- The OpenGL depth buffer and depth testing are disabled by default. You need to turn them on.<br>
-- In order to use this property correctly.<br>
-- `setPositionZ()` also sets the `setGlobalZValue()` with the positionZ as value.<br>
-- see `setGlobalZValue()`<br>
-- param positionZ  OpenGL Z vertex of this node.<br>
-- js setVertexZ
-- @function [parent=#Node] setPositionZ 
-- @param self
-- @param #float positionZ
-- @return Node#Node self (return value: cc.Node)
        
--------------------------------
-- Sets the rotation (X,Y,Z) in degrees.<br>
-- Useful for 3d rotations.<br>
-- warning The physics body doesn't support this.<br>
-- param rotation The rotation of the node in 3d.<br>
-- js NA
-- @function [parent=#Node] setRotation3D 
-- @param self
-- @param #vec3_table rotation
-- @return Node#Node self (return value: cc.Node)
        
--------------------------------
-- Gets/Sets x or y coordinate individually for position.<br>
-- These methods are used in Lua and Javascript Bindings<br>
-- Sets the x coordinate of the node in its parent's coordinate system.<br>
-- param x The x coordinate of the node.
-- @function [parent=#Node] setPositionX 
-- @param self
-- @param #float x
-- @return Node#Node self (return value: cc.Node)
        
--------------------------------
-- Sets the transformation matrix manually.<br>
-- param transform A given transformation matrix.
-- @function [parent=#Node] setNodeToParentTransform 
-- @param self
-- @param #mat4_table transform
-- @return Node#Node self (return value: cc.Node)
        
--------------------------------
-- Returns the anchor point in percent.<br>
-- see `setAnchorPoint(const Vec2&)`<br>
-- return The anchor point of node.
-- @function [parent=#Node] getAnchorPoint 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
-- Returns the numbers of actions that are running plus the ones that are schedule to run (actions in actionsToAdd and actions arrays).<br>
-- Composable actions are counted as 1 action. Example:<br>
-- If you are running 1 Sequence of 7 actions, it will return 1.<br>
-- If you are running 7 Sequences of 2 actions, it will return 7.<br>
-- return The number of actions that are running plus the ones that are schedule to run.
-- @function [parent=#Node] getNumberOfRunningActions 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- Calls children's updateTransform() method recursively.<br>
-- This method is moved from Sprite, so it's no longer specific to Sprite.<br>
-- As the result, you apply SpriteBatchNode's optimization on your customed Node.<br>
-- e.g., `batchNode->addChild(myCustomNode)`, while you can only addChild(sprite) before.
-- @function [parent=#Node] updateTransform 
-- @param self
-- @return Node#Node self (return value: cc.Node)
        
--------------------------------
-- Sets the shader program for this node<br>
-- Since v2.0, each rendering node must set its shader program.<br>
-- It should be set in initialize phase.<br>
-- code<br>
-- node->setGLProgram(GLProgramCache::getInstance()->getProgram(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR));<br>
-- endcode<br>
-- param glprogram The shader program.
-- @function [parent=#Node] setGLProgram 
-- @param self
-- @param #cc.GLProgram glprogram
-- @return Node#Node self (return value: cc.Node)
        
--------------------------------
-- Determines if the node is visible.<br>
-- see `setVisible(bool)`<br>
-- return true if the node is visible, false if the node is hidden.
-- @function [parent=#Node] isVisible 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- Returns the amount of children.<br>
-- return The amount of children.
-- @function [parent=#Node] getChildrenCount 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- Converts a Vec2 to node (local) space coordinates. The result is in Points.<br>
-- treating the returned/received node point as anchor relative.<br>
-- param worldPoint A given coordinate.<br>
-- return A point in node (local) space coordinates, anchor relative.
-- @function [parent=#Node] convertToNodeSpaceAR 
-- @param self
-- @param #vec2_table worldPoint
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
-- Adds a component.<br>
-- param component A given component.<br>
-- return True if added success.
-- @function [parent=#Node] addComponent 
-- @param self
-- @param #cc.Component component
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- Executes an action, and returns the action that is executed.<br>
-- This node becomes the action's target. Refer to Action::getTarget().<br>
-- warning Actions don't retain their target.<br>
-- param action An Action pointer.
-- @function [parent=#Node] runAction 
-- @param self
-- @param #cc.Action action
-- @return Action#Action ret (return value: cc.Action)
        
--------------------------------
-- @overload self         
-- @overload self, cc.Renderer, mat4_table, unsigned int         
-- @function [parent=#Node] visit
-- @param self
-- @param #cc.Renderer renderer
-- @param #mat4_table parentTransform
-- @param #unsigned int parentFlags
-- @return Node#Node self (return value: cc.Node)

--------------------------------
-- Returns the rotation of the node in degrees.<br>
-- see `setRotation(float)`<br>
-- return The rotation of the node in degrees.
-- @function [parent=#Node] getRotation 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#Node] getPhysicsBody 
-- @param self
-- @return PhysicsBody#PhysicsBody ret (return value: cc.PhysicsBody)
        
--------------------------------
-- Returns the anchorPoint in absolute pixels.<br>
-- warning You can only read it. If you wish to modify it, use anchorPoint instead.<br>
-- see `getAnchorPoint()`<br>
-- return The anchor point in absolute pixels.
-- @function [parent=#Node] getAnchorPointInPoints 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
-- Removes a child from the container by tag value. It will also cleanup all running actions depending on the cleanup parameter.<br>
-- param name       A string that identifies a child node.<br>
-- param cleanup   True if all running actions and callbacks on the child node will be cleanup, false otherwise.
-- @function [parent=#Node] removeChildByName 
-- @param self
-- @param #string name
-- @param #bool cleanup
-- @return Node#Node self (return value: cc.Node)
        
--------------------------------
-- Return the GLProgramState currently used for this node.<br>
-- return The GLProgramState currently used for this node.
-- @function [parent=#Node] getGLProgramState 
-- @param self
-- @return GLProgramState#GLProgramState ret (return value: cc.GLProgramState)
        
--------------------------------
-- Sets a Scheduler object that is used to schedule all "updates" and timers.<br>
-- warning If you set a new Scheduler, then previously created timers/update are going to be removed.<br>
-- param scheduler     A Scheduler object that is used to schedule all "update" and timers.
-- @function [parent=#Node] setScheduler 
-- @param self
-- @param #cc.Scheduler scheduler
-- @return Node#Node self (return value: cc.Node)
        
--------------------------------
-- Stops and removes all actions from the running action list .
-- @function [parent=#Node] stopAllActions 
-- @param self
-- @return Node#Node self (return value: cc.Node)
        
--------------------------------
-- Returns the X skew angle of the node in degrees.<br>
-- see `setSkewX(float)`<br>
-- return The X skew angle of the node in degrees.
-- @function [parent=#Node] getSkewX 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- Returns the Y skew angle of the node in degrees.<br>
-- see `setSkewY(float)`<br>
-- return The Y skew angle of the node in degrees.
-- @function [parent=#Node] getSkewY 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- Query node's displayed color.<br>
-- return A Color3B color value.
-- @function [parent=#Node] getDisplayedColor 
-- @param self
-- @return color3b_table#color3b_table ret (return value: color3b_table)
        
--------------------------------
-- Gets an action from the running action list by its tag.<br>
-- see `setTag(int)`, `getTag()`.<br>
-- return The action object with the given tag.
-- @function [parent=#Node] getActionByTag 
-- @param self
-- @param #int tag
-- @return Action#Action ret (return value: cc.Action)
        
--------------------------------
--  Changes the name that is used to identify the node easily.<br>
-- param name A string that identifies the node.<br>
-- since v3.2
-- @function [parent=#Node] setName 
-- @param self
-- @param #string name
-- @return Node#Node self (return value: cc.Node)
        
--------------------------------
-- Update method will be called automatically every frame if "scheduleUpdate" is called, and the node is "live".<br>
-- param delta In seconds.
-- @function [parent=#Node] update 
-- @param self
-- @param #float delta
-- @return Node#Node self (return value: cc.Node)
        
--------------------------------
-- Return the node's display opacity.<br>
-- The difference between opacity and displayedOpacity is:<br>
-- The displayedOpacity is what's the final rendering opacity of node.<br>
-- return A GLubyte value.
-- @function [parent=#Node] getDisplayedOpacity 
-- @param self
-- @return unsigned char#unsigned char ret (return value: unsigned char)
        
--------------------------------
-- Gets the local Z order of this node.<br>
-- see `setLocalZOrder(int)`<br>
-- return The local (relative to its siblings) Z order.
-- @function [parent=#Node] getLocalZOrder 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- @overload self         
-- @overload self         
-- @function [parent=#Node] getScheduler
-- @param self
-- @return Scheduler#Scheduler ret (return value: cc.Scheduler)

--------------------------------
-- 
-- @function [parent=#Node] getParentToNodeAffineTransform 
-- @param self
-- @return AffineTransform#AffineTransform ret (return value: cc.AffineTransform)
        
--------------------------------
--  Returns the normalized position.<br>
-- return The normalized position.
-- @function [parent=#Node] getPositionNormalized 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
-- Change the color of node.<br>
-- param color A Color3B color value.
-- @function [parent=#Node] setColor 
-- @param self
-- @param #color3b_table color
-- @return Node#Node self (return value: cc.Node)
        
--------------------------------
-- Returns whether or not the node is "running".<br>
-- If the node is running it will accept event callbacks like onEnter(), onExit(), update().<br>
-- return Whether or not the node is running.
-- @function [parent=#Node] isRunning 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @overload self         
-- @overload self         
-- @function [parent=#Node] getParent
-- @param self
-- @return Node#Node ret (return value: cc.Node)

--------------------------------
-- Gets position Z coordinate of this node.<br>
-- see setPositionZ(float)<br>
-- return The position Z coordinate of this node.<br>
-- js getVertexZ
-- @function [parent=#Node] getPositionZ 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
--  Gets the y coordinate of the node in its parent's coordinate system.<br>
-- return The y coordinate of the node.
-- @function [parent=#Node] getPositionY 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
--  Gets the x coordinate of the node in its parent's coordinate system.<br>
-- return The x coordinate of the node.
-- @function [parent=#Node] getPositionX 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- Removes a child from the container by tag value. It will also cleanup all running actions depending on the cleanup parameter.<br>
-- param tag       An integer number that identifies a child node.<br>
-- param cleanup   True if all running actions and callbacks on the child node will be cleanup, false otherwise.<br>
-- Please use `removeChildByName` instead.
-- @function [parent=#Node] removeChildByTag 
-- @param self
-- @param #int tag
-- @param #bool cleanup
-- @return Node#Node self (return value: cc.Node)
        
--------------------------------
--  Sets the y coordinate of the node in its parent's coordinate system.<br>
-- param y The y coordinate of the node.
-- @function [parent=#Node] setPositionY 
-- @param self
-- @param #float y
-- @return Node#Node self (return value: cc.Node)
        
--------------------------------
-- 
-- @function [parent=#Node] getNodeToWorldAffineTransform 
-- @param self
-- @return AffineTransform#AffineTransform ret (return value: cc.AffineTransform)
        
--------------------------------
-- Update node's displayed color with its parent color.<br>
-- param parentColor A Color3B color value.
-- @function [parent=#Node] updateDisplayedColor 
-- @param self
-- @param #color3b_table parentColor
-- @return Node#Node self (return value: cc.Node)
        
--------------------------------
-- Sets whether the node is visible.<br>
-- The default value is true, a node is default to visible.<br>
-- param visible   true if the node is visible, false if the node is hidden.
-- @function [parent=#Node] setVisible 
-- @param self
-- @param #bool visible
-- @return Node#Node self (return value: cc.Node)
        
--------------------------------
-- Returns the matrix that transform parent's space coordinates to the node's (local) space coordinates.<br>
-- The matrix is in Pixels.<br>
-- return The transformation matrix.
-- @function [parent=#Node] getParentToNodeTransform 
-- @param self
-- @return mat4_table#mat4_table ret (return value: mat4_table)
        
--------------------------------
-- Checks whether a lambda function is scheduled.<br>
-- param key      key of the callback<br>
-- return Whether the lambda function selector is scheduled.<br>
-- js NA<br>
-- lua NA
-- @function [parent=#Node] isScheduled 
-- @param self
-- @param #string key
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- Defines the order in which the nodes are renderer.<br>
-- Nodes that have a Global Z Order lower, are renderer first.<br>
-- In case two or more nodes have the same Global Z Order, the order is not guaranteed.<br>
-- The only exception if the Nodes have a Global Z Order == 0. In that case, the Scene Graph order is used.<br>
-- By default, all nodes have a Global Z Order = 0. That means that by default, the Scene Graph order is used to render the nodes.<br>
-- Global Z Order is useful when you need to render nodes in an order different than the Scene Graph order.<br>
-- Limitations: Global Z Order can't be used by Nodes that have SpriteBatchNode as one of their ancestors.<br>
-- And if ClippingNode is one of the ancestors, then "global Z order" will be relative to the ClippingNode.<br>
-- see `setLocalZOrder()`<br>
-- see `setVertexZ()`<br>
-- since v3.0<br>
-- param globalZOrder The global Z order value.
-- @function [parent=#Node] setGlobalZOrder 
-- @param self
-- @param #float globalZOrder
-- @return Node#Node self (return value: cc.Node)
        
--------------------------------
-- @overload self, float, float         
-- @overload self, float         
-- @function [parent=#Node] setScale
-- @param self
-- @param #float scaleX
-- @param #float scaleY
-- @return Node#Node self (return value: cc.Node)

--------------------------------
-- Gets a child from the container with its tag.<br>
-- param tag   An identifier to find the child node.<br>
-- return a Node object whose tag equals to the input parameter.<br>
-- Please use `getChildByName()` instead.
-- @function [parent=#Node] getChildByTag 
-- @param self
-- @param #int tag
-- @return Node#Node ret (return value: cc.Node)
        
--------------------------------
-- Returns the scale factor on Z axis of this node<br>
-- see `setScaleZ(float)`<br>
-- return The scale factor on Z axis.
-- @function [parent=#Node] getScaleZ 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- Returns the scale factor on Y axis of this node<br>
-- see `setScaleY(float)`<br>
-- return The scale factor on Y axis.
-- @function [parent=#Node] getScaleY 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- Returns the scale factor on X axis of this node<br>
-- see setScaleX(float)<br>
-- return The scale factor on X axis.
-- @function [parent=#Node] getScaleX 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- LocalZOrder is the 'key' used to sort the node relative to its siblings.<br>
-- The Node's parent will sort all its children based on the LocalZOrder value.<br>
-- If two nodes have the same LocalZOrder, then the node that was added first to the children's array will be in front of the other node in the array.<br>
-- Also, the Scene Graph is traversed using the "In-Order" tree traversal algorithm ( http:en.wikipedia.org/wiki/Tree_traversal#In-order )<br>
-- And Nodes that have LocalZOrder values < 0 are the "left" subtree<br>
-- While Nodes with LocalZOrder >=0 are the "right" subtree.<br>
-- see `setGlobalZOrder`<br>
-- see `setVertexZ`<br>
-- param localZOrder The local Z order value.
-- @function [parent=#Node] setLocalZOrder 
-- @param self
-- @param #int localZOrder
-- @return Node#Node self (return value: cc.Node)
        
--------------------------------
-- 
-- @function [parent=#Node] getWorldToNodeAffineTransform 
-- @param self
-- @return AffineTransform#AffineTransform ret (return value: cc.AffineTransform)
        
--------------------------------
-- If you want node's color affect the children node's color, then set it to true.<br>
-- Otherwise, set it to false.<br>
-- param cascadeColorEnabled A boolean value.
-- @function [parent=#Node] setCascadeColorEnabled 
-- @param self
-- @param #bool cascadeColorEnabled
-- @return Node#Node self (return value: cc.Node)
        
--------------------------------
-- Change node opacity.<br>
-- param opacity A GLubyte opacity value.
-- @function [parent=#Node] setOpacity 
-- @param self
-- @param #unsigned char opacity
-- @return Node#Node self (return value: cc.Node)
        
--------------------------------
-- Stops all running actions and schedulers
-- @function [parent=#Node] cleanup 
-- @param self
-- @return Node#Node self (return value: cc.Node)
        
--------------------------------
-- / @{/ @name component functions<br>
-- Gets a component by its name.<br>
-- param name A given name of component.<br>
-- return The Component by name.
-- @function [parent=#Node] getComponent 
-- @param self
-- @param #string name
-- @return Component#Component ret (return value: cc.Component)
        
--------------------------------
-- Returns the untransformed size of the node.<br>
-- see `setContentSize(const Size&)`<br>
-- return The untransformed size of the node.
-- @function [parent=#Node] getContentSize 
-- @param self
-- @return size_table#size_table ret (return value: size_table)
        
--------------------------------
-- Removes all actions from the running action list by its tag.<br>
-- param tag   A tag that indicates the action to be removed.
-- @function [parent=#Node] stopAllActionsByTag 
-- @param self
-- @param #int tag
-- @return Node#Node self (return value: cc.Node)
        
--------------------------------
-- Query node's color value.<br>
-- return A Color3B color value.
-- @function [parent=#Node] getColor 
-- @param self
-- @return color3b_table#color3b_table ret (return value: color3b_table)
        
--------------------------------
-- Returns an AABB (axis-aligned bounding-box) in its parent's coordinate system.<br>
-- return An AABB (axis-aligned bounding-box) in its parent's coordinate system
-- @function [parent=#Node] getBoundingBox 
-- @param self
-- @return rect_table#rect_table ret (return value: rect_table)
        
--------------------------------
-- Sets whether the anchor point will be (0,0) when you position this node.<br>
-- This is an internal method, only used by Layer and Scene. Don't call it outside framework.<br>
-- The default value is false, while in Layer and Scene are true.<br>
-- param ignore    true if anchor point will be (0,0) when you position this node.
-- @function [parent=#Node] setIgnoreAnchorPointForPosition 
-- @param self
-- @param #bool ignore
-- @return Node#Node self (return value: cc.Node)
        
--------------------------------
--  Set event dispatcher for scene.<br>
-- param dispatcher The event dispatcher of scene.
-- @function [parent=#Node] setEventDispatcher 
-- @param self
-- @param #cc.EventDispatcher dispatcher
-- @return Node#Node self (return value: cc.Node)
        
--------------------------------
-- Returns the Node's Global Z Order.<br>
-- see `setGlobalZOrder(int)`<br>
-- return The node's global Z order
-- @function [parent=#Node] getGlobalZOrder 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- @overload self         
-- @overload self, cc.Renderer, mat4_table, unsigned int         
-- @function [parent=#Node] draw
-- @param self
-- @param #cc.Renderer renderer
-- @param #mat4_table transform
-- @param #unsigned int flags
-- @return Node#Node self (return value: cc.Node)

--------------------------------
-- Returns a user assigned Object.<br>
-- Similar to UserData, but instead of holding a void* it holds an object.<br>
-- The UserObject will be retained once in this method,<br>
-- and the previous UserObject (if existed) will be released.<br>
-- The UserObject will be released in Node's destructor.<br>
-- param userObject    A user assigned Object.
-- @function [parent=#Node] setUserObject 
-- @param self
-- @param #cc.Ref userObject
-- @return Node#Node self (return value: cc.Node)
        
--------------------------------
-- @overload self, bool         
-- @overload self         
-- @function [parent=#Node] removeFromParentAndCleanup
-- @param self
-- @param #bool cleanup
-- @return Node#Node self (return value: cc.Node)

--------------------------------
-- Sets the position (X, Y, and Z) in its parent's coordinate system.<br>
-- param position The position (X, Y, and Z) in its parent's coordinate system.<br>
-- js NA
-- @function [parent=#Node] setPosition3D 
-- @param self
-- @param #vec3_table position
-- @return Node#Node self (return value: cc.Node)
        
--------------------------------
-- Returns the numbers of actions that are running plus the ones that are<br>
-- schedule to run (actions in actionsToAdd and actions arrays) with a<br>
-- specific tag.<br>
-- Composable actions are counted as 1 action. Example:<br>
-- If you are running 1 Sequence of 7 actions, it will return 1.<br>
-- If you are running 7 Sequences of 2 actions, it will return 7.<br>
-- param  tag The tag that will be searched.<br>
-- return The number of actions that are running plus the<br>
-- ones that are schedule to run with specific tag.
-- @function [parent=#Node] getNumberOfRunningActionsByTag 
-- @param self
-- @param #int tag
-- @return int#int ret (return value: int)
        
--------------------------------
-- Sorts the children array once before drawing, instead of every time when a child is added or reordered.<br>
-- This approach can improves the performance massively.<br>
-- note Don't call this manually unless a child added needs to be removed in the same frame.
-- @function [parent=#Node] sortAllChildren 
-- @param self
-- @return Node#Node self (return value: cc.Node)
        
--------------------------------
-- Returns the inverse world affine transform matrix. The matrix is in Pixels.<br>
-- return The transformation matrix.
-- @function [parent=#Node] getWorldToNodeTransform 
-- @param self
-- @return mat4_table#mat4_table ret (return value: mat4_table)
        
--------------------------------
-- Gets the scale factor of the node,  when X and Y have the same scale factor.<br>
-- warning Assert when `_scaleX != _scaleY`<br>
-- see setScale(float)<br>
-- return The scale factor of the node.
-- @function [parent=#Node] getScale 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- Return the node's opacity.<br>
-- return A GLubyte value.
-- @function [parent=#Node] getOpacity 
-- @param self
-- @return unsigned char#unsigned char ret (return value: unsigned char)
        
--------------------------------
--  !!! ONLY FOR INTERNAL USE<br>
-- Sets the arrival order when this node has a same ZOrder with other children.<br>
-- A node which called addChild subsequently will take a larger arrival order,<br>
-- If two children have the same Z order, the child with larger arrival order will be drawn later.<br>
-- warning This method is used internally for localZOrder sorting, don't change this manually<br>
-- param orderOfArrival   The arrival order.
-- @function [parent=#Node] updateOrderOfArrival 
-- @param self
-- @return Node#Node self (return value: cc.Node)
        
--------------------------------
-- 
-- @function [parent=#Node] getNormalizedPosition 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
-- Gets the X rotation (angle) of the node in degrees which performs a horizontal rotation skew.<br>
-- see `setRotationSkewX(float)`<br>
-- return The X rotation in degrees.<br>
-- js getRotationX 
-- @function [parent=#Node] getRotationSkewX 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- Gets the Y rotation (angle) of the node in degrees which performs a vertical rotational skew.<br>
-- see `setRotationSkewY(float)`<br>
-- return The Y rotation in degrees.<br>
-- js getRotationY
-- @function [parent=#Node] getRotationSkewY 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- Changes the tag that is used to identify the node easily.<br>
-- Please refer to getTag for the sample code.<br>
-- param tag   A integer that identifies the node.<br>
-- Please use `setName()` instead.
-- @function [parent=#Node] setTag 
-- @param self
-- @param #int tag
-- @return Node#Node self (return value: cc.Node)
        
--------------------------------
-- Query whether cascadeColor is enabled or not.<br>
-- return Whether cascadeColor is enabled or not.
-- @function [parent=#Node] isCascadeColorEnabled 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- Stops and removes an action from the running action list.<br>
-- param action    The action object to be removed.
-- @function [parent=#Node] stopAction 
-- @param self
-- @param #cc.Action action
-- @return Node#Node self (return value: cc.Node)
        
--------------------------------
-- @overload self         
-- @overload self         
-- @function [parent=#Node] getActionManager
-- @param self
-- @return ActionManager#ActionManager ret (return value: cc.ActionManager)

--------------------------------
-- Allocates and initializes a node.<br>
-- return A initialized node which is marked as "autorelease".
-- @function [parent=#Node] create 
-- @param self
-- @return Node#Node ret (return value: cc.Node)
        
--------------------------------
-- 
-- @function [parent=#Node] Node 
-- @param self
-- @return Node#Node self (return value: cc.Node)
        
return nil
