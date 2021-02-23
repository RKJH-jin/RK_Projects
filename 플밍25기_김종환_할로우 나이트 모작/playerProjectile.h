#pragma once
#include "gameNode.h"
#include "playerEnum.h"

class playerProjectile : public gameNode
{
private:
    RECT _rc;
    image* _img;
    float _x, _y;
    float _preX, _preY;
    float _goalX, _goalY;
    float _angle;
    float _speed;
    float _width, _height;
    bool isStart;
    bool isEnd;
    PLAYER::DIRECTION _dir;

public:
    playerProjectile() {};
    ~playerProjectile() {};

    virtual HRESULT init(float playerX, float playerY, float playerWidth, float playerHeight, PLAYER::DIRECTION dir);
    virtual void release();
    virtual void update();
    virtual void render();

    void hornetSpearMove();
    BOOL hornetSpearCheck();

    inline RECT getRect() { return _rc; }
};

