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

#ifndef _TILEMAP_TEST_H_
#define _TILEMAP_TEST_H_

#include "../BaseTest.h"

DEFINE_TEST_SUITE(TileMapTests);

class TileDemo : public TestCase
{
public:
    TileDemo();
    virtual ~TileDemo();

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual void onExit() override;

    void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
};

class TileMapTest : public TileDemo
{
public:
    CREATE_FUNC(TileMapTest);
    TileMapTest();
    virtual std::string title() const override;
};

class TileMapEditTest : public TileDemo
{
public:
    CREATE_FUNC(TileMapEditTest);
    TileMapEditTest ();
    virtual std::string title() const override;

    void updateMap(float dt);
};

class TMXOrthoTest : public TileDemo
{
public:
    CREATE_FUNC(TMXOrthoTest);
    TMXOrthoTest();
    virtual std::string title() const override;

    virtual void onEnter() override;
    virtual void onExit() override;
};

class TMXStaggeredTest : public TileDemo
{
public:
    CREATE_FUNC(TMXStaggeredTest);
    TMXStaggeredTest();
    virtual std::string title() const override;
    
    virtual void onEnter() override;
    virtual void onExit() override;
};

class TMXOrthoTest2 : public TileDemo
{
public:
    CREATE_FUNC(TMXOrthoTest2);
    TMXOrthoTest2();
    virtual std::string title() const override;
};

class TMXOrthoTest3 : public TileDemo
{
public:
    CREATE_FUNC(TMXOrthoTest3);
    TMXOrthoTest3();
    virtual std::string title() const override;
};

class TMXOrthoTest4 : public TileDemo
{
public:
    CREATE_FUNC(TMXOrthoTest4);
    TMXOrthoTest4();
    void removeSprite(float dt);
    virtual std::string title() const override;
};

class TMXReadWriteTest : public TileDemo
{
    unsigned int _gid;
    unsigned int _gid2;
public:
    CREATE_FUNC(TMXReadWriteTest);
    TMXReadWriteTest();
    virtual std::string title() const override;

    void removeSprite(Node* sender);
    void updateCol(float dt);
    void repaintWithGID(float dt);
    void removeTiles(float dt);
};

class TMXHexTest : public TileDemo
{
public:
    CREATE_FUNC(TMXHexTest);
    TMXHexTest();
    virtual std::string title() const override;
};

class TMXIsoTest : public TileDemo
{
public:
    CREATE_FUNC(TMXIsoTest);
    TMXIsoTest();
    virtual std::string title() const override;
};

class TMXIsoTest1 : public TileDemo
{
public:
    CREATE_FUNC(TMXIsoTest1);
    TMXIsoTest1();
    virtual std::string title() const override;
};

class TMXIsoTest2 : public TileDemo
{
public:
    CREATE_FUNC(TMXIsoTest2);
    TMXIsoTest2();
    virtual std::string title() const override;
};

class TMXUncompressedTest : public TileDemo
{
public:
    CREATE_FUNC(TMXUncompressedTest);
    TMXUncompressedTest();
    virtual std::string title() const override;
};

class TMXTilesetTest : public TileDemo
{
public:
    CREATE_FUNC(TMXTilesetTest);
    TMXTilesetTest();
    virtual std::string title() const override;
};

class TMXCvsFormatTest : public TileDemo
{
public:
    CREATE_FUNC(TMXCvsFormatTest);
    TMXCvsFormatTest();
    virtual std::string title() const override;
};

class TMXOrthoObjectsTest : public TileDemo
{
public:
    CREATE_FUNC(TMXOrthoObjectsTest);
    TMXOrthoObjectsTest();
    virtual std::string title() const override;

    virtual std::string subtitle() const override;
};

class TMXIsoObjectsTest : public TileDemo
{
public:
    CREATE_FUNC(TMXIsoObjectsTest);
    TMXIsoObjectsTest();
    virtual std::string title() const override;

    virtual std::string subtitle() const override;
};

class TMXResizeTest : public TileDemo
{
public:
    CREATE_FUNC(TMXResizeTest);
    TMXResizeTest();
    virtual std::string title() const override;

    virtual std::string subtitle() const override;
};

class TMXIsoZorder : public TileDemo
{
    cocos2d::Sprite*    _tamara;
public:
    CREATE_FUNC(TMXIsoZorder);
    TMXIsoZorder();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual void onExit()override;

