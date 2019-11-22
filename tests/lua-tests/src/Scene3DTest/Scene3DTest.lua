
local GAME_LAYER = 
{
    LAYER_SKYBOX = 1,
    LAYER_GAME   = 2,
    LAYER_UI     = 3,
    LAYER_ACTOR  = 4,
    LAYER_ZOOM   = 5,
    LAYER_OSD    = 6,
    LAYER_COUNT  = 7,
}

local s_CF  = 
{
    cc.CameraFlag.DEFAULT,
    cc.CameraFlag.USER1,
    cc.CameraFlag.USER2,
    cc.CameraFlag.USER3,
    cc.CameraFlag.USER4,
    cc.CameraFlag.USER5,
}

local s_CM =
{
    s_CF[1],
    s_CF[2],
    s_CF[3],
    s_CF[4],
    s_CF[5],
    s_CF[6],
}


----------------------------------------
----TerrainWalkThru
----------------------------------------

local PLAER_STATE =
{
    LEFT     = 0,
    RIGHT    = 1,
    IDLE     = 2,
    FORWARD  = 3, 
    BACKWARD = 4,
}

local PLAYER_HEIGHT = 0

local camera_offset = cc.vec3(0, 45, 60)

local Player = class("Player", function(file, cam, terrain)
    local sprite = cc.Sprite3D:create(file)
    if nil ~= sprite then
        sprite._headingAngle = 0
        sprite._playerState = PLAER_STATE.IDLE
        sprite._cam = cam
        sprite._terrain = terrain
    end
    return sprite
end)

function Player:ctor()
    -- body
    self:init()      
end

function Player:init()
    self._headingAxis = cc.vec3(0.0, 0.0, 0.0)
    self:scheduleUpdateWithPriorityLua(function(dt)
        local curPos = self:getPosition3D()
        if self._playerState == PLAER_STATE.IDLE then

        elseif self._playerState == PLAER_STATE.FORWARD then
            local newFaceDir = cc.vec3sub(self._targetPos, curPos)
            newFaceDir.y = 0.0
            newFaceDir = cc.vec3normalize(newFaceDir)
            local offset = cc.vec3mul(newFaceDir, 25.0 * dt)
            curPos = cc.vec3add(curPos, offset)
            self:setPosition3D(curPos)
        elseif self._playerState ==  PLAER_STATE.BACKWARD then
            
            local transform   = self:getNodeToWorldTransform()
            local forward_vec = cc.vec3(-transform[9], -transform[10], -transform[11])
            forward_vec = cc.vec3normalize(forward_vec)
            self:setPosition3D(cc.vec3sub(curPos, cc.vec3mul(forward_vec, 15 * dt)))
        elseif self._playerState == PLAER_STATE.LEFT then
            player:setRotation3D(cc.vec3(curPos.x, curPos.y + 25 * dt, curPos.z))
        elseif self._playerState == PLAER_STATE.RIGHT then
            player:setRotation3D(cc.vec3(curPos.x, curPos.y - 25 * dt, curPos.z))
        end

        local normal = cc.vec3(0.0, 0.0, 0.0)
        local player_h, normal = self._terrain:getHeight(self:getPositionX(), self:getPositionZ(), normal)
        self:setPositionY(player_h + PLAYER_HEIGHT)

        --need to scriptfile
        local q2 = cc.quaternion_createFromAxisAngle(cc.vec3(0, 1, 0), -math.pi)
        local headingQ = cc.quaternion_createFromAxisAngle(self._headingAxis, self._headingAngle)
        local x = headingQ.w * q2.x + headingQ.x * q2.w + headingQ.y * q2.z - headingQ.z * q2.y
        local y = headingQ.w * q2.y - headingQ.x * q2.z + headingQ.y * q2.w + headingQ.z * q2.x
        local z = headingQ.w * q2.z + headingQ.x * q2.y - headingQ.y * q2.x + headingQ.z * q2.w
        local w = headingQ.w * q2.w - headingQ.x * q2.x - headingQ.y * q2.y - headingQ.z * q2.z
        headingQ = cc.quaternion(x, y, z, w)
        self:setRotationQuat(headingQ)

        local vec_offset = cc.vec4(camera_offset.x, camera_offset.y, camera_offset.z, 1)
        local transform  = self:getNodeToWorldTransform()
        vec_offset = mat4_transformVector(transform, vec_offset)
        local playerPos = self:getPosition3D()
        self._cam:setPosition3D(cc.vec3add(playerPos, camera_offset))
        self:updateState()
    end, 0)

    self:registerScriptHandler(function (event)
        -- body
        if "exit" == event then
            self:unscheduleUpdate()
        end
    end)
