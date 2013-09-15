/****************************************************************************
 Copyright (c) 2013 cocos2d-x.org
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

/** Add deprecated global functions and variables here
 */

#ifndef COCOS2D_CCDEPRECATED_EXT_H__
#define COCOS2D_CCDEPRECATED_EXT_H__

NS_CC_EXT_BEGIN

CC_DEPRECATED_ATTRIBUTE typedef TableView CCTableView;
CC_DEPRECATED_ATTRIBUTE typedef TableViewCell CCTableViewCell;
CC_DEPRECATED_ATTRIBUTE typedef TableViewDelegate CCTableViewDelegate;
CC_DEPRECATED_ATTRIBUTE typedef TableViewDataSource CCTableViewDataSource;
CC_DEPRECATED_ATTRIBUTE typedef TableView CCTableView;
CC_DEPRECATED_ATTRIBUTE typedef ScrollView CCScrollView;
CC_DEPRECATED_ATTRIBUTE typedef ScrollViewDelegate CCScrollViewDelegate;
CC_DEPRECATED_ATTRIBUTE typedef ScrollView CCScrollView;
CC_DEPRECATED_ATTRIBUTE typedef SortableObject CCSortableObject;
CC_DEPRECATED_ATTRIBUTE typedef ArrayForObjectSorting CCArrayForObjectSorting;
CC_DEPRECATED_ATTRIBUTE typedef TableViewCell CCTableViewCell;
CC_DEPRECATED_ATTRIBUTE typedef EditBox CCEditBox;
CC_DEPRECATED_ATTRIBUTE typedef EditBoxDelegate CCEditBoxDelegate;

CC_DEPRECATED_ATTRIBUTE typedef Color3bObject CCColor3bObject;
CC_DEPRECATED_ATTRIBUTE typedef ControlUtils CCControlUtils;
CC_DEPRECATED_ATTRIBUTE typedef Scale9Sprite CCScale9Sprite;
CC_DEPRECATED_ATTRIBUTE typedef ControlSwitchSprite CCControlSwitchSprite;
CC_DEPRECATED_ATTRIBUTE typedef ControlHuePicker CCControlHuePicker;
CC_DEPRECATED_ATTRIBUTE typedef Invocation CCInvocation;
CC_DEPRECATED_ATTRIBUTE typedef ControlSaturationBrightnessPicker CCControlSaturationBrightnessPicker;
CC_DEPRECATED_ATTRIBUTE typedef ControlStepper CCControlStepper;
CC_DEPRECATED_ATTRIBUTE typedef ControlPotentiometer CCControlPotentiometer;
CC_DEPRECATED_ATTRIBUTE typedef ControlSwitchSprite CCControlSwitchSprite;
CC_DEPRECATED_ATTRIBUTE typedef ControlSwitch CCControlSwitch;
CC_DEPRECATED_ATTRIBUTE typedef ControlButton CCControlButton;
CC_DEPRECATED_ATTRIBUTE typedef ControlSlider CCControlSlider;
CC_DEPRECATED_ATTRIBUTE typedef Control CCControl;
CC_DEPRECATED_ATTRIBUTE typedef ControlLoader CCControlLoader;
CC_DEPRECATED_ATTRIBUTE typedef ControlColourPicker CCControlColourPicker;

