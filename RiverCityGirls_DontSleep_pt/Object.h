#pragma once
#include "gameNode.h"
#include "GameObject.h"
class Player;

struct tagInfo
{
	bool iscollision;
	int value;
	Player* player;

	ITEM_TYPE type;
};

class Object : public gameNode
{
protected:
	GameObject _obj;
	OBJECT_TYPE _type;
	tagInfo _info;
	float _renderTimer;

public:

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();


	float getTimer() { return _renderTimer; }
	void setTimer(float time) { _renderTimer = time; }
	GameObject* getObj() { return &_obj; }
	GameObject& getRefObj() { return _obj; }
	tagInfo& getInfo() { return _info; }
	OBJECT_TYPE getType() { return _type; }

	void setLinkPlayer(Player* player) { _info.player = player; }
};

