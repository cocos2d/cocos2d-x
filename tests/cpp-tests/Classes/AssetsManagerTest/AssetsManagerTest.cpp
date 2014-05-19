 #include "AssetsManagerTest.h"
#include "../testResource.h"
#include "cocos2d.h"

std::vector<std::string> sceneId {"AMTestScene1", "AMTestScene2", "AMTestScene3"};
std::vector<std::string> sceneManifests {"Manifests/AMTestScene1/project.manifest", "Manifests/AMTestScene2/project.manifest", "Manifests/AMTestScene3/project.manifest"};
std::vector<std::string> storagePaths {"CppTests/AssetsManagerTest/scene1/", "CppTests/AssetsManagerTest/scene2/", "CppTests/AssetsManagerTest/scene3"};
std::vector<std::string> backgroundPaths {"Images/background1.jpg", "Images/background2.jpg", "background3.png"};

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
    Layer::onEnter();
    _background = Sprite::create(_spritePath);
    addChild(_background, 1);
    _background->setPosition( VisibleRect::center() );
}


static int currentScene = 0;

void AssetsManagerTestScene::runThisTest()
{
    _background = backgroundPaths[currentScene];
    new AssetsManagerLoaderScene(sceneId[currentScene], sceneManifests[currentScene], storagePaths[currentScene], this);
    currentScene++;
}

void AssetsManagerTestScene::onLoad()
{
    auto layer = new AssetsManagerTestLayer(_background);
    addChild(layer);
    layer->release();
    
    Director::getInstance()->replaceScene(this);
}


AssetsManagerLoaderScene::AssetsManagerLoaderScene(std::string managerId, std::string manifestPath, std::string storagePath, AssetsManagerTestScene *scene)
: _scene(scene)
{
    Sprite *sprite = Sprite::create("Images/Icon.png");
    auto layer = new Layer();
    addChild(layer);
    layer->addChild(sprite);
    sprite->setPosition( VisibleRect::center() );
    layer->release();
    
    AAssetsManager *am = AAssetsManager::create(managerId, manifestPath, storagePath);
    
    if (!am->getLocalManifest()->isLoaded())
    {
        CCLOG("Fail to update assets, step skipped.");
        scene->onLoad();
    }
    else
    {
        am->addUpdateEventListener([scene](EventCustom* event){
            AAssetsManager::UpdateEvent *e = (AAssetsManager::UpdateEvent *)event->getUserData();
            switch (e->code)
            {
                case AAssetsManager::ALREADY_UP_TO_DATE:
                case AAssetsManager::FINISHED_UPDATE:
                    scene->onLoad();
                    break;
                case AAssetsManager::FINISHED_WITH_ERROR:
                    CCLOG("Fail to update assets, step skipped.");
                    scene->onLoad();
                    break;
                case AAssetsManager::UPDATING_ERROR:
                    CCLOG("Asset %s : %s", e->assetId.c_str(), e->message.c_str());
                    break;
                default:
                    break;
            }
        });
        
        am->addNoLocalManifestErrorListener([scene](EventCustom* event){
            CCLOG("No local manifest file found, skip assets update.");
            scene->onLoad();
        });
        
        am->addUpdateProgressEventListener([scene](EventCustom* event){
            double *percent = (double *)event->getUserData();
            CCLOG("Update percent : %f", *percent);
        });
        
        am->update();
        
        Director::getInstance()->replaceScene(this);
    }
}