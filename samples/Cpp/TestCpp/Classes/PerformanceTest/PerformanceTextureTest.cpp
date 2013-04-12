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
    CCScene* pScene = NULL;

    switch (m_nCurCase)
    {
    case 0:
        pScene = TextureTest::scene();
        break;
    }
    s_nTexCurCase = m_nCurCase;

    if (pScene)
    {
        CCDirector::sharedDirector()->replaceScene(pScene);
    }
}

void TextureMenuLayer::onEnter()
{
    PerformBasicLayer::onEnter();

    CCSize s = CCDirector::sharedDirector()->getWinSize();

    // Title
    CCLabelTTF *label = CCLabelTTF::create(title().c_str(), "Arial", 40);
    addChild(label, 1);
    label->setPosition(ccp(s.width/2, s.height-32));
    label->setColor(ccc3(255,255,40));

    // Subtitle
    std::string strSubTitle = subtitle();
    if(strSubTitle.length())
    {
        CCLabelTTF *l = CCLabelTTF::create(strSubTitle.c_str(), "Thonburi", 16);
        addChild(l, 1);
        l->setPosition(ccp(s.width/2, s.height-80));
    }

    performTests();
}

std::string TextureMenuLayer::title()
{
    return "no title";
}

std::string TextureMenuLayer::subtitle()
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
    CCTexture2D *texture;
    CCTextureCache *cache = CCTextureCache::sharedTextureCache();

    CCLog("RGBA 8888");
    CCTexture2D::setDefaultAlphaPixelFormat(kCCTexture2DPixelFormat_RGBA8888);
    gettimeofday(&now, NULL);
    texture = cache->addImage(filename);
    if( texture )
        CCLog("  ms:%f", calculateDeltaTime(&now) );
    else
        CCLog(" ERROR");
    cache->removeTexture(texture);

    CCLog("RGBA 4444");
    CCTexture2D::setDefaultAlphaPixelFormat(kCCTexture2DPixelFormat_RGBA4444);
    gettimeofday(&now, NULL);
    texture = cache->addImage(filename);
    if( texture )
        CCLog("  ms:%f", calculateDeltaTime(&now) );
    else
        CCLog(" ERROR");
    cache->removeTexture(texture);

    CCLog("RGBA 5551");
    CCTexture2D::setDefaultAlphaPixelFormat(kCCTexture2DPixelFormat_RGB5A1);
    gettimeofday(&now, NULL);
    texture = cache->addImage(filename);
    if( texture )
        CCLog("  ms:%f", calculateDeltaTime(&now) );
    else
        CCLog(" ERROR");
    cache->removeTexture(texture);

    CCLog("RGB 565");
    CCTexture2D::setDefaultAlphaPixelFormat(kCCTexture2DPixelFormat_RGB565);
    gettimeofday(&now, NULL);    
    texture = cache->addImage(filename);
    if( texture )
        CCLog("  ms:%f", calculateDeltaTime(&now) );
    else
        CCLog(" ERROR");
    cache->removeTexture(texture);
}

