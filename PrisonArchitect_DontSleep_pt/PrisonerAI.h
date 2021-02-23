#pragma once

#include "AllComponents.h"

class PrisonerEat;
class TrayDirty;
class CreateTray;


class PrisonerAI : public AI
{
private:
    Selector* _root;
    //==========취침==========//
    StrCondition* _conTimeSleep;
    Selector* _selTimeSleep;
    StrCondition* _conHaveJail;

    StrCondition* _conInJail;
    Selector* _selHaveJail;
    AssignTarget* _assJail;
    VoidCondition* _conHaveGoalToJail;

    //==========식사==========//
    StrCondition* _conTimeMeal;
    Selector* _selTimeMeal;
    StrCondition* _conHaveRestaurant;
    Selector* _selHaveRestaurant;
    StrCondition* _conInRestaurant;
    VoidCondition* _conHaveGoalToRestaurant;
    AssignTarget* _assRestaurant;

    //==========식당에서==========//
    Selector* _selInRestaurant;
    StrCondition* _conHaveTable;
    
    Selector* _selHaveTable;
    VoidCondition* _conUseTable;
    Sequence* _seqUseTable;
    TrayDirty* _trayDirty;
    PrisonerEat* _prisonerEat;

    StrCondition* _conHaveEmptyTable;
    Selector* _selHaveEmptyTable;
    StrCondition* _conHaveTray;
    
    Selector* _selHaveTray;
    VoidCondition* _conHaveGoalToTable;
    AssignTarget* _assGoalToTable;
    
    VoidCondition* _conArriveTable;
    

    Selector* _selNonHaveTray;
    StrCondition* _conHaveDBTable;

    Selector* _selHaveDBTable;
    VoidCondition* _conUseDBTable;
    StrCondition* _conHaveEmptyDBTable;
    Selector* _selHaveEmptyDBTable;
    VoidCondition* _conHaveGoalToDBTable;
    AssignTarget* _assGoalToDBTable;
    CreateTray* _createTray;
    VoidCondition* _conArriveDBTable;
    float eatTimer;
    //==========샤워==========//
    StrCondition* _conTimeWash;
    Selector* _selTimeWash;
    StrCondition* _conHaveShowerRoom;
    Selector* _selHaveShowerRoom;
    StrCondition* _conInShowerRoom;
    VoidCondition* _conHaveGoalToShowerRoom;
    AssignTarget* _assShowerRoom;

    //==========투옥==========//
    StrCondition* _conTimeImprison;
    Selector* _selTimeImprison;
    // 나머지는 취침이랑 동일

    //==========운동==========//
    StrCondition* _conTimeGround;

    //==========휴식==========//
    StrCondition* _conTimeRest;

    

    //==========대기==========//
    Selector* _selWait;
    VoidCondition* _conHaveGoalRND;
    AssignTarget* _assRNDTarget;
    MoveToTarget* _MTT;
public:
	PrisonerAI();
	~PrisonerAI();

    HRESULT init(Character* character);
    void Update();

    // 공용 사용 함수
    bool CheckTimeSchedule(string schedule);        // 시간표 확인
    bool CheckHaveRegion(string region);            // 맵에 지역이 있는지 확인
    bool CheckIsInRegion(string region);            // 캐릭터가 지역에 있는지 확인
    bool CheckHaveGoalRND();                        // 캐릭터가 움직일 목표가 있는지 확인
    bool CheckHaveObject(string objectName);        // 지역에 오브젝트가 있는지 탐색
    bool CheckObjectHaveEmpty(string objectName);   // 지역에 있는 오브젝트에 빈자리가 있는지 탐색
    bool CheckHaveTool(string toolName);            // 손에 해당 도구가 있는지 판단

    bool CheckHaveGoalToJail();                     // 해당 지역으로 골이 찍혔는지
    bool CheckHaveGoalToRestaurant();               // 해당 지역으로 골이 찍혔는지
    bool CheckHaveGoalToShowerRoom();
    // 식당에서
    bool CheckHaveGoalToDBTable();                  // 빈 배식대를 목표로
    bool CheckHaveGoalToTable();                    // 빈 식탁을 목표로
    bool CheckUseTable();                           // 식탁 사용중인지 체크
    bool CheckUseDBTable();                         // 배식대 사용중인지 체크
    bool CheckArriveDBTable();
    bool CheckArriveTable();
};