CC_DEPRECATED_ATTRIBUTE typedef LabelBMFontLoader CCLabelBMFontLoader;
CC_DEPRECATED_ATTRIBUTE typedef ScrollViewLoader CCScrollViewLoader;
CC_DEPRECATED_ATTRIBUTE typedef SpriteLoader CCSpriteLoader;
CC_DEPRECATED_ATTRIBUTE typedef NodeLoader CCNodeLoader;
CC_DEPRECATED_ATTRIBUTE typedef NodeLoaderLibrary CCNodeLoaderLibrary;
CC_DEPRECATED_ATTRIBUTE typedef NodeLoaderListener CCNodeLoaderListener;
CC_DEPRECATED_ATTRIBUTE typedef LayerLoader CCLayerLoader;
CC_DEPRECATED_ATTRIBUTE typedef MenuLoader CCMenuLoader;
CC_DEPRECATED_ATTRIBUTE typedef Color3BWapper CCColor3BWapper;
CC_DEPRECATED_ATTRIBUTE typedef ParticleSystemQuadLoader CCParticleSystemQuadLoader;
CC_DEPRECATED_ATTRIBUTE typedef MenuItemImageLoader CCMenuItemImageLoader;
CC_DEPRECATED_ATTRIBUTE typedef ControlButtonLoader CCControlButtonLoader;
CC_DEPRECATED_ATTRIBUTE typedef LayerGradientLoader CCLayerGradientLoader;
CC_DEPRECATED_ATTRIBUTE typedef Scale9SpriteLoader CCScale9SpriteLoader;
CC_DEPRECATED_ATTRIBUTE typedef NodeLoaderLibrary CCNodeLoaderLibrary;
CC_DEPRECATED_ATTRIBUTE typedef MenuItemLoader CCMenuItemLoader;
CC_DEPRECATED_ATTRIBUTE typedef LayerColorLoader CCLayerColorLoader;
CC_DEPRECATED_ATTRIBUTE typedef LabelTTFLoader CCLabelTTFLoader;


#if CC_ENABLE_BOX2D_INTEGRATION || CC_ENABLE_CHIPMUNK_INTEGRATION
CC_DEPRECATED_ATTRIBUTE typedef PhysicsSprite CCPhysicsSprite;
#endif

#if CC_ENABLE_CHIPMUNK_INTEGRATION
CC_DEPRECATED_ATTRIBUTE typedef PhysicsDebugNode CCPhysicsDebugNode;
#endif

CC_DEPRECATED_ATTRIBUTE typedef ComController CCComController;
CC_DEPRECATED_ATTRIBUTE typedef ComAttribute CCComAttribute;
CC_DEPRECATED_ATTRIBUTE typedef InputDelegate CCInputDelegate;
CC_DEPRECATED_ATTRIBUTE typedef ComAudio CCComAudio;

CC_DEPRECATED_ATTRIBUTE typedef HttpClient CCHttpClient;
CC_DEPRECATED_ATTRIBUTE typedef HttpResponse CCHttpResponse;
CC_DEPRECATED_ATTRIBUTE typedef HttpRequest CCHttpRequest;
CC_DEPRECATED_ATTRIBUTE typedef Skin CCSkin;

CC_DEPRECATED_ATTRIBUTE typedef AtlasFormat CCAtlasFormat;
CC_DEPRECATED_ATTRIBUTE typedef AtlasFilter CCAtlasFilter;
CC_DEPRECATED_ATTRIBUTE typedef AtlasWrap CCAtlasWrap;
CC_DEPRECATED_ATTRIBUTE typedef AtlasPage CCAtlasPage;
CC_DEPRECATED_ATTRIBUTE typedef AtlasRegion CCAtlasRegion;
CC_DEPRECATED_ATTRIBUTE typedef Atlas CCAtlas;
CC_DEPRECATED_ATTRIBUTE typedef AnimationStateData CCAnimationStateData;
CC_DEPRECATED_ATTRIBUTE typedef SlotData CCSlotData;
CC_DEPRECATED_ATTRIBUTE typedef AttachmentLoader CCAttachmentLoader;
CC_DEPRECATED_ATTRIBUTE typedef AnimationState CCAnimationState;
CC_DEPRECATED_ATTRIBUTE typedef SkeletonJson CCSkeletonJson;
CC_DEPRECATED_ATTRIBUTE typedef Timeline CCTimeline;
CC_DEPRECATED_ATTRIBUTE typedef CurveTimeline CCCurveTimeline;
CC_DEPRECATED_ATTRIBUTE typedef RotateTimeline CCRotateTimeline;
CC_DEPRECATED_ATTRIBUTE typedef TranslateTimeline CCTranslateTimeline;
CC_DEPRECATED_ATTRIBUTE typedef ScaleTimeline CCScaleTimeline;
CC_DEPRECATED_ATTRIBUTE typedef ColorTimeline CCColorTimeline;
CC_DEPRECATED_ATTRIBUTE typedef AttachmentTimeline CCAttachmentTimeline;
CC_DEPRECATED_ATTRIBUTE typedef AtlasAttachmentLoader CCAtlasAttachmentLoader;
CC_DEPRECATED_ATTRIBUTE typedef VertexIndex CCVertexIndex;
CC_DEPRECATED_ATTRIBUTE typedef RegionAttachment CCRegionAttachment;

