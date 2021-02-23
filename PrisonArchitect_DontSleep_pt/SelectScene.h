#pragma once
#include "Scene.h"
class SelectScene : public Scene
{

private:

public:

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

};

