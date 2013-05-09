require "luaScript/PerformanceTest/PerformanceSpriteTest"

local MAX_COUNT     = 5
local LINE_SPACE    = 40
local kItemTagBasic = 1000

local testsName =
{
    "PerformanceNodeChildrenTest",
    "PerformanceParticleTest",
    "PerformanceSpriteTest",
    "PerformanceTextureTest",
    "PerformanceTouchesTest"
}

local s = CCDirector:sharedDirector():getWinSize()

--Create toMainLayr MenuItem
function CreatePerfomBasicLayerMenu(pMenu)
	if nil == pMenu then
		return
	end
	local function toMainLayer()
       local pScene = PerformanceTestMain()
       if pScene ~= nil then
           CCDirector:sharedDirector():replaceScene(pScene)
       end
    end	
    --Create BackMneu
    CCMenuItemFont:setFontName("Arial")
    CCMenuItemFont:setFontSize(24);
   	local pMenuItemFont = CCMenuItemFont:create("Back");
    pMenuItemFont:setPosition(ccp(VisibleRect:rightBottom().x - 50, VisibleRect:rightBottom().y + 25))
    pMenuItemFont:registerScriptTapHandler(toMainLayer)
    pMenu:addChild(pMenuItemFont)
end

----------------------------------
--PerformanceNodeChildrenTest
----------------------------------
local NodeChildrenTestParam = 
{
	kTagInfoLayer = 1,
	kTagMainLayer = 2,
	kTagLabelAtlas = 3,
	kTagBase = 20000,
	TEST_COUNT = 4,
	kMaxNodes = 15000,
	kNodesIncrease = 500,
}

