/****************************************************************************
 Copyright (c) 2012 cocos2d-x.org
 Copyright (c) 2013-2014 Chukong Technologies Inc.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

// local import
#include "Texture2dTest.h"
#include "../testResource.h"

USING_NS_CC;

enum {
    kTagLabel = 1,
    kTagSprite1 = 2,
    kTagSprite2 = 3,
};

Texture2DTests::Texture2DTests()
{
    ADD_TEST_CASE(TextureMipMap);
    ADD_TEST_CASE(TextureMemoryAlloc);
    ADD_TEST_CASE(TextureAlias);
    ADD_TEST_CASE(TexturePVRMipMap);
    ADD_TEST_CASE(TexturePVRMipMap2);
    ADD_TEST_CASE(TexturePVRNonSquare);
    ADD_TEST_CASE(TexturePVRNPOT4444);
    ADD_TEST_CASE(TexturePVRNPOT8888);
    ADD_TEST_CASE(TexturePVRTest);
    ADD_TEST_CASE(TexturePVR2BPP);
    ADD_TEST_CASE(TexturePVR2BPPv3);
    ADD_TEST_CASE(TexturePVR4BPP);
    ADD_TEST_CASE(TexturePVR4BPPv3);
    ADD_TEST_CASE(TexturePVRII4BPPv3);
    ADD_TEST_CASE(TexturePVRRGBA8888);
    ADD_TEST_CASE(TexturePVRRGBA8888v3);
    ADD_TEST_CASE(TexturePVRBGRA8888);
    ADD_TEST_CASE(TexturePVRBGRA8888v3);
    ADD_TEST_CASE(TexturePVRRGBA4444);
    ADD_TEST_CASE(TexturePVRRGBA4444v3);
    ADD_TEST_CASE(TexturePVRRGBA4444GZ);
    ADD_TEST_CASE(TexturePVRRGBA4444CCZ);
    ADD_TEST_CASE(TexturePVRRGBA5551);
    ADD_TEST_CASE(TexturePVRRGBA5551v3);
    ADD_TEST_CASE(TexturePVRRGB565);
    ADD_TEST_CASE(TexturePVRRGB565v3);
    ADD_TEST_CASE(TexturePVRRGB888);
    ADD_TEST_CASE(TexturePVRRGB888v3);
    ADD_TEST_CASE(TexturePVRA8);
    ADD_TEST_CASE(TexturePVRA8v3);
    ADD_TEST_CASE(TexturePVRI8);
    ADD_TEST_CASE(TexturePVRI8v3);
    ADD_TEST_CASE(TexturePVRAI88);
    ADD_TEST_CASE(TexturePVRAI88v3);
    
    ADD_TEST_CASE(TexturePVRv3Premult);
    
    ADD_TEST_CASE(TexturePVRBadEncoding);
    ADD_TEST_CASE(TexturePNG);
    ADD_TEST_CASE(TextureJPEG);
    ADD_TEST_CASE(TextureTIFF);
    ADD_TEST_CASE(TextureTGA);
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WINRT)
    ADD_TEST_CASE(TextureWEBP);
    ADD_TEST_CASE(TextureWEBPNoAlpha)
#endif
    ADD_TEST_CASE(TexturePixelFormat);
    ADD_TEST_CASE(TextureBlend);
    ADD_TEST_CASE(TextureAsync);
    ADD_TEST_CASE(TextureGlClamp);
    ADD_TEST_CASE(TextureGlRepeat);
    ADD_TEST_CASE(TextureSizeTest);
    ADD_TEST_CASE(TextureCache1);
    ADD_TEST_CASE(TextureDrawAtPoint);
    ADD_TEST_CASE(TextureDrawInRect);
    
    ADD_TEST_CASE(TextureETC1);
    
    ADD_TEST_CASE(TextureS3TCDxt1);
    ADD_TEST_CASE(TextureS3TCDxt3);
    ADD_TEST_CASE(TextureS3TCDxt5);
    ADD_TEST_CASE(TextureS3TCWithNoMipmaps);
    
    ADD_TEST_CASE(TextureATITCRGB);
    ADD_TEST_CASE(TextureATITCExplicit);
    ADD_TEST_CASE(TextureATITCInterpolated);
    
    ADD_TEST_CASE(TextureConvertRGB888);
    ADD_TEST_CASE(TextureConvertRGBA8888);
    ADD_TEST_CASE(TextureConvertI8);
    ADD_TEST_CASE(TextureConvertAI88);
};

//------------------------------------------------------------------
//
// TextureDemo
//
//------------------------------------------------------------------
void TextureDemo::onEnter()
{
    TestCase::onEnter();

    auto col = LayerColor::create(Color4B(128,128,128,255));
    addChild(col, -10);

    auto textureCache = Director::getInstance()->getTextureCache();
    log("%s\n", textureCache->getCachedTextureInfo().c_str());
}

TextureDemo::~TextureDemo()
{
    auto textureCache = Director::getInstance()->getTextureCache();
    textureCache->removeUnusedTextures();
    log("%s\n", textureCache->getCachedTextureInfo().c_str());
}

//------------------------------------------------------------------
//
// TextureTIFF
//
//------------------------------------------------------------------

void TextureTIFF::onEnter()
{
    TextureDemo::onEnter();
    auto s = Director::getInstance()->getWinSize();

    auto img = Sprite::create("Images/test_image.tiff");
    img->setPosition(Vec2( s.width/2.0f, s.height/2.0f));
    this->addChild(img);

    log("%s\n", Director::getInstance()->getTextureCache()->getCachedTextureInfo().c_str());
}

std::string TextureTIFF::title() const
{
    return "TIFF Test";
}


//------------------------------------------------------------------
//
// TextureTGA
//
//------------------------------------------------------------------

void TextureTGA::onEnter()
{
    TextureDemo::onEnter();
    auto s = Director::getInstance()->getWinSize();
    
    auto img = Sprite::create("TileMaps/levelmap.tga");
    img->setPosition(Vec2( s.width/2.0f, s.height/2.0f));
    this->addChild(img);
    log("%s\n", Director::getInstance()->getTextureCache()->getCachedTextureInfo().c_str());
}

std::string TextureTGA::title() const
{
    return "TGA Test";
}

//------------------------------------------------------------------
//
// TexturePNG
//
//------------------------------------------------------------------
void TexturePNG::onEnter()
{
    TextureDemo::onEnter();    

    auto s = Director::getInstance()->getWinSize();

    auto img = Sprite::create("Images/test_image.png");
    img->setPosition(Vec2( s.width/2.0f, s.height/2.0f));
    addChild(img);
    log("%s\n", Director::getInstance()->getTextureCache()->getCachedTextureInfo().c_str());
    
    // Test PNG files with different pixel formats
    // grayscale without alpha
    auto i8 = Sprite::create("Images/test_image_i8.png");
    i8->setPosition(s.width/4.0f, s.height/4.0f);
    addChild(i8);
    
    // grayscale with alpha
    auto ai88 = Sprite::create("Images/test_image_ai88.png");
    ai88->setPosition(s.width / 4.0f, s.height * 3.0f / 4.0f);
    addChild(ai88);
    
    // rgb without alpha
    auto rgb888 = Sprite::create("Images/test_image_rgb888.png");
    rgb888->setPosition(s.width * 3.0f / 4.0f, s.height / 4.0f);
    addChild(rgb888);
    
    // rgba with alpha
    auto rgba8888 = Sprite::create("Images/test_image_rgba8888.png");
    rgba8888->setPosition(s.width * 3.0f / 4.0f, s.height * 3.0f / 4.0f);
    addChild(rgba8888);
}

std::string TexturePNG::title() const
{
    return "PNG Test";
}

std::string TexturePNG::subtitle() const
{
    return "LB:I8, LT:AI8\nRB:RGB888, RT: RGBA8888";
}

//------------------------------------------------------------------
//
// TextureJPEG
//
//------------------------------------------------------------------
void TextureJPEG::onEnter()
{
    TextureDemo::onEnter();
    auto s = Director::getInstance()->getWinSize();
    
    auto img = Sprite::create("Images/test_image.jpeg");
    img->setPosition(Vec2( s.width/2.0f, s.height/2.0f));
    addChild(img);
    log("%s\n", Director::getInstance()->getTextureCache()->getCachedTextureInfo().c_str());
}

std::string TextureJPEG::title() const
{
    return "JPEG Test";
}

//------------------------------------------------------------------
//
// TextureWEBP
//
//------------------------------------------------------------------
void TextureWEBP::onEnter()
{
    TextureDemo::onEnter();
    auto s = Director::getInstance()->getWinSize();
    
    auto img = Sprite::create("Images/test_image.webp");
    img->setPosition(Vec2( s.width/2.0f, s.height/2.0f));
    addChild(img);
    log("%s\n", Director::getInstance()->getTextureCache()->getCachedTextureInfo().c_str());
    Texture2D* texture = Director::getInstance()->getTextureCache()->getTextureForKey("Images/test_image.webp");
    log("pixel format:%d, premultiplied alpha:%d\n", texture->getPixelFormat(), texture->hasPremultipliedAlpha());
}

std::string TextureWEBP::title() const
{
    return "WEBP with alpha Test";
}

//------------------------------------------------------------------
//
// TextureWEBPNoAlpha
//
//------------------------------------------------------------------
void TextureWEBPNoAlpha::onEnter()
{
    TextureDemo::onEnter();
    auto s = Director::getInstance()->getWinSize();
    
    auto img = Sprite::create("Images/test_image_no_alpha.webp");
    img->setPosition(Vec2( s.width/2.0f, s.height/2.0f));
    addChild(img);
    log("%s\n", Director::getInstance()->getTextureCache()->getCachedTextureInfo().c_str());
    Texture2D* texture = Director::getInstance()->getTextureCache()->getTextureForKey("Images/test_image_no_alpha.webp");
    log("pixel format:%d, premultiplied alpha:%d\n", texture->getPixelFormat(), texture->hasPremultipliedAlpha());
}

std::string TextureWEBPNoAlpha::title() const
{
    return "WEBP without alpha Test";
}

//------------------------------------------------------------------
//
// TextureMipMap
//
//------------------------------------------------------------------
void TextureMipMap::onEnter()
{
    TextureDemo::onEnter();
    auto s = Director::getInstance()->getWinSize();

    auto texture0 = Director::getInstance()->getTextureCache()->addImage("Images/grossini_dance_atlas.png");
    texture0->generateMipmap();
    Texture2D::TexParams texParams = { GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE };
    texture0->setTexParameters(texParams);

    auto texture1 = Director::getInstance()->getTextureCache()->addImage("Images/grossini_dance_atlas_nomipmap.png");

    auto img0 = Sprite::createWithTexture(texture0);
    img0->setTextureRect(Rect(85, 121, 85, 121));
    img0->setPosition(Vec2( s.width/3.0f, s.height/2.0f));
    addChild(img0);

    auto img1 = Sprite::createWithTexture(texture1);
    img1->setTextureRect(Rect(85, 121, 85, 121));
    img1->setPosition(Vec2( 2*s.width/3.0f, s.height/2.0f));
    addChild(img1);
    
    
    auto scale1 = EaseOut::create(ScaleBy::create(4, 0.01f), 3);
    auto sc_back = scale1->reverse();
    
    auto scale2 = scale1->clone();
    auto sc_back2 = scale2->reverse();

    img0->runAction(RepeatForever::create(Sequence::create(scale1, sc_back, nullptr)));
    img1->runAction(RepeatForever::create(Sequence::create(scale2, sc_back2, nullptr)));
    log("%s\n", Director::getInstance()->getTextureCache()->getCachedTextureInfo().c_str());
}

std::string TextureMipMap::title() const
{
    return "Texture Mipmap";
}

std::string TextureMipMap::subtitle() const
{
    return "Left image uses mipmap. Right image doesn't";
}

//------------------------------------------------------------------
//
// TexturePVRMipMap
// To generate PVR images read this article:
// http://developer.apple.com/iphone/library/qa/qa2008/qa1611.html
//
//------------------------------------------------------------------
void TexturePVRMipMap::onEnter()
{
    TextureDemo::onEnter();
    auto s = Director::getInstance()->getWinSize();

    auto imgMipMap = Sprite::create("Images/logo-mipmap.pvr");
    if( imgMipMap )
    {
        imgMipMap->setPosition(Vec2( s.width/2.0f-100, s.height/2.0f));
        addChild(imgMipMap);

        // support mipmap filtering
        Texture2D::TexParams texParams = { GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE };
        imgMipMap->getTexture()->setTexParameters(texParams);
    }

    auto img = Sprite::create("Images/logo-nomipmap.pvr");
    if( img )
    {
        img->setPosition(Vec2( s.width/2.0f+100, s.height/2.0f));
        addChild(img);

        auto scale1 = EaseOut::create(ScaleBy::create(4, 0.01f), 3);
        auto sc_back = scale1->reverse();

        auto scale2 = scale1->clone();
        auto sc_back2 = scale2->reverse();
        
        imgMipMap->runAction(RepeatForever::create(Sequence::create(scale1, sc_back, nullptr)));
        img->runAction(RepeatForever::create(Sequence::create(scale2, sc_back2, nullptr)));
    }
    log("%s\n", Director::getInstance()->getTextureCache()->getCachedTextureInfo().c_str());
}

std::string TexturePVRMipMap::title() const
{
    return "PVRTC MipMap Test";
}
std::string TexturePVRMipMap::subtitle() const
{
    return "Left image uses mipmap. Right image doesn't";
}

//------------------------------------------------------------------
//
// TexturePVRMipMap2
//
//------------------------------------------------------------------
void TexturePVRMipMap2::onEnter()
{
    TextureDemo::onEnter();
    auto s = Director::getInstance()->getWinSize();
    
    auto imgMipMap = Sprite::create("Images/test_image_rgba4444_mipmap.pvr");
    imgMipMap->setPosition(Vec2( s.width/2.0f-100, s.height/2.0f));
    addChild(imgMipMap);
    
    // support mipmap filtering
    Texture2D::TexParams texParams = { GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE };
    imgMipMap->getTexture()->setTexParameters(texParams);

    auto img = Sprite::create("Images/test_image.png");
    img->setPosition(Vec2( s.width/2.0f+100, s.height/2.0f));
    addChild(img);
    
    auto scale1 = EaseOut::create(ScaleBy::create(4, 0.01f), 3);
    auto sc_back = scale1->reverse();

    auto scale2 = scale1->clone();
    auto sc_back2 = scale2->reverse();
    
    imgMipMap->runAction(RepeatForever::create(Sequence::create(scale1, sc_back, nullptr)));
    img->runAction(RepeatForever::create(Sequence::create(scale2, sc_back2, nullptr)));
    log("%s\n", Director::getInstance()->getTextureCache()->getCachedTextureInfo().c_str());
}

std::string TexturePVRMipMap2::title() const
{
    return "PVR MipMap Test #2";
}

std::string TexturePVRMipMap2::subtitle() const
{
    return "Left image uses mipmap. Right image doesn't";
}

//------------------------------------------------------------------
//
// TexturePVR2BPP
// Image generated using PVRTexTool:
// http://www.imgtec.com/powervr/insider/powervr-pvrtextool.asp
//
//------------------------------------------------------------------
void TexturePVR2BPP::onEnter()
{
    TextureDemo::onEnter();
    auto s = Director::getInstance()->getWinSize();

    auto img = Sprite::create("Images/test_image_pvrtc2bpp.pvr");
    
    if( img )
    {
        img->setPosition(Vec2( s.width/2.0f, s.height/2.0f));
        addChild(img);
    }
    log("%s\n", Director::getInstance()->getTextureCache()->getCachedTextureInfo().c_str());
}

std::string TexturePVR2BPP::title() const
{
    return "PVR TC 2bpp Test";
}

//------------------------------------------------------------------
//
// TexturePVR
// To generate PVR images read this article:
// http://developer.apple.com/iphone/library/qa/qa2008/qa1611.html
//
//------------------------------------------------------------------
void TexturePVRTest::onEnter()
{
    TextureDemo::onEnter();
    auto s = Director::getInstance()->getWinSize();
    
    auto img = Sprite::create("Images/test_image.pvr");
    
    if( img )
    {
        img->setPosition(Vec2( s.width/2.0f, s.height/2.0f));
        addChild(img);
    }
    else
    {
        log("This test is not supported.");
    }
    log("%s\n", Director::getInstance()->getTextureCache()->getCachedTextureInfo().c_str());

}

std::string TexturePVRTest::title() const
{
    return "PVR TC 4bpp Test #2";
}

//------------------------------------------------------------------
//
// TexturePVR4BPP
// Image generated using PVRTexTool:
// http://www.imgtec.com/powervr/insider/powervr-pvrtextool.asp
//
//------------------------------------------------------------------
void TexturePVR4BPP::onEnter()
{
    TextureDemo::onEnter();
    auto s = Director::getInstance()->getWinSize();

    auto img = Sprite::create("Images/test_image_pvrtc4bpp.pvr");
    
    if( img )
    {
        img->setPosition(Vec2( s.width/2.0f, s.height/2.0f));
        addChild(img);
    }
    else
    {
        log("This test is not supported in cocos2d-mac");
    }
    log("%s\n", Director::getInstance()->getTextureCache()->getCachedTextureInfo().c_str());
}

std::string TexturePVR4BPP::title() const
{
    return "PVR TC 4bpp Test #3";
}

//------------------------------------------------------------------
//
// TexturePVRRGBA8888
// Image generated using PVRTexTool:
// http://www.imgtec.com/powervr/insider/powervr-pvrtextool.asp
//
//------------------------------------------------------------------
void TexturePVRRGBA8888::onEnter()
{
    TextureDemo::onEnter();
    auto s = Director::getInstance()->getWinSize();

    auto img = Sprite::create("Images/test_image_rgba8888.pvr");
    img->setPosition(Vec2( s.width/2.0f, s.height/2.0f));
    addChild(img);
    log("%s\n", Director::getInstance()->getTextureCache()->getCachedTextureInfo().c_str());
}

std::string TexturePVRRGBA8888::title() const
{
    return "PVR + RGBA  8888 Test";
}

//------------------------------------------------------------------
//
// TexturePVRBGRA8888
// Image generated using PVRTexTool:
// http://www.imgtec.com/powervr/insider/powervr-pvrtextool.asp
//
//------------------------------------------------------------------
void TexturePVRBGRA8888::onEnter()
{
    TextureDemo::onEnter();
    auto s = Director::getInstance()->getWinSize();
    
    auto img = Sprite::create("Images/test_image_bgra8888.pvr");
    if( img )
    {
        img->setPosition(Vec2( s.width/2.0f, s.height/2.0f));
        addChild(img);
    }
    else
    {
        log("BGRA8888 images are not supported");
    }
    log("%s\n", Director::getInstance()->getTextureCache()->getCachedTextureInfo().c_str());
}

std::string TexturePVRBGRA8888::title() const
{
    return "PVR + BGRA 8888 Test";
}

//------------------------------------------------------------------
//
// TexturePVRRGBA5551
// Image generated using PVRTexTool:
// http://www.imgtec.com/powervr/insider/powervr-pvrtextool.asp
//
//------------------------------------------------------------------
void TexturePVRRGBA5551::onEnter()
{
    TextureDemo::onEnter();
    auto s = Director::getInstance()->getWinSize();
    
    auto img = Sprite::create("Images/test_image_rgba5551.pvr");
    img->setPosition(Vec2( s.width/2.0f, s.height/2.0f));
    addChild(img);
    log("%s\n", Director::getInstance()->getTextureCache()->getCachedTextureInfo().c_str());
}

std::string TexturePVRRGBA5551::title() const
{
    return "PVR + RGBA 5551 Test";
}

//------------------------------------------------------------------
//
// TexturePVRRGBA4444
// Image generated using PVRTexTool:
// http://www.imgtec.com/powervr/insider/powervr-pvrtextool.asp
//
//------------------------------------------------------------------
void TexturePVRRGBA4444::onEnter()
{
    TextureDemo::onEnter();
    auto s = Director::getInstance()->getWinSize();
    
    auto img = Sprite::create("Images/test_image_rgba4444.pvr");
    img->setPosition(Vec2( s.width/2.0f, s.height/2.0f));
    addChild(img);
    log("%s\n", Director::getInstance()->getTextureCache()->getCachedTextureInfo().c_str());
}

std::string TexturePVRRGBA4444::title() const
{
    return "PVR + RGBA 4444 Test";
}

//------------------------------------------------------------------
//
// TexturePVRRGBA4444GZ
// Image generated using PVRTexTool:
// http://www.imgtec.com/powervr/insider/powervr-pvrtextool.asp
//
//------------------------------------------------------------------
void TexturePVRRGBA4444GZ::onEnter()
{
    TextureDemo::onEnter();
    auto s = Director::getInstance()->getWinSize();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    // android can not pack .gz file into apk file
    auto img = Sprite::create("Images/test_image_rgba4444.pvr");
#else
    auto img = Sprite::create("Images/test_image_rgba4444.pvr.gz");
#endif
    img->setPosition(Vec2( s.width/2.0f, s.height/2.0f));
    addChild(img);
    log("%s\n", Director::getInstance()->getTextureCache()->getCachedTextureInfo().c_str());
}

std::string TexturePVRRGBA4444GZ::title() const
{
    return "PVR + RGBA 4444 + GZ Test";
}

std::string TexturePVRRGBA4444GZ::subtitle() const
{
    return "This is a gzip PVR image";
}

//------------------------------------------------------------------
//
// TexturePVRRGBA4444CCZ
// Image generated using PVRTexTool:
// http://www.imgtec.com/powervr/insider/powervr-pvrtextool.asp
//
//------------------------------------------------------------------
void TexturePVRRGBA4444CCZ::onEnter()
{
    TextureDemo::onEnter();
    auto s = Director::getInstance()->getWinSize();

    auto img = Sprite::create("Images/test_image_rgba4444.pvr.ccz");
    img->setPosition(Vec2( s.width/2.0f, s.height/2.0f));
    addChild(img);    
    log("%s\n", Director::getInstance()->getTextureCache()->getCachedTextureInfo().c_str());
}

std::string TexturePVRRGBA4444CCZ::title() const
{
    return "PVR + RGBA 4444 + CCZ Test";
}

std::string TexturePVRRGBA4444CCZ::subtitle() const
{
    return "This is a ccz PVR image";
}

//------------------------------------------------------------------
//
// TexturePVRRGB565
// Image generated using PVRTexTool:
// http://www.imgtec.com/powervr/insider/powervr-pvrtextool.asp
//
//------------------------------------------------------------------
void TexturePVRRGB565::onEnter()
{
    TextureDemo::onEnter();
    auto s = Director::getInstance()->getWinSize();
    
    auto img = Sprite::create("Images/test_image_rgb565.pvr");
    img->setPosition(Vec2( s.width/2.0f, s.height/2.0f));
    addChild(img);
    log("%s\n", Director::getInstance()->getTextureCache()->getCachedTextureInfo().c_str());
}

std::string TexturePVRRGB565::title() const
{
    return "PVR + RGB 565 Test";
}

// TexturePVR RGB888
// Image generated using PVRTexTool:
// http://www.imgtec.com/powervr/insider/powervr-pvrtextool.asp
void TexturePVRRGB888::onEnter()
{
    TextureDemo::onEnter();
    auto s = Director::getInstance()->getWinSize();

    auto img = Sprite::create("Images/test_image_rgb888.pvr");
    if (img != nullptr)
    {
        img->setPosition(Vec2( s.width/2.0f, s.height/2.0f));
        addChild(img);
    }

    log("%s\n", Director::getInstance()->getTextureCache()->getCachedTextureInfo().c_str());

}
std::string TexturePVRRGB888::title() const
{
    return "PVR + RGB 888 Test";
}

//------------------------------------------------------------------
//
// TexturePVRA8
// Image generated using PVRTexTool:
// http://www.imgtec.com/powervr/insider/powervr-pvrtextool.asp
//
//------------------------------------------------------------------
void TexturePVRA8::onEnter()
{
    TextureDemo::onEnter();
    auto s = Director::getInstance()->getWinSize();
    
    auto img = Sprite::create("Images/test_image_a8.pvr");
    img->setPosition(Vec2( s.width/2.0f, s.height/2.0f));
    addChild(img);
    log("%s\n", Director::getInstance()->getTextureCache()->getCachedTextureInfo().c_str());

}

std::string TexturePVRA8::title() const
{
    return "PVR + A8 Test";
}

//------------------------------------------------------------------
//
// TexturePVRI8
// Image generated using PVRTexTool:
// http://www.imgtec.com/powervr/insider/powervr-pvrtextool.asp
//
//------------------------------------------------------------------
void TexturePVRI8::onEnter()
{
    TextureDemo::onEnter();
    auto s = Director::getInstance()->getWinSize();

    auto img = Sprite::create("Images/test_image_i8.pvr");
    img->setPosition(Vec2( s.width/2.0f, s.height/2.0f));
    addChild(img);
    log("%s\n", Director::getInstance()->getTextureCache()->getCachedTextureInfo().c_str());
}

std::string TexturePVRI8::title() const
{
    return "PVR + I8 Test";
}

//------------------------------------------------------------------
//
// TexturePVRAI88
// Image generated using PVRTexTool:
// http://www.imgtec.com/powervr/insider/powervr-pvrtextool.asp
//
//------------------------------------------------------------------
void TexturePVRAI88::onEnter()
{
    TextureDemo::onEnter();
    auto s = Director::getInstance()->getWinSize();
    
    auto img = Sprite::create("Images/test_image_ai88.pvr");
    img->setPosition(Vec2( s.width/2.0f, s.height/2.0f));
    addChild(img);
    log("%s\n", Director::getInstance()->getTextureCache()->getCachedTextureInfo().c_str());
}

std::string TexturePVRAI88::title() const
{
    return "PVR + AI88 Test";
}

// TexturePVR2BPPv3
void TexturePVR2BPPv3::onEnter()
{
    TextureDemo::onEnter();
    auto s = Director::getInstance()->getWinSize();
    
    auto img = Sprite::create("Images/test_image_pvrtc2bpp_v3.pvr");
    
    if (img)
    {
        img->setPosition(Vec2(s.width/2.0f, s.height/2.0f));
        addChild(img);
    }
    
    log("%s\n", Director::getInstance()->getTextureCache()->getCachedTextureInfo().c_str());
}

std::string TexturePVR2BPPv3::title() const
{
    return "PVR TC 2bpp Test";
}

std::string TexturePVR2BPPv3::subtitle() const
{
    return "Testing PVR File Format v3";
}

// TexturePVRII2BPPv3
void TexturePVRII2BPPv3::onEnter()
{
    TextureDemo::onEnter();
    auto s = Director::getInstance()->getWinSize();
    
    auto img = Sprite::create("Images/test_image_pvrtcii2bpp_v3.pvr");
    
    if (img)
    {
        img->setPosition(Vec2(s.width/2.0f, s.height/2.0f));
        addChild(img);
    }
    
    log("%s\n", Director::getInstance()->getTextureCache()->getCachedTextureInfo().c_str());
}

std::string TexturePVRII2BPPv3::title() const
{
    return "PVR TC II 2bpp Test";
}

std::string TexturePVRII2BPPv3::subtitle() const
{
    return "Testing PVR File Format v3";
}

// TexturePVR4BPPv3
void TexturePVR4BPPv3::onEnter()
{
    TextureDemo::onEnter();
    auto s = Director::getInstance()->getWinSize();
    
    auto img = Sprite::create("Images/test_image_pvrtc4bpp_v3.pvr");
    
    if (img)
    {
        img->setPosition(Vec2(s.width/2.0f, s.height/2.0f));
        addChild(img);
    }
    else
    {
        log("This test is not supported");
    }
    
    log("%s\n", Director::getInstance()->getTextureCache()->getCachedTextureInfo().c_str());
}

std::string TexturePVR4BPPv3::title() const
{
    return "PVR TC 4bpp Test";
}

std::string TexturePVR4BPPv3::subtitle() const
{
    return "Testing PVR File Format v3";
}

// TexturePVRII4BPPv3

// Image generated using PVRTexTool:
// http://www.imgtec.com/powervr/insider/powervr-pvrtextool.asp

void TexturePVRII4BPPv3::onEnter()
{
    TextureDemo::onEnter();
    auto s = Director::getInstance()->getWinSize();
    
    auto img = Sprite::create("Images/test_image_pvrtcii4bpp_v3.pvr");
    
    if (img)
    {
        img->setPosition(Vec2(s.width/2.0f, s.height/2.0f));
        addChild(img);
    }
    else
    {
        log("This test is not supported");
    }
    
    log("%s\n", Director::getInstance()->getTextureCache()->getCachedTextureInfo().c_str());
}

std::string TexturePVRII4BPPv3::title() const
{
    return "PVR TC II 4bpp Test";
}

std::string TexturePVRII4BPPv3::subtitle() const
{
    return "Testing PVR File Format v3";
}

// TexturePVRRGBA8888v3
void TexturePVRRGBA8888v3::onEnter()
{
    TextureDemo::onEnter();
    auto s = Director::getInstance()->getWinSize();
    
    auto img = Sprite::create("Images/test_image_rgba8888_v3.pvr");
    
    if (img)
    {
        img->setPosition(Vec2(s.width/2.0f, s.height/2.0f));
        addChild(img);
    }
    
    log("%s\n", Director::getInstance()->getTextureCache()->getCachedTextureInfo().c_str());
}

std::string TexturePVRRGBA8888v3::title() const
{
    return "PVR + RGBA  8888 Test";
}

std::string TexturePVRRGBA8888v3::subtitle() const
{
    return "Testing PVR File Format v3";
}

// TexturePVRBGRA8888v3
void TexturePVRBGRA8888v3::onEnter()
{
    TextureDemo::onEnter();
    auto s = Director::getInstance()->getWinSize();
    
    auto img = Sprite::create("Images/test_image_bgra8888_v3.pvr");
    
    if (img)
    {
        img->setPosition(Vec2(s.width/2.0f, s.height/2.0f));
        addChild(img);
    }
    else
    {
        log("BGRA images are not supported");
    }
    
    log("%s\n", Director::getInstance()->getTextureCache()->getCachedTextureInfo().c_str());
}

std::string TexturePVRBGRA8888v3::title() const
{
    return "PVR + BGRA 8888 Test";
}

std::string TexturePVRBGRA8888v3::subtitle() const
{
    return "Testing PVR File Format v3";
}

// TexturePVRRGBA5551v3
void TexturePVRRGBA5551v3::onEnter()
{
    TextureDemo::onEnter();
    auto s = Director::getInstance()->getWinSize();
    
    auto img = Sprite::create("Images/test_image_rgba5551_v3.pvr");
    
    if (img)
    {
        img->setPosition(Vec2(s.width/2.0f, s.height/2.0f));
        addChild(img);
    }
    
    log("%s\n", Director::getInstance()->getTextureCache()->getCachedTextureInfo().c_str());
}

std::string TexturePVRRGBA5551v3::title() const
{
    return "PVR + RGBA 5551 Test";
}

std::string TexturePVRRGBA5551v3::subtitle() const
{
    return "Testing PVR File Format v3";
}

// TexturePVRRGBA4444v3
void TexturePVRRGBA4444v3::onEnter()
{
    TextureDemo::onEnter();
    auto s = Director::getInstance()->getWinSize();
    
    auto img = Sprite::create("Images/test_image_rgba4444_v3.pvr");
    
    if (img)
    {
        img->setPosition(Vec2(s.width/2.0f, s.height/2.0f));
        addChild(img);
    }
    
    log("%s\n", Director::getInstance()->getTextureCache()->getCachedTextureInfo().c_str());
}

std::string TexturePVRRGBA4444v3::title() const
{
    return "PVR + RGBA 4444 Test";
}

std::string TexturePVRRGBA4444v3::subtitle() const
{
    return "Testing PVR File Format v3";
}

// TexturePVRRGB565v3
void TexturePVRRGB565v3::onEnter()
{
    TextureDemo::onEnter();
    auto s = Director::getInstance()->getWinSize();
    
    auto img = Sprite::create("Images/test_image_rgb565_v3.pvr");
    
    if (img)
    {
        img->setPosition(Vec2(s.width/2.0f, s.height/2.0f));
        addChild(img);
    }
    
    log("%s\n", Director::getInstance()->getTextureCache()->getCachedTextureInfo().c_str());
}

std::string TexturePVRRGB565v3::title() const
{
    return "PVR + RGB 565 Test";
}

std::string TexturePVRRGB565v3::subtitle() const
{
    return "Testing PVR File Format v3";
}

// TexturePVRRGB888v3
void TexturePVRRGB888v3::onEnter()
{
    TextureDemo::onEnter();
    auto s = Director::getInstance()->getWinSize();
    
    auto img = Sprite::create("Images/test_image_rgb888_v3.pvr");
    
    if (img)
    {
        img->setPosition(Vec2(s.width/2.0f, s.height/2.0f));
        addChild(img);
    }
    
    log("%s\n", Director::getInstance()->getTextureCache()->getCachedTextureInfo().c_str());
}

std::string TexturePVRRGB888v3::title() const
{
    return "PVR + RGB 888 Test";
}

std::string TexturePVRRGB888v3::subtitle() const
{
    return "Testing PVR File Format v3";
}

// TexturePVRA8v3
void TexturePVRA8v3::onEnter()
{
    TextureDemo::onEnter();
    auto s = Director::getInstance()->getWinSize();
    
    auto img = Sprite::create("Images/test_image_a8_v3.pvr");
    
    if (img)
    {
        img->setPosition(Vec2(s.width/2.0f, s.height/2.0f));
        addChild(img);
    }
    
    log("%s\n", Director::getInstance()->getTextureCache()->getCachedTextureInfo().c_str());
}

std::string TexturePVRA8v3::title() const
{
    return "PVR + A8 Test";
}

std::string TexturePVRA8v3::subtitle() const
{
    return "Testing PVR File Format v3";
}

// TexturePVRI8v3
void TexturePVRI8v3::onEnter()
{
    TextureDemo::onEnter();
    auto s = Director::getInstance()->getWinSize();
    
    auto img = Sprite::create("Images/test_image_i8_v3.pvr");
    
    if (img)
    {
        img->setPosition(Vec2(s.width/2.0f, s.height/2.0f));
        addChild(img);
    }
    
    log("%s\n", Director::getInstance()->getTextureCache()->getCachedTextureInfo().c_str());
}

std::string TexturePVRI8v3::title() const
{
    return "PVR + I8 Test";
}

std::string TexturePVRI8v3::subtitle() const
{
    return "Testing PVR File Format v3";
}

// TexturePVRAI88v3
void TexturePVRAI88v3::onEnter()
{
    TextureDemo::onEnter();
    auto s = Director::getInstance()->getWinSize();
    
    auto img = Sprite::create("Images/test_image_ai88_v3.pvr");
    
    if (img)
    {
        img->setPosition(Vec2(s.width/2.0f, s.height/2.0f));
        addChild(img);
    }
    
    log("%s\n", Director::getInstance()->getTextureCache()->getCachedTextureInfo().c_str());
}

std::string TexturePVRAI88v3::title() const
{
    return "PVR + AI88 Test";
}

std::string TexturePVRAI88v3::subtitle() const
{
    return "Testing PVR File Format v3";
}

//------------------------------------------------------------------
//
// TexturePVRBadEncoding
// Image generated using PVRTexTool:
// http://www.imgtec.com/powervr/insider/powervr-pvrtextool.asp
//
//------------------------------------------------------------------
void TexturePVRBadEncoding::onEnter()
{
    TextureDemo::onEnter();
    auto s = Director::getInstance()->getWinSize();

    auto img = Sprite::create("Images/test_image-bad_encoding.pvr");
    if( img )
    {
        img->setPosition(Vec2( s.width/2.0f, s.height/2.0f));
        addChild(img);
    }
}

std::string TexturePVRBadEncoding::title() const
{
    return "PVR Unsupported encoding";
}

std::string TexturePVRBadEncoding::subtitle() const
{
    return "You should not see any image";
}

//------------------------------------------------------------------
//
// TexturePVRNonSquare
//
//------------------------------------------------------------------
void TexturePVRNonSquare::onEnter()
{
    TextureDemo::onEnter();
    auto s = Director::getInstance()->getWinSize();
    
    auto img = Sprite::create("Images/grossini_128x256_mipmap.pvr");
    img->setPosition(Vec2( s.width/2.0f, s.height/2.0f));
    addChild(img);
    log("%s\n", Director::getInstance()->getTextureCache()->getCachedTextureInfo().c_str());
}

std::string TexturePVRNonSquare::title() const
{
    return "PVR + Non square texture";
}

std::string TexturePVRNonSquare::subtitle() const
{
    return "Loading a 128x256 texture";
}

//------------------------------------------------------------------
//
// TexturePVRNPOT4444
//
//------------------------------------------------------------------
void TexturePVRNPOT4444::onEnter()
{
    TextureDemo::onEnter();
    auto s = Director::getInstance()->getWinSize();

    auto img = Sprite::create("Images/grossini_pvr_rgba4444.pvr");
    if ( img )
    {
        img->setPosition(Vec2( s.width/2.0f, s.height/2.0f));
        addChild(img);
    }
    log("%s\n", Director::getInstance()->getTextureCache()->getCachedTextureInfo().c_str());
}

std::string TexturePVRNPOT4444::title() const
{
    return "PVR RGBA4 + NPOT texture";
}

std::string TexturePVRNPOT4444::subtitle() const
{
    return "Loading a 81x121 RGBA4444 texture.";
}

//------------------------------------------------------------------
//
// TexturePVRNPOT8888
//
//------------------------------------------------------------------
void TexturePVRNPOT8888::onEnter()
{
    TextureDemo::onEnter();
    auto s = Director::getInstance()->getWinSize();
    
    auto img = Sprite::create("Images/grossini_pvr_rgba8888.pvr");
    if( img )
    {
        img->setPosition(Vec2( s.width/2.0f, s.height/2.0f));
        addChild(img);
    }
    log("%s\n", Director::getInstance()->getTextureCache()->getCachedTextureInfo().c_str());
}

std::string TexturePVRNPOT8888::title() const
{
    return "PVR RGBA8 + NPOT texture";
}

std::string TexturePVRNPOT8888::subtitle() const
{
    return "Loading a 81x121 RGBA8888 texture.";
}

//------------------------------------------------------------------
//
// TextureAlias
//
//------------------------------------------------------------------
void TextureAlias::onEnter()
{
    TextureDemo::onEnter();
    auto s = Director::getInstance()->getWinSize();
    
    //
    // Sprite 1: GL_LINEAR
    //
    // Default filter is GL_LINEAR
    
    auto sprite = Sprite::create("Images/grossinis_sister1.png");
    sprite->setPosition(Vec2( s.width/3.0f, s.height/2.0f));
    addChild(sprite);
    
    // this is the default filterting
    sprite->getTexture()->setAntiAliasTexParameters();
    
    //
    // Sprite 1: GL_NEAREST
    //    
    
    auto sprite2 = Sprite::create("Images/grossinis_sister2.png");
    sprite2->setPosition(Vec2( 2*s.width/3.0f, s.height/2.0f));
    addChild(sprite2);
    
    // Use Nearest in this one
    sprite2->getTexture()->setAliasTexParameters();
        
    // scale them to show
    auto sc = ScaleBy::create(3, 8.0f);
    auto sc_back = sc->reverse();
    auto scaleforever = RepeatForever::create(Sequence::create(sc, sc_back, nullptr));
    auto scaleToo = scaleforever->clone();

    sprite2->runAction(scaleforever);
    sprite->runAction(scaleToo);
    log("%s\n", Director::getInstance()->getTextureCache()->getCachedTextureInfo().c_str());
}

std::string TextureAlias::title() const
{
    return "AntiAlias / Alias textures";
}

std::string TextureAlias::subtitle() const
{
    return "Left image is antialiased. Right image is aliases";
}

//------------------------------------------------------------------
//
// TexturePixelFormat
//
//------------------------------------------------------------------
void TexturePixelFormat::onEnter()
{
    //
    // This example displays 1 png images 4 times.
    // Each time the image is generated using:
    // 1- 32-bit RGBA8
    // 2- 16-bit RGBA4
    // 3- 16-bit RGB5A1
    // 4- 16-bit RGB565
    TextureDemo::onEnter();
        
    auto s = Director::getInstance()->getWinSize();

    auto background = LayerColor::create(Color4B(128,128,128,255), s.width, s.height);
    addChild(background, -1);
    
    // RGBA 8888 image (32-bit)
    Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::RGBA8888);
    auto sprite1 = Sprite::create("Images/test-rgba1.png");
    sprite1->setPosition(Vec2(1*s.width/7, s.height/2+32));
    addChild(sprite1, 0);

    // remove texture from texture manager    
    Director::getInstance()->getTextureCache()->removeTexture(sprite1->getTexture());

    // RGBA 4444 image (16-bit)
    Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::RGBA4444);
    auto sprite2 = Sprite::create("Images/test-rgba1.png");
    sprite2->setPosition(Vec2(2*s.width/7, s.height/2-32));
    addChild(sprite2, 0);

    // remove texture from texture manager    
    Director::getInstance()->getTextureCache()->removeTexture(sprite2->getTexture());

    // RGB5A1 image (16-bit)
    Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::RGB5A1);
    auto sprite3 = Sprite::create("Images/test-rgba1.png");
    sprite3->setPosition(Vec2(3*s.width/7, s.height/2+32));
    addChild(sprite3, 0);

    // remove texture from texture manager    
    Director::getInstance()->getTextureCache()->removeTexture(sprite3->getTexture());

    // RGB888 image
    Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::RGB888);
    auto sprite4 = Sprite::create("Images/test-rgba1.png");
    sprite4->setPosition(Vec2(4*s.width/7, s.height/2-32));
    addChild(sprite4, 0);

    // remove texture from texture manager    
    Director::getInstance()->getTextureCache()->removeTexture(sprite4->getTexture());

    // RGB565 image (16-bit)
    Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::RGB565);
    auto sprite5 = Sprite::create("Images/test-rgba1.png");
    sprite5->setPosition(Vec2(5*s.width/7, s.height/2+32));
    addChild(sprite5, 0);

    // remove texture from texture manager    
    Director::getInstance()->getTextureCache()->removeTexture(sprite5->getTexture());

    // A8 image (8-bit)
    Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::A8);
    auto sprite6 = Sprite::create("Images/test-rgba1.png");
    sprite6->setPosition(Vec2(6*s.width/7, s.height/2-32));
    addChild(sprite6, 0);
    
    // remove texture from texture manager    
    Director::getInstance()->getTextureCache()->removeTexture(sprite6->getTexture());

    auto fadeout = FadeOut::create(2);
    auto fadein  = FadeIn::create(2);
    auto seq = Sequence::create(DelayTime::create(2), fadeout, fadein, nullptr);
    auto seq_4ever = RepeatForever::create(seq);
    auto seq_4ever2 = seq_4ever->clone();
    auto seq_4ever3 = seq_4ever->clone();
    auto seq_4ever4 = seq_4ever->clone();
    auto seq_4ever5 = seq_4ever->clone();
    
    sprite1->runAction(seq_4ever);
    sprite2->runAction(seq_4ever2);
    sprite3->runAction(seq_4ever3);
    sprite4->runAction(seq_4ever4);
    sprite5->runAction(seq_4ever5);

    // restore default
    Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::DEFAULT);
    log("%s\n", Director::getInstance()->getTextureCache()->getCachedTextureInfo().c_str());
}

std::string TexturePixelFormat::title() const
{
    return "Texture Pixel Formats";
}

std::string TexturePixelFormat::subtitle() const
{
    return "Textures: RGBA8888, RGBA4444, RGB5A1, RGB888, RGB565, A8";
}

//------------------------------------------------------------------
//
// TextureBlend
//
//------------------------------------------------------------------
void TextureBlend::onEnter()
{
    TextureDemo::onEnter();

    for( int i=0;i < 15;i++ )
    {
        // BOTTOM sprites have alpha pre-multiplied
        // they use by default GL_ONE, GL_ONE_MINUS_SRC_ALPHA
        auto cloud = Sprite::create("Images/test_blend.png");
        addChild(cloud, i+1, 100+i);
        cloud->setPosition(Vec2(50+25*i, 80));
        cloud->setBlendFunc( BlendFunc::ALPHA_PREMULTIPLIED );

        // CENTER sprites have also alpha pre-multiplied
        // they use by default GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA
        cloud = Sprite::create("Images/test_blend.png");
        addChild(cloud, i+1, 200+i);
        cloud->setPosition(Vec2(50+25*i, 160));
        BlendFunc blendFunc2 = { GL_ONE_MINUS_DST_COLOR, GL_ZERO };
        cloud->setBlendFunc(blendFunc2);

        // UPPER sprites are using custom blending function
        // You can set any blend function to your sprites
        cloud = Sprite::create("Images/test_blend.png");
        addChild(cloud, i+1, 200+i);
        cloud->setPosition(Vec2(50+25*i, 320-80));
        BlendFunc blendFunc3 = { GL_SRC_ALPHA, GL_ONE };
        cloud->setBlendFunc(blendFunc3);  // additive blending
    }
}

std::string TextureBlend::title() const
{
    return "Texture Blending";
}

std::string TextureBlend::subtitle() const
{
    return "Testing 3 different blending modes";
}


//------------------------------------------------------------------
//
// TextureAsync
//
//------------------------------------------------------------------

void TextureAsync::onEnter()
{
    TextureDemo::onEnter();

    _imageOffset = 0;

    auto size = Director::getInstance()->getWinSize();

    auto label = Label::createWithTTF("Loading...", "fonts/Marker Felt.ttf", 32);
    label->setPosition(Vec2( size.width/2, size.height/2));
    addChild(label, 10);

    auto scale = ScaleBy::create(0.3f, 2);
    auto scale_back = scale->reverse();
    auto seq = Sequence::create(scale, scale_back, nullptr);
    label->runAction(RepeatForever::create(seq));

    scheduleOnce(CC_SCHEDULE_SELECTOR(TextureAsync::loadImages), 1.0f);
}

TextureAsync::~TextureAsync()
{
    auto textureCache = Director::getInstance()->getTextureCache();
    textureCache->unbindAllImageAsync();
    textureCache->removeAllTextures();
}

void TextureAsync::loadImages(float dt)
{
    auto textureCache = Director::getInstance()->getTextureCache();
    for( int i=0;i < 8;i++) {
        for( int j=0;j < 8; j++) {
            char szSpriteName[100] = {0};
            sprintf(szSpriteName, "Images/sprites_test/sprite-%d-%d.png", i, j);
            textureCache->addImageAsync(szSpriteName, CC_CALLBACK_1(TextureAsync::imageLoaded, this));
        }
    }

    textureCache->addImageAsync("Images/background1.jpg", CC_CALLBACK_1(TextureAsync::imageLoaded, this));
    textureCache->addImageAsync("Images/background2.jpg", CC_CALLBACK_1(TextureAsync::imageLoaded, this));
    textureCache->addImageAsync("Images/background.png", CC_CALLBACK_1(TextureAsync::imageLoaded, this));
    textureCache->addImageAsync("Images/atlastest.png", CC_CALLBACK_1(TextureAsync::imageLoaded, this));
    textureCache->addImageAsync("Images/grossini_dance_atlas.png", CC_CALLBACK_1(TextureAsync::imageLoaded, this));
}


void TextureAsync::imageLoaded(Texture2D* texture)
{
    auto director = Director::getInstance();

    //CCASSERT( [NSThread currentThread] == [director runningThread], @"FAIL. Callback should be on cocos2d thread");

    // IMPORTANT: The order on the callback is not guaranteed. Don't depend on the callback

    // This test just creates a sprite based on the Texture

    auto sprite = Sprite::createWithTexture(texture);
    sprite->setAnchorPoint(Vec2(0,0));
    addChild(sprite, -1);

    auto size = director->getWinSize();
    int i = _imageOffset * 32;
    sprite->setPosition(Vec2( i % (int)size.width, (i / (int)size.width) * 32 ));

    _imageOffset++;

    log("Image loaded: %p", texture);
}

std::string TextureAsync::title() const
{
    return "Texture Async Load";
}

std::string TextureAsync::subtitle() const
{
    return "Textures should load while an animation is being run";
}


//------------------------------------------------------------------
//
// TextureGlClamp
//
//------------------------------------------------------------------
void TextureGlClamp::onEnter()
{
    TextureDemo::onEnter();

    auto size = Director::getInstance()->getWinSize();

    // The .png image MUST be power of 2 in order to create a continue effect.
    // eg: 32x64, 512x128, 256x1024, 64x64, etc..
    auto sprite = Sprite::create("Images/pattern1.png", Rect(0,0,512,256));
    addChild(sprite, -1, kTagSprite1);
    sprite->setPosition(Vec2(size.width/2,size.height/2));
    Texture2D::TexParams params = {GL_LINEAR,GL_LINEAR,GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE};
    sprite->getTexture()->setTexParameters(params);

    auto rotate = RotateBy::create(4, 360);
    sprite->runAction(rotate);
    auto scale = ScaleBy::create(2, 0.04f);
    auto scaleBack = scale->reverse();
    auto seq = Sequence::create(scale, scaleBack, nullptr);
    sprite->runAction(seq);
}

std::string TextureGlClamp::title() const
{
    return "Texture GL_CLAMP";
}

TextureGlClamp::~TextureGlClamp()
{
    Director::getInstance()->getTextureCache()->removeUnusedTextures();
}

//------------------------------------------------------------------
//
// TextureGlRepeat
//
//------------------------------------------------------------------
void TextureGlRepeat::onEnter()
{
    TextureDemo::onEnter();

    auto size = Director::getInstance()->getWinSize();
    
    // The .png image MUST be power of 2 in order to create a continue effect.
    // eg: 32x64, 512x128, 256x1024, 64x64, etc..
    auto sprite = Sprite::create("Images/pattern1.png", Rect(0, 0, 4096, 4096));
    addChild(sprite, -1, kTagSprite1);
    sprite->setPosition(Vec2(size.width/2,size.height/2));
    Texture2D::TexParams params = {GL_LINEAR,GL_LINEAR,GL_REPEAT,GL_REPEAT};
    sprite->getTexture()->setTexParameters(params);
    
    auto rotate = RotateBy::create(4, 360);
    sprite->runAction(rotate);
    auto scale = ScaleBy::create(2, 0.04f);
    auto scaleBack = scale->reverse();
    auto seq = Sequence::create(scale, scaleBack, nullptr);
    sprite->runAction(seq);
}

std::string TextureGlRepeat::title() const
{
    return "Texture GL_REPEAT";
}

TextureGlRepeat::~TextureGlRepeat()
{
    Director::getInstance()->getTextureCache()->removeUnusedTextures();
}

//------------------------------------------------------------------
//
// TextureSizeTest
//
//------------------------------------------------------------------
void TextureSizeTest::onEnter()
{
    TextureDemo::onEnter();
    Sprite *sprite = nullptr;
    
    log("Loading 512x512 image...");
    sprite = Sprite::create("Images/texture512x512.png");
    if( sprite )
        log("OK");
    else
        log("Error");

    log("Loading 1024x1024 image...");
    sprite = Sprite::create("Images/texture1024x1024.png");
    if( sprite )
        log("OK");
    else
        log("Error");
//     @todo
//     log("Loading 2048x2048 image...");
//     sprite = Sprite::create("Images/texture2048x2048.png");
//     if( sprite )
//         log("OK");
//     else
//         log("Error");
//     
//     log("Loading 4096x4096 image...");
//     sprite = Sprite::create("Images/texture4096x4096.png");
//     if( sprite )
//         log("OK");
//     else
//         log("Error");
}

std::string TextureSizeTest::title() const
{
    return "Different Texture Sizes";
}

std::string TextureSizeTest::subtitle() const
{
    return "512x512, 1024x1024. See the console.";
}

//------------------------------------------------------------------
//
// TextureCache1
//
//------------------------------------------------------------------
void TextureCache1::onEnter()
{
    TextureDemo::onEnter();

    auto s = Director::getInstance()->getWinSize();
    
    Sprite *sprite;

    sprite = Sprite::create("Images/grossinis_sister1.png");
    sprite->setPosition(Vec2(s.width/5*1, s.height/2));
    sprite->getTexture()->setAliasTexParameters();
    sprite->setScale(2);
    addChild(sprite);

    Director::getInstance()->getTextureCache()->removeTexture(sprite->getTexture());
    
    sprite = Sprite::create("Images/grossinis_sister1.png");
    sprite->setPosition(Vec2(s.width/5*2, s.height/2));
    sprite->getTexture()->setAntiAliasTexParameters();
    sprite->setScale(2);
    addChild(sprite);

    // 2nd set of sprites
    
    sprite = Sprite::create("Images/grossinis_sister2.png");
    sprite->setPosition(Vec2(s.width/5*3, s.height/2));
    sprite->getTexture()->setAliasTexParameters();
    sprite->setScale(2);
    addChild(sprite);
    
    Director::getInstance()->getTextureCache()->removeTextureForKey("Images/grossinis_sister2.png");

    sprite = Sprite::create("Images/grossinis_sister2.png");
    sprite->setPosition(Vec2(s.width/5*4, s.height/2));
    sprite->getTexture()->setAntiAliasTexParameters();
    sprite->setScale(2);
    addChild(sprite);
}

std::string TextureCache1::title() const
{
    return "CCTextureCache: remove";
}

std::string TextureCache1::subtitle() const
{
    return "4 images should appear: alias, antialias, alias, antilias";
}

// TextureDrawAtPoint
void TextureDrawAtPoint::onEnter()
{
    TextureDemo::onEnter();

    _tex1 = Director::getInstance()->getTextureCache()->addImage("Images/grossinis_sister1.png");
    _Tex2F = Director::getInstance()->getTextureCache()->addImage("Images/grossinis_sister2.png");

    _tex1->retain();
    _Tex2F->retain();
}

TextureDrawAtPoint::~TextureDrawAtPoint()
{
    _tex1->release();
    _Tex2F->release();
}

std::string TextureDrawAtPoint::title() const
{
    return "CCTexture2D: drawAtPoint";
}

std::string TextureDrawAtPoint::subtitle() const
{
    return "draws 2 textures using drawAtPoint";
}

void TextureDrawAtPoint::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
    TextureDemo::draw(renderer, transform, flags);
    
    _renderCmd.init(_globalZOrder, transform, flags);
    _renderCmd.func = CC_CALLBACK_0(TextureDrawAtPoint::onDraw, this, transform, flags);
    renderer->addCommand(&_renderCmd);

}

void TextureDrawAtPoint::onDraw(const Mat4 &transform, uint32_t flags)
{
    Director* director = Director::getInstance();
    CCASSERT(nullptr != director, "Director is null when seting matrix stack");
    director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, transform);

    auto s = Director::getInstance()->getWinSize();
    
    _tex1->drawAtPoint(Vec2(s.width/2-50, s.height/2 - 50));
    _Tex2F->drawAtPoint(Vec2(s.width/2+50, s.height/2 - 50));
    
    director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
}

// TextureDrawInRect

void TextureDrawInRect::onEnter()
{
    TextureDemo::onEnter();
    _tex1 = Director::getInstance()->getTextureCache()->addImage("Images/grossinis_sister1.png");
    _Tex2F = Director::getInstance()->getTextureCache()->addImage("Images/grossinis_sister2.png");

    _tex1->retain();
    _Tex2F->retain();
}

TextureDrawInRect::~TextureDrawInRect()
{
    _tex1->release();
    _Tex2F->release();
}

void TextureDrawInRect::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
    TextureDemo::draw(renderer, transform, flags);

    _renderCmd.init(_globalZOrder, transform, flags);
    _renderCmd.func = CC_CALLBACK_0(TextureDrawInRect::onDraw, this, transform, flags);
    renderer->addCommand(&_renderCmd);
}

void TextureDrawInRect::onDraw(const Mat4 &transform, uint32_t flags)
{
    Director* director = Director::getInstance();
    CCASSERT(nullptr != director, "Director is null when seting matrix stack");
    director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, transform);
    
    auto s = Director::getInstance()->getWinSize();
    
    auto rect1 = Rect( s.width/2 - 80, 20, _tex1->getContentSize().width * 0.5f, _tex1->getContentSize().height *2 );
    auto rect2 = Rect( s.width/2 + 80, s.height/2, _tex1->getContentSize().width * 2, _tex1->getContentSize().height * 0.5f );
    
    _tex1->drawInRect(rect1);
    _Tex2F->drawInRect(rect2);
    
    director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
}

std::string TextureDrawInRect::title() const
{
    return "CCTexture2D: drawInRect";
}

std::string TextureDrawInRect::subtitle() const
{
    return "draws 2 textures using drawInRect";
}

//------------------------------------------------------------------
//
// TextureMemoryAlloc
//
//------------------------------------------------------------------
void TextureMemoryAlloc::onEnter()
{
    TextureDemo::onEnter();
    _background = nullptr;
    
    MenuItemFont::setFontSize(24);
    
    auto item1 = MenuItemFont::create("PNG", CC_CALLBACK_1(TextureMemoryAlloc::updateImage, this));
    item1->setTag(0);
    
    auto item2 = MenuItemFont::create("RGBA8", CC_CALLBACK_1(TextureMemoryAlloc::updateImage, this));
    item2->setTag(1);
    
    auto item3 = MenuItemFont::create("RGB8", CC_CALLBACK_1(TextureMemoryAlloc::updateImage, this));
    item3->setTag(2);
    
    auto item4 = MenuItemFont::create("RGBA4", CC_CALLBACK_1(TextureMemoryAlloc::updateImage, this));
    item4->setTag(3);
    
    auto item5 = MenuItemFont::create("A8", CC_CALLBACK_1(TextureMemoryAlloc::updateImage, this));
    item5->setTag(4);
    
    auto menu = Menu::create(item1, item2, item3, item4, item5, nullptr);
    menu->alignItemsHorizontally();
    
    addChild(menu);
    
    auto warmup = MenuItemFont::create("warm up texture", CC_CALLBACK_1(TextureMemoryAlloc::changeBackgroundVisible, this));
    
    auto menu2 = Menu::create(warmup, nullptr);

    menu2->alignItemsHorizontally();
    
    addChild(menu2);
    auto s = Director::getInstance()->getWinSize();
    
    menu2->setPosition(Vec2(s.width/2, s.height/4));
}

void TextureMemoryAlloc::changeBackgroundVisible(cocos2d::Ref *sender)
{
    if (_background)
    {
        _background->setVisible(true);
    }
}

void TextureMemoryAlloc::updateImage(cocos2d::Ref *sender)
{
    if (_background)
    {
        _background->removeFromParentAndCleanup(true);
    }
    
    Director::getInstance()->getTextureCache()->removeUnusedTextures();
	
    int tag = ((Node*)sender)->getTag();
	std::string file;
	switch (tag) 
    {
		case 0:
			file = "Images/test_image.png";
			break;
        case 1:
            file = "Images/test_image_rgba8888.pvr";
            break;
        case 2:
            file = "Images/test_image_rgb888.pvr";
            break;
        case 3:
            file = "Images/test_image_rgba4444.pvr";
            break;
        case 4:
            file = "Images/test_image_a8.pvr";
            break;
	}

    _background = Sprite::create(file.c_str());
    addChild(_background, -10);
	
    _background->setVisible(false);
    
    auto s = Director::getInstance()->getWinSize();
    _background->setPosition(Vec2(s.width/2, s.height/2));
}

std::string TextureMemoryAlloc::title() const
{
    return "Texture memory";
}

std::string TextureMemoryAlloc::subtitle() const
{
    return "Testing Texture Memory allocation. Use Instruments + VM Tracker";
}

// TexturePVRv3Premult
TexturePVRv3Premult::TexturePVRv3Premult()
{
    auto size = Director::getInstance()->getWinSize();
        
    auto background = LayerColor::create(Color4B(128,128,128,255), size.width, size.height);
    addChild(background, -1);
    
    
    // PVR premultiplied
    auto pvr1 = Sprite::create("Images/grossinis_sister1-testalpha_premult.pvr");
    addChild(pvr1, 0);
    pvr1->setPosition(Vec2(size.width/4*1, size.height/2));
    transformSprite(pvr1);
    
    // PVR non-premultiplied
    auto pvr2 = Sprite::create("Images/grossinis_sister1-testalpha_nopremult.pvr");
    addChild(pvr2, 0);
    pvr2->setPosition(Vec2(size.width/4*2, size.height/2));
    transformSprite(pvr2);
    
    // PNG
    Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::RGBA8888);
    Director::getInstance()->getTextureCache()->removeTextureForKey("Images/grossinis_sister1-testalpha.png");
    auto png = Sprite::create("Images/grossinis_sister1-testalpha.png");
    addChild(png, 0);
    png->setPosition(Vec2(size.width/4*3, size.height/2));
    transformSprite(png);
}

std::string TexturePVRv3Premult::title() const
{
    return "PVRv3 Premult Flag";
}

std::string TexturePVRv3Premult::subtitle() const
{
    return "All images should look exactly the same";
}

void TexturePVRv3Premult::transformSprite(cocos2d::Sprite *sprite)
{
    auto fade = FadeOut::create(2);
    auto dl = DelayTime::create(2);
    auto fadein = fade->reverse();
    auto seq = Sequence::create(fade, fadein, dl, nullptr);
    auto repeat = RepeatForever::create(seq);
    sprite->runAction(repeat);
}

// Implementation of ETC1

/*
class TextureETC1 : public TextureDemo
{
public:
    TextureETC1();
    
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};
 */

