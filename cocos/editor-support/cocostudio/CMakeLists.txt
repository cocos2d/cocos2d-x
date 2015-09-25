
if(WINDOWS AND BUILD_SHARED_LIBS)
  ADD_DEFINITIONS (-D_USRSTUDIODLL)
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ")

set(COCOS_CS_SRC

  editor-support/cocostudio/CCActionFrame.cpp
  editor-support/cocostudio/CCActionFrameEasing.cpp
  editor-support/cocostudio/CCActionManagerEx.cpp
  editor-support/cocostudio/CCActionNode.cpp
  editor-support/cocostudio/CCActionObject.cpp
  editor-support/cocostudio/CCArmature.cpp
  editor-support/cocostudio/CCArmatureAnimation.cpp
  editor-support/cocostudio/CCArmatureDataManager.cpp
  editor-support/cocostudio/CCArmatureDefine.cpp
  editor-support/cocostudio/CCBatchNode.cpp
  editor-support/cocostudio/CCBone.cpp
  editor-support/cocostudio/CCColliderDetector.cpp
  editor-support/cocostudio/CCComAttribute.cpp
  editor-support/cocostudio/CCComAudio.cpp
  editor-support/cocostudio/CCComController.cpp
  editor-support/cocostudio/CCComRender.cpp
  editor-support/cocostudio/CCDataReaderHelper.cpp
  editor-support/cocostudio/CCDatas.cpp
  editor-support/cocostudio/CCDecorativeDisplay.cpp
  editor-support/cocostudio/CCDisplayFactory.cpp
  editor-support/cocostudio/CCDisplayManager.cpp
  editor-support/cocostudio/CCInputDelegate.cpp
  editor-support/cocostudio/CCProcessBase.cpp
  editor-support/cocostudio/CCSGUIReader.cpp
  editor-support/cocostudio/CCSSceneReader.cpp
  editor-support/cocostudio/CCSkin.cpp
  editor-support/cocostudio/CCSpriteFrameCacheHelper.cpp
  editor-support/cocostudio/CCTransformHelp.cpp
  editor-support/cocostudio/CCTween.cpp
  editor-support/cocostudio/CCUtilMath.cpp
  editor-support/cocostudio/CocoLoader.cpp
  editor-support/cocostudio/DictionaryHelper.cpp
  editor-support/cocostudio/TriggerBase.cpp
  editor-support/cocostudio/TriggerMng.cpp
  editor-support/cocostudio/TriggerObj.cpp
  editor-support/cocostudio/FlatBuffersSerialize.cpp
  editor-support/cocostudio/CCComExtensionData.cpp
  editor-support/cocostudio/CocoStudio.cpp
  editor-support/cocostudio/WidgetReader/NodeReader/NodeReader.cpp
  editor-support/cocostudio/WidgetReader/SingleNodeReader/SingleNodeReader.cpp
  editor-support/cocostudio/WidgetReader/SpriteReader/SpriteReader.cpp 
  editor-support/cocostudio/WidgetReader/ParticleReader/ParticleReader.cpp 
  editor-support/cocostudio/WidgetReader/GameMapReader/GameMapReader.cpp 
  editor-support/cocostudio/WidgetReader/ProjectNodeReader/ProjectNodeReader.cpp 
  editor-support/cocostudio/WidgetReader/ComAudioReader/ComAudioReader.cpp 
  editor-support/cocostudio/WidgetReader/WidgetReader.cpp
  editor-support/cocostudio/WidgetReader/LoadingBarReader/LoadingBarReader.cpp
  editor-support/cocostudio/WidgetReader/ListViewReader/ListViewReader.cpp
  editor-support/cocostudio/WidgetReader/TextFieldReader/TextFieldReader.cpp
  editor-support/cocostudio/WidgetReader/WidgetReader.cpp
  editor-support/cocostudio/WidgetReader/CheckBoxReader/CheckBoxReader.cpp
  editor-support/cocostudio/WidgetReader/SliderReader/SliderReader.cpp
  editor-support/cocostudio/WidgetReader/PageViewReader/PageViewReader.cpp
  editor-support/cocostudio/WidgetReader/TextReader/TextReader.cpp
  editor-support/cocostudio/WidgetReader/Node3DReader/Node3DReader.cpp
  editor-support/cocostudio/WidgetReader/UserCameraReader/UserCameraReader.cpp
  editor-support/cocostudio/WidgetReader/Particle3DReader/Particle3DReader.cpp    
  editor-support/cocostudio/WidgetReader/Sprite3DReader/Sprite3DReader.cpp
  editor-support/cocostudio/WidgetReader/SkeletonReader/BoneNodeReader.cpp
  editor-support/cocostudio/WidgetReader/SkeletonReader/SkeletonNodeReader.cpp
  editor-support/cocostudio/WidgetReader/TextAtlasReader/TextAtlasReader.cpp
  editor-support/cocostudio/WidgetReader/LayoutReader/LayoutReader.cpp
  editor-support/cocostudio/WidgetReader/TextBMFontReader/TextBMFontReader.cpp
  editor-support/cocostudio/WidgetReader/ImageViewReader/ImageViewReader.cpp
  editor-support/cocostudio/WidgetReader/ButtonReader/ButtonReader.cpp
  editor-support/cocostudio/WidgetReader/ScrollViewReader/ScrollViewReader.cpp
  editor-support/cocostudio/WidgetReader/GameNode3DReader/GameNode3DReader.cpp
  editor-support/cocostudio/ActionTimeline/CCActionTimelineCache.cpp
  editor-support/cocostudio/ActionTimeline/CCActionTimeline.cpp
  editor-support/cocostudio/ActionTimeline/CCActionTimelineNode.cpp
  editor-support/cocostudio/ActionTimeline/CCFrame.cpp
  editor-support/cocostudio/ActionTimeline/CCTimeLine.cpp
  editor-support/cocostudio/ActionTimeline/CSLoader.cpp
  editor-support/cocostudio/ActionTimeline/CCBoneNode.cpp
  editor-support/cocostudio/ActionTimeline/CCSkeletonNode.cpp
  editor-support/cocostudio/ActionTimeline/CCSkinNode.cpp
  editor-support/cocostudio/FlatBuffersSerialize.cpp
  editor-support/cocostudio/WidgetReader/ArmatureNodeReader/ArmatureNodeReader.cpp
)

include_directories( editor-support )
