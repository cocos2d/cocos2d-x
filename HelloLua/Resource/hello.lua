lastMouseX = 0;
lastMouseY = 0;



g_Scene = cocos2d.CCScene:node();
pSprite = cocos2d.CCSprite:spriteWithFile("90001.jpg");
pSprite:setPosition(cocos2d.CCPoint(300, 400));

pLayer = cocos2d.CCLayer:node();
pLayer:setIsTouchEnabled(true);
pLayer:setAnchorPoint(cocos2d.CCPoint(0,0));
pLayer:setPosition( cocos2d.CCPoint(0, -300) );
pLayer:addChild(pSprite);
g_Scene:addChild(pLayer);


cocos2d.CCDirector:sharedDirector():runWithScene(g_Scene);


