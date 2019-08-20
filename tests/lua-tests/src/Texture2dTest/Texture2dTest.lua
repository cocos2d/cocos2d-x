local scheduler = cc.Director:getInstance():getScheduler()
local    kTagLabel = 1
local    kTagSprite1 = 2
local    kTagSprite2 = 3

local originCreateLayer = createTestLayer
local function createTestLayer(title, subtitle)
    local ret = originCreateLayer(title, subtitle)
    Helper.titleLabel:setTag(kTagLabel)
    print(cc.Director:getInstance():getTextureCache():getCachedTextureInfo())
    local col = cc.LayerColor:create(cc.c4b(128,128,128,255))
    ret:addChild(col, -10)
    print(cc.Director:getInstance():getTextureCache():getCachedTextureInfo())
    return ret
end

--------------------------------------------------------------------
--
-- TexturePNG
--
--------------------------------------------------------------------
local function TexturePNG()
    local ret = createTestLayer("PNG Test")

    local s = cc.Director:getInstance():getWinSize()

    local img = cc.Sprite:create("Images/test_image.png")
    img:setPosition(cc.p( s.width/2.0, s.height/2.0))
    ret:addChild(img)
    print(cc.Director:getInstance():getTextureCache():getCachedTextureInfo())
    return ret
end

--------------------------------------------------------------------
--
-- TextureJPEG
--
--------------------------------------------------------------------
local function TextureJPEG()
    local ret = createTestLayer("JPEG Test")
    local s = cc.Director:getInstance():getWinSize()

    local img = cc.Sprite:create("Images/test_image.jpeg")
    img:setPosition(cc.p( s.width/2.0, s.height/2.0))
    ret:addChild(img)
    print(cc.Director:getInstance():getTextureCache():getCachedTextureInfo())
    return ret
end

--------------------------------------------------------------------
--
-- TextureWEBP
--
--------------------------------------------------------------------
local function TextureWEBP()
    local ret = createTestLayer("WEBP Test")
    local s = cc.Director:getInstance():getWinSize()

    local img = cc.Sprite:create("Images/test_image.webp")
    img:setPosition(cc.p( s.width/2.0, s.height/2.0))
    ret:addChild(img)
    print(cc.Director:getInstance():getTextureCache():getCachedTextureInfo())
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
    local s = cc.Director:getInstance():getWinSize()

    local texture0 = cc.Director:getInstance():getTextureCache():addImage(
        "Images/grossini_dance_atlas.png")
    texture0:generateMipmap()
    texture0:setTexParameters(ccb.SamplerFilter.LINEAR_MIPMAP_LINEAR, ccb.SamplerFilter.LINEAR, ccb.SamplerAddressMode.CLAMP_TO_EDGE, ccb.SamplerAddressMode.CLAMP_TO_EDGE)

    local texture1 = cc.Director:getInstance():getTextureCache():addImage(
        "Images/grossini_dance_atlas_nomipmap.png")

    local img0 = cc.Sprite:createWithTexture(texture0)
    img0:setTextureRect(cc.rect(85, 121, 85, 121))
    img0:setPosition(cc.p( s.width/3.0, s.height/2.0))
    ret:addChild(img0)

    local img1 = cc.Sprite:createWithTexture(texture1)
    img1:setTextureRect(cc.rect(85, 121, 85, 121))
    img1:setPosition(cc.p( 2*s.width/3.0, s.height/2.0))
    ret:addChild(img1)

    local  scale1 = cc.EaseOut:create(cc.ScaleBy:create(4, 0.01), 3)
    local  sc_back = scale1:reverse()

    local  scale2 = scale1:clone()
    local  sc_back2 = scale2:reverse()

    img0:runAction(cc.RepeatForever:create(cc.Sequence:create(scale1, sc_back)))
    img1:runAction(cc.RepeatForever:create(cc.Sequence:create(scale2, sc_back2)))
    print(cc.Director:getInstance():getTextureCache():getCachedTextureInfo())
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
    local s = cc.Director:getInstance():getWinSize()

    local imgMipMap = cc.Sprite:create("Images/logo-mipmap.pvr")
    if imgMipMap ~= nil and imgMipMap:getTexture() ~= nil then
        imgMipMap:setPosition(cc.p( s.width/2.0-100, s.height/2.0))
        ret:addChild(imgMipMap)

        -- support mipmap filtering
        imgMipMap:getTexture():setTexParameters(ccb.SamplerFilter.LINEAR_MIPMAP_LINEAR, ccb.SamplerFilter.LINEAR, ccb.SamplerAddressMode.CLAMP_TO_EDGE, ccb.SamplerAddressMode.CLAMP_TO_EDGE)
    end

    local img = cc.Sprite:create("Images/logo-nomipmap.pvr")
    if img ~= nil then

        img:setPosition(cc.p( s.width/2.0+100, s.height/2.0))
        ret:addChild(img)

        local  scale1 = cc.EaseOut:create(cc.ScaleBy:create(4, 0.01), 3)
        local  sc_back = scale1:reverse()

        local  scale2 = scale1:clone()
        local  sc_back2 = scale2:reverse()

        imgMipMap:runAction(cc.RepeatForever:create(cc.Sequence:create(scale1, sc_back)))
        img:runAction(cc.RepeatForever:create(cc.Sequence:create(scale2, sc_back2)))
    end
    print(cc.Director:getInstance():getTextureCache():getCachedTextureInfo())
    return ret
