
include(../../cocos2dx/proj.qt5/common.pri)

TEMPLATE = lib
CONFIG += static

#SOURCES += $$files(../qt5/*.cpp)

SOURCES += ../CCBReader/CCBFileLoader.cpp \
../CCBReader/CCMenuItemImageLoader.cpp \
../CCBReader/CCBReader.cpp \
../CCBReader/CCMenuItemLoader.cpp \
../CCBReader/CCControlButtonLoader.cpp \
../CCBReader/CCNodeLoader.cpp \
../CCBReader/CCControlLoader.cpp \
../CCBReader/CCNodeLoaderLibrary.cpp \
../CCBReader/CCLabelBMFontLoader.cpp \
../CCBReader/CCParticleSystemQuadLoader.cpp \
../CCBReader/CCLabelTTFLoader.cpp \
../CCBReader/CCScale9SpriteLoader.cpp \
../CCBReader/CCLayerColorLoader.cpp \
../CCBReader/CCScrollViewLoader.cpp \
../CCBReader/CCLayerGradientLoader.cpp \
../CCBReader/CCSpriteLoader.cpp \
../CCBReader/CCLayerLoader.cpp \
../CCBReader/CCBAnimationManager.cpp \
../CCBReader/CCBKeyframe.cpp \
../CCBReader/CCBSequence.cpp \
../CCBReader/CCBSequenceProperty.cpp \
../CCBReader/CCBValue.cpp \
../CCBReader/CCNode+CCBRelativePositioning.cpp \
../GUI/CCScrollView/CCScrollView.cpp \
../GUI/CCScrollView/CCSorting.cpp \
../GUI/CCScrollView/CCTableView.cpp \
../GUI/CCScrollView/CCTableViewCell.cpp \
../GUI/CCControlExtension/CCControlButton.cpp \
../GUI/CCControlExtension/CCControlColourPicker.cpp \
../GUI/CCControlExtension/CCControl.cpp \
../GUI/CCControlExtension/CCControlHuePicker.cpp \
../GUI/CCControlExtension/CCControlSaturationBrightnessPicker.cpp \
../GUI/CCControlExtension/CCControlSlider.cpp \
../GUI/CCControlExtension/CCControlSwitch.cpp \
../GUI/CCControlExtension/CCControlUtils.cpp \
../GUI/CCControlExtension/CCInvocation.cpp \
../GUI/CCControlExtension/CCScale9Sprite.cpp \
../GUI/CCControlExtension/CCControlPotentiometer.cpp \
../GUI/CCControlExtension/CCControlStepper.cpp \
../GUI/CCEditBox/CCEditBox.cpp \
../GUI/CCEditBox/CCEditBoxImplNone.cpp \
../network/HttpClient.cpp \
../physics_nodes/CCPhysicsDebugNode.cpp \
../physics_nodes/CCPhysicsSprite.cpp \
../spine/Animation.cpp \
../spine/AnimationState.cpp \
../spine/AnimationStateData.cpp \
../spine/Atlas.cpp \
../spine/AtlasAttachmentLoader.cpp \
../spine/Attachment.cpp \
../spine/AttachmentLoader.cpp \
../spine/Bone.cpp \
../spine/BoneData.cpp \
../spine/Json.cpp \
../spine/RegionAttachment.cpp \
../spine/Skeleton.cpp \
../spine/SkeletonData.cpp \
../spine/SkeletonJson.cpp \
../spine/Skin.cpp \
../spine/Slot.cpp \
../spine/SlotData.cpp \
../spine/extension.cpp \
../spine/spine-cocos2dx.cpp \
../spine/CCSkeleton.cpp \
../spine/CCSkeletonAnimation.cpp \
    ../CocoStudio/Action/CCActionObject.cpp \
    ../CocoStudio/Action/CCActionNode.cpp \
    ../CocoStudio/Action/CCActionManagerEx.cpp \
    ../CocoStudio/Action/CCActionFrameEasing.cpp \
    ../CocoStudio/Action/CCActionFrame.cpp \
    ../CocoStudio/Armature/CCBone.cpp \
    ../CocoStudio/Armature/CCArmature.cpp \
    ../CocoStudio/Armature/animation/CCTween.cpp \
    ../CocoStudio/Armature/animation/CCProcessBase.cpp \
    ../CocoStudio/Armature/animation/CCArmatureAnimation.cpp \
    ../CocoStudio/Armature/datas/CCDatas.cpp \
    ../CocoStudio/Armature/display/CCSkin.cpp \
    ../CocoStudio/Armature/display/CCDisplayManager.cpp \
    ../CocoStudio/Armature/display/CCDisplayFactory.cpp \
    ../CocoStudio/Armature/display/CCDecorativeDisplay.cpp \
    ../CocoStudio/Armature/display/CCBatchNode.cpp \
    ../CocoStudio/Armature/physics/CCColliderDetector.cpp \
    ../CocoStudio/Armature/utils/CCUtilMath.cpp \
    ../CocoStudio/Armature/utils/CCTweenFunction.cpp \
    ../CocoStudio/Armature/utils/CCTransformHelp.cpp \
    ../CocoStudio/Armature/utils/CCSpriteFrameCacheHelper.cpp \
    ../CocoStudio/Armature/utils/CCDataReaderHelper.cpp \
    ../CocoStudio/Armature/utils/CCArmatureDefine.cpp \
    ../CocoStudio/Armature/utils/CCArmatureDataManager.cpp \
    ../CocoStudio/Components/CCInputDelegate.cpp \
    ../CocoStudio/Components/CCComRender.cpp \
    ../CocoStudio/Components/CCComController.cpp \
    ../CocoStudio/Components/CCComAudio.cpp \
    ../CocoStudio/Components/CCComAttribute.cpp \
    ../CocoStudio/GUI/BaseClasses/UIWidget.cpp \
    ../CocoStudio/GUI/BaseClasses/UIRootWidget.cpp \
    ../CocoStudio/GUI/Layouts/UILayoutDefine.cpp \
    ../CocoStudio/GUI/Layouts/LayoutParameter.cpp \
    ../CocoStudio/GUI/Layouts/Layout.cpp \
    ../CocoStudio/GUI/System/UILayer.cpp \
    ../CocoStudio/GUI/System/UIInputManager.cpp \
    ../CocoStudio/GUI/System/UIHelper.cpp \
    ../CocoStudio/GUI/System/CocosGUI.cpp \
    ../CocoStudio/GUI/UIWidgets/UITextField.cpp \
    ../CocoStudio/GUI/UIWidgets/UISlider.cpp \
    ../CocoStudio/GUI/UIWidgets/UILoadingBar.cpp \
    ../CocoStudio/GUI/UIWidgets/UILabelBMFont.cpp \
    ../CocoStudio/GUI/UIWidgets/UILabelAtlas.cpp \
    ../CocoStudio/GUI/UIWidgets/UILabel.cpp \
    ../CocoStudio/GUI/UIWidgets/UIImageView.cpp \
    ../CocoStudio/GUI/UIWidgets/UICheckBox.cpp \
    ../CocoStudio/GUI/UIWidgets/UIButton.cpp \
    ../CocoStudio/GUI/UIWidgets/ScrollWidget/UIScrollView.cpp \
    ../CocoStudio/GUI/UIWidgets/ScrollWidget/UIPageView.cpp \
    ../CocoStudio/GUI/UIWidgets/ScrollWidget/UIListView.cpp \
    ../CocoStudio/GUI/UIWidgets/ScrollWidget/UIDragPanel.cpp \
    ../CocoStudio/Json/DictionaryHelper.cpp \
    ../CocoStudio/Json/CSContentJsonDictionary.cpp \
    ../CocoStudio/Json/lib_json/json_writer.cpp \
    ../CocoStudio/Json/lib_json/json_valueiterator.inl \
    ../CocoStudio/Json/lib_json/json_value.cpp \
    ../CocoStudio/Json/lib_json/json_reader.cpp \
    ../CocoStudio/Json/lib_json/json_internalmap.inl \
    ../CocoStudio/Json/lib_json/json_internalarray.inl \
    ../CocoStudio/Reader/CCSSceneReader.cpp \
    ../CocoStudio/Reader/CCSGUIReader.cpp