local function runNodeChildrenTest()
	--NodeChildrenMainScene
	local    nLastRenderedCount = 0
    local    nQuantityOfNodes = 0
    local    nCurrentQuantityOfNodes = 0
    --IterateSpriteSheet
    local    pBatchNode  = nil
    
    --BasiceLayer param
    local bControlMenuVisible = false
    local nMaxCases = 0
    local nCurCase  = 0
    
    local pNewscene = CCScene:create()
    
    local function GetTitle()
    	if 0 == nCurCase then
    		return "B - Iterate SpriteSheet"
    	elseif 1 == nCurCase then
    		return "C - Add to spritesheet"
    	elseif 2 == nCurCase then
    		return "D - Del from spritesheet"
    	elseif 3 == nCurCase then
			return "E - Reorder from spritesheet"
		end
    end
    
    local function GetSubTitle()
    	if 0 == nCurCase then
    		return "Iterate children using C Array API. See console"
    	elseif 1 == nCurCase then
    		return "Adds %10 of total sprites with random z. See console"
    	elseif 2 == nCurCase then
    		return "Remove %10 of total sprites placed randomly. See console"
    	elseif 3 == nCurCase then
			return "Reorder %10 of total sprites placed randomly. See console"
		end
    end
    
    local function GetProfilerName()
    	if 0 == nCurCase then
    		return "iter c-array"
    	elseif 1 == nCurCase then
    		return "add sprites"
    	elseif 2 == nCurCase then
    		return "remove sprites"
    	elseif 3 == nCurCase then
			return "reorder sprites"
		end
    end
    
    local function CreateBasicLayerMenuItem(pMenu,bMenuVisible,nMaxCasesNum,nCurCaseIndex)
    	if nil ~= pMenu then
    		bControlMenuVisible = bMenuVisible
    		nMaxCases           = nMaxCasesNum
    		nCurCase            = nCurCaseIndex
    		if true == bControlMenuVisible then
    			local function backCallback()
    				nCurCase = nCurCase - 1
    				if nCurCase < 0 then
    					nCurCase = nCurCase + nMaxCases
    				end
    				ShowCurrentTest()
    			end
    
    			local function restartCallback()
    				ShowCurrentTest()
    			end
    
    			local function nextCallback()
    				nCurCase = nCurCase + 1
    				--No check nMaxCases
    				nCurCase = nCurCase % nMaxCases
    				ShowCurrentTest()
   				end
   				
    			local size = CCDirector:sharedDirector():getWinSize()
    			local item1 = CCMenuItemImage:create(s_pPathB1, s_pPathB2)
    			item1:registerScriptTapHandler(backCallback)
    			pMenu:addChild(item1,kItemTagBasic)
    			local item2 = CCMenuItemImage:create(s_pPathR1, s_pPathR2)
    			item2:registerScriptTapHandler(restartCallback)
    			pMenu:addChild(item2,kItemTagBasic)
    			local item3 = CCMenuItemImage:create(s_pPathF1, s_pPathF2)
    			pMenu:addChild(item3,kItemTagBasic) 
    			item3:registerScriptTapHandler(nextCallback)
    			
    			local size = CCDirector:sharedDirector():getWinSize()
    			item1:setPosition(CCPointMake(size.width / 2 - item2:getContentSize().width * 2, item2:getContentSize().height / 2))
    			item2:setPosition(CCPointMake(size.width / 2, item2:getContentSize().height / 2))
    			item3:setPosition(CCPointMake(size.width / 2 + item2:getContentSize().width * 2, item2:getContentSize().height / 2))
    		end 
    	end
    end
    
   local function updateQuantityLabel()
    	 if nQuantityOfNodes ~= nLastRenderedCount then	
 --     	local pInfoLabel = pNewscene:getChildByTag(NodeChildrenTestParam.kTagInfoLayer)
 			local  pInfoLabel = tolua.cast(pNewscene:getChildByTag(NodeChildrenTestParam.kTagInfoLayer), "CCLabelTTF")
       		local strNode = nQuantityOfNodes.." nodes"
        	pInfoLabel:setString(strNode)
        	nLastRenderedCount = nQuantityOfNodes
        end   	
    end
    
    local function IterateSpriteSheetCArrayUpdate(t)
    		if nil == pBatchNode then
    			return
    		end
    	    local pChildren = pBatchNode:getChildren()
    		local pObject   = nil  
			if nil == pChildren then
				return
			end
    		local i = 0
    		local len = pChildren:count()
    		for i = 0, len - 1, 1 do
        		local  child = tolua.cast(pChildren:objectAtIndex(i), "CCSprite")
        		child:setVisible(false)
    		end
    end
    
    local function AddSpriteSheetUpdate(t)
    	if nil == pBatchNode then
    		return
    	end
    	
    	--15 percent
    	local nTotalToAdd = nCurrentQuantityOfNodes * 0.15
    	local zs = {}
    	if nTotalToAdd > 0 then
    		local pSprites = CCArray:createWithCapacity(nTotalToAdd);
    		local i = 0
    		for i = 0 , nTotalToAdd - 1 do
    			local pSprite = CCSprite:createWithTexture(pBatchNode:getTexture(), CCRectMake(0,0,32,32))
            	pSprites:addObject(pSprite)
            	zs[i]    = math.random(-1,1) * 50
    		end
    		
    		for i = 0 , nTotalToAdd - 1 do
    			local pChild = tolua.cast(pSprites:objectAtIndex(i),"CCNode")
    			pBatchNode:addChild(pChild, zs[i], NodeChildrenTestParam.kTagBase + i);
    		end
    		
    		pBatchNode:sortAllChildren()
    		
    		for i = 0 , nTotalToAdd - 1 do
    			pBatchNode:removeChildByTag( NodeChildrenTestParam.kTagBase + i, true);
    		end
    	end
    end
    
    local function RemoveSpriteSheetUpdate(t)
    	if nil == pBatchNode then
    		return
    	end
     	local nTotalToAdd = nCurrentQuantityOfNodes * 0.15
		if  nTotalToAdd > 0 then
			 local pSprites = CCArray:createWithCapacity(nTotalToAdd);

        	-- Don't include the sprite creation time as part of the profiling
        	local i = 0
        	for i = 0, nTotalToAdd - 1 do
        		 local pSprite = CCSprite:createWithTexture(pBatchNode:getTexture(), CCRectMake(0,0,32,32));
            	 pSprites:addObject(pSprite);
        	end
       		-- add them with random Z (very important!)
        	for i=0, nTotalToAdd - 1  do
        		local pChild = tolua.cast(pSprites:objectAtIndex(i),"CCNode")
        		pBatchNode:addChild(pChild, math.random(-1,1) * 50, NodeChildrenTestParam.kTagBase + i)
            end
                    
        	for i = 0, nTotalToAdd - 1  do
        		pBatchNode:removeChildByTag( NodeChildrenTestParam.kTagBase + i, true);
        	end
        end  
    end
    
    local function ReorderSpriteSheetUpdate(t)
    	if nil == pBatchNode then
    		return
    	end
        -- 15 percent
    	local nTotalToAdd = nCurrentQuantityOfNodes * 0.15;

    	if nTotalToAdd > 0 then  
        	local pSprites = CCArray:createWithCapacity(nTotalToAdd);

        	-- Don't include the sprite creation time as part of the profiling
        	local i = 0
        	for i = 0,nTotalToAdd - 1 do       
            	local pSprite = CCSprite:createWithTexture(pBatchNode:getTexture(), CCRectMake(0,0,32,32));
            	pSprites:addObject(pSprite);
        	end

        	--dd them with random Z (very important!)
        	for i = 0, nTotalToAdd - 1 do 
        		local pChild = tolua.cast(pSprites:objectAtIndex(i),"CCNode")
        		pBatchNode:addChild(pChild, math.random(-1,1) * 50, NodeChildrenTestParam.kTagBase + i)         	
       		end

        	pBatchNode:sortAllChildren();

        	-- reorder them
      		for i = 0, nTotalToAdd - 1 do    	
        		local pNode =  tolua.cast(pBatchNode:getChildren():objectAtIndex(i),"CCNode")
            	pBatchNode:reorderChild(pNode,  math.random(-1,1) * 50);
        	end	      
        	pBatchNode:sortAllChildren();
        	--remove them
        	for i = 0, nTotalToAdd - 1 do   
				pBatchNode:removeChildByTag( NodeChildrenTestParam.kTagBase+i, true);
        	end
        end
    end
    
    local function NodeChildrenScheduleUpdate()
    	if 0 == nCurCase then
	   		pNewscene:scheduleUpdateWithPriorityLua(IterateSpriteSheetCArrayUpdate,0)
    	elseif 1 == nCurCase then
    		pNewscene:scheduleUpdateWithPriorityLua(AddSpriteSheetUpdate,0)
    	elseif 2 == nCurCase then
    		pNewscene:scheduleUpdateWithPriorityLua(RemoveSpriteSheetUpdate,0)   		
    	elseif 3 == nCurCase then
			pNewscene:scheduleUpdateWithPriorityLua(ReorderSpriteSheetUpdate,0)  
		end
    end
    
    local function updateQuantityOfNodes()
    	local s = CCDirector:sharedDirector():getWinSize()  	
   		--increase nodes
    	if( nCurrentQuantityOfNodes < nQuantityOfNodes ) then
    		local i = 0
    		for i = 0,nQuantityOfNodes - nCurrentQuantityOfNodes - 1 do 
            	local sprite = CCSprite:createWithTexture(pBatchNode:getTexture(), CCRectMake(0, 0, 32, 32))
            	pBatchNode:addChild(sprite)
            	sprite:setPosition(ccp( math.random() * s.width, math.random() * s.height))
            	if 0 ~= nCurCase then
            		sprite:setVisible(false)
            	end
        	end    
    	elseif (nCurrentQuantityOfNodes > nQuantityOfNodes ) then 
    		i = 0
        	for i = 0, nCurrentQuantityOfNodes - nQuantityOfNodes - 1 do
            	local index = nCurrentQuantityOfNodes - i - 1
            	pBatchNode:removeChildAtIndex(index, true)
        	end
    	end
    	
    	
    	nCurrentQuantityOfNodes = nQuantityOfNodes
    end
    
    local function onDecrease()
    	nQuantityOfNodes = nQuantityOfNodes - NodeChildrenTestParam.kNodesIncrease
    	if nQuantityOfNodes < 0 then
    		nQuantityOfNodes = 0
    	end
    	
    	updateQuantityLabel()
	   	updateQuantityOfNodes()
    end
    
    local function onIncrease()
    	nQuantityOfNodes = nQuantityOfNodes + NodeChildrenTestParam.kNodesIncrease
    	if nQuantityOfNodes >  NodeChildrenTestParam.kMaxNodes then
    		nQuantityOfNodes =  NodeChildrenTestParam.kMaxNodes
    	end
    	
    	updateQuantityLabel()
    	updateQuantityOfNodes()
    end
    
    
    local function SpecialInitWithQuantityOfNodes()
    --	if 0 == nCurCase then
    		pBatchNode = CCSpriteBatchNode:create("Images/spritesheet1.png")
    		pNewscene:addChild(pBatchNode)
    	--[[
    	else
    		pBatchNode = CCSpriteBatchNode:create("Images/spritesheet1.png");
    		pNewscene:addChild(pBatchNode);
    	end 
    	]]--
    end
    
    local function MainSceneInitWithQuantityOfNodes(nNodes)
    	local s = CCDirector:sharedDirector():getWinSize()
    		
        --Title
   		local pLabel = CCLabelTTF:create(GetTitle(), "Arial", 40)
    	pNewscene:addChild(pLabel, 1)
    	pLabel:setPosition(ccp(s.width/2, s.height-32))
    	pLabel:setColor(ccc3(255,255,40))  	
    	
   		if (nil ~= GetSubTitle()) and ("" ~= GetSubTitle()) then
        	local pSubLabel = CCLabelTTF:create(GetSubTitle(), "Thonburi", 16);
        	pNewscene:addChild(pSubLabel, 1);
        	pSubLabel:setPosition(ccp(s.width/2, s.height-80))
        end
        
        nLastRenderedCount = 0 	
    	nCurrentQuantityOfNodes = 0
    	nQuantityOfNodes = nNodes
    	
    	--"+"¡¢"-" Menu
		CCMenuItemFont:setFontSize(65);
    	local pDecrease = CCMenuItemFont:create(" - ")
    	pDecrease:registerScriptTapHandler(onDecrease)
    	pDecrease:setColor(ccc3(0,200,20));
    	local pIncrease = CCMenuItemFont:create(" + ")
    	pIncrease:registerScriptTapHandler(onIncrease)
   		pIncrease:setColor(ccc3(0,200,20));
    	
    	local pMenuAddOrSub = CCMenu:create()
    	pMenuAddOrSub:addChild(pDecrease)
    	pMenuAddOrSub:addChild(pIncrease)
    	pMenuAddOrSub:alignItemsHorizontally();
    	pMenuAddOrSub:setPosition(ccp(s.width/2, s.height/2+15));
   		pNewscene:addChild(pMenuAddOrSub,1)
   		
   		--InfoLayer
   		local pInfoLabel = CCLabelTTF:create("0 nodes", "Marker Felt", 30);
    	pInfoLabel:setColor(ccc3(0,200,20));
    	pInfoLabel:setPosition(ccp(s.width/2, s.height/2-15));
    	pNewscene:addChild(pInfoLabel, 1, NodeChildrenTestParam.kTagInfoLayer);
    	
    	--NodeChildrenMenuLayer
    	local pNodeChildrenMenuLayer 	= CCLayer:create()
    	local pNodeChildrenMenuMenu     = CCMenu:create()
    	CreatePerfomBasicLayerMenu(pNodeChildrenMenuMenu)
		CreateBasicLayerMenuItem(pNodeChildrenMenuMenu,true,NodeChildrenTestParam.TEST_COUNT,nCurCase)
		pNodeChildrenMenuMenu:setPosition(ccp(0, 0))
		pNodeChildrenMenuLayer:addChild(pNodeChildrenMenuMenu)
		pNewscene:addChild(pNodeChildrenMenuLayer) 
		
		updateQuantityLabel()
		updateQuantityOfNodes()	
		
    end
	
	function ShowCurrentTest()
		if nil ~= pNewscene then
			pNewscene:unscheduleUpdate()
		end
		
		pNewscene = CCScene:create()
    	if nil ~= pNewscene then
    		SpecialInitWithQuantityOfNodes()
			MainSceneInitWithQuantityOfNodes(nQuantityOfNodes)
