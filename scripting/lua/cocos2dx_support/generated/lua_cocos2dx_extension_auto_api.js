/**
 * @module cocos2dx_extension
 */
var cc = cc || {};

/**
 * @class Control
 */
cc.Control = {

/**
 * @method setEnabled
 * @param {bool}
 */
setEnabled : function () {},

/**
 * @method getState
 * @return A value converted from C/C++ "cocos2d::extension::Control::State"
 */
getState : function () {},

/**
 * @method isTouchInside
 * @return A value converted from C/C++ "bool"
 * @param {cocos2d::Touch*}
 */
isTouchInside : function () {},

/**
 * @method sendActionsForControlEvents
 * @param {cocos2d::extension::Control::EventType}
 */
sendActionsForControlEvents : function () {},

/**
 * @method setSelected
 * @param {bool}
 */
setSelected : function () {},

/**
 * @method registerWithTouchDispatcher
 */
registerWithTouchDispatcher : function () {},

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
 * @method needsLayout
 */
needsLayout : function () {},

/**
 * @method hasVisibleParents
 * @return A value converted from C/C++ "bool"
 */
hasVisibleParents : function () {},

/**
 * @method isSelected
 * @return A value converted from C/C++ "bool"
 */
isSelected : function () {},

/**
 * @method init
 * @return A value converted from C/C++ "bool"
 */
init : function () {},

/**
 * @method setHighlighted
 * @param {bool}
 */
setHighlighted : function () {},

/**
 * @method isOpacityModifyRGB
 * @return A value converted from C/C++ "bool"
 */
isOpacityModifyRGB : function () {},

/**
 * @method getTouchLocation
 * @return A value converted from C/C++ "cocos2d::Point"
 * @param {cocos2d::Touch*}
 */
getTouchLocation : function () {},

/**
 * @method isHighlighted
 * @return A value converted from C/C++ "bool"
 */
isHighlighted : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::extension::Control*"
 */
create : function () {},

/**
 * @method Control
 * @constructor
 */
Control : function () {},

};

/**
 * @class CCBReader
 */
cc._Reader = {

/**
 * @method addOwnerOutletName
 * @param {std::string}
 */
addOwnerOutletName : function () {},

/**
 * @method getOwnerCallbackNames
 * @return A value converted from C/C++ "cocos2d::Array*"
 */
getOwnerCallbackNames : function () {},

/**
 * @method addDocumentCallbackControlEvents
 * @param {cocos2d::extension::Control::EventType}
 */
addDocumentCallbackControlEvents : function () {},

/**
 * @method setCCBRootPath
 * @param {const char*}
 */
setCCBRootPath : function () {},

/**
 * @method addOwnerOutletNode
 * @param {cocos2d::Node*}
 */
addOwnerOutletNode : function () {},

/**
 * @method getOwnerCallbackNodes
 * @return A value converted from C/C++ "cocos2d::Array*"
 */
getOwnerCallbackNodes : function () {},

/**
 * @method readSoundKeyframesForSeq
 * @return A value converted from C/C++ "bool"
 * @param {cocos2d::extension::CCBSequence*}
 */
readSoundKeyframesForSeq : function () {},

/**
 * @method getCCBRootPath
 * @return A value converted from C/C++ "std::string"
 */
getCCBRootPath : function () {},

/**
 * @method getOwnerCallbackControlEvents
 * @return A value converted from C/C++ "cocos2d::Array*"
 */
getOwnerCallbackControlEvents : function () {},

/**
 * @method getOwnerOutletNodes
 * @return A value converted from C/C++ "cocos2d::Array*"
 */
getOwnerOutletNodes : function () {},

/**
 * @method readUTF8
 * @return A value converted from C/C++ "std::string"
 */
readUTF8 : function () {},

/**
 * @method addOwnerCallbackControlEvents
 * @param {cocos2d::extension::Control::EventType}
 */
addOwnerCallbackControlEvents : function () {},

/**
 * @method getOwnerOutletNames
 * @return A value converted from C/C++ "cocos2d::Array*"
 */
getOwnerOutletNames : function () {},

/**
 * @method setAnimationManager
 * @param {cocos2d::extension::CCBAnimationManager*}
 */
setAnimationManager : function () {},

/**
 * @method readCallbackKeyframesForSeq
 * @return A value converted from C/C++ "bool"
 * @param {cocos2d::extension::CCBSequence*}
 */
readCallbackKeyframesForSeq : function () {},

/**
 * @method getAnimationManagersForNodes
 * @return A value converted from C/C++ "cocos2d::Array*"
 */
getAnimationManagersForNodes : function () {},

/**
 * @method getNodesWithAnimationManagers
 * @return A value converted from C/C++ "cocos2d::Array*"
 */
getNodesWithAnimationManagers : function () {},

/**
 * @method getAnimationManager
 * @return A value converted from C/C++ "cocos2d::extension::CCBAnimationManager*"
 */
getAnimationManager : function () {},

/**
 * @method setResolutionScale
 * @param {float}
 */
setResolutionScale : function () {},

};

/**
 * @class Scale9Sprite
 */
