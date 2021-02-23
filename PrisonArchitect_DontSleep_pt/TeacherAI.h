#pragma once
#include "AllComponents.h"

class MoveToTarget2;
class StuffObject;
class AssignTargetOnce;
class AssignRNDGoalOnce;
class ToolObject;

class TeacherAI : public AI
{
private:

	Selector* _root;
	Sequence* _noPlace;
	Sequence* _hasPlace;
	Sequence* _hang;

	Condition* _isPlace;
	Condition* _isReached;
	Condition* _isWorking;

	AssignTargetOnce* _home;
	MoveToTarget2* _moveToHome;

	AssignRNDGoalOnce* _rndgoal;
	MoveToTarget2* _hangAround;

	AssignTargetOnce* _getWork;
	MoveToTarget2* _working;

	ToolObject* _object;

public:
	TeacherAI();

	HRESULT init(Character* character);
	void Update();

	bool IsTileObject(string name);
	bool IsReached(string name);
};