end


--------------------------------------------------------------------
--
-- TexturePVRMipMap2
--
--------------------------------------------------------------------
local function TexturePVRMipMap2()
    local ret = createTestLayer("PVR MipMap Test #2", "Left image uses mipmap. Right image doesn't")
    local s = cc.Director:getInstance():getWinSize()

    local imgMipMap = cc.Sprite:create("Images/test_image_rgba4444_mipmap.pvr")
    imgMipMap:setPosition(cc.p( s.width/2.0-100, s.height/2.0))
    ret:addChild(imgMipMap)

    -- support mipmap filtering
    imgMipMap:getTexture():setTexParameters(ccb.SamplerFilter.LINEAR_MIPMAP_LINEAR, ccb.SamplerFilter.LINEAR, ccb.SamplerAddressMode.CLAMP_TO_EDGE, ccb.SamplerAddressMode.CLAMP_TO_EDGE)

    local img = cc.Sprite:create("Images/test_image.png")
    img:setPosition(cc.p( s.width/2.0+100, s.height/2.0))
    ret:addChild(img)

    local  scale1 = cc.EaseOut:create(cc.ScaleBy:create(4, 0.01), 3)
    local  sc_back = scale1:reverse()

    local  scale2 = scale1:clone()
    local  sc_back2 = scale2:reverse()

    imgMipMap:runAction(cc.RepeatForever:create(cc.Sequence:create(scale1, sc_back)))
    img:runAction(cc.RepeatForever:create(cc.Sequence:create(scale2, sc_back2)))

    print(cc.Director:getInstance():getTextureCache():getCachedTextureInfo())
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

    local s = cc.Director:getInstance():getWinSize()

    local img = cc.Sprite:create("Images/test_image_pvrtc2bpp.pvr")

    if img ~= nil then
        img:setPosition(cc.p( s.width/2.0, s.height/2.0))
        ret:addChild(img)
    end

    print(cc.Director:getInstance():getTextureCache():getCachedTextureInfo())
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
    local s = cc.Director:getInstance():getWinSize()

    local img = cc.Sprite:create("Images/test_image.pvr")

    if img ~= nil then
        img:setPosition(cc.p( s.width/2.0, s.height/2.0))
        ret:addChild(img)
    else
        cclog("This test is not supported.")
    end
    print(cc.Director:getInstance():getTextureCache():getCachedTextureInfo())
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

    local s = cc.Director:getInstance():getWinSize()

    local img = cc.Sprite:create("Images/test_image_pvrtc4bpp.pvr")

    if img ~= nil then
        img:setPosition(cc.p( s.width/2.0, s.height/2.0))
        ret:addChild(img)
    else
        cclog("This test is not supported in cocos2d-mac")
    end
    print(cc.Director:getInstance():getTextureCache():getCachedTextureInfo())
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

    local s = cc.Director:getInstance():getWinSize()

    local img = cc.Sprite:create("Images/test_image_rgba8888.pvr")
    img:setPosition(cc.p( s.width/2.0, s.height/2.0))
    ret:addChild(img)
    print(cc.Director:getInstance():getTextureCache():getCachedTextureInfo())
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

    local s = cc.Director:getInstance():getWinSize()

    local img = cc.Sprite:create("Images/test_image_bgra8888.pvr")
    if img ~= nil then
        img:setPosition(cc.p( s.width/2.0, s.height/2.0))
        ret:addChild(img)
    else
        cclog("BGRA8888 images are not supported")
    end
    print(cc.Director:getInstance():getTextureCache():getCachedTextureInfo())
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
    local s = cc.Director:getInstance():getWinSize()

    local img = cc.Sprite:create("Images/test_image_rgba5551.pvr")
    img:setPosition(cc.p( s.width/2.0, s.height/2.0))
    ret:addChild(img)
    print(cc.Director:getInstance():getTextureCache():getCachedTextureInfo())
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
    local s = cc.Director:getInstance():getWinSize()

    local img = cc.Sprite:create("Images/test_image_rgba4444.pvr")
    img:setPosition(cc.p( s.width/2.0, s.height/2.0))
    ret:addChild(img)
    print(cc.Director:getInstance():getTextureCache():getCachedTextureInfo())
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
    local s = cc.Director:getInstance():getWinSize()

    local img = cc.Sprite:create("Images/test_image_rgba4444.pvr")
    img:setPosition(cc.p( s.width/2.0, s.height/2.0))
    ret:addChild(img)
    print(cc.Director:getInstance():getTextureCache():getCachedTextureInfo())
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
    local ret = createTestLayer("PVR + RGBA 4444 + cc.Z Test",
                                "This is a ccz PVR image")
    local s = cc.Director:getInstance():getWinSize()

    local img = cc.Sprite:create("Images/test_image_rgba4444.pvr.ccz")
    img:setPosition(cc.p( s.width/2.0, s.height/2.0))
    ret:addChild(img)
    print(cc.Director:getInstance():getTextureCache():getCachedTextureInfo())
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
    local s = cc.Director:getInstance():getWinSize()

    local img = cc.Sprite:create("Images/test_image_rgb565.pvr")
    img:setPosition(cc.p( s.width/2.0, s.height/2.0))
    ret:addChild(img)
    print(cc.Director:getInstance():getTextureCache():getCachedTextureInfo())
    return ret