    ~TMXIsoZorder();
    void repositionSprite(float dt);
};

class TMXOrthoZorder : public TileDemo
{
    cocos2d::Sprite*    _tamara;
public:
    CREATE_FUNC(TMXOrthoZorder);
    TMXOrthoZorder();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;

    virtual ~TMXOrthoZorder();
    void repositionSprite(float dt);
};

class TMXIsoVertexZ : public TileDemo
{
    cocos2d::Sprite*    _tamara;
public:
    CREATE_FUNC(TMXIsoVertexZ);
    TMXIsoVertexZ();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;

    ~TMXIsoVertexZ();
    void repositionSprite(float dt);
    virtual void onEnter() override;
    virtual void onExit() override;
};

class TMXOrthoVertexZ : public TileDemo
{
    cocos2d::Sprite*    _tamara;
public:
    CREATE_FUNC(TMXOrthoVertexZ);
    TMXOrthoVertexZ();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;

    ~TMXOrthoVertexZ();
    void repositionSprite(float dt);
    virtual void onEnter() override;
    virtual void onExit() override;
};

class TMXIsoMoveLayer : public TileDemo
{
public:
    CREATE_FUNC(TMXIsoMoveLayer);
    TMXIsoMoveLayer();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class TMXOrthoMoveLayer : public TileDemo
{
public:
    CREATE_FUNC(TMXOrthoMoveLayer);
    TMXOrthoMoveLayer();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class TMXTilePropertyTest : public TileDemo
{
public:
    CREATE_FUNC(TMXTilePropertyTest);
    TMXTilePropertyTest();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class TMXOrthoFlipTest : public TileDemo
{
public:
    CREATE_FUNC(TMXOrthoFlipTest);
    TMXOrthoFlipTest();
    virtual std::string title() const override;
};

class TMXOrthoFlipRunTimeTest : public TileDemo
{
public:
    CREATE_FUNC(TMXOrthoFlipRunTimeTest);
    TMXOrthoFlipRunTimeTest();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    void flipIt(float dt);
};

class TMXOrthoFromXMLTest : public TileDemo
{
public:
    CREATE_FUNC(TMXOrthoFromXMLTest);
    TMXOrthoFromXMLTest();
    virtual std::string title() const override;
};

class TMXOrthoXMLFormatTest : public TileDemo
{
public:
    CREATE_FUNC(TMXOrthoXMLFormatTest);
    TMXOrthoXMLFormatTest();
    virtual std::string title() const override;
};

class TMXBug987 : public TileDemo
{
public:
    CREATE_FUNC(TMXBug987);
    TMXBug987();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class TMXBug787 : public TileDemo
{
public:
    CREATE_FUNC(TMXBug787);
    TMXBug787();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class TMXGIDObjectsTest : public TileDemo
{
public:
    CREATE_FUNC(TMXGIDObjectsTest);
    TMXGIDObjectsTest();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;    
};

class TMXHexOddXTest : public TileDemo
{
public:
    CREATE_FUNC(TMXHexOddXTest);
    TMXHexOddXTest();
    virtual std::string title() const override;
};

class TMXHexOddYTest : public TileDemo
{
public:
    CREATE_FUNC(TMXHexOddYTest);
    TMXHexOddYTest();
    virtual std::string title() const override;
};

class TMXHexEvenXTest : public TileDemo
{
public:
    CREATE_FUNC(TMXHexEvenXTest);
    TMXHexEvenXTest();
    virtual std::string title() const override;
};

class TMXHexEvenYTest : public TileDemo
{
public:
    CREATE_FUNC(TMXHexEvenYTest);
    TMXHexEvenYTest();
    virtual std::string title() const override;
};

class TMXHexAxisXTest : public TileDemo
{
public:
    CREATE_FUNC(TMXHexAxisXTest);
    TMXHexAxisXTest();
    virtual std::string title() const override;

};

class Issue16105Test : public TileDemo
{
public:
    CREATE_FUNC(Issue16105Test);
    Issue16105Test();
    virtual std::string title() const override;

};

class Issue16512Test : public TileDemo
{
public:
    CREATE_FUNC(Issue16512Test);
    Issue16512Test();
    virtual std::string title() const override;

};

#endif
