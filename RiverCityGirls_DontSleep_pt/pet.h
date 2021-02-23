#pragma once
#include "gameNode.h"
#include "GameObject.h"

class pet :public GameObject
{
	GameObject _obj;
	float _xOffset, _yOffset;	//오프셋
	float _speed;
public:
	pet() {};
	~pet() {};
	virtual HRESULT init();		//초기화
	virtual void release();		//해제
	virtual void update(vector3 pos);		//업데이트
	virtual void render(HDC hdc);		//렌더
};

