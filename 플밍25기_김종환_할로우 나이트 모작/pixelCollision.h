#pragma once
#include "gameNode.h"
class pixelCollision : public gameNode
{
private:
    image* _testImg;
    image* _ball;

    RECT _rc;
    float _x, _y;
    int _probeY;

    RECT _msRC;
public:
    pixelCollision() {};
    ~pixelCollision() {};

    virtual HRESULT init();
    virtual void release();
    virtual void update();
    virtual void render();



};

