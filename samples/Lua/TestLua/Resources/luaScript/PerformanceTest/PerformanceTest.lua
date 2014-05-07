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
    CCMenuItemFont:setFontSize(24)
   	local pMenuItemFont = CCMenuItemFont:create("Back")
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
    		local pSprites = CCArray:createWithCapacity(nTotalToAdd)
    		local i = 0
    		for i = 0 , nTotalToAdd - 1 do
    			local pSprite = CCSprite:createWithTexture(pBatchNode:getTexture(), CCRectMake(0,0,32,32))
            	pSprites:addObject(pSprite)
            	zs[i]    = math.random(-1,1) * 50
    		end
    		
    		for i = 0 , nTotalToAdd - 1 do
    			local pChild = tolua.cast(pSprites:objectAtIndex(i),"CCNode")
    			pBatchNode:addChild(pChild, zs[i], NodeChildrenTestParam.kTagBase + i)
    		end
    		
    		pBatchNode:sortAllChildren()
    		
    		for i = 0 , nTotalToAdd - 1 do
    			pBatchNode:removeChildByTag( NodeChildrenTestParam.kTagBase + i, true)
    		end
    	end
    end
    
    local function RemoveSpriteSheetUpdate(t)
    	if nil == pBatchNode then
    		return
    	end
     	local nTotalToAdd = nCurrentQuantityOfNodes * 0.15
		if  nTotalToAdd > 0 then
			 local pSprites = CCArray:createWithCapacity(nTotalToAdd)

        	-- Don't include the sprite creation time as part of the profiling
        	local i = 0
        	for i = 0, nTotalToAdd - 1 do
        		 local pSprite = CCSprite:createWithTexture(pBatchNode:getTexture(), CCRectMake(0,0,32,32))
            	 pSprites:addObject(pSprite)
        	end
       		-- add them with random Z (very important!)
        	for i=0, nTotalToAdd - 1  do
        		local pChild = tolua.cast(pSprites:objectAtIndex(i),"CCNode")
        		pBatchNode:addChild(pChild, math.random(-1,1) * 50, NodeChildrenTestParam.kTagBase + i)
            end
                    
        	for i = 0, nTotalToAdd - 1  do
        		pBatchNode:removeChildByTag( NodeChildrenTestParam.kTagBase + i, true)
        	end
        end  
    end
    
    local function ReorderSpriteSheetUpdate(t)
    	if nil == pBatchNode then
    		return
    	end
        -- 15 percent
    	local nTotalToAdd = nCurrentQuantityOfNodes * 0.15

    	if nTotalToAdd > 0 then  
        	local pSprites = CCArray:createWithCapacity(nTotalToAdd)

        	-- Don't include the sprite creation time as part of the profiling
        	local i = 0
        	for i = 0,nTotalToAdd - 1 do       
            	local pSprite = CCSprite:createWithTexture(pBatchNode:getTexture(), CCRectMake(0,0,32,32))
            	pSprites:addObject(pSprite)
        	end

        	--dd them with random Z (very important!)
        	for i = 0, nTotalToAdd - 1 do 
        		local pChild = tolua.cast(pSprites:objectAtIndex(i),"CCNode")
        		pBatchNode:addChild(pChild, math.random(-1,1) * 50, NodeChildrenTestParam.kTagBase + i)         	
       		end

        	pBatchNode:sortAllChildren()

        	-- reorder them
      		for i = 0, nTotalToAdd - 1 do    	
        		local pNode =  tolua.cast(pBatchNode:getChildren():objectAtIndex(i),"CCNode")
            	pBatchNode:reorderChild(pNode,  math.random(-1,1) * 50)
        	end	      
        	pBatchNode:sortAllChildren()
        	--remove them
        	for i = 0, nTotalToAdd - 1 do   
				pBatchNode:removeChildByTag( NodeChildrenTestParam.kTagBase+i, true)
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
    		pBatchNode = CCSpriteBatchNode:create("Images/spritesheet1.png")
    		pNewscene:addChild(pBatchNode)
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
        	local pSubLabel = CCLabelTTF:create(GetSubTitle(), "Thonburi", 16)
        	pNewscene:addChild(pSubLabel, 1)
        	pSubLabel:setPosition(ccp(s.width/2, s.height-80))
        end
        
        nLastRenderedCount = 0 	
    	nCurrentQuantityOfNodes = 0
    	nQuantityOfNodes = nNodes
    	
    	--"+","-" Menu
		CCMenuItemFont:setFontSize(65)
    	local pDecrease = CCMenuItemFont:create(" - ")
    	pDecrease:registerScriptTapHandler(onDecrease)
    	pDecrease:setColor(ccc3(0,200,20))
    	local pIncrease = CCMenuItemFont:create(" + ")
    	pIncrease:registerScriptTapHandler(onIncrease)
   		pIncrease:setColor(ccc3(0,200,20))
    	
    	local pMenuAddOrSub = CCMenu:create()
    	pMenuAddOrSub:addChild(pDecrease)
    	pMenuAddOrSub:addChild(pIncrease)
    	pMenuAddOrSub:alignItemsHorizontally()
    	pMenuAddOrSub:setPosition(ccp(s.width/2, s.height/2+15))
   		pNewscene:addChild(pMenuAddOrSub,1)
   		
   		--InfoLayer
   		local pInfoLabel = CCLabelTTF:create("0 nodes", "Marker Felt", 30)
    	pInfoLabel:setColor(ccc3(0,200,20))
    	pInfoLabel:setPosition(ccp(s.width/2, s.height/2-15))
    	pNewscene:addChild(pInfoLabel, 1, NodeChildrenTestParam.kTagInfoLayer)
    	
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
    
    kSubMenuBasicZOrder = 10
}