end

function Player:updateState()
    if self._playerState == PLAER_STATE.FORWARD then
        local player_pos = cc.p(self:getPositionX(),self:getPositionZ())
        local targetPos = cc.p(self._targetPos.x, self._targetPos.z)
        local dist = cc.pGetDistance(player_pos, targetPos)
        if dist < 1 then
            self._playerState = PLAER_STATE.IDLE
        end
    end
end

local TerrainWalkThru = class("TerrainWalkThru", function ()
    local layer = cc.Layer:create()
    Helper.initWithLayer(layer)
    return layer
end)

function TerrainWalkThru:ctor()
    -- body
    local function onNodeEvent(event)
        if "enter" == event then
            self:onEnter()
        elseif "exit" == event then
            self:onExit()
        end
    end
     self:registerScriptHandler(onNodeEvent)
end

function TerrainWalkThru:onEnter()
    self:init()
end

function TerrainWalkThru:onExit()

end

function TerrainWalkThru:init()
    Helper.titleLabel:setString(self:title())
    Helper.subtitleLabel:setString(self:subtitle())

    local listener = cc.EventListenerTouchAllAtOnce:create()

    listener:registerScriptHandler(function (touches, event)

    end,cc.Handler.EVENT_TOUCHES_BEGAN)

    listener:registerScriptHandler(function (touches, event)

        local touch = touches[1]
        local location = touch:getLocationInView()
        if self._camera ~= nil then
            if self._player ~= nil then
                local nearP = cc.vec3(location.x, location.y, 0.0)
                local farP  = cc.vec3(location.x, location.y, 1.0)

                local size = cc.Director:getInstance():getWinSize()
                nearP = self._camera:unproject(size, nearP, nearP)
                farP  = self._camera:unproject(size, farP, farP)
                local dir = cc.vec3sub(farP, nearP)
                dir = cc.vec3normalize(dir)

                local collisionPoint = cc.vec3(-999,-999,-999)
                local ray =  cc.Ray:new(nearP, dir)
                local isInTerrain = true
                isInTerrain, collisionPoint = self._terrain:getIntersectionPoint(ray, collisionPoint)

                if( not isInTerrain) then  
                    self._player._playerState = PLAER_STATE.IDLE
                    return
                end

                local playerPos = self._player:getPosition3D()
                dir = cc.vec3sub(collisionPoint, playerPos)
                dir.y = 0
                dir = cc.vec3normalize(dir)
                self._player._headingAngle =  -1 * math.acos(-dir.z)

                self._player._headingAxis = vec3_cross(dir, cc.vec3(0, 0, -1), self._player._headingAxis)
                self._player._targetPos = collisionPoint
                self._player._playerState = PLAER_STATE.FORWARD
            end
        end
    end,cc.Handler.EVENT_TOUCHES_ENDED)

    local eventDispatcher = self:getEventDispatcher()
    eventDispatcher:addEventListenerWithSceneGraphPriority(listener, self)

    local visibleSize = cc.Director:getInstance():getVisibleSize()
    self._camera = cc.Camera:createPerspective(60, visibleSize.width/visibleSize.height, 0.1, 200)
    self._camera:setCameraFlag(cc.CameraFlag.USER1)
    self:addChild(self._camera)

    local detailMapR = { _detailMapSrc = "TerrainTest/dirt.jpg", _detailMapSize = 35}
    local detailMapG = { _detailMapSrc = "TerrainTest/Grass2.jpg", _detailMapSize = 10}
    local detailMapB = { _detailMapSrc = "TerrainTest/road.jpg", _detailMapSize = 35}
    local detailMapA = { _detailMapSrc = "TerrainTest/GreenSkin.jpg", _detailMapSize = 20}
    local terrainData = { _heightMapSrc = "TerrainTest/heightmap16.jpg", _alphaMapSrc = "TerrainTest/alphamap.png" , _detailMaps = {detailMapR, detailMapG, detailMapB, detailMapA}, _detailMapAmount = 4, _mapHeight = 40.0, _mapScale = 2.0 }

    self._terrain = cc.Terrain:create(terrainData,cc.Terrain.CrackFixedType.SKIRT)
    self._terrain:setMaxDetailMapAmount(4)
    self._terrain:setCameraMask(2)
    self._terrain:setDrawWire(false)

    self._terrain:setSkirtHeightRatio(3)
    self._terrain:setLODDistance(64,128,192)

    self._player = Player:create("Sprite3DTest/girl.c3b", self._camera, self._terrain)
    self._player:setCameraMask(2)
    self._player:setScale(0.08)
    self._player:setPositionY(self._terrain:getHeight(self._player:getPositionX(), self._player:getPositionZ()) + PLAYER_HEIGHT)

    --add Particle3D for test blend
    local rootps = cc.PUParticleSystem3D:create("Particle3D/scripts/mp_torch.pu")
    rootps:setCameraMask(cc.CameraFlag.USER1)
    rootps:setScale(30.0)
    rootps:startParticleSystem()
    self._player:addChild(rootps)

    --add BillBoard for test blend
    local billboard = cc.BillBoard:create("Images/btn-play-normal.png")
    billboard:setPosition3D(cc.vec3(0,180,0))
    billboard:setCameraMask(cc.CameraFlag.USER1)
    self._player:addChild(billboard)

    local animation = cc.Animation3D:create("Sprite3DTest/girl.c3b","Take 001")
    if nil ~= animation then
        local animate = cc.Animate3D:create(animation)
        self._player:runAction(cc.RepeatForever:create(animate))
    end

    local playerPos = self._player:getPosition3D()
    self._camera:setPosition3D(cc.vec3add(playerPos, camera_offset))
    self._camera:setRotation3D(cc.vec3(-45,0,0))

    self:addChild(self._player)
    self:addChild(self._terrain)

    self:extend()
