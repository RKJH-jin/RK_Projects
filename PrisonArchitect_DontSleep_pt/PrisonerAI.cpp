#include "stdafx.h"
#include "PrisonerAI.h"
#include "MapToolScene.h"
#include "Character.h"
#include "AssignTarget.h"
#include "AssignRNDGoalOnce.h"
#include "MoveToTarget.h"
#include "TileArea.h"
#include "PrisonerEat.h"
#include "TrayDirty.h"
#include "CreateTray.h"


PrisonerAI::PrisonerAI()
{
    _root = new Selector();
    // 대기
    _selWait = new Selector();
    _conHaveGoalRND = new VoidCondition(bind(&PrisonerAI::CheckHaveGoalRND, this));
    _MTT = new MoveToTarget();
    _assRNDTarget = new AssignTarget();
    ///////////////////////////////////////

    // 취침
    _conTimeSleep = new StrCondition(bind(&PrisonerAI::CheckTimeSchedule, this, placeholders::_1), "SLEEP");
    _selTimeSleep = new Selector();
    _conHaveJail = new StrCondition(bind(&PrisonerAI::CheckHaveRegion, this, placeholders::_1), "감옥");
    _selHaveJail = new Selector();
    _conInJail = new StrCondition(bind(&PrisonerAI::CheckIsInRegion, this, placeholders::_1), "감옥");
    _conHaveGoalToJail = new VoidCondition(bind(&PrisonerAI::CheckHaveGoalToJail, this));
    _assJail = new AssignTarget();

    // 식사
    _conTimeMeal = new StrCondition(bind(&PrisonerAI::CheckTimeSchedule, this, placeholders::_1), "MEAL");
    _selTimeMeal = new Selector();
    _conHaveRestaurant = new StrCondition(bind(&PrisonerAI::CheckHaveRegion, this, placeholders::_1), "식당");
    _selHaveRestaurant = new Selector();
    _conInRestaurant = new StrCondition(bind(&PrisonerAI::CheckIsInRegion, this, placeholders::_1), "식당");
    _conHaveGoalToRestaurant = new VoidCondition(bind(&PrisonerAI::CheckHaveGoalToRestaurant, this));
    _assRestaurant = new AssignTarget();

    // 식당에서
    _selInRestaurant = new Selector();
    _conHaveTable = new StrCondition(bind(&PrisonerAI::CheckHaveObject, this, placeholders::_1), "식탁");

    // - 식탁이 있는경우
    _selHaveTable = new Selector();
    _conHaveEmptyTable = new StrCondition(bind(&PrisonerAI::CheckObjectHaveEmpty, this, placeholders::_1), "식탁");
    _seqUseTable = new Sequence();
    // - 빈 식탁이 있는 경우
    _selHaveEmptyTable = new Selector();
    _conHaveTray = new StrCondition(bind(&PrisonerAI::CheckHaveTool, this, placeholders::_1), "식판");

    // - 식판이 있는 경우
    _selHaveTray = new Selector();
    _conHaveGoalToTable = new VoidCondition(bind(&PrisonerAI::CheckHaveGoalToTable, this));
    _assGoalToTable = new AssignTarget();
    _conUseTable = new VoidCondition(bind(&PrisonerAI::CheckUseTable, this));
    _conArriveTable = new VoidCondition(bind(&PrisonerAI::CheckArriveTable, this));
    _prisonerEat = new PrisonerEat();
    _trayDirty = new TrayDirty();
    
    // - 식판이 없는 경우
    _selNonHaveTray = new Selector();
    _conHaveDBTable = new StrCondition(bind(&PrisonerAI::CheckHaveObject, this, placeholders::_1), "배식대");

    // - 배식대가 있는 경우
    _selHaveDBTable = new Selector();
    _conHaveEmptyDBTable = new StrCondition(bind(&PrisonerAI::CheckObjectHaveEmpty, this, placeholders::_1), "배식대");

    // - 배식대에 빈자리가 있는 경우
    _selHaveEmptyDBTable = new Selector();
    _conUseDBTable = new VoidCondition(bind(&PrisonerAI::CheckUseDBTable, this));
    _conHaveGoalToDBTable = new VoidCondition(bind(&PrisonerAI::CheckHaveGoalToDBTable, this));
    _assGoalToDBTable = new AssignTarget();
    _createTray = new CreateTray();
    _conArriveDBTable = new VoidCondition(bind(&PrisonerAI::CheckArriveDBTable, this));
    // 샤워
    _conTimeWash = new StrCondition(bind(&PrisonerAI::CheckTimeSchedule, this, placeholders::_1), "WASH");
    _selTimeWash = new Selector();
    _conHaveShowerRoom = new StrCondition(bind(&PrisonerAI::CheckHaveRegion, this, placeholders::_1), "샤워실");
    _selHaveShowerRoom = new Selector();
    _conInShowerRoom = new StrCondition(bind(&PrisonerAI::CheckIsInRegion, this, placeholders::_1), "샤워실");
    _conHaveGoalToShowerRoom = new VoidCondition(bind(&PrisonerAI::CheckHaveGoalToShowerRoom, this));
    _assShowerRoom = new AssignTarget();

    // 운동
    _conTimeGround = new StrCondition(bind(&PrisonerAI::CheckTimeSchedule, this, placeholders::_1), "GROUND");
    
    // 운동
    _conTimeRest = new StrCondition(bind(&PrisonerAI::CheckTimeSchedule, this, placeholders::_1), "REST");

    // 투옥
    _conTimeImprison = new StrCondition(bind(&PrisonerAI::CheckTimeSchedule, this, placeholders::_1), "IMPRISON");
    _selTimeImprison = new Selector();

}