local function runParticleTest()
	--PerformanceParticle param
    local nLastRenderedCount = 0
    local nQuantityParticles = 0
    local nSubtestNumber     = 0
    --BasiceLayer param
    local bControlMenuVisible = false
    local nMaxCases = 0
    local nCurCase  = 0
    
    local ScheduleSelector = nil
    
    local pNewScene = CCScene:create()
    
    local function GetTitle()
    	local strTitle = nil
    	if 0 == nCurCase then
    		strTitle = string.format("A (%d) size=4",nSubtestNumber)
    	elseif 1 == nCurCase then
    		strTitle = string.format("B (%d) size=8",nSubtestNumber)
    	elseif 2 == nCurCase then
    		strTitle = string.format("C (%d) size=32",nSubtestNumber)
    	elseif 3 == nCurCase then
    		strTitle = string.format("D (%d) size=64",nSubtestNumber)
    	end
    	return strTitle
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
    
    local function TestNCallback(tag,pMenuItem)
		local nIndex = pMenuItem:getZOrder() - ParticleTestParam.kSubMenuBasicZOrder
		nSubtestNumber = nIndex
		ShowCurrentTest()
    end
    
    local function UpdateQuantityLabel()
    	if nQuantityParticles ~= nLastRenderedCount then
    		local  pInfoLabel = tolua.cast(pNewScene:getChildByTag(ParticleTestParam.kTagInfoLayer), "CCLabelTTF")
    		local  strInfo    = string.format("%u particles", nQuantityParticles)
    		pInfoLabel:setString(strInfo)
    		
    		nLastRenderedCount = nQuantityParticles
    	end
    end
    
    local function doTest()
   		local s = CCDirector:sharedDirector():getWinSize()
   		local pParticleSystem = tolua.cast(pNewScene:getChildByTag(ParticleTestParam.kTagParticleSystem),"CCParticleSystem")
   		if nil == pParticleSystem then
   			return
   		end
   		if 0 == nCurCase then  		
    		   --duration
    		   pParticleSystem:setDuration(-1)

    		  --gravity
    		  pParticleSystem:setGravity(ccp(0,-90))

    	      --angle
    		  pParticleSystem:setAngle(90)
    		  pParticleSystem:setAngleVar(0)

    		  --radial
    		  pParticleSystem:setRadialAccel(0)
    		  pParticleSystem:setRadialAccelVar(0)

    		  -- speed of particles
              pParticleSystem:setSpeed(180)
    		  pParticleSystem:setSpeedVar(50)
    		  
    		  -- emitter position
    		  pParticleSystem:setPosition(ccp(s.width/2, 100))
   			  pParticleSystem:setPosVar(ccp(s.width/2,0))

    		  -- life of particles
   			  pParticleSystem:setLife(2.0)
    		  pParticleSystem:setLifeVar(1)

    		  --emits per frame
    		  pParticleSystem:setEmissionRate(pParticleSystem:getTotalParticles() / pParticleSystem:getLife())
    		  
    		  --color of particles
    		  pParticleSystem:setStartColor(ccc4f(0.5, 0.5, 0.5, 1.0))

    		  pParticleSystem:setStartColorVar( ccc4f(0.5, 0.5, 0.5, 1.0))

    		  pParticleSystem:setEndColor(ccc4f(0.1, 0.1, 0.1, 0.2))
   
    		  pParticleSystem:setEndColorVar(ccc4f(0.1, 0.1, 0.1, 0.2))

    		  -- size, in pixels
    		  pParticleSystem:setEndSize(4.0)
    		  pParticleSystem:setStartSize(4.0)
    		  pParticleSystem:setEndSizeVar(0)
    		  pParticleSystem:setStartSizeVar(0)

    		  -- additive
    		  pParticleSystem:setBlendAdditive(false)
    				
    	elseif 1 == nCurCase then
    		  --duration
    		  pParticleSystem:setDuration(-1)

    		  --gravity
    		  pParticleSystem:setGravity(ccp(0,-90))

    	      --angle
    		  pParticleSystem:setAngle(90)
    		  pParticleSystem:setAngleVar(0)

    		  --radial
    		  pParticleSystem:setRadialAccel(0)
    		  pParticleSystem:setRadialAccelVar(0)
    		  
    		      		  -- speed of particles
              pParticleSystem:setSpeed(180)
    		  pParticleSystem:setSpeedVar(50)
    		  
    		  -- emitter position
    		  pParticleSystem:setPosition(ccp(s.width/2, 100))
   			  pParticleSystem:setPosVar(ccp(s.width/2,0))

    		  -- life of particles
   			  pParticleSystem:setLife(2.0)
    		  pParticleSystem:setLifeVar(1)

    		  --emits per frame
    		  pParticleSystem:setEmissionRate(pParticleSystem:getTotalParticles() / pParticleSystem:getLife())
    		  
    		  --color of particles
    		  pParticleSystem:setStartColor(ccc4f(0.5, 0.5, 0.5, 1.0))

    		  pParticleSystem:setStartColorVar( ccc4f(0.5, 0.5, 0.5, 1.0))

    		  pParticleSystem:setEndColor(ccc4f(0.1, 0.1, 0.1, 0.2))
   
    		  pParticleSystem:setEndColorVar(ccc4f(0.1, 0.1, 0.1, 0.2))

    		  -- size, in pixels
    		  pParticleSystem:setEndSize(8.0)
    		  pParticleSystem:setStartSize(8.0)
    		  pParticleSystem:setEndSizeVar(0)
    		  pParticleSystem:setStartSizeVar(0)  
    		  
    		  -- additive
    		  pParticleSystem:setBlendAdditive(false)		
    	elseif 2 == nCurCase then
    	   	  --duration
    		  pParticleSystem:setDuration(-1)

    		  --gravity
    		  pParticleSystem:setGravity(ccp(0,-90))

    	      --angle
    		  pParticleSystem:setAngle(90)
    		  pParticleSystem:setAngleVar(0)

    		  --radial
    		  pParticleSystem:setRadialAccel(0)
    		  pParticleSystem:setRadialAccelVar(0)
    		  
    		      		  -- speed of particles
              pParticleSystem:setSpeed(180)
    		  pParticleSystem:setSpeedVar(50)
    		  
    		  -- emitter position
    		  pParticleSystem:setPosition(ccp(s.width/2, 100))
   			  pParticleSystem:setPosVar(ccp(s.width/2,0))

    		  -- life of particles
   			  pParticleSystem:setLife(2.0)
    		  pParticleSystem:setLifeVar(1)

    		  --emits per frame
    		  pParticleSystem:setEmissionRate(pParticleSystem:getTotalParticles() / pParticleSystem:getLife())
    		  
    		  --color of particles
    		  pParticleSystem:setStartColor(ccc4f(0.5, 0.5, 0.5, 1.0))

    		  pParticleSystem:setStartColorVar( ccc4f(0.5, 0.5, 0.5, 1.0))

    		  pParticleSystem:setEndColor(ccc4f(0.1, 0.1, 0.1, 0.2))
   
    		  pParticleSystem:setEndColorVar(ccc4f(0.1, 0.1, 0.1, 0.2))

    		  -- size, in pixels
    		  pParticleSystem:setEndSize(32.0)
    		  pParticleSystem:setStartSize(32.0)
    		  pParticleSystem:setEndSizeVar(0)
    		  pParticleSystem:setStartSizeVar(0)
    		
    		  -- additive
    		  pParticleSystem:setBlendAdditive(false)	
    	elseif 3 == nCurCase then
    	   	  --duration
    		  pParticleSystem:setDuration(-1)

    		  --gravity
    		  pParticleSystem:setGravity(ccp(0,-90))

    	      --angle
    		  pParticleSystem:setAngle(90)
    		  pParticleSystem:setAngleVar(0)

    		  --radial
    		  pParticleSystem:setRadialAccel(0)
    		  pParticleSystem:setRadialAccelVar(0)
    		  
    		  -- speed of particles
              pParticleSystem:setSpeed(180)
    		  pParticleSystem:setSpeedVar(50)
    		  
    		  -- emitter position
    		  pParticleSystem:setPosition(ccp(s.width/2, 100))
   			  pParticleSystem:setPosVar(ccp(s.width/2,0))

    		  -- life of particles
   			  pParticleSystem:setLife(2.0)
    		  pParticleSystem:setLifeVar(1)

    		  --emits per frame
    		  pParticleSystem:setEmissionRate(pParticleSystem:getTotalParticles() / pParticleSystem:getLife())
    		  
    		  --color of particles
    		  pParticleSystem:setStartColor(ccc4f(0.5, 0.5, 0.5, 1.0))

    		  pParticleSystem:setStartColorVar( ccc4f(0.5, 0.5, 0.5, 1.0))

    		  pParticleSystem:setEndColor(ccc4f(0.1, 0.1, 0.1, 0.2))
   
    		  pParticleSystem:setEndColorVar(ccc4f(0.1, 0.1, 0.1, 0.2))

    		  -- size, in pixels
    		  pParticleSystem:setEndSize(64.0)
    		  pParticleSystem:setStartSize(64.0)
    		  pParticleSystem:setEndSizeVar(0)
    		  pParticleSystem:setStartSizeVar(0)
    		
    		  -- additive
    		  pParticleSystem:setBlendAdditive(false)	   		
    	end
    end
    
    local function CreateParticleSystem()
   			local pParticleSystem = nil
   			--[[
    		* Tests:
   		    * 1: Point Particle System using 32-bit textures (PNG)
   		    * 2: Point Particle System using 16-bit textures (PNG)
    		* 3: Point Particle System using 8-bit textures (PNG)
    		* 4: Point Particle System using 4-bit textures (PVRTC)

    		* 5: Quad Particle System using 32-bit textures (PNG)
    		* 6: Quad Particle System using 16-bit textures (PNG)
    		* 7: Quad Particle System using 8-bit textures (PNG)
    		* 8: Quad Particle System using 4-bit textures (PVRTC)
    		]]--
    		pNewScene:removeChildByTag(ParticleTestParam.kTagParticleSystem, true)
    		
    		--remove the "fire.png" from the TextureCache cache. 
    		local pTexture = CCTextureCache:sharedTextureCache():addImage("Images/fire.png")
    		CCTextureCache:sharedTextureCache():removeTexture(pTexture)
    		local pParticleSystem = CCParticleSystemQuad:new()
    		if 1 == nSubtestNumber then
    		    CCTexture2D:setDefaultAlphaPixelFormat(kCCTexture2DPixelFormat_RGBA8888)
    		elseif 2 == nSubtestNumber then
    			CCTexture2D:setDefaultAlphaPixelFormat(kCCTexture2DPixelFormat_RGBA4444)
    		elseif 3 == nSubtestNumber then
    		    CCTexture2D:setDefaultAlphaPixelFormat(kCCTexture2DPixelFormat_A8)
    		elseif 4 == nSubtestNumber then 
    			CCTexture2D:setDefaultAlphaPixelFormat(kCCTexture2DPixelFormat_RGBA8888)
    		elseif 5 == nSubtestNumber then 
    		    CCTexture2D:setDefaultAlphaPixelFormat(kCCTexture2DPixelFormat_RGBA4444)
    		elseif 6 == nSubtestNumber then 
    			CCTexture2D:setDefaultAlphaPixelFormat(kCCTexture2DPixelFormat_A8)
    		else
    			pParticleSystem = nil
    			print("Shall not happen!")
    		end
    		
    		if nil ~= pParticleSystem then
    			pParticleSystem:initWithTotalParticles(nQuantityParticles)
        		pParticleSystem:setTexture(CCTextureCache:sharedTextureCache():addImage("Images/fire.png"))
    		end
    		
    		pNewScene:addChild(pParticleSystem, 0, ParticleTestParam.kTagParticleSystem)
    		
    		doTest()
    		--restore the default pixel format
    		CCTexture2D:setDefaultAlphaPixelFormat(kCCTexture2DPixelFormat_RGBA8888)  
	end
	
	local function step(t)
		  local pAtlas = tolua.cast(pNewScene:getChildByTag(ParticleTestParam.kTagLabelAtlas),"CCLabelAtlas")
    	  local pEmitter = tolua.cast(pNewScene:getChildByTag(ParticleTestParam.kTagParticleSystem),"CCParticleSystem")
    	  local strInfo = string.format("%4d",pEmitter:getParticleCount())
    	  pAtlas:setString(strInfo)
	end
	
	local function ScheduleFuncion()
		 local function OnEnterOrExit(tag)
    		  local scheduler = CCDirector:sharedDirector():getScheduler()
			    if tag == "enter" then
					ScheduleSelector = scheduler:scheduleScriptFunc(step,0,false)
				elseif tag == "exit" then
					scheduler:unscheduleScriptEntry(ScheduleSelector)
				end
    	end 
    	pNewScene:registerScriptHandler(OnEnterOrExit)
	end
    
    local function onDecrease()
		nQuantityParticles = nQuantityParticles - ParticleTestParam.kNodesIncrease
    	if nQuantityParticles  < 0 then
        	nQuantityParticles = 0
        end

    	UpdateQuantityLabel()
    	CreateParticleSystem()
    end
    
    local function onIncrease()
		nQuantityParticles = nQuantityParticles + ParticleTestParam.kNodesIncrease
    	if nQuantityParticles > ParticleTestParam.kMaxParticles then
        	nQuantityParticles = ParticleTestParam.kMaxParticles
        end

    	UpdateQuantityLabel()
    	CreateParticleSystem()
    end
    
    local function InitWithSubTest(nSubtest,nParticles)
    	nSubtestNumber = nSubtest
    	local s = CCDirector:sharedDirector():getWinSize()
    	
    	nLastRenderedCount = 0
    	nQuantityParticles = nParticles
    	
    	--"+","-" Menu
		CCMenuItemFont:setFontSize(65)
    	local pDecrease = CCMenuItemFont:create(" - ")
    	pDecrease:registerScriptTapHandler(onDecrease)
    	pDecrease:setColor(ccc3(0,200,20))
    	local pIncrease = CCMenuItemFont:create(" + ")
    	pIncrease:registerScriptTapHandler(onIncrease)
   		pIncrease:setColor(ccc3(0,200,20))
   		
   		local pMenuAddOrSub = CCMenu:create()
    	pMenuAddOrSub:addChild(pDecrease)
    	pMenuAddOrSub:addChild(pIncrease)
    	pMenuAddOrSub:alignItemsHorizontally()
    	pMenuAddOrSub:setPosition(ccp(s.width/2, s.height/2+15))
   		pNewScene:addChild(pMenuAddOrSub,1)
   		
   		local pInfoLabel = CCLabelTTF:create("0 nodes", "Marker Felt", 30)
        pInfoLabel:setColor(ccc3(0,200,20))
    	pInfoLabel:setPosition(ccp(s.width/2, s.height - 90))
    	pNewScene:addChild(pInfoLabel, 1, ParticleTestParam.kTagInfoLayer)
    	
    	--particles on stage
    	local pLabelAtlas = CCLabelAtlas:create("0000", "fps_images.png", 12, 32, string.byte('.'))
    	pNewScene:addChild(pLabelAtlas, 0, ParticleTestParam.kTagLabelAtlas)
    	pLabelAtlas:setPosition(ccp(s.width-66,50))
    	
    	--ParticleTestMenuLayer
    	local pParticleMenuLayer 	= CCLayer:create()
    	local pParticleMenu         = CCMenu:create()
    	CreatePerfomBasicLayerMenu(pParticleMenu)
		CreateBasicLayerMenuItem(pParticleMenu,true,ParticleTestParam.TEST_COUNT,nCurCase)
		pParticleMenu:setPosition(ccp(0, 0))
		pParticleMenuLayer:addChild(pParticleMenu)
		pNewScene:addChild(pParticleMenuLayer) 
		
		--Sub Tests
		CCMenuItemFont:setFontSize(40)
    	local pSubMenu = CCMenu:create()
    	local i = 1
    	for  i = 1, 6 do
  			local strNum = string.format("%d ",i)
        	local pItemFont = CCMenuItemFont:create(strNum)
        	pItemFont:registerScriptTapHandler(TestNCallback)     	
        	pSubMenu:addChild(pItemFont, i + ParticleTestParam.kSubMenuBasicZOrder)
        	if i <= 3 then
            	pItemFont:setColor(ccc3(200,20,20))
        	else
            	pItemFont:setColor(ccc3(0,200,20))
        	end
   		end
    	pSubMenu:alignItemsHorizontally()
    	pSubMenu:setPosition(ccp(s.width/2, 80))
    	pNewScene:addChild(pSubMenu, 2)
    	
    	local pLabel = CCLabelTTF:create(GetTitle(), "Arial", 40)
    	pNewScene:addChild(pLabel, 1)
    	pLabel:setPosition(ccp(s.width/2, s.height-32))
    	pLabel:setColor(ccc3(255,255,40))
    	
    	UpdateQuantityLabel()  	
    	CreateParticleSystem()
    	ScheduleFuncion()
    end
    
    function ShowCurrentTest()
    	if nil ~= pNewScene then
    		CCDirector:sharedDirector():getScheduler():unscheduleScriptEntry(ScheduleSelector)
    	end  	
		pNewScene = CCScene:create()
		InitWithSubTest(nSubtestNumber,nQuantityParticles)
		CCDirector:sharedDirector():replaceScene(pNewScene)	   	
    end
    
	
	InitWithSubTest(1,ParticleTestParam.kNodesIncrease)
	return pNewScene
