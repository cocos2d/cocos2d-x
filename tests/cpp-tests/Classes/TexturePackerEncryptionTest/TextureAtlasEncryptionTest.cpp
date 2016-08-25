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
