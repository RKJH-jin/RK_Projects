#pragma once
#include "GameObject.h"
class Mouse : public GameObject
{
protected:
	MOUSESTATE _state;			//마우스 스테이트
	bool _isOnUI;				//UI위에 있는지
	float _speed;

public:
	Mouse() { _speed = 2.0f; };
	virtual void Init();
	virtual void Release();
	virtual void Update();
	virtual void Render();

	void SetState(MOUSESTATE state) { _state = state; };
	float GetSpeed() { return _speed; }

};

