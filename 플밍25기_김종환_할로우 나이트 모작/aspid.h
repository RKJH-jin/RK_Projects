#pragma once
#include "enemy.h"
#include "enemyEnum.h"

class aspid : public enemy
{
private:

public:
    aspid() {};
    ~aspid() {};

    virtual HRESULT init(float x, float y);
    virtual void release();
    virtual void update();
    virtual void render();

};

