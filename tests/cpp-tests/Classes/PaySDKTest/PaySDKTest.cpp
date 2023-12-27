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
#include "PaySDKTest.h"
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

PaySDKTests::PaySDKTests() { ADD_TEST_CASE(PaySDKControlTest); }

PaySDKControlTest::PaySDKControlTest() {
  auto label = Label::createWithTTF("Pay SDK Test", "fonts/arial.ttf", 28);
  addChild(label, 0);
  label->setPosition(VisibleRect::center().x, VisibleRect::top().y - 50);

    //检查支付环境
  auto sdkItem = TextButton::create("Checking the Payment Environment", [&](TextButton *button) {
    cocos2d::SDKApplication::checkPayEnv();
  });
  sdkItem->setPosition(VisibleRect::center().x, VisibleRect::top().y - 150);
  addChild(sdkItem);
    
    //查询消耗商品
  auto sdkItem1 = TextButton::create("Querying Consumable Products", [&](TextButton *button) {
    cocos2d::SDKApplication::queryConsumProdts();
  });
  sdkItem1->setPosition(VisibleRect::center().x, VisibleRect::top().y - 200);
  addChild(sdkItem1);
    
    //购买
  auto sdkItem2 = TextButton::create("Buying", [&](TextButton *button) {
    cocos2d::SDKApplication::buy();
  });
  sdkItem2->setPosition(VisibleRect::center().x, VisibleRect::top().y - 250);
  addChild(sdkItem2);

    //消耗
  auto sdkItem3 = TextButton::create("Consumes", [&](TextButton *button) {
    cocos2d::SDKApplication::consume();
  });
  sdkItem3->setPosition(VisibleRect::center().x, VisibleRect::top().y - 300);
  addChild(sdkItem3);

    //查询非消耗型商品
  auto sdkItem4 = TextButton::create("Query non-consumable goods", [&](TextButton *button) {
    cocos2d::SDKApplication::queryNoConsumableGoods();
  });
  sdkItem4->setPosition(VisibleRect::center().x, VisibleRect::top().y - 350);
  addChild(sdkItem4);

    //非消耗型商品购买
  auto sdkItem5 = TextButton::create("Purchase of non-consumable goods", [&](TextButton *button) {
    cocos2d::SDKApplication::purchaseOfNonConsumableGoods();
  });
  sdkItem5->setPosition(VisibleRect::center().x, VisibleRect::top().y - 400);
  addChild(sdkItem5);

    //消耗型商品掉单查询
  auto sdkItem6 = TextButton::create("Disposable goods order query", [&](TextButton *button) {
    cocos2d::SDKApplication::disposableGoodsOrderQuery();
  });
  sdkItem6->setPosition(VisibleRect::center().x, VisibleRect::top().y - 450);
  addChild(sdkItem6);

    //查询非消耗型商品的购买记录
  auto sdkItem7 = TextButton::create("Querying Purchase Records of Non-consumable Products", [&](TextButton *button) {
    cocos2d::SDKApplication::nonConsumableProductsRecords();
  });
  sdkItem7->setPosition(VisibleRect::center().x, VisibleRect::top().y - 500);
  addChild(sdkItem7);

    //查询消耗型商品的购买记录
  auto sdkItem8 = TextButton::create("Querying Purchase Records of Consumable Products", [&](TextButton *button) {
    cocos2d::SDKApplication::consumableProductsRecords();
  });
  sdkItem8->setPosition(VisibleRect::center().x, VisibleRect::top().y - 550);
  addChild(sdkItem8);
    
  auto getResult = TextButton::create("Get Result", [&](TextButton *button) {
    auto result = Label::createWithTTF("", "fonts/arial.ttf", 20);
    result->setPosition(VisibleRect::center().x, VisibleRect::top().y - 650);
    std::string sdkResult = "";
    sdkResult = cocos2d::SDKApplication::getPaySDKResult();
    result->setString(sdkResult);
    addChild(result);
  });
  getResult->setPosition(VisibleRect::center().x, VisibleRect::top().y - 610);
  addChild(getResult);
}