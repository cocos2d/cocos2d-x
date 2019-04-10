/****************************************************************************
 Copyright (c) 2012 cocos2d-x.org
 Copyright (c) 2013-2016 Chukong Technologies Inc.
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

#include "SpriteFrameCacheTest.h"

#include <cassert>

// enable log
#define COCOS2D_DEBUG 1

USING_NS_CC;

SpriteFrameCacheTests::SpriteFrameCacheTests()
{
    ADD_TEST_CASE(SpriteFrameCachePixelFormatTest);
    ADD_TEST_CASE(SpriteFrameCacheLoadMultipleTimes);
    ADD_TEST_CASE(SpriteFrameCacheFullCheck);
}

SpriteFrameCachePixelFormatTest::SpriteFrameCachePixelFormatTest()
{
    const Size screenSize = Director::getInstance()->getWinSize();

    infoLabel = Label::create();
    infoLabel->setAnchorPoint(Point(0.5f, 1.0f));
    infoLabel->setAlignment(cocos2d::TextHAlignment::CENTER);
    infoLabel->setPosition(screenSize.width * 0.5f, screenSize.height * 0.7f);
    addChild(infoLabel);
    
    // load atlas definition with specified PixelFormat and check that it matches to expected format
    loadSpriteFrames("Images/sprite_frames_test/test_A8.plist", Texture2D::PixelFormat::A8);
    loadSpriteFrames("Images/sprite_frames_test/test_RGBA8888.plist", Texture2D::PixelFormat::RGBA8888);
    loadSpriteFrames("Images/sprite_frames_test/test_AI88.plist", Texture2D::PixelFormat::AI88);
    loadSpriteFrames("Images/sprite_frames_test/test_RGBA8888.plist", Texture2D::PixelFormat::RGBA8888);
    loadSpriteFrames("Images/sprite_frames_test/test_RGB565.plist", Texture2D::PixelFormat::RGB565);
    loadSpriteFrames("Images/sprite_frames_test/test_RGB888.plist", Texture2D::PixelFormat::RGB888);
    loadSpriteFrames("Images/sprite_frames_test/test_RGBA4444.plist", Texture2D::PixelFormat::RGBA4444);
    loadSpriteFrames("Images/sprite_frames_test/test_RGBA5551.plist", Texture2D::PixelFormat::RGB5A1);
    
    if (Configuration::getInstance()->supportsPVRTC()) {
        loadSpriteFrames("Images/sprite_frames_test/test_PVRTC2.plist", Texture2D::PixelFormat::PVRTC2A);
        loadSpriteFrames("Images/sprite_frames_test/test_PVRTC4.plist", Texture2D::PixelFormat::PVRTC4A);
        loadSpriteFrames("Images/sprite_frames_test/test_PVRTC2_NOALPHA.plist", Texture2D::PixelFormat::PVRTC2);
    }
    
    // test loading atlases without PixelFormat specified
    Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::RGB5A1);
    loadSpriteFrames("Images/sprite_frames_test/test_NoFormat.plist", Texture2D::PixelFormat::RGB5A1);
    
    // restore default alpha pixel format
    Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::RGBA8888);
}

void SpriteFrameCachePixelFormatTest::loadSpriteFrames(const std::string &file, cocos2d::Texture2D::PixelFormat expectedFormat)
{
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(file);
    SpriteFrame *spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName("grossini.png");
    Texture2D *texture = spriteFrame->getTexture();
    const ssize_t bitsPerKB = 8 * 1024;
    const double memorySize = 1.0 * texture->getBitsPerPixelForFormat() * texture->getContentSizeInPixels().width * texture->getContentSizeInPixels().height / bitsPerKB;
    CC_ASSERT(texture->getPixelFormat() == expectedFormat);
    
    const std::string textureInfo = StringUtils::format("%s: %.2f KB\r\n", texture->getStringForFormat(), memorySize);
    infoLabel->setString(infoLabel->getString() + textureInfo);
    
    SpriteFrameCache::getInstance()->removeSpriteFramesFromFile(file);
    Director::getInstance()->getTextureCache()->removeTexture(texture);
}


SpriteFrameCacheLoadMultipleTimes::SpriteFrameCacheLoadMultipleTimes()
{
    const Size screenSize = Director::getInstance()->getWinSize();

    // load atlas definition with specified PixelFormat and check that it matches to expected format
    loadSpriteFrames("Images/sprite_frames_test/test_RGBA8888.plist", Texture2D::PixelFormat::RGBA8888);
    loadSpriteFrames("Images/sprite_frames_test/test_RGBA8888.plist", Texture2D::PixelFormat::RGBA8888);
    loadSpriteFrames("Images/sprite_frames_test/test_RGBA8888.plist", Texture2D::PixelFormat::RGBA8888);
    loadSpriteFrames("Images/sprite_frames_test/test_RGBA8888.plist", Texture2D::PixelFormat::RGBA8888);

}

void SpriteFrameCacheLoadMultipleTimes::loadSpriteFrames(const std::string &file, cocos2d::Texture2D::PixelFormat expectedFormat)
{
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(file);
    SpriteFrame *spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName("grossini.png");
    Texture2D *texture = spriteFrame->getTexture();
    CC_ASSERT(texture->getPixelFormat() == expectedFormat);

    SpriteFrameCache::getInstance()->removeSpriteFrameByName("grossini.png");
    Director::getInstance()->getTextureCache()->removeTexture(texture);
}


SpriteFrameCacheFullCheck::SpriteFrameCacheFullCheck()
{
    const Size screenSize = Director::getInstance()->getWinSize();
    // load atlas definition with specified PixelFormat and check that it matches to expected format
    loadSpriteFrames("Images/test_polygon.plist", Texture2D::PixelFormat::RGBA8888);
}

void SpriteFrameCacheFullCheck::loadSpriteFrames(const std::string &file, cocos2d::Texture2D::PixelFormat expectedFormat)
{
    auto cache = SpriteFrameCache::getInstance();

    CCASSERT(cache->isSpriteFramesWithFileLoaded("plist which not exists") == false, "Plist not exists");

    cache->addSpriteFramesWithFile(file);
    CCASSERT(cache->isSpriteFramesWithFileLoaded(file) == true, "Plist should be full after loaded");

    cache->removeSpriteFrameByName("not_exists_grossinis_sister.png");
    CCASSERT(cache->isSpriteFramesWithFileLoaded(file) == true, "Plist should not be still full");

    cache->removeSpriteFrameByName("grossinis_sister1.png");
    CCASSERT(cache->isSpriteFramesWithFileLoaded(file) == false, "Plist should not be full after remove any sprite");

    cache->addSpriteFramesWithFile(file);
    CCASSERT(cache->isSpriteFramesWithFileLoaded(file) == true, "Plist should be full after reloaded");
}