end

-- TexturePVR RGB888
-- Image generated using PVRTexTool:
-- http:--www.imgtec.com/powervr/insider/powervr-pvrtextool.asp
local function TexturePVRRGB888()
    local ret = createTestLayer("PVR + RGB 888 Test")
    local s = cc.Director:getInstance():getWinSize()

    local img = cc.Sprite:create("Images/test_image_rgb888.pvr")
    if img ~= nil then
        img:setPosition(cc.p( s.width/2.0, s.height/2.0))
        ret:addChild(img)
    end
    print(cc.Director:getInstance():getTextureCache():getCachedTextureInfo())
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
    local s = cc.Director:getInstance():getWinSize()

    local img = cc.Sprite:create("Images/test_image_a8.pvr")
    img:setPosition(cc.p( s.width/2.0, s.height/2.0))
    ret:addChild(img)
    print(cc.Director:getInstance():getTextureCache():getCachedTextureInfo())
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
    local s = cc.Director:getInstance():getWinSize()

    local img = cc.Sprite:create("Images/test_image_i8.pvr")
    img:setPosition(cc.p( s.width/2.0, s.height/2.0))
    ret:addChild(img)
    print(cc.Director:getInstance():getTextureCache():getCachedTextureInfo())
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
    local s = cc.Director:getInstance():getWinSize()

    local img = cc.Sprite:create("Images/test_image_ai88.pvr")
    img:setPosition(cc.p( s.width/2.0, s.height/2.0))
    ret:addChild(img)
    print(cc.Director:getInstance():getTextureCache():getCachedTextureInfo())
    return ret
end

-- TexturePVR2BPPv3
local function TexturePVR2BPPv3()
    local ret = createTestLayer("PVR TC 2bpp Test", "Testing PVR File Format v3")
    local s = cc.Director:getInstance():getWinSize()

    local img = cc.Sprite:create("Images/test_image_pvrtc2bpp_v3.pvr")

    if img ~= nil then
        img:setPosition(cc.p(s.width/2.0, s.height/2.0))
        ret:addChild(img)
    end
    print(cc.Director:getInstance():getTextureCache():getCachedTextureInfo())
    return ret
end

-- TexturePVRII2BPPv3
local function TexturePVRII2BPPv3()
    local ret = createTestLayer("PVR TC II 2bpp Test", "Testing PVR File Format v3")
    local s = cc.Director:getInstance():getWinSize()

    local img = cc.Sprite:create("Images/test_image_pvrtcii2bpp_v3.pvr")

    if img ~= nil then
        img:setPosition(cc.p(s.width/2.0, s.height/2.0))
        ret:addChild(img)
    end

    print(cc.Director:getInstance():getTextureCache():getCachedTextureInfo())
    return ret
end

-- TexturePVR4BPPv3
local function TexturePVR4BPPv3()
    local ret = createTestLayer("PVR TC 4bpp Test", "Testing PVR File Format v3")
    local s = cc.Director:getInstance():getWinSize()

    local img = cc.Sprite:create("Images/test_image_pvrtc4bpp_v3.pvr")

    if img ~= nil then
        img:setPosition(cc.p(s.width/2.0, s.height/2.0))
        ret:addChild(img)
    else
        cclog("This test is not supported")
    end

    print(cc.Director:getInstance():getTextureCache():getCachedTextureInfo())
    return ret
end

-- TexturePVRII4BPPv3

-- Image generated using PVRTexTool:
-- http:--www.imgtec.com/powervr/insider/powervr-pvrtextool.asp

local function TexturePVRII4BPPv3()
    local ret = createTestLayer("PVR TC II 4bpp Test",
                                "Testing PVR File Format v3")
    local s = cc.Director:getInstance():getWinSize()

    local img = cc.Sprite:create("Images/test_image_pvrtcii4bpp_v3.pvr")

    if img ~= nil then
        img:setPosition(cc.p(s.width/2.0, s.height/2.0))
        ret:addChild(img)
    else
        cclog("This test is not supported")
    end
    print(cc.Director:getInstance():getTextureCache():getCachedTextureInfo())
    return ret
end

-- TexturePVRRGBA8888v3
local function TexturePVRRGBA8888v3()
    local ret = createTestLayer("PVR + RGBA  8888 Test",
                                "Testing PVR File Format v3")
    local s = cc.Director:getInstance():getWinSize()

    local img = cc.Sprite:create("Images/test_image_rgba8888_v3.pvr")

    if img ~= nil then
        img:setPosition(cc.p(s.width/2.0, s.height/2.0))
        ret:addChild(img)
    end

    print(cc.Director:getInstance():getTextureCache():getCachedTextureInfo())
    return ret
end

-- TexturePVRBGRA8888v3
local function TexturePVRBGRA8888v3()
    local ret = createTestLayer("PVR + BGRA 8888 Test",
                                "Testing PVR File Format v3")

    local s = cc.Director:getInstance():getWinSize()

    local img = cc.Sprite:create("Images/test_image_bgra8888_v3.pvr")

    if img ~= nil then
        img:setPosition(cc.p(s.width/2.0, s.height/2.0))
        ret:addChild(img)
    else
        cclog("BGRA images are not supported")
    end

    print(cc.Director:getInstance():getTextureCache():getCachedTextureInfo())
    return ret
end