cc.Scale9Sprite = {

/**
 * @method resizableSpriteWithCapInsets
 * @return A value converted from C/C++ "cocos2d::extension::Scale9Sprite*"
 * @param {cocos2d::Rect}
 */
resizableSpriteWithCapInsets : function () {},

/**
 * @method setOpacityModifyRGB
 * @param {bool}
 */
setOpacityModifyRGB : function () {},

/**
 * @method setContentSize
 * @param {cocos2d::Size}
 */
setContentSize : function () {},

/**
 * @method setInsetBottom
 * @param {float}
 */
setInsetBottom : function () {},

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
 * @method setInsetTop
 * @param {float}
 */
setInsetTop : function () {},

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
 * @method setPreferredSize
 * @param {cocos2d::Size}
 */
setPreferredSize : function () {},

/**
 * @method getOpacity
 * @return A value converted from C/C++ "unsigned char"
 */
getOpacity : function () {},

/**
 * @method setSpriteFrame
 * @param {cocos2d::SpriteFrame*}
 */
setSpriteFrame : function () {},

/**
 * @method getColor
 * @return A value converted from C/C++ "cocos2d::Color3B"
 */
getColor : function () {},

/**
 * @method getInsetBottom
 * @return A value converted from C/C++ "float"
 */
getInsetBottom : function () {},

/**
 * @method getCapInsets
 * @return A value converted from C/C++ "cocos2d::Rect"
 */
getCapInsets : function () {},

/**
 * @method updateWithBatchNode
 * @return A value converted from C/C++ "bool"
 * @param {cocos2d::SpriteBatchNode*}
 * @param {cocos2d::Rect}
 * @param {bool}
 * @param {cocos2d::Rect}
 */
updateWithBatchNode : function () {},

/**
 * @method getInsetRight
 * @return A value converted from C/C++ "float"
 */
getInsetRight : function () {},

/**
 * @method getOriginalSize
 * @return A value converted from C/C++ "cocos2d::Size"
 */
getOriginalSize : function () {},

/**
 * @method setColor
 * @param {cocos2d::Color3B}
 */
setColor : function () {},

/**
 * @method getInsetTop
 * @return A value converted from C/C++ "float"
 */
getInsetTop : function () {},

/**
 * @method setInsetLeft
 * @param {float}
 */
setInsetLeft : function () {},

/**
 * @method getPreferredSize
 * @return A value converted from C/C++ "cocos2d::Size"
 */
getPreferredSize : function () {},

/**
 * @method setCapInsets
 * @param {cocos2d::Rect}
 */
setCapInsets : function () {},

/**
 * @method getInsetLeft
 * @return A value converted from C/C++ "float"
 */
getInsetLeft : function () {},

/**
 * @method updateDisplayedColor
 * @param {cocos2d::Color3B}
 */
updateDisplayedColor : function () {},

/**
 * @method setInsetRight
 * @param {float}
 */
setInsetRight : function () {},

/**
 * @method Scale9Sprite
 * @constructor
 */
Scale9Sprite : function () {},

};

/**
 * @class ControlButton
 */