end

function TerrainWalkThru:title()
    return "Player walk around in terrain"
end

function TerrainWalkThru:subtitle()
    return "touch to move"
end

function TerrainWalkThru:extend()
    
end

----------------------------------------
----Scene3DTest
----------------------------------------
local Scene3DTest = class("Scene3DTest", TerrainWalkThru)

function Scene3DTest:create3DWorld()
    -- terrain and player has been create in TerrainWalkThru:init
    -- we only need override there camera mask
    self._terrain:setCameraMask(s_CM[GAME_LAYER.LAYER_GAME])
    self._player:setCameraMask(s_CM[GAME_LAYER.LAYER_GAME])
    self._player:setScale(self._player:getScale() * 1.5)

    --add two Sprite3D monster, one is transparent
    local playerPos = self._player:getPosition3D()
    local monster = cc.Sprite3D:create("Sprite3DTest/orc.c3b")
    monster:setRotation3D(cc.vec3(0,180,0))
    monster:setPosition3D(cc.vec3(playerPos.x + 50, playerPos.y - 10, playerPos.z))
    monster:setCameraMask(s_CM[GAME_LAYER.LAYER_GAME])
    monster:setOpacity(128)
    self:addChild(monster)
    monster = cc.Sprite3D:create("Sprite3DTest/orc.c3b")
    monster:setRotation3D(cc.vec3(0,180,0))
    monster:setPosition3D(cc.vec3(playerPos.x - 50, playerPos.y - 5, playerPos.z))
    monster:setCameraMask(s_CM[GAME_LAYER.LAYER_GAME])
    self:addChild(monster)

    --add a particle 3d above player
    local rootps = cc.PUParticleSystem3D:create("Particle3D/scripts/blackHole.pu", "Particle3D/materials/pu_mediapack_01.material")
    rootps:setScale(2)
    rootps:setPosition3D(cc.vec3(0, 150, 0))
    rootps:setCameraMask(s_CM[GAME_LAYER.LAYER_GAME])
    local moveby  = cc.MoveBy:create(2.0, cc.p(50.0, 0.0))
    local moveby1 = cc.MoveBy:create(2.0, cc.p(-50.0, 0.0))
    rootps:runAction(cc.RepeatForever:create(cc.Sequence:create(moveby, moveby1)))
    rootps:startParticleSystem()
    self._player:addChild(rootps, 0)

    --then, create skybox
    --create and set our custom shader

    local cmVert = cc.FileUtils:getInstance():getStringFromFile("Sprite3DTest/cube_map.vert")
    local cmFrag = cc.FileUtils:getInstance():getStringFromFile("Sprite3DTest/cube_map.frag")
    local program = ccb.Device:getInstance():newProgram(cmVert, cmFrag)
    local state = ccb.ProgramState:new(program)
    program:release()
    --create the second texture for cylinder
    self._textureCube = cc.TextureCube:create("Sprite3DTest/skybox/left.jpg", "Sprite3DTest/skybox/right.jpg",
                                       "Sprite3DTest/skybox/top.jpg", "Sprite3DTest/skybox/bottom.jpg",
                                       "Sprite3DTest/skybox/front.jpg", "Sprite3DTest/skybox/back.jpg")

    --set texture parameters
    local tRepeatParams = { magFilter = ccb.SamplerFilter.LINEAR , minFilter = ccb.SamplerFilter.LINEAR , sAddressMode = ccb.SamplerAddressMode.MIRRORED_REPEAT  , tAddressMode = ccb.SamplerAddressMode.MIRRORED_REPEAT }
    self._textureCube:setTexParameters(tRepeatParams)

    --pass the texture sampler to our custom shader
    local cubeTexLoc = state:getUniformLocation("u_cubeTex")
    state:setTexture(cubeTexLoc, 0, self._textureCube:getBackendTexture())

    --add skybox
    self._skyBox = cc.Skybox:create()
    self._skyBox:setCameraMask(s_CM[GAME_LAYER.LAYER_SKYBOX])
    self._skyBox:setTexture(self._textureCube)
    self:addChild(self._skyBox)

