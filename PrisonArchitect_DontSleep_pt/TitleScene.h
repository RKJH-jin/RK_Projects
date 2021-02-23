#pragma once
#include "Scene.h"
class TitleScene : public Scene
{
private:
	Image* _logoImg;
	Image* _background;
	UI* _volume;
	wstring _text;


public:

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

};

