local scheduler = CCDirector:sharedDirector():getScheduler()
local    kTagLabel = 1
local    kTagSprite1 = 2
local    kTagSprite2 = 3

local originCreateLayer = createTestLayer
local function createTestLayer(title, subtitle)
    local ret = originCreateLayer(title, subtitle)
    Helper.titleLabel:setTag(kTagLabel)
    CCTextureCache:sharedTextureCache():dumpCachedTextureInfo()
    local col = CCLayerColor:create(ccc4(128,128,128,255))
    ret:addChild(col, -10)
    CCTextureCache:sharedTextureCache():dumpCachedTextureInfo()
    return ret
end
--------------------------------------------------------------------
--
-- TextureTIFF
--
--------------------------------------------------------------------

local function TextureTIFF()
    local ret = createTestLayer("TIFF Test")
    local s = CCDirector:sharedDirector():getWinSize()

    local img = CCSprite:create("Images/test_image.tiff")
    img:setPosition(ccp( s.width/2.0, s.height/2.0))
    ret:addChild(img)
    CCTextureCache:sharedTextureCache():dumpCachedTextureInfo()
    return ret
end

--------------------------------------------------------------------
--
-- TexturePNG
--
--------------------------------------------------------------------
local function TexturePNG()
    local ret = createTestLayer("PNG Test")

    local s = CCDirector:sharedDirector():getWinSize()

    local img = CCSprite:create("Images/test_image.png")
    img:setPosition(ccp( s.width/2.0, s.height/2.0))
    ret:addChild(img)
    CCTextureCache:sharedTextureCache():dumpCachedTextureInfo()
    return ret
end

--------------------------------------------------------------------
--
-- TextureJPEG
--
--------------------------------------------------------------------
local function TextureJPEG()
    local ret = createTestLayer("JPEG Test")
    local s = CCDirector:sharedDirector():getWinSize()

    local img = CCSprite:create("Images/test_image.jpeg")
    img:setPosition(ccp( s.width/2.0, s.height/2.0))
    ret:addChild(img)
    CCTextureCache:sharedTextureCache():dumpCachedTextureInfo()
    return ret
end

--------------------------------------------------------------------
--
-- TextureWEBP
--
--------------------------------------------------------------------
local function TextureWEBP()
    local ret = createTestLayer("WEBP Test")
    local s = CCDirector:sharedDirector():getWinSize()

    local img = CCSprite:create("Images/test_image.webp")
    img:setPosition(ccp( s.width/2.0, s.height/2.0))
    ret:addChild(img)
    CCTextureCache:sharedTextureCache():dumpCachedTextureInfo()
    return ret
end

--------------------------------------------------------------------
--
-- TextureMipMap
--
--------------------------------------------------------------------
local function TextureMipMap()
    local ret = createTestLayer("Texture Mipmap",
                                "Left image uses mipmap. Right image doesn't")
    local s = CCDirector:sharedDirector():getWinSize()

    local texture0 = CCTextureCache:sharedTextureCache():addImage(
        "Images/grossini_dance_atlas.png")
    texture0:generateMipmap()
    local texParams     = ccTexParams()
    texParams.minFilter = GL_LINEAR_MIPMAP_LINEAR
    texParams.magFilter = GL_LINEAR
    texParams.wrapS     = GL_CLAMP_TO_EDGE
    texParams.wrapT     = GL_CLAMP_TO_EDGE
    texture0:setTexParameters(texParams)

    local texture1 = CCTextureCache:sharedTextureCache():addImage(
        "Images/grossini_dance_atlas_nomipmap.png")

    local img0 = CCSprite:createWithTexture(texture0)
    img0:setTextureRect(CCRectMake(85, 121, 85, 121))
    img0:setPosition(ccp( s.width/3.0, s.height/2.0))
    ret:addChild(img0)

    local img1 = CCSprite:createWithTexture(texture1)
    img1:setTextureRect(CCRectMake(85, 121, 85, 121))
    img1:setPosition(ccp( 2*s.width/3.0, s.height/2.0))
    ret:addChild(img1)

    local  scale1 = CCEaseOut:create(CCScaleBy:create(4, 0.01), 3)
    local  sc_back = scale1:reverse()

    local  scale2 = tolua.cast(scale1:copy(), "CCEaseOut")
    scale2:autorelease()
    local  sc_back2 = scale2:reverse()

    local arr = CCArray:create()
    arr:addObject(scale1)
    arr:addObject(sc_back)
    img0:runAction(CCRepeatForever:create(CCSequence:create(arr)))

    arr = CCArray:create()
    arr:addObject(scale2)
    arr:addObject(sc_back2)
    img1:runAction(CCRepeatForever:create(CCSequence:create(arr)))
    CCTextureCache:sharedTextureCache():dumpCachedTextureInfo()
    return ret
end

--------------------------------------------------------------------
--
-- TexturePVRMipMap
-- To generate PVR images read this article:
-- http:--developer.apple.com/iphone/library/qa/qa2008/qa1611.html
--
--------------------------------------------------------------------
local function TexturePVRMipMap()
    local ret = createTestLayer("PVRTC MipMap Test", "Left image uses mipmap. Right image doesn't")
    local s = CCDirector:sharedDirector():getWinSize()

    local imgMipMap = CCSprite:create("Images/logo-mipmap.pvr")
    if imgMipMap ~= nil then
        imgMipMap:setPosition(ccp( s.width/2.0-100, s.height/2.0))
        ret:addChild(imgMipMap)

        -- support mipmap filtering
        local texParams     = ccTexParams()
        texParams.minFilter = GL_LINEAR_MIPMAP_LINEAR
        texParams.magFilter = GL_LINEAR
        texParams.wrapS     = GL_CLAMP_TO_EDGE
        texParams.wrapT     = GL_CLAMP_TO_EDGE

        imgMipMap:getTexture():setTexParameters(texParams)
    end

    local img = CCSprite:create("Images/logo-nomipmap.pvr")
    if img ~= nil then

        img:setPosition(ccp( s.width/2.0+100, s.height/2.0))
        ret:addChild(img)

        local  scale1 = CCEaseOut:create(CCScaleBy:create(4, 0.01), 3)
        local  sc_back = scale1:reverse()

        local  scale2 = tolua.cast(scale1:copy(), "CCEaseOut")
        scale2:autorelease()
        local  sc_back2 = scale2:reverse()

        local arr = CCArray:create()
        arr:addObject(scale1)
        arr:addObject(sc_back)
        imgMipMap:runAction(CCRepeatForever:create(CCSequence:create(arr)))

        arr = CCArray:create()
        arr:addObject(scale2)
        arr:addObject(sc_back2)

        img:runAction(CCRepeatForever:create(CCSequence:create(arr)))
    end
    CCTextureCache:sharedTextureCache():dumpCachedTextureInfo()
    return ret
end


