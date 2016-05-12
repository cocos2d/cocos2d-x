/**
 * @module cocos2dx_ui
 */
var ccui = ccui || {};

/**
 * @class LayoutParameter
 */
ccui.LayoutParameter = {

/**
 * @method clone
 * @return {ccui.LayoutParameter}
 */
clone : function (
)
{
    return ccui.LayoutParameter;
},

/**
 * @method getLayoutType
 * @return {ccui.LayoutParameter::Type}
 */
getLayoutType : function (
)
{
    return 0;
},

/**
 * @method createCloneInstance
 * @return {ccui.LayoutParameter}
 */
createCloneInstance : function (
)
{
    return ccui.LayoutParameter;
},

/**
 * @method copyProperties
 * @param {ccui.LayoutParameter} arg0
 */
copyProperties : function (
layoutparameter 
)
{
},

/**
 * @method create
 * @return {ccui.LayoutParameter}
 */
create : function (
)
{
    return ccui.LayoutParameter;
},

/**
 * @method LayoutParameter
 * @constructor
 */
LayoutParameter : function (
)
{
},

};

/**
 * @class LinearLayoutParameter
 */
ccui.LinearLayoutParameter = {

/**
 * @method setGravity
 * @param {ccui.LinearLayoutParameter::LinearGravity} arg0
 */
setGravity : function (
lineargravity 
)
{
},

/**
 * @method getGravity
 * @return {ccui.LinearLayoutParameter::LinearGravity}
 */
getGravity : function (
)
{
    return 0;
},

/**
 * @method create
 * @return {ccui.LinearLayoutParameter}
 */
create : function (
)
{
    return ccui.LinearLayoutParameter;
},

/**
 * @method LinearLayoutParameter
 * @constructor
 */
LinearLayoutParameter : function (
)
{
},

};

/**
 * @class RelativeLayoutParameter
 */
ccui.RelativeLayoutParameter = {

/**
 * @method setAlign
 * @param {ccui.RelativeLayoutParameter::RelativeAlign} arg0
 */
setAlign : function (
relativealign 
)
{
},

/**
 * @method setRelativeToWidgetName
 * @param {String} arg0
 */
setRelativeToWidgetName : function (
str 
)
{
},

/**
 * @method getRelativeName
 * @return {String}
 */
getRelativeName : function (
)
{
    return ;
},

/**
 * @method getRelativeToWidgetName
 * @return {String}
 */
getRelativeToWidgetName : function (
)
{
    return ;
},

/**
 * @method setRelativeName
 * @param {String} arg0
 */
setRelativeName : function (
str 
)
{
},

/**
 * @method getAlign
 * @return {ccui.RelativeLayoutParameter::RelativeAlign}
 */
getAlign : function (
)
{
    return 0;
},

/**
 * @method create
 * @return {ccui.RelativeLayoutParameter}
 */
create : function (
)
{
    return ccui.RelativeLayoutParameter;
},

/**
 * @method RelativeLayoutParameter
 * @constructor
 */
RelativeLayoutParameter : function (
)
{
},

};

/**
 * @class Widget
 */
ccui.Widget = {

/**
 * @method setLayoutComponentEnabled
 * @param {bool} arg0
 */
setLayoutComponentEnabled : function (
bool 
)
{
},

/**
 * @method setSizePercent
 * @param {vec2_object} arg0
 */
setSizePercent : function (
vec2 
)
{
},

/**
 * @method getCustomSize
 * @return {size_object}
 */
getCustomSize : function (
)
{
    return cc.Size;
},

/**
 * @method getLeftBoundary
 * @return {float}
 */
getLeftBoundary : function (
)
{
    return 0;
},

/**
 * @method setFlippedX
 * @param {bool} arg0
 */
setFlippedX : function (
bool 
)
{
},

/**
 * @method setCallbackName
 * @param {String} arg0
 */
setCallbackName : function (
str 
)
{
},

/**
 * @method getVirtualRenderer
 * @return {cc.Node}
 */
getVirtualRenderer : function (
)
{
    return cc.Node;
},

/**
 * @method setPropagateTouchEvents
 * @param {bool} arg0
 */
setPropagateTouchEvents : function (
bool 
)
{
},

/**
 * @method isUnifySizeEnabled
 * @return {bool}
 */
isUnifySizeEnabled : function (
)
{
    return false;
},

/**
 * @method getSizePercent
 * @return {vec2_object}
 */
getSizePercent : function (
)
{
    return cc.Vec2;
},

/**
 * @method setPositionPercent
 * @param {vec2_object} arg0
 */
setPositionPercent : function (
vec2 
)
{
},

/**
 * @method setSwallowTouches
 * @param {bool} arg0
 */
setSwallowTouches : function (
bool 
)
{
},

/**
 * @method getLayoutSize
 * @return {size_object}
 */
getLayoutSize : function (
)
{
    return cc.Size;
},

/**
 * @method setHighlighted
 * @param {bool} arg0
 */
setHighlighted : function (
bool 
)
{
},

/**
 * @method setPositionType
 * @param {ccui.Widget::PositionType} arg0
 */
setPositionType : function (
positiontype 
)
{
},

/**
 * @method isIgnoreContentAdaptWithSize
 * @return {bool}
 */
isIgnoreContentAdaptWithSize : function (
)
{
    return false;
},

/**
 * @method getVirtualRendererSize
 * @return {size_object}
 */
getVirtualRendererSize : function (
)
{
    return cc.Size;
},

/**
 * @method isHighlighted
 * @return {bool}
 */
isHighlighted : function (
)
{
    return false;
},

/**
 * @method getLayoutParameter
 * @return {ccui.LayoutParameter}
 */
getLayoutParameter : function (
)
{
    return ccui.LayoutParameter;
},

/**
 * @method addCCSEventListener
 * @param {function} arg0
 */
addCCSEventListener : function (
func 
)
{
},

/**
 * @method getPositionType
 * @return {ccui.Widget::PositionType}
 */
getPositionType : function (
)
{
    return 0;
},

/**
 * @method getTopBoundary
 * @return {float}
 */
getTopBoundary : function (
)
{
    return 0;
},

/**
 * @method ignoreContentAdaptWithSize
 * @param {bool} arg0
 */
ignoreContentAdaptWithSize : function (
bool 
)
{
},

/**
 * @method findNextFocusedWidget
 * @param {ccui.Widget::FocusDirection} arg0
 * @param {ccui.Widget} arg1
 * @return {ccui.Widget}
 */
findNextFocusedWidget : function (
focusdirection, 
widget 
)
{
    return ccui.Widget;
},

/**
 * @method isEnabled
 * @return {bool}
 */
isEnabled : function (
)
{
    return false;
},

/**
 * @method isFocused
 * @return {bool}
 */
isFocused : function (
)
{
    return false;
},

/**
 * @method getTouchBeganPosition
 * @return {vec2_object}
 */
getTouchBeganPosition : function (
)
{
    return cc.Vec2;
},

/**
 * @method isTouchEnabled
 * @return {bool}
 */
isTouchEnabled : function (
)
{
    return false;
},

/**
 * @method getCallbackName
 * @return {String}
 */
getCallbackName : function (
)
{
    return ;
},

/**
 * @method getActionTag
 * @return {int}
 */
getActionTag : function (
)
{
    return 0;
},

/**
 * @method getWorldPosition
 * @return {vec2_object}
 */
getWorldPosition : function (
)
{
    return cc.Vec2;
},

/**
 * @method isFocusEnabled
 * @return {bool}
 */
isFocusEnabled : function (
)
{
    return false;
},

/**
 * @method setFocused
 * @param {bool} arg0
 */
setFocused : function (
bool 
)
{
},

/**
 * @method setActionTag
 * @param {int} arg0
 */
setActionTag : function (
int 
)
{
},

/**
 * @method setTouchEnabled
 * @param {bool} arg0
 */
setTouchEnabled : function (
bool 
)
{
},

/**
 * @method setFlippedY
 * @param {bool} arg0
 */
setFlippedY : function (
bool 
)
{
},

/**
 * @method init
 * @return {bool}
 */
init : function (
)
{
    return false;
},

/**
 * @method setEnabled
 * @param {bool} arg0
 */
setEnabled : function (
bool 
)
{
},

/**
 * @method getRightBoundary
 * @return {float}
 */
getRightBoundary : function (
)
{
    return 0;
},

/**
 * @method setBrightStyle
 * @param {ccui.Widget::BrightStyle} arg0
 */
setBrightStyle : function (
brightstyle 
)
{
},

/**
 * @method setLayoutParameter
 * @param {ccui.LayoutParameter} arg0
 */
setLayoutParameter : function (
layoutparameter 
)
{
},

/**
 * @method clone
 * @return {ccui.Widget}
 */
clone : function (
)
{
    return ccui.Widget;
},

/**
 * @method setFocusEnabled
 * @param {bool} arg0
 */
setFocusEnabled : function (
bool 
)
{
},

/**
 * @method getBottomBoundary
 * @return {float}
 */
getBottomBoundary : function (
)
{
    return 0;
},

/**
 * @method isBright
 * @return {bool}
 */
isBright : function (
)
{
    return false;
},

/**
 * @method dispatchFocusEvent
 * @param {ccui.Widget} arg0
 * @param {ccui.Widget} arg1
 */
dispatchFocusEvent : function (
widget, 
widget 
)
{
},

/**
 * @method setUnifySizeEnabled
 * @param {bool} arg0
 */
setUnifySizeEnabled : function (
bool 
)
{
},

/**
 * @method isPropagateTouchEvents
 * @return {bool}
 */
isPropagateTouchEvents : function (
)
{
    return false;
},

/**
 * @method hitTest
 * @param {vec2_object} arg0
 * @param {cc.Camera} arg1
 * @param {vec3_object} arg2
 * @return {bool}
 */
hitTest : function (
vec2, 
camera, 
vec3 
)
{
    return false;
},

/**
 * @method isLayoutComponentEnabled
 * @return {bool}
 */
isLayoutComponentEnabled : function (
)
{
    return false;
},

/**
 * @method requestFocus
 */
requestFocus : function (
)
{
},

/**
 * @method updateSizeAndPosition
* @param {size_object} size
*/
updateSizeAndPosition : function(
size 
)
{
},

/**
 * @method onFocusChange
 * @param {ccui.Widget} arg0
 * @param {ccui.Widget} arg1
 */
onFocusChange : function (
widget, 
widget 
)
{
},

/**
 * @method getTouchMovePosition
 * @return {vec2_object}
 */
getTouchMovePosition : function (
)
{
    return cc.Vec2;
},

/**
 * @method getSizeType
 * @return {ccui.Widget::SizeType}
 */
getSizeType : function (
)
{
    return 0;
},

/**
 * @method getCallbackType
 * @return {String}
 */
getCallbackType : function (
)
{
    return ;
},

/**
 * @method addTouchEventListener
 * @param {function} arg0
 */
addTouchEventListener : function (
func 
)
{
},

/**
 * @method getTouchEndPosition
 * @return {vec2_object}
 */
getTouchEndPosition : function (
)
{
    return cc.Vec2;
},

/**
 * @method getPositionPercent
 * @return {vec2_object}
 */
getPositionPercent : function (
)
{
    return cc.Vec2;
},

/**
 * @method propagateTouchEvent
 * @param {ccui.Widget::TouchEventType} arg0
 * @param {ccui.Widget} arg1
 * @param {cc.Touch} arg2
 */
propagateTouchEvent : function (
toucheventtype, 
widget, 
touch 
)
{
},

/**
 * @method addClickEventListener
 * @param {function} arg0
 */
addClickEventListener : function (
func 
)
{
},

/**
 * @method isFlippedX
 * @return {bool}
 */
isFlippedX : function (
)
{
    return false;
},

/**
 * @method isFlippedY
 * @return {bool}
 */
isFlippedY : function (
)
{
    return false;
},

/**
 * @method isClippingParentContainsPoint
 * @param {vec2_object} arg0
 * @return {bool}
 */
isClippingParentContainsPoint : function (
vec2 
)
{
    return false;
},

/**
 * @method setSizeType
 * @param {ccui.Widget::SizeType} arg0
 */
setSizeType : function (
sizetype 
)
{
},

/**
 * @method interceptTouchEvent
 * @param {ccui.Widget::TouchEventType} arg0
 * @param {ccui.Widget} arg1
 * @param {cc.Touch} arg2
 */
interceptTouchEvent : function (
toucheventtype, 
widget, 
touch 
)
{
},

/**
 * @method setBright
 * @param {bool} arg0
 */
setBright : function (
bool 
)
{
},

/**
 * @method setCallbackType
 * @param {String} arg0
 */
setCallbackType : function (
str 
)
{
},

/**
 * @method isSwallowTouches
 * @return {bool}
 */
isSwallowTouches : function (
)
{
    return false;
},

/**
 * @method enableDpadNavigation
 * @param {bool} arg0
 */
enableDpadNavigation : function (
bool 
)
{
},

/**
 * @method getCurrentFocusedWidget
 * @return {ccui.Widget}
 */
getCurrentFocusedWidget : function (
)
{
    return ccui.Widget;
},

/**
 * @method create
 * @return {ccui.Widget}
 */
create : function (
)
{
    return ccui.Widget;
},

/**
 * @method Widget
 * @constructor
 */
Widget : function (
)
{
},

};

