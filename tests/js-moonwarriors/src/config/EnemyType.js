/****************************************************************************
 Cocos2d-html5 show case : Moon Warriors

 Copyright (c) 2011-2012 cocos2d-x.org
 Copyright (c) 2013-2014 Chukong Technologies Inc.

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
 FITNESS FOR A PARTICULAR PURPOSE AND NON INFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.

 @Authors:
 Programmer: Shengxiang Chen (陈升想), Dingping Lv (吕定平), Ricardo Quesada
 Effects animation: Hao Wu (吴昊)
 Quality Assurance: Sean Lin (林顺)
 ****************************************************************************/

var EnemyType = [
    {
        type:0,
        textureName:"E0.png",
        bulletType:"W2.png",
        HP:1,
        moveType:MW.ENEMY_MOVE_TYPE.ATTACK,
        attackMode:MW.ENEMY_MOVE_TYPE.NORMAL,
        scoreValue:15
    },
    {
        type:1,
        textureName:"E1.png",
        bulletType:"W2.png",
        HP:2,
        moveType:MW.ENEMY_MOVE_TYPE.ATTACK,
        attackMode:MW.ENEMY_MOVE_TYPE.NORMAL,
        scoreValue:40
    },
    {
        type:2,
        textureName:"E2.png",
        bulletType:"W2.png",
        HP:4,
        moveType:MW.ENEMY_MOVE_TYPE.HORIZONTAL,
        attackMode:MW.ENEMY_ATTACK_MODE.TSUIHIKIDAN,
        scoreValue:60
    },
    {
        type:3,
        textureName:"E3.png",
        bulletType:"W2.png",
        HP:6,
        moveType:MW.ENEMY_MOVE_TYPE.OVERLAP,
        attackMode:MW.ENEMY_MOVE_TYPE.NORMAL,
        scoreValue:80
    },
    {
        type:4,
        textureName:"E4.png",
        bulletType:"W2.png",
        HP:10,
        moveType:MW.ENEMY_MOVE_TYPE.HORIZONTAL,
        attackMode:MW.ENEMY_ATTACK_MODE.TSUIHIKIDAN,
        scoreValue:150
    },
    {
        type:5,
        textureName:"E5.png",
        bulletType:"W2.png",
        HP:15,
        moveType:MW.ENEMY_MOVE_TYPE.HORIZONTAL,
        attackMode:MW.ENEMY_MOVE_TYPE.NORMAL,
        scoreValue:200
    }
];
