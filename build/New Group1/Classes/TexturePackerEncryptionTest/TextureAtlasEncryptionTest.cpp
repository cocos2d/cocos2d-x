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

#include "TextureAtlasEncryptionTest.h"
#include "../testResource.h"

USING_NS_CC;

TextureAtlasEncryptionTests::TextureAtlasEncryptionTests()
{
    ADD_TEST_CASE(TextureAtlasEncryptionDemo);
}

std::string TextureAtlasEncryptionDemo::title() const
{
    return "Texture Atlas Encryption";
}

void TextureAtlasEncryptionDemo::onEnter()
{
    TestCase::onEnter();
    
    auto s = Director::getInstance()->getWinSize();

    // Load the non-encrypted atlas
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/nonencryptedAtlas.plist", "Images/nonencryptedAtlas.pvr.ccz");
    
    // Create a sprite from the non-encrypted atlas
    auto nonencryptedSprite = Sprite::createWithSpriteFrameName("Icon.png");
    nonencryptedSprite->setPosition(Vec2(s.width * 0.25f, s.height * 0.5f));
    this->addChild(nonencryptedSprite);
    
    auto nonencryptedSpriteLabel = Label::createWithTTF("non-encrypted", "fonts/arial.ttf", 28);
    nonencryptedSpriteLabel->setPosition(Vec2(s.width * 0.25f, nonencryptedSprite->getBoundingBox().getMinY() - nonencryptedSprite->getContentSize().height/2));
    this->addChild(nonencryptedSpriteLabel, 1);
    
    // Load the encrypted atlas
    // 1) Set the encryption keys or step 2 will fail
    // In this case the encryption key 0xaaaaaaaabbbbbbbbccccccccdddddddd is
    // split into four parts. See the header docs for more information.
    ZipUtils::setPvrEncryptionKeyPart(0, 0xaaaaaaaa);
    ZipUtils::setPvrEncryptionKeyPart(1, 0xbbbbbbbb);
    ZipUtils::setPvrEncryptionKeyPart(2, 0xcccccccc);
    ZipUtils::setPvrEncryptionKeyPart(3, 0xdddddddd);
    
    // Alternatively, you can call the function that accepts the key in a single
    // function call.
    // This is slightly less secure because the entire key is more easily
    // found in the compiled source. See the header docs for more information.
    // ZipUtils::ccSetPvrEncryptionKey(0xaaaaaaaa, 0xbbbbbbbb, 0xcccccccc, 0xdddddddd);

    // 2) Load the encrypted atlas
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/encryptedAtlas.plist", "Images/encryptedAtlas.pvr.ccz");
    
    // 3) Create a sprite from the encrypted atlas
    auto encryptedSprite = Sprite::createWithSpriteFrameName("powered.png");
    encryptedSprite->setPosition(Vec2(s.width * 0.75f, s.height * 0.5f));
    this->addChild(encryptedSprite);
    
    auto encryptedSpriteLabel = Label::createWithTTF("encrypted", "fonts/arial.ttf", 28);
    encryptedSpriteLabel->setPosition(Vec2(s.width * 0.75f, encryptedSprite->getBoundingBox().getMinY() - encryptedSpriteLabel->getContentSize().height/2));
    this->addChild(encryptedSpriteLabel, 1);
}
