#include "Level1.h"

using namespace cocos2d;

template <typename T>
std::string to_string(T value)
{
    std::ostringstream os ;
    os << value ;
    return os.str() ;
}

Level1::Level1() {};

Scene* Level1::createScene()
{
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // some upfront items that we need
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    Size playingSize = Size(visibleSize.width, visibleSize.height - (visibleSize.height/8)); // actual playing size to work with
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // create a scene
    // 'scene' is an autorelease object
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    scene = Scene::createWithPhysics();
    scene->setContentSize(cocos2d::Size(visibleSize.width, visibleSize.height));
    
    cocos2d::PhysicsBody* body = cocos2d::PhysicsBody::createEdgeBox(playingSize, cocos2d::PHYSICSBODY_MATERIAL_DEFAULT, 3);
    body->setContactTestBitmask(UINT_MAX);
    body->setCategoryBitmask(0x01);
    
    cocos2d::Node* edgeNode = cocos2d::Node::create();
    edgeNode->setPosition(cocos2d::Point((playingSize.width / 2),(playingSize.height / 2)));
    edgeNode->setPhysicsBody(body);
    scene->addChild(edgeNode);
    
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // create a node to hold all of the labels
    // create the player and score labels
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    int paddingX = 20;
    int paddingY = 20;
    
    auto labelNode = Node::create();
    labelNode->setName("labelNode");
    
    auto player1 = Label::createWithTTF("Player 1", "fonts/Marker Felt.ttf", 32);
    auto player2 = Label::createWithTTF("Player 2", "fonts/Marker Felt.ttf", 32);
    
    auto player1Score = Label::createWithTTF("00000", "fonts/Marker Felt.ttf", 32);
    auto player2Score = Label::createWithTTF("00000", "fonts/Marker Felt.ttf", 32);
    auto pleaseWait = Label::createWithTTF("Please wait 10 seconds...", "fonts/Marker Felt.ttf", 32);
    
    labelNode->addChild(player1, -2);
    labelNode->addChild(player1Score, -1);
    labelNode->addChild(player2, 1);
    labelNode->addChild(player2Score, 2);
    labelNode->addChild(pleaseWait, 2);
    
    player1->setPosition(Vec2(0 + player1->getContentSize().width / 2 + paddingX, visibleSize.height - player1->getContentSize().height / 2 - paddingY));
    
    player1Score->setPosition(Vec2(0 + player1->getPositionX() + player1->getContentSize().width + paddingX, visibleSize.height - player1->getContentSize().height / 2 - paddingY));
    
    player2Score->setPosition(Vec2(visibleSize.width - player2Score->getContentSize().width / 2 - paddingX, visibleSize.height - player2Score->getContentSize().height / 2 - paddingY));
    
    player2->setPosition(Vec2(player2Score->getPositionX() - player2Score->getContentSize().width - paddingX, visibleSize.height - player2Score->getContentSize().height / 2 - paddingY));
    
    pleaseWait->setPosition(Vec2(playingSize.width / 2, playingSize.height / 2));
    
    scene->addChild(labelNode, 0);
    
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // create a node to hold non-sprites.
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    auto nodeItems = Node::create();
    nodeItems->setName("nodeItems");
    
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // create a path/walkway
    // depending upon how large the screen is we need to decide how many blocks to lay down.
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    auto testSprite = Sprite::create("ZigzagForest_Square.png");
    
    int howMany = std::ceil(visibleSize.width / testSprite->getContentSize().width);
    
    int sX = 0; // act as a counter for setPosition x coordinate.
    int sY = 0; // act as a counter for setPosition y coordinate.
    
    playingSize = Size(visibleSize.width, visibleSize.height - testSprite->getContentSize().height);
    
    for (int i=0; i < howMany; i++)
    {
        auto sprite = Sprite::create("ZigzagForest_Square.png");
        sprite->setAnchorPoint(Vec2(0,0));
        sprite->setPosition(sX,sY);
        
        sX += sprite->getContentSize().width;
        
        nodeItems->addChild(sprite, -1);
    }
    
    testSprite = NULL;
    
    
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // create a few blocks as obstables
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    testSprite = Sprite::create("ZigzagGrass_Mud_Round.png");
    
    // left side blocks
    sX = visibleSize.width/4 - testSprite->getContentSize().width;
    sY = playingSize.height/2 - testSprite->getContentSize().height * 2;
    
    for (int i=0; i < 3; i++)
    {
        auto sprite = Sprite::create("ZigzagGrass_Mud_Round.png");
        sprite->setAnchorPoint(Vec2(0,0));
        sprite->setPosition(sX,sY);
        
        sX += sprite->getContentSize().width;
        
        if (i == 1)
        {
            sprite->setName("middleBlock1");
        }
        
        nodeItems->addChild(sprite, 1);
    }
    
    // right side blocks
    sX = (visibleSize.width/2 + visibleSize.width/4) - testSprite->getContentSize().width;
    sY = playingSize.height/2 - testSprite->getContentSize().height * 2;
    
    for (int i=0; i < 3; i++)
    {
        auto sprite = Sprite::create("ZigzagGrass_Mud_Round.png");
        sprite->setAnchorPoint(Vec2(0,0));
        sprite->setPosition(sX,sY);
        
        sX += sprite->getContentSize().width;
        
        if (i == 1)
        {
            sprite->setName("middleBlock2");
        }
        
        nodeItems->addChild(sprite, 1);
    }
    
    // center blocks
    sX = visibleSize.width/2 - testSprite->getContentSize().width;
    sY = (playingSize.height/2 + playingSize.height/4) - testSprite->getContentSize().height * 2;
    
    for (int i=0; i < 3; i++)
    {
        auto sprite = Sprite::create("ZigzagGrass_Mud_Round.png");
        sprite->setAnchorPoint(Vec2(0,0));
        sprite->setPosition(sX,sY);
        
        sX += sprite->getContentSize().width;
        
        nodeItems->addChild(sprite, 1);
    }
    
    testSprite = NULL;
    
    scene->addChild(nodeItems, 1);
    
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // create a node to hold sprites
    // create a sprite
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    auto spriteNode = Node::create();
    spriteNode->setName("spriteNode");
    
    auto sprite1 = Sprite::create("Blue_Front1.png");
    sprite1->setAnchorPoint(Vec2(0,0));
    sprite1->setPosition(100, (visibleSize.height - playingSize.height));
    sprite1->setName("mainSprite");
    
    spriteNode->addChild(sprite1, 1);
    
    scene->addChild(spriteNode, 1);
    
    // schedule something to happen in 10 seconds
    labelNode->scheduleOnce([=](float dt){
        scene->removeChildByName("nodeItems");
        scene->removeChildByName("spriteNode");
        scene->removeChildByName("labelNode");
        
        scene->addChild(physics(playingSize, scene));
    }, 10.0f, "show-physics");

    
    // return the scene
    return scene;
}

