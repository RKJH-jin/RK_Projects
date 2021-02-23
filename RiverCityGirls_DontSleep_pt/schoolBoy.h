#pragma once
#include "Enemy.h"
class schoolBoy : public Enemy
{

public:

	virtual HRESULT init();
	virtual void release();
	virtual void update();
};

