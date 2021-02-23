#include "stdafx.h"
#include "keyManager.h"

keyManager::keyManager()
{
}


keyManager::~keyManager()
{
}

HRESULT keyManager::init()
{
	for (int i = 0; i < KEYMAX; i++)
	{
		this->getKeyUp().set(i, false);
	}
	return S_OK;
}

void keyManager::release()
{
}

bool keyManager::isOnceKeyDown(int key)
{
	//이전에 누른적이 없고 호풀시점에 눌림
	if (GetAsyncKeyState(key) & 0x8000)
	{
		if (!this->getKeyDown()[key])
		{
			this->setKeyDown(key, true);
			return true;
		}
	}
	else this->setKeyDown(key, false);
	return false;
}

//받은 키를 키버퍼(벡터)에 집어넣는다. 
bool keyManager::isOnceKeyDownV(int key)
{
	//이전에 누른 적이 없고 호출 시점에는 눌려있는 상태
	if (GetAsyncKeyState(key) & 0x8000)
	{
		//현재이 객체의 getkey다운의 인덱스번호가 false일경우 즉, 키입력이 들어온 경우
		if (!this->getKeyDown()[key])
		{
			this->setKeyDown(key, true);
			_vKeyComendBuffer.push_back(key); //키벡터에집어넣는다!!
			return true;
		}
	}

	else this->setKeyDown(key, false);
	return false;
}

bool keyManager::isOnceKeyUp(int key)
{
	if (GetAsyncKeyState(key) & 0x8000) this->setKeyUp(key, true);

	else
	{
		if (this->getKeyUp()[key])
		{
			this->setKeyUp(key, false);
			return true;
		}
	}

	return false;
}

bool keyManager::isStayKeyDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000) return true;

	return false;
}

bool keyManager::isToggleKey(int key)
{
	//GetKeyState vs GetASyncKeyState
	if (GetKeyState(key) & 0x0001) return true;
	return false;
}

//키버퍼(벡터)를 비운다
void keyManager::clearVKey()
{
	_vKeyComendBuffer.clear();
}
