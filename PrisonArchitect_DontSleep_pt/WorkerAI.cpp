#include "stdafx.h"
#include "WorkerAI.h"
#include "MoveToTarget.h"
#include "AssignTarget.h"
#include "AssignTargetOnce.h"

#include "MapToolScene.h"


WorkerAI::WorkerAI()
{
	//루트
	_root = new Selector();

	_conIsStorage = new StrCondition(bind(&WorkerAI::IsTileObject, this, std::placeholders::_1), "창고");
	_seqIsTree = new Sequence();
	_assGoToStorage = new AssignTargetOnce;
	_actMoveToStorage = new MoveToTarget;
}

HRESULT WorkerAI::init(Character * character)
{
	_character = character;

	_actMoveToStorage->init(_character);

	_root->AddChild(_conIsStorage);
	_conIsStorage->AddChild(_seqIsTree);
	_seqIsTree->AddChild(_assGoToStorage);
	_seqIsTree->AddChild(_actMoveToStorage);

	return S_OK;
}

void WorkerAI::Update()
{
	_root->invoke();
}

bool WorkerAI::IsTileObject(string name)
{
	TileAttribute* obj = DATAMANAGER->GetMapToolScene()->GetMapM()->GetTileMap()->FindTileObject(name);

	if (obj == nullptr)		//null 이면 없다.
	{
		return false;
	}
	else if (obj != nullptr)	//아니면 있다.
	{
		Vector2 temp = obj->GetCenterIndex();
		_assGoToStorage->init(_character, temp);

		return true;
	}
	return false;
}

bool WorkerAI::IsStuffObject(string name)
{
	return false;
}
