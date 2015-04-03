#ifndef TERRAIN_TESH_H
#include "../testBasic.h"
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
    Terrain * _terrain;
protected:
    Camera * _camera;
};

#define PLAYER_STATE_LEFT 0 
#define PLAYER_STATE_RIGHT 1
#define PLAYER_STATE_IDLE 2
#define PLAYER_STATE_FORWARD 3
#define PLAYER_STATE_BACKWARD 4

class Player : public Sprite3D
{
public:
    static Player * create(const char * file, Camera * cam, Terrain * terrain);
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
    Vec3 _headingAxis;
private:
    Terrain * _terrain;
    Camera * _cam;
    int _playerState;
};


class TerrainWalkThru : public TerrainTestDemo
{
public:
    CREATE_FUNC(TerrainWalkThru);
    TerrainWalkThru();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    void onTouchesEnd(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
protected:
    Label * forward;
    Label * backward;
    Label * left;
    Label * right;
    Camera * _camera;
    Terrain * _terrain;
    Player * _player;
};

#endif // !TERRAIN_TESH_H
