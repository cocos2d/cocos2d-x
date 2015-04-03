require "PerformanceTest/PerformanceSpriteTest"

local MAX_COUNT     = 6
local LINE_SPACE    = 40
local kItemTagBasic = 1000

local testsName =
{
    "PerformanceNodeChildrenTest",
    "PerformanceParticleTest",
    "PerformanceSpriteTest",
    "PerformanceTextureTest",
    "PerformanceTouchesTest",
    "PerformanceFuncRelateWithTable",
}

local s = cc.Director:getInstance():getWinSize()

--Create toMainLayr MenuItem
function CreatePerfomBasicLayerMenu(pMenu)
    if nil == pMenu then
        return
    end
    local function toMainLayer()
       local pScene = PerformanceTestMain()
       if pScene ~= nil then
           cc.Director:getInstance():replaceScene(pScene)
       end
    end 
    --Create BackMneu
    cc.MenuItemFont:setFontName("Arial")
    cc.MenuItemFont:setFontSize(24)
    local pMenuItemFont = cc.MenuItemFont:create("Back")
    pMenuItemFont:setPosition(cc.p(VisibleRect:rightBottom().x - 50, VisibleRect:rightBottom().y + 25))
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
    
    local pNewscene = cc.Scene:create()
    
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
                
                local size = cc.Director:getInstance():getWinSize()
                local item1 = cc.MenuItemImage:create(s_pPathB1, s_pPathB2)
                item1:registerScriptTapHandler(backCallback)
                pMenu:addChild(item1,kItemTagBasic)
                local item2 = cc.MenuItemImage:create(s_pPathR1, s_pPathR2)
                item2:registerScriptTapHandler(restartCallback)
                pMenu:addChild(item2,kItemTagBasic)
                local item3 = cc.MenuItemImage:create(s_pPathF1, s_pPathF2)
                pMenu:addChild(item3,kItemTagBasic) 
                item3:registerScriptTapHandler(nextCallback)
                
                local size = cc.Director:getInstance():getWinSize()
                item1:setPosition(cc.p(size.width / 2 - item2:getContentSize().width * 2, item2:getContentSize().height / 2))
                item2:setPosition(cc.p(size.width / 2, item2:getContentSize().height / 2))
                item3:setPosition(cc.p(size.width / 2 + item2:getContentSize().width * 2, item2:getContentSize().height / 2))
            end 
        end
    end
    
   local function updateQuantityLabel()
         if nQuantityOfNodes ~= nLastRenderedCount then 
 --         local pInfoLabel = pNewscene:getChildByTag(NodeChildrenTestParam.kTagInfoLayer)
            local  pInfoLabel = pNewscene:getChildByTag(NodeChildrenTestParam.kTagInfoLayer)
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
            local len = table.getn(pChildren)
            for i = 0, len - 1, 1 do
                local  child = pChildren[i + 1]
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
            local pSprites = {}
            local i = 0
            for i = 0 , nTotalToAdd - 1 do
                local pSprite = cc.Sprite:createWithTexture(pBatchNode:getTexture(), cc.rect(0,0,32,32))
                pSprites[i + 1] = pSprite
                zs[i]    = math.random(-1,1) * 50
            end
            
            for i = 0 , nTotalToAdd - 1 do
                local pChild = pSprites[i + 1]
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
             local pSprites = {}
            -- Don't include the sprite creation time as part of the profiling
            local i = 0
            for i = 0, nTotalToAdd - 1 do
                 local pSprite = cc.Sprite:createWithTexture(pBatchNode:getTexture(), cc.rect(0,0,32,32))
                 pSprites[i + 1] = pSprite
            end
            -- add them with random Z (very important!)
            for i=0, nTotalToAdd - 1  do
                local pChild = pSprites[i + 1]
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
            local pSprites = {}
            -- Don't include the sprite creation time as part of the profiling
            local i = 0
            for i = 0,nTotalToAdd - 1 do       
                local pSprite = cc.Sprite:createWithTexture(pBatchNode:getTexture(), cc.rect(0,0,32,32))
                pSprites[i + 1] = pSprite
            end

            --dd them with random Z (very important!)
            for i = 0, nTotalToAdd - 1 do 
                local pChild = pSprites[i + 1]
                pBatchNode:addChild(pChild, math.random(-1,1) * 50, NodeChildrenTestParam.kTagBase + i)             
            end

            pBatchNode:sortAllChildren()

            -- reorder them
            for i = 0, nTotalToAdd - 1 do       
                local pNode =  pSprites[i + 1]
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
        local s = cc.Director:getInstance():getWinSize()    
        --increase nodes
        if( nCurrentQuantityOfNodes < nQuantityOfNodes ) then
            local i = 0
            for i = 0,nQuantityOfNodes - nCurrentQuantityOfNodes - 1 do 
                local sprite = cc.Sprite:createWithTexture(pBatchNode:getTexture(), cc.rect(0, 0, 32, 32))
                pBatchNode:addChild(sprite)
                sprite:setPosition(cc.p( math.random() * s.width, math.random() * s.height))
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
    --  if 0 == nCurCase then
            pBatchNode = cc.SpriteBatchNode:create("Images/spritesheet1.png")
            pNewscene:addChild(pBatchNode)
        --[[
        else
            pBatchNode = cc.SpriteBatchNode:create("Images/spritesheet1.png")
            pNewscene:addChild(pBatchNode)
        end 
        ]]--
    end
    
    local function MainSceneInitWithQuantityOfNodes(nNodes)
        local s = cc.Director:getInstance():getWinSize()
            
        --Title
        local pLabel = cc.Label:createWithTTF(GetTitle(), s_arialPath, 40)
        pNewscene:addChild(pLabel, 1)
        pLabel:setAnchorPoint(cc.p(0.5, 0.5))
        pLabel:setPosition(cc.p(s.width/2, s.height-32))
        pLabel:setColor(cc.c3b(255,255,40))     
        
        if (nil ~= GetSubTitle()) and ("" ~= GetSubTitle()) then
            local pSubLabel = cc.Label:createWithTTF(GetSubTitle(), s_thonburiPath, 16)
            pNewscene:addChild(pSubLabel, 1)
            pSubLabel:setAnchorPoint(cc.p(0.5, 0.5))
            pSubLabel:setPosition(cc.p(s.width/2, s.height-80))
        end
        
        nLastRenderedCount = 0  
        nCurrentQuantityOfNodes = 0
        nQuantityOfNodes = nNodes
        
        --"+","-" Menu
        cc.MenuItemFont:setFontSize(65)
        local pDecrease = cc.MenuItemFont:create(" - ")
        pDecrease:registerScriptTapHandler(onDecrease)
        pDecrease:setColor(cc.c3b(0,200,20))
        local pIncrease = cc.MenuItemFont:create(" + ")
        pIncrease:registerScriptTapHandler(onIncrease)
        pIncrease:setColor(cc.c3b(0,200,20))
        
        local pMenuAddOrSub = cc.Menu:create()
        pMenuAddOrSub:addChild(pDecrease)
        pMenuAddOrSub:addChild(pIncrease)
        pMenuAddOrSub:alignItemsHorizontally()
        pMenuAddOrSub:setPosition(cc.p(s.width/2, s.height/2+15))
        pNewscene:addChild(pMenuAddOrSub,1)
        
        --InfoLayer
        local pInfoLabel = cc.Label:createWithTTF("0 nodes", s_markerFeltFontPath, 30)
        pInfoLabel:setColor(cc.c3b(0,200,20))
        pInfoLabel:setAnchorPoint(cc.p(0.5, 0.5))
        pInfoLabel:setPosition(cc.p(s.width/2, s.height/2-15))
        pNewscene:addChild(pInfoLabel, 1, NodeChildrenTestParam.kTagInfoLayer)
        
        --NodeChildrenMenuLayer
        local pNodeChildrenMenuLayer    = cc.Layer:create()
        local pNodeChildrenMenuMenu     = cc.Menu:create()
        CreatePerfomBasicLayerMenu(pNodeChildrenMenuMenu)
        CreateBasicLayerMenuItem(pNodeChildrenMenuMenu,true,NodeChildrenTestParam.TEST_COUNT,nCurCase)
        pNodeChildrenMenuMenu:setPosition(cc.p(0, 0))
        pNodeChildrenMenuLayer:addChild(pNodeChildrenMenuMenu)
        pNewscene:addChild(pNodeChildrenMenuLayer) 
        
        updateQuantityLabel()
        updateQuantityOfNodes() 
        
    end
    
    function ShowCurrentTest()
        if nil ~= pNewscene then
            pNewscene:unscheduleUpdate()
        end
        
        pNewscene = cc.Scene:create()
        if nil ~= pNewscene then
            SpecialInitWithQuantityOfNodes()
            MainSceneInitWithQuantityOfNodes(nQuantityOfNodes)
