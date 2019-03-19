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

#include "Scene3DTest.h"

#include "ui/CocosGUI.h"
#include "renderer/CCRenderState.h"
#include <spine/spine-cocos2dx.h>

#include "../testResource.h"
#include "../TerrainTest/TerrainTest.h"

USING_NS_CC;
using namespace spine;

class SkeletonAnimationCullingFix : public SkeletonAnimation
{
public:
    SkeletonAnimationCullingFix()
    : SkeletonAnimation()
    {}
    
    virtual void draw(cocos2d::Renderer* renderer, const cocos2d::Mat4& transform, uint32_t transformFlags) override
    {
        glDisable(GL_CULL_FACE);
        SkeletonAnimation::draw(renderer, transform, transformFlags);
        RenderState::StateBlock::invalidate(cocos2d::RenderState::StateBlock::RS_ALL_ONES);
    }
    
    static SkeletonAnimationCullingFix* createWithFile (const std::string& skeletonDataFile, const std::string& atlasFile, float scale = 1)
    {
        SkeletonAnimationCullingFix* node = new SkeletonAnimationCullingFix();
        spAtlas* atlas = spAtlas_createFromFile(atlasFile.c_str(), 0);
        node->initWithJsonFile(skeletonDataFile, atlas, scale);
        node->autorelease();
        return node;
    }
};

////////////////////////////////////////////////////////////////////////////////
// Declare Scene3DTestScene

/** Scene3DTestScene designed for test 2D-3D mixed render for common 3D game usage.
 *
 *  Scene has three logic sub scenes:
 *  -   World scene for maintain 3D game world objects, there are two cameras in this
 *      scene, one for skybox, another for other 3D models.
 *  -   UI scene, the root scene, maintain a menu in main UI.
 *  -   Dialog scene maintain two dialogs, which has 3D models on it and another
 *      2D elements above on 3D models, there are three cameras for them.
 *  -   OSD scene, maintain the UI element, like the description dialog, above
 *  -   on other elements.
 */
class Scene3DTestScene : public TestCase
{
public:
    CREATE_FUNC(Scene3DTestScene);
    
    bool onTouchBegan(Touch* touch, Event* event) { return true; }
    void onTouchEnd(Touch*, Event*);
    
private:
    Scene3DTestScene();
    virtual ~Scene3DTestScene();
    bool init() override;
    
    void createWorld3D();
    void createUI();
    void createPlayerDlg();
    void createDetailDlg();
    void createDescDlg();
    
    // init in init()
    std::vector<Camera *> _gameCameras;
    Node* _worldScene;
    Node* _dlgScene;
    Node* _osdScene;
    
    // init in createWorld3D()
    TextureCube*        _textureCube;
    Skybox*             _skyBox;
    cocos2d::Terrain*   _terrain;
    Player *            _player;
    Node*               _monsters[2];
    
    // init in createUI()
    Node* _playerItem;
    Node* _detailItem;
    Node* _descItem;
    Node* _ui;
    
    // init in createPlayerDlg()
    Node* _playerDlg;
    // init in createDetailDlg()
    Node* _detailDlg;
    // init in createDescDlg()
    Node* _descDlg;
    enum SkinType
    {
        HAIR = 0,
        GLASSES,
        FACE,
        UPPER_BODY,
        HAND,
        PANTS,
        SHOES,
        MAX_TYPE,
    };
    
    std::vector<std::string> _skins[(int)SkinType::MAX_TYPE]; //all skins
    int                      _curSkin[(int)SkinType::MAX_TYPE]; //current skin index
    cocos2d::Sprite3D* _reskinGirl;
    
    // for capture screen
    static const int SNAPSHOT_TAG = 119;
    std::string _snapshotFile;
};

/** Define the sub scenes in test. */
enum GAME_SCENE {
    SCENE_UI = 0,
    SCENE_WORLD,
    SCENE_DIALOG,
    SCENE_OSD,
    SCENE_COUNT,
};

/** Define the layers in scene, layer separated by camera mask. */
enum SCENE_LAYER {
    LAYER_BACKGROUND = 0,
    LAYER_DEFAULT,
    LAYER_MIDDLE,
    LAYER_TOP,
    LAYER_COUNT,
};

