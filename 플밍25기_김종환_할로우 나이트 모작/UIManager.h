#pragma once
#include "gameNode.h"
#include "progressBar.h"
#include <vector>
class player;

class UIManager : public gameNode
{
private:
    vector<progressBar*>            _vHpBack;
    vector<progressBar*>::iterator  _viHpBack;

    vector<progressBar*>            _vHpFront;
    vector<progressBar*>::iterator  _viHpFront;

    image* _hpSoul;
private:
    player* _cPlayer;
    
public:
    UIManager() {};
    ~UIManager() {};

    virtual HRESULT init(float fx, float fy);
    virtual void release();
    virtual void update();
    virtual void render(float fx, float fy);

    inline void setLinkPlayer(player* pl) { _cPlayer = pl; }
};

