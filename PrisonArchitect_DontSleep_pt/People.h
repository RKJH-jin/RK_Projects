#pragma once
#include "Character.h"

class People : public Character
{
private:
	PEOPLEROLE _role;

public:
	People(PEOPLEROLE role);
	~People() {};

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

