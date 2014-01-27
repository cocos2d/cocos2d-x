set(CS_SRC
  CCActionEaseEx.cpp
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
  DictionaryHelper.cpp
  CCSGUIReader.cpp
  CCSSceneReader.cpp
  ObjectFactory.cpp
  TriggerBase.cpp
  TriggerMng.cpp
  TriggerObj.cpp
)

include_directories(
  ..
)

add_library(cocostudio STATIC
  ${CS_SRC}
)

target_link_libraries(cocostudio
)

set_target_properties(cocostudio
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)