/**
 * @class Layout
 */
ccui.Layout = {

/**
 * @method setBackGroundColorVector
 * @param {vec2_object} arg0
 */
setBackGroundColorVector : function (
vec2 
)
{
},

/**
 * @method setClippingType
 * @param {ccui.Layout::ClippingType} arg0
 */
setClippingType : function (
clippingtype 
)
{
},

/**
 * @method setBackGroundColorType
 * @param {ccui.Layout::BackGroundColorType} arg0
 */
setBackGroundColorType : function (
backgroundcolortype 
)
{
},

/**
 * @method setLoopFocus
 * @param {bool} arg0
 */
setLoopFocus : function (
bool 
)
{
},

/**
 * @method setBackGroundImageColor
 * @param {color3b_object} arg0
 */
setBackGroundImageColor : function (
color3b 
)
{
},

/**
 * @method getBackGroundColorVector
 * @return {vec2_object}
 */
getBackGroundColorVector : function (
)
{
    return cc.Vec2;
},

/**
 * @method getClippingType
 * @return {ccui.Layout::ClippingType}
 */
getClippingType : function (
)
{
    return 0;
},

/**
 * @method getRenderFile
 * @return {cc.ResourceData}
 */
getRenderFile : function (
)
{
    return cc.ResourceData;
},

/**
 * @method isLoopFocus
 * @return {bool}
 */
isLoopFocus : function (
)
{
    return false;
},

/**
 * @method removeBackGroundImage
 */
removeBackGroundImage : function (
)
{
},

/**
 * @method getBackGroundColorOpacity
 * @return {unsigned char}
 */
getBackGroundColorOpacity : function (
)
{
    return 0;
},

/**
 * @method isClippingEnabled
 * @return {bool}
 */
isClippingEnabled : function (
)
{
    return false;
},

/**
 * @method setBackGroundImageOpacity
 * @param {unsigned char} arg0
 */
setBackGroundImageOpacity : function (
char 
)
{
},

/**
 * @method setBackGroundImage
 * @param {String} arg0
 * @param {ccui.Widget::TextureResType} arg1
 */
setBackGroundImage : function (
str, 
texturerestype 
)
{
},

/**
 * @method setBackGroundColor
* @param {color3b_object|color3b_object} color3b
* @param {color3b_object} color3b
*/
setBackGroundColor : function(
color3b,
color3b 
)
{
},

/**
 * @method requestDoLayout
 */
requestDoLayout : function (
)
{
},

/**
 * @method getBackGroundImageCapInsets
 * @return {rect_object}
 */
getBackGroundImageCapInsets : function (
)
{
    return cc.Rect;
},

/**
 * @method getBackGroundColor
 * @return {color3b_object}
 */
getBackGroundColor : function (
)
{
    return cc.Color3B;
},

/**
 * @method setClippingEnabled
 * @param {bool} arg0
 */
setClippingEnabled : function (
bool 
)
{
},

/**
 * @method getBackGroundImageColor
 * @return {color3b_object}
 */
getBackGroundImageColor : function (
)
{
    return cc.Color3B;
},

/**
 * @method isBackGroundImageScale9Enabled
 * @return {bool}
 */
isBackGroundImageScale9Enabled : function (
)
{
    return false;
},

/**
 * @method getBackGroundColorType
 * @return {ccui.Layout::BackGroundColorType}
 */
getBackGroundColorType : function (
)
{
    return 0;
},

/**
 * @method getBackGroundEndColor
 * @return {color3b_object}
 */
getBackGroundEndColor : function (
)
{
    return cc.Color3B;
},

/**
 * @method setBackGroundColorOpacity
 * @param {unsigned char} arg0
 */
setBackGroundColorOpacity : function (
char 
)
{
},

/**
 * @method getBackGroundImageOpacity
 * @return {unsigned char}
 */
getBackGroundImageOpacity : function (
)
{
    return 0;
},

/**
 * @method isPassFocusToChild
 * @return {bool}
 */
isPassFocusToChild : function (
)
{
    return false;
},

/**
 * @method setBackGroundImageCapInsets
 * @param {rect_object} arg0
 */
setBackGroundImageCapInsets : function (
rect 
)
{
},

/**
 * @method getBackGroundImageTextureSize
 * @return {size_object}
 */
getBackGroundImageTextureSize : function (
)
{
    return cc.Size;
},

/**
 * @method forceDoLayout
 */
forceDoLayout : function (
)
{
},

/**
 * @method getLayoutType
 * @return {ccui.Layout::Type}
 */
getLayoutType : function (
)
{
    return 0;
},

/**
 * @method setPassFocusToChild
 * @param {bool} arg0
 */
setPassFocusToChild : function (
bool 
)
{
},

/**
 * @method getBackGroundStartColor
 * @return {color3b_object}
 */
getBackGroundStartColor : function (
)
{
    return cc.Color3B;
},

/**
 * @method setBackGroundImageScale9Enabled
 * @param {bool} arg0
 */
setBackGroundImageScale9Enabled : function (
bool 
)
{
},

/**
 * @method setLayoutType
 * @param {ccui.Layout::Type} arg0
 */
setLayoutType : function (
type 
)
{
},

/**
 * @method create
 * @return {ccui.Layout}
 */
create : function (
)
{
    return ccui.Layout;
},

/**
 * @method Layout
 * @constructor
 */
Layout : function (
)
{
},

};

/**
 * @class Button
 */
ccui.Button = {

/**
 * @method getNormalTextureSize
 * @return {size_object}
 */
getNormalTextureSize : function (
)
{
    return cc.Size;
},

/**
 * @method getTitleText
 * @return {String}
 */
getTitleText : function (
)
{
    return ;
},

/**
 * @method setTitleFontSize
 * @param {float} arg0
 */
setTitleFontSize : function (
float 
)
{
},

/**
 * @method resetPressedRender
 */
resetPressedRender : function (
)
{
},

/**
 * @method setScale9Enabled
 * @param {bool} arg0
 */
setScale9Enabled : function (
bool 
)
{
},

/**
 * @method resetDisabledRender
 */
resetDisabledRender : function (
)
{
},

/**
 * @method getTitleRenderer
 * @return {cc.Label}
 */
getTitleRenderer : function (
)
{
    return cc.Label;
},

/**
 * @method getRendererClicked
 * @return {ccui.Scale9Sprite}
 */
getRendererClicked : function (
)
{
    return ccui.Scale9Sprite;
},

/**
 * @method getDisabledFile
 * @return {cc.ResourceData}
 */
getDisabledFile : function (
)
{
    return cc.ResourceData;
},

/**
 * @method getZoomScale
 * @return {float}
 */
getZoomScale : function (
)
{
    return 0;
},

/**
 * @method getCapInsetsDisabledRenderer
 * @return {rect_object}
 */
getCapInsetsDisabledRenderer : function (
)
{
    return cc.Rect;
},

/**
 * @method setTitleColor
 * @param {color3b_object} arg0
 */
setTitleColor : function (
color3b 
)
{
},

/**
 * @method getNormalFile
 * @return {cc.ResourceData}
 */
getNormalFile : function (
)
{
    return cc.ResourceData;
},

/**
 * @method resetNormalRender
 */
resetNormalRender : function (
)
{
},

/**
 * @method getRendererDisabled
 * @return {ccui.Scale9Sprite}
 */
getRendererDisabled : function (
)
{
    return ccui.Scale9Sprite;
},

/**
 * @method setCapInsetsDisabledRenderer
 * @param {rect_object} arg0
 */
setCapInsetsDisabledRenderer : function (
rect 
)
{
},

/**
 * @method setCapInsets
 * @param {rect_object} arg0
 */
setCapInsets : function (
rect 
)
{
},

/**
 * @method loadTextureDisabled
 * @param {String} arg0
 * @param {ccui.Widget::TextureResType} arg1
 */
loadTextureDisabled : function (
str, 
texturerestype 
)
{
},

/**
 * @method init
 * @param {String} arg0
 * @param {String} arg1
 * @param {String} arg2
 * @param {ccui.Widget::TextureResType} arg3
 * @return {bool}
 */
init : function (
str, 
str, 
str, 
texturerestype 
)
{
    return false;
},

/**
 * @method setTitleText
 * @param {String} arg0
 */
setTitleText : function (
str 
)
{
},

/**
 * @method setCapInsetsNormalRenderer
 * @param {rect_object} arg0
 */
setCapInsetsNormalRenderer : function (
rect 
)
{
},

/**
 * @method loadTexturePressed
 * @param {String} arg0
 * @param {ccui.Widget::TextureResType} arg1
 */
loadTexturePressed : function (
str, 
texturerestype 
)
{
},

/**
 * @method setTitleFontName
 * @param {String} arg0
 */
setTitleFontName : function (
str 
)
{
},

/**
 * @method getCapInsetsNormalRenderer
 * @return {rect_object}
 */
getCapInsetsNormalRenderer : function (
)
{
    return cc.Rect;
},

/**
 * @method setTitleAlignment
* @param {cc.TextHAlignment|cc.TextHAlignment} texthalignment
* @param {cc.TextVAlignment} textvalignment
*/
setTitleAlignment : function(
texthalignment,
textvalignment 
)
{
},

/**
 * @method getCapInsetsPressedRenderer
 * @return {rect_object}
 */
getCapInsetsPressedRenderer : function (
)
{
    return cc.Rect;
},

/**
 * @method loadTextures
 * @param {String} arg0
 * @param {String} arg1
 * @param {String} arg2
 * @param {ccui.Widget::TextureResType} arg3
 */
loadTextures : function (
str, 
str, 
str, 
texturerestype 
)
{
},

/**
 * @method isScale9Enabled
 * @return {bool}
 */
isScale9Enabled : function (
)
{
    return false;
},

/**
 * @method loadTextureNormal
 * @param {String} arg0
 * @param {ccui.Widget::TextureResType} arg1
 */
loadTextureNormal : function (
str, 
texturerestype 
)
{
},

/**
 * @method setCapInsetsPressedRenderer
 * @param {rect_object} arg0
 */
setCapInsetsPressedRenderer : function (
rect 
)
{
},

/**
 * @method getPressedFile
 * @return {cc.ResourceData}
 */
getPressedFile : function (
)
{
    return cc.ResourceData;
},

/**
 * @method getTitleFontSize
 * @return {float}
 */
getTitleFontSize : function (
)
{
    return 0;
},

/**
 * @method getRendererNormal
 * @return {ccui.Scale9Sprite}
 */
getRendererNormal : function (
)
{
    return ccui.Scale9Sprite;
},

/**
 * @method getTitleFontName
 * @return {String}
 */
getTitleFontName : function (
)
{
    return ;
},

/**
 * @method getTitleColor
 * @return {color3b_object}
 */
getTitleColor : function (
)
{
    return cc.Color3B;
},

/**
 * @method setPressedActionEnabled
 * @param {bool} arg0
 */
setPressedActionEnabled : function (
bool 
)
{
},

/**
 * @method setZoomScale
 * @param {float} arg0
 */
setZoomScale : function (
float 
)
{
},

/**
 * @method create
* @param {String} str
* @param {String} str
* @param {String} str
* @param {ccui.Widget::TextureResType} texturerestype
* @return {ccui.Button|ccui.Button}
*/
create : function(
str,
str,
str,
texturerestype 
)
{
    return ccui.Button;
},

/**
 * @method Button
 * @constructor
 */
Button : function (
)
{
},

};

/**
 * @class AbstractCheckButton
 */