/** Define the all cameras, which in Scene3DTest, render order. */
enum GAME_CAMERAS_ORDER {
    CAMERA_WORLD_3D_SKYBOX = 0,
    CAMERA_WORLD_3D_SCENE,
    CAMERA_UI_2D,
    CAMERA_DIALOG_2D_BASE,
    CAMERA_DIALOG_3D_MODEL,
    CAMERA_DIALOG_2D_ABOVE,
    CAMERA_OSD_2D_BASE,
    CAMERA_OSD_3D_MODEL,
    CAMERA_OSD_2D_ABOVE,
    CAMERA_COUNT,
};

/*
 Defined s_CF and s_CM to avoid force conversion when call Camera::setCameraFlag
 and Node::setCameraMask.
 
 Usage:
 -   Camera::setCameraFlag(s_CF[<SCENE_LAYER_INDEX>]);
 -   Node::setCameraMask(s_CM[<SCENE_LAYER_INDEX>]);
 
 Note:
 For LAYER_DEFAULT, we use CameraFlag::DEFAULT, thus we don't need to set
 camera flag/mask for this layer, for other layers we must to set camera
 flag/mask to distinguish between each other.
 */
static CameraFlag s_CF[LAYER_COUNT] =
{
    CameraFlag::USER1,      //  LAYER_BACKGROUND
    CameraFlag::DEFAULT,    //  LAYER_DEFAULT
    CameraFlag::USER3,      //  LAYER_MIDDLE
    CameraFlag::USER4,      //  LAYER_TOP
};

static unsigned short s_CM[LAYER_COUNT] =
{
    (unsigned short)s_CF[0],
    (unsigned short)s_CF[1],
    (unsigned short)s_CF[2],
    (unsigned short)s_CF[3],
};

static const char * s_CameraNames[CAMERA_COUNT] =
{
    "World 3D Skybox",
    "World 3D Scene",
    "UI 2D",
    "Dialog 2D Base",
    "Dialog 3D Model",
    "Dialog 2D Above",
    "OSD 2D Base",
    "OSD 3D Model",
    "OSD 2D Above"
};

/** The scenes, located in different position, won't see each other. */
static Vec3 s_scenePositons[SCENE_COUNT] = {
    Vec3(0, 0, 0),          //  center  :   UI scene
    Vec3(0, 10000, 0),      //  top     :   World sub scene
    Vec3(10000, 0, 0),      //  right   :   Dialog sub scene
    Vec3(0, -10000, 0),     //  bottom  :   OSD sub scene
};

////////////////////////////////////////////////////////////////////////////////
// Implements Scene3DTestScene

Scene3DTestScene::Scene3DTestScene()
: _worldScene(nullptr)
, _dlgScene(nullptr)
, _osdScene(nullptr)
, _textureCube(nullptr)
, _skyBox(nullptr)
, _terrain(nullptr)
, _player(nullptr)
, _playerItem(nullptr)
, _detailItem(nullptr)
, _descItem(nullptr)
, _ui(nullptr)
, _playerDlg(nullptr)
, _detailDlg(nullptr)
, _descDlg(nullptr)
{
    _monsters[0] = _monsters[1] = nullptr;
}

Scene3DTestScene::~Scene3DTestScene()
{
}

