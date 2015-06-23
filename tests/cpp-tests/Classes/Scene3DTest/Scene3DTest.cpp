#include "Scene3DTest.h"

#include "ui/CocosGUI.h"
#include <spine/spine-cocos2dx.h>

#include "../testResource.h"
#include "../TerrainTest/TerrainTest.h"

USING_NS_CC;
using namespace spine;

////////////////////////////////////////////////////////////////////////////////
// Implements Scene3DTestScene

class Scene3DTestScene : public TerrainWalkThru
{
public:
    CREATE_FUNC(Scene3DTestScene);
    
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_WP8 || CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    cocos2d::EventListenerCustom* _backToForegroundListener;
#endif
    
private:
    Scene3DTestScene();
    virtual ~Scene3DTestScene();
    bool init() override;
    
    void create3DWorld();
    void createUI();
    void createPlayerDlg();
    void createDetailDlg();
    void createDescDlg();
    
    std::vector<Camera *> _gameCameras;
    
    Node* _playerDlg;
    Node* _detailDlg;
    Node* _descDlg;
    
    TextureCube* _textureCube;
    Skybox* _skyBox;
};

enum GAME_LAYER {
    LAYER_SKYBOX = 0,
    LAYER_GAME,
    LAYER_UI,
    LAYER_ACTOR,
    LAYER_ZOOM,
    LAYER_OSD,
    LAYER_COUNT,
};

static CameraFlag s_CF[LAYER_COUNT] = {
    CameraFlag::DEFAULT,
    CameraFlag::USER1,
    CameraFlag::USER2,
    CameraFlag::USER3,
    CameraFlag::USER4,
    CameraFlag::USER5,
};

static unsigned short s_CM[LAYER_COUNT] = {
    (unsigned short)s_CF[0],
    (unsigned short)s_CF[1],
    (unsigned short)s_CF[2],
    (unsigned short)s_CF[3],
    (unsigned short)s_CF[4],
    (unsigned short)s_CF[5],
};


Scene3DTestScene::Scene3DTestScene()
: _playerDlg(nullptr)
, _detailDlg(nullptr)
, _descDlg(nullptr)
{
}

Scene3DTestScene::~Scene3DTestScene()
{
}

bool Scene3DTestScene::init()
{
    bool ret = false;
    do
    {
        CC_BREAK_IF(false == TerrainWalkThru::init());

        // prepare for camera creation, we need create three custom cameras
        _gameCameras.resize(LAYER_COUNT);
        
        Camera *ca = nullptr;
        auto visibleSize = Director::getInstance()->getVisibleSize();
        // first, create a camera to look the skybox
        ca = Camera::createPerspective(60, visibleSize.width / visibleSize.height, 10, 1000);
        ca->setPosition3D(Vec3(0.f, 0.f, 50.f));
        ca->setCameraFlag(s_CF[LAYER_SKYBOX]);
        ca->setDepth(LAYER_SKYBOX);
        _gameCameras[LAYER_SKYBOX] = ca;
        this->addChild(ca);
        
        // second, create a camera to look the 3D game scene
        // it has been create in TerrainWalkThru::init
        ca = this->_camera;
        ca->setCameraFlag(s_CF[LAYER_GAME]);
        ca->setDepth(LAYER_GAME);
        _gameCameras[LAYER_GAME] = ca;
        
        // third, use the default camera to look 2D base UI layer
        ca =this->getDefaultCamera();
        ca->setCameraFlag(s_CF[LAYER_UI]);
        ca->setDepth(LAYER_UI);
        _gameCameras[LAYER_UI] = ca;

        // forth, create a camera to look the 3D model in dialogs
        ca = Camera::create();
        ca->setCameraFlag(s_CF[LAYER_ACTOR]);
        ca->setDepth(LAYER_ACTOR);
        _gameCameras[LAYER_ACTOR] = ca;
        this->addChild(ca);
        
        // fifth, create a camera to look the UI element over on the 3D models
        ca = Camera::create();
        ca->setCameraFlag(s_CF[LAYER_ZOOM]);
        ca->setDepth(LAYER_ZOOM);
        _gameCameras[LAYER_ZOOM] = ca;
        this->addChild(ca);
        
        // sixth, create a camera to look the OSD UI
        ca = Camera::create();
        ca->setCameraFlag(s_CF[LAYER_OSD]);
        ca->setDepth(LAYER_OSD);
        _gameCameras[LAYER_OSD] = ca;
        this->addChild(ca);

        // create all object in game
        create3DWorld();
        createUI();
        createPlayerDlg();
        createDetailDlg();
        createDescDlg();
        
        _playerDlg->setVisible(false);
        _detailDlg->setVisible(false);
        //_terrain->setVisible(false);
        ret = true;
    } while (0);
    
    return ret;
}

