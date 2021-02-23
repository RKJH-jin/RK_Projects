#pragma once
#include "Scene.h"

class LoadingScene : public Scene
{
private:
	image* _sprite;
	animation* ani;

public:
	LoadingScene() {}
	~LoadingScene() {}

	int _max;
	int _count;

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

};

static DWORD CALLBACK threadFunction(LPVOID lpParameter);