end

function Scene3DTest:createUI()
    --add player button
    local showLeftDlgItem = cc.MenuItemImage:create("Images/Pea.png", "Images/Pea.png")
    showLeftDlgItem:registerScriptTapHandler(function (tag, sender)
        if nil ~= self._playerDlg then
            self._playerDlg:setVisible(not self._playerDlg:isVisible())
        end
    end)
    showLeftDlgItem:setPosition(VisibleRect:left().x + 30, VisibleRect:top().y - 30)

    local ttfConfig = { fontFilePath = "fonts/arial.ttf", fontSize = 20}
    local descItem  = cc.MenuItemLabel:create(cc.Label:createWithTTF(ttfConfig, "Description"))
    descItem:registerScriptTapHandler(function(tag, sender)
        if nil ~= self._descDlg then
            self._descDlg:setVisible(not self._descDlg:isVisible())
        end
    end)
    descItem:setPosition(cc.p(VisibleRect:right().x - 50, VisibleRect:top().y - 25))

    local backItem = cc.MenuItemLabel:create(cc.Label:createWithTTF(ttfConfig, "Back"))
    backItem:setPosition(cc.p(VisibleRect:right().x - 50, VisibleRect:bottom().y + 25))

    local menu = cc.Menu:create(showLeftDlgItem, descItem)
    menu:setPosition(cc.p(0.0, 0.0))
    menu:setCameraMask(s_CM[GAME_LAYER.LAYER_UI], true)
    self:addChild(menu)
end

