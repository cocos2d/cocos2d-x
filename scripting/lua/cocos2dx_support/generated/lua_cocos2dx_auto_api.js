/**
 * @module cocos2dx
 */
var cc = cc || {};

/**
 * @class Object
 */
cc.Object = {

/**
 * @method isSingleReference
 * @return A value converted from C/C++ "bool"
 */
isSingleReference : function () {},

/**
 * @method release
 */
release : function () {},

/**
 * @method retain
 */
retain : function () {},

/**
 * @method retainCount
 * @return A value converted from C/C++ "unsigned int"
 */
retainCount : function () {},

/**
 * @method Object
 * @constructor
 */
Object : function () {},

};

/**
 * @class Action
 */
cc.Action = {

/**
 * @method startWithTarget
 * @param {cocos2d::Node*}
 */
startWithTarget : function () {},

/**
 * @method setOriginalTarget
 * @param {cocos2d::Node*}
 */
setOriginalTarget : function () {},

/**
 * @method clone
 * @return A value converted from C/C++ "cocos2d::Action*"
 */
clone : function () {},

/**
 * @method getOriginalTarget
 * @return A value converted from C/C++ "cocos2d::Node*"
 */
getOriginalTarget : function () {},

/**
 * @method stop
 */
stop : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method getTarget
 * @return A value converted from C/C++ "cocos2d::Node*"
 */
getTarget : function () {},

/**
 * @method step
 * @param {float}
 */
step : function () {},

/**
 * @method setTag
 * @param {int}
 */
setTag : function () {},

/**
 * @method getTag
 * @return A value converted from C/C++ "int"
 */
getTag : function () {},

/**
 * @method setTarget
 * @param {cocos2d::Node*}
 */
setTarget : function () {},

/**
 * @method isDone
 * @return A value converted from C/C++ "bool"
 */
isDone : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::Action*"
 */
reverse : function () {},

};

/**
 * @class FiniteTimeAction
 */
cc.FiniteTimeAction = {

/**
 * @method clone
 * @return A value converted from C/C++ "cocos2d::FiniteTimeAction*"
 */
clone : function () {},

/**
 * @method setDuration
 * @param {float}
 */
setDuration : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::FiniteTimeAction*"
 */
reverse : function () {},

/**
 * @method getDuration
 * @return A value converted from C/C++ "float"
 */
getDuration : function () {},

};

/**
 * @class Speed
 */
cc.Speed = {

/**
 * @method setInnerAction
 * @param {cocos2d::ActionInterval*}
 */
setInnerAction : function () {},

/**
 * @method startWithTarget
 * @param {cocos2d::Node*}
 */
startWithTarget : function () {},

/**
 * @method getSpeed
 * @return A value converted from C/C++ "float"
 */
getSpeed : function () {},

/**
 * @method clone
 * @return A value converted from C/C++ "cocos2d::Speed*"
 */
clone : function () {},

/**
 * @method stop
 */
stop : function () {},

/**
 * @method step
 * @param {float}
 */
step : function () {},

/**
 * @method setSpeed
 * @param {float}
 */
setSpeed : function () {},

/**
 * @method initWithAction
 * @return A value converted from C/C++ "bool"
 * @param {cocos2d::ActionInterval*}
 * @param {float}
 */
initWithAction : function () {},

/**
 * @method getInnerAction
 * @return A value converted from C/C++ "cocos2d::ActionInterval*"
 */
getInnerAction : function () {},

/**
 * @method isDone
 * @return A value converted from C/C++ "bool"
 */
isDone : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::Speed*"
 */
reverse : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::Speed*"
 * @param {cocos2d::ActionInterval*}
 * @param {float}
 */
create : function () {},

/**
 * @method Speed
 * @constructor
 */
Speed : function () {},

};

/**
 * @class Follow
 */
cc.Follow = {

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::Follow*"
 */
reverse : function () {},

/**
 * @method clone
 * @return A value converted from C/C++ "cocos2d::Follow*"
 */
clone : function () {},

/**
 * @method initWithTarget
 * @return A value converted from C/C++ "bool"
 * @param {cocos2d::Node*}
 * @param {cocos2d::Rect}
 */
initWithTarget : function () {},

/**
 * @method stop
 */
stop : function () {},

/**
 * @method setBoudarySet
 * @param {bool}
 */
setBoudarySet : function () {},

/**
 * @method step
 * @param {float}
 */
step : function () {},

/**
 * @method isDone
 * @return A value converted from C/C++ "bool"
 */
isDone : function () {},

/**
 * @method isBoundarySet
 * @return A value converted from C/C++ "bool"
 */
isBoundarySet : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::Follow*"
 * @param {cocos2d::Node*}
 * @param {cocos2d::Rect}
 */
create : function () {},

/**
 * @method Follow
 * @constructor
 */
Follow : function () {},

};

/**
 * @class GLProgram
 */
cc.GLProgram = {

/**
 * @method fragmentShaderLog
 * @return A value converted from C/C++ "const char*"
 */
fragmentShaderLog : function () {},

/**
 * @method addAttribute
 * @param {const char*}
 * @param {unsigned int}
 */
addAttribute : function () {},

/**
 * @method setUniformLocationWithMatrix4fv
 * @param {int}
 * @param {float*}
 * @param {unsigned int}
 */
setUniformLocationWithMatrix4fv : function () {},

/**
 * @method getUniformLocationForName
 * @return A value converted from C/C++ "int"
 * @param {const char*}
 */
getUniformLocationForName : function () {},

/**
 * @method use
 */
use : function () {},

/**
 * @method vertexShaderLog
 * @return A value converted from C/C++ "const char*"
 */
vertexShaderLog : function () {},

/**
 * @method initWithVertexShaderByteArray
 * @return A value converted from C/C++ "bool"
 * @param {const char*}
 * @param {const char*}
 */
initWithVertexShaderByteArray : function () {},

/**
 * @method initWithVertexShaderFilename
 * @return A value converted from C/C++ "bool"
 * @param {const char*}
 * @param {const char*}
 */
initWithVertexShaderFilename : function () {},

/**
 * @method setUniformsForBuiltins
 */
setUniformsForBuiltins : function () {},

/**
 * @method setUniformLocationWith3i
 * @param {int}
 * @param {int}
 * @param {int}
 * @param {int}
 */
setUniformLocationWith3i : function () {},

/**
 * @method setUniformLocationWith3iv
 * @param {int}
 * @param {int*}
 * @param {unsigned int}
 */
setUniformLocationWith3iv : function () {},

/**
 * @method updateUniforms
 */
updateUniforms : function () {},

/**
 * @method setUniformLocationWith4iv
 * @param {int}
 * @param {int*}
 * @param {unsigned int}
 */
setUniformLocationWith4iv : function () {},

/**
 * @method link
 * @return A value converted from C/C++ "bool"
 */
link : function () {},

/**
 * @method setUniformLocationWith2iv
 * @param {int}
 * @param {int*}
 * @param {unsigned int}
 */
setUniformLocationWith2iv : function () {},

/**
 * @method reset
 */
reset : function () {},

/**
 * @method setUniformLocationWith4i
 * @param {int}
 * @param {int}
 * @param {int}
 * @param {int}
 * @param {int}
 */
setUniformLocationWith4i : function () {},

/**
 * @method setUniformLocationWith1i
 * @param {int}
 * @param {int}
 */
setUniformLocationWith1i : function () {},

/**
 * @method setUniformLocationWith2i
 * @param {int}
 * @param {int}
 * @param {int}
 */
setUniformLocationWith2i : function () {},

/**
 * @method GLProgram
 * @constructor
 */
GLProgram : function () {},

};

/**
 * @class Touch
 */
cc.Touch = {

/**
 * @method getPreviousLocationInView
 * @return A value converted from C/C++ "cocos2d::Point"
 */
getPreviousLocationInView : function () {},

/**
 * @method getLocation
 * @return A value converted from C/C++ "cocos2d::Point"
 */
getLocation : function () {},

/**
 * @method getDelta
 * @return A value converted from C/C++ "cocos2d::Point"
 */
getDelta : function () {},

/**
 * @method getStartLocationInView
 * @return A value converted from C/C++ "cocos2d::Point"
 */
getStartLocationInView : function () {},

/**
 * @method getStartLocation
 * @return A value converted from C/C++ "cocos2d::Point"
 */
getStartLocation : function () {},

/**
 * @method getID
 * @return A value converted from C/C++ "int"
 */
getID : function () {},

/**
 * @method setTouchInfo
 * @param {int}
 * @param {float}
 * @param {float}
 */
setTouchInfo : function () {},

/**
 * @method getLocationInView
 * @return A value converted from C/C++ "cocos2d::Point"
 */
getLocationInView : function () {},

/**
 * @method getPreviousLocation
 * @return A value converted from C/C++ "cocos2d::Point"
 */
getPreviousLocation : function () {},

/**
 * @method Touch
 * @constructor
 */
Touch : function () {},

};

/**
 * @class Set
 */
cc.Set = {

/**
 * @method count
 * @return A value converted from C/C++ "int"
 */
count : function () {},

/**
 * @method addObject
 * @param {cocos2d::Object*}
 */
addObject : function () {},

/**
 * @method mutableCopy
 * @return A value converted from C/C++ "cocos2d::Set*"
 */
mutableCopy : function () {},

/**
 * @method anyObject
 * @return A value converted from C/C++ "cocos2d::Object*"
 */
anyObject : function () {},

/**
 * @method removeAllObjects
 */
removeAllObjects : function () {},

/**
 * @method removeObject
 * @param {cocos2d::Object*}
 */
removeObject : function () {},

/**
 * @method copy
 * @return A value converted from C/C++ "cocos2d::Set*"
 */
copy : function () {},

/**
 * @method containsObject
 * @return A value converted from C/C++ "bool"
 * @param {cocos2d::Object*}
 */
containsObject : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::Set*"
 */
create : function () {},

};

/**
 * @class Texture2D
 */
cc.Texture2D = {

/**
 * @method getShaderProgram
 * @return A value converted from C/C++ "cocos2d::GLProgram*"
 */
getShaderProgram : function () {},

/**
 * @method getMaxT
 * @return A value converted from C/C++ "float"
 */
getMaxT : function () {},

/**
 * @method getStringForFormat
 * @return A value converted from C/C++ "const char*"
 */
getStringForFormat : function () {},

/**
 * @method setShaderProgram
 * @param {cocos2d::GLProgram*}
 */
setShaderProgram : function () {},

/**
 * @method getMaxS
 * @return A value converted from C/C++ "float"
 */
getMaxS : function () {},

/**
 * @method hasPremultipliedAlpha
 * @return A value converted from C/C++ "bool"
 */
hasPremultipliedAlpha : function () {},

/**
 * @method getPixelsHigh
 * @return A value converted from C/C++ "unsigned int"
 */
getPixelsHigh : function () {},

/**
 * @method initWithMipmaps
 * @return A value converted from C/C++ "bool"
 * @param {MipmapInfo*}
 * @param {int}
 * @param {cocos2d::Texture2D::PixelFormat}
 * @param {unsigned int}
 * @param {unsigned int}
 */
initWithMipmaps : function () {},

/**
 * @method getName
 * @return A value converted from C/C++ "unsigned int"
 */
getName : function () {},

/**
 * @method setMaxT
 * @param {float}
 */
setMaxT : function () {},

/**
 * @method drawInRect
 * @param {cocos2d::Rect}
 */
drawInRect : function () {},

/**
 * @method getContentSize
 * @return A value converted from C/C++ "cocos2d::Size"
 */
getContentSize : function () {},

/**
 * @method setAliasTexParameters
 */
setAliasTexParameters : function () {},

/**
 * @method setAntiAliasTexParameters
 */
setAntiAliasTexParameters : function () {},

/**
 * @method generateMipmap
 */
generateMipmap : function () {},

/**
 * @method getPixelFormat
 * @return A value converted from C/C++ "cocos2d::Texture2D::PixelFormat"
 */
getPixelFormat : function () {},

/**
 * @method getContentSizeInPixels
 * @return A value converted from C/C++ "cocos2d::Size"
 */
getContentSizeInPixels : function () {},

/**
 * @method getPixelsWide
 * @return A value converted from C/C++ "unsigned int"
 */
getPixelsWide : function () {},

/**
 * @method drawAtPoint
 * @param {cocos2d::Point}
 */
drawAtPoint : function () {},

/**
 * @method hasMipmaps
 * @return A value converted from C/C++ "bool"
 */
hasMipmaps : function () {},

/**
 * @method setMaxS
 * @param {float}
 */
setMaxS : function () {},

/**
 * @method setDefaultAlphaPixelFormat
 * @param {cocos2d::Texture2D::PixelFormat}
 */
setDefaultAlphaPixelFormat : function () {},

/**
 * @method getPixelFormatInfoMap
 * @return A value converted from C/C++ "cocos2d::Texture2D::PixelFormatInfoMap"
 */
getPixelFormatInfoMap : function () {},

/**
 * @method getDefaultAlphaPixelFormat
 * @return A value converted from C/C++ "cocos2d::Texture2D::PixelFormat"
 */
getDefaultAlphaPixelFormat : function () {},

/**
 * @method PVRImagesHavePremultipliedAlpha
 * @param {bool}
 */
PVRImagesHavePremultipliedAlpha : function () {},

/**
 * @method Texture2D
 * @constructor
 */
Texture2D : function () {},

};

/**
 * @class Node
 */
cc.Node = {

/**
 * @method removeComponent
 * @return A value converted from C/C++ "bool"
 * @param {const char*}
 */
removeComponent : function () {},

/**
 * @method convertToWorldSpaceAR
 * @return A value converted from C/C++ "cocos2d::Point"
 * @param {cocos2d::Point}
 */
convertToWorldSpaceAR : function () {},

/**
 * @method isIgnoreAnchorPointForPosition
 * @return A value converted from C/C++ "bool"
 */
isIgnoreAnchorPointForPosition : function () {},

/**
 * @method init
 * @return A value converted from C/C++ "bool"
 */
init : function () {},

/**
 * @method setRotation
 * @param {float}
 */
setRotation : function () {},

/**
 * @method setZOrder
 * @param {int}
 */
setZOrder : function () {},

/**
 * @method setScaleY
 * @param {float}
 */
setScaleY : function () {},

/**
 * @method setScaleX
 * @param {float}
 */
setScaleX : function () {},

/**
 * @method removeAllComponents
 */
removeAllComponents : function () {},

/**
 * @method getTag
 * @return A value converted from C/C++ "int"
 */
getTag : function () {},

/**
 * @method getNodeToWorldTransform
 * @return A value converted from C/C++ "cocos2d::AffineTransform"
 */
getNodeToWorldTransform : function () {},

/**
 * @method removeChild
 * @param {cocos2d::Node*}
 * @param {bool}
 */
removeChild : function () {},

/**
 * @method convertToWorldSpace
 * @return A value converted from C/C++ "cocos2d::Point"
 * @param {cocos2d::Point}
 */
convertToWorldSpace : function () {},

/**
 * @method setSkewX
 * @param {float}
 */
setSkewX : function () {},

/**
 * @method setSkewY
 * @param {float}
 */
setSkewY : function () {},

/**
 * @method convertTouchToNodeSpace
 * @return A value converted from C/C++ "cocos2d::Point"
 * @param {cocos2d::Touch*}
 */
convertTouchToNodeSpace : function () {},

/**
 * @method getRotationX
 * @return A value converted from C/C++ "float"
 */
getRotationX : function () {},

/**
 * @method getRotationY
 * @return A value converted from C/C++ "float"
 */
getRotationY : function () {},

/**
 * @method setParent
 * @param {cocos2d::Node*}
 */
setParent : function () {},

/**
 * @method getNodeToParentTransform
 * @return A value converted from C/C++ "cocos2d::AffineTransform"
 */
getNodeToParentTransform : function () {},

/**
 * @method convertToNodeSpace
 * @return A value converted from C/C++ "cocos2d::Point"
 * @param {cocos2d::Point}
 */
convertToNodeSpace : function () {},

/**
 * @method stopActionByTag
 * @param {int}
 */
stopActionByTag : function () {},

/**
 * @method reorderChild
 * @param {cocos2d::Node*}
 * @param {int}
 */
reorderChild : function () {},

/**
 * @method ignoreAnchorPointForPosition
 * @param {bool}
 */
ignoreAnchorPointForPosition : function () {},

/**
 * @method setPositionY
 * @param {float}
 */
setPositionY : function () {},

/**
 * @method setPositionX
 * @param {float}
 */
setPositionX : function () {},

/**
 * @method getAnchorPoint
 * @return A value converted from C/C++ "cocos2d::Point"
 */
getAnchorPoint : function () {},

/**
 * @method getNumberOfRunningActions
 * @return A value converted from C/C++ "unsigned int"
 */
getNumberOfRunningActions : function () {},

/**
 * @method updateTransform
 */
updateTransform : function () {},

/**
 * @method isVisible
 * @return A value converted from C/C++ "bool"
 */
isVisible : function () {},

/**
 * @method getChildrenCount
 * @return A value converted from C/C++ "unsigned int"
 */
getChildrenCount : function () {},

/**
 * @method setAnchorPoint
 * @param {cocos2d::Point}
 */
setAnchorPoint : function () {},

/**
 * @method convertToNodeSpaceAR
 * @return A value converted from C/C++ "cocos2d::Point"
 * @param {cocos2d::Point}
 */
convertToNodeSpaceAR : function () {},

/**
 * @method addComponent
 * @return A value converted from C/C++ "bool"
 * @param {cocos2d::Component*}
 */
addComponent : function () {},

/**
 * @method visit
 */
visit : function () {},

/**
 * @method setShaderProgram
 * @param {cocos2d::GLProgram*}
 */
setShaderProgram : function () {},

/**
 * @method getRotation
 * @return A value converted from C/C++ "float"
 */
getRotation : function () {},

/**
 * @method resumeSchedulerAndActions
 */
resumeSchedulerAndActions : function () {},

/**
 * @method getZOrder
 * @return A value converted from C/C++ "int"
 */
getZOrder : function () {},

/**
 * @method getAnchorPointInPoints
 * @return A value converted from C/C++ "cocos2d::Point"
 */
getAnchorPointInPoints : function () {},

/**
 * @method runAction
 * @return A value converted from C/C++ "cocos2d::Action*"
 * @param {cocos2d::Action*}
 */
runAction : function () {},

/**
 * @method transform
 */
transform : function () {},

/**
 * @method setVertexZ
 * @param {float}
 */
setVertexZ : function () {},

/**
 * @method setScheduler
 * @param {cocos2d::Scheduler*}
 */
setScheduler : function () {},

/**
 * @method stopAllActions
 */
stopAllActions : function () {},

/**
 * @method getSkewX
 * @return A value converted from C/C++ "float"
 */
getSkewX : function () {},

/**
 * @method getSkewY
 * @return A value converted from C/C++ "float"
 */
getSkewY : function () {},

/**
 * @method getActionByTag
 * @return A value converted from C/C++ "cocos2d::Action*"
 * @param {int}
 */
getActionByTag : function () {},

/**
 * @method setRotationX
 * @param {float}
 */
setRotationX : function () {},

/**
 * @method setRotationY
 * @param {float}
 */
setRotationY : function () {},

/**
 * @method setAdditionalTransform
 * @param {cocos2d::AffineTransform}
 */
setAdditionalTransform : function () {},

/**
 * @method getOrderOfArrival
 * @return A value converted from C/C++ "int"
 */
getOrderOfArrival : function () {},

/**
 * @method setContentSize
 * @param {cocos2d::Size}
 */
setContentSize : function () {},

/**
 * @method setActionManager
 * @param {cocos2d::ActionManager*}
 */
setActionManager : function () {},

/**
 * @method isRunning
 * @return A value converted from C/C++ "bool"
 */
isRunning : function () {},

/**
 * @method getPositionY
 * @return A value converted from C/C++ "float"
 */
getPositionY : function () {},

/**
 * @method getPositionX
 * @return A value converted from C/C++ "float"
 */
getPositionX : function () {},

/**
 * @method removeChildByTag
 * @param {int}
 * @param {bool}
 */
removeChildByTag : function () {},

/**
 * @method setVisible
 * @param {bool}
 */
setVisible : function () {},

/**
 * @method getParentToNodeTransform
 * @return A value converted from C/C++ "cocos2d::AffineTransform"
 */
getParentToNodeTransform : function () {},

/**
 * @method pauseSchedulerAndActions
 */
pauseSchedulerAndActions : function () {},

/**
 * @method getVertexZ
 * @return A value converted from C/C++ "float"
 */
getVertexZ : function () {},

/**
 * @method _setZOrder
 * @param {int}
 */
_setZOrder : function () {},

/**
 * @method setScale
 * @param {float}
 */
setScale : function () {},

/**
 * @method getChildByTag
 * @return A value converted from C/C++ "cocos2d::Node*"
 * @param {int}
 */
getChildByTag : function () {},

/**
 * @method setOrderOfArrival
 * @param {int}
 */
setOrderOfArrival : function () {},

/**
 * @method getScaleY
 * @return A value converted from C/C++ "float"
 */
getScaleY : function () {},

/**
 * @method getScaleX
 * @return A value converted from C/C++ "float"
 */
getScaleX : function () {},

/**
 * @method cleanup
 */
cleanup : function () {},

/**
 * @method getComponent
 * @return A value converted from C/C++ "cocos2d::Component*"
 * @param {const char*}
 */
getComponent : function () {},

/**
 * @method getContentSize
 * @return A value converted from C/C++ "cocos2d::Size"
 */
getContentSize : function () {},

/**
 * @method setGrid
 * @param {cocos2d::GridBase*}
 */
setGrid : function () {},

/**
 * @method getBoundingBox
 * @return A value converted from C/C++ "cocos2d::Rect"
 */
getBoundingBox : function () {},

/**
 * @method draw
 */
draw : function () {},

/**
 * @method transformAncestors
 */
transformAncestors : function () {},

/**
 * @method setUserObject
 * @param {cocos2d::Object*}
 */
setUserObject : function () {},

/**
 * @method convertTouchToNodeSpaceAR
 * @return A value converted from C/C++ "cocos2d::Point"
 * @param {cocos2d::Touch*}
 */
convertTouchToNodeSpaceAR : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method sortAllChildren
 */
sortAllChildren : function () {},

/**
 * @method getWorldToNodeTransform
 * @return A value converted from C/C++ "cocos2d::AffineTransform"
 */
getWorldToNodeTransform : function () {},

/**
 * @method getScale
 * @return A value converted from C/C++ "float"
 */
getScale : function () {},

/**
 * @method getCamera
 * @return A value converted from C/C++ "cocos2d::Camera*"
 */
getCamera : function () {},

/**
 * @method setTag
 * @param {int}
 */
setTag : function () {},

/**
 * @method stopAction
 * @param {cocos2d::Action*}
 */
stopAction : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::Node*"
 */
create : function () {},

/**
 * @method Node
 * @constructor
 */
Node : function () {},

};

/**
 * @class NodeRGBA
 */
cc.NodeRGBA = {

/**
 * @method updateDisplayedColor
 * @param {cocos2d::Color3B}
 */
updateDisplayedColor : function () {},

/**
 * @method setColor
 * @param {cocos2d::Color3B}
 */
setColor : function () {},

/**
 * @method isCascadeOpacityEnabled
 * @return A value converted from C/C++ "bool"
 */
isCascadeOpacityEnabled : function () {},

/**
 * @method getColor
 * @return A value converted from C/C++ "cocos2d::Color3B"
 */
getColor : function () {},

/**
 * @method getDisplayedOpacity
 * @return A value converted from C/C++ "unsigned char"
 */
getDisplayedOpacity : function () {},

/**
 * @method setCascadeColorEnabled
 * @param {bool}
 */
setCascadeColorEnabled : function () {},

/**
 * @method setOpacity
 * @param {unsigned char}
 */
setOpacity : function () {},

/**
 * @method setOpacityModifyRGB
 * @param {bool}
 */
setOpacityModifyRGB : function () {},

/**
 * @method setCascadeOpacityEnabled
 * @param {bool}
 */
setCascadeOpacityEnabled : function () {},

/**
 * @method updateDisplayedOpacity
 * @param {unsigned char}
 */
updateDisplayedOpacity : function () {},

/**
 * @method init
 * @return A value converted from C/C++ "bool"
 */
init : function () {},

/**
 * @method getOpacity
 * @return A value converted from C/C++ "unsigned char"
 */
getOpacity : function () {},

/**
 * @method isOpacityModifyRGB
 * @return A value converted from C/C++ "bool"
 */
isOpacityModifyRGB : function () {},

/**
 * @method isCascadeColorEnabled
 * @return A value converted from C/C++ "bool"
 */
isCascadeColorEnabled : function () {},

/**
 * @method getDisplayedColor
 * @return A value converted from C/C++ "cocos2d::Color3B"
 */
getDisplayedColor : function () {},

/**
 * @method NodeRGBA
 * @constructor
 */
NodeRGBA : function () {},

};

/**
 * @class SpriteFrame
 */