ccui.AbstractCheckButton = {

/**
 * @method getCrossDisabledFile
 * @return {cc.ResourceData}
 */
getCrossDisabledFile : function (
)
{
    return cc.ResourceData;
},

/**
 * @method getBackDisabledFile
 * @return {cc.ResourceData}
 */
getBackDisabledFile : function (
)
{
    return cc.ResourceData;
},

/**
 * @method loadTextureBackGroundSelected
 * @param {String} arg0
 * @param {ccui.Widget::TextureResType} arg1
 */
loadTextureBackGroundSelected : function (
str, 
texturerestype 
)
{
},

/**
 * @method loadTextureBackGroundDisabled
 * @param {String} arg0
 * @param {ccui.Widget::TextureResType} arg1
 */
loadTextureBackGroundDisabled : function (
str, 
texturerestype 
)
{
},

/**
 * @method getCrossNormalFile
 * @return {cc.ResourceData}
 */
getCrossNormalFile : function (
)
{
    return cc.ResourceData;
},

/**
 * @method setSelected
 * @param {bool} arg0
 */
setSelected : function (
bool 
)
{
},

/**
 * @method getBackPressedFile
 * @return {cc.ResourceData}
 */
getBackPressedFile : function (
)
{
    return cc.ResourceData;
},

/**
 * @method getRendererFrontCrossDisabled
 * @return {cc.Sprite}
 */
getRendererFrontCrossDisabled : function (
)
{
    return cc.Sprite;
},

/**
 * @method getRendererBackground
 * @return {cc.Sprite}
 */
getRendererBackground : function (
)
{
    return cc.Sprite;
},

/**
 * @method loadTextureFrontCross
 * @param {String} arg0
 * @param {ccui.Widget::TextureResType} arg1
 */
loadTextureFrontCross : function (
str, 
texturerestype 
)
{
},

/**
 * @method getRendererBackgroundDisabled
 * @return {cc.Sprite}
 */
getRendererBackgroundDisabled : function (
)
{
    return cc.Sprite;
},

/**
 * @method isSelected
 * @return {bool}
 */
isSelected : function (
)
{
    return false;
},

/**
 * @method init
 * @param {String} arg0
 * @param {String} arg1
 * @param {String} arg2
 * @param {String} arg3
 * @param {String} arg4
 * @param {ccui.Widget::TextureResType} arg5
 * @return {bool}
 */
init : function (
str, 
str, 
str, 
str, 
str, 
texturerestype 
)
{
    return false;
},

/**
 * @method getBackNormalFile
 * @return {cc.ResourceData}
 */
getBackNormalFile : function (
)
{
    return cc.ResourceData;
},

/**
 * @method loadTextures
 * @param {String} arg0
 * @param {String} arg1
 * @param {String} arg2
 * @param {String} arg3
 * @param {String} arg4
 * @param {ccui.Widget::TextureResType} arg5
 */
loadTextures : function (
str, 
str, 
str, 
str, 
str, 
texturerestype 
)
{
},

/**
 * @method getZoomScale
 * @return {float}
 */
getZoomScale : function (
)
{
    return 0;
},

/**
 * @method getRendererFrontCross
 * @return {cc.Sprite}
 */
getRendererFrontCross : function (
)
{
    return cc.Sprite;
},

/**
 * @method getRendererBackgroundSelected
 * @return {cc.Sprite}
 */
getRendererBackgroundSelected : function (
)
{
    return cc.Sprite;
},

/**
 * @method loadTextureBackGround
 * @param {String} arg0
 * @param {ccui.Widget::TextureResType} arg1
 */
loadTextureBackGround : function (
str, 
texturerestype 
)
{
},

/**
 * @method setZoomScale
 * @param {float} arg0
 */
setZoomScale : function (
float 
)
{
},

/**
 * @method loadTextureFrontCrossDisabled
 * @param {String} arg0
 * @param {ccui.Widget::TextureResType} arg1
 */
loadTextureFrontCrossDisabled : function (
str, 
texturerestype 
)
{
},

};

/**
 * @class CheckBox
 */
ccui.CheckBox = {

/**
 * @method addEventListener
 * @param {function} arg0
 */
addEventListener : function (
func 
)
{
},

/**
 * @method create
* @param {String|String} str
* @param {String|String} str
* @param {String|ccui.Widget::TextureResType} str
* @param {String} str
* @param {String} str
* @param {ccui.Widget::TextureResType} texturerestype
* @return {ccui.CheckBox|ccui.CheckBox|ccui.CheckBox}
*/
create : function(
str,
str,
str,
str,
str,
texturerestype 
)
{
    return ccui.CheckBox;
},

/**
 * @method CheckBox
 * @constructor
 */
CheckBox : function (
)
{
},

};

/**
 * @class RadioButton
 */
ccui.RadioButton = {

/**
 * @method addEventListener
 * @param {function} arg0
 */
addEventListener : function (
func 
)
{
},

/**
 * @method create
* @param {String|String} str
* @param {String|String} str
* @param {String|ccui.Widget::TextureResType} str
* @param {String} str
* @param {String} str
* @param {ccui.Widget::TextureResType} texturerestype
* @return {ccui.RadioButton|ccui.RadioButton|ccui.RadioButton}
*/
create : function(
str,
str,
str,
str,
str,
texturerestype 
)
{
    return ccui.RadioButton;
},

/**
 * @method RadioButton
 * @constructor
 */
RadioButton : function (
)
{
},

};

/**
 * @class RadioButtonGroup
 */
ccui.RadioButtonGroup = {

/**
 * @method removeRadioButton
 * @param {ccui.RadioButton} arg0
 */
removeRadioButton : function (
radiobutton 
)
{
},

/**
 * @method isAllowedNoSelection
 * @return {bool}
 */
isAllowedNoSelection : function (
)
{
    return false;
},

/**
 * @method getSelectedButtonIndex
 * @return {int}
 */
getSelectedButtonIndex : function (
)
{
    return 0;
},

/**
 * @method setAllowedNoSelection
 * @param {bool} arg0
 */
setAllowedNoSelection : function (
bool 
)
{
},

/**
 * @method setSelectedButtonWithoutEvent
* @param {ccui.RadioButton|int} radiobutton
*/
setSelectedButtonWithoutEvent : function(
int 
)
{
},

/**
 * @method addEventListener
 * @param {function} arg0
 */
addEventListener : function (
func 
)
{
},

/**
 * @method removeAllRadioButtons
 */
removeAllRadioButtons : function (
)
{
},

/**
 * @method getRadioButtonByIndex
 * @param {int} arg0
 * @return {ccui.RadioButton}
 */
getRadioButtonByIndex : function (
int 
)
{
    return ccui.RadioButton;
},

/**
 * @method getNumberOfRadioButtons
 * @return {long}
 */
getNumberOfRadioButtons : function (
)
{
    return 0;
},

/**
 * @method addRadioButton
 * @param {ccui.RadioButton} arg0
 */
addRadioButton : function (
radiobutton 
)
{
},

/**
 * @method setSelectedButton
* @param {ccui.RadioButton|int} radiobutton
*/
setSelectedButton : function(
int 
)
{
},

/**
 * @method create
 * @return {ccui.RadioButtonGroup}
 */
create : function (
)
{
    return ccui.RadioButtonGroup;
},

/**
 * @method RadioButtonGroup
 * @constructor
 */
RadioButtonGroup : function (
)
{
},

};

/**
 * @class ImageView
 */
ccui.ImageView = {

/**
 * @method loadTexture
 * @param {String} arg0
 * @param {ccui.Widget::TextureResType} arg1
 */
loadTexture : function (
str, 
texturerestype 
)
{
},

/**
 * @method init
 * @param {String} arg0
 * @param {ccui.Widget::TextureResType} arg1
 * @return {bool}
 */
init : function (
str, 
texturerestype 
)
{
    return false;
},

/**
 * @method setScale9Enabled
 * @param {bool} arg0
 */
setScale9Enabled : function (
bool 
)
{
},

/**
 * @method setTextureRect
 * @param {rect_object} arg0
 */
setTextureRect : function (
rect 
)
{
},

/**
 * @method setCapInsets
 * @param {rect_object} arg0
 */
setCapInsets : function (
rect 
)
{
},

/**
 * @method getRenderFile
 * @return {cc.ResourceData}
 */
getRenderFile : function (
)
{
    return cc.ResourceData;
},

/**
 * @method getCapInsets
 * @return {rect_object}
 */
getCapInsets : function (
)
{
    return cc.Rect;
},

/**
 * @method isScale9Enabled
 * @return {bool}
 */
isScale9Enabled : function (
)
{
    return false;
},

/**
 * @method create
* @param {String} str
* @param {ccui.Widget::TextureResType} texturerestype
* @return {ccui.ImageView|ccui.ImageView}
*/
create : function(
str,
texturerestype 
)
{
    return ccui.ImageView;
},

/**
 * @method ImageView
 * @constructor
 */
ImageView : function (
)
{
},

};

/**
 * @class Text
 */
ccui.Text = {

/**
 * @method enableShadow
 */
enableShadow : function (
)
{
},

/**
 * @method getFontSize
 * @return {float}
 */
getFontSize : function (
)
{
    return 0;
},

/**
 * @method getString
 * @return {String}
 */
getString : function (
)
{
    return ;
},

/**
 * @method disableEffect
* @param {cc.LabelEffect} labeleffect
*/
disableEffect : function(
labeleffect 
)
{
},

/**
 * @method getLabelEffectType
 * @return {cc.LabelEffect}
 */
getLabelEffectType : function (
)
{
    return 0;
},

/**
 * @method getTextColor
 * @return {color4b_object}
 */
getTextColor : function (
)
{
    return cc.Color4B;
},

/**
 * @method setTextVerticalAlignment
 * @param {cc.TextVAlignment} arg0
 */
setTextVerticalAlignment : function (
textvalignment 
)
{
},

/**
 * @method setFontName
 * @param {String} arg0
 */
setFontName : function (
str 
)
{
},

/**
 * @method setTouchScaleChangeEnabled
 * @param {bool} arg0
 */
setTouchScaleChangeEnabled : function (
bool 
)
{
},

/**
 * @method getShadowOffset
 * @return {size_object}
 */
getShadowOffset : function (
)
{
    return cc.Size;
},

/**
 * @method setString
 * @param {String} arg0
 */
setString : function (
str 
)
{
},

/**
 * @method getOutlineSize
 * @return {int}
 */
getOutlineSize : function (
)
{
    return 0;
},

/**
 * @method init
 * @param {String} arg0
 * @param {String} arg1
 * @param {float} arg2
 * @return {bool}
 */
init : function (
str, 
str, 
float 
)
{
    return false;
},

/**
 * @method getShadowBlurRadius
 * @return {float}
 */
getShadowBlurRadius : function (
)
{
    return 0;
},

/**
 * @method isTouchScaleChangeEnabled
 * @return {bool}
 */
isTouchScaleChangeEnabled : function (
)
{
    return false;
},

/**
 * @method getFontName
 * @return {String}
 */
getFontName : function (
)
{
    return ;
},

/**
 * @method setTextAreaSize
 * @param {size_object} arg0
 */
setTextAreaSize : function (
size 
)
{
},

/**
 * @method getStringLength
 * @return {long}
 */
getStringLength : function (
)
{
    return 0;
},

/**
 * @method getAutoRenderSize
 * @return {size_object}
 */
getAutoRenderSize : function (
)
{
    return cc.Size;
},

/**
 * @method enableOutline
 * @param {color4b_object} arg0
 * @param {int} arg1
 */
enableOutline : function (
color4b, 
int 
)
{
},

/**
 * @method getEffectColor
 * @return {color4b_object}
 */
getEffectColor : function (
)
{
    return cc.Color4B;
},

/**
 * @method getType
 * @return {ccui.Text::Type}
 */
getType : function (
)
{
    return 0;
},

/**
 * @method getTextHorizontalAlignment
 * @return {cc.TextHAlignment}
 */
getTextHorizontalAlignment : function (
)
{
    return 0;
},

/**
 * @method isShadowEnabled
 * @return {bool}
 */
isShadowEnabled : function (
)
{
    return false;
},

/**
 * @method setFontSize
 * @param {float} arg0
 */
setFontSize : function (
float 
)
{
},

/**
 * @method getShadowColor
 * @return {color4b_object}
 */
getShadowColor : function (
)
{
    return cc.Color4B;
},

/**
 * @method setTextColor
 * @param {color4b_object} arg0
 */
setTextColor : function (
color4b 
)
{
},

/**
 * @method enableGlow
 * @param {color4b_object} arg0
 */
enableGlow : function (
color4b 
)
{
},

/**
 * @method getTextVerticalAlignment
 * @return {cc.TextVAlignment}
 */
getTextVerticalAlignment : function (
)
{
    return 0;
},

/**
 * @method getTextAreaSize
 * @return {size_object}
 */
getTextAreaSize : function (
)
{
    return cc.Size;
},

/**
 * @method setTextHorizontalAlignment
 * @param {cc.TextHAlignment} arg0
 */
setTextHorizontalAlignment : function (
texthalignment 
)
{
},

/**
 * @method create
* @param {String} str
* @param {String} str
* @param {float} float
* @return {ccui.Text|ccui.Text}
*/
create : function(
str,
str,
float 
)
{
    return ccui.Text;
},

/**
 * @method Text
 * @constructor
 */
Text : function (
)
{
},

};

/**
 * @class TextAtlas
 */
ccui.TextAtlas = {

/**
 * @method getStringLength
 * @return {long}
 */
getStringLength : function (
)
{
    return 0;
},

/**
 * @method getString
 * @return {String}
 */
getString : function (
)
{
    return ;
},

/**
 * @method setString
 * @param {String} arg0
 */
setString : function (
str 
)
{
},

/**
 * @method getRenderFile
 * @return {cc.ResourceData}
 */
getRenderFile : function (
)
{
    return cc.ResourceData;
},

/**
 * @method setProperty
 * @param {String} arg0
 * @param {String} arg1
 * @param {int} arg2
 * @param {int} arg3
 * @param {String} arg4
 */
setProperty : function (
str, 
str, 
int, 
int, 
str 
)
{
},

/**
 * @method adaptRenderers
 */
adaptRenderers : function (
)
{
},

/**
 * @method create
* @param {String} str
* @param {String} str
* @param {int} int
* @param {int} int
* @param {String} str
* @return {ccui.TextAtlas|ccui.TextAtlas}
*/
create : function(
str,
str,
int,
int,
str 
)
{
    return ccui.TextAtlas;
},

/**
 * @method TextAtlas
 * @constructor
 */
TextAtlas : function (
)
{
},

};

