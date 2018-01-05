#include "Bug-18609.h"
#include <base/ZipUtils.h>

Bug18609Layer::Bug18609Layer() {
  auto size = Director::getInstance()->getWinSize();
  ZipUtils::setPvrEncryptionKeyPart(0, 0xfc5cc0ed);
  ZipUtils::setPvrEncryptionKeyPart(1, 0x15b97c42);
  ZipUtils::setPvrEncryptionKeyPart(2, 0x51ce7d9e);
  ZipUtils::setPvrEncryptionKeyPart(3, 0x3e26102b);
  SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/bugs/18609.plist","Images/bugs/18609.pvr.ccz");
  SpriteFrame *spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName("grossini.png");
  // auto img = Sprite::create();
  auto img = ui::Button::create();
  img->setTag(2);
  // img->initWithFile("Images/grossini.png");
  img->loadTextureNormal("bt_blank_green.png",
                        ui::Widget::TextureResType::PLIST);
  img->setPosition(Vec2(size.width / 3, size.height / 2));
  this->addChild(img);

  img = ui::Button::create();
  // img->initWithFile("Images/grossini.png");
  img->loadTextureNormal("ico_bg_notif.png",
                        ui::Widget::TextureResType::PLIST);
  img->setPosition(Vec2(2*size.width / 3, size.height / 2));
  this->addChild(img);



  ui::Button *bt = ui::Button::create();
  bt->loadTextureNormal("Images/btn-play-normal.png",
                        ui::Widget::TextureResType::LOCAL);
  this->addChild(bt);
  bt->setAnchorPoint(Vec2(1, 0.5));
  bt->setPosition(Vec2(size.width - 20, size.height / 2));
  bt->addTouchEventListener(CC_CALLBACK_2(Bug18609Layer::testCallback, this));
}

std::string Bug18609Layer::title() const {
  // return "Issue 18609 CCSprite::initWithSpriteFrameName";
  return "";
}

std::string Bug18609Layer::subtitle() const
{
  return "When you call to initWithSpriteFrameName() 2nd time, sprite will have error in "
         "rendering. The Left button should be like the Right button when you press Play";
}

void Bug18609Layer::testCallback(Ref* sender, ui::Widget::TouchEventType type)
{
  if (type == ui::Widget::TouchEventType::ENDED) {
    // Sprite *spr = dynamic_cast<Sprite *>(getChildByTag(2));
    auto spr = dynamic_cast<ui::Button *>(getChildByTag(2));
    // spr->initWithSpriteFrame(spriteFrame);
    spr->loadTextureNormal("ico_bg_notif.png",
                            ui::Widget::TextureResType::PLIST);
  }
}
