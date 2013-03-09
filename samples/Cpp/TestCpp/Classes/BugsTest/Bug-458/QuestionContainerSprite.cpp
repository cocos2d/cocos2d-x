#include "QuestionContainerSprite.h"

#define kLabelTag

USING_NS_CC;

bool QuestionContainerSprite::init()
{
    if (CCSprite::init())
    {
        //Add label
        CCLabelTTF* label = CCLabelTTF::create("Answer 1", "Arial", 12);
        label->setTag(100);

        //Add the background
        CCSize size = CCDirector::sharedDirector()->getWinSize();
        CCSprite* corner = CCSprite::create("Images/bugs/corner.png");

        int width = size.width * 0.9f - (corner->getContentSize().width * 2);
        int height = size.height * 0.15f  - (corner->getContentSize().height * 2);
        CCLayerColor* layer = CCLayerColor::create(ccc4(255, 255, 255, 255 * .75), width, height);
        layer->setPosition(ccp(-width / 2, -height / 2));

        //First button is blue,
        //Second is red
        //Used for testing - change later
        static int a = 0;
        
        if (a == 0)
            label->setColor(ccBLUE);
        else
        {
            CCLog("Color changed");
            label->setColor(ccRED);
        }
        a++;
        addChild(layer);

        corner->setPosition(ccp(-(width / 2 + corner->getContentSize().width / 2), -(height / 2 + corner->getContentSize().height / 2)));
        addChild(corner);

        CCSprite* corner2 = CCSprite::create("Images/bugs/corner.png");
        corner2->setPosition(ccp(-corner->getPosition().x, corner->getPosition().y));
        corner2->setFlipX(true);
        addChild(corner2);

        CCSprite* corner3 = CCSprite::create("Images/bugs/corner.png");
        corner3->setPosition(ccp(corner->getPosition().x, -corner->getPosition().y));
        corner3->setFlipY(true);
        addChild(corner3);

        CCSprite* corner4 = CCSprite::create("Images/bugs/corner.png");
        corner4->setPosition(ccp(corner2->getPosition().x, -corner2->getPosition().y));
        corner4->setFlipX(true);
        corner4->setFlipY(true);
        addChild(corner4);

        CCSprite* edge = CCSprite::create("Images/bugs/edge.png");
        edge->setScaleX(width);
        edge->setPosition(ccp(corner->getPosition().x + (corner->getContentSize().width / 2) + (width / 2), corner->getPosition().y));
        addChild(edge);
        
        CCSprite* edge2 = CCSprite::create("Images/bugs/edge.png");
        edge2->setScaleX(width);
        edge2->setPosition(ccp(corner->getPosition().x + (corner->getContentSize().width / 2) + (width / 2), -corner->getPosition().y));
        edge2->setFlipY(true);
        addChild(edge2);

        CCSprite* edge3 = CCSprite::create("Images/bugs/edge.png");
        edge3->setRotation(90);
        edge3->setScaleX(height);
        edge3->setPosition(ccp(corner->getPosition().x, corner->getPosition().y + (corner->getContentSize().height / 2) + (height / 2)));
        addChild(edge3);

        CCSprite* edge4 = CCSprite::create("Images/bugs/edge.png");
        edge4->setRotation(270);
        edge4->setScaleX(height);
        edge4->setPosition(ccp(-corner->getPosition().x, corner->getPosition().y + (corner->getContentSize().height / 2) + (height / 2)));
        addChild(edge4);

        addChild(label);
        return true;
    }

    return false;
}