TextureETC1::TextureETC1()
{
    auto sprite = Sprite::create("Images/ETC1.pkm");
    
    auto size = Director::getInstance()->getWinSize();
    sprite->setPosition(Vec2(size.width/2, size.height/2));
    
    addChild(sprite);
}

std::string TextureETC1::title() const
{
    return "ETC1 texture";
}

std::string TextureETC1::subtitle() const
{
    return "only supported on android";
}

//Implement of S3TC Dxt1
TextureS3TCDxt1::TextureS3TCDxt1()
{
    auto sprite = Sprite::create("Images/test_256x256_s3tc_dxt1_mipmaps.dds");
    //auto sprite = Sprite::create("Images/water_2_dxt1.dds");
    auto size = Director::getInstance()->getWinSize();
    sprite->setPosition(Vec2(size.width / 2, size.height / 2));
    
    addChild(sprite);
}
std::string TextureS3TCDxt1::title() const
{
    return "S3TC texture test#1";
}
std::string TextureS3TCDxt1::subtitle() const
{
    return "S3TC dxt1 decode,one bit for Alpha";
}

//Implement of S3TC Dxt3
TextureS3TCDxt3::TextureS3TCDxt3()
{
    auto sprite = Sprite::create("Images/test_256x256_s3tc_dxt3_mipmaps.dds");
    //auto sprite = Sprite::create("Images/water_2_dxt3.dds");
    auto size = Director::getInstance()->getWinSize();
    sprite->setPosition(Vec2(size.width / 2, size.height / 2));
    
    addChild(sprite);
}
std::string TextureS3TCDxt3::title() const
{
    return "S3TC texture test#2";
}
std::string TextureS3TCDxt3::subtitle() const
{
    return "S3TC dxt3 decode";
}