function Scene3DTest:createPlayerDlg()
    cc.SpriteFrameCache:getInstance():addSpriteFrames(s_s9s_ui_plist)
    
    local dlgSize = cc.size(190, 240)
    local pos = VisibleRect:center()
    local margin = 10

    --first, create dialog ui part, include background, title and buttons
    self._playerDlg = ccui.Scale9Sprite:createWithSpriteFrameName("button_actived.png")
    self._playerDlg:setContentSize(dlgSize)
    self._playerDlg:setAnchorPoint(cc.p(1, 0.5))
    pos.y = pos.y - margin
    pos.x = pos.x - margin
    self._playerDlg:setPosition(pos)

    --title
    local title = cc.Label:createWithTTF("Player Dialog","fonts/arial.ttf",16)
    title:setPosition(dlgSize.width / 2, dlgSize.height - margin * 2)
    self._playerDlg:addChild(title)

    --player background
    local bgSize = cc.size(110, 180)
    local bgPos  = cc.p(margin, dlgSize.height / 2 - margin)
    local playerBg = ccui.Scale9Sprite:createWithSpriteFrameName("item_bg.png")
    playerBg:setContentSize(bgSize)
    playerBg:setAnchorPoint(cc.p(0, 0.5))
    playerBg:setPosition(bgPos)
    self._playerDlg:addChild(playerBg)

    --item background and item
    local itemSize   = cc.size(48, 48)
    local itemAnchor = cc.p(0, 1)
    local itemPos    = cc.p(bgPos.x + bgSize.width + margin, bgPos.y + bgSize.height / 2)
    local itemBg = ccui.Scale9Sprite:createWithSpriteFrameName("item_bg.png")
    itemBg:setContentSize(itemSize)
    itemBg:setAnchorPoint(itemAnchor)
    itemBg:setPosition(itemPos)
    self._playerDlg:addChild(itemBg)

    local item = ccui.Button:create("crystal.png", "", "", ccui.TextureResType.plistType)
    item:setScale(1.5)
    item:setAnchorPoint(itemAnchor)
    item:setPosition(itemPos)
    item:addClickEventListener(function(sender)
        if self._detailDlg ~= nil then
            self._detailDlg:setVisible(not self._detailDlg:isVisible())
        end
    end)
    self._playerDlg:addChild(item)

    --after add ui element, add player dialog to scene
    self._playerDlg:setCameraMask(s_CM[GAME_LAYER.LAYER_UI])
    self:addChild(self._playerDlg)

    --second, add 3d actor, which on dialog layer
    local girl = cc.Sprite3D:create("Sprite3DTest/girl.c3b")
    girl:setScale(0.5)
    girl:setPosition(bgSize.width / 2, margin * 2)
    girl:setCameraMask(s_CM[GAME_LAYER.LAYER_ACTOR])
    playerBg:addChild(girl)

    --third, add zoom in/out button, which is 2d ui element and over 3d actor
    local zoomIn = ccui.Button:create("cocosui/animationbuttonnormal.png","cocosui/animationbuttonpressed.png")
    zoomIn:setScale(0.5)
    zoomIn:setAnchorPoint(cc.p(1, 1))
    zoomIn:setPosition(cc.p(bgSize.width / 2 - margin / 2, bgSize.height - margin))
    zoomIn:addClickEventListener(function(sender)
        girl:setScale(girl:getScale() * 2)
    end)
    zoomIn:setTitleText("Zoom In")
    zoomIn:setCameraMask(s_CM[GAME_LAYER.LAYER_ZOOM])
    playerBg:addChild(zoomIn)

    local zoomOut = ccui.Button:create("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png")
    zoomOut:setScale(0.5)
    zoomOut:setAnchorPoint(cc.p(0, 1))
    zoomOut:setPosition(cc.p(bgSize.width / 2 + margin / 2, bgSize.height - margin))
    zoomOut:addClickEventListener(function(sender)
        girl:setScale(girl:getScale() / 2)
    end)
    zoomOut:setTitleText("Zoom Out")
    zoomOut:setCameraMask(s_CM[GAME_LAYER.LAYER_ZOOM])
    playerBg:addChild(zoomOut)
end

