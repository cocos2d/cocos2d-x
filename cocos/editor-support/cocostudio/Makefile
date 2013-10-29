TARGET = libcocostudio.a

COCOS_ROOT=../../..

INCLUDES = -I../../2d \
-I../../../external \
-I.. \
-I../.. \

SOURCES = CCActionFrame.cpp \
CCActionFrameEasing.cpp \
CCActionManagerEx.cpp \
CCActionNode.cpp \
CCActionObject.cpp \
CCArmature.cpp \
CCBone.cpp \
CCArmatureAnimation.cpp \
CCProcessBase.cpp \
CCTween.cpp \
CCDatas.cpp \
CCBatchNode.cpp \
CCDecorativeDisplay.cpp \
CCDisplayFactory.cpp \
CCDisplayManager.cpp \
CCSkin.cpp \
CCColliderDetector.cpp \
CCArmatureDataManager.cpp \
CCArmatureDefine.cpp \
CCDataReaderHelper.cpp \
CCSpriteFrameCacheHelper.cpp \
CCTransformHelp.cpp \
CCTweenFunction.cpp \
CCUtilMath.cpp \
CCComAttribute.cpp \
CCComAudio.cpp \
CCComController.cpp \
CCComRender.cpp \
CCInputDelegate.cpp \
CSContentJsonDictionary.cpp \
DictionaryHelper.cpp \
CCSGUIReader.cpp \
CCSSceneReader.cpp \
../../../external/json/json_reader.cpp \
../../../external/json/json_value.cpp \
../../../external/json/json_writer.cpp

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

$(OBJ_DIR)/%.o: ../../../%.cpp $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_CXX)$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEFINES) -c $< -o $@

$(OBJ_DIR)/%.o: %.c $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_CC)$(CC) $(CCFLAGS) $(INCLUDES) $(DEFINES) -c $< -o $@
