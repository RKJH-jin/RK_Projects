#pragma once
#include "AllComponents.h"

class MoveToTarget;
class AssignTarget;
class Character;
class AssignTargetOnce;
class AssignRNDGoalOnce;
class BTCreateStuff;
class BTCook;
class CookerAI : public AI
{
private:

	//만들재료타입
	STUFFTTYPE _meterial;
	//루트: 시작
	Selector* _ROOT;
	//요리재료없나?
	Condition* _CONIsMeterial;
	Selector* _SELIsNotMeterial;

	//주방있음?
	Condition* _CONIsKitchen;
	//주방에 재료생성
	Sequence* _SEQCreateMeterial;
	//랜덤주방세팅함?
	Condition* _CONIsSetGoalRNDKitchen; //랜덤
	AssignTargetOnce* _ATRNDKitchen;
	//이동후 재료생성
	Sequence* _SEQMoveAfter;
	Condition* _CONIsReackKitchen; //랜덤
	BTCreateStuff* _ATCreateMeterial;

	//랜덤위치잡기
	Selector* _SELRND;//돌려쓴다
	Condition* _CONIsSetGoalRND; //랜덤
	AssignRNDGoalOnce* _ATRND;
	//도착안함?
	Condition* _CONIsNotReachGoal;//돌려쓰자
	//이동
	MoveToTarget* _ATMoveToTarget;
	//루트: 식사시간인가
	Condition* _CONIsMealTime;
	//요리중인가
	Condition* _CONIsCooking;
	BTCook* _ATCook;
	//=========================================
	//식사시간아님
	Condition* _ROOTCONIsnotMealTime;
	Condition* _ROOTCONIsKitchen;
	//주방위치찾기
	Selector* _SELFindKitchen;
	//위치세팅함?
	Condition* _CONIsSetGoalKtRND; //랜덤





public:
	CookerAI();
	~CookerAI() {};

	HRESULT init(Character* character);
	void Update();

	bool checkMealTime();
	bool checkNotMealTime();
	bool checkIsCooking();
	bool checkHasTool(TOOLTYPE tool);
	bool checkHasStuff(string stuff);
	bool checkHasMeterial();
	bool checkSetNotPos();
	bool checkNotReach();
	bool checkReach();
	bool checkIsNotMeterial();
	bool checkIsSpot(string name);
};