bool Scene3DTestScene::init()
{
    bool ret = false;
    do
    {
        CC_BREAK_IF(false == TestCase::init());

        // prepare for camera creation, we need several custom cameras
        _gameCameras.resize(CAMERA_COUNT);
        auto visibleSize = Director::getInstance()->getVisibleSize();
        Camera *ca = nullptr;   // temp variable
        
        ////////////////////////////////////////////////////////////////////////
        // create world 3D scene, this scene has two camera
        _worldScene = Node::create();
        // create a camera to look the skybox
        ca = _gameCameras[CAMERA_WORLD_3D_SKYBOX] =
            Camera::createPerspective(60,
                                      visibleSize.width / visibleSize.height,
                                      10,
                                      1000);
        ca->setDepth(CAMERA_WORLD_3D_SKYBOX);
        ca->setName(s_CameraNames[CAMERA_WORLD_3D_SKYBOX]);
        ca->setCameraFlag(s_CF[LAYER_BACKGROUND]);
        ca->setPosition3D(Vec3(0.f, 0.f, 50.f));
        _worldScene->addChild(ca);
        // create a camera to look the 3D models in world 3D scene
        ca = _gameCameras[CAMERA_WORLD_3D_SCENE] =
            Camera::createPerspective(60,
                                      visibleSize.width/visibleSize.height,
                                      0.1f,
                                      200);
        ca->setDepth(CAMERA_WORLD_3D_SCENE);
        ca->setName(s_CameraNames[CAMERA_WORLD_3D_SCENE]);
        _worldScene->addChild(ca);
        // create 3D objects and add to world scene
        createWorld3D();
        _worldScene->addChild(_skyBox);
        _worldScene->addChild(_terrain);
        _worldScene->addChild(_player);
        _worldScene->addChild(_monsters[0]);
        _worldScene->addChild(_monsters[1]);
        // move camera above player
        ca->setPosition3D(_player->getPosition3D()+Vec3(0, 45, 60));
        ca->setRotation3D(Vec3(-45,0,0));
        _worldScene->setPosition3D(s_scenePositons[SCENE_WORLD]);
        this->addChild(_worldScene);
        
        ////////////////////////////////////////////////////////////////////////
        // test scene is UI scene, use default camera
        // use the default camera to look 2D base UI layer
        ca = _gameCameras[CAMERA_UI_2D] = this->getDefaultCamera();
        ca->setDepth(CAMERA_UI_2D);
        ca->setName(s_CameraNames[CAMERA_UI_2D]);
        // create UI element and add to ui scene
        createUI();
        this->addChild(_ui);
        
        ////////////////////////////////////////////////////////////////////////
        // create dialog scene, this scene has two dialog and three cameras
        _dlgScene = Node::create();
        // use default camera to render the base 2D elements
        ca = _gameCameras[CAMERA_DIALOG_2D_BASE] = Camera::create();
        ca->setDepth(CAMERA_DIALOG_2D_BASE);
        ca->setName(s_CameraNames[CAMERA_DIALOG_2D_BASE]);
        _dlgScene->addChild(ca);
        // create a camera to look the 3D model in dialog scene
        ca = _gameCameras[CAMERA_DIALOG_3D_MODEL] = Camera::create();
        ca->setDepth(CAMERA_DIALOG_3D_MODEL);
        ca->setName(s_CameraNames[CAMERA_DIALOG_3D_MODEL]);
        ca->setCameraFlag(s_CF[LAYER_MIDDLE]);
        _dlgScene->addChild(ca);
        // create a camera to look the UI element over on the 3D models
        ca = _gameCameras[CAMERA_DIALOG_2D_ABOVE] = Camera::create();
        ca->setDepth(CAMERA_DIALOG_2D_ABOVE);
        ca->setName(s_CameraNames[CAMERA_DIALOG_2D_ABOVE]);
        ca->setCameraFlag(s_CF[LAYER_TOP]);
        _dlgScene->addChild(ca);
        // create dialogs and add to dialog scene
        createPlayerDlg();
        _dlgScene->addChild(_playerDlg);
        createDetailDlg();
        _dlgScene->addChild(_detailDlg);
        // add dialog scene to test scene, which can't see the other element
        _dlgScene->setPosition3D(s_scenePositons[SCENE_DIALOG]);
        this->addChild(_dlgScene);

        ////////////////////////////////////////////////////////////////////////
        // create description scene, this scene has a dialog and three cameras
        _osdScene = Node::create();
        // use default camera for render 2D element
        ca = _gameCameras[CAMERA_OSD_2D_BASE] = Camera::create();
        ca->setDepth(CAMERA_OSD_2D_BASE);
        ca->setName(s_CameraNames[CAMERA_OSD_2D_BASE]);
        _osdScene->addChild(ca);
        // create a camera to look the 3D model in dialog scene
        ca = _gameCameras[CAMERA_OSD_3D_MODEL] = Camera::create();
        ca->setDepth(CAMERA_OSD_3D_MODEL);
        ca->setName(s_CameraNames[CAMERA_OSD_3D_MODEL]);
        ca->setCameraFlag(s_CF[LAYER_MIDDLE]);
        _osdScene->addChild(ca);
        // create a camera to look the UI element over on the 3D models
        ca = _gameCameras[CAMERA_OSD_2D_ABOVE] = Camera::create();
        ca->setDepth(CAMERA_OSD_2D_ABOVE);
        ca->setName(s_CameraNames[CAMERA_OSD_2D_ABOVE]);
        ca->setCameraFlag(s_CF[LAYER_TOP]);
        _osdScene->addChild(ca);
        // create desc dialog and add to osd scene
        createDescDlg();
        _osdScene->addChild(_descDlg);
        // add osd scene to test scene, which can't see the other elements
        _osdScene->setPosition3D(s_scenePositons[SCENE_OSD]);
        this->addChild(_osdScene);

        _playerDlg->setVisible(false);
        _detailDlg->setVisible(false);
        _descDlg->setVisible(false);

        ////////////////////////////////////////////////////////////////////////
        // add touch event callback
        auto listener = EventListenerTouchOneByOne::create();
        listener->onTouchBegan = CC_CALLBACK_2(Scene3DTestScene::onTouchBegan, this);
        listener->onTouchEnded = CC_CALLBACK_2(Scene3DTestScene::onTouchEnd, this);
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

        ret = true;
    } while (0);
    
    return ret;
}

