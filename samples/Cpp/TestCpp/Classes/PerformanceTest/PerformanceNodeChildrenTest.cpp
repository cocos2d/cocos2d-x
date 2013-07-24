#include "PerformanceNodeChildrenTest.h"

enum {
    kTagInfoLayer = 1,
    kTagMainLayer = 2,
    kTagLabelAtlas = 3,

    kTagBase = 20000,

    TEST_COUNT = 4,
};

enum {
    kMaxNodes = 15000,
    kNodesIncrease = 500,
};

static int s_nCurCase = 0;

////////////////////////////////////////////////////////
//
// NodeChildrenMenuLayer
//
////////////////////////////////////////////////////////
NodeChildrenMenuLayer::NodeChildrenMenuLayer(bool bControlMenuVisible, int nMaxCases, int nCurCase)
: PerformBasicLayer(bControlMenuVisible, nMaxCases, nCurCase)
{

}

void NodeChildrenMenuLayer::showCurrentTest()
{
    int nNodes = ((NodeChildrenMainScene*)getParent())->getQuantityOfNodes();
    NodeChildrenMainScene* scene = NULL;

    switch (_curCase)
    {
//     case 0:
//         scene = new IterateSpriteSheetFastEnum();
//         break;
    case 0:
        scene = new IterateSpriteSheetCArray();
        break;
    case 1:
        scene = new AddSpriteSheet();
        break;
    case 2:
        scene = new RemoveSpriteSheet();
        break;
    case 3:
        scene = new ReorderSpriteSheet();
        break;
    }
    s_nCurCase = _curCase;

    if (scene)
    {
        scene->initWithQuantityOfNodes(nNodes);

        Director::getInstance()->replaceScene(scene);
        scene->release();
    }
}

////////////////////////////////////////////////////////
//
// NodeChildrenMainScene
//
////////////////////////////////////////////////////////
void NodeChildrenMainScene::initWithQuantityOfNodes(unsigned int nNodes)
{
    //srand(time());
    Size s = Director::getInstance()->getWinSize();

    // Title
    LabelTTF *label = LabelTTF::create(title().c_str(), "Arial", 40);
    addChild(label, 1);
    label->setPosition(Point(s.width/2, s.height-32));
    label->setColor(Color3B(255,255,40));

    // Subtitle
    std::string strSubTitle = subtitle();
    if(strSubTitle.length())
    {
        LabelTTF *l = LabelTTF::create(strSubTitle.c_str(), "Thonburi", 16);
        addChild(l, 1);
        l->setPosition(Point(s.width/2, s.height-80));
    }

    lastRenderedCount = 0;
    currentQuantityOfNodes = 0;
    quantityOfNodes = nNodes;

    MenuItemFont::setFontSize(65);
    MenuItemFont *decrease = MenuItemFont::create(" - ", [&](Object *sender) {
		quantityOfNodes -= kNodesIncrease;
		if( quantityOfNodes < 0 )
			quantityOfNodes = 0;

		updateQuantityLabel();
		updateQuantityOfNodes();
	});
    decrease->setColor(Color3B(0,200,20));
    MenuItemFont *increase = MenuItemFont::create(" + ", [&](Object *sender) {
		quantityOfNodes += kNodesIncrease;
		if( quantityOfNodes > kMaxNodes )
			quantityOfNodes = kMaxNodes;

		updateQuantityLabel();
		updateQuantityOfNodes();
	});
    increase->setColor(Color3B(0,200,20));

    Menu *menu = Menu::create(decrease, increase, NULL);
    menu->alignItemsHorizontally();
    menu->setPosition(Point(s.width/2, s.height/2+15));
    addChild(menu, 1);

    LabelTTF *infoLabel = LabelTTF::create("0 nodes", "Marker Felt", 30);
    infoLabel->setColor(Color3B(0,200,20));
    infoLabel->setPosition(Point(s.width/2, s.height/2-15));
    addChild(infoLabel, 1, kTagInfoLayer);

    NodeChildrenMenuLayer* menuLayer = new NodeChildrenMenuLayer(true, TEST_COUNT, s_nCurCase);
    addChild(menuLayer);
    menuLayer->release();

    updateQuantityLabel();
    updateQuantityOfNodes();
}

std::string NodeChildrenMainScene::title()
{
    return "No title";
}

std::string NodeChildrenMainScene::subtitle()
{
    return "";
}

void NodeChildrenMainScene::updateQuantityLabel()
{
    if( quantityOfNodes != lastRenderedCount )
    {
        LabelTTF *infoLabel = (LabelTTF *) getChildByTag(kTagInfoLayer);
        char str[20] = {0};
        sprintf(str, "%u nodes", quantityOfNodes);
        infoLabel->setString(str);

        lastRenderedCount = quantityOfNodes;
    }
}

////////////////////////////////////////////////////////
//
// IterateSpriteSheet
//
////////////////////////////////////////////////////////
IterateSpriteSheet::~IterateSpriteSheet()
{

}

