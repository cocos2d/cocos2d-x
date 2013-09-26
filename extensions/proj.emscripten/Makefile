TARGET = libextension.a

COCOS_ROOT=../..

INCLUDES = -I$(COCOS_ROOT)/external \
	-I$(COCOS_ROOT)/external/chipmunk/include/chipmunk \
	-I$(COCOS_ROOT)/CocosDenshion/include \
	-I.. \
	-I../CCBReader \
	-I../GUI/CCControlExtension \
	-I../network \
	-I../GUI/CCEditBox \
	-I../CocoStudio/Armature \
	-I../CocoStudio/Components \
	-I../CocoStudio/GUI \
	-I../CocoStudio/Json \
	-I../CocoStudio/Reader \

DEFINES += -DCC_ENABLE_CHIPMUNK_INTEGRATION=1
DEFINES += -D__CC_PLATFORM_IMAGE_CPP__

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
../CocoStudio/Armature/utils/CCArmatureDataManager.cpp \
../CocoStudio/Armature/utils/CCArmatureDefine.cpp \
../CocoStudio/Armature/utils/CCDataReaderHelper.cpp \
../CocoStudio/Armature/utils/CCSpriteFrameCacheHelper.cpp \
../CocoStudio/Armature/utils/CCTransformHelp.cpp \
../CocoStudio/Armature/utils/CCTweenFunction.cpp \
../CocoStudio/Armature/utils/CCUtilMath.cpp \
../CocoStudio/GUI/BaseClasses/UIRootWidget.cpp \
../CocoStudio/GUI/BaseClasses/UIWidget.cpp \
../CocoStudio/GUI/Layouts/Layout.cpp \
../CocoStudio/GUI/Layouts/LayoutParameter.cpp \
../CocoStudio/GUI/Layouts/UILayoutDefine.cpp \
../CocoStudio/GUI/System/CocosGUI.cpp \
../CocoStudio/GUI/System/UIHelper.cpp \
../CocoStudio/GUI/System/UIInputManager.cpp \
../CocoStudio/GUI/System/UILayer.cpp \
../CocoStudio/GUI/UIWidgets/ScrollWidget/UIDragPanel.cpp \
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
../CocoStudio/GUI/UIWidgets/UISwitch.cpp \
../CocoStudio/GUI/UIWidgets/UITextField.cpp \
../CocoStudio/Components/CCComAttribute.cpp \
../CocoStudio/Components/CCComAudio.cpp \
../CocoStudio/Components/CCComController.cpp \
../CocoStudio/Components/CCComRender.cpp \
../CocoStudio/Components/CCInputDelegate.cpp \
../CocoStudio/Json/CSContentJsonDictionary.cpp \
../CocoStudio/Json/DictionaryHelper.cpp \
../CocoStudio/Json/lib_json/json_value.cpp \
../CocoStudio/Json/lib_json/json_reader.cpp \
../CocoStudio/Json/lib_json/json_writer.cpp \
../CocoStudio/Reader/CCSSceneReader.cpp \
../CocoStudio/Reader/CCSGUIReader.cpp \
../CocoStudio/Action/CCActionManager.cpp \
../CocoStudio/Action/CCActionObject.cpp \
../CocoStudio/Action/CCActionNode.cpp \
../CocoStudio/Action/CCActionFrame.cpp \
../CocoStudio/Action/CCActionFrameEasing.cpp \

include $(COCOS_ROOT)/cocos2dx/proj.emscripten/cocos2dx.mk

CXXFLAGS += -Wno-multichar

TARGET := $(LIB_DIR)/$(TARGET)

all: $(TARGET)

$(TARGET): $(OBJECTS) $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(AR) $(ARFLAGS) $@ $(OBJECTS)

$(OBJ_DIR)/%.o: ../%.cpp $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEFINES) -c $< -o $@

$(OBJ_DIR)/%.o: ../%.c $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(CC) $(CCFLAGS) $(INCLUDES) $(DEFINES) -c $< -o $@