cc.SpriteFrame = {

/**
 * @method clone
 * @return A value converted from C/C++ "cocos2d::SpriteFrame*"
 */
clone : function () {},

/**
 * @method setRotated
 * @param {bool}
 */
setRotated : function () {},

/**
 * @method setTexture
 * @param {cocos2d::Texture2D*}
 */
setTexture : function () {},

/**
 * @method setRectInPixels
 * @param {cocos2d::Rect}
 */
setRectInPixels : function () {},

/**
 * @method getTexture
 * @return A value converted from C/C++ "cocos2d::Texture2D*"
 */
getTexture : function () {},

/**
 * @method getRect
 * @return A value converted from C/C++ "cocos2d::Rect"
 */
getRect : function () {},

/**
 * @method setOffsetInPixels
 * @param {cocos2d::Point}
 */
setOffsetInPixels : function () {},

/**
 * @method getRectInPixels
 * @return A value converted from C/C++ "cocos2d::Rect"
 */
getRectInPixels : function () {},

/**
 * @method setOriginalSize
 * @param {cocos2d::Size}
 */
setOriginalSize : function () {},

/**
 * @method getOriginalSizeInPixels
 * @return A value converted from C/C++ "cocos2d::Size"
 */
getOriginalSizeInPixels : function () {},

/**
 * @method setOriginalSizeInPixels
 * @param {cocos2d::Size}
 */
setOriginalSizeInPixels : function () {},

/**
 * @method setOffset
 * @param {cocos2d::Point}
 */
setOffset : function () {},

/**
 * @method getOffset
 * @return A value converted from C/C++ "cocos2d::Point"
 */
getOffset : function () {},

/**
 * @method isRotated
 * @return A value converted from C/C++ "bool"
 */
isRotated : function () {},

/**
 * @method setRect
 * @param {cocos2d::Rect}
 */
setRect : function () {},

/**
 * @method getOffsetInPixels
 * @return A value converted from C/C++ "cocos2d::Point"
 */
getOffsetInPixels : function () {},

/**
 * @method getOriginalSize
 * @return A value converted from C/C++ "cocos2d::Size"
 */
getOriginalSize : function () {},

};

/**
 * @class AnimationFrame
 */
cc.AnimationFrame = {

/**
 * @method setSpriteFrame
 * @param {cocos2d::SpriteFrame*}
 */
setSpriteFrame : function () {},

/**
 * @method getUserInfo
 * @return A value converted from C/C++ "cocos2d::Dictionary*"
 */
getUserInfo : function () {},

/**
 * @method setDelayUnits
 * @param {float}
 */
setDelayUnits : function () {},

/**
 * @method clone
 * @return A value converted from C/C++ "cocos2d::AnimationFrame*"
 */
clone : function () {},

/**
 * @method getSpriteFrame
 * @return A value converted from C/C++ "cocos2d::SpriteFrame*"
 */
getSpriteFrame : function () {},

/**
 * @method getDelayUnits
 * @return A value converted from C/C++ "float"
 */
getDelayUnits : function () {},

/**
 * @method setUserInfo
 * @param {cocos2d::Dictionary*}
 */
setUserInfo : function () {},

/**
 * @method initWithSpriteFrame
 * @return A value converted from C/C++ "bool"
 * @param {cocos2d::SpriteFrame*}
 * @param {float}
 * @param {cocos2d::Dictionary*}
 */
initWithSpriteFrame : function () {},

/**
 * @method AnimationFrame
 * @constructor
 */
AnimationFrame : function () {},

};

/**
 * @class Animation
 */
cc.Animation = {

/**
 * @method getLoops
 * @return A value converted from C/C++ "unsigned int"
 */
getLoops : function () {},

/**
 * @method setFrames
 * @param {cocos2d::Array*}
 */
setFrames : function () {},

/**
 * @method getFrames
 * @return A value converted from C/C++ "cocos2d::Array*"
 */
getFrames : function () {},

/**
 * @method addSpriteFrame
 * @param {cocos2d::SpriteFrame*}
 */
addSpriteFrame : function () {},

/**
 * @method setRestoreOriginalFrame
 * @param {bool}
 */
setRestoreOriginalFrame : function () {},

/**
 * @method clone
 * @return A value converted from C/C++ "cocos2d::Animation*"
 */
clone : function () {},

/**
 * @method setDelayPerUnit
 * @param {float}
 */
setDelayPerUnit : function () {},

/**
 * @method initWithAnimationFrames
 * @return A value converted from C/C++ "bool"
 * @param {cocos2d::Array*}
 * @param {float}
 * @param {unsigned int}
 */
initWithAnimationFrames : function () {},

/**
 * @method init
 * @return A value converted from C/C++ "bool"
 */
init : function () {},

/**
 * @method initWithSpriteFrames
 * @return A value converted from C/C++ "bool"
 * @param {cocos2d::Array*}
 * @param {float}
 */
initWithSpriteFrames : function () {},

/**
 * @method setLoops
 * @param {unsigned int}
 */
setLoops : function () {},

/**
 * @method addSpriteFrameWithFileName
 * @param {const char*}
 */
addSpriteFrameWithFileName : function () {},

/**
 * @method getTotalDelayUnits
 * @return A value converted from C/C++ "float"
 */
getTotalDelayUnits : function () {},

/**
 * @method getDelayPerUnit
 * @return A value converted from C/C++ "float"
 */
getDelayPerUnit : function () {},

/**
 * @method getRestoreOriginalFrame
 * @return A value converted from C/C++ "bool"
 */
getRestoreOriginalFrame : function () {},

/**
 * @method getDuration
 * @return A value converted from C/C++ "float"
 */
getDuration : function () {},

/**
 * @method addSpriteFrameWithTexture
 * @param {cocos2d::Texture2D*}
 * @param {cocos2d::Rect}
 */
addSpriteFrameWithTexture : function () {},

/**
 * @method createWithSpriteFrames
 * @return A value converted from C/C++ "cocos2d::Animation*"
 * @param {cocos2d::Array*}
 * @param {float}
 */
createWithSpriteFrames : function () {},

/**
 * @method Animation
 * @constructor
 */
Animation : function () {},

};

/**
 * @class ActionInterval
 */
cc.ActionInterval = {

/**
 * @method startWithTarget
 * @param {cocos2d::Node*}
 */
startWithTarget : function () {},

/**
 * @method setAmplitudeRate
 * @param {float}
 */
setAmplitudeRate : function () {},

/**
 * @method initWithDuration
 * @return A value converted from C/C++ "bool"
 * @param {float}
 */
initWithDuration : function () {},

/**
 * @method clone
 * @return A value converted from C/C++ "cocos2d::ActionInterval*"
 */
clone : function () {},

/**
 * @method getAmplitudeRate
 * @return A value converted from C/C++ "float"
 */
getAmplitudeRate : function () {},

/**
 * @method step
 * @param {float}
 */
step : function () {},

/**
 * @method getElapsed
 * @return A value converted from C/C++ "float"
 */
getElapsed : function () {},

/**
 * @method isDone
 * @return A value converted from C/C++ "bool"
 */
isDone : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::ActionInterval*"
 */
reverse : function () {},

};

/**
 * @class Sequence
 */
cc.Sequence = {

/**
 * @method startWithTarget
 * @param {cocos2d::Node*}
 */
startWithTarget : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::Sequence*"
 */
reverse : function () {},

/**
 * @method clone
 * @return A value converted from C/C++ "cocos2d::Sequence*"
 */
clone : function () {},

/**
 * @method stop
 */
stop : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method initWithTwoActions
 * @return A value converted from C/C++ "bool"
 * @param {cocos2d::FiniteTimeAction*}
 * @param {cocos2d::FiniteTimeAction*}
 */
initWithTwoActions : function () {},

};

/**
 * @class Repeat
 */
cc.Repeat = {

/**
 * @method setInnerAction
 * @param {cocos2d::FiniteTimeAction*}
 */
setInnerAction : function () {},

/**
 * @method startWithTarget
 * @param {cocos2d::Node*}
 */
startWithTarget : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::Repeat*"
 */
reverse : function () {},

/**
 * @method clone
 * @return A value converted from C/C++ "cocos2d::Repeat*"
 */
clone : function () {},

/**
 * @method stop
 */
stop : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method initWithAction
 * @return A value converted from C/C++ "bool"
 * @param {cocos2d::FiniteTimeAction*}
 * @param {unsigned int}
 */
initWithAction : function () {},

/**
 * @method getInnerAction
 * @return A value converted from C/C++ "cocos2d::FiniteTimeAction*"
 */
getInnerAction : function () {},

/**
 * @method isDone
 * @return A value converted from C/C++ "bool"
 */
isDone : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::Repeat*"
 * @param {cocos2d::FiniteTimeAction*}
 * @param {unsigned int}
 */
create : function () {},

};

/**
 * @class RepeatForever
 */
cc.RepeatForever = {

/**
 * @method setInnerAction
 * @param {cocos2d::ActionInterval*}
 */
setInnerAction : function () {},

/**
 * @method startWithTarget
 * @param {cocos2d::Node*}
 */
startWithTarget : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::RepeatForever*"
 */
reverse : function () {},

/**
 * @method clone
 * @return A value converted from C/C++ "cocos2d::RepeatForever*"
 */
clone : function () {},

/**
 * @method step
 * @param {float}
 */
step : function () {},

/**
 * @method initWithAction
 * @return A value converted from C/C++ "bool"
 * @param {cocos2d::ActionInterval*}
 */
initWithAction : function () {},

/**
 * @method getInnerAction
 * @return A value converted from C/C++ "cocos2d::ActionInterval*"
 */
getInnerAction : function () {},

/**
 * @method isDone
 * @return A value converted from C/C++ "bool"
 */
isDone : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::RepeatForever*"
 * @param {cocos2d::ActionInterval*}
 */
create : function () {},

/**
 * @method RepeatForever
 * @constructor
 */
RepeatForever : function () {},

};

/**
 * @class Spawn
 */
cc.Spawn = {

/**
 * @method startWithTarget
 * @param {cocos2d::Node*}
 */
startWithTarget : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::Spawn*"
 */
reverse : function () {},

/**
 * @method clone
 * @return A value converted from C/C++ "cocos2d::Spawn*"
 */
clone : function () {},

/**
 * @method stop
 */
stop : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method initWithTwoActions
 * @return A value converted from C/C++ "bool"
 * @param {cocos2d::FiniteTimeAction*}
 * @param {cocos2d::FiniteTimeAction*}
 */
initWithTwoActions : function () {},

};

/**
 * @class RotateTo
 */
cc.RotateTo = {

/**
 * @method startWithTarget
 * @param {cocos2d::Node*}
 */
startWithTarget : function () {},

/**
 * @method clone
 * @return A value converted from C/C++ "cocos2d::RotateTo*"
 */
clone : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::RotateTo*"
 */
reverse : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

};

/**
 * @class RotateBy
 */
cc.RotateBy = {

/**
 * @method startWithTarget
 * @param {cocos2d::Node*}
 */
startWithTarget : function () {},

/**
 * @method clone
 * @return A value converted from C/C++ "cocos2d::RotateBy*"
 */
clone : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::RotateBy*"
 */
reverse : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

};

/**
 * @class MoveBy
 */
cc.MoveBy = {

/**
 * @method startWithTarget
 * @param {cocos2d::Node*}
 */
startWithTarget : function () {},

/**
 * @method clone
 * @return A value converted from C/C++ "cocos2d::MoveBy*"
 */
clone : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::MoveBy*"
 */
reverse : function () {},

/**
 * @method initWithDuration
 * @return A value converted from C/C++ "bool"
 * @param {float}
 * @param {cocos2d::Point}
 */
initWithDuration : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::MoveBy*"
 * @param {float}
 * @param {cocos2d::Point}
 */
create : function () {},

};

/**
 * @class MoveTo
 */
cc.MoveTo = {

/**
 * @method startWithTarget
 * @param {cocos2d::Node*}
 */
startWithTarget : function () {},

/**
 * @method clone
 * @return A value converted from C/C++ "cocos2d::MoveTo*"
 */
clone : function () {},

/**
 * @method initWithDuration
 * @return A value converted from C/C++ "bool"
 * @param {float}
 * @param {cocos2d::Point}
 */
initWithDuration : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::MoveTo*"
 * @param {float}
 * @param {cocos2d::Point}
 */
create : function () {},

};

/**
 * @class SkewTo
 */
cc.SkewTo = {

/**
 * @method startWithTarget
 * @param {cocos2d::Node*}
 */
startWithTarget : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::SkewTo*"
 */
reverse : function () {},

/**
 * @method initWithDuration
 * @return A value converted from C/C++ "bool"
 * @param {float}
 * @param {float}
 * @param {float}
 */
initWithDuration : function () {},

/**
 * @method clone
 * @return A value converted from C/C++ "cocos2d::SkewTo*"
 */
clone : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::SkewTo*"
 * @param {float}
 * @param {float}
 * @param {float}
 */
create : function () {},

/**
 * @method SkewTo
 * @constructor
 */
SkewTo : function () {},

};

/**
 * @class SkewBy
 */
cc.SkewBy = {

/**
 * @method startWithTarget
 * @param {cocos2d::Node*}
 */
startWithTarget : function () {},

/**
 * @method clone
 * @return A value converted from C/C++ "cocos2d::SkewBy*"
 */
clone : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::SkewBy*"
 */
reverse : function () {},

/**
 * @method initWithDuration
 * @return A value converted from C/C++ "bool"
 * @param {float}
 * @param {float}
 * @param {float}
 */
initWithDuration : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::SkewBy*"
 * @param {float}
 * @param {float}
 * @param {float}
 */
create : function () {},

};

/**
 * @class JumpBy
 */
cc.JumpBy = {

/**
 * @method startWithTarget
 * @param {cocos2d::Node*}
 */
startWithTarget : function () {},

/**
 * @method clone
 * @return A value converted from C/C++ "cocos2d::JumpBy*"
 */
clone : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::JumpBy*"
 */
reverse : function () {},

/**
 * @method initWithDuration
 * @return A value converted from C/C++ "bool"
 * @param {float}
 * @param {cocos2d::Point}
 * @param {float}
 * @param {int}
 */
initWithDuration : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::JumpBy*"
 * @param {float}
 * @param {cocos2d::Point}
 * @param {float}
 * @param {int}
 */
create : function () {},

};

/**
 * @class JumpTo
 */
cc.JumpTo = {

/**
 * @method startWithTarget
 * @param {cocos2d::Node*}
 */
startWithTarget : function () {},

/**
 * @method clone
 * @return A value converted from C/C++ "cocos2d::JumpTo*"
 */
clone : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::JumpTo*"
 */
reverse : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::JumpTo*"
 * @param {float}
 * @param {cocos2d::Point}
 * @param {float}
 * @param {int}
 */
create : function () {},

};

/**
 * @class BezierBy
 */
cc.BezierBy = {

/**
 * @method startWithTarget
 * @param {cocos2d::Node*}
 */
startWithTarget : function () {},

/**
 * @method clone
 * @return A value converted from C/C++ "cocos2d::BezierBy*"
 */
clone : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::BezierBy*"
 */
reverse : function () {},

/**
 * @method initWithDuration
 * @return A value converted from C/C++ "bool"
 * @param {float}
 * @param {cocos2d::ccBezierConfig}
 */
initWithDuration : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

};

/**
 * @class BezierTo
 */
cc.BezierTo = {

/**
 * @method startWithTarget
 * @param {cocos2d::Node*}
 */
startWithTarget : function () {},

/**
 * @method clone
 * @return A value converted from C/C++ "cocos2d::BezierTo*"
 */
clone : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::BezierTo*"
 */
reverse : function () {},

/**
 * @method initWithDuration
 * @return A value converted from C/C++ "bool"
 * @param {float}
 * @param {cocos2d::ccBezierConfig}
 */
initWithDuration : function () {},

};

/**
 * @class ScaleTo
 */
cc.ScaleTo = {

/**
 * @method startWithTarget
 * @param {cocos2d::Node*}
 */
startWithTarget : function () {},

/**
 * @method clone
 * @return A value converted from C/C++ "cocos2d::ScaleTo*"
 */
clone : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::ScaleTo*"
 */
reverse : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

};

/**
 * @class ScaleBy
 */
cc.ScaleBy = {

/**
 * @method startWithTarget
 * @param {cocos2d::Node*}
 */
startWithTarget : function () {},

/**
 * @method clone
 * @return A value converted from C/C++ "cocos2d::ScaleBy*"
 */
clone : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::ScaleBy*"
 */
reverse : function () {},

};

/**
 * @class Blink
 */
cc.Blink = {

/**
 * @method startWithTarget
 * @param {cocos2d::Node*}
 */
startWithTarget : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::Blink*"
 */
reverse : function () {},

/**
 * @method initWithDuration
 * @return A value converted from C/C++ "bool"
 * @param {float}
 * @param {int}
 */
initWithDuration : function () {},

/**
 * @method clone
 * @return A value converted from C/C++ "cocos2d::Blink*"
 */
clone : function () {},

/**
 * @method stop
 */
stop : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::Blink*"
 * @param {float}
 * @param {int}
 */
create : function () {},

};

/**
 * @class FadeIn
 */
cc.FadeIn = {

/**
 * @method clone
 * @return A value converted from C/C++ "cocos2d::FadeIn*"
 */
clone : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::ActionInterval*"
 */
reverse : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::FadeIn*"
 * @param {float}
 */
create : function () {},

};

/**
 * @class FadeOut
 */
cc.FadeOut = {

/**
 * @method clone
 * @return A value converted from C/C++ "cocos2d::FadeOut*"
 */
clone : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::ActionInterval*"
 */
reverse : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::FadeOut*"
 * @param {float}
 */
create : function () {},

};

/**
 * @class FadeTo
 */
cc.FadeTo = {

/**
 * @method startWithTarget
 * @param {cocos2d::Node*}
 */
startWithTarget : function () {},

/**
 * @method clone
 * @return A value converted from C/C++ "cocos2d::FadeTo*"
 */
clone : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::FadeTo*"
 */
reverse : function () {},

/**
 * @method initWithDuration
 * @return A value converted from C/C++ "bool"
 * @param {float}
 * @param {unsigned char}
 */
initWithDuration : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::FadeTo*"
 * @param {float}
 * @param {unsigned char}
 */
create : function () {},

};

/**
 * @class TintTo
 */
cc.TintTo = {

/**
 * @method startWithTarget
 * @param {cocos2d::Node*}
 */
startWithTarget : function () {},

/**
 * @method clone
 * @return A value converted from C/C++ "cocos2d::TintTo*"
 */
clone : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::TintTo*"
 */
reverse : function () {},

/**
 * @method initWithDuration
 * @return A value converted from C/C++ "bool"
 * @param {float}
 * @param {unsigned char}
 * @param {unsigned char}
 * @param {unsigned char}
 */
initWithDuration : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::TintTo*"
 * @param {float}
 * @param {unsigned char}
 * @param {unsigned char}
 * @param {unsigned char}
 */
create : function () {},

};

/**
 * @class TintBy
 */
cc.TintBy = {

/**
 * @method startWithTarget
 * @param {cocos2d::Node*}
 */
startWithTarget : function () {},

/**
 * @method clone
 * @return A value converted from C/C++ "cocos2d::TintBy*"
 */
clone : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::TintBy*"
 */
reverse : function () {},

/**
 * @method initWithDuration
 * @return A value converted from C/C++ "bool"
 * @param {float}
 * @param {short}
 * @param {short}
 * @param {short}
 */
initWithDuration : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::TintBy*"
 * @param {float}
 * @param {short}
 * @param {short}
 * @param {short}
 */
create : function () {},

};

/**
 * @class DelayTime
 */
cc.DelayTime = {

/**
 * @method clone
 * @return A value converted from C/C++ "cocos2d::DelayTime*"
 */
clone : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::DelayTime*"
 */
reverse : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::DelayTime*"
 * @param {float}
 */
create : function () {},

};

/**
 * @class Animate
 */
cc.Animate = {

/**
 * @method startWithTarget
 * @param {cocos2d::Node*}
 */
startWithTarget : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::Animate*"
 */
reverse : function () {},

/**
 * @method clone
 * @return A value converted from C/C++ "cocos2d::Animate*"
 */
clone : function () {},

/**
 * @method stop
 */
stop : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method initWithAnimation
 * @return A value converted from C/C++ "bool"
 * @param {cocos2d::Animation*}
 */
initWithAnimation : function () {},

/**
 * @method setAnimation
 * @param {cocos2d::Animation*}
 */
setAnimation : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::Animate*"
 * @param {cocos2d::Animation*}
 */
create : function () {},

/**
 * @method Animate
 * @constructor
 */
Animate : function () {},

};

/**
 * @class TargetedAction
 */
cc.TargetedAction = {

/**
 * @method startWithTarget
 * @param {cocos2d::Node*}
 */
startWithTarget : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::TargetedAction*"
 */
reverse : function () {},

/**
 * @method setForcedTarget
 * @param {cocos2d::Node*}
 */
setForcedTarget : function () {},

/**
 * @method clone
 * @return A value converted from C/C++ "cocos2d::TargetedAction*"
 */
clone : function () {},

/**
 * @method initWithTarget
 * @return A value converted from C/C++ "bool"
 * @param {cocos2d::Node*}
 * @param {cocos2d::FiniteTimeAction*}
 */
initWithTarget : function () {},

/**
 * @method stop
 */
stop : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::TargetedAction*"
 * @param {cocos2d::Node*}
 * @param {cocos2d::FiniteTimeAction*}
 */
create : function () {},

/**
 * @method TargetedAction
 * @constructor
 */
TargetedAction : function () {},

};

/**
 * @class ActionCamera
 */
cc.ActionCamera = {

/**
 * @method startWithTarget
 * @param {cocos2d::Node*}
 */
startWithTarget : function () {},

/**
 * @method clone
 * @return A value converted from C/C++ "cocos2d::ActionCamera*"
 */
clone : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::ActionCamera*"
 */
reverse : function () {},

/**
 * @method ActionCamera
 * @constructor
 */
ActionCamera : function () {},

};

/**
 * @class OrbitCamera
 */
cc.OrbitCamera = {

/**
 * @method startWithTarget
 * @param {cocos2d::Node*}
 */
startWithTarget : function () {},

/**
 * @method initWithDuration
 * @return A value converted from C/C++ "bool"
 * @param {float}
 * @param {float}
 * @param {float}
 * @param {float}
 * @param {float}
 * @param {float}
 * @param {float}
 */
initWithDuration : function () {},

/**
 * @method clone
 * @return A value converted from C/C++ "cocos2d::OrbitCamera*"
 */
clone : function () {},

/**
 * @method sphericalRadius
 * @param {float*}
 * @param {float*}
 * @param {float*}
 */
sphericalRadius : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::OrbitCamera*"
 * @param {float}
 * @param {float}
 * @param {float}
 * @param {float}
 * @param {float}
 * @param {float}
 * @param {float}
 */
create : function () {},

/**
 * @method OrbitCamera
 * @constructor
 */
OrbitCamera : function () {},

};

/**
 * @class ActionManager
 */
cc.ActionManager = {

/**
 * @method getActionByTag
 * @return A value converted from C/C++ "cocos2d::Action*"
 * @param {unsigned int}
 * @param {cocos2d::Object*}
 */
getActionByTag : function () {},

/**
 * @method removeActionByTag
 * @param {unsigned int}
 * @param {cocos2d::Object*}
 */
removeActionByTag : function () {},

/**
 * @method removeAllActions
 */
removeAllActions : function () {},

/**
 * @method addAction
 * @param {cocos2d::Action*}
 * @param {cocos2d::Node*}
 * @param {bool}
 */
addAction : function () {},

/**
 * @method resumeTarget
 * @param {cocos2d::Object*}
 */
resumeTarget : function () {},

/**
 * @method getNumberOfRunningActionsInTarget
 * @return A value converted from C/C++ "unsigned int"
 * @param {cocos2d::Object*}
 */
getNumberOfRunningActionsInTarget : function () {},

/**
 * @method removeAllActionsFromTarget
 * @param {cocos2d::Object*}
 */
removeAllActionsFromTarget : function () {},

/**
 * @method resumeTargets
 * @param {cocos2d::Set*}
 */
resumeTargets : function () {},

/**
 * @method removeAction
 * @param {cocos2d::Action*}
 */
removeAction : function () {},

/**
 * @method pauseTarget
 * @param {cocos2d::Object*}
 */
pauseTarget : function () {},

/**
 * @method pauseAllRunningActions
 * @return A value converted from C/C++ "cocos2d::Set*"
 */
pauseAllRunningActions : function () {},

/**
 * @method ActionManager
 * @constructor
 */
ActionManager : function () {},

};

/**
 * @class ActionEase
 */
cc.ActionEase = {

/**
 * @method startWithTarget
 * @param {cocos2d::Node*}
 */
startWithTarget : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::ActionEase*"
 */
reverse : function () {},

/**
 * @method clone
 * @return A value converted from C/C++ "cocos2d::ActionEase*"
 */
clone : function () {},

/**
 * @method stop
 */
stop : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method initWithAction
 * @return A value converted from C/C++ "bool"
 * @param {cocos2d::ActionInterval*}
 */
initWithAction : function () {},

/**
 * @method getInnerAction
 * @return A value converted from C/C++ "cocos2d::ActionInterval*"
 */
getInnerAction : function () {},

};

/**
 * @class EaseRateAction
 */