--			pNewscene:registerScriptHandler(onNodeEvent)
			NodeChildrenScheduleUpdate()
			CCDirector:sharedDirector():replaceScene(pNewscene)
    	end	
    end
    
	SpecialInitWithQuantityOfNodes()
	MainSceneInitWithQuantityOfNodes(NodeChildrenTestParam.kNodesIncrease)
--	pNewscene:registerScriptHandler(onNodeEvent)
	NodeChildrenScheduleUpdate()
	
	return pNewscene
end
----------------------------------
--PerformanceParticleTest
----------------------------------
local ParticleTestParam = 
{
    kTagInfoLayer = 1,
    kTagMainLayer = 2,
    kTagParticleSystem = 3,
    kTagLabelAtlas = 4,
    kTagMenuLayer = 1000,

    TEST_COUNT = 4,
    kMaxParticles = 14000,
    kNodesIncrease = 500,
}

----------------------------------
--PerformanceTextureTest
----------------------------------
local TextureTestParam = 
{
	TEST_COUNT = 1,
}

local function runTextureTest()
	
	local function GetTitle()
		return "Texture Performance Test"
	end
	
	local function GetSubtitle()
		return "See console for results"
	end
	
	local nTexCurCase = 0	
	local pNewscene = CCScene:create()
	local pLayer    = CCLayer:create()
	local s 		= CCDirector:sharedDirector():getWinSize()
	
	local function PerformTestsPNG(strFileName)
		  local time
		  local pTexture = nil
    	  local pCache = CCTextureCache:sharedTextureCache()
    	  print("RGBA 8888")
    	  CCTexture2D:setDefaultAlphaPixelFormat(kCCTexture2DPixelFormat_RGBA8888)
    	  pTexture = pCache:addImage(strFileName) 		  
    	  if nil ~= pTexture then
    	  	--os.time()--get secs,not micr sec
    		print("add sucess")
    	  else
    		print(" ERROR")
          end
    	  pCache:removeTexture(pTexture)
    	  
    	  print("RGBA 4444");
    	  CCTexture2D:setDefaultAlphaPixelFormat(kCCTexture2DPixelFormat_RGBA4444)
    	  --gettimeofday(&now, NULL);
    	  pTexture = pCache:addImage(strFileName);
    	  if nil ~= pTexture then 
            print("add sucess")
    	  else
        	print(" ERROR")
          end
    	  pCache:removeTexture(pTexture)
    	  
    	  print("RGBA 5551");
    	  CCTexture2D:setDefaultAlphaPixelFormat(kCCTexture2DPixelFormat_RGB5A1);
    	  --gettimeofday(&now, NULL);
    	  pTexture = pCache:addImage(strFileName);
    	  if nil ~= pTexture then
        	 print("add sucess")
    	  else
        	 print(" ERROR")
          end
    	  pCache:removeTexture(pTexture);
    	  
    	  print("RGB 565");
   		  CCTexture2D:setDefaultAlphaPixelFormat(kCCTexture2DPixelFormat_RGB565);
   		 -- gettimeofday(&now, NULL);    
    	 pTexture = pCache:addImage(strFileName);
    	 if nil ~= pTexture then
        	--CCLog("  ms:%f", calculateDeltaTime(&now) );
        	print("add sucess")
    	 else
       	    print(" ERROR");
       	 end
    	 pCache:removeTexture(pTexture);   	  
	end
	local function PerformTests()
		  print("--------")
    	  print("--- PNG 128x128 ---")
    	  PerformTestsPNG("Images/test_image.png")
    	  
    	  print("--- PNG 512x512 ---")
    	  PerformTestsPNG("Images/texture512x512.png")
    	  
    	  print("EMPTY IMAGE")
    	  print("--- PNG 1024x1024 ---")
    	  PerformTestsPNG("Images/texture1024x1024.png")
    	  
    	  print("SPRITESHEET IMAGE");
    	  print("--- PNG 1024x1024 ---");
   		  PerformTestsPNG("Images/PlanetCute-1024x1024.png");
   		  
   		  print("LANDSCAPE IMAGE");
	      print("--- PNG 1024x1024 ---");
    	  PerformTestsPNG("Images/landscape-1024x1024.png");
	end
	
	local function InitTextureMenuLayer()
		if nil == pLayer then
			return
		end
		
		--Title
    	local pLabel = CCLabelTTF:create(GetTitle(), "Arial", 40)
    	pLayer:addChild(pLabel, 1)
    	pLabel:setPosition(ccp(s.width/2, s.height-32))
    	pLabel:setColor(ccc3(255,255,40))

    	--Subtitle
        local pSubLabel = CCLabelTTF:create(GetSubtitle(), "Thonburi", 16)
        pLayer:addChild(pSubLabel, 1)
        pSubLabel:setPosition(ccp(s.width/2, s.height-80))
        
        --menu
        local pMenu = CCMenu:create()
        CreatePerfomBasicLayerMenu(pMenu)
        pMenu:setPosition(ccp(0, 0))
        pLayer:addChild(pMenu)
        
        PerformTests()
	end
	
	InitTextureMenuLayer()
	pNewscene:addChild(pLayer)
	return pNewscene
