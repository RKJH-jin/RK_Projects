#pragma once
#include "gameNode.h"
#include "enemyEnum.h"

class enemyProjectile : public gameNode
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

    float _distance;
    POINT pts[4];
    POINT _LT, _RT, _LB, _RB;
    ENEMY::ENEMYTYPE _enemyType;
    ENEMY::DIRECTIONTYPE _dir;
    bool isFire;
    bool isEnd;
public:
    enemyProjectile() {};
    ~enemyProjectile() {};

    virtual HRESULT init(float enemyX, float enemyY, float enemyWidth, float enemyHeight, float enemyAngle, ENEMY::ENEMYTYPE enemyType, ENEMY::DIRECTIONTYPE dir);
    virtual void release();
    virtual void update();
    virtual void render();

    void aspidProjectileInit(float enemyX, float enemyY, float enemyWidth, float enemyHeight, float enemyAngle);
    BOOL aspidProjectileMove();
    void aspidProjectileRender();

    void xeroProjectileInit(float enemyX, float enemyY, float enemyWidth, float enemyHeight, float enemyAngle, float distance, ENEMY::DIRECTIONTYPE dir);
    void xeroProjectileMove(float enemyX, float enemyY);
    void xeroProjectileFire(float angle);
    void xeroProjectileFireMove();
    bool xeroProjectileFireMoveCheck(float enemyX, float enemyY, float enemyWidth, float enemyHeight);
    void xeroProjectileRender();
    void xeroProjectileFireRender();

    inline void setProjectileX(float x) { _x = x; }
    inline void setProjectileY(float y) { _y = y; }
    inline float getProjectileX() { return _x; }
    inline float getProjectileY() { return _y; }
    inline bool getProjectileIsFire() { return isFire; }
    inline void setProjectileIsFire(bool isBool) { isFire = isBool; }
    inline bool getProjectileIsEnd() { return isEnd; }
    inline void setProjectileIsEnd(bool isBool) { isEnd = isBool; }
    inline RECT getRect() { return _rc; }
    inline POINT getLB() { return _LB; }
    inline POINT getRB() { return _RB; }
    inline POINT getLT() { return _LT; }
    inline POINT getRT() { return _RT; }
};