cc.EaseRateAction = {

/**
 * @method clone
 * @return A value converted from C/C++ "cocos2d::EaseRateAction*"
 */
clone : function () {},

/**
 * @method setRate
 * @param {float}
 */
setRate : function () {},

/**
 * @method initWithAction
 * @return A value converted from C/C++ "bool"
 * @param {cocos2d::ActionInterval*}
 * @param {float}
 */
initWithAction : function () {},

/**
 * @method getRate
 * @return A value converted from C/C++ "float"
 */
getRate : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::EaseRateAction*"
 */
reverse : function () {},

};

/**
 * @class EaseIn
 */
cc.EaseIn = {

/**
 * @method clone
 * @return A value converted from C/C++ "cocos2d::EaseIn*"
 */
clone : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::EaseIn*"
 */
reverse : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::EaseIn*"
 * @param {cocos2d::ActionInterval*}
 * @param {float}
 */
create : function () {},

};

/**
 * @class EaseOut
 */
cc.EaseOut = {

/**
 * @method clone
 * @return A value converted from C/C++ "cocos2d::EaseOut*"
 */
clone : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::EaseOut*"
 */
reverse : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::EaseOut*"
 * @param {cocos2d::ActionInterval*}
 * @param {float}
 */
create : function () {},

};

/**
 * @class EaseInOut
 */
cc.EaseInOut = {

/**
 * @method clone
 * @return A value converted from C/C++ "cocos2d::EaseInOut*"
 */
clone : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::EaseInOut*"
 */
reverse : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::EaseInOut*"
 * @param {cocos2d::ActionInterval*}
 * @param {float}
 */
create : function () {},

};

/**
 * @class EaseExponentialIn
 */
cc.EaseExponentialIn = {

/**
 * @method clone
 * @return A value converted from C/C++ "cocos2d::EaseExponentialIn*"
 */
clone : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::ActionEase*"
 */
reverse : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::EaseExponentialIn*"
 * @param {cocos2d::ActionInterval*}
 */
create : function () {},

};

/**
 * @class EaseExponentialOut
 */
cc.EaseExponentialOut = {

/**
 * @method clone
 * @return A value converted from C/C++ "cocos2d::EaseExponentialOut*"
 */
clone : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::ActionEase*"
 */
reverse : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::EaseExponentialOut*"
 * @param {cocos2d::ActionInterval*}
 */
create : function () {},

};

/**
 * @class EaseExponentialInOut
 */
cc.EaseExponentialInOut = {

/**
 * @method clone
 * @return A value converted from C/C++ "cocos2d::EaseExponentialInOut*"
 */
clone : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::EaseExponentialInOut*"
 */
reverse : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::EaseExponentialInOut*"
 * @param {cocos2d::ActionInterval*}
 */
create : function () {},

};

/**
 * @class EaseSineIn
 */
cc.EaseSineIn = {

/**
 * @method clone
 * @return A value converted from C/C++ "cocos2d::EaseSineIn*"
 */
clone : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::ActionEase*"
 */
reverse : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::EaseSineIn*"
 * @param {cocos2d::ActionInterval*}
 */
create : function () {},

};

/**
 * @class EaseSineOut
 */
cc.EaseSineOut = {

/**
 * @method clone
 * @return A value converted from C/C++ "cocos2d::EaseSineOut*"
 */
clone : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::ActionEase*"
 */
reverse : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::EaseSineOut*"
 * @param {cocos2d::ActionInterval*}
 */
create : function () {},

};

/**
 * @class EaseSineInOut
 */
cc.EaseSineInOut = {

/**
 * @method clone
 * @return A value converted from C/C++ "cocos2d::EaseSineInOut*"
 */
clone : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::EaseSineInOut*"
 */
reverse : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::EaseSineInOut*"
 * @param {cocos2d::ActionInterval*}
 */
create : function () {},

};

/**
 * @class EaseElastic
 */
cc.EaseElastic = {

/**
 * @method clone
 * @return A value converted from C/C++ "cocos2d::EaseElastic*"
 */
clone : function () {},

/**
 * @method initWithAction
 * @return A value converted from C/C++ "bool"
 * @param {cocos2d::ActionInterval*}
 * @param {float}
 */
initWithAction : function () {},

/**
 * @method setPeriod
 * @param {float}
 */
setPeriod : function () {},

/**
 * @method getPeriod
 * @return A value converted from C/C++ "float"
 */
getPeriod : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::EaseElastic*"
 */
reverse : function () {},

};

/**
 * @class EaseElasticIn
 */
cc.EaseElasticIn = {

/**
 * @method clone
 * @return A value converted from C/C++ "cocos2d::EaseElasticIn*"
 */
clone : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::EaseElastic*"
 */
reverse : function () {},

};

/**
 * @class EaseElasticOut
 */
cc.EaseElasticOut = {

/**
 * @method clone
 * @return A value converted from C/C++ "cocos2d::EaseElasticOut*"
 */
clone : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::EaseElastic*"
 */
reverse : function () {},

};

/**
 * @class EaseElasticInOut
 */
cc.EaseElasticInOut = {

/**
 * @method clone
 * @return A value converted from C/C++ "cocos2d::EaseElasticInOut*"
 */
clone : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::EaseElasticInOut*"
 */
reverse : function () {},

};

/**
 * @class EaseBounce
 */
cc.EaseBounce = {

/**
 * @method bounceTime
 * @return A value converted from C/C++ "float"
 * @param {float}
 */
bounceTime : function () {},

/**
 * @method clone
 * @return A value converted from C/C++ "cocos2d::EaseBounce*"
 */
clone : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::EaseBounce*"
 */
reverse : function () {},

};

/**
 * @class EaseBounceIn
 */
cc.EaseBounceIn = {

/**
 * @method clone
 * @return A value converted from C/C++ "cocos2d::EaseBounceIn*"
 */
clone : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::EaseBounce*"
 */
reverse : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::EaseBounceIn*"
 * @param {cocos2d::ActionInterval*}
 */
create : function () {},

};

/**
 * @class EaseBounceOut
 */
cc.EaseBounceOut = {

/**
 * @method clone
 * @return A value converted from C/C++ "cocos2d::EaseBounceOut*"
 */
clone : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::EaseBounce*"
 */
reverse : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::EaseBounceOut*"
 * @param {cocos2d::ActionInterval*}
 */
create : function () {},

};

/**
 * @class EaseBounceInOut
 */
cc.EaseBounceInOut = {

/**
 * @method clone
 * @return A value converted from C/C++ "cocos2d::EaseBounceInOut*"
 */
clone : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::EaseBounceInOut*"
 */
reverse : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::EaseBounceInOut*"
 * @param {cocos2d::ActionInterval*}
 */
create : function () {},

};

/**
 * @class EaseBackIn
 */
cc.EaseBackIn = {

/**
 * @method clone
 * @return A value converted from C/C++ "cocos2d::EaseBackIn*"
 */
clone : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::ActionEase*"
 */
reverse : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::EaseBackIn*"
 * @param {cocos2d::ActionInterval*}
 */
create : function () {},

};

/**
 * @class EaseBackOut
 */
cc.EaseBackOut = {

/**
 * @method clone
 * @return A value converted from C/C++ "cocos2d::EaseBackOut*"
 */
clone : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::ActionEase*"
 */
reverse : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::EaseBackOut*"
 * @param {cocos2d::ActionInterval*}
 */
create : function () {},

};

/**
 * @class EaseBackInOut
 */
cc.EaseBackInOut = {

/**
 * @method clone
 * @return A value converted from C/C++ "cocos2d::EaseBackInOut*"
 */
clone : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::EaseBackInOut*"
 */
reverse : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::EaseBackInOut*"
 * @param {cocos2d::ActionInterval*}
 */
create : function () {},

};

/**
 * @class ActionInstant
 */
cc.ActionInstant = {

/**
 * @method step
 * @param {float}
 */
step : function () {},

/**
 * @method clone
 * @return A value converted from C/C++ "cocos2d::ActionInstant*"
 */
clone : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::ActionInstant*"
 */
reverse : function () {},

/**
 * @method isDone
 * @return A value converted from C/C++ "bool"
 */
isDone : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

};

/**
 * @class Show
 */
cc.Show = {

/**
 * @method clone
 * @return A value converted from C/C++ "cocos2d::Show*"
 */
clone : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::ActionInstant*"
 */
reverse : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::Show*"
 */
create : function () {},

/**
 * @method Show
 * @constructor
 */
Show : function () {},

};

/**
 * @class Hide
 */
cc.Hide = {

/**
 * @method clone
 * @return A value converted from C/C++ "cocos2d::Hide*"
 */
clone : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::ActionInstant*"
 */
reverse : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::Hide*"
 */
create : function () {},

/**
 * @method Hide
 * @constructor
 */
Hide : function () {},

};

/**
 * @class ToggleVisibility
 */
cc.ToggleVisibility = {

/**
 * @method clone
 * @return A value converted from C/C++ "cocos2d::ToggleVisibility*"
 */
clone : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::ToggleVisibility*"
 */
reverse : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::ToggleVisibility*"
 */
create : function () {},

/**
 * @method ToggleVisibility
 * @constructor
 */
ToggleVisibility : function () {},

};

/**
 * @class RemoveSelf
 */
cc.RemoveSelf = {

/**
 * @method clone
 * @return A value converted from C/C++ "cocos2d::RemoveSelf*"
 */
clone : function () {},

/**
 * @method init
 * @return A value converted from C/C++ "bool"
 * @param {bool}
 */
init : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::RemoveSelf*"
 */
reverse : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::RemoveSelf*"
 */
create : function () {},

/**
 * @method RemoveSelf
 * @constructor
 */
RemoveSelf : function () {},

};

/**
 * @class FlipX
 */
cc.FlipX = {

/**
 * @method initWithFlipX
 * @return A value converted from C/C++ "bool"
 * @param {bool}
 */
initWithFlipX : function () {},

/**
 * @method clone
 * @return A value converted from C/C++ "cocos2d::FlipX*"
 */
clone : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::FlipX*"
 */
reverse : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::FlipX*"
 * @param {bool}
 */
create : function () {},

/**
 * @method FlipX
 * @constructor
 */
FlipX : function () {},

};

/**
 * @class FlipY
 */
cc.FlipY = {

/**
 * @method initWithFlipY
 * @return A value converted from C/C++ "bool"
 * @param {bool}
 */
initWithFlipY : function () {},

/**
 * @method clone
 * @return A value converted from C/C++ "cocos2d::FlipY*"
 */
clone : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::FlipY*"
 */
reverse : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::FlipY*"
 * @param {bool}
 */
create : function () {},

/**
 * @method FlipY
 * @constructor
 */
FlipY : function () {},

};

/**
 * @class Place
 */
cc.Place = {

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::Place*"
 */
reverse : function () {},

/**
 * @method clone
 * @return A value converted from C/C++ "cocos2d::Place*"
 */
clone : function () {},

/**
 * @method initWithPosition
 * @return A value converted from C/C++ "bool"
 * @param {cocos2d::Point}
 */
initWithPosition : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::Place*"
 * @param {cocos2d::Point}
 */
create : function () {},

/**
 * @method Place
 * @constructor
 */
Place : function () {},

};

/**
 * @class CallFunc
 */
cc.CallFunc = {

/**
 * @method execute
 */
execute : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::CallFunc*"
 */
reverse : function () {},

/**
 * @method clone
 * @return A value converted from C/C++ "cocos2d::CallFunc*"
 */
clone : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method getTargetCallback
 * @return A value converted from C/C++ "cocos2d::Object*"
 */
getTargetCallback : function () {},

/**
 * @method setTargetCallback
 * @param {cocos2d::Object*}
 */
setTargetCallback : function () {},

/**
 * @method CallFunc
 * @constructor
 */
CallFunc : function () {},

};

/**
 * @class GridAction
 */
cc.GridAction = {

/**
 * @method startWithTarget
 * @param {cocos2d::Node*}
 */
startWithTarget : function () {},

/**
 * @method clone
 * @return A value converted from C/C++ "cocos2d::GridAction*"
 */
clone : function () {},

/**
 * @method getGrid
 * @return A value converted from C/C++ "cocos2d::GridBase*"
 */
getGrid : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::GridAction*"
 */
reverse : function () {},

/**
 * @method initWithDuration
 * @return A value converted from C/C++ "bool"
 * @param {float}
 * @param {cocos2d::Size}
 */
initWithDuration : function () {},

};

/**
 * @class Grid3DAction
 */
cc.Grid3DAction = {

/**
 * @method clone
 * @return A value converted from C/C++ "cocos2d::Grid3DAction*"
 */
clone : function () {},

/**
 * @method getGrid
 * @return A value converted from C/C++ "cocos2d::GridBase*"
 */
getGrid : function () {},

};

/**
 * @class TiledGrid3DAction
 */
cc.TiledGrid3DAction = {

/**
 * @method clone
 * @return A value converted from C/C++ "cocos2d::TiledGrid3DAction*"
 */
clone : function () {},

/**
 * @method getGrid
 * @return A value converted from C/C++ "cocos2d::GridBase*"
 */
getGrid : function () {},

};

/**
 * @class StopGrid
 */
cc.StopGrid = {

/**
 * @method startWithTarget
 * @param {cocos2d::Node*}
 */
startWithTarget : function () {},

/**
 * @method clone
 * @return A value converted from C/C++ "cocos2d::StopGrid*"
 */
clone : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::StopGrid*"
 */
reverse : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::StopGrid*"
 */
create : function () {},

};

/**
 * @class ReuseGrid
 */
cc.ReuseGrid = {

/**
 * @method startWithTarget
 * @param {cocos2d::Node*}
 */
startWithTarget : function () {},

/**
 * @method initWithTimes
 * @return A value converted from C/C++ "bool"
 * @param {int}
 */
initWithTimes : function () {},

/**
 * @method clone
 * @return A value converted from C/C++ "cocos2d::ReuseGrid*"
 */
clone : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::ReuseGrid*"
 */
reverse : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::ReuseGrid*"
 * @param {int}
 */
create : function () {},

};

/**
 * @class Waves3D
 */
cc.Waves3D = {

/**
 * @method setAmplitudeRate
 * @param {float}
 */
setAmplitudeRate : function () {},

/**
 * @method initWithDuration
 * @return A value converted from C/C++ "bool"
 * @param {float}
 * @param {cocos2d::Size}
 * @param {unsigned int}
 * @param {float}
 */
initWithDuration : function () {},

/**
 * @method clone
 * @return A value converted from C/C++ "cocos2d::Waves3D*"
 */
clone : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method getAmplitudeRate
 * @return A value converted from C/C++ "float"
 */
getAmplitudeRate : function () {},

/**
 * @method setAmplitude
 * @param {float}
 */
setAmplitude : function () {},

/**
 * @method getAmplitude
 * @return A value converted from C/C++ "float"
 */
getAmplitude : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::Waves3D*"
 * @param {float}
 * @param {cocos2d::Size}
 * @param {unsigned int}
 * @param {float}
 */
create : function () {},

};

/**
 * @class FlipX3D
 */
cc.FlipX3D = {

/**
 * @method initWithSize
 * @return A value converted from C/C++ "bool"
 * @param {cocos2d::Size}
 * @param {float}
 */
initWithSize : function () {},

/**
 * @method clone
 * @return A value converted from C/C++ "cocos2d::FlipX3D*"
 */
clone : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method initWithDuration
 * @return A value converted from C/C++ "bool"
 * @param {float}
 */
initWithDuration : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::FlipX3D*"
 * @param {float}
 */
create : function () {},

};

/**
 * @class FlipY3D
 */
cc.FlipY3D = {

/**
 * @method clone
 * @return A value converted from C/C++ "cocos2d::FlipY3D*"
 */
clone : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::FlipY3D*"
 * @param {float}
 */
create : function () {},

};

/**
 * @class Lens3D
 */
cc.Lens3D = {

/**
 * @method setConcave
 * @param {bool}
 */
setConcave : function () {},

/**
 * @method initWithDuration
 * @return A value converted from C/C++ "bool"
 * @param {float}
 * @param {cocos2d::Size}
 * @param {cocos2d::Point}
 * @param {float}
 */
initWithDuration : function () {},

/**
 * @method setLensEffect
 * @param {float}
 */
setLensEffect : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method getLensEffect
 * @return A value converted from C/C++ "float"
 */
getLensEffect : function () {},

/**
 * @method setPosition
 * @param {cocos2d::Point}
 */
setPosition : function () {},

/**
 * @method clone
 * @return A value converted from C/C++ "cocos2d::Lens3D*"
 */
clone : function () {},

/**
 * @method getPosition
 * @return A value converted from C/C++ "cocos2d::Point"
 */
getPosition : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::Lens3D*"
 * @param {float}
 * @param {cocos2d::Size}
 * @param {cocos2d::Point}
 * @param {float}
 */
create : function () {},

};

/**
 * @class Ripple3D
 */
cc.Ripple3D = {

/**
 * @method setAmplitudeRate
 * @param {float}
 */
setAmplitudeRate : function () {},

/**
 * @method initWithDuration
 * @return A value converted from C/C++ "bool"
 * @param {float}
 * @param {cocos2d::Size}
 * @param {cocos2d::Point}
 * @param {float}
 * @param {unsigned int}
 * @param {float}
 */
initWithDuration : function () {},

/**
 * @method clone
 * @return A value converted from C/C++ "cocos2d::Ripple3D*"
 */
clone : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method getAmplitudeRate
 * @return A value converted from C/C++ "float"
 */
getAmplitudeRate : function () {},

/**
 * @method setAmplitude
 * @param {float}
 */
setAmplitude : function () {},

/**
 * @method getAmplitude
 * @return A value converted from C/C++ "float"
 */
getAmplitude : function () {},

/**
 * @method setPosition
 * @param {cocos2d::Point}
 */
setPosition : function () {},

/**
 * @method getPosition
 * @return A value converted from C/C++ "cocos2d::Point"
 */
getPosition : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::Ripple3D*"
 * @param {float}
 * @param {cocos2d::Size}
 * @param {cocos2d::Point}
 * @param {float}
 * @param {unsigned int}
 * @param {float}
 */
create : function () {},

};

/**
 * @class Shaky3D
 */
cc.Shaky3D = {

/**
 * @method clone
 * @return A value converted from C/C++ "cocos2d::Shaky3D*"
 */
clone : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method initWithDuration
 * @return A value converted from C/C++ "bool"
 * @param {float}
 * @param {cocos2d::Size}
 * @param {int}
 * @param {bool}
 */
initWithDuration : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::Shaky3D*"
 * @param {float}
 * @param {cocos2d::Size}
 * @param {int}
 * @param {bool}
 */
create : function () {},

};

/**
 * @class Liquid
 */
cc.Liquid = {

/**
 * @method setAmplitudeRate
 * @param {float}
 */
setAmplitudeRate : function () {},

/**
 * @method initWithDuration
 * @return A value converted from C/C++ "bool"
 * @param {float}
 * @param {cocos2d::Size}
 * @param {unsigned int}
 * @param {float}
 */
initWithDuration : function () {},

/**
 * @method clone
 * @return A value converted from C/C++ "cocos2d::Liquid*"
 */
clone : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method getAmplitudeRate
 * @return A value converted from C/C++ "float"
 */
getAmplitudeRate : function () {},

/**
 * @method setAmplitude
 * @param {float}
 */
setAmplitude : function () {},

/**
 * @method getAmplitude
 * @return A value converted from C/C++ "float"
 */
getAmplitude : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::Liquid*"
 * @param {float}
 * @param {cocos2d::Size}
 * @param {unsigned int}
 * @param {float}
 */
create : function () {},

};

/**
 * @class Waves
 */
cc.Waves = {

/**
 * @method setAmplitudeRate
 * @param {float}
 */
setAmplitudeRate : function () {},

/**
 * @method initWithDuration
 * @return A value converted from C/C++ "bool"
 * @param {float}
 * @param {cocos2d::Size}
 * @param {unsigned int}
 * @param {float}
 * @param {bool}
 * @param {bool}
 */
initWithDuration : function () {},

/**
 * @method clone
 * @return A value converted from C/C++ "cocos2d::Waves*"
 */
clone : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method getAmplitudeRate
 * @return A value converted from C/C++ "float"
 */
getAmplitudeRate : function () {},

/**
 * @method setAmplitude
 * @param {float}
 */
setAmplitude : function () {},

/**
 * @method getAmplitude
 * @return A value converted from C/C++ "float"
 */
getAmplitude : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::Waves*"
 * @param {float}
 * @param {cocos2d::Size}
 * @param {unsigned int}
 * @param {float}
 * @param {bool}
 * @param {bool}
 */
create : function () {},

};

/**
 * @class Twirl
 */
cc.Twirl = {

/**
 * @method setAmplitudeRate
 * @param {float}
 */
setAmplitudeRate : function () {},

/**
 * @method initWithDuration
 * @return A value converted from C/C++ "bool"
 * @param {float}
 * @param {cocos2d::Size}
 * @param {cocos2d::Point}
 * @param {unsigned int}
 * @param {float}
 */
initWithDuration : function () {},

/**
 * @method clone
 * @return A value converted from C/C++ "cocos2d::Twirl*"
 */
clone : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method getAmplitudeRate
 * @return A value converted from C/C++ "float"
 */
getAmplitudeRate : function () {},

/**
 * @method setAmplitude
 * @param {float}
 */
setAmplitude : function () {},

/**
 * @method getAmplitude
 * @return A value converted from C/C++ "float"
 */
getAmplitude : function () {},

/**
 * @method setPosition
 * @param {cocos2d::Point}
 */
setPosition : function () {},

/**
 * @method getPosition
 * @return A value converted from C/C++ "cocos2d::Point"
 */
getPosition : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::Twirl*"
 * @param {float}
 * @param {cocos2d::Size}
 * @param {cocos2d::Point}
 * @param {unsigned int}
 * @param {float}
 */
create : function () {},

};

/**
 * @class PageTurn3D
 */
cc.PageTurn3D = {

/**
 * @method clone
 * @return A value converted from C/C++ "cocos2d::PageTurn3D*"
 */
clone : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::PageTurn3D*"
 * @param {float}
 * @param {cocos2d::Size}
 */
create : function () {},

};

/**
 * @class ProgressTo
 */
cc.ProgressTo = {

/**
 * @method startWithTarget
 * @param {cocos2d::Node*}
 */
startWithTarget : function () {},

/**
 * @method clone
 * @return A value converted from C/C++ "cocos2d::ProgressTo*"
 */
clone : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::ProgressTo*"
 */
reverse : function () {},

/**
 * @method initWithDuration
 * @return A value converted from C/C++ "bool"
 * @param {float}
 * @param {float}
 */
initWithDuration : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::ProgressTo*"
 * @param {float}
 * @param {float}
 */
create : function () {},

};

/**
 * @class ProgressFromTo
 */
cc.ProgressFromTo = {

/**
 * @method startWithTarget
 * @param {cocos2d::Node*}
 */
startWithTarget : function () {},

/**
 * @method clone
 * @return A value converted from C/C++ "cocos2d::ProgressFromTo*"
 */
clone : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::ProgressFromTo*"
 */
reverse : function () {},

/**
 * @method initWithDuration
 * @return A value converted from C/C++ "bool"
 * @param {float}
 * @param {float}
 * @param {float}
 */
initWithDuration : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::ProgressFromTo*"
 * @param {float}
 * @param {float}
 * @param {float}
 */
create : function () {},

};

/**
 * @class ShakyTiles3D
 */
cc.ShakyTiles3D = {

/**
 * @method clone
 * @return A value converted from C/C++ "cocos2d::ShakyTiles3D*"
 */
clone : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method initWithDuration
 * @return A value converted from C/C++ "bool"
 * @param {float}
 * @param {cocos2d::Size}
 * @param {int}
 * @param {bool}
 */
initWithDuration : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::ShakyTiles3D*"
 * @param {float}
 * @param {cocos2d::Size}
 * @param {int}
 * @param {bool}
 */
create : function () {},

};

/**
 * @class ShatteredTiles3D
 */
cc.ShatteredTiles3D = {

/**
 * @method clone
 * @return A value converted from C/C++ "cocos2d::ShatteredTiles3D*"
 */
clone : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method initWithDuration
 * @return A value converted from C/C++ "bool"
 * @param {float}
 * @param {cocos2d::Size}
 * @param {int}
 * @param {bool}
 */
initWithDuration : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::ShatteredTiles3D*"
 * @param {float}
 * @param {cocos2d::Size}
 * @param {int}
 * @param {bool}
 */
create : function () {},

};

/**
 * @class ShuffleTiles
 */
cc.ShuffleTiles = {

/**
 * @method startWithTarget
 * @param {cocos2d::Node*}
 */
startWithTarget : function () {},

/**
 * @method placeTile
 * @param {cocos2d::Point}
 * @param {cocos2d::Tile*}
 */
placeTile : function () {},

/**
 * @method initWithDuration
 * @return A value converted from C/C++ "bool"
 * @param {float}
 * @param {cocos2d::Size}
 * @param {unsigned int}
 */
initWithDuration : function () {},

/**
 * @method getDelta
 * @return A value converted from C/C++ "cocos2d::Size"
 * @param {cocos2d::Size}
 */
getDelta : function () {},

/**
 * @method clone
 * @return A value converted from C/C++ "cocos2d::ShuffleTiles*"
 */
clone : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method shuffle
 * @param {unsigned int*}
 * @param {unsigned int}
 */
shuffle : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::ShuffleTiles*"
 * @param {float}
 * @param {cocos2d::Size}
 * @param {unsigned int}
 */
create : function () {},

};

