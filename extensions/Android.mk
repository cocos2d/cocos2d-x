LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE    := cocos_extension_static

LOCAL_MODULE_FILENAME := libextension

LOCAL_SRC_FILES := AssetsManager/AssetsManager.cpp \
CCArmature/CCArmature.cpp \
CCArmature/CCBone.cpp \
CCArmature/animation/CCArmatureAnimation.cpp \
CCArmature/animation/CCProcessBase.cpp \
CCArmature/animation/CCTween.cpp \
CCArmature/datas/CCDatas.cpp \
CCArmature/display/CCBatchNode.cpp \
CCArmature/display/CCDecorativeDisplay.cpp \
CCArmature/display/CCDisplayFactory.cpp \
CCArmature/display/CCDisplayManager.cpp \
CCArmature/display/CCShaderNode.cpp \
CCArmature/display/CCSkin.cpp \
CCArmature/external_tool/GLES-Render.cpp \
CCArmature/external_tool/Json/CSContentJsonDictionary.cpp \
CCArmature/external_tool/Json/lib_json/json_value.cpp \
CCArmature/external_tool/Json/lib_json/json_reader.cpp \
CCArmature/external_tool/Json/lib_json/json_writer.cpp \
CCArmature/physics/CCColliderDetector.cpp \
CCArmature/physics/CCPhysicsWorld.cpp \
CCArmature/utils/CCArmatureDataManager.cpp \
CCArmature/utils/CCDataReaderHelper.cpp \
CCArmature/utils/CCSpriteFrameCacheHelper.cpp \
CCArmature/utils/CCTransformHelp.cpp \
CCArmature/utils/CCTweenFunction.cpp \
CCArmature/utils/CCUtilMath.cpp \
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
CCBReader/CCNode+CCBRelativePositioning.cpp \
Components/CCComAttribute.cpp \
Components/CCComAudio.cpp \
Components/CCComController.cpp \
Components/CCInputDelegate.cpp \
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
network/SocketIO.cpp \
physics_nodes/CCPhysicsDebugNode.cpp \
physics_nodes/CCPhysicsSprite.cpp \
LocalStorage/LocalStorageAndroid.cpp \
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
CCDeprecated-ext.cpp

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_curl_static
LOCAL_WHOLE_STATIC_LIBRARIES += box2d_static
LOCAL_WHOLE_STATIC_LIBRARIES += chipmunk_static
LOCAL_WHOLE_STATIC_LIBRARIES += libwebsockets_static

LOCAL_CXXFLAGS += -fexceptions

LOCAL_CFLAGS += -DCC_ENABLE_CHIPMUNK_INTEGRATION=1
LOCAL_EXPORT_CFLAGS += -DCC_ENABLE_CHIPMUNK_INTEGRATION=1

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH) \
                           $(LOCAL_PATH)/CCBReader \
                           $(LOCAL_PATH)/GUI/CCControlExtension \
                           $(LOCAL_PATH)/GUI/CCScrollView \
                           $(LOCAL_PATH)/network \
                           $(LOCAL_PATH)/LocalStorage 
                    
include $(BUILD_STATIC_LIBRARY)

$(call import-module,cocos2dx)
$(call import-module,CocosDenshion/android)
$(call import-module,cocos2dx/platform/third_party/android/prebuilt/libcurl)
$(call import-module,external/Box2D)
$(call import-module,external/chipmunk)
$(call import-module,external/libwebsockets/android)