-- TexturePVRRGBA5551v3
local function TexturePVRRGBA5551v3()
    local ret = createTestLayer("PVR + RGBA 5551 Test",
                                "Testing PVR File Format v3")
    local s = cc.Director:getInstance():getWinSize()
    local img = cc.Sprite:create("Images/test_image_rgba5551_v3.pvr")

    if img ~= nil then
        img:setPosition(cc.p(s.width/2.0, s.height/2.0))
        ret:addChild(img)
    end

    print(cc.Director:getInstance():getTextureCache():getCachedTextureInfo())
    return ret
end

-- TexturePVRRGBA4444v3
local function TexturePVRRGBA4444v3()
    local ret = createTestLayer("PVR + RGBA 4444 Test",
                                "Testing PVR File Format v3")
    local s = cc.Director:getInstance():getWinSize()

    local img = cc.Sprite:create("Images/test_image_rgba4444_v3.pvr")

    if img ~= nil then
        img:setPosition(cc.p(s.width/2.0, s.height/2.0))
        ret:addChild(img)
    end

    print(cc.Director:getInstance():getTextureCache():getCachedTextureInfo())
    return ret
end

-- TexturePVRRGB565v3
local function TexturePVRRGB565v3()
    local ret = createTestLayer("PVR + RGB 565 Test",
                                "Testing PVR File Format v3")
    local s = cc.Director:getInstance():getWinSize()

    local img = cc.Sprite:create("Images/test_image_rgb565_v3.pvr")

    if img ~= nil then
        img:setPosition(cc.p(s.width/2.0, s.height/2.0))
        ret:addChild(img)
    end

    print(cc.Director:getInstance():getTextureCache():getCachedTextureInfo())
    return ret
end

-- TexturePVRRGB888v3
local function TexturePVRRGB888v3()
    local ret = createTestLayer("PVR + RGB 888 Test",
                                "Testing PVR File Format v3")
    local s = cc.Director:getInstance():getWinSize()

    local img = cc.Sprite:create("Images/test_image_rgb888_v3.pvr")

    if img ~= nil then
        img:setPosition(cc.p(s.width/2.0, s.height/2.0))
        ret:addChild(img)
    end

    print(cc.Director:getInstance():getTextureCache():getCachedTextureInfo())
    return ret
end

-- TexturePVRA8v3
local function TexturePVRA8v3()
    local ret = createTestLayer("PVR + A8 Test",
                                "Testing PVR File Format v3")
    local s = cc.Director:getInstance():getWinSize()

    local img = cc.Sprite:create("Images/test_image_a8_v3.pvr")

    if img ~= nil then
        img:setPosition(cc.p(s.width/2.0, s.height/2.0))
        ret:addChild(img)
    end

    print(cc.Director:getInstance():getTextureCache():getCachedTextureInfo())
    return ret
end

-- TexturePVRI8v3
local function TexturePVRI8v3()
    local ret = createTestLayer("PVR + I8 Test",
                                "Testing PVR File Format v3")
    local s = cc.Director:getInstance():getWinSize()

    local img = cc.Sprite:create("Images/test_image_i8_v3.pvr")

    if img ~= nil then
        img:setPosition(cc.p(s.width/2.0, s.height/2.0))
        ret:addChild(img)
    end

    print(cc.Director:getInstance():getTextureCache():getCachedTextureInfo())
    return ret
end