/**
 * @class FadeOutTRTiles
 */
cc.FadeOutTRTiles = {

/**
 * @method turnOnTile
 * @param {cocos2d::Point}
 */
turnOnTile : function () {},

/**
 * @method turnOffTile
 * @param {cocos2d::Point}
 */
turnOffTile : function () {},

/**
 * @method transformTile
 * @param {cocos2d::Point}
 * @param {float}
 */
transformTile : function () {},

/**
 * @method clone
 * @return A value converted from C/C++ "cocos2d::FadeOutTRTiles*"
 */
clone : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method testFunc
 * @return A value converted from C/C++ "float"
 * @param {cocos2d::Size}
 * @param {float}
 */
testFunc : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::FadeOutTRTiles*"
 * @param {float}
 * @param {cocos2d::Size}
 */
create : function () {},

};

/**
 * @class FadeOutBLTiles
 */
cc.FadeOutBLTiles = {

/**
 * @method clone
 * @return A value converted from C/C++ "cocos2d::FadeOutBLTiles*"
 */
clone : function () {},

/**
 * @method testFunc
 * @return A value converted from C/C++ "float"
 * @param {cocos2d::Size}
 * @param {float}
 */
testFunc : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::FadeOutBLTiles*"
 * @param {float}
 * @param {cocos2d::Size}
 */
create : function () {},

};

/**
 * @class FadeOutUpTiles
 */
cc.FadeOutUpTiles = {

/**
 * @method clone
 * @return A value converted from C/C++ "cocos2d::FadeOutUpTiles*"
 */
clone : function () {},

/**
 * @method transformTile
 * @param {cocos2d::Point}
 * @param {float}
 */
transformTile : function () {},

/**
 * @method testFunc
 * @return A value converted from C/C++ "float"
 * @param {cocos2d::Size}
 * @param {float}
 */
testFunc : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::FadeOutUpTiles*"
 * @param {float}
 * @param {cocos2d::Size}
 */
create : function () {},

};

/**
 * @class FadeOutDownTiles
 */
cc.FadeOutDownTiles = {

/**
 * @method clone
 * @return A value converted from C/C++ "cocos2d::FadeOutDownTiles*"
 */
clone : function () {},

/**
 * @method testFunc
 * @return A value converted from C/C++ "float"
 * @param {cocos2d::Size}
 * @param {float}
 */
testFunc : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::FadeOutDownTiles*"
 * @param {float}
 * @param {cocos2d::Size}
 */
create : function () {},

};

/**
 * @class TurnOffTiles
 */
cc.TurnOffTiles = {

/**
 * @method turnOnTile
 * @param {cocos2d::Point}
 */
turnOnTile : function () {},

/**
 * @method startWithTarget
 * @param {cocos2d::Node*}
 */
startWithTarget : function () {},

/**
 * @method turnOffTile
 * @param {cocos2d::Point}
 */
turnOffTile : function () {},

/**
 * @method shuffle
 * @param {unsigned int*}
 * @param {unsigned int}
 */
shuffle : function () {},

/**
 * @method initWithDuration
 * @return A value converted from C/C++ "bool"
 * @param {float}
 * @param {cocos2d::Size}
 * @param {unsigned int}
 */
initWithDuration : function () {},

/**
 * @method clone
 * @return A value converted from C/C++ "cocos2d::TurnOffTiles*"
 */
clone : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

};

/**
 * @class WavesTiles3D
 */
cc.WavesTiles3D = {

/**
 * @method setAmplitudeRate
 * @param {float}
 */
setAmplitudeRate : function () {},

/**
 * @method initWithDuration
 * @return A value converted from C/C++ "bool"
 * @param {float}
 * @param {cocos2d::Size}
 * @param {unsigned int}
 * @param {float}
 */
initWithDuration : function () {},

/**
 * @method clone
 * @return A value converted from C/C++ "cocos2d::WavesTiles3D*"
 */
clone : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method getAmplitudeRate
 * @return A value converted from C/C++ "float"
 */
getAmplitudeRate : function () {},

/**
 * @method setAmplitude
 * @param {float}
 */
setAmplitude : function () {},

/**
 * @method getAmplitude
 * @return A value converted from C/C++ "float"
 */
getAmplitude : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::WavesTiles3D*"
 * @param {float}
 * @param {cocos2d::Size}
 * @param {unsigned int}
 * @param {float}
 */
create : function () {},

};

/**
 * @class JumpTiles3D
 */
cc.JumpTiles3D = {

/**
 * @method setAmplitudeRate
 * @param {float}
 */
setAmplitudeRate : function () {},

/**
 * @method initWithDuration
 * @return A value converted from C/C++ "bool"
 * @param {float}
 * @param {cocos2d::Size}
 * @param {unsigned int}
 * @param {float}
 */
initWithDuration : function () {},

/**
 * @method clone
 * @return A value converted from C/C++ "cocos2d::JumpTiles3D*"
 */
clone : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method getAmplitudeRate
 * @return A value converted from C/C++ "float"
 */
getAmplitudeRate : function () {},

/**
 * @method setAmplitude
 * @param {float}
 */
setAmplitude : function () {},

/**
 * @method getAmplitude
 * @return A value converted from C/C++ "float"
 */
getAmplitude : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::JumpTiles3D*"
 * @param {float}
 * @param {cocos2d::Size}
 * @param {unsigned int}
 * @param {float}
 */
create : function () {},

};

/**
 * @class SplitRows
 */
cc.SplitRows = {

/**
 * @method startWithTarget
 * @param {cocos2d::Node*}
 */
startWithTarget : function () {},

/**
 * @method clone
 * @return A value converted from C/C++ "cocos2d::SplitRows*"
 */
clone : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method initWithDuration
 * @return A value converted from C/C++ "bool"
 * @param {float}
 * @param {unsigned int}
 */
initWithDuration : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::SplitRows*"
 * @param {float}
 * @param {unsigned int}
 */
create : function () {},

};

/**
 * @class SplitCols
 */
cc.SplitCols = {

/**
 * @method startWithTarget
 * @param {cocos2d::Node*}
 */
startWithTarget : function () {},

/**
 * @method clone
 * @return A value converted from C/C++ "cocos2d::SplitCols*"
 */
clone : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method initWithDuration
 * @return A value converted from C/C++ "bool"
 * @param {float}
 * @param {unsigned int}
 */
initWithDuration : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::SplitCols*"
 * @param {float}
 * @param {unsigned int}
 */
create : function () {},

};

/**
 * @class ActionTween
 */
cc.ActionTween = {

/**
 * @method startWithTarget
 * @param {cocos2d::Node*}
 */
startWithTarget : function () {},

/**
 * @method clone
 * @return A value converted from C/C++ "cocos2d::ActionTween*"
 */
clone : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method initWithDuration
 * @return A value converted from C/C++ "bool"
 * @param {float}
 * @param {const char*}
 * @param {float}
 * @param {float}
 */
initWithDuration : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::ActionTween*"
 */
reverse : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::ActionTween*"
 * @param {float}
 * @param {const char*}
 * @param {float}
 * @param {float}
 */
create : function () {},

};

/**
 * @class CardinalSplineTo
 */
cc.CardinalSplineTo = {

/**
 * @method startWithTarget
 * @param {cocos2d::Node*}
 */
startWithTarget : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::CardinalSplineTo*"
 */
reverse : function () {},

/**
 * @method initWithDuration
 * @return A value converted from C/C++ "bool"
 * @param {float}
 * @param {cocos2d::PointArray*}
 * @param {float}
 */
initWithDuration : function () {},

/**
 * @method getPoints
 * @return A value converted from C/C++ "cocos2d::PointArray*"
 */
getPoints : function () {},

/**
 * @method updatePosition
 * @param {cocos2d::Point}
 */
updatePosition : function () {},

/**
 * @method clone
 * @return A value converted from C/C++ "cocos2d::CardinalSplineTo*"
 */
clone : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method CardinalSplineTo
 * @constructor
 */
CardinalSplineTo : function () {},

};

/**
 * @class CardinalSplineBy
 */
cc.CardinalSplineBy = {

/**
 * @method startWithTarget
 * @param {cocos2d::Node*}
 */
startWithTarget : function () {},

/**
 * @method clone
 * @return A value converted from C/C++ "cocos2d::CardinalSplineBy*"
 */
clone : function () {},

/**
 * @method updatePosition
 * @param {cocos2d::Point}
 */
updatePosition : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::CardinalSplineBy*"
 */
reverse : function () {},

/**
 * @method CardinalSplineBy
 * @constructor
 */
CardinalSplineBy : function () {},

};

/**
 * @class CatmullRomTo
 */
cc.CatmullRomTo = {

/**
 * @method clone
 * @return A value converted from C/C++ "cocos2d::CatmullRomTo*"
 */
clone : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::CatmullRomTo*"
 */
reverse : function () {},

/**
 * @method initWithDuration
 * @return A value converted from C/C++ "bool"
 * @param {float}
 * @param {cocos2d::PointArray*}
 */
initWithDuration : function () {},

};

/**
 * @class CatmullRomBy
 */
cc.CatmullRomBy = {

/**
 * @method clone
 * @return A value converted from C/C++ "cocos2d::CatmullRomBy*"
 */
clone : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::CatmullRomBy*"
 */
reverse : function () {},

/**
 * @method initWithDuration
 * @return A value converted from C/C++ "bool"
 * @param {float}
 * @param {cocos2d::PointArray*}
 */
initWithDuration : function () {},

};

/**
 * @class AtlasNode
 */
cc.AtlasNode = {

/**
 * @method draw
 */
draw : function () {},

/**
 * @method updateAtlasValues
 */
updateAtlasValues : function () {},

/**
 * @method initWithTexture
 * @return A value converted from C/C++ "bool"
 * @param {cocos2d::Texture2D*}
 * @param {unsigned int}
 * @param {unsigned int}
 * @param {unsigned int}
 */
initWithTexture : function () {},

/**
 * @method setColor
 * @param {cocos2d::Color3B}
 */
setColor : function () {},

/**
 * @method setOpacity
 * @param {unsigned char}
 */
setOpacity : function () {},

/**
 * @method getTexture
 * @return A value converted from C/C++ "cocos2d::Texture2D*"
 */
getTexture : function () {},

/**
 * @method setTextureAtlas
 * @param {cocos2d::TextureAtlas*}
 */
setTextureAtlas : function () {},

/**
 * @method getTextureAtlas
 * @return A value converted from C/C++ "cocos2d::TextureAtlas*"
 */
getTextureAtlas : function () {},

/**
 * @method setOpacityModifyRGB
 * @param {bool}
 */
setOpacityModifyRGB : function () {},

/**
 * @method getQuadsToDraw
 * @return A value converted from C/C++ "unsigned int"
 */
getQuadsToDraw : function () {},

/**
 * @method setTexture
 * @param {cocos2d::Texture2D*}
 */
setTexture : function () {},

/**
 * @method getColor
 * @return A value converted from C/C++ "cocos2d::Color3B"
 */
getColor : function () {},

/**
 * @method initWithTileFile
 * @return A value converted from C/C++ "bool"
 * @param {const char*}
 * @param {unsigned int}
 * @param {unsigned int}
 * @param {unsigned int}
 */
initWithTileFile : function () {},

/**
 * @method isOpacityModifyRGB
 * @return A value converted from C/C++ "bool"
 */
isOpacityModifyRGB : function () {},

/**
 * @method setQuadsToDraw
 * @param {unsigned int}
 */
setQuadsToDraw : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::AtlasNode*"
 * @param {const char*}
 * @param {unsigned int}
 * @param {unsigned int}
 * @param {unsigned int}
 */
create : function () {},

/**
 * @method AtlasNode
 * @constructor
 */
AtlasNode : function () {},

};

/**
 * @class DrawNode
 */
cc.DrawNode = {

/**
 * @method draw
 */
draw : function () {},

/**
 * @method clear
 */
clear : function () {},

/**
 * @method init
 * @return A value converted from C/C++ "bool"
 */
init : function () {},

/**
 * @method drawDot
 * @param {cocos2d::Point}
 * @param {float}
 * @param {cocos2d::Color4F}
 */
drawDot : function () {},

/**
 * @method drawSegment
 * @param {cocos2d::Point}
 * @param {cocos2d::Point}
 * @param {float}
 * @param {cocos2d::Color4F}
 */
drawSegment : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::DrawNode*"
 */
create : function () {},

/**
 * @method DrawNode
 * @constructor
 */
DrawNode : function () {},

};

/**
 * @class Camera
 */
cc.Camera = {

/**
 * @method locate
 */
locate : function () {},

/**
 * @method restore
 */
restore : function () {},

/**
 * @method setEyeXYZ
 * @param {float}
 * @param {float}
 * @param {float}
 */
setEyeXYZ : function () {},

/**
 * @method setCenterXYZ
 * @param {float}
 * @param {float}
 * @param {float}
 */
setCenterXYZ : function () {},

/**
 * @method isDirty
 * @return A value converted from C/C++ "bool"
 */
isDirty : function () {},

/**
 * @method init
 */
init : function () {},

/**
 * @method setDirty
 * @param {bool}
 */
setDirty : function () {},

/**
 * @method setUpXYZ
 * @param {float}
 * @param {float}
 * @param {float}
 */
setUpXYZ : function () {},

/**
 * @method getZEye
 * @return A value converted from C/C++ "float"
 */
getZEye : function () {},

/**
 * @method Camera
 * @constructor
 */
Camera : function () {},

};

/**
 * @class LabelAtlas
 */
cc.LabelAtlas = {

/**
 * @method setString
 * @param {const char*}
 */
setString : function () {},

/**
 * @method updateAtlasValues
 */
updateAtlasValues : function () {},

/**
 * @method getString
 * @return A value converted from C/C++ "const char*"
 */
getString : function () {},

/**
 * @method LabelAtlas
 * @constructor
 */
LabelAtlas : function () {},

};

/**
 * @class Director
 */
cc.Director = {

/**
 * @method pause
 */
pause : function () {},

/**
 * @method setContentScaleFactor
 * @param {float}
 */
setContentScaleFactor : function () {},

/**
 * @method getContentScaleFactor
 * @return A value converted from C/C++ "float"
 */
getContentScaleFactor : function () {},

/**
 * @method getWinSizeInPixels
 * @return A value converted from C/C++ "cocos2d::Size"
 */
getWinSizeInPixels : function () {},

/**
 * @method getDeltaTime
 * @return A value converted from C/C++ "float"
 */
getDeltaTime : function () {},

/**
 * @method setGLDefaultValues
 */
setGLDefaultValues : function () {},

/**
 * @method setActionManager
 * @param {cocos2d::ActionManager*}
 */
setActionManager : function () {},

/**
 * @method setAlphaBlending
 * @param {bool}
 */
setAlphaBlending : function () {},

/**
 * @method popToRootScene
 */
popToRootScene : function () {},

/**
 * @method getNotificationNode
 * @return A value converted from C/C++ "cocos2d::Node*"
 */
getNotificationNode : function () {},

/**
 * @method getWinSize
 * @return A value converted from C/C++ "cocos2d::Size"
 */
getWinSize : function () {},

/**
 * @method end
 */
end : function () {},

/**
 * @method isSendCleanupToScene
 * @return A value converted from C/C++ "bool"
 */
isSendCleanupToScene : function () {},

/**
 * @method getVisibleOrigin
 * @return A value converted from C/C++ "cocos2d::Point"
 */
getVisibleOrigin : function () {},

/**
 * @method mainLoop
 */
mainLoop : function () {},

/**
 * @method setDepthTest
 * @param {bool}
 */
setDepthTest : function () {},

/**
 * @method getSecondsPerFrame
 * @return A value converted from C/C++ "float"
 */
getSecondsPerFrame : function () {},

/**
 * @method convertToUI
 * @return A value converted from C/C++ "cocos2d::Point"
 * @param {cocos2d::Point}
 */
convertToUI : function () {},

/**
 * @method setAccelerometer
 * @param {cocos2d::Accelerometer*}
 */
setAccelerometer : function () {},

/**
 * @method setDefaultValues
 */
setDefaultValues : function () {},

/**
 * @method init
 * @return A value converted from C/C++ "bool"
 */
init : function () {},

/**
 * @method setScheduler
 * @param {cocos2d::Scheduler*}
 */
setScheduler : function () {},

/**
 * @method startAnimation
 */
startAnimation : function () {},

/**
 * @method getRunningScene
 * @return A value converted from C/C++ "cocos2d::Scene*"
 */
getRunningScene : function () {},

/**
 * @method setViewport
 */
setViewport : function () {},

/**
 * @method stopAnimation
 */
stopAnimation : function () {},

/**
 * @method popToSceneStackLevel
 * @param {int}
 */
popToSceneStackLevel : function () {},

/**
 * @method resume
 */
resume : function () {},

/**
 * @method isNextDeltaTimeZero
 * @return A value converted from C/C++ "bool"
 */
isNextDeltaTimeZero : function () {},

/**
 * @method setOpenGLView
 * @param {cocos2d::EGLView*}
 */
setOpenGLView : function () {},

/**
 * @method convertToGL
 * @return A value converted from C/C++ "cocos2d::Point"
 * @param {cocos2d::Point}
 */
convertToGL : function () {},

/**
 * @method purgeCachedData
 */
purgeCachedData : function () {},

/**
 * @method getTotalFrames
 * @return A value converted from C/C++ "unsigned int"
 */
getTotalFrames : function () {},

/**
 * @method runWithScene
 * @param {cocos2d::Scene*}
 */
runWithScene : function () {},

/**
 * @method setNotificationNode
 * @param {cocos2d::Node*}
 */
setNotificationNode : function () {},

/**
 * @method drawScene
 */
drawScene : function () {},

/**
 * @method popScene
 */
popScene : function () {},

/**
 * @method isDisplayStats
 * @return A value converted from C/C++ "bool"
 */
isDisplayStats : function () {},

/**
 * @method setProjection
 * @param {cocos2d::Director::Projection}
 */
setProjection : function () {},

/**
 * @method getZEye
 * @return A value converted from C/C++ "float"
 */
getZEye : function () {},

/**
 * @method setNextDeltaTimeZero
 * @param {bool}
 */
setNextDeltaTimeZero : function () {},

/**
 * @method getVisibleSize
 * @return A value converted from C/C++ "cocos2d::Size"
 */
getVisibleSize : function () {},

/**
 * @method getScheduler
 * @return A value converted from C/C++ "cocos2d::Scheduler*"
 */
getScheduler : function () {},

/**
 * @method pushScene
 * @param {cocos2d::Scene*}
 */
pushScene : function () {},

/**
 * @method getAnimationInterval
 * @return A value converted from C/C++ "double"
 */
getAnimationInterval : function () {},

/**
 * @method isPaused
 * @return A value converted from C/C++ "bool"
 */
isPaused : function () {},

/**
 * @method setDisplayStats
 * @param {bool}
 */
setDisplayStats : function () {},

/**
 * @method replaceScene
 * @param {cocos2d::Scene*}
 */
replaceScene : function () {},

/**
 * @method setAnimationInterval
 * @param {double}
 */
setAnimationInterval : function () {},

/**
 * @method getActionManager
 * @return A value converted from C/C++ "cocos2d::ActionManager*"
 */
getActionManager : function () {},

/**
 * @method getInstance
 * @return A value converted from C/C++ "cocos2d::Director*"
 */
getInstance : function () {},

};

/**
 * @class GridBase
 */
cc.GridBase = {

/**
 * @method setGridSize
 * @param {cocos2d::Size}
 */
setGridSize : function () {},

/**
 * @method calculateVertexPoints
 */
calculateVertexPoints : function () {},

/**
 * @method afterDraw
 * @param {cocos2d::Node*}
 */
afterDraw : function () {},

/**
 * @method beforeDraw
 */
beforeDraw : function () {},

/**
 * @method isTextureFlipped
 * @return A value converted from C/C++ "bool"
 */
isTextureFlipped : function () {},

/**
 * @method getGridSize
 * @return A value converted from C/C++ "cocos2d::Size"
 */
getGridSize : function () {},

/**
 * @method getStep
 * @return A value converted from C/C++ "cocos2d::Point"
 */
getStep : function () {},

/**
 * @method set2DProjection
 */
set2DProjection : function () {},

/**
 * @method setStep
 * @param {cocos2d::Point}
 */
setStep : function () {},

/**
 * @method setTextureFlipped
 * @param {bool}
 */
setTextureFlipped : function () {},

/**
 * @method blit
 */
blit : function () {},

/**
 * @method setActive
 * @param {bool}
 */
setActive : function () {},

/**
 * @method getReuseGrid
 * @return A value converted from C/C++ "int"
 */
getReuseGrid : function () {},

/**
 * @method setReuseGrid
 * @param {int}
 */
setReuseGrid : function () {},

/**
 * @method isActive
 * @return A value converted from C/C++ "bool"
 */
isActive : function () {},

/**
 * @method reuse
 */
reuse : function () {},

};

/**
 * @class Grid3D
 */
cc.Grid3D = {

/**
 * @method calculateVertexPoints
 */
calculateVertexPoints : function () {},

/**
 * @method reuse
 */
reuse : function () {},

/**
 * @method blit
 */
blit : function () {},

/**
 * @method Grid3D
 * @constructor
 */
Grid3D : function () {},

};

/**
 * @class TiledGrid3D
 */
cc.TiledGrid3D = {

/**
 * @method calculateVertexPoints
 */
calculateVertexPoints : function () {},

/**
 * @method reuse
 */
reuse : function () {},

/**
 * @method blit
 */
blit : function () {},

/**
 * @method TiledGrid3D
 * @constructor
 */
TiledGrid3D : function () {},

};

/**
 * @class Sprite
 */
cc.Sprite = {

/**
 * @method draw
 */
draw : function () {},

/**
 * @method setTexture
 * @param {cocos2d::Texture2D*}
 */
setTexture : function () {},

/**
 * @method isFlipX
 * @return A value converted from C/C++ "bool"
 */
isFlipX : function () {},

/**
 * @method getTexture
 * @return A value converted from C/C++ "cocos2d::Texture2D*"
 */
getTexture : function () {},

/**
 * @method setRotationY
 * @param {float}
 */
setRotationY : function () {},

/**
 * @method setRotationX
 * @param {float}
 */
setRotationX : function () {},

/**
 * @method setScale
 * @param {float}
 */
setScale : function () {},

/**
 * @method setOpacity
 * @param {unsigned char}
 */
setOpacity : function () {},

/**
 * @method setDisplayFrameWithAnimationName
 * @param {const char*}
 * @param {int}
 */
setDisplayFrameWithAnimationName : function () {},

/**
 * @method setScaleX
 * @param {float}
 */
setScaleX : function () {},

/**
 * @method setAnchorPoint
 * @param {cocos2d::Point}
 */
setAnchorPoint : function () {},

/**
 * @method getBatchNode
 * @return A value converted from C/C++ "cocos2d::SpriteBatchNode*"
 */
getBatchNode : function () {},

/**
 * @method getOffsetPosition
 * @return A value converted from C/C++ "cocos2d::Point"
 */
getOffsetPosition : function () {},

/**
 * @method isOpacityModifyRGB
 * @return A value converted from C/C++ "bool"
 */
isOpacityModifyRGB : function () {},

/**
 * @method updateDisplayedOpacity
 * @param {unsigned char}
 */
updateDisplayedOpacity : function () {},

/**
 * @method initWithSpriteFrameName
 * @return A value converted from C/C++ "bool"
 * @param {const char*}
 */
initWithSpriteFrameName : function () {},

/**
 * @method setVertexZ
 * @param {float}
 */
setVertexZ : function () {},

/**
 * @method reorderChild
 * @param {cocos2d::Node*}
 * @param {int}
 */
reorderChild : function () {},

/**
 * @method isFrameDisplayed
 * @return A value converted from C/C++ "bool"
 * @param {cocos2d::SpriteFrame*}
 */
isFrameDisplayed : function () {},

/**
 * @method getAtlasIndex
 * @return A value converted from C/C++ "int"
 */
getAtlasIndex : function () {},

/**
 * @method setRotation
 * @param {float}
 */
setRotation : function () {},

/**
 * @method setDisplayFrame
 * @param {cocos2d::SpriteFrame*}
 */
setDisplayFrame : function () {},

/**
 * @method setBatchNode
 * @param {cocos2d::SpriteBatchNode*}
 */
setBatchNode : function () {},

/**
 * @method setScaleY
 * @param {float}
 */
setScaleY : function () {},

/**
 * @method setTextureAtlas
 * @param {cocos2d::TextureAtlas*}
 */
setTextureAtlas : function () {},

/**
 * @method setFlipY
 * @param {bool}
 */
setFlipY : function () {},

/**
 * @method setFlipX
 * @param {bool}
 */
setFlipX : function () {},

/**
 * @method removeAllChildrenWithCleanup
 * @param {bool}
 */
removeAllChildrenWithCleanup : function () {},

/**
 * @method isDirty
 * @return A value converted from C/C++ "bool"
 */
isDirty : function () {},

/**
 * @method setAtlasIndex
 * @param {int}
 */
setAtlasIndex : function () {},

/**
 * @method updateDisplayedColor
 * @param {cocos2d::Color3B}
 */
updateDisplayedColor : function () {},

/**
 * @method setDirty
 * @param {bool}
 */
setDirty : function () {},

/**
 * @method isTextureRectRotated
 * @return A value converted from C/C++ "bool"
 */
isTextureRectRotated : function () {},

/**
 * @method sortAllChildren
 */
sortAllChildren : function () {},

/**
 * @method getTextureRect
 * @return A value converted from C/C++ "cocos2d::Rect"
 */
getTextureRect : function () {},

/**
 * @method ignoreAnchorPointForPosition
 * @param {bool}
 */
ignoreAnchorPointForPosition : function () {},

/**
 * @method setColor
 * @param {cocos2d::Color3B}
 */
setColor : function () {},

/**
 * @method getTextureAtlas
 * @return A value converted from C/C++ "cocos2d::TextureAtlas*"
 */
getTextureAtlas : function () {},

/**
 * @method initWithSpriteFrame
 * @return A value converted from C/C++ "bool"
 * @param {cocos2d::SpriteFrame*}
 */
initWithSpriteFrame : function () {},

/**
 * @method removeChild
 * @param {cocos2d::Node*}
 * @param {bool}
 */
removeChild : function () {},

/**
 * @method updateTransform
 */
updateTransform : function () {},

/**
 * @method isFlipY
 * @return A value converted from C/C++ "bool"
 */
isFlipY : function () {},

/**
 * @method setOpacityModifyRGB
 * @param {bool}
 */
setOpacityModifyRGB : function () {},

/**
 * @method setVertexRect
 * @param {cocos2d::Rect}
 */
setVertexRect : function () {},

/**
 * @method setSkewX
 * @param {float}
 */
setSkewX : function () {},

/**
 * @method setSkewY
 * @param {float}
 */
setSkewY : function () {},

/**
 * @method setVisible
 * @param {bool}
 */
setVisible : function () {},

/**
 * @method createWithSpriteFrameName
 * @return A value converted from C/C++ "cocos2d::Sprite*"
 * @param {const char*}
 */
createWithSpriteFrameName : function () {},

/**
 * @method createWithSpriteFrame
 * @return A value converted from C/C++ "cocos2d::Sprite*"
 * @param {cocos2d::SpriteFrame*}
 */
createWithSpriteFrame : function () {},

/**
 * @method Sprite
 * @constructor
 */
Sprite : function () {},

};

