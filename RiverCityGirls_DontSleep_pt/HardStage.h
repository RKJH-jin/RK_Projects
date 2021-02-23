#pragma once
#include "Stage.h"
class HardStage : public Stage
{

public:

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

