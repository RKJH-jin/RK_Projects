#include "stdafx.h"
#include "DataManager.h"
#include "Player.h"
#include "StageManager.h"
#include "Stage.h"

DataManager::DataManager()
{
}

DataManager::~DataManager()
{
}

HRESULT DataManager::init()
{
	return S_OK;
}

void DataManager::release()
{
}

void DataManager::addData()
{
	// 데이터 추가
	tagSaveLoadData saveLoadData;
	//==========[Player]==========
	saveLoadData.PosX = to_string((int)_data.playerPos.x);
	saveLoadData.PosY = to_string(0);
	saveLoadData.PosZ = to_string((int)_data.playerPos.z);
	saveLoadData.HP = to_string(_data.hp);
	saveLoadData.MaxHP = to_string(_data.maxHP);
	saveLoadData.Force = to_string(_data.force);
	saveLoadData.Coin = to_string(_data.coin);
	saveLoadData.LV = to_string(_data.LV);
	saveLoadData.EXP = to_string(_data.exp);

	//==========[Stage]==========
	saveLoadData.CurrentStage = to_string(_data.curStage);
	if (_data.easyLockEventEnd == false) saveLoadData.easyLockEvent = to_string(0);
	else saveLoadData.easyLockEvent = to_string(1);
	if (_data.normalLockEventEnd == false) saveLoadData.normalLockEvent = to_string(0);
	else saveLoadData.normalLockEvent = to_string(1);
	if (_data.hardLockEventEnd == false) saveLoadData.hardLockEvent = to_string(0);
	else saveLoadData.hardLockEvent = to_string(1);


	arrSaveLoadData arrData;
	arrData.push_back(saveLoadData);

	_vDatas.push_back(arrData);

}

void DataManager::saveIniData(int num)
{
	char str[256];
	char dir[256];

	ZeroMemory(dir, sizeof(dir));
	sprintf_s(dir, "\\%s%d.ini", "Save_Data", num);

	GetCurrentDirectory(256, str);
	strncat_s(str, 256, dir, 254); // 파일 위치


	for (int i = 0; i < _vDatas.size(); i++)
	{
		arrSaveLoadData arrData = _vDatas[i];

		WritePrivateProfileString("Player", "PosX", arrData[0].PosX.c_str(), str);
		WritePrivateProfileString("Player", "PosY", arrData[0].PosY.c_str(), str);
		WritePrivateProfileString("Player", "PosZ", arrData[0].PosZ.c_str(), str);
		WritePrivateProfileString("Player", "HP", arrData[0].HP.c_str(), str);
		WritePrivateProfileString("Player", "MaxHP", arrData[0].MaxHP.c_str(), str);
		WritePrivateProfileString("Player", "Force", arrData[0].Force.c_str(), str);
		WritePrivateProfileString("Player", "Coin", arrData[0].Coin.c_str(), str);
		WritePrivateProfileString("Player", "LV", arrData[0].LV.c_str(), str);
		WritePrivateProfileString("Player", "EXP", arrData[0].EXP.c_str(), str);

		WritePrivateProfileString("Stage", "CurrentStage", arrData[0].CurrentStage.c_str(), str);
		WritePrivateProfileString("Stage", "EasyLockEvent", arrData[0].easyLockEvent.c_str(), str);
		WritePrivateProfileString("Stage", "NormalLockEvent", arrData[0].normalLockEvent.c_str(), str);
		WritePrivateProfileString("Stage", "HardLockEvent", arrData[0].hardLockEvent.c_str(), str);
		arrData.clear();
	}

	_vDatas.clear();
}

bool DataManager::loadIniData(int num)
{
	char str[256];
	char dir[256];

	ZeroMemory(dir, sizeof(dir));
	sprintf_s(dir, "\\%s%d.ini", "Save_Data", num);

	GetCurrentDirectory(256, str);
	strncat_s(str, 256, dir, 254);

	if (PathFileExists(str))
	{
		_data.playerPos.x = GetPrivateProfileInt("Player", "PosX", 0, str);
		_data.playerPos.y = GetPrivateProfileInt("Player", "PosY", 0, str);
		_data.playerPos.z = GetPrivateProfileInt("Player", "PosZ", 0, str);
		_data.hp = GetPrivateProfileInt("Player", "HP", 0, str);
		_data.maxHP = GetPrivateProfileInt("Player", "MaxHP", 0, str);
		_data.force = GetPrivateProfileInt("Player", "Force", 0, str);
		_data.coin = GetPrivateProfileInt("Player", "Coin", 0, str);
		_data.LV = GetPrivateProfileInt("Player", "LV", 0, str);
		_data.exp = GetPrivateProfileInt("Player", "EXP", 0, str);
		_data.curStage = GetPrivateProfileInt("Stage", "CurrentStage", -1, str);
		_data.easyLockEventEnd = GetPrivateProfileInt("Stage", "EasyLockEvent", 0, str);
		_data.normalLockEventEnd = GetPrivateProfileInt("Stage", "NormalLockEvent", 0, str);
		_data.hardLockEventEnd = GetPrivateProfileInt("Stage", "HardLockEvent", 0, str);
		return true;
	}
	else
	{
		_data.curStage = -1;
		return false;
	}
}

