#pragma once
#include "Enemy.h"
class cheerLeader : public Enemy
{
private:

public:

	virtual HRESULT init();
	virtual void release();
	virtual void update();
};

