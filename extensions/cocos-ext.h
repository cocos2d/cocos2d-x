#ifndef __COCOS2D_EXT_H__
#define __COCOS2D_EXT_H__

#include "ExtensionMacros.h"

#include "CCBReader/CCBFileLoader.h"
#include "CCBReader/CCBMemberVariableAssigner.h"
#include "CCBReader/CCBReader.h"
#include "CCBReader/CCBSelectorResolver.h"
#include "CCBReader/CCControlButtonLoader.h"
#include "CCBReader/CCControlLoader.h"
#include "CCBReader/CCLabelBMFontLoader.h"
#include "CCBReader/CCLabelTTFLoader.h"
#include "CCBReader/CCLayerColorLoader.h"
#include "CCBReader/CCLayerGradientLoader.h"
#include "CCBReader/CCLayerLoader.h"
#include "CCBReader/CCMenuItemImageLoader.h"
#include "CCBReader/CCMenuItemLoader.h"
#include "CCBReader/CCMenuLoader.h"
#include "CCBReader/CCNodeLoader.h"
#include "CCBReader/CCNodeLoaderLibrary.h"
#include "CCBReader/CCNodeLoaderListener.h"
#include "CCBReader/CCParticleSystemQuadLoader.h"
#include "CCBReader/CCScale9SpriteLoader.h"
#include "CCBReader/CCScrollViewLoader.h"
#include "CCBReader/CCSpriteLoader.h"
#include "CCBReader/CCBAnimationManager.h"
#include "CCBReader/CCBKeyframe.h"
#include "CCBReader/CCBSequence.h"
#include "CCBReader/CCBSequenceProperty.h"
#include "CCBReader/CCBValue.h"
#include "CCBReader/CCNode+CCBRelativePositioning.h"

#include "GUI/CCControlExtension/CCControlExtensions.h"
#include "GUI/CCScrollView/CCScrollView.h"
#include "GUI/CCScrollView/CCTableView.h"
#include "GUI/CCEditBox/CCEditBox.h"

#include "network/HttpRequest.h"
#include "network/HttpResponse.h"
#include "network/HttpClient.h"
#include "network/WebSocket.h"
#include "network/SocketIO.h"

// Physics integration
#if CC_ENABLE_CHIPMUNK_INTEGRATION || CC_ENABLE_BOX2D_INTEGRATION
#include "physics_nodes/CCPhysicsDebugNode.h"
#include "physics_nodes/CCPhysicsSprite.h"
#endif

#include "spine/spine-cocos2dx.h"

#include "CocoStudio/Armature/CCArmature.h"
#include "CocoStudio/Armature/CCBone.h"
#include "CocoStudio/Armature/animation/CCArmatureAnimation.h"
#include "CocoStudio/Armature/datas/CCDatas.h"
#include "CocoStudio/Armature/display/CCBatchNode.h"
#include "CocoStudio/Armature/display/CCDecorativeDisplay.h"
#include "CocoStudio/Armature/display/CCDisplayManager.h"
#include "CocoStudio/Armature/display/CCSkin.h"
#include "CocoStudio/Armature/physics/CCColliderDetector.h"
#include "CocoStudio/Armature/utils/CCArmatureDataManager.h"
#include "CocoStudio/Armature/utils/CCDataReaderHelper.h"
#include "CocoStudio/Armature/utils/CCTweenFunction.h"
#include "CocoStudio/Armature/utils/CCArmatureDataManager.h"

#include "CocoStudio/Components/CCComAttribute.h"
#include "CocoStudio/Components/CCComAudio.h"
#include "CocoStudio/Components/CCComController.h"
#include "CocoStudio/Components/CCComRender.h"

#include "CocoStudio/GUI/System/CocosGUI.h"

#include "CocoStudio/Json/CSContentJsonDictionary.h"
#include "CocoStudio/Json/DictionaryHelper.h"

#include "CocoStudio/Reader/CCSSceneReader.h"
#include "CocoStudio/Reader/CCSGUIReader.h"

#include "CocoStudio/Action/CCActionManagerEx.h"

#include "CCDeprecated-ext.h"

#include "AssetsManager/AssetsManager.h"

#endif /* __COCOS2D_EXT_H__ */