PrisonerAI::~PrisonerAI()
{
}

HRESULT PrisonerAI::init(Character* character)
{
    _character = character;

    // 사전 초기화 가능한 것들
    _MTT->init(_character);
    _prisonerEat->init(_character);
    _trayDirty->init(_character);
    _createTray->init(_character);

    // 대기
    _selWait->AddChild(_conHaveGoalRND);
    _conHaveGoalRND->AddChild(_assRNDTarget);
    _selWait->AddChild(_MTT);
    //////////


    //============================취침============================//
    _root->AddChild(_conTimeSleep);
    _conTimeSleep->AddChild(_selTimeSleep);
    _selTimeSleep->AddChild(_conHaveJail);
    _selTimeSleep->AddChild(_selWait);
    _conHaveJail->AddChild(_selHaveJail);
    _selHaveJail->AddChild(_conInJail);
    _conInJail->AddChild(_selWait);
    _selHaveJail->AddChild(_conHaveGoalToJail);
    _conHaveGoalToJail->AddChild(_assJail);
    _selHaveJail->AddChild(_MTT);
    //============================================================//

    //============================식사============================//
    _root->AddChild(_conTimeMeal);
    _conTimeMeal->AddChild(_selTimeMeal);
    _selTimeMeal->AddChild(_conHaveRestaurant);
    _selTimeMeal->AddChild(_selWait);
    _conHaveRestaurant->AddChild(_selHaveRestaurant);
    _selHaveRestaurant->AddChild(_conInRestaurant);
    _conInRestaurant->AddChild(_selInRestaurant);
    _selHaveRestaurant->AddChild(_conHaveGoalToRestaurant);
    _conHaveGoalToRestaurant->AddChild(_assRestaurant);
    _selHaveRestaurant->AddChild(_MTT);

    // 식당에서
    _selInRestaurant->AddChild(_conHaveTable);
    _selInRestaurant->AddChild(_selWait);
    _conHaveTable->AddChild(_selHaveTable);

    // -식탁이 있니?
    _selHaveTable->AddChild(_conUseTable);
    _conUseTable->AddChild(_seqUseTable);
    _seqUseTable->AddChild(_trayDirty);
    _seqUseTable->AddChild(_prisonerEat);

    _selHaveTable->AddChild(_conHaveEmptyTable);
    _selHaveTable->AddChild(_selWait);
    _conHaveEmptyTable->AddChild(_selHaveEmptyTable);
    _selHaveEmptyTable->AddChild(_conHaveTray);
    _conHaveTray->AddChild(_selNonHaveTray);
    _selHaveEmptyTable->AddChild(_selHaveTray);
    
    // -식판이 있는 경우
    _selHaveTray->AddChild(_conHaveGoalToTable);
    _conHaveGoalToTable->AddChild(_assGoalToTable);
    _selHaveTray->AddChild(_conArriveTable);
    _conArriveTable->AddChild(_MTT);
    
    // -식판이 없는 경우
    _selNonHaveTray->AddChild(_conHaveDBTable);
    _selNonHaveTray->AddChild(_selWait);
    _conHaveDBTable->AddChild(_selHaveDBTable);

    // -배식대가 있는 경우
    _selHaveDBTable->AddChild(_conUseDBTable);
    _conUseDBTable->AddChild(_createTray);
    _selHaveDBTable->AddChild(_conHaveEmptyDBTable);
    _conHaveEmptyDBTable->AddChild(_selHaveEmptyDBTable);
    _selHaveDBTable->AddChild(_selWait);

    // -배식대에 빈 자리가 있는 경우
    _selHaveEmptyDBTable->AddChild(_conHaveGoalToDBTable);
    _conHaveGoalToDBTable->AddChild(_assGoalToDBTable);
    _selHaveEmptyDBTable->AddChild(_conArriveDBTable);
    _conArriveDBTable->AddChild(_MTT);

    //============================================================//

    //============================샤워============================//
    _root->AddChild(_conTimeWash);
    _conTimeWash->AddChild(_selTimeWash);
    _selTimeWash->AddChild(_conHaveShowerRoom);
    _selTimeWash->AddChild(_selWait);
    _conHaveShowerRoom->AddChild(_selHaveShowerRoom);
    _selHaveShowerRoom->AddChild(_conInShowerRoom);
    _conInShowerRoom->AddChild(_selWait);
    _selHaveShowerRoom->AddChild(_conHaveGoalToShowerRoom);
    _conHaveGoalToShowerRoom->AddChild(_assShowerRoom);
    _selHaveShowerRoom->AddChild(_MTT);
    //============================================================//
    
    //============================운동============================//
    _root->AddChild(_conTimeGround);
    _conTimeGround->AddChild(_selWait);
    //============================================================//

    //============================휴식============================//
    _root->AddChild(_conTimeRest);
    _conTimeRest->AddChild(_selWait);
    //============================================================//

    //============================취침============================//
    _root->AddChild(_conTimeImprison);
    _conTimeImprison->AddChild(_selTimeImprison);
    _selTimeImprison->AddChild(_conHaveJail);
    _selTimeImprison->AddChild(_selWait);
    //============================================================//


    return S_OK;
}