CC_DEPRECATED_ATTRIBUTE typedef NodeLoaderMap CCNodeLoaderMap;
CC_DEPRECATED_ATTRIBUTE typedef NodeLoaderMapEntry CCNodeLoaderMapEntry;
CC_DEPRECATED_ATTRIBUTE typedef EventRegistry CCEventRegistry;
CC_DEPRECATED_ATTRIBUTE typedef AttachmentType CCAttachmentType;


CC_DEPRECATED_ATTRIBUTE const ScrollView::Direction kCCScrollViewDirectionNone = ScrollView::Direction::NONE;
CC_DEPRECATED_ATTRIBUTE const ScrollView::Direction kCCScrollViewDirectionHorizontal = ScrollView::Direction::HORIZONTAL;
CC_DEPRECATED_ATTRIBUTE const ScrollView::Direction kCCScrollViewDirectionVertical = ScrollView::Direction::VERTICAL;
CC_DEPRECATED_ATTRIBUTE const ScrollView::Direction kCCScrollViewDirectionBoth = ScrollView::Direction::BOTH;
CC_DEPRECATED_ATTRIBUTE typedef ScrollView::Direction CCScrollViewDirection;

CC_DEPRECATED_ATTRIBUTE const TableView::VerticalFillOrder kCCTableViewFillTopDown = TableView::VerticalFillOrder::TOP_DOWN;
CC_DEPRECATED_ATTRIBUTE const TableView::VerticalFillOrder kCCTableViewFillBottomUp = TableView::VerticalFillOrder::BOTTOM_UP;
CC_DEPRECATED_ATTRIBUTE typedef TableView::VerticalFillOrder CCTableViewVerticalFillOrder;

CC_DEPRECATED_ATTRIBUTE const EditBox::KeyboardReturnType  kKeyboardReturnTypeDefault = EditBox::KeyboardReturnType::DEFAULT;
CC_DEPRECATED_ATTRIBUTE const EditBox::KeyboardReturnType  kKeyboardReturnTypeDone = EditBox::KeyboardReturnType::DONE;
CC_DEPRECATED_ATTRIBUTE const EditBox::KeyboardReturnType  kKeyboardReturnTypeSend = EditBox::KeyboardReturnType::SEND;
CC_DEPRECATED_ATTRIBUTE const EditBox::KeyboardReturnType  kKeyboardReturnTypeSearch = EditBox::KeyboardReturnType::SEARCH;
CC_DEPRECATED_ATTRIBUTE const EditBox::KeyboardReturnType  kKeyboardReturnTypeGo = EditBox::KeyboardReturnType::GO;

CC_DEPRECATED_ATTRIBUTE const EditBox::InputMode kEditBoxInputModeAny = EditBox::InputMode::ANY;
CC_DEPRECATED_ATTRIBUTE const EditBox::InputMode kEditBoxInputModeEmailAddr = EditBox::InputMode::EMAIL_ADDRESS;
CC_DEPRECATED_ATTRIBUTE const EditBox::InputMode kEditBoxInputModeNumeric = EditBox::InputMode::NUMERIC;
CC_DEPRECATED_ATTRIBUTE const EditBox::InputMode kEditBoxInputModePhoneNumber = EditBox::InputMode::PHONE_NUMBER;
CC_DEPRECATED_ATTRIBUTE const EditBox::InputMode kEditBoxInputModeUrl = EditBox::InputMode::URL;
CC_DEPRECATED_ATTRIBUTE const EditBox::InputMode kEditBoxInputModeDecimal = EditBox::InputMode::DECIMAL;
CC_DEPRECATED_ATTRIBUTE const EditBox::InputMode kEditBoxInputModeSingleLine = EditBox::InputMode::SINGLE_LINE;