end

----------------------------------
--PerformanceSpriteTest
----------------------------------
local SpriteTestParam = 
{
	kMaxNodes = 50000,
    kNodesIncrease = 250,
    TEST_COUNT = 7,
    
    kTagInfoLayer = 1,
    kTagMainLayer = 2,
    -- 50000 -- kMaxNodes
    kTagMenuLayer = 50000 + 1000,
    kInitNodes = 50,   
    kSubMenuBasicZOrder = 20,
    
    kRandMax = 32767
}

local function runSpriteTest()
	--PerformanceParticle param
    local nLastRenderedCount = 0
    local nQuantityNodes = 0
    local nSubtestNumber     = 0
    --BasiceLayer param
    local bControlMenuVisible = false
    local nMaxCases = 0
    local nCurCase  = 0
    
    local ScheduleSelector = nil
    
    --SubTest
    local pBatchNode = nil
    
    local function GetTitle()
    	local strTitle = nil
    	if 0 == nCurCase then
    		strTitle = string.format("A (%d) position",nSubtestNumber)
    	elseif 1 == nCurCase then
    		strTitle = string.format("B (%d) scale",nSubtestNumber)
    	elseif 2 == nCurCase then
    		strTitle = string.format("C (%d) scale + rot",nSubtestNumber)
    	elseif 3 == nCurCase then
    		strTitle = string.format("D (%d) 100%% out",nSubtestNumber)
    	elseif 4 == nCurCase then
    		strTitle = string.format("E (%d) 80%% out",nSubtestNumber)
    	elseif 5 == nCurCase then
    		strTitle = string.format("F (%d) actions",nSubtestNumber)
    	elseif 6 == nCurCase then
    		strTitle = string.format("G (%d) actions 80%% out",nSubtestNumber)
    	end
    	
    	return strTitle
    end
    
    local pNewScene = CCScene:create()
    
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
    
    local function UpdateNodes()
    	  if  nQuantityNodes ~= nLastRenderedCount then   		
        	 local pInfoLabel = tolua.cast(pNewScene:getChildByTag(SpriteTestParam.kTagInfoLayer), "CCLabelTTF")
        	 local strInfo = string.format("%u nodes", nQuantityNodes)
        	 pInfoLabel:setString(strInfo)
        	 nLastRenderedCount = nQuantityNodes
    	 end
    end
    
    local function PerformancePosition(pSprite)
    	local size = CCDirector:sharedDirector():getWinSize()
    	pSprite:setPosition(ccp((math.random(0,SpriteTestParam.kRandMax) % (size.width) ), (math.random(0,SpriteTestParam.kRandMax) % (size.height))))
    end
    
    local function PerformanceScale(pSprite)
    	local size = CCDirector:sharedDirector():getWinSize()
    	pSprite:setPosition(ccp((math.random(0,SpriteTestParam.kRandMax) % (size.width) ), (math.random(0,SpriteTestParam.kRandMax) % (size.height))))
    	pSprite:setScale(math.random() * 100 / 50)
	end
	
	local function PerformanceRotationScale(pSprite)
	    local size = CCDirector:sharedDirector():getWinSize()
    	pSprite:setPosition(ccp((math.random(0,SpriteTestParam.kRandMax) % (size.width) ), (math.random(0,SpriteTestParam.kRandMax) % (size.height))))
    	pSprite:setRotation(math.random() * 360)
    	pSprite:setScale(math.random() * 2)
	end
	
	local function PerformanceOut100(pSprite)
    	pSprite:setPosition(ccp( -1000, -1000))
	end
	
	local function Performanceout20(pSprite)
		  local size = CCDirector:sharedDirector():getWinSize()

    	  if math.random() < 0.2 then
        	pSprite:setPosition(ccp((math.random(0,SpriteTestParam.kRandMax) % (size.width) ), (math.random(0,SpriteTestParam.kRandMax) % (size.height))))
    	  else
        	pSprite:setPosition(ccp( -1000, -1000))
		  end
	end
	
	local function PerformanceActions(pSprite)
	    local size = CCDirector:sharedDirector():getWinSize()
    	pSprite:setPosition(ccp((math.random(0,SpriteTestParam.kRandMax) % (size.width) ), (math.random(0,SpriteTestParam.kRandMax) % (size.height))))

    	local fPeriod = 0.5 + (math.random(0,SpriteTestParam.kRandMax) % 1000) / 500.0
    	local pRot    = CCRotateBy:create(fPeriod, 360.0 * math.random() )
    	local pRot_back = pRot:reverse()
    	local arrRot = CCArray:create()
    	arrRot:addObject(pRot)
    	arrRot:addObject(pRot_back)
    	local pPermanentRotation = CCRepeatForever:create(CCSequence:create(arrRot))
    	pSprite:runAction(pPermanentRotation)

    	local fGrowDuration = 0.5 + (math.random(0,SpriteTestParam.kRandMax) % 1000) / 500.0
    	local pGrow         = CCScaleBy:create(fGrowDuration, 0.5, 0.5)
    	local arrGrow = CCArray:create()
    	arrGrow:addObject(pGrow)
    	arrGrow:addObject(pGrow:reverse())
    	local pPermanentScaleLoop = CCRepeatForever:create(CCSequence:create(arrGrow))
    	pSprite:runAction(pPermanentScaleLoop)
	end
	
	local function PerformanceActions20(pSprite)
		  local size = CCDirector:sharedDirector():getWinSize()
		  
    	  if math.random() < 0.2  then
        	pSprite:setPosition(ccp((math.random(0,SpriteTestParam.kRandMax) % (size.width) ), (math.random(0,SpriteTestParam.kRandMax) % (size.height))))
    	  else
        	pSprite:setPosition(ccp( -1000, -1000))
          end
         
    	  local pPeriod = 0.5 + (math.random(0,SpriteTestParam.kRandMax) % 1000) / 500.0
    	  local pRot    = CCRotateBy:create(pPeriod, 360.0 * math.random())
    	  local pRot_back = pRot:reverse()
    	  local arrRot = CCArray:create()
    	  arrRot:addObject(pRot)
    	  arrRot:addObject(pRot_back)
    	  local pPermanentRotation = CCRepeatForever:create(CCSequence:create(arrRot))
    	  pSprite:runAction(pPermanentRotation)


    	  local fGrowDuration = 0.5 + (math.random(0,SpriteTestParam.kRandMax)  % 1000) / 500.0
    	  local pGrow         = CCScaleBy:create(fGrowDuration, 0.5, 0.5)
          local pPermanentScaleLoop = CCRepeatForever:create(CCSequence:createWithTwoActions(pGrow, pGrow:reverse()))
    	  pSprite:runAction(pPermanentScaleLoop)
    	     	  
	end
	
	local function CreateSpriteWithTag(nTag)
        --create 
    	CCTexture2D:setDefaultAlphaPixelFormat(kCCTexture2DPixelFormat_RGBA8888)
    	local pSprite = nil
    	if 1 == nSubtestNumber then
    		pSprite = CCSprite:create("Images/grossinis_sister1.png")
            pNewScene:addChild(pSprite, 0, nTag+100)
    	elseif 2 == nSubtestNumber or 3 == nSubtestNumber then
    		pSprite = CCSprite:createWithTexture(pBatchNode:getTexture(), CCRectMake(0, 0, 52, 139))
            pBatchNode:addChild(pSprite, 0, nTag+100)
    	elseif 4 == nSubtestNumber then
    	    local nIndex = math.floor((math.random() * 1400 / 100)) + 1
            local strPath = string.format("Images/grossini_dance_%02d.png", nIndex)
            pSprite = CCSprite:create(strPath)
            pNewScene:addChild(pSprite, 0, nTag+100)
    	elseif 5 == nSubtestNumber or 6 == nSubtestNumber then
    	     local nY = 0
    	     local nX = 0
             local nR = math.floor(math.random() * 1400 / 100)
         
             nX = nR % 5
             nY = math.floor(nR / 5)

             nX = nX * 85
             nY = nY * 121
             pSprite = CCSprite:createWithTexture(pBatchNode:getTexture(), CCRectMake(nX,nY,85,121))
             pBatchNode:addChild(pSprite, 0, nTag+100)
    	elseif 7 == nSubtestNumber then
    	  	local nX = 0
    	  	local nY = 0
            local nR = math.floor(math.random() * 6400 / 100)

 			nX = nR % 8
            nY = math.floor(nR / 8)
            
            local strPath = string.format("Images/sprites_test/sprite-%d-%d.png", nX, nY)
            pSprite = CCSprite:create(strPath)
            pNewScene:addChild(pSprite, 0, nTag+100)
    	elseif 8 == nSubtestNumber or 9 == nSubtestNumber then
    	  	local nX = 0
    	  	local nY = 0
            local nR = math.floor(math.random() * 6400 / 100)

 			nX = nR % 8
            nY = math.floor(nR / 8)

            nX = nX * 32
            nY = nY * 32
            pSprite = CCSprite:createWithTexture(pBatchNode:getTexture(), CCRectMake(nX,nY,32,32))
            pBatchNode:addChild(pSprite, 0, nTag+100)
    	end
		CCTexture2D:setDefaultAlphaPixelFormat(kCCTexture2DPixelFormat_Default)
		
		return  pSprite  	
    end
    
    local function RemoveByTag(nTag)
    	if 1 == nSubtestNumber or 4 == nSubtestNumber or 7 == nSubtestNumber then
    		pNewScene:removeChildByTag(nTag + 100, true)
    	elseif 2 == nSubtestNumber or 3 == nSubtestNumber or 5 == nSubtestNumber or 6 == nSubtestNumber or 8 == nSubtestNumber or 9 == nSubtestNumber then
    		pBatchNode:removeChildAtIndex(nTag,true)
    	end
    	
    end

    local function DoTest(pSprite)
    	if 0 == nCurCase then
    		PerformancePosition(pSprite)
    	elseif 1 == nCurCase then
   			PerformanceScale(pSprite)
    	elseif 2 == nCurCase then
    		PerformanceRotationScale(pSprite)
    	elseif 3 == nCurCase then
    		PerformanceOut100(pSprite)
    	elseif 4 == nCurCase then
    		Performanceout20(pSprite)
    	elseif 5 == nCurCase then
    		PerformanceActions(pSprite)
    	elseif 6 == nCurCase then
    		PerformanceActions20(pSprite)
    	end
    end
    
    local function onDecrease()
		if nQuantityNodes <= 0 then
			return
		end
		
		local i = 0
		for i = 0 , SpriteTestParam.kNodesIncrease - 1 do
			nQuantityNodes = nQuantityNodes - 1
			RemoveByTag(nQuantityNodes)
		end
		UpdateNodes()
    end
    
    local function onIncrease()
    	if nQuantityNodes >= SpriteTestParam.kMaxNodes then
    		return
    	end
    	
    	local i = 0
    	for i = 0,SpriteTestParam.kNodesIncrease - 1 do
    		local pSprite = CreateSpriteWithTag(nQuantityNodes)
            DoTest(pSprite)
    		nQuantityNodes = nQuantityNodes + 1
    	end
		UpdateNodes()		
    end
    
    local function TestNCallback(tag,pMenuItem)
		local nIndex = pMenuItem:getZOrder() - SpriteTestParam.kSubMenuBasicZOrder
		nSubtestNumber = nIndex
		ShowCurrentTest()
    end
    
    local function InitWithSubTest(nSubTest)
    	pBatchNode = nil
    	--[[
    	* Tests:
    	* 1: 1 (32-bit) PNG sprite of 52 x 139
    	* 2: 1 (32-bit) PNG Batch Node using 1 sprite of 52 x 139
    	* 3: 1 (16-bit) PNG Batch Node using 1 sprite of 52 x 139
    	* 4: 1 (4-bit) PVRTC Batch Node using 1 sprite of 52 x 139

    	* 5: 14 (32-bit) PNG sprites of 85 x 121 each
    	* 6: 14 (32-bit) PNG Batch Node of 85 x 121 each
    	* 7: 14 (16-bit) PNG Batch Node of 85 x 121 each
    	* 8: 14 (4-bit) PVRTC Batch Node of 85 x 121 each

    	* 9: 64 (32-bit) sprites of 32 x 32 each
    	*10: 64 (32-bit) PNG Batch Node of 32 x 32 each
    	*11: 64 (16-bit) PNG Batch Node of 32 x 32 each
    	*12: 64 (4-bit) PVRTC Batch Node of 32 x 32 each
    	]]--
    	--purge textures
    	local pMgr = CCTextureCache:sharedTextureCache()
    	--[mgr removeAllTextures]
    	pMgr:removeTexture(pMgr:addImage("Images/grossinis_sister1.png"))
    	pMgr:removeTexture(pMgr:addImage("Images/grossini_dance_atlas.png"))
    	pMgr:removeTexture(pMgr:addImage("Images/spritesheet1.png"))
    	
    	if 1 == nSubTest or 4 == nSubTest or 7 == nSubTest then
    	elseif 2 == nSubTest then
    	    CCTexture2D:setDefaultAlphaPixelFormat(kCCTexture2DPixelFormat_RGBA8888)
            pBatchNode = CCSpriteBatchNode:create("Images/grossinis_sister1.png", 100)
            pNewScene:addChild(pBatchNode, 0)
    	elseif 3 == nSubTest then
    		CCTexture2D:setDefaultAlphaPixelFormat(kCCTexture2DPixelFormat_RGBA4444)
            pBatchNode = CCSpriteBatchNode:create("Images/grossinis_sister1.png", 100)
            pNewScene:addChild(pBatchNode, 0)
    	elseif 5 == nSubTest then
    	    CCTexture2D:setDefaultAlphaPixelFormat(kCCTexture2DPixelFormat_RGBA8888)
            pBatchNode = CCSpriteBatchNode:create("Images/grossini_dance_atlas.png", 100)
            pNewScene:addChild(pBatchNode, 0)
    	elseif 6 == nSubTest then
    	    CCTexture2D:setDefaultAlphaPixelFormat(kCCTexture2DPixelFormat_RGBA4444)
            pBatchNode = CCSpriteBatchNode:create("Images/grossini_dance_atlas.png", 100)
            pNewScene:addChild(pBatchNode, 0)
    	elseif 8 == nSubTest then
    	    CCTexture2D:setDefaultAlphaPixelFormat(kCCTexture2DPixelFormat_RGBA8888)
            pBatchNode = CCSpriteBatchNode:create("Images/spritesheet1.png", 100)
            pNewScene:addChild(pBatchNode, 0)
    	elseif 9 == nSubTest then
    	    CCTexture2D:setDefaultAlphaPixelFormat(kCCTexture2DPixelFormat_RGBA4444)
            pBatchNode = CCSpriteBatchNode:create("Images/spritesheet1.png", 100)
            pNewScene:addChild(pBatchNode, 0)
    	end
    	
    	if nil ~= pBatchNode then
    	    pBatchNode:retain()
    	end
    
    	CCTexture2D:setDefaultAlphaPixelFormat(kCCTexture2DPixelFormat_Default)
    end
        
    local function InitWithSpriteTest(nSubtest,nNodes)
    	nSubtestNumber = nSubtest
    	--about create subset
    	InitWithSubTest(nSubtest)
    	local s = CCDirector:sharedDirector():getWinSize()
    	
    	nLastRenderedCount = 0
    	nQuantityNodes    = 0
    	
    	--"+","-" Menu
		CCMenuItemFont:setFontSize(65)
    	local pDecrease = CCMenuItemFont:create(" - ")
   		pDecrease:registerScriptTapHandler(onDecrease)
    	pDecrease:setColor(ccc3(0,200,20))
    	local pIncrease = CCMenuItemFont:create(" + ")
	   	pIncrease:registerScriptTapHandler(onIncrease)
   		pIncrease:setColor(ccc3(0,200,20))
   		
   		local pMenuAddOrSub = CCMenu:create()
    	pMenuAddOrSub:addChild(pDecrease)
    	pMenuAddOrSub:addChild(pIncrease)
    	pMenuAddOrSub:alignItemsHorizontally()
    	pMenuAddOrSub:setPosition(ccp(s.width/2, s.height/2+15))
   		pNewScene:addChild(pMenuAddOrSub,1)
   		
   		local pInfoLabel = CCLabelTTF:create("0 nodes", "Marker Felt", 30)
        pInfoLabel:setColor(ccc3(0,200,20))
    	pInfoLabel:setPosition(ccp(s.width/2, s.height - 90))
    	pNewScene:addChild(pInfoLabel, 1, SpriteTestParam.kTagInfoLayer)
    	
    	--SpriteTestMenuLayer
    	local pSpriteMenuLayer 	= CCLayer:create()
    	local pSpriteMenu       = CCMenu:create()
    	CreatePerfomBasicLayerMenu(pSpriteMenu)
		CreateBasicLayerMenuItem(pSpriteMenu,true,SpriteTestParam.TEST_COUNT,nCurCase)
		pSpriteMenu:setPosition(ccp(0, 0))
		pSpriteMenuLayer:addChild(pSpriteMenu)
		pNewScene:addChild(pSpriteMenuLayer,1,SpriteTestParam.kTagMenuLayer) 
		
		
		--Sub Tests
		CCMenuItemFont:setFontSize(40)
    	local pSubMenu = CCMenu:create()
    	local i = 1
    	for  i = 1, 9 do
  			local strNum = string.format("%d ",i)
        	local pItemFont = CCMenuItemFont:create(strNum)
	       	pItemFont:registerScriptTapHandler(TestNCallback)     	
        	pSubMenu:addChild(pItemFont, i + SpriteTestParam.kSubMenuBasicZOrder)
 			if i <= 3 then
 				pItemFont:setColor(ccc3(200,20,20))
 			elseif i <= 6  then
 				pItemFont:setColor(ccc3(0,200,20))
 			else
 				pItemFont:setColor(ccc3(0,20,200))
 			end        	
   		end
   		
   		
    	pSubMenu:alignItemsHorizontally()
    	pSubMenu:setPosition(ccp(s.width/2, 80))
    	pNewScene:addChild(pSubMenu, 2)
    	
    	local pLabel = CCLabelTTF:create(GetTitle(), "Arial", 40)
    	pNewScene:addChild(pLabel, 1)
    	pLabel:setPosition(ccp(s.width/2, s.height-32))
    	pLabel:setColor(ccc3(255,255,40))
    	while nQuantityNodes < nNodes do
    		onIncrease()
    	end
    end
    
    function ShowCurrentTest() 	
		pNewScene = CCScene:create()
		InitWithSpriteTest(nSubtestNumber,nQuantityNodes)
		CCDirector:sharedDirector():replaceScene(pNewScene)	 
    end
    
    InitWithSpriteTest(1,SpriteTestParam.kInitNodes)
    
    return pNewScene