//Implement of S3TC Dxt5
TextureS3TCDxt5::TextureS3TCDxt5()
{
    auto sprite = Sprite::create("Images/test_256x256_s3tc_dxt5_mipmaps.dds");
    //auto sprite = Sprite::create("Images/water_2_dxt5.dds");
    auto size = Director::getInstance()->getWinSize();
    sprite->setPosition(Vec2(size.width / 2, size.height / 2));
    
    addChild(sprite);
}
std::string TextureS3TCDxt5::title() const
{
    return "S3TC texture test#3";
}
std::string TextureS3TCDxt5::subtitle() const
{
    return "S3TC dxt5 decode";    
}

//Implement of S3TC with no mipmaps
TextureS3TCWithNoMipmaps::TextureS3TCWithNoMipmaps()
{
    auto sprite = Sprite::create("Images/test_512x512_s3tc_dxt5_with_no_mipmaps.dds");
    auto size = Director::getInstance()->getWinSize();
    sprite->setPosition(Vec2(size.width / 2, size.height / 2));
    
    addChild(sprite);
}
std::string TextureS3TCWithNoMipmaps::title() const
{
    return "S3TC with no mipmaps";
}

//Implement of ATITC
TextureATITCRGB::TextureATITCRGB()
{
    auto sprite = Sprite::create("Images/test_256x256_ATC_RGB_mipmaps.ktx");
    
    auto size = Director::getInstance()->getWinSize();
    sprite->setPosition(Vec2(size.width / 2, size.height / 2));

    addChild(sprite);
}
std::string TextureATITCRGB::title() const
{
    return "ATITC texture (*.ktx file) test#1";
}
std::string TextureATITCRGB::subtitle() const
{
    return "ATITC RGB (no Alpha channel) compressed texture test";
}

