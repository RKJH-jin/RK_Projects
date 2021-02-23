#pragma once
#include "Stage.h"
class BossStage : public Stage
{

public:

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

