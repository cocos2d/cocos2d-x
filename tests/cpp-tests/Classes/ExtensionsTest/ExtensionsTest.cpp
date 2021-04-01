/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

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
