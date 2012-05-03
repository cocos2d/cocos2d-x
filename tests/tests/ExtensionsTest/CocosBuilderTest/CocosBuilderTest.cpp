#include "CocosBuilderTest.h"
#include "../../testResource.h"
#include "CCBReader.h"

void CocosBuilderTestScene::runThisTest()
{
    CCNode* node = CCBReader::nodeGraphFromFile("example.ccb") ;
	this->addChild(node) ;
    
    CCDirector::sharedDirector()->replaceScene(this);
}