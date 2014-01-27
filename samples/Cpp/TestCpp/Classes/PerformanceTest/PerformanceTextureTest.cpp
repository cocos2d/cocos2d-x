#include "PerformanceTextureTest.h"

enum
{
    TEST_COUNT = 1,
};

static int s_nTexCurCase = 0;

float calculateDeltaTime( struct timeval *lastUpdate )
{
    struct timeval now;

    gettimeofday( &now, NULL);

    float dt = (now.tv_sec - lastUpdate->tv_sec) + (now.tv_usec - lastUpdate->tv_usec) / 1000000.0f;

    return dt;
}

////////////////////////////////////////////////////////
//
// TextureMenuLayer
//
////////////////////////////////////////////////////////
void TextureMenuLayer::showCurrentTest()
{
    Scene* scene = NULL;

    switch (_curCase)
    {
    case 0:
        scene = TextureTest::scene();
        break;
    }
    s_nTexCurCase = _curCase;

    if (scene)
    {
        Director::getInstance()->replaceScene(scene);
    }
}

void TextureMenuLayer::onEnter()
{
    PerformBasicLayer::onEnter();

    auto s = Director::getInstance()->getWinSize();

    // Title
    auto label = LabelTTF::create(title().c_str(), "Arial", 40);
    addChild(label, 1);
    label->setPosition(Point(s.width/2, s.height-32));
    label->setColor(Color3B(255,255,40));

    // Subtitle
    std::string strSubTitle = subtitle();
    if(strSubTitle.length())
    {
        auto l = LabelTTF::create(strSubTitle.c_str(), "Thonburi", 16);
        addChild(l, 1);
        l->setPosition(Point(s.width/2, s.height-80));
    }

    performTests();
}

std::string TextureMenuLayer::title() const
{
    return "no title";
}

std::string TextureMenuLayer::subtitle() const
{
    return "no subtitle";
}

////////////////////////////////////////////////////////
//
// TextureTest
//
////////////////////////////////////////////////////////
void TextureTest::performTestsPNG(const char* filename)
{
    struct timeval now;
    Texture2D *texture;
    auto cache = Director::getInstance()->getTextureCache();
    
    Texture2D::PixelFormat defaultFormat = Texture2D::getDefaultAlphaPixelFormat();

    log("RGBA 8888");
    Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::RGBA8888);
    gettimeofday(&now, NULL);
    texture = cache->addImage(filename);
    if( texture )
        log("  ms:%f", calculateDeltaTime(&now) );
    else
        log(" ERROR");
    cache->removeTexture(texture);

    log("RGBA 4444");
    Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::RGBA4444);
    gettimeofday(&now, NULL);
    texture = cache->addImage(filename);
    if( texture )
        log("  ms:%f", calculateDeltaTime(&now) );
    else
        log(" ERROR");
    cache->removeTexture(texture);

    log("RGBA 5551");
    Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::RGB5A1);
    gettimeofday(&now, NULL);
    texture = cache->addImage(filename);
    if( texture )
        log("  ms:%f", calculateDeltaTime(&now) );
    else
        log(" ERROR");
    cache->removeTexture(texture);

    log("RGB 565");
    Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::RGB565);
    gettimeofday(&now, NULL);    
    texture = cache->addImage(filename);
    if( texture )
        log("  ms:%f", calculateDeltaTime(&now) );
    else
        log(" ERROR");
    cache->removeTexture(texture);
    
    Texture2D::setDefaultAlphaPixelFormat(defaultFormat);
}