CC_DEPRECATED_ATTRIBUTE const EditBox::InputFlag kEditBoxInputFlagPassword = EditBox::InputFlag::PASSWORD;
CC_DEPRECATED_ATTRIBUTE const EditBox::InputFlag kEditBoxInputFlagSensitive = EditBox::InputFlag::SENSITIVE;
CC_DEPRECATED_ATTRIBUTE const EditBox::InputFlag kEditBoxInputFlagInitialCapsWord = EditBox::InputFlag::INITIAL_CAPS_WORD;
CC_DEPRECATED_ATTRIBUTE const EditBox::InputFlag kEditBoxInputFlagInitialCapsSentence = EditBox::InputFlag::INITIAL_CAPS_SENTENCE;
CC_DEPRECATED_ATTRIBUTE const EditBox::InputFlag kEditBoxInputFlagInitialCapsAllCharacters = EditBox::InputFlag::INTIAL_CAPS_ALL_CHARACTERS;

CC_DEPRECATED_ATTRIBUTE typedef EditBox::KeyboardReturnType KeyboardReturnType;
CC_DEPRECATED_ATTRIBUTE typedef EditBox::InputMode EditBoxInputMode;
CC_DEPRECATED_ATTRIBUTE typedef EditBox::InputFlag EditBoxInputFlag;

CC_DEPRECATED_ATTRIBUTE typedef ControlStepper::Part ControlStepperPart;
CC_DEPRECATED_ATTRIBUTE const ControlStepper::Part kCCControlStepperPartMinus = ControlStepper::Part::MINUS;
CC_DEPRECATED_ATTRIBUTE const ControlStepper::Part kCCControlStepperPartPlus = ControlStepper::Part::PLUS;
CC_DEPRECATED_ATTRIBUTE const ControlStepper::Part kCCControlStepperPartNone = ControlStepper::Part::NONE;

CC_DEPRECATED_ATTRIBUTE const Control::EventType CCControlEventTouchDown = Control::EventType::TOUCH_DOWN;
CC_DEPRECATED_ATTRIBUTE const Control::EventType CCControlEventTouchDragInside = Control::EventType::DRAG_INSIDE;
CC_DEPRECATED_ATTRIBUTE const Control::EventType CCControlEventTouchDragOutside = Control::EventType::DRAG_OUTSIDE;
CC_DEPRECATED_ATTRIBUTE const Control::EventType CCControlEventTouchDragEnter = Control::EventType::DRAG_ENTER;
CC_DEPRECATED_ATTRIBUTE const Control::EventType CCControlEventTouchDragExit = Control::EventType::DRAG_EXIT;
CC_DEPRECATED_ATTRIBUTE const Control::EventType CCControlEventTouchUpInside = Control::EventType::TOUCH_UP_INSIDE;
CC_DEPRECATED_ATTRIBUTE const Control::EventType CCControlEventTouchUpOutside = Control::EventType::TOUCH_UP_OUTSIDE;
CC_DEPRECATED_ATTRIBUTE const Control::EventType CCControlEventTouchCancel = Control::EventType::TOUCH_CANCEL;
CC_DEPRECATED_ATTRIBUTE const Control::EventType CCControlEventValueChanged = Control::EventType::VALUE_CHANGED;

CC_DEPRECATED_ATTRIBUTE typedef Control::EventType CCControlEvent;

CC_DEPRECATED_ATTRIBUTE const Control::State CCControlStateNormal = Control::State::NORMAL;
CC_DEPRECATED_ATTRIBUTE const Control::State CCControlStateHighlighted = Control::State::HIGH_LIGHTED;
CC_DEPRECATED_ATTRIBUTE const Control::State CCControlStateDisabled = Control::State::DISABLED;
CC_DEPRECATED_ATTRIBUTE const Control::State CCControlStateSelected = Control::State::SELECTED;
CC_DEPRECATED_ATTRIBUTE typedef Control::State CCControlState;

CC_DEPRECATED_ATTRIBUTE typedef Control::Handler SEL_CCControlHandler;

// For CCBReader

CC_DEPRECATED_ATTRIBUTE const CCBValue::Type kIntValue = CCBValue::Type::INT;
CC_DEPRECATED_ATTRIBUTE const CCBValue::Type kFloatValue = CCBValue::Type::FLOAT;
CC_DEPRECATED_ATTRIBUTE const CCBValue::Type kBoolValue = CCBValue::Type::BOOL;
CC_DEPRECATED_ATTRIBUTE const CCBValue::Type kUnsignedCharValue = CCBValue::Type::UNSIGNED_CHAR;
CC_DEPRECATED_ATTRIBUTE const CCBValue::Type kStringValue = CCBValue::Type::STRING;
CC_DEPRECATED_ATTRIBUTE const CCBValue::Type kArrayValue = CCBValue::Type::ARRAY;


