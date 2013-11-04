set(CS_SRC
  CCActionFrame.cpp
  CCActionFrameEasing.cpp
  CCActionManagerEx.cpp
  CCActionNode.cpp
  CCActionObject.cpp
  CCArmature.cpp
  CCBone.cpp
  CCArmatureAnimation.cpp
  CCProcessBase.cpp
  CCTween.cpp
  CCDatas.cpp
  CCBatchNode.cpp
  CCDecorativeDisplay.cpp
  CCDisplayFactory.cpp
  CCDisplayManager.cpp
  CCSkin.cpp
  CCColliderDetector.cpp
  CCArmatureDataManager.cpp
  CCArmatureDefine.cpp
  CCDataReaderHelper.cpp
  CCSpriteFrameCacheHelper.cpp
  CCTransformHelp.cpp
  CCTweenFunction.cpp
  CCUtilMath.cpp
  CCComAttribute.cpp
  CCComAudio.cpp
  CCComController.cpp
  CCComRender.cpp
  CCInputDelegate.cpp
  CSContentJsonDictionary.cpp
  DictionaryHelper.cpp
  CCSGUIReader.cpp
  CCSSceneReader.cpp
)

include_directories(
  ..
)

add_library(cocostudio STATIC
  ${CS_SRC}
)

target_link_libraries(cocostudio
  jsoncpp
)

set_target_properties(cocostudio
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib"
)

