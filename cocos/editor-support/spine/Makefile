TARGET = libspine.a

INCLUDES = -I..

SOURCES = Animation.cpp \
AnimationState.cpp \
AnimationStateData.cpp \
Atlas.cpp \
AtlasAttachmentLoader.cpp \
Attachment.cpp \
AttachmentLoader.cpp \
Bone.cpp \
BoneData.cpp \
Json.cpp \
RegionAttachment.cpp \
Skeleton.cpp \
SkeletonData.cpp \
SkeletonJson.cpp \
Skin.cpp \
Slot.cpp \
SlotData.cpp \
extension.cpp \
spine-cocos2dx.cpp \
CCSkeleton.cpp \
CCSkeletonAnimation.cpp

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