void Scene3DTestScene::createWorld3D()
{
    // create skybox
    //create and set our custom shader
    auto shader = GLProgram::createWithFilenames("Sprite3DTest/cube_map.vert",
                                                 "Sprite3DTest/cube_map.frag");
    auto state = GLProgramState::create(shader);
    
    // create the second texture for cylinder
    _textureCube = TextureCube::create("Sprite3DTest/skybox/left.jpg",
                                       "Sprite3DTest/skybox/right.jpg",
                                       "Sprite3DTest/skybox/top.jpg",
                                       "Sprite3DTest/skybox/bottom.jpg",
                                       "Sprite3DTest/skybox/front.jpg",
                                       "Sprite3DTest/skybox/back.jpg");
    //set texture parameters
    Texture2D::TexParams tRepeatParams;
    tRepeatParams.magFilter = GL_LINEAR;
    tRepeatParams.minFilter = GL_LINEAR;
    tRepeatParams.sAddressMode = GL_MIRRORED_REPEAT;
    tRepeatParams.tAddressMode = GL_MIRRORED_REPEAT;
    _textureCube->setTexParameters(tRepeatParams);
    
    // pass the texture sampler to our custom shader
    state->setUniformTexture("u_cubeTex", _textureCube);
    
    // add skybox
    _skyBox = Skybox::create();
    _skyBox->setCameraMask(s_CM[LAYER_BACKGROUND]);
    _skyBox->setTexture(_textureCube);

    // create terrain
    Terrain::DetailMap r("TerrainTest/dirt.jpg");
    Terrain::DetailMap g("TerrainTest/Grass2.jpg",10);
    Terrain::DetailMap b("TerrainTest/road.jpg");
    Terrain::DetailMap a("TerrainTest/GreenSkin.jpg",20);
    Terrain::TerrainData data("TerrainTest/heightmap16.jpg",
                              "TerrainTest/alphamap.png",
                              r,g,b,a,Size(32,32),40.0f,2);
    _terrain = Terrain::create(data,Terrain::CrackFixedType::SKIRT);
    _terrain->setMaxDetailMapAmount(4);
    _terrain->setDrawWire(false);

    _terrain->setSkirtHeightRatio(3);
    _terrain->setLODDistance(64,128,192);
    
    // create player
    _player = Player::create("Sprite3DTest/girl.c3b",
                             _gameCameras[CAMERA_WORLD_3D_SCENE],
                             _terrain);
    _player->setScale(0.08f);
    _player->setPositionY(_terrain->getHeight(_player->getPositionX(),
                                              _player->getPositionZ()));
    
    auto animation = Animation3D::create("Sprite3DTest/girl.c3b","Take 001");
    if (animation)
    {
        auto animate = Animate3D::create(animation);
        _player->runAction(RepeatForever::create(animate));
    }
    // add a particle 3d above player
    auto rootps =
        PUParticleSystem3D::create("Particle3D/scripts/blackHole.pu",
                                   "Particle3D/materials/pu_mediapack_01.material");
    rootps->setScale(2);
    rootps->setPosition3D(Vec3(0, 150, 0));
    auto moveby = MoveBy::create(2.0f, Vec2(50.0f, 0.0f));
    auto moveby1 = MoveBy::create(2.0f, Vec2(-50.0f, 0.0f));
    rootps->runAction(RepeatForever::create(Sequence::create(moveby, moveby1, nullptr)));
    rootps->startParticleSystem();
    
    _player->addChild(rootps, 0);
    
    // add BillBoard for test blend
    auto billboard = BillBoard::create("Images/btn-play-normal.png");
    billboard->setPosition3D(Vec3(0,180,0));
    _player->addChild(billboard);
    
    // create two Sprite3D monster, one is transparent
    auto monster = Sprite3D::create("Sprite3DTest/orc.c3b");
    monster->setRotation3D(Vec3(0,180,0));
    monster->setPosition3D(_player->getPosition3D() + Vec3(50, -10, 0));
    monster->setOpacity(128);
    _monsters[0] = monster;
    monster = Sprite3D::create("Sprite3DTest/orc.c3b");
    monster->setRotation3D(Vec3(0,180,0));
    monster->setPosition3D(_player->getPosition3D() + Vec3(-50, -5, 0));
    _monsters[1] = monster;
}