function Scene3DTest:createDetailDlg()
    cc.SpriteFrameCache:getInstance():addSpriteFrames(s_s9s_ui_plist)
    
    local dlgSize = cc.size(190, 240)
    local pos = VisibleRect:center()
    local margin = 10
    
    --create dialog
    self._detailDlg = ccui.Scale9Sprite:createWithSpriteFrameName("button_actived.png")
    self._detailDlg:setContentSize(dlgSize)
    self._detailDlg:setAnchorPoint(cc.p(0, 0.5))
    self._detailDlg:setOpacity(224)
    pos.y = pos.y  - margin
    pos.x = pos.x  + margin
    self._detailDlg:setPosition(pos)

    -- title
    local title = cc.Label:createWithTTF("Detail Dialog","fonts/arial.ttf",16)
    title:setPosition(dlgSize.width / 2, dlgSize.height - margin * 2)
    self._detailDlg:addChild(title)
    
    -- add a spine ffd animation on it
    -- TODO coulsonwang: spine is not enable in V4.0
--    local skeletonNode = sp.SkeletonAnimation:create("spine/goblins-pro.json", "spine/goblins.atlas", 1.5)
--    skeletonNode:setAnimation(0, "walk", true)
--    skeletonNode:setSkin("goblin")
--
--    skeletonNode:setScale(0.25)
--    local windowSize = cc.Director:getInstance():getWinSize()
--    skeletonNode:setPosition(cc.p(dlgSize.width / 2, 20))
--    self._detailDlg:addChild(skeletonNode)

    local listener = cc.EventListenerTouchOneByOne:create()
    listener:registerScriptHandler(function (touch, event)
--        if (not skeletonNode:getDebugBonesEnabled()) then
--            skeletonNode:setDebugBonesEnabled(true)
--        elseif skeletonNode:getTimeScale() == 1 then
--            skeletonNode:setTimeScale(0.3)
--        else
--            skeletonNode:setTimeScale(1)
--            skeletonNode:setDebugBonesEnabled(false)
--        end

        return true
    end,cc.Handler.EVENT_TOUCH_BEGAN )

    local eventDispatcher = self:getEventDispatcher()
    eventDispatcher:addEventListenerWithSceneGraphPriority(listener, self)

    --after add ui element, add dialog to scene
    self._detailDlg:setCameraMask(s_CM[GAME_LAYER.LAYER_UI])
    self:addChild(self._detailDlg)
end

function Scene3DTest:createDescDlg()
    cc.SpriteFrameCache:getInstance():addSpriteFrames(s_s9s_ui_plist)
    
    local dlgSize = cc.size(440, 240)
    local pos = VisibleRect:center()
    local margin = 10
    
    --create dialog
    self._descDlg = ccui.Scale9Sprite:createWithSpriteFrameName("button_actived.png")
    self._descDlg:setContentSize(dlgSize)
    self._descDlg:setOpacity(224)
    self._descDlg:setPosition(pos)

    --title
    local title = cc.Label:createWithTTF("Description Dialog","fonts/arial.ttf",16)
    title:setPosition(dlgSize.width / 2, dlgSize.height - margin * 2)
    self._descDlg:addChild(title)

    --add a label to retain description text
    local textSize = cc.size(400, 220)
    local desc =  "Scene 3D test for 2D and 3D mix rendering.\n" ..
    "\n" ..
    "- Game world composite with terrain, skybox and 3D objects.\n" ..
    "- UI composite with 2D nodes.\n" ..
    "- Click the icon at the topleft conner, will show a player dialog which" ..
    "there is a 3D sprite on it.\n" ..
    "- There are two button to zoom the player model, which should keep above" ..
    "on 3D model.\n" ..
    "- This description dialog should above all other elements.\n" ..
    "\n" ..
    "Click \"Description\" button to hide this dialog.\n"

    local text = cc.Label:createWithSystemFont(desc, "Helvetica", 12, textSize)
    text:setAnchorPoint(cc.p(0, 1))
    text:setPosition(margin, dlgSize.height - (20 + margin))
    self._descDlg:addChild(text)
    
    --after add ui element, add dialog to scene
    self._descDlg:setCameraMask(s_CM[GAME_LAYER.LAYER_OSD])
    self:addChild(self._descDlg)
