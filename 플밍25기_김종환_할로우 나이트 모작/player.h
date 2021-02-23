#pragma once
#include "gameNode.h"
#include "playerEnum.h"
#include "hornetAnimation.h"
#include "struct_tagPlayer.h"
#include <vector>

#define DASHLENGTH 600
#define DASHSPEED _player.speed * 2

using namespace PLAYER;

struct tagCollisionCheck
{
    RECT objectRect;
    BOOL boolValue;
};

class mapManager;
class projectile;
class enemyManager;

class player : public gameNode
{
private:
    tagPlayer _player;
    timer* _testTimer;
    hornetAnimation* _hornetAni;
    mapManager* _cMapManager;
    projectile* _cProjectile;
    enemyManager* _cEnemyManager;

    int checkNum = 0;
public:
    player();
    ~player();

    virtual HRESULT init();
    virtual void release();
    virtual void update();
    virtual void render();

    void makePlayerHornet();
    void playerControl();
    void playerMove();
    void playerAtkEnemy();

    void hitDamage(float dmg);


    void hornetAnimationSelect();
    void animationUpdateReset();
    void hornetAnimationRender();

    tagCollisionCheck rectCollision();


    //=====================ÇÈ¼¿ Ã¼Å©=====================//
    BOOL pixelCheckLeft();
    BOOL pixelCheckRight();
    BOOL pixelCheckUp();
    BOOL pixelCheckDown();
    BOOL pixelCheckDownLeft();
    BOOL pixelCheckDownRight();
    //==========================getter==========================//
    inline tagPlayer getPlayer() { return _player; }
    
    inline void setPlayerState(PLAYER::STATE state) { _player.stateType = state; }
    inline void setPlayerDirection(PLAYER::DIRECTION dir) { _player.dirType = dir; }
    inline void setPlayerPosition(PLAYER::POSITION pos) { _player.posType = pos; }
    inline RECT getRect() { return _player.rc; }
    inline bool getIsJump() { return _player.isJump; }
    inline bool getIsAttack() { return _player.isAttack; }

    inline void setIsJump(bool _is) { _player.isJump = _is; }
    inline void setIsAttack(bool _is) { _player.isAttack = _is; }

    inline void setLinkMapManager(mapManager* _mM) { _cMapManager = _mM; }
    inline void setLinkProjectile(projectile* pj) { _cProjectile = pj; }
    inline void setLinkEnemyManager(enemyManager* em) { _cEnemyManager = em; }
};

