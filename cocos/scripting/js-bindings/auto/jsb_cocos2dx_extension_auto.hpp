#ifndef __cocos2dx_extension_h__
#define __cocos2dx_extension_h__

#include "jsapi.h"
#include "jsfriendapi.h"


extern JSClass  *jsb_cocos2d_extension_Control_class;
extern JSObject *jsb_cocos2d_extension_Control_prototype;

bool js_cocos2dx_extension_Control_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_extension_Control_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_extension_Control(JSContext *cx, JSObject *global);
void register_all_cocos2dx_extension(JSContext* cx, JSObject* obj);
bool js_cocos2dx_extension_Control_setEnabled(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_Control_getState(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_Control_sendActionsForControlEvents(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_Control_setSelected(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_Control_isEnabled(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_Control_needsLayout(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_Control_hasVisibleParents(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_Control_isSelected(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_Control_isTouchInside(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_Control_setHighlighted(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_Control_getTouchLocation(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_Control_isHighlighted(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_Control_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_Control_Control(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocos2d_extension_ControlButton_class;
extern JSObject *jsb_cocos2d_extension_ControlButton_prototype;

bool js_cocos2dx_extension_ControlButton_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_extension_ControlButton_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_extension_ControlButton(JSContext *cx, JSObject *global);
void register_all_cocos2dx_extension(JSContext* cx, JSObject* obj);
bool js_cocos2dx_extension_ControlButton_isPushed(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlButton_setSelected(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlButton_setTitleLabelForState(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlButton_setAdjustBackgroundImage(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlButton_setHighlighted(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlButton_setZoomOnTouchDown(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlButton_setTitleForState(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlButton_setLabelAnchorPoint(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlButton_getLabelAnchorPoint(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlButton_initWithBackgroundSprite(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlButton_getTitleTTFSizeForState(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlButton_setTitleTTFForState(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlButton_setTitleTTFSizeForState(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlButton_setTitleLabel(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlButton_setPreferredSize(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlButton_getCurrentTitleColor(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlButton_setEnabled(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlButton_setBackgroundSprite(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlButton_getBackgroundSpriteForState(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlButton_getHorizontalOrigin(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlButton_needsLayout(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlButton_initWithTitleAndFontNameAndFontSize(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlButton_getCurrentTitle(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlButton_getScaleRatio(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlButton_getTitleTTFForState(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlButton_getBackgroundSprite(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlButton_getTitleColorForState(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlButton_setTitleColorForState(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlButton_doesAdjustBackgroundImage(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlButton_setBackgroundSpriteFrameForState(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlButton_setBackgroundSpriteForState(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlButton_setScaleRatio(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlButton_initWithLabelAndBackgroundSprite(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlButton_getTitleLabel(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlButton_getPreferredSize(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlButton_getVerticalMargin(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlButton_getTitleLabelForState(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlButton_setMargins(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlButton_setTitleBMFontForState(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlButton_getTitleBMFontForState(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlButton_getZoomOnTouchDown(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlButton_getTitleForState(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlButton_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlButton_ControlButton(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocos2d_extension_ControlHuePicker_class;
extern JSObject *jsb_cocos2d_extension_ControlHuePicker_prototype;

bool js_cocos2dx_extension_ControlHuePicker_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_extension_ControlHuePicker_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_extension_ControlHuePicker(JSContext *cx, JSObject *global);
void register_all_cocos2dx_extension(JSContext* cx, JSObject* obj);
bool js_cocos2dx_extension_ControlHuePicker_setEnabled(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlHuePicker_initWithTargetAndPos(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlHuePicker_setHue(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlHuePicker_getStartPos(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlHuePicker_getHue(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlHuePicker_getSlider(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlHuePicker_setBackground(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlHuePicker_setHuePercentage(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlHuePicker_getBackground(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlHuePicker_getHuePercentage(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlHuePicker_setSlider(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlHuePicker_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlHuePicker_ControlHuePicker(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocos2d_extension_ControlSaturationBrightnessPicker_class;
extern JSObject *jsb_cocos2d_extension_ControlSaturationBrightnessPicker_prototype;

bool js_cocos2dx_extension_ControlSaturationBrightnessPicker_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_extension_ControlSaturationBrightnessPicker_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_extension_ControlSaturationBrightnessPicker(JSContext *cx, JSObject *global);
void register_all_cocos2dx_extension(JSContext* cx, JSObject* obj);
bool js_cocos2dx_extension_ControlSaturationBrightnessPicker_getShadow(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlSaturationBrightnessPicker_initWithTargetAndPos(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlSaturationBrightnessPicker_getStartPos(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlSaturationBrightnessPicker_getOverlay(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlSaturationBrightnessPicker_setEnabled(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlSaturationBrightnessPicker_getSlider(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlSaturationBrightnessPicker_getBackground(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlSaturationBrightnessPicker_getSaturation(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlSaturationBrightnessPicker_getBrightness(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlSaturationBrightnessPicker_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlSaturationBrightnessPicker_ControlSaturationBrightnessPicker(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocos2d_extension_ControlColourPicker_class;
extern JSObject *jsb_cocos2d_extension_ControlColourPicker_prototype;

bool js_cocos2dx_extension_ControlColourPicker_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_extension_ControlColourPicker_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_extension_ControlColourPicker(JSContext *cx, JSObject *global);
void register_all_cocos2dx_extension(JSContext* cx, JSObject* obj);
bool js_cocos2dx_extension_ControlColourPicker_setEnabled(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlColourPicker_getHuePicker(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlColourPicker_setColor(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlColourPicker_hueSliderValueChanged(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlColourPicker_getcolourPicker(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlColourPicker_setBackground(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlColourPicker_setcolourPicker(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlColourPicker_colourSliderValueChanged(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlColourPicker_setHuePicker(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlColourPicker_getBackground(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlColourPicker_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlColourPicker_ControlColourPicker(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocos2d_extension_ControlPotentiometer_class;
extern JSObject *jsb_cocos2d_extension_ControlPotentiometer_prototype;

bool js_cocos2dx_extension_ControlPotentiometer_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_extension_ControlPotentiometer_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_extension_ControlPotentiometer(JSContext *cx, JSObject *global);
void register_all_cocos2dx_extension(JSContext* cx, JSObject* obj);
bool js_cocos2dx_extension_ControlPotentiometer_setPreviousLocation(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlPotentiometer_setValue(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlPotentiometer_getProgressTimer(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlPotentiometer_getMaximumValue(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlPotentiometer_angleInDegreesBetweenLineFromPoint_toPoint_toLineFromPoint_toPoint(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlPotentiometer_potentiometerBegan(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlPotentiometer_setMaximumValue(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlPotentiometer_getMinimumValue(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlPotentiometer_setThumbSprite(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlPotentiometer_getValue(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlPotentiometer_getPreviousLocation(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlPotentiometer_distanceBetweenPointAndPoint(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlPotentiometer_potentiometerEnded(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlPotentiometer_setProgressTimer(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlPotentiometer_setMinimumValue(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlPotentiometer_getThumbSprite(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlPotentiometer_initWithTrackSprite_ProgressTimer_ThumbSprite(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlPotentiometer_potentiometerMoved(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlPotentiometer_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlPotentiometer_ControlPotentiometer(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocos2d_extension_ControlSlider_class;
extern JSObject *jsb_cocos2d_extension_ControlSlider_prototype;

bool js_cocos2dx_extension_ControlSlider_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_extension_ControlSlider_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_extension_ControlSlider(JSContext *cx, JSObject *global);
void register_all_cocos2dx_extension(JSContext* cx, JSObject* obj);
bool js_cocos2dx_extension_ControlSlider_getSelectedThumbSprite(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlSlider_locationFromTouch(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlSlider_setSelectedThumbSprite(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlSlider_setProgressSprite(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlSlider_getMaximumAllowedValue(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlSlider_getMinimumAllowedValue(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlSlider_getMinimumValue(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlSlider_setThumbSprite(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlSlider_setMinimumValue(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlSlider_setMinimumAllowedValue(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlSlider_setEnabled(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlSlider_setValue(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlSlider_setMaximumValue(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlSlider_needsLayout(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlSlider_getBackgroundSprite(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlSlider_initWithSprites(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlSlider_getMaximumValue(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlSlider_isTouchInside(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlSlider_getValue(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlSlider_getThumbSprite(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlSlider_getProgressSprite(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlSlider_setBackgroundSprite(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlSlider_setMaximumAllowedValue(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlSlider_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlSlider_ControlSlider(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocos2d_extension_ControlStepper_class;
extern JSObject *jsb_cocos2d_extension_ControlStepper_prototype;

bool js_cocos2dx_extension_ControlStepper_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_extension_ControlStepper_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_extension_ControlStepper(JSContext *cx, JSObject *global);
void register_all_cocos2dx_extension(JSContext* cx, JSObject* obj);
bool js_cocos2dx_extension_ControlStepper_setMinusSprite(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlStepper_getMinusLabel(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlStepper_setWraps(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlStepper_isContinuous(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlStepper_getMinusSprite(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlStepper_updateLayoutUsingTouchLocation(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlStepper_setValueWithSendingEvent(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlStepper_getPlusLabel(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlStepper_stopAutorepeat(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlStepper_setMinimumValue(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlStepper_getPlusSprite(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlStepper_setPlusSprite(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlStepper_setMinusLabel(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlStepper_setValue(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlStepper_setStepValue(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlStepper_setMaximumValue(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlStepper_update(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlStepper_startAutorepeat(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlStepper_initWithMinusSpriteAndPlusSprite(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlStepper_getValue(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlStepper_setPlusLabel(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlStepper_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlStepper_ControlStepper(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocos2d_extension_ControlSwitch_class;
extern JSObject *jsb_cocos2d_extension_ControlSwitch_prototype;

bool js_cocos2dx_extension_ControlSwitch_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_extension_ControlSwitch_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_extension_ControlSwitch(JSContext *cx, JSObject *global);
void register_all_cocos2dx_extension(JSContext* cx, JSObject* obj);
bool js_cocos2dx_extension_ControlSwitch_setEnabled(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlSwitch_setOn(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlSwitch_isOn(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlSwitch_initWithMaskSprite(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlSwitch_hasMoved(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlSwitch_locationFromTouch(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlSwitch_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ControlSwitch_ControlSwitch(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocos2d_extension_ScrollView_class;
extern JSObject *jsb_cocos2d_extension_ScrollView_prototype;

bool js_cocos2dx_extension_ScrollView_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_extension_ScrollView_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_extension_ScrollView(JSContext *cx, JSObject *global);
void register_all_cocos2dx_extension(JSContext* cx, JSObject* obj);
bool js_cocos2dx_extension_ScrollView_isClippingToBounds(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ScrollView_setContainer(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ScrollView_setContentOffsetInDuration(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ScrollView_setZoomScaleInDuration(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ScrollView_updateTweenAction(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ScrollView_setMaxScale(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ScrollView_hasVisibleParents(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ScrollView_getDirection(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ScrollView_getContainer(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ScrollView_setMinScale(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ScrollView_getZoomScale(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ScrollView_updateInset(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ScrollView_initWithViewSize(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ScrollView_pause(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ScrollView_setDirection(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ScrollView_init(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ScrollView_setContentOffset(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ScrollView_isDragging(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ScrollView_isTouchEnabled(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ScrollView_isBounceable(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ScrollView_setTouchEnabled(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ScrollView_getContentOffset(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ScrollView_resume(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ScrollView_setClippingToBounds(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ScrollView_setViewSize(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ScrollView_getViewSize(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ScrollView_maxContainerOffset(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ScrollView_setBounceable(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ScrollView_isTouchMoved(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ScrollView_isNodeVisible(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ScrollView_minContainerOffset(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ScrollView_setZoomScale(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ScrollView_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_ScrollView_ScrollView(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocos2d_extension_TableViewCell_class;
extern JSObject *jsb_cocos2d_extension_TableViewCell_prototype;

bool js_cocos2dx_extension_TableViewCell_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_extension_TableViewCell_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_extension_TableViewCell(JSContext *cx, JSObject *global);
void register_all_cocos2dx_extension(JSContext* cx, JSObject* obj);
bool js_cocos2dx_extension_TableViewCell_reset(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_TableViewCell_getIdx(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_TableViewCell_setIdx(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_TableViewCell_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_TableViewCell_TableViewCell(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocos2d_extension_TableView_class;
extern JSObject *jsb_cocos2d_extension_TableView_prototype;

bool js_cocos2dx_extension_TableView_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_extension_TableView_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_extension_TableView(JSContext *cx, JSObject *global);
void register_all_cocos2dx_extension(JSContext* cx, JSObject* obj);
bool js_cocos2dx_extension_TableView_updateCellAtIndex(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_TableView_setVerticalFillOrder(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_TableView_scrollViewDidZoom(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_TableView__updateContentSize(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_TableView_getVerticalFillOrder(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_TableView_removeCellAtIndex(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_TableView_initWithViewSize(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_TableView_scrollViewDidScroll(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_TableView_reloadData(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_TableView_insertCellAtIndex(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_TableView_cellAtIndex(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_TableView_dequeueCell(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_TableView_TableView(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocos2d_extension_EventAssetsManagerEx_class;
extern JSObject *jsb_cocos2d_extension_EventAssetsManagerEx_prototype;

bool js_cocos2dx_extension_EventAssetsManagerEx_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_extension_EventAssetsManagerEx_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_extension_EventAssetsManagerEx(JSContext *cx, JSObject *global);
void register_all_cocos2dx_extension(JSContext* cx, JSObject* obj);
bool js_cocos2dx_extension_EventAssetsManagerEx_getAssetsManagerEx(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_EventAssetsManagerEx_getAssetId(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_EventAssetsManagerEx_getCURLECode(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_EventAssetsManagerEx_getMessage(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_EventAssetsManagerEx_getCURLMCode(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_EventAssetsManagerEx_getPercentByFile(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_EventAssetsManagerEx_getEventCode(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_EventAssetsManagerEx_getPercent(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_EventAssetsManagerEx_EventAssetsManagerEx(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocos2d_extension_Manifest_class;
extern JSObject *jsb_cocos2d_extension_Manifest_prototype;

bool js_cocos2dx_extension_Manifest_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_extension_Manifest_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_extension_Manifest(JSContext *cx, JSObject *global);
void register_all_cocos2dx_extension(JSContext* cx, JSObject* obj);
bool js_cocos2dx_extension_Manifest_getManifestFileUrl(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_Manifest_isVersionLoaded(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_Manifest_isLoaded(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_Manifest_getPackageUrl(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_Manifest_getVersion(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_Manifest_getVersionFileUrl(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_Manifest_getSearchPaths(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocos2d_extension_AssetsManagerEx_class;
extern JSObject *jsb_cocos2d_extension_AssetsManagerEx_prototype;

bool js_cocos2dx_extension_AssetsManagerEx_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_extension_AssetsManagerEx_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_extension_AssetsManagerEx(JSContext *cx, JSObject *global);
void register_all_cocos2dx_extension(JSContext* cx, JSObject* obj);
bool js_cocos2dx_extension_AssetsManagerEx_getState(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_AssetsManagerEx_checkUpdate(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_AssetsManagerEx_getStoragePath(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_AssetsManagerEx_update(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_AssetsManagerEx_getLocalManifest(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_AssetsManagerEx_getRemoteManifest(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_AssetsManagerEx_downloadFailedAssets(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_AssetsManagerEx_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_AssetsManagerEx_AssetsManagerEx(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocos2d_extension_EventListenerAssetsManagerEx_class;
extern JSObject *jsb_cocos2d_extension_EventListenerAssetsManagerEx_prototype;

bool js_cocos2dx_extension_EventListenerAssetsManagerEx_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_extension_EventListenerAssetsManagerEx_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_extension_EventListenerAssetsManagerEx(JSContext *cx, JSObject *global);
void register_all_cocos2dx_extension(JSContext* cx, JSObject* obj);
bool js_cocos2dx_extension_EventListenerAssetsManagerEx_init(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_EventListenerAssetsManagerEx_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_extension_EventListenerAssetsManagerEx_EventListenerAssetsManagerEx(JSContext *cx, uint32_t argc, jsval *vp);
#endif