TextureATITCExplicit::TextureATITCExplicit()
{
    auto sprite = Sprite::create("Images/test_256x256_ATC_RGBA_Explicit_mipmaps.ktx");
    
    auto size = Director::getInstance()->getWinSize();
    sprite->setPosition(Vec2(size.width / 2, size.height / 2));
    
    addChild(sprite);
}
std::string TextureATITCExplicit::title() const
{
    return "ATITC texture (*.ktx file) test#2";
}
std::string TextureATITCExplicit::subtitle() const
{
    return "ATITC RGBA explicit Alpha compressed texture test";
}

TextureATITCInterpolated::TextureATITCInterpolated()
{
    auto sprite = Sprite::create("Images/test_256x256_ATC_RGBA_Interpolated_mipmaps.ktx");
    
    auto size = Director::getInstance()->getWinSize();
    sprite->setPosition(Vec2(size.width / 2, size.height /2));

    addChild(sprite);
}
std::string TextureATITCInterpolated::title() const
{
    return "ATITC texture (*.ktx file) test#3";
}
std::string TextureATITCInterpolated::subtitle() const
{
    return "ATITC RGBA Interpolated Alpha comrpessed texture test";
}

static void addImageToDemo(TextureDemo& demo, float x, float y, const char* path, Texture2D::PixelFormat format)
{
    Texture2D::setDefaultAlphaPixelFormat(format);
    auto sprite = Sprite::create(path);
    sprite->setPosition(Vec2(x, y));
    demo.addChild(sprite, 0);
    
    //remove texture from texture manager
    Director::getInstance()->getTextureCache()->removeTexture(sprite->getTexture());
}