--------------------------------------------------------------------
--
-- TexturePVRMipMap2
--
--------------------------------------------------------------------
local function TexturePVRMipMap2()
    local ret = createTestLayer("PVR MipMap Test #2", "Left image uses mipmap. Right image doesn't")
    local s = CCDirector:sharedDirector():getWinSize()

    local imgMipMap = CCSprite:create("Images/test_image_rgba4444_mipmap.pvr")
    imgMipMap:setPosition(ccp( s.width/2.0-100, s.height/2.0))
    ret:addChild(imgMipMap)

    -- support mipmap filtering
    local texParams =  ccTexParams()
    texParams.minFilter = GL_LINEAR_MIPMAP_LINEAR
    texParams.magFilter = GL_LINEAR
    texParams.wrapS     = GL_CLAMP_TO_EDGE
    texParams.wrapT     = GL_CLAMP_TO_EDGE

    imgMipMap:getTexture():setTexParameters(texParams)

    local img = CCSprite:create("Images/test_image.png")
    img:setPosition(ccp( s.width/2.0+100, s.height/2.0))
    ret:addChild(img)

    local  scale1 = CCEaseOut:create(CCScaleBy:create(4, 0.01), 3)
    local  sc_back = scale1:reverse()

    local  scale2 = tolua.cast(scale1:copy(), "CCEaseOut")
    scale2:autorelease()
    local  sc_back2 = scale2:reverse()
    local arr = CCArray:create()
    arr:addObject(scale1)
    arr:addObject(sc_back)

    imgMipMap:runAction(CCRepeatForever:create(CCSequence:create(arr)))

    arr = CCArray:create()
    arr:addObject(scale2)
    arr:addObject(sc_back2)

    img:runAction(CCRepeatForever:create(CCSequence:create(arr)))
    CCTextureCache:sharedTextureCache():dumpCachedTextureInfo()
    return ret
end

--------------------------------------------------------------------
--
-- TexturePVR2BPP
-- Image generated using PVRTexTool:
-- http:--www.imgtec.com/powervr/insider/powervr-pvrtextool.asp
--
--------------------------------------------------------------------
local function TexturePVR2BPP()
    local ret = createTestLayer("PVR TC 2bpp Test")

    local s = CCDirector:sharedDirector():getWinSize()

    local img = CCSprite:create("Images/test_image_pvrtc2bpp.pvr")

    if img ~= nil then
        img:setPosition(ccp( s.width/2.0, s.height/2.0))
        ret:addChild(img)
    end

    CCTextureCache:sharedTextureCache():dumpCachedTextureInfo()
    return ret
end

--------------------------------------------------------------------
--
-- TexturePVR
-- To generate PVR images read this article:
-- http:--developer.apple.com/iphone/library/qa/qa2008/qa1611.html
--
--------------------------------------------------------------------
local function TexturePVR()
    local ret = createTestLayer("PVR TC 4bpp Test #2")
    local s = CCDirector:sharedDirector():getWinSize()

    local img = CCSprite:create("Images/test_image.pvr")

    if img ~= nil then
        img:setPosition(ccp( s.width/2.0, s.height/2.0))
        ret:addChild(img)
    else
        cclog("This test is not supported.")
    end
    CCTextureCache:sharedTextureCache():dumpCachedTextureInfo()
    return ret
end

--------------------------------------------------------------------
--
-- TexturePVR4BPP
-- Image generated using PVRTexTool:
-- http:--www.imgtec.com/powervr/insider/powervr-pvrtextool.asp
--
--------------------------------------------------------------------
local function TexturePVR4BPP()
    local ret = createTestLayer("PVR TC 4bpp Test #3")

    local s = CCDirector:sharedDirector():getWinSize()

    local img = CCSprite:create("Images/test_image_pvrtc4bpp.pvr")

    if img ~= nil then
        img:setPosition(ccp( s.width/2.0, s.height/2.0))
        ret:addChild(img)
    else
        cclog("This test is not supported in cocos2d-mac")
    end
    CCTextureCache:sharedTextureCache():dumpCachedTextureInfo()
    return ret
end

--------------------------------------------------------------------
--
-- TexturePVRRGBA8888
-- Image generated using PVRTexTool:
-- http:--www.imgtec.com/powervr/insider/powervr-pvrtextool.asp
--
--------------------------------------------------------------------
local function TexturePVRRGBA8888()
    local ret = createTestLayer("PVR + RGBA  8888 Test")

    local s = CCDirector:sharedDirector():getWinSize()

    local img = CCSprite:create("Images/test_image_rgba8888.pvr")
    img:setPosition(ccp( s.width/2.0, s.height/2.0))
    ret:addChild(img)
    CCTextureCache:sharedTextureCache():dumpCachedTextureInfo()
    return ret
end

--------------------------------------------------------------------
--
-- TexturePVRBGRA8888
-- Image generated using PVRTexTool:
-- http:--www.imgtec.com/powervr/insider/powervr-pvrtextool.asp
--
--------------------------------------------------------------------
local function TexturePVRBGRA8888()
    local ret = createTestLayer("PVR + BGRA 8888 Test")

    local s = CCDirector:sharedDirector():getWinSize()

    local img = CCSprite:create("Images/test_image_bgra8888.pvr")
    if img ~= nil then
        img:setPosition(ccp( s.width/2.0, s.height/2.0))
        ret:addChild(img)
    else
        cclog("BGRA8888 images are not supported")
    end
    CCTextureCache:sharedTextureCache():dumpCachedTextureInfo()
    return ret
end

--------------------------------------------------------------------
--
-- TexturePVRRGBA5551
-- Image generated using PVRTexTool:
-- http:--www.imgtec.com/powervr/insider/powervr-pvrtextool.asp
--
--------------------------------------------------------------------
local function TexturePVRRGBA5551()
    local ret = createTestLayer("PVR + RGBA 5551 Test")
    local s = CCDirector:sharedDirector():getWinSize()

    local img = CCSprite:create("Images/test_image_rgba5551.pvr")
    img:setPosition(ccp( s.width/2.0, s.height/2.0))
    ret:addChild(img)
    CCTextureCache:sharedTextureCache():dumpCachedTextureInfo()
    return ret
end

--------------------------------------------------------------------
--
-- TexturePVRRGBA4444
-- Image generated using PVRTexTool:
-- http:--www.imgtec.com/powervr/insider/powervr-pvrtextool.asp
--
--------------------------------------------------------------------
local function TexturePVRRGBA4444()
    local ret = createTestLayer("PVR + RGBA 4444 Test")
    local s = CCDirector:sharedDirector():getWinSize()

    local img = CCSprite:create("Images/test_image_rgba4444.pvr")
    img:setPosition(ccp( s.width/2.0, s.height/2.0))
    ret:addChild(img)
    CCTextureCache:sharedTextureCache():dumpCachedTextureInfo()
    return ret
end

