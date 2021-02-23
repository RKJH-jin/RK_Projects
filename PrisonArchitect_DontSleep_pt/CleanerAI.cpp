#include "stdafx.h"
#include "CleanerAI.h"
#include "Character.h"
#include "ToolObject.h"

#include "MoveToTarget.h"
#include "AssignTarget.h"
#include "AssignRNDGoal.h"
#include "PutDownTrash.h"
#include "PickUpTrash.h"
#include "SweepIndex.h"
#include "StuffObject.h"
#include "MapToolScene.h"
#include "AssignCleanerRND.h"
#include "AssignDumpingTarget.h"
#include "BTCreateStuff.h"
//●
CleanerAI::CleanerAI()
{
	_root = new Selector();

	_conHaveTrash = new VoidCondition(bind(&CleanerAI::checkHaveTrash, this));
	_selHaveTrash = new Selector();
	_conInDumping = new VoidCondition(bind(&CleanerAI::checkInDumping, this));
	_seqInDumping = new Sequence();
	_putDownTrash = new PutDownTrash();
	_assignRandomGoal = new AssignRNDGoal();
	_seqNoDumping = new Sequence;
	_assignDumping = new AssignTarget();
	_conDumping = new StrCondition(bind(&CleanerAI::checkDumping, this, std::placeholders::_1), "쓰레기장");
	_seqNoGoalN = new Sequence();
	_selNonTrash = new Selector();
	_conArriveGoalN = new VoidCondition(bind(&CleanerAI::checkArriveN, this));
	_seqNonDumping = new Sequence();
	_pickUpTrash = new PickUpTrash();
	_conSweep = new VoidCondition(bind(&CleanerAI::checkSweep, this));
	_sweepIndex = new SweepIndex();
	_conHaveGoal = new VoidCondition(bind(&CleanerAI::checkHaveGoal, this));
	_selSweep = new Selector();
	_moveToGoal = new MoveToTarget();
	_selDumping = new Selector();
	_assignCleanerRND = new AssignCleanerRND();
	_assignDumpingTarget = new AssignDumpingTarget();
	_btCreateStuff = new BTCreateStuff();
}

HRESULT CleanerAI::init(Character * character)
{
	_character = character;
	_character->GetInfo().isSweep = false;
	_character->GetInfo().isStart = true;
	_character->GetInfo().isDumping = false;
	_assignDumpingTarget->init(_character, Vector2(30, 30));
	_moveToGoal->init(_character);
	_assignCleanerRND->init(_character);
	_putDownTrash->init(_character);
	_pickUpTrash->init(_character);
	_sweepIndex->init(_character);
	_btCreateStuff->init(_character);
	_btCreateStuff->setStuff(STUFFTTYPE::TRASH);

	_root->AddChild(_conDumping);
	_conDumping->AddChild(_selDumping);
	_selDumping->AddChild(_conHaveTrash);
	_conHaveTrash->AddChild(_selHaveTrash);
	_selHaveTrash->AddChild(_conInDumping);
	_conInDumping->AddChild(_seqInDumping);
	_seqInDumping->AddChild(_putDownTrash);
	_seqInDumping->AddChild(_btCreateStuff);
	_seqInDumping->AddChild(_assignCleanerRND);
	_selHaveTrash->AddChild(_seqNonDumping);
	_seqNonDumping->AddChild(_assignDumpingTarget);
	_seqNonDumping->AddChild(_moveToGoal);
	//////////////////////////////////////////////////////////////
	_selDumping->AddChild(_selNonTrash);

	_selNonTrash->AddChild(_conArriveGoalN);
	_conArriveGoalN->AddChild(_selSweep);
	_selSweep->AddChild(_conSweep);
	_conSweep->AddChild(_sweepIndex);
	_selSweep->AddChild(_pickUpTrash);

	_selNonTrash->AddChild(_seqNoGoalN);
	_seqNoGoalN->AddChild(_assignCleanerRND);
	_seqNoGoalN->AddChild(_moveToGoal);

	_root->AddChild(_seqNoDumping);
	_seqNoDumping->AddChild(_assignCleanerRND);
	_seqNoDumping->AddChild(_moveToGoal);

	return S_OK;
}

void CleanerAI::Update()
{
	_root->invoke();

}

bool CleanerAI::checkHaveTrash()
{
	// 얘는 청소부니까

	if (_character->GetInfo().toolObject != nullptr &&
		_character->GetInfo().toolObject->getToolType() == TOOLTYPE::TRASH)
	{
		return true;
	}

	return false;
}

bool CleanerAI::checkInDumping()
{
	//쓰레기장이 없을 때의 예외처리 안 돼 있음! 터짐!
	//TileAttribute* obj = DATAMANAGER->GetMapToolScene()->GetMapM()->GetTileMap()->FindTileObject("쓰레기장");
	//Vector2 temp = obj->GetLeftTopIndex();

	if (_character->GetTransform()->GetIndex() == _character->GetTransform()->GetEndIndex() && !_character->GetInfo().isDumping)
	{
		return true;
	}
	return false;
}


bool CleanerAI::checkArriveN()
{
	// 현재 내 위치가 골 지점이랑 같으면
	if (_character->GetTransform()->GetIndex() == _character->GetTransform()->GetEndIndex())
	{
		return true;
	}

	return false;
}

bool CleanerAI::checkHaveGoal()
{
	if (_character->GetTransform()->GetPath().empty())
	{
		return true;
	}
	return false;
}

bool CleanerAI::checkSweep()
{
	if (!_character->GetInfo().isSweep)
	{
		_character->GetInfo().countTime = TIMEMANAGER->getWorldTime();
		return true;
	}
	return false;
}

bool CleanerAI::checkDumping(string name)
{
	TileAttribute* obj = DATAMANAGER->GetMapToolScene()->GetMapM()->GetTileMap()->FindTileObject(name);
	if (obj == nullptr)		//null 이면 없다.
	{
		return false;
	}
	else if (obj != nullptr)	//아니면 있다.
	{
		Vector2 temp = obj->GetRandomIndex();
		_assignDumpingTarget->init(_character, temp);

		return true;
	}
	return false;
}
