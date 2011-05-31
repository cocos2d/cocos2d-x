lastMouseX = 0;
lastMouseY = 0;



g_Scene = cocos2d.CCScene:node();
pSprite = cocos2d.CCSprite:spriteWithFile("90001.jpg");pSprite:setPosition(cocos2d.CCPoint(300, 400));


pLayer = cocos2d.CCLayer:node();
pLayer:setIsTouchEnabled(true);
pLayer:setAnchorPoint(cocos2d.CCPoint(0,0));
pLayer:setPosition( cocos2d.CCPoint(0, -300) );
g_Scene:addChild(pLayer);



function btnTouchMove(e)
 
cocos2d.CCLuaLog("mousemove");
touch = e:anyObject()
debug.setmetatable(touch, cocos2d.CCTouch)
cocos2d.CCLuaLog("btnTouchBegin")
X = touch:locationInView(touch:view()).x
Y = touch:locationInView(touch:view()).y

OffX = lastMouseX - X;
OffY = lastMouseY - Y;
lastMouseX = X;
lastMouseY = Y;

point = pLayer:getPosition();

point.x = point.x + OffX;
--point.y = point.y + OffY;

if point.x  >100 then
point.x = 100
elseif point.x  < 0 then
point.x = 0
end

--[[
if point.y  > 405 then 
point.y = 405
elseif
point.y  < -500 then
point.y = -500
end
]]

pLayer:setPosition(point)



end --fuction


function btnTouchBegin(e)

count = e:count();
if count > 1 then
cocos2d.CCLuaLog("2 click");
end

touch = e:anyObject()
debug.setmetatable(touch, cocos2d.CCTouch)
cocos2d.CCLuaLog("btnTouchBegin")
lastMouseX = touch:locationInView(touch:view()).x
lastMouseY = touch:locationInView(touch:view()).y

cocos2d.CCLuaLog("btnTouchBegin")
end




function btnTouchEnd(e)
cocos2d.CCLuaLog("btnTouchEnd")
end

pLayer.__CCTouchDelegate__:registerLuaTouchEvent("ccTouchBegan", "btnTouchBegin")
pLayer.__CCTouchDelegate__:registerLuaTouchEvent("ccTouchMoved", "btnTouchMove")
pLayer.__CCTouchDelegate__:registerLuaTouchEvent("ccTouchEnded", "btnTouchEnd")
pLayer:addChild(pSprite)




menuItem = cocos2d.CCMenuItemImage:itemFromNormalImage("menu2.png","menu2.png");
menuItem:setAnchorPoint(cocos2d.CCPoint(0,0));
menuItem:setPosition( cocos2d.CCPoint(100, 200) );	
menuItem:registerMenuHandler("CloseMenu");
pMenu = cocos2d.CCMenu:menuWithItem(menuItem);
pMenu:setPosition( cocos2d.CCPoint(1000, 200) );
g_Scene:addChild(pMenu);



function CloseMenu()

pMenu:setPosition(cocos2d.CCPoint(1000, 200) );


end



function PopMenu()
 
pMenu:setPosition( cocos2d.CCPoint(0, -50) );
cocos2d.CCLuaLog("pop click");

end


 

pCloseItem = cocos2d.CCMenuItemImage:itemFromNormalImage("menu1.png","menu1.png");
pCloseItem:setPosition( cocos2d.CCPoint(30, 40) );	
pCloseItem:registerMenuHandler("PopMenu");
pcloseMenu = cocos2d.CCMenu:menuWithItem(pCloseItem);
pcloseMenu:setPosition( cocos2d.CCPoint(30, 40) );
g_Scene:addChild(pcloseMenu);
	


for i=0,3,1 do
for j=0,1,1 do

landSprite = cocos2d.CCSprite:spriteWithFile("land1.png");
pLayer:addChild(landSprite);

landSprite:setAnchorPoint(cocos2d.CCPoint(0,0));
landSprite:setPosition(cocos2d.CCPoint(90+j*180 - i%2*90, 200+i*95/2));

end
end



--crop

for i=0,3,1 do
for j=0,1,1 do

texturecrop = cocos2d.CCTextureCache:sharedTextureCache():addImage("crop1.png");
framecrop = cocos2d.CCSpriteFrame:frameWithTexture(texturecrop, cocos2d.CCRectMake(0, 0, 105, 95));
spritecrop = cocos2d.CCSprite:spriteWithSpriteFrame(framecrop);

pLayer:addChild(spritecrop);

spritecrop:setAnchorPoint(cocos2d.CCPoint(0,0));
spritecrop:setPosition(cocos2d.CCPoint(45+90+j*180 - i%2*90, 25+200+i*95/2));

end
end




nFrameWidth = 105;
nFrameHeight = 95;

texture = cocos2d.CCTextureCache:sharedTextureCache():addImage("dog1.png");
frame0 = cocos2d.CCSpriteFrame:frameWithTexture(texture, cocos2d.CCRectMake(0, 0, nFrameWidth, nFrameHeight));
frame1 = cocos2d.CCSpriteFrame:frameWithTexture(texture, cocos2d.CCRectMake(nFrameWidth*1, 0, nFrameWidth, nFrameHeight));


spritedog = cocos2d.CCSprite:spriteWithSpriteFrame(frame0);
spritedog:setPosition(cocos2d.CCPoint(300, 500));
pLayer:addChild(spritedog);



animFrames = cocos2d.CCMutableArray_CCSpriteFrame__:new(2);

animFrames:addObject(frame0);
animFrames:addObject(frame1);


animation = cocos2d.CCAnimation:animationWithName("wait", 0.5, animFrames)
--animation:addFrame(frame0);
--animation:addFrame(frame1);

animate = cocos2d.CCAnimate:actionWithAnimation(animation, false);
spritedog:runAction(cocos2d.CCRepeatForever:actionWithAction(animate))





--[[
seq = cocos2d.CCSequence:actionOneTwo(animate,nil);
spritedog:runAction(cocos2d.CCRepeatForever:actionWithAction(seq));
--animFrames:release();
 ]]

--[[
animation = cocos2d.CCAnimation();
animate = cocos2d.CCAnimate:new();
animation:initWithName("pest_anim", 0.19, animFrames);
animate:initWithAnimation(animation, true);
animFrames:release();
animation:release();

repeat1 = cocos2d.CCRepeatForever:initWithAction(animate);
 
animate:release();

]]


cocos2d.CCDirector:sharedDirector():runWithScene(g_Scene);



function tick(cc)


point = cocos2d.CCPoint(300, 500);
point = spritedog:getPosition();


if point.x > 600 then
point.x = 0
spritedog:setPosition(point)
else
point.x = point.x + 1 
spritedog:setPosition(point) 
end
--cocos2d.CCLuaLog("222");
--cocos2d.CCMessageBox("aaaa", "bbbbb")
end

cocos2d.CCDirector:sharedDirector():registerTick("tick")

print("asdf");

 
