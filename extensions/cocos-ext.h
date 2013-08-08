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
#include "CCBReader/CCData.h"
#include "CCBReader/CCNode+CCBRelativePositioning.h"

#include "GUI/CCControlExtension/CCControlExtensions.h"
#include "GUI/CCScrollView/CCScrollView.h"
#include "GUI/CCScrollView/CCTableView.h"
#include "GUI/CCEditBox/CCEditBox.h"

#include "network/HttpRequest.h"
#include "network/HttpResponse.h"
#include "network/HttpClient.h"

#include "CCArmature/CCArmature.h"
#include "CCArmature/CCBone.h"
#include "CCArmature/animation/CCArmatureAnimation.h"
#include "CCArmature/datas/CCDatas.h"
#include "CCArmature/display/CCBatchNode.h"
#include "CCArmature/display/CCDecorativeDisplay.h"
#include "CCArmature/display/CCDisplayManager.h"
#include "CCArmature/display/CCSkin.h"
#include "CCArmature/physics/CCColliderDetector.h"
#include "CCArmature/utils/CCArmatureDataManager.h"
#include "CCArmature/utils/CCDataReaderHelper.h"
#include "CCArmature/utils/CCTweenFunction.h"
#include "CCArmature/external_tool/sigslot.h"
// Physics integration
#if CC_ENABLE_CHIPMUNK_INTEGRATION || CC_ENABLE_BOX2D_INTEGRATION
#include "physics_nodes/CCPhysicsDebugNode.h"
#include "physics_nodes/CCPhysicsSprite.h"
#endif

#include "spine/spine-cocos2dx.h"

#include "Components/CCComAttribute.h"
#include "Components/CCComAudio.h"
#include "Components/CCComController.h"
#include "Components/CCComRender.h"

#include "CocostudioReader/CCJsonReader.h"
#include "CocoGUILIB/System/CocosGUI.h"
#endif /* __COCOS2D_EXT_H__ */
