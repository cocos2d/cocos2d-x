/****************************************************************************
 Copyright (c) 2010-2011 cocos2d-x.org
 Copyright (c) 2010      Ray Wenderlich
 
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

#ifndef _GAME_OVER_SCENE_H_
#define _GAME_OVER_SCENE_H_

#include "cocos2d.h"

class GameOverLayer : public cocos2d::LayerColor
{
public:
    GameOverLayer():_label(NULL) {};
    virtual ~GameOverLayer();
    bool init();
    CREATE_FUNC(GameOverLayer);

    void gameOverDone();

    CC_SYNTHESIZE_READONLY(cocos2d::LabelTTF*, _label, Label);
};

class GameOverScene : public cocos2d::Scene
{
public:
    GameOverScene():_layer(NULL) {};
    ~GameOverScene();
    bool init();
    CREATE_FUNC(GameOverScene);
  
    CC_SYNTHESIZE_READONLY(GameOverLayer*, _layer, Layer);
};

#endif // _GAME_OVER_SCENE_H_
