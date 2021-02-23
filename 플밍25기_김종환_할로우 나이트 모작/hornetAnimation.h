#pragma once
#include "gameNode.h"
#include <map>

class hornetAnimation : public gameNode
{
private:
    typedef map<string, animation*>             mapAnimation;
    typedef map<string, animation*>::iterator   mapIterAnimation;
private:
    mapAnimation        _mAnimation;
    mapIterAnimation    _miAnimation;
    animation* _idleNormalLeft;
    animation* _idleNormalRight;
    image* img;
    float _x, _y;


public:
    hornetAnimation() {};
    ~hornetAnimation() {};

    virtual HRESULT init(float x, float y);
    virtual void release();
    virtual void update(float x, float y);
    virtual void render();

};

