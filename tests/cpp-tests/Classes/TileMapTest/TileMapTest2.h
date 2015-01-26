#ifndef _TILEMAP_TEST_NEW_H_
#define _TILEMAP_TEST_NEW_H_

#include "../testBasic.h"
#include "../BaseTest.h"

class TileDemoNew : public BaseTest
{
public:
    TileDemoNew(void);
    virtual ~TileDemoNew(void);

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual void onEnter() override;
    virtual void onExit()override;

    void restartCallback(Ref* sender);
    void nextCallback(Ref* sender);
    void backCallback(Ref* sender);

    void onTouchesMoved(const std::vector<Touch*>& touches, Event  *event);
};

class TileMapTestNew : public TileDemoNew
{
public:
    TileMapTestNew(void);
    virtual std::string title() const override;
};

class TileMapEditTestNew : public TileDemoNew
{
public:
    TileMapEditTestNew (void);
    virtual std::string title() const override;

    void updateMap(float dt);
};

class TMXOrthoTestNew : public TileDemoNew
{
public:
    TMXOrthoTestNew(void);
    virtual std::string title() const override;

    virtual void onEnter() override;
    virtual void onExit() override;
};

class TMXOrthoTest2New : public TileDemoNew
{
public:
    TMXOrthoTest2New(void);
    virtual std::string title() const override;
};

class TMXOrthoTest3New : public TileDemoNew
{
public:
    TMXOrthoTest3New(void);
    virtual std::string title() const override;
};

class TMXOrthoTest4New : public TileDemoNew
{
public:
    TMXOrthoTest4New(void);
    void removeSprite(float dt);
    virtual std::string title() const override;
};

class TMXReadWriteTestNew : public TileDemoNew
{
    unsigned int _gid;
    unsigned int _gid2;
public:
    TMXReadWriteTestNew(void);
    virtual std::string title() const override;

    void removeSprite(Node* sender);
    void updateCol(float dt);
    void repaintWithGID(float dt);
    void removeTiles(float dt);
};

class TMXHexTestNew : public TileDemoNew
{
public:
    TMXHexTestNew(void);
    virtual std::string title() const override;
};

class TMXIsoTestNew : public TileDemoNew
{
public:
    TMXIsoTestNew(void);
    virtual std::string title() const override;
};

class TMXIsoTest1New : public TileDemoNew
{
public:
    TMXIsoTest1New(void);
    virtual std::string title() const override;
};

class TMXIsoTest2New : public TileDemoNew
{
public:
    TMXIsoTest2New(void);
    virtual std::string title() const override;
};

class TMXUncompressedTestNew : public TileDemoNew
{
public:
    TMXUncompressedTestNew(void);
    virtual std::string title() const override;
};

class TMXTilesetTestNew : public TileDemoNew
{
public:
    TMXTilesetTestNew(void);
    virtual std::string title() const override;
};



class TMXOrthoObjectsTestNew : public TileDemoNew
{
public:
    TMXOrthoObjectsTestNew(void);
    virtual std::string title() const override;

    virtual std::string subtitle() const override;
};

class TMXIsoObjectsTestNew : public TileDemoNew
{
public:
    TMXIsoObjectsTestNew(void);
    virtual std::string title() const override;

    virtual std::string subtitle() const override;
};

class TMXResizeTestNew : public TileDemoNew
{
public:
    TMXResizeTestNew(void);
    virtual std::string title() const override;

    virtual std::string subtitle() const override;
};

class TMXIsoZorderNew : public TileDemoNew
{
    Sprite*    _tamara;
public:
    TMXIsoZorderNew(void);
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual void onExit(void);

    ~TMXIsoZorderNew();
    void repositionSprite(float dt);
};

class TMXOrthoZorderNew : public TileDemoNew
{
    Sprite*    _tamara;
public:
    TMXOrthoZorderNew(void);
    virtual std::string title() const override;
    virtual std::string subtitle() const override;

    virtual ~TMXOrthoZorderNew();
    void repositionSprite(float dt);
};

class TMXIsoVertexZNew : public TileDemoNew
{
    Sprite*    _tamara;
public:
    TMXIsoVertexZNew(void);
    virtual std::string title() const override;
    virtual std::string subtitle() const override;

    ~TMXIsoVertexZNew();
    void repositionSprite(float dt);
    virtual void onEnter() override;
    virtual void onExit() override;
};

class TMXOrthoVertexZNew : public TileDemoNew
{
    Sprite*    _tamara;
public:
    TMXOrthoVertexZNew(void);
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
    TMXIsoMoveLayerNew(void);
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class TMXOrthoMoveLayerNew : public TileDemoNew
{
public:
    TMXOrthoMoveLayerNew(void);
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class TMXTilePropertyTestNew : public TileDemoNew
{
public:
    TMXTilePropertyTestNew();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class TMXOrthoFlipTestNew : public TileDemoNew
{
public:
    TMXOrthoFlipTestNew();
    virtual std::string title() const override;
};

class TMXOrthoFlipRunTimeTestNew : public TileDemoNew
{
public:
    TMXOrthoFlipRunTimeTestNew();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    void flipIt(float dt);
};

class TMXOrthoFromXMLTestNew : public TileDemoNew
{
public:
    TMXOrthoFromXMLTestNew();
    virtual std::string title() const override;
};

class TMXOrthoXMLFormatTestNew : public TileDemoNew
{
public:
    TMXOrthoXMLFormatTestNew();
    virtual std::string title() const override;
};

class TMXBug987New : public TileDemoNew
{
public:
    TMXBug987New();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class TMXBug787New : public TileDemoNew
{
public:
    TMXBug787New();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class TMXGIDObjectsTestNew : public TileDemoNew
{
public:
    TMXGIDObjectsTestNew();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;   
};

class TileMapTestSceneNew : public TestScene
{
public:
    virtual void runThisTest();
};

#endif
