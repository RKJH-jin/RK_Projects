#pragma once
#include "gameNode.h"
#include "objectEnum.h"
#include <vector>

class object : public gameNode
{
protected:
    RECT _rc;
    image* _img;

    float _x, _y;
    float _width, _height;
    objectType _type;

private:

public:
    object() {};
    ~object() {};

    virtual HRESULT init(float x, float y, int width, int height, objectType type);
    virtual void release();
    virtual void update();
    virtual void render();

    inline RECT getRect() { return _rc; }
    inline image* getImage() { return _img; }
    inline void setImage(image* img) { _img = img; }
};