void TextureTest::performTests()
{
//     CCTexture2D *texture;
//     struct timeval now;
//     CCTextureCache *cache = CCTextureCache::sharedTextureCache();

    CCLog("--------");

    CCLog("--- PNG 128x128 ---");
    performTestsPNG("Images/test_image.png");

//     CCLog("--- PVR 128x128 ---");
//     CCLog("RGBA 8888");
//     gettimeofday(&now, NULL);    
//     texture = cache->addImage("Images/test_image_rgba8888.pvr");
//     if( texture )
//         CCLog("  ms:%f", calculateDeltaTime(&now) );
//     else
//         CCLog("ERROR");
//     cache->removeTexture(texture);
// 
//     CCLog("BGRA 8888");
//     gettimeofday(&now, NULL);    
//     texture = cache->addImage("Images/test_image_bgra8888.pvr");
//     if( texture )
//         CCLog("  ms:%f", calculateDeltaTime(&now) );
//     else
//         CCLog("ERROR");
//     cache->removeTexture(texture);
// 
//     CCLog("RGBA 4444");
//     gettimeofday(&now, NULL);    
//     texture = cache->addImage("Images/test_image_rgba4444.pvr");
//     if( texture )
//         CCLog("  ms:%f", calculateDeltaTime(&now) );
//     else
//         CCLog("ERROR");
//     cache->removeTexture(texture);
// 
//     CCLog("RGB 565");
//     gettimeofday(&now, NULL);
//     texture = cache->addImage("Images/test_image_rgb565.pvr");
//     if( texture )
//         CCLog("  ms:%f", calculateDeltaTime(&now) );
//     else
//         CCLog("ERROR");
//     cache->removeTexture(texture);


    CCLog("--- PNG 512x512 ---");
    performTestsPNG("Images/texture512x512.png");

//     CCLog("--- PVR 512x512 ---");
//     CCLog("RGBA 4444");
//     gettimeofday(&now, NULL);    
//     texture = cache->addImage("Images/texture512x512_rgba4444.pvr");
//     if( texture )
//         CCLog("  ms:%f", calculateDeltaTime(&now) );
//     else
//         CCLog("ERROR");
//     cache->removeTexture(texture);

    //
    // ---- 1024X1024
    // RGBA4444
    // Empty image
    //

    CCLog("EMPTY IMAGE");
    CCLog("--- PNG 1024x1024 ---");
    performTestsPNG("Images/texture1024x1024.png");

//     CCLog("--- PVR 1024x1024 ---");
//     CCLog("RGBA 4444");
//     gettimeofday(&now, NULL);    
//     texture = cache->addImage("Images/texture1024x1024_rgba4444.pvr");
//     if( texture )
//         CCLog("  ms:%f", calculateDeltaTime(&now) );
//     else
//         CCLog("ERROR");
//     cache->removeTexture(texture);
// 
//     CCLog("--- PVR.GZ 1024x1024 ---");
//     CCLog("RGBA 4444");
//     gettimeofday(&now, NULL);    
//     texture = cache->addImage("Images/texture1024x1024_rgba4444.pvr.gz");
//     if( texture )
//         CCLog("  ms:%f", calculateDeltaTime(&now) );
//     else
//         CCLog("ERROR");
//     cache->removeTexture(texture);
// 
//     CCLog("--- PVR.CCZ 1024x1024 ---");
//     CCLog("RGBA 4444");
//     gettimeofday(&now, NULL);    
//     texture = cache->addImage("Images/texture1024x1024_rgba4444.pvr.ccz");
//     if( texture )
//         CCLog("  ms:%f", calculateDeltaTime(&now) );
//     else
//         CCLog("ERROR");
//     cache->removeTexture(texture);

    //
    // ---- 1024X1024
    // RGBA4444
    // SpriteSheet images
    //

    CCLog("SPRITESHEET IMAGE");
    CCLog("--- PNG 1024x1024 ---");
    performTestsPNG("Images/PlanetCute-1024x1024.png");

//     CCLog("--- PVR 1024x1024 ---");
//     CCLog("RGBA 4444");
//     gettimeofday(&now, NULL);    
//     texture = cache->addImage("Images/PlanetCute-1024x1024-rgba4444.pvr");
//     if( texture )
//         CCLog("  ms:%f", calculateDeltaTime(&now) );
//     else
//         CCLog("ERROR");
//     cache->removeTexture(texture);
// 
//     CCLog("--- PVR.GZ 1024x1024 ---");
//     CCLog("RGBA 4444");
//     gettimeofday(&now, NULL);    
//     texture = cache->addImage("Images/PlanetCute-1024x1024-rgba4444.pvr.gz");
//     if( texture )
//         CCLog("  ms:%f", calculateDeltaTime(&now) );
//     else
//         CCLog("ERROR");
//     cache->removeTexture(texture);
// 
//     CCLog("--- PVR.CCZ 1024x1024 ---");
//     CCLog("RGBA 4444");
//     gettimeofday(&now, NULL);    
//     texture = cache->addImage("Images/PlanetCute-1024x1024-rgba4444.pvr.ccz");
//     if( texture )
//         CCLog("  ms:%f", calculateDeltaTime(&now) );
//     else
//         CCLog("ERROR");
//     cache->removeTexture(texture);


    //
    // ---- 1024X1024
    // RGBA8888
    // Landscape Image
    //

    CCLog("LANDSCAPE IMAGE");

    CCLog("--- PNG 1024x1024 ---");
    performTestsPNG("Images/landscape-1024x1024.png");

//     CCLog("--- PVR 1024x1024 ---");
//     CCLog("RGBA 8888");
//     gettimeofday(&now, NULL);    
//     texture = cache->addImage("Images/landscape-1024x1024-rgba8888.pvr");
//     if( texture )
//         CCLog("  ms:%f", calculateDeltaTime(&now) );
//     else
//         CCLog("ERROR");
//     cache->removeTexture(texture);
// 
//     CCLog("--- PVR.GZ 1024x1024 ---");
//     CCLog("RGBA 8888");
//     gettimeofday(&now, NULL);    
//     texture = cache->addImage("Images/landscape-1024x1024-rgba8888.pvr.gz");
//     if( texture )
//         CCLog("  ms:%f", calculateDeltaTime(&now) );
//     else
//         CCLog("ERROR");
//     cache->removeTexture(texture);
// 
//     CCLog("--- PVR.CCZ 1024x1024 ---");
//     CCLog("RGBA 8888");
//     gettimeofday(&now, NULL);    
//     texture = cache->addImage("Images/landscape-1024x1024-rgba8888.pvr.ccz");
//     if( texture )
//         CCLog("  ms:%f", calculateDeltaTime(&now) );
//     else
//         CCLog("ERROR");
//     cache->removeTexture(texture);


    //
    // 2048x2048
    // RGBA444
    //

// most platform don't support texture with width/height is 2048
//     CCLog("--- PNG 2048x2048 ---");
//     performTestsPNG("Images/texture2048x2048.png");

//     CCLog("--- PVR 2048x2048 ---");
//     CCLog("RGBA 4444");
//     gettimeofday(&now, NULL);    
//     texture = cache->addImage("Images/texture2048x2048_rgba4444.pvr");
//     if( texture )
//         CCLog("  ms:%f", calculateDeltaTime(&now) );
//     else
//         CCLog("ERROR");
//     cache->removeTexture(texture);
}

std::string TextureTest::title()
{
    return "Texture Performance Test";
}

std::string TextureTest::subtitle()
{
    return "See console for results";
}

CCScene* TextureTest::scene()
{
    CCScene *pScene = CCScene::create();
    TextureTest *layer = new TextureTest(false, TEST_COUNT, s_nTexCurCase);
    pScene->addChild(layer);
    layer->release();

    return pScene;
}

void runTextureTest()
{
    s_nTexCurCase = 0;
    CCScene* pScene = TextureTest::scene();
    CCDirector::sharedDirector()->replaceScene(pScene);
}
