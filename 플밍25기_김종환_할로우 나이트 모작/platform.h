#pragma once
#include "object.h"
#include "objectEnum.h"

class platform : public object
{
public:
    platform() {};
    ~platform() {};

    virtual HRESULT init(float x, float y, int width, int height, objectType type);
    virtual void release();
    virtual void update();
    virtual void render();

};

