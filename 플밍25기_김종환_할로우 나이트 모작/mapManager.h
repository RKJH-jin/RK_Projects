#pragma once
#include "gameNode.h"
#include "object.h"
#include "platform.h"
#include <vector>

class player;

class mapManager : public gameNode
{
private:
    object* _townFloor1;
    object* _townWallLeft;
    object* _wall2;
    object* _platform1;
    float _gravity;
    player* _cPlayer;
    vector<object*>             _vTownObject;
    vector<object*>::iterator   _viTownObject;

public:
    mapManager();
    ~mapManager();

    virtual HRESULT init();
    virtual void release();
    virtual void update();
    virtual void render();

    void platformInit(float x, float y, float width, float height, string imgKey, objectType obj);

    inline float getGravity() { return _gravity; }
    inline void setLinkPlayer(player* _pl) { _cPlayer = _pl; }

    inline vector<object*> getVObject() { return _vTownObject; }
    inline vector<object*>::iterator getVIObject() { return _viTownObject; }
};