void PrisonerAI::Update()
{
    _root->invoke();   
}

bool PrisonerAI::CheckTimeSchedule(string schedule)
{
    if (DATAMANAGER->GetTimeSchedule() == schedule) return true;
    return false;
}

bool PrisonerAI::CheckHaveRegion(string region)
{
    if (DATAMANAGER->GetMapToolScene()->GetMapM()->GetTileMap()->FindTileObject(region))  return true;
    return false;
}

bool PrisonerAI::CheckIsInRegion(string region)
{
    if ((*_character).GetIsInArea(region))  return true;
    return false;
}

bool PrisonerAI::CheckHaveGoalRND()
{
    if (_character->GetInfo().goalState == GOALSTATE::NONE || _character->GetInfo().goalState == GOALSTATE::GOALREACH)
    {
        //내가 있는 지역을 가져와야한다.
        Vector2 temp = DATAMANAGER->GetMapToolScene()->GetMapM()->GetTileMap()->GetCount(); // 타일 전체 갯수
        Vector2 chaIndex = _character->GetTransform()->GetIndex();  // 내 위치 인덱스
        Vector2 RNDtemp; //랜덤인덱스 받을 벡터
        TileAttribute* tempTile = DATAMANAGER->GetMapToolScene()->GetMapM()->GetTileMap()->GetvTile()[chaIndex.y * temp.x + chaIndex.x]->_area;
        if (tempTile != nullptr && (DATAMANAGER->GetTimeSchedule() != "GROUND" && DATAMANAGER->GetTimeSchedule() != "REST")) // 내가 현재 어떠한 지역에 있으면
        {
            RNDtemp = tempTile->GetRandomIndex();
        }
        else
        {
            RNDtemp = Vector2(RND->getInt(temp.x), RND->getInt(temp.y));
            while (true)
            {
                if (DATAMANAGER->GetMapToolScene()->GetMapM()->GetTileMap()->GetvTile()[RNDtemp.y * temp.x + RNDtemp.x]->GetTileEmpty()) break;
                RNDtemp = Vector2(RND->getInt(temp.x), RND->getInt(temp.y));
            }
        }
        _assRNDTarget->init(_character, RNDtemp);
        _character->GetInfo().goalState = GOALSTATE::GOALSET;
        return true;
    }
    return false;
}