void Scene3DTestScene::createUI()
{
    _ui = Layer::create();
    
    // first, add menu to ui
    // create player button
    auto showPlayerDlgItem = MenuItemImage::create("Images/Pea.png",
                                                   "Images/Pea.png",
                                                   [this](Ref* sender){
        this->_playerDlg->setVisible(!this->_playerDlg->isVisible());
    });
    showPlayerDlgItem->setName("showPlayerDlgItem");
    showPlayerDlgItem->setPosition(VisibleRect::left().x + 30, VisibleRect::top().y - 30);
    
    // create description button
    TTFConfig ttfConfig("fonts/arial.ttf", 20);
    auto descItem = MenuItemLabel::create(Label::createWithTTF(ttfConfig, "Description"),
                                          [this](Ref* sender)
    {
        if (this->_descDlg->isVisible())
        {
            // hide descDlg
            _descDlg->setVisible(false);
        }
        else
        {
            // animate show descDlg
            _descDlg->setVisible(true);
            _descDlg->setScale(0);
            _descDlg->runAction(ScaleTo::create(2, 1.0));
        }
    });
    descItem->setName("descItem");
    descItem->setPosition(Vec2(VisibleRect::right().x - 50, VisibleRect::top().y - 25));

    auto menu = Menu::create(showPlayerDlgItem,
                             descItem,
                             nullptr);
    menu->setPosition(Vec2::ZERO);
    _ui->addChild(menu);
    
    // second, add cameras control button to ui
    auto createCameraButton = [this](int tag, const char* text)-> Node *
    {
        auto cb = ui::CheckBox::create("cocosui/check_box_normal.png",
                                       "cocosui/check_box_normal_press.png",
                                       "cocosui/check_box_active.png",
                                       "cocosui/check_box_normal_disable.png",
                                       "cocosui/check_box_active_disable.png");
        cb->setTag(tag);
        cb->setSelected(true);
        if (text) cb->setName(text);
        cb->setAnchorPoint(Vec2(0, 0.5));
        cb->setScale(0.8f);
        cb->addClickEventListener([this](Ref* sender)
            {
                auto index = static_cast<Node *>(sender)->getTag();
                auto camera = this->_gameCameras[index];
                camera->setVisible(!camera->isVisible());
            });
        if (text)
        {
            auto label = ui::Text::create();
            label->setString(text);
            label->setAnchorPoint(Vec2(0, 0));
            label->setPositionX(cb->getContentSize().width);
            cb->addChild(label);
        }
        return cb;
    };
    
    Vec2 pos = VisibleRect::leftBottom();
    pos.y += 30;
    float stepY = 25;
    for (int i = CAMERA_COUNT - 1; i >= 0; --i)
    {
        // if hide CAMERA_UI_2D, the menu won't show again
        // so skip it
        if (CAMERA_UI_2D == i)
        {
            continue;
        }
        auto cameraBtn = createCameraButton(i, s_CameraNames[i]);
        cameraBtn->setPosition(pos);
        _ui->addChild(cameraBtn);
        pos.y += stepY;
    }
    auto labelCameras = ui::Text::create();
    labelCameras->setString("Cameras");
    labelCameras->setAnchorPoint(Vec2(0, 0));
    labelCameras->setPosition(pos);
    _ui->addChild(labelCameras);
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
    
    auto item = ui::Button::create("crystal.png", "", "", ui::Widget::TextureResType::PLIST);
    item->setTitleText("Crystal");
    item->setScale(1.5);
    item->setAnchorPoint(itemAnchor);
    item->setPosition(itemPos);
    item->addClickEventListener([this](Ref* sender){
        this->_detailDlg->setVisible(!this->_detailDlg->isVisible());
    });
    _playerDlg->addChild(item);
    
    // second, add 3d actor, which on dialog layer
    std::string filename = "Sprite3DTest/girl.c3b";
    auto girl = Sprite3D::create(filename);
    girl->setScale(0.5);
    girl->setPosition(bgSize.width / 2, margin * 2);
    girl->setCameraMask(s_CM[LAYER_MIDDLE]);
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
    zoomIn->setName("Zoom In");
    zoomIn->setCameraMask(s_CM[LAYER_TOP]);
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
    zoomOut->setName("Zoom Out");
    zoomOut->setCameraMask(s_CM[LAYER_TOP]);
    playerBg->addChild(zoomOut);
    
    // forth, add slider bar
    ui::Slider* slider = ui::Slider::create("cocosui/slidbar.png", "cocosui/sliderballnormal.png");
    slider->setScale9Enabled(true);
    slider->setPosition(Vec2(bgSize.width / 2, margin));
    slider->setContentSize(Size(bgSize.width - margin, slider->getContentSize().height));
    slider->addEventListener([girl, slider](Ref* sender,ui::Slider::EventType type)
    {
        girl->setRotation3D(Vec3(0, 360 * slider->getPercent() / 100, 0));
    });
    slider->setName("Slider");
    slider->setCameraMask(s_CM[LAYER_TOP]);
    playerBg->addChild(slider);
}