//TextureConvertRGB888
void TextureConvertRGB888::onEnter()
{
    TextureDemo::onEnter();
    
    auto s = Director::getInstance()->getWinSize();
    
    auto background = LayerColor::create(Color4B(255,0,0,255), s.width, s.height);
    addChild(background, -1);
    
    const char* img = "Images/test_image_rgb888.png";
    addImageToDemo(*this, 1*s.width/9, s.height/2+32, img, Texture2D::PixelFormat::RGBA8888);
    addImageToDemo(*this, 2*s.width/9, s.height/2-32, img, Texture2D::PixelFormat::RGB888);
    addImageToDemo(*this, 3*s.width/9, s.height/2+32, img, Texture2D::PixelFormat::RGB565);
    addImageToDemo(*this, 4*s.width/9, s.height/2-32, img, Texture2D::PixelFormat::A8);
    addImageToDemo(*this, 5*s.width/9, s.height/2+32, img, Texture2D::PixelFormat::I8);
    addImageToDemo(*this, 6*s.width/9, s.height/2-32, img, Texture2D::PixelFormat::AI88);
    addImageToDemo(*this, 7*s.width/9, s.height/2+32, img, Texture2D::PixelFormat::RGBA4444);
    addImageToDemo(*this, 8*s.width/9, s.height/2-32, img, Texture2D::PixelFormat::RGB5A1);
    
    // restore default
    Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::DEFAULT);
    log("%s\n", Director::getInstance()->getTextureCache()->getCachedTextureInfo().c_str());
}