--          pNewscene:registerScriptHandler(onNodeEvent)
            NodeChildrenScheduleUpdate()
            cc.Director:getInstance():replaceScene(pNewscene)
        end 
    end
    
    SpecialInitWithQuantityOfNodes()
    MainSceneInitWithQuantityOfNodes(NodeChildrenTestParam.kNodesIncrease)
--  pNewscene:registerScriptHandler(onNodeEvent)
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
    
    local pNewScene = cc.Scene:create()
    
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
                
                local size = cc.Director:getInstance():getWinSize()
                local item1 = cc.MenuItemImage:create(s_pPathB1, s_pPathB2)
                item1:registerScriptTapHandler(backCallback)
                pMenu:addChild(item1,kItemTagBasic)
                local item2 = cc.MenuItemImage:create(s_pPathR1, s_pPathR2)
                item2:registerScriptTapHandler(restartCallback)
                pMenu:addChild(item2,kItemTagBasic)
                local item3 = cc.MenuItemImage:create(s_pPathF1, s_pPathF2)
                pMenu:addChild(item3,kItemTagBasic) 
                item3:registerScriptTapHandler(nextCallback)
                
                local size = cc.Director:getInstance():getWinSize()
                item1:setPosition(cc.p(size.width / 2 - item2:getContentSize().width * 2, item2:getContentSize().height / 2))
                item2:setPosition(cc.p(size.width / 2, item2:getContentSize().height / 2))
                item3:setPosition(cc.p(size.width / 2 + item2:getContentSize().width * 2, item2:getContentSize().height / 2))
            end 
        end
    end
    
    local function TestNCallback(tag,pMenuItem)
        local nIndex = pMenuItem:getLocalZOrder() - ParticleTestParam.kSubMenuBasicZOrder
        nSubtestNumber = nIndex
        ShowCurrentTest()
    end
    
    local function UpdateQuantityLabel()
        if nQuantityParticles ~= nLastRenderedCount then
            local  pInfoLabel = pNewScene:getChildByTag(ParticleTestParam.kTagInfoLayer)
            local  strInfo    = string.format("%u particles", nQuantityParticles)
            pInfoLabel:setString(strInfo)
            
            nLastRenderedCount = nQuantityParticles
        end
    end
    
    local function doTest()
        local s = cc.Director:getInstance():getWinSize()
        local pParticleSystem = pNewScene:getChildByTag(ParticleTestParam.kTagParticleSystem)
        if nil == pParticleSystem then
            return
        end
        if 0 == nCurCase then       
               --duration
               pParticleSystem:setDuration(-1)

              --gravity
              pParticleSystem:setGravity(cc.p(0,-90))

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
              pParticleSystem:setPosition(cc.p(s.width/2, 100))
              pParticleSystem:setPosVar(cc.p(s.width/2,0))

              -- life of particles
              pParticleSystem:setLife(2.0)
              pParticleSystem:setLifeVar(1)

              --emits per frame
              pParticleSystem:setEmissionRate(pParticleSystem:getTotalParticles() / pParticleSystem:getLife())
              
              --color of particles
              pParticleSystem:setStartColor(cc.c4f(0.5, 0.5, 0.5, 1.0))

              pParticleSystem:setStartColorVar( cc.c4f(0.5, 0.5, 0.5, 1.0))

              pParticleSystem:setEndColor(cc.c4f(0.1, 0.1, 0.1, 0.2))
   
              pParticleSystem:setEndColorVar(cc.c4f(0.1, 0.1, 0.1, 0.2))

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
              pParticleSystem:setGravity(cc.p(0,-90))

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
              pParticleSystem:setPosition(cc.p(s.width/2, 100))
              pParticleSystem:setPosVar(cc.p(s.width/2,0))

              -- life of particles
              pParticleSystem:setLife(2.0)
              pParticleSystem:setLifeVar(1)

              --emits per frame
              pParticleSystem:setEmissionRate(pParticleSystem:getTotalParticles() / pParticleSystem:getLife())
              
              --color of particles
              pParticleSystem:setStartColor(cc.c4f(0.5, 0.5, 0.5, 1.0))

              pParticleSystem:setStartColorVar( cc.c4f(0.5, 0.5, 0.5, 1.0))

              pParticleSystem:setEndColor(cc.c4f(0.1, 0.1, 0.1, 0.2))
   
              pParticleSystem:setEndColorVar(cc.c4f(0.1, 0.1, 0.1, 0.2))

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
              pParticleSystem:setGravity(cc.p(0,-90))

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
              pParticleSystem:setPosition(cc.p(s.width/2, 100))
              pParticleSystem:setPosVar(cc.p(s.width/2,0))

              -- life of particles
              pParticleSystem:setLife(2.0)
              pParticleSystem:setLifeVar(1)

              --emits per frame
              pParticleSystem:setEmissionRate(pParticleSystem:getTotalParticles() / pParticleSystem:getLife())
              
              --color of particles
              pParticleSystem:setStartColor(cc.c4f(0.5, 0.5, 0.5, 1.0))

              pParticleSystem:setStartColorVar( cc.c4f(0.5, 0.5, 0.5, 1.0))

              pParticleSystem:setEndColor(cc.c4f(0.1, 0.1, 0.1, 0.2))
   
              pParticleSystem:setEndColorVar(cc.c4f(0.1, 0.1, 0.1, 0.2))

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
              pParticleSystem:setGravity(cc.p(0,-90))

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
              pParticleSystem:setPosition(cc.p(s.width/2, 100))
              pParticleSystem:setPosVar(cc.p(s.width/2,0))

              -- life of particles
              pParticleSystem:setLife(2.0)
              pParticleSystem:setLifeVar(1)

              --emits per frame
              pParticleSystem:setEmissionRate(pParticleSystem:getTotalParticles() / pParticleSystem:getLife())
              
              --color of particles
              pParticleSystem:setStartColor(cc.c4f(0.5, 0.5, 0.5, 1.0))

              pParticleSystem:setStartColorVar( cc.c4f(0.5, 0.5, 0.5, 1.0))

              pParticleSystem:setEndColor(cc.c4f(0.1, 0.1, 0.1, 0.2))
   
              pParticleSystem:setEndColorVar(cc.c4f(0.1, 0.1, 0.1, 0.2))

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
            local pTexture = cc.Director:getInstance():getTextureCache():addImage("Images/fire.png")
            cc.Director:getInstance():getTextureCache():removeTexture(pTexture)
            local pParticleSystem = cc.ParticleSystemQuad:createWithTotalParticles(nQuantityParticles)
            if 1 == nSubtestNumber then
                cc.Texture2D:setDefaultAlphaPixelFormat(cc.TEXTURE2_D_PIXEL_FORMAT_RGB_A8888)
            elseif 2 == nSubtestNumber then
                cc.Texture2D:setDefaultAlphaPixelFormat(cc.TEXTURE2_D_PIXEL_FORMAT_RGB_A4444)
            elseif 3 == nSubtestNumber then
                cc.Texture2D:setDefaultAlphaPixelFormat(cc.TEXTURE2_D_PIXEL_FORMAT_A8)
            elseif 4 == nSubtestNumber then 
                cc.Texture2D:setDefaultAlphaPixelFormat(cc.TEXTURE2_D_PIXEL_FORMAT_RGB_A8888)
            elseif 5 == nSubtestNumber then 
                cc.Texture2D:setDefaultAlphaPixelFormat(cc.TEXTURE2_D_PIXEL_FORMAT_RGB_A4444)
            elseif 6 == nSubtestNumber then 
                cc.Texture2D:setDefaultAlphaPixelFormat(cc.TEXTURE2_D_PIXEL_FORMAT_A8)
            else
                pParticleSystem = nil
                print("Shall not happen!")
            end
            
            if nil ~= pParticleSystem then
                pParticleSystem:setTexture(cc.Director:getInstance():getTextureCache():addImage("Images/fire.png"))
            end
            
            pNewScene:addChild(pParticleSystem, 0, ParticleTestParam.kTagParticleSystem)
            
            doTest()
            --restore the default pixel format
            cc.Texture2D:setDefaultAlphaPixelFormat(cc.TEXTURE2_D_PIXEL_FORMAT_RGB_A8888)  
    end
    
    local function step(t)
          local pAtlas = pNewScene:getChildByTag(ParticleTestParam.kTagLabelAtlas)
          local pEmitter = pNewScene:getChildByTag(ParticleTestParam.kTagParticleSystem)
          local strInfo = string.format("%4d",pEmitter:getParticleCount())
          pAtlas:setString(strInfo)
    end
    
    local function ScheduleFuncion()
         local function OnEnterOrExit(tag)
              local scheduler = cc.Director:getInstance():getScheduler()
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
        local s = cc.Director:getInstance():getWinSize()
        
        nLastRenderedCount = 0
        nQuantityParticles = nParticles
        
        --"+","-" Menu
        cc.MenuItemFont:setFontSize(65)
        local pDecrease = cc.MenuItemFont:create(" - ")
        pDecrease:registerScriptTapHandler(onDecrease)
        pDecrease:setColor(cc.c3b(0,200,20))
        local pIncrease = cc.MenuItemFont:create(" + ")
        pIncrease:registerScriptTapHandler(onIncrease)
        pIncrease:setColor(cc.c3b(0,200,20))
        
        local pMenuAddOrSub = cc.Menu:create()
        pMenuAddOrSub:addChild(pDecrease)
        pMenuAddOrSub:addChild(pIncrease)
        pMenuAddOrSub:alignItemsHorizontally()
        pMenuAddOrSub:setPosition(cc.p(s.width/2, s.height/2+15))
        pNewScene:addChild(pMenuAddOrSub,1)
        
        local pInfoLabel = cc.Label:createWithTTF("0 nodes", s_markerFeltFontPath, 30)
        pInfoLabel:setColor(cc.c3b(0,200,20))
        pInfoLabel:setAnchorPoint(cc.p(0.5, 0.5))
        pInfoLabel:setPosition(cc.p(s.width/2, s.height - 90))
        pNewScene:addChild(pInfoLabel, 1, ParticleTestParam.kTagInfoLayer)
        
        --particles on stage
        local pLabelAtlas = cc.LabelAtlas:_create("0000", "fps_images.png", 12, 32, string.byte('.'))
        pNewScene:addChild(pLabelAtlas, 0, ParticleTestParam.kTagLabelAtlas)
        pLabelAtlas:setPosition(cc.p(s.width-66,50))
        
        --ParticleTestMenuLayer
        local pParticleMenuLayer    = cc.Layer:create()
        local pParticleMenu         = cc.Menu:create()
        CreatePerfomBasicLayerMenu(pParticleMenu)
        CreateBasicLayerMenuItem(pParticleMenu,true,ParticleTestParam.TEST_COUNT,nCurCase)
        pParticleMenu:setPosition(cc.p(0, 0))
        pParticleMenuLayer:addChild(pParticleMenu)
        pNewScene:addChild(pParticleMenuLayer) 
        
        --Sub Tests
        cc.MenuItemFont:setFontSize(40)
        local pSubMenu = cc.Menu:create()
        local i = 1
        for  i = 1, 6 do
            local strNum = string.format("%d ",i)
            local pItemFont = cc.MenuItemFont:create(strNum)
            pItemFont:registerScriptTapHandler(TestNCallback)       
            pSubMenu:addChild(pItemFont, i + ParticleTestParam.kSubMenuBasicZOrder)
            if i <= 3 then
                pItemFont:setColor(cc.c3b(200,20,20))
            else
                pItemFont:setColor(cc.c3b(0,200,20))
            end
        end
        pSubMenu:alignItemsHorizontally()
        pSubMenu:setPosition(cc.p(s.width/2, 80))
        pNewScene:addChild(pSubMenu, 2)
        
        local pLabel = cc.Label:createWithTTF(GetTitle(), s_arialPath, 40)
        pNewScene:addChild(pLabel, 1)
        pLabel:setAnchorPoint(cc.p(0.5, 0.5))
        pLabel:setPosition(cc.p(s.width/2, s.height-32))
        pLabel:setColor(cc.c3b(255,255,40))
        
        UpdateQuantityLabel()   
        CreateParticleSystem()
        ScheduleFuncion()
    end
    
    function ShowCurrentTest()
        if nil ~= pNewScene then
            cc.Director:getInstance():getScheduler():unscheduleScriptEntry(ScheduleSelector)
        end     
        pNewScene = cc.Scene:create()
        InitWithSubTest(nSubtestNumber,nQuantityParticles)
        cc.Director:getInstance():replaceScene(pNewScene)       
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
    
    local pNewScene = cc.Scene:create()
    
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
                
                local size = cc.Director:getInstance():getWinSize()
                local item1 = cc.MenuItemImage:create(s_pPathB1, s_pPathB2)
                item1:registerScriptTapHandler(backCallback)
                pMenu:addChild(item1,kItemTagBasic)
                local item2 = cc.MenuItemImage:create(s_pPathR1, s_pPathR2)
                item2:registerScriptTapHandler(restartCallback)
                pMenu:addChild(item2,kItemTagBasic)
                local item3 = cc.MenuItemImage:create(s_pPathF1, s_pPathF2)
                pMenu:addChild(item3,kItemTagBasic) 
                item3:registerScriptTapHandler(nextCallback)
                
                local size = cc.Director:getInstance():getWinSize()
                item1:setPosition(cc.p(size.width / 2 - item2:getContentSize().width * 2, item2:getContentSize().height / 2))
                item2:setPosition(cc.p(size.width / 2, item2:getContentSize().height / 2))
                item3:setPosition(cc.p(size.width / 2 + item2:getContentSize().width * 2, item2:getContentSize().height / 2))
            end 
        end
    end
    
    local function UpdateNodes()
          if  nQuantityNodes ~= nLastRenderedCount then         
             local pInfoLabel = pNewScene:getChildByTag(SpriteTestParam.kTagInfoLayer)
             local strInfo = string.format("%u nodes", nQuantityNodes)
             pInfoLabel:setString(strInfo)
             nLastRenderedCount = nQuantityNodes
         end
    end
    
    local function PerformancePosition(pSprite)
        local size = cc.Director:getInstance():getWinSize()
        pSprite:setPosition(cc.p((math.random(0,SpriteTestParam.kRandMax) % (size.width) ), (math.random(0,SpriteTestParam.kRandMax) % (size.height))))
    end
    
    local function PerformanceScale(pSprite)
        local size = cc.Director:getInstance():getWinSize()
        pSprite:setPosition(cc.p((math.random(0,SpriteTestParam.kRandMax) % (size.width) ), (math.random(0,SpriteTestParam.kRandMax) % (size.height))))
        pSprite:setScale(math.random() * 100 / 50)
    end
    
    local function PerformanceRotationScale(pSprite)
        local size = cc.Director:getInstance():getWinSize()
        pSprite:setPosition(cc.p((math.random(0,SpriteTestParam.kRandMax) % (size.width) ), (math.random(0,SpriteTestParam.kRandMax) % (size.height))))
        pSprite:setRotation(math.random() * 360)
        pSprite:setScale(math.random() * 2)
    end
    
    local function PerformanceOut100(pSprite)
        pSprite:setPosition(cc.p( -1000, -1000))
    end
    
    local function Performanceout20(pSprite)
          local size = cc.Director:getInstance():getWinSize()
          print("come in")
          if math.random() < 0.2 then
            pSprite:setPosition(cc.p((math.random(0,SpriteTestParam.kRandMax) % (size.width) ), (math.random(0,SpriteTestParam.kRandMax) % (size.height))))
          else
            pSprite:setPosition(cc.p( -1000, -1000))
          end
    end
    
    local function PerformanceActions(pSprite)
        local size = cc.Director:getInstance():getWinSize()
        pSprite:setPosition(cc.p((math.random(0,SpriteTestParam.kRandMax) % (size.width) ), (math.random(0,SpriteTestParam.kRandMax) % (size.height))))

        local fPeriod = 0.5 + (math.random(0,SpriteTestParam.kRandMax) % 1000) / 500.0
        local pRot    = cc.RotateBy:create(fPeriod, 360.0 * math.random() )
        local pRot_back = pRot:reverse()
        local pPermanentRotation = cc.RepeatForever:create(cc.Sequence:create(pRot, pRot_back))
        pSprite:runAction(pPermanentRotation)

        local fGrowDuration = 0.5 + (math.random(0,SpriteTestParam.kRandMax) % 1000) / 500.0
        local pGrow         = cc.ScaleBy:create(fGrowDuration, 0.5, 0.5)
        local pPermanentScaleLoop = cc.RepeatForever:create(cc.Sequence:create(pGrow, pGrow:reverse()))
        pSprite:runAction(pPermanentScaleLoop)
    end
    
    local function PerformanceActions20(pSprite)
          local size = cc.Director:getInstance():getWinSize()
          
          if math.random() < 0.2  then
            pSprite:setPosition(cc.p((math.random(0,SpriteTestParam.kRandMax) % (size.width) ), (math.random(0,SpriteTestParam.kRandMax) % (size.height))))
          else
            pSprite:setPosition(cc.p( -1000, -1000))
          end
         
          local pPeriod = 0.5 + (math.random(0,SpriteTestParam.kRandMax) % 1000) / 500.0
          local pRot    = cc.RotateBy:create(pPeriod, 360.0 * math.random())
          local pRot_back = pRot:reverse()
          local pPermanentRotation = cc.RepeatForever:create(cc.Sequence:create(pRot, pRot_back))
          pSprite:runAction(pPermanentRotation)


          local fGrowDuration = 0.5 + (math.random(0,SpriteTestParam.kRandMax)  % 1000) / 500.0
          local pGrow         = cc.ScaleBy:create(fGrowDuration, 0.5, 0.5)
          local pPermanentScaleLoop = cc.RepeatForever:create(cc.Sequence:create(pGrow, pGrow:reverse()))
          pSprite:runAction(pPermanentScaleLoop)
                  
    end
    
    local function CreateSpriteWithTag(nTag)
        --create 
        cc.Texture2D:setDefaultAlphaPixelFormat(cc.TEXTURE2_D_PIXEL_FORMAT_RGB_A8888)
        local pSprite = nil
        if 1 == nSubtestNumber then
            pSprite = cc.Sprite:create("Images/grossinis_sister1.png")
            pNewScene:addChild(pSprite, 0, nTag+100)
        elseif 2 == nSubtestNumber or 3 == nSubtestNumber then
            pSprite = cc.Sprite:createWithTexture(pBatchNode:getTexture(), cc.rect(0, 0, 52, 139))
            pBatchNode:addChild(pSprite, 0, nTag+100)
        elseif 4 == nSubtestNumber then
            local nIndex = math.floor((math.random() * 1400 / 100)) + 1
            local strPath = string.format("Images/grossini_dance_%02d.png", nIndex)
            pSprite = cc.Sprite:create(strPath)
            pNewScene:addChild(pSprite, 0, nTag+100)
        elseif 5 == nSubtestNumber or 6 == nSubtestNumber then
             local nY = 0
             local nX = 0
             local nR = math.floor(math.random() * 1400 / 100)
         
             nX = nR % 5
             nY = math.floor(nR / 5)

             nX = nX * 85
             nY = nY * 121
             pSprite = cc.Sprite:createWithTexture(pBatchNode:getTexture(), cc.rect(nX,nY,85,121))
             pBatchNode:addChild(pSprite, 0, nTag+100)
        elseif 7 == nSubtestNumber then
            local nX = 0
            local nY = 0
            local nR = math.floor(math.random() * 6400 / 100)

            nX = nR % 8
            nY = math.floor(nR / 8)
            
            local strPath = string.format("Images/sprites_test/sprite-%d-%d.png", nX, nY)
            pSprite = cc.Sprite:create(strPath)
            pNewScene:addChild(pSprite, 0, nTag+100)
        elseif 8 == nSubtestNumber or 9 == nSubtestNumber then
            local nX = 0
            local nY = 0
            local nR = math.floor(math.random() * 6400 / 100)

            nX = nR % 8
            nY = math.floor(nR / 8)

            nX = nX * 32
            nY = nY * 32
            pSprite = cc.Sprite:createWithTexture(pBatchNode:getTexture(), cc.rect(nX,nY,32,32))
            pBatchNode:addChild(pSprite, 0, nTag+100)
        end
        cc.Texture2D:setDefaultAlphaPixelFormat(cc.TEXTURE2_D_PIXEL_FORMAT_DEFAULT)
        
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
        local nIndex = pMenuItem:getLocalZOrder() - SpriteTestParam.kSubMenuBasicZOrder
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
        local pMgr = cc.Director:getInstance():getTextureCache()
        --[mgr removeAllTextures]
        pMgr:removeTexture(pMgr:addImage("Images/grossinis_sister1.png"))
        pMgr:removeTexture(pMgr:addImage("Images/grossini_dance_atlas.png"))
        pMgr:removeTexture(pMgr:addImage("Images/spritesheet1.png"))
        
        if 1 == nSubTest or 4 == nSubTest or 7 == nSubTest then
        elseif 2 == nSubTest then
            cc.Texture2D:setDefaultAlphaPixelFormat(cc.TEXTURE2_D_PIXEL_FORMAT_RGB_A8888)
            pBatchNode = cc.SpriteBatchNode:create("Images/grossinis_sister1.png", 100)
            pNewScene:addChild(pBatchNode, 0)
        elseif 3 == nSubTest then
            cc.Texture2D:setDefaultAlphaPixelFormat(cc.TEXTURE2_D_PIXEL_FORMAT_RGB_A4444)
            pBatchNode = cc.SpriteBatchNode:create("Images/grossinis_sister1.png", 100)
            pNewScene:addChild(pBatchNode, 0)
        elseif 5 == nSubTest then
            cc.Texture2D:setDefaultAlphaPixelFormat(cc.TEXTURE2_D_PIXEL_FORMAT_RGB_A8888)
            pBatchNode = cc.SpriteBatchNode:create("Images/grossini_dance_atlas.png", 100)
            pNewScene:addChild(pBatchNode, 0)
        elseif 6 == nSubTest then
            cc.Texture2D:setDefaultAlphaPixelFormat(cc.TEXTURE2_D_PIXEL_FORMAT_RGB_A4444)
            pBatchNode = cc.SpriteBatchNode:create("Images/grossini_dance_atlas.png", 100)
            pNewScene:addChild(pBatchNode, 0)
        elseif 8 == nSubTest then
            cc.Texture2D:setDefaultAlphaPixelFormat(cc.TEXTURE2_D_PIXEL_FORMAT_RGB_A8888)
            pBatchNode = cc.SpriteBatchNode:create("Images/spritesheet1.png", 100)
            pNewScene:addChild(pBatchNode, 0)
        elseif 9 == nSubTest then
            cc.Texture2D:setDefaultAlphaPixelFormat(cc.TEXTURE2_D_PIXEL_FORMAT_RGB_A4444)
            pBatchNode = cc.SpriteBatchNode:create("Images/spritesheet1.png", 100)
            pNewScene:addChild(pBatchNode, 0)
        end
        
        if nil ~= pBatchNode then
            pBatchNode:retain()
        end
    
        cc.Texture2D:setDefaultAlphaPixelFormat(cc.TEXTURE2_D_PIXEL_FORMAT_DEFAULT)
    end
        
    local function InitWithSpriteTest(nSubtest,nNodes)
        nSubtestNumber = nSubtest
        --about create subset
        InitWithSubTest(nSubtest)
        local s = cc.Director:getInstance():getWinSize()
        
        nLastRenderedCount = 0
        nQuantityNodes    = 0
        
        --"+","-" Menu
        cc.MenuItemFont:setFontSize(65)
        local pDecrease = cc.MenuItemFont:create(" - ")
        pDecrease:registerScriptTapHandler(onDecrease)
        pDecrease:setColor(cc.c3b(0,200,20))
        local pIncrease = cc.MenuItemFont:create(" + ")
        pIncrease:registerScriptTapHandler(onIncrease)
        pIncrease:setColor(cc.c3b(0,200,20))
        
        local pMenuAddOrSub = cc.Menu:create()
        pMenuAddOrSub:addChild(pDecrease)
        pMenuAddOrSub:addChild(pIncrease)
        pMenuAddOrSub:alignItemsHorizontally()
        pMenuAddOrSub:setPosition(cc.p(s.width/2, s.height/2+15))
        pNewScene:addChild(pMenuAddOrSub,1)
        
        local pInfoLabel = cc.Label:createWithTTF("0 nodes", s_markerFeltFontPath, 30)
        pInfoLabel:setColor(cc.c3b(0,200,20))
        pInfoLabel:setAnchorPoint(cc.p(0.5, 0.5))
        pInfoLabel:setPosition(cc.p(s.width/2, s.height - 90))
        pNewScene:addChild(pInfoLabel, 1, SpriteTestParam.kTagInfoLayer)
        
        --SpriteTestMenuLayer
        local pSpriteMenuLayer  = cc.Layer:create()
        local pSpriteMenu       = cc.Menu:create()
        CreatePerfomBasicLayerMenu(pSpriteMenu)
        CreateBasicLayerMenuItem(pSpriteMenu,true,SpriteTestParam.TEST_COUNT,nCurCase)
        pSpriteMenu:setPosition(cc.p(0, 0))
        pSpriteMenuLayer:addChild(pSpriteMenu)
        pNewScene:addChild(pSpriteMenuLayer,1,SpriteTestParam.kTagMenuLayer) 
        
        
        --Sub Tests
        cc.MenuItemFont:setFontSize(40)
        local pSubMenu = cc.Menu:create()
        local i = 1
        for  i = 1, 9 do
            local strNum = string.format("%d ",i)
            local pItemFont = cc.MenuItemFont:create(strNum)
            pItemFont:registerScriptTapHandler(TestNCallback)       
            pSubMenu:addChild(pItemFont, i + SpriteTestParam.kSubMenuBasicZOrder)
            if i <= 3 then
                pItemFont:setColor(cc.c3b(200,20,20))
            elseif i <= 6  then
                pItemFont:setColor(cc.c3b(0,200,20))
            else
                pItemFont:setColor(cc.c3b(0,20,200))
            end         
        end
        
        
        pSubMenu:alignItemsHorizontally()
        pSubMenu:setPosition(cc.p(s.width/2, 80))
        pNewScene:addChild(pSubMenu, 2)
        
        local pLabel = cc.Label:createWithTTF(GetTitle(), s_arialPath, 40)
        pNewScene:addChild(pLabel, 1)
        pLabel:setAnchorPoint(cc.p(0.5, 0.5))
        pLabel:setPosition(cc.p(s.width/2, s.height-32))
        pLabel:setColor(cc.c3b(255,255,40))
        while nQuantityNodes < nNodes do
            onIncrease()
        end
    end
    
    function ShowCurrentTest()  
        pNewScene = cc.Scene:create()
        InitWithSpriteTest(nSubtestNumber,nQuantityNodes)
        cc.Director:getInstance():replaceScene(pNewScene)    
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
    local pNewscene = cc.Scene:create()
    local pLayer    = cc.Layer:create()
    local s         = cc.Director:getInstance():getWinSize()
    
    local function PerformTestsPNG(strFileName)
          local time
          local pTexture = nil
          local pCache = cc.Director:getInstance():getTextureCache()

          local pDefaultFormat = cc.Texture2D:getDefaultAlphaPixelFormat();

          print("RGBA 8888")
          cc.Texture2D:setDefaultAlphaPixelFormat(cc.TEXTURE2_D_PIXEL_FORMAT_RGB_A8888)
          pTexture = pCache:addImage(strFileName)         
          if nil ~= pTexture then
            --os.time()--get secs,not micr sec
            print("add sucess")
          else
            print(" ERROR")
          end
          pCache:removeTexture(pTexture)
          
          print("RGBA 4444")
          cc.Texture2D:setDefaultAlphaPixelFormat(cc.TEXTURE2_D_PIXEL_FORMAT_RGB_A4444)
          --gettimeofday(&now, NULL)
          pTexture = pCache:addImage(strFileName)
          if nil ~= pTexture then 
            print("add sucess")
          else
            print(" ERROR")
          end
          pCache:removeTexture(pTexture)
          
          print("RGBA 5551")
          cc.Texture2D:setDefaultAlphaPixelFormat(cc.TEXTURE2_D_PIXEL_FORMAT_RGB5_A1)
          --gettimeofday(&now, NULL)
          pTexture = pCache:addImage(strFileName)
          if nil ~= pTexture then
             print("add sucess")
          else
             print(" ERROR")
          end
          pCache:removeTexture(pTexture)
          
          print("RGB 565")
          cc.Texture2D:setDefaultAlphaPixelFormat(cc.TEXTURE2_D_PIXEL_FORMAT_RG_B565)
         -- gettimeofday(&now, NULL)    
         pTexture = pCache:addImage(strFileName)
         if nil ~= pTexture then
            --log("  ms:%f", calculateDeltaTime(&now) )
            print("add sucess")
         else
            print(" ERROR")
         end
         pCache:removeTexture(pTexture)       

         cc.Texture2D:setDefaultAlphaPixelFormat(pDefaultFormat)
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
        local pLabel = cc.Label:createWithTTF(GetTitle(), s_arialPath, 40)
        pLayer:addChild(pLabel, 1)
        pLabel:setAnchorPoint(cc.p(0.5, 0.5))
        pLabel:setPosition(cc.p(s.width/2, s.height-32))
        pLabel:setColor(cc.c3b(255,255,40))

        --Subtitle
        local pSubLabel = cc.Label:createWithTTF(GetSubtitle(), s_thonburiPath, 16)
        pLayer:addChild(pSubLabel, 1)
        pSubLabel:setAnchorPoint(cc.p(0.5, 0.5))
        pSubLabel:setPosition(cc.p(s.width/2, s.height-80))
        
        --menu
        local pMenu = cc.Menu:create()
        CreatePerfomBasicLayerMenu(pMenu)
        pMenu:setPosition(cc.p(0, 0))
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
    
    local  s = cc.Director:getInstance():getWinSize()
    local  pNewscene = cc.Scene:create()
    local  pLayer    = cc.Layer:create()
    
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
                
                local size = cc.Director:getInstance():getWinSize()
                local item1 = cc.MenuItemImage:create(s_pPathB1, s_pPathB2)
                item1:registerScriptTapHandler(backCallback)
                pMenu:addChild(item1,kItemTagBasic)
                local item2 = cc.MenuItemImage:create(s_pPathR1, s_pPathR2)
                item2:registerScriptTapHandler(restartCallback)
                pMenu:addChild(item2,kItemTagBasic)
                local item3 = cc.MenuItemImage:create(s_pPathF1, s_pPathF2)
                pMenu:addChild(item3,kItemTagBasic) 
                item3:registerScriptTapHandler(nextCallback)
                
                local size = cc.Director:getInstance():getWinSize()
                item1:setPosition(cc.p(size.width / 2 - item2:getContentSize().width * 2, item2:getContentSize().height / 2))
                item2:setPosition(cc.p(size.width / 2, item2:getContentSize().height / 2))
                item3:setPosition(cc.p(size.width / 2 + item2:getContentSize().width * 2, item2:getContentSize().height / 2))
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
    local function onTouchEnded(touch, event)
        nNumberOfTouchesE = nNumberOfTouchesE + 1
    end

    local function onTouchBegan(touch, event)
        nNumberOfTouchesB = nNumberOfTouchesB + 1
    end

    local function onTouchMoved(touch, event)
        nNumberOfTouchesM = nNumberOfTouchesM + 1
    end

    local function onTouchCancelled(touch, event)
        nNumberOfTouchesC = nNumberOfTouchesC + 1
    end


    local function onTouchesEnded(touches, event)
        nNumberOfTouchesE  = nNumberOfTouchesE + table.getn(touches)
    end

    local function onTouchesBegan(touches, event)
        nNumberOfTouchesB  = nNumberOfTouchesB + table.getn(touches)
    end

    local function onTouchesMoved(touches, event)
        nNumberOfTouchesM = nNumberOfTouchesM + table.getn(touches)
    end

    local function onTouchesCancelled(touches, event)
        nNumberOfTouchesC= nNumberOfTouchesC + table.getn(touches)
    end
    
    local function InitLayer()
        --menu
        local pTouchesTestMenu     = cc.Menu:create()
        CreatePerfomBasicLayerMenu(pTouchesTestMenu)
        CreateBasicLayerMenuItem(pTouchesTestMenu,true,TouchesTestParam.TEST_COUNT,nCurCase)
        pTouchesTestMenu:setPosition(cc.p(0, 0))
        pLayer:addChild(pTouchesTestMenu)
        
        --Title
        local pLabel = cc.Label:createWithTTF(GetTitle(), s_arialPath, 40)
        pLayer:addChild(pLabel, 1)
        pLabel:setAnchorPoint(cc.p(0.5, 0.5))
        pLabel:setPosition(cc.p(s.width/2, s.height-32))
        pLabel:setColor(cc.c3b(255,255,40)) 
        
        pLayer:scheduleUpdateWithPriorityLua(update,0)  
    
        pClassLabel = cc.Label:createWithBMFont("fonts/arial16.fnt", "00.0")
        pClassLabel:setAnchorPoint(cc.p(0.5, 0.5))
        pClassLabel:setPosition(cc.p(s.width/2, s.height/2))
        pLayer:addChild(pClassLabel) 
    
        fElapsedTime = 0.0
        nNumberOfTouchesB = 0
        nNumberOfTouchesM = 0
        nNumberOfTouchesE = 0
        nNumberOfTouchesC = 0   

        if 0 == nCurCase then
            local listener = cc.EventListenerTouchOneByOne:create()
            listener:registerScriptHandler(onTouchBegan,cc.Handler.EVENT_TOUCH_BEGAN )
            listener:registerScriptHandler(onTouchMoved,cc.Handler.EVENT_TOUCH_MOVED )
            listener:registerScriptHandler(onTouchEnded,cc.Handler.EVENT_TOUCH_ENDED )
            listener:registerScriptHandler(onTouchCancelled,cc.Handler.EVENT_TOUCH_CANCELLED )
            local eventDispatcher = pLayer:getEventDispatcher()
            eventDispatcher:addEventListenerWithSceneGraphPriority(listener, pLayer)
        elseif 1 == nCurCase then
            local listener = cc.EventListenerTouchAllAtOnce:create()
            listener:registerScriptHandler(onTouchesBegan,cc.Handler.EVENT_TOUCHES_BEGAN )
            listener:registerScriptHandler(onTouchesMoved,cc.Handler.EVENT_TOUCHES_MOVED )
            listener:registerScriptHandler(onTouchesEnded,cc.Handler.EVENT_TOUCHES_ENDED )
            listener:registerScriptHandler(onTouchesCancelled,cc.Handler.EVENT_TOUCHES_CANCELLED )
            local eventDispatcher = pLayer:getEventDispatcher()
            eventDispatcher:addEventListenerWithSceneGraphPriority(listener, pLayer)
        end
    end
    
    function ShowCurrentTest()
        if nil ~= pLayer then
            pLayer:unscheduleUpdate()
        end
        
        pNewscene = cc.Scene:create()
        
        if nil ~= pNewscene then
            pLayer = cc.Layer:create()
            InitLayer()
            pNewscene:addChild(pLayer)
            cc.Director:getInstance():replaceScene(pNewscene)
        end 
    end

    InitLayer()
    pNewscene:addChild(pLayer)
    return pNewscene
