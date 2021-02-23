#include "stdafx.h"
#include "Event.h"
#include "Video.h"
#include "Player.h"
#include "UI.h"
#include "EnemyManager.h"


void Event::enter(bool playerControl)
{
	_isMovie = _isCameraMove = false;
	if (_player) _player->setIsControl(playerControl);
}

void Event::exit()
{
	_isMovie = _isCameraMove = false;
	if (_player) _player->setIsControl(true);
}

/*====================================================================
	카메라 이동과 배율 조정 이벤트
====================================================================*/
cameraMove::cameraMove(vector3 goal, float moveSpeed, float mag, float magSpeed)
{
	_goal = goal;

	_goal.x += WINSIZEX / 2;
	_goal.y += WINSIZEY / 2;

	_moveSpeed = moveSpeed;
	_mag = mag;
	_magSpeed = magSpeed;
}
void cameraMove::enter(bool playerControl)
{
	Event::enter(playerControl);
	_isCameraMove = true;
}

bool cameraMove::update()
{
	CAMERA_M->SetPos(_goal.x, _goal.y, 0, 0, _moveSpeed);
	CAMERA_M->SetMagnification(_mag, _magSpeed);

	if (getDistance(CAMERA_M->GetX(), CAMERA_M->GetY(), _goal.x, _goal.y) < 50
		&& CAMERA_M->GetMagnificiation() == _mag)
	{
		CAMERA_M->SetPos(_goal.x, _goal.y);
		return true;
	}
	return false;
}

void cameraMove::exit()
{
	Event::exit();
}

/*====================================================================
	동영상 재생 이벤트
====================================================================*/
moviePlay::moviePlay(VIDEOTYPE file)
{
	_video = new Video;
	switch (file)
	{
	case VIDEOTYPE::GAME_INTRO:
		_video->init("source/video/intro.wmv");
		break;

	case VIDEOTYPE::BOSS_INTRO:
		_video->init("source/video/boss.wmv");
		break;

	default:
		break;
	}
}

void moviePlay::enter(bool playerControl)
{
	Event::enter(playerControl);

	_video->play();
	_isMovie = true;
}

bool moviePlay::update()
{
	//엔터나 스페이스바로 스킵
	if (_video->getIsPlaying() && (KEY_M->isOnceKeyDown(VK_RETURN) || KEY_M->isOnceKeyDown(VK_SPACE))) _video->stop();

	//영상 재생이 끝났는지 확인
	if (_video->getIsPlaying())
	{
		char lp[10];
		long mode = MCIWndGetMode(_video->getVideo(), lp, sizeof(lp));
		if (mode == 525)  _video->stop();	//영상 재생을 종료시킴
	}
	//영상 재생이 끝남을 리턴
	if (!_video->getIsPlaying()) return true;

	return false;
}

void moviePlay::exit()
{
	Event::exit();

	//영상 재생중이 아니라고 함.
	_isMovie = false;

	//영상 삭제
	SAFE_DELETE(_video);
}

/*====================================================================
	대사창과 대화 이벤트
====================================================================*/

dialogue::dialogue(DIALOGLIST file)
{
	string filePath = "source/dialog/";
	string fileName;
	{
		switch (file)
		{
		case DIALOGLIST::EASY_START:
			fileName = filePath + "easy_start.txt";
			break;
		case DIALOGLIST::BOSS_START:
			fileName = filePath + "boss_start.txt";
			break;
		case DIALOGLIST::BOSS_END:
			fileName = filePath + "boss_end.txt";
			break;
		default:
			break;
		}
	}
	_vScript = TXTDATA->txtLoad(fileName.c_str());
}

