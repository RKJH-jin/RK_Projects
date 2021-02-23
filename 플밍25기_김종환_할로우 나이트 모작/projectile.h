#pragma once
#include "gameNode.h"
#include "playerEnum.h"
#include "enemyEnum.h"
#include "playerProjectile.h"
#include "enemyProjectile.h"
#include <vector>

class player;
class enemyManager;

class projectile : public gameNode
{
private:
    vector<enemyProjectile*>            _vAspidPJ;
    vector<enemyProjectile*>::iterator  _viAspidPJ;
private:
    vector<enemyProjectile*>            _vXeroPJ;
    vector<enemyProjectile*>::iterator  _viXeroPJ;
    vector<int>                         _vAtkSpearIdx;
    vector<int>                         _vNonAtkSpearIdx;
    int spearEndCount = 0;
private:
    player* _cPlayer;
    enemyManager* _cEnemyManager;
    playerProjectile* _spear;
    
public:

    virtual HRESULT init();
    virtual void release();
    virtual void update();
    virtual void render();

    void hornetSpearInit(float playerX, float playerY, float playerWidth, float playerHeight, PLAYER::DIRECTION dir);
    void playerPJUpdate();
    void playerPJRender();

    void aspidPJInit(float enemyX, float enemyY, float enemyWidth, float enemyHeight, float enemyAngle, ENEMY::ENEMYTYPE enemyType, ENEMY::DIRECTIONTYPE dir);
    void aspidPJUpdate();
    void aspidPJRender();
    void removeAspidPJ(int arrNum);

    void xeroPJInit(float enemyX, float enemyY, float enemyWidth, float enemyHeight, float enemyAngle, ENEMY::PHASE ph);
    void xeroPJUpdate();
    void xeroPJRender();
    void removeXeroPJ(int arrNum);

    void collision();

    inline void setLinkPlayer(player* pl) { _cPlayer = pl; }
    inline void setLinkEnemyManager(enemyManager* em) { _cEnemyManager = em; }
    inline BOOL getCheckSpear()
    { 
        if (_spear == nullptr) return false;
        else return true;
    }
};

