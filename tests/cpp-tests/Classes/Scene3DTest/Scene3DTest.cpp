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
    void createDialog();
    
    Node* _ui;
    Node* _dialog;
};
#define GAME_3D_MASK        CameraFlag::DEFAULT
#define GAME_UI_MASK        CameraFlag::USER1
#define GAME_DIALOG_MASK    CameraFlag::USER2
#define GAME_UI_ZORDER      1
#define GAME_DIALOG_ZORDER  2

Scene3DTestScene::Scene3DTestScene()
: _dialog(nullptr)
{
    
}

Scene3DTestScene::~Scene3DTestScene()
{
    CC_SAFE_RELEASE(_dialog);
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
    auto closeItem = MenuItemImage::create(s_pathClose, s_pathClose, [this](Ref* sender){
        this->_dialog->setVisible(!this->_dialog->isVisible());
    });
    closeItem->setPosition(240 + 20, 160);
    
    auto menu = Menu::create(closeItem, nullptr);
    menu->setPosition(Vec2::ZERO);
    menu->setCameraMask((unsigned short)GAME_UI_MASK, true);
    this->addChild(menu, GAME_UI_ZORDER);
    _ui = menu;
    
    auto uiCamera = Camera::create();
    // uiCamera->setPositionX(uiCamera->getPositionX() + 50);
    uiCamera->setCameraFlag(GAME_UI_MASK);
    this->addChild(uiCamera);
}

void Scene3DTestScene::createDialog()
{
    if (_dialog) {
        return;
    }

    auto layer = LayerColor::create(Color4B(166, 166, 166, 255), 240, 160);
    layer->setPosition(120, 80);
    //layer->setVisible(false);
    
    auto title = Label::createWithTTF("Actor Dialog","fonts/arial.ttf",16);
    title->setPosition(120, 140);
    layer->addChild(title);
    
    std::string filename = "Sprite3DTest/girl.c3b";
    auto girl = Sprite3D::create(filename);
    girl->setScale(0.5);
    girl->setPosition(100, -20);
    layer->addChild(girl);
    
    this->addChild(layer, GAME_DIALOG_ZORDER);
    _dialog = layer;
}

////////////////////////////////////////////////////////////////////////////////
// Implements Scene3DTests
Scene3DTests::Scene3DTests()
{
    ADD_TEST_CASE(Scene3DTestScene);
}