std::string TextureConvertRGB888::title() const
{
    return "RGB888 convert test";
}

std::string TextureConvertRGB888::subtitle() const
{
    return "RGBA8888,RGB888,RGB565,A8,I8,AI88,RGBA4444,RGB5A1";
}
//TextureConvertRGBA8888
void TextureConvertRGBA8888::onEnter()
{
    TextureDemo::onEnter();
    
    auto s = Director::getInstance()->getWinSize();
    
    auto background = LayerColor::create(Color4B(255,0,0,255), s.width, s.height);
    addChild(background, -1);
    
    const char* img = "Images/test_image_rgba8888.png";
    addImageToDemo(*this, 1*s.width/9, s.height/2+32, img, Texture2D::PixelFormat::RGBA8888);
    addImageToDemo(*this, 2*s.width/9, s.height/2-32, img, Texture2D::PixelFormat::RGB888);
    addImageToDemo(*this, 3*s.width/9, s.height/2+32, img, Texture2D::PixelFormat::RGB565);
    addImageToDemo(*this, 4*s.width/9, s.height/2-32, img, Texture2D::PixelFormat::A8);
    addImageToDemo(*this, 5*s.width/9, s.height/2+32, img, Texture2D::PixelFormat::I8);
    addImageToDemo(*this, 6*s.width/9, s.height/2-32, img, Texture2D::PixelFormat::AI88);
    addImageToDemo(*this, 7*s.width/9, s.height/2+32, img, Texture2D::PixelFormat::RGBA4444);
    addImageToDemo(*this, 8*s.width/9, s.height/2-32, img, Texture2D::PixelFormat::RGB5A1);
    
    // restore default
    Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::DEFAULT);
    log("%s\n", Director::getInstance()->getTextureCache()->getCachedTextureInfo().c_str());
}

