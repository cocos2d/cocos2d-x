winSize = cocos2d.CCDirector:sharedDirector():getWinSize()

sceneGame= cocos2d.CCScene:node()
layer= cocos2d.CCLayerColor:layerWithColor( cocos2d.ccc4(0,0,255, 255) )
sceneGame:addChild( layer )

label= cocos2d.CCLabelTTF:labelWithString("LuaProjectTemplate", "Arial", 48.0)
label:setColor( cocos2d.ccc3(255,255,255) )
label:setPosition( cocos2d.CCPoint( winSize.width/2, winSize.height/2) )
layer:addChild( label )

-- run 
cocos2d.CCDirector:sharedDirector():runWithScene( sceneGame )