CC_DEPRECATED_ATTRIBUTE const CCBReader::PropertyType    kCCBPropTypePosition        = CCBReader::PropertyType::POSITION;
CC_DEPRECATED_ATTRIBUTE const CCBReader::PropertyType    kCCBPropTypeSize            = CCBReader::PropertyType::SIZE;
CC_DEPRECATED_ATTRIBUTE const CCBReader::PropertyType    kCCBPropTypePoint           = CCBReader::PropertyType::POINT;
CC_DEPRECATED_ATTRIBUTE const CCBReader::PropertyType    kCCBPropTypePointLock       = CCBReader::PropertyType::POINT_LOCK;
CC_DEPRECATED_ATTRIBUTE const CCBReader::PropertyType    kCCBPropTypeScaleLock       = CCBReader::PropertyType::SCALE_LOCK;
CC_DEPRECATED_ATTRIBUTE const CCBReader::PropertyType    kCCBPropTypeDegrees         = CCBReader::PropertyType::DEGREES;
CC_DEPRECATED_ATTRIBUTE const CCBReader::PropertyType    kCCBPropTypeInteger         = CCBReader::PropertyType::INTEGER;
CC_DEPRECATED_ATTRIBUTE const CCBReader::PropertyType    kCCBPropTypeFloat           = CCBReader::PropertyType::FLOAT;
CC_DEPRECATED_ATTRIBUTE const CCBReader::PropertyType    kCCBPropTypeFloatVar        = CCBReader::PropertyType::FLOAT_VAR;
CC_DEPRECATED_ATTRIBUTE const CCBReader::PropertyType    kCCBPropTypeCheck           = CCBReader::PropertyType::CHECK;
CC_DEPRECATED_ATTRIBUTE const CCBReader::PropertyType    kCCBPropTypeSpriteFrame     = CCBReader::PropertyType::SPRITEFRAME;
CC_DEPRECATED_ATTRIBUTE const CCBReader::PropertyType    kCCBPropTypeTexture         = CCBReader::PropertyType::TEXTURE;
CC_DEPRECATED_ATTRIBUTE const CCBReader::PropertyType    kCCBPropTypeByte            = CCBReader::PropertyType::BYTE;
CC_DEPRECATED_ATTRIBUTE const CCBReader::PropertyType    kCCBPropTypeColor3          = CCBReader::PropertyType::COLOR3;
CC_DEPRECATED_ATTRIBUTE const CCBReader::PropertyType    kCCBPropTypeColor4FVar      = CCBReader::PropertyType::COLOR4F_VAR;
CC_DEPRECATED_ATTRIBUTE const CCBReader::PropertyType    kCCBPropTypeFlip            = CCBReader::PropertyType::FLIP;
CC_DEPRECATED_ATTRIBUTE const CCBReader::PropertyType    kCCBPropTypeBlendmode       = CCBReader::PropertyType::BLEND_MODE;
CC_DEPRECATED_ATTRIBUTE const CCBReader::PropertyType    kCCBPropTypeFntFile         = CCBReader::PropertyType::FNT_FILE;
CC_DEPRECATED_ATTRIBUTE const CCBReader::PropertyType    kCCBPropTypeText            = CCBReader::PropertyType::TEXT;
CC_DEPRECATED_ATTRIBUTE const CCBReader::PropertyType    kCCBPropTypeFontTTF         = CCBReader::PropertyType::FONT_TTF;
CC_DEPRECATED_ATTRIBUTE const CCBReader::PropertyType    kCCBPropTypeIntegerLabeled  = CCBReader::PropertyType::INTEGER_LABELED;
CC_DEPRECATED_ATTRIBUTE const CCBReader::PropertyType    kCCBPropTypeBlock           = CCBReader::PropertyType::BLOCK;
CC_DEPRECATED_ATTRIBUTE const CCBReader::PropertyType    kCCBPropTypeAnimation       = CCBReader::PropertyType::ANIMATION;
CC_DEPRECATED_ATTRIBUTE const CCBReader::PropertyType    kCCBPropTypeCCBFile         = CCBReader::PropertyType::CCB_FILE;
CC_DEPRECATED_ATTRIBUTE const CCBReader::PropertyType    kCCBPropTypeString          = CCBReader::PropertyType::STRING;
CC_DEPRECATED_ATTRIBUTE const CCBReader::PropertyType    kCCBPropTypeBlockCCControl  = CCBReader::PropertyType::BLOCK_CONTROL;
CC_DEPRECATED_ATTRIBUTE const CCBReader::PropertyType    kCCBPropTypeFloatScale      = CCBReader::PropertyType::FLOAT_SCALE;
CC_DEPRECATED_ATTRIBUTE const CCBReader::PropertyType    kCCBPropTypeFloatXY         = CCBReader::PropertyType::FLOAT_XY;

