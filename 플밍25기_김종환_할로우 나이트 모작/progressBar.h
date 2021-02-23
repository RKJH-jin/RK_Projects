#pragma once
#include "gameNode.h"
class progressBar : public gameNode
{
private:
    RECT _rc;
    float x, y;
    int width, maxWidth;
    int height, maxHeight;

    image* _progressBarFront;
    image* _progressBarBack;
    bool frontOn = true;
public:
    progressBar() {};
    ~progressBar() {};

    virtual HRESULT init(float fx, float fy, int iwidth, int iheight);
    virtual void release();
    virtual void update();
    virtual void render();

    virtual void adjRender();
    
    void setGauge(float currentGauge, float maxGauge);

    inline RECT getRect() { return _rc; }
    inline void setX(float fx) { x = fx; }
    inline void setY(float fy) { y = fy; }
    inline image* getProgressBarFront() { return _progressBarFront; }
    inline image* getProgressBarBack() { return _progressBarBack; }
    inline void setProgressBarFront(image* img) { _progressBarFront = img; }
    inline void setProgressBarBack(image* img) { _progressBarBack = img; }
    inline bool getFrontBool() { return frontOn; }
    inline void setFrontBool(bool isBool) { frontOn = isBool; }
};

