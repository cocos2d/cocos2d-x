/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
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

#include "PerformanceTextureTest.h"
#include "Profile.h"

USING_NS_CC;

PerformceTextureTests::PerformceTextureTests()
{
    ADD_TEST_CASE(TexturePerformceTest);
}

static float calculateDeltaTime( struct timeval *lastUpdate )
{
    struct timeval now;

    gettimeofday( &now, nullptr);

    float dt = (now.tv_sec - lastUpdate->tv_sec) + (now.tv_usec - lastUpdate->tv_usec) / 1000000.0f;

    return dt;
}

////////////////////////////////////////////////////////
//
// TexturePerformceTest
//
////////////////////////////////////////////////////////
void TexturePerformceTest::performTestsPNG(const char* filename, const char* fileType, const char* resolution, const char* remark)
{
    struct timeval now;
    Texture2D *texture;
    auto cache = Director::getInstance()->getTextureCache();
    
    Texture2D::PixelFormat defaultFormat = Texture2D::getDefaultAlphaPixelFormat();

    log("RGBA 8888");
    Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::RGBA8888);
    gettimeofday(&now, nullptr);
    texture = cache->addImage(filename);
    if( texture )
    {
        auto dt = calculateDeltaTime(&now);
        log("  ms:%f", dt);
        if (isAutoTesting())
            Profile::getInstance()->addTestResult(genStrVector(fileType, resolution, "RGBA8888", remark, nullptr),
                                                  genStrVector(genStr("%fms", dt).c_str(), nullptr));
    }
    else
        log(" ERROR");
    cache->removeTexture(texture);

    log("RGBA 4444");
    Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::RGBA4444);
    gettimeofday(&now, nullptr);
    texture = cache->addImage(filename);
    if( texture )
    {
        auto dt = calculateDeltaTime(&now);
        log("  ms:%f", dt);
        if (isAutoTesting())
            Profile::getInstance()->addTestResult(genStrVector(fileType, resolution, "RGBA4444", remark, nullptr),
                                              genStrVector(genStr("%fms", dt).c_str(), nullptr));
    }
    else
        log(" ERROR");
    cache->removeTexture(texture);

    log("RGBA 5551");
    Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::RGB5A1);
    gettimeofday(&now, nullptr);
    texture = cache->addImage(filename);
    if( texture )
    {
        auto dt = calculateDeltaTime(&now);
        log("  ms:%f", dt);
        if (isAutoTesting())
            Profile::getInstance()->addTestResult(genStrVector(fileType, resolution, "RGBA5551", remark, nullptr),
                                              genStrVector(genStr("%fms", dt).c_str(), nullptr));
    }
    else
        log(" ERROR");
    cache->removeTexture(texture);

    log("RGB 565");
    Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::RGB565);
    gettimeofday(&now, nullptr);    
    texture = cache->addImage(filename);
    if( texture )
    {
        auto dt = calculateDeltaTime(&now);
        log("  ms:%f", dt);
        if (isAutoTesting())
            Profile::getInstance()->addTestResult(genStrVector(fileType, resolution, "RGB565", remark, nullptr),
                                              genStrVector(genStr("%fms", dt).c_str(), nullptr));
    }
    else
        log(" ERROR");
    cache->removeTexture(texture);
    
    Texture2D::setDefaultAlphaPixelFormat(defaultFormat);
}

