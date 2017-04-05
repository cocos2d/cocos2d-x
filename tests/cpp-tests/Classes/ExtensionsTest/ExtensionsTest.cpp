#include "ExtensionsTest.h"
#include "../testResource.h"
#include "AssetsManagerExTest/AssetsManagerExTest.h"
#include "NetworkTest/HttpClientTest.h"
#include "TableViewTest/TableViewTestScene.h"

#include "NetworkTest/WebSocketTest.h"
#include "NetworkTest/SocketIOTest.h"

ExtensionsTests::ExtensionsTests()
{
    addTest("AssetsManagerExTest", [](){ return new (std::nothrow) AssetsManagerExTests; });
    addTest("HttpClientTest", [](){ return new (std::nothrow) HttpClientTests; });
    addTest("WebSocketTest", [](){ return new (std::nothrow) WebSocketTests; });
    addTest("SocketIOTest", [](){ return new (std::nothrow) SocketIOTests; });
    addTest("TableViewTest", [](){ return new (std::nothrow) TableViewTests; });
}
