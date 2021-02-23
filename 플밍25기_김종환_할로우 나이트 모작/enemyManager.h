#pragma once
#include "gameNode.h"
#include "enemy.h"
#include "aspid.h"
#include "xero.h"
#include <vector>

class player;
class projectile;

class enemyManager : public gameNode
{
private:
    typedef vector<enemy*>              vEnemy;
    typedef vector<enemy*>::iterator    viEnemy;
private:
    vEnemy _vAspid;
    viEnemy _viAspid;

    vEnemy _vXero;
    viEnemy _viXero;

    player* _cPlayer;
    projectile* _cProjectile;

public:
    enemyManager();
    ~enemyManager();

    virtual HRESULT init();
    virtual void release();
    virtual void update();
    virtual void render();

    void eraseEnemy();

    void setLinkPlayer(player* pl) { _cPlayer = pl; }
    void setLinkProjectile(projectile* pj) { _cProjectile = pj; }
    

    inline vEnemy getVXero() { return _vXero; }
    inline vEnemy getVAspid() { return _vAspid; }
};

