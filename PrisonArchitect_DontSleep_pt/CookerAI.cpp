#include "stdafx.h"
#include "CookerAI.h"
#include "MoveToTarget.h"
#include "AssignTarget.h"
#include "Character.h"
#include "MapToolScene.h"
#include "StuffObject.h"
#include "AssignTargetOnce.h"
#include "AssignRNDGoalOnce.h"
#include "BTCook.h"
#include "BTCreateStuff.h"

CookerAI::CookerAI()
{
	//루트: 시작
	_ROOT = new Selector;
	//요리재료없음?
	_CONIsMeterial = new VoidCondition(bind(&CookerAI::checkIsNotMeterial, this));
	_SELIsNotMeterial = new Selector;
	//주방있음?
	_CONIsKitchen = new StrCondition(bind(&CookerAI::checkIsSpot, this, std::placeholders::_1), "부엌");
	//주방에 재료 생성
	_SEQCreateMeterial = new Sequence;
	//랜덤주방세팅함?
	_CONIsSetGoalRNDKitchen = new VoidCondition(bind(&CookerAI::checkSetNotPos, this));
	_ATRNDKitchen = new AssignTargetOnce;
	//이동후 재료생성
	_SEQMoveAfter = new Sequence;
	_ATCreateMeterial = new BTCreateStuff;
	//랜덤위치잡기
	_SELRND = new Selector;
	_CONIsSetGoalRND = new VoidCondition(bind(&CookerAI::checkSetNotPos, this));
	_ATRND = new AssignRNDGoalOnce;
	//도착안함?
	_CONIsNotReachGoal = new VoidCondition(bind(&CookerAI::checkNotReach, this));
	_CONIsReackKitchen = new VoidCondition(bind(&CookerAI::checkReach, this));
	//이동세팅
	_ATMoveToTarget = new MoveToTarget;
	//요리중?
	_CONIsCooking = new VoidCondition(bind(&CookerAI::checkIsCooking, this));
	_ATCook = new BTCook();
	//식사시간?
	_CONIsMealTime = new VoidCondition(bind(&CookerAI::checkMealTime, this));
	//식사시간아님

	//루트: 주방있음?
	_ROOTCONIsnotMealTime = new VoidCondition(bind(&CookerAI::checkNotMealTime, this));
	_ROOTCONIsKitchen = new StrCondition(bind(&CookerAI::checkIsSpot, this, std::placeholders::_1), "부엌");
	_SELFindKitchen = new Selector;
	//주방골정함?
	_CONIsSetGoalKtRND = new VoidCondition(bind(&CookerAI::checkSetNotPos, this));
}

HRESULT CookerAI::init(Character * character)
{
	//초기화
	_character = character;
	_ATMoveToTarget->init(_character);
	_ATRND->init(_character);
	_ATCreateMeterial->init(_character);
	_ATCook->init(_character);

	//노드 연결
	{
		//루트: 시작
		_ROOT->AddChild(_CONIsMeterial);
		//◈ 요리재료없나?
		_CONIsMeterial->AddChild(_SELIsNotMeterial);
		//주방있음?
		_SELIsNotMeterial->AddChild(_CONIsKitchen);
		//주방에재료생성
		_CONIsKitchen->AddChild(_SEQCreateMeterial);

		//주방위치세팅함?
		_SEQCreateMeterial->AddChild(_CONIsSetGoalRNDKitchen);
		_CONIsSetGoalRNDKitchen->AddChild(_ATRNDKitchen);
		//이동후재료생성★ _SEQCreateMeterial
		_SEQCreateMeterial->AddChild(_SEQMoveAfter);
		_SEQMoveAfter->AddChild(_CONIsNotReachGoal);
		_SEQMoveAfter->AddChild(_ATMoveToTarget);
		_SEQMoveAfter->AddChild(_CONIsReackKitchen);
		_CONIsReackKitchen->AddChild(_ATCreateMeterial);

		//랜덤위치잡기
		_SELIsNotMeterial->AddChild(_SELRND);
		_SELRND->AddChild(_CONIsSetGoalRND);
		_CONIsSetGoalRND->AddChild(_ATRND);
		_SELRND->AddChild(_CONIsNotReachGoal);
		_CONIsNotReachGoal->AddChild(_ATMoveToTarget);

		//◈ 요리 안끝났나?
		_ROOT->AddChild(_CONIsCooking);
		_CONIsCooking->AddChild(_ATCook);

		//◈ 식사시간인가?
		_ROOT->AddChild(_CONIsMealTime);
		_CONIsMealTime->AddChild(_ATCook);

		//주방확인
		_ROOT->AddChild(_ROOTCONIsnotMealTime);
		_ROOTCONIsnotMealTime->AddChild(_ROOTCONIsKitchen);
		_ROOTCONIsKitchen->AddChild(_SELFindKitchen);
		//주방위치세팅
		_SELFindKitchen->AddChild(_CONIsSetGoalKtRND);
		_CONIsSetGoalKtRND->AddChild(_ATRNDKitchen);
		//주방이동
		_SELFindKitchen->AddChild(_CONIsNotReachGoal);
		_CONIsNotReachGoal->AddChild(_ATMoveToTarget);

		//랜덤돌아다니는 루트 연결
		_ROOT->AddChild(_SELRND);


	}
	return S_OK;
}

