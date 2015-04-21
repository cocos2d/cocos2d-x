/*
 * ControlScene.m
 *
 * Copyright (c) 2011 Yannick Loriot
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#include "CCControlScene.h"
#include "CCControlSceneManager.h"
#include "../ExtensionsTest.h"

USING_NS_CC;
USING_NS_CC_EXT;

bool ControlScene::init()
{
    if (TestCase::init())
    {    
        // Add the generated background
        auto background = Sprite::create("extensions/background.png");
        background->setPosition(VisibleRect::center());
        addChild(background);
        
        // Add the ribbon
        auto ribbon = Scale9Sprite::create("extensions/ribbon.png", Rect(1, 1, 48, 55));
        ribbon->setContentSize(Size(VisibleRect::getVisibleRect().size.width, 57));
        ribbon->setPosition(VisibleRect::center().x, VisibleRect::top().y - ribbon->getContentSize().height / 2.0f);
        addChild(ribbon);

        return true;
    }
    return false;
}
