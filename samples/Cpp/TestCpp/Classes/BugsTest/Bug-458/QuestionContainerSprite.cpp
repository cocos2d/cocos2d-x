#include "QuestionContainerSprite.h"

#define kLabelTag

USING_NS_CC;

bool QuestionContainerSprite::init()
{
    if (Sprite::init())
    {
        //Add label
        auto label = LabelTTF::create("Answer 1", "Arial", 12);
        label->setTag(100);

        //Add the background
        auto size = Director::getInstance()->getWinSize();
        auto corner = Sprite::create("Images/bugs/corner.png");

        int width = size.width * 0.9f - (corner->getContentSize().width * 2);
        int height = size.height * 0.15f  - (corner->getContentSize().height * 2);
        auto layer = LayerColor::create(Color4B(255, 255, 255, 255 * .75), width, height);
        layer->setPosition(Point(-width / 2, -height / 2));

        //First button is blue,
        //Second is red
        //Used for testing - change later
        static int a = 0;
        
        if (a == 0)
            label->setColor(Color3B::BLUE);
        else
        {
            log("Color changed");
            label->setColor(Color3B::RED);
        }
        a++;
        addChild(layer);

        corner->setPosition(Point(-(width / 2 + corner->getContentSize().width / 2), -(height / 2 + corner->getContentSize().height / 2)));
        addChild(corner);

        auto corner2 = Sprite::create("Images/bugs/corner.png");
        corner2->setPosition(Point(-corner->getPosition().x, corner->getPosition().y));
        corner2->setFlippedX(true);
        addChild(corner2);

        auto corner3 = Sprite::create("Images/bugs/corner.png");
        corner3->setPosition(Point(corner->getPosition().x, -corner->getPosition().y));
        corner3->setFlippedY(true);
        addChild(corner3);

        auto corner4 = Sprite::create("Images/bugs/corner.png");
        corner4->setPosition(Point(corner2->getPosition().x, -corner2->getPosition().y));
        corner4->setFlippedX(true);
        corner4->setFlippedY(true);
        addChild(corner4);

        auto edge = Sprite::create("Images/bugs/edge.png");
        edge->setScaleX(width);
        edge->setPosition(Point(corner->getPosition().x + (corner->getContentSize().width / 2) + (width / 2), corner->getPosition().y));
        addChild(edge);
        
        auto edge2 = Sprite::create("Images/bugs/edge.png");
        edge2->setScaleX(width);
        edge2->setPosition(Point(corner->getPosition().x + (corner->getContentSize().width / 2) + (width / 2), -corner->getPosition().y));
        edge2->setFlippedY(true);
        addChild(edge2);

        auto edge3 = Sprite::create("Images/bugs/edge.png");
        edge3->setRotation(90);
        edge3->setScaleX(height);
        edge3->setPosition(Point(corner->getPosition().x, corner->getPosition().y + (corner->getContentSize().height / 2) + (height / 2)));
        addChild(edge3);

        auto edge4 = Sprite::create("Images/bugs/edge.png");
        edge4->setRotation(270);
        edge4->setScaleX(height);
        edge4->setPosition(Point(-corner->getPosition().x, corner->getPosition().y + (corner->getContentSize().height / 2) + (height / 2)));
        addChild(edge4);

        addChild(label);
        return true;
    }

    return false;
}
