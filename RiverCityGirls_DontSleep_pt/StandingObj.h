#pragma once
#include "Object.h"
class StandingObj : public Object
{

public:
	StandingObj(OBJECT_TYPE type, vector3 pos);

	virtual HRESULT init();

	virtual void release();
	virtual void update();
	virtual void render();
};