cc.ControlButton = {

/**
 * @method setTitleColorDispatchTable
 * @param {cocos2d::Dictionary*}
 */
setTitleColorDispatchTable : function () {},

/**
 * @method isPushed
 * @return A value converted from C/C++ "bool"
 */
isPushed : function () {},

/**
 * @method setSelected
 * @param {bool}
 */
setSelected : function () {},

/**
 * @method setTitleLabelForState
 * @param {cocos2d::Node*}
 * @param {cocos2d::extension::Control::State}
 */
setTitleLabelForState : function () {},

/**
 * @method ccTouchBegan
 * @return A value converted from C/C++ "bool"
 * @param {cocos2d::Touch*}
 * @param {cocos2d::Event*}
 */
ccTouchBegan : function () {},

/**
 * @method setAdjustBackgroundImage
 * @param {bool}
 */
setAdjustBackgroundImage : function () {},

/**
 * @method ccTouchEnded
 * @param {cocos2d::Touch*}
 * @param {cocos2d::Event*}
 */
ccTouchEnded : function () {},

/**
 * @method setHighlighted
 * @param {bool}
 */
setHighlighted : function () {},

/**
 * @method setZoomOnTouchDown
 * @param {bool}
 */
setZoomOnTouchDown : function () {},

/**
 * @method setBackgroundSpriteDispatchTable
 * @param {cocos2d::Dictionary*}
 */
setBackgroundSpriteDispatchTable : function () {},

/**
 * @method setTitleForState
 * @param {cocos2d::String*}
 * @param {cocos2d::extension::Control::State}
 */
setTitleForState : function () {},

/**
 * @method getTitleDispatchTable
 * @return A value converted from C/C++ "cocos2d::Dictionary*"
 */
getTitleDispatchTable : function () {},

/**
 * @method setLabelAnchorPoint
 * @param {cocos2d::Point}
 */
setLabelAnchorPoint : function () {},

/**
 * @method getPreferredSize
 * @return A value converted from C/C++ "cocos2d::Size"
 */
getPreferredSize : function () {},

/**
 * @method getLabelAnchorPoint
 * @return A value converted from C/C++ "cocos2d::Point"
 */
getLabelAnchorPoint : function () {},

/**
 * @method initWithBackgroundSprite
 * @return A value converted from C/C++ "bool"
 * @param {cocos2d::extension::Scale9Sprite*}
 */
initWithBackgroundSprite : function () {},

/**
 * @method getTitleTTFSizeForState
 * @return A value converted from C/C++ "float"
 * @param {cocos2d::extension::Control::State}
 */
getTitleTTFSizeForState : function () {},

/**
 * @method setTitleDispatchTable
 * @param {cocos2d::Dictionary*}
 */
setTitleDispatchTable : function () {},

/**
 * @method setOpacity
 * @param {unsigned char}
 */
setOpacity : function () {},

/**
 * @method init
 * @return A value converted from C/C++ "bool"
 */
init : function () {},

/**
 * @method setTitleTTFForState
 * @param {const char*}
 * @param {cocos2d::extension::Control::State}
 */
setTitleTTFForState : function () {},

/**
 * @method setTitleTTFSizeForState
 * @param {float}
 * @param {cocos2d::extension::Control::State}
 */
setTitleTTFSizeForState : function () {},

/**
 * @method setTitleLabel
 * @param {cocos2d::Node*}
 */
setTitleLabel : function () {},

/**
 * @method ccTouchMoved
 * @param {cocos2d::Touch*}
 * @param {cocos2d::Event*}
 */
ccTouchMoved : function () {},

/**
 * @method getOpacity
 * @return A value converted from C/C++ "unsigned char"
 */
getOpacity : function () {},

/**
 * @method getCurrentTitleColor
 * @return A value converted from C/C++ "cocos2d::Color3B"
 */
getCurrentTitleColor : function () {},

/**
 * @method getTitleColorDispatchTable
 * @return A value converted from C/C++ "cocos2d::Dictionary*"
 */
getTitleColorDispatchTable : function () {},

/**
 * @method setEnabled
 * @param {bool}
 */
setEnabled : function () {},

/**
 * @method setBackgroundSprite
 * @param {cocos2d::extension::Scale9Sprite*}
 */
setBackgroundSprite : function () {},

/**
 * @method getBackgroundSpriteForState
 * @return A value converted from C/C++ "cocos2d::extension::Scale9Sprite*"
 * @param {cocos2d::extension::Control::State}
 */
getBackgroundSpriteForState : function () {},

/**
 * @method getColor
 * @return A value converted from C/C++ "cocos2d::Color3B"
 */
getColor : function () {},

/**
 * @method setMargins
 * @param {int}
 * @param {int}
 */
setMargins : function () {},

/**
 * @method needsLayout
 */
needsLayout : function () {},

/**
 * @method initWithTitleAndFontNameAndFontSize
 * @return A value converted from C/C++ "bool"
 * @param {std::string}
 * @param {const char*}
 * @param {float}
 */
initWithTitleAndFontNameAndFontSize : function () {},

/**
 * @method getCurrentTitle
 * @return A value converted from C/C++ "cocos2d::String*"
 */
getCurrentTitle : function () {},

/**
 * @method getHorizontalOrigin
 * @return A value converted from C/C++ "int"
 */
getHorizontalOrigin : function () {},

/**
 * @method getTitleTTFForState
 * @return A value converted from C/C++ "const char*"
 * @param {cocos2d::extension::Control::State}
 */
getTitleTTFForState : function () {},

/**
 * @method getBackgroundSprite
 * @return A value converted from C/C++ "cocos2d::extension::Scale9Sprite*"
 */
getBackgroundSprite : function () {},

/**
 * @method getTitleColorForState
 * @return A value converted from C/C++ "cocos2d::Color3B"
 * @param {cocos2d::extension::Control::State}
 */
getTitleColorForState : function () {},

/**
 * @method setTitleColorForState
 * @param {cocos2d::Color3B}
 * @param {cocos2d::extension::Control::State}
 */
setTitleColorForState : function () {},

/**
 * @method doesAdjustBackgroundImage
 * @return A value converted from C/C++ "bool"
 */
doesAdjustBackgroundImage : function () {},

/**
 * @method setBackgroundSpriteFrameForState
 * @param {cocos2d::SpriteFrame*}
 * @param {cocos2d::extension::Control::State}
 */
setBackgroundSpriteFrameForState : function () {},

/**
 * @method setBackgroundSpriteForState
 * @param {cocos2d::extension::Scale9Sprite*}
 * @param {cocos2d::extension::Control::State}
 */
setBackgroundSpriteForState : function () {},

/**
 * @method setColor
 * @param {cocos2d::Color3B}
 */
setColor : function () {},

/**
 * @method getTitleLabelDispatchTable
 * @return A value converted from C/C++ "cocos2d::Dictionary*"
 */
getTitleLabelDispatchTable : function () {},

/**
 * @method initWithLabelAndBackgroundSprite
 * @return A value converted from C/C++ "bool"
 * @param {cocos2d::Node*}
 * @param {cocos2d::extension::Scale9Sprite*}
 */
initWithLabelAndBackgroundSprite : function () {},

/**
 * @method setPreferredSize
 * @param {cocos2d::Size}
 */
setPreferredSize : function () {},

/**
 * @method setTitleLabelDispatchTable
 * @param {cocos2d::Dictionary*}
 */
setTitleLabelDispatchTable : function () {},

/**
 * @method getTitleLabel
 * @return A value converted from C/C++ "cocos2d::Node*"
 */
getTitleLabel : function () {},

/**
 * @method ccTouchCancelled
 * @param {cocos2d::Touch*}
 * @param {cocos2d::Event*}
 */
ccTouchCancelled : function () {},

/**
 * @method getVerticalMargin
 * @return A value converted from C/C++ "int"
 */
getVerticalMargin : function () {},

/**
 * @method getBackgroundSpriteDispatchTable
 * @return A value converted from C/C++ "cocos2d::Dictionary*"
 */
getBackgroundSpriteDispatchTable : function () {},

/**
 * @method getTitleLabelForState
 * @return A value converted from C/C++ "cocos2d::Node*"
 * @param {cocos2d::extension::Control::State}
 */
getTitleLabelForState : function () {},

/**
 * @method setTitleBMFontForState
 * @param {const char*}
 * @param {cocos2d::extension::Control::State}
 */
setTitleBMFontForState : function () {},

/**
 * @method getTitleBMFontForState
 * @return A value converted from C/C++ "const char*"
 * @param {cocos2d::extension::Control::State}
 */
getTitleBMFontForState : function () {},

/**
 * @method getZoomOnTouchDown
 * @return A value converted from C/C++ "bool"
 */
getZoomOnTouchDown : function () {},

/**
 * @method getTitleForState
 * @return A value converted from C/C++ "cocos2d::String*"
 * @param {cocos2d::extension::Control::State}
 */
getTitleForState : function () {},

/**
 * @method ControlButton
 * @constructor
 */
ControlButton : function () {},

};

/**
 * @class ScrollView
 */