-- TexturePVRAI88v3
local function TexturePVRAI88v3()
    local ret = createTestLayer("PVR + AI88 Test",
                                "Testing PVR File Format v3")
    local s = cc.Director:getInstance():getWinSize()

    local img = cc.Sprite:create("Images/test_image_ai88_v3.pvr")

    if img ~= nil then
        img:setPosition(cc.p(s.width/2.0, s.height/2.0))
        ret:addChild(img)
    end

    print(cc.Director:getInstance():getTextureCache():getCachedTextureInfo())
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
    local s = cc.Director:getInstance():getWinSize()

    local img = cc.Sprite:create("Images/test_image-bad_encoding.pvr")
    if img  ~= nil then
        img:setPosition(cc.p( s.width/2.0, s.height/2.0))
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
    local s = cc.Director:getInstance():getWinSize()

    local img = cc.Sprite:create("Images/grossini_128x256_mipmap.pvr")
    img:setPosition(cc.p( s.width/2.0, s.height/2.0))
    ret:addChild(img)
    print(cc.Director:getInstance():getTextureCache():getCachedTextureInfo())
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
    local s = cc.Director:getInstance():getWinSize()

    local img = cc.Sprite:create("Images/grossini_pvr_rgba4444.pvr")
    if img ~= nil then
        img:setPosition(cc.p( s.width/2.0, s.height/2.0))
        ret:addChild(img)
    end
    print(cc.Director:getInstance():getTextureCache():getCachedTextureInfo())
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
    local s = cc.Director:getInstance():getWinSize()

    local img = cc.Sprite:create("Images/grossini_pvr_rgba8888.pvr")
    if img ~= nil then
        img:setPosition(cc.p( s.width/2.0, s.height/2.0))
        ret:addChild(img)
    end
    print(cc.Director:getInstance():getTextureCache():getCachedTextureInfo())
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
    local s = cc.Director:getInstance():getWinSize()

    --
    -- Sprite 1: ccb.SamplerFilter.LINEAR
    --
    -- Default filter is ccb.SamplerFilter.LINEAR

    local sprite = cc.Sprite:create("Images/grossinis_sister1.png")
    sprite:setPosition(cc.p( s.width/3.0, s.height/2.0))
    ret:addChild(sprite)

    -- this is the default filtering
    sprite:getTexture():setAntiAliasTexParameters()

    --
    -- Sprite 1: GL_NEAREST
    --

    local sprite2 = cc.Sprite:create("Images/grossinis_sister2.png")
    sprite2:setPosition(cc.p( 2*s.width/3.0, s.height/2.0))
    ret:addChild(sprite2)

    -- Use Nearest in this one
    sprite2:getTexture():setAliasTexParameters()

    -- scale them to show
    local  sc = cc.ScaleBy:create(3, 8.0)
    local  sc_back = sc:reverse()
    local  scaleforever = cc.RepeatForever:create(cc.Sequence:create(sc, sc_back))
    local  scaleToo = scaleforever:clone()

    sprite2:runAction(scaleforever)
    sprite:runAction(scaleToo)
    print(cc.Director:getInstance():getTextureCache():getCachedTextureInfo())
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

    local label = ret:getChildByTag(kTagLabel)
    label:setColor(cc.c3b(16,16,255))

    local s = cc.Director:getInstance():getWinSize()

    local background = cc.LayerColor:create(cc.c4b(128,128,128,255), s.width, s.height)
    ret:addChild(background, -1)

    -- RGBA 8888 image (32-bit)
    cc.Texture2D:setDefaultAlphaPixelFormat(cc.TEXTURE2_D_PIXEL_FORMAT_RGB_A8888)
    local sprite1 = cc.Sprite:create("Images/test-rgba1.png")
    sprite1:setPosition(cc.p(1*s.width/7, s.height/2+32))
    ret:addChild(sprite1, 0)

    -- remove texture from texture manager
    cc.Director:getInstance():getTextureCache():removeTexture(sprite1:getTexture())

    -- RGBA 4444 image (16-bit)
    cc.Texture2D:setDefaultAlphaPixelFormat(cc.TEXTURE2_D_PIXEL_FORMAT_RGB_A4444)
    local sprite2 = cc.Sprite:create("Images/test-rgba1.png")
    sprite2:setPosition(cc.p(2*s.width/7, s.height/2-32))
    ret:addChild(sprite2, 0)

    -- remove texture from texture manager
    cc.Director:getInstance():getTextureCache():removeTexture(sprite2:getTexture())

    -- RGB5A1 image (16-bit)
    cc.Texture2D:setDefaultAlphaPixelFormat(cc.TEXTURE2_D_PIXEL_FORMAT_RGB5_A1)
    local sprite3 = cc.Sprite:create("Images/test-rgba1.png")
    sprite3:setPosition(cc.p(3*s.width/7, s.height/2+32))
    ret:addChild(sprite3, 0)

    -- remove texture from texture manager
    cc.Director:getInstance():getTextureCache():removeTexture(sprite3:getTexture())

    -- RGB888 image
    cc.Texture2D:setDefaultAlphaPixelFormat(cc.TEXTURE2_D_PIXEL_FORMAT_RG_B888 )
    local sprite4 = cc.Sprite:create("Images/test-rgba1.png")
    sprite4:setPosition(cc.p(4*s.width/7, s.height/2-32))
    ret:addChild(sprite4, 0)

    -- remove texture from texture manager
    cc.Director:getInstance():getTextureCache():removeTexture(sprite4:getTexture())

    -- RGB565 image (16-bit)
    cc.Texture2D:setDefaultAlphaPixelFormat(cc.TEXTURE2_D_PIXEL_FORMAT_RG_B565)
    local sprite5 = cc.Sprite:create("Images/test-rgba1.png")
    sprite5:setPosition(cc.p(5*s.width/7, s.height/2+32))
    ret:addChild(sprite5, 0)

    -- remove texture from texture manager
    cc.Director:getInstance():getTextureCache():removeTexture(sprite5:getTexture())

    -- A8 image (8-bit)
    cc.Texture2D:setDefaultAlphaPixelFormat(cc.TEXTURE2_D_PIXEL_FORMAT_A8 )
    local sprite6 = cc.Sprite:create("Images/test-rgba1.png")
    sprite6:setPosition(cc.p(6*s.width/7, s.height/2-32))
    ret:addChild(sprite6, 0)

    -- remove texture from texture manager
    cc.Director:getInstance():getTextureCache():removeTexture(sprite6:getTexture())

    local  fadeout = cc.FadeOut:create(2)
    local  fadein  = cc.FadeIn:create(2)
    local  seq = cc.Sequence:create(cc.DelayTime:create(2), fadeout, fadein)
    local  seq_4ever = cc.RepeatForever:create(seq)
    local  seq_4ever2 = seq_4ever:clone()
    local  seq_4ever3 = seq_4ever:clone()
    local  seq_4ever4 = seq_4ever:clone()
    local  seq_4ever5 = seq_4ever:clone()

    sprite1:runAction(seq_4ever)
    sprite2:runAction(seq_4ever2)
    sprite3:runAction(seq_4ever3)
    sprite4:runAction(seq_4ever4)
    sprite5:runAction(seq_4ever5)

    -- restore default
    cc.Texture2D:setDefaultAlphaPixelFormat(cc.TEXTURE2_D_PIXEL_FORMAT_DEFAULT)
    print(cc.Director:getInstance():getTextureCache():getCachedTextureInfo())
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
        local cloud = cc.Sprite:create("Images/test_blend.png")
        ret:addChild(cloud, i+1, 100+i)
        cloud:setPosition(cc.p(50+25*i, 80))
        cloud:setBlendFunc(cc.blendFunc(ccb.BlendFactor.ONE, ccb.BlendFactor.ONE_MINUS_SRC_ALPHA))

        -- CENTER sprites have also alpha pre-multiplied
        -- they use by default GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA
        cloud = cc.Sprite:create("Images/test_blend.png")
        ret:addChild(cloud, i+1, 200+i)
        cloud:setPosition(cc.p(50+25*i, 160))
        cloud:setBlendFunc(cc.blendFunc(ccb.BlendFactor.ONE_MINUS_DST_COLOR , ccb.BlendFactor.ZERO))

        -- UPPER sprites are using custom blending function
        -- You can set any blend function to your sprites
        cloud = cc.Sprite:create("Images/test_blend.png")
        ret:addChild(cloud, i+1, 200+i)
        cloud:setPosition(cc.p(50+25*i, 320-80))
        cloud:setBlendFunc(cc.blendFunc(ccb.BlendFactor.SRC_ALPHA, ccb.BlendFactor.ONE))  -- additive blending
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

    local size =cc.Director:getInstance():getWinSize()

    local label = cc.Label:createWithTTF("Loading...", s_markerFeltFontPath, 32)
    label:setAnchorPoint(cc.p(0.5, 0.5))
    label:setPosition(cc.p( size.width/2, size.height/2))
    ret:addChild(label, 10)

    local  scale = cc.ScaleBy:create(0.3, 2)
    local  scale_back = scale:reverse()
    local  seq = cc.Sequence:create(scale, scale_back)
    label:runAction(cc.RepeatForever:create(seq))

    local function imageLoaded(texture)
        local director = cc.Director:getInstance()

        local sprite = cc.Sprite:createWithTexture(texture)
        sprite:setAnchorPoint(cc.p(0,0))
        ret:addChild(sprite, -1)

        local size = director:getWinSize()
        local i = m_nImageOffset * 32
        sprite:setPosition(cc.p( i % size.width, math.floor((i / size.width)) * 32 ))

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
                cc.Director:getInstance():getTextureCache():addImageAsync(
                    szSpriteName, imageLoaded)
            end
        end

        cc.Director:getInstance():getTextureCache():addImageAsync("Images/background1.jpg", imageLoaded)
        cc.Director:getInstance():getTextureCache():addImageAsync("Images/background2.jpg", imageLoaded)
        cc.Director:getInstance():getTextureCache():addImageAsync("Images/background.png", imageLoaded)
        cc.Director:getInstance():getTextureCache():addImageAsync("Images/atlastest.png", imageLoaded)
        cc.Director:getInstance():getTextureCache():addImageAsync("Images/grossini_dance_atlas.png",imageLoaded)

        ret:unscheduleUpdate()
    end

    local function onNodeEvent(event)
        if event == "enter" then
            ret:scheduleUpdateWithPriorityLua(loadImages,0)
        elseif event == "exit" then
            ret:unscheduleUpdate()
            cc.Director:getInstance():getTextureCache():removeAllTextures()
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

    local size = cc.Director:getInstance():getWinSize()

    -- The .png image MUST be power of 2 in order to create a continue effect.
    -- eg: 32x64, 512x128, 256x1024, 64x64, etc..
    local sprite = cc.Sprite:create("Images/pattern1.png", cc.rect(0,0,512,256))
    ret:addChild(sprite, -1, kTagSprite1)
    sprite:setPosition(cc.p(size.width/2,size.height/2))
    sprite:getTexture():setTexParameters(ccb.SamplerFilter.LINEAR, ccb.SamplerFilter.LINEAR, ccb.SamplerAddressMode.CLAMP_TO_EDGE, ccb.SamplerAddressMode.CLAMP_TO_EDGE)

    local  rotate = cc.RotateBy:create(4, 360)
    sprite:runAction(rotate)
    local  scale = cc.ScaleBy:create(2, 0.04)
    local  scaleBack = scale:reverse()
    local  seq = cc.Sequence:create(scale, scaleBack)
    sprite:runAction(seq)
    local function onNodeEvent(event)
        if event == "exit" then
            cc.Director:getInstance():getTextureCache():removeUnusedTextures()
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
    local ret = createTestLayer("Texture ccb.SamplerFilter.REPEAT")

    local size = cc.Director:getInstance():getWinSize()

    -- The .png image MUST be power of 2 in order to create a continue effect.
    -- eg: 32x64, 512x128, 256x1024, 64x64, etc..
    local sprite = cc.Sprite:create("Images/pattern1.png", cc.rect(0, 0, 4096, 4096))
    ret:addChild(sprite, -1, kTagSprite1)
    sprite:setPosition(cc.p(size.width/2,size.height/2))
    sprite:getTexture():setTexParameters(ccb.SamplerFilter.LINEAR, ccb.SamplerFilter.LINEAR, ccb.SamplerAddressMode.REPEAT, ccb.SamplerAddressMode.REPEAT)

    local  rotate = cc.RotateBy:create(4, 360)
    sprite:runAction(rotate)
    local  scale = cc.ScaleBy:create(2, 0.04)
    local  scaleBack = scale:reverse()
    local  seq = cc.Sequence:create(scale, scaleBack)
    sprite:runAction(seq)
    local function onNodeEvent(event)
        if event == "exit" then
            cc.Director:getInstance():getTextureCache():removeUnusedTextures()
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
    sprite = cc.Sprite:create("Images/texture512x512.png")
    if sprite ~= nil then
        cclog("OK\n")
    else
        cclog("Error\n")

        cclog("Loading 1024x1024 image...")
        sprite = cc.Sprite:create("Images/texture1024x1024.png")
        if sprite ~= nil then
            cclog("OK\n")
        else
            cclog("Error\n")
            --     @todo
            --     cclog("Loading 2048x2048 image...")
            --     sprite = cc.Sprite:create("Images/texture2048x2048.png")
            --     if( sprite )
            --         cclog("OK\n")
            --     else
            --         cclog("Error\n")
            --
            --     cclog("Loading 4096x4096 image...")
            --     sprite = cc.Sprite:create("Images/texture4096x4096.png")
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
    local ret = createTestLayer("TextureCache: remove",
                    "4 images should appear: alias, antialias, alias, antialias")
    local s = cc.Director:getInstance():getWinSize()

    local sprite = nil

    sprite = cc.Sprite:create("Images/grossinis_sister1.png")
    sprite:setPosition(cc.p(s.width/5*1, s.height/2))
    sprite:getTexture():setAliasTexParameters()
    sprite:setScale(2)
    ret:addChild(sprite)

    cc.Director:getInstance():getTextureCache():removeTexture(sprite:getTexture())

    sprite = cc.Sprite:create("Images/grossinis_sister1.png")
    sprite:setPosition(cc.p(s.width/5*2, s.height/2))
    sprite:getTexture():setAntiAliasTexParameters()
    sprite:setScale(2)
    ret:addChild(sprite)

    -- 2nd set of sprites

    sprite = cc.Sprite:create("Images/grossinis_sister2.png")
    sprite:setPosition(cc.p(s.width/5*3, s.height/2))
    sprite:getTexture():setAliasTexParameters()
    sprite:setScale(2)
    ret:addChild(sprite)

    cc.Director:getInstance():getTextureCache():removeTextureForKey("Images/grossinis_sister2.png")

    sprite = cc.Sprite:create("Images/grossinis_sister2.png")
    sprite:setPosition(cc.p(s.width/5*4, s.height/2))
    sprite:getTexture():setAntiAliasTexParameters()
    sprite:setScale(2)
    ret:addChild(sprite)
    return ret
