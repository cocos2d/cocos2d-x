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
  BoundingBoxAttachment.cpp
  Event.cpp
  EventData.cpp
  Json.cpp
  RegionAttachment.cpp
  Skeleton.cpp
  SkeletonBounds.cpp
  SkeletonData.cpp
  SkeletonJson.cpp
  Skin.cpp
  Slot.cpp
  SlotData.cpp
  Slot.cpp
  SlotData.cpp
  extension.cpp
  spine-cocos2dx.cpp
  CCSkeleton.cpp
  CCSkeletonAnimation.cpp
  BoundingBoxAttachment.cpp
  Event.cpp
  EventData.cpp
  SkeletonBounds.cpp
)

include_directories( .. )

add_library(spine STATIC ${SPINE_SRC})

set_target_properties(spine
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)

