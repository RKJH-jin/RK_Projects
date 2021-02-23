#pragma once
#include "UI.h"
class HelperUI : public UI
{
private:
	Button* _helper;
	Image* _helperImg;
public:
	HelperUI();

	virtual void update();
	virtual void render();
};

