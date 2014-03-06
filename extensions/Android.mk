LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE    := cocos_extension_static

LOCAL_MODULE_FILENAME := libextension

LOCAL_SRC_FILES := AssetsManager/AssetsManager.cpp \
CCBReader/CCBFileLoader.cpp \
CCBReader/CCBReader.cpp \
CCBReader/CCControlButtonLoader.cpp \
CCBReader/CCControlLoader.cpp \
CCBReader/CCLabelBMFontLoader.cpp \
CCBReader/CCLabelTTFLoader.cpp \
CCBReader/CCLayerColorLoader.cpp \
CCBReader/CCLayerGradientLoader.cpp \
CCBReader/CCLayerLoader.cpp \
CCBReader/CCMenuItemImageLoader.cpp \
CCBReader/CCMenuItemLoader.cpp \
CCBReader/CCNodeLoader.cpp \
CCBReader/CCNodeLoaderLibrary.cpp \
CCBReader/CCParticleSystemQuadLoader.cpp \
CCBReader/CCScale9SpriteLoader.cpp \
CCBReader/CCScrollViewLoader.cpp \
CCBReader/CCSpriteLoader.cpp \
CCBReader/CCBAnimationManager.cpp \
CCBReader/CCBKeyframe.cpp \
CCBReader/CCBSequence.cpp \
CCBReader/CCBSequenceProperty.cpp \
CCBReader/CCBValue.cpp \
CCBReader/CCData.cpp \
CCBReader/CCNode+CCBRelativePositioning.cpp \
GUI/CCControlExtension/CCControl.cpp \
GUI/CCControlExtension/CCControlButton.cpp \
GUI/CCControlExtension/CCControlColourPicker.cpp \
GUI/CCControlExtension/CCControlHuePicker.cpp \
GUI/CCControlExtension/CCControlSaturationBrightnessPicker.cpp \
GUI/CCControlExtension/CCControlSlider.cpp \
GUI/CCControlExtension/CCControlSwitch.cpp \
GUI/CCControlExtension/CCControlUtils.cpp \
GUI/CCControlExtension/CCInvocation.cpp \
GUI/CCControlExtension/CCScale9Sprite.cpp \
GUI/CCControlExtension/CCControlPotentiometer.cpp \
GUI/CCControlExtension/CCControlStepper.cpp \
GUI/CCScrollView/CCScrollView.cpp \
GUI/CCScrollView/CCTableView.cpp \
GUI/CCScrollView/CCTableViewCell.cpp \
GUI/CCScrollView/CCSorting.cpp \
GUI/CCEditBox/CCEditBox.cpp \
GUI/CCEditBox/CCEditBoxImplAndroid.cpp \
network/HttpClient.cpp \
network/WebSocket.cpp \
physics_nodes/CCPhysicsDebugNode.cpp \
physics_nodes/CCPhysicsSprite.cpp \
LocalStorage/LocalStorageAndroid.cpp \
CocoStudio/Armature/CCArmature.cpp \
CocoStudio/Armature/CCBone.cpp \
CocoStudio/Armature/animation/CCArmatureAnimation.cpp \
CocoStudio/Armature/animation/CCProcessBase.cpp \
CocoStudio/Armature/animation/CCTween.cpp \
CocoStudio/Armature/datas/CCDatas.cpp \
CocoStudio/Armature/display/CCBatchNode.cpp \
CocoStudio/Armature/display/CCDecorativeDisplay.cpp \
CocoStudio/Armature/display/CCDisplayFactory.cpp \
CocoStudio/Armature/display/CCDisplayManager.cpp \
CocoStudio/Armature/display/CCSkin.cpp \
CocoStudio/Armature/physics/CCColliderDetector.cpp \
CocoStudio/Armature/utils/CCArmatureDefine.cpp \
CocoStudio/Armature/utils/CCArmatureDataManager.cpp \
CocoStudio/Armature/utils/CCDataReaderHelper.cpp \
CocoStudio/Armature/utils/CCSpriteFrameCacheHelper.cpp \
CocoStudio/Armature/utils/CCTransformHelp.cpp \
CocoStudio/Armature/utils/CCTweenFunction.cpp \
CocoStudio/Armature/utils/CCUtilMath.cpp \
CocoStudio/GUI/BaseClasses/UIWidget.cpp \
CocoStudio/GUI/Layouts/UILayout.cpp \
CocoStudio/GUI/Layouts/UILayoutParameter.cpp \
CocoStudio/GUI/Layouts/UILayoutDefine.cpp \
CocoStudio/GUI/System/CocosGUI.cpp \
CocoStudio/GUI/System/UIHelper.cpp \
CocoStudio/GUI/System/UITouchGroup.cpp \
CocoStudio/GUI/UIWidgets/ScrollWidget/UIListView.cpp \
CocoStudio/GUI/UIWidgets/ScrollWidget/UIPageView.cpp \
CocoStudio/GUI/UIWidgets/ScrollWidget/UIScrollView.cpp \
CocoStudio/GUI/UIWidgets/UIButton.cpp \
CocoStudio/GUI/UIWidgets/UICheckBox.cpp \
CocoStudio/GUI/UIWidgets/UIImageView.cpp \
CocoStudio/GUI/UIWidgets/UILabel.cpp \
CocoStudio/GUI/UIWidgets/UILabelAtlas.cpp \
CocoStudio/GUI/UIWidgets/UILabelBMFont.cpp \
CocoStudio/GUI/UIWidgets/UILoadingBar.cpp \
CocoStudio/GUI/UIWidgets/UISlider.cpp \
CocoStudio/GUI/UIWidgets/UITextField.cpp \
CocoStudio/GUI/UIWidgets/UIRichText.cpp \
CocoStudio/Components/CCComAttribute.cpp \
CocoStudio/Components/CCComAudio.cpp \
CocoStudio/Components/CCComController.cpp \
CocoStudio/Components/CCComRender.cpp \
CocoStudio/Components/CCInputDelegate.cpp \
CocoStudio/Json/DictionaryHelper.cpp \
CocoStudio/Reader/SceneReader.cpp \
CocoStudio/Reader/GUIReader.cpp \
CocoStudio/Reader/WidgetReader/WidgetReader.cpp \
CocoStudio/Reader/WidgetReader/ButtonReader/ButtonReader.cpp \
CocoStudio/Reader/WidgetReader/CheckBoxReader/CheckBoxReader.cpp \
CocoStudio/Reader/WidgetReader/ImageViewReader/ImageViewReader.cpp \
CocoStudio/Reader/WidgetReader/LabelAtlasReader/LabelAtlasReader.cpp \
CocoStudio/Reader/WidgetReader/LabelBMFontReader/LabelBMFontReader.cpp \
CocoStudio/Reader/WidgetReader/LabelReader/LabelReader.cpp \
CocoStudio/Reader/WidgetReader/LayoutReader/LayoutReader.cpp \
CocoStudio/Reader/WidgetReader/ListViewReader/ListViewReader.cpp \
CocoStudio/Reader/WidgetReader/LoadingBarReader/LoadingBarReader.cpp \
CocoStudio/Reader/WidgetReader/PageViewReader/PageViewReader.cpp \
CocoStudio/Reader/WidgetReader/ScrollViewReader/ScrollViewReader.cpp \
CocoStudio/Reader/WidgetReader/SliderReader/SliderReader.cpp \
CocoStudio/Reader/WidgetReader/TextFieldReader/TextFieldReader.cpp \
CocoStudio/Action/CCActionManager.cpp \
CocoStudio/Action/CCActionObject.cpp \
CocoStudio/Action/CCActionNode.cpp \
CocoStudio/Action/CCActionFrame.cpp \
CocoStudio/Action/CCActionEaseEx.cpp \
CocoStudio/Action/CCActionFrameEasing.cpp \
CocoStudio/Trigger/ObjectFactory.cpp \
CocoStudio/Trigger/TriggerBase.cpp \
CocoStudio/Trigger/TriggerMng.cpp \
CocoStudio/Trigger/TriggerObj.cpp \
spine/Animation.cpp \
spine/AnimationState.cpp \
spine/AnimationStateData.cpp \
spine/Atlas.cpp \
spine/AtlasAttachmentLoader.cpp \
spine/Attachment.cpp \
spine/AttachmentLoader.cpp \
spine/Bone.cpp \
spine/BoneData.cpp \
spine/Json.cpp \
spine/RegionAttachment.cpp \
spine/Skeleton.cpp \
spine/SkeletonData.cpp \
spine/SkeletonJson.cpp \
spine/Skin.cpp \
spine/Slot.cpp \
spine/SlotData.cpp \
spine/extension.cpp \
spine/CCSkeletonAnimation.cpp \
spine/CCSkeleton.cpp \
spine/spine-cocos2dx.cpp \

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_curl_static
LOCAL_WHOLE_STATIC_LIBRARIES += box2d_static
LOCAL_WHOLE_STATIC_LIBRARIES += chipmunk_static
LOCAL_WHOLE_STATIC_LIBRARIES += libwebsockets_static

LOCAL_CFLAGS += -DCC_ENABLE_CHIPMUNK_INTEGRATION=1
LOCAL_EXPORT_CFLAGS += -DCC_ENABLE_CHIPMUNK_INTEGRATION=1
LOCAL_CPPFLAGS += -DCC_ENABLE_CHIPMUNK_INTEGRATION=1
LOCAL_EXPORT_CPPFLAGS += -DCC_ENABLE_CHIPMUNK_INTEGRATION=1

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH) \
                           $(LOCAL_PATH)/CCBReader \
                           $(LOCAL_PATH)/GUI/CCControlExtension \
                           $(LOCAL_PATH)/GUI/CCScrollView \
                           $(LOCAL_PATH)/network \
                           $(LOCAL_PATH)/LocalStorage \
						               $(LOCAL_PATH)/CocoStudio/Armature

LOCAL_CFLAGS := -fexceptions
                    
include $(BUILD_STATIC_LIBRARY)

$(call import-module,cocos2dx)
$(call import-module,CocosDenshion/android)
$(call import-module,cocos2dx/platform/third_party/android/prebuilt/libcurl)
$(call import-module,external/Box2D)
$(call import-module,external/chipmunk)
$(call import-module,external/libwebsockets/android)