void dialogue::enter(bool playerControl)
{
	Event::enter(playerControl);
	if (_player) _player->setIsControl(false);

	_txtIndex = 0;
	_scriptIndex = 0;
	_autoSkip = true;
	_diaWindow = IMG_M->findImage("dialogWindow");
	_isRender = true;

	_img._portrait = IMG_M->findImage("shadow");
	_txtTime = TIME_M->getWorldTime();
	_txtInterval = 0.02f;

	_img._pos.x = 100;
	_img._pos.y = 500;
	_img._inter.moveTo(&_img._pos, _img._pos.x +
		cosf(getAngle(_img._pos.x, _img._pos.y, WINSIZEX / 2, _img._pos.y)) * 30, _img._pos.y, 0.3f);

	_state = DIALOGSTATE::ENTER;
}

bool dialogue::update()
{
	_img._inter.update();
	switch (_state)
	{
		case dialogue::DIALOGSTATE::ENTER:
		{	
			_dialogTime = TIME_M->getWorldTime();

			//현재 텍스트를 결정한다.
			_txt = _vScript[_scriptIndex];

			//이미지와 메시지를 결정한다.
			char imgfile[512];
			strncpy_s(imgfile, 512, _txt.c_str(), 510);
			char* _temp;
			strtok_s(imgfile, "@", &_temp);
			_txt = _temp;	//텍스트

			if (!strcmp(imgfile, "kyoko_1") || !strcmp(imgfile, "kyoko_2") || !strcmp(imgfile, "kyoko_3")) _img._dest = DIRECTION::LEFT;
			if (!strcmp(imgfile, "misuzu_1") || !strcmp(imgfile, "misuzu_2") || !strcmp(imgfile, "misuzu_3")) _img._dest = DIRECTION::RIGHT;

			switch (_img._dest)		//이미지 방향
			{
				case DIRECTION::LEFT:	 _img._pos.x = 100; _img._pos.y = 500;	_txtPos = 280;			break;
				case DIRECTION::RIGHT:	 _img._pos.x = WINSIZEX - 100; _img._pos.y = 500;	_txtPos = 80;  break;
			}
			_img._portrait = IMG_M->findImage(imgfile);		//초상화 이미지
			//이미지를 선형 보간으로 이동시킨다.
			_img._inter.moveTo(&_img._pos, _img._pos.x + cosf(getAngle(_img._pos.x, _img._pos.y, WINSIZEX / 2, _img._pos.y)) * 30, _img._pos.y, 0.3f);

			_state = DIALOGSTATE::UPDATE;
		}
		break;
		case dialogue::DIALOGSTATE::UPDATE:
		{
			//자동 스킵
			if (KEY_M->isOnceKeyDown(VK_LCONTROL)) { _autoSkip = !_autoSkip; }

			//전체 스킵
			if (KEY_M->isOnceKeyDown(VK_RETURN)) _scriptIndex = _vScript.size() - 1;

			//대사 한 글자씩 출력
			if (_txtIndex <= _txt.length() && TIME_M->getWorldTime() - _txtTime > _txtInterval)
			{
				_txtIndex++;
				_txtTime = TIME_M->getWorldTime();
			}

			//대사 바로 보이기
			if (_txtIndex < _txt.length() && KEY_M->isOnceKeyDown(VK_SPACE)) _txtIndex = _txt.length();

			//대사 스킵
			if (_txtIndex >= _txt.length()) _state = DIALOGSTATE::EXIT;

			//대화 끝내기
			if (_scriptIndex >= _vScript.size() - 1) return true;
		}
		break;
		case dialogue::DIALOGSTATE::EXIT:
		{
			if (KEY_M->isOnceKeyDown(VK_SPACE) || (_autoSkip && TIME_M->getWorldTime() - _dialogTime > strlen(_txt.c_str()) * 0.05f + 0.6f))
			{
				_scriptIndex++;
				_txtIndex = 0;
				_state = DIALOGSTATE::ENTER;
			}
		}
		break;
	}
	return false;
}

void dialogue::exit()
{
	Event::exit();
	_isRender = false;
}

