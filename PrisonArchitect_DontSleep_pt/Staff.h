#pragma once
#include "Character.h"

class Staff : public Character
{
private:
	STAFFROLE _role;

public:
	Staff(STAFFROLE role);
	~Staff() {};

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

