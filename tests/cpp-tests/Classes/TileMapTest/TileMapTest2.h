#ifndef _TILEMAP_TEST_NEW_H_
#define _TILEMAP_TEST_NEW_H_

#include "../BaseTest.h"

DEFINE_TEST_SUITE(FastTileMapTests);

class TileDemoNew : public TestCase
{
public:
    TileDemoNew();
    virtual ~TileDemoNew();

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual void onExit() override;

    void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
};

class TileMapTestNew : public TileDemoNew
{
public:
    CREATE_FUNC(TileMapTestNew);
    TileMapTestNew();
    virtual std::string title() const override;
};

class TileMapEditTestNew : public TileDemoNew
{
public:
    CREATE_FUNC(TileMapEditTestNew);
    TileMapEditTestNew ();
    virtual std::string title() const override;

    void updateMap(float dt);
};

class TMXOrthoTestNew : public TileDemoNew
{
public:
    CREATE_FUNC(TMXOrthoTestNew);
    TMXOrthoTestNew();
    virtual std::string title() const override;

    virtual void onEnter() override;
    virtual void onExit() override;
};

class TMXOrthoTest2New : public TileDemoNew
{
public:
    CREATE_FUNC(TMXOrthoTest2New);
    TMXOrthoTest2New();
    virtual std::string title() const override;
};

class TMXOrthoTest3New : public TileDemoNew
{
public:
    CREATE_FUNC(TMXOrthoTest3New);
    TMXOrthoTest3New();
    virtual std::string title() const override;
};

class TMXOrthoTest4New : public TileDemoNew
{
public:
    CREATE_FUNC(TMXOrthoTest4New);
    TMXOrthoTest4New();
    void removeSprite(float dt);
    virtual std::string title() const override;
};

class TMXReadWriteTestNew : public TileDemoNew
{
    unsigned int _gid;
    unsigned int _gid2;
public:
    CREATE_FUNC(TMXReadWriteTestNew);
    TMXReadWriteTestNew();
    virtual std::string title() const override;

    void removeSprite(Node* sender);
    void updateCol(float dt);
    void repaintWithGID(float dt);
    void removeTiles(float dt);
};

class TMXHexTestNew : public TileDemoNew
{
public:
    CREATE_FUNC(TMXHexTestNew);
    TMXHexTestNew();
    virtual std::string title() const override;
};

class TMXIsoTestNew : public TileDemoNew
{
public:
    CREATE_FUNC(TMXIsoTestNew);
    TMXIsoTestNew();
    virtual std::string title() const override;
};

class TMXIsoTest1New : public TileDemoNew
{
public:
    CREATE_FUNC(TMXIsoTest1New);
    TMXIsoTest1New();
    virtual std::string title() const override;
};

class TMXIsoTest2New : public TileDemoNew
{
public:
    CREATE_FUNC(TMXIsoTest2New);
    TMXIsoTest2New();
    virtual std::string title() const override;
};

class TMXUncompressedTestNew : public TileDemoNew
{
public:
    CREATE_FUNC(TMXUncompressedTestNew);
    TMXUncompressedTestNew();
    virtual std::string title() const override;
};

class TMXTilesetTestNew : public TileDemoNew
{
public:
    CREATE_FUNC(TMXTilesetTestNew);
    TMXTilesetTestNew();
    virtual std::string title() const override;
};

class TMXOrthoObjectsTestNew : public TileDemoNew
{
public:
    CREATE_FUNC(TMXOrthoObjectsTestNew);
    TMXOrthoObjectsTestNew();
    virtual std::string title() const override;

    virtual std::string subtitle() const override;
};

class TMXIsoObjectsTestNew : public TileDemoNew
{
public:
    CREATE_FUNC(TMXIsoObjectsTestNew);
    TMXIsoObjectsTestNew();
    virtual std::string title() const override;

    virtual std::string subtitle() const override;
};

class TMXResizeTestNew : public TileDemoNew
{
public:
    CREATE_FUNC(TMXResizeTestNew);
    TMXResizeTestNew();
    virtual std::string title() const override;

    virtual std::string subtitle() const override;
};

class TMXIsoZorderNew : public TileDemoNew
{
    cocos2d::Sprite*    _tamara;
public:
    CREATE_FUNC(TMXIsoZorderNew);
    TMXIsoZorderNew();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual void onExit()override;

    ~TMXIsoZorderNew();
    void repositionSprite(float dt);
};

class TMXOrthoZorderNew : public TileDemoNew
{
    cocos2d::Sprite*    _tamara;
public:
    CREATE_FUNC(TMXOrthoZorderNew);
    TMXOrthoZorderNew();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;

    virtual ~TMXOrthoZorderNew();
    void repositionSprite(float dt);
};

class TMXIsoVertexZNew : public TileDemoNew
{
    cocos2d::Sprite*    _tamara;
public:
    CREATE_FUNC(TMXIsoVertexZNew);
    TMXIsoVertexZNew();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;

    ~TMXIsoVertexZNew();
    void repositionSprite(float dt);
    virtual void onEnter() override;
    virtual void onExit() override;
};

class TMXOrthoVertexZNew : public TileDemoNew
{
    cocos2d::Sprite*    _tamara;
public:
    CREATE_FUNC(TMXOrthoVertexZNew);
    TMXOrthoVertexZNew();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;

    ~TMXOrthoVertexZNew();
    void repositionSprite(float dt);
    virtual void onEnter() override;
    virtual void onExit() override;
};

class TMXIsoMoveLayerNew : public TileDemoNew
{
public:
    CREATE_FUNC(TMXIsoMoveLayerNew);
    TMXIsoMoveLayerNew();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class TMXOrthoMoveLayerNew : public TileDemoNew
{
public:
    CREATE_FUNC(TMXOrthoMoveLayerNew);
    TMXOrthoMoveLayerNew();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class TMXTilePropertyTestNew : public TileDemoNew
{
public:
    CREATE_FUNC(TMXTilePropertyTestNew);
    TMXTilePropertyTestNew();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class TMXOrthoFlipTestNew : public TileDemoNew
{
public:
    CREATE_FUNC(TMXOrthoFlipTestNew);
    TMXOrthoFlipTestNew();
    virtual std::string title() const override;
};

class TMXOrthoFlipRunTimeTestNew : public TileDemoNew
{
public:
    CREATE_FUNC(TMXOrthoFlipRunTimeTestNew);
    TMXOrthoFlipRunTimeTestNew();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    void flipIt(float dt);
};

class TMXOrthoFromXMLTestNew : public TileDemoNew
{
public:
    CREATE_FUNC(TMXOrthoFromXMLTestNew);
    TMXOrthoFromXMLTestNew();
    virtual std::string title() const override;
};

class TMXOrthoXMLFormatTestNew : public TileDemoNew
{
public:
    CREATE_FUNC(TMXOrthoXMLFormatTestNew);
    TMXOrthoXMLFormatTestNew();
    virtual std::string title() const override;
};

class TMXBug987New : public TileDemoNew
{
public:
    CREATE_FUNC(TMXBug987New);
    TMXBug987New();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class TMXBug787New : public TileDemoNew
{
public:
    CREATE_FUNC(TMXBug787New);
    TMXBug787New();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class TMXGIDObjectsTestNew : public TileDemoNew
{
public:
    CREATE_FUNC(TMXGIDObjectsTestNew);
    TMXGIDObjectsTestNew();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;   
};

#endif
