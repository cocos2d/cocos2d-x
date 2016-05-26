#include "Intro.h"

// our next Scene
#include "Level1.h"

using namespace cocos2d;

template <typename T>
std::string to_string(T value)
{
    std::ostringstream os ;
    os << value ;
    return os.str() ;
}

Intro::Intro() {};

Scene* Intro::createScene()
{
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // some upfront items that we need
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    Size playingSize = Size(visibleSize.width, visibleSize.height - (visibleSize.height/8)); // actual playing size to work with
    
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // create a scene for our game to hold everything
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
    // create the title dialog
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    auto color = Color4F(1.0f, 0.5f, 0.3f, 1);
    
    int verts = 4;
    
    Vec2 box[] = {
        Vec2::ZERO,
        Vec2(0,200),
        Vec2(600,200),
        Vec2(600,0)
    };
    
    DrawNode* dotNode1 = DrawNode::create();
    dotNode1->setName("dotnode1");
    dotNode1->setContentSize(Size(600, 200));
    dotNode1->drawPolygon(box, verts, color, 0, color);
    
    dotNode1->setPosition(Vec2(visibleSize.width/2 - (dotNode1->getContentSize().width / 2), playingSize.height - dotNode1->getContentSize().height + 20));
    
    auto label = Label::createWithTTF("Super Aliens", "fonts/Marker Felt.ttf", 64);
    dotNode1->addChild(label, 1);
    auto dotNodeSize = dotNode1->getContentSize();
    label->setPosition(Vec2(dotNodeSize.width/2, dotNodeSize.height/2));
    
    
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // create a node to hold all labels
    // create the player and score labels
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    int paddingX = 20;
    int paddingY = 20;
    
    labelNode = Node::create();
    labelNode->setName("labelnode1");
    auto player1 = Label::createWithTTF("Coins", "fonts/Marker Felt.ttf", 32);
    
    player1Coins = Label::createWithTTF("00000", "fonts/Marker Felt.ttf", 32);
    
    labelNode->addChild(player1, 0);
    labelNode->addChild(player1Coins, 0);
    
    auto player1Size = player1->getContentSize();
    auto player1ScoreSize = player1Coins->getContentSize();
    
    player1->setPosition(Vec2(0 + player1Size.width / 2 + paddingX,
                              visibleSize.height - player1Size.height / 2 - paddingY));
    
    player1Coins->setPosition(Vec2(0 + player1->getPositionX() + player1ScoreSize.width + paddingX,
                                   visibleSize.height - player1ScoreSize.height / 2 - paddingY));
    
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // create a node to hold non-sprites.
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    auto nodeItems = Node::create();
    nodeItems->setName("nodeitems1");
    
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // create a path/walkway
    // depending upon how large the screen is we need to decide how many blocks to lay down.
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    auto testSprite = Sprite::create("ZigzagForest_Square.png");
    auto spriteSize = testSprite->getContentSize();
    
    int howMany = std::ceil(visibleSize.width / spriteSize.width);
    
    int sX = 0; // act as a counter for setPosition x coordinate.
    int sY = 0; // act as a counter for setPosition y coordinate.
    
    playingSize = Size(visibleSize.width, visibleSize.height - spriteSize.height);
    
    for (int i=0; i < howMany; i++)
    {
        auto sprite = Sprite::create("ZigzagForest_Square.png");
        sprite->setAnchorPoint(Vec2::ZERO);
        sprite->setPosition(sX,sY);
        
        sX += sprite->getContentSize().width;
        
        nodeItems->addChild(sprite, 0);
    }
    
    testSprite = NULL;
    
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // create the blocks
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    testSprite = Sprite::create("ZigzagGrass_Mud_Round.png");
    
    sX = visibleSize.width/2 - testSprite->getContentSize().width;
    sY = playingSize.height/2 - testSprite->getContentSize().height * 2;
    
    for (int i=0; i < 5; i++)
    {
        auto sprite = Sprite::create("ZigzagGrass_Mud_Round.png");
        sprite->setAnchorPoint(Vec2::ZERO);
        sprite->setPosition(sX,sY);
        
        sX += sprite->getContentSize().width;
        
        nodeItems->addChild(sprite, 0);
    }
    
    testSprite = NULL;
    
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // create a node to hold all sprites
    // create  a few sprites
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    auto spriteNode = Node::create();
    spriteNode->setName("spritenode1");
    
    auto sprite1 = Sprite::create("Blue_Front1.png");
    sprite1->setName("bluealien");
    sprite1->setAnchorPoint(Vec2(0,0));
    sprite1->setPosition(playingSize.width/2, (visibleSize.height - playingSize.height));
    spriteNode->addChild(sprite1, 1);
    getAliens().push_back(sprite1);
    
    auto sprite2 = Sprite::create("LightBlue_Front1.png");
    sprite2->setName("lightbluealien");
    sprite2->setAnchorPoint(Vec2(0,0));
    sprite2->setPosition(500, (visibleSize.height - playingSize.height));
    spriteNode->addChild(sprite2, 1);
    getAliens().push_back(sprite2);
    
    auto sprite3 = Sprite::create("White_Front1.png");
    sprite3->setName("whitealien");
    sprite3->setAnchorPoint(Vec2(0,0));
    sprite3->setPosition(800, (visibleSize.height - playingSize.height));
    spriteNode->addChild(sprite3, 1);
    getAliens().push_back(sprite3);
    
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // create a node to hold menu
    // create a menu
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    auto menuNode = Node::create();
    menuNode->setName("menunode1");
    
    auto menuItem1 = MenuItemFont::create("Start Game");
    menuItem1->setFontNameObj("fonts/Marker Felt.ttf");
    menuItem1->setFontSizeObj(64);
    menuItem1->setTag(99);
    
    menuItem1->setCallback([&](Ref *sender) {
        Level1* level1 = new Level1();
        
        Director::getInstance()->replaceScene(level1->createScene());
    });
    
    auto menu = Menu::create(menuItem1, NULL);
    menuNode->addChild(menu, 0);
    
    // ******************************
    // adding things step by step
    // ******************************
    
    // 1. title screen
    scene->addChild(dotNode1, -1);
    
    // 2. ground and blocks
    scene->addChild(nodeItems, 1);
    
    // 3. Sprites
    scene->addChild(spriteNode, 1);
    
    // 4. Labels
    scene->addChild(labelNode, -1);
    
    // 5. Menus
    scene->addChild(menuNode, 2);
    
    // 6. make aliens move
    makeAliensMove(getAliens(), playingSize.width/2, (visibleSize.height - playingSize.height));
    
    // 7. make one jump and rotate
    makeAliensJump(getAliens(), playingSize.width/2, (visibleSize.height - playingSize.height));
    
    // 8. music
    playMusic();

    return scene;
}