bool PrisonerAI::CheckHaveObject(string objectName)
{
    Vector2 temp = DATAMANAGER->GetMapToolScene()->GetMapM()->GetTileMap()->GetCount(); // 타일 전체 갯수
    Vector2 chaIndex = _character->GetTransform()->GetIndex();  // 내 위치 인덱스
    TileAttribute* tempArea = DATAMANAGER->GetMapToolScene()->GetMapM()->GetTileMap()->GetvTile()[chaIndex.y * temp.x + chaIndex.x]->_area; // 내 위치
    if (tempArea == nullptr) return false;
    if (dynamic_cast<TileArea*>(tempArea)->CheckHaveObject(objectName)) return true;
    return false;
}

bool PrisonerAI::CheckObjectHaveEmpty(string objectName)
{
    Vector2 temp = DATAMANAGER->GetMapToolScene()->GetMapM()->GetTileMap()->GetCount(); // 타일 전체 갯수
    Vector2 chaIndex = _character->GetTransform()->GetIndex();  // 내 위치 인덱스
    TileAttribute* tempArea = DATAMANAGER->GetMapToolScene()->GetMapM()->GetTileMap()->GetvTile()[chaIndex.y * temp.x + chaIndex.x]->_area; // 내 위치
    vector<TileObject*> tempVObj = dynamic_cast<TileArea*>(tempArea)->GetHaveObject(objectName);
    if (!tempVObj.empty())
    {
        for (int i = 0; i < tempVObj.size(); ++i)
        {
            if (tempVObj[i]->CheckVoidIndex())  return true;
        }
    }

    return false;
}

bool PrisonerAI::CheckHaveTool(string toolName)
{
    if (_character->GetInfo().toolObject == nullptr)  return true;
    if (_character->GetInfo().toolObject->GetKey() == toolName)
    {
        return false;
    }
    return true;
}

bool PrisonerAI::CheckHaveGoalToJail()
{
    if (_character->GetInfo().goalState == GOALSTATE::NONE || _character->GetInfo().goalState == GOALSTATE::GOALREACH)
    {
        _assJail->init(_character, DATAMANAGER->GetMapToolScene()->GetMapM()->GetTileMap()->FindTileObject("감옥")->GetCenterIndex());
        _character->GetInfo().goalState = GOALSTATE::GOALSET;
        
        return true;
    }
    return false;
}

bool PrisonerAI::CheckHaveGoalToRestaurant()
{
    if (_character->GetInfo().goalState == GOALSTATE::NONE || _character->GetInfo().goalState == GOALSTATE::GOALREACH)
    {
        _assRestaurant->init(_character, DATAMANAGER->GetMapToolScene()->GetMapM()->GetTileMap()->FindTileObject("식당")->GetCenterIndex());
        _character->GetInfo().goalState = GOALSTATE::GOALSET;
        return true;
    }
    return false;
}

bool PrisonerAI::CheckHaveGoalToShowerRoom()
{
    if (_character->GetInfo().goalState == GOALSTATE::NONE || _character->GetInfo().goalState == GOALSTATE::GOALREACH)
    {
        _assShowerRoom->init(_character, DATAMANAGER->GetMapToolScene()->GetMapM()->GetTileMap()->FindTileObject("샤워실")->GetCenterIndex());
        _character->GetInfo().goalState = GOALSTATE::GOALSET;
        return true;
    }
    return false;
}


