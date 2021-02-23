#include "stdafx.h"
#include "UI.h"
#include "Player.h"

HRESULT UI::init()
{
	return S_OK;
}

void UI::release()
{
}

/*====================================================================
						단일 이미지 UI
====================================================================*/
void UI::update()
{
}

void UI::render(HDC hdc)
{
	_img->render(hdc, _pos->x + _img->getWidth() / 2, _pos->y + _img->getHeight() / 2);
}

/*====================================================================
						Prgress Bar
====================================================================*/

Bar::Bar(image * front, image * back, int* currentGauge, int* maxGauge)
{
	_front = front;
	_back = back;
	_current = currentGauge;
	_max = maxGauge;
}
HRESULT Bar::init()
{
	_ratio = *_current / *_max;
	_rc = RectMakeCenter(_pos->x, _pos->y, _back->getWidth(), _back->getHeight());
	return S_OK;
}
void Bar::release()
{

}
void Bar::update()
{
	_ratio = (float)*_current / (float)*_max;
}
void Bar::render(HDC hdc)
{
	//Bar는 x, y가 Left Top 기준으로 그려진다.
	_back->render(hdc, _pos->x + _back->getWidth() / 2, _pos->y + _back->getHeight() / 2);
	_front->render(hdc, _pos->x, _pos->y, 0, 0, _front->getWidth()*_ratio, _front->getHeight());			//잘라 그리는 버전
	//_front->render(hdc, _pos.x + _front->getWidth() / 2, _pos.y + _back->getHeight() / 2, _ratio, 1); //비율로 축소 시켜 그리는 버전
}

/*====================================================================
						핸 드 폰
====================================================================*/
HRESULT CallPhone::init()
{
	_img = IMG_M->findImage("phone");
	_itemImg = IMG_M->findImage("ui_bat");
	return S_OK;
}

void CallPhone::release()
{
}

void CallPhone::update()
{
}


void CallPhone::render(HDC hdc)
{
	if(_isActive)
	{ 
		_img->render(hdc, WINSIZEX*0.2 , WINSIZEY*0.57);
		if (_player->getInfo().hasWeapon)_itemImg->render(hdc, WINSIZEX*0.186, WINSIZEY * 0.48);
	}
}

/*====================================================================
						지역락 UI
====================================================================*/
LocationLock::LocationLock()
{
	isLockingStart = isLockingEnd = isUnlockingStart = isUnlockingEnd = false;

	_chainLeft.img = IMG_M->findImage("Stage_UI_Chain_Left");
	_chainLeft.speed = 10;
	_chainLeft.pos = vector3(_chainLeft.img->getWidth() / 2, 0, (WINSIZEY / 2) * 3);

	_chainRight.img = IMG_M->findImage("Stage_UI_Chain_Right");
	_chainRight.speed = 10;
	_chainRight.pos = vector3(WINSIZEX - _chainRight.img->getWidth() / 2, 0, -WINSIZEY / 2);

	_chainTop.img = IMG_M->findImage("Stage_UI_Chain_Top");
	_chainTop.speed = 20;
	_chainTop.pos = vector3(-WINSIZEX / 2, 0, _chainTop.img->getHeight() / 2);

	_chainBottom.img = IMG_M->findImage("Stage_UI_Chain_Bottom");
	_chainBottom.speed = 20;
	_chainBottom.pos = vector3((WINSIZEX / 2) * 3, 0, WINSIZEY - _chainBottom.img->getHeight() / 2);

	_Lock = IMG_M->findImage("Stage_UI_Lock_Appear");

	_chainTimer = _lockTimer = 0;
	_imgFrameX = 0;
}


HRESULT LocationLock::init()
{
	return S_OK;
}

void LocationLock::release()
{
}