end

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
    	  
    	  print("RGBA 4444")
    	  CCTexture2D:setDefaultAlphaPixelFormat(kCCTexture2DPixelFormat_RGBA4444)
    	  --gettimeofday(&now, NULL)
    	  pTexture = pCache:addImage(strFileName)
    	  if nil ~= pTexture then 
            print("add sucess")
    	  else
        	print(" ERROR")
          end
    	  pCache:removeTexture(pTexture)
    	  
    	  print("RGBA 5551")
    	  CCTexture2D:setDefaultAlphaPixelFormat(kCCTexture2DPixelFormat_RGB5A1)
    	  --gettimeofday(&now, NULL)
    	  pTexture = pCache:addImage(strFileName)
    	  if nil ~= pTexture then
        	 print("add sucess")
    	  else
        	 print(" ERROR")
          end
    	  pCache:removeTexture(pTexture)
    	  
    	  print("RGB 565")
   		  CCTexture2D:setDefaultAlphaPixelFormat(kCCTexture2DPixelFormat_RGB565)
   		 -- gettimeofday(&now, NULL)    
    	 pTexture = pCache:addImage(strFileName)
    	 if nil ~= pTexture then
        	--CCLog("  ms:%f", calculateDeltaTime(&now) )
        	print("add sucess")
    	 else
       	    print(" ERROR")
       	 end
    	 pCache:removeTexture(pTexture)   	  
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
    	  
    	  print("SPRITESHEET IMAGE")
    	  print("--- PNG 1024x1024 ---")
   		  PerformTestsPNG("Images/PlanetCute-1024x1024.png")
   		  
   		  print("LANDSCAPE IMAGE")
	      print("--- PNG 1024x1024 ---")
    	  PerformTestsPNG("Images/landscape-1024x1024.png")
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
        	  fElapsedTime = 0
        	  nNumberOfTouchesB = 0
        	  nNumberOfTouchesM = 0
        	  nNumberOfTouchesE = 0
        	  nNumberOfTouchesC = 0
        	  
       		  local strInfo = string.format("%.1f %.1f %.1f %.1f",fFrameRateB, fFrameRateM, fFrameRateE, fFrameRateC)
       		  if nil ~= pClassLabel then
       		  	pClassLabel:setString(strInfo) 
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
    
    	pClassLabel = CCLabelBMFont:create("00.0", "fonts/arial16.fnt")
    	pClassLabel:setPosition(ccp(s.width/2, s.height/2))
    	pLayer:addChild(pClassLabel) 
    
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