--------------------------------------------------------------------
--
-- TexturePVRRGBA4444GZ
-- Image generated using PVRTexTool:
-- http:--www.imgtec.com/powervr/insider/powervr-pvrtextool.asp
--
--------------------------------------------------------------------
local function TexturePVRRGBA4444GZ()
    local ret = createTestLayer("PVR + RGBA 4444 + GZ Test",
                                "This is a gzip PVR image")
    local s = CCDirector:sharedDirector():getWinSize()

    local img = CCSprite:create("Images/test_image_rgba4444.pvr")
    img:setPosition(ccp( s.width/2.0, s.height/2.0))
    ret:addChild(img)
    CCTextureCache:sharedTextureCache():dumpCachedTextureInfo()
    return ret
end

--------------------------------------------------------------------
--
-- TexturePVRRGBA4444CCZ
-- Image generated using PVRTexTool:
-- http:--www.imgtec.com/powervr/insider/powervr-pvrtextool.asp
--
--------------------------------------------------------------------
local function TexturePVRRGBA4444CCZ()
    local ret = createTestLayer("PVR + RGBA 4444 + CCZ Test",
                                "This is a ccz PVR image")
    local s = CCDirector:sharedDirector():getWinSize()

    local img = CCSprite:create("Images/test_image_rgba4444.pvr.ccz")
    img:setPosition(ccp( s.width/2.0, s.height/2.0))
    ret:addChild(img)
    CCTextureCache:sharedTextureCache():dumpCachedTextureInfo()
    return ret
end

--------------------------------------------------------------------
--
-- TexturePVRRGB565
-- Image generated using PVRTexTool:
-- http:--www.imgtec.com/powervr/insider/powervr-pvrtextool.asp
--
--------------------------------------------------------------------
local function TexturePVRRGB565()
    local ret = createTestLayer("PVR + RGB 565 Test")
    local s = CCDirector:sharedDirector():getWinSize()

    local img = CCSprite:create("Images/test_image_rgb565.pvr")
    img:setPosition(ccp( s.width/2.0, s.height/2.0))
    ret:addChild(img)
    CCTextureCache:sharedTextureCache():dumpCachedTextureInfo()
    return ret
end

-- TexturePVR RGB888
-- Image generated using PVRTexTool:
-- http:--www.imgtec.com/powervr/insider/powervr-pvrtextool.asp
local function TexturePVRRGB888()
    local ret = createTestLayer("PVR + RGB 888 Test")
    local s = CCDirector:sharedDirector():getWinSize()

    local img = CCSprite:create("Images/test_image_rgb888.pvr")
    if img ~= nil then
        img:setPosition(ccp( s.width/2.0, s.height/2.0))
        ret:addChild(img)
    end
    CCTextureCache:sharedTextureCache():dumpCachedTextureInfo()
    return ret
end

--------------------------------------------------------------------
--
-- TexturePVRA8
-- Image generated using PVRTexTool:
-- http:--www.imgtec.com/powervr/insider/powervr-pvrtextool.asp
--
--------------------------------------------------------------------
local function TexturePVRA8()
    local ret = createTestLayer("PVR + A8 Test")
    local s = CCDirector:sharedDirector():getWinSize()

    local img = CCSprite:create("Images/test_image_a8.pvr")
    img:setPosition(ccp( s.width/2.0, s.height/2.0))
    ret:addChild(img)
    CCTextureCache:sharedTextureCache():dumpCachedTextureInfo()
    return ret
end

--------------------------------------------------------------------
--
-- TexturePVRI8
-- Image generated using PVRTexTool:
-- http:--www.imgtec.com/powervr/insider/powervr-pvrtextool.asp
--
--------------------------------------------------------------------
local function TexturePVRI8()
    local ret = createTestLayer("PVR + I8 Test")
    local s = CCDirector:sharedDirector():getWinSize()

    local img = CCSprite:create("Images/test_image_i8.pvr")
    img:setPosition(ccp( s.width/2.0, s.height/2.0))
    ret:addChild(img)
    CCTextureCache:sharedTextureCache():dumpCachedTextureInfo()
    return ret
end


--------------------------------------------------------------------
--
-- TexturePVRAI88
-- Image generated using PVRTexTool:
-- http:--www.imgtec.com/powervr/insider/powervr-pvrtextool.asp
--
--------------------------------------------------------------------
local function TexturePVRAI88()
    local ret = createTestLayer("PVR + AI88 Test")
    local s = CCDirector:sharedDirector():getWinSize()

    local img = CCSprite:create("Images/test_image_ai88.pvr")
    img:setPosition(ccp( s.width/2.0, s.height/2.0))
    ret:addChild(img)
    CCTextureCache:sharedTextureCache():dumpCachedTextureInfo()
    return ret
end

-- TexturePVR2BPPv3
local function TexturePVR2BPPv3()
    local ret = createTestLayer("PVR TC 2bpp Test", "Testing PVR File Format v3")
    local s = CCDirector:sharedDirector():getWinSize()

    local img = CCSprite:create("Images/test_image_pvrtc2bpp_v3.pvr")

    if img ~= nil then
        img:setPosition(ccp(s.width/2.0, s.height/2.0))
        ret:addChild(img)
    end
    CCTextureCache:sharedTextureCache():dumpCachedTextureInfo()
    return ret
end

-- TexturePVRII2BPPv3
local function TexturePVRII2BPPv3()
    local ret = createTestLayer("PVR TC II 2bpp Test", "Testing PVR File Format v3")
    local s = CCDirector:sharedDirector():getWinSize()

    local img = CCSprite:create("Images/test_image_pvrtcii2bpp_v3.pvr")

    if img ~= nil then
        img:setPosition(ccp(s.width/2.0, s.height/2.0))
        ret:addChild(img)
    end

    CCTextureCache:sharedTextureCache():dumpCachedTextureInfo()
    return ret
end

-- TexturePVR4BPPv3
local function TexturePVR4BPPv3()
    local ret = createTestLayer("PVR TC 4bpp Test", "Testing PVR File Format v3")
    local s = CCDirector:sharedDirector():getWinSize()

    local img = CCSprite:create("Images/test_image_pvrtc4bpp_v3.pvr")

    if img ~= nil then
        img:setPosition(ccp(s.width/2.0, s.height/2.0))
        ret:addChild(img)
    else
        cclog("This test is not supported")
    end

    CCTextureCache:sharedTextureCache():dumpCachedTextureInfo()
    return ret
end

-- TexturePVRII4BPPv3

-- Image generated using PVRTexTool:
-- http:--www.imgtec.com/powervr/insider/powervr-pvrtextool.asp

local function TexturePVRII4BPPv3()
    local ret = createTestLayer("PVR TC II 4bpp Test",
                                "Testing PVR File Format v3")
    local s = CCDirector:sharedDirector():getWinSize()

    local img = CCSprite:create("Images/test_image_pvrtcii4bpp_v3.pvr")

    if img ~= nil then
        img:setPosition(ccp(s.width/2.0, s.height/2.0))
        ret:addChild(img)
    else
        cclog("This test is not supported")
    end
    CCTextureCache:sharedTextureCache():dumpCachedTextureInfo()
    return ret
