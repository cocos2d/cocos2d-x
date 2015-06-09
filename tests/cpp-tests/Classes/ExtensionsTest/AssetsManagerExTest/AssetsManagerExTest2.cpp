#include "AssetsManagerExTest2.h"
#include "cocos2d.h"

USING_NS_CC;

AssetsManagerExTest2 * AssetsManagerExTest2::_single_instance = nullptr;
const char * AssetsManagerExTest2::EVENT_PROGRESS = "_ame2_event_progress";
const char * AssetsManagerExTest2::EVENT_FINISHED = "_ame2_event_finished";

AssetsManagerExTest2::AssetsManagerExTest2()
:_am(nullptr)
,_amListener(nullptr)
{
}
AssetsManagerExTest2::~AssetsManagerExTest2()
{
	CC_SAFE_RELEASE_NULL(_am);	
	_eventDispatcher->removeEventListener(_amListener);
	CC_SAFE_RELEASE_NULL(_amListener);
}

AssetsManagerExTest2 * AssetsManagerExTest2::getInstance()
{
	if (_single_instance == nullptr)
	{
		_single_instance = new (std::nothrow) AssetsManagerExTest2;
	}
	return _single_instance;
}

void AssetsManagerExTest2::destoryInstance()
{
	if (_single_instance != nullptr)
	{
		delete _single_instance;
		_single_instance = nullptr;
	}
	return;
}

void AssetsManagerExTest2::doAssetsUpdate(std::string manifestPath)
{
	std::string storagePath = cocos2d::FileUtils::getInstance()->getWritablePath();
	CCLOG("storage path = %s", storagePath.c_str());

	if (_am!=nullptr) {
		CC_SAFE_RELEASE_NULL(_am);
	}
	_am = AssetsManagerEx::create(manifestPath, storagePath);
	_am->retain();

	if (!_am->getLocalManifest()->isLoaded())
	{
		CCLOG("Fail to update assets, step skipped.");
	}
	else
	{
		_amListener = cocos2d::extension::EventListenerAssetsManagerEx::create(_am, [this](EventAssetsManagerEx* event){
		static int failCount = 0;
		switch (event->getEventCode())
		{
				case EventAssetsManagerEx::EventCode::ERROR_NO_LOCAL_MANIFEST:
					{
						CCLOG("No local manifest file found, skip assets update.");
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
							auto event = EventCustom(AssetsManagerExTest2::EVENT_PROGRESS);
							auto data = Value(percent);
							event.setUserData(&data);
							Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
						}

					}
					break;
				case EventAssetsManagerEx::EventCode::ERROR_DOWNLOAD_MANIFEST:
				case EventAssetsManagerEx::EventCode::ERROR_PARSE_MANIFEST:
					{
						CCLOG("Fail to download manifest file, update skipped.");

					}
					break;
				case EventAssetsManagerEx::EventCode::ALREADY_UP_TO_DATE:
				case EventAssetsManagerEx::EventCode::UPDATE_FINISHED:
					{
						CCLOG("Update finished. %s", event->getMessage().c_str());
						CC_SAFE_RELEASE_NULL(_am);
						Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(AssetsManagerExTest2::EVENT_FINISHED);
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