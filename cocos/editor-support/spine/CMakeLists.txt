
project(SPINE)

#===============================================================================
# Define Spine target.
set(SPINE_TARGET "spine" CACHE INTERNAL "")
add_library(${SPINE_TARGET} STATIC ${CMAKE_CURRENT_LIST_FILE})
cocos_tweak_target_output_directory(${SPINE_TARGET})

set_target_properties(${SPINE_TARGET} PROPERTIES
    FOLDER "external"
    )

#===============================================================================
# Add include directories.
target_include_directories(${SPINE_TARGET} PRIVATE "..")

#===============================================================================
# Add sources.
set(spine_src
    ${CMAKE_CURRENT_LIST_FILE}
    Animation.c
    AnimationState.c
    AnimationStateData.c
    Atlas.c
    AtlasAttachmentLoader.c
    Attachment.c
    AttachmentLoader.c
    Bone.c
    BoneData.c
    BoundingBoxAttachment.c
    Event.c
    EventData.c
    extension.c
    IkConstraint.c
    IkConstraintData.c
    Json.c
    MeshAttachment.c
    PolygonBatch.cpp
    RegionAttachment.c
    Skeleton.c
    SkeletonAnimation.cpp
    SkeletonBounds.c
    SkeletonData.c
    SkeletonJson.c
    SkeletonRenderer.cpp
    Skin.c
    SkinnedMeshAttachment.c
    Slot.c
    SlotData.c
    spine-cocos2dx.cpp
)
file(GLOB spine_header ${CMAKE_CURRENT_LIST_DIR} "*.h")

target_sources(${SPINE_TARGET} PRIVATE ${spine_src} ${spine_header})

#===============================================================================
# Link dependent libraries.
target_link_libraries(${SPINE_TARGET} ${COCOS2D_TARGET})

