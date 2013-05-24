TARGET = libextension.a

COCOS_ROOT=../..

INCLUDES = -I$(COCOS_ROOT)/external \
	-I$(COCOS_ROOT)/external/chipmunk/include/chipmunk \
	-I$(COCOS_ROOT)/CocosDenshion/include \
	-I.. \
	-I../CCBReader \
	-I../GUI/CCControlExtension \
	-I../network
	-I../GUI/CCEditBox \

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
../physics_nodes/CCPhysicsSprite.cpp

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