cc.ScrollView = {

/**
 * @method isClippingToBounds
 * @return A value converted from C/C++ "bool"
 */
isClippingToBounds : function () {},

/**
 * @method setContainer
 * @param {cocos2d::Node*}
 */
setContainer : function () {},

/**
 * @method setContentOffsetInDuration
 * @param {cocos2d::Point}
 * @param {float}
 */
setContentOffsetInDuration : function () {},

/**
 * @method setZoomScaleInDuration
 * @param {float}
 * @param {float}
 */
setZoomScaleInDuration : function () {},

/**
 * @method ccTouchBegan
 * @return A value converted from C/C++ "bool"
 * @param {cocos2d::Touch*}
 * @param {cocos2d::Event*}
 */
ccTouchBegan : function () {},

/**
 * @method getContainer
 * @return A value converted from C/C++ "cocos2d::Node*"
 */
getContainer : function () {},

/**
 * @method ccTouchEnded
 * @param {cocos2d::Touch*}
 * @param {cocos2d::Event*}
 */
ccTouchEnded : function () {},

/**
 * @method getDirection
 * @return A value converted from C/C++ "cocos2d::extension::ScrollView::Direction"
 */
getDirection : function () {},

/**
 * @method getZoomScale
 * @return A value converted from C/C++ "float"
 */
getZoomScale : function () {},

/**
 * @method updateInset
 */
updateInset : function () {},

/**
 * @method initWithViewSize
 * @return A value converted from C/C++ "bool"
 * @param {cocos2d::Size}
 * @param {cocos2d::Node*}
 */
initWithViewSize : function () {},

/**
 * @method pause
 * @param {cocos2d::Object*}
 */
pause : function () {},

/**
 * @method setDirection
 * @param {cocos2d::extension::ScrollView::Direction}
 */
setDirection : function () {},

/**
 * @method setBounceable
 * @param {bool}
 */
setBounceable : function () {},

/**
 * @method setContentOffset
 * @param {cocos2d::Point}
 * @param {bool}
 */
setContentOffset : function () {},

/**
 * @method isDragging
 * @return A value converted from C/C++ "bool"
 */
isDragging : function () {},

/**
 * @method init
 * @return A value converted from C/C++ "bool"
 */
init : function () {},

/**
 * @method isBounceable
 * @return A value converted from C/C++ "bool"
 */
isBounceable : function () {},

/**
 * @method getContentSize
 * @return A value converted from C/C++ "cocos2d::Size"
 */
getContentSize : function () {},

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
 * @method getContentOffset
 * @return A value converted from C/C++ "cocos2d::Point"
 */
getContentOffset : function () {},

/**
 * @method resume
 * @param {cocos2d::Object*}
 */
resume : function () {},

/**
 * @method setClippingToBounds
 * @param {bool}
 */
setClippingToBounds : function () {},

/**
 * @method setViewSize
 * @param {cocos2d::Size}
 */
setViewSize : function () {},

/**
 * @method getViewSize
 * @return A value converted from C/C++ "cocos2d::Size"
 */
getViewSize : function () {},

/**
 * @method maxContainerOffset
 * @return A value converted from C/C++ "cocos2d::Point"
 */
maxContainerOffset : function () {},

/**
 * @method setContentSize
 * @param {cocos2d::Size}
 */
setContentSize : function () {},

/**
 * @method isTouchMoved
 * @return A value converted from C/C++ "bool"
 */
isTouchMoved : function () {},

/**
 * @method isNodeVisible
 * @return A value converted from C/C++ "bool"
 * @param {cocos2d::Node*}
 */
isNodeVisible : function () {},

/**
 * @method ccTouchCancelled
 * @param {cocos2d::Touch*}
 * @param {cocos2d::Event*}
 */
ccTouchCancelled : function () {},

/**
 * @method minContainerOffset
 * @return A value converted from C/C++ "cocos2d::Point"
 */
minContainerOffset : function () {},

/**
 * @method registerWithTouchDispatcher
 */
registerWithTouchDispatcher : function () {},

/**
 * @method ScrollView
 * @constructor
 */
ScrollView : function () {},

};

/**
 * @class CCBAnimationManager
 */
cc.AnimationManager = {

/**
 * @method moveAnimationsFromNode
 * @param {cocos2d::Node*}
 * @param {cocos2d::Node*}
 */
moveAnimationsFromNode : function () {},

/**
 * @method setAutoPlaySequenceId
 * @param {int}
 */
setAutoPlaySequenceId : function () {},

/**
 * @method getDocumentCallbackNames
 * @return A value converted from C/C++ "cocos2d::Array*"
 */
getDocumentCallbackNames : function () {},

/**
 * @method actionForSoundChannel
 * @return A value converted from C/C++ "cocos2d::Object*"
 * @param {cocos2d::extension::CCBSequenceProperty*}
 */
actionForSoundChannel : function () {},

/**
 * @method setBaseValue
 * @param {cocos2d::Object*}
 * @param {cocos2d::Node*}
 * @param {const char*}
 */
setBaseValue : function () {},

/**
 * @method getDocumentOutletNodes
 * @return A value converted from C/C++ "cocos2d::Array*"
 */
getDocumentOutletNodes : function () {},

/**
 * @method addNode
 * @param {cocos2d::Node*}
 * @param {cocos2d::Dictionary*}
 */
addNode : function () {},

/**
 * @method getLastCompletedSequenceName
 * @return A value converted from C/C++ "std::string"
 */
getLastCompletedSequenceName : function () {},

/**
 * @method setRootNode
 * @param {cocos2d::Node*}
 */
setRootNode : function () {},

/**
 * @method runAnimationsForSequenceNamedTweenDuration
 * @param {const char*}
 * @param {float}
 */
runAnimationsForSequenceNamedTweenDuration : function () {},

/**
 * @method addDocumentOutletName
 * @param {std::string}
 */
addDocumentOutletName : function () {},

/**
 * @method getSequences
 * @return A value converted from C/C++ "cocos2d::Array*"
 */
getSequences : function () {},

/**
 * @method getRootContainerSize
 * @return A value converted from C/C++ "cocos2d::Size"
 */
getRootContainerSize : function () {},

/**
 * @method setDocumentControllerName
 * @param {std::string}
 */
setDocumentControllerName : function () {},

/**
 * @method getContainerSize
 * @return A value converted from C/C++ "cocos2d::Size"
 * @param {cocos2d::Node*}
 */
getContainerSize : function () {},

/**
 * @method actionForCallbackChannel
 * @return A value converted from C/C++ "cocos2d::Object*"
 * @param {cocos2d::extension::CCBSequenceProperty*}
 */
actionForCallbackChannel : function () {},

/**
 * @method getDocumentOutletNames
 * @return A value converted from C/C++ "cocos2d::Array*"
 */
getDocumentOutletNames : function () {},

/**
 * @method addDocumentCallbackControlEvents
 * @param {cocos2d::extension::Control::EventType}
 */
addDocumentCallbackControlEvents : function () {},

/**
 * @method init
 * @return A value converted from C/C++ "bool"
 */
init : function () {},

/**
 * @method getKeyframeCallbacks
 * @return A value converted from C/C++ "cocos2d::Array*"
 */
getKeyframeCallbacks : function () {},

/**
 * @method getDocumentCallbackControlEvents
 * @return A value converted from C/C++ "cocos2d::Array*"
 */
getDocumentCallbackControlEvents : function () {},

/**
 * @method setRootContainerSize
 * @param {cocos2d::Size}
 */
setRootContainerSize : function () {},

/**
 * @method runAnimationsForSequenceIdTweenDuration
 * @param {int}
 * @param {float}
 */
runAnimationsForSequenceIdTweenDuration : function () {},

/**
 * @method getRunningSequenceName
 * @return A value converted from C/C++ "const char*"
 */
getRunningSequenceName : function () {},

/**
 * @method getAutoPlaySequenceId
 * @return A value converted from C/C++ "int"
 */
getAutoPlaySequenceId : function () {},

/**
 * @method addDocumentCallbackName
 * @param {std::string}
 */
addDocumentCallbackName : function () {},

/**
 * @method getRootNode
 * @return A value converted from C/C++ "cocos2d::Node*"
 */
getRootNode : function () {},

/**
 * @method addDocumentOutletNode
 * @param {cocos2d::Node*}
 */
addDocumentOutletNode : function () {},

/**
 * @method getSequenceDuration
 * @return A value converted from C/C++ "float"
 * @param {const char*}
 */
getSequenceDuration : function () {},

/**
 * @method addDocumentCallbackNode
 * @param {cocos2d::Node*}
 */
addDocumentCallbackNode : function () {},

/**
 * @method runAnimationsForSequenceNamed
 * @param {const char*}
 */
runAnimationsForSequenceNamed : function () {},

/**
 * @method getSequenceId
 * @return A value converted from C/C++ "int"
 * @param {const char*}
 */
getSequenceId : function () {},

/**
 * @method getDocumentCallbackNodes
 * @return A value converted from C/C++ "cocos2d::Array*"
 */
getDocumentCallbackNodes : function () {},

/**
 * @method setSequences
 * @param {cocos2d::Array*}
 */
setSequences : function () {},

/**
 * @method debug
 */
debug : function () {},

/**
 * @method getDocumentControllerName
 * @return A value converted from C/C++ "std::string"
 */
getDocumentControllerName : function () {},

/**
 * @method CCBAnimationManager
 * @constructor
 */
CCBAnimationManager : function () {},

};

