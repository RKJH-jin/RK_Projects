#pragma once
#include "GameObject.h"
#include "AllComponents.h"
#include "AllEnums.h"

/*
바닥에 있는 짐 오브젝트 : 무조건 플레이어 밑으로 렌더된다. 사용횟수에 따라 이미지가 바뀐다.
*/
class StuffObject : public GameObject
{
private:
	int _useCount;		//사용횟수
	STUFFTTYPE _stuffType;
public:
	StuffObject(STUFFTTYPE stuffType);
	~StuffObject() {};

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void MouseEnter();
	virtual void MouseStay();
	virtual void MouseExit();

	//게터
	virtual int getUseCount() { return _useCount; }
	STUFFTTYPE getStuffType() { return _stuffType; }

	//세터
	virtual void setUseCount(int useCount) { _useCount = useCount; }

};