cocos2d::Node* Level1::physics(const Size& playingSize, Scene* _scene)
{
    // build up what to show
    auto root = Node::create();
    
    for (int i = 0; i < 40; ++i)
    {
        auto physicsBody = PhysicsBody::createBox(Size(65.0f, 81.0f),
                PhysicsMaterial(0.1f, 1.0f, 0.0f));
        
        physicsBody->setGravityEnable(false);
        physicsBody->setCategoryBitmask(0x08);
        physicsBody->setContactTestBitmask(UINT_MAX);
        
        physicsBody->setVelocity(Vec2(cocos2d::random(-500,500),
                                      cocos2d::random(-500,500)));
        physicsBody->setTag(0x80);
        
        auto sprite = Sprite::create("Blue_Front1.png");
        sprite->setPosition(Vec2(playingSize.width/2 + cocos2d::random(-300,300), playingSize.height/2 + cocos2d::random(-300,300)));
        sprite->setPhysicsBody(physicsBody);
        sprite->getPhysicsBody()->setCategoryBitmask(0x01);    // 0001
        sprite->getPhysicsBody()->setCollisionBitmask(UINT_MAX);   // 0010
        
        auto contactListener = EventListenerPhysicsContact::create();
        
        contactListener->onContactBegin = std::bind(&Level1::onContactBegin, this, std::placeholders::_1);
        
        cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, sprite);
        
        root->addChild(sprite);
    }
    
    for (int i = 0; i < 40; ++i)
    {
        auto physicsBody = PhysicsBody::createBox(Size(65.0f, 81.0f),
                                                  PhysicsMaterial(0.1f, 1.0f, 0.0f));
        
        physicsBody->setGravityEnable(false);
        physicsBody->setCategoryBitmask(0x09);
        physicsBody->setContactTestBitmask(UINT_MAX);
        
        physicsBody->setVelocity(Vec2(cocos2d::random(-500,500),
                                      cocos2d::random(-500,500)));
        physicsBody->setTag(0x90);
        
        auto sprite = Sprite::create("LightBlue_Front1.png");
        sprite->setPosition(Vec2(playingSize.width/2 + cocos2d::random(-300,300), playingSize.height/2 + cocos2d::random(-300,300)));
        sprite->setPhysicsBody(physicsBody);
        sprite->getPhysicsBody()->setCategoryBitmask(0x03);    // 0001
        sprite->getPhysicsBody()->setCollisionBitmask(UINT_MAX);   // 0010
        
        auto contactListener = EventListenerPhysicsContact::create();
        
        contactListener->onContactBegin = std::bind(&Level1::onContactBegin, this, std::placeholders::_1);
        
        cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, sprite);
        
        root->addChild(sprite);
    }
    
    for (int i = 0; i < 30; ++i)
    {
        auto physicsBody = PhysicsBody::createBox(Size(65.0f, 81.0f),
                                                  PhysicsMaterial(0.1f, 1.0f, 0.0f));
        
        physicsBody->setGravityEnable(false);
        physicsBody->setCategoryBitmask(0x09);
        physicsBody->setContactTestBitmask(UINT_MAX);
        
        physicsBody->setVelocity(Vec2(cocos2d::random(-500,500),
                                      cocos2d::random(-500,500)));
        physicsBody->setTag(0x90);
        
        auto sprite = Sprite::create("White_Front1.png");
        sprite->setPosition(Vec2(playingSize.width/2 + cocos2d::random(-300,300), playingSize.height/2 + cocos2d::random(-300,300)));
        sprite->setPhysicsBody(physicsBody);
        sprite->getPhysicsBody()->setCategoryBitmask(0x03);    // 0001
        sprite->getPhysicsBody()->setCollisionBitmask(UINT_MAX);   // 0010
        
        auto contactListener = EventListenerPhysicsContact::create();
        contactListener->onContactBegin = std::bind(&Level1::onContactBegin, this, std::placeholders::_1);
        cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, sprite);
        
        root->addChild(sprite);
    }
    
    for (int i = 0; i < 50; ++i)
    {
        auto physicsBody = PhysicsBody::createBox(Size(65.0f, 81.0f),
                                                  PhysicsMaterial(0.1f, 1.0f, 0.0f));
        
        physicsBody->setGravityEnable(false);
        physicsBody->setCategoryBitmask(0x09);
        physicsBody->setContactTestBitmask(UINT_MAX);
        
        physicsBody->setVelocity(Vec2(cocos2d::random(-500,500),
                                      cocos2d::random(-500,500)));
        physicsBody->setTag(0x90);
        
        auto sprite = Sprite::create("Brown_Front1.png");
        sprite->setPosition(Vec2(playingSize.width/2 + cocos2d::random(-300,300), playingSize.height/2 + cocos2d::random(-300,300)));
        sprite->setPhysicsBody(physicsBody);
        sprite->getPhysicsBody()->setCategoryBitmask(0x04);    // 0001
        sprite->getPhysicsBody()->setCollisionBitmask(UINT_MAX);   // 0010
        
        auto contactListener = EventListenerPhysicsContact::create();
        
        contactListener->onContactBegin = std::bind(&Level1::onContactBegin, this, std::placeholders::_1);
        
        cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, sprite);
        
        root->addChild(sprite);
    }
    
    for (int i = 0; i < 30; ++i)
    {
        auto physicsBody = PhysicsBody::createBox(Size(65.0f, 81.0f),
                                                  PhysicsMaterial(0.1f, 1.0f, 0.0f));
        
        physicsBody->setGravityEnable(false);
        physicsBody->setCategoryBitmask(0x09);
        physicsBody->setContactTestBitmask(UINT_MAX);
        
        physicsBody->setVelocity(Vec2(cocos2d::random(-500,500),
                                      cocos2d::random(-500,500)));
        physicsBody->setTag(0x90);
        
        auto sprite = Sprite::create("Pink_Front1.png");
        sprite->setPosition(Vec2(playingSize.width/2 + cocos2d::random(-300,300), playingSize.height/2 + cocos2d::random(-300,300)));
        sprite->setPhysicsBody(physicsBody);
        sprite->getPhysicsBody()->setCategoryBitmask(0x05);    // 0001
        sprite->getPhysicsBody()->setCollisionBitmask(UINT_MAX);   // 0010
        
        auto contactListener = EventListenerPhysicsContact::create();
        contactListener->onContactBegin = std::bind(&Level1::onContactBegin, this, std::placeholders::_1);
        cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, sprite);
        
        root->addChild(sprite);
    }
    
    return root;
}

bool Level1::onContactBegin(PhysicsContact& contact)
{
    PhysicsBody* a = contact.getShapeA()->getBody();
    PhysicsBody* b = contact.getShapeB()->getBody();
    
    PhysicsBody* body = (a->getCategoryBitmask() == 0x02 || a->getCategoryBitmask() == 0x01) ? a : b;
    
    CC_UNUSED_PARAM(body);
    
    return true;
}
