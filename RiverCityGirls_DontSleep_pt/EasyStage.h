#pragma once
#include "Stage.h"

class EasyStage : public Stage
{
private:

public:

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

