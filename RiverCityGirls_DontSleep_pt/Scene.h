#pragma once
#include "gameNode.h"

/*====================================================================
	모든 씬들은 씬을 상속받습니다.
====================================================================*/

class Scene : public gameNode
{
protected:
	image* _background;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

