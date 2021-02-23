#pragma once
#include "Character.h"

//ÁË¼ö
class Prisoner : public Character
{
private:
	GameObject* _head;	//½ÅÃ¼ÆÄÃ÷
	int _bodNum;		//¸öÅëÁ¾·ù
public:
	Prisoner();
	~Prisoner();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void SetNaked(bool isNaked);
};