void Scene3DTestScene::create3DWorld()
{
    // terrain and player has been create in TerrainWalkThru::init
    // we only need override there camera mask
    _terrain->setCameraMask(s_CM[LAYER_GAME]);
    _player->setCameraMask(s_CM[LAYER_GAME]);
    _player->setScale(_player->getScale() * 1.5);
    
    // add two Sprite3D monster, one is transparent
    auto monster = Sprite3D::create("Sprite3DTest/orc.c3b");
    monster->setRotation3D(Vec3(0,180,0));
    monster->setPosition3D(_player->getPosition3D() + Vec3(50, -10, 0));
    monster->setCameraMask(s_CM[LAYER_GAME]);
    monster->setOpacity(128);
    this->addChild(monster);
    monster = Sprite3D::create("Sprite3DTest/orc.c3b");
    monster->setRotation3D(Vec3(0,180,0));
    monster->setPosition3D(_player->getPosition3D() + Vec3(-50, -5, 0));
    monster->setCameraMask(s_CM[LAYER_GAME]);
    this->addChild(monster);

    // add a particle 3d above player
    auto rootps = PUParticleSystem3D::create("Particle3D/scripts/blackHole.pu", "Particle3D/materials/pu_mediapack_01.material");
    rootps->setScale(2);
    rootps->setPosition3D(Vec3(0, 150, 0));
    rootps->setCameraMask(s_CM[LAYER_GAME]);
    auto moveby = MoveBy::create(2.0f, Vec2(50.0f, 0.0f));
    auto moveby1 = MoveBy::create(2.0f, Vec2(-50.0f, 0.0f));
    rootps->runAction(RepeatForever::create(Sequence::create(moveby, moveby1, nullptr)));
    rootps->startParticleSystem();
    
    _player->addChild(rootps, 0);

    // then, create skybox
    //create and set our custom shader
    auto shader = GLProgram::createWithFilenames("Sprite3DTest/cube_map.vert", "Sprite3DTest/cube_map.frag");
    auto state = GLProgramState::create(shader);
    
    // create the second texture for cylinder
    _textureCube = TextureCube::create("Sprite3DTest/skybox/left.jpg", "Sprite3DTest/skybox/right.jpg",
                                       "Sprite3DTest/skybox/top.jpg", "Sprite3DTest/skybox/bottom.jpg",
                                       "Sprite3DTest/skybox/front.jpg", "Sprite3DTest/skybox/back.jpg");
    _textureCube->retain();
    //set texture parameters
    Texture2D::TexParams tRepeatParams;
    tRepeatParams.magFilter = GL_LINEAR;
    tRepeatParams.minFilter = GL_LINEAR;
    tRepeatParams.wrapS = GL_MIRRORED_REPEAT;
    tRepeatParams.wrapT = GL_MIRRORED_REPEAT;
    _textureCube->setTexParameters(tRepeatParams);
    
    // pass the texture sampler to our custom shader
    state->setUniformTexture("u_cubeTex", _textureCube);
    
    // add skybox
    _skyBox = Skybox::create();
    _skyBox->retain();
    _skyBox->setCameraMask(s_CM[LAYER_SKYBOX]);
    _skyBox->setTexture(_textureCube);
    _skyBox->setScale(700.f);
    this->addChild(_skyBox);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_WP8 || CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    _backToForegroundListener = EventListenerCustom::create(EVENT_RENDERER_RECREATED,
                                                            [this](EventCustom*)
                                                            {
                                                                auto state = _skyBox->getGLProgramState();
                                                                auto glProgram = state->getGLProgram();
                                                                glProgram->reset();
                                                                glProgram->initWithFilenames("Sprite3DTest/cube_map.vert", "Sprite3DTest/cube_map.frag");
                                                                glProgram->link();
                                                                glProgram->updateUniforms();
                                                                
                                                                _textureCube->reloadTexture();
                                                                
                                                                Texture2D::TexParams tRepeatParams;
                                                                tRepeatParams.magFilter = GL_NEAREST;
                                                                tRepeatParams.minFilter = GL_NEAREST;
                                                                tRepeatParams.wrapS = GL_MIRRORED_REPEAT;
                                                                tRepeatParams.wrapT = GL_MIRRORED_REPEAT;
                                                                _textureCube->setTexParameters(tRepeatParams);
                                                                state->setUniformTexture("u_cubeTex", _textureCube);
                                                                
                                                                _skyBox->reload();
                                                                _skyBox->setTexture(_textureCube);
                                                            });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(_backToForegroundListener, 1);
#endif
}