end
----------------------------------
--PerformanceTouchesTest
----------------------------------
local TouchesTestParam = 
{
	TEST_COUNT = 2,
}
local function runTouchesTest()
	local nTouchCurCase = 0
	--PerformBasicLayer param
	local  bControlMenuVisible = false
    local  nMaxCases = 0
    local  nCurCase = 0
    --TouchesMainScene param
    local  pClassLabel = nil
    local  nNumberOfTouchesB  = 0
    local  nNumberOfTouchesM  = 0
    local  nNumberOfTouchesE  = 0
    local  nNumberOfTouchesC  = 0
    local  fElapsedTime       = 0.0
    
    local  s = CCDirector:sharedDirector():getWinSize()
   	local  pNewscene = CCScene:create()
	local  pLayer    = CCLayer:create()
	
    local  function GetTitle()
    	if 0 == nCurCase then
    		return "Targeted touches"
    	elseif 1 == nCurCase then
    		return "Standard touches"
    	end
    end
	
    local function CreateBasicLayerMenuItem(pMenu,bMenuVisible,nMaxCasesNum,nCurCaseIndex)
    	if nil ~= pMenu then
    		bControlMenuVisible = bMenuVisible
    		nMaxCases           = nMaxCasesNum
    		nCurCase            = nCurCaseIndex
    		if true == bControlMenuVisible then
    			local function backCallback()
    				nCurCase = nCurCase - 1
    				if nCurCase < 0 then
    					nCurCase = nCurCase + nMaxCases
    				end
    				ShowCurrentTest()
    			end
    
    			local function restartCallback()
    				ShowCurrentTest()
    			end
    
    			local function nextCallback()
    				nCurCase = nCurCase + 1
    				--No check nMaxCases
    				nCurCase = nCurCase % nMaxCases
    				ShowCurrentTest()
   				end
   				
    			local size = CCDirector:sharedDirector():getWinSize()
    			local item1 = CCMenuItemImage:create(s_pPathB1, s_pPathB2)
    			item1:registerScriptTapHandler(backCallback)
    			pMenu:addChild(item1,kItemTagBasic)
    			local item2 = CCMenuItemImage:create(s_pPathR1, s_pPathR2)
    			item2:registerScriptTapHandler(restartCallback)
    			pMenu:addChild(item2,kItemTagBasic)
    			local item3 = CCMenuItemImage:create(s_pPathF1, s_pPathF2)
    			pMenu:addChild(item3,kItemTagBasic) 
    			item3:registerScriptTapHandler(nextCallback)
    			
    			local size = CCDirector:sharedDirector():getWinSize()
    			item1:setPosition(CCPointMake(size.width / 2 - item2:getContentSize().width * 2, item2:getContentSize().height / 2))
    			item2:setPosition(CCPointMake(size.width / 2, item2:getContentSize().height / 2))
    			item3:setPosition(CCPointMake(size.width / 2 + item2:getContentSize().width * 2, item2:getContentSize().height / 2))
    		end 
    	end
    end
    
    local function update(fTime)
    	  fElapsedTime = fElapsedTime + fTime

    	  if  fElapsedTime > 1.0 then
    	  	  local fFrameRateB = nNumberOfTouchesB / fElapsedTime
        	  local fFrameRateM = nNumberOfTouchesM / fElapsedTime
        	  local fFrameRateE = nNumberOfTouchesE / fElapsedTime
        	  local fFrameRateC = nNumberOfTouchesC / fElapsedTime
        	  fElapsedTime = 0;
        	  nNumberOfTouchesB = 0
        	  nNumberOfTouchesM = 0
        	  nNumberOfTouchesE = 0
        	  nNumberOfTouchesC = 0
        	  
       		  local strInfo = string.format("%.1f %.1f %.1f %.1f",fFrameRateB, fFrameRateM, fFrameRateE, fFrameRateC)
       		  if nil ~= pClassLabel then
       		  	pClassLabel:setString(strInfo); 
       		  end
    	  end
  
    end
    
    -- handling touch events   
    local function onTouchBegan(tableArray)
		if 0 == nCurCase then
			nNumberOfTouchesB = nNumberOfTouchesB + 1
		elseif 1 == nCurCase then
			nNumberOfTouchesB  = nNumberOfTouchesB + table.getn(tableArray)
		end
    end
    
    local function onTouchMoved(tableArray)			
		if 0 == nCurCase then
			nNumberOfTouchesM = nNumberOfTouchesM + 1
		elseif 1 == nCurCase then
			nNumberOfTouchesM  = nNumberOfTouchesM + table.getn(tableArray)
		end
    end
    
    local function onTouchEnded(tableArray)			
		if 0 == nCurCase then
			nNumberOfTouchesE = nNumberOfTouchesE + 1
		elseif 1 == nCurCase then
			nNumberOfTouchesE  = nNumberOfTouchesE + table.getn(tableArray)
		end
    end
    
    local function onTouchCancelled(tableArray)			
		if 0 == nCurCase then
			nNumberOfTouchesC = nNumberOfTouchesC + 1
		elseif 1 == nCurCase then
			nNumberOfTouchesC  = nNumberOfTouchesC + table.getn(tableArray)
		end
    end

   	local function onTouch(eventType,tableArray)
        if eventType == "began" then
            return onTouchBegan(tableArray)
        elseif eventType == "moved" then
            return onTouchMoved(tableArray)
        elseif eventType == "ended" then
        	return onTouchEnded(tableArray)	
        elseif eventType == "cancelled" then
        	return onTouchCancelled(tableArray)	
        end
    end
    
    local function InitLayer()
     	--menu
     	local pTouchesTestMenu     = CCMenu:create()
    	CreatePerfomBasicLayerMenu(pTouchesTestMenu)
		CreateBasicLayerMenuItem(pTouchesTestMenu,true,TouchesTestParam.TEST_COUNT,nCurCase)
		pTouchesTestMenu:setPosition(ccp(0, 0))
		pLayer:addChild(pTouchesTestMenu)
		
     	--Title
   	    local pLabel = CCLabelTTF:create(GetTitle(), "Arial", 40)
    	pLayer:addChild(pLabel, 1)
   		pLabel:setPosition(ccp(s.width/2, s.height-32))
	   	pLabel:setColor(ccc3(255,255,40)) 
    	
    	pLayer:scheduleUpdateWithPriorityLua(update,0)	
    
    	pClassLabel = CCLabelBMFont:create("00.0", "fonts/arial16.fnt");
    	pClassLabel:setPosition(ccp(s.width/2, s.height/2));
    	pLayer:addChild(pClassLabel); 
    
    	fElapsedTime = 0.0
    	nNumberOfTouchesB = 0
    	nNumberOfTouchesM = 0
    	nNumberOfTouchesE = 0
    	nNumberOfTouchesC = 0   
    	pLayer:setTouchEnabled(true)
    	
    	pLayer:registerScriptTouchHandler(onTouch,true) 
    end
    
    function ShowCurrentTest()
    	if nil ~= pLayer then
			pLayer:unscheduleUpdate()
		end
		
		pNewscene = CCScene:create()
		
    	if nil ~= pNewscene then
    		pLayer = CCLayer:create()
    		InitLayer()
			pNewscene:addChild(pLayer)
			CCDirector:sharedDirector():replaceScene(pNewscene)
    	end	
    end

	InitLayer()
	pNewscene:addChild(pLayer)
	return pNewscene