/**
 * @class LoadingBar
 */
ccui.LoadingBar = {

/**
 * @method setPercent
 * @param {float} arg0
 */
setPercent : function (
float 
)
{
},

/**
 * @method loadTexture
 * @param {String} arg0
 * @param {ccui.Widget::TextureResType} arg1
 */
loadTexture : function (
str, 
texturerestype 
)
{
},

/**
 * @method setDirection
 * @param {ccui.LoadingBar::Direction} arg0
 */
setDirection : function (
direction 
)
{
},

/**
 * @method getRenderFile
 * @return {cc.ResourceData}
 */
getRenderFile : function (
)
{
    return cc.ResourceData;
},

/**
 * @method setScale9Enabled
 * @param {bool} arg0
 */
setScale9Enabled : function (
bool 
)
{
},

/**
 * @method setCapInsets
 * @param {rect_object} arg0
 */
setCapInsets : function (
rect 
)
{
},

/**
 * @method getDirection
 * @return {ccui.LoadingBar::Direction}
 */
getDirection : function (
)
{
    return 0;
},

/**
 * @method getCapInsets
 * @return {rect_object}
 */
getCapInsets : function (
)
{
    return cc.Rect;
},

/**
 * @method isScale9Enabled
 * @return {bool}
 */
isScale9Enabled : function (
)
{
    return false;
},

/**
 * @method getPercent
 * @return {float}
 */
getPercent : function (
)
{
    return 0;
},

/**
 * @method create
* @param {String|String} str
* @param {float|ccui.Widget::TextureResType} float
* @param {float} float
* @return {ccui.LoadingBar|ccui.LoadingBar|ccui.LoadingBar}
*/
create : function(
str,
texturerestype,
float 
)
{
    return ccui.LoadingBar;
},

/**
 * @method LoadingBar
 * @constructor
 */
LoadingBar : function (
)
{
},

};

/**
 * @class ScrollView
 */
ccui.ScrollView = {

/**
 * @method scrollToTop
 * @param {float} arg0
 * @param {bool} arg1
 */
scrollToTop : function (
float, 
bool 
)
{
},

/**
 * @method scrollToPercentHorizontal
 * @param {float} arg0
 * @param {float} arg1
 * @param {bool} arg2
 */
scrollToPercentHorizontal : function (
float, 
float, 
bool 
)
{
},

/**
 * @method setScrollBarOpacity
 * @param {unsigned char} arg0
 */
setScrollBarOpacity : function (
char 
)
{
},

/**
 * @method setScrollBarEnabled
 * @param {bool} arg0
 */
setScrollBarEnabled : function (
bool 
)
{
},

/**
 * @method isInertiaScrollEnabled
 * @return {bool}
 */
isInertiaScrollEnabled : function (
)
{
    return false;
},

/**
 * @method scrollToBottom
 * @param {float} arg0
 * @param {bool} arg1
 */
scrollToBottom : function (
float, 
bool 
)
{
},

/**
 * @method getDirection
 * @return {ccui.ScrollView::Direction}
 */
getDirection : function (
)
{
    return 0;
},

/**
 * @method setScrollBarColor
 * @param {color3b_object} arg0
 */
setScrollBarColor : function (
color3b 
)
{
},

/**
 * @method scrollToBottomLeft
 * @param {float} arg0
 * @param {bool} arg1
 */
scrollToBottomLeft : function (
float, 
bool 
)
{
},

/**
 * @method getInnerContainer
 * @return {ccui.Layout}
 */
getInnerContainer : function (
)
{
    return ccui.Layout;
},

/**
 * @method jumpToBottom
 */
jumpToBottom : function (
)
{
},

/**
 * @method setInnerContainerPosition
 * @param {vec2_object} arg0
 */
setInnerContainerPosition : function (
vec2 
)
{
},

/**
 * @method setDirection
 * @param {ccui.ScrollView::Direction} arg0
 */
setDirection : function (
direction 
)
{
},

/**
 * @method scrollToTopLeft
 * @param {float} arg0
 * @param {bool} arg1
 */
scrollToTopLeft : function (
float, 
bool 
)
{
},

/**
 * @method jumpToTopRight
 */
jumpToTopRight : function (
)
{
},

/**
 * @method scrollToPercentBothDirection
 * @param {vec2_object} arg0
 * @param {float} arg1
 * @param {bool} arg2
 */
scrollToPercentBothDirection : function (
vec2, 
float, 
bool 
)
{
},

/**
 * @method setInnerContainerSize
 * @param {size_object} arg0
 */
setInnerContainerSize : function (
size 
)
{
},

/**
 * @method getInnerContainerPosition
 * @return {vec2_object}
 */
getInnerContainerPosition : function (
)
{
    return cc.Vec2;
},

/**
 * @method getInnerContainerSize
 * @return {size_object}
 */
getInnerContainerSize : function (
)
{
    return cc.Size;
},

/**
 * @method isBounceEnabled
 * @return {bool}
 */
isBounceEnabled : function (
)
{
    return false;
},

/**
 * @method jumpToPercentVertical
 * @param {float} arg0
 */
jumpToPercentVertical : function (
float 
)
{
},

/**
 * @method addEventListener
 * @param {function} arg0
 */
addEventListener : function (
func 
)
{
},

/**
 * @method setScrollBarAutoHideTime
 * @param {float} arg0
 */
setScrollBarAutoHideTime : function (
float 
)
{
},

/**
 * @method setScrollBarPositionFromCornerForHorizontal
 * @param {vec2_object} arg0
 */
setScrollBarPositionFromCornerForHorizontal : function (
vec2 
)
{
},

/**
 * @method setInertiaScrollEnabled
 * @param {bool} arg0
 */
setInertiaScrollEnabled : function (
bool 
)
{
},

/**
 * @method setScrollBarAutoHideEnabled
 * @param {bool} arg0
 */
setScrollBarAutoHideEnabled : function (
bool 
)
{
},

/**
 * @method getScrollBarColor
 * @return {color3b_object}
 */
getScrollBarColor : function (
)
{
    return cc.Color3B;
},

/**
 * @method jumpToTopLeft
 */
jumpToTopLeft : function (
)
{
},

/**
 * @method jumpToPercentHorizontal
 * @param {float} arg0
 */
jumpToPercentHorizontal : function (
float 
)
{
},

/**
 * @method jumpToBottomRight
 */
jumpToBottomRight : function (
)
{
},

/**
 * @method setTouchTotalTimeThreshold
 * @param {float} arg0
 */
setTouchTotalTimeThreshold : function (
float 
)
{
},

/**
 * @method getTouchTotalTimeThreshold
 * @return {float}
 */
getTouchTotalTimeThreshold : function (
)
{
    return 0;
},

/**
 * @method getScrollBarPositionFromCornerForHorizontal
 * @return {vec2_object}
 */
getScrollBarPositionFromCornerForHorizontal : function (
)
{
    return cc.Vec2;
},

/**
 * @method setScrollBarWidth
 * @param {float} arg0
 */
setScrollBarWidth : function (
float 
)
{
},

/**
 * @method setBounceEnabled
 * @param {bool} arg0
 */
setBounceEnabled : function (
bool 
)
{
},

/**
 * @method stopAutoScroll
 */
stopAutoScroll : function (
)
{
},

/**
 * @method jumpToTop
 */
jumpToTop : function (
)
{
},

/**
 * @method scrollToLeft
 * @param {float} arg0
 * @param {bool} arg1
 */
scrollToLeft : function (
float, 
bool 
)
{
},

/**
 * @method jumpToPercentBothDirection
 * @param {vec2_object} arg0
 */
jumpToPercentBothDirection : function (
vec2 
)
{
},

/**
 * @method getScrollBarPositionFromCornerForVertical
 * @return {vec2_object}
 */
getScrollBarPositionFromCornerForVertical : function (
)
{
    return cc.Vec2;
},

/**
 * @method scrollToPercentVertical
 * @param {float} arg0
 * @param {float} arg1
 * @param {bool} arg2
 */
scrollToPercentVertical : function (
float, 
float, 
bool 
)
{
},

/**
 * @method getScrollBarOpacity
 * @return {unsigned char}
 */
getScrollBarOpacity : function (
)
{
    return 0;
},

/**
 * @method scrollToBottomRight
 * @param {float} arg0
 * @param {bool} arg1
 */
scrollToBottomRight : function (
float, 
bool 
)
{
},

/**
 * @method setScrollBarPositionFromCorner
 * @param {vec2_object} arg0
 */
setScrollBarPositionFromCorner : function (
vec2 
)
{
},

/**
 * @method setScrollBarPositionFromCornerForVertical
 * @param {vec2_object} arg0
 */
setScrollBarPositionFromCornerForVertical : function (
vec2 
)
{
},

/**
 * @method getScrollBarAutoHideTime
 * @return {float}
 */
getScrollBarAutoHideTime : function (
)
{
    return 0;
},

/**
 * @method jumpToLeft
 */
jumpToLeft : function (
)
{
},

/**
 * @method scrollToRight
 * @param {float} arg0
 * @param {bool} arg1
 */
scrollToRight : function (
float, 
bool 
)
{
},

/**
 * @method isScrollBarEnabled
 * @return {bool}
 */
isScrollBarEnabled : function (
)
{
    return false;
},

/**
 * @method getScrollBarWidth
 * @return {float}
 */
getScrollBarWidth : function (
)
{
    return 0;
},

/**
 * @method isScrollBarAutoHideEnabled
 * @return {bool}
 */
isScrollBarAutoHideEnabled : function (
)
{
    return false;
},

/**
 * @method jumpToBottomLeft
 */
jumpToBottomLeft : function (
)
{
},

/**
 * @method jumpToRight
 */
jumpToRight : function (
)
{
},

/**
 * @method scrollToTopRight
 * @param {float} arg0
 * @param {bool} arg1
 */
scrollToTopRight : function (
float, 
bool 
)
{
},

/**
 * @method create
 * @return {ccui.ScrollView}
 */
create : function (
)
{
    return ccui.ScrollView;
},

/**
 * @method ScrollView
 * @constructor
 */
ScrollView : function (
)
{
},

};

/**
 * @class ListView
 */
ccui.ListView = {

/**
 * @method setGravity
 * @param {ccui.ListView::Gravity} arg0
 */
setGravity : function (
gravity 
)
{
},

/**
 * @method removeLastItem
 */
removeLastItem : function (
)
{
},

/**
 * @method getCenterItemInCurrentView
 * @return {ccui.Widget}
 */
getCenterItemInCurrentView : function (
)
{
    return ccui.Widget;
},

/**
 * @method getCurSelectedIndex
 * @return {long}
 */
getCurSelectedIndex : function (
)
{
    return 0;
},

/**
 * @method getItemsMargin
 * @return {float}
 */
getItemsMargin : function (
)
{
    return 0;
},

/**
 * @method jumpToItem
 * @param {long} arg0
 * @param {vec2_object} arg1
 * @param {vec2_object} arg2
 */
jumpToItem : function (
long, 
vec2, 
vec2 
)
{
},

/**
 * @method setMagneticType
 * @param {ccui.ListView::MagneticType} arg0
 */
setMagneticType : function (
magnetictype 
)
{
},

/**
 * @method getIndex
 * @param {ccui.Widget} arg0
 * @return {long}
 */
getIndex : function (
widget 
)
{
    return 0;
},

/**
 * @method pushBackCustomItem
 * @param {ccui.Widget} arg0
 */
pushBackCustomItem : function (
widget 
)
{
},

/**
 * @method insertDefaultItem
 * @param {long} arg0
 */
insertDefaultItem : function (
long 
)
{
},

/**
 * @method setMagneticAllowedOutOfBoundary
 * @param {bool} arg0
 */
setMagneticAllowedOutOfBoundary : function (
bool 
)
{
},

/**
 * @method addEventListener
 * @param {function} arg0
 */
addEventListener : function (
func 
)
{
},

/**
 * @method doLayout
 */
doLayout : function (
)
{
},

/**
 * @method getTopmostItemInCurrentView
 * @return {ccui.Widget}
 */
getTopmostItemInCurrentView : function (
)
{
    return ccui.Widget;
},

/**
 * @method removeAllItems
 */
removeAllItems : function (
)
{
},

/**
 * @method getBottommostItemInCurrentView
 * @return {ccui.Widget}
 */
getBottommostItemInCurrentView : function (
)
{
    return ccui.Widget;
},

/**
 * @method getItems
 * @return {Array}
 */
getItems : function (
)
{
    return new Array();
},

/**
 * @method getLeftmostItemInCurrentView
 * @return {ccui.Widget}
 */
getLeftmostItemInCurrentView : function (
)
{
    return ccui.Widget;
},

/**
 * @method setItemsMargin
 * @param {float} arg0
 */
setItemsMargin : function (
float 
)
{
},

/**
 * @method getMagneticType
 * @return {ccui.ListView::MagneticType}
 */
getMagneticType : function (
)
{
    return 0;
},

/**
 * @method getItem
 * @param {long} arg0
 * @return {ccui.Widget}
 */
getItem : function (
long 
)
{
    return ccui.Widget;
},

/**
 * @method removeItem
 * @param {long} arg0
 */
removeItem : function (
long 
)
{
},

/**
 * @method scrollToItem
* @param {long|long} long
* @param {vec2_object|vec2_object} vec2
* @param {vec2_object|vec2_object} vec2
* @param {float} float
*/
scrollToItem : function(
long,
vec2,
vec2,
float 
)
{
},

/**
 * @method pushBackDefaultItem
 */
pushBackDefaultItem : function (
)
{
},

/**
 * @method getMagneticAllowedOutOfBoundary
 * @return {bool}
 */
getMagneticAllowedOutOfBoundary : function (
)
{
    return false;
},

/**
 * @method getClosestItemToPosition
 * @param {vec2_object} arg0
 * @param {vec2_object} arg1
 * @return {ccui.Widget}
 */
getClosestItemToPosition : function (
vec2, 
vec2 
)
{
    return ccui.Widget;
},

/**
 * @method getRightmostItemInCurrentView
 * @return {ccui.Widget}
 */
getRightmostItemInCurrentView : function (
)
{
    return ccui.Widget;
},

/**
 * @method getClosestItemToPositionInCurrentView
 * @param {vec2_object} arg0
 * @param {vec2_object} arg1
 * @return {ccui.Widget}
 */
getClosestItemToPositionInCurrentView : function (
vec2, 
vec2 
)
{
    return ccui.Widget;
},

/**
 * @method setItemModel
 * @param {ccui.Widget} arg0
 */
setItemModel : function (
widget 
)
{
},

/**
 * @method insertCustomItem
 * @param {ccui.Widget} arg0
 * @param {long} arg1
 */
insertCustomItem : function (
widget, 
long 
)
{
},

/**
 * @method create
 * @return {ccui.ListView}
 */
create : function (
)
{
    return ccui.ListView;
},

/**
 * @method ListView
 * @constructor
 */
ListView : function (
)
{
},

};

