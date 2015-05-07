#include "Scene3DTest.h"
#include "../testResource.h"

USING_NS_CC;

////////////////////////////////////////////////////////////////////////////////
// Implements Scene3DTestScene

class Scene3DTestScene : public TestCase
{
public:
    CREATE_FUNC(Scene3DTestScene);
    
private:
    Scene3DTestScene();
    virtual ~Scene3DTestScene();
    bool init() override;
    
    void create3DWorld();
    void createUI();
    Node* createDialog();
    
    static const int DLG_COUNT = 3;
    std::vector<Node*> _dlgs;
};
#define GAME_SCENE_MASK     CameraFlag::DEFAULT
#define GAME_UI_MASK        CameraFlag::USER1
#define GAME_ACTOR_MASK     CameraFlag::USER2
#define GAME_ZOOM_MASK      CameraFlag::USER3

#define SCENE_CAMERA_DEPTH      0
#define UI_CAMERA_DEPTH         1
#define ACTOR_CAMERA_DEPTH      2
#define ZOOM_CAMERA_DEPTH       3

Scene3DTestScene::Scene3DTestScene()
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
        createDialog();
        ret = true;
    } while (0);
    
    return ret;
}

void Scene3DTestScene::create3DWorld()
{
    std::string filename = "Sprite3DTest/girl.c3b";
    auto girl = Sprite3D::create(filename);
    girl->setPosition(240, 0);
    this->addChild(girl);
}

void Scene3DTestScene::createUI()
{
    auto uiCamera = Camera::create();
    // uiCamera->setPositionX(uiCamera->getPositionX() + 50);
    uiCamera->setCameraFlag(GAME_UI_MASK);
    uiCamera->setDepth(UI_CAMERA_DEPTH);
    this->addChild(uiCamera);

    auto showDlgItem = MenuItemImage::create(s_pathClose, s_pathClose, [this](Ref* sender){
        this->_dlgs[0]->setVisible(!this->_dlgs[0]->isVisible());
    });
    showDlgItem->setPosition(VisibleRect::right().x - 30, VisibleRect::top().y - 30);
    
    auto moveCameraLeft = MenuItemImage::create(s_pathClose, s_pathClose, [uiCamera](Ref* sender){
        uiCamera->setPositionX(uiCamera->getPositionX() - 10);
    });
    moveCameraLeft->setPosition(VisibleRect::left().x + 30, VisibleRect::left().y);
    
    auto moveCameraRight = MenuItemImage::create(s_pathClose, s_pathClose, [uiCamera](Ref* sender){
        uiCamera->setPositionX(uiCamera->getPositionX() + 10);
    });
    moveCameraRight->setPosition(VisibleRect::right().x - 30, VisibleRect::right().y);

    auto menu = Menu::create(showDlgItem, moveCameraLeft, moveCameraRight, nullptr);
    menu->setPosition(Vec2::ZERO);
    menu->setCameraMask((unsigned short)GAME_UI_MASK, true);
    this->addChild(menu);
    
}

Node* Scene3DTestScene::createDialog()
{
    // create dialog layer
    int layerW = 240;
    int layerH = 160;
    int margin = 10;
    auto layer = LayerColor::create(Color4B(166, 166, 166, 255), layerW, layerH);
    //layer->setPosition(120, 80);
    layer->setVisible(false);
    // add 2d ui element on dialog:
    // actor background
    auto actorBg = LayerColor::create(Color4B(0, 0, 0, 255), layerW / 2 - 2 * margin, layerH - 2 * margin - 16);
    actorBg->setPosition(margin, margin);
    layer->addChild(actorBg);
    
    // title
    auto title = Label::createWithTTF("Actor Dialog","fonts/arial.ttf",16);
    title->setPosition(layerW / 2, layerH - margin);
    layer->addChild(title);
    
    // add layer to scene and set camera mask
    layer->setCameraMask((unsigned short)GAME_UI_MASK);
    this->addChild(layer);

    // add actor, which on dialog layer, and specify a camera for it
    std::string filename = "Sprite3DTest/girl.c3b";
    auto girl = Sprite3D::create(filename);
    girl->setScale(0.5);
    girl->setPosition(100, -20);
    girl->setCameraMask((unsigned short)GAME_ACTOR_MASK);
    layer->addChild(girl);
    
    auto actorCamera = Camera::create();
    actorCamera->setCameraFlag(GAME_ACTOR_MASK);
    actorCamera->setDepth(ACTOR_CAMERA_DEPTH);
    this->addChild(actorCamera);
    
    // add zoom in/out button, which is 2d ui element and over 3d actor, and specify a camera for it
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
    menu->setCameraMask((unsigned short)GAME_ZOOM_MASK, true);
    layer->addChild(menu);
    
    auto zoomBtnCamera = Camera::create();
    zoomBtnCamera->setCameraFlag(GAME_ZOOM_MASK);
    zoomBtnCamera->setDepth(ZOOM_CAMERA_DEPTH);
    this->addChild(zoomBtnCamera);
    
    return layer;
}

////////////////////////////////////////////////////////////////////////////////
// Implements Scene3DTests
Scene3DTests::Scene3DTests()
{
    ADD_TEST_CASE(Scene3DTestScene);
}
