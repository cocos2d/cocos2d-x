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


NS_CC_EXT_END

#endif // COCOS2D_CCDEPRECATED_EXT_H__