end

function Scene3DTest:extend()
    self._playerDlg = nil
    self._detailDlg = nil
    self._descDlg   = nil
    self._gameCameras = {nil, nil, nil, nil, nil, nil}

    cc.Director:getInstance():setDisplayStats(false)

    local ca = nil
    local visibleSize = cc.Director:getInstance():getVisibleSize()
    --first, create a camera to look the skybox
    ca = cc.Camera:createPerspective(60, visibleSize.width / visibleSize.height, 10, 1000)
    ca:setPosition3D(cc.vec3(0.0, 0.0, 50.0))
    ca:setCameraFlag(s_CF[GAME_LAYER.LAYER_SKYBOX])
    ca:setDepth(GAME_LAYER.LAYER_SKYBOX)
    self._gameCameras[GAME_LAYER.LAYER_SKYBOX] = ca
    self:addChild(ca)   

    -- second, create a camera to look the 3D game scene
    -- it has been create in TerrainWalkThru:init
    ca = self._camera
    ca:setCameraFlag(s_CF[GAME_LAYER.LAYER_GAME])
    ca:setDepth(GAME_LAYER.LAYER_GAME)
    self._gameCameras[GAME_LAYER.LAYER_GAME] = ca

    --third, use the default camera to look 2D base UI layer
    local scene = cc.Director:getInstance():getRunningScene()
    ca = scene:getDefaultCamera()
    ca:setCameraFlag(s_CF[GAME_LAYER.LAYER_UI])
    ca:setDepth(GAME_LAYER.LAYER_UI)
    self._gameCameras[GAME_LAYER.LAYER_UI] = ca

    --forth, create a camera to look the 3D model in dialogs
    ca = cc.Camera:create()
    ca:setCameraFlag(s_CF[GAME_LAYER.LAYER_ACTOR])
    ca:setDepth(GAME_LAYER.LAYER_ACTOR)
    self._gameCameras[GAME_LAYER.LAYER_ACTOR] = ca
    self:addChild(ca)

    -- fifth, create a camera to look the UI element over on the 3D models
    ca = cc.Camera:create()
    ca:setCameraFlag(s_CF[GAME_LAYER.LAYER_ZOOM])
    ca:setDepth(GAME_LAYER.LAYER_ZOOM)
    self._gameCameras[GAME_LAYER.LAYER_ZOOM] = ca
    self:addChild(ca)

    --sixth, create a camera to look the OSD UI
    ca = cc.Camera:create()
    ca:setCameraFlag(s_CF[GAME_LAYER.LAYER_OSD])
    ca:setDepth(GAME_LAYER.LAYER_OSD)
    self._gameCameras[GAME_LAYER.LAYER_OSD] = ca
    self:addChild(ca)

    self:create3DWorld()
    self:createUI()
    self:createPlayerDlg()
    self:createDetailDlg()
    self:createDescDlg()

    self._playerDlg:setVisible(false)
    self._detailDlg:setVisible(false)
end

function Scene3DTest:title()
    return ""
end

function Scene3DTest:subtitle()
    return ""
end

function Scene3DTest:onExit()
    local targetPlatform = cc.Application:getInstance():getTargetPlatform()
    if targetPlatform == cc.PLATFORM_OS_ANDROID  or targetPlatform == cc.PLATFORM_OS_WINRT  or targetPlatform == cc.PLATFORM_OS_WP8  then
        cc.Director:getInstance():getEventDispatcher():removeEventListener(self._backToForegroundListener)
    end
end



function Scene3DTestMain()
    local scene = cc.Scene:create()

    Helper.createFunctionTable =
    {
        Scene3DTest.create,
    }
    Helper.index = 1

    scene:addChild(Scene3DTest.create())
    local menu = CreateBackMenuItem()
    menu:setCameraMask(s_CM[GAME_LAYER.LAYER_UI])
    scene:addChild(menu)

    return scene
end