void LocationLock::update()
{
	_lockTimer += TIME_M->getElapsedTime();

	if (isLockingStart)
	{
		_chainTimer += TIME_M->getElapsedTime();

		if (isLockingEnd == false)
		{
			_chainLeft.pos.z -= _chainLeft.speed;
			_chainRight.pos.z += _chainRight.speed;
			_chainTop.pos.x += _chainTop.speed;
			_chainBottom.pos.x -= _chainBottom.speed;
		}

		if (_chainTimer >= 1.0f)
		{
			isLockingEnd = true;
			isLockingStart = false;
		}
		return;
	}

	if (_lockTimer >= 5 * TIME_M->getElapsedTime())
	{
		_lockTimer = 0;
		_imgFrameX += 1;
		if (_imgFrameX >= _Lock->getMaxFrameX()) _imgFrameX = _Lock->getMaxFrameX();
	}
	
	if (isUnlockingStart)
	{
		if (_imgFrameX >= _Lock->getMaxFrameX())
		{
			_chainTimer += TIME_M->getElapsedTime();

			if (isUnlockingEnd == false)
			{
				_chainLeft.pos.z += _chainLeft.speed;
				_chainRight.pos.z -= _chainRight.speed;
				_chainTop.pos.x -= _chainTop.speed;
				_chainBottom.pos.x += _chainBottom.speed;
			}

			if (_chainTimer >= 1.0f)
			{
				isUnlockingStart = false;
				isUnlockingEnd = true;
				_isActive = false;
			}
		}
	}
}

void LocationLock::render(HDC hdc)
{
	_chainLeft.img->render(hdc, _chainLeft.pos.x, _chainLeft.pos.z);
	_chainRight.img->render(hdc, _chainRight.pos.x, _chainRight.pos.z);
	_chainTop.img->render(hdc, _chainTop.pos.x, _chainTop.pos.z);
	_chainBottom.img->render(hdc, _chainBottom.pos.x, _chainBottom.pos.z);
	if (isLockingEnd)
	{
		_Lock->frameRender(hdc, WINSIZEX / 2 + 15, _pos->z - WINSIZEY / 2 + _Lock->getFrameHeight() / 2 + 20, _imgFrameX, 0);
	}
}

void LocationLock::startLock()
{
	isLockingStart = true;
}

void LocationLock::resetFrameIdx()
{
	_imgFrameX = 0;
}

void LocationLock::changeLockImg1()
{
	_Lock = IMG_M->findImage("Stage_UI_Lock_Damage1");
}

void LocationLock::changeLockImg2()
{
	_Lock = IMG_M->findImage("Stage_UI_Lock_Damage2");
}

void LocationLock::startUnlock()
{
	isUnlockingStart = true;
	_Lock = IMG_M->findImage("Stage_UI_Lock_Disappear");
	_imgFrameX = 0;
	_chainTimer = 0;
}

void LocationLock::resetUI()
{
	isLockingStart = isLockingEnd = isUnlockingStart = isUnlockingEnd = false;

	_chainLeft.img = IMG_M->findImage("Stage_UI_Chain_Left");
	_chainLeft.speed = 10;
	_chainLeft.pos = vector3(_chainLeft.img->getWidth() / 2, 0, (WINSIZEY / 2) * 3);

	_chainRight.img = IMG_M->findImage("Stage_UI_Chain_Right");
	_chainRight.speed = 10;
	_chainRight.pos = vector3(WINSIZEX - _chainRight.img->getWidth() / 2, 0, -WINSIZEY / 2);

	_chainTop.img = IMG_M->findImage("Stage_UI_Chain_Top");
	_chainTop.speed = 20;
	_chainTop.pos = vector3(-WINSIZEX / 2, 0, _chainTop.img->getHeight() / 2);

	_chainBottom.img = IMG_M->findImage("Stage_UI_Chain_Bottom");
	_chainBottom.speed = 20;
	_chainBottom.pos = vector3((WINSIZEX / 2) * 3, 0, WINSIZEY - _chainBottom.img->getHeight() / 2);


	_Lock = IMG_M->findImage("Stage_UI_Lock_Appear");

	_chainTimer = _lockTimer = 0;
	_imgFrameX = 0;
}

HRESULT EndingUI::init()
{
	_img = IMG_M->findImage("endScene");
	return S_OK;
}

void EndingUI::release()
{
}

void EndingUI::update()
{
}

void EndingUI::render(HDC hdc)
{
	if (_isActive)
	{
		_img->render(hdc, WINSIZEX*0.5, WINSIZEY*0.57);
	}
}