end

-- TexturePVRRGBA8888v3
local function TexturePVRRGBA8888v3()
    local ret = createTestLayer("PVR + RGBA  8888 Test",
                                "Testing PVR File Format v3")
    local s = CCDirector:sharedDirector():getWinSize()

    local img = CCSprite:create("Images/test_image_rgba8888_v3.pvr")

    if img ~= nil then
        img:setPosition(ccp(s.width/2.0, s.height/2.0))
        ret:addChild(img)
    end

    CCTextureCache:sharedTextureCache():dumpCachedTextureInfo()
    return ret
end

-- TexturePVRBGRA8888v3
local function TexturePVRBGRA8888v3()
    local ret = createTestLayer("PVR + BGRA 8888 Test",
                                "Testing PVR File Format v3")

    local s = CCDirector:sharedDirector():getWinSize()

    local img = CCSprite:create("Images/test_image_bgra8888_v3.pvr")

    if img ~= nil then
        img:setPosition(ccp(s.width/2.0, s.height/2.0))
        ret:addChild(img)
    else
        cclog("BGRA images are not supported")
    end

    CCTextureCache:sharedTextureCache():dumpCachedTextureInfo()
    return ret
end

-- TexturePVRRGBA5551v3
local function TexturePVRRGBA5551v3()
    local ret = createTestLayer("PVR + RGBA 5551 Test",
                                "Testing PVR File Format v3")
    local s = CCDirector:sharedDirector():getWinSize()
    local img = CCSprite:create("Images/test_image_rgba5551_v3.pvr")

    if img ~= nil then
        img:setPosition(ccp(s.width/2.0, s.height/2.0))
        ret:addChild(img)
    end

    CCTextureCache:sharedTextureCache():dumpCachedTextureInfo()
    return ret
end

-- TexturePVRRGBA4444v3
local function TexturePVRRGBA4444v3()
    local ret = createTestLayer("PVR + RGBA 4444 Test",
                                "Testing PVR File Format v3")
    local s = CCDirector:sharedDirector():getWinSize()

    local img = CCSprite:create("Images/test_image_rgba4444_v3.pvr")

    if img ~= nil then
        img:setPosition(ccp(s.width/2.0, s.height/2.0))
        ret:addChild(img)
    end

    CCTextureCache:sharedTextureCache():dumpCachedTextureInfo()
    return ret
end

-- TexturePVRRGB565v3
local function TexturePVRRGB565v3()
    local ret = createTestLayer("PVR + RGB 565 Test",
                                "Testing PVR File Format v3")
    local s = CCDirector:sharedDirector():getWinSize()

    local img = CCSprite:create("Images/test_image_rgb565_v3.pvr")

    if img ~= nil then
        img:setPosition(ccp(s.width/2.0, s.height/2.0))
        ret:addChild(img)
    end

    CCTextureCache:sharedTextureCache():dumpCachedTextureInfo()
    return ret
end

-- TexturePVRRGB888v3
local function TexturePVRRGB888v3()
    local ret = createTestLayer("PVR + RGB 888 Test",
                                "Testing PVR File Format v3")
    local s = CCDirector:sharedDirector():getWinSize()

    local img = CCSprite:create("Images/test_image_rgb888_v3.pvr")

    if img ~= nil then
        img:setPosition(ccp(s.width/2.0, s.height/2.0))
        ret:addChild(img)
    end

    CCTextureCache:sharedTextureCache():dumpCachedTextureInfo()
    return ret
end

-- TexturePVRA8v3
local function TexturePVRA8v3()
    local ret = createTestLayer("PVR + A8 Test",
                                "Testing PVR File Format v3")
    local s = CCDirector:sharedDirector():getWinSize()

    local img = CCSprite:create("Images/test_image_a8_v3.pvr")

    if img ~= nil then
        img:setPosition(ccp(s.width/2.0, s.height/2.0))
        ret:addChild(img)
    end

    CCTextureCache:sharedTextureCache():dumpCachedTextureInfo()
    return ret
end

-- TexturePVRI8v3
local function TexturePVRI8v3()
    local ret = createTestLayer("PVR + I8 Test",
                                "Testing PVR File Format v3")
    local s = CCDirector:sharedDirector():getWinSize()

    local img = CCSprite:create("Images/test_image_i8_v3.pvr")

    if img ~= nil then
        img:setPosition(ccp(s.width/2.0, s.height/2.0))
        ret:addChild(img)
    end

    CCTextureCache:sharedTextureCache():dumpCachedTextureInfo()
    return ret
end

-- TexturePVRAI88v3
local function TexturePVRAI88v3()
    local ret = createTestLayer("PVR + AI88 Test",
                                "Testing PVR File Format v3")
    local s = CCDirector:sharedDirector():getWinSize()

    local img = CCSprite:create("Images/test_image_ai88_v3.pvr")

    if img ~= nil then
        img:setPosition(ccp(s.width/2.0, s.height/2.0))
        ret:addChild(img)
    end

    CCTextureCache:sharedTextureCache():dumpCachedTextureInfo()
    return ret
end

--------------------------------------------------------------------
--
-- TexturePVRBadEncoding
-- Image generated using PVRTexTool:
-- http:--www.imgtec.com/powervr/insider/powervr-pvrtextool.asp
--
--------------------------------------------------------------------
local function TexturePVRBadEncoding()
    local ret = createTestLayer("PVR Unsupported encoding",
                                "You should not see any image")
    local s = CCDirector:sharedDirector():getWinSize()

    local img = CCSprite:create("Images/test_image-bad_encoding.pvr")
    if img  ~= nil then
        img:setPosition(ccp( s.width/2.0, s.height/2.0))
        ret:addChild(img)
    end
    return ret
end

--------------------------------------------------------------------
--
-- TexturePVRNonSquare
--
--------------------------------------------------------------------
local function TexturePVRNonSquare()
    local ret = createTestLayer("PVR + Non square texture",
                                "Loading a 128x256 texture")
    local s = CCDirector:sharedDirector():getWinSize()

    local img = CCSprite:create("Images/grossini_128x256_mipmap.pvr")
    img:setPosition(ccp( s.width/2.0, s.height/2.0))
    ret:addChild(img)
    CCTextureCache:sharedTextureCache():dumpCachedTextureInfo()
    return ret
end

--------------------------------------------------------------------
--
-- TexturePVRNPOT4444
--
--------------------------------------------------------------------
local function TexturePVRNPOT4444()
    local ret = createTestLayer("PVR RGBA4 + NPOT texture",
                                "Loading a 81x121 RGBA4444 texture.")
    local s = CCDirector:sharedDirector():getWinSize()

    local img = CCSprite:create("Images/grossini_pvr_rgba4444.pvr")
    if img ~= nil then
        img:setPosition(ccp( s.width/2.0, s.height/2.0))
        ret:addChild(img)
    end
    CCTextureCache:sharedTextureCache():dumpCachedTextureInfo()
    return ret
end