void Scene3DTestScene::createUI()
{
    // add player button
    auto showLeftDlgItem = MenuItemImage::create("Images/Pea.png", "Images/Pea.png", [this](Ref* sender){
        this->_playerDlg->setVisible(!this->_playerDlg->isVisible());
    });
    showLeftDlgItem->setPosition(VisibleRect::left().x + 30, VisibleRect::top().y - 30);
    
    // add discription button
    TTFConfig ttfConfig("fonts/arial.ttf", 20);
    auto descItem = MenuItemLabel::create(Label::createWithTTF(ttfConfig, "Description"),
                                          [this](Ref* sender)
    {
        this->_descDlg->setVisible(!this->_descDlg->isVisible());
    });
    descItem->setPosition(Vec2(VisibleRect::right().x - 50, VisibleRect::top().y - 25));
    
    // add back button
    auto backItem = MenuItemLabel::create(Label::createWithTTF(ttfConfig, "Back"),
                                          [this](Ref* sender){
                                              this->getTestSuite()->backsUpOneLevel();
                                          });
    backItem->setPosition(Vec2(VisibleRect::right().x - 50, VisibleRect::bottom().y + 25));
    
    MenuItemImage *moveCameraLeft = nullptr, *moveCameraRight = nullptr;
//    auto uiCamera = _gameCameras[LAYER_UI];
//    moveCameraLeft = MenuItemImage::create(s_pathClose, s_pathClose, [uiCamera](Ref* sender){
//        uiCamera->setPositionX(uiCamera->getPositionX() - 10);
//    });
//    moveCameraLeft->setPosition(VisibleRect::left().x + 30, VisibleRect::left().y);
//    
//    moveCameraRight = MenuItemImage::create(s_pathClose, s_pathClose, [uiCamera](Ref* sender){
//        uiCamera->setPositionX(uiCamera->getPositionX() + 10);
//    });
//    moveCameraRight->setPosition(VisibleRect::right().x - 30, VisibleRect::right().y);

    auto menu = Menu::create(showLeftDlgItem,
                             descItem,
                             backItem,
                             moveCameraLeft,
                             moveCameraRight,
                             nullptr);
    menu->setPosition(Vec2::ZERO);
    menu->setCameraMask(s_CM[LAYER_UI], true);
    this->addChild(menu);
    
}