void DataManager::saveStageData()
{
	//플레이어 데이터
	_data.playerPos = _player->getObj().pos;
	_data.hp = _player->getInfo().hp;
	_data.maxHP = _player->getInfo().maxHP;
	_data.force = _player->getInfo().force;
	_data.coin = _player->getInfo().coin;
	_data.LV = _player->getInfo().LV;
	_data.exp = _player->getInfo().exp;

	//스테이지 데이터
	switch (_stageM->getCurStage())
	{
	case STAGETYPE::EASY:
		_data.curStage = 0;
		_data.easyLockEventEnd = _stageM->getStage()->getLockEventEnd();
		_data.normalLockEventEnd = 0;
		_data.hardLockEventEnd = 0;
		break;
	case STAGETYPE::NORMAL:
		_data.curStage = 1;
		_data.easyLockEventEnd = 1;
		_data.normalLockEventEnd = _stageM->getStage()->getLockEventEnd();
		_data.hardLockEventEnd = 0;
		break;
	case STAGETYPE::HARD:
		_data.curStage = 2;
		_data.easyLockEventEnd = 1;
		_data.normalLockEventEnd = 1;
		_data.hardLockEventEnd = _stageM->getStage()->getLockEventEnd();
		break;
	case STAGETYPE::BOSS:
		_data.curStage = 3;
		_data.easyLockEventEnd = 1;
		_data.normalLockEventEnd = 1;
		_data.hardLockEventEnd = 1;
		break;
	default:
		break;
	}

}


bool DataManager::loadStageData()
{

	if (_data.curStage == -1) return false;

	//스테이지 데이터
	switch (_data.curStage)
	{
	case 0:
		_stageM->setStage(STAGETYPE::EASY);
		_stageM->getStage()->setLockEventEnd(_data.easyLockEventEnd);
		break;
	case 1:
		_stageM->setStage(STAGETYPE::NORMAL);
		_stageM->getStage()->setLockEventEnd(_data.normalLockEventEnd);
		break;
	case 2:
		_stageM->setStage(STAGETYPE::HARD);
		_stageM->getStage()->setLockEventEnd(_data.hardLockEventEnd);
		break;
	case 3:
		_stageM->setStage(STAGETYPE::BOSS);
		break;
	default:
		break;
	}


	//플레이어 데이터
	_player->getPObj()->pos = _data.playerPos;
	_player->getInfo().hp = _data.hp;
	_player->getInfo().maxHP = _data.maxHP;
	_player->getInfo().force = _data.force;
	_player->getInfo().coin = _data.coin;
	_player->getInfo().LV = _data.LV;
	_player->getInfo().exp = _data.exp;
	_player->setState(PL_STATE::IDLE);

	return true;
}

int DataManager::loadIniStageData(int num)
{
	char str[256];
	char dir[256];

	ZeroMemory(dir, sizeof(dir));
	sprintf_s(dir, "\\%s%d.ini", "Save_Data", num);

	GetCurrentDirectory(256, str);
	strncat_s(str, 256, dir, 254);

	if (PathFileExists(str))
	{
		return GetPrivateProfileInt("Stage", "CurrentStage", 0, str);
	}
	else -1;
}




void DataManager::checkData()
{
	cout << "플레이어 위치X: " << _data.playerPos.x << endl;
	cout << "플레이어 위치Y: " << _data.playerPos.y << endl;
	cout << "플레이어 위치Z: " << _data.playerPos.z << endl;
	cout << "플레이어 hp: " << _data.hp << endl;
	cout << "플레이어 maxHP: " << _data.maxHP << endl;
	cout << "플레이어 coin: " << _data.coin << endl;
	cout << "플레이어 force: " << _data.force << endl;
	cout << "플레이어 LV: " << _data.LV << endl;
	cout << "플레이어 exp: " << _data.exp << endl;

	cout << "플레이어 현재 스테이지: " << _data.curStage << endl;
	cout << "플레이어 이지지역락 이벤트: " << _data.easyLockEventEnd << endl;
	cout << "플레이어 노말지역락 이벤트: " << _data.normalLockEventEnd << endl;
	cout << "플레이어 하드지역락 이벤트: " << _data.hardLockEventEnd << endl;
}

void DataManager::setPlayerHP(int num)
{
	_data.hp = num;
}

void DataManager::plusPlayerHP(int num)
{
	_data.hp += num;
	if (_data.hp > _data.maxHP) _data.hp = _data.maxHP;
}

bool DataManager::minusPlayerCoin(int numf)
{
	if (_data.coin < numf) return false;
	_data.coin -= numf;
	return true;
}

void DataManager::setLinkPlayer(Player* player)
{
	_player = player;
}

void DataManager::setLinkStageM(StageManager* stageM)
{
	_stageM = stageM;
}

int DataManager::getStage(int num)
{
	char str[256];
	char dir[256];

	ZeroMemory(dir, sizeof(dir));
	sprintf_s(dir, "\\%s%d.ini", "Save_Data", num);

	GetCurrentDirectory(256, str);
	strncat_s(str, 256, dir, 254);

	if (PathFileExists(str))
	{
		_data.curStage = GetPrivateProfileInt("Stage", "CurrentStage", 0, str);
		return _data.curStage;
	}
	else
	{
		return -1;
	}
}
