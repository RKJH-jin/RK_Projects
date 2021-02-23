#pragma once
#include "singletonBase.h"
#include "animation.h"
#include <map>

class animationManager : public singletonBase<animationManager>
{
private:
    typedef map<string, animation*>             mapAnimation;
    typedef map<string, animation*>::iterator   mapIterAnimation;
private:
    mapAnimation        _mAnimation;
    mapIterAnimation    _miAnimation;

public:
    animationManager();
    ~animationManager();

    virtual HRESULT init();
    virtual void release();
    virtual void update();
    virtual void render();

    BOOL deleteAnimation(string strKey);
    BOOL deleteAll();

    animation* findAnimation(string strKey);

    // 현재 애니메이션을 제외하고 나머지 다 리셋
    void resetExceptCurrentAni(string strKey);
    // strKey 애니메이션을 리셋
    void resetCurrentAni(string strKey);

    animation* addAnimation(string imgStrKey, string aniStrKey, BOOL reverse, BOOL loop, int fps);
    animation* addAnimation(string imgStrKey, string aniStrKey, int idxStart, int idxEnd, BOOL reverse, BOOL loop, int fps);
    animation* addAnimation(string strKey, int totalW, int totalH, int frameW, int frameH, BOOL reverse, BOOL loop, int fps);
    
    
    void updateAnimation(string strKey, int num);
    void aniRender(string imgStrKey, string aniStrKey, HDC hdc, float x, float y);
    
};