void Scene3DTestScene::createPlayerDlg()
{
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(s_s9s_ui_plist);
    
    Size dlgSize(190, 240);
    Vec2 pos = VisibleRect::center();
    float margin = 10;
    
    // first, create dialog ui part, include background, title and buttons
    _playerDlg = ui::Scale9Sprite::createWithSpriteFrameName("button_actived.png");
    _playerDlg->setContentSize(dlgSize);
    _playerDlg->setAnchorPoint(Vec2(1, 0.5));
    pos.y -= margin;
    pos.x -= margin;
    _playerDlg->setPosition(pos);
    
    // title
    auto title = Label::createWithTTF("Player Dialog","fonts/arial.ttf",16);
    title->setPosition(dlgSize.width / 2, dlgSize.height - margin * 2);
    _playerDlg->addChild(title);
    
    // player background
    Size bgSize(110, 180);
    Vec2 bgPos(margin, dlgSize.height / 2 - margin);
    auto playerBg = ui::Scale9Sprite::createWithSpriteFrameName("item_bg.png");
    playerBg->setContentSize(bgSize);
    playerBg->setAnchorPoint(Vec2(0, 0.5));
    playerBg->setPosition(bgPos);
    _playerDlg->addChild(playerBg);

    // item background and item
    Size itemSize(48, 48);
    Vec2 itemAnchor(0, 1);
    Vec2 itemPos(bgPos.x + bgSize.width + margin, bgPos.y + bgSize.height / 2);
    auto itemBg = ui::Scale9Sprite::createWithSpriteFrameName("item_bg.png");
    itemBg->setContentSize(itemSize);
    itemBg->setAnchorPoint(itemAnchor);
    itemBg->setPosition(itemPos);
    _playerDlg->addChild(itemBg);
    
    auto item = ui::Button::create("crystal.png", "", "", ui::TextureResType::PLIST);
    item->setScale(1.5);
    item->setAnchorPoint(itemAnchor);
    item->setPosition(itemPos);
    item->addClickEventListener([this](Ref* sender){
        this->_detailDlg->setVisible(!this->_detailDlg->isVisible());
    });
    _playerDlg->addChild(item);
    
    // after add ui element, add player dialog to scene
    _playerDlg->setCameraMask(s_CM[LAYER_UI]);
    this->addChild(_playerDlg);
    
    // second, add 3d actor, which on dialog layer
    std::string filename = "Sprite3DTest/girl.c3b";
    auto girl = Sprite3D::create(filename);
    girl->setScale(0.5);
    girl->setPosition(bgSize.width / 2, margin * 2);
    girl->setCameraMask(s_CM[LAYER_ACTOR]);
    playerBg->addChild(girl);
    
    // third, add zoom in/out button, which is 2d ui element and over 3d actor
    ui::Button* zoomIn = ui::Button::create("cocosui/animationbuttonnormal.png",
                                    "cocosui/animationbuttonpressed.png");
    zoomIn->setScale(0.5);
    zoomIn->setAnchorPoint(Vec2(1, 1));
    zoomIn->setPosition(Vec2(bgSize.width / 2 - margin / 2, bgSize.height - margin));
    zoomIn->addClickEventListener([girl](Ref* sender){
        girl->setScale(girl->getScale() * 2);
    });
    zoomIn->setTitleText("Zoom In");
    zoomIn->setCameraMask(s_CM[LAYER_ZOOM]);
    playerBg->addChild(zoomIn);

    ui::Button* zoomOut = ui::Button::create("cocosui/animationbuttonnormal.png",
                                            "cocosui/animationbuttonpressed.png");
    zoomOut->setScale(0.5);
    zoomOut->setAnchorPoint(Vec2(0, 1));
    zoomOut->setPosition(Vec2(bgSize.width / 2 + margin / 2, bgSize.height - margin));
    zoomOut->addClickEventListener([girl](Ref* sender){
        girl->setScale(girl->getScale() / 2);
    });
    zoomOut->setTitleText("Zoom Out");
    zoomOut->setCameraMask(s_CM[LAYER_ZOOM]);
    playerBg->addChild(zoomOut);
}