/**
 * @class ControlHuePicker
 */
cc.ControlHuePicker = {

/**
 * @method setEnabled
 * @param {bool}
 */
setEnabled : function () {},

/**
 * @method initWithTargetAndPos
 * @return A value converted from C/C++ "bool"
 * @param {cocos2d::Node*}
 * @param {cocos2d::Point}
 */
initWithTargetAndPos : function () {},

/**
 * @method setHue
 * @param {float}
 */
setHue : function () {},

/**
 * @method getStartPos
 * @return A value converted from C/C++ "cocos2d::Point"
 */
getStartPos : function () {},

/**
 * @method getHue
 * @return A value converted from C/C++ "float"
 */
getHue : function () {},

/**
 * @method ccTouchBegan
 * @return A value converted from C/C++ "bool"
 * @param {cocos2d::Touch*}
 * @param {cocos2d::Event*}
 */
ccTouchBegan : function () {},

/**
 * @method setBackground
 * @param {cocos2d::Sprite*}
 */
setBackground : function () {},

/**
 * @method setHuePercentage
 * @param {float}
 */
setHuePercentage : function () {},

/**
 * @method getBackground
 * @return A value converted from C/C++ "cocos2d::Sprite*"
 */
getBackground : function () {},

/**
 * @method ccTouchMoved
 * @param {cocos2d::Touch*}
 * @param {cocos2d::Event*}
 */
ccTouchMoved : function () {},

/**
 * @method getSlider
 * @return A value converted from C/C++ "cocos2d::Sprite*"
 */
getSlider : function () {},

/**
 * @method getHuePercentage
 * @return A value converted from C/C++ "float"
 */
getHuePercentage : function () {},

/**
 * @method setSlider
 * @param {cocos2d::Sprite*}
 */
setSlider : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::extension::ControlHuePicker*"
 * @param {cocos2d::Node*}
 * @param {cocos2d::Point}
 */
create : function () {},

/**
 * @method ControlHuePicker
 * @constructor
 */
ControlHuePicker : function () {},

};

/**
 * @class ControlSaturationBrightnessPicker
 */
cc.ControlSaturationBrightnessPicker = {

/**
 * @method getShadow
 * @return A value converted from C/C++ "cocos2d::Sprite*"
 */
getShadow : function () {},

/**
 * @method initWithTargetAndPos
 * @return A value converted from C/C++ "bool"
 * @param {cocos2d::Node*}
 * @param {cocos2d::Point}
 */
initWithTargetAndPos : function () {},

/**
 * @method getStartPos
 * @return A value converted from C/C++ "cocos2d::Point"
 */
getStartPos : function () {},

/**
 * @method getOverlay
 * @return A value converted from C/C++ "cocos2d::Sprite*"
 */
getOverlay : function () {},

/**
 * @method setEnabled
 * @param {bool}
 */
setEnabled : function () {},

/**
 * @method getSlider
 * @return A value converted from C/C++ "cocos2d::Sprite*"
 */
getSlider : function () {},

/**
 * @method getBackground
 * @return A value converted from C/C++ "cocos2d::Sprite*"
 */
getBackground : function () {},

/**
 * @method getSaturation
 * @return A value converted from C/C++ "float"
 */
getSaturation : function () {},

/**
 * @method getBrightness
 * @return A value converted from C/C++ "float"
 */
getBrightness : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::extension::ControlSaturationBrightnessPicker*"
 * @param {cocos2d::Node*}
 * @param {cocos2d::Point}
 */
create : function () {},

/**
 * @method ControlSaturationBrightnessPicker
 * @constructor
 */
ControlSaturationBrightnessPicker : function () {},

};

/**
 * @class ControlColourPicker
 */
