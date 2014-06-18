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
  CCUtilMath.cpp
  CCComAttribute.cpp
  CCComAudio.cpp
  CCComController.cpp
  CCComRender.cpp
  CCInputDelegate.cpp
  DictionaryHelper.cpp
  CCSGUIReader.cpp
  CCSSceneReader.cpp
  TriggerBase.cpp
  TriggerMng.cpp
  TriggerObj.cpp
  WidgetReader/WidgetReader.cpp
  WidgetReader/ButtonReader/ButtonReader.cpp
  WidgetReader/CheckBoxReader/CheckBoxReader.cpp
  WidgetReader/ImageViewReader/ImageViewReader.cpp
  WidgetReader/LayoutReader/LayoutReader.cpp
  WidgetReader/ListViewReader/ListViewReader.cpp
  WidgetReader/LoadingBarReader/LoadingBarReader.cpp
  WidgetReader/PageViewReader/PageViewReader.cpp
  WidgetReader/ScrollViewReader/ScrollViewReader.cpp
  WidgetReader/SliderReader/SliderReader.cpp
  WidgetReader/TextAtlasReader/TextAtlasReader.cpp
  WidgetReader/TextBMFontReader/TextBMFontReader.cpp
  WidgetReader/TextFieldReader/TextFieldReader.cpp
  WidgetReader/TextReader/TextReader.cpp
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

