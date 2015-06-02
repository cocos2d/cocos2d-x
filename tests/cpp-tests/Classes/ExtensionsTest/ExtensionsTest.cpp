#include "ExtensionsTest.h"
#include "../testResource.h"
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT && _MSC_VER < 1900)
// Window 10 UWP does not yet support CURL
#include "AssetsManagerExTest/AssetsManagerExTest.h"
#endif
#include "NotificationCenterTest/NotificationCenterTest.h"
#include "ControlExtensionTest/CCControlSceneManager.h"
#include "CocosBuilderTest/CocosBuilderTest.h"
#if (CC_TARGET_PLATFORM != CC_PLATFORM_EMSCRIPTEN) && (CC_TARGET_PLATFORM != CC_PLATFORM_NACL)
#include "NetworkTest/HttpClientTest.h"
#endif
#include "TableViewTest/TableViewTestScene.h"

#include "CocoStudioArmatureTest/ArmatureScene.h"
#include "CocoStudioActionTimelineTest/ActionTimelineTestScene.h"
#include "CocoStudioComponentsTest/ComponentsTestScene.h"
#include "CocoStudioSceneTest/SceneEditorTest.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) || (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
#include "NetworkTest/WebSocketTest.h"
#include "NetworkTest/SocketIOTest.h"
#endif

ExtensionsTests::ExtensionsTests()
{
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT && _MSC_VER < 1900)
    // Window 10 UWP does not yet support CURL
    addTest("AssetsManagerExTest", [](){ return new (std::nothrow) AssetsManagerExTests; });
#endif
    addTest("NotificationCenterTest", [](){ return new (std::nothrow) NotificationCenterTests; });
    addTest("CCControlButtonTest", [](){ return new (std::nothrow) ControlTests; });
    addTest("CocosBuilderTest", [](){ return new (std::nothrow) CocosBuilderTests; });
#if (CC_TARGET_PLATFORM != CC_PLATFORM_EMSCRIPTEN) && (CC_TARGET_PLATFORM != CC_PLATFORM_NACL)
    addTest("HttpClientTest", [](){ return new (std::nothrow) HttpClientTests; });
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) || (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    addTest("WebSocketTest", [](){ return new (std::nothrow) WebSocketTests; });
    addTest("SocketIOTest", [](){ return new (std::nothrow) SocketIOTests; });
#endif
    addTest("TableViewTest", [](){ return new (std::nothrow) TableViewTests; });
    addTest("CocoStudioArmatureTest", [](){ return new (std::nothrow) CocoStudioArmatureTests; });
    addTest("CocoStudioActionTimelineTest", [](){ return new (std::nothrow) CocoStudioActionTimelineTests; });
    addTest("CocoStudioComponentsTest", [](){ return new (std::nothrow) CocoStudioComponentsTests; });
    addTest("CocoStudioSceneTest", [](){ return new (std::nothrow) CocoStudioSceneEditTests; });
}
