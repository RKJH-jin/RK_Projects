#pragma once
#include "GameObject.h"
#include "AllComponents.h"
#include "AllEnums.h"

/*
캐릭터가 드는 도구 오브젝트 : 무조건 플레이어 위로 렌더된다.
*/
class Character;
class ToolObject : public GameObject
{
private:
	int _useCount;		//사용횟수
	TOOLTYPE _toolType;

	Character* _charecter;
public:
	ToolObject();
	~ToolObject() {};

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void MouseEnter();
	virtual void MouseStay();
	virtual void MouseExit();

	//게터
	virtual int getUseCount() { return _useCount; }
	virtual TOOLTYPE& getToolType() { return _toolType; }
	virtual void SetToolType(TOOLTYPE type);
	//세터
	virtual void setUseCount(int useCount) { _useCount = useCount; }
	//링커
	virtual void setLinkCharacter(Character* character);
};