std::string TextureConvertRGBA8888::title() const
{
    return "RGBA8888 convert test";
}

std::string TextureConvertRGBA8888::subtitle() const
{
    return "RGBA8888,RGB888,RGB565,A8,I8,AI88,RGBA4444,RGB5A1";
}
//TextureConvertI8
void TextureConvertI8::onEnter()
{
    TextureDemo::onEnter();
    
    auto s = Director::getInstance()->getWinSize();
    
    auto background = LayerColor::create(Color4B(255,0,0,255), s.width, s.height);
    addChild(background, -1);
    
    const char* img = "Images/test_image_i8.png";
    addImageToDemo(*this, 1*s.width/9, s.height/2+32, img, Texture2D::PixelFormat::RGBA8888);
    addImageToDemo(*this, 2*s.width/9, s.height/2-32, img, Texture2D::PixelFormat::RGB888);
    addImageToDemo(*this, 3*s.width/9, s.height/2+32, img, Texture2D::PixelFormat::RGB565);
    addImageToDemo(*this, 4*s.width/9, s.height/2-32, img, Texture2D::PixelFormat::A8);
    addImageToDemo(*this, 5*s.width/9, s.height/2+32, img, Texture2D::PixelFormat::I8);
    addImageToDemo(*this, 6*s.width/9, s.height/2-32, img, Texture2D::PixelFormat::AI88);
    addImageToDemo(*this, 7*s.width/9, s.height/2+32, img, Texture2D::PixelFormat::RGBA4444);
    addImageToDemo(*this, 8*s.width/9, s.height/2-32, img, Texture2D::PixelFormat::RGB5A1);
    
    // restore default
    Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::DEFAULT);
    log("%s\n", Director::getInstance()->getTextureCache()->getCachedTextureInfo().c_str());
}