end

-- TextureDrawAtPoint
local function TextureDrawAtPoint()
    local m_pTex1 = nil
    local m_pTex2F = nil
    local ret = createTestLayer("Texture2D: drawAtPoint",
                                "draws 2 textures using drawAtPoint")

    local function draw(transform, globalZOrder)
        local director = cc.Director:getInstance()
        assert(nil ~= director, "Director is null when setting matrix stack")
        director:pushMatrix(cc.MATRIX_STACK_TYPE.MODELVIEW)
        director:loadMatrix(cc.MATRIX_STACK_TYPE.MODELVIEW, transform)

        local s = cc.Director:getInstance():getWinSize()
    
        m_pTex1:drawAtPoint(cc.p(s.width/2-50, s.height/2 - 50), globalZOrder)
        m_pTex2F:drawAtPoint(cc.p(s.width/2+50, s.height/2 - 50), globalZOrder)
    
        director:popMatrix(cc.MATRIX_STACK_TYPE.MODELVIEW)
    end

    m_pTex1 = cc.Director:getInstance():getTextureCache():addImage("Images/grossinis_sister1.png")
    m_pTex2F = cc.Director:getInstance():getTextureCache():addImage("Images/grossinis_sister2.png")

    m_pTex1:retain()
    m_pTex2F:retain()

    local luaNode = cc.LuaNode:create()
    luaNode:setContentSize(cc.size(256, 256))
    luaNode:setAnchorPoint(cc.p(0,0))
    luaNode:registerScriptDrawHandler(draw)
    ret:addChild(luaNode)

    local function onNodeEvent(event)
        if event == "exit" then
            m_pTex1:release()
            m_pTex2F:release()
        end
    end

    ret:registerScriptHandler(onNodeEvent)

    return ret