/**
 * @class LabelTTF
 */
cc.LabelTTF = {

/**
 * @method enableShadow
 * @param {cocos2d::Size}
 * @param {float}
 * @param {float}
 * @param {bool}
 */
enableShadow : function () {},

/**
 * @method setDimensions
 * @param {cocos2d::Size}
 */
setDimensions : function () {},

/**
 * @method getFontSize
 * @return A value converted from C/C++ "float"
 */
getFontSize : function () {},

/**
 * @method getString
 * @return A value converted from C/C++ "const char*"
 */
getString : function () {},

/**
 * @method setTextDefinition
 * @param {cocos2d::FontDefinition}
 */
setTextDefinition : function () {},

/**
 * @method setFontName
 * @param {const char*}
 */
setFontName : function () {},

/**
 * @method getHorizontalAlignment
 * @return A value converted from C/C++ "cocos2d::TextHAlignment"
 */
getHorizontalAlignment : function () {},

/**
 * @method initWithStringAndTextDefinition
 * @return A value converted from C/C++ "bool"
 * @param {const char*}
 * @param {cocos2d::FontDefinition}
 */
initWithStringAndTextDefinition : function () {},

/**
 * @method setString
 * @param {const char*}
 */
setString : function () {},

/**
 * @method init
 * @return A value converted from C/C++ "bool"
 */
init : function () {},

/**
 * @method setFontFillColor
 * @param {cocos2d::Color3B}
 * @param {bool}
 */
setFontFillColor : function () {},

/**
 * @method enableStroke
 * @param {cocos2d::Color3B}
 * @param {float}
 * @param {bool}
 */
enableStroke : function () {},

/**
 * @method getDimensions
 * @return A value converted from C/C++ "cocos2d::Size"
 */
getDimensions : function () {},

/**
 * @method setVerticalAlignment
 * @param {cocos2d::TextVAlignment}
 */
setVerticalAlignment : function () {},

/**
 * @method setFontSize
 * @param {float}
 */
setFontSize : function () {},

/**
 * @method getVerticalAlignment
 * @return A value converted from C/C++ "cocos2d::TextVAlignment"
 */
getVerticalAlignment : function () {},

/**
 * @method getTextDefinition
 * @return A value converted from C/C++ "cocos2d::FontDefinition"
 */
getTextDefinition : function () {},

/**
 * @method getFontName
 * @return A value converted from C/C++ "const char*"
 */
getFontName : function () {},

/**
 * @method setHorizontalAlignment
 * @param {cocos2d::TextHAlignment}
 */
setHorizontalAlignment : function () {},

/**
 * @method disableShadow
 */
disableShadow : function () {},

/**
 * @method disableStroke
 */
disableStroke : function () {},

/**
 * @method createWithFontDefinition
 * @return A value converted from C/C++ "cocos2d::LabelTTF*"
 * @param {const char*}
 * @param {cocos2d::FontDefinition}
 */
createWithFontDefinition : function () {},

/**
 * @method LabelTTF
 * @constructor
 */
LabelTTF : function () {},

};

/**
 * @class SpriteBatchNode
 */
cc.SpriteBatchNode = {

/**
 * @method appendChild
 * @param {cocos2d::Sprite*}
 */
appendChild : function () {},

/**
 * @method reorderBatch
 * @param {bool}
 */
reorderBatch : function () {},

/**
 * @method visit
 */
visit : function () {},

/**
 * @method setTexture
 * @param {cocos2d::Texture2D*}
 */
setTexture : function () {},

/**
 * @method removeChildAtIndex
 * @param {unsigned int}
 * @param {bool}
 */
removeChildAtIndex : function () {},

/**
 * @method removeSpriteFromAtlas
 * @param {cocos2d::Sprite*}
 */
removeSpriteFromAtlas : function () {},

/**
 * @method atlasIndexForChild
 * @return A value converted from C/C++ "unsigned int"
 * @param {cocos2d::Sprite*}
 * @param {int}
 */
atlasIndexForChild : function () {},

/**
 * @method getTexture
 * @return A value converted from C/C++ "cocos2d::Texture2D*"
 */
getTexture : function () {},

/**
 * @method increaseAtlasCapacity
 */
increaseAtlasCapacity : function () {},

/**
 * @method insertChild
 * @param {cocos2d::Sprite*}
 * @param {unsigned int}
 */
insertChild : function () {},

/**
 * @method lowestAtlasIndexInChild
 * @return A value converted from C/C++ "unsigned int"
 * @param {cocos2d::Sprite*}
 */
lowestAtlasIndexInChild : function () {},

/**
 * @method draw
 */
draw : function () {},

/**
 * @method initWithTexture
 * @return A value converted from C/C++ "bool"
 * @param {cocos2d::Texture2D*}
 * @param {int}
 */
initWithTexture : function () {},

/**
 * @method setTextureAtlas
 * @param {cocos2d::TextureAtlas*}
 */
setTextureAtlas : function () {},

/**
 * @method removeAllChildrenWithCleanup
 * @param {bool}
 */
removeAllChildrenWithCleanup : function () {},

/**
 * @method sortAllChildren
 */
sortAllChildren : function () {},

/**
 * @method reorderChild
 * @param {cocos2d::Node*}
 * @param {int}
 */
reorderChild : function () {},

/**
 * @method rebuildIndexInOrder
 * @return A value converted from C/C++ "unsigned int"
 * @param {cocos2d::Sprite*}
 * @param {unsigned int}
 */
rebuildIndexInOrder : function () {},

/**
 * @method getTextureAtlas
 * @return A value converted from C/C++ "cocos2d::TextureAtlas*"
 */
getTextureAtlas : function () {},

/**
 * @method getDescendants
 * @return A value converted from C/C++ "cocos2d::Array*"
 */
getDescendants : function () {},

/**
 * @method removeChild
 * @param {cocos2d::Node*}
 * @param {bool}
 */
removeChild : function () {},

/**
 * @method highestAtlasIndexInChild
 * @return A value converted from C/C++ "unsigned int"
 * @param {cocos2d::Sprite*}
 */
highestAtlasIndexInChild : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::SpriteBatchNode*"
 * @param {const char*}
 * @param {int}
 */
create : function () {},

/**
 * @method createWithTexture
 * @return A value converted from C/C++ "cocos2d::SpriteBatchNode*"
 * @param {cocos2d::Texture2D*}
 * @param {int}
 */
createWithTexture : function () {},

/**
 * @method SpriteBatchNode
 * @constructor
 */
SpriteBatchNode : function () {},

};

/**
 * @class LabelBMFont
 */
cc.LabelBMFont = {

/**
 * @method setAnchorPoint
 * @param {cocos2d::Point}
 */
setAnchorPoint : function () {},

/**
 * @method createFontChars
 */
createFontChars : function () {},

/**
 * @method getString
 * @return A value converted from C/C++ "const char*"
 */
getString : function () {},

/**
 * @method setScale
 * @param {float}
 */
setScale : function () {},

/**
 * @method setOpacity
 * @param {unsigned char}
 */
setOpacity : function () {},

/**
 * @method setCascadeOpacityEnabled
 * @param {bool}
 */
setCascadeOpacityEnabled : function () {},

/**
 * @method getFntFile
 * @return A value converted from C/C++ "const char*"
 */
getFntFile : function () {},

/**
 * @method updateLabel
 */
updateLabel : function () {},

/**
 * @method setWidth
 * @param {float}
 */
setWidth : function () {},

/**
 * @method isOpacityModifyRGB
 * @return A value converted from C/C++ "bool"
 */
isOpacityModifyRGB : function () {},

/**
 * @method isCascadeOpacityEnabled
 * @return A value converted from C/C++ "bool"
 */
isCascadeOpacityEnabled : function () {},

/**
 * @method initWithString
 * @return A value converted from C/C++ "bool"
 * @param {const char*}
 * @param {const char*}
 * @param {float}
 * @param {cocos2d::TextHAlignment}
 * @param {cocos2d::Point}
 */
initWithString : function () {},

/**
 * @method setCascadeColorEnabled
 * @param {bool}
 */
setCascadeColorEnabled : function () {},

/**
 * @method setOpacityModifyRGB
 * @param {bool}
 */
setOpacityModifyRGB : function () {},

/**
 * @method updateDisplayedOpacity
 * @param {unsigned char}
 */
updateDisplayedOpacity : function () {},

/**
 * @method init
 * @return A value converted from C/C++ "bool"
 */
init : function () {},

/**
 * @method setFntFile
 * @param {const char*}
 */
setFntFile : function () {},

/**
 * @method getOpacity
 * @return A value converted from C/C++ "unsigned char"
 */
getOpacity : function () {},

/**
 * @method setLineBreakWithoutSpace
 * @param {bool}
 */
setLineBreakWithoutSpace : function () {},

/**
 * @method setScaleY
 * @param {float}
 */
setScaleY : function () {},

/**
 * @method setScaleX
 * @param {float}
 */
setScaleX : function () {},

/**
 * @method getColor
 * @return A value converted from C/C++ "cocos2d::Color3B"
 */
getColor : function () {},

/**
 * @method getDisplayedOpacity
 * @return A value converted from C/C++ "unsigned char"
 */
getDisplayedOpacity : function () {},

/**
 * @method isCascadeColorEnabled
 * @return A value converted from C/C++ "bool"
 */
isCascadeColorEnabled : function () {},

/**
 * @method setColor
 * @param {cocos2d::Color3B}
 */
setColor : function () {},

/**
 * @method setCString
 * @param {const char*}
 */
setCString : function () {},

/**
 * @method getDisplayedColor
 * @return A value converted from C/C++ "cocos2d::Color3B"
 */
getDisplayedColor : function () {},

/**
 * @method updateDisplayedColor
 * @param {cocos2d::Color3B}
 */
updateDisplayedColor : function () {},

/**
 * @method setAlignment
 * @param {cocos2d::TextHAlignment}
 */
setAlignment : function () {},

/**
 * @method purgeCachedData
 */
purgeCachedData : function () {},

/**
 * @method LabelBMFont
 * @constructor
 */
LabelBMFont : function () {},

};

/**
 * @class Label
 */
cc.Label = {

/**
 * @method setLineBreakWithoutSpace
 * @param {bool}
 */
setLineBreakWithoutSpace : function () {},

/**
 * @method setScaleY
 * @param {float}
 */
setScaleY : function () {},

/**
 * @method setScaleX
 * @param {float}
 */
setScaleX : function () {},

/**
 * @method setScale
 * @param {float}
 */
setScale : function () {},

/**
 * @method setAlignment
 * @param {cocos2d::TextHAlignment}
 */
setAlignment : function () {},

/**
 * @method setWidth
 * @param {float}
 */
setWidth : function () {},

/**
 * @method createWithBMFont
 * @return A value converted from C/C++ "cocos2d::Label*"
 * @param {const char*}
 * @param {const char*}
 * @param {int}
 */
createWithBMFont : function () {},

/**
 * @method createWithBMFontOLD
 * @return A value converted from C/C++ "cocos2d::Label*"
 * @param {const char*}
 * @param {const char*}
 * @param {int}
 */
createWithBMFontOLD : function () {},

/**
 * @method createWithTTF
 * @return A value converted from C/C++ "cocos2d::Label*"
 * @param {const char*}
 * @param {const char*}
 * @param {int}
 * @param {cocos2d::GlyphCollection}
 * @param {int}
 * @param {const char*}
 */
createWithTTF : function () {},

};

/**
 * @class Layer
 */
cc.Layer = {

/**
 * @method keyBackClicked
 */
keyBackClicked : function () {},

/**
 * @method ccTouchBegan
 * @return A value converted from C/C++ "bool"
 * @param {cocos2d::Touch*}
 * @param {cocos2d::Event*}
 */
ccTouchBegan : function () {},

/**
 * @method isKeyboardEnabled
 * @return A value converted from C/C++ "bool"
 */
isKeyboardEnabled : function () {},

/**
 * @method setAccelerometerInterval
 * @param {double}
 */
setAccelerometerInterval : function () {},

/**
 * @method ccTouchesCancelled
 * @param {cocos2d::Set*}
 * @param {cocos2d::Event*}
 */
ccTouchesCancelled : function () {},

/**
 * @method ccTouchesMoved
 * @param {cocos2d::Set*}
 * @param {cocos2d::Event*}
 */
ccTouchesMoved : function () {},

/**
 * @method isSwallowsTouches
 * @return A value converted from C/C++ "bool"
 */
isSwallowsTouches : function () {},

/**
 * @method getTouchMode
 * @return A value converted from C/C++ "cocos2d::Touch::DispatchMode"
 */
getTouchMode : function () {},

/**
 * @method setAccelerometerEnabled
 * @param {bool}
 */
setAccelerometerEnabled : function () {},

/**
 * @method init
 * @return A value converted from C/C++ "bool"
 */
init : function () {},

/**
 * @method isTouchEnabled
 * @return A value converted from C/C++ "bool"
 */
isTouchEnabled : function () {},

/**
 * @method ccTouchMoved
 * @param {cocos2d::Touch*}
 * @param {cocos2d::Event*}
 */
ccTouchMoved : function () {},

/**
 * @method setTouchEnabled
 * @param {bool}
 */
setTouchEnabled : function () {},

/**
 * @method setKeyboardEnabled
 * @param {bool}
 */
setKeyboardEnabled : function () {},

/**
 * @method isKeypadEnabled
 * @return A value converted from C/C++ "bool"
 */
isKeypadEnabled : function () {},

/**
 * @method ccTouchesEnded
 * @param {cocos2d::Set*}
 * @param {cocos2d::Event*}
 */
ccTouchesEnded : function () {},

/**
 * @method setTouchMode
 * @param {cocos2d::Touch::DispatchMode}
 */
setTouchMode : function () {},

/**
 * @method isAccelerometerEnabled
 * @return A value converted from C/C++ "bool"
 */
isAccelerometerEnabled : function () {},

/**
 * @method ccTouchEnded
 * @param {cocos2d::Touch*}
 * @param {cocos2d::Event*}
 */
ccTouchEnded : function () {},

/**
 * @method ccTouchCancelled
 * @param {cocos2d::Touch*}
 * @param {cocos2d::Event*}
 */
ccTouchCancelled : function () {},

/**
 * @method setSwallowsTouches
 * @param {bool}
 */
setSwallowsTouches : function () {},

/**
 * @method ccTouchesBegan
 * @param {cocos2d::Set*}
 * @param {cocos2d::Event*}
 */
ccTouchesBegan : function () {},

/**
 * @method setTouchPriority
 * @param {int}
 */
setTouchPriority : function () {},

/**
 * @method getTouchPriority
 * @return A value converted from C/C++ "int"
 */
getTouchPriority : function () {},

/**
 * @method setKeypadEnabled
 * @param {bool}
 */
setKeypadEnabled : function () {},

/**
 * @method registerWithTouchDispatcher
 */
registerWithTouchDispatcher : function () {},

/**
 * @method keyMenuClicked
 */
keyMenuClicked : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::Layer*"
 */
create : function () {},

/**
 * @method Layer
 * @constructor
 */
Layer : function () {},

};

/**
 * @class LayerRGBA
 */
cc.LayerRGBA = {

/**
 * @method updateDisplayedColor
 * @param {cocos2d::Color3B}
 */
updateDisplayedColor : function () {},

/**
 * @method setColor
 * @param {cocos2d::Color3B}
 */
setColor : function () {},

/**
 * @method isCascadeOpacityEnabled
 * @return A value converted from C/C++ "bool"
 */
isCascadeOpacityEnabled : function () {},

/**
 * @method getColor
 * @return A value converted from C/C++ "cocos2d::Color3B"
 */
getColor : function () {},

/**
 * @method getDisplayedOpacity
 * @return A value converted from C/C++ "unsigned char"
 */
getDisplayedOpacity : function () {},

/**
 * @method setCascadeColorEnabled
 * @param {bool}
 */
setCascadeColorEnabled : function () {},

/**
 * @method setOpacity
 * @param {unsigned char}
 */
setOpacity : function () {},

/**
 * @method setOpacityModifyRGB
 * @param {bool}
 */
setOpacityModifyRGB : function () {},

/**
 * @method setCascadeOpacityEnabled
 * @param {bool}
 */
setCascadeOpacityEnabled : function () {},

/**
 * @method updateDisplayedOpacity
 * @param {unsigned char}
 */
updateDisplayedOpacity : function () {},

/**
 * @method init
 * @return A value converted from C/C++ "bool"
 */
init : function () {},

/**
 * @method getOpacity
 * @return A value converted from C/C++ "unsigned char"
 */
getOpacity : function () {},

/**
 * @method isOpacityModifyRGB
 * @return A value converted from C/C++ "bool"
 */
isOpacityModifyRGB : function () {},

/**
 * @method isCascadeColorEnabled
 * @return A value converted from C/C++ "bool"
 */
isCascadeColorEnabled : function () {},

/**
 * @method getDisplayedColor
 * @return A value converted from C/C++ "cocos2d::Color3B"
 */
getDisplayedColor : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::LayerRGBA*"
 */
create : function () {},

/**
 * @method LayerRGBA
 * @constructor
 */
LayerRGBA : function () {},

};

/**
 * @class LayerColor
 */
cc.LayerColor = {

/**
 * @method changeWidthAndHeight
 * @param {float}
 * @param {float}
 */
changeWidthAndHeight : function () {},

/**
 * @method setColor
 * @param {cocos2d::Color3B}
 */
setColor : function () {},

/**
 * @method draw
 */
draw : function () {},

/**
 * @method setOpacity
 * @param {unsigned char}
 */
setOpacity : function () {},

/**
 * @method changeWidth
 * @param {float}
 */
changeWidth : function () {},

/**
 * @method setContentSize
 * @param {cocos2d::Size}
 */
setContentSize : function () {},

/**
 * @method changeHeight
 * @param {float}
 */
changeHeight : function () {},

/**
 * @method LayerColor
 * @constructor
 */
LayerColor : function () {},

};

/**
 * @class LayerGradient
 */
cc.LayerGradient = {

/**
 * @method getStartColor
 * @return A value converted from C/C++ "cocos2d::Color3B"
 */
getStartColor : function () {},

/**
 * @method isCompressedInterpolation
 * @return A value converted from C/C++ "bool"
 */
isCompressedInterpolation : function () {},

/**
 * @method getStartOpacity
 * @return A value converted from C/C++ "unsigned char"
 */
getStartOpacity : function () {},

/**
 * @method setVector
 * @param {cocos2d::Point}
 */
setVector : function () {},

/**
 * @method setStartOpacity
 * @param {unsigned char}
 */
setStartOpacity : function () {},

/**
 * @method setCompressedInterpolation
 * @param {bool}
 */
setCompressedInterpolation : function () {},

/**
 * @method setEndOpacity
 * @param {unsigned char}
 */
setEndOpacity : function () {},

/**
 * @method getVector
 * @return A value converted from C/C++ "cocos2d::Point"
 */
getVector : function () {},

/**
 * @method setEndColor
 * @param {cocos2d::Color3B}
 */
setEndColor : function () {},

/**
 * @method getEndColor
 * @return A value converted from C/C++ "cocos2d::Color3B"
 */
getEndColor : function () {},

/**
 * @method getEndOpacity
 * @return A value converted from C/C++ "unsigned char"
 */
getEndOpacity : function () {},

/**
 * @method setStartColor
 * @param {cocos2d::Color3B}
 */
setStartColor : function () {},

};

/**
 * @class LayerMultiplex
 */
cc.LayerMultiplex = {

/**
 * @method initWithArray
 * @return A value converted from C/C++ "bool"
 * @param {cocos2d::Array*}
 */
initWithArray : function () {},

/**
 * @method switchToAndReleaseMe
 * @param {unsigned int}
 */
switchToAndReleaseMe : function () {},

/**
 * @method addLayer
 * @param {cocos2d::Layer*}
 */
addLayer : function () {},

/**
 * @method switchTo
 * @param {unsigned int}
 */
switchTo : function () {},

/**
 * @method LayerMultiplex
 * @constructor
 */
LayerMultiplex : function () {},

};

/**
 * @class Scene
 */
cc.Scene = {

/**
 * @method init
 * @return A value converted from C/C++ "bool"
 */
init : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::Scene*"
 */
create : function () {},

/**
 * @method Scene
 * @constructor
 */
Scene : function () {},

};

/**
 * @class TransitionEaseScene
 */
cc.TransitionEaseScene = {

/**
 * @method easeActionWithAction
 * @return A value converted from C/C++ "cocos2d::ActionInterval*"
 * @param {cocos2d::ActionInterval*}
 */
easeActionWithAction : function () {},

};

/**
 * @class TransitionScene
 */
cc.TransitionScene = {

/**
 * @method draw
 */
draw : function () {},

/**
 * @method finish
 */
finish : function () {},

/**
 * @method initWithDuration
 * @return A value converted from C/C++ "bool"
 * @param {float}
 * @param {cocos2d::Scene*}
 */
initWithDuration : function () {},

/**
 * @method cleanup
 */
cleanup : function () {},

/**
 * @method hideOutShowIn
 */
hideOutShowIn : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::TransitionScene*"
 * @param {float}
 * @param {cocos2d::Scene*}
 */
create : function () {},

/**
 * @method TransitionScene
 * @constructor
 */
TransitionScene : function () {},

};

/**
 * @class TransitionSceneOriented
 */
cc.TransitionSceneOriented = {

/**
 * @method initWithDuration
 * @return A value converted from C/C++ "bool"
 * @param {float}
 * @param {cocos2d::Scene*}
 * @param {cocos2d::TransitionScene::Orientation}
 */
initWithDuration : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::TransitionSceneOriented*"
 * @param {float}
 * @param {cocos2d::Scene*}
 * @param {cocos2d::TransitionScene::Orientation}
 */
create : function () {},

/**
 * @method TransitionSceneOriented
 * @constructor
 */
TransitionSceneOriented : function () {},

};

/**
 * @class TransitionRotoZoom
 */
cc.TransitionRotoZoom = {

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::TransitionRotoZoom*"
 * @param {float}
 * @param {cocos2d::Scene*}
 */
create : function () {},

/**
 * @method TransitionRotoZoom
 * @constructor
 */
TransitionRotoZoom : function () {},

};

/**
 * @class TransitionJumpZoom
 */
cc.TransitionJumpZoom = {

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::TransitionJumpZoom*"
 * @param {float}
 * @param {cocos2d::Scene*}
 */
create : function () {},

/**
 * @method TransitionJumpZoom
 * @constructor
 */
TransitionJumpZoom : function () {},

};

/**
 * @class TransitionMoveInL
 */
cc.TransitionMoveInL = {

/**
 * @method action
 * @return A value converted from C/C++ "cocos2d::ActionInterval*"
 */
action : function () {},

/**
 * @method easeActionWithAction
 * @return A value converted from C/C++ "cocos2d::ActionInterval*"
 * @param {cocos2d::ActionInterval*}
 */
easeActionWithAction : function () {},

/**
 * @method initScenes
 */
initScenes : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::TransitionMoveInL*"
 * @param {float}
 * @param {cocos2d::Scene*}
 */
create : function () {},

/**
 * @method TransitionMoveInL
 * @constructor
 */
TransitionMoveInL : function () {},

};

