#include "cocos2d.h"
#include "AssetsManagerExTest2.h"
#include "AssetsManagerExTest2LoaderScene.h"
#include "../../testResource.h"

USING_NS_CC;
USING_NS_CC_EXT;

AssetsManagerExTestSimple::AssetsManagerExTestSimple()
{
	addTestCase("AssetsManagerEx simple", [](){ return AssetsManagerExTest2LoaderScene::create(); });
}

AssetsManagerExTest2LoaderScene::AssetsManagerExTest2LoaderScene()
	:_downloadMenu_Yes(nullptr)
	,_downloadMenu_No(nullptr)
	,_progress(nullptr)
{

}

AssetsManagerExTest2LoaderScene::~AssetsManagerExTest2LoaderScene()
{
	getEventDispatcher()->removeCustomEventListeners(AssetsManagerExTest2::EVENT_PROGRESS);
	getEventDispatcher()->removeCustomEventListeners(AssetsManagerExTest2::EVENT_FINISHED);
}

AssetsManagerExTest2LoaderScene* AssetsManagerExTest2LoaderScene::create()
{
    auto scene = new (std::nothrow) AssetsManagerExTest2LoaderScene();
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


bool AssetsManagerExTest2LoaderScene::init()
{
    if (!TestCase::init())
    {
        return false;
    }

    auto downloadLabelYes = Label::createWithTTF("Start Download", "fonts/arial.ttf", 16);
    auto downloadItemYes = MenuItemLabel::create(downloadLabelYes, CC_CALLBACK_1(AssetsManagerExTest2LoaderScene::startDownloadYesCallback, this));
    downloadItemYes->setPosition(Vec2(VisibleRect::center().x, VisibleRect::top().y - 80));
    auto _downloadMenuYes = Menu::create(downloadItemYes, nullptr);
    _downloadMenuYes->setPosition(Vec2::ZERO);
    this->addChild(_downloadMenuYes, 1);
	
    auto downloadLabelNo = Label::createWithTTF("Don't Download", "fonts/arial.ttf", 16);
    auto downloadItemNo = MenuItemLabel::create(downloadLabelNo, CC_CALLBACK_1(AssetsManagerExTest2LoaderScene::startDownloadNoCallback, this));
    downloadItemNo->setPosition(Vec2(VisibleRect::center().x, VisibleRect::top().y - 200));
    auto _downloadMenuNo = Menu::create(downloadItemNo, nullptr);
    _downloadMenuNo->setPosition(Vec2::ZERO);
    this->addChild(_downloadMenuNo, 1);	

    _loadLayer = Layer::create();
    addChild(_loadLayer);

    auto sprite = Sprite::create("Images/Icon.png");
    _loadLayer->addChild(sprite);
    sprite->setPosition( VisibleRect::center() );
    
    TTFConfig config("fonts/tahoma.ttf", 30);
    _progress = Label::createWithTTF(config, "0%", TextHAlignment::CENTER);
    _progress->setPosition( Vec2(VisibleRect::center().x, VisibleRect::center().y + 50) );
    _loadLayer->addChild(_progress);

    return true;
}

void AssetsManagerExTest2LoaderScene::onLoadEnd()
{
    removeChild(_loadLayer, true);
    _loadLayer = nullptr;

    auto backgroundSprite = Sprite::create("Images/assetMgrBackground1.jpg");
    addChild(backgroundSprite, 1);
    backgroundSprite->setPosition(VisibleRect::center());
}

void AssetsManagerExTest2LoaderScene::startDownloadYesCallback(Ref* sender)
{
	removeChild(_downloadMenu_Yes);
	_downloadMenu_Yes = nullptr;

	removeChild(_downloadMenu_No);
	_downloadMenu_No = nullptr;

	//// label of progress
	//auto size = Director::getInstance()->getWinSize();
	//TTFConfig config("fonts/arial.ttf", 30);
	//_progress = Label::createWithTTF(config, "0%", TextHAlignment::CENTER);
	//_progress->setPosition( Vec2(VisibleRect::center().x, VisibleRect::bottom().y + 100) );
	//this->addChild(_progress);

	// progress event
	getEventDispatcher()->addCustomEventListener(	AssetsManagerExTest2::EVENT_PROGRESS
													,[this](EventCustom* event)
													{
														auto data = (Value*)event->getUserData();
														float percent = data->asFloat();
														std::string str = StringUtils::format("%.2f", percent) + "%";
														CCLOG("%.2f Percent", percent);
														if (this->_progress != nullptr) 
														{
															this->_progress->setString(str);
														}
													}
												);
	// finished event
	getEventDispatcher()->addCustomEventListener(	AssetsManagerExTest2::EVENT_FINISHED
													,[this](EventCustom* event)
													{
														// clear cache
														Director::getInstance()->getTextureCache()->removeAllTextures();
														// next scene [your code here]
														auto scene = AssetsManagerExTest2LoaderScene::create();
														Director::getInstance()->replaceScene(scene);
													}
												);
	// update resources
	AssetsManagerExTest2::getInstance()->doAssetsUpdate("AMTestScene1/project.manifest");
	//AssetsManagerExTest2::getInstance()->doAssetsUpdate("Manifests/local.manifest");
}


void AssetsManagerExTest2LoaderScene::startDownloadNoCallback(Ref* sender)
{
	removeChild(_downloadMenu_Yes);
	_downloadMenu_Yes = nullptr;

	removeChild(_downloadMenu_No);
	_downloadMenu_No = nullptr;

	// next scene [your code here]
	auto scene = AssetsManagerExTest2LoaderScene::create();
	Director::getInstance()->replaceScene(scene);

}

void AssetsManagerExTest2LoaderScene::onExit()
{

    TestCase::onExit();
}

std::string AssetsManagerExTest2LoaderScene::title() const
{
    return "AssetsManagerExTest2";
}