/**
 * @class Slider
 */
ccui.Slider = {

/**
 * @method setPercent
 * @param {int} arg0
 */
setPercent : function (
int 
)
{
},

/**
 * @method getMaxPercent
 * @return {int}
 */
getMaxPercent : function (
)
{
    return 0;
},

/**
 * @method loadSlidBallTextureNormal
 * @param {String} arg0
 * @param {ccui.Widget::TextureResType} arg1
 */
loadSlidBallTextureNormal : function (
str, 
texturerestype 
)
{
},

/**
 * @method loadProgressBarTexture
 * @param {String} arg0
 * @param {ccui.Widget::TextureResType} arg1
 */
loadProgressBarTexture : function (
str, 
texturerestype 
)
{
},

/**
 * @method getBallNormalFile
 * @return {cc.ResourceData}
 */
getBallNormalFile : function (
)
{
    return cc.ResourceData;
},

/**
 * @method setScale9Enabled
 * @param {bool} arg0
 */
setScale9Enabled : function (
bool 
)
{
},

/**
 * @method getBallPressedFile
 * @return {cc.ResourceData}
 */
getBallPressedFile : function (
)
{
    return cc.ResourceData;
},

/**
 * @method getZoomScale
 * @return {float}
 */
getZoomScale : function (
)
{
    return 0;
},

/**
 * @method setCapInsetProgressBarRenderer
 * @param {rect_object} arg0
 */
setCapInsetProgressBarRenderer : function (
rect 
)
{
},

/**
 * @method loadSlidBallTextures
 * @param {String} arg0
 * @param {String} arg1
 * @param {String} arg2
 * @param {ccui.Widget::TextureResType} arg3
 */
loadSlidBallTextures : function (
str, 
str, 
str, 
texturerestype 
)
{
},

/**
 * @method addEventListener
 * @param {function} arg0
 */
addEventListener : function (
func 
)
{
},

/**
 * @method setMaxPercent
 * @param {int} arg0
 */
setMaxPercent : function (
int 
)
{
},

/**
 * @method loadBarTexture
 * @param {String} arg0
 * @param {ccui.Widget::TextureResType} arg1
 */
loadBarTexture : function (
str, 
texturerestype 
)
{
},

/**
 * @method getProgressBarFile
 * @return {cc.ResourceData}
 */
getProgressBarFile : function (
)
{
    return cc.ResourceData;
},

/**
 * @method getCapInsetsBarRenderer
 * @return {rect_object}
 */
getCapInsetsBarRenderer : function (
)
{
    return cc.Rect;
},

/**
 * @method getCapInsetsProgressBarRenderer
 * @return {rect_object}
 */
getCapInsetsProgressBarRenderer : function (
)
{
    return cc.Rect;
},

/**
 * @method loadSlidBallTexturePressed
 * @param {String} arg0
 * @param {ccui.Widget::TextureResType} arg1
 */
loadSlidBallTexturePressed : function (
str, 
texturerestype 
)
{
},

/**
 * @method getBackFile
 * @return {cc.ResourceData}
 */
getBackFile : function (
)
{
    return cc.ResourceData;
},

/**
 * @method isScale9Enabled
 * @return {bool}
 */
isScale9Enabled : function (
)
{
    return false;
},

/**
 * @method getBallDisabledFile
 * @return {cc.ResourceData}
 */
getBallDisabledFile : function (
)
{
    return cc.ResourceData;
},

/**
 * @method setCapInsetsBarRenderer
 * @param {rect_object} arg0
 */
setCapInsetsBarRenderer : function (
rect 
)
{
},

/**
 * @method getPercent
 * @return {int}
 */
getPercent : function (
)
{
    return 0;
},

/**
 * @method setCapInsets
 * @param {rect_object} arg0
 */
setCapInsets : function (
rect 
)
{
},

/**
 * @method loadSlidBallTextureDisabled
 * @param {String} arg0
 * @param {ccui.Widget::TextureResType} arg1
 */
loadSlidBallTextureDisabled : function (
str, 
texturerestype 
)
{
},

/**
 * @method setZoomScale
 * @param {float} arg0
 */
setZoomScale : function (
float 
)
{
},

/**
 * @method create
* @param {String} str
* @param {String} str
* @param {ccui.Widget::TextureResType} texturerestype
* @return {ccui.Slider|ccui.Slider}
*/
create : function(
str,
str,
texturerestype 
)
{
    return ccui.Slider;
},

/**
 * @method Slider
 * @constructor
 */
Slider : function (
)
{
},

};

/**
 * @class UICCTextField
 */
ccui.UICCTextField = {

/**
 * @method onTextFieldAttachWithIME
 * @param {cc.TextFieldTTF} arg0
 * @return {bool}
 */
onTextFieldAttachWithIME : function (
textfieldttf 
)
{
    return false;
},

/**
 * @method setPasswordText
 * @param {String} arg0
 */
setPasswordText : function (
str 
)
{
},

/**
 * @method setAttachWithIME
 * @param {bool} arg0
 */
setAttachWithIME : function (
bool 
)
{
},

/**
 * @method getDeleteBackward
 * @return {bool}
 */
getDeleteBackward : function (
)
{
    return false;
},

/**
 * @method getAttachWithIME
 * @return {bool}
 */
getAttachWithIME : function (
)
{
    return false;
},

/**
 * @method onTextFieldDeleteBackward
 * @param {cc.TextFieldTTF} arg0
 * @param {char} arg1
 * @param {unsigned long} arg2
 * @return {bool}
 */
onTextFieldDeleteBackward : function (
textfieldttf, 
char, 
long 
)
{
    return false;
},

/**
 * @method getInsertText
 * @return {bool}
 */
getInsertText : function (
)
{
    return false;
},

/**
 * @method deleteBackward
 */
deleteBackward : function (
)
{
},

/**
 * @method setInsertText
 * @param {bool} arg0
 */
setInsertText : function (
bool 
)
{
},

/**
 * @method getDetachWithIME
 * @return {bool}
 */
getDetachWithIME : function (
)
{
    return false;
},

/**
 * @method getCharCount
 * @return {unsigned long}
 */
getCharCount : function (
)
{
    return 0;
},

/**
 * @method closeIME
 */
closeIME : function (
)
{
},

/**
 * @method setPasswordEnabled
 * @param {bool} arg0
 */
setPasswordEnabled : function (
bool 
)
{
},

/**
 * @method setMaxLengthEnabled
 * @param {bool} arg0
 */
setMaxLengthEnabled : function (
bool 
)
{
},

/**
 * @method isPasswordEnabled
 * @return {bool}
 */
isPasswordEnabled : function (
)
{
    return false;
},

/**
 * @method insertText
 * @param {char} arg0
 * @param {unsigned long} arg1
 */
insertText : function (
char, 
long 
)
{
},

/**
 * @method setPasswordStyleText
 * @param {String} arg0
 */
setPasswordStyleText : function (
str 
)
{
},

/**
 * @method onTextFieldInsertText
 * @param {cc.TextFieldTTF} arg0
 * @param {char} arg1
 * @param {unsigned long} arg2
 * @return {bool}
 */
onTextFieldInsertText : function (
textfieldttf, 
char, 
long 
)
{
    return false;
},

/**
 * @method onTextFieldDetachWithIME
 * @param {cc.TextFieldTTF} arg0
 * @return {bool}
 */
onTextFieldDetachWithIME : function (
textfieldttf 
)
{
    return false;
},

/**
 * @method getMaxLength
 * @return {int}
 */
getMaxLength : function (
)
{
    return 0;
},

/**
 * @method isMaxLengthEnabled
 * @return {bool}
 */
isMaxLengthEnabled : function (
)
{
    return false;
},

/**
 * @method openIME
 */
openIME : function (
)
{
},

/**
 * @method setDetachWithIME
 * @param {bool} arg0
 */
setDetachWithIME : function (
bool 
)
{
},

/**
 * @method setMaxLength
 * @param {int} arg0
 */
setMaxLength : function (
int 
)
{
},

/**
 * @method setDeleteBackward
 * @param {bool} arg0
 */
setDeleteBackward : function (
bool 
)
{
},

/**
 * @method create
 * @param {String} arg0
 * @param {String} arg1
 * @param {float} arg2
 * @return {ccui.UICCTextField}
 */
create : function (
str, 
str, 
float 
)
{
    return ccui.UICCTextField;
},

/**
 * @method UICCTextField
 * @constructor
 */
UICCTextField : function (
)
{
},

};

/**
 * @class TextField
 */