/**
 * @class TransitionMoveInR
 */
cc.TransitionMoveInR = {

/**
 * @method initScenes
 */
initScenes : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::TransitionMoveInR*"
 * @param {float}
 * @param {cocos2d::Scene*}
 */
create : function () {},

/**
 * @method TransitionMoveInR
 * @constructor
 */
TransitionMoveInR : function () {},

};

/**
 * @class TransitionMoveInT
 */
cc.TransitionMoveInT = {

/**
 * @method initScenes
 */
initScenes : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::TransitionMoveInT*"
 * @param {float}
 * @param {cocos2d::Scene*}
 */
create : function () {},

/**
 * @method TransitionMoveInT
 * @constructor
 */
TransitionMoveInT : function () {},

};

/**
 * @class TransitionMoveInB
 */
cc.TransitionMoveInB = {

/**
 * @method initScenes
 */
initScenes : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::TransitionMoveInB*"
 * @param {float}
 * @param {cocos2d::Scene*}
 */
create : function () {},

/**
 * @method TransitionMoveInB
 * @constructor
 */
TransitionMoveInB : function () {},

};

/**
 * @class TransitionSlideInL
 */
cc.TransitionSlideInL = {

/**
 * @method action
 * @return A value converted from C/C++ "cocos2d::ActionInterval*"
 */
action : function () {},

/**
 * @method easeActionWithAction
 * @return A value converted from C/C++ "cocos2d::ActionInterval*"
 * @param {cocos2d::ActionInterval*}
 */
easeActionWithAction : function () {},

/**
 * @method initScenes
 */
initScenes : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::TransitionSlideInL*"
 * @param {float}
 * @param {cocos2d::Scene*}
 */
create : function () {},

/**
 * @method TransitionSlideInL
 * @constructor
 */
TransitionSlideInL : function () {},

};

/**
 * @class TransitionSlideInR
 */
cc.TransitionSlideInR = {

/**
 * @method action
 * @return A value converted from C/C++ "cocos2d::ActionInterval*"
 */
action : function () {},

/**
 * @method initScenes
 */
initScenes : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::TransitionSlideInR*"
 * @param {float}
 * @param {cocos2d::Scene*}
 */
create : function () {},

/**
 * @method TransitionSlideInR
 * @constructor
 */
TransitionSlideInR : function () {},

};

/**
 * @class TransitionSlideInB
 */
cc.TransitionSlideInB = {

/**
 * @method action
 * @return A value converted from C/C++ "cocos2d::ActionInterval*"
 */
action : function () {},

/**
 * @method initScenes
 */
initScenes : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::TransitionSlideInB*"
 * @param {float}
 * @param {cocos2d::Scene*}
 */
create : function () {},

/**
 * @method TransitionSlideInB
 * @constructor
 */
TransitionSlideInB : function () {},

};

/**
 * @class TransitionSlideInT
 */
cc.TransitionSlideInT = {

/**
 * @method action
 * @return A value converted from C/C++ "cocos2d::ActionInterval*"
 */
action : function () {},

/**
 * @method initScenes
 */
initScenes : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::TransitionSlideInT*"
 * @param {float}
 * @param {cocos2d::Scene*}
 */
create : function () {},

/**
 * @method TransitionSlideInT
 * @constructor
 */
TransitionSlideInT : function () {},

};

/**
 * @class TransitionShrinkGrow
 */
cc.TransitionShrinkGrow = {

/**
 * @method easeActionWithAction
 * @return A value converted from C/C++ "cocos2d::ActionInterval*"
 * @param {cocos2d::ActionInterval*}
 */
easeActionWithAction : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::TransitionShrinkGrow*"
 * @param {float}
 * @param {cocos2d::Scene*}
 */
create : function () {},

/**
 * @method TransitionShrinkGrow
 * @constructor
 */
TransitionShrinkGrow : function () {},

};

/**
 * @class TransitionFlipX
 */
cc.TransitionFlipX = {

/**
 * @method TransitionFlipX
 * @constructor
 */
TransitionFlipX : function () {},

};

/**
 * @class TransitionFlipY
 */
cc.TransitionFlipY = {

/**
 * @method TransitionFlipY
 * @constructor
 */
TransitionFlipY : function () {},

};

/**
 * @class TransitionFlipAngular
 */
cc.TransitionFlipAngular = {

/**
 * @method TransitionFlipAngular
 * @constructor
 */
TransitionFlipAngular : function () {},

};

/**
 * @class TransitionZoomFlipX
 */
cc.TransitionZoomFlipX = {

/**
 * @method TransitionZoomFlipX
 * @constructor
 */
TransitionZoomFlipX : function () {},

};

/**
 * @class TransitionZoomFlipY
 */
cc.TransitionZoomFlipY = {

/**
 * @method TransitionZoomFlipY
 * @constructor
 */
TransitionZoomFlipY : function () {},

};

/**
 * @class TransitionZoomFlipAngular
 */
cc.TransitionZoomFlipAngular = {

/**
 * @method TransitionZoomFlipAngular
 * @constructor
 */
TransitionZoomFlipAngular : function () {},

};

/**
 * @class TransitionFade
 */
cc.TransitionFade = {

/**
 * @method TransitionFade
 * @constructor
 */
TransitionFade : function () {},

};

/**
 * @class TransitionCrossFade
 */
cc.TransitionCrossFade = {

/**
 * @method draw
 */
draw : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::TransitionCrossFade*"
 * @param {float}
 * @param {cocos2d::Scene*}
 */
create : function () {},

/**
 * @method TransitionCrossFade
 * @constructor
 */
TransitionCrossFade : function () {},

};

/**
 * @class TransitionTurnOffTiles
 */
cc.TransitionTurnOffTiles = {

/**
 * @method easeActionWithAction
 * @return A value converted from C/C++ "cocos2d::ActionInterval*"
 * @param {cocos2d::ActionInterval*}
 */
easeActionWithAction : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::TransitionTurnOffTiles*"
 * @param {float}
 * @param {cocos2d::Scene*}
 */
create : function () {},

/**
 * @method TransitionTurnOffTiles
 * @constructor
 */
TransitionTurnOffTiles : function () {},

};

/**
 * @class TransitionSplitCols
 */
cc.TransitionSplitCols = {

/**
 * @method action
 * @return A value converted from C/C++ "cocos2d::ActionInterval*"
 */
action : function () {},

/**
 * @method easeActionWithAction
 * @return A value converted from C/C++ "cocos2d::ActionInterval*"
 * @param {cocos2d::ActionInterval*}
 */
easeActionWithAction : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::TransitionSplitCols*"
 * @param {float}
 * @param {cocos2d::Scene*}
 */
create : function () {},

/**
 * @method TransitionSplitCols
 * @constructor
 */
TransitionSplitCols : function () {},

};

/**
 * @class TransitionSplitRows
 */
cc.TransitionSplitRows = {

/**
 * @method action
 * @return A value converted from C/C++ "cocos2d::ActionInterval*"
 */
action : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::TransitionSplitRows*"
 * @param {float}
 * @param {cocos2d::Scene*}
 */
create : function () {},

/**
 * @method TransitionSplitRows
 * @constructor
 */
TransitionSplitRows : function () {},

};

/**
 * @class TransitionFadeTR
 */
cc.TransitionFadeTR = {

/**
 * @method easeActionWithAction
 * @return A value converted from C/C++ "cocos2d::ActionInterval*"
 * @param {cocos2d::ActionInterval*}
 */
easeActionWithAction : function () {},

/**
 * @method actionWithSize
 * @return A value converted from C/C++ "cocos2d::ActionInterval*"
 * @param {cocos2d::Size}
 */
actionWithSize : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::TransitionFadeTR*"
 * @param {float}
 * @param {cocos2d::Scene*}
 */
create : function () {},

/**
 * @method TransitionFadeTR
 * @constructor
 */
TransitionFadeTR : function () {},

};

/**
 * @class TransitionFadeBL
 */
cc.TransitionFadeBL = {

/**
 * @method actionWithSize
 * @return A value converted from C/C++ "cocos2d::ActionInterval*"
 * @param {cocos2d::Size}
 */
actionWithSize : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::TransitionFadeBL*"
 * @param {float}
 * @param {cocos2d::Scene*}
 */
create : function () {},

/**
 * @method TransitionFadeBL
 * @constructor
 */
TransitionFadeBL : function () {},

};

/**
 * @class TransitionFadeUp
 */
cc.TransitionFadeUp = {

/**
 * @method actionWithSize
 * @return A value converted from C/C++ "cocos2d::ActionInterval*"
 * @param {cocos2d::Size}
 */
actionWithSize : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::TransitionFadeUp*"
 * @param {float}
 * @param {cocos2d::Scene*}
 */
create : function () {},

/**
 * @method TransitionFadeUp
 * @constructor
 */
TransitionFadeUp : function () {},

};

/**
 * @class TransitionFadeDown
 */
cc.TransitionFadeDown = {

/**
 * @method actionWithSize
 * @return A value converted from C/C++ "cocos2d::ActionInterval*"
 * @param {cocos2d::Size}
 */
actionWithSize : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::TransitionFadeDown*"
 * @param {float}
 * @param {cocos2d::Scene*}
 */
create : function () {},

/**
 * @method TransitionFadeDown
 * @constructor
 */
TransitionFadeDown : function () {},

};

/**
 * @class TransitionPageTurn
 */
cc.TransitionPageTurn = {

/**
 * @method actionWithSize
 * @return A value converted from C/C++ "cocos2d::ActionInterval*"
 * @param {cocos2d::Size}
 */
actionWithSize : function () {},

/**
 * @method initWithDuration
 * @return A value converted from C/C++ "bool"
 * @param {float}
 * @param {cocos2d::Scene*}
 * @param {bool}
 */
initWithDuration : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::TransitionPageTurn*"
 * @param {float}
 * @param {cocos2d::Scene*}
 * @param {bool}
 */
create : function () {},

/**
 * @method TransitionPageTurn
 * @constructor
 */
TransitionPageTurn : function () {},

};

/**
 * @class TransitionProgress
 */
cc.TransitionProgress = {

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::TransitionProgress*"
 * @param {float}
 * @param {cocos2d::Scene*}
 */
create : function () {},

/**
 * @method TransitionProgress
 * @constructor
 */
TransitionProgress : function () {},

};

/**
 * @class TransitionProgressRadialCCW
 */
cc.TransitionProgressRadialCCW = {

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::TransitionProgressRadialCCW*"
 * @param {float}
 * @param {cocos2d::Scene*}
 */
create : function () {},

};

/**
 * @class TransitionProgressRadialCW
 */
cc.TransitionProgressRadialCW = {

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::TransitionProgressRadialCW*"
 * @param {float}
 * @param {cocos2d::Scene*}
 */
create : function () {},

};

/**
 * @class TransitionProgressHorizontal
 */
cc.TransitionProgressHorizontal = {

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::TransitionProgressHorizontal*"
 * @param {float}
 * @param {cocos2d::Scene*}
 */
create : function () {},

};

/**
 * @class TransitionProgressVertical
 */
cc.TransitionProgressVertical = {

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::TransitionProgressVertical*"
 * @param {float}
 * @param {cocos2d::Scene*}
 */
create : function () {},

};

/**
 * @class TransitionProgressInOut
 */
cc.TransitionProgressInOut = {

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::TransitionProgressInOut*"
 * @param {float}
 * @param {cocos2d::Scene*}
 */
create : function () {},

};

/**
 * @class TransitionProgressOutIn
 */
cc.TransitionProgressOutIn = {

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::TransitionProgressOutIn*"
 * @param {float}
 * @param {cocos2d::Scene*}
 */
create : function () {},

};

/**
 * @class MenuItem
 */
cc.MenuItem = {

/**
 * @method setEnabled
 * @param {bool}
 */
setEnabled : function () {},

/**
 * @method activate
 */
activate : function () {},

/**
 * @method isEnabled
 * @return A value converted from C/C++ "bool"
 */
isEnabled : function () {},

/**
 * @method isSelected
 * @return A value converted from C/C++ "bool"
 */
isSelected : function () {},

/**
 * @method selected
 */
selected : function () {},

/**
 * @method unselected
 */
unselected : function () {},

/**
 * @method rect
 * @return A value converted from C/C++ "cocos2d::Rect"
 */
rect : function () {},

/**
 * @method MenuItem
 * @constructor
 */
MenuItem : function () {},

};

/**
 * @class MenuItemLabel
 */
cc.MenuItemLabel = {

/**
 * @method setEnabled
 * @param {bool}
 */
setEnabled : function () {},

/**
 * @method setLabel
 * @param {cocos2d::Node*}
 */
setLabel : function () {},

/**
 * @method activate
 */
activate : function () {},

/**
 * @method getDisabledColor
 * @return A value converted from C/C++ "cocos2d::Color3B"
 */
getDisabledColor : function () {},

/**
 * @method setString
 * @param {const char*}
 */
setString : function () {},

/**
 * @method selected
 */
selected : function () {},

/**
 * @method initWithLabel
 * @return A value converted from C/C++ "bool"
 * @param {cocos2d::Node*}
 * @param {cocos2d::ccMenuCallback}
 */
initWithLabel : function () {},

/**
 * @method setDisabledColor
 * @param {cocos2d::Color3B}
 */
setDisabledColor : function () {},

/**
 * @method getLabel
 * @return A value converted from C/C++ "cocos2d::Node*"
 */
getLabel : function () {},

/**
 * @method unselected
 */
unselected : function () {},

/**
 * @method MenuItemLabel
 * @constructor
 */
MenuItemLabel : function () {},

};

/**
 * @class MenuItemAtlasFont
 */
cc.MenuItemAtlasFont = {

/**
 * @method initWithString
 * @return A value converted from C/C++ "bool"
 * @param {const char*}
 * @param {const char*}
 * @param {int}
 * @param {int}
 * @param {char}
 * @param {cocos2d::ccMenuCallback}
 */
initWithString : function () {},

/**
 * @method MenuItemAtlasFont
 * @constructor
 */
MenuItemAtlasFont : function () {},

};

/**
 * @class MenuItemFont
 */
cc.MenuItemFont = {

/**
 * @method setFontNameObj
 * @param {const char*}
 */
setFontNameObj : function () {},

/**
 * @method getFontSizeObj
 * @return A value converted from C/C++ "unsigned int"
 */
getFontSizeObj : function () {},

/**
 * @method initWithString
 * @return A value converted from C/C++ "bool"
 * @param {const char*}
 * @param {cocos2d::ccMenuCallback}
 */
initWithString : function () {},

/**
 * @method setFontSizeObj
 * @param {unsigned int}
 */
setFontSizeObj : function () {},

/**
 * @method getFontNameObj
 * @return A value converted from C/C++ "const char*"
 */
getFontNameObj : function () {},

/**
 * @method setFontName
 * @param {const char*}
 */
setFontName : function () {},

/**
 * @method getFontSize
 * @return A value converted from C/C++ "unsigned int"
 */
getFontSize : function () {},

/**
 * @method getFontName
 * @return A value converted from C/C++ "const char*"
 */
getFontName : function () {},

/**
 * @method setFontSize
 * @param {unsigned int}
 */
setFontSize : function () {},

/**
 * @method MenuItemFont
 * @constructor
 */
MenuItemFont : function () {},

};

/**
 * @class MenuItemSprite
 */
cc.MenuItemSprite = {

/**
 * @method setEnabled
 * @param {bool}
 */
setEnabled : function () {},

/**
 * @method selected
 */
selected : function () {},

/**
 * @method setNormalImage
 * @param {cocos2d::Node*}
 */
setNormalImage : function () {},

/**
 * @method setDisabledImage
 * @param {cocos2d::Node*}
 */
setDisabledImage : function () {},

/**
 * @method initWithNormalSprite
 * @return A value converted from C/C++ "bool"
 * @param {cocos2d::Node*}
 * @param {cocos2d::Node*}
 * @param {cocos2d::Node*}
 * @param {cocos2d::ccMenuCallback}
 */
initWithNormalSprite : function () {},

/**
 * @method setSelectedImage
 * @param {cocos2d::Node*}
 */
setSelectedImage : function () {},

/**
 * @method getDisabledImage
 * @return A value converted from C/C++ "cocos2d::Node*"
 */
getDisabledImage : function () {},

/**
 * @method getSelectedImage
 * @return A value converted from C/C++ "cocos2d::Node*"
 */
getSelectedImage : function () {},

/**
 * @method getNormalImage
 * @return A value converted from C/C++ "cocos2d::Node*"
 */
getNormalImage : function () {},

/**
 * @method unselected
 */
unselected : function () {},

/**
 * @method MenuItemSprite
 * @constructor
 */
MenuItemSprite : function () {},

};

/**
 * @class MenuItemImage
 */
cc.MenuItemImage = {

/**
 * @method setDisabledSpriteFrame
 * @param {cocos2d::SpriteFrame*}
 */
setDisabledSpriteFrame : function () {},

/**
 * @method setSelectedSpriteFrame
 * @param {cocos2d::SpriteFrame*}
 */
setSelectedSpriteFrame : function () {},

/**
 * @method setNormalSpriteFrame
 * @param {cocos2d::SpriteFrame*}
 */
setNormalSpriteFrame : function () {},

/**
 * @method init
 * @return A value converted from C/C++ "bool"
 */
init : function () {},

/**
 * @method initWithNormalImage
 * @return A value converted from C/C++ "bool"
 * @param {const char*}
 * @param {const char*}
 * @param {const char*}
 * @param {cocos2d::ccMenuCallback}
 */
initWithNormalImage : function () {},

/**
 * @method MenuItemImage
 * @constructor
 */
MenuItemImage : function () {},

};

/**
 * @class MenuItemToggle
 */
cc.MenuItemToggle = {

/**
 * @method setSubItems
 * @param {cocos2d::Array*}
 */
setSubItems : function () {},

/**
 * @method initWithItem
 * @return A value converted from C/C++ "bool"
 * @param {cocos2d::MenuItem*}
 */
initWithItem : function () {},

/**
 * @method setSelectedIndex
 * @param {unsigned int}
 */
setSelectedIndex : function () {},

/**
 * @method setEnabled
 * @param {bool}
 */
setEnabled : function () {},

/**
 * @method getSelectedIndex
 * @return A value converted from C/C++ "unsigned int"
 */
getSelectedIndex : function () {},

/**
 * @method addSubItem
 * @param {cocos2d::MenuItem*}
 */
addSubItem : function () {},

/**
 * @method activate
 */
activate : function () {},

/**
 * @method selected
 */
selected : function () {},

/**
 * @method unselected
 */
unselected : function () {},

/**
 * @method getSelectedItem
 * @return A value converted from C/C++ "cocos2d::MenuItem*"
 */
getSelectedItem : function () {},

/**
 * @method MenuItemToggle
 * @constructor
 */
MenuItemToggle : function () {},

};

/**
 * @class Menu
 */
cc.Menu = {

/**
 * @method initWithArray
 * @return A value converted from C/C++ "bool"
 * @param {cocos2d::Array*}
 */
initWithArray : function () {},

/**
 * @method alignItemsVertically
 */
alignItemsVertically : function () {},

/**
 * @method ccTouchBegan
 * @return A value converted from C/C++ "bool"
 * @param {cocos2d::Touch*}
 * @param {cocos2d::Event*}
 */
ccTouchBegan : function () {},

/**
 * @method ccTouchEnded
 * @param {cocos2d::Touch*}
 * @param {cocos2d::Event*}
 */
ccTouchEnded : function () {},

/**
 * @method isOpacityModifyRGB
 * @return A value converted from C/C++ "bool"
 */
isOpacityModifyRGB : function () {},

/**
 * @method isEnabled
 * @return A value converted from C/C++ "bool"
 */
isEnabled : function () {},

/**
 * @method setOpacityModifyRGB
 * @param {bool}
 */
setOpacityModifyRGB : function () {},

/**
 * @method setHandlerPriority
 * @param {int}
 */
setHandlerPriority : function () {},

/**
 * @method init
 * @return A value converted from C/C++ "bool"
 */
init : function () {},

/**
 * @method alignItemsHorizontallyWithPadding
 * @param {float}
 */
alignItemsHorizontallyWithPadding : function () {},

/**
 * @method alignItemsHorizontally
 */
alignItemsHorizontally : function () {},

/**
 * @method setEnabled
 * @param {bool}
 */
setEnabled : function () {},

/**
 * @method ccTouchMoved
 * @param {cocos2d::Touch*}
 * @param {cocos2d::Event*}
 */
ccTouchMoved : function () {},

/**
 * @method ccTouchCancelled
 * @param {cocos2d::Touch*}
 * @param {cocos2d::Event*}
 */
ccTouchCancelled : function () {},

/**
 * @method removeChild
 * @param {cocos2d::Node*}
 * @param {bool}
 */
removeChild : function () {},

/**
 * @method alignItemsVerticallyWithPadding
 * @param {float}
 */
alignItemsVerticallyWithPadding : function () {},

/**
 * @method registerWithTouchDispatcher
 */
registerWithTouchDispatcher : function () {},

/**
 * @method Menu
 * @constructor
 */
Menu : function () {},

};

/**
 * @class ClippingNode
 */
cc.ClippingNode = {

/**
 * @method isInverted
 * @return A value converted from C/C++ "bool"
 */
isInverted : function () {},

/**
 * @method visit
 */
visit : function () {},

/**
 * @method setInverted
 * @param {bool}
 */
setInverted : function () {},

/**
 * @method setStencil
 * @param {cocos2d::Node*}
 */
setStencil : function () {},

/**
 * @method getAlphaThreshold
 * @return A value converted from C/C++ "float"
 */
getAlphaThreshold : function () {},

/**
 * @method getStencil
 * @return A value converted from C/C++ "cocos2d::Node*"
 */
getStencil : function () {},

/**
 * @method setAlphaThreshold
 * @param {float}
 */
setAlphaThreshold : function () {},

};

/**
 * @class MotionStreak
 */
cc.MotionStreak = {

/**
 * @method reset
 */
reset : function () {},

/**
 * @method getOpacity
 * @return A value converted from C/C++ "unsigned char"
 */
getOpacity : function () {},

/**
 * @method setTexture
 * @param {cocos2d::Texture2D*}
 */
setTexture : function () {},

/**
 * @method isOpacityModifyRGB
 * @return A value converted from C/C++ "bool"
 */
isOpacityModifyRGB : function () {},

/**
 * @method setOpacity
 * @param {unsigned char}
 */
setOpacity : function () {},

/**
 * @method getTexture
 * @return A value converted from C/C++ "cocos2d::Texture2D*"
 */
getTexture : function () {},

/**
 * @method tintWithColor
 * @param {cocos2d::Color3B}
 */
tintWithColor : function () {},

/**
 * @method setStartingPositionInitialized
 * @param {bool}
 */
setStartingPositionInitialized : function () {},

/**
 * @method isFastMode
 * @return A value converted from C/C++ "bool"
 */
isFastMode : function () {},

/**
 * @method setOpacityModifyRGB
 * @param {bool}
 */
setOpacityModifyRGB : function () {},

/**
 * @method isStartingPositionInitialized
 * @return A value converted from C/C++ "bool"
 */
isStartingPositionInitialized : function () {},

/**
 * @method setPosition
 * @param {cocos2d::Point}
 */
setPosition : function () {},

/**
 * @method setFastMode
 * @param {bool}
 */
setFastMode : function () {},

/**
 * @method MotionStreak
 * @constructor
 */
MotionStreak : function () {},

};

/**
 * @class ProgressTimer
 */
cc.ProgressTimer = {

/**
 * @method setAnchorPoint
 * @param {cocos2d::Point}
 */
setAnchorPoint : function () {},

/**
 * @method draw
 */
draw : function () {},

/**
 * @method isReverseDirection
 * @return A value converted from C/C++ "bool"
 */
isReverseDirection : function () {},

/**
 * @method setBarChangeRate
 * @param {cocos2d::Point}
 */
setBarChangeRate : function () {},

/**
 * @method getPercentage
 * @return A value converted from C/C++ "float"
 */
getPercentage : function () {},

/**
 * @method setSprite
 * @param {cocos2d::Sprite*}
 */
setSprite : function () {},

/**
 * @method getType
 * @return A value converted from C/C++ "cocos2d::ProgressTimer::Type"
 */
getType : function () {},

/**
 * @method getOpacity
 * @return A value converted from C/C++ "unsigned char"
 */
getOpacity : function () {},

/**
 * @method setOpacity
 * @param {unsigned char}
 */
setOpacity : function () {},

/**
 * @method getSprite
 * @return A value converted from C/C++ "cocos2d::Sprite*"
 */
getSprite : function () {},

/**
 * @method setMidpoint
 * @param {cocos2d::Point}
 */
setMidpoint : function () {},

/**
 * @method getMidpoint
 * @return A value converted from C/C++ "cocos2d::Point"
 */
getMidpoint : function () {},

/**
 * @method getColor
 * @return A value converted from C/C++ "cocos2d::Color3B"
 */
getColor : function () {},

/**
 * @method getBarChangeRate
 * @return A value converted from C/C++ "cocos2d::Point"
 */
getBarChangeRate : function () {},

/**
 * @method initWithSprite
 * @return A value converted from C/C++ "bool"
 * @param {cocos2d::Sprite*}
 */
initWithSprite : function () {},

/**
 * @method setColor
 * @param {cocos2d::Color3B}
 */
setColor : function () {},

/**
 * @method setPercentage
 * @param {float}
 */
setPercentage : function () {},

/**
 * @method setType
 * @param {cocos2d::ProgressTimer::Type}
 */
setType : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::ProgressTimer*"
 * @param {cocos2d::Sprite*}
 */
create : function () {},

/**
 * @method ProgressTimer
 * @constructor
 */
ProgressTimer : function () {},

};