void Scene3DTestScene::createDetailDlg()
{
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(s_s9s_ui_plist);
    
    Size dlgSize(190, 240);
    Vec2 pos = VisibleRect::center();
    float margin = 10;
    
    // create dialog
    // use Scale9Sprite as background, it won't swallow touch event
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

    
    // add capture screen buttons
    ui::Button* capture = ui::Button::create("cocosui/animationbuttonnormal.png",
                                             "cocosui/animationbuttonpressed.png");
    capture->setScale(0.5);
    capture->setAnchorPoint(Vec2(0.5, 0));
    capture->setPosition(Vec2(dlgSize.width / 3, margin));
    capture->addClickEventListener([this](Ref* sender)
    {
        Director::getInstance()->getTextureCache()->removeTextureForKey(_snapshotFile);
        _osdScene->removeChildByTag(SNAPSHOT_TAG);
        _snapshotFile = "CaptureScreenTest.png";
        utils::captureScreen([this](bool succeed, const std::string& outputFile)
        {
            if (!succeed)
            {
                log("Capture screen failed.");
                return;
            }
            auto sp = Sprite::create(outputFile);
            _osdScene->addChild(sp, 0, SNAPSHOT_TAG);
            Size s = Director::getInstance()->getWinSize();
            sp->setPosition(s.width / 2, s.height / 2);
            sp->setScale(0.25);
            _snapshotFile = outputFile;
        }, _snapshotFile);
    });
    capture->setTitleText("Take Snapshot");
    capture->setName("Take Snapshot");
    _detailDlg->addChild(capture);
    
    ui::Button* remove = ui::Button::create("cocosui/animationbuttonnormal.png",
                                            "cocosui/animationbuttonpressed.png");
    remove->setScale(0.5);
    remove->setAnchorPoint(Vec2(0.5, 0));
    remove->setPosition(Vec2(dlgSize.width * 2 / 3, margin));
    remove->addClickEventListener([this](Ref* sender)
    {
        _osdScene->removeChildByTag(SNAPSHOT_TAG);
    });
    remove->setTitleText("Del Snapshot");
    remove->setName("Del Snapshot");
    _detailDlg->addChild(remove);
    
    // add a spine ffd animation on it
    auto skeletonNode =
        SkeletonAnimationCullingFix::createWithFile("spine/goblins-pro.json", "spine/goblins.atlas", 1.5f);
    skeletonNode->setAnimation(0, "walk", true);
    skeletonNode->setSkin("goblin");
    
    skeletonNode->setScale(0.25);
    Size windowSize = Director::getInstance()->getWinSize();
    skeletonNode->setPosition(Vec2(dlgSize.width / 2, remove->getContentSize().height / 2 + 2 * margin));
    _detailDlg->addChild(skeletonNode);
}

