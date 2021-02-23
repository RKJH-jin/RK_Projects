#include "stdafx.h"
#include "DataManager.h"

#include "TileTerrain.h"
#include "TileWall.h"
#include "TileObject.h"
#include "TileArea.h"

#include "Staff.h"
#include "People.h"
#include "Prisoner.h"

void DataManager::init()
{
	_info.money = 1000000;

	_terrainImg = IMAGEMANAGER->FindImage("terrain");

	//지형 추가
	for (int i = 0; i < (int)TILETERRAIN::END; i++)
	{
		TileAttribute* obj = new TileTerrain((TILETERRAIN)i);
		_mTileObject.insert(make_pair(obj->GetKey(), obj));
	}

	//벽 추가
	for (int i = 0; i < (int)TILEWALL::END; i++)
	{
		TileAttribute* obj = new TileWall((TILEWALL)i);
		_mTileObject.insert(make_pair(obj->GetKey(), obj));
	}

	//오브젝트 추가
	for (int i = 0; i < (int)TILEOBJECT::END; i++)
	{
		TileAttribute* obj = new TileObject((TILEOBJECT)i);
		_mTileObject.insert(make_pair(obj->GetKey(), obj));
	}

	//지역 추가
	for (int i = 0; i < (int)TILEAREA::END; i++)
	{
		TileAttribute* obj = new TileArea((TILEAREA)i);
		_mTileObject.insert(make_pair(obj->GetKey(), obj));
	}

	//직원 추가
	for (int i = 0; i < (int)STAFFROLE::END; i++)
	{
		Character* obj = new Staff((STAFFROLE)i);
		_mCharacter.insert(make_pair(obj->GetName(), obj));
	}
	//죄수 추가
	Character* obj = new Prisoner();
	_mCharacter.insert(make_pair(obj->GetName(), obj));

	//하늘
    _info.skyAlpha = 0.0f;

	//소리
	_info.soundVolume = 1.0f;
	_info.sfxVolume = 1.0f;
	_info.bgmVolume = 1.0f;
}

void DataManager::update()
{
}

TileAttribute * DataManager::FindTileObject(string key)
{
	//오브젝트 찾기
	miTileAttribute iter = _mTileObject.find(key);
	if (iter != _mTileObject.end()) return iter->second;

	return nullptr;
}

TileAttribute * DataManager::CreateTileObject(string key)
{
	TileAttribute* tileObj = FindTileObject(key);

	switch (tileObj->GetInfo()._attribute)
	{
		case TILEATTRIBUTE::TERRAIN:
		{tileObj = new TileTerrain((TILETERRAIN)tileObj->GetInfo()._type); }
		break;
		case TILEATTRIBUTE::WALL:
		{tileObj = new TileWall((TILEWALL)tileObj->GetInfo()._type); }
		break;
		case TILEATTRIBUTE::OBJECT:
		{tileObj = new TileObject((TILEOBJECT)tileObj->GetInfo()._type); }
		break;
		case TILEATTRIBUTE::AREA:
		{tileObj = new TileArea((TILEAREA)tileObj->GetInfo()._type); }
		break;
	}
	return tileObj;

	return nullptr;
}

string DataManager::GetTimeSchedule()
{
    string result;
    switch (_info.schedule)
    {
    case TIMESCHEDULE::SLEEP:
        result = "SLEEP";
        break;
    case TIMESCHEDULE::MEAL:
        result = "MEAL";
        break;
    case TIMESCHEDULE::WASH:
        result = "WASH";
        break;
    case TIMESCHEDULE::GROUND:
        result = "GROUND";
        break;
    case TIMESCHEDULE::REST:
        result = "REST";
        break;
    case TIMESCHEDULE::IMPRISON:
        result = "IMPRISON";
        break;
    default:
        break;
    }
    return result;
}

Character * DataManager::FindCharacter(string key)
{
	//오브젝트 찾기
	miCharacter iter = _mCharacter.find(key);
	if (iter != _mCharacter.end()) return iter->second;
	return nullptr;
}