void TexturePerformceTest::performTests()
{
    if (isAutoTesting()) {
        Profile::getInstance()->testCaseBegin("TextureTest",
                                              genStrVector("FileType", "Resolution", "TextureFormat", "Remark", nullptr),
                                              genStrVector("Time", nullptr));
    }

//     Texture2D *texture;
//     struct timeval now;
//     auto cache = Director::getInstance()->getTextureCache();

    log("--------");

    log("--- PNG 128x128 ---");
    performTestsPNG("Images/test_image.png", "png", "128x128", "");

//     log("--- PVR 128x128 ---");
//     log("RGBA 8888");
//     gettimeofday(&now, nullptr);    
//     texture = cache->addImage("Images/test_image_rgba8888.pvr");
//     if( texture )
//         log("  ms:%f", calculateDeltaTime(&now) );
//     else
//         log("ERROR");
//     cache->removeTexture(texture);
// 
//     log("BGRA 8888");
//     gettimeofday(&now, nullptr);    
//     texture = cache->addImage("Images/test_image_bgra8888.pvr");
//     if( texture )
//         log("  ms:%f", calculateDeltaTime(&now) );
//     else
//         log("ERROR");
//     cache->removeTexture(texture);
// 
//     log("RGBA 4444");
//     gettimeofday(&now, nullptr);    
//     texture = cache->addImage("Images/test_image_rgba4444.pvr");
//     if( texture )
//         log("  ms:%f", calculateDeltaTime(&now) );
//     else
//         log("ERROR");
//     cache->removeTexture(texture);
// 
//     log("RGB 565");
//     gettimeofday(&now, nullptr);
//     texture = cache->addImage("Images/test_image_rgb565.pvr");
//     if( texture )
//         log("  ms:%f", calculateDeltaTime(&now) );
//     else
//         log("ERROR");
//     cache->removeTexture(texture);


    log("--- PNG 512x512 ---");
    performTestsPNG("Images/texture512x512.png", "png", "512x512", "");

//     log("--- PVR 512x512 ---");
//     log("RGBA 4444");
//     gettimeofday(&now, nullptr);    
//     texture = cache->addImage("Images/texture512x512_rgba4444.pvr");
//     if( texture )
//         log("  ms:%f", calculateDeltaTime(&now) );
//     else
//         log("ERROR");
//     cache->removeTexture(texture);

    //
    // ---- 1024X1024
    // RGBA4444
    // Empty image
    //

    log("EMPTY IMAGE");
    log("--- PNG 1024x1024 ---");
    performTestsPNG("Images/texture1024x1024.png", "png", "1024x1024", "EMPTY IMAGE");

//     log("--- PVR 1024x1024 ---");
//     log("RGBA 4444");
//     gettimeofday(&now, nullptr);    
//     texture = cache->addImage("Images/texture1024x1024_rgba4444.pvr");
//     if( texture )
//         log("  ms:%f", calculateDeltaTime(&now) );
//     else
//         log("ERROR");
//     cache->removeTexture(texture);
// 
//     log("--- PVR.GZ 1024x1024 ---");
//     log("RGBA 4444");
//     gettimeofday(&now, nullptr);    
//     texture = cache->addImage("Images/texture1024x1024_rgba4444.pvr.gz");
//     if( texture )
//         log("  ms:%f", calculateDeltaTime(&now) );
//     else
//         log("ERROR");
//     cache->removeTexture(texture);
// 
//     log("--- PVR.CCZ 1024x1024 ---");
//     log("RGBA 4444");
//     gettimeofday(&now, nullptr);    
//     texture = cache->addImage("Images/texture1024x1024_rgba4444.pvr.ccz");
//     if( texture )
//         log("  ms:%f", calculateDeltaTime(&now) );
//     else
//         log("ERROR");
//     cache->removeTexture(texture);

    //
    // ---- 1024X1024
    // RGBA4444
    // SpriteSheet images
    //

    log("SPRITESHEET IMAGE");
    log("--- PNG 1024x1024 ---");
    performTestsPNG("Images/PlanetCute-1024x1024.png", "png", "1024x1024", "SPRITESHEET IMAGE");

//     log("--- PVR 1024x1024 ---");
//     log("RGBA 4444");
//     gettimeofday(&now, nullptr);    
//     texture = cache->addImage("Images/PlanetCute-1024x1024-rgba4444.pvr");
//     if( texture )
//         log("  ms:%f", calculateDeltaTime(&now) );
//     else
//         log("ERROR");
//     cache->removeTexture(texture);
// 
//     log("--- PVR.GZ 1024x1024 ---");
//     log("RGBA 4444");
//     gettimeofday(&now, nullptr);    
//     texture = cache->addImage("Images/PlanetCute-1024x1024-rgba4444.pvr.gz");
//     if( texture )
//         log("  ms:%f", calculateDeltaTime(&now) );
//     else
//         log("ERROR");
//     cache->removeTexture(texture);
// 
//     log("--- PVR.CCZ 1024x1024 ---");
//     log("RGBA 4444");
//     gettimeofday(&now, nullptr);    
//     texture = cache->addImage("Images/PlanetCute-1024x1024-rgba4444.pvr.ccz");
//     if( texture )
//         log("  ms:%f", calculateDeltaTime(&now) );
//     else
//         log("ERROR");
//     cache->removeTexture(texture);


    //
    // ---- 1024X1024
    // RGBA8888
    // Landscape Image
    //

    log("LANDSCAPE IMAGE");

    log("--- PNG 1024x1024 ---");
    performTestsPNG("Images/landscape-1024x1024.png", "png", "1024x1024", "LANDSCAPE IMAGE");

//     log("--- PVR 1024x1024 ---");
//     log("RGBA 8888");
//     gettimeofday(&now, nullptr);    
//     texture = cache->addImage("Images/landscape-1024x1024-rgba8888.pvr");
//     if( texture )
//         log("  ms:%f", calculateDeltaTime(&now) );
//     else
//         log("ERROR");
//     cache->removeTexture(texture);
// 
//     log("--- PVR.GZ 1024x1024 ---");
//     log("RGBA 8888");
//     gettimeofday(&now, nullptr);    
//     texture = cache->addImage("Images/landscape-1024x1024-rgba8888.pvr.gz");
//     if( texture )
//         log("  ms:%f", calculateDeltaTime(&now) );
//     else
//         log("ERROR");
//     cache->removeTexture(texture);
// 
//     log("--- PVR.CCZ 1024x1024 ---");
//     log("RGBA 8888");
//     gettimeofday(&now, nullptr);    
//     texture = cache->addImage("Images/landscape-1024x1024-rgba8888.pvr.ccz");
//     if( texture )
//         log("  ms:%f", calculateDeltaTime(&now) );
//     else
//         log("ERROR");
//     cache->removeTexture(texture);


    //
    // 2048x2048
    // RGBA444
    //

// most platform don't support texture with width/height is 2048
//     log("--- PNG 2048x2048 ---");
//     performTestsPNG("Images/texture2048x2048.png");

//     log("--- PVR 2048x2048 ---");
//     log("RGBA 4444");
//     gettimeofday(&now, nullptr);    
//     texture = cache->addImage("Images/texture2048x2048_rgba4444.pvr");
//     if( texture )
//         log("  ms:%f", calculateDeltaTime(&now) );
//     else
//         log("ERROR");
//     cache->removeTexture(texture);
    
    if (isAutoTesting())
    {
        Profile::getInstance()->testCaseEnd();
        setAutoTesting(false);
    }
}

void TexturePerformceTest::onEnter()
{
    TestCase::onEnter();

    performTests();
}

std::string TexturePerformceTest::title() const
{
    return "Texture Performance Test";
}

std::string TexturePerformceTest::subtitle() const
{
    return "See console for results";
}