void Scene3DTestScene::createDescDlg()
{
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(s_s9s_ui_plist);
    
    Size dlgSize(440, 240);
    Vec2 pos = VisibleRect::center();
    float margin = 10;
    
    // first, create dialog, add title and description text on it
    // use Layout, which setTouchEnabled(true), as background, it will swallow touch event
    auto desdDlg = ui::Layout::create();
    desdDlg->setBackGroundImageScale9Enabled(true);
    desdDlg->setBackGroundImage("button_actived.png", ui::Widget::TextureResType::PLIST);
    desdDlg->setContentSize(dlgSize);
    desdDlg->setAnchorPoint(Vec2(0.5f, 0.5f));
    desdDlg->setOpacity(224);
    desdDlg->setPosition(pos);
    desdDlg->setTouchEnabled(true);
    _descDlg = desdDlg;

    
    // title
    auto title = Label::createWithTTF("Description Dialog","fonts/arial.ttf",16);
    title->setPosition(dlgSize.width / 2, dlgSize.height - margin * 2);
    _descDlg->addChild(title);

    // add a label to retain description text
    Size textSize(400, 220);
    Vec2 textPos(margin, dlgSize.height - (20 + margin));
    std::string desc = std::string(
    "    Scene 3D test for 2D and 3D mix rendering.\n"
    "- Game world composite with terrain, skybox and 3D objects.\n"
    "- UI composite with 2D nodes.\n"
    "- Click the icon at the topleft conner, will show a player dialog which "
    "there is a 3D sprite on it.\n"
    "- There are two button to zoom the player model, which should keep above "
    "on 3D model.\n"
    " - This description dialog should above all other elements.\n"
    "\n"
    "    Game scene composite with root scene and three sub scene. These scene "
    " located at different location, they can't see each other.\n"
    "- Root scene contains ui layer\n"
    "- World scene contains skybox and 3d scene.\n"
    "- Dialog scene contains actor dialog and detail dialog.\n"
    "- OSD scene contains description dialog.\n"
    "\n"
    "Click \"Description\" button to hide this dialog.\n");
    auto text = Label::createWithSystemFont(desc, "", 9, textSize);
    text->setAnchorPoint(Vec2(0, 1));
    text->setPosition(textPos);
    _descDlg->addChild(text);
    
    // second, add a 3D model
    std::string fileName = "Sprite3DTest/ReskinGirl.c3b";
    Vec2 girlPos(textPos.x + textSize.width - 40, margin);
    _reskinGirl = Sprite3D::create(fileName);
    _reskinGirl->setCameraMask(s_CM[LAYER_MIDDLE]);
    _reskinGirl->setScale(2.5);
    _reskinGirl->setPosition(girlPos);
    _descDlg->addChild(_reskinGirl);
    auto animation = Animation3D::create(fileName);
    if (animation)
    {
        auto animate = Animate3D::create(animation);
        
        _reskinGirl->runAction(RepeatForever::create(animate));
    }
    
    auto& body = _skins[(int)SkinType::UPPER_BODY];
    body.push_back("Girl_UpperBody01");
    body.push_back("Girl_UpperBody02");
    
    auto& pants = _skins[(int)SkinType::PANTS];
    pants.push_back("Girl_LowerBody01");
    pants.push_back("Girl_LowerBody02");
    
    auto& shoes = _skins[(int)SkinType::SHOES];
    shoes.push_back("Girl_Shoes01");
    shoes.push_back("Girl_Shoes02");
    
    auto& hair = _skins[(int)SkinType::HAIR];
    hair.push_back("Girl_Hair01");
    hair.push_back("Girl_Hair02");
    
    auto& face = _skins[(int)SkinType::FACE];
    face.push_back("Girl_Face01");
    face.push_back("Girl_Face02");
    
    auto& hand = _skins[(int)SkinType::HAND];
    hand.push_back("Girl_Hand01");
    hand.push_back("Girl_Hand02");
    
    auto& glasses = _skins[(int)SkinType::GLASSES];
    glasses.push_back("");
    glasses.push_back("Girl_Glasses01");
    
    memset(_curSkin, 0, (int)SkinType::MAX_TYPE * sizeof(int));
    
    auto applyCurSkin = [this]()
    {
        for (ssize_t i = 0; i < this->_reskinGirl->getMeshCount(); i++) {
            auto mesh = this->_reskinGirl->getMeshByIndex(static_cast<int>(i));
            bool isVisible = false;
            for (int j = 0; j < (int)SkinType::MAX_TYPE; j++) {
                if (mesh->getName() == _skins[j].at(_curSkin[j]))
                {
                    isVisible = true;
                    break;
                }
            }
            this->_reskinGirl->getMeshByIndex(static_cast<int>(i))->setVisible(isVisible);
        }
    };
    applyCurSkin();
    
    // third, add reskin buttons above 3D model
    static const std::string btnTexts[SkinType::MAX_TYPE] =
    {
        "Hair",
        "Glasses",
        "Face",
        "Coat",
        "Hand",
        "Pants",
        "Shoes",
    };
    Vec2 btnPos(dlgSize.width - margin, margin);
    for (int i = SkinType::MAX_TYPE - 1; i >= 0; --i) {
        auto btn = ui::Button::create("cocosui/animationbuttonnormal.png",
                                      "cocosui/animationbuttonpressed.png");
        btn->setScale(0.5);
        btn->setTag(i);
        btn->setAnchorPoint(Vec2(1, 0));
        btn->setPosition(btnPos);
        btnPos.y += 20;
        btn->addClickEventListener([this, applyCurSkin](Ref* sender)
        {
            auto index = static_cast<Node *>(sender)->getTag();
            if (index < SkinType::MAX_TYPE)
            {
                _curSkin[index] = (_curSkin[index] + 1) % _skins[index].size();
                applyCurSkin();
            }
        });
        btn->setTitleText(btnTexts[i]);
        btn->setCameraMask(s_CM[LAYER_TOP]);
        _descDlg->addChild(btn);
    }
}