std::string TextureConvertI8::title() const
{
    return "I8 convert test";
}

std::string TextureConvertI8::subtitle() const
{
    return "RGBA8888,RGB888,RGB565,A8,I8,AI88,RGBA4444,RGB5A1";
}
//TextureConvertAI88
void TextureConvertAI88::onEnter()
{
    TextureDemo::onEnter();
    
    auto s = Director::getInstance()->getWinSize();
    
    auto background = LayerColor::create(Color4B(255,0,0,255), s.width, s.height);
    addChild(background, -1);
    
    const char* img = "Images/test_image_ai88.png";
    addImageToDemo(*this, 1*s.width/9, s.height/2+32, img, Texture2D::PixelFormat::RGBA8888);
    addImageToDemo(*this, 2*s.width/9, s.height/2-32, img, Texture2D::PixelFormat::RGB888);
    addImageToDemo(*this, 3*s.width/9, s.height/2+32, img, Texture2D::PixelFormat::RGB565);
    addImageToDemo(*this, 4*s.width/9, s.height/2-32, img, Texture2D::PixelFormat::A8);
    addImageToDemo(*this, 5*s.width/9, s.height/2+32, img, Texture2D::PixelFormat::I8);
    addImageToDemo(*this, 6*s.width/9, s.height/2-32, img, Texture2D::PixelFormat::AI88);
    addImageToDemo(*this, 7*s.width/9, s.height/2+32, img, Texture2D::PixelFormat::RGBA4444);
    addImageToDemo(*this, 8*s.width/9, s.height/2-32, img, Texture2D::PixelFormat::RGB5A1);
    
    // restore default
    Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::DEFAULT);
    log("%s\n", Director::getInstance()->getTextureCache()->getCachedTextureInfo().c_str());
}

std::string TextureConvertAI88::title() const
{
    return "AI88 convert test";
}

std::string TextureConvertAI88::subtitle() const
{
    return "RGBA8888,RGB888,RGB565,A8,I8,AI88,RGBA4444,RGB5A1";
}
