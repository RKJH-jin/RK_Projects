#pragma once
#include "UI.h"
class UpperUI : public UI
{

private:
	Button* _schedule;
	Button* _manageDay;
	Button* _money;
	Button* _prisoner;

public:
	UpperUI();

	virtual void release();
	virtual void update();
	virtual void render();
};