--------------------------------------------------------------------
--
-- TexturePVRNPOT8888
--
--------------------------------------------------------------------
local function TexturePVRNPOT8888()
    local ret = createTestLayer("PVR RGBA8 + NPOT texture",
                                "Loading a 81x121 RGBA8888 texture.")
    local s = CCDirector:sharedDirector():getWinSize()

    local img = CCSprite:create("Images/grossini_pvr_rgba8888.pvr")
    if img ~= nil then
        img:setPosition(ccp( s.width/2.0, s.height/2.0))
        ret:addChild(img)
    end
    CCTextureCache:sharedTextureCache():dumpCachedTextureInfo()
    return ret
end

--------------------------------------------------------------------
--
-- TextureAlias
--
--------------------------------------------------------------------
local function TextureAlias()
    local ret = createTestLayer("AntiAlias / Alias textures",
                                "Left image is antialiased. Right image is aliases")
    local s = CCDirector:sharedDirector():getWinSize()

    --
    -- Sprite 1: GL_LINEAR
    --
    -- Default filter is GL_LINEAR

    local sprite = CCSprite:create("Images/grossinis_sister1.png")
    sprite:setPosition(ccp( s.width/3.0, s.height/2.0))
    ret:addChild(sprite)

    -- this is the default filterting
    sprite:getTexture():setAntiAliasTexParameters()

    --
    -- Sprite 1: GL_NEAREST
    --

    local sprite2 = CCSprite:create("Images/grossinis_sister2.png")
    sprite2:setPosition(ccp( 2*s.width/3.0, s.height/2.0))
    ret:addChild(sprite2)

    -- Use Nearest in this one
    sprite2:getTexture():setAliasTexParameters()

    -- scale them to show
    local  sc = CCScaleBy:create(3, 8.0)
    local  sc_back = tolua.cast(sc:reverse(), "CCScaleBy")
    local arr = CCArray:create()
    arr:addObject(sc)
    arr:addObject(sc_back)
    local  scaleforever = CCRepeatForever:create(CCSequence:create(arr))
    local  scaleToo = tolua.cast(scaleforever:copy(), "CCRepeatForever")
    scaleToo:autorelease()

    sprite2:runAction(scaleforever)
    sprite:runAction(scaleToo)
    CCTextureCache:sharedTextureCache():dumpCachedTextureInfo()
    return ret
end

--------------------------------------------------------------------
--
-- TexturePixelFormat
--
--------------------------------------------------------------------
local function TexturePixelFormat()
    local ret = createTestLayer("Texture Pixel Formats",
                                "Textures: RGBA8888, RGBA4444, RGB5A1, RGB888, RGB565, A8")
    --
    -- This example displays 1 png images 4 times.
    -- Each time the image is generated using:
    -- 1- 32-bit RGBA8
    -- 2- 16-bit RGBA4
    -- 3- 16-bit RGB5A1
    -- 4- 16-bit RGB565

    local label = tolua.cast(ret:getChildByTag(kTagLabel), "CCLabelTTF")
    label:setColor(ccc3(16,16,255))

    local s = CCDirector:sharedDirector():getWinSize()

    local background = CCLayerColor:create(ccc4(128,128,128,255), s.width, s.height)
    ret:addChild(background, -1)

    -- RGBA 8888 image (32-bit)
    CCTexture2D:setDefaultAlphaPixelFormat(kCCTexture2DPixelFormat_RGBA8888)
    local sprite1 = CCSprite:create("Images/test-rgba1.png")
    sprite1:setPosition(ccp(1*s.width/7, s.height/2+32))
    ret:addChild(sprite1, 0)

    -- remove texture from texture manager
    CCTextureCache:sharedTextureCache():removeTexture(sprite1:getTexture())

    -- RGBA 4444 image (16-bit)
    CCTexture2D:setDefaultAlphaPixelFormat(kCCTexture2DPixelFormat_RGBA4444)
    local sprite2 = CCSprite:create("Images/test-rgba1.png")
    sprite2:setPosition(ccp(2*s.width/7, s.height/2-32))
    ret:addChild(sprite2, 0)

    -- remove texture from texture manager
    CCTextureCache:sharedTextureCache():removeTexture(sprite2:getTexture())

    -- RGB5A1 image (16-bit)
    CCTexture2D:setDefaultAlphaPixelFormat(kCCTexture2DPixelFormat_RGB5A1)
    local sprite3 = CCSprite:create("Images/test-rgba1.png")
    sprite3:setPosition(ccp(3*s.width/7, s.height/2+32))
    ret:addChild(sprite3, 0)

    -- remove texture from texture manager
    CCTextureCache:sharedTextureCache():removeTexture(sprite3:getTexture())

    -- RGB888 image
    CCTexture2D:setDefaultAlphaPixelFormat(kCCTexture2DPixelFormat_RGB888)
    local sprite4 = CCSprite:create("Images/test-rgba1.png")
    sprite4:setPosition(ccp(4*s.width/7, s.height/2-32))
    ret:addChild(sprite4, 0)

    -- remove texture from texture manager
    CCTextureCache:sharedTextureCache():removeTexture(sprite4:getTexture())

    -- RGB565 image (16-bit)
    CCTexture2D:setDefaultAlphaPixelFormat(kCCTexture2DPixelFormat_RGB565)
    local sprite5 = CCSprite:create("Images/test-rgba1.png")
    sprite5:setPosition(ccp(5*s.width/7, s.height/2+32))
    ret:addChild(sprite5, 0)

    -- remove texture from texture manager
    CCTextureCache:sharedTextureCache():removeTexture(sprite5:getTexture())

    -- A8 image (8-bit)
    CCTexture2D:setDefaultAlphaPixelFormat(kCCTexture2DPixelFormat_A8)
    local sprite6 = CCSprite:create("Images/test-rgba1.png")
    sprite6:setPosition(ccp(6*s.width/7, s.height/2-32))
    ret:addChild(sprite6, 0)

    -- remove texture from texture manager
    CCTextureCache:sharedTextureCache():removeTexture(sprite6:getTexture())

    local  fadeout = CCFadeOut:create(2)
    local   fadein  = CCFadeIn:create(2)
    local arr = CCArray:create()
    arr:addObject(CCDelayTime:create(2))
    arr:addObject(fadeout)
    arr:addObject(fadein)
    local  seq = CCSequence:create(arr)
    local  seq_4ever = CCRepeatForever:create(seq)
    local  seq_4ever2 = tolua.cast(seq_4ever:copy(), "CCRepeatForever")
    seq_4ever2:autorelease()
    local  seq_4ever3 = tolua.cast(seq_4ever:copy(), "CCRepeatForever")
    seq_4ever3:autorelease()
    local  seq_4ever4 = tolua.cast(seq_4ever:copy(), "CCRepeatForever")
    seq_4ever4:autorelease()
    local  seq_4ever5 = tolua.cast(seq_4ever:copy(), "CCRepeatForever")
    seq_4ever5:autorelease()

    sprite1:runAction(seq_4ever)
    sprite2:runAction(seq_4ever2)
    sprite3:runAction(seq_4ever3)
    sprite4:runAction(seq_4ever4)
    sprite5:runAction(seq_4ever5)

    -- restore default
    CCTexture2D:setDefaultAlphaPixelFormat(kCCTexture2DPixelFormat_Default)
    CCTextureCache:sharedTextureCache():dumpCachedTextureInfo()
    return ret
