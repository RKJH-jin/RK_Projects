#pragma once
#include "singletonBase.h"
#include "timer.h"

class timeManager : public singletonBase<timeManager>
{
private:
    timer* _timer;

public:
    timeManager();
    ~timeManager();

    virtual HRESULT init();
    virtual void release();
    virtual void update(float lock = 0.0f);
    virtual void render(HDC hdc);

    inline float getElapsedTime() const { return _timer->getElapsedTime(); }
    inline float getWorldTime() const { return _timer->getWorldTime(); }
};