cc.ControlColourPicker = {

/**
 * @method setEnabled
 * @param {bool}
 */
setEnabled : function () {},

/**
 * @method getHuePicker
 * @return A value converted from C/C++ "cocos2d::extension::ControlHuePicker*"
 */
getHuePicker : function () {},

/**
 * @method setColor
 * @param {cocos2d::Color3B}
 */
setColor : function () {},

/**
 * @method hueSliderValueChanged
 * @param {cocos2d::Object*}
 * @param {cocos2d::extension::Control::EventType}
 */
hueSliderValueChanged : function () {},

/**
 * @method getcolourPicker
 * @return A value converted from C/C++ "cocos2d::extension::ControlSaturationBrightnessPicker*"
 */
getcolourPicker : function () {},

/**
 * @method setBackground
 * @param {cocos2d::Sprite*}
 */
setBackground : function () {},

/**
 * @method init
 * @return A value converted from C/C++ "bool"
 */
init : function () {},

/**
 * @method setcolourPicker
 * @param {cocos2d::extension::ControlSaturationBrightnessPicker*}
 */
setcolourPicker : function () {},

/**
 * @method colourSliderValueChanged
 * @param {cocos2d::Object*}
 * @param {cocos2d::extension::Control::EventType}
 */
colourSliderValueChanged : function () {},

/**
 * @method setHuePicker
 * @param {cocos2d::extension::ControlHuePicker*}
 */
setHuePicker : function () {},

/**
 * @method getBackground
 * @return A value converted from C/C++ "cocos2d::Sprite*"
 */
getBackground : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::extension::ControlColourPicker*"
 */
create : function () {},

/**
 * @method ControlColourPicker
 * @constructor
 */
ControlColourPicker : function () {},

};

/**
 * @class ControlPotentiometer
 */
cc.ControlPotentiometer = {

/**
 * @method setPreviousLocation
 * @param {cocos2d::Point}
 */
setPreviousLocation : function () {},

/**
 * @method setProgressTimer
 * @param {cocos2d::ProgressTimer*}
 */
setProgressTimer : function () {},

/**
 * @method potentiometerMoved
 * @param {cocos2d::Point}
 */
potentiometerMoved : function () {},

/**
 * @method ccTouchEnded
 * @param {cocos2d::Touch*}
 * @param {cocos2d::Event*}
 */
ccTouchEnded : function () {},

/**
 * @method getMinimumValue
 * @return A value converted from C/C++ "float"
 */
getMinimumValue : function () {},

/**
 * @method setThumbSprite
 * @param {cocos2d::Sprite*}
 */
setThumbSprite : function () {},

/**
 * @method ccTouchMoved
 * @param {cocos2d::Touch*}
 * @param {cocos2d::Event*}
 */
ccTouchMoved : function () {},

/**
 * @method ccTouchBegan
 * @return A value converted from C/C++ "bool"
 * @param {cocos2d::Touch*}
 * @param {cocos2d::Event*}
 */
ccTouchBegan : function () {},

/**
 * @method setEnabled
 * @param {bool}
 */
setEnabled : function () {},

/**
 * @method setValue
 * @param {float}
 */
setValue : function () {},

/**
 * @method setMaximumValue
 * @param {float}
 */
setMaximumValue : function () {},

/**
 * @method setMinimumValue
 * @param {float}
 */
setMinimumValue : function () {},

/**
 * @method potentiometerEnded
 * @param {cocos2d::Point}
 */
potentiometerEnded : function () {},

/**
 * @method distanceBetweenPointAndPoint
 * @return A value converted from C/C++ "float"
 * @param {cocos2d::Point}
 * @param {cocos2d::Point}
 */
distanceBetweenPointAndPoint : function () {},

/**
 * @method getProgressTimer
 * @return A value converted from C/C++ "cocos2d::ProgressTimer*"
 */
getProgressTimer : function () {},

/**
 * @method getMaximumValue
 * @return A value converted from C/C++ "float"
 */
getMaximumValue : function () {},

/**
 * @method angleInDegreesBetweenLineFromPoint_toPoint_toLineFromPoint_toPoint
 * @return A value converted from C/C++ "float"
 * @param {cocos2d::Point}
 * @param {cocos2d::Point}
 * @param {cocos2d::Point}
 * @param {cocos2d::Point}
 */
angleInDegreesBetweenLineFromPoint_toPoint_toLineFromPoint_toPoint : function () {},

/**
 * @method isTouchInside
 * @return A value converted from C/C++ "bool"
 * @param {cocos2d::Touch*}
 */
isTouchInside : function () {},

/**
 * @method getValue
 * @return A value converted from C/C++ "float"
 */
getValue : function () {},

/**
 * @method potentiometerBegan
 * @param {cocos2d::Point}
 */
potentiometerBegan : function () {},

/**
 * @method getThumbSprite
 * @return A value converted from C/C++ "cocos2d::Sprite*"
 */
getThumbSprite : function () {},

/**
 * @method initWithTrackSprite_ProgressTimer_ThumbSprite
 * @return A value converted from C/C++ "bool"
 * @param {cocos2d::Sprite*}
 * @param {cocos2d::ProgressTimer*}
 * @param {cocos2d::Sprite*}
 */
initWithTrackSprite_ProgressTimer_ThumbSprite : function () {},

/**
 * @method getPreviousLocation
 * @return A value converted from C/C++ "cocos2d::Point"
 */
getPreviousLocation : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::extension::ControlPotentiometer*"
 * @param {const char*}
 * @param {const char*}
 * @param {const char*}
 */
create : function () {},

/**
 * @method ControlPotentiometer
 * @constructor
 */
ControlPotentiometer : function () {},

};

/**
 * @class ControlSlider
 */
