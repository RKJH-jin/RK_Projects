#pragma once
#include "AllComponents.h"

class MoveToTarget;
class AssignTarget;
class StuffObject;
class AssignTargetOnce;

class WorkerAI : public AI
{
private:

	//루트
	Selector* _root;

	//창고
	Condition* _conIsStorage;		//창고 있는지
	Sequence* _seqIsTree;
	AssignTargetOnce* _assGoToStorage;
	MoveToTarget* _actMoveToStorage;

	//휴식
	Condition* _conIsBreakTime;		//휴식시간
	Condition* _conIsLounge;		//휴게실 있는지

	//랜덤




public:
	WorkerAI();

	HRESULT init(Character* character);
	void Update();

	bool IsTileObject(string name);
	bool IsStuffObject(string name);


};

