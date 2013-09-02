

#include "CCBParseScene.h"

CCBParseScene::CCBParseScene()
{
    
}

CCBParseScene::~CCBParseScene()
{
    
}

void CCBParseScene::onEnter()
{
    CCScene::onEnter();
}

void CCBParseScene::onExit()
{
    m_pUILayer->removeFromParent();
    
    CCJsonReader::purgeJsonReader();
    UIHelper::purgeUIHelper();
    
    CCScene::onExit();
}

void CCBParseScene::runThisTest()
{
    CCDirector::sharedDirector()->replaceScene(this);
}