cc.ControlSlider = {

/**
 * @method locationFromTouch
 * @return A value converted from C/C++ "cocos2d::Point"
 * @param {cocos2d::Touch*}
 */
locationFromTouch : function () {},

/**
 * @method setProgressSprite
 * @param {cocos2d::Sprite*}
 */
setProgressSprite : function () {},

/**
 * @method getMaximumAllowedValue
 * @return A value converted from C/C++ "float"
 */
getMaximumAllowedValue : function () {},

/**
 * @method getMinimumAllowedValue
 * @return A value converted from C/C++ "float"
 */
getMinimumAllowedValue : function () {},

/**
 * @method getMinimumValue
 * @return A value converted from C/C++ "float"
 */
getMinimumValue : function () {},

/**
 * @method setThumbSprite
 * @param {cocos2d::Sprite*}
 */
setThumbSprite : function () {},

/**
 * @method setMinimumValue
 * @param {float}
 */
setMinimumValue : function () {},

/**
 * @method setMinimumAllowedValue
 * @param {float}
 */
setMinimumAllowedValue : function () {},

/**
 * @method setEnabled
 * @param {bool}
 */
setEnabled : function () {},

/**
 * @method setValue
 * @param {float}
 */
setValue : function () {},

/**
 * @method setMaximumValue
 * @param {float}
 */
setMaximumValue : function () {},

/**
 * @method needsLayout
 */
needsLayout : function () {},

/**
 * @method getBackgroundSprite
 * @return A value converted from C/C++ "cocos2d::Sprite*"
 */
getBackgroundSprite : function () {},

/**
 * @method initWithSprites
 * @return A value converted from C/C++ "bool"
 * @param {cocos2d::Sprite*}
 * @param {cocos2d::Sprite*}
 * @param {cocos2d::Sprite*}
 */
initWithSprites : function () {},

/**
 * @method getMaximumValue
 * @return A value converted from C/C++ "float"
 */
getMaximumValue : function () {},

/**
 * @method isTouchInside
 * @return A value converted from C/C++ "bool"
 * @param {cocos2d::Touch*}
 */
isTouchInside : function () {},

/**
 * @method getValue
 * @return A value converted from C/C++ "float"
 */
getValue : function () {},

/**
 * @method getThumbSprite
 * @return A value converted from C/C++ "cocos2d::Sprite*"
 */
getThumbSprite : function () {},

/**
 * @method getProgressSprite
 * @return A value converted from C/C++ "cocos2d::Sprite*"
 */
getProgressSprite : function () {},

/**
 * @method setBackgroundSprite
 * @param {cocos2d::Sprite*}
 */
setBackgroundSprite : function () {},

/**
 * @method setMaximumAllowedValue
 * @param {float}
 */
setMaximumAllowedValue : function () {},

/**
 * @method ControlSlider
 * @constructor
 */
ControlSlider : function () {},

};

/**
 * @class ControlStepper
 */
cc.ControlStepper = {

/**
 * @method setMinusSprite
 * @param {cocos2d::Sprite*}
 */
setMinusSprite : function () {},

/**
 * @method ccTouchBegan
 * @return A value converted from C/C++ "bool"
 * @param {cocos2d::Touch*}
 * @param {cocos2d::Event*}
 */
ccTouchBegan : function () {},

/**
 * @method getMinusLabel
 * @return A value converted from C/C++ "cocos2d::LabelTTF*"
 */
getMinusLabel : function () {},

/**
 * @method setWraps
 * @param {bool}
 */
setWraps : function () {},

/**
 * @method ccTouchEnded
 * @param {cocos2d::Touch*}
 * @param {cocos2d::Event*}
 */
ccTouchEnded : function () {},

/**
 * @method isContinuous
 * @return A value converted from C/C++ "bool"
 */
isContinuous : function () {},

/**
 * @method getMinusSprite
 * @return A value converted from C/C++ "cocos2d::Sprite*"
 */
getMinusSprite : function () {},

/**
 * @method updateLayoutUsingTouchLocation
 * @param {cocos2d::Point}
 */
updateLayoutUsingTouchLocation : function () {},

/**
 * @method setValueWithSendingEvent
 * @param {double}
 * @param {bool}
 */
setValueWithSendingEvent : function () {},

/**
 * @method getPlusLabel
 * @return A value converted from C/C++ "cocos2d::LabelTTF*"
 */
getPlusLabel : function () {},

/**
 * @method stopAutorepeat
 */
stopAutorepeat : function () {},

/**
 * @method ccTouchMoved
 * @param {cocos2d::Touch*}
 * @param {cocos2d::Event*}
 */
ccTouchMoved : function () {},

/**
 * @method setMaximumValue
 * @param {double}
 */
setMaximumValue : function () {},

/**
 * @method setPlusSprite
 * @param {cocos2d::Sprite*}
 */
setPlusSprite : function () {},

/**
 * @method setMinusLabel
 * @param {cocos2d::LabelTTF*}
 */
setMinusLabel : function () {},

/**
 * @method setValue
 * @param {double}
 */
setValue : function () {},

/**
 * @method setStepValue
 * @param {double}
 */
setStepValue : function () {},

/**
 * @method getPlusSprite
 * @return A value converted from C/C++ "cocos2d::Sprite*"
 */
getPlusSprite : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method setMinimumValue
 * @param {double}
 */
setMinimumValue : function () {},

/**
 * @method startAutorepeat
 */
startAutorepeat : function () {},

/**
 * @method initWithMinusSpriteAndPlusSprite
 * @return A value converted from C/C++ "bool"
 * @param {cocos2d::Sprite*}
 * @param {cocos2d::Sprite*}
 */
initWithMinusSpriteAndPlusSprite : function () {},

/**
 * @method getValue
 * @return A value converted from C/C++ "double"
 */
getValue : function () {},

/**
 * @method setPlusLabel
 * @param {cocos2d::LabelTTF*}
 */
setPlusLabel : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::extension::ControlStepper*"
 * @param {cocos2d::Sprite*}
 * @param {cocos2d::Sprite*}
 */
create : function () {},

/**
 * @method ControlStepper
 * @constructor
 */
ControlStepper : function () {},

};

/**
 * @class ControlSwitch
 */
cc.ControlSwitch = {

/**
 * @method setEnabled
 * @param {bool}
 */
setEnabled : function () {},

/**
 * @method ccTouchBegan
 * @return A value converted from C/C++ "bool"
 * @param {cocos2d::Touch*}
 * @param {cocos2d::Event*}
 */
ccTouchBegan : function () {},

/**
 * @method isOn
 * @return A value converted from C/C++ "bool"
 */
isOn : function () {},

/**
 * @method ccTouchCancelled
 * @param {cocos2d::Touch*}
 * @param {cocos2d::Event*}
 */
ccTouchCancelled : function () {},

/**
 * @method ccTouchEnded
 * @param {cocos2d::Touch*}
 * @param {cocos2d::Event*}
 */
ccTouchEnded : function () {},

/**
 * @method ccTouchMoved
 * @param {cocos2d::Touch*}
 * @param {cocos2d::Event*}
 */
ccTouchMoved : function () {},

/**
 * @method hasMoved
 * @return A value converted from C/C++ "bool"
 */
hasMoved : function () {},

/**
 * @method locationFromTouch
 * @return A value converted from C/C++ "cocos2d::Point"
 * @param {cocos2d::Touch*}
 */
locationFromTouch : function () {},

/**
 * @method ControlSwitch
 * @constructor
 */
ControlSwitch : function () {},

};