end

--------------------------------------------------------------------
--
-- TextureBlend
--
--------------------------------------------------------------------
local function TextureBlend()
    local ret = createTestLayer("Texture Blending",
                                "Testing 3 different blending modes")
    local i = 0
    for i=0, 14 do
        -- BOTTOM sprites have alpha pre-multiplied
        -- they use by default GL_ONE, GL_ONE_MINUS_SRC_ALPHA
        local cloud = CCSprite:create("Images/test_blend.png")
        ret:addChild(cloud, i+1, 100+i)
        cloud:setPosition(ccp(50+25*i, 80))
        local blendFunc1 =  ccBlendFunc()
        blendFunc1.src = GL_ONE
        blendFunc1.dst = GL_ONE_MINUS_SRC_ALPHA
        cloud:setBlendFunc(blendFunc1)

        -- CENTER sprites have also alpha pre-multiplied
        -- they use by default GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA
        cloud = CCSprite:create("Images/test_blend.png")
        ret:addChild(cloud, i+1, 200+i)
        cloud:setPosition(ccp(50+25*i, 160))
        local blendFunc2 =  ccBlendFunc()
        blendFunc2.src = GL_ONE_MINUS_DST_COLOR
        blendFunc2.dst = GL_ZERO
        cloud:setBlendFunc(blendFunc2)

        -- UPPER sprites are using custom blending function
        -- You can set any blend function to your sprites
        cloud = CCSprite:create("Images/test_blend.png")
        ret:addChild(cloud, i+1, 200+i)
        cloud:setPosition(ccp(50+25*i, 320-80))
        local blendFunc3 =  ccBlendFunc()
        blendFunc3.src = GL_SRC_ALPHA
        blendFunc3.dst = GL_ONE
        cloud:setBlendFunc(blendFunc3)  -- additive blending
    end
    return ret
end

--------------------------------------------------------------------
--
-- TextureAsync
--
--------------------------------------------------------------------

local function TextureAsync()
    local ret = createTestLayer("Texture Async Load",
                                "Textures should load while an animation is being run")
    local m_nImageOffset = 0

    local size =CCDirector:sharedDirector():getWinSize()

    local label = CCLabelTTF:create("Loading...", "Marker Felt", 32)
    label:setPosition(ccp( size.width/2, size.height/2))
    ret:addChild(label, 10)

    local  scale = CCScaleBy:create(0.3, 2)
    local  scale_back = tolua.cast(scale:reverse(), "CCScaleBy")
    local arr = CCArray:create()
    arr:addObject(scale)
    arr:addObject(scale_back)
    local  seq = CCSequence:create(arr)
    label:runAction(CCRepeatForever:create(seq))

    local function imageLoaded(pObj)
        local  tex = tolua.cast(pObj, "CCTexture2D")
        local director = CCDirector:sharedDirector()

        --CCAssert( [NSThread currentThread] == [director runningThread], @"FAIL. Callback should be on cocos2d thread")

        -- IMPORTANT: The order on the callback is not guaranteed. Don't depend on the callback

        -- This test just creates a sprite based on the Texture

        local sprite = CCSprite:createWithTexture(tex)
        sprite:setAnchorPoint(ccp(0,0))
        ret:addChild(sprite, -1)

        local size = director:getWinSize()
        local i = m_nImageOffset * 32
        sprite:setPosition(ccp( i % size.width, (i / size.width) * 32 ))

        m_nImageOffset = m_nImageOffset + 1
        cclog("Image loaded:...")-- %p", tex)
    end

    local function loadImages(dt)
        local i = 0
        local j = 0
        for i=0, 7 do
            for j=0, 7 do
                local szSpriteName = string.format(
                    "Images/sprites_test/sprite-%d-%d.png", i, j)
                CCTextureCache:sharedTextureCache():addImageAsync(
                    szSpriteName, imageLoaded)
            end
        end

        CCTextureCache:sharedTextureCache():addImageAsync("Images/background1.jpg", imageLoaded)
        CCTextureCache:sharedTextureCache():addImageAsync("Images/background2.jpg", imageLoaded)
        CCTextureCache:sharedTextureCache():addImageAsync("Images/background.png", imageLoaded)
        CCTextureCache:sharedTextureCache():addImageAsync("Images/atlastest.png", imageLoaded)
        CCTextureCache:sharedTextureCache():addImageAsync("Images/grossini_dance_atlas.png",imageLoaded)
    end

    local schedulerEntry = nil
    local function onNodeEvent(event)
        if event == "enter" then
            schedulerEntry = scheduler:scheduleScriptFunc(loadImages, 1.0, false)
        elseif event == "exit" then
            scheduler:unscheduleScriptEntry(schedulerEntry)
            CCTextureCache:sharedTextureCache():removeAllTextures()
        end
    end

    ret:registerScriptHandler(onNodeEvent)
    return ret
end

--------------------------------------------------------------------
--
-- TextureGlClamp
--
--------------------------------------------------------------------
local function TextureGlClamp()
    local ret = createTestLayer("Texture GL_CLAMP")

    local size = CCDirector:sharedDirector():getWinSize()

    -- The .png image MUST be power of 2 in order to create a continue effect.
    -- eg: 32x64, 512x128, 256x1024, 64x64, etc..
    local sprite = CCSprite:create("Images/pattern1.png", CCRectMake(0,0,512,256))
    ret:addChild(sprite, -1, kTagSprite1)
    sprite:setPosition(ccp(size.width/2,size.height/2))
    local  texParams = ccTexParams()
    texParams.minFilter = GL_LINEAR
    texParams.magFilter = GL_LINEAR
    texParams.wrapS     = GL_CLAMP_TO_EDGE
    texParams.wrapT     = GL_CLAMP_TO_EDGE

    sprite:getTexture():setTexParameters(texParams)

    local  rotate = CCRotateBy:create(4, 360)
    sprite:runAction(rotate)
    local  scale = CCScaleBy:create(2, 0.04)
    local  scaleBack = tolua.cast(scale:reverse(), "CCScaleBy")
    local arr = CCArray:create()
    arr:addObject(scale)
    arr:addObject(scaleBack)
    local  seq = CCSequence:create(arr)
    sprite:runAction(seq)
    local function onNodeEvent(event)
        if event == "exit" then
            CCTextureCache:sharedTextureCache():removeUnusedTextures()
        end
    end

    ret:registerScriptHandler(onNodeEvent)

    return ret
end

