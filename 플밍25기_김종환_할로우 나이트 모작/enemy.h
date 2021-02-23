#pragma once
#include "gameNode.h"
#include "struct_tagEnemy.h"
#include "enemyEnum.h"
#include <vector>

class enemyState;

class enemy : public gameNode
{
protected:


private:
    tagEnemy _enemy;
    enemyState* _state;

public:
    enemy();
    ~enemy();

    virtual HRESULT init();
    virtual void release();
    virtual void update();
    virtual void render();


    void aspidInit(float x, float y);
    void xeroInit(float x, float y);


    void enemyIdle();
    void enemyMove();
    void enemyAttack();
    void enemyDead();

    void hitDamage(float dmg);

    inline tagEnemy getEnemy() { return _enemy; }
    inline enemyState* getEnemyState() { return _state; }
    inline RECT getEnemyRect() { return _enemy.rc; }

    inline void setEnemy(tagEnemy enemy) { _enemy = enemy; }
    inline void setEnemyDir(ENEMY::DIRECTIONTYPE dir) { _enemy.dirType = dir; }
    inline void setState(enemyState* state) { _state = state; }
    inline void setEnemyPoint(POINT pt) { _enemy.x = pt.x, _enemy.y = pt.y; }
    inline void setEnemyImage(image* img) { _enemy.img = img; }
    inline void setEnemyAnimation(animation* ani) { _enemy.curPlayAni = ani; }
    inline void setEnemyAngle(float angle) { _enemy.angle = angle; }
    inline void setEnemyAtkType(ENEMY::ATTACKTYPE atk) { _enemy.atkType = atk; }
    inline void setEnemyWidth(float width) { _enemy.width = width; }
    inline void setEnemyHeight(float height) { _enemy.height = height; }
    inline void setEnemyPhase(ENEMY::PHASE ph) { _enemy.phase = ph; }
    inline void setEnemyPhase1(bool isBool) { _enemy.phase1 = isBool; }
    inline void setEnemyPhase2(bool isBool) { _enemy.phase2 = isBool; }
    inline void setEnemyPhase3(bool isBool) { _enemy.phase3 = isBool; }
    inline void setEnemyIsAtking(bool isBool) { _enemy.isAtking = isBool; }
    inline void setEnemyIsDead(bool isBool) { _enemy.isDead = isBool; }
    inline void setEnemyDeadAniCount(int num) { _enemy.deadAniCount = num; }
};