end


------------------------
--
------------------------
local CreatePerformancesTestTable = 
{
	runNodeChildrenTest,
	runParticleTest,
	runSpriteTest,
	runTextureTest,
	runTouchesTest	
}

local function CreatePerformancesTestScene(nPerformanceNo)
  local pNewscene = CreatePerformancesTestTable[nPerformanceNo]()
  return pNewscene
end
local function menuCallback(tag, pMenuItem)
	local scene = nil
    local nIdx = pMenuItem:getZOrder() - kItemTagBasic
	local PerformanceTestScene = CreatePerformancesTestScene(nIdx)
    if nil ~= PerformanceTestScene then
         CCDirector:sharedDirector():replaceScene(PerformanceTestScene)
    end
end

local function PerformanceMainLayer()
	local layer = CCLayer:create()

	local menu = CCMenu:create()
    menu:setPosition(CCPointMake(0, 0))
    CCMenuItemFont:setFontName("Arial")
    CCMenuItemFont:setFontSize(24)
    for i = 1, MAX_COUNT do
		local item = CCMenuItemFont:create(testsName[i])
        item:registerScriptTapHandler(menuCallback)
        item:setPosition(s.width / 2, s.height - (i + 1) * LINE_SPACE)
        menu:addChild(item, kItemTagBasic + i)
	end

    layer:addChild(menu)

	return layer
end

-------------------------------------
--  Performance Test
-------------------------------------
function PerformanceTestMain()
	local scene = CCScene:create()

	scene:addChild(PerformanceMainLayer())
	scene:addChild(CreateBackMenuItem())

	return scene
end
