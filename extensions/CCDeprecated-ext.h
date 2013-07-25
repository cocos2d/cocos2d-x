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
CC_DEPRECATED_ATTRIBUTE typedef ScrollViewDirection CCScrollViewDirection;
CC_DEPRECATED_ATTRIBUTE typedef TableViewVerticalFillOrder CCTableViewVerticalFillOrder;
CC_DEPRECATED_ATTRIBUTE typedef ControlStepperPart CCControlStepperPart;
CC_DEPRECATED_ATTRIBUTE typedef ControlEvent CCControlEvent;
CC_DEPRECATED_ATTRIBUTE typedef ControlState CCControlState;
CC_DEPRECATED_ATTRIBUTE typedef NodeLoaderMap CCNodeLoaderMap;
CC_DEPRECATED_ATTRIBUTE typedef NodeLoaderMapEntry CCNodeLoaderMapEntry;
CC_DEPRECATED_ATTRIBUTE typedef EventRegistry CCEventRegistry;
CC_DEPRECATED_ATTRIBUTE typedef AttachmentType CCAttachmentType;

#define kCCTableViewFillTopDown kTableViewFillTopDown
#define kCCTableViewFillBottomUp kTableViewFillBottomUp
#define kCCScrollViewDirectionNone kScrollViewDirectionNone
#define kCCScrollViewDirectionHorizontal kScrollViewDirectionHorizontal
#define kCCScrollViewDirectionVertical kScrollViewDirectionVertical
#define kCCScrollViewDirectionBoth kScrollViewDirectionBoth
#define kCCKeyboardReturnTypeDefault kKeyboardReturnTypeDefault
#define kCCKeyboardReturnTypeDone kKeyboardReturnTypeDone
#define kCCKeyboardReturnTypeSend kKeyboardReturnTypeSend
#define kCCKeyboardReturnTypeSearch kKeyboardReturnTypeSearch
#define kCCKeyboardReturnTypeGo kKeyboardReturnTypeGo

#define kCCEditBoxInputModeAny kEditBoxInputModeAny
#define kCCEditBoxInputModeEmailAddr kEditBoxInputModeEmailAddr
#define kCCEditBoxInputModeNumeric kEditBoxInputModeNumeric
#define kCCEditBoxInputModePhoneNumber kEditBoxInputModePhoneNumber
#define kCCEditBoxInputModeUrl kEditBoxInputModeUrl
#define kCCEditBoxInputModeDecimal kEditBoxInputModeDecimal
#define kCCEditBoxInputModeSingleLine kEditBoxInputModeSingleLine

#define kCCControlStepperPartMinus kControlStepperPartMinus
#define kCCControlStepperPartPlus kControlStepperPartPlus
#define kCCControlStepperPartNone kControlStepperPartNone

#define CCControlEventTouchDown ControlEventTouchDown
#define CCControlEventTouchDragInside ControlEventTouchDragInside
#define CCControlEventTouchDragOutside ControlEventTouchDragOutside
#define CCControlEventTouchDragEnter ControlEventTouchDragEnter
#define CCControlEventTouchDragExit ControlEventTouchDragExit
#define CCControlEventTouchUpInside ControlEventTouchUpInside
#define CCControlEventTouchUpOutside ControlEventTouchUpOutside
#define CCControlEventTouchCancel ControlEventTouchCancel
#define CCControlEventValueChanged ControlEventValueChanged

#define CCControlStateNormal ControlStateNormal
#define CCControlStateHighlighted ControlStateHighlighted
#define CCControlStateDisabled ControlStateDisabled
#define CCControlStateSelected ControlStateSelected

#define kCCCreateFile kCreateFile
#define kCCNetwork kNetwork
#define kCCNoNewVersion kNoNewVersion
#define kCCUncompress kUncompress

#define kCCHttpGet kHttpGet
#define kCCHttpPut kHttpPut
#define kCCHttpPost kHttpPost
#define kCCHttpDelete kHttpDelete
#define kCCHttpUnkown kHttpUnkown

NS_CC_EXT_END

#endif // COCOS2D_CCDEPRECATED_EXT_H__
