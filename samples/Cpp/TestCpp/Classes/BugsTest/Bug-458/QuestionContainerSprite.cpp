#include "QuestionContainerSprite.h"

#define kLabelTag

USING_NS_CC;

bool QuestionContainerSprite::init()
{
    if (Sprite::init())
    {
        //Add label
        LabelTTF* label = LabelTTF::create("Answer 1", "Arial", 12);
        label->setTag(100);

        //Add the background
        Size size = Director::sharedDirector()->getWinSize();
        Sprite* corner = Sprite::create("Images/bugs/corner.png");

        int width = size.width * 0.9f - (corner->getContentSize().width * 2);
        int height = size.height * 0.15f  - (corner->getContentSize().height * 2);
        LayerColor* layer = LayerColor::create(ccc4(255, 255, 255, 255 * .75), width, height);
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

        Sprite* corner2 = Sprite::create("Images/bugs/corner.png");
        corner2->setPosition(ccp(-corner->getPosition().x, corner->getPosition().y));
        corner2->setFlipX(true);
        addChild(corner2);

        Sprite* corner3 = Sprite::create("Images/bugs/corner.png");
        corner3->setPosition(ccp(corner->getPosition().x, -corner->getPosition().y));
        corner3->setFlipY(true);
        addChild(corner3);

        Sprite* corner4 = Sprite::create("Images/bugs/corner.png");
        corner4->setPosition(ccp(corner2->getPosition().x, -corner2->getPosition().y));
        corner4->setFlipX(true);
        corner4->setFlipY(true);
        addChild(corner4);

        Sprite* edge = Sprite::create("Images/bugs/edge.png");
        edge->setScaleX(width);
        edge->setPosition(ccp(corner->getPosition().x + (corner->getContentSize().width / 2) + (width / 2), corner->getPosition().y));
        addChild(edge);
        
        Sprite* edge2 = Sprite::create("Images/bugs/edge.png");
        edge2->setScaleX(width);
        edge2->setPosition(ccp(corner->getPosition().x + (corner->getContentSize().width / 2) + (width / 2), -corner->getPosition().y));
        edge2->setFlipY(true);
        addChild(edge2);

        Sprite* edge3 = Sprite::create("Images/bugs/edge.png");
        edge3->setRotation(90);
        edge3->setScaleX(height);
        edge3->setPosition(ccp(corner->getPosition().x, corner->getPosition().y + (corner->getContentSize().height / 2) + (height / 2)));
        addChild(edge3);

        Sprite* edge4 = Sprite::create("Images/bugs/edge.png");
        edge4->setRotation(270);
        edge4->setScaleX(height);
        edge4->setPosition(ccp(-corner->getPosition().x, corner->getPosition().y + (corner->getContentSize().height / 2) + (height / 2)));
        addChild(edge4);

        addChild(label);
        return true;
    }

    return false;
}
