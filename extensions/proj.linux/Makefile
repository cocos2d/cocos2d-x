TARGET = libextension.a

COCOS_ROOT=../..

INCLUDES = -I$(COCOS_ROOT)/external \
	-I$(COCOS_ROOT)/external/chipmunk/include/chipmunk \
	-I$(COCOS_ROOT)/CocosDenshion/include \
	-I.. \
	-I../CCBReader \
	-I../GUI/CCControlExtension \
	-I../GUI/CCEditBox \
	-I../network \
	-I../CocoStudio/Armature \
	-I../CocoStudio/Components \
	-I../CocoStudio/GUI \
	-I../CocoStudio/Json \
	-I../CocoStudio/Reader \

SOURCES = ../CCBReader/CCBFileLoader.cpp \
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
../CCBReader/CCData.cpp \
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
../CocoStudio/Armature/CCArmature.cpp \
../CocoStudio/Armature/CCBone.cpp \
../CocoStudio/Armature/animation/CCArmatureAnimation.cpp \
../CocoStudio/Armature/animation/CCProcessBase.cpp \
../CocoStudio/Armature/animation/CCTween.cpp \
../CocoStudio/Armature/datas/CCDatas.cpp \
../CocoStudio/Armature/display/CCBatchNode.cpp \
../CocoStudio/Armature/display/CCDecorativeDisplay.cpp \
../CocoStudio/Armature/display/CCDisplayFactory.cpp \
../CocoStudio/Armature/display/CCDisplayManager.cpp \
../CocoStudio/Armature/display/CCSkin.cpp \
../CocoStudio/Armature/physics/CCColliderDetector.cpp \
../CocoStudio/Armature/utils/CCArmatureDefine.cpp \
../CocoStudio/Armature/utils/CCArmatureDataManager.cpp \
../CocoStudio/Armature/utils/CCDataReaderHelper.cpp \
../CocoStudio/Armature/utils/CCSpriteFrameCacheHelper.cpp \
../CocoStudio/Armature/utils/CCTransformHelp.cpp \
../CocoStudio/Armature/utils/CCTweenFunction.cpp \
../CocoStudio/Armature/utils/CCUtilMath.cpp \
../CocoStudio/ActionTimeline/CCActionTimeline.cpp \
../CocoStudio/ActionTimeline/CCActionTimelineCache.cpp \
../CocoStudio/ActionTimeline/CCFrame.cpp \
../CocoStudio/ActionTimeline/CCNodeReader.cpp \
../CocoStudio/ActionTimeline/CCTimeLine.cpp \
../CocoStudio/GUI/BaseClasses/UIWidget.cpp \
../CocoStudio/GUI/Layouts/UILayout.cpp \
../CocoStudio/GUI/Layouts/UILayoutParameter.cpp \
../CocoStudio/GUI/Layouts/UILayoutDefine.cpp \
../CocoStudio/GUI/System/CocosGUI.cpp \
../CocoStudio/GUI/System/UIHelper.cpp \
../CocoStudio/GUI/System/UITouchGroup.cpp \
../CocoStudio/GUI/UIWidgets/ScrollWidget/UIListView.cpp \
../CocoStudio/GUI/UIWidgets/ScrollWidget/UIPageView.cpp \
../CocoStudio/GUI/UIWidgets/ScrollWidget/UIScrollView.cpp \
../CocoStudio/GUI/UIWidgets/UIButton.cpp \
../CocoStudio/GUI/UIWidgets/UICheckBox.cpp \
../CocoStudio/GUI/UIWidgets/UIImageView.cpp \
../CocoStudio/GUI/UIWidgets/UILabel.cpp \
../CocoStudio/GUI/UIWidgets/UILabelAtlas.cpp \
../CocoStudio/GUI/UIWidgets/UILabelBMFont.cpp \
../CocoStudio/GUI/UIWidgets/UILoadingBar.cpp \
../CocoStudio/GUI/UIWidgets/UISlider.cpp \
../CocoStudio/GUI/UIWidgets/UITextField.cpp \
../CocoStudio/GUI/UIWidgets/UIRichText.cpp \
../CocoStudio/Components/CCComAttribute.cpp \
../CocoStudio/Components/CCComAudio.cpp \
../CocoStudio/Components/CCComController.cpp \
../CocoStudio/Components/CCComRender.cpp \
../CocoStudio/Components/CCInputDelegate.cpp \
../CocoStudio/Json/DictionaryHelper.cpp \
../CocoStudio/Json/CocoLoader.cpp \
../CocoStudio/Reader/SceneReader.cpp \
../CocoStudio/Reader/GUIReader.cpp \
../CocoStudio/Reader/WidgetReader/WidgetReader.cpp \
../CocoStudio/Reader/WidgetReader/ButtonReader/ButtonReader.cpp \
../CocoStudio/Reader/WidgetReader/CheckBoxReader/CheckBoxReader.cpp \
../CocoStudio/Reader/WidgetReader/ImageViewReader/ImageViewReader.cpp \
../CocoStudio/Reader/WidgetReader/LabelAtlasReader/LabelAtlasReader.cpp \
../CocoStudio/Reader/WidgetReader/LabelBMFontReader/LabelBMFontReader.cpp \
../CocoStudio/Reader/WidgetReader/LabelReader/LabelReader.cpp \
../CocoStudio/Reader/WidgetReader/LayoutReader/LayoutReader.cpp \
../CocoStudio/Reader/WidgetReader/ListViewReader/ListViewReader.cpp \
../CocoStudio/Reader/WidgetReader/LoadingBarReader/LoadingBarReader.cpp \
../CocoStudio/Reader/WidgetReader/PageViewReader/PageViewReader.cpp \
../CocoStudio/Reader/WidgetReader/ScrollViewReader/ScrollViewReader.cpp \
../CocoStudio/Reader/WidgetReader/SliderReader/SliderReader.cpp \
../CocoStudio/Reader/WidgetReader/TextFieldReader/TextFieldReader.cpp \
../CocoStudio/Action/CCActionManager.cpp \
../CocoStudio/Action/CCActionObject.cpp \
../CocoStudio/Action/CCActionNode.cpp \
../CocoStudio/Action/CCActionFrame.cpp \
../CocoStudio/Action/CCActionEaseEx.cpp \
../CocoStudio/Action/CCActionFrameEasing.cpp \
../CocoStudio/Trigger/ObjectFactory.cpp \
../CocoStudio/Trigger/TriggerBase.cpp \
../CocoStudio/Trigger/TriggerMng.cpp \
../CocoStudio/Trigger/TriggerObj.cpp \

include $(COCOS_ROOT)/cocos2dx/proj.linux/cocos2dx.mk

CXXFLAGS += -Wno-multichar -Wno-delete-non-virtual-dtor

TARGET := $(LIB_DIR)/$(TARGET)

all: $(TARGET)

$(TARGET): $(OBJECTS) $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_AR)$(AR) $(ARFLAGS) $@ $(OBJECTS)

$(OBJ_DIR)/%.o: ../%.cpp $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_CXX)$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEFINES) -c $< -o $@

$(OBJ_DIR)/%.o: ../%.c $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_CC)$(CC) $(CCFLAGS) $(INCLUDES) $(DEFINES) -c $< -o $@