/**
 * @class RenderTexture
 */
cc.RenderTexture = {

/**
 * @method clearStencil
 * @param {int}
 */
clearStencil : function () {},

/**
 * @method draw
 */
draw : function () {},

/**
 * @method listenToForeground
 * @param {cocos2d::Object*}
 */
listenToForeground : function () {},

/**
 * @method getClearDepth
 * @return A value converted from C/C++ "float"
 */
getClearDepth : function () {},

/**
 * @method getClearStencil
 * @return A value converted from C/C++ "int"
 */
getClearStencil : function () {},

/**
 * @method end
 */
end : function () {},

/**
 * @method setClearStencil
 * @param {int}
 */
setClearStencil : function () {},

/**
 * @method visit
 */
visit : function () {},

/**
 * @method getSprite
 * @return A value converted from C/C++ "cocos2d::Sprite*"
 */
getSprite : function () {},

/**
 * @method isAutoDraw
 * @return A value converted from C/C++ "bool"
 */
isAutoDraw : function () {},

/**
 * @method setClearFlags
 * @param {unsigned int}
 */
setClearFlags : function () {},

/**
 * @method begin
 */
begin : function () {},

/**
 * @method setAutoDraw
 * @param {bool}
 */
setAutoDraw : function () {},

/**
 * @method setClearColor
 * @param {cocos2d::Color4F}
 */
setClearColor : function () {},

/**
 * @method endToLua
 */
endToLua : function () {},

/**
 * @method clearDepth
 * @param {float}
 */
clearDepth : function () {},

/**
 * @method getClearColor
 * @return A value converted from C/C++ "cocos2d::Color4F"
 */
getClearColor : function () {},

/**
 * @method listenToBackground
 * @param {cocos2d::Object*}
 */
listenToBackground : function () {},

/**
 * @method clear
 * @param {float}
 * @param {float}
 * @param {float}
 * @param {float}
 */
clear : function () {},

/**
 * @method getClearFlags
 * @return A value converted from C/C++ "unsigned int"
 */
getClearFlags : function () {},

/**
 * @method newImage
 * @return A value converted from C/C++ "cocos2d::Image*"
 */
newImage : function () {},

/**
 * @method setClearDepth
 * @param {float}
 */
setClearDepth : function () {},

/**
 * @method setSprite
 * @param {cocos2d::Sprite*}
 */
setSprite : function () {},

/**
 * @method RenderTexture
 * @constructor
 */
RenderTexture : function () {},

};

/**
 * @class ParticleBatchNode
 */
cc.ParticleBatchNode = {

/**
 * @method draw
 */
draw : function () {},

/**
 * @method setTexture
 * @param {cocos2d::Texture2D*}
 */
setTexture : function () {},

/**
 * @method initWithFile
 * @return A value converted from C/C++ "bool"
 * @param {const char*}
 * @param {unsigned int}
 */
initWithFile : function () {},

/**
 * @method disableParticle
 * @param {unsigned int}
 */
disableParticle : function () {},

/**
 * @method visit
 */
visit : function () {},

/**
 * @method getTexture
 * @return A value converted from C/C++ "cocos2d::Texture2D*"
 */
getTexture : function () {},

/**
 * @method setTextureAtlas
 * @param {cocos2d::TextureAtlas*}
 */
setTextureAtlas : function () {},

/**
 * @method removeAllChildrenWithCleanup
 * @param {bool}
 */
removeAllChildrenWithCleanup : function () {},

/**
 * @method getTextureAtlas
 * @return A value converted from C/C++ "cocos2d::TextureAtlas*"
 */
getTextureAtlas : function () {},

/**
 * @method removeChild
 * @param {cocos2d::Node*}
 * @param {bool}
 */
removeChild : function () {},

/**
 * @method insertChild
 * @param {cocos2d::ParticleSystem*}
 * @param {int}
 */
insertChild : function () {},

/**
 * @method initWithTexture
 * @return A value converted from C/C++ "bool"
 * @param {cocos2d::Texture2D*}
 * @param {unsigned int}
 */
initWithTexture : function () {},

/**
 * @method removeChildAtIndex
 * @param {unsigned int}
 * @param {bool}
 */
removeChildAtIndex : function () {},

/**
 * @method reorderChild
 * @param {cocos2d::Node*}
 * @param {int}
 */
reorderChild : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::ParticleBatchNode*"
 * @param {const char*}
 * @param {unsigned int}
 */
create : function () {},

/**
 * @method createWithTexture
 * @return A value converted from C/C++ "cocos2d::ParticleBatchNode*"
 * @param {cocos2d::Texture2D*}
 * @param {unsigned int}
 */
createWithTexture : function () {},

/**
 * @method ParticleBatchNode
 * @constructor
 */
ParticleBatchNode : function () {},

};

/**
 * @class ParticleSystem
 */
cc.ParticleSystem = {

/**
 * @method getStartSizeVar
 * @return A value converted from C/C++ "float"
 */
getStartSizeVar : function () {},

/**
 * @method getTexture
 * @return A value converted from C/C++ "cocos2d::Texture2D*"
 */
getTexture : function () {},

/**
 * @method isFull
 * @return A value converted from C/C++ "bool"
 */
isFull : function () {},

/**
 * @method getBatchNode
 * @return A value converted from C/C++ "cocos2d::ParticleBatchNode*"
 */
getBatchNode : function () {},

/**
 * @method getStartColor
 * @return A value converted from C/C++ "cocos2d::Color4F"
 */
getStartColor : function () {},

/**
 * @method getPositionType
 * @return A value converted from C/C++ "cocos2d::ParticleSystem::PositionType"
 */
getPositionType : function () {},

/**
 * @method setPosVar
 * @param {cocos2d::Point}
 */
setPosVar : function () {},

/**
 * @method getEndSpin
 * @return A value converted from C/C++ "float"
 */
getEndSpin : function () {},

/**
 * @method setRotatePerSecondVar
 * @param {float}
 */
setRotatePerSecondVar : function () {},

/**
 * @method getStartSpinVar
 * @return A value converted from C/C++ "float"
 */
getStartSpinVar : function () {},

/**
 * @method getRadialAccelVar
 * @return A value converted from C/C++ "float"
 */
getRadialAccelVar : function () {},

/**
 * @method init
 * @return A value converted from C/C++ "bool"
 */
init : function () {},

/**
 * @method getEndSizeVar
 * @return A value converted from C/C++ "float"
 */
getEndSizeVar : function () {},

/**
 * @method setRotation
 * @param {float}
 */
setRotation : function () {},

/**
 * @method setTangentialAccel
 * @param {float}
 */
setTangentialAccel : function () {},

/**
 * @method setScaleY
 * @param {float}
 */
setScaleY : function () {},

/**
 * @method setScaleX
 * @param {float}
 */
setScaleX : function () {},

/**
 * @method getRadialAccel
 * @return A value converted from C/C++ "float"
 */
getRadialAccel : function () {},

/**
 * @method setStartRadius
 * @param {float}
 */
setStartRadius : function () {},

/**
 * @method setRotatePerSecond
 * @param {float}
 */
setRotatePerSecond : function () {},

/**
 * @method setEndSize
 * @param {float}
 */
setEndSize : function () {},

/**
 * @method getStartColorVar
 * @return A value converted from C/C++ "cocos2d::Color4F"
 */
getStartColorVar : function () {},

/**
 * @method getTangentialAccel
 * @return A value converted from C/C++ "float"
 */
getTangentialAccel : function () {},

/**
 * @method setEndRadius
 * @param {float}
 */
setEndRadius : function () {},

/**
 * @method getSpeed
 * @return A value converted from C/C++ "float"
 */
getSpeed : function () {},

/**
 * @method getAngle
 * @return A value converted from C/C++ "float"
 */
getAngle : function () {},

/**
 * @method setEndColor
 * @param {cocos2d::Color4F}
 */
setEndColor : function () {},

/**
 * @method setStartSpin
 * @param {float}
 */
setStartSpin : function () {},

/**
 * @method setDuration
 * @param {float}
 */
setDuration : function () {},

/**
 * @method initWithTotalParticles
 * @return A value converted from C/C++ "bool"
 * @param {unsigned int}
 */
initWithTotalParticles : function () {},

/**
 * @method setTexture
 * @param {cocos2d::Texture2D*}
 */
setTexture : function () {},

/**
 * @method getPosVar
 * @return A value converted from C/C++ "cocos2d::Point"
 */
getPosVar : function () {},

/**
 * @method updateWithNoTime
 */
updateWithNoTime : function () {},

/**
 * @method isBlendAdditive
 * @return A value converted from C/C++ "bool"
 */
isBlendAdditive : function () {},

/**
 * @method getSpeedVar
 * @return A value converted from C/C++ "float"
 */
getSpeedVar : function () {},

/**
 * @method setPositionType
 * @param {cocos2d::ParticleSystem::PositionType}
 */
setPositionType : function () {},

/**
 * @method stopSystem
 */
stopSystem : function () {},

/**
 * @method getSourcePosition
 * @return A value converted from C/C++ "cocos2d::Point"
 */
getSourcePosition : function () {},

/**
 * @method setLifeVar
 * @param {float}
 */
setLifeVar : function () {},

/**
 * @method setTotalParticles
 * @param {unsigned int}
 */
setTotalParticles : function () {},

/**
 * @method setEndColorVar
 * @param {cocos2d::Color4F}
 */
setEndColorVar : function () {},

/**
 * @method updateQuadWithParticle
 * @param {tParticle*}
 * @param {cocos2d::Point}
 */
updateQuadWithParticle : function () {},

/**
 * @method getAtlasIndex
 * @return A value converted from C/C++ "int"
 */
getAtlasIndex : function () {},

/**
 * @method getStartSize
 * @return A value converted from C/C++ "float"
 */
getStartSize : function () {},

/**
 * @method setStartSpinVar
 * @param {float}
 */
setStartSpinVar : function () {},

/**
 * @method resetSystem
 */
resetSystem : function () {},

/**
 * @method setAtlasIndex
 * @param {int}
 */
setAtlasIndex : function () {},

/**
 * @method setTangentialAccelVar
 * @param {float}
 */
setTangentialAccelVar : function () {},

/**
 * @method setEndRadiusVar
 * @param {float}
 */
setEndRadiusVar : function () {},

/**
 * @method getEndRadius
 * @return A value converted from C/C++ "float"
 */
getEndRadius : function () {},

/**
 * @method isOpacityModifyRGB
 * @return A value converted from C/C++ "bool"
 */
isOpacityModifyRGB : function () {},

/**
 * @method isActive
 * @return A value converted from C/C++ "bool"
 */
isActive : function () {},

/**
 * @method setRadialAccelVar
 * @param {float}
 */
setRadialAccelVar : function () {},

/**
 * @method setStartSize
 * @param {float}
 */
setStartSize : function () {},

/**
 * @method setSpeed
 * @param {float}
 */
setSpeed : function () {},

/**
 * @method getStartSpin
 * @return A value converted from C/C++ "float"
 */
getStartSpin : function () {},

/**
 * @method getRotatePerSecond
 * @return A value converted from C/C++ "float"
 */
getRotatePerSecond : function () {},

/**
 * @method initParticle
 * @param {tParticle*}
 */
initParticle : function () {},

/**
 * @method setEmitterMode
 * @param {cocos2d::ParticleSystem::Mode}
 */
setEmitterMode : function () {},

/**
 * @method getDuration
 * @return A value converted from C/C++ "float"
 */
getDuration : function () {},

/**
 * @method setSourcePosition
 * @param {cocos2d::Point}
 */
setSourcePosition : function () {},

/**
 * @method getEndSpinVar
 * @return A value converted from C/C++ "float"
 */
getEndSpinVar : function () {},

/**
 * @method setBlendAdditive
 * @param {bool}
 */
setBlendAdditive : function () {},

/**
 * @method setLife
 * @param {float}
 */
setLife : function () {},

/**
 * @method setAngleVar
 * @param {float}
 */
setAngleVar : function () {},

/**
 * @method setRotationIsDir
 * @param {bool}
 */
setRotationIsDir : function () {},

/**
 * @method setEndSizeVar
 * @param {float}
 */
setEndSizeVar : function () {},

/**
 * @method setAngle
 * @param {float}
 */
setAngle : function () {},

/**
 * @method setBatchNode
 * @param {cocos2d::ParticleBatchNode*}
 */
setBatchNode : function () {},

/**
 * @method getTangentialAccelVar
 * @return A value converted from C/C++ "float"
 */
getTangentialAccelVar : function () {},

/**
 * @method getEmitterMode
 * @return A value converted from C/C++ "cocos2d::ParticleSystem::Mode"
 */
getEmitterMode : function () {},

/**
 * @method setEndSpinVar
 * @param {float}
 */
setEndSpinVar : function () {},

/**
 * @method initWithFile
 * @return A value converted from C/C++ "bool"
 * @param {const char*}
 */
initWithFile : function () {},

/**
 * @method getAngleVar
 * @return A value converted from C/C++ "float"
 */
getAngleVar : function () {},

/**
 * @method setStartColor
 * @param {cocos2d::Color4F}
 */
setStartColor : function () {},

/**
 * @method getRotatePerSecondVar
 * @return A value converted from C/C++ "float"
 */
getRotatePerSecondVar : function () {},

/**
 * @method getEndSize
 * @return A value converted from C/C++ "float"
 */
getEndSize : function () {},

/**
 * @method getLife
 * @return A value converted from C/C++ "float"
 */
getLife : function () {},

/**
 * @method setSpeedVar
 * @param {float}
 */
setSpeedVar : function () {},

/**
 * @method setAutoRemoveOnFinish
 * @param {bool}
 */
setAutoRemoveOnFinish : function () {},

/**
 * @method setGravity
 * @param {cocos2d::Point}
 */
setGravity : function () {},

/**
 * @method postStep
 */
postStep : function () {},

/**
 * @method setEmissionRate
 * @param {float}
 */
setEmissionRate : function () {},

/**
 * @method getEndColorVar
 * @return A value converted from C/C++ "cocos2d::Color4F"
 */
getEndColorVar : function () {},

/**
 * @method getRotationIsDir
 * @return A value converted from C/C++ "bool"
 */
getRotationIsDir : function () {},

/**
 * @method setScale
 * @param {float}
 */
setScale : function () {},

/**
 * @method getEmissionRate
 * @return A value converted from C/C++ "float"
 */
getEmissionRate : function () {},

/**
 * @method getEndColor
 * @return A value converted from C/C++ "cocos2d::Color4F"
 */
getEndColor : function () {},

/**
 * @method getLifeVar
 * @return A value converted from C/C++ "float"
 */
getLifeVar : function () {},

/**
 * @method setStartSizeVar
 * @param {float}
 */
setStartSizeVar : function () {},

/**
 * @method setOpacityModifyRGB
 * @param {bool}
 */
setOpacityModifyRGB : function () {},

/**
 * @method addParticle
 * @return A value converted from C/C++ "bool"
 */
addParticle : function () {},

/**
 * @method getStartRadius
 * @return A value converted from C/C++ "float"
 */
getStartRadius : function () {},

/**
 * @method getParticleCount
 * @return A value converted from C/C++ "unsigned int"
 */
getParticleCount : function () {},

/**
 * @method getStartRadiusVar
 * @return A value converted from C/C++ "float"
 */
getStartRadiusVar : function () {},

/**
 * @method setStartColorVar
 * @param {cocos2d::Color4F}
 */
setStartColorVar : function () {},

/**
 * @method setEndSpin
 * @param {float}
 */
setEndSpin : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method setRadialAccel
 * @param {float}
 */
setRadialAccel : function () {},

/**
 * @method isAutoRemoveOnFinish
 * @return A value converted from C/C++ "bool"
 */
isAutoRemoveOnFinish : function () {},

/**
 * @method getTotalParticles
 * @return A value converted from C/C++ "unsigned int"
 */
getTotalParticles : function () {},

/**
 * @method setStartRadiusVar
 * @param {float}
 */
setStartRadiusVar : function () {},

/**
 * @method getEndRadiusVar
 * @return A value converted from C/C++ "float"
 */
getEndRadiusVar : function () {},

/**
 * @method getGravity
 * @return A value converted from C/C++ "cocos2d::Point"
 */
getGravity : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::ParticleSystem*"
 * @param {const char*}
 */
create : function () {},

/**
 * @method createWithTotalParticles
 * @return A value converted from C/C++ "cocos2d::ParticleSystem*"
 * @param {unsigned int}
 */
createWithTotalParticles : function () {},

/**
 * @method ParticleSystem
 * @constructor
 */
ParticleSystem : function () {},

};

/**
 * @class ParticleSystemQuad
 */
cc.ParticleSystem = {

/**
 * @method initTexCoordsWithRect
 * @param {cocos2d::Rect}
 */
initTexCoordsWithRect : function () {},

/**
 * @method setTextureWithRect
 * @param {cocos2d::Texture2D*}
 * @param {cocos2d::Rect}
 */
setTextureWithRect : function () {},

/**
 * @method initIndices
 */
initIndices : function () {},

/**
 * @method setDisplayFrame
 * @param {cocos2d::SpriteFrame*}
 */
setDisplayFrame : function () {},

/**
 * @method createWithTotalParticles
 * @return A value converted from C/C++ "cocos2d::ParticleSystemQuad*"
 * @param {unsigned int}
 */
createWithTotalParticles : function () {},

/**
 * @method ParticleSystemQuad
 * @constructor
 */
ParticleSystemQuad : function () {},

};

/**
 * @class ParticleFire
 */
cc.ParticleFire = {

/**
 * @method init
 * @return A value converted from C/C++ "bool"
 */
init : function () {},

/**
 * @method initWithTotalParticles
 * @return A value converted from C/C++ "bool"
 * @param {unsigned int}
 */
initWithTotalParticles : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::ParticleFire*"
 */
create : function () {},

/**
 * @method createWithTotalParticles
 * @return A value converted from C/C++ "cocos2d::ParticleFire*"
 * @param {unsigned int}
 */
createWithTotalParticles : function () {},

/**
 * @method ParticleFire
 * @constructor
 */
ParticleFire : function () {},

};

/**
 * @class ParticleFireworks
 */
cc.ParticleFireworks = {

/**
 * @method init
 * @return A value converted from C/C++ "bool"
 */
init : function () {},

/**
 * @method initWithTotalParticles
 * @return A value converted from C/C++ "bool"
 * @param {unsigned int}
 */
initWithTotalParticles : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::ParticleFireworks*"
 */
create : function () {},

/**
 * @method createWithTotalParticles
 * @return A value converted from C/C++ "cocos2d::ParticleFireworks*"
 * @param {unsigned int}
 */
createWithTotalParticles : function () {},

/**
 * @method ParticleFireworks
 * @constructor
 */
ParticleFireworks : function () {},

};

/**
 * @class ParticleSun
 */
cc.ParticleSun = {

/**
 * @method init
 * @return A value converted from C/C++ "bool"
 */
init : function () {},

/**
 * @method initWithTotalParticles
 * @return A value converted from C/C++ "bool"
 * @param {unsigned int}
 */
initWithTotalParticles : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::ParticleSun*"
 */
create : function () {},

/**
 * @method createWithTotalParticles
 * @return A value converted from C/C++ "cocos2d::ParticleSun*"
 * @param {unsigned int}
 */
createWithTotalParticles : function () {},

/**
 * @method ParticleSun
 * @constructor
 */
ParticleSun : function () {},

};

/**
 * @class ParticleGalaxy
 */
cc.ParticleGalaxy = {

/**
 * @method init
 * @return A value converted from C/C++ "bool"
 */
init : function () {},

/**
 * @method initWithTotalParticles
 * @return A value converted from C/C++ "bool"
 * @param {unsigned int}
 */
initWithTotalParticles : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::ParticleGalaxy*"
 */
create : function () {},

/**
 * @method createWithTotalParticles
 * @return A value converted from C/C++ "cocos2d::ParticleGalaxy*"
 * @param {unsigned int}
 */
createWithTotalParticles : function () {},

/**
 * @method ParticleGalaxy
 * @constructor
 */
ParticleGalaxy : function () {},

};

/**
 * @class ParticleFlower
 */
cc.ParticleFlower = {

/**
 * @method init
 * @return A value converted from C/C++ "bool"
 */
init : function () {},

/**
 * @method initWithTotalParticles
 * @return A value converted from C/C++ "bool"
 * @param {unsigned int}
 */
initWithTotalParticles : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::ParticleFlower*"
 */
create : function () {},

/**
 * @method createWithTotalParticles
 * @return A value converted from C/C++ "cocos2d::ParticleFlower*"
 * @param {unsigned int}
 */
createWithTotalParticles : function () {},

/**
 * @method ParticleFlower
 * @constructor
 */
ParticleFlower : function () {},

};

/**
 * @class ParticleMeteor
 */
cc.ParticleMeteor = {

/**
 * @method init
 * @return A value converted from C/C++ "bool"
 */
init : function () {},

/**
 * @method initWithTotalParticles
 * @return A value converted from C/C++ "bool"
 * @param {unsigned int}
 */
initWithTotalParticles : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::ParticleMeteor*"
 */
create : function () {},

/**
 * @method createWithTotalParticles
 * @return A value converted from C/C++ "cocos2d::ParticleMeteor*"
 * @param {unsigned int}
 */
createWithTotalParticles : function () {},

/**
 * @method ParticleMeteor
 * @constructor
 */
ParticleMeteor : function () {},

};

/**
 * @class ParticleSpiral
 */
cc.ParticleSpiral = {

/**
 * @method init
 * @return A value converted from C/C++ "bool"
 */
init : function () {},

/**
 * @method initWithTotalParticles
 * @return A value converted from C/C++ "bool"
 * @param {unsigned int}
 */
initWithTotalParticles : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::ParticleSpiral*"
 */
create : function () {},

/**
 * @method createWithTotalParticles
 * @return A value converted from C/C++ "cocos2d::ParticleSpiral*"
 * @param {unsigned int}
 */
createWithTotalParticles : function () {},

/**
 * @method ParticleSpiral
 * @constructor
 */
ParticleSpiral : function () {},

};

/**
 * @class ParticleExplosion
 */
cc.ParticleExplosion = {

/**
 * @method init
 * @return A value converted from C/C++ "bool"
 */
init : function () {},

/**
 * @method initWithTotalParticles
 * @return A value converted from C/C++ "bool"
 * @param {unsigned int}
 */
initWithTotalParticles : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::ParticleExplosion*"
 */
create : function () {},

/**
 * @method createWithTotalParticles
 * @return A value converted from C/C++ "cocos2d::ParticleExplosion*"
 * @param {unsigned int}
 */
createWithTotalParticles : function () {},

/**
 * @method ParticleExplosion
 * @constructor
 */
ParticleExplosion : function () {},

};

/**
 * @class ParticleSmoke
 */
cc.ParticleSmoke = {

/**
 * @method init
 * @return A value converted from C/C++ "bool"
 */
init : function () {},

/**
 * @method initWithTotalParticles
 * @return A value converted from C/C++ "bool"
 * @param {unsigned int}
 */
initWithTotalParticles : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::ParticleSmoke*"
 */
create : function () {},

/**
 * @method createWithTotalParticles
 * @return A value converted from C/C++ "cocos2d::ParticleSmoke*"
 * @param {unsigned int}
 */
createWithTotalParticles : function () {},

/**
 * @method ParticleSmoke
 * @constructor
 */
ParticleSmoke : function () {},

};

/**
 * @class ParticleSnow
 */
cc.ParticleSnow = {

/**
 * @method init
 * @return A value converted from C/C++ "bool"
 */
init : function () {},

/**
 * @method initWithTotalParticles
 * @return A value converted from C/C++ "bool"
 * @param {unsigned int}
 */
initWithTotalParticles : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::ParticleSnow*"
 */
create : function () {},

/**
 * @method createWithTotalParticles
 * @return A value converted from C/C++ "cocos2d::ParticleSnow*"
 * @param {unsigned int}
 */
createWithTotalParticles : function () {},

/**
 * @method ParticleSnow
 * @constructor
 */
ParticleSnow : function () {},

};

/**
 * @class ParticleRain
 */
cc.ParticleRain = {

/**
 * @method init
 * @return A value converted from C/C++ "bool"
 */
init : function () {},

/**
 * @method initWithTotalParticles
 * @return A value converted from C/C++ "bool"
 * @param {unsigned int}
 */
initWithTotalParticles : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::ParticleRain*"
 */
create : function () {},

/**
 * @method createWithTotalParticles
 * @return A value converted from C/C++ "cocos2d::ParticleRain*"
 * @param {unsigned int}
 */
createWithTotalParticles : function () {},

/**
 * @method ParticleRain
 * @constructor
 */
ParticleRain : function () {},

};

/**
 * @class FileUtils
 */