void Scene3DTestScene::createDetailDlg()
{
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(s_s9s_ui_plist);
    
    Size dlgSize(190, 240);
    Vec2 pos = VisibleRect::center();
    float margin = 10;
    
    // create dialog
    _detailDlg = ui::Scale9Sprite::createWithSpriteFrameName("button_actived.png");
    _detailDlg->setContentSize(dlgSize);
    _detailDlg->setAnchorPoint(Vec2(0, 0.5));
    _detailDlg->setOpacity(224);
    pos.y -= margin;
    pos.x += margin;
    _detailDlg->setPosition(pos);
    
    // title
    auto title = Label::createWithTTF("Detail Dialog","fonts/arial.ttf",16);
    title->setPosition(dlgSize.width / 2, dlgSize.height - margin * 2);
    _detailDlg->addChild(title);
    
    // add a spine ffd animation on it
    auto skeletonNode = SkeletonAnimation::createWithFile("spine/goblins-ffd.json", "spine/goblins-ffd.atlas", 1.5f);
    skeletonNode->setAnimation(0, "walk", true);
    skeletonNode->setSkin("goblin");
    
    skeletonNode->setScale(0.25);
    Size windowSize = Director::getInstance()->getWinSize();
    skeletonNode->setPosition(Vec2(dlgSize.width / 2, 20));
    _detailDlg->addChild(skeletonNode);
    
    scheduleUpdate();
    
    EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [skeletonNode] (Touch* touch, Event* event) -> bool {
        if (!skeletonNode->getDebugBonesEnabled())
            skeletonNode->setDebugBonesEnabled(true);
        else if (skeletonNode->getTimeScale() == 1)
            skeletonNode->setTimeScale(0.3f);
        else
        {
            skeletonNode->setTimeScale(1);
            skeletonNode->setDebugBonesEnabled(false);
        }
        return true;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    // after add ui element, add dialog to scene
    _detailDlg->setCameraMask(s_CM[LAYER_UI]);
    this->addChild(_detailDlg);
}

void Scene3DTestScene::createDescDlg()
{
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(s_s9s_ui_plist);
    
    Size dlgSize(440, 240);
    Vec2 pos = VisibleRect::center();
    float margin = 10;
    
    // create dialog
    _descDlg = ui::Scale9Sprite::createWithSpriteFrameName("button_actived.png");
    _descDlg->setContentSize(dlgSize);
    _descDlg->setOpacity(224);
    _descDlg->setPosition(pos);
    
    // title
    auto title = Label::createWithTTF("Description Dialog","fonts/arial.ttf",16);
    title->setPosition(dlgSize.width / 2, dlgSize.height - margin * 2);
    _descDlg->addChild(title);
    
    // add a label to retain description text
    Size textSize(400, 220);
    auto desc =
    "Scene 3D test for 2D and 3D mix rendering.\n"
    "\n"
    "- Game world composite with terrain, skybox and 3D objects.\n"
    "- UI composite with 2D nodes.\n"
    "- Click the icon at the topleft conner, will show a player dialog which "
    "there is a 3D sprite on it.\n"
    "- There are two button to zoom the player model, which should keep above "
    "on 3D model.\n"
    " - This description dialog should above all other elements.\n"
    "\n"
    "Click \"Description\" button to hide this dialog.\n";
    auto text = Label::createWithSystemFont(desc, "Helvetica", 12, textSize);
    text->setAnchorPoint(Vec2(0, 1));
    text->setPosition(margin, dlgSize.height - (20 + margin));
    _descDlg->addChild(text);
    
    // after add ui element, add dialog to scene
    _descDlg->setCameraMask(s_CM[LAYER_OSD]);
    this->addChild(_descDlg);
}

////////////////////////////////////////////////////////////////////////////////
// Implements Scene3DTests
Scene3DTests::Scene3DTests()
{
    ADD_TEST_CASE(Scene3DTestScene);
}
