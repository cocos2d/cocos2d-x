#include "Scene3DTest.h"

#include "../testResource.h"
#include "TerrainTest.h"

USING_NS_CC;


////////////////////////////////////////////////////////////////////////////////
// Implements Scene3DTestScene
static Vec3 camera_offset(0, 45, 60);

class Scene3DTestScene : public TestCase
{
public:
    CREATE_FUNC(Scene3DTestScene);
    
    void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    void onTouchesEnd(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
private:
    Scene3DTestScene();
    virtual ~Scene3DTestScene();
    bool init() override;
    
    void create3DWorld();
    void createUI();
    Node* createDialog();
    
    std::vector<Camera *> _gameCameras;
    
    Terrain *_terrain;
    Player  *_player;
    
    static const int DLG_COUNT = 3;
    std::vector<Node*> _dlgs;
};

enum LAYER_DEPTH {
    LAYER_DEPTH_GAME  = 0,
    LAYER_DEPTH_UI,
    LAYER_DEPTH_ACTOR,
    LAYER_DEPTH_ZOOM,
    LAYER_DEPTH_COUNT,
};

static CameraFlag s_CF[LAYER_DEPTH_COUNT] = {
    CameraFlag::DEFAULT,
    CameraFlag::USER1,
    CameraFlag::USER2,
    CameraFlag::USER3,
};

static unsigned short s_CM[LAYER_DEPTH_COUNT] = {
    (unsigned short)s_CF[0],
    (unsigned short)s_CF[1],
    (unsigned short)s_CF[2],
    (unsigned short)s_CF[3],
};


Scene3DTestScene::Scene3DTestScene()
: _terrain(nullptr)
, _player(nullptr)
{
    
}

Scene3DTestScene::~Scene3DTestScene()
{
    for (auto dlg : _dlgs) {
        CC_SAFE_RELEASE(dlg);
    }
}

bool Scene3DTestScene::init()
{
    bool ret = false;
    do
    {
        CC_BREAK_IF(false == TestCase::init());
        
        Director::getInstance()->setDisplayStats(false);

        // prepare for camera creation, we need create three custom cameras
        Size visibleSize = Director::getInstance()->getVisibleSize();
        _gameCameras.resize(LAYER_DEPTH_COUNT);
        
        // first, create a camera to look the 3d game scene
        Camera *ca = Camera::createPerspective(60,visibleSize.width/visibleSize.height,0.1,200);
        ca->setCameraFlag(s_CF[LAYER_DEPTH_GAME]);
        ca->setDepth(LAYER_DEPTH_GAME);
        _gameCameras[LAYER_DEPTH_GAME] = ca;
        this->addChild(ca);
        
        // second, use the default camera to look 2d base ui layer
        ca =this->getDefaultCamera();
        ca->setCameraFlag(s_CF[LAYER_DEPTH_UI]);
        ca->setDepth(LAYER_DEPTH_UI);
        _gameCameras[LAYER_DEPTH_UI] = ca;

        // third, create a camera to look the 3d model in dialogs
        ca = Camera::create();
        ca->setCameraFlag(s_CF[LAYER_DEPTH_ACTOR]);
        ca->setDepth(LAYER_DEPTH_ACTOR);
        _gameCameras[LAYER_DEPTH_ACTOR] = ca;
        this->addChild(ca);
        
        // forth, create a camera to kook the ui element over on the 3d models
        ca = Camera::create();
        ca->setCameraFlag(s_CF[LAYER_DEPTH_ZOOM]);
        ca->setDepth(LAYER_DEPTH_ZOOM);
        _gameCameras[LAYER_DEPTH_ZOOM] = ca;
        this->addChild(ca);
        
        // create all object in game
        create3DWorld();
        createUI();
        Size step = VisibleRect::getVisibleRect().size;
        step.width /= (DLG_COUNT + 1);
        step.height /= (DLG_COUNT + 1);
        Vec2 pos = VisibleRect::leftBottom();

        Node * dlg;
        for (int i = 0; i < DLG_COUNT; ++i) {
            dlg = createDialog();
            dlg->setPosition(pos);
            dlg->retain();
            _dlgs.push_back(dlg);
            pos.x += step.width;
            pos.y += step.height;
        }
        
        // add touch callback
//        auto listener = EventListenerTouchAllAtOnce::create();
//        listener->onTouchesBegan = CC_CALLBACK_2(Scene3DTestScene::onTouchesBegan, this);
//        listener->onTouchesMoved = CC_CALLBACK_2(Scene3DTestScene::onTouchesMoved, this);
//        listener->onTouchesEnded = CC_CALLBACK_2(Scene3DTestScene::onTouchesEnd, this);
//        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
        
        ret = true;
    } while (0);
    
    return ret;
}

void Scene3DTestScene::create3DWorld()
{
//    Size visibleSize = Director::getInstance()->getVisibleSize();
    auto camera = _gameCameras[LAYER_DEPTH_GAME];

    // first, create terrain
    Terrain::DetailMap r("TerrainTest/dirt.jpg");
    Terrain::DetailMap g("TerrainTest/Grass2.jpg",10);
    Terrain::DetailMap b("TerrainTest/road.jpg");
    Terrain::DetailMap a("TerrainTest/GreenSkin.jpg",20);
    Terrain::TerrainData data("TerrainTest/heightmap16.jpg",
                              "TerrainTest/alphamap.png",
                              r,g,b,a,Size(32,32),40.0f,2);
    _terrain = Terrain::create(data,Terrain::CrackFixedType::SKIRT);
    _terrain->setMaxDetailMapAmount(4);
    _terrain->setCameraMask(s_CM[LAYER_DEPTH_GAME]);
    _terrain->setDrawWire(false);
    _terrain->setSkirtHeightRatio(3);
    _terrain->setLODDistance(64,128,192);
    this->addChild(_terrain);
    
    // second, create actor
    _player = Player::create("Sprite3DTest/girl.c3b",camera,_terrain);
    _player->setCameraMask(s_CM[LAYER_DEPTH_GAME]);
    _player->setScale(0.08);
    _player->setPositionY(_terrain->getHeight(_player->getPositionX(),_player->getPositionZ()));
    
    auto animation = Animation3D::create("Sprite3DTest/girl.c3b","Take 001");
    if (animation)
    {
        auto animate = Animate3D::create(animation);
        _player->runAction(RepeatForever::create(animate));
    }
    
    addChild(_player);
    
    // third, set camera position
    camera->setPosition3D(_player->getPosition3D()+camera_offset);
    camera->setRotation3D(Vec3(-45,0,0));
}

void Scene3DTestScene::createUI()
{
    auto showLeftDlgItem = MenuItemImage::create(s_pathClose, s_pathClose, [this](Ref* sender){
        this->_dlgs[0]->setVisible(!this->_dlgs[0]->isVisible());
    });
    showLeftDlgItem->setPosition(VisibleRect::left().x + 30, VisibleRect::top().y - 30);
    
    auto showMidDlgItem = MenuItemImage::create(s_pathClose, s_pathClose, [this](Ref* sender){
        this->_dlgs[1]->setVisible(!this->_dlgs[1]->isVisible());
    });
    showMidDlgItem->setPosition(VisibleRect::top().x, VisibleRect::top().y - 30);
    
    auto showRightDlgItem = MenuItemImage::create(s_pathClose, s_pathClose, [this](Ref* sender){
        this->_dlgs[2]->setVisible(!this->_dlgs[2]->isVisible());
    });
    
    showRightDlgItem->setPosition(VisibleRect::right().x - 30, VisibleRect::top().y - 30);
    
    auto uiCamera = _gameCameras[LAYER_DEPTH_UI];
    auto moveCameraLeft = MenuItemImage::create(s_pathClose, s_pathClose, [uiCamera](Ref* sender){
        uiCamera->setPositionX(uiCamera->getPositionX() - 10);
    });
    moveCameraLeft->setPosition(VisibleRect::left().x + 30, VisibleRect::left().y);
    
    auto moveCameraRight = MenuItemImage::create(s_pathClose, s_pathClose, [uiCamera](Ref* sender){
        uiCamera->setPositionX(uiCamera->getPositionX() + 10);
    });
    moveCameraRight->setPosition(VisibleRect::right().x - 30, VisibleRect::right().y);

    auto menu = Menu::create(showLeftDlgItem,
                             showMidDlgItem,
                             showRightDlgItem,
                             moveCameraLeft,
                             moveCameraRight,
                             nullptr);
    menu->setPosition(Vec2::ZERO);
    menu->setCameraMask(s_CM[LAYER_DEPTH_UI], true);
    this->addChild(menu);
    
}

Node* Scene3DTestScene::createDialog()
{
    // create dialog layer
    int layerW = 240;
    int layerH = 160;
    int margin = 10;
    static char clr = 0x3f;
    auto layer = LayerColor::create(Color4B(clr, clr, clr, 255), layerW, layerH);
    clr = clr << 1;
    layer->setVisible(false);
    
    // add 2d ui element on dialog:
    // actor background
    auto actorBg = LayerColor::create(Color4B(0, 0, 128, 255), layerW / 2 - 2 * margin, layerH - 2 * margin - 16);
    actorBg->setPosition(margin, margin);
    layer->addChild(actorBg);
    
    // title
    auto title = Label::createWithTTF("Actor Dialog","fonts/arial.ttf",16);
    title->setPosition(layerW / 2, layerH - margin);
    layer->addChild(title);
    
    // add layer to scene and set camera mask
    layer->setCameraMask(s_CM[LAYER_DEPTH_UI]);
    this->addChild(layer);

    // add actor, which on dialog layer
    std::string filename = "Sprite3DTest/girl.c3b";
    auto girl = Sprite3D::create(filename);
    girl->setScale(0.5);
    girl->setPosition(layerW / 4, margin * 3);
    girl->setCameraMask(s_CM[LAYER_DEPTH_ACTOR]);
    layer->addChild(girl);
    
    // add zoom in/out button, which is 2d ui element and over 3d actor
    auto zoomIn = MenuItemImage::create(s_pathClose, s_pathClose, [girl](Ref* sender){
        girl->setScale(girl->getScale() * 2);
    });
    zoomIn->setPosition(margin, layerH - margin);
    
    auto zoomOut = MenuItemImage::create(s_pathClose, s_pathClose, [girl](Ref* sender){
        girl->setScale(girl->getScale() / 2);
    });
    zoomOut->setPosition(layerW / 2 - margin, layerH - margin);

    auto menu = Menu::create(zoomIn, zoomOut, nullptr);
    menu->setPosition(Vec2::ZERO);
    menu->setCameraMask(s_CM[LAYER_DEPTH_ZOOM]);
    layer->addChild(menu);
    
    return layer;
}

////////////////////////////////////////////////////////////////////////////////
// Implements Scene3DTests
Scene3DTests::Scene3DTests()
{
    ADD_TEST_CASE(Scene3DTestScene);
}
