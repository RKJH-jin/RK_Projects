#pragma once
#include "enemy.h"
#include "enemyEnum.h"

class xero : public enemy
{
private:
public:
    xero() {};
    ~xero() {};

    virtual HRESULT init(float x, float y);
    virtual void release();
    virtual void update();
    virtual void render();
};

