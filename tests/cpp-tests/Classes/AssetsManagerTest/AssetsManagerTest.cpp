 #include "AssetsManagerTest.h"
#include "../testResource.h"
#include "cocos2d.h"

std::vector<std::string> sceneId {"AMTestScene1", "AMTestScene2", "AMTestScene3"};
std::vector<std::string> sceneManifests {"Manifests/AMTestScene1/project.manifest", "Manifests/AMTestScene2/project.manifest", "Manifests/AMTestScene3/project.manifest"};
std::vector<std::string> storagePaths {"CppTests/AssetsManagerTest/scene1/", "CppTests/AssetsManagerTest/scene2/", "CppTests/AssetsManagerTest/scene3"};
std::vector<std::string> backgroundPaths {"Images/background1.jpg", "Images/background2.jpg", "Images/background3.png"};

AssetsManagerTestLayer::AssetsManagerTestLayer(std::string spritePath)
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
    addChild(_background, 1);
    _background->setPosition( VisibleRect::center() );
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
    else AssetsManagerLoaderScene::currentScene = 0;
    auto scene = new AssetsManagerLoaderScene();
    scene->runThisTest();
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
{
}

void AssetsManagerLoaderScene::runThisTest()
{
    int currentId = currentScene;
    std::string managerId = sceneId[currentId], manifestPath = sceneManifests[currentId], storagePath = storagePaths[currentId];
    
    Sprite *sprite = Sprite::create("Images/Icon.png");
    auto layer = new Layer();
    addChild(layer);
    layer->addChild(sprite);
    sprite->setPosition( VisibleRect::center() );
    layer->release();
    
    _am = AAssetsManager::create(managerId, manifestPath, storagePath);
    _am->retain();
    
    if (!_am->getLocalManifest()->isLoaded())
    {
        CCLOG("Fail to update assets, step skipped.");
        AssetsManagerTestScene *scene = new AssetsManagerTestScene(backgroundPaths[currentId]);
        Director::getInstance()->replaceScene(scene);
    }
    else
    {
        _am->addUpdateEventListener([currentId](EventCustom* event){
            AAssetsManager::UpdateEvent *e = (AAssetsManager::UpdateEvent *)event->getUserData();
            AssetsManagerTestScene *scene;
            switch (e->code)
            {
                case AAssetsManager::FAIL_DOWNLOAD_MANIFEST:
                case AAssetsManager::FAIL_PARSE_MANIFEST:
                    CCLOG("Fail to download manifest file, update skipped.");
                    scene = new AssetsManagerTestScene(backgroundPaths[currentId]);
                    Director::getInstance()->replaceScene(scene);
                    break;
                case AAssetsManager::ALREADY_UP_TO_DATE:
                case AAssetsManager::FINISHED_UPDATE:
                    CCLOG("Update succeeded.");
                    scene = new AssetsManagerTestScene(backgroundPaths[currentId]);
                    Director::getInstance()->replaceScene(scene);
                    break;
                case AAssetsManager::FINISHED_WITH_ERROR:
                    CCLOG("Fail to update assets, update skipped.");
                    scene = new AssetsManagerTestScene(backgroundPaths[currentId]);
                    Director::getInstance()->replaceScene(scene);
                    break;
                case AAssetsManager::UPDATING_ERROR:
                    CCLOG("Asset %s : %s.", e->assetId.c_str(), e->message.c_str());
                    scene = new AssetsManagerTestScene(backgroundPaths[currentId]);
                    Director::getInstance()->replaceScene(scene);
                    break;
                default:
                    break;
            }
        });
        
        _am->addNoLocalManifestErrorListener([currentId](EventCustom* event){
            CCLOG("No local manifest file found, skip assets update.");
            AssetsManagerTestScene *scene = new AssetsManagerTestScene(backgroundPaths[currentId]);
            Director::getInstance()->replaceScene(scene);
        });
        
        _am->addUpdateProgressEventListener([](EventCustom* event){
            double *percent = (double *)event->getUserData();
            CCLOG("Update percent : %f", *percent);
        });
        
        _am->update();
        
        Director::getInstance()->replaceScene(this);
    }
}

void AssetsManagerLoaderScene::onExit()
{
    _am->release();
    Scene::onExit();
}