ccui.TextField = {

/**
 * @method setAttachWithIME
 * @param {bool} arg0
 */
setAttachWithIME : function (
bool 
)
{
},

/**
 * @method getFontSize
 * @return {int}
 */
getFontSize : function (
)
{
    return 0;
},

/**
 * @method getString
 * @return {String}
 */
getString : function (
)
{
    return ;
},

/**
 * @method setPasswordStyleText
 * @param {char} arg0
 */
setPasswordStyleText : function (
char 
)
{
},

/**
 * @method getDeleteBackward
 * @return {bool}
 */
getDeleteBackward : function (
)
{
    return false;
},

/**
 * @method getTextColor
 * @return {color4b_object}
 */
getTextColor : function (
)
{
    return cc.Color4B;
},

/**
 * @method getPlaceHolder
 * @return {String}
 */
getPlaceHolder : function (
)
{
    return ;
},

/**
 * @method getAttachWithIME
 * @return {bool}
 */
getAttachWithIME : function (
)
{
    return false;
},

/**
 * @method setFontName
 * @param {String} arg0
 */
setFontName : function (
str 
)
{
},

/**
 * @method getInsertText
 * @return {bool}
 */
getInsertText : function (
)
{
    return false;
},

/**
 * @method setInsertText
 * @param {bool} arg0
 */
setInsertText : function (
bool 
)
{
},

/**
 * @method setString
 * @param {String} arg0
 */
setString : function (
str 
)
{
},

/**
 * @method getDetachWithIME
 * @return {bool}
 */
getDetachWithIME : function (
)
{
    return false;
},

/**
 * @method setTextVerticalAlignment
 * @param {cc.TextVAlignment} arg0
 */
setTextVerticalAlignment : function (
textvalignment 
)
{
},

/**
 * @method addEventListener
 * @param {function} arg0
 */
addEventListener : function (
func 
)
{
},

/**
 * @method didNotSelectSelf
 */
didNotSelectSelf : function (
)
{
},

/**
 * @method getFontName
 * @return {String}
 */
getFontName : function (
)
{
    return ;
},

/**
 * @method setTextAreaSize
 * @param {size_object} arg0
 */
setTextAreaSize : function (
size 
)
{
},

/**
 * @method attachWithIME
 */
attachWithIME : function (
)
{
},

/**
 * @method getStringLength
 * @return {int}
 */
getStringLength : function (
)
{
    return 0;
},

/**
 * @method getAutoRenderSize
 * @return {size_object}
 */
getAutoRenderSize : function (
)
{
    return cc.Size;
},

/**
 * @method setPasswordEnabled
 * @param {bool} arg0
 */
setPasswordEnabled : function (
bool 
)
{
},

/**
 * @method getPlaceHolderColor
 * @return {color4b_object}
 */
getPlaceHolderColor : function (
)
{
    return cc.Color4B;
},

/**
 * @method getPasswordStyleText
 * @return {char}
 */
getPasswordStyleText : function (
)
{
    return 0;
},

/**
 * @method setMaxLengthEnabled
 * @param {bool} arg0
 */
setMaxLengthEnabled : function (
bool 
)
{
},

/**
 * @method isPasswordEnabled
 * @return {bool}
 */
isPasswordEnabled : function (
)
{
    return false;
},

/**
 * @method setDeleteBackward
 * @param {bool} arg0
 */
setDeleteBackward : function (
bool 
)
{
},

/**
 * @method setCursorPosition
 * @param {unsigned long} arg0
 */
setCursorPosition : function (
long 
)
{
},

/**
 * @method getTextHorizontalAlignment
 * @return {cc.TextHAlignment}
 */
getTextHorizontalAlignment : function (
)
{
    return 0;
},

/**
 * @method setFontSize
 * @param {int} arg0
 */
setFontSize : function (
int 
)
{
},

/**
 * @method setPlaceHolder
 * @param {String} arg0
 */
setPlaceHolder : function (
str 
)
{
},

/**
 * @method setCursorFromPoint
 * @param {vec2_object} arg0
 * @param {cc.Camera} arg1
 */
setCursorFromPoint : function (
vec2, 
camera 
)
{
},

/**
 * @method setPlaceHolderColor
* @param {color4b_object|color3b_object} color4b
*/
setPlaceHolderColor : function(
color3b 
)
{
},

/**
 * @method setTextHorizontalAlignment
 * @param {cc.TextHAlignment} arg0
 */
setTextHorizontalAlignment : function (
texthalignment 
)
{
},

/**
 * @method setTextColor
 * @param {color4b_object} arg0
 */
setTextColor : function (
color4b 
)
{
},

/**
 * @method setCursorChar
 * @param {char} arg0
 */
setCursorChar : function (
char 
)
{
},

/**
 * @method getMaxLength
 * @return {int}
 */
getMaxLength : function (
)
{
    return 0;
},

/**
 * @method isMaxLengthEnabled
 * @return {bool}
 */
isMaxLengthEnabled : function (
)
{
    return false;
},

/**
 * @method setDetachWithIME
 * @param {bool} arg0
 */
setDetachWithIME : function (
bool 
)
{
},

/**
 * @method getTextVerticalAlignment
 * @return {cc.TextVAlignment}
 */
getTextVerticalAlignment : function (
)
{
    return 0;
},

/**
 * @method setTouchAreaEnabled
 * @param {bool} arg0
 */
setTouchAreaEnabled : function (
bool 
)
{
},

/**
 * @method setMaxLength
 * @param {int} arg0
 */
setMaxLength : function (
int 
)
{
},

/**
 * @method setCursorEnabled
 * @param {bool} arg0
 */
setCursorEnabled : function (
bool 
)
{
},

/**
 * @method setTouchSize
 * @param {size_object} arg0
 */
setTouchSize : function (
size 
)
{
},

/**
 * @method getTouchSize
 * @return {size_object}
 */
getTouchSize : function (
)
{
    return cc.Size;
},

/**
 * @method create
* @param {String} str
* @param {String} str
* @param {int} int
* @return {ccui.TextField|ccui.TextField}
*/
create : function(
str,
str,
int 
)
{
    return ccui.TextField;
},

/**
 * @method TextField
 * @constructor
 */
TextField : function (
)
{
},

};

/**
 * @class TextBMFont
 */
ccui.TextBMFont = {

/**
 * @method getStringLength
 * @return {long}
 */
getStringLength : function (
)
{
    return 0;
},

/**
 * @method getString
 * @return {String}
 */
getString : function (
)
{
    return ;
},

/**
 * @method setString
 * @param {String} arg0
 */
setString : function (
str 
)
{
},

/**
 * @method getRenderFile
 * @return {cc.ResourceData}
 */
getRenderFile : function (
)
{
    return cc.ResourceData;
},

/**
 * @method setFntFile
 * @param {String} arg0
 */
setFntFile : function (
str 
)
{
},

/**
 * @method resetRender
 */
resetRender : function (
)
{
},

/**
 * @method create
* @param {String} str
* @param {String} str
* @return {ccui.TextBMFont|ccui.TextBMFont}
*/
create : function(
str,
str 
)
{
    return ccui.TextBMFont;
},

/**
 * @method TextBMFont
 * @constructor
 */
TextBMFont : function (
)
{
},

};

/**
 * @class PageView
 */
ccui.PageView = {

/**
 * @method setIndicatorSpaceBetweenIndexNodes
 * @param {float} arg0
 */
setIndicatorSpaceBetweenIndexNodes : function (
float 
)
{
},

/**
 * @method setIndicatorSelectedIndexColor
 * @param {color3b_object} arg0
 */
setIndicatorSelectedIndexColor : function (
color3b 
)
{
},

/**
 * @method getIndicatorSelectedIndexColor
 * @return {color3b_object}
 */
getIndicatorSelectedIndexColor : function (
)
{
    return cc.Color3B;
},

/**
 * @method getIndicatorPositionAsAnchorPoint
 * @return {vec2_object}
 */
getIndicatorPositionAsAnchorPoint : function (
)
{
    return cc.Vec2;
},

/**
 * @method setIndicatorPosition
 * @param {vec2_object} arg0
 */
setIndicatorPosition : function (
vec2 
)
{
},

/**
 * @method getIndicatorPosition
 * @return {vec2_object}
 */
getIndicatorPosition : function (
)
{
    return cc.Vec2;
},

/**
 * @method insertPage
 * @param {ccui.Widget} arg0
 * @param {int} arg1
 */
insertPage : function (
widget, 
int 
)
{
},

/**
 * @method getCurrentPageIndex
 * @return {long}
 */
getCurrentPageIndex : function (
)
{
    return 0;
},

/**
 * @method removePage
 * @param {ccui.Widget} arg0
 */
removePage : function (
widget 
)
{
},

/**
 * @method addEventListener
 * @param {function} arg0
 */
addEventListener : function (
func 
)
{
},

/**
 * @method setCurrentPageIndex
 * @param {long} arg0
 */
setCurrentPageIndex : function (
long 
)
{
},

/**
 * @method getIndicatorEnabled
 * @return {bool}
 */
getIndicatorEnabled : function (
)
{
    return false;
},

/**
 * @method scrollToPage
 * @param {long} arg0
 */
scrollToPage : function (
long 
)
{
},

/**
 * @method setIndicatorPositionAsAnchorPoint
 * @param {vec2_object} arg0
 */
setIndicatorPositionAsAnchorPoint : function (
vec2 
)
{
},

/**
 * @method scrollToItem
 * @param {long} arg0
 */
scrollToItem : function (
long 
)
{
},

/**
 * @method setIndicatorEnabled
 * @param {bool} arg0
 */
setIndicatorEnabled : function (
bool 
)
{
},

/**
 * @method addPage
 * @param {ccui.Widget} arg0
 */
addPage : function (
widget 
)
{
},

/**
 * @method getIndicatorSpaceBetweenIndexNodes
 * @return {float}
 */
getIndicatorSpaceBetweenIndexNodes : function (
)
{
    return 0;
},

/**
 * @method removeAllPages
 */
removeAllPages : function (
)
{
},

/**
 * @method removePageAtIndex
 * @param {long} arg0
 */
removePageAtIndex : function (
long 
)
{
},

/**
 * @method create
 * @return {ccui.PageView}
 */
create : function (
)
{
    return ccui.PageView;
},

/**
 * @method PageView
 * @constructor
 */
PageView : function (
)
{
},

};

/**
 * @class Helper
 */
ccui.Helper = {

/**
 * @method getSubStringOfUTF8String
 * @param {String} arg0
 * @param {unsigned long} arg1
 * @param {unsigned long} arg2
 * @return {String}
 */
getSubStringOfUTF8String : function (
str, 
long, 
long 
)
{
    return ;
},

/**
 * @method convertBoundingBoxToScreen
 * @param {cc.Node} arg0
 * @return {rect_object}
 */
convertBoundingBoxToScreen : function (
node 
)
{
    return cc.Rect;
},

/**
 * @method changeLayoutSystemActiveState
 * @param {bool} arg0
 */
changeLayoutSystemActiveState : function (
bool 
)
{
},

/**
 * @method seekActionWidgetByActionTag
 * @param {ccui.Widget} arg0
 * @param {int} arg1
 * @return {ccui.Widget}
 */
seekActionWidgetByActionTag : function (
widget, 
int 
)
{
    return ccui.Widget;
},

/**
 * @method seekWidgetByName
 * @param {ccui.Widget} arg0
 * @param {String} arg1
 * @return {ccui.Widget}
 */
seekWidgetByName : function (
widget, 
str 
)
{
    return ccui.Widget;
},

/**
 * @method seekWidgetByTag
 * @param {ccui.Widget} arg0
 * @param {int} arg1
 * @return {ccui.Widget}
 */
seekWidgetByTag : function (
widget, 
int 
)
{
    return ccui.Widget;
},

/**
 * @method restrictCapInsetRect
 * @param {rect_object} arg0
 * @param {size_object} arg1
 * @return {rect_object}
 */
restrictCapInsetRect : function (
rect, 
size 
)
{
    return cc.Rect;
},

/**
 * @method doLayout
 * @param {cc.Node} arg0
 */
doLayout : function (
node 
)
{
},

};

/**
 * @class RichElement
 */
ccui.RichElement = {

/**
 * @method init
 * @param {int} arg0
 * @param {color3b_object} arg1
 * @param {unsigned char} arg2
 * @return {bool}
 */
init : function (
int, 
color3b, 
char 
)
{
    return false;
},

/**
 * @method RichElement
 * @constructor
 */
RichElement : function (
)
{
},

};

/**
 * @class RichElementText
 */
ccui.RichElementText = {

/**
 * @method init
 * @param {int} arg0
 * @param {color3b_object} arg1
 * @param {unsigned char} arg2
 * @param {String} arg3
 * @param {String} arg4
 * @param {float} arg5
 * @param {unsigned int} arg6
 * @param {String} arg7
 * @return {bool}
 */
init : function (
int, 
color3b, 
char, 
str, 
str, 
float, 
int, 
str 
)
{
    return false;
},

/**
 * @method create
 * @param {int} arg0
 * @param {color3b_object} arg1
 * @param {unsigned char} arg2
 * @param {String} arg3
 * @param {String} arg4
 * @param {float} arg5
 * @param {unsigned int} arg6
 * @param {String} arg7
 * @return {ccui.RichElementText}
 */
create : function (
int, 
color3b, 
char, 
str, 
str, 
float, 
int, 
str 
)
{
    return ccui.RichElementText;
},

/**
 * @method RichElementText
 * @constructor
 */
RichElementText : function (
)
{
},

};

/**
 * @class RichElementImage
 */
ccui.RichElementImage = {

/**
 * @method setHeight
 * @param {int} arg0
 */
setHeight : function (
int 
)
{
},

/**
 * @method init
 * @param {int} arg0
 * @param {color3b_object} arg1
 * @param {unsigned char} arg2
 * @param {String} arg3
 * @return {bool}
 */
init : function (
int, 
color3b, 
char, 
str 
)
{
    return false;
},

/**
 * @method setWidth
 * @param {int} arg0
 */
setWidth : function (
int 
)
{
},

/**
 * @method create
 * @param {int} arg0
 * @param {color3b_object} arg1
 * @param {unsigned char} arg2
 * @param {String} arg3
 * @return {ccui.RichElementImage}
 */
create : function (
int, 
color3b, 
char, 
str 
)
{
    return ccui.RichElementImage;
},

/**
 * @method RichElementImage
 * @constructor
 */
RichElementImage : function (
)
{
},

};

/**
 * @class RichElementCustomNode
 */
ccui.RichElementCustomNode = {

/**
 * @method init
 * @param {int} arg0
 * @param {color3b_object} arg1
 * @param {unsigned char} arg2
 * @param {cc.Node} arg3
 * @return {bool}
 */
init : function (
int, 
color3b, 
char, 
node 
)
{
    return false;
},

/**
 * @method create
 * @param {int} arg0
 * @param {color3b_object} arg1
 * @param {unsigned char} arg2
 * @param {cc.Node} arg3
 * @return {ccui.RichElementCustomNode}
 */
create : function (
int, 
color3b, 
char, 
node 
)
{
    return ccui.RichElementCustomNode;
},

/**
 * @method RichElementCustomNode
 * @constructor
 */
RichElementCustomNode : function (
)
{
},

};

/**
 * @class RichText
 */
