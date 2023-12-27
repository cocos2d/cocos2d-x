/****************************************************************************
 Copyright (c) 2014-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/
#include "SDKTest.h"
#include "CCSDKApplication.h"
USING_NS_CC;

namespace {
class TextButton : public cocos2d::Label {
public:
  static TextButton *
  create(const std::string &text,
         const std::function<void(TextButton *)> &onTriggered) {
    auto ret = new (std::nothrow) TextButton();

    TTFConfig ttfconfig("fonts/arial.ttf", 25);
    if (ret && ret->setTTFConfig(ttfconfig)) {
      ret->setString(text);
      ret->_onTriggered = onTriggered;

      ret->autorelease();

      return ret;
    }

    delete ret;
    return nullptr;
  }

  void setEnabled(bool enabled) {
    _enabled = enabled;
    if (_enabled) {
      this->setColor(Color3B::WHITE);
    } else {
      this->setColor(Color3B::GRAY);
    }
  }

private:
  TextButton() : _enabled(true), _onTriggered(nullptr) {
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);

    listener->onTouchBegan = CC_CALLBACK_2(TextButton::onTouchBegan, this);
    listener->onTouchEnded = CC_CALLBACK_2(TextButton::onTouchEnded, this);
    listener->onTouchCancelled =
        CC_CALLBACK_2(TextButton::onTouchCancelled, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
  }

  bool touchHits(Touch *touch) {
    auto hitPos = this->convertToNodeSpace(touch->getLocation());
    if (hitPos.x >= 0 && hitPos.y >= 0 && hitPos.x <= _contentSize.width &&
        hitPos.y <= _contentSize.height) {
      return true;
    }
    return false;
  }

  bool onTouchBegan(Touch *touch, Event *event) {
    auto hits = touchHits(touch);
    if (hits) {
      scaleButtonTo(0.95f);
    }
    return hits;
  }

  void onTouchEnded(Touch *touch, Event *event) {
    if (_enabled) {
      auto hits = touchHits(touch);
      if (hits && _onTriggered) {
        _onTriggered(this);
      }
    }

    scaleButtonTo(1);
  }

  void onTouchCancelled(Touch *touch, Event *event) { scaleButtonTo(1); }

  void scaleButtonTo(float scale) {
    auto action = ScaleTo::create(0.05f, scale);
    action->setTag(10000);
    stopActionByTag(10000);
    runAction(action);
  }

  std::function<void(TextButton *)> _onTriggered;

  bool _enabled;
};
} // namespace

SDKTests::SDKTests() { ADD_TEST_CASE(SDKControlTest); }

SDKControlTest::SDKControlTest() {
  auto label = Label::createWithTTF("SDK Test", "fonts/arial.ttf", 28);
  addChild(label, 0);
  label->setPosition(VisibleRect::center().x, VisibleRect::top().y - 50);



  auto sdkItem = TextButton::create("Login Init", [&](TextButton *button) {
    cocos2d::SDKApplication::loginInit();
  });
  sdkItem->setPosition(VisibleRect::center().x, VisibleRect::top().y - 150);
  addChild(sdkItem);
    
  auto sdkItem1 = TextButton::create("Login Authorization", [&](TextButton *button) {
    cocos2d::SDKApplication::authorization();
  });
  sdkItem1->setPosition(VisibleRect::center().x, VisibleRect::top().y - 200);
  addChild(sdkItem1);

  auto sdkItem2 = TextButton::create("Get Player Info", [&](TextButton *button) {
    cocos2d::SDKApplication::getPlayerInfo();
  });
  sdkItem2->setPosition(VisibleRect::center().x, VisibleRect::top().y - 250);
  addChild(sdkItem2);

  auto sdkItem3 = TextButton::create("Report Player Info", [&](TextButton *button) {
    cocos2d::SDKApplication::reportPlayerInfo();
  });
  sdkItem3->setPosition(VisibleRect::center().x, VisibleRect::top().y - 300);
  addChild(sdkItem3);
    
    
  auto getResult = TextButton::create("Get Result", [&](TextButton *button) {
    auto result = Label::createWithTTF("", "fonts/arial.ttf", 20);
    result->setPosition(VisibleRect::center().x, VisibleRect::top().y - 400);
    std::string sdkResult = "";
    sdkResult = cocos2d::SDKApplication::getLginSDKResult();
    result->setString(sdkResult);
    addChild(result);
  });

  getResult->setPosition(VisibleRect::center().x, VisibleRect::top().y - 350);
  addChild(getResult);
}