end

-- TextureDrawInRect

local function TextureDrawInRect()
    local m_pTex1 = nil
    local m_pTex2F = nil
    local ret = createTestLayer("Texture2D: drawInRect",
                                "draws 2 textures using drawInRect")
    local function draw(transform, globalZOrder)
        local director = cc.Director:getInstance()
        assert(nullptr ~= director, "Director is null when setting matrix stack")
        director:pushMatrix(cc.MATRIX_STACK_TYPE.MODELVIEW)
        director:loadMatrix(cc.MATRIX_STACK_TYPE.MODELVIEW, transform)

        local s = cc.Director:getInstance():getWinSize()

        local rect1 = cc.rect( s.width/2 - 80, 20, m_pTex1:getContentSize().width * 0.5, m_pTex1:getContentSize().height *2 )
        local rect2 = cc.rect( s.width/2 + 80, s.height/2, m_pTex1:getContentSize().width * 2, m_pTex1:getContentSize().height * 0.5 )

        m_pTex1:drawInRect(rect1, globalZOrder)
        m_pTex2F:drawInRect(rect2, globalZOrder)
    end

    m_pTex1 = cc.Director:getInstance():getTextureCache():addImage("Images/grossinis_sister1.png")
    m_pTex2F = cc.Director:getInstance():getTextureCache():addImage("Images/grossinis_sister2.png")

    m_pTex1:retain()
    m_pTex2F:retain()

    local luaNode = cc.LuaNode:create()
    luaNode:setContentSize(cc.size(256, 256))
    luaNode:setAnchorPoint(cc.p(0,0))
    luaNode:registerScriptDrawHandler(draw)
    ret:addChild(luaNode)

    local function onNodeEvent(event)
        if event == "exit" then
            m_pTex1:release()
            m_pTex2F:release()
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

    cc.MenuItemFont:setFontSize(24)

    local function updateImage(tag,sender)
        if m_pBackground ~= nil then
            cclog("updateImage"..tag)
            m_pBackground:removeFromParent(true)
        end
        cc.Director:getInstance():getTextureCache():removeUnusedTextures()

        local targetPlatform = cc.Application:getInstance():getTargetPlatform()
        local file = ""

        if tag == 0 then
                file = "Images/test_image.png"
            elseif tag == 1 then
                file = "Images/test_image_rgba8888.pvr"
            elseif tag == 2 then
                file = "Images/test_image_rgb888.pvr"
            elseif tag == 3 then
                file = "Images/test_image_rgba4444.pvr"
            elseif tag == 4 then
                file = "Images/test_image_a8.pvr"
            end

        m_pBackground = cc.Sprite:create(file)
        ret:addChild(m_pBackground, -10)

        m_pBackground:setVisible(false)

        local s = cc.Director:getInstance():getWinSize()
        m_pBackground:setPosition(cc.p(s.width/2, s.height/2))
    end

    local item1 = cc.MenuItemFont:create("PNG")
    item1:registerScriptTapHandler(updateImage)
    item1:setTag(0)

    local item2 = cc.MenuItemFont:create("RGBA8")
    item2:registerScriptTapHandler(updateImage)
    item2:setTag(1)

    local item3 = cc.MenuItemFont:create("RGB8")
    item3:registerScriptTapHandler(updateImage)
    item3:setTag(2)

    local item4 = cc.MenuItemFont:create("RGBA4")
    item4:registerScriptTapHandler(updateImage)
    item4:setTag(3)

    local item5 = cc.MenuItemFont:create("A8")
    item5:registerScriptTapHandler(updateImage)
    item5:setTag(4)

    local menu = cc.Menu:create(item1, item2, item3, item4, item5)
    menu:alignItemsHorizontally()

    ret:addChild(menu)

    local warmup = cc.MenuItemFont:create("warm up texture")

    local function changeBackgroundVisible(tag, sender)
        if m_pBackground ~= nil then
            cclog("changeBackgroundVisible")
            m_pBackground:setVisible(true)
        end
    end

    warmup:registerScriptTapHandler(changeBackgroundVisible)
    local menu2 = cc.Menu:create(warmup)

    menu2:alignItemsHorizontally()

    ret:addChild(menu2)
    local s = cc.Director:getInstance():getWinSize()

    menu2:setPosition(cc.p(s.width/2, s.height/4))
    return ret