bool PrisonerAI::CheckHaveGoalToDBTable()
{
    Vector2 temp = DATAMANAGER->GetMapToolScene()->GetMapM()->GetTileMap()->GetCount(); // 타일 전체 갯수
    Vector2 chaIndex = _character->GetTransform()->GetIndex();  // 내 위치 인덱스
    TileAttribute* tempArea = DATAMANAGER->GetMapToolScene()->GetMapM()->GetTileMap()->GetvTile()[chaIndex.y * temp.x + chaIndex.x]->_area; // 내 위치
    vector<TileObject*> tempVObj = dynamic_cast<TileArea*>(tempArea)->GetHaveObject("배식대");

    vector<Tile*> tempV = DATAMANAGER->GetMapToolScene()->GetMapM()->GetTileMap()->GetvTile();
    TileAttribute* tempTA = tempV[chaIndex.y * temp.x + chaIndex.x]->_tileObj;
    if (tempTA != nullptr && tempTA->GetKey() == "배식대")
    {
        _character->GetInfo().btState = BTSTATE::SERVING;
        return false;
    }

    if (!tempVObj.empty() && _character->GetInfo().goalState != GOALSTATE::GOALSET)
    {
        for (int i = 0; i < tempVObj.size(); ++i)
        {
            if (tempVObj[i]->CheckVoidIndex())
            {
                _assGoalToDBTable->init(_character, *tempVObj[i]->GetVoidIndexfromVector());
                _character->GetInfo().goalState = GOALSTATE::GOALSET;
                return true;
            }
        }
    }
    return false;
}

bool PrisonerAI::CheckHaveGoalToTable()
{
    Vector2 temp = DATAMANAGER->GetMapToolScene()->GetMapM()->GetTileMap()->GetCount(); // 타일 전체 갯수
    Vector2 chaIndex = _character->GetTransform()->GetIndex();  // 내 위치 인덱스
    TileAttribute* tempArea = DATAMANAGER->GetMapToolScene()->GetMapM()->GetTileMap()->GetvTile()[chaIndex.y * temp.x + chaIndex.x]->_area; // 내 위치
    vector<TileObject*> tempVObj = dynamic_cast<TileArea*>(tempArea)->GetHaveObject("식탁");

    vector<Tile*> tempV = DATAMANAGER->GetMapToolScene()->GetMapM()->GetTileMap()->GetvTile();
    TileAttribute* tempTA = tempV[chaIndex.y * temp.x + chaIndex.x]->_tileObj;
    if (tempTA != nullptr && tempTA->GetKey() == "식탁")
    {
        _character->GetInfo().btState = BTSTATE::EAT;
        return false;
    }

    if (!tempVObj.empty() && _character->GetInfo().goalState != GOALSTATE::GOALSET)
    {
        for (int i = 0; i < tempVObj.size(); ++i)
        {
            if (tempVObj[i]->CheckVoidIndex())
            {
                _assGoalToTable->init(_character, *tempVObj[i]->GetVoidIndexfromVector());
                _character->GetInfo().goalState = GOALSTATE::GOALSET;
                return true;
            }
        }
    }
    return false;
}

bool PrisonerAI::CheckUseTable()
{
    if (_character->GetInfo().btState == BTSTATE::EAT)
    {
        return true;
    }
    return false;
}

bool PrisonerAI::CheckUseDBTable()
{
    if (_character->GetInfo().btState == BTSTATE::SERVING)
    {
        return true;
    }
    return false;
}


bool PrisonerAI::CheckArriveDBTable()
{
    Vector2 temp = _character->GetTransform()->GetIndex();
    Vector2 tempC = DATAMANAGER->GetMapToolScene()->GetMapM()->GetTileMap()->GetCount(); // 타일 전체 갯수
    vector<Tile*> tempV = DATAMANAGER->GetMapToolScene()->GetMapM()->GetTileMap()->GetvTile();
    TileAttribute* tempTA = tempV[temp.y * tempC.x + temp.x]->_tileObj;
    if (tempTA != nullptr && tempTA->GetKey() == "배식대")
    {
        _character->GetInfo().btState = BTSTATE::SERVING;
        return false;
    }
    return true;
}

bool PrisonerAI::CheckArriveTable()
{
    Vector2 temp = _character->GetTransform()->GetIndex();
    Vector2 tempC = DATAMANAGER->GetMapToolScene()->GetMapM()->GetTileMap()->GetCount(); // 타일 전체 갯수
    vector<Tile*> tempV = DATAMANAGER->GetMapToolScene()->GetMapM()->GetTileMap()->GetvTile();
    TileAttribute* tempTA = tempV[temp.y * tempC.x + temp.x]->_tileObj;
    if (tempTA != nullptr && tempTA->GetKey() == "식탁")
    {
        _character->GetInfo().btState = BTSTATE::EAT;
        return false;
    }
    return true;
}


