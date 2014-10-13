#ifndef _TILEMAP_TEST_H_
#define _TILEMAP_TEST_H_

#include "../testBasic.h"
#include "../BaseTest.h"

class TileDemo : public BaseTest
{
public:
    TileDemo(void);
    virtual ~TileDemo(void);

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual void onEnter() override;
    virtual void onExit()override;

    void restartCallback(Ref* sender);
    void nextCallback(Ref* sender);
    void backCallback(Ref* sender);

    void onTouchesMoved(const std::vector<Touch*>& touches, Event  *event);
};

class TileMapTest : public TileDemo
{
public:
    TileMapTest(void);
    virtual std::string title() const override;
};

class TileMapEditTest : public TileDemo
{
public:
    TileMapEditTest (void);
    virtual std::string title() const override;

    void updateMap(float dt);
};

class TMXOrthoTest : public TileDemo
{
public:
    TMXOrthoTest(void);
    virtual std::string title() const override;

    virtual void onEnter() override;
    virtual void onExit() override;
};

class TMXStaggeredTest : public TileDemo
{
public:
    TMXStaggeredTest(void);
    virtual std::string title() const override;
    
    virtual void onEnter() override;
    virtual void onExit() override;
};

class TMXOrthoTest2 : public TileDemo
{
public:
    TMXOrthoTest2(void);
    virtual std::string title() const override;
};

class TMXOrthoTest3 : public TileDemo
{
public:
    TMXOrthoTest3(void);
    virtual std::string title() const override;
};

class TMXOrthoTest4 : public TileDemo
{
public:
    TMXOrthoTest4(void);
    void removeSprite(float dt);
    virtual std::string title() const override;
};

class TMXReadWriteTest : public TileDemo
{
    unsigned int _gid;
    unsigned int _gid2;
public:
    TMXReadWriteTest(void);
    virtual std::string title() const override;

    void removeSprite(Node* sender);
    void updateCol(float dt);
    void repaintWithGID(float dt);
    void removeTiles(float dt);
};

class TMXHexTest : public TileDemo
{
public:
    TMXHexTest(void);
    virtual std::string title() const override;
};

class TMXIsoTest : public TileDemo
{
public:
    TMXIsoTest(void);
    virtual std::string title() const override;
};

class TMXIsoTest1 : public TileDemo
{
public:
    TMXIsoTest1(void);
    virtual std::string title() const override;
};

class TMXIsoTest2 : public TileDemo
{
public:
    TMXIsoTest2(void);
    virtual std::string title() const override;
};

class TMXUncompressedTest : public TileDemo
{
public:
    TMXUncompressedTest(void);
    virtual std::string title() const override;
};

class TMXTilesetTest : public TileDemo
{
public:
    TMXTilesetTest(void);
    virtual std::string title() const override;
};



class TMXOrthoObjectsTest : public TileDemo
{
public:
    TMXOrthoObjectsTest(void);
    virtual std::string title() const override;

    virtual std::string subtitle() const override;
};

class TMXIsoObjectsTest : public TileDemo
{
public:
    TMXIsoObjectsTest(void);
    virtual std::string title() const override;

    virtual std::string subtitle() const override;
};

class TMXResizeTest : public TileDemo
{
public:
    TMXResizeTest(void);
    virtual std::string title() const override;

    virtual std::string subtitle() const override;
};

class TMXIsoZorder : public TileDemo
{
    Sprite*    _tamara;
public:
    TMXIsoZorder(void);
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual void onExit(void);

    ~TMXIsoZorder();
    void repositionSprite(float dt);
};

class TMXOrthoZorder : public TileDemo
{
    Sprite*    _tamara;
public:
    TMXOrthoZorder(void);
    virtual std::string title() const override;
    virtual std::string subtitle() const override;

    virtual ~TMXOrthoZorder();
    void repositionSprite(float dt);
};

class TMXIsoVertexZ : public TileDemo
{
    Sprite*    _tamara;
public:
    TMXIsoVertexZ(void);
    virtual std::string title() const override;
    virtual std::string subtitle() const override;

    ~TMXIsoVertexZ();
    void repositionSprite(float dt);
    virtual void onEnter() override;
    virtual void onExit() override;
};

class TMXOrthoVertexZ : public TileDemo
{
    Sprite*    _tamara;
public:
    TMXOrthoVertexZ(void);
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
    TMXIsoMoveLayer(void);
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class TMXOrthoMoveLayer : public TileDemo
{
public:
    TMXOrthoMoveLayer(void);
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class TMXTilePropertyTest : public TileDemo
{
public:
    TMXTilePropertyTest();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class TMXOrthoFlipTest : public TileDemo
{
public:
    TMXOrthoFlipTest();
    virtual std::string title() const override;
};

class TMXOrthoFlipRunTimeTest : public TileDemo
{
public:
    TMXOrthoFlipRunTimeTest();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    void flipIt(float dt);
};

class TMXOrthoFromXMLTest : public TileDemo
{
public:
    TMXOrthoFromXMLTest();
    virtual std::string title() const override;
};

class TMXOrthoXMLFormatTest : public TileDemo
{
public:
    TMXOrthoXMLFormatTest();
    virtual std::string title() const override;
};

class TMXBug987 : public TileDemo
{
public:
    TMXBug987();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class TMXBug787 : public TileDemo
{
public:
    TMXBug787();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class TMXGIDObjectsTest : public TileDemo
{
public:
    TMXGIDObjectsTest();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;    
};

class TileMapTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

#endif