end

-- TexturePVRv3Premult
local function TexturePVRv3Premult()
    local ret = createTestLayer("PVRv3 Premult Flag",
                                "All images should look exactly the same")

    local function transformSprite(sprite)
        local fade = cc.FadeOut:create(2)
        local dl = cc.DelayTime:create(2)
        local fadein = fade:reverse()
        local seq = cc.Sequence:create(fade, fadein, dl)
        local repeatAction = cc.RepeatForever:create(seq)
        sprite:runAction(repeatAction)
    end

    local size = cc.Director:getInstance():getWinSize()

    local background = cc.LayerColor:create(cc.c4b(128,128,128,255), size.width, size.height)
    ret:addChild(background, -1)


    -- PVR premultiplied
    local pvr1 = cc.Sprite:create("Images/grossinis_sister1-testalpha_premult.pvr")
    ret:addChild(pvr1, 0)
    pvr1:setPosition(cc.p(size.width/4*1, size.height/2))
    transformSprite(pvr1)

    -- PVR non-premultiplied
    local pvr2 = cc.Sprite:create("Images/grossinis_sister1-testalpha_nopremult.pvr")
    ret:addChild(pvr2, 0)
    pvr2:setPosition(cc.p(size.width/4*2, size.height/2))
    transformSprite(pvr2)

    -- PNG
    cc.Texture2D:setDefaultAlphaPixelFormat(cc.TEXTURE2_D_PIXEL_FORMAT_RGB_A8888)
    cc.Director:getInstance():getTextureCache():removeTextureForKey("Images/grossinis_sister1-testalpha.png")
    local png = cc.Sprite:create("Images/grossinis_sister1-testalpha.png")
    ret:addChild(png, 0)
    png:setPosition(cc.p(size.width/4*3, size.height/2))
    transformSprite(png)
    return ret
end


function Texture2dTestMain()
    cclog("Texture2dTestMain")
    Helper.index = 1
    local scene = cc.Scene:create()
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
    Helper.index = 1
    
    scene:addChild(TextureMemoryAlloc())
    scene:addChild(CreateBackMenuItem())
    return scene
end