--------------------------------------------------------------------
--
-- TextureGlRepeat
--
--------------------------------------------------------------------
local function TextureGlRepeat()
    local ret = createTestLayer("Texture GL_REPEAT")

    local size = CCDirector:sharedDirector():getWinSize()

    -- The .png image MUST be power of 2 in order to create a continue effect.
    -- eg: 32x64, 512x128, 256x1024, 64x64, etc..
    local sprite = CCSprite:create("Images/pattern1.png", CCRectMake(0, 0, 4096, 4096))
    ret:addChild(sprite, -1, kTagSprite1)
    sprite:setPosition(ccp(size.width/2,size.height/2))
    local  texParams = ccTexParams()

    texParams.minFilter = GL_LINEAR
    texParams.magFilter = GL_LINEAR
    texParams.wrapS     = GL_REPEAT
    texParams.wrapT     = GL_REPEAT

    sprite:getTexture():setTexParameters(texParams)

    local  rotate = CCRotateBy:create(4, 360)
    sprite:runAction(rotate)
    local  scale = CCScaleBy:create(2, 0.04)
    local  scaleBack = tolua.cast(scale:reverse(), "CCScaleBy")
    local arr = CCArray:create()
    arr:addObject(scale)
    arr:addObject(scaleBack)
    local  seq = CCSequence:create(arr)
    sprite:runAction(seq)
    local function onNodeEvent(event)
        if event == "exit" then
            CCTextureCache:sharedTextureCache():removeUnusedTextures()
        end
    end

    ret:registerScriptHandler(onNodeEvent)

    return ret
end

--------------------------------------------------------------------
--
-- TextureSizeTest
--
--------------------------------------------------------------------
local function TextureSizeTest()
    local ret = createTestLayer("Different Texture Sizes",
                                "512x512, 1024x1024. See the console.")
    local sprite = nil

    cclog("Loading 512x512 image...")
    sprite = CCSprite:create("Images/texture512x512.png")
    if sprite ~= nil then
        cclog("OK\n")
    else
        cclog("Error\n")

        cclog("Loading 1024x1024 image...")
        sprite = CCSprite:create("Images/texture1024x1024.png")
        if sprite ~= nil then
            cclog("OK\n")
        else
            cclog("Error\n")
            --     @todo
            --     cclog("Loading 2048x2048 image...")
            --     sprite = CCSprite:create("Images/texture2048x2048.png")
            --     if( sprite )
            --         cclog("OK\n")
            --     else
            --         cclog("Error\n")
            --
            --     cclog("Loading 4096x4096 image...")
            --     sprite = CCSprite:create("Images/texture4096x4096.png")
            --     if( sprite )
            --         cclog("OK\n")
            --     else
            --         cclog("Error\n")
        end
    end
    return ret
end
--------------------------------------------------------------------
--
-- TextureCache1
--
--------------------------------------------------------------------
local function TextureCache1()
    local ret = createTestLayer("CCTextureCache: remove",
                    "4 images should appear: alias, antialias, alias, antilias")
    local s = CCDirector:sharedDirector():getWinSize()

    local sprite = nil

    sprite = CCSprite:create("Images/grossinis_sister1.png")
    sprite:setPosition(ccp(s.width/5*1, s.height/2))
    sprite:getTexture():setAliasTexParameters()
    sprite:setScale(2)
    ret:addChild(sprite)

    CCTextureCache:sharedTextureCache():removeTexture(sprite:getTexture())

    sprite = CCSprite:create("Images/grossinis_sister1.png")
    sprite:setPosition(ccp(s.width/5*2, s.height/2))
    sprite:getTexture():setAntiAliasTexParameters()
    sprite:setScale(2)
    ret:addChild(sprite)

    -- 2nd set of sprites

    sprite = CCSprite:create("Images/grossinis_sister2.png")
    sprite:setPosition(ccp(s.width/5*3, s.height/2))
    sprite:getTexture():setAliasTexParameters()
    sprite:setScale(2)
    ret:addChild(sprite)

    CCTextureCache:sharedTextureCache():removeTextureForKey("Images/grossinis_sister2.png")

    sprite = CCSprite:create("Images/grossinis_sister2.png")
    sprite:setPosition(ccp(s.width/5*4, s.height/2))
    sprite:getTexture():setAntiAliasTexParameters()
    sprite:setScale(2)
    ret:addChild(sprite)
    return ret
end

-- TextureDrawAtPoint
local function TextureDrawAtPoint()
    local m_pTex1 = nil
    local m_pTex2 = nil
    local ret = createTestLayer("CCTexture2D: drawAtPoint",
                                "draws 2 textures using drawAtPoint")

    local function draw()
        -- TextureDemo:draw()

        local s = CCDirector:sharedDirector():getWinSize()

        m_pTex1:drawAtPoint(ccp(s.width/2-50, s.height/2 - 50))
        m_pTex2:drawAtPoint(ccp(s.width/2+50, s.height/2 - 50))
    end

    m_pTex1 = CCTextureCache:sharedTextureCache():addImage("Images/grossinis_sister1.png")
    m_pTex2 = CCTextureCache:sharedTextureCache():addImage("Images/grossinis_sister2.png")

    m_pTex1:retain()
    m_pTex2:retain()
    local function onNodeEvent(event)
        if event == "exit" then
            m_pTex1:release()
            m_pTex2:release()
        end
    end

    ret:registerScriptHandler(onNodeEvent)

    return ret
end

-- TextureDrawInRect

local function TextureDrawInRect()
    local ret = createTestLayer("CCTexture2D: drawInRect",
                                "draws 2 textures using drawInRect")
    local function draw()
        -- TextureDemo:draw()

        local s = CCDirector:sharedDirector():getWinSize()

        local rect1 = CCRectMake( s.width/2 - 80, 20, m_pTex1:getContentSize().width * 0.5, m_pTex1:getContentSize().height *2 )
        local rect2 = CCRectMake( s.width/2 + 80, s.height/2, m_pTex1:getContentSize().width * 2, m_pTex1:getContentSize().height * 0.5 )

        m_pTex1:drawInRect(rect1)
        m_pTex2:drawInRect(rect2)
    end

    local m_pTex1 = CCTextureCache:sharedTextureCache():addImage("Images/grossinis_sister1.png")
    local m_pTex2 = CCTextureCache:sharedTextureCache():addImage("Images/grossinis_sister2.png")

    m_pTex1:retain()
    m_pTex2:retain()
    local function onNodeEvent(event)
        if event == "exit" then
            m_pTex1:release()
            m_pTex2:release()
        end
    end

    ret:registerScriptHandler(onNodeEvent)

    return ret
end