void TextureTest::performTests()
{
//     Texture2D *texture;
//     struct timeval now;
//     auto cache = Director::getInstance()->getTextureCache();

    log("--------");

    log("--- PNG 128x128 ---");
    performTestsPNG("Images/test_image.png");

//     log("--- PVR 128x128 ---");
//     log("RGBA 8888");
//     gettimeofday(&now, NULL);    
//     texture = cache->addImage("Images/test_image_rgba8888.pvr");
//     if( texture )
//         log("  ms:%f", calculateDeltaTime(&now) );
//     else
//         log("ERROR");
//     cache->removeTexture(texture);
// 
//     log("BGRA 8888");
//     gettimeofday(&now, NULL);    
//     texture = cache->addImage("Images/test_image_bgra8888.pvr");
//     if( texture )
//         log("  ms:%f", calculateDeltaTime(&now) );
//     else
//         log("ERROR");
//     cache->removeTexture(texture);
// 
//     log("RGBA 4444");
//     gettimeofday(&now, NULL);    
//     texture = cache->addImage("Images/test_image_rgba4444.pvr");
//     if( texture )
//         log("  ms:%f", calculateDeltaTime(&now) );
//     else
//         log("ERROR");
//     cache->removeTexture(texture);
// 
//     log("RGB 565");
//     gettimeofday(&now, NULL);
//     texture = cache->addImage("Images/test_image_rgb565.pvr");
//     if( texture )
//         log("  ms:%f", calculateDeltaTime(&now) );
//     else
//         log("ERROR");
//     cache->removeTexture(texture);


    log("--- PNG 512x512 ---");
    performTestsPNG("Images/texture512x512.png");

//     log("--- PVR 512x512 ---");
//     log("RGBA 4444");
//     gettimeofday(&now, NULL);    
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
    performTestsPNG("Images/texture1024x1024.png");

//     log("--- PVR 1024x1024 ---");
//     log("RGBA 4444");
//     gettimeofday(&now, NULL);    
//     texture = cache->addImage("Images/texture1024x1024_rgba4444.pvr");
//     if( texture )
//         log("  ms:%f", calculateDeltaTime(&now) );
//     else
//         log("ERROR");
//     cache->removeTexture(texture);
// 
//     log("--- PVR.GZ 1024x1024 ---");
//     log("RGBA 4444");
//     gettimeofday(&now, NULL);    
//     texture = cache->addImage("Images/texture1024x1024_rgba4444.pvr.gz");
//     if( texture )
//         log("  ms:%f", calculateDeltaTime(&now) );
//     else
//         log("ERROR");
//     cache->removeTexture(texture);
// 
//     log("--- PVR.CCZ 1024x1024 ---");
//     log("RGBA 4444");
//     gettimeofday(&now, NULL);    
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
    performTestsPNG("Images/PlanetCute-1024x1024.png");

//     log("--- PVR 1024x1024 ---");
//     log("RGBA 4444");
//     gettimeofday(&now, NULL);    
//     texture = cache->addImage("Images/PlanetCute-1024x1024-rgba4444.pvr");
//     if( texture )
//         log("  ms:%f", calculateDeltaTime(&now) );
//     else
//         log("ERROR");
//     cache->removeTexture(texture);
// 
//     log("--- PVR.GZ 1024x1024 ---");
//     log("RGBA 4444");
//     gettimeofday(&now, NULL);    
//     texture = cache->addImage("Images/PlanetCute-1024x1024-rgba4444.pvr.gz");
//     if( texture )
//         log("  ms:%f", calculateDeltaTime(&now) );
//     else
//         log("ERROR");
//     cache->removeTexture(texture);
// 
//     log("--- PVR.CCZ 1024x1024 ---");
//     log("RGBA 4444");
//     gettimeofday(&now, NULL);    
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
    performTestsPNG("Images/landscape-1024x1024.png");

//     log("--- PVR 1024x1024 ---");
//     log("RGBA 8888");
//     gettimeofday(&now, NULL);    
//     texture = cache->addImage("Images/landscape-1024x1024-rgba8888.pvr");
//     if( texture )
//         log("  ms:%f", calculateDeltaTime(&now) );
//     else
//         log("ERROR");
//     cache->removeTexture(texture);
// 
//     log("--- PVR.GZ 1024x1024 ---");
//     log("RGBA 8888");
//     gettimeofday(&now, NULL);    
//     texture = cache->addImage("Images/landscape-1024x1024-rgba8888.pvr.gz");
//     if( texture )
//         log("  ms:%f", calculateDeltaTime(&now) );
//     else
//         log("ERROR");
//     cache->removeTexture(texture);
// 
//     log("--- PVR.CCZ 1024x1024 ---");
//     log("RGBA 8888");
//     gettimeofday(&now, NULL);    
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
//     gettimeofday(&now, NULL);    
//     texture = cache->addImage("Images/texture2048x2048_rgba4444.pvr");
//     if( texture )
//         log("  ms:%f", calculateDeltaTime(&now) );
//     else
//         log("ERROR");
//     cache->removeTexture(texture);
}

std::string TextureTest::title() const
{
    return "Texture Performance Test";
}

std::string TextureTest::subtitle() const
{
    return "See console for results";
}

Scene* TextureTest::scene()
{
    auto scene = Scene::create();
    TextureTest *layer = new TextureTest(false, TEST_COUNT, s_nTexCurCase);
    scene->addChild(layer);
    layer->release();

    return scene;
}

void runTextureTest()
{
    s_nTexCurCase = 0;
    auto scene = TextureTest::scene();
    Director::getInstance()->replaceScene(scene);
}