void dialogue::render(HDC hdc)
{
	if (!_isRender) return;

	//대사창을 그린다.
	_diaWindow->render(hdc, WINSIZEX/2, WINSIZEY-_diaWindow->getHeight()/2);
	
	//폰트에 대해 설정한다.
	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, RGB(255, 220, 255));
	HFONT font, oldFont;
	RECT rcText = RectMake(_txtPos, WINSIZEY - 135,  WINSIZEX-400, 320);
	font = CreateFont(50, 0, 0, 0, 0, false, false, false,
		DEFAULT_CHARSET, OUT_STRING_PRECIS, CLIP_DEFAULT_PRECIS,
		PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, TEXT("CookieRunOTF Bold"));
	oldFont = (HFONT)SelectObject(hdc, font);

	//텍스트를 출력한다.
	DrawText(hdc, TEXT(_txt.c_str()), _txtIndex, &rcText, DT_LEFT | DT_WORDBREAK | DT_VCENTER);

	//이미지를 출력한다.
	if (_img._portrait && _state != DIALOGSTATE::ENTER) _img._portrait->render(hdc, _img._pos.x, _img._pos.y);

	//폰트를 삭제한다.
	DeleteObject(font);
}

/*====================================================================
	second를 대기하는 이벤트
====================================================================*/
waitForSec::waitForSec(float sec)
{
	_endTime = TIME_M->getWorldTime() + sec;
}

void waitForSec::enter(bool playerControl)
{
	Event::enter(playerControl);
	_isCameraMove = true;
}

bool waitForSec::update()
{
	if (TIME_M->getWorldTime() >= _endTime) return true;
	return false;
}

void waitForSec::exit()
{
	Event::exit();
}



/*====================================================================
	지역락 이벤트
====================================================================*/
locationLock::locationLock()
{
	
}

void locationLock::enter(bool playerControl)
{
	_isMovie = false;
	_isCameraMove = true;
	if (_player) _player->setIsControl(playerControl);
	_event = (LocationLock*)UI_M->findUI("LocationLock");
	_event->resetUI();
	_event->setActive(true);
	_event->startLock();
}

bool locationLock::update()
{

	if (_player->getEnemyM()->getVEnemy().empty() && _event->getIsLockingEnd()) _event->setUnlockEnd(true);

	if (_event->isUnlockEnd() == true )
	{
		
		return true;
	}
	return false;
}

void locationLock::exit()
{
	Event::exit();
}

heart::heart(bool reverse)
{
	_isReverse = reverse;
}

/*====================================================================
	하트 이벤트
====================================================================*/
void heart::enter(bool playerControl)
{
	Event::enter(playerControl);
	if(_isReverse)_ratio = 1;
	else _ratio = 0.2f;
	_img = IMG_M->findImage("UI_heart");
	_timer = TIME_M->getWorldTime() + 0.5f;
}

bool heart::update()
{
	if (_isReverse)
	{

		//0.01로초마다 비율을 줄인다.
		if (TIME_M->getWorldTime() - _timer > 0.01f)
		{
			_ratio -= 0.02f;
			_timer = TIME_M->getWorldTime();
		}
		//비율이 0.2이하면 이벤트를 종료한다.
		if (_ratio <= 0.2f) return true;
		return false;
	}
	else
	{
		//0.01로초마다 비율로 늘린다.
		if (TIME_M->getWorldTime() - _timer > 0.01f)
		{
			_ratio += 0.02f;
			_timer = TIME_M->getWorldTime();
		}
		//비율이 1이상이면 이벤트를 종료한다.
		if (_ratio >= 1.0f) return true;
		return false;
	}
}

void heart::exit()
{
	Event::exit();
}

void heart::render(HDC hdc)
{
	_img->render(hdc, WINSIZEX/2+_img->getWidth()*(1-_ratio)/2 , WINSIZEY / 2 + _img->getHeight() *(1- _ratio)/2 , _ratio, _ratio);
}