CC_DEPRECATED_ATTRIBUTE const CCBReader::FloatType kCCBFloat0         = CCBReader::FloatType::_0;
CC_DEPRECATED_ATTRIBUTE const CCBReader::FloatType kCCBFloat1         = CCBReader::FloatType::_1;
CC_DEPRECATED_ATTRIBUTE const CCBReader::FloatType kCCBFloatMinus1    = CCBReader::FloatType::MINUS1;
CC_DEPRECATED_ATTRIBUTE const CCBReader::FloatType kCCBFloat05        = CCBReader::FloatType::_05;
CC_DEPRECATED_ATTRIBUTE const CCBReader::FloatType kCCBFloatInteger   = CCBReader::FloatType::INTEGER;
CC_DEPRECATED_ATTRIBUTE const CCBReader::FloatType kCCBFloatFull      = CCBReader::FloatType::FULL;

CC_DEPRECATED_ATTRIBUTE const CCBReader::PlatformType kCCBPlatformAll = CCBReader::PlatformType::ALL;
CC_DEPRECATED_ATTRIBUTE const CCBReader::PlatformType kCCBPlatformIOS = CCBReader::PlatformType::IOS;
CC_DEPRECATED_ATTRIBUTE const CCBReader::PlatformType kCCBPlatformMac = CCBReader::PlatformType::MAC;

CC_DEPRECATED_ATTRIBUTE const CCBReader::TargetType kCCBTargetTypeNone = CCBReader::TargetType::NONE;
CC_DEPRECATED_ATTRIBUTE const CCBReader::TargetType kCCBTargetTypeDocumentRoot = CCBReader::TargetType::DOCUMENT_ROOT;
CC_DEPRECATED_ATTRIBUTE const CCBReader::TargetType kCCBTargetTypeOwner = CCBReader::TargetType::OWNER;

CC_DEPRECATED_ATTRIBUTE const CCBKeyframe::EasingType    kCCBKeyframeEasingInstant       = CCBKeyframe::EasingType::INSTANT       ;
CC_DEPRECATED_ATTRIBUTE const CCBKeyframe::EasingType    kCCBKeyframeEasingLinear        = CCBKeyframe::EasingType::LINEAR        ;
CC_DEPRECATED_ATTRIBUTE const CCBKeyframe::EasingType    kCCBKeyframeEasingCubicIn       = CCBKeyframe::EasingType::CUBIC_IN      ;
CC_DEPRECATED_ATTRIBUTE const CCBKeyframe::EasingType    kCCBKeyframeEasingCubicOut      = CCBKeyframe::EasingType::CUBIC_OUT     ;
CC_DEPRECATED_ATTRIBUTE const CCBKeyframe::EasingType    kCCBKeyframeEasingCubicInOut    = CCBKeyframe::EasingType::CUBIC_INOUT   ;
CC_DEPRECATED_ATTRIBUTE const CCBKeyframe::EasingType    kCCBKeyframeEasingElasticIn     = CCBKeyframe::EasingType::ELASTIC_IN    ;
CC_DEPRECATED_ATTRIBUTE const CCBKeyframe::EasingType    kCCBKeyframeEasingElasticOut    = CCBKeyframe::EasingType::ELASTIC_OUT   ;
CC_DEPRECATED_ATTRIBUTE const CCBKeyframe::EasingType    kCCBKeyframeEasingElasticInOut  = CCBKeyframe::EasingType::ELASTIC_INOUT ;
CC_DEPRECATED_ATTRIBUTE const CCBKeyframe::EasingType    kCCBKeyframeEasingBounceIn      = CCBKeyframe::EasingType::BOUNCE_IN     ;
CC_DEPRECATED_ATTRIBUTE const CCBKeyframe::EasingType    kCCBKeyframeEasingBounceOut     = CCBKeyframe::EasingType::BOUNCE_OUT    ;
CC_DEPRECATED_ATTRIBUTE const CCBKeyframe::EasingType    kCCBKeyframeEasingBounceInOut   = CCBKeyframe::EasingType::BOUNCE_INOUT  ;
CC_DEPRECATED_ATTRIBUTE const CCBKeyframe::EasingType    kCCBKeyframeEasingBackIn        = CCBKeyframe::EasingType::BACK_IN       ;
CC_DEPRECATED_ATTRIBUTE const CCBKeyframe::EasingType    kCCBKeyframeEasingBackOut       = CCBKeyframe::EasingType::BACK_OUT      ;
CC_DEPRECATED_ATTRIBUTE const CCBKeyframe::EasingType    kCCBKeyframeEasingBackInOut     = CCBKeyframe::EasingType::BACK_INOUT    ;

