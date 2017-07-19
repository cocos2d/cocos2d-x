#include "NetSprite.h"
#include  "network/CCDownloader.h"

USING_NS_CC;

cocos2d::Sprite* NetSprite::create()
{
	auto sp = new (std::nothrow)Sprite();
	if (sp &&sp->init())
	{
		sp->autorelease();
		return sp;
	}
	CC_SAFE_DELETE(sp);
	return nullptr;

}

cocos2d::Sprite* NetSprite::create(const std::string& filename)
{
	auto sp = new (std::nothrow)Sprite();
	if(sp && sp->initWithFile(filename))
	{
		sp->autorelease();
		return sp;
	}
	CC_SAFE_DELETE(sp);
	return nullptr;
}

cocos2d::Sprite* NetSprite::create(const std::string& filename, cocos2d::Rect& rect)
{
	auto sp = new (std::nothrow)Sprite();
	if(sp && sp->initWithFile(filename,rect))
	{
		sp->autorelease();
		return sp;
	}
	CC_SAFE_DELETE(sp);
	return nullptr;
}

cocos2d::Sprite* NetSprite::createWithTexture(cocos2d::Texture2D* texture)
{
	auto sp = new (std::nothrow)Sprite();
	if(sp && sp->initWithTexture(texture))
	{
		sp->autorelease();
		return sp;
	}
	CC_SAFE_DELETE(sp);
	return nullptr;
}

cocos2d::Sprite* NetSprite::createWithTexture(cocos2d::Texture2D* texture, cocos2d::Rect& rect)
{
	auto sp = new (std::nothrow)Sprite();
	if(sp && sp->initWithTexture(texture,rect))
	{
		sp->autorelease();
		return sp;
	}
	CC_SAFE_DELETE(sp);
	return nullptr;
}

cocos2d::Sprite* NetSprite::createWithSpriteFrame(cocos2d::SpriteFrame* spriteFrame)
{
	auto sp = new (std::nothrow)::Sprite();
	if (sp && sp->initWithSpriteFrame(spriteFrame))
	{
		sp->autorelease();
		return sp;
	}
	CC_SAFE_DELETE(sp);
	return nullptr;
}

cocos2d::Sprite* NetSprite::createWithSpriteFrameName(const std::string& spriteFrameName)
{
	auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteFrameName);
	
#ifdef COCOS2D_DEBUG > 0
	char msg[256] = { 0 };
	sprintf(msg, "Invaild SpriteFrameName %s", spriteFrameName);
	CCASSERT(frame != nullptr, msg);
#endif 
	return createWithSpriteFrame(frame);
}

void NetSprite::createWithUrl(const std::string urls, const std::string &name)
{
	auto sp = new (std::nothrow)NetSprite();
	sp->initWithUrl(urls,name);
	sp->autorelease();
}

void NetSprite::initWithUrl(const std::string& url, const std::string &name)
{
	auto downloader = new (std::nothrow)network::Downloader();
	
	downloader->createDownloadDataTask(url, name);
	downloader->onTaskProgress = [this](const network::DownloadTask &task, int64_t r, int64_t t, int64_t e)
	{
		float p = float(t * 100) / e;

		char buff[256] = { 0 };

		sprintf(buff, "%1.f%%[total %d KB] Speed %d KB",p,e / 1024, r / 1024);

		CCLOG(buff);
	};

	downloader->onDataTaskSuccess = [this](const network::DownloadTask &task, std::vector<unsigned char>&data)
	{
		Texture2D * texture;
		do
		{
			Image img;
			if (false == img.initWithImageData(data.data(), data.size()))
			{
				CCLOG("data error");
				break;
			}
			texture = new Texture2D();
			if (false == texture->initWithImage(&img))
			{
				CCLOG("image error");
				break;
			}

			auto sprite = createWithTexture(texture);
			auto scene = Director::getInstance()->getRunningScene();

			auto size = scene->getContentSize();
			sprite->setAnchorPoint(Vec2(0.5, 0.5));
			sprite->setPosition(size.width / 2, size.height / 2);
			CCLOG(scene->getName().c_str());
			scene->addChild(sprite, 2);

		} while (0);

	};

	downloader->onTaskError = [this](const cocos2d::network::DownloadTask& task,int errorCode,int errorCodeInternal,const std::string& errorStr)
	{
		CCLOG("Failed to download : %s, identifier(%s) error code(%d), internal error code(%d) desc(%s)"
			, task.requestURL.c_str()
			, task.identifier.c_str()
			, errorCode
			, errorCodeInternal
			, errorStr.c_str());
	};
}