/**
 * @class TableViewCell
 */
cc.TableViewCell = {

/**
 * @method reset
 */
reset : function () {},

/**
 * @method setIdx
 * @param {unsigned int}
 */
setIdx : function () {},

/**
 * @method setObjectID
 * @param {unsigned int}
 */
setObjectID : function () {},

/**
 * @method getObjectID
 * @return A value converted from C/C++ "unsigned int"
 */
getObjectID : function () {},

/**
 * @method getIdx
 * @return A value converted from C/C++ "unsigned int"
 */
getIdx : function () {},

/**
 * @method TableViewCell
 * @constructor
 */
TableViewCell : function () {},

};

/**
 * @class TableView
 */
cc.TableView = {

/**
 * @method updateCellAtIndex
 * @param {unsigned int}
 */
updateCellAtIndex : function () {},

/**
 * @method setVerticalFillOrder
 * @param {cocos2d::extension::TableView::VerticalFillOrder}
 */
setVerticalFillOrder : function () {},

/**
 * @method scrollViewDidZoom
 * @param {cocos2d::extension::ScrollView*}
 */
scrollViewDidZoom : function () {},

/**
 * @method ccTouchBegan
 * @return A value converted from C/C++ "bool"
 * @param {cocos2d::Touch*}
 * @param {cocos2d::Event*}
 */
ccTouchBegan : function () {},

/**
 * @method getVerticalFillOrder
 * @return A value converted from C/C++ "cocos2d::extension::TableView::VerticalFillOrder"
 */
getVerticalFillOrder : function () {},

/**
 * @method removeCellAtIndex
 * @param {unsigned int}
 */
removeCellAtIndex : function () {},

/**
 * @method initWithViewSize
 * @return A value converted from C/C++ "bool"
 * @param {cocos2d::Size}
 * @param {cocos2d::Node*}
 */
initWithViewSize : function () {},

/**
 * @method scrollViewDidScroll
 * @param {cocos2d::extension::ScrollView*}
 */
scrollViewDidScroll : function () {},

/**
 * @method reloadData
 */
reloadData : function () {},

/**
 * @method ccTouchCancelled
 * @param {cocos2d::Touch*}
 * @param {cocos2d::Event*}
 */
ccTouchCancelled : function () {},

/**
 * @method ccTouchEnded
 * @param {cocos2d::Touch*}
 * @param {cocos2d::Event*}
 */
ccTouchEnded : function () {},

/**
 * @method ccTouchMoved
 * @param {cocos2d::Touch*}
 * @param {cocos2d::Event*}
 */
ccTouchMoved : function () {},

/**
 * @method _updateContentSize
 */
_updateContentSize : function () {},

/**
 * @method insertCellAtIndex
 * @param {unsigned int}
 */
insertCellAtIndex : function () {},

/**
 * @method cellAtIndex
 * @return A value converted from C/C++ "cocos2d::extension::TableViewCell*"
 * @param {unsigned int}
 */
cellAtIndex : function () {},

/**
 * @method dequeueCell
 * @return A value converted from C/C++ "cocos2d::extension::TableViewCell*"
 */
dequeueCell : function () {},

/**
 * @method TableView
 * @constructor
 */
TableView : function () {},

};

/**
 * @class EditBox
 */
cc.EditBox = {

/**
 * @method setAnchorPoint
 * @param {cocos2d::Point}
 */
setAnchorPoint : function () {},

/**
 * @method getText
 * @return A value converted from C/C++ "const char*"
 */
getText : function () {},

/**
 * @method setPlaceholderFontName
 * @param {const char*}
 */
setPlaceholderFontName : function () {},

/**
 * @method getPlaceHolder
 * @return A value converted from C/C++ "const char*"
 */
getPlaceHolder : function () {},

/**
 * @method setFontName
 * @param {const char*}
 */
setFontName : function () {},

/**
 * @method setPlaceholderFontSize
 * @param {int}
 */
setPlaceholderFontSize : function () {},

/**
 * @method setInputMode
 * @param {cocos2d::extension::EditBox::InputMode}
 */
setInputMode : function () {},

/**
 * @method setPlaceholderFontColor
 * @param {cocos2d::Color3B}
 */
setPlaceholderFontColor : function () {},

/**
 * @method setFontColor
 * @param {cocos2d::Color3B}
 */
setFontColor : function () {},

/**
 * @method setPlaceholderFont
 * @param {const char*}
 * @param {int}
 */
setPlaceholderFont : function () {},

/**
 * @method setFontSize
 * @param {int}
 */
setFontSize : function () {},

/**
 * @method initWithSizeAndBackgroundSprite
 * @return A value converted from C/C++ "bool"
 * @param {cocos2d::Size}
 * @param {cocos2d::extension::Scale9Sprite*}
 */
initWithSizeAndBackgroundSprite : function () {},

/**
 * @method setPlaceHolder
 * @param {const char*}
 */
setPlaceHolder : function () {},

/**
 * @method setPosition
 * @param {cocos2d::Point}
 */
setPosition : function () {},

/**
 * @method setReturnType
 * @param {cocos2d::extension::EditBox::KeyboardReturnType}
 */
setReturnType : function () {},

/**
 * @method setInputFlag
 * @param {cocos2d::extension::EditBox::InputFlag}
 */
setInputFlag : function () {},

/**
 * @method getMaxLength
 * @return A value converted from C/C++ "int"
 */
getMaxLength : function () {},

/**
 * @method setText
 * @param {const char*}
 */
setText : function () {},

/**
 * @method setMaxLength
 * @param {int}
 */
setMaxLength : function () {},

/**
 * @method setContentSize
 * @param {cocos2d::Size}
 */
setContentSize : function () {},

/**
 * @method setFont
 * @param {const char*}
 * @param {int}
 */
setFont : function () {},

/**
 * @method setVisible
 * @param {bool}
 */
setVisible : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::extension::EditBox*"
 * @param {cocos2d::Size}
 * @param {cocos2d::extension::Scale9Sprite*}
 * @param {cocos2d::extension::Scale9Sprite*}
 * @param {cocos2d::extension::Scale9Sprite*}
 */
create : function () {},

/**
 * @method EditBox
 * @constructor
 */
EditBox : function () {},

};