INCLUDEPATH += ..
INCLUDEPATH += ../include
INCLUDEPATH += ../CCBReader
INCLUDEPATH += ../GUI/CCControlExtension
INCLUDEPATH += ../GUI/CCEditBox
INCLUDEPATH += ../network
INCLUDEPATH += ../Components
INCLUDEPATH += ../CCArmature

#INCLUDES = -I$(COCOS_ROOT)/external \

TARGET = $${LIB_OUTPUT_DIR}/extension

HEADERS += \
    ../CocoStudio/Action/CCActionObject.h \
    ../CocoStudio/Action/CCActionNode.h \
    ../CocoStudio/Action/CCActionManagerEx.h \
    ../CocoStudio/Action/CCActionFrameEasing.h \
    ../CocoStudio/Action/CCActionFrame.h \
    ../CocoStudio/Armature/CCBone.h \
    ../CocoStudio/Armature/CCArmature.h \
    ../CocoStudio/Armature/animation/CCTween.h \
    ../CocoStudio/Armature/animation/CCProcessBase.h \
    ../CocoStudio/Armature/animation/CCArmatureAnimation.h \
    ../CocoStudio/Armature/datas/CCDatas.h \
    ../CocoStudio/Armature/display/CCSkin.h \
    ../CocoStudio/Armature/display/CCDisplayManager.h \
    ../CocoStudio/Armature/display/CCDisplayFactory.h \
    ../CocoStudio/Armature/display/CCDecorativeDisplay.h \
    ../CocoStudio/Armature/display/CCBatchNode.h \
    ../CocoStudio/Armature/physics/CCColliderDetector.h \
    ../CocoStudio/Armature/utils/CCUtilMath.h \
    ../CocoStudio/Armature/utils/CCTweenFunction.h \
    ../CocoStudio/Armature/utils/CCTransformHelp.h \
    ../CocoStudio/Armature/utils/CCSpriteFrameCacheHelper.h \
    ../CocoStudio/Armature/utils/CCDataReaderHelper.h \
    ../CocoStudio/Armature/utils/CCArmatureDefine.h \
    ../CocoStudio/Armature/utils/CCArmatureDataManager.h \
    ../CocoStudio/Components/CCInputDelegate.h \
    ../CocoStudio/Components/CCComRender.h \
    ../CocoStudio/Components/CCComController.h \
    ../CocoStudio/Components/CCComAudio.h \
    ../CocoStudio/Components/CCComAttribute.h \
    ../CocoStudio/GUI/BaseClasses/UIWidget.h \
    ../CocoStudio/GUI/BaseClasses/UIRootWidget.h \
    ../CocoStudio/GUI/Layouts/UILayoutDefine.h \
    ../CocoStudio/GUI/Layouts/LayoutParameter.h \
    ../CocoStudio/GUI/Layouts/Layout.h \
    ../CocoStudio/GUI/System/UILayer.h \
    ../CocoStudio/GUI/System/UIInputManager.h \
    ../CocoStudio/GUI/System/UIHelper.h \
    ../CocoStudio/GUI/System/CocosGUI.h \
    ../CocoStudio/GUI/UIWidgets/UITextField.h \
    ../CocoStudio/GUI/UIWidgets/UISlider.h \
    ../CocoStudio/GUI/UIWidgets/UILoadingBar.h \
    ../CocoStudio/GUI/UIWidgets/UILabelBMFont.h \
    ../CocoStudio/GUI/UIWidgets/UILabelAtlas.h \
    ../CocoStudio/GUI/UIWidgets/UILabel.h \
    ../CocoStudio/GUI/UIWidgets/UIImageView.h \
    ../CocoStudio/GUI/UIWidgets/UICheckBox.h \
    ../CocoStudio/GUI/UIWidgets/UIButton.h \
    ../CocoStudio/GUI/UIWidgets/ScrollWidget/UIScrollView.h \
    ../CocoStudio/GUI/UIWidgets/ScrollWidget/UIScrollInterface.h \
    ../CocoStudio/GUI/UIWidgets/ScrollWidget/UIPageView.h \
    ../CocoStudio/GUI/UIWidgets/ScrollWidget/UIListView.h \
    ../CocoStudio/GUI/UIWidgets/ScrollWidget/UIDragPanel.h \
    ../CocoStudio/Json/DictionaryHelper.h \
    ../CocoStudio/Json/CSContentJsonDictionary.h \
    ../CocoStudio/Json/lib_json/writer.h \
    ../CocoStudio/Json/lib_json/value.h \
    ../CocoStudio/Json/lib_json/reader.h \
    ../CocoStudio/Json/lib_json/json_tool.h \
    ../CocoStudio/Json/lib_json/json_lib.h \
    ../CocoStudio/Json/lib_json/json_batchallocator.h \
    ../CocoStudio/Json/lib_json/forwards.h \
    ../CocoStudio/Json/lib_json/features.h \
    ../CocoStudio/Json/lib_json/config.h \
    ../CocoStudio/Json/lib_json/autolink.h \
    ../CocoStudio/Reader/CCSSceneReader.h \
    ../CocoStudio/Reader/CCSGUIReader.h

OTHER_FILES += \
    ../CocoStudio/Json/lib_json/sconscript