end

local function runFuncRelateWithTable()
    -- body
    local newscene  = cc.Scene:create()
    local layer     = cc.Layer:create()
    local s         = cc.Director:getInstance():getWinSize()
    local scheduler = cc.Director:getInstance():getScheduler()
    local scheduleEntryID = 0
    local quantityOfNodes = 10000
    local socket = require("socket")
    local maxTime = 0.0
    local minTime = 99999
    local averageTime1 = 0.0
    local averageTime2 = 0.0
    local totalTime    = 0.0
    local numberOfCalls = 0

    local function GetTitle()
        return "Func Releated Table Performance Test"
    end
    
    local function GetSubtitle()
        return "See console for results"
    end

    local function initVar()
        maxTime = 0.0
        minTime = 99999
        averageTime1 = 0.0
        averageTime2 = 0.0
        totalTime    = 0.0
        numberOfCalls = 0
    end

    --Title
    local title = cc.Label:createWithTTF(GetTitle(), s_arialPath, 28)
    layer:addChild(title, 1)
    title:setAnchorPoint(cc.p(0.5, 0.5))
    title:setPosition(cc.p(s.width/2, s.height-32))
    title:setColor(cc.c3b(255,255,40)) 
    --Subtitle
    local subTitle = cc.Label:createWithTTF(GetSubtitle(), s_thonburiPath, 16)
    layer:addChild(subTitle, 1)
    subTitle:setAnchorPoint(cc.p(0.5, 0.5))
    subTitle:setPosition(cc.p(s.width/2, s.height-80))

    --"+","-" Menu
    local function onDecrease()
        quantityOfNodes = quantityOfNodes - 100
        if quantityOfNodes == 0 then
            quantityOfNodes = 100
        end
        local  numLabel = layer:getChildByTag(NodeChildrenTestParam.kTagInfoLayer)
        local  strNum = string.format("%d", quantityOfNodes)
        numLabel:setString(strNum)    
    end

    local function onIncrease()
        quantityOfNodes = quantityOfNodes + 100
        local  numLabel = layer:getChildByTag(NodeChildrenTestParam.kTagInfoLayer)
        local  strNum = string.format("%d", quantityOfNodes)
        numLabel:setString(strNum)  
    end

    cc.MenuItemFont:setFontSize(65)
    local decrease = cc.MenuItemFont:create(" - ")
    decrease:registerScriptTapHandler(onDecrease)
    decrease:setColor(cc.c3b(0,200,20))
    local increase = cc.MenuItemFont:create(" + ")
    increase:registerScriptTapHandler(onIncrease)
    increase:setColor(cc.c3b(0,200,20))
        
    local menuAddOrSub = cc.Menu:create()
    menuAddOrSub:addChild(decrease)
    menuAddOrSub:addChild(increase)
    menuAddOrSub:alignItemsHorizontally()
    menuAddOrSub:setPosition(cc.p(s.width/2, s.height/2+15))
    layer:addChild(menuAddOrSub,1)

    --num
    local numLabel = cc.Label:createWithTTF("10000", s_markerFeltFontPath, 30)
    numLabel:setColor(cc.c3b(0,200,20))
    numLabel:setAnchorPoint(cc.p(0.5, 0.5))
    numLabel:setPosition(cc.p(s.width/2, s.height/2-15))
    layer:addChild(numLabel, 1, NodeChildrenTestParam.kTagInfoLayer)

    --setPosition,getPosition,Point
    cc.MenuItemFont:setFontSize(18)
    local setPositionItem = cc.MenuItemFont:create("setPosition")
    local getPositionItem = cc.MenuItemFont:create("getPosition")
    local getAnchorPointItem = cc.MenuItemFont:create("getAnchorPoint")
    local pointItem       = cc.MenuItemFont:create("object")
    local funcToggleItem  = cc.MenuItemToggle:create(setPositionItem)
    funcToggleItem:addSubItem(getPositionItem)
    funcToggleItem:addSubItem(getAnchorPointItem)
    funcToggleItem:addSubItem(pointItem)
    funcToggleItem:setAnchorPoint(cc.p(0.0, 0.5))
    funcToggleItem:setPosition(cc.p(VisibleRect:left()))
    local funcMenu = cc.Menu:create(funcToggleItem)
    funcMenu:setPosition(cc.p(0, 0))
    layer:addChild(funcMenu)

    local testNode = cc.Node:create()
    layer:addChild(testNode)

    local function step(dt)
        print(string.format("push num: %d, avg1:%f, avg2:%f,min:%f, max:%f, total: %f, calls: %d",quantityOfNodes, averageTime1, averageTime2, minTime, maxTime, totalTime, numberOfCalls))
    end

    local function profileEnd(startTime)
        local duration = socket.gettime() - startTime
        totalTime = totalTime + duration
        averageTime1 = (averageTime1 + duration) / 2
        averageTime2 = totalTime / numberOfCalls

        if maxTime < duration then
            maxTime = duration
        end

        if minTime > duration then
            minTime = duration
        end
    end

    local function callSetPosition()
        numberOfCalls = numberOfCalls + 1
        local startTime = socket.gettime()
        for i=1,quantityOfNodes do
            testNode:setPosition(cc.p(1,2))
        end
        profileEnd(startTime)
    end

    local function callGetPosition()
        numberOfCalls = numberOfCalls + 1
        local startTime = socket.gettime()
        for i=1,quantityOfNodes do
            local x,y = testNode:getPosition()
        end
        profileEnd(startTime)
    end

    local function callGetAnchorPoint()
        numberOfCalls = numberOfCalls + 1
        local startTime = socket.gettime()
        for i=1,quantityOfNodes do
            local anchorPoint = testNode:getAnchorPoint()
        end
        profileEnd(startTime)
    end

    local function callTableObject()
        numberOfCalls = numberOfCalls + 1
        local startTime = socket.gettime()
        for i=1,quantityOfNodes do
            local pt = cc.p(1,2)
        end
        profileEnd(startTime)
    end

    local function update(dt)

        local funcSelected = funcToggleItem:getSelectedIndex()
        if 0 == funcSelected then
            callSetPosition()
        elseif 1 == funcSelected then
            callGetPosition()
        elseif 2 == funcSelected then
            callGetAnchorPoint()
        elseif 3 == funcSelected then
            callTableObject()
        end
    end

    local function onNodeEvent(tag)
        if tag == "exit" then
            layer:unscheduleUpdate()
            scheduler:unscheduleScriptEntry(scheduleEntryID)
        end
    end

    layer:registerScriptHandler(onNodeEvent)


    local function startCallback()
        initVar()
        decrease:setEnabled(false)
        increase:setEnabled(false)
        funcToggleItem:setEnabled(false)
        layer:unscheduleUpdate()
        layer:scheduleUpdateWithPriorityLua(update, 0)
        scheduler:unscheduleScriptEntry(scheduleEntryID)
        scheduleEntryID = scheduler:scheduleScriptFunc(step,2,false)
    end

    local function stopCallback()
        decrease:setEnabled(true)
        increase:setEnabled(true)
        funcToggleItem:setEnabled(true)
        layer:unscheduleUpdate()
        scheduler:unscheduleScriptEntry(scheduleEntryID)
    end
    local startItem = cc.MenuItemFont:create("start")
    startItem:registerScriptTapHandler(startCallback)
    local stopItem  = cc.MenuItemFont:create("stop")
    stopItem:registerScriptTapHandler(stopCallback)
    local startAndStop = cc.Menu:create(startItem,stopItem)
    startAndStop:alignItemsVertically()
    startAndStop:setPosition(VisibleRect:right().x - 50, VisibleRect:right().y)
    layer:addChild(startAndStop)

    --back menu
    local menu = cc.Menu:create()
    CreatePerfomBasicLayerMenu(menu)
    menu:setPosition(cc.p(0, 0))
    layer:addChild(menu)

    newscene:addChild(layer)
    return newscene
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
    runTouchesTest,
    runFuncRelateWithTable,    
}