-- --------------------------------------------------------------------
-- --
-- TextureMemoryAlloc
--
--------------------------------------------------------------------
local function TextureMemoryAlloc()
    local ret = createTestLayer("Texture memory",
                                "Testing Texture Memory allocation. Use Instruments + VM Tracker")
    local m_pBackground = nil

    CCMenuItemFont:setFontSize(24)

    local function updateImage(tag,sender)
        if m_pBackground ~= nil then
            cclog("updateImage"..tag)
            m_pBackground:removeFromParentAndCleanup(true)
        end
        CCTextureCache:sharedTextureCache():removeUnusedTextures()

        local targetPlatform = CCApplication:sharedApplication():getTargetPlatform()
        local file = ""

        if targetPlatform == kTargetAndroid then
            if tag == 0 then
                file = "Images/test_1021x1024.png"
            elseif tag == 1 then
                file = "Images/test_1021x1024_rgba8888.pvr"
            elseif tag == 2 then
                file = "Images/test_1021x1024_rgb888.pvr"
            elseif tag == 3 then
                 file = "Images/test_1021x1024_rgba4444.pvr"
            elseif tag == 4 then
                file = "Images/test_1021x1024_a8.pvr"
            end
        else
            if tag == 0 then
                file = "Images/test_1021x1024.png"
            elseif tag == 1 then
                file = "Images/test_1021x1024_rgba8888.pvr.gz"
            elseif tag == 2 then
                file = "Images/test_1021x1024_rgb888.pvr.gz"
            elseif tag == 3 then
                file = "Images/test_1021x1024_rgba4444.pvr.gz"
            elseif tag == 4 then
                file = "Images/test_1021x1024_a8.pvr.gz"
            end
        end

        m_pBackground = CCSprite:create(file)
        ret:addChild(m_pBackground, -10)

        m_pBackground:setVisible(false)

        local s = CCDirector:sharedDirector():getWinSize()
        m_pBackground:setPosition(ccp(s.width/2, s.height/2))
    end

    local item1 = CCMenuItemFont:create("PNG")
    item1:registerScriptTapHandler(updateImage)
    item1:setTag(0)

    local item2 = CCMenuItemFont:create("RGBA8")
    item2:registerScriptTapHandler(updateImage)
    item2:setTag(1)

    local item3 = CCMenuItemFont:create("RGB8")
    item3:registerScriptTapHandler(updateImage)
    item3:setTag(2)

    local item4 = CCMenuItemFont:create("RGBA4")
    item4:registerScriptTapHandler(updateImage)
    item4:setTag(3)

    local item5 = CCMenuItemFont:create("A8")
    item5:registerScriptTapHandler(updateImage)
    item5:setTag(4)

    local arr = CCArray:create()
    arr:addObject(item1)
    arr:addObject(item2)
    arr:addObject(item3)
    arr:addObject(item4)
    arr:addObject(item5)
    local menu = CCMenu:createWithArray(arr)
    menu:alignItemsHorizontally()

    ret:addChild(menu)

    local warmup = CCMenuItemFont:create("warm up texture")

    local function changeBackgroundVisible(tag, sender)
        if m_pBackground ~= nil then
            cclog("changeBackgroundVisible")
            m_pBackground:setVisible(true)
        end
    end

    warmup:registerScriptTapHandler(changeBackgroundVisible)
    local menu2 = CCMenu:createWithItem(warmup)

    menu2:alignItemsHorizontally()

    ret:addChild(menu2)
    local s = CCDirector:sharedDirector():getWinSize()

    menu2:setPosition(ccp(s.width/2, s.height/4))
    return ret
end

-- TexturePVRv3Premult
local function TexturePVRv3Premult()
    local ret = createTestLayer("PVRv3 Premult Flag",
                                "All images should look exactly the same")

    local function transformSprite(sprite)
        local fade = CCFadeOut:create(2)
        local dl = CCDelayTime:create(2)
        local fadein = tolua.cast(fade:reverse(), "CCFadeOut")
        local arr = CCArray:create()
        arr:addObject(fade)
        arr:addObject(fadein)
        arr:addObject(dl)
        local seq = CCSequence:create(arr)
        local repeatAction = CCRepeatForever:create(seq)
        sprite:runAction(repeatAction)
    end

    local size = CCDirector:sharedDirector():getWinSize()

    local background = CCLayerColor:create(ccc4(128,128,128,255), size.width, size.height)
    ret:addChild(background, -1)


    -- PVR premultiplied
    local pvr1 = CCSprite:create("Images/grossinis_sister1-testalpha_premult.pvr")
    ret:addChild(pvr1, 0)
    pvr1:setPosition(ccp(size.width/4*1, size.height/2))
    transformSprite(pvr1)

    -- PVR non-premultiplied
    local pvr2 = CCSprite:create("Images/grossinis_sister1-testalpha_nopremult.pvr")
    ret:addChild(pvr2, 0)
    pvr2:setPosition(ccp(size.width/4*2, size.height/2))
    transformSprite(pvr2)

    -- PNG
    CCTexture2D:setDefaultAlphaPixelFormat(kCCTexture2DPixelFormat_RGBA8888)
    CCTextureCache:sharedTextureCache():removeTextureForKey("Images/grossinis_sister1-testalpha.png")
    local png = CCSprite:create("Images/grossinis_sister1-testalpha.png")
    ret:addChild(png, 0)
    png:setPosition(ccp(size.width/4*3, size.height/2))
    transformSprite(png)
    return ret
end


function Texture2dTestMain()
    cclog("Texture2dTestMain")
    Helper.index = 1
    local scene = CCScene:create()
    Helper.createFunctionTable = {
        TextureMemoryAlloc,
        TextureAlias,
        TexturePVRMipMap,
        TexturePVRMipMap2,
        TexturePVRNonSquare,
        TexturePVRNPOT4444,
        TexturePVRNPOT8888,
        TexturePVR,
        TexturePVR2BPP,
        TexturePVR2BPPv3,
        TexturePVR4BPP,
        TexturePVR4BPPv3,
        TexturePVRII4BPPv3,
        TexturePVRRGBA8888,
        TexturePVRRGBA8888v3,
        TexturePVRBGRA8888,
        TexturePVRBGRA8888v3,
        TexturePVRRGBA4444,
        TexturePVRRGBA4444v3,
        TexturePVRRGBA4444GZ,
        TexturePVRRGBA4444CCZ,
        TexturePVRRGBA5551,
        TexturePVRRGBA5551v3,
        TexturePVRRGB565,
        TexturePVRRGB565v3,
        TexturePVRRGB888,
        TexturePVRRGB888v3,
        TexturePVRA8,
        TexturePVRA8v3,
        TexturePVRI8,
        TexturePVRI8v3,
        TexturePVRAI88,
        TexturePVRAI88v3,
        TexturePVRv3Premult,
        TexturePVRBadEncoding,
        TexturePNG,
        TextureJPEG,
        TextureTIFF,
        TextureWEBP,
        TextureMipMap,
        TexturePixelFormat,
        TextureBlend,
        TextureAsync,
        TextureGlClamp,
        TextureGlRepeat,
        TextureSizeTest,
        TextureCache1,
        TextureDrawAtPoint,
        TextureDrawInRect
    }
    scene:addChild(TextureMemoryAlloc())
    scene:addChild(CreateBackMenuItem())
    return scene
end
