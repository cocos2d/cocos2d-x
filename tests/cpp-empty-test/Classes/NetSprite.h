#pragma once
#include "cocos2d.h"

class NetSprite :
	public cocos2d::Sprite
{
public:
	static cocos2d::Sprite* create();
	static cocos2d::Sprite* create(const std::string &filename);
	static cocos2d::Sprite* create(const std::string &filename, cocos2d::Rect &rect);

	static cocos2d::Sprite* createWithTexture(cocos2d::Texture2D *texture);
	static cocos2d::Sprite* createWithTexture(cocos2d::Texture2D *texture, cocos2d::Rect &rect);
	static cocos2d::Sprite* createWithSpriteFrame(cocos2d::SpriteFrame *spriteFrame);
	static cocos2d::Sprite* createWithSpriteFrameName(const std::string& spriteFrameName);
	virtual void initWithUrl(const std::string& cs, const std::string &name);
	static void createWithUrl(const std::string url,const std::string &name);

	
};

