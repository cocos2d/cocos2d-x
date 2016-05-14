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
 * @param {bool} arg0
 */
setEnabled : function (
bool 
)
{
},

/**
 * @method getState
 * @return {cc.Control::State}
 */
getState : function (
)
{
    return 0;
},

/**
 * @method sendActionsForControlEvents
 * @param {cc.Control::EventType} arg0
 */
sendActionsForControlEvents : function (
eventtype 
)
{
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
 * @method isEnabled
 * @return {bool}
 */
isEnabled : function (
)
{
    return false;
},

/**
 * @method needsLayout
 */
needsLayout : function (
)
{
},

/**
 * @method hasVisibleParents
 * @return {bool}
 */
hasVisibleParents : function (
)
{
    return false;
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
 * @method isTouchInside
 * @param {cc.Touch} arg0
 * @return {bool}
 */
isTouchInside : function (
touch 
)
{
    return false;
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
 * @method getTouchLocation
 * @param {cc.Touch} arg0
 * @return {vec2_object}
 */
getTouchLocation : function (
touch 
)
{
    return cc.Vec2;
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
 * @method create
 * @return {cc.Control}
 */
create : function (
)
{
    return cc.Control;
},

/**
 * @method Control
 * @constructor
 */
Control : function (
)
{
},

};

/**
 * @class ControlButton
 */
cc.ControlButton = {

/**
 * @method isPushed
 * @return {bool}
 */
isPushed : function (
)
{
    return false;
},

/**
 * @method setTitleLabelForState
 * @param {cc.Node} arg0
 * @param {cc.Control::State} arg1
 */
setTitleLabelForState : function (
node, 
state 
)
{
},

/**
 * @method setAdjustBackgroundImage
 * @param {bool} arg0
 */
setAdjustBackgroundImage : function (
bool 
)
{
},

/**
 * @method setTitleForState
 * @param {String} arg0
 * @param {cc.Control::State} arg1
 */
setTitleForState : function (
str, 
state 
)
{
},

/**
 * @method setLabelAnchorPoint
 * @param {vec2_object} arg0
 */
setLabelAnchorPoint : function (
vec2 
)
{
},

/**
 * @method getLabelAnchorPoint
 * @return {vec2_object}
 */
getLabelAnchorPoint : function (
)
{
    return cc.Vec2;
},

/**
 * @method initWithBackgroundSprite
 * @param {ccui.Scale9Sprite} arg0
 * @return {bool}
 */
initWithBackgroundSprite : function (
scale9sprite 
)
{
    return false;
},

/**
 * @method getTitleTTFSizeForState
 * @param {cc.Control::State} arg0
 * @return {float}
 */
getTitleTTFSizeForState : function (
state 
)
{
    return 0;
},

/**
 * @method setTitleTTFForState
 * @param {String} arg0
 * @param {cc.Control::State} arg1
 */
setTitleTTFForState : function (
str, 
state 
)
{
},

/**
 * @method setTitleTTFSizeForState
 * @param {float} arg0
 * @param {cc.Control::State} arg1
 */
setTitleTTFSizeForState : function (
float, 
state 
)
{
},

/**
 * @method setTitleLabel
 * @param {cc.Node} arg0
 */
setTitleLabel : function (
node 
)
{
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
 * @method getCurrentTitleColor
 * @return {color3b_object}
 */
getCurrentTitleColor : function (
)
{
    return cc.Color3B;
},

/**
 * @method setZoomOnTouchDown
 * @param {bool} arg0
 */
setZoomOnTouchDown : function (
bool 
)
{
},

/**
 * @method setBackgroundSprite
 * @param {ccui.Scale9Sprite} arg0
 */
setBackgroundSprite : function (
scale9sprite 
)
{
},

/**
 * @method getBackgroundSpriteForState
 * @param {cc.Control::State} arg0
 * @return {ccui.Scale9Sprite}
 */
getBackgroundSpriteForState : function (
state 
)
{
    return ccui.Scale9Sprite;
},

/**
 * @method getHorizontalOrigin
 * @return {int}
 */
getHorizontalOrigin : function (
)
{
    return 0;
},

/**
 * @method initWithTitleAndFontNameAndFontSize
 * @param {String} arg0
 * @param {String} arg1
 * @param {float} arg2
 * @return {bool}
 */
initWithTitleAndFontNameAndFontSize : function (
str, 
str, 
float 
)
{
    return false;
},

/**
 * @method setTitleBMFontForState
 * @param {String} arg0
 * @param {cc.Control::State} arg1
 */
setTitleBMFontForState : function (
str, 
state 
)
{
},

/**
 * @method getScaleRatio
 * @return {float}
 */
getScaleRatio : function (
)
{
    return 0;
},

/**
 * @method getTitleTTFForState
 * @param {cc.Control::State} arg0
 * @return {String}
 */
getTitleTTFForState : function (
state 
)
{
    return ;
},

/**
 * @method getBackgroundSprite
 * @return {ccui.Scale9Sprite}
 */
getBackgroundSprite : function (
)
{
    return ccui.Scale9Sprite;
},

/**
 * @method getTitleColorForState
 * @param {cc.Control::State} arg0
 * @return {color3b_object}
 */
getTitleColorForState : function (
state 
)
{
    return cc.Color3B;
},

/**
 * @method setTitleColorForState
 * @param {color3b_object} arg0
 * @param {cc.Control::State} arg1
 */
setTitleColorForState : function (
color3b, 
state 
)
{
},

/**
 * @method doesAdjustBackgroundImage
 * @return {bool}
 */
doesAdjustBackgroundImage : function (
)
{
    return false;
},

/**
 * @method setBackgroundSpriteFrameForState
 * @param {cc.SpriteFrame} arg0
 * @param {cc.Control::State} arg1
 */
setBackgroundSpriteFrameForState : function (
spriteframe, 
state 
)
{
},

/**
 * @method setBackgroundSpriteForState
 * @param {ccui.Scale9Sprite} arg0
 * @param {cc.Control::State} arg1
 */
setBackgroundSpriteForState : function (
scale9sprite, 
state 
)
{
},

/**
 * @method setScaleRatio
 * @param {float} arg0
 */
setScaleRatio : function (
float 
)
{
},

/**
 * @method getTitleBMFontForState
 * @param {cc.Control::State} arg0
 * @return {String}
 */
getTitleBMFontForState : function (
state 
)
{
    return ;
},

/**
 * @method getTitleLabel
 * @return {cc.Node}
 */
getTitleLabel : function (
)
{
    return cc.Node;
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
 * @method getVerticalMargin
 * @return {int}
 */
getVerticalMargin : function (
)
{
    return 0;
},

/**
 * @method getTitleLabelForState
 * @param {cc.Control::State} arg0
 * @return {cc.Node}
 */
getTitleLabelForState : function (
state 
)
{
    return cc.Node;
},

/**
 * @method setMargins
 * @param {int} arg0
 * @param {int} arg1
 */
setMargins : function (
int, 
int 
)
{
},

/**
 * @method getCurrentTitle
* @return {String|String}
*/
getCurrentTitle : function(
)
{
    return ;
},

/**
 * @method initWithLabelAndBackgroundSprite
 * @param {cc.Node} arg0
 * @param {ccui.Scale9Sprite} arg1
 * @param {bool} arg2
 * @return {bool}
 */
initWithLabelAndBackgroundSprite : function (
node, 
scale9sprite, 
bool 
)
{
    return false;
},

/**
 * @method getZoomOnTouchDown
 * @return {bool}
 */
getZoomOnTouchDown : function (
)
{
    return false;
},

/**
 * @method getTitleForState
 * @param {cc.Control::State} arg0
 * @return {String}
 */
getTitleForState : function (
state 
)
{
    return ;
},

/**
 * @method create
* @param {ccui.Scale9Sprite|cc.Node|String|cc.Node} scale9sprite
* @param {ccui.Scale9Sprite|String|ccui.Scale9Sprite} scale9sprite
* @param {float|bool} float
* @return {cc.ControlButton|cc.ControlButton|cc.ControlButton|cc.ControlButton|cc.ControlButton}
*/
create : function(
node,
scale9sprite,
bool 
)
{
    return cc.ControlButton;
},

/**
 * @method ControlButton
 * @constructor
 */
ControlButton : function (
)
{
},

};

/**
 * @class ControlHuePicker
 */
cc.ControlHuePicker = {

/**
 * @method initWithTargetAndPos
 * @param {cc.Node} arg0
 * @param {vec2_object} arg1
 * @return {bool}
 */
initWithTargetAndPos : function (
node, 
vec2 
)
{
    return false;
},

/**
 * @method setHue
 * @param {float} arg0
 */
setHue : function (
float 
)
{
},

/**
 * @method getStartPos
 * @return {vec2_object}
 */
getStartPos : function (
)
{
    return cc.Vec2;
},

/**
 * @method getHue
 * @return {float}
 */
getHue : function (
)
{
    return 0;
},

/**
 * @method getSlider
 * @return {cc.Sprite}
 */
getSlider : function (
)
{
    return cc.Sprite;
},

/**
 * @method setBackground
 * @param {cc.Sprite} arg0
 */
setBackground : function (
sprite 
)
{
},

/**
 * @method setHuePercentage
 * @param {float} arg0
 */
setHuePercentage : function (
float 
)
{
},

/**
 * @method getBackground
 * @return {cc.Sprite}
 */
getBackground : function (
)
{
    return cc.Sprite;
},

/**
 * @method getHuePercentage
 * @return {float}
 */
getHuePercentage : function (
)
{
    return 0;
},

/**
 * @method setSlider
 * @param {cc.Sprite} arg0
 */
setSlider : function (
sprite 
)
{
},

/**
 * @method create
 * @param {cc.Node} arg0
 * @param {vec2_object} arg1
 * @return {cc.ControlHuePicker}
 */
create : function (
node, 
vec2 
)
{
    return cc.ControlHuePicker;
},

/**
 * @method ControlHuePicker
 * @constructor
 */
ControlHuePicker : function (
)
{
},

};

/**
 * @class ControlSaturationBrightnessPicker
 */
cc.ControlSaturationBrightnessPicker = {

/**
 * @method getShadow
 * @return {cc.Sprite}
 */
getShadow : function (
)
{
    return cc.Sprite;
},

/**
 * @method initWithTargetAndPos
 * @param {cc.Node} arg0
 * @param {vec2_object} arg1
 * @return {bool}
 */
initWithTargetAndPos : function (
node, 
vec2 
)
{
    return false;
},

/**
 * @method getStartPos
 * @return {vec2_object}
 */
getStartPos : function (
)
{
    return cc.Vec2;
},

/**
 * @method getOverlay
 * @return {cc.Sprite}
 */
getOverlay : function (
)
{
    return cc.Sprite;
},

/**
 * @method getSlider
 * @return {cc.Sprite}
 */
getSlider : function (
)
{
    return cc.Sprite;
},

/**
 * @method getBackground
 * @return {cc.Sprite}
 */
getBackground : function (
)
{
    return cc.Sprite;
},

/**
 * @method getSaturation
 * @return {float}
 */
getSaturation : function (
)
{
    return 0;
},

/**
 * @method getBrightness
 * @return {float}
 */
getBrightness : function (
)
{
    return 0;
},

/**
 * @method create
 * @param {cc.Node} arg0
 * @param {vec2_object} arg1
 * @return {cc.ControlSaturationBrightnessPicker}
 */
create : function (
node, 
vec2 
)
{
    return cc.ControlSaturationBrightnessPicker;
},

/**
 * @method ControlSaturationBrightnessPicker
 * @constructor
 */
ControlSaturationBrightnessPicker : function (
)
{
},

};

/**
 * @class ControlColourPicker
 */
cc.ControlColourPicker = {

/**
 * @method hueSliderValueChanged
 * @param {cc.Ref} arg0
 * @param {cc.Control::EventType} arg1
 */
hueSliderValueChanged : function (
ref, 
eventtype 
)
{
},

/**
 * @method getHuePicker
 * @return {cc.ControlHuePicker}
 */
getHuePicker : function (
)
{
    return cc.ControlHuePicker;
},

/**
 * @method getcolourPicker
 * @return {cc.ControlSaturationBrightnessPicker}
 */
getcolourPicker : function (
)
{
    return cc.ControlSaturationBrightnessPicker;
},

/**
 * @method setBackground
 * @param {cc.Sprite} arg0
 */
setBackground : function (
sprite 
)
{
},

/**
 * @method setcolourPicker
 * @param {cc.ControlSaturationBrightnessPicker} arg0
 */
setcolourPicker : function (
controlsaturationbrightnesspicker 
)
{
},

/**
 * @method colourSliderValueChanged
 * @param {cc.Ref} arg0
 * @param {cc.Control::EventType} arg1
 */
colourSliderValueChanged : function (
ref, 
eventtype 
)
{
},

/**
 * @method setHuePicker
 * @param {cc.ControlHuePicker} arg0
 */
setHuePicker : function (
controlhuepicker 
)
{
},

/**
 * @method getBackground
 * @return {cc.Sprite}
 */
getBackground : function (
)
{
    return cc.Sprite;
},

/**
 * @method create
 * @return {cc.ControlColourPicker}
 */
create : function (
)
{
    return cc.ControlColourPicker;
},

/**
 * @method ControlColourPicker
 * @constructor
 */
ControlColourPicker : function (
)
{
},

};

/**
 * @class ControlPotentiometer
 */
cc.ControlPotentiometer = {

/**
 * @method setPreviousLocation
 * @param {vec2_object} arg0
 */
setPreviousLocation : function (
vec2 
)
{
},

/**
 * @method setValue
 * @param {float} arg0
 */
setValue : function (
float 
)
{
},

/**
 * @method getProgressTimer
 * @return {cc.ProgressTimer}
 */
getProgressTimer : function (
)
{
    return cc.ProgressTimer;
},

/**
 * @method getMaximumValue
 * @return {float}
 */
getMaximumValue : function (
)
{
    return 0;
},

/**
 * @method angleInDegreesBetweenLineFromPoint_toPoint_toLineFromPoint_toPoint
 * @param {vec2_object} arg0
 * @param {vec2_object} arg1
 * @param {vec2_object} arg2
 * @param {vec2_object} arg3
 * @return {float}
 */
angleInDegreesBetweenLineFromPoint_toPoint_toLineFromPoint_toPoint : function (
vec2, 
vec2, 
vec2, 
vec2 
)
{
    return 0;
},

/**
 * @method potentiometerBegan
 * @param {vec2_object} arg0
 */
potentiometerBegan : function (
vec2 
)
{
},

/**
 * @method setMaximumValue
 * @param {float} arg0
 */
setMaximumValue : function (
float 
)
{
},

/**
 * @method getMinimumValue
 * @return {float}
 */
getMinimumValue : function (
)
{
    return 0;
},

/**
 * @method setThumbSprite
 * @param {cc.Sprite} arg0
 */
setThumbSprite : function (
sprite 
)
{
},

/**
 * @method getValue
 * @return {float}
 */
getValue : function (
)
{
    return 0;
},

/**
 * @method getPreviousLocation
 * @return {vec2_object}
 */
getPreviousLocation : function (
)
{
    return cc.Vec2;
},

/**
 * @method distanceBetweenPointAndPoint
 * @param {vec2_object} arg0
 * @param {vec2_object} arg1
 * @return {float}
 */
distanceBetweenPointAndPoint : function (
vec2, 
vec2 
)
{
    return 0;
},

/**
 * @method potentiometerEnded
 * @param {vec2_object} arg0
 */
potentiometerEnded : function (
vec2 
)
{
},

/**
 * @method setProgressTimer
 * @param {cc.ProgressTimer} arg0
 */
setProgressTimer : function (
progresstimer 
)
{
},

/**
 * @method setMinimumValue
 * @param {float} arg0
 */
setMinimumValue : function (
float 
)
{
},

/**
 * @method getThumbSprite
 * @return {cc.Sprite}
 */
getThumbSprite : function (
)
{
    return cc.Sprite;
},

/**
 * @method initWithTrackSprite_ProgressTimer_ThumbSprite
 * @param {cc.Sprite} arg0
 * @param {cc.ProgressTimer} arg1
 * @param {cc.Sprite} arg2
 * @return {bool}
 */
initWithTrackSprite_ProgressTimer_ThumbSprite : function (
sprite, 
progresstimer, 
sprite 
)
{
    return false;
},

/**
 * @method potentiometerMoved
 * @param {vec2_object} arg0
 */
potentiometerMoved : function (
vec2 
)
{
},

/**
 * @method create
 * @param {char} arg0
 * @param {char} arg1
 * @param {char} arg2
 * @return {cc.ControlPotentiometer}
 */
create : function (
char, 
char, 
char 
)
{
    return cc.ControlPotentiometer;
},

/**
 * @method ControlPotentiometer
 * @constructor
 */
ControlPotentiometer : function (
)
{
},

};

/**
 * @class ControlSlider
 */
cc.ControlSlider = {

/**
 * @method setBackgroundSprite
 * @param {cc.Sprite} arg0
 */
setBackgroundSprite : function (
sprite 
)
{
},

/**
 * @method getMaximumAllowedValue
 * @return {float}
 */
getMaximumAllowedValue : function (
)
{
    return 0;
},

/**
 * @method initWithSprites
* @param {cc.Sprite|cc.Sprite} sprite
* @param {cc.Sprite|cc.Sprite} sprite
* @param {cc.Sprite|cc.Sprite} sprite
* @param {cc.Sprite} sprite
* @return {bool|bool}
*/
initWithSprites : function(
sprite,
sprite,
sprite,
sprite 
)
{
    return false;
},

/**
 * @method getMinimumAllowedValue
 * @return {float}
 */
getMinimumAllowedValue : function (
)
{
    return 0;
},

/**
 * @method getMaximumValue
 * @return {float}
 */
getMaximumValue : function (
)
{
    return 0;
},

/**
 * @method getSelectedThumbSprite
 * @return {cc.Sprite}
 */
getSelectedThumbSprite : function (
)
{
    return cc.Sprite;
},

/**
 * @method setProgressSprite
 * @param {cc.Sprite} arg0
 */
setProgressSprite : function (
sprite 
)
{
},

/**
 * @method setMaximumValue
 * @param {float} arg0
 */
setMaximumValue : function (
float 
)
{
},

/**
 * @method getMinimumValue
 * @return {float}
 */
getMinimumValue : function (
)
{
    return 0;
},

/**
 * @method setThumbSprite
 * @param {cc.Sprite} arg0
 */
setThumbSprite : function (
sprite 
)
{
},

/**
 * @method getValue
 * @return {float}
 */
getValue : function (
)
{
    return 0;
},

/**
 * @method getBackgroundSprite
 * @return {cc.Sprite}
 */
getBackgroundSprite : function (
)
{
    return cc.Sprite;
},

/**
 * @method getThumbSprite
 * @return {cc.Sprite}
 */
getThumbSprite : function (
)
{
    return cc.Sprite;
},

/**
 * @method setValue
 * @param {float} arg0
 */
setValue : function (
float 
)
{
},

/**
 * @method locationFromTouch
 * @param {cc.Touch} arg0
 * @return {vec2_object}
 */
locationFromTouch : function (
touch 
)
{
    return cc.Vec2;
},

/**
 * @method setMinimumValue
 * @param {float} arg0
 */
setMinimumValue : function (
float 
)
{
},

/**
 * @method setMinimumAllowedValue
 * @param {float} arg0
 */
setMinimumAllowedValue : function (
float 
)
{
},

/**
 * @method getProgressSprite
 * @return {cc.Sprite}
 */
getProgressSprite : function (
)
{
    return cc.Sprite;
},

/**
 * @method setSelectedThumbSprite
 * @param {cc.Sprite} arg0
 */
setSelectedThumbSprite : function (
sprite 
)
{
},

/**
 * @method setMaximumAllowedValue
 * @param {float} arg0
 */
setMaximumAllowedValue : function (
float 
)
{
},

/**
 * @method create
* @param {cc.Sprite|char|char|cc.Sprite} sprite
* @param {cc.Sprite|char|char|cc.Sprite} sprite
* @param {cc.Sprite|char|char|cc.Sprite} sprite
* @param {char|cc.Sprite} char
* @return {cc.ControlSlider|cc.ControlSlider|cc.ControlSlider|cc.ControlSlider}
*/
create : function(
sprite,
sprite,
sprite,
sprite 
)
{
    return cc.ControlSlider;
},

/**
 * @method ControlSlider
 * @constructor
 */
ControlSlider : function (
)
{
},

};

/**
 * @class ControlStepper
 */
cc.ControlStepper = {

/**
 * @method getMinusSprite
 * @return {cc.Sprite}
 */
getMinusSprite : function (
)
{
    return cc.Sprite;
},

/**
 * @method setValue
 * @param {double} arg0
 */
setValue : function (
double 
)
{
},

/**
 * @method setStepValue
 * @param {double} arg0
 */
setStepValue : function (
double 
)
{
},

/**
 * @method initWithMinusSpriteAndPlusSprite
 * @param {cc.Sprite} arg0
 * @param {cc.Sprite} arg1
 * @return {bool}
 */
initWithMinusSpriteAndPlusSprite : function (
sprite, 
sprite 
)
{
    return false;
},

/**
 * @method setValueWithSendingEvent
 * @param {double} arg0
 * @param {bool} arg1
 */
setValueWithSendingEvent : function (
double, 
bool 
)
{
},

/**
 * @method setMaximumValue
 * @param {double} arg0
 */
setMaximumValue : function (
double 
)
{
},

/**
 * @method getMinusLabel
 * @return {cc.Label}
 */
getMinusLabel : function (
)
{
    return cc.Label;
},

/**
 * @method getPlusLabel
 * @return {cc.Label}
 */
getPlusLabel : function (
)
{
    return cc.Label;
},

/**
 * @method setWraps
 * @param {bool} arg0
 */
setWraps : function (
bool 
)
{
},

/**
 * @method setMinusLabel
 * @param {cc.Label} arg0
 */
setMinusLabel : function (
label 
)
{
},

/**
 * @method startAutorepeat
 */
startAutorepeat : function (
)
{
},

/**
 * @method updateLayoutUsingTouchLocation
 * @param {vec2_object} arg0
 */
updateLayoutUsingTouchLocation : function (
vec2 
)
{
},

/**
 * @method isContinuous
 * @return {bool}
 */
isContinuous : function (
)
{
    return false;
},

/**
 * @method stopAutorepeat
 */
stopAutorepeat : function (
)
{
},

/**
 * @method setMinimumValue
 * @param {double} arg0
 */
setMinimumValue : function (
double 
)
{
},

/**
 * @method setPlusLabel
 * @param {cc.Label} arg0
 */
setPlusLabel : function (
label 
)
{
},

/**
 * @method getValue
 * @return {double}
 */
getValue : function (
)
{
    return 0;
},

/**
 * @method getPlusSprite
 * @return {cc.Sprite}
 */
getPlusSprite : function (
)
{
    return cc.Sprite;
},

/**
 * @method setPlusSprite
 * @param {cc.Sprite} arg0
 */
setPlusSprite : function (
sprite 
)
{
},

/**
 * @method setMinusSprite
 * @param {cc.Sprite} arg0
 */
setMinusSprite : function (
sprite 
)
{
},

/**
 * @method create
 * @param {cc.Sprite} arg0
 * @param {cc.Sprite} arg1
 * @return {cc.ControlStepper}
 */
create : function (
sprite, 
sprite 
)
{
    return cc.ControlStepper;
},

/**
 * @method ControlStepper
 * @constructor
 */
ControlStepper : function (
)
{
},

};

/**
 * @class ControlSwitch
 */
cc.ControlSwitch = {

/**
 * @method setOn
* @param {bool|bool} bool
* @param {bool} bool
*/
setOn : function(
bool,
bool 
)
{
},

/**
 * @method locationFromTouch
 * @param {cc.Touch} arg0
 * @return {vec2_object}
 */
locationFromTouch : function (
touch 
)
{
    return cc.Vec2;
},

/**
 * @method isOn
 * @return {bool}
 */
isOn : function (
)
{
    return false;
},

/**
 * @method initWithMaskSprite
* @param {cc.Sprite|cc.Sprite} sprite
* @param {cc.Sprite|cc.Sprite} sprite
* @param {cc.Sprite|cc.Sprite} sprite
* @param {cc.Sprite|cc.Sprite} sprite
* @param {cc.Label} label
* @param {cc.Label} label
* @return {bool|bool}
*/
initWithMaskSprite : function(
sprite,
sprite,
sprite,
sprite,
label,
label 
)
{
    return false;
},

/**
 * @method hasMoved
 * @return {bool}
 */
hasMoved : function (
)
{
    return false;
},

/**
 * @method create
* @param {cc.Sprite|cc.Sprite} sprite
* @param {cc.Sprite|cc.Sprite} sprite
* @param {cc.Sprite|cc.Sprite} sprite
* @param {cc.Sprite|cc.Sprite} sprite
* @param {cc.Label} label
* @param {cc.Label} label
* @return {cc.ControlSwitch|cc.ControlSwitch}
*/
create : function(
sprite,
sprite,
sprite,
sprite,
label,
label 
)
{
    return cc.ControlSwitch;
},

/**
 * @method ControlSwitch
 * @constructor
 */
ControlSwitch : function (
)
{
},

};

/**
 * @class ScrollView
 */
cc.ScrollView = {

/**
 * @method isClippingToBounds
 * @return {bool}
 */
isClippingToBounds : function (
)
{
    return false;
},

/**
 * @method setContainer
 * @param {cc.Node} arg0
 */
setContainer : function (
node 
)
{
},

/**
 * @method setContentOffsetInDuration
 * @param {vec2_object} arg0
 * @param {float} arg1
 */
setContentOffsetInDuration : function (
vec2, 
float 
)
{
},

/**
 * @method setZoomScaleInDuration
 * @param {float} arg0
 * @param {float} arg1
 */
setZoomScaleInDuration : function (
float, 
float 
)
{
},

/**
 * @method updateTweenAction
 * @param {float} arg0
 * @param {String} arg1
 */
updateTweenAction : function (
float, 
str 
)
{
},

/**
 * @method setMaxScale
 * @param {float} arg0
 */
setMaxScale : function (
float 
)
{
},

/**
 * @method hasVisibleParents
 * @return {bool}
 */
hasVisibleParents : function (
)
{
    return false;
},

/**
 * @method getDirection
 * @return {cc.ScrollView::Direction}
 */
getDirection : function (
)
{
    return 0;
},

/**
 * @method getContainer
 * @return {cc.Node}
 */
getContainer : function (
)
{
    return cc.Node;
},

/**
 * @method setMinScale
 * @param {float} arg0
 */
setMinScale : function (
float 
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
 * @method updateInset
 */
updateInset : function (
)
{
},

/**
 * @method initWithViewSize
 * @param {size_object} arg0
 * @param {cc.Node} arg1
 * @return {bool}
 */
initWithViewSize : function (
size, 
node 
)
{
    return false;
},

/**
 * @method pause
 * @param {cc.Ref} arg0
 */
pause : function (
ref 
)
{
},

/**
 * @method setDirection
 * @param {cc.ScrollView::Direction} arg0
 */
setDirection : function (
direction 
)
{
},

/**
 * @method stopAnimatedContentOffset
 */
stopAnimatedContentOffset : function (
)
{
},

/**
 * @method setContentOffset
 * @param {vec2_object} arg0
 * @param {bool} arg1
 */
setContentOffset : function (
vec2, 
bool 
)
{
},

/**
 * @method isDragging
 * @return {bool}
 */
isDragging : function (
)
{
    return false;
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
 * @method isBounceable
 * @return {bool}
 */
isBounceable : function (
)
{
    return false;
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
 * @method getContentOffset
 * @return {vec2_object}
 */
getContentOffset : function (
)
{
    return cc.Vec2;
},

/**
 * @method resume
 * @param {cc.Ref} arg0
 */
resume : function (
ref 
)
{
},

/**
 * @method setClippingToBounds
 * @param {bool} arg0
 */
setClippingToBounds : function (
bool 
)
{
},

/**
 * @method setViewSize
 * @param {size_object} arg0
 */
setViewSize : function (
size 
)
{
},

/**
 * @method getViewSize
 * @return {size_object}
 */
getViewSize : function (
)
{
    return cc.Size;
},

/**
 * @method maxContainerOffset
 * @return {vec2_object}
 */
maxContainerOffset : function (
)
{
    return cc.Vec2;
},

/**
 * @method setBounceable
 * @param {bool} arg0
 */
setBounceable : function (
bool 
)
{
},

/**
 * @method isTouchMoved
 * @return {bool}
 */
isTouchMoved : function (
)
{
    return false;
},

/**
 * @method isNodeVisible
 * @param {cc.Node} arg0
 * @return {bool}
 */
isNodeVisible : function (
node 
)
{
    return false;
},

/**
 * @method minContainerOffset
 * @return {vec2_object}
 */
minContainerOffset : function (
)
{
    return cc.Vec2;
},

/**
 * @method setZoomScale
* @param {float|float} float
* @param {bool} bool
*/
setZoomScale : function(
float,
bool 
)
{
},

/**
 * @method create
* @param {size_object} size
* @param {cc.Node} node
* @return {cc.ScrollView|cc.ScrollView}
*/
create : function(
size,
node 
)
{
    return cc.ScrollView;
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
 * @class TableViewCell
 */
cc.TableViewCell = {

/**
 * @method reset
 */
reset : function (
)
{
},

/**
 * @method getIdx
 * @return {long}
 */
getIdx : function (
)
{
    return 0;
},

/**
 * @method setIdx
 * @param {long} arg0
 */
setIdx : function (
long 
)
{
},

/**
 * @method create
 * @return {cc.TableViewCell}
 */
create : function (
)
{
    return cc.TableViewCell;
},

/**
 * @method TableViewCell
 * @constructor
 */
TableViewCell : function (
)
{
},

};

/**
 * @class TableView
 */
cc.TableView = {

/**
 * @method updateCellAtIndex
 * @param {long} arg0
 */
updateCellAtIndex : function (
long 
)
{
},

/**
 * @method setVerticalFillOrder
 * @param {cc.TableView::VerticalFillOrder} arg0
 */
setVerticalFillOrder : function (
verticalfillorder 
)
{
},

/**
 * @method scrollViewDidZoom
 * @param {cc.ScrollView} arg0
 */
scrollViewDidZoom : function (
scrollview 
)
{
},

/**
 * @method _updateContentSize
 */
_updateContentSize : function (
)
{
},

/**
 * @method getVerticalFillOrder
 * @return {cc.TableView::VerticalFillOrder}
 */
getVerticalFillOrder : function (
)
{
    return 0;
},

/**
 * @method removeCellAtIndex
 * @param {long} arg0
 */
removeCellAtIndex : function (
long 
)
{
},

/**
 * @method initWithViewSize
 * @param {size_object} arg0
 * @param {cc.Node} arg1
 * @return {bool}
 */
initWithViewSize : function (
size, 
node 
)
{
    return false;
},

/**
 * @method scrollViewDidScroll
 * @param {cc.ScrollView} arg0
 */
scrollViewDidScroll : function (
scrollview 
)
{
},

/**
 * @method reloadData
 */
reloadData : function (
)
{
},

/**
 * @method insertCellAtIndex
 * @param {long} arg0
 */
insertCellAtIndex : function (
long 
)
{
},

/**
 * @method cellAtIndex
 * @param {long} arg0
 * @return {cc.TableViewCell}
 */
cellAtIndex : function (
long 
)
{
    return cc.TableViewCell;
},

/**
 * @method dequeueCell
 * @return {cc.TableViewCell}
 */
dequeueCell : function (
)
{
    return cc.TableViewCell;
},

/**
 * @method TableView
 * @constructor
 */
TableView : function (
)
{
},

};

/**
 * @class EventAssetsManagerEx
 */
cc.EventAssetsManager = {

/**
 * @method getAssetsManagerEx
 * @return {cc.AssetsManagerEx}
 */
getAssetsManagerEx : function (
)
{
    return cc.AssetsManagerEx;
},

/**
 * @method getAssetId
 * @return {String}
 */
getAssetId : function (
)
{
    return ;
},

/**
 * @method getCURLECode
 * @return {int}
 */
getCURLECode : function (
)
{
    return 0;
},

/**
 * @method getMessage
 * @return {String}
 */
getMessage : function (
)
{
    return ;
},

/**
 * @method getCURLMCode
 * @return {int}
 */
getCURLMCode : function (
)
{
    return 0;
},

/**
 * @method getPercentByFile
 * @return {float}
 */
getPercentByFile : function (
)
{
    return 0;
},

/**
 * @method getEventCode
 * @return {cc.EventAssetsManagerEx::EventCode}
 */
getEventCode : function (
)
{
    return 0;
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
 * @method EventAssetsManagerEx
 * @constructor
 * @param {String} arg0
 * @param {cc.AssetsManagerEx} arg1
 * @param {cc.EventAssetsManagerEx::EventCode} arg2
 * @param {float} arg3
 * @param {float} arg4
 * @param {String} arg5
 * @param {String} arg6
 * @param {int} arg7
 * @param {int} arg8
 */
EventAssetsManagerEx : function (
str, 
assetsmanagerex, 
eventcode, 
float, 
float, 
str, 
str, 
int, 
int 
)
{
},

};

/**
 * @class Manifest
 */
cc.Manifest = {

/**
 * @method getManifestFileUrl
 * @return {String}
 */
getManifestFileUrl : function (
)
{
    return ;
},

/**
 * @method isVersionLoaded
 * @return {bool}
 */
isVersionLoaded : function (
)
{
    return false;
},

/**
 * @method isLoaded
 * @return {bool}
 */
isLoaded : function (
)
{
    return false;
},

/**
 * @method getPackageUrl
 * @return {String}
 */
getPackageUrl : function (
)
{
    return ;
},

/**
 * @method getVersion
 * @return {String}
 */
getVersion : function (
)
{
    return ;
},

/**
 * @method getVersionFileUrl
 * @return {String}
 */
getVersionFileUrl : function (
)
{
    return ;
},

/**
 * @method getSearchPaths
 * @return {Array}
 */
getSearchPaths : function (
)
{
    return new Array();
},

};

/**
 * @class AssetsManagerEx
 */
cc.AssetsManager = {

/**
 * @method getState
 * @return {cc.AssetsManagerEx::State}
 */
getState : function (
)
{
    return 0;
},

/**
 * @method checkUpdate
 */
checkUpdate : function (
)
{
},

/**
 * @method getStoragePath
 * @return {String}
 */
getStoragePath : function (
)
{
    return ;
},

/**
 * @method update
 */
update : function (
)
{
},

/**
 * @method getLocalManifest
 * @return {cc.Manifest}
 */
getLocalManifest : function (
)
{
    return cc.Manifest;
},

/**
 * @method getRemoteManifest
 * @return {cc.Manifest}
 */
getRemoteManifest : function (
)
{
    return cc.Manifest;
},

/**
 * @method downloadFailedAssets
 */
downloadFailedAssets : function (
)
{
},

/**
 * @method create
 * @param {String} arg0
 * @param {String} arg1
 * @return {cc.AssetsManagerEx}
 */
create : function (
str, 
str 
)
{
    return cc.AssetsManagerEx;
},

/**
 * @method AssetsManagerEx
 * @constructor
 * @param {String} arg0
 * @param {String} arg1
 */
AssetsManagerEx : function (
str, 
str 
)
{
},

};

/**
 * @class EventListenerAssetsManagerEx
 */
cc.EventListenerAssetsManager = {

/**
 * @method EventListenerAssetsManagerEx
 * @constructor
 */
EventListenerAssetsManagerEx : function (
)
{
},

};