void IterateSpriteSheet::updateQuantityOfNodes()
{
    Size s = Director::getInstance()->getWinSize();

    // increase nodes
    if( currentQuantityOfNodes < quantityOfNodes )
    {
        for(int i = 0; i < (quantityOfNodes-currentQuantityOfNodes); i++)
        {
            Sprite *sprite = Sprite::createWithTexture(batchNode->getTexture(), Rect(0, 0, 32, 32));
            batchNode->addChild(sprite);
            sprite->setPosition(Point( CCRANDOM_0_1()*s.width, CCRANDOM_0_1()*s.height));
        }
    }

    // decrease nodes
    else if ( currentQuantityOfNodes > quantityOfNodes )
    {
        for(int i = 0; i < (currentQuantityOfNodes-quantityOfNodes); i++)
        {
            int index = currentQuantityOfNodes-i-1;
            batchNode->removeChildAtIndex(index, true);
        }
    }

    currentQuantityOfNodes = quantityOfNodes;
}

void IterateSpriteSheet::initWithQuantityOfNodes(unsigned int nNodes)
{
    batchNode = SpriteBatchNode::create("Images/spritesheet1.png");
    addChild(batchNode);
    
    NodeChildrenMainScene::initWithQuantityOfNodes(nNodes);

    scheduleUpdate();
}

const char*  IterateSpriteSheet::profilerName()
{
    return "none";
}

////////////////////////////////////////////////////////
//
// IterateSpriteSheetFastEnum
//
////////////////////////////////////////////////////////
void IterateSpriteSheetFastEnum::update(float dt)
{
    // iterate using fast enumeration protocol
    Array* pChildren = batchNode->getChildren();
    Object* pObject = NULL;

    CC_PROFILER_START_INSTANCE(this, this->profilerName());

    CCARRAY_FOREACH(pChildren, pObject)
    {
        Sprite* sprite = static_cast<Sprite*>(pObject);
        sprite->setVisible(false);
    }

    CC_PROFILER_STOP_INSTANCE(this, this->profilerName());
}

std::string IterateSpriteSheetFastEnum::title()
{
    return "A - Iterate SpriteSheet";
}

std::string IterateSpriteSheetFastEnum::subtitle()
{
    return "Iterate children using Fast Enum API. See console";
}

const char*  IterateSpriteSheetFastEnum::profilerName()
{
    return "iter fast enum";
}

////////////////////////////////////////////////////////
//
// IterateSpriteSheetCArray
//
////////////////////////////////////////////////////////
void IterateSpriteSheetCArray::update(float dt)
{
    // iterate using fast enumeration protocol
    Array* pChildren = batchNode->getChildren();
    Object* pObject = NULL;

    CC_PROFILER_START(this->profilerName());

    CCARRAY_FOREACH(pChildren, pObject)
    {
        Sprite* sprite = static_cast<Sprite*>(pObject);
        sprite->setVisible(false);
    }

    CC_PROFILER_STOP(this->profilerName());
}


std::string IterateSpriteSheetCArray::title()
{
    return "B - Iterate SpriteSheet";
}

std::string IterateSpriteSheetCArray::subtitle()
{
    return "Iterate children using C Array API. See console";
}

const char*  IterateSpriteSheetCArray::profilerName()
{
    return "iter c-array";
}

////////////////////////////////////////////////////////
//
// AddRemoveSpriteSheet
//
////////////////////////////////////////////////////////
AddRemoveSpriteSheet::~AddRemoveSpriteSheet()
{

}

void AddRemoveSpriteSheet::initWithQuantityOfNodes(unsigned int nNodes)
{
    batchNode = SpriteBatchNode::create("Images/spritesheet1.png");
    addChild(batchNode);

    NodeChildrenMainScene::initWithQuantityOfNodes(nNodes);

    scheduleUpdate();
}

void AddRemoveSpriteSheet::updateQuantityOfNodes()
{
    Size s = Director::getInstance()->getWinSize();

    // increase nodes
    if( currentQuantityOfNodes < quantityOfNodes )
    {
        for (int i=0; i < (quantityOfNodes-currentQuantityOfNodes); i++)
        {
            Sprite *sprite = Sprite::createWithTexture(batchNode->getTexture(), Rect(0, 0, 32, 32));
            batchNode->addChild(sprite);
            sprite->setPosition(Point( CCRANDOM_0_1()*s.width, CCRANDOM_0_1()*s.height));
            sprite->setVisible(false);
        }
    }
    // decrease nodes
    else if ( currentQuantityOfNodes > quantityOfNodes )
    {
        for(int i=0;i < (currentQuantityOfNodes-quantityOfNodes);i++)
        {
            int index = currentQuantityOfNodes-i-1;
            batchNode->removeChildAtIndex(index, true);
        }
    }

    currentQuantityOfNodes = quantityOfNodes;
}

const char*  AddRemoveSpriteSheet::profilerName()
{
    return "none";
}