ccui.RichText = {

/**
 * @method insertElement
 * @param {ccui.RichElement} arg0
 * @param {int} arg1
 */
insertElement : function (
richelement, 
int 
)
{
},

/**
 * @method pushBackElement
 * @param {ccui.RichElement} arg0
 */
pushBackElement : function (
richelement 
)
{
},

/**
 * @method setWrapMode
 * @param {ccui.RichText::WrapMode} arg0
 */
setWrapMode : function (
wrapmode 
)
{
},

/**
 * @method setVerticalSpace
 * @param {float} arg0
 */
setVerticalSpace : function (
float 
)
{
},

/**
 * @method getWrapMode
 * @return {ccui.RichText::WrapMode}
 */
getWrapMode : function (
)
{
    return 0;
},

/**
 * @method formatText
 */
formatText : function (
)
{
},

/**
 * @method initWithXML
 * @param {String} arg0
 * @return {bool}
 */
initWithXML : function (
str 
)
{
    return false;
},

/**
 * @method removeElement
* @param {ccui.RichElement|int} richelement
*/
removeElement : function(
int 
)
{
},

/**
 * @method create
 * @return {ccui.RichText}
 */
create : function (
)
{
    return ccui.RichText;
},

/**
 * @method createWithXML
 * @param {String} arg0
 * @return {ccui.RichText}
 */
createWithXML : function (
str 
)
{
    return ccui.RichText;
},

/**
 * @method RichText
 * @constructor
 */
RichText : function (
)
{
},

};

/**
 * @class HBox
 */
ccui.HBox = {

/**
 * @method initWithSize
 * @param {size_object} arg0
 * @return {bool}
 */
initWithSize : function (
size 
)
{
    return false;
},

/**
 * @method create
* @param {size_object} size
* @return {ccui.HBox|ccui.HBox}
*/
create : function(
size 
)
{
    return ccui.HBox;
},

/**
 * @method HBox
 * @constructor
 */
HBox : function (
)
{
},

};

/**
 * @class VBox
 */
ccui.VBox = {

/**
 * @method initWithSize
 * @param {size_object} arg0
 * @return {bool}
 */
initWithSize : function (
size 
)
{
    return false;
},

/**
 * @method create
* @param {size_object} size
* @return {ccui.VBox|ccui.VBox}
*/
create : function(
size 
)
{
    return ccui.VBox;
},

/**
 * @method VBox
 * @constructor
 */
VBox : function (
)
{
},

};

/**
 * @class RelativeBox
 */
ccui.RelativeBox = {

/**
 * @method initWithSize
 * @param {size_object} arg0
 * @return {bool}
 */
initWithSize : function (
size 
)
{
    return false;
},

/**
 * @method create
* @param {size_object} size
* @return {ccui.RelativeBox|ccui.RelativeBox}
*/
create : function(
size 
)
{
    return ccui.RelativeBox;
},

/**
 * @method RelativeBox
 * @constructor
 */
RelativeBox : function (
)
{
},

};

/**
 * @class Scale9Sprite
 */
ccui.Scale9Sprite = {

/**
 * @method disableCascadeColor
 */
disableCascadeColor : function (
)
{
},

/**
 * @method updateWithSprite
* @param {cc.Sprite|cc.Sprite} sprite
* @param {rect_object|rect_object} rect
* @param {bool|bool} bool
* @param {vec2_object|rect_object} vec2
* @param {size_object} size
* @param {rect_object} rect
* @return {bool|bool}
*/
updateWithSprite : function(
sprite,
rect,
bool,
vec2,
size,
rect 
)
{
    return false;
},

/**
 * @method isFlippedX
 * @return {bool}
 */
isFlippedX : function (
)
{
    return false;
},

/**
 * @method setScale9Enabled
 * @param {bool} arg0
 */
setScale9Enabled : function (
bool 
)
{
},

/**
 * @method setFlippedY
 * @param {bool} arg0
 */
setFlippedY : function (
bool 
)
{
},

/**
 * @method setFlippedX
 * @param {bool} arg0
 */
setFlippedX : function (
bool 
)
{
},

/**
 * @method resizableSpriteWithCapInsets
 * @param {rect_object} arg0
 * @return {ccui.Scale9Sprite}
 */
resizableSpriteWithCapInsets : function (
rect 
)
{
    return ccui.Scale9Sprite;
},

/**
 * @method disableCascadeOpacity
 */
disableCascadeOpacity : function (
)
{
},

/**
 * @method getState
 * @return {ccui.Scale9Sprite::State}
 */
getState : function (
)
{
    return 0;
},

/**
 * @method setState
 * @param {ccui.Scale9Sprite::State} arg0
 */
setState : function (
state 
)
{
},

/**
 * @method setInsetBottom
 * @param {float} arg0
 */
setInsetBottom : function (
float 
)
{
},

/**
 * @method initWithSpriteFrameName
* @param {String|String} str
* @param {rect_object} rect
* @return {bool|bool}
*/
initWithSpriteFrameName : function(
str,
rect 
)
{
    return false;
},

/**
 * @method getSprite
 * @return {cc.Sprite}
 */
getSprite : function (
)
{
    return cc.Sprite;
},

/**
 * @method setInsetTop
 * @param {float} arg0
 */
setInsetTop : function (
float 
)
{
},

/**
 * @method setRenderingType
 * @param {ccui.Scale9Sprite::RenderingType} arg0
 */
setRenderingType : function (
renderingtype 
)
{
},

/**
 * @method init
* @param {cc.Sprite|cc.Sprite|cc.Sprite} sprite
* @param {rect_object|rect_object|rect_object} rect
* @param {rect_object|bool|bool} rect
* @param {rect_object|vec2_object} rect
* @param {size_object} size
* @param {rect_object} rect
* @return {bool|bool|bool}
*/
init : function(
sprite,
rect,
bool,
vec2,
size,
rect 
)
{
    return false;
},

/**
 * @method setPreferredSize
 * @param {size_object} arg0
 */
setPreferredSize : function (
size 
)
{
},

/**
 * @method setSpriteFrame
 * @param {cc.SpriteFrame} arg0
 * @param {rect_object} arg1
 */
setSpriteFrame : function (
spriteframe, 
rect 
)
{
},

/**
 * @method getBlendFunc
 * @return {cc.BlendFunc}
 */
getBlendFunc : function (
)
{
    return cc.BlendFunc;
},

/**
 * @method getInsetBottom
 * @return {float}
 */
getInsetBottom : function (
)
{
    return 0;
},

/**
 * @method getCapInsets
 * @return {rect_object}
 */
getCapInsets : function (
)
{
    return cc.Rect;
},

/**
 * @method isScale9Enabled
 * @return {bool}
 */
isScale9Enabled : function (
)
{
    return false;
},

/**
 * @method resetRender
 */
resetRender : function (
)
{
},

/**
 * @method getRenderingType
 * @return {ccui.Scale9Sprite::RenderingType}
 */
getRenderingType : function (
)
{
    return 0;
},

/**
 * @method getInsetRight
 * @return {float}
 */
getInsetRight : function (
)
{
    return 0;
},

/**
 * @method getOriginalSize
 * @return {size_object}
 */
getOriginalSize : function (
)
{
    return cc.Size;
},

/**
 * @method initWithFile
* @param {String|String|rect_object|String} str
* @param {rect_object|rect_object|String} rect
* @param {rect_object} rect
* @return {bool|bool|bool|bool}
*/
initWithFile : function(
str,
rect,
rect 
)
{
    return false;
},

/**
 * @method setBlendFunc
 * @param {cc.BlendFunc} arg0
 */
setBlendFunc : function (
blendfunc 
)
{
},

/**
 * @method getInsetTop
 * @return {float}
 */
getInsetTop : function (
)
{
    return 0;
},

/**
 * @method setInsetLeft
 * @param {float} arg0
 */
setInsetLeft : function (
float 
)
{
},

/**
 * @method initWithSpriteFrame
* @param {cc.SpriteFrame|cc.SpriteFrame} spriteframe
* @param {rect_object} rect
* @return {bool|bool}
*/
initWithSpriteFrame : function(
spriteframe,
rect 
)
{
    return false;
},

/**
 * @method getPreferredSize
 * @return {size_object}
 */
getPreferredSize : function (
)
{
    return cc.Size;
},

/**
 * @method setCapInsets
 * @param {rect_object} arg0
 */
setCapInsets : function (
rect 
)
{
},

/**
 * @method isFlippedY
 * @return {bool}
 */
isFlippedY : function (
)
{
    return false;
},

/**
 * @method getInsetLeft
 * @return {float}
 */
getInsetLeft : function (
)
{
    return 0;
},

/**
 * @method setInsetRight
 * @param {float} arg0
 */
setInsetRight : function (
float 
)
{
},

/**
 * @method create
* @param {String|rect_object|String|String} str
* @param {rect_object|String|rect_object} rect
* @param {rect_object} rect
* @return {ccui.Scale9Sprite|ccui.Scale9Sprite|ccui.Scale9Sprite|ccui.Scale9Sprite|ccui.Scale9Sprite}
*/
create : function(
str,
rect,
rect 
)
{
    return ccui.Scale9Sprite;
},

/**
 * @method createWithSpriteFrameName
* @param {String|String} str
* @param {rect_object} rect
* @return {ccui.Scale9Sprite|ccui.Scale9Sprite}
*/
createWithSpriteFrameName : function(
str,
rect 
)
{
    return ccui.Scale9Sprite;
},

/**
 * @method createWithSpriteFrame
* @param {cc.SpriteFrame|cc.SpriteFrame} spriteframe
* @param {rect_object} rect
* @return {ccui.Scale9Sprite|ccui.Scale9Sprite}
*/
createWithSpriteFrame : function(
spriteframe,
rect 
)
{
    return ccui.Scale9Sprite;
},

/**
 * @method Scale9Sprite
 * @constructor
 */
Scale9Sprite : function (
)
{
},

};

/**
 * @class EditBox
 */
ccui.EditBox = {

/**
 * @method getText
 * @return {char}
 */
getText : function (
)
{
    return 0;
},

/**
 * @method setFontSize
 * @param {int} arg0
 */
setFontSize : function (
int 
)
{
},

/**
 * @method setPlaceholderFontName
 * @param {char} arg0
 */
setPlaceholderFontName : function (
char 
)
{
},

/**
 * @method getPlaceHolder
 * @return {char}
 */
getPlaceHolder : function (
)
{
    return 0;
},

/**
 * @method setFontName
 * @param {char} arg0
 */
setFontName : function (
char 
)
{
},

/**
 * @method setText
 * @param {char} arg0
 */
setText : function (
char 
)
{
},

/**
 * @method setPlaceholderFontSize
 * @param {int} arg0
 */
setPlaceholderFontSize : function (
int 
)
{
},

/**
 * @method setInputMode
 * @param {ccui.EditBox::InputMode} arg0
 */
setInputMode : function (
inputmode 
)
{
},

/**
 * @method setPlaceholderFontColor
* @param {color4b_object|color3b_object} color4b
*/
setPlaceholderFontColor : function(
color3b 
)
{
},

/**
 * @method setFontColor
* @param {color4b_object|color3b_object} color4b
*/
setFontColor : function(
color3b 
)
{
},

/**
 * @method setPlaceholderFont
 * @param {char} arg0
 * @param {int} arg1
 */
setPlaceholderFont : function (
char, 
int 
)
{
},

/**
 * @method initWithSizeAndBackgroundSprite
* @param {size_object|size_object} size
* @param {ccui.Scale9Sprite|String} scale9sprite
* @param {ccui.Widget::TextureResType} texturerestype
* @return {bool|bool}
*/
initWithSizeAndBackgroundSprite : function(
size,
str,
texturerestype 
)
{
    return false;
},

/**
 * @method setPlaceHolder
 * @param {char} arg0
 */
setPlaceHolder : function (
char 
)
{
},

/**
 * @method setReturnType
 * @param {ccui.EditBox::KeyboardReturnType} arg0
 */
setReturnType : function (
keyboardreturntype 
)
{
},

/**
 * @method setInputFlag
 * @param {ccui.EditBox::InputFlag} arg0
 */
setInputFlag : function (
inputflag 
)
{
},

/**
 * @method getMaxLength
 * @return {int}
 */
getMaxLength : function (
)
{
    return 0;
},

/**
 * @method setMaxLength
 * @param {int} arg0
 */
setMaxLength : function (
int 
)
{
},

/**
 * @method setFont
 * @param {char} arg0
 * @param {int} arg1
 */
setFont : function (
char, 
int 
)
{
},

/**
 * @method create
* @param {size_object|size_object} size
* @param {String|ccui.Scale9Sprite} str
* @param {ccui.Widget::TextureResType|ccui.Scale9Sprite} texturerestype
* @param {ccui.Scale9Sprite} scale9sprite
* @return {ccui.EditBox|ccui.EditBox}
*/
create : function(
size,
scale9sprite,
scale9sprite,
scale9sprite 
)
{
    return ccui.EditBox;
},

/**
 * @method EditBox
 * @constructor
 */
EditBox : function (
)
{
},

};

/**
 * @class LayoutComponent
 */
