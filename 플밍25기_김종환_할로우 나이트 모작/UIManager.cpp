#include "stdafx.h"
#include "UIManager.h"
#include "player.h"

HRESULT UIManager::init(float fx, float fy)
{
    _hpSoul = IMAGEMANAGER->findImage("hpbar_soul");

    for (int i = 0; i < 5; ++i)
    {
        progressBar* tBack;
        tBack = new progressBar;
        tBack->init(fx + 20 * i, fy, 55, 71);
        tBack->setProgressBarBack(IMAGEMANAGER->findImage("hpbar_back"));
        _vHpBack.push_back(tBack);

        progressBar* tFront;
        tFront = new progressBar;
        tFront->init(fx + 20 * i, fy, 55, 71);
        tFront->setProgressBarFront(IMAGEMANAGER->findImage("hpbar_front"));
        _vHpFront.push_back(tFront);      
    }

    return S_OK;
}

void UIManager::release()
{
}

void UIManager::update()
{
    int temp = (_cPlayer->getPlayer().maxHp - _cPlayer->getPlayer().hp) / 20;

    if (temp <= 5)
    {
        for (int i = _vHpFront.size() - 1; i >= _vHpFront.size() - temp; --i)
        {
            _vHpFront[i]->setFrontBool(false);
        }
    }

}

void UIManager::render(float fx, float fy)
{
    _hpSoul->render(getMemDC(), fx, fy);
    for (int i = 0; i < _vHpBack.size(); ++i)
    {
        _vHpBack[i]->getProgressBarBack()->render(getMemDC(), fx + 130 + 75 * i, fy);
    }

    for (int i = 0; i < _vHpFront.size(); ++i)
    {   
        if (_vHpFront[i]->getFrontBool())
        {
            _vHpFront[i]->getProgressBarFront()->render(getMemDC(), fx + 130 + 75 * i, fy);
        }
    }
}
