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

#ifndef TERRAIN_TESH_H

#include "../BaseTest.h"

#include "3d/CCSprite3D.h"
#include "3d/CCTerrain.h"
#include "2d/CCCamera.h"
#include "2d/CCAction.h"

DEFINE_TEST_SUITE(TerrainTests);

class TerrainTestDemo : public TestCase
{
protected:
    std::string    _title;
};

class TerrainSimple : public TerrainTestDemo
{
public:
    CREATE_FUNC(TerrainSimple);
    TerrainSimple();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    cocos2d::Terrain* _terrain;
protected:
    cocos2d::Camera* _camera;
};

#define PLAYER_STATE_LEFT 0 
#define PLAYER_STATE_RIGHT 1
#define PLAYER_STATE_IDLE 2
#define PLAYER_STATE_FORWARD 3
#define PLAYER_STATE_BACKWARD 4

class Player : public cocos2d::Sprite3D
{
public:
    static Player * create(const char * file, cocos2d::Camera*  cam, cocos2d::Terrain* terrain);
    virtual bool isDone() const;
    virtual void update(float dt);

    void turnLeft();
    void turnRight();
    void forward();
    void backward();
    void idle();
    cocos2d::Vec3 _targetPos;
    void updateState();
    float _headingAngle;
    cocos2d::Vec3 _headingAxis;
private:
    cocos2d::Terrain* _terrain;
    cocos2d::Camera*  _cam;
    int _playerState;
};


class TerrainWalkThru : public TerrainTestDemo
{
public:
    CREATE_FUNC(TerrainWalkThru);
    TerrainWalkThru();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    void onTouchesEnd(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
protected:
    cocos2d::Camera*  _camera;
    cocos2d::Terrain* _terrain;
    Player * _player;
};

class TerrainWithLightMap : public TerrainTestDemo
{
public:
    CREATE_FUNC(TerrainWithLightMap);
    TerrainWithLightMap();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    
protected:
    cocos2d::Terrain* _terrain;
    cocos2d::Camera* _camera;
};

#endif // !TERRAIN_TESH_H