ccui.LayoutComponent = {

/**
 * @method setStretchWidthEnabled
 * @param {bool} arg0
 */
setStretchWidthEnabled : function (
bool 
)
{
},

/**
 * @method setPercentWidth
 * @param {float} arg0
 */
setPercentWidth : function (
float 
)
{
},

/**
 * @method getAnchorPosition
 * @return {vec2_object}
 */
getAnchorPosition : function (
)
{
    return cc.Vec2;
},

/**
 * @method setPositionPercentXEnabled
 * @param {bool} arg0
 */
setPositionPercentXEnabled : function (
bool 
)
{
},

/**
 * @method setStretchHeightEnabled
 * @param {bool} arg0
 */
setStretchHeightEnabled : function (
bool 
)
{
},

/**
 * @method setActiveEnabled
 * @param {bool} arg0
 */
setActiveEnabled : function (
bool 
)
{
},

/**
 * @method getRightMargin
 * @return {float}
 */
getRightMargin : function (
)
{
    return 0;
},

/**
 * @method getSize
 * @return {size_object}
 */
getSize : function (
)
{
    return cc.Size;
},

/**
 * @method setAnchorPosition
 * @param {vec2_object} arg0
 */
setAnchorPosition : function (
vec2 
)
{
},

/**
 * @method refreshLayout
 */
refreshLayout : function (
)
{
},

/**
 * @method isPercentWidthEnabled
 * @return {bool}
 */
isPercentWidthEnabled : function (
)
{
    return false;
},

/**
 * @method setVerticalEdge
 * @param {ccui.LayoutComponent::VerticalEdge} arg0
 */
setVerticalEdge : function (
verticaledge 
)
{
},

/**
 * @method getTopMargin
 * @return {float}
 */
getTopMargin : function (
)
{
    return 0;
},

/**
 * @method setSizeWidth
 * @param {float} arg0
 */
setSizeWidth : function (
float 
)
{
},

/**
 * @method getPercentContentSize
 * @return {vec2_object}
 */
getPercentContentSize : function (
)
{
    return cc.Vec2;
},

/**
 * @method getVerticalEdge
 * @return {ccui.LayoutComponent::VerticalEdge}
 */
getVerticalEdge : function (
)
{
    return 0;
},

/**
 * @method setPercentWidthEnabled
 * @param {bool} arg0
 */
setPercentWidthEnabled : function (
bool 
)
{
},

/**
 * @method isStretchWidthEnabled
 * @return {bool}
 */
isStretchWidthEnabled : function (
)
{
    return false;
},

/**
 * @method setLeftMargin
 * @param {float} arg0
 */
setLeftMargin : function (
float 
)
{
},

/**
 * @method getSizeWidth
 * @return {float}
 */
getSizeWidth : function (
)
{
    return 0;
},

/**
 * @method setPositionPercentYEnabled
 * @param {bool} arg0
 */
setPositionPercentYEnabled : function (
bool 
)
{
},

/**
 * @method getSizeHeight
 * @return {float}
 */
getSizeHeight : function (
)
{
    return 0;
},

/**
 * @method getPositionPercentY
 * @return {float}
 */
getPositionPercentY : function (
)
{
    return 0;
},

/**
 * @method getPositionPercentX
 * @return {float}
 */
getPositionPercentX : function (
)
{
    return 0;
},

/**
 * @method setTopMargin
 * @param {float} arg0
 */
setTopMargin : function (
float 
)
{
},

/**
 * @method getPercentHeight
 * @return {float}
 */
getPercentHeight : function (
)
{
    return 0;
},

/**
 * @method getUsingPercentContentSize
 * @return {bool}
 */
getUsingPercentContentSize : function (
)
{
    return false;
},

/**
 * @method setPositionPercentY
 * @param {float} arg0
 */
setPositionPercentY : function (
float 
)
{
},

/**
 * @method setPositionPercentX
 * @param {float} arg0
 */
setPositionPercentX : function (
float 
)
{
},

/**
 * @method setRightMargin
 * @param {float} arg0
 */
setRightMargin : function (
float 
)
{
},

/**
 * @method isPositionPercentYEnabled
 * @return {bool}
 */
isPositionPercentYEnabled : function (
)
{
    return false;
},

/**
 * @method setPercentHeight
 * @param {float} arg0
 */
setPercentHeight : function (
float 
)
{
},

/**
 * @method setPercentOnlyEnabled
 * @param {bool} arg0
 */
setPercentOnlyEnabled : function (
bool 
)
{
},

/**
 * @method setHorizontalEdge
 * @param {ccui.LayoutComponent::HorizontalEdge} arg0
 */
setHorizontalEdge : function (
horizontaledge 
)
{
},

/**
 * @method setPosition
 * @param {vec2_object} arg0
 */
setPosition : function (
vec2 
)
{
},

/**
 * @method setUsingPercentContentSize
 * @param {bool} arg0
 */
setUsingPercentContentSize : function (
bool 
)
{
},

/**
 * @method getLeftMargin
 * @return {float}
 */
getLeftMargin : function (
)
{
    return 0;
},

/**
 * @method getPosition
 * @return {vec2_object}
 */
getPosition : function (
)
{
    return cc.Vec2;
},

/**
 * @method setSizeHeight
 * @param {float} arg0
 */
setSizeHeight : function (
float 
)
{
},

/**
 * @method isPositionPercentXEnabled
 * @return {bool}
 */
isPositionPercentXEnabled : function (
)
{
    return false;
},

/**
 * @method getBottomMargin
 * @return {float}
 */
getBottomMargin : function (
)
{
    return 0;
},

/**
 * @method setPercentHeightEnabled
 * @param {bool} arg0
 */
setPercentHeightEnabled : function (
bool 
)
{
},

/**
 * @method setPercentContentSize
 * @param {vec2_object} arg0
 */
setPercentContentSize : function (
vec2 
)
{
},

/**
 * @method isPercentHeightEnabled
 * @return {bool}
 */
isPercentHeightEnabled : function (
)
{
    return false;
},

/**
 * @method getPercentWidth
 * @return {float}
 */
getPercentWidth : function (
)
{
    return 0;
},

/**
 * @method getHorizontalEdge
 * @return {ccui.LayoutComponent::HorizontalEdge}
 */
getHorizontalEdge : function (
)
{
    return 0;
},

/**
 * @method isStretchHeightEnabled
 * @return {bool}
 */
isStretchHeightEnabled : function (
)
{
    return false;
},

/**
 * @method setBottomMargin
 * @param {float} arg0
 */
setBottomMargin : function (
float 
)
{
},

/**
 * @method setSize
 * @param {size_object} arg0
 */
setSize : function (
size 
)
{
},

/**
 * @method create
 * @return {ccui.LayoutComponent}
 */
create : function (
)
{
    return ccui.LayoutComponent;
},

/**
 * @method bindLayoutComponent
 * @param {cc.Node} arg0
 * @return {ccui.LayoutComponent}
 */
bindLayoutComponent : function (
node 
)
{
    return ccui.LayoutComponent;
},

/**
 * @method LayoutComponent
 * @constructor
 */
LayoutComponent : function (
)
{
},

};

/**
 * @class TabHeader
 */
ccui.TabHeader = {

/**
 * @method getIndexInTabControl
 * @return {int}
 */
getIndexInTabControl : function (
)
{
    return 0;
},

/**
 * @method getTitleText
 * @return {String}
 */
getTitleText : function (
)
{
    return ;
},

/**
 * @method setTitleFontSize
 * @param {float} arg0
 */
setTitleFontSize : function (
float 
)
{
},

/**
 * @method setTitleFontName
 * @param {String} arg0
 */
setTitleFontName : function (
str 
)
{
},

/**
 * @method getTitleFontSize
 * @return {float}
 */
getTitleFontSize : function (
)
{
    return 0;
},

/**
 * @method getTitleFontName
 * @return {String}
 */
getTitleFontName : function (
)
{
    return ;
},

/**
 * @method getTitleColor
 * @return {color4b_object}
 */
getTitleColor : function (
)
{
    return cc.Color4B;
},

/**
 * @method getTitleRenderer
 * @return {cc.Label}
 */
getTitleRenderer : function (
)
{
    return cc.Label;
},

/**
 * @method setTitleText
 * @param {String} arg0
 */
setTitleText : function (
str 
)
{
},

/**
 * @method setTitleColor
 * @param {color4b_object} arg0
 */
setTitleColor : function (
color4b 
)
{
},

/**
 * @method create
* @param {String|String} str
* @param {String|String} str
* @param {String|String} str
* @param {ccui.Widget::TextureResType|String} texturerestype
* @param {String} str
* @param {String} str
* @param {ccui.Widget::TextureResType} texturerestype
* @return {ccui.TabHeader|ccui.TabHeader|ccui.TabHeader}
*/
create : function(
str,
str,
str,
str,
str,
str,
texturerestype 
)
{
    return ccui.TabHeader;
},

};

/**
 * @class TabControl
 */
ccui.TabControl = {

/**
 * @method setHeaderWidth
 * @param {float} arg0
 */
setHeaderWidth : function (
float 
)
{
},

/**
 * @method removeTab
 * @param {int} arg0
 */
removeTab : function (
int 
)
{
},

/**
 * @method getTabCount
 * @return {unsigned long}
 */
getTabCount : function (
)
{
    return 0;
},

/**
 * @method getHeaderDockPlace
 * @return {ccui.TabControl::Dock}
 */
getHeaderDockPlace : function (
)
{
    return 0;
},

/**
 * @method getSelectedTabIndex
 * @return {int}
 */
getSelectedTabIndex : function (
)
{
    return 0;
},

/**
 * @method insertTab
 * @param {int} arg0
 * @param {ccui.TabHeader} arg1
 * @param {ccui.Layout} arg2
 */
insertTab : function (
int, 
tabheader, 
layout 
)
{
},

/**
 * @method ignoreHeadersTextureSize
 * @param {bool} arg0
 */
ignoreHeadersTextureSize : function (
bool 
)
{
},

/**
 * @method getHeaderWidth
 * @return {float}
 */
getHeaderWidth : function (
)
{
    return 0;
},

/**
 * @method setHeaderDockPlace
 * @param {ccui.TabControl::Dock} arg0
 */
setHeaderDockPlace : function (
dock 
)
{
},

/**
 * @method setSelectTab
* @param {ccui.TabHeader|int} tabheader
*/
setSelectTab : function(
int 
)
{
},

/**
 * @method getTabHeader
 * @param {int} arg0
 * @return {ccui.TabHeader}
 */
getTabHeader : function (
int 
)
{
    return ccui.TabHeader;
},

/**
 * @method isIgnoreHeadersTextureSize
 * @return {bool}
 */
isIgnoreHeadersTextureSize : function (
)
{
    return false;
},

/**
 * @method setTabChangedEventListener
 * @param {function} arg0
 */
setTabChangedEventListener : function (
func 
)
{
},

/**
 * @method setHeaderSelectedZoom
 * @param {float} arg0
 */
setHeaderSelectedZoom : function (
float 
)
{
},

/**
 * @method setHeaderHeight
 * @param {float} arg0
 */
setHeaderHeight : function (
float 
)
{
},

/**
 * @method indexOfTabHeader
 * @param {ccui.TabHeader} arg0
 * @return {int}
 */
indexOfTabHeader : function (
tabheader 
)
{
    return 0;
},

/**
 * @method getTabContainer
 * @param {int} arg0
 * @return {ccui.Layout}
 */
getTabContainer : function (
int 
)
{
    return ccui.Layout;
},

/**
 * @method getHeaderSelectedZoom
 * @return {float}
 */
getHeaderSelectedZoom : function (
)
{
    return 0;
},

/**
 * @method getHeaderHeight
 * @return {int}
 */
getHeaderHeight : function (
)
{
    return 0;
},

/**
 * @method create
 * @return {ccui.TabControl}
 */
create : function (
)
{
    return ccui.TabControl;
},

};

/**
 * @class ScrollViewBar
 */
ccui.ScrollViewBar = {

/**
 * @method setAutoHideEnabled
 * @param {bool} arg0
 */
setAutoHideEnabled : function (
bool 
)
{
},

/**
 * @method onScrolled
 * @param {vec2_object} arg0
 */
onScrolled : function (
vec2 
)
{
},

/**
 * @method isAutoHideEnabled
 * @return {bool}
 */
isAutoHideEnabled : function (
)
{
    return false;
},

/**
 * @method setAutoHideTime
 * @param {float} arg0
 */
setAutoHideTime : function (
float 
)
{
},

/**
 * @method getWidth
 * @return {float}
 */
getWidth : function (
)
{
    return 0;
},

/**
 * @method getPositionFromCorner
 * @return {vec2_object}
 */
getPositionFromCorner : function (
)
{
    return cc.Vec2;
},

/**
 * @method setPositionFromCorner
 * @param {vec2_object} arg0
 */
setPositionFromCorner : function (
vec2 
)
{
},

/**
 * @method getAutoHideTime
 * @return {float}
 */
getAutoHideTime : function (
)
{
    return 0;
},

/**
 * @method setWidth
 * @param {float} arg0
 */
setWidth : function (
float 
)
{
},

/**
 * @method create
 * @param {ccui.ScrollView} arg0
 * @param {ccui.ScrollView::Direction} arg1
 * @return {ccui.ScrollViewBar}
 */
create : function (
scrollview, 
direction 
)
{
    return ccui.ScrollViewBar;
},

/**
 * @method ScrollViewBar
 * @constructor
 * @param {ccui.ScrollView} arg0
 * @param {ccui.ScrollView::Direction} arg1
 */
ScrollViewBar : function (
scrollview, 
direction 
)
{
},

};