void CookerAI::Update()
{
	_ROOT->invoke();
}

//식사시간인지 체크
bool CookerAI::checkMealTime()
{
	if (DATAMANAGER->GetInfo().schedule == TIMESCHEDULE::MEAL)return true;
	if (DATAMANAGER->GetInfo().schedule != TIMESCHEDULE::MEAL)return false;
}

//식사시간아닌지체크
bool CookerAI::checkNotMealTime()
{
	if (DATAMANAGER->GetInfo().schedule != TIMESCHEDULE::MEAL)
	{
		_character->GetInfo().toolObject->SetToolType(TOOLTYPE::NONE);
		_character->initHands();
		return true;
	}

	if (DATAMANAGER->GetInfo().schedule == TIMESCHEDULE::MEAL)return false;
}

//요리중인지 체크
bool CookerAI::checkIsCooking()
{
	if (_character->GetInfo().btState == BTSTATE::COOKING)return true;
	return false;
}

//도구 들고 있는지 체크
bool CookerAI::checkHasTool(TOOLTYPE tool)
{
	if (_character->GetInfo().toolObject->getToolType() == tool)
		return true;
	return false;
}



//짐이 존재 하는지 체크
bool CookerAI::checkHasStuff(string stuff)
{
	StuffObject* obj = DATAMANAGER->GetMapToolScene()->GetMapM()->FindStuffObject(stuff);

	if (obj == nullptr)return false;
	else if (obj != nullptr)
	{

		return true;
	}

}


bool CookerAI::checkHasMeterial()
{
	if (_character->GetInfo().toolObject != nullptr)
	{
		if (_character->GetInfo().toolObject->getToolType() == TOOLTYPE::BACON
			|| _character->GetInfo().toolObject->getToolType() == TOOLTYPE::CABBAGE
			|| _character->GetInfo().toolObject->getToolType() == TOOLTYPE::POTATO
			)return true;

	}
	return false;
}



//골세팅이 안되어는지확인
bool CookerAI::checkSetNotPos()
{

	if (_character->GetInfo().goalState != GOALSTATE::GOALSET)
	{
		_character->GetInfo().goalState = GOALSTATE::NONE;
		return true;
	}


	return false;
}
//도착안했는지 확인
bool CookerAI::checkNotReach()
{

	if (_character->GetInfo().goalState != GOALSTATE::GOALREACH)
	{
		return true;
	}
	return false;
}

//도착했는지
bool CookerAI::checkReach()
{
	if (_character->GetInfo().goalState == GOALSTATE::GOALREACH)
	{
		return true;
	}

	return false;
}

//요리재료가 존재하는지 확인
bool CookerAI::checkIsNotMeterial()
{

	MapManager* mapM = DATAMANAGER->GetMapToolScene()->GetMapM();

	if (!mapM->FindStuffObject("베이컨 꾸러미"))
	{
		_ATCreateMeterial->setStuff(STUFFTTYPE::BACONS);
		return true;
	}

	if (!mapM->FindStuffObject("양배추 꾸러미"))
	{
		_ATCreateMeterial->setStuff(STUFFTTYPE::CABBAGES);
		return true;
	}

	if (!mapM->FindStuffObject("감자 꾸러미"))
	{
		_ATCreateMeterial->setStuff(STUFFTTYPE::POTATOS);
		return true;
	}



	return false;
}

bool CookerAI::checkIsSpot(string name)
{
	TileAttribute* obj = DATAMANAGER->GetMapToolScene()->GetMapM()->GetTileMap()->FindTileObject(name);

	if (obj == nullptr)		//null 이면 없다.
		return false;
	else if (obj != nullptr)	//아니면 있다.
	{
		Vector2 temp = obj->GetRandomIndex();
		_ATRNDKitchen->init(_character, temp);
		return true;
	}
	return false;
}