Character * DataManager::CreateCharacter(string key)
{
	Character* charObj = FindCharacter(key);

	switch (charObj->GetInfo().type)
	{
	case CHARACTERTYPE::PEOPLE:
		charObj = new People((PEOPLEROLE)charObj->GetInfo().role);
		charObj->SetPeopleRandomName();
		break;
	case CHARACTERTYPE::PRISONER:
		charObj = new Prisoner();
		charObj->SetPrisonerRandomName();
		break;
	case CHARACTERTYPE::STAFF:
		charObj = new Staff((STAFFROLE)charObj->GetInfo().role);
		charObj->SetPeopleRandomName();
		break;
	}
	return charObj;
	
	return nullptr;
}

void DataManager::UpdateTime()
{
	_info.time.milliSeconds += TIMEMANAGER->getElapsedTime() * _info.gameSpeed * 160;

	_info.time.second = (int)_info.time.milliSeconds;
	if (_info.time.second >= 60)
	{
		_info.time.milliSeconds -= _info.time.second;
		_info.time.minute += 1;
		_info.time.second = 0;
		//_skyAlpha max값 = 0.7f
		if (19 <= _info.time.hour && _info.time.hour <= 24)
		{
			_info.skyAlpha += (0.7f / 5) / 60;
		}
		else if (5 <= _info.time.hour && _info.time.hour < 7)
		{
			_info.skyAlpha -= (0.7f / 2) / 60;
			if (_info.skyAlpha < 0) _info.skyAlpha = 0;
		}
	}

	if (_info.time.minute >= 60)
	{
		_info.time.hour += 1;
		_info.time.minute = 0;
	}

	if (_info.time.hour >= 24)
	{
		_info.time.day += 1;
		_info.time.hour = 0;
	}

    if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD1))
    {
        DATAMANAGER->GetInfo().schedule = TIMESCHEDULE::SLEEP;
    }
    if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD2))
    {
        DATAMANAGER->GetInfo().schedule = TIMESCHEDULE::MEAL;
    }
    if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD3))
    {
        DATAMANAGER->GetInfo().schedule = TIMESCHEDULE::WASH;
    }
    if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD4))
    {
        DATAMANAGER->GetInfo().schedule = TIMESCHEDULE::GROUND;
    }
    if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD5))
    {
        DATAMANAGER->GetInfo().schedule = TIMESCHEDULE::REST;
    }
    if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD6))
    {
        DATAMANAGER->GetInfo().schedule = TIMESCHEDULE::IMPRISON;
    }
	//if ((22 <= _info.time.hour && _info.time.hour <= 24) ||
	//	(0 <= _info.time.hour && _info.time.hour <= 7))
	//{
	//	_info.schedule = TIMESCHEDULE::SLEEP;
	//}
	//else if (7 <= _info.time.hour && _info.time.hour <= 8)
	//{
	//	_info.schedule = TIMESCHEDULE::MEAL;
	//}
	//else if (8 <= _info.time.hour && _info.time.hour <= 9)
	//{
	//	_info.schedule = TIMESCHEDULE::WASH;
	//}
	//else if (9 <= _info.time.hour && _info.time.hour <= 12)
	//{
	//	_info.schedule = TIMESCHEDULE::IMPRISON;
	//}
	//else if (12 <= _info.time.hour && _info.time.hour <= 13)
	//{
	//	_info.schedule = TIMESCHEDULE::MEAL;
	//}
	//else if (13 <= _info.time.hour && _info.time.hour <= 17)
	//{
	//	_info.schedule = TIMESCHEDULE::GROUND;
	//}
	//else if (17 <= _info.time.hour && _info.time.hour <= 18)
	//{
	//	_info.schedule = TIMESCHEDULE::MEAL;
	//}
	//else if (18 <= _info.time.hour && _info.time.hour <= 22)
	//{
	//	_info.schedule = TIMESCHEDULE::REST;
	//}
}

void DataManager::Save()
{
    ofstream output("SaveData_Data.txt");

    boost::archive::text_oarchive oa(output);
    oa << _info;

}

void DataManager::Load()
{
    ifstream input("SaveData_Data.txt");
    boost::archive::text_iarchive ia(input);

    ia >> _info;

}