#include "AssetsManagerTest.h"
#include "../../testResource.h"
#include "cocos2d.h"
#include "extensions/assets-manager/CCEventAssetsManager.h"
#include "extensions/assets-manager/CCEventListenerAssetsManager.h"

const char* sceneManifests[] = {"AMTestScene1/project.manifest", "AMTestScene2/project.manifest", "AMTestScene3/project.manifest"};
const char* storagePaths[] = {"CppTests/AssetsManagerTest/scene1/", "CppTests/AssetsManagerTest/scene2/", "CppTests/AssetsManagerTest/scene3"};
const char* backgroundPaths[] = {"Images/background1.jpg", "Images/background2.jpg", "Images/background3.png"};

AssetsManagerTestLayer::AssetsManagerTestLayer(const std::string& spritePath)
: _spritePath(spritePath)
{
}

AssetsManagerTestLayer::~AssetsManagerTestLayer(void)
{
}

std::string AssetsManagerTestLayer::title() const
{
    return "AssetsManagerTest";
}

void AssetsManagerTestLayer::onEnter()
{
    BaseTest::onEnter();
    _background = Sprite::create(_spritePath);
    if (_background)
    {
        addChild(_background, 1);
        _background->setPosition( VisibleRect::center() );
    }
}

void AssetsManagerTestLayer::restartCallback(Ref* sender)
{
}

void AssetsManagerTestLayer::nextCallback(Ref* sender)
{
    if (AssetsManagerLoaderScene::currentScene < 2)
    {
        AssetsManagerLoaderScene::currentScene++;
    }
    else
    {
        AssetsManagerLoaderScene::currentScene = 0;
    }
    auto scene = new AssetsManagerLoaderScene();
    scene->runThisTest();
    scene->release();
}

void AssetsManagerTestLayer::backCallback(Ref* sender)
{
    if (AssetsManagerLoaderScene::currentScene > 0)
    {
        AssetsManagerLoaderScene::currentScene--;
    }
    else AssetsManagerLoaderScene::currentScene = 2;
    auto scene = new AssetsManagerLoaderScene();
    scene->runThisTest();
    scene->release();
}


AssetsManagerTestScene::AssetsManagerTestScene(std::string background)
{
    auto layer = new AssetsManagerTestLayer(background);
    addChild(layer);
    layer->release();
}

void AssetsManagerTestScene::runThisTest()
{
}

int AssetsManagerLoaderScene::currentScene = 0;
AssetsManagerLoaderScene::AssetsManagerLoaderScene()
: _progress(nullptr)
, _amListener(nullptr)
{
}

void AssetsManagerLoaderScene::runThisTest()
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
    
    _am = AssetsManager::create(manifestPath, storagePath);
    _am->retain();
    
    if (!_am->getLocalManifest()->isLoaded())
    {
        CCLOG("Fail to update assets, step skipped.");
        AssetsManagerTestScene *scene = new AssetsManagerTestScene(backgroundPaths[currentId]);
        Director::getInstance()->replaceScene(scene);
        scene->release();
    }
    else
    {
        _amListener = cocos2d::extension::EventListenerAssetsManager::create(_am, [currentId, this](EventAssetsManager* event){
            static int failCount = 0;
            AssetsManagerTestScene *scene;
            switch (event->getEventCode())
            {
                case EventAssetsManager::EventCode::ERROR_NO_LOCAL_MANIFEST:
                {
                    CCLOG("No local manifest file found, skip assets update.");
                    scene = new AssetsManagerTestScene(backgroundPaths[currentId]);
                    Director::getInstance()->replaceScene(scene);
                    scene->release();
                }
                    break;
                case EventAssetsManager::EventCode::UPDATE_PROGRESSION:
                {
                    std::string assetId = event->getAssetId();
                    float percent = event->getPercent();
                    std::string str;
                    if (assetId == AssetsManager::VERSION_ID)
                    {
                        str = StringUtils::format("Version file: %.2f", percent) + "%";
                    }
                    else if (assetId == AssetsManager::MANIFEST_ID)
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
                case EventAssetsManager::EventCode::ERROR_DOWNLOAD_MANIFEST:
                case EventAssetsManager::EventCode::ERROR_PARSE_MANIFEST:
                {
                    CCLOG("Fail to download manifest file, update skipped.");
                    scene = new AssetsManagerTestScene(backgroundPaths[currentId]);
                    Director::getInstance()->replaceScene(scene);
                    scene->release();
                }
                    break;
                case EventAssetsManager::EventCode::ALREADY_UP_TO_DATE:
                case EventAssetsManager::EventCode::UPDATE_FINISHED:
                {
                    CCLOG("Update finished. %s", event->getMessage().c_str());
                    scene = new AssetsManagerTestScene(backgroundPaths[currentId]);
                    Director::getInstance()->replaceScene(scene);
                    scene->release();
                }
                    break;
                case EventAssetsManager::EventCode::UPDATE_FAILED:
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
                        scene = new AssetsManagerTestScene(backgroundPaths[currentId]);
                        Director::getInstance()->replaceScene(scene);
                        scene->release();
                    }
                }
                    break;
                case EventAssetsManager::EventCode::ERROR_UPDATING:
                {
                    CCLOG("Asset %s : %s", event->getAssetId().c_str(), event->getMessage().c_str());
                }
                    break;
                case EventAssetsManager::EventCode::ERROR_DECOMPRESS:
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

void AssetsManagerLoaderScene::onExit()
{
    _eventDispatcher->removeEventListener(_amListener);
    _am->release();
    Scene::onExit();
}
