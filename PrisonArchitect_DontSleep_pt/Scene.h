#pragma once
#include "gameNode.h"
#include "Mouse.h"

class Scene : public gameNode
{

protected:
	Camera* _camera;
	Mouse* _mouse;

public:

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	Camera* GetCamera() { return _camera; }
};

