#include "AssetsManagerExTest.h"
#include "../../testResource.h"
#include "cocos2d.h"

USING_NS_CC;
USING_NS_CC_EXT;

const char* sceneManifests[] = {"AMTestScene1/project.manifest", "AMTestScene2/project.manifest", "AMTestScene3/project.manifest"};
const char* storagePaths[] = {"CppTests/AssetsManagerExTest/scene1/", "CppTests/AssetsManagerExTest/scene2/", "CppTests/AssetsManagerExTest/scene3"};
const char* backgroundPaths[] = {"Images/assetMgrBackground1.jpg", "Images/assetMgrBackground2.png", "Images/assetMgrBackground3.png"};

AssetsManagerExTests::AssetsManagerExTests()
{
    addTestCase("AssetsManager Test1", [](){ return AssetsManagerExLoaderScene::create(0); });
    addTestCase("AssetsManager Test2", [](){ return AssetsManagerExLoaderScene::create(1); });
    addTestCase("AssetsManager Test3", [](){ return AssetsManagerExLoaderScene::create(2); });
}

AssetsManagerExLoaderScene* AssetsManagerExLoaderScene::create(int testIndex)
{
    auto scene = new (std::nothrow) AssetsManagerExLoaderScene(testIndex);
    if (scene && scene->init())
    {
        scene->autorelease();
    }
    else
    {
        delete scene;
        scene = nullptr;
    }

    return scene;
}

AssetsManagerExLoaderScene::AssetsManagerExLoaderScene(int testIndex)
: _testIndex(testIndex)
, _loadLayer(nullptr)
, _downloadMenu(nullptr)
, _am(nullptr)
, _progress(nullptr)
, _amListener(nullptr)
{

}

bool AssetsManagerExLoaderScene::init()
{
    if (!TestCase::init())
    {
        return false;
    }

    auto downloadLabel = Label::createWithTTF("Start Download", "fonts/arial.ttf", 16);
    auto downloadItem = MenuItemLabel::create(downloadLabel, CC_CALLBACK_1(AssetsManagerExLoaderScene::startDownloadCallback, this));
    downloadItem->setPosition(Vec2(VisibleRect::center().x, VisibleRect::bottom().y + 100));
    _downloadMenu = Menu::create(downloadItem, nullptr);
    _downloadMenu->setPosition(Vec2::ZERO);
    this->addChild(_downloadMenu, 1);

    _loadLayer = Layer::create();
    addChild(_loadLayer);

    auto sprite = Sprite::create("Images/Icon.png");
    _loadLayer->addChild(sprite);
    sprite->setPosition( VisibleRect::center() );
    
    TTFConfig config("fonts/tahoma.ttf", 30);
    _progress = Label::createWithTTF(config, "0%", TextHAlignment::CENTER);
    _progress->setPosition( Vec2(VisibleRect::center().x, VisibleRect::center().y + 50) );
    _loadLayer->addChild(_progress);
    
    std::string manifestPath = sceneManifests[_testIndex], storagePath = FileUtils::getInstance()->getWritablePath() + storagePaths[_testIndex];
    CCLOG("Storage path for this test : %s", storagePath.c_str());
    _am = AssetsManagerEx::create(manifestPath, storagePath);
    _am->retain();

    return true;
}

void AssetsManagerExLoaderScene::onLoadEnd()
{
    removeChild(_loadLayer, true);
    _loadLayer = nullptr;

    auto backgroundSprite = Sprite::create(backgroundPaths[_testIndex]);
    addChild(backgroundSprite, 1);
    backgroundSprite->setPosition(VisibleRect::center());
}

void AssetsManagerExLoaderScene::startDownloadCallback(Ref* sender)
{
    removeChild(_downloadMenu);
    _downloadMenu = nullptr;

    if (!_am->getLocalManifest()->isLoaded())
    {
        CCLOG("Fail to update assets, step skipped.");
        onLoadEnd();
    }
    else
    {
        int testIndex = _testIndex;
        _amListener = cocos2d::extension::EventListenerAssetsManagerEx::create(_am, [testIndex, this](EventAssetsManagerEx* event){
            static int failCount = 0;
            switch (event->getEventCode())
            {
            case EventAssetsManagerEx::EventCode::ERROR_NO_LOCAL_MANIFEST:
            {
                CCLOG("No local manifest file found, skip assets update.");
                this->onLoadEnd();
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
                this->onLoadEnd();
            }
            break;
            case EventAssetsManagerEx::EventCode::ALREADY_UP_TO_DATE:
            case EventAssetsManagerEx::EventCode::UPDATE_FINISHED:
            {
                CCLOG("Update finished. %s", event->getMessage().c_str());
                this->onLoadEnd();
            }
            break;
            case EventAssetsManagerEx::EventCode::UPDATE_FAILED:
            {
                CCLOG("Update failed. %s", event->getMessage().c_str());

                failCount++;
                if (failCount < 5)
                {
                    _am->downloadFailedAssets();
                }
                else
                {
                    CCLOG("Reach maximum fail count, exit update process");
                    failCount = 0;
                    this->onLoadEnd();
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
    }
}

void AssetsManagerExLoaderScene::onExit()
{
    _eventDispatcher->removeEventListener(_amListener);
    _am->release();
    TestCase::onExit();
}

std::string AssetsManagerExLoaderScene::title() const
{
    return "AssetsManagerExTest";
}
