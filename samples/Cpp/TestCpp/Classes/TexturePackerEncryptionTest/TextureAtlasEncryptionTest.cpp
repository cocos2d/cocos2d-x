#include "TextureAtlasEncryptionTest.h"
#include "../testResource.h"
#include "support/zip_support/ZipUtils.h"

std::string TextureAtlasEncryptionDemo::title()
{
    return "Texture Atlas Encryption";
}

std::string TextureAtlasEncryptionDemo::subtitle()
{
    return "";
}

void TextureAtlasEncryptionDemo::onEnter()
{
    CCLayer::onEnter();
    
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    CCLabelTTF* label = CCLabelTTF::create(title().c_str(), "Arial", 28);
    label->setPosition( ccp(s.width/2, s.height * 0.75f) );
    this->addChild(label, 1);
    
    std::string strSubtitle = subtitle();
    if(strSubtitle.empty() == false)
    {
        CCLabelTTF* subLabel = CCLabelTTF::create(strSubtitle.c_str(), "Thonburi", 16);
        subLabel->setPosition( ccp(s.width/2, s.height-80) );
        this->addChild(subLabel, 1);
    }
    
    // Load the non-encrypted atlas
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Images/nonencryptedAtlas.plist", "Images/nonencryptedAtlas.pvr.ccz");
    
    // Create a sprite from the non-encrypted atlas
    CCSprite *nonencryptedSprite = CCSprite::createWithSpriteFrameName("Icon.png");
    nonencryptedSprite->setPosition(ccp(s.width * 0.25f, s.height * 0.5f));
    this->addChild(nonencryptedSprite);
    
    CCLabelTTF* nonencryptedSpriteLabel = CCLabelTTF::create("non-encrypted", "Arial", 28);
    nonencryptedSpriteLabel->setPosition(ccp(s.width * 0.25f, nonencryptedSprite->boundingBox().getMinY() - nonencryptedSprite->getContentSize().height/2));
    this->addChild(nonencryptedSpriteLabel, 1);
    
    // Load the encrypted atlas
    // 1) Set the encryption keys or step 2 will fail
    // In this case the encryption key 0xaaaaaaaabbbbbbbbccccccccdddddddd is
    // split into four parts. See the header docs for more information.
    ZipUtils::ccSetPvrEncryptionKeyPart(0, 0xaaaaaaaa);
    ZipUtils::ccSetPvrEncryptionKeyPart(1, 0xbbbbbbbb);
    ZipUtils::ccSetPvrEncryptionKeyPart(2, 0xcccccccc);
    ZipUtils::ccSetPvrEncryptionKeyPart(3, 0xdddddddd);
    
    // Alternatively, you can call the function that accepts the key in a single
    // function call.
    // This is slightly less secure because the entire key is more easily
    // found in the compiled source. See the header docs for more information.
    // ZipUtils::ccSetPvrEncryptionKey(0xaaaaaaaa, 0xbbbbbbbb, 0xcccccccc, 0xdddddddd);

    // 2) Load the encrypted atlas
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Images/encryptedAtlas.plist", "Images/encryptedAtlas.pvr.ccz");
    
    // 3) Create a sprite from the encrypted atlas
    CCSprite *encryptedSprite = CCSprite::createWithSpriteFrameName("powered.png");
    encryptedSprite->setPosition(ccp(s.width * 0.75f, s.height * 0.5f));
    this->addChild(encryptedSprite);
    
    CCLabelTTF* encryptedSpriteLabel = CCLabelTTF::create("encrypted", "Arial", 28);
    encryptedSpriteLabel->setPosition(ccp(s.width * 0.75f, encryptedSprite->boundingBox().getMinY() - encryptedSpriteLabel->getContentSize().height/2));
    this->addChild(encryptedSpriteLabel, 1);
}

void TextureAtlasEncryptionTestScene::runThisTest()
{
    CCLayer *layer = new TextureAtlasEncryptionDemo;
    layer->autorelease();
    
    addChild(layer);
    
    CCDirector::sharedDirector()->replaceScene(this);
}

