
--------------------------------
-- @module Node
-- @extend Ref

--------------------------------
-- overload function: addChild(cc.Node, int)
--          
-- overload function: addChild(cc.Node)
--          
-- overload function: addChild(cc.Node, int, int)
--          
-- @function [parent=#Node] addChild
-- @param self
-- @param #cc.Node node
-- @param #int int
-- @param #int int

--------------------------------
-- @function [parent=#Node] removeComponent 
-- @param self
-- @param #string str
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#Node] setPhysicsBody 
-- @param self
-- @param #cc.PhysicsBody physicsbody
        
--------------------------------
-- @function [parent=#Node] getDescription 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- @function [parent=#Node] setRotationSkewY 
-- @param self
-- @param #float float
        
--------------------------------
-- @function [parent=#Node] setOpacityModifyRGB 
-- @param self
-- @param #bool bool
        
--------------------------------
-- @function [parent=#Node] setCascadeOpacityEnabled 
-- @param self
-- @param #bool bool
        
--------------------------------
-- overload function: getChildren()
--          
-- overload function: getChildren()
--          
-- @function [parent=#Node] getChildren
-- @param self
-- @return array_table#array_table ret (retunr value: array_table)

--------------------------------
-- @function [parent=#Node] pause 
-- @param self
        
--------------------------------
-- @function [parent=#Node] convertToWorldSpaceAR 
-- @param self
-- @param #vec2_table vec2
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
-- @function [parent=#Node] isIgnoreAnchorPointForPosition 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#Node] getChildByName 
-- @param self
-- @param #string str
-- @return Node#Node ret (return value: cc.Node)
        
--------------------------------
-- @function [parent=#Node] updateDisplayedOpacity 
-- @param self
-- @param #unsigned char char
        
--------------------------------
-- @function [parent=#Node] setRotation 
-- @param self
-- @param #float float
        
--------------------------------
-- @function [parent=#Node] setScaleZ 
-- @param self
-- @param #float float
        
--------------------------------
-- @function [parent=#Node] setScaleY 
-- @param self
-- @param #float float
        
--------------------------------
-- @function [parent=#Node] setScaleX 
-- @param self
-- @param #float float
        
--------------------------------
-- @function [parent=#Node] setRotationSkewX 
-- @param self
-- @param #float float
        
--------------------------------
-- @function [parent=#Node] removeAllComponents 
-- @param self
        
--------------------------------
-- @function [parent=#Node] _setLocalZOrder 
-- @param self
-- @param #int int
        
--------------------------------
-- @function [parent=#Node] getTag 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- @function [parent=#Node] getGLProgram 
-- @param self
-- @return GLProgram#GLProgram ret (return value: cc.GLProgram)
        
--------------------------------
-- @function [parent=#Node] getNodeToWorldTransform 
-- @param self
-- @return mat4_table#mat4_table ret (return value: mat4_table)
        
--------------------------------
-- @function [parent=#Node] getPosition3D 
-- @param self
-- @return vec3_table#vec3_table ret (return value: vec3_table)
        
--------------------------------
-- @function [parent=#Node] removeChild 
-- @param self
-- @param #cc.Node node
-- @param #bool bool
        
--------------------------------
-- @function [parent=#Node] convertToWorldSpace 
-- @param self
-- @param #vec2_table vec2
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
-- @function [parent=#Node] getScene 
-- @param self
-- @return Scene#Scene ret (return value: cc.Scene)
        
--------------------------------
-- @function [parent=#Node] getEventDispatcher 
-- @param self
-- @return EventDispatcher#EventDispatcher ret (return value: cc.EventDispatcher)
        
--------------------------------
-- @function [parent=#Node] setSkewX 
-- @param self
-- @param #float float
        
--------------------------------
-- @function [parent=#Node] setGLProgramState 
-- @param self
-- @param #cc.GLProgramState glprogramstate
        
--------------------------------
-- @function [parent=#Node] getOpacity 
-- @param self
-- @return unsigned char#unsigned char ret (return value: unsigned char)
        
--------------------------------
-- @function [parent=#Node] setNormalizedPosition 
-- @param self
-- @param #vec2_table vec2
        
--------------------------------
-- @function [parent=#Node] convertTouchToNodeSpace 
-- @param self
-- @param #cc.Touch touch
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
-- overload function: removeAllChildrenWithCleanup(bool)
--          
-- overload function: removeAllChildrenWithCleanup()
--          
-- @function [parent=#Node] removeAllChildrenWithCleanup
-- @param self
-- @param #bool bool

--------------------------------
-- @function [parent=#Node] getNodeToParentAffineTransform 
-- @param self
-- @return AffineTransform#AffineTransform ret (return value: cc.AffineTransform)
        
--------------------------------
-- @function [parent=#Node] isCascadeOpacityEnabled 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#Node] setParent 
-- @param self
-- @param #cc.Node node
        
--------------------------------
-- @function [parent=#Node] getName 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- @function [parent=#Node] getRotation3D 
-- @param self
-- @return vec3_table#vec3_table ret (return value: vec3_table)
        
--------------------------------
-- @function [parent=#Node] getNodeToParentTransform 
-- @param self
-- @return mat4_table#mat4_table ret (return value: mat4_table)
        
--------------------------------
-- @function [parent=#Node] convertTouchToNodeSpaceAR 
-- @param self
-- @param #cc.Touch touch
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
-- @function [parent=#Node] convertToNodeSpace 
-- @param self
-- @param #vec2_table vec2
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
-- @function [parent=#Node] resume 
-- @param self
        
--------------------------------
-- @function [parent=#Node] getPhysicsBody 
-- @param self
-- @return PhysicsBody#PhysicsBody ret (return value: cc.PhysicsBody)
        
--------------------------------
-- overload function: setPosition(float, float)
--          
-- overload function: setPosition(vec2_table)
--          
-- @function [parent=#Node] setPosition
-- @param self
-- @param #float float
-- @param #float float

--------------------------------
-- @function [parent=#Node] stopActionByTag 
-- @param self
-- @param #int int
        
--------------------------------
-- @function [parent=#Node] reorderChild 
-- @param self
-- @param #cc.Node node
-- @param #int int
        
--------------------------------
-- @function [parent=#Node] ignoreAnchorPointForPosition 
-- @param self
-- @param #bool bool
        
--------------------------------
-- @function [parent=#Node] setSkewY 
-- @param self
-- @param #float float
        
--------------------------------
-- @function [parent=#Node] setPositionZ 
-- @param self
-- @param #float float
        
--------------------------------
-- @function [parent=#Node] setRotation3D 
-- @param self
-- @param #vec3_table vec3
        
--------------------------------
-- @function [parent=#Node] setPositionX 
-- @param self
-- @param #float float
        
--------------------------------
-- @function [parent=#Node] setNodeToParentTransform 
-- @param self
-- @param #mat4_table mat4
        
--------------------------------
-- @function [parent=#Node] getAnchorPoint 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
-- @function [parent=#Node] getNumberOfRunningActions 
-- @param self
-- @return long#long ret (return value: long)
        
--------------------------------
-- @function [parent=#Node] updateTransform 
-- @param self
        
--------------------------------
-- @function [parent=#Node] setGLProgram 
-- @param self
-- @param #cc.GLProgram glprogram
        
--------------------------------
-- @function [parent=#Node] isVisible 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#Node] getChildrenCount 
-- @param self
-- @return long#long ret (return value: long)
        
--------------------------------
-- @function [parent=#Node] convertToNodeSpaceAR 
-- @param self
-- @param #vec2_table vec2
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
-- @function [parent=#Node] addComponent 
-- @param self
-- @param #cc.Component component
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#Node] runAction 
-- @param self
-- @param #cc.Action action
-- @return Action#Action ret (return value: cc.Action)
        
--------------------------------
-- @function [parent=#Node] isOpacityModifyRGB 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#Node] getRotation 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- @function [parent=#Node] getAnchorPointInPoints 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
-- overload function: visit()
--          
-- overload function: visit(cc.Renderer, mat4_table, unsigned int)
--          
-- @function [parent=#Node] visit
-- @param self
-- @param #cc.Renderer renderer
-- @param #mat4_table mat4
-- @param #unsigned int int

--------------------------------
-- @function [parent=#Node] getGLProgramState 
-- @param self
-- @return GLProgramState#GLProgramState ret (return value: cc.GLProgramState)
        
--------------------------------
-- @function [parent=#Node] setScheduler 
-- @param self
-- @param #cc.Scheduler scheduler
        
--------------------------------
-- @function [parent=#Node] stopAllActions 
-- @param self
        
--------------------------------
-- @function [parent=#Node] getSkewX 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- @function [parent=#Node] getSkewY 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- @function [parent=#Node] getDisplayedColor 
-- @param self
-- @return color3b_table#color3b_table ret (return value: color3b_table)
        
--------------------------------
-- @function [parent=#Node] getActionByTag 
-- @param self
-- @param #int int
-- @return Action#Action ret (return value: cc.Action)
        
--------------------------------
-- @function [parent=#Node] setName 
-- @param self
-- @param #string str
        
--------------------------------
-- overload function: setAdditionalTransform(cc.AffineTransform)
--          
-- overload function: setAdditionalTransform(mat4_table)
--          
-- @function [parent=#Node] setAdditionalTransform
-- @param self
-- @param #mat4_table mat4

--------------------------------
-- @function [parent=#Node] getDisplayedOpacity 
-- @param self
-- @return unsigned char#unsigned char ret (return value: unsigned char)
        
--------------------------------
-- @function [parent=#Node] getLocalZOrder 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- overload function: getScheduler()
--          
-- overload function: getScheduler()
--          
-- @function [parent=#Node] getScheduler
-- @param self
-- @return Scheduler#Scheduler ret (retunr value: cc.Scheduler)

--------------------------------
-- @function [parent=#Node] getParentToNodeAffineTransform 
-- @param self
-- @return AffineTransform#AffineTransform ret (return value: cc.AffineTransform)
        
--------------------------------
-- @function [parent=#Node] getOrderOfArrival 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- @function [parent=#Node] setActionManager 
-- @param self
-- @param #cc.ActionManager actionmanager
        
--------------------------------
-- @function [parent=#Node] setColor 
-- @param self
-- @param #color3b_table color3b
        
--------------------------------
-- @function [parent=#Node] isRunning 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- overload function: getParent()
--          
-- overload function: getParent()
--          
-- @function [parent=#Node] getParent
-- @param self
-- @return Node#Node ret (retunr value: cc.Node)

--------------------------------
-- @function [parent=#Node] getPositionZ 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- @function [parent=#Node] getPositionY 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- @function [parent=#Node] getPositionX 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- @function [parent=#Node] removeChildByTag 
-- @param self
-- @param #int int
-- @param #bool bool
        
--------------------------------
-- @function [parent=#Node] setPositionY 
-- @param self
-- @param #float float
        
--------------------------------
-- @function [parent=#Node] getNodeToWorldAffineTransform 
-- @param self
-- @return AffineTransform#AffineTransform ret (return value: cc.AffineTransform)
        
--------------------------------
-- @function [parent=#Node] updateDisplayedColor 
-- @param self
-- @param #color3b_table color3b
        
--------------------------------
-- @function [parent=#Node] setVisible 
-- @param self
-- @param #bool bool
        
--------------------------------
-- @function [parent=#Node] getParentToNodeTransform 
-- @param self
-- @return mat4_table#mat4_table ret (return value: mat4_table)
        
--------------------------------
-- @function [parent=#Node] setGlobalZOrder 
-- @param self
-- @param #float float
        
--------------------------------
-- overload function: setScale(float, float)
--          
-- overload function: setScale(float)
--          
-- @function [parent=#Node] setScale
-- @param self
-- @param #float float
-- @param #float float

--------------------------------
-- @function [parent=#Node] getChildByTag 
-- @param self
-- @param #int int
-- @return Node#Node ret (return value: cc.Node)
        
--------------------------------
-- @function [parent=#Node] setOrderOfArrival 
-- @param self
-- @param #int int
        
--------------------------------
-- @function [parent=#Node] getScaleZ 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- @function [parent=#Node] getScaleY 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- @function [parent=#Node] getScaleX 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- @function [parent=#Node] setLocalZOrder 
-- @param self
-- @param #int int
        
--------------------------------
-- @function [parent=#Node] getWorldToNodeAffineTransform 
-- @param self
-- @return AffineTransform#AffineTransform ret (return value: cc.AffineTransform)
        
--------------------------------
-- @function [parent=#Node] setCascadeColorEnabled 
-- @param self
-- @param #bool bool
        
--------------------------------
-- @function [parent=#Node] setOpacity 
-- @param self
-- @param #unsigned char char
        
--------------------------------
-- @function [parent=#Node] cleanup 
-- @param self
        
--------------------------------
-- @function [parent=#Node] getComponent 
-- @param self
-- @param #string str
-- @return Component#Component ret (return value: cc.Component)
        
--------------------------------
-- @function [parent=#Node] getContentSize 
-- @param self
-- @return size_table#size_table ret (return value: size_table)
        
--------------------------------
-- @function [parent=#Node] getColor 
-- @param self
-- @return color3b_table#color3b_table ret (return value: color3b_table)
        
--------------------------------
-- @function [parent=#Node] getBoundingBox 
-- @param self
-- @return rect_table#rect_table ret (return value: rect_table)
        
--------------------------------
-- @function [parent=#Node] setEventDispatcher 
-- @param self
-- @param #cc.EventDispatcher eventdispatcher
        
--------------------------------
-- @function [parent=#Node] getGlobalZOrder 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- overload function: draw()
--          
-- overload function: draw(cc.Renderer, mat4_table, unsigned int)
--          
-- @function [parent=#Node] draw
-- @param self
-- @param #cc.Renderer renderer
-- @param #mat4_table mat4
-- @param #unsigned int int

--------------------------------
-- @function [parent=#Node] setUserObject 
-- @param self
-- @param #cc.Ref ref
        
--------------------------------
-- @function [parent=#Node] enumerateChildren 
-- @param self
-- @param #string str
-- @param #function func
        
--------------------------------
-- overload function: removeFromParentAndCleanup(bool)
--          
-- overload function: removeFromParentAndCleanup()
--          
-- @function [parent=#Node] removeFromParentAndCleanup
-- @param self
-- @param #bool bool

--------------------------------
-- @function [parent=#Node] setPosition3D 
-- @param self
-- @param #vec3_table vec3
        
--------------------------------
-- @function [parent=#Node] update 
-- @param self
-- @param #float float
        
--------------------------------
-- @function [parent=#Node] sortAllChildren 
-- @param self
        
--------------------------------
-- @function [parent=#Node] getWorldToNodeTransform 
-- @param self
-- @return mat4_table#mat4_table ret (return value: mat4_table)
        
--------------------------------
-- @function [parent=#Node] getScale 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- @function [parent=#Node] getNormalizedPosition 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
-- @function [parent=#Node] getRotationSkewX 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- @function [parent=#Node] getRotationSkewY 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- @function [parent=#Node] setTag 
-- @param self
-- @param #int int
        
--------------------------------
-- @function [parent=#Node] isCascadeColorEnabled 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#Node] stopAction 
-- @param self
-- @param #cc.Action action
        
--------------------------------
-- overload function: getActionManager()
--          
-- overload function: getActionManager()
--          
-- @function [parent=#Node] getActionManager
-- @param self
-- @return ActionManager#ActionManager ret (retunr value: cc.ActionManager)

--------------------------------
-- @function [parent=#Node] create 
-- @param self
-- @return Node#Node ret (return value: cc.Node)
        
return nil