local function CreatePerformancesTestScene(nPerformanceNo)
  local pNewscene = CreatePerformancesTestTable[nPerformanceNo]()
  return pNewscene
end
local function menuCallback(tag, pMenuItem)
    local scene = nil
    local nIdx = pMenuItem:getLocalZOrder() - kItemTagBasic
    local PerformanceTestScene = CreatePerformancesTestScene(nIdx)
    if nil ~= PerformanceTestScene then
         cc.Director:getInstance():replaceScene(PerformanceTestScene)
    end
end

local function PerformanceMainLayer()
    local layer = cc.Layer:create()

    local menu = cc.Menu:create()
    menu:setPosition(cc.p(0, 0))
    cc.MenuItemFont:setFontName("Arial")
    cc.MenuItemFont:setFontSize(24)
    for i = 1, MAX_COUNT do
        local item = cc.MenuItemFont:create(testsName[i])
        item:registerScriptTapHandler(menuCallback)
        item:setPosition(s.width / 2, s.height - i * LINE_SPACE)
        menu:addChild(item, kItemTagBasic + i)
        if i == MAX_COUNT then
            local targetPlatform = cc.Application:getInstance():getTargetPlatform()
            if (cc.PLATFORM_OS_IPHONE ~= targetPlatform) and (cc.PLATFORM_OS_IPAD ~= targetPlatform) and 
               (cc.PLATFORM_OS_ANDROID ~= targetPlatform) and (cc.PLATFORM_OS_WINDOWS ~= targetPlatform) and
               (cc.PLATFORM_OS_MAC ~= targetPlatform) then
               item:setEnabled(false)
            end
        end
    end

    layer:addChild(menu)

    return layer
end

-------------------------------------
--  Performance Test
-------------------------------------
function PerformanceTestMain()
    local scene = cc.Scene:create()

    scene:addChild(PerformanceMainLayer())
    scene:addChild(CreateBackMenuItem())

    return scene
end