void Scene3DTestScene::onTouchEnd(Touch* touch, Event* event)
{
    auto location = touch->getLocation();
    auto camera = _gameCameras[CAMERA_WORLD_3D_SCENE];
    if(camera != Camera::getVisitingCamera())
    {
        return;
    }

    if(_player)
    {
        Vec3 nearP(location.x, location.y, 0.0f), farP(location.x, location.y, 1.0f);
        // convert screen touch location to the world location on near and far plane
        auto size = Director::getInstance()->getWinSize();
        camera->unprojectGL(size, &nearP, &nearP);
        camera->unprojectGL(size, &farP, &farP);
        Vec3 dir = farP - nearP;
        dir.normalize();
        Vec3 collisionPoint;
        bool isInTerrain = _terrain->getIntersectionPoint(Ray(nearP, dir), collisionPoint);
        if (!isInTerrain)
        {
            _player->idle();
        }
        else
        {
            dir = collisionPoint - _player->getPosition3D();
            dir.y = 0;
            dir.normalize();
            _player->_headingAngle =  -1*acos(dir.dot(Vec3(0,0,-1)));
            dir.cross(dir,Vec3(0,0,-1),&_player->_headingAxis);
            _player->_targetPos=collisionPoint;
            _player->forward();
        }
    }
    event->stopPropagation();
}

////////////////////////////////////////////////////////////////////////////////
// Implements Scene3DTests
Scene3DTests::Scene3DTests()
{
    ADD_TEST_CASE(Scene3DTestScene);
}