CC_DEPRECATED_ATTRIBUTE const CCBReader::PositionType    kCCBPositionTypeRelativeBottomLeft  =   CCBReader::PositionType::RELATIVE_BOTTOM_LEFT ;
CC_DEPRECATED_ATTRIBUTE const CCBReader::PositionType    kCCBPositionTypeRelativeTopLeft     =   CCBReader::PositionType::RELATIVE_TOP_LEFT    ;
CC_DEPRECATED_ATTRIBUTE const CCBReader::PositionType    kCCBPositionTypeRelativeTopRight    =   CCBReader::PositionType::RELATIVE_TOP_RIGHT   ;
CC_DEPRECATED_ATTRIBUTE const CCBReader::PositionType    kCCBPositionTypeRelativeBottomRight =   CCBReader::PositionType::RELATIVE_BOTTOM_RIGHT;
CC_DEPRECATED_ATTRIBUTE const CCBReader::PositionType    kCCBPositionTypePercent             =   CCBReader::PositionType::PERCENT              ;
CC_DEPRECATED_ATTRIBUTE const CCBReader::PositionType    kCCBPositionTypeMultiplyResolution  =   CCBReader::PositionType::MULTIPLY_RESOLUTION  ;
;
CC_DEPRECATED_ATTRIBUTE const CCBReader::SizeType    kCCBSizeTypeAbsolute              =  CCBReader::SizeType::ABSOLUTE           ;
CC_DEPRECATED_ATTRIBUTE const CCBReader::SizeType    kCCBSizeTypePercent               =  CCBReader::SizeType::PERCENT            ;
CC_DEPRECATED_ATTRIBUTE const CCBReader::SizeType    kCCBSizeTypeRelativeContainer     =  CCBReader::SizeType::RELATIVE_CONTAINER ;
CC_DEPRECATED_ATTRIBUTE const CCBReader::SizeType    kCCBSizeTypeHorizontalPercent     =  CCBReader::SizeType::HORIZONTAL_PERCENT ;
CC_DEPRECATED_ATTRIBUTE const CCBReader::SizeType    kCCBSizeTypeVerticalPercent       =  CCBReader::SizeType::VERTICAL_PERCENT   ;
CC_DEPRECATED_ATTRIBUTE const CCBReader::SizeType    kCCBSizeTypeMultiplyResolution    =  CCBReader::SizeType::MULTIPLY_RESOLUTION;


CC_DEPRECATED_ATTRIBUTE const CCBReader::ScaleType    kCCBScaleTypeAbsolute  = CCBReader::ScaleType::ABSOLUTE;
CC_DEPRECATED_ATTRIBUTE const CCBReader::ScaleType    kCCBScaleTypeMultiplyResolution  = CCBReader::ScaleType::MULTIPLY_RESOLUTION;

NS_CC_EXT_END

#endif // COCOS2D_CCDEPRECATED_EXT_H__