////////////////////////////////////////////////////////
//
// AddSpriteSheet
//
////////////////////////////////////////////////////////
void AddSpriteSheet::update(float dt)
{
    // reset seed
    //srandom(0);

    // 15 percent
    int totalToAdd = currentQuantityOfNodes * 0.15f;

    if( totalToAdd > 0 )
    {
        Array* sprites = Array::createWithCapacity(totalToAdd);
        int *zs = new int[totalToAdd];

        // Don't include the sprite creation time and random as part of the profiling
        for(int i=0; i<totalToAdd; i++)
        {
            Sprite* sprite = Sprite::createWithTexture(batchNode->getTexture(), Rect(0,0,32,32));
            sprites->addObject(sprite);
            zs[i]      = CCRANDOM_MINUS1_1() * 50;
        }

        // add them with random Z (very important!)
        CC_PROFILER_START( this->profilerName() );

        for( int i=0; i < totalToAdd;i++ )
        {
            batchNode->addChild((Node*) (sprites->objectAtIndex(i)), zs[i], kTagBase+i);
        }
        
        batchNode->sortAllChildren();
        
        CC_PROFILER_STOP(this->profilerName());

        // remove them
        for( int i=0;i <  totalToAdd;i++)
        {
            batchNode->removeChildByTag(kTagBase+i, true);
        }

        delete [] zs;
    }
}

std::string AddSpriteSheet::title()
{
    return "C - Add to spritesheet";
}

std::string AddSpriteSheet::subtitle()
{
    return "Adds %10 of total sprites with random z. See console";
}

const char*  AddSpriteSheet::profilerName()
{
    return "add sprites";
}

////////////////////////////////////////////////////////
//
// RemoveSpriteSheet
//
////////////////////////////////////////////////////////
void RemoveSpriteSheet::update(float dt)
{
    //srandom(0);

    // 15 percent
    int totalToAdd = currentQuantityOfNodes * 0.15f;

    if( totalToAdd > 0 )
    {
        Array* sprites = Array::createWithCapacity(totalToAdd);

        // Don't include the sprite creation time as part of the profiling
        for(int i=0;i<totalToAdd;i++)
        {
            Sprite* sprite = Sprite::createWithTexture(batchNode->getTexture(), Rect(0,0,32,32));
            sprites->addObject(sprite);
        }

        // add them with random Z (very important!)
        for( int i=0; i < totalToAdd;i++ )
        {
            batchNode->addChild((Node*) (sprites->objectAtIndex(i)), CCRANDOM_MINUS1_1() * 50, kTagBase+i);
        }

        // remove them
        CC_PROFILER_START( this->profilerName() );

        for( int i=0;i <  totalToAdd;i++)
        {
            batchNode->removeChildByTag(kTagBase+i, true);
        }

        CC_PROFILER_STOP( this->profilerName() );
    }
}

std::string RemoveSpriteSheet::title()
{
    return "D - Del from spritesheet";
}

std::string RemoveSpriteSheet::subtitle()
{
    return "Remove %10 of total sprites placed randomly. See console";
}

const char*  RemoveSpriteSheet::profilerName()
{
    return "remove sprites";
}

////////////////////////////////////////////////////////
//
// ReorderSpriteSheet
//
////////////////////////////////////////////////////////
void ReorderSpriteSheet::update(float dt)
{
    //srandom(0);

    // 15 percent
    int totalToAdd = currentQuantityOfNodes * 0.15f;

    if( totalToAdd > 0 )
    {
        Array* sprites = Array::createWithCapacity(totalToAdd);

        // Don't include the sprite creation time as part of the profiling
        for(int i=0; i<totalToAdd; i++)
        {
            Sprite* sprite = Sprite::createWithTexture(batchNode->getTexture(), Rect(0,0,32,32));
            sprites->addObject(sprite);
        }

        // add them with random Z (very important!)
        for( int i=0; i < totalToAdd;i++ )
        {
            batchNode->addChild((Node*) (sprites->objectAtIndex(i)), CCRANDOM_MINUS1_1() * 50, kTagBase+i);
        }

        batchNode->sortAllChildren();

        // reorder them
        CC_PROFILER_START( this->profilerName() );

        for( int i=0;i <  totalToAdd;i++)
        {
            Node* node = (Node*) (batchNode->getChildren()->objectAtIndex(i));
            batchNode->reorderChild(node, CCRANDOM_MINUS1_1() * 50);
        }
        
        batchNode->sortAllChildren();
        CC_PROFILER_STOP( this->profilerName() );

        // remove them
        for( int i=0;i <  totalToAdd;i++)
        {
            batchNode->removeChildByTag(kTagBase+i, true);
        }
    }
}

std::string ReorderSpriteSheet::title()
{
    return "E - Reorder from spritesheet";
}

std::string ReorderSpriteSheet::subtitle()
{
    return "Reorder %10 of total sprites placed randomly. See console";
}

const char*  ReorderSpriteSheet::profilerName()
{
    return "reorder sprites";
}

void runNodeChildrenTest()
{
    IterateSpriteSheet* scene = new IterateSpriteSheetCArray();
    scene->initWithQuantityOfNodes(kNodesIncrease);

    Director::getInstance()->replaceScene(scene);
    scene->release();
}
