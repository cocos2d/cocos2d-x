TARGET = libcocosbuilder.a

INCLUDES = 

SOURCES = CCBFileLoader.cpp \
CCMenuItemImageLoader.cpp \
CCBReader.cpp \
CCMenuItemLoader.cpp \
CCControlButtonLoader.cpp \
CCNodeLoader.cpp \
CCControlLoader.cpp \
CCNodeLoaderLibrary.cpp \
CCLabelBMFontLoader.cpp \
CCParticleSystemQuadLoader.cpp \
CCLabelTTFLoader.cpp \
CCScale9SpriteLoader.cpp \
CCLayerColorLoader.cpp \
CCScrollViewLoader.cpp \
CCLayerGradientLoader.cpp \
CCSpriteLoader.cpp \
CCLayerLoader.cpp \
CCBAnimationManager.cpp \
CCBKeyframe.cpp \
CCBSequence.cpp \
CCBSequenceProperty.cpp \
CCBValue.cpp \
CCNode+CCBRelativePositioning.cpp

include ../../2d/cocos2dx.mk

CXXFLAGS += -Wno-multichar

TARGET := $(LIB_DIR)/$(TARGET)

all: $(TARGET)

$(TARGET): $(OBJECTS) $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_AR)$(AR) $(ARFLAGS) $@ $(OBJECTS)

$(OBJ_DIR)/%.o: %.cpp $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_CXX)$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEFINES) -c $< -o $@

