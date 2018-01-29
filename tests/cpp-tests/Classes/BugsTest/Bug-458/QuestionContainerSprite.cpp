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

#include "QuestionContainerSprite.h"

#define kLabelTag

USING_NS_CC;

bool QuestionContainerSprite::init()
{
    if (Sprite::init())
    {
        //Add label
        auto label = Label::createWithTTF("Answer 1", "fonts/arial.ttf", 12);
        label->setTag(100);

        //Add the background
        auto size = Director::getInstance()->getWinSize();
        auto corner = Sprite::create("Images/bugs/corner.png");

        int width = size.width * 0.9f - (corner->getContentSize().width * 2);
        int height = size.height * 0.15f  - (corner->getContentSize().height * 2);
        auto layer = LayerColor::create(Color4B(255, 255, 255, 255 * .75), width, height);
        layer->setPosition(Vec2(-width / 2, -height / 2));

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

        corner->setPosition(Vec2(-(width / 2 + corner->getContentSize().width / 2), -(height / 2 + corner->getContentSize().height / 2)));
        addChild(corner);

        auto corner2 = Sprite::create("Images/bugs/corner.png");
        corner2->setPosition(Vec2(-corner->getPosition().x, corner->getPosition().y));
        corner2->setFlippedX(true);
        addChild(corner2);

        auto corner3 = Sprite::create("Images/bugs/corner.png");
        corner3->setPosition(Vec2(corner->getPosition().x, -corner->getPosition().y));
        corner3->setFlippedY(true);
        addChild(corner3);

        auto corner4 = Sprite::create("Images/bugs/corner.png");
        corner4->setPosition(Vec2(corner2->getPosition().x, -corner2->getPosition().y));
        corner4->setFlippedX(true);
        corner4->setFlippedY(true);
        addChild(corner4);

        auto edge = Sprite::create("Images/bugs/edge.png");
        edge->setScaleX(width);
        edge->setPosition(Vec2(corner->getPosition().x + (corner->getContentSize().width / 2) + (width / 2), corner->getPosition().y));
        addChild(edge);
        
        auto edge2 = Sprite::create("Images/bugs/edge.png");
        edge2->setScaleX(width);
        edge2->setPosition(Vec2(corner->getPosition().x + (corner->getContentSize().width / 2) + (width / 2), -corner->getPosition().y));
        edge2->setFlippedY(true);
        addChild(edge2);

        auto edge3 = Sprite::create("Images/bugs/edge.png");
        edge3->setRotation(90);
        edge3->setScaleX(height);
        edge3->setPosition(Vec2(corner->getPosition().x, corner->getPosition().y + (corner->getContentSize().height / 2) + (height / 2)));
        addChild(edge3);

        auto edge4 = Sprite::create("Images/bugs/edge.png");
        edge4->setRotation(270);
        edge4->setScaleX(height);
        edge4->setPosition(Vec2(-corner->getPosition().x, corner->getPosition().y + (corner->getContentSize().height / 2) + (height / 2)));
        addChild(edge4);

        addChild(label);
        return true;
    }

    return false;
}
