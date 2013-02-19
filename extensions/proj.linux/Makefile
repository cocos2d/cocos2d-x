CC      = gcc
CXX     = g++
AR      = ar
TARGET	= libextension.a
CCFLAGS = -Wall
CXXFLAGS = -Wall
ARFLAGS = cr

COCOS2DX_ROOT=../..

INCLUDES =  -I$(COCOS2DX_ROOT)/cocos2dx \
			-I$(COCOS2DX_ROOT)/cocos2dx/platform/third_party/linux/libfreetype2 \
			-I$(COCOS2DX_ROOT)/cocos2dx/include \
			-I$(COCOS2DX_ROOT)/cocos2dx/kazmath/include \
			-I$(COCOS2DX_ROOT)/cocos2dx/platform/linux \
			-I$(COCOS2DX_ROOT)/cocos2dx/platform/third_party/linux/libpng \
			-I$(COCOS2DX_ROOT)/cocos2dx/platform/third_party/linux/libjpeg \
			-I$(COCOS2DX_ROOT)/cocos2dx/platform/third_party/linux/libtiff/include \
			-I$(COCOS2DX_ROOT)/cocos2dx/platform/third_party/linux/libwebp \
			-I$(COCOS2DX_ROOT)/external \
			-I$(COCOS2DX_ROOT)/external/chipmunk/include/chipmunk \
			-I.. \
			-I../CCBReader \
			-I../GUI/CCControlExtension \
			-I../network 

DEFINES = -DLINUX
DEFINES += -DCC_ENABLE_CHIPMUNK_INTEGRATION=1
DEFINES += -D__CC_PLATFORM_IMAGE_CPP__

OBJECTS = ../CCBReader/CCBFileLoader.o \
../CCBReader/CCMenuItemImageLoader.o \
../CCBReader/CCBReader.o \
../CCBReader/CCMenuItemLoader.o \
../CCBReader/CCControlButtonLoader.o \
../CCBReader/CCNodeLoader.o \
../CCBReader/CCControlLoader.o \
../CCBReader/CCNodeLoaderLibrary.o \
../CCBReader/CCLabelBMFontLoader.o \
../CCBReader/CCParticleSystemQuadLoader.o \
../CCBReader/CCLabelTTFLoader.o \
../CCBReader/CCScale9SpriteLoader.o \
../CCBReader/CCLayerColorLoader.o \
../CCBReader/CCScrollViewLoader.o \
../CCBReader/CCLayerGradientLoader.o \
../CCBReader/CCSpriteLoader.o \
../CCBReader/CCLayerLoader.o \
../CCBReader/CCBAnimationManager.o \
../CCBReader/CCBKeyframe.o \
../CCBReader/CCBSequence.o \
../CCBReader/CCBSequenceProperty.o \
../CCBReader/CCBValue.o \
../CCBReader/CCData.o \
../CCBReader/CCNode+CCBRelativePositioning.o \
../GUI/CCScrollView/CCScrollView.o \
../GUI/CCScrollView/CCSorting.o \
../GUI/CCScrollView/CCTableView.o \
../GUI/CCScrollView/CCTableViewCell.o \
../GUI/CCControlExtension/CCControlButton.o \
../GUI/CCControlExtension/CCControlColourPicker.o \
../GUI/CCControlExtension/CCControl.o \
../GUI/CCControlExtension/CCControlHuePicker.o \
../GUI/CCControlExtension/CCControlSaturationBrightnessPicker.o \
../GUI/CCControlExtension/CCControlSlider.o \
../GUI/CCControlExtension/CCControlSwitch.o \
../GUI/CCControlExtension/CCControlUtils.o \
../GUI/CCControlExtension/CCInvocation.o \
../GUI/CCControlExtension/CCScale9Sprite.o \
../GUI/CCControlExtension/CCControlPotentiometer.o \
../GUI/CCControlExtension/CCControlStepper.o \
../network/HttpClient.o \
../physics_nodes/CCPhysicsDebugNode.o \
../physics_nodes/CCPhysicsSprite.o 


debug: CCFLAGS += -g3 -O0
debug: CXXFLAGS += -g3 -O0
debug: DEFINES += -DDEBUG
debug: $(TARGET)

release: CCFLAGS += -O3
release: CXXFLAGS += -O3
release: DEFINES += -DNDEBUG
release: $(TARGET)

####### Build rules
$(TARGET): $(OBJECTS) 
	$(AR) $(ARFLAGS) $(TARGET) $(OBJECTS)  

####### Compile
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEFINES) -c $< -o $@

%.o: %.c
	$(CC) $(CCFLAGS) $(INCLUDES) $(DEFINES) -c $< -o $@

clean: 
	rm -f $(OBJECTS) $(TARGET) core