cc.FileUtils = {

/**
 * @method isFileExist
 * @return A value converted from C/C++ "bool"
 * @param {std::string}
 */
isFileExist : function () {},

/**
 * @method isPopupNotify
 * @return A value converted from C/C++ "bool"
 */
isPopupNotify : function () {},

/**
 * @method purgeCachedEntries
 */
purgeCachedEntries : function () {},

/**
 * @method fullPathFromRelativeFile
 * @return A value converted from C/C++ "const char*"
 * @param {const char*}
 * @param {const char*}
 */
fullPathFromRelativeFile : function () {},

/**
 * @method getFileData
 * @return A value converted from C/C++ "unsigned char*"
 * @param {const char*}
 * @param {const char*}
 * @param {unsigned long*}
 */
getFileData : function () {},

/**
 * @method setFilenameLookupDictionary
 * @param {cocos2d::Dictionary*}
 */
setFilenameLookupDictionary : function () {},

/**
 * @method addSearchResolutionsOrder
 * @param {const char*}
 */
addSearchResolutionsOrder : function () {},

/**
 * @method getFileDataFromZip
 * @return A value converted from C/C++ "unsigned char*"
 * @param {const char*}
 * @param {const char*}
 * @param {unsigned long*}
 */
getFileDataFromZip : function () {},

/**
 * @method fullPathForFilename
 * @return A value converted from C/C++ "std::string"
 * @param {const char*}
 */
fullPathForFilename : function () {},

/**
 * @method isAbsolutePath
 * @return A value converted from C/C++ "bool"
 * @param {std::string}
 */
isAbsolutePath : function () {},

/**
 * @method getWritablePath
 * @return A value converted from C/C++ "std::string"
 */
getWritablePath : function () {},

/**
 * @method addSearchPath
 * @param {const char*}
 */
addSearchPath : function () {},

/**
 * @method setPopupNotify
 * @param {bool}
 */
setPopupNotify : function () {},

/**
 * @method loadFilenameLookupDictionaryFromFile
 * @param {const char*}
 */
loadFilenameLookupDictionaryFromFile : function () {},

/**
 * @method destroyInstance
 */
destroyInstance : function () {},

/**
 * @method getInstance
 * @return A value converted from C/C++ "cocos2d::FileUtils*"
 */
getInstance : function () {},

};

/**
 * @class Application
 */
cc.Application = {

/**
 * @method getTargetPlatform
 * @return A value converted from C/C++ "cocos2d::ApplicationProtocol::Platform"
 */
getTargetPlatform : function () {},

/**
 * @method setAnimationInterval
 * @param {double}
 */
setAnimationInterval : function () {},

/**
 * @method getCurrentLanguage
 * @return A value converted from C/C++ "cocos2d::LanguageType"
 */
getCurrentLanguage : function () {},

/**
 * @method getInstance
 * @return A value converted from C/C++ "cocos2d::Application*"
 */
getInstance : function () {},

};

/**
 * @class ShaderCache
 */
cc.ShaderCache = {

/**
 * @method reloadDefaultShaders
 */
reloadDefaultShaders : function () {},

/**
 * @method addProgram
 * @param {cocos2d::GLProgram*}
 * @param {const char*}
 */
addProgram : function () {},

/**
 * @method programForKey
 * @return A value converted from C/C++ "cocos2d::GLProgram*"
 * @param {const char*}
 */
programForKey : function () {},

/**
 * @method loadDefaultShaders
 */
loadDefaultShaders : function () {},

/**
 * @method destroyInstance
 */
destroyInstance : function () {},

/**
 * @method getInstance
 * @return A value converted from C/C++ "cocos2d::ShaderCache*"
 */
getInstance : function () {},

/**
 * @method ShaderCache
 * @constructor
 */
ShaderCache : function () {},

};

/**
 * @class AnimationCache
 */
cc.AnimationCache = {

/**
 * @method animationByName
 * @return A value converted from C/C++ "cocos2d::Animation*"
 * @param {const char*}
 */
animationByName : function () {},

/**
 * @method addAnimation
 * @param {cocos2d::Animation*}
 * @param {const char*}
 */
addAnimation : function () {},

/**
 * @method init
 * @return A value converted from C/C++ "bool"
 */
init : function () {},

/**
 * @method addAnimationsWithDictionary
 * @param {cocos2d::Dictionary*}
 */
addAnimationsWithDictionary : function () {},

/**
 * @method removeAnimationByName
 * @param {const char*}
 */
removeAnimationByName : function () {},

/**
 * @method addAnimationsWithFile
 * @param {const char*}
 */
addAnimationsWithFile : function () {},

/**
 * @method destroyInstance
 */
destroyInstance : function () {},

/**
 * @method getInstance
 * @return A value converted from C/C++ "cocos2d::AnimationCache*"
 */
getInstance : function () {},

/**
 * @method AnimationCache
 * @constructor
 */
AnimationCache : function () {},

};

/**
 * @class SpriteFrameCache
 */
cc.SpriteFrameCache = {

/**
 * @method addSpriteFrame
 * @param {cocos2d::SpriteFrame*}
 * @param {const char*}
 */
addSpriteFrame : function () {},

/**
 * @method removeUnusedSpriteFrames
 */
removeUnusedSpriteFrames : function () {},

/**
 * @method getSpriteFrameByName
 * @return A value converted from C/C++ "cocos2d::SpriteFrame*"
 * @param {const char*}
 */
getSpriteFrameByName : function () {},

/**
 * @method removeSpriteFramesFromFile
 * @param {const char*}
 */
removeSpriteFramesFromFile : function () {},

/**
 * @method init
 * @return A value converted from C/C++ "bool"
 */
init : function () {},

/**
 * @method removeSpriteFrames
 */
removeSpriteFrames : function () {},

/**
 * @method removeSpriteFramesFromTexture
 * @param {cocos2d::Texture2D*}
 */
removeSpriteFramesFromTexture : function () {},

/**
 * @method removeSpriteFrameByName
 * @param {const char*}
 */
removeSpriteFrameByName : function () {},

/**
 * @method destroyInstance
 */
destroyInstance : function () {},

/**
 * @method getInstance
 * @return A value converted from C/C++ "cocos2d::SpriteFrameCache*"
 */
getInstance : function () {},

};

/**
 * @class TextureCache
 */
cc.TextureCache = {

/**
 * @method dumpCachedTextureInfo
 */
dumpCachedTextureInfo : function () {},

/**
 * @method addUIImage
 * @return A value converted from C/C++ "cocos2d::Texture2D*"
 * @param {cocos2d::Image*}
 * @param {const char*}
 */
addUIImage : function () {},

/**
 * @method removeTextureForKey
 * @param {const char*}
 */
removeTextureForKey : function () {},

/**
 * @method textureForKey
 * @return A value converted from C/C++ "cocos2d::Texture2D*"
 * @param {const char*}
 */
textureForKey : function () {},

/**
 * @method snapshotTextures
 * @return A value converted from C/C++ "cocos2d::Dictionary*"
 */
snapshotTextures : function () {},

/**
 * @method addImage
 * @return A value converted from C/C++ "cocos2d::Texture2D*"
 * @param {const char*}
 */
addImage : function () {},

/**
 * @method removeAllTextures
 */
removeAllTextures : function () {},

/**
 * @method removeUnusedTextures
 */
removeUnusedTextures : function () {},

/**
 * @method removeTexture
 * @param {cocos2d::Texture2D*}
 */
removeTexture : function () {},

/**
 * @method destroyInstance
 */
destroyInstance : function () {},

/**
 * @method reloadAllTextures
 */
reloadAllTextures : function () {},

/**
 * @method getInstance
 * @return A value converted from C/C++ "cocos2d::TextureCache*"
 */
getInstance : function () {},

/**
 * @method TextureCache
 * @constructor
 */
TextureCache : function () {},

};

/**
 * @class ParallaxNode
 */
cc.ParallaxNode = {

/**
 * @method visit
 */
visit : function () {},

/**
 * @method removeAllChildrenWithCleanup
 * @param {bool}
 */
removeAllChildrenWithCleanup : function () {},

/**
 * @method removeChild
 * @param {cocos2d::Node*}
 * @param {bool}
 */
removeChild : function () {},

/**
 * @method setParallaxArray
 * @param {_ccArray*}
 */
setParallaxArray : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::ParallaxNode*"
 */
create : function () {},

/**
 * @method ParallaxNode
 * @constructor
 */
ParallaxNode : function () {},

};

/**
 * @class TMXObjectGroup
 */
cc.TMXObjectGroup = {

/**
 * @method setPositionOffset
 * @param {cocos2d::Point}
 */
setPositionOffset : function () {},

/**
 * @method getProperty
 * @return A value converted from C/C++ "cocos2d::String*"
 * @param {const char*}
 */
getProperty : function () {},

/**
 * @method getPositionOffset
 * @return A value converted from C/C++ "cocos2d::Point"
 */
getPositionOffset : function () {},

/**
 * @method getObject
 * @return A value converted from C/C++ "cocos2d::Dictionary*"
 * @param {const char*}
 */
getObject : function () {},

/**
 * @method getObjects
 * @return A value converted from C/C++ "cocos2d::Array*"
 */
getObjects : function () {},

/**
 * @method setGroupName
 * @param {const char*}
 */
setGroupName : function () {},

/**
 * @method getProperties
 * @return A value converted from C/C++ "cocos2d::Dictionary*"
 */
getProperties : function () {},

/**
 * @method getGroupName
 * @return A value converted from C/C++ "const char*"
 */
getGroupName : function () {},

/**
 * @method setProperties
 * @param {cocos2d::Dictionary*}
 */
setProperties : function () {},

/**
 * @method setObjects
 * @param {cocos2d::Array*}
 */
setObjects : function () {},

/**
 * @method TMXObjectGroup
 * @constructor
 */
TMXObjectGroup : function () {},

};

/**
 * @class TMXLayerInfo
 */
cc.TMXLayerInfo = {

/**
 * @method setProperties
 * @param {cocos2d::Dictionary*}
 */
setProperties : function () {},

/**
 * @method getProperties
 * @return A value converted from C/C++ "cocos2d::Dictionary*"
 */
getProperties : function () {},

/**
 * @method TMXLayerInfo
 * @constructor
 */
TMXLayerInfo : function () {},

};

/**
 * @class TMXTilesetInfo
 */
cc.TMXTilesetInfo = {

/**
 * @method rectForGID
 * @return A value converted from C/C++ "cocos2d::Rect"
 * @param {unsigned int}
 */
rectForGID : function () {},

/**
 * @method TMXTilesetInfo
 * @constructor
 */
TMXTilesetInfo : function () {},

};

/**
 * @class TMXMapInfo
 */
cc.TMXMapInfo = {

/**
 * @method setObjectGroups
 * @param {cocos2d::Array*}
 */
setObjectGroups : function () {},

/**
 * @method setTileSize
 * @param {cocos2d::Size}
 */
setTileSize : function () {},

/**
 * @method initWithTMXFile
 * @return A value converted from C/C++ "bool"
 * @param {const char*}
 */
initWithTMXFile : function () {},

/**
 * @method getOrientation
 * @return A value converted from C/C++ "int"
 */
getOrientation : function () {},

/**
 * @method isStoringCharacters
 * @return A value converted from C/C++ "bool"
 */
isStoringCharacters : function () {},

/**
 * @method setLayers
 * @param {cocos2d::Array*}
 */
setLayers : function () {},

/**
 * @method parseXMLFile
 * @return A value converted from C/C++ "bool"
 * @param {const char*}
 */
parseXMLFile : function () {},

/**
 * @method getParentElement
 * @return A value converted from C/C++ "int"
 */
getParentElement : function () {},

/**
 * @method setTMXFileName
 * @param {const char*}
 */
setTMXFileName : function () {},

/**
 * @method parseXMLString
 * @return A value converted from C/C++ "bool"
 * @param {const char*}
 */
parseXMLString : function () {},

/**
 * @method getLayers
 * @return A value converted from C/C++ "cocos2d::Array*"
 */
getLayers : function () {},

/**
 * @method getTilesets
 * @return A value converted from C/C++ "cocos2d::Array*"
 */
getTilesets : function () {},

/**
 * @method getParentGID
 * @return A value converted from C/C++ "unsigned int"
 */
getParentGID : function () {},

/**
 * @method setParentElement
 * @param {int}
 */
setParentElement : function () {},

/**
 * @method initWithXML
 * @return A value converted from C/C++ "bool"
 * @param {const char*}
 * @param {const char*}
 */
initWithXML : function () {},

/**
 * @method setParentGID
 * @param {unsigned int}
 */
setParentGID : function () {},

/**
 * @method getLayerAttribs
 * @return A value converted from C/C++ "int"
 */
getLayerAttribs : function () {},

/**
 * @method getTileSize
 * @return A value converted from C/C++ "cocos2d::Size"
 */
getTileSize : function () {},

/**
 * @method getTileProperties
 * @return A value converted from C/C++ "cocos2d::Dictionary*"
 */
getTileProperties : function () {},

/**
 * @method getObjectGroups
 * @return A value converted from C/C++ "cocos2d::Array*"
 */
getObjectGroups : function () {},

/**
 * @method getTMXFileName
 * @return A value converted from C/C++ "const char*"
 */
getTMXFileName : function () {},

/**
 * @method setCurrentString
 * @param {const char*}
 */
setCurrentString : function () {},

/**
 * @method setProperties
 * @param {cocos2d::Dictionary*}
 */
setProperties : function () {},

/**
 * @method setOrientation
 * @param {int}
 */
setOrientation : function () {},

/**
 * @method setTileProperties
 * @param {cocos2d::Dictionary*}
 */
setTileProperties : function () {},

/**
 * @method setMapSize
 * @param {cocos2d::Size}
 */
setMapSize : function () {},

/**
 * @method setStoringCharacters
 * @param {bool}
 */
setStoringCharacters : function () {},

/**
 * @method getMapSize
 * @return A value converted from C/C++ "cocos2d::Size"
 */
getMapSize : function () {},

/**
 * @method setTilesets
 * @param {cocos2d::Array*}
 */
setTilesets : function () {},

/**
 * @method getProperties
 * @return A value converted from C/C++ "cocos2d::Dictionary*"
 */
getProperties : function () {},

/**
 * @method getCurrentString
 * @return A value converted from C/C++ "const char*"
 */
getCurrentString : function () {},

/**
 * @method setLayerAttribs
 * @param {int}
 */
setLayerAttribs : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::TMXMapInfo*"
 * @param {const char*}
 */
create : function () {},

/**
 * @method createWithXML
 * @return A value converted from C/C++ "cocos2d::TMXMapInfo*"
 * @param {const char*}
 * @param {const char*}
 */
createWithXML : function () {},

/**
 * @method TMXMapInfo
 * @constructor
 */
TMXMapInfo : function () {},

};

/**
 * @class TMXLayer
 */
cc.TMXLayer = {

/**
 * @method addChild
 * @param {cocos2d::Node*}
 * @param {int}
 * @param {int}
 */
addChild : function () {},

/**
 * @method getTileGIDAt
 * @return A value converted from C/C++ "unsigned int"
 * @param {cocos2d::Point}
 * @param {cocos2d::ccTMXTileFlags*}
 */
getTileGIDAt : function () {},

/**
 * @method getPositionAt
 * @return A value converted from C/C++ "cocos2d::Point"
 * @param {cocos2d::Point}
 */
getPositionAt : function () {},

/**
 * @method setLayerOrientation
 * @param {unsigned int}
 */
setLayerOrientation : function () {},

/**
 * @method releaseMap
 */
releaseMap : function () {},

/**
 * @method setTiles
 * @param {unsigned int*}
 */
setTiles : function () {},

/**
 * @method getLayerSize
 * @return A value converted from C/C++ "cocos2d::Size"
 */
getLayerSize : function () {},

/**
 * @method setMapTileSize
 * @param {cocos2d::Size}
 */
setMapTileSize : function () {},

/**
 * @method getLayerOrientation
 * @return A value converted from C/C++ "unsigned int"
 */
getLayerOrientation : function () {},

/**
 * @method setProperties
 * @param {cocos2d::Dictionary*}
 */
setProperties : function () {},

/**
 * @method setLayerName
 * @param {const char*}
 */
setLayerName : function () {},

/**
 * @method removeTileAt
 * @param {cocos2d::Point}
 */
removeTileAt : function () {},

/**
 * @method initWithTilesetInfo
 * @return A value converted from C/C++ "bool"
 * @param {cocos2d::TMXTilesetInfo*}
 * @param {cocos2d::TMXLayerInfo*}
 * @param {cocos2d::TMXMapInfo*}
 */
initWithTilesetInfo : function () {},

/**
 * @method setupTiles
 */
setupTiles : function () {},

/**
 * @method getMapTileSize
 * @return A value converted from C/C++ "cocos2d::Size"
 */
getMapTileSize : function () {},

/**
 * @method getProperty
 * @return A value converted from C/C++ "cocos2d::String*"
 * @param {const char*}
 */
getProperty : function () {},

/**
 * @method setLayerSize
 * @param {cocos2d::Size}
 */
setLayerSize : function () {},

/**
 * @method getLayerName
 * @return A value converted from C/C++ "const char*"
 */
getLayerName : function () {},

/**
 * @method setTileSet
 * @param {cocos2d::TMXTilesetInfo*}
 */
setTileSet : function () {},

/**
 * @method removeChild
 * @param {cocos2d::Node*}
 * @param {bool}
 */
removeChild : function () {},

/**
 * @method getTileSet
 * @return A value converted from C/C++ "cocos2d::TMXTilesetInfo*"
 */
getTileSet : function () {},

/**
 * @method getProperties
 * @return A value converted from C/C++ "cocos2d::Dictionary*"
 */
getProperties : function () {},

/**
 * @method getTileAt
 * @return A value converted from C/C++ "cocos2d::Sprite*"
 * @param {cocos2d::Point}
 */
getTileAt : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::TMXLayer*"
 * @param {cocos2d::TMXTilesetInfo*}
 * @param {cocos2d::TMXLayerInfo*}
 * @param {cocos2d::TMXMapInfo*}
 */
create : function () {},

/**
 * @method TMXLayer
 * @constructor
 */
TMXLayer : function () {},

};

/**
 * @class TMXTiledMap
 */
cc.TMXTiledMap = {

/**
 * @method setObjectGroups
 * @param {cocos2d::Array*}
 */
setObjectGroups : function () {},

/**
 * @method getProperty
 * @return A value converted from C/C++ "cocos2d::String*"
 * @param {const char*}
 */
getProperty : function () {},

/**
 * @method setMapSize
 * @param {cocos2d::Size}
 */
setMapSize : function () {},

/**
 * @method getObjectGroup
 * @return A value converted from C/C++ "cocos2d::TMXObjectGroup*"
 * @param {const char*}
 */
getObjectGroup : function () {},

/**
 * @method getPropertiesForGID
 * @return A value converted from C/C++ "cocos2d::Dictionary*"
 * @param {int}
 */
getPropertiesForGID : function () {},

/**
 * @method getObjectGroups
 * @return A value converted from C/C++ "cocos2d::Array*"
 */
getObjectGroups : function () {},

/**
 * @method initWithTMXFile
 * @return A value converted from C/C++ "bool"
 * @param {const char*}
 */
initWithTMXFile : function () {},

/**
 * @method getTileSize
 * @return A value converted from C/C++ "cocos2d::Size"
 */
getTileSize : function () {},

/**
 * @method getMapSize
 * @return A value converted from C/C++ "cocos2d::Size"
 */
getMapSize : function () {},

/**
 * @method getProperties
 * @return A value converted from C/C++ "cocos2d::Dictionary*"
 */
getProperties : function () {},

/**
 * @method setTileSize
 * @param {cocos2d::Size}
 */
setTileSize : function () {},

/**
 * @method initWithXML
 * @return A value converted from C/C++ "bool"
 * @param {const char*}
 * @param {const char*}
 */
initWithXML : function () {},

/**
 * @method getLayer
 * @return A value converted from C/C++ "cocos2d::TMXLayer*"
 * @param {const char*}
 */
getLayer : function () {},

/**
 * @method getMapOrientation
 * @return A value converted from C/C++ "int"
 */
getMapOrientation : function () {},

/**
 * @method setMapOrientation
 * @param {int}
 */
setMapOrientation : function () {},

/**
 * @method setProperties
 * @param {cocos2d::Dictionary*}
 */
setProperties : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::TMXTiledMap*"
 * @param {const char*}
 */
create : function () {},

/**
 * @method createWithXML
 * @return A value converted from C/C++ "cocos2d::TMXTiledMap*"
 * @param {const char*}
 * @param {const char*}
 */
createWithXML : function () {},

/**
 * @method TMXTiledMap
 * @constructor
 */
TMXTiledMap : function () {},

};

/**
 * @class TileMapAtlas
 */
cc.TileMapAtlas = {

/**
 * @method initWithTileFile
 * @return A value converted from C/C++ "bool"
 * @param {const char*}
 * @param {const char*}
 * @param {int}
 * @param {int}
 */
initWithTileFile : function () {},

/**
 * @method releaseMap
 */
releaseMap : function () {},

/**
 * @method getTGAInfo
 * @return A value converted from C/C++ "sImageTGA*"
 */
getTGAInfo : function () {},

/**
 * @method getTileAt
 * @return A value converted from C/C++ "cocos2d::Color3B"
 * @param {cocos2d::Point}
 */
getTileAt : function () {},

/**
 * @method setTile
 * @param {cocos2d::Color3B}
 * @param {cocos2d::Point}
 */
setTile : function () {},

/**
 * @method setTGAInfo
 * @param {sImageTGA*}
 */
setTGAInfo : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::TileMapAtlas*"
 * @param {const char*}
 * @param {const char*}
 * @param {int}
 * @param {int}
 */
create : function () {},

/**
 * @method TileMapAtlas
 * @constructor
 */
TileMapAtlas : function () {},

};

/**
 * @class Timer
 */
cc.Timer = {

/**
 * @method getInterval
 * @return A value converted from C/C++ "float"
 */
getInterval : function () {},

/**
 * @method setInterval
 * @param {float}
 */
setInterval : function () {},

/**
 * @method initWithScriptHandler
 * @return A value converted from C/C++ "bool"
 * @param {int}
 * @param {float}
 */
initWithScriptHandler : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method getScriptHandler
 * @return A value converted from C/C++ "int"
 */
getScriptHandler : function () {},

/**
 * @method Timer
 * @constructor
 */
Timer : function () {},

};

/**
 * @class Scheduler
 */
cc.Scheduler = {

/**
 * @method setTimeScale
 * @param {float}
 */
setTimeScale : function () {},

/**
 * @method getTimeScale
 * @return A value converted from C/C++ "float"
 */
getTimeScale : function () {},

/**
 * @method Scheduler
 * @constructor
 */
Scheduler : function () {},

};

/**
 * @class SimpleAudioEngine
 */
cc.AudioEngine = {

/**
 * @method stopAllEffects
 */
stopAllEffects : function () {},

/**
 * @method getBackgroundMusicVolume
 * @return A value converted from C/C++ "float"
 */
getBackgroundMusicVolume : function () {},

/**
 * @method isBackgroundMusicPlaying
 * @return A value converted from C/C++ "bool"
 */
isBackgroundMusicPlaying : function () {},

/**
 * @method getEffectsVolume
 * @return A value converted from C/C++ "float"
 */
getEffectsVolume : function () {},

/**
 * @method setBackgroundMusicVolume
 * @param {float}
 */
setBackgroundMusicVolume : function () {},

/**
 * @method stopEffect
 * @param {unsigned int}
 */
stopEffect : function () {},

/**
 * @method stopBackgroundMusic
 */
stopBackgroundMusic : function () {},

/**
 * @method playBackgroundMusic
 * @param {const char*}
 * @param {bool}
 */
playBackgroundMusic : function () {},

/**
 * @method pauseAllEffects
 */
pauseAllEffects : function () {},

/**
 * @method preloadBackgroundMusic
 * @param {const char*}
 */
preloadBackgroundMusic : function () {},

/**
 * @method resumeBackgroundMusic
 */
resumeBackgroundMusic : function () {},

/**
 * @method playEffect
 * @return A value converted from C/C++ "unsigned int"
 * @param {const char*}
 * @param {bool}
 * @param {float}
 * @param {float}
 * @param {float}
 */
playEffect : function () {},

/**
 * @method rewindBackgroundMusic
 */
rewindBackgroundMusic : function () {},

/**
 * @method willPlayBackgroundMusic
 * @return A value converted from C/C++ "bool"
 */
willPlayBackgroundMusic : function () {},

/**
 * @method unloadEffect
 * @param {const char*}
 */
unloadEffect : function () {},

/**
 * @method preloadEffect
 * @param {const char*}
 */
preloadEffect : function () {},

/**
 * @method setEffectsVolume
 * @param {float}
 */
setEffectsVolume : function () {},

/**
 * @method pauseEffect
 * @param {unsigned int}
 */
pauseEffect : function () {},

/**
 * @method resumeAllEffects
 */
resumeAllEffects : function () {},

/**
 * @method pauseBackgroundMusic
 */
pauseBackgroundMusic : function () {},

/**
 * @method resumeEffect
 * @param {unsigned int}
 */
resumeEffect : function () {},

/**
 * @method end
 */
end : function () {},

/**
 * @method getInstance
 * @return A value converted from C/C++ "CocosDenshion::SimpleAudioEngine*"
 */
getInstance : function () {},

};
