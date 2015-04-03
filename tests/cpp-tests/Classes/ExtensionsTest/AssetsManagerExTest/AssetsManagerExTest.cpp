#include "AssetsManagerExTest.h"
#include "../../testResource.h"
#include "cocos2d.h"

const char* sceneManifests[] = {"AMTestScene1/project.manifest", "AMTestScene2/project.manifest", "AMTestScene3/project.manifest"};
const char* storagePaths[] = {"CppTests/AssetsManagerExTest/scene1/", "CppTests/AssetsManagerExTest/scene2/", "CppTests/AssetsManagerExTest/scene3"};
const char* backgroundPaths[] = {"Images/assetMgrBackground1.jpg", "Images/assetMgrBackground2.png", "Images/assetMgrBackground3.png"};

AssetsManagerExTestLayer::AssetsManagerExTestLayer(const std::string& spritePath)
: _spritePath(spritePath)
{
}

AssetsManagerExTestLayer::~AssetsManagerExTestLayer(void)
{
}

std::string AssetsManagerExTestLayer::title() const
{
    return "AssetsManagerExTest";
}

void AssetsManagerExTestLayer::onEnter()
{
    BaseTest::onEnter();
    _background = Sprite::create(_spritePath);
    if (_background)
    {
        addChild(_background, 1);
        _background->setPosition( VisibleRect::center() );
    }
}

void AssetsManagerExTestLayer::restartCallback(Ref* sender)
{
}

void AssetsManagerExTestLayer::nextCallback(Ref* sender)
{
    if (AssetsManagerExLoaderScene::currentScene < 2)
    {
        AssetsManagerExLoaderScene::currentScene++;
    }
    else
    {
        AssetsManagerExLoaderScene::currentScene = 0;
    }
    auto scene = new AssetsManagerExLoaderScene();
    scene->runThisTest();
    scene->release();
}

void AssetsManagerExTestLayer::backCallback(Ref* sender)
{
    if (AssetsManagerExLoaderScene::currentScene > 0)
    {
        AssetsManagerExLoaderScene::currentScene--;
    }
    else AssetsManagerExLoaderScene::currentScene = 2;
    auto scene = new AssetsManagerExLoaderScene();
    scene->runThisTest();
    scene->release();
}


AssetsManagerExTestScene::AssetsManagerExTestScene(std::string background)
{
    auto layer = new AssetsManagerExTestLayer(background);
    addChild(layer);
    layer->release();
}

void AssetsManagerExTestScene::runThisTest()
{
}

int AssetsManagerExLoaderScene::currentScene = 0;
AssetsManagerExLoaderScene::AssetsManagerExLoaderScene()
: _progress(nullptr)
, _amListener(nullptr)
{
}

void AssetsManagerExLoaderScene::runThisTest()
{
    int currentId = currentScene;
    std::string manifestPath = sceneManifests[currentId], storagePath = FileUtils::getInstance()->getWritablePath() + storagePaths[currentId];
    CCLOG("Storage path for this test : %s", storagePath.c_str());
    
    Sprite *sprite = Sprite::create("Images/Icon.png");
    auto layer = Layer::create();
    addChild(layer);
    layer->addChild(sprite);
    sprite->setPosition( VisibleRect::center() );
    
    TTFConfig config("fonts/tahoma.ttf", 30);
    _progress = Label::createWithTTF(config, "0%", TextHAlignment::CENTER);
    _progress->setPosition( Vec2(VisibleRect::center().x, VisibleRect::center().y + 50) );
    layer->addChild(_progress);
    
    _am = AssetsManagerEx::create(manifestPath, storagePath);
    _am->retain();
    
    if (!_am->getLocalManifest()->isLoaded())
    {
        CCLOG("Fail to update assets, step skipped.");
        AssetsManagerExTestScene *scene = new AssetsManagerExTestScene(backgroundPaths[currentId]);
        Director::getInstance()->replaceScene(scene);
        scene->release();
    }
    else
    {
        _amListener = cocos2d::extension::EventListenerAssetsManagerEx::create(_am, [currentId, this](EventAssetsManagerEx* event){
            static int failCount = 0;
            AssetsManagerExTestScene *scene;
            switch (event->getEventCode())
            {
                case EventAssetsManagerEx::EventCode::ERROR_NO_LOCAL_MANIFEST:
                {
                    CCLOG("No local manifest file found, skip assets update.");
                    scene = new AssetsManagerExTestScene(backgroundPaths[currentId]);
                    Director::getInstance()->replaceScene(scene);
                    scene->release();
                }
                    break;
                case EventAssetsManagerEx::EventCode::UPDATE_PROGRESSION:
                {
                    std::string assetId = event->getAssetId();
                    float percent = event->getPercent();
                    std::string str;
                    if (assetId == AssetsManagerEx::VERSION_ID)
                    {
                        str = StringUtils::format("Version file: %.2f", percent) + "%";
                    }
                    else if (assetId == AssetsManagerEx::MANIFEST_ID)
                    {
                        str = StringUtils::format("Manifest file: %.2f", percent) + "%";
                    }
                    else
                    {
                        str = StringUtils::format("%.2f", percent) + "%";
                        CCLOG("%.2f Percent", percent);
                    }
                    if (this->_progress != nullptr)
                        this->_progress->setString(str);
                }
                    break;
                case EventAssetsManagerEx::EventCode::ERROR_DOWNLOAD_MANIFEST:
                case EventAssetsManagerEx::EventCode::ERROR_PARSE_MANIFEST:
                {
                    CCLOG("Fail to download manifest file, update skipped.");
                    scene = new AssetsManagerExTestScene(backgroundPaths[currentId]);
                    Director::getInstance()->replaceScene(scene);
                    scene->release();
                }
                    break;
                case EventAssetsManagerEx::EventCode::ALREADY_UP_TO_DATE:
                case EventAssetsManagerEx::EventCode::UPDATE_FINISHED:
                {
                    CCLOG("Update finished. %s", event->getMessage().c_str());
                    scene = new AssetsManagerExTestScene(backgroundPaths[currentId]);
                    Director::getInstance()->replaceScene(scene);
                    scene->release();
                }
                    break;
                case EventAssetsManagerEx::EventCode::UPDATE_FAILED:
                {
                    CCLOG("Update failed. %s", event->getMessage().c_str());

                    failCount ++;
                    if (failCount < 5)
                    {
                        _am->downloadFailedAssets();
                    }
                    else
                    {
                        CCLOG("Reach maximum fail count, exit update process");
                        failCount = 0;
                        scene = new AssetsManagerExTestScene(backgroundPaths[currentId]);
                        Director::getInstance()->replaceScene(scene);
                        scene->release();
                    }
                }
                    break;
                case EventAssetsManagerEx::EventCode::ERROR_UPDATING:
                {
                    CCLOG("Asset %s : %s", event->getAssetId().c_str(), event->getMessage().c_str());
                }
                    break;
                case EventAssetsManagerEx::EventCode::ERROR_DECOMPRESS:
                {
                    CCLOG("%s", event->getMessage().c_str());
                }
                    break;
                default:
                    break;
            }
        });
        Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(_amListener, 1);
        
        _am->update();
        
        Director::getInstance()->replaceScene(this);
    }
}

void AssetsManagerExLoaderScene::onExit()
{
    _eventDispatcher->removeEventListener(_amListener);
    _am->release();
    Scene::onExit();
}
