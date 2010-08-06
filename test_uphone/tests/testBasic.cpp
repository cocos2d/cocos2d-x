#include "testBasic.h"

TestLayer::TestLayer()
{
    /**
    @todo 添加用于控制当前所运行测试的菜单
    */
}

TestScene::TestScene()
{
    CCLayer* pLayer = new TestLayer();
    pLayer->autorelease();
    pLayer->retain();

    addChild(pLayer);
}