void Intro::makeAliensMove(const std::vector<Sprite*> _aliens, const float& _screenWidth, const float& _screenHeight)
{
    auto delay = DelayTime::create(0.25f);
    
    auto goRight = MoveBy::create(2, Vec2(700, 0));
    auto goLeft = MoveBy::create(2, Vec2(-300, 0));
    auto putCenter = MoveTo::create(4, Vec2(_screenWidth/2, _screenHeight));
    
    auto seq = Sequence::create(goRight, delay, goLeft, delay, goLeft->clone(), delay->clone(), goRight->clone(), delay->clone(), putCenter, nullptr);
    
    _aliens.at(1)->runAction(RepeatForever::create(seq));
    
    _aliens.at(2)->runAction(RepeatForever::create(seq->clone()));
}

void Intro::makeAliensJump(const std::vector<Sprite*> _aliens, const float& _screenWidth, const float& _screenHeight)
{
    Vector<SpriteFrame*> animFrames;
    animFrames.reserve(12);
    animFrames.pushBack(SpriteFrame::create("Blue_Front1.png", Rect(0,0,65,81)));
    animFrames.pushBack(SpriteFrame::create("Blue_Front2.png", Rect(0,0,65,81)));
    animFrames.pushBack(SpriteFrame::create("Blue_Front3.png", Rect(0,0,65,81)));
    animFrames.pushBack(SpriteFrame::create("Blue_Left1.png", Rect(0,0,65,81)));
    animFrames.pushBack(SpriteFrame::create("Blue_Left2.png", Rect(0,0,65,81)));
    animFrames.pushBack(SpriteFrame::create("Blue_Left3.png", Rect(0,0,65,81)));
    animFrames.pushBack(SpriteFrame::create("Blue_Back1.png", Rect(0,0,65,81)));
    animFrames.pushBack(SpriteFrame::create("Blue_Back2.png", Rect(0,0,65,81)));
    animFrames.pushBack(SpriteFrame::create("Blue_Back3.png", Rect(0,0,65,81)));
    animFrames.pushBack(SpriteFrame::create("Blue_Right1.png", Rect(0,0,65,81)));
    animFrames.pushBack(SpriteFrame::create("Blue_Right2.png", Rect(0,0,65,81)));
    animFrames.pushBack(SpriteFrame::create("Blue_Right3.png", Rect(0,0,65,81)));
    
    Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
    Animate* animate = Animate::create(animation);
    
    auto jump = JumpBy::create(0.5, Point(0, 0), 200, 1);
    
    auto spawn = Spawn::createWithTwoActions(animate, jump);
    
    _aliens.at(0)->runAction(RepeatForever::create(spawn));
}

void Intro::playMusic()
{
    auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
    
    audio->playBackgroundMusic("bgm_main.mp3", true);
}