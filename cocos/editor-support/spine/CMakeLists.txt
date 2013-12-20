set(SPINE_SRC
  Animation.cpp
  AnimationState.cpp
  AnimationStateData.cpp
  Atlas.cpp
  AtlasAttachmentLoader.cpp
  Attachment.cpp
  AttachmentLoader.cpp
  Bone.cpp
  BoneData.cpp
  Json.cpp
  RegionAttachment.cpp
  Skeleton.cpp
  SkeletonData.cpp
  SkeletonJson.cpp
  Skin.cpp
  Slot.cpp
  SlotData.cpp
  extension.cpp
  spine-cocos2dx.cpp
  CCSkeleton.cpp
  CCSkeletonAnimation.cpp
)

include_directories(
  ..
)

add_library(spine STATIC
  ${SPINE_SRC}
)

set_target_properties(spine
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib"
)

