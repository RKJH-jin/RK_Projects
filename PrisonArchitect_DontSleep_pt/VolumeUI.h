#pragma once
#include "UI.h"

class VolumeUI : public UI
{
private:
	float _startPosX;
	float _barHeight;
	float _maxWidth;

	FloatRect _uiRc;

	FloatRect _masterRc;
	FloatRect _bgmRc;
	FloatRect _sfxRc;

	FloatRect _masterBar;
	FloatRect _bgmBar;
	FloatRect _sfxBar;

public:
	VolumeUI();

	virtual void update();
	virtual void render();
	
};

