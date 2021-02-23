#pragma once
#include "singletonBase.h"
#include "UI.h"

class UIManager : public singletonBase<UIManager>
{
private:
	vector<BarButtonUI*> _underBar;
	vector<WindowUI*> _underBarWindowUI;


	BarButtonUI* currentUnderBarActive;
public:
	UIManager();
	~UIManager();


	HRESULT init();
	void release();
	void update();
	void render();

};

