#pragma once
#include "AllComponents.h"

class MoveToTarget;
class AssignTarget;
class StuffObject;
class Character;
class AssignRNDGoal;
class PutDownTrash;
class PickUpTrash;
class SweepIndex;
class AssignDumpingTarget;
class AssignCleanerRND;
class BTCreateStuff;

class CleanerAI : public AI
{
private:
	Character*  _character;

	//루트
	Selector* _root;

	//조건 노드
	Condition* _conHaveTrash;
	Selector* _selHaveTrash;
	Selector* _selDumping;
	Condition* _conInDumping;
	Sequence* _seqInDumping;
	Condition* _conDumping;
	Sequence* _seqNonDumping;
	Condition* _conArriveGoalN;

	Selector* _selNonTrash;
	Condition* _conSweep;
	Sequence* _seqNoGoalN;
	Condition* _conHaveGoal;
	Sequence* _seqNoDumping;
	Selector* _selSweep;

	//액션 노드
	AssignRNDGoal* _assignRandomGoal;
	MoveToTarget* _moveToGoal;
	AssignTarget* _assignDumping;
	PutDownTrash* _putDownTrash;
	PickUpTrash* _pickUpTrash;
	SweepIndex* _sweepIndex;
	AssignDumpingTarget* _assignDumpingTarget;
	AssignCleanerRND* _assignCleanerRND;
	BTCreateStuff* _btCreateStuff;
public:
	CleanerAI();
	~CleanerAI() {};

	HRESULT init(Character* character);
	void Update();

	bool checkHaveTrash();
	bool checkInDumping();
	bool checkArriveN();
	bool checkHaveGoal();
	bool checkSweep();
	bool checkDumping(string